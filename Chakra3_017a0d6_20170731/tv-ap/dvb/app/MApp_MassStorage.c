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

#define MAPP_MASSSTORAGE

#include "datatype.h"
#include "debug.h"
#include "Board.h"

#include <stdio.h>
#include <string.h>

#include "msAPI_Memory.h"

#if ENABLE_CARDREADER
#include "drvCReader.h"
#endif

#include "drvUSB.h"
#include "msAPI_MSDCtrl.h"
#include "MApp_MassStorage.h"

#undef MAPP_MASSSTORAGE
#if ENABLE_DTV_CHCEK_USB_DELAY_2S
#include "MApp_GlobalVar.h"
#endif

#include "msAPI_FCtrl.h"


#define msAPI_FS_GetDriveCount() msAPI_FCtrl_GetDriveCount()
#define msAPI_FS_GetDriveCountByPort(x) msAPI_FCtrl_GetDriveCountByPort(x)
#define msAPI_FS_StartDevice(x) msAPI_FCtrl_ActiveDevice(x)
#define msAPI_FS_GetDriveByIndex(x,y) msAPI_FCtrl_GetDriveByIndex(x,y)
#define MApp_FS_GetValidDevice() MApp_MassStorage_GetValidDevice()
#define msAPI_FS_DisconnectDevice(x) msAPI_MSDCtrl_ResetDevice(x)
#define msAPI_FS_DisconnectDeviceOnPort(x) msAPI_MSDCtrl_ResetDevicesOnPort(x);

/*definition ====================================================================================*/
#define DISKMNG_DISK_LETTER_START               'C'
#define DISKMNG_INVALID_DRIVE
#define STORAGE_DRIVE_NUM  DISK_DRIVE_NUM

/*************************************************************************************************/
//static BOOLEAN _pbDeviceStatus[MSD_PORT_NUM][STORAGE_DEVICE_NUM][DISK_DRIVE_NUM];  //global device / drive status

//static U8 _u8CurrentDriveLetter[MS_MAX_DRIVE_SUPPORT];                  //global current drive letter

//static BOOLEAN _bMultiDrive[MSD_PORT_NUM];                              //global multi drive flag
static U8 _u8TotalDriveCount;                             //global total drive count
static U8 _u8TotalDriveCountPerPort[MSD_PORT_NUM];                      //global total drive count per port
//static U8 _u8ActiveDrive = 0;                                           //global active drive
//static U8 _u8ActiveDriveCount = 0;                                      //global active drive count

static U8 _u8CurrentDeviceIndex=0;
static U8 _u8CurrentDriveIndex=0;
static U32 s_u32CurrentValidDevice = 0;
static U8 u8MassStorageInit    = FALSE;
/*************************************************************************************************/

// Table for the convertion between UI and Mass Storge Device
// The high byte means device number, the low byte means drive number, and f means invalid
// Example1: 0x30 means device number is 3 and drive number is 0
// Example2: 0xf0 means invalid device
code U8 u8UI2STORAGE_TBL[2][9] =
{
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}, // Multi-Drive
    {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80}, // Multi-Device
};

#define MASSSTORAGE_DBG(x)  //x

//static U8 environmentId=0xFF;

/*###############################################################################################*/
/*/////////////////////////////////Mass Storage -> Init/DeInit //////////////////////////////////*/
/*###############################################################################################*/
void MApp_MassStorage_Init()
{
    s_u32CurrentValidDevice = 0;
}

