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
// (!MStar Confidential Information!L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MW_USBDOWNLOAD_C

/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <stdio.h>
#include <string.h>

// Global Layer
#include "datatype.h"
#include "MsTypes.h"
#include "imginfo.h"
#include "debug.h"
#include "Board.h"

// Driver Layer
#include "drvUSB.h"
#include "drvBDMA.h"

// API Layer
#include "msAPI_FCtrl.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_Memory.h"

// MW Layer
#include "mw_usbdownload.h"

// APP Layer
#include "mapp_swupdate.h"
#include "msAPI_Timer.h"
#include "MApp_USBDownload.h"

#if(ENABLE_MFC_6M30)
#include "drvUrsa6M30.h"
#include "MApp_Isp.h"
#elif (ENABLE_MFC_6M20)  //
#include "drvUrsaMFCAPI.h"
#include "MApp_Isp.h"
#elif(ENABLE_6M40_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#include "MApp_Isp.h"
#endif


/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
BOOLEAN b_isWriteCIkey = FALSE;
BOOLEAN b_isCIkeyFileExit = TRUE;
#endif

// Debug message for USB Download
#define USB_DL_DBG(x)           //x
#define USB_DL_ASSERT(x)        x

// Max USB detection duration
#define MAX_USB_DETECTION_DURATION  2000    // ms
#define XD2PHY(xadr)        ((U32)(xadr))

/******************************************************************************/
/*                                 Structure                                  */
/******************************************************************************/

/******************************************************************************/
/*                             Public Variable                                */
/******************************************************************************/
pZUIDrawCB pZUIDrawPercentageCB = 0;

/******************************************************************************/
/*                             Private Variable                               */
/******************************************************************************/
static U8 _u8USBEnvironmentID = 0xFF;
static U8 _u8USBStatus = 0;
static U8 _u8USBPortNo = 0;
static U8 _u8UpgradeMode = 0;
static U8 _u8MemType = 0;
static U8 _u8FlashID = 0;
static U8 _pu8FileName[20] ={0};
static U32 _u32DRAMAddr = 0;
static U32 _u32DRAMLen = 0;
static U32 _u32FlashSize = 0;
static U32 _u32DownloadSize = 0;

#if ENABLE_TTSTEST_FROM_USB
static U8 *_pu16FileStr = NULL;
static U16 _u16Length = 0;
static U16 _u16TestFileSize = 0;
static U8 u8ReadTxTFlag = 0;
#define DOWNLOAD_BUFFER_ADR_TTSTEST  ((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR))
#define DOWNLOAD_BUFFER_LEN_TTSTEST   DOWNLOAD_BUFFER_LEN
#endif

static BOOLEAN  _bUsbInitialized = FALSE;
static BOOLEAN  _bAPBinFlag = FALSE;
static BOOLEAN  _bFlashID1 = FALSE;
static BOOLEAN  _bFlashID2 = FALSE;
static FileEntry _fileEntry2;
static FileEntry _fileEntry;

static DownloadCheckEnumType _DownloadCheckType = DL_CK_NONE;
static DownloadErrorEnumType _DownloadErrorType = DL_ERROR_NORMAL;

/******************************************************************************/
/*                           Public Function                                  */
/******************************************************************************/
void MW_UsbDownload_Init(U8 u8USBPortNo, U8 u8FlashID, U32 u32DRAMAddr, U32 u32DRAMLen, U32 u32FlashSize, U8 u8UpgradeMode, U8 u8MemType, U8 * pu8FileName, pZUIDrawCB ZUIDrawPercentage, BOOLEAN bAPBinFlag);
BOOLEAN MW_UsbDownload_Search(void);
BOOLEAN MW_UsbDownload_Start(void);

/******************************************************************************/
/*                             Private Function                                */
/******************************************************************************/
static BOOLEAN _MW_UsbDownload_StartDevice(S8 deviceIndex);
static BOOLEAN _MW_UsbDownload_SearchFileInRoot(U8* pu8FileName, FileEntry* pFileEntry);
static BOOLEAN _MW_UsbDownload_Copy(U32 u32DRAMAddr, U32 u32DRAMLen, U32 u32FlashSize);
static BOOLEAN _MW_UsbDownload_InitFileSystem(void);
static void _MW_UsbDownload_Exit(void);
static BOOLEAN _MW_UsbDownload_CheckHeader(void);

