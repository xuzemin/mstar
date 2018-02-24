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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// @file
// @brief
// @author MStarSemi Inc.
//
//-
//-
//
////////////////////////////////////////////////////////////////////////////////
#define _MSAPI_FSENV_C

#include "drvpower_if.h"
#include "msAPI_FCtrl.h"
#include "msAPI_N51FS.h"
#include "msAPI_FAT.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FSEnv.h"
#include "msAPI_Timer.h"
#include "msAPI_Global.h"


#define FSENV_DBG(x)     //printf("[FS_ENV] ",__FILE__);x
static FS_EnvironmentStruct g_environment_list[4];

#define DEBUG_FSENV(x)  //x

BOOLEAN msAPI_FSEnv_Init(U32 u32FS_adr,U32 u32FS_len)
{
    U8 i;

    DEBUG_FSENV( PRINT_CURRENT_LINE(); );
    DEBUG_FSENV( printf("msAPI_FSEnv_Init(u32FS_adr=%X, u32FS_len=%X)\n", u32FS_adr, u32FS_len); );


    _FILE_SYSTEM_POOL_ADR = u32FS_adr;
    _FILE_SYSTEM_POOL_LEN = u32FS_len;

#if (ENABLE_N51FS)
    if(_FILE_SYSTEM_POOL_LEN < 0x1B000)
    {
        __ASSERT(0);
        FSENV_DBG(printf("Not Enough Memory for File System!! At Least 0x17000 Bytes Required!!\n"));
        return FALSE;
    }
#else
    if(_FILE_SYSTEM_POOL_LEN < 0x10000)
    {
        __ASSERT(0);
        FSENV_DBG(printf("Not Enough Memory for File System!! At Least 0x10000 Bytes Required!!\n"));
        return FALSE;
    }
#endif

    if(_FILE_SYSTEM_POOL_LEN <= MIN_FS_MEMORY)
    {
        FS_FILE_HANDLE_NUM = 1;        //for read / write
    }
    else
    {
        FS_FILE_HANDLE_NUM = MAX_FS_FILE_HANDLE_NUM;        //for read / write
    }

    if(FILE_SYSTEM_POOL_LEN <= MIN_FS_MEMORY)
    {
        FS_ENVIRONMENT_NUM = 1;
    }
    else
    {
        FS_ENVIRONMENT_NUM = MAX_FS_ENVIRONMENT_NUM;
    }

    if(FILE_SYSTEM_POOL_LEN <= MIN_FS_MEMORY)
    {
        DISK_DRIVE_NUM = 1;
    }
    else
    {
        DISK_DRIVE_NUM = MAX_DISK_DRIVE_NUM;
    }

    // ######## FS MEMORY
    //USB_IO_TEMP_ADDR = (MemAlign(_FILE_SYSTEM_POOL_ADR, 0x1000) | NONCACHE_MASK);

    USB_IO_TEMP_ADDR_CACHE = MemAlign(_FILE_SYSTEM_POOL_ADR, 0x1000);
    USB_IO_TEMP_ADDR = msOS_CacheToNonCache(USB_IO_TEMP_ADDR_CACHE);

    DEBUG_FSENV( printf("USB_IO_TEMP_ADDR_CACHE=%X\n", USB_IO_TEMP_ADDR_CACHE); );
    DEBUG_FSENV( printf("USB_IO_TEMP_ADDR=%X\n", USB_IO_TEMP_ADDR); );

    //#define USB_IO_TEMP_LEN                 0x1000UL

#if (MEMORY_MAP <= MMAP_32MB)
    USB_IO_TEMP_ADDR2 = USB_IO_TEMP_ADDR;
#else
    USB_IO_TEMP_ADDR2 = (USB_IO_TEMP_ADDR_CACHE + USB_IO_TEMP_LEN);
    //#define USB_IO_TEMP_LEN2         0x1000UL
#endif

    DEVICE_IO_BUFFER_ADDR = (USB_IO_TEMP_ADDR2 + USB_IO_TEMP_LEN2);
    //#define DEVICE_IO_BUFFER_LEN           0x1000UL

    //following define should be used only in msAPI_MSDCtrl for W/R
    STORAGE_DEVICE_MEMORY_ADDR = (DEVICE_IO_BUFFER_ADDR + DEVICE_IO_BUFFER_LEN);
    //#define STORAGE_DEVICE_MEMORY_LEN       0x800UL    // 2K  5 * 2 (sizeof(StorageDevice))

    DEBUG_FSENV( printf("STORAGE_DEVICE_MEMORY_ADDR=%X)\n", STORAGE_DEVICE_MEMORY_ADDR); );

    DRIVE_MEMORY_ADDR = (STORAGE_DEVICE_MEMORY_ADDR + STORAGE_DEVICE_MEMORY_LEN);
    //#define DRIVE_MEMORY_LEN                0x800UL    //2K  16 * 8 ( sizeof(MSDCtrl_Drive))

    FILE_SYSTEM_MOUNTED_ADDR = (DRIVE_MEMORY_ADDR + DRIVE_MEMORY_LEN);  // 4K aligned
    //#define FILE_SYSTEM_MOUNTED_LEN         0x2000UL  //8K  16 * 512(FileStruct_Size)

    FILE_ENVIRONMENT_POOL = (FILE_SYSTEM_MOUNTED_ADDR + FILE_SYSTEM_MOUNTED_LEN); //4K aligned
    FILE_ENVIRONMENT_POOL_LEN = (FILE_ENVIRONMENT_MEMORY_SIZE * FS_ENVIRONMENT_NUM); //

    FILE_FAT_TABLE_CACHE = (FILE_ENVIRONMENT_POOL + FILE_ENVIRONMENT_POOL_LEN);
    FILE_FAT_TABLE_CACHE_LEN = FAT_TABLE_CACHE_LEN * DISK_DRIVE_NUM; //16 is drive num


    FILE_INODE_POOL = (FILE_FAT_TABLE_CACHE + FILE_FAT_TABLE_CACHE_LEN);
    FILE_INODE_POOL_LEN = (FILE_INODE_MEMORY_SIZE * FS_FILE_HANDLE_NUM);

    FILE_HANDLE_POOL = (FILE_INODE_POOL + FILE_INODE_POOL_LEN);
    FILE_HANDLE_POOL_LEN = (FILE_HANDLE_MEMORY_SIZE * FS_FILE_HANDLE_NUM);




#if (ENABLE_N51FS)
    N51FS_TEMP_4K_BACKUP_BUFFER_0 = (FILE_HANDLE_POOL + FILE_HANDLE_POOL_LEN); //4K aligned
    //#define N51FS_TEMP_4K_BACKUP_BUFFER_0_LEN       0x1000UL

    N51FS_TEMP_4K_BACKUP_BUFFER_1 = (N51FS_TEMP_4K_BACKUP_BUFFER_0 + N51FS_TEMP_4K_BACKUP_BUFFER_0_LEN); //4K aligned
    //#define N51FS_TEMP_4K_BACKUP_BUFFER_1_LEN       0x1000UL

    N51FS_TEMP_4K_BACKUP_BUFFER_2 = (N51FS_TEMP_4K_BACKUP_BUFFER_1 + N51FS_TEMP_4K_BACKUP_BUFFER_1_LEN); //4K aligned
    //#define N51FS_TEMP_4K_BACKUP_BUFFER_2_LEN       0x1000UL

    N51FS_TEMP_4K_BUFFER_0 = (N51FS_TEMP_4K_BACKUP_BUFFER_2 + N51FS_TEMP_4K_BACKUP_BUFFER_2_LEN);
    //#define N51FS_TEMP_4K_BUFFER_0_LEN       0x1000UL

    //N51FS_TEMP_4K_BUFFER_1 = (N51FS_TEMP_4K_BUFFER_0 + N51FS_TEMP_4K_BUFFER_0_LEN);
    //#define N51FS_TEMP_4K_BUFFER_1_LEN       0x1000UL

    //N51FS_INDEX_BUFFER_ADDR = (N51FS_TEMP_4K_BUFFER_1 + N51FS_TEMP_4K_BUFFER_1_LEN);
    //#define N51FS_INDEX_BUFFER_LEN          0x1000UL

    N51FS_TEMP_4K_FIXUP = (N51FS_TEMP_4K_BUFFER_0 + N51FS_TEMP_4K_BUFFER_0_LEN);//(N51FS_INDEX_BUFFER_ADDR + N51FS_INDEX_BUFFER_LEN);
    //#define N51FS_TEMP_4K_FIXUP_LEN       0x1000UL

    FS_MEMORY_MAP_END = (N51FS_TEMP_4K_FIXUP + N51FS_TEMP_4K_FIXUP_LEN);

//~!~
    #if SUPPORT_COMPRESS
    printf("support compress \n");
    N51FS_CB_SRC_BUFFER_ADDR = _PA2VA(NTFS_DECOMPRESS_BUF_ADR);
    N51FS_CB_DST_BUFFER_ADDR = N51FS_CB_SRC_BUFFER_ADDR + N51FS_CB_SRC_LEN;
    printf("N51FS_CB_SRC_BUFFER_ADDR=%x, N51FS_CB_DST_BUFFER_ADDR=%x \n",N51FS_CB_SRC_BUFFER_ADDR, N51FS_CB_DST_BUFFER_ADDR);
    #else
    printf("unsupport N51 FS compress \n");
    #endif

#else

    FS_MEMORY_MAP_END = (FILE_HANDLE_POOL + FILE_HANDLE_POOL_LEN);
#endif

    FSENV_DBG(printf("Total Used File System Memory: 0x%x(0x%x)!!", (FS_MEMORY_MAP_END-_FILE_SYSTEM_POOL_ADR), _FILE_SYSTEM_POOL_LEN));
    if(FS_MEMORY_MAP_END > (_FILE_SYSTEM_POOL_ADR+_FILE_SYSTEM_POOL_LEN))
    {
        __ASSERT(0);
        FSENV_DBG(printf("File System Memory MAP Overflow!!!"));
        return FALSE;
    }
    //######## FS MEMORY

    for(i = 0; i<FS_ENVIRONMENT_NUM; i++)
    {
        XDataAddr[i][0] = FILE_ENVIRONMENT_POOL + FAT_ENVIRONMENT_ADR+i*FILE_ENVIRONMENT_MEMORY_SIZE;
        XDataAddr[i][1] = FILE_ENVIRONMENT_POOL + FAT_DIR_ENTRY_CACHE_ADR+i*FILE_ENVIRONMENT_MEMORY_SIZE;
        XDataAddr[i][2] = FILE_ENVIRONMENT_POOL + FAT_FSINFO_SECTOR_ADR+i*FILE_ENVIRONMENT_MEMORY_SIZE;
        XDataAddr[i][3] = FILE_ENVIRONMENT_POOL + FAT_CURRENT_INFO_ADR+i*FILE_ENVIRONMENT_MEMORY_SIZE;

        g_environment_list[i].u8CurrentDirectoryIndex = 0xFF;
        g_environment_list[i].u8DeviceIndex = 0xFF;
        g_environment_list[i].u8FileSystemID = 0xFF;
        g_environment_list[i].u8FileSystemType = FILE_SYSTEM_TYPE_NONE;
        g_environment_list[i].bIsInit = FALSE;
    }
    return TRUE;
}

