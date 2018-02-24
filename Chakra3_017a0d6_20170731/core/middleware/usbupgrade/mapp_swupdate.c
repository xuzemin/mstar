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
#define MAPP_SWUPDATE_C

/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <stdio.h>
#include <string.h>

//#include "MsP4Identifier.h"
#include "MsTypes.h"

// Global Layer
#include "Utl.h"
#include "imginfo.h"

// Driver Layer

// API Layer
#include "msAPI_Memory.h"

// MW Layer
#define ENABLE_CMAC_CHECK       0     //1: enable CMAC check. NOTE: Makefile also needs to be modified to add CMAC 16 bytes at the end of MERGE.bin.
#include "mw_usb_sz.h"
#include "mw_usbdownload.h"
#if ENABLE_CMAC_CHECK
#include "mw_usbcmac.h"
#endif

// APP Layer
#include "mapp_swupdate.h"
//@@debug #include "mw_usbu_ver.h"

#include "SysInit_Common.h"

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
// Debug
#if(CHAKRA3_AUTO_TEST)
    #define BURN_DBG(x)             x
#else
    #define BURN_DBG(x)
#endif

#define APD_DBG(x)              //x   // Auto partial download

#define MAX_FLASH_SIZE          0x1000000               //SIZE_16MB
#define DOWNLOAD_WIN1_LEN       0x1000                  // 4K
#define DOWNLOAD_VERIFY_LEN     DOWNLOAD_WIN1_LEN/2     // 2K

#define CLEAN                   0
#define DIRTY                   1

#define SAME_IMAGE              0
#define DIFFERENT_IMAGE         1

// Partial update unit: depending on max flash block erase size and min bootloader size.
// Must be 64KB because that max block erase size is 64KB now and min bootloader size is 64KB
#define SW_UPDATE_BLOCK_SIZE    0x10000    //SIZE_64KB

#define MEMBER_OFFSET(struct_name, member_name) ( (U16) &(((struct_name *)0)->member_name) )                     // 16-bit Offset
#define EEPROM_OFFSET(member_name)              (RM_ADDR_DOWNLOAD+MEMBER_OFFSET(ST_DOWNLOAD_INFO, member_name))     // ST_DOWNLOAD_INFO member offset on EEPROM

#define FLASH_ID0   0x0
#define FLASH_ID1   0x1

//typedef unsigned char               MS_BOOL;
//typedef unsigned char               MS_U8;                              // 1 byte
//typedef unsigned long               MS_U32;                             // 4 bytes
/******************************************************************************/
/*                          Private Variables                                 */
/******************************************************************************/
static U8 _u8BarIndex;
static U8 *_pau8CurBar;
static U8 _u8MemCopyType;
//static U32 _u32BufStartAddr;

// An update flag (one bit) that represents a block need update (value 1) or not (value 0)
// Max flash size is 16MB
static U8 _au8DirtyBlock[MAX_FLASH_SIZE/SW_UPDATE_BLOCK_SIZE] = {0};
static BOOLEAN _bDownloadType;
static BOOLEAN _bAPBinFlag;

// Progress bar
static U8 _u8CurPercent;
static U8 _u8PercentStart;
static U8 _u8PercentEnd;
static U32 _u32ProgressMaxSize;

#if 0
static MSIF_Version _mw_swupdate_version = {
       .MW = { MW_USBU_VER },
};
#endif

/******************************************************************************/
/*                          External Variables                                */
/******************************************************************************/
extern pZUIDrawCB pZUIDrawPercentageCB;
extern U8 USBUpgrade_Percent[];
extern U32 u32ImgInfoOffset;

/******************************************************************************/
/*                           Public Function                                  */
/******************************************************************************/
BOOLEAN MApp_SwUpdate_Start(EN_SW_UPDATE_MODE u8UpdateMode, BOOLEAN allowTwoFlashMode, BOOLEAN bDownloadType, BOOLEAN bSecondRun, U32 u32DramStartAddr, U32 u32FileSize, U8 u8MemType, BOOLEAN bAPBinFlag);
void MDrv_Sys_WholeChipReset( void );

/******************************************************************************/
/*                          Private Function                                  */
/******************************************************************************/
static void _MApp_SwUpdate_SetAllDirtyBlocks(U8 u8Flag);
static void _MApp_SwUpdate_SetDirtyBlock(U16 u16BlockNo, U8 u8Flag);
static BOOLEAN _MApp_SwUpdate_IsDirtyBlock(U16 u16BlockNo);
static void _MApp_SwUpdate_ShowError(const S8 *pMsg);
static BOOLEAN _MApp_SwUpdate_BurnData(EN_SW_UPDATE_MODE u8UpdateMode, U32 u32DramStartAddr, U32 u32FlashStartAddr, U32 u32DataSize);
static BOOLEAN _MApp_SwUpdate_EraseFlash(U32 u32FlashStartAddr, U32 u32DataSize);
static BOOLEAN _MApp_SwUpdate_WriteFlash(U32 u32SrcAddr, U32 u32DstAddr, U32 u32DataSize);
static BOOLEAN _MApp_SwUpdate_VerifyFlash(U32 u32SrcAddr, U32 u32FlashAddr, U32 u32DataSize);
static U8 _MApp_SwUpdate_CompareImage(EN_SW_UPDATE_MODE u8UpdateMode, U32 u32SrcAddr, U32 u32FlashAddr, U32 u32DataSize);
static void _MApp_SwUpdate_ProgressBar_ShowByPercent( U8 u8Percent );
static void _MApp_SwUpdate_ProgressBar_ShowByValue( U32 u32Value );
static void _MApp_SwUpdate_NextBarPos0(U32 u32Size);
static void _MApp_SwUpdate_NextBarPos1(U32 u32Size);
static void _MApp_SwUpdate_ProgressBar_Init( U8 u8PercentStart, U8 u8PercentEnd, U32 u32Size );

