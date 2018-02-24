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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_APEngine.h
/// @brief API for AP Engine
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#define _MSAPI_APENGINE_C_

#if (ENABLE_CAPE)
/******************************************************************************/
/*                            Header Files                                    */
/* ****************************************************************************/
#include <string.h>
#include "drvGlobal.h"

#include "datatype.h"
#include "Board.h"
#include "debug.h"
#include "MsCommon.h"

#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "apiAUDIO.h"
#include "drvISR.h"
#include "drvCPU.h"
#include "msAPI_CPU.h"
#include "apiGOP.h"
#include "msAPI_MMap.h"
#include "apiGOP.h"
#include "msAPI_APEngine.h"
#include "msAPI_Music.h"
#include "msAPI_audio.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "ms_decompress.h"
#include "MApp_InputSource.h"
#include "MApp_GlobalVar.h"
#include "msAPI_Video.h"
#include "MApp_MVDMode.h"
#include "MApp_PCMode.h"
#include "MApp_Scaler.h"
#include "MApp_XC_PQ.h"


#include "drvMIU.h"

#include "sysinfo.h"


#ifdef SUPPORT_AP_BIN_IN_FLASH_2
#include "InfoBlock.h"
#endif

#include "msAPI_MPEG_Subtitle.h"
#include "MsOS.h"

#if ENABLE_DMP
#include "mapp_mplayer.h"
#endif

#include "mapp_videoplayer.h"
#include "msAPI_MailBox.h"
#include "debug.h"


#define APENGINE_MAILBOX_SEND(_class,_index,_type,_count,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10) _APEngine_SendMailboxMsg((U8)_class,(U8)_index,(MBX_MSG_Type)_type,(U8)_count,(U8) _p1,(U8) _p2,(U8) _p3,(U8) _p4,(U8) _p5,(U8) _p6,(U8) _p7,(U8) _p8,(U8) _p9,(U8) _p10)

#define ALIVE_CHECK_INTERVAL  5000        //ms

static BOOLEAN _bCAPEFinalizeIsDone, _bCAPEInitializeIsDone;
static U32 _u32CAPEAliveCount;

#if ENABLE_MPLAYER_PLUGIN
static U32 _u32RomFsSize = 0;
#endif


static void _APEngine_SendMailboxMsg(U8 _class, U8 _index, MBX_MSG_Type _type, U8 _count,
                                      U8 _p1, U8 _p2, U8 _p3, U8 _p4, U8 _p5, U8 _p6, U8 _p7, U8 _p8, U8 _p9, U8 _p10)
{
    MBX_Msg m5_mbxMsg;
    MBX_Result mbxResult;

    m5_mbxMsg.u8MsgClass            = _class;
    m5_mbxMsg.u8Index               = _index;
    m5_mbxMsg.u8ParameterCount      = _count;
    m5_mbxMsg.eMsgType              = _type;
    m5_mbxMsg.u8Parameters[0]       = _p1;
    m5_mbxMsg.u8Parameters[1]       = _p2;
    m5_mbxMsg.u8Parameters[2]       = _p3;
    m5_mbxMsg.u8Parameters[3]       = _p4;
    m5_mbxMsg.u8Parameters[4]       = _p5;
    m5_mbxMsg.u8Parameters[5]       = _p6;
    m5_mbxMsg.u8Parameters[6]       = _p7;
    m5_mbxMsg.u8Parameters[7]       = _p8;
    m5_mbxMsg.u8Parameters[8]       = _p9;
    m5_mbxMsg.u8Parameters[9]       = _p10;

    do
    {
        mbxResult = MSApi_MBX_SendMsg(&m5_mbxMsg);
        switch(mbxResult)
        {
            case E_MBX_ERR_PEER_CPU_BUSY:
            case E_MBX_ERR_PEER_CPU_NOTREADY:
            case E_MBX_ERR_PEER_CPU_NOT_ALIVE:
                //Error Handling here...
                break;
            case E_MBX_ERR_PEER_CPU_OVERFLOW:
                //MsOS_DelayTask(1);
                break;
            default:
                break;
        }
    }while(E_MBX_SUCCESS != mbxResult);
}


