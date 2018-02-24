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

#define MAPP_RECORD_C

//system
#include "Board.h"                  //For pvr select
#include "sysinfo.h"                //For record buffer

#include "debug.h"

#if ENABLE_PVR

//api
#include "IOUtil.h"                 //For Unicode String compare
#include "msAPI_Timer.h"            //For timer
#include "msAPI_PVR.h"              //For pvr
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_CIPVR_Adaption.h"              //For pvr
#endif
#include "msAPI_PVRFileSystem.h"
//ap
#include "mapp_demux.h"             //For demux
#include "mapp_si.h"                //For SI
#ifdef S3PLUS
#include "MApp_MHEG5_Main.h"        //For MHEG5
#endif
#include "MApp_ChannelChange.h"     //For channel change
#include "MApp_Playback.h"          //For playback-linkage
#include "MApp_Record.h"            //For itself
#include "MApp_PVR_Browser.h"
#include "MApp_GlobalFunction.h"
//ui <--better not be here
#ifdef PVR_8051
#ifdef S3PLUS
#include "MApp_UiMenuFunc.h"
#endif
#include "MApp_UiMenu.h"
#else
#include "MApp_UiMenuDef.h"
#endif
#include "MApp_MultiTasks.h"



/*************************************************************************************************/
#define DEBUG_RECORD_STATE      0

#define DEBUG_RECORD(x)     //x

/*************************************************************************************************/
#ifndef S3PLUS
static _msAPI_PVR_RecordPath *   _pstPvrRecordPath[PVR_MAX_RECORD_PATH]= {NULL, NULL, NULL}; //three record path
#else
static _msAPI_PVR_RecordPath *   _pstPvrRecordPath[PVR_MAX_RECORD_PATH]= {NULL};             //one   record path
#endif
#if 0//def PVR_8051
static U16 xdata * _pu16RecordFileName = (U16 xdata *)0xf000;
#else
static U16 _pu16RecordFileName[RECORD_NAME_LENGTH]={0};
#endif

static enRecordState    _enRecordState      = E_RECORD_STATE_WAIT;      //record_state
static enRecordInput    _enRecordInput      = E_RECORD_INPUT_NONE;      //record_input from outside
static U32              _u32RecordExtPara   = 0;                        //record_input from outside
static enPvrApiStatus   _enRecordStatus     = E_PVR_API_STATUS_OK;      //record_status

static U8               _u8RecordPathPioneer= RECORD_PATH_DEFAULT;
static BOOLEAN          _bRecordAll         = FALSE;

#if ENABLE_FileIn_PMTMonitor
extern BOOLEAN _RecordUpdateAllPIDs;
#endif

extern U16 g_u16CiPinCode;
/*************************************************************************************************/

/*###############################################################################################*/
/*//////////////////////////////////////// record path //////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static U8 MApp_Record_GetWorkingPathCount(void)
{
    U8 u8RecordPathNum;
    U8 u8WorkingPathCount = 0;

    for(u8RecordPathNum = 0; u8RecordPathNum < PVR_MAX_RECORD_PATH; u8RecordPathNum++)
    {
        if(_pstPvrRecordPath[u8RecordPathNum] != NULL)
        {
            u8WorkingPathCount++;
        }
    }

    return u8WorkingPathCount;
}
void MApp_Record_Reset(U8 u8PathNum)
{
    LongLong llFilePos;
    U32 u32pvrBeginFilePosition = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE;

    if (u32RecordLastWriteDataSize)
    {
            u32RecordLastWriteDataSize = 0; //not roll back err data
            llFilePos = msAPI_PVRFS_FileTell(_pstPvrRecordPath[u8PathNum]->hWriteFile);
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
            msAPI_PVRFS_FileSeek(_pstPvrRecordPath[u8PathNum]->hWriteFile, llFilePos, PVRFS_SEEK_OPTION_FROM_BEGIN);
    }

    msAPI_PVR_RecoreReset(_pstPvrRecordPath[u8PathNum]);
}

/***************************************************************************************/
static U8 MApp_Record_Open(U16 *pu16RecordFileName)
{
    U8 u8RecordOpen = FALSE;
    U8 u8RecordPathNum;

    /*[01]error condition =============================================================*/
    if ((_enRecordState != E_RECORD_STATE_WAIT) && (_enRecordState != E_RECORD_STATE_RECORDING))
    {
        return RECORD_PATH_INVALID;
    }
  //printf("MApp_Record_Open \n");

    if(msAPI_PVR_IsRecordSpaceEnough() == FALSE)
    {
        _enRecordStatus = E_PVR_API_STATUS_NO_DISK_SPACE;
        _enRecordState = E_RECORD_STATE_WAIT;

        return RECORD_PATH_INVALID;
    }
    /*[02-1]set pvr record path =======================================================*/
    #ifdef PVR_8051
    MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
    #endif
    _pu16RecordFileName[0] = 0;
    //UnicodeCpy((S8 *)_pu16RecordFileName, (S8 *)pu16RecordFileName);
    UnicodeCpy2((S8 *)_pu16RecordFileName, (S8 *)pu16RecordFileName, RECORD_NAME_LENGTH);
    #ifdef PVR_8051
    MDrv_Sys_ReleaseXdataWindow1();
    #endif

    for(u8RecordPathNum = 0; u8RecordPathNum < PVR_MAX_RECORD_PATH; u8RecordPathNum++)
    {
        if(_pstPvrRecordPath[u8RecordPathNum] == NULL)
        {
          //printf("u8RecordPathNum = %02bu \n", u8RecordPathNum);
            break;
        }
        else if(u8RecordPathNum == (PVR_MAX_RECORD_PATH-1))
        {
            return RECORD_PATH_INVALID;
        }
    }

    if(u8RecordPathNum >= PVR_MAX_RECORD_PATH)
    {
        return RECORD_PATH_INVALID;
    }

    _pstPvrRecordPath[u8RecordPathNum] = msAPI_PVR_RecordPathOpen(pu16RecordFileName, E_FILE_MODE_NORMAL);

    if(_pstPvrRecordPath[u8RecordPathNum])
    {
        //inherit from Pioneer Path (OPEN)
        if(_enRecordState == E_RECORD_STATE_RECORDING)
        {
            //none
        }
        u8RecordOpen = TRUE;

        WORD wProgramPositon;
        MEMBER_SERVICETYPE bServiceType;
        bServiceType = msAPI_CM_GetCurrentServiceType();
        wProgramPositon = msAPI_CM_GetCurrentPosition(bServiceType);

#if ENABLE_PVR_AESDMA
          _pstPvrRecordPath[u8RecordPathNum]->enEncryptionType = E_PVR_ENCRYPTION_DEFAULT;
#else
        _pstPvrRecordPath[u8RecordPathNum]->enEncryptionType = E_PVR_ENCRYPTION_NONE;
#endif

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        U16 u16CiPinCode = g_u16CiPinCode;
        CI_CC_URI_LICENSE stUriLicense;
        U8 u8aCICAMID[CC_AUTH_ID_SIZE] = { 0 };
        if(msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED)
                ||(EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode()))
        {
            enPvrApiStatus enPvrStatus = MAPP_CIPVR_CIPlusPVRHandling(PVR_PATH_RECORD,false,u16CiPinCode);
            if((E_PVR_API_STATUS_OK != enPvrStatus) && (E_PVR_API_STATUS_SUCCESS_CIPLUS_COPY_PROTECTION != enPvrStatus))
            {
                printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                _enRecordStatus = enPvrStatus;
                _enRecordState = E_RECORD_STATE_WAIT;
                msAPI_PVR_RecordPathClose(_pstPvrRecordPath[u8RecordPathNum]);
                _pstPvrRecordPath[u8RecordPathNum] = NULL;
                msAPI_PVRFS_FileDelete(pu16RecordFileName);
                msAPI_CIPVRFS_FileDelete(pu16RecordFileName);
                return RECORD_PATH_INVALID;
            }
            if(E_PVR_API_STATUS_SUCCESS_CIPLUS_COPY_PROTECTION == enPvrStatus)
            {
                //for CI+ scramble only
                _pstPvrRecordPath[u8RecordPathNum]->enEncryptionType = E_PVR_ENCRYPTION_CIPLUS;
                if(FALSE == msAPI_CI_CC_GetCICAMID(u8aCICAMID))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enRecordStatus = E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                    _enRecordState = E_RECORD_STATE_WAIT;
                    msAPI_PVR_RecordPathClose(_pstPvrRecordPath[u8RecordPathNum]);
                    _pstPvrRecordPath[u8RecordPathNum] = NULL;
                    msAPI_PVRFS_FileDelete(pu16RecordFileName);
                    msAPI_CIPVRFS_FileDelete(pu16RecordFileName);
                    return RECORD_PATH_INVALID;
                }
                if(msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED)
                        &&(FALSE == msAPI_CI_CC_GetCicamUriLicenseUpdate(&stUriLicense,false)))
                {
                    printf(".....ERROR_CIPLUS_COPY.....%s %d .............\n",__FUNCTION__,__LINE__);
                    _enRecordStatus = E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION;
                    _enRecordState = E_RECORD_STATE_WAIT;
                    msAPI_PVR_RecordPathClose(_pstPvrRecordPath[u8RecordPathNum]);
                    _pstPvrRecordPath[u8RecordPathNum] = NULL;
                    msAPI_PVRFS_FileDelete(pu16RecordFileName);
                    msAPI_CIPVRFS_FileDelete(pu16RecordFileName);
                    return RECORD_PATH_INVALID;
                }
            }
            else
            {
                //for CI scramble only
                _pstPvrRecordPath[u8RecordPathNum]->enEncryptionType = E_PVR_ENCRYPTION_DEFAULT;
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
            _pstPvrRecordPath[u8RecordPathNum]->u8CicamCheckLevel = (U8)CicamVersion;
        }
        else
