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

// Common Definition
#include "Board.h"

#include "Utl.h"
#include "msAPI_Global.h"

#include "msAPI_DB_CH.h"

#include "msAPI_Flash.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"

//===============================================================

#define DEBUG_DB_CH(x)      //x
#define DEBUG_DB_CH_FLOW(x) //x
//#define DEBUG_DB_CH_FLOW(x) do{ msDebug_ANSI_SetColorText(E_FONT_COLOR_GREEN);  x;  msDebug_ANSI_AllAttrOffText(); } while(0)

//===============================================================

#define DB_CH_FLASH_BANK_SIZE       0x10000


#define DB_CH_HEADER_SIZE    16

#if( ENABLE_S2 /*|| (( CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN))*/ )
    #define ENABLE_DB_CH_WRITE_DATA_PER_BANK   1  // Write one bank for each time
#else
    #define ENABLE_DB_CH_WRITE_DATA_PER_BANK   0  // Write one bank for each time
#endif

typedef enum
{
    E_DB_CH_STATE__IDLE,
    E_DB_CH_STATE__ERASE_START,
    E_DB_CH_STATE__ERASE_IN_PROGRESS,

    E_DB_CH_STATE__WRITE_DATA,

    E_DB_CH_STATE__UNKNOWN,
} Enu_DB_CH_State;

#define E_DB_CH_STATE__WRITE_DB_1ST_STATE   E_DB_CH_STATE__ERASE_START

//===============================================================

static Stru_DB_CH_InitData s_stDB_CH_InitData;


typedef struct
{
    // Flash constant info ...
    //U8 u8FlashUnitNumPer1Bank;
    //U8 u8FlashUnitNumTotal;
    //U16 u16FlashUnitInfoOffset;
    U8 u8FlashBankStart_0;
    U8 u8FlashBankStart_1;
    U32 u32CheckDataOffset;

    // Flash control flag
    //U8 u8FlashCurUnitIdx;
    //U8 u8FlashNextEmptyUnitIdx;
    U8 u8CurDataBaseIdx;
    U32 u32WriteFlashTime;

    // Control ...
    BOOL bWriteFlashStart;

    Enu_DB_CH_State eState;


    // Debug
    BOOL bEnVerifyWrite;

} Stru_DB_CH_Info;

static Stru_DB_CH_Info s_stDB_CH_Info;


//#define DATABASE_INFO_SIZE      sizeof(Stru_DB_CH_Info)
#define DB_CH_VERSION_INVALID   0

typedef struct
{
    U32 u32MagicNO;
    U32 u32WriteTime;
    U16 u16CheckSum;
} __attribute__ ((packed)) Stru_DB_CH_Header;

//===============================================================
#define DB_CH_FLASH_BANK(idx)  ((idx) ? s_stDB_CH_Info.u8FlashBankStart_1 : s_stDB_CH_Info.u8FlashBankStart_0)

#define DB_CH_VERSION_FLASH_ADDR(u8DBIdx)   ((DB_CH_FLASH_BANK(u8DBIdx)*DB_CH_FLASH_BANK_SIZE) + s_stDB_CH_Info.u32CheckDataOffset)

//==============================================================
//==============================================================

void _msAPI_DB_CH_Set_State(Enu_DB_CH_State eState)
{
    //DEBUG_DB_CH( printf("_msAPI_DB_CH_Set_State(eState=%u)\n", eState); );

    if( eState >= E_DB_CH_STATE__UNKNOWN )
    {
        eState = E_DB_CH_STATE__IDLE;
    }

    //s_DB_CH_eState = eState;
    s_stDB_CH_Info.eState = eState;
}

Enu_DB_CH_State _msAPI_DB_CH_Get_State(void)
{
    //DEBUG_DB_CH( printf("_msAPI_DB_CH_Get_State()"); );

    //return s_DB_CH_eState;
    return s_stDB_CH_Info.eState;
}

U16 _msAPI_DB_CH_CalCheckSum(U8* pu8Data, U16 u16DataSize)
{
#if ENABLE_SW_CRC16 // Use CRC16 cal CheckSum

    return msAPI_CRC16_Cal(pu8Data, u16DataSize);

#else
    U16 i;
    U16 u16CheckSum = 0x1234;

    for( i = 0; i < u16DataSize; ++ i )
    {
        u16CheckSum += pu8Data[i];
    }

    return u16CheckSum;
#endif
}

#define DB_CH_CAL_HEADER_CHECKSUM(pstDBCH_Header) _msAPI_DB_CH_CalCheckSum((U8*)(pstDBCH_Header), sizeof(Stru_DB_CH_Header)-2)

BOOL _msAPI_DB_CH_ReadHeaderFromFlash(U8 u8DBIdx, Stru_DB_CH_Header* pstDB_CH_Header)
{
    U32 u32FlashAddr;

    DEBUG_DB_CH(printf("_msAPI_DB_CH_ReadHeaderFromFlash(u8DBIdx=0x%x)\n", u8DBIdx); );

    msAPI_Flash_WaitWriteDone(5000);

    u32FlashAddr = DB_CH_VERSION_FLASH_ADDR(u8DBIdx);

    if( FALSE == MDrv_FLASH_Read(u32FlashAddr, sizeof(Stru_DB_CH_Header), (U8*)pstDB_CH_Header) )
    {
        printf("\nError: DB_CH_Header: Read flash failed!\n");
        return FALSE;
    }

    // Check CheckSum
    if( pstDB_CH_Header->u16CheckSum != DB_CH_CAL_HEADER_CHECKSUM(pstDB_CH_Header)  )
    {
        printf("\nError: DB_CH_Header: Checksum is wrong! 0x%X, 0x%X\n", pstDB_CH_Header->u16CheckSum, DB_CH_CAL_HEADER_CHECKSUM(pstDB_CH_Header));
        return FALSE;
    }

    // Check ID
    if( pstDB_CH_Header->u32MagicNO != s_stDB_CH_InitData.u32MagicId )
    {
        printf("\nError: DB_CH_Header: Id is wrong! 0x%X, 0x%X\n", pstDB_CH_Header->u32MagicNO, s_stDB_CH_InitData.u32MagicId);
        return FALSE;
    }

    return TRUE;
}

