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
/// file    msAPI_CEC.c
/// @author MStar Semiconductor Inc.
/// @brief  HDMI CEC API Interface
///////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include <string.h>
#include "stdio.h"

#if ENABLE_CEC

#define _MSAPICEC_C_

#include "drvGlobal.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_OSD.h"
#include "apiCEC.h"
#include "msAPI_CEC.h"
#include "msAPI_CEC_Customer.h"

#include "msIR.h"
#include "MApp_Key.h"
#include "apiPNL.h"
#include "Panel.h"
#include "MApp_GlobalVar.h"
#include "MApp_InputSource.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_exefunc.h"
#include "msAPI_Tuning.h"
#include "drvPM.h"
#include "MApp_Audio.h"
#include "MApp_ZUI_ACTglobal.h"
#include "msAPI_audio.h"
#if ENABLE_DMP
#include "mapp_mplayer.h"
#endif
#include "MApp_ChannelChange.h"
#include "MApp_TopStateMachine.h"
#include "msAPI_Timer.h"
#include "drvGPIO.h"

#include "MApp_GlobalFunction.h"

#include "MApp_ZUI_ACTcoexistWin.h"
#include "MApp_ZUI_ACTinputsource.h"

#include "ZUI_tables_h.inl"
#if ENABLE_PVR
#include "MApp_PVR.h"
#endif

#if ENABLE_DMP
#include "MApp_DMP_Main.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define CEC_PORT1   0x10    //HDMI 1
#define CEC_PORT2   0x20    //HDMI 2
#define CEC_PORT3   0x30    //HDMI 3
#define CEC_PORT4   0x40    //HDMI 4


#define CEC_DEBUG                           FALSE
#if CEC_DEBUG
    #define CEC_ERROR_DEBUG(str, x)         printf(str, x)
    #define CEC_DPUTSTR(str)                printf(str)
    #define CEC_DPRINTF(str, x)             printf(str, x)
    #define CEC_FEATURE(str, x)             printf(str, x)
    #define CEC_MSG(x)                      x
    #define CEC_POSTMSG_DEBUG(x)            x
    #define CEC_POSTMSG_ERROR_DEBUG(x)      x
    #define CEC_POLLING_MSG_DBG(x)          x
    #define CEC_STATE_INFO(x)               x
    #define CEC_ARC_INFO(x)                 x
    #define CEC_PR(x)                       x
#else
    #define CEC_ERROR_DEBUG(str, x)         //printf(str, x)
    #define CEC_DPUTSTR(str)                //printf(str)
    #define CEC_DPRINTF(str, x)             //printf(str, x)
    #define CEC_FEATURE(str, x)             //printf(str, x)
    #define CEC_MSG(x)                      //x
    #define CEC_POSTMSG_DEBUG(x)            //x
    #define CEC_POSTMSG_ERROR_DEBUG(x)      //x
    #define CEC_POLLING_MSG_DBG(x)          //x
    #define CEC_STATE_INFO(x)               //x
    #define CEC_ARC_INFO(x)                 //x
    #define CEC_PR(x)                       //x
#endif

    #define CEC_TX(x)                       x
    #define CEC_RX(x)                       x


// CEC function catalog
#define ONE_TOUCH_PLAY_SUPPORT                  1 // TV, CEC switches
#define ROUTING_CONTROL_SUPPORT                 1 // TV, CEC switches
#define STANDBY_COMMAND_SUPPORT                 1 // All
#define SYSTEM_INFORMATION_SUPPORT              1 // All
#define ONE_TOUCH_RECORD_SUPPORT                0 // Recording devices
#define TIMER_PROGRAMMER_SUPPORT                0 //
#define DECK_CONTROL_SUPPORT                    0
#define TUNER_CONTROL_SUPPORT                   0
#define VENDOR_SPECIFIC_SUPPORT                 1 // All
#define OSD_DISPLAY_SUPPORT                     0
#define DEVICE_OSD_NAME_TRANSFER_SUPPORT        1 //anvi cec
#define DEVICE_MENU_CONTROL_SUPPORT             1
#define REMOTE_CONTROL_PASSTHROUGH_SUPPORT      1
#define POWER_STATUS_SUPPORT                    1 // All except CEC switches
#define SYSTEM_AUDIO_CONTROL_SUPPORT            1
#define GENERAL_PROTOCAL_SUPPORT                1 // All
#define AUDIO_RETURN_CHANNEL_SUPPORT            1

//
//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------
//

static MS_U8 u8VendorID_MST[3] = {0x4D, 0x53, 0x54};

///Record the time of each interval timer type
U32 m_gCECStartTime[INTERVAL_TIMER_MAX];

//
MsCEC_DEVICELA enUserCtrlPressedLA = E_LA_TV;

//
//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
//

static BOOLEAN gCECInitDone = FALSE;

static CECMSGQUEUE  _stCecMsgQueue;

static MSAPI_CEC_INFO_LIST      _stMsApiCecInfoList;
static ST_CEC_STATE_INFO_LIST   _stCecStateInfoList;


#if DECK_CONTROL_SUPPORT
MsCEC_MSG_DC_DECK_STATUS_PARM gCECDeckStatus = (MsCEC_MSG_DC_DECK_STATUS_PARM) 0xFF;
#endif

BOOLEAN bDuringChannelChange = 0;

// TO DO.  are all of those variables necessary?
BOOLEAN gCECRecordEnable = FALSE;
BOOLEAN gCECUserControlEnable;
BOOLEAN gCECMenuControlEnable = FALSE;
BOOLEAN gCECGetMenuStatusMsg = FALSE;

static U8 u8CECAmpControlVolume = 0;
static BOOLEAN bSystemAudioMode = FALSE;

static BOOLEAN gIsCECAmpARCOn = FALSE;
static MS_U8 ARCAudioVolume = 0;
static BOOLEAN ARCAMPIsMute = FALSE;


//
//-------------------------------------------------------------------------------------------------
//  External Variables
//-------------------------------------------------------------------------------------------------
//

extern E_OSD_ID _eActiveOSD;

//
//-------------------------------------------------------------------------------------------------
//  external Functions
//-------------------------------------------------------------------------------------------------
//

extern void MsOS_DelayTask(U32 u32milisec);

extern BOOLEAN MApp_UiMenu_IsCountDownWinShow(void);

// drv layer in utopia
extern void MDrv_CEC_ConfigWakeupInfoVendorID(MS_U8* u8CecVendorID);
extern void MDrv_CEC_SetRetryCount(MS_U8 u8RetryCount);

//
//-------------------------------------------------------------------------------------------------
//  Local Functions prototype
//-------------------------------------------------------------------------------------------------
//

static void msCecDeviceListInitData(MS_U8 Idx);


//
//-------------------------------------------------------------------------------------------------
//  external Files
//-------------------------------------------------------------------------------------------------
//

#include "msAPI_CEC_base.c"
#include "msAPI_CEC_PostMsg.c"
#include "msAPI_CEC_Customer.c"


//
//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
//

void msCecShowDeviceMap(void)
{
#if CEC_DEBUG
    U8 i;

    printf("\n") ;
    printf(" ============================================================================= \n") ;
    printf("    LA  PA       VendorID   Ver       Type         Power         Name          \n") ;
    printf(" ============================================================================= \n") ;

//    printf("\n\33[0;31m") ;
    printf("\e[31;1;42m") ;
    for (i=(int)E_LA_RECORDER1; i<(int)E_LA_MAX; i++)
    {
        if ( msAPI_CEC_IsDeviceExist((MsCEC_DEVICELA)i) )
        {
            if (msAPI_CEC_GetActiveDevice() == (MsCEC_DEVICELA)i)
            {
                printf(" @") ;
            }
            else
            {
                printf("  ") ;
            }

            // Logical Address
            printf("  %X", i) ;

            // Physcial Address
            printf("   %X.%X.%X.%X",
                    (_stMsApiCecInfoList.u16PhysicalAddress[i]&0xF000) >> 12,
                    (_stMsApiCecInfoList.u16PhysicalAddress[i]&0x0F00) >> 8,
                    (_stMsApiCecInfoList.u16PhysicalAddress[i]&0x00F0) >> 4,
                    (_stMsApiCecInfoList.u16PhysicalAddress[i]&0x000F) ) ;

            // Vendor ID
            printf("  0x%02X%02X%02X ",
                            _stMsApiCecInfoList.u8CecVendorID[i][0],
                            _stMsApiCecInfoList.u8CecVendorID[i][1],
                            _stMsApiCecInfoList.u8CecVendorID[i][2]) ;

            // CEC Version
            printf(" (%3d)", _stMsApiCecInfoList.u8CECVersion[i]) ;
            switch (_stMsApiCecInfoList.u8CECVersion[i])
            {
                case CEC_VERSION_11:    printf("1.1 ");    break;
                case CEC_VERSION_12:    printf("1.2 ");    break;
                case CEC_VERSION_12a:   printf("1.2a");    break;
                case CEC_VERSION_13:    printf("1.3 ");    break;
                case CEC_VERSION_13a:   printf("1.3a");    break;
                case CEC_VERSION_14:    printf("1.4 ");    break;
                default:                printf(" -  ");    break;
            }


            // Device Type
            printf("  (%d)", _stMsApiCecInfoList.enDeviceType[i]) ;
            switch (_stMsApiCecInfoList.enDeviceType[i])
            {
                case E_DEVICE_TYPE_TV:                 printf("TV      ");   break;
                case E_DEVICE_TYPE_RECORDING_DEVICE:   printf("RECORDER");   break;
                case E_DEVICE_TYPE_RESERVED:           printf("DEVICE  ");   break;
                case E_DEVICE_TYPE_TUNER:              printf("TUNER   ");   break;
                case E_DEVICE_TYPE_PLAYBACK_DEVICE:    printf("PLAYER  ");   break;
                case E_DEVICE_TYPE_AUDIO_SYSTEM:       printf("AUDIO   ");   break;
                default:                               printf("   -    ");   break;
            }


            // Power Status
            printf("  (%d)", _stMsApiCecInfoList.enPowerStatus[i]) ;
            switch (_stMsApiCecInfoList.enPowerStatus[i])
            {
                case E_MSG_PWRSTA_ON:              printf("ON        ");   break;
                case E_MSG_PWRSTA_STANDBY:         printf("STANDBY   ");   break;
                case E_MSG_PWRSTA_STANDBY2ON:      printf("STANDBY2ON");   break;
                case E_MSG_PWRSTA_ON2STANDBY:      printf("ON2STANDBY");   break;
                case E_MSG_PWRSTA_UNKNOW:          printf("UNKNOW    ");   break;
                default:                           printf("   -      ");   break;
            }


            // OSD Name
            printf(" %s \n", _stMsApiCecInfoList.u8CecDeviceName[i]) ;
        }
    }
    printf("\33[m");
    printf(" =============================================================================== \n");
#endif
}

void msCecDbgRxCmd(ST_CEC_MSG stCecMsg)
{
    MS_U8 i;

    CEC_DPUTSTR("\n\033[41;4m ======= [CEC] =======\33[0m \n");

    CEC_DPRINTF(" header   = 0x%bx \n", stCecMsg.u8header);
    CEC_DPRINTF(" opcode   = 0x%bx ", stCecMsg.u8opcode);
//    CEC_DPRINTF("\e[31;1m %s \33[m \n", (char *)CEC_opCodeStr_Customer[stCecMsg.u8opcode]);
    CEC_DPRINTF(" %s \n", (char *)CEC_opCodeStr_Customer[stCecMsg.u8opcode]);

    for(i = 0; i<(stCecMsg.u8MsgLen-2); i++)
    {
        CEC_DPRINTF(" para%2d   =", i);
        CEC_DPRINTF(" 0x%bx \n", stCecMsg.u8Para[i]);
    }
    //printf(" enDevice    = 0x%bx \n", ((stCecMsg.u8header & 0xF0)>>4));
    //printf(" enDeviceDst = 0x%bx \n", (stCecMsg.u8header & 0x0F));
    CEC_DPUTSTR("\033[41;4m ===================== \33[0m \n");
}


static void msCecDeviceListInitData(MS_U8 Idx)
{
    CEC_MSG( printf("[CEC] DeviceListInitData(%d) \n", Idx) );

    _stMsApiCecInfoList.State[Idx] = E_STM_POLLING; //E_STM_EMPTY;

    _stMsApiCecInfoList.bCecDevicesExisted[Idx] = FALSE;

    _stMsApiCecInfoList.u16PhysicalAddress[Idx] = 0x0000;
    _stMsApiCecInfoList.u8PhysicalAddress[Idx][0] = 0x00;
    _stMsApiCecInfoList.u8PhysicalAddress[Idx][1] = 0x00;

    _stMsApiCecInfoList.u8CecVendorID[Idx][0] = 0x00;
    _stMsApiCecInfoList.u8CecVendorID[Idx][1] = 0x00;
    _stMsApiCecInfoList.u8CecVendorID[Idx][2] = 0x00;

    _stMsApiCecInfoList.u8CECVersion[Idx] = 0xFF;
    _stMsApiCecInfoList.enPowerStatus[Idx] = E_MSG_PWRSTA_UNKNOW;
    _stMsApiCecInfoList.enDeviceType[Idx] = E_DEVICE_TYPE_TV;
}


static void msCecInitCecStructure(void)
{
    MsCEC_DEVICELA _Idex = E_LA_TV;

    memset(&_stMsApiCecInfoList, 0, sizeof(MSAPI_CEC_INFO_LIST));

    CEC_MSG( printf("\033[30m\033[43m[CEC] InitCecStructure() \033[0m \n") );

    _stMsApiCecInfoList.fCecFirstPollingFinish = FALSE;
    _stMsApiCecInfoList.fCecPowerOnPollingFinish = FALSE;
    _stMsApiCecInfoList.PollingIdx = E_LA_RECORDER1;
    _stMsApiCecInfoList.State[E_LA_TV] = E_STM_NONE;

    _stMsApiCecInfoList.enActiveDeviceLA = E_LA_TV;
    _stMsApiCecInfoList.u8CecDeviceCount = 0;

    for (_Idex=E_LA_RECORDER1; _Idex<(E_LA_MAX+1); _Idex++)
    {
        msCecDeviceListInitData(_Idex);
    }

    msCecLoadDefaultDeviceName_All(stGenSetting.g_SysSetting.Language);

    /***********************
    If TV receives <Give Device Power Status> while it shifts to Power-on state,
    it shall be sent <Report Power Status> ["In transition Standby to On"] for directly address.
    ***********************/
    _stMsApiCecInfoList.enPowerStatus[E_LA_TV] = E_MSG_PWRSTA_STANDBY2ON;
}


