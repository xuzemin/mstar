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

#include "msAPI_DB_CH.h"
#include "msAPI_Timer.h"

#include "MApp_FlashMap.h"
#include "MApp_GlobalSettingSt.h"

#include "MApp_SaveData.h"
#include "MApp_DataBase_CH.h"
#include "MApp_RestoreToDefault.h"

#if ENABLE_ATSC
#include "Utl.h"
#include "MApp_GlobalSettingSt_ATSC.h"
#include "MApp_GlobalVar_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_DataBase_ATSC.h"
#endif


#define DEBUG_APP_DB_CH(x)      //x


static BOOL s_DB_CH_bDataChanged = FALSE;


void MApp_DB_CH_CallBack_BeforeWriteFlash(void);

void MApp_DB_CH_Init(void)
{
    DEBUG_APP_DB_CH( printf("MApp_DB_CH_Init()\n"); );

    //printf("MApp_DB_CH_Init() at %u\n", MsOS_GetSystemTime());

    s_DB_CH_bDataChanged = FALSE;


    Stru_DB_CH_InitData stDB_CH_InitData =
    {
        DB_CH_VERSION_ID, //U32 u32MagicId;

        // Flash ...
        FMAP_CH_DB_BANK_START,//U8 u8FlashBankStart;
        DB_BANK_COUNT,//U8 u8FlashSaveBankCount;

        // Dram
        RAM_DISK_DB_64K_START_ADDR,//U32 u32DramDataAddr;
        RM_DB_CH_AND_VERSION_TOTAL_USAGE,//U32 u32DramDataSize;

        // CallBack function
        MApp_DB_CH_CallBack_BeforeWriteFlash, //void (*pfCallBack_BeforeWriteFlash)(void);

        // Debug
        1, //U8 u8DebugFlag;
    } ;

    msAPI_DB_CH_Init( &stDB_CH_InitData );

    //printf("p1 %u\n", MsOS_GetSystemTime());
    msAPI_DB_CH_Printf_Variable();
    //printf("p2 %u\n", MsOS_GetSystemTime());

    // Load data from flash to dram
    MApp_DB_CH_LoadDataBase();

    //printf("MApp_DB_CH_Init() end at %u\n", MsOS_GetSystemTime());
}

void MApp_DB_CH_Set_DataChanged(BOOL bDataChanged)
{
    DEBUG_APP_DB_CH( printf("MApp_DB_CH_Set_DataChanged(%u)\n", bDataChanged); );

    if( bDataChanged )
    {
        s_DB_CH_bDataChanged = TRUE;
    }
    else
    {
        s_DB_CH_bDataChanged = FALSE;
    }
}

BOOL MApp_DB_CH_Get_DataChanged(void)
{
    return s_DB_CH_bDataChanged;
}

