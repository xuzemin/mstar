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

#include "msAPI_Flash.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "Utl.h"

#include "msAPI_DB_GEN.h"



#define DEBUG_DB_GEN(x)         //x

#define DEBUG_DB_GEN_LVL(lvl, x)     do { \
    if( s_stDB_GEN_InitData.u8DebugFlag >= lvl ) \
    { \
        x; \
    } \
} while(0)



#define DEBUG_DB_GEN_FLOW(x)    //x

#define DEBUG_DB_GEN_WT(x)  //x

#define DB_GEN_TODO()   printf("\nWarning: %s() todo\n", __FUNCTION__);

//================================================================
#define DB_GEN_CHECK_WRITE_TIME     0
#define DB_GEN_WRITE_TIME_MAX       1000000


//================================================================
#define DB_GEN_FLASH_BANK_SIZE      0x10000ul

#define DB_GEN_INVALID_UNIT_IDX     0xFF

#define DB_GEN_UNIT_STATUS_ERASED   0xFF // 1111-1111b
#define DB_GEN_UNIT_STATUS_EMPTY    0x7F // 0111-1111b
#define DB_GEN_UNIT_STATUS_WRITING  0x3F // 0011-1111b
#define DB_GEN_UNIT_STATUS_GOOD     0x1F // 0001-1111b
//#define DB_GEN_UNIT_STATUS_OBSOLETE 0x0F // 0000-1111b
#define DB_GEN_UNIT_STATUS_BAD      0x00 // 0000-0000b


#define DB_GEN_UNIT_STATUS_UNKNOWN  0x11


#define DB_GEN_UNIT_INFO_SIZE               32
#define DB_GEN_UNIT_INFO_STATUS_OFFSET      31


#define DB_GEN_HEADER_MAGIC_ID      0x123455AA


#define DB_GEN_UINT_FLASH_ADDR(unitIdx)    (DB_GEN_FLASH_BANK_SIZE*s_stDB_GEN_InitData.u8FlashBank + unitIdx*s_stDB_GEN_InitData.u16FlashSaveUnitSize)

#define DB_GEN_UINT_DATA_FLASH_ADDR(unitIdx)    (DB_GEN_UINT_FLASH_ADDR(unitIdx) + 0)
#define DB_GEN_UNIT_INFO_STATUS_ADDR(unitIdx)   (DB_GEN_UINT_FLASH_ADDR(unitIdx) + s_stDB_GEN_Info.u16FlashUnitInfoOffset + DB_GEN_UNIT_INFO_STATUS_OFFSET)
#define DB_GEN_UNIT_HEADER_ADDR(unitIdx)        (DB_GEN_UINT_FLASH_ADDR(unitIdx) + s_stDB_GEN_Info.u16FlashUnitInfoOffset)


typedef enum
{
    E_DB_GEN_STATE__IDLE,
    E_DB_GEN_STATE__WRITE_START,
    E_DB_GEN_STATE__ERASE_FLASH,
    E_DB_GEN_STATE__WAIT_ERASE_DONE,
    E_DB_GEN_STATE__WRITE_DATA,
} EunDB_GEN_State;

typedef struct
{
    // Flash constant info ...
    U8 u8FlashUnitNumPer1Bank;
    U8 u8FlashUnitNumTotal;
    U16 u16FlashUnitInfoOffset;

    // Flash control flag
    U8 u8FlashCurUnitIdx;
    U8 u8FlashNextEmptyUnitIdx;

    // Control ...
    //BOOL bDataChanged;
    BOOL bWriteFlashStart;

    EunDB_GEN_State eState;


    // Debug
    BOOL bEnVerifyWrite;

} Stru_DB_GEN_Info;

static Stru_DB_GEN_Info s_stDB_GEN_Info;

static Stru_DB_GEN_InitData s_stDB_GEN_InitData;

#define DB_EGN_ATTR_PACK  __attribute__((__packed__))

typedef struct
{
    U16 u16CheckSum;

    U32 u32MagicId;
    U32 u32WriteTime;
    U16 u16UnitSize;

    //U8 au8Dummy[23];
} DB_EGN_ATTR_PACK Stru_DB_Gen_Header;
static Stru_DB_Gen_Header s_stDB_GEN_Header;


void _msAPI_DB_GEN_EraseFlash(U8 u8FlashBank, BOOL bWait);
void msAPI_DB_GEN_Print_InitData(void);
void msAPI_DB_GEN_Print_FlashHeader(void);

//===========================================================================

