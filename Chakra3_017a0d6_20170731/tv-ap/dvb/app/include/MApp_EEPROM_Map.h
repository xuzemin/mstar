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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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

#ifndef MAPP_EEPROM_MAP_H
#define MAPP_EEPROM_MAP_H


#include "Board.h"

//#include "msAPI_Flash.h"
//#include "msAPI_Bootloader.h"
#include "MApp_GlobalSettingSt.h" //ZUI


#if (RM_EEPROM_TYPE == RM_TYPE_24C512 )
#define MAX_LIMITED_EEPROM_SIZE     0x10000
#elif (RM_EEPROM_TYPE == RM_TYPE_24C16 )
#define MAX_LIMITED_EEPROM_SIZE     0x800
#elif (RM_EEPROM_TYPE == RM_TYPE_24C32 )
#define MAX_LIMITED_EEPROM_SIZE     0x1000
#elif (RM_EEPROM_TYPE == RM_TYPE_24C64)
#define MAX_LIMITED_EEPROM_SIZE     0x2000
#endif


#if( ENABLE_SAVE_DATA_TO_EEPROM )
    #if (RM_EEPROM_TYPE == RM_TYPE_24C512 )
        #define RM_MAX_ADDRESS  (0xffff)
    #elif (RM_EEPROM_TYPE == RM_TYPE_24C16 )
        #define RM_MAX_ADDRESS  (0x07ff)
    #elif (RM_EEPROM_TYPE == RM_TYPE_24C32 )
        #define RM_MAX_ADDRESS  (0x0fff)
    #elif (RM_EEPROM_TYPE == RM_TYPE_24C64)
        #define RM_MAX_ADDRESS (0x1fff)
    #endif

    //EEPROM ID for eeprom case only
    #define RM_EEPROM_ID_ADDRESS                (RM_MAX_ADDRESS)
    #define RM_EEPROM_ID_SIZE                   1

#endif



//HDCP Key
#if (HDCP_KEY_TYPE==HDCP_KEY_IN_24C04)
#define HDCP_KEY_ADDR                0
#elif (HDCP_KEY_TYPE==HDCP_KEY_IN_24C64)
#define HDCP_KEY_ADDR                RM_HDCP_KEY_ADDR
#endif
#define HDCP_KEY_SIZE                304


// ================EPPROM MAP ====================
//#define RM_ADDR_DOWNLOAD            (0)     // Must be at absolute address 0. The same as that in MApp_SaveData.h
//#define RM_SIZE_DOWNLOAD            ((U16)sizeof(ST_DOWNLOAD_INFO))
// 128 Bytes for bloader
#define RM_BOOTLOADER_ADDR              0 //(RM_ADDR_DOWNLOAD + RM_SIZE_DOWNLOAD)
#if (EEPROM_DB_STORAGE==EEPROM_SAVE_NONE)
    #define RM_SIZE_BOOTLOADER          0//RM_SIZE_BOOTLOADER_INIT
#else
    #define RM_SIZE_BOOTLOADER          0x80//RM_SIZE_BOOTLOADER_INIT
#endif
#define RM_BOOTLOADER_END_ADDR          (RM_BOOTLOADER_ADDR + RM_SIZE_BOOTLOADER)
//--------------------------------------------------------------------------------
#define RM_HDCP_KEY_ADDR                (RM_BOOTLOADER_END_ADDR)
#if (HDCP_KEY_TYPE==HDCP_KEY_IN_24C64)
  #define RM_SIZE_HDCP_KEY              HDCP_KEY_SIZE
#else
  #define RM_SIZE_HDCP_KEY              0
#endif
#define RM_HDCP_KEY_END_ADDR            (RM_HDCP_KEY_ADDR+RM_SIZE_HDCP_KEY)
//--------------------------------------------------------------------------------

#define RM_FACTORY_START_ADDR           (RM_HDCP_KEY_END_ADDR)
#define RM_FACTORY_SIZE                 (sizeof(MS_FACTORY_SETTING))
#define RM_FACTORY_END_ADDR             (RM_FACTORY_START_ADDR + RM_FACTORY_SIZE)

//--------------------------------------------------------------------------------

#define RM_GENSET_START_ADR             (RM_FACTORY_END_ADDR)
#define RM_SIZE_GENSET                  (sizeof(MS_GENSETTING))
#define RM_GENSET_END_ADR               (RM_GENSET_START_ADR + RM_SIZE_GENSET)

//--------------------------------------------------------------------------------

#define RM_GEN_BLOCK_TOTAL_USAGE_REAL   (RM_GENSET_END_ADR)

#if 0//( EEPROM_DB_STORAGE == EEPROM_SAVE_NONE)
    #define RM_GEN_USAGE                (QUICK_DB_GENST_SIZE)
#else
    //#define RM_GEN_USAGE                MemAlign((RM_GEN_BLOCK_TOTAL_USAGE_REAL-RM_ADDR_DOWNLOAD),8) //4K, for GENSETTING
    #define RM_GEN_USAGE                (RM_GEN_BLOCK_TOTAL_USAGE_REAL)
#endif

// Flash DB_GEN save range:
// RM_addr_0  ~  RM_GEN_USAGE
// Total save size is RM_GEN_USAGE

//======================================================================================================

#define RM_SYS_SETTING_ADDRESS          (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_SysSetting))

#define RM_SOUND_SETTING_ADDRESS        (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_SoundSetting))
#define RM_TIME_DATA_ADDRESS            (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_Time))
#define RM_SCANMENU_SETTING_ADDRESS     (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->stScanMenuSetting))
#define RM_BLOCK_DATA_ADDRESS           (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_BlockSysSetting))
#if ENABLE_GAMMA_ADJUST
#define RM_GAMMA_SETTING_ADDRESS        (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_GammaSetting))
#endif
#if ENABLE_SSC
#define RM_SSC_DATA_ADDRESS             (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_SSCSetting))
#endif
#if (ENABLE_NONLINEAR_CURVE)
#define RM_NONLINER_SETTING_ADDRESS     (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_NonLinearCurveSetting))
#endif

#if( FALSE == ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK )
#define RM_FACTORY_SETTING_DATA_ADDRESS  (RM_FACTORY_START_ADDR)   //(RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_FactorySetting))
#endif


#if ENABLE_DRM
#define RM_DRM_DATA_ADDRESS             (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_VDplayerDRMInfo))
#endif

#if (ENABLE_PIP)
#define RM_PIP_DATA_ADDRESS             (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_stPipSetting))
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#define RM_NETWORK_INFO_DATA_ADDRESS    (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_Network_TS))
#endif

#if ENABLE_CI
#define RM_CI_DATA_ADDRESS              (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_CISetting))
#endif

#if (ENABLE_CI && ENABLE_CI_PLUS)
//#define RM_CI_PLUS_DATA_ADDRESS         (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_CIKeySetting))
#define RM_CI_PLUS_DATA_ADDRESS         (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->stCIPlusSetting))
#endif


#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
#define RM_MM_LASTMEMORY_SETTING_ADDRESS (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_MmLastMemorySetting))
#endif


#define RM_GEN_VERSION_1_ADDRESS    (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->u8VersionCheck))
#define RM_GEN_VERSION_2_ADDRESS    (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->u8VersionCheckCom))



#endif


