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
//#include "MApp_SaveData.h"

#include "msAPI_DB_GEN.h"


//=============================================================


#define DEBUG_DB_GEN(y)             //y

#define FLASH_BUF_SIZE              1024

#define QUICK_DB_GENST_EMPTY        0xFF
#define QUICK_DB_GENST_WRITING      0x7F
#define QUICK_DB_GENST_GOOD         0x3F
#define QUICK_DB_GENST_OBSOLETE     0x1F

#define QUICK_DB_GENST_INVALID_IDX  0xFF

#define QUICK_DB_GENST_UPDATE             0x80
#define QUICK_DB_GENST_MODIFIED           0x40
#define QUICK_DB_GENST_MASK               0x30
#define QUICK_DB_GENST_READY              0x10
#define QUICK_DB_GENST_ERASE_IN_PROGRESS  0x20
#define QUICK_DB_GENST_ERASE_DONE         0x30




//extern U32 u32QuickDatabaseTimer;

static U8 g_u8QuickDataBase_Gen;

static U32 g_SYSTEM_BANK_SIZE;

static U8 g_QUICK_DB_GENSETTING_BANK;
static U16 g_QUICK_DB_GENST_SIZE;
static U8 g_QUICK_DB_GENST_NUM;


static U16 g_u16QuickGenSettingIdx;

static BOOL g_bGenSettingStoreUseNewMethod = 1;

static U32 g_u32DataBaseAddr;
static U32 g_RM_GEN_USAGE;


static Stru_DB_GEN_InitData s_stDB_GEN_InitData;

typedef enum
{
	ERASE_BANK0 = 0,
	ERASE_BANK1 = 1,
	ERASE_NUM   = 2
}ERASE_GENSETTING_BANK;
static ERASE_GENSETTING_BANK g_u8EraseGenSettingBank;

//=============================================================
// void msAPI_MIU_CheckGenStateFlag(U16 u16GenIndex);
// void msAPI_MIU_QuickGenSettingErase(U8 u8Bank, U8 u8Wait);


void MApp_DB_SaveGenSetting(void);
void MApp_DB_SaveNowGenSetting(void);

void msAPI_MIU_QuickGenSettingLoad(U8 u8Bank);

void MApp_DB_QuickGenSettingMonitor(void);


BOOL msAPI_Flash_CheckFlash(void);

void MApp_DB_GEN_Print_InitData(void);

#define g_bOpenGenstStoreDBG    0

//=============================================================

void msAPI_DB_GEN_Init(Stru_DB_GEN_InitData* pstDB_GEN_InitData)
{
    DEBUG_DB_GEN( printf("msAPI_DB_GEN_Init()\n"); );

    s_stDB_GEN_InitData = *pstDB_GEN_InitData;

    DEBUG_DB_GEN( MApp_DB_GEN_Print_InitData(); );

    if( s_stDB_GEN_InitData.u16FlashSaveUnitSize == 0 )
    {
        printf("\nError: u16FlashSaveUnitSize=%x\n", s_stDB_GEN_InitData.u16FlashSaveUnitSize);
        s_stDB_GEN_InitData.u16FlashSaveUnitSize = 4096;
    }

    // Clear high nibble
    g_u8QuickDataBase_Gen = 0;

    g_u16QuickGenSettingIdx = QUICK_DB_GENST_INVALID_IDX;
    g_SYSTEM_BANK_SIZE = SYSTEM_BANK_SIZE;

    g_QUICK_DB_GENSETTING_BANK = s_stDB_GEN_InitData.u8FlashBank;
    g_QUICK_DB_GENST_SIZE = s_stDB_GEN_InitData.u16FlashSaveUnitSize;

    g_u32DataBaseAddr = s_stDB_GEN_InitData.u32DramDataAddr;
    g_RM_GEN_USAGE = s_stDB_GEN_InitData.u16DramDataSize;

    //g_QUICK_DB_GENST_NUM = QUICK_DB_GENST_NUM;
    g_QUICK_DB_GENST_NUM = 0x10000 / g_QUICK_DB_GENST_SIZE * 2;
}

BOOL msAPI_DB_GEN_LoadFromFlash(void)
{
    BOOL bResult = FALSE;

    bResult = msAPI_Flash_CheckFlash();

    if(g_u16QuickGenSettingIdx == 1)
    {
        g_u8EraseGenSettingBank = ERASE_BANK0;
    }

    g_u8QuickDataBase_Gen |= QUICK_DB_GENST_READY;

    return bResult;
}

