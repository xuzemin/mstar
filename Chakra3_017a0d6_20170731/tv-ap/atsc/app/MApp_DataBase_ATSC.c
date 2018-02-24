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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////



/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include "Board.h"

#define MAPP_DATABASE_ATSC_C

#if(ENABLE_ATSC)

#include "datatype.h"
#include "MsCommon.h"
#include "Utl.h"

#include "msAPI_Global.h"
#include "msAPI_Ram.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "msAPI_Flash.h"

#include "MApp_SaveData.h"
#include "MApp_DataBase_ATSC.h"
#include "MApp_GlobalVar_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"




#define DEBUG_DB_ATSC(x)    //x


/******************************************************************************/
/*                            Global variable                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 Local                                        */
/******************************************************************************/
static U32 s_ATSC_u32ChSettingStartAddr = 0;

static U16 s_ATSC_u16VirChMaxIdx = 0;
static U32 u32VirChStartAddr = 0;

static U16 s_ATSC_u16PhyChMaxIdx = 0;
static U32 s_ATSC_u32PhyChMemStartAddr = 0;

//*************************************************************************
//Function name:        MApp_DB_ATSC_SaveVirChannel
//Passing parameter:    U16 u16SrvIdx, MS_SHORT_VIRTUAL_CHANNEL *pstShortVirtualCh, MS_VIRTUAL_CHANNEL *pstVirtualCh
//Return parameter:     none
//Description:          Save 1 channel from SDRAM to SDRAM
//*************************************************************************
void MApp_DB_ATSC_SaveVirChannel(U16 u16SrvIdx, MS_VIRTUAL_CHANNEL *pstVirCh)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_SaveVirChannel(u16SrvIdx=%u)\n", u16SrvIdx););

    if( u16SrvIdx > s_ATSC_u16VirChMaxIdx )
    {
        printf("\nError: DB_ATSC: Save VirCh: u16SrvIdx=%u\n", u16SrvIdx);
        return;
    }

#if 1
    MApp_WriteDatabase( (u32VirChStartAddr + u16SrvIdx * sizeof(MS_VIRTUAL_CHANNEL)), (U8*)pstVirCh, sizeof(MS_VIRTUAL_CHANNEL));
#else
    memcpy((U8*)_PA2VA(u32VirChStartAddr + sizeof(MS_VIRTUAL_CHANNEL)*u16SrvIdx),(U8*)(pstVirtualCh_func),sizeof(MS_VIRTUAL_CHANNEL));
#endif
}

void MApp_DB_ATSC_LoadVirChannel(U16 u16SrvIdx, MS_VIRTUAL_CHANNEL *pstVirCh)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_LoadVirChannel(u16SrvIdx=%u)\n", u16SrvIdx););

    if( u16SrvIdx > s_ATSC_u16VirChMaxIdx )
    {
        printf("\nError: DB_ATSC: Load VirCh: u16SrvIdx=%u\n", u16SrvIdx);
        return;
    }

    MApp_ReadDatabase( (u32VirChStartAddr + u16SrvIdx * sizeof(MS_VIRTUAL_CHANNEL)), (U8*)pstVirCh, sizeof(MS_VIRTUAL_CHANNEL));
}

/****Copy Variable to Dram****/
void MApp_DB_ATSC_SaveRfChannel(U16 u16SrvIdx, MS_RF_CHANNEL_new *pstRfCh_func)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_SaveRfChannel(u16SrvIdx=%u)\n", u16SrvIdx););

#if 1
    if( u16SrvIdx > s_ATSC_u16PhyChMaxIdx )
    {
        printf("\nError: DB_ATSC: Save RfCh: u16SrvIdx=%u\n", u16SrvIdx);
        return;
    }

    MApp_WriteDatabase( (s_ATSC_u32PhyChMemStartAddr + u16SrvIdx * sizeof(MS_RF_CHANNEL_new)), (U8*)(pstRfCh_func), sizeof(MS_RF_CHANNEL_new));

