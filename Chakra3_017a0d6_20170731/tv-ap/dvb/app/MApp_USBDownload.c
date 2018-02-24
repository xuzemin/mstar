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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_USBDOWNLOAD_C

/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// Global Layer
#include "MsCommon.h"
#include "sysinfo.h"
#include "imginfo.h"

#include "debug.h"

// Driver Layer
#include "drvTVEncoder.h"
#include "drvMIU.h"
#include "drvCPU.h"
#include "drvSERFLASH.h"
#include "SysInit.h"
#include "drvUSB.h"

#include "mw_usbdownload.h"

// API Layer
#include "apiXC.h"
#include "apiXC_Sys.h"
#include "msAPI_Memory.h"
#include "msAPI_BDMA.h"
#include "msAPI_audio.h"
#include "msAPI_VD.h"

// AP Layer
#include "MApp_USBDownload.h"
#include "mapp_swupdate.h"
#if (ENABLE_MFC_6M20)
#include "drvUrsaMFCAPI.h"
#endif
#if ENABLE_MFC_6M30
#include "drvUrsa6M30.h"
#endif
#if(ENABLE_6M40_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#endif
#include "MApp_ChannelChange.h"
#include "MApp_Scaler.h"
#include "MApp_PCMode.h"

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)
#include "MApp_Isp.h"
#include "Utl.h"
#define SW_NAME_MFC                "MFC.BIN"
#endif

#if ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN
// API Layer
#include "msAPI_FCtrl.h"
#include "MApp_FileBrowser.h"
#include "msAPI_FSCommon.h"

// MW Layer
#include "string.h"
#include "MApp_MassStorage.h"
#include "msAPI_Timer.h"
#if ENABLE_SECURITY_R2_HDCP22
#include "msAPI_SecurityR2.h"
#endif
#endif

extern void MApp_InputSource_ChangeVideoSource( INPUT_SOURCE_TYPE_t enInputSourceType );

BOOLEAN MDrv_UsbDeviceConnect(void);

// Progress bar start and end positions
#ifdef SUPPORT_AP_BIN_IN_FLASH_2
// Download two images into different flash
U8 USBUpgrade_Percent[] =
{
    // Compare: 0 ~ 10
    0,
    // Erase: 10 ~ 25
    10,
    // Write: 25 ~ 40
    25,
    // Verify: 40 ~ 50
    40,
    50,
     // Compare: 50 ~ 60
    50,
    // Erase: 60 ~ 75
    60,
    // Write: 75 ~ 90
    75,
    // Verify: 90 ~ 100
    90,
    100
};
#else
// Single image (Boot or app)
U8 USBUpgrade_Percent[] =
{
    // Check CMAC: 0 ~ 10
    0,
    // Compare: 10 ~ 20
    10,
    // Erase: 20 ~ 50
    20,
    // Write: 50 ~ 80
    50,
    // Verify: 80 ~ 100
    80,
    100
};
#endif

// Below functions are used by swupdate library; do not remove them.
void MApp_UsbClearWatchDog(void)
{
    MDrv_Sys_ClearWatchDog();
}

void MApp_UsbEnableWatchDog(void)
{
    MDrv_Sys_EnableWatchDog();
}

void MApp_UsbSetWatchDogTimer(U8 u8sec)
{
    MDrv_Sys_SetWatchDogTimer(u8sec);
}

void MApp_UsbBDMA_Copy(U32 u32Srcaddr, U32 u32Dstaddr, U32 u32Len, U8 eType)
{
    MApi_BDMA_Copy(u32Srcaddr, u32Dstaddr, u32Len, (MEMCOPYTYPE)eType);
}

U32 MApp_UsbVA2PA(U32 u32x)
{
    return _VA2PA(u32x);
}