/******************************************************************************/
/*                          External Function                                 */
/******************************************************************************/
extern void ASCIItoUnicode2(S8 *ps8FileName, U8 len);
extern U32 msAPI_Timer_GetTime0(void);
extern U32 msAPI_Timer_DiffTimeFromNow(U32 u32TaskTimer);
extern BOOLEAN MApp_MassStorage_DeviceDisconnect(void);
extern void MApp_UsbClearWatchDog(void);

/******************************************************************************/
/*                             Code Implementation                            */
/******************************************************************************/
static BOOLEAN _MW_UsbDownload_StartDevice(S8 deviceIndex)
{
    EN_MSD_STATUS status=msAPI_MSDCtrl_GetDeviceStatus(deviceIndex);

    USB_DL_DBG(printf("deviceStatus=%d for deviceIndex=%d\n",(U8)status,(U8)deviceIndex));

    if(status==MSD_STATUS_INSERTED)
    {
        return msAPI_FCtrl_ActiveDevice(deviceIndex);
    }
    else if(status==MSD_STATUS_IDLE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static BOOLEAN _MW_UsbDownload_SearchFileInRoot(U8* pu8FileName, FileEntry* pFileEntry)
{
    U8  len;
    U8 *pu8Name;

    BOOLEAN result=FALSE;
    U16 *pFileNameToCompare=NULL;

    USB_DL_DBG(printf("_MW_UsbDownload_SearchFileInRoot(%s)\n", pu8FileName));

    len = strlen((char *)pu8FileName);

    if(len==0)
    {
        USB_DL_ASSERT(printf("Error> File name length is 0\n"));
        return FALSE;
    }

    if(!msAPI_FCtrl_DirectoryChangeToRoot(_u8USBEnvironmentID))
    {
        USB_DL_ASSERT(printf("Error> msAPI_FCtrl_DirectoryChangeToRoot failed\n"));
        return FALSE;
    }

    pu8Name=(U8 *)msAPI_Memory_Allocate(128*2, BUF_ID_USB_DOWNLOAD);
    if(pu8Name==NULL)
    {
        __ASSERT(0);
        USB_DL_ASSERT(printf("Error> 1. msAPI_Memory_Allocate failed\n"));
        return FALSE;
    }

    memset(pu8Name, 0, 256); //memset(pu8Name, 0, sizeof(pu8Name)); fix coverity 12848
    memcpy(pu8Name, pu8FileName, strlen((char *)pu8FileName));
    ASCIItoUnicode2((S8 *)pu8Name, strlen((char *)pu8Name));

    pFileNameToCompare=(U16 *)msAPI_Memory_Allocate(128*2, BUF_ID_USB_DOWNLOAD);
    if(pFileNameToCompare==NULL)
    {
        __ASSERT(0);
        if (pu8Name != NULL)
        {
            msAPI_Memory_Free(pu8Name, BUF_ID_USB_DOWNLOAD);
            pu8Name = NULL;
        }
        USB_DL_ASSERT(printf("Error> 2. msAPI_Memory_Allocate failed\n"));
        return FALSE;
    }


    //printf("Check files in disk:\n");

nextentry:

    while(msAPI_FCtrl_EntryNext(_u8USBEnvironmentID,pFileEntry)==ENTRY_NEXT_RESULT_SUCCESS)
    {
        U8 lenToCompare;

        MApp_UsbClearWatchDog();
        lenToCompare = msAPI_FCtrl_EntryGetCurrentName(_u8USBEnvironmentID, XD2PHY(pFileNameToCompare), 127);

    #if 0 // Print file name in USB disk
        {
            U8 u8ChIdx;
            U16 u16Tmp;


            for(u8ChIdx = 0; (u8ChIdx < lenToCompare)&&(u8ChIdx<30); ++ u8ChIdx )
            {
                u16Tmp = pFileNameToCompare[u8ChIdx];
                if( u16Tmp == 0 )
                    break;

                if( (u16Tmp >= 0x80) || (u16Tmp < 0x20) )
                    printf("(0x%X)", u16Tmp);
                else
                    printf("%c",u16Tmp);
            }
            printf("\n");
        }
    #endif

        if(lenToCompare==len)
        {
            U8 i;
		#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
			if(b_isWriteCIkey == TRUE)
			{
				for(i=len-1; i > len-5; i--)
				{
					U16 c1, c2;

					c1 = pu8FileName[i];
					c2 = pFileNameToCompare[i];

					if ((c1 >= 'a') && (c1 <= 'z'))
					{
						c1 -= 'a' - 'A';
					}

					if ((c2 >= 'a') && (c2 <= 'z'))
					{
						c2 -= 'a' - 'A';
					}

					if (c1 != c2 )
					{
						goto nextentry;
					}
				}

			}
			else
		#endif
			{
	            for(i=0; i<len; i++)
	            {
	                U16 c1, c2;

	                c1 = pu8FileName[i];
	                c2 = pFileNameToCompare[i];

	                if ((c1 >= 'a') && (c1 <= 'z'))
	                {
	                    c1 -= 'a' - 'A';
	                }

	                if ((c2 >= 'a') && (c2 <= 'z'))
	                {
	                    c2 -= 'a' - 'A';
	                }

	                if (c1 != c2 )
	                {
	                    goto nextentry;
	                }
	            }
			}
            USB_DL_DBG(printf("*Found %s\n", pu8FileName));

            result=TRUE;
            break;
        }
    }

    msAPI_Memory_Free(pFileNameToCompare, BUF_ID_USB_DOWNLOAD);
    pFileNameToCompare = NULL;

    msAPI_Memory_Free(pu8Name, BUF_ID_USB_DOWNLOAD);
    pu8Name = NULL;

    return result;
}

static BOOLEAN _MW_UsbDownload_Copy(U32 u32DRAMAddr, U32 u32DRAMLen, U32 u32FlashSize)
{
    U8      u8HandleNo;
    U32     u32FileSize = 0;
    U32     u32LengthLeft = 0;

    u8HandleNo = msAPI_FCtrl_FileOpen(&_fileEntry, OPEN_MODE_FOR_READ);
    if(u8HandleNo == FCTRL_INVALID_FILE_HANDLE)
    {
        USB_DL_ASSERT(printf("Error> Image file open failed\n"));
        return FALSE;
    }

    u32FileSize = msAPI_FCtrl_FileLength(u8HandleNo);
    printf("File size: 0x%08lx; Flash size: 0x%08lx;\n", u32FileSize, u32FlashSize);
    printf("Download Buffer Addr: 0x%08lx; Download Buffer Size: 0x%08lx\n", u32DRAMAddr, u32DRAMLen);

    if ((u32FileSize == 0) || (u32FileSize > u32FlashSize) || (u32FileSize > u32DRAMLen))
    {
        USB_DL_ASSERT(printf("Error> File size error\n"));
        msAPI_FCtrl_FileClose(u8HandleNo);
        return FALSE;
    }

    MApp_UsbClearWatchDog();

    printf("Copying image from USB to DRAM\n");
    u32LengthLeft = msAPI_FCtrl_FileRead(u8HandleNo, u32DRAMAddr, u32FileSize);
    msAPI_FCtrl_FileClose(u8HandleNo);

  #if (ENABLE_MFC_6M30||ENABLE_MFC_6M20||ENABLE_6M40_4KX2K_PROCESS)  //
    if (g_eUSBSWUpdateChipType == SWUpdateForMFC)
    {
          MApp_MFC_ISP_Init(u32DRAMAddr, u32FileSize);

          if(u32LengthLeft != 0)
          {
               USB_DL_ASSERT(printf("Error> Read MFC file failed\n"));
               return FALSE;
          }
	   else
          {
               USB_DL_ASSERT(printf("OK> Read MFC file completed\n"));
               return TRUE;
          }
    }
  #endif

    if(u32LengthLeft == 0)
    {
        _u32DownloadSize = u32FileSize;
        if(0x0 != MDrv_BDMA_CRC32(u32DRAMAddr, _u32DownloadSize, BDMA_CRC32_POLY, BDMA_CRC_SEED_0, E_BDMA_SRCDEV_MIU0, FALSE))
        {
            USB_DL_ASSERT(printf("Error> CRC32 Integrity Check failed !!\n"));
            return FALSE;
        }
        else
        {
            printf("CRC32 Integrity Check pass !!\n");
        }
    }
    else
    {
        USB_DL_ASSERT(printf("Error> Read file failed\n"));
        return FALSE;
    }

    return TRUE;
}

/////////////////////////////////////////////////////
static BOOLEAN _MW_UsbDownload_InitFileSystem(void)
{
    _bUsbInitialized = FALSE;
    _u8USBEnvironmentID = 0xFF;
    int i;


    //printf("_MW_UsbDownload_InitFileSystem() _u8USBPortNo=%u\n", _u8USBPortNo);

    // Disable debug-U2U function
#if( ENABLE_UART_MSG_TO_USB )
    msDebug_UartToUSB_Set_Enable(DISABLE);
#endif

    msAPI_FS_Init();
    msAPI_MSDCtrl_CheckDevices();

    if (_u8USBPortNo == 0x1)
    {
        //EN_MSD_STATUS DeviceStatus = msAPI_MSDCtrl_GetDeviceStatus(MSD_USB_INDEX_START);
        for(i = MSD_USB_INDEX_START; i < MSD_USB_INDEX_START + MSD_USB_NUM; i++)
        {
            EN_MSD_STATUS eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);

            if( eMsdStatue == MSD_STATUS_INSERTED )
            {
                _MW_UsbDownload_StartDevice(i);
                eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);
            }

            if( eMsdStatue == MSD_STATUS_IDLE )
            {
                _u8USBEnvironmentID = msAPI_FSEnv_Register(0x00 /*'A'*/);
                _bUsbInitialized = msAPI_FCtrl_DirectoryChangeToRoot(_u8USBEnvironmentID);
                break;
            }
        }
        if(!_bUsbInitialized)
        {
            USB_DL_ASSERT(printf("Error> USB PORT 1 DEVICE DETECT ERROR!!\n"));
        }
    }
    else if (_u8USBPortNo == 0x2)
    {
        for(i = MSD_USB_2_INDEX_START; i < MSD_USB_2_INDEX_START + MSD_USB_2_NUM; i++)
        {
            EN_MSD_STATUS eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);

            if( eMsdStatue == MSD_STATUS_INSERTED )
            {
                _MW_UsbDownload_StartDevice(i);
                eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);
            }

            if( eMsdStatue == MSD_STATUS_IDLE )
            {
                _u8USBEnvironmentID = msAPI_FSEnv_Register(0x00 /*'A'*/);
                _bUsbInitialized = msAPI_FCtrl_DirectoryChangeToRoot(_u8USBEnvironmentID);
                break;
            }
        }
        if(!_bUsbInitialized)
        {
            USB_DL_ASSERT(printf("Error> USB PORT 2 DEVICE DETECT ERROR!!\n"));
        }
    }
    else if (_u8USBPortNo == 0x4)
    {
        for(i = MSD_USB_3_INDEX_START; i < MSD_USB_3_INDEX_START + MSD_USB_3_NUM; i++)
        {
            EN_MSD_STATUS eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);

            if( eMsdStatue == MSD_STATUS_INSERTED )
            {
                _MW_UsbDownload_StartDevice(i);
                eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);
            }

            if( eMsdStatue == MSD_STATUS_IDLE )
            {
                _u8USBEnvironmentID = msAPI_FSEnv_Register(0x00 /*'A'*/);
                _bUsbInitialized = msAPI_FCtrl_DirectoryChangeToRoot(_u8USBEnvironmentID);
                break;
            }
        }
        if(!_bUsbInitialized)
        {
            USB_DL_ASSERT(printf("Error> USB PORT 3 DEVICE DETECT ERROR!!\n"));
        }
    }
    else if (_u8USBPortNo == 0x8)
    {
        for(i = MSD_USB_4_INDEX_START; i < MSD_USB_4_INDEX_START + MSD_USB_4_NUM; i++)
        {
            EN_MSD_STATUS eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);
            if( eMsdStatue == MSD_STATUS_INSERTED )
            {
                _MW_UsbDownload_StartDevice(i);
                eMsdStatue = msAPI_MSDCtrl_GetDeviceStatus(i);
            }

            if( eMsdStatue == MSD_STATUS_IDLE )
            {
                _u8USBEnvironmentID = msAPI_FSEnv_Register(0x00 /*'A'*/);
                _bUsbInitialized = msAPI_FCtrl_DirectoryChangeToRoot(_u8USBEnvironmentID);
                break;
            }
        }
        if(!_bUsbInitialized)
        {
            USB_DL_ASSERT(printf("Error> USB PORT 4 DEVICE DETECT ERROR!!\n"));
        }
    }

    else
    {
        USB_DL_ASSERT(printf("Error> USB PORT NUMBER ERROR!!\n"));
    }

    if (_bUsbInitialized)
    {
        return TRUE;
    }
    else
    {
        USB_DL_ASSERT(printf("Error> File system init error\n"));
        return FALSE;
    }
}

