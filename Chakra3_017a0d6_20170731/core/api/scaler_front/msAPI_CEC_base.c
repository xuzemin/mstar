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
/// file    msAPI_CEC_base.c
/// @author MStar Semiconductor Inc.
/// @brief  HDMI CEC API Interface
///////////////////////////////////////////////////////////////////////////////////////////////////



//
//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------
//

CECWAKEUPCMD gCecWakeupCmd;


//
//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
//

void msCecSetStartTime(EN_CECIntervalTimerType uctimer)
{
    m_gCECStartTime[uctimer] = msAPI_Timer_GetTime0();
}

MS_U32 msHDMICecGetTimeInterval(EN_CECIntervalTimerType uctimer) //unit = ms
{
    return msAPI_Timer_DiffTimeFromNow(m_gCECStartTime[uctimer]);
}

//
//***************************************************************************************
//

void msCecInitInterval(void)
{
    MS_U8 i;

    for (i=(MS_U8)INTERVAL_CEC_NULL; i<(MS_U8)INTERVAL_TIMER_MAX; i++ )
    {
        msCecSetStartTime( (EN_CECIntervalTimerType)i );
    }
}

//
//***************************************************************************************
//

BOOLEAN IsDeviceConnectedWithHDMI(MsCEC_DEVICELA enDeviceLA, INPUT_SOURCE_TYPE_t enInputSource)
{
    MS_U8 u8port = enInputSource - INPUT_SOURCE_HDMI + 1;

    CEC_MSG( printf("\033[32;1m port = 0x%02X;  PA[%x] = 0x%02X \033[0m \n",
            (int)(u8port<<4), (int)enDeviceLA,
            (int)(_stMsApiCecInfoList.u8PhysicalAddress[enDeviceLA][0] & 0xF0)) );

    if (_stMsApiCecInfoList.State[enDeviceLA] != E_STM_EMPTY)
    {
        if ( (_stMsApiCecInfoList.u8PhysicalAddress[enDeviceLA][0] & 0xF0) == (u8port<<4) )
            return TRUE;
    }

    return FALSE;
}

//
//***************************************************************************************
//

MS_BOOL msAPI_CEC_IsDeviceExist(MsCEC_DEVICELA enDevice)
{
  #if 0
    return (_stMsApiCecInfoList.State[enDevice] > E_STM_POLLING);

  #else
    return _stMsApiCecInfoList.bCecDevicesExisted[enDevice];
  #endif
}

//
//***************************************************************************************
//

MS_U8 msAPI_CEC_QueryAudioStatusValue(void)
{
    return u8CECAmpControlVolume;
}

void msAPI_CEC_SetSystemAudioMode(BOOLEAN bMode)
{
    CEC_MSG( printf("\033[32;1m[CEC] SysAudioMode set to %d \033[0m \n", bMode) );
    bSystemAudioMode = bMode;
}

BOOLEAN msAPI_CEC_QuerySystemAudioMode(void)
{
    return bSystemAudioMode;
}

//
//***************************************************************************************
//

void msAPI_CEC_SaveAmpControlVolume(MS_U8 _u8CECAmpControlVolume)
{
    u8CECAmpControlVolume = _u8CECAmpControlVolume;
}

MS_U8 msAPI_CEC_QueryAmpVolumeValue(void)
{
    return (msAPI_CEC_QueryAudioStatusValue()& 0x7F);
}

//
//***************************************************************************************
//

