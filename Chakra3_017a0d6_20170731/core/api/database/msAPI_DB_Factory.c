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

#include "Board.h"

#if (ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK)
#include "Utl.h"

#include "msAPI_Flash.h"
#include "msAPI_Timer.h"


//==========================================================================================

#define DEBUG_API_DB_FACTORY(x)     //x
#define DEBUG_DB_FAC_STATUS_FLAG(x) //x
#define DEBUG_DB_FAC_USE_TIME(x)    //x


#define DB_FAC_SAVE_DATA_RETRY_TIME 2

#define DB_FAC_CHECK_CRC_WHEN_LOAD  ENABLE


#define DB_FAC_FLASH_START_ADDR     (0x10000 * FMAP_FACTORY_SETTING_BANK_START)
#define DB_FAC_FLASH_END_ADDR       ((0x10000 * (FMAP_FACTORY_SETTING_BANK_START+FMAP_FACTORY_SETTING_BANK_COUNT)) - 1 )


#define ENABLE_FACTORY_ERASE_4K     1

#if( ENABLE_FACTORY_ERASE_4K )

#define DB_FAC_DATA_COPY_NUM    2

#define DB_FAC_BLOCK_SIZE   0x1000 // 4K
#define DB_FAC_BLOCK_NUM    16

#define DB_FAC_BLOCK_DATA_FLASH_ADDR(blockIdx)  ( DB_FAC_FLASH_START_ADDR+(DB_FAC_BLOCK_SIZE * blockIdx) )

#define DB_FAC_BLOCK_INFO_OFFSET                0x0FF0
#define DB_FAC_BLOCK_INFO_STATUS_OFFSET         0x0FFF

#else

#define DB_FAC_DATA_COPY_NUM    1

#define DB_FAC_BLOCK_SIZE   0x10000 // 64K
#define DB_FAC_BLOCK_NUM    2

#define DB_FAC_BLOCK_DATA_FLASH_ADDR(blockIdx)  ( DB_FAC_FLASH_START_ADDR+(DB_FAC_BLOCK_SIZE * blockIdx) )

#define DB_FAC_BLOCK_INFO_OFFSET                0xFFF0
#define DB_FAC_BLOCK_INFO_STATUS_OFFSET         0xFFFF

#endif

#define DB_FAC_SAVE_DATA_SIZE_MAX   (0x1000-0x10)


#define DB_FAC_BLOCK_INFO_FLASH_ADDR(blockIdx)         (DB_FAC_BLOCK_DATA_FLASH_ADDR(blockIdx)+DB_FAC_BLOCK_INFO_OFFSET)
#define DB_FAC_BLOCK_INFO_STATUS_FLASH_ADDR(blockIdx)  (DB_FAC_BLOCK_DATA_FLASH_ADDR(blockIdx)+DB_FAC_BLOCK_INFO_STATUS_OFFSET)


#define DB_FAC_BLOCK_STATUS_EMPTY      0xFF
#define DB_FAC_BLOCK_STATUS_WRITING    0x7F
#define DB_FAC_BLOCK_STATUS_GOOD       0x3F
//#define DB_FAC_BLOCK_STATUS_GOOD_OLD   0x1F

#define DB_FAC_BLOCK_STATUS_CRC_ERR    0x0F

#define DB_FAC_BLOCK_STATUS_BAD        0x00

#define DB_FAC_BLOCK_STATUS_INVALID    0xF1

#define DB_FAC_BLOCK_INDEX_INVALID  0xFF


typedef struct
{
    // 0 ~ 3
    U32 u32WriteTime;

    // 4 ~ 7
    U16 u16DataSize;
    U8 u8Dummy6;
    U8 u8Dummy7;

    // 8 ~ 11
    U32 u32DataCheckSum;

    // 12 ~ 15
    U8 u8Dummy12;
    U8 u8Dummy13;
    U8 u8Dummy14;
    U8 u8BlockStatus;
} __attribute__((__packed__)) StruFactoryBlockInfo;

static U8 s_DB_FAC_u8LastBlcokIdx = 0;
static StruFactoryBlockInfo s_DB_FAC_stLastBlockInfo;

#define DB_FAC_DATA_BUF_SIZE    4096

static U8 s_DB_FAC_au8DataBuf[DB_FAC_DATA_BUF_SIZE];