void msAPI_DB_GEN_Set_DataChanged(BOOL bDataChanged)
{
    if( bDataChanged )
    {
        g_u8QuickDataBase_Gen |= QUICK_DB_GENST_MODIFIED;
    }
    else
    {
        g_u8QuickDataBase_Gen &= (~QUICK_DB_GENST_MODIFIED);
    }
}

BOOL msAPI_DB_GEN_Get_DataChanged(void)
{
    if( g_u8QuickDataBase_Gen & QUICK_DB_GENST_MODIFIED )
        return TRUE;

    return FALSE;
}

void msAPI_DB_GEN_WriteToFlash(void)
{
    //MApp_DB_SaveGenSetting();
    msAPI_DB_GEN_Set_DataChanged(TRUE);
}

void msAPI_DB_GEN_WriteToFlash_RightNow(void)
{
    //store to flash immediately
//    msAPI_Flash_EraseGensettingBank();

    MApp_DB_SaveNowGenSetting();
}

void msAPI_DB_GEN_Task(void)
{
    static U32 s_u32TaskTime = 0;


    // Check time period
    if( msAPI_Timer_DiffTime_2(s_u32TaskTime, msAPI_Timer_GetTime0()) < 50 )
        return;

    s_u32TaskTime = msAPI_Timer_GetTime0();


    // If flash is busy, don't do anything
    if( MDrv_SERFLASH_CheckWriteDone() == FALSE )
    {
        DEBUG_DB_GEN( printf("GEN: Flash busy\n"); );
        return;
    }

    MApp_DB_QuickGenSettingMonitor();
}

void _msAPI_DB_GEN_CallBack_BeforeWriteFlash(void)
{
    if( s_stDB_GEN_InitData.pfCallBack_BeforeWriteFlash )
    {
        s_stDB_GEN_InitData.pfCallBack_BeforeWriteFlash();
    }
}


/******************************************************************************/
/// API for MIU Store Database::
/// Copy database information from SDRAM to flash
/// @param u32srcaddr \b IN SDRAM address for Database information
/// @param s32size \b IN Database information size
/******************************************************************************/
void msAPI_MIU_QuickGenSettingLoad(U8 u8Bank)    // SRAM2Flash
{
    U32 dst0,dst1;
    U32 dst;
    U16 count;
    U8 *flash_buf;
    U8 u8i;

    g_u16QuickGenSettingIdx = QUICK_DB_GENST_INVALID_IDX;

    flash_buf = (U8*)msAPI_Memory_Allocate(FLASH_BUF_SIZE, BUF_ID_FLASH);
    if (flash_buf == NULL)
    {
        __ASSERT(0);
        printf("malloc flash_buf fail!\r\n");
        return;
    }

    //printf("flash_buf=%X\n", (U32)flash_buf);

    if(g_bGenSettingStoreUseNewMethod)
    {
        dst0 = (g_SYSTEM_BANK_SIZE * u8Bank);
        dst1 = (g_SYSTEM_BANK_SIZE * (u8Bank+1));
        count = g_QUICK_DB_GENST_NUM/2;
    }
    else
    {
        dst = (g_SYSTEM_BANK_SIZE * u8Bank);
        count = g_QUICK_DB_GENST_NUM;
    }

    if(g_bGenSettingStoreUseNewMethod)
    {
        MDrv_FLASH_Read(dst0,count, flash_buf);
        MDrv_FLASH_Read(dst1,count, &flash_buf[count]);
    }
    else
    {
        MDrv_FLASH_Read(dst,count, flash_buf);
    }

    if(g_bGenSettingStoreUseNewMethod)
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("\nLoadUnitFlag = ");
            for(u8i = 0; u8i<g_QUICK_DB_GENST_NUM; u8i++)
            {
                if(u8i == 0 || u8i == g_QUICK_DB_GENST_NUM/2)
                    printf("\n");
                printf("0x%X ", flash_buf[u8i]);

            }
            printf("\n");
        }

        for(u8i = 1; u8i<g_QUICK_DB_GENST_NUM; u8i++)
        {
            if(u8i == (g_QUICK_DB_GENST_NUM/2))
            {
                u8i = (g_QUICK_DB_GENST_NUM/2) + 1;
            }

            if(flash_buf[u8i] == QUICK_DB_GENST_GOOD)
            {
               if(u8i < g_QUICK_DB_GENST_NUM/2)
               {
                   g_u16QuickGenSettingIdx = 2*u8i - 1;
               }
               else
               {
                   g_u16QuickGenSettingIdx = (u8i - g_QUICK_DB_GENST_NUM/2)*2;
               }
               break;
            }
        }
        if(g_bOpenGenstStoreDBG)
        {
            printf("load u8i(%d),GenSettingIdx(%d) \r\n",u8i,g_u16QuickGenSettingIdx);
        }
    }
    else
    {
        for(u8i = 1; u8i<g_QUICK_DB_GENST_NUM; u8i++)
        {
           if(flash_buf[u8i] == QUICK_DB_GENST_GOOD)
           {
               g_u16QuickGenSettingIdx = u8i;
               break;
           }
        }
    }

    MSAPI_MEMORY_FREE(flash_buf, BUF_ID_FLASH);
}