static void msCecInitVariable(void)
{
    msCecInitCecStructure();

    memcpy(&_stMsApiCecInfoList.u8CecVendorID[E_LA_TV], &u8VendorID_MST, sizeof(u8VendorID_MST)/sizeof(MS_U8));
    MDrv_CEC_ConfigWakeupInfoVendorID(_stMsApiCecInfoList.u8CecVendorID[E_LA_TV]);

    _stMsApiCecInfoList.u8CECVersion[E_LA_TV] = HDMI_CEC_VERSION;

    gCECRecordEnable = FALSE;
    if (  (stGenSetting.stHDMISetting.g_bHdmiCecDeviceControl == ENABLE)
       || (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
       )
    {
        gCECUserControlEnable = TRUE;
    }
    else
    {
        gCECUserControlEnable = FALSE;
    }

    // default All Feature is On.
    memset(&stCecFeatureSupport, 1, sizeof(ST_CEC_Feature_Support));

    // reset all CEC state machine info
    memset(&_stCecStateInfoList, 0, sizeof(ST_CEC_STATE_INFO_LIST));


    gCECInitDone = TRUE;
}


//
//**************************************************************************
//

//**************************************************************************
//  [Function Name]:
//                   msCecIsByPassCommand()
//  [Description]
//                   Bypass CEC Cmd
//  [Arguments]:
//                   none
//  [Return]:
//                   none
//@20090212 by hansen.chen
//**************************************************************************
BOOLEAN msCecIsByPassCommand(void)
{
    if (  msAPI_Tuner_IsTuningProcessorBusy()
       || (MApp_ZUI_GetActiveOSD() == E_OSD_AUTO_TUNING)    //by pass atuo tunning tv
      #if ENABLE_ATSC
       || (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATSC_SCAN)
      #endif
       )
    {
        return TRUE;
    }

#if ENABLE_PVR
    enPVRState PVRState = MApp_PVR_StateMachineGet();

    if (  (PVRState == E_PVR_STATE_TIMESHIFT)
       || (PVRState == E_PVR_STATE_RECORD)
       || (PVRState == E_PVR_STATE_PLAYBACK)
       || (PVRState == E_PVR_STATE_RECORDnPLAYBACK)
       )
    {
        return TRUE;
    }
#endif

    if (bDuringChannelChange)
    {
        return TRUE;
    }

    return FALSE;
}


static void msCecAddDevice(MsCEC_DEVICELA enDevice, BOOLEAN uSendGivePhyAddr)
{
    if (enDevice < E_LA_UNREGISTERED)
    {
        if (msAPI_CEC_IsDeviceExist(enDevice) == FALSE)
        {
            _stMsApiCecInfoList.bCecDevicesExisted[enDevice] = TRUE;

            _stMsApiCecInfoList.u8CecDeviceCount++;

            if (uSendGivePhyAddr)
                msAPI_CEC_PostMsg_GivePhysicalAddress(DIRECTMSG, enDevice);

            if (enDevice == E_LA_AUDIO_SYS)
            {
                if ( (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
                  #if ARC_COMMAND_ONLY_IF_AMP_IN_CORRECT_PORT
                   &&( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
                     &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
                  #endif
                   )
                {
                    //msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);
                #if 0//(ENABLE_DOLBY_BULLETIN24)
                    msAPI_CEC_PostMsg_RequestShortAudioDescriptor(POSTMSG, E_LA_AUDIO_SYS);
                #endif
                }
            }

            //CEC_DPRINTF("[Add New Device] 0x%x \n", (MS_U8)enDevice );
        }
    }
}


static void msCecRemoveDevice(MsCEC_DEVICELA enDevice)
{
    MS_U8 txbuf[3] = {0x00, 0x00, 0x00};

    if (msAPI_CEC_IsDeviceExist(enDevice) == TRUE)
    {
        CEC_DPRINTF("[Remove Device] %bx \n", (MS_U8) enDevice);

        _stMsApiCecInfoList.bCecDevicesExisted[enDevice] = FALSE;

        msAPI_CEC_SetDeviceIdx_PhyAddr(enDevice, 0x00);

        msAPI_CEC_SetDeviceName(enDevice, NULL, TRUE);

        msAPI_CEC_SetDeviceVendorID(enDevice, txbuf);

        msAPI_CEC_SetCecVersion(enDevice, 0xFF);

        msAPI_CEC_SetDeviceType(enDevice, E_DEVICE_TYPE_TV);

        _stMsApiCecInfoList.u8CecDeviceCount--;

        if ( _stMsApiCecInfoList.u8CecDeviceCount > 0)
        {
            msCecShowDeviceMap();
        }
        else
        {
            msCecSetActiveDevice(E_LA_TV);
        }

    #if (ENABLE_DOLBY_BULLETIN24)
        if (enDevice == E_LA_AUDIO_SYS)
        {
            msAPI_DolbyBulletin24_remove_SAD();
        }
    #endif
    }
}

void msAPI_CEC_RequestARCAction(U8 action)
{
    MsCEC_DEVICELA DeviceIdex = MApi_CEC_GetActiveLogicalAddress();
#if ARC_PATCH_FOR_CHINA
    U8  port = SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) - INPUT_SOURCE_HDMI + 1;
    U16 u16AMPPhyAddr = msAPI_CEC_GetDeviceIdx_PhyAddr(E_LA_AUDIO_SYS);
#endif

    if (DeviceIdex < E_LA_FREE_USE)
    {
        if (action == CEC_ARC_REQUEST_INITIATION)
        {
          #if ARC_PATCH_FOR_CHINA
            SetArcOnBehavior();
          #else
            msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);
          #endif
        }
        else if (action == CEC_ARC_REQUEST_TERMINATION)
        {
            msCecSetARCStatus(FALSE);
            msAPI_CEC_PostMsg_RequestARCTermination(DIRECTMSG, E_LA_AUDIO_SYS);

          #if ARC_PATCH_FOR_CHINA
            if (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS))
            {
                if ( IsHDMIInUse())
                {
                    if ( (u16AMPPhyAddr & 0xF000) == (port * 0x1000) )
                    {
                        msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
                    }
                }
                else
                {
                    msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
                }
            }
          #endif
        }
    }
}

//***************************************************************************************


static void msCecInputSourceSwitchHDMI(E_UI_INPUT_SOURCE CecUIInputSource)
{
    if ( 1
      #if (INPUT_HDMI_VIDEO_COUNT >= 1)
       && (CecUIInputSource != UI_INPUT_SOURCE_HDMI)
      #endif
      #if (INPUT_HDMI_VIDEO_COUNT >= 2)
       && (CecUIInputSource != UI_INPUT_SOURCE_HDMI2)
      #endif
      #if (INPUT_HDMI_VIDEO_COUNT >= 3)
       && (CecUIInputSource != UI_INPUT_SOURCE_HDMI3)
      #endif
      #if (INPUT_HDMI_VIDEO_COUNT >= 4)
       && (CecUIInputSource != UI_INPUT_SOURCE_HDMI4)
      #endif
       )
    {
        return;
    }

  #if ENABLE_DMP
    if(IsStorageInUse())
    {
        MApp_MPlayer_StopPreview();
        MApp_MPlayer_Stop();
        MApp_MPlayer_ExitMediaPlayer();
    }
  #endif

    if(UI_INPUT_SOURCE_TYPE != CecUIInputSource)
    {
        MApp_ZUI_ACT_ShutdownOSD();

        MApp_ZUI_ACT_InputSourceSwitch(CecUIInputSource);
    }
  #if ENABLE_DMP
    MApp_ChannelChange_VariableInit();
    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
  #endif
}

void msAPI_CEC_DeviceChange(MsCEC_DEVICELA enChangedDevice)
{
    WORD u16ChangedPhyAddr, u16CurrentPhyAddr;
    MS_U8 u8Value;
    MS_U8 au8TxBuf[2];

    u16CurrentPhyAddr = msAPI_CEC_GetActivePhyAddr();

    //VL++
    u16ChangedPhyAddr = msAPI_CEC_GetDeviceIdx_PhyAddr(enChangedDevice);
    u8Value = (u16ChangedPhyAddr & 0xF000) >> 12;

    CEC_MSG( printf("\e[31;1;42m[CEC] Device Change from 0x%x ", u16CurrentPhyAddr) );
    CEC_MSG( printf("to [0x%x][0x%x] \033[0m \n", u16ChangedPhyAddr, enChangedDevice) );

  #if 0 // 11.1.2-1: CTS request us to select any device
    if (u16CurrentPhyAddr == u16ChangedPhyAddr)
        return;
  #endif

    /*
    CEC compliance test 11.1.2-1: froce to change source if it's not in HDMI
    */
    if (IsHDMIInUse() == FALSE)
    {
        E_UI_INPUT_SOURCE eUiInputSource = UI_INPUT_SOURCE_NONE;

        switch (u8Value)
        {
            case 0x01:
                if (UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI)
                {
                    eUiInputSource = UI_INPUT_SOURCE_HDMI;
                }
                break;

          #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case 0x02:
                if (UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI2)
                {
                    eUiInputSource = UI_INPUT_SOURCE_HDMI2;
                }
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case 0x03:
                if (UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI3)
                {
                    eUiInputSource = UI_INPUT_SOURCE_HDMI3;
                }
            break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case 0x04:
                if (UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI4)
                {
                    eUiInputSource = UI_INPUT_SOURCE_HDMI4;
                }
            break;
          #endif
        }

        if (eUiInputSource != UI_INPUT_SOURCE_NONE)
        {
            msCecInputSourceSwitchHDMI(eUiInputSource);
        }
    }

    if ( enChangedDevice != E_LA_AUDIO_SYS )
    {
        msCecSetActiveDevice(enChangedDevice);
        msAPI_CEC_SetActivePhyAddr(u16ChangedPhyAddr);

        if (u16ChangedPhyAddr != 0xFFFF)
        {
            au8TxBuf[0] = u16ChangedPhyAddr >> 8;
            au8TxBuf[1] = u16ChangedPhyAddr & 0xFF;

            msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, au8TxBuf);

            // should also update the active Physical Address
            _stMsApiCecInfoList.u8ActiveSourceAddress[0] = au8TxBuf[0];
            _stMsApiCecInfoList.u8ActiveSourceAddress[1] = au8TxBuf[1];
            _stMsApiCecInfoList.u16ActiveSourceAddress = u16ChangedPhyAddr;
        }
    }
}

//**************************************************************************
// For CEC usage - sending routing change or active source when switching source
// - Routing change: HDMI -> HDMI, non-HDMI -> HDMI
// - Active source   : HDMI -> non-HDMI

void msAPI_CEC_RoutingControl_SourceChange(INPUT_SOURCE_TYPE_t pre_srctype, INPUT_SOURCE_TYPE_t cur_srctype)
{
    U8 orig_phyaddress[2], new_phyaddress[2];

    CEC_MSG( printf("\e[31;1m >> SourceChange(%d, %d) \33[m \n", pre_srctype, cur_srctype) );

    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return;
    }

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == DISABLE)
    {
       return;
    }

    MApp_CEC_SetMyPhyAddr(pre_srctype, cur_srctype);

    if ( IsSrcTypeHDMI(pre_srctype) && (!IsSrcTypeHDMI(cur_srctype)) )
    {
        MS_U8 au8TxBuf[2];

        au8TxBuf[0] = 0x00;
        au8TxBuf[1] = 0x00;

        msAPI_CEC_PostMsg_ActiveSource(DIRECTMSG, au8TxBuf);
    }
    else if ( (IsSrcTypeHDMI(pre_srctype) && IsSrcTypeHDMI(cur_srctype))
           || (!IsSrcTypeHDMI(pre_srctype) && IsSrcTypeHDMI(cur_srctype)) )
    {
        switch (pre_srctype)
        {
            case INPUT_SOURCE_HDMI:
                orig_phyaddress[0] = CEC_PORT1;
                break;

          #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_HDMI2:
                orig_phyaddress[0] = CEC_PORT2;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case INPUT_SOURCE_HDMI3:
                orig_phyaddress[0] = CEC_PORT3;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case INPUT_SOURCE_HDMI4:
                orig_phyaddress[0] = CEC_PORT4;
                break;
          #endif

            default:
                if(!IsSrcTypeHDMI(pre_srctype)) // switch to the internal TV sources
                    orig_phyaddress[0] = 0x00;
                break;
        }
        orig_phyaddress[1] = 0x00;

        switch (cur_srctype)
        {
            case INPUT_SOURCE_HDMI:
                new_phyaddress[0] = CEC_PORT1;
                break;

          #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case INPUT_SOURCE_HDMI2:
                new_phyaddress[0] = CEC_PORT2;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case INPUT_SOURCE_HDMI3:
                new_phyaddress[0] = CEC_PORT3;
                break;
          #endif

          #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case INPUT_SOURCE_HDMI4:
                new_phyaddress[0] = CEC_PORT4;
                break;
          #endif

            default:
                break;
        }
        new_phyaddress[1] = 0x00;

        msAPI_CEC_PostMsg_RoutingChange(DIRECTMSG, orig_phyaddress, new_phyaddress);

        msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, new_phyaddress);
    }

  #if ARC_PATCH_FOR_CHINA
    if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
    {
         if(msAPI_CEC_ARC_GetAmpMute() == FALSE) //for Yamaha amp will unmute after SetArcOnBehavior()
        {
            SetArcOnBehavior();
        }
    }
    else
    {
        CEC_ARC_INFO( printf("\e[31;1m Line: %d \33[m \n", __LINE__) );
        msAPI_CEC_PostMsg_RequestARCTermination(POSTMSG, E_LA_AUDIO_SYS);
        msAPI_CEC_SetSystemUnMute();
        msCecSetARCStatus(FALSE);
    }
  #endif
}

//**************************************************************************

void msAPI_CEC_ForceImmediatelyPolling(BOOLEAN bCecDeviceListPolling)
{
    MsCEC_DEVICELA idx = E_LA_TV;

  #if 1
    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == TRUE)
    {
        CEC_MSG( printf("\e[31;1;42m[CEC] trigger Device Recognition \033[0m \n") );

      #if 0

        msCecInitCecStructure();

      #else // only update State;

        _stMsApiCecInfoList.fCecDeviceListPolling = bCecDeviceListPolling;

        _stMsApiCecInfoList.fCecFirstPollingFinish = FALSE;

        for (idx = E_LA_RECORDER1; idx < (E_LA_MAX+1); idx++)
        {
            _stMsApiCecInfoList.State[idx] = E_STM_POLLING;
            _stMsApiCecInfoList.bCecDevicesExisted[idx] = FALSE;
        }

      #endif

        msCecEmptySwMsgQueue();
    }
  #else
    g_bCecForceImmediatelyPolling = TRUE;

    msCecInitCecStructure();
  #endif
}

void msAPI_CEC_SendMenuRequestDeactive(void)
{
    if((gCECMenuControlEnable == TRUE) && (gCECGetMenuStatusMsg == TRUE))
    {
        msAPI_CEC_PostMsg_MenuRequest(DIRECTMSG,msAPI_CEC_GetActiveDevice(),E_MSG_MENU_REQ_DEACTIVATED);
    }
}


//
/***********************
 - ARC setting: Off -> On
Audio system is connected HDMI port which support ARC and
change ARC setting from "Off" to "On", TV sends <Request ARC Initiation>
***********************/
//
void msAPI_CEC_ARC_Off2On(void)
{
    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == DISABLE)
        return;

    CEC_MSG( printf("\n\033[41;4m[CEC] ARC: Off -> On \033[0m \n") );

    if ( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
       &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
    {
        CEC_STATE_INFO( printf("\033[41;4m[CEC] trigger ARC Off -> On \033[0m \n") );

        _stCecStateInfoList.stState_ArcOff2On.enState =
            CEC_ARC_OFF2ON_SEND_REQUEST_ARC_INITIATION;
    }
}

//
/***********************
 - ARC setting: On -> Off
Audio system is connected HDMI port which support ARC and
change ARC setting from "On" to "Off", TV sends <Request ARC Termination>
***********************/
//
void msAPI_CEC_ARC_On2Off(void)
{
    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == DISABLE)
        return;

    CEC_MSG( printf("\n\033[41;4m[CEC] ARC: On -> Off \033[0m \n") );

    if (MApp_CEC_CheckDeviceValidForARC() == TRUE)
    {
        CEC_STATE_INFO( printf("\033[41;4m[CEC] trigger ARC On -> Off \033[0m \n") );

        _stCecStateInfoList.stState_ArcOn2Off.enState =
            CEC_ARC_ON2OFF_SEND_REQUEST_ARC_TERMINATION;
    }
}

//***************************************************************************************

void msAPI_CEC_DeviceRecog_Polling(void)
{
    CEC_ERROR_CODE  res = E_CEC_FEATURE_ABORT;

    //check LA(m_CECInfoExtend.PollingIdx) is legal
    ASSERT(MSrv_IsLALegal(_stMsApiCecInfoList.PollingIdx));

    if (_stMsApiCecInfoList.PollingIdx == E_LA_TV)
    {
        _stMsApiCecInfoList.PollingIdx = E_LA_RECORDER1;
    }

    if ( (_stMsApiCecInfoList.fCecDeviceListPolling == FALSE)
       &&(_stMsApiCecInfoList.PollingIdx == RESERVED_1)
       )
    {
        U8 orig_phyaddress[2], new_phyaddress[2];

        orig_phyaddress[0] = 0x00;
        orig_phyaddress[1] = 0x00;

        new_phyaddress[0] = _stMsApiCecInfoList.u8ActiveSourceAddress[0];
        new_phyaddress[1] = _stMsApiCecInfoList.u8ActiveSourceAddress[1];

        msAPI_CEC_PostMsg_RoutingChange(DIRECTMSG, orig_phyaddress, new_phyaddress);
    }

    if ( _stMsApiCecInfoList.PollingIdx == E_LA_UNREGISTERED )
    {
        CEC_MSG( printf("\n\033[32;1m Device recognition done (%d ms).. \033[0m \n\n",
            msHDMICecGetTimeInterval(INTERVAL_CEC_DeviceRecognition) ) );

        //depend on msAPI_CEC_CheckWakeupByOneTouchPlayCommand()
        if ( (_stMsApiCecInfoList.PowerOnByActiveSource)
           ||( (_stMsApiCecInfoList.fCecPowerOnPollingFinish == FALSE)
             &&(_stMsApiCecInfoList.enActiveDeviceLA == E_LA_TV) )  // no active source while booting up
           )
        {
            msAPI_CEC_PostMsg_RequestActiveSource(POSTMSG);
        }

        _stMsApiCecInfoList.fCecFirstPollingFinish  = TRUE ;
        _stMsApiCecInfoList.fCecARCStatusFinish     = TRUE;
        _stMsApiCecInfoList.PollingIdx              = E_LA_RECORDER1 ;
        _stMsApiCecInfoList.enPowerStatus[E_LA_TV]  = E_MSG_PWRSTA_ON;
        _stMsApiCecInfoList.fCecDeviceListPolling   = FALSE;

        _stMsApiCecInfoList.fCecPowerOnPollingFinish = TRUE;

        msCecSetStartTime(INTERVAL_CEC_FSM_RequestARC);

        return;
    }

    res = msAPI_CEC_PingDevice(_stMsApiCecInfoList.PollingIdx);

    CEC_MSG( printf("\e[32;1m <Ping %X> %s (0x%x) \033[0m \n", _stMsApiCecInfoList.PollingIdx,
                        ((res & E_CEC_TX_SUCCESS)?("- added"):("       ")), res) );

    /*
    TV send only Ping messagee when execute device scan while booting up,
    and AMP is in standby mode; sometimes we will get ping status as system busy;
    utopia will not ping again.
    */
  #if 0
    if (res == E_CEC_SYSTEM_BUSY)
    {
        MsOS_DelayTask(INTERVAL_200_MS);    // wait 200 ms

        res = msAPI_CEC_PingDevice(_stMsApiCecInfoList.PollingIdx);

        CEC_MSG( printf("\033[41;4m <Ping %X> %s (0x%x) \033[0m \n", _stMsApiCecInfoList.PollingIdx,
                            ((res & E_CEC_TX_SUCCESS)?("- added"):("       ")), res) );
    }
  #endif

    if (res == E_CEC_TX_SUCCESS)
    {
        if (_stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx] == E_STM_POLLING)
        {
            _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx] = E_STM_ACKED ;
        }
    }
    else
    {
        _stMsApiCecInfoList.CecFirstPollingCnt++ ;
        _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx] = E_STM_POLLING ;
        _stMsApiCecInfoList.enPowerStatus[_stMsApiCecInfoList.PollingIdx] = E_MSG_PWRSTA_UNKNOW ;

        if (_stMsApiCecInfoList.PollingIdx == E_LA_AUDIO_SYS)
        {
            CEC_MSG( printf("\033[32;1m[CEC]{%4d} SysAudioMode set to OFF \033[0m \n", __LINE__) );
            _stMsApiCecInfoList.SysAudioMode = FALSE ;
        }
    }

    if( _stMsApiCecInfoList.CecFirstPollingCnt == HDMI_CEC_FIRST_POLLING_CNT )
    {
        if( _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx] == E_STM_POLLING)
        {
            _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx] = E_STM_EMPTY;
        }
        _stMsApiCecInfoList.PollingIdx = (MsCEC_DEVICELA)(_stMsApiCecInfoList.PollingIdx+1) ;
        _stMsApiCecInfoList.CecFirstPollingCnt = 0 ;
    }
}

