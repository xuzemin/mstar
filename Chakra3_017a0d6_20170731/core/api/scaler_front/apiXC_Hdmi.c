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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    apiXC_Hdmi.c
/// @brief  Scaler API layer Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////
#define _API_XC_HDMI_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include <string.h>

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "debug.h"

#include "Board.h"
#include "drvAUDIO.h"
#include "msAPI_audio.h"
#include "apiAUDIO.h"

#include "msAPI_Ram.h"
#include "msAPI_Timer.h"
#include "drvXC_HDMI_if.h"
#include "apiXC_Hdmi.h"

#include "apiXC.h"
#include "apiXC_Adc.h"


#include "drvXC_HDMI_if.h"
#include "apiXC_Sys.h"
#include "msAPI_MIU.h"

#include "drvPM.h"
#include "drvGPIO.h"

#include "MApp_SaveData.h"
#include "MApp_PCMode.h"

#include "MApp_GlobalFunction.h"


#if ENABLE_SECURITY_R2_HDCP22
#include "msAPI_SecurityR2.h"
#include "drvHDCPRx.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define msg_hdmi(x)                 //x
#define HDMI_AUDIO_STABLE_CNT       (40)



// In 199M case, audio on->off->on->off->on, so, we wait 4 * HDMI_AUDIO_STABLE_CNT, if unstable,
// enable audio still to prevent mute audio always because of un-stable
#define HDMI_AUDIO_FORCE_ENABLE         (HDMI_AUDIO_STABLE_CNT*2)
#define COLOR_PKG_TIMEOUT_TIME 200

// AV MUTE/UNMUTE STABLE COUNT
#define HDMI_AV_MUTE_STABLE_COUNT   2
#define HDMI_AV_UNMUTE_STABLE_COUNT 10

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

HDMI_PACKET_INFO_t      g_HdmiPacketInfo;
static XC_HDMI_InitData _stXC_HDMI_InitData;
//#0585821 [HDMI certification] When sink's AVI InfoFrame change YCbCr to No AVI InfoFrame, there is no nomal RGB output.
static MS_BOOL bStatus_NoAviNullPkg = 0;        // 0 : in NoAviNull pagckage status   1: in AviNull package status
static MS_BOOL bNoAvi_BounceTime = FALSE;
static MS_U32 u16TimeOut_NoAviNullPkg = 0 ;

//------------------------------------------------------------------------------

typedef struct
{
    EnuHdmiHpdStatus eHpdStatus;
    EnuHdmiClkStatus eClkStatus;

    U32 u32SetHpdTime;
    U32 u32SetClkTime;
} StuHdmiPortStatus;

static StuHdmiPortStatus s_HDMI_aePortStatus[4];

//------------------------------------------------------------------------------
static U32 g_HDMI_u32Receive_GC_Packet_LastTime = 0;


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

void MApi_XC_HDMI_InitVar_PortStatus(void)
{
    U8 u8PortIdx;

    memset(s_HDMI_aePortStatus, 0, sizeof(s_HDMI_aePortStatus) );

    for( u8PortIdx = 0; u8PortIdx < 4; u8PortIdx += 1 )
    {
        s_HDMI_aePortStatus[u8PortIdx].eHpdStatus = HDMI_HPD_STATUS_UNKNOWN;
        s_HDMI_aePortStatus[u8PortIdx].eClkStatus = HDMI_CLK_STATUS_UNKNOWN;
    }
}

void MApi_XC_HDMI_Set_HpdStatus(E_MUX_INPUTPORT enInputPortType, EnuHdmiHpdStatus eHpdStatus)
{
    if( enInputPortType < INPUT_PORT_DVI0 || enInputPortType > INPUT_PORT_DVI3 )
        return;

    U8 u8PortIdx = enInputPortType - INPUT_PORT_DVI0;

    s_HDMI_aePortStatus[u8PortIdx].eHpdStatus = eHpdStatus;

    //MApi_XC_HDMI_Print_PortStatus();
}

EnuHdmiHpdStatus MApi_XC_HDMI_Get_HpdStatus(E_MUX_INPUTPORT enInputPortType)
{
    if( enInputPortType < INPUT_PORT_DVI0 || enInputPortType > INPUT_PORT_DVI3 )
        return HDMI_HPD_STATUS_UNKNOWN;

    U8 u8PortIdx = enInputPortType - INPUT_PORT_DVI0;

    return s_HDMI_aePortStatus[u8PortIdx].eHpdStatus;
}

void MApi_XC_HDMI_Set_ClkStatus(E_MUX_INPUTPORT enInputPortType, EnuHdmiClkStatus eClkStatus)
{
    if( enInputPortType < INPUT_PORT_DVI0 || enInputPortType > INPUT_PORT_DVI3 )
        return;

    U8 u8PortIdx = enInputPortType - INPUT_PORT_DVI0;

    s_HDMI_aePortStatus[u8PortIdx].eClkStatus = eClkStatus;
    //MApi_XC_HDMI_Print_PortStatus();
}

void MApi_XC_HDMI_Print_PortStatus(void)
{
    U8 u8PortIdx;

    printf("\nHDMI port status: --------------------------------------------\n");
    for( u8PortIdx = 0; u8PortIdx < 4; u8PortIdx += 1 )
    {
        printf("%u Hpd=%u, Clk=%u\n", u8PortIdx, s_HDMI_aePortStatus[u8PortIdx].eHpdStatus, s_HDMI_aePortStatus[u8PortIdx].eClkStatus);
    }
    printf("----------------------------------------------------------------\n");
}

//******************************************************************************
//  [Function Name]:
//      U16 MApi_XC_HDMI_Func_Caps(void)
//  [Description]:
//      This routine is used to get the needed function list for HDMI.
//   Some chips don't need specific function, we can get this infomation
//   throught this interface
//  [Arguments]:
//      None:
//  [Return]:
//      None,
//*******************************************************************************
U16 MApi_XC_HDMI_Func_Caps(void)
{
    return MDrv_HDMI_Func_Caps();
}

#if (INPUT_HDMI_VIDEO_COUNT > 0)

char* MApi_HDMI_Get_ColorFormatString(U8 u8ColorFormat)
{
    char* pStr = "MS_HDMI_COLOR_UNKNOWN";

    switch( u8ColorFormat )
    {
        case MS_HDMI_COLOR_RGB:
            pStr = "MS_HDMI_COLOR_RGB";
            break;

        case MS_HDMI_COLOR_YUV_422:
            pStr = "MS_HDMI_COLOR_YUV_422";
            break;

        case MS_HDMI_COLOR_YUV_444:
            pStr = "MS_HDMI_COLOR_YUV_444";
            break;

        case MS_HDMI_COLOR_RESERVED:
            pStr = "MS_HDMI_COLOR_RESERVED";
            break;

        default:
        case MS_HDMI_COLOR_UNKNOWN:
            break;
    }

    return pStr;
}

