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

////////////////////////////////////////////////////////////////////////////////
//  [Doxygen]
/// @file msAPI_MIU.h
/// This file includes MStar application interface for MIU.
/// @brief API for MIU
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_MIU_C

#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "datatype.h"
#include "sysinfo.h"
#include "drvMIU.h"
#include "SysInit.h"
#include "hal_misc.h"

#include "drvSERFLASH.h"
#include "GPIO.h"
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"
#include "msAPI_OSD_Resource.h"
#include "msAPI_Timer.h"

#include "hwreg.h"
#include "MsOS.h"
#include "msAPI_Global.h"

#include "MApp_SaveData.h"

#define APIMIU_DBG(y) //y

static U32 bmpaddr;


#if 0//(SWCHECKSUM_SWITCH)
static U32 CCSAddress;
static U8 CCSValue;
#endif


/******************************************************************************/
/// API for MIU initialization::
/// Initialize bitmap, font buffer address and size.
/// Initialize flash, SRAM and SDRAM base address and length.
/******************************************************************************/
void msAPI_MIU_Init()
{
    bmpaddr = GE_ADDR_ALIGNMENT(((BMP_START_MEMORY_TYPE & MIU1) ? (BMP_START_ADR | MIU_INTERVAL) : (BMP_START_ADR)));

    #if(SWCHECKSUM_SWITCH)
    CCSAddress = CODE_MAP_BASE_ADR;
    CCSValue = 0;
    #endif
}


/******************************************************************************/
/// MIU Load Bitmap
/// Copy bitmap table from flash to SDRAM
/// @param u16ID \b IN ID of the bitmap
/// @param u16width \b IN Bitmap width
/// @param u16height \b IN Bitmap height
/******************************************************************************/
BMPHANDLE msAPI_MIU_LoadFlashBitmap(U16 u16ID, U16 u16width, U16 u16height)
{
    BMPHANDLE   handle = INVALID_BMPHANDLE;
    BININFO   BinInfo;
    BOOLEAN bResult;

    BinInfo.B_ID = u16ID;
      msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS )
    {
        //printf("Error msAPI_MIU_LoadFlashBitmap: ID=0x%X\n", u16ID);
        return INVALID_BMPHANDLE;
    }

    if (bmpaddr + BinInfo.B_Len <= ((BMP_START_MEMORY_TYPE & MIU1) ? (BMP_START_ADR | MIU_INTERVAL) : (BMP_START_ADR))+ BMP_START_LEN)
    {
        MApi_BDMA_XCopy(MCPY_LOADBITMAP, BinInfo.B_FAddr, bmpaddr, BinInfo.B_Len);
        handle = msAPI_OSD_RESOURCE_LoadBitmap(bmpaddr, BinInfo.B_Len, u16width, u16height, BMP_FMT_ARGB1555);
        bmpaddr = GE_ADDR_ALIGNMENT(bmpaddr + BinInfo.B_Len);
    }
    else
    {
        msWarning(ERR_BMP_OUT_OF_BUFFER);
        //printf("not enough, bmpaddr=%x Binfo.B_Len=%x \r\n", bmpaddr, BinInfo.B_Len);
        //printf("BMP_START_ADR=%x, BMP_START_LEN=%x \r\n", ((BMP_START_MEMORY_TYPE & MIU1) ? (BMP_START_ADR | MIU_INTERVAL) : (BMP_START_ADR)), BMP_START_LEN);
    }

    return handle;
}

//OSDCOMPOSER
BMPHANDLE msAPI_MIU_LoadFlashBitmap_Osdcp(U32 u32addr, U16 u16width, U16 u16height)
{
    U32 u32dstaddr = bmpaddr;
    U32 u32len = (U32)u16width*u16height*2;

    //MDrv_MIU_XCopy(MCPY_LOADBITMAP, u32addr, u32dstaddr, u32len);
    msAPI_MIU_Copy(u32addr, u32dstaddr, GE_ALIGNED_VALUE(u32len,8), MIU_FLASH2SDRAM);
    bmpaddr = GE_ADDR_ALIGNMENT(bmpaddr + u32len);

    return msAPI_OSD_RESOURCE_LoadBitmap( u32dstaddr, u32len, u16width, u16height, BMP_FMT_ARGB1555 );
}