/*
BOOL MApp_DB_Factory_CheckBank(U8 u8BlockIdx, U8 u8BlockStatus)
{
    if( DB_FAC_BLOCK_STATUS_GOOD == u8BlockStatus )
    {
        // Check status
        if( s_Factory_astBlockInfo[0].u8BlockStatus != DB_FAC_BLOCK_STATUS_GOOD )
        {
            return FALSE;
        }

        // Check data/checksum
    }
    return FALSE;
}
*/

BOOL _msAPI_DB_FAC_ReadFlash(U32 u32StartAddr, U32 u32ReadSize, U8 * user_buffer)
{
    return MDrv_FLASH_Read(u32StartAddr, u32ReadSize, user_buffer);
}

BOOL _msAPI_DB_FAC_VerifyFlash( U32 u32FlashAddr, U32 u32DataSize, U8* pu8DataBuf)
{
    DEBUG_API_DB_FACTORY( printf("_msAPI_DB_FAC_VerifyFlash(u32FlashAddr=0x%X, size=%u)\n", u32FlashAddr, u32DataSize); );

    U8 au8TmpBuf[256];
    U16 i;
    U8* p8DramData;
    U32 u32AddrOffset = 0;
    U16 u16CurCheckSize = 0;


    //DEBUG_API_DB_FACTORY( printf("  Verify flash data ...\n" ); );

    while( u32AddrOffset < u32DataSize )
    {
        if( (u32DataSize - u32AddrOffset) < 256 )
            u16CurCheckSize = u32DataSize - u32AddrOffset;
        else
            u16CurCheckSize = 256;

        //printf(" Check: ram=0x%X, f=0x%X, Size=%u\n",
        //    u32DramAddr + u32AddrOffset, u32FlashAddr + u32AddrOffset, u16CurCheckSize);

        if( FALSE == _msAPI_DB_FAC_ReadFlash(u32FlashAddr + u32AddrOffset, u16CurCheckSize, au8TmpBuf) )
        {
            printf("\nError: Fac_Verify : Read flash failed\n");
            return FALSE;
        }

        //p8DramData = (U8*)MsOS_PA2KSEG1(u32DramAddr + u32AddrOffset);
        p8DramData = pu8DataBuf + u32AddrOffset;

        for( i = 0; i < u16CurCheckSize; ++ i )
        {
            if( au8TmpBuf[i] != p8DramData[i] )
            {
                printf("\nError: Fac_Verify: data diff at Flash:0x%X.\n", u32FlashAddr + u32AddrOffset + i);
                return FALSE;
            }
        }

        u32AddrOffset += u16CurCheckSize;
    }

    return TRUE; //Exit with success
}

BOOL _msAPI_DB_FAC_WriteFlash(U32 u32StartAddr, U32 u32WriteSize, U8 * user_buffer)
{
    BOOL bRtn;


    DEBUG_API_DB_FACTORY( printf("_msAPI_DB_FAC_WriteFlash(u32FlashAddr=0x%X, size=%u)\n", u32StartAddr, u32WriteSize); );


    // Check boundry
    {
        U32 u32EndAddr = u32StartAddr + u32WriteSize - 1;

        if( (u32StartAddr < DB_FAC_FLASH_START_ADDR)
          ||(u32EndAddr > (DB_FAC_FLASH_END_ADDR))
          )
        {
            printf("\nError: FAC_W: Addr(0x%X,0x%X) out of boundary!\n", u32StartAddr, u32EndAddr);
            return FALSE;
        }
    }


    bRtn = MDrv_FLASH_Write( u32StartAddr, u32WriteSize, user_buffer );
    if( FALSE == bRtn )
    {
        printf("\nError: MDrv_FLASH_Write failed (0x%X,%u)\n", u32StartAddr, u32WriteSize);
        return FALSE;
    }

    // Verify the data on flash
    bRtn = _msAPI_DB_FAC_VerifyFlash( u32StartAddr, u32WriteSize, user_buffer);
    if( FALSE == bRtn )
    {
        printf("\nError: Write flash verify failed (0x%X,%u)\n", u32StartAddr, u32WriteSize);
        return FALSE;
    }

    return TRUE;
}