U32 MApp_MassStorage_GetValidDevice()
{
    U32 u32Result=0;
    U8 i=0;
    U8 count=msAPI_MSDCtrl_GetTotalDeviceCount();
    //printf("MApp_MassStorage_GetValidDevice(): count=%d\n", count);
    for(i=0;i<MSD_PORT_NUM;i++)
    {
        if(msAPI_MSDCtrl_IsPortChanged((EN_MSD_PORT)i))
        {
            //printf("port %u changed\n", i);
            msAPI_MSDCtrl_CheckDevicesOnPort((EN_MSD_PORT)i);
        }
    }

    for(i=0;i<count;i++)
    {
        EN_MSD_STATUS status=msAPI_MSDCtrl_GetDeviceStatus(i);
        EN_MSD_PORT type=msAPI_MSDCtrl_GetDevicePort(i);
        //printf("i=%u status=%u,type=%u\n", i,status,type);
        if(status==MSD_STATUS_BUSY||status==MSD_STATUS_IDLE||status==MSD_STATUS_INSERTED)
        {
            if(type==MSD_PORT_0)
            {
                //result|=0x10;
                u32Result |= (1<<MSD_CREADER_INDEX_START);
            }
            else
            {
                u32Result |= (1<<i);
            }
        }
        //printf(" result=%X\n", u16Result);
    }
    //printf("MApp_MassStorage_GetValidDevice : result=%04X\n",u32Result);
    return u32Result;

}

