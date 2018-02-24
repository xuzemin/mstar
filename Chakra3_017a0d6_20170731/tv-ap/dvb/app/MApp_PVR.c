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

#define MAPP_PVR_C

//system
#include "Board.h"                  //For pvr select

#include "debug.h"
//driver
#ifdef PVR_8051
#include "drvUART.h"                //For compiled error
#endif
#include "SysInit.h"                 //For watch dog timer

#if ENABLE_PVR

//api
#include "msAPI_MSDCtrl.h"          //For file system part
#include "msAPI_FCtrl.h"            //For file system part
#include "msAPI_PVRFileSystem.h"    //For file system part
#include "msAPI_Timer.h"            //For timer
#include "msAPI_PVR.h"              //For pvr
#include "msAPI_Player.h"           //For player

//ap
#include "MApp_MassStorage.h"       //For mass storage
#include "MApp_FileBrowser.h"       //For file browser
#include "MApp_SignalMonitor.h"     //For signal check
#include "MApp_TimeShift.h"         //For TimeShift AP
#include "MApp_Record.h"            //For Record AP
#include "MApp_Playback.h"          //For Playback AP
#include "MApp_PVR.h"               //For itself
#include "MApp_ZUI_ACTpvr.h"        //need to be removed from APP layer
#include "MApp_TopStateMachine.h"
//ui <--better not be here
#include "MApp_UiPvr.h"
#ifdef PVR_8051
#include "MApp_UiMenu.h"
#include "MApp_UiMenu2.h"
#else
#include "ZUI_exefunc.h"
#include "MApp_ZUI_Main.h"
#include "MApp_UiMenuDef.h"
#endif

#include "MApp_ZUI_ACTpvr.h"
#include "MApp_Audio.h"
#include "MApp_CIMMI.h"

#define PVRDBG(x)   //MS_DEBUG_MSG(x)
#define POWER_ON_PVR_INIT_DELAY_TIME     15000

/*************************************************************************************************/

/*************************************************************************************************/
static enPVRState       _enPVRState         = E_PVR_STATE_IDLE;         //pvr_state_machine
static enPVRInput       _enPVRInput         = E_PVR_INPUT_NONE;         //pvr_input from outside
static U32              _u32PVRExtPara      = 0;                        //pvr input from outside
static enPvrApiStatus   _enPVRStatus        = E_PVR_API_STATUS_OK;      //pvr_status

/*************************************************************************************************/
#define FAT_AVERAGE_READ_WRITE_KBYTES         0x80 //128 KBytes //need to syn with msAPI_PVRFileSystem.c or refine later
#define FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC 2048 //2048 KBytes/sec //need to syn with msAPI_PVRFileSystem.c or refine later
#define USBRESETCOUNT   2
/*###############################################################################################*/
/*//////////////////////////////// pvr disk ap - (1)disk format /////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static U16 g_u16TotalBulkNum    = 0;
static U8  g_u8EnvId            = INVALID_FS_ENVIRONMENT_INDEX;
static U32 _u32WriteSectorCount = 0;
static U8 _u8USBResetCounter  = 0;
#if BRAZIL_PVR_CC
static U16 _u16CCPID = 0;
#endif
/***************************************************************************************/
BOOLEAN MApp_PVR_SetDiskDriveIndex(U8 u8DriveIndex, BOOLEAN bForceInit)
{
    U8 u8UserBrowserHandle = INVALID_BROWSER_HANDLE;
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

    //printf("MApp_PVR_SetDiskDriveIndex(u8DriveIndex=%u, bForceInit=%u)\n", u8DriveIndex, bForceInit);

    if (u8DriveIndex >= DISK_DRIVE_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_PVRFS_Reset();

    //Check device connection status
    MApp_MassStorage_DeviceChangeStatusCheck();
    MApp_MassStorage_DeviceStatusCheck();

    //Prepare file system
    u8UserBrowserHandle = MApp_FileBrowser_GetEnvironment();
    MApp_FileBrowser_Destroy(u8UserBrowserHandle);
    if(!MApp_MassStorage_DriveConnect(u8DriveIndex))
    {
        PVRDBG(printf("MApp_PVR_SetDiskDriveIndex Connect No Device\n"));
        return FALSE;
    }
    u8UserBrowserHandle = MApp_FileBrowser_Create(u8DriveIndex);
    if(u8UserBrowserHandle == INVALID_BROWSER_HANDLE)
    {
        PVRDBG(printf("MApp_PVR_SetDiskDriveIndex Create File browser Failed\n"));
        return FALSE;
    }

    MsOS_FlushMemory();
    MApp_FileBrowser_SetEnvironment(u8UserBrowserHandle);

    //Set related device index
    if (!msAPI_PVRFS_SetDiskDriveIndex(u8DriveIndex))
        return FALSE;

    if (!msAPI_PVRFS_SetDeviceIndex(MApp_MassStorage_GetDriveDevice(u8DriveIndex)))
        return FALSE;

    // Fix Mantis 0805679_0805571_0854334
    if (bForceInit == TRUE)
    {
        // 0854334
        if (!msAPI_PVRFS_Initial(TRUE))
            return FALSE;
    }
    else
    {
        // 0805679_0805571
        if (!msAPI_PVRFS_Initial(FALSE))
            return FALSE;
    }

#if (ENABLE_BULK_FILE_SYSTEM)
    msAPI_PVRFS_SetDefaultDiskDriveIndex(u8DriveIndex);
#endif

#if 1//ndef PVR_8051
    //MApp_ZUI_ACT_PVR_OpenUI(MENU_PVR_INITIAL);
#endif

#if(ENABLE_PVR_BROWSER)
    MApp_UiPvr_Browser_DeInit();
    MApp_UiPvr_Browser_Init();
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););

    return TRUE;
}

void MApp_PVR_ReleaseEvnId(void)
{
    if(g_u8EnvId != INVALID_FS_ENVIRONMENT_INDEX)
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
    }
}

/***************************************************************************************/
#if 0
U8 MApp_PVR_GetDefaultDiskDriveIndex(void)
{
    U8 u8CurrentDeviceIndex = INVALID_DEVICE_INDEX;
    U8 u8DefaultDiskDriveIndex = INVALID_DRIVE_INDEX;
    U8 u8DeviceStatus = MApp_MassStorage_DeviceConnectionDetect();
    U8 u8TotalDriveNum = 0;
    U8 u8FirstDriveIndex = INVALID_DRIVE_INDEX;
    U8 u8CurrDriveIndex = INVALID_DRIVE_INDEX;
    U8 u8Index = 0;

    if(!(u8DeviceStatus & MS_USB_CONNECTED) && !(u8DeviceStatus & MS_USB2_CONNECTED))
    {
        return INVALID_DRIVE_INDEX;
    }

    u8DefaultDiskDriveIndex = msAPI_PVRFS_GetDefaultDiskDriveIndex();
    if (msAPI_PVRFS_IsFormated(u8DefaultDiskDriveIndex)) //default disk drive is PVR formatted.
    {
        return u8DefaultDiskDriveIndex;
    }

    //Default disk drive is not PVR formatted.
    //Find the 1st PVR formatted drive from current device
    u8CurrentDeviceIndex = MApp_MassStorage_GetCurrentDeviceIndex();
    if (u8DeviceStatus & MS_USB_CONNECTED) ////USB 1
    {
        u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNumPerPort(MSD_PORT_1);
        u8FirstDriveIndex = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_1);
    }
    else if (u8DeviceStatus & MS_USB2_CONNECTED) ////USB 2
    {
        u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNumPerPort(MSD_PORT_2);
        u8FirstDriveIndex = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_2);
    }
#if ENABLE_CARDREADER
    else if (u8DeviceStatus & MS_CREAD_CONNECTED) //Card Reader
    {
        u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNumPerPort(MSD_PORT_0);
        u8FirstDriveIndex = MApp_MassStorage_GetFirstDriveByPort(MSD_PORT_0);
    }
#endif
    else return u8DefaultDiskDriveIndex; //No support

    if (u8TotalDriveNum == 0) //current drive is not formatted
        return u8DefaultDiskDriveIndex;

    while(u8Index < u8TotalDriveNum)
    {
        u8CurrDriveIndex = MApp_MassStorage_GetNextDriveIndexByDevice(u8CurrentDeviceIndex, u8FirstDriveIndex);
        if (msAPI_PVRFS_IsFormated(u8CurrDriveIndex)) //default disk drive is formatted.
        {
            msAPI_PVRFS_SetDefaultDiskDriveIndex(u8CurrDriveIndex); //the drive is formatted, update this drive to be default drive.
            return u8CurrDriveIndex;
        }
        u8Index++;
    }
    msAPI_PVRFS_SetDefaultDiskDriveIndex(0); //no drive is formatted, update default drive.

    return u8DefaultDiskDriveIndex;
}
#endif