void msAPI_DB_GEN_Init(Stru_DB_GEN_InitData* pstDB_GEN_InitData)
{
    DEBUG_DB_GEN( printf("msAPI_DB_GEN_Init()\n"); );

    s_stDB_GEN_InitData = *pstDB_GEN_InitData;

    DEBUG_DB_GEN( msAPI_DB_GEN_Print_InitData(); );

    if( s_stDB_GEN_InitData.u16FlashSaveUnitSize == 0 )
    {
        printf("\nError: u16FlashSaveUnitSize = %u\n", s_stDB_GEN_InitData.u16FlashSaveUnitSize);
        //return ;
        s_stDB_GEN_InitData.u16FlashSaveUnitSize = 4096;
        printf("Force u16FlashSaveUnitSize to %u\n", s_stDB_GEN_InitData.u16FlashSaveUnitSize);
        msAPI_Timer_Delayms(5000);
    }

    if( s_stDB_GEN_InitData.u16DramDataSize > (s_stDB_GEN_InitData.u16FlashSaveUnitSize-DB_GEN_UNIT_INFO_SIZE) )
    {
        printf("\nError: u16DramDataSize(%u) > u16FlashSaveUnitSize(%u)\n", s_stDB_GEN_InitData.u16DramDataSize, s_stDB_GEN_InitData.u16FlashSaveUnitSize);
        s_stDB_GEN_InitData.u16DramDataSize = s_stDB_GEN_InitData.u16FlashSaveUnitSize - DB_GEN_UNIT_INFO_SIZE;
        printf("Force u16DramDataSize to %u\n", s_stDB_GEN_InitData.u16DramDataSize);
        msAPI_Timer_Delayms(5000);
    }


    if( sizeof(Stru_DB_Gen_Header) > (DB_GEN_UNIT_INFO_SIZE-1) )
    {
        printf("\nError: sizeof(Stru_DB_Gen_Header)=%u >= %u\n", sizeof(Stru_DB_Gen_Header), (DB_GEN_UNIT_INFO_SIZE-1));
        msAPI_Timer_Delayms(5000);
    }


    memset( &s_stDB_GEN_Info, 0, sizeof(Stru_DB_GEN_Info) );

    // Flash constant info ...
    s_stDB_GEN_Info.u8FlashUnitNumPer1Bank = DB_GEN_FLASH_BANK_SIZE / s_stDB_GEN_InitData.u16FlashSaveUnitSize;
    s_stDB_GEN_Info.u8FlashUnitNumTotal = s_stDB_GEN_Info.u8FlashUnitNumPer1Bank * 2;

    // Flash control flag
    s_stDB_GEN_Info.u8FlashCurUnitIdx = DB_GEN_INVALID_UNIT_IDX;
    s_stDB_GEN_Info.u8FlashNextEmptyUnitIdx = DB_GEN_INVALID_UNIT_IDX;

    s_stDB_GEN_Info.u16FlashUnitInfoOffset = s_stDB_GEN_InitData.u16FlashSaveUnitSize - DB_GEN_UNIT_INFO_SIZE;

    // Control ...
    //s_stDB_GEN_Info.bDataChanged = FALSE;
    s_stDB_GEN_Info.bWriteFlashStart = FALSE;

    s_stDB_GEN_Info.eState = E_DB_GEN_STATE__IDLE;

    // Debug
    s_stDB_GEN_Info.bEnVerifyWrite = TRUE;

    // Init header
    memset( &s_stDB_GEN_Header, 0, sizeof(s_stDB_GEN_Header) );
    s_stDB_GEN_Header.u32MagicId = DB_GEN_HEADER_MAGIC_ID;
    s_stDB_GEN_Header.u32WriteTime = 0;
    s_stDB_GEN_Header.u16UnitSize = s_stDB_GEN_InitData.u16FlashSaveUnitSize;

    //printf("sizeof(Stru_DB_Gen_Header)=%u\n", sizeof(Stru_DB_Gen_Header));
    //printf("sizeof(s_stDB_GEN_Header)=%u\n", sizeof(s_stDB_GEN_Header));
}

/*
void MApp_DB_GEN_Set_DataChanged(BOOL bDataChanged)
{
    DEBUG_DB_GEN( printf("MApp_DB_GEN_Set_DataChanged(bDataChanged=%u)\n", bDataChanged); );
    if( bDataChanged )
    {
        s_stDB_GEN_Info.bDataChanged = 1;
    }
    else
    {
        s_stDB_GEN_Info.bDataChanged = 0;
    }
}

BOOL MApp_DB_GEN_Get_DataChanged(void)
{
    return s_stDB_GEN_Info.bDataChanged;
}
*/

U8 _msAPI_DB_GEN_Get_UnitStatus(U8 u8UnitIdx)
{
    U8 u8UnitStatus_Final = 0;

    // Check unit idx
    if( u8UnitIdx >= (s_stDB_GEN_Info.u8FlashUnitNumTotal) )
    {
        return DB_GEN_UNIT_STATUS_UNKNOWN;
    }

    if( FALSE == MDrv_FLASH_Read(DB_GEN_UNIT_INFO_STATUS_ADDR(u8UnitIdx), 1, &u8UnitStatus_Final) )
    {
        printf("\nError: Get_UnitStatus: Read flash faild\n");
        return DB_GEN_UNIT_STATUS_UNKNOWN;
    }

    return u8UnitStatus_Final;
}

BOOL _msAPI_DB_GEN_Set_UnitStatus(U8 u8UnitIdx, U8 u8UnitStatus)
{
    U8 u8UnitStatus_Final;


    DEBUG_DB_GEN(printf("_msAPI_DB_GEN_Set_UnitStatus(u8UnitIdx=%u, u8UnitStatus=%X)\n", u8UnitIdx, u8UnitStatus););

    // Check unit idx
    if( u8UnitIdx >= (s_stDB_GEN_Info.u8FlashUnitNumTotal) )
    {
        printf("\nError: Set_UnitStatus: UnitIdx(%u) error\n", u8UnitIdx);
        return FALSE;
    }

    // Disable WP ?

    // Write to flash
    if( FALSE == MDrv_FLASH_Write(DB_GEN_UNIT_INFO_STATUS_ADDR(u8UnitIdx), 1, &u8UnitStatus) )
    {
        printf("\nError: Set_UnitStatus: Write flash faild. unit=%u, status=0x%X\n", u8UnitIdx, u8UnitStatus);
        return FALSE;
    }


    // Verify
    u8UnitStatus_Final = _msAPI_DB_GEN_Get_UnitStatus(u8UnitIdx);

    if( u8UnitStatus_Final != u8UnitStatus )
    {
        printf("\nError: Set_UnitStatus(%u,0x%X): Verify faild! => 0x%X\n", u8UnitIdx, u8UnitStatus, u8UnitStatus_Final);
        return FALSE;
    }

    return TRUE;
}