#if 0
/******************************************************************************/
// s32size must be a multiple of 64KB
void msAPI_MIU_SDRAM2Flash(U32 u32srcaddr, U32 u32desaddr, S32 s32size)    // SRAM2Flash
{
    U16 count;
    U8 *flash_buf;

    flash_buf = (U8*)msAPI_Memory_Allocate(FLASH_BUF_SIZE,BUF_ID_FLASH);
    if (flash_buf == NULL)
    {
        //printf("malloc flash_buf fail!\n");
        return;
    }

    APIMIU_DBG(printf("StoreSDRAM2Flash, src=0x%Lx, dst=0x%Lx, size=0x%Lx\n", u32srcaddr, u32desaddr, s32size));
    MDrv_FLASH_AddressErase(u32desaddr, s32size, TRUE);
    while (s32size > 0)
    {
        count = MIN(s32size, FLASH_BUF_SIZE);

        msAPI_MIU_Copy(u32srcaddr, XD2PHY(flash_buf), count, MIU_SDRAM2SDRAM);
        u32srcaddr += count;

        MDrv_Flash_Write(u32desaddr, count, flash_buf);
        u32desaddr += count;
        s32size -= count;
    }

    msAPI_Memory_Free(flash_buf,BUF_ID_FLASH);
}
#endif

/******************************************************************************/
/// Convert XDATA address in 0x2800-0xBFFF to physical SDRAM address
/// @param u16addr \n IN: address in XDATA
/// @return U32: physical address in SDRAM
/******************************************************************************/
U32 msAPI_MIU_XData2SDRAMAddr(U32 u32addr)
{
    return XD2PHY(u32addr);
}

/******************************************************************************/
/// API for MIU Copy::
/// Memory Copy Interface
/// @param srcaddr \b IN Source address
/// @param dstaddr \b IN Destination address
/// @param len \b IN Size
/// @param type \b IN The Type of Memory copy
/******************************************************************************/
void msAPI_MIU_Copy(MS_PHYADDR srcaddr, MS_PHYADDR dstaddr, U32 len, MEMCOPYTYPE type)
{
    APIMIU_DBG(printf("msAPI_MIU_Copy( Src = 0x%08LX, Dst = 0x%08LX, Len = 0x%LX , Type = 0x%02bx\n", srcaddr, dstaddr, len, type));

    CHECK_PHY_ADDR(dstaddr);
    CHECK_PHY_ADDR(srcaddr);

    if(type==MIU_FLASH2SDRAM)
    {
        MApi_BDMA_CopyFromResource(srcaddr, _PA2VA(dstaddr), len);
    }
    else
    {
        MApi_BDMA_Copy(srcaddr, dstaddr, len, type);
    }
}

// If data different, return TRUE
#define bDebugMsg  0
#if (bDebugMsg)
    #define DEBUG_MIU_COMPARE(x)    x
#else
    #define DEBUG_MIU_COMPARE(x)    //x
#endif
BOOL msAPI_MIU_CompareBuf(U32 u32MemAddr, U8* pu8Buf, U32 u32CompareSize)
{
    BOOL bDataDifferent = FALSE;

    if( bDebugMsg )
    {
        DEBUG_MIU_COMPARE(printf("msAPI_MIU_CompareBuf(u32MemAddr=0x%X,u32CompareSize=%u )\n", u32MemAddr, u32CompareSize ););
    }

#if (bDebugMsg) //for debug
    U8* pu8MemVA;
    U32 i;

    pu8MemVA = (U8*)MsOS_PA2KSEG1(u32MemAddr);

    for( i = 0; i < u32CompareSize; ++ i)
    {
        if( bDebugMsg )
        {
            printf("%X %X -> ", pu8MemVA[i], pu8Buf[i]);
            if( pu8MemVA[i] == pu8Buf[i] )
                printf("O");
            else
                printf("X");
            printf("\n");
        }
        if( pu8MemVA[i] != pu8Buf[i])
        {
            bDataDifferent = TRUE;
            printf("1 data diff\n");
        }
    }
#endif


    U32 u32MemVA;

    // Convert to virtual address
    u32MemVA = MsOS_PA2KSEG1(u32MemAddr);

    MsOS_FlushMemory();

    // Check if data changed
    if( memcmp( (const void *)u32MemVA, (const void *)pu8Buf, u32CompareSize) != 0 )
    {
        bDataDifferent = TRUE;
        DEBUG_MIU_COMPARE(printf("2 data diff\n"););
    }


    if( bDebugMsg )
    {
        if( bDataDifferent )
        {
            DEBUG_MIU_COMPARE(printf(" Comp => changed\n"););
        }
        else
        {
            DEBUG_MIU_COMPARE(printf(" Comp => No changed\n"););
        }
    }

    return bDataDifferent;
}