U32 MApp_UsbPA2VA(U32 u32x)
{
    return _PA2VA(u32x);
}

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)  //
BOOLEAN MApp_UsbDownload_USB_UpDate_SetMFCPort(void)
{
    printf("==USBProgMFC==\n");
    g_eUSBSWUpdateChipType = SWUpdateForMFC;
    return TRUE;
}
BOOLEAN MApp_UsbDownload_USB_UpDate_SetHKPort(void)
{
    printf("==USBProgHK==\n");
    g_eUSBSWUpdateChipType = SWUpdateForHK;
    return TRUE;
}

USBSWUpdateChipType MApp_UsbDownload_USB_Update_GetPort(void)
{
    return g_eUSBSWUpdateChipType;
}

#endif

//****************************************************************************
/// USB Download port check
/// @paramvoid
/// @return portNo for USB download init 0xFF is no device
//****************************************************************************
U8 MApp_UsbDownloadCheckPort(void)
{
    U8 u8PortEnStatus = 0;
    U8 u8PortNo = INVALID_USB_PORT;

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();


    if( (u8PortEnStatus & BIT0) == BIT0 )
    {

        if (!MDrv_UsbDeviceConnect())
       {
           MsOS_DelayTask(1000);
           if (!MDrv_UsbDeviceConnect())
           {
               if((u8PortEnStatus & BIT1) != BIT1)
                   return u8PortNo;
           }
           else
           {
               u8PortNo = BIT0;
           }
       }
       else
       {
           u8PortNo = BIT0;
       }
    }


    if((u8PortNo== INVALID_USB_PORT) &&(u8PortEnStatus & BIT1) == BIT1)  //USB port 1 is not connectted check port2
    {
        if (!MDrv_UsbDeviceConnect_Port2())
        {
            MsOS_DelayTask(1000);
            if (!MDrv_UsbDeviceConnect_Port2())
            {
                return u8PortNo;
            }
            else
            {
                u8PortNo = BIT1;
            }

        }
        else
        {
            u8PortNo = BIT1;
        }

    }


    return u8PortNo;

}