BOOLEAN _msAPI_DB_GEN_InitUnit(U8 u8UnitIdxStart, U8 u8UnitNum )
{
    U8 i, u8UnitIdx;
    BOOL bResult = TRUE;
    U8 u8FailCount = 0;

    DEBUG_DB_GEN( printf("_msAPI_DB_GEN_InitUnit(u8UnitIdxStart=%u, u8UnitNum=0x%X)\n", u8UnitIdxStart, u8UnitNum); );

    for( i = 0; i < u8UnitNum; ++i )
    {
        u8UnitIdx = (u8UnitIdxStart + i) % s_stDB_GEN_Info.u8FlashUnitNumTotal;

        bResult = _msAPI_DB_GEN_Set_UnitStatus( u8UnitIdx, DB_GEN_UNIT_STATUS_EMPTY);
        if( bResult == FALSE )
        {
            printf("\nError: InitUnit: Set unit_%u status-empty failed\n", u8UnitIdx);
            _msAPI_DB_GEN_Set_UnitStatus(u8UnitIdx, DB_GEN_UNIT_STATUS_BAD);
            u8FailCount += 1;
        }
    }

    if( u8FailCount )
    {
        printf("DB_GEN: InitUnit: u8FailCount=%u\n", u8FailCount);
    }

    if( u8FailCount == u8UnitNum )
    {
        return FALSE;
    }

    return TRUE;
}

U8 _msAPI_DB_GEN_FindUnit(U8 u8FromUnitIdx, U8 u8UnitStatus)
{
    U8 u8CurCheckIdx;
    U8 u8CheckCount = 0;
    U8 u8CurUnitStatus;

    DEBUG_DB_GEN( printf("_msAPI_DB_GEN_FindUnit(u8FromUnitIdx=%u, u8UnitStatus=0x%X)\n", u8FromUnitIdx, u8UnitStatus); );

    if( u8FromUnitIdx >= (s_stDB_GEN_Info.u8FlashUnitNumTotal-1) )
    {
        u8FromUnitIdx = 0;
    }

    u8CurCheckIdx = u8FromUnitIdx;
    for( u8CheckCount = 0; u8CheckCount < s_stDB_GEN_Info.u8FlashUnitNumTotal; u8CheckCount += 1 )
    {
        u8CurUnitStatus = _msAPI_DB_GEN_Get_UnitStatus(u8CurCheckIdx);

        //printf(" [Check unit-%u = 0x%X] ", u8CurCheckIdx, u8CurUnitStatus);

        if( u8CurUnitStatus == u8UnitStatus )
        {
            return u8CurCheckIdx;
        }

        u8CurCheckIdx = (u8CurCheckIdx + 1) % s_stDB_GEN_Info.u8FlashUnitNumTotal;
    }

/*
    if( u8UnitStatus == DB_GEN_UNIT_STATUS_EMPTY )
    {
    }
    else if( u8UnitStatus == DB_GEN_UNIT_STATUS_GOOD )
    {
    }
*/
    return DB_GEN_INVALID_UNIT_IDX;
}

U16 _msAPI_DB_GEN_CalCheckSum(Stru_DB_Gen_Header* pstDB_Gen_Header )
{
    U16 u16CheckSum = 0x1111;
    U8 i;
    U8* pu8Data = (U8*)pstDB_Gen_Header;

    // Skip checksum ==> i =2
    for( i = 2; i < sizeof(Stru_DB_Gen_Header); ++ i )
    {
        u16CheckSum += pu8Data[i];
    }

    return u16CheckSum;
}

BOOL _msAPI_DB_GEN_Read_Header(U8 u8UnitIdx, Stru_DB_Gen_Header* pstDB_Gen_Header, BOOL bCheckHeaderData)
{
    BOOL bResult = TRUE;

    bResult = MDrv_FLASH_Read(DB_GEN_UNIT_HEADER_ADDR(u8UnitIdx),
                        sizeof(Stru_DB_Gen_Header),
                        (U8*)pstDB_Gen_Header);
    if( FALSE == bResult )
    {
        printf("\nError: Read_Header: Read flash faild\n");
        return FALSE;
    }

    // Check magic id
    if( bCheckHeaderData )
    {
        // Check checksum
        if( pstDB_Gen_Header->u16CheckSum != _msAPI_DB_GEN_CalCheckSum(pstDB_Gen_Header) )
        {
            printf("\nError: Read_Header(unit=%u): Checksum wrong!\n", u8UnitIdx);
            return FALSE;
        }

        if( pstDB_Gen_Header->u32MagicId != DB_GEN_HEADER_MAGIC_ID )
        {
            printf("\nError: Read_Header(unit=%u): MagicId wrong!\n", u8UnitIdx);
            return FALSE;
        }

        if( pstDB_Gen_Header->u16UnitSize != s_stDB_GEN_InitData.u16FlashSaveUnitSize )
        {
            printf("\nError: Read_Header(unit=%u): Unit size wrong(0x%X, 0x%X)!\n", u8UnitIdx, pstDB_Gen_Header->u16UnitSize, s_stDB_GEN_InitData.u16FlashSaveUnitSize );
            return FALSE;
        }

    #if(DB_GEN_CHECK_WRITE_TIME)
        if( pstDB_Gen_Header->u32WriteTime > DB_GEN_WRITE_TIME_MAX )
        {
            printf("\nError: Read_Header(unit=%u): Write time too big(0x%X)!\n", u8UnitIdx, pstDB_Gen_Header->u32WriteTime );
            DEBUG_DB_GEN_WT( msAPI_Flash_PrintData(DB_GEN_UNIT_HEADER_ADDR(u8UnitIdx), 16); );
            return FALSE;
        }
    #endif
    }

    return TRUE;
}