void msAPI_MIU_QuickGenSettingErase(U8 u8Bank, U8 u8Wait)
{
    U32 dst;

    dst = g_SYSTEM_BANK_SIZE * u8Bank;
    printf("msAPI_MIU_QuickGenSettingErase, dst=0x%Lx \r\n", (U32)dst);

    // Disable DB-Gen WP
    msAPI_Flash_Set_WP_DB_GEN(DISABLE);


    MDrv_FLASH_AddressErase(dst, g_SYSTEM_BANK_SIZE, u8Wait);
}

BOOL msAPI_Flash_CheckFlash(void)
{
    BOOL bResult = FALSE;

/*
    if(g_bOpenGenstStoreDBG)
    {
        MApp_Printf_Flash_Variable();
    }
*/
    // Find good unit on flash ==> g_u16QuickGenSettingIdx
    msAPI_MIU_QuickGenSettingLoad(g_QUICK_DB_GENSETTING_BANK);

    // If good unit found
    if( g_u16QuickGenSettingIdx != QUICK_DB_GENST_INVALID_IDX )
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("GenSetting OK!\n");
        }

        if(g_bGenSettingStoreUseNewMethod)
        {
            if(g_u16QuickGenSettingIdx%2)
            {
                msAPI_MIU_Copy(
                       g_SYSTEM_BANK_SIZE*g_QUICK_DB_GENSETTING_BANK+((U32)g_QUICK_DB_GENST_SIZE * (U32)(g_u16QuickGenSettingIdx/2 + 1)),
                       g_u32DataBaseAddr,
                       g_RM_GEN_USAGE,
                       MIU_FLASH2SDRAM);
            }
            else
            {
                 msAPI_MIU_Copy(
                    g_SYSTEM_BANK_SIZE*(g_QUICK_DB_GENSETTING_BANK+1)+((U32)g_QUICK_DB_GENST_SIZE * (U32)(g_u16QuickGenSettingIdx/2)),
                    g_u32DataBaseAddr,
                    g_RM_GEN_USAGE,
                    MIU_FLASH2SDRAM);
            }
        }
        else
        {
              msAPI_MIU_Copy(
                g_SYSTEM_BANK_SIZE*g_QUICK_DB_GENSETTING_BANK+((U32)g_QUICK_DB_GENST_SIZE * (U32)(g_u16QuickGenSettingIdx)),
                g_u32DataBaseAddr,
                g_RM_GEN_USAGE,
                MIU_FLASH2SDRAM);
        }

        bResult = TRUE;

        //MApp_LoadGenSetting();
    }
    else // Can not find any good unit
    {
        bResult = FALSE;

        if(g_bOpenGenstStoreDBG)
        {
            printf("GenSetting NG! Reset \r\n");
        }

        //MApp_InitGenSetting();

        msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK, TRUE);
        msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK+1, TRUE);

        g_u16QuickGenSettingIdx = 0;
        if(g_bOpenGenstStoreDBG)
        {
            printf("\n----msAPI_Flash_CheckFlash----\n");
        }
        //MApp_DB_SaveGenSetting();
    }

    return bResult;
}