#else
    if( ANT_TYPE == ANT_AIR )
    {
        if(u16SrvIdx < MAX_AIR_PHYSICAL_CH_NUM)
        {
            //printf("\r\n[Save RF Air]=%d  Addr=0x%08lx",u16SrvIdx,(RF_CH_AIR_START_ADR + sizeof(MS_RF_CHANNEL_new)*u16SrvIdx));
            //memcpy((U8*)_PA2VA(RF_CH_AIR_START_ADR + sizeof(MS_RF_CHANNEL_new)*u16SrvIdx), (U8*)(pstRfCh_func), sizeof(MS_RF_CHANNEL_new));

            MApp_WriteDatabase( (RM_ATSC_AIR_RF_CH_START_ADR + u16SrvIdx * sizeof(MS_RF_CHANNEL_new)), (U8*)(pstRfCh_func), sizeof(MS_RF_CHANNEL_new));
        }
        else
        {
            printf("\nSave Air RF Channel Idx=%u over max num!\n", u16SrvIdx);
        }
    }
    else // CATV
    {
        if( u16SrvIdx < MAX_CATV_PHYSICAL_CH_NUM)
        {
            //printf("\r\n[Save RF Cbl]=%d  Addr=0x%08lx",u16SrvIdx,(RF_CH_CABLE_START_ADR + sizeof(MS_RF_CHANNEL_new)*u16SrvIdx));
            //memcpy((U8*)_PA2VA(RF_CH_CABLE_START_ADR + sizeof(MS_RF_CHANNEL_new)*u16SrvIdx),(U8*)(pstRfCh_func),sizeof(MS_RF_CHANNEL_new));

            printf("\r\n[Save RF Cbl]=%d  freq=%u\n",u16SrvIdx, pstRfCh_func->stTPSetting.u16Frequency );

            MApp_WriteDatabase( (RM_ATSC_CATV_RF_CH_START_ADR + u16SrvIdx * sizeof(MS_RF_CHANNEL_new)), (U8*)(pstRfCh_func), sizeof(MS_RF_CHANNEL_new));
        }
        else
        {
            printf("\r\nCable RF Channel Idx over max num!Plz check\n");
        }
    }
#endif
}

void MApp_DB_ATSC_LoadRfChannel(U16 u16SrvIdx, MS_RF_CHANNEL_new *pstRfCh_func)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_LoadRfChannel(u16SrvIdx=%u)\n", u16SrvIdx););

#if 1
    if( u16SrvIdx > s_ATSC_u16PhyChMaxIdx )
    {
        printf("\nError: DB_ATSC: Load RfCh: u16SrvIdx=%u\n", u16SrvIdx);
        memset(pstRfCh_func, 0, sizeof(MS_RF_CHANNEL_new)); // Coverity
        return;
    }

    MApp_ReadDatabase( (s_ATSC_u32PhyChMemStartAddr + u16SrvIdx * sizeof(MS_RF_CHANNEL_new)), (U8*)(pstRfCh_func), sizeof(MS_RF_CHANNEL_new));
#else

    if( ANT_TYPE == ANT_AIR )
    {
        if(u16SrvIdx < MAX_AIR_PHYSICAL_CH_NUM)
        {
            MApp_ReadDatabase( (RM_ATSC_AIR_RF_CH_START_ADR + u16SrvIdx * sizeof(MS_RF_CHANNEL_new)), (U8*)(pstRfCh_func), sizeof(MS_RF_CHANNEL_new));
        }
        else
        {
            memset(pstRfCh_func, 0, sizeof(MS_RF_CHANNEL_new)); // Coverity
            printf("\nLoad Air RF Channel Idx=%u over max num!\n", u16SrvIdx);
        }
    }
    else//ANT_VABLE
    {
        if( u16SrvIdx < MAX_CATV_PHYSICAL_CH_NUM)
        {
            MApp_ReadDatabase( (RM_ATSC_CATV_RF_CH_START_ADR + u16SrvIdx * sizeof(MS_RF_CHANNEL_new)), (U8*)(pstRfCh_func), sizeof(MS_RF_CHANNEL_new));

            //printf("\r\n[Load RF Cbl]=%d  freq=%u\n", u16SrvIdx, pstRfCh_func->stTPSetting.u16Frequency );
        }
        else
        {
            memset(pstRfCh_func, 0, sizeof(MS_RF_CHANNEL_new)); // Coverity
            printf("\r\nCable RF Channel Idx over max num!Plz check\n");
        }
    }
