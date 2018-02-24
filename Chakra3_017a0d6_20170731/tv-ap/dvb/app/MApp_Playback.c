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
/*
++++++++++++++++++++++++++++++++++???????????????++++++++++++++++++++++++++++++++++++++++++??????????????????????++++++++++++++++++++++++++++++++++++++++=++????
++++++++++++++++++++++++++++++++++IIIIIIIIIIIIII????????????????????????????????????????????IIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++++++++++++++++++++++++++++++IIIIIIIIIIII????????????????????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=+IIIIIIIIIII+++++++++++++++?$$$$$$$$$77II??????????I???????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++++DMMMMMMMMMMMZI++++++++++++=NMMMMMMMMMMMZ$?I77$$$$$$I?????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMD7=+++++++++IMMMMMMMMMMMMM8OZZ$7I???????????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMM8++++++++++DMMMMMMMMMMMMMD8$I?????????????????III???????????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++=+?=8MMMMMMMMMMMMMMZZ++++++?DMMMMMMMMMMMMMMZZ???????????????IIIIIIIIIII????????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I=DMMMMMMMMMMMMMMMN?=++++8MMMMMMMMMMMMMMMZ$??????????????IIIIIIIIIIIIII??????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I+8MMMMMMMMMMMMMMMMD?=+IDMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIII????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++?I+8MMMMMMMMMMMMMMMMMOI~OMMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIIII????????????IIIIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++II+8MMMMMMMMMMMNNMMNMND8MMNNMMNNMMMMMMMMMMZ$????????????IZZ8888OZ7IIIIIIIIIIIIIIIIIIIIIIZD7IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++++II+8MMMMMMMMMMII????????OOOOOOZ8MMMMMMMMMMZ$??????????ZDMMMMMDDDNND87IIIIIIIIIIIIIII?Z8MMDIIIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI++++++7$ZZZZZZZOOMMMMMMMMMMZ$??????IINMMMMMMD+IIII7I7DMMIIIIIIII?I8NMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI+++++I$ZZZZZZZZ$ZMMMMMMMMMMZ$??????IMMMMMMMMMI??????IIO87IIIIII?DMMMMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++?III+8MMMMMMMMMMI++=$$ZZZZZZZZZIIZMMMMMMMMMMZ$??????MMMMMMMMMMMZ??????????????IIIMMMMMMMMMMD$ZZZZIIIIIIIIII+Z8DDNMMMDDDOO$I?????????????IIIII$ZZZ7IIII7O8887II
+?IIII+8MMMMMMMMMMI++7ZZZZZZZZZZI+IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMM$????????????OMMMMMMMMMMMMMMMMMMNIIIIIIIII8MMMD888DMMMMMMMND$?????????8MMMMMMMMMMOII78MMMMM8?I
+?IIII+8MMMMMMMMMMI?7ZZZZZZZZZZ?++IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMMMM8??????????+++?MMMMMMMMMM8IIIIIIIIIIIZMMM77IIIIIII8MMMMMMMMND?II????8MMMMMMMMMMOODNZII7Z8I7I
?IIIII+8MMMMMMMMMMZZZZZZZZZZZZI+++IZMMMMMMMMMMZ$??????NMMMMMMMMMMMMMMDII??????????IMMMMMMMMMM8IIIIIIIIIIIO8ZI?IIIIIIIIZDMMMMMMMMMD??????8MMMMMMMMMMN8D7IIIIIIIII
?IIIII+8MMMMMMMMMNZZZZZZZZZZZZ++++?ZMMMMMMMMMMZ$??????ZMMMMMMMMMMMMMMMMN7?????????IMMMMMMMMMM8IIIIIIIIIIIIIII?IIIIIIIIZDMMMMMMMMMMI?????8MMMMMMMMMM8IIIIIIIIIIII
?IIIII+8MMMMMMMMN8ZZZZZZZZZZZ?++++?ZMMMMMMMMMMZ$??????I8MMMMMMMMMMMMMMMM8?????????IMMMMMMMMMMO?IIIIIIIIIIIII7I7777777IODMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMNZZZZZZZZZZZZ7+++++?ZMMMMMMMMMMZ$????????8MMMMMMMMMMMMMMMMDD???????IMMMMMMMMMMO??IIIIIIIII7DMMMMMMMDDMDDNMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNZZZZZZZZZZZZ$++++++?ZMMMMMMMMMMZ$I????????7NMMMMMMMMMMMMMMMMDI?????IMMMMMMMMMMO????IIIIIZ8MMMMMMMM7III7ONMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNOZZZZZZZZZZZ7++++++?ZMMMMMMMMMMZ$III??????+IMMMMMMMMMMMMMMMMN$+????IMMMMMMMMMMO????IIII?NMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMNOZZZZZZZZ?++++++?ZMMMMMMMMMMZ$IIII????????ZMMMMMMMMMMMMMMMO?????IMMMMMMMMMMZ?????III$MMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMM?$ZZZZZZ$+++++++?ZMMMMMMMMMMZ$IIIIIIIIII???ZMMMMMMMMMMMMMMDZ????IMMMMMMMMMMZ?????IIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII=DMMMMMMMMMM?++7ZZZ7?+++++++IZMMMMMMMMMMZ$IIIIIIIIIIIIII7OMMMMMMMMMMMM8?????IMMMMMMMMMMZ????IIIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?II?II+8MMMMMMMMMMI++?ZOZ7?+++++++?ZMMMMMMMMMMZ$IIII7OZIIIIIIIII8MMMMMMMMMMMZ?????IMMMMMMMMMM$???OOD7IIMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIMMMMMMMMMMMMMMNNNN8O$I++++?NMNNMMMMMMMMMMMMMMD8I77NM8IIIIIIIIOMMMMMMMMMO??????+8MMMMMMMMMZ??$MM$?IIZMMMMMMMMM?IIIZNMMMMMMMMMMMZ?????8MMMMMMMMMMOIIIIIIIIIIII
?II?MMMMMMMMMMMMMMMMMM88??++++?MMMMMMMMMMMMMMMMMMD8II7IDMMOIIIIIIOMMMMMMMDOIIII??I??NMMMMMMMMMO8MZ$?IIIIZMMMMMMMMZIZ8MDMMMMMMMMMMMO?????8MMMMMMMMMMOIIIIIIIIIIII
?II?DDDDDDDDDDDDDDD8DDZ$++++++?D8D8DDDDDDDDDDDDDDOZIIIIII?7ODMMMMMMMNDZ7?IIIIIII??????ZDMMMMN8Z7??I?IIIIIIIZ8MMMMN8Z??7$ZZZZZZZZZZZ+????IZZZZZZZZZZ7IIIIIIIIIIII
?IIIII++++++++++++++++=+++++++++++IIIIIIIIIIIIIIIIII???I?????I77ZZ77IIIIIIIIIIIII????I???II??????????IIIIIIII?777IIIIIIII???????????????????????IIIIIIIIIIIIIIII
*/
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

#define MAPP_PLAYBACK_C

//system
#include "Board.h"                  //For pvr select
#include "sysinfo.h"                //For playback buffer

#include "debug.h"

#if ENABLE_PVR

//api
#include "IOUtil.h"                 //For Unicode String compare
#include "msAPI_Timer.h"            //For timer
#include "msAPI_DTVSystem.h"        //For audio info
#include "msAPI_PVR.h"              //For pvr
#include "msAPI_Player.h"           //For player
#ifdef S3PLUS
#include "drvCi_Api.h"                //For tuner
#endif

//ap
#ifdef PVR_8051
#include "mapp_demux.h"             //For demux
#else
#include "MApp_GlobalVar.h"         //For demux
#endif
#include "mapp_si.h"                //For SI
#include "MApp_Subtitle.h"          //For subtitle
#ifdef S3PLUS
//#include "MApp_MHEG5_Main.h"        //For MHEG5
#endif
#include "MApp_ChannelChange.h"     //For channel change
#include "MApp_Record.h"            //For record-linkage
#include "MApp_Playback.h"          //For itself
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_TV.h"
#include "MApp_CIPVR_Adaption.h"
#endif
#include "msAPI_audio.h"

#include "MApp_AVSync.h"
#if ENABLE_DVB_T2
#include "MApp_Scan.h"
#endif
#include "GPIO.h"                   //For audio

#include "msAPI_Demod.h"


#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#endif

//
/*************************************************************************************************/
#define JUMPDETECTTIMER         30000
#define JUMPSTEPCOUNTER         1000
#define BEGINJUMPTHRELD         100     // IN  1/10 second

#define DEBUG_PLAYBACK_STATE    0

/*************************************************************************************************/
typedef enum
{
    E_PLAYBACK_NEXTACT_NONE,
    E_PLAYBACK_NEXTACT_ENABLE,
    E_PLAYBACK_NEXTACT_RESUME,
    E_PLAYBACK_NEXTACT_FASTFORWARD,
    E_PLAYBACK_NEXTACT_FASTBACKWARD,
    E_PLAYBACK_NEXTACT_JUMPFORWARD,
    E_PLAYBACK_NEXTACT_JUMPBACKWARD,
    E_PLAYBACK_NEXTACT_JUMPTOTIME,
    E_PLAYBACK_NEXTACT_STEPIN,
    E_PLAYBACK_NEXTACT_SLOWFORWARD,
} enPlaybackActionAfterPause;

/*************************************************************************************************/
static _msAPI_PVR_RecordPath   * _pstPvrRecordPath;                   //one record   path for playback
static _msAPI_PVR_PlaybackPath * _pstPvrPlaybackPath;                 //one playback path for playback

static enPlaybackState    _enPlaybackState      = E_PLAYBACK_STATE_WAIT;    //playback_state
static enPlaybackState    _enPrePlaybackState      = E_PLAYBACK_STATE_WAIT;    //playback_state
static enPlaySpeed        _enPlaybackSpeed      = E_PLAY_SPEED_1X;          //playback_speed
static enPlaybackInput    _enPlaybackInput      = E_PLAYBACK_INPUT_NONE;    //playback_input from outside
static U32                _u32PlaybackExtPara   = 0;                        //playback_input from outside
static enPvrApiStatus     _enPlaybackStatus     = E_PVR_API_STATUS_OK;      //playback_status

static BOOL _bPlaybackStepIn = FALSE;        // the timer difference direction
static BOOL _bStepInTrigger = FALSE;        // the timer difference direction
static U32 u32TempTimeCounter = 0;
static U32 u32StartSysTime =0;
static BOOL _bDisplayOneField = FALSE;
static U8 _u8RecordedParentalRating = 0;
static U16 _pu16PlaybackFileName[RECORD_NAME_LENGTH]={0};
static U32  u32PrePlayTime = 0;
#ifdef MEASURE_FFFB_TIME //=======================$$$//
static U32                _u32FastForwardStartTime;
static U32                _u32FastBackwardStartTime;
#endif //MEASURE_FFFB_TIME =======================$$$//
#define TIME_CALIBRATION_MACRO      1
#define TIME_CALIBRATION_MICRO      2

/*************************************************************************************************/
//@@@Do not control demux/file system/audio/scaler/video directly in this layer

/*************************************************************************************************/
///-----------------------------------------------------------------------------------
///Adjust Timer By file position when FF / FB,
///@param none
///@return none
///-----------------------------------------------------------------------------------
/*************************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////////// playback path /////////////////////////////////////////*/
/*###############################################################################################*/

#define DEBUG_PLAYBACK(x)   //x
#define INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE_EXE TRUE

