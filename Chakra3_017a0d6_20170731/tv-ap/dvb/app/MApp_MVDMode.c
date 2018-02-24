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

#define MAPP_MVDMODE_C

#include <stdio.h>
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "msAPI_Global.h"

#include "debug.h"
#if (ENABLE_CI)
#include "msAPI_CI.h"
#endif

#include "apiXC.h"
#include "apiXC_Adc.h"

#include "apiXC_Sys.h"
#include "msAPI_Global.h"
#include "msAPI_Video.h"
#include "msAPI_Timer.h"
#include "apiGOP.h"
#include "apiXC_Ace.h"
#include "apiXC.h"
#include "drvPQ.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "msAPI_audio.h"
//ZUI: #include "MApp_DispMenu.h"
#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_Scaler.h"
#include "MApp_MVDMode.h"
#include "MApp_TV.h"
#include "MApp_MultiTasks.h"
#include "MApp_PCMode.h"
#include "MApp_XC_Sys.h"

#include "MApp_ChannelChange.h"

//for Audio mute issue
#include "MApp_Audio.h"
//for Audio mute issue

#include "MApp_ATVProc.h"
#include "msAPI_DTVSystem.h"
#include "MApp_BlockSys.h" //ZUI:
#include "MApp_TopStateMachine.h"

#if ENABLE_PVR
#include "MApp_PVR.h"
#include "MApp_TimeShift.h"
#endif

#if( ENABLE_TTX )
#include "mapp_ttx.h"
#endif


//#define DBG_VIDEO_APP
#define MVD_DEBUG(msg) //msg

#define DEBUG_HVD_TIMING(x) x


/********************************************************************************/
/*                     Local                    */
/********************************************************************************/

#define MVD_TIMING_STABLE_COUNT 1
#define MVD_BAD_VIDEO_COUNT     10 // 10s
#define MVD_BAD_PICTUR_COUNT    1
#define MVD_GOOD_PICTUR_COUNT   2


static BOOLEAN sbIsAspectRatioWide    = FALSE;

//static U32 u32MonitorMVDValidTimer;

#if(ENABLE_DTV)
static U32 PictureCounter;
static U8   BadPictureCounter;
static U32  u32PicCounterTimer;
#endif


// calvin 070130, add a timeout for MVD first frame check
#define MVD_FF_READY_TIMEOUT 15000 //071210_daniel set timeout to 15sec for Audio_tests_Layer_2_256-384kbps.mpg
static U32 u32FFReadyTimer;


// enable this if we want to freeze image when bitstream has error
#define FREEZE_VIDEO_ENABLE  0

#if FREEZE_VIDEO_ENABLE
#define MVD_BAD_VIDEO_FREEZE_TIMEOUT 600
static BOOLEAN bEnErrFreeze;
static BOOLEAN bEnErrMute;
static U8 u8ErrCnt;
static U32 u32ErrFreezeCounter;
static U32 u32ErrMuteCounter;
#endif

#if (DTV_USE_FBL)
#define FBLMSG(fmt, args...)   printf("[MApp_Scaler][%5d]" fmt, __LINE__, ## args)
#else
#define FBLMSG(fmt, args...)
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

/********************************************************************************/
/*                   Functions                      */
/********************************************************************************/
//*************************************************************************
//Function name:  _MApp_VID_CheckVideoStatus
//Passing parameter: none
//Return parameter: none
//Description: polling codec decode status.
//*************************************************************************
#if (ENABLE_DTV)

void MApp_VID_CheckFrameCnt_Init(void)
{
    BadPictureCounter = 0;
//    PictureCounter = msAPI_VID_GetPicCount();
    PictureCounter = MApi_VDEC_GetFrameCnt();
    u32PicCounterTimer = msAPI_Timer_GetTime0();
}

static EN_MVD_VIDEO_STATUS _MApp_VID_CheckVideoStatus(void)
{
    EN_MVD_VIDEO_STATUS eCheckFrameCntResult = MVD_UNKNOWN_VIDEO;

    if( (msAPI_Timer_DiffTimeFromNow( u32PicCounterTimer ) > 1000)
      &&(enMVDVideoStatus != MVD_UNKNOWN_VIDEO)
       )
    {
        U32 u32PictureNumber = 0;

        if ( MApi_VDEC_GetFrameCnt() < PictureCounter )
        {
            u32PictureNumber = 0xFFFFFFFF - PictureCounter + MApi_VDEC_GetFrameCnt();
        }
        else
        {
            u32PictureNumber = MApi_VDEC_GetFrameCnt() - PictureCounter;
        }

        if ( u32PictureNumber < MVD_BAD_PICTUR_COUNT )
        {
            BadPictureCounter++;
            if ( BadPictureCounter > MVD_BAD_VIDEO_COUNT )
            {
                //enMVDVideoStatus = MVD_BAD_VIDEO;
                eCheckFrameCntResult = MVD_BAD_VIDEO;
                BadPictureCounter = 0;
            }
        }
        else
        {
            if(u32PictureNumber > MVD_GOOD_PICTUR_COUNT)
            {
                //enMVDVideoStatus = MVD_GOOD_VIDEO;
                eCheckFrameCntResult = MVD_GOOD_VIDEO;
                //BadPictureCounter = 0;
            }
            BadPictureCounter = 0;

        #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
         #if (ENABLE_BOOTTIME==DISABLE)
            if (g_bAutobuildDebug == TRUE)
         #endif
            {
                if (gbBootTimeFinish == FALSE)
                {
                    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
                    printf("[TIME] Good video status = %ld\n", gU32TmpTime);
                }
            }
        #endif
        }

        u32PicCounterTimer = msAPI_Timer_GetTime0();

        PictureCounter = MApi_VDEC_GetFrameCnt();
    }

    return eCheckFrameCntResult;
}
#endif

//*************************************************************************
//Function name:    MApp_VID_VariableInit
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************
void MApp_VID_VariableInit(void)
{
#if (ENABLE_DTV)
    if( IS_HVD_CODEC(g_eCodecType ) ) //msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
        MApp_AVCH264_VariableInit();
    else
        MApp_MVD_VariableInit();

    g_bSetModeDone = FALSE;

    MApp_VID_CheckFrameCnt_Init();
#endif
}


#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)
static void _VdecCB(MS_U32 u32Event, void *param)
{
    param = param;
    if (u32Event & (E_VDEC_EVENT_DISP_INFO_CHG))
    {
        if (E_VDEC_OK != MApi_VDEC_SetBlueScreen(TRUE))
        {
            printf("MApi_VDEC_SetBlueScreen (OFF) Fail\n");
        }
        else
        {
            //if VDEC mute screen by timing change, Reset VID to set timing again.
            MApp_VID_VariableInit();
        }
    }
}



void MApp_VID_CBInit(void)
{
    // Register Callback event after VDEC initial
    MApi_VDEC_SetEvent(E_VDEC_EVENT_DISP_INFO_CHG, _VdecCB, NULL);
}

#endif