static void msCecDeviceRecognition(void)
{
    MsCEC_DEVICELA idx = _stMsApiCecInfoList.PollingIdx;
    EN_CEC_STATEMACHINE_CECLIST State = _stMsApiCecInfoList.State[idx];

    if (State == E_STM_EMPTY)
        return;

    CEC_MSG( printf("\e[33;1m[CEC] msAPI_CEC_DeviceRecog(0x%02X): %d \033[0m \n",
                        idx, (int)State) );
    if ( (State > E_STM_ACKED) && (State < E_STM_NONE) )
    {
        CEC_MSG( printf("\e[33;1m      (%d) %s \033[0m \n",
                        (int)_stMsApiCecInfoList.State[idx],
                        (char *) CEC_StatemachineCecListStr[State]) );
    }

    switch (_stMsApiCecInfoList.State[idx])
    {
        case E_STM_POLLING:
            msAPI_CEC_DeviceRecog_Polling();
            break;

        case E_STM_ACKED:
            _stMsApiCecInfoList.State[idx] = E_STM_GIVE_PHY_ADDR;
            break;

        case E_STM_GIVE_PHY_ADDR:
            msAPI_CEC_PostMsg_GivePhysicalAddress(DIRECTMSG, idx);

            /*
            recovery: somehow QD882 sent <Report Physical Address>,
                      however, SW can not receive this message.
            */
            msCecSetStartTime(INTERVAL_CEC_DeviceRecognition_ReportPhyAddr);

            _stMsApiCecInfoList.State[idx] = E_STM_REPORT_PHY_ADDR;
            break;

        case E_STM_REPORT_PHY_ADDR:
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_DeviceRecognition_ReportPhyAddr)
                > INTERVAL_200_MS )
            {
                msAPI_CEC_PostMsg_GivePhysicalAddress(DIRECTMSG, idx);
                MsOS_DelayTask(INTERVAL_100_MS);
                _stMsApiCecInfoList.State[idx] = E_STM_GIVE_DEV_VENDOR_ID;
            }
            break;

        case E_STM_GIVE_DEV_VENDOR_ID:
          #if VENDOR_SPECIFIC_SUPPORT
            msAPI_CEC_PostMsg_GiveDeviceVendorID(DIRECTMSG, idx);
          #endif

            _stMsApiCecInfoList.State[idx] = E_STM_GET_CEC_VER;
            break;

        case E_STM_GET_CEC_VER:
          #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
            msAPI_CEC_PostMsg_GetCECVersion(DIRECTMSG, idx);
          #endif

            _stMsApiCecInfoList.State[idx] = E_STM_GIVE_OSD_NAME;
            break;

        case E_STM_GIVE_OSD_NAME:
          #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
            msAPI_CEC_PostMsg_GiveOSDName(DIRECTMSG, idx);
          #endif

            /* 1. when TV detects Audio system */
            if ( idx == E_LA_AUDIO_SYS )
            {
                /*
                2. TV Speakers setting is "Speakers EasyLink"
                11.1.15-4: issues a <Give System Audio Mode Status> message to the amplifier.
                */
                if ( (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
                  #if 0//ARC_COMMAND_ONLY_IF_AMP_IN_CORRECT_PORT
                   &&( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
                     &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
                  #endif
                    )
                {
                    _stMsApiCecInfoList.State[idx] = E_STM_GIVE_AUDIO_MODE_STATUS;
                }
                else if ( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
                        &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
                {
                    _stMsApiCecInfoList.State[idx] = E_STM_REQUEST_SHORT_AUDIO_DESCRIPTOR;
                }
                else
                {
                    _stMsApiCecInfoList.State[idx] = E_STM_DONE;
                }
            }
            else
            {
                _stMsApiCecInfoList.State[idx] = E_STM_DONE;
            }
            break;

        case E_STM_GIVE_AUDIO_MODE_STATUS:
            msAPI_CEC_PostMsg_GiveSystemAudioModeStatus(DIRECTMSG, idx);

          #if 0
            /* Audio system is connected with HDMI port which support ARC */
            if ( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
               &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
            {
                _stMsApiCecInfoList.State[idx] = E_STM_REQUEST_ARC_STATUS;
            }
            else
            {
                _stMsApiCecInfoList.State[idx] = E_STM_DONE;
            }
          #else
            _stMsApiCecInfoList.State[idx] = E_STM_REQUEST_SHORT_AUDIO_DESCRIPTOR;
          #endif

            break;

        case E_STM_REQUEST_ARC_STATUS:
            if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
            {
                msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);
            }
            else
            {
                msAPI_CEC_PostMsg_RequestARCTermination(DIRECTMSG, E_LA_AUDIO_SYS);
            }

            _stMsApiCecInfoList.State[idx] = E_STM_REQUEST_SHORT_AUDIO_DESCRIPTOR;
            break;

        case E_STM_REQUEST_SHORT_AUDIO_DESCRIPTOR:
          #if (ENABLE_DOLBY_BULLETIN24)
            msAPI_CEC_PostMsg_RequestShortAudioDescriptor(DIRECTMSG, idx);
          #endif

            _stMsApiCecInfoList.State[idx] = E_STM_DONE;
            break;


        case E_STM_GIVE_POW_STATUS:
        case E_STM_REQUEST_ACTIVE_SOURCE:
        case E_STM_SET_STREAM_PATH:
            _stMsApiCecInfoList.State[idx] = E_STM_DONE;
            break;

        case E_STM_DONE:
            _stMsApiCecInfoList.PollingIdx = (MsCEC_DEVICELA)(_stMsApiCecInfoList.PollingIdx+1) ;
            _stMsApiCecInfoList.CecFirstPollingCnt = 0;

            _stMsApiCecInfoList.State[idx] = E_STM_NONE;
            break;

        case E_STM_NONE:
        default:
            // do nothing
            break;
    }
}


//
/***********************
When the following conditions are met,
then TV acquires the device information only from the detected device.
 - TV is in power-on state
 - TV detected that the new device is connected by receiving <Report Physical Address>
***********************/
//
void msCecDeviceDetect(MsCEC_DEVICELA idx)
{
    if ( (_stMsApiCecInfoList.State[idx] < E_STM_GIVE_PHY_ADDR)
       ||(_stMsApiCecInfoList.State[idx] > E_STM_GIVE_OSD_NAME) )
    {
        return;
    }

    CEC_MSG( printf("\033[41;4m[CEC] DeviceDetect(0x%02X): %d \033[0m \n",
                                idx, (int)_stMsApiCecInfoList.State[idx]) );

    switch (_stMsApiCecInfoList.State[idx])
    {
        case E_STM_GIVE_PHY_ADDR:
            CEC_MSG( printf("      -> E_STM_GIVE_DEV_VENDOR_ID \n") );
          #if VENDOR_SPECIFIC_SUPPORT
            msAPI_CEC_PostMsg_GiveDeviceVendorID(DIRECTMSG, idx);
          #endif
            _stMsApiCecInfoList.State[idx] = E_STM_GIVE_DEV_VENDOR_ID;
            break;

        case E_STM_GIVE_DEV_VENDOR_ID:
            CEC_MSG( printf("      -> E_STM_GET_CEC_VER \n") );
          #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
            msAPI_CEC_PostMsg_GetCECVersion(DIRECTMSG, idx);
          #endif
            _stMsApiCecInfoList.State[idx] = E_STM_GET_CEC_VER;
            break;

        case E_STM_GET_CEC_VER:
            CEC_MSG( printf("      -> E_STM_GIVE_OSD_NAME \n") );
          #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
            msAPI_CEC_PostMsg_GiveOSDName(DIRECTMSG, idx);
          #endif
            _stMsApiCecInfoList.State[idx] = E_STM_GIVE_OSD_NAME;
            break;

        case E_STM_GIVE_OSD_NAME:
            if (idx == E_LA_AUDIO_SYS)
            {
                /*
                Only when TV detects Audio system and TV Speakers setting is "Speakers EasyLink"
                */
                if ( (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
                  #if ARC_COMMAND_ONLY_IF_AMP_IN_CORRECT_PORT
                   &&( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
                     &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
                  #endif
                   )
                {
                    _stCecStateInfoList.stState_DeviceDetect.enState =
                        CEC_DEVICE_DETECT_SEND_GIVE_SYSTEM_AUDIO_MODE_STATUS;
                }
                else
                {
                    _stCecStateInfoList.stState_DeviceDetect.enState =
                        CEC_DEVICE_DETECT_SEND_REQUEST_SHORT_AUDIO_DESCRIPTOR;

                }
            }
            else
            {
                INPUT_SOURCE_TYPE_t eInput = stSystemInfo[MAIN_WINDOW].enInputSourceType;

                if ( ((_stMsApiCecInfoList.u8PhysicalAddress[idx][0] & 0xF0)>>4) ==
                     ((U8)(eInput-INPUT_SOURCE_HDMI)+1) )
                {
                    _stCecStateInfoList.stState_DeviceDetect.enState =
                        CEC_DEVICE_DETECT_SEND_REQUEST_ACTIVE_SOURCE;
                }
                else
                {
                    _stCecStateInfoList.stState_DeviceDetect.enState =
                        CEC_DEVICE_DETECT_PROCESS_FINISH;
                }
            }

            if (_stCecStateInfoList.stState_DeviceDetect.enState != CEC_DEVICE_DETECT_IDLE)
            {
                CEC_STATE_INFO( printf("\e[31;1;42m[CEC] trigger Device Detect %s \033[0m \n",
                    (char *) CEC_Device_Detect_Str[_stCecStateInfoList.stState_DeviceDetect.enState]) );
            }

            _stMsApiCecInfoList.State[idx] = E_STM_NONE;
            break;

        case E_STM_NONE:
        default:
            // do nothing
            break;
    }
}

//
// polling all devices
//
static void msCecPollingFSM(void)
{
    CEC_ERROR_CODE res = E_CEC_FEATURE_ABORT;

    //check LA(m_CECInfoExtend.PollingIdx) is legal
    ASSERT(MSrv_IsLALegal(_stMsApiCecInfoList.PollingIdx));

    // Normally we polling 1 time when we enter this polling FSM
    //CEC Device LA 12, 13 are reserved
    if ( (_stMsApiCecInfoList.PollingIdx <= E_LA_PLYBACK3)
       ||(_stMsApiCecInfoList.PollingIdx >= E_LA_FREE_USE) )
    {
        res = msAPI_CEC_PingDevice(_stMsApiCecInfoList.PollingIdx);

        // If the LA is avaliable on CEC List, give it one more try.
        if ( (res != E_CEC_TX_SUCCESS)
           &&(E_STM_EMPTY != _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx]) )
        {
            res = msAPI_CEC_PingDevice(_stMsApiCecInfoList.PollingIdx);
        }
    }
    else
    {
        res = E_CEC_FEATURE_ABORT;
    }

    if (res == E_CEC_TX_SUCCESS)
    {
        if (E_STM_EMPTY == _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx])
        {
            _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx] = E_STM_GIVE_PHY_ADDR;
            msAPI_CEC_PostMsg_GivePhysicalAddress(DIRECTMSG, _stMsApiCecInfoList.PollingIdx);
            printf("\e[32;1m <%X> work \033[0m \n", _stMsApiCecInfoList.PollingIdx);
        }
    }
    else
    {
        if ( (_stMsApiCecInfoList.PollingIdx <= E_LA_MAX)
           &&(E_STM_EMPTY != _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx]) )
        {
            printf("\e[32;1m <%X> unplugged \033[0m \n", _stMsApiCecInfoList.PollingIdx);

            if (_stMsApiCecInfoList.PollingIdx == E_LA_AUDIO_SYS)
            {
                //msCecSetARCStatus(FALSE);
                msAPI_CEC_SetSystemUnMute();
                msAPI_CEC_SetSystemAudioMode(FALSE);
                gIsCECAmpARCOn = FALSE;
            }

            _stMsApiCecInfoList.State[_stMsApiCecInfoList.PollingIdx] = E_STM_EMPTY ;
            _stMsApiCecInfoList.enPowerStatus[_stMsApiCecInfoList.PollingIdx] = E_MSG_PWRSTA_UNKNOW ;

            msCecRemoveDevice(_stMsApiCecInfoList.PollingIdx);
        }
    }

    _stMsApiCecInfoList.PollingIdx = (MsCEC_DEVICELA)(_stMsApiCecInfoList.PollingIdx+1);

  #if PING_AMP_QUICKLY
    if (_stMsApiCecInfoList.PollingIdx == E_LA_AUDIO_SYS)
    {
        _stMsApiCecInfoList.PollingIdx = (MsCEC_DEVICELA)(_stMsApiCecInfoList.PollingIdx+1);
    }
  #endif

    if (_stMsApiCecInfoList.PollingIdx == E_LA_UNREGISTERED)
    {
        _stMsApiCecInfoList.PollingIdx = E_LA_RECORDER1;
        _stMsApiCecInfoList.fCecStartNormalPollingOnce = FALSE;
        msCecSetStartTime(INTERVAL_CEC_Polling_Once);
    }
}

//
// ping AMP if exist
//
static void msCecPollingAMP(void)
{
    CEC_ERROR_CODE res = E_CEC_FEATURE_ABORT;

    res = msAPI_CEC_PingDevice(E_LA_AUDIO_SYS);

    // If the LA is avaliable on CEC List, give it one more try.
    if ( (res != E_CEC_TX_SUCCESS)
       &&(E_STM_EMPTY != _stMsApiCecInfoList.State[E_LA_AUDIO_SYS]) )
    {
        res = msAPI_CEC_PingDevice(E_LA_AUDIO_SYS);
    }

    if (res == E_CEC_TX_SUCCESS)
    {
        if (E_STM_EMPTY == _stMsApiCecInfoList.State[E_LA_AUDIO_SYS])
        {
            _stMsApiCecInfoList.State[E_LA_AUDIO_SYS] = E_STM_GIVE_PHY_ADDR;
            msAPI_CEC_PostMsg_GivePhysicalAddress(DIRECTMSG, E_LA_AUDIO_SYS);
            printf("\e[32;1m AMP work \033[0m \n");
        }
    }
    else
    {
        if (E_STM_EMPTY != _stMsApiCecInfoList.State[E_LA_AUDIO_SYS])
        {
            printf("\e[32;1m AMP unplugged \033[0m \n");

            //msCecSetARCStatus(FALSE);
            msAPI_CEC_SetSystemUnMute();
            msAPI_CEC_SetSystemAudioMode(FALSE);
            gIsCECAmpARCOn = FALSE;

            _stMsApiCecInfoList.State[E_LA_AUDIO_SYS] = E_STM_EMPTY ;
            _stMsApiCecInfoList.enPowerStatus[E_LA_AUDIO_SYS] = E_MSG_PWRSTA_UNKNOW ;

            msCecRemoveDevice(E_LA_AUDIO_SYS);
        }
    }

    msCecSetStartTime(INTERVAL_CEC_Polling_AMP_Once);
}