void msAPI_MIU_CheckGenStateFlag(U16 u16GenIndex)//Check Two Good Version Patch
{
    U32 dst;
    U8 ucByte;
    U8 u8i;
    U8 u8Bank = g_QUICK_DB_GENSETTING_BANK;

    for(u8i = 1; u8i<g_QUICK_DB_GENST_NUM; u8i++)
    {
        if(u8i%2)
            dst = (g_SYSTEM_BANK_SIZE * u8Bank) + (u8i/2 + 1);
        else
            dst = (g_SYSTEM_BANK_SIZE * (u8Bank + 1)) + (u8i/2);
        MDrv_FLASH_Read(dst, 1, &ucByte);
        if(g_bOpenGenstStoreDBG)
        {
            printf("\nFlag[%d][0x%X] = 0x%X ", u8i, dst, ucByte);
            if(u8i == u16GenIndex)
                printf("----is CurIndex!", ucByte);
        }
        if(u8i == u16GenIndex) continue;

        if(ucByte!=0xFF && ucByte==QUICK_DB_GENST_GOOD)
        {
            ucByte = QUICK_DB_GENST_OBSOLETE;
            MDrv_FLASH_Write(dst, 1, &ucByte);
            if(g_bOpenGenstStoreDBG)
            {
                printf("\n[WAMING: Find GOOD Index]WamingIndex=%d, CurIndex=%d, Address=0x%X\n", u8i, u16GenIndex, dst);
            }
        }
    }
}

/******************************************************************************/
/// API for MIU Store Database::
/// Copy database information from SDRAM to flash
/// @param u32srcaddr \b IN SDRAM address for Database information
/// @param s32size \b IN Database information size
/******************************************************************************/
void msAPI_MIU_QuickGenSettingWrite(U8 u8Bank, U32 u32srcaddr, S32 s32size)    // SRAM2Flash
{
    U32 dst;
    U32 count;
    U8 *flash_buf;


    printf("msAPI_MIU_QuickGenSettingWrite( u8Bank=0x%X, u32srcaddr=0x%X, s32size=%d)\n", u8Bank, u32srcaddr, s32size );

    flash_buf = (U8*)msAPI_Memory_Allocate(FLASH_BUF_SIZE, BUF_ID_FLASH);
    if (flash_buf == NULL)
    {
        __ASSERT(0);
        printf("malloc flash_buf fail!\r\n");
        return;
    }

    if(g_bOpenGenstStoreDBG)
    {
        printf("Store2Flash,src=0x%Lx,dst=0x%Lx,sz=0x%Lx\n", u32srcaddr, (U32)(g_SYSTEM_BANK_SIZE * u8Bank), s32size);
    }

    // Notify system :  it will write data to flash soon
    _msAPI_DB_GEN_CallBack_BeforeWriteFlash();

    // Disable DB-Gen WP
    msAPI_Flash_Set_WP_DB_GEN(DISABLE);


    if(g_bGenSettingStoreUseNewMethod)
    {
        if(g_u16QuickGenSettingIdx%2)
        {
            dst = (g_SYSTEM_BANK_SIZE * u8Bank) + ((U32)g_QUICK_DB_GENST_SIZE * (U32)(g_u16QuickGenSettingIdx/2 + 1));
        }
        else
        {
            dst = (g_SYSTEM_BANK_SIZE * u8Bank) + ((U32)g_QUICK_DB_GENST_SIZE * (U32)(g_u16QuickGenSettingIdx/2));
        }

        if(g_bOpenGenstStoreDBG)
        {
            printf("\r\n [GenSettingWrite u8Bank_00]:0x%X---dst=0x%X\n", u8Bank, dst);
        }
    }
    else
    {
        dst = (g_SYSTEM_BANK_SIZE * u8Bank) + ((U32)g_QUICK_DB_GENST_SIZE * (U32)g_u16QuickGenSettingIdx);
    }


    // TODO: Set unit status to writing


    while (s32size > 0)
    {
        count = MIN(s32size, FLASH_BUF_SIZE);

        memcpy(flash_buf, (void*)_PA2VA(u32srcaddr), count);
        u32srcaddr += count;
        MDrv_FLASH_Write(dst,count, flash_buf);
        dst += count;
        s32size -= count;
    }

    //
    //=====
    if(g_bGenSettingStoreUseNewMethod)
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("\r\n Write g_u16QuickGenSettingIdx:%d\n",g_u16QuickGenSettingIdx);
            printf("\r\n [GenSettingWrite u8Bank_11]:0x%X\n", u8Bank);
        }
        if(g_u16QuickGenSettingIdx%2)
        {
            dst = (g_SYSTEM_BANK_SIZE * u8Bank) + (g_u16QuickGenSettingIdx/2 + 1);
            flash_buf[0] = QUICK_DB_GENST_GOOD;
            count = 1;
            MDrv_FLASH_Write(dst, count, flash_buf);
            if(g_bOpenGenstStoreDBG)
            {
                printf("\r\n a [GOOD]VersionAddr dst1[%x]\n",dst);
            }

            if(g_u16QuickGenSettingIdx != 1)
                dst = (g_SYSTEM_BANK_SIZE * (u8Bank+1)) + (g_u16QuickGenSettingIdx/2);
            else
                dst = (g_SYSTEM_BANK_SIZE * (u8Bank+1)) + ((g_QUICK_DB_GENST_NUM-2)/2);
            flash_buf[0] = QUICK_DB_GENST_OBSOLETE;
            count = 1;
            MDrv_FLASH_Write(dst, count, flash_buf);
            if(g_bOpenGenstStoreDBG)
            {
                printf("\r\n a [OBSOLETE]VersionAddr dst0[%x]\n",dst);
            }
        }
        else
        {
            dst = (g_SYSTEM_BANK_SIZE * u8Bank) + (g_u16QuickGenSettingIdx/2);
            flash_buf[0] = QUICK_DB_GENST_GOOD;
            count = 1;
            MDrv_FLASH_Write(dst, count, flash_buf);
            if(g_bOpenGenstStoreDBG)
            {
                printf("\r\n b [GOOD]VersionAddr dst1[%x]\n",dst);
            }

            dst = (g_SYSTEM_BANK_SIZE * (u8Bank-1)) + (g_u16QuickGenSettingIdx/2);
            flash_buf[0] = QUICK_DB_GENST_OBSOLETE;
            count = 1;
            MDrv_FLASH_Write(dst, count, flash_buf);
            if(g_bOpenGenstStoreDBG)
            {
                printf("\r\n b [OBSOLETE]VersionAddr dst0[%x]\n",dst);
            }
        }

        msAPI_MIU_CheckGenStateFlag(g_u16QuickGenSettingIdx);
    }
    else
    {
        dst = (g_SYSTEM_BANK_SIZE * u8Bank) + (g_u16QuickGenSettingIdx - 1);
        flash_buf[0] = QUICK_DB_GENST_OBSOLETE;
        flash_buf[1] = QUICK_DB_GENST_GOOD;
        count = 2;
        MDrv_FLASH_Write(dst, count, flash_buf);
    }

    //=====

    // Enable DB-Gen WP
    msAPI_Flash_Set_WP_DB_GEN(ENABLE);


    MSAPI_MEMORY_FREE(flash_buf, BUF_ID_FLASH);
}