static void _MW_UsbDownload_Exit(void)
{
    USB_DL_DBG(printf("_MW_UsbDownload_Exit\n"));
    if (_bUsbInitialized)
    {
        //_bUsbInitialized = FALSE;
        //msAPI_FCtrl_FileHandleResetAll();
        msAPI_FSEnv_UnRegister(_u8USBEnvironmentID);

        //MApp_MassStorage_DeviceDisconnect();
        //msAPI_FCtrl_Init();
    }
}

static BOOLEAN _MW_UsbDownload_CheckHeader(void)
{
    U8    u8HandleNo;
    U32  u32LengthLeft;
    U32  u32FileSize;

    u8HandleNo = msAPI_FCtrl_FileOpen(&_fileEntry2, OPEN_MODE_FOR_READ);
    if(u8HandleNo == FCTRL_INVALID_FILE_HANDLE)
    {
        USB_DL_ASSERT(printf("Error> Open the 2nd flash BIN file failed\n"));
        return FALSE;
    }

    u32FileSize = msAPI_FCtrl_FileLength(u8HandleNo);
    USB_DL_DBG( printf("File size: %d ; Download Buffer Size: %d\n", u32FileSize, _u32DRAMLen) );

    u32LengthLeft = msAPI_FCtrl_FileRead(u8HandleNo, _u32DRAMAddr, u32FileSize);
    if(u32LengthLeft == 0)
    {
        _u32DownloadSize = u32FileSize;
    }
    else
    {
        USB_DL_ASSERT(printf("Error> Read the 2nd flash BIN file failed\n"));
    }

    msAPI_FCtrl_FileClose(u8HandleNo);

    // Check BIN file header: the first 5 bytes
    if((*((U8 *)_u32DRAMAddr) == 0x09) &&
      (*((U8 *)_u32DRAMAddr+1) == 0x58) &&
      (*((U8 *)_u32DRAMAddr+2) == 0x33) &&
      (*((U8 *)_u32DRAMAddr+3) == 0x69)&&
      (*((U8 *)_u32DRAMAddr+4) == 0x00))
    {
        //USB_DL_DBG(printf("Find the 2nd flash BIN file header\n"));
        return TRUE;
    }
    else
    {
        USB_DL_ASSERT(printf("Error> Read the 2nd flash BIN file header failed\n"));
        return FALSE;
    }
}