U8 _msAPI_DB_Factory_Get_BlockStatus(U8 u8BlockIdx)
{
    BOOL bRtn;
    U8 u8Status;


    DEBUG_API_DB_FACTORY( printf("_msAPI_DB_Factory_Get_BlockStatus(Block=%u)\n", u8BlockIdx); );

    if( u8BlockIdx > DB_FAC_BLOCK_NUM )
        return DB_FAC_BLOCK_STATUS_INVALID;


    // Read flash
    bRtn = _msAPI_DB_FAC_ReadFlash( DB_FAC_BLOCK_INFO_STATUS_FLASH_ADDR(u8BlockIdx),
                             1,
                             (U8*)&u8Status );
    if( FALSE == bRtn )
    {
        printf("\nError: Read flash failed\n");
        return DB_FAC_BLOCK_STATUS_INVALID;
    }

    return u8Status;
}

BOOL _msAPI_DB_Factory_Set_BlockStatus(U8 u8BlockIdx, U8 u8Status)
{
    BOOL bRtn;
    //U8 u8Status2;


    DEBUG_API_DB_FACTORY( printf("_msAPI_DB_Factory_Set_BlockStatus(Block=%u, stu=0x%X)\n", u8BlockIdx, u8Status); );

    if( u8BlockIdx > DB_FAC_BLOCK_NUM )
        return FALSE;

    bRtn = _msAPI_DB_FAC_WriteFlash( DB_FAC_BLOCK_INFO_STATUS_FLASH_ADDR(u8BlockIdx),
                                    1,
                                    (U8*)&u8Status );
    if( FALSE == bRtn )
    {
        printf("\nError: Fac_set_block(%u %X): Write flash failed\n", u8BlockIdx, u8Status);

        u8Status = DB_FAC_BLOCK_STATUS_BAD;
        _msAPI_DB_FAC_WriteFlash( DB_FAC_BLOCK_INFO_STATUS_FLASH_ADDR(u8BlockIdx),
                                1,
                                (U8*)&u8Status );
        return FALSE;
    }

#if 0
    // Verify
    u8Status2 = _msAPI_DB_Factory_Get_BlockStatus(u8BlockIdx);
    if( u8Status != u8Status )
    {
        printf("\nError: Fac_set_block(%u %X): Verify failed\n", u8BlockIdx, u8Status);
        return FALSE;
    }
#endif

    return TRUE;
}

BOOL _msAPI_DB_Factory_Read_BlockInfo(U8 u8BlockIdx, StruFactoryBlockInfo* pstBlockInfo)
{
    BOOL bRtn;

    if( u8BlockIdx > DB_FAC_BLOCK_NUM )
        return FALSE;

    bRtn = _msAPI_DB_FAC_ReadFlash( DB_FAC_BLOCK_INFO_FLASH_ADDR(u8BlockIdx),
                                    sizeof(StruFactoryBlockInfo),
                                    (U8*)pstBlockInfo );
    if( FALSE == bRtn )
    {
        printf("\nError: Read-Block: Read flash failed\n");
        return FALSE;
    }

    return TRUE;
}

BOOL _msAPI_DB_Factory_Write_BlockInfo(U8 u8BlockIdx, StruFactoryBlockInfo* pstBlockInfo)
{
    BOOL bRtn;
    //StruFactoryBlockInfo astBlock_Tmp;

    if( u8BlockIdx > DB_FAC_BLOCK_NUM )
        return FALSE;

    bRtn = _msAPI_DB_FAC_WriteFlash( DB_FAC_BLOCK_INFO_FLASH_ADDR(u8BlockIdx),
                                     sizeof(StruFactoryBlockInfo),
                                     (U8*)pstBlockInfo );
    if( FALSE == bRtn )
    {
        printf("\nError: Write-Block: Write flash failed\n");
        return FALSE;
    }

#if 0
    // Verify ...
    memset(&astBlock_Tmp, 0, sizeof(StruFactoryBlockInfo));

    bRtn = _msAPI_DB_Factory_Read_BlockInfo( u8BlockIdx, &astBlock_Tmp);
    if( FALSE == bRtn )
    {
        printf("\nError: Write-Block: Read block failed\n");
        return FALSE;
    }


    {
        U8 i;
        U8* pu8Data_1 = (U8*)pstBlockInfo;
        U8* pu8Data_2 = (U8*)&astBlock_Tmp;

        for( i = 0; i < sizeof(StruFactoryBlockInfo); ++ i)
        {
            if( pu8Data_1[i] != pu8Data_2[i] )
            {
                printf("\nError: Write-Block: Verify failed\n");
                return FALSE;
            }
        }
    }
#endif

    return TRUE;
}