/***************************************************************************************/
BOOLEAN MApp_PVR_DiskFormat(EN_PVRFS_FSTYPE ePVRFSFileSystemType)
{
    U8 u8DiskDriveIndex = msAPI_PVRFS_GetDriveIndex();
    U8 u8DeviceIndex = msAPI_PVRFS_GetDeviceIndex();
    BOOLEAN bFlag = msAPI_PVRFS_IsPartitionReady(u8DiskDriveIndex, u8DeviceIndex);
    BOOLEAN bFinished = FALSE;
    MSDCtrl_Drive  target_drive;

    memset(&target_drive,0,sizeof(MSDCtrl_Drive));

    g_u16TotalBulkNum = 0;
    g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;

    //Partition is not ready.
    if (!bFlag)
    {
        __ASSERT(0);
        return FALSE;
    }
     if(!msAPI_FCtrl_GetDriveByIndex(u8DiskDriveIndex, &target_drive) ||
                    target_drive.DeviceIndex!=u8DeviceIndex)
    {
                __ASSERT(0);
                return FALSE;
    }

    PVRDBG(printf("\n[BulkFileSystem]##Start Preparing, DiskDriveIndex=%u, partitionNO=%d, DeviceIndex=%u\n",
                                              u8DiskDriveIndex, target_drive.PartitionNo, u8DeviceIndex));
    PVRDBG(printf("Formatting...\n"));
#if(WATCH_DOG == ENABLE )
    MDrv_Sys_DisableWatchDog();
#endif

    _u32WriteSectorCount = 0;
#ifdef OBAMA
    if (msAPI_PVRFS_Format(ePVRFSFileSystemType, msAPI_PVRFS_GetDriveIndex()))
    {
        while (!bFinished)
        {
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_PVR_FORMAT_PROGRESS);
            if (msAPI_PVRFS_GetFormatPercentage() == 100)
                bFinished = TRUE;
        }
    }
    else
    {
        __ASSERT(0);
        return FALSE;
    }
#else
    msAPI_PVRFS_SetFileSystemType(ePVRFSFileSystemType);
    while (!bFinished)
    {
        #ifdef PVR_8051
        MApp_UiMenu_PVR_CheckFS_UpdateUI();
        #else
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_PVR_FORMAT_PROGRESS);
        #endif
        if (!msAPI_PVRFS_Format(target_drive.u32MBRLogicBlockAddress, target_drive.u8IndexInMBR, &_u32WriteSectorCount, &bFinished))
        {
            __ASSERT(0);
            return FALSE;
        }
    }
#endif
    msAPI_MSDCtrl_ResetDevice(u8DeviceIndex);
    //Re-Check device since the disk is formated.
    msAPI_MSDCtrl_CheckDevices();
    if (!msAPI_FCtrl_ActiveDevice(u8DeviceIndex))
    {
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }

    g_u8EnvId = msAPI_FSEnv_Register(u8DiskDriveIndex);
    if (g_u8EnvId >= FS_ENVIRONMENT_NUM)
    {
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }
    PVRDBG(printf("    Format Finished\n"));
#if(WATCH_DOG == ENABLE )
    MDrv_Sys_EnableWatchDog();
#endif
    MS_DEBUG_MSG(printf("Finish Formatting...\n"));

    return TRUE;
}

/***************************************************************************************/
#if (ENABLE_BULK_FILE_SYSTEM)
BOOLEAN MApp_PVR_DiskFormatCreateFolder(void)
{
    U8 u8DiskDriveIndex = msAPI_PVRFS_GetDriveIndex();

    msAPI_PVRFS_CreateBulks(EN_CREATE_BULKS_INIT, g_u8EnvId, 0); //Init parameters of bulks
    //After EN_CREATE_BULKS_INIT, the "CreateBulksState" should be "EN_CREATE_BULKS_CREATEFOLDER"
    if (msAPI_PVRFS_GetCreateBulksState() != EN_CREATE_BULKS_CREATEFOLDER)
    {
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        return FALSE;
    }

    //Check if g_u8EnvId is valid, if not, check device and register again.
    if (g_u8EnvId >= FS_ENVIRONMENT_NUM)
    {
        g_u8EnvId = msAPI_FSEnv_Register(u8DiskDriveIndex);
        if (g_u8EnvId >= FS_ENVIRONMENT_NUM)
        {
            g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
            __ASSERT(0);
            return FALSE;
        }
    }

    //Change to root directory to create bulk forder
    if (!msAPI_FCtrl_DirectoryChangeToRoot(g_u8EnvId))
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }

    if (!msAPI_FCtrl_EntryFirst(g_u8EnvId))
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }
#if(WATCH_DOG == ENABLE )
    MDrv_Sys_DisableWatchDog();
#endif
    PVRDBG(printf("    Creating Folder...\n"));
    //Start to create bulk folder
    if (!msAPI_PVRFS_CreateBulks(EN_CREATE_BULKS_CREATEFOLDER, g_u8EnvId, 0))
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }
#if(WATCH_DOG == ENABLE )
    MDrv_Sys_EnableWatchDog();
#endif
    return TRUE;
}

/***************************************************************************************/
BOOLEAN MApp_PVR_DiskFormatCreateBulks(BOOLEAN *bFinished)
{
    U8 u8DiskDriveIndex = msAPI_PVRFS_GetDriveIndex();

    if (msAPI_PVRFS_GetCreateBulksState() != EN_CREATE_BULKS_CREATEBULKS)
    {
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        return FALSE;
    }

    //Check if g_u8EnvId is valid, if not, check device and register again.
    if (g_u8EnvId >= FS_ENVIRONMENT_NUM)
    {
        g_u8EnvId = msAPI_FSEnv_Register(u8DiskDriveIndex);
        if (g_u8EnvId >= FS_ENVIRONMENT_NUM)
        {
            g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
            __ASSERT(0);
            return FALSE;
        }
    }
#if(WATCH_DOG == ENABLE )
    MDrv_Sys_DisableWatchDog();
#endif
    if (msAPI_PVRFS_CreateBulks(EN_CREATE_BULKS_CREATEBULKS, g_u8EnvId, &g_u16TotalBulkNum))
    {
        if(msAPI_PVRFS_GetCreateBulksState() == EN_CREATE_BULKS_CREATEINDEX)
            *bFinished = TRUE;
        else *bFinished = FALSE;
    }
    else
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }
#if(WATCH_DOG == ENABLE )
    MDrv_Sys_EnableWatchDog();
#endif
    if(msAPI_PVRFS_GetCurrentCreateBulkNum()>0 &&(msAPI_PVRFS_GetCurrentCreateBulkNum()<=msAPI_PVRFS_GetBulksNumToCreate()))
    {
        #ifdef PVR_8051
        MApp_UiMenu_PVR_CreateFileSystemProgress();
        #else
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_PVR_FORMAT_PROGRESS);
        #endif
        PVRDBG(printf("Percentage : %d [%d][%d]\n",(U16)((msAPI_PVRFS_GetCurrentCreateBulkNum()*100)/msAPI_PVRFS_GetBulksNumToCreate()),msAPI_PVRFS_GetCurrentCreateBulkNum(),msAPI_PVRFS_GetBulksNumToCreate()));
    }
    return TRUE;
}

/***************************************************************************************/
BOOLEAN MApp_PVR_DiskFormatCreateIndexFile(void)
{
    U8 u8DiskDriveIndex = msAPI_PVRFS_GetDriveIndex();

    if (msAPI_PVRFS_GetCreateBulksState() != EN_CREATE_BULKS_CREATEINDEX)
    {
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        return FALSE;
    }

    //Check if g_u8EnvId is valid, if not, check device and register again.
    if (g_u8EnvId >= FS_ENVIRONMENT_NUM)
    {
        g_u8EnvId = msAPI_FSEnv_Register(u8DiskDriveIndex);
        if (g_u8EnvId >= FS_ENVIRONMENT_NUM)
        {
            g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
            __ASSERT(0);
            return FALSE;
        }
    }

#if(WATCH_DOG == ENABLE )
    MDrv_Sys_DisableWatchDog();
#endif

    if (!msAPI_PVRFS_CreateBulks(EN_CREATE_BULKS_CREATEINDEX, g_u8EnvId, &g_u16TotalBulkNum))
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }
    if (!msAPI_PVRFS_CreateBulks(EN_CREATE_BULKS_CREATEEPG, g_u8EnvId, &g_u16TotalBulkNum))
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }
#if(WATCH_DOG == ENABLE )
    MDrv_Sys_EnableWatchDog();