//******************************************************************************
//  [Function Name]:
//      void _MDrv_HDMI_audio_downsample(void)
//  [Description]:
//      This routine is used to set HDMI audio sample rate below 48K.
//      crystal: 12MHz(216MHz)
//  [Arguments]:
//      None:
//  [Return]:
//      None,
//*******************************************************************************
void _MDrv_HDMI_audio_downsample(void)
{
    MS_U8  temp;
    MS_U16 freq;
    freq = MApi_AUDIO_HDMI_GetSynthFreq(); //freq = MDrv_AUDIO_ReadByte(0x2C2C) + 0x100 * MDrv_AUDIO_ReadByte(0x2C2D);
                                           //if(freq & 0x8000) return;   //no signal
    if ( freq )
    {
        if ( freq < (0x08CA-20) )      //> 96K
        {
            temp = 2;
        }
        else if ( freq < (0x1194-20) ) //> 48K
        {
            temp = 1;
        }
        else
        {
            temp = 0;
        }
    }
    else
    {
        temp = 4;
    }

    MApi_AUDIO_HDMI_SetDownSample(temp); //MDrv_AUDIO_WriteMaskByte(0x2C48, 0x03, temp);
}

//=========================================================//
// Function : _MApi_XC_HDMI_CheckMode
// Description: check HDMI or DVI
//=========================================================//
static BOOLEAN _MApi_XC_HDMI_CheckMode( BOOLEAN bImmediately )
{
    static U8 u8CheckDebounce = 0;
    MS_HDCP_STATUS_INFO_t *enStatus_info;
    enStatus_info = MDrv_HDCP_GetStatus();

#if 0 // Daniel_Test
    static MS_HDCP_STATUS_INFO_t eHDCP_Status_Last;
    if( 0 != memcmp( (U8*)&eHDCP_Status_Last, (U8*)enStatus_info, sizeof(MS_HDCP_STATUS_INFO_t) ) )
    {
        printf("HDCP Status change: \n");
        Print_Buffer( (U8*)&eHDCP_Status_Last, sizeof(MS_HDCP_STATUS_INFO_t) );
        Print_Buffer( (U8*)enStatus_info, sizeof(MS_HDCP_STATUS_INFO_t) );
        eHDCP_Status_Last = *enStatus_info;
    }
#endif

    if((enStatus_info->b_St_HDMI_Mode != g_HdmiPollingStatus.bIsHDMIMode) || (enStatus_info->b_St_HDMI_Mode && bImmediately))
    {
        if(!bImmediately)
        {
            if(u8CheckDebounce++ < 3)
                return FALSE;
        }
        u8CheckDebounce = 0;

        msg_hdmi(printf("\r\ncheck hdmi input is Change %s\n", enStatus_info->b_St_HDMI_Mode ? "HDMI" : "DVI"));

        // if DVI -> HDMI or DVI -> HDMI
        // SimplayHD 8-26: Auto Clear AVMute After DVI Transition
        // (HDMI -> DVI): The previous state DUT would be received "AVMUTE" from test equipment
        //   with HDMI signal. After a while, test equipment would change signal from HDMI to DVI. Then DUT shall automatically clear AVMUTE by itself.
        if(enStatus_info->b_St_HDMI_Mode != g_HdmiPollingStatus.bIsHDMIMode)
        {
            //MDrv_HDMI_pkt_reset(REST_HW_HDMI);
            MDrv_HDMI_pkt_reset(REST_AVMUTE|REST_Y_COLOR|REST_PIXEL_REPETITION|REST_FRAME_REPETITION|REST_GCP_PKT|REST_HDMI_STATUS);
            msg_hdmi(printf("HDMI HW reset\n"));
        }
        g_HdmiPollingStatus.bIsHDMIMode = enStatus_info->b_St_HDMI_Mode;

        return TRUE;
    }

    return FALSE;
}

BOOLEAN MApi_XC_HDMI_CheckSumAndBCH(INPUT_SOURCE_TYPE_t enInputSourceType)
{
    if ( g_HdmiPacketInfo.enPKT_Status.ChecksumErrOrBCHParityErr ) // BCH & Checksum error
    {
        printf("\n ChecksumErrOrBCHParityErr:  at %u\n", MsOS_GetSystemTime() );

        if ( g_HdmiPollingStatus.u8LostHDMICounter < 255 )
            g_HdmiPollingStatus.u8LostHDMICounter ++;

        printf(" u8LostHDMICounter=%u\n", g_HdmiPollingStatus.u8LostHDMICounter);

        if ( g_HdmiPollingStatus.u8LostHDMICounter > 4 )
        {
            {
                if( (m_eAudioSource>=E_AUDIOSOURCE_HDMI) && (m_eAudioSource<=E_AUDIOSOURCE_HDMI3))
                {
                    MW_AUD_SetSoundMute(SOUND_MUTE_TV, E_MUTE_ON);
                }
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, MAIN_WINDOW);
                printf("\n BCH or Checksum error\n");
            }

            if ( g_HdmiPollingStatus.u8LostHDMICounter == 10 )
            {
                printf("\n u8LostHDMICounter=10 => Reset XC IP\n");
                MApi_XC_SoftwareReset(REST_IP_F2, MAIN_WINDOW);
                MsOS_DelayTask( 250 );
            }
            else if ( g_HdmiPollingStatus.u8LostHDMICounter == 30 )
            {
                printf("\n u8LostHDMICounter=30 => Set HPD\n");

                //E_MUX_INPUTPORT enHDMIPort =  MApi_XC_Mux_GetHDMIPort(enInputSourceType);
                //MApi_XC_Sys_SetHPD( DISABLE, enHDMIPort);
                //MsOS_DelayTask( HDMI_HPD_DELAY);
                //MApi_XC_Sys_SetHPD( ENABLE, enHDMIPort);
                MApi_XC_Sys_Do_HPD( enInputSourceType );
            }

            return FALSE;
        }
    }
    else
    {
        if( g_HdmiPollingStatus.u8LostHDMICounter )
        {
            printf(" u8LostHDMICounter=%u => 0\n", g_HdmiPollingStatus.u8LostHDMICounter);
            g_HdmiPollingStatus.u8LostHDMICounter = 0;
        }
    }

    return TRUE;
}