BOOLEAN MApp_MassStorage_IsGetUnsupportUsbDevice(void)
{
    if(MDrv_GetUsbDevInterfaceClass()<=0x07
    ||MDrv_GetUsbDevInterfaceClass()==0x10
    ||(MApp_MassStorage_GetValidDevice() == 0)
    )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/***************************************************************************************/

/*###############################################################################################*/
/*////////////////////////////////Mass Storage -> Device Monitor ////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_DeviceConnectionDetect(void)
{
    U8 u8DeviceStatus = 0;
  //printf("DeviceConnectDetection!!\n");

    if (MDrv_UsbDeviceConnect())
    {
		#if ENABLE_DTV_CHCEK_USB_DELAY_2S
		if(!(g_u8DTVCheckUSBFlag&DTV_CHECK_USB_WAIT_BIT))
		{
	        u8DeviceStatus |= MS_USB_CONNECTED;
		}
		#else
        u8DeviceStatus |= MS_USB_CONNECTED;
		#endif
        //u8DeviceStatus |= MS_USB2_CONNECTED;
    }

    #if ENABLE_USB_2

    if (MDrv_UsbDeviceConnect_Port2())
    {
		#if ENABLE_DTV_CHCEK_USB_DELAY_2S
		if(!(g_u8DTVCheckUSBFlag&DTV_CHECK_USB_WAIT_BIT))
		{
			u8DeviceStatus |= MS_USB2_CONNECTED;
		}
		#else
        u8DeviceStatus |= MS_USB2_CONNECTED;
		#endif
    }

    #endif

    #if ENABLE_USB_3

    if (MDrv_UsbDeviceConnect_Port3())
    {
    #if ENABLE_DTV_CHCEK_USB_DELAY_2S
		if(!(g_u8DTVCheckUSBFlag&DTV_CHECK_USB_WAIT_BIT))
		{
			u8DeviceStatus |= MS_USB3_CONNECTED;
		}
    #else
        u8DeviceStatus |= MS_USB3_CONNECTED;
    #endif
    }

    #endif

    #if ENABLE_USB_4

    if (MDrv_UsbDeviceConnect_Port4())
    {
    #if ENABLE_DTV_CHCEK_USB_DELAY_2S
		if(!(g_u8DTVCheckUSBFlag&DTV_CHECK_USB_WAIT_BIT))
		{
			u8DeviceStatus |= MS_USB4_CONNECTED;
		}
    #else
        u8DeviceStatus |= MS_USB4_CONNECTED;
    #endif
    }

    #endif

    #if ENABLE_CARDREADER
    {
        U8 u8CardStatus = MDrv_CReader_CardDetect();

        if ((u8CardStatus == DETECT_CARDEXIST_CARDCHG)||(u8CardStatus == DETECT_CARDEXIST))
        {
            //MASSSTORAGE_DBG(printf("Detect Card.\n"));
			#if ENABLE_DTV_CHCEK_USB_DELAY_2S
			if(!(g_u8DTVCheckUSBFlag&DTV_CHECK_USB_WAIT_BIT))
			{
				u8DeviceStatus |= MS_CREAD_CONNECTED;
			}
			#else
            u8DeviceStatus |= MS_CREAD_CONNECTED;
			#endif
        }
    }
    #endif //ENABLE_CARDREADER

    return u8DeviceStatus;
}

/***************************************************************************************/
/// Check valid devices and if the status is changed, reset all devices
/// @param - none
/// @return - TRUE: check successful    FALSE: check failed
/***************************************************************************************/
BOOLEAN MApp_MassStorage_DeviceStatusCheck(void)
{
    MSDCtrl_Drive pDrive;
    memset(&pDrive,0,sizeof(MSDCtrl_Drive));
    U8 u8Port=0;
    U32 u32ValidDevice;
    U8 u8Device = 0;
    U8 i;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    /*[01]get the newest valid device =================================================*/
    u32ValidDevice = MApp_FS_GetValidDevice();
    if(u32ValidDevice == s_u32CurrentValidDevice)
    {
        return TRUE;
    }
    else
    {
        s_u32CurrentValidDevice = u32ValidDevice;   //update the current valid device
    }

    /*[02]initial all device/drive status in Mapp_MassStorage() =======================*/

/* //Disable 0
    for(u8Device = 0 ; u8Device < STORAGE_DEVICE_NUM ; u8Device++)
    {
#if 1
        U8 port = msAPI_MSDCtrl_GetDevicePort(u8Device);
        printf("Initial Port[%bx] Device[%bx]",port, u8Device);
        if(port!=INVALID_MSD_PORT)
        {
            if( (msAPI_MSDCtrl_IsPortChanged(port)&&msAPI_MSDCtrl_IsPortOpened(port)) ||
                !msAPI_MSDCtrl_IsPortOpened(port))
            {
                if(msAPI_MSDCtrl_IsPortChanged(port))
                    printf(" [Port changed] ");
                if(msAPI_MSDCtrl_IsPortOpened(port))
                    printf(" [Port Opened]");
                if(!msAPI_MSDCtrl_IsPortOpened(port))
                    printf(" [Port Closed] ");
                printf(" -- initialized\n");
                for(u8Drive = 0 ; u8Drive < STORAGE_DRIVE_NUM ; u8Drive++)
                {
                    _pbDeviceStatus[port][u8Device][u8Drive] = 0;
                }
            }
            else
            {
                if(msAPI_MSDCtrl_IsPortChanged(port))
                    printf(" [Port changed] ");
                if(msAPI_MSDCtrl_IsPortOpened(port))
                    printf(" [Port Opened]");
                if(!msAPI_MSDCtrl_IsPortOpened(port))
                    printf(" [Port Closed] ");
                printf("\n");
            }
        }
        else
        {
            printf(" [Port invalid] ");
            printf(" -- initialized\n");
            for(u8Drive = 0 ; u8Drive < STORAGE_DRIVE_NUM ; u8Drive++)
            {
                _pbDeviceStatus[port][u8Device][u8Drive] = 0;
            }
        }
#else
        for(u8Drive = 0 ; u8Drive < STORAGE_DRIVE_NUM ; u8Drive++)
        {
            _pbDeviceStatus[u8Device][u8Drive] = 0;
        }
#endif

    }
*/
    /*[03]reset device and check device ===============================================*/

    for(i=0;i<MSD_PORT_NUM;i++)
    {
        if(msAPI_MSDCtrl_IsPortChanged((EN_MSD_PORT)i))
        {
            // Marked by coverity_0459
            //printf("Reset devices on Port[%bd]\n",i);

            msAPI_MSDCtrl_ResetDevicesOnPort((EN_MSD_PORT)i);
            msAPI_MSDCtrl_CheckDevicesOnPort((EN_MSD_PORT)i);
        }
    }
    //msAPI_MSDCtrl_ResetDevices();

/*  //Disable 0
    #if (N51FS)
    msAPI_MSDCtrl_CheckDevices();
    #else
    if(!msAPI_MSDCtrl_CheckDevices())
    {
        return FALSE;
    }
    #endif
*/
    /*[04]start all devices ===========================================================*/
/*  //Disable 0
    for(i=0;i<MSD_PORT_NUM;i++)
    {
        if(msAPI_MSDCtrl_IsPortChanged(i))
        {
            if(_u8TotalDriveCount>0)
            {
                _u8TotalDriveCount -= _u8TotalDriveCountPerPort[i];
            }
            _u8TotalDriveCountPerPort[i] = 0;
            _bMultiDrive[i] = FALSE;
        }
    }
*/
    for(u8Device = 0; u8Device < u8DeviceNum; u8Device++)
    {
        if(MApp_FS_GetValidDevice() & (1<<u8Device))  //<---check if the device is valid
        {
            u8Port = msAPI_MSDCtrl_GetDevicePort(u8Device);
            if(msAPI_MSDCtrl_IsPortChanged((EN_MSD_PORT)u8Port))
            {
                //printf("Port[%bd] - Device[%bd] active --> \n",msAPI_MSDCtrl_GetDevicePort(u8Device),u8Device);
                if(msAPI_FS_StartDevice(u8Device))
                {
                    /* //Disable 0
                    for(u8Drive = 0 ; u8Drive < (msAPI_FS_GetDriveCountByPort(u8Port)-_u8TotalDriveCountPerPort[u8Port]); u8Drive ++)
                    {
                        _pbDeviceStatus[u8Port][u8Device][u8Drive] = 1;
                        MASSSTORAGE_DBG(printf("Port-Device-Drive %bx-%bx-%bx is available \n",u8Port,u8Device, u8Drive));
                    }

                    if((msAPI_FS_GetDriveCountByPort(u8Port)-_u8TotalDriveCountPerPort[u8Port])>1)
                    {
                        MASSSTORAGE_DBG(printf("Connection Device is Multi-Drive\n"));
                        _bMultiDrive[u8Port] = TRUE;
                    }
                    */


                }
                else
                {
                    MASSSTORAGE_DBG(printf("msAPI_FS_StartDevice Failed\n"));
                    //return FALSE;  //<--- continue to check next
                }
            }
        }
    }

    _u8TotalDriveCount = msAPI_FS_GetDriveCount();
    for(i=0;i<MSD_PORT_NUM;i++)
    {
        _u8TotalDriveCountPerPort[i] = msAPI_FS_GetDriveCountByPort(i);
        MASSSTORAGE_DBG(printf("Total Drive on Port[%bd] = 0x%02bx \n", i,_u8TotalDriveCountPerPort[i]));

    }
    MASSSTORAGE_DBG(printf("MApp_MassStorage_DeviceStatusCheck Total Drive = 0x%02bx \n", _u8TotalDriveCount));

    U8 u8TempDeviceIndex = _u8CurrentDeviceIndex;
    //Device status is changed, clear current device index and drive inedx here.
    _u8CurrentDeviceIndex = 0xFF;
    _u8CurrentDriveIndex = 0xFF;

    for(i=0;i<STORAGE_DRIVE_NUM;i++)
    {
        if(!msAPI_FCtrl_GetDriveByIndex(i,&pDrive))
        {
            MASSSTORAGE_DBG(printf("Drive ID Fail\n"));
        }
        //Recalculate new current device index and drive index.
        //Search every drive to find previous device index.
        //If find, set new device index and drive index.
        if(pDrive.DeviceIndex == u8TempDeviceIndex)
        {
            _u8CurrentDeviceIndex = u8TempDeviceIndex;
            _u8CurrentDriveIndex = i;
        }

        u8Port = msAPI_MSDCtrl_GetDevicePort(pDrive.DeviceIndex);
        if(msAPI_FCtrl_IsDriveMounted(i) && msAPI_MSDCtrl_IsPortChanged((EN_MSD_PORT)u8Port))
        {
      //      U32 UnusedSize;
     //       U32 TotalSize;
       //     TotalSize = msAPI_FCtrl_GetTotalSizeInKB_ByDriveIndex(i);
       //     UnusedSize=msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(i);
            //printf("Drive[%bd] : Total size[%lu], Unused size[%lu]\n",i,TotalSize,UnusedSize);
        }
    }

    return TRUE;
}

/***************************************************************************************/
/// Check devices and if the status is changed, reset all devices
/// @param - none
/// @return - TRUE: check successful    FALSE: check failed
/***************************************************************************************/
BOOLEAN MApp_MassStorage_DeviceChangeStatusCheck(void)
{
    //printf("MApp_MassStorage_DeviceChangeStatusCheck() \n");
    return msAPI_MSDCtrl_DevicesChangeStatusCheck();
}

/***************************************************************************************/
/// Disconnect all devices
/// @param -  none
/// @return - TRUE: disconnect successful
/***************************************************************************************/
BOOLEAN MApp_MassStorage_DeviceDisconnect(void)
{
    U8 u8Device;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(u8Device = 0; u8Device < u8DeviceNum; u8Device++)
    {
        /*
        U8 port = msAPI_MSDCtrl_GetDevicePort(u8Device);
        if(msAPI_MSDCtrl_IsPortChanged(port))
        {
            msAPI_FS_DisconnectDeviceOnPort(u8Device);
        }
        */
        msAPI_FS_DisconnectDevice(u8Device);
    }
/*  //Disable 0
    s_u32CurrentValidDevice = 0;

    for(i=0;i<MSD_PORT_NUM;i++)
    {
        if(msAPI_MSDCtrl_IsPortChanged(i))
        {
            if(_u8TotalDriveCount>0)
            {
                _u8TotalDriveCount -= _u8TotalDriveCountPerPort[i];
            }
            _u8TotalDriveCountPerPort[i] = 0;
        }
    }
*/
    return TRUE;
}

/***************************************************************************************/
/// Connect certain drive
/// @param -  u8DriveIndex      IN: connected drive index
/// @return - TRUE: connect successful      FALSE: connect failed
/***************************************************************************************/
BOOLEAN MApp_MassStorage_DriveConnect(U8 u8DriveIndex)
{
    MSDCtrl_Drive stConnectDrive;
//    U8 u8MatchedDeviceNum = 0;
//    U8 u8Device = 0;
//    U8 u8Drive = 0;
    EN_MSD_PORT u8Port=INVALID_MSD_PORT;
    u8Port = MApp_MassStorage_GetDrivePort(u8DriveIndex);

    if(u8Port==INVALID_MSD_PORT)
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[01]mapping device index and drive index ========================================*/
    //if   ==> card reader is connected, and the device that want to connect is the last drive
    //then ==> connect to card reader
    if((MApp_FS_GetValidDevice()&(1<<MSD_CREADER_INDEX_START)) && (u8DriveIndex==(_u8TotalDriveCount-1)))
    {
        _u8CurrentDeviceIndex = MSD_CREADER_INDEX_START;
        _u8CurrentDriveIndex = u8DriveIndex;
    }
    else
    {
/*  //Disable 0
        if(_bMultiDrive[u8Port]==TRUE)  // Multi Drive
        {
            _u8CurrentDeviceIndex = (u8UI2STORAGE_TBL[0][u8DriveIndex] & 0xF0)>>4;
            _u8CurrentDriveIndex  = (u8UI2STORAGE_TBL[0][u8DriveIndex] & 0x0F);
        }
        else  // Multi Devices
        {

            u8MatchedDeviceNum = 0;
            u8Device = 0;

            while((u8MatchedDeviceNum<(u8DriveIndex+1)) && (u8Device<STORAGE_DEVICE_NUM))
            {
                if(_pbDeviceStatus[u8Port][u8Device][0]==1)
                {
                    u8MatchedDeviceNum++;
                }
                u8Device++;
            }

            _u8CurrentDeviceIndex = u8Device-1;
            _u8CurrentDriveIndex  = u8DriveIndex;
        }
*/
    }

    // //Disable 0  add
    _u8CurrentDeviceIndex = MApp_MassStorage_GetDriveDevice(u8DriveIndex);
    _u8CurrentDriveIndex  = u8DriveIndex;

    MASSSTORAGE_DBG(printf("MApp_MassStorage_DriveConnect = %bx %bx\n",_u8CurrentDeviceIndex,_u8CurrentDriveIndex ));

    /*[02]check if the given device is valid ==========================================*/
    if((MApp_FS_GetValidDevice() & (1<<_u8CurrentDeviceIndex)) == 0)
    {
        MASSSTORAGE_DBG(printf("MApp_MassStorage_DriveConnect: No such device\n"));
        return FALSE;
    }

    /*[03]get drive structure =========================================================*/
    if(!msAPI_FS_GetDriveByIndex(_u8CurrentDriveIndex, &stConnectDrive))
    {
        MASSSTORAGE_DBG(printf("MApp_MassStorage_DriveConnect: No such drive\n"));
        return FALSE;
    }

    /*[04]init mass storage ===========================================================*/
    u8MassStorageInit = TRUE;

    return TRUE;

}

/***************************************************************************************/
/// Disconnect certain drive
/// @param -  u8DriveIndex      IN: disconnected drive index
/// @return - TRUE: disconnect successful      FALSE: disconnect failed
/***************************************************************************************/
BOOLEAN MApp_MassStorage_DriveDisconnect(U8 u8DriveIndex)
{
    //U8 u8GivenDriveNo;
//    U8 u8MatchedDeviceNum=0;
//    U8 u8Device = 0;
    EN_MSD_PORT u8Port=INVALID_MSD_PORT;

    s_u32CurrentValidDevice = 0;

    u8Port = MApp_MassStorage_GetDrivePort(u8DriveIndex);

    if(_u8TotalDriveCount > 0)
    {
        _u8TotalDriveCount --;
    }

    if(u8Port==INVALID_MSD_PORT)
    {
        __ASSERT(0);
        return FALSE;
    }

    /*[01]check if there is drive to disconnect =======================================*/
    if(u8MassStorageInit == FALSE)
    {
        return TRUE;
    }
#if 0
    /*[02]mapping device index and drive index ========================================*/
    //if   ==> card reader is connected, and the device that want to disconnect is the last drive
    //then ==> disconnect to card reader
    if((MApp_FS_GetValidDevice()&(1<<MSD_CREADER_INDEX_START)) && (u8DriveIndex==(_u8TotalDriveCount-1)))
    {
        _u8CurrentDeviceIndex = MSD_CREADER_INDEX_START;
        _u8CurrentDriveIndex  = 0x0;
    }
    else
    {
        if(_bMultiDrive[u8Port]==TRUE)  // Multi Drive
        {
            _u8CurrentDeviceIndex = (u8UI2STORAGE_TBL[0][u8DriveIndex] & 0xF0)>>4;
            _u8CurrentDriveIndex  = (u8UI2STORAGE_TBL[0][u8DriveIndex] & 0x0F);
        }
        else  // Multi Devices
        {
            u8MatchedDeviceNum = 0;
            u8Device = 0;

            while((u8MatchedDeviceNum<(u8DriveIndex+1)) && (u8Device<STORAGE_DEVICE_NUM))
            {
                if(_pbDeviceStatus[u8Port][u8Device][0]==1)
                {
                    u8MatchedDeviceNum++;
                }
                u8Device++;
            }

            _u8CurrentDeviceIndex = u8Device - 1;
            _u8CurrentDriveIndex  = u8DriveIndex;
        }
    }
    MASSSTORAGE_DBG(printf("MApp_MassStorage_DriveDisconnect Device = %bx\n",_u8CurrentDeviceIndex));

    /*[03]update total drive count ====================================================*/
    if(MApp_FS_GetValidDevice() == 0)
    {
        U8 i;
        _u8TotalDriveCount = 0;
        for(i=0;i<MSD_PORT_NUM;i++)
        {
            _u8TotalDriveCountPerPort[i]=0;
        }
    }

    /*[04]look for the drive letter ===================================================*/
    for(u8GivenDriveNo=0; u8GivenDriveNo<MS_MAX_DRIVE_SUPPORT; u8GivenDriveNo++)
    {
        if(_u8CurrentDriveLetter[u8GivenDriveNo] == (u8DriveIndex+DISKMNG_DISK_LETTER_START))
        {
            break;
        }
        else if(u8GivenDriveNo == (MS_MAX_DRIVE_SUPPORT-1))
        {
            return FALSE;
        }
    }
    MASSSTORAGE_DBG(printf("MApp_MassStorage_DriveDisconnect DriveLetter = %c\n",_u8CurrentDriveLetter[u8GivenDriveNo]));

    /*[05]deinit drive ================================================================*/
    u8MassStorageInit = FALSE;
    #if (!N51FS)
    MApp_MassStorage_DeInit(_u8CurrentDriveLetter[u8GivenDriveNo]);
    #endif
#endif
    return TRUE;
}


/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
BOOLEAN MApp_MassStorage_DeviceGetStatus(U8 u8DeviceIndex, U8 u8DriveIndex)
{
    MSDCtrl_Drive stConnectDrive;
    EN_MSD_STATUS status;
    BOOLEAN DeviceStatus=FALSE;
    BOOLEAN DriveStatus=FALSE;
    /*[01]error condition =============================================================*/
    if(u8DriveIndex>STORAGE_DRIVE_NUM-1)
    {
        return 0;
    }

    /*[02]multi-drive =================================================================*/
/*
    if(_bMultiDrive==TRUE)  // Multi Drive
    {
        u8DeviceIndex = (u8UI2STORAGE_TBL[0][u8DeviceIndex]&0xF0)>>4;
        u8DriveIndex = (u8UI2STORAGE_TBL[0][u8DriveIndex]&0x0F);
    }
    else  // Multi Devices
    {
        u8DeviceIndex = (u8UI2STORAGE_TBL[1][u8DeviceIndex]&0xF0)>>4;
        u8DriveIndex = (u8UI2STORAGE_TBL[1][u8DriveIndex]&0x0F);
    }

    // 0xF in Table u8UI2STORAGE_TBL means invalid
    if((u8DriveIndex==0xF)||((u8DriveIndex==0xF)))
    {
        return 0;
    }

    MASSSTORAGE_DBG(printf("MApp_MassStorage_DeviceGetStatus %bx %bx %bx\n",u8DeviceIndex,u8DriveIndex,_pbDeviceStatus[u8DeviceIndex][u8DriveIndex]));
*/
    /*[03]return the device / drive status ============================================*/
    //return _pbDeviceStatus[u8DeviceIndex][u8DriveIndex];

    status=msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIndex);
    DriveStatus=msAPI_FS_GetDriveByIndex(u8DriveIndex,&stConnectDrive);

    if(status==MSD_STATUS_BUSY||status==MSD_STATUS_IDLE||status==MSD_STATUS_INSERTED)
    {
        DeviceStatus=TRUE;
    }

    return (DeviceStatus&&DriveStatus);

}