U32 _msAPI_DB_Factory_CalCheckSum(U8* pu8DataBuf, U32 u32DataSize)
{
#if( ENABLE_SW_CRC32 )
    return msAPI_CRC_Cal(pu8DataBuf, u32DataSize);
#else
    return MApp_CalCheckSum( pu8DataBuf, u32DataSize );
#endif
}

U8 _msAPI_DB_FAC_FindLast(void)
{
    U8 u8BlockIdx;
    StruFactoryBlockInfo stBlockInfo;
    U8 u8BlockIdx_Max = DB_FAC_BLOCK_INDEX_INVALID;
    U32 u32WriteTime_Max = 0;



    DEBUG_API_DB_FACTORY( printf("_msAPI_DB_FAC_FindLast()\n"); );


    for( u8BlockIdx = 0; u8BlockIdx < DB_FAC_BLOCK_NUM; ++ u8BlockIdx )
    {
        if( FALSE == _msAPI_DB_Factory_Read_BlockInfo( u8BlockIdx, &stBlockInfo ) )
        {
            printf("\nError: FindLast: Read block(%u) failed\n", u8BlockIdx);
            continue;
        }

        DEBUG_API_DB_FACTORY( printf(" %u) 0x%X", u8BlockIdx, stBlockInfo.u8BlockStatus); );

        // Check status
        if( stBlockInfo.u8BlockStatus != DB_FAC_BLOCK_STATUS_GOOD )
        {
            DEBUG_API_DB_FACTORY( printf("\n"); );
            continue;
        }

        // Compare write time
        DEBUG_API_DB_FACTORY(printf(" WT=%u", stBlockInfo.u32WriteTime); );
        if( stBlockInfo.u32WriteTime > u32WriteTime_Max )
        {
            u8BlockIdx_Max = u8BlockIdx;
            u32WriteTime_Max = stBlockInfo.u32WriteTime;
        }

        DEBUG_API_DB_FACTORY( printf("\n"); );
    }

    if( u8BlockIdx_Max == DB_FAC_BLOCK_INDEX_INVALID )
    {
        DEBUG_API_DB_FACTORY(printf(" FAC_FindLast: No good block!!\n"););
    }
    else
    {
        DEBUG_API_DB_FACTORY(printf(" FAC_FindLast: Good block=%u\n", u8BlockIdx_Max); );
    }

    return u8BlockIdx_Max;
}

BOOL _msAPI_DB_FAC_CheckFlashBlockCRC(U8 u8BlockIdx)
{
    StruFactoryBlockInfo stBlockInfo;
    BOOL bRtn;


    bRtn = _msAPI_DB_Factory_Read_BlockInfo( u8BlockIdx, &stBlockInfo );
    if( FALSE == bRtn )
    {
        printf("\nError: Read block failed\n");
        return FALSE;
    }

    if( stBlockInfo.u8BlockStatus != DB_FAC_BLOCK_STATUS_GOOD )
    {
        return FALSE;
    }

    // Load data from flash to tmp buffer
    bRtn = _msAPI_DB_FAC_ReadFlash(
            DB_FAC_BLOCK_DATA_FLASH_ADDR(u8BlockIdx),
            stBlockInfo.u16DataSize,
            s_DB_FAC_au8DataBuf);
    if( FALSE == bRtn )
    {
        printf("\nError: Read factory data failed\n");
        return FALSE;
    }

    // Check CRC
    U32 u32CheckSum = _msAPI_DB_Factory_CalCheckSum( s_DB_FAC_au8DataBuf, stBlockInfo.u16DataSize );

    if( u32CheckSum != stBlockInfo.u32DataCheckSum )
    {
        printf(" {DB_FAC: block_%u CRC error} ", u8BlockIdx );
        return FALSE;
    }

    return TRUE;;
}

