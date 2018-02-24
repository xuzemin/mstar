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
#define  MSAPI_MSDCTRL_C

#include "Board.h"
#include "MsCommon.h"
#include "msAPI_FSCommon.h"
#include "msAPI_FSEnv.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "debug.h"
#include "drvUSB.h"
#include "SysInit.h"

#if ENABLE_CARDREADER
#include "drvCReader.h"
#endif

#if ENABLE_NAND
#include "drvnand_if.h"
#endif

// shjang_070816 change
#include "msAPI_MSDCtrl.h"

#define MSD_DBG(x)  //x;

//static global status
static BOOLEAN g_bMSDPortOpened[MSD_PORT_NUM];
static BOOLEAN g_bMSDPortChanged[MSD_PORT_NUM];
static BOOLEAN g_bMSDPortIsConnected[MSD_PORT_NUM];

#define FS_CardReaderWrite(x,y,z)    MDrv_CReader_Write(x,y,z)
#define FS_CardReaderRead(x,y,z)    MDrv_CReader_Read(x,y,z)

#if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
U8 gu8CurrentSlot;
#endif

#if ENABLE_USB
U8 g_u8USBCardReaderStatus=0xff;
#endif

#if (ENABLE_USB_2||ENABLE_USB_3||ENABLE_USB_4)
U8 g_u8USB2CardReaderStatus=0xff;
#endif

static void MSD_ClosePort(EN_MSD_PORT port)
{
    if(port==MSD_PORT_0)
    {
      #if ENABLE_CARDREADER
        g_bMSDPortOpened[MSD_PORT_0]=0;
        //nothing to do??
      #else
        __ASSERT(0);
      #endif
    }
    else if(port==MSD_PORT_1)
    {
      #if ENABLE_USB
        g_bMSDPortOpened[MSD_PORT_1]=0;
        MDrv_UsbClose();
      #else
        __ASSERT(0);
      #endif
    }
    else if(port==MSD_PORT_2)
    {
      #if ENABLE_USB_2
        g_bMSDPortOpened[MSD_PORT_2]=0;
        MDrv_UsbClose_Port2();
      #else
        __ASSERT(0);
      #endif
    }
    else if (port == MSD_PORT_3)
    {
        #if defined(ENABLE_CF) && (ENABLE_CF == 1)
            g_bMSDPortOpened[MSD_PORT_3]=0;
        #else
            __ASSERT(0);
        #endif
    }
    else if (port == MSD_PORT_4)
    {
        #if (ENABLE_NAND)
            g_bMSDPortOpened[MSD_PORT_4] = 0;
        #else
            __ASSERT(0);
        #endif
    }
    else
    {
        __ASSERT(0);
    }
}


U8 MSD_GetDeviceIDByMSDAddress(EN_MSD_PORT port,U8 GID)
{
    U8 u8index=INVALID_DEVICE_INDEX;

    if(GID==0xFF)
    {
        __ASSERT(0);
        return INVALID_DEVICE_INDEX;
    }
    if(port>MSD_PORT_NUM)
    {
        __ASSERT(0);
        return INVALID_DEVICE_INDEX;
    }

    if(!msAPI_MSDCtrl_IsPortEnabled(port))
    {
        __ASSERT(0);
        return INVALID_DEVICE_INDEX;
    }

    switch (port)
    {
        case MSD_PORT_0:
        {
            u8index=GID+MSD_CREADER_INDEX_START;
            return u8index;
        }
        case MSD_PORT_1:
        {
            u8index=GID+MSD_USB_INDEX_START;
            return u8index;
        }
        case MSD_PORT_2:
        {
            u8index=GID+MSD_USB_2_INDEX_START;
            return u8index;
        }
        case MSD_PORT_3:
        {
            #if(ENABLE_USB_3 )
            u8index = GID + MSD_USB_3_INDEX_START;
            #else
            u8index = GID + MSD_CF_INDEX_START;
            #endif
            return u8index;
        }
        case MSD_PORT_4:
        {
            #if(ENABLE_USB_4 )
            u8index = GID + MSD_USB_4_INDEX_START;
            #else
            u8index = GID + MSD_NAND_INDEX_START;
            #endif
            return u8index;
        }
        default:
            return INVALID_DEVICE_INDEX;
     }

}

static void MSD_SetPortConnected(EN_MSD_PORT port, BOOLEAN isConnected)
{
    if(port >= MSD_PORT_NUM)
    {
        __ASSERT(0);
        return;
    }
    g_bMSDPortIsConnected[port]=isConnected;
}

BOOLEAN msAPI_MSDCtrl_IsPortConnected(EN_MSD_PORT port)
{
    if(port >= MSD_PORT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }
    return g_bMSDPortIsConnected[port];
}

static void MSD_SetPortChanged(EN_MSD_PORT port, BOOLEAN isChanged)
{
    if(port >= MSD_PORT_NUM)
    {
        __ASSERT(0);
        return;
    }
    g_bMSDPortChanged[port]=isChanged;
}

#if FILE_SYSTEM_ENABLE_MSD_IS_PORT_CHANGED
BOOLEAN msAPI_MSDCtrl_IsPortChanged(EN_MSD_PORT port)
{
    if(port >= MSD_PORT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }
    return g_bMSDPortChanged[port];
}
#endif

static void MSD_SetPortOpened(EN_MSD_PORT port, BOOLEAN isOpened)
{
    if(port >= MSD_PORT_NUM)
    {
        __ASSERT(0);
        return;
    }
    g_bMSDPortOpened[port]=isOpened;
}

#if ((ENABLE_USB||ENABLE_USB_2||ENABLE_USB_3||ENABLE_USB_4) || (ENABLE_CARDREADER) || (defined(ENABLE_CF)&&(ENABLE_CF == 1)) )
//status is not set
static void MSD_RegisterDevice(U8 deviceIndex,EN_MSD_PORT port,U8 GID)
{
    StorageDevice* pDevice;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    if(deviceIndex>=u8DeviceNum)
    {
        __ASSERT(0);
        return;
    }

    pDevice=(StorageDevice xdata*)msAPI_FS_GetAddr(STORAGE_DEVICE_MEMORY_ADDR);

    pDevice[deviceIndex].DeviceIndex=deviceIndex;
    pDevice[deviceIndex].MSDAddress.GID=GID;
    pDevice[deviceIndex].MSDAddress.Port=port;
}
#endif

#ifdef ENABLE_PTP
static void MSD_SetDeviceClass(U8 deviceIndex,EN_USB_CLASS class)
{
    StorageDevice* pDevice;
    U16 addr;

    if(deviceIndex>=STORAGE_DEVICE_NUM)
    {
        __ASSERT(0);
        return;
    }

    addr = (STORAGE_DEVICE_MEMORY_ADDR>>12);
    pDevice=(StorageDevice xdata*)msAPI_FS_GetXData(addr);
    pDevice[deviceIndex].DeviceClass=class;
    msAPI_FS_ReturnXData();
}
#endif

#if 0
//status is not set
static void MSD_DeregisterDevice(U8 deviceIndex)
{
    StorageDevice* pDevice;
    U16 addr;

    if(deviceIndex>=STORAGE_DEVICE_NUM)
    {
        __ASSERT(0);
        return;
    }

    addr = (STORAGE_DEVICE_MEMORY_ADDR>>12);
    pDevice=(StorageDevice xdata*)msAPI_FS_GetXData(addr);
    pDevice[deviceIndex].DeviceIndex=INVALID_DEVICE_INDEX;
    pDevice[deviceIndex].MSDAddress.GID=0xFF;
    pDevice[deviceIndex].MSDAddress.Port=INVALID_MSD_PORT;
    msAPI_FS_ReturnXData();
}
#endif

#if ((ENABLE_USB) || (ENABLE_USB_2)||(ENABLE_USB_3)||(ENABLE_USB_4) || (ENABLE_CARDREADER) || (defined(ENABLE_CF)&&(ENABLE_CF == 1)) )
static void MSD_DeviceStatusControlInserted(U8 deviceIndex)
{
    if(msAPI_MSDCtrl_GetDeviceStatus(deviceIndex) == MSD_STATUS_EMPTY)
    {
        msAPI_MSDCtrl_SetDeviceStatus(deviceIndex,MSD_STATUS_INSERTED);
    }
}
#endif

#if (ENABLE_USB|| ENABLE_USB_2||ENABLE_USB_3||ENABLE_USB_4)
static void MSD_DeviceStatusControlUnplugged(U8 deviceIndex)
{
    EN_MSD_STATUS status = msAPI_MSDCtrl_GetDeviceStatus(deviceIndex);
    switch(status)
    {
        case MSD_STATUS_EMPTY:
        case MSD_STATUS_UNPLUGGED:
            break;
        case MSD_STATUS_EJECTED:
        case MSD_STATUS_IDLE:
        case MSD_STATUS_INSERTED:
            msAPI_MSDCtrl_SetDeviceStatus(deviceIndex, MSD_STATUS_UNPLUGGED);
            MSD_DBG(printf("  Set Device=%bu unplugged\n", deviceIndex););
            break;
        case MSD_STATUS_BUSY:
        default:
            msAPI_MSDCtrl_SetDeviceStatus(deviceIndex, MSD_STATUS_ERROR);
            MSD_DBG(printf("  Set Device=%bu error\n", deviceIndex););
            break;
    }
}
#endif

BOOLEAN msAPI_MSDCtrl_IsPortEnabled(EN_MSD_PORT port)
{
    switch (port)
    {
      #if ENABLE_CARDREADER
        case MSD_PORT_0:
            return TRUE;
      #endif
      #if ENABLE_USB
        case MSD_PORT_1:
            return TRUE;
      #endif
      #if ENABLE_USB_2
        case MSD_PORT_2:
            return TRUE;
      #endif

      #if (defined(ENABLE_CF) && (ENABLE_CF == 1)||(ENABLE_USB_3))
        case MSD_PORT_3:
            return TRUE;
      #endif

      #if ((ENABLE_NAND)||(ENABLE_USB_4))
        case MSD_PORT_4:
            return TRUE;
      #endif
        default:
            return FALSE;
    };

}


extern void msAPI_FCtrl_UnmountDrivesOnDevice(U8 deviceIndex);
void msAPI_MSDCtrl_EjectDevice(U8 deviceIndex)
{
    StorageDevice* pDevice;

    pDevice=(StorageDevice xdata*)msAPI_FS_GetAddr(STORAGE_DEVICE_MEMORY_ADDR);

    pDevice[deviceIndex].MSDStatus=MSD_STATUS_EJECTED;

    msAPI_FCtrl_UnmountDrivesOnDevice(deviceIndex);

    MSD_DBG(printf("  MSDDevice=%bu ejected!!\n",(U8)deviceIndex));

}



void msAPI_MSDCtrl_ResetDevice(U8 deviceIndex)
{

    StorageDevice* pDevice;

    msAPI_FCtrl_UnmountDrivesOnDevice(deviceIndex);

    pDevice=(StorageDevice xdata*)msAPI_FS_GetAddr(STORAGE_DEVICE_MEMORY_ADDR);

    pDevice[deviceIndex].MSDStatus=MSD_STATUS_EMPTY;
    pDevice[deviceIndex].MSDAddress.GID=0xFF;
    pDevice[deviceIndex].MSDAddress.Port=INVALID_MSD_PORT;
    pDevice[deviceIndex].DeviceIndex=INVALID_DEVICE_INDEX;
#ifdef ENABLE_PTP
    pDevice[deviceIndex].DeviceClass=USB_CLASS_INVALID;
#endif

    MSD_DBG(printf("  MSDDevice=%bu reseted!!\n",(U8)deviceIndex));

}

void msAPI_MSDCtrl_ResetDevicesOnPort(EN_MSD_PORT port)
{
    U8 i=0;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i=0;i<u8DeviceNum;i++)
    {
        if(msAPI_MSDCtrl_GetDevicePort(i)==port)
        {
            msAPI_MSDCtrl_ResetDevice(i);
        }
    }
}