#endif
    msAPI_PVRFS_SetCreateBulksState(EN_CREATE_BULKS_INIT);
    PVRDBG(printf("    ReInital BKFS ...\n"));

    if(!msAPI_PVRFS_Initial(TRUE))
    {
        msAPI_FSEnv_UnRegister(g_u8EnvId);
        g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
        __ASSERT(0);
        return FALSE;
    }
    PVRDBG(printf("    ReInital BKFS Done !...\n"));

    PVRDBG(printf("    Check format status ...\n"));
    if(msAPI_PVRFS_IsFormated(u8DiskDriveIndex))
    {
        PVRDBG(printf("    Check format status DONE !...\n"));
    }
    else
    {
        PVRDBG(printf("    Check format status Fail !...\n"));
    }
    PVRDBG(printf("[BulkFileSystem]##Finish Preparing\n"));

    msAPI_FSEnv_UnRegister(g_u8EnvId);
    g_u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;

    return TRUE;
}
#endif

/***************************************************************************************/
U8 MApp_PVR_DiskFormatGetPercentage(void)
{   //progress of MApp_PVR_DiskFormat()
#ifdef OBAMA
    return msAPI_PVRFS_GetFormatPercentage();
#else
#if (ENABLE_BULK_FILE_SYSTEM)
    U32 total  = msAPI_PVRFS_GetFATFormatWriteCnt(msAPI_PVRFS_GetDriveIndex());
    if(total > 0)
    {
        return (_u32WriteSectorCount*100/total);
    }
#endif
#endif
    return 0;
}

/***************************************************************************************/
#if (ENABLE_BULK_FILE_SYSTEM)
U8 MApp_PVR_DiskFormatGetCreateFilePercentage(void)
{   //progress of MApp_PVR_DiskFormatCreateFolder(), MApp_PVR_DiskFormatCreateBulks(), MApp_PVR_DiskFormatCreateIndexFile()
    U8 percentage = 0;
    if (msAPI_PVRFS_GetBulksNumToCreate())
        percentage = (((U32)msAPI_PVRFS_GetCurrentCreateBulkNum()*100)/msAPI_PVRFS_GetBulksNumToCreate());
    if(percentage > 100)
    {
        percentage = 0;
    }
    return percentage;
}
#endif
/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////// pvr disk ap - (2)disk size //////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U32 MApp_PVR_DiskGetAvailableSizeMB(void)
{
    U8  u8DiskDriveIndex = msAPI_PVRFS_GetDriveIndex();
    U8  u8EnvId = FS_ENVIRONMENT_NUM;
    U32 u32AvailableDiskSizeMB = 0;

    u8EnvId = msAPI_FSEnv_Register(u8DiskDriveIndex);
    //Check if g_u8EnvId is valid, if not, check device and register again.
    if (u8EnvId >= FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return 0;
    }

    u32AvailableDiskSizeMB = msAPI_PVRFS_GetAvailableDiskSizeMB(u8EnvId);

    msAPI_FSEnv_UnRegister(u8EnvId);
    u8EnvId = INVALID_FS_ENVIRONMENT_INDEX;
    return u32AvailableDiskSizeMB;
}

/***************************************************************************************/

/*###############################################################################################*/
/*//////////////////////////////// pvr disk ap - (3)disk speed ///////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
U16 MApp_PVR_DiskCheckSpeed(void)
{
    U16 u16Speed = 0;
#if (ENABLE_BULK_FILE_SYSTEM) //temp solution
    u16Speed = msAPI_PVRFS_SpeedCheck();
#endif
    return u16Speed;
}

/***************************************************************************************/
U16 MApp_PVR_DiskGetSpeed(void)
{
    U16 u16Speed = 0;

    if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
    {
        #if (ENABLE_BULK_FILE_SYSTEM)
        u16Speed = msAPI_PVRFS_GetBulkSpeed();
        #endif
    }
    else
    {
        if (msAPI_PVRFS_IsInitialized())
        {
            u16Speed = g_u16DiskSpeed;//FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC;
        }
    }
    return u16Speed;
}

/***************************************************************************************/
BOOLEAN MApp_PVR_DiskSetSpeed(U16 newSpeed)
{
#if (ENABLE_BULK_FILE_SYSTEM) //temp solution
    BOOLEAN bResult = FALSE;

    bResult = msAPI_PVRFS_SetBulkSpeed(newSpeed);
    return bResult;
#else
    newSpeed = newSpeed;
    return TRUE;
#endif
}