BOOLEAN msAPI_CEC_IsAudioSystemKeyValid(void)
{
    /*
    Audio system key valid condition as below

    1) TV speaker = CEC
    2) CEC switch = ON
    3) Already connect an audio device
    4) System audio mode = ON
    5) ARC switch = ON
    */
    if (  (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
       && (stGenSetting.stHDMISetting.g_bHdmiCecMode == ENABLE)
       && (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) == TRUE)
       && (msAPI_CEC_QuerySystemAudioMode() == TRUE)
       && (stGenSetting.stHDMISetting.g_enHDMIARC == ENABLE)
       )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//==================================================
//
// Audio return channel (ARC)
//
//==================================================

BOOLEAN MApp_CEC_CheckInputAMPExist(void)
{
    if(_stMsApiCecInfoList.State[E_LA_AUDIO_SYS] != E_STM_EMPTY)
    {
        return TRUE ;
    }

    return FALSE ;
}

BOOLEAN MApp_CEC_CheckDeviceValidForARC(void)
{
    CEC_MSG( printf("[CEC] CheckDeviceValidForARC (%d, %d) \n",
                            ARC_SUPPORT_PORT, _stMsApiCecInfoList.AMPPort ));

    if (ARC_SUPPORT_PORT == 0) // no ARC support port
    {
        CEC_MSG( printf("     \e[31;1m No ARC port supported \e[m \n") );
        return FALSE;
    }

    if (ARC_SUPPORT_PORT == _stMsApiCecInfoList.AMPPort)
    {
        CEC_MSG( printf("     \e[31;1m AMP in ARC port \e[m \n") );
        return TRUE;
    }

    CEC_MSG( printf("     \e[31;1m AMP not in ARC port \e[m \n") );
    return FALSE;
}

BOOLEAN MApp_CEC_IsAdjacentARCDeviceExist(void)
{
    MS_U16 u16AmpPhyAddr = _stMsApiCecInfoList.u16PhysicalAddress[E_LA_AUDIO_SYS];

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == DISABLE)
    {
        return FALSE;
    }

  #if 0
    if (MApp_CEC_CheckInputAMPExist() == FALSE )
    {
        return FALSE;
    }
  #endif

    CEC_MSG( printf("[CEC] MApp_CEC_IsAdjacentARCDeviceExist (0x%4X) \n", u16AmpPhyAddr) );

    //
    // check non-adjacent ARC device part I
    // Normally, for TV, the physical addres of adjacent ARC device must be
    // PA=1.0.0.0, PA=2.0.0.0, PA=3.0.0.0 or PA=4.0.0.0
    //
    if ( u16AmpPhyAddr & 0x0FFF )
    {
        return FALSE;
    }

    return TRUE;
}


//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_ARC_GetARCAudioVolume()
//  [Description]
//                  Get ARC AudioVolume
//  [Arguments]:
//
//  [Return]:
//               MS_U8
//**************************************************************************

MS_U8 msAPI_CEC_ARC_GetARCAudioVolume(void)  //anvi22
{
    return ARCAudioVolume;
}

//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_ARC_SetAmpMute()
//  [Description]
//                   Set ARC Amp mute status
//  [Arguments]:
//
//  [Return]:
//               void
//**************************************************************************

void  msAPI_CEC_ARC_SetAmpMute(BOOLEAN isMute)  //anvi22
{
    ARCAMPIsMute = isMute;
}


//**************************************************************************
//  [Function Name]:
//                   MApp_CEC_ARC_AmpIsMute()
//  [Description]
//                  Get ARC Amp mute status
//  [Arguments]:
//
//  [Return]:
//               BOOLEAN
//**************************************************************************

BOOLEAN msAPI_CEC_ARC_GetAmpMute(void)  //anvi22
{
    return ARCAMPIsMute;
}

//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_ARC_TX_Control()
//  [Description]
//                   CEC ARC TX output enable/disable
//  [Arguments]:
//                   0: disable / else: enable
//  [Return]:
//                   void
//**************************************************************************
void msAPI_CEC_ARC_TX_Control(BOOLEAN bEn)
{
    MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, bEn, FALSE);
}