#if (DISPLAY_LOGO)
/******************************************************************************/
/// API for MIU Load LOGO::
/// Copy LOGO from flash to SDRAM
/// @param u32Flashaddr \b IN Flash address
/// @param u32Dstaddr \b IN SDRAM address
/// @param u32Len \b IN LOGO size in bytes
/******************************************************************************/
void msAPI_MIU_LoadLogo(U32 u32Flashaddr, U32 u32Dstaddr, U32 u32Len)
{
#if 0//defined(MSOS_TYPE_LINUX)
    MApi_BDMA_CopyFromResource(u32Flashaddr, _PA2VA(u32Dstaddr), u32Len);
#else
    MApi_BDMA_XCopy(MCPY_LOADLOGO, u32Flashaddr, u32Dstaddr, u32Len);
#endif
}
#endif

#if 0
/******************************************************************************/
/// API for MIU Clear SDRAM::
/// Memory Clear Interface
/// @param miu \b IN MIU Selection. (0: MIU0, 1: MIU1)
/// @param addr \b IN Starting address
/// @param len \b IN Size in byte
/// @param clear_value \b IN One-byte value to set
/******************************************************************************/
void msAPI_MIU_Clear(U8 miu, U32 addr, U32 len, U8 clear_value)
{
    miu=miu;   //for remove warnning message
    MDrv_GE_ClearFrameBuffer( addr, len, clear_value);

}
#endif

#if 0
/******************************************************************************/
/// API for MIU Set Flash Bin Packet Header Address::
/// Set Header address
/// @param addr \b IN Header address
/******************************************************************************/
void msAPI_MIU_Set_BinHeader_Addr(U32 addr)
{
    MDrv_MIU_Set_BinHeader_Addr(addr);
}

/******************************************************************************/
/// API for MIU Get Flash Bin Packet Header Address::
/// Get Header address
/// @return Header address
/******************************************************************************/
U32 msAPI_MIU_Get_BinHeader_Addr(void)
{
    return MDrv_MIU_Get_BinHeader_Addr();
}

/******************************************************************************/
/// API for MIU to map xdata space for DVB SI table monitor::
/// Map table monitor space to xdata
/// @param u32SdramBase \b IN SDRAM base address to be mapped to xdata space
/******************************************************************************/
void msAPI_MIU_MapSIData(U32 u32SdramBase)
{
    MDrv_Sys_SetXdataWindow1Base(u32SdramBase/4096);
}
#endif

/******************************************************************************/
#if 0//(SWCHECKSUM_SWITCH)
#define CCSLength 32
void msAPI_MIU_CCS(void)
{
    U8 CCSBufer[CCSLength], i;

    if(CCSAddress >= CODE_MAP_BASE_ADR + CODE_MAP_LEN)
        CCSAddress = CODE_MAP_BASE_ADR;

    if (((CCSAddress - CODE_MAP_BASE_ADR) & 0xFFFF) == 0x0)
    {
        if (CCSValue != 0)
        {
            #if 0
            MDrv_Sys_SetWatchDogTimer(0);
            MDrv_Sys_EnableWatchDog();
            while(1);
            #else
            MDrv_Sys_WholeChipReset();
            #endif
        }
    }

    MApi_BDMA_XCopy(MCPY_CCS, CCSAddress, XD2PHY(&CCSBufer[0]), CCSLength);
    CCSAddress += CCSLength;

    for(i=0; i<CCSLength; i++)
        CCSValue += CCSBufer[i];
}
#endif

