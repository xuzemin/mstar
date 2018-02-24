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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_TIMESHIFT_C

//system
#include "Board.h"                  //For pvr select
#include "sysinfo.h"                //For record/playback buffer

#include "debug.h"

#if ENABLE_PVR

//api
#include "IOUtil.h"                 //For Unicode String compare
#include "msAPI_Timer.h"            //For timer
#include "msAPI_DTVSystem.h"        //For audio info
#include "msAPI_PVR.h"              //For pvr
#include "msAPI_Player.h"           //For player
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_TV.h"
#include "MApp_CIPVR_Adaption.h"              //For pvr
#endif
#include "msAPI_PVRFileSystem.h"
#include "msAPI_audio.h"
//ap
#ifdef PVR_8051
#include "mapp_demux.h"             //For demux
#else
#include "MApp_GlobalVar.h"         //For demux
#endif
#include "mapp_si.h"                //For SI
#ifdef S3PLUS
#include "MApp_MHEG5_Main.h"        //For MHEG5
#endif
#include "MApp_ChannelChange.h"     //For channel change
#include "MApp_TimeShift.h"         //For itself
#include "MApp_MassStorage.h"       //For USB detection

#include "MApp_AVSync.h"

//ui <--better not be here
#ifdef PVR_8051
#ifdef S3PLUS
#include "MApp_UiMenuFunc.h"
#endif
#include "MApp_UiMenu.h"
#else
#include "MApp_UiMenuDef.h"
#endif
#include "MApp_UiPvr.h"
#include "MApp_ZUI_ACTpvr.h"
#include "MApp_MVDMode.h"
#include "MApp_Audio.h"
#include "MApp_CIMMI.h"

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#endif


/*************************************************************************************************/
#define JUMPDETECTTIMER         30000
#define JUMPSTEPCOUNTER         1000
#define BEGINJUMPTHRELD         100     // IN  1/10 second

#define DEBUG_TIMESHIFT_STATE   0

/*************************************************************************************************/
typedef enum
{
    E_TIMESHIFT_PLAYBACK_NEXTACT_NONE,
    E_TIMESHIFT_PLAYBACK_NEXTACT_RECORDOPEN,
    E_TIMESHIFT_PLAYBACK_NEXTACT_ENABLE,
    E_TIMESHIFT_PLAYBACK_NEXTACT_RESUME,
    E_TIMESHIFT_PLAYBACK_NEXTACT_FASTFORWARD,
    E_TIMESHIFT_PLAYBACK_NEXTACT_FASTBACKWARD,
    E_TIMESHIFT_PLAYBACK_NEXTACT_JUMPFORWARD,
    E_TIMESHIFT_PLAYBACK_NEXTACT_JUMPBACKWARD,
    E_TIMESHIFT_PLAYBACK_NEXTACT_JUMPTOTIME,
    E_TIMESHIFT_PLAYBACK_NEXTACT_STEPIN,
    E_TIMESHIFT_PLAYBACK_NEXTACT_SLOWFORWARD,
} enTimeShiftPlaybackActionAfterPause;

//<<record state>>===============================================================================//
typedef enum
{
    E_TIMESHIFT_RECORD_STATE_DISABLE,
    E_TIMESHIFT_RECORD_STATE_OPEN,
    E_TIMESHIFT_RECORD_STATE_RUNNING,
    E_TIMESHIFT_RECORD_STATE_STOP
} enTimeShiftRecordState;

/*************************************************************************************************/
static _msAPI_PVR_RecordPath   * _pstPvrRecordPath;                                                 //one record   path for timeshift
static _msAPI_PVR_PlaybackPath * _pstPvrPlaybackPath;                                               //one playback path for timeshift

static enTimeShiftRecordState   _enTimeShiftRecordState     = E_TIMESHIFT_RECORD_STATE_DISABLE;     //record_state
static enTimeShiftPlaybackState _enTimeShiftPlaybackState   = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;   //playback_state
static enPlaySpeed              _enTimeShiftPlaybackSpeed   = E_PLAY_SPEED_1X;                      //playback_speed
static enTimeShiftState         _enTimeShiftState           = E_TIMESHIFT_STATE_WAIT;               //timeshift_state_machine
static enTimeShiftInput         _enTimeShiftInput           = E_TIMESHIFT_INPUT_NONE;               //timeshift_input from outside
static U32                      _u32TimeShiftExtPara        = 0;                                    //timeshift_input from outside
static enPvrApiStatus           _enTimeShiftStatus          = E_PVR_API_STATUS_OK;                  //timeshift_status

static U16 _pu16TimeShiftFileName[]={'T','I','M','E','S','H','I','F','T','.','T','S',0};

static BOOL _bTimeshiftStepIn = FALSE;        // the timer difference direction
static BOOL _bTimeshiftStepInTrigger = FALSE;        // the timer difference direction


static U32 u32TimeshiftTempTimeCounter = 0;
static U32 u32TimeshiftStartSysTime =0;
static U32 u32OriginPlayTime =0;

#define TIME_CALIBRATION_MACRO      1
#define TIME_CALIBRATION_MICRO      2

#define INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE    TRUE

extern U16 g_u16CiPinCode;

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
/*//////////////////////////////////////// record path //////////////////////////////////////////*/
/*###############################################################################################*/

void msAPI_TimeShift_VideoInit(enPlayVideoType enVideoType, enPlaySource enSource)
{
    VDEC_DispInfo preInfo;

    memcpy(&preInfo, &gstPreVidStatus, sizeof(VDEC_DispInfo));

    msAPI_Player_VideoInit(enVideoType,  enSource);

    bMVDTimingChange = FALSE;
    memcpy(&gstPreVidStatus, &preInfo, sizeof(VDEC_DispInfo));
}

/***************************************************************************************/
void MApp_TimeShift_DelTsFileName(void)
{
    U8 fhander;
    U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
    if((!(u8USBState & MS_USB_CONNECTED)) && (!(u8USBState & MS_USB2_CONNECTED))){
        _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
        return;
    }

    fhander = msAPI_PVRFS_FileOpen(_pu16TimeShiftFileName, PVRFS_OPEN_FOR_READ);
    if(fhander != INVALID_FILE_HANDLE)
    {
        msAPI_PVRFS_FileClose(fhander);
        msAPI_PVRFS_FileDelete(_pu16TimeShiftFileName);
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        msAPI_CIPVRFS_FileDelete(_pu16TimeShiftFileName);
#endif
        _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
    }
}

/***************************************************************************************/
U32  MApp_TimeShift_RecordStopDiv(void)
{
    if (_enTimeShiftRecordState == E_TIMESHIFT_RECORD_STATE_STOP)
        return msAPI_Timer_DiffTimeFromNow(_pstPvrRecordPath->u32RecordedTime);
    else
        return 0;
}

/***************************************************************************************/
BOOLEAN MApp_TimeShift_IsRecordStoping(void)
{
    if(_enTimeShiftRecordState == E_TIMESHIFT_RECORD_STATE_STOP)
        return TRUE;
    else
        return FALSE;
}

void MApp_TimeShift_Record_Reset(void)
{
    LongLong llFilePos;
    U32 u32pvrBeginFilePosition = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE;

    if (u32RecordLastWriteDataSize)
    {
            u32RecordLastWriteDataSize = 0; // nor roll back err data
            llFilePos = msAPI_PVRFS_FileTell(_pstPvrRecordPath->hWriteFile);
                printf("current file position =  %x, last write data size = %d\n",llFilePos.Lo,u32RecordLastWriteDataSize);
            if (llFilePos.Lo > (u32RecordLastWriteDataSize + u32pvrBeginFilePosition))
            {
                printf("reset position\n");
                llFilePos.Lo = llFilePos.Lo - u32RecordLastWriteDataSize;
                u32RecordReWriteDataSize += u32RecordLastWriteDataSize;
                if (llFilePos.Lo % PVR_TS_PACKET_SIZE)
                {
                    U32 u32tmpValue;
                    u32tmpValue = llFilePos.Lo % PVR_TS_PACKET_SIZE;
                    llFilePos.Lo = llFilePos.Lo - u32tmpValue;
                    u32RecordReWriteDataSize += u32tmpValue;
                }
            }
            else
            {
                u32RecordReWriteDataSize = llFilePos.Lo - u32pvrBeginFilePosition;
                llFilePos.Lo = u32pvrBeginFilePosition;
            }
            u32RecordLastWriteDataSize = 0;
            msAPI_PVRFS_FileSeek(_pstPvrRecordPath->hWriteFile, llFilePos, PVRFS_SEEK_OPTION_FROM_BEGIN);
    }

    msAPI_PVR_RecoreReset(_pstPvrRecordPath);
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_RecordOpen(void)
{
    U8 u8RecordOpen = FALSE;

    /*[01]error condition =============================================================*/
    if (_enTimeShiftRecordState != E_TIMESHIFT_RECORD_STATE_DISABLE)
    {
          return FALSE;
    }
    //printf("MApp_TimeShift_RecordOpen \n");
    if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
       msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    {
        if(msAPI_PVR_IsRecordSpaceEnough() == FALSE)
        {
            _enTimeShiftStatus = E_PVR_API_STATUS_NO_DISK_SPACE;
            _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
            return FALSE;
        }
    }
    /*[02-1]set pvr record path =======================================================*/
    _pstPvrRecordPath = msAPI_PVR_RecordPathOpen(_pu16TimeShiftFileName, E_FILE_MODE_RING);

    if(_pstPvrRecordPath)
    {
        u8RecordOpen = TRUE;

        WORD wProgramPositon;
        MEMBER_SERVICETYPE bServiceType;
        bServiceType = msAPI_CM_GetCurrentServiceType();
        wProgramPositon = msAPI_CM_GetCurrentPosition(bServiceType);

#if ENABLE_PVR_AESDMA
          _pstPvrRecordPath->enEncryptionType = E_PVR_ENCRYPTION_DEFAULT;
#else
        _pstPvrRecordPath->enEncryptionType = E_PVR_ENCRYPTION_NONE;
#endif

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        U16 u16CiPinCode = g_u16CiPinCode;
        CI_CC_URI_LICENSE stUriLicense;
        U8 u8aCICAMID[CC_AUTH_ID_SIZE] = { 0 };
        if(msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED)
                ||(EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode()))
        {
            enPvrApiStatus enPvrStatus = MAPP_CIPVR_CIPlusPVRHandling(PVR_PATH_RECORD,true,u16CiPinCode);
            if((E_PVR_API_STATUS_OK != enPvrStatus) && (E_PVR_API_STATUS_SUCCESS_CIPLUS_COPY_PROTECTION != enPvrStatus))
            {
                _enTimeShiftStatus = enPvrStatus;
                _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
                msAPI_PVR_RecordPathClose(_pstPvrRecordPath);
                _pstPvrRecordPath = NULL;
                msAPI_PVRFS_FileDelete(_pu16TimeShiftFileName);
                msAPI_CIPVRFS_FileDelete(_pu16TimeShiftFileName);
              return RECORD_PATH_INVALID;
            }
            if(E_PVR_API_STATUS_SUCCESS_CIPLUS_COPY_PROTECTION == enPvrStatus)
            {
                //for CI+ scramble only
                _pstPvrRecordPath->enEncryptionType = E_PVR_ENCRYPTION_CIPLUS;
                if(FALSE == msAPI_CI_CC_GetCICAMID(u8aCICAMID))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enTimeShiftStatus = E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                    _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
                    msAPI_PVR_RecordPathClose(_pstPvrRecordPath);
                    _pstPvrRecordPath = NULL;
                    msAPI_PVRFS_FileDelete(_pu16TimeShiftFileName);
                    msAPI_CIPVRFS_FileDelete(_pu16TimeShiftFileName);
                    return RECORD_PATH_INVALID;
                }
                if(msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED)
                        &&(FALSE == msAPI_CI_CC_GetCicamUriLicenseUpdate(&stUriLicense,false)))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enTimeShiftStatus = E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                    _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
                    msAPI_PVR_RecordPathClose(_pstPvrRecordPath);
                    _pstPvrRecordPath = NULL;
                    msAPI_PVRFS_FileDelete(_pu16TimeShiftFileName);
                    msAPI_CIPVRFS_FileDelete(_pu16TimeShiftFileName);
                    return RECORD_PATH_INVALID;
                }
            }
            else
            {
                //for CI scramble only
                _pstPvrRecordPath->enEncryptionType = E_PVR_ENCRYPTION_DEFAULT;
            }
            MAPP_CIPVR_RecordStartEventUpdate(stUriLicense, u8aCICAMID);
        }
