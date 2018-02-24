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

#include "msAPI_DB_Factory.h"

#include "MApp_SaveData.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_DataBase_Factory.h"


//======================================================


#define DEBUG_DB_FACTORY(x)  //x

#define DEBUG_DB_FACTORY_DATA_CHANGE(x) x

//======================================================

U16 MApp_SaveData_ADC_CalChecksum(U8 u8AdcSettingIdx);
U16 MApp_SaveData_SubColor_CalCheckSum(U8 u8DataIdx);

//======================================================

U16 _MApp_DB_Factory_CalCheckSum(void)
{
    return MApp_CalCheckSum_SkipFirst2Byte( ((U8*)&G_FACTORY_SETTING), sizeof(MS_FACTORY_SETTING) );
}

void MApp_DB_Factory_UpdateAllCheckSum(void)
{
    U8 i;

    DEBUG_DB_FACTORY( printf("MApp_DB_Factory_UpdateAllCheckSum()\n"); );

    // Adc setting ...
    {
        for( i = 0; i < ADC_SET_NUMS; i++ )
        {
            G_ADC_SETTING[i].u16ADCDataCS = MApp_SaveData_ADC_CalChecksum(i);
        }
    }

    // White Balance
    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        G_WHITE_BALANCE_SETTING[i].wWhiteBalanceDataCS = MApp_SaveData_WB_CalCheckSum((E_DATA_INPUT_SOURCE)i);
    }

    // Sub color
    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        G_SUB_COLOR_SETTING[i].u16SubColorDataCS = MApp_SaveData_SubColor_CalCheckSum(i);
    }

    // Other setting ...
    MApp_SaveData_Update_CheckSum(E_SAVE_DATA_ID_FACTORY_ALL);

    G_FACTORY_SETTING.u16FactorySettignCS = _MApp_DB_Factory_CalCheckSum();
}

void MApp_DB_Factory_ResetAll(void)
{
    //DEBUG_DB_FACTORY( printf("MApp_DB_Factory_ResetAll()\n"); );
    printf("MApp_DB_Factory_ResetAll()\n");

    // Init all factory variable
    MApp_DataBase_RestoreDefaultFactorySetting();

    // Save to falsh
    MApp_DB_Factory_SaveData();
}

void MApp_DB_Facotry_CheckAllDataCorrect(void)
{
    // Check sub checksum
    MApp_SaveData_ADC_CheckIfDataCorrect();

    // Check WB setting checksum
    MApp_CheckWhiteBalanceSetting();

    // Check subColor setting checksum
    MApp_CheckSubColorSetting();

    MApp_SaveData_Check_IfDataCorrect(E_SAVE_DATA_ID_FACTORY_ALL);

    G_FACTORY_SETTING.u16FactorySettignCS = _MApp_DB_Factory_CalCheckSum();
}

#if (ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK)

void MApp_DB_Factory_Init(void)
{
    BOOL bNeedResetAll = FALSE;
    U16 u16CheckSum;


    printf("MApp_DB_Factory_Init() at %u\n", MsOS_GetSystemTime());

    msAPI_DB_Factory_Init();

    // Load setting from flash
    if( FALSE == msAPI_DB_Factory_LoadFromFlash((U8*)&G_FACTORY_SETTING, sizeof(MS_FACTORY_SETTING)) ) //Data base is not valid
    {
        bNeedResetAll = TRUE;
        printf("\nError: Load factory setting failed\n");
    }
    else
    {
        // Check check sum
        u16CheckSum = _MApp_DB_Factory_CalCheckSum();

        if( u16CheckSum != G_FACTORY_SETTING.u16FactorySettignCS )
        {
            bNeedResetAll = TRUE;
            printf("\nError: Factory setting checksum error\n");
        }
    }

    if( bNeedResetAll )
    {
        MApp_DB_Factory_ResetAll();
    }
    else
    {
        MApp_DB_Facotry_CheckAllDataCorrect();
    }

    printf("MApp_DB_Factory_Init() end at %u\n", MsOS_GetSystemTime());
}

#else