U32 _msAPI_DB_CH_ReadFlashDataBaseVersion(U8 u8DBIdx)
{
    //U32 u32FlashAddr;
    Stru_DB_CH_Header stDB_CH_Header;


    memset( &stDB_CH_Header, 0, sizeof(Stru_DB_CH_Header) );

    DEBUG_DB_CH(printf("_msAPI_DB_CH_ReadFlashDataBaseVersion(u8DBIdx=0x%x)\n", u8DBIdx); );

    if( FALSE == _msAPI_DB_CH_ReadHeaderFromFlash(u8DBIdx, &stDB_CH_Header) )
    {
        printf("\nError: DB_Ver: Read header");
        return DB_CH_VERSION_INVALID;
    }

    // todo: Check other ??

    return stDB_CH_Header.u32WriteTime;
}

BOOL _msAPI_DB_CH_WriteHeaderToFlash(U8 u8DBIdx)
{
    U32 u32FlashAddr;
    Stru_DB_CH_Header stDB_CH_Header;


    DEBUG_DB_CH(printf("_msAPI_DB_CH_WriteHeaderToFlash(u8DBIdx=0x%x)\n", u8DBIdx); );

    if( sizeof(Stru_DB_CH_Header) > DB_CH_HEADER_SIZE )
    {
        printf("\nError: DB_CH_Ver: struct size(%u) > DB_CH_HEADER_SIZE!\n", sizeof(Stru_DB_CH_Header));
        return FALSE;
    }

    memset( &stDB_CH_Header, 0, sizeof(Stru_DB_CH_Header) );

    msAPI_Flash_WaitWriteDone(5000);

    // Disable DB WP
    //msAPI_Flash_Set_WP_DB_CH(DISABLE);

    stDB_CH_Header.u32MagicNO = s_stDB_CH_InitData.u32MagicId;
    stDB_CH_Header.u32WriteTime = s_stDB_CH_Info.u32WriteFlashTime;
    stDB_CH_Header.u16CheckSum = DB_CH_CAL_HEADER_CHECKSUM( &stDB_CH_Header );
    //printf("stDB_CH_Info.u16CheckSum=0x%X\n", stDB_CH_Info.u16CheckSum);

    u32FlashAddr = DB_CH_VERSION_FLASH_ADDR(u8DBIdx);
    MDrv_FLASH_Write(u32FlashAddr, sizeof(Stru_DB_CH_Header), (U8*)&stDB_CH_Header);


    // Verify header on flash
    {
        Stru_DB_CH_Header st_DB_CH_Header_Tmp;
        U8 i;
        U8 *pu8Header1 = (U8*)&stDB_CH_Header;
        U8 *pu8Header2 = (U8*)&st_DB_CH_Header_Tmp;;

        if( FALSE == _msAPI_DB_CH_ReadHeaderFromFlash(u8DBIdx, &st_DB_CH_Header_Tmp) )
        {
            printf("\nError: DB_CH_Header_Ver: Read header failed!\n");
            return FALSE;
        }

        // compare data
        for( i = 0; i < sizeof(Stru_DB_CH_Header); i += 1 )
        {
            if( pu8Header1[i] != pu8Header2[i] )
            {
                printf("\nError: DB_CH_Header_Ver: header data is different!\n");
                return FALSE;
            }
        }
    }
    DEBUG_DB_CH(printf(" DB_CH: verify header ok\n"); );


    // Enable DB WP
    //msAPI_Flash_Set_WP_DB_CH(ENABLE);

    return TRUE;
}


/*
typedef struct
{
    // Flash ...
    U8 u8FlashBankStart;
    //U16 u16FlashSaveUnitSize;
    U8 u8FlashSaveBankCount;

    // Dram
    U32 u32DramDataAddr;
    U32 u32DramDataSize;

    // CallBack function
    void (*pfCallBack_BeforeWriteFlash)(void);

    // Debug
    U8 u8DebugFlag;
} Stru_DB_CH_InitData;
*/
void msAPI_DB_CH_Print_InitData(void);