// Return Environment handle ID
// 0xFF means invalid handle
U8 msAPI_FSEnv_Register(U8 driveID)
{
    U8 i;
    MSDCtrl_Drive target_drive;

    memset(&target_drive,0,sizeof(target_drive));
    //drive label from A
    if(driveID >= DISK_DRIVE_NUM)
    {
        return INVALID_FS_ENVIRONMENT_INDEX;
    }

    for(i = 0; i<FS_ENVIRONMENT_NUM; i++)
    {
        if(g_environment_list[i].bIsInit==FALSE)
        {
            // do registeration
            if(!msAPI_FCtrl_GetDriveByIndex(driveID, &target_drive))
            {
                return INVALID_FS_ENVIRONMENT_INDEX;
            }

            g_environment_list[i].u8FileSystemType = target_drive.FileSystemType;
            g_environment_list[i].u8FileSystemID = driveID;
            g_environment_list[i].u8DeviceIndex = target_drive.DeviceIndex;

            if(target_drive.FileSystemType==FILE_SYSTEM_TYPE_FAT)
            {
                if(!FAT_SaveEnvironment(i))
                {
                    return INVALID_FS_ENVIRONMENT_INDEX;
                }
            }
            else if(target_drive.FileSystemType==FILE_SYSTEM_TYPE_N51FS)
            {
                #if ENABLE_N51FS
                if(!N51FS_SaveEnvironment(i))
                {
                    return INVALID_FS_ENVIRONMENT_INDEX;
                }
                #else
                __ASSERT(0);
                return INVALID_FS_ENVIRONMENT_INDEX;
                #endif
            }
            else
            {
                return INVALID_FS_ENVIRONMENT_INDEX;
            }

            g_environment_list[i].bIsInit = TRUE;

            FSENV_DBG(printf("Register Drive %bu with environmentID=%bu for FSType=%bu\n",target_drive.DriveIndex,i,target_drive.FileSystemType));

            return i;
        }
    }
    FSENV_DBG(printf("!!! msAPI_FSEnv_Register fail !!! -- no more free environment handle\n"));

    return INVALID_FS_ENVIRONMENT_INDEX;
}