BOOLEAN MApi_XC_HDMI_CheckColor(void)
{
    BOOL bColorChange = FALSE;

    if( g_HdmiPacketInfo.enPKT_Value.PKT_AVI_VALUE // If got AVI packet
     && (g_HdmiPacketInfo.enPKT_Status.PacketColorFormat != MS_HDMI_COLOR_UNKNOWN )
      )
    {
        if(g_HdmiPollingStatus.u8ColorFormat != g_HdmiPacketInfo.enPKT_Status.PacketColorFormat)
        {
            printf("[HDMI] Color change: %u(%s) => %u(%s)\n",
                g_HdmiPollingStatus.u8ColorFormat, MApi_HDMI_Get_ColorFormatString(g_HdmiPollingStatus.u8ColorFormat),
                g_HdmiPacketInfo.enPKT_Status.PacketColorFormat, MApi_HDMI_Get_ColorFormatString(g_HdmiPacketInfo.enPKT_Status.PacketColorFormat));

            //DEBUG_HDMI_COLOR( printf("g_HdmiPollingStatus.bColorFMTChange = 1;\n"); );
            g_HdmiPollingStatus.bColorFMTChange = 1;

            bColorChange = TRUE;

            g_HdmiPollingStatus.u8ColorFormat = g_HdmiPacketInfo.enPKT_Status.PacketColorFormat;
        }
    }
    else
    {
    #if 0
        g_HdmiPacketInfo.enPKT_Status.PacketColorFormat = MS_HDMI_COLOR_DEFAULT;

        DEBUG_HDMI_COLOR( printf("[HDMI] NO AVI => Real=%u\n", g_HdmiPacketInfo.enPKT_Status.PacketColorFormat); );

        // #0585821 [HDMI certification] When sink's AVI InfoFrame change YCbCr to No AVI InfoFrame, there is no nomal RGB output.
        // No in NoAviNull status
        if ( g_HdmiPollingStatus.u8ColorFormat != g_HdmiPacketInfo.enPKT_Status.PacketColorFormat )
        {
            DEBUG_HDMI_COLOR( printf("[HDMI] Polling=%u != Real=%u\n", g_HdmiPollingStatus.u8ColorFormat, g_HdmiPacketInfo.enPKT_Status.PacketColorFormat); );
            g_HdmiPollingStatus.bColorFMTChange = 1;
            g_HdmiPollingStatus.u8ColorFormat = g_HdmiPacketInfo.enPKT_Status.PacketColorFormat;
        }
        else
        {
            g_HdmiPollingStatus.bColorFMTChange = 0;
        }
    #endif
    }

#if 0
    msg_hdmi(printf(" u8ColorFormat %s \r\n",
        (g_HdmiPollingStatus.u8ColorFormat == MS_HDMI_COLOR_RGB)? "MS_HDMI_COLOR_RGB"
        :(g_HdmiPollingStatus.u8ColorFormat == MS_HDMI_COLOR_YUV_422)? "MS_HDMI_COLOR_YUV_422"
        :(g_HdmiPollingStatus.u8ColorFormat == MS_HDMI_COLOR_YUV_444)? "MS_HDMI_COLOR_YUV_444"
        :(g_HdmiPollingStatus.u8ColorFormat == MS_HDMI_COLOR_DEFAULT)? "MS_HDMI_COLOR_DEFAULT"
        :(g_HdmiPollingStatus.u8ColorFormat == MS_HDMI_COLOR_RESERVED)? "MS_HDMI_COLOR_RESERVED"
        :"MS_HDMI_COLOR_UNKNOWN" ));
#endif

    return bColorChange;
}

#define HDMI_TASK_CHECK()     //CHECK_MIU_PROTECT_LOG_AND_CLEAR()