//*************************************************************************
//Function name:        MApp_DB_SaveNowGenSetting
//Passing parameter:    none
//Return parameter:     none
//Description:          Save database from SDRAM to FLASH
//*************************************************************************
void MApp_DB_SaveNowGenSetting(void)
{
    U32 u32Timer;


    if(g_bOpenGenstStoreDBG)
    {
        printf("MApp_DB_SaveNowGenSetting()\n");
    }

    u32Timer = msAPI_Timer_GetTime0();
    while( (g_u8QuickDataBase_Gen&QUICK_DB_GENST_UPDATE) == QUICK_DB_GENST_UPDATE )
    {
        MApp_DB_QuickGenSettingMonitor();
        if(g_bOpenGenstStoreDBG)
        {
            printf("[Warming]--g_u8QuickDataBase&QUICK_DB_GENST_UPDATE)==QUICK_DB_GENST_UPDATE\n");
        }
        if(msAPI_Timer_DiffTimeFromNow(u32Timer) > 1000)
        {
            if(g_bOpenGenstStoreDBG)
            {
                printf("[Warming]SaveNowGenSetting time out --- %ld\n", msAPI_Timer_DiffTimeFromNow(u32Timer));
            }
            break;
        }
    }

    //memcpy((void*) _PA2VA((U32)(g_u32DataBaseAddr+g_RM_GENSET_START_ADR)),
    //       (void*) &stGenSetting, g_RM_SIZE_GENSET);


    if(g_bGenSettingStoreUseNewMethod)
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("[3]g_u16QuickGenSettingIdx++\n");
        }
        g_u16QuickGenSettingIdx++;

        if(g_u16QuickGenSettingIdx >= (g_QUICK_DB_GENST_NUM - 1))
        {
            msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK, TRUE);
            g_u16QuickGenSettingIdx = 1;
            g_u8EraseGenSettingBank = ERASE_BANK0;
            if(g_bOpenGenstStoreDBG)
            {
                printf("ERASE_BANK0 >>%0x%X!\n", g_QUICK_DB_GENSETTING_BANK);
            }
        }
        else if(g_u8EraseGenSettingBank == ERASE_BANK0 && g_u16QuickGenSettingIdx == 2)
        {
            msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK+1, TRUE);
            g_u16QuickGenSettingIdx = 2;
            g_u8EraseGenSettingBank = ERASE_NUM;
            if(g_bOpenGenstStoreDBG)
            {
                printf("ERASE_BANK1 >>%0x%X!\n", g_QUICK_DB_GENSETTING_BANK+1);
            }
        }
        if(g_bOpenGenstStoreDBG)
        {
            printf("Save GenSettingIdx = %d\n", g_u16QuickGenSettingIdx);
        }
        msAPI_MIU_QuickGenSettingWrite((g_u16QuickGenSettingIdx%2) ? (g_QUICK_DB_GENSETTING_BANK) : (g_QUICK_DB_GENSETTING_BANK+1) , g_u32DataBaseAddr, g_RM_GEN_USAGE);
    }
    else
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("[4]g_u16QuickGenSettingIdx++\n");
        }
        g_u16QuickGenSettingIdx++;

        if(g_u16QuickGenSettingIdx >= g_QUICK_DB_GENST_NUM)
        {
            msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK, TRUE);
            msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK + 1, FALSE);
            g_u16QuickGenSettingIdx = 1;
            if(g_bOpenGenstStoreDBG)
            {
                printf("QUICK_DB_GENSETTING_BANK   >>0x%X!\n", g_QUICK_DB_GENSETTING_BANK);
                printf("QUICK_DB_GENSETTING_BANK+1 >>0x%X!\n", g_QUICK_DB_GENSETTING_BANK + 1);
            }
        }
        msAPI_MIU_QuickGenSettingWrite(g_QUICK_DB_GENSETTING_BANK, g_u32DataBaseAddr, g_RM_GEN_USAGE);
    }

    //g_u8QuickDataBase &= ~g_QUICK_DB_GENST_MODIFIED;
    msAPI_DB_GEN_Set_DataChanged(FALSE);
}