static void _APEngine_GWIN_Create(MBX_Msg MB_Message)
{
    //[0]:gefmt
    //[12]:width
    //[34]:height
    //[5678]:addr
    U8 u8FbId, u8GwinId;
    U8 gefmt;
    U16 width, height;
    U32 addr;

    gefmt = MB_Message.u8Parameters[0];
    width = ReadU16BE(&MB_Message.u8Parameters[1]);
    height = ReadU16BE(&MB_Message.u8Parameters[3]);
    addr = ReadU32BE(&MB_Message.u8Parameters[5]);

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    u8GwinId = MApi_GOP_GWIN_CreateWin(32, 32, GFX_FMT_YUV422);
    u8FbId = MApi_GOP_GWIN_GetFBfromGWIN(u8GwinId);
    MApi_GOP_GWIN_DestroyFB(u8FbId);
    u8FbId = MApi_GOP_GWIN_GetFreeFBID();
    MApi_GOP_GWIN_CreateFBbyStaticAddr(u8FbId, 0, 0, width, height, gefmt, addr);
    MApi_GOP_GWIN_MapFB2Win(u8FbId, u8GwinId);
    MApi_GOP_GWIN_SetWinDispPosition(u8GwinId, 200, 200);
    MApi_GOP_GWIN_SetBlending(u8GwinId, FALSE, 63);
    MApi_GOP_GWIN_Enable(u8GwinId, TRUE);
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_GWIN_CREATE_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,u8GwinId
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

static void _APEngine_GWIN_Enable(MBX_Msg MB_Message)
{
    //[0]:gwinid
    //[1]:1=enable, 0=disable
    U8 u8GwinId, enable;
    u8GwinId = MB_Message.u8Parameters[0];
    enable = MB_Message.u8Parameters[1];

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    MApi_GOP_GWIN_Enable(u8GwinId, enable);
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_GWIN_ENABLE_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _APEngine_GWIN_Move(MBX_Msg MB_Message)
{
    //[0]:gwinid
    //[12]:x
    //[34]:y
    U8 u8GwinId;
    U16 x, y;

    u8GwinId = MB_Message.u8Parameters[0];
    x = ReadU16BE(&MB_Message.u8Parameters[1]);
    y = ReadU16BE(&MB_Message.u8Parameters[3]);

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    MApi_GOP_GWIN_SetWinPosition(u8GwinId, x, y);
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_GWIN_MOVE_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _APEngine_GWIN_Destroy(MBX_Msg MB_Message)
{
    //[0]:gwinid
    U8 u8GwinId;
    u8GwinId = MB_Message.u8Parameters[2];

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    MApi_GOP_GWIN_ReleaseWin(u8GwinId);
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_GWIN_DESTROY_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _APEngine_VOP_Init(MBX_Msg MB_Message)
{
    //[01]:width
    //[23]:height
    //[4567]:addr
    U16 u16Width, u16Height;
    U32 u32BuffAddr;
    MVOP_VidStat stMvopVidSt;

    u16Width = ReadU16BE(&MB_Message.u8Parameters[0]);
    u16Height = ReadU16BE(&MB_Message.u8Parameters[2]);
    u32BuffAddr = ReadU32BE(&MB_Message.u8Parameters[4]);

    U16 u16DisplayX, u16DisplayY, u16DisplayWidth, u16DisplayHeight;
    u16DisplayX = 0;
    u16DisplayY = 0;
    u16DisplayWidth = u16Width;
    u16DisplayHeight = u16Height;

    gstVidStatus.u32FrameRate = 60000;

//    msAPI_VID_VOPInit();
    MDrv_MVOP_Init();
//    msAPI_VID_SetVOPClk(TRUE);

    {
        MVOP_InputCfg dc_param;
        #if 0
        MS_SYS_INFO enMsSysInfo;
        #endif

        // Enable Blue Screen
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);

//        msAPI_VID_VOPInit();
        MDrv_MVOP_Init();

    //Refine: When we enter MM or Internet APs, input source type already be set to INPUT_SOURCE_STORAGE and
    //          msAPI_Scaler_SetSourceType() was called. So, we don't need to set source type again.
#if 0
         // set Scaler input source
        SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) = INPUT_SOURCE_STORAGE;
        enMsSysInfo.enDataInputSourceType = DATA_INPUT_SOURCE_STORAGE;
        enMsSysInfo.enInputSourceType = INPUT_SOURCE_STORAGE;
        enMsSysInfo.enAspectRatio = VIDEOSCREEN_NORMAL;
        msAPI_Scaler_SetSourceType(enMsSysInfo.enInputSourceType,OUTPUT_SCALER_MAIN_WINDOW);
#endif

        // set mvop parameters
        //=========JPEG TETS==========
        dc_param.u16HSize = u16Width;
        dc_param.u16VSize = u16Height;
        dc_param.u32YOffset = u32BuffAddr;
        dc_param.u32UVOffset = dc_param.u32YOffset+ 8; //No Use, in MDrv_VOP_Input_Mode, it will be reset
        dc_param.bSD = 1;
        dc_param.bYUV422 = 1;
        dc_param.bProgressive = 1;
        dc_param.bUV7bit = 0;
        dc_param.bDramRdContd = 1;
        dc_param.bField = 0;
        dc_param.b422pack = 1;
        dc_param.u16StripSize = dc_param.u16HSize;
        MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &dc_param);

        gstVidStatus.u16HorSize = dc_param.u16HSize;
        gstVidStatus.u16VerSize = dc_param.u16VSize;
        gstVidStatus.u8AspectRate = ASP_4TO3;   //ASP_16TO9;
        gstVidStatus.u8Interlace = 0;
    }

    U32 u32Width, u32Height;
    u32Width = (U32)gstVidStatus.u16HorSize;
    u32Height = (U32)gstVidStatus.u16VerSize;

    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));
    stMvopVidSt.u16HorSize   = gstVidStatus.u16HorSize;
    stMvopVidSt.u16VerSize   = gstVidStatus.u16VerSize;
    stMvopVidSt.u16FrameRate = gstVidStatus.u32FrameRate;
    stMvopVidSt.u8AspectRate = gstVidStatus.u8AspectRate;
    stMvopVidSt.u8Interlace  = gstVidStatus.u8Interlace;
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);

    {
        U16 displayX, displayY, displayHSize, displayVSize;
        MS_WINDOW_TYPE tDstWin;
        S32 s32QuotientDiff, s32RemainderDiff;

        // set scaling aspect to program
        // [071017 Andy] set to original aspect
        stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_ORIGIN;

        #if 0
        if(enVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW)
        {
            u16DisplayX = MOVIE_PREVIEW_X;
            u16DisplayY = MOVIE_PREVIEW_Y;
            u16DisplayWidth = MOVIE_PREVIEW_WIDTH;
            u16DisplayHeight = MOVIE_PREVIEW_HEIGHT;
        }
        #endif

        // Set to the original aspect ratio
        s32QuotientDiff = ((((U32)u16DisplayWidth * 32) / (U32)u16DisplayHeight) - (((U32)u16Width * 32) / (U32)u16Height));
        s32RemainderDiff = ((((U32)u16DisplayWidth * 32) % (U32)u16DisplayHeight) - (((U32)u16Width * 32) % (U32)u16Height));
        // Set to the original aspect ratio
        if ((s32QuotientDiff > 0)
                || ((s32QuotientDiff == 0) && (s32RemainderDiff > 0)))
        {
            // Height major
            displayHSize = (U16)(((U32)u16DisplayHeight * 32 / (U32)u16Height) *
                                  (U32)u16Width / 32) & 0xFFFE;
            displayX = u16DisplayX + (u16DisplayWidth - displayHSize) / 2;
            displayY = u16DisplayY;
            displayVSize = u16DisplayHeight;
        }
        else
        {
            // Width major
            displayVSize = (U16)(((U32)u16DisplayWidth * 32 / (U32)u16Width) *
                                  (U32)u16Height / 32) & 0xFFFE;
            displayY = u16DisplayY + (u16DisplayHeight - displayVSize) / 2;
            displayX = u16DisplayX;
            displayHSize = u16DisplayWidth;
        }

        {
            tDstWin.x = displayX;
            tDstWin.y = displayY;
            tDstWin.width = displayHSize;
            tDstWin.height = displayVSize;

            MApp_Scaler_EnableOverScan(FALSE);
            MApp_Scaler_SetWindow(NULL, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                                   SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        }

        //switch MIU to 0
        MDrv_MVOP_MiuSwitch(0);

        MDrv_MVOP_Enable(TRUE);
//        msAPI_VID_SetVOPClk(ENABLE);

        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    }

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_VOP_INIT_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _APEngine_VOP_SetBlueScreen(MBX_Msg MB_Message)
{
    //[0]:1=enable, 0=disable
    U8 enable;
    enable = MB_Message.u8Parameters[0];

    msAPI_Scaler_SetBlueScreen(enable, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_VOP_SETBLUESCREEN_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _APEngine_VOP_Move(MBX_Msg MB_Message)
{
    //[01]:x
    //[23]:y
    //[45]:w
    //[67]:h
    U16 x, y, w, h;
    MS_WINDOW_TYPE tDstWin;

    x = ReadU16BE(&MB_Message.u8Parameters[0]);
    y = ReadU16BE(&MB_Message.u8Parameters[2]);
    w = ReadU16BE(&MB_Message.u8Parameters[4]);
    h = ReadU16BE(&MB_Message.u8Parameters[6]);

    tDstWin.x = x;
    tDstWin.y = y;
    tDstWin.width = w;
    tDstWin.height = h;
    MApp_Scaler_SetWindow(NULL, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_VOP_MOVE_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _APEngine_VOP_Destroy(MBX_Msg MB_Message)
{
    UNUSED(MB_Message);

    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_VOP_DESTROY_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

#if ENABLE_DMP
static void _APEngine_Audio_ReloadCode(En_DVB_decSystemType enDecSystem)
{
    BOOLEAN bUserMute = msAPI_AUD_IsAudioMutedByUser();

    MApp_InputSource_ChangeAudioSource( stSystemInfo[MAIN_WINDOW].enInputSourceType,UI_INPUT_SOURCE_NONE );
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);

    MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_NONE);
    MApi_AUDIO_SetSystem(enDecSystem);
    if ( enDecSystem == MSAPI_AUD_DVB_MP3 )
    {
        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MP3);
        MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);//MDrv_MAD_SetAdMixMode(MAIN_MIX_AD, MIX_ON);
    }
    if (!bUserMute)
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    //force unmute ... the mute might be triggerrd from SIF which we can hardly
    // determine which type it is...
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);

}
static void _APEngine_Audio_Init(MBX_Msg MB_Message)
{
    //[0]:system
    //[12]:sample rate
    //[34]:bits per sample
    //[5]:channel number
    En_DVB_decSystemType enDecSystem = (En_DVB_decSystemType) MB_Message.u8Parameters[0];
    if ( enDecSystem == MSAPI_AUD_DVB_XPCM )
    {
        U16 u16SampleRate;
        U16 u16BitsPerSample;
        U8 u8CannelNumber;

        u16SampleRate = ReadU16BE(&MB_Message.u8Parameters[1]);
        u16BitsPerSample  = ReadU16BE(&MB_Message.u8Parameters[3]);
        u8CannelNumber = MB_Message.u8Parameters[5];

        //MDrv_MAD_XPCM_setParam(1, u8CannelNumber-1, u16SampleRate, u16BitsPerSample, 0, 0);
        MApi_AUDIO_XPCM_Param(LPCM, u8CannelNumber-1, u16SampleRate, u16BitsPerSample, 0, 0);
    }
    _APEngine_Audio_ReloadCode(enDecSystem);

    //fire mbx to send response to co-processor
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_AUDIO_INIT_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    //MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);
}
#endif

static void _APEngine_I8_Set(MBX_Msg MB_Message)
{

    U32 *pMsInitDataInRAM = NULL;

    U32 gs32ProtocolParameterBuffer = ReadU32BE( &MB_Message.u8Parameters[2]);

    U16 StartIndex = ReadU16BE(&MB_Message.u8Parameters[6]);
    U16 ColorCount = ReadU16BE(&MB_Message.u8Parameters[8]);

    pMsInitDataInRAM = (U32 *) KSEG02KSEG1(gs32ProtocolParameterBuffer);


    GOP_PaletteEntry * pPalArray = (GOP_PaletteEntry *) pMsInitDataInRAM;

    MApi_GOP_GWIN_2GSetPaletteOpt(pPalArray,StartIndex,StartIndex+ColorCount-1);
    //printf("SET=%d %d=====\n",StartIndex,ColorCount);
    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_I8_SET_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
    //printf("send SET RES \n");
}

static void _APEngine_I8_Get(MBX_Msg MB_Message)
{

    U32 *pMsInitDataInRAM = NULL;
    U32 i;

    U32 gs32ProtocolParameterBuffer = ReadU32BE( &MB_Message.u8Parameters[2]);
    pMsInitDataInRAM = (U32 *) KSEG02KSEG1(gs32ProtocolParameterBuffer);

    U16 StartIndex = ReadU16BE(&MB_Message.u8Parameters[6]);
    U16 ColorCount = ReadU16BE(&MB_Message.u8Parameters[8]);

    U32 *pPalArray = pMsInitDataInRAM;
    //printf("GET=====%d %d=====\n",StartIndex,ColorCount);
    for(i = 0;i<ColorCount;i++)
    {
        MApi_GOP_GWIN_2GReadPalette(StartIndex+i, (U32*)(pPalArray+i));
    }
    // send response to aeon
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_I8_GET_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
    // printf("send GET RES \n");
}

static void _APEngine_APP_Finalize_Done(MBX_Msg MB_Message)
{
    UNUSED(MB_Message);
    _bCAPEFinalizeIsDone= TRUE;
}

void msAPI_APEngine_APP_Finalize_Init(void)
{
    _bCAPEFinalizeIsDone= FALSE;
}

BOOLEAN msAPI_APEngine_APP_Finalize_Check(void)
{
    return _bCAPEFinalizeIsDone;
}

static void _APEngine_APP_Initialize_Done(MBX_Msg MB_Message)
{
    UNUSED(MB_Message);
    _bCAPEInitializeIsDone = TRUE;
    _u32CAPEAliveCount = msAPI_Timer_GetTime0();
}

BOOLEAN msAPI_APEngine_APP_Initialize_Check(void)
{
    return _bCAPEInitializeIsDone;
}

static void _APEngine_APP_Alive_Record(MBX_Msg MB_Message)
{
    UNUSED(MB_Message);
    _u32CAPEAliveCount = msAPI_Timer_GetTime0();
    //printf("got signal in %d\n", _u32CAPEAliveCount);
}

BOOLEAN msAPI_APEngine_APP_Alive_Check(void)
{
    if(msAPI_APEngine_APP_Initialize_Check())
    {
        if(msAPI_Timer_DiffTimeFromNow(_u32CAPEAliveCount) > ALIVE_CHECK_INTERVAL)
        {
            return FALSE;
        }
    }

    return TRUE;
}

static void _APEngine_File_Len_Info(MBX_Msg MB_Message)
{
    //get file info
    BININFO BinInfo;
    BinInfo.B_ID = ReadU32BE(&MB_Message.u8Parameters[0]);

    BOOLEAN bResult;
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS )
    {
        printf( "Fail to find AEON binary on flash.\n" );
        return;
    }

    //fire mbx to send response to co-processor
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_FILE_LEN_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,4
    /*p1*/              ,(U8)((BinInfo.B_Len & 0xFF000000) >> 24)
    /*p2*/              ,(U8)((BinInfo.B_Len & 0x00FF0000) >> 16)
    /*p3*/              ,(U8)((BinInfo.B_Len & 0x0000FF00) >> 8)
    /*p4*/              ,(U8)((BinInfo.B_Len & 0x000000FF))
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _APEngine_File_Copy2Dram(MBX_Msg MB_Message)
{
    //copy data
    BININFO BinInfo;
    BinInfo.B_ID = ReadU32BE(&MB_Message.u8Parameters[0]);

    BOOLEAN bResult;
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS)
    {
        printf( "Fail to find AEON binary on flash.\n" );
        return;
    }

    U32 u32StartAddr = ReadU32BE(&MB_Message.u8Parameters[4]);

    //U8 u8MIUProtectAeon_ID[2];
    //u8MIUProtectAeon_ID[0] = MIU_CLI_AEON_RW;
    //u8MIUProtectAeon_ID[1] = 0;
    //MDrv_MIU_Protect(2, u8MIUProtectAeon_ID, u32StartAddr, u32StartAddr+BinInfo.B_Len-1, DISABLE);
    if( TRUE != MDrv_SERFLASH_CopyHnd(BinInfo.B_FAddr, u32StartAddr, (BinInfo.B_Len+0x07)&~0x07, E_SPIDMA_DEV_MIU0, SPIDMA_OPCFG_DEF) )
    {
        //printf( "Font bin is copyed failed\n" );
    }

    //fire mbx to send response to co-processor
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_CAPE
    /*Index*/           ,MB_CAPE_FILE_COPY_RES
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,1
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

void msAPI_APEngine_ProcessMailBox(void)
{
    MBX_Msg MB_Message;
    if( E_MBX_SUCCESS == MSApi_MBX_RecvMsg(E_MBX_CLASS_CAPE, &MB_Message, 0, MBX_CHECK_NORMAL_MSG) )
    {
        if ( E_MBX_CLASS_CAPE == MB_Message.u8MsgClass ) //command class
        {
            switch (MB_Message.u8Index)
            {
                case MB_CAPE_GWIN_CREATE_REQ:
                    _APEngine_GWIN_Create(MB_Message);
                    break;

                case MB_CAPE_GWIN_ENABLE_REQ:
                    _APEngine_GWIN_Enable(MB_Message);
                    break;

                case MB_CAPE_GWIN_MOVE_REQ:
                    _APEngine_GWIN_Move(MB_Message);
                    break;

                case MB_CAPE_GWIN_DESTROY_REQ:
                    _APEngine_GWIN_Destroy(MB_Message);
                    break;

                case MB_CAPE_VOP_INIT_REQ:
                    _APEngine_VOP_Init(MB_Message);
                    break;

                case MB_CAPE_VOP_SETBLUESCREEN_REQ:
                    _APEngine_VOP_SetBlueScreen(MB_Message);
                    break;

                case MB_CAPE_VOP_MOVE_REQ:
                    _APEngine_VOP_Move(MB_Message);
                    break;

                case MB_CAPE_VOP_DESTROY_REQ:
                    _APEngine_VOP_Destroy(MB_Message);
                    break;

#if ENABLE_DMP
                case MB_CAPE_AUDIO_INIT_REQ:
                    _APEngine_Audio_Init(MB_Message);
                    break;
#endif
                case MB_CAPE_I8_SET_REQ:
                    _APEngine_I8_Set(MB_Message);
                    break;

                case MB_CAPE_I8_GET_REQ:
                    _APEngine_I8_Get(MB_Message);
                    break;

                case MB_CAPE_APP_FINALIZED_SIG:
                     //printf("======= received MB_CAPE_APP_FINALIZE_REQ===========\n");
                     _APEngine_APP_Finalize_Done(MB_Message);
                     break;

                case MB_CAPE_APP_ALIVE_SIG:
                     //printf("======= CAPE is ALIVE===========\n");
                     _APEngine_APP_Alive_Record(MB_Message);
                     break;

                case MB_CAPE_APP_INITIALIZED_SIG:
                     //printf("======= received MB_CAPE_APP_INITIALIZE_REQ===========\n");
                     _APEngine_APP_Initialize_Done(MB_Message);
                     break;


                case MB_CAPE_FILE_LEN_REQ:
                     _APEngine_File_Len_Info(MB_Message);
                     break;

                case MB_CAPE_FILE_COPY_REQ:
                     _APEngine_File_Copy2Dram(MB_Message);
                     break;

                default:
                    break;
            }
        }
        else
        {
            //assert
            __ASSERT(FALSE);
        }
    }
}

/******************************************************************************/
///- This API is for transmitting IR key to CAPE
/// @param u8Key \b IN: IR Key to transmit
/// @param Status \b IN: status for Aeon
/******************************************************************************/
void msAPI_APEngine_TransmitKey(U8 u8Key)
{
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_INPUT
    /*Index*/           ,MB_INPUT_CMD_IR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,u8Key
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

/******************************************************************************/
///- This API is for transmitting IR key to CAPE
/// @param u8Key \b IN: IR Key to transmit
/// @param Status \b IN: status for Aeon
/******************************************************************************/
void msAPI_APEngine_TransmitJoystick(U16 u16State)
{
    //==> Send mail.
    APENGINE_MAILBOX_SEND(E_MBX_CLASS_INPUT
    /*Index*/           ,MB_INPUT_CMD_JOYSTICK
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,2
    /*p1*/              ,u16State & 0xff
    /*p2*/              ,u16State >> 8
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}


//For CAPE combined-bin
/******************************************************************************/
//The header fields(total 512 bytes):
    //[01234]:magic number
    //[5]:APP type(0: APP, 1: GAME)
    //[678]:APP file entension(APP, NES, SMC, etc.)
    //[9abcdef]:APP note
    //[0123]>>1:CRC value
    //[4567]>>1:romfs length
    //[89ab]>>1:executable length
    //[cdef]>>1:compressed bin length
    //32 bytes reserved
    //448 bytes version check
/******************************************************************************/
BOOLEAN msAPI_APEngine_AppIsHeaderValid(U8 u8Type, U8 *pHeader, U16 u16HeaderLen)
{
    if ( u16HeaderLen != APP_HEADER_LENGTH )
    {
        return FALSE;
    }

    // check type
    U8 u8HeaderType = pHeader[5];
    if ( (u8Type != APP_DONT_CARE) && (u8HeaderType != u8Type) )
    {
        printf("APEngine: Bin file type error!\n");
        return FALSE;
    }

    // check magic number
    if( pHeader[0] != 0x09 ||
        pHeader[1] != 0x58 ||
        pHeader[2] != 0x33 ||
        pHeader[3] != 0x69 ||
        pHeader[4] != 0x00
    )
    {
        printf("APEngine: %02x %02x %02x %02x %02x magic number error\n!!", pHeader[0], pHeader[1], pHeader[2], pHeader[3], pHeader[4]);
        return FALSE;
    }

    return TRUE;

}

BOOLEAN msAPI_APEngine_AppIsContentValid(U8 *pContent, U32 u32ContentLen)
{
    // parsing APP header
    if ( u32ContentLen < APP_HEADER_LENGTH )
    {
        return FALSE;
    }

    U8 *pHeader = (U8*) (pContent + u32ContentLen - APP_HEADER_LENGTH);

    // check crc
    U32 u32CRC = ReadU32BE(&pHeader[16]);
    U32 u32BinFileLen = ReadU32BE(&pHeader[28]);

    // compute HW crc
    U32 u32CRCResult = MDrv_BDMA_CRC32((U32)pContent, u32BinFileLen , BDMA_CRC32_POLY, BDMA_CRC_SEED_0, E_BDMA_SRCDEV_MIU0, FALSE);

    if (u32CRCResult != u32CRC)
    {
        printf(" HW CRC error: u32CRCResult=0x%08lx, u32CRC=0x%08lx\n", u32CRCResult, u32CRC);
        // start SW crc patch check
        {
            U8  u8bit;
            U32 u32Remainder = u32CRCResult;
            U32 u32Width = 32;
            U32 u32Topbit = (1 <<(u32Width-1) );

            u32Remainder ^= pContent[u32BinFileLen-1] << (u32Width - 8);

            for (u8bit = 8; u8bit > 0; --u8bit)
            {

                if (u32Remainder & u32Topbit)
                {
                    u32Remainder = (u32Remainder << 1) ^ BDMA_CRC32_POLY;
                }
                else
                {
                    u32Remainder = (u32Remainder << 1);
                }
            }
            u32CRCResult = u32Remainder ^ BDMA_CRC_SEED_0;
        }

        if (u32CRCResult != u32CRC)
        {
            printf(" SW CRC error: u32CRCResult=0x%08lx, u32CRC=0x%08lx\n", u32CRCResult, u32CRC);
            return FALSE;
        }
    }

    return TRUE;
}

BOOLEAN msAPI_APEngine_GetExtension(U8 *pExtension, U8 u8ExtLen, U8 *pHeader, U16 u16HeaderLen)
{
    if ( u16HeaderLen != APP_HEADER_LENGTH )
    {
        return FALSE;
    }

    if (u8ExtLen < 4)
    {
        return FALSE;
    }

    strncpy((char*)pExtension, (char*)&pHeader[6], 3);
    return TRUE;
}


#if ENABLE_MPLAYER_PLUGIN
static BOOLEAN _APEngine_SendRomFsSize(void)
{
    U8 u8Info[4];

    u8Info[0] = (U8)((_u32RomFsSize)     &0xFF);
    u8Info[1] = (U8)((_u32RomFsSize>>8)  &0xFF);
    u8Info[2] = (U8)((_u32RomFsSize>>16) &0xFF);
    u8Info[3] = (U8)((_u32RomFsSize>>24) &0xFF);
    if( E_MBX_SUCCESS != MSApi_MBX_SetInformation(&u8Info[0], 4) )
    {
        return FALSE;
    }

    return TRUE;
}

static BOOLEAN _APEngine_InitMBX(void)
{
    if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_CAPE, MAX_MBX_QUEUE_SIZE/8))
    {
        if(E_MBX_SUCCESS != MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_CAPE))
        {
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_CAPE, MAX_MBX_QUEUE_SIZE/8))
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

BOOLEAN msAPI_APEngine_AppRun(U32 u32AppBinaryAddr, U32 u32Len, U32 u32BEON_ADR, U32 u32BEON_LEN)
{
    U8 *pHeader = (U8*)(_PA2VA(u32AppBinaryAddr) + u32Len - APP_HEADER_LENGTH);

    // decompress
    U32 ResBinLen = ReadU32BE(&pHeader[20]);
    U32 AppBinLen = ReadU32BE(&pHeader[24]);

    if ( AppBinLen > u32BEON_LEN )
    {
        printf("app too large to fit: app=%08lx, cape=%08lx\n", AppBinLen, u32BEON_LEN);
        return FALSE;
    }
    if ( ResBinLen > CAPE_BUFFER_LEN )
    {
        printf("resource too large to fit: res=%08lx, cape=%08lx\n", ResBinLen, (U32)CAPE_BUFFER_LEN);
        return FALSE;
    }
    if (ms_DecompressInit((U8*)_PA2VA(((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)))) == FALSE)
    {
        printf("decompress fail!\n");
        return FALSE;
    }
    ms_Decompress((U8*)_PA2VA(u32AppBinaryAddr), u32Len-APP_HEADER_LENGTH);
    ms_DecompressDeInit();

    // init romfs size
    _u32RomFsSize = 0;

    MsOS_DisableInterrupt(E_INT_FIQ_AEON_TO_BEON);
    MsOS_DisableInterrupt(E_INT_FIQ_BEON_TO_AEON);
#if defined(MIPS_CHAKRA) || defined(__AEONR2__)
    MDrv_COPRO_Disable();
#else
    MDrv_COPRO_Disable();
#endif

    U8 u8MIUProtectAeon_ID[2];
    u8MIUProtectAeon_ID[0] = MIU_CLIENT_MHEG5_ICACHE_RW;
    u8MIUProtectAeon_ID[1] = 0;

    //MDrv_WriteByte(0x33DE , 0x02); // for aeon judgement

    MDrv_MIU_Protect(2, &u8MIUProtectAeon_ID[0], u32BEON_ADR, u32BEON_ADR+ALIGNED_VALUE(AppBinLen, 8)-1, DISABLE);
    U32 BinAddr = _PA2VA((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR))+ResBinLen ;
    MDrv_BDMA_CopyHnd(BinAddr, u32BEON_ADR, ALIGNED_VALUE(AppBinLen,8), E_BDMA_SDRAM2SDRAM, BDMA_OPCFG_DEF);

    {
        // error check, temporarily
        U32 *u32Ptr = (U32*)_PA2VA(u32BEON_ADR);
        if ( (*u32Ptr)==0xFFFFFFFF )
        {
            printf("MDrv_BDMA_CopyHnd to 0x%08lx[len=%lu] failed\n", _PA2VA(u32BEON_ADR), (U32)GE_ALIGNED_VALUE(AppBinLen,8));
        }
    }

    _u32RomFsSize = ALIGNED_VALUE(ResBinLen, 8);

#if defined(MIPS_CHAKRA) || defined(__AEONR2__)
    msAPI_COPRO_Init_ByAddr(u32BEON_ADR, u32BEON_LEN);
#else
    msAPI_COPRO_Init_ByAddr(u32BEON_ADR, u32BEON_LEN);
#endif

    if( !_APEngine_InitMBX() )
    {
        printf("mailbox error\n");
        return FALSE;
    }

    if( !msAPI_MMap_SendMMapAddr_CAPE() )
    {
        printf("send mmap information error\n");
        return FALSE;
    }
    if( !_APEngine_SendRomFsSize() )
    {
        printf("send romfs error\n");
        return FALSE;
    }

    return TRUE;

}

BOOLEAN msAPI_APEngine_AppRunByBinID(U16 u16BinID, U32 u32BEON_ADR, U32 u32BEON_LEN)
{
    BININFO BinInfo;
    U8 *pHeader;
    BinInfo.B_ID = u16BinID;
    BOOLEAN bResult;

    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS)
    {
        printf("Fail to find binary on flash.\n");
        return FALSE;
    }

    // init romfs size
    _u32RomFsSize = 0;

    ///-Note: BinIDPackFiles.py would pad '8' bytes in the end of file.
    U32 u32ContentSize = ALIGNED_VALUE(BinInfo.B_Len,8) - 8;

    U32 u32TmpAddr = (_PA2VA((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)) + CAPE_BUFFER_LEN - BinInfo.B_Len) & ~(8-1); //8 bytes alignment

    ///-Copy firmware code from flash to SDRAM
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_Start(&BinInfo);
#endif

    MDrv_SERFLASH_CopyHnd(BinInfo.B_FAddr, u32TmpAddr, ALIGNED_VALUE(BinInfo.B_Len,8), E_SPIDMA_DEV_MIU0, SPIDMA_OPCFG_DEF);

#ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_Flash_2_Checking_End(&BinInfo);
#endif

    pHeader = (U8*) _PA2VA((u32TmpAddr + u32ContentSize - APP_HEADER_LENGTH));
    if (msAPI_APEngine_AppIsHeaderValid(APP_DONT_CARE, pHeader, APP_HEADER_LENGTH))
    {
        if (msAPI_APEngine_AppIsContentValid((U8*)u32TmpAddr,  u32ContentSize))
        {
            if (!msAPI_APEngine_AppRun(u32TmpAddr, u32ContentSize, u32BEON_ADR, u32BEON_LEN))
            {
                return FALSE;
            }
        }
        else
        {
            printf("Invalid Contents.\n");
            return FALSE;
        }
    }
    else
    {
        MsOS_DisableInterrupt(E_INT_FIQ_AEON_TO_BEON);
        MsOS_DisableInterrupt(E_INT_FIQ_BEON_TO_AEON);
#if defined(MIPS_CHAKRA) || defined(__AEONR2__)
        MDrv_COPRO_Disable();
#else
        MDrv_COPRO_Disable();
#endif

        U8 u8MIUProtectAeon_ID[2];
        u8MIUProtectAeon_ID[0] = MIU_CLIENT_MHEG5_ICACHE_RW;
        u8MIUProtectAeon_ID[1] = 0;

        MDrv_WriteByte(0x33DE , 0x02); // for aeon judgement

      #if 0
        printf( "AEON code flash:0x%08LX --> DRAM:0x%08LX, length=0x%08LX->0x%08LX\n",
        BinInfo.B_FAddr, u32BEON_ADR, BinInfo.B_Len, GE_ALIGNED_VALUE(BinInfo.B_Len,8));
      #else // Modified it by coverity_0487
        printf( "AEON code flash:0x%08lx --> DRAM:0x%08lx, length=0x%08lx->0x%08lx\n",
        BinInfo.B_FAddr, u32BEON_ADR, BinInfo.B_Len, GE_ALIGNED_VALUE(BinInfo.B_Len,8));
      #endif
        MDrv_MIU_Protect(2, &u8MIUProtectAeon_ID[0], u32BEON_ADR, u32BEON_ADR+ALIGNED_VALUE(BinInfo.B_Len,8)-1, DISABLE);

    #ifdef ENABLE_KTV
        msAPI_Timer_Delayms(200);
    #endif

        ///-Copy firmware code from flash to SDRAM
        MDrv_SERFLASH_CopyHnd(BinInfo.B_FAddr, u32BEON_ADR, GE_ALIGNED_VALUE(BinInfo.B_Len,8), E_SPIDMA_DEV_MIU0, SPIDMA_OPCFG_DEF);
        {
            // error check, temporarily
            U32 *u32Ptr = (U32*)u32BEON_ADR;
            if ( (*u32Ptr)==0xFFFFFFFF )
            {
                printf("MDrv_SERFLASH_CopyHnd to 0x%08lx[len=%lu] failed\n", u32BEON_ADR, (U32)GE_ALIGNED_VALUE(BinInfo.B_Len,8));
            }
        }

        msAPI_COPRO_Init_ByAddr(u32BEON_ADR, u32BEON_LEN);
        msAPI_MMap_SendMMapAddr_CAPE();
        _APEngine_SendRomFsSize();
    }

    return TRUE;

}
#endif // #if ENABLE_MPLAYER_PLUGIN



#endif //#if (ENABLE_CAPE)


#undef _MSAPI_APENGINE_C_