BOOLEAN MApi_XC_HDMI_Monitor( INPUT_SOURCE_TYPE_t enInputSourceType)
{
    BOOLEAN bResult = TRUE;

    if ( !g_HdmiPollingStatus.bIsHDMIMode )
        return FALSE;


    //printf("MApi_XC_HDMI_Monitor() at %u\n", MsOS_GetSystemTime());

    // count down some timers (everytime executed this function takes HDMI_POLLING_COUNTER ms)
    //g_AVMUTEMissingCounter = (g_AVMUTEMissingCounter > HDMI_POLLING_COUNTER) ?
    //    (g_AVMUTEMissingCounter - HDMI_POLLING_COUNTER) : 0;
    //printf("g_AVMUTEMissingCounter=%u\n", g_AVMUTEMissingCounter);

    g_AVIMissingCounter = (g_AVIMissingCounter > HDMI_POLLING_COUNTER) ?
        (g_AVIMissingCounter - HDMI_POLLING_COUNTER) : 0;

   g_ACPMissingCounter = (g_ACPMissingCounter > HDMI_POLLING_COUNTER) ?
        (g_ACPMissingCounter - HDMI_POLLING_COUNTER) : 0;

    HDMI_TASK_CHECK();
    // Get Packet Info
    MApi_XC_HDMI_CheckPacketInfo();

    HDMI_TASK_CHECK();

    if( (m_eAudioSource>=E_AUDIOSOURCE_HDMI) && (m_eAudioSource<=E_AUDIOSOURCE_HDMI3))
    {
        _MDrv_HDMI_audio_downsample();
    }

    HDMI_TASK_CHECK();

    if(g_HdmiPacketInfo.enPKT_Value.PKT_GC_VALUE)
    {
        msg_hdmi(printf(" PKT_GC_VALUE == FALSE %bu \r\n", g_HdmiPacketInfo.enPKT_Value.PKT_GC_VALUE));
        if ( g_HdmiPacketInfo.enPKT_Status.AVMuteStatus ) // AV Mute control
        {
            bResult = FALSE;
            msg_hdmi(printf(" AVMuteStatus %bu \r\n", g_HdmiPacketInfo.enPKT_Status.AVMuteStatus));
            if ( !g_HdmiPollingStatus.bMuteHDMIVideo )
            {
                g_HdmiPollingStatus.bMuteHDMIVideo = 1;
                g_HdmiPollingStatus.u8LostHDMICounter = 0;

                printf("[HDMI] av_mute = 1\n");

                HDMI_TASK_CHECK();
                if( (m_eAudioSource>=E_AUDIOSOURCE_HDMI) && (m_eAudioSource<=E_AUDIOSOURCE_HDMI3))
                {
                   // MW_AUD_SetSoundMute(SOUND_MUTE_TV, E_MUTE_ON);
                   msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_HDMI_AVMUTE_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
                HDMI_TASK_CHECK();

                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_HDMI_AVMUTE, ENABLE, 0, MAIN_WINDOW);

                HDMI_TASK_CHECK();
            }

            goto exit_SetHDMI_Video;
        }
    }

    HDMI_TASK_CHECK();

//   For audio to play, has to check audioPktErr,
    // audioSamplePKT (audio data) and ACR_PKT (audio clock)
    //
    // Sometimes the player will send audio signal after video showed up like this:
    //
    //  (after video showed up)
    //  audioPktErr     |  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  (0 forever)
    //  ACR_PKT         |  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  (1 forever)
    //  audioSamplePKT  |  1 1 1 0 0 1 1 0 0 0 1 1 1 1 1 1  (1 forever)
    //
    // The unstable time is un-predictable.
    //
    // In this case, we use u8AudioStbCnt to wait for stable.
    // But if the player is always un-stable, we'll have no chance to play audio.
    //
    //   So, if u8AudioForceEnableCnt (audioPktErr=0, ACR_PKT=1, audioSamplePKT=1)
    // greater than HDMI_AUDIO_FORCE_ENABLE, after that, we'll turn on audio only if
    // (audioPktErr=0, ACR_PKT=1, audioSamplePKT=1), else, we'll turn audio off.
    //
    //   By doing so, the user could hear the abnormal sounds even the input audio
    // is always un-stable.
    if((g_HdmiPacketInfo.enPKT_Status.AudioPacketErr ) ||
        (!(g_HdmiPacketInfo.enPKT_Value.PKT_ASAMPLE_VALUE)) ||
        (!(g_HdmiPacketInfo.enPKT_Value.PKT_ACR_VALUE)))
    {
        g_HdmiPollingStatus.bMuteHDMIAudio = TRUE;
        g_HdmiPollingStatus.u8AudioStbCnt = 0;
    }
    else if(g_HdmiPacketInfo.enPKT_Value.PKT_AUI_VALUE )
    {
        if((g_HdmiPollingStatus.u8AudioStbCnt > HDMI_AUDIO_STABLE_CNT) ||
            (g_HdmiPollingStatus.u8AudioForceEnableCnt > HDMI_AUDIO_FORCE_ENABLE))
        {
            g_HdmiPollingStatus.bMuteHDMIAudio = 0;
        }
        else
        {
            g_HdmiPollingStatus.u8AudioStbCnt++;
            g_HdmiPollingStatus.u8AudioForceEnableCnt++;
        }
    }

    HDMI_TASK_CHECK();

    // Check color space
    if ( ( g_HdmiPacketInfo.enPKT_Value.PKT_AVI_VALUE ) || (g_HdmiPacketInfo.enPKT_Value.PKT_NULL_VALUE ) )
    {
        g_HdmiPollingStatus.u8LostHDMICounter = 0;

        // For lossing pkg
        bStatus_NoAviNullPkg = FALSE;   // Reset Status
        bNoAvi_BounceTime = FALSE;      // Clear

        // If not receive AVI packet
        if ( g_HdmiPacketInfo.enPKT_Value.PKT_AVI_VALUE )
        {
            //we need to monitor aspectratio...
            msg_hdmi(printf(" bAVI_PKT_Received? OK %bu \r\n", (U8)g_HdmiPacketInfo.enPKT_Value.PKT_AVI_VALUE));
        }
        else
        {
        #if 0
            msg_hdmi(printf(" g_HdmiPollingStatus.bAVI_PKT_Received NO!! %bu \r\n", g_HdmiPacketInfo.enPKT_Value.PKT_AVI_VALUE));

            if ( g_HdmiPacketInfo.enPKT_Value.PKT_NULL_VALUE )
            {
                msg_hdmi(printf(" bNULL_PKT_Received? %bu \r\n", (U8)g_HdmiPacketInfo.enPKT_Value.PKT_NULL_VALUE));
                if ( g_HdmiPollingStatus.u8ColorFormat == MS_HDMI_COLOR_UNKNOWN )
                {
                    g_HdmiPollingStatus.u8ColorFormat = MS_HDMI_COLOR_DEFAULT;
                    DEBUG_HDMI_COLOR( printf("[HDMI] NULL PKT => Polling.Color = Default=%u(%s)\n", g_HdmiPollingStatus.u8ColorFormat, MApi_HDMI_Get_ColorFormatString(g_HdmiPollingStatus.u8ColorFormat)); );
                }
            }
        #endif
        }

        if ( g_HdmiPollingStatus.u8ColorFormat == g_HdmiPacketInfo.enPKT_Status.PacketColorFormat )
        {
            //20100224, Fix BBK DVD don't send AVI_PKT first then send, and make video/Audio be Muted issue.
            if(g_HdmiPollingStatus.bMuteHDMIVideo && g_HdmiPacketInfo.enPKT_Status.AVMuteStatus)
                bResult = TRUE;
            else
            {
                if(g_HdmiPollingStatus.bMuteHDMIVideo)
                {
                    HDMI_TASK_CHECK();
                    g_HdmiPollingStatus.bMuteHDMIVideo = 0;//clear the flag set by u8LostHDMICounter.

                    printf("[HDMI] av_mute = 0\n");

                    if( (m_eAudioSource>=E_AUDIOSOURCE_HDMI) && (m_eAudioSource<=E_AUDIOSOURCE_HDMI3))//Added by jiangtao 2010-03-12
                    {
                        //MW_AUD_SetSoundMute(SOUND_MUTE_TV, E_MUTE_OFF);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_HDMI_AVMUTE_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        msg_hdmi(printf("\t Audio unMute ... \r\n"));
                    }
                    HDMI_TASK_CHECK();

                #if(ENABLE_HW_DETECT_HDMI_AVMUTE) // HW_AUTO_DISABLE_INPUTSOURCE_WHEN_HDMI_AVMUTE
                    // If enable HW auto detect AVMute=1, HW will auto set "DisableInputSource" to 1,
                    // but it will not set "DisableInputSource" to 0,
                    // So SW need set "DisableInputSource" to 0 here~
                    if( FALSE == MApi_XC_Sys_Get_BlueScreenStatus(MAIN_WINDOW))
                    {
                        msAPI_XC_Sys_Set_DisableInput(FALSE, MAIN_WINDOW); //MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
                    }
                #endif

                    HDMI_TASK_CHECK();

                    // Enable timer mute-client for garbage~
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 100, MAIN_WINDOW);

                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_HDMI_AVMUTE, DISABLE, 0, MAIN_WINDOW);

                    //MApp_UI_NotifySysEvent(E_SYS_EVENT_HDMI_AVMUTE_1_TO_0, NULL);

                    HDMI_TASK_CHECK();

                    msg_hdmi(printf("\t Video unMute ... \r\n"));
                }
                bResult = FALSE;
            }

            goto exit_SetHDMI_Video;
        }

        HDMI_TASK_CHECK();
        MApi_XC_HDMI_CheckColor();
        HDMI_TASK_CHECK();

    }
    else
    {
        bResult = FALSE;

        HDMI_TASK_CHECK();

        // #0585821 [HDMI certification] When sink's AVI InfoFrame change YCbCr to No AVI InfoFrame, there is no nomal RGB output.
        // No in NoAviNull status
        if ( !bStatus_NoAviNullPkg && !bNoAvi_BounceTime)
        {
            u16TimeOut_NoAviNullPkg = MsOS_GetSystemTime() + COLOR_PKG_TIMEOUT_TIME;
            bNoAvi_BounceTime = TRUE;
        }
        else if ( !bStatus_NoAviNullPkg && bNoAvi_BounceTime)
        {
            if ( u16TimeOut_NoAviNullPkg  < MsOS_GetSystemTime() ) // TimeOut
            {
                bNoAvi_BounceTime = FALSE;
                bStatus_NoAviNullPkg = TRUE;

                // Reset Color format
                g_HdmiPacketInfo.enPKT_Status.PacketColorFormat = MS_HDMI_COLOR_DEFAULT;

                DEBUG_HDMI_COLOR( printf("[HDMI] Reset PktColr=%u\n", g_HdmiPacketInfo.enPKT_Status.PacketColorFormat); );

                MApi_XC_HDMI_CheckColor();
            }
        }

        HDMI_TASK_CHECK();

        msg_hdmi( printf(" bAVI_PKT_Received  %bu \r\n", g_HdmiPacketInfo.enPKT_Value.PKT_AVI_VALUE));
        msg_hdmi( printf(" bNULL_PKT_Received %bu \r\n", g_HdmiPacketInfo.enPKT_Value.PKT_NULL_VALUE));
        {
            //For fail case ===================>
       		bResult=MApi_XC_HDMI_CheckSumAndBCH(enInputSourceType);
            //<=================== For fail case
        }

        HDMI_TASK_CHECK();

        goto exit_SetHDMI_Video;
    }


    exit_SetHDMI_Video:

    HDMI_TASK_CHECK();

    return bResult;
}

BOOLEAN MApi_XC_HDMI_CheckModeChanged( BOOLEAN bImmediately, SCALER_WIN eWindow )
{
    UNUSED(eWindow);

    // HDMI <-> DVI or HDMI set mode
    if(_MApi_XC_HDMI_CheckMode(bImmediately))
    {
        // if HDMI mode, clear packet buffers
        g_HdmiPollingStatus.u8AudioStbCnt = 0;
        g_HdmiPollingStatus.u8AudioForceEnableCnt= 0;

        g_HdmiPacketInfo.enPKT_Value = MDrv_HDMI_Packet_Received(DISABLE) ;
        g_HdmiPacketInfo.enPKT_Status.AVMuteStatus = 0;
        g_HdmiPacketInfo.enPKT_Status.AudioNotPCM = 0;
        g_HdmiPacketInfo.enPKT_Status.PreAudiostatus = 0xFF;
        g_HdmiPacketInfo.enPKT_Status.ChecksumErrOrBCHParityErr = 0;
        g_HdmiPacketInfo.enPKT_Status.PacketColorFormat = MS_HDMI_COLOR_UNKNOWN;
        g_HdmiPacketInfo.enPKT_Status.AspectRatio = HDMI_AR_INIT_VALUE;

        // 20100423.DanielWu: Why call MApi_XC_DisableInputSource() here??
        //MApi_XC_DisableInputSource( DISABLE, eWindow );
        //printf("Call MApi_XC_DisableInputSource( DISABLE, eWindow )\n  %u:%s\n", __LINE__, __FILE__ );

        //MDrv_SC_fielddetect(enInputSourceType, &g_VideoDisplayWindow_t);

        return TRUE;
    }


    // Here return TRUE will cause mode change!
    // But, Color change should not mode change!!
    /*
    if(g_HdmiPollingStatus.bColorFMTChange == TRUE)
    {
        g_HdmiPollingStatus.bColorFMTChange = FALSE;
        return TRUE;
    }
    */

    return FALSE;

}

