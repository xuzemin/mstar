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

#include "Utl.h"


#include "msAPI_DB_GEN.h"
#include "msAPI_Timer.h"

#include "MApp_FlashMap.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_SaveData.h"

#include "MApp_DataBase_Factory.h"



//*************************************************************************


#define DEBUG_APP_DB_GEN(x)         //x



typedef struct
{
    BOOL bDataChanged;

} Stru_App_DB_GEN_Info;

static Stru_App_DB_GEN_Info s_AppDBGenInfo;


//*************************************************************************


void MApp_DB_GEN_Set_DataChanged(BOOL bDataChanged)
{
    DEBUG_APP_DB_GEN( printf("MApp_DB_GEN_Set_DataChanged(bDataChanged=%u)\n", bDataChanged); );
    if( bDataChanged )
    {
        s_AppDBGenInfo.bDataChanged = 1;
    }
    else
    {
        s_AppDBGenInfo.bDataChanged = 0;
    }
}

BOOL MApp_DB_GEN_Get_DataChanged(void)
{
    return s_AppDBGenInfo.bDataChanged;
}

//*************************************************************************
//Function name:        MApp_DB_GEN_VersionCheck
//Passing parameter:    none
//Return parameter: BOOLEAN fError
//Description:          Check data base version and integrity
//*************************************************************************
BOOLEAN MApp_DB_GEN_VersionCheck(void)
{
    U8 u8Version1, u8Version2;


    MApp_ReadDatabase(RM_GEN_VERSION_1_ADDRESS, &u8Version1, 1);
    MApp_ReadDatabase(RM_GEN_VERSION_2_ADDRESS, &u8Version2, 1);


    //if(stGenSetting.u8VersionCheck == DEFAULT_DATABASE_VERSION &&
    //    stGenSetting.u8VersionCheckCom == DEFAULT_DATABASE_VERSION_COM)
    if( u8Version1 == DEFAULT_DATABASE_VERSION &&
        u8Version2 == DEFAULT_DATABASE_VERSION_COM )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void MApp_DB_GEN_Init(void)
{
#if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
    BOOL bLoadGenFromFlashResult = FALSE;
    BOOL bDB_Gen_VersionCheckResult = FALSE;


    DEBUG_APP_DB_GEN( printf("MApp_DB_GEN_Init() at %u\n", MsOS_GetSystemTime()); );


    memset(&s_AppDBGenInfo, 0, sizeof(Stru_App_DB_GEN_Info));



    Stru_DB_GEN_InitData stDB_GEN_InitData =
    {
        // Flash ...
        QUICK_DB_GENSETTING_BANK, // U8 u8FlashBank;
        QUICK_DB_GENST_SIZE,    // U16 u16FlashSaveUnitSize;

        // Dram
        RAM_DISK_DB_GEN_START_ADDR,//U32 u32DramDataAddr;
        RM_GEN_USAGE,//U16 u32DramDataSize;

        // CallBack function
        MApp_SaveData_CallBack_BeforeWriteFlash,//void (*pfCallBack_BeforeWriteFlash)(void);

        // Debug
        1, //U8 u8DebugFlag;
    };

    msAPI_DB_GEN_Init( &stDB_GEN_InitData );


    // Copy DB_GEN from flash to dram
    bLoadGenFromFlashResult = msAPI_DB_GEN_LoadFromFlash();
    // Debug: Force init
    //bLoadGenFromFlashResult = FALSE;
    if( bLoadGenFromFlashResult == FALSE )
    {
        bDB_Gen_VersionCheckResult = FALSE;
        printf("\nError: Load DB_GEN from flash failed\n");
    }
    else
    {
        // Check DB_GEN ID:
        bDB_Gen_VersionCheckResult = MApp_DB_GEN_VersionCheck();
        //bDB_Gen_VersionCheckResult = 0;
        if( bDB_Gen_VersionCheckResult == FALSE )
        {
            printf("\nError: GenSetting Version Check Fail!\n");
        }
    }

    // Load DB_GEN from flash to dram
    if( FALSE == bDB_Gen_VersionCheckResult )  // Load GenSetting failed
    {
        // Init all GenSetting, and write to RamDisk
        MApp_InitGenSetting();
    }
    else // Load OK
    {
        MApp_LoadGenSetting();
    }


    DEBUG_APP_DB_GEN( msAPI_DB_GEN_Printf_Variable(); );


    // Load Factory setting
  #if( ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK == FALSE )
    if( FALSE == bLoadGenFromFlashResult )  // Load factory failed
    {
        // Init all factory setting
        MApp_DB_Factory_ResetAll();
    }
    else
    {
        MApp_DB_Factory_LoadSettingAndCheck();

    #if 0//ENABLE_VD_PACH_IN_CHINA
        G_FACTORY_SETTING.stVDSetting.u8AFEC_A0 = 0x10;
        G_FACTORY_SETTING.stVDSetting.u8AFEC_A1 = 0x20;
        MApp_DB_Factory_SaveData();
    #endif
    }
  #endif

    if( (bLoadGenFromFlashResult == FALSE)
      ||(bDB_Gen_VersionCheckResult == FALSE) )
    {
        // Write to flash right now!
        msAPI_DB_GEN_WriteToFlash_RightNow();

        MApp_DB_GEN_Set_DataChanged(FALSE);
    }

    DEBUG_APP_DB_GEN( printf("MApp_DB_GEN_Init() end at %u\n", MsOS_GetSystemTime()); );
#endif
}

void MApp_DB_GEN_SaveData_RightNow(void)
{
#if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
    msAPI_DB_GEN_WriteToFlash_RightNow();
#endif
    MApp_DB_GEN_Set_DataChanged(FALSE);
}

#define TRIGGER_WRITE_FLASH_BY_TIMER    0
#define TRIGGER_WRITE_FLASH_TIME        2000

void MApp_DB_GEN_Task(void)
{
    BOOL bDoApp_DB_GEN_Job = FALSE;
    static U32 s_u32TaskTime = 0;
#if( TRIGGER_WRITE_FLASH_BY_TIMER )
    static U32 s_DB_GEN_u32DataChangeTimer = 0;
#endif


    // Check time period
    if( msAPI_Timer_DiffTime_2(s_u32TaskTime, msAPI_Timer_GetTime0()) >= 200 )
    {
        bDoApp_DB_GEN_Job = TRUE;
        s_u32TaskTime = msAPI_Timer_GetTime0();
    }


    if( bDoApp_DB_GEN_Job )
    {
        // Check GenSetting if data changed...
        //if( MApp_DB_GEN_Get_DataChanged() == FALSE )
        {
            MApp_GenSetting_DataCheckHandler();
        }


        // If RamDisk data changed, trigger write falsh
        if( MApp_DB_GEN_Get_DataChanged() )
        {
            MApp_DB_GEN_Set_DataChanged(FALSE);

        #if( TRIGGER_WRITE_FLASH_BY_TIMER )
            s_DB_GEN_u32DataChangeTimer = msAPI_Timer_GetTime0();
            printf("t1=%u\n", msAPI_Timer_GetTime0());
        #else
          #if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
            DEBUG_APP_DB_GEN( printf("\nTrigger Write flash\n"); );
            msAPI_DB_GEN_WriteToFlash();
          #endif
        #endif
        }
        else
        {

        #if( TRIGGER_WRITE_FLASH_BY_TIMER )
            if( s_DB_GEN_u32DataChangeTimer )
            {
                if( msAPI_Timer_DiffTime_2(s_DB_GEN_u32DataChangeTimer, msAPI_Timer_GetTime0()) > TRIGGER_WRITE_FLASH_TIME )
                {
                    printf("t1=%u\n", msAPI_Timer_GetTime0());
                #if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
                    DEBUG_APP_DB_GEN( printf("\nTrigger Write flash\n"); );
                    msAPI_DB_GEN_WriteToFlash();
                #endif
                    s_DB_GEN_u32DataChangeTimer = 0;
                }
            }
        #endif
        }
    }


#if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
    msAPI_DB_GEN_Task();
#endif

}