#endif

#if (ENABLE_CI == 1)
        if(TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED))
        {
            EN_CI_VERSION CicamVersion = msAPI_CI_CC_CAM_Mode();
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
            if(TRUE == MAPP_CIPVR_IsCopyFreely(TRUE))
            {
                CicamVersion = EN_CI_VERSION_CI;
            }
#endif
    printf(".record  e1.....%s %d .%d..........\n",__FUNCTION__,__LINE__,CicamVersion);
            _pstPvrRecordPath->u8CicamCheckLevel = (U8)CicamVersion;
        }
        else
#endif
        {
    printf(".record  e2.....%s %d . .......\n",__FUNCTION__,__LINE__);
            _pstPvrRecordPath->u8CicamCheckLevel = 0;
        }
    }
    else
    {
        //printf("TimeShift record open fail\n");
        u8RecordOpen = FALSE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/
    if(u8RecordOpen)
    {
        _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_OPEN;
        return TRUE;
    }
    else
    {
        _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
        return FALSE;
    }
}

/***************************************************************************************/
static BOOLEAN  MApp_TimeShift_RecordEnable(void)
{
    U8 u8RecordEnable = FALSE;
#if 1
    U8 u8i;
    AUD_INFO AudioStreamInfo;
#endif


    /*[01]error condition =============================================================*/
    if (_enTimeShiftRecordState != E_TIMESHIFT_RECORD_STATE_OPEN)
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_RecordEnable \n");

    /*[02-1]set pvr record path =======================================================*/
    _pstPvrRecordPath->u32BufferStart  = PvrGetWriteSdramAdr();                 //<--from system
    _pstPvrRecordPath->u32BufferLength = PVR_WRITE_SDRAM_LEN;                 //<--from system
    if ((_enTimeShiftStatus=msAPI_PVR_RecordPathSet(_pstPvrRecordPath)) == E_PVR_API_STATUS_OK)
    {
        //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, g_u16Current_PCRPID,             MSAPI_DMX_FILTER_TYPE_PCR);          //<--from other AP:(01) PCR
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, g_u16Current_PVR_VideoPID,       MSAPI_DMX_FILTER_TYPE_VIDEO);        //<--from other AP:(02) VIDEO
      //msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, g_u16Current_PVR_AudioPID,       MSAPI_DMX_FILTER_TYPE_AUDIO);        //<--from other AP:(03) AUDIO
        #ifndef S3PLUS
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, g_u16Current_AudioDescriptorPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);       //<--from other AP:(04) AUDIO DESCRIPTOR
        #endif