//**************************************************************************
//  [Function Name]:
//                   msAPI_CEC_ARC_Is_Connect()
//  [Description]
//                  CEC ARC connect judge and show menu info
//  [Arguments]:
//
//  [Return]:
//               bool
//**************************************************************************
BOOLEAN msAPI_CEC_ARC_Is_Connect(void)  //anvi22
{
    BOOLEAN ret = FALSE;

    if (  (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) == TRUE)
       && (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
       && (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
       && (gIsCECAmpARCOn == TRUE)
       )
    {
        ret = TRUE;
    }

    return ret;
}


//
//***************************************************************************************
//
void msAPI_CEC_SetDeviceName(MS_U8 u8Device, MS_U8* pName, BOOLEAN bIsDefault)
{
    if (bIsDefault)
    {
        msCecLoadDefaultDeviceName(u8Device, stGenSetting.g_SysSetting.Language);
    }
    else
    {
        MS_U8 len = strlen((char *)pName); // Mantis 0894728 fixed

        if (len >= MAX_CEC_DEVICE_OSD_NAME)
            len = (MAX_CEC_DEVICE_OSD_NAME-1);

        strncpy((char *)_stMsApiCecInfoList.u8CecDeviceName[u8Device], (char *)pName, len);
        _stMsApiCecInfoList.u8CecDeviceName[u8Device][len] = 0;
    }
}

MS_U8* msAPI_CEC_GetDeviceName(MS_U8 u8Device)
{
    return (MS_U8*)_stMsApiCecInfoList.u8CecDeviceName[u8Device];
}

//
//***************************************************************************************
//

MS_U8* msAPI_CEC_GetDeviceVendorID(MS_U8 u8Device)
{
    return (MS_U8*) _stMsApiCecInfoList.u8CecVendorID[u8Device];
}

void msAPI_CEC_SetDeviceVendorID(MS_U8 u8Device, MS_U8* pName)
{
    _stMsApiCecInfoList.u8CecVendorID[u8Device][0] = pName[0];
    _stMsApiCecInfoList.u8CecVendorID[u8Device][1] = pName[1];
    _stMsApiCecInfoList.u8CecVendorID[u8Device][2] = pName[2];

  #if 0
    printf(" <Device Vendor ID> 0x%x: ", u8Device );
    printf(" = 0x%x,", _stMsApiCecInfoList.u8CecVendorID[u8Device][0]);
    printf(" 0x%x,",   _stMsApiCecInfoList.u8CecVendorID[u8Device][1]);
    printf(" 0x%x \n", _stMsApiCecInfoList.u8CecVendorID[u8Device][2]);
  #endif
}

//
//***************************************************************************************
//

MS_U16 msAPI_CEC_GetDeviceIdx_PhyAddr(MS_U8 u8Idx)
{
    return _stMsApiCecInfoList.u16PhysicalAddress[u8Idx];
}

void msAPI_CEC_SetDeviceIdx_PhyAddr(MS_U8 u8Idx, MS_U16 u16PhyAddr)
{
  #if 0
    MsCEC_DEVICELA eDivIdx= msAPI_CEC_CheckDeviceIdx_PhyAddr(u16PhyAddr);

    if (  (eDivIdx != E_LA_UNREGISTERED) && (eDivIdx != u8Idx)
        && ((u16PhyAddr & 0xFF00) != (u16PhyAddr & 0xF000))
       )
    {
        msCecRemoveDevice(eDivIdx);
    }
  #endif

    _stMsApiCecInfoList.u16PhysicalAddress[u8Idx] = u16PhyAddr;
    _stMsApiCecInfoList.u8PhysicalAddress[u8Idx][0] = ((u16PhyAddr & 0xFF00) >> 8);
    _stMsApiCecInfoList.u8PhysicalAddress[u8Idx][1] = (u16PhyAddr & 0x00FF);
}

//
//***************************************************************************************
//

void msCecSetActiveDevice(MsCEC_DEVICELA enDevice)
{
    //printf(" >> msCecSetActiveDevice(0x%x) \n", enDevice);

    _stMsApiCecInfoList.enActiveDeviceLA = (MsCEC_DEVICELA) (enDevice & 0x0F);
}

MsCEC_DEVICELA msAPI_CEC_GetActiveDevice(void)
{
    return _stMsApiCecInfoList.enActiveDeviceLA;
}

MsCEC_DEVICELA GetActiveLogicalAddress(void)
{
    MsCEC_DEVICELA idx = E_LA_TV;
    MS_U16 u16PhyAddr = _stMsApiCecInfoList.u16ActiveSourceAddress;

    CEC_MSG( printf("\n[CEC] GetActiveLogicalAddress() \n") );

    CEC_MSG( printf("[CEC] Active LA: %02X \n", _stMsApiCecInfoList.enActiveDeviceLA) );
    CEC_MSG( printf("[CEC] Active PA: 0x%04X \n", _stMsApiCecInfoList.u16ActiveSourceAddress) );

    for (idx = E_LA_TV ; idx < E_LA_FREE_USE ; idx =(MsCEC_DEVICELA)(idx+1))
    {
        if (_stMsApiCecInfoList.State[idx] > E_STM_POLLING)
        {
            CEC_MSG( printf("[CEC] PhysicalAddress: 0x%04X \n",
                              _stMsApiCecInfoList.u16PhysicalAddress[idx]) );
        }

        if ( (_stMsApiCecInfoList.u16PhysicalAddress[idx] == u16PhyAddr)
           &&(idx != E_LA_AUDIO_SYS) )
        {
            break;
        }
    }

    if (idx != E_LA_FREE_USE)
    {
        CEC_MSG( printf("      Active LA: 0x%x \n", (int)idx) );
        return idx ;
    }

    return E_LA_TV ;
}

MsCEC_DEVICELA GetLogicalAddressByPhysicalAddress(MS_U16 u16PhyAddr)
{
    MsCEC_DEVICELA idx = E_LA_TV;

    CEC_MSG( printf("\n[CEC] GetLogicalAddressByPhysicalAddress(0x%04X) \n", u16PhyAddr) );

    CEC_MSG( printf("[CEC] Active %02X: [0x%04X] \n",
            _stMsApiCecInfoList.enActiveDeviceLA,
            _stMsApiCecInfoList.u16PhysicalAddress[_stMsApiCecInfoList.enActiveDeviceLA]) );

    for (idx = E_LA_TV ; idx < E_LA_FREE_USE ; idx =(MsCEC_DEVICELA)(idx+1))
    {
        if (_stMsApiCecInfoList.State[idx] > E_STM_POLLING)
        {
            CEC_MSG( printf("[CEC] PhysicalAddress: 0x%04X \n",
                              _stMsApiCecInfoList.u16PhysicalAddress[idx]) );
        }

        if ( (_stMsApiCecInfoList.u16PhysicalAddress[idx] == u16PhyAddr)
           &&(idx != E_LA_AUDIO_SYS) )
        {
            break;
        }
    }

    if (idx != E_LA_FREE_USE)
    {
        CEC_MSG( printf("      Active LA: 0x%x \n", (int)idx) );
        return idx ;
    }

    return E_LA_TV ;
}


//
//***************************************************************************************
//

void msAPI_CEC_SetPowerStatus(MsCEC_DEVICELA enDevice, MsCEC_MSG_POWER_STATUS_PARM enPowerStatus)
{
    _stMsApiCecInfoList.enPowerStatus[enDevice] = enPowerStatus;

    CEC_DPRINTF(" Set enDevice 0x%x,", enDevice);
    CEC_DPUTSTR(" POWER_STATUS:");
    CEC_DPRINTF(" %s \n",
            (enPowerStatus == E_MSG_PWRSTA_ON)?          "ON"
            :(enPowerStatus == E_MSG_PWRSTA_STANDBY)?    "STANDBY"
            :(enPowerStatus == E_MSG_PWRSTA_STANDBY2ON)? "STANDBY2ON"
            :(enPowerStatus == E_MSG_PWRSTA_ON2STANDBY)? "ON2STANDBY"
            :                                            "UNKNOW");
}

MsCEC_MSG_POWER_STATUS_PARM msAPI_CEC_GetPowerStatus(MsCEC_DEVICELA enDevice)
{
    MsCEC_MSG_POWER_STATUS_PARM enPowerStatus = _stMsApiCecInfoList.enPowerStatus[enDevice];

    CEC_DPRINTF(" enDevice 0x%x,", enDevice);
    CEC_DPUTSTR(" POWER_STATUS:");
    CEC_DPRINTF(" %s \n",
            (enPowerStatus == E_MSG_PWRSTA_ON)?          "ON"
            :(enPowerStatus == E_MSG_PWRSTA_STANDBY)?    "STANDBY"
            :(enPowerStatus == E_MSG_PWRSTA_STANDBY2ON)? "STANDBY2ON"
            :(enPowerStatus == E_MSG_PWRSTA_ON2STANDBY)? "ON2STANDBY"
            :                                            "UNKNOW");

    return enPowerStatus;
}

//
//***************************************************************************************
//

void msAPI_CEC_SetActivePhyAddr(MS_U16 u16ActPhyAddr)
{
    MsCEC_DEVICELA iActLA = msAPI_CEC_GetActiveDevice();

    _stMsApiCecInfoList.u16PhysicalAddress[iActLA] = u16ActPhyAddr;
    _stMsApiCecInfoList.u8PhysicalAddress[iActLA][0] = (u16ActPhyAddr & 0xFF00) >> 8;
    _stMsApiCecInfoList.u8PhysicalAddress[iActLA][1] = (u16ActPhyAddr & 0x00FF);

    //printf(" Active Device 0x%x:", iActLA);
    //printf(" 0x%x \n", _stMsApiCecInfoList.u16PhysicalAddress[iActLA]);
}

MS_U16 msAPI_CEC_GetActivePhyAddr(void)
{
    MsCEC_DEVICELA iActLA = msAPI_CEC_GetActiveDevice();

    return _stMsApiCecInfoList.u16PhysicalAddress[iActLA];
}

//
//***************************************************************************************
//

void msAPI_CEC_SetCecVersion(MsCEC_DEVICELA enDevice, MS_U8 u8Version)
{
    _stMsApiCecInfoList.u8CECVersion[enDevice] = u8Version;

    CEC_MSG( printf(" CEC Version of 0x%x is %d:", enDevice, u8Version) );

    switch (u8Version)
    {
        case CEC_VERSION_11:
            CEC_DPUTSTR(" Ver 1.1 \n");
            break;
        case CEC_VERSION_12:
            CEC_DPUTSTR(" Ver 1.2 \n");
            break;
        case CEC_VERSION_12a:
            CEC_DPUTSTR(" Ver 1.2a \n");
            break;
        case CEC_VERSION_13:
            CEC_DPUTSTR(" Ver 1.3 \n");
           break;
        case CEC_VERSION_13a:
            CEC_DPUTSTR(" Ver 1.3a \n");
            break;
        case CEC_VERSION_14:
            CEC_DPUTSTR(" Ver 1.4 \n");
            break;
        default:
            CEC_DPUTSTR(" Unknow Ver \n");
           break;
    }
}

MS_U8 msAPI_CEC_GetCecVersion(MsCEC_DEVICELA enDevice)
{
    return _stMsApiCecInfoList.u8CECVersion[enDevice];
}

//
//***************************************************************************************
//

MS_U8 msAPI_CEC_GetDeviceTotalNum(void)
{
    return _stMsApiCecInfoList.u8CecDeviceCount;
}

static void msAPI_CEC_SetDeviceType(MS_U8 u8Idx, MsCEC_DEVICE_TYPE enDeviceType)
{
    _stMsApiCecInfoList.enDeviceType[u8Idx] = enDeviceType;
}

//
//***************************************************************************************
//

void MApp_CEC_SetMyPhyAddr(INPUT_SOURCE_TYPE_t pre_srctype, INPUT_SOURCE_TYPE_t cur_srctype)
{
  #if 0
    if ( gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return;
    }

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == DISABLE)
    {
        return;
    }
  #endif

    if ( IsSrcTypeHDMI(pre_srctype) && (!IsSrcTypeHDMI(cur_srctype)) )
    {
        _stMsApiCecInfoList.u8ActiveSourceAddress[0] = 0x00;
        _stMsApiCecInfoList.u8ActiveSourceAddress[1] = 0x00;
    }
    else if ( IsSrcTypeHDMI(cur_srctype) )
    {
        _stMsApiCecInfoList.u8ActiveSourceAddress[0] = (cur_srctype-INPUT_SOURCE_HDMI+1)<<4;
        _stMsApiCecInfoList.u8ActiveSourceAddress[1] = 0x00 ;
    }

    _stMsApiCecInfoList.u16ActiveSourceAddress =
        (_stMsApiCecInfoList.u8ActiveSourceAddress[0] << 8) | _stMsApiCecInfoList.u8ActiveSourceAddress[1];

    CEC_MSG( printf("[CEC] SetMyPhyAddr 0x%04X \n", _stMsApiCecInfoList.u16ActiveSourceAddress) );
}

