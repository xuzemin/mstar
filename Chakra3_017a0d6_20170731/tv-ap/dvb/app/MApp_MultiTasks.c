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
#define MAPP_MULTITASKS_C

//==============================================================================
/*                            Header Files                                      */
//==============================================================================
// C Library
#include <stdio.h>
#include "autotest.h"

// Global Layer
#include "Board.h"
#include "datatype.h"
#include "msAPI_Global.h"
#include "debug.h"


//Driver Layer
#include "hal_misc.h"
#include "drvDDC2BI.h"
#include "drvTVEncoder.h"
#include "drvpower_if.h"
#include "drvUART.h"
#include "drvCPU.h"

// API Layer
#include "msAPI_Timer.h"
#include "msAPI_Video.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "apiXC_Sys.h"
#include "apiXC_PCMonitor.h"
#include "apiXC_Dlc.h"
#include "apiXC_Hdmi.h"

#include "msAPI_Global.h"
#include "msAPI_IR.h"
#include "msAPI_DCC.h"
#include "msAPI_Power.h"

#include "msAPI_audio.h"
#include "msAPI_MIU.h"
#include "msAPI_FS_SysInfo.h"

#if( ENABLE_TEST_PATTERN )
#include "msAPI_TestPattern.h"
#endif


#include "MApp_GlobalSettingSt.h"
#include "MApp_Font.h"
#include "MApp_PixelID.h"
#include "MApp_ZUI_ACTcoexistWin.h"

#if (ENABLE_MHL == ENABLE)
#include "msAPI_MHL.h"
#if (MHL_TYPE == MHL_TYPE_INTERNAL)
#include "apiMHL.h"
#elif (MHL_TYPE == MHL_TYPE_ELAND)
#include "apiMHL_ELAND.h"
#endif
#endif

#if ENABLE_OAD
#include "MApp_OAD.h"
#endif //ENABLE_OAD

#if ENABLE_CEC
#include "msAPI_CEC.h"
#endif

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
//#include "msAPI_vbi.h"
#endif
// APP Layer
#if (ENABLE_PVR)
#include "MApp_UiPvr.h"
#include "MApp_TimeShift.h"
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_CIPVR_Adaption.h"
#endif
#ifdef PVR_8051
#include "MApp_Pvr.h"
#endif
#endif

#if (ENABLE_SUBTITLE)
#include "MApp_Subtitle.h"
#endif

#if (ENABLE_EWS)
#include "MApp_EWS.h"
#endif
#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_IR.h"
#include "MApp_Init.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#include "mapp_si.h"
#include "mapp_si_util.h"
#endif

//ZUI: #include "MApp_DispMenu.h"
#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif

#include "MApp_Init.h"
#include "MApp_Scan.h"
#include "MApp_SignalMonitor.h"
#include "MApp_PCMode.h"
#include "MApp_VDMode.h"
#include "MApp_MVDMode.h"
#include "MApp_MultiTasks.h"
#include "MApp_InputSource.h"
#include "MApp_Key.h"
#include "MApp_Sleep.h"
#include "MApp_NoOperate_AutoSleep.h"
#include "MApp_Main.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_BlockSys.h" //ZUI:
#include "MApp_EpgTimer.h"
#include "MApp_ChannelList.h"
#include "MApp_TV.h"
#include "MApp_AnalogInputs.h"
#include "MApp_SaveData.h"
#include "MApp_TopStateMachine.h"
#include "MApp_ChannelChange.h"

#if ENABLE_TTSTEST_FROM_USB
#include "MApp_ZUI_ACTmainpage.h"
#endif

#if MHEG5_ENABLE
#include "msAPI_MHEG5.h"
#include "MApp_MHEG5_Main.h"
#endif

#include "MApp_Scaler.h"
#include "MApp_XC_Sys.h"

#if (ENABLE_SECURITY_R2)
#include "msAPI_SecurityR2.h"
#endif


#if (EEPROM_DB_STORAGE!=EEPROM_SAVE_ALL)
#include "MApp_DataBase.h"
#endif

#include "MApp_ATVProc.h"

#if (ENABLE_TTX)
#include "mapp_ttx.h"
#endif

//#include "ZL10353.h"
#include "msIR.h"


#if (ENABLE_MVDMONITOR)
//#include "saturn.h"
static U8 u8MVDMonitor_FailCount = 0;
#endif

#if ENABLE_DMP
#include "mapp_mplayer.h"
#include "MApp_UiMediaPlayer.h"
#endif

#include "mapp_digitalmedia.h"

//#if (ENABLE_MADMONITOR)
//#include "msAPI_audio.h"
//#endif

// 5V Antenna Monitor
#include "GPIO.h"


#if ENABLE_CI
#include "MApp_CIMMI.h"
#include "msAPI_CI.h"
#endif
#include "msAPI_FreqTableDTV.h"

#if ENABLE_MSTV_UART_DEBUG
#include "drvUartDebug.h"
#endif


#include "MApp_Audio.h"

#if (ENABLE_S2_CI)
#include "MApp_GlobalVar.h"
#endif

#include "msAPI_MailBox.h"
#if (ENABLE_NEW_AUTO_NR)
#include "msAPI_NR.h"
#endif

#ifdef CUS_HISENSE
#include "drvMWE.h"
#endif

#if ENABLE_DIP_MONITOR
#include "mapp_dipclk_monitor.h"
#endif
#include "MApp_ZUI_GlobalFunction.h"

#include "msAPI_Demod.h"


#if ENABLE_S2
#include "MApp_MenuChannel.h"
#include "ZUI_exefunc.h"
#endif
#if (ENABLE_CI_PLUS)
#include "MApp_CIMMI.h"
#include "MApp_ZUI_ACTcimmi.h"
#endif//ENABLE_CI_PLUS

#if(ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#include "msAPI_MSDCtrl.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_ACTmsgbox.h"

#if (CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

#include "IF_Demodulator.h"
#if ENABLE_KEY_LOGGER
#include "MApp_KeyLogger.h"
#endif

#include "MApp_ParentalRating.h"
#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
#include "MApp_UiMenuFunc_ATSC.h"
#endif

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#endif


#if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
#include "MApp_VChip.h"
#endif


#include "MApp_AVSync.h"

#include "MApp_ZUI_ACTinputsource.h"

#if (NO_SIGNAL_AUTO_SHUTDOWN )
#include "MApp_NoSignal_AutoSleep.h"
#endif

#if(ENABLE_DVB)
#include "MApp_SDT_Monitor.h"
#endif

#if (LD_ENABLE)
#include "msAPI_LD.h"
#endif

#if GAME_ENABLE
#include "MApp_Game_Main.h"
#endif

#if ENABLE_KEY_TO_SPEECH
#include "MApp_KeyToSpeech.h"
#endif

#include "msAPI_DrvInit.h" //MP333


//
//======================================================
//

//static U32 u32PMRTCUpdateTimer=0;
#define PM_RTC_UPDATE_TIMEOUT    1000 //ms

extern void MApp_KeyProc_Mute(void);
extern void MApp_UiMenu_MuteWin_Hide(void);

#if ENABLE_DTV
BOOLEAN gu8VerChange = FALSE;
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

#ifndef AUTOBOOT
#define AUTOBOOT    0
#endif

#ifndef AUTOBOOTCL
#define AUTOBOOTCL  0
#endif

#if ENABLE_S2
BYTE test_13_18V = 0;
#endif

/********************************************************************************/
/*                               Macro                                          */
/********************************************************************************/
//#define PARA_MSG(x) //x

// 070523_SK 5V Antenna Monitor
#define _HIGH   1
#define _LOW    0

#define ANTENNA_5V_MONITOR_TIME        100        // every 100msec

#ifndef VDEC_SCREEN_MUTE_TIME_OUT
  #if(ENABLE_RIKS_TV)
    #define VDEC_SCREEN_MUTE_TIME_OUT   750    //ms
    #define VDEC_HVD_SCREEN_MUTE_TIME_OUT   VDEC_SCREEN_MUTE_TIME_OUT   //ms
  #elif (ENABLE_ISDBT)
    #define VDEC_SCREEN_MUTE_TIME_OUT   2500
    #define VDEC_HVD_SCREEN_MUTE_TIME_OUT   VDEC_SCREEN_MUTE_TIME_OUT    //ms
  #else
    #define VDEC_SCREEN_MUTE_TIME_OUT   500    //ms
    #define VDEC_HVD_SCREEN_MUTE_TIME_OUT   1500    //ms
  #endif
#endif

//#define MAX_SI_SDT_WAIT_FREECA_TIME 1000 // Wait MAD/MVD decode time when scramble
//#if ENABLE_SDT_OTHER_MONITOR
//#define CHANGE_TO_MOVE_SERVICE_TIMEOUT 15000
//#endif

#if (ENABLE_CI_PLUS)
#define MSRV_DVB_PLAYER_CI_FREE_TUNE_INFO(x)     {\
                                                        if (NULL != x.pu8TuneDescriptors)\
                                                        {\
                                                            free(x.pu8TuneDescriptors);\
                                                        }\
                                                        memset(&(x), 0x00, sizeof(x));\
                                                    }
#endif //ENABLE_CI_PLUS

/********************************************************************************/
/*                                 Local                                        */
/********************************************************************************/
static BOOLEAN m_bAntenna5VMonitorEnable;
static DWORD m_dwAntenna5VMonitorTimer;


#ifdef ENABLE_5VANTENNA
static void Antenna5VMonitor(void);
#endif

#if (ENABLE_DVB)
static void _MApp_Service_Check( void );
#endif

//ZUI
//static void MApp_PreProcessKey(void);

#if (ENABLE_DTV)
static BOOLEAN _bAutoSystemTime = FALSE;
#endif
#if ENABLE_FileIn_PMTMonitor
BOOLEAN _RecordUpdateAllPIDs = FALSE;
#endif
extern BOOLEAN g_bMheg5Existed;
#if (ENABLE_DTV)
typedef struct   //Same Service ID
{
    U8  u8bStillPic :1;
    U8  u8fMHEG5    :1;
    U8  u8IsCAExist :1;
    U8  eVideoType  :3;
    U8  u8Reserved  :2;
    U16 wPmtPid;
    U16 wVideo_PID;
    U16 wPCRPid;
    U8  u8AudStreamNum;
    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];
} MS_CUR_SERVICE_INFO;

#endif
extern BOOL bIsMoreOpTune;

#if ENABLE_USB_DEVICE_LIST
static U32 m_u32USBDeviceCheckTimer;
#endif


/********************************************************************************/
/*                               Functions                                      */
/********************************************************************************/

//=======================================================
// Local function:
#if ENABLE_DTV
void MApp_VDEC_Task(void);
#endif

//=======================================================
#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC) ||  (ATSC_CC == DTV_CC))
static void MApp_FontLoadMonitor(void)
{
    if (enCCFontStatus !=CC_FONT_LOAD)
    {
        if (MApp_LoadFont_CC() == TRUE)
        {
            enCCFontStatus=CC_FONT_LOAD;
        }
    }
}
#endif

#if 0//(ENABLE_DREC || ENABLE_BULK_FILE_SYSTEM)
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#endif

#if ENABLE_DMP
#if ENABLE_USB_DEVICE_LIST
#include "MApp_MassStorage.h"
#include "MApp_DMP_Main.h"

static void _MApp_Storage_Monitor(void)
{
#if ENABLE_DTV_CHCEK_USB_DELAY_2S
    if (g_u8DTVCheckUSBFlag&DTV_CHECK_USB_MONITOR_START_BIT)
        return;
#endif

    if(msAPI_Timer_DiffTimeFromNow(m_u32USBDeviceCheckTimer) > 500 )
    {
        EN_TOP_STATE TopState;
        TopState = MApp_TopStateMachine_GetTopState();
        static U8 PowerOnFlag=TRUE;
        static U8 u8oldUSBState;
        U8 u8USBState=MApp_MassStorage_DeviceConnectionDetect();

        if (PowerOnFlag)
        {
            u8oldUSBState =MApp_MassStorage_DeviceConnectionDetect();

            if (MApp_MassStorage_DeviceChangeStatusCheck())
            {
                MApp_MassStorage_DeviceStatusCheck();

                if(MApp_MassStorage_IsGetUnsupportUsbDevice())
                    g_u8USBValidflag = FALSE;
                else
                    g_u8USBValidflag = TRUE;
            }
            PowerOnFlag=FALSE;
        }

        // need refine here
        //at these state machine do not do anything,just update
        if (TopState == STATE_TOP_DMP
            ||TopState == STATE_TOP_ATV_SCAN
            ||TopState == STATE_TOP_ATV_MANUAL_TUNING
            //||TopState == STATE_TOP_CHANNELCHANGE
            ||(MApp_ZUI_GetActiveOSD() == E_OSD_FACTORY_MENU)
           )
        {
            u8oldUSBState =MApp_MassStorage_DeviceConnectionDetect();

            if ((u8oldUSBState != u8USBState))
            {
                if(( (u8USBState & MS_USB_CONNECTED) || (u8USBState & MS_USB2_CONNECTED) ) && MDrv_GetUsbDevInterfaceClass()!=0x09)
                    g_u8USBdetectflag=TRUE;
                else  if(!(u8USBState & MS_USB_CONNECTED) && !(u8USBState & MS_USB2_CONNECTED))
                    g_u8USBdetectflag=FALSE;

                if (g_u8USBdetectflag == TRUE)
                {
                    if (MApp_MassStorage_DeviceChangeStatusCheck())
                    {
                        MApp_MassStorage_DeviceStatusCheck();

                        if(MApp_MassStorage_IsGetUnsupportUsbDevice())
                        {
                            g_u8USBValidflag = FALSE;
                        }
                        else
                        {
                            g_u8USBValidflag = TRUE;
                        }
                    }
                }
                else
                {
                    MApp_MassStorage_DeviceChangeStatusCheck();
                    g_u8USBValidflag = FALSE;
                }
            }
        }
        else
        {
            if ((u8oldUSBState != u8USBState))
            {
                if(( (u8USBState & MS_USB_CONNECTED) || (u8USBState & MS_USB2_CONNECTED) ) && MDrv_GetUsbDevInterfaceClass()!=0x09)
                    g_u8USBdetectflag=TRUE;
                else  if(!(u8USBState & MS_USB_CONNECTED) && !(u8USBState & MS_USB2_CONNECTED))
                    g_u8USBdetectflag=FALSE;

                if (g_u8USBdetectflag == TRUE)
                {
                    if (MApp_MassStorage_DeviceChangeStatusCheck() == TRUE)
                    {
                        MApp_MassStorage_DeviceStatusCheck();
                    }

                    if(MApp_MassStorage_IsGetUnsupportUsbDevice())
                    {
                        g_u8USBValidflag = FALSE;
                    }
                    else
                    {
                        g_u8USBValidflag = TRUE;
                    }
                }
                else
                {
                    if (MApp_MassStorage_DeviceChangeStatusCheck() == TRUE)
                    {
                        MApp_MassStorage_DeviceStatusCheck();
                    }
                    g_u8USBValidflag = FALSE;
                }

                if ((g_u8USBdetectflag == TRUE)&&(g_u8USBValidflag == TRUE))
                {
                    MApp_MPlayer_InitializeAllDevices();
                    MApp_DMP_RecalculateDriveMappingTable();

                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_USB_LIST_MSG);
                }
                else
                {
                }
            }

        u8oldUSBState =u8USBState;
        }
        m_u32USBDeviceCheckTimer = msAPI_Timer_GetTime0();
    }
}
#endif
#endif

#if ENABLE_PVR
#include "msAPI_PVRFileSystem.h"
#endif

#if 0//(ENABLE_DREC)
#include "MApp_MSD.h"
#define DREC_FLAG_TICK 10UL*1024*1024

static U8 _DREC_Status=0;//0 stop 1 play
static U32 _DREC_SectorPos=0;
static U8 _DREC_KeyCount=0;
static U8 _DREC_FID=0xFF;
static U32 _DREC_BufferCurrentPos=DREC_RECORDER_BUFFER_ADR;
static U32 _DREC_RecordedBytes=0;// bytes that are already recorded
static U32 _DREC_Flag=DREC_FLAG_TICK*1;
static U32 _DREC_Timer;
static U32 _DREC_StartCluster=0;
static U8 _DREC_FileNumber;
static U32 _DREC_DiskTotalSectors;
static U8 _DREC_EnvironmentID=0xFF;

static U32 _DREC_RecorderSectorWrite(U8 driveNo,U32 addr, U32 len)
{
    U32 writeSectorCount;
    MSDCtrl_Drive drive;

    if (!msAPI_FCtrl_GetDriveByIndex(driveNo,&drive))
    {
        printf("    Get drive failed!!\n");
        return 0xFFFFFFFF;
    }

    if (len==0)
    {
        return 0;
    }
    else
    {
        writeSectorCount=len>>9;
    }

    if ((writeSectorCount+_DREC_SectorPos) > _DREC_DiskTotalSectors)
    {
        printf("    Disk full!!\n");
        return 0xFFFFFFFF;
    }


    if (writeSectorCount>0)
    {

        if (!msAPI_MSDCtrl_SectorWrite(drive.DeviceIndex,_DREC_SectorPos, writeSectorCount,addr ))
        {
            printf("    Write failed!!\n");
            return 0xFFFFFFFF;
        }
        else
            _DREC_SectorPos+=writeSectorCount;

    }
    return writeSectorCount<<9;
}