//*************************************************************************
//Function name:        MApp_DB_SaveGenSetting
//Passing parameter:    none
//Return parameter:     none
//Description:          Save database from SDRAM to FLASH
//*************************************************************************
void MApp_DB_SaveGenSetting(void)
{
    if(g_bOpenGenstStoreDBG)
    {
        printf("MApp_DB_SaveGenSetting()\n");
    }

    //memcpy((void*) _PA2VA((U32)(g_u32DataBaseAddr+g_RM_GENSET_START_ADR)),
    //       (void*) &stGenSetting, g_RM_SIZE_GENSET);

    if(g_bGenSettingStoreUseNewMethod)
    {
        if((g_u8QuickDataBase_Gen & QUICK_DB_GENST_MASK)==QUICK_DB_GENST_ERASE_IN_PROGRESS)
        {
            if(g_bOpenGenstStoreDBG)
            {
                printf("[++]ERASE_IN_PROGRESS >> Return\n");
            }
            return;
        }

        if(g_bOpenGenstStoreDBG)
        {
            printf("[1]g_u16QuickGenSettingIdx++\n");
        }

        // Find empty unit
        g_u16QuickGenSettingIdx ++;


        if(g_u16QuickGenSettingIdx >= (g_QUICK_DB_GENST_NUM - 1))//Erase Bank0
        {
            if(g_bOpenGenstStoreDBG)
            {
                printf("\r\n Attention Initial BANK0(g_u8QuickDataBase_Gen = 0x%X)\n", g_u8QuickDataBase_Gen);
            }
            g_u8EraseGenSettingBank = ERASE_BANK0;
            g_u8QuickDataBase_Gen |= QUICK_DB_GENST_UPDATE;
        }
        else if(g_u8EraseGenSettingBank == ERASE_BANK0 && g_u16QuickGenSettingIdx == 2)//Erase Bank1
        {
            if(g_bOpenGenstStoreDBG)
            {
                printf("\r\n Attention Initial BANK1(g_u8QuickDataBase_Gen = 0x%X)\n", g_u8QuickDataBase_Gen);
            }
            g_u8EraseGenSettingBank = ERASE_BANK1;
            g_u8QuickDataBase_Gen |= QUICK_DB_GENST_UPDATE;
        }
        else
        {
            if(g_bOpenGenstStoreDBG)
            {
                printf("[SaveGenSetting]Save GenSettingIdx = %d\n", g_u16QuickGenSettingIdx);
            }
            msAPI_MIU_QuickGenSettingWrite((g_u16QuickGenSettingIdx%2) ? (g_QUICK_DB_GENSETTING_BANK) : (g_QUICK_DB_GENSETTING_BANK+1) , g_u32DataBaseAddr, g_RM_GEN_USAGE);
        }
    }
    else
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("[2]g_u16QuickGenSettingIdx++\n");
        }
        g_u16QuickGenSettingIdx++;
        //printf("MApp_DB_SaveGenSetting>> g_u16QuickGenSettingIdx = %d\n", g_u16QuickGenSettingIdx);

        if(g_u16QuickGenSettingIdx >= g_QUICK_DB_GENST_NUM)
        {
            g_u16QuickGenSettingIdx = 0;
            g_u8QuickDataBase_Gen |= QUICK_DB_GENST_UPDATE;
        }
        else
        {
            msAPI_MIU_QuickGenSettingWrite(g_QUICK_DB_GENSETTING_BANK, g_u32DataBaseAddr, g_RM_GEN_USAGE);
        }
    }

    //g_u8QuickDataBase_Gen &= ~g_QUICK_DB_GENST_MODIFIED;
    msAPI_DB_GEN_Set_DataChanged(FALSE);
}