void MApp_DB_Factory_LoadSettingAndCheck(void)
{
    U16 u16CheckSum;

    DEBUG_DB_FACTORY( printf("MApp_DB_Factory_LoadSettingAndCheck()\n"); );

    // Copy ramdisk to variable
    MApp_ReadDatabase(RM_FACTORY_SETTING_DATA_ADDRESS, (BYTE *)&(G_FACTORY_SETTING), sizeof(MS_FACTORY_SETTING));

    u16CheckSum = _MApp_DB_Factory_CalCheckSum();

    if( G_FACTORY_SETTING.u16FactorySettignCS != u16CheckSum )
    {
        MApp_DB_Factory_ResetAll();
    }
    else
    {
        MApp_DB_Facotry_CheckAllDataCorrect();
    }
}

BOOL MApp_DB_Factory_CheckIfDataChanged(void)
{
    U16 u16CheckSum;
    U8 u8DataIdx = DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW);
    BOOL bDataChanged = FALSE;


    if( u8DataIdx < DATA_INPUT_SOURCE_NUM )
    {
        // Check g_astWhiteBalance
        u16CheckSum = MApp_SaveData_WB_CalCheckSum(u8DataIdx);
        if( G_WHITE_BALANCE_SETTING[u8DataIdx].wWhiteBalanceDataCS != u16CheckSum )
        {
            DEBUG_DB_FACTORY_DATA_CHANGE( printf("g_astWhiteBalance changed!\n"); );
            MApp_SaveWhiteBalanceSetting((E_DATA_INPUT_SOURCE)u8DataIdx);
            bDataChanged = TRUE;
        }

        // Check g_astSubcolor
        u16CheckSum = MApp_SaveData_SubColor_CalCheckSum(u8DataIdx);
        if( G_SUB_COLOR_SETTING[u8DataIdx].u16SubColorDataCS != u16CheckSum )
        {
            DEBUG_DB_FACTORY_DATA_CHANGE( printf("g_astSubcolor changed!\n"); );
            MApp_SaveSubColorSetting((E_DATA_INPUT_SOURCE)u8DataIdx);
            bDataChanged = TRUE;
        }
    }
    else
    {
        printf("\nError: DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW)=%u\n", u8DataIdx );
    }

    // Check adc
    {
        U8 u8AdcIdx;
        for( u8AdcIdx = 0; u8AdcIdx < ADC_SET_NUMS; u8AdcIdx++ )
        {
            u16CheckSum = MApp_SaveData_ADC_CalChecksum(u8AdcIdx);
            if( G_ADC_SETTING[u8AdcIdx].u16ADCDataCS != u16CheckSum )
            {
                DEBUG_DB_FACTORY_DATA_CHANGE( printf("G_ADC_SETTING changed!\n"); );
                MApp_SaveData_ADC_SaveSetting((E_ADC_SET_INDEX)u8AdcIdx);
                bDataChanged = TRUE;
            }
        }
    }

    // Check other
    if( MApp_SaveData_Check_IfDataChanged(E_SAVE_DATA_ID_FACTORY_ALL) )
    {
        bDataChanged = TRUE;
    }

    // Check other
    u16CheckSum = _MApp_DB_Factory_CalCheckSum();;
    if( G_FACTORY_SETTING.u16FactorySettignCS != u16CheckSum )
    {
        DEBUG_DB_FACTORY_DATA_CHANGE( printf("G_FACTORY_SETTING changed!\n"); );
        bDataChanged = TRUE;
    }

    if( bDataChanged )
    {
        MApp_DB_Factory_SaveData();
    }

    return bDataChanged;
}

#endif

//void MApp_SaveFactorySetting(void)
void MApp_DB_Factory_SaveData(void)
{
    DEBUG_DB_FACTORY( printf(" MApp_DB_Factory_SaveData!\n"); );

    MApp_DB_Factory_UpdateAllCheckSum();

#if( ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK )
    // Save to falsh
    msAPI_DB_Factory_SaveToFlash( (U8*)&G_FACTORY_SETTING, sizeof(MS_FACTORY_SETTING) );
#else
    // todo: save gen??
    MApp_WriteDatabase(RM_FACTORY_SETTING_DATA_ADDRESS, (BYTE *)&(G_FACTORY_SETTING), sizeof(MS_FACTORY_SETTING));
#endif
}