/***************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////// pvr disk ap - (4)timeshift related //////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
BOOLEAN MApp_PVR_TimeShiftSetRecordLengthMB(U32 u32TimeShiftRecordLengthMB)
{
#if (ENABLE_BULK_FILE_SYSTEM) //temp solution
    BOOLEAN bResult = FALSE;
    bResult = msAPI_PVRFS_SetTimeShiftRecordLengthMB(u32TimeShiftRecordLengthMB);
    return bResult;
#else
    u32TimeShiftRecordLengthMB = u32TimeShiftRecordLengthMB;
    return FALSE;
#endif
}

/***************************************************************************************/
U32 MApp_PVR_TimeShiftGetRecordLengthMB(void)
{
#if (ENABLE_BULK_FILE_SYSTEM) //temp solution
    U32 u32TimeShiftRecordLengthMB = 0;

    u32TimeShiftRecordLengthMB = msAPI_PVRFS_GetTimeShiftRecordLengthMB();
    return u32TimeShiftRecordLengthMB;
#else
    return 0;
#endif
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////// pvr (DTV ap related) //////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
BOOLEAN MApp_PVR_IsVideoFrameCountStillIncrease(void)
{
    #define READ_LENGTH_UNIT        3
    #define WAIT_VIDPICCOUNT_TIME   2
    static U8 u8Cnt;
    static U32 u32FrameCnt = 0, u32Timer;

    if(u32FrameCnt != msAPI_Player_VideoGetPicCount())
    {
        u32FrameCnt = msAPI_Player_VideoGetPicCount();
        u8Cnt = 0;
    }
    else
    {
        u8Cnt++;
        if(u8Cnt == WAIT_VIDPICCOUNT_TIME)
        {
            u32Timer = msAPI_Timer_GetTime0();
        }
    }
    if((u8Cnt >= WAIT_VIDPICCOUNT_TIME) && msAPI_Timer_DiffTimeFromNow(u32Timer) > 1000)
    {
        u32FrameCnt = 0;
        u8Cnt = 0;
        u32Timer = 0;
      //printf("TS switch to normal mode\n");
        return FALSE;
    }
    return TRUE;
}

/***************************************************************************************/
BOOLEAN MApp_PVR_IsSystemReady(void)
{
    return
    ((_enPVRState != E_PVR_STATE_IDLE) &&
     (_enPVRState != E_PVR_STATE_INIT) &&
     (_enPVRState != E_PVR_STATE_WAITFORMAT));
}

/***************************************************************************************/
BOOLEAN MApp_PVR_IsFileFormatCheckFail(void)
{
#if (ENABLE_BULK_FILE_SYSTEM) //temp solution
    return (((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) ||
             (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED) ||
             (MApp_MassStorage_DeviceConnectionDetect() & MS_USB3_CONNECTED)||
             (MApp_MassStorage_DeviceConnectionDetect() & MS_USB4_CONNECTED)) &&
             !(msAPI_PVRFS_IsFormated( msAPI_PVRFS_GetDriveIndex() ) && (msAPI_PVRFS_GetBulkSpeed() > 0)));
#else
    return (((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) ||
             (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED) ||
             (MApp_MassStorage_DeviceConnectionDetect() & MS_USB3_CONNECTED) ||
             (MApp_MassStorage_DeviceConnectionDetect() & MS_USB4_CONNECTED)) &&
             !(msAPI_PVRFS_IsFormated( msAPI_PVRFS_GetDriveIndex() ) ));
#endif
}

/***************************************************************************************/
BOOLEAN MApp_PVR_IsFileFormatVersionChanged(void)
{
#if (ENABLE_BULK_FILE_SYSTEM) //temp solution
    return (((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED)
              ||(MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED)
              ||(MApp_MassStorage_DeviceConnectionDetect() & MS_USB3_CONNECTED)
              ||(MApp_MassStorage_DeviceConnectionDetect() & MS_USB4_CONNECTED))
                    && (msAPI_PVRFS_isBulkVersionChanged() == BKF_VERCHK_DIFFERENT_VERSION));
#else
    return FALSE;
#endif
}

void MApp_PVR_GetPlaybackFileName(U16 * u16NameBuffer)
{
    if(((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     ((MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PAUSE)))
    {
        MApp_Playback_GetCurrentFileName(u16NameBuffer);
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
      (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING          )))
    {
        MApp_TimeShift_GetFileName(u16NameBuffer);
    }
}

void MApp_PVR_GetRecordFileName(U16 * u16NameBuffer)
{
    if(((_enPVRState == E_PVR_STATE_RECORD) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     (MApp_Record_StateMachineGet() == E_RECORD_STATE_RECORDING))
    {
        MApp_Record_GetCurrentFileName(RECORD_PATH_DEFAULT,u16NameBuffer);
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
     (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDING)))
    {
        MApp_TimeShift_GetFileName(u16NameBuffer);
    }
}

U32 MApp_PVR_GetRecordStartSysTime(void)
{
    if(((_enPVRState == E_PVR_STATE_RECORD) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     (MApp_Record_StateMachineGet() == E_RECORD_STATE_RECORDING))
    {
        return MApp_Record_GetStartSysTime(RECORD_PATH_DEFAULT);
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
     (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDING)))
    {
        return MApp_TimeShift_GetStartSysTime();
    }
    else if(((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     ((MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PAUSE)))
    {
        return MApp_Playback_GetStartSysTime();
    }
    return 0;
}

U32 MApp_PVR_GetCurRecordTimeInSec(void)
{
    if(((_enPVRState == E_PVR_STATE_RECORD) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     (MApp_Record_StateMachineGet() == E_RECORD_STATE_RECORDING))
    {
        return MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT);
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
     (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDING)))
    {
        return MApp_TimeShift_GetRecordEndTimeSec() - MApp_TimeShift_GetRecordStartTimeSec();
    }
    return 0;
}

U32 MApp_PVR_GetDurationTime(void)
{
    if(((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     ((MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PAUSE)))
    {
        return MApp_Playback_GetTotalTimeSec();
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
      (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING          )))
    {
        return MApp_TimeShift_GetRecordEndTimeSec();
    }
    return 0;
}

U32 MApp_PVR_GetPlaybackTimeSec(void)
{
    if(((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     ((MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PAUSE)))
    {
        return MApp_Playback_GetPlaybackTimeSec();
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
      (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING          )))
    {
        return MApp_TimeShift_GetPlaybackTimeSec();
    }
    return 0;
}

enPvrEncryptType MApp_PVR_GetEncryptionType(void)
{
    if(((_enPVRState == E_PVR_STATE_RECORD) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     (MApp_Record_StateMachineGet() == E_RECORD_STATE_RECORDING))
    {
        return MApp_Record_GetEncryptionType(RECORD_PATH_DEFAULT);
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
     (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDING) ||
     (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING )))
    {
        return MApp_TimeShift_GetEncryptionType();
    }
    else if(((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     ((MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PAUSE)))
    {
        return MApp_Playback_GetEncryptionType();
    }
    return E_PVR_ENCRYPTION_NONE;
}

BOOL MApp_PVR_SetCicamCheckLevel(U8 u8CicamCheckLevel)
{
    if(((_enPVRState == E_PVR_STATE_RECORD) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     (MApp_Record_StateMachineGet() == E_RECORD_STATE_RECORDING))
    {
        return MApp_Record_SetCicamCheckLevel(RECORD_PATH_DEFAULT,u8CicamCheckLevel);
    }
    else if((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
     (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDING)))
    {
        return MApp_TimeShift_SetCicamCheckLevel(u8CicamCheckLevel);
    }
    return FALSE;
}

/***************************************************************************************/
BOOLEAN MApp_PVR_IsPlaybacking(void)
{
    return
    (((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     ((MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTFORWARD ) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_FASTBACKWARD) ||
      (MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PAUSE       )))
    ||
    ((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
      (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING          )));
}
BOOLEAN MApp_PVR_IsPVRStatePlaybacking(void)
{
    if((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK) ||(_enPVRState == E_PVR_STATE_TIMESHIFT) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/***************************************************************************************/
BOOLEAN MApp_PVR_IsRecording(void)
{
    return
    (((_enPVRState == E_PVR_STATE_RECORD) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK)) &&
     (MApp_Record_StateMachineGet() == E_RECORD_STATE_RECORDING))
    ||
    ((_enPVRState == E_PVR_STATE_TIMESHIFT) &&
     ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) ||
     (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDING)));
}

/***************************************************************************************/
BOOL MApp_PVR_GetRecordCAPVR(void)
{
    return msAPI_PVR_GetRecordCAPVR();
}

/***************************************************************************************/
BOOLEAN MApp_PVR_IsFastPlaybacking(void)
{
    return
    (  ((E_PVR_STATE_PLAYBACK == _enPVRState || E_PVR_STATE_RECORDnPLAYBACK == _enPVRState)
                && (E_PLAYBACK_STATE_FASTFORWARD == MApp_Playback_StateMachineGet() || E_PLAYBACK_STATE_FASTBACKWARD == MApp_Playback_StateMachineGet()))
    ||(E_PVR_STATE_TIMESHIFT == _enPVRState
                && (E_TIMESHIFT_STATE_PLAYBACKING == MApp_TimeShift_StateMachineGet() || E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING == MApp_TimeShift_StateMachineGet())
                && (MApp_TimeShift_IfFastForward() || MApp_TimeShift_IfFastBackward())));
}

BOOLEAN MApp_PVR_IsFastBackwardPlaybacking(void)
{
    return
    (((E_PVR_STATE_PLAYBACK == _enPVRState || E_PVR_STATE_RECORDnPLAYBACK == _enPVRState)
                && (E_PLAYBACK_STATE_FASTBACKWARD == MApp_Playback_StateMachineGet()))
    ||(E_PVR_STATE_TIMESHIFT == _enPVRState
                && (E_TIMESHIFT_STATE_PLAYBACKING == MApp_TimeShift_StateMachineGet() || E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING == MApp_TimeShift_StateMachineGet())
                && (MApp_TimeShift_IfFastBackward())));
}

/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////////////// pvr audio related //////////////////////////////////////*/
/*###############################################################################################*/

/******************************************************************************/
/// Public function: Add audio pid to record path
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_RecordAudioAddServices(U8 u8PathNum, U8 u8Idx, U8 u8Num)
{
    MApp_Record_AudioAddServices(u8PathNum, u8Idx, u8Num);
}

/******************************************************************************/
/// Public function: Return the recorded selected audio service
/// @param
/// @return
/******************************************************************************/
U8 MApp_PVR_PlaybackAudioGetLanguageSelection(void)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        return MApp_Playback_AudioGetLanguageSelection();
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        return MApp_TimeShift_AudioGetLanguageSelection();
    }
    else
    {
        return 0;
    }
}

/******************************************************************************/
/// Public function: Return total available audio language options.
/// @param
/// @return
/******************************************************************************/
U8 MApp_PVR_PlaybackAudioGetLanguageTotal(void)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        return MApp_Playback_AudioGetLanguageTotal();
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        return MApp_TimeShift_AudioGetLanguageTotal();
    }
    else
    {
        return 0;
    }
}

/******************************************************************************/
/// Public function: Return the audio info
/// @param
/// @return
/******************************************************************************/
BYTE MApp_PVR_PlaybackAudioGetLanguageInfo(void)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        return MApp_Playback_AudioGetLanguageInfo();
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        return MApp_TimeShift_AudioGetLanguageInfo();
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************/
/// Public function: Return the audio info
/// @param
/// @return
/******************************************************************************/
BOOLEAN MApp_PVR_PlaybackAudioGetStreamInfo(AUD_INFO* pstAudioStreamInfo, U8 u8Idx)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        return MApp_Playback_AudioGetStreamInfo(pstAudioStreamInfo, u8Idx);
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        return MApp_TimeShift_AudioGetStreamInfo(pstAudioStreamInfo, u8Idx);
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************/
/// Public function: Set playback audio language
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_PlaybackAudioSelectLanguage(U8 u8AudSelectedIndex)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        MApp_Playback_AudioSelectLanguage(u8AudSelectedIndex);
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        MApp_TimeShift_AudioSelectLanguage(u8AudSelectedIndex);
    }
}

/******************************************************************************/
/// Public function: Stop playback audio language
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_PlaybackAudioStopLanguage(U8 u8AudSelectedIndex)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        MApp_Playback_AudioStopLanguage(u8AudSelectedIndex);
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        MApp_TimeShift_AudioStopLanguage(u8AudSelectedIndex);
    }
}