/******************************************************************************/
/*                          External Function                                 */
/******************************************************************************/
extern void MApp_UsbClearWatchDog(void);
extern void MApp_UsbEnableWatchDog(void);
extern void MApp_UsbSetWatchDogTimer(U8 u8sec);
extern void MApp_UsbBDMA_Copy(U32 u32Srcaddr, U32 u32Dstaddr, U32 u32Len, U8 eType);
extern U32 MApp_UsbVA2PA(U32 u32x);
extern U32 MApp_UsbPA2VA(U32 u32x);
extern U32 msAPI_Timer_GetTime0(void);
extern U32 msAPI_Timer_DiffTimeFromNow(U32 u32TaskTimer);
extern void msAPI_Timer_Delayms(U32 u32DelayTime);
extern MS_BOOL MDrv_FLASH_WriteProtect(MS_BOOL bEnable);
extern MS_BOOL MDrv_FLASH_AddressErase(MS_U32 u32StartAddr, MS_U32 u32Size, MS_U8 u8Wait);
extern MS_BOOL MDrv_FLASH_Read(MS_U32 u32addr, MS_U32 u32size, MS_U8 *pdat);
extern MS_BOOL MDrv_FLASH_Write(MS_U32 u32addr, MS_U32 u32size, MS_U8 *pdat);
extern BOOLEAN msFlash_ChipSelect(U8 u8FlashID);

/******************************************************************************/
/*                               Functions                                    */
/******************************************************************************/
/******************************************************************************
 *@brief  : Get library version
 *@param    ppVersion  : [OUT]  MSIF_Version
 *@return : status
/// - 1: success
/// - 0: false
 ******************************************************************************/

#if 0
BOOLEAN MApp_SwUpdate_GetLibVer(const MSIF_Version **ppVersion)
{
    if (!ppVersion)
    {
        return false;
    }

    *ppVersion = &_mw_swupdate_version;

    return true ;
}
#endif

static void _MApp_SwUpdate_SetAllDirtyBlocks(U8 u8Flag)
{
    if (u8Flag == 0)
    {
        memset(_au8DirtyBlock, 0, sizeof(_au8DirtyBlock));
    }
    else
    {
        memset(_au8DirtyBlock, 0xFF, sizeof(_au8DirtyBlock));
    }
}

static void _MApp_SwUpdate_SetDirtyBlock(U16 u16BlockNo, U8 u8Flag)
{
    U8  u8Mask;

    //BURN_DBG( printf( "_MApp_SwUpdate_SetDirtyBlock(u16BlockNo=%u, u8Flag=%u)\n", u16BlockNo, u8Flag ) );

    u8Mask = ( 1 << (U8)(u16BlockNo % 8) );
    _au8DirtyBlock[u16BlockNo / 8] &= (~u8Mask);

    if (u8Flag != 0)
    {
        _au8DirtyBlock[u16BlockNo / 8] |= u8Mask;
    }
}

static BOOLEAN _MApp_SwUpdate_IsDirtyBlock(U16 u16BlockNo)
{
    U8  u8Flag;

    u8Flag = _au8DirtyBlock[u16BlockNo / 8] >> (U8)(u16BlockNo % 8);
    u8Flag = u8Flag & 1;
    return (u8Flag == DIRTY);
}

static void _MApp_SwUpdate_ShowError(const S8 *pMsg)
{
    printf("\n%s\n", pMsg);
}

static BOOLEAN _MApp_SwUpdate_BurnData(EN_SW_UPDATE_MODE u8UpdateMode, U32 u32DramStartAddr, U32 u32FlashStartAddr, U32 u32DataSize)
{
    BURN_DBG( printf( "_MApp_SwUpdate_BurnData()\n" ) );

    if (u32DataSize == 0)
    {
        return FALSE;
    }

    // Set dirty blocks
    if (SAME_IMAGE == _MApp_SwUpdate_CompareImage(u8UpdateMode, u32DramStartAddr, u32FlashStartAddr, u32DataSize))
    {
        return TRUE;
    }

    if (!MDrv_FLASH_WriteProtect(DISABLE))
    {
        printf("Failed to disable flash write protection\n");
        return FALSE;
    }

    if (_MApp_SwUpdate_EraseFlash(u32FlashStartAddr, u32DataSize))
    {
        if (_MApp_SwUpdate_WriteFlash(u32DramStartAddr, u32FlashStartAddr, u32DataSize))
        {
            if (_MApp_SwUpdate_VerifyFlash(u32DramStartAddr, u32FlashStartAddr, u32DataSize))
            {
                MDrv_FLASH_WriteProtect(ENABLE);
                return TRUE;
            }
        }
    }

    printf("\nError: Verify flash failed!\n");

    // Failed! Here the contents of flash may be destroyed.
    // Need to make the system unable to boot up
    // The way is to erase the start sector of the bootloader or AP
    MApp_UsbClearWatchDog();

    MDrv_FLASH_AddressErase( u32FlashStartAddr, SW_UPDATE_BLOCK_SIZE, TRUE );

    MDrv_FLASH_WriteProtect(ENABLE);

    return FALSE;
}