#if ENABLE_SSC
void msAPI_MIU_SetSsc(U16 u16Periodx100Hz, U16 u16Percentx100, BOOLEAN bEnable)
{
#if 0 //Not ready!!
    u16Periodx100Hz = u16Periodx100Hz;
    u16Percentx100 = u16Percentx100;
    bEnable = bEnable;
#else
//printf(" msAPI_MIU_SetSsc0 %d %d %d", u16Periodx100Hz, u16Percentx100, bEnable);
    MDrv_MIU_SetSsc(u16Periodx100Hz, u16Percentx100, bEnable);
//printf(" msAPI_MIU_SetSsc1 %d %d %d", u16Periodx100Hz, u16Percentx100, bEnable);
#endif
}
/*
void msAPI_MIU_SetSsc(U16 u16Periodx100Hz, U16 u16Percentx100)
{
    MDrv_MIU_SetSsc(u16Periodx100Hz, u16Percentx100);
}
*/
#endif


void msAPI_MIU_SetRoundRobin(BOOLEAN bEnable)
{
    bEnable = bEnable;
//    MDrv_MIU_SetRoundRobin(bEnable);
}


#if 0
void msAPI_MIU_SetGEFlowControl(BOOLEAN bEnable)
{
    MDrv_MIU_SetGEFlowControl(bEnable);
}
#endif

/******************************************************************************/
/// API for MIU XCOPY F/W Status::
/// Set F/W source status
/// @param bFWStatus \b IN F/W source status
///                         TRUE:   F/W is on Nand Flash
///                         FALSE:  F/W is on SPI Flash
/******************************************************************************/
void msAPI_MIU_Clear(U8 miu, U32 addr, U32 len, U8 clear_value)
{
    U32 tempaddr;

    UNUSED(miu);

    tempaddr = (addr &0x7FFFFFFF);
    if(tempaddr >= 0x8000000)
    {
        tempaddr -=  0x8000000;
        tempaddr += 0x80000000;
    }

    MApi_GFX_ClearFrameBuffer(tempaddr, len, clear_value);
}

void msAPI_MIU_WriteMemByte(U32 u32MemAddr, U8 u8Data )
{
    U8 *pu8;
    pu8 = (U8*)MsOS_PA2KSEG1(u32MemAddr);

    MsOS_FlushMemory();
    *pu8 = u8Data;
    MsOS_FlushMemory();
}

void msAPI_MIU_WriteMemBytes(U32 u32MemAddr, U8* pu8Data, U32 u32Size )
{
    U32 i;
    U8 *pu8;

    pu8 = (U8*)MsOS_PA2KSEG1(u32MemAddr);

    MsOS_FlushMemory();

    for( i = 0; i < u32Size; ++ i )
    {
        *pu8 = pu8Data[i];
        pu8 += 1;
    }

    MsOS_FlushMemory();
}

U8 msAPI_MIU_ReadMemByte(U32 u32MemAddr )
{
    U8 *pu8;

    pu8 = (U8*)MsOS_PA2KSEG1(u32MemAddr);

    MsOS_FlushMemory();

    return *pu8;
}

void msAPI_MIU_ReadMemBytes(U32 u32MemAddr, U8* pu8Data, U32 u32Size )
{
    U32 i;
    U8 *pu8;

    pu8 = (U8*)MsOS_PA2KSEG1(u32MemAddr);

    MsOS_FlushMemory();

    for( i = 0; i < u32Size; ++ i )
    {
        pu8Data[i] = *pu8;
        pu8 += 1;
    }
}