//
//***************************************************************************************
//

void msAPI_CEC_SetSystemMute(void)
{
    if (stCecFeatureSupport.bCECFeatureSupport_SystemAudioControl == FALSE)
    {
        return;
    }

    printf("\33[0;31m[CEC] SetSystemMute \e[m\n");

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_HDMI_CEC_ARC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
}

void msAPI_CEC_SetSystemUnMute(void)
{
    if(stCecFeatureSupport.bCECFeatureSupport_SystemAudioControl == FALSE)
    {
        return;
    }

    printf("\33[0;31m[CEC] SetSystemUnMute \e[m\n");

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_HDMI_CEC_ARC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
}

static void msCecSetARCStatus(BOOL bEnable)
{
    msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW);
    CEC_DPRINTF("\n[CEC] msCecSetARCStatus(%s) \n", ((bEnable)?("TRUE"):("FALSE")));
    msDebug_ANSI_AllAttrOffText();

    if (bEnable)    // turn on ARC
    {
        msAPI_CEC_ARC_TX_Control(TRUE);
        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);
    }
    else
    {
        msAPI_CEC_ARC_TX_Control(FALSE);
        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
    }
}

void SetArcOnBehavior(void)
{
    U8  port = SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) - INPUT_SOURCE_HDMI + 1;
    U16 u16AMPPhyAddr = msAPI_CEC_GetDeviceIdx_PhyAddr(E_LA_AUDIO_SYS);
    CEC_ARC_INFO( printf("\e[31;1m port: %d \33[m \n", port) );
    CEC_ARC_INFO( printf("\e[31;1m u16AMPPhyAddr: 0x%04X \33[m \n", u16AMPPhyAddr) );

    if (msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS))
    {
        if ( IsHDMIInUse())
        {
            if ( (u16AMPPhyAddr & 0xF000) == (port * 0x1000) )
            {
                if ( (MApp_CEC_CheckDeviceValidForARC()   == TRUE)   // AMP is connected with HDMI port which supports ARC
                   &&(MApp_CEC_IsAdjacentARCDeviceExist() == TRUE) ) // AMP is connected with validate HDMI port (x.0.0.0)
                {
                    msAPI_CEC_SetSystemMute();
                    msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);
                }
            }
            else
            {
                msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);
            }
        }
        else
        {
            msAPI_CEC_PostMsg_RequestARCInitiation(DIRECTMSG, E_LA_AUDIO_SYS);
        }

        msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, TRUE);
    }
}