static BOOLEAN _MApp_SwUpdate_EraseFlash(U32 u32FlashStartAddr, U32 u32DataSize)
{
    U16     u16StartBlock, u16EndBlock, u16BlockNo;
    U32     u32FlashEndAddr;
    U8      u8Buf[16];
    U32     u32TimeStart = msAPI_Timer_GetTime0();

    BURN_DBG(printf("_MApp_SwUpdate_EraseFlash(u32FlashStartAddr=0x%x,u32DataSize=0x%X)\n", u32FlashStartAddr, u32DataSize); );

    printf("Erasing...\n");

    if (u32DataSize == 0)
    {
        return FALSE;
    }

    u32FlashEndAddr = u32FlashStartAddr + u32DataSize - 1;

    // Here, each block is treated as uniform size
    // They may be not the same as that of flash
    u16StartBlock  = u32FlashStartAddr/SW_UPDATE_BLOCK_SIZE;
    u16EndBlock    = u32FlashEndAddr/SW_UPDATE_BLOCK_SIZE;

    if(_bAPBinFlag == FALSE)
    {
        _MApp_SwUpdate_NextBarPos0(u16EndBlock-u16StartBlock+1);
    }
    else
    {
        _MApp_SwUpdate_NextBarPos1(u16EndBlock-u16StartBlock+1);
    }

    BURN_DBG(printf("SW_UPDATE_BLOCK_SIZE=0x%x\n", (U32)SW_UPDATE_BLOCK_SIZE));
    BURN_DBG(printf("u16StartBlock=%d, u16EndBlock=%d\n", u16StartBlock, u16EndBlock));

    for ( u16BlockNo = u16StartBlock; u16BlockNo <= u16EndBlock; u16BlockNo++ )
    {
        MApp_UsbClearWatchDog();

        _MApp_SwUpdate_ProgressBar_ShowByValue( u16BlockNo - u16StartBlock );

        if (_MApp_SwUpdate_IsDirtyBlock(u16BlockNo))
        {
            U32     u32FlashAddr;
            U8      u8I;

            APD_DBG( printf( "Erasing block %2d\n", u16BlockNo) );
            u32FlashAddr = (U32) u16BlockNo * SW_UPDATE_BLOCK_SIZE;

            if ( !MDrv_FLASH_AddressErase(u32FlashAddr, SW_UPDATE_BLOCK_SIZE, TRUE) )
            {
                _MApp_SwUpdate_ShowError((S8 *)"Error: Flash Erase!" );
                return FALSE;
            }

            // Check if the flash block is blank to early find out write problem problem
            // It's enough to check the first few bytes (length is 8-byte alignment) of each block to save check time.
            // If a block is not blank and no error is found here, _MApp_SwUpdate_VerifyFlash() would find it finally.

            MDrv_FLASH_Read(u32FlashAddr, (U32)16,(U8*)((U32)u8Buf));

            for (u8I = 0; u8I < 16; u8I++)
            {
                if (u8Buf[u8I] != 0xFF)
                {
                    _MApp_SwUpdate_ShowError((S8 *)"Error: Flash Blanking (maybe write protect problem)!" );
                    return FALSE;
                }
            }
        }
    }

    printf("   Time: %d sec\n", msAPI_Timer_DiffTimeFromNow(u32TimeStart)/1000);

    return TRUE;
}