E_XC_HDMI_Status MApi_XC_HDMI_GetHdmiType(INPUT_SOURCE_TYPE_t enInputSourceType)
{
    if(IsSrcTypeHDMI(enInputSourceType))
    {
        if(g_HdmiPollingStatus.bIsHDMIMode)
            return E_HDMI_STATUS_HDMI;
        else
            return E_HDMI_STATUS_DVI;
    }
    else
    {
        return E_HDMI_STATUS_UNKNOWN;
    }
}

#define ENABLE_DEBUG_HDMI_COLOR 0

#if(ENABLE_DEBUG_HDMI_COLOR)
U8 g_HDMI_ForceColorFormat = 0;
#endif

static U8 s_HDMI_u8UnMuteStableCount=0, s_HDMI_u8MuteStableCount=0;

void MApi_XC_HDMI_Reset_Packet_State_Variable(void)
{
    s_HDMI_u8UnMuteStableCount = 0;
    s_HDMI_u8MuteStableCount = 0;
}

void MApi_XC_HDMI_Packet_State(MS_HDMI_PACKET_STATE_t u8state)
{
    U16 u16MuteFlag;
    U8 u8ACPType;


    switch(u8state)
    {
        case PKT_AVI:
            {
                U8 u8CurColorFormat = MDrv_HDMI_Get_ColorFormat();

            #if(ENABLE_DEBUG_HDMI_COLOR)
                if( g_HDMI_ForceColorFormat )
                {
                    if( g_HDMI_ForceColorFormat == 1 )
                        u8CurColorFormat = MS_HDMI_COLOR_RGB;
                    else if( g_HDMI_ForceColorFormat == 2 )
                        u8CurColorFormat = MS_HDMI_COLOR_YUV_422;
                    else //if( g_HDMI_ForceColorFormat == 1 )
                        u8CurColorFormat = MS_HDMI_COLOR_YUV_444;
                }
            #endif

                if( g_HdmiPacketInfo.enPKT_Status.PacketColorFormat != u8CurColorFormat )
                {
                    DEBUG_HDMI_COLOR( printf("[HDMI] PktColor =%u(%s)\n", u8CurColorFormat, MApi_HDMI_Get_ColorFormatString(u8CurColorFormat) ); );
                    g_HdmiPacketInfo.enPKT_Status.PacketColorFormat = u8CurColorFormat;
                }

                g_HdmiPacketInfo.enPKT_Status.AspectRatio = MDrv_HDMI_Get_AspectRatio(ENABLE, ENABLE); //(bEn_PAR, bEn_AFAR)
            }
            break;

        case PKT_GC:
            if(g_HdmiPacketInfo.enPKT_Value.PKT_GC_VALUE)
            {
                u16MuteFlag = MDrv_HDMI_GC_Info(G_CTRL_AVMUTE);

                if( u16MuteFlag )
                {
                    s_HDMI_u8UnMuteStableCount = 0; // Clear unmute count
                    //if( u8MuteStableCount < 20 )
                    if( s_HDMI_u8MuteStableCount < HDMI_AV_MUTE_STABLE_COUNT )
                    {
                        s_HDMI_u8MuteStableCount ++;
                    }
                    else
                    {
                        g_HdmiPacketInfo.enPKT_Status.AVMuteStatus = TRUE;
                    }

                    // Check screen mute flag
                    if( msAPI_Scaler_GetScreenMute(MAIN_WINDOW) == 0 )
                    {
                        printf("\nWarning: Need to mute~\n");
                    }
                }
                else
                {
                    s_HDMI_u8MuteStableCount = 0; // Clear mute count
                    //if( u8UnMuteStableCount < 10 )
                    if( s_HDMI_u8UnMuteStableCount < HDMI_AV_UNMUTE_STABLE_COUNT )
                    {
                        s_HDMI_u8UnMuteStableCount ++;
                    }
                    else
                    {
                        g_HdmiPacketInfo.enPKT_Status.AVMuteStatus = FALSE;
                    }
                }
            }
            else // No GC packet received
            {
                printf("No GC packet ==> AVMuteStatus=0\n");
                g_HdmiPacketInfo.enPKT_Status.AVMuteStatus = FALSE;
                s_HDMI_u8MuteStableCount = 0;
                s_HDMI_u8UnMuteStableCount = 0;
            }
            break;

        case PKT_ACP:
            if(g_HdmiPacketInfo.enPKT_Value.PKT_ACP_VALUE)
            {
                u8ACPType = MDrv_HDMI_audio_cp_hdr_info();

                //[DF140322-00668][HDMI certification] there is optical output in ACP Type=2 audio.
                if(u8ACPType >= 2)
                {
                    MApi_AUDIO_SPDIF_HWEN(FALSE);
                }
                else
                {
                    MApi_AUDIO_SPDIF_HWEN(TRUE);
                }
            }
            else
            {
                MApi_AUDIO_SPDIF_HWEN(TRUE);
            }
            break;

        case PKT_MPEG:
        case PKT_AUI:
        case PKT_SPD:
        case PKT_ASAMPLE:
        case PKT_ACR:
        case PKT_VS:
#if ENABLE_3D_PROCESS
            {
                if(E_HDMI_3D_FORMAT == MDrv_HDMI_Check_Additional_Format())
                {
                    g_HdmiInput3DFormatStatus = MDrv_HDMI_Get_3D_Structure();
                }
                else
                {
                    g_HdmiInput3DFormatStatus = E_XC_3D_INPUT_MODE_NONE;
                }
            }
#endif

        case PKT_NULL:
        case PKT_ISRC2:
        case PKT_ISRC1:
        case PKT_ONEBIT_AUD:
            break;
        default:
            break;
    }
}

const HDMI_PACKET_INFO_t *MApi_XC_HDMI_GetPacketInfo(void)
{
    return &g_HdmiPacketInfo;
}