//
//**************************************************************************
//  [Function Name]: msAPI_CEC_CheckSamePhysicalAddr
//
//  [Description]: It used to check if 2 different LA have the same physical address
//
//  [Arguments]: physical addrress, device type, LA
//
//  [Return]: void
//
//**************************************************************************
//
BOOLEAN msAPI_CEC_CheckSameLogicalAddr(MS_U8 pa0, MS_U8 pa1, MS_U8 pa2, MS_U8 NewLA)
{
    MsCEC_DEVICELA idx ;

    for (idx = E_LA_RECORDER1; idx < E_LA_MAX; idx = (MsCEC_DEVICELA)(idx+1))
    {
        if (idx == NewLA)
        {
            if ( (_stMsApiCecInfoList.u8PhysicalAddress[idx][0] != pa0)
               ||(_stMsApiCecInfoList.u8PhysicalAddress[idx][1] != pa1)
               ||(_stMsApiCecInfoList.enDeviceType[idx] != (MsCEC_DEVICE_TYPE)pa2) )
            {
                CEC_MSG( printf("\e[31;1m[CEC] CheckSameCECLogicalAddr() \33[m \n") );
                CEC_MSG( printf("      LA  :     %X  (  %X  ) \n", (int)idx, (int)NewLA) );
                CEC_MSG( printf("      PA  : 0x%04X  (0x%04X) \n",               \
                                _stMsApiCecInfoList.u16PhysicalAddress[idx],    \
                                (pa0 << 8) | (pa1)) );
                CEC_MSG( printf("      Type:     %X  (  %X  ) \n", _stMsApiCecInfoList.enDeviceType[idx], pa2) );

                msCecDeviceListInitData((U8)idx) ;
                if( idx == E_LA_AUDIO_SYS )
                {
                    _stMsApiCecInfoList.AMPPort = 0xFF ;
                }
                return TRUE;
            }
        }
    }
    return FALSE ;
}