BOOL _msAPI_DB_GEN_Write_Header(U8 u8UnitIdx, Stru_DB_Gen_Header* pstDB_Gen_Header )
{
    BOOL bResult = TRUE;
    Stru_DB_Gen_Header stDB_Gen_Header_tmp;


    // Check write time
#if(DB_GEN_CHECK_WRITE_TIME)
    if( pstDB_Gen_Header->u32WriteTime > DB_GEN_WRITE_TIME_MAX )
    {
        printf("\nError: Write_Header(unit=%u): Write time too big(0x%X)!\n", u8UnitIdx, pstDB_Gen_Header->u32WriteTime );
        //return FALSE;
        //PRINT_CURRENT_LINE();
        //while(1) {}
    }
#endif

    // Update check sum
    pstDB_Gen_Header->u16CheckSum = _msAPI_DB_GEN_CalCheckSum(pstDB_Gen_Header);


    bResult = MDrv_FLASH_Write( DB_GEN_UNIT_HEADER_ADDR(u8UnitIdx),
                                sizeof(Stru_DB_Gen_Header),
                                (U8*)pstDB_Gen_Header );
    if( FALSE == bResult )
    {
        printf("\nError: Write_Header: Write flash faild\n");
        return FALSE;
    }

    // todo: Verify header
    memset( &stDB_Gen_Header_tmp, 0, sizeof(Stru_DB_Gen_Header) );
    if( FALSE == _msAPI_DB_GEN_Read_Header( u8UnitIdx, &stDB_Gen_Header_tmp, FALSE) )
    {
        printf("\nError: Write_Header: Read header faild\n");
        return FALSE;
    }

    // compare data
    {
        U8 i;
        U8* pu8Header1 = (U8*)pstDB_Gen_Header;
        U8* pu8Header2 = (U8*)&stDB_Gen_Header_tmp;

        for( i = 0; i < sizeof(Stru_DB_Gen_Header); i += 1 )
        {
            if( pu8Header1[i] != pu8Header2[i] )
            {
                printf("\nError: Write_Header: Verify faild!\n");
                return FALSE;
            }
        }
    }

    return TRUE;
}

#define DEBUG_FIND_LAST(x)  //x
U8 msAPI_DB_GEN_FindLastGood(void)
{
    U8 u8UnitIdx;
    //U32 u32Time1;
    U8 u8CurUnitStatus;
    U8 u8GoodUnitIdx_Last = DB_GEN_INVALID_UNIT_IDX;
    U8 u8GoodUnitCount = 0;
    U32 u32WriteTime_Last = 0;
    Stru_DB_Gen_Header stDB_Gen_Header_Cur;


    DEBUG_DB_GEN( printf("msAPI_DB_GEN_FindLastGood()\n"); );

    //u32Time1 = MsOS_GetSystemTime();

    memset( &stDB_Gen_Header_Cur, 0, sizeof(Stru_DB_Gen_Header) );

    // Find good unit,
    for( u8UnitIdx = 0; u8UnitIdx < s_stDB_GEN_Info.u8FlashUnitNumTotal; u8UnitIdx += 1 )
    {
        u8CurUnitStatus = _msAPI_DB_GEN_Get_UnitStatus(u8UnitIdx);

        DEBUG_FIND_LAST(printf("unit-%u = 0x%X", u8UnitIdx, u8CurUnitStatus););

        if( u8CurUnitStatus == DB_GEN_UNIT_STATUS_GOOD )
        {
            DEBUG_FIND_LAST(printf(" GOOD "););

            // Read header for check write time
            if( FALSE == _msAPI_DB_GEN_Read_Header( u8UnitIdx, &stDB_Gen_Header_Cur, TRUE) )
            {
                printf("\nError: Read Unit(%u) header faild\n", u8UnitIdx);
                continue;
            }

            u8GoodUnitCount += 1;

            DEBUG_FIND_LAST(printf(" WT=%u(0x%X) ", stDB_Gen_Header_Cur.u32WriteTime,stDB_Gen_Header_Cur.u32WriteTime););

            DEBUG_FIND_LAST(printf(" UnitSize=0x%X ", stDB_Gen_Header_Cur.u16UnitSize););

            // Save cur unit...
            if( (u8GoodUnitCount == 1)
              ||(stDB_Gen_Header_Cur.u32WriteTime > u32WriteTime_Last)
              )
            {
                u8GoodUnitIdx_Last = u8UnitIdx;
                u32WriteTime_Last = stDB_Gen_Header_Cur.u32WriteTime;
            }

        }

        DEBUG_FIND_LAST(printf("\n"););

    }

    //printf("Find Last use %u\n", msAPI_Timer_DiffTime_2(u32Time1, MsOS_GetSystemTime()) );

    DEBUG_FIND_LAST(printf(" u8GoodUnitIdx_Last=%u, u32WriteTime_Last=%u\n", u8GoodUnitIdx_Last, u32WriteTime_Last););

#if 0
    u8GoodUnitIdx1 = _msAPI_DB_GEN_FindUnit(0, DB_GEN_UNIT_STATUS_GOOD);
    DEBUG_DB_GEN( printf(" u8GoodUnitIdx1=%u\n", u8GoodUnitIdx1 ); );
    // If can not find any good unit
    if( u8GoodUnitIdx1 == DB_GEN_INVALID_UNIT_IDX )
    {
        printf("\nError: Can not find any good unit\n");

        // todo: Find last old...

        return DB_GEN_INVALID_UNIT_IDX;
    }

    // Already find one good
    u8GoodUnitCount = 1;


    // Find another good unit
    u8GoodUnitIdx2 = _msAPI_DB_GEN_FindUnit(u8GoodUnitIdx1+1, DB_GEN_UNIT_STATUS_GOOD);
    if( u8GoodUnitIdx2 == u8GoodUnitIdx1 ) // Only one good
    {
        u8GoodUnitIdx2 = DB_GEN_INVALID_UNIT_IDX;
    }
    else // 2 good found
    {
        u8GoodUnitCount = 2;
        DEBUG_DB_GEN( printf(" u8GoodUnitIdx2=%u\n", u8GoodUnitIdx2 ); );
    }

    // Compare 2 unit's writetime
    if( u8GoodUnitCount == 2 )
    {
//        BOOL _msAPI_DB_GEN_Read_Header(U8 u8UnitIdx, Stru_DB_Gen_Header* pstDB_Gen_Header )

    }
#endif

    return u8GoodUnitIdx_Last;
}