#if 1
        _pstPvrRecordPath->u8audioLangTotal = msAPI_CM_GetAudioStreamCount(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
        _pstPvrRecordPath->u8audioLangSel = g_u8AudLangSelected;

        #ifdef S3PLUS
        for (u8i=0 ; u8i < _pstPvrRecordPath->u8audioLangTotal; u8i++)
        {
            if (E_RESULT_SUCCESS == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
            {
                if (u8i == g_u8AudLangSelected)
                {
                    msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, AudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
                    memcpy(&_pstPvrRecordPath->PVRAudioInfo[0], &AudioStreamInfo, sizeof(AudioStreamInfo));
                    break;
                }
            }
        }
        _pstPvrRecordPath->u8audioLangTotal = 1;
        _pstPvrRecordPath->u8audioLangSel   = 0;
        #else
        for (u8i=0; u8i < _pstPvrRecordPath->u8audioLangTotal; u8i++)
        {
            #ifdef PVR_8051
            if( E_RESULT_SUCCESS == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
            #else
            if( TRUE == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
            #endif
            {
                msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, AudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
                memcpy(&_pstPvrRecordPath->PVRAudioInfo[u8i], &AudioStreamInfo, sizeof(AudioStreamInfo));
            }
        }
        #endif
#endif
        //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#if (ENABLE_SUBTITLE)

        _pstPvrRecordPath->u8DVBSubtitleServiceNum = u8DVBSubtitleServiceNum;
        _pstPvrRecordPath->u8SubtitleMenuNum = u8SubtitleMenuNum;

        for (u8i =0; u8i < u8DVBSubtitleServiceNum; u8i++)
        {
            msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, DVBSubtitleServices[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
            memcpy( _pstPvrRecordPath->PVRDVBSubtitleServices[u8i].StringCodes, DVBSubtitleServices[u8i].StringCodes, 4);
            _pstPvrRecordPath->PVRDVBSubtitleServices[u8i].u16PID                   = DVBSubtitleServices[u8i].u16PID;
            _pstPvrRecordPath->PVRDVBSubtitleServices[u8i].u16Ancillary_Page_id     = DVBSubtitleServices[u8i].u16Ancillary_Page_id;
            _pstPvrRecordPath->PVRDVBSubtitleServices[u8i].u16Composition_Page_id   = DVBSubtitleServices[u8i].u16Composition_Page_id;
            _pstPvrRecordPath->PVRDVBSubtitleServices[u8i].u8SubtitleType           = DVBSubtitleServices[u8i].u8SubtitleType;
        }
        _pstPvrRecordPath->u8EnableSubtitle    = stGenSetting.g_SysSetting.fEnableSubTitle;
        _pstPvrRecordPath->u8EnableTTXSubtitle = stGenSetting.g_SysSetting.fEnableTTXSubTitle;

        for (u8i =0; u8i < u8SubtitleMenuNum; u8i++)
        {
            if ((SubtitleMenu[u8i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT) || (SubtitleMenu[u8i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH))
            {
                msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, SubtitleMenu[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
            }
            memcpy( _pstPvrRecordPath->PVRSubtitleMenu[u8i].StringCodes, SubtitleMenu[u8i].StringCodes, 4);
            _pstPvrRecordPath->PVRSubtitleMenu[u8i].u16PID                      = SubtitleMenu[u8i].u16PID;
            _pstPvrRecordPath->PVRSubtitleMenu[u8i].u8Magazine                  = SubtitleMenu[u8i].u8Magazine;
            _pstPvrRecordPath->PVRSubtitleMenu[u8i].u8Page                      = SubtitleMenu[u8i].u8Page;
            _pstPvrRecordPath->PVRSubtitleMenu[u8i].u8SubtitleType              = SubtitleMenu[u8i].u8SubtitleType;
        }

#endif
        #if BRAZIL_PVR_CC
        {
            U16 u16CCPid =MApp_SI_Get_CC_PID();
            MApp_PVR_Playback_SetCCPID(u16CCPid);
            if (u16CCPid != MSAPI_DMX_INVALID_PID)
            {
                if(E_PVR_API_STATUS_OK != msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, u16CCPid, MSAPI_DMX_FILTER_TYPE_SUBTITLE))     //<--from other AP:(05) CC
                {
                    printf("Rcdpath Add cc pid fail\n");
                }
            }
        }
        #endif

      //msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, MApp_Subitle_GetCurPID(),        MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
        //(TYPE3)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, PID_PAT,                         MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(06) PAT
        #ifdef PVR_8051
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, g_stSIInfo.stPmtMonInfo.wPmtPid, MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(07) PMT
        #else
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, MApp_SI_Get_PMT_PID(),           MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(07) PMT
        #endif
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, PID_CAT,                         MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(08) CAT
        //(TYPE4)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, PID_NIT,                         MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(09) NIT
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, PID_SDT_BAT,                     MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(10) SDT/BAT
        //(TYPE5)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, PID_EIT_CIT,                     MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(11) EIT/CIT
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath, PID_TDT_TOT,                     MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(12) TDT/TOT
        //((( )))~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        //msAPI_Player_ScalerReduceBW(TRUE);  // we don't ReduceBW here, because at this moment it is in the [pause] state. It's meaningless and not working to reduce BW here.
        #ifdef S3PLUS
        msAPI_Aeon_Disable();                           //<--bandwidth problem, S3P only
        #endif

        msAPI_PVR_RecordPathStart(_pstPvrRecordPath);
        u8RecordEnable = TRUE;
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        MAPP_CIPVR_PVRReTriggerURICopyProtect();
#endif
    }
    else
    {
        u8RecordEnable = FALSE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    /*XXXXXXXXX msAPI_Player_ScalerReduceBW(TRUE); move to before msAPI_PVR_RecordPathStart(); XXXXXXXXX*/


    /*[03]change state ================================================================*/
    if(u8RecordEnable)
    {
        _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_RUNNING;
        return TRUE;
    }
    else
    {
        _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
        return FALSE;
    }
}

/***************************************************************************************/
static BOOLEAN  MApp_TimeShift_RecordRoutine(void)
{
    /*[01]error condition =============================================================*/
    if (_enTimeShiftRecordState != E_TIMESHIFT_RECORD_STATE_RUNNING)
    {
        return TRUE;
    }
    //printf("MApp_TimeShift_RecordRoutine \n");

    /*[02-1]set pvr record path =======================================================*/
    if ((_enTimeShiftStatus=msAPI_PVR_RecordPathInput(_pstPvrRecordPath)) != E_PVR_API_STATUS_OK)
    {
        if(_enTimeShiftStatus == E_PVR_API_STATUS_RECORD_FILE_OVER_SIZE &&
            (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32  || msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT))
        {
            //do nothing
        }
        else if (_enTimeShiftStatus == E_PVR_API_STATUS_RECORD_BUFFER_ERROR)
        {
            MApp_TimeShift_Record_Reset();
        }
        else
        return FALSE;
    }

    if ((_enTimeShiftStatus=msAPI_PVR_RecordPathGatherStatistics(_pstPvrRecordPath)) != E_PVR_API_STATUS_OK)
    {
        if(_enTimeShiftStatus == E_PVR_API_STATUS_DISK_SPEED_SLOW)
        {
            //MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_LOW_DISK_SPEED);
            //_enTimeShiftStatus = E_PVR_API_STATUS_OK;  // need to modify Uipvr later
            return TRUE;
        }
        else
        return FALSE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/
    _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_RUNNING;

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN  MApp_TimeShift_RecordDisable(void)
{
    /*[01]error condition =============================================================*/
    if ((_enTimeShiftRecordState != E_TIMESHIFT_RECORD_STATE_OPEN   ) &&
        (_enTimeShiftRecordState != E_TIMESHIFT_RECORD_STATE_RUNNING)   )
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_RecordDisable\n");
    if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
        msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    {
    #ifdef PVR_8051
        MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_PROCESSING);
    #else
          MS_DEBUG_MSG(printf("Need to add ZUI here2!\n"));  //need to modify UI for Chakra
    #endif
    }
    /*[02-1]set pvr record path =======================================================*/
    if(_pstPvrPlaybackPath != NULL)
        _pstPvrPlaybackPath->bLinkRecord = FALSE;

    msAPI_PVR_RecordPathStop(_pstPvrRecordPath);

    /*[02-2]set audio/scaler/video ====================================================*/
    msAPI_Player_ScalerReduceBW(FALSE);
    #ifdef S3PLUS
    if(App_GetOSDCountrySetting()==OSD_COUNTRY_UK)
    {
        #if (MHEG5_ENABLE)
        msAPI_Aeon_ReInitial( BIN_ID_CODE_AEON_MHEG5 ); //<--bandwidth problem, S3P only
        #endif
    }
    #endif

    /*[03]change state ================================================================*/
    _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_STOP;

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN  MApp_TimeShift_RecordClose(void)
{
    /*[01]error condition =============================================================*/
    if (_enTimeShiftRecordState != E_TIMESHIFT_RECORD_STATE_STOP)
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_RecordClose \n");

    /*[02-1]set pvr record path =======================================================*/
    msAPI_PVR_RecordPathClose(_pstPvrRecordPath);

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_RECORD_STOP,EN_CC_PVR_OPERATING_MODE_RESERVED,NULL,0);
        MAPP_CIPVR_PVRReTriggerURICopyProtect();
        MAPP_CIPVR_SetMuteFlag(false,E_SCREEN_MUTE_BY_LIVE_PIN_EVENT);
#endif

    /*[02-2]set audio/scaler/video ====================================================*/
    /*[03]change state ================================================================*/
    if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
        msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    { // set E_TIMESHIFT_RECORD_STATE_DISABLE at UI_Monitor
        _pstPvrRecordPath->u32RecordedTime = msAPI_Timer_GetTime0();  //for save Delete time
    }
    else
    {
    _enTimeShiftRecordState = E_TIMESHIFT_RECORD_STATE_DISABLE;
    }

    return TRUE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////////// playback path /////////////////////////////////////////*/
/*###############################################################################################*/

#define DEBUG_TIMESHIFT_PLAYBACK(x) //x

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackJumpToTime(U32 u32TimeSec)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    U8 u8BumpEnd = FALSE;
  //  U16 u32JumpSec = 0;

    /*[01]error condition =============================================================*/
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }

    U32 u32RecordStartTime = MApp_TimeShift_GetRecordStartTimeSec();
    // U32 u32PlaybackTime = MApp_TimeShift_GetPlaybackTimeSec();
    U32 u32RecordEndTime = MApp_TimeShift_GetRecordEndTimeSec();


    #ifdef PVR_UTOPIA
    MApi_DMX_BypassFileInTimeStamp(TRUE);
    msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath); //CL:81713
    MApi_DMX_BypassFileInTimeStamp(FALSE);
    #endif

    if(u32TimeSec <= (u32RecordEndTime - u32RecordStartTime))
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,u32TimeSec*1000,E_JUMP_BUFFER_RESET);
        u8BumpEnd = FALSE;
    }
    else
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,(u32RecordEndTime - u32RecordStartTime)*1000,E_JUMP_BUFFER_RESET);
        u8BumpEnd = TRUE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    #ifndef S3PLUS
    //printf("audio stop; scaler freeze; video stop->reset; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();
#ifdef PVR_UTOPIA  //can't clear bitstream buffer, so, have to reset MVD
    msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
#else
    msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
#endif
    #else
    //printf("audio stop; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();

    msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif

    /*[03]change state ================================================================*/
    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_STOP;

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
static BOOLEAN MApp_TimeShift_PlaybackOpen(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););

    U8 u8PlaybackOpen = FALSE;

    /*[01]error condition =============================================================*/
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_DISABLE)
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_PlaybackOpen \n");

    /*[02-1]set pvr playback path =====================================================*/
    _pstPvrPlaybackPath = msAPI_PVR_PlaybackPathOpen(_pu16TimeShiftFileName);

    if(_pstPvrPlaybackPath)
    {
        _pstPvrPlaybackPath->bLinkRecord = TRUE;    //<---(R-P-1)establish record linkage (timeshift always link)

        u8PlaybackOpen = TRUE;
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        printf("............MApp_TimeShift_PlaybackOpen.....%d......\n",_pstPvrPlaybackPath->pstPvrRecordPath->u8CicamCheckLevel);
        switch(_pstPvrRecordPath->u8CicamCheckLevel)
        {
            case EN_CI_VERSION_CI_PLUS:
            {
                MAPP_CIPVR_CIPVRFS_PlaybackFileRead();
                enPvrApiStatus enPvrStatus = MAPP_CIPVR_CIPlusPVRHandling(PVR_PATH_PLAYBACK,true,0xFFFF);
                if((E_PVR_API_STATUS_OK != enPvrStatus))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;
                    _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
                    _enTimeShiftStatus = enPvrStatus;
                    msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
                    return FALSE;
                }

                U8 u8aCICAMID[CC_AUTH_ID_SIZE] = { 0 };
                if(FALSE == msAPI_CI_CC_GetCICAMID(u8aCICAMID))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;
                    _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
                    _enTimeShiftStatus = E_PVR_API_STATUS_ERROR_RETENTION_LIMIT_EXPIRED;
                    msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
                    return FALSE;
                }
                else if(FALSE == MAPP_CIPVR_PlaybackCiSecuredPatternCheck(u8aCICAMID))
                {
                     printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;
                    _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
                    _enTimeShiftStatus = E_PVR_API_STATUS_ERROR_RETENTION_LIMIT_EXPIRED;
                    msAPI_PVR_PlaybackPathClose(_pstPvrPlaybackPath);
                    return FALSE;
                }
                else
                {
                    U32 u32JumpTime = 0;
                    BOOL bRetentionLimitExpire = MAPP_CIPVR_RetentionLimitMonitor(0, &u32JumpTime);
                    //u8PlaybackEnable = TRUE;
                    if((TRUE == bRetentionLimitExpire) && (MApp_TimeShift_GetRecordEndTimeSec() <= u32JumpTime))
                    {
                        printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;
                        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
                        _enTimeShiftStatus = E_PVR_API_STATUS_ERROR_RETENTION_LIMIT_EXPIRED;
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
        u8PlaybackOpen = FALSE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    msAPI_Player_ScalerReduceBW(TRUE);


    /*[03]change state ================================================================*/
    if(u8PlaybackOpen)
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_OPEN;
        return TRUE;
    }
    else
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;
        return FALSE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackEnable(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    U8 u8PlaybackEnable = FALSE;

    /*[01]error condition =============================================================*/
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_OPEN)
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_PlaybackEnable \n");

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

    if ((_enTimeShiftStatus=msAPI_PVR_PlaybackPathSet(_pstPvrPlaybackPath)) == E_PVR_API_STATUS_OK)
    {
        //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        #ifdef PVR_8051
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

        //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #ifndef S3PLUS
        msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, g_u16Current_PCRPID,             MSAPI_DMX_FILTER_TYPE_PCR);          //<--from other AP:(01) PCR
        U8 u8FID;
        for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
        {
            if (_pstPvrPlaybackPath->pstPvrRecordPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_SUBTITLE)  //SUBTITLE_FID
            {
                #if BRAZIL_PVR_CC
                MApp_PVR_Playback_SetCCPID(_pstPvrPlaybackPath->pstPvrRecordPath->u16PID[u8FID]);
                #endif
            }
        }
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
            if (_pstPvrPlaybackPath->pstPvrRecordPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_SUBTITLE)  //SUBTITLE_FID
            {
                #if BRAZIL_PVR_CC
                MApp_PVR_Playback_SetCCPID(_pstPvrPlaybackPath->pstPvrRecordPath->u16PID[u8FID]);
                #endif
            }
        }
        if(gAvSync_PcrFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            //printf("Invalid gAvSync_PcrFid\n");
        }
    }
    #endif
        msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, g_u16Current_PVR_VideoPID,       MSAPI_DMX_FILTER_TYPE_VIDEO);        //<--from other AP:(02) VIDEO
        //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, g_u16Current_PVR_AudioPID,       MSAPI_DMX_FILTER_TYPE_AUDIO);        //<--from other AP:(03) AUDIO
        #ifndef S3PLUS
        //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, g_u16Current_AudioDescriptorPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);       //<--from other AP:(04) AUDIO DESCRIPTOR
        #endif
        //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, MApp_Subitle_GetCurPID(),        MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
        #if (ENABLE_SUBTITLE)
        MApp_Subtitle_Open_Filter(MApp_Subitle_GetCurPID());
        #endif

        #ifndef PVR_UTOPIA
        msAPI_DMX_RestoreDataPath();
        #endif
        //(TYPE3)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, PID_PAT,                         MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(06) PAT
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, g_stSIInfo.stPmtMonInfo.wPmtPid, MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(07) PMT
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, PID_CAT,                         MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(08) CAT
        //(TYPE4)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, PID_NIT,                         MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(09) NIT
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, PID_SDT_BAT,                     MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(10) SDT/BAT
        //(TYPE5)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, PID_EIT_CIT,                     MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(11) EIT/CIT
      //msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, PID_TDT_TOT,                     MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(12) TDT/TOT
        //((( )))~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        //link record-playback at start up ============================================//
        _pstPvrPlaybackPath->u32FileValidPosStrKB   = _pstPvrRecordPath->u32FileValidPosStrKB;

        _pstPvrPlaybackPath->enVideoType    = _pstPvrRecordPath->enVideoType;
        _pstPvrPlaybackPath->enAudioType    = _pstPvrRecordPath->enAudioType;
        _pstPvrPlaybackPath->enAdAudioType  = _pstPvrRecordPath->enAdAudioType;
        //link record-playback at start up ============================================//

        msAPI_PVR_PlaybackPathStart(_pstPvrPlaybackPath);
        u8PlaybackEnable = TRUE;
    }
    else
    {
        u8PlaybackEnable = FALSE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio stop->init; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();

#if( ENABLE_DVB_AUDIO_DESC )
    msAPI_Player_AudioInit(_pstPvrPlaybackPath->enAudioType,  E_PLAY_SOURCE_FILE, stGenSetting.g_SoundSetting.bEnableAD, _pstPvrPlaybackPath->enAdAudioType);
#else
    msAPI_Player_AudioInit(_pstPvrPlaybackPath->enAudioType,  E_PLAY_SOURCE_FILE, FALSE, E_PLAY_AUDIO_TYPE_INVALID);
#endif

    msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);

    /*[03]change state ================================================================*/
    if(u8PlaybackEnable)
    {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_MODE_CHANGE,EN_CC_PVR_OPERATING_MODE_TIMESHIFT,NULL,0);
        MAPP_CIPVR_PVRReTriggerURICopyProtect();