//*************************************************************************
//Function name:    MApp_MVD_VariableInit
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************
void MApp_MVD_VariableInit ( void )
{
    bMVDTimingChange = TRUE;
    bFastTimingCheck = TRUE;
    u8MVDTimingStableCount = 0;
    //u8MVDDecodeCount = 0;
    bMVDDoSetMode = FALSE;

#if FREEZE_VIDEO_ENABLE
    bEnErrFreeze = FALSE;
    bEnErrMute = FALSE;
#endif

  #ifdef U03//hjkoh 070518 - for hide uncontinuous screen when DTV channel change in Saturn2.
    bMVDTimingChange = FALSE;
    bFastTimingCheck = TRUE;
  #else
    bMVDTimingChange = TRUE;
    bFastTimingCheck = FALSE;
  #endif

  #if 0//def PATCH_BBY_VP403_TIMING_CHANGE
    bFastTimingCheck = FALSE;
  #endif

    bPrepareChange = FALSE;
    //bFirstTimeCheck = FALSE;
    //fCurMVDValidFlag = TRUE;
    //u32MonitorMVDValidTimer = ( msAPI_Timer_GetTime0() - 3000 );

  #if AUTO_ASPECT_RATIO
    sbIsAspectRatioWide = FALSE;
  #endif

    memset( &gstVidStatus, 0, sizeof( VDEC_DispInfo ) );
    memset( &gstPreVidStatus, 0, sizeof( VDEC_DispInfo ) );

    //Init PreVidStatus.u8AFD to 0xFF for AFD monitor;
    gstPreVidStatus.u8AFD = 0xFF;

    enMVDVideoStatus = MVD_UNKNOWN_VIDEO;

    u32FFReadyTimer = msAPI_Timer_GetTime0();

}

#if (ENABLE_DTV)

U32 g_u32PreVdecFrameCnt;

//*************************************************************************
//Function name:    MApp_VID_TimingMonitor
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************
void MApp_VID_TimingMonitor(SCALER_WIN eWindow)
{
    if( (msAPI_VID_GetPlayMode() == MSAPI_VID_STOP)
      ||(msAPI_VID_GetPlayMode() == MSAPI_VID_RESET)
      )
    {
        return;
    }

    if( IS_HVD_CODEC(msAPI_VID_GetCodecType()) )//msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    {
        MApp_AVCH264_TimingMonitor(eWindow);
    }
    else
    {
    #if( ENABLE_MVD_MONITOR_2016 )
        MApp_MVD_TimingMonitor_2016(eWindow);
    #else
        MApp_MVD_TimingMonitor(eWindow);
    #endif
    }
}

//*************************************************************************
//Function name:    MApp_MVD_TimingMonitor
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************
#if (ENABLE_VE)
#define ENABLE_MVD_TWICEFRC FALSE
#else
#define ENABLE_MVD_TWICEFRC FALSE
#endif
#define DEBUG_MVD_MONITOR(x)    //do{ printf("(%u) ", __LINE__); x; } while(0)


#if( ENABLE_MVD_MONITOR_2016 )

void MApp_MVD_TimingMonitor_2016( SCALER_WIN eWindow )
{
    DEBUG_MVD_MONITOR( printf("MApp_MVD_TimingMonitor() at %u\n", MsOS_GetSystemTime()); );

    // Check if cur status is good
    BOOLEAN bCurVidInfoIsGood = FALSE;


    if( (E_VDEC_OK == MApi_VDEC_CheckDispInfoRdy())
      &&(TRUE == msAPI_VID_GetVidInfo(&gstVidStatus))
      )
    {
    #if ENABLE_DVB
        MEMBER_SERVICETYPE bServiceType = msAPI_CM_GetCurrentServiceType();
        U16 u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);

        if( (E_VDEC_FAIL == MApi_VDEC_IsWithValidStream())
        #if ENABLE_DVB
          &&(msAPI_CM_GetProgramAttribute(bServiceType,u16CurPosition, E_ATTRIBUTE_IS_STILL_PICTURE) == FALSE) // Not Picture
        #endif
          )
        {
            bCurVidInfoIsGood = FALSE;
        }
        else
    #endif
        {

            bCurVidInfoIsGood = TRUE;

        #if ENABLE_MVD_TWICEFRC
            //let MVOP do double FRC if 25P/30P signal, it will fix the subtitle of VE ouput shaking issue
            //because the VE do not has good FRC capability
            if( (gstVidStatus.u32FrameRate < 35000) && (gstVidStatus.u8Interlace==FALSE) )
            {
                gstVidStatus.u32FrameRate *= 2;
            }
        #endif
        }
    }
    else // Get info failed
    {
        bCurVidInfoIsGood = FALSE;
    }

    DEBUG_MVD_MONITOR( printf(" bCurVidInfoIsGood=%u\n", bCurVidInfoIsGood); );

    // Check if stable, check stable count
    if( bCurVidInfoIsGood )
    {
        if( ( gstPreVidStatus.u16HorSize == gstVidStatus.u16HorSize )
         && ( gstPreVidStatus.u16VerSize == gstVidStatus.u16VerSize )
        #if AUTO_ASPECT_RATIO
         && ( gstPreVidStatus.u8AspectRate == gstVidStatus.u8AspectRate )
        #endif
         && ( gstPreVidStatus.u32FrameRate == gstVidStatus.u32FrameRate )
         && ( gstPreVidStatus.u8Interlace == gstVidStatus.u8Interlace )
          )
        {
            if( u8MVDTimingStableCount < 10 )
            {
                u8MVDTimingStableCount += 1;
                DEBUG_MVD_MONITOR( printf(" u8MVDTimingStableCount = %u\n", u8MVDTimingStableCount); );
            }
        }
        else
        {
            DEBUG_MVD_MONITOR( printf(" gstPreVidStatus != gstVidStatus\n"); );
            u8MVDTimingStableCount = 0;
            gstPreVidStatus.u16HorSize = gstVidStatus.u16HorSize;
            gstPreVidStatus.u16VerSize = gstVidStatus.u16VerSize;
            gstPreVidStatus.u8AspectRate = gstVidStatus.u8AspectRate;
            gstPreVidStatus.u32FrameRate = gstVidStatus.u32FrameRate;
            gstPreVidStatus.u8Interlace = gstVidStatus.u8Interlace;
        }

    }
    else
    {
        u8MVDTimingStableCount = 0;
        memset( &gstPreVidStatus, 0, sizeof( VDEC_DispInfo ) );
    }

    EN_MVD_VIDEO_STATUS eCurVideoStatus = MVD_BAD_VIDEO;

    if( u8MVDTimingStableCount > MVD_TIMING_STABLE_COUNT )
    {
        eCurVideoStatus = MVD_GOOD_VIDEO;

    }
    else
    {
    }

    // Old is good, new is good => Check frame count
    if( (enMVDVideoStatus == MVD_GOOD_VIDEO) && (eCurVideoStatus == MVD_GOOD_VIDEO) )
    {
        EN_MVD_VIDEO_STATUS eCheckFrameCntResult = _MApp_VID_CheckVideoStatus();

        if( eCheckFrameCntResult == MVD_BAD_VIDEO )
        {

        }
    }


    // Old is Good,
    if( (enMVDVideoStatus == MVD_GOOD_VIDEO) )
    {
        // Good ==> Bad
        if( eCurVideoStatus != MVD_GOOD_VIDEO )
        {
            DEBUG_MVD_MONITOR( printf("  Good ==> Bad\n"); );

        #if ENABLE_PVR
            enPVRState       PVRState       = MApp_PVR_StateMachineGet();
            enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();

             if((PVRState != E_PVR_STATE_RECORDnPLAYBACK && PVRState != E_PVR_STATE_PLAYBACK)
             &&(TimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING && TimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING))
             {
                MApp_VID_PrepareTimingChange(eWindow);
             }
        #else
             MApp_VID_PrepareTimingChange(eWindow);
        #endif

            enMVDVideoStatus = MVD_BAD_VIDEO;
        }
    }
    else // Old is Bad or Unknown
    {
        // Bad ==> Good
        if( eCurVideoStatus == MVD_GOOD_VIDEO )
        {
            DEBUG_MVD_MONITOR( printf("  Bad ==> Good\n"); );
        #if(DEBUG_CHG_SRC_TIME)
            msDebug_PrintChgSrcTime("enMVDVideoStatus = MVD_GOOD_VIDEO" );
        #endif

            U16 u16SyncTolerance = 25;
            if( gstVidStatus.u32FrameRate > 0 )
                u16SyncTolerance = (600000/gstVidStatus.u32FrameRate); // 0.6 frame time = (1000ms / (u32FrameRate/1000))* 0.6 =  (600000/u32FrameRate)

            MApi_VDEC_AVSyncOn(TRUE, 180 ,u16SyncTolerance);          //Sync offset will influence DTV lip-sync timing
                                                       //if you want to change sync offset, please inform audio team and video team

            bMVDDoSetMode = TRUE;

            enMVDVideoStatus = MVD_GOOD_VIDEO;

            // Init frame count check
            MApp_VID_CheckFrameCnt_Init();
        }
    }

}