static BOOLEAN _MApp_SwUpdate_WriteFlash(U32 u32SrcAddr, U32 u32FlashAddr, U32 u32DataSize)
{
    U32 u32LeftSize = u32DataSize;
    U16 u16CopySize = DOWNLOAD_WIN1_LEN;
    U16 u16PrevDirtyBlock = -1;
    U8  *pu8TempBuf = NULL;
    U32 u32TimeStart = msAPI_Timer_GetTime0();

    BURN_DBG(printf("_MApp_SwUpdate_WriteFlash(u32SrcAddr=0x%x,u32FlashAddr=0x%X,u32DataSize=0x%X)\n", u32SrcAddr, u32FlashAddr, u32DataSize ); );

    printf( "Writing...\n" );

    if(_bAPBinFlag == FALSE)
    {
        _MApp_SwUpdate_NextBarPos0(u32DataSize);
    }
    else
    {
        _MApp_SwUpdate_NextBarPos1(u32DataSize);
    }

    pu8TempBuf = (U8 *)msAPI_Memory_Allocate(u16CopySize, BUF_ID_USB_DOWNLOAD);
    if( pu8TempBuf == NULL )
    {
        printf( "WriteFlash Buf Allocation Fail\n" );
        return FALSE;
    }

    while ( u32LeftSize > 0 )
    {
        U16 u16BlockNo = u32FlashAddr/SW_UPDATE_BLOCK_SIZE;

        MApp_UsbClearWatchDog();

        _MApp_SwUpdate_ProgressBar_ShowByValue(u32DataSize-u32LeftSize);

        if (u32LeftSize < u16CopySize)
        {
            u16CopySize = u32LeftSize;
        }

        if (_MApp_SwUpdate_IsDirtyBlock(u16BlockNo))
        {
            if (u16PrevDirtyBlock != u16BlockNo)
            {
                u16PrevDirtyBlock = u16BlockNo;
                APD_DBG( printf( "Writing block %2d\n", u16BlockNo) );
                //printf( "Writing block %2d\n", u16BlockNo);
            }

            MApp_UsbBDMA_Copy(u32SrcAddr, MApp_UsbVA2PA((U32)pu8TempBuf), (U32)u16CopySize, (U8)_u8MemCopyType);

            if ( !MDrv_FLASH_Write( u32FlashAddr, u16CopySize, pu8TempBuf ))
            {
                _MApp_SwUpdate_ShowError((S8 *)"Error: Writing flash failed!" );
                if (pu8TempBuf != NULL)
                {
                    msAPI_Memory_Free((void *)(pu8TempBuf), BUF_ID_USB_DOWNLOAD);
                    pu8TempBuf = NULL;
                }
                return FALSE;
            }
        }

        u32SrcAddr += u16CopySize;
        u32FlashAddr += u16CopySize;
        u32LeftSize -= u16CopySize;
    }

    if (pu8TempBuf != NULL)
    {
        msAPI_Memory_Free((void *)(pu8TempBuf), BUF_ID_USB_DOWNLOAD);
        pu8TempBuf = NULL;
    }

    printf("   Time: %d sec\n", msAPI_Timer_DiffTimeFromNow(u32TimeStart)/1000);

    return TRUE;
}

static BOOLEAN _MApp_SwUpdate_VerifyFlash(U32 u32SrcAddr, U32 u32FlashAddr, U32 u32DataSize)
{
    U32     u32LeftSize = u32DataSize;
    U16     u16CopySize = DOWNLOAD_VERIFY_LEN;
    U8      *pu8VerBuf1 = NULL;
    U8      *pu8VerBuf2 = NULL;
    U32     u32TimeStart = msAPI_Timer_GetTime0();
    printf("Verifying...\n");

    BURN_DBG(printf("VerifyFlash - Download Buffer Addr: 0x%08X; Flash Addr: 0x%08X; DataSize: 0x%08X\n", u32SrcAddr, u32FlashAddr, u32DataSize));

    if(_bAPBinFlag == FALSE)
    {
        _MApp_SwUpdate_NextBarPos0(u32DataSize);
    }
    else
    {
        _MApp_SwUpdate_NextBarPos1(u32DataSize);
    }

    pu8VerBuf1 = (U8 *)msAPI_Memory_Allocate(u16CopySize, BUF_ID_USB_DOWNLOAD);
    if( pu8VerBuf1 == NULL )
    {
        BURN_DBG( printf( "Verify Buf1 Allocation Fail\n" ) );
        return FALSE;
    }

    pu8VerBuf2 = (U8 *)msAPI_Memory_Allocate(u16CopySize, BUF_ID_USB_DOWNLOAD);
    if( pu8VerBuf2 == NULL )
    {
        BURN_DBG( printf( "Verify Buf2 Allocation Fail\n" ) );
        return FALSE;
    }

    while (u32LeftSize > 0)
    {
        MApp_UsbClearWatchDog();

        _MApp_SwUpdate_ProgressBar_ShowByValue(u32DataSize-u32LeftSize);

        if (u32LeftSize < u16CopySize)
        {
            u16CopySize = u32LeftSize;
        }

        MDrv_FLASH_Read(u32FlashAddr, (U32)u16CopySize, pu8VerBuf1/*(U8*)MApp_UsbVA2PA((void*)pu8VerBuf1)*/);
        //MApp_UsbBDMA_Copy(u32FlashAddr, (U32)pu8VerBuf1, (U32)u16CopySize, (U8)MIU_FLASH2SDRAM);
        MApp_UsbBDMA_Copy(u32SrcAddr, MApp_UsbVA2PA((U32)pu8VerBuf2), (U32)u16CopySize, (U8)_u8MemCopyType);

        if (memcmp((U8 *)pu8VerBuf1, (U8 *)pu8VerBuf2, u16CopySize) != 0)
        {
            BURN_DBG( printf("Flash Addr: 0x%08X, DRAM Addr: 0x%08X", u32FlashAddr, u32SrcAddr) );
            _MApp_SwUpdate_ShowError((S8 *)"Error: Data error in verification!");
            if (pu8VerBuf1 != NULL)
            {
                msAPI_Memory_Free((void *)(pu8VerBuf1), BUF_ID_USB_DOWNLOAD);
                pu8VerBuf1 = NULL;
            }

            if (pu8VerBuf2 != NULL)
            {
                msAPI_Memory_Free((void *)(pu8VerBuf2), BUF_ID_USB_DOWNLOAD);
                pu8VerBuf2 = NULL;
            }

            printf("\nVerify fail!\n");
            return FALSE;
        }

        u32SrcAddr += u16CopySize;
        u32FlashAddr += u16CopySize;
        u32LeftSize -= u16CopySize;
    }

    BURN_DBG(printf("\n"));

    if (pu8VerBuf1 != NULL)
    {
        msAPI_Memory_Free((void *)(pu8VerBuf1), BUF_ID_USB_DOWNLOAD);
        pu8VerBuf1 = NULL;
    }

    if (pu8VerBuf2 != NULL)
    {
        msAPI_Memory_Free((void *)(pu8VerBuf2), BUF_ID_USB_DOWNLOAD);
        pu8VerBuf2 = NULL;
    }

    printf("\nVerify OK\n");
    printf(" Time: %d sec\n", msAPI_Timer_DiffTimeFromNow(u32TimeStart)/1000);

    return TRUE;
}