void msAPI_MSDCtrl_ResetPort(EN_MSD_PORT port)
{
    if(msAPI_MSDCtrl_IsPortEnabled(port))
    {
        msAPI_MSDCtrl_ResetDevicesOnPort(port);
        MSD_ClosePort(port);
        MSD_DBG(printf("  MSDPort=%u reseted!!\n",(U8)port));
    }
}

BOOLEAN msAPI_MSDCtrl_CheckUSBCardReaderChanged(EN_MSD_PORT port)
{
    switch(port)
    {
    #if ENABLE_USB
        case MSD_PORT_1:
        {
            U8 u8Temp;
        #ifdef USB_HID_ENABLE
            if(MDrv_GetUsbDeviceType() != USB_INTERFACE_CLASS_HID)
         #endif
            {
                u8Temp = MDrv_GET_MASS_VALID_LUN();
                if(u8Temp != 0xff && u8Temp != g_u8USBCardReaderStatus)
                {
                    #if 0 //We met a compatible issue with SEC android phone. Actually, we don't need this.
                    if(g_u8USBCardReaderStatus == 0)
                    {
                        msAPI_MSDCtrl_ResetPort(MSD_PORT_1);
                    }
                    #endif
                    g_u8USBCardReaderStatus=u8Temp;
                    MSD_SetPortChanged(MSD_PORT_1, TRUE);
                    MS_DEBUG_MSG(printf("USB Card Reader changed!\n"));
                    return TRUE;
                }
            }
        }
        break;
    #endif

    #if ENABLE_USB_2
        case MSD_PORT_2:
        {
            U8 u8Temp;
        #ifdef USB2_HID_ENABLE
            if(MDrv_GetUsbDeviceType_Port2() != USB_INTERFACE_CLASS_HID)
         #endif
            {
                u8Temp = MDrv_GET_MASS_VALID_LUN_PORT2();
                if(u8Temp != 0xff && u8Temp != g_u8USB2CardReaderStatus)
                {
                    #if 0 //We met a compatible issue with SEC android phone. Actually, we don't need this.
                    if(g_u8USB2CardReaderStatus == 0)
                    {
                        msAPI_MSDCtrl_ResetPort(MSD_PORT_2);
                    }
                    #endif
                    g_u8USB2CardReaderStatus=u8Temp;
                    MSD_SetPortChanged(MSD_PORT_2, TRUE);
                    MS_DEBUG_MSG(printf("USB_2 Card Reader changed!\n"));
                    return TRUE;
                }
            }
        }
        break;
    #endif

        default:
            return FALSE;
        break;
    }
    return FALSE;
}

#if FILE_SYSTEM_ENABLE_MSD_RESET_PORTS
void msAPI_MSDCtrl_ResetPorts()
{
    U8 i=0;
    for(i=0;i<MSD_PORT_NUM;i++)
    {
        if(msAPI_MSDCtrl_IsPortEnabled((EN_MSD_PORT)i))
        {
            msAPI_MSDCtrl_ResetPort((EN_MSD_PORT)i);
        }
    }
}
#endif

void msAPI_MSDCtrl_ResetDevices()
{
    U8 i=0;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i=0;i<u8DeviceNum;i++)
    {
        msAPI_MSDCtrl_ResetDevice(i);
    }
}


#if (ENABLE_CARDREADER)

#if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)

static void MSD_CheckMSDPort0Devices(void)
{
    U8 ret = MDrv_CReader_CardDetect();
    U8 deviceIndex = MSD_GetDeviceIDByMSDAddress(MSD_PORT_0,0);

    if (ret == STS_CR_SD_MS_XD_CARDCHG ||
        ret == STS_CR_CF_SDMSXD_CARDCHG)
    {
        MSD_DBG(printf("MSD : card reader is just inserted\n"););

        gu8CurrentSlot = SLOT_4IN1;
        if(MDrv_CReader_WaitCardReady(eSD_MS_XD) != STS_CR_CARD_INIT_OK)
        {
            MSD_DBG(printf("wait cr rdy failed\n"););
            return;
        }

        MSD_SetPortOpened(MSD_PORT_0,TRUE);
        MSD_RegisterDevice(deviceIndex,MSD_PORT_0,0);
        MSD_DeviceStatusControlInserted(deviceIndex);
    }
    else if (
        ret == STS_CR_SDCARD ||
        ret == STS_CR_MSCARD ||
        ret == STS_CR_XDCARD ||
        ret == STS_CR_SMCARD ||
        ret == STS_CR_CF_SDCARD ||
        ret == STS_CR_CF_MSCARD ||
        ret == STS_CR_CF_SMCARD ||
        ret == STS_CR_CF_XDCARD)
    {
        MSD_DBG(printf("MSD : card reader is ready\n"););
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_0))
        {
            gu8CurrentSlot = SLOT_4IN1;
            if(!MDrv_CReader_WaitCardReady(eSD_MS_XD))
            {
                MSD_DBG(printf("wait card rdy failed\n"););
                return;
            }

            MSD_SetPortOpened(MSD_PORT_0,TRUE);
            MSD_RegisterDevice(deviceIndex,MSD_PORT_0,0);
            MSD_DeviceStatusControlInserted(deviceIndex);
        }
    }
    else if(ret == STS_CR_NOMEDIA)
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_0))
        {
           MSD_SetPortOpened(MSD_PORT_0,FALSE);
           msAPI_MSDCtrl_ResetPort(MSD_PORT_0);
        }
    }
}

#else // non CERAMAL project

static void MSD_CheckMSDPort0Devices(void)
{
    U8 ret = MDrv_CReader_CardDetect();
    U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_0,0);

    if(ret == DETECT_CARDEXIST_CARDCHG)
    {
        MSD_DBG(printf("MSD : card reader is just inserted\n"););
        if(!MDrv_CReader_WaitCardReady())
        {
            MSD_DBG(printf("  card not ready!!\r\n"););
            return;
        }

        MSD_SetPortOpened(MSD_PORT_0,TRUE);
        MSD_RegisterDevice(deviceIndex,MSD_PORT_0,0);
        MSD_DeviceStatusControlInserted(deviceIndex);

    }
    else if(ret == DETECT_CARDEXIST)
    {
        MSD_DBG(printf("MSD : card reader is ready\n"););
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_0))
        {
            if(!MDrv_CReader_WaitCardReady())
            {
                MSD_DBG(printf("  card ready failed!!\r\n",0););
                return;
            }

            MSD_SetPortOpened(MSD_PORT_0,TRUE);

        }

            MSD_RegisterDevice(deviceIndex,MSD_PORT_0,0);
            MSD_DeviceStatusControlInserted(deviceIndex);

        }
    else if(ret == DETECT_NOCARD_CARDCHG || ret == DETECT_NOCARD)
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_0))
        {
           MSD_SetPortOpened(MSD_PORT_0,FALSE);
           msAPI_MSDCtrl_ResetPort(MSD_PORT_0);
        }

    }
}
#endif // #if CERAMAL_N51FS
#endif


#if (ENABLE_USB)
static U8 MSD_GetMSDPort1LUNCount(void)
{
    U8 u8Max=MDrv_UsbGetMaxLUNCount();
    u8Max = (u8Max > MSD_USB_NUM) ? MSD_USB_NUM: u8Max;
    return u8Max;
}

//USB
static void MSD_CheckMSDPort1Devices(void)
{
    U8 lun=0xFF;
    U8 count=0;
    if(MDrv_UsbDeviceConnect())
    {
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_1))
        {
MDrv_Sys_DisableWatchDog();
            FS_RESET_WDT();
            if(MDrv_Usb_Device_Enum()==FALSE)
            {
                MSD_DBG(printf("P1 DEVICE ENUM FAILED!!\n"););
                //MDrv_UsbClose();
                //return;
            }
MDrv_Sys_EnableWatchDog();

            MSD_SetPortOpened(MSD_PORT_1,TRUE);

        }

#ifdef ENABLE_PTP
        //if (MDrv_GetUsbDeviceType() == USB_INTERFACE_CLASS_MSD)
        if (0)
        {
            count=MSD_GetMSDPort1LUNCount();
            lun = MDrv_GET_MASS_VALID_LUN();
            if(lun == 0xFF)
            {
                MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                return;
            }
            else
            {
                U8 i=0;
                for(i=0;i<MSD_USB_NUM;i++)
                {
                    BOOLEAN ready=(lun>>(i))&1;
                    U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_1,i);

                    if(ready)
                    {
                        MSD_RegisterDevice(deviceIndex,MSD_PORT_1,i);
                        MSD_SetDeviceClass(deviceIndex,USB_CLASS_MSD);
                        MSD_DeviceStatusControlInserted(deviceIndex);
                    }
                    else
                    {
                        MSD_DeviceStatusControlUnplugged(deviceIndex);
                    }
                }
            }
        }
        //else if (MDrv_GetUsbDeviceType() == USB_INTERFACE_CLASS_IMAGE)
        else
        {
            // Assume one drive.
            U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_1,0);

            MSD_RegisterDevice(deviceIndex,MSD_PORT_1,0);
            MSD_SetDeviceClass(deviceIndex,USB_CLASS_IMAGE);
            MSD_DeviceStatusControlInserted(deviceIndex);
        }
#else
        count=MSD_GetMSDPort1LUNCount();
 MDrv_Sys_DisableWatchDog();
        lun = MDrv_GET_MASS_VALID_LUN();
MDrv_Sys_EnableWatchDog();
        g_u8USBCardReaderStatus = lun;
        if(lun == 0xFF)
        {
             MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
             return;
        }
        else
        {
            U8 i=0;
            for(i=0;i<MSD_USB_NUM;i++)
            {

                BOOLEAN ready=(lun>>(i))&1;
                U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_1,i);

                if(ready)
                {
                    MSD_RegisterDevice(deviceIndex,MSD_PORT_1,i);
                    MSD_DeviceStatusControlInserted(deviceIndex);
                }
                else
                {
                    MSD_DeviceStatusControlUnplugged(deviceIndex);
                }
            }

        }
#endif
    }
    else
    {

        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_1))
        {
            MSD_SetPortOpened(MSD_PORT_1,FALSE);
            msAPI_MSDCtrl_ResetPort(MSD_PORT_1);
        }
    }
}
#endif

#if ENABLE_USB_2
static U8 MSD_GetMSDPort2LUNCount(void)
{
    U8 u8Max=MDrv_UsbGetMaxLUNCount_Port2();
    u8Max = (u8Max > MSD_USB_2_NUM) ? MSD_USB_2_NUM: u8Max;
    return u8Max;
}

static void MSD_CheckMSDPort2Devices(void)
{
    U8 lun=0xFF;
    U8 count=0;
    U8 i=0;
    U8 u8Iend;
    if(MDrv_UsbDeviceConnect_Port2())
    {
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_2))
        {
MDrv_Sys_DisableWatchDog();
            FS_RESET_WDT();
            if(MDrv_Usb_Device_Enum_Port2()==FALSE)
            {
                MSD_DBG(printf("P2 DEVICE ENUM FAILED!!\n"););
                //MDrv_UsbClose();
                //return;
            }
MDrv_Sys_EnableWatchDog();
            MSD_SetPortOpened(MSD_PORT_2,TRUE);
        }

#ifdef ENABLE_PTP
        //if (MDrv_GetUsbDeviceType_Port2() == USB_INTERFACE_CLASS_MSD)
        if (1)
        {
            count=MSD_GetMSDPort2LUNCount();
            lun = MDrv_GET_MASS_VALID_LUN_PORT2();
            if(lun == 0xFF)
            {
                MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                return;
            }
            else
            {
                u8Iend = MSD_USB_NUM;
                for(i=0;i<u8Iend;i++)
                {
                    BOOLEAN ready=(lun>>(i))&1;
                    U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_2,i);

                    if(ready)
                    {
                        MSD_RegisterDevice(deviceIndex,MSD_PORT_2,i);
                        MSD_SetDeviceClass(deviceIndex,USB_CLASS_MSD);
                        MSD_DeviceStatusControlInserted(deviceIndex);
                    }
                    else
                    {
                        MSD_DeviceStatusControlUnplugged(deviceIndex);
                    }
                }
            }
        }
        else if (MDrv_GetUsbDeviceType_Port2() == USB_INTERFACE_CLASS_IMAGE)
        {
            // Assume one drive.
            U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_2,0);

            MSD_RegisterDevice(deviceIndex,MSD_PORT_2,0);
            MSD_SetDeviceClass(deviceIndex,USB_CLASS_IMAGE);
            MSD_DeviceStatusControlInserted(deviceIndex);
        }