#if ENABLE_TTSTEST_FROM_USB
void MW_TTSTestFromUSB_Init(U8 u8USBPortNo, U8 * pu8FileName, U8 * pu16FileStr, U16 u16Length )
{
    u8ReadTxTFlag = TRUE;
    _u8USBPortNo = u8USBPortNo;
    _pu16FileStr = pu16FileStr;
    _u16Length = u16Length;
    memcpy(_pu8FileName, pu8FileName, sizeof(_pu8FileName));
    _bUsbInitialized = FALSE;
}

#endif

//****************************************************************************
/// USB Download Init
/// @param ZUIDrawPercentage IN: UI draw call back function pointer
/// -@see pZUIDrawCB
/// @return void
//****************************************************************************
void MW_UsbDownload_Init(U8 u8USBPortNo, U8 u8FlashID, U32 u32DRAMAddr, U32 u32DRAMLen, U32 u32FlashSize, U8 u8UpgradeMode, U8 u8MemType, U8 * pu8FileName, pZUIDrawCB ZUIDrawPercentage, BOOLEAN bAPBinFlag)
{
    USB_DL_DBG(printf("MW_UsbDownload_Init\n"));

    _u8USBStatus = 0;
    _u8USBPortNo = u8USBPortNo;
    _u8FlashID = u8FlashID;
    _u8MemType = u8MemType;
    _u8UpgradeMode = u8UpgradeMode;
    memcpy(_pu8FileName, pu8FileName, sizeof(_pu8FileName));
    _u32DRAMAddr = u32DRAMAddr;
    _u32DRAMLen = u32DRAMLen;
    _u32FlashSize = u32FlashSize;

    pZUIDrawPercentageCB = ZUIDrawPercentage;

    _bUsbInitialized = FALSE;

    if(bAPBinFlag == TRUE)
    {
        _bAPBinFlag = TRUE;
        _bFlashID1 = FALSE;
        _bFlashID2 = FALSE;
    }
}