#if( ENABLE_API_MIU_PROTECT )
BOOL MDrv_MIU_Get_ProtectHitLog(StuMiuHitProtectLog* pProtectHitLog)
{
    U16 u16RegVal_12DE = MHAL_MIU_Get_ProtectHitLog();//MDrv_Read2Byte(0x1012DE);

    //printf("u16RegVal_12DE=0x%X\n", u16RegVal_12DE);
    if( u16RegVal_12DE&BIT4 )
    {
        pProtectHitLog->bHitFlag = 1;
        pProtectHitLog->u8ProtectNo = (u16RegVal_12DE>>5)&0x7;
        // bit14~8: reg_r_hit_protect_id
        //
        pProtectHitLog->u8Group = (u16RegVal_12DE>>12)&0xF;
        pProtectHitLog->u8ClientID = (u16RegVal_12DE>>8)&0xF;

        pProtectHitLog->u32Address = /*MDrv_Read4Byte(0x1012DA)*/ MHAL_MIU_Get_ProtectHitAddr() * 32;
    }
    else
    {
        pProtectHitLog->bHitFlag = 0;
    }

    return pProtectHitLog->bHitFlag;
}

void MDrv_MIU_Clr_ProtectHitLog(void)
{
    //MDrv_WriteRegBit(0x1012DE, 1, BIT0);
    //MDrv_WriteRegBit(0x1012DE, 0, BIT0);
    MHAL_MIU_ClearProtectHitLog();
}

void msAPI_MIU_PrintProtectLog(void)
{
    StuMiuHitProtectLog log;

    msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);

    printf("MIU Hit protect log:\n");
    if( MDrv_MIU_Get_ProtectHitLog( &log) )
    {
        printf(" Hit happened:\n");
        printf(" u8ProtectNo=%u, Group=0x%X, Id = 0x%X\n", log.u8ProtectNo, log.u8Group, log.u8ClientID);
        if( log.u32Address != 0xFFFFFFFF )
        {
            printf(" Addr=0x%X ~ 0x%X\n", log.u32Address, log.u32Address+31 );
        #if 0//( CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON )
            printf(" Addr=0x%X ~ 0x%X\n", log.u32Address*4, log.u32Address*4+127 );
        #endif
        }
    }
    else
    {
        printf(" No log\n");
    }

    msDebug_ANSI_AllAttrOffText();
}

char msAPI_MIU_Check_Log(char* pcName, int iLine)
{
    /*MsOS_Dcache_Flush(0x20B30000, 0xA00000); */
    /*MsOS_Dcache_Flush(0x20000000, 0x100000*512); */
    /*MsOS_FlushMemory(); */

    char cResult = 0;

    StuMiuHitProtectLog tmpMiuProtectInfo;

    if( MDrv_MIU_Get_ProtectHitLog(&tmpMiuProtectInfo) )
    {
        printf("\nError: MIU protect hit log at %s %u\n", pcName, iLine);
        msAPI_MIU_PrintProtectLog();

        cResult = 1;
    }

    return cResult;
}

char msAPI_MIU_Check_Log_And_Clear(char* pcName, int iLine)
{
    /*MsOS_Dcache_Flush(0x20B30000, 0xA00000); */
    /*MsOS_Dcache_Flush(0x20000000, 0x100000*512); */
    /*MsOS_FlushMemory(); */

    char cResult = 0;

    StuMiuHitProtectLog tmpMiuProtectInfo;

    if( MDrv_MIU_Get_ProtectHitLog(&tmpMiuProtectInfo) )
    {
        printf("\nError: MIU protect hit log at %s %u\n", pcName, iLine);
        msAPI_MIU_PrintProtectLog();
        MDrv_MIU_Clr_ProtectHitLog();

        cResult = 1;
    }

    return cResult;
}

#endif

