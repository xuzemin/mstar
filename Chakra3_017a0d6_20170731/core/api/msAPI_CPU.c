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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (??MStar Confidential Information??) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
/// @file   drvdma.c
/// @brief  DRAM BDMA control driver
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Include List
////////////////////////////////////////////////////////////////////////////////

#include "Board.h"

//#include "SW_Config.h"
//#include "default_option_define.h"

#include "SysInit.h"
#include "debug.h"
#include "Utl.h"


#include "MsCommon.h"
#include "drvMIU.h"
#include "drvCPU.h"
#include "drvGlobal.h"

#include "msAPI_DrvInit.h"
#include "msAPI_BDMA.h"
#include "msAPI_MIU.h"

//#include "ms_decompress.h"


#include <stdlib.h>


//#include "sysinfo.h"

////////////////////////////////////////////////////////////////////////////////
// Local defines & local structures
////////////////////////////////////////////////////////////////////////////////

extern MS_BOOL _bOSD_On;

////////////////////////////////////////////////////////////////////////////////
// Local Global Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// External Funciton
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global Funciton
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_COPRO_Init()
/// @brief \b Function \b Description : Co-Processor initial
/// @param <IN>        \b None        :
/// @param <OUT>       \b pBinInfo    : Get Bin Information
/// @param <RET>       \b BOOL     : Success or Fail
/// @param <GLOBAL>    \b None        :
////////////////////////////////////////////////////////////////////////////////
#define MIU_MAX_PROTECT_ID       (16)

#define DEBUG_COPRO(x)  //x

void msAPI_COPRO_Init(MS_U16 u16BinID, MS_U32 u32_ADR, MS_U32 u32_LEN)
{
#if(!SUPPORT_AEON_MM)
    UNUSED(u16BinID);
    UNUSED(u32_ADR);
    UNUSED(u32_LEN);
#else
    BININFO BinInfo;
    U32 bin_addr = 0;
    BOOLEAN bResult;
    BinInfo.B_ID = u16BinID;
    MS_U8 u8MIUProtectAeon_ID[MIU_MAX_PROTECT_ID] = { 0 };
    _bOSD_On = FALSE;
    MS_U32 pageshift = 0;
#if ( ENABLE_AEON_MEM_USE_MIU_PROTECT )
    MS_U32 u32_ADREnd=u32_ADR+u32_LEN;
#endif

    DEBUG_COPRO( PRINT_CURRENT_LINE(); );

    DEBUG_COPRO( printf("msAPI_COPRO_Init(u16BinID=0x%X, u32_ADR=0x%X, u32_LEN=0x%X)\n", u16BinID, u32_ADR, u32_LEN); );

    memset(&u8MIUProtectAeon_ID[0], 0, sizeof(u8MIUProtectAeon_ID));


    // for fix compile waring - warning: unused parameter 'u32_LEN'
    u32_LEN = u32_LEN;

    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if( bResult != PASS )
    {
        printf("\nError: Can not find bin=0x%X\n", u16BinID);
        return;
    }

    bin_addr = BinInfo.B_FAddr;


    if( u16BinID == 0 )
    {
        printf("\nError: Bin ID is 0!\n");
        return;
    }

    if( !MDrv_COPRO_GetBase() )
    {
        printf("\nError: COPRO GetBase Error!");
        return;
    }

    //HK: AEON
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)
    u8MIUProtectAeon_ID[0] = MIU_CLIENT_MSP_ICACHE_RW;
#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET)
    MDrv_SetBEON_Host(1);
    u8MIUProtectAeon_ID[0] = MIU_CLIENT_SECURE_R2_RW;

#elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)
    u8MIUProtectAeon_ID[0] = MIU_CLIENT_SECURE_R2_RW;

 #elif( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) \
      ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)\
      )
    u8MIUProtectAeon_ID[0] = MIU_CLIENT_MAU0_RW;

#else
    u8MIUProtectAeon_ID[0] = MIU_CLIENT_MAU0_RW;
#endif

#if MHEG5_ENABLE
    if(BIN_ID_CODE_MHEG5 == u16BinID)
    {
        u8MIUProtectAeon_ID[1] = MIU_CLIENT_GE_RW;
#if ENABLE_CI_PLUS
  #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)
        u8MIUProtectAeon_ID[2] = MIU_CLIENT_TSP_JPD_RW;
  #else
        u8MIUProtectAeon_ID[2] = MIU_CLIENT_JPD_RW;
  #endif
#endif
    } else
#endif