#else

void MApp_MVD_TimingMonitor ( SCALER_WIN eWindow )
{
#if ENABLE_DVB
    MEMBER_SERVICETYPE bServiceType;
    U16 u16CurPosition;
#endif
//    U8              PictureNumber;
    DEBUG_MVD_MONITOR( printf("MApp_MVD_TimingMonitor() at %u\n", MsOS_GetSystemTime()); );

#if FREEZE_VIDEO_ENABLE
    U8              u8CurrErrCnt;

//    u8CurrErrCnt = msAPI_VID_GetErrCnt();

    if(IS_MVD_CODEC(msAPI_VID_GetCodecType()))
    {//msAPI_VID_GetCodecType()==E_VDEC_CODEC_TYPE_MPEG2){
        u8CurrErrCnt = MApi_VDEC_GetErrCnt();
    }
    else
    {
        SHOW_VIDEO_ERR(("Driver Layer do not support this function yet"));
    }
    if (u8ErrCnt != u8CurrErrCnt)
    {
        MApi_XC_FreezeImg(TRUE, eWindow);
        bEnErrFreeze = TRUE;
        u8ErrCnt = u8CurrErrCnt;
        u32ErrFreezeCounter = msAPI_Timer_GetTime0();
    }
    else if( bEnErrFreeze
           &&(msAPI_Timer_DiffTimeFromNow(u32ErrFreezeCounter) > MVD_BAD_VIDEO_FREEZE_TIMEOUT)
           )
    {
        MApi_XC_FreezeImg(FALSE, eWindow);
        bEnErrFreeze = FALSE;
    }
#endif

    // fast timing check for speedup channel change
    if(TRUE == bFastTimingCheck)
    {
        DEBUG_MVD_MONITOR( printf("bFastTimingCheck=1\n"); );
        if(E_VDEC_OK == MApi_VDEC_CheckDispInfoRdy() && TRUE == msAPI_VID_GetVidInfo(&gstVidStatus))
        {
        #if ENABLE_MVD_TWICEFRC
            //let MVOP do double FRC if 25P/30P signal, it will fix the subtitle of VE ouput shaking issue
            //because the VE do not has good FRC capability
            if((gstVidStatus.u32FrameRate < 35000) && (gstVidStatus.u8Interlace==FALSE))
            {
                gstVidStatus.u32FrameRate *=2;
            }
        #endif
            gstPreVidStatus.u16HorSize = gstVidStatus.u16HorSize;
            gstPreVidStatus.u16VerSize = gstVidStatus.u16VerSize;
            gstPreVidStatus.u8AspectRate = gstVidStatus.u8AspectRate;
            gstPreVidStatus.u32FrameRate = gstVidStatus.u32FrameRate;
            gstPreVidStatus.u8Interlace = gstVidStatus.u8Interlace;

            // 2007.12.20 Daniel.Huang: code refine
            #if 0
            (printf( "MVD fast timing change\n" ));
            (printf( "H=%u\n", gstVidStatus.u16HorSize ));
            (printf( "V=%u\n", gstVidStatus.u16VerSize ));
            (printf( "F=%u\n", gstVidStatus.u32FrameRate ));
            (printf( "A=%bu\n", gstVidStatus.u8AspectRate ));
            (printf( "I=%bu\n", gstVidStatus.u8Interlace ));
            #endif

            MApp_VID_PrepareTimingChange(eWindow);
            bMVDDoSetMode = TRUE;
            bFastTimingCheck=FALSE;
            bMVDTimingChange=FALSE; //2007-11-9[daniel.huang]: solve 2 times setmode
            return;
        }

        if(msAPI_Timer_DiffTimeFromNow(u32FFReadyTimer)>MVD_FF_READY_TIMEOUT)
        {
            MApp_MVD_VariableInit();
            bFastTimingCheck = FALSE;
            enMVDVideoStatus = MVD_BAD_VIDEO;
        }
        return;
    }

    //--------------------------------------------
    DEBUG_MVD_MONITOR( printf("bMVDTimingChange=%u\n", bMVDTimingChange); );

    if ( bMVDTimingChange == TRUE )
    {
        DEBUG_MVD_MONITOR( printf("MVD TimingChange~\n"); );
        bMVDTimingChange = FALSE;

        DEBUG_MVD_MONITOR( printf("Set bPrepareChange = TRUE\n"); );
        bPrepareChange = TRUE;

    #if ENABLE_PVR
        enPVRState       PVRState       = MApp_PVR_StateMachineGet();
        enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();

         if((PVRState != E_PVR_STATE_RECORDnPLAYBACK && PVRState != E_PVR_STATE_PLAYBACK)
         &&(TimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING && TimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING))
         {
            MApp_VID_PrepareTimingChange(eWindow);
         }
    #else
         MApp_VID_PrepareTimingChange(eWindow);
    #endif

        return;
    }

    //if ( FALSE == bFirstTimeCheck )
    {
        //bFirstTimeCheck = TRUE;
        //u8MVDDecodeCount = 0;
    }

//    if(msAPI_VID_GetDispRdy())
    if( E_VDEC_OK == MApi_VDEC_CheckDispInfoRdy() )
    {
        DEBUG_MVD_MONITOR( printf("VDEC_CheckDispInfoRdy => OK\n"); );
#if ENABLE_DVB
        bServiceType = msAPI_CM_GetCurrentServiceType();
        u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);
#endif
        if( (
            #if ENABLE_DVB
                msAPI_CM_GetProgramAttribute(bServiceType,u16CurPosition, E_ATTRIBUTE_IS_STILL_PICTURE) == FALSE &&
            #endif
                E_VDEC_FAIL == MApi_VDEC_IsWithValidStream()
            )
           || (FALSE == msAPI_VID_GetVidInfo(&gstVidStatus))
          )
        {
            MVD_DEBUG(printf( "invalid mpeg or video info\n"));

    #if ENABLE_PVR
            enPVRState       PVRState       = MApp_PVR_StateMachineGet();
            enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();

             if((PVRState != E_PVR_STATE_RECORDnPLAYBACK && PVRState != E_PVR_STATE_PLAYBACK)
             &&(TimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING && TimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING))
    #endif
            {
                MApp_MVD_VariableInit();
                bFastTimingCheck = FALSE;
                enMVDVideoStatus = MVD_BAD_VIDEO;
            }
            return;
        }
#if ENABLE_MVD_TWICEFRC
        else
        {
            //let MVOP do double FRC if 25P/30P signal, it will fix the subtitle of VE ouput shaking issue
            //because the VE do not has good FRC capability
            if((gstVidStatus.u32FrameRate < 35000) && (gstVidStatus.u8Interlace==FALSE))
            {
                gstVidStatus.u32FrameRate *=2;
            }
        }
#endif
    }
    else
    {
        DEBUG_MVD_MONITOR( printf("VDEC_CheckDispInfoRdy => NG\n"); );
        if(msAPI_Timer_DiffTimeFromNow(u32FFReadyTimer) > MVD_FF_READY_TIMEOUT)
        {
            MVD_DEBUG(printf("wait FF ready timeout \n"));
            enMVDVideoStatus = MVD_BAD_VIDEO;
            u8MVDTimingStableCount = 0;
            u32FFReadyTimer=msAPI_Timer_GetTime0();
        }
        else
        {
            MVD_DEBUG(printf( "FF not ready \n" ));
            return;
        }
    }

    //--------------------------------------------
    // Check timing stable

    if( ( gstPreVidStatus.u16HorSize != gstVidStatus.u16HorSize )
     || ( gstPreVidStatus.u16VerSize != gstVidStatus.u16VerSize )
    #if AUTO_ASPECT_RATIO
        //( (gstPreVidStatus.u8AspectRate != gstVidStatus.u8AspectRate) && (stGenSetting.g_SysSetting.u8AspectRatioMode==1)) ||
     || ( gstPreVidStatus.u8AspectRate != gstVidStatus.u8AspectRate)
    #endif
     || ( gstPreVidStatus.u32FrameRate != gstVidStatus.u32FrameRate )
     || ( gstPreVidStatus.u8Interlace != gstVidStatus.u8Interlace )
      ) // calvin 070131
    {
        DEBUG_MVD_MONITOR( printf(" gstVidStatus != gstPreVidStatus\n"); );

        // This line will cause set mode 2 times
        //bMVDDoSetMode = TRUE;

        DEBUG_MVD_MONITOR( printf("Set bMVDTimingChange = TRUE\n"); );
        bMVDTimingChange = TRUE;    // Not stable

        u8MVDTimingStableCount = 0;
        gstPreVidStatus.u16HorSize = gstVidStatus.u16HorSize;
        gstPreVidStatus.u16VerSize = gstVidStatus.u16VerSize;
        gstPreVidStatus.u8AspectRate = gstVidStatus.u8AspectRate;
        gstPreVidStatus.u32FrameRate = gstVidStatus.u32FrameRate;
        gstPreVidStatus.u8Interlace = gstVidStatus.u8Interlace; // calvin 070131
    }
    else // gstVidStatus is same
    {
        if ( bPrepareChange == TRUE )
        {
            u8MVDTimingStableCount ++;
            DEBUG_MVD_MONITOR( printf(" u8MVDTimingStableCount = %u\n", u8MVDTimingStableCount); );

            MVD_DEBUG(printf( "Prepare Change! \n" ));
            if ( u8MVDTimingStableCount > MVD_TIMING_STABLE_COUNT )
            {
                // Do set mode here
                // 2007.12.20 Daniel.Huang: code refine
            #if 0
                (printf( "MVD timing change\n" ));
                (printf( "H=%u\n", gstVidStatus.u16HorSize ));
                (printf( "V=%u\n", gstVidStatus.u16VerSize ));
                (printf( "F=%u\n", gstVidStatus.u32FrameRate ));
                (printf( "A=%bu\n", gstVidStatus.u8AspectRate ));
                (printf( "I=%bu\n", gstVidStatus.u8Interlace ));
            #endif


                U16 u16SyncTolerance = 25;
                if( gstVidStatus.u32FrameRate > 0 )
                    u16SyncTolerance = (600000/gstVidStatus.u32FrameRate); // 0.6 frame time = (1000ms / (u32FrameRate/1000))* 0.6 =  (600000/u32FrameRate)

                MApi_VDEC_AVSyncOn(TRUE, 180 ,u16SyncTolerance);          //Sync offset will influence DTV lip-sync timing
                                                           //if you want to change sync offset, please inform audio team and video team

                bMVDDoSetMode = TRUE;
                bPrepareChange = FALSE;
                u8MVDTimingStableCount = 0;
            }
        }
        else
        {
            EN_MVD_VIDEO_STATUS eCheckFrameCntResult = _MApp_VID_CheckVideoStatus();
            if( eCheckFrameCntResult == MVD_BAD_VIDEO )
            {
                enMVDVideoStatus = MVD_BAD_VIDEO;
            }
            else if( eCheckFrameCntResult == MVD_GOOD_VIDEO)
            {
                enMVDVideoStatus = MVD_GOOD_VIDEO;
            }
        }
    }

  #if (ENABLE_BOOTTIME)
    if (gbBootTimeFinish == FALSE && bMVDDoSetMode == TRUE)
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
        printf("[TIME] get disp info = %d\n", gU32TmpTime);
    }
  #endif
}
#endif