void msAPI_MIU_Task(void)
{
    // Check MIU protect hit
#if( ENABLE_API_MIU_PROTECT )
    StuMiuHitProtectLog stMiuProtectInfo;
    static U8 _s_u8PrintLogTime = 0;


    MDrv_MIU_Get_ProtectHitLog(&stMiuProtectInfo);

    if( stMiuProtectInfo.bHitFlag )
    {
        printf("\n===== Miu protect hit happeded! =====\n");
        //printf(" u8Block = %X\n", stMiuProtectInfo.u8Block);
        //printf(" u8Group = %X,", stMiuProtectInfo.u8Group);
        //printf(" u8ClientID = %X\n", stMiuProtectInfo.u8ClientID);
        printf(" u8ProtectNo=%u, Group=0x%X, Id = 0x%X\n", stMiuProtectInfo.u8ProtectNo, stMiuProtectInfo.u8Group, stMiuProtectInfo.u8ClientID);
        printf(" Addr=0x%X ~ 0x%X\n", stMiuProtectInfo.u32Address, stMiuProtectInfo.u32Address+31 );

        if( _s_u8PrintLogTime < 3 )
        {
            _s_u8PrintLogTime += 1;
        }
        else
        {
            MDrv_MIU_Clr_ProtectHitLog();
            _s_u8PrintLogTime = 0;
        }
    }
    else
    {
        _s_u8PrintLogTime = 0;
    }

#endif

#if(ENABLE_MIU_BWC)
    msAPI_MIU_BWC_Task();
#endif
}

BOOL msAPI_MIU_Set_MiuProtect(U8 u8ProtectIdx, U8 *pu8ProtectId, U32 u32Start, U32 u32End, BOOL bEnable)
{
    U32 u32MiuProtectAlign;
    U32 u32MiuProtectAddr_Start;
    U32 u32MiuProtectAddr_End;
    U8 au8ProtectIds_Empty[1]= {0};
    U8* pu8ProtectId_final;


    printf("msAPI_MIU_Set_MiuProtect(u8ProtectIdx=%u, u32Start=0x%X, u32End=0x%X, bEnable=%u)\n", u8ProtectIdx, u32Start, u32End, bEnable);


    MDrv_MIU_ProtectAlign(&u32MiuProtectAlign);

    u32MiuProtectAddr_Start = ALIGN(u32Start + ((1<<u32MiuProtectAlign) - 1), u32MiuProtectAlign);
    u32MiuProtectAddr_End = ALIGN(u32End, u32MiuProtectAlign);

    if( bEnable )
    {
        printf("Miu protect align = %u(0x%X)\n", u32MiuProtectAlign, 1 << u32MiuProtectAlign);
        printf("Miu protect: 0x%X ~ 0x%X\n", u32Start, u32End);
        printf("Miu protect-align: 0x%X ~ 0x%X\n", u32MiuProtectAddr_Start, u32MiuProtectAddr_End );
    }

    if( pu8ProtectId )
    {
        pu8ProtectId_final = pu8ProtectId;
    }
    else
    {
        pu8ProtectId_final = au8ProtectIds_Empty;
    }

    MDrv_MIU_Protect(
        u8ProtectIdx,
        pu8ProtectId_final,
        u32MiuProtectAddr_Start, u32MiuProtectAddr_End,
        bEnable);

    return FALSE;
}


#if(ENABLE_MIU_BWC)

//#define REG_MIU_BWC_W   (MIU_REG_BASE + 0x1A)//0x10121A => reg_deb_sel
//#define REG_MIU_BWC_R   (MIU_REG_BASE + 0x1C)//0x10121C => reg_r_deb_bus

#define MIU_BWC_IP_NUM      0x30
#define MIU_BWC_READ_TIME   10
#define MIU_BWC_READ_DELAY  2000 // us

#define MIU_BWC_AVG_WAIT_TIME   10 // 20

typedef enum
{
    MIU_BWC_STATE_NONE,

    MIU_BWC_STATE_AVG_START,
    MIU_BWC_STATE_AVG_SEL_IP_RESET,
    MIU_BWC_STATE_AVG_SEL_IP,
    MIU_BWC_STATE_AVG_WAIT_AND_GET_INFO,

    MIU_BWC_STATE_AVG_REPORT,

} EnuMiuBWCheckState;

static EnuMiuBWCheckState s_MIU_BWC_eState = MIU_BWC_STATE_NONE;
static U8 s_MIU_BWC_u8CurClient;
static U32 s_MIU_BWC_u32WaitTime;

static U16 s_MIU_BWC_au16BW[MIU_BWC_IP_NUM][MIU_BWC_READ_TIME];