#endif
        {
            printf(".record  e2.....%s %d . .......\n",__FUNCTION__,__LINE__);
            _pstPvrRecordPath[u8RecordPathNum]->u8CicamCheckLevel = 0;
        }
    }
    else
    {
        //printf("Record open fail\n");
        _enRecordStatus = E_PVR_API_STATUS_NO_DISK_SPACE;   //temp solution
        #ifdef PVR_8051
        MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
        #endif
        _pu16RecordFileName[0] = 0; //to prevent "instant play"
        #ifdef PVR_8051
        MDrv_Sys_ReleaseXdataWindow1();
        #endif
        u8RecordOpen = FALSE;
    }

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/
    if(u8RecordOpen)
    {
        if(_enRecordState != E_RECORD_STATE_RECORDING)
        {
            _enRecordState = E_RECORD_STATE_OPEN;
        }
        return u8RecordPathNum;
    }
    else
    {
        if(_enRecordState != E_RECORD_STATE_RECORDING)
        {
            _enRecordState = E_RECORD_STATE_WAIT;
        }
        return RECORD_PATH_INVALID;
    }
}

/***************************************************************************************/
static BOOLEAN  MApp_Record_Enable(U8 u8PathNum)
{
    U8 u8RecordEnable = FALSE;
#if 1
    U8 u8i;
    AUD_INFO AudioStreamInfo;
#endif

    //PRINT_CURRENT_LINE();
    DEBUG_RECORD( printf("MApp_Record_Enable(u8PathNum=%u)\n", u8PathNum); );
    DEBUG_RECORD( printf("_enRecordState=%u\n", _enRecordState); );

    /*[01]error condition =============================================================*/
    if ((_enRecordState != E_RECORD_STATE_OPEN) && (_enRecordState != E_RECORD_STATE_RECORDING))
    {
        return FALSE;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return FALSE;
    }
  //printf("MApp_Record_Enable \n");

    /*[02-1]set pvr record path =======================================================*/
    if (_bRecordAll)
    {
      #if 1//def MIPS_CHAKRA
        _pstPvrRecordPath[u8PathNum]->u32BufferStart  = _PA2VA(((PVR_TRICK_MODE_MEMORY_TYPE&MIU1)?PVR_TRICK_MODE_ADR|MIU_INTERVAL:PVR_TRICK_MODE_ADR)); //_PA2VA(PVR_TRICK_MODE_ADR); // PvrGetWriteSdramAdr();                 //<--from system
      #else
        _pstPvrRecordPath[u8PathNum]->u32BufferStart  = PVR_TRICK_MODE_ADR;
      #endif
        _pstPvrRecordPath[u8PathNum]->u32BufferLength = PVR_TRICK_MODE_LEN;                 //<--from system
    }
    else
    {
        _pstPvrRecordPath[u8PathNum]->u32BufferStart  = PvrGetWriteSdramAdr();                 //<--from system
        _pstPvrRecordPath[u8PathNum]->u32BufferLength = PVR_WRITE_SDRAM_LEN;                 //<--from system
    }


    if ((_enRecordStatus=msAPI_PVR_RecordPathSet(_pstPvrRecordPath[u8PathNum])) == E_PVR_API_STATUS_OK)
    {
        //============== special treatment for factory mode - record all ==============*/
        if(_bRecordAll)
        {
            _pstPvrRecordPath[u8PathNum]->bRecordAll = TRUE;
        }
        //============== special treatment for factory mode - record all ==============*/

        //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_u16Current_PCRPID,             MSAPI_DMX_FILTER_TYPE_PCR);          //<--from other AP:(01) PCR
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_u16Current_PVR_VideoPID,       MSAPI_DMX_FILTER_TYPE_VIDEO);        //<--from other AP:(02) VIDEO
      //msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_u16Current_PVR_AudioPID,       MSAPI_DMX_FILTER_TYPE_AUDIO);        //<--from other AP:(03) AUDIO
        #ifndef S3PLUS
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_u16Current_AudioDescriptorPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);       //<--from other AP:(04) AUDIO DESCRIPTOR
        #endif