//
//**************************************************************************
//  [Function Name]: msAPI_CEC_CheckSamePhysicalAddr
//
//  [Description]: It used to check if 2 different LA have the same physical address
//
//  [Arguments]: physical addrress, device type, LA
//
//  [Return]: void
//
//**************************************************************************
//
void msAPI_CEC_CheckSamePhysicalAddr(MS_U8 pa0, MS_U8 pa1, MS_U8 pa2, MS_U8 NewLA)
{
    MsCEC_DEVICELA idx ;

    for (idx = E_LA_RECORDER1; idx < E_LA_MAX; idx = (MsCEC_DEVICELA)(idx+1))
    {
        if ( (_stMsApiCecInfoList.u8PhysicalAddress[idx][0] == pa0)
           &&(_stMsApiCecInfoList.u8PhysicalAddress[idx][1] == pa1)
           //&&(_stMsApiCecInfoList.enDeviceType[idx] == pa2)
           &&(idx!=NewLA) )
        {
            CEC_ERROR_CODE  res = E_CEC_FEATURE_ABORT;

            CEC_MSG( printf("\e[31;1m[CEC] CheckSameCECPhysicalAddr() \33[m \n") );
            CEC_MSG( printf("      LA:     %X  (  %X  ) \n", (int)idx, (int)NewLA) );
            CEC_MSG( printf("      PA: 0x%04X  (0x%04X) \n",
                                    _stMsApiCecInfoList.u16PhysicalAddress[idx],
                                    (pa0 << 8) | (pa1) ) );

            res = msAPI_CEC_PingDevice(idx);
            CEC_MSG( printf("\e[31;1m[CEC] Ping %X: %s \33[m \n",
                (int)idx, ((res & E_CEC_TX_SUCCESS)?("Exist'"):("Removed"))) );
            if (res != E_CEC_TX_SUCCESS)
            {
                msCecDeviceListInitData((U8)idx) ;
                if( idx == E_LA_AUDIO_SYS )
                {
                    _stMsApiCecInfoList.AMPPort = 0xFF ;
                }
            }
            return ;
        }
    }

    UNUSED(pa2);
}