void MApp_DB_QuickGenSettingMonitor(void)
{
    if ((g_u8QuickDataBase_Gen & QUICK_DB_GENST_UPDATE) == QUICK_DB_GENST_UPDATE)
    {
        U8 u8StatusGen;

        if(g_bOpenGenstStoreDBG)
        {
            printf("\n----MApp_DB_QuickGenSettingMonitor[QUICK_DB_GENST_UPDATE]----0x%X\n", g_u8QuickDataBase_Gen);
        }
        u8StatusGen = (g_u8QuickDataBase_Gen & QUICK_DB_GENST_MASK);
        if(u8StatusGen == QUICK_DB_GENST_READY)
        {
            if(g_bGenSettingStoreUseNewMethod)
            {
                if(g_u8EraseGenSettingBank == ERASE_BANK0)
                {
                    if(g_bOpenGenstStoreDBG)
                    {
                        printf("\nERASE_BANK0 !!!\n");
                    }
                    msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK, TRUE);
                }
                else if(g_u8EraseGenSettingBank == ERASE_BANK1)
                {
                    if(g_bOpenGenstStoreDBG)
                    {
                        printf("\nERASE_BANK1 !!!\n");
                    }
                    msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK+1, TRUE);
                }
            }
            else
            {
                msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK, TRUE);
                msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK+1, FALSE);
            }
            g_u8QuickDataBase_Gen = ((g_u8QuickDataBase_Gen & ~QUICK_DB_GENST_MASK) | QUICK_DB_GENST_ERASE_IN_PROGRESS);
        }
        else if(u8StatusGen == QUICK_DB_GENST_ERASE_IN_PROGRESS)
        {
            if (msAPI_MIU_QuickDataBaseCheck() == TRUE)
            {
                g_u8QuickDataBase_Gen = ((g_u8QuickDataBase_Gen & ~QUICK_DB_GENST_MASK) | QUICK_DB_GENST_ERASE_DONE);
            }
        }
        else if(u8StatusGen == QUICK_DB_GENST_ERASE_DONE)
        {
            if(g_bGenSettingStoreUseNewMethod)
            {
                if(g_u8EraseGenSettingBank == ERASE_BANK0)
                {
                    g_u16QuickGenSettingIdx = 0;
                }
                else if(g_u8EraseGenSettingBank == ERASE_BANK1)
                {
                    if(g_bOpenGenstStoreDBG)
                    {
                        printf("if(g_u8EraseGenSettingBank == ERASE_BANK1) g_u16QuickGenSettingIdx = 1\n");
                    }
                    g_u16QuickGenSettingIdx = 1;
                }

                if(g_u8EraseGenSettingBank == ERASE_BANK1)
                {
                    g_u8EraseGenSettingBank = ERASE_NUM;
                }
            }
            else
            {
                g_u16QuickGenSettingIdx = 0;
            }

            if(g_bOpenGenstStoreDBG)
            {
                printf("\n----MApp_DB_QuickGenSettingMonitor[2]----\n");
            }
            MApp_DB_SaveGenSetting();

            g_u8QuickDataBase_Gen = ((g_u8QuickDataBase_Gen & ~QUICK_DB_GENST_MASK) | QUICK_DB_GENST_READY);
            g_u8QuickDataBase_Gen &= (~QUICK_DB_GENST_UPDATE);
            //u32QuickDatabaseTimer = msAPI_Timer_GetTime0();
        }
    }

    //if (g_u8QuickDataBase & g_QUICK_DB_GENST_MODIFIED)
    if( msAPI_DB_GEN_Get_DataChanged() )
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("\n----MApp_DB_QuickGenSettingMonitor[g_QUICK_DB_GENST_MODIFIED]----0x%X\n", g_u8QuickDataBase_Gen);
        }

        if((g_u8QuickDataBase_Gen & QUICK_DB_GENST_MASK)!=QUICK_DB_GENST_ERASE_IN_PROGRESS && \
           (g_u8QuickDataBase_Gen & QUICK_DB_GENST_MASK)!=QUICK_DB_GENST_ERASE_DONE )
        {
            MApp_DB_SaveGenSetting();
        }
        else
        {
            printf("[Warming]QuickGenSettingMonitor[IN_PROGRESS,ERASE_DONE]---0x%X\n", g_u8QuickDataBase_Gen);
        }
    }
}