/******************************************************************************/
/// Public function: Set playback AD audio language
/// @param
/// @return
/******************************************************************************/
#ifndef S3PLUS
void MApp_PVR_PlaybackAdAudioSelectLanguage(U8 u8AudSelectedIndex)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        MApp_Playback_AdAudioSelectLanguage(u8AudSelectedIndex);
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        MApp_TimeShift_AdAudioSelectLanguage(u8AudSelectedIndex);
    }
}

/******************************************************************************/
/// Public function: Stop playback AD audio language
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_PlaybackAdAudioStopLanguage(U8 u8AudSelectedIndex)
{
    if ((_enPVRState == E_PVR_STATE_PLAYBACK) || (_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
    {
        MApp_Playback_AdAudioStopLanguage(u8AudSelectedIndex);
    }
    else if (_enPVRState == E_PVR_STATE_TIMESHIFT)
    {
        MApp_TimeShift_AdAudioStopLanguage(u8AudSelectedIndex);
    }
}
#endif
/******************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////////// pvr subtitle related ////////////////////////////////////*/
/*###############################################################################################*/

/******************************************************************************/
/// Public function: Add subtitle pid to record path
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_RecordSubtitleAddServices(U8 u8PathNum, U8 u8Idx, U8 u8Num, DVB_SUBTITLE_SERVICE* pSubtitleServices)
{
    MApp_Record_SubtitleAddServices(u8PathNum, u8Idx, u8Num, pSubtitleServices);
}

/******************************************************************************/
/// Public function: Load the subtitle menu from record path
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_PlaybackSubtitleLoadServices(U8* pu8SelIdx, U8* pu8Num, DVB_SUBTITLE_SERVICE* pSubtitleServices)
{
    if ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) || (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING))
    {
        MApp_TimeShift_Subtitle_LoadServices(pu8SelIdx, pu8Num, pSubtitleServices);
    }
    else if(MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING)
    {
        MApp_Playback_Subtitle_LoadServices(pu8SelIdx, pu8Num, pSubtitleServices);
    }
}

/******************************************************************************/
/// Public function: Load the subtitle menu from record path
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_PlaybackSubtitleLoadMenu(U8* pu8SelIdx, U8* pu8Num, SUBTITLE_MENU* pSubtitleServices, U8* pu8fEnableSubtitle, U8* pu8fEnableTTXSubtitle)
{
    if ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) || (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING))
    {
        MApp_TimeShift_Subtitle_LoadMenu(pu8SelIdx, pu8Num, pSubtitleServices, pu8fEnableSubtitle, pu8fEnableTTXSubtitle);
    }
    else if(MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING)
    {
        MApp_Playback_Subtitle_LoadMenu(pu8SelIdx, pu8Num, pSubtitleServices, pu8fEnableSubtitle, pu8fEnableTTXSubtitle);
    }
}

/******************************************************************************/
/// Public function: Return the TTX subtitle number from record path
/// @param
/// @return
/******************************************************************************/
void MApp_PVR_PlaybackGetTTXSubtitleNum(U8* pu8Num)
{
    if ((MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING) || (MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_PLAYBACKING))
    {
        MApp_TimeShift_TTXSubtitle_GetNum(pu8Num);
    }
    else if(MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING)
    {
        MApp_Playback_TTXSubtitle_GetNum(pu8Num);
    }
}
#if BRAZIL_PVR_CC
U16 MApp_PVR_Playback_GetCCPID(void)
{
    return _u16CCPID;
}
void MApp_PVR_Playback_SetCCPID(U16 u16PID)
{
    _u16CCPID = u16PID;
}
#endif
/******************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////////// pvr state machine ///////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/

#if ((ENABLE_CI_PLUS == 1) && (!ENABLE_CIPLUS_PVR))
MS_BOOL bIsURIBlock = FALSE;
#endif

extern BOOLEAN u8DMPStartFlag;
#define DEBUG_PVR_SM_TIME()     //printf("PVR:%u %u\n", __LINE__, MsOS_GetSystemTime());
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
extern BOOLEAN     g_bTimerTypeRecord;
#endif

#define DEBUG_PVR_STATE_1   0

#define DEBUG_PVR_STATE(x)  //x

#define PVR_SM_CHECKPOINT()     //PRINT_CURRENT_LINE()

void MApp_PVR_StateMachineRunning(void)
{
    U32 u32Time1 = MsOS_GetSystemTime();

    #if DEBUG_PVR_STATE_1 //=============================================================//
    {
        static U8 preState = 0xFF;
        if(preState != _enPVRState)
        {
            printf("PVR [%u]->[%u]\n", preState, _enPVRState);
            preState = _enPVRState;
        }
    }
    #endif  //=========================================================================//

    PVR_SM_CHECKPOINT();

    // if AD on, open it in playback and record&playback state
    {
        static U8 preADState = 0xFF;
        if(preADState != _enPVRState)
        {
            preADState = _enPVRState;

            if((_enPVRState == E_PVR_STATE_PLAYBACK)||(_enPVRState == E_PVR_STATE_RECORDnPLAYBACK))
            {
            #if(ENABLE_DVB_AUDIO_DESC)
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

                    // if ad exist
                    if (g_u8AdAudSelected != 0xFF)
                    {
                        MApp_Audio_SetAdAudio(g_u8AdAudSelected);
                        MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);
                        MApp_Audio_AdjustADVolume(stGenSetting.g_SoundSetting.ADVolume);
                    }
                }
            #endif
            }
        }
    }

    PVR_SM_CHECKPOINT();

/*Fix : URI protect PVR function*/
#if ((ENABLE_CI_PLUS == 1) && (!ENABLE_CIPLUS_PVR))
    if(msAPI_CI_CardDetect() && (EN_CI_VERSION_CI_PLUS == msAPI_CI_CC_CAM_Mode()))
    {
        MEMBER_SERVICETYPE bServiceType;
        WORD wProgramPositon;
        U8 u8URI_RCT = 0, u8URI_EMI = 0, u8URI_APS = 0, u8URI_ICT = 0, u8URI_RL = 0;
        msAPI_CI_CC_GetURI(&u8URI_RCT, &u8URI_EMI, &u8URI_APS, &u8URI_ICT, &u8URI_RL);
        wProgramPositon = msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType());
        bServiceType = msAPI_CM_GetCurrentServiceType();
        EN_CC_CICAM_PIN_CAPABILITIES eCicamPinCap = msAPI_CI_CC_GetCicamPinCapability();
        if( (_enPVRState != E_PVR_STATE_PLAYBACK) && (( 0x00 != u8URI_EMI )||( EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY_CACHED == eCicamPinCap )||( EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN_CACHED == eCicamPinCap ))
          && msAPI_CM_GetProgramAttribute(bServiceType, wProgramPositon, E_ATTRIBUTE_IS_SCRAMBLED) )
        {
            switch(_enPVRState)
            {
                case E_PVR_STATE_TIMESHIFT:
                {
                    MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_PLAYBACK_CLOSE, _u32PVRExtPara);
                    MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_RECORD_CLOSE, _u32PVRExtPara);

                    _enPVRState = E_PVR_STATE_WAIT;
                    _enPVRStatus = E_PVR_API_STATUS_PROTECTION;

                    break;
                }
                case E_PVR_STATE_RECORD:
                {

                    if(MApp_PvrBrowser_IsAnyFileRecording())
                    {
                        U32 recTime = (MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT));
                        MApp_PvrBrowser_GetRecordingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)CHAR_BUFFER, RECORD_NAME_LENGTH*2);
                        MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_PROGRAM_DURATION, (U16*)CHAR_BUFFER, (BYTE*)&recTime);
                        MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, NULL, NULL);
                    }
                    MApp_Record_StateMachineInput(E_RECORD_INPUT_RECORD_CLOSE, _u32PVRExtPara);

                    _enPVRState = E_PVR_STATE_WAIT;
                    _enPVRStatus = E_PVR_API_STATUS_PROTECTION;
                    break;
                }
                case E_PVR_STATE_RECORDnPLAYBACK:
                {

                    if(MApp_PvrBrowser_IsAnyFileRecording())
                    {
                    U32 recTime = (MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT));
                    MApp_PvrBrowser_GetRecordingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)CHAR_BUFFER, RECORD_NAME_LENGTH*2);
                    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_PROGRAM_DURATION, (U16*)CHAR_BUFFER, (BYTE*)&recTime);
                    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, NULL, NULL);
                    }
                    if(MApp_PvrBrowser_IsAnyFilePlaying()) //for record&play case
                    {
                    MApp_PvrBrowser_GetPlayingAttribute(E_PVR_ATTR_FILE_NAME, (BYTE*)CHAR_BUFFER, RECORD_NAME_LENGTH*2);
                    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, NULL, NULL);
                    }
                    MApp_Record_StateMachineInput(E_RECORD_INPUT_RECORD_CLOSE, _u32PVRExtPara);

                    _enPVRState = E_PVR_STATE_PLAYBACK;
                    _enPVRStatus = E_PVR_API_STATUS_PROTECTION;
                    break;
                }

                default:
                break;
            }

            bIsURIBlock = TRUE;
        }
        else
            bIsURIBlock = FALSE;

     }