#else
        count=MSD_GetMSDPort2LUNCount();
MDrv_Sys_DisableWatchDog();
        lun = MDrv_GET_MASS_VALID_LUN_PORT2();
MDrv_Sys_EnableWatchDog();
        g_u8USB2CardReaderStatus = lun;
        if(lun == 0xFF)
        {
             MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
             return;
        }
        else
        {
            u8Iend = MSD_USB_2_NUM;
            for(i=0;i<u8Iend;i++)
            {
                BOOLEAN ready=(lun>>(i))&1;
                U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_2,i);

                if(ready)
                {
                    MSD_RegisterDevice(deviceIndex,MSD_PORT_2,i);
                    MSD_DeviceStatusControlInserted(deviceIndex);
                }
                else
                {
                    MSD_DeviceStatusControlUnplugged(deviceIndex);
                }
            }
        }
#endif
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_2))
        {
            MSD_SetPortOpened(MSD_PORT_2,FALSE);
            msAPI_MSDCtrl_ResetPort(MSD_PORT_2);
        }
    }
}

#endif

#if (defined(ENABLE_USB_3) && (ENABLE_USB_3 == 1)) || (defined(ENABLE_CF) && (ENABLE_CF == 1))
#if (defined(ENABLE_USB_3) && (ENABLE_USB_3 == 1))
static U8 MSD_GetMSDPort3LUNCount(void)
{
    U8 u8Max=MDrv_UsbGetMaxLUNCount_Port3();
    u8Max = (u8Max > MSD_USB_3_NUM) ? MSD_USB_3_NUM: u8Max;
    return u8Max;
}

static void MSD_CheckMSDPort3Devices(void)
{
    U8 lun=0xFF;
    U8 count=0;
    U8 i=0;
    U8 u8Iend;
    if(MDrv_UsbDeviceConnect_Port3())
    {
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_3))
        {
MDrv_Sys_DisableWatchDog();
            FS_RESET_WDT();
            if(MDrv_Usb_Device_Enum_Port3()==FALSE)
            {
                MSD_DBG(printf("P3 DEVICE ENUM FAILED!!\n"););
                //MDrv_UsbClose();
                //return;
            }
MDrv_Sys_EnableWatchDog();
            MSD_SetPortOpened(MSD_PORT_3,TRUE);
        }

#ifdef ENABLE_PTP
        //if (MDrv_GetUsbDeviceType_Port3() == USB_INTERFACE_CLASS_MSD)
        if (1)
        {
            count=MSD_GetMSDPort3LUNCount();
            lun = MDrv_GET_MASS_VALID_LUN_PORT3();
            if(lun == 0xFF)
            {
                MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                return;
            }
            else
            {
                u8Iend = MSD_USB_NUM;
                for(i=0;i<u8Iend;i++)
                {
                    BOOLEAN ready=(lun>>(i))&1;
                    U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_3,i);

                    if(ready)
                    {
                        MSD_RegisterDevice(deviceIndex,MSD_PORT_3,i);
                        MSD_SetDeviceClass(deviceIndex,USB_CLASS_MSD);
                        MSD_DeviceStatusControlInserted(deviceIndex);
                    }
                    else
                    {
                        MSD_DeviceStatusControlUnplugged(deviceIndex);
                    }
                }
            }
        }
        else if (MDrv_GetUsbDeviceType_Port3() == USB_INTERFACE_CLASS_IMAGE)
        {
            // Assume one drive.
            U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_3,0);

            MSD_RegisterDevice(deviceIndex,MSD_PORT_3,0);
            MSD_SetDeviceClass(deviceIndex,USB_CLASS_IMAGE);
            MSD_DeviceStatusControlInserted(deviceIndex);
        }
#else
        count=MSD_GetMSDPort3LUNCount();
        MDrv_Sys_DisableWatchDog();
        lun = MDrv_GET_MASS_VALID_LUN_PORT3();
        MDrv_Sys_EnableWatchDog();
        g_u8USB2CardReaderStatus = lun;
        if(lun == 0xFF)
        {
             MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
             return;
        }
        else
        {
            u8Iend = MSD_USB_3_NUM;
            for(i=0;i<u8Iend;i++)
            {
                BOOLEAN ready=(lun>>(i))&1;
                U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_3,i);

                if(ready)
                {
                    MSD_RegisterDevice(deviceIndex,MSD_PORT_3,i);
                    MSD_DeviceStatusControlInserted(deviceIndex);
                }
                else
                {
                    MSD_DeviceStatusControlUnplugged(deviceIndex);
                }
            }
        }
#endif
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_3))
        {
            MSD_SetPortOpened(MSD_PORT_3,FALSE);
            msAPI_MSDCtrl_ResetPort(MSD_PORT_3);
        }
    }
}

#elif defined(ENABLE_CF) && (ENABLE_CF == 1)
static void MSD_CheckMSDPort3Devices(void)
{
    U8 ret = MDrv_CReader_CardDetect();
    U8 deviceIndex = MSD_GetDeviceIDByMSDAddress(MSD_PORT_3,0);

    if (ret == STS_CR_CF_CARDCHG ||
        ret == STS_CR_CF_SDMSXD_CARDCHG)
    {
        MSD_DBG(printf("MSD : CF is just inserted\n"););

        gu8CurrentSlot = SLOT_CF;
        if(MDrv_CReader_WaitCardReady(eCF) != STS_CR_CARD_INIT_OK)
        {
            MSD_DBG(printf("wait CF rdy failed\n"););
            return;
        }

        MSD_SetPortOpened(MSD_PORT_3,TRUE);
        MSD_RegisterDevice(deviceIndex,MSD_PORT_3,0);
        MSD_DeviceStatusControlInserted(deviceIndex);
    }
    else if (
        ret == STS_CR_CFCARD ||
        ret == STS_CR_CF_SDCARD ||
        ret == STS_CR_CF_MSCARD ||
        ret == STS_CR_CF_SMCARD ||
        ret == STS_CR_CF_XDCARD)
    {
        MSD_DBG(printf("MSD : CF reader is ready\n"););
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_3))
        {
            gu8CurrentSlot = SLOT_CF;
            if(!MDrv_CReader_WaitCardReady(eCF))
            {
                printf("wait CF rdy failed\n");
                return;
            }

            MSD_SetPortOpened(MSD_PORT_3,TRUE);
            MSD_RegisterDevice(deviceIndex,MSD_PORT_3,0);
            MSD_DeviceStatusControlInserted(deviceIndex);
        }
    }
    else if(ret == STS_CR_NOMEDIA)
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_3))
        {
           MSD_SetPortOpened(MSD_PORT_3,FALSE);
           msAPI_MSDCtrl_ResetPort(MSD_PORT_3);
        }
    }
}
#endif
#endif

#if (defined(ENABLE_USB_4) && (ENABLE_USB_4 == 1)) || ENABLE_NAND
#if (defined(ENABLE_USB_4) && (ENABLE_USB_4 == 1))
static U8 MSD_GetMSDPort4LUNCount(void)
{
    U8 u8Max=MDrv_UsbGetMaxLUNCount_Port4();
    u8Max = (u8Max > MSD_USB_4_NUM) ? MSD_USB_4_NUM: u8Max;
    return u8Max;
}

static void MSD_CheckMSDPort4Devices(void)
{
    U8 lun=0xFF;
    U8 count=0;
    U8 i=0;
    U8 u8Iend;
    if(MDrv_UsbDeviceConnect_Port4())
    {
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_4))
        {
MDrv_Sys_DisableWatchDog();
            FS_RESET_WDT();
            if(MDrv_Usb_Device_Enum_Port4()==FALSE)
            {
                MSD_DBG(printf("P3 DEVICE ENUM FAILED!!\n"););
                //MDrv_UsbClose();
                //return;
            }
MDrv_Sys_EnableWatchDog();
            MSD_SetPortOpened(MSD_PORT_4,TRUE);
        }

#ifdef ENABLE_PTP
        //if (MDrv_GetUsbDeviceType_Port4() == USB_INTERFACE_CLASS_MSD)
        if (1)
        {
            count=MSD_GetMSDPort4LUNCount();
            lun = MDrv_GET_MASS_VALID_LUN_PORT4();
            if(lun == 0xFF)
            {
                MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                return;
            }
            else
            {
                u8Iend = MSD_USB_NUM;
                for(i=0;i<u8Iend;i++)
                {
                    BOOLEAN ready=(lun>>(i))&1;
                    U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_4,i);

                    if(ready)
                    {
                        MSD_RegisterDevice(deviceIndex,MSD_PORT_4,i);
                        MSD_SetDeviceClass(deviceIndex,USB_CLASS_MSD);
                        MSD_DeviceStatusControlInserted(deviceIndex);
                    }
                    else
                    {
                        MSD_DeviceStatusControlUnplugged(deviceIndex);
                    }
                }
            }
        }
        else if (MDrv_GetUsbDeviceType_Port4() == USB_INTERFACE_CLASS_IMAGE)
        {
            // Assume one drive.
            U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_4,0);

            MSD_RegisterDevice(deviceIndex,MSD_PORT_4,0);
            MSD_SetDeviceClass(deviceIndex,USB_CLASS_IMAGE);
            MSD_DeviceStatusControlInserted(deviceIndex);
        }
#else
        count=MSD_GetMSDPort4LUNCount();
MDrv_Sys_DisableWatchDog();
        lun = MDrv_GET_MASS_VALID_LUN_PORT4();
MDrv_Sys_EnableWatchDog();
        g_u8USB2CardReaderStatus = lun;
        if(lun == 0xFF)
        {
             MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
             return;
        }
        else
        {
            u8Iend = MSD_USB_4_NUM;
            for(i=0;i<u8Iend;i++)
            {
                BOOLEAN ready=(lun>>(i))&1;
                U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_4,i);

                if(ready)
                {
                    MSD_RegisterDevice(deviceIndex,MSD_PORT_4,i);
                    MSD_DeviceStatusControlInserted(deviceIndex);
                }
                else
                {
                    MSD_DeviceStatusControlUnplugged(deviceIndex);
                }
            }
        }
#endif
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_4))
        {
            MSD_SetPortOpened(MSD_PORT_4,FALSE);
            msAPI_MSDCtrl_ResetPort(MSD_PORT_4);
        }
    }
}
#elif ENABLE_NAND
static void MSD_CheckMSDPort4Devices(void)
{
    U8 deviceIndex = MSD_GetDeviceIDByMSDAddress(MSD_PORT_4,0);
    U8 u8Retry = 4;
    NC_NAND_STATUS eStatus;

    printf("check port 4\n");

    do {
        eStatus = MDrv_NAND_CheckReady();
        if(u8Retry-- == 0x00)
            break;
    } while (eStatus == NC_STS_MEDIA_CHANGE);

    if (eStatus == NC_STS_READY)
    {
        printf("nand rdy\n");
        if (!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_4))
        {
            MSD_SetPortOpened(MSD_PORT_4, TRUE);
            MSD_RegisterDevice(deviceIndex, MSD_PORT_4, 0);
            MSD_DeviceStatusControlInserted(deviceIndex);
        }
    }
    else
    {
        if (msAPI_MSDCtrl_IsPortOpened(MSD_PORT_4))
        {
           MSD_SetPortOpened(MSD_PORT_4, FALSE);
           msAPI_MSDCtrl_ResetPort(MSD_PORT_4);
        }
        __ASSERT(0);
    }
}
#endif
#endif