#endif
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_OPEN;    //no change
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
    else
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
        return FALSE;
    }
}

/***************************************************************************************/
static BOOLEAN  MApp_TimeShift_PlayabackRoutine(void)
{
    //DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    /*[01]error condition =============================================================*/
    if(_bTimeshiftStepIn)
    {
        if(!_bTimeshiftStepInTrigger)
        {
            _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_PAUSE;
        }
        else
        {
            if(MApi_VDEC_IsStepDispDone())
            {
                MApi_VDEC_StepDisp();
                _bTimeshiftStepInTrigger =FALSE;
                _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_PAUSE;
            }
            else
            {
                _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_RUNNING;
            }
        }
    }

    if ((_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_RUNNING    ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD))
    {
        return TRUE;
    }
    //printf("MApp_TimeShift_PlayabackRoutine \n");

    /*[02-1]set pvr playback path =====================================================*/
    /*[02-1a]link record-playback =====================================================*/
    if(_pstPvrPlaybackPath->bLinkRecord)
    {
        _pstPvrPlaybackPath->u32FileLimitedSizeKB   = _pstPvrRecordPath->u32FileLimitedSizeKB;
        _pstPvrPlaybackPath->u32FileValidPosStrKB   = _pstPvrRecordPath->u32FileValidPosStrKB;
        _pstPvrPlaybackPath->u32FileValidPosEndKB   = _pstPvrRecordPath->u32FileValidPosEndKB;

    }
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
    U32 u32JumpTargetTime = 0;
    if(0)//(MAPP_CIPVR_RetentionLimitMonitor(MApp_Playback_GetPlaybackTimeSec(), &u32JumpTargetTime))
    {
        MApp_TimeShift_PlaybackJumpToTime(u32JumpTargetTime);
    }
#endif
    /*[02-1b]playback path output routine =============================================*/
    /*[##-1]Fast Backward =============================================================*/
    if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD)
    {
        // U32 playTime = MApp_TimeShift_GetPlaybackTimeSec();
        // U32 recstartTime = MApp_TimeShift_GetRecordStartTimeSec();
        U16 u16JumpSec = 0;

        switch(_enTimeShiftPlaybackSpeed)
        {
            case E_PLAY_SPEED_1X:
                break;
            case E_PLAY_SPEED_2X:
                u16JumpSec = 1;
                break;
            case E_PLAY_SPEED_4X:
                u16JumpSec = 2;
                break;
            case E_PLAY_SPEED_8X:
                u16JumpSec = 4;
                break;
            case E_PLAY_SPEED_16X:
                u16JumpSec = 8;
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


            if(u32TimeshiftTempTimeCounter/90 > msAPI_Timer_DiffTimeFromNow(u32TimeshiftStartSysTime) * u16JumpSec)
            {
                msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,(u32TimeshiftTempTimeCounter/90 - msAPI_Timer_DiffTimeFromNow(u32TimeshiftStartSysTime) * u16JumpSec), E_JUMP_BUFFER_CONTINUOUS);
            }
            else
            {
                msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath,0, E_JUMP_BUFFER_CONTINUOUS);
            }
        }

        if((_enTimeShiftStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
        {
            return FALSE;
        }

    }

    /*[##-2]Fast Forward ==============================================================*/
    else if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD)
    {
        U32 playTime = MApp_TimeShift_GetPlaybackTimeSec();
        U32 starTime = MApp_TimeShift_GetRecordStartTimeSec();
        U32 endTime = MApp_TimeShift_GetRecordEndTimeSec();

        if(_enTimeShiftPlaybackSpeed != E_PLAY_SPEED_2X)
        {
            if(MApi_VDEC_IsStepDispDone())
            {
                MApi_DMX_BypassFileInTimeStamp(TRUE);
                msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                MApi_DMX_BypassFileInTimeStamp(FALSE);
                MApi_VDEC_StepDisp();

                if(_enTimeShiftPlaybackSpeed > E_PLAY_SPEED_2X)
                {
                    U16 u16JumpSec = 0;

                    switch(_enTimeShiftPlaybackSpeed)
                    {/*
                        case E_PLAY_SPEED_1X:
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

                    if(playTime<(endTime - starTime))
                    {
                        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, (u32TimeshiftTempTimeCounter/90 + msAPI_Timer_DiffTimeFromNow(u32TimeshiftStartSysTime) * u16JumpSec ), E_JUMP_BUFFER_CONTINUOUS);
                    }
                 }
            }
        }
        else
        {
            MApi_DMX_Pvr_SetPlaybackStamp((u32TimeshiftTempTimeCounter/90 + msAPI_Timer_DiffTimeFromNow(u32TimeshiftStartSysTime) * _enTimeShiftPlaybackSpeed )*90);
        }

        if((_enTimeShiftStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
        {
            return FALSE;
        }
    }
    else if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD)
    {
        MApi_DMX_Pvr_SetPlaybackStamp((u32TimeshiftTempTimeCounter/90 + msAPI_Timer_DiffTimeFromNow(u32TimeshiftStartSysTime) / _enTimeShiftPlaybackSpeed )*90);
        if((_enTimeShiftStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
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
        //MApp_AVSync_ForceSync();
        #endif
        #endif

        msAPI_Player_VideoMonitor(FALSE); // Get GOP size info.
        if ((_enTimeShiftStatus=msAPI_PVR_PlaybackPathForwardOutput(_pstPvrPlaybackPath)) != E_PVR_API_STATUS_OK)
        {
            return FALSE;
        }
    }

    /*[03]change state ================================================================*/
    if((_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD) &&
       (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD) &&
       (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD))
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_RUNNING;
    }
    return TRUE;
}


/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackStepIn(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    if(!_bTimeshiftStepIn)
    {
        _bTimeshiftStepIn = TRUE;
        msAPI_Player_ScalerWaitFree(10);
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
        msAPI_Player_VideoConfigForwardSpeed(_enTimeShiftPlaybackSpeed);
        msAPI_Player_VideoPause();
        MApi_VDEC_StepDisp();
        msAPI_PVR_PlaybackPathStepIn(_pstPvrPlaybackPath);
        _bTimeshiftStepInTrigger =FALSE;
    }
    else
    {
        _bTimeshiftStepInTrigger =TRUE;
    }

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackJumpForward(U32 u32JumpSec)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    U8 u8BumpEnd;
    U16 u16TimeDiffSec;

    /*[01]error condition =============================================================*/
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_PlaybackJumpForward \n");

    /*[02-1]set pvr playback path =====================================================*/
    /*[02-1a]jump forward =============================================================*/
    u16TimeDiffSec = MApp_TimeShift_GetRecordEndTimeSec() - MApp_TimeShift_GetPlaybackTimeSec() - MApp_TimeShift_GetRecordStartTimeSec();
    if(u16TimeDiffSec >= u32JumpSec)
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, (MApp_TimeShift_GetPlaybackTimeSec()+u32JumpSec)*1000,E_JUMP_BUFFER_RESET);
        u8BumpEnd = FALSE;
    }
    else
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, (MApp_TimeShift_GetRecordEndTimeSec() - MApp_TimeShift_GetRecordStartTimeSec())*1000,  E_JUMP_BUFFER_RESET);
        u8BumpEnd = TRUE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    #ifndef S3PLUS
    //printf("audio stop; scaler freeze; video stop->reset; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();
#ifdef PVR_UTOPIA  //can't clear bitstream buffer, so, have to reset MVD
    msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
#else
    msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
#endif
    #else
    //printf("audio stop; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();

    msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif

    /*[03]change state ================================================================*/
    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_STOP;

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
static BOOLEAN MApp_TimeShift_PlaybackJumpBackward(U32 u32JumpSec)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    U16 u16TimeDiffSec;

    /*[01]error condition =============================================================*/
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_PlaybackJumpBackward \n");

    /*[02-1]set pvr playback path =====================================================*/
    /*[02-1a]jump backward ============================================================*/
    u16TimeDiffSec = MApp_TimeShift_GetPlaybackTimeSec() ;
    if(u16TimeDiffSec >= u32JumpSec)
    {
        msAPI_PVR_PlaybackPathJumpForward(_pstPvrPlaybackPath, (MApp_TimeShift_GetPlaybackTimeSec()- u32JumpSec)*1000,E_JUMP_BUFFER_RESET);
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
    msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
#else
    msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
#endif
    #else
    //printf("audio stop; scaler freeze; video stop->init; \n");
    msAPI_Player_AudioStop();
    msAPI_Player_ScalerFreeze();
    msAPI_Player_VideoStop();

    msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif

    /*[03]change state ================================================================*/
    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_STOP;

    return TRUE;
}

/***************************************************************************************/
static enTimeShiftPlaybackState enPrevPlayDirection = E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD;
/***************************************************************************************/
static BOOLEAN MApp_TimeShift_Playback_SlowForward(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    /*[01]error condition =============================================================*/
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }

    /*[02-1]set pvr playback path =====================================================*/
    msAPI_PVR_PlaybackPathSlowForward(_pstPvrPlaybackPath);

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio nop; scaler waitfree; video ffspeed; \n");
    if((enPrevPlayDirection == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD)||
        (enPrevPlayDirection == E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD))
    {
      //printf("reverse backward->forward\n");
        enPrevPlayDirection = E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD;
        _enTimeShiftPlaybackSpeed    = E_PLAY_SPEED_1X;
    }

    if(_enTimeShiftPlaybackSpeed < E_PLAY_SPEED_32X)
    {
        U8 u8TimeShiftPlaybackSpeed = (U8)_enTimeShiftPlaybackSpeed;
        _enTimeShiftPlaybackSpeed = (enPlaySpeed)(u8TimeShiftPlaybackSpeed << 1);
    }
    else
    {
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_2X;
    }

#ifdef S3PLUS
    _pstPvrPlaybackPath->enPlaySpeed = _enTimeShiftPlaybackSpeed;
#endif

#ifdef S3PLUS  // I am not sure if need enable in other platform
    msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);  //for clean afifo
    //MUTE_On();  don't  use this mute ....it's H/W mute ....