static void msCecPollingDevices(void)
{
    MsCEC_DEVICELA DeviceIdx;

    /******************************************
    ***** For Device recognition sequence *****
    *******************************************/
    if (_stMsApiCecInfoList.fCecFirstPollingFinish)
    {
        /***********************
        When TV detected that the new device is connected
        by receiving <Report Physical Address>,
        TV acquires the device information only from the detected device
        ***********************/
        if ( msHDMICecGetTimeInterval(INTERVAL_CEC_DeviceDetectByReportPhyAddr)
           > INTERVAL_1_SECOND )
        {
            msCecSetStartTime(INTERVAL_CEC_DeviceDetectByReportPhyAddr) ;

            for (DeviceIdx=E_LA_RECORDER1; DeviceIdx<E_LA_MAX; DeviceIdx=(MsCEC_DEVICELA)(DeviceIdx+1))
            {
                msCecDeviceDetect(DeviceIdx) ;
            }
        }

      #if ARC_PATCH_FOR_CHINA
        if (_stMsApiCecInfoList.fCecARCStatusFinish)
        {
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_RequestARC) > INTERVAL_600_MS )
            {
                _stMsApiCecInfoList.fCecARCStatusFinish = FALSE;

                if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
                {
                    SetArcOnBehavior();
                }
                else
                {
                    msAPI_CEC_SetSystemUnMute();
                    if (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS))
                    {
                        msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, TRUE);
                    }
                }
            }
        }
      #endif
        if (_stMsApiCecInfoList.fCecARCStatusFinish)
        {
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_RequestARC) > INTERVAL_600_MS )
            {
                _stMsApiCecInfoList.fCecARCStatusFinish = FALSE;

                if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
                {
                    SetArcOnBehavior();
                }
            }
        }

    #if CEC_BACKGROUND_POLLING

        /***** Background Normal Polling *****/
        if ( msHDMICecGetTimeInterval(INTERVAL_CEC_Polling_Once) > INTERVAL_60_SECOND )
        {
            _stMsApiCecInfoList.fCecStartNormalPollingOnce = TRUE;
            msCecSetStartTime(INTERVAL_CEC_Polling_Once);
        }

        if ( msHDMICecGetTimeInterval(INTERVAL_CEC_Normal_Polling) > INTERVAL_200_MS )
        {
            if (_stMsApiCecInfoList.fCecStartNormalPollingOnce)
            {
                msCecPollingFSM();
                msCecSetStartTime(INTERVAL_CEC_Normal_Polling) ;
            }
        }

      #if PING_AMP_QUICKLY
        if ( msHDMICecGetTimeInterval(INTERVAL_CEC_Polling_AMP_Once) > INTERVAL_20_SECOND )
        {
            msCecPollingAMP();
            msCecSetStartTime(INTERVAL_CEC_Polling_AMP_Once) ;
        }
      #endif

    #endif // #if CEC_BACKGROUND_POLLING

        /**********************************************************************/
    }
    else
    {
        msCecSetStartTime(INTERVAL_CEC_DeviceRecognition);
        msCecSetStartTime(INTERVAL_CEC_DeviceDetectByReportPhyAddr);

        msCecDeviceRecognition();
    }

    // TO DO

    msCecPollingCustomer();
}


static void msCecFeatureAbortHandler(ST_CEC_MSG stCecMsg)
{
    MS_U8 u8opCode = stCecMsg.u8Para[0];
    MsCEC_DEVICELA enDeviceFA = (MsCEC_DEVICELA) (stCecMsg.u8header & 0x0F);

    CEC_DPRINTF("UnSupport opCode =%bx \n", u8opCode);
    CEC_DPRINTF("UnSupport reason =%bx ", stCecMsg.u8Para[1]);
    CEC_DPRINTF("\e[31;1m %s \33[m \n", (char *)CEC_AbortReasonStr[stCecMsg.u8Para[1]]);

    switch (u8opCode)      //CEC1.3a Table 7 ~ 27
    {
      #if SYSTEM_AUDIO_CONTROL_SUPPORT
        case E_MSG_SAC_GIVE_AUDIO_STATUS:
        {
            break;
        }

        case E_MSG_ARC_REQUEST_ARC_INITIATION:
        {
            if (enDeviceFA == E_LA_AUDIO_SYS)
            {
                CEC_MSG(printf("\n Amp ARC OFF!\n"));
                gIsCECAmpARCOn = FALSE;

                printf(" speak open [%s,%s,%d]\n\n", __FUNCTION__,__FILE__,__LINE__);
                msCecSetARCStatus(FALSE);
            }

            break;
        }
      #endif


      #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
        case E_MSG_OSDNT_GIVE_OSD_NAME:
        {
            if (msAPI_CEC_IsDeviceExist(enDeviceFA) == TRUE )
            {
                msAPI_CEC_SetDeviceName(enDeviceFA, NULL, TRUE);
            }
        }
        break;
      #endif

    #if (ENABLE_DOLBY_BULLETIN24)
        case E_MSG_SAC_REQUEST_SHORT_AUDIO_DESCRIPTOR:
        {
            msAPI_DolbyBulletin24_remove_SAD();
        }
        break;
    #endif

      #if VENDOR_SPECIFIC_SUPPORT
        case E_MSG_VS_GIVE_DEVICE_VENDOR_ID:
        {
        }
        break;
      #endif

        default:
            break;
    }
}