void msAPI_MSDCtrl_Init(void)
{
    U8 i=0;
    StorageDevice sd;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    if(STORAGE_DEVICE_NUM*sizeof(StorageDevice)>STORAGE_DEVICE_MEMORY_LEN)
    {
        __ASSERT(0);
    }

    if(DISK_DRIVE_NUM*sizeof(MSDCtrl_Drive)>DRIVE_MEMORY_LEN)
    {
        __ASSERT(0);
    }

    for(i=0;i<MSD_PORT_NUM;i++)
    {
        MSD_SetPortOpened((EN_MSD_PORT)i,FALSE);
        MSD_SetPortChanged((EN_MSD_PORT)i,FALSE);
        MSD_SetPortConnected((EN_MSD_PORT)i,FALSE);
    }


    sd.DeviceIndex=INVALID_DEVICE_INDEX;
    sd.MSDStatus=MSD_STATUS_EMPTY;
    sd.MSDAddress.GID=0xFF;
    sd.MSDAddress.Port=INVALID_MSD_PORT;

    for(i=0;i<u8DeviceNum;i++)
    {
        msAPI_FS_MIU_Copy((U32)&sd, STORAGE_DEVICE_MEMORY_ADDR+(i)*sizeof(StorageDevice),sizeof(StorageDevice));
    }


    for(i=0;i<MSD_PORT_NUM;i++)
    {
        if(msAPI_MSDCtrl_IsPortEnabled((EN_MSD_PORT)i))
        {
            msAPI_MSDCtrl_ResetPort((EN_MSD_PORT)i);
        }
    }
}



//should be called when detecting new device
BOOLEAN msAPI_MSDCtrl_ConnectDevice(U8 u8DeviceIndex, StorageDevice dev)
{
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    if(u8DeviceIndex >= u8DeviceNum)
    {
        __ASSERT(0);
        return FALSE;
    }
    //MSD_DBG(printf("MSDCtrl ConnectDevice 1 DeviceIndex = %d, device type = %d\n",(U16)dev.DeviceIndex, (U16)dev.Type););
    if(msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIndex) == MSD_STATUS_EMPTY)
    {
        msAPI_MSDCtrl_SetDeviceStatus(u8DeviceIndex, MSD_STATUS_INSERTED);
        msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&dev), STORAGE_DEVICE_MEMORY_ADDR + sizeof(EN_MSD_STATUS) * STORAGE_DEVICE_NUM + u8DeviceIndex * sizeof(StorageDevice), sizeof(StorageDevice));
        MSD_DBG(printf("\nDevice %bu connected!!\n",u8DeviceIndex));
        return TRUE;
    }
    return FALSE;
}

void msAPI_MSDCtrl_CheckDevices(void)
{
    //DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

#if (ENABLE_USB)
    MSD_CheckMSDPort1Devices();
#endif
#if (ENABLE_USB_2)
    MSD_CheckMSDPort2Devices();
#endif

#if (defined(ENABLE_USB_3) && (ENABLE_USB_3 == 1)) || (defined(ENABLE_CF) && (ENABLE_CF == 1))
    MSD_CheckMSDPort3Devices();
#endif

#if (defined(ENABLE_USB_4) && (ENABLE_USB_4 == 1)) || ENABLE_NAND
    MSD_CheckMSDPort4Devices();
#endif

#if (ENABLE_CARDREADER)
    MSD_CheckMSDPort0Devices();
#endif

    //DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}

#if FILE_SYSTEM_ENABLE_MSD_CHECK_DEVICES_ON_PORTS
void msAPI_MSDCtrl_CheckDevicesOnPort(EN_MSD_PORT port)
{
    switch (port)
    {
      #if ENABLE_CARDREADER
        case MSD_PORT_0:
            MSD_CheckMSDPort0Devices();
            break;
      #endif
      #if ENABLE_USB
        case MSD_PORT_1:
            MSD_CheckMSDPort1Devices();
            break;
      #endif
      #if ENABLE_USB_2
        case MSD_PORT_2:
            MSD_CheckMSDPort2Devices();
            break;
      #endif
      #if (defined(ENABLE_USB_3) && (ENABLE_USB_3 == 1)) || (defined(ENABLE_CF) && (ENABLE_CF == 1))
        case MSD_PORT_3:
            MSD_CheckMSDPort3Devices();
            break;
      #endif
      #if (defined(ENABLE_USB_4) && (ENABLE_USB_4 == 1)) || ENABLE_NAND
        case MSD_PORT_4:
            MSD_CheckMSDPort4Devices();
            break;
      #endif
        default:
            break;
    };
}
#endif

#if FILE_SYSTEM_ENABLE_MSD_DEVICES_CHANGE_STATUS_CHECK
BOOLEAN msAPI_MSDCtrl_DevicesChangeStatusCheck(void)
{
    BOOLEAN bIsChanged = FALSE;
#if (ENABLE_USB)
    if(MDrv_UsbDeviceConnect() )
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_1) && !msAPI_MSDCtrl_CheckUSBCardReaderChanged(MSD_PORT_1))
        {
            MSD_SetPortChanged(MSD_PORT_1,FALSE);
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_1,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 1 change to Connected\n"));
        }
        MSD_SetPortConnected(MSD_PORT_1,TRUE);
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_1))
        {
            MSD_SetPortChanged(MSD_PORT_1,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 1 change to Disconnected\n"));
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_1,FALSE);
        }
        MSD_SetPortConnected(MSD_PORT_1,FALSE);

    }
#endif

#if (ENABLE_USB_2)
    if(MDrv_UsbDeviceConnect_Port2())
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_2) && !msAPI_MSDCtrl_CheckUSBCardReaderChanged(MSD_PORT_2))
        {
            MSD_SetPortChanged(MSD_PORT_2,FALSE);
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_2,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 2 change to Connected\n"));

        }
        MSD_SetPortConnected(MSD_PORT_2,TRUE);
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_2))
        {
            MSD_SetPortChanged(MSD_PORT_2,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 2 change to Disconnected\n"));
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_2,FALSE);
        }
        MSD_SetPortConnected(MSD_PORT_2,FALSE);

    }
#endif

#if (ENABLE_USB_3)
    if(MDrv_UsbDeviceConnect_Port3())
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_3) && !msAPI_MSDCtrl_CheckUSBCardReaderChanged(MSD_PORT_3))
        {
            MSD_SetPortChanged(MSD_PORT_3,FALSE);
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_3,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 3 change to Connected\n"));

        }
        MSD_SetPortConnected(MSD_PORT_3,TRUE);
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_3))
        {
            MSD_SetPortChanged(MSD_PORT_3,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 3 change to Disconnected\n"));
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_3,FALSE);
        }
        MSD_SetPortConnected(MSD_PORT_3,FALSE);

    }
#endif

#if (ENABLE_USB_4)
    if(MDrv_UsbDeviceConnect_Port4())
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_4) && !msAPI_MSDCtrl_CheckUSBCardReaderChanged(MSD_PORT_4))
        {
            MSD_SetPortChanged(MSD_PORT_4,FALSE);
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_4,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 4 change to Connected\n"));

        }
        MSD_SetPortConnected(MSD_PORT_4,TRUE);
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortConnected(MSD_PORT_4))
        {
            MSD_SetPortChanged(MSD_PORT_4,TRUE);
            bIsChanged = TRUE;
            MS_DEBUG_MSG(printf("USB Port 4 change to Disconnected\n"));
        }
        else
        {
            MSD_SetPortChanged(MSD_PORT_4,FALSE);
        }
        MSD_SetPortConnected(MSD_PORT_4,FALSE);

    }
#endif

    return bIsChanged;
}
#endif

void msAPI_MSDCtrl_SetDeviceStatus(U8 u8DeviceIndex, EN_MSD_STATUS status)
{
    StorageDevice* pDevice=NULL;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    //printf("msAPI_MSDCtrl_SetDeviceStatus(u8DeviceIndex=%u, status=%u)\n", u8DeviceIndex, status);

    if( u8DeviceIndex >= u8DeviceNum )
    {
        PRINT_CURRENT_LINE();
        printf("\nError: u8DeviceIndex=%u >= u8DeviceNum=%u\n", u8DeviceIndex, u8DeviceNum);

        __ASSERT(0);
    }

    pDevice=(StorageDevice xdata*)msAPI_FS_GetAddr(STORAGE_DEVICE_MEMORY_ADDR);
    //printf("STORAGE_DEVICE_MEMORY_ADDR=%X\n", STORAGE_DEVICE_MEMORY_ADDR);
    //printf("pDevice=%X\n", pDevice);

    pDevice[u8DeviceIndex].MSDStatus=status;
}

EN_MSD_STATUS msAPI_MSDCtrl_GetDeviceStatus(U8 u8DeviceIndex)
{
    EN_MSD_STATUS status = MSD_STATUS_ERROR;
    StorageDevice* pDevice=NULL;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    if(u8DeviceIndex >= u8DeviceNum)
    {
        __ASSERT(0);
    }

    pDevice=(StorageDevice xdata*)msAPI_FS_GetAddr(STORAGE_DEVICE_MEMORY_ADDR);

    status=pDevice[u8DeviceIndex].MSDStatus;

    MSD_DBG(
    {
        if(status != MSD_STATUS_EMPTY)
        {
            printf(" %bu status=%bu\n", u8DeviceIndex, (U8) status);
        }
    })

    return status;
}

U8 msAPI_MSDCtrl_Get_USBPort_ByDeviceIdx(U8 deviceIndex, U8* pu8DeviceIdxNew)
{
    U8 u8IndexStart;
    U8 u8IndexEnd;

    *pu8DeviceIdxNew = 0;

#if (ENABLE_USB)
    u8IndexStart = MSD_USB_INDEX_START;
    u8IndexEnd = MSD_USB_INDEX_END;
    //if( deviceIndex < u8IndexEnd )//please keep this line due to the MSD_USB_INDEX_START may not always be 0
    if( deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd )
    {
        *pu8DeviceIdxNew = deviceIndex - MSD_USB_INDEX_START;
        return USB_PORT_0;
    }
#endif

#if (ENABLE_USB_2)
    u8IndexStart = MSD_USB_2_INDEX_START;
    u8IndexEnd = MSD_USB_2_INDEX_END;
    if( deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd )
    {
        *pu8DeviceIdxNew = deviceIndex - MSD_USB_2_INDEX_START;
        return USB_PORT_2;
    }
#endif

#if (ENABLE_USB_3)
    u8IndexStart = MSD_USB_3_INDEX_START;
    u8IndexEnd = MSD_USB_3_INDEX_END;
    if( deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd )
    {
        *pu8DeviceIdxNew = deviceIndex - MSD_USB_3_INDEX_START;
        return USB_PORT_3;
    }
#endif

#if (ENABLE_USB_4)
    u8IndexStart = MSD_USB_4_INDEX_START;
    u8IndexEnd = MSD_USB_4_INDEX_END;
    if( deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd )
    {
        *pu8DeviceIdxNew = deviceIndex - MSD_USB_4_INDEX_START;
        return USB_PORT_4;
    }
#endif

    return 0xFF;
}

U32 msAPI_MSDCtrl_Get_USBBlockSize_ByPort(U8 u8UsbPort, U8 u8UsbDeviceIdx)
{
    U32 u32BlockSize = 0;

    switch(u8UsbPort)
    {
    #if(ENABLE_USB)
        case USB_PORT_0:
            u32BlockSize = MDrv_GetUsbBlockSize(u8UsbDeviceIdx);
            break;
    #endif

    #if(ENABLE_USB_2)
        case USB_PORT_2:
            u32BlockSize = MDrv_GetUsbBlockSize_Port2(u8UsbDeviceIdx);
            break;
    #endif

    #if(ENABLE_USB_3)
        case USB_PORT_3:
            u32BlockSize = MDrv_GetUsbBlockSize_Port3(u8UsbDeviceIdx);
            break;
    #endif

    #if(ENABLE_USB_4)
        case USB_PORT_4:
            u32BlockSize = MDrv_GetUsbBlockSize_Port4(u8UsbDeviceIdx);
            break;
    #endif

        default:
            break;
    }

    return u32BlockSize;
}