void msAPI_DB_CH_Init(Stru_DB_CH_InitData* pstDB_CH_InitData)
{
    DEBUG_DB_CH( printf("msAPI_DB_CH_Init()\n"); );

    s_stDB_CH_InitData = *pstDB_CH_InitData;

    DEBUG_DB_CH( msAPI_DB_CH_Print_InitData(); );

    if( s_stDB_CH_InitData.u8FlashSaveBankCount == 0 )
    {
        printf("\nError: u8FlashSaveBankCount = %u\n", s_stDB_CH_InitData.u8FlashSaveBankCount);
        //return ;
        s_stDB_CH_InitData.u8FlashSaveBankCount = 1;
        printf("Force u8FlashSaveBankCount to %u\n", s_stDB_CH_InitData.u8FlashSaveBankCount);
        msAPI_Timer_Delayms(5000);
    }

    if( s_stDB_CH_InitData.u32DramDataSize > (U32)(s_stDB_CH_InitData.u8FlashSaveBankCount*DB_CH_FLASH_BANK_SIZE-DB_CH_HEADER_SIZE) )
    {
        printf("\nError: u32DramDataSize(%u) > u16FlashSaveSize(%u)\n", s_stDB_CH_InitData.u32DramDataSize,
                            s_stDB_CH_InitData.u8FlashSaveBankCount*DB_CH_FLASH_BANK_SIZE );
        s_stDB_CH_InitData.u32DramDataSize = s_stDB_CH_InitData.u8FlashSaveBankCount*DB_CH_FLASH_BANK_SIZE-DB_CH_HEADER_SIZE;
        printf("Force u32DramDataSize to %u\n", s_stDB_CH_InitData.u32DramDataSize);
        msAPI_Timer_Delayms(5000);
    }

    memset( &s_stDB_CH_Info, 0, sizeof(Stru_DB_CH_Info) );

    s_stDB_CH_Info.u8FlashBankStart_0 = s_stDB_CH_InitData.u8FlashBankStart;
    s_stDB_CH_Info.u8FlashBankStart_1 = s_stDB_CH_Info.u8FlashBankStart_0 + s_stDB_CH_InitData.u8FlashSaveBankCount;

    s_stDB_CH_Info.u32CheckDataOffset = s_stDB_CH_InitData.u8FlashSaveBankCount*DB_CH_FLASH_BANK_SIZE-DB_CH_HEADER_SIZE;

    //u8DataBaseBank = 0;
    s_stDB_CH_Info.u8CurDataBaseIdx = 0;

    s_stDB_CH_Info.u32WriteFlashTime = 0;

    //s_DB_CH_eState = E_DB_CH_STATE__IDLE;
    s_stDB_CH_Info.eState = E_DB_CH_STATE__IDLE;
}

// This function only copy the data from flash to dram
BOOL msAPI_DB_CH_LoadFromFlash(void)
{
    BOOL bResult = TRUE;
    U8 u8CurDataBaseIdx = 0;
    U32 u32SN0 = DB_CH_VERSION_INVALID;
    U32 u32SN1 = DB_CH_VERSION_INVALID;


    DEBUG_DB_CH( printf("msAPI_DB_CH_LoadFromFlash()\n"); );

    //u8DataBaseBank = 0;
    s_stDB_CH_Info.u8CurDataBaseIdx = 0;

    s_stDB_CH_Info.u32WriteFlashTime = 0;

    // Wait flash free...
    msAPI_Flash_WaitWriteDone(3000);

#if 0//ENABLE_S2
    u32SN0 = _msAPI_DB_CH_ReadFlashDataBaseVersion((U8)(VERSION_DB_BANK0), 0);
    u32SN1 = _msAPI_DB_CH_ReadFlashDataBaseVersion((U8)VERSION_DB_BANK1, 0);
#else
    u32SN0 = _msAPI_DB_CH_ReadFlashDataBaseVersion(0);
    u32SN1 = _msAPI_DB_CH_ReadFlashDataBaseVersion(1);
#endif

    DEBUG_DB_CH( printf(" s8SN0(%x) s8SN1(%x)\n", u32SN0, u32SN1); );

    // BD_0 is invalid and DB_1 is invalid
    if ( (u32SN0 == DB_CH_VERSION_INVALID) && (u32SN1 == DB_CH_VERSION_INVALID) )
    {
        bResult = FALSE;
        printf("\nWarning: DB_CH: DataBase version is wrong!\n");
    }
    else // BD_0 is valid or DB_1 is valid
    {
        bResult = TRUE;

        if( u32SN0 != DB_CH_VERSION_INVALID ) // BD_0 is valid
        {
            if( u32SN1 != DB_CH_VERSION_INVALID ) // BD_0 is valid && DB_1 is valid
            { // BD_0 and DB_1 are valid, compare write time
                if( u32SN0 > u32SN1 )
                    u8CurDataBaseIdx = 0;
                else
                    u8CurDataBaseIdx = 1;
            }
            else  // BD_0 is valid && DB_1 is invalid
            {
                u8CurDataBaseIdx = 0;
            }
        }
        else // BD_0 is invalid && DB_1 is valid
        {
            u8CurDataBaseIdx = 1;
        }

        s_stDB_CH_Info.u32WriteFlashTime = u8CurDataBaseIdx ? u32SN1 : u32SN0;

        DEBUG_DB_CH( printf(" u8CurDataBaseIdx=0x%X, s_DB_CH_u32WriteTime=0x%x\n", u8CurDataBaseIdx, s_stDB_CH_Info.u32WriteFlashTime); );

        s_stDB_CH_Info.u8CurDataBaseIdx = u8CurDataBaseIdx;

        // Copy data from flash to dram:
    /*
    #if(ENABLE_COMPRESS_DATA)
        MS_U8 u8DataBaseBankStart = (u8CurDataBaseIdx ? SYSTEM_BANK_DATABASE1_S2 : SYSTEM_BANK_DATABASE0_S2);
        MApi_DecompressData(u8DataBaseBankStart);
    #else
        msAPI_MIU_Copy(DB_CH_FLASH_BANK_SIZE* (DB_CH_FLASH_BANK(u8CurDataBaseIdx)),
                DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR))),
                RM_64K_USAGE,
                MIU_FLASH2SDRAM);
    #endif
    */
        DEBUG_DB_CH( printf("Copy flash(0x%X) to dram(0x%X) size=%u\n",
                        DB_CH_FLASH_BANK_SIZE * (DB_CH_FLASH_BANK(s_stDB_CH_Info.u8CurDataBaseIdx)),
                        s_stDB_CH_InitData.u32DramDataAddr,
                        s_stDB_CH_InitData.u32DramDataSize ); );

        msAPI_MIU_Copy( DB_CH_FLASH_BANK_SIZE * (DB_CH_FLASH_BANK(s_stDB_CH_Info.u8CurDataBaseIdx)),
                s_stDB_CH_InitData.u32DramDataAddr,
                s_stDB_CH_InitData.u32DramDataSize,
                MIU_FLASH2SDRAM);
    }

    return bResult;
}