//****************************************************************************
/// USB Download Search
/// @param void
/// @return BOOLEAN
/// - TURE : Search donwload file successfully.
/// - FALSE : Search download file failed.
//****************************************************************************
BOOLEAN MW_UsbDownload_Search(void)
{
    U8      u8HandleNo;
    U32     u32TimeStart = msAPI_Timer_GetTime0();

    USB_DL_DBG(printf("MW_UsbDownload_Search\n"));
    MApp_UsbClearWatchDog();

    if(_u8USBPortNo == 0x1)
    {
        while (!MDrv_UsbDeviceConnect())
        {
            U32 u32Duration = msAPI_Timer_DiffTimeFromNow(u32TimeStart);
            MApp_UsbClearWatchDog();
            if (u32Duration > MAX_USB_DETECTION_DURATION)
            {
                USB_DL_ASSERT(printf("Error> USB Download Search: port 1 connection timeout\n"));
                return FALSE;
            }
        }
    }
    else if(_u8USBPortNo == 0x2)
    {
        while (!MDrv_UsbDeviceConnect_Port2())
        {
            U32 u32Duration = msAPI_Timer_DiffTimeFromNow(u32TimeStart);
            MApp_UsbClearWatchDog();
            if (u32Duration > MAX_USB_DETECTION_DURATION)
            {
                USB_DL_ASSERT(printf("Error> USB Download Search: port 2 connection timeout\n"));
                return FALSE;
            }
        }
    }
#if (ENABLE_USB_3)
    else if(_u8USBPortNo == 0x4)
    {
        while (!MDrv_UsbDeviceConnect_Port3())
        {
            U32 u32Duration = msAPI_Timer_DiffTimeFromNow(u32TimeStart);
            MApp_UsbClearWatchDog();
            if (u32Duration > MAX_USB_DETECTION_DURATION)
            {
                USB_DL_ASSERT(printf("Error> USB Download Search: port 3 connection timeout\n"));
                return FALSE;
            }
        }

    }
#endif
#if (ENABLE_USB_4)
    else if(_u8USBPortNo == 0x8)
    {
        while (!MDrv_UsbDeviceConnect_Port4())
        {
            U32 u32Duration = msAPI_Timer_DiffTimeFromNow(u32TimeStart);
            MApp_UsbClearWatchDog();
            if (u32Duration > MAX_USB_DETECTION_DURATION)
            {
                USB_DL_ASSERT(printf("Error> USB Download Search: port 4 connection timeout\n"));
                return FALSE;
            }
        }

    }
#endif
    else
    {
        USB_DL_ASSERT(printf("Error> USB Download Search: port number error\n"));
        return FALSE;
    }

    // Init USB and file system, ...
    MApp_UsbClearWatchDog();

    if (!_MW_UsbDownload_InitFileSystem())
    {
        _MW_UsbDownload_Exit();
        return FALSE;
    }

    // Search files
    MApp_UsbClearWatchDog();

    if(_bAPBinFlag == TRUE)
    {
        if((_MW_UsbDownload_SearchFileInRoot((U8 *)(_pu8FileName), &_fileEntry2) == TRUE)&&(_MW_UsbDownload_CheckHeader() == TRUE))
        {
            _bFlashID2 = TRUE;
        }
        else
        {
            USB_DL_ASSERT(printf("Error> Search %s.bin failed code line=%d\n",_pu8FileName,__LINE__));
        }

        if(! _MW_UsbDownload_SearchFileInRoot((U8 *)(_pu8FileName), &_fileEntry))
        {
            USB_DL_ASSERT(printf("Error> Search %s.bin failed code line=%d\n",_pu8FileName,__LINE__));
            if(! _MW_UsbDownload_SearchFileInRoot((U8 *)(_pu8FileName), &_fileEntry))
            {
                USB_DL_ASSERT(printf("Error> Search %s.bin failed code line=%d\n",_pu8FileName,__LINE__));
                if(_bFlashID2 == TRUE)
                {
                    return TRUE;// Only update BIN file
                }
                else
                {
                    return FALSE;
                }
            }
        }
        else
        {
            _bFlashID1 = TRUE;
        }
    }
    else
    {
        if(! _MW_UsbDownload_SearchFileInRoot((U8 *)(_pu8FileName), &_fileEntry))
        {
            if(! _MW_UsbDownload_SearchFileInRoot((U8 *)(_pu8FileName), &_fileEntry))
            {
                USB_DL_ASSERT(printf("Error> Search %s.bin failed code line=%d\n",_pu8FileName,__LINE__));
                _MW_UsbDownload_Exit();
                return FALSE;
            }
        }
    }

    u8HandleNo = msAPI_FCtrl_FileOpen(&_fileEntry, OPEN_MODE_FOR_READ);
#if ENABLE_TTSTEST_FROM_USB
    if(u8ReadTxTFlag)
    {
        u8ReadTxTFlag = FALSE;
        _u16TestFileSize = msAPI_FCtrl_FileLength(u8HandleNo);
        memset((void*)_PA2VA(DOWNLOAD_BUFFER_ADR_TTSTEST), 0, DOWNLOAD_BUFFER_LEN); //clear this buffer to storage tts test file

        //if tts test txt file size > max size,just read max size
        msAPI_FCtrl_FileRead(u8HandleNo, DOWNLOAD_BUFFER_ADR_TTSTEST, (_u16TestFileSize > _u16Length ? _u16Length : _u16TestFileSize));
        memcpy(_pu16FileStr,(void *)_PA2VA(DOWNLOAD_BUFFER_ADR_TTSTEST),(_u16TestFileSize > _u16Length ? _u16Length : _u16TestFileSize));
    }
#endif
    if(u8HandleNo == FCTRL_INVALID_FILE_HANDLE)
    {
        USB_DL_ASSERT(printf("Error> Open file failed\n"));
        _MW_UsbDownload_Exit();
        return FALSE;
    }

    msAPI_FCtrl_FileClose(u8HandleNo);
    _u8USBStatus=TRUE;

    USB_DL_DBG(printf("USB Download Search: OK\n"));

    #if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)  //
    if(g_eUSBSWUpdateChipType == SWUpdateForMFC)
    {
        printf("MFC image found\n");
    }
    else
    {
         printf("Merged image found\n");
    }
    #endif

    return TRUE;
}