/***************************************************************************************/
static BOOLEAN MApp_Playback_JumpToTime(U32 u32TimeSec)
{
    U8 u8BumpEnd = FALSE;
  //  U16 u32JumpSec = 0;

    /*[01]error condition =============================================================*/
    if (_enPlaybackState != E_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }

    U32 u32RecordStartTime = MApp_Playback_GetRecordStartTimeSec();
   // U32 u32PlaybackTime = MApp_Playback_GetPlaybackTimeSec();
    U32 u32RecordEndTime = MApp_Playback_GetRecordEndTimeSec();
    U32 u32TotalTime        = MApp_Playback_GetTotalTimeSec();

    #ifdef PVR_UTOPIA
    MApi_DMX_BypassFileInTimeStamp(TRUE);
    msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath); //CL:81713
    MApi_DMX_BypassFileInTimeStamp(FALSE);
    #endif

    if(u32TimeSec <= u32TotalTime)
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,u32TimeSec*1000,E_JUMP_BUFFER_RESET);
        u8BumpEnd = FALSE;
    }
    else
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,(u32RecordEndTime - u32RecordStartTime)*1000,E_JUMP_BUFFER_RESET);
        _enPlaybackStatus = E_PVR_API_STATUS_FILE_BUMP_END;
        u8BumpEnd = TRUE;
    }



    /*[02-2]set audio/scaler/video ====================================================*/
    #ifndef S3PLUS
    //printf("audio stop; scaler freeze; video stop->reset; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();
#ifdef PVR_UTOPIA  //can't clear bitstream buffer, so, have to reset MVD
    msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
#else
    msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
#endif
    #else
    //printf("audio stop; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();

    msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif

    /*[03]change state ================================================================*/
#ifndef PVR_UTOPIA
    _enPlaybackState = E_PLAYBACK_STATE_STOP;
#endif

    if(u8BumpEnd == TRUE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_Open(U16 *pu16PlaybackFileName)
{
    U8 u8PlaybackOpen = FALSE;

    /*[01]error condition =============================================================*/
    if (_enPlaybackState != E_PLAYBACK_STATE_WAIT)
    {
        return FALSE;
    }
    //printf("MApp_Playback_Open \n");
    memset(_pu16PlaybackFileName,0,sizeof(_pu16PlaybackFileName));
    UnicodeCpy((S8 *)_pu16PlaybackFileName, (S8 *)pu16PlaybackFileName);

    /*[02-1]set pvr playback path =====================================================*/
    _pstPvrPlaybackPath = msAPI_PVR_PlaybackPathOpen(pu16PlaybackFileName);

    if(_pstPvrPlaybackPath)
    {
        if(MApp_Record_CheckPlaybackLinkage(RECORD_PATH_DEFAULT, pu16PlaybackFileName))
        {
            _pstPvrPlaybackPath->bLinkRecord = TRUE;    //<---(R-P-1)establish record linkage
        }

        u8PlaybackOpen = TRUE;
        _pstPvrRecordPath = _pstPvrPlaybackPath->pstPvrRecordPath;   //<---Linking to Record Path in Playback Mode

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        printf("............MApp_Playback_Enable2.....%d......\n",_pstPvrPlaybackPath->pstPvrRecordPath->u8CicamCheckLevel);
        switch(_pstPvrPlaybackPath->pstPvrRecordPath->u8CicamCheckLevel)
        {
            case EN_CI_VERSION_CI_PLUS:
            {
                MAPP_CIPVR_CIPVRFS_PlaybackFileRead();
                enPvrApiStatus enPvrStatus = MAPP_CIPVR_CIPlusPVRHandling(PVR_PATH_PLAYBACK,false,0xFFFF);
                if((E_PVR_API_STATUS_OK != enPvrStatus))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enPlaybackState = E_PLAYBACK_STATE_WAIT;
                    _enPlaybackSpeed = E_PLAY_SPEED_1X;
                    _enPlaybackStatus = enPvrStatus;
                    msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
                   return FALSE;
                }

                U8 u8aCICAMID[CC_AUTH_ID_SIZE] = { 0 };
                if(FALSE == msAPI_CI_CC_GetCICAMID(u8aCICAMID))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enPlaybackState = E_PLAYBACK_STATE_WAIT;
                    _enPlaybackSpeed = E_PLAY_SPEED_1X;
                    _enPlaybackStatus = E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                    msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
                    return FALSE;
                }
                else if(FALSE == MAPP_CIPVR_PlaybackCiSecuredPatternCheck(u8aCICAMID))
                {
                     printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enPlaybackState = E_PLAYBACK_STATE_WAIT;
                    _enPlaybackSpeed = E_PLAY_SPEED_1X;
                    _enPlaybackStatus = E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                    msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
                    return FALSE;
                }
                else
                {
                    U32 u32JumpTime = 0;
                    BOOL bRetentionLimitExpire = MAPP_CIPVR_RetentionLimitMonitor(0, &u32JumpTime);
                    //u8PlaybackEnable = TRUE;
                    if((TRUE == bRetentionLimitExpire) && (MApp_Playback_GetTotalTimeSec() <= u32JumpTime))
                    {
                        printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                        _enPlaybackState = E_PLAYBACK_STATE_WAIT;
                        _enPlaybackSpeed = E_PLAY_SPEED_1X;
                        _enPlaybackStatus = E_PVR_API_STATUS_ERROR_RETENTION_LIMIT_EXPIRED;
                        msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
                        return FALSE;
                    }
                }
            }
            break;
            default:
                break;
        }
#endif
    }
    else
    {
        MS_DEBUG_MSG(printf("Playback open fail\n"));
        _enPlaybackStatus = E_PVR_API_STATUS_FILE_READ_ERROR;
        u8PlaybackOpen = FALSE;
        memset(_pu16PlaybackFileName,0,sizeof(_pu16PlaybackFileName));
    }

    /*[02-2]set audio/scaler/video ====================================================*/

    /*[03]change state ================================================================*/
    if(u8PlaybackOpen)
    {
        _enPlaybackState = E_PLAYBACK_STATE_OPEN;
        return TRUE;
    }
    else
    {
        _enPlaybackState = E_PLAYBACK_STATE_WAIT;
        return FALSE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_Enable(void)
{
    #ifndef S3PLUS
    #ifndef PVR_UTOPIA
    msAPI_DMX_Switch2Pinpon(FALSE);
    #endif
    #endif

//    U8 u8PlaybackEnable = FALSE;

    /*[01]error condition =============================================================*/
    if (_enPlaybackState != E_PLAYBACK_STATE_OPEN)
    {
        return FALSE;
    }
    //printf("MApp_Playback_Enable \n");

    /*[02-1]set pvr playback path =====================================================*/
    _pstPvrPlaybackPath->u32BufferStart  = PvrGetReadSdramAdr();                //<--from system

#ifdef PVR_UTOPIA
    #if (PVR_READ_SDRAM_LEN >= (PVR_FILE_IN_SIZE*3))
        //printf("CmdQ num=3\n");
        _pstPvrPlaybackPath->u32BufferLength = PVR_FILE_IN_SIZE*3;                //<--from system
    #elif (PVR_READ_SDRAM_LEN >= (PVR_FILE_IN_SIZE*2))
        //printf("CmdQ num=2\n");
        _pstPvrPlaybackPath->u32BufferLength = PVR_FILE_IN_SIZE*2;                //<--from system
    #else
        {
            printf("\n\nFatal error:Read Buff overflow\n\n");
            return FALSE;
        }
    #endif
#else
    _pstPvrPlaybackPath->u32BufferLength = PVR_READ_SDRAM_LEN;
#endif
    #if BRAZIL_PVR_CC
    MApp_PVR_Playback_SetCCPID(MSAPI_DMX_INVALID_PID);
    #endif

    if ((_enPlaybackStatus=msAPI_PVR_PlaybackPathSet(_pstPvrPlaybackPath)) == E_PVR_API_STATUS_OK)
    {
        //############################ ************************* ############################
        _pstPvrRecordPath = _pstPvrPlaybackPath->pstPvrRecordPath;   //<---Linking to Record Path in Playback Mode
        _pstPvrRecordPath->u32RecordedTime = msAPI_Timer_GetTime0();
        //############################ ************************* ############################

        {
        #ifdef PVR_8051
            //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            msAPI_DMX_Stop(u8PcrFid);               //PCR_FID
            msAPI_DMX_Close(u8PcrFid);
            u8PcrFid = MSAPI_DMX_INVALID_FLT_ID;
            msAPI_DMX_Stop(u8VidFid);               //VID_FID
            msAPI_DMX_Close(u8VidFid);
            u8VidFid = MSAPI_DMX_INVALID_FLT_ID;
            msAPI_DMX_Stop(u8AudFid);               //AUD_FID
            msAPI_DMX_Close(u8AudFid);
            u8AudFid = MSAPI_DMX_INVALID_FLT_ID;
            #ifndef S3PLUS
            msAPI_DMX_Stop(u8AdAFid);               //ADA_FID
            msAPI_DMX_Close(u8AdAFid);
            u8AdAFid = MSAPI_DMX_INVALID_FLT_ID;
            #endif
            //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            msAPI_DMX_Stop(g_u8PesFID);             //SUBTITLE_FID
            msAPI_DMX_Close(g_u8PesFID);
            g_u8PesFID = MSAPI_DMX_INVALID_FLT_ID;
        #else
            //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_PCR_FID));               //PCR_FID
            msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_PCR_FID));
            MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_PCR_FID);
            msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_VIDEO_FID) );               //VID_FID
            msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_VIDEO_FID) );
            MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_VIDEO_FID);
            msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AUDIO_FID));               //AUD_FID
            msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_AUDIO_FID));
            MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_AUDIO_FID);
            msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AD_FID));               //ADA_FID
            msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_AD_FID));
            MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_AD_FID);
            //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_PES_FID));             //SUBTITLE_FID
            msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_PES_FID));
            MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_PES_FID);
        #endif
            //(TYPE3)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            //(TYPE4)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            //(TYPE5)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            //((( )))~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        }
        {
            U8 u8FID;

            for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
            {
                if (_pstPvrRecordPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
                {
                    //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    if(_pstPvrRecordPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_PCR)             //PCR_FID
                    {
                    #ifndef S3PLUS
                        msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_PCR);
                    #else
                        {
                            U8 u8FID;
                            gAvSync_PcrFid = MSAPI_DMX_INVALID_FLT_ID;
                            msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, 0x1ffe, MSAPI_DMX_FILTER_TYPE_PCR);
                            for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
                            {
                                if (_pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_PCR)
                                {
                                    gAvSync_PcrFid = _pstPvrPlaybackPath->u8FilterID[u8FID];
                                    //printf("gAvSync_PcrFid=%bd\n",gAvSync_PcrFid);
                                    break;
                                }
                            }
                            if(gAvSync_PcrFid == MSAPI_DMX_INVALID_FLT_ID)
                            {
                                //printf("Invalid gAvSync_PcrFid\n");
                            }
                        }
                    #endif
                    }
                    else if(_pstPvrRecordPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_VIDEO)      //VID_FID
                    {
                        msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_VIDEO);
                    }
                    else if(_pstPvrRecordPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO)      //AUD_FID
                    {
                        //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_AUDIO);
                    }
                    #ifndef S3PLUS
                    else if(_pstPvrRecordPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO2)     //ADA_FID
                    {
                        //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_AUDIO2);
                    }
                    #endif
                    //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    else if (_pstPvrRecordPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_SUBTITLE)  //SUBTITLE_FID
                    {
                        #if BRAZIL_PVR_CC
                        MApp_PVR_Playback_SetCCPID(_pstPvrRecordPath->u16PID[u8FID]);
                        #endif
                        //msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_MIU, MSAPI_DMX_DATAPATH_IN_MIU, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
                        //MApp_Dmx_PES_Monitor(_pstPvrRecordPath->u16PID[u8FID]);
                        //msAPI_DMX_RestoreDataPath();
                    }
                    //(TYPE3)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    //(TYPE4)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    //(TYPE5)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    //((( )))~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                }
            }
        }

        //link record-playback at start up ============================================//
        _pstPvrPlaybackPath->u32FileValidPosStrKB   = _pstPvrRecordPath->u32FileValidPosStrKB;

        _pstPvrPlaybackPath->enVideoType            = _pstPvrRecordPath->enVideoType;
        _pstPvrPlaybackPath->enAudioType            = _pstPvrRecordPath->enAudioType;
        _pstPvrPlaybackPath->enAdAudioType          = _pstPvrRecordPath->enAdAudioType;

        _u8RecordedParentalRating = _pstPvrRecordPath->u8Parental_Control;
        //link record-playback at start up ============================================//

        U8 u8i;
        for (u8i=0; u8i < MApp_Playback_AudioGetLanguageTotal(); u8i++)
        {
            _pstPvrPlaybackPath->PVRAudioInfo[u8i].wAudPID = _pstPvrRecordPath->PVRAudioInfo[u8i].wAudPID;
        }

        #ifdef S3PLUS
        MApp_Dmx_DisableTableMonitor();     //<--no table monitor because demux switch to playback
        #endif

        msAPI_PVR_PlaybackPathStart(_pstPvrPlaybackPath);

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        U16 u16RecordFileName[FILE_NAME_LENGTH];
        U16 u16PlaybackFileName[FILE_NAME_LENGTH];
        MApp_PVR_GetPlaybackFileName(u16PlaybackFileName);
        MApp_PVR_GetRecordFileName(u16RecordFileName);
        if(u16RecordFileName ==  u16PlaybackFileName)
        {
            MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,EN_CC_PVR_OPERATING_MODE_TIMESHIFT,NULL,0);
        }
        else
        {
            MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING,NULL,0);
        }
        MAPP_CIPVR_PVRReTriggerURICopyProtect();