void msAPI_DB_CH_WriteToFlash(void)
{
    DEBUG_DB_CH( printf("msAPI_DB_CH_WriteToFlash()\n"); );
    s_stDB_CH_Info.bWriteFlashStart = TRUE;

#if( ENABLE_DB_CH_WRITE_DATA_PER_BANK )
    // If DB_CH is in writing data state, re-start all state
    if( _msAPI_DB_CH_Get_State() == E_DB_CH_STATE__WRITE_DATA )
    {
        printf("DB_CH: Re-Start state\n");
        _msAPI_DB_CH_Set_State(E_DB_CH_STATE__WRITE_DB_1ST_STATE);
    }
#endif
}

void msAPI_DB_CH_WriteToFlash_RightNow(void)
{
    DEBUG_DB_CH( printf("msAPI_DB_CH_WriteToFlash_RightNow()\n"); );

    msAPI_DB_CH_WriteToFlash();


    while( msAPI_DB_CH_Is_Busy() )
    {
#if 1//( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
#endif

        msAPI_DB_CH_Task();
    }

    DEBUG_DB_CH( printf("msAPI_DB_CH_WriteToFlash_RightNow() - end\n"); );
}

//void msAPI_MIU_QuickDataBaseErase(U8 u8Bank, BOOL bWait)
BOOL _msAPI_DB_CH_EraseFlash(U8 u8Bank, BOOL bWait)
{
    BOOL bResult = TRUE;
    U32 dst;

    dst = DB_CH_FLASH_BANK_SIZE * u8Bank;
    DEBUG_DB_CH(printf("_msAPI_DB_CH_EraseFlash, dst=0x%Lx \r\n", (U32)dst));

    // Disable DB WP
    //msAPI_Flash_Set_WP_DB_CH(DISABLE);

    bResult = MDrv_FLASH_AddressErase(dst, DB_CH_FLASH_BANK_SIZE, bWait);
    if( bResult == FALSE )
    {
        printf("\nError: MDrv_FLASH_AddressErase() failed\n");
        return FALSE;
    }

    return TRUE;
}

BOOL _MApp_DB_CH_VerifyFlash(U32 u32DramAddr, U32 u32FlashAddr, U32 u32DataSize)
{
    DEBUG_DB_CH( printf("_MApp_DB_CH_VerifyFlash(u32DramAddr=0x%X, u32FlashAddr=0x%X, size=%u)\n", u32DramAddr, u32FlashAddr,u32DataSize); );

    U8 au8TmpBuf[256];
    U16 i;
    U8* p8DramData;
    U32 u32AddrOffset = 0;
    U16 u16CurCheckSize = 0;


    DEBUG_DB_CH( printf("  Verify flash data ...\n" ); );

    while( u32AddrOffset < u32DataSize )
    {
        if( (u32DataSize - u32AddrOffset) < 256 )
            u16CurCheckSize = u32DataSize - u32AddrOffset;
        else
            u16CurCheckSize = 256;

        //printf(" Check: ram=0x%X, f=0x%X, Size=%u\n",
        //    u32DramAddr + u32AddrOffset, u32FlashAddr + u32AddrOffset, u16CurCheckSize);

        if( FALSE == MDrv_FLASH_Read(u32FlashAddr + u32AddrOffset, u16CurCheckSize, au8TmpBuf) )
        {
            printf("\nError: Verify Flash: Read flash failed\n");
            return FALSE;
        }

        p8DramData = (U8*)MsOS_PA2KSEG1(u32DramAddr + u32AddrOffset);

        for( i = 0; i < u16CurCheckSize; ++ i )
        {
            if( au8TmpBuf[i] != p8DramData[i] )
            {
                printf("\nError: Verify data failed at Flash:0x%X.\n", u32FlashAddr + u32AddrOffset + i);
                return FALSE;
            }
        }

        u32AddrOffset += u16CurCheckSize;
    }


    return TRUE; //Exit with success
}

BOOL msAPI_DB_CH_WriteDram2Flash(U32 u32DramAddr, U32 u32FlashAddr, U32 u32Size)    // SRAM2Flash
{
    U32 u32DataVirAddr = MsOS_PA2KSEG0(u32DramAddr);
    BOOL bResult;
    //U32 u32Crc_dram;
    //U32 u32Crc_Flash;


    DEBUG_DB_CH( printf(" StoreDataBase2Flash(u32DramAddr=0x%X, u32FlashAddr=0x%X, size=%d(0x%X))\n", u32DramAddr, u32FlashAddr, u32Size, u32Size); );

    // Flush D-cache
    MsOS_Dcache_Flush( u32DataVirAddr, u32Size );

    // Flush Memory
    MsOS_FlushMemory();


    // Write data to falsh
    //printf("MDrv_FLASH_Write(u32FlashAddr=%X, u32Size=%X)\n", u32FlashAddr, u32Size);
    DEBUG_DB_CH( printf("MDrv_FLASH_Write(u32FlashAddr=%X, u32Size=%X)\n", u32FlashAddr, u32Size); );
    bResult = MDrv_FLASH_Write( u32FlashAddr,
                                u32Size,
                                (U8*)u32DataVirAddr );
    if( bResult == FALSE )
    {
        printf("\nError: StoreDataBase2Flash: Write data failed\n");
        return FALSE;
    }

    // Verify ...
    DEBUG_DB_CH( printf("Verify CH data on flash\n"); );

    if( FALSE == _MApp_DB_CH_VerifyFlash(u32DramAddr, u32FlashAddr, u32Size) )
    {
        printf("\nError: DB_CH: Verify data faild\n");
        return FALSE;
    }
    DEBUG_DB_CH(printf(" DB_CH: verify data ok\n"); );

    return TRUE;
}