#if 1
        _pstPvrRecordPath[u8PathNum]->u8audioLangTotal = msAPI_CM_GetAudioStreamCount(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
        _pstPvrRecordPath[u8PathNum]->u8audioLangSel = g_u8AudLangSelected;
        _pstPvrRecordPath[u8PathNum]->u16ServiceID  = msAPI_CM_GetService_ID(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
        _pstPvrRecordPath[u8PathNum]->u8Parental_Control = MApp_EIT_GetCurParentControl();

        #ifdef S3PLUS
        for (u8i=0; u8i < _pstPvrRecordPath[u8PathNum]->u8audioLangTotal; u8i++)
        {
            if (E_RESULT_SUCCESS == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
            {
                if (u8i == g_u8AudLangSelected)
                {
                    msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], AudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
                    memcpy(&_pstPvrRecordPath[u8PathNum]->PVRAudioInfo[0], &AudioStreamInfo, sizeof(AudioStreamInfo));
                    break;
                }
            }
        }
        _pstPvrRecordPath[u8PathNum]->u8audioLangTotal = 1;
        _pstPvrRecordPath[u8PathNum]->u8audioLangSel   = 0;
        #else
        for (u8i=0; u8i < _pstPvrRecordPath[u8PathNum]->u8audioLangTotal; u8i++)
        {
            #ifdef PVR_8051
            if( E_RESULT_SUCCESS == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
            #else
            if( TRUE == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
            #endif
            {
                msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], AudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
                memcpy(&_pstPvrRecordPath[u8PathNum]->PVRAudioInfo[u8i], &AudioStreamInfo, sizeof(AudioStreamInfo));
            }
        }
        #endif
#endif
        //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#if (ENABLE_SUBTITLE)
        #ifdef S3PLUS
        if (u8SubtitleMenuNum ==0)
        {
            _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum   = 0;
            _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuNum         = 0;

            _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = 0;
            _pstPvrRecordPath[u8PathNum]->u8TTXSubtitleServiceNum   = 0;
        }
        else if (SutitleItemSelIdx == 0)
        {
            if (MApp_UiMenuFunc_SelectSubtileLang())
            {
                _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum   = 1;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = 1;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuNum         = 1;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = 1;
               bRestoreSubtitleSelIdx = TRUE;
            }
            else
            {
                _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum   = 0;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = 0;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuNum         = 0;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = 0;
                bRestoreSubtitleSelIdx = FALSE;
            }
       }
        else
        {
            if ((SubtitleMenu[SutitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT) || (SubtitleMenu[SutitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH))
            {
                _pstPvrRecordPath[u8PathNum]->u8TTXSubtitleServiceNum   = 0;
                _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum   = 0;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuNum         = 0;
                _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = 0;
            }
            else
            {
                _pstPvrRecordPath[u8PathNum]->u8TTXSubtitleServiceNum   = 0;
                _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum   = 1;
            _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuNum         = 1;
            _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = 1;
        }
        }
        #else
        _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum = u8DVBSubtitleServiceNum;
        _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuNum    = u8SubtitleMenuNum;

        #ifdef PVR_8051
        _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = SutitleItemSelIdx;
        _pstPvrRecordPath[u8PathNum]->u8TTXSubtitleServiceNum = u8TTXSubtitleServiceNum;
        #else
        _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = u8SubtitleItemSelIdx;
        _pstPvrRecordPath[u8PathNum]->u8TTXSubtitleServiceNum = gu8TTXSubtitleServiceNum;
        #endif
        #endif

        #ifdef S3PLUS
        for (u8i =0; u8i < u8DVBSubtitleServiceNum; u8i++)
        {
            if (u8i == SutitleItemSelIdx-1)
            {
                msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], DVBSubtitleServices[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
                memcpy( _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[0].StringCodes, DVBSubtitleServices[u8i].StringCodes, 4);
                _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[0].u16PID                   = DVBSubtitleServices[u8i].u16PID;
                _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[0].u16Ancillary_Page_id     = DVBSubtitleServices[u8i].u16Ancillary_Page_id;
                _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[0].u16Composition_Page_id   = DVBSubtitleServices[u8i].u16Composition_Page_id;
                _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[0].u8SubtitleType           = DVBSubtitleServices[u8i].u8SubtitleType;
                break;
            }
        }
        #else
        for (u8i =0; u8i < u8DVBSubtitleServiceNum; u8i++)
        {
            msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], DVBSubtitleServices[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
            memcpy( _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].StringCodes, DVBSubtitleServices[u8i].StringCodes, 4);
            _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u16PID                   = DVBSubtitleServices[u8i].u16PID;
            _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u16Ancillary_Page_id     = DVBSubtitleServices[u8i].u16Ancillary_Page_id;
            _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u16Composition_Page_id   = DVBSubtitleServices[u8i].u16Composition_Page_id;
            _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u8SubtitleType           = DVBSubtitleServices[u8i].u8SubtitleType;
        }
        #endif

        _pstPvrRecordPath[u8PathNum]->u8EnableSubtitle    = stGenSetting.g_SysSetting.fEnableSubTitle;
        _pstPvrRecordPath[u8PathNum]->u8EnableTTXSubtitle = stGenSetting.g_SysSetting.fEnableTTXSubTitle;
#endif

#if (ENABLE_SUBTITLE)
        #ifdef S3PLUS
        for (u8i =0; u8i < u8SubtitleMenuNum; u8i++)
        {
            if (u8i == SutitleItemSelIdx-1)
            {
                msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], SubtitleMenu[0].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
                memcpy( _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[0].StringCodes, SubtitleMenu[u8i].StringCodes, 4);
                _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[0].u16PID                      = SubtitleMenu[u8i].u16PID;
                _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[0].u8Magazine                  = SubtitleMenu[u8i].u8Magazine;
                _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[0].u8Page                      = SubtitleMenu[u8i].u8Page;
                _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[0].u8SubtitleType              = SubtitleMenu[u8i].u8SubtitleType;
                break;
            }
        }
        if (bRestoreSubtitleSelIdx)
        {
           SutitleItemSelIdx = 0;
           bRestoreSubtitleSelIdx = FALSE;
        }
        #else
        for (u8i =0; u8i < u8SubtitleMenuNum; u8i++)
        {
            if ((SubtitleMenu[u8i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT) || (SubtitleMenu[u8i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH))
            {
                msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], SubtitleMenu[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
            }
            memcpy( _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[u8i].StringCodes, SubtitleMenu[u8i].StringCodes, 4);
            _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[u8i].u16PID                      = SubtitleMenu[u8i].u16PID;
            _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[u8i].u8Magazine                  = SubtitleMenu[u8i].u8Magazine;
            _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[u8i].u8Page                      = SubtitleMenu[u8i].u8Page;
            _pstPvrRecordPath[u8PathNum]->PVRSubtitleMenu[u8i].u8SubtitleType              = SubtitleMenu[u8i].u8SubtitleType;
        }
        #endif
#endif
        #if BRAZIL_PVR_CC
        {
            U16 u16CCPid =MApp_SI_Get_CC_PID();
            if (u16CCPid != MSAPI_DMX_INVALID_PID)
                msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], u16CCPid, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) CC
        }
        #endif

      //msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], MApp_Subitle_GetCurPID(),        MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
        //(TYPE3)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], PID_PAT,                         MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(06) PAT
        #ifdef PVR_8051
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_stSIInfo.stPmtMonInfo.wPmtPid, MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(07) PMT
        #else
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], MApp_SI_Get_PMT_PID(),           MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(07) PMT
        #endif
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], PID_CAT,                         MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(08) CAT
        //(TYPE4)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], PID_NIT,                         MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(09) NIT
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], PID_SDT_BAT,                     MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(10) SDT/BAT
        //(TYPE5)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], PID_EIT_CIT,                     MSAPI_DMX_FILTER_TYPE_SECTION_4K);   //<--from other AP:(11) EIT/CIT
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], PID_TDT_TOT,                     MSAPI_DMX_FILTER_TYPE_SECTION_1K);   //<--from other AP:(12) TDT/TOT
        //((( )))~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        msAPI_Player_ScalerReduceBW(TRUE);  //<---to here ***
        #ifdef S3PLUS
        msAPI_Aeon_Disable();                           //<--bandwidth problem, S3P only
        #endif

        msAPI_PVR_RecordPathStart(_pstPvrRecordPath[u8PathNum]);