U8 _msAPI_DB_FAC_FindLastGood(void)
{
    //U32 u32CheckSum;
    U8 u8LastBlockIdx;
    //BOOL bRtn;
    BOOL bBlockCRCErrorCount = 0;


    DEBUG_API_DB_FACTORY( printf("_msAPI_DB_FAC_FindLastGood()\n"); );


    while( bBlockCRCErrorCount < DB_FAC_BLOCK_NUM )
    {
        // Get last and good block
        u8LastBlockIdx = _msAPI_DB_FAC_FindLast();
        if( DB_FAC_BLOCK_INDEX_INVALID == u8LastBlockIdx )
        {
            //printf("No more good block\n");
            break;
        }


    #if( DB_FAC_CHECK_CRC_WHEN_LOAD )
        // Check CRC ...
        if( FALSE == _msAPI_DB_FAC_CheckFlashBlockCRC(u8LastBlockIdx) )
        {
            printf("\nWarning: Factory block_%u CRC failed!\n", u8LastBlockIdx);

            // Modify block status to CRC_ERR ...
            bBlockCRCErrorCount += 1;
            if( bBlockCRCErrorCount == 1 )
            {
                // Disable write protect
                msAPI_Flash_Set_WriteProtect_Disable_Range( DB_FAC_BLOCK_DATA_FLASH_ADDR(u8LastBlockIdx), DB_FAC_BLOCK_SIZE);
            }

            // Modify block status to CRC_ERR
            _msAPI_DB_Factory_Set_BlockStatus(u8LastBlockIdx, DB_FAC_BLOCK_STATUS_CRC_ERR);
        }
        else
    #endif
        {
            DEBUG_API_DB_FACTORY( printf(" => Block_%u CRC OK\n", u8LastBlockIdx); );

            s_DB_FAC_u8LastBlcokIdx = u8LastBlockIdx;
            _msAPI_DB_Factory_Read_BlockInfo( s_DB_FAC_u8LastBlcokIdx, &s_DB_FAC_stLastBlockInfo );

            break;
        }

    }

    if( bBlockCRCErrorCount )
    {
        // Recovery write protect
        msAPI_Flash_Set_WriteProtect(ENABLE);
    }

    return u8LastBlockIdx;
}

BOOL msAPI_DB_Factory_Init(void)
{
    DEBUG_API_DB_FACTORY( printf("msAPI_DB_Factory_Init()\n"); );

    memset( &(s_DB_FAC_stLastBlockInfo), 0, sizeof(StruFactoryBlockInfo));
    memset( s_DB_FAC_au8DataBuf, 0, DB_FAC_DATA_BUF_SIZE );


    printf("Factory use flash: 0x%X ~ 0x%X\n", DB_FAC_FLASH_START_ADDR, DB_FAC_FLASH_END_ADDR);

    //msAPI_DB_Factory_PrintBlockInfo();

    return TRUE;
}

BOOL msAPI_DB_Factory_LoadFromFlash(U8* pu8DataBuf, U32 u32DataSize)
{
    BOOL bRtn = TRUE;
    U8 u8GoodBlockIdx;
    DEBUG_DB_FAC_USE_TIME( U32 u32Time1; );


    DEBUG_API_DB_FACTORY( printf("msAPI_DB_Factory_LoadFromFlash()\n"); );

    if( sizeof(StruFactoryBlockInfo) != 16 )
    {
        printf("\nError: sizeof(StruFactoryBlockInfo) is not 16\n");
        return FALSE;
    }

    if( u32DataSize > DB_FAC_SAVE_DATA_SIZE_MAX)
    {
        printf("\nError: DB_FAC: u32DataSize=%0x%X > 0x%X\n", u32DataSize, DB_FAC_SAVE_DATA_SIZE_MAX);
        return FALSE;
    }

    // Wait flash write done
    msAPI_Flash_WaitWriteDone(5000);


    DEBUG_DB_FAC_STATUS_FLAG( msAPI_DB_Factory_PrintBlockInfo(); );

    DEBUG_DB_FAC_USE_TIME( u32Time1 = MsOS_GetSystemTime(); );

    // Find good block ...
    u8GoodBlockIdx = _msAPI_DB_FAC_FindLastGood();

    if( u8GoodBlockIdx == DB_FAC_BLOCK_INDEX_INVALID )
    {
        printf("\nError: Can not find good factory block!!");
        return FALSE;
    }

    // Read flash-factory data
    bRtn = _msAPI_DB_FAC_ReadFlash(DB_FAC_BLOCK_DATA_FLASH_ADDR(u8GoodBlockIdx), u32DataSize, pu8DataBuf);
    if( FALSE == bRtn )
    {
        printf("\nError: Read factory data failed\n");
        return FALSE;
    }

    printf(" DB_FAC: Good block=%u\n", u8GoodBlockIdx );

    DEBUG_DB_FAC_USE_TIME(printf("Load Fac data use %u\n", msAPI_Timer_DiffTime_2(u32Time1, MsOS_GetSystemTime()) ); );

    return TRUE;
}