//****************************************************************************
/// USB Download Init
/// @param u8PortNo IN: USB port number
/// @param ZUIDrawPercentage IN: UI draw call back function pointer
/// -@see pZUIDrawCB
/// @return void
//****************************************************************************
void MApp_UsbDownload_Init(U8 u8PortNo, pZUIDrawCB ZUIDrawPercentage)
{
// Choose SW Update Mode: full burn or partial
#define SW_UPDATE_MODE          SW_UPDATE_MODE_PARTIAL //SW_UPDATE_MODE_FULL

#define DOWNLOAD_BUFFER_ADR_USB   ((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR))
#define DOWNLOAD_BUFFER_LEN_USB   DOWNLOAD_BUFFER_LEN
#define DOWNLOAD_BUFFER_TYPE_USB  MIU_SDRAM2SDRAM

#ifdef SUPPORT_AP_BIN_IN_FLASH_2
    BOOLEAN bSupportAPBINInFlash2 = TRUE;
#else
    BOOLEAN bSupportAPBINInFlash2 = FALSE;
#endif

    U8      u8FlashID = 0x0; // 0x0: flash ID0, 0x1: flash ID1
    U8      pu8FileName[20] = "MP332.BIN";//"MERGE.BIN"; //gchen @ 20190130
    U32     u32FlashSize = 0;


    printf("MApp_UsbDownload_Init()\n");


#if 0
    U8      u8MIUProtectAeon_ID[2];
    U32     u32BaseAddr = 0;

    u32BaseAddr = MDrv_COPRO_GetBase();
    if(u32BaseAddr == 0xBF800000) //HK: MIPS
    {
        u8MIUProtectAeon_ID[0] = MIU_CLI_AEON_RW;
    }
    else if(u32BaseAddr == 0xA0000000) //HK: AEON
    {
        u8MIUProtectAeon_ID[0] = 0x05;
    }
    else
    {
        printf("Error> Code base error\n");
    }

    u8MIUProtectAeon_ID[1] = MIU_CLI_DMA_R;
    MDrv_MIU_Protect(MIU_PROTECT_IDX_1, &u8MIUProtectAeon_ID[0], (U32)DOWNLOAD_BUFFER_ADR_USB, (U32)(DOWNLOAD_BUFFER_ADR_USB + DOWNLOAD_BUFFER_LEN_USB-1), ENABLE);
#endif

  #if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)  //
    //#define SW_NAME_MFC              "MFC.BIN"            // Capital
    if (g_eUSBSWUpdateChipType == SWUpdateForMFC)
    {
        memcpy(pu8FileName, "MFC.BIN   ", 7);
        pu8FileName[7] = '\0';
    }
  #endif

    #if (!BLOADER)
    /*
    *  Disable Some HW Engines for Downloading
    */
    {
        MS_VE_Output_Ctrl OutputCtrl;
        // disable VE
        OutputCtrl.bEnable = FALSE;
        msAPI_VE_SetOutputCtrl(&OutputCtrl);

        // Enable Blue&black screen
        msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, MAIN_WINDOW);


        //MW_AUD_SetSoundMute(SOUND_MUTE_ALL, E_MUTE_ON);

        if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
        }
        else
        {
            MApp_ChannelChange_DisableAV(MAIN_WINDOW);
        }

        // disable vd
        msAPI_AVD_Exit();
    }
    #endif

    if(!MDrv_SERFLASH_DetectSize(&u32FlashSize))
    {
        MS_DEBUG_MSG(printf("Error> Detect Flash Size Failed !!\n"));
    }
    else
    {
  #if (ENABLE_MFC_6M20||ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)  //
       if (g_eUSBSWUpdateChipType == SWUpdateForHK)
  #endif
        {
             u32FlashSize = u32FlashSize - 0x20000; // Data Base use the last 2 banks
        }
    }

    MW_UsbDownload_Init(u8PortNo, u8FlashID, (U32)DOWNLOAD_BUFFER_ADR_USB, (U32)DOWNLOAD_BUFFER_LEN_USB, u32FlashSize, (U8)SW_UPDATE_MODE, (U8)DOWNLOAD_BUFFER_TYPE_USB, pu8FileName, ZUIDrawPercentage, bSupportAPBINInFlash2);
}

void MApp_UsbDownload_Exit(void)
{
    MS_VE_Output_Ctrl OutputCtrl;
    // enable VE
    OutputCtrl.bEnable = ENABLE;
    msAPI_VE_SetOutputCtrl(&OutputCtrl);

    // enable vd
    if(IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        MApp_InputSource_ChangeVideoSource(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
    }

    if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
    }
    else
    {
        MApp_Scaler_Setting_SetVDScale( ST_VIDEO.eAspectRatio, MAIN_WINDOW );
        MApp_PCMode_Reset(MAIN_WINDOW);
    }
}

#if (ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN)
extern U8 MDrv_USBGetPortEnableStatus(void);
extern BOOLEAN MDrv_UsbDeviceConnect(void);
extern 	BOOLEAN MDrv_UsbDeviceConnect_Port2(void);

U8 MApp_CheckUsbPortStatus(void)
{
    U8 u8PortEnStatus;
    U8 u8UsbPortNo = 0;
    BOOL bUsbStatusIsGood = FALSE;
    U32 u32Time1;


    printf(" MApp_UsbDownloadBin_CheckUsbStatus()\n");

    // Check USB status
    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    printf("  u8PortEnStatus=%u\n", u8PortEnStatus);


    // Check port 1
    if( (u8PortEnStatus & BIT0) == BIT0 )
    {
        u32Time1 = MsOS_GetSystemTime();
        while( (MsOS_Timer_DiffTimeFromNow(u32Time1) < 1000) )
        {
            if( MDrv_UsbDeviceConnect() )
            {
                u8UsbPortNo = BIT0;
                bUsbStatusIsGood = TRUE;
                break;
            }
        }
    }

    if( bUsbStatusIsGood )
    {
        return u8UsbPortNo;
    }
#if (ENABLE_USB_2)
    if( (u8PortEnStatus & BIT1) == BIT1 )
    {
        u32Time1 = MsOS_GetSystemTime();
        while( (MsOS_Timer_DiffTimeFromNow(u32Time1) < 1000) )
        {
            if( MDrv_UsbDeviceConnect_Port2() )
            {
                u8UsbPortNo = BIT1;
                bUsbStatusIsGood = TRUE;
                break;
            }
        }
    }

    if( bUsbStatusIsGood )
    {
        return u8UsbPortNo;
    }
    #endif

    return 0;
}
#endif