U32 msAPI_MSDCtrl_Get_USBBlockNum_ByPort(U8 u8UsbPort, U8 u8UsbDeviceIdx)
{
    U32 u32BlockNum = 0;

    switch(u8UsbPort)
    {
    #if(ENABLE_USB)
        case USB_PORT_0:
            u32BlockNum = MDrv_GetUsbBlockNum(u8UsbDeviceIdx);
            break;
    #endif

    #if(ENABLE_USB_2)
        case USB_PORT_2:
            u32BlockNum = MDrv_GetUsbBlockNum_Port2(u8UsbDeviceIdx);
            break;
    #endif

    #if(ENABLE_USB_3)
        case USB_PORT_3:
            u32BlockNum = MDrv_GetUsbBlockNum_Port3(u8UsbDeviceIdx);
            break;
    #endif

    #if(ENABLE_USB_4)
        case USB_PORT_4:
            u32BlockNum = MDrv_GetUsbBlockNum_Port4(u8UsbDeviceIdx);
            break;
    #endif

        default:
            break;
    }

    return u32BlockNum;
}

BOOLEAN _msAPI_MSDCtrl_UsbBlockWriteFromMIU_ByPort(U8 u8UsbPort, U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer)
{
    BOOLEAN bRtn = FALSE;

    switch(u8UsbPort)
    {
    #if(ENABLE_USB)
        case USB_PORT_0:
            bRtn = MDrv_UsbBlockWriteFromMIU( lun, u32BlockAddr, u32BlockNum, u32Buffer);
            break;
    #endif

    #if(ENABLE_USB_2)
        case USB_PORT_2:
            bRtn = MDrv_UsbBlockWriteFromMIU_Port2( lun, u32BlockAddr, u32BlockNum, u32Buffer);
            break;
    #endif

    #if(ENABLE_USB_3)
        case USB_PORT_3:
            bRtn = MDrv_UsbBlockWriteFromMIU_Port3( lun, u32BlockAddr, u32BlockNum, u32Buffer);
            break;
    #endif

    #if(ENABLE_USB_4)
        case USB_PORT_4:
            bRtn = MDrv_UsbBlockWriteFromMIU_Port4( lun, u32BlockAddr, u32BlockNum, u32Buffer);
            break;
    #endif

        default:
            return FALSE;
            break;
    }

    return bRtn;
}

#if FILE_SYSTEM_LIMIT_IO_SECTORS
#define MAX_IO_SECTORS 128
#else
#define MAX_IO_SECTORS 1024
#endif

