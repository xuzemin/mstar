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

#ifndef MAPP_DATABASE_ATSC_H
#define MAPP_DATABASE_ATSC_H

#include "Board.h"

#ifdef MAPP_DATABASE_ATSC_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif


////////////////////////////////////////////////////////////////////////////////

#if(ENABLE_ATSC)

#define OFFSETOF(type, member) ((U32)&(((type *)0)->member))


//==============================================================================
/*                               Macro                                          */
//==============================================================================


///////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------
//#define DB_MAGIC_CODE                   0xA5A5A5A5

#define DB_ATSC_CH_SETTING_MAGCI_CODE_1 0x12347788
#define DB_ATSC_CH_SETTING_MAGCI_CODE_2 0xA5A5A5A5

/**********************************************************************************/


//*************************************************************************
//              Function prototypes
//*************************************************************************


//--------------------------------------------------------------------------------------

#define MApp_DB_SaveRfChannel( u16SrvIdx, pstRfCh_func) do{\
    MApp_DB_ATSC_SaveRfChannel(u16SrvIdx, pstRfCh_func);    \
}while(0);

//-------------------------------------------------------------------------------------

void MApp_DB_ATSC_SaveVirChannel(U16 u16SrvIdx, MS_VIRTUAL_CHANNEL *pstVirCh);
void MApp_DB_ATSC_LoadVirChannel(U16 u16SrvIdx, MS_VIRTUAL_CHANNEL *pstVirCh);


void MApp_DB_ATSC_SaveRfChannel(U16 u16SrvIdx, MS_RF_CHANNEL_new *pstRfCh_func);
void MApp_DB_ATSC_LoadRfChannel(U16 u16SrvIdx, MS_RF_CHANNEL_new *pstRfCh_func);

void MApp_DB_ATSC_InitBaseAddr(EN_ANT_TYPE enAntennaType);

void MApp_DB_ATSC_SaveChSetting(MS_CHANNEL_SETTING* pstAtscChSetting);
void MApp_DB_ATSC_LoadChSetting(MS_CHANNEL_SETTING* pstAtscChSetting);

void MApp_DB_ATSC_SaveCurChSetting(void);
void MApp_DB_ATSC_LoadCurChSetting(void);


void MApp_DB_ATSC_ResetAllChData(void);
void MApp_DB_ATSC_LoadAllChData(void);

//=============================================================

#define ENABLE_DB_ATSC_RRT5_API 1
//-------------------------------------------------------------------------

//#define RRT_DESCRIPTOR_START_ADDRESS    RRT5_DIM_START_ADR
#define RRT_DESCRIPTOR_START_ADDRESS    ATSC_RRT5_DESCRIPTOR_START_ADDR

#define SIZE_RRT_ONE_DESCRIPTOR             ((sizeof(U8))*REGION5_RATING_DES_MAX_LENGTH)
#define SIZE_RRT_ONE_DIMENSION_DESCRIPTOR   (SIZE_RRT_ONE_DESCRIPTOR * REGION5_MAX_RATING_OPTION)
#define SIZE_RRT_ALL_DESCRIPTORS            (SIZE_RRT_ONE_DIMENSION_DESCRIPTOR * REGION5_DIMENSION_NUM)

//#define RRT_SETTING_MEMORIZE_START_ADR      (RRT_DESCRIPTOR_START_ADDRESS+SIZE_RRT_ALL_DESCRIPTORS)
#define RRT_SETTING_MEMORIZE_START_ADR      (ATSC_RRT5_EZ_REGION_START_ADDR)
#define RRT_SETTING_MEMORIZE_SIZE           ((U16)sizeof(MS_EZ_REGION5_RATING)*MAX_RRT_SAVED) // 59*20 = 1180 bytes


#if 1//(!ENABLE_DB_ATSC_RRT5_API)
// u8DimensionIdx, u8OptionIdx is 0 based...........
#define GET_RRT_DESCRIPTOR_ADDRESS(u8DimensionIdx, u8OptionIdx) \
( RRT_DESCRIPTOR_START_ADDRESS+(SIZE_RRT_ONE_DIMENSION_DESCRIPTOR*u8DimensionIdx) + (SIZE_RRT_ONE_DESCRIPTOR*u8OptionIdx) )

#define GET_SAVED_RRT_SETTING_ADDRESS(u8RegionIdx) \
( RRT_SETTING_MEMORIZE_START_ADR+((U16)sizeof(MS_EZ_REGION5_RATING)*u8RegionIdx))
#endif

//------------------------------------------------------------
#if( ENABLE_DB_ATSC_RRT5_API )
void MApp_DB_ATSC_Save_RRT_Descriptor(U8 u8DimensionIdx, U8 u8OptionIdx, U8* pDescriptorData, U16 u16DataSize );
void MApp_DB_ATSC_Load_RRT_Descriptor(U8 u8DimensionIdx, U8 u8OptionIdx, U8* pDescriptorData, U16 u16DataSize );

void MApp_DB_ATSC_Save_RRT_EZ_REGION(U8 u8RegionIdx, MS_EZ_REGION5_RATING* pstMS_EZ_REGION );
void MApp_DB_ATSC_Load_RRT_EZ_REGION(U8 u8RegionIdx, MS_EZ_REGION5_RATING* pstMS_EZ_REGION );
#endif

//=============================================================


#endif // #if(ENABLE_ATSC)


//******************************************************************************

#undef INTERFACE

//******************************************************************************

#endif // #ifndef MAPP_DATABASE_ATSC_H