//*************************************************************************
//Function name:    MApp_VID_SetMode
//Passing parameter:    none
//Return parameter:    TRUE = MVD has output , FALSE = Mode doesn't have output
//Description:
//*************************************************************************
BOOLEAN MApp_VID_SetMode( SCALER_WIN eWindow)
{
    BOOLEAN bIsHvd = IS_HVD_CODEC(msAPI_VID_GetCodecType());

    if( bIsHvd )
    {
        if( FALSE == bH264DoSetMode )
        {
            return FALSE;
        }
        bH264DoSetMode = FALSE;
    }
    else
    {
        if( FALSE == bMVDDoSetMode )
        {
            return FALSE;
        }

        bMVDDoSetMode = FALSE;
    }

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    memset(&g_tSrcWin, 0, sizeof(MS_WINDOW_TYPE));
    g_bApplyMVOPCrop = FALSE;
    g_u16HorOffset = 0;
    g_u16VerOffset = 0;
#endif

    BOOLEAN bRtn;

    if( bIsHvd )
    {
        bRtn = MApp_AVCH264_SetMode(eWindow);

        g_u32PreVdecFrameCnt = MApi_VDEC_GetFrameCnt();
    }
    else
    {
        bRtn = MApp_MVD_SetMode(eWindow, bIsHvd );
    }

    g_bSetModeDone = TRUE;

    return bRtn;
}

#if DTV_XC_ENABLE_RFBL
BOOL g_bDTVIsRFBL;
#endif

void MApp_MVD_Set_PQModeInfo(VDEC_DispInfo* pstVDEC_DispInfo)
{
    // Pass mode info to drvPQ
    MS_PQ_Mode_Info stMS_PQ_Mode_Info;
    memset(&stMS_PQ_Mode_Info, 0, sizeof(stMS_PQ_Mode_Info) );

    MDrv_PQ_Get_ModeInfo(PQ_MAIN_WINDOW, &stMS_PQ_Mode_Info);

    stMS_PQ_Mode_Info.bInterlace = pstVDEC_DispInfo->u8Interlace;
    stMS_PQ_Mode_Info.u16input_hsize = pstVDEC_DispInfo->u16HorSize;
    stMS_PQ_Mode_Info.u16input_vsize = pstVDEC_DispInfo->u16VerSize;
    stMS_PQ_Mode_Info.u16input_vfreq = pstVDEC_DispInfo->u32FrameRate/100;
    stMS_PQ_Mode_Info.bFBL = MApi_XC_IsCurrentFrameBufferLessMode();
    MDrv_PQ_Set_ModeInfo(PQ_MAIN_WINDOW, PQ_INPUT_SOURCE_DTV, &stMS_PQ_Mode_Info);

    MS_U16 u16PqSrcType = QM_InputSourceToIndex(PQ_MAIN_WINDOW, PQ_INPUT_SOURCE_DTV);
    printf(" u16PQSrcType=%u(%s)\n", u16PqSrcType, MDrv_PQ_GetSrcTypeName_2(PQ_MAIN_WINDOW,u16PqSrcType) );
}

//*************************************************************************
//Function name:    MApp_MVD_SetMode
//Passing parameter:    none
//Return parameter:    TRUE = MVD has output , FALSE = Mode doesn't have output
//Description:
//*************************************************************************
BOOLEAN MApp_MVD_SetMode( SCALER_WIN eWindow, BOOLEAN bIsHVD )
{
    BOOL bDTVUseFBL = FALSE;
    U32 u32MVDPicCounterCheckTimer;
    U8 u8TurnOffDestination = DISABLE;

    bIsHVD = bIsHVD;

/*
    if ( FALSE == bMVDDoSetMode )
    {
        return FALSE;
    }

    bMVDDoSetMode = FALSE;
*/

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););