//
//**************************************************************************
//  [Function Name]: msAPI_CEC_CheckDeviceIdx_PhyAddr
//
//  [Description]: It used to get the index of the  physical addrress we search
//
//  [Arguments]: physical addrress
//
//  [Return]: index of  physical addrress searched. otherwise, return E_LA_UNREGISTERED
//
//**************************************************************************
//
MsCEC_DEVICELA msAPI_CEC_CheckDeviceIdx_PhyAddr(MS_U16 u16PhyAddr)
{
    MsCEC_DEVICELA i = E_LA_TV;

    for (i= E_LA_TV; i< E_LA_UNREGISTERED; i++)
    {
        if( _stMsApiCecInfoList.u16PhysicalAddress[i] == u16PhyAddr)
        {
            return i;
        }
    }

    return E_LA_UNREGISTERED;
}

//
//***************************************************************************************
//

void msAPI_CEC_GetDeviceInfo(void)
{
    MS_U8 i= 0, j= 0;

    printf("\e[31;1m [%d]: %s \33[m \n", __LINE__, __FUNCTION__);

    for (i=(int)E_LA_RECORDER1; i<(int)E_LA_MAX; i++)
    {
        if(msAPI_CEC_IsDeviceExist((MsCEC_DEVICELA)i))
        {
            g_stMenuCecDeviceList.aenDeviceLA[j]= (MsCEC_DEVICELA)i;
//            strcpy((char *)g_stMenuCecDeviceList.au8CecDeviceName[j] ,(char *)msAPI_CEC_GetDeviceName((MsCEC_DEVICELA)i));

            strncpy( (char *)g_stMenuCecDeviceList.au8CecDeviceName[j] ,
                     (char *)msAPI_CEC_GetDeviceName((MsCEC_DEVICELA)i),
                      //MIN(sizeof(g_stMenuCecDeviceList.au8CecDeviceName[j]), strlen((char *)msAPI_CEC_GetDeviceName((MsCEC_DEVICELA)i)))
                     MAX_CEC_DEVICE_OSD_NAME
                    );

            // Give string terminated
            g_stMenuCecDeviceList.au8CecDeviceName[j][MAX_CEC_DEVICE_OSD_NAME-1] = 0;

            g_stMenuCecDeviceList.u8CECDeviceNum++;
            g_stMenuCecDeviceList.wPhyAddr[j]= msAPI_CEC_GetDeviceIdx_PhyAddr((MsCEC_DEVICELA)i);
            j++;
        }
    }
}