#if ENABLE_FileIn_PMTMonitor
        _RecordUpdateAllPIDs = FALSE;
#endif
        //inherit from Pioneer Path (START)
        if(_enRecordState == E_RECORD_STATE_RECORDING)
        {
            _pstPvrRecordPath[u8PathNum]->u32FileValidPosStrKB  =  (_pstPvrRecordPath[_u8RecordPathPioneer]->u32FileValidPosEndKB/3)*3;
        }

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
        if(_enRecordState != E_RECORD_STATE_RECORDING)
        {
            _enRecordState = E_RECORD_STATE_RECORDING;
        }
        return TRUE;
    }
    else
    {
        if(_enRecordState != E_RECORD_STATE_RECORDING)
        {
            _enRecordState = E_RECORD_STATE_WAIT;
        }
        return FALSE;
    }
}

/***************************************************************************************/
#if ENABLE_FileIn_PMTMonitor

static BOOLEAN  MApp_RecordCheckSIChange(U8 u8PathNum)
{
    U8 u8i;
    AUD_INFO AudioStreamInfo;
    WORD wCurrentPosition;
    MEMBER_SERVICETYPE bServiceType;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);

    AUD_INFO stAdAudioStreamInfo;
    msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &stAdAudioStreamInfo, g_u8AdAudSelected);


    /* Video and PCR *//* Audio PIDs and Info */
    g_u16Current_PCRPID = msAPI_CM_GetPCR_PID(bServiceType,wCurrentPosition);
    g_u16Current_PVR_VideoPID= msAPI_CM_GetVideoPID(bServiceType,wCurrentPosition);
    g_u16Current_AudioDescriptorPID= stAdAudioStreamInfo.wAudPID;

    /* PMT_PID */
    msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], MApp_SI_Get_PMT_PID(),           MSAPI_DMX_FILTER_TYPE_SECTION_1K);
    /* Video_PID */
    msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_u16Current_PVR_VideoPID,       MSAPI_DMX_FILTER_TYPE_VIDEO);        //<--from other AP:(02) VIDEO
    /* PCR_PID */
    msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_u16Current_PCRPID,             MSAPI_DMX_FILTER_TYPE_PCR);
    /* AUDIO2_PID */
    msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], g_u16Current_AudioDescriptorPID, MSAPI_DMX_FILTER_TYPE_AUDIO2);
    /* AUDIO_PID */
    for (u8i=0; u8i < _pstPvrRecordPath[u8PathNum]->u8audioLangTotal; u8i++)
    {
        if( TRUE == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
        {
            msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], AudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
        }
    }
    #if (ENABLE_SUBTITLE)
    for (u8i =0; u8i < u8DVBSubtitleServiceNum; u8i++)
    {
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], DVBSubtitleServices[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
    }
    for (u8i =0; u8i < u8SubtitleMenuNum; u8i++)
    {
        if ((SubtitleMenu[u8i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT) || (SubtitleMenu[u8i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH))
        {
            msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], SubtitleMenu[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
        }
    }
    #endif
    #if BRAZIL_PVR_CC
    {
        U16 u16CCPid = MApp_SI_Get_CC_PID();
        if (u16CCPid != MSAPI_DMX_INVALID_PID)
            msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], u16CCPid, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) CC
    }
    #endif

    /* TTX_SUB_PID and  TTX_PID  */   //MApp_SI_Parse_PMT
    return TRUE;
}
#endif
/***************************************************************************************/
static BOOLEAN  MApp_Record_Routine(U8 u8PathNum)
{
    DEBUG_RECORD( printf("MApp_Record_Routine(u8PathNum=%u)\n", u8PathNum); );

    /*[01]error condition =============================================================*/
    if (_enRecordState != E_RECORD_STATE_RECORDING)
    {
        return TRUE;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return TRUE;
    }
    //printf("_pstPvrRecordPath[u8PathNum]=0x%X)\n", (U32)_pstPvrRecordPath[u8PathNum]);

  //printf("MApp_Record_Routine \n");
  #if ENABLE_FileIn_PMTMonitor
     if(_RecordUpdateAllPIDs)
     {
         _RecordUpdateAllPIDs = FALSE;
         MApp_RecordCheckSIChange(u8PathNum);
     }
  #endif

    /*[02-1]set pvr record path =======================================================*/
    if(u8PathNum == _u8RecordPathPioneer)   //only Pioneer Path undertake for input
    {
        if ((_enRecordStatus = msAPI_PVR_RecordPathInput(_pstPvrRecordPath[u8PathNum])) != E_PVR_API_STATUS_OK)
        {
            DEBUG_RECORD( printf("_enRecordStatus=%u\n", _enRecordStatus); );
            DEBUG_RECORD( printf("msAPI_PVRFS_GetFileSystemType()=%u\n", msAPI_PVRFS_GetFileSystemType()); );

            if(_enRecordStatus == E_PVR_API_STATUS_RECORD_FILE_OVER_SIZE &&
                (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 || msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT))
            {
                U16 u16NewFileName[RECORD_NAME_LENGTH];

                memset(u16NewFileName, 0, RECORD_NAME_LENGTH);
                MApp_Record_GetCurrentFileName(u8PathNum, u16NewFileName);
                //=== get new file name =====================================
                if(MApp_Record_GetNextSeqFileName(u16NewFileName))
                {
                    if(msAPI_PVRFS_FileExist(u16NewFileName))
                    {
                        return FALSE;
                    }
                }
                else
                {
                    return FALSE;
                }

            #if 0//def PVR_8051
                MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
            #endif
                _pu16RecordFileName[0] = 0;
                UnicodeCpy((S8 *)_pu16RecordFileName, (S8 *)u16NewFileName);

            #if 0//def PVR_8051
                MDrv_Sys_ReleaseXdataWindow1();
            #endif

            #if(ENABLE_PVR_BROWSER)
                PVR_UI_BROWSER_ENTRY E;
                memset(&E, 0, sizeof(PVR_UI_BROWSER_ENTRY));
                U32 recTime;

                //=== Set PVR BROWSWE ======================================
                MApp_PvrBrowser_GetRecordingAttributes(&E);
                recTime = MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT);
                MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_PROGRAM_DURATION, (U16*)E.u16FileName, (BYTE*)&recTime);
                MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, NULL, NULL);
                //===========================================================
            #endif

                if(msAPI_PVR_RecordChangeFile(u16NewFileName, _pstPvrRecordPath[u8PathNum]) != E_PVR_API_STATUS_OK)
                {
                    return FALSE;
                }

            #if(ENABLE_PVR_BROWSER)
                //=== Set PVR BROWSWE ======================================
                UnicodeCpy((S8*)E.u16FileName, (S8*)u16NewFileName);
                E.u32StartTime = MApp_GetLocalSystemTime();
                E.u32Duration  = 0;
                MApp_PvrBrowser_AddNewEntry(&E);
                //MApp_UiPvr_Browser_AddProgramme(u16NewFileName, MApp_GetLocalSystemTime());
                MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, u16NewFileName, NULL);
            #endif
            }
            else if (_enRecordStatus == E_PVR_API_STATUS_RECORD_BUFFER_ERROR)
            {
                MApp_Record_Reset(u8PathNum);
            }
            else
            {
                return FALSE;
            }
        }
    }
    else    //inherit from Pioneer Path (INPUT)
    {
        _pstPvrRecordPath[u8PathNum]->u32FilePositionKB  =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32FilePositionKB;
        _pstPvrRecordPath[u8PathNum]->u32FilePosRmnBytes  =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32FilePosRmnBytes;
        _pstPvrRecordPath[u8PathNum]->u32FileSizeKB      =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32FileSizeKB;

        _pstPvrRecordPath[u8PathNum]->u32FileWriteTime   =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32FileWriteTime;
        _pstPvrRecordPath[u8PathNum]->u32FileWriteSizeKB =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32FileWriteSizeKB;

        _pstPvrRecordPath[u8PathNum]->u32RecordedPeriod  = msAPI_Timer_DiffTimeFromNow(_pstPvrRecordPath[u8PathNum]->u32RecordedTime)/100;
    }
    if ((_enRecordStatus=msAPI_PVR_RecordPathGatherStatistics(_pstPvrRecordPath[u8PathNum])) != E_PVR_API_STATUS_OK)
    {
        if(_enRecordStatus == E_PVR_API_STATUS_DISK_SPEED_SLOW)
        {
            //MApp_UiMenu_PVR_PopUp_Warning_Msg(E_PVR_WARNING_REC_LOW_DISK_SPEED);
            //_enRecordStatus = E_PVR_API_STATUS_OK;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/
    _enRecordState = E_RECORD_STATE_RECORDING;

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN  MApp_Record_Disable(U8 u8PathNum)
{
    DEBUG_RECORD( printf("MApp_Record_Disable(u8PathNum=%u)\n", u8PathNum); );

    /*[01]error condition =============================================================*/
    if (_enRecordState != E_RECORD_STATE_RECORDING)
    {
        return FALSE;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return FALSE;
    }
  //printf("MApp_Record_Disable \n");

    /*[02-1]set pvr record path =======================================================*/
    MApp_Playback_StopRecordLinkage();              //<---(R-P-3)terminate record linkage

    msAPI_PVR_RecordPathStop(_pstPvrRecordPath[u8PathNum]);

    //inherit from Pioneer Path (STOP)
    if(MApp_Record_GetWorkingPathCount() > 1)
    {
        U8 u8RecordPathNum;

        for(u8RecordPathNum = 0; u8RecordPathNum < PVR_MAX_RECORD_PATH; u8RecordPathNum++)
        {
            if(_pstPvrRecordPath[u8RecordPathNum] != NULL)
            {
                if(u8RecordPathNum != _u8RecordPathPioneer)
                {
                    break;
                }
            }
        }

        if(u8RecordPathNum >= PVR_MAX_RECORD_PATH)
        {
            return FALSE;
        }

        _pstPvrRecordPath[u8RecordPathNum]->u32BufferStart        =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32BufferStart;
        _pstPvrRecordPath[u8RecordPathNum]->u32BufferLength       =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32BufferLength;
        _pstPvrRecordPath[u8RecordPathNum]->u32BufferReadPointer  =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32BufferReadPointer;
        _pstPvrRecordPath[u8RecordPathNum]->u32BufferWritePointer =  _pstPvrRecordPath[_u8RecordPathPioneer]->u32BufferWritePointer;

        _pstPvrRecordPath[u8RecordPathNum]->hWriteFile            =  _pstPvrRecordPath[_u8RecordPathPioneer]->hWriteFile;

        _u8RecordPathPioneer = u8RecordPathNum; //pioneer transfer
    }

    /*[02-2]set audio/scaler/video ====================================================*/
    if(MApp_Record_GetWorkingPathCount()==1)
    {
        msAPI_Player_ScalerReduceBW(FALSE);
        #ifdef S3PLUS
        if(App_GetOSDCountrySetting()==OSD_COUNTRY_UK)
        {
            #if (MHEG5_ENABLE)
            msAPI_Aeon_ReInitial( BIN_ID_CODE_AEON_MHEG5 ); //<--bandwidth problem, S3P only
            #endif
        }
        #endif
    }

    /*[03]change state ================================================================*/
    if(MApp_Record_GetWorkingPathCount()==1)
    {
        _enRecordState = E_RECORD_STATE_STOP;
    }

    return TRUE;
}

/***************************************************************************************/
static BOOLEAN  MApp_Record_Close(U8 u8PathNum)
{
    /*[01]error condition =============================================================*/
    if ((_enRecordState != E_RECORD_STATE_STOP) && (_enRecordState != E_RECORD_STATE_RECORDING))
    {
        return FALSE;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return FALSE;
    }
  //printf("MApp_Record_Close \n");

    /*[02-1]set pvr record path =======================================================*/
    msAPI_PVR_RecordPathClose(_pstPvrRecordPath[u8PathNum]);
    _pstPvrRecordPath[u8PathNum] = NULL;

    /*[02-2]set audio/scaler/video ====================================================*/

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        MAPP_CIPVR_PVRCIPlusOperatingMode(EN_CC_DATATYPE_ID_RECORD_STOP,EN_CC_PVR_OPERATING_MODE_RESERVED,NULL,0);
        MAPP_CIPVR_PVRReTriggerURICopyProtect();
        MAPP_CIPVR_SetMuteFlag(false,E_SCREEN_MUTE_BY_LIVE_PIN_EVENT);
#endif

    /*[03]change state ================================================================*/
    if(MApp_Record_GetWorkingPathCount()==0)
    {
        _u8RecordPathPioneer = RECORD_PATH_DEFAULT;
        _enRecordState = E_RECORD_STATE_WAIT;
    }

    return TRUE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*//////////////////////////////// record path (factory mode) ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
BOOLEAN MApp_Record_RecordAllEnable(void)
{
    /*[01]error condition =============================================================*/
    if (_enRecordState == E_RECORD_STATE_RECORDING)
    {
        return FALSE;
    }

    /*[02-1]set pvr record path =======================================================*/
    _bRecordAll = TRUE;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/

    return TRUE;
}

/***************************************************************************************/
BOOLEAN MApp_Record_RecordAllDisable(void)
{
    /*[01]error condition =============================================================*/
    if (_enRecordState == E_RECORD_STATE_RECORDING)
    {
        return FALSE;
    }

    /*[02-1]set pvr record path =======================================================*/
    _bRecordAll = FALSE;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/

    return TRUE;
}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////// record ap (time-bar-related) ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U32 MApp_Record_GetStartTimeSec(U8 u8PathNum)
{
    U32 u32StartTime;

    /*[01]error condition =============================================================*/
    if ((_enRecordState != E_RECORD_STATE_RECORDING) && (_enRecordState != E_RECORD_STATE_STOP))
    {
        return 0;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return 0;
    }
  //printf("MApp_Record_GetStartTimeSec \n");

    /*[02-1]set pvr record path =======================================================*/
    if((_pstPvrRecordPath[u8PathNum]->u32RecordedPeriod - _pstPvrRecordPath[u8PathNum]->u32PausedPeriod) < _pstPvrRecordPath[u8PathNum]->u32FileValidPeriod)
    {
        u32StartTime = _pstPvrRecordPath[u8PathNum]->u32RecordedTime/1000;
    }
    else
    {
        u32StartTime = _pstPvrRecordPath[u8PathNum]->u32RecordedTime/1000  +   //in 1/1000 SECOND
                       _pstPvrRecordPath[u8PathNum]->u32RecordedPeriod/10  -   //in 1/10   SECOND
                       _pstPvrRecordPath[u8PathNum]->u32PausedPeriod/10    -   //in 1/10   SECOND
                       _pstPvrRecordPath[u8PathNum]->u32FileValidPeriod/10;    //in 1/10   SECOND
    }
    return u32StartTime;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/
U32 MApp_Record_GetEndTimeSec(U8 u8PathNum)
{
    U32 u32EndTime;

    /*[01]error condition =============================================================*/
    if ((_enRecordState != E_RECORD_STATE_RECORDING) && (_enRecordState != E_RECORD_STATE_STOP))
    {
        return 0;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return 0;
    }
  //printf("MApp_Record_GetEndTimeSec \n");

    /*[02-1]set pvr record path =======================================================*/
    u32EndTime = _pstPvrRecordPath[u8PathNum]->u32RecordedTime/1000 +        //in 1/1000 SECOND
                 _pstPvrRecordPath[u8PathNum]->u32RecordedPeriod/10 -        //in 1/10   SECOND
                 _pstPvrRecordPath[u8PathNum]->u32PausedPeriod/10;           //in 1/10   SECOND

    return u32EndTime;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/

U32 MApp_Record_GetTotalTimeSec(U8 u8PathNum)
{
    U32 u32TotalTime;

    /*[01]error condition =============================================================*/
    if ((_enRecordState != E_RECORD_STATE_RECORDING) && (_enRecordState != E_RECORD_STATE_STOP))
    {
        return 0;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return 0;
    }

    u32TotalTime =_pstPvrRecordPath[u8PathNum]->u32RecordedPeriod/10 +           //in 1/10   SECOND
                          _pstPvrRecordPath[u8PathNum]->u32RecordedTotalTime/10 ;      //in 1/10   SECOND

    return u32TotalTime;

}

/***************************************************************************************/
U16 MApp_Record_GetAvgRecordRateKB(U8 u8PathNum)
{
    /*[01]error condition =============================================================*/
    if (_enRecordState != E_RECORD_STATE_RECORDING)
    {
        return 0;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return 0;
    }
  //printf("MApp_Record_GetAvgRecordRateKB \n");

    /*[02-1]set pvr record path =======================================================*/
    return _pstPvrRecordPath[u8PathNum]->u16RecordedAvgRate;

    /*[02-2]set audio/scaler/video ====================================================*/



    /*[03]change state ================================================================*/


}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////// record ap (link to playback) ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
BOOLEAN MApp_Record_StopPlaybackLinkage(U8 u8PathNum)
{
    if(_enRecordState != E_RECORD_STATE_WAIT)
    {
        _pstPvrRecordPath[u8PathNum]->bLinkPlayback = FALSE;
      //printf("StopPlaybackLinkage \n");
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/
BOOLEAN MApp_Record_CheckPlaybackLinkage(U8 u8PathNum, U16 *pu16PlaybackFileName)
{
    if(_enRecordState == E_RECORD_STATE_RECORDING)
    {
        #ifdef PVR_8051
        MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
        #endif
        if(UnicodeCmp((S8 *)_pu16RecordFileName, (S8 *)pu16PlaybackFileName)==TRUE)
        {
            #ifdef PVR_8051
            MDrv_Sys_ReleaseXdataWindow1();
            #endif

            _pstPvrRecordPath[u8PathNum]->bLinkPlayback = TRUE;
          //printf("StartPlaybackLinkage \n");
            return TRUE;
        }
        else
        {
            #ifdef PVR_8051
            MDrv_Sys_ReleaseXdataWindow1();
            #endif

            _pstPvrRecordPath[u8PathNum]->bLinkPlayback = FALSE;
          //printf("StopPlaybackLinkage \n");
            return TRUE;
        }
    }
    return FALSE;
}

/***************************************************************************************/
void MApp_Record_GetCurrentFileName(U8 u8PathNum, U16 * u16NameBuffer)
{
    u8PathNum = u8PathNum;  //temp to prevent compiled warning

    #ifdef PVR_8051
    MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
    #endif
    UnicodeCpy((S8 *)u16NameBuffer, (S8 *)_pu16RecordFileName);
    #ifdef PVR_8051
    MDrv_Sys_ReleaseXdataWindow1();
    #endif
}

enPvrEncryptType MApp_Record_GetEncryptionType(U8 u8PathNum)
{
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return E_PVR_ENCRYPTION_NONE;
    }
  //printf("MApp_Record_GetAvgRecordRateKB \n");

    /*[02-1]set pvr record path =======================================================*/
    return _pstPvrRecordPath[u8PathNum]->enEncryptionType;
}

BOOL MApp_Record_SetCicamCheckLevel(U8 u8PathNum, U8 u8CicamCheckLevel)
{
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return FALSE;
    }

    /*[02-1]set pvr record path/ =======================================================*/
    if(u8CicamCheckLevel > _pstPvrRecordPath[u8PathNum]->u8CicamCheckLevel)
    {
        _pstPvrRecordPath[u8PathNum]->u8CicamCheckLevel = u8CicamCheckLevel;
    }
    return TRUE;
}

/***************************************************************************************/
void MApp_Record_ClearCurrentFileName(U8 u8PathNum)
{
    u8PathNum = u8PathNum;  //temp to prevent compiled warning

    #ifdef PVR_8051
    MDrv_Sys_SetXdataWindow1Base(PVR_RECORD_FILENAME_BUFFER_ADR/4096);
    #endif
    _pu16RecordFileName[0] = 0;
    #ifdef PVR_8051
    MDrv_Sys_ReleaseXdataWindow1();
    #endif
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////// record ap (link to audio) /////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void MApp_Record_AudioAddServices(U8 u8PathNum, U8 u8Idx, U8 u8Num)
{
    U8 u8i;
    AUD_INFO AudioStreamInfo;

    _pstPvrRecordPath[u8PathNum]->u8audioLangTotal = u8Num;
    _pstPvrRecordPath[u8PathNum]->u8audioLangSel = u8Idx;

    for(u8i=0 ; u8i < _pstPvrRecordPath[u8PathNum]->u8audioLangTotal ; u8i++)
    {
        #ifdef PVR_8051
        if( E_RESULT_SUCCESS == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
        #else
        if( TRUE == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &AudioStreamInfo, u8i))
        #endif
        {
            msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], AudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO);
            memcpy(&_pstPvrRecordPath[u8PathNum]->PVRAudioInfo[u8i], &AudioStreamInfo, sizeof(AudioStreamInfo));
        }
    }
}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////// record ap (link to subtitle) ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void MApp_Record_SubtitleAddServices(U8 u8PathNum, U8 u8Idx, U8 u8Num, DVB_SUBTITLE_SERVICE* pSubtitleServices)
{
    U8 u8i;

    _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum = u8Num;
    _pstPvrRecordPath[u8PathNum]->u8SubtitleMenuSelectedIdx = u8Idx;

    for ( u8i =0 ; u8i < _pstPvrRecordPath[u8PathNum]->u8DVBSubtitleServiceNum ; u8i++)
    {
        msAPI_PVR_RecordPathAddPID(_pstPvrRecordPath[u8PathNum], pSubtitleServices[u8i].u16PID, MSAPI_DMX_FILTER_TYPE_SUBTITLE);     //<--from other AP:(05) SUBTITLE
        memcpy( _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].StringCodes, pSubtitleServices[u8i].StringCodes, 4);
        _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u16PID                   = pSubtitleServices[u8i].u16PID;
        _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u16Ancillary_Page_id     = pSubtitleServices[u8i].u16Ancillary_Page_id;
        _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u16Composition_Page_id   = pSubtitleServices[u8i].u16Composition_Page_id;
        _pstPvrRecordPath[u8PathNum]->PVRDVBSubtitleServices[u8i].u8SubtitleType           = pSubtitleServices[u8i].u8SubtitleType;
    }
}

/***************************************************************************************/

/*###############################################################################################*/
/*//////////////////////////// record ap (finite state machine) /////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/

#define RECORD_SM_CHECKPOINT()  //PRINT_CURRENT_LINE()

void MApp_Record_StateMachineRunning(void)
{
    #if DEBUG_RECORD_STATE  //=========================================================//
    {
        static U8 preState = 0xFF;
        if(preState != _enRecordState)
        {
            printf("Record [%d]->[%d]\n", (int)preState, (int)_enRecordState);
            preState = _enRecordState;
        }
    }
    #endif  //=========================================================================//

    RECORD_SM_CHECKPOINT();

    switch (_enRecordState)
    {
        /*[01]WAIT state (channel change) =============================================*/
        case E_RECORD_STATE_WAIT:
        {
            RECORD_SM_CHECKPOINT();
            if(_enRecordInput == E_RECORD_INPUT_RECORD_OPEN)
            {
              #if 0//def PVR_8051
                U16   u16RecordExtPara        = (U16        )_u32RecordExtPara;   //type casting
                U16 xdata * pu16RecordExtPara = (U16 xdata *) u16RecordExtPara;   //typp casting
              #else
                U16       * pu16RecordExtPara = (U16       *)_u32RecordExtPara;   //typp casting
              #endif

                U8 u8RecordPathNum;
                if((u8RecordPathNum = MApp_Record_Open(pu16RecordExtPara)) != RECORD_PATH_INVALID)
                {
                    if(MApp_Record_Enable(u8RecordPathNum) == TRUE)
                    {
                      //printf("STCH[[REC]]@WAIT->RECORDING\n");
                        _enRecordState = E_RECORD_STATE_RECORDING;
                        _enRecordInput = E_RECORD_INPUT_NONE;
                    }
                    else
                    {
                    }
                }
                else
                {
                  //printf("STCH[[REC]]@WAIT->WAIT\n");
                  //_enRecordState = E_RECORD_STATE_WAIT;           //<--exception-1
                    printf("\nError: MApp_Record_Open() failed!\n");
                    _enRecordInput = E_RECORD_INPUT_NONE;
                }
            }
            else if(_enRecordInput != E_RECORD_INPUT_NONE)
            {
                MS_DEBUG_MSG(printf("ERROR_INPUT_TO_WAIT\n"));
                _enRecordInput = E_RECORD_INPUT_NONE;
            }
            RECORD_SM_CHECKPOINT();
            break;
        }

        case E_RECORD_STATE_OPEN:
            break;

        /*[02]RECORDING state =========================================================*/
        case E_RECORD_STATE_RECORDING:
        {
            RECORD_SM_CHECKPOINT();
            //printf("[E_RECORD_STATE_RECORDING]\n");
            //printf("_enRecordInput=%u\n",_enRecordInput);
            /*[02-1]record on/off =====================================================*/
            if(_enRecordInput == E_RECORD_INPUT_RECORD_OPEN)
            {
                RECORD_SM_CHECKPOINT();
              #if 0//def PVR_8051
                U16   u16RecordExtPara        = (U16        )_u32RecordExtPara;   //type casting
                U16 xdata * pu16RecordExtPara = (U16 xdata *) u16RecordExtPara;   //typp casting
              #else
                U16       * pu16RecordExtPara = (U16       *)_u32RecordExtPara;   //typp casting
              #endif

                U8 u8RecordPathNum;
                if((u8RecordPathNum = MApp_Record_Open(pu16RecordExtPara)) != RECORD_PATH_INVALID)
                {
                    if(MApp_Record_Enable(u8RecordPathNum) == TRUE)
                    {
                      //printf("STCH[[REC]]@RECORDING->RECORDING\n");
                      //_enRecordState = E_RECORD_STATE_RECORDING;
                        _enRecordInput = E_RECORD_INPUT_NONE;
                    }
                }
                else
                {
                  //printf("STCH[[REC]]@RECORDING->RECORDING\n");
                  //_enRecordState = E_RECORD_STATE_RECORDING;      //<--exception-3
                    _enRecordInput = E_RECORD_INPUT_NONE;
                }
            }
            else if(_enRecordInput == E_RECORD_INPUT_RECORD_CLOSE)
            {
                RECORD_SM_CHECKPOINT();
                MApp_Record_Disable((U8)_u32RecordExtPara);
                MApp_Record_Close((U8)_u32RecordExtPara);

                if(MApp_Record_GetWorkingPathCount()==0)
                {
                    //printf("STCH[[REC]]@RECORDING->WAIT\n");
                    _enRecordState = E_RECORD_STATE_WAIT;
                    _enRecordInput = E_RECORD_INPUT_NONE;
                }
                else
                {
                    //printf("STCH[[REC]]@RECORDING->RECORDING\n");
                    //_enRecordState = E_RECORD_STATE_RECORDING;
                    _enRecordInput = E_RECORD_INPUT_NONE;
                }
            }
            else if(_enRecordInput != E_RECORD_INPUT_NONE)
            {
                RECORD_SM_CHECKPOINT();
                MS_DEBUG_MSG(printf("ERROR_INPUT_TO_RECORDING\n"));
                _enRecordInput = E_RECORD_INPUT_NONE;
            }

            RECORD_SM_CHECKPOINT();

            /*[02-2]record running ====================================================*/
            {
                U8 u8RecordPathNum;

                for(u8RecordPathNum = 0; u8RecordPathNum < PVR_MAX_RECORD_PATH; u8RecordPathNum++)
                {
                    RECORD_SM_CHECKPOINT(); 
                    //printf("u8RecordPathNum=%u\n", u8RecordPathNum);
                    if(!MApp_Record_Routine(u8RecordPathNum))
                    {
                        printf("MApp_Record_Routine() fail => Record Stop!\n");

                        RECORD_SM_CHECKPOINT();
                        for(u8RecordPathNum = 0; u8RecordPathNum < PVR_MAX_RECORD_PATH; u8RecordPathNum++)
                        {
                            if(_pstPvrRecordPath[u8RecordPathNum] != NULL)
                            {
                                MApp_Record_Disable(u8RecordPathNum);
                            }
                        }
                        RECORD_SM_CHECKPOINT();

                      //printf("STCH[[REC]]@RECORDING->STOP\n");
                      //_enRecordState = E_RECORD_STATE_STOP;                 //<--exception-2
                        _enRecordInput = E_RECORD_INPUT_NONE;

                        break;
                    }

                    #if 0 //AP LAYER MONITORING ===============================================//
                    {
                        static U32 u32TimerToDisplay = 0;
                        if(msAPI_Timer_DiffTimeFromNow(u32TimerToDisplay)>=10000)
                        {
                            printf("#############################\n");
                            printf("###[%10lu|%10lu]###\n", MApp_Record_GetStartTimeMs(u8RecordPathNum),
                                                            MApp_Record_GetEndTimeMs(u8RecordPathNum));
                            printf("#############################\n");
                            u32TimerToDisplay = msAPI_Timer_GetTime0();
                        }
                    }
                    #endif //AP LAYER MONITORING ==============================================//
                }

                RECORD_SM_CHECKPOINT();
            }

            break;
        }

        /*[03]STOP state ==============================================================*/
        case E_RECORD_STATE_STOP:
        {
            /*[03-1]record on/off =====================================================*/
            if(_enRecordInput == E_RECORD_INPUT_RECORD_CLOSE)
            {
                RECORD_SM_CHECKPOINT();
                MApp_Record_Close((U8)_u32RecordExtPara);

                if(MApp_Record_GetWorkingPathCount()==0)
                {
                  //printf("STCH[[REC]]@STOP->WAIT\n");
                    _enRecordState = E_RECORD_STATE_WAIT;
                    _enRecordInput = E_RECORD_INPUT_NONE;
                }
                else
                {
                  //printf("STCH[[REC]]@STOP->STOP\n");
                  //_enRecordState = E_RECORD_STATE_STOP;
                    _enRecordInput = E_RECORD_INPUT_NONE;
                }
            }
            else if(_enRecordInput != E_RECORD_INPUT_NONE)
            {
                RECORD_SM_CHECKPOINT();
                MS_DEBUG_MSG(printf("ERROR_INPUT_TO_STOP\n"));
                _enRecordInput = E_RECORD_INPUT_NONE;
            }
            break;
        }
    }

    RECORD_SM_CHECKPOINT();
}

/***************************************************************************************/
void MApp_Record_StateMachineInput(enRecordInput enSMInput, U32 u32ExtParameter)
{
    _enRecordInput      = enSMInput;
    _u32RecordExtPara   = u32ExtParameter;

    switch (_enRecordInput)
    {
        //(1)record open ==============================================================//
        case E_RECORD_INPUT_RECORD_OPEN:
        {
          //printf("E_RECORD_INPUT_RECORD_OPEN\n");
            break;
        }

        //(2)record close =============================================================//
        case E_RECORD_INPUT_RECORD_CLOSE:
        {
          //printf("E_RECORD_INPUT_RECORD_CLOSE\n");
            break;
        }

        //(0)default ==================================================================//
        default:
        {
          //printf("MApp_Record Unknown Input: %x\n", enSMInput);
            break;
        }

        //=============================================================================//
    }

    MApp_Record_StateMachineRunning();

    _enRecordInput      = E_RECORD_INPUT_NONE;      //ensure to consume any input
    _u32RecordExtPara   = 0;                        //ensure to consume any parameter
}

/***************************************************************************************/
enRecordState MApp_Record_StateMachineGet(void)
{
    return _enRecordState;
}

/***************************************************************************************/
enPvrApiStatus  MApp_Record_StatusGet(void)
{
    enPvrApiStatus enRecordStatus = _enRecordStatus;
    _enRecordStatus = E_PVR_API_STATUS_OK;    //read clear
    return enRecordStatus;
}

/***************************************************************************************/

BOOLEAN MApp_Record_GetNextSeqFileName(U16 *u16NewFileName)
{
    U16 StrLen;

    StrLen = UnicodeLen((S8 *)u16NewFileName);

    if(StrLen >= 6)
    {
        if ( (u16NewFileName[StrLen-4] >= (U16)'0' && u16NewFileName[StrLen-4] <= (U16)'9')
          && (u16NewFileName[StrLen-5] >= (U16)'0' && u16NewFileName[StrLen-5] <= (U16)'9')
          && (u16NewFileName[StrLen-6] >= (U16)'0' && u16NewFileName[StrLen-6] <= (U16)'9'))
        {
            u16NewFileName[StrLen-4]++;
            if(u16NewFileName[StrLen-4] > (U16)'9')
            {
                u16NewFileName[StrLen-4] = (U16)'0';
                u16NewFileName[StrLen-5]++;
            }

            if(u16NewFileName[StrLen-5] > (U16)'9')
            {
                u16NewFileName[StrLen-5] = (U16)'0';
                u16NewFileName[StrLen-6]++;
            }
        }
        else
        {
            u16NewFileName[StrLen  ] = (U16)'0';
            u16NewFileName[StrLen+1] = (U16)'0';
            u16NewFileName[StrLen+2] = (U16)'2';
            u16NewFileName[StrLen+3] = (U16)'.';
            u16NewFileName[StrLen+4] = (U16)'t';
            u16NewFileName[StrLen+5] = (U16)'s';
            u16NewFileName[StrLen+6] = 0;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

U32 MApp_Record_GetStartSysTime(U8 u8PathNum)
{
    /*[01]error condition =============================================================*/
    if ((_enRecordState != E_RECORD_STATE_RECORDING) && (_enRecordState != E_RECORD_STATE_STOP))
    {
        return 0;
    }
    if (_pstPvrRecordPath[u8PathNum] == NULL)
    {
        return 0;
    }

    return _pstPvrRecordPath[u8PathNum]->u32RecordedStartSysTime;
}

#else
BOOLEAN code compile_mapp_record;
#endif//ENABLE_PVR
#undef MAPP_RECORD_C