#if (ENABLE_CHCHANGETIME)
    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime);
    printf("\n>>>[ChChangeTime][Start_MVD_SetMode] =[%d]\n", gU32TmpTime);
#endif
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("MVD_SetMode - Start" );
#endif

#if AUTO_ASPECT_RATIO
    if(gstVidStatus.u8AspectRate==ASP_4TO3)
    {
        sbIsAspectRatioWide = FALSE;
        MVD_DEBUG(printf( "sbIsAspectRatio 4TO3 \n" ));
    }
    else if(gstVidStatus.u8AspectRate==ASP_16TO9)
    {
        sbIsAspectRatioWide = TRUE;
        MVD_DEBUG(printf( "sbIsAspectRatio WIDE:ASP_16TO9 \n" ));
    }
    else if(gstVidStatus.u8AspectRate==ASP_1TO1)
    {
        //720*480 must be 4:3 ( Input H/ Input V > 1.5 => wide)
        if( ((U32)gstVidStatus.u16HorSize*2) > ((U32)gstVidStatus.u16VerSize*3) )
            sbIsAspectRatioWide = TRUE;
        else
            sbIsAspectRatioWide = FALSE;

        MVD_DEBUG(printf( "sbIsAspectRatio WIDE&ASP_1TO1 \n" ));
    }
    else if(gstVidStatus.u8AspectRate==ASP_221TO100)
    {
        sbIsAspectRatioWide = TRUE;
        MVD_DEBUG(printf( "ASP_221TO100 \n" ));
    }
#endif

#if (MirrorEnable)
    MApp_MVOP_SetMirrorMode(ENABLE);
#endif

#if (DTV_USE_FBL)
    bDTVUseFBL = msAPI_VID_IsNeedFrameBufferLessMode(&gstVidStatus);
#endif

    if( bDTVUseFBL )
    {
        FBLMSG("Enable FBL\n");
        MApi_XC_EnableFrameBufferLess(TRUE);
    }
    else
    {
        MApi_XC_EnableFrameBufferLess(FALSE);
    }


    // Check QMAP if need RFBL...
    //MApp_MVD_Set_PQModeInfo( &gstVidStatus );


#if DTV_XC_ENABLE_RFBL
    g_bDTVIsRFBL = FALSE;

    if(bDTVUseFBL == FALSE)
    {
        if( gstVidStatus.u8Interlace == FALSE && gstVidStatus.u16VerSize >= 750 )
        {
            if( gstVidStatus.u32FrameRate < 48500 )
            {
                g_bDTVIsRFBL = TRUE;
            }
        }
    }
#endif

    if( bDTVUseFBL
#if DTV_XC_ENABLE_RFBL
      ||g_bDTVIsRFBL
#endif
      )
    {
        if((gstVidStatus.u32FrameRate > 24500)&&(gstVidStatus.u32FrameRate <= 25000))
        {
            //stVidStatus.u32FrameRate = 25000;
        }
        else if((gstVidStatus.u32FrameRate > 49500)&&(gstVidStatus.u32FrameRate <= 50000))
        {
            gstVidStatus.u32FrameRate = gstVidStatus.u32FrameRate/2; //25
        }
        else if((gstVidStatus.u32FrameRate > 23500)&&(gstVidStatus.u32FrameRate <= 24000) )
        {
            gstVidStatus.u32FrameRate = (U32)gstVidStatus.u32FrameRate*5/4; //30
        }
        else if((gstVidStatus.u32FrameRate > 29500)&&(gstVidStatus.u32FrameRate <= 30000))
        {
            //~30
        }
        else
        {
            gstVidStatus.u32FrameRate = 30000;
        }
        if( gstVidStatus.u8Interlace == 0 )
        {
            gstVidStatus.u32FrameRate = gstVidStatus.u32FrameRate << 1;
        }
    }
    else
    {
    }

    FBLMSG("MVD Video W=%u, H=%u\n\n", gstVidStatus.u16HorSize, gstVidStatus.u16VerSize);
    //FBLMSG("MVD vop W=%u, H=%u\n",     MDrv_MVOP_GetHSize(), MDrv_MVOP_GetVSize());

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    if(MApi_XC_IsCurrentFrameBufferLessMode())
    {
        enMVOPVideoType = MVOP_MPG;
        MApp_Scaler_EnableOverScan(FALSE);
        MApp_Scaler_Adjust_AspectRatio_FBL(stSystemInfo[eWindow].enAspectRatio, &g_tSrcWin);
        U16 u16VDE = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom + 2 * g_u16VerOffset;
        MApp_Scaler_SetFixVtotal(gstVidStatus.u8Interlace, (U16)gstVidStatus.u32FrameRate, u16VDE);
    }
#endif

//    msAPI_VID_SetMVDOutput(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), &gstVidStatus );
    msAPI_VID_SetOutput(&gstVidStatus );

    if( (gstVidStatus.u16HorSize <= 720) && (gstVidStatus.u16VerSize <= 576) )
        MApi_XC_Sys_SetSrcIsHD(FALSE,eWindow);
    else
        MApi_XC_Sys_SetSrcIsHD(TRUE,eWindow);


    g_u32VDecPicCountTimer = msAPI_Timer_GetTime0();

    enMVDVideoStatus = MVD_GOOD_VIDEO;        //move here for MHEG5 check

    // Set ARC 16:9 in Edit mode or Auto Scanning state
    //stSystemInfo.enAspectRatio = MApp_Scaler_GetAspectRatio(ST_VIDEO.eAspectRatio);
    MAPI_XC_MUX_TRIGGER_PATH_SYNC_EVENT(SYS_INPUT_SOURCE_TYPE(eWindow),NULL);

#if ENABLE_TTX
    // Should Set Video window again for TTX Rendering Phase Video+TTX model
    if (MApp_TTX_IsTeletextOn() == TRUE)
    {
        MApp_TTX_SetRP_Video_TTX(TRUE);
    }
#endif

    MApp_CheckBlockProgramme();// Check DTV/ATV LOCK and ENABLE/DISABLE VE OUT

    // Enable screen mute client_vdec
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_VDEC, ENABLE, 0, eWindow);

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)
{
    if (E_VDEC_OK != MApi_VDEC_SetBlueScreen(FALSE))
    {
        printf("MApi_VDEC_SetBlueScreen (OFF) Fail\n");
    }
}
#endif

    u8TurnOffDestination = ENABLE;
    // signal detected. Enable all destination.
    MAPI_XC_MUX_TRIGGER_DEST_ON_OFF_EVENT(SYS_INPUT_SOURCE_TYPE(eWindow),&u8TurnOffDestination);

    MApi_XC_Enable_TwoInitFactor(TRUE, MAIN_WINDOW);

    u32MVDPicCounterCheckTimer=msAPI_Timer_GetTime0();

    MVD_DEBUG(printf( "MApp_MVD_SetMode good\n" ));

#if (ENABLE_CHCHANGETIME)
    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime);
    printf("\n>>>[ChChangeTime][End_MVD_SetMode] =[%d]\n", gU32TmpTime);
#endif

    //g_bSetModeDone = TRUE;

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("MVD_SetMode - End" );
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););

    return TRUE;
}

//*************************************************************************
//Function name:    MApp_VID_PrepareTimingChange
//Passing parameter:    eWindow
//Return parameter:    none
//Description:
//*************************************************************************
void MApp_VID_PrepareTimingChange(SCALER_WIN eWindow)
{
    if(IS_HVD_CODEC(msAPI_VID_GetCodecType()))//msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
        MApp_AVCH264_PrepareTimingChange(eWindow);
    else
        MApp_MVD_PrepareTimingChange(eWindow);
}