#endif
    msAPI_Player_VideoConfigSlowForwardSpeed(_enTimeShiftPlaybackSpeed);
    msAPI_Player_ScalerWaitFree(10);

    /*[03]change state ================================================================*/
    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD;

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackFastForward(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););

    /*[01]error condition =============================================================*/
#if (INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE)
    enPlaySpeed prePlaySpeed = _enTimeShiftPlaybackSpeed;
#else
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
#endif
    //printf("MApp_TimeShift_PlaybackFastForward \n");


    /*[02-1]set pvr playback path =====================================================*/
    msAPI_PVR_PlaybackPathFastForward(_pstPvrPlaybackPath);

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio nop; scaler waitfree; video ffspeed; \n");
    if((enPrevPlayDirection == E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD) ||
        (enPrevPlayDirection == E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD))
    {
        //printf("reverse backward->forward\n");
        enPrevPlayDirection       = E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD;
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
    }

    if(_enTimeShiftPlaybackSpeed < E_PLAY_SPEED_16X)
    {
        U8 u8TimeShiftPlaybackSpeed = (U8)_enTimeShiftPlaybackSpeed;
        _enTimeShiftPlaybackSpeed = (enPlaySpeed)(u8TimeShiftPlaybackSpeed << 1);
    }
    else
    {
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_2X;
    }

    DEBUG_TIMESHIFT_PLAYBACK( printf("_enTimeShiftPlaybackSpeed=%u\n", _enTimeShiftPlaybackSpeed); );
    if(_enTimeShiftPlaybackSpeed == E_PLAY_SPEED_2X)
    {
        /* Need Do (AVFifoClean + VDEC_Flush) : FB/FF->FFx2 */
        msAPI_PVR_PlaybackPathWaitAVFifoClean();
        MApi_DMX_BypassFileInTimeStamp(TRUE);
        msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
        MApi_DMX_BypassFileInTimeStamp(FALSE);

        MApi_VDEC_Play();
    }
    else
    {
        //printf("MApi_VDEC_StepDisp()\n");

#if (INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE)
        if( (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD && prePlaySpeed == E_PLAY_SPEED_2X) ||
            (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD && _enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD)
            )
#endif
        {
            MApi_VDEC_StepDisp();
        }
    }


#if 0//def S3PLUS
    _pstPvrPlaybackPath->enPlaySpeed = _enTimeShiftPlaybackSpeed;
#endif

#if 0//def S3PLUS // I am not sure if need enable in other platform
    msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);  //for clean afifo
#endif

    msAPI_Player_VideoConfigForwardSpeed(_enTimeShiftPlaybackSpeed);
    msAPI_Player_ScalerWaitFree(10);

    /*[03]change state ================================================================*/
    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD;

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackFastBackward(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    /*[01]error condition =============================================================*/
#if (!INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE)
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_PAUSE)
    {
        return FALSE;
    }
#endif
    //printf("MApp_TimeShift_PlaybackFastBackward \n");
    /***************************/
    //printf("MApi_VDEC_StepDisp()\n");
#if (INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE)
    if( (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD && _enTimeShiftPlaybackSpeed == E_PLAY_SPEED_2X) ||
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD && _enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD)
        )
#endif
    {
        MApi_VDEC_StepDisp();
    }
    /***************************/

    /*[02-1]set pvr playback path =====================================================*/
    msAPI_PVR_PlaybackPathFastBackward(_pstPvrPlaybackPath);

    /*[02-2]set audio/scaler/video ====================================================*/
    //printf("audio nop; scaler waitfree; video fbspeed; \n");
    if((enPrevPlayDirection == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD)||
        (enPrevPlayDirection == E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD))
    {
        //printf("reverse forward->backward\n");
        enPrevPlayDirection       = E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD;
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
    }

    if(_enTimeShiftPlaybackSpeed < E_PLAY_SPEED_16X)
    {
        U8 u8TimeShiftPlaybackSpeed = (U8)_enTimeShiftPlaybackSpeed;
        _enTimeShiftPlaybackSpeed = (enPlaySpeed)(u8TimeShiftPlaybackSpeed << 1);
    }
    else
    {
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_2X;
    }

    msAPI_Player_VideoConfigBackwardSpeed(_enTimeShiftPlaybackSpeed);
    msAPI_Player_ScalerWaitFree(10);

  #if 0//def S3PLUS
    msAPI_Aeon_ReInitial( BIN_ID_CODE_AEON_TSSEARCH );
    msAPI_DMX_EnableReserveFlt(FALSE);
    msAPI_Player_AeonPatternSearchInit();
  #endif

    /*[03]change state ================================================================*/
    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD;

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackPause(enTimeShiftPlaybackActionAfterPause eNextAct)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    U8 u8PlaybackEnable = FALSE;

    /*[01]error condition =============================================================*/
    if ((_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_DISABLE     ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_OPEN        ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_RUNNING     ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD))
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_PlaybackPause \n");

    /*[02-1]set pvr playback path =====================================================*/
    if((_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_DISABLE) ||
       (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_OPEN   )   )   //live in
    {
        u8PlaybackEnable = FALSE;
    }
    else if (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD)
    {
        msAPI_PVR_PlaybackPathPause(_pstPvrPlaybackPath);

        u8PlaybackEnable = TRUE;
    }
    else if (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD)
    {
        msAPI_PVR_PlaybackPathPause(_pstPvrPlaybackPath);

        u8PlaybackEnable = TRUE;
    }
    else // E_TIMESHIFT_PLAYBACK_STATE_RUNNING            //file in
    {
        msAPI_PVR_PlaybackPathPause(_pstPvrPlaybackPath);

        u8PlaybackEnable = TRUE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_DISABLE)  //live in
    {
        //printf("audio stop; scaler freeze; video stop->reset; \n");
        msAPI_Player_AudioStop();
        msAPI_Player_ScalerFreeze();
        msAPI_Player_VideoStop();
    #ifndef S3PLUS
        #ifdef PVR_UTOPIA_T3
        #else
        msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
        #endif
    #else
        msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    #endif

        fEnableMvdTimingMonitor = FALSE;
        //printf("[[[fEnableMvdTimingMonitor = FALSE;]]]\n");
    }
    else if(((_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD)||
            (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD))&&
            ((eNextAct == E_TIMESHIFT_PLAYBACK_NEXTACT_RESUME) ||
             (eNextAct == E_TIMESHIFT_PLAYBACK_NEXTACT_NONE  )                  )   )
    {
        //printf("audio nop; scaler freeze->mute; video stop->reset->init; \n");
        msAPI_Player_ScalerFreeze();
    #ifndef PVR_UTOPIA  //ther video cant' return after Mute, we need scaler to check this issue to improve the video quality
        msAPI_Player_ScalerMute(50);
    #endif
        msAPI_Player_VideoStop();
    #ifndef PVR_UTOPIA  //diffenent funciton in utopia
        msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
    #endif
        msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);
    }
    else if(((_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD)||
            (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD))&&
            ((eNextAct == E_TIMESHIFT_PLAYBACK_NEXTACT_RESUME) ||
             (eNextAct == E_TIMESHIFT_PLAYBACK_NEXTACT_NONE  )                   )   )
    {
        //printf("audio nop; scaler freeze->mute; video stop->reset->init; \n");
        msAPI_Player_ScalerFreeze();
    #ifndef PVR_UTOPIA  //ther video cant' return after Mute, we need scaler to check this issue to improve the video quality
        msAPI_Player_ScalerMute(50);
    #endif
        msAPI_Player_VideoStop();
    #ifndef PVR_UTOPIA  //diffenent funciton in utopia
        msAPI_Player_VideoReset(E_PLAY_SOURCE_FILE);
    #endif
        msAPI_TimeShift_VideoInit(_pstPvrPlaybackPath->enVideoType,  E_PLAY_SOURCE_FILE);

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

#if (BRAZIL_CC)
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
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_PAUSE;
        return TRUE;
    }
    else
    {
        //_enTimeShiftPlaybackState = _enTimeShiftPlaybackState;        //no change
        return TRUE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackResume(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););
    /*[01]error condition =============================================================*/
    if ((_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_DISABLE     ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_OPEN        ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_PAUSE       ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD ) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_SLOWFORWARD) &&
        (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_STOP        )   )
    {
        return FALSE;
    }
    //printf("MApp_TimeShift_PlaybackResume \n");