#endif
    }
    else
    {
        //u8PlaybackEnable = FALSE;
        _enPlaybackState = E_PLAYBACK_STATE_WAIT;
        _enPlaybackSpeed = E_PLAY_SPEED_1X;
        return FALSE;

    }

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio stop->init; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();
/*
    #if (defined(S3PLUS) || defined(S4LITE))
    msAPI_Player_AudioInit(_pstPvrPlaybackPath->enAudioType,  E_PLAY_SOURCE_FILE, FALSE, E_PLAY_AUDIO_TYPE_INVALID);
    #else
    msAPI_Player_AudioInit(_pstPvrPlaybackPath->enAudioType,  E_PLAY_SOURCE_FILE, stGenSetting.g_SoundSetting.bEnableAD, _pstPvrPlaybackPath->enAdAudioType);
    #endif
*/
  #if( ENABLE_DVB_AUDIO_DESC )
    msAPI_Player_AudioInit(_pstPvrPlaybackPath->enAudioType,  E_PLAY_SOURCE_FILE, stGenSetting.g_SoundSetting.bEnableAD, _pstPvrPlaybackPath->enAdAudioType);
  #else
    msAPI_Player_AudioInit(_pstPvrPlaybackPath->enAudioType,  E_PLAY_SOURCE_FILE, FALSE, E_PLAY_AUDIO_TYPE_INVALID);
  #endif


    msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);

    /*[03]change state ================================================================*/
    //if(u8PlaybackEnable)
    {
        _enPlaybackState = E_PLAYBACK_STATE_OPEN;   //no change
        _enPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
    //else
    //{
        //_enPlaybackState = E_PLAYBACK_STATE_WAIT;
        //_enPlaybackSpeed = E_PLAY_SPEED_1X;
        //return FALSE;
    //}
}
/***************************************************************************************/
#if ENABLE_FileIn_PMTMonitor