BOOLEAN msCecCheckMsgFrame(ST_CEC_MSG stCecMsg)
{
    BOOLEAN bCheckFrameOK = TRUE;

    switch (stCecMsg.u8opcode)      //CEC1.3a Table 7 ~ 27
    {
    //----- One Touch Play ---------------
        case E_MSG_OTP_IMAGE_VIEW_ON:     //if in standby, firstly power on
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTP_IMAGE_VIEW_ON(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_OTP_TEXT_VIEW_ON:      //if in standby, firstly power on
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTP_TEXT_VIEW_ON(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- One Touch Play end ---------------


    //----- One Touch Play --------------
    //----- Routing Control --------------
        case E_MSG_ACTIVE_SOURCE:             //broadcast, if addressed, ignored
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ACTIVE_SOURCE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- One Touch Play end --------------
    //----- Routing Control end --------------


    //----- Routing Control --------------
        case E_MSG_RC_INACTIVE_SOURCE:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_INACTIVE_SOURCE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_REQUEST_ACTIVE_SOURCE:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_REQUEST_ACTIVE_SOURCE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_ROUTING_CHANGE:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 6) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_ROUTING_CHANGE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_ROUTING_INFORMATION:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_ROUTING_INFO(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_RC_SET_STREM_PATH:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_RC_SET_STREM_PATH(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- Routing Control end --------------


    //----- Standby Command --------------
    #if STANDBY_COMMAND_SUPPORT
        case E_MSG_STANDBY:
            if (MApi_CEC_CheckFrame(E_TRANS_BOTHTYPE_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_STANDBY(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if STANDBY_COMMAND_SUPPORT
    //----- Standby Command end --------------


    //----- One Touch Record--------------
    #if ONE_TOUCH_RECORD_SUPPORT
        case E_MSG_OTR_RECORD_ON:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTR_RECORD_ON(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_OTR_RECORD_OFF:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTR_RECORD_OFF(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_OTR_RECORD_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTR_RECORD_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        // Initiate a recording using the <Record On> message, or send a <Feature Abort> [!!¡ÓCannot provide source!!L]
        // if the presently displayed source is not recordable.
        case E_MSG_OTR_RECORD_TV_SCREEN:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OTR_RECORD_TV_SCREEN(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if ONE_TOUCH_RECORD_SUPPORT
    //----- One Touch Record end --------------


    //----- Timer programmer -------------
    #if TIMER_PROGRAMMER_SUPPORT
        case E_MSG_TP_CLEAR_ANALOGUE_TIMER:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_CLEAR_ANALOGUE_TIMER(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_CLEAR_DIGITAL_TIMER:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_CLEAR_DIGITAL_TIMER(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_CLEAR_EXTERNAL_TIMER:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_CLEAR_EXTERNAL_TIMER(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_SET_ANALOGUE_TIMER:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_SET_ANALOGUE_TIMER(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_SET_DIGITAL_TIMER:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_SET_DIGITAL_TIMER(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_SET_EXTERNAL_TIMER:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_SET_EXTERNAL_TIMER(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_SET_TIMER_PROGRAM_TITLE:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_SET_TIMER_PROGRAM_TITLE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_TIMER_CLEARD_STATUS:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_TIMER_CLEARD_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TP_TIMER_STATUS:
            //TO DO
            if(0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TP_TIMER_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif
    //----- Timer programmer end -------------


    //----- System Information -----------
    //----- Vendor Specific -----------
        case E_MSG_SI_CEC_VERSION:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_CEC_VERSION(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_GET_CEC_VERSION:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_GET_CEC_VERSION(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- System Information end -----------
    //----- Vendor Specific end -----------



    //----- System Information -----------
        case E_MSG_SI_GIVE_PHYSICAL_ADDRESS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_GIVE_PHYSICAL_ADDRESS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_REPORT_PHYSICAL_ADDRESS:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 5) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_REPORT_PHYSICAL_ADDRESS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_GET_MENU_LANGUAGE:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_GET_MENU_LANGUAGE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SI_SET_MENU_LANGUAGE:
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 5) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SI_SET_MENU_LANGUAGE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

//        case E_MSG_SI_POLLING_MESSAGE:
//                break;
    //----- System Information end -----------


    //----- Deck Control Feature----------
    #if DECK_CONTROL_SUPPORT
        case E_MSG_DC_DECK_CONTROL:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DC_DECK_CONTROL(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_DC_DECK_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DC_DECK_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_DC_GIVE_DECK_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DC_GIVE_DECK_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_DC_PLAY:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DC_PLAY(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if DECK_CONTROL_SUPPORT
    //----- Deck Control Feature end -----------


    #if TUNER_CONTROL_SUPPORT
    //----- Tuner Control ----------------
        case E_MSG_TC_GIVE_TUNER_DEVICE_STATUS:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TC_GIVE_TUNER_DEVICE_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TC_SEL_ANALOGUE_SERVICE:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TC_SEL_ANALOGUE_SERVICE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TC_SELECT_DIGITAL_SERVICE:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TC_SELECT_DIGITAL_SERVICE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TC_TUNER_DEVICE_STATUS:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TC_TUNER_DEVICE_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TC_TUNER_STEP_DECREMENT:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TC_TUNER_STEP_DECREMENT(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_TC_TUNER_STEP_INCREMENT:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_TC_TUNER_STEP_INCREMENT(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    #endif // #if TUNER_CONTROL_SUPPORT
    //----- Tuner Control end -----------


    //---------Vendor Specific -----------
        case E_MSG_VS_DEVICE_VENDOR_ID: // 0x87
            if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_DEVICE_VENDOR_ID(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_VS_GIVE_DEVICE_VENDOR_ID:   // 0x8C
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_GIVE_DEVICE_VENDOR_ID(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_VS_VENDOR_COMMAND:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_VENDOR_COMMAND(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_VS_VENDOR_COMMAND_WITH_ID:
            if (0)// ((MApi_CEC_CheckFrame(E_TRANS_BOTHTYPE_MSG, ) == 0) && (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0) )
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_VENDOR_COMMAND_WITH_ID(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_VS_VENDOR_REMOTE_BUTTON_DOWN:
            if (0)// ((MApi_CEC_CheckFrame(E_TRANS_BOTHTYPE_MSG, ) == 0) && (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0) )
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_VENDOR_REMOTE_BUTTON_DOWN(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_VS_VENDOR_REMOTE_BUTTON_UP:
            if (0)// ((MApi_CEC_CheckFrame(E_TRANS_BOTHTYPE_MSG, ) == 0) && (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0) )
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_VS_VENDOR_REMOTE_BUTTON_UP(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- Vendor Specific end -----------


    //----- OSD Display ------------------
        case E_MSG_SET_OSD_STRING:
            if (0)// (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SET_OSD_STRING(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- OSD Display end -----------


    //----- Device OSD Name Transfer  ----
        case E_MSG_OSDNT_GIVE_OSD_NAME:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OSDNT_GIVE_OSD_NAME(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_OSDNT_SET_OSD_NAME:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)    // at least 3 frames
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_OSDNT_SET_OSD_NAME(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- Device OSD Name Transfer end -----------


    //----- Device Menu Control ----------
        case E_MSG_DMC_MENU_REQUEST:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DMC_MENU_REQUEST(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_DMC_MENU_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DMC_MENU_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- Device Menu Control end -----------


    //----- Remote Control Passthrough ---
    //----- UI Message -------------------
        case E_MSG_DMC_USER_CONTROL_PRESSED:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DMC_USER_CONTROL_PRESSED(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_DMC_USER_CONTROL_RELEASED:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_DMC_USER_CONTROL_RELEASED(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- Remote Control Passthrough end -----------
    //----- UI Message end -----------


    //----- Power Status Support -----
        case E_MSG_PS_GIVE_DEVICE_POWER_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_PS_GIVE_DEVICE_POWER_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

      case E_MSG_PS_REPORT_POWER_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_PS_REPORT_POWER_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- Power Status Support end ---------


    //----- System Audio Control ---------
        case E_MSG_SAC_GIVE_AUDIO_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_GIVE_AUDIO_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SAC_REPORT_AUDIO_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_REPORT_AUDIO_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SAC_SET_SYSTEM_AUDIO_MODE:
            // support Directly addressed and Broadcast both
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                if (MApi_CEC_CheckFrame(E_TRANS_BROADCAST_MSG, 3) == 0)
                {
                    CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_SET_SYSTEM_AUDIO_MODE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                    bCheckFrameOK = FALSE;
                }
            }
            break;

        case E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 3) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_SAC_SET_AUDIO_RATE:
            if (0)//MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, ) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_SET_AUDIO_RATE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- System Audio Control end ---------

    //----- Audio Return Channel Support ---------
        case E_MSG_ARC_INITIATE_ARC:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ARC_INITIATE_ARC(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_ARC_REPORT_ARC_INITIATED:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ARC_REPORT_ARC_INITIATED(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_ARC_REPORT_ARC_TERMINATED:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ARC_REPORT_ARC_TERMINATED(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_ARC_REQUEST_ARC_INITIATION:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ARC_REQUEST_ARC_INITIATION(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_ARC_REQUEST_ARC_TERMINATION:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ARC_REQUEST_ARC_TERMINATION(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        case E_MSG_ARC_TERMINATE_ARC:
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ARC_TERMINATE_ARC(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

      #if (ENABLE_DOLBY_BULLETIN24)
        case E_MSG_SAC_REPORT_SHORT_AUDIO_DESCRIPTOR:
            if ((MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 5) == 0)
                ||(MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 8) == 0)
                ||(MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 11) == 0)
                ||(MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 14) == 0)
                )
            {
                break;
            }
            CEC_ERROR_DEBUG("[CEC] E_MSG_SAC_REPORT_SHORT_AUDIO_DESCRIPTOR(0x%x) Frame Fail \n", stCecMsg.u8opcode);
            bCheckFrameOK = FALSE;
            break;
      #endif
    //----- Audio Return Channel Support end ---------


    //----- General Protocal Message -----
        //----- Feature Abort ----------------
        case E_MSG_FEATURE_ABORT:     //[DA],
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 4) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_FEATURE_ABORT(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;

        //----- Abort Message ----------------
        case E_MSG_ABORT_MESSAGE: //same as default, for testing
            if (MApi_CEC_CheckFrame(E_TRANS_DIRECT_MSG, 2) == 0)
            {
                CEC_ERROR_DEBUG("[CEC] E_MSG_ABORT_MESSAGE(0x%x) Frame Fail \n", stCecMsg.u8opcode);
                bCheckFrameOK = FALSE;
            }
            break;
    //----- General Protocal Message end -----


        default:    //not support stCecMsg.u8opcode
            CEC_ERROR_DEBUG("[CEC] Not Support stCecMsg.u8opcode(0x%x) \n", stCecMsg.u8opcode);
            bCheckFrameOK = FALSE;
            break;
    }

    return bCheckFrameOK;
}

static void msCecProcessRxCmdCore(ST_CEC_MSG stCecMsg)
{
    MS_U8 header, len;
    MsCEC_MSGLIST opcode;
    MsCEC_DEVICELA enDevice, enDeviceDst;
    MS_U8 para0 = 0, para1 = 0, para2 = 0, para3 = 0;

    //*************************************************************************

    header      = stCecMsg.u8header;
    opcode      = (MsCEC_MSGLIST) stCecMsg.u8opcode;
    len         = stCecMsg.u8MsgLen;
    enDevice    = (MsCEC_DEVICELA)((stCecMsg.u8header & 0xF0)>>4);
    enDeviceDst = (MsCEC_DEVICELA) (stCecMsg.u8header & 0x0F);
    if (len>2)  para0  = stCecMsg.u8Para[0];
    if (len>3)  para1  = stCecMsg.u8Para[1];
    if (len>4)  para2  = stCecMsg.u8Para[2];
    if (len>5)  para3  = stCecMsg.u8Para[3];


    //*************************************************************************
    msCecDbgRxCmd(stCecMsg);


    if (msAPI_CEC_IsDeviceExist(enDevice) == FALSE )
    {
        if (E_MSG_ABORT_MESSAGE != opcode )
        {
            msCecAddDevice(enDevice, FALSE);
        }
    }


    switch (opcode)      //CEC1.3a Table 7 ~ 27
    {
    //----- One Touch Play ---------------
        case E_MSG_OTP_IMAGE_VIEW_ON:     //if in standby, firstly power on
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msCecSetActiveDevice(enDevice);

            // <Image View On>: Shoud not change TV menu or PIP status.
            break;
        }

        case E_MSG_OTP_TEXT_VIEW_ON:      //if in standby, firstly power on
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msCecSetActiveDevice(enDevice);  // anvi cec

            // <Text View On>: Should remove PIPs and menus form the screen.
            u8KeyCode = KEY_EXIT;

          #if ENABLE_ATSC
            if ( !msCecIsByPassCommand() )
            {
                MApp_ClosedCaption_Exit();
                MApp_ZUI_ACT_ShutdownOSD();
              #if ENABLE_DMP
                if( IsStorageInUse())
                {
                    MApp_DMP_Exit();
                }
              #endif
            }
          #endif
            break;
        }
    //----- One Touch Play end ---------------

    //----- One Touch Play --------------
    //----- Routing Control --------------
        case E_MSG_ACTIVE_SOURCE:
        {
            MS_U8 port = HIGHNIBBLE(stCecMsg.u8Para[0]&0xF0);
            MS_U16 u16PhyAddr, u16OldActivePhyAddr, u16AMPhyAddr;

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            if (msCecIsByPassCommand())
            {
                CEC_DPUTSTR("Active source cmd is cec-by-pass\n");
                break;
            }

            u16PhyAddr = (stCecMsg.u8Para[0] << 8) | stCecMsg.u8Para[1];
            u16OldActivePhyAddr = msAPI_CEC_GetActivePhyAddr();

            /***********************
            If <Active Source> is received, then this processing is finished
            ***********************/
            if ( _stCecStateInfoList.stState_DeviceDetect.enState ==
                    CEC_DEVICE_DETECT_WAIT_ACTIVE_SOURCE)
            {
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_PROCESS_FINISH;
            }

            msAPI_CEC_SetPowerStatus(enDevice, E_MSG_PWRSTA_ON);

            msCecSetActiveDevice(enDevice);  // anvi cec start
            msAPI_CEC_SetActivePhyAddr(u16PhyAddr);
            _stMsApiCecInfoList.u8ActiveSourceAddress[0] = stCecMsg.u8Para[0] ;
            _stMsApiCecInfoList.u8ActiveSourceAddress[1] = stCecMsg.u8Para[1] ;
            _stMsApiCecInfoList.u16ActiveSourceAddress = u16PhyAddr;

            CEC_DPRINTF(" switch into HDMI%d \n", port);
            msCecInputSourceSwitchHDMI((E_UI_INPUT_SOURCE)(UI_INPUT_SOURCE_HDMI + port - 1));

            /*
            CEC compliance test 11.1.15-1: sends a correctly formateed <System Audio Mode Request> message.
            */
            if (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
            {
                if ( msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) )
                {
                    u16AMPhyAddr = msAPI_CEC_GetDeviceIdx_PhyAddr(E_LA_AUDIO_SYS);
                    //_stMsApiCecInfoList.AMPPort = HIGHNIBBLE(stCecMsg.u8Para[0]&0xF0) ;
                    if ( (u16AMPhyAddr & 0xF000) == (MS_U16)((stCecMsg.u8Para[0]<<8) & 0xF000 ) )
                    {
                      #if ARC_PATCH_FOR_CHINA
                        if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
                        {
                            // UnMute AMP
                            CEC_PR(printf("\n\r msAPI_CEC_PostMsg_SystemAudioModeReq %s : %d",__FILE__,__LINE__));
                            //msAPI_CEC_PostMsg_SystemAudioModeReq(DIRECTMSG, (MS_U16)((stCecMsg.u8Para[0]<<8)|stCecMsg.u8Para[1]));
                            msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, TRUE);
                        }
                      #else
                        //msAPI_CEC_PostMsg_SystemAudioModeReq(DIRECTMSG, (MS_U16)((stCecMsg.u8Para[0]<<8)|stCecMsg.u8Para[1]));
                        msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, TRUE);
                      #endif
                    }
                }
            }

            /*
            sometimes AMP will send Active source to TV
            however, DVD is directly connected with AMP, DVD should be the active one.
            so we resend Routing Change again, AMP should reply Routing Information
            with the correct information of active physcial address
            */
            if (enDevice == E_LA_AUDIO_SYS)
            {
                U8 orig_phyaddress[2], new_phyaddress[2];

                orig_phyaddress[0] = 0x00;
                orig_phyaddress[1] = 0x00;

                new_phyaddress[0] = para0;
                new_phyaddress[1] = para1;

                msAPI_CEC_PostMsg_RoutingChange(POSTMSG, orig_phyaddress, new_phyaddress);
            }

            break;
        }
    //----- One Touch Play end --------------
    //----- Routing Control end --------------

    //----- Routing Control --------------
        case E_MSG_RC_INACTIVE_SOURCE:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            //broadcast, addressed, no para
            //cec anvi
            //VL++
            //_stCecApiInfo.ActivePhysicalAddress[0] = 0x0 ;
            //_stCecApiInfo.ActivePhysicalAddress[1] = 0x0 ;
            CEC_DPRINTF(" =E_MSG_RC_INACTIVE_SOURCE=, PHY= 0x%bx \n", para0);
            CEC_DPRINTF(" 0x%bx\r\n", para1);
            break;
        }

        case E_MSG_RC_REQUEST_ACTIVE_SOURCE:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            if ( !IsHDMIInUse() )
            {
                MS_U8 au8TxBuf[2];

                au8TxBuf[0] = 0x00;
                au8TxBuf[1] = 0x00;

                msAPI_CEC_PostMsg_ActiveSource(POSTMSG, au8TxBuf);
            }
            break;
        }

        case E_MSG_RC_ROUTING_CHANGE:
        {
            MS_U8 u8port;
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            if ( !IsHDMIInUse() && (enDevice != E_LA_TV) )
            {
                MS_U8 au8TxBuf[2];

                au8TxBuf[0] = 0x00;
                au8TxBuf[1] = 0x00;

                msAPI_CEC_PostMsg_ActiveSource(POSTMSG, au8TxBuf);
            }

            u8port = stSystemInfo[MAIN_WINDOW].enInputSourceType - INPUT_SOURCE_HDMI + 1;

            if ( IsHDMIInUse() && (u8port == ((para2>>4)&0x0F)) )
            {
                _stMsApiCecInfoList.u8ActiveSourceAddress[0] = para2;
                _stMsApiCecInfoList.u8ActiveSourceAddress[1] = para3;
                _stMsApiCecInfoList.u16ActiveSourceAddress = (para2 << 8) | para3;
                _stMsApiCecInfoList.enActiveDeviceLA = GetActiveLogicalAddress();
            }

            break;
        }


        case E_MSG_RC_ROUTING_INFORMATION:
        {
            MS_U8 u8port, au8TxBuf[2];

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            u8port = stSystemInfo[MAIN_WINDOW].enInputSourceType - INPUT_SOURCE_HDMI + 1;

            if ( IsHDMIInUse() && (u8port == ((para0>>4)&0x0F)) )
            {
                _stMsApiCecInfoList.u8ActiveSourceAddress[0] = para0;
                _stMsApiCecInfoList.u8ActiveSourceAddress[1] = para1;
                _stMsApiCecInfoList.u16ActiveSourceAddress = (para0 << 8) | para1;
                _stMsApiCecInfoList.enActiveDeviceLA = GetActiveLogicalAddress();
            }

            if (msAPI_CEC_IsDeviceExist(enDevice) == TRUE)
            {
                au8TxBuf[0] = stCecMsg.u8Para[0];
                au8TxBuf[1] = stCecMsg.u8Para[1];

                //VL++ fix CTS 9.4-2
                msAPI_CEC_PostMsg_RoutingInformation(DIRECTMSG, au8TxBuf);
            }

            break;
        }

      #if 0 // not supported yet.
        case E_MSG_RC_SET_STREM_PATH:
        {
            CEC_DPRINTF("[CEC] E_MSG_RC_SET_STREM_PATH(0x%x) not Support \n", opcode);

            break;
        }
      #endif
    //----- Routing Control end --------------


    //----- Standby Command --------------
        case E_MSG_STANDBY:
        {
            MsCEC_MSG_POWER_STATUS_PARM enPowerStatus;

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            enPowerStatus = msAPI_CEC_GetPowerStatus(E_LA_TV);

            /*
            CEC compliance test 11.1.3-2: responds to broadcast <Standby> messages.
            CEC compliance test 11.1.3-3: responds to directed <Standby> messages.
            */
            if ( enPowerStatus == E_MSG_PWRSTA_ON )    //when power on, not standby
            {
                CEC_DPUTSTR(" =Standby= \n");
                u8KeyCode = KEY_POWER;
            }
            break;
        }
    //----- Standby Command end --------------


    //----- One Touch Record--------------
    #if ONE_TOUCH_RECORD_SUPPORT
        case E_MSG_OTR_RECORD_ON:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }

        case E_MSG_OTR_RECORD_OFF:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }

        case E_MSG_OTR_RECORD_STATUS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            CEC_DPRINTF(" = RECORD_STATUS %bd = \n", para0);

            switch(para0)
            {
                case E_MSG_RECORD_INFO_RECORDING_OWN_SOURCE:  // Recording currently selected source
                case E_MSG_RECORD_INFO_RECORDING_DIGITAL_SERVICE:  // Recording Digital Service
                    gCECRecordEnable = TRUE;
                    CEC_DPRINTF(" CEC recording source is = %bx \n", para0);
                    break;

                case E_MSG_RECORD_INFO_NO_RECORDING_DIGITAL_SERVICE:  // unable to record Digital Service, no suitable tuner.
            #if(HDMI_CEC_VERSION == CEC_VERSION_13a)
                case E_MSG_RECORD_INFO_NO_RECORDING_ANALOGUE_SERVICE:  // unable to record Analogue Service, no suitable tuner.
                case E_MSG_RECORD_INFO_NO_RECORDING_REQ_SERVICE:  // unable to select required service, Has suitable tuner, but the requested parameters are invalid or out of range for that tuner.
                case E_MSG_RECORD_INFO_NO_RECORDING_INVALID_EXTERNAL_PLUG_NUMBER:  // invalid External plug number
                case E_MSG_RECORD_INFO_NO_RECORDING_INVALID_EXTERNAL_PHYSICAL_ADDRESS:  // invalid External Physical Address
                case E_MSG_RECORD_INFO_NO_RECORDING_CA_NOT_SUPPORT:  // CA system not supported
                case E_MSG_RECORD_INFO_NO_RECORDING_CA_NO:  // No or Insufficient CA Entitlements
                case E_MSG_RECORD_INFO_NO_RECORDING_COPY_NEVER:  // Not allowed to copy source, source is ¡§copy never¡¨.
                case E_MSG_RECORD_INFO_NO_RECORDING_NO_FURTHER_COPY:  // No further copies allowed
                case E_MSG_RECORD_INFO_NO_RECORDING_NOT_ENOUGH_SPACE:  // not enough space available
                case E_MSG_RECORD_INFO_NO_RECORDING_PARENTAL_LOCK:  // Parental Lock On
            #endif
                case E_MSG_RECORD_INFO_NO_RECORDING_NO_MEDIA:  // no media
                case E_MSG_RECORD_INFO_NO_RECORDING_MEDIA_PROTECTED:  // media protected
                case E_MSG_RECORD_INFO_NO_RECORDING_NO_SOURCE:  // no source signal
                case E_MSG_RECORD_INFO_NO_RECORDING_OTHER_REASON:  // No recording ¡V other reason
                    gCECRecordEnable= FALSE;
                    CEC_DPRINTF(" CEC no recording, error code is = %bx \n", para0);
                    break;

                case E_MSG_RECORD_INFO_NO_RECORDING_ALREADY_RECORDING:  // already recording
                    gCECRecordEnable= TRUE;
                    CEC_DPRINTF(" CEC already recording, error code is = %bx \n", para0);
                    break;

                case E_MSG_RECORD_INFO_NO_RECORDING_PLAYING:  // Playing
                    gCECRecordEnable= FALSE;
                    CEC_DPRINTF(" CEC no recording, error code is = %bx \n", para0);
                    break;

                case E_MSG_RECORD_INFO_NO_RECORDING_MEDIA_PROBLEM:  // media problem
                    gCECRecordEnable= FALSE;
                    CEC_DPRINTF(" CEC no recording, error code is = %bx \n", para0);
                    break;

            #if(HDMI_CEC_VERSION == CEC_VERSION_13a)
                case E_MSG_RECORD_INFO_RECORDING_TERMINATED_NORMALLY:  // Recording terminated normally, can optionally be sent in response to a <Record Off> message.
                case E_MSG_RECORD_INFO_RECORDING_ALREADY_TERMINATED:  // Recording has already terminated, can optionally be sent in response to a <Record Off> message.
                    gCECRecordEnable= FALSE;
                    CEC_DPRINTF(" CEC recording terminated status is = %bx \n", para0);
                    break;
            #endif

                default:
                    CEC_DPRINTF(" CEC recording unknow state = %bx \n", para0);
                    break;
            }

            break;
        }

        // Initiate a recording using the <Record On> message, or send a <Feature Abort> [¡§Cannot provide source¡¨]
        // if the presently displayed source is not recordable.
        case E_MSG_OTR_RECORD_TV_SCREEN:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            MsAPI_CEC_Msg_RecordOn(MApi_CEC_GetActiveLogicalAddress(), E_MSG_RECORD_TYPE_OWN_SOURCE);

            break;
        }
    #endif // #if ONE_TOUCH_RECORD_SUPPORT
    //----- One Touch Record end --------------


    //----- Timer programmer -------------
    #if TIMER_PROGRAMMER_SUPPORT
        case E_MSG_TP_CLEAR_ANALOG_TIMER:
        case E_MSG_TP_CLEAR_ANALOGUE_TIMER:
        case E_MSG_TP_CLEAR_EXTERNAL_TIMER:
        case E_MSG_TP_SET_ANALOGUE_TIMER:
        case E_MSG_TP_SET_DIGITAL_TIMER:
        case E_MSG_TP_SET_EXTERNAL_TIMER:
        case E_MSG_TP_SET_TIMER_PROGRAM_TITLE:
        case E_MSG_TP_TIMER_CLEARD_STATUS:
        case E_MSG_TP_TIMER_STATUS:
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
    #endif // #if TIMER_PROGRAMMER_SUPPORT
    //----- Timer programmer end -------------


    //----- System Information -----------
    //----- Vendor Specific -----------
        case E_MSG_SI_CEC_VERSION:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msAPI_CEC_SetCecVersion(enDevice, stCecMsg.u8Para[0]);
            break;
        }

        case E_MSG_SI_GET_CEC_VERSION:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msAPI_CEC_PostMsg_CECVersion(DIRECTMSG, enDevice, _stMsApiCecInfoList.u8CECVersion[E_LA_TV]);
            break;
        }
    //----- System Information end -----------
    //----- Vendor Specific end -----------


    //----- System Information -----------
        case E_MSG_SI_GIVE_PHYSICAL_ADDRESS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msAPI_CEC_PostMsg_ReportPhysicalAddress(DIRECTMSG);
            break;
        }

        case E_MSG_SI_REPORT_PHYSICAL_ADDRESS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            if (_stMsApiCecInfoList.fCecFirstPollingFinish)
            {
                msAPI_CEC_CheckSamePhysicalAddr(para0, para1, para2, enDevice);

                if ( msAPI_CEC_CheckSameLogicalAddr(para0, para1, para2, enDevice) )
                {
                    if ( msAPI_CEC_GetActiveDevice() == enDevice )
                    {
                        msCecSetActiveDevice(E_LA_TV);
                    }
                }

                /***********************
                When TV detected that the new device is connected by receiving <Report Physical Address>,
                TV acquires the device information only from the detected device.
                ***********************/
                if ( (_stMsApiCecInfoList.State[enDevice] < E_STM_GIVE_PHY_ADDR)
                   ||(_stMsApiCecInfoList.u8PhysicalAddress[enDevice][0] != para0)
                   ||(_stMsApiCecInfoList.u8PhysicalAddress[enDevice][1] != para1)
                   ||(_stMsApiCecInfoList.enDeviceType[enDevice] != (MsCEC_DEVICE_TYPE)para2)
                   )
                {
                    CEC_MSG( printf("\e[31;1;42m[CEC] trigger Device Detect for LA: %X \033[0m \n", (int)enDevice) );

                    _stCecStateInfoList.stState_DeviceDetect.enDstDeviceLA        = enDevice;
                    _stCecStateInfoList.stState_DeviceDetect.MyPhysicalAddress[0] = para0 ;
                    _stCecStateInfoList.stState_DeviceDetect.MyPhysicalAddress[1] = para1 ;

                    _stMsApiCecInfoList.State[enDevice] = E_STM_GIVE_PHY_ADDR ;
                }
            }
            else
            {
                if (_stMsApiCecInfoList.State[enDevice] == E_STM_REPORT_PHY_ADDR)
                {
                    _stMsApiCecInfoList.State[enDevice] = E_STM_GIVE_DEV_VENDOR_ID;
                }
            }

            msAPI_CEC_SetDeviceIdx_PhyAddr(enDevice,
                    (U16)((stCecMsg.u8Para[0]<<8) | stCecMsg.u8Para[1]));

            msAPI_CEC_SetDeviceType(enDevice, (MsCEC_DEVICE_TYPE)stCecMsg.u8Para[2]);

            CEC_MSG( printf("[CEC] DeviceLA = 0x%X, State = %d, DeviceType = %d \n",  \
                                 enDevice, _stMsApiCecInfoList.State[enDevice],       \
                                 _stMsApiCecInfoList.enDeviceType[enDevice]) );

            CEC_MSG( printf("      PhysicalAddress = [%02X, %02X],  \n",        \
                            _stMsApiCecInfoList.u8PhysicalAddress[enDevice][0], \
                            _stMsApiCecInfoList.u8PhysicalAddress[enDevice][1]) );

            if( enDevice == E_LA_AUDIO_SYS )
            {
                MS_U8 port = HIGHNIBBLE(stCecMsg.u8Para[0]&0xF0);

                _stMsApiCecInfoList.AMPPort = (port) ;
                CEC_MSG( printf("\e[31;1m[CEC] AMPPort = %d \033[0m \n", _stMsApiCecInfoList.AMPPort) );
            }

          #if 0
            if ( (enDevice != E_LA_BROADCAST))
            {
              #if VENDOR_SPECIFIC_SUPPORT
                msAPI_CEC_PostMsg_GiveDeviceVendorID(DIRECTMSG, enDevice);
              #endif

              #if (SYSTEM_INFORMATION_SUPPORT | VENDOR_SPECIFIC_SUPPORT)
                msAPI_CEC_PostMsg_GetCECVersion(DIRECTMSG, enDevice);
              #endif

              #if DEVICE_OSD_NAME_TRANSFER_SUPPORT
                msAPI_CEC_PostMsg_GiveOSDName(DIRECTMSG, enDevice);
              #endif
            }
          #endif

          #if 0
            /*
            CEC compliance test 11.1.15-4: issues a <Give System Audio Mode Status> message to the amplifier.
            */
            if ( (enDevice == E_LA_AUDIO_SYS)
               &&(stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
               )
            {
                msAPI_CEC_PostMsg_GiveSystemAudioModeStatus(POSTMSG, E_LA_AUDIO_SYS);
            }
          #endif

            /*
            CEC compliance test 11.1.15-5: respond with <System Audio Mode Request> message to the amplifier.
            */
            if ( (enDevice == E_LA_AUDIO_SYS)
               &&(stGenSetting.stHDMISetting.g_enHDMIARC == DISABLE)
               )
            {
                //msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(POSTMSG);
                msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
            }

            break;
        }

        case E_MSG_SI_GET_MENU_LANGUAGE:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            /*
               fixed 11.1.6-5 Ensure that the DUT responds correctly to a <Get Menu Language> message
               with a different version number to that it holds, coming from various logical addresses
               including the unregistered address.
            */

            EN_LANGUAGE eLanguage;
            U8 u8CecLangCode[MAX_ISO639CODE_LENGTH] = { 0 };

            eLanguage = MApp_GetMenuLanguage();

            if ( MApp_GetOSDLangCodeFromIndex(eLanguage, u8CecLangCode) == TRUE)
            {
                msAPI_CEC_PostMsg_SetMenuLang(DIRECTMSG, u8CecLangCode);
            }

            break;
        }

        case E_MSG_SI_SET_MENU_LANGUAGE:
        {
            break;
        }

      #if 0 // not supported yet.
        case E_MSG_SI_POLLING_MESSAGE:
                break;
      #endif
    //----- System Information end -----------


    //----- Deck Control Feature----------
    #if DECK_CONTROL_SUPPORT
        case E_MSG_DC_DECK_STATUS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            gCECDeckStatus = (MsCEC_MSG_DC_DECK_STATUS_PARM) stCecMsg.u8Para[0];

            break;
        }

        case E_MSG_DC_DECK_CONTROL:
        case E_MSG_DC_GIVE_DECK_STATUS:
        case E_MSG_DC_PLAY:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }
    #endif
    //----- Deck Control end -----------


    //----- Tuner Control ----------------
    #if TUNER_CONTROL_SUPPORT
        case E_MSG_TC_GIVE_TUNER_DEVICE_STATUS:
        case E_MSG_TC_SEL_ANALOGUE_SERVICE:
        case E_MSG_TC_SELECT_DIGITAL_SERVICE:
        case E_MSG_TC_TUNER_DEVICE_STATUS:
        case E_MSG_TC_TUNER_STEP_DECREMENT:
        case E_MSG_TC_TUNER_STEP_INCREMENT:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }
    #endif
    //----- Tuner Control end -----------


    //---------Vendor Specific -----------
        case E_MSG_VS_DEVICE_VENDOR_ID:
        {
            MS_U8 txbuf[3];

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            txbuf[0] = stCecMsg.u8Para[0];
            txbuf[1] = stCecMsg.u8Para[1];
            txbuf[2] = stCecMsg.u8Para[2];

            msAPI_CEC_SetDeviceVendorID(enDevice, txbuf);
            break;
        }

        case E_MSG_VS_GIVE_DEVICE_VENDOR_ID:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msAPI_CEC_PostMsg_DeviceVendorID(DIRECTMSG, enDeviceDst);
            break;
        }

        case E_MSG_VS_VENDOR_COMMAND:
        case E_MSG_VS_VENDOR_COMMAND_WITH_ID:
        case E_MSG_VS_VENDOR_REMOTE_BUTTON_DOWN:
        case E_MSG_VS_VENDOR_REMOTE_BUTTON_UP:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }
    //----- Vendor Specific end -----------


    //----- OSD Display ------------------
    #if OSD_DISPLAY_SUPPORT
        case E_MSG_SET_OSD_STRING:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }
    #endif
    //----- OSD Display end -----------


    //----- Device OSD Name Transfer  ----
        case E_MSG_OSDNT_GIVE_OSD_NAME:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msAPI_CEC_PostMsg_SetOSDName(DIRECTMSG, enDevice);
            break;
        }

        case E_MSG_OSDNT_SET_OSD_NAME:
        {
            U8 u8NameLen, au8StringBuffer[13];

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            memset(&au8StringBuffer, 0x00, 13);

            if(len> 2 && para0!=0)
            {
                for(u8NameLen=0;u8NameLen<(len-2);u8NameLen++)
                {
                    au8StringBuffer[u8NameLen] = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), u8NameLen+2);
                }
                au8StringBuffer[u8NameLen]= '\0';

                CEC_MSG( printf("Device Name: %s \n", au8StringBuffer) );

                msAPI_CEC_SetDeviceName(enDevice, (U8*)&au8StringBuffer, FALSE);
            }
            else
            {
                msAPI_CEC_SetDeviceName(enDevice, NULL, TRUE);
            }

            break;
        }
    //----- Device OSD Name Transfer end -----------


    //----- Device Menu Control ----------
    #if DEVICE_MENU_CONTROL_SUPPORT
//        case E_MSG_DMC_MENU_REQUEST:
//            break;

        case E_MSG_DMC_MENU_STATUS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

          #if 1
            /*
               CEC Table 27 Message dependencies when receiving a message
               If device does not <Feature Abort> "Unrecognized opcode" with <Menu Request>
               It shall not <Feature Abort> "Unrecognized opcode" with
                <User Control Pressed> and <User Control Released>
            */
            gCECUserControlEnable = TRUE;
            gCECGetMenuStatusMsg = TRUE;

            if(para0 == E_MSG_MENU_ACTIVATED)
            {
                gCECMenuControlEnable = TRUE;
            }
            else
                gCECMenuControlEnable = FALSE;
          #else
            switch(para0)
            {
                case E_MSG_MENU_ACTIVATED:
                    gCECUserControlEnable = TRUE;
                    break;
                case E_MSG_MENU_DEACTIVATED:
                    gCECUserControlEnable = FALSE;
                    break;
            }
          #endif
            break;
        }
    #endif
    //----- Device Menu Control end -----------


    //----- Remote Control Passthrough ---
    //----- UI Message -------------------
        case E_MSG_DMC_USER_CONTROL_PRESSED:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            CEC_DPRINTF(" = UI_Press (0x%x) = \n", para0);

            switch(para0)   //UI command
            {
                case E_MSG_UI_SUB_PICTURE:  //PIP
                  #if (IR_TYPE_SEL != IR_TYPE_CUS21SH)
                    IR_CODE = IRKEY_PICTURE;
                    g_bIrDetect = TRUE;
                  #endif
                    break;

                case E_MSG_UI_LEFT:
                    IR_CODE = IRKEY_LEFT;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_UP:
                    IR_CODE = IRKEY_UP;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_ROOTMENU:
                    IR_CODE = IRKEY_MENU;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_DOWN:
                    IR_CODE = IRKEY_DOWN;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_RIGHT:
                    IR_CODE = IRKEY_RIGHT;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_SELECT:
                    IR_CODE = IRKEY_INPUT_SOURCE;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_POWER:
                case E_MSG_UI_POWER_ON_FUN:               //Panasonic DVD-S53 think only as power on
                    CEC_DPRINTF(" =E_MSG_UI_POWER= %bd \n", MApi_CEC_GetPowerStatus());
                    if(MApi_CEC_GetPowerStatus() == E_MSG_PWRSTA_STANDBY)
                    {
                        IR_CODE = IRKEY_POWER;
                        g_bIrDetect = TRUE;
                    }
                    break;

                case E_MSG_UI_NUMBER_0:
                    IR_CODE = IRKEY_NUM_0;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_1:
                    IR_CODE = IRKEY_NUM_1;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_2:
                    IR_CODE = IRKEY_NUM_2;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_3:
                    IR_CODE = IRKEY_NUM_3;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_4:
                    IR_CODE = IRKEY_NUM_4;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_5:
                    IR_CODE = IRKEY_NUM_5;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_6:
                    IR_CODE = IRKEY_NUM_6;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_7:
                    IR_CODE = IRKEY_NUM_7;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_8:
                    IR_CODE = IRKEY_NUM_8;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_NUMBER_9:
                    IR_CODE = IRKEY_NUM_9;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_DISPLAY_INFO:
                    IR_CODE = IRKEY_INFO;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_MUTE:
                    IR_CODE = IRKEY_MUTE;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_VOLUME_UP:
                    IR_CODE = IRKEY_VOLUME_PLUS;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_VOLUME_DOWN:
                    IR_CODE = IRKEY_VOLUME_MINUS;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_CHANNEL_UP:
                    IR_CODE = IRKEY_CHANNEL_PLUS;
                    g_bIrDetect = TRUE;
                    break;

                case E_MSG_UI_CHANNEL_DOWN:
                    IR_CODE = IRKEY_CHANNEL_MINUS;
                    g_bIrDetect = TRUE;
                    break;

                default:    //UI command, no support parameter,need abort a reason, REFUSED reason, or ignore
                    IR_CODE = IRKEY_DUMY;
                    g_bIrDetect = TRUE;
                    msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, MApi_CEC_GetActiveLogicalAddress(), opcode, E_MSG_AR_REFUSED);
                    break;
            }

            break;
        }

        case E_MSG_DMC_USER_CONTROL_RELEASED:
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
    //----- Remote Control Passthrough end -----------
    //----- UI Message end -----------


    //----- Power Status Support -----
        case E_MSG_PS_GIVE_DEVICE_POWER_STATUS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msAPI_CEC_PostMsg_ReportPowerStatus(DIRECTMSG, enDevice, msAPI_CEC_GetPowerStatus(E_LA_TV));
            break;
        }

        case E_MSG_PS_REPORT_POWER_STATUS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msAPI_CEC_SetPowerStatus(enDevice, (MsCEC_MSG_POWER_STATUS_PARM) para0);

            if (para0 < (U8)E_MSG_PWRSTA_UNKNOW)
            {
                /***********************
                When <Report Power Status> is received :
                - If [Power Status] is "On", then TV sends <Set Stream Path> with physical address of
                  the connected device.
                - If [Power State] is "Standby", "In transition Standby to On" or "In transition On to Standby",
                  then TV executes <Give Device Power Status> re-send processing (Refer to 6.13.2.6).
                - If [Power Status] is "On" after re-send processing, TV sends <Set Stream Path> with
                  physical address of the connected device.
                - If [Power Status] is "Standby", "In transition Standby to On" or "In transition On to Standby"
                  after re-send processing, TV should not send <Set Stream Path>.
                ***********************/
                if (_stCecStateInfoList.stState_DeviceDetect.enState ==
                        CEC_DEVICE_DETECT_WAIT_REPORT_POWER_STATUS)
                {
                    if ( (MsCEC_MSG_POWER_STATUS_PARM) para0 == E_MSG_PWRSTA_ON)
                    {
                        _stCecStateInfoList.stState_DeviceDetect.enState =
                            CEC_DEVICE_DETECT_SEND_STREAM_PATH;
                    }
                    else
                    {
                        _stCecStateInfoList.stState_DeviceDetect.enDstDeviceLA = enDevice;

                        _stCecStateInfoList.stState_DeviceDetect.enState =
                            CEC_DEVICE_DETECT_GIVE_DEVICE_POWER_STATUS_RETRANSMISSION;
                    }
                }
            }

            break;
        }
    //----- Power Status Support end ---------


    //----- System Audio Control ---------
        case E_MSG_SAC_GIVE_AUDIO_STATUS:
        case E_MSG_SAC_GIVE_SYSTEM_AUDIO_MODE_STATUS:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            if (stGenSetting.g_SoundSetting.TVspeakerMode != TVspeaker_Mode_ExtAmp)
            {
                if (enDeviceDst != E_LA_BROADCAST) // broadcast will not respond feature abort
                {
                    msCecProcessGeneralProtocolMessage(enDevice, opcode);
                }
            }

            break;
        }


        case E_MSG_SAC_REPORT_AUDIO_STATUS:
        {
            MS_U8 u8AudioMute;
            MS_U8 u8AudioVolumeLevel;

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            u8AudioMute        = para0 & 0x80;
            u8AudioVolumeLevel = para0 & 0x7F;
            CEC_DPRINTF(" Audio Mute %s,", (u8AudioMute)?("On"):("Off"));
            CEC_DPRINTF(" Volume level: %d% \n", u8AudioVolumeLevel);
            ARCAudioVolume = u8AudioVolumeLevel;
            ARCAMPIsMute = (u8AudioMute)?TRUE:FALSE;

            if (stGenSetting.g_SoundSetting.TVspeakerMode != TVspeaker_Mode_ExtAmp)
            {
                CEC_DPUTSTR(" Ignored \n"); // ignored message
                break;
            }
            else
            {
              #if ARC_COMMAND_ONLY_IF_AMP_IN_CORRECT_PORT
              if ( (MApp_CEC_CheckDeviceValidForARC()   == FALSE)   // AMP is NOT connected with HDMI port which supports ARC
                 ||(MApp_CEC_IsAdjacentARCDeviceExist() == FALSE)   // AMP is NOT connected with validate HDMI port (x.0.0.0)
                 ||(stGenSetting.stHDMISetting.g_enHDMIARC == FALSE)) // If ARC off,Adjust AMP Vol should not control TV Spekear, mantis: 1088264
                {
                    CEC_DPUTSTR(" Ignored: AMP in wrong ARC port \n"); // ignored message
                    break;
                }
              #endif
            }

            if (u8KeyCode == KEY_NULL && !ARCAMPIsMute)
            {
                u8KeyCode = KEY_VOLUME_MINUS;   //assign a key in order to draw volume OSD, mantis: 0794921
            }

            msAPI_CEC_SaveAmpControlVolume(para0);
            break;
        }


        case E_MSG_SAC_SET_SYSTEM_AUDIO_MODE:
        {
            BOOLEAN bAudioMode;

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            bAudioMode = (para0 & 0x01);
            CEC_DPRINTF(" Sys. Aduio Status: %s \n", (bAudioMode)?("On"):("Off"));

            if (stGenSetting.g_SoundSetting.TVspeakerMode != TVspeaker_Mode_ExtAmp)
            {
                if (enDeviceDst == E_LA_BROADCAST)
                {
                    if (bAudioMode == 1)
                    {
                        // Terminate System Audio Mode because "Speaker Mode" is not "ExtAmp"
                        //msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(POSTMSG);
                        msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
                    }
                    CEC_DPUTSTR(" Ignored \n"); // ignored message
                }
                else
                {
                    msCecProcessGeneralProtocolMessage(enDevice, opcode);
                }
                msAPI_CEC_SetSystemAudioMode(FALSE);
                break;
            }
            else
            {

              #if ARC_COMMAND_ONLY_IF_AMP_IN_CORRECT_PORT
                if (//11.1.15 - 2 audio mode did not check the arc (MApp_CEC_CheckDeviceValidForARC()   == FALSE) ||  // AMP is NOT connected with HDMI port which supports ARC
                   (MApp_CEC_IsAdjacentARCDeviceExist() == FALSE) ) // AMP is NOT connected with validate HDMI port (x.0.0.0)
                {
                    CEC_DPUTSTR(" Ignored: AMP in wrong ARC port \n"); // ignored message
                    msAPI_CEC_SetSystemAudioMode(FALSE);
                    break;
                }
              #endif
            }

          #if ARC_PATCH_FOR_CHINA
            if ( (stGenSetting.stHDMISetting.g_enHDMIARC == DISABLE)
               && (bAudioMode == TRUE))
            {
                CEC_MSG( printf("[CEC] ARC: Off => Request to turn off System Audio Mode \n") );
                //msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(DIRECTMSG);
                msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
                break;
            }
          #endif

            msAPI_CEC_SetSystemAudioMode(bAudioMode);

            if (bAudioMode)//Amp
            {
                msAPI_CEC_SetSystemMute();
            }
            else//TV
            {
                msAPI_CEC_SetSystemUnMute();
            }

            if (bAudioMode != msAPI_CEC_QuerySystemAudioMode())
            {
                msAPI_CEC_PostMsg_GiveAudioStatus(POSTMSG, E_LA_AUDIO_SYS);
            }


            if (_stCecStateInfoList.stState_DeviceDetect.enState ==
                    CEC_DEVICE_DETECT_WAIT_SYSTEM_AUDIO_MODE_STATUS)
            {
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_REQUEST_SHORT_AUDIO_DESCRIPTOR;
            }

            break;
        }

      #if 0 // not supported yet.
        case E_MSG_SAC_SYSTEM_AUDIO_MODE_REQUEST:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }
      #endif

        case E_MSG_SAC_SYSTEM_AUDIO_MODE_STATUS:
        {
            BOOLEAN bAudioMode;

            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            bAudioMode = (para0 & 0x01);
            CEC_DPRINTF(" Sys. Aduio Status: %s \n", (bAudioMode)?("On"):("Off"));

            if (stGenSetting.g_SoundSetting.TVspeakerMode != TVspeaker_Mode_ExtAmp)
            {
                CEC_DPUTSTR(" Ignored \n"); // ignored message
                msAPI_CEC_SetSystemAudioMode(FALSE);
                break;
            }
            else
            {
              #if ARC_COMMAND_ONLY_IF_AMP_IN_CORRECT_PORT
                if (//11.1.15 - 2 audio mode did not check the arc (MApp_CEC_CheckDeviceValidForARC()   == FALSE)  || // AMP is NOT connected with HDMI port which supports ARC
                    (MApp_CEC_IsAdjacentARCDeviceExist() == FALSE) ) // AMP is NOT connected with validate HDMI port (x.0.0.0)
                {
                    CEC_DPUTSTR(" Ignored: AMP in wrong ARC port \n"); // ignored message
                    msAPI_CEC_SetSystemAudioMode(FALSE);
                    break;
                }
              #endif
            }

          #if ARC_PATCH_FOR_CHINA
            if ( (stGenSetting.stHDMISetting.g_enHDMIARC == DISABLE)
               && (bAudioMode == TRUE))
            {
                CEC_MSG( printf("[CEC] ARC: Off => Request to turn off System Audio Mode \n") );
                //msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(DIRECTMSG);
                msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
                break;
            }
          #endif

            msAPI_CEC_SetSystemAudioMode(bAudioMode);

            if (bAudioMode)   //Amp
            {
                msAPI_CEC_SetSystemMute();
            }
            else//TV
            {
                msAPI_CEC_SetSystemUnMute();
            }

            if (_stCecStateInfoList.stState_DeviceDetect.enState ==
                    CEC_DEVICE_DETECT_WAIT_SYSTEM_AUDIO_MODE_STATUS)
            {
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_REQUEST_SHORT_AUDIO_DESCRIPTOR;
            }

            break;
        }

      #if 0 // not supported yet.
        case E_MSG_SAC_SET_AUDIO_RATE:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );
            break;
        }
      #endif

      #if (ENABLE_DOLBY_BULLETIN24)
        case E_MSG_SAC_REPORT_SHORT_AUDIO_DESCRIPTOR:
        {
            if (_stCecStateInfoList.stState_DeviceDetect.enState ==
                    CEC_DEVICE_DETECT_WAIT_REPORT_SHORT_ADUIO_DESCRIPTOR)
            {
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_REQUEST_ARC_INITIATION;
            }

            #define MAX_SAD_LEN 12
            U8 u8SADBuffer[MAX_SAD_LEN];

            memset(u8SADBuffer, 0x00, MAX_SAD_LEN);

            if(len> 2 && para0!=0)
            {
                U8 idx = 0;
                for(idx=2;idx<len;idx++)
                {
                    u8SADBuffer[idx-2] = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), idx);
                }
                msAPI_DolbyBulletin24_receive_SAD(u8SADBuffer, (len-2));
            }
        }
        break;
      #endif
    //----- System Audio Control end ---------


    //----- Audio Return Channel Support ---------
        case E_MSG_ARC_INITIATE_ARC:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            if (enDevice != E_LA_AUDIO_SYS)
            {
                CEC_MSG( printf("[CEC] Not E_LA_AUDIO_SYS\n") );
                break;
            }

            /***********************
            ARC: Off
            PA: x.x.x.x => <Feature Abort> ["Unrecognized Opcode"]

            ARC: On
            PA: ARC.0.0.0 => OK
                ARC.x.0.0 => <Feature Abort>["Refused"]
                          => <Request ARC Termination>
            ***********************/
            if (stGenSetting.stHDMISetting.g_enHDMIARC == DISABLE)
            {
                CEC_MSG( printf("[CEC] ARC: Off => <Feature Abort> [Unrecognized Opcode] \n") );
                msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, E_LA_AUDIO_SYS, opcode, E_MSG_AR_UNRECOGNIZE_OPCDE);
                msCecSetARCStatus(FALSE);
              #if (ARC_PATCH_FOR_CHINA)
                msAPI_CEC_SetSystemUnMute();
                msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
              #endif
                break;
            }
            else
            {
                if (MApp_CEC_CheckDeviceValidForARC() == FALSE)
                {
                    CEC_MSG( printf("[CEC] AUDIO is not in ARC port \n") );
                    msAPI_CEC_PostMsg_RequestARCTermination(DIRECTMSG, E_LA_AUDIO_SYS);
                    msCecSetARCStatus(FALSE);
                    break;
                }
                else if ( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)     // AMP is in ARC port
                        &&(MApp_CEC_IsAdjacentARCDeviceExist() == FALSE) )  // validate port
                {
                    CEC_MSG( printf("[CEC] Non-adjacent ARC device exist [Refused] \n") );
                    msCecSetARCStatus(FALSE);
                    msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, E_LA_AUDIO_SYS, opcode, E_MSG_AR_REFUSED);
                    break;
                }

              #if (ARC_PATCH_FOR_CHINA)
                if ( IsHDMIInUse())
                {
                    U8  port = SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) - INPUT_SOURCE_HDMI + 1;
                    U16 u16AMPPhyAddr = msAPI_CEC_GetDeviceIdx_PhyAddr(E_LA_AUDIO_SYS);

                    if ( (u16AMPPhyAddr & 0xF000) == (port * 0x1000) )
                    {
                        CEC_ARC_INFO( printf("[CEC] DVD-AMP => [Refused] \n") );
                        msAPI_CEC_SetSystemMute();
                        msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG, E_LA_AUDIO_SYS, opcode, E_MSG_AR_REFUSED);
                        msCecSetARCStatus(FALSE);
                        break;
                    }
                }
              #endif
            }

            gIsCECAmpARCOn = TRUE;

            msCecSetARCStatus(TRUE);

            if ( _stCecStateInfoList.stState_ArcOff2On.enState ==
                 CEC_ARC_OFF2ON_WAIT_INITIATE_ARC )
            {
                _stCecStateInfoList.stState_ArcOff2On.enState =
                    CEC_ARC_OFF2ON_PROCESS_FINISH;
            }

            msAPI_CEC_PostMsg_ReportARCInitiated(DIRECTMSG, enDevice);
            msAPI_CEC_TxMsgSystemAudioModeRequest(DIRECTMSG, TRUE);
            break;
        }

        case E_MSG_ARC_TERMINATE_ARC:
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            //Power off ARC
            //ARC_CTRL_OFF();
            msCecSetARCStatus(FALSE);
            msAPI_CEC_SetSystemUnMute();

            if (stGenSetting.stHDMISetting.g_enHDMIARC == ENABLE)
            {
                stGenSetting.stHDMISetting.g_enHDMIARC = DISABLE;
            }
            gIsCECAmpARCOn = FALSE;

            msAPI_CEC_PostMsg_ReportARCTerminated(DIRECTMSG, enDevice);

            break;
        }
    //----- Audio Return Channel Support end ---------


    //----- General Protocal Message -----
        //----- Feature Abort ----------------
        case E_MSG_FEATURE_ABORT:     //[DA],
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            msCecFeatureAbortHandler(stCecMsg);
            break;
        }

        //----- Abort Message ----------------
        case E_MSG_ABORT_MESSAGE: //same as default, for testing
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

          #if 0 // no need, should be updated in CEC library
            /*
            CEC compliance test 9.7-1: waits for at least 5 bit periods
                                       before transmitting a new message.
            5 bit periods are about 12.0ms.
            */
            MsOS_DelayTask(5);
          #endif

            msCecProcessGeneralProtocolMessage(enDevice, opcode);

            break;
        }
    //----- General Protocal Message end -----


        default:    //not support opcode
        {
            CEC_MSG( printf("[%lu] %s(0x%x) \n", __LINE__, (char *)CEC_opCodeStr_Customer[opcode], opcode) );

            if (enDeviceDst != E_LA_BROADCAST)   // broadcast will not respond feature abort
            {
                msCecProcessGeneralProtocolMessage(enDevice, opcode);
            }

            break;
        }
    }//switch end

    msCecShowDeviceMap();
}