#ifdef S3PLUS
    _pstPvrPlaybackPath->enPlaySpeed = E_PLAY_SPEED_1X;
#endif

    /*[02-1]set pvr playback path =====================================================*/
    if((_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_DISABLE) ||
       (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_OPEN)      )    //live in
    {
        //%%%no-such-case, remove if necessary%%%//
    }
    else // E_TIMESHIFT_PLAYBACK_STATE_PAUSE || E_TIMESHIFT_PLAYBACK_STATE_STOP //file in
    {
        msAPI_PVR_PlaybackPathResume(_pstPvrPlaybackPath);
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    if((_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_DISABLE) ||
       (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_OPEN)    ||
       (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_STOP)      )    //live in
    {
        //printf("audio play; scaler waitfree; video play; \n");
        msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);
        msAPI_Player_ScalerWaitFree(50);
        msAPI_Player_ScalerMute(50);
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        msAPI_Player_VideoEncoderReset();
        msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);

        fEnableMvdTimingMonitor = TRUE;
        g_bSetModeDone = TRUE;
      //printf("[[[fEnableMvdTimingMonitor = TRUE;]]]\n");
    }
    else
    {
        //printf("audio stop->play; scaler waitfree; video monitor->resume; \n");
        msAPI_Player_AudioStop();
        msAPI_Player_AudioPlay(E_PLAY_SOURCE_FILE);
        #ifndef S3PLUS
        msAPI_Player_ScalerWaitFree(10);
        #else
        msAPI_Player_ScalerWaitFree(50);
        #endif
        msAPI_Player_VideoEncoderReset();
        msAPI_Player_VideoMonitor(TRUE); // Reset GOP size info
    #ifdef PVR_UTOPIA
        #ifdef PVR_UTOPIA_T3
        msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
        #else
        _enPlaybackSpeed = E_PLAY_SPEED_1X;
        msAPI_Player_VideoConfigForwardSpeed(_enPlaybackSpeed);
        #endif
    #else
        msAPI_Player_VideoResume();
    #endif

        fEnableMvdTimingMonitor = TRUE;
        g_bSetModeDone = TRUE;
      //printf("[[[fEnableMvdTimingMonitor = TRUE;]]]\n");
    }
    //start CC
#if (BRAZIL_CC)
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
    if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_DISABLE)
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;    //no change
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
    else
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_RUNNING;
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackDisable(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););

    U8 u8PlaybackEnable = FALSE;

    /*[01]error condition =============================================================*/
  //printf("MApp_TimeShift_PlaybackDisable \n");

    /*[02-1]set pvr playback path =====================================================*/
    if (_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_DISABLE)
    {
        u8PlaybackEnable = FALSE;
    }
    else
    {
        msAPI_PVR_PlaybackPathStop(_pstPvrPlaybackPath);

        u8PlaybackEnable = TRUE;
    }

#ifdef PVR_UTOPIA
  #if ENABLE_CI
    if (msAPI_CI_CardDetect())
    {
       // msAPI_Tuner_Serial_Control(TRUE,FALSE);
    }
    else
  #endif
    {
        //msAPI_Tuner_Serial_Control(FALSE,FALSE);
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);
    }
#endif

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
    msAPI_DMX_StartFilter( g_u16Current_AudioDescriptorPID, MSAPI_DMX_FILTER_TYPE_AUDIO2, MApp_Dmx_GetFid(EN_AD_FID));
    #endif
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
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    msAPI_Player_VideoRestore();
    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
#if (BRAZIL_CC)
    if(*MApp_Dmx_GetFid(EN_PES_FID) != MSAPI_DMX_INVALID_FLT_ID)
    {
        if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE)== STATE_CAPTION_PARSER)
        {
            MApp_CC_StopParser();
        }
        MApp_Dmx_PES_Stop();
    }
#endif
    /*[03]change state ================================================================*/
    if(u8PlaybackEnable)
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_STOP;
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
    else
    {
        _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;    //no change
        _enTimeShiftPlaybackSpeed = E_PLAY_SPEED_1X;
        return TRUE;
    }
}

/***************************************************************************************/
static BOOLEAN MApp_TimeShift_PlaybackClose(void)
{
    DEBUG_TIMESHIFT_PLAYBACK(PRINT_CURRENT_LINE(););

    /*[01]error condition =============================================================*/
    if (_enTimeShiftPlaybackState != E_TIMESHIFT_PLAYBACK_STATE_STOP)
    {
        return FALSE;
    }
  //printf("MApp_TimeShift_PlaybackClose \n");

    /*[02-1]set pvr playback path =====================================================*/
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
#endif

    /*[03]change state ================================================================*/
    _enTimeShiftPlaybackState = E_TIMESHIFT_PLAYBACK_STATE_DISABLE;

    return TRUE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////// timeshift ap (time-bar-related) /////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U32 MApp_TimeShift_GetRecordStartTimeSec(void)
{
    U32 u32StartTime;

    /*[01]error condition =============================================================*/
    if ((_enTimeShiftState != E_TIMESHIFT_STATE_RECORDING            ) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING          )   )
    {
        return 0;
    }
  //printf("MApp_TimeShift_GetRecordStartTimeSec \n");

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
U32 MApp_TimeShift_GetRecordEndTimeSec(void)
{
    U32 u32EndTime;

    /*[01]error condition =============================================================*/
    if ((_enTimeShiftState != E_TIMESHIFT_STATE_RECORDING            ) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING          )   )
    {
        return 0;
    }
  //printf("MApp_TimeShift_GetRecordEndTimeSec \n");

    /*[02-1]set pvr record path =======================================================*/
    u32EndTime = _pstPvrRecordPath->u32RecordedTime/1000 +        //in 1/1000 SECOND
                 _pstPvrRecordPath->u32RecordedPeriod/10 -        //in 1/10   SECOND
                 _pstPvrRecordPath->u32PausedPeriod/10;           //in 1/10   SECOND

    return u32EndTime;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/
U32 MApp_TimeShift_GetRecordValidPeriodSec(void)
{
    U32 u32ValidPeriod = 0;

    /*[01]error condition =============================================================*/
    if ((_enTimeShiftState != E_TIMESHIFT_STATE_RECORDING            ) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING          )   )
    {
        return 0;
    }
  //printf("MApp_TimeShift_GetRecordValidPeriodSec \n");

    /*[02-1]set pvr record path =======================================================*/
    u32ValidPeriod = _pstPvrRecordPath->u32FileValidPeriod/10;

    return u32ValidPeriod;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/
U32 MApp_TimeShift_GetPlaybackTimeSec(void)
{
    U32 u32PlayTime;
    U32 u32TimeStamp;

    /*[01]error condition =============================================================*/
    // if ((_enTimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
    //     (_enTimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING          )   )
    // {
    //     return _pstPvrRecordPath->u32RecordedTime/1000;     //the beginning
    // }
    // else
    {
        MApi_DMX_GetFileInTimeStamp(&u32TimeStamp);

        if((MApp_TimeShift_GetRecordValidPeriodSec()>1)&&((u32TimeStamp>(MApp_TimeShift_GetRecordValidPeriodSec()-1)*90*1000)&&(u32TimeStamp<MApp_TimeShift_GetRecordValidPeriodSec()*90*1000)))
        {
            u32TimeStamp =MApp_TimeShift_GetRecordValidPeriodSec()*90*1000;
        }
        //1?ë???ó²î

        u32PlayTime = u32TimeStamp/90/1000;  //SECOND
    }

    // avoid play time get error
    if (u32PlayTime > u32OriginPlayTime+50)
    {
        u32PlayTime  = u32OriginPlayTime;
    }
    else
    {
        if (u32PlayTime != 0)
        {
            u32OriginPlayTime = u32PlayTime;
        }
    }

    return u32PlayTime;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/
enPlaySpeed MApp_TimeShift_GetPlaybackSpeed(void)
{
    /*[01]error condition =============================================================*/
    if ((_enTimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING          )   )
    {
        return E_PLAY_SPEED_1X;
    }
  //printf("MApp_TimeShift_GetPlaybackSpeed \n");

    /*[02-1]set pvr record path =======================================================*/
    return _enTimeShiftPlaybackSpeed;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}


/*###############################################################################################*/
/*////////////////////////////// timeshift ap (link to audio) ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U8 MApp_TimeShift_AudioGetLanguageSelection(void)
{
    return _pstPvrRecordPath->u8audioLangSel;
}

/***************************************************************************************/
U8 MApp_TimeShift_AudioGetLanguageTotal(void)
{
    return _pstPvrRecordPath->u8audioLangTotal;
}

/***************************************************************************************/
BYTE MApp_TimeShift_AudioGetLanguageInfo(void)
{
    return  _pstPvrRecordPath->PVRAudioInfo[g_u8AudLangSelected].aISOLangInfo[0].bISOLanguageInfo;
}

/***************************************************************************************/
BOOLEAN MApp_TimeShift_AudioGetStreamInfo(AUD_INFO* pstAudioStreamInfo, U8 u8Idx)
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
void MApp_TimeShift_SetAudioLanguage(void)
{
    // Set Audio Track
    g_u8AudLangSelected = MApp_TimeShift_AudioGetLanguageSelection();
    MApp_TimeShift_AudioStopLanguage(g_u8AudLangSelected);
    MApp_TimeShift_AudioSelectLanguage(g_u8AudLangSelected);

    // Set AD Audio
    if (stGenSetting.g_SoundSetting.bEnableAD)
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

        if (0xFF != g_u8AdAudSelected)
        {
            MApp_Audio_SetAdAudio(g_u8AdAudSelected);
        }
    }
}

/***************************************************************************************/
void MApp_TimeShift_AudioSelectLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
}