static _DREC_Stop()
{

        MApi_DMX_Stop(_DREC_FID);
        MApi_DMX_Close(_DREC_FID);

        printf("Total Recorded Bytes: 0x%08lx (%lu bytes/sec)\n",_DREC_RecordedBytes,(_DREC_RecordedBytes/(msAPI_Timer_DiffTimeFromNow(_DREC_Timer)/1000)));
        msAPI_FCtrl_FinishDRECFile(0 ,_DREC_FileNumber ,_DREC_StartCluster ,_DREC_RecordedBytes);
        msAPI_FSEnv_UnRegister(_DREC_EnvironmentID);
        _DREC_EnvironmentID=0xFF;

        MApp_Dmx_EnableTableMonitor();
}
static _DREC_ForceStop()
{
    _DREC_Stop();
    _DREC_Status=0;
}

static BOOLEAN _DREC_Initial()
{

    FileEntry fileEntry;
    printf("DREC_RECORDER_BUFFER_ADR=0x%08lx\n",(U32)DREC_RECORDER_BUFFER_ADR);

    MApp_Dmx_DisableTableMonitor();

    if (!msAPI_FCtrl_IsDriveMounted(0))
    {
        msAPI_MSDCtrl_CheckDevices();
        if (msAPI_MSDCtrl_GetDeviceStatus(0) == MSD_STATUS_INSERTED)
        {
            if (!msAPI_FCtrl_ActiveDevice(0))
            {
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
    }


    _DREC_EnvironmentID=msAPI_FSEnv_Register(0);

    if (_DREC_EnvironmentID==0xFF)
    {
        return FALSE;
    }

    if (!msAPI_FCtrl_DirectoryChangeToRoot(_DREC_EnvironmentID))
    {
        __ASSERT(0);
        return FALSE;
    }

    _DREC_FileNumber=0;


    while(msAPI_FCtrl_EntryNext(_DREC_EnvironmentID,&fileEntry)==ENTRY_NEXT_RESULT_SUCCESS)
        _DREC_FileNumber++;

    _DREC_FileNumber+=1;


    if (!msAPI_FCtrl_CreateDRECFile(0,_DREC_FileNumber,&_DREC_StartCluster,&_DREC_SectorPos))
    {
        return FALSE;
    }

    _DREC_FID=msAPI_DMX_Open(MSAPI_DMX_FILTER_TYPE_RECORD);
    msAPI_DMX_SetPid(_DREC_FID, MSAPI_DMX_BYPASS_PID);  // IF PID == MSAPI_DMX_BYPASS_PID THEN Record All
    //msAPI_DMX_SetRecordBuffer(_DREC_FID,  DREC_RECORDER_BUFFER_ADR,  DREC_RECORDER_BUFFER_LEN);
    msAPI_DMX_SetRecordBuffer(DREC_RECORDER_BUFFER_ADR,  DREC_RECORDER_BUFFER_LEN);

    msAPI_DMX_Reset(_DREC_FID);
    msAPI_DMX_Start(_DREC_FID);
    _DREC_Timer=msAPI_Timer_GetTime0();

    return TRUE;
}


static void _DREC_Task()
{

    if (_DREC_Status==1)
    {

        U32 inBufferPos=0;
        U32 len=0;
        U32 writeLen=0;

        inBufferPos=msAPI_DMX_GetRecordWrite();
        if (inBufferPos<_DREC_BufferCurrentPos)
        {
           len=((DREC_RECORDER_BUFFER_ADR+DREC_RECORDER_BUFFER_LEN)-_DREC_BufferCurrentPos);
           if ((len+_DREC_RecordedBytes)>0xFF000000)
           {
               printf("DREC stopped due to size limitation!!\n");
               _DREC_ForceStop();

               return;
           }

           writeLen=_DREC_RecorderSectorWrite(0,_DREC_BufferCurrentPos,len);
           if (writeLen==0xFFFFFFFF)
           {

               printf("DREC stopped due to write error!!\n");
               _DREC_ForceStop();

               return;
           }
           _DREC_RecordedBytes+=writeLen;
           _DREC_BufferCurrentPos=DREC_RECORDER_BUFFER_ADR;
        }
        //printf("inBufferPos=0x%08lx,_DREC_BufferCurrentPos=0x%08lx\n",inBufferPos,_DREC_BufferCurrentPos);
        len=inBufferPos-_DREC_BufferCurrentPos;

        if ((len+_DREC_RecordedBytes)>0xFF000000)
        {
               printf("DREC stopped due to size limitation!!\n");
               _DREC_ForceStop();

               return;
        }

        if (len>0)
        {
            writeLen=_DREC_RecorderSectorWrite(0,_DREC_BufferCurrentPos,len);
            if (writeLen==0xFFFFFFFF)
            {
                printf("DREC stopped due to write error!!\n");
                _DREC_ForceStop();

                return;
            }

            _DREC_RecordedBytes+=writeLen;
            _DREC_BufferCurrentPos+=writeLen;


            if (_DREC_RecordedBytes>_DREC_Flag)
            {
                printf("    Recorded Bytes=0x%08lx, Elapsed Time=%08lu\n",_DREC_RecordedBytes,msAPI_Timer_DiffTimeFromNow(_DREC_Timer));
                _DREC_Flag+=DREC_FLAG_TICK;
            }
        }
    }
}
#endif

#if MHEG5_ENABLE

/* this function is called in mheg5 loop for enabling AV when change AV pid                     */
/* because it calls static function "MApp_ScreenMuteMonitor", so we create this function here   */
// MApp_MHEG_MultiTasks -- for S4, S4L...
bool MApp_MHEG_MultiTasks(void)
{
    //Replace by callback function. 090625 k.

    //For Sleep Timer -- exit mheg ui
    if (u8KeyCode ==  KEY_COUNTDOWN_EXIT_TT_SUBTITLE)
    {
    #if CIPLUS_MHEG_1_3
        msAPI_MHEG5_Key_Transmit( KEY_MENU, 0 );
    #else
        msAPI_MHEG5_Key_Transmit( KEY_INFO, 0 );
    #endif
        MApp_ChannelPosition_Restore();
    }

    // always return true. this return value is useless, no code should use this return value.
    return TRUE;
}

#endif
#if (0)
U8 u8MuteDelayFlag;
U32 u32MUTEWaitTimer;
static void MApp_KeyProc_Mute_Moniter()
{
#if ENABLE_KEEP_MUTE_ICON
    static U32 u32MUTEWaitTimer;
    BOOLEAN bIsAudioMuted;

    if ( STATE_TOP_CHANNELCHANGE == MApp_TopStateMachine_GetTopState())
    {
        return;
    }

    bIsAudioMuted = msAPI_AUD_IsAudioMutedByUser();
 //printf("bIsAudioMuted=%bx,%bx\n",bIsAudioMuted,u8OSDGWinTbl[GWIN_MUTE]);
    if (bIsAudioMuted && u8OSDGWinTbl[GWIN_MUTE] == GWIN_ID_INVALID)
    {
        U8 u8IdS, u8IdE;
        if (u8MuteDelayFlag == 0)
        {
            u32MUTEWaitTimer = msAPI_Timer_GetTime0();
            u8MuteDelayFlag++;
            return;
        }
        if ( msAPI_Timer_DiffTimeFromNow( u32MUTEWaitTimer ) < 1500L)
        {//delay until top_state stable
            return;
        }
        u8MuteDelayFlag = 0;

        printf("Mute_Moniter\n");
        u8IdS = GWIN_ID_3;//GWIN_ID_1;
        u8IdE = MAXNUM_GWIN;//GWIN_ID_0;
        for (; u8IdS<u8IdE; u8IdS++)
        {
            if (u8OSDGWinTbl[u8IdS] != GWIN_ID_INVALID)
            {// GWIN_ID_1 used by other menu page
            printf("u8IdS=%bx\n",u8IdS);
                return;
            }
        }
        MApp_UiMenu_DrawMuteWin();

    }

#else
    BOOLEAN bIsAudioMuted;
    bIsAudioMuted = msAPI_AUD_IsAudioMutedByUser();

    if (bIsAudioMuted && (u32MonitorOsdTimer > 0))
    {
        if (msAPI_Timer_DiffTimeFromNow(u32MonitorOsdTimer) > MUTE_OSD_MONITOR_TIME)
        {
            MApp_UiMenu_ClearMuteWin();
            u32MonitorOsdTimer = 0;
        }
    }
#endif
}
#endif

#if ENABLE_CI
static BOOLEAN _bEnableCIProcess=TRUE;
void MApp_CI_Enable_Process(BOOLEAN bEnable)
{
    _bEnableCIProcess=bEnable;
}

void MApp_CI_Switch_TS(BOOLEAN bZarLinkReset)
{
    static U8 TS_State = 0;
    BOOLEAN bPVRMode = FALSE;

    bZarLinkReset=bZarLinkReset;

#if ENABLE_PVR
    if (MApp_PVR_IsRecording())
    {
        bPVRMode = TRUE;
        // When PVR is working, Should not chnage demod path
        return;
    }
#endif

    BOOL bCurCICardDetect = msAPI_CI_CardDetect();

    if ((TS_State != bCurCICardDetect))
    {
        /*if (bZarLinkReset)
        {
        }*/

    #if (ENABLE_S2_CI)
        if(IsS2InUse())
        {
        #if(FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211)
            if( bCurCICardDetect )
            {
                MDrv_CofdmDmd_SetTsSerial(0,1,1);
            }
            else
            {
                MDrv_CofdmDmd_SetTsSerial(0,0,1);
            }
        #endif
        }
    #endif

        if (bCurCICardDetect)
        {
        #if 0//(!ENABLE_CI_PLUS)
            msAPI_Tuner_Serial_Control(TRUE, bPVRMode);
            msAPI_Tuner_SetByPassMode(FALSE, bPVRMode);
        #endif

        #if 0//(ENABLE_S2_CI)
            if( IsS2InUse() )
            {
                //msAPI_Tuner_Serial_Control(TRUE,bPVRMode);
            }
        #endif

        #if(ENABLE_CI_PLUS)
            // Need check more: HSS
            msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_CI_BY_PASS);
        #else
            msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_CI_IN_USE);
        #endif

            TunerOnPCMCIA();
        }
        else
        {
            //msAPI_Tuner_Serial_Control(FALSE, bPVRMode);
            msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);

            TunerOffPCMCIA();
        }

    #if MHEG5_ENABLE
        MApp_MHEG5_RestoreWindow(TRUE);
    #endif

        TS_State = bCurCICardDetect;
    }
}

void MApp_MultiTasks_CI(void)
{
    if(_bEnableCIProcess==FALSE)return;

    if (msAPI_CI_Polling())
    {
        //ZUI: refine CIMMI: MMI_MessageHandle();
        MMI_MessageHandle();
    }

    if (g_bRealTimeMonitorOnly == FALSE)
    {
        MApp_CI_Switch_TS(TRUE);
        if (msAPI_CI_CardDetect())
        {
            if(TRUE == bIsMoreOpTune)
            {
                MApp_CI_CiEventCommandOpTune();
            }
            else
            {
                msAPI_CI_MAINLOOP();

            #if (ENABLE_CI_PLUS)
                if (TRUE == g_bOpSearchSuspended)
                {
                    if (msAPI_Timer_DiffTimeFromNow(g_u32OpSearchQueryPostEventTimer) > CI_OP_SEARCH_QUERY_POST_EVENT_INTERVAL)
                    {
                        printf("[CI+][OP] Post EV_CIPLUS_OP_REFRESH_QUERY Event to Idle Frame!\r\n");
                        MApp_ZUI_ACT_OPRefreshQueryUI();
                        g_u32OpSearchQueryPostEventTimer = msAPI_Timer_GetTime0();
                    }
                }

                MApp_CI_Monitor();
            #endif //ENABLE_CI_PLUS
            }
        }

        MMI_MessageHandle();
    }
}
#endif

void MApp_Time_Tasks(void)
{
    static U32 u32RTCUpdateTime = 0;

    if (msAPI_Timer_DiffTimeFromNow(u32RTCUpdateTime) > PM_RTC_UPDATE_TIMEOUT)
    {
        u32RTCUpdateTime = msAPI_Timer_GetTime0();
        MApp_Time_Tasks_Set_RTC_NextWakeUpTime();
    }

    #if 0 //non-used
    MApp_Timer_SetElapsedTimer();
    #endif

    if (g_u8TimeInfo_Flag != stGenSetting.g_Time.NVRAM_g_u8TimeInfo_Flag)
    {
        stGenSetting.g_Time.NVRAM_g_u8TimeInfo_Flag = g_u8TimeInfo_Flag;
    }
}

////////////////////////////////////////////////////////////////////////////////
// MIPS sends debug message to AEON by mailbox
////////////////////////////////////////////////////////////////////////////////

#define ENABLE_MIPS_MBOX_DBGOUT 0

#if(ENABLE_MIPS_MBOX_DBGOUT)
void MIPS_MBOX_DBGOUT(void)
{
    UART_DEVICE_TYPE uart;
    //U8 mailbox[13]={0};
    U32 *ptr;
    MBX_Msg MB_Message;

    memset(&MB_Message, 0, sizeof(MBX_Msg));

    if (MSApi_MBX_RecvMsg(E_MBX_CLASS_PRINT_MESSAGE, &MB_Message, 0,MBX_CHECK_NORMAL_MSG)==E_MBX_SUCCESS)
    {
        //MailBox MB;
        //MailBox* pMB = NULL;

        //memcpy(&MB, &mailbox[0], 13);
        //pMB = (MailBox *)&MB;
        uart = mdrv_uart_get_connection(E_UART_PORT0);
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
        if (uart != E_UART_AEON_R2)
        {
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
        }
#else
        if (uart != E_UART_AEON)
        {
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
        }
#endif
        ptr = (U32*)(((MB_Message.u8Parameters[0] << 24) & 0xFF000000)|
              ((MB_Message.u8Parameters[1] << 16) & 0x00FF0000)|
              ((MB_Message.u8Parameters[2] << 8 ) & 0x0000FF00)|
              ((MB_Message.u8Parameters[3]      ) & 0x000000FF));

        // Marked it by coverity_0489
        //printf("MIPS_MBOX_DBGOUT:%s\n", &ptr);
        mdrv_uart_connect(E_UART_PORT0, uart);
    }
}
#endif

//extern  U16 g_wRegsArray[10];

#if (ENABLE_DTV)

////////////////////////////////////////////
// DTV Handler
////////////////////////////////////////////
//#define DEBUG_DTV_HNDL_TIME()   //printf("DTV_HNDL-%u %u\n", __LINE__, MsOS_GetSystemTime());
#define DEBUG_DTV_HNDL_TIME()   //CHECK_MIU_PROTECT_LOG_AND_CLEAR()