BOOL msAPI_DB_GEN_LoadFromFlash(void)
{
    U8 u8GoodUnitIdx;
    Stru_DB_Gen_Header stDB_Gen_Header;


    DEBUG_DB_GEN( printf("msAPI_DB_GEN_LoadFromFlash()\n"); );

    DEBUG_DB_GEN( msAPI_DB_GEN_Print_FlashHeader(); );

    u8GoodUnitIdx = msAPI_DB_GEN_FindLastGood();

    if( DB_GEN_INVALID_UNIT_IDX == u8GoodUnitIdx )
    {
        printf("\nError: Can not find any good unit\n");

        // Erase 1 gen bank
        //msAPI_Flash_WaitWriteDone(3000);

        //_msAPI_DB_GEN_EraseFlash(s_stDB_GEN_InitData.u8FlashBank, TRUE);

        //_msAPI_DB_GEN_InitUnit(0, s_stDB_GEN_Info.u8FlashUnitNumPer1Bank);

        return FALSE;
    }


    // Good unit found ...
    s_stDB_GEN_Info.u8FlashCurUnitIdx = u8GoodUnitIdx;

    DEBUG_DB_GEN( printf("  => Good unit=%u\n", s_stDB_GEN_Info.u8FlashCurUnitIdx ); );

    // Get header
    //DEBUG_DB_GEN( printf(" Get unit header\n" ); );
    memset( &stDB_Gen_Header, 0, sizeof(Stru_DB_Gen_Header) );
    if( FALSE == _msAPI_DB_GEN_Read_Header( s_stDB_GEN_Info.u8FlashCurUnitIdx, &stDB_Gen_Header, TRUE) )
    {
        printf("\nError: Read Unit header: Read flash faild\n");
        return FALSE;
    }
    else
    {
        DEBUG_DB_GEN( printf(" Unit Header: u32MagicId=0x%X, u32WriteTime=%u\n", stDB_Gen_Header.u32MagicId, stDB_Gen_Header.u32WriteTime); );

        printf("=> GoodUnit=%u, WriteTime=%u\n", s_stDB_GEN_Info.u8FlashCurUnitIdx, stDB_Gen_Header.u32WriteTime);

    /*
        if( stDB_Gen_Header.u32MagicId != DB_GEN_HEADER_MAGIC_ID )
        {
            printf("\nError: Header MagicId is wrong!\n");
            return FALSE;
        }
        else
        */
        {
            s_stDB_GEN_Header.u32WriteTime = stDB_Gen_Header.u32WriteTime;
        }
    }

    // Copy flash data to dram
    DEBUG_DB_GEN( printf(" Copy flash data to dram\n" ); );
    msAPI_MIU_Copy( DB_GEN_UINT_DATA_FLASH_ADDR(s_stDB_GEN_Info.u8FlashCurUnitIdx), // flash addr
                    s_stDB_GEN_InitData.u32DramDataAddr, // Dram addr
                    s_stDB_GEN_InitData.u16DramDataSize, // copy size
                    MIU_FLASH2SDRAM );


    return TRUE;
}

void msAPI_DB_GEN_WriteToFlash(void)
{
    DEBUG_DB_GEN( printf("msAPI_DB_GEN_WriteToFlash()\n"); );
    s_stDB_GEN_Info.bWriteFlashStart = TRUE;
}

void msAPI_DB_GEN_WriteToFlash_RightNow(void)
{
    DEBUG_DB_GEN( printf("msAPI_DB_GEN_WriteToFlash_RightNow()\n"); );


    msAPI_DB_GEN_WriteToFlash();
    //s_stDB_GEN_Info.bWriteFlashStart = TRUE;

    while( s_stDB_GEN_Info.bWriteFlashStart
        || (s_stDB_GEN_Info.eState != E_DB_GEN_STATE__IDLE)
         )
    {
#if 1//( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
#endif

        msAPI_DB_GEN_Task();
    }

    DEBUG_DB_GEN( printf("msAPI_DB_GEN_WriteToFlash_RightNow() - end\n"); );
}

void _msAPI_DB_GEN_CallBack_BeforeWriteFlash(void)
{
    if( s_stDB_GEN_InitData.pfCallBack_BeforeWriteFlash )
    {
        s_stDB_GEN_InitData.pfCallBack_BeforeWriteFlash();
    }
}