// Set dirty blocks by binary comparison
static U8 _MApp_SwUpdate_CompareImage(EN_SW_UPDATE_MODE u8UpdateMode, U32 u32SrcAddr, U32 u32FlashAddr, U32 u32DataSize)
{
    U8      u8CompResult;
    U32     u32TimeStart = msAPI_Timer_GetTime0();

    printf("Comparing image...\n");

    if (u8UpdateMode == SW_UPDATE_MODE_FULL)
    {
        u8CompResult = DIFFERENT_IMAGE;

        APD_DBG(printf("Full update\n"));
        // Set all blocks to be 'dirty'
        _MApp_SwUpdate_SetAllDirtyBlocks(DIRTY);
    }
    else
    {
        U32     u32LeftSize;
        U16     u16CopySize;
        U16     u16BlockNo;
        U16     u16StartBlock;
        U16     u16EndBlock;
        U8      *pu8VerBuf1 = NULL;
        U8      *pu8VerBuf2 = NULL;

        APD_DBG(printf("Auto partial update\n"));
        // Set all blocks to be 'clean'
        _MApp_SwUpdate_SetAllDirtyBlocks(CLEAN);

        APD_DBG(printf("Compare Size: %d\n", u32DataSize));
        u16BlockNo = 0;
        u32LeftSize = u32DataSize;
        u16CopySize = DOWNLOAD_VERIFY_LEN;
        u8CompResult = SAME_IMAGE;

        pu8VerBuf1 = (U8 *)msAPI_Memory_Allocate(DOWNLOAD_VERIFY_LEN, BUF_ID_USB_DOWNLOAD);
        if( pu8VerBuf1 == NULL )
        {
            BURN_DBG( printf( "Verify Buf1 Allocation Fail\n" ) );
            _MApp_SwUpdate_SetAllDirtyBlocks(DIRTY);
            u8CompResult = DIFFERENT_IMAGE;
            return u8CompResult;
        }

        pu8VerBuf2 = (U8 *)msAPI_Memory_Allocate(DOWNLOAD_VERIFY_LEN, BUF_ID_USB_DOWNLOAD);
        if( pu8VerBuf2 == NULL )
        {
            BURN_DBG( printf( "Verify Buf2 Allocation Fail\n" ) );
            _MApp_SwUpdate_SetAllDirtyBlocks(DIRTY);
            u8CompResult = DIFFERENT_IMAGE;
            return u8CompResult;
        }

        u16StartBlock = u32FlashAddr/SW_UPDATE_BLOCK_SIZE;
        u16EndBlock    = (u32FlashAddr + u32DataSize)/SW_UPDATE_BLOCK_SIZE;

        if(_bAPBinFlag == FALSE)
        {
            _MApp_SwUpdate_NextBarPos0( u16EndBlock -  u16StartBlock + 1);
        }
        else
        {
            _MApp_SwUpdate_NextBarPos1( u16EndBlock -  u16StartBlock + 1);
        }
        while (u32LeftSize > 0)
        {
            MApp_UsbClearWatchDog();

            u16BlockNo = u32FlashAddr/SW_UPDATE_BLOCK_SIZE;

            if (u32LeftSize < DOWNLOAD_VERIFY_LEN)
            {
                u16CopySize = u32LeftSize;
            }

            _MApp_SwUpdate_ProgressBar_ShowByValue( u16BlockNo - u16StartBlock );

            if ( !_MApp_SwUpdate_IsDirtyBlock(u16BlockNo) )
            {
                MDrv_FLASH_Read(u32FlashAddr, (U32)u16CopySize, (U8*)((void*)pu8VerBuf1));
                //MApp_UsbBDMA_Copy(u32FlashAddr, (U32)pu8VerBuf1, (U32)u16CopySize, (U8)MIU_FLASH2SDRAM);
                MApp_UsbBDMA_Copy(u32SrcAddr, MApp_UsbVA2PA((U32)pu8VerBuf2), (U32)u16CopySize, (U8)_u8MemCopyType);

                if (memcmp((U8 *)pu8VerBuf1, (U8 *)pu8VerBuf2, u16CopySize) != 0)
                {
                    APD_DBG (printf("Block %2d different\n", u16BlockNo));
#if 0
                    {
                       U32 i,j;
                       printf("u32FlashAddr = 0x%08X\n", u32FlashAddr);
                       printf("pu8VerBuf1 = 0x%08X\n", pu8VerBuf1);
                       for(i=0;i<(u16CopySize/0x10);i++)
                       {
                            for(j=0;j<0x10;j++)
                            {
                                printf("%02X ", *(pu8VerBuf1 + i * 16 + j));
                            }
                            printf("\n");
                        }

                        printf("pu8VerBuf2 = 0x%08X\n", pu8VerBuf2);
                        for(i=0;i<(u16CopySize/0x10);i++)
                        {
                            for(j=0;j<0x10;j++)
                            {
                                printf("%02X ", *(pu8VerBuf2 + i * 16 + j));
                            }
                            printf("\n");
                        }

                        printf("u32SrcAddr = 0x%08X\n", u32SrcAddr);
                        for(i=0;i<(u16CopySize/0x10);i++)
                        {
                            for(j=0;j<0x10;j++)
                            {
                                printf("%02X ", *((U8 *)MApp_UsbPA2VA(u32SrcAddr) + i * 16 + j));
                            }
                            printf("\n");
                        }

                        printf("Stop\n");
                        while(1);
                    }
#endif
                    u8CompResult = DIFFERENT_IMAGE;
                    _MApp_SwUpdate_SetDirtyBlock(u16BlockNo, DIRTY);
                }
            }

            u32SrcAddr += u16CopySize;
            u32FlashAddr += u16CopySize;
            u32LeftSize -= u16CopySize;
        }

        if (u8CompResult == SAME_IMAGE)
        {
            //APD_DBG(printf("Same image\n"));
            printf(" => Same image\n");
        }
        else
        {
            // App image may be involved (note: some projects do not have bootloader)
            // Need to make them dirty for the first and the last blocks
            // This is because that it may power off during SW upgrade. Integrity check in bootloader would find this error.

            //APD_DBG(printf("Different image\n"));
            printf("==> Different image\n");

            APD_DBG(printf("The last block: %d\n", u16BlockNo));

            // make app's first block be dirty
            //don't update first block if it is no change
            //_MApp_SwUpdate_SetDirtyBlock(0, DIRTY);
            // make app's last block be dirty
            _MApp_SwUpdate_SetDirtyBlock(u16BlockNo, DIRTY);
        }

        if (pu8VerBuf1 != NULL)
        {
            msAPI_Memory_Free((void *)(pu8VerBuf1), BUF_ID_USB_DOWNLOAD);
            pu8VerBuf1 = NULL;
        }

        if (pu8VerBuf2 != NULL)
        {
            msAPI_Memory_Free((void *)(pu8VerBuf2), BUF_ID_USB_DOWNLOAD);
            pu8VerBuf2 = NULL;
        }

    }

    printf("   Time: %d sec\n", msAPI_Timer_DiffTimeFromNow(u32TimeStart)/1000);

    return u8CompResult;
}