#endif
}

//*************************************************************************
//Function name:    MApp_DB_ATSC_InitBaseAddr
//Passing parameter:    EN_ANT_TYPE enAntennaType
//Return parameter:     none
//Description:      set database address by antenna type
//*************************************************************************
void MApp_DB_ATSC_InitBaseAddr(EN_ANT_TYPE enAntennaType)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_InitBaseAddr(enAntennaType=%u)\n", enAntennaType););

    if( enAntennaType == ANT_AIR )
    {
        s_ATSC_u32ChSettingStartAddr = RM_AIR_CH_SETTING_START_ADR;

    #if !ENABLE_ATSC_SCAN_NEW_MODE
        stGenSetting.stScanMenuSetting.u8RFChannelNumber = CHAN_AIR_MIN;
    #endif

        u32VirChStartAddr = RM_AIR_VIR_CH_START_ADR;
        s_ATSC_u16VirChMaxIdx = MAX_NUM_OF_AIR_VIR_CH;

        s_ATSC_u16PhyChMaxIdx = MAX_AIR_PHYSICAL_CH_NUM - 1;
        s_ATSC_u32PhyChMemStartAddr = RM_ATSC_AIR_RF_CH_START_ADR;
    }
    else //ANT_CATV
    {
        s_ATSC_u32ChSettingStartAddr = RM_CATV_CH_SETTING_START_ADR;

    #if !ENABLE_ATSC_SCAN_NEW_MODE
        stGenSetting.stScanMenuSetting.u8RFChannelNumber = CHAN_CATV_MIN;
    #endif

        u32VirChStartAddr = RM_CATV_VIR_CH_START_ADR;
        s_ATSC_u16VirChMaxIdx = MAX_NUM_OF_CATV_VIR_CH;

        s_ATSC_u16PhyChMaxIdx = MAX_CATV_PHYSICAL_CH_NUM - 1;
        s_ATSC_u32PhyChMemStartAddr = RM_ATSC_CATV_RF_CH_START_ADR;
    }
}

void MApp_DB_ATSC_SaveChSetting(MS_CHANNEL_SETTING* pstAtscChSetting)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_SaveChSetting()\n" ););

    // Add magic code
    pstAtscChSetting->u32MagicCode_1 = DB_ATSC_CH_SETTING_MAGCI_CODE_1;
    pstAtscChSetting->u32MagicCode_2 = DB_ATSC_CH_SETTING_MAGCI_CODE_2;

    MApp_WriteDatabase(s_ATSC_u32ChSettingStartAddr, (U8*)pstAtscChSetting, sizeof(MS_CHANNEL_SETTING));
}

void MApp_DB_ATSC_LoadChSetting(MS_CHANNEL_SETTING* pstAtscChSetting)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_LoadChSetting()\n" ););

    MApp_ReadDatabase(s_ATSC_u32ChSettingStartAddr, (U8*)pstAtscChSetting, sizeof(MS_CHANNEL_SETTING));
}

void MApp_DB_ATSC_SaveCurChSetting(void)
{
    MApp_DB_ATSC_SaveChSetting(&stChSetting);
}

void MApp_DB_ATSC_LoadCurChSetting(void)
{
    MApp_DB_ATSC_LoadChSetting(&stChSetting);
    if(stChSetting.u32MagicCode_1 != DB_ATSC_CH_SETTING_MAGCI_CODE_1
    ||stChSetting.u32MagicCode_2 != DB_ATSC_CH_SETTING_MAGCI_CODE_2)
    {
        printf("\n Error: DB_ATSC magic code is wrong! [%s,%s,%d]\n",__FILE__,__FUNCTION__,__LINE__);

        MApp_DB_ATSC_ResetAllChData();
    }
}