#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)
BOOLEAN MApp_Ursa_SwUpdate_Start(void)
{
    U8 u8Percent;
    //FlashProgErrorType eErrCode;

    if (g_eUSBSWUpdateChipType == SWUpdateForHK)
      return FALSE;

    do
    {
        u8Percent = MApp_MFC_ISP_Program();
    }while ((u8Percent < 0xF0) && (u8Percent != 0));

    if (u8Percent == 0)
    {
        printf("MFC.bin updating Success.\n");
        //sprintf(&(au8String[0]), "%s","Updated sucess!!!!");
        //USB_DL_ASSERT(printf("Updated sucess!!!!\n"));
        msAPI_Timer_Delayms(5000);
        return TRUE;
    }
    else
    {
        printf("MFC.bin updating Fail.\n");
        //sprintf(&(au8String[0]), "%s","Updated error!!!!");
        //MApp_UiMenu_DrawOneLineText(UI_FACTORY_MENU_START_X,UI_POPUP_MSG_WIDTH,UI_FACTORY_BG_COLOR,UI_FACTORY_MENU_START_X+20, UI_FACTORY_MENU_START_Y+120, UI_POPUP_MSG_WIDTH-20, 40, COLOR_RED, 0x000000/*trans*/, EN_ALIGNMENT_CENTER, au8String);
        msAPI_Timer_Delayms(5000);
        return FALSE;
        //eErrCode = (u8Percent -0xF0);
    }
}
#endif