void MApp_DTV_Handler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly)
{
#if(ENABLE_DVB)
    SCALER_WIN eWindow = MAIN_WINDOW;

    DEBUG_DTV_HNDL_TIME();


  #if (ENABLE_PIP)
    //either MAIN or SUB window input source can be DTV type
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        eWindow = MAIN_WINDOW;
    }
    else if (MApp_Get_PIPMode() != EN_PIP_MODE_OFF && IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
    {
        eWindow = SUB_WINDOW;
    }
  #endif

    DEBUG_DTV_HNDL_TIME();

    //////////////////////////////////////
    // DTV timing monitor
    if (fEnableSignalMonitor == TRUE)
    {
        MApp_SignalMonitor();

        DEBUG_DTV_HNDL_TIME();

        if (enFrotEndLockStatus == FRONTEND_LOCK)
        {
            if (fEnableMvdTimingMonitor == TRUE
             #if 0//def CI
               && (FALSE==MApp_Scramble_GetCurStatus() || msAPI_CI_CardDetect())
             #endif
               )
            {
                MApp_VID_TimingMonitor(eWindow);

                DEBUG_DTV_HNDL_TIME();

              #if (ENABLE_BOOTTIME)
                if (gbBootTimeFinish == FALSE)
                {
                    gU32BootStepTime = msAPI_Timer_GetTime0();
                }
              #endif

                fTVSetModeDone = MApp_VID_SetMode(eWindow);

                DEBUG_DTV_HNDL_TIME();

              #if (ENABLE_BOOTTIME)
                if (gbBootTimeFinish == FALSE)
                {
                    static U16 u16LoopCount = 0;
                    u16LoopCount++;

                    if (fTVSetModeDone)
                    {
                        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootStepTime);
                        printf("[TIME] MApp_VID_SetMode() use %ld\n", gU32TmpTime);

                        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                        printf("[TIME] u16LoopCount = %d, fTVSetModeDone = %ld\n", u16LoopCount, (int)gU32TmpTime);
                    }
                }
              #endif

              #if (ENABLE_AUTOTEST)
                if (gbBootTimeFinish == FALSE && fTVSetModeDone)
                {
                    PRINT_AUTOTEST_CHECKPT_TIME("start unmute");
                }
            #endif
                if (fTVSetModeDone == TRUE)
                {
                    msAPI_ClearIRFIFO();
                }
            }

            DEBUG_DTV_HNDL_TIME();

          #if (ENABLE_DTV_EPG)
            MApp_Dmx_EIT_Proc(5);
          #endif

            DEBUG_DTV_HNDL_TIME();

        #if ENABLE_FileIn_PMTMonitor
          #if ENABLE_PVR
            if (MApp_PVR_IsPlaybacking())
                 MApp_SI_FileIn_Parse();
          #endif
        #endif

            DEBUG_DTV_HNDL_TIME();

        #if(ENABLE_DVB)
            MApp_SI_Table_Monitor();
        #endif

            DEBUG_DTV_HNDL_TIME();

        #if (ENABLE_DTV_EPG)
            MApp_Dmx_EIT_Proc(10);
        #endif

            DEBUG_DTV_HNDL_TIME();

            if (MApp_Dmx_GetMonitorStatus(EN_MONITOR_TABLE_ALL))
            {
              #if ENABLE_PVR
                if (!MApp_PVR_IsPlaybacking())
              #endif
                {
                    _MApp_Service_Check();
                }

              #if ENABLE_SDT_OTHER_MONITOR
                //_MApp_Check_ChangeToSameService(); // Move to MApp_SDT_Monitor()
              #endif

            #if ENABLE_DVB
                if( IsDVBInUse() )
                {
                    MApp_SDT_Monitor();

                    MApp_ParentalRating_BlockStatus_Monitor();

                    //_MApp_SDT_FreeCAModeCheck(); // Move to MApp_SDT_Monitor()
                    //_MApp_SDT_RunningStatusCheck(); // Move to MApp_SDT_Monitor()
                }
            #endif

            #if 0
                if (MApp_SI_IsAutoClockValid())
                {
                    g_u8TimeInfo_Flag  |= UI_TIME_MANUAL_SET;
                    stGenSetting.g_Time.en_ClockMode = EN_ClockMode_Auto;
                }
                else
                {
                    stGenSetting.g_Time.en_ClockMode = EN_ClockMode_Manual;
                }
            #else
                if(stGenSetting.g_Time.en_ClockMode == EN_ClockMode_Auto)
                {
                    if(MApp_SI_IsAutoClockValid())
                    {
                        g_u8TimeInfo_Flag  |= UI_TIME_MANUAL_SET;
                        //stGenSetting.g_Time.en_ClockMode = EN_ClockMode_Auto;
                      #if (ENABLE_DTV)
                        _bAutoSystemTime = TRUE;
                      #endif
                    }
                    else
                    {
                        //stGenSetting.g_Time.en_ClockMode = EN_ClockMode_Manual;
                    #if (ENABLE_DTV)
                        _bAutoSystemTime = FALSE;
                    #endif
                    }
                }
            #endif

              #if MHEG5_ENABLE
                if ((g_bMHEG5Service == FALSE) && (SI_MHEG5_DISABLE != MApp_MHEG5_CheckMHEG5Status()))
                {
                    g_bMHEG5Service=TRUE;
                    if (msAPI_MHEG5_IsRunning() == false && msAPI_MHEG5_checkGoBackMHEG5()==false)
                    {
                        if (enCheckMHEGLoadingStatus == EN_MHEG5_WAIT)
                        {
                            enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
                        }
                    }
                }
              #endif

              #if ENABLE_PVR
                if (MApp_SI_IsTSChanged() && MApp_PVR_IsRecording())
                {
                    MApp_UiPvr_RecordStop();
                }
              #endif
            }
        }
        else if (enFrotEndLockStatus == FRONTEND_UNLOCK)
        {
        #if ENABLE_PVR
            if ( (MApp_PVR_StateMachineGet() == E_PVR_STATE_PLAYBACK)
               ||(MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORDnPLAYBACK)
               ||((MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT) && (MApp_TimeShift_IfPause() == FALSE))
               )
            {
                if (fEnableMvdTimingMonitor == TRUE)
                {
                    //MApp_Dmx_PES_Proc();
                    MApp_VID_TimingMonitor(eWindow);
                    fTVSetModeDone = MApp_VID_SetMode(eWindow);

                    if (fTVSetModeDone==TRUE)
                    {
                        msAPI_ClearIRFIFO();
                    }
                }

                // monitor SI table if no signal
            #if ENABLE_FileIn_PMTMonitor
              #if ENABLE_PVR
                if (MApp_PVR_IsPlaybacking())
                    MApp_SI_FileIn_Parse();
              #endif
            #endif

                if ( IsDVBInUse() )
                {
                    MApp_ParentalRating_BlockStatus_Monitor();
                }

                if (MApp_Dmx_GetMonitorStatus(EN_MONITOR_TABLE_ALL))
                {
                    MApp_SI_Table_Monitor();
                }
            }
        #endif // #if ENABLE_PVR
        }

        DEBUG_DTV_HNDL_TIME();

    #if ENABLE_OAD
        if(MApp_TopStateMachine_GetTopState() == STATE_TOP_OAD)
        {
            MApp_OAD_Monitor();
            MApp_OAD_Download() ;
          #if OAD_TEST
            MApp_OAD_AppTest();
          #endif
        }

        if(IsDTVInUse()&& MApp_OAD_IsUserSelectOn())
        {
            MApp_OAD_Monitor();
            MApp_OAD_Download();
        }
        DEBUG_DTV_HNDL_TIME();
    #endif

        MApp_Picture_AFDMonitor();

#if(ASTRA_HD_ENABLE)
        if(IsS2InUse())
        {
            if(msAPI_CM_GetAdd2ListFlag())
            {
                  msAPI_CM_IsAdd2List(FALSE);
                  MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                  MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_ADD_CHANNEL2LIST );
            }
        }
#endif

    }

    DEBUG_DTV_HNDL_TIME();

    //////////////////////////////////////
    // always do AV sync for DTMB
    //
  #if (AV_SYNC_ADJUST)
    MApp_AVSync_Adjust();

    DEBUG_DTV_HNDL_TIME();
  #endif

    //////////////////////////////////////
    // >> Teletex Handler
    //
#if ENABLE_TTX
    if ( (MApp_TTX_IsTeletextOn() == TRUE)
      #if PVR_AND_TTX_DIFF_WITH_MHEG5
       &&(MApp_TTX_CanBeTurnedOn())
      #endif
       )
    {
      #if ENABLE_PVR
        if ( (MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT)
           &&(MApp_TimeShift_StateMachineGet()== E_TIMESHIFT_STATE_RECORDING) )
        {
            ;
        }
        else
      #endif
        {
        #if ENABLE_PVR  //Add to reduce PVR write gap time related with TTX subtitle 20100721EL
          #if( (CHIP_FAMILY_TYPE != CHIP_FAMILY_EMERALD)    \
              &&(CHIP_FAMILY_TYPE != CHIP_FAMILY_MILAN)     \
              &&(CHIP_FAMILY_TYPE != CHIP_FAMILY_MARLON)    \
              )
            MApp_PVR_StateMachineRunning();
          #endif
        #endif

            MApp_TTX_Decoder_Process( );
        }

        if( MApp_ParentalControl_GetBlockStatus())
            MApp_TTX_TeletextCommand(TTX_TV);

        if( stGenSetting.g_SysSetting.fEnableTTXSubTitle == FALSE &&
            MApp_TTX_IsTeletextOn()==TRUE &&
            MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
        {
            MApp_TTX_TeletextCommand(TTX_TV);
        }
    }

    DEBUG_DTV_HNDL_TIME();

#endif // #if ENABLE_TTX
    //
    // << Teletex Handler
    //////////////////////////////////////


    //////////////////////////////////////
    // >> MHEG5 Handler
    //
#if (MHEG5_ENABLE)
  #if(ENABLE_S2_SOURCE)
    if ( IsDTVInUse()||IsS2InUse())
  #else
    if (IsDTVInUse())
  #endif
    {
    #if ENABLE_SUBTITLE
      #if (MHEG5_WITH_SUBTITLE==0)
        if ( ( ((stGenSetting.g_SysSetting.fEnableSubTitle == FALSE) || (u8SubtitleMenuNum==0))
             &&(MApp_Subtitle_IsRunning() == FALSE) )
          #if CIPLUS_MHEG_1_3
           ||(msAPI_MHEG5_GoMHEGWhenSubtitleOn() != 0 )   // go mheg process if mheg runs only or subtitle runs with hidden mheg
          #endif
           )
      #endif
    #endif
        {
            _MApp_MHEG5_Process();
        }
    }

    DEBUG_DTV_HNDL_TIME();

#endif // #if (MHEG5_ENABLE)
    //
    // << MHEG5 Handler
    //////////////////////////////////////


    //////////////////////////////////////
    // >> Subtitle Handler
    //
  #if ENABLE_SUBTITLE
    if (g_bRealTimeMonitorOnly == FALSE)
    {
        if (bEnableSubtitleTimeoutMonitor)
        {
            if (msAPI_Timer_DiffTimeFromNow(u32SubtitleTimeOut) > SUBTITLE_TIMEOUT_THRESHOLD)
            {
                MApp_Subtitle_TimeOut_Clear();
                bEnableSubtitleTimeoutMonitor = FALSE;
            }
        }

    #if (MHEG5_ENABLE && MHEG5_WITH_SUBTITLE)
        if (msAPI_MHEG5_GetSubtitleMode() == 1 || MApp_Subtitle_IsRunning() == TRUE)
    #endif
    #if MHEG5_ENABLE
      #if CIPLUS_MHEG_1_3
        if ( (enCheckMHEGLoadingStatus != EN_MHEG5_WAIT)
           ||(msAPI_MHEG5_GoMHEGWhenSubtitleOn() == 1)    //  subtitle runs with hidden mheg
           )
      #endif
    #endif
        {
        #if (SUBTITLE_WITH_OSD)
            if (msAPI_Timer_DiffTimeFromNow(u32SubtitleMainProcTimeOut) > SUBTITLE_MAINPROC_TIMEOUT_THRESHOLD
                ||(u8KeyCode != KEY_NULL))
            {
                DEBUG_DTV_HNDL_TIME();

                MApp_Subtitle_Main();

                DEBUG_DTV_HNDL_TIME();
                u32SubtitleMainProcTimeOut = msAPI_Timer_GetTime0();
            }
        #endif
        }

        DEBUG_DTV_HNDL_TIME();

        MApp_Subtitle_PID_Monitor();

        DEBUG_DTV_HNDL_TIME();
    }

    DEBUG_DTV_HNDL_TIME();

  #endif // #if ENABLE_SUBTITLE
    //
    // << Subtitle Handler
    //////////////////////////////////////


    //////////////////////////////////////
    // >> PVR Handler
    //
  #if ENABLE_PVR
    {
        if( MApp_Is_InAutoScan_ATV() || MApp_Is_InAutoScan_DTV() )
        {
            ;
        }
        else
        {
            MApp_PVR_StateMachineRunning();
            DEBUG_DTV_HNDL_TIME();
            MApp_TimeShift_StateMachineRunning();
        #if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
            MAPP_CIPVR_CIPVRActionMonitor();
        #endif
        }
    }

    DEBUG_DTV_HNDL_TIME();

  #endif // #if ENABLE_PVR
    //
    // << PVR Handler
    //////////////////////////////////////

#endif // #if(ENABLE_DVB)


    UNUSED(src); UNUSED(bRealTimeMonitorOnly);
}
#endif // #if (ENABLE_DTV)


////////////////////////////////////////////
// ATV Handler
////////////////////////////////////////////

#define ENABLE_DEBUG_ATV_HANDLER_TIME   0
#if( ENABLE_DEBUG_ATV_HANDLER_TIME )
    #define DEBUG_ATV_HANDLER_TIME(x)   x
#else
    #define DEBUG_ATV_HANDLER_TIME(x)
#endif
void MApp_ATV_Handler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly)
{
    UNUSED(src); UNUSED(bRealTimeMonitorOnly);
    SCALER_WIN eWindow = MAIN_WINDOW;
    static U32 s_ATV_Handler_u32LastTime = 0;
    DEBUG_ATV_HANDLER_TIME( U32 au32Times[4]; )


    if( msAPI_Timer_DiffTime_2(s_ATV_Handler_u32LastTime, MsOS_GetSystemTime()) < 8 )
    {
        return;
    }

    s_ATV_Handler_u32LastTime = MsOS_GetSystemTime();


#if 0//( DEBUG_CHG_SRC_TIME)
    printf("ATV-1 src=%u R=%u %u\n", src, bRealTimeMonitorOnly, g_Debug_u32Time_ChangeSrc);
#endif


  #if (ENABLE_PIP)
    //only one source of digital VD (AV/SV/ATV/SCART) can be present in the same time
    if (IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        eWindow = MAIN_WINDOW;
    }
    else if (MApp_Get_PIPMode() != EN_PIP_MODE_OFF && IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
    {
        eWindow = SUB_WINDOW;
    }
  #endif

    DEBUG_ATV_HANDLER_TIME( au32Times[0] = MsOS_GetSystemTime(); );


    DEBUG_ATV_HANDLER_TIME( au32Times[1] = MsOS_GetSystemTime(); );

    MApp_ATVProc_Handler(eWindow);

    DEBUG_ATV_HANDLER_TIME( au32Times[2] = MsOS_GetSystemTime(); );

  #if ENABLE_TTX
    if (MApp_TTX_IsTeletextOn() == TRUE)
    {
      #if ENABLE_PVR
        if ((MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT) &&
            (MApp_TimeShift_StateMachineGet()== E_TIMESHIFT_STATE_RECORDING))
        {

        }
        else
      #endif
        {
            MApp_TTX_Decoder_Process( );
        }
    }
  #endif

    DEBUG_ATV_HANDLER_TIME( au32Times[3] = MsOS_GetSystemTime(); );

#if 0//( DEBUG_CHG_SRC_TIME)
    printf("ATV-10 %u\n",  g_Debug_u32Time_ChangeSrc);
#endif

 {
    U16 u16StdTime = 20;

    if( IsATVInUse() ) // ATV
    {
        if( gbTVAutoScanChannelEnable )
        {
            //printf("[Scan]");
            u16StdTime = 100;
        }
    }
#if(ENABLE_DEBUG_ATV_HANDLER_TIME)
    if( msAPI_Timer_DiffTime_2(s_ATV_Handler_u32LastTime, MsOS_GetSystemTime()) > u16StdTime )
    {
        printf("%s use %u\n",  __FUNCTION__, msAPI_Timer_DiffTime_2(s_ATV_Handler_u32LastTime, MsOS_GetSystemTime()));
        {
            U8 i;
            for( i = 0; i < 4; ++ i )
            {
                printf("t_%u=%u\n", i, au32Times[i]);
            }
        }
    }
#endif
  }

}

//#if ENABLE_DMP
////////////////////////////////////////////
// Storage Handler (Media Player)
////////////////////////////////////////////
void MApp_Storage_Handler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly)
{
    UNUSED(src);
    UNUSED(bRealTimeMonitorOnly);
}
//#endif

static void _MApp_Video_Handler(BOOLEAN bRealTimeMonitorOnly)
{
  #if (ENABLE_SWITCH_CHANNEL_TIME)
    #define PT_MApp_VH_SetBeginTime()       u32TimeBegin = msAPI_Timer_GetTime0()
    #define PT_MApp_VH_PrintfTime(x)        u32TimeEnd = msAPI_Timer_DiffTimeFromNow(u32TimeBegin);          \
                                            if(u32TimeEnd > 2)                                               \
                                            {                                                                \
                                                printf(x, u32TimeEnd);                                       \
                                                SwitchChannelTimePrintf("--[Duration--%ld]\n");              \
                                            }                                                                \
                                            u32TimeBegin = msAPI_Timer_GetTime0()

    U32 u32TimeBegin = 0x00;
    U32 u32TimeEnd   = 0x00;
  #else
    #define PT_MApp_VH_SetBeginTime()   //CHECK_MIU_PROTECT_LOG_AND_CLEAR()
    #define PT_MApp_VH_PrintfTime(x)    //CHECK_MIU_PROTECT_LOG_AND_CLEAR()
  #endif

    PT_MApp_VH_SetBeginTime();

    MApi_XC_Mux_SourceMonitor(bRealTimeMonitorOnly);

    PT_MApp_VH_PrintfTime("[VH]MApi_XC_Mux_SourceMonitor() -- %ld");

    //MHL
#if (ENABLE_MHL == ENABLE)
   #if 0//(ENABLE_POST_INIT)
    if ( MApp_Get_PostInit_Status() == TRUE )
   #endif
    {
        msAPI_MHL_Handler(UI_INPUT_SOURCE_TYPE);
        PT_MApp_VH_PrintfTime("[VH]msAPI_MHL_Handler() -- %ld");
    }
#endif

    MApp_ScreenMuteMonitor(MAIN_WINDOW);
    PT_MApp_VH_PrintfTime("[VH]MApp_ScreenMuteMonitor(MAIN_WINDOW) -- %ld");

  #if (ENABLE_PIP)
    //To monitor sub window if PIP is enabled.
    if (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        MApp_ScreenMuteMonitor(SUB_WINDOW);
        PT_MApp_VH_PrintfTime("[VH]MApp_ScreenMuteMonitor(SUB_WINDOW) -- %ld");
    }
  #endif

    PT_MApp_VH_PrintfTime("[VH]_MApp_Video_Handler() -- %ld");
}

#if (ENABLE_PIP)
//To monitor sub window data struct;
// If the chip is only support 1 window and sub window struct had been modified ==> warning msg output!
static void _MApp_PIP_SubWinMonitor(void)
{
    if (stSystemInfo[SUB_WINDOW].enInputSourceType != INPUT_SOURCE_NONE)
    {
        printf("[PIP] SYS_INPUT_SOURCE_TYPE[SUB_WINDOW] = %d\n", stSystemInfo[SUB_WINDOW].enInputSourceType);
    }
}
#endif

void MApp_Vif_Handler(void)
{
#if ( ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)) )
    EN_VIF_WORKING_STATUS eVifWorkingStatus = MApp_InputSource_GetVifWorkingStatus();
    extern BOOLEAN gbTVAutoScanChannelEnable;

    if(eVifWorkingStatus == E_VIF_ON_ATV_DISPLAY)
    {
        MDrv_VIF_Handler(gbTVAutoScanChannelEnable);
    }
    else if(eVifWorkingStatus == E_VIF_ON_ATV_CVBSOUT)
    {
        MDrv_VIF_Handler(FALSE);
    }
    else
    {
        //Do nothing
    }
#endif
}


#define ENABLE_DEBUG_SHOW_SYS_INFO  1