#if( ENABLE_DB_CH_WRITE_DATA_PER_BANK )
#else
/******************************************************************************/
/// API for MIU Store Database::
/// Copy database information from SDRAM to flash
/// @param u8Bank \b IN: bank number
/// @param u32srcaddr \b IN: SDRAM address for Database information
/// @param s32size \b IN: Database information size
/******************************************************************************/
//BOOL msAPI_MIU_StoreDataBase2Flash(U8 u8Bank, U32 u32srcaddr, U32 u32Size, BOOLEAN bErase)    // SRAM2Flash
BOOL _msAPI_DB_CH_StoreDataBase2Flash(U8 u8DBIdx, U32 u32SrcAddr, U32 u32Size)    // SRAM2Flash
{
    BOOL bResult = TRUE;
    U8 u8Bank = DB_CH_FLASH_BANK(u8DBIdx);
    U32 u32FlashAddr;
    //U32 u32Time;


    DEBUG_DB_CH( printf(" StoreDataBase2Flash(u8Bank=0x%X, src=0x%X, size=%d)\n", u8Bank, u32SrcAddr, u32Size); );

    u32FlashAddr = DB_CH_FLASH_BANK_SIZE * u8Bank;
    DEBUG_DB_CH( printf("   u32FlashAddr=0x%X\n", u32FlashAddr ); );

    //u32Time = msAPI_Timer_GetTime0();

    //msAPI_Flash_WaitWriteDone(3000);

    //msAPI_Flash_ChipSelect((FLASH_CHIP_SELECT)0);

    //msAPI_Flash_Set_WP_DB_CH(DISABLE);

    //printf("t4=%u,", msAPI_Timer_GetTime0());

#if 1 // No need copy data to temp buffer
    {
        // Write data to flash - new unit
        U32 u32DataVirAddr = MsOS_PA2KSEG0(u32SrcAddr);
        //printf("u32DataVirAddr=0x%X\n", u32DataVirAddr);

        // Flush D-cache
        MsOS_Dcache_Flush( u32DataVirAddr, u32Size );

        // Flush Memory
        MsOS_FlushMemory();

        DEBUG_DB_CH( printf("Copy dram(0x%X) to flash(0x%X) size=0x%X\n",
                        u32SrcAddr, u32FlashAddr, u32Size ); );


        // Write data to falsh
        bResult = MDrv_FLASH_Write( u32FlashAddr,
                                    u32Size,
                                    (U8*)MsOS_PA2KSEG1(u32SrcAddr) );
        if( bResult == FALSE )
        {
            printf("\nError: StoreDataBase2Flash: Write data failed\n");
            return FALSE;
        }
    }
#else
    {
        U8 *flash_buf;
        U32 count;

        flash_buf = (U8*)msAPI_Memory_Allocate(FLASH_BUF_SIZE, BUF_ID_FLASH);
        if (flash_buf == NULL)
        {
            //__ASSERT(0);
            printf("\nError: malloc flash_buf fail!\n");
            bResult = FALSE;
        }
        else
        {
            while (u32Size > 0)
            {
                count = MIN(u32Size, FLASH_BUF_SIZE);
                memcpy( (flash_buf), (void *)_PA2VA(u32srcaddr),  count);
                u32srcaddr += count;
                MDrv_FLASH_Write(u32FlashAddr,count, flash_buf);
                u32FlashAddr += count;
                u32Size -= count;
            }

            MSAPI_MEMORY_FREE(flash_buf, BUF_ID_FLASH);
        }
    }
#endif

    //printf("t5=%u,", msAPI_Timer_GetTime0());

    DEBUG_DB_CH( printf("Verify CH data on flash\n"); );

    if( FALSE == _MApp_DB_CH_VerifyFlash(u32SrcAddr, u32FlashAddr, u32Size) )
    {
        printf("\nError: DB_CH: Verify data faild\n");
        return FALSE;
    }
    DEBUG_DB_CH(printf(" DB_CH: verify data ok\n"); );

    // Write header to flash ...
    if( FALSE == _msAPI_DB_CH_WriteHeaderToFlash(u8DBIdx) )
    {
        printf("\nError: DB_CH: Write header faild\n");
        return FALSE;
    }

    //msAPI_Flash_Set_WP_DB_CH(ENABLE);

    //printf("tt=%u,", msAPI_Timer_DiffTime_2(u32Time, msAPI_Timer_GetTime0()));

    return bResult;
}
#endif

BOOL msAPI_DB_CH_Is_Busy(void)
{
    if( s_stDB_CH_Info.bWriteFlashStart
      ||(_msAPI_DB_CH_Get_State() != E_DB_CH_STATE__IDLE)
      )
    {
        return TRUE;
    }

    return FALSE;
}

void msAPI_DB_CH_CallBack_BeforeWriteFlash(void)
{
    if( s_stDB_CH_InitData.pfCallBack_BeforeWriteFlash )
    {
        s_stDB_CH_InitData.pfCallBack_BeforeWriteFlash();
    }
}

#if(ENABLE_DB_CH_WRITE_DATA_PER_BANK)
static U32 s_DB_CH_u32WriteData_Count = 0;
static U32 s_DB_CH_u32WriteData_MaxSize = 0;
static BOOL s_DB_CH_bWriteDataDone;
static BOOL s_DB_CH_bWriteHeaderDone;