void MApp_DB_ATSC_ResetAllChData(void)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_ResetAllChData()\n" ););

    memset(&stChSetting, 0, sizeof(MS_CHANNEL_SETTING));

    stChSetting.u32MagicCode_1 = DB_ATSC_CH_SETTING_MAGCI_CODE_1;
    stChSetting.u32MagicCode_2 = DB_ATSC_CH_SETTING_MAGCI_CODE_2;

    MApp_ChanProc_RefreshVirChInfoStartIdx();

#if 1 // Clear one DB not 2 DB
    MApp_DB_ATSC_SaveChSetting(&stChSetting);
#else

 #if 1 // Use DB API
    MApp_WriteDatabase(RM_AIR_CH_SETTING_START_ADR, (U8*)&stChSetting, sizeof(MS_CHANNEL_SETTING));
    MApp_WriteDatabase(RM_CATV_CH_SETTING_START_ADR, (U8*)&stChSetting, sizeof(MS_CHANNEL_SETTING));
 #else
    memcpy((U8*)_PA2VA(AIR_CH_SETTING_START_ADR),(U8*)&stChSetting,AIR_CH_SETTING_LEN);
    memcpy((U8*)_PA2VA(CATV_CH_SETTING_START_ADR),(U8*)&stChSetting,CATV_CH_SETTING_LEN);
 #endif
#endif

    // Clear all RF channel
    {
        MS_RF_CHANNEL_new stRfChTmp;
        memset(&stRfChTmp, 0, sizeof(stRfChTmp));

        U8 u8PhyIdx;

        for(u8PhyIdx = 0; u8PhyIdx <= s_ATSC_u16PhyChMaxIdx; u8PhyIdx ++)
        {
            MApp_DB_ATSC_SaveRfChannel(u8PhyIdx, &stRfChTmp);
        }
    }

    // Clear all vir channel
    {
        MS_VIRTUAL_CHANNEL stMS_VIRTUAL_CHANNEL_Tmp;
        memset(&stMS_VIRTUAL_CHANNEL_Tmp, 0, sizeof(stMS_VIRTUAL_CHANNEL_Tmp));

        U16 u16VirChIdx;

        for(u16VirChIdx = 0; u16VirChIdx <= s_ATSC_u16VirChMaxIdx; u16VirChIdx ++)
        {
            MApp_DB_ATSC_SaveVirChannel(u16VirChIdx, &stMS_VIRTUAL_CHANNEL_Tmp);
        }
    }
}

void MApp_DB_ATSC_LoadAllChData(void)
{
    DEBUG_DB_ATSC(printf("MApp_DB_ATSC_LoadAllChData()\n" ););

    //printf("_PA2VA(u32ChSettingStartAddr)=0x%X\n", _PA2VA(u32ChSettingStartAddr));
    //printf("u16ChSettingLength=0x%X\n", u16ChSettingLength);

    // Check ATSC mem base
    if( s_ATSC_u32ChSettingStartAddr == 0 )
    {
        MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
    }

    MApp_DB_ATSC_LoadCurChSetting();

    DEBUG_DB_ATSC(printf("stChSetting.u32MagicCode=0x%X\n", stChSetting.u32MagicCode); );

    if( (stChSetting.u32MagicCode_1 != DB_ATSC_CH_SETTING_MAGCI_CODE_1)
      ||(stChSetting.u32MagicCode_2 != DB_ATSC_CH_SETTING_MAGCI_CODE_2)
      )
    {
        printf("\nError: DB_ATSC magic code is wrong!\n");

        MApp_DB_ATSC_ResetAllChData();
    }
    else
    {
        DEBUG_DB_ATSC(printf("DB_ATSC magic code is correct~\n" ););

        // Check last watched
    #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
        extern void MApp_Channel_ChSetting_Disp_Init(void);
        MApp_Channel_ChSetting_Disp_Init();
        if(stGenSetting.g_SysSetting.u16MainListLastWatched > MApp_ChanProc_GetNumOfServices( MAIN_LIST ))
        {
            stGenSetting.g_SysSetting.u16MainListLastWatched = 1;
        }

        MApp_ChanProc_ResetAllIndex(stGenSetting.g_SysSetting.u16MainListLastWatched);
    #else
        if(stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] > MApp_ChanProc_GetNumOfServices( MAIN_LIST ))
        {
            //Protect last watch to avoid exceeding total DB
            stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = 1;
        }

        MApp_ChanProc_ResetAllIndex(stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE]);
    #endif

        MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST);
    }
}