#if ENABLE_KEY_LOGGER
BOOLEAN MApp_Usb_InitForWrite(void)
{
    U8 u8PortEnStatus = 0;

    #if ENABLE_USB_2    //Dual usb
    if ((MDrv_UsbDeviceConnect() == FALSE) && (MDrv_UsbDeviceConnect_Port2() == FALSE))
    #elif ENABLE_USB    //Single usb
    if (MDrv_UsbDeviceConnect() == FALSE)
    #else   //No usb
    #endif
    {
        printf("\n init USB__fail \n");
        return FALSE;
    }

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();

    if((u8PortEnStatus & BIT0) == BIT0)
    {
        MApp_UsbSaveData_SetPort(BIT0);
    }
    else if((u8PortEnStatus & BIT1) == BIT1)
    {
        MApp_UsbSaveData_SetPort(BIT1);
    }
    else
    {
        printf("Error> Unknown USB port\n");
        return FALSE;
    }
    if (!MApp_UsbSaveData_InitFileSystem())
    {
        MApp_UsbSaveData_Exit();
        printf("Exit");
        return FALSE;
    }
    return TRUE;
}
#endif

#if ENABLE_USB_DOWNLOAD_HDCPKEY22_BIN

#define  HDCP22_FOLDER_NAME_LEN 11
#define  STRING_BUFF_LENGTH  127
extern void MApp_DB_SaveHDCP22_KEY(U8 *au8AesKey, U8 *au8Hdcp22Key);
extern void void MApp_DB_EraseHDCPBank(void);
void msAPI_PrintfCharAarray(U16 *u16paarry,U8 u8len)
{
    int i = 0 ;
    printf("\n");
    for(i=0;i<u8len;i++)
    {
        if(u16paarry[i]==NULL)
        break ;

        printf("%c",u16paarry[i]);
    }
    printf("\n");
}

U8  msAPI_SearchBinFileFromCurrentDirectory(FileEntry *pstFileEntry, U16 *u16FileName,U8 u8Length)
{

       DirEntryStruct *pCurrentDirEntry   = NULL;
     //  U16 u16TempFileName[STRING_BUFFER_LENGTH]={'\0'};
       U8 u8PltFileNameLen =0;


       memset(pstFileEntry,0,sizeof(FileEntry));
       memset(&u16FileName[0],0,sizeof(U16)*u8Length);

       if(!MApp_FileBrowser_ToFirstEntryInCurrentDirectory())
           {
           printf("FileBrowser_ToFirstEntryInCurrentDirectory fail!\n");
           return FALSE;
           }
       else// success
           {
            pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
           }


       while(pCurrentDirEntry!=NULL)
       {
           MApp_FileBrowser_GetCurrentFileEntry(pstFileEntry);

           if(pstFileEntry->EntryType!=ENTRY_TYPE_DIR_DOT\
              &&pstFileEntry->EntryType!=ENTRY_TYPE_DIR_DOTDOT\
              &&pstFileEntry->EntryType!=ENTRY_TYPE_NULL)
            {
                 u8PltFileNameLen = MApp_FileBrowser_GetLongFileNameByFileEntry(pstFileEntry,(U32)(u16FileName),u8Length);
                 msAPI_PrintfCharAarray(u16FileName,u8Length);
                 printf("u8PltFileNameLen =%d\n",u8PltFileNameLen);

                 if(u16FileName[0]=='h'&&\
                    u16FileName[1]=='d'&&\
                    u16FileName[2]=='c'&&\
                    u16FileName[3]=='p'&&\
                    u16FileName[4]=='2'&&\
                    u16FileName[5]=='2'&&\
                    u16FileName[6]=='m'&&\
                    u16FileName[7]=='s'&&\
                    u16FileName[8]=='d'&&\
                    u16FileName[9]=='_')
                    {
                        printf("\n !!!!!find it!!!!\n");
                        return  u8PltFileNameLen;

                    }

            }

           pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
       }

     printf("!!!!!!No Find it!!!!!!\n");
     return 0;


}