static void msCecProcessUnSupportCmd(ST_CEC_MSG stCecMsg)
{
    MsCEC_MSGLIST opcode    = (MsCEC_MSGLIST) stCecMsg.u8opcode;;
    MsCEC_DEVICELA enDevice = (MsCEC_DEVICELA)((stCecMsg.u8header & 0xF0)>>4);

    CEC_DPRINTF("[CEC] Not Support opCode(0x%x) \n", opcode);


    switch (opcode)      //CEC1.3a Table 7 ~ 27
    {
        //Fixed 9.5-1 Fail SYSTEM: The DUT shall not respond with <Feature Abort>.
        case E_MSG_OSDNT_SET_OSD_NAME:
        case E_MSG_OSDNT_GIVE_OSD_NAME:
            break;

        default:
            msAPI_CEC_PostMsg_FeatureAbort(DIRECTMSG,
                                           enDevice, opcode,
                                           E_MSG_AR_REFUSED);
            break;
    }
}

//**************************************************************************
//  [Function Name]:
//                   MsAPI_CECProcessCmd()
//  [Description]
//                   It used to parse CEC command
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msCecProcessRxCmd(void)
{
    ST_CEC_MSG stCecMsg;
    MS_U8 u8Fifoidx;
    MS_U8 i;

    //if (MApi_CEC_GetMsgCnt() == 0 ) return;  //no received message to process

    memset(&stCecMsg, 0, sizeof(stCecMsg));

    stCecMsg.u8header = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 0);
    stCecMsg.u8opcode = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 1);
    stCecMsg.u8MsgLen = MApi_CEC_GetCmdLen();
    for(i = 0; i<(stCecMsg.u8MsgLen-2); i++)
    {
        stCecMsg.u8Para[i] = MApi_CEC_GetRxData( MApi_CEC_GetFifoIdx(), 2+i);
    }

    msDebug_ANSI_SetColorText(E_FONT_COLOR_WHITE);
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_BLACK);
    printf("\n CEC RX < ");
    printf("%02X %02X ", (U8)stCecMsg.u8header, (U8)stCecMsg.u8opcode);
    for(i = 0; i<(stCecMsg.u8MsgLen-2); i++)
    {
        printf("%02X ", (U8)stCecMsg.u8Para[i]);
    }
    printf("> : %s \n", (char *)CEC_opCodeStr_Customer[stCecMsg.u8opcode]);
    msDebug_ANSI_AllAttrOffText();

    // 1st step: check Feature is supported or not
    if (msCecCheckFeatureSupport(stCecMsg.u8opcode) == TRUE)
    {
        // Check Frame is valid or not
        if ( msCecCheckMsgFrame(stCecMsg) )
        {
            msCecProcessRxCmdCore(stCecMsg);
        }
    }
    else
    {
        msCecProcessUnSupportCmd(stCecMsg);
    }

    //**************************************************************************

    u8Fifoidx = MApi_CEC_GetFifoIdx();

    if ( (u8Fifoidx+1) >= CEC_FIFO_CNT )
        MApi_CEC_SetFifoIdx(0);
    else
        MApi_CEC_SetFifoIdx(u8Fifoidx+1);

    MApi_CEC_SetMsgCnt(MApi_CEC_GetMsgCnt() - 1);

    CEC_DPUTSTR(" -------------------- \n");

}