BOOLEAN msAPI_MSDCtrl_SectorRead(U8 deviceIndex, U32 u32StartSector, U32 u32SectorCount, U32 u32BufferAddress)
{
#if ((ENABLE_USB) || (ENABLE_USB_2) || (ENABLE_USB_3) || (ENABLE_USB_4) || (ENABLE_CARDREADER) || (defined(ENABLE_CF)&&(ENABLE_CF == 1)) )
    U32 u32Count;
    U32 u32MaxSector, u32SectorsPerDevice;
    U32 u32BytePerSector;
    U8 u8IndexStart, u8IndexEnd;
#endif

    if(u32SectorCount==0)
    {
        return TRUE;
    }

#if (ENABLE_USB)
    u8IndexStart = 0;
    u8IndexEnd = MSD_USB_INDEX_END;
    if( deviceIndex < u8IndexEnd )
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_INDEX_START;
        u32BytePerSector = MDrv_GetUsbBlockSize(u8DeviceIndex);
        if(!u32BytePerSector)
        {	//Alan.yu 2010 06 22 redo usb device enum(fix issue:plugin card reader,then plugin SD Card)
        	if(MDrv_Usb_Device_Enum())
        		u32BytePerSector = MDrv_GetUsbBlockSize(u8DeviceIndex);
		    else
		    {
			    __ASSERT(0);
			    return FALSE;
		    }
        }

        if( u32BytePerSector == 0 )
        {
            printf("\nError: u32BytePerSector=%u\n", u32BytePerSector);
            __ASSERT(0);
            return FALSE;
        }
        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;
        u32SectorsPerDevice = MDrv_GetUsbBlockNum(u8DeviceIndex);

        if( (u32SectorsPerDevice - u32StartSector + 1) < u32SectorCount )  //(Total sectors < sector) error!
        //if( (u32SectorsPerDevice - u32SectorCount) < u32StartSector )
        {
            MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx,u32ReadSectors=0x%08lx, u32SectorsPerDevice=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)u32SectorCount, (U32)u32SectorCount, (U32)u32SectorsPerDevice););
            __ASSERT(0);
            return FALSE;
        }
        if((u32BufferAddress)&0x03) //non-aligned read
        {
MDrv_Sys_DisableWatchDog();
            for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {
                if ( !MDrv_UsbBlockReadToMIU( u8DeviceIndex,u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))
                {
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }
                msAPI_FS_MIU_Copy (DEVICE_IO_BUFFER_ADDR, u32BufferAddress +u32Count*u32BytePerSector, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));
            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
        else
        {

            U32 _sectors;
MDrv_Sys_DisableWatchDog();
            while(u32SectorCount>0)
            {
                _sectors=(u32SectorCount>MAX_IO_SECTORS)?MAX_IO_SECTORS:u32SectorCount;
                if(!MDrv_UsbBlockReadToMIU(u8DeviceIndex,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                {
                    MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx, _sectors=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)_sectors););
                    __ASSERT(0);
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }

                u32SectorCount-=_sectors;
                u32StartSector+=_sectors;
                u32BufferAddress+=(_sectors*u32BytePerSector);

                FS_RESET_WDT();

            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
    }
#endif

#if (ENABLE_USB_2)
    u8IndexStart = MSD_USB_2_INDEX_START;
    u8IndexEnd = MSD_USB_2_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd)
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_2_INDEX_START;
        u32BytePerSector = MDrv_GetUsbBlockSize_Port2(u8DeviceIndex);
        if( u32BytePerSector == 0 )
        {
            printf("\nError: u32BytePerSector=%u\n", u32BytePerSector);
            __ASSERT(0);
            return FALSE;
        }
        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;
        u32SectorsPerDevice = MDrv_GetUsbBlockNum_Port2(u8DeviceIndex);

        if( (u32SectorsPerDevice - u32StartSector + 1) < u32SectorCount )  //(Total sectors < sector) error!
        //if( (u32SectorsPerDevice - u32SectorCount) < u32StartSector )
        {
            MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx,u32ReadSectors=0x%08lx, u32SectorsPerDevice=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)u32SectorCount, (U32)u32SectorCount, (U32)u32SectorsPerDevice););
            __ASSERT(0);
            return FALSE;
        }

        if((u32BufferAddress)&0x03) //non-aligned read
        {
 MDrv_Sys_DisableWatchDog();
           for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {

                if ( !MDrv_UsbBlockReadToMIU_Port2( u8DeviceIndex,u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))
                {
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }
                msAPI_FS_MIU_Copy (DEVICE_IO_BUFFER_ADDR, u32BufferAddress +u32Count*u32BytePerSector, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));
            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
        else
        {

            U32 _sectors;
 MDrv_Sys_DisableWatchDog();
           while(u32SectorCount>0)
            {
                _sectors=(u32SectorCount>MAX_IO_SECTORS)?MAX_IO_SECTORS:u32SectorCount;

                if(!MDrv_UsbBlockReadToMIU_Port2(u8DeviceIndex,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                {
                    __ASSERT(0);
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }

                u32SectorCount-=_sectors;
                u32StartSector+=_sectors;
                u32BufferAddress+=(_sectors*u32BytePerSector);

                FS_RESET_WDT();

            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
    }
#endif

#if (ENABLE_USB_3)
    u8IndexStart = MSD_USB_3_INDEX_START;
    u8IndexEnd = MSD_USB_3_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd)
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_3_INDEX_START;
        u32BytePerSector = MDrv_GetUsbBlockSize_Port3(u8DeviceIndex);
        if( u32BytePerSector == 0 )
        {
            printf("\nError: u32BytePerSector=%u\n", u32BytePerSector);
            __ASSERT(0);
            return FALSE;
        }
        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;
        u32SectorsPerDevice = MDrv_GetUsbBlockNum_Port3(u8DeviceIndex);

        if( (u32SectorsPerDevice - u32StartSector + 1) < u32SectorCount )  //(Total sectors < sector) error!
        //if( (u32SectorsPerDevice - u32SectorCount) < u32StartSector )
        {
            MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx,u32ReadSectors=0x%08lx, u32SectorsPerDevice=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)u32SectorCount, (U32)u32SectorCount, (U32)u32SectorsPerDevice););
            __ASSERT(0);
            return FALSE;
        }

        if((u32BufferAddress)&0x03) //non-aligned read
        {
 MDrv_Sys_DisableWatchDog();
           for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {

                if ( !MDrv_UsbBlockReadToMIU_Port3( u8DeviceIndex,u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))
                {
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }
                msAPI_FS_MIU_Copy (DEVICE_IO_BUFFER_ADDR, u32BufferAddress +u32Count*u32BytePerSector, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));
            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
        else
        {

            U32 _sectors;
 MDrv_Sys_DisableWatchDog();
           while(u32SectorCount>0)
            {
                _sectors=(u32SectorCount>MAX_IO_SECTORS)?MAX_IO_SECTORS:u32SectorCount;

                if(!MDrv_UsbBlockReadToMIU_Port3(u8DeviceIndex,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                {
                    __ASSERT(0);
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }

                u32SectorCount-=_sectors;
                u32StartSector+=_sectors;
                u32BufferAddress+=(_sectors*u32BytePerSector);

                FS_RESET_WDT();

            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
    }
#endif


#if (ENABLE_USB_4)
    u8IndexStart = MSD_USB_4_INDEX_START;
    u8IndexEnd = MSD_USB_4_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd)
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_4_INDEX_START;
        u32BytePerSector = MDrv_GetUsbBlockSize_Port4(u8DeviceIndex);
        if( u32BytePerSector == 0 )
        {
            printf("\nError: u32BytePerSector=%u\n", u32BytePerSector);
            __ASSERT(0);
            return FALSE;
        }
        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;
        u32SectorsPerDevice = MDrv_GetUsbBlockNum_Port4(u8DeviceIndex);

        if( (u32SectorsPerDevice - u32StartSector + 1) < u32SectorCount )  //(Total sectors < sector) error!
        //if( (u32SectorsPerDevice - u32SectorCount) < u32StartSector )
        {
            MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx,u32ReadSectors=0x%08lx, u32SectorsPerDevice=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)u32SectorCount, (U32)u32SectorCount, (U32)u32SectorsPerDevice););
            __ASSERT(0);
            return FALSE;
        }

        if((u32BufferAddress)&0x03) //non-aligned read
        {
 MDrv_Sys_DisableWatchDog();
           for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {

                if ( !MDrv_UsbBlockReadToMIU_Port4( u8DeviceIndex,u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))
                {
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }
                msAPI_FS_MIU_Copy (DEVICE_IO_BUFFER_ADDR, u32BufferAddress +u32Count*u32BytePerSector, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));
            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
        else
        {

            U32 _sectors;
 MDrv_Sys_DisableWatchDog();
           while(u32SectorCount>0)
            {
                _sectors=(u32SectorCount>MAX_IO_SECTORS)?MAX_IO_SECTORS:u32SectorCount;

                if(!MDrv_UsbBlockReadToMIU_Port4(u8DeviceIndex,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                {
                    __ASSERT(0);
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }

                u32SectorCount-=_sectors;
                u32StartSector+=_sectors;
                u32BufferAddress+=(_sectors*u32BytePerSector);

                FS_RESET_WDT();

            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
    }
#endif

#if (ENABLE_CARDREADER) || (defined(ENABLE_CF) && (ENABLE_CF == 1))
// if 4in1 card reader or CF card reader is enabled.
    u8IndexStart = MSD_CREADER_INDEX_START;
    u8IndexEnd = MSD_CREADER_INDEX_END;

    #if (ENABLE_CARDREADER) && (defined(ENABLE_CF) && (ENABLE_CF == 1))
    // both 4in1 and CF card readers are enabled
        if ((deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd)
            || (deviceIndex >= MSD_CF_INDEX_START && deviceIndex < MSD_CF_INDEX_END))
    #elif (ENABLE_CARDREADER)
    // only 4in1 card reader enabled
        if ((deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd))
    #else
    // only CF card reader enabled
        if ((deviceIndex >= MSD_CF_INDEX_START && deviceIndex < MSD_CF_INDEX_END))
    #endif
    {

        U8 u8DeviceIndex;

        #if (ENABLE_CARDREADER) && (defined(ENABLE_CF) && (ENABLE_CF == 1))
        // both 4in1 and CF card readers are enabled
            if (deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd)
            {
                // read 4in1 card reader
                #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
                gu8CurrentSlot = SLOT_4IN1;
                #endif
                u8DeviceIndex = deviceIndex - MSD_CREADER_INDEX_START;
            }
            else
            {
                // read CF
                #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
                gu8CurrentSlot = SLOT_CF;
                #endif
                u8DeviceIndex = deviceIndex - MSD_CF_INDEX_START;
            }
        #elif (ENABLE_CARDREADER)
        // only 4in1 card reader enabled
            #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
            gu8CurrentSlot = SLOT_4IN1;
            #endif
            u8DeviceIndex = deviceIndex - MSD_CREADER_INDEX_START;
        #else
        // only CF card reader enabled
            #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
            gu8CurrentSlot = SLOT_CF;
            #endif
            u8DeviceIndex = deviceIndex - MSD_CF_INDEX_START;
        #endif

        u32BytePerSector = FAT_SECTOR_SIZE_512BYTE;
        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;

        if((u32BufferAddress)&0x07) //non-aligned read
        {
            for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {
                #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
                    if (STS_SUCCESS != FS_CardReaderRead(u32StartSector+u32Count,
                        u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, (U32)_VA2PA((void *)DEVICE_IO_BUFFER_ADDR)))
                    {
                        return FALSE;
                    }
                #else
                if ( !FS_CardReaderRead(u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, (U32)_VA2PA((void *)DEVICE_IO_BUFFER_ADDR)))
                {
                    return FALSE;
                }
                #endif
                msAPI_FS_MIU_Copy (DEVICE_IO_BUFFER_ADDR, u32BufferAddress +u32Count*u32BytePerSector, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));
            }
            return TRUE;
        }
        else
        {
            #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
                return (STS_SUCCESS == FS_CardReaderRead( u32StartSector, u32SectorCount, (U32)_VA2PA((void *)u32BufferAddress)));
            #else
            return(FS_CardReaderRead( u32StartSector, u32SectorCount, (U32)_VA2PA((void *)u32BufferAddress)));
            #endif
        }
    }

#endif // if 4in1 card reader or CF card reader is enabled.

#if (ENABLE_NAND)
    if (deviceIndex >= MSD_NAND_INDEX_START
        && deviceIndex < MSD_NAND_INDEX_END )
    {
        return (STS_SUCCESS == nand_disk_read(NULL, (U32)_VA2PA((void *)u32BufferAddress), u32SectorCount, u32StartSector));
    }
#endif

#if ((!ENABLE_USB)&&(!ENABLE_CARDREADER)&&(!ENABLE_USB_2) && !(defined(CERAMAL_N51FS) && ENABLE_CF) && !ENABLE_NAND)
//eliminate compiling warring
    UNUSED(deviceIndex);
    UNUSED(u32SectorCount);
    UNUSED(u32BufferAddress);
    UNUSED(u32StartSector);
#endif
    return FALSE;

}

BOOLEAN msAPI_MSDCtrl_SectorWrite(U8 deviceIndex, U32 u32StartSector, U32 u32SectorCount, U32 u32BufferAddress)
{
#if ((ENABLE_USB) || (ENABLE_USB_2) || (ENABLE_CARDREADER) || (defined(ENABLE_CF)&&(ENABLE_CF == 1)) )
    U32 u32Count;
    U32 u32MaxSector, u32SectorsPerDevice;
    U32 u32BytePerSector;
    U8 u8IndexStart,u8IndexEnd;
#endif

#if( (ENABLE_USB_3) || (ENABLE_USB_4) )
    U32 u32Count;
    U32 u32MaxSector, u32SectorsPerDevice;
    U32 u32BytePerSector;
#endif


    //printf("write to sector=0x%08lx with count=0x%08lx from 0x%08lx\n",u32StartSector,u32SectorCount,u32BufferAddress);
    if(u32SectorCount==0)
    {
        return TRUE;
    }


#if (ENABLE_USB)
    u8IndexStart = 0;
    u8IndexEnd = MSD_USB_INDEX_END;
    if( deviceIndex < u8IndexEnd )//please keep this line due to the MSD_USB_INDEX_START may not always be 0
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_INDEX_START;
        u32BytePerSector = MDrv_GetUsbBlockSize(u8DeviceIndex);
        // Check u32BytePerSector == 0 ...
        if( u32BytePerSector == 0 ) // Remove USB may cause thie happed!
        {
            printf("\nError: u32BytePerSector=%u\n", u32BytePerSector);
            __ASSERT(0);
            return FALSE;
        }
        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;
        u32SectorsPerDevice = MDrv_GetUsbBlockNum(u8DeviceIndex);

        if( (u32SectorsPerDevice - u32StartSector + 1) < u32SectorCount )  //(Total sectors < sector) error!
        //if( (u32SectorsPerDevice - u32SectorCount) < u32StartSector )
        {
            MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx,u32ReadSectors=0x%08lx, u32SectorsPerDevice=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)u32SectorCount, (U32)u32SectorCount, (U32)u32SectorsPerDevice););
            __ASSERT(0);
            return FALSE;
        }

        if((u32BufferAddress)&0x03) //non-aligned write
        {
MDrv_Sys_DisableWatchDog();
            for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {
                msAPI_FS_MIU_Copy (u32BufferAddress +u32Count*u32BytePerSector, DEVICE_IO_BUFFER_ADDR, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));

                if ( !MDrv_UsbBlockWriteFromMIU( u8DeviceIndex,u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))
                {
 MDrv_Sys_EnableWatchDog();
                   return FALSE;
                }
           }
  MDrv_Sys_EnableWatchDog();
           return TRUE;
        }
        else
        {

            U32 _sectors;
MDrv_Sys_DisableWatchDog();
            while(u32SectorCount>0)
            {
                _sectors=(u32SectorCount>MAX_IO_SECTORS)?MAX_IO_SECTORS:u32SectorCount;

                if(!MDrv_UsbBlockWriteFromMIU(u8DeviceIndex,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                {
                    __ASSERT(0);
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }

                u32SectorCount-=_sectors;
                u32StartSector+=_sectors;
                u32BufferAddress+=(_sectors*u32BytePerSector);

                FS_RESET_WDT();

            }
MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
    }
#endif

#if (ENABLE_USB_2)
    u8IndexStart = MSD_USB_2_INDEX_START;
    u8IndexEnd = MSD_USB_2_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd )
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_2_INDEX_START;
        u32BytePerSector = MDrv_GetUsbBlockSize_Port2(u8DeviceIndex);
        // Check u32BytePerSector == 0 ...
        if( u32BytePerSector == 0 ) // Remove USB may cause thie happed!
        {
            printf("\nError: u32BytePerSector=%u\n", u32BytePerSector);
            __ASSERT(0);
            return FALSE;
        }

        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;
        u32SectorsPerDevice = MDrv_GetUsbBlockNum_Port2(u8DeviceIndex);

        if( (u32SectorsPerDevice - u32StartSector + 1) < u32SectorCount )  //(Total sectors < sector) error!
        //if( (u32SectorsPerDevice - u32SectorCount) < u32StartSector )
        {
            MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx,u32ReadSectors=0x%08lx, u32SectorsPerDevice=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)u32SectorCount, (U32)u32SectorCount, (U32)u32SectorsPerDevice););
            __ASSERT(0);
            return FALSE;
        }

        if((u32BufferAddress)&0x03) //non-aligned write
        {
 MDrv_Sys_DisableWatchDog();
           for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {
                msAPI_FS_MIU_Copy (u32BufferAddress +u32Count*u32BytePerSector, DEVICE_IO_BUFFER_ADDR, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));

                if ( !MDrv_UsbBlockWriteFromMIU_Port2( u8DeviceIndex,u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))
                {
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }
            }
 MDrv_Sys_EnableWatchDog();
           return TRUE;
        }
        else
        {

            U32 _sectors;
MDrv_Sys_DisableWatchDog();
            while(u32SectorCount>0)
            {
                _sectors=(u32SectorCount>MAX_IO_SECTORS)?MAX_IO_SECTORS:u32SectorCount;

                if(!MDrv_UsbBlockWriteFromMIU_Port2(u8DeviceIndex,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                {
                    __ASSERT(0);
MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }

                u32SectorCount-=_sectors;
                u32StartSector+=_sectors;
                u32BufferAddress+=(_sectors*u32BytePerSector);

                FS_RESET_WDT();

           }
  MDrv_Sys_EnableWatchDog();
           return TRUE;
        }
    }
#endif


#if (ENABLE_USB_3 || ENABLE_USB_4)
    U8 u8UsbDeviceIdx = 0;
    U8 u8UsbPort = msAPI_MSDCtrl_Get_USBPort_ByDeviceIdx( deviceIndex, &u8UsbDeviceIdx);

    //u8IndexStart = MSD_USB_3_INDEX_START;
    //u8IndexEnd = MSD_USB_3_INDEX_END;
    //if(deviceIndex >= u8IndexStart
    //   && deviceIndex < u8IndexEnd )
    if( USB_PORT_3 <= u8UsbPort && u8UsbPort <= USB_PORT_4 )
    {
        //U8 u8DeviceIndex=deviceIndex-MSD_USB_3_INDEX_START;
        //u32BytePerSector = MDrv_GetUsbBlockSize_Port3(u8DeviceIndex);
        u32BytePerSector = msAPI_MSDCtrl_Get_USBBlockSize_ByPort(u8UsbPort, u8UsbDeviceIdx);

        // Check u32BytePerSector == 0 ...
        if( u32BytePerSector == 0 ) // Remove USB may cause thie happed!
        {
            printf("\nError: u32BytePerSector=%u\n", u32BytePerSector);
            __ASSERT(0);
            return FALSE;
        }

        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;
        //u32SectorsPerDevice = MDrv_GetUsbBlockNum_Port3(u8DeviceIndex);
        u32SectorsPerDevice = msAPI_MSDCtrl_Get_USBBlockNum_ByPort(u8UsbPort, u8UsbDeviceIdx);

        if( (u32SectorsPerDevice - u32StartSector + 1) < u32SectorCount )  //(Total sectors < sector) error!
        //if( (u32SectorsPerDevice - u32SectorCount) < u32StartSector )
        {
            MSD_DBG(printf("u8DeviceIndex=%u, u32StartSector=0x%08lx,u32ReadSectors=0x%08lx, u32SectorsPerDevice=0x%08lx\n", u8DeviceIndex, (U32)u32StartSector,(U32)u32SectorCount, (U32)u32SectorCount, (U32)u32SectorsPerDevice););
            __ASSERT(0);
            return FALSE;
        }

        if((u32BufferAddress)&0x03) //non-aligned write
        {
            MDrv_Sys_DisableWatchDog();

            for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {
                msAPI_FS_MIU_Copy (u32BufferAddress +u32Count*u32BytePerSector, DEVICE_IO_BUFFER_ADDR, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));

                MDrv_Sys_EnableWatchDog();

                //if ( !MDrv_UsbBlockWriteFromMIU_Port3( u8DeviceIndex,u32StartSector+u32Count,
                //    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))

                if ( !_msAPI_MSDCtrl_UsbBlockWriteFromMIU_ByPort( u8UsbPort, u8UsbDeviceIdx, u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, _VA2PA(DEVICE_IO_BUFFER_ADDR)))
                {
                    MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }
            }

            MDrv_Sys_EnableWatchDog();
            return TRUE;
        }
        else
        {
            U32 _sectors;

            while(u32SectorCount>0)
            {
                MDrv_Sys_EnableWatchDog();

                _sectors=(u32SectorCount>MAX_IO_SECTORS)?MAX_IO_SECTORS:u32SectorCount;

                //if(!MDrv_UsbBlockWriteFromMIU_Port3(u8DeviceIndex,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                if(!_msAPI_MSDCtrl_UsbBlockWriteFromMIU_ByPort(u8UsbPort, u8UsbDeviceIdx,u32StartSector, _sectors, _VA2PA(u32BufferAddress)))
                {
                    __ASSERT(0);
                    MDrv_Sys_EnableWatchDog();
                    return FALSE;
                }

                u32SectorCount-=_sectors;
                u32StartSector+=_sectors;
                u32BufferAddress+=(_sectors*u32BytePerSector);

                FS_RESET_WDT();

            }

            MDrv_Sys_EnableWatchDog();

            return TRUE;
        }
    }