void MApi_XC_HDMI_CheckPacketInfo(void)
{
    U8 u8Err = 0;

    //printf("MApi_XC_HDMI_CheckPacketInfo() at %u\n", MsOS_GetSystemTime());

    g_HdmiPacketInfo.enPKT_Value = MDrv_HDMI_Packet_Received(ENABLE);

// SimplayHD 8-25: Auto Clear AVMute After 5 Seconds
// -In HDMI mode, the previous state DUT would be received "AVMUTE" from test equipment.
//   If "SET_AVMUTE" is not received within 5 sec, DUT shall automatically clear AVMUTE by itself.
    if( g_HdmiPacketInfo.enPKT_Value.PKT_GC_VALUE )
    {
        MApi_XC_HDMI_Packet_State(PKT_GC);
        //g_AVMUTEMissingCounter = 5000;
        g_HDMI_u32Receive_GC_Packet_LastTime = MsOS_GetSystemTime();
    }
    else
    {
        //if((g_AVMUTEMissingCounter <= 2*HDMI_POLLING_COUNTER) && (g_AVMUTEMissingCounter > 0))  // in order to reset once if there is no more GCP received in a while
        if( (g_HDMI_u32Receive_GC_Packet_LastTime != 0)
          &&( msAPI_Timer_DiffTime_2(g_HDMI_u32Receive_GC_Packet_LastTime, MsOS_GetSystemTime()) > 5000 )
          )
        {
            msg_hdmi(printf("SimplayHD 8-25: AVMUTE Handling\n"));
            printf("No receive GC packet for 5 seconds~\n");

            //g_AVMUTEMissingCounter = 0;
            g_HDMI_u32Receive_GC_Packet_LastTime = 0;

            MDrv_HDMI_pkt_reset(REST_AVMUTE);

            // Reset avmute packet status
            MApi_XC_HDMI_Packet_State(PKT_GC);
        }
    }

// SimplayHD 8-20: AVI Color Space InfoFrames
// - If AVI packet is missing within 300msec, DUT shall interpret input color is RGB(default).
    if ( g_HdmiPacketInfo.enPKT_Value.PKT_AVI_VALUE )
    {
        MApi_XC_HDMI_Packet_State(PKT_AVI);
        //msg_hdmi(printf("HDMI Color is 0x%bx; Aspect Ratio is 0x%bx\n",
        //    g_HdmiPacketInfo.enPKT_Status.PacketColorFormat, g_HdmiPacketInfo.enPKT_Status.AspectRatio));
        g_AVIMissingCounter = 300;
    }
    else // No AVI packet received
    {
        if((g_AVIMissingCounter <= 2*HDMI_POLLING_COUNTER) && (g_AVIMissingCounter > 0)) // in order to reset once if there is no more AVI received in a while
        {
            msg_hdmi(printf("SimplayHD 8-20: AVI Handling\n"));
            g_AVIMissingCounter = 0;

            if( g_HdmiPacketInfo.enPKT_Status.PacketColorFormat == MS_HDMI_COLOR_UNKNOWN )
            {
                g_HdmiPacketInfo.enPKT_Status.PacketColorFormat = MS_HDMI_COLOR_RGB;
                DEBUG_HDMI_COLOR( printf("[HDMI] No AVI timeout => PktColr= RGB\n"); );
            }

             //reset AVI color information
            MDrv_HDMI_pkt_reset(REST_Y_COLOR);
        }
    }

    //DEBUG_HDMI_COLOR( printf("[HDMI-Packet] PktColr = %u\n", g_HdmiPacketInfo.enPKT_Status.PacketColorFormat); );

// SimplayHD 8-7: Audio Output Compliance
// -    If "ACP_TYPE > 2", DUT shall disable the external S/PDIF output.
// -    Or no receiving ACP packet within 600 msec, DUT shall set ACP type to 0.
    if( g_HdmiPacketInfo.enPKT_Value.PKT_ACP_VALUE)
    {
        MApi_XC_HDMI_Packet_State(PKT_ACP);
        g_ACPMissingCounter = 600;
    }
    else
    {
        if((g_ACPMissingCounter <= 2*HDMI_POLLING_COUNTER) && (g_ACPMissingCounter > 0)) // in order to reset once if there is no more ACP received in a while
        {
            MApi_XC_HDMI_Packet_State(PKT_ACP);
            msg_hdmi(printf("SimplayHD 8-7: ACP Handling\n"));
            g_ACPMissingCounter = 0;
        }
    }
#if ENABLE_3D_PROCESS
    if(g_HdmiPacketInfo.enPKT_Value.PKT_VS_VALUE)
    {
        MApi_XC_HDMI_Packet_State(PKT_VS);
    }
    else
    {
        g_HdmiInput3DFormatStatus = E_XC_3D_INPUT_MODE_NONE;
    }
#endif

#if ENABLE_HDMI_4K_2K
   //MDrv_HDMI_3D_4Kx2K_Process();//hdmi1.4 new feature
#endif

    g_HdmiPacketInfo.enPKT_Status.AudioNotPCM  = ( MDrv_HDMI_audio_channel_status(_BYTE_0) & BIT6);

    // update bChecksumErrOrBCHParityErr and clear REG_HDMI_ERR1
    u8Err = MDrv_HDMI_err_status_update(0x00, TRUE /*means READ*/);
    MDrv_HDMI_err_status_update(u8Err, FALSE /*means WRITE*/);

    g_HdmiPacketInfo.enPKT_Status.ChecksumErrOrBCHParityErr = ( u8Err & ( BIT2 | BIT1 ) );
    if( g_HdmiPacketInfo.enPKT_Status.ChecksumErrOrBCHParityErr )
    {
        printf("ChecksumErrOrBCHParityErr=0x%X\n", g_HdmiPacketInfo.enPKT_Status.ChecksumErrOrBCHParityErr);
    }

    g_HdmiPacketInfo.enPKT_Status.AudioPacketErr = ( u8Err & (BIT4 | BIT5) );
    if( g_HdmiPacketInfo.enPKT_Status.AudioPacketErr )
    {
        printf(" AudioPacketErr=0x%X\n", g_HdmiPacketInfo.enPKT_Status.AudioPacketErr);
    }

    return;
}
#endif


#ifndef DVI_NEW_Patch
//++[DVI_PATCH_01]
void MApi_XC_HDMI_CheckAndAdjustDVI(INPUT_SOURCE_TYPE_t InputSourceType)
{
    E_MUX_INPUTPORT eHDMIPort;
    static BOOLEAN bClockLessThan70MHz_o = 0xFF;
    eHDMIPort = MApi_XC_Mux_GetHDMIPort(InputSourceType);
    BOOLEAN bClockLessThan70MHz = MDrv_HDMI_SetForClockLessThan70Mhz(eHDMIPort);

    if (bClockLessThan70MHz_o != bClockLessThan70MHz)
    {
        bClockLessThan70MHz_o = bClockLessThan70MHz;
        MDrv_HDMI_dvi_adjust(bClockLessThan70MHz);
    }
}
#endif

void MApi_XC_HDCP_Vsync_end_en(MS_BOOL bStable)
{
    MDrv_HDCP_Vsync_end_en(bStable);
}

U8 MApi_XC_HDMI_Covert_InputPortToHdmiIdx(E_MUX_INPUTPORT enInputPortType)
{
    U8 u8HdmiIdx = 0;


    switch(enInputPortType)
    {
        default:
        case INPUT_PORT_DVI0:
            u8HdmiIdx = 0;
            break;

        case INPUT_PORT_DVI1:
            u8HdmiIdx = 1;
            break;

        case INPUT_PORT_DVI2:
            u8HdmiIdx = 2;
            break;

        case INPUT_PORT_DVI3:
            u8HdmiIdx = 3;
            break;

    }

    return u8HdmiIdx;
}