/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetTotalDriveNum()
{
    return _u8TotalDriveCount;
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetTotalDriveNumPerPort(EN_MSD_PORT port)
{
    if(port < MSD_PORT_NUM)
    {
        return _u8TotalDriveCountPerPort[port];
    }
    else
    {
        return 0;
    }
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetCurrentDeviceIndex()
{
    return _u8CurrentDeviceIndex;
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetCurrentDriveIndex()
{
    return _u8CurrentDriveIndex;
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
EN_MSD_PORT MApp_MassStorage_GetDrivePort(U8 drvIndex)
{
    MSDCtrl_Drive drv;
    memset(&drv,0,sizeof(MSDCtrl_Drive));
    if(drvIndex> STORAGE_DRIVE_NUM)
    {
        return INVALID_MSD_PORT;
    }

    if(msAPI_FCtrl_GetDriveByIndex(drvIndex,&drv))
    {
        return msAPI_MSDCtrl_GetDevicePort(drv.DeviceIndex);
    }
    else
    {
        return INVALID_MSD_PORT;
    }
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetDriveDevice(U8 drvIndex)
{
    MSDCtrl_Drive drv;
    memset(&drv,0,sizeof(MSDCtrl_Drive));
    if(drvIndex>STORAGE_DRIVE_NUM)
    {
        return INVALID_DEVICE_INDEX;
    }

    if(msAPI_FCtrl_GetDriveByIndex(drvIndex,&drv))
    {
        return drv.DeviceIndex;
    }
    else
    {
        return INVALID_DEVICE_INDEX;
    }
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetNextDriveIndexByDevice(U8 u8DeviceIndex, U8 u8CurrentDriveIndex)
{
    MSDCtrl_Drive drv;
    U8 u8Index = 0;

    memset(&drv,0,sizeof(MSDCtrl_Drive));


    if(u8CurrentDriveIndex >= DISK_DRIVE_NUM)
    {
        return u8CurrentDriveIndex;
    }

    while(u8Index < DISK_DRIVE_NUM)
    {
        u8CurrentDriveIndex++;
        if (u8CurrentDriveIndex == DISK_DRIVE_NUM)
            u8CurrentDriveIndex = 0;
        if(msAPI_FCtrl_GetDriveByIndex(u8CurrentDriveIndex,&drv))
        {
            if (drv.DeviceIndex == u8DeviceIndex)
            {
                break;
            }
        }
        u8Index++;
    }
    return u8CurrentDriveIndex;
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetPrevDriveIndexByDevice(U8 u8DeviceIndex, U8 u8CurrentDriveIndex)
{
    MSDCtrl_Drive drv;
    U8 u8Index = 0;

    memset(&drv,0,sizeof(MSDCtrl_Drive));

    if(u8CurrentDriveIndex >= DISK_DRIVE_NUM)
    {
        return u8CurrentDriveIndex;
    }

    while(u8Index < DISK_DRIVE_NUM)
    {
        u8CurrentDriveIndex--;
        if (u8CurrentDriveIndex >= DISK_DRIVE_NUM)
            u8CurrentDriveIndex = DISK_DRIVE_NUM-1;
        if(msAPI_FCtrl_GetDriveByIndex(u8CurrentDriveIndex,&drv))
        {
            if (drv.DeviceIndex == u8DeviceIndex)
            {
                break;
            }
        }
        u8Index++;
    }
    return u8CurrentDriveIndex;
}

/***************************************************************************************/
///
/// @param -
/// @return -
/***************************************************************************************/
U8 MApp_MassStorage_GetFirstDriveByPort(EN_MSD_PORT port)
{
    U8 u8DriveIndex = 0;

    if (port >= MSD_PORT_NUM)
        return INVALID_DRIVE_INDEX;

    for (u8DriveIndex = 0; u8DriveIndex <DISK_DRIVE_NUM; u8DriveIndex++)
    {
        if (port == MApp_MassStorage_GetDrivePort(u8DriveIndex))
            return u8DriveIndex;
    }

    return INVALID_DRIVE_INDEX;
}
/***************************************************************************************/