//*************************************************************************
//Function name:    MApp_MVD_PrepareTimingChange
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************
void MApp_MVD_PrepareTimingChange ( SCALER_WIN eWindow )
{
    MVD_DEBUG(printf( "MApp_MVD_PrepareTimingChange \n" ));

    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, eWindow);

    // calvin 070130, add a timeout for MVD first frame check
    u32FFReadyTimer = msAPI_Timer_GetTime0();
}

/*
void MApp_MVD_ValidFlagMonitor(void)
{
    if ( msAPI_Timer_DiffTimeFromNow(u32MonitorMVDValidTimer) > 3000)
    {
        if (MApi_VDEC_IsWithValidStream() == E_VDEC_OK)
        {
            fCurMVDValidFlag = TRUE;
        }
        else
        {
            fCurMVDValidFlag = FALSE;
        }
        u32MonitorMVDValidTimer =  msAPI_Timer_GetTime0();
    }
}
*/

BOOLEAN MApp_MVD_IsAspectRatioWide(void)
{
    if( sbIsAspectRatioWide    == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOLEAN MApp_VID_Is_VdecStatusGood(void)
{
    if( enMVDVideoStatus == MVD_GOOD_VIDEO )
        return TRUE;

    return FALSE;
}

#endif

#if (ENABLE_DTV)
static U16 g_VDEC_u16VdecNotRunCnt = 0;
static U32 g_VDEC_u32VdecNotRunTimer = 0;
#endif
//*************************************************************************
//Function name:    MApp_AVCH264_VariableInit
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************
void MApp_AVCH264_VariableInit( void )
{
    bH264TimingCheck = TRUE;
    bH264DoSetMode = FALSE;
    sbIsAspectRatioWide = FALSE;
    bH264FastReset = TRUE;
#if (ENABLE_DTV)
    g_VDEC_u16VdecNotRunCnt = 0;
    g_VDEC_u32VdecNotRunTimer = 0;
#endif
    memset( &gstVidStatus, 0, sizeof( VDEC_DispInfo ) );
    memset( &gstPreVidStatus, 0, sizeof( VDEC_DispInfo ) );

    enMVDVideoStatus = MVD_UNKNOWN_VIDEO;
}

#if (ENABLE_DTV)

//*************************************************************************
//Function name:    MApp_MVD_TimingMonitor
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************

void MApp_AVCH264_TimingMonitor( SCALER_WIN eWindow )
{
#if ENABLE_DVB
    MEMBER_SERVICETYPE bServiceType;
    U16 u16CurPosition;
    BOOL bStillPic = FALSE;
#endif

    U32 u32DisplayReady = 0;
    VDEC_DispInfo NewVidStatus;

    memset(&NewVidStatus, 0, sizeof(VDEC_DispInfo));

    if(TRUE == bH264TimingCheck || E_VDEC_OK == MApi_VDEC_IsSeqChg())
    {
        u32DisplayReady = MApi_VDEC_CheckDispInfoRdy();

        if(E_VDEC_OK == MApi_VDEC_CheckDispInfoRdy())
        {
            if (!msAPI_VID_GetVidInfo(&NewVidStatus))
            {
                MS_DEBUG_MSG(printf("Get SVD Seq Info failed\n"));
            }

            // Error handle for large framerate
            if ( NewVidStatus.u32FrameRate > 60000 )
            {
                NewVidStatus.u32FrameRate = 30000;  // use 30 as default framerate
            }

#if ENABLE_DVB
            bServiceType = msAPI_CM_GetCurrentServiceType();
            u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);
            bStillPic = msAPI_CM_GetProgramAttribute(bServiceType,u16CurPosition, E_ATTRIBUTE_IS_STILL_PICTURE);
            if( ((TRUE == bStillPic) ||  //for still picture video, do not check fr<10fps
                 ((FALSE == bStillPic) && (10000 <= NewVidStatus.u32FrameRate))) &&
                (NewVidStatus.u32FrameRate<= 200000) &&
                (NewVidStatus.u16HorSize!= 0)  && (NewVidStatus.u16VerSize!= 0)   )
#else
            if( ( 10000 <= NewVidStatus.u32FrameRate) && ( NewVidStatus.u32FrameRate<= 200000) &&
                 (NewVidStatus.u16HorSize!= 0)  && (NewVidStatus.u16VerSize!= 0)   )
#endif
            {
#if ENABLE_MVD_TWICEFRC
                //let MVOP do double FRC if 25P/30P signal, it will fix the subtitle of VE ouput shaking issue
                //because the VE do not has good FRC capability

                if((NewVidStatus.u32FrameRate < 35000) && (NewVidStatus.u8Interlace==FALSE))
                {
                    NewVidStatus.u32FrameRate *=2;
                }
#endif //ENABLE_MVD_TWICEFRC

        #if ENABLE_DTV
                if ( NewVidStatus.u32FrameRate < 10000 )
                {
                    printf("FrameRate = %ld, force to 30fps for still picture\n", NewVidStatus.u32FrameRate);
                    NewVidStatus.u32FrameRate = 30000;  // use 30 as default framerate
                }
        #endif


                memcpy(&gstVidStatus, &NewVidStatus, sizeof(VDEC_DispInfo));

                gstVidStatus.u8AFD = MApi_VDEC_GetActiveFormat();

                memcpy(&gstPreVidStatus, &gstVidStatus, sizeof(VDEC_DispInfo));



                U16 u16SyncTolerance = 25;
                if(NewVidStatus.u32FrameRate > 0)
                    u16SyncTolerance = (600000/NewVidStatus.u32FrameRate); // 0.6 frame time = (1000ms / (u32FrameRate/1000))* 0.6 =  (600000/u32FrameRate)



                MApi_VDEC_AVSyncOn(TRUE, 180 ,u16SyncTolerance);          //Sync offset will influence DTV lip-sync timing

                MApp_VID_PrepareTimingChange(eWindow);
                bH264TimingCheck = FALSE;
                bH264DoSetMode = TRUE;
                bH264FastReset = FALSE;
                bH264FirstTimeCheck = FALSE;
            }
            else
            {
                MS_DEBUG_MSG(printf("h264 get invalid frame rate:%ld\n" , NewVidStatus.u32FrameRate  ));
                if (E_VDEC_OK != MApi_VDEC_SetBlueScreen(FALSE))
                {
                    MS_DEBUG_MSG(printf("MApi_VDEC_SetBlueScreen Fail\n"));
                }
            }
        }

    }
    else
    {
        if (!msAPI_VID_GetVidInfo(&gstVidStatus))
        {
            MS_DEBUG_MSG(printf("Get Vid Info failed\n"));
        }
#if ENABLE_MVD_TWICEFRC
        else
        {
            //let MVOP do double FRC if 25P/30P signal, it will fix the subtitle of VE ouput shaking issue
            //because the VE do not has good FRC capability
            // Error handle for large framerate
            if ( gstVidStatus.u32FrameRate > 60000 )
            {
                gstVidStatus.u32FrameRate = 30000;  // use 30 as default framerate
            }

            if((gstVidStatus.u32FrameRate < 35000) && (gstVidStatus.u8Interlace==FALSE))
            {
                gstVidStatus.u32FrameRate *=2;
            }
        }
#endif //ENABLE_MVD_TWICEFRC
        gstVidStatus.u8AFD = MApi_VDEC_GetActiveFormat();
        //printf("Check SEQ \n");
        if((gstPreVidStatus.u16HorSize != gstVidStatus.u16HorSize) ||
           (gstPreVidStatus.u16VerSize != gstVidStatus.u16VerSize) ||
           (gstPreVidStatus.u32FrameRate != gstVidStatus.u32FrameRate) ||
           (gstPreVidStatus.u8AspectRate != gstVidStatus.u8AspectRate)||//NorDig task 05:12 => aspect ratio run time change
           (gstPreVidStatus.u8Interlace != gstVidStatus.u8Interlace))
        {
            memcpy(&gstPreVidStatus, &gstVidStatus, sizeof(VDEC_DispInfo));


            U16 u16SyncTolerance = 25;
            if(gstVidStatus.u32FrameRate > 0)
                u16SyncTolerance = (600000/gstVidStatus.u32FrameRate); // 0.6 frame time = (1000ms / (u32FrameRate/1000))* 0.6 =  (600000/u32FrameRate)


            MApi_VDEC_AVSyncOn(TRUE, 180 ,u16SyncTolerance);          //Sync offset will influence DTV lip-sync timing
                                                         //if you want to change sync offset, please inform audio team and video team
            MApp_VID_PrepareTimingChange(eWindow);
            bH264DoSetMode = TRUE;
            //printf("SEQ Chg \n");
        }

    }

    if(bH264FastReset && !bH264FirstTimeCheck)
    {
    #if( ENABLE_ATSC )
        CC_SourceFuns.StopMVDParser();
        CC_SourceFuns.Stop708Parsing();
    #endif
        msAPI_VID_Command(MSAPI_VID_STOP);
        MDrv_MVOP_Enable(FALSE);
#if ENABLE_PVR
        if( MApp_PVR_IsPlaybacking())
        {
            msAPI_VID_Init(TRUE, E_VDEC_SRC_MODE_TS_FILE);
        }
        else
#endif
        {
            //msAPI_VID_Init(TRUE, E_VDEC_SRC_MODE_DTV);
            //1042192: [PLM/DF151223-00500][#16_STREAM][Basic Function][Video]Play stream"8124_BRO_hf032pskipmb_basicC_576i.trp"the vertical bar move abnormal
            msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV); // drop error frame. mpeg2 also drop error frame
        }

        msAPI_VID_Command(MSAPI_VID_PLAY);
        bH264FastReset = FALSE;
    #if( ENABLE_ATSC )
        MApp_CC_Initialize();
        MApp_ClosedCaption_GetUserCmd();
    #endif
    }

    if( E_VDEC_OK == MApi_VDEC_IsAlive() )
    {
        g_VDEC_u16VdecNotRunCnt = 0;
    }
    else
    {
        if( msAPI_Timer_DiffTime_2(g_VDEC_u32VdecNotRunTimer, MsOS_GetSystemTime()) > 200 ) //200ms
        {
            g_VDEC_u16VdecNotRunCnt ++;
            g_VDEC_u32VdecNotRunTimer = MsOS_GetSystemTime();
        }
    }

    //cause the av sync threshold is 5.5 .
    if (g_VDEC_u16VdecNotRunCnt == 30) //Remark: VDEC notAlive 6s, channel change to recover
    {
        printf("\r\n [MST]...... H.264 Vdec Reset Action :%d,u16VdecNotRunCnt:%d\n",MApi_VDEC_IsAlive(),g_VDEC_u16VdecNotRunCnt);
        g_VDEC_u16VdecNotRunCnt = 0;
        MApp_ChannelChange_DisableChannel(FALSE,MAIN_WINDOW);
        msAPI_Timer_Delayms(500);
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
    }


    if(bH264DoSetMode == FALSE)
    {
    #if 0
        MS_U32 u32stc32 = ~0;
        MS_U32 u32stc = ~0;
        MApi_DMX_Stc_Get(&u32stc32, &u32stc);
        printf("\r\nSysTime: %ld, ErrCnt: %lu, FrmCnt: %lu, SkipCnt: %lu, DropCnt: %lu, STC: %lu, PTS: %lu, Delta: %lld\n",
        MsOS_GetSystemTime(),
        MApi_VDEC_GetErrCnt(),
        MApi_VDEC_GetFrameCnt(),
        MApi_VDEC_GetSkipCnt(),
        MApi_VDEC_GetDropCnt(),
        u32stc / 90,
        MApi_VDEC_GetPTS(),
        MApi_VDEC_GetVideoPtsStcDelta() / 90);
        printf("AVSync On=%x, ReachSync=%x, Freerun=%x, StartSync=%x\n",
        MApi_VDEC_IsAVSyncOn(),
        MApi_VDEC_IsReachSync(),
        MApi_VDEC_IsFreerun(),
        MApi_VDEC_IsStartSync());
    #endif

        EN_MVD_VIDEO_STATUS eCheckFrameCntResult = _MApp_VID_CheckVideoStatus();
        if( eCheckFrameCntResult == MVD_BAD_VIDEO )
        {
            enMVDVideoStatus = MVD_BAD_VIDEO;
        }
        else if( eCheckFrameCntResult == MVD_GOOD_VIDEO)
        {
            enMVDVideoStatus = MVD_GOOD_VIDEO;
        }

    }

    #if (ENABLE_BOOTTIME)
    if (gbBootTimeFinish == FALSE && bH264DoSetMode == TRUE)
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
        printf("[TIME] get disp info = %d\n", gU32TmpTime);
    }
    #endif