//******************************************************************************
/// Change to a specific directory
/// @param  pu8DstPathBuf \b IN Specify the path
/// @param  pu16DstPathLen \b IN Specify the path length in string
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_USB_ChangeToSpecificDirectory(U16 *pu16DstPath, U16 pu16DstPathLen)
{
    BOOLEAN bRet = FALSE;
    U16 i, u16DirNameLen;
    U16* pu16TempDstPath;
    U16 pu16FolderName[128]={0};

    FileEntry stDirEntry;
    memset(&stDirEntry, 0, sizeof(FileEntry));

    if(MApp_FileBrowser_ChangeToRootDirectory() == FALSE)
    {
        printf("Change to Root fail\n");
        goto MApp_MPlayer_ChangeToSpecificDirectory_END;
    }

    i=0;
    u16DirNameLen=0;

    if(pu16DstPath[0] == '\\')
    {
        if(pu16DstPath[1] == '\0')
        {
            //root
        }
        else
        {
            i=1;
            pu16TempDstPath = &pu16DstPath[i];
            while(i < pu16DstPathLen)
            {
                if(pu16DstPath[i] == '\\' || pu16DstPath[i] == '\0')
                {
                    if(u16DirNameLen != 0)
                    {
                        memcpy(pu16FolderName, pu16TempDstPath, u16DirNameLen*2);
                        pu16FolderName[u16DirNameLen] = '\0';

                        //open new folder and enter
                        if(FALSE == MApp_FileBrowser_OpenNewFolder_And_GetFileEntry(pu16FolderName,u16DirNameLen, &stDirEntry))
                        {
                            printf("ERROR MApp_FileBrowser_OpenNewFolder_And_GetFileEntry Fail 1\n");
                            goto MApp_MPlayer_ChangeToSpecificDirectory_END;
                        }

                        if(FALSE == MApp_FileBrowser_DirectoryChange(&stDirEntry))
                        {
                            printf("ERROR MApp_FileBrowser_DirectoryChange Fail 1\n");
                            goto MApp_MPlayer_ChangeToSpecificDirectory_END;
                        }

                        if(pu16DstPath[i] == '\0')
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }

                    i++;
                    u16DirNameLen=0;
                    pu16TempDstPath = &pu16DstPath[i];
                }
                else
                {
                    i++;
                    u16DirNameLen++;
                }
            }
        }
    }

    bRet = TRUE;
MApp_MPlayer_ChangeToSpecificDirectory_END:

    return bRet;
}
BOOLEAN msAPI_WriteHdcp22keyToFlash(FileEntry * pstFileEntry)
{

   U8  u8HandleNo =0;
   U8 u8hdcp22key[HDCP22_KEY_SIZE]={'\0'};


   printf("====>%ld,%ld\n",pstFileEntry->EntryFileLength,pstFileEntry->FileLength);


  u8HandleNo = msAPI_FCtrl_FileOpen(pstFileEntry, OPEN_MODE_FOR_READ);


   if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
   {
      msAPI_Timer_ResetWDT();
      memset(u8hdcp22key,0,HDCP22_KEY_SIZE);
      msAPI_FCtrl_FileRead(u8HandleNo, HDCP_KEY_BUFFER_ADR, HDCP22_KEY_SIZE);
      memcpy(u8hdcp22key,(void *)_PA2VA(((HDCP_KEY_BUFFER_MEMORY_TYPE & MIU1) ? (HDCP_KEY_BUFFER_ADR | MIU_INTERVAL) : (HDCP_KEY_BUFFER_ADR))),HDCP22_KEY_SIZE);

      #if (HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB)
         MApp_DB_EraseHDCPBank();
         MApp_DB_SaveHDCP22_KEY(NULL,u8hdcp22key);
      #endif
      printf("\n hdcp2.2 key write to flash finshed!!\n");
      msAPI_FCtrl_FileClose(u8HandleNo);
      return TRUE;
   }
  else
  {
       printf("\n FCTRL_INVALID_FILE_HANDLE\n");
       return FALSE;
  }

}