#if( ENABLE_DB_ATSC_RRT5_API )

void MApp_DB_ATSC_Save_RRT_Descriptor(U8 u8DimensionIdx, U8 u8OptionIdx, U8* pDescriptorData, U16 u16DataSize )
{
    if( u8DimensionIdx >= REGION5_DIMENSION_NUM )
        return;

    if( u8OptionIdx >= REGION5_MAX_RATING_OPTION )
        return;

    if( u16DataSize > SIZE_RRT_ONE_DESCRIPTOR )
        u16DataSize = SIZE_RRT_ONE_DESCRIPTOR;

    U32 u32RamDiskAddr = GET_RRT_DESCRIPTOR_ADDRESS(u8DimensionIdx, u8OptionIdx);

    //SetNVRAM(u32RamDiskAddr, pDescriptorData, u16DataSize);
    MApp_WriteDatabase(u32RamDiskAddr, pDescriptorData, u16DataSize);
}

void MApp_DB_ATSC_Load_RRT_Descriptor(U8 u8DimensionIdx, U8 u8OptionIdx, U8* pDescriptorData, U16 u16DataSize )
{
    if( u8DimensionIdx >= REGION5_DIMENSION_NUM )
        return;

    if( u8OptionIdx >= REGION5_MAX_RATING_OPTION )
        return;

    if( u16DataSize > SIZE_RRT_ONE_DESCRIPTOR )
        u16DataSize = SIZE_RRT_ONE_DESCRIPTOR;

    U32 u32RamDiskAddr = GET_RRT_DESCRIPTOR_ADDRESS(u8DimensionIdx, u8OptionIdx);

    //GetNVRAM(u32RamDiskAddr, pDescriptorData, u16DataSize);
    MApp_ReadDatabase(u32RamDiskAddr, pDescriptorData, u16DataSize);
}

void MApp_DB_ATSC_Save_RRT_EZ_REGION(U8 u8RegionIdx, MS_EZ_REGION5_RATING* pstMS_EZ_REGION )
{
    U32 u32RamDiskAddr = GET_SAVED_RRT_SETTING_ADDRESS(u8RegionIdx);

    if( u8RegionIdx >= MAX_RRT_SAVED )
        return;

    //SetNVRAM(u32RamDiskAddr, (U8*)pstMS_EZ_REGION, sizeof(MS_EZ_REGION5_RATING) );
    MApp_WriteDatabase(u32RamDiskAddr, (U8*)pstMS_EZ_REGION, sizeof(MS_EZ_REGION5_RATING) );
}

void MApp_DB_ATSC_Load_RRT_EZ_REGION(U8 u8RegionIdx, MS_EZ_REGION5_RATING* pstMS_EZ_REGION )
{
    U32 u32RamDiskAddr = GET_SAVED_RRT_SETTING_ADDRESS(u8RegionIdx);

    if( u8RegionIdx >= MAX_RRT_SAVED )
        return;

    //GetNVRAM(u32RamDiskAddr, (U8*)pstMS_EZ_REGION, sizeof(MS_EZ_REGION5_RATING) );
    MApp_ReadDatabase(u32RamDiskAddr, (U8*)pstMS_EZ_REGION, sizeof(MS_EZ_REGION5_RATING) );
}

#endif // ENABLE_DB_ATSC_RRT5_API

#endif // #if(ENABLE_ATSC)

//******************************************************************************

#undef MAPP_DATABASE_ATSC_C