//****************************************************************************
/// USB Download Start
/// @param void
/// @return BOOLEAN
/// - TRUE : USB download succeedfully.
/// - FALSE : USB download failed.
//****************************************************************************
BOOLEAN MW_UsbDownload_Start(void)
{
    USB_DL_DBG(printf("MW_UsbDownload_Start\n"));

    if(_bAPBinFlag == TRUE)
    {
        if((_bFlashID1 == TRUE)&&(_bFlashID2 == TRUE))
        {
            printf("== Case 1 ==\n");
            if (_MW_UsbDownload_Copy(_u32DRAMAddr, _u32DRAMLen, _u32FlashSize))
            {
            #if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)  //
                if (g_eUSBSWUpdateChipType == SWUpdateForMFC)
                {
                    if(MApp_Ursa_SwUpdate_Start())
                    {
                        USB_DL_ASSERT(printf("Error> Update the 1st flash failed\n"));
                    }
                    else
                    {
                        USB_DL_DBG(printf("Update the 1st flash successfully\n"));
                    }
                }
                else
            #endif
                {
                    if(MApp_SwUpdate_Start((EN_SW_UPDATE_MODE)_u8UpgradeMode, FALSE, FALSE, TRUE, _u32DRAMAddr, _u32DownloadSize, _u8MemType, TRUE) == FALSE)
                    {
                        USB_DL_ASSERT(printf("Error> Update the 1st flash failed\n"));
                    }
                    else
                    {
                        USB_DL_DBG(printf("Update the 1st flash successfully\n"));
                    }
                }
            }
            else
            {
                USB_DL_ASSERT(printf("Error> Copy Merge.bin failed\n"));
            }

            _MW_UsbDownload_CheckHeader();
            _MW_UsbDownload_Exit();
            return MApp_SwUpdate_Start((EN_SW_UPDATE_MODE)_u8UpgradeMode, TRUE, TRUE, FALSE, _u32DRAMAddr, _u32DownloadSize, _u8MemType, TRUE);
        }
        else if((_bFlashID1 == TRUE)&&(_bFlashID2 == FALSE))
        {
            printf("== Case 2 ==\n");
            if (_MW_UsbDownload_Copy(_u32DRAMAddr, _u32DRAMLen, _u32FlashSize))
            {
                _MW_UsbDownload_Exit();
                return MApp_SwUpdate_Start((EN_SW_UPDATE_MODE)_u8UpgradeMode, FALSE, FALSE, FALSE, _u32DRAMAddr, _u32DownloadSize, _u8MemType, TRUE);
            }
            else
            {
                USB_DL_ASSERT(printf("Error> Copy Merge.bin failed\n"));
            }
        }
        else if((_bFlashID1 == FALSE)&&(_bFlashID2 == TRUE))
        {
            printf("== Case 3 ==\n");
            if(_MW_UsbDownload_CheckHeader())
            {
                _MW_UsbDownload_Exit();
                return MApp_SwUpdate_Start((EN_SW_UPDATE_MODE)_u8UpgradeMode, TRUE, TRUE, FALSE, _u32DRAMAddr, _u32DownloadSize, _u8MemType, TRUE);
            }
            else
            {
                USB_DL_ASSERT(printf("Error> Copy Merge2.bin failed\n"));
            }
        }
    }
    else
    {
        printf("== Case 4 ==\n");
        if (_MW_UsbDownload_Copy(_u32DRAMAddr, _u32DRAMLen, _u32FlashSize))
        {
            _MW_UsbDownload_Exit();
        #if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)  //
            if (g_eUSBSWUpdateChipType == SWUpdateForMFC)
            {
                if(MApp_Ursa_SwUpdate_Start())
                {
                    USB_DL_ASSERT(printf("Error> Update the 1st flash failed\n"));
                    return TRUE;
                }
                else
                {
                    USB_DL_DBG(printf("Update the 1st flash successfully\n"));
                    return FALSE;
                }
            }
            else
        #endif
            {
                BOOL bSwUpdateResult = FALSE;

            /*
                PRINT_CURRENT_LINE();
                printf("_u8UpgradeMode=0x%X\n", _u8UpgradeMode);
                printf("_u8FlashID=0x%X\n", _u8FlashID);
                printf("_u32DRAMAddr=0x%X\n", _u32DRAMAddr);
                printf("_u32DownloadSize=0x%X\n", _u32DownloadSize);
                printf("_u8MemType=0x%X\n", _u8MemType);
             */
                bSwUpdateResult = MApp_SwUpdate_Start((EN_SW_UPDATE_MODE)_u8UpgradeMode, _u8FlashID, FALSE, FALSE, _u32DRAMAddr, _u32DownloadSize, _u8MemType, FALSE);

                printf("bSwUpdateResult=%u\n", bSwUpdateResult);

                return bSwUpdateResult;
            }
        }
        else
        {
            printf("_MW_UsbDownload_Copy() faild!\n");
        }
    }

    return FALSE;
}