BOOL _msAPI_DB_FAC_WriteDataToFlash(U8* pu8DataBuf, U32 u32DataSize)
{
    U8 u8RetryTime;
    BOOL bRtn = TRUE;
    U8 u8TargetBlockIdx;
    U32 u32Time1;
    StruFactoryBlockInfo stNewBlockInfo;
    //U8 u8NGCount = 0;
    //U8 u8OKCount = 0;


    // Capture start time
    u32Time1 = MsOS_GetSystemTime();

    DEBUG_API_DB_FACTORY( printf("msAPI_DB_Factory_SaveToFlash(u32DataSize=%u)\n", u32DataSize); );

    if( sizeof(StruFactoryBlockInfo) != 16 )
    {
        printf("\nError: sizeof(StruFactoryBlockInfo) is not 16\n");
        return FALSE;
    }

    if( u32DataSize > DB_FAC_SAVE_DATA_SIZE_MAX)
    {
        printf("\nError: DB_FAC: u32DataSize=%0x%X > 0x%X\n", u32DataSize, DB_FAC_SAVE_DATA_SIZE_MAX);
        return FALSE;
    }


    DEBUG_API_DB_FACTORY( printf(" Cur=%u: WriteTime=%u\n",
            s_DB_FAC_u8LastBlcokIdx, s_DB_FAC_stLastBlockInfo.u32WriteTime ); );


    memset( &(stNewBlockInfo), 0, sizeof(StruFactoryBlockInfo));

    // Cal data-checksum
    stNewBlockInfo.u16DataSize = u32DataSize;
    stNewBlockInfo.u32DataCheckSum = _msAPI_DB_Factory_CalCheckSum( pu8DataBuf, u32DataSize );

    // Increase writetime
    stNewBlockInfo.u32WriteTime = s_DB_FAC_stLastBlockInfo.u32WriteTime + 1;
    DEBUG_API_DB_FACTORY( printf(" New: WriteTime=%u\n", stNewBlockInfo.u32WriteTime ); );


    // Wait flash write done
    msAPI_Flash_WaitWriteDone(5000);

    // Disable write protect...
#if( ENABLE_FACTORY_ERASE_4K )
    // Disable WP for all factory bank
    msAPI_Flash_Set_WriteProtect_Disable_Range( DB_FAC_BLOCK_DATA_FLASH_ADDR(0), 0x10000);
#else
    if( s_DB_FAC_u8LastBlcokIdx == 0 )
        u8TargetBlockIdx = 1;
    else
        u8TargetBlockIdx = 0;
    // Disable WP for target bank
    msAPI_Flash_Set_WriteProtect_Disable_Range( DB_FAC_BLOCK_DATA_FLASH_ADDR(u8TargetBlockIdx), 0x10000);
#endif

    for( u8RetryTime = 0; u8RetryTime < DB_FAC_SAVE_DATA_RETRY_TIME; ++ u8RetryTime )
    {
        bRtn = TRUE;

    #if( ENABLE_FACTORY_ERASE_4K )
        u8TargetBlockIdx = (s_DB_FAC_u8LastBlcokIdx + 1 + u8RetryTime)%DB_FAC_BLOCK_NUM;
    #endif

        DEBUG_API_DB_FACTORY( printf(" u8TargetBlockIdx=%u\n", u8TargetBlockIdx ); );

        // Step 1: Erase flash
    #if(ENABLE_FACTORY_ERASE_4K )
        MDrv_SERFLASH_SectorErase(DB_FAC_BLOCK_DATA_FLASH_ADDR(u8TargetBlockIdx),
                                  DB_FAC_BLOCK_DATA_FLASH_ADDR(u8TargetBlockIdx)+0xFFF );
    #else

        MDrv_FLASH_AddressErase(DB_FAC_BLOCK_DATA_FLASH_ADDR(u8TargetBlockIdx), DB_FAC_BLOCK_SIZE, TRUE);
    #endif

        // Wait erase done
        msAPI_Flash_WaitWriteDone(5000);

        // Step 2: Set target block-status to writing
        DEBUG_API_DB_FACTORY( printf(" Set Block(%u) to writing\n", u8TargetBlockIdx ); );
        stNewBlockInfo.u8BlockStatus = DB_FAC_BLOCK_STATUS_WRITING;

        //  Update block-status to flash
        bRtn = _msAPI_DB_Factory_Set_BlockStatus( u8TargetBlockIdx, stNewBlockInfo.u8BlockStatus );
        if( FALSE == bRtn )
        {
            printf("\nError: Fac_Write: Write status failed\n");
            goto DB_FAC_CHECK_RESULT;
        }

        // Step 3: Write data to flash
        bRtn = _msAPI_DB_FAC_WriteFlash(DB_FAC_BLOCK_DATA_FLASH_ADDR(u8TargetBlockIdx), u32DataSize, pu8DataBuf );
        if( FALSE == bRtn )
        {
            printf("\nError: Fac_Write: Write data failed\n");
            goto DB_FAC_CHECK_RESULT;
        }

        // Step 4: Set target block-status to good ...
        stNewBlockInfo.u8BlockStatus = DB_FAC_BLOCK_STATUS_GOOD;
        DEBUG_API_DB_FACTORY( printf(" Set Block(%u) to good\n", u8TargetBlockIdx ); );

        //  Write block-info to flash
        bRtn = _msAPI_DB_Factory_Write_BlockInfo(u8TargetBlockIdx, &stNewBlockInfo );
        if( FALSE == bRtn )
        {
            printf("\nError: Fac_Write: Write block-info failed\n");
            goto DB_FAC_CHECK_RESULT;
        }


    DB_FAC_CHECK_RESULT:

        if( bRtn == TRUE ) // Write successful
        {
            //u8OKCount += 1;
            break; // Exit with successful
        }
        else // Something wrong happen
        {
            //u8NGCount += 1;
            printf("Retry(%u) save factory to flash\n", u8RetryTime);
        }
    }

    // Recovery write protect
    msAPI_Flash_Set_WriteProtect(ENABLE);


    if( bRtn == TRUE )
    {
        s_DB_FAC_u8LastBlcokIdx = u8TargetBlockIdx;
        s_DB_FAC_stLastBlockInfo = stNewBlockInfo;

        printf("DB_FAC: Write done => block=%u, WT=%u, t=%u\n",
            s_DB_FAC_u8LastBlcokIdx, s_DB_FAC_stLastBlockInfo.u32WriteTime, msAPI_Timer_DiffTime_2(u32Time1,MsOS_GetSystemTime()));
    }
    else
    {
        printf("\nError: Save factory to flash failed!\n");
    }

    //DEBUG_DB_FAC_USE_TIME( printf("Save fac use %u\n", msAPI_Timer_DiffTime_2(u32Time1,MsOS_GetSystemTime()) ); );

    DEBUG_DB_FAC_STATUS_FLAG( msAPI_DB_Factory_PrintBlockInfo(); );

    return bRtn;
}

