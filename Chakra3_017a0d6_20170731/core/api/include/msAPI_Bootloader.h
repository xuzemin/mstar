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

////////////////////////////////////////////////////////////////////////////////////////////
// This file is commonly used by bootloader and system(main).
// Must be backward compatible with previously released version of bootloader.
////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_BOOTLOADER_H
#define    MSAPI_BOOTLOADER_H

#include "datatype.h"
#include "msAPI_FreqTableCommon.h"

#ifdef MSAPI_BOOTLOADER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define INVALID_PHYSICAL_CHANNEL_NUMBER     0xFF
#define BOOTLOADER_CODE_SIZE        0
//////////////////////////////////////////////////////////////////////////////////////////////////////
// Any change of RM_ADDR_DOWNLOAD may not be backward compatible with previously released bootloader
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define RM_ADDR_DOWNLOAD            (0)     // Must be at absolute address 0. The same as that in MApp_SaveData.h
#define RM_SIZE_DOWNLOAD            ((U16)sizeof(ST_DOWNLOAD_INFO))

///////////////////////////////////////////////////////////////////////////////////////////////////
// Any change of DOWNLOAD_TYPE may not be backward compatible with previously released bootloader
// Two different bits or more between any of the two download types
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    DOWNLOAD_TYPE_NONE          = 0x00,     // No download

    // Over Air Download / On The Air
    DOWNLOAD_TYPE_OAD_USER      = 0x13,     // AP detect the OAD Data
    DOWNLOAD_TYPE_OAD_AUTO      = 0x14,     // In the BootLoader, program will find the OAD Stream automatically

    // UART
    DOWNLOAD_TYPE_1KXMODEM      = 0x25,     // 1K XMODEM

    // USB
    DOWNLOAD_TYPE_USB_USER      = 0x37,     // User mode
    DOWNLOAD_TYPE_USB_EXPERT    = 0x3A,     // Expert mode

    // Max value is 0xFF since using data type U8
} EN_DOWNLOAD_TYPE;

typedef enum
{
    // System Status
    DLREASON_SELECTEDBL_OK               = 0x00,
    DLREASON_SELECTEDAP_OK               = 0x01,

    // Bootloader 1 Status
    DLREASON_BL1_RECEIVEDIMAGE_FL        = 0x10,
    DLREASON_BL1_INTEGRITY_FL            = 0x11,
    DLREASON_BL1_IMAGESIZE_FL            = 0x12,
    DLREASON_BL1_IMAGECRC_FL             = 0x13,

    // Bootloader 2 Status
    DLREASON_BL2_RECEIVEDIMAGE_FL        = 0x20,
    DLREASON_BL2_INTEGRITY_FL            = 0x21,
    DLREASON_BL2_IMAGESIZE_FL            = 0x22,
    DLREASON_BL2_IMAGECRC_FL             = 0x23,

    // AP1 Status
    DLREASON_AP1_RECEIVEDIMAGE_FL        = 0x30,
    DLREASON_AP1_INTEGRITY_FL            = 0x31,
    DLREASON_AP1_IMAGESIZE_FL            = 0x32,
    DLREASON_AP1_IMAGECRC_FL             = 0x33,

    // AP2 Status
    DLREASON_AP2_RECEIVEDIMAGE_FL        = 0x40,
    DLREASON_AP2_INTEGRITY_FL            = 0x41,
    DLREASON_AP2_IMAGESIZE_FL            = 0x42,
    DLREASON_AP2_IMAGECRC_FL             = 0x43,

    // Max value is 0xFF since using data type U8
} EN_DL_REASON_TYPE;

typedef enum
{
    DL_IMAGE_TYPE_BL1       = 0x00,
    DL_IMAGE_TYPE_BL2       = 0x01,
    DL_IMAGE_TYPE_AP1       = 0x10,
    DL_IMAGE_TYPE_AP2       = 0x11,
} EN_CHECK_IMAGE_TYPE;

typedef enum
{
    DL_IMAGE_STATUS_OK       = 0x00,
    DL_IMAGE_STATUS_FL       = 0x01,
} EN_IMAGE_STATUS;

typedef enum
{
    DL_DEFAULT_IMAGE_AP1       = 0x00,
    DL_DEFAULT_IMAGE_AP2       = 0x01,
} EN_DEFAULT_IMAGE_TYPE;

typedef enum
{
    DL_UPDATE_NONE      = 0x00,
    DL_UPDATE_DONE      = 0x01,
} EN_DL_UPDATE_ID;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Any change of ST_DOWNLOAD_INFO may not be backward compatible with previously released bootloader
// All members are initialized to zeros.
///////////////////////////////////////////////////////////////////////////////////////////////////
#define DL_INTEGRITY_ID           0x5A
#define DL_MAX_SHORTNAME_LEN      (2+1+8+1+3)     // "A:\12345678.123"
#define DL_MAX_LONGNAME_LEN       40              // File name only, not including path.
#define DL_RESERVED_LEN           (100 - 38 - (DL_MAX_SHORTNAME_LEN+1) - (DL_MAX_LONGNAME_LEN + 1))