void MApi_XC_HDMI_SetHotPlug(MS_BOOL bEnable, E_MUX_INPUTPORT enInputPortType)
{
    MS_BOOL bInverse;

    DEBUG_HDMI_HOT_PLUG(printf( ANSI_COLOR_GREEN "\n\n@@-- %s (en=%u, port=%u) at %u\n\n" ANSI_COLOR_RESET, __FUNCTION__, bEnable, enInputPortType, MsOS_GetSystemTime() ); );

    if( enInputPortType == INPUT_PORT_NONE_PORT )
        return;

    U8 u8HdmiIdx = MApi_XC_HDMI_Covert_InputPortToHdmiIdx(enInputPortType);


  #if ENABLE_MHL//HDCP_HPD_INVERSE
    // MHL port don't need invert
    if ( (  (INPUT_SUPPORT_MHL_PATH == E_INPUT_SUPPORT_MHL_PORT_DVI0)
          &&(enInputPortType == INPUT_PORT_DVI0)  )
       ||( (INPUT_SUPPORT_MHL_PATH == E_INPUT_SUPPORT_MHL_PORT_DVI1)
          &&(enInputPortType == INPUT_PORT_DVI1) )
       ||( (INPUT_SUPPORT_MHL_PATH == E_INPUT_SUPPORT_MHL_PORT_DVI2)
          &&(enInputPortType == INPUT_PORT_DVI2) )
       ||( (INPUT_SUPPORT_MHL_PATH == E_INPUT_SUPPORT_MHL_PORT_DVI3)
          &&(enInputPortType == INPUT_PORT_DVI3) )
       )
    {
        bInverse = FALSE;//!_stXC_HDMI_InitData.bHotPlugInverse;
    }
    else
  #endif
    {
        bInverse = _stXC_HDMI_InitData.bHotPlugInverse[u8HdmiIdx];
    }


    MApi_XC_HDMI_Set_HpdStatus(enInputPortType, (bEnable?HDMI_HPD_STATUS_HIGH:HDMI_HPD_STATUS_LOW) );

    DEBUG_HDMI_HOT_PLUG(printf(ANSI_COLOR_GREEN" => call MDrv_HDMI_pullhpd( bEnable=%u, enInputPortType=%u, bInverse=%u)\n"ANSI_COLOR_RESET, bEnable, enInputPortType, bInverse););

#if ENABLE_SECURITY_R2_HDCP22
    if(bEnable)
    {
        drv_HDCPRx_InitBySystem();
    }
#endif

    MDrv_HDMI_pullhpd( bEnable, enInputPortType, bInverse);
}

void MApi_XC_HDMI_SetDVIClkPullLow(MS_BOOL bPullLow, E_MUX_INPUTPORT enInputPortType)
{
    DEBUG_HDMI_HOT_PLUG(printf( ANSI_COLOR_GREEN "\n\n@@-- %s (Port=%u, PullLow=%u,) at %u\n\n" ANSI_COLOR_RESET, __FUNCTION__, enInputPortType, bPullLow,MsOS_GetSystemTime() ); );

    if( enInputPortType == INPUT_PORT_NONE_PORT )
        return;

    MApi_XC_HDMI_Set_ClkStatus(enInputPortType, (bPullLow?HDMI_CLK_STATUS_LOW:HDMI_CLK_STATUS_HIGH) );

    MDrv_DVI_ClkPullLow(bPullLow, enInputPortType);
}

/******************************************************************************/
///-Set DVI Source and clock
///-
/******************************************************************************/
void MApi_XC_DVI_SwitchSrc(E_MUX_INPUTPORT enInputPortType )
{
    MDrv_DVI_SwitchSrc(enInputPortType);
}

static void _MApi_XC_HDMI_InitVariables ( void )
{
    //g_AVMUTEMissingCounter = 5000; // 5sec
    g_HDMI_u32Receive_GC_Packet_LastTime = 0;
    g_AVIMissingCounter = 300; // 300 msec
    g_ACPMissingCounter = 600; // 600 msec

    g_HdmiPollingStatus.bIsHDMIMode = TRUE; // default is HDMI mode, when set mode, will call MApi_XC_HDMI_CheckModeChanged(TRUE) to exam if DVI or HDMI
    g_HdmiPollingStatus.u8ColorFormat = MS_HDMI_COLOR_UNKNOWN;
    g_HdmiPollingStatus.bMuteHDMIVideo = 0;
    g_HdmiPollingStatus.u8LostHDMICounter = 0;
  #if(ENABLE_HDMI_AR_CHECK)
    g_HdmiPollingStatus.u8AspectRatio = HDMI_AR_INIT_VALUE;
  #endif

    g_HdmiPollingStatus.bColorFMTChange = 0;
    #if (ENABLE_HDMI_AUDIO_APP==TRUE)
    g_HdmiPollingStatus.bMuteHDMIAudio = TRUE;
    g_HdmiPollingStatus.bEnableNonPCM = FALSE;
    g_HdmiPollingStatus.u8AudioStbCnt = 0;
    g_HdmiPollingStatus.u8AudioForceEnableCnt= 0;
    #endif

    g_HdmiPacketInfo.enPKT_Value = MDrv_HDMI_Packet_Received(DISABLE);
    g_HdmiPacketInfo.enPKT_Status.AVMuteStatus = 0;
    g_HdmiPacketInfo.enPKT_Status.AudioNotPCM = 0;
    g_HdmiPacketInfo.enPKT_Status.PreAudiostatus = 0xFF;
    g_HdmiPacketInfo.enPKT_Status.ChecksumErrOrBCHParityErr = 0;
    g_HdmiPacketInfo.enPKT_Status.PacketColorFormat = MS_HDMI_COLOR_UNKNOWN;
    g_HdmiPacketInfo.enPKT_Status.AspectRatio = HDMI_AR_INIT_VALUE;

    MApi_XC_HDMI_Reset_Packet_State_Variable();
}

void MApi_XC_HDMI_Handler_Init(void)
{
    _MApi_XC_HDMI_InitVariables();
}

void MApi_XC_HDCP_Init(MS_U8 *pu8HDCP_Key)
{
    MDrv_HDCP_initproductionkey(pu8HDCP_Key);
}

void MApi_XC_HDCP_Status_Reset(void)
{
    MDrv_HDCP_ClearStatus();
}

void MApi_XC_HDCP_Enable(MS_BOOL bEnable)
{
    MDrv_HDCP_Enable(bEnable);
}

XC_HDMI_Result MApi_XC_HDMI_Init(XC_HDMI_InitData *pstXC_HDMI_InitData, MS_U32 u32InitDataLen)
{
#if (HDMI_NEED_SET_PACKAGE_TYPE)

    // Use the define in bd_xxx.h
    Mdrv_HDMI_SetPackageType(HDMI_DRIVER_PACKET_TYPE);

#endif // #if (HDMI_NEED_SET_PACKAGE_TYPE)


    if( u32InitDataLen != sizeof(XC_HDMI_InitData) )
    {
        printf("\nError: MApi_XC_HDMI_Init() :HDMI_Init failed because of InitData wrong\n");
        return E_XC_HDMI_FAIL;
    }

    memcpy(&_stXC_HDMI_InitData, pstXC_HDMI_InitData, sizeof(XC_HDMI_InitData));

    _MApi_XC_HDMI_InitVariables();

    MApi_XC_HDMI_InitVar_PortStatus();

    MApi_XC_HDMI_Print_PortStatus();


    MDrv_HDMI_init();

    MApi_XC_HDCP_Init(pstXC_HDMI_InitData->pu8HDCP_Key);

    if(MApi_XC_HDMI_Func_Caps() & CAPS_DVI_ADJ_70M)
    {
#ifdef DVI_NEW_Patch
        MsOS_AttachInterrupt(E_INT_IRQ_ADCDVI2RIU, (InterruptCb)_MDrv_CecRxIsr);
        MsOS_EnableInterrupt(E_INT_IRQ_ADCDVI2RIU);
#endif
    }

    return E_XC_HDMI_OK;
}