static void _MApp_SwUpdate_ProgressBar_ShowByPercent( U8 u8Percent )
{
    if ( u8Percent == _u8CurPercent )
    {
        // Avoid flicker
        return;
    }

    MApp_UsbClearWatchDog();

    _u8CurPercent = u8Percent;
    //BURN_DBG( printf( "\r%d%%", (int)_u8CurPercent ) );
    BURN_DBG( printf( "{%u}", (int)_u8CurPercent ) );

    if (pZUIDrawPercentageCB != NULL)
    {
        pZUIDrawPercentageCB(_u8CurPercent);
    }
}

static void _MApp_SwUpdate_ProgressBar_ShowByValue( U32 u32Value )
{
    U8  u8Percent;

    u8Percent = _u8PercentStart + u32Value * ( _u8PercentEnd - _u8PercentStart ) / _u32ProgressMaxSize;
    _MApp_SwUpdate_ProgressBar_ShowByPercent( u8Percent );
}

static void _MApp_SwUpdate_NextBarPos1(U32 u32Size)
{
    U8 start, end;

    MApp_UsbClearWatchDog();

    if (_pau8CurBar == NULL)
    {
        _MApp_SwUpdate_ProgressBar_Init(0, 100, u32Size);
    }
    else
    {
        start = _pau8CurBar[_u8BarIndex];
        if ((start >= 50)&&(_bDownloadType == FALSE))
        {
            start = 50;
        }
        else if((start >= 100)&&(_bDownloadType == TRUE))
        {
            start = 100;
        }
        else
        {
            _u8BarIndex++;
        }

        end = _pau8CurBar[_u8BarIndex];
        if ((end > 50) && (_bDownloadType == FALSE))
        {
            end = 50;
        }
        else if((start >= 100)&&(_bDownloadType == TRUE))
        {
            start = 100;
        }

        if (end < start)
        {
            end = start;
        }

        printf("start = %02d, end = %02d, u32Size = %d\n", start, end, u32Size);
        _MApp_SwUpdate_ProgressBar_Init(start, end, u32Size);
    }

    // Update progress bar in OSD
    _MApp_SwUpdate_ProgressBar_ShowByValue(0);
}

static void _MApp_SwUpdate_NextBarPos0(U32 u32Size)
{
    U8 start, end;

    MApp_UsbClearWatchDog();

    if (_pau8CurBar == NULL)
    {
        _MApp_SwUpdate_ProgressBar_Init(0, 100, u32Size);
    }
    else
    {
        start = _pau8CurBar[_u8BarIndex];
        if (start >= 100)
        {
            start = 100;
        }
        else
        {
            _u8BarIndex++;
        }

        end = _pau8CurBar[_u8BarIndex];
        if (end > 100)
        {
            end = 100;
        }

        if (end < start)
        {
            end = start;
        }

        _MApp_SwUpdate_ProgressBar_Init(start, end, u32Size);
    }

    // Update progress bar in OSD
    _MApp_SwUpdate_ProgressBar_ShowByValue(0);
}