BOOL msAPI_DB_Factory_SaveToFlash(U8* pu8DataBuf, U32 u32DataSize)
{
    BOOL bRtn;
    U8 u8NGCount = 0;
    U8 u8OKCount = 0;


    while(1)
    {
        bRtn = _msAPI_DB_FAC_WriteDataToFlash(pu8DataBuf, u32DataSize);
        if( FALSE == bRtn )
        {
            u8NGCount += 1;
            if( u8NGCount >= 1 )
            {
                break;
            }
        }
        else
        {
            u8OKCount += 1;
            if( u8OKCount >= DB_FAC_DATA_COPY_NUM )
            {
                break;
            }
        }
    }

    if( u8OKCount )
        return TRUE;
    else
        return FALSE;
}

void msAPI_DB_Factory_PrintBlockInfo(void)
{
    StruFactoryBlockInfo stBlockInfo;
    U8 i;

    printf("DB_Factory block info:\n");
    for( i = 0; i < DB_FAC_BLOCK_NUM; i += 1 )
    {
        _msAPI_DB_Factory_Read_BlockInfo( i, &stBlockInfo );

        printf(" %u) 0x%X", i, stBlockInfo.u8BlockStatus);

        if( stBlockInfo.u8BlockStatus != DB_FAC_BLOCK_STATUS_EMPTY )
        {
            printf(" WT=%u", stBlockInfo.u32WriteTime);
        }
        if( stBlockInfo.u8BlockStatus == DB_FAC_BLOCK_STATUS_GOOD )
        {
            printf(" S=%u C=0x%08X", stBlockInfo.u16DataSize, stBlockInfo.u32DataCheckSum);

            if( _msAPI_DB_FAC_CheckFlashBlockCRC(i) )
            {
                printf(" CRC OK");
            }
        }

        printf("\n");
    }
}

#endif