BOOLEAN MApp_DB_CH_CheckData(void)
{
    U32 u32MagicId;

    MApp_ReadDatabase(RM_DB_VERSION_START_ADDR, (U8*)&u32MagicId, 4);

    if( u32MagicId == DB_CH_VERSION_ID )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void MApp_DB_CH_WriteMagicDataToDram(void)
{
    U32 u32MagicId = DB_CH_VERSION_ID;

    //printf("MApp_DB_CH_WriteMagicDataToDram()\n");
    //printf(" RM_DB_VERSION_START_ADDR=%X\n\n", RM_DB_VERSION_START_ADDR);

    MApp_WriteDatabase(RM_DB_VERSION_START_ADDR, (U8*)&u32MagicId, 4);
}

void MApp_DB_CH_LoadDataBase(void)
{
    BOOL bLoadCHDataFromFlashResult = FALSE;
    BOOL bDB_CH_CheckDataResult = FALSE;


    DEBUG_APP_DB_CH( printf("MApp_DB_CH_LoadDataBase()\n"); );

    // Load data from flash to dram~
    bLoadCHDataFromFlashResult = msAPI_DB_CH_LoadFromFlash();

    if( bLoadCHDataFromFlashResult == FALSE )
    {
        bDB_CH_CheckDataResult = FALSE;
        printf("\nError: Load DB_CH from flash failed\n");
    }
    else
    {
        // Check DB_CH ID:
        bDB_CH_CheckDataResult = MApp_DB_CH_CheckData();
        //bDB_Gen_VersionCheckResult = 0;
        if( bDB_CH_CheckDataResult == FALSE )
        {
            printf("\nError: DB_CH Check data Fail!\n");
            //MApp_DB_CH_WriteMagicDataToDram();
        }
    }

    // Always write DB version to dram!!
    MApp_DB_CH_WriteMagicDataToDram();

#if(ENABLE_API_DTV_SYSTEM)// (ENABLE_DTV)
    // Beforce use msAPI_CM_xxx(), must init first!!!
    msAPI_CM_Init();
#endif

    if( FALSE == bDB_CH_CheckDataResult ) // Load data failed!
    {
        //printf("\nWarning: DB: Load from flash failed!\n");

    #if (ENABLE_API_DTV_SYSTEM)
        msAPI_CM_ResetDTVDataManager(TRUE);
    #endif

    #if (!BLOADER)
        msAPI_ATV_ResetATVDataManager();
        MApp_SaveData_InitGenSettingExt();
    #endif

    #if (ENABLE_S2)
        MApp_DataBase_RestoreDefaultSatlite();
    #endif

    #if(ENABLE_VCHIP_REGION5)
        MApp_VChipRegion5_Init();
    #endif

    #if ENABLE_ATSC
        MApp_DB_ATSC_ResetAllChData();
    #endif
    }
    else // Load data OK~
    {
        // todo: Rule is too simple!!
        DEBUG_APP_DB_CH( printf("DB_CH: Load data to dram ok~\n"); );

    #if (ENABLE_API_DTV_SYSTEM)
        msAPI_CM_InitDTVDataManager();
    #endif

        msAPI_ATV_InitATVDataManager();

    #if ENABLE_ATSC
        MApp_DB_ATSC_LoadAllChData();
    #endif

      #if (!BLOADER)
        MApp_SaveData_LoadGenSettingExt();
      #endif

    #if(ENABLE_S2)
        MApi_DB_SAT_InitSATTable();
    #endif

    #if(ENABLE_VCHIP_REGION5)
        MApp_VChipRegion5_LoadAndCheck();
    #endif
    }

}

void MApp_DB_CH_SaveData(void)
{
    DEBUG_APP_DB_CH( printf("MApp_DB_CH_SaveData()\n"); );

    msAPI_DB_CH_WriteToFlash();
}

//void MApp_DB_CH_WriteToFlash_RightNow(void)
void MApp_DB_CH_SaveData_RightNow(void)
{
    DEBUG_APP_DB_CH( printf("MApp_DB_CH_SaveData_RightNow()\n"); );

    msAPI_DB_CH_WriteToFlash_RightNow();

    MApp_DB_CH_Set_DataChanged(FALSE);
}

void MApp_DB_CH_WaitJobFinish(void)
{
    if( msAPI_DB_CH_Is_Busy() )
    {
        printf("Wait DB_CH finish~\n");
        while( msAPI_DB_CH_Is_Busy() )
        {
            msAPI_Timer_ResetWDT();

            msAPI_DB_CH_Task();
        }
    }
}

void MApp_DB_CH_Task(void)
{
    static U32 s_u32TaskTime = 0;
    BOOL bDoApp_DB_CH_Job = FALSE;
#if(ENABLE_VCHIP_REGION5)
    static U32 s_u32TaskTime_RRT5 = 0;
#endif


#if(ENABLE_VCHIP_REGION5)
    // Check RRT5
    if( msAPI_Timer_DiffTime_2(s_u32TaskTime_RRT5, msAPI_Timer_GetTime0()) >= 1000 )
    {
        s_u32TaskTime_RRT5 = msAPI_Timer_GetTime0();
        MApp_VChipRegion5_CheckIfDataChanged();
    }
#endif

    // Check time period
    if( msAPI_Timer_DiffTime_2(s_u32TaskTime, msAPI_Timer_GetTime0()) >= 200 )
    {
        bDoApp_DB_CH_Job = TRUE;
        s_u32TaskTime = msAPI_Timer_GetTime0();
    }

    // Speed up auto scan:
    if( gbTVAutoScanChannelEnable )
    {
        //bDoApp_DB_CH_Job = FALSE;
    }

    if( bDoApp_DB_CH_Job )
    {
        // If RamDisk data changed, trigger write falsh
        if( MApp_DB_CH_Get_DataChanged() )
        {
            MApp_DB_CH_Set_DataChanged(FALSE);

          #if (ENABLE_DRAM_DB_CH_SAVE_TO_FLASH)
            DEBUG_APP_DB_CH( printf("\nTrigger Write flash\n"); );
            msAPI_DB_CH_WriteToFlash();
          #endif
        }
    }

    msAPI_DB_CH_Task();

}

void MApp_DB_CH_CallBack_BeforeWriteFlash(void)
{
    //PRINT_CUR_FUNCTION();

    // Final confirm data in dram is correct~

#if ENABLE_ATSC
    // Final confirm data in dram is correct~
    //memcpy((U8*)_PA2VA(u32ChSettingStartAddr), (U8*)&stChSetting, u16ChSettingLength);
    MApp_DB_ATSC_SaveCurChSetting();
#endif

    // Check DB version
    if( FALSE == MApp_DB_CH_CheckData() )
    {
        printf("\nError: DB_CH Check data Fail!\n");
        // Write DB version(Magic data) to dram
        MApp_DB_CH_WriteMagicDataToDram();
    }

    MApp_DB_CH_Set_DataChanged(FALSE);
}


#if(ENABLE_COMPRESS_DATA)

#include "MApp_Compression.h"

#define HEADCHECKNUM  0xAB12CD34 //Be no greater than 4 BYTE
#define CH_DATABASE_FLASH_SIZE_IN_MEMERY   RM_64K_USAGE//0xA0000
#define SYSTEM_BANK_DATABASE_BMP_OFFSET 	0//0x500000
#define CH_DATABASE_FLASH_SIZE   0x40000 //128K

int compressdb(MS_U8* database,MS_U8 *u8compres)
{
	MS_U32 u32compressnum,u32CheckNum = HEADCHECKNUM;
	memset(u8compres,0xFF,CH_DATABASE_FLASH_SIZE);
	u32compressnum =Encode(database,u8compres+8,CH_DATABASE_FLASH_SIZE_IN_MEMERY);
	if(u32compressnum > CH_DATABASE_FLASH_SIZE-8)
	{
		return -1;
	}

	memcpy(u8compres+4,&u32compressnum,4);
	memcpy(u8compres,&u32CheckNum,4);
	return u32compressnum+8;
}

 int decompressdb(MS_U8* database,MS_U8* u8compres)
{
    MS_U32 u32compressnum,decodesize = 0;
    memcpy(&u32compressnum,u8compres,4);
    if(u32compressnum != HEADCHECKNUM)
    {
        return -1;
    }
    else
    {
        memcpy(&u32compressnum,u8compres+4,4);
        if(u32compressnum > CH_DATABASE_FLASH_SIZE_IN_MEMERY)
        {
            printf("decode error!! decode size is too big!\n");
            return -1;
        }
        else
        {
            decodesize = Decode(u8compres+8,database,u32compressnum);
            if(decodesize > CH_DATABASE_FLASH_SIZE_IN_MEMERY)
            {
                return -1;
            }
        }
    }
    return decodesize;
}

#define FLASH_BANK_SIZE 0x10000

void MApi_DecompressData(MS_U8 uBankStart)
{
	MS_U32 u32compressnum;
	MS_U32 u8compres = (MS_U32)((SCALER_2DTO3D_DR_BUF_MEMORY_TYPE& MIU1) ? (SCALER_2DTO3D_DR_BUF_ADR | MIU_INTERVAL) : ((SCALER_2DTO3D_DR_BUF_ADR)+SYSTEM_BANK_DATABASE_BMP_OFFSET));
	MS_U8 iBank;
	MS_U32 pDatabaseInDram;

	for(iBank=uBankStart; iBank<uBankStart+SYSTEM_BANK_DATABASE_NUM; iBank++)
	{
		msAPI_MIU_Copy(SYSTEM_BANK_SIZE*iBank,
		((SCALER_2DTO3D_DR_BUF_MEMORY_TYPE& MIU1) ? (SCALER_2DTO3D_DR_BUF_ADR | MIU_INTERVAL) : ((SCALER_2DTO3D_DR_BUF_ADR)+SYSTEM_BANK_DATABASE_BMP_OFFSET)) + SYSTEM_BANK_SIZE*(iBank-uBankStart),
		FLASH_BANK_SIZE,
		MIU_FLASH2SDRAM);
		HERE
	}
	pDatabaseInDram = RAM_DISK_DB_64K_START_ADDR;//DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)));
	u32compressnum = decompressdb((U8 *)_PA2VA((MS_U32)pDatabaseInDram),(U8 *)_PA2VA((MS_U32)u8compres));
}

void MApi_CompressData(MS_U8 uBankStart, BOOLEAN bErase)
{
	MS_U32 u32compressnum;
	MS_U32 u8compres =  ((SCALER_2DTO3D_DR_BUF_MEMORY_TYPE& MIU1) ? (SCALER_2DTO3D_DR_BUF_ADR | MIU_INTERVAL) : ((SCALER_2DTO3D_DR_BUF_ADR)+SYSTEM_BANK_DATABASE_BMP_OFFSET));
	MS_U8 iBank;
	MS_U32 pDatabaseInDram;

	pDatabaseInDram = RAM_DISK_DB_64K_START_ADDR;//DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)));
	u32compressnum = compressdb((U8 *)_PA2VA((MS_U32)pDatabaseInDram),(U8 *)_PA2VA((MS_U32)u8compres));
	for(iBank=uBankStart ; iBank<uBankStart+SYSTEM_BANK_DATABASE_NUM; iBank++)
	{
		msAPI_MIU_StoreDataBase2Flash(iBank, ((SCALER_2DTO3D_DR_BUF_MEMORY_TYPE& MIU1) ? (SCALER_2DTO3D_DR_BUF_ADR | MIU_INTERVAL) : ((SCALER_2DTO3D_DR_BUF_ADR)+SYSTEM_BANK_DATABASE_BMP_OFFSET))+FLASH_BANK_SIZE*(iBank-uBankStart), FLASH_BANK_SIZE, bErase);
	}
}

#endif // #if(ENABLE_COMPRESS_DATA)