void MApi_XC_HDMI_Task(void)
{
    static U32 _s_u32LastHDMI_Task_Time = 0;
    U32 t1,t2;

    if( msAPI_Timer_DiffTime_2(_s_u32LastHDMI_Task_Time, MsOS_GetSystemTime()) < 5 )
    {
        return;
    }

    _s_u32LastHDMI_Task_Time = MsOS_GetSystemTime();

    INPUT_SOURCE_TYPE_t eInputSourceType = SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW);
    if( !IsSrcTypeHDMI(eInputSourceType) )
    {
        return;
    }

#ifndef DVI_NEW_Patch // mark the original DVI 70 MHz patch
    if( MApi_XC_HDMI_Func_Caps() & CAPS_DVI_ADJ_70M )
    {
        if( IsSrcTypeHDMI(eInputSourceType) )
        {
            MApi_XC_HDMI_CheckAndAdjustDVI(eInputSourceType);
        }
    }
#endif


    t1 = MsOS_GetSystemTime();

#if(SUPPORT_HDMI_2_0)
    // 1. enable/disable HDMI2.0 power
    // 2. Check TMDS over 3.4 GMHz to change another mode
    MDrv_HDMI_StablePolling(); // 1. enable/disable HDMI2.0 power  2. Check TMDS over 3.4 GMHz to change another mode
#endif

    t2 = MsOS_GetSystemTime();

    if( (t2-t1) > 1 )
    {
        printf(" HDMI polling use %u ms at %u\n", t2-t1, t2);

    #if 0//(DEBUG_CHG_SRC_TIME)
        //msDebug_PrintChgSrcTime("HDMI polling");
    #endif
    }

}

#if ENABLE_EDID_SWITCH

#define EDID_14_ver     1
#define EDID_20_ver     2

BOOLEAN MApi_XC_HDMI_DetectEdidVersion(INPUT_SOURCE_TYPE_t enInputSourceType)
{
    DEBUG_EDID_SWITCH( printf("MApi_XC_HDMI_DetectEdidVersion(src=%u)\n", enInputSourceType); );

    E_MUX_INPUTPORT enHDMIPort = MApi_XC_Mux_GetHDMIPort(enInputSourceType);

    DEBUG_EDID_SWITCH( printf("enHDMIPort=%u\n", enHDMIPort); );

    //if(enInputSourceType == INPUT_SOURCE_HDMI)
    {
        if(MDrv_HDMI_GetDEStableStatus(enHDMIPort) == FALSE)
        {
            DEBUG_EDID_SWITCH(printf("[HDMI-EDID] Port-%u DE UnStable\n", enHDMIPort););
            return FALSE;
        }

        DEBUG_EDID_SWITCH( printf("[HDMI-EDID] Port-%u DE Stable\n", enHDMIPort); );

        MS_U8 u8ret = MDrv_HDMI_GetSourceVersion(enHDMIPort);
        DEBUG_EDID_SWITCH( printf("[HDMI-EDID] SourceVersion=%u ", u8ret); );
        if(u8ret == EDID_14_ver)
        {
            printf("=> EDID_14_ver\n");
            MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_1p4, TRUE);

            // Reset timing monitor
            //MApp_PCMode_Reset_TimingMonitor(MAIN_WINDOW);
        }
        else if(u8ret == EDID_20_ver)
        {
            DEBUG_EDID_SWITCH( printf("=> EDID_20_ver\n"); );
        }
        else
        {
            DEBUG_EDID_SWITCH( printf("=> EDID_UNKNOW\n"); );
            return FALSE;
        }
    }

    return TRUE;
}

BOOLEAN g_bDetectHDMI1status = FALSE, g_bCurHDMI1status = TRUE, g_bLastHDMI1status = FALSE;

void MApi_XC_HDMI_EdidSwitch_ResetSM(void)
{
    g_bCurHDMI1status = FALSE;
    g_bDetectHDMI1status = FALSE;
    g_bLastHDMI1status = FALSE;
}

BOOLEAN MApi_XC_HDMI_EDID_Monitor(void)
{
    static U32 _s_u32LastHDMI_Edid_Task_Time = 0;


    if( msAPI_Timer_DiffTime_2(_s_u32LastHDMI_Edid_Task_Time, MsOS_GetSystemTime()) < 10 )
    {
        return TRUE;
    }

    _s_u32LastHDMI_Edid_Task_Time = MsOS_GetSystemTime();

    if( !IsHDMIInUse() )
        return FALSE;

    if( MApi_XC_Sys_Get_UserEdidSel() != E_USER_HDMI_EDID_AUTO )
        return FALSE;


    INPUT_SOURCE_TYPE_t enInputSourceType = stSystemInfo[MAIN_WINDOW].enInputSourceType;

    switch(enInputSourceType)
    {
        case INPUT_SOURCE_HDMI:
            g_bCurHDMI1status = HDMI1_INPUT_DETECT();
            break;
        case INPUT_SOURCE_HDMI2:
            g_bCurHDMI1status = HDMI2_INPUT_DETECT();
            break;
        case INPUT_SOURCE_HDMI3:
            g_bCurHDMI1status = HDMI3_INPUT_DETECT();
            break;
        case INPUT_SOURCE_HDMI4:
            g_bCurHDMI1status = HDMI4_INPUT_DETECT();
            break;

        default:
            printf("\nError: Unsupported src=%u\n", enInputSourceType);
            return FALSE;
    }


    //if(stSystemInfo[MAIN_WINDOW].enInputSourceType == INPUT_SOURCE_HDMI)
    {
        //g_bCurHDMI1status = HDMI1_INPUT_DETECT();

        // unplug cable, reset detect status
        if(g_bCurHDMI1status == FALSE)
        {
            g_bDetectHDMI1status = FALSE;
        }

        // from plug to unplug, reset EDID to 2.0
        if((g_bLastHDMI1status == TRUE)&&(g_bCurHDMI1status == FALSE))
        {
            printf("[EDID] plug to unplug => Reset EDID to 2.0\n");
            //printf("\r\n >>>> %s reset EDID to 2.0", __FUNCTION__);

            MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_2p0, FALSE );

            g_bLastHDMI1status = FALSE;
        }

        if(((g_bCurHDMI1status == TRUE)&&(g_bDetectHDMI1status == TRUE))
            ||((g_bCurHDMI1status == FALSE)&&(g_bDetectHDMI1status == FALSE)))
        {
            return FALSE;
        }

        //printf("\r\n >>>> %s g_bDetectHDMI1status = %d, g_bCurHDMI1status = %d", __FUNCTION__, g_bDetectHDMI1status, g_bCurHDMI1status);

        // From unplug to plug
        if( (g_bCurHDMI1status == TRUE)&&(g_bDetectHDMI1status == FALSE) )
        {
            DEBUG_EDID_SWITCH( printf("[EDID] unplug to plug\n"); );
            if( MApi_XC_HDMI_DetectEdidVersion(enInputSourceType) == TRUE )
            {
                g_bDetectHDMI1status = TRUE;
                g_bLastHDMI1status = TRUE;
            }
        }
    }

    return FALSE;
}

#endif

#undef _API_XC_HDMI_C_