#define DB_CH_WRITE_DATA_SIZE_STEP  0x8000//0x10000

void msAPI_DB_CH_Init_WriteData(void)
{
    s_DB_CH_bWriteDataDone = FALSE;
    s_DB_CH_bWriteHeaderDone = FALSE;

    s_DB_CH_u32WriteData_Count = 0;
    s_DB_CH_u32WriteData_MaxSize = s_stDB_CH_InitData.u32DramDataSize;
    DEBUG_DB_CH(printf(" DB_CH: s_DB_CH_u32WriteData_MaxSize=0x%X\n", s_DB_CH_u32WriteData_MaxSize););

    s_stDB_CH_Info.u32WriteFlashTime = (s_stDB_CH_Info.u32WriteFlashTime + 1);
    DEBUG_DB_CH(printf(" DB_CH: s_DB_CH_u32WriteTime=0x%X\n", s_stDB_CH_Info.u32WriteFlashTime););
}

typedef enum
{
    DB_CH_WRITE_DATA_RESULT_STAY_SAME_STATE,
    DB_CH_WRITE_DATA_RESULT_EXIT_WITH_SUCCESSFUL,
    DB_CH_WRITE_DATA_RESULT_EXIT_WITH_FAIL_AND_RETRY,
    DB_CH_WRITE_DATA_RESULT_EXIT_WITH_FAIL_AND_STOP,
} EnuDB_CH_WriteDataResult;

#endif