void msAPI_MIU_BWC_Set_Enable(BOOL bEnable)
{
    if( bEnable )
    {
        memset( (U8*)s_MIU_BWC_au16BW, 0, sizeof(s_MIU_BWC_au16BW) );
        s_MIU_BWC_eState = MIU_BWC_STATE_AVG_START;
    }
    else
    {
        s_MIU_BWC_eState = MIU_BWC_STATE_NONE;
    }
}

void msAPI_MIU_BWC_PrintBWArray(void)
{
    U8 i, j;
    BOOL bIpUseMiu;


    printf("s_MIU_BWC_au16BW[][]=\n");
    for( i = 0; i < MIU_BWC_IP_NUM; ++ i )
    {
        bIpUseMiu = FALSE;
        for( j = 0; j < MIU_BWC_READ_TIME; ++ j )
        {
            if( s_MIU_BWC_au16BW[i][j] )
            {
                bIpUseMiu = TRUE;
                break;
            }
        }

        if( bIpUseMiu )
        {
            printf("[0x%X]", i );
            for( j = 0; j < MIU_BWC_READ_TIME; ++ j )
            {
                printf("%u,", s_MIU_BWC_au16BW[i][j] );
            }
            printf("\n" );
        }
    }
}

void msAPI_MIU_BWC_Task(void)
{
    U16 u16Tmp;

    switch(s_MIU_BWC_eState)
    {
        default:
        case MIU_BWC_STATE_NONE:
            break;

        case MIU_BWC_STATE_AVG_START:
            s_MIU_BWC_u8CurClient = 0;
            s_MIU_BWC_eState = MIU_BWC_STATE_AVG_SEL_IP_RESET;
            break;

        case MIU_BWC_STATE_AVG_SEL_IP_RESET:
            u16Tmp = (s_MIU_BWC_u8CurClient<<8)|0x40; // average
            //MDrv_Write2Byte(REG_MIU_BWC_W, u16Tmp); // Sel client and clear
            MHAL_MIU_Set_DebugSel(u16Tmp); // Sel client and clear
            s_MIU_BWC_eState = MIU_BWC_STATE_AVG_SEL_IP;
            break;

        case MIU_BWC_STATE_AVG_SEL_IP:
            u16Tmp = (s_MIU_BWC_u8CurClient<<8)|0x41; // average
            //MDrv_Write2Byte(REG_MIU_BWC_W, u16Tmp); // Sel client and start record
            MHAL_MIU_Set_DebugSel(u16Tmp); // Sel client and start record
            s_MIU_BWC_u32WaitTime = MsOS_GetSystemTime();
            s_MIU_BWC_eState = MIU_BWC_STATE_AVG_WAIT_AND_GET_INFO;
            break;

        case MIU_BWC_STATE_AVG_WAIT_AND_GET_INFO:
            if( msAPI_Timer_DiffTime_2(s_MIU_BWC_u32WaitTime, MsOS_GetSystemTime()) >= MIU_BWC_AVG_WAIT_TIME )
            {
                // Get BW info
                //s_MIU_BWC_au16BW[s_MIU_BWC_u8CurClient] = MDrv_Read2Byte(REG_MIU_BWC_R);
                for( u16Tmp = 0; u16Tmp < MIU_BWC_READ_TIME; ++u16Tmp )
                {
                    s_MIU_BWC_au16BW[s_MIU_BWC_u8CurClient][u16Tmp] = MHAL_MIU_Get_DebugPort();
                    msAPI_Timer_DelayUs(MIU_BWC_READ_DELAY);
                }

                // Change to next client
                s_MIU_BWC_u8CurClient += 1;

                if( s_MIU_BWC_u8CurClient >= MIU_BWC_IP_NUM )
                {
                    s_MIU_BWC_eState = MIU_BWC_STATE_AVG_REPORT;
                }
                else
                {
                    s_MIU_BWC_eState = MIU_BWC_STATE_AVG_SEL_IP_RESET;
                }
            }
            break;

        case MIU_BWC_STATE_AVG_REPORT:
            msAPI_MIU_BWC_PrintBWArray();
            s_MIU_BWC_eState = MIU_BWC_STATE_NONE;
            break;

    }
}
#endif


#undef MSAPI_MIU_C