//
//***************************************************************************************
//

void  msAPI_CEC_CheckWakeUpPort(void)
{
    if (gCECInitDone == FALSE)
    {
        //printf("!!! CEC HW not Init yet !!! \n");
        return;
    }

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == FALSE)
    {
        return;
    }

    if (msAPI_Power_IswakeupsourceCEC())
    {
        msAPI_CEC_PostMsg_RequestActiveSource(DIRECTMSG);
    }
}

BOOLEAN msAPI_CEC_CheckWakeupByOneTouchPlayCommand(void)
{

#if(PM_RUNS_IN == PM_RUNS_IN_FLASH)
    // TO DO
    return FALSE;

#else //PM51
    MS_U8 u8Length;

    u8Length = ((MDrv_ReadByte(REG_CEC_RX_LENGTH)) & 0x0F);
    CEC_DPRINTF("\r\n >> CEC_Check OneTouchPlay [%d] \n", u8Length);

    if(u8Length == 1)
    {
        CEC_DPRINTF("REG_CEC_DEVICE = %x\r\n",MDrv_ReadByte(REG_CEC_DEVICE));
        CEC_DPRINTF("REG_CEC_OPCODE = %x\r\n",MDrv_ReadByte(REG_CEC_OPCODE));

        gCecWakeupCmd.enDevice = (MsCEC_DEVICELA) (((MDrv_ReadByte(REG_CEC_DEVICE)) & 0xF0)>>4);
        gCecWakeupCmd.opcode = (MsCEC_MSGLIST) MDrv_ReadByte(REG_CEC_OPCODE);

        CEC_DPRINTF(" enDevice = 0x%x \n", gCecWakeupCmd.enDevice);
        CEC_DPRINTF(" opcode   = 0x%x \n", gCecWakeupCmd.opcode);

    #if ONE_TOUCH_PLAY_SUPPORT
        if (  (gCecWakeupCmd.opcode == E_MSG_OTP_IMAGE_VIEW_ON)
           || (gCecWakeupCmd.opcode == E_MSG_OTP_TEXT_VIEW_ON)
           )
        {
            return TRUE;
        }
    #endif
    }
    return FALSE;

#endif//end PM51
}

//
//***************************************************************************************
//