#endif



#if (ENABLE_CARDREADER) || (defined(ENABLE_CF) && (ENABLE_CF == 1))
// if 4in1 card reader or CF card reader is enabled.
    u8IndexStart = MSD_CREADER_INDEX_START;
    u8IndexEnd = MSD_CREADER_INDEX_END;

    #if (ENABLE_CARDREADER) && (defined(ENABLE_CF) && (ENABLE_CF == 1))
    // both 4in1 and CF card readers are enabled
        if ((deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd)
            || (deviceIndex >= MSD_CF_INDEX_START && deviceIndex < MSD_CF_INDEX_END))
    #elif (ENABLE_CARDREADER)
    // only 4in1 card reader enabled
        if ((deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd))
    #else
    // only CF card reader enabled
        if ((deviceIndex >= MSD_CF_INDEX_START && deviceIndex < MSD_CF_INDEX_END))
    #endif
    {
        U8 u8DeviceIndex;

        #if (ENABLE_CARDREADER) && (defined(ENABLE_CF) && (ENABLE_CF == 1))
        // both 4in1 and CF card readers are enabled
            if (deviceIndex >= u8IndexStart && deviceIndex < u8IndexEnd)
            {
                // write 4in1 card reader
                #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
                gu8CurrentSlot = SLOT_4IN1;
                #endif
                u8DeviceIndex = deviceIndex - MSD_CREADER_INDEX_START;
            }
            else
    {
                // write CF
                gu8CurrentSlot = SLOT_CF;
                u8DeviceIndex = deviceIndex - MSD_CF_INDEX_START;
            }
        #elif (ENABLE_CARDREADER)
        // only 4in1 card reader enabled
            #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
            gu8CurrentSlot = SLOT_4IN1;
            #endif
            u8DeviceIndex = deviceIndex - MSD_CREADER_INDEX_START;
        #else
        // only CF card reader enabled
            #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
            gu8CurrentSlot = SLOT_CF;
            #endif
            u8DeviceIndex = deviceIndex - MSD_CF_INDEX_START;
        #endif

        u32BytePerSector = FAT_SECTOR_SIZE_512BYTE;
        u32MaxSector = DEVICE_IO_BUFFER_LEN/u32BytePerSector;

        if((u32BufferAddress)&0x07) //non-aligned write
        {
            for(u32Count=0;u32Count<u32SectorCount;u32Count+=u32MaxSector)
            {
                msAPI_FS_MIU_Copy (u32BufferAddress +u32Count*u32BytePerSector, DEVICE_IO_BUFFER_ADDR, (U32)u32BytePerSector*(u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count));

                #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
                    if ( STS_SUCCESS != FS_CardReaderWrite(u32StartSector+u32Count,
                        u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, (U32)_VA2PA((void *)DEVICE_IO_BUFFER_ADDR)))
                    {
                        return FALSE;
                    }
                #else
                if ( !FS_CardReaderWrite(u32StartSector+u32Count,
                    u32SectorCount - u32Count>u32MaxSector?u32MaxSector:u32SectorCount - u32Count, (U32)_VA2PA((void *)DEVICE_IO_BUFFER_ADDR)))
                {
                    return FALSE;
                }
                #endif
            }
            return TRUE;
        }
        else
        {
            #if defined(CERAMAL_N51FS) && (CERAMAL_N51FS == 1)
                return (STS_SUCCESS == FS_CardReaderWrite(u32StartSector, u32SectorCount, (U32)_VA2PA((void *)u32BufferAddress)));
            #else
            return (FS_CardReaderWrite(u32StartSector, u32SectorCount, (U32)_VA2PA((void *)u32BufferAddress)));
            #endif
        }
    }
#endif  // if 4in1 card reader or CF card reader is enabled.

#if (ENABLE_NAND)
    if (deviceIndex >= MSD_NAND_INDEX_START
        && deviceIndex < MSD_NAND_INDEX_END )
    {
        // U8 u8DeviceIndex = deviceIndex - MSD_NAND_INDEX_START;
        return (STS_SUCCESS == nand_disk_write(NULL, (U32)_VA2PA((void *)u32BufferAddress), u32SectorCount, u32StartSector));
    }
#endif

#if ((!ENABLE_USB)&&(!ENABLE_CARDREADER)&&(!ENABLE_USB_2) && !(defined(CERAMAL_N51FS) && ENABLE_CF) && !ENABLE_NAND)
//eliminate compiling warring
    UNUSED(deviceIndex);
    UNUSED(u32SectorCount);
    UNUSED(u32BufferAddress);
    UNUSED(u32StartSector);
#endif
    return FALSE;
}


#if 0
BOOLEAN msAPI_MSDCtrl_SectorErase(U8 deviceIndex, U32 u32StartSector, U32 u32SectorCount)
{
    __ASSERT(0);


    UNUSED(deviceIndex);
    UNUSED(u32StartSector);
    UNUSED(u32SectorCount);

    return FALSE;

}
#endif


BOOLEAN msAPI_MSDCtrl_HasNewDevice(void)
{
    U8 i;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i = 0; i < u8DeviceNum ; i++)
    {
        if(msAPI_MSDCtrl_GetDeviceStatus(i) == MSD_STATUS_INSERTED)
            return TRUE;
    }
    return FALSE;
}


#if FILE_SYSTEM_ENABLE_MSD_GET_BLOCK_SIZE
U32 msAPI_MSDCtrl_GetBlockSize(U8 deviceIndex)
{
    #if ((ENABLE_USB) || (ENABLE_USB_2) || (ENABLE_CARDREADER) || (defined(ENABLE_CF)&&(ENABLE_CF == 1)) )
    U8 u8IndexStart,u8IndexEnd;
    #endif
    #if (ENABLE_USB)
    u8IndexStart = 0;
    u8IndexEnd = MSD_USB_INDEX_END;
    if( deviceIndex < u8IndexEnd )
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_INDEX_START;
        return MDrv_GetUsbBlockSize(u8DeviceIndex);
    }
    #endif

    #if (ENABLE_USB_2)
    u8IndexStart = MSD_USB_2_INDEX_START;
    u8IndexEnd = MSD_USB_2_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd)
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_2_INDEX_START;
        return MDrv_GetUsbBlockSize_Port2(u8DeviceIndex);
    }
    #endif

    #if (ENABLE_CARDREADER)
    u8IndexStart = MSD_CREADER_INDEX_START;
    u8IndexEnd = MSD_CREADER_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd)
    {
        //U8 u8DeviceIndex=deviceIndex-MSD_CREADER_INDEX_START;
        return 512;
    }
    #endif

    #if defined(ENABLE_CF) && (ENABLE_CF == 1)
    if (deviceIndex >= MSD_CF_INDEX_START
        && deviceIndex < MSD_CF_INDEX_END)
    {
        //U8 u8DeviceIndex=deviceIndex-MSD_CF_INDEX_START;
        return 512;
    }
    #endif

    #if ENABLE_NAND
    if (deviceIndex >= MSD_NAND_INDEX_START
        && deviceIndex < MSD_NAND_INDEX_END)
    {
        //U8 u8DeviceIndex = deviceIndex - MSD_NAND_INDEX_START;
        return 512;
    }
    #endif

    UNUSED(deviceIndex);
    return 0;
}
#endif

U32 msAPI_MSDCtrl_GetBlockNum(U8 deviceIndex)
{
    #if ((ENABLE_USB) || (ENABLE_USB_2) || (ENABLE_CARDREADER) || (defined(ENABLE_CF)&&(ENABLE_CF == 1)) )
    U8 u8IndexStart,u8IndexEnd;
    #endif

    #if (ENABLE_USB)
    u8IndexStart = 0;
    u8IndexEnd = MSD_USB_INDEX_END;
    if( deviceIndex < u8IndexEnd )
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_INDEX_START;
        return MDrv_GetUsbBlockNum(u8DeviceIndex);
    }
    #endif

    #if (ENABLE_USB_2)
    u8IndexStart = MSD_USB_2_INDEX_START;
    u8IndexEnd = MSD_USB_2_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd)
    {
        U8 u8DeviceIndex=deviceIndex-MSD_USB_2_INDEX_START;
        return MDrv_GetUsbBlockNum_Port2(u8DeviceIndex);
    }
    #endif

    #if (ENABLE_CARDREADER)
    u8IndexStart = MSD_CREADER_INDEX_START;
    u8IndexEnd = MSD_CREADER_INDEX_END;
    if(deviceIndex >= u8IndexStart
       && deviceIndex < u8IndexEnd)
    {
        //U8 u8DeviceIndex=deviceIndex-MSD_CREADER_INDEX_START;
        __ASSERT(0);
        return 0;
    }
    #endif

    #if defined(ENABLE_CF) && (ENABLE_CF == 1)
    if (deviceIndex >= MSD_CF_INDEX_START
        && deviceIndex < MSD_CF_INDEX_END)
    {
        //U8 u8DeviceIndex = deviceIndex - MSD_CF_INDEX_START;
        __ASSERT(0);
        return 0;
    }
    #endif

    #if ENABLE_NAND
    if (deviceIndex >= MSD_NAND_INDEX_START
        && deviceIndex < MSD_NAND_INDEX_END)
    {
        //U8 u8DeviceIndex = deviceIndex - MSD_NAND_INDEX_START;
        __ASSERT(0);
        return 0;
    }
    #endif

    UNUSED(deviceIndex);
    return 0;
}



#if (!FILE_SYSTEM_SMALL)
BOOLEAN msAPI_MSDCtrl_HasUnpluggedDevice(void)
{
    U8 i;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i = 0; i < u8DeviceNum ; i++)
    {
        if(MSD_STATUS_UNPLUGGED==msAPI_MSDCtrl_GetDeviceStatus(i))
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOLEAN msAPI_MSDCtrl_HasEjectedDevice(void)
{
    U8 i;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i = 0; i < u8DeviceNum ; i++)
    {
        if(MSD_STATUS_EJECTED==msAPI_MSDCtrl_GetDeviceStatus(i))
            return TRUE;
    }
    return FALSE;
}


BOOLEAN msAPI_MSDCtrl_HasIdleDevice(void)
{
    U8 i;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i = 0; i < u8DeviceNum ; i++)
    {
        if(MSD_STATUS_IDLE==msAPI_MSDCtrl_GetDeviceStatus(i))
            return TRUE;
    }
    return FALSE;
}


BOOLEAN msAPI_MSDCtrl_HasEmptyDevice(void)
{
    U8 i;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i = 0; i < u8DeviceNum ; i++)
    {
        if(MSD_STATUS_EMPTY == msAPI_MSDCtrl_GetDeviceStatus(i))
            return TRUE;
    }
    return FALSE;
}