#if( ENABLE_DEBUG_SHOW_SYS_INFO )
void MApp_Debug_ShowInfo_Task(void)
{
    static U32 s_u32ShowInfo_LastTime = 0;

#if (ENABLE_TEST_PATTERN)
    if( msAPI_TestPattern_Get_Status() )
    {
        return;
    }
#endif


    // Check video mute
    if( msAPI_Scaler_GetScreenMute(MAIN_WINDOW) )
    {
        if( FALSE == MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
        {
            PRINT_CURRENT_LINE();
        }
    }

    if( msAPI_Timer_DiffTime_2(s_u32ShowInfo_LastTime, MsOS_GetSystemTime()) < 5000 )
        return;

    s_u32ShowInfo_LastTime = MsOS_GetSystemTime();

    //printf("t=%u\n", s_u32ShowInfo_LastTime);
    //printf(" OPVSyncCount=%u\n", MApi_XC_Sys_Get_OutputVSyncCount());

    //printf(" MApi_XC_FrameLockCheck=%u\n", MApi_XC_FrameLockCheck());

#if 0//MP333
	//<<gchen @ 20180321 //MP333
	//check dc det 
	if(DC_get_level())
	{
		printf(" DC_get_level true \n");

		//if is bat det bat ad
		Detect_BatAD();
		//set bat led color
		
		//if bat ad < 5% then show bat low info 3 secs

		//set g_bBatLowFlag true g_bBatLowShowFlag is true

		//
		
		//iCountBatLowTime > 3 secs then set g_bBatLowShowFlag is false

	}
	else
	{
		printf(" DC_get_level false \n");
		//if is dc not det bat
		Detect_BatAD();
		//if g_bBatLowShowFlag is ture hide it
		
	}

	//check sw det
	if(PowerOff_get_level())
	{
		printf(" PowerOff_get_level true \n");
		//if sw det then power down
		//msAPI_Power_PowerDown_EXEC();
	}
	else
	{
		printf(" PowerOff_get_level false \n");
	}


	//>>gchen @ 20180321 //MP333


#endif

    DEBUG_HDMI_HOT_PLUG( MApi_XC_HDMI_Print_PortStatus(); );


    if ( (FALSE == MApp_Is_InAutoScan_DTV())
       &&(FALSE == MApp_Is_InAutoScan_ATV())
       )
    {
        // Check video mute
        BOOLEAN bPrintVideoMute = TRUE;

    #if( ENABLE_FM_RADIO )
        if( MApp_Is_CruSrcFMRadio() )
        {
            bPrintVideoMute = FALSE;
        }
    #endif

        if( bPrintVideoMute )
        {
            MApi_XC_Sys_CheckMuteStatus();
        }

        // Check Audio Mute
        if(MApp_ZUI_ACT_GetAudioMessageFlag())
        {
            if( msAPI_AUD_IsAudioMuted() )
            {
                //printf("Audio is muted\n");
                //msAPI_AUD_PrintMuteClient(); //MP333
            }
        }
    }

#if 0//(ENABLE_DTV)
    if( IsDTVInUse() )
    {
        EN_DEMODULATOR_TYPE eCurDemod = msAPI_Demod_GetCurrentDemodType();
        U16 u16SignalStrength = 0;

        // Show demod status
        printf("Cur demod=%u(%s):\n", eCurDemod, msAPI_Demod_Get_DemodTypeName(eCurDemod));
        printf(" Signal Quality=%u\n", msAPI_Demod_Get_SignalQualityPercentage(eCurDemod));


        FUNCTION_RESULT eFuncResult = msAPI_Tuner_CheckSignalStrength(&u16SignalStrength);
        if( eFuncResult == E_RESULT_SUCCESS )
        {
            printf(" u16SignalStrength=%u\n", u16SignalStrength);
        }

        BOOLEAN bDemodLockResult = FALSE;
        if(  msAPI_Tuner_CheckLock( &bDemodLockResult, FALSE) )
        {
            printf(" bDemodLock=%u\n", bDemodLockResult);
        }

        // Show last set tuner freq
        printf("Last tuner freq=%u\n", g_Debug_u32LastTunerFreq);
    }
#endif

}
#endif

void MApp_ScreenSaverHandler(void)
{

#if(ENABLE_TEST_PATTERN)
    if(msAPI_TestPattern_Get_Status())
    {
        SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
        if (MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER)
        {
            MApp_ZUI_ACT_ShutdownOSD();
        }
        return;
    }
#endif
      if (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) != EN_SCREENSAVER_NULL && MApp_TV_ScreenSaverClear(MAIN_WINDOW))
      {
          if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
          {
              if (MApp_GetSignalStatus() != SIGNAL_UNKNOWN &&
                  SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) != EN_SCREENSAVER_NO_SHOW_PROGRAM)
              {
                  SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
              }
          }
          else
          {
              SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
          }
      }

#if (ENABLE_PIP)
      if ((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NULL && MApp_TV_ScreenSaverClear(SUB_WINDOW))
      {
          if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
          {
              if (MApp_GetSignalStatus() != SIGNAL_UNKNOWN && SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NO_SHOW_PROGRAM)
              {
                  SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
              }
          }
          else
          {
              SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
          }
      }
#endif

      if (MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER)
      {
    #if (ENABLE_PIP)
          if ((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) == EN_SCREENSAVER_NULL) && (SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) == EN_SCREENSAVER_NULL))
          {
              MApp_ZUI_ACT_ShutdownOSD();
          }
          else
    #endif
          if ((SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) == EN_SCREENSAVER_NULL)
        #if (ENABLE_PIP)
              && (MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
        #endif
             )
          {
              MApp_ZUI_ACT_ShutdownOSD();
          }
      }

}

#if(ENABLE_CEC)
#define DEBUG_CEC_HANDLER_TIME  0
void MApp_CEC_Handler(void)
{
#if(DEBUG_CEC_HANDLER_TIME)
    U32 u32HandlerStartTime = MsOS_GetSystemTime();
#endif

    msAPI_CEC_Handler();

#if(DEBUG_CEC_HANDLER_TIME)
    U32 u32HandlerUseTime = msAPI_Timer_DiffTime_2(u32HandlerStartTime, MsOS_GetSystemTime());
    if( u32HandlerUseTime > 120 )
    {
        printf(" u32HandlerUseTime=%u\n", u32HandlerUseTime );
        //printf(" u32HandlerUseTime=%u, %u %u\n",u32HandlerUseTime, MApp_TTS_Get_DecodeBufferLevel_ms(), MApp_TTS_Get_AudioBufferLevel_ms() );
    }
#endif
}
#endif


//=============================================================
#define DEBUG_MULTI_TASK_TOTAL_TIME     1

#define ENABLE_MT_CHECK_POINT      0

#if( ENABLE_MT_CHECK_POINT )
    #define MT_CHECK_POINT_INIT()  U32 u32CheckPoint_Time1 = msAPI_Timer_GetTime0(); \
                                    U32 u32CheckPoint_Time2;    \
                                    U32 u32CheckPoint_Time3;
    #define MT_CHECK_POINT()        do { \
                                        u32CheckPoint_Time2 = msAPI_Timer_GetTime0();   \
                                        u32CheckPoint_Time3 = msAPI_Timer_DiffTime_2(u32CheckPoint_Time1,u32CheckPoint_Time2); \
                                        if( u32CheckPoint_Time3 > 4 )   \
                                        {   \
                                            printf("MT:Line_%u use %u\n", __LINE__, u32CheckPoint_Time3);   \
                                        }   \
                                        u32CheckPoint_Time1 = msAPI_Timer_GetTime0();   \
                                    } while(0)

#else
    #define MT_CHECK_POINT_INIT()   //PRINT_CURRENT_LINE()
    #define MT_CHECK_POINT()        //printf("<M %u>", __LINE__ ); //CHECK_MIU_PROTECT_LOG_AND_CLEAR() // PRINT_CURRENT_LINE() //

#endif

void MApp_MultiTasks(void)
{

#if ENABLE_UART2
	  //MDrv_UART2_TestRXD(); //gchen @ 20180118 //uart2
	  MDrv_UART2_MCU_RXD();
#endif

	#if (ENABLE_EAR_PHONE_VALUME_LINE) //MP333
	if(EAR_PHONE_get_level() != gU8EarPhoneChangeFlag)
	{
		//printf(" \n");
		printf("\ngU8EarPhoneChangeFlag2 = %d\n",gU8EarPhoneChangeFlag);
		printf("\ngU8EarPhoneChangeFlag3 = %d\n",EAR_PHONE_get_level());
		gU8EarPhoneChangeFlag = EAR_PHONE_get_level();
		msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
	}
	#endif
		if(EAR_PHONE_get_level())
		{
			//printf(" \n");
			MUTE_Off();
			EarPhone_ON();
		}
		else
		{
			//printf(" \n");
			MUTE_On();
			EarPhone_OFF();
		}
		

#if( DEBUG_MULTI_TASK_TOTAL_TIME )
    //static U32 s_MultiTask_u32LastEndTime = 0;
    static U32 s_MT_u32StartTime = 0;
    static U32 s_MultiTask_u32Counter = 0;

    s_MT_u32StartTime = MsOS_GetSystemTime();
    s_MultiTask_u32Counter += 1;
#endif

#if 0//( DEBUG_MULTI_TASK_TOTAL_TIME )
    // Check MultiTask freq
    U32 u32MTExecDelay = msAPI_Timer_DiffTime_2(s_MultiTask_u32LastEndTime, s_MT_u32StartTime);
    if( u32MTExecDelay >= 20 )
    {
        if( MApp_IsSrcHasSignal(MAIN_WINDOW) )
        {
            printf("\nu32MTExecDelay=%u,%u at %u\n", u32MTExecDelay, s_MultiTask_u32Counter, s_MT_u32StartTime);
        }
    }
#endif

#if(ENABLE_BOOTTIME)
    #define PT_Multi_SetBeginTime()     u32TimeBegin = msAPI_Timer_GetTime0()
    #define PT_Multi_PrintfTime(x)      u32TimeEnd = msAPI_Timer_DiffTimeFromNow(u32TimeBegin); \
                                        if(u32TimeEnd >= 20)                                    \
                                        {                                                       \
                                            printf("    [Multi]");                              \
                                            printf(x, u32TimeEnd);                              \
                                            u32TimeBegin = msAPI_Timer_GetTime0();              \
                                        }

    U32 u32TimeBegin                    = 0x00;
    U32 u32TimeEnd                      = 0x00;
#else
    #define PT_Multi_SetBeginTime()
    #define PT_Multi_PrintfTime(x)
#endif

    CHECK_MIU_PROTECT_LOG_AND_CLEAR();

    MT_CHECK_POINT_INIT();

    MT_CHECK_POINT();

#if ENABLE_ATSC
  #if ENABLE_TTSTEST_FROM_USB
    if(bIsAutoTestTTS)
    {
        MApp_ZUI_ACT_AutoCycleTTSTest();
    }
  #endif
#endif

#if (ENABLE_SECURITY_R2)
// HDCP2.2 handler
// 1. get command from DDC
// 2. talk with SecurityR2(SPU)
// 3. ack to player(HDMI_TX)
// 4. check SPU_HK_DUMMY1 reigser is counting to know SPU is running(check every one second)
    #if (!HDCP22_ALL_R2_TASK_ENABLE)
    msAPI_SecurityR2_Handler();
    #endif
#endif

    MT_CHECK_POINT();

#if ENABLE_PVR
    if (IsDTVInUse())
    {
    #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
         // To speed up power on time, two cases to avoid connect USB because it waste time.
         // First case, show up video ok, then you can connect USB by check flag gbBootTimeFinish.
         // Second case, if no signal, the gbBootTimeFinish flag will not true, so wait 10 secs.
        if( (gbBootTimeFinish) || (msAPI_Timer_DiffTimeFromNow(gU32BootTime)>10000))
    #else
        if( MsOS_GetSystemTime() > 12000 ) // After power on 12sec
    #endif
        {
            //PRINT_CURRENT_LINE();
            //printf("%u %u\n", gbBootTimeFinish, msAPI_Timer_DiffTimeFromNow(gU32BootTime) );
            //msAPI_MSDCtrl_CheckDevices_Ex();
            msAPI_MSDCtrl_CheckDevices();
        }
    }
#endif

    MT_CHECK_POINT();

#if (CHAKRA3_AUTO_TEST)
    MApp_AT_Task();
#endif

    PT_Multi_SetBeginTime();
#if (ENABLE_BOOTTIME)
    static BOOLEAN bMutltTaskFirst = FALSE;
#endif

#if AUTOBOOT
    static U32 autoboot_count = 0;
    static U32 autoboot_timer;
    if (autoboot_count == 0)
    {
        autoboot_timer = msAPI_Timer_GetTime0();
        printf("CL %d\n", AUTOBOOTCL);
        autoboot_count++;
    }

    if(autoboot_count == 1 && (msAPI_Timer_DiffTimeFromNow(autoboot_timer)/1000) > 120)
    {
        printf("system survive\n");
        autoboot_count++;
    }
#endif

#if (ENABLE_BOOTTIME)
    if (bMutltTaskFirst == FALSE)
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
        printf("[TIME] MApp_MultiTasks = %ld\n", gU32TmpTime);
        printf("[TIME] gU32CompressTotalStepTime = %ld\n", gU32CompressTotalStepTime);

        bMutltTaskFirst = TRUE;
    }
#endif

    MT_CHECK_POINT();

#if MHEG5_ENABLE
  #if ENABLE_AUTOTEST
    if (g_bAutobuildDebug && msAPI_MHEG5_IsRunning())
    {
        MDrv_Mheg5_Debug();
    }
  #endif
#endif
    PT_Multi_PrintfTime("#if MHEG5_ENABLE-- %ld\n");

    MT_CHECK_POINT();

#if (ENABLE_MSTV_UART_DEBUG)
    while( 1 ) // stop main loop for debug
    {
        if( msAPI_UART_DecodeCommand() )
        {
        #if (!CHANNEL_SCAN_AUTO_TEST)
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif
        #endif

            continue;
        }

        break;
    }
#endif
    PT_Multi_PrintfTime("#if (ENABLE_MSTV_UART_DEBUG)-- %ld\n");


    msAPI_Timer_ResetWDT();
    PT_Multi_PrintfTime("msAPI_Timer_ResetWDT()-- %ld\n");

    MT_CHECK_POINT();

#if 1//( DEBUG_XC_SYS_SYNC_STATUS )
    MApi_XC_Sys_Task();
#endif

    MT_CHECK_POINT();

#if (ENABLE_EWS)

    MApp_EWS_Handler();

#endif

#if (NEW_DEMOD_SCAN)
    msAPI_Qam_No_Channel_Detect();
#endif

    MApp_ProcessUserInput();
    //<<gchen @ 20180321 //MP333
    
	//check dc det 
	if(msAPI_Timer_DiffTimeFromNow(gU32BatCheckStartTime) >= 500)
	{
		gU32BatCheckStartTime = msAPI_Timer_GetTime0();
		
		if(DC_get_level())
		{
			//this is bat mode
			Detect_BatAD();

			//after bat low hint 5 mins show PowerOff Flag and Mute And Optical Off
			if(gU8BatLowHaveShowFlag)
			{
				gU32BatLowDiffTime = msAPI_Timer_DiffTimeFromNow(gU32BatLowStartTime);
				if(gU32BatLowDiffTime >= 300000)
				{
					if(gU8BatLowPowerOffType == 0)
					{

						gU32PowerOffStartTime = msAPI_Timer_GetTime0();
						MApp_UiMenu_TempDetWin_Show();
						gU8BatLowPowerOffType = 1;
							
					}
					else if(gU8BatLowPowerOffType == 1)
					{
						if(msAPI_Timer_DiffTimeFromNow(gU32PowerOffStartTime) > 5000)
						{
							MApp_UiMenu_TempDetWin_Hide();
							MUTE_On();
							msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, 0, 0);
							dpp2600_config_blank(FALSE);
							gU8BatLowPowerOffType = 2;
						}
					}
				}
			}
		}
		else
		{
			//this is dc mode
			if(gU8BatLowPowerOffType == 2)
			{
				dpp2600_config_blank(TRUE);
				msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
				MUTE_Off();	
			}
			else if(gU8BatLowPowerOffType == 1)
			{
				MApp_UiMenu_TempDetWin_Hide();
			}
			//set led
			BAT_LED_G_OFF();
			BAT_LED_R_OFF();
			gU8BatType = 0;
			gU8BatLowHaveShowFlag = 0;
			gU16BatLowCount = 0;
			gU8BatLowPowerOffType = 0;
		}
		
		//check bat show window
		//if gU8BatLowShowingFlag is ture hide it
		if(gU8BatLowShowingFlag == 1)
		{
			gU32BatLowDiffTime = msAPI_Timer_DiffTimeFromNow(gU32BatLowStartTime);
			if(gU32BatLowDiffTime >= 3000)
			{
				MApp_UiMenu_BatLowWin_Hide();
				gU8BatLowShowingFlag = 0;
			}
		}
	}
	
	//check sw det
	if(PowerOff_get_level())
	{
		//if sw det then power down
		
	}
	else
	{
		printf(" PowerOff_get_level false 2\n");
		msAPI_Power_PowerDown_EXEC();
		printf(" PowerOff_get_level false 3\n");
	}
	
	
	//>>gchen @ 20180321 //MP333
    MT_CHECK_POINT();

#if 0//nine-lattice sample code
    #include "MApp_NineLattice.h"
    if (u8KeyCode == KEY_MTS)
    {
        MApp_NineLattice_Set(STATE_NL_SWITCH);
        u8KeyCode = KEY_NULL;
    }
    else if (u8KeyCode == KEY_AUDIO)
    {
        MApp_NineLattice_Set(STATE_NL_INIT);
        u8KeyCode = KEY_NULL;
    }
    else if (u8KeyCode == KEY_EXIT)
    {
        MApp_NineLattice_Set(STATE_NL_EXIT);
        //u8KeyCode = KEY_NULL;
    }

    MApp_NineLattice();
#endif