void msAPI_FSEnv_UnRegister(U8 environmentId)
{
    if(environmentId>=FS_ENVIRONMENT_NUM||environmentId==INVALID_FILE_HANDLE)
        return;

    FSENV_DBG(printf("Unregister Drive %bu with environmentID=%bu for FSID=%bu\n", g_environment_list[environmentId].u8DeviceIndex,environmentId,g_environment_list[environmentId].u8FileSystemID));

    g_environment_list[environmentId].u8CurrentDirectoryIndex = 0xFF;
    g_environment_list[environmentId].u8DeviceIndex = 0xFF;
    g_environment_list[environmentId].u8FileSystemID = 0xFF;
    g_environment_list[environmentId].u8FileSystemType = FILE_SYSTEM_TYPE_NONE;
    g_environment_list[environmentId].bIsInit = FALSE;
}

FS_EnvironmentStruct* msAPI_FSEnv_GetEnvironment(U8 environmentId)
{
    if(environmentId>=FS_ENVIRONMENT_NUM)
    {
        __ASSERT(0);
        return NULL;
    }
    return &g_environment_list[environmentId];
}

U32 msAPI_FS_GetAddr(U32 addr)
{
    return addr;
}

static code U8 FS_SolarCal[12] =
{
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
static code U16 FS_SolarDays[28] =
{
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 396, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366, 397
};

U8 msAPI_FS_GetLeap ( U16 u16year )
{
    if ( u16year % 400 == 0 )
    {
        return 1;
    }
    else if ( u16year % 100 == 0 )
    {
        return 0;
    }
    else if ( u16year % 4 == 0 )
    {
        return 1;
    }

    return 0;
}

U8 msAPI_FS_GetDaysOfThisMonth ( U16 u16Year, U8 u8Month )
{
    if ( u8Month >= 1 && u8Month <= 12 )
    {
        return ( ( msAPI_FS_GetLeap( u16Year ) && u8Month == 2 ) ? 29 : FS_SolarCal[u8Month - 1] );
    }
    else
    {
        return 0;
    }
}

U32 msAPI_FS_ConvertStTime2Seconds ( FS_TIME *pstTime )
{
    U32 u32TotalSeconds;
    U32 u32YearCalc;
    U8 u8Temp;

    u32TotalSeconds = 0;
    u32YearCalc =0;
    /* sec */
    u32TotalSeconds += pstTime->u8Sec;

    /* min */
    u32TotalSeconds += pstTime->u8Min * SECONDS_PER_MIN;

    /* hour */
    u32TotalSeconds += pstTime->u8Hour * SECONDS_PER_HOUR;

    /* day */
    u32TotalSeconds += pstTime->u8Day  * SECONDS_PER_DAY;

    /* month */
    u8Temp = msAPI_FS_GetLeap( pstTime->u16Year ) * 14 + pstTime->u8Month - 1 ;
    if(u8Temp >= 28)
    {
        __ASSERT(0);
        return 0;
    }
    u32TotalSeconds += FS_SolarDays[u8Temp] * SECONDS_PER_DAY;

    /* year */
    #if 0
    u32YearCalc = pstTime->u16Year;
    while(u32YearCalc > DEFAULT_YEAR)
    {
        u32YearCalc--;
        u16Days = msAPI_FS_GetLeap( u32YearCalc ) ? 366 : 365;
        u32TotalSeconds += u16Days * SECONDS_PER_DAY;
    }
    #else
    if(pstTime->u16Year != FS_DEFAULT_YEAR)
    {
        u32YearCalc = (pstTime->u16Year-FS_DEFAULT_YEAR)*365 + (pstTime->u16Year - 1 - FS_DEFAULT_YEAR)/4 + 1;
    }
    u32YearCalc -= (pstTime->u16Year > 2000)?1:0;
    u32YearCalc *= SECONDS_PER_DAY;
    u32TotalSeconds += u32YearCalc;
    #endif

    return u32TotalSeconds;
}

void msAPI_FS_ConvertSeconds2StTime ( U32 u32SystemTime, FS_TIME *pstTime )
{
    U16 u16TotalDays, u16Days;

    /* set to base date */
    pstTime->u16Year = FS_DEFAULT_YEAR;
    pstTime->u8Month = FS_DEFAULT_MONTH;
    pstTime->u8Day = FS_DEFAULT_DAY;
    pstTime->u8Hour = FS_DEFAULT_HOUR;
    pstTime->u8Min = FS_DEFAULT_MIN;
    pstTime->u8Sec = FS_DEFAULT_SEC;

    /* u32SystemTime = total accumulative seconds from base date */
    if(u32SystemTime > 0)
    {
        /* sec */
        pstTime->u8Sec = (U8)(u32SystemTime % SECONDS_PER_MIN);
        u32SystemTime -= pstTime->u8Sec;

        /* min */
        pstTime->u8Min = (U8)(( u32SystemTime / SECONDS_PER_MIN ) % MINS_PER_HOUR);
        u32SystemTime -= pstTime->u8Min * SECONDS_PER_MIN;

        /* hour */
        pstTime->u8Hour = (U8)(( u32SystemTime / SECONDS_PER_HOUR ) % HOURS_PER_DAY);
        u32SystemTime -= pstTime->u8Hour * SECONDS_PER_HOUR;

        /* days */
        u16TotalDays = (U16)(u32SystemTime / SECONDS_PER_DAY);

        /* year */
        u16Days = msAPI_FS_GetLeap( pstTime->u16Year ) ? 366 : 365;
        while ( u16TotalDays >= u16Days )
        {
            u16TotalDays -= u16Days;
            pstTime->u16Year++;
            u16Days = msAPI_FS_GetLeap( pstTime->u16Year ) ? 366 : 365;
        }

        /* month */
        u16Days = msAPI_FS_GetDaysOfThisMonth( pstTime->u16Year, pstTime->u8Month );
        while ( u16TotalDays >= u16Days )
        {
            u16TotalDays -= u16Days;
            pstTime->u8Month++;
            u16Days = msAPI_FS_GetDaysOfThisMonth( pstTime->u16Year, pstTime->u8Month );
        }

        /* day */
        pstTime->u8Day += ( U8 ) u16TotalDays;
    }
}

#if (FILE_SYSTEM_WRITE_ENABLE)

#define FS_Local_Time(utc)     ((U32)(utc) + (U32)msAPI_Timer_GetOffsetTime())

#if 0
static U32 FS_GetSecondsFrom1980To2000(void)
{
    FS_TIME start_Date;
    FS_TIME end_Date;
    start_Date.u16Year = 1980;
    start_Date.u8Month = 1;
    start_Date.u8Day = 1;
    start_Date.u8Hour = 0;
    start_Date.u8Min = 0;
    start_Date.u8Sec = 0;

    end_Date.u16Year = 2000;
    end_Date.u8Month = 1;
    end_Date.u8Day = 1;
    end_Date.u8Hour = 0;
    end_Date.u8Min = 0;
    end_Date.u8Sec = 0;

    return (msAPI_FS_ConvertStTime2Seconds(&end_Date)-msAPI_FS_ConvertStTime2Seconds(&start_Date));
}
#endif

FS_TIME msAPI_FS_GetLocalTime(void)
{
    FS_TIME fsTime;
    U32 u32LocalTime;

    u32LocalTime = msAPI_Timer_GetSystemTime();
    if (g_u8TimeInfo_Flag)
    {
        //Alan.Yu marked on 2011.1.4 : because u32LocalTime is the absolute time
        //U32 u32DiffTime = FS_GetSecondsFrom1980To2000();
        u32LocalTime = FS_Local_Time(u32LocalTime);

        //msAPI_FS_ConvertSeconds2StTime((u32LocalTime+u32DiffTime), &fsTime);
        msAPI_FS_ConvertSeconds2StTime(u32LocalTime, &fsTime);
    }
    else
    {
        fsTime.u16Year = 2008;
        fsTime.u8Month = 1;
        fsTime.u8Day = 1;
        fsTime.u8Hour = 12;
        fsTime.u8Min = 0;
        fsTime.u8Sec = 0;
    }

    FSENV_DBG(printf("\nY: %u, M: %02bd, D: %02bd", fsTime.u16Year, fsTime.u8Month, fsTime.u8Day));
    FSENV_DBG(printf("\nHour: %02bd, Min: %02bd, Sec: %02bd", fsTime.u8Hour, fsTime.u8Min, fsTime.u8Sec));

    return fsTime;
}
#endif

#undef _MSAPI_FSENV_C
