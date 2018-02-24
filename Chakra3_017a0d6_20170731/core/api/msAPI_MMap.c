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
//  Description: Memory mapping information package
//
///////////////////////////////////////////////////////////////////////////////
#define MSAPI_MMAP_C

#include "Board.h"

#include "sysinfo.h"

#include "drvGlobal.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "msAPI_Global.h"
#include "msAPI_MailBox.h"
#include "msAPI_MMap.h"
#include "msAPI_Timer.h"

#include "MApp_UiMediaPlayer_Define.h"




#define MMAPDBG(x)  //x

#if DYNAMIC_MMAP_FOR_BEON

//-----------------------------------------------
// Memory map structure
//-----------------------------------------------
typedef struct __attribute__ ((__packed__))
{
    U8 MIU_Number;
    U8 MMAP_Block_ID;
    U32 MMAP_Start_Address;
    U32 MMAP_Length;
} MMAP_ID_FMT;


//-----------------------------------------------
// MIU ID
//-----------------------------------------------
// Memory block ID define for MCU
#define MIUNUM_0                0x00
#define MIUNUM_1                0x01

//AEON will search this table content by Memory Block ID.
MMAP_ID_FMT MemoryMap[] =
{
    // MIU Number,  Memory Block ID,        Start Address,                  Memory Length

 #if defined(MIPS_CHAKRA) || defined (__AEONR2__) ||defined(ARM_CHAKRA)
    {MIUNUM_0,      MMAP_ID_BEON_A,         ((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MEM_ADR | MIU_INTERVAL) : ( AEON_MEM_ADR)),                   AEON_MEM_LEN},
 #else
    {MIUNUM_0,      MMAP_ID_BEON_A,         ((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)),                   BEON_MEM_LEN},
 #endif

    {MIUNUM_0,      MMAP_ID_MAD_BASE_BUF,    ((MAD_BASE_BUFFER_MEMORY_TYPE & MIU1) ? (MAD_BASE_BUFFER_ADR | MIU_INTERVAL) : (MAD_BASE_BUFFER_ADR)),             MAD_BASE_BUFFER_LEN},

#if (MHEG5_ENABLE == 1)
    {MIUNUM_0,      MMAP_ID_BEON_BUF,       ((MHEG5_BUFFER_MEMORY_TYPE & MIU1) ? (MHEG5_BUFFER_ADR | MIU_INTERVAL) : (MHEG5_BUFFER_ADR)),               MHEG5_BUFFER_LEN},

    #ifdef MHEG5_BIG5_FONT_ENABLE
    {MIUNUM_0,      MMAP_ID_M5FONT_BUF,     ((MHEG5_FONTBUFFER_MEMORY_TYPE & MIU1) ? (MHEG5_FONTBUFFER_ADR | MIU_INTERVAL) : (MHEG5_FONTBUFFER_ADR)),           MHEG5_FONTBUFFER_LEN},
    {MIUNUM_0,      MMAP_ID_M5FONT_RM,      ((M5_FONTRM_BUFFER_MEMORY_TYPE & MIU1) ? (M5_FONTRM_BUFFER_ADR | MIU_INTERVAL) : (M5_FONTRM_BUFFER_ADR)),           M5_FONTRM_BUFFER_LEN},
    #endif
#endif

#if ENABLE_MPLAYER_PLUGIN
#ifdef ENABLE_LOAD_APP_FROM_USB
    {MIUNUM_0,      MMAP_ID_CAPE_BUF,       ((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)),                CAPE_BUFFER_LEN},
    {MIUNUM_0,      MMAP_ID_CAPE_JPEG_BUF,  ((CAPE_JPG_MEMORY_TYPE & MIU1) ? (CAPE_JPG_ADR | MIU_INTERVAL) : (CAPE_JPG_ADR)),                   CAPE_JPG_LEN},
#endif
#endif
};