BOOLEAN MW_UsbDownload_SetDownloadType(DownloadCheckEnumType DownloadCheckType)
{
    _DownloadCheckType = DownloadCheckType;
    return TRUE;
}
DownloadErrorEnumType MW_UsbDownload_GetErrorType(void)
{
    return _DownloadErrorType;
}
#if (ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION == ENABLE || ENABLE_UPGRADE_CIPLUSKEY_BY_USB == ENABLE || ENABLE_UPGRADE_HDCPKEY_BY_USB == ENABLE   || ENABLE_KEY_LOGGER ||ENABLE_TCON_BIN_IN_DB)
void MApp_UsbSaveData_SetPort(U8 u8USBPortNo)
{
    _u8USBPortNo = u8USBPortNo;
}

U8 MApp_UsbSaveData_OpenNewFileForWrite(U16* pString,U8 charLen)
{
    return msAPI_FCtrl_FileCreate(_u8USBEnvironmentID ,pString, charLen, CREATE_MODE_NEW);
}

BOOLEAN MApp_UsbSaveData_SearchFileInRoot(U8* pu8FileName, FileEntry* pFileEntry)
{
    return _MW_UsbDownload_SearchFileInRoot(pu8FileName, pFileEntry);
}

BOOLEAN MApp_UsbSaveData_InitFileSystem(void)
{
    return _MW_UsbDownload_InitFileSystem();
}

void MApp_UsbSaveData_Exit(void)
{
    _MW_UsbDownload_Exit();
}
#endif

#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB || ENABLE_UPGRADE_HDCPKEY_BY_USB)
void MW_UsbDownload_SetUSBPortNo(U8 u8PortNo)
{
    _u8USBPortNo = u8PortNo;
}
#endif

#undef MW_USBDOWNLOAD_C