void msAPI_DB_CH_Task(void)
{
    U32 u32TaskTimePeriod = 20;

    static U32 s_DB_CH_u32TaskTime = 0;
    static U8 s_u8WriteFailCount = 0;
    static U8 s_DB_CH_u8NewDBIdx = 0;
    static MS_U8 u8EraseBankCount = 0;
    U32 u32Time;
    BOOL bWriteFlashResult = TRUE;



    // Setup task period
    if( s_stDB_CH_Info.eState == E_DB_CH_STATE__ERASE_IN_PROGRESS )
        u32TaskTimePeriod = 100;
    else
        u32TaskTimePeriod = 20;

    // Check time period
    //if( msAPI_Timer_DiffTime_2(s_DB_CH_u32TaskTime, msAPI_Timer_GetTime0()) < 10 )
    if( msAPI_Timer_DiffTime_2(s_DB_CH_u32TaskTime, msAPI_Timer_GetTime0()) < u32TaskTimePeriod )
        return;

    s_DB_CH_u32TaskTime = msAPI_Timer_GetTime0();


    if( (s_stDB_CH_Info.bWriteFlashStart == FALSE)
      &&(_msAPI_DB_CH_Get_State() == E_DB_CH_STATE__IDLE)
      )
        return;



    if( MDrv_SERFLASH_CheckWriteDone() == FALSE )
    {
        printf(" [DB_CH: Flash busy] ");
        return;
    }


    {
        switch( _msAPI_DB_CH_Get_State() )
        {
            default:
                //s_DB_CH_eState = E_DB_CH_STATE__IDLE;
                _msAPI_DB_CH_Set_State(E_DB_CH_STATE__IDLE);
                break;

            case E_DB_CH_STATE__IDLE:
                DEBUG_DB_CH_FLOW(printf(" = [E_DB_CH_STATE__IDLE]\n"););
                if( s_stDB_CH_Info.bWriteFlashStart )
                {
                     _msAPI_DB_CH_Set_State(E_DB_CH_STATE__ERASE_START);
                }
                break;

            //case QUICK_DB_READY:
            case E_DB_CH_STATE__ERASE_START:
                DEBUG_DB_CH_FLOW(printf(" = [E_DB_CH_STATE__ERASE_START]\n"););

                // Decide which bank is the target:
                if( s_stDB_CH_Info.u8CurDataBaseIdx == 0 )
                    s_DB_CH_u8NewDBIdx = 1;
                else
                    s_DB_CH_u8NewDBIdx = 0;

                DEBUG_DB_CH(printf(" DB_CH: u8CurDataBaseIdx=%u, u8NewDBIdx=%u\n", s_stDB_CH_Info.u8CurDataBaseIdx, s_DB_CH_u8NewDBIdx););

                // Disable DB WP
                msAPI_Flash_Set_WP_DB_CH(DISABLE);

                DEBUG_DB_CH(printf(" DB_CH: Erase bank=0x%X\n\n", DB_CH_FLASH_BANK(s_DB_CH_u8NewDBIdx)););
                _msAPI_DB_CH_EraseFlash( DB_CH_FLASH_BANK(s_DB_CH_u8NewDBIdx), FALSE );

                u8EraseBankCount = 1;

                _msAPI_DB_CH_Set_State(E_DB_CH_STATE__ERASE_IN_PROGRESS);
                break;

            //case QUICK_DB_ERASE_IN_PROGRESS:
            case E_DB_CH_STATE__ERASE_IN_PROGRESS:
                DEBUG_DB_CH_FLOW(printf(" = [QUICK_DB_ERASE_IN_PROGRESS]\n"););

                //if (msAPI_MIU_QuickDataBaseCheck() == TRUE)
                {
                    if( u8EraseBankCount >= s_stDB_CH_InitData.u8FlashSaveBankCount ) // If all bank erased?
                    {
                    #if( ENABLE_DB_CH_WRITE_DATA_PER_BANK )
                        msAPI_DB_CH_Init_WriteData();
                    #endif
                        _msAPI_DB_CH_Set_State(E_DB_CH_STATE__WRITE_DATA);

                        u8EraseBankCount = 0;
                    }
                    else
                    {   // Continue Erase...
                        //msAPI_MIU_QuickDataBaseErase(u8DataBaseBank ? (SYSTEM_BANK_DATABASE1+u8EraseBank) : (SYSTEM_BANK_DATABASE0)+u8EraseBank, FALSE);
                        _msAPI_DB_CH_EraseFlash( DB_CH_FLASH_BANK(s_DB_CH_u8NewDBIdx) + u8EraseBankCount, FALSE);
                        u8EraseBankCount ++;
                    }
                }
                break;

        #if( 0 == ENABLE_DB_CH_WRITE_DATA_PER_BANK )
            //case QUICK_DB_ERASE_DONE:
            case E_DB_CH_STATE__WRITE_DATA:
              {
                DEBUG_DB_CH_FLOW(printf(" = [E_DB_CH_STATE__WRITE_DATA]\n"););
                BOOL bWriteDone;

                u32Time = msAPI_Timer_GetTime0();

                s_stDB_CH_Info.u32WriteFlashTime = (s_stDB_CH_Info.u32WriteFlashTime + 1);
                DEBUG_DB_CH(printf(" DB_CH: s_DB_CH_u32WriteTime=0x%X\n", s_stDB_CH_Info.u32WriteFlashTime););

                msAPI_DB_CH_CallBack_BeforeWriteFlash();

                // Write data to flash...
            #if 0//(ENABLE_S2_8M_FLASH&&ENABLE_COMPRESS_DATA)
                iBankStart = s_DB_CH_u8NewDBIdx ? SYSTEM_BANK_DATABASE1_S2 : SYSTEM_BANK_DATABASE0_S2;
                //MApi_CompressData(iBankStart, (!((g_u8QuickDataBase & (QUICK_DB_MASK)) == (QUICK_DB_ERASE_DONE))));
                MApi_CompressData(iBankStart, FALSE); // No need erase
                //msAPI_MIU_QuickDataBaseErase(s_DB_CH_u8NewDBIdx ? VERSION_DB_BANK1 : VERSION_DB_BANK0, TRUE);

                _msAPI_DB_CH_WriteHeaderToFlash(s_DB_CH_u8NewDBIdx);
                bWriteFlashResult = TRUE;

            #else
                bWriteFlashResult = _msAPI_DB_CH_StoreDataBase2Flash(
                                        s_DB_CH_u8NewDBIdx,
                                        s_stDB_CH_InitData.u32DramDataAddr,
                                        s_stDB_CH_InitData.u32DramDataSize );
            #endif

                // Enable WP
                msAPI_Flash_Set_WP_DB_CH(ENABLE);

                // Check write flash result...
                if( FALSE == bWriteFlashResult ) // Write fail
                {
                    printf("\nError: DB_CH: Write data failed!\n");

                    if( s_u8WriteFailCount < 255 )
                    {
                        s_u8WriteFailCount += 1;
                        printf(" DB_CH: s_u8WriteFailCount=%u\n", s_u8WriteFailCount);
                    }

                    // If write failed count < 3, retry write~
                    if( s_u8WriteFailCount < 2 )
                    {
                        bWriteDone = FALSE;
                    }
                    else
                    {
                        // Stop retry ...
                        s_u8WriteFailCount = 0;
                        bWriteDone = TRUE;
                    }
                }
                else // Write successful
                {
                    // Change current DB idx to new one
                    s_stDB_CH_Info.u8CurDataBaseIdx = s_DB_CH_u8NewDBIdx;
                    printf("DB_CH: Write Done~ DB=%u, use %ums\n", s_stDB_CH_Info.u8CurDataBaseIdx, msAPI_Timer_DiffTime_2(u32Time, msAPI_Timer_GetTime0()));

                    s_u8WriteFailCount = 0;
                    bWriteDone = TRUE;
                }

                if( bWriteDone ) // Write finish
                {
                    //g_u8QuickDataBase = ((g_u8QuickDataBase & ~QUICK_DB_MASK) | QUICK_DB_READY);
                    _msAPI_DB_CH_Set_State(E_DB_CH_STATE__IDLE);
                    s_stDB_CH_Info.bWriteFlashStart = FALSE;
                }
                else // Need retry
                {
                    // Write again~
                    printf(" DB_CH: Retry write flash\n");
                    _msAPI_DB_CH_Set_State(E_DB_CH_STATE__ERASE_START);
                }
              }
                break;

        #else

            case E_DB_CH_STATE__WRITE_DATA:
              {
                DEBUG_DB_CH_FLOW(printf(" = [E_DB_CH_STATE__WRITE_DATA]\n"););
                U32 u32DramAddr;
                U32 u32FlashAddr;
                U32 u32CurWriteSize;
                EnuDB_CH_WriteDataResult eWriteDataResult = DB_CH_WRITE_DATA_RESULT_STAY_SAME_STATE;


                u32Time = msAPI_Timer_GetTime0();

                // If write first bank
                if( s_DB_CH_u32WriteData_Count == 0 )
                {
                    msAPI_DB_CH_CallBack_BeforeWriteFlash();
                }


                if( s_DB_CH_bWriteDataDone == FALSE )
                {
                    // Write data to flash...
                    if( (s_DB_CH_u32WriteData_MaxSize - s_DB_CH_u32WriteData_Count) < DB_CH_WRITE_DATA_SIZE_STEP )
                        u32CurWriteSize = (s_DB_CH_u32WriteData_MaxSize - s_DB_CH_u32WriteData_Count);
                    else
                        u32CurWriteSize = DB_CH_WRITE_DATA_SIZE_STEP;

                    u32DramAddr = s_stDB_CH_InitData.u32DramDataAddr + s_DB_CH_u32WriteData_Count;
                    u32FlashAddr = DB_CH_FLASH_BANK(s_DB_CH_u8NewDBIdx)*DB_CH_FLASH_BANK_SIZE + s_DB_CH_u32WriteData_Count;

                    bWriteFlashResult = msAPI_DB_CH_WriteDram2Flash( u32DramAddr, u32FlashAddr, u32CurWriteSize);
                    //printf("DB_CH: Write DB=%u, 0x%X, use %ums\n", s_DB_CH_u8NewDBIdx, s_DB_CH_u32WriteData_Count, msAPI_Timer_DiffTime_2(u32Time, msAPI_Timer_GetTime0()));

                    s_DB_CH_u32WriteData_Count += u32CurWriteSize;

                    // Check if all data is written ...
                    if( s_DB_CH_u32WriteData_Count < s_DB_CH_u32WriteData_MaxSize ) // Not finish yet
                    {
                    }
                    else // All data is written
                    {
                        if( bWriteFlashResult ) // Write flash successful
                        {
                            s_DB_CH_bWriteDataDone = TRUE;
                        }
                    }
                }
                else if( s_DB_CH_bWriteHeaderDone == FALSE )
                {
                    // Write header to flash ...
                    bWriteFlashResult = _msAPI_DB_CH_WriteHeaderToFlash(s_DB_CH_u8NewDBIdx);

                    if( bWriteFlashResult ) // Write flash successful
                    {
                        s_DB_CH_bWriteHeaderDone = TRUE;
                    }
                }

                // After write flash, Check last write flash result...
                if( FALSE == bWriteFlashResult ) // Write fail
                {
                    printf("\nError: DB_CH: Write data failed!\n");

                    if( s_u8WriteFailCount < 255 )
                    {
                        s_u8WriteFailCount += 1;
                        printf(" DB_CH: s_u8WriteFailCount=%u\n", s_u8WriteFailCount);
                    }

                    // If write failed count < 3, retry write~
                    if( s_u8WriteFailCount < 2 )
                    {
                        eWriteDataResult = DB_CH_WRITE_DATA_RESULT_EXIT_WITH_FAIL_AND_RETRY;
                    }
                    else
                    {
                        // Stop retry ...
                        s_u8WriteFailCount = 0;
                        eWriteDataResult = DB_CH_WRITE_DATA_RESULT_EXIT_WITH_FAIL_AND_STOP;
                    }
                }
                else // Write successful
                {
                    s_u8WriteFailCount = 0;

                    // Check if all data is written ...
                    if( s_DB_CH_bWriteDataDone && s_DB_CH_bWriteHeaderDone ) // All data is written
                    {
                        // Change current DB idx to new one
                        s_stDB_CH_Info.u8CurDataBaseIdx = s_DB_CH_u8NewDBIdx;

                        eWriteDataResult = DB_CH_WRITE_DATA_RESULT_EXIT_WITH_SUCCESSFUL;

                        // Enable WP
                        msAPI_Flash_Set_WP_DB_CH(ENABLE);

                        printf("DB_CH: Write Done~ DB=%u, use %ums\n", s_stDB_CH_Info.u8CurDataBaseIdx, msAPI_Timer_DiffTime_2(u32Time, msAPI_Timer_GetTime0()));
                    }
                    else
                    {
                        eWriteDataResult = DB_CH_WRITE_DATA_RESULT_STAY_SAME_STATE;
                    }
                }

                switch(eWriteDataResult)
                {
                    case DB_CH_WRITE_DATA_RESULT_STAY_SAME_STATE:
                        // Continue write data...
                        break;

                    default:
                    case DB_CH_WRITE_DATA_RESULT_EXIT_WITH_SUCCESSFUL:
                    case DB_CH_WRITE_DATA_RESULT_EXIT_WITH_FAIL_AND_STOP:
                        _msAPI_DB_CH_Set_State(E_DB_CH_STATE__IDLE);
                        s_stDB_CH_Info.bWriteFlashStart = FALSE;
                        break;

                    case DB_CH_WRITE_DATA_RESULT_EXIT_WITH_FAIL_AND_RETRY:
                        printf(" DB_CH: Retry write flash\n");
                        _msAPI_DB_CH_Set_State(E_DB_CH_STATE__ERASE_START);
                        break;
                }

              }
                break;

        #endif


        }
    }

}