static void _MApp_SwUpdate_ProgressBar_Init( U8 u8PercentStart, U8 u8PercentEnd, U32 u32Size )
{
    _u8CurPercent = u8PercentStart;

    // For updating progress bar after Init,
    // Need to let g_u8CurPercent be different with g_u8PercentStart
    if (_u8CurPercent > 0)
    {
        _u8CurPercent--;
    }

    _u8PercentStart = u8PercentStart;
    _u8PercentEnd = u8PercentEnd;
    _u32ProgressMaxSize = ( u32Size == 0 ) ? 1 : u32Size;

    MApp_UsbClearWatchDog();
}

static void _MApp_SwUpdate_Init_PrivateVariable(BOOLEAN bDownloadType)
{
    _bDownloadType = bDownloadType;

    // Progress bar
    if(_bDownloadType == FALSE)
    {
        _u8BarIndex = 1; // 0 is for check CMAC; 1 is for compare image
    }
    else
    {
        _u8BarIndex = 5;
    }

    _pau8CurBar = USBUpgrade_Percent;//NULL
    _u8CurPercent = 0;
    _u8PercentStart = 0;
    _u8PercentEnd = 100;
    _u32ProgressMaxSize = 100;

    _MApp_SwUpdate_SetAllDirtyBlocks(DIRTY);
}

static void _MApp_SwUpdate_Reboot(void)
{
    #if 0
    MDrv_Sys_SetWatchDogTimer(0);
    MDrv_Sys_EnableWatchDog();
    while(1);   // Necessary because of using watch dog reset
    #else
    MDrv_Sys_WholeChipReset();
    #endif
}