/***************************************************************************************/
void MApp_TimeShift_AudioStopLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
}

/***************************************************************************************/
#ifndef S3PLUS
void MApp_TimeShift_AdAudioSelectLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathAddPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);
}

/***************************************************************************************/
void MApp_TimeShift_AdAudioStopLanguage(U8 u8AudSelectedIndex)
{
    msAPI_PVR_PlaybackPathDelPID(_pstPvrPlaybackPath, _pstPvrRecordPath->PVRAudioInfo[u8AudSelectedIndex].wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);
}
#endif
/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////// playback ap (link to subtitle) //////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void MApp_TimeShift_Subtitle_LoadServices(U8* pu8SelIdx, U8* pu8Num, DVB_SUBTITLE_SERVICE* options)
{
    *pu8Num    = _pstPvrRecordPath->u8DVBSubtitleServiceNum;
    *pu8SelIdx = _pstPvrRecordPath->u8SubtitleMenuSelectedIdx;
    memcpy(options, _pstPvrRecordPath->PVRDVBSubtitleServices, sizeof(_pstPvrRecordPath->PVRDVBSubtitleServices));
}

/***************************************************************************************/
void MApp_TimeShift_Subtitle_LoadMenu(U8* pu8SelIdx, U8* pu8Num, SUBTITLE_MENU* options, U8* pu8fEnableSubtitle, U8* pu8fEnableTTXSubtitle)
{
    *pu8Num    = _pstPvrRecordPath->u8SubtitleMenuNum;
    *pu8SelIdx = _pstPvrRecordPath->u8SubtitleMenuSelectedIdx;
    memcpy(options, _pstPvrRecordPath->PVRSubtitleMenu, sizeof(_pstPvrRecordPath->PVRSubtitleMenu));
    *pu8fEnableSubtitle    = _pstPvrRecordPath->u8EnableSubtitle;
    *pu8fEnableTTXSubtitle = _pstPvrRecordPath->u8EnableTTXSubtitle;
}

/***************************************************************************************/
void MApp_TimeShift_TTXSubtitle_GetNum(U8* pu8Num)
{
    *pu8Num =_pstPvrRecordPath->u8TTXSubtitleServiceNum;
}

/*###############################################################################################*/
/*//////////////////////////////////////// ui related ///////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
BOOLEAN MApp_TimeShift_IfPause(void)
{
    if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_PAUSE   ||
       _enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_DISABLE ||
       _enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_OPEN      )
    {
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/
BOOLEAN MApp_TimeShift_IfFastForward(void)
{
    if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTFORWARD)
    {
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/
BOOLEAN MApp_TimeShift_IfFastBackward(void)
{
    if(_enTimeShiftPlaybackState == E_TIMESHIFT_PLAYBACK_STATE_FASTBACKWARD)
    {
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////// timeshift ap (AB Loop) //////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void MApp_TimeShift_ABLoop_SetA(void)
{
    if(_enTimeShiftState != E_TIMESHIFT_STATE_WAIT)
    {
        _pstPvrPlaybackPath->u32FilePosAKB = _pstPvrPlaybackPath->u32FilePositionKB;
    }
}

/***************************************************************************************/
void MApp_TimeShift_ABLoop_SetB(void)
{
    if(_enTimeShiftState != E_TIMESHIFT_STATE_WAIT)
    {
        _pstPvrPlaybackPath->bABLoopSwitch = TRUE;
    }
}