void msAPI_DB_CH_Print_InitData(void)
{
    printf(" s_stDB_CH_InitData:\n u8FlashBankStart: 0x%X\n", s_stDB_CH_InitData.u8FlashBankStart);
    printf(" .u8FlashSaveBankCount: %u\n",s_stDB_CH_InitData.u8FlashSaveBankCount);
    printf(" .u32DramDataAddr: 0x%X\n", s_stDB_CH_InitData.u32DramDataAddr);
    printf(" .u32DramDataSize: 0x%X\n", s_stDB_CH_InitData.u32DramDataSize);
}

void msAPI_DB_CH_Printf_Variable(void)
{
    if( s_stDB_CH_InitData.u8DebugFlag >= 1 )
    {
        printf("\n=================================\n");
        printf("msAPI_DB_CH_Printf_Variable():\n");

        msAPI_DB_CH_Print_InitData();

        printf(" u8FlashBankStart_0=0x%X\n", s_stDB_CH_Info.u8FlashBankStart_0);
        printf(" u8FlashBankStart_1=0x%X\n", s_stDB_CH_Info.u8FlashBankStart_1);
        printf(" u32CheckDataOffset=0x%X\n", s_stDB_CH_Info.u32CheckDataOffset);
        printf("=================================\n");
    }
}