#if 0
    if (u8KeyCode == KEY_1)
    {
        if(MApp_PixelID_IsEnabled() == FALSE)
        {
            printf("pixel ID init and begin\n");
            MApp_PixelID_Set(STATE_PIXELID_INIT);
            u8KeyCode = KEY_NULL;
        }
        else
        {
            printf("pixel id is already inited and drawn\n");
        }
    }
    else if (u8KeyCode == KEY_2)
    {
        printf("pixel is exit\n");
        MApp_PixelID_Set(STATE_PIXELID_EXIT);
        u8KeyCode = KEY_NULL;
    }

    MApp_PixelID();
#endif


  #if 0
    msAPI_Scaler_FPLL_FSM(MAIN_WINDOW);
    MT_TIME();
  #endif

    MT_CHECK_POINT();

#if (ENABLE_TEST_PATTERN)
    if(msAPI_TestPattern_Get_Status()==FALSE)
#endif
    {
        _MApp_Video_Handler(g_bRealTimeMonitorOnly);
    }

    MT_CHECK_POINT();

#if ENABLE_TCON
    if ( (g_PNL_TypeSel == TCON_PNL_WXGA_IPS_ALPHA_AH080A016G_Hisense)
       ||(g_PNL_TypeSel == TCON_PNL_WXGA_BOE_HV320WXC)
       )
    {
        if (gSystemTimeCount_TCON >= 28)
        {
            U8 u8SubBank;
            u8SubBank = MDrv_ReadByte(0x103000);
            if(u8SubBank != 0x00)
            {
                MDrv_WriteByte(0x103000, 0x00);
            }

            if ( MDrv_ReadByte(0x103072) & 0x80)
            {
                MDrv_WriteByteMask(0x103072, 0, BIT7);
                printf("[0] \n");
            }
            else
            {
                MDrv_WriteByteMask(0x103072, BIT7, BIT7);
                printf("[1] \n");
            }

            if(u8SubBank != 0x00)
            {
                MDrv_WriteByte(0x103000, u8SubBank);
            }

            gSystemTimeCount_TCON = 0;
        }
    }
#endif

    MT_CHECK_POINT();

#if (LD_ENABLE)
    MApi_LD_Main();
    MT_CHECK_POINT();
#endif

    MApp_Audio_Task(g_bRealTimeMonitorOnly);

    MT_CHECK_POINT();

    if (g_bRealTimeMonitorOnly == FALSE)
    {
      #if (SWCHECKSUM_SWITCH)
        msAPI_MIU_CCS();
      #endif
    }

    MT_CHECK_POINT();

    if (IsDTVInUse())
    {
        msAPI_AUD_MPEG_Monitor();
    }

    MT_CHECK_POINT();

  #if ENABLE_OFFLINE_SIGNAL_DETECTION
    MApp_AISMonitor();
  #endif

    MT_CHECK_POINT();

#if (ATSC_CC == DTV_CC)
    MApp_FontLoadMonitor();
    //benny merge from chakra2 for preview don't flash in 20160525!
    CC_RenderFuns.SoftBlinkEngine();//for CC preview window blink.
    CC_SourceFuns.CheckVCHIPTimeOut();//for vchip rating time out
    //CC_SourceFuns.ResetXDSInfo(); //for XDS info time out//canceled for mantis 1187931: Channel name and program title is not shown under ATV channel.
#endif

    // SH@
#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#if (BRAZIL_CC )
    if(IS_SBTVD_APP)
#endif
    {
        if(IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            MApp_FontLoadMonitor();

            MT_CHECK_POINT();

            if (MApp_VD_IsSyncLock())
            {
#if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
                MApp_VChip_MonitorVChip();
#endif
                /* monitor VBI data*/
                if(enCCFontStatus == CC_FONT_LOAD)
                {
                    // edit by jany
                    //msAPI_VBI_MonitorVBIData((EN_EIA608_SRV_TYPE)(DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode&0x0F)); //analog
                    CC_SourceFuns.MonitorVBIData((EN_EIA608_SRV_TYPE)DB_CC_SETTING.enATVCaptionType);

                    CC_SourceFuns.MonitorVBIData( (EN_EIA608_SRV_TYPE)(DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode&0x0F) ); //analog
                }
            }
#if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
            else
            {
                if(MApp_VChip_GetCurVChipBlockStatus())
                {
                    MApp_VChip_Init();  //  For no signal After rating Blocking.
                }
            }
#endif
        }
    }
#endif

    MT_CHECK_POINT();

  #if ENABLE_DVB
    MApp_AudioMuteMonitor();
  #endif

    MT_CHECK_POINT();
    if (g_bRealTimeMonitorOnly == FALSE)
    {
      #if ENABLE_DDCCI
        msAPI_DDC2BI_CommandHandler();
      #endif

        MT_CHECK_POINT();

    #if( ENABLE_HDMI_HPD_TASK )
        if( MApi_XC_HPD_Is_Task_Working() )
        {
            MApi_XC_HPD_Task();
        }
    #endif

        MT_CHECK_POINT();

        //CEC
      #if ENABLE_CEC
        MApp_CEC_Handler();
      #endif

        MT_CHECK_POINT();

      #if (EEPROM_DB_STORAGE != EEPROM_SAVE_ALL)
        MApp_DB_QuickDatabaseMonitor();
      #endif

        MT_CHECK_POINT();

        MApp_ScreenSaverHandler();

        MT_CHECK_POINT();

       //For Sleep Timer
        if (MApp_TopStateMachine_GetTopState()!= STATE_TOP_STANDBY)
        {
            MApp_Sleep_Monitor();
        }

    #if ( ENABLE_NO_OPERATE_AUTO_SLEEP )
        MApp_NoOperateAutoSleep_Task();
    #endif
    #if ( ENABLE_CI_PLUS_V1_4 )
        MApp_CI_PowerDown_Task();
    #endif  //ENABLE_CI_PLUS_V1_4
        MT_CHECK_POINT();

        MApp_Time_Tasks();
        MT_CHECK_POINT();

      #if ENABLE_TTX
        if (MApp_TTX_IsTeletextOn() == TRUE)
        {
            MApp_TTX_ClockMode_Monitor();
            MT_CHECK_POINT();
        }
      #endif

  #if ENABLE_CI
     #if (ENABLE_PIP)
        if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
         ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
     #else
        if ( IsDTVInUse() ) // IsDTVInUse() already DVBS
     #endif
        {
            MApp_MultiTasks_CI();
            MT_CHECK_POINT();
        }
  #endif


      #ifdef ENABLE_5VANTENNA
        Antenna5VMonitor();
        MT_CHECK_POINT();
      #endif

      #if (ENABLE_DTV_EPG)
        MApp_EpgTimer_ManualTimerMonitor();
        MT_CHECK_POINT();
      #endif  //#if (ENABLE_DTV_EPG)
    }

    MT_CHECK_POINT();

  #if ENABLE_TTX_ACI
    MApp_TTX_ProcessACI();
  #endif

    MT_CHECK_POINT();

  #if ENABLE_DMP
    if (IsStorageInUse())
    {
        //printf("Media Player TASK\n");
        MApp_MPlayer_Task();
        MT_CHECK_POINT();
    }
   #if ENABLE_USB_DEVICE_LIST
    else
    {
        _MApp_Storage_Monitor();
        MT_CHECK_POINT();
    }
   #endif
  #endif

    MT_CHECK_POINT();

#if (ENABLE_DIGITAL_MEDIA_API)
    MApp_DigitalMedia_Task();
    MT_CHECK_POINT();
#endif

  #if 0//ENABLE_DREC
    _DREC_Task();
  #endif

  #if ENABLE_DTV_CHCEK_USB_DELAY_2S
    MApp_DTV_USB_CheckMonitor();
  #endif

    MT_CHECK_POINT();

#if ENABLE_PVR
{
 #define DEBUG_PVR_USE_TIME  0
 #if(DEBUG_PVR_USE_TIME )
    U32 u32PVR_T1 = MsOS_GetSystemTime();
    U32 u32PVR_T2;
 #endif

    MApp_UiPvr_UIMonitor();
 #if(DEBUG_PVR_USE_TIME )
    u32PVR_T2 = MsOS_GetSystemTime();
    if( msAPI_Timer_DiffTime_2(u32PVR_T1, u32PVR_T2) > 30)
    {
        printf("t1=%u, t2=%u\n", u32PVR_T1, u32PVR_T2);
    }
 #endif

  #ifdef PVR_8051
    MApp_UiTimeShift_UIMonitor();
  #endif
}
#endif

    MT_CHECK_POINT();

  #if(ENABLE_MIPS_MBOX_DBGOUT)
    MIPS_MBOX_DBGOUT();
  #endif

    MT_CHECK_POINT();

  #if (ENABLE_PIP)
    if(IsPIPSupported() == FALSE)
    {
        _MApp_PIP_SubWinMonitor();
    }
  #endif

    MT_CHECK_POINT();

  #ifdef CUS_HISENSE
    if (msAPI_ACE_MWEStatus())
    {
        msAPI_ACE_MWEHandle();
    }
  #endif

    MT_CHECK_POINT();

  //for monitor clock control of digital IP (U3 only now)
  #if (ENABLE_DIP_MONITOR)
    MApp_PWS_monitor();
  #endif

    MT_CHECK_POINT();


#if (ENABLE_TEST_PATTERN)
    if(msAPI_TestPattern_Get_Status()==FALSE)
#endif
    {
    #if (ENABLE_NEW_AUTO_NR)
        if(MApp_IsSrcHasSignal(MAIN_WINDOW) && (ST_VIDEO.eNRMode.eNR != MS_NR_OFF) &&(IsATVInUse()))
        {
            msAPI_DNR_Handler();
        }
    #endif

    #if ENABLE_ATV_AUDIOCHECK_IN_OTHER_SRC
        if (!(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
            ||IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            )
            {
                Mapi_ATV_AudioProcessor();
            }
    #endif
    }

    MT_CHECK_POINT();

#if(ENABLE_MPLAYER_VIDEO_CAPTURE)
    if(MApp_MPlayer_IsCapturingVideo())
    {
        MApp_MPlayer_CaptureVideoTask();
    }
    MT_CHECK_POINT();
#endif
#if(ENABLE_MPLAYER_AUDIO_CAPTURE)
    if(MApp_MPlayer_IsCapturingAudio())
    {
        MApp_MPlayer_CaptureAudioTask();
    }
#endif

    MT_CHECK_POINT();

#if( ENABLE_UART_MSG_TO_USB )
    if(g_stFactorySetting.stFacMiscSetting.eFactoryUSBLog == EN_FACTORY_USB_LOG_ON)
    {
        msDebug_UartToUSB_Task();
    }
#endif

    MT_CHECK_POINT();

#if( ENABLE_SCRIPT_EXECUTE)
    if(g_stFactorySetting.stFacMiscSetting.eFactoryExecuteScript== EN_FACTORY_EXECUTE_SCRIPT_ON)
    {
        msUS_ExecuteScript_Task();
    }
#endif

    MT_CHECK_POINT();

    msAPI_MIU_Task();

    MT_CHECK_POINT();

#if (ENABLE_TEST_PATTERN)
    if(msAPI_TestPattern_Get_Status()==FALSE)
#endif
    {
        MApp_Vif_Handler();
    }

    MT_CHECK_POINT();

#if ENABLE_KEY_LOGGER
    MApp_KeyLogger_Action_Task();
#endif

    MT_CHECK_POINT();

#if (INPUT_HDMI_VIDEO_COUNT > 0)
    if( IsHDMIInUse() )
    {
        MApi_XC_HDMI_Task();

    #if ENABLE_EDID_SWITCH
        MApi_XC_HDMI_EDID_Monitor();
    #endif
        //MDrv_HDMI_StablePolling(); // 1. enable/disable HDMI2.0 power  2. Check TMDS over 3.4 GMHz to change another mode
    }
#endif

    MT_CHECK_POINT();

#if( ENABLE_ATSC )
    #if ENABLE_OAD
        if(MApp_TopStateMachine_GetTopState() == STATE_TOP_OAD)
        {
            MApp_OAD_Monitor();
            MApp_OAD_Download() ;
          #if OAD_TEST
            MApp_OAD_AppTest();
          #endif
        }
        MT_CHECK_POINT();

        if(IsDTVInUse()&& MApp_OAD_IsUserSelectOn())
        {
            MApp_OAD_Monitor();
            MT_CHECK_POINT();
            MApp_OAD_Download();
        }
    #endif
    MT_CHECK_POINT();
    if( IsAtscInUse() || IsATVInUse() || (IsAVInUse()) )
    {
        MApp_MultiTasks_ATSC();
    }
    MT_CHECK_POINT();
#endif

#if( ENABLE_DTV )
    MApp_VDEC_Task();
    MT_CHECK_POINT();
#endif

#if (INPUT_SCART_VIDEO_COUNT > 0)
    if( !IsStorageInUse() )
    {
        MApp_InputSource_ScartIOMonitor();
        MT_CHECK_POINT();
    }
#endif

#if(NO_SIGNAL_AUTO_SHUTDOWN)
    MApp_NoSignalAutoSleep_Task();
    MT_CHECK_POINT();
#endif


#if (ENABLE_STACK_CHECK)
    if( MDrv_StackChk_CheckFlag() )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: Stack is overflow!\n");
    }
#endif

#if(ENABLE_CHECK_MEMORY_CHANGE)
    if( FALSE == msDebug_CheckMemChg_Check(__LINE__) )
    {
        PRINT_CURRENT_LINE();
    }
#endif

#if( ENABLE_DEBUG_SHOW_SYS_INFO )
    MApp_Debug_ShowInfo_Task();
#endif

    MT_CHECK_POINT();

#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
    if ((g_AudioOnly == AUDIO_ONLY_ON) && (!fEnableAudioOnlyFunc))
    {
        if ((msAPI_Timer_DiffTimeFromNow(u32MonitorAudioOnlyTimer) > AUDIO_ONLY_TIMER))
        {
            u32MonitorAudioOnlyTimer = msAPI_Timer_GetTime0();
            MApp_UiMenuFunc_EnterAudioOnlyMode();
        }
    }
#endif

#if(ENABLE_KEY_TO_SPEECH)
    MApp_KTS_Task();
    MT_CHECK_POINT();
#endif

#if( DEBUG_MULTI_TASK_TOTAL_TIME )
    {
        U32 u32TaskEndTime = MsOS_GetSystemTime();
        U32 u32UseTime = msAPI_Timer_DiffTime_2(s_MT_u32StartTime, u32TaskEndTime);
        U16 u16StdTime = 20;


        if( IsStorageInUse() )
        {
        #if ENABLE_MPLAYER_MOVIE
            if( MApp_MPlayer_IsMoviePlaying() )
            {
                u16StdTime = 50;
            }
        #endif
        }
        else if( IsDTVInUse() ) // DTV
        {
            //printf("[IsDTVInUse]");
        #if( CHIP_FAMILY_NASA == CHIP_FAMILY_TYPE )
            u16StdTime = 30;
        #endif
        #if( CHIP_FAMILY_EDEN == CHIP_FAMILY_TYPE )
            u16StdTime = 40;
        #endif
        #if( CHIP_FAMILY_WHISKY == CHIP_FAMILY_TYPE )
            u16StdTime = 40;
        #endif

        #if( ( CHIP_FAMILY_MARLON == CHIP_FAMILY_TYPE )\
          ||( CHIP_FAMILY_MILAN == CHIP_FAMILY_TYPE )   \
          ||( CHIP_FAMILY_MAZDA == CHIP_FAMILY_TYPE )   \
          )

            u16StdTime = 40;
          #if(ENABLE_PVR)
            if( MApp_PVR_Is_InRecording() )
            {
                u16StdTime = 400; // When recording
            }
          #endif
        #endif

            // Auto Scan
        }
        else if( IsATVInUse() ) // ATV
        {
        #if( CHIP_FAMILY_WHISKY == CHIP_FAMILY_TYPE )
            u16StdTime = 30;
        #endif

        #if(ENABLE_ATSC)
            // In this condition, system will set tuner usually~
            if( MApp_GetSignalLockStatus() == FE_NOT_LOCK )
            {
                u16StdTime = 80;
            }
        #endif

            //printf("[IsATVInUse]");
            if( gbTVAutoScanChannelEnable )
            {
                //printf("[Scan]");
                u16StdTime = 300;
            }
        }

      #if (ENABLE_TIME_LOG)
        if ( u32UseTime > u16StdTime )
        {
            printf(" MultiTask %u use %u at %u!\n", s_MultiTask_u32Counter, u32UseTime, u32TaskEndTime );
        }
      #endif
    }

    //s_MultiTask_u32LastEndTime = MsOS_GetSystemTime();
#endif

    CHECK_MIU_PROTECT_LOG_AND_CLEAR();
}

void EnableAntenna5VMonitor(BOOLEAN bAntenna5VMonitorOnOff)
{
    m_dwAntenna5VMonitorTimer =   msAPI_Timer_GetTime0();
    m_bAntenna5VMonitorEnable = bAntenna5VMonitorOnOff;
}

#ifdef ENABLE_5VANTENNA
static void Antenna5VMonitor(void)
{
    if (FALSE == m_bAntenna5VMonitorEnable)
    {
        return;
    }

    if (msAPI_Timer_DiffTimeFromNow(m_dwAntenna5VMonitorTimer) > ANTENNA_5V_MONITOR_TIME)
    {
        m_dwAntenna5VMonitorTimer =   msAPI_Timer_GetTime0();

        if (ANT_5V_MNT_Read() == _LOW)
        {
            EnableAntenna5VMonitor(FALSE);
            stGenSetting.g_SysSetting.f5VAntennaPower = EN_5V_AntennaPower_Off;
            ANT_5V_CTL_Off();
        }
    }
}
#endif
// 070523_SK 5V Antenna Monitor
void AdjustAntenna5VMonitor(EN_MENU_5V_AntennaPower en5VAntennaOnOff)
{
    if (en5VAntennaOnOff == EN_5V_AntennaPower_On)
    {
        EnableAntenna5VMonitor(FALSE);
        ANT_5V_CTL_On();
    }
    else
    {
        EnableAntenna5VMonitor(TRUE);
        ANT_5V_CTL_Off();
    }
}