static BOOLEAN bMMAP_Wait_Receive = FALSE;

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: _msAPI_MMap_SetMMapWaitReceive()
/// @brief \b Function \b Description: Send memory map address
/// @param  <IN>     \b BOOLEAN status : TRUE/FALSE
/// @param  <OUT>    \b None :
/// @param  <RET>    \b None :
////////////////////////////////////////////////////////////////////////////////
void _msAPI_MMap_SetMMapWaitReceive(BOOLEAN status)
{
    bMMAP_Wait_Receive = status;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: _msAPI_MMap_GetMMapWaitReceive()
/// @brief \b Function \b Description: Send memory map address
/// @param  <IN>     \b None :
/// @param  <OUT>    \b None :
/// @param  <RET>    \b BOOLEAN bMMAP_Wait_Receive : TRUE/FALSE
////////////////////////////////////////////////////////////////////////////////
BOOLEAN _msAPI_MMap_GetMMapWaitReceive(void)
{
    return bMMAP_Wait_Receive;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_MMap_SendMMapAddr()
/// @brief \b Function \b Description: Send memory map address
/// @param  <IN>     \b None :
/// @param  <OUT>    \b None :
/// @param  <RET>    \b None :
////////////////////////////////////////////////////////////////////////////////
/*
BOOLEAN _msAPI_MMap_SendMMapAddr_OBA(void)
{
    return TRUE;
}
*/

BOOLEAN _msAPI_MMap_SendMMapAddr(void)
{
    #if MHEG5_ENABLE
    U8 mapSize;

    MMAPDBG(U32 u32wait_ms = msAPI_Timer_GetTime0();)

    mapSize = sizeof(MemoryMap)/sizeof(MMAP_ID_FMT);

    MMAPDBG(printf("msAPI_MMap_SendMMapAddr mapSize = 0x%x\n",mapSize));
    {
        MS_U8 pU8Info[8];
        int i;

        //Send Size;
        pU8Info[0] = 0x08;
        pU8Info[1] = 0x94;
        pU8Info[2] = mapSize;
        MSApi_MBX_SetInformation(pU8Info,3);

        //Send Mem Map
        for(i=0;i<mapSize;i++)
        {
            MMAPDBG(printf("MIU_Number:%02lx MMAP_Block_ID:%02lx MMAP_Start_Address:%08lx MMAP_Length:%08lx\n", (U32)MemoryMap[i].MIU_Number, (U32)MemoryMap[i].MMAP_Block_ID, (U32)MemoryMap[i].MMAP_Start_Address, (U32)MemoryMap[i].MMAP_Length));
            pU8Info[0] = MemoryMap[i].MIU_Number;
            pU8Info[1] = MemoryMap[i].MMAP_Block_ID;
            MSApi_MBX_SetInformation(pU8Info,2);
            pU8Info[0] = (U8)((MemoryMap[i].MMAP_Start_Address)     &0xFF);
            pU8Info[1] = (U8)((MemoryMap[i].MMAP_Start_Address>>8)  &0xFF);
            pU8Info[2] = (U8)((MemoryMap[i].MMAP_Start_Address>>16) &0xFF);
            pU8Info[3] = (U8)((MemoryMap[i].MMAP_Start_Address>>24) &0xFF);

            pU8Info[4] = (U8)((MemoryMap[i].MMAP_Length)            &0xFF);
            pU8Info[5] = (U8)((MemoryMap[i].MMAP_Length>>8)         &0xFF);
            pU8Info[6] = (U8)((MemoryMap[i].MMAP_Length>>16)        &0xFF);
            pU8Info[7] = (U8)((MemoryMap[i].MMAP_Length>>24)        &0xFF);
            MSApi_MBX_SetInformation(pU8Info,8);
        }
    }
    MMAPDBG(printf("BEON finish init MMAP:%lu ms\n",msAPI_Timer_DiffTimeFromNow(u32wait_ms)));

    _msAPI_MMap_SetMMapWaitReceive(FALSE);

    #endif
    return TRUE;
}

BOOLEAN msAPI_MMap_SendMMapAddr_CAPE(void)
{
    U32 addr =(U32) (&(MemoryMap[0]));
    U8 mapSize = sizeof(MemoryMap)/sizeof(MMAP_ID_FMT);
    U8 u8Info[5];
    u8Info[0] = (U8)((addr)     &0xFF);
    u8Info[1] = (U8)((addr>>8)  &0xFF);
    u8Info[2] = (U8)((addr>>16) &0xFF);
    u8Info[3] = (U8)((addr>>24) &0xFF);
    u8Info[4] = mapSize;
    if( E_MBX_SUCCESS != MSApi_MBX_SetInformation(&u8Info[0], 5) )
    {
        return FALSE;
    }
    return TRUE;
}

BOOLEAN msAPI_MMap_SendMMapAddr(void)
{
            _msAPI_MMap_SendMMapAddr();
    return TRUE;
}

#endif // #if DYNAMIC_MMAP_FOR_BEON


#if(ENABLE_API_MMAP_GET_BUF)
#define DEBUG_MMAP(x)   //x

BOOL msAPI_MMAP_Get_BufInfo(EnuMMAPBufId eBufId, U32 * pu32BufAddr, U32 * pu32BufSize )
{
    if( eBufId >= E_BUFID_NUMS )
        return FALSE;

    U32 u32BufAddr = 0;
    U32 u32BufSize = 0;

#if 0
/* SUBTITLE   */
//co_buffer L4
#define SUBTITLE_AVAILABLE                                     0x0003720000
#define SUBTITLE_ADR                                           0x0003720000  //Alignment 0x10000
#define SUBTITLE_GAP_CHK                                       0x0000000000
#define SUBTITLE_LEN                                           0x00003A0000
#define SUBTITLE_MEMORY_TYPE                                   (MIU0 | SW | CO_BUF_L4 | WRITE_BACK)
#endif

    switch( eBufId )
    {
        default:
            printf("\nError: Undefined Buf Id = %u\n", eBufId);
            return FALSE;
            break;

        case E_BUFID_SUBTITLE:
        // Convert SUBTITLE_BUF to new name
        /*
        #ifndef SUBTITLE_MM_ADR
            #define SUBTITLE_MM_ADR     SUBTITLE_ADR
        #endif
        #ifndef SUBTITLE_DTV_ADR
            #define SUBTITLE_DTV_ADR    SUBTITLE_ADR
        #endif
        #ifndef SUBTITLE_MM_LEN
            #define SUBTITLE_MM_LEN     SUBTITLE_LEN
        #endif
        #ifndef SUBTITLE_DTV_LEN
            #define SUBTITLE_DTV_LEN    SUBTITLE_LEN
        #endif
        #ifndef SUBTITLE_MM_MEMORY_TYPE
            #define SUBTITLE_MM_MEMORY_TYPE     SUBTITLE_MEMORY_TYPE
        #endif
        #ifndef SUBTITLE_DTV_MEMORY_TYPE
            #define SUBTITLE_DTV_MEMORY_TYPE    SUBTITLE_MEMORY_TYPE
        #endif
        */

            if( IsStorageInUse() )
            {
            #if defined(SUBTITLE_MM_ADR)
                u32BufAddr = SUBTITLE_MM_ADR;
                u32BufSize = SUBTITLE_MM_LEN;

            #elif( defined(SUBTITLE_HD_MM_BMP_ADR)&&(SUBTITLE_HD_MM_BMP_LEN>0) )
                u32BufAddr = SUBTITLE_HD_MM_BMP_ADR;
                u32BufSize = SUBTITLE_HD_MM_BMP_LEN;

            #elif defined(SUBTITLE_MM_VIDEO_ADR) // For CK2 naming
                u32BufAddr = SUBTITLE_MM_VIDEO_ADR;
                u32BufSize = SUBTITLE_MM_VIDEO_LEN;
            #else
                u32BufAddr = SUBTITLE_ADR;
                u32BufSize = SUBTITLE_LEN;
            #endif
            }
            else
        #if( ENABLE_DTV&&ENABLE_DVB ) // ATSC no need!
            if( IsDTVInUse() )
            {
            #if defined(SUBTITLE_DTV_ADR)
                u32BufAddr = SUBTITLE_DTV_ADR;
                u32BufSize = SUBTITLE_DTV_LEN;
            #else
                u32BufAddr = SUBTITLE_ADR;
                u32BufSize = SUBTITLE_LEN;
            #endif
            }
            else
        #endif
            {   // Other source
                printf("\nError: Undefine Subtitle buf!\n");
            #if defined(SUBTITLE_ADR)
                u32BufAddr = SUBTITLE_ADR;
                u32BufSize = SUBTITLE_LEN;
            #else
                return FALSE;
            #endif
            }
            break;

        case E_BUFID_VDEC_BITSTREAM:
            if( IsStorageInUse() )
            {
            #if defined(VDEC_BITSTREAM_MM_ADR)
                u32BufAddr = VDEC_BITSTREAM_MM_ADR;
                u32BufSize = VDEC_BITSTREAM_MM_LEN;
            #else
                u32BufAddr = VDEC_BITSTREAM_ADR;
                u32BufSize = VDEC_BITSTREAM_LEN;
            #endif
            }
            else
        #if( ENABLE_DTV )
            if( IsDTVInUse() )
            {
            #if defined(VDEC_BITSTREAM_DTV_ADR)
                u32BufAddr = VDEC_BITSTREAM_DTV_ADR;
                u32BufSize = VDEC_BITSTREAM_DTV_LEN;
            #else
                u32BufAddr = VDEC_BITSTREAM_ADR;
                u32BufSize = VDEC_BITSTREAM_LEN;
            #endif
            }
            else
        #endif
            {   // Other source
                //printf("\nError: Undefine VDEC_BITSTREAM buf!\n");
            #if defined(VDEC_BITSTREAM_DTV_ADR)
                u32BufAddr = VDEC_BITSTREAM_DTV_ADR;
                u32BufSize = VDEC_BITSTREAM_DTV_LEN;
            #else
                u32BufAddr = VDEC_BITSTREAM_ADR;
                u32BufSize = VDEC_BITSTREAM_LEN;
            #endif
            }
            break;

        case E_BUFID_VDEC_FRAMEBUFFER:
            if( IsStorageInUse() )
            {
            #if defined(VDEC_FRAMEBUFFER_MM_ADR)
                u32BufAddr = VDEC_FRAMEBUFFER_MM_ADR;
                u32BufSize = VDEC_FRAMEBUFFER_MM_LEN;
            #else
                u32BufAddr = VDEC_FRAMEBUFFER_ADR;
                u32BufSize = VDEC_FRAMEBUFFER_LEN;
            #endif
            }
            else
        #if( ENABLE_DTV )
            if( IsDTVInUse() )
            {
            #if defined(VDEC_FRAMEBUFFER_DTV_ADR)
                u32BufAddr = VDEC_FRAMEBUFFER_DTV_ADR;
                u32BufSize = VDEC_FRAMEBUFFER_DTV_LEN;
            #else
                u32BufAddr = VDEC_FRAMEBUFFER_ADR;
                u32BufSize = VDEC_FRAMEBUFFER_LEN;
            #endif
            }
            else
        #endif
            {   // Other source
                //printf("\nError: Undefine VDEC_BITSTREAM buf!\n");
            #if defined(VDEC_FRAMEBUFFER_DTV_ADR)
                u32BufAddr = VDEC_FRAMEBUFFER_DTV_ADR;
                u32BufSize = VDEC_FRAMEBUFFER_DTV_LEN;
            #else
                u32BufAddr = VDEC_FRAMEBUFFER_ADR;
                u32BufSize = VDEC_FRAMEBUFFER_LEN;
            #endif
            }
            break;

    }

    DEBUG_MMAP( PRINT_CURRENT_LINE(); );
    DEBUG_MMAP( printf("Buf_%u: 0x%X, 0x%X\n", eBufId, u32BufAddr, u32BufSize ); );

    *pu32BufAddr = u32BufAddr;
    *pu32BufSize = u32BufSize;

    return TRUE;
}
#endif // ENABLE_API_MMAP_GET_BUF