//****************************************************************************
/// Software Update Start
/// @param u8UpdateMode IN: Update Mode
/// -@see EN_SW_UPDATE_MODE
/// @param allowTwoFlashMode \b IN: Allow two flash or not
/// -TRUE: Allow two flash
/// -FALSE: Not allow two flash
/// @param bDownloadType IN: Normal download or BIN file download
/// -TRUE: BIN file download
/// -FALSE: Normal download
/// @param bSecondRun IN: Download one image or two images
/// -TRUE: Download two different images to different flash
/// -FALSE: Download one image
/// @return BOOLEAN
/// -TRUE: Software update successfully.
/// -FALSE: Software update failed.
//****************************************************************************
BOOLEAN MApp_SwUpdate_Start(EN_SW_UPDATE_MODE u8UpdateMode, BOOLEAN allowTwoFlashMode, BOOLEAN bDownloadType, BOOLEAN bSecondRun, U32 u32DramStartAddr, U32 u32FileSize, U8 u8MemType, BOOLEAN bAPBinFlag)
{
    U32     u32DataSize;
    U8      u8CurImgType;
    BOOLEAN bResult;
    MS_IMG_INFO TempImgInfo;
    U32 imgBaseOffset;

    BURN_DBG( printf("MApp_SwUpdate_Start(\n" ); );
    BURN_DBG( printf(" u8UpdateMode=0x%X\n", u8UpdateMode); );
    BURN_DBG( printf(" allowTwoFlashMode=%u\n", allowTwoFlashMode); );
    BURN_DBG( printf(" bDownloadType=%u\n", bDownloadType); );
    BURN_DBG( printf(" u32DramStartAddr=0x%X\n", u32DramStartAddr); );
    BURN_DBG( printf(" u32FileSize=0x%X\n", u32FileSize); );
    BURN_DBG( printf(" u8MemType=0x%X\n", u8MemType); );


    U32 u32TimeStart = msAPI_Timer_GetTime0();

    BURN_DBG( printf( "Updating...\n" ) );

#if 0// (MSP4_IDENTIFIER_VALUE != GUKA)
    printf("\n!!! This libswupdate is illegally released !!!\n");
#endif

    //_u32BufStartAddr = u32DramStartAddr ;
    _u8MemCopyType = u8MemType ;
    _bAPBinFlag = bAPBinFlag;

    _MApp_SwUpdate_Init_PrivateVariable(bDownloadType);

    MApp_UsbClearWatchDog();

    bResult = FALSE;
    u32DataSize = u32FileSize;
    BURN_DBG(printf("Software size: %d (0x%08X)\n", u32DataSize, u32DataSize));
    BURN_DBG(printf("Software addr: 0x%08X\n", (U32)u32DramStartAddr));

    if (u32DataSize == 0)
    {
        BURN_DBG(printf("MApp_SwUpdate_UpdateSoftware length=0\n"));
        _MApp_SwUpdate_ShowError((S8 *)"Error: No data!");
        return FALSE;
    }
 #if ENABLE_CMAC_CHECK
    else
    {
        U32 u32TimeStartCMAC = msAPI_Timer_GetTime0();
        printf("Checking Signature...\n");
        if (Check_CMAC(MApp_UsbPA2VA(u32DramStartAddr), u32FileSize) != TRUE)
        {
            printf("Error> Signature checking failed !!\n");
            return FALSE;
        }
        printf("   Time: %d sec\n", msAPI_Timer_DiffTimeFromNow(u32TimeStartCMAC)/1000);
    }
 #endif

    // Get image type
    u8CurImgType = IMG_TYPE_NONE;
    BURN_DBG(printf("Checking image...\n"));
    //MApp_UsbBDMA_Copy( _u32BufStartAddr + u32ImgInfoOffset, MApp_UsbVA2PA((U32)(&TempImgInfo)), sizeof( MS_IMG_INFO ), (U8)_u8MemCopyType);
    MApp_UsbBDMA_Copy( u32DramStartAddr + u32ImgInfoOffset, MApp_UsbVA2PA((U32)(&TempImgInfo)), sizeof( MS_IMG_INFO ), (U8)_u8MemCopyType);

    if(bDownloadType == FALSE)
    {
        if (MApp_ImgInfo_IsAppImage(&TempImgInfo))
        {
            u8CurImgType |= IMG_TYPE_APP;
        }
    }
    else
    {
        u8CurImgType |= IMG_TYPE_APP;
    }

    BURN_DBG( printf( "\nModel Name: %s\n", TempImgInfo.u8ModelName ) );
    BURN_DBG( printf( "\nu8CurImgType 0x%02x\n", u8CurImgType ) );

    //////////////////////////////////////////////////////////////////////
    /* Start to Burn AP/Bootcode from SDRAM to FALSH */
    //////////////////////////////////////////////////////////////////////
    imgBaseOffset=0;

    if ( u8CurImgType == IMG_TYPE_APP )
    {
        U32 u32FlashAddr;
        BURN_DBG( printf( "App image:\n" ) );
        BURN_DBG( printf( "  Updating app\n" ) );

        if(allowTwoFlashMode)
        {
            imgBaseOffset=0;
            msFlash_ChipSelect(FLASH_ID1);
            BURN_DBG(printf("update AP2!\n"));
        }
        else
        {
            imgBaseOffset=0;
            msFlash_ChipSelect(FLASH_ID0);
            BURN_DBG(printf("force to update AP1!\n"));
        }

        //MDrv_FLASH_Read(u32ImgInfoOffset, sizeof( MS_IMG_INFO ), (U8 *) (void*)&TempImgInfo);

        u32FlashAddr = 0;


        U32 u32Offset = 0;
        if(u8UpdateMode == SW_UPDATE_MODE_PARTIAL_OAD)
        {
            printf("Update for OAD\n");
            U32 AP_OFFSET, AP_OFFSET_ADDR;
            U8 chunk[128];
            AP_OFFSET_ADDR = 0x18;
            u32Offset = 0x20000;
            //Read AP offset
            MDrv_FLASH_Read(u32Offset, 128, (U8 *) (void*)chunk);
            AP_OFFSET = chunk[AP_OFFSET_ADDR+3];
            AP_OFFSET <<= 8;
            AP_OFFSET |= chunk[AP_OFFSET_ADDR+2];
            AP_OFFSET <<= 8;
            AP_OFFSET |= chunk[AP_OFFSET_ADDR+1];
            AP_OFFSET <<= 8;
            AP_OFFSET |= chunk[AP_OFFSET_ADDR+0];
            BURN_DBG( printf("AP_OFFSET: %08X\n", AP_OFFSET) );
            u32Offset = AP_OFFSET;
        }

        //if ( _MApp_SwUpdate_BurnData( u8UpdateMode, _u32BufStartAddr+u32Offset, u32FlashAddr+u32Offset, u32DataSize-u32Offset ) == TRUE )
        if ( _MApp_SwUpdate_BurnData( u8UpdateMode, u32DramStartAddr+u32Offset, u32FlashAddr+u32Offset, u32DataSize-u32Offset ) == TRUE )
        {
            bResult = TRUE;
        }
        else
        {
            BURN_DBG( printf( "Fail to Burn AP Code\n" ) );
            _MApp_SwUpdate_ProgressBar_ShowByPercent(0xFD);  //return error flag
        }
    }
    else
    {
        _MApp_SwUpdate_ShowError( (S8 *)"Error: Unknown TV software!" );
        BURN_DBG( printf( "Unknown image type\n" ) );
        _MApp_SwUpdate_ProgressBar_ShowByPercent(0xFC);  //return error flag
        return FALSE;
    }

    if (bResult == TRUE)
    {
        _MApp_SwUpdate_ProgressBar_ShowByPercent(100);
        printf("Success.\n");
        printf("Update Time: %d sec\n", msAPI_Timer_DiffTimeFromNow(u32TimeStart)/1000);

        if(bSecondRun == FALSE)
        {
            // Sync code from CL1454568(Mantis-996579)
            //  User want to see OSD show 100%, so wait 1 sec here.
            msAPI_Timer_Delayms(1000);


            BURN_DBG(printf("Rebooting...\n"));
            msFlash_ChipSelect(FLASH_ID0);
            _MApp_SwUpdate_Reboot();
            BURN_DBG(printf("Rebooting...fail\n"));
            _MApp_SwUpdate_ProgressBar_ShowByPercent(0xFB);  //return error flag
        }
    }
    else
    {
        printf("Failed!\n");
        BURN_DBG( printf( "\nError: Failed to update software.\n" ) );
        _MApp_SwUpdate_ProgressBar_ShowByPercent(0xFA);  //return error flag

        MDrv_Sys_StopCpu(1);
    }

    return bResult;
}

#undef MAPP_SWUPDATE_C

