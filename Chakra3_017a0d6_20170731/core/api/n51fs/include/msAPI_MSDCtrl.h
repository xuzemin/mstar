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

#ifndef MSAPI_MSDCTRL_H
#define    MSAPI_MSDCTRL_H

#if OBA2
#include "N51FS_Wrapper.h"
#else

#include "msAPI_FSCommon.h"


#define STORAGE_DRIVE_NUM DISK_DRIVE_NUM

typedef U8 (*READ_SECTOR)(void *MSDPtr, U32 StartSector, U32 SectorCount, U32 Buffer);
typedef U8 (*WRITE_SECTOR)(void *MSDPtr, U32 StartSector, U32 SectorCount, U32 Buffer);
typedef U8 (*ERASE_SECTOR)(void *MSDPtr, U32 StartSector, U32 SectorCount);


#if 0
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#endif

#define CARDREADER_MSD_PORT  MSD_PORT_0
#define USB_MSD_PORT0        MSD_PORT_1
#define USB_MSD_PORT1        MSD_PORT_2
#define CF_MSD_PORT          MSD_PORT_3
#define NAND_MSD_PORT        MSD_PORT_4

/*enum==*/
typedef enum
{
    MSD_STATUS_EMPTY,
    MSD_STATUS_BUSY,
    MSD_STATUS_IDLE,
    MSD_STATUS_INSERTED,
    MSD_STATUS_UNPLUGGED,
    MSD_STATUS_EJECTED,
    MSD_STATUS_ERROR,
}EN_MSD_STATUS;//EMPTY->INSERTED->IDLE->BUSY->IDLE->UNPLUGGED->EMPTY

typedef enum
{
    MSD_PORT_0,//Card Reader
    MSD_PORT_1,//USB 1
    MSD_PORT_2,//USB 2
    MSD_PORT_3, // CF
    MSD_PORT_4, // NAND
    MSD_PORT_NUM,
    INVALID_MSD_PORT=0xFF,
}EN_MSD_PORT;

typedef enum
{
    MSD_ALL_PORT_ENUM_DONE = 0,
    MSD_PORT_0_ENUM_PROCESSING = 1<<MSD_PORT_0, // Card Reader
    MSD_PORT_1_ENUM_PROCESSING = 1<<MSD_PORT_1, // USB 1
    MSD_PORT_2_ENUM_PROCESSING = 1<<MSD_PORT_2, // USB 2
    MSD_PORT_3_ENUM_PROCESSING = 1<<MSD_PORT_3, // CF
    MSD_PORT_4_ENUM_PROCESSING = 1<<MSD_PORT_4, // NAND
}EN_MSD_EACH_PORT_ENUM_STATE;

#ifdef ENABLE_PTP
typedef enum
{
    USB_CLASS_MSD,
    USB_CLASS_IMAGE,
    USB_CLASS_INVALID = 0xFF,
}EN_USB_CLASS;
#endif

typedef struct
{
    EN_MSD_PORT Port;
    U8 GID;
}StorageDeviceAddress;

typedef struct
{
    U8 DeviceIndex;
    EN_MSD_STATUS MSDStatus;
    StorageDeviceAddress MSDAddress;
#ifdef ENABLE_PTP
    EN_USB_CLASS DeviceClass;
#endif
}StorageDevice;







/*function ======================================================================================*/
#ifdef MSAPI_MSDCTRL_C
#define INTERFACE
#else
#define    INTERFACE extern
#endif

INTERFACE void msAPI_MSDCtrl_Init(void);


/*for sector liked IO*/
INTERFACE BOOLEAN msAPI_MSDCtrl_SectorRead(U8 u8DeviceIndex, U32 u32StartSector, U32 u32SectorCount, U32 u32BufferAddress);
INTERFACE BOOLEAN msAPI_MSDCtrl_SectorWrite(U8 u8DeviceIndex, U32 u32StartSector, U32 u32SectorCount, U32 u32BufferAddress);

INTERFACE EN_MSD_DEVICE_TYPE msAPI_MSDCtrl_GetDeviceType(U8 u8DeviceIndex);