BOOLEAN msAPI_MSDCtrl_HasConnectedDevice(void)
{
    U8 i;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    for(i = 0; i < u8DeviceNum ; i++)
    {
        if(
              MSD_STATUS_IDLE == msAPI_MSDCtrl_GetDeviceStatus(i)
            ||MSD_STATUS_INSERTED == msAPI_MSDCtrl_GetDeviceStatus(i)
            ||MSD_STATUS_BUSY == msAPI_MSDCtrl_GetDeviceStatus(i)
            ||MSD_STATUS_EJECTED == msAPI_MSDCtrl_GetDeviceStatus(i)

           )
           return TRUE;
    }
    return FALSE;
}


BOOLEAN msAPI_MSDCtrl_GetDeviceMSDAddress(U8 deviceIndex,StorageDeviceAddress* pMSDAddrToSet)
{
    StorageDevice* pDevice=NULL;
    U8 u8DeviceNum = STORAGE_DEVICE_NUM;

    if(deviceIndex>=u8DeviceNum)
    {
        __ASSERT(0);
        return FALSE;
    }

    pDevice=(StorageDevice xdata*)msAPI_FS_GetAddr(STORAGE_DEVICE_MEMORY_ADDR);

    if(pDevice->DeviceIndex==INVALID_DEVICE_INDEX)
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        memcpy(pMSDAddrToSet,&pDevice[deviceIndex].MSDAddress,sizeof(StorageDeviceAddress));

        return TRUE;
    }
}

U8 msAPI_MSDCtrl_GetTotalDeviceCount()
{
    return STORAGE_DEVICE_NUM;
}



#endif

BOOLEAN msAPI_MSDCtrl_IsPortOpened(EN_MSD_PORT port)
{
    if(port >= MSD_PORT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }
    return g_bMSDPortOpened[port];
}

BOOLEAN msAPI_MSDCtrl_IsDeviceConnected(EN_MSD_PORT port)    //Check device directly
{
    if(port >= MSD_PORT_NUM)
    {
        __ASSERT(0);
        return FALSE;
    }

    switch(port)
    {
        case MSD_PORT_1://USB 1
            return MDrv_UsbDeviceConnect();
#if ENABLE_USB_2
        case MSD_PORT_2://USB 2
            return MDrv_UsbDeviceConnect_Port2();
#endif
        default:
            return FALSE;
    }
}

EN_MSD_PORT msAPI_MSDCtrl_GetDevicePort(U8 deviceIndex)
{
    EN_MSD_PORT port=INVALID_MSD_PORT;
    StorageDevice* pDevice=NULL;
    pDevice=(StorageDevice xdata*)msAPI_FS_GetAddr(STORAGE_DEVICE_MEMORY_ADDR);
    port=pDevice[deviceIndex].MSDAddress.Port;

    return port;
}

#ifdef ENABLE_PTP
EN_USB_CLASS msAPI_MSDCtrl_GetDeviceClass(U8 deviceIndex)
{
    U16 addr;

    EN_USB_CLASS class=INVALID_MSD_PORT;
    StorageDevice* pDevice=NULL;
    addr = (STORAGE_DEVICE_MEMORY_ADDR>>12);
    pDevice=(StorageDevice xdata*)msAPI_FS_GetXData(addr);
    class=pDevice[deviceIndex].DeviceClass;
    msAPI_FS_ReturnXData();

    return class;
}
#endif


#if FILE_SYSTEM_ENABLE_GET_MAX_DEVICE_COUNT
U8 msAPI_MSDCtrl_GetMaxDeviceCount(void)
{
    return STORAGE_DEVICE_NUM;
}
#endif

#if ENABLE_USB
static BOOLEAN MSD_CheckMSDPort1Devices_Ex(void)
{
    if(MDrv_UsbDeviceConnect())
    {
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_1))
        {
MDrv_Sys_DisableWatchDog();
            FS_RESET_WDT();
            U8 u8USBInitStatus = MDrv_Usb_Device_Enum_EX();
            switch(u8USBInitStatus)
            {
                case DEVENUM_OK:
                    MSD_SetPortOpened(MSD_PORT_1,TRUE);
                    break;

                case DEVENUM_INPROGRESS:
                    return TRUE;
                    break;

                case DEVENUM_FAIL:
                    MSD_DBG(printf("P1 DEVICE ENUM FAILED!!\n"););
                    MSD_SetPortOpened(MSD_PORT_1,TRUE);
                    break;

                default:
                    break;
            }
MDrv_Sys_EnableWatchDog();
        }

        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_1))
        {
            U8 lun=0xFF;
            U8 count=0;
#ifdef ENABLE_PTP
            //if (MDrv_GetUsbDeviceType() == USB_INTERFACE_CLASS_MSD)
            if (0)
            {
                count=MSD_GetMSDPort1LUNCount();
                lun = MDrv_GET_MASS_VALID_LUN();
                if(lun == 0xFF)
                {
                    MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                    return FALSE;
                }
                else
                {
                    U8 i=0;
                    for(i=0;i<MSD_USB_NUM;i++)
                    {
                        BOOLEAN ready=(lun>>(i))&1;
                        U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_1,i);

                        if(ready)
                        {
                            MSD_RegisterDevice(deviceIndex,MSD_PORT_1,i);
                            MSD_SetDeviceClass(deviceIndex,USB_CLASS_MSD);
                            MSD_DeviceStatusControlInserted(deviceIndex);
                        }
                        else
                        {
                            MSD_DeviceStatusControlUnplugged(deviceIndex);
                        }
                    }
                }
            }
            //else if (MDrv_GetUsbDeviceType() == USB_INTERFACE_CLASS_IMAGE)
            else
            {
                // Assume one drive.
                U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_1,0);

                MSD_RegisterDevice(deviceIndex,MSD_PORT_1,0);
                MSD_SetDeviceClass(deviceIndex,USB_CLASS_IMAGE);
                MSD_DeviceStatusControlInserted(deviceIndex);
            }
#else
            count=MSD_GetMSDPort1LUNCount();
MDrv_Sys_DisableWatchDog();
            lun = MDrv_GET_MASS_VALID_LUN();
MDrv_Sys_EnableWatchDog();
            g_u8USBCardReaderStatus = lun;
            if(lun == 0xFF)
            {
                MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                return FALSE;
            }
            else
            {
                U8 i=0;
                for(i=0;i<MSD_USB_NUM;i++)
                {

                    BOOLEAN ready=(lun>>(i))&1;
                    U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_1,i);

                    if(ready)
                    {
                        MSD_RegisterDevice(deviceIndex,MSD_PORT_1,i);
                        MSD_DeviceStatusControlInserted(deviceIndex);
                    }
                    else
                    {
                        MSD_DeviceStatusControlUnplugged(deviceIndex);
                    }
                }
            }
#endif
        }
        return FALSE;
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_1))
        {
            MSD_SetPortOpened(MSD_PORT_1,FALSE);
            msAPI_MSDCtrl_ResetPort(MSD_PORT_1);
        }
        return FALSE;
    }
}
#endif

#if ENABLE_USB_2
static BOOLEAN MSD_CheckMSDPort2Devices_Ex(void)
{
    if(MDrv_UsbDeviceConnect_Port2())
    {
        if(!msAPI_MSDCtrl_IsPortOpened(MSD_PORT_2))
        {
MDrv_Sys_DisableWatchDog();
            FS_RESET_WDT();
            U8 u8USBInitStatus = MDrv_Usb_Device_Enum_EX_Port2();
            switch(u8USBInitStatus)
            {
                case DEVENUM_OK:
                    MSD_SetPortOpened(MSD_PORT_2,TRUE);
                    break;

                case DEVENUM_INPROGRESS:
                    return TRUE;
                    break;

                case DEVENUM_FAIL:
                    MSD_DBG(printf("P1 DEVICE ENUM FAILED!!\n"););
                    MSD_SetPortOpened(MSD_PORT_2,TRUE);
                    break;

                default:
                    break;
            }
MDrv_Sys_EnableWatchDog();
        }

        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_2))
        {
            U8 lun=0xFF;
            U8 count=0;
            U8 i=0;
            U8 u8Iend;
#ifdef ENABLE_PTP
            //if (MDrv_GetUsbDeviceType_Port2() == USB_INTERFACE_CLASS_MSD)
            if (1)
            {
                count=MSD_GetMSDPort2LUNCount();
                lun = MDrv_GET_MASS_VALID_LUN_PORT2();
                if(lun == 0xFF)
                {
                    MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                    return FALSE;
                }
                else
                {
                    u8Iend = MSD_USB_NUM;
                    for(i=0;i<u8Iend;i++)
                    {
                        BOOLEAN ready=(lun>>(i))&1;
                        U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_2,i);

                        if(ready)
                        {
                            MSD_RegisterDevice(deviceIndex,MSD_PORT_2,i);
                            MSD_SetDeviceClass(deviceIndex,USB_CLASS_MSD);
                            MSD_DeviceStatusControlInserted(deviceIndex);
                        }
                        else
                        {
                            MSD_DeviceStatusControlUnplugged(deviceIndex);
                        }
                    }
                }
            }
            else if (MDrv_GetUsbDeviceType_Port2() == USB_INTERFACE_CLASS_IMAGE)
            {
                // Assume one drive.
                U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_2,0);

                MSD_RegisterDevice(deviceIndex,MSD_PORT_2,0);
                MSD_SetDeviceClass(deviceIndex,USB_CLASS_IMAGE);
                MSD_DeviceStatusControlInserted(deviceIndex);
            }
#else
            count=MSD_GetMSDPort2LUNCount();
MDrv_Sys_DisableWatchDog();
            lun = MDrv_GET_MASS_VALID_LUN_PORT2();
MDrv_Sys_EnableWatchDog();
            g_u8USB2CardReaderStatus = lun;
            if(lun == 0xFF)
            {
                 MSD_DBG(printf("GET LUN TIMEOUT!!\n"););
                 return FALSE;
            }
            else
            {
                u8Iend = MSD_USB_2_NUM;
                for(i=0;i<u8Iend;i++)
                {
                    BOOLEAN ready=(lun>>(i))&1;
                    U8 deviceIndex=MSD_GetDeviceIDByMSDAddress(MSD_PORT_2,i);

                    if(ready)
                    {
                        MSD_RegisterDevice(deviceIndex,MSD_PORT_2,i);
                        MSD_DeviceStatusControlInserted(deviceIndex);
                    }
                    else
                    {
                        MSD_DeviceStatusControlUnplugged(deviceIndex);
                    }
                }
            }
#endif
        }
        return FALSE;
    }
    else
    {
        if(msAPI_MSDCtrl_IsPortOpened(MSD_PORT_2))
        {
            MSD_SetPortOpened(MSD_PORT_2,FALSE);
            msAPI_MSDCtrl_ResetPort(MSD_PORT_2);
        }
        return FALSE;
    }
}
#endif

U8 msAPI_MSDCtrl_CheckDevices_Ex(void)
{
    U8 u8Return = 0;
#if (ENABLE_USB)
    if(MSD_CheckMSDPort1Devices_Ex()==TRUE)
    {
        u8Return |= MSD_PORT_1_ENUM_PROCESSING;
    }
    else
    {
        u8Return &= ~MSD_PORT_1_ENUM_PROCESSING;
    }
#endif

#if (ENABLE_USB_2)
    if(MSD_CheckMSDPort2Devices_Ex()==TRUE)
    {
        u8Return |= MSD_PORT_2_ENUM_PROCESSING;
    }
    else
    {
        u8Return &= ~MSD_PORT_2_ENUM_PROCESSING;
    }
#endif

#if (ENABLE_CARDREADER)
    MSD_CheckMSDPort0Devices();
#endif
#if defined(ENABLE_CF) && (ENABLE_CF == 1)
    MSD_CheckMSDPort3Devices();
#endif

#if ENABLE_NAND
    MSD_CheckMSDPort4Devices();
#endif

    return u8Return;
}

#undef   MSAPI_MSDCTRL_C