static void msCecProcessTxMsg(void)
{
    static CECMSG _stCecMsg;
    static BOOLEAN _bCecTxChkStatus = FALSE;

    if (msAPI_CEC_GetMsgInQueue(&_stCecMsg))
    {
        CEC_ERROR_CODE res;

        res = msAPI_CEC_PostMsg(_stCecMsg.enDevice, _stCecMsg.enOpcode, _stCecMsg.au8Operand, _stCecMsg.u8Len);

        _bCecTxChkStatus = TRUE;

      #if 0 // can't just add/remove device, will cause some CEC compliance test fail.
        if (res & E_CEC_TX_SUCCESS)
        {
            msCecAddDevice(_stCecMsg.enDevice, FALSE);
        }
        else
        {
          #if CEC_DEBUG
            printf("TxMsg 0x%x ", _stCecMsg.enDevice);
            printf("with opCode 0x%x Fail \n", _stCecMsg.enOpcode);
          #endif

            msCecRemoveDevice(_stCecMsg.enDevice);
        }
      #endif
    }
}

//
//
/******************************************************************************/
//

static void msCecStateMachine_DeviceDetect(void)
{
    EN_CEC_STATE_DEVICE_DETECT enState = _stCecStateInfoList.stState_DeviceDetect.enState;
//    INPUT_SOURCE_TYPE_t eInput = stSystemInfo[MAIN_WINDOW].enInputSourceType;

    if ( enState == CEC_DEVICE_DETECT_IDLE )
        return;

    CEC_STATE_INFO( printf("\n\033[41;4m[CEC] %s \033[0m \n", (char *) CEC_Device_Detect_Str[enState]) );

  #if 0
    CEC_STATE_INFO( printf("      ActiveSourceAddress = 0x%04X \n",
            ((m_CECInfoExtend.ActiveSourceAddress[0]<<8)|m_CECInfoExtend.ActiveSourceAddress[1])) );
    CEC_STATE_INFO( printf("      MyPhysicalAddress   = 0x%04X \n",
            ((m_CECInfoExtend.MyPhysicalAddress[0]<<8)|m_CECInfoExtend.MyPhysicalAddress[1])) );
    CEC_STATE_INFO( printf("      6_1_1_2.Phy.Address = 0x%04X \n",
            ((m_CECFunaiStateInfoList.stFunaiState_6_1_1_2.MyPhysicalAddress[0]<<8)|m_CECFunaiStateInfoList.stFunaiState_6_1_1_2.MyPhysicalAddress[1])) );
  #endif

    switch (enState)
    {
        case CEC_DEVICE_DETECT_SEND_GIVE_SYSTEM_AUDIO_MODE_STATUS:
            _stCecStateInfoList.stState_DeviceDetect.enState =
                CEC_DEVICE_DETECT_WAIT_SYSTEM_AUDIO_MODE_STATUS;

            msAPI_CEC_PostMsg_GiveSystemAudioModeStatus(DIRECTMSG, E_LA_AUDIO_SYS);

            msCecSetStartTime(INTERVAL_CEC_FSM_DeviceDetect) ;
            break;

        case CEC_DEVICE_DETECT_WAIT_SYSTEM_AUDIO_MODE_STATUS:
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_DeviceDetect) > INTERVAL_1_SECOND )
            {
                CEC_STATE_INFO( printf("\033[41;4m              Over 1 second \033[0m \n") );

                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_REQUEST_SHORT_AUDIO_DESCRIPTOR;
            }
            break;

        case CEC_DEVICE_DETECT_SEND_REQUEST_SHORT_AUDIO_DESCRIPTOR:
            /* Audio system is connected with HDMI port which support ARC */
            if ( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
               &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
            {
              #if (ENABLE_DOLBY_BULLETIN24)
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_WAIT_REPORT_SHORT_ADUIO_DESCRIPTOR;

                msAPI_CEC_PostMsg_RequestShortAudioDescriptor(DIRECTMSG, E_LA_AUDIO_SYS);

                msCecSetStartTime(INTERVAL_CEC_FSM_DeviceDetect) ;
              #else
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_REQUEST_ARC_INITIATION;
              #endif
            }
            else
            {
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_PROCESS_FINISH;
            }
            break;

        case CEC_DEVICE_DETECT_WAIT_REPORT_SHORT_ADUIO_DESCRIPTOR:
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_DeviceDetect) > INTERVAL_1_SECOND )
            {
                CEC_STATE_INFO( printf("\033[41;4m              Over 1 second \033[0m \n") );

                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_REQUEST_ARC_INITIATION;
            }
            break;

        case CEC_DEVICE_DETECT_SEND_REQUEST_ARC_INITIATION:
            if ( stGenSetting.stHDMISetting.g_enHDMIARC == TRUE )
            {
              #if ARC_PATCH_FOR_CHINA
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_REQUEST_ACTIVE_SOURCE;

                SetArcOnBehavior();

              #else
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_WAIT_INITIATE_ARC;
                msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);

                msCecSetStartTime(INTERVAL_CEC_FSM_DeviceDetect) ;
              #endif
            }
            else
            {
              #if ARC_PATCH_FOR_CHINA
                CEC_ARC_INFO( printf("\e[31;1m Line: %d \33[m \n", __LINE__) );
                msAPI_CEC_SetSystemUnMute();
              #endif

                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_PROCESS_FINISH;
            }
            break;

        case CEC_DEVICE_DETECT_WAIT_INITIATE_ARC:
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_DeviceDetect) > INTERVAL_1_SECOND )
            {
                CEC_STATE_INFO( printf("\033[41;4m              Over 1 second \033[0m \n") );

                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_PROCESS_FINISH;
            }
            break;

        case CEC_DEVICE_DETECT_SEND_REQUEST_ACTIVE_SOURCE:
            if ( IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
            {
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_WAIT_ACTIVE_SOURCE;

                msAPI_CEC_PostMsg_RequestActiveSource(DIRECTMSG);

                msCecSetStartTime(INTERVAL_CEC_FSM_DeviceDetect) ;
            }
            else
            {
                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_PROCESS_FINISH;
            }
            break;

        case CEC_DEVICE_DETECT_WAIT_ACTIVE_SOURCE:
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_DeviceDetect) > INTERVAL_500_MS )
            {
                CEC_STATE_INFO( printf("\033[41;4m              Over 500 ms \033[0m \n") );

                /***********************
                If <Active Source> is not received for 500ms
                and physical address of <Report Physical Address> is the same as current HDMI input,
                then TV sends <Give Device Power Status>.
                ***********************/
                if ( IsDeviceConnectedWithHDMI(_stCecStateInfoList.stState_DeviceDetect.enDstDeviceLA, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                {
                    _stCecStateInfoList.stState_DeviceDetect.enState =
                        CEC_DEVICE_DETECT_SEND_GIVE_DEVICE_POWER_STATUS;
                }
                else
                {
                    _stCecStateInfoList.stState_DeviceDetect.enState =
                        CEC_DEVICE_DETECT_PROCESS_FINISH;
                }
            }
            break;

        case CEC_DEVICE_DETECT_SEND_GIVE_DEVICE_POWER_STATUS:
            _stCecStateInfoList.stState_DeviceDetect.enState =
                CEC_DEVICE_DETECT_WAIT_REPORT_POWER_STATUS;

            msAPI_CEC_PostMsg_GiveDevicePowerStatus(DIRECTMSG, _stCecStateInfoList.stState_DeviceDetect.enDstDeviceLA);

            msCecSetStartTime(INTERVAL_CEC_FSM_DeviceDetect) ;
            break;

        case CEC_DEVICE_DETECT_WAIT_REPORT_POWER_STATUS:
            if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_DeviceDetect) > INTERVAL_1_SECOND )
            {
                CEC_STATE_INFO( printf("\033[41;4m              Over 1 second \033[0m \n") );

                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_GIVE_DEVICE_POWER_STATUS_RETRANSMISSION;
            }
            break;

        case CEC_DEVICE_DETECT_GIVE_DEVICE_POWER_STATUS_RETRANSMISSION:
            /***********************
            Retransmission times is max 5 (include 1st transmission), interval is 6 sec.
            ***********************/
            if ( _stCecStateInfoList.stState_DeviceDetect.RetransmissionTimes >= 5 )
            {
                CEC_STATE_INFO( printf("\033[41;4m              Over 5 times retransmission \033[0m \n") );

                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_PROCESS_FINISH;
            }
            else if ( msHDMICecGetTimeInterval(INTERVAL_CEC_FSM_DeviceDetect) > INTERVAL_6_SECOND )
            {
                CEC_STATE_INFO( printf("\033[41;4m              Over 6 seconds \033[0m \n") );

                _stCecStateInfoList.stState_DeviceDetect.enState =
                    CEC_DEVICE_DETECT_SEND_GIVE_DEVICE_POWER_STATUS;

                _stCecStateInfoList.stState_DeviceDetect.RetransmissionTimes++;
            }
            break;

        case CEC_DEVICE_DETECT_SEND_STREAM_PATH:
            _stCecStateInfoList.stState_DeviceDetect.enState =
                CEC_DEVICE_DETECT_PROCESS_FINISH;

            msAPI_CEC_PostMsg_SetStreamPath(DIRECTMSG, _stCecStateInfoList.stState_DeviceDetect.MyPhysicalAddress);
            break;

        case CEC_DEVICE_DETECT_PROCESS_FINISH:
            memset(&(_stCecStateInfoList.stState_DeviceDetect), 0, sizeof(ST_CEC_STATE_DEVICE_DETECT));
            _stCecStateInfoList.stState_DeviceDetect.enState = CEC_DEVICE_DETECT_IDLE;
            break;


        default :
            break;
    }
}