BOOL _msAPI_DB_GEN_VerifyFlash(U32 u32DramAddr, U32 u32FlashAddr, U32 u32DataSize)
{
    DEBUG_DB_GEN( printf("_msAPI_DB_GEN_VerifyFlash(u32DramAddr=0x%X, u32FlashAddr=0x%X, size=%u)\n", u32DramAddr, u32FlashAddr,u32DataSize); );

    U8 au8TmpBuf[256];
    U16 i;
    U8* p8DramData;
    U32 u32AddrOffset = 0;
    U16 u16CurCheckSize = 0;


    DEBUG_DB_GEN( printf("  Verify flash data ...\n" ); );

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


#define DEBUG_WRITE_TIME(x)     //x
BOOL _msAPI_DB_GEN_WriteDataToFlash(U8 u8OldUnitIdx, U8 u8NewUnitIdx)
{
    BOOL bResult = TRUE;
    DEBUG_WRITE_TIME(U32 au32Time[7];);

    u8OldUnitIdx=u8OldUnitIdx;


    DEBUG_DB_GEN( printf("_msAPI_DB_GEN_WriteDataToFlash(u8OldUnitIdx=%u, u8NewUnitIdx=%u)\n", u8OldUnitIdx, u8NewUnitIdx); );

    DEBUG_WRITE_TIME(au32Time[0] = MsOS_GetSystemTime(););

    // Notify system :  it will write data to flash soon
    _msAPI_DB_GEN_CallBack_BeforeWriteFlash();

    DEBUG_WRITE_TIME(au32Time[1] = MsOS_GetSystemTime(););


    // Disable DB-Gen WP
    msAPI_Flash_Set_WP_DB_GEN(DISABLE);

    DEBUG_WRITE_TIME(au32Time[2] = MsOS_GetSystemTime(););
    // Use do-while for control sw flow easy...
    do
    {
        // Set new nuit status to writing
        bResult = _msAPI_DB_GEN_Set_UnitStatus(u8NewUnitIdx, DB_GEN_UNIT_STATUS_WRITING);
        if( bResult == FALSE )
        {
            printf("\nError: WriteDataToFlash: Set unit status-writing failed\n");
            _msAPI_DB_GEN_Set_UnitStatus(u8NewUnitIdx, DB_GEN_UNIT_STATUS_BAD);

            // Exit write flash sequence...
            break;
        }


        // Write data to flash - new unit
        U32 u32DataVirAddr = MsOS_PA2KSEG0(s_stDB_GEN_InitData.u32DramDataAddr);
        //printf("u32DataVirAddr=0x%X\n", u32DataVirAddr);

        // Flush D-cache
        MsOS_Dcache_Flush( u32DataVirAddr, s_stDB_GEN_InitData.u16DramDataSize );

        // Flush Memory
        MsOS_FlushMemory();

        DEBUG_WRITE_TIME(au32Time[3] = MsOS_GetSystemTime(););

        // Write data to falsh
        bResult = MDrv_FLASH_Write( DB_GEN_UINT_DATA_FLASH_ADDR(u8NewUnitIdx),
                            s_stDB_GEN_InitData.u16DramDataSize,
                            (U8*)MsOS_PA2KSEG1(s_stDB_GEN_InitData.u32DramDataAddr) );
        if( bResult == FALSE )
        {
            printf("\nError: WriteDataToFlash: Write data failed\n");
            _msAPI_DB_GEN_Set_UnitStatus(u8NewUnitIdx, DB_GEN_UNIT_STATUS_BAD);
            // Exit write flash sequence...
            break;
        }

        DEBUG_WRITE_TIME(au32Time[4] = MsOS_GetSystemTime(););

        // Verify data if need ...
        if( s_stDB_GEN_Info.bEnVerifyWrite )
        {
            DEBUG_DB_GEN( printf("  Verify flash data ...\n" ); );
            bResult = _msAPI_DB_GEN_VerifyFlash(
                                s_stDB_GEN_InitData.u32DramDataAddr,
                                DB_GEN_UINT_DATA_FLASH_ADDR(u8NewUnitIdx),
                                s_stDB_GEN_InitData.u16DramDataSize);
            if( bResult == FALSE )
            {
                printf("\nError: Verify data faild\n");
                _msAPI_DB_GEN_Set_UnitStatus(u8NewUnitIdx, DB_GEN_UNIT_STATUS_BAD);
                break; // Exit write flash sequence...
            }

            DEBUG_DB_GEN_LVL( 2, printf("   Verify data OK\n"); );
        }

        DEBUG_WRITE_TIME(au32Time[5] = MsOS_GetSystemTime(););

        // Write unit header to flash
        //s_stDB_GEN_Header.u32MagicId = DB_GEN_HEADER_MAGIC_ID;
        s_stDB_GEN_Header.u32WriteTime += 1;
        bResult = _msAPI_DB_GEN_Write_Header(u8NewUnitIdx, &s_stDB_GEN_Header );
        if( bResult == FALSE )
        {
            printf("\nError: WriteDataToFlash: Write header failed\n");
            _msAPI_DB_GEN_Set_UnitStatus(u8NewUnitIdx, DB_GEN_UNIT_STATUS_BAD);
            // Exit write flash sequence...
            break;
        }


        // Set new nuit status to good
        _msAPI_DB_GEN_Set_UnitStatus(u8NewUnitIdx, DB_GEN_UNIT_STATUS_GOOD);
        if( bResult == FALSE )
        {
            printf("\nError: WriteDataToFlash: Set unit status-good failed\n");
            _msAPI_DB_GEN_Set_UnitStatus(u8NewUnitIdx, DB_GEN_UNIT_STATUS_BAD);
            // Exit write flash sequence...
            break;
        }

        // Set old nuit status to old:
        // Check unit idx
    #if 0
        if( u8OldUnitIdx < (s_stDB_GEN_Info.u8FlashUnitNumTotal) )
        {
            _msAPI_DB_GEN_Set_UnitStatus(u8OldUnitIdx, DB_GEN_UNIT_STATUS_OBSOLETE);
            if( bResult == FALSE )
            {
                printf("\nError: WriteDataToFlash: Set unit status-old failed\n", u8OldUnitIdx);
                _msAPI_DB_GEN_Set_UnitStatus(u8OldUnitIdx, DB_GEN_UNIT_STATUS_BAD);
                // Exit write flash sequence...
                break;
            }
        }
    #endif
    } while(0);

    // Enable DB-Gen WP
    msAPI_Flash_Set_WP_DB_GEN(ENABLE);

    DEBUG_WRITE_TIME(au32Time[6] = MsOS_GetSystemTime(););
    /*
    {
        U8 i;
        for( i = 0; i < 7; ++ i )
        {
            printf("(%u) %u\n", i, au32Time[i]);
        }
    }
    */

    return bResult; // Return with success
}

void _msAPI_DB_GEN_EraseFlash(U8 u8FlashBank, BOOL bWait)
{
    U32 u32FlashAddr;

    DEBUG_DB_GEN_LVL( 1, printf("_msAPI_DB_GEN_EraseFlash(u8Bank=0x%X, wait=%u)\n", u8FlashBank, bWait); );

    u32FlashAddr = DB_GEN_FLASH_BANK_SIZE * u8FlashBank;

    //DEBUG_DB_GEN( printf(" => u32FlashAddr=0x%X\n", u32FlashAddr); );
    //DEBUG_DB_GEN_LVL( 1, printf("Erase flash bank=0x%X\n", u8EraseBank); );

    // Disable DB-Gen WP
    msAPI_Flash_Set_WP_DB_GEN(DISABLE);

    // Erase falsh and no wait
    MDrv_FLASH_AddressErase(u32FlashAddr, DB_GEN_FLASH_BANK_SIZE, bWait);

    // Enable write protect
}

void msAPI_DB_GEN_Task(void)
{
    static U32 s_u32TaskTime = 0;
    U32 u32TaskTimePeriod = 20;
    static U8 s_u8WriteFailCount = 0;
    static U8 s_u8LastEraseBank;
    static U8 s_u8LastEraseUnitIdxStart;
    static U8 s_u8LastEraseUnitNum;




    // Setup task period
    if( s_stDB_GEN_Info.eState == E_DB_GEN_STATE__WAIT_ERASE_DONE )
        u32TaskTimePeriod = 100;
    else
        u32TaskTimePeriod = 20;


    // Check time period
    if( msAPI_Timer_DiffTime_2(s_u32TaskTime, msAPI_Timer_GetTime0()) < u32TaskTimePeriod )
    //if( msAPI_Timer_DiffTime_2(s_u32TaskTime, msAPI_Timer_GetTime0()) < 20 )
        return;

    s_u32TaskTime = msAPI_Timer_GetTime0();


    if( (s_stDB_GEN_Info.bWriteFlashStart == FALSE)
      &&(s_stDB_GEN_Info.eState == E_DB_GEN_STATE__IDLE )
      )
        return;


    // If flash is busy, don't do anything
    if( MDrv_SERFLASH_CheckWriteDone() == FALSE )
    {
        DEBUG_DB_GEN_LVL( 1, printf("GEN: Flash busy\n"); );
        return;
    }

    switch( s_stDB_GEN_Info.eState )
    {
        case E_DB_GEN_STATE__IDLE:
            //DEBUG_DB_GEN_FLOW( printf("[GEN - IDLE]\n"););

            if( s_stDB_GEN_Info.bWriteFlashStart )
            {
                s_stDB_GEN_Info.eState = E_DB_GEN_STATE__WRITE_START;
            }

            break;

        case E_DB_GEN_STATE__WRITE_START:
            DEBUG_DB_GEN_FLOW( printf("[GEN - WRITE_START]\n"););

            DEBUG_DB_GEN(printf(" .u8FlashCurUnitIdx=%u\n", s_stDB_GEN_Info.u8FlashCurUnitIdx ););

            // Find empty unit ...
            DEBUG_DB_GEN( printf("  Find empty unit...\n"); );
            s_stDB_GEN_Info.u8FlashNextEmptyUnitIdx = _msAPI_DB_GEN_FindUnit(s_stDB_GEN_Info.u8FlashCurUnitIdx + 1, DB_GEN_UNIT_STATUS_EMPTY);
            DEBUG_DB_GEN( printf("   Empty UnitIdx=%u\n", s_stDB_GEN_Info.u8FlashNextEmptyUnitIdx ); );

            if( DB_GEN_INVALID_UNIT_IDX == s_stDB_GEN_Info.u8FlashNextEmptyUnitIdx )
            {
                // Can't find any empty unit
                printf(" Can't find any empty unit, need to erase\n" );

                // goto erase state
                s_stDB_GEN_Info.eState = E_DB_GEN_STATE__ERASE_FLASH;
            }
            else
            {
                // goto write data
                s_stDB_GEN_Info.eState = E_DB_GEN_STATE__WRITE_DATA;
            }
            break;

        case E_DB_GEN_STATE__ERASE_FLASH:
            DEBUG_DB_GEN_FLOW( printf("[GEN - ERASE_FLASH]\n"););
            {
                // Check what bank should erase...

                // If current unit is in first bank, erase 2nd bank
                if( s_stDB_GEN_Info.u8FlashCurUnitIdx < s_stDB_GEN_Info.u8FlashUnitNumPer1Bank )
                {
                    s_u8LastEraseBank = s_stDB_GEN_InitData.u8FlashBank + 1;
                    s_u8LastEraseUnitIdxStart = s_stDB_GEN_Info.u8FlashUnitNumPer1Bank;
                    s_u8LastEraseUnitNum = s_stDB_GEN_Info.u8FlashUnitNumPer1Bank;
                }
                else // current unit is in second bank, erase 1st  bank
                {
                    s_u8LastEraseBank = s_stDB_GEN_InitData.u8FlashBank;
                    s_u8LastEraseUnitIdxStart = 0;
                    s_u8LastEraseUnitNum = s_stDB_GEN_Info.u8FlashUnitNumPer1Bank;
                }

                DEBUG_DB_GEN_LVL( 1, printf("Erase flash bank=0x%X\n", s_u8LastEraseBank); );
                _msAPI_DB_GEN_EraseFlash(s_u8LastEraseBank, FALSE);
            }

            // goto write_start
            s_stDB_GEN_Info.eState = E_DB_GEN_STATE__WAIT_ERASE_DONE;

            break;

        case E_DB_GEN_STATE__WAIT_ERASE_DONE:
            DEBUG_DB_GEN( printf("[GEN - WAIT_ERASE_DONE]\n"););

            // Set unit to empty
            if( FALSE == _msAPI_DB_GEN_InitUnit(s_u8LastEraseUnitIdxStart, s_u8LastEraseUnitNum) )
            {
                printf("\nError: DB_GEN: InitUnit fail! (Please check WP)\n");
                s_stDB_GEN_Info.eState = E_DB_GEN_STATE__IDLE;
                s_stDB_GEN_Info.bWriteFlashStart = FALSE;
            }
            else
            { // Init unit OK
                s_stDB_GEN_Info.eState = E_DB_GEN_STATE__WRITE_START;
            }

            break;

        case E_DB_GEN_STATE__WRITE_DATA:
            DEBUG_DB_GEN_FLOW( printf("[GEN - WRITE_DATA]\n"););
            {
                BOOL bWriteDone = TRUE;
                U32 u32GenWriteTime = MsOS_GetSystemTime();

                // write data to flash
                if( FALSE == _msAPI_DB_GEN_WriteDataToFlash( s_stDB_GEN_Info.u8FlashCurUnitIdx,
                                                           s_stDB_GEN_Info.u8FlashNextEmptyUnitIdx ) )
                {
                    printf("\nError: Write flash failed!\n");

                    if( s_u8WriteFailCount < 255 )
                    {
                        s_u8WriteFailCount += 1;
                    }

                    // If write failed count < 2, retry write~
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
                else // Write flash successful
                {
                    s_u8WriteFailCount = 0;

                    // Change current unit idx to new unit
                    s_stDB_GEN_Info.u8FlashCurUnitIdx = s_stDB_GEN_Info.u8FlashNextEmptyUnitIdx;
                    DEBUG_DB_GEN_LVL( 1, printf(" DB_GEN: Write flash done~ => UnitIdx=%u, wt=%u, use %ums\n", s_stDB_GEN_Info.u8FlashCurUnitIdx, s_stDB_GEN_Header.u32WriteTime, msAPI_Timer_DiffTime_2(u32GenWriteTime, MsOS_GetSystemTime())); );
                    DEBUG_DB_GEN( msAPI_DB_GEN_Print_FlashHeader(); );
                    bWriteDone = TRUE;
                }

                if( bWriteDone )
                {
                    // !!! Very important
                    // Must clear dataChanged flag
                    //MApp_DB_GEN_Set_DataChanged(FALSE);

                    s_stDB_GEN_Info.bWriteFlashStart = FALSE;

                    // goto idle
                    s_stDB_GEN_Info.eState = E_DB_GEN_STATE__IDLE;
                }
                else
                {
                    // Write again~
                    printf(" ==> Retry write flash\n");
                    s_stDB_GEN_Info.eState = E_DB_GEN_STATE__WRITE_START;
                    //msAPI_DB_GEN_Print_FlashHeader();
                }
            }
            break;

        default:
            printf("\nError: s_stDB_GEN_Info.eState=%u\n", s_stDB_GEN_Info.eState);
            msAPI_Timer_Delayms(5000);
            s_stDB_GEN_Info.eState = E_DB_GEN_STATE__IDLE;
            break;
    }
}

void msAPI_DB_GEN_Print_InitData(void)
{
    printf(" s_stDB_GEN_InitData:\n u8FlashBank: 0x%X\n", s_stDB_GEN_InitData.u8FlashBank);
    printf(" .u16FlashSaveUnitSize: %u\n",s_stDB_GEN_InitData.u16FlashSaveUnitSize);
    printf(" .u32DramDataAddr: 0x%X\n", s_stDB_GEN_InitData.u32DramDataAddr);
    printf(" .u16DramDataSize: %u\n", s_stDB_GEN_InitData.u16DramDataSize);
}

void msAPI_DB_GEN_Printf_Variable(void)
{
    if( s_stDB_GEN_InitData.u8DebugFlag >= 1 )
    {
        printf("\n=================================\n");
        printf("msAPI_DB_GEN_Printf_Variable():\n");

        msAPI_DB_GEN_Print_InitData();

        printf(" u8FlashUnitNumPer1Bank=%u\n", s_stDB_GEN_Info.u8FlashUnitNumPer1Bank);
        printf(" u8FlashUnitNumTotal=%u\n", s_stDB_GEN_Info.u8FlashUnitNumTotal);
        printf(" u16FlashUnitInfoOffset=0x%X\n", s_stDB_GEN_Info.u16FlashUnitInfoOffset);
        printf("=================================\n");
    }
}

const char* _msAPI_DB_GEN_Get_StatusString(U8 u8Status)
{
    switch(u8Status)
    {
        case DB_GEN_UNIT_STATUS_ERASED:
            return "ERASED";
        case DB_GEN_UNIT_STATUS_EMPTY:
            return "EMPTY";
        case DB_GEN_UNIT_STATUS_WRITING:
            return "WRITING";
        case DB_GEN_UNIT_STATUS_GOOD:
            return "GOOD";
        //case DB_GEN_UNIT_STATUS_OBSOLETE:
          //  return "OLD";
        case DB_GEN_UNIT_STATUS_BAD:
            return "BAD";
        case DB_GEN_UNIT_STATUS_UNKNOWN:
            return "UNKNOWN";
        default:
            break;
    }

    return "INVALID";
}

void msAPI_DB_GEN_Print_FlashHeader(void)
{
    U8 i;
    U8 u8Status;
    Stru_DB_Gen_Header stGenHeader;

    memset( &stGenHeader, 0, sizeof(Stru_DB_Gen_Header) );

    printf("Flash status:\n" );

    for( i = 0; i < s_stDB_GEN_Info.u8FlashUnitNumTotal; ++ i )
    {
        u8Status = _msAPI_DB_GEN_Get_UnitStatus(i);
        _msAPI_DB_GEN_Read_Header(i, &stGenHeader, FALSE);

        printf("(%02u) %02X(%s)", i, u8Status, _msAPI_DB_GEN_Get_StatusString(u8Status) );
        if( (u8Status == DB_GEN_UNIT_STATUS_GOOD)
          //||(u8Status == DB_GEN_UNIT_STATUS_OBSOLETE)
          ||(u8Status == DB_GEN_UNIT_STATUS_BAD)
          )
        {
            printf(" 0x%X ", stGenHeader.u32MagicId);
            printf(" %u ", stGenHeader.u32WriteTime);
        }
        printf("\n");
    }
}