/* Total 100 Bytes */
typedef struct
{
#if 0
                                            // 38 Bytes
    U8  u8DL_ID;                            // For integrity check of download type. (0x5A)
    U8  u8DL_DWNType;                       // Must be explicitly declared as U8 instead of DOWNLOAD_TYPE.
    U8  u8DL_UpdatedStatus;                 // Report the status after download & burn
    U8  u8DL_UpdatedReasonID;               // Reason ID for three type download method

    U8  u8DL_DefaultAPSelection;            // Select AP1 or AP2
    U8  u8DL_PreviousAP_Version_MajorNo;    // Previous AP code version, major number
    U8  u8DL_PreviousAP_Version_MinorNo;    // Previous AP code version, minor number

    U8  u8DL_AP1_Status;                    // FW code (AP code) Status. 0-> Good / 1-> Bad
    U8  u8DL_AP1_Version_MajorNo;           // FW Version Major number
    U8  u8DL_AP1_Version_MinorNo;           // FW Version Minor number

    U8  u8DL_AP2_Status;
    U8  u8DL_AP2_Version_MajorNo;
    U8  u8DL_AP2_Version_MinorNo;

    U8  u8DL_DefaultBLSelection;            // Select BootLoader 1 or BootLoader 2
    U8  u8DL_BL1_Status;                    // FW code (BootLoader code) Status. 0-> Good / 1-> Bad
    U8  u8DL_BL1_Version_MajorNo;           // BootLoader Version Major number
    U8  u8DL_BL1_Version_MinorNo;           // BootLoader Version Minor number

    U8  u8DL_BL2_Status;
    U8  u8DL_BL2_Version_MajorNo;
    U8  u8DL_BL2_Version_MinorNo;
#endif

    /* For OAD Usage */
    U8  u8DL_OAD_PID_High;                  // High byte of PID
    U8  u8DL_OAD_PID_Low;                   // Low byte of PID
    U8  u8DL_OAD_TSFreq1;                   // Physical Freqency
    U8  u8DL_OAD_TSFreq2;                   // Physical Freqency
    U8  u8DL_OAD_TSFreq3;                   // Physical Freqency
    U8  u8DL_OAD_TSFreq4;                   // Physical Freqency
    U8  u8DL_OAD_BW;                        // Bandwidth setting: 6/7/8 MHz
    //U8  u8DL_OAD_CountryGroup;              // Set Country Group
    U8  u8DL_OAD_ScheduleOn;
    U8  u8DL_OAD_Country;                   // Set Country
    U8  u8DL_OAD_MonitorState;
    U16 u16DL_OAD_NID;
    U16 u16DL_OAD_TID;
    U16 u16DL_OAD_SID;
    U32 u32DL_OAD_StartTime;
    U32 u32DL_OAD_EndTime;
    U16 u16DL_OAD_AssociationTag;
    U16 u16DL_OAD_DTVSource;

#if 0
    /* Use the Tag to control which TV production needed to download new FW */
    U8  u8DL_Board_Version;                 // HW Board Version
    U8  u8DL_ProductSeqNo1;                 // Production Unique ID1
    U8  u8DL_ProductSeqNo2;                 // Production Unique ID2
    U8  u8DL_ProductAreaID;                 // Customer's Area
#endif

#if 0
    /* Buyer ID */
    U8  u8DL_CustomID1;
    U8  u8DL_CustomID2;
    U8  u8DL_CustomID3;
#endif

#if 0
    /* Manufacturer */
    U8  u8DL_ManufactureID1;                // IEEE OUI1
    U8  u8DL_ManufactureID2;                // IEEE OUI2
    U8  u8DL_ManufactureID3;                // IEEE OUI3
#endif

    /*For save service*/
    U16 u16Save_TSID;
    U16 u16Save_ONID;
    U16 u16Save_SID;

    /* UNT shedule time */
    U8 auDLSchedule_time[48];
#if 1
    /* Reserved bytes */
    U8  u8DL_Reserved[DL_RESERVED_LEN];                     // remaining 8 Bytes
#endif
} ST_DOWNLOAD_INFO;

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
INTERFACE void msAPI_BLoader_ClearDownloadInfo(void);
INTERFACE void msAPI_BLoader_BootupSwitch(void);
INTERFACE void msAPI_BLoader_Reboot(void);
INTERFACE BOOLEAN msAPI_BLoader_CheckIntegrity(void);
INTERFACE BOOLEAN msAPI_BLoader_GetDownloadType(EN_DOWNLOAD_TYPE * u8Type);
INTERFACE void msAPI_BLoader_SetDownloadType(EN_DOWNLOAD_TYPE u8DownloadType);
INTERFACE void msAPI_BLoader_SetCountry(U8 u8Country);

#ifdef TWO_AP_IN_FLASH_TWO_4MB
INTERFACE BOOLEAN msAPI_BLoader_CheckIntegrity3(void);
#endif

INTERFACE BOOLEAN msAPI_BLoader_IsIspUpdate(void);
INTERFACE BOOLEAN msAPI_BLoader_ClearIspUpdate(void);


#undef INTERFACE

#endif

