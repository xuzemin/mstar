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
#ifndef _DRVUSB_H_
#define _DRVUSB_H_
#include "SW_Config.h"
#include "Board.h"
#if (ENABLE_PWS == 1)
//#define     USB_POWER_SAVING_MODE
#endif

#if ENABLE_DMP
#define     USBHOST2PORT                                //for 2 usb ports board, if you use only one port , please undefine it.
#endif


extern void MDrv_USB_EnterPowerSaveMode(void);
extern void MDrv_USB_EnterPowerSaveMode_Port2(void);
extern void MDrv_USB_EnterPowerSaveMode_Port3(void);
extern void MDrv_USB_EnterPowerSaveMode_Port4(void);


extern BOOLEAN MDrv_UsbHost_Init(void);
extern BOOLEAN MDrv_UsbHost_Init_Enum(void);
U8 MDrv_USBGetPortEnableStatus(void);

#define     MDrv_UsbDiskRead_Port2    MDrv_UsbBlockReadToMIU_Port2
#define     MDrv_UsbDiskWrite_Port2   MDrv_UsbBlockWriteFromMIU_Port2
extern BOOLEAN MDrv_UsbBlockReadToMIU_Port2(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbBlockWriteFromMIU_Port2(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbDeviceConnect_Port2(void);
U8 MDrv_GET_MASS_MAX_LUN_PORT2(void);
U8 MDrv_GET_MASS_VALID_LUN_PORT2(void);
extern BOOLEAN  MDrv_Usb_Device_Enum_Port2(void);
extern U8 MDrv_Usb_Device_Enum_EX_Port2(void);
extern void MDrv_UsbClose_Port2(void);
extern void MDrv_USB_Init_Port2(U32);
extern U8 MDrv_UsbGetMaxLUNCount_Port2(void);
extern void MDrv_EjectUsbDevice_Port2(void);
U32 MDrv_GetUsbBlockSize_Port2(U8 lun);
U32 MDrv_GetUsbBlockNum_Port2(U8 lun);
extern BOOLEAN MDrv_UsbHost_Init_Enum_Port2(void);
U8  MDrv_GetUsbDeviceStatusPort2(void);
void MDrv_SetUsbDeviceStatus_Port2(U8 status);
U8 MDrv_GetUsbDeviceType_Port2(void);
void MDrv_GetUsbString_Port2(U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
U8*  MDrv_Get_HID_Report_Raw_Data_Port2(void);
U8 MDrv_USBGetqTDTimeoutValue_Port2(void);
void MDrv_USBSetqTDTimeoutValue_Port2(U8 u8Value);
U8 MDrv_USBGetIORetryCount_Port2(void);
void MDrv_USBSetIORetryCount_Port2(U8 u8Value);
void MDrv_GetUsbStorString_Port2(U8 uLun, U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
void MDrv_UsbSendTestPacket_Port2(void);
void MDrv_UsbSendSE0_Port2(void);
void MDrv_UsbSendTestJ_Port2(void);
void MDrv_UsbSendTestK_Port2(void);
U8 MDrv_GetUsbDevInterfaceClass_Port2(void);

#define     MDrv_UsbDiskRead    MDrv_UsbBlockReadToMIU
#define     MDrv_UsbDiskWrite   MDrv_UsbBlockWriteFromMIU
extern BOOLEAN MDrv_UsbBlockReadToMIU(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbBlockWriteFromMIU(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbDeviceConnect(void);
extern U8 MDrv_UsbGetInterfaceClass(U8 i,U8 j);
extern void MDrv_UsbClose(void);
extern void MDrv_USB_Init(U32);
extern BOOLEAN  MDrv_Usb_Device_Enum(void);
extern U8 MDrv_Usb_Device_Enum_EX(void);
extern U8 flib_Host20_Enumerate (U8,U8 );
extern void MDrv_EjectUsbDevice(void);
U32 MDrv_GetUsbBlockSize(U8 lun);
U32 MDrv_GetUsbBlockNum(U8 lun);

extern U8 MDrv_UsbGetMaxLUNCount(void);
U8 MDrv_GET_MASS_MAX_LUN(void);
U8 MDrv_GET_MASS_VALID_LUN(void);

U8  MDrv_GetUsbDeviceStatus(void);
void MDrv_SetUsbDeviceStatus(U8 status);
void  MDrv_ClearUsbDeviceStatus(void);
U8 MDrv_GetUsbDeviceType(void);
void MDrv_GetUsbString(U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
U16  MDrv_GET_JOYSTICK_STATUS(void);
U8*  MDrv_Get_HID_Report_Raw_Data(void);
U8 MDrv_USBGetqTDTimeoutValue(void);
void MDrv_USBSetqTDTimeoutValue(U8 u8Value);
U8 MDrv_USBGetIORetryCount(void);
void MDrv_USBSetIORetryCount(U8 u8Value);
BOOLEAN MDrv_USBGetPortAutoSwitchStatus(void);
void MDrv_USBSetPortAutoSwitchStatus(BOOLEAN bEnable);
void MDrv_USBSetPortSwitch(U8 uPort);
void MDrv_GetUsbStorString(U8 uLun, U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
void MDrv_UsbSendTestPacket(void);
void MDrv_UsbSendSE0(void);
void MDrv_UsbSendTestJ(void);
void MDrv_UsbSendTestK(void);
U8 MDrv_GetUsbDevInterfaceClass(void);

#define     MDrv_UsbDiskRead_Port3    MDrv_UsbBlockReadToMIU_Port3
#define     MDrv_UsbDiskWrite_Port3   MDrv_UsbBlockWriteFromMIU_Port3
extern BOOLEAN MDrv_UsbBlockReadToMIU_Port3(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbBlockWriteFromMIU_Port3(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbDeviceConnect_Port3(void);
U8 MDrv_GET_MASS_MAX_LUN_PORT3(void);
U8 MDrv_GET_MASS_VALID_LUN_PORT3(void);
extern BOOLEAN  MDrv_Usb_Device_Enum_Port3(void);
extern U8 MDrv_Usb_Device_Enum_EX_Port3(void);
extern void MDrv_UsbClose_Port3(void);
extern void MDrv_USB_Init_Port3(U32);
extern U8 MDrv_UsbGetMaxLUNCount_Port3(void);
extern void MDrv_EjectUsbDevice_Port3(void);
U32 MDrv_GetUsbBlockSize_Port3(U8 lun);
U32 MDrv_GetUsbBlockNum_Port3(U8 lun);
extern BOOLEAN MDrv_UsbHost_Init_Enum_Port3(void);
U8  MDrv_GetUsbDeviceStatusPort3(void);
void MDrv_SetUsbDeviceStatus_Port3(U8 status);
U8 MDrv_GetUsbDeviceType_Port3(void);
void MDrv_GetUsbString_Port3(U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
U8*  MDrv_Get_HID_Report_Raw_Data_Port3(void);
U8 MDrv_USBGetqTDTimeoutValue_Port3(void);
void MDrv_USBSetqTDTimeoutValue_Port3(U8 u8Value);
U8 MDrv_USBGetIORetryCount_Port3(void);
void MDrv_USBSetIORetryCount_Port3(U8 u8Value);
void MDrv_GetUsbStorString_Port3(U8 uLun, U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
void MDrv_UsbSendTestPacket_Port3(void);
void MDrv_UsbSendSE0_Port3(void);
void MDrv_UsbSendTestJ_Port3(void);
void MDrv_UsbSendTestK_Port3(void);
U8 MDrv_GetUsbDevInterfaceClass_Port3(void);

#define     MDrv_UsbDiskRead_Port4    MDrv_UsbBlockReadToMIU_Port4
#define     MDrv_UsbDiskWrite_Port4   MDrv_UsbBlockWriteFromMIU_Port4
extern BOOLEAN MDrv_UsbBlockReadToMIU_Port4(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbBlockWriteFromMIU_Port4(U8 lun,U32 u32BlockAddr, U32 u32BlockNum,U32 u32Buffer);
extern BOOLEAN MDrv_UsbDeviceConnect_Port4(void);
U8 MDrv_GET_MASS_MAX_LUN_PORT4(void);
U8 MDrv_GET_MASS_VALID_LUN_PORT4(void);
extern BOOLEAN  MDrv_Usb_Device_Enum_Port4(void);
extern U8 MDrv_Usb_Device_Enum_EX_Port4(void);
extern void MDrv_UsbClose_Port4(void);
extern void MDrv_USB_Init_Port4(U32);
extern U8 MDrv_UsbGetMaxLUNCount_Port4(void);
extern void MDrv_EjectUsbDevice_Port4(void);
U32 MDrv_GetUsbBlockSize_Port4(U8 lun);
U32 MDrv_GetUsbBlockNum_Port4(U8 lun);
extern BOOLEAN MDrv_UsbHost_Init_Enum_Port4(void);
U8  MDrv_GetUsbDeviceStatusPort4(void);
void MDrv_SetUsbDeviceStatus_Port4(U8 status);
U8 MDrv_GetUsbDeviceType_Port4(void);
void MDrv_GetUsbString_Port4(U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
U8*  MDrv_Get_HID_Report_Raw_Data_Port4(void);
U8 MDrv_USBGetqTDTimeoutValue_Port4(void);
void MDrv_USBSetqTDTimeoutValue_Port4(U8 u8Value);
U8 MDrv_USBGetIORetryCount_Port4(void);
void MDrv_USBSetIORetryCount_Port4(U8 u8Value);
void MDrv_GetUsbStorString_Port4(U8 uLun, U8 u8StrID, S8 *pStrBuf, U8 u8BufLen);
void MDrv_UsbSendTestPacket_Port4(void);
void MDrv_UsbSendSE0_Port4(void);
void MDrv_UsbSendTestJ_Port4(void);
void MDrv_UsbSendTestK_Port4(void);
U8 MDrv_GetUsbDevInterfaceClass_Port4(void);

#define USB_NOT_RESPONSE		    0xff
#define USB_INTERFACE_CLASS_NONE 0
#define USB_INTERFACE_CLASS_MSD  0x08
#define USB_INTERFACE_CLASS_HUB  0x09
#define USB_INTERFACE_CLASS_IMAGE  0x06
#define USB_INTERFACE_CLASS_HID  0x03


//Chip ID deifinition
#define CHIPID_NEPTUNE     0x2
#define CHIPID_ERIS            0x3
#define CHIPID_TITANIA      0x4
#define CHIPID_PLUTO          0x5
#define CHIPID_TRITON        0x6
#define CHIPID_TITANIA2    0xB
#define CHIPID_TITANIA3    0xF
#define CHIPID_EUCLID        0x15
#define CHIPID_TITANIA4     0x18
#define CHIPID_TITANIA7     0x1C
#define CHIPID_TITANIA8     0x1F
#define CHIPID_TITANIA9     0x23
#define CHIPID_JANUS        0x1D

// project code definition
#define     JUPITER                 0
#define     NEPTUNE                 1
#define     RAPHAEL                 2
#define     ERIS                    3

#define 	NO_DEVICE               0
#define     USB11_DEVICE            1
#define 	USB20_DEVICE            2
#define	    BAD_DEVICE              3
#define     CONNECT_DEVICE          4
#define     POWER_SAVING            5
#define     WAIT_INIT               6

#define USB_PORT_0          0
#define USB_PORT_2          1
#define USB_PORT_3          2
#define USB_PORT_4          3

#define USB_STR_VENDOR              1
#define USB_STR_PRODUCT            2

enum // for return value of MDrv_Usb_Device_Enum_EX()
{
DEVENUM_OK = 0,
DEVENUM_INPROGRESS,
DEVENUM_FAIL
};
#endif