/*
void msAPI_Flash_EraseGensettingBank(void)
{
    if(g_u16QuickGenSettingIdx >= (g_QUICK_DB_GENST_NUM - 1))
    {
        msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK, TRUE);
        g_u16QuickGenSettingIdx = 0;
        g_u8EraseGenSettingBank = ERASE_BANK0;
    }
    else if(g_u8EraseGenSettingBank == ERASE_BANK0 && g_u16QuickGenSettingIdx == 2)
    {
        msAPI_MIU_QuickGenSettingErase(g_QUICK_DB_GENSETTING_BANK+1, TRUE);
        g_u16QuickGenSettingIdx = 1;
        g_u8EraseGenSettingBank = ERASE_NUM;
    }
}
*/

void MApp_DB_GEN_Print_InitData(void)
{
    printf(" s_stDB_GEN_InitData:\n u8FlashBank: 0x%X\n", s_stDB_GEN_InitData.u8FlashBank);
    printf(" .u16FlashSaveUnitSize: %d\n",s_stDB_GEN_InitData.u16FlashSaveUnitSize);
    printf(" .u32DramDataAddr: %d\n", s_stDB_GEN_InitData.u32DramDataAddr);
    printf(" .u16DramDataSize: %d\n", s_stDB_GEN_InitData.u16DramDataSize);
}

void msAPI_DB_GEN_Printf_Variable(void)
{
    printf("msAPI_DB_GEN_Printf_Variable()\n");

    //printf(" g_bOpenGenstStoreDBG: %d\n",g_bOpenGenstStoreDBG);
    printf(" g_QUICK_DB_GENSETTING_BANK: 0x%X\n", g_QUICK_DB_GENSETTING_BANK);
    printf(" g_QUICK_DB_GENST_SIZE: %d\n", g_QUICK_DB_GENST_SIZE);
    printf(" g_QUICK_DB_GENST_NUM: %d\n", g_QUICK_DB_GENST_NUM);


/*
	printf("\r\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" g_bOpenGenstStoreDBG: %d\n",g_bOpenGenstStoreDBG);
	printf(" g_bGenSettingStoreUseNewMethod: %d\n",g_bGenSettingStoreUseNewMethod);
	printf(" g_SYSTEM_BANK_SIZE: 0x%X\n",g_SYSTEM_BANK_SIZE);
	printf(" g_u32DataBaseAddr: 0x%X\n",g_u32DataBaseAddr);
	printf(" g_QUICK_DB_GENST_NUM: %d\n",g_QUICK_DB_GENST_NUM);
	printf(" g_RM_GEN_USAGE: %d\n",g_RM_GEN_USAGE);
	printf(" g_MEMCOPYTYPE: %d\n",g_MEMCOPYTYPE);
	printf(" g_QUICK_DB_GENST_SIZE: %d\n",g_QUICK_DB_GENST_SIZE);
	printf("\r\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	*/
}