static BOOLEAN  MApp_PlaybackPMTMonitor(void)
{
    U8 u8FID,u8i;

    FileIn_SERVICE_INFO FileIn_Service_Info;
    MApp_SI_GetFileInPIDS(&FileIn_Service_Info);

    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
            if(_pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_PCR)             //PCR_FID
            {
                if(_pstPvrPlaybackPath->u16PID[u8FID] != FileIn_Service_Info.wPCR_PID)
                {
                    if(FileIn_Service_Info.wPCR_PID != 0)
                    {
                        msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrPlaybackPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_PCR);
                    }
                    _pstPvrPlaybackPath->u16PID[u8FID] = FileIn_Service_Info.wPCR_PID;
                    msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, FileIn_Service_Info.wPCR_PID, MSAPI_DMX_FILTER_TYPE_PCR);
                    break;
                }
            }
            else if(_pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_VIDEO)      //VID_FID
            {
                if((_pstPvrPlaybackPath->u16PID[u8FID] != FileIn_Service_Info.wVideo_PID)||((_pstPvrPlaybackPath->u16PID[u8FID]==SI_INVALID_PID)&&( FileIn_Service_Info.wVideo_PID!= SI_INVALID_PID)))
                {
                    if(FileIn_Service_Info.wVideo_PID != 0)
                    {
                        msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrPlaybackPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_VIDEO);
                    }
                     _pstPvrPlaybackPath->u16PID[u8FID] = FileIn_Service_Info.wVideo_PID;
                     msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, FileIn_Service_Info.wVideo_PID, MSAPI_DMX_FILTER_TYPE_VIDEO);
                     break;
                }
            }
            else if(_pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO)     //AUD_FID
            {
                for(u8i = 0 ; u8i < MApp_Playback_AudioGetLanguageTotal(); u8i++)
                {
                    if((_pstPvrPlaybackPath->PVRAudioInfo[u8i].wAudPID!= FileIn_Service_Info.stAudInfo[u8i].wAudPID)||((_pstPvrPlaybackPath->u16PID[u8FID]==SI_INVALID_PID)&&( FileIn_Service_Info.stAudInfo[u8i].wAudPID!= 0)))
                    {
                        if(FileIn_Service_Info.stAudInfo[u8i].wAudPID != 0)
                        {
                            msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrPlaybackPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_AUDIO);
                        }
                        _pstPvrPlaybackPath->PVRAudioInfo[u8i].wAudPID = FileIn_Service_Info.stAudInfo[u8i].wAudPID;
                        _pstPvrPlaybackPath->u16PID[u8FID] = FileIn_Service_Info.stAudInfo[u8i].wAudPID;
                        msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, FileIn_Service_Info.stAudInfo[u8i].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
                        break;

                    }
                }
            }
            else if(_pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO2)     //ADA_FID
            {
                /*if((_pstPvrPlaybackPath->u16PID[u8FID] != FileIn_Service_Info.wAudio_PID)||((_pstPvrPlaybackPath->u16PID[u8FID]==SI_INVALID_PID)&&( FileIn_Service_Info.wAudio_PID!= SI_INVALID_PID)))
                {
                    if(FileIn_Service_Info.wAudio_PID != 0)
                    {
                        msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrPlaybackPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_AUDIO2);
                    }
                    _pstPvrPlaybackPath->u16PID[u8FID] = FileIn_Service_Info.wAudio_PID;
                     msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, FileIn_Service_Info.wAudio_PID, MSAPI_DMX_FILTER_TYPE_AUDIO2);
                     break;
                }*/
            }
            //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            else if (_pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_SUBTITLE)  //SUBTITLE_FID
            {
                #if BRAZIL_PVR_CC
                U16 u16CCPid = MApp_SI_Get_CC_PID();
                if((_pstPvrPlaybackPath->u16PID[u8FID] != u16CCPid)||((_pstPvrPlaybackPath->u16PID[u8FID]==SI_INVALID_PID)&&( FileIn_Service_Info.wSubtitle_PID!= SI_INVALID_PID)))
                {
                    if(FileIn_Service_Info.wSubtitle_PID != 0)
                    msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrPlaybackPath->u16PID[u8FID], MSAPI_DMX_FILTER_TYPE_SUBTITLE);
                    _pstPvrPlaybackPath->u16PID[u8FID] = u16CCPid;
                     msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, u16CCPid, MSAPI_DMX_FILTER_TYPE_SUBTITLE);
                     break;
                }
                #endif
            }

            //(TYPE3)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            //(TYPE4)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            //(TYPE5)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            //((( )))~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }
    return TRUE;
}
#endif
/***************************************************************************************/
static BOOLEAN  MApp_Playback_Routine(void)
{

#if ENABLE_FileIn_PMTMonitor
    MApp_PlaybackPMTMonitor();
#endif
    /*[01]error condition =============================================================*/
    if(_bPlaybackStepIn)
    {
        if(!_bStepInTrigger)
        {
            _enPlaybackState = E_PLAYBACK_STATE_PAUSE;
        }
        else
        {
            if(MApi_VDEC_IsStepDispDone())
            {
                MApi_VDEC_StepDisp();
                _bStepInTrigger =FALSE;
                _enPlaybackState = E_PLAYBACK_STATE_PAUSE;
            }
            else
            {
                _enPlaybackState = E_PLAYBACK_STATE_PLAYBACKING;
            }
        }
    }

    if ((_enPlaybackState != E_PLAYBACK_STATE_PLAYBACKING ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD))
    {
        return TRUE;
    }
    //printf("MApp_Playback_Routine \n");

    /*[02-1]set pvr playback path =====================================================*/
    /*[02-1a]link record-playback =====================================================*/
    _pstPvrPlaybackPath->u32FileLimitedSizeKB   = _pstPvrRecordPath->u32FileLimitedSizeKB;
    _pstPvrPlaybackPath->u32FileValidPosStrKB   = _pstPvrRecordPath->u32FileValidPosStrKB;
    _pstPvrPlaybackPath->u32FileValidPosEndKB   = _pstPvrRecordPath->u32FileValidPosEndKB;
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    U32 u32JumpTargetTime = 0;
    if(0)//(MAPP_CIPVR_RetentionLimitMonitor(MApp_Playback_GetPlaybackTimeSec(), &u32JumpTargetTime))
    {
        MApp_Playback_JumpToTime(u32JumpTargetTime);
    }
#endif
    /*[02-1b]playback path output routine =============================================*/
    /*[##-1]Fast Backward =============================================================*/
    if(_enPlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)
    {
       // U32 playTime = MApp_Playback_GetPlaybackTimeSec();
        U16 u16JumpSec = 0;

        switch(_enPlaybackSpeed)
        {
            case E_PLAY_SPEED_1X:
                break;
            case E_PLAY_SPEED_2X:
                u16JumpSec = 2;
                break;
            case E_PLAY_SPEED_4X:
                u16JumpSec = 4;
                break;
            case E_PLAY_SPEED_8X:
                u16JumpSec = 7;
                break;
            case E_PLAY_SPEED_16X:
                u16JumpSec = 10;
                break;
            case E_PLAY_SPEED_32X:
                u16JumpSec = 16;
                break;
        }

        if(MApi_VDEC_IsStepDispDone())
        {
            MApi_DMX_BypassFileInTimeStamp(TRUE);
            msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
            MApi_DMX_BypassFileInTimeStamp(FALSE);
            MApi_VDEC_StepDisp();
        }

        if(u32TempTimeCounter/90 > msAPI_Timer_DiffTimeFromNow(u32StartSysTime) * u16JumpSec)
        {
          if((_enPlaybackStatus = msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,(u32TempTimeCounter/90 - msAPI_Timer_DiffTimeFromNow(u32StartSysTime) * u16JumpSec), E_JUMP_BUFFER_CONTINUOUS)) == E_PVR_API_STATUS_OK)
          {
            if((_enPlaybackStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
            {
              return FALSE;
            }
          }
        }
      else
      {
        if((_enPlaybackStatus = msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,0, E_JUMP_BUFFER_CONTINUOUS)) == E_PVR_API_STATUS_OK)
        {
          if((_enPlaybackStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
          {
            return FALSE;
          }
        }
      }

    }

    /*[##-2]Fast Forward ==============================================================*/
    else if(_enPlaybackState == E_PLAYBACK_STATE_FASTFORWARD)
    {
        U32 playTime = MApp_Playback_GetPlaybackTimeSec();
        //U32 starTime = MApp_Playback_GetRecordStartTimeSec();
        //U32 endTime = MApp_Playback_GetRecordEndTimeSec();
        U32 TotalTime        = MApp_Playback_GetTotalTimeSec();
        if(_enPlaybackSpeed != E_PLAY_SPEED_2X)
        {
            if(MApi_VDEC_IsStepDispDone())
            {
                MApi_DMX_BypassFileInTimeStamp(TRUE);
                msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                MApi_DMX_BypassFileInTimeStamp(FALSE);
                MApi_VDEC_StepDisp();
            }
        }
        if( _enPlaybackSpeed > E_PLAY_SPEED_2X)
        {
            U16 u16JumpSec = 0;

            switch(_enPlaybackSpeed)
            {
            /*    case E_PLAY_SPEED_1X:
                    #ifndef S3PLUS
                    u16JumpSec = 0;
                    #else
                    u16JumpSec = 0; //s3p performance is not good enough
                    #endif
                    break;
                case E_PLAY_SPEED_2X:
                    #ifndef S3PLUS
                    u16JumpSec = 0;
                    #else
                    u16JumpSec = 1; //s3p performance is not good enough
                    #endif
                    break;
            */
                case E_PLAY_SPEED_4X:
                    #ifndef S3PLUS
                    u16JumpSec = 3;
                    #else
                    u16JumpSec = 3; //s3p performance is not good enough
                    #endif
                    break;

                case E_PLAY_SPEED_8X:
                    #ifndef S3PLUS
                    u16JumpSec = 6; // ~ 10x
                    #else
                    u16JumpSec = 5; //s3p performance is not good enough
                    #endif
                    break;
                case E_PLAY_SPEED_16X:
                    #ifndef S3PLUS
                    u16JumpSec = 10; // ~ 20x
                    #else
                    u16JumpSec =10; //s3p performance is not good enough
                    #endif
                    break;
                case E_PLAY_SPEED_32X:
                    #ifndef S3PLUS
                    u16JumpSec = 16; // ~ 30x
                    #else
                    u16JumpSec =20; //s3p performance is not good enough
                    #endif
                    break;
                default:
                    u16JumpSec = 0;
                    break;
            }
                    if(playTime<TotalTime)
            {
                msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,(u32TempTimeCounter/90 + msAPI_Timer_DiffTimeFromNow(u32StartSysTime) * u16JumpSec), E_JUMP_BUFFER_CONTINUOUS);
      }
     }
        else
        {
            MApi_DMX_Pvr_SetPlaybackStamp((u32TempTimeCounter/90 + msAPI_Timer_DiffTimeFromNow(u32StartSysTime) * _enPlaybackSpeed )*90);
        }

        if((_enPlaybackStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
        {
            return FALSE;
        }
    }
    else if(_enPlaybackState == E_PLAYBACK_STATE_SLOWFORWARD)
    {
        MApi_DMX_Pvr_SetPlaybackStamp((u32TempTimeCounter/90 + msAPI_Timer_DiffTimeFromNow(u32StartSysTime) / _enPlaybackSpeed )*90);
        if((_enPlaybackStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
        {
            return FALSE;
        }
    }
    /*[##-3]Normal Play ===============================================================*/
    else
    {
        #ifdef S3PLUS
        MApp_AVSync_SetSTC();
        #else
        #ifdef PVR_UTOPIA
        MApp_AVSync_ForceSync();
        #endif
        #endif

        msAPI_Player_VideoMonitor(FALSE); // Get GOP size info.
        if ((_enPlaybackStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
        {
            return FALSE;
        }
    }

    /*[03]change state ================================================================*/
    if((_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
       (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
       (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) )
    {
        _enPlaybackState = E_PLAYBACK_STATE_PLAYBACKING;
    }

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_StepIn(void)
{
    #if 1
    if(!_bPlaybackStepIn)
    {
        _bPlaybackStepIn = TRUE;
        msAPI_Player_ScalerWaitFree(10);
        _enPlaybackSpeed = E_PLAY_SPEED_1X;
        msAPI_Player_VideoConfigForwardSpeed(_enPlaybackSpeed);
        msAPI_Player_VideoPause();
        MApi_VDEC_StepDisp();
        msAPI_PVR_PlaybackPathStepIn(_pstPvrPlaybackPath);
        _bStepInTrigger =FALSE;
    }
    else
    {
        _bStepInTrigger =TRUE;
    }
    #endif
    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_JumpForward(U32 u32JumpSec)
{
    U8 u8BumpEnd;
    U16 u16TimeDiffSec;

    /*[01]error condition =============================================================*/
    if (_enPlaybackState != E_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
    //printf("MApp_Playback_JumpForward \n");

    /*[02-1]set pvr playback path =====================================================*/
    /*[02-1a]jump forward =============================================================*/
    u16TimeDiffSec = MApp_Playback_GetTotalTimeSec() - MApp_Playback_GetPlaybackTimeSec();
    if(u16TimeDiffSec >= u32JumpSec)
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, (MApp_Playback_GetPlaybackTimeSec()+u32JumpSec)*1000,E_JUMP_BUFFER_RESET);
        u8BumpEnd = FALSE;
    }
    else
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, MApp_Playback_GetTotalTimeSec()*1000,  E_JUMP_BUFFER_RESET);
        _enPlaybackStatus = E_PVR_API_STATUS_FILE_BUMP_END;
        u8BumpEnd = TRUE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    #ifndef S3PLUS
    //printf("audio stop; scaler freeze; video stop->reset; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();
#ifdef PVR_UTOPIA  //can't clear bitstream buffer, so, have to reset MVD
    msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
#else
    msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
#endif
    #else
    //printf("audio stop; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();

    msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif

    /*[03]change state ================================================================*/
#ifndef PVR_UTOPIA
    _enPlaybackState = E_PLAYBACK_STATE_STOP;
#endif

    if(u8BumpEnd == TRUE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_JumpBackward(U32 u32JumpSec)
{
    U16 u16TimeDiffSec;

    /*[01]error condition =============================================================*/
    if (_enPlaybackState != E_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
    //printf("MApp_Playback_JumpBackward \n");

    /*[02-1]set pvr playback path =====================================================*/
    /*[02-1a]jump backward ============================================================*/
    u16TimeDiffSec = MApp_Playback_GetPlaybackTimeSec();
    if(u16TimeDiffSec >= u32JumpSec)
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, (MApp_Playback_GetPlaybackTimeSec()-u32JumpSec)*1000,E_JUMP_BUFFER_RESET);
    }
    else
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, 0, E_JUMP_BUFFER_RESET);
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    #ifndef S3PLUS
    //printf("audio stop; scaler freeze; video stop->reset; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();
#ifdef PVR_UTOPIA
    msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
#else
    msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
#endif
    #else
    //printf("audio stop; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();

    msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif

    /*[03]change state ================================================================*/
#ifndef PVR_UTOPIA
    _enPlaybackState = E_PLAYBACK_STATE_STOP;
#endif

    return TRUE;
}

/***************************************************************************************/
static enPlaybackState enPrevPlayDirection = E_PLAYBACK_STATE_FASTFORWARD;
/***************************************************************************************/
static BOOLEAN MApp_Playback_SlowForward(void)
{
    DEBUG_PLAYBACK( printf("MApp_Playback_SlowForward()\n"); );

    /*[01]error condition =============================================================*/
    if (_enPlaybackState != E_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }


    /*[02-1]set pvr playback path =====================================================*/
    msAPI_PVR_PlaybackPathSlowForward(_pstPvrPlaybackPath);

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio nop; scaler waitfree; video ffspeed; \n");
    if((enPrevPlayDirection == E_PLAYBACK_STATE_FASTFORWARD)||
        (enPrevPlayDirection == E_PLAYBACK_STATE_FASTBACKWARD))
    {
      //printf("reverse backward->forward\n");
        enPrevPlayDirection = E_PLAYBACK_STATE_SLOWFORWARD;
        _enPlaybackSpeed    = E_PLAY_SPEED_1X;
    }

    if(_enPlaybackSpeed < E_PLAY_SPEED_32X)
    {
        U8 u8PlaybackSpeed = (U8)_enPlaybackSpeed;
        _enPlaybackSpeed = (enPlaySpeed)(u8PlaybackSpeed << 1);
    }
    else
    {
        _enPlaybackSpeed = E_PLAY_SPEED_2X;
    }

#ifdef S3PLUS
    _pstPvrPlaybackPath->enPlaySpeed = _enPlaybackSpeed;
#endif

#ifdef S3PLUS  // I am not sure if need enable in other platform
    msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);  //for clean afifo
    //MUTE_On();  don't  use this mute ....it's H/W mute ....
#endif
    msAPI_Player_VideoConfigSlowForwardSpeed(_enPlaybackSpeed);
    msAPI_Player_ScalerWaitFree(10);

    /*[03]change state ================================================================*/
    _enPlaybackState = E_PLAYBACK_STATE_SLOWFORWARD;

    return TRUE;
}
/***************************************************************************************/
static BOOLEAN MApp_Playback_FastForward(void)
{
    DEBUG_PLAYBACK( printf("MApp_Playback_FastForward()\n"); );

    /*[01]error condition =============================================================*/
    #if INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE_EXE
    enPlaySpeed prePlaySpeed = _enPlaybackSpeed;
    #else
    if (_enPlaybackState != E_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
    #endif
    //printf("MApp_Playback_FastForward \n");

    /*[02-1]set pvr playback path =====================================================*/
    msAPI_PVR_PlaybackPathFastForward(_pstPvrPlaybackPath);

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio nop; scaler waitfree; video ffspeed; \n");
    if((enPrevPlayDirection == E_PLAYBACK_STATE_FASTBACKWARD)||
        (enPrevPlayDirection == E_PLAYBACK_STATE_SLOWFORWARD))
    {
      //printf("reverse backward->forward\n");
        enPrevPlayDirection = E_PLAYBACK_STATE_FASTFORWARD;
        _enPlaybackSpeed    = E_PLAY_SPEED_1X;
    }

    if(_enPlaybackSpeed < E_PLAY_SPEED_16X)
    {
        U8 u8PlaybackSpeed = (U8)_enPlaybackSpeed;
        _enPlaybackSpeed = (enPlaySpeed)(u8PlaybackSpeed << 1);
    }
    else
    {
        _enPlaybackSpeed = E_PLAY_SPEED_2X;
    }

    DEBUG_PLAYBACK( printf("_enPlaybackSpeed=%u\n", _enPlaybackSpeed); );

    /***************************/
    if(_enPlaybackSpeed == E_PLAY_SPEED_2X)
    {
        /* Need Do (AVFifoClean + VDEC_Flush) : FB/FF->FFx2 */
        msAPI_PVR_PlaybackPathWaitAVFifoClean();
        MApi_DMX_BypassFileInTimeStamp(TRUE);
        msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
        MApi_DMX_BypassFileInTimeStamp(FALSE);

        MApi_VDEC_Play();
    }
    else
    #if INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE_EXE
    if( ((E_PLAYBACK_STATE_FASTFORWARD == _enPlaybackState) && (E_PLAY_SPEED_2X == prePlaySpeed)) ||
        ((E_PLAYBACK_STATE_FASTFORWARD != _enPlaybackState) && (E_PLAYBACK_STATE_FASTBACKWARD != _enPlaybackState)))
    #endif
    {
        MApi_VDEC_StepDisp();
    }
    /***************************/


#ifdef S3PLUS
    _pstPvrPlaybackPath->enPlaySpeed = _enPlaybackSpeed;
#endif

#ifdef S3PLUS  // I am not sure if need enable in other platform
    msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);  //for clean afifo
    //MUTE_On();  don't  use this mute ....it's H/W mute ....
#endif
    msAPI_Player_VideoConfigForwardSpeed(_enPlaybackSpeed);
    msAPI_Player_ScalerWaitFree(10);

    /*[03]change state ================================================================*/
    _enPlaybackState = E_PLAYBACK_STATE_FASTFORWARD;

    #ifdef MEASURE_FFFB_TIME //=======================$$$//
    _u32FastForwardStartTime = msAPI_Timer_GetTime0();
    #endif //MEASURE_FFFB_TIME =======================$$$//

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_FastBackward(void)
{
    DEBUG_PLAYBACK( printf("MApp_Playback_FastBackward()\n"); );

    /*[01]error condition =============================================================*/
    #if (!INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE_EXE)
    if (_enPlaybackState != E_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
    #endif
    //printf("MApp_Playback_FastBackward \n");


    /***************************/
    #if INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE_EXE
    if( ((E_PLAYBACK_STATE_FASTFORWARD == _enPlaybackState) && (E_PLAY_SPEED_2X == _enPlaybackSpeed)) ||
        ((E_PLAYBACK_STATE_FASTFORWARD != _enPlaybackState) && (E_PLAYBACK_STATE_FASTBACKWARD != _enPlaybackState)))
    #endif
    {
        MApi_VDEC_StepDisp();
    }
    /***************************/


    /*[02-1]set pvr playback path =====================================================*/
    msAPI_PVR_PlaybackPathFastBackward(_pstPvrPlaybackPath);

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio nop; scaler waitfree; video fbspeed; \n");
    if((enPrevPlayDirection == E_PLAYBACK_STATE_FASTFORWARD)||
        (enPrevPlayDirection == E_PLAYBACK_STATE_SLOWFORWARD))
    {
      //printf("reverse forward->backward\n");
        enPrevPlayDirection = E_PLAYBACK_STATE_FASTBACKWARD;
        _enPlaybackSpeed    = E_PLAY_SPEED_1X;
    }

    if(_enPlaybackSpeed < E_PLAY_SPEED_16X)
    {
        U8 u8PlaybackSpeed = (U8)_enPlaybackSpeed;
        _enPlaybackSpeed = (enPlaySpeed)(u8PlaybackSpeed << 1);
    }
    else
    {
        _enPlaybackSpeed = E_PLAY_SPEED_2X;
    }
    msAPI_Player_VideoConfigBackwardSpeed(_enPlaybackSpeed);
    msAPI_Player_ScalerWaitFree(10);

    #ifdef S3PLUS
    msAPI_Aeon_ReInitial( BIN_ID_CODE_AEON_TSSEARCH );
    msAPI_DMX_EnableReserveFlt(FALSE);
    msAPI_Player_AeonPatternSearchInit();
    #endif

    /*[03]change state ================================================================*/
    _enPlaybackState = E_PLAYBACK_STATE_FASTBACKWARD;

    #ifdef MEASURE_FFFB_TIME //=======================$$$//
    _u32FastBackwardStartTime = msAPI_Timer_GetTime0();
    #endif //MEASURE_FFFB_TIME =======================$$$//

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_Pause(enPlaybackActionAfterPause eNextAct)
{
    DEBUG_PLAYBACK( printf("MApp_Playback_Pause()\n"); );

    U8 u8PlaybackEnable = FALSE;

    /*[01]error condition =============================================================*/
    if ((_enPlaybackState != E_PLAYBACK_STATE_OPEN        ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_PLAYBACKING ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) )
    {
        return FALSE;
    }
    //printf("MApp_Playback_Pause \n");

    /*[02-1]set pvr playback path =====================================================*/
    if(_enPlaybackState == E_PLAYBACK_STATE_OPEN)   //live in
    {
        u8PlaybackEnable = FALSE;
    }
    else if (_enPlaybackState == E_PLAYBACK_STATE_FASTFORWARD)
    {
        //Need to freeze scaler here, because msAPI_PVR_PlaybackPathPause may modify DMX settings
        msAPI_Player_ScalerFreeze();

        msAPI_PVR_PlaybackPathPause(_pstPvrPlaybackPath);

        u8PlaybackEnable = TRUE;

        #ifdef MEASURE_FFFB_TIME //=======================$$$//
        printf("Fast Forward used time %04lu S\n",msAPI_Timer_DiffTimeFromNow(_u32FastForwardStartTime)/1000);
        #endif //MEASURE_FFFB_TIME =======================$$$//
    }
    else if (_enPlaybackState == E_PLAYBACK_STATE_FASTBACKWARD)
    {
        //Need to freeze scaler here, because msAPI_PVR_PlaybackPathPause may modify DMX settings
        msAPI_Player_ScalerFreeze();

        msAPI_PVR_PlaybackPathPause(_pstPvrPlaybackPath);

        u8PlaybackEnable = TRUE;

        #ifdef MEASURE_FFFB_TIME //=======================$$$//
        printf("Fast Backward used time %04lu S\n",msAPI_Timer_DiffTimeFromNow(_u32FastBackwardStartTime)/1000);
        #endif //MEASURE_FFFB_TIME =======================$$$//
    }
    else // E_PLAYBACK_STATE_PLAYBACKING            //file in
    {
        msAPI_PVR_PlaybackPathPause(_pstPvrPlaybackPath);

        u8PlaybackEnable = TRUE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    if(((_enPlaybackState == E_PLAYBACK_STATE_FASTFORWARD)||
        (_enPlaybackState == E_PLAYBACK_STATE_SLOWFORWARD))&&
       ((eNextAct == E_PLAYBACK_NEXTACT_RESUME) ||
        (eNextAct == E_PLAYBACK_NEXTACT_NONE  )   )         )
    {
      //printf("audio nop; scaler freeze->mute; video stop->reset->init; \n");
        //msAPI_Player_ScalerFreeze();
    #ifndef PVR_UTOPIA  //ther video cant' return after Mute, we need scaler to check this issue to improve the video quality
        msAPI_Player_ScalerMute(50);
    #endif

    #ifndef PVR_UTOPIA_T3
        msAPI_Player_VideoStop();
    #endif

    #ifndef PVR_UTOPIA  //diffenent funciton in utopia
        msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
    #endif

    #ifndef PVR_UTOPIA_T3
        msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif
    }
    else if((_enPlaybackState == E_PLAYBACK_STATE_FASTBACKWARD) &&
            ((eNextAct == E_PLAYBACK_NEXTACT_RESUME) ||
             (eNextAct == E_PLAYBACK_NEXTACT_NONE  )   )          )
    {
        //printf("audio nop; scaler freeze->mute; video stop->reset->init; \n");
        //msAPI_Player_ScalerFreeze();
    #ifndef PVR_UTOPIA  //ther video cant' return after Mute, we need scaler to check this issue to improve the video quality
        msAPI_Player_ScalerMute(50);
    #endif

    #ifndef PVR_UTOPIA_T3
        msAPI_Player_VideoStop();
    #endif

    #ifndef PVR_UTOPIA  //diffenent funciton in utopia
        msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
    #endif

    #ifndef PVR_UTOPIA_T3
        msAPI_Player_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif
        #ifdef S3PLUS
        msAPI_Aeon_Disable();                           //<--bandwidth problem, S3P only
        #endif
    }
    else
    {
        //printf("audio pause; scaler freeze; video pause; \n");
        msAPI_Player_AudioPause();
        msAPI_Player_ScalerFreeze();
        msAPI_Player_VideoPause();

        fEnableMvdTimingMonitor = FALSE;
        //printf("[[[fEnableMvdTimingMonitor = FALSE;]]]\n");
    }
#if ((ENABLE_SBTVD_DTV_SYSTEM) && (BRAZIL_CC))
    if(*MApp_Dmx_GetFid(EN_PES_FID) != MSAPI_DMX_INVALID_FLT_ID)
    {
        if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
        {
            MApp_CC_StopParser();
        }
        MApp_Dmx_PES_Stop();
    }
#endif
    /*[03]change state ================================================================*/
    if(u8PlaybackEnable)
    {
        _enPlaybackState = E_PLAYBACK_STATE_PAUSE;
        return TRUE;
    }
    else
    {
        //_enPlaybackState = _enPlaybackState;        //no change
        return TRUE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_Resume(void)
{
    DEBUG_PLAYBACK( printf("MApp_Playback_Resume()\n"); );

    enPvrPlaybackPathDirection _enPreDirection = _pstPvrPlaybackPath->enDirection;
    /*[01]error condition =============================================================*/
    if ((_enPlaybackState != E_PLAYBACK_STATE_OPEN        ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_PAUSE       ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_STOP        )   )
    {
        if(_enPlaybackState == E_PLAYBACK_STATE_WAIT)
        {
            MS_DEBUG_MSG(printf("_enPlaybackState == E_PLAYBACK_STATE_WAIT \n"));
            msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
            msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);
            msAPI_Player_ScalerWaitFree(50);
            msAPI_Player_ScalerMute(50);
            msAPI_Player_VideoEncoderReset();
            msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
        }
        return FALSE;
    }
  //printf("MApp_Playback_Resume \n");
#ifdef S3PLUS
    _pstPvrPlaybackPath->enPlaySpeed = E_PLAY_SPEED_1X;
#endif
    /*[02-1]set pvr playback path =====================================================*/
    if(_enPlaybackState == E_PLAYBACK_STATE_OPEN)    //live in
    {
        //%%%no-such-case, remove if necessary%%%//
    }
    else // E_PLAYBACK_STATE_PAUSE || E_PLAYBACK_STATE_STOP //file in
    {
        msAPI_PVR_PlaybackPathResume(_pstPvrPlaybackPath);
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    if((_enPlaybackState == E_PLAYBACK_STATE_OPEN) ||
       (_enPlaybackState == E_PLAYBACK_STATE_STOP)   )    //live in
    {
      //printf("audio play; scaler waitfree->mute; video play; \n");
        msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);
        msAPI_Player_ScalerWaitFree(100);
        msAPI_Player_ScalerMute(1000);
        if ( msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_DTV )
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }
        msAPI_Player_VideoEncoderReset();
        msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);

        fEnableMvdTimingMonitor = TRUE;
      //printf("[[[fEnableMvdTimingMonitor = TRUE;]]]\n");
    }
    else
    {
      //printf("audio stop->play; scaler waitfree; video monitor->resume; \n");
        //#ifdef PVR_UTOPIA
        //if(_enPlaybackState != E_PLAYBACK_STATE_PAUSE) //audio "pause-stop-play" will cause pvr "pause->play" without av sync
        //#endif
        if((_enPrePlaybackState != E_PLAYBACK_STATE_PAUSE)
            ||((_enPreDirection == E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD)
            ||(_enPreDirection == E_PLAYBACK_PATH_DIRECTION_FASTFORWARD)))
      {
        msAPI_Player_AudioStop();
      }
        msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);
        #ifndef S3PLUS
        #if(ENABLE_SBTVD_DTV_SYSTEM)
            msAPI_Player_ScalerWaitFree(500);
        #else
            //Enlarge un-freeze time for mantis 0796613:
            //[Milan 073B][PVR] Play recording file -> FF or FB -> Play, µe­±·|°{¤@¤U
            msAPI_Player_ScalerWaitFree(300);//(10);
        #endif
        #else
        msAPI_Player_ScalerWaitFree(50);
        #endif
        msAPI_Player_VideoEncoderReset();
        msAPI_Player_VideoMonitor(TRUE); // Reset GOP size info

    #ifdef PVR_UTOPIA
        msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
        _enPlaybackSpeed = E_PLAY_SPEED_1X;
        msAPI_Player_VideoConfigForwardSpeed(_enPlaybackSpeed);
    #else
        msAPI_Player_VideoResume();
    #endif
        if(((_enPrePlaybackState == E_PLAYBACK_STATE_FASTFORWARD) || (_enPrePlaybackState == E_PLAYBACK_STATE_FASTBACKWARD))
            &&(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_RESUME))
        {
            //Don't enable timing monitor for FF/FB -> play case
            //Which will lead to extra MVD setmode (then triggers XC set window, load pq, etc.)
            //for mantis 0796613:[Milan 073B][PVR] Play recording file -> FF or FB -> Play, µe­±·|°{¤@¤U
        }
        else
        {
            fEnableMvdTimingMonitor = TRUE;
        }
      //printf("[[[fEnableMvdTimingMonitor = TRUE;]]]\n");
    }
    //start CC
#if ((ENABLE_SBTVD_ATV_SYSTEM) && (BRAZIL_CC))
    U16 u16CCPid = MApp_PVR_Playback_GetCCPID();
    if(*MApp_Dmx_GetFid(EN_PES_FID) != MSAPI_DMX_INVALID_FLT_ID)
    {
        if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
        {
            MApp_CC_StopParser();
        }
        MApp_Dmx_PES_Stop();
    }
    if(u16CCPid!=MSAPI_DMX_INVALID_PID)
    {
        MApp_ClosedCaption_Open_Filter(u16CCPid);
        if (*MApp_Dmx_GetFid(EN_PES_FID) != MSAPI_DMX_INVALID_FLT_ID)
        {
            MApp_CC_CtrlParser(CC_SELECTOR_MODE, CC_MODE_DTV);
            MApp_CC_CtrlParser(CC_SELECTOR_SERVICE, CC_SERVICE_SERVICE1);
            MApp_CC_StartParser();
        }
    }
#endif
    /*[03]change state ================================================================*/
    _enPlaybackState = E_PLAYBACK_STATE_PLAYBACKING;
    _enPlaybackSpeed  = E_PLAY_SPEED_1X;

    return TRUE;
}

void _MApp_GetAudioIndexByAudioPID(void)
{
    MEMBER_SERVICETYPE bServiceType;
    AUD_INFO aAudioStreamInfo;
    WORD wCurrentPosition;
    U8 AudioLangNum;
    U8 i;

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    AudioLangNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);

    for (i = 0; i < AudioLangNum; i++)
    {
        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);

        if (aAudioStreamInfo.wAudPID == g_u16Current_PVR_AudioPID)
        {
            g_u8AudLangSelected = i;
            return;
        }
    }

    return;
}
/***************************************************************************************/
static BOOLEAN MApp_Playback_Disable(void)
{
    DEBUG_PLAYBACK( printf("MApp_Playback_Disable()\n"); );

    U8 u8PlaybackEnable = FALSE;

/*
#ifdef PVR_UTOPIA
    BOOL TS_PARALLEL_TYPE = FALSE;

    #if ENABLE_ATSC
        if(IsAtscInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ATSC_OUTPUT;
    #endif
    #if ENABLE_DVBT
        if(IsDVBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBT_OUTPUT;
    #endif
    #if ENABLE_DVBC
        if(IsDVBCInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBC_OUTPUT;
    #endif
    #if ENABLE_DTMB
        if(IsDTMBInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DTMB_OUTPUT;
    #endif
   #if ENABLE_ISDBT
        if(IsISDBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ISDBT_OUTPUT;
    #endif
#endif
*/
    /*[01]error condition =============================================================*/
    //printf("MApp_Playback_Disable \n");

    /*[02-1]set pvr playback path =====================================================*/
    if (_enPlaybackState == E_PLAYBACK_STATE_WAIT)
    {
        u8PlaybackEnable = FALSE;
    }
    else
    {
        msAPI_PVR_PlaybackPathStop(_pstPvrPlaybackPath);

        #ifdef S3PLUS
        gAvSync_PcrFid = MSAPI_DMX_INVALID_FLT_ID;
        #endif

        u8PlaybackEnable = TRUE;
    }

    /*[02-1-2]InIt TSP and set TSP filter  =====================================================*/
  #ifdef S3PLUS
    //Init TSP and set Tuner to serial mode
    if(MApp_Record_StateMachineGet()==E_RECORD_STATE_WAIT)
    {
        msAPI_DMX_Initial();//Init TSP

        if(bCardAInside) //Set Tuner to serial mode
        {
            //msAPI_Tuner_Serial_Control(FALSE,FALSE);
        }
        else
        {
            //msAPI_Tuner_Serial_Control(TRUE,FALSE);
        }
    }
    else
    {
        //We don't init TSP if the the record process is still running
    }
  #endif

    //Set TSP filter
    //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #ifdef PVR_8051
    msAPI_DMX_StartFilter( g_u16Current_PCRPID,             MSAPI_DMX_FILTER_TYPE_PCR,    &u8PcrFid );
    msAPI_DMX_StartFilter( g_u16Current_PVR_VideoPID,       MSAPI_DMX_FILTER_TYPE_VIDEO,  &u8VidFid );
    msAPI_DMX_StartFilter( g_u16Current_PVR_AudioPID,       MSAPI_DMX_FILTER_TYPE_AUDIO,  &u8AudFid );
    #ifndef S3PLUS
    msAPI_DMX_StartFilter( g_u16Current_AudioDescriptorPID, MSAPI_DMX_FILTER_TYPE_AUDIO2, &u8AdAFid );
    #endif
    #else
    msAPI_DMX_StartFilter( g_u16Current_PCRPID,             MSAPI_DMX_FILTER_TYPE_PCR,    MApp_Dmx_GetFid(EN_PCR_FID));
    msAPI_DMX_StartFilter( g_u16Current_PVR_VideoPID,       MSAPI_DMX_FILTER_TYPE_VIDEO,  MApp_Dmx_GetFid(EN_VIDEO_FID) );
    msAPI_DMX_StartFilter( g_u16Current_PVR_AudioPID,       MSAPI_DMX_FILTER_TYPE_AUDIO,  MApp_Dmx_GetFid(EN_AUDIO_FID) );
    msAPI_DMX_StartFilter( g_u16Current_AudioDescriptorPID, MSAPI_DMX_FILTER_TYPE_AUDIO2, MApp_Dmx_GetFid(EN_AD_FID) );
    #endif

    _MApp_GetAudioIndexByAudioPID();

    //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #if (ENABLE_SUBTITLE)
    #ifndef S3PLUS
    MApp_Subtitle_PID_Updated();
    #endif
    #endif
    //(TYPE3)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //(TYPE4)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //(TYPE5)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //((( )))~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /*[02-2]set audio/scaler/video ====================================================*/
  //printf("audio stop->restore->play; scaler freeze->waitfree; video stop->reset->restore->play; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();
    msAPI_Player_VideoReset(E_PLAY_SOURCE_LIVE);

/*
    #if (defined(S3PLUS) || defined(S4LITE))
    msAPI_Player_AudioRestore(FALSE);
    #else
    msAPI_Player_AudioRestore(stGenSetting.g_SoundSetting.bEnableAD);
    #endif
*/
  #if( ENABLE_DVB_AUDIO_DESC )
    msAPI_Player_AudioRestore(stGenSetting.g_SoundSetting.bEnableAD);
  #else
    msAPI_Player_AudioRestore(FALSE);
  #endif

    msAPI_Player_AudioPlay(E_PLAY_SOURCE_LIVE);
    msAPI_Player_ScalerWaitFree(50);
    msAPI_Player_ScalerMute(50);
    if ( msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_DTV )
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    msAPI_Player_VideoRestore();
    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);

  #ifdef S3PLUS
    MApp_Dmx_EnableTableMonitor();          //<--restore table monitor because demux switch to live
  #endif

#ifdef PVR_UTOPIA
#if( ENABLE_DVB&&ENABLE_CI )
    if (msAPI_CI_CardDetect())
    {
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_CI_IN_USE);
    }
    else
#endif
    {
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);
    }
#endif // #ifdef PVR_UTOPIA


#ifdef MEASURE_FFFB_TIME //=======================$$$//
    if(_enPlaybackState == E_PLAYBACK_STATE_FASTFORWARD)
    {
        printf("Fast Forward used time %04lu S\n",msAPI_Timer_DiffTimeFromNow(_u32FastForwardStartTime)/1000);
    }
#endif //MEASURE_FFFB_TIME =======================$$$//

#ifndef S3PLUS
  #ifndef PVR_UTOPIA
    msAPI_DMX_Switch2Pinpon(TRUE);
 #endif
#endif

#if ((ENABLE_SBTVD_DTV_SYSTEM) && (BRAZIL_CC))
    if(*MApp_Dmx_GetFid(EN_PES_FID) != MSAPI_DMX_INVALID_FLT_ID)
    {
        if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
        {
            MApp_CC_StopParser();
        }
        MApp_Dmx_PES_Stop();
    }
#endif

    /*[03]change state ================================================================*/
    if(u8PlaybackEnable)
    {
        _enPlaybackState = E_PLAYBACK_STATE_STOP;
        _enPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
    else
    {
        _enPlaybackState = E_PLAYBACK_STATE_WAIT;    //no change
        _enPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_Playback_Close(void)
{
    DEBUG_PLAYBACK( printf("MApp_Playback_Close()\n"); );

    /*[01]error condition =============================================================*/
    if (_enPlaybackState != E_PLAYBACK_STATE_STOP)
    {
        return FALSE;
    }
    //printf("MApp_Playback_Close \n");

    /*[02-1]set pvr playback path =====================================================*/
    _u8RecordedParentalRating = 0;
    msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);

    /*[02-2]set audio/scaler/video ====================================================*/

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        EN_CC_PVR_OPERATING_MODE eOperatingMode = EN_CC_PVR_OPERATING_MODE_WATCH_AND_BUFFER;
#if (ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL == 1)
        if(TRUE == MApp_GetActiveStandbyMode())
            eOperatingMode = EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING;
#endif
        MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,eOperatingMode,NULL,0);
        MAPP_CIPVR_PVRReTriggerURICopyProtect();
        MAPP_CIPVR_SetMuteFlag(false,E_SCREEN_MUTE_BY_PLAYBACK_PIN_EVENT);
        msAPI_CI_MMIClose();
#endif

    /*[03]change state ================================================================*/
    _enPlaybackState = E_PLAYBACK_STATE_WAIT;
    memset(_pu16PlaybackFileName,0,sizeof(_pu16PlaybackFileName));

    return TRUE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////// playback ap (time-bar-related) //////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U32 MApp_Playback_GetRecordStartTimeSec(void)
{
    U32 u32StartTime;

    /*[01]error condition =============================================================*/
    if ((_enPlaybackState != E_PLAYBACK_STATE_PLAYBACKING ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_PAUSE       ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) )
    {
        return 0;
    }
    //printf("MApp_Playback_GetRecordStartTimeSec \n");

    /*[02-1]set pvr record path =======================================================*/
    if((_pstPvrRecordPath->u32RecordedPeriod - _pstPvrRecordPath->u32PausedPeriod) < _pstPvrRecordPath->u32FileValidPeriod)
    {
        u32StartTime = _pstPvrRecordPath->u32RecordedTime/1000;
    }
    else
    {
        u32StartTime = _pstPvrRecordPath->u32RecordedTime/1000  +   //in 1/1000 SECOND
                       _pstPvrRecordPath->u32RecordedPeriod/10  -   //in 1/10   SECOND
                       _pstPvrRecordPath->u32PausedPeriod/10    -   //in 1/10   SECOND
                       _pstPvrRecordPath->u32FileValidPeriod/10;    //in 1/10   SECOND
    }
    return u32StartTime;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/
U32 MApp_Playback_GetRecordEndTimeSec(void)
{
    U32 u32EndTime;

    /*[01]error condition =============================================================*/
    if ((_enPlaybackState != E_PLAYBACK_STATE_PLAYBACKING ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_PAUSE       ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) )
    {
        return 0;
    }
    //printf("MApp_Playback_GetRecordEndTimeSec \n");

    /*[02-1]set pvr record path =======================================================*/
    u32EndTime = _pstPvrRecordPath->u32RecordedTime/1000 +        //in 1/1000 SECOND
                 _pstPvrRecordPath->u32RecordedPeriod/10 -        //in 1/10   SECOND
                 _pstPvrRecordPath->u32PausedPeriod/10;           //in 1/10   SECOND

    return u32EndTime;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/
U32 MApp_Playback_GetRecordValidPeriodSec(void)
{
    U32 u32ValidPeriod = 0;

    /*[01]error condition =============================================================*/
    if ((_enPlaybackState != E_PLAYBACK_STATE_PLAYBACKING ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_PAUSE       ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) )
    {
        return 0;
    }
    //printf("MApp_Playback_GetRecordValidPeriodSec \n");

    /*[02-1]set pvr record path =======================================================*/
    u32ValidPeriod = _pstPvrRecordPath->u32RecordedPeriod/10 -
                     _pstPvrRecordPath->u32PausedPeriod/10;

    return u32ValidPeriod;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

U32 MApp_Playback_GetTotalTimeSec(void)
{
    U32 u32TotalTime;

    u32TotalTime =_pstPvrRecordPath->u32RecordedPeriod/10 +           //in 1/10   SECOND
                          _pstPvrRecordPath->u32RecordedTotalTime/10 ;      //in 1/10   SECOND

    return u32TotalTime;

}

U32 MApp_Playback_GetStartSysTime(void)
{
    return _pstPvrRecordPath->u32RecordedStartSysTime;
}

enPvrEncryptType MApp_Playback_GetEncryptionType(void)
{
    return _pstPvrRecordPath->enEncryptionType;
}

void MApp_Playback_GetCurrentFileName(U16 * u16NameBuffer)
{
    #ifdef PVR_8051
    MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
    #endif
    UnicodeCpy((S8 *)u16NameBuffer, (S8 *)_pu16PlaybackFileName);
    #ifdef PVR_8051
    MDrv_Sys_ReleaseXdataWindow1();
    #endif
}

/***************************************************************************************/
U32 MApp_Playback_GetPlaybackTimeSec(void)
{
    U32 u32PlayTime;
    U32 u32TimeStamp;

    /*[01]error condition =============================================================*/
    if ((_enPlaybackState != E_PLAYBACK_STATE_PLAYBACKING ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_PAUSE       ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) )
    {
        return 0;
    }
    //printf("MApp_Playback_GetPlaybackTimeSec \n");
    MApi_DMX_GetFileInTimeStamp(&u32TimeStamp);

    if((MApp_Playback_GetRecordValidPeriodSec()>1)&&((u32TimeStamp>(MApp_Playback_GetRecordValidPeriodSec()-1)*90*1000)&&(u32TimeStamp<MApp_Playback_GetRecordValidPeriodSec()*90*1000)))
    {
        u32TimeStamp =MApp_Playback_GetRecordValidPeriodSec()*90*1000;
    }
    //1

    u32PlayTime = u32TimeStamp/90/1000;  //SECOND

    // avoid play time get error
    if (u32PlayTime > u32PrePlayTime+50)
    {
        u32PlayTime  = u32PrePlayTime;
    }
    else
    {
        if (u32PlayTime != 0)
        {
            u32PrePlayTime = u32PlayTime;
        }
    }
    /*[02-1]set pvr playback path =====================================================*/

    return u32PlayTime;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/
enPlaySpeed MApp_Playback_GetPlaybackSpeed(void)
{
    /*[01]error condition =============================================================*/
    if ((_enPlaybackState != E_PLAYBACK_STATE_PLAYBACKING ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_PAUSE       ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enPlaybackState != E_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enPlaybackState != E_PLAYBACK_STATE_SLOWFORWARD) )
    {
        return E_PLAY_SPEED_1X;
    }
    //printf("MApp_Playback_GetPlaybackSpeed \n");

    /*[02-1]set pvr playback path =====================================================*/
    return _enPlaybackSpeed;

    /*[02-2]set audio/scaler/video ====================================================*/

    /*[03]change state ================================================================*/
}

/*###############################################################################################*/
/*////////////////////////////// playback ap (link to record) ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
BOOLEAN MApp_Playback_StopRecordLinkage(void)
{
    if(_enPlaybackState != E_PLAYBACK_STATE_WAIT)
    {
        _pstPvrPlaybackPath->bLinkRecord = FALSE;
        //printf("StopRecordLinkage \n");
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////// playback ap (link to audio) ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U8 MApp_Playback_AudioGetLanguageSelection(void)
{
    return _pstPvrRecordPath->u8audioLangSel;
}

/***************************************************************************************/
U8 MApp_Playback_AudioGetLanguageTotal(void)
{
    if (MAX_AUD_LANG_NUM < _pstPvrRecordPath->u8audioLangTotal)
    {
        return MAX_AUD_LANG_NUM;
    }
    else
    {
        return _pstPvrRecordPath->u8audioLangTotal;
    }
}

/***************************************************************************************/
BYTE MApp_Playback_AudioGetLanguageInfo(void)
{
    return  _pstPvrRecordPath->PVRAudioInfo[g_u8AudLangSelected].aISOLangInfo[0].bISOLanguageInfo;
}

/***************************************************************************************/
BOOLEAN MApp_Playback_AudioGetStreamInfo(AUD_INFO* pstAudioStreamInfo, U8 u8Idx)
{
    if (u8Idx < _pstPvrRecordPath->u8audioLangTotal)
    {
        memcpy(pstAudioStreamInfo, &_pstPvrRecordPath->PVRAudioInfo[u8Idx], sizeof(_pstPvrRecordPath->PVRAudioInfo[u8Idx]));
        return TRUE;
    }
    else
        return FALSE;
}

/***************************************************************************************/
void MApp_Playback_AudioSelectLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
}

/***************************************************************************************/
void MApp_Playback_AudioStopLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
}

/***************************************************************************************/
#ifndef S3PLUS
void MApp_Playback_AdAudioSelectLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);
}

/***************************************************************************************/
void MApp_Playback_AdAudioStopLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);
}
#endif
/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////// playback ap (link to subtitle) //////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void MApp_Playback_Subtitle_LoadServices(U8* pu8SelIdx, U8* pu8Num, DVB_SUBTITLE_SERVICE* options)
{
    *pu8Num    = _pstPvrRecordPath->u8DVBSubtitleServiceNum;
    *pu8SelIdx = _pstPvrRecordPath->u8SubtitleMenuSelectedIdx;
    memcpy(options, _pstPvrRecordPath->PVRDVBSubtitleServices, sizeof(_pstPvrRecordPath->PVRDVBSubtitleServices));
}

/***************************************************************************************/
void MApp_Playback_Subtitle_LoadMenu(U8* pu8SelIdx, U8* pu8Num, SUBTITLE_MENU* options, U8* pu8fEnableSubtitle, U8* pu8fEnableTTXSubtitle)
{
    *pu8Num    = _pstPvrRecordPath->u8SubtitleMenuNum;
    *pu8SelIdx = _pstPvrRecordPath->u8SubtitleMenuSelectedIdx;
    memcpy(options, _pstPvrRecordPath->PVRSubtitleMenu, sizeof(_pstPvrRecordPath->PVRSubtitleMenu));
    *pu8fEnableSubtitle    = _pstPvrRecordPath->u8EnableSubtitle;
    *pu8fEnableTTXSubtitle = _pstPvrRecordPath->u8EnableTTXSubtitle;
}

/***************************************************************************************/
void MApp_Playback_TTXSubtitle_GetNum(U8* pu8Num)
{
    *pu8Num =_pstPvrRecordPath->u8TTXSubtitleServiceNum;
}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////////// playback ap (AB Loop) //////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void MApp_Playback_ABLoop_SetA(void)
{
    if(_enPlaybackState != E_PLAYBACK_STATE_WAIT)
    {
        _pstPvrPlaybackPath->u32FilePosAKB = _pstPvrPlaybackPath->u32FilePositionKB;
    }
}

/***************************************************************************************/
void MApp_Playback_ABLoop_SetB(void)
{
    if(_enPlaybackState != E_PLAYBACK_STATE_WAIT)
    {
        _pstPvrPlaybackPath->bABLoopSwitch = TRUE;
    }
}

/***************************************************************************************/
void MApp_Playback_ABLoop_Off(void)
{
    if(_enPlaybackState != E_PLAYBACK_STATE_WAIT)
    {
        if(_pstPvrPlaybackPath != NULL)
        {
            _pstPvrPlaybackPath->bABLoopSwitch = FALSE;
        }
    }
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////// playback ap (finite state machine) ////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
/***************************************************************************************/
void MApp_Playback_StateMachineRunning(void)
{
    #if DEBUG_PLAYBACK_STATE  //=======================================================//
    {
        static U8 preState = 0xFF;
        if(preState != _enPlaybackState)
        {
            //printf("Playback [%d]->[%d]\n", (int)preState, (int)_enPlaybackState);
            preState = _enPlaybackState;
        }
    }
    #endif  //=========================================================================//
    _enPrePlaybackState = _enPlaybackState;

    switch (_enPlaybackState)
    {
        /*[01]WAIT state (channel change) =============================================*/
        case E_PLAYBACK_STATE_WAIT:
        {
            if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_OPEN)
            {
                #ifdef PVR_8051
                U16   u16PlaybackExtPara        = (U16        )_u32PlaybackExtPara;   //type casting
                U16 xdata * pu16PlaybackExtPara = (U16 xdata *) u16PlaybackExtPara;   //typp casting
                #else
                U16 * pu16PlaybackExtPara       = (U16       *)_u32PlaybackExtPara;   //typp casting
                #endif

                if(!MApp_Playback_Open(pu16PlaybackExtPara))
                {
                    //printf("STCH[[PLAYBACK]]@WAIT->WAIT\n");
                    _enPlaybackState = E_PLAYBACK_STATE_WAIT;                   //<--exception-1
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                    break;
                }
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_ENABLE);
                if(MApp_Playback_Enable())
                {
                    MApp_Playback_Resume();
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                    MAPP_CIPVR_SetMuteFlag(false,E_SCREEN_MUTE_BY_LIVE_PIN_EVENT);
#endif
                    MApp_Dmx_EnableFileInMonitorNumber(_pstPvrRecordPath->u16ServiceID);
                    //printf("STCH[[PLAYBACK]]@WAIT->PLAYBACKING\n");
                    _enPlaybackState = E_PLAYBACK_STATE_PLAYBACKING;
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                    u32PrePlayTime = 0;
                }
                else
                {
                    MApp_Playback_Resume();
                    //printf("STCH[[PLAYBACK]]@WAIT->E_PLAYBACK_STATE_WAIT\n");
                    _enPlaybackState = E_PLAYBACK_STATE_WAIT;
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                }
            }
            else if(_enPlaybackInput != E_PLAYBACK_INPUT_NONE)
            {
                MS_DEBUG_MSG(printf("ERROR_INPUT_TO_WAIT\n"));
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
            }

            break;
        }

        case E_PLAYBACK_STATE_OPEN:
            break;

        /*[02]PLAYBACKING state =========================================================*/
        case E_PLAYBACK_STATE_PLAYBACKING:
        case E_PLAYBACK_STATE_PAUSE:
        case E_PLAYBACK_STATE_SLOWFORWARD:
        case E_PLAYBACK_STATE_FASTFORWARD:
        case E_PLAYBACK_STATE_FASTBACKWARD:
        {
            if((_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_FAST_FORWARD)
            ||(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_FAST_BACKWARD))
            {
                if(_bDisplayOneField == FALSE)
                {
                    _bDisplayOneField = TRUE;
                    MApi_VDEC_SetControl(VDEC_USER_CMD_DISP_ONE_FIELD, 1);
                }
            }
            else if(_enPlaybackInput != E_PLAYBACK_INPUT_NONE)
            {
                if(_bDisplayOneField == TRUE)
                {
                    _bDisplayOneField = FALSE;
                    MApi_VDEC_SetControl(VDEC_USER_CMD_DISP_ONE_FIELD, 0);
                }
            }

            /*[02-1]playback on/off =====================================================*/
            if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_CLOSE)
            {
                MApp_Dmx_DisableFileInMonitor();
                msAPI_PVR_PlaybackPathWaitAVFifoClean();//reset CmdQ ,and wait AVFifo clean to prevent TSP from going in the block state
                MApi_DMX_BypassFileInTimeStamp(TRUE);
                // Fix Mantis 0814268
                if (MApi_DMX_Filein_IsPause())
                {
                    MApi_DMX_Filein_Resume();
                }
                msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                MApi_DMX_BypassFileInTimeStamp(FALSE);
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_RESUME);
                MApp_Playback_Resume();
                MApp_Playback_Disable();
                MApp_Playback_Close();
              //printf("STCH[[PLAYBACK]]@PLAYBACKING->WAIT\n");
                _enPlaybackState = E_PLAYBACK_STATE_WAIT;
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_PAUSE)
            {
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_NONE);
                if(!MApi_DMX_Filein_IsPause())
                {
                    MApi_DMX_Filein_Pause();
                }
                _enPlaybackState = E_PLAYBACK_STATE_PAUSE;
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_STEP_IN)
            {
                if(MApi_DMX_Filein_IsPause())
                {
                    MApi_DMX_Filein_Resume();
                }
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_STEPIN);  //fast forward / fast backward
                MApp_Playback_StepIn();
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_JUMP_TO_TIME)
            {
                //msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_JUMPTOTIME);
                if(!MApp_Playback_JumpToTime(_u32PlaybackExtPara))
                {
                    MApp_Playback_Resume();
                    MApp_Playback_Disable();
                    MApp_Playback_Close();
                  //printf("STCH[[PLAYBACK]]@PLAYBACKING->STOP\n");
                    _enPlaybackState = E_PLAYBACK_STATE_STOP;
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                }
                else
                {
                    MApp_Playback_Resume();
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                }
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_JUMP_FORWARD)
            {
                //msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_JUMPFORWARD);
                if(!MApp_Playback_JumpForward(_u32PlaybackExtPara))
                {
                    MApp_Playback_Resume();
                    MApp_Playback_Disable();
                    MApp_Playback_Close();
                  //printf("STCH[[PLAYBACK]]@PLAYBACKING->STOP\n");
                    _enPlaybackState = E_PLAYBACK_STATE_STOP;
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                }
                else
                {
                    MApp_Playback_Resume();
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                }
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_JUMP_BACKWARD)
            {
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_JUMPBACKWARD);
                MApp_Playback_JumpBackward(_u32PlaybackExtPara);
                MApp_Playback_Resume();
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_SLOW_FORWARD)
            {
                MApi_DMX_GetFileInTimeStamp(&u32TempTimeCounter);
                u32StartSysTime = msAPI_Timer_GetTime0();
                if(MApi_DMX_Filein_IsPause())
                {
                    MApi_DMX_Filein_Resume();
                }
                if(_bPlaybackStepIn)
                {
                    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
                }
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_SLOWFORWARD);
                MApp_Playback_SlowForward();
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_FAST_FORWARD)
            {
                MApi_DMX_GetFileInTimeStamp(&u32TempTimeCounter);
                u32StartSysTime = msAPI_Timer_GetTime0();
                if(MApi_DMX_Filein_IsPause())
                {
                    MApi_DMX_Filein_Resume();
                }
                if(_bPlaybackStepIn)
                {
                    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
                }
                #if (!INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE_EXE)
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_FASTFORWARD);
                #endif
                MApp_Playback_FastForward();
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_FAST_BACKWARD)
            {
                MApi_DMX_GetFileInTimeStamp(&u32TempTimeCounter);
                u32StartSysTime = msAPI_Timer_GetTime0();
                if(MApi_DMX_Filein_IsPause())
                {
                    MApi_DMX_Filein_Resume();
                }
                if(_bPlaybackStepIn)
                {
                    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
                }
                #if (!INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE_EXE)
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_FASTBACKWARD);
                #endif
                MApp_Playback_FastBackward();
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_RESUME)
            {
                 if(MApi_DMX_Filein_IsPause())
                {
                    MApi_DMX_Filein_Resume();
                }
                MApp_Playback_Pause(E_PLAYBACK_NEXTACT_RESUME);  //fast forward / fast backward
                MApp_Playback_Resume();
                _enPlaybackState = E_PLAYBACK_STATE_PLAYBACKING;
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }
            else if(_enPlaybackInput != E_PLAYBACK_INPUT_NONE)
            {
                MS_DEBUG_MSG(printf("ERROR_INPUT_TO_PLAYBACKING\n"));
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                _bPlaybackStepIn = FALSE;
            }

            /*[02-2]playback running ====================================================*/
            if(!MApp_Playback_Routine())
            {
                if(_enPlaybackStatus != E_PVR_API_STATUS_PLAYBACK_NO_OUTPUT)    //wait data runout
                {
                    msAPI_PVR_PlaybackPathWaitAVFifoClean();////reset CmdQ ,and wait AVFifo clean to prevent TSP from going in the block state
                    MApi_DMX_BypassFileInTimeStamp(TRUE);
                    msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                    MApi_DMX_BypassFileInTimeStamp(FALSE);
                    MApp_Playback_Pause(E_PLAYBACK_NEXTACT_RESUME);
                    MApp_Playback_Resume();
                    MApp_Playback_Disable();
                  //printf("STCH[[PLAYBACK]]@PLAYBACKING->STOP\n");
                    _enPlaybackState = E_PLAYBACK_STATE_STOP;                   //<--exception-2
                    _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
                    _bPlaybackStepIn = FALSE;
                }
            }

            break;
        }

        /*[03]STOP state ==============================================================*/
        case E_PLAYBACK_STATE_STOP:
        {
            /*[03-1]playback on/off =====================================================*/
            if(_enPlaybackInput == E_PLAYBACK_INPUT_PLAYBACK_CLOSE)
            {
                MApp_Playback_Close();
              //printf("STCH[[PLAYBACK]]@STOP->WAIT\n");
                _enPlaybackState = E_PLAYBACK_STATE_WAIT;
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
            }
            else if(_enPlaybackInput != E_PLAYBACK_INPUT_NONE)
            {
                MS_DEBUG_MSG(printf("ERROR_INPUT_TO_STOP\n"));
                _enPlaybackInput = E_PLAYBACK_INPUT_NONE;
            }
            _bPlaybackStepIn = FALSE;
            break;
        }
    }
}