//#if DEBUG_H264
//    MDrv_VDEC_DebugMonitor(E_VDEC_SVD);
//#endif
}

//*************************************************************************
//Function name:    MApp_AVCH264_SetMode
//Passing parameter:    none
//Return parameter:    TRUE = H264 has output , FALSE = Mode doesn't have output
//Description:
//*************************************************************************
BOOLEAN MApp_AVCH264_SetMode( SCALER_WIN eWindow )
{
    U8 u8TurnOffDestination = ENABLE;
    BOOL bDTVUseFBL = FALSE;

/*
    if ( FALSE==bH264DoSetMode )
    {
        return FALSE;
    }
    bH264DoSetMode = FALSE;
*/
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

#if (ENABLE_CHCHANGETIME)
    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime);
    printf("\n>>>[ChChangeTime][Start_AVCH264_SetMode] =[%d]\n", gU32TmpTime);
#endif

    if(!msAPI_VID_AVCH264IsAspectRatioWide(&gstVidStatus,&sbIsAspectRatioWide))
    {
        MVD_DEBUG( printf( "msAPI_VID_AVCH264IsAspectRatioWide error \n" ) );
    }

#if (MirrorEnable)
    MApp_MVOP_SetMirrorMode(ENABLE);
#endif

    DEBUG_HVD_TIMING( printf("CodecType=%u\n", msAPI_VID_GetCodecType()); );
    DEBUG_HVD_TIMING( printf("u16HorSize=%u, u16VerSize=%u, u32FrameRate=%u, Interlace=%u\n", gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, gstVidStatus.u32FrameRate, gstVidStatus.u8Interlace); );

#if (DTV_USE_FBL)
    bDTVUseFBL = msAPI_VID_IsNeedFrameBufferLessMode(&gstVidStatus);
#endif

    if( bDTVUseFBL == FALSE )
    {
        // 1080P/i
        if( (gstVidStatus.u16HorSize >= 1900)&&(gstVidStatus.u16VerSize >= 1060) )
        {
            if( gstVidStatus.u8Interlace ) // Interlace
            {
            }
            else // Non-Interlace
            {
                if( gstVidStatus.u32FrameRate >= 48500 ) // >= 48.5 Hz
                {
                #if( SCALER_USE_FBL_IN_DTV_H265_1080P_50P )
                    if( msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_HEVC )
                    {
                        bDTVUseFBL = TRUE;
                    }
                #endif
                }
            }
        }
    }

    if( bDTVUseFBL )
    {
        FBLMSG("Enable FBL\n");
        MApi_XC_EnableFrameBufferLess(TRUE);
    }
    else
    {
        MApi_XC_EnableFrameBufferLess(FALSE);
    }

    //MApp_MVD_Set_PQModeInfo( &gstVidStatus );