/********************************************************************************/
void MApp_PreProcessUserInput(void)
{

  #if 0//(ENABLE_DREC)
    if (u8KeyCode == KEY_0)
    {
        _DREC_KeyCount=1;
    }
    else if(u8KeyCode == KEY_RIGHT)
    {
        if (_DREC_KeyCount == 1)
        {
            if (_DREC_Status == 0)
            {
                if (_DREC_Initial())
                {
                    _DREC_Status=1;
                    _DREC_BufferCurrentPos=DREC_RECORDER_BUFFER_ADR;
                    _DREC_RecordedBytes=0;
                    _DREC_DiskTotalSectors=msAPI_FCtrl_GetTotalSectors(0);
                    _DREC_Flag=DREC_FLAG_TICK*1;
                    printf("DREC started!!\n");
                }
                else
                {
                    _DREC_Status=0;

                    MApi_DMX_Stop(_DREC_FID);
                    MApi_DMX_Close(_DREC_FID);
                    msAPI_FSEnv_UnRegister(_DREC_EnvironmentID);
                    _DREC_EnvironmentID=0xFF;
                    MApp_Dmx_EnableTableMonitor();
                    printf("DREC initial failed!!\n");
                }
            }
            else
            {
               printf("DREC RECORDING!!\n");
            }
        }

        _DREC_KeyCount=0;

    }
    else if (u8KeyCode==KEY_LEFT)
    {
        if (_DREC_KeyCount==1)
        {
            if (_DREC_Status==1)
            {
                _DREC_Stop();
                _DREC_Status=0;
            }
            printf("DREC STOPPED!!\n");
        }
        _DREC_KeyCount=0;
    }
    else if (u8KeyCode!=KEY_NULL)
    {
        _DREC_KeyCount=0;
    }
  #endif

/*
  #if (ENABLE_BULK_FILE_SYSTEM)
    if (u8KeyCode==KEY_0)
    {
        _SpecialKeyCount=1;
    }
    else if (u8KeyCode==KEY_DOWN)
    {
        if (_SpecialKeyCount==1)
        {
            U8 _diskDriveIndex;
            U8 _deviceIndex;
            BOOLEAN flag=FALSE;
            _SpecialKeyCount=0;

            _diskDriveIndex=msAPI_BKFS_GetDriveIndex();
            _deviceIndex=msAPI_BKFS_GetDeviceIndex();

            if (_diskDriveIndex==INVALID_DRIVE_INDEX)
            {
                __ASSERT(0);
            }
            else if(_deviceIndex==INVALID_DEVICE_INDEX)
            {
                __ASSERT(0);
            }
            else
            {
                if (!msAPI_FCtrl_IsDriveMounted(_diskDriveIndex))
                {
                    msAPI_MSDCtrl_CheckDevices();
                    if (msAPI_MSDCtrl_GetDeviceStatus(_deviceIndex)==MSD_STATUS_INSERTED)
                    {
                        if (msAPI_FCtrl_ActiveDevice(_deviceIndex))
                        {
                            flag=TRUE;
                        }
                    }
                }
                else
                {
                    flag=TRUE;
                }
            }

            if (TRUE == flag)
            {
                U8 envId;
                flag  = FALSE;
                envId = msAPI_FSEnv_Register(_diskDriveIndex);
                if (envId != INVALID_FS_ENVIRONMENT_INDEX)
                {
                    printf("\n[BulkFileSystem]##Start Preparing, environmentID=%bu, DiskDriveIndex=%bu, DeviceIndex=%bu\n",envId,_diskDriveIndex,_deviceIndex);
                    printf("    Formatting...\n");
                    MDrv_Sys_DisableWatchDog();
                    if (!msAPI_BKFS_Format(_diskDriveIndex))
                    {
                        __ASSERT(0);
                    }

                    msAPI_FSEnv_UnRegister(envId);
                    msAPI_MSDCtrl_ResetDevice(_deviceIndex);

                    printf("    Format Finished\n");
                    msAPI_MSDCtrl_CheckDevices();

                    if (!msAPI_FCtrl_ActiveDevice(_deviceIndex))
                    {
                        __ASSERT(0);
                    }

                    envId = msAPI_FSEnv_Register(_diskDriveIndex);

                    if (!msAPI_FCtrl_DirectoryChangeToRoot(envId))
                    {
                        __ASSERT(0);
                    }

                    if (!msAPI_FCtrl_EntryFirst(envId))
                    {
                        __ASSERT(0);
                    }
                    printf("    Creating Bulks...\n");
                    if (!msAPI_BKFS_CreateBulks(envId))
                    {
                        __ASSERT(0);
                    }
                    printf("    Create Finished...\n");
                    printf("[BulkFileSystem]##Finish Preparing\n");
                    MDrv_Sys_EnableWatchDog();
                    msAPI_FSEnv_UnRegister(envId);
                }
                else
                {
                    __ASSERT(0);
                }
            }
        }
    }
    else if (u8KeyCode!=KEY_NULL)
    {
        _SpecialKeyCount=0;
    }
  #else
    UNUSED(_SpecialKeyCount);
  #endif
*/

    //*** Process Hot key ***********************
    switch(u8KeyCode)
    {
#if 0
    	 case KEY_TEMP_DET:
	        if ((MApp_TopStateMachine_GetTopState() != STATE_TOP_ATV_SCAN)
              	#if ENABLE_DTV
                	&& (MApp_TopStateMachine_GetTopState() != STATE_TOP_DTV_SCAN)
              	#endif
              	#if ENABLE_DMP
                	&& (MApp_TopStateMachine_GetTopState() != STATE_TOP_DMP)
              	#endif
               )
	        {
	              u8KeyCode = KEY_NULL;
	              MApp_UiMenu_TempDetWin_Show();
	        }
		 break;
#endif

    	 case KEY_BAT_LOW:
	        if ((MApp_TopStateMachine_GetTopState() != STATE_TOP_ATV_SCAN)
              	#if ENABLE_DTV
                	&& (MApp_TopStateMachine_GetTopState() != STATE_TOP_DTV_SCAN)
              	#endif
              	#if ENABLE_DMP
                	&& (MApp_TopStateMachine_GetTopState() != STATE_TOP_DMP)
              	#endif
               )
	        {
	              u8KeyCode = KEY_NULL;
	              MApp_UiMenu_BatLowWin_Show();
	        }
		 break;
        /*case KEY_RED://anvi
            MApp_UiMenu_ARCDiscWin_Show();
            break;//*/
        case KEY_MUTE:
            if ((MApp_TopStateMachine_GetTopState() != STATE_TOP_ATV_SCAN)
              #if ENABLE_DVB //ENABLE_DTV
                && (MApp_TopStateMachine_GetTopState() != STATE_TOP_DTV_SCAN)
              #endif
              #if ENABLE_DMP
                && (MApp_TopStateMachine_GetTopState() != STATE_TOP_DMP)
              #endif
              #if ENABLE_OAD
                  && (MApp_TopStateMachine_GetTopState() != STATE_TOP_OAD)
              #endif
               )
            {
                MApp_KeyProc_Mute();
              #if (NO_SIGNAL_AUTO_SHUTDOWN )
                if((MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
                    && (enIndicateTimerSource  == TS_TYPE_SLEEPTIMER_NOSIGNAL)
                    && (MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_QUERY_IS_POWER_OFF_COUNTDOWN_MSG_BOX)))
                {
                    u8KeyCode = KEY_EXIT;
                }
              #endif
            }

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                printf("91_KEY_MUTE\n");
            }
          #endif
            break;
        case KEY_VOLUME_PLUS: //disable MUTE win before show volume bar
        	//printf("KEY_VOLUME_PLUS 11111\n");
			//MApp_UiMenu_BatLowWin_Show();
			//LEDPWR_ENABLE();
			//break;
        case KEY_VOLUME_MINUS:
			//MApp_UiMenu_BatLowWin_Hide();
			//LEDPWR_DISABLE();
			//printf("KEY_VOLUME_MINUS 11111\n");
          #if ENABLE_DMP
            if (MApp_TopStateMachine_GetTopState() != STATE_TOP_DMP)
          #endif
            {
                MApp_UiMenu_ARCDeviceStatusWin_Hide();
                MApp_UiMenu_MuteWin_Hide();
            }
            break;
	
		case KEY_KEYSTONE_NEG:    //xzm @20171228 keystone
        case KEY_KEYSTONE_POS:
		#if ENABLE_DMP
            if (MApp_TopStateMachine_GetTopState() != STATE_TOP_DMP && 
			MApp_TopStateMachine_GetTopState() != STATE_TOP_INPUTSOURCE)
        #endif
        {
            MApp_ZUI_ACT_StartupOSD(E_OSD_KEYSTONE_ANGLE);
            MApp_TV_ProcessKeystoneAngleKey(u8KeyCode);
            MApp_AnalogInputs_ResetTimer(MAIN_WINDOW);
			u8KeyCode = KEY_NULL;
        }
        break;
        default:
            break;
    }
}

#if ENABLE_VDEC_INFO_MONITOR
extern MS_U32 u32decodemonitortimer;
extern MS_BOOL gbsyncreach;
extern void MApi_VDEC_DbgDumpStatus(void);
#endif

#if (ENABLE_SW_CH_FREEZE_SCREEN)
extern BOOLEAN bVideoStandardChanged;
#endif



void MApp_ScreenMuteMonitor(SCALER_WIN eWindow)
{
  #if (ENABLE_SWITCH_CHANNEL_TIME)
    #define PT_MApp_SMM_SetBeginTime()      u32TimeBegin = msAPI_Timer_GetTime0()
    #define PT_MApp_SMM_PrintfTime(x)       u32TimeEnd = msAPI_Timer_DiffTimeFromNow(u32TimeBegin); \
                                            if(u32TimeEnd > 5)                                     \
                                            {                                                       \
                                                printf("[ScreenMuteMonitor]");                      \
                                                printf(x, u32TimeEnd);                              \
                                            }                                                       \
                                            u32TimeBegin = msAPI_Timer_GetTime0()

    U32 u32TimeBegin = 0x00;
    U32 u32TimeEnd   = 0x00;
  #else
    #define PT_MApp_SMM_SetBeginTime()
    #define PT_MApp_SMM_PrintfTime(x)
  #endif
    static U32 s_u32ScreenMuteTaskLastTime = 0;

  #if 0//ENABLE_DTV
    MEMBER_SERVICETYPE bServiceType;
    U16 u16CurPosition;
    BOOL bStillPic = FALSE;
  #endif


    if( msAPI_Timer_DiffTime_2(s_u32ScreenMuteTaskLastTime, MsOS_GetSystemTime()) < 5 )
        return;

    s_u32ScreenMuteTaskLastTime = MsOS_GetSystemTime();


    PT_MApp_SMM_SetBeginTime();

    // Check scaler fpll status
    MApi_XC_Sys_CheckFpllStatusTask();



  #if ENABLE_DTV
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        PT_MApp_SMM_SetBeginTime();
        if (MApp_TV_IsProgramRunning() == FALSE)
        {
            PT_MApp_SMM_PrintfTime("MApp_TV_IsProgramRunning() -- %ld\n");
            if ((msAPI_Scaler_GetScreenMute(eWindow)&E_SCREEN_MUTE_TEMPORARY) == 0)
            {
                PT_MApp_SMM_PrintfTime("msAPI_Scaler_GetScreenMute(eWindow)&E_SCREEN_MUTE_TEMPORARY) -- %ld\n");
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 1000, eWindow);
                PT_MApp_SMM_PrintfTime("msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 1000, eWindow) -- %ld\n");
            }

            if (msAPI_AUD_IsAudioMuted() == FALSE)
            {
                PT_MApp_SMM_PrintfTime("msAPI_AUD_IsAudioMuted() -- %ld\n");
              #if (ENABLE_PIP)
                if ((MApp_Get_PIPMode() == EN_PIP_MODE_OFF && eWindow == MAIN_WINDOW) || UI_IS_AUDIO_SOURCE_IN(eWindow))
              #endif
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    PT_MApp_SMM_PrintfTime("msAPI_AUD_AdjustAudioFactor() -- %ld\n");
                }
            }
            return;
        }
    }
  #endif

    PT_MApp_SMM_SetBeginTime();

  #if (ENABLE_SW_CH_FREEZE_SCREEN)
    if(msAPI_Scaler_GetScreenMute(eWindow) & E_SCREEN_MUTE_CHANNEL)
    {
        if(bVideoStandardChanged)
        {
            msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            msAPI_Scaler_SetFreezeScreen(DISABLE, 0, MAIN_WINDOW);
        }
        else if(msAPI_Timer_GetDownTimer0() == 0)
        {
            msAPI_Scaler_SetFreezeScreen(DISABLE, 0, MAIN_WINDOW);
        }
    }
    else
  #endif
    if (MApi_XC_IsBlackVideoEnable(eWindow))
    {
        PT_MApp_SMM_PrintfTime("MApi_XC_IsBlackVideoEnable() -- %ld\n");


        if (((msAPI_Scaler_GetScreenMute(eWindow) ^ E_SCREEN_MUTE_TEMPORARY) == 0)
        #if ENABLE_PVR
            || (MApp_PVR_StateMachineGet() == E_PVR_STATE_PLAYBACK)
            || (MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT)
        #endif
           )
        {
            PT_MApp_SMM_PrintfTime("msAPI_Scaler_GetScreenMute(eWindow) -- %ld\n");

            //printf(" CD=%u ", msAPI_Timer_GetDownTimer0());

            if (msAPI_Timer_GetDownTimer0() == 0) //unit = ms
            {
                SwitchChannelTimePrintf("[SwitchChannelTime](msAPI_Timer_GetDownTimer0() == 0) --- %ld\n");

            // Use new method to control screen mute,
            // Add new mute client = E_SCREEN_MUTE_BY_VDEC
            #if 0
                if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow)))
                {
                  #if MHEG5_ENABLE
                    if (g_MHEG5Video.bIFrame)
                    {
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, eWindow);
                        msAPI_VE_SetBlackScreen(DISABLE);
                    }
                    else
                  #endif
                    if (enMVDVideoStatus == MVD_GOOD_VIDEO)
                    {
                        SwitchChannelTimePrintf("[SwitchChannelTime](enMVDVideoStatus == MVD_GOOD_VIDEO) --- %ld\n");
                      #if 0
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, NULL);
                        g_bRealTimeMonitorOnly = FALSE;
                      #else
                        SwitchChannelTimePrintf("[SwitchChannelTime]IS_HVD_CODEC(g_eCodecType) --- %ld\n");
                        if (IS_HVD_CODEC(g_eCodecType))   //FIXME !!
                        {
                            PT_MApp_SMM_SetBeginTime();
                         #if ENABLE_DTV
                            bServiceType = msAPI_CM_GetCurrentServiceType();
                            u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);
                            bStillPic = msAPI_CM_GetProgramAttribute(bServiceType,u16CurPosition, E_ATTRIBUTE_IS_STILL_PICTURE);
                            //if(MApi_VDEC_IsFrameRdy() == E_VDEC_OK)

                            if (((MApi_VDEC_IsReachSync() == E_VDEC_OK)&&(MApi_VDEC_GetFrameCnt() > 50)) ||
                               (( MApi_VDEC_IsAVSyncOn() != E_VDEC_OK) &&  (MApi_VDEC_IsFrameRdy() == E_VDEC_OK)) ||
                               ((((bStillPic == TRUE)&& (MApi_VDEC_GetFrameCnt() > 3))||(MApi_VDEC_GetFrameCnt() > 50)) &&  (MApi_VDEC_IsStartSync()  != E_VDEC_OK) && ( MApi_VDEC_IsReachSync() != E_VDEC_OK) && (MApi_VDEC_IsFrameRdy() == E_VDEC_OK)) ||
                               ((MApi_VDEC_IsFrameRdy() == E_VDEC_OK) && (msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer) > SCREEN_MUTE_TIME_OUT)))
                         #else
                            if ( (MApi_VDEC_IsReachSync() == E_VDEC_OK) ||
                               ( ( MApi_VDEC_IsAVSyncOn() != E_VDEC_OK) &&  (MApi_VDEC_IsFrameRdy() == E_VDEC_OK)) ||
                               ( (MApi_VDEC_GetFrameCnt() > 200) && (MApi_VDEC_IsStartSync()  != E_VDEC_OK) && ( MApi_VDEC_IsReachSync() != E_VDEC_OK  ) && (MApi_VDEC_IsFrameRdy() == E_VDEC_OK)))
                         #endif
                            {
                                PT_MApp_SMM_PrintfTime("msAPI_Scaler_GetScreenMute(eWindow) -- %ld\n");
                              #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
                              #if (ENABLE_BOOTTIME==DISABLE)
                                if (g_bAutobuildDebug == TRUE)
                              #endif
                                {
                                    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                                    printf("[TIME] HVD sync ok = %ld\n", gU32TmpTime);
                                }
                              #endif

                                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, eWindow);
                                msAPI_VE_SetBlackScreen(DISABLE);
                                PT_MApp_SMM_PrintfTime("msAPI_VE_SetBlackScreen(DISABLE); -- %ld\n");
                              #if (ENABLE_PIP)
                                if ((MApp_Get_PIPMode() == EN_PIP_MODE_OFF && eWindow == MAIN_WINDOW) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                              #endif
                                {
                                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                    PT_MApp_SMM_PrintfTime("msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE...); -- %ld\n");
                                }
                                g_bRealTimeMonitorOnly = FALSE;
                            }
                        }
                        else
                        {
                            SwitchChannelTimePrintf("[SwitchChannelTime]VVVVV_VDEC_IsIFrameFound() --- %ld\n");
                            if (MApi_VDEC_IsIFrameFound() == E_VDEC_OK)
                            {
                                SwitchChannelTimePrintf("[SwitchChannelTime]MApi_VDEC_IsIFrameFound() --- %ld\n");
                                if (msAPI_VID_IsSyncEnable() == 1)
                                {
                                    if (MApi_VDEC_IsReachSync() == E_VDEC_OK)
                                    {
                                        SwitchChannelTimePrintf("[SwitchChannelTime]VDEC 1st frame ready: --- %ld\n");
                                      #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
                                      #if (ENABLE_BOOTTIME==DISABLE)
                                        if (g_bAutobuildDebug == TRUE)
                                      #endif
                                        {
                                            gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                                            printf("[TIME] VID sync ok= %ld\n", gU32TmpTime);
                                        }
                                      #endif

                                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, eWindow);
                                        PT_MApp_SMM_PrintfTime("[E_VDEC_OK]msAPI_Scaler_SetScreenMute(DISABLE); -- %ld\n");
                                        msAPI_VE_SetBlackScreen(DISABLE);
                                        PT_MApp_SMM_PrintfTime("[E_VDEC_OK]msAPI_VE_SetBlackScreen(DISABLE); -- %ld\n");
                                      #if (ENABLE_PIP)
                                        if ((MApp_Get_PIPMode() == EN_PIP_MODE_OFF && eWindow == MAIN_WINDOW) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                                      #endif
                                        {
                                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                            PT_MApp_SMM_PrintfTime("[E_VDEC_OK]msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,...); -- %ld\n");
                                          }
                                        #if 0//(ENABLE_POST_INIT)
                                        MApp_StartPostInit();
                                        #endif
                                        g_bRealTimeMonitorOnly = FALSE;
                                        //printf("sync done\n");
                                    }
                                    else
                                    {
                                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, DELAY_FOR_REMOVE_SCREENMUTE ,eWindow);

                                        if (msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer) > SCREEN_MUTE_TIME_OUT)
                                        {
                                            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, eWindow);
                                            msAPI_VE_SetBlackScreen(DISABLE);
                                            #if 0//(ENABLE_POST_INIT)
                                            MApp_StartPostInit();
                                            #endif
                                          #if (ENABLE_PIP)
                                            if((MApp_Get_PIPMode() == EN_PIP_MODE_OFF && eWindow == MAIN_WINDOW) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                                          #endif
                                            {
                                                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                             }
                                            g_bRealTimeMonitorOnly = FALSE;
                                            //printf("sync timeout\n");
                                        }
                                    }
                                }
                                else
                                {  // for video-only stream, we don't wait sync complete
                                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, eWindow);
                                    msAPI_VE_SetBlackScreen(DISABLE);

                                  #if (ENABLE_PIP)
                                    if((MApp_Get_PIPMode() == EN_PIP_MODE_OFF && eWindow == MAIN_WINDOW) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                                  #endif
                                    {
                                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                    }
                                    g_bRealTimeMonitorOnly = FALSE;
                                }
                            }
                            else// For no I frame bitstream, we cannot decode correct
                            {   // frames just after changing channel. Therefore, we
                                // need to hide decoded frames for a while.
                                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, DELAY_FOR_REMOVE_SCREENMUTE, eWindow);

                                if (msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer) > SCREEN_MUTE_TIME_OUT )
                                {
                                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, eWindow);
                                    msAPI_VE_SetBlackScreen(DISABLE);

                                  #if (ENABLE_PIP)
                                    if((MApp_Get_PIPMode() == EN_PIP_MODE_OFF && eWindow == MAIN_WINDOW) || UI_IS_AUDIO_SOURCE_IN(eWindow) )
                                  #endif
                                    {
                                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                    }
                                    g_bRealTimeMonitorOnly = FALSE;
                                }
                            }
                        }
                      #endif
                    }
                #if ENABLE_PVR
                    else
                    {
                        if(MApi_AUDIO_IsMadLock())
                        {
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        }
                    }
                #endif
                }
                else
           #endif
                {
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, eWindow);
                    msAPI_VE_SetBlackScreen(DISABLE);

                  #if (ENABLE_PIP)
                    if ((MApp_Get_PIPMode() == EN_PIP_MODE_OFF && eWindow == MAIN_WINDOW) || UI_IS_AUDIO_SOURCE_IN(eWindow))
                  #endif
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }

                    g_bRealTimeMonitorOnly = FALSE;
                }
            }
        }