#if ( ENABLE_AEON_MEM_USE_MIU_PROTECT )
 #if( VD_PLAYER_IS_IN_CROP_CPU )
    if(BIN_ID_CODE_VDPLAYER == u16BinID)
    {
        // Add HK-CPU to valid client
    #if defined(__aeon__)
        u8MIUProtectAeon_ID[1] = MIU_CLIENT_R2M_W;
        u8MIUProtectAeon_ID[2] = MIU_CLIENT_R2M_R;

    #elif defined(__mips__)

      #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET)
        u8MIUProtectAeon_ID[1] = MIU_CLIENT_MIPS_W;
        u8MIUProtectAeon_ID[2] = MIU_CLIENT_MIPS_R;

      #elif ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)   \
            ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)  \
            )
        u8MIUProtectAeon_ID[1] = MIU_CLIENT_MIPS_RW;

      #else

        #error "[IMPORTANT] Please choose the correct protection id for this chip !!!"

      #endif

    #endif
    }
 #endif
#endif


    MDrv_COPRO_Init_Front();

    MDrv_MIU_ProtectAlign(&pageshift);

    // Disable MIU protec for AeonMM mem
#if ( ENABLE_AEON_MEM_USE_MIU_PROTECT )
    MDrv_MIU_Protect(AEON_MEM_USE_MIU_PROTECT_BLOCK_ID, &u8MIUProtectAeon_ID[0], ALIGN(u32_ADR + ((1<<pageshift) - 1), pageshift), ALIGN(u32_ADREnd, pageshift), DISABLE);
#endif

#if (ENABLE_DTV && MHEG5_ENABLE)
    if(!MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32_ADR), _PA2VA(((MHEG5_BUFFER_MEMORY_TYPE&MIU1)?MHEG5_BUFFER_ADR|MIU_INTERVAL:MHEG5_BUFFER_ADR)), _PA2VA(MHEG5_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1)))
    {
        MS_DEBUG_MSG(printf("\r\n !Load Bin Fail!"));
    }
#else
    if(!MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32_ADR), _PA2VA((POOL_BUFFER_MEMORY_TYPE & MIU1 ?POOL_BUFFER_ADR | MIU_INTERVAL: POOL_BUFFER_ADR)), _PA2VA((POOL_BUFFER_MEMORY_TYPE & MIU1 ? POOL_BUFFER_ADR | MIU_INTERVAL: POOL_BUFFER_ADR)+BUF_FOR_DECOMPRESS_OFFSET1)))
    {
        printf("\r\n !Load Bin Fail!");
    }
#endif

    // Enable MIU protec for AeonMM mem
#if ( ENABLE_AEON_MEM_USE_MIU_PROTECT )
    if( (BIN_ID_CODE_MHEG5 == u16BinID)
    #if( VD_PLAYER_IS_IN_CROP_CPU )
      ||(BIN_ID_CODE_VDPLAYER == u16BinID)
    #endif
      )
    {
        MDrv_MIU_Protect(AEON_MEM_USE_MIU_PROTECT_BLOCK_ID, &u8MIUProtectAeon_ID[0], ALIGN(u32_ADR + ((1<<pageshift) - 1), pageshift), ALIGN(u32_ADREnd, pageshift), ENABLE);
    }
#endif

    MDrv_COPRO_Init_End(u32_ADR);
#endif
}

#if 0 // Nobody use it~
void msAPI_COPRO_Init_ByAddr(MS_U32 u32_ADR, MS_U32 u32_LEN) // fix me
{
    MS_U8 u8MIUProtectAeon_ID[2];

    u32_LEN=u32_LEN;
    _bOSD_On = FALSE;

    if( !MDrv_COPRO_GetBase() )
    {
        MS_DEBUG_MSG(printf("COPRO GetBase Error!\n"));
    }

    //HK: AEON
    u8MIUProtectAeon_ID[0] = MIU_CLIENT_MHEG5_ICACHE_RW;
    u8MIUProtectAeon_ID[1] = MIU_CLIENT_GE_RW;

    MDrv_COPRO_Init_Front();

    // Disable MIU protect-2

    MDrv_MIU_Protect(MIU_PROTECT_IDX_2, &u8MIUProtectAeon_ID[0], u32_ADR|MIU_INTERVAL, (u32_ADR + u32_LEN-1)|MIU_INTERVAL, DISABLE);

    MDrv_COPRO_Init_End(u32_ADR);

    // Enable MIU protect-2
    MDrv_MIU_Protect(MIU_PROTECT_IDX_2, &u8MIUProtectAeon_ID[0], u32_ADR|MIU_INTERVAL, (u32_ADR + u32_LEN-1)|MIU_INTERVAL, ENABLE);
}
#endif

void msAPI_COPRO_Disable(void)
{
#if 1
    msAPI_AEON_Disable();
#else
    msAPI_BEON_Disable();
#endif
}