#if DTV_XC_ENABLE_RFBL
    g_bDTVIsRFBL = FALSE;

    if( bDTVUseFBL == FALSE && gstVidStatus.u8Interlace == FALSE && gstVidStatus.u16VerSize >= 750 )
    {
        if( gstVidStatus.u32FrameRate < 48500 )
        {
            g_bDTVIsRFBL = TRUE;
        }
    }
#endif

    if( bDTVUseFBL
#if DTV_XC_ENABLE_RFBL
      || g_bDTVIsRFBL
#endif
        )
    {
        if((gstVidStatus.u32FrameRate > 24500)&&(gstVidStatus.u32FrameRate <= 25000))
        {
            //stVidStatus.u32FrameRate = 25000;
        }
        else if((gstVidStatus.u32FrameRate > 49500)&&(gstVidStatus.u32FrameRate <= 50000))
        {
            gstVidStatus.u32FrameRate = gstVidStatus.u32FrameRate/2; //25
        }
        else if((gstVidStatus.u32FrameRate > 23500)&&(gstVidStatus.u32FrameRate <= 24000) )
        {
            gstVidStatus.u32FrameRate = (U32)gstVidStatus.u32FrameRate*5/4; //30
        }
        else if((gstVidStatus.u32FrameRate > 29500)&&(gstVidStatus.u32FrameRate <= 30000))
        {
            //~30
        }
        else
        {
            gstVidStatus.u32FrameRate = 30000;
        }

        if( gstVidStatus.u8Interlace == 0 )
        {
            gstVidStatus.u32FrameRate = gstVidStatus.u32FrameRate << 1;
        }

        DEBUG_HVD_TIMING( printf("2. u16HorSize=%u, u16VerSize=%u, u32FrameRate=%u,Interlace=%u\n", gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, gstVidStatus.u32FrameRate, gstVidStatus.u8Interlace); );
    }
    else
    {
    }

    // FBLMSG("HVD vop W=%u, H=%u\n",     MDrv_MVOP_GetHSize(), MDrv_MVOP_GetVSize());


#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    if(MApi_XC_IsCurrentFrameBufferLessMode())
    {
        enMVOPVideoType = MVOP_H264;
        g_u16StripSize = gstVidStatus.u16HorSize;
        MApp_Scaler_EnableOverScan(FALSE);
        MApp_Scaler_Adjust_AspectRatio_FBL(stSystemInfo[eWindow].enAspectRatio, &g_tSrcWin);
        U16 u16VDE = gstVidStatus.u16VerSize - gstVidStatus.u16CropTop - gstVidStatus.u16CropBottom + 2 * g_u16VerOffset;
        MApp_Scaler_SetFixVtotal(gstVidStatus.u8Interlace, (U16)gstVidStatus.u32FrameRate, u16VDE);
    }
#endif

    //    msAPI_VID_SetH264Output(&gstVidStatus);
    msAPI_VID_SetOutput(&gstVidStatus);

    if(gstVidStatus.u16HorSize <=720&&gstVidStatus.u16VerSize<=576)
        MApi_XC_Sys_SetSrcIsHD(FALSE,eWindow);
    else
        MApi_XC_Sys_SetSrcIsHD(TRUE,eWindow);

    // Set ARC 16:9 in Edit mode or Auto Scanning state
    //stSystemInfo.enAspectRatio = MApp_Scaler_GetAspectRatio(ST_VIDEO.eAspectRatio);
    MAPI_XC_MUX_TRIGGER_PATH_SYNC_EVENT(SYS_INPUT_SOURCE_TYPE(eWindow),NULL);

#if ENABLE_TTX
    // Should Set Video window again for TTX Rendering Phase Video+TTX model
    if (MApp_TTX_IsTeletextOn() == TRUE)
    {
        MApp_TTX_SetRP_Video_TTX(TRUE);
    }
#endif

    // Enable screen mute client_vdec
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_VDEC, ENABLE, 0, eWindow);

    u8TurnOffDestination = ENABLE;
    // signal detected. Enable all destination.
    MAPI_XC_MUX_TRIGGER_DEST_ON_OFF_EVENT(SYS_INPUT_SOURCE_TYPE(eWindow),&u8TurnOffDestination);
    MApi_XC_Enable_TwoInitFactor(TRUE, MAIN_WINDOW);

//    msAPI_VID_AVCH264GetDispInfoDone();
    if (E_VDEC_OK != MApi_VDEC_SetBlueScreen(FALSE))
    {
        MS_DEBUG_MSG(printf("MApi_VDEC_SetBlueScreen Fail\n"));
    }

    MVD_DEBUG(printf( "MApp_AVCH264_SetMode good\n" ));

#if (ENABLE_CHCHANGETIME)
    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime);
    printf("\n>>>[ChChangeTime][End_AVCH264_SetMode] =[%d]\n", gU32TmpTime);
#endif

	g_u32VDecPicCountTimer = msAPI_Timer_GetTime0();

    enMVDVideoStatus = MVD_GOOD_VIDEO;

    //g_bSetModeDone = TRUE;

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););

    return TRUE;
}

//*************************************************************************
//Function name:    MApp_AVCH264_PrepareTimingChange
//Passing parameter:    none
//Return parameter:    none
//Description:
//*************************************************************************
void MApp_AVCH264_PrepareTimingChange ( SCALER_WIN eWindow )
{
    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, eWindow);
    MVD_DEBUG(printf( "MApp_AVCH264_PrepareTimingChange \n" ));
    // calvin 070130, add a timeout for MVD first frame check
    u32FFReadyTimer=msAPI_Timer_GetTime0();
}

#if (MirrorEnable)
void MApp_MVOP_SetMirrorMode(BOOL bMVOPMirror)
{
    if(bMVOPMirror)
    {
        if(MIRROR_NORMAL != MApi_XC_GetMirrorModeType())
        {
            FBLMSG("Disable Scaler mirror. use mvop mirror\n");
            MApi_XC_EnableMirrorMode(FALSE);
        }
        if(MApp_Image_GetMirror())
        {
            #if ENABLE_PANEL_H_MIRROR
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_HORIZONTALL);
            #else
            MDrv_MVOP_SetVOPMirrorMode(ENABLE, E_VOPMIRROR_HORIZONTALL);
            #endif
            MDrv_MVOP_SetVOPMirrorMode(ENABLE, E_VOPMIRROR_VERTICAL);

        #if(ENABLE_VE)
            #if ENABLE_PANEL_H_MIRROR
            MDrv_VE_EnableMirrorMode(MS_VE_MIRROR_V_ONLY);
            #else
            MDrv_VE_EnableMirrorMode(MS_VE_MIRROR_HV);
            #endif
        #endif
        }
#if ENABLE_PANEL_H_MIRROR
        else
        {
            MDrv_MVOP_SetVOPMirrorMode(ENABLE, E_VOPMIRROR_HORIZONTALL);
            #if(ENABLE_VE)
            MDrv_VE_EnableMirrorMode(MS_VE_MIRROR_H_ONLY);
            #endif
        }
#endif
    }
    else
    {
        if(MApp_Image_GetMirror())
        {
            //Leaving storage source, so switch to XC mirror
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_HORIZONTALL);
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_VERTICAL);
        #if(ENABLE_VE)
            MDrv_VE_EnableMirrorMode(MS_VE_MIRROR_NORMAL);
        #endif

            msAPI_XC_EnableMirrorMode(TRUE);
        }
#if ENABLE_PANEL_H_MIRROR
        else
        {
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_HORIZONTALL);

            msAPI_XC_EnableMirrorMode(FALSE);

        #if(ENABLE_VE)
            MDrv_VE_EnableMirrorMode(MS_VE_MIRROR_H_ONLY);
        #endif
        }
#endif
    }
}
#endif

#endif

#undef MAPP_MVDMODE_C