static void msCecStateMachine(void)
{
    // basic state for Device is plugged in by sending <Report Physical Address>
    msCecStateMachine_DeviceDetect();


    if (_stMsApiCecInfoList.fCecFirstPollingFinish == TRUE)
    {
        msCecStateMachineCustomer();
    }
}

//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecInit()
//  [Description]
//                  CEC initial sequence
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_Init(void)
{
    MS_CEC_INIT_INFO msCecInfo;

    MDrv_CEC_SetRetryCount(CEC_RETRY_TIME);

    memset(&msCecInfo, 0, sizeof(MS_CEC_INIT_INFO));
    msCecInfo.u32XTAL_CLK_Hz = MST_XTAL_CLOCK_HZ;
    MApi_CEC_InitChip(&msCecInfo);

    msCecInitVariable();
    msCecInitInterval();

    msCecSetActiveDevice(E_LA_TV);
    msCecEmptySwMsgQueue();

    MApp_Aud_SetTVSpeaker();    //CEC 13.15.2, Amplifier comes out of standby if receive <System Audio Mode Request>[PA]
}

//**************************************************************************
//  [Function Name]:
//                   msApp_CEC_ARC_Handler()
//  [Description]
//                  CEC ARC connect judge and show menu info
//  [Arguments]:
//
//  [Return]:
//               bool
//**************************************************************************

BOOLEAN msApp_CEC_ARC_Handler(void)
{
    static BOOLEAN ARCConnectMenuIsShow =FALSE;
    static BOOLEAN ARCDisconnectMenuIsShow =FALSE;
    static BOOLEAN _bPreARCConnectedStatus = FALSE;
    BOOLEAN bNeedToUpdate = FALSE;

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == FALSE)
    {
        return FALSE;
    }

  #if(CEC_VERSION_USING == CEC_NEW_VERSION)
    if (_bPreARCConnectedStatus != msAPI_CEC_IsAudioSystemKeyValid())
  #else
    if (_bPreARCConnectedStatus != msAPI_CEC_ARC_Is_Connect())
  #endif
    {
        bNeedToUpdate = TRUE;
    }

  #if(CEC_VERSION_USING == CEC_NEW_VERSION)
    _bPreARCConnectedStatus = msAPI_CEC_IsAudioSystemKeyValid();
  #else
    _bPreARCConnectedStatus = msAPI_CEC_ARC_Is_Connect();
  #endif

    if (bNeedToUpdate)
    {
      #if(CEC_VERSION_USING == CEC_NEW_VERSION)
        if ( (msAPI_CEC_IsAudioSystemKeyValid() == TRUE)
      #else
        if ( (msAPI_CEC_ARC_Is_Connect() == TRUE)
      #endif
           &&(MApp_CEC_CheckDeviceValidForARC() == TRUE) )
        {
            msCecSetARCStatus(TRUE);

            if (ARCConnectMenuIsShow == FALSE)
            {
                MApp_UiMenu_ARCDeviceStatusWin_Show(TRUE);
                ARCConnectMenuIsShow = TRUE;
                ARCDisconnectMenuIsShow = FALSE;
            }
        }
        else
        {
            msCecSetARCStatus(FALSE);

            if ( (ARCDisconnectMenuIsShow == FALSE)
               &&(ARCConnectMenuIsShow == TRUE) )
            {
                MApp_UiMenu_ARCDeviceStatusWin_Show(FALSE);
                ARCConnectMenuIsShow = FALSE;
                ARCDisconnectMenuIsShow = TRUE;
            }
        }
    }
    return TRUE;
}


static void msCecEmptyHwMsgFifo(void)
{
    MS_U8 u8Fifoidx;

    if ( MApi_CEC_GetMsgCnt() == 0 ) return;  //no received message to process

    u8Fifoidx = MApi_CEC_GetFifoIdx();

    if ( (u8Fifoidx+1) >= CEC_FIFO_CNT )
        MApi_CEC_SetFifoIdx(0);
    else
        MApi_CEC_SetFifoIdx(u8Fifoidx+1);

    MApi_CEC_SetMsgCnt(MApi_CEC_GetMsgCnt() - 1);
}

void msAPI_CEC_EmptyAllMsgFifo(void)
{
    while ( MApi_CEC_GetMsgCnt() != 0 )
    {
        printf("\n\e[31;1m msAPI_CEC_EmptyAllMsgFifo \33[m \n");

        msCecEmptyHwMsgFifo();
    }
}


//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_Handler_ForBootUp()
//  [Description]
//                   CEC handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

void msAPI_CEC_Handler_ForBootUp(MS_U8 u8CecDevicesCount)
{
    U8 i;

    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return;
    }

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == DISABLE)
    {
        //printf("CEC function OFF!\n");
        return;
    }

    for (i=0; i<(u8CecDevicesCount+1); i++)
    {
      #if (!ENABLE_CEC_INT) // if not enable CEC interrupt, use sw polling to instead of
        MApi_CEC_ChkRxBuf();
      #endif

        msCecProcessRxCmd();
    }
}

//**************************************************************************
//  [Function Name]:
//                   MsAPI_CecCecHandler()
//  [Description]
//                   CEC handler
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void msAPI_CEC_Handler(void)
{
    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return;
    }

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == DISABLE)
    {
        //printf("CEC function OFF!\n");
        msAPI_CEC_EmptyAllMsgFifo();

        _stMsApiCecInfoList.fCecPowerOnPollingFinish = TRUE;

        return;
    }
    else
    {
        msApp_CEC_ARC_Handler();
    }

    msCecProcessTxMsg();

//    msAPI_CEC_AMPHanlder();

  #if (!ENABLE_CEC_INT) // if not enable CEC interrupt, use sw polling to instead of
    MApi_CEC_ChkRxBuf();
  #endif

    if ( MApi_CEC_GetMsgCnt() != 0 ) // if received message to process
    {
        msCecProcessRxCmd();
    }
    else
    {
        msCecPollingDevices();

        msCecStateMachine();
    }
}

BOOLEAN msCecPostMsgUserCtrlPressed(void)
{
#if ARC_PATCH_FOR_CHINA
    if (  (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) == TRUE)
       && (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
       && (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
       )
    {
        return TRUE;
    }
#else
    #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON || \
        CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)
        //send userctrlpressed when using audio system, dont check the arc but check the audio mode
        if (  (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) == TRUE)
           && (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
           && (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
           &&(msAPI_CEC_QuerySystemAudioMode() == TRUE)
           )
        {
            return TRUE;
        }
    #else
        if ( (msAPI_CEC_ARC_Is_Connect() == TRUE)
           &&(msAPI_CEC_QuerySystemAudioMode() == TRUE) )
        {
            return TRUE;
        }
    #endif//#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)
#endif

    return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_SendCECKeyFromTVtoDev()
//  [Description]
//                   CEC key process
//  [Arguments]:
//                   keycode: key code
//  [Return]:
//                   return CEC key parse is enable or not
BOOLEAN msAPI_CEC_SendCECKeyFromTVtoDev(U8 keycode)
{
    BOOLEAN user_ctrl_flag = FALSE;
//    MsCEC_MSG_USER_CTRL_PARM CECKey = 0xFF;
    MS_U8 CECKey = 0xFF;

    if (stCecFeatureSupport.bCECFeatureSupport_RemoteControlPassThrough == FALSE)
    {
        return FALSE;
    }

    if ( gCECInitDone == FALSE)
    {
        //printf("\r\n CEC Irda Key - HW not Init \n");
        return FALSE;
    }

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode != ENABLE)
    {
        //printf("[CEC] !!! Master EasyLink is OFF !!! \n");
        return FALSE;
    }

    if (stGenSetting.stHDMISetting.g_bHdmiCecDeviceControl == FALSE)
    {
        switch (keycode)
        {
            case KEY_VOLUME_PLUS:
            case KEY_VOLUME_MINUS:
            case KEY_MUTE:
                break;

            default:
                //printf("[CEC] !!! Device control is OFF !!! \n");
                return FALSE;
        }
    }

    enUserCtrlPressedLA = GetActiveLogicalAddress();
    CEC_DPRINTF(" Active Logical Address = 0x%x \n", enUserCtrlPressedLA);

    CECKey = msCecTransferIrKeyToCecKey(keycode);
    //CEC_DPRINTF("\r\n CEC Irda Key(0x%bx) \n", keycode);

    if (CECKey != E_MSG_UI_UNKNOWN)
    {
        if (keycode == KEY_POWER)
        {
            if ( !MApp_UiMenu_IsCountDownWinShow() )    // don't power off DVD when countdown win showing
            {
                msAPI_CEC_PostMsg_Standby(DIRECTMSG);
            }

            MsOS_DelayTask(100);
            return FALSE;
        }
    }
    else
    {
        CEC_DPRINTF(" CEC Key return 2 (0x%x) \n", keycode);
        return FALSE;
    }

    switch ( (MsCEC_MSG_USER_CTRL_PARM)CECKey )
    {
        default:
        {
            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enUserCtrlPressedLA,
                                              (MsCEC_MSG_USER_CTRL_PARM)CECKey);
            user_ctrl_flag = TRUE;
            break;
        }

        case E_MSG_UI_UP:
        case E_MSG_UI_DOWN:
        case E_MSG_UI_LEFT:
        case E_MSG_UI_RIGHT:
        case E_MSG_UI_SELECT:
        {
            if ( msCecIsRCPassThroughBypass() )
            {
                return FALSE;
            }

            msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                              enUserCtrlPressedLA,
                                              (MsCEC_MSG_USER_CTRL_PARM)CECKey);
            user_ctrl_flag = TRUE;
            break;
        }

        case E_MSG_UI_STOP:
        {
            if (gCECRecordEnable) // record on
            {
                gCECRecordEnable = FALSE;
                msAPI_CEC_PostMsg_RecordOff(DIRECTMSG, enUserCtrlPressedLA);
            }
            else
            {
                user_ctrl_flag = TRUE;
                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, gCECUserControlEnable,
                                                  enUserCtrlPressedLA,
                                                  (MsCEC_MSG_USER_CTRL_PARM)CECKey);
            }
            break;
        }

        case E_MSG_UI_MUTE:
        case E_MSG_UI_VOLUME_UP:
        case E_MSG_UI_VOLUME_DOWN:
        {
            enUserCtrlPressedLA = E_LA_AUDIO_SYS;

            if(msCecPostMsgUserCtrlPressed() == TRUE)
            {
                user_ctrl_flag = FALSE;

                if ( (MsCEC_MSG_USER_CTRL_PARM)CECKey == E_MSG_UI_MUTE )
                {
                    MApp_ARC_KeyProc_Mute();
                }

                msAPI_CEC_PostMsg_UserCtrlPressed(DIRECTMSG, TRUE,
                                                  enUserCtrlPressedLA,
                                                  (MsCEC_MSG_USER_CTRL_PARM)CECKey);
            }
            else
            {
                msCecSetARCStatus(FALSE);
                return FALSE;
            }

            break;
        }
    }

    if (user_ctrl_flag && !gCECUserControlEnable) // if menu status is deactived, remote control key should handle locally, not send CEC message out
    {
        return FALSE;
    }
    else
    {
        if ( ! ( (CECKey == E_MSG_UI_VOLUME_UP)
               ||(CECKey == E_MSG_UI_VOLUME_DOWN)
               ||(CECKey == E_MSG_UI_MUTE) ) )
        {
            u8KeyCode = KEY_NULL;
        }

        return TRUE;
    }
}

void msAPI_CEC_SetPowerStatusOn2Standby(void)
{
    msAPI_CEC_SetPowerStatus(E_LA_TV, E_MSG_PWRSTA_ON2STANDBY);

    MApi_CEC_SetActivePowerStatus(E_MSG_PWRSTA_ON2STANDBY);
}

//
//**************************************************************************
//

#else

MS_U8 code gCECdummy; // Add a dummy variable for complier link

#endif // ENABLE_CEC