#endif

    PVR_SM_CHECKPOINT();
    DEBUG_PVR_SM_TIME();
    //printf("_enPVRState=%u\n", _enPVRState);

    switch(_enPVRState)
    {
        case E_PVR_STATE_IDLE:
        {
            DEBUG_PVR_SM_TIME();
#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
         // To speed up power on time, two cases to avoid connect USB because it waste time.
         // First case, show up video ok, then you can connect USB by check flag gbBootTimeFinish.
         // Second case, if no signal, the gbBootTimeFinish flag will not true, so wait 15 secs.
			if ((!gbBootTimeFinish) && (msAPI_Timer_DiffTimeFromNow(gU32BootTime)<POWER_ON_PVR_INIT_DELAY_TIME))
				break;
#endif
             U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();

            //DEBUG_PVR_SM_TIME();
            if (_enPVRInput == E_PVR_INPUT_RECORD_CLOSE)
                break;

            PVR_SM_CHECKPOINT();

            if((u8USBState & MS_USB_CONNECTED) \
            || (u8USBState & MS_USB2_CONNECTED) \
            ||(u8USBState & MS_USB3_CONNECTED) \
            ||(u8USBState & MS_USB4_CONNECTED))
            {
                if(u8USBState & MS_USB_CONNECTED)
                g_u8PVRActiveDevice = MSD_USB_INDEX_START;
                else if(u8USBState & MS_USB2_CONNECTED)
                g_u8PVRActiveDevice = MSD_USB_2_INDEX_START;
                else if(u8USBState & MS_USB3_CONNECTED)
                g_u8PVRActiveDevice = MSD_USB_3_INDEX_START;
                else if(u8USBState & MS_USB4_CONNECTED)
                g_u8PVRActiveDevice = MSD_USB_4_INDEX_START;

            #ifdef PVR_8051
                MApp_UiMenu_PVR_Initial_Warning_Open();  //show UI first
            #else
            #endif

                //DEBUG_PVR_SM_TIME();
                PVR_SM_CHECKPOINT();
                msAPI_PVRFS_SetDeviceIndex(g_u8PVRActiveDevice);
                PVR_SM_CHECKPOINT();
            #if (ENABLE_BULK_FILE_SYSTEM)
                msAPI_MSDCtrl_ResetDevice(g_u8PVRActiveDevice);
                PVR_SM_CHECKPOINT();
                DEBUG_PVR_SM_TIME();
                msAPI_MSDCtrl_CheckDevices();
                PVR_SM_CHECKPOINT();
                DEBUG_PVR_SM_TIME();
                if(msAPI_MSDCtrl_GetDeviceStatus(g_u8PVRActiveDevice)==MSD_STATUS_INSERTED)
                {
                    PVR_SM_CHECKPOINT();
                    DEBUG_PVR_SM_TIME();
                    if (!msAPI_FCtrl_ActiveDevice(g_u8PVRActiveDevice))
                    {
                        PVR_SM_CHECKPOINT();
                        //DEBUG_PVR_SM_TIME();
                        __ASSERT(0);
                        break;
                    }
                    PVR_SM_CHECKPOINT();
                }
                else
                {
                    PVR_SM_CHECKPOINT();
                    DEBUG_PVR_SM_TIME();
                    if (_u8USBResetCounter < USBRESETCOUNT)
                    {
                        msAPI_MSDCtrl_ResetPorts();
                        _u8USBResetCounter ++;
                    }
                    //DEBUG_PVR_SM_TIME();
                    __ASSERT(0);
                    break;
                }
                DEBUG_PVR_SM_TIME();
                g_u8PVRActiveDisk = msAPI_PVRFS_GetDefaultDiskDriveIndex();
            #else
                g_u8PVRActiveDisk = 0;
            #endif

                PVR_SM_CHECKPOINT();
                //DEBUG_PVR_SM_TIME();
                #ifndef PVR_8051
				if(MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
				{
                	MApp_ZUI_ACT_PVR_OpenUI(MENU_PVR_INITIAL);
				}
                #endif

                PVR_SM_CHECKPOINT();
                DEBUG_PVR_SM_TIME();
                MApp_PVR_SetDiskDriveIndex(g_u8PVRActiveDisk, TRUE);
                PVR_SM_CHECKPOINT();
                _enPVRState = E_PVR_STATE_INIT;
            }
            else
            {
                _u8USBResetCounter = 0;
            }
            DEBUG_PVR_SM_TIME();
            PVR_SM_CHECKPOINT();
            break;
        }

        case E_PVR_STATE_INIT:
        {
            DEBUG_PVR_SM_TIME();
            PVR_SM_CHECKPOINT();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            PVR_SM_CHECKPOINT();
            if ((u8USBState & MS_USB_CONNECTED) \
                ||(u8USBState & MS_USB2_CONNECTED) \
                ||(u8USBState & MS_USB3_CONNECTED) \
                ||(u8USBState & MS_USB4_CONNECTED))
            {
                PVR_SM_CHECKPOINT();
                if(msAPI_PVR_Initial() == E_PVR_API_STATUS_OK) //should init first
                {
                    PVR_SM_CHECKPOINT();
                    MApp_Record_ClearCurrentFileName(RECORD_PATH_DEFAULT); //for instant play
                    PVR_SM_CHECKPOINT();
                    if((msAPI_PVRFS_IsFormated( msAPI_PVRFS_GetDriveIndex())) &&  //check formated second
                       (MApp_PVR_DiskGetSpeed() > 0))                           //check speed third
                    {
                        //printf("STCH[[PVR]]@INIT->WAIT\n");
                        _enPVRState = E_PVR_STATE_WAIT;
                        //MApp_UiPvr_Browser_Init();
                    }
                    else
                    {
                      //printf("STCH[[PVR]]@INIT->WAITFORMAT\n");
                        _enPVRState = E_PVR_STATE_WAITFORMAT;
                    }
                }
                else
                {
                    PVR_SM_CHECKPOINT();
                    //reset to drive 0 and init. again.
                    if (msAPI_PVRFS_GetDriveIndex() != 0)
                    {
                        //printf("STCH[[PVR]]@INIT->again\n");
                        if (MApp_PVR_SetDiskDriveIndex(0, FALSE))
                            _enPVRState = E_PVR_STATE_INIT;
                        else _enPVRState = E_PVR_STATE_WAITFORMAT;
                    }
                    else //need to format first.
                    {
                        //printf("STCH[[PVR]]@INIT->WAITFORMAT\n");
                        _enPVRState = E_PVR_STATE_WAITFORMAT;
                    }
                }
                PVR_SM_CHECKPOINT();
            }
            else
            {
                //printf("STCH[[PVR]]@INIT->IDLE\n");
                _enPVRState = E_PVR_STATE_IDLE;
            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
            #endif
            }
            DEBUG_PVR_SM_TIME();
            break;
        }

        case E_PVR_STATE_WAITFORMAT:
        {
            DEBUG_PVR_SM_TIME();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            if ((u8USBState & MS_USB_CONNECTED) \
            || (u8USBState & MS_USB2_CONNECTED) \
            || (u8USBState & MS_USB3_CONNECTED) \
            || (u8USBState & MS_USB4_CONNECTED))
            {
                if(MApp_PVR_DiskGetSpeed()==0)
                {
                    //do nothing, regard it as not-format-yet
                    //may need bulk file system to provide an API to check formatted or not
                }
                else
                {
                    if(msAPI_PVR_Initial() == E_PVR_API_STATUS_OK)
                    {
                        MApp_Record_ClearCurrentFileName(RECORD_PATH_DEFAULT); //for instant play

                      //printf("STCH[[PVR]]@WAITFORMAT->WAIT\n");
                        _enPVRState = E_PVR_STATE_WAIT;
                    #if(ENABLE_PVR_BROWSER)
                        MApp_UiPvr_Browser_Init();
                    #endif
                    }
                    else
                    {
                      //printf("STCH[[PVR]]@WAITFORMAT->IDLE\n");
                        _enPVRState = E_PVR_STATE_IDLE;
                    }
                }
            }
            else
            {
              //printf("STCH[[PVR]]@WAITFORMAT->IDLE\n");
                _enPVRState = E_PVR_STATE_IDLE;
            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
            #endif
            }
            DEBUG_PVR_SM_TIME();
            break;
        }

        case E_PVR_STATE_WAIT:
        {
            DEBUG_PVR_SM_TIME();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            if (((u8USBState & MS_USB_CONNECTED) \
            || (u8USBState & MS_USB2_CONNECTED) \
            || (u8USBState & MS_USB3_CONNECTED) \
            || (u8USBState & MS_USB4_CONNECTED))&&(u8DMPStartFlag == FALSE))
            {
                if(_enPVRInput == E_PVR_INPUT_PLAYBACK_PAUSE)
                {
                    MApp_TimeShift_StateMachineInput((enTimeShiftInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@WAIT->TIMESHIFT\n");
                    _enPVRState = E_PVR_STATE_TIMESHIFT;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if(_enPVRInput == E_PVR_INPUT_RECORD_OPEN)
                {
                    MApp_Record_StateMachineInput((enRecordInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@WAIT->RECORD\n");
                    _enPVRState = E_PVR_STATE_RECORD;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if(_enPVRInput == E_PVR_INPUT_PLAYBACK_OPEN)
                {
                    MApp_Playback_StateMachineInput((enPlaybackInput)_enPVRInput, _u32PVRExtPara);

                    if(MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_PLAYBACKING)
                    {
                      //printf("STCH[[PVR]]@WAIT->PLAYBACK\n");
                        _enPVRState = E_PVR_STATE_PLAYBACK;
                        _enPVRInput = E_PVR_INPUT_NONE;

                    #if(ENABLE_PVR_BROWSER)
                        MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, (U16 *)_u32PVRExtPara, NULL);
                    #endif
                    }
                }
            }
            else
            {
              //printf("STCH[[PVR]]@WAIT->IDLE\n");
                _enPVRState = E_PVR_STATE_IDLE;
            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
            #endif
                if(u8DMPStartFlag == TRUE)
                {
                    u8DMPStartFlag = FALSE;
                }
            }
            DEBUG_PVR_SM_TIME();
            break;
        }

        case E_PVR_STATE_TIMESHIFT:
        {
            DEBUG_PVR_STATE( printf("E_PVR_STATE_TIMESHIFT:\n"); );
            DEBUG_PVR_SM_TIME();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            if ((u8USBState & MS_USB_CONNECTED) \
            || (u8USBState & MS_USB2_CONNECTED) \
            || (u8USBState & MS_USB3_CONNECTED) \
            || (u8USBState & MS_USB4_CONNECTED))
            {
                if((_enPVRInput == E_PVR_INPUT_PLAYBACK_OPEN) && (MApp_TimeShift_StateMachineGet()==E_TIMESHIFT_STATE_WAIT))
                {
                    MApp_Playback_StateMachineInput((enPlaybackInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@TIMESHIFT->PLAYBACK\n");
                    _enPVRState = E_PVR_STATE_PLAYBACK;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if(_enPVRInput == E_PVR_INPUT_RECORD_OPEN)
                {
                    MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_PLAYBACK_CLOSE, _u32PVRExtPara);
                    MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_RECORD_CLOSE, _u32PVRExtPara);
                    MApp_Record_StateMachineInput((enRecordInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@TIMESHIFT->RECORD\n");
                    _enPVRState = E_PVR_STATE_RECORD;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if(_enPVRInput != E_PVR_INPUT_NONE)
                {
                    MApp_TimeShift_StateMachineInput((enTimeShiftInput)_enPVRInput, _u32PVRExtPara);
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                MApp_TimeShift_StateMachineRunning();

                if(MApp_TimeShift_StateMachineGet() == E_TIMESHIFT_STATE_WAIT)
                {
                    _enPVRState = E_PVR_STATE_WAIT;
                }
            }
            else
            {
                MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_PLAYBACK_CLOSE, _u32PVRExtPara);
                MApp_TimeShift_StateMachineInput(E_TIMESHIFT_INPUT_RECORD_CLOSE, _u32PVRExtPara);
              //printf("STCH[[PVR]]@TIMESHIFT->IDLE\n");
                _enPVRState = E_PVR_STATE_IDLE;
                _enPVRStatus = E_PVR_API_STATUS_NO_DISK_FOR_WRITE;

              #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
              #endif

              #if (MHEG5_ENABLE)
                enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
              #endif
            }
            DEBUG_PVR_SM_TIME();
            break;
        }

        case E_PVR_STATE_RECORD:
        {
            DEBUG_PVR_STATE( printf("E_PVR_STATE_RECORD:\n"); );
            DEBUG_PVR_SM_TIME();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            if ((u8USBState & MS_USB_CONNECTED) \
            || (u8USBState & MS_USB2_CONNECTED) \
            || (u8USBState & MS_USB3_CONNECTED) \
            || (u8USBState & MS_USB4_CONNECTED))
            {
                if((_enPVRInput == E_PVR_INPUT_PLAYBACK_PAUSE) && (MApp_Record_StateMachineGet()==E_RECORD_STATE_WAIT))
                {
                    MApp_Record_StateMachineInput(E_RECORD_INPUT_RECORD_CLOSE, _u32PVRExtPara);
                    MApp_TimeShift_StateMachineInput((enTimeShiftInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@RECORD->TIMESHIFT\n");
                    _enPVRState = E_PVR_STATE_TIMESHIFT;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if((_enPVRInput == E_PVR_INPUT_PLAYBACK_OPEN) && (MApp_Record_StateMachineGet()==E_RECORD_STATE_WAIT))
                {
                    MApp_Playback_StateMachineInput((enPlaybackInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@RECORD->PLAYBACK\n");
                    _enPVRState = E_PVR_STATE_PLAYBACK;
                    _enPVRInput = E_PVR_INPUT_NONE;
                #if(ENABLE_PVR_BROWSER)
                    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, (U16 *)_u32PVRExtPara, NULL);
                #endif
                }
                else if(_enPVRInput == E_PVR_INPUT_PLAYBACK_OPEN)
                {
                    MApp_Playback_StateMachineInput((enPlaybackInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@RECORD->RECORDnPLAYBACK\n");
                    _enPVRState = E_PVR_STATE_RECORDnPLAYBACK;
                    _enPVRInput = E_PVR_INPUT_NONE;
                #if(ENABLE_PVR_BROWSER)
                    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, (U16 *)_u32PVRExtPara, NULL);
                #endif
                }
                else if(_enPVRInput != E_PVR_INPUT_NONE)
                {
                    MApp_Record_StateMachineInput((enRecordInput)_enPVRInput, _u32PVRExtPara);
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                MApp_Record_StateMachineRunning();

                if(MApp_Record_StateMachineGet() == E_RECORD_STATE_WAIT)
                {
                    _enPVRState = E_PVR_STATE_WAIT;
                }
            }
            else
            {
                MApp_Record_StateMachineInput(E_RECORD_INPUT_RECORD_CLOSE, _u32PVRExtPara);

            #if(ENABLE_PVR_BROWSER)
                MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, NULL, NULL);
            #endif

              //printf("STCH[[PVR]]@RECORD->IDLE\n");
                _enPVRState = E_PVR_STATE_IDLE;
                _enPVRStatus = E_PVR_API_STATUS_NO_DISK_FOR_WRITE;
            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
            #endif
            }
            DEBUG_PVR_SM_TIME();
            break;
        }

        case E_PVR_STATE_RECORDnPLAYBACK:
        {
            DEBUG_PVR_STATE( printf("E_PVR_STATE_RECORDnPLAYBACK:\n"); );

            DEBUG_PVR_SM_TIME();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            if ((u8USBState & MS_USB_CONNECTED) \
            || (u8USBState & MS_USB2_CONNECTED) \
            || (u8USBState & MS_USB3_CONNECTED) \
            || (u8USBState & MS_USB4_CONNECTED))
            {
                if((_enPVRInput == E_PVR_INPUT_RECORD_CLOSE) &&
                   ((MApp_Record_StateMachineGet()==E_RECORD_STATE_RECORDING) || MApp_Record_StateMachineGet()==E_RECORD_STATE_STOP))
                {
                    MApp_Record_StateMachineInput((enRecordInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@RECORDnPLAYBACK->PLAYBACK\n");
                    _enPVRState = E_PVR_STATE_PLAYBACK;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if(_enPVRInput != E_PVR_INPUT_NONE)
                {
                    MApp_Playback_StateMachineInput((enPlaybackInput)_enPVRInput, _u32PVRExtPara);
                    _enPVRInput = E_PVR_INPUT_NONE;
                }

                if(MApp_Record_StateMachineGet()==E_RECORD_STATE_WAIT)
                {
                  //printf("STCH[[PVR]]@RECORDnPLAYBACK->PLAYBACK\n");
                    _enPVRState = E_PVR_STATE_PLAYBACK;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }

                if(MApp_Playback_StateMachineGet()==E_PLAYBACK_STATE_WAIT)
                {
                  //printf("STCH[[PVR]]@RECORDnPLAYBACK->RECORD\n");
                    _enPVRState = E_PVR_STATE_RECORD;
                    _enPVRInput = E_PVR_INPUT_NONE;
                #if(ENABLE_PVR_BROWSER)
                    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, NULL, NULL);
                #endif
                }

                MApp_Record_StateMachineRunning();
                MApp_Playback_StateMachineRunning();

                if(MApp_Record_StateMachineGet() == E_RECORD_STATE_WAIT && MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_WAIT)
                {
                    _enPVRState = E_PVR_STATE_WAIT;
                }
            }
            else
            {
                MApp_Record_StateMachineInput(E_RECORD_INPUT_RECORD_CLOSE, _u32PVRExtPara);
				MApp_Playback_StateMachineInput(E_PLAYBACK_INPUT_PLAYBACK_RESUME, _u32PVRExtPara);
                MApp_Playback_StateMachineInput(E_PLAYBACK_INPUT_PLAYBACK_CLOSE, _u32PVRExtPara);
            #if(ENABLE_PVR_BROWSER)
                MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, NULL, NULL);
                MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_RECORDING, NULL, NULL);
            #endif
              //printf("STCH[[PVR]]@RECORDnPLAYBACK->IDLE\n");
                _enPVRState = E_PVR_STATE_IDLE;
                _enPVRStatus = E_PVR_API_STATUS_NO_DISK_FOR_READ;
            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
            #endif
            }
            DEBUG_PVR_SM_TIME();
            break;
        }

        case E_PVR_STATE_PLAYBACK:
        {
            DEBUG_PVR_STATE( printf("E_PVR_STATE_PLAYBACK:\n"); );
            DEBUG_PVR_SM_TIME();
            U8 u8USBState = MApp_MassStorage_DeviceConnectionDetect();
            if ((u8USBState & MS_USB_CONNECTED) \
            || (u8USBState & MS_USB2_CONNECTED) \
            ||(u8USBState & MS_USB3_CONNECTED) \
            ||(u8USBState & MS_USB4_CONNECTED))
            {
                if((_enPVRInput == E_PVR_INPUT_RECORD_OPEN) && (MApp_Playback_StateMachineGet()==E_PLAYBACK_STATE_WAIT))
                {
                    MApp_Record_StateMachineInput((enRecordInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@PLAYBACK->RECORD\n");
                    _enPVRState = E_PVR_STATE_RECORD;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if((_enPVRInput == E_PVR_INPUT_PLAYBACK_PAUSE) && (MApp_Playback_StateMachineGet()==E_PLAYBACK_STATE_WAIT))
                {
                    MApp_TimeShift_StateMachineInput((enTimeShiftInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@PLAYBACK->TIMESHIFT\n");
                    _enPVRState = E_PVR_STATE_TIMESHIFT;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if(_enPVRInput == E_PVR_INPUT_RECORD_OPEN)
                {
                    MApp_Record_StateMachineInput((enRecordInput)_enPVRInput, _u32PVRExtPara);
                  //printf("STCH[[PVR]]@PLAYBACK->RECORDnPLAYBACK\n");
                    _enPVRState = E_PVR_STATE_RECORDnPLAYBACK;
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                else if(_enPVRInput != E_PVR_INPUT_NONE)
                {
                    MApp_Playback_StateMachineInput((enPlaybackInput)_enPVRInput, _u32PVRExtPara);
                    _enPVRInput = E_PVR_INPUT_NONE;
                }
                MApp_Playback_StateMachineRunning();

                if(MApp_Playback_StateMachineGet() == E_PLAYBACK_STATE_WAIT)
                {
                    _enPVRState = E_PVR_STATE_WAIT;
                #if(ENABLE_PVR_BROWSER)
                    MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, NULL, NULL);
                #endif
                }
            }
            else
            {
				MApp_Playback_StateMachineInput(E_PLAYBACK_INPUT_PLAYBACK_RESUME, _u32PVRExtPara);
                MApp_Playback_StateMachineInput(E_PLAYBACK_INPUT_PLAYBACK_CLOSE, _u32PVRExtPara);
            #if(ENABLE_PVR_BROWSER)
                MApp_PvrBrowser_SetAttributeByFileName(E_PVR_ATTR_IS_PLAYING, NULL, NULL);
            #endif
              //printf("STCH[[PVR]]@PLAYBACK->IDLE\n");
                _enPVRState = E_PVR_STATE_IDLE;
                _enPVRStatus = E_PVR_API_STATUS_NO_DISK_FOR_READ;
            #if(ENABLE_PVR_BROWSER)
                MApp_UiPvr_Browser_DeInit();
            #endif
            }
            DEBUG_PVR_SM_TIME();
            break;
        }
    }

    PVR_SM_CHECKPOINT();

#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
	if(MApp_PVR_IsRecording())
	{
	 g_bTimerTypeRecord = TRUE;
	}

#endif
    DEBUG_PVR_SM_TIME();
    PVR_SM_CHECKPOINT();

    msAPI_Player_ScalerCheckFree();

    DEBUG_PVR_SM_TIME();
    PVR_SM_CHECKPOINT();

    if( msAPI_Timer_DiffTime_2( u32Time1, MsOS_GetSystemTime() ) > 300 )
    {
        printf("\n %s use %u\n", __FUNCTION__, MsOS_GetSystemTime() - u32Time1 );
    }
}

/***************************************************************************************/
void MApp_PVR_StateMachineInput(enPVRInput enSMInput, U32 u32ExtParameter)
{
    _enPVRInput     = enSMInput;
    _u32PVRExtPara  = u32ExtParameter;

    MApp_PVR_StateMachineRunning();

    _enPVRInput     = E_PVR_INPUT_NONE;     //ensure to consume any input
    _u32PVRExtPara  = 0;                    //ensure to consume any parameter
}

/***************************************************************************************/
enPVRState  MApp_PVR_StateMachineGet(void)
{
    return _enPVRState;
}

/***************************************************************************************/
enPvrApiStatus  MApp_PVR_StatusGet(void)
{
    enPvrApiStatus enPVRStatus = _enPVRStatus;
    _enPVRStatus = E_PVR_API_STATUS_OK;    //read clear
    return enPVRStatus;
}

/***************************************************************************************/
BOOLEAN MApp_PVR_Is_InRecording(void)
{
    if( _enPVRState == E_PVR_STATE_TIMESHIFT )
    {
        return MApp_TimeShift_Is_InRecording();
    }

    return FALSE;
}

/***************************************************************************************/

#else
BOOLEAN code compile_mapp_pvr;
#endif//ENABLE_PVR
#undef MAPP_PVR_C