#if FILE_SYSTEM_ENABLE_MSD_GET_BLOCK_SIZE
INTERFACE U32 msAPI_MSDCtrl_GetBlockSize(U8 u8DeviceIndex);
#endif
INTERFACE U32 msAPI_MSDCtrl_GetBlockNum(U8 u8DeviceIndex);


/*device status*/
INTERFACE void msAPI_MSDCtrl_CheckDevices(void);
#if FILE_SYSTEM_ENABLE_MSD_CHECK_DEVICES_ON_PORTS
INTERFACE void msAPI_MSDCtrl_CheckDevicesOnPort(EN_MSD_PORT port);
#endif
INTERFACE EN_MSD_STATUS msAPI_MSDCtrl_GetDeviceStatus(U8 u8DeviceIndex);
INTERFACE void msAPI_MSDCtrl_SetDeviceStatus(U8 u8DeviceIndex, EN_MSD_STATUS status);

INTERFACE U8 msAPI_MSDCtrl_GetTotalDeviceCount(void);
INTERFACE BOOLEAN msAPI_MSDCtrl_HasUnpluggedDevice(void);
INTERFACE BOOLEAN msAPI_MSDCtrl_HasEjectedDevice(void);
INTERFACE BOOLEAN msAPI_MSDCtrl_HasIdleDevice(void);
INTERFACE BOOLEAN msAPI_MSDCtrl_HasEmptyDevice(void);
INTERFACE BOOLEAN msAPI_MSDCtrl_HasConnectedDevice(void);
INTERFACE BOOLEAN msAPI_MSDCtrl_HasNewDevice(void);


INTERFACE void msAPI_MSDCtrl_EjectDevice(U8 deviceIndex);
INTERFACE void msAPI_MSDCtrl_ResetDevice(U8 deviceIndex);
INTERFACE void msAPI_MSDCtrl_ResetDevices(void);
INTERFACE void msAPI_MSDCtrl_ResetPort(EN_MSD_PORT port);
#if FILE_SYSTEM_ENABLE_MSD_RESET_PORTS
INTERFACE void msAPI_MSDCtrl_ResetPorts(void);
#endif

INTERFACE BOOLEAN msAPI_MSDCtrl_IsPortOpened(EN_MSD_PORT port);
INTERFACE BOOLEAN msAPI_MSDCtrl_IsPortEnabled(EN_MSD_PORT port);
INTERFACE EN_MSD_PORT msAPI_MSDCtrl_GetDevicePort(U8 deviceIndex);
#ifdef ENABLE_PTP
INTERFACE EN_USB_CLASS msAPI_MSDCtrl_GetDeviceClass(U8 deviceIndex);
#endif
#if FILE_SYSTEM_ENABLE_GET_MAX_DEVICE_COUNT
INTERFACE U8 msAPI_MSDCtrl_GetMaxDeviceCount(void);
#endif
INTERFACE void msAPI_MSDCtrl_ResetDevicesOnPort(EN_MSD_PORT port);
INTERFACE BOOLEAN msAPI_MSDCtrl_IsDeviceConnected(EN_MSD_PORT port);   //Check device directly
#if FILE_SYSTEM_ENABLE_MSD_IS_PORT_CHANGED
INTERFACE BOOLEAN msAPI_MSDCtrl_IsPortChanged(EN_MSD_PORT port);
#endif

#if FILE_SYSTEM_ENABLE_MSD_DEVICES_CHANGE_STATUS_CHECK
INTERFACE BOOLEAN msAPI_MSDCtrl_DevicesChangeStatusCheck(void);
#endif

INTERFACE U8 msAPI_MSDCtrl_CheckDevices_Ex(void);

extern U8  MDrv_GetUsbDeviceStatus(void);
#define msAPI_GetUsbDeviceStatus() MDrv_GetUsbDeviceStatus()
#define msAPI_GetUsbDeviceStatusPort2() MDrv_GetUsbDeviceStatusPort2()
#define msAPI_GetUsbDeviceStatusPort3() MDrv_GetUsbDeviceStatusPort3()
#define msAPI_GetUsbDeviceStatusPort4() MDrv_GetUsbDeviceStatusPort4()

#undef INTERFACE
#endif /*OBAMA*/
#endif    /*_MSAPI_MSDCTRL_H END */