/***************************************************************************************/
void MApp_TimeShift_ABLoop_Off(void)
{
    if(_enTimeShiftState != E_TIMESHIFT_STATE_WAIT)
    {
        if(_pstPvrPlaybackPath != NULL)
        {
            _pstPvrPlaybackPath->bABLoopSwitch = FALSE;
        }
    }
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////// timeshift ap (finite state machine) ///////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
/***************************************************************************************/
void MApp_TimeShift_StateMachineRunning(void)
{
    #if DEBUG_TIMESHIFT_STATE  //=====================================================//
    {
        static U8 preState = 0xFF;
        if(preState != _enTimeShiftState)
        {
            //printf("Timeshift [%bu]->[%bu]\n", preState, _enTimeShiftState);
            preState = _enTimeShiftState;
        }
    }
    #endif  //=========================================================================//

    switch (_enTimeShiftState)
    {
        /*[01]WAIT state (channel change) =============================================*/
        case E_TIMESHIFT_STATE_WAIT:
        {
            if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_PAUSE)
            {
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_RECORDOPEN);
                if(MApp_TimeShift_RecordOpen() == TRUE)
                {
                    if(MApp_TimeShift_RecordEnable() == TRUE)
                    {
                      //printf("STCH[[TSH]]@WAIT->RUNNING\n");
                        _enTimeShiftState = E_TIMESHIFT_STATE_RECORDING;
                        _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                        u32OriginPlayTime = 0;
                    }
                }
                else
                {
                    MApp_TimeShift_PlaybackResume();
                    MApp_TimeShift_PlaybackDisable();
                    MApp_TimeShift_PlaybackClose();
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
            }
            else if(_enTimeShiftInput != E_TIMESHIFT_INPUT_NONE)
            {
                //printf("ERROR_INPUT_TO_WAIT\n");
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
            }

            break;
        }

        /*[02]RUNNING state ===========================================================*/
        case E_TIMESHIFT_STATE_RECORDING:
        case E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING:
        case E_TIMESHIFT_STATE_PLAYBACKING:
        {
            /*[02-1]record/playback on/off ============================================*/
            if(_enTimeShiftInput == E_TIMESHIFT_INPUT_RECORD_CLOSE)
            {
                MApp_TimeShift_RecordDisable();
                MApp_TimeShift_RecordClose();

                if(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                {
                    // printf("STCH[[TSH]]@RECORDINGnPLAYBACKING->PLAYBACKING\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_PLAYBACKING;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                else if(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDING)
                {
                    MApp_TimeShift_PlaybackResume();

                    // printf("STCH[[TSH]]@RECORDING->WAIT\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_WAIT;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                    // fixed: switch audio when timeshift then exit,it will not SPDIF out.
#if(ENABLE_CHECK_SPDIF_MUTE_STATUS)

                     if(MApi_AUDIO_SPDIF_GetMute_Status() == 1)
                    {
                       MApi_AUDIO_SPDIF_SetMute(FALSE);
                    }
#endif
                }
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_CLOSE)
            {
                msAPI_PVR_PlaybackPathWaitAVFifoClean();//reset CmdQ ,and wait AVFifo clean to prevent TSP from going in the block state
                if((_enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)||(_enTimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
                {
                    MApi_DMX_BypassFileInTimeStamp(TRUE);
                    msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                    MApi_DMX_BypassFileInTimeStamp(FALSE);
                }
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_RESUME);
                MApp_TimeShift_PlaybackResume();
                MApp_TimeShift_PlaybackDisable();
                MApp_TimeShift_PlaybackClose();

                if(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                {
                  //printf("STCH[[TSH]]@RECORDINGnPLAYBACKING->RECORDING\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_RECORDING;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                else if(_enTimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING)
                {
                  //printf("STCH[[TSH]]@PLAYBACKING->WAIT\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_WAIT;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_PAUSE)
            {
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_NONE);
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_STEP_IN)
            {
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_STEPIN);  //fast forward / fast backward
                MApp_TimeShift_PlaybackStepIn();
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_JUMP_TO_TIME)
            {
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_JUMPTOTIME);
                if(!MApp_TimeShift_PlaybackJumpToTime(_u32TimeShiftExtPara))
                {
                    MApp_TimeShift_PlaybackResume();
                    MApp_TimeShift_PlaybackDisable();
                    MApp_TimeShift_PlaybackClose();

                    if( _enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                    {
                        MApp_TimeShift_RecordDisable();
                        MApp_TimeShift_RecordClose();
                    }
                  //printf("STCH[[TSH]]@RECORDINGnPLAYBACKING->WAIT\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_WAIT;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                else
                {
                    MApp_TimeShift_PlaybackResume();
                }

                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_JUMP_FORWARD)
            {
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_JUMPFORWARD);
                if(!MApp_TimeShift_PlaybackJumpForward(_u32TimeShiftExtPara))
                {
                    MApp_TimeShift_PlaybackResume();
                    MApp_TimeShift_PlaybackDisable();
                    MApp_TimeShift_PlaybackClose();

                    if( _enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                    {
                        MApp_TimeShift_RecordDisable();
                        MApp_TimeShift_RecordClose();
                    }
                  //printf("STCH[[TSH]]@RECORDINGnPLAYBACKING->WAIT\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_WAIT;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                else
                {
                    MApp_TimeShift_PlaybackResume();
                }

                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_JUMP_BACKWARD)
            {
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_JUMPBACKWARD);
                MApp_TimeShift_PlaybackJumpBackward(_u32TimeShiftExtPara);
                MApp_TimeShift_PlaybackResume();
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_SLOW_FORWARD)
            {
                MApi_DMX_GetFileInTimeStamp(&u32TimeshiftTempTimeCounter);
                u32TimeshiftStartSysTime = msAPI_Timer_GetTime0();
                if(_bTimeshiftStepIn)
                {
                    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
                }
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_SLOWFORWARD);
                MApp_TimeShift_Playback_SlowForward();
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_FAST_FORWARD)
            {
                MApi_DMX_GetFileInTimeStamp(&u32TimeshiftTempTimeCounter);
                u32TimeshiftStartSysTime = msAPI_Timer_GetTime0();
                if(_bTimeshiftStepIn)
                {
                    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
                }
#if (!INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE)
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_FASTFORWARD);
#endif
                MApp_TimeShift_PlaybackFastForward();
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_FAST_BACKWARD)
            {
                MApi_DMX_GetFileInTimeStamp(&u32TimeshiftTempTimeCounter);
                u32TimeshiftStartSysTime = msAPI_Timer_GetTime0();
                if(_bTimeshiftStepIn)
                {
                    msAPI_Player_VideoPlay(E_PLAY_MODE_NORMAL);
                }
#if (!INPUT_FAST_PLAYBACK_WHEN_STEPDISP_DONE)
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_FASTBACKWARD);
#endif
                MApp_TimeShift_PlaybackFastBackward();
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }
            else if(_enTimeShiftInput == E_TIMESHIFT_INPUT_PLAYBACK_RESUME)
            {
                MApp_TimeShift_PlaybackOpen();
                MApp_TimeShift_PlaybackEnable();
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_RESUME); //fast forward / fast backward
                MApp_TimeShift_PlaybackResume();
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
                MAPP_CIPVR_SetMuteFlag(false,E_SCREEN_MUTE_BY_LIVE_PIN_EVENT);
 #endif
                MApp_TimeShift_SetAudioLanguage();

                _bTimeshiftStepIn = FALSE;

                if(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDING)
                {
                  //printf("STCH[[TSH]]@RECORDING->RECORDINGnPLAYBACKING\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING;
                }
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
            }
            else if(_enTimeShiftInput != E_TIMESHIFT_INPUT_NONE)
            {
                MS_DEBUG_MSG(printf("ERROR_INPUT_TO_RUNNING\n"));
                _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                _bTimeshiftStepIn = FALSE;
            }

            /*[02-2]record running ====================================================*/
            if(!MApp_TimeShift_RecordRoutine())
            {
                MApp_TimeShift_RecordDisable();
                MApp_TimeShift_RecordClose();

                if(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                {
                  //printf("STCH[[TSH]]@RECORDINGnPLAYBACKING->PLAYBACKING\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_PLAYBACKING;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                else if(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDING)
                {/*
                    if(_enTimeShiftStatus == E_PVR_API_STATUS_DISK_SPEED_SLOW)
                    {
                        MApp_TimeShift_PlaybackOpen();
                        MApp_TimeShift_PlaybackResume();
                        MApp_TimeShift_PlaybackDisable();
                        MApp_TimeShift_PlaybackClose();

                      //printf("STCH[[TSH]]@RECORDING->WAIT\n");
                        _enTimeShiftState = E_TIMESHIFT_STATE_WAIT;
                        _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                    }
                    else*/
                    {
                        if(MApp_TimeShift_PlaybackOpen())
                        {
                          //printf("STCH[[TSH]]@RECORDING->PLAYBACKING\n");
                            _enTimeShiftState = E_TIMESHIFT_STATE_PLAYBACKING;
                        }
                        _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                    }
                }
                _bTimeshiftStepIn = FALSE;
            }

            /*[02-3]playback running ==================================================*/
            if (!MApp_TimeShift_PlayabackRoutine())
            {
                msAPI_PVR_PlaybackPathWaitAVFifoClean();////reset CmdQ ,and wait AVFifo clean to prevent TSP from going in the block state
                if((_enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)||(_enTimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING))
                {
                    MApi_DMX_BypassFileInTimeStamp(TRUE);
                    msAPI_PVR_ClearBitStreamBuff(_pstPvrPlaybackPath);
                    MApi_DMX_BypassFileInTimeStamp(FALSE);
                }
                MApp_TimeShift_PlaybackPause(E_TIMESHIFT_PLAYBACK_NEXTACT_RESUME);
                MApp_TimeShift_PlaybackResume();
                MApp_TimeShift_PlaybackDisable();
                MApp_TimeShift_PlaybackClose();

                if(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
                {
                    MApp_TimeShift_RecordDisable();
                    MApp_TimeShift_RecordClose();

                  //printf("STCH[[TSH]]@RECORDINGnPLAYBACKING->WAIT\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_WAIT;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                else if(_enTimeShiftState == E_TIMESHIFT_STATE_PLAYBACKING)
                {
                  //printf("STCH[[TSH]]@PLAYBACKING->WAIT\n");
                    _enTimeShiftState = E_TIMESHIFT_STATE_WAIT;
                    _enTimeShiftInput = E_TIMESHIFT_INPUT_NONE;
                }
                _bTimeshiftStepIn = FALSE;
            }


            break;
        }
    }
}

/***************************************************************************************/
void MApp_TimeShift_StateMachineInput(enTimeShiftInput enSMInput, U32 u32ExtParameter)
{
    _enTimeShiftInput    = enSMInput;
    _u32TimeShiftExtPara = u32ExtParameter;

    switch (_enTimeShiftInput)
    {
        //(1)record close =============================================================//
        case E_TIMESHIFT_INPUT_RECORD_CLOSE:
        {
          //printf("E_TIMESHIFT_INPUT_RECORD_CLOSE\n");
            break;
        }

        //(2)playback pause ===========================================================//
        case E_TIMESHIFT_INPUT_PLAYBACK_PAUSE:
        {
          //printf("E_TIMESHIFT_INPUT_PLAYBACK_PAUSE\n");
            break;
        }

        //(3)playback resume ==========================================================//
        case E_TIMESHIFT_INPUT_PLAYBACK_RESUME:
        {
          //printf("E_TIMESHIFT_INPUT_PLAYBACK_RESUME\n");
            break;
        }

        //(4)jump forward =============================================================//
        case E_TIMESHIFT_INPUT_PLAYBACK_JUMP_FORWARD:
        {
          //printf("E_TIMESHIFT_INPUT_PLAYBACK_JUMP_FORWARD\n");
            break;
        }

        //(5)jump backward ===========================================================//
        case E_TIMESHIFT_INPUT_PLAYBACK_JUMP_BACKWARD:
        {
          //printf("E_TIMESHIFT_INPUT_PLAYBACK_JUMP_BACKWARD\n");
            break;
        }

        //(6)fast forward =============================================================//
        case E_TIMESHIFT_INPUT_PLAYBACK_FAST_FORWARD:
        {
          //printf("E_TIMESHIFT_INPUT_PLAYBACK_FAST_FORWARD\n");
            break;
        }

        //(7)fast backward ===========================================================//
        case E_TIMESHIFT_INPUT_PLAYBACK_FAST_BACKWARD:
        {
          //printf("E_TIMESHIFT_INPUT_PLAYBACK_FAST_BACKWARD\n");
            break;
        }

        //(8)playback close ==========================================================//
        case E_TIMESHIFT_INPUT_PLAYBACK_CLOSE:
        {
          //printf("E_TIMESHIFT_INPUT_PLAYBACK_CLOSE\n");
            break;
        }

        //(0)default ==================================================================//
        default:
        {
          //printf("MApp_TimeShift Unknown Input: %x\n", enSMInput);
            break;
        }

        //=============================================================================//
    }

        MApp_TimeShift_StateMachineRunning();

    _enTimeShiftInput    = E_TIMESHIFT_INPUT_NONE;  //ensure to consume any input
    _u32TimeShiftExtPara = 0;                       //ensure to consume any parameter
}

/***************************************************************************************/
enTimeShiftState MApp_TimeShift_StateMachineGet(void)
{
    return _enTimeShiftState;
}

/***************************************************************************************/
enTimeShiftPlaybackState MApp_TimeShift_Playback_StateMachineGet(void)
{
    return _enTimeShiftPlaybackState;
}

void MApp_TimeShift_GetFileName(U16 * u16NameBuffer)
{
    #ifdef PVR_8051
    MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
    #endif
    UnicodeCpy((S8 *)u16NameBuffer, (S8 *)_pu16TimeShiftFileName);
    #ifdef PVR_8051
    MDrv_Sys_ReleaseXdataWindow1();
    #endif
}

/***************************************************************************************/
enPvrApiStatus  MApp_TimeShift_StatusGet(void)
{
    enPvrApiStatus enTimeShiftStatus = _enTimeShiftStatus;
    _enTimeShiftStatus = E_PVR_API_STATUS_OK;    //read clear
    return enTimeShiftStatus;
}

BOOLEAN MApp_TimeShift_Is_InRecording(void)
{
    if( (_enTimeShiftState == E_TIMESHIFT_STATE_RECORDING)
      ||(_enTimeShiftState == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING)
      )
    {
        return TRUE;
    }

    return FALSE;
}

U32 MApp_TimeShift_GetStartSysTime(void)
{
    /*[01]error condition =============================================================*/
    if ((_enTimeShiftState != E_TIMESHIFT_STATE_RECORDING            ) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) &&
        (_enTimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING          )   )
    {
        return 0;
    }
    if (_pstPvrRecordPath == NULL)
    {
        return 0;
    }

    return _pstPvrRecordPath->u32RecordedStartSysTime;
}

enPvrEncryptType MApp_TimeShift_GetEncryptionType(void)
{
    if (_pstPvrRecordPath== NULL)
    {
        return E_PVR_ENCRYPTION_NONE;
    }
    return _pstPvrRecordPath->enEncryptionType;
}

BOOL MApp_TimeShift_SetCicamCheckLevel(U8 u8CicamCheckLevel)
{
    if (_pstPvrRecordPath== NULL)
    {
        return FALSE;
    }

    if(u8CicamCheckLevel > _pstPvrRecordPath->u8CicamCheckLevel)
    {
        _pstPvrRecordPath->u8CicamCheckLevel = u8CicamCheckLevel;
    }
    return TRUE;
}

/***************************************************************************************/

#else
BOOLEAN code compile_mapp_timeshift;
#endif//ENABLE_PVR
#undef MAPP_TIMESHIFT_C