#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
        else if((g_AudioOnly == AUDIO_ONLY_ON)\
         &&((msAPI_Scaler_GetScreenMute(eWindow)^(E_SCREEN_MUTE_BY_AUDIO_ONLY|E_SCREEN_MUTE_TEMPORARY))==0) \
        )
        {
            if (msAPI_Timer_GetDownTimer0()==0)
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                g_bRealTimeMonitorOnly = FALSE;
            }
        }
#endif
    }
}
/********************************************************************************/

#if ENABLE_MVDMONITOR
/********************************************************************************/
/// MVD Monitor
///
/// if MVD status checking fails 10 times, reinitialize mvd.
/********************************************************************************/
void MVD_Monitor(void)
{
    if ((MDrv_ReadByte(MVD_STATUS) & 0x02 ) != 0x02)
    {
        u8MVDMonitor_FailCount++;
        #if 1
        printf("\r\nMVD fail count %d\n", u8MVDMonitor_FailCount);
        #endif
        if (u8MVDMonitor_FailCount >= 10)
        {
            //printf("Run msAPI_VID_MVDInit() : u8MVDMonitor_FailCount==10 \n");
            u8MVDMonitor_FailCount = 0;
        #if  (ATSC_CC == DTV_CC)
            msAPI_CC_Reset();
        #endif
            //MAPI_VID_Init(E_VDEC_CODEC_TYPE_MPEG2,FALSE);
            msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);

            //msAPI_VID_MVDCommand(MSAPI_VID_PLAY);
            msAPI_VID_Command(MSAPI_VID_PLAY);
        }
    }
    else
    {
        u8MVDMonitor_FailCount = 0;
    }
}
#endif

#if(ENABLE_DVB)
static void _MApp_Service_Check( void )
{
    MS_SI_CUR_SERVICE_INFO stSIServiceInfo;
    E_SERVICE_CHANGE eChangeType;

    if (MApp_SI_Is_Service_Change(&stSIServiceInfo,&eChangeType)
#if ENABLE_SDT_OTHER_MONITOR
        ||(g_SDT_u32CheckMovServieTimer && MApp_SI_IsSdtOtherCome())
#endif
#ifdef ENABLE_DELETE_PROGRAM_CONTROL
        || msAPI_CM_GetRemoveProgram(&eChangeType)
#endif
        )
    {
        BOOLEAN bNeedRestartChnChange = FALSE;
        //BOOLEAN bGotSameAudio=FALSE;
        BOOLEAN bNeedUpdateAudInfo = FALSE, bTrueFalse;
        MEMBER_SERVICETYPE bServiceType;
        WORD wCurrentPosition, wCurServiceID;
        WORD wVideo_PID = 0, wPCR_PID = 0;
        U8 i, j, AudioNum;
        BYTE bSelectedAudStream = 0xFF;
        AUD_INFO aAudioStreamInfo;
        AUD_INFO NewstAudioStreamInfo,OldstAudioStreamInfo;
        U8 u8PreLRAudioMode = g_u8LRAudioMode;
        BOOLEAN bGetSameAudioPidAsDB;

        if (E_SERVICE_REMOVED == eChangeType)
        {
            if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
            #if ENABLE_SDT_OTHER_MONITOR
                MEMBER_SERVICETYPE bServiceTypeTmp = E_SERVICETYPE_DTV;
                WORD wSIDTmp = 0;
                WORD wLCNTmp = 0;

                MApp_SDT_Get_UserService(&bServiceTypeTmp, &wSIDTmp, &wLCNTmp);

                MApp_Dmx_Disable_Reset_Filter();
                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);

                //g_SDT_eUserServiceType=bServiceTypeTmp;
                //g_SDT_u16UserSID= wSIDTmp;
                //g_SDT_u16UserLCN= wLCNTmp;
                MApp_SDT_Set_UserService(bServiceTypeTmp, wSIDTmp, wLCNTmp);

                gu8VerChange = TRUE;

            #else
            #if(ENABLE_S2)
                if (Dvbs2_Default_Scan == 1)
                {
                    Dvbs2_Default_Scan = 0;
                }
                else
            #endif
                {
                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                gu8VerChange = TRUE;
                }
            #endif

            }

          #if (ENABLE_PIP)
            if (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                {
                    MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                    MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                }
            }
          #endif

        }
      #if ENABLE_SDT_OTHER_MONITOR
        else if ((E_SERVICE_MOVE == eChangeType)||(g_SDT_u32CheckMovServieTimer && MApp_SI_IsSdtOtherCome()))
        {
            MOVE_SERVICE_IDS stMoveSrv;
            MEMBER_SERVICETYPE eGotServiceType;
            WORD u16GotPosition;
            if(g_SDT_u32CheckMovServieTimer && msAPI_SI_Timer_DiffTime(msAPI_SI_Timer_GetTime(), g_SDT_u32CheckMovServieTimer) > CHANGE_TO_MOVE_SERVICE_TIMEOUT)
            {
                MApp_SI_ResetSdtOtherComeFlag();
                g_SDT_u32CheckMovServieTimer = 0;
            }
            else
            {
                MApp_SI_Get_MoveServiceIDS(&stMoveSrv);
                if (TRUE == msAPI_CM_GetServiceTypeAndPositionWithIDs(stMoveSrv.wTSID, stMoveSrv.wONID, stMoveSrv.wSID, 1, &eGotServiceType, &u16GotPosition, TRUE))
                {
                    if(MApp_ChannelChange_ChangeSpeciChannel(stMoveSrv.wSID, stMoveSrv.wONID, stMoveSrv.wTSID, TYPE_CHANNEL_CHANGE_SER_ID, TRUE, TRUE))
                    {
                    //printf("ChannelChange_ChangeSpeciChannel \n");
                    }
                }
                else if(g_SDT_u32CheckMovServieTimer == 0 && MApp_SI_IsSdtOtherCome()==FALSE)
                {
                    g_SDT_u32CheckMovServieTimer = msAPI_SI_Timer_GetTime();
                }
                if(MApp_SI_IsSdtOtherCome()==TRUE)
                {
                    MApp_SI_ResetSdtOtherComeFlag();
                    if(g_SDT_u32CheckMovServieTimer)
                        g_SDT_u32CheckMovServieTimer = 0;
                }
            }
        }
      #endif
        else
        {
            MS_CUR_SERVICE_INFO stServiceInfo;
            BOOLEAN bSaveAudio=MApp_SI_Is_Save_Audio();//20090806
            stServiceInfo.eVideoType = msAPI_SI_ToCM_Video_Type(stSIServiceInfo.eVideoType);
            stServiceInfo.u8bStillPic = stSIServiceInfo.u8bStillPic;
            stServiceInfo.u8fMHEG5 = stSIServiceInfo.u8fMHEG5;
            stServiceInfo.u8IsCAExist = stSIServiceInfo.u8IsCAExist;
            stServiceInfo.wPmtPid = stSIServiceInfo.wPmtPid;
            stServiceInfo.wVideo_PID = stSIServiceInfo.wVideo_PID;
            stServiceInfo.wPCRPid = stSIServiceInfo.wPCRPid;
            stServiceInfo.u8AudStreamNum = stSIServiceInfo.u8AudStreamNum;

            if(stServiceInfo.u8fMHEG5)
            {
                g_bMheg5Existed = TRUE;
            }
            else
            {
                g_bMheg5Existed = FALSE;
            }


            int maxAudio = MAX_AUD_LANG_NUM > SI_MAX_AUD_LANG_NUM ? SI_MAX_AUD_LANG_NUM : MAX_AUD_LANG_NUM;
        #if 1 // Use new API
            msAPI_SI_Copy_SI_AudInfo_To_CM_AudInfo(stSIServiceInfo.stAudInfo, stServiceInfo.stAudInfo, maxAudio);

        #else

            int maxISO = MAX_AUD_ISOLANG_NUM > SI_MAX_AUD_ISOLANG_NUM ? SI_MAX_AUD_ISOLANG_NUM : MAX_AUD_ISOLANG_NUM;

            for (i = 0; i < maxAudio; i++)
            {
                //stServiceInfo.stAudInfo[i].wAudType=msAPI_SI_ToCM_Audio_Type(stSIServiceInfo.stAudInfo[i].wAudType);
                stServiceInfo.stAudInfo[i].eSIAudType = (SI_AUDIOSTREAM_TYPE)stSIServiceInfo.stAudInfo[i].wAudType;
                stServiceInfo.stAudInfo[i].wAudPID=stSIServiceInfo.stAudInfo[i].wAudPID;

                //stServiceInfo.stAudInfo[i].u8ProfileAndLevel=stSIServiceInfo.stAudInfo[i].u8ProfileAndLevel;
                stServiceInfo.stAudInfo[i].eProfileAndLevel = msAPI_SI_ToCM_ProfileAndLevel(stSIServiceInfo.stAudInfo[i].u8ProfileAndLevel);

                //stServiceInfo.stAudInfo[i].u8Component_AAC_Type=stSIServiceInfo.stAudInfo[i].u8Component_AAC_Type;

                for (j = 0; j < maxISO; j++)
                {
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLangIndex = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLangIndex;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo = msAPI_SI_ToCM_Audio_Mode(stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo);
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bAudType = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bAudType;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bIsValid = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bIsValid;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD;
                    stServiceInfo.stAudInfo[i].aISOLangInfo[j].bReserved = stSIServiceInfo.stAudInfo[i].aISOLangInfo[j].bReserved;
                }
            }
        #endif

            bServiceType = msAPI_CM_GetCurrentServiceType();
            wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
            wVideo_PID = msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition);
            wCurServiceID = msAPI_CM_GetService_ID(bServiceType, wCurrentPosition);

            //Note: Don't need to take care about TTX and Subtitle.
            //      These modules will do the updat by themselves in data gathering stage.
            if (stServiceInfo.u8IsCAExist != msAPI_CM_GetProgramAttribute(bServiceType, wCurrentPosition, E_ATTRIBUTE_IS_SCRAMBLED))
            {
                msAPI_CM_ScrambleProgram(bServiceType,wCurrentPosition,stServiceInfo.u8IsCAExist);
                //bNeedRestartChnChange = TRUE; //**-- Italy CI Certificate --**//
                //bReturn  = TRUE;
            }
            if (stServiceInfo.u8bStillPic != msAPI_CM_GetProgramAttribute(bServiceType, wCurrentPosition, E_ATTRIBUTE_IS_STILL_PICTURE))
            {
                bTrueFalse = stServiceInfo.u8bStillPic;
                // To do. msAPI_CM_UpdateProgram() does not support this yet.
                //if(E_RESULT_SUCCESS == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, &bTrueFalse, E_ATTRIBUTE_IS_STILL_PICTURE))
                //{
                //}
            }
            if (msAPI_CM_GetProgramAttribute(bServiceType, wCurrentPosition, E_ATTRIBUTE_IS_SERVICE_ID_ONLY) == TRUE)
            {
                msAPI_CM_ServiceIDOnlyProgram(bServiceType, wCurrentPosition, FALSE);
            }

            if (stServiceInfo.eVideoType != (U8)msAPI_CM_GetProgramVideoType(bServiceType, wCurrentPosition))
            {
                msAPI_CM_SetProgramVideoType(bServiceType,wCurrentPosition,stServiceInfo.eVideoType);
                bNeedRestartChnChange = TRUE;
            }
            if (stServiceInfo.wPmtPid != msAPI_CM_GetPmtPID(bServiceType,wCurrentPosition))
            {
                //printf("Service (%u) Change Pmt PID, old(%u):new(%u)\n",wCurServiceID,msAPI_CM_GetPmtPID(bServiceType,wCurrentPosition),stServiceInfo.wPmtPid);
                if(TRUE == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)&stServiceInfo.wPmtPid, E_DATA_PMT_PID))
                {
                  #if ENABLE_FileIn_PMTMonitor
                    _RecordUpdateAllPIDs = TRUE;
                  #endif
                    //bNeedRestartChnChange = TRUE;
                }
            }
            if (stServiceInfo.wVideo_PID != msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition))
            {
                //printf("Service (%u) Change Vid PID, old(%u):new(%u)\n",wCurServiceID,msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition),stServiceInfo.wVideo_PID);
                if(TRUE == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)&stServiceInfo.wVideo_PID, E_DATA_VIDEO_PID))
                {
                  #if ENABLE_FileIn_PMTMonitor
                    _RecordUpdateAllPIDs = TRUE;
                  #endif
                    bNeedRestartChnChange = TRUE;
                }
            }
            if (stServiceInfo.wPCRPid != msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition))
            {
                //printf("Service (%u) Change PCR PID, old(%u):new(%u)\n",wCurServiceID,msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition),stServiceInfo.wPCRPid);
                if(TRUE == msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)&stServiceInfo.wPCRPid, E_DATA_PCR_PID))
                {
                  #if ENABLE_FileIn_PMTMonitor
                    _RecordUpdateAllPIDs = TRUE;
                  #endif
                }
            }
            msAPI_DMX_Pid(*MApp_Dmx_GetFid(EN_PCR_FID),&wPCR_PID,FALSE);
            if (stServiceInfo.wPCRPid != wPCR_PID)
            {
                DMX_FILTER_STATUS eDMXFLTSTA;
                msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_PCR_FID) );
                eDMXFLTSTA = msAPI_DMX_StartFilter( stServiceInfo.wPCRPid, MSAPI_DMX_FILTER_TYPE_PCR, MApp_Dmx_GetFid(EN_PCR_FID) );
            }

            /* Check Audio*/
            /* Get current audio count */
            AudioNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);
            /* Get all the audio infor */
            if (AudioNum != stServiceInfo.u8AudStreamNum)
            {
                //printf("PMT content change: audio number change, old(%bu), new(%bu)\n",AudioNum,pPmtInfo->u8AudStreamNum);
                bNeedUpdateAudInfo = TRUE;
            }
            else
            {
                /* Get current selected audio index */
                bSelectedAudStream = g_u8AudLangSelected;//msAPI_CM_GetSelectedAudioStream(bServiceType, wCurrentPosition);
                for(i = 0; i< AudioNum; i++)
                {
                    bGetSameAudioPidAsDB = FALSE;
                    /* Get all audio information */
                    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);

                    /* check audio info change or not */
                    for(j = 0; j < stServiceInfo.u8AudStreamNum; j++)
                    {
                        if (stServiceInfo.stAudInfo[j].wAudPID == aAudioStreamInfo.wAudPID)
                        {
                            bGetSameAudioPidAsDB = TRUE;
                            //if (stServiceInfo.stAudInfo[j].wAudType == aAudioStreamInfo.wAudType)
                            if (stServiceInfo.stAudInfo[j].eSIAudType == aAudioStreamInfo.eSIAudType)
                            {
                                if (!memcmp(stServiceInfo.stAudInfo[j].aISOLangInfo, aAudioStreamInfo.aISOLangInfo,sizeof(LANG_ISO639)*MAX_AUD_ISOLANG_NUM))
                                {
                                    break;
                                }
                                else
                                {
                                    bNeedUpdateAudInfo = TRUE;
                                    break;
                                }
                            }
                            else
                            {
                                if (bSelectedAudStream == i)
                                {
                                    //bNeedRestartChnChange = TRUE;
                                }
                                bNeedUpdateAudInfo = TRUE;
                                break;
                            }
                        }
                    }
                    if(bGetSameAudioPidAsDB == FALSE)
                    {
                        bNeedUpdateAudInfo = TRUE;
                        if(bSelectedAudStream == i)
                        {
                            //bNeedRestartChnChange = TRUE;
                            break;
                        }
                    }
                }
            }

            if (bNeedUpdateAudInfo == TRUE)
            {
                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &OldstAudioStreamInfo, g_u8AudLangSelected);
                msAPI_CM_EnableStoreDataToFlash(bSaveAudio);//20090806
                #if ENABLE_FileIn_PMTMonitor
                _RecordUpdateAllPIDs = TRUE;
                #endif
                if (TRUE != msAPI_CM_UpdateProgram(bServiceType, wCurrentPosition, (U8*)stServiceInfo.stAudInfo, E_DATA_AUDIO_STREAM_INFO))
                {
                    //printf("Update Aud info fail\n");
                }
                msAPI_CM_EnableStoreDataToFlash(TRUE);//20090806
                //NZ freview spec, got prefer language should change audio
                if ((bNeedRestartChnChange == FALSE) && (bSelectedAudStream!=0xFF)&& (stGenSetting.g_SoundSetting.enSoundAudioLan1 != OldstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex) /*&& (stGenSetting.g_SoundSetting.enSoundAudioLan2 != OldstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex)*/)
                {
                    U8 temp=g_u8AudLangSelected;
                #if (ENABLE_CI_PLUS)
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        MApp_ChannelChange_SearchDefaultOPAudioLang();
                    }
                    else
                    {
                        MApp_ChannelChange_SearchDefaultAudioLang();
                    }
                #else
                    MApp_ChannelChange_SearchDefaultAudioLang();
                #endif
                    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &NewstAudioStreamInfo, g_u8AudLangSelected);
                    if((stGenSetting.g_SoundSetting.enSoundAudioLan1 == NewstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex) || (stGenSetting.g_SoundSetting.enSoundAudioLan2 == NewstAudioStreamInfo.aISOLangInfo[0].bISOLangIndex))
                    {
                        bSelectedAudStream=0xFF;

                    }
                    else
                    {
                        g_u8AudLangSelected=temp;
                    }
                }

            #if(ENABLE_DVB_AUDIO_DESC)
                if(stGenSetting.g_SoundSetting.bEnableAD == TRUE)
                {
                #if ENABLE_CI_PLUS
                    if(TRUE == MApp_CI_IsOpMode())
                    {
                        MApp_Audio_OpSearchAdAudio();
                    }
                    else
                #endif
                    {
                        MApp_Audio_SearchAdAudio();
                    }

                    // if ad exist
                    if (g_u8AdAudSelected != 0xFF)
                    {
                        MApp_Audio_SetAdAudio(g_u8AdAudSelected);
                        //MApp_Audio_SetAudioLanguage(g_u8AdAudSelected);
                        MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);
                        MApp_Audio_AdjustADVolume(stGenSetting.g_SoundSetting.ADVolume);
                    }
                }
            #endif
            }

            if (bNeedRestartChnChange == TRUE)
            {
                //printf("need Restar Chn with stopDSMCC %bu\n",!_stSIInfo.stPmtMonInfo.u8fMHEG5);
                //printf("### change channel due to PMT content change>>\n");
                if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    BOOLEAN bCheckPW = FALSE;

                  #if ENABLE_SDT_OTHER_MONITOR
                    MEMBER_SERVICETYPE bServiceTypeTmp=E_SERVICETYPE_DTV;
                    WORD wSIDTmp=0;
                    WORD wLCNTmp=0;

                    MApp_SDT_Get_UserService(&bServiceTypeTmp, &wSIDTmp, &wLCNTmp);

                #if 0//MHEG5_ENABLE
                    BOOLEAN bIsCIMHEGRun = FALSE;
                    if (msAPI_IsCIMHEGRun() != E_MHEG_CI_OFF)
                    {
                        bIsCIMHEGRun = TRUE;
                    }
                #endif
                    MApp_Dmx_Disable_Reset_Filter();
                    MApp_Dmx_SetReset_EventInfo_status(FALSE);
                    MApp_ChannelChange_DisableChannel(FALSE,MAIN_WINDOW);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);

                    if( MApp_Get_ParentalBlock_state() /*_bParentalBlock*/)
                    {
                        MApp_ParentalControl_SetBlockStatus(TRUE);
                        if(bCheckPW)
                            MApp_Set_CheckParentalPWStatus(TRUE);
                    }

                    MApp_Dmx_SetReset_EventInfo_status(TRUE);

                    //g_SDT_eUserServiceType=bServiceTypeTmp;
                    //g_SDT_u16UserSID= wSIDTmp;
                    //g_SDT_u16UserLCN= wLCNTmp;
                    MApp_SDT_Set_UserService(bServiceTypeTmp, wSIDTmp, wLCNTmp);

                  #else
                    MApp_Dmx_SetReset_EventInfo_status(FALSE);
                    bCheckPW = MApp_Get_CheckParentalPWStatus();
                    MApp_ChannelChange_DisableChannel(FALSE,MAIN_WINDOW);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                    if( MApp_Get_ParentalBlock_state() /*_bParentalBlock*/)
                    {
                        MApp_ParentalControl_SetBlockStatus(TRUE);
                        if(bCheckPW)
                            MApp_Set_CheckParentalPWStatus(TRUE);
                    }
                    MApp_Dmx_SetReset_EventInfo_status(TRUE);
                  #endif

                #if 0//MHEG5_ENABLE
                    if(bIsCIMHEGRun == TRUE)
                    {
                        msAPI_MHEG5_SetCIMHEGRun(E_MHEG_CI_TRIGGER);
                        bIsCIMHEGRun = FALSE;
                    }
                #endif
                }
              #if (ENABLE_PIP)
                if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                    {
                        MApp_ChannelChange_DisableChannel(FALSE,SUB_WINDOW);
                        MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                    }
                }
              #endif
            }
            else if(bNeedUpdateAudInfo == TRUE)//check if need replay later
            {
            #if (ENABLE_CI_PLUS)
                if(TRUE == MApp_CI_IsOpMode())
                {
                    MApp_ChannelChange_SearchDefaultOPAudioLang();
                }
                else
                {
                    MApp_ChannelChange_SearchDefaultAudioLang();
                }
            #else
                MApp_ChannelChange_SearchDefaultAudioLang();
            #endif

            #if(ENABLE_DVB_AUDIO_DESC)
                if(g_u8AdAudSelected == 0xFF)
                {
                    MApp_ChannelChange_SearchBroadcastMixAudio();
                }
            #endif

                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &NewstAudioStreamInfo, g_u8AudLangSelected);

                if (OldstAudioStreamInfo.wAudPID != NewstAudioStreamInfo.wAudPID ||
                    u8PreLRAudioMode != g_u8LRAudioMode ||
                    //OldstAudioStreamInfo.wAudType != NewstAudioStreamInfo.wAudType
                    OldstAudioStreamInfo.eSIAudType != NewstAudioStreamInfo.eSIAudType
                    )
                {
                    MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
                }
            }
        }

    }
}

