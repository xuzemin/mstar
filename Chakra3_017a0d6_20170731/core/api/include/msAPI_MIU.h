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

#ifndef MSAPI_MIU_H
#define MSAPI_MIU_H

#include "datatype.h"
#include "sysinfo.h"
#include "msAPI_Font.h"

#include "drvSERFLASH.h"
#include "SysInit.h"
#include "msAPI_OSD.h"
#include "msAPI_BDMA.h"
#include "drvMIU.h"


#ifdef MSAPI_MIU_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define ENABLE_AUTO_DQS_Factory    0
#define ENABLE_AUTO_DQS_Design    0


#define MIU_MCU_WRITE_BLK_ID 13
#define msAPI_MIU_GetW1StartAddress() 0xF000
#define msAPI_MIU_Set_DRAM2DRAM_Mode(mode)

////////////////////////////////////////////////////

typedef enum
{
    MIU_PROTECT_IDX_0,
    MIU_PROTECT_IDX_1,
    MIU_PROTECT_IDX_2,
    MIU_PROTECT_IDX_3,
} EnuMiuProtectIdx;


INTERFACE void msAPI_MIU_Init(void);
void msAPI_MIU_Set_TTX_FontInfo(U8 charSize, U16 fontID);
INTERFACE FONTHANDLE msAPI_MIU_LoadFlashFont_TTX(U16 u16BinID, U8 u8GlyphSize,
    U16 u16char_num, U8 u8width, U8 u8height, FONTHANDLE fHandle);
INTERFACE BMPHANDLE msAPI_MIU_LoadFlashBitmap(U16 u16ID, U16 u16width, U16 u16height);

INTERFACE U32 msAPI_MIU_XData2SDRAMAddr(U32 u32addr);
INTERFACE void msAPI_MIU_LoadLogo(U32 u32Flashaddr, U32 u32Dstaddr, U32 u32Len);
INTERFACE void msAPI_MIU_Clear(U8 miu, U32 addr, U32 len, U8 clear_value);
//#define msAPI_MIU_Clear(a,x,y,z)    MDrv_GE_ClearFrameBuffer(x,y,z)

//INTERFACE void msAPI_MIU_Set_BinHeader_Addr(U32 addr);
//INTERFACE U32 msAPI_MIU_Get_BinHeader_Addr(void);

#define msAPI_MIU_Set_BinHeader_Addr(u32Addr) MDrv_MIU_Set_BinHeader_Addr(u32Addr)
#define msAPI_MIU_Get_BinHeader_Addr() MDrv_MIU_Get_BinHeader_Addr()

// u8XBase and u8XSize are xdata address and should be multiple of 1k bytes.
//INTERFACE void msAPI_MIU_MapSIData(U32 u32SdramBase);
//#define msAPI_MIU_MapSIData(u32MiuBase) MDrv_Sys_SetXdataWindow1Base((u32MiuBase)/4096)

INTERFACE void msAPI_MIU_SDRAM2Flash(U32 u32srcaddr, U32 u32desaddr, S32 s32size);
INTERFACE void msAPI_MIU_Copy(U32 u32srcaddr, U32 u32dstaddr, U32 u32len, MEMCOPYTYPE type);
BOOL msAPI_MIU_CompareBuf(U32 u32MemAddr, U8* pu8Buf, U32 u32CompareSize);


//INTERFACE BOOLEAN msAPI_MIU_Get_BinInfo(BININFO *pBinInfo);
#define msAPI_MIU_Get_BinInfo(pBinInfo, pbResult) MDrv_Sys_Get_BinInfo(pBinInfo, pbResult)
INTERFACE void msAPI_MIU_CCS(void);

//OSDCOMPOSER
INTERFACE BMPHANDLE msAPI_MIU_LoadFlashBitmap_Osdcp(U32 u32addr, U16 u16width, U16 u16height);

#if ENABLE_SSC
INTERFACE void msAPI_MIU_SetSsc(U16 u16Periodx100Hz, U16 u16Percentx100, BOOLEAN bEnable);
#endif

INTERFACE void msAPI_MIU_SetRoundRobin(BOOLEAN bEnable);
//INTERFACE void msAPI_MIU_SetGEFlowControl(BOOLEAN bEnable);

//=====================================================

void msAPI_MIU_WriteMemByte(U32 u32MemAddr, U8 u8Data );
void msAPI_MIU_WriteMemBytes(U32 u32MemAddr, U8* pu8Data, U32 u32Size );
U8 msAPI_MIU_ReadMemByte(U32 u32MemAddr );
void msAPI_MIU_ReadMemBytes(U32 u32MemAddr, U8* pu8Data, U32 u32Size );

//=====================================================

INTERFACE void msAPI_MIU_Task(void);

#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)\
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)\
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)\
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)\
   )
    #define ENABLE_API_MIU_PROTECT  1
#else
    #define ENABLE_API_MIU_PROTECT  0
#endif

#if( ENABLE_API_MIU_PROTECT )

typedef struct
{
    BOOL bHitFlag;
    U8 u8ProtectNo;
    //U8 u8Id;
    U8 u8Group;
    U8 u8ClientID;

    U32 u32Address;
}StuMiuHitProtectLog;

BOOL MDrv_MIU_Get_ProtectHitLog(StuMiuHitProtectLog* pProtectHitLog);
void MDrv_MIU_Clr_ProtectHitLog(void);

void msAPI_MIU_PrintProtectLog(void);

char msAPI_MIU_Check_Log(char* pcName, int iLine);
char msAPI_MIU_Check_Log_And_Clear(char* pcName, int iLine);

/*
#define MIU_CHECK_PROTECT_HIT_HAPPEN()  do {    \
    StuMiuHitProtectLog tmpMiuProtectInfo;           \
    MsOS_Dcache_Flush(0, 0x600000);             \
    MsOS_FlushMemory();                         \
    MsOS_DelayTask(10);                             \
    if( MDrv_MIU_Get_ProtectHitLog(&tmpMiuProtectInfo) )                       \
    {                                               \
        printf("\nError: MIU protect hit log at %s %u\n", __FILE__, __LINE__); \
        msAPI_MIU_PrintProtectLog(); \
    }    \
} while(0)
*/

#define CHECK_MIU_PROTECT_LOG() do {        \
    msAPI_MIU_Check_Log(__FILE__, __LINE__);    \
} while(0) \


#define CHECK_MIU_PROTECT_LOG_AND_CLEAR() do {        \
    msAPI_MIU_Check_Log_And_Clear(__FILE__, __LINE__);  \
    } while(0) \


#else

    #define CHECK_MIU_PROTECT_LOG()     //do { } while(0)
    #define CHECK_MIU_PROTECT_LOG_AND_CLEAR()

#endif

//======================================================
#define ENABLE_MIU_BWC     0

#if(ENABLE_MIU_BWC)
void msAPI_MIU_BWC_Set_Enable(BOOL bEnable);
void msAPI_MIU_BWC_Task(void);
#endif


//======================================================

BOOL msAPI_MIU_Set_MiuProtect(U8 u8ProtectIdx, U8 *pu8ProtectId, U32 u32Start, U32 u32End, BOOL bEnable);

//======================================================


#undef INTERFACE
#endif