EN_TYPE_UPGRADE_HDCP22KEY  MApp_UpgardeHdcp22keyFromUsb(void)
{
    U16 u16SourceDir[] = {'\\','h','d','c','p','2','2','m','s','d','\0'};
    U16 u16StringBufferTemp[STRING_BUFF_LENGTH]={'\0'};
    BOOLEAN bret = 0 ;
    FileEntry   stBinFileEntry  ;

     memset(&stBinFileEntry,0,sizeof(FileEntry));
//=================================================
    // 1 . Check USB
	if(0==MApp_CheckUsbPortStatus())
	{
		printf("NO USB DEVICE!!!\n");
		return E_UPGRADE_HDCP22_NO_USB;
	}
	else
	{

		printf(" CHECK USB DEVICE  OK!!!\n");
	}

    if (MApp_MassStorage_DeviceChangeStatusCheck())
    {
        MApp_MassStorage_DeviceStatusCheck();
    }

    // 2.  create FileBrowser handle

    U8 u8CurFileBrowserHandle = INVALID_BROWSER_HANDLE;
    U8 u8PreFileBrwoserHandle = INVALID_BROWSER_HANDLE;
    u8PreFileBrwoserHandle = MApp_FileBrowser_GetEnvironment();
    u8CurFileBrowserHandle = MApp_FileBrowser_Create(0); //u8ConnectDrive是你要連的USB drive index
    if(u8CurFileBrowserHandle == INVALID_BROWSER_HANDLE)
    {
       printf(" FileBroswser handle create failed\n");
       return E_UPGRADE_HDCP22_FS_INIT_ERROR;
    }
    MApp_FileBrowser_SetEnvironment(u8CurFileBrowserHandle);

    //goto path

    MApp_USB_ChangeToSpecificDirectory((U16 *)u16SourceDir,HDCP22_FOLDER_NAME_LEN);// -> ?複製Chakra3 _MApp_MPlayer_ChangeToSpecificDirectory並自行改名

    //  search index file (>>get FileEntry)
    msAPI_SearchBinFileFromCurrentDirectory(&stBinFileEntry,u16StringBufferTemp,STRING_BUFF_LENGTH);


    //   upgrade bin file

    bret =   msAPI_WriteHdcp22keyToFlash(&stBinFileEntry);

    if(bret == 0)
    {
       return E_UPGRADE_HDCP22_WRITE_BIN_ERROR;
    }

    //  delete bin file

    bret = MApp_FileBrowser_DeleteFileByFileEntry(&stBinFileEntry);

    if(bret == 0)
    {
       return E_UPGRADE_HDCP22_DELETE_BIN_ERROR;
    }

    printf("delay 1s for delete bin file... \n");

    msAPI_Timer_Delayms(1000);

  //FileBrowser handle用完?得?回去
    if(u8CurFileBrowserHandle != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_SetEnvironment(u8PreFileBrwoserHandle);
        MApp_FileBrowser_Destroy(u8CurFileBrowserHandle);
    }

    printf("\n>>>>>>>>>>UPGRADE HDCP2.2 KEY SUCCESSED<<<<<<<<<<<<\n");

    return E_UPGRADE_HDCP22_SUCCESS;

}
#endif

#undef MAPP_USBDOWNLOAD_C