/***************************************************************************************/
void MApp_Playback_StateMachineInput(enPlaybackInput enSMInput, U32 u32ExtParameter)
{
    _enPlaybackInput    = enSMInput;
    _u32PlaybackExtPara = u32ExtParameter;

    switch (_enPlaybackInput)
    {
        //(1)playback open ============================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_OPEN:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_OPEN\n");
            break;
        }

        //(2)playback pause ===========================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_PAUSE:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_PAUSE\n");
            break;
        }

        //(3)playback resume ==========================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_RESUME:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_RESUME\n");
            break;
        }

        //(4)jump forward =============================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_JUMP_FORWARD:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_JUMP_FORWARD\n");
            break;
        }

        //(5)jump backward ===========================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_JUMP_BACKWARD:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_JUMP_BACKWARD\n");
            break;
        }

        //(6)fast forward =============================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_FAST_FORWARD:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_FAST_FORWARD\n");
            break;
        }

        //(7)fast backward ===========================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_FAST_BACKWARD:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_FAST_BACKWARD\n");
            break;
        }

        //(8)playback close ===========================================================//
        case E_PLAYBACK_INPUT_PLAYBACK_CLOSE:
        {
          //printf("E_PLAYBACK_INPUT_PLAYBACK_CLOSE\n");
            break;
        }

        //(0)default ==================================================================//
        default:
        {
          //printf("MApp_Playback Unknown Input: %x\n", enSMInput);
            break;
        }

        //=============================================================================//
    }

    MApp_Playback_StateMachineRunning();

    _enPlaybackInput    = E_PLAYBACK_INPUT_NONE;    //ensure to consume any input
    _u32PlaybackExtPara = 0;                        //ensure to consume any parameter

}

/***************************************************************************************/
enPlaybackState MApp_Playback_StateMachineGet(void)
{
    return _enPlaybackState;
}

/***************************************************************************************/
enPvrApiStatus  MApp_Playback_StatusGet(void)
{
    enPvrApiStatus enPlaybackStatus = _enPlaybackStatus;
    _enPlaybackStatus = E_PVR_API_STATUS_OK;    //read clear
    return enPlaybackStatus;
}

U8  MApp_Playback_GetParentRating(void)
{
    return _u8RecordedParentalRating;
}

/***************************************************************************************/


#else
BOOLEAN code compile_mapp_playback;
#endif//ENABLE_PVR
#undef MAPP_PLAYBACK_C