#endif

#if (ENABLE_DTV)
BOOLEAN MApp_GetAutoSystemTimeFlag(void)
{
    return _bAutoSystemTime;
}
#endif

#if ENABLE_DTV
#define DEBUG_VDEC_TASK(x)  //x

extern U32 g_u32PreVdecFrameCnt;

void MApp_VDEC_Task(void)
{
    static U32 s_u32VDECTaskLastTime = 0;

    if( msAPI_Timer_DiffTime_2(s_u32VDECTaskLastTime, MsOS_GetSystemTime()) < 10 )
        return;

    s_u32VDECTaskLastTime = MsOS_GetSystemTime();

    if( !IsDTVInUse() )
        return;

    BOOL bVDECIsOK = FALSE;
    BOOL bCurUseHVD = (IS_HVD_CODEC(g_eCodecType))? TRUE: FALSE;

    // If E_SCREEN_MUTE_BY_VDEC active
    if( msAPI_Scaler_GetScreenMute(MAIN_WINDOW)&E_SCREEN_MUTE_BY_VDEC )
    {
        DEBUG_VDEC_TASK(printf(" Check VDEC,"););

      #if MHEG5_ENABLE
        if (g_MHEG5Video.bIFrame)
        {
            bVDECIsOK = TRUE;
        }
        else
      #endif
        if (enMVDVideoStatus == MVD_GOOD_VIDEO)
        {
            if (bCurUseHVD) // HVD
            {

                U32 u32FrameCnt = MApi_VDEC_GetFrameCnt();
                U32 u32XC_FrameCnt = MApi_XC_IsCurrentFrameBufferLessMode() ? 0 : 2;
                DEBUG_VDEC_TASK(printf(" FrameCnt()=%u,", u32FrameCnt););


                BOOL bIsReachSync = (MApi_VDEC_IsReachSync() == E_VDEC_OK);
                BOOL bIsAVSyncOn = (MApi_VDEC_IsAVSyncOn() == E_VDEC_OK);
                BOOL bIsFrameRdy = (MApi_VDEC_IsFrameRdy() == E_VDEC_OK);

            #if(ENABLE_DVB)
                BOOL bIsStartSync = (MApi_VDEC_IsStartSync() == E_VDEC_OK);
                MEMBER_SERVICETYPE bServiceType = msAPI_CM_GetCurrentServiceType();
                U16 u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);
                BOOL bStillPic = msAPI_CM_GetProgramAttribute(bServiceType,u16CurPosition, E_ATTRIBUTE_IS_STILL_PICTURE);
            #endif

                if( (bIsReachSync && (u32FrameCnt >= g_u32PreVdecFrameCnt+u32XC_FrameCnt))
                  ||( !bIsAVSyncOn && bIsFrameRdy )
            #if(ENABLE_DVB)
                  ||((( bStillPic && (u32FrameCnt > 3))||(u32FrameCnt > 50)) && !bIsStartSync && !bIsReachSync && bIsFrameRdy )
            #endif
                  ||(bIsFrameRdy && (msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer) > VDEC_HVD_SCREEN_MUTE_TIME_OUT))
                  )
                {
                    DEBUG_VDEC_TASK(printf("\n.condi_1=%d;condi_2=%d;condi_3=%d\n",(bIsReachSync && (u32FrameCnt >= g_u32PreVdecFrameCnt+u32XC_FrameCnt)),
                                                ( !bIsAVSyncOn && bIsFrameRdy ),
                                                (bIsFrameRdy && (msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer) > VDEC_HVD_SCREEN_MUTE_TIME_OUT))));
                    bVDECIsOK = TRUE;
                }
                if(!bIsReachSync)
                {
                    g_u32PreVdecFrameCnt = u32FrameCnt;
                }
            }
            else // MPEG
            {
                //DEBUG_VDEC_TASK(printf(" IFrameFound()=%u,", MApi_VDEC_IsIFrameFound()););
                //DEBUG_VDEC_TASK(printf(" msAPI_VID_IsSyncEnable()=%u,", msAPI_VID_IsSyncEnable()););
                //DEBUG_VDEC_TASK(printf(" MApi_VDEC_IsReachSync()=%u\n", MApi_VDEC_IsReachSync()););
                //DEBUG_VDEC_TASK(printf(" FrameCnt()=%u,", MApi_VDEC_GetFrameCnt()););

                if (MApi_VDEC_IsIFrameFound() == E_VDEC_OK)
                {
                    if (msAPI_VID_IsSyncEnable() == 1)
                    {
                        if (MApi_VDEC_IsReachSync() == E_VDEC_OK)
                        {
                            bVDECIsOK = TRUE;
                        }
                        else
                        {
                            DEBUG_VDEC_TASK(printf("Wait ReachSync, %u,%u\n", g_u32VDecPicCountTimer, msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer)););
                            if (msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer) > VDEC_SCREEN_MUTE_TIME_OUT )
                            {
                                printf(" g_u32VDecPicCountTimer timeout - 1\n");
                                // Timeout
                                bVDECIsOK = TRUE;
                            }
                        }
                    }
                    else
                    {  // for video-only stream, we don't wait sync complete
                        bVDECIsOK = TRUE;
                    }
                }
                else// For no I frame bitstream, we cannot decode correct
                {   // frames just after changing channel. Therefore, we
                    // need to hide decoded frames for a while.
                    //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, DELAY_FOR_REMOVE_SCREENMUTE, eWindow);
                    DEBUG_VDEC_TASK(printf(" IFrameFound()=0\n"););

                    if (msAPI_Timer_DiffTimeFromNow(g_u32VDecPicCountTimer) > VDEC_SCREEN_MUTE_TIME_OUT )
                    {
                        bVDECIsOK = TRUE;
                        printf(" g_u32VDecPicCountTimer timeout -2\n");
                    }
                }
            }
        }
        else
        {
            DEBUG_VDEC_TASK(printf(" enMVDVideoStatus != MVD_GOOD_VIDEO\n" ););
        }

        if( bVDECIsOK )
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_VDEC, DISABLE, 0, MAIN_WINDOW);
        #if (ENABLE_CHCHANGETIME)
            printf("\n>>>[ChChangeTime][VDEC sync ok]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
        #endif
        #if(DEBUG_CHG_SRC_TIME)
            msDebug_PrintChgSrcTime("VDEC Sync ok" );
        #endif

        #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
          #if (ENABLE_BOOTTIME==DISABLE)
            if (g_bAutobuildDebug == TRUE)
          #endif
            {
                gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                printf("[TIME] VDEC(%u) sync ok at %u (%ld)\n", bCurUseHVD, MsOS_GetSystemTime(), gU32TmpTime);
            }
        #endif
        }
    }


  #if ENABLE_VDEC_INFO_MONITOR
    {
        MS_U32 curdecodecnt=0;
        MS_U32 decodemonitortimer=0;
        MS_U32 u32_H_STC=0;
        MS_U32 u32_L_STC=0;


        curdecodecnt = MApi_VDEC_GetFrameCnt();
        decodemonitortimer=MsOS_GetSystemTime();
        if(  decodemonitortimer  >=  (u32decodemonitortimer + 1500 )  || (MApi_VDEC_IsSeqChg() == E_VDEC_OK) ||
              ( (gbsyncreach == FALSE)  &&  (MApi_VDEC_IsReachSync()== E_VDEC_OK) )   )
        {

            MApi_DMX_Stc_Get(&u32_H_STC, &u32_L_STC);

            printf( "VPTS:%lu  STC:%lu (Seq:%lu I:%lu 1stF:%lu) AV(on:%lx Start:%lu Reach:%lu)(Dec:%lu Err:%lu Skip:%lu Drop:%lu) ES(R:%lx W:%lx)\n"  , MApi_VDEC_GetPTS(),(MS_U32)(u32_L_STC/90),
                (MS_U32)MApi_VDEC_IsSeqChg()  , (MS_U32)MApi_VDEC_IsIFrameFound() , (MS_U32)MApi_VDEC_IsFrameRdy()    ,
                (MS_U32)MApi_VDEC_IsAVSyncOn() ,   (MS_U32)MApi_VDEC_IsStartSync()     ,   (MS_U32)MApi_VDEC_IsReachSync() ,
                curdecodecnt , MApi_VDEC_GetErrCnt() , MApi_VDEC_GetSkipCnt() , MApi_VDEC_GetDropCnt() ,
                MApi_VDEC_GetESReadPtr()  ,  MApi_VDEC_GetESWritePtr() );
            //MApi_VDEC_DbgDumpStatus();
            u32decodemonitortimer=decodemonitortimer;
            if( MApi_VDEC_IsReachSync() )
            {
                gbsyncreach=TRUE;
            }
        }
    }
    //PT_MApp_SMM_PrintfTime("#if ENABLE_VDEC_INFO_MONITOR -- %ld\n");
  #endif

}
#endif


#undef MAPP_MULTITASKS_C

