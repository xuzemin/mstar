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
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_DECOMPRESS_C

#include "Board.h"

//#include "MsCommon.h"
//#include "BinInfo.h"
//#include "InfoBlock.h"
//#include "drvGlobal.h"
#include "msAPI_Decompress.h"
//#include "msAPI_MIU.h"
//#include "msAPI_Timer.h"

#if 0//def LZSS_ON_TSP
No use
void _sendTSPMBX(U32 u32SrcAddr, U32 u32SrcLen, U32 u32DstAddr)
{
    //printf("sendTSPMBX 0x%x --(0x%x)--> 0x%x\n", u32SrcAddr, u32SrcLen, u32DstAddr);

    MDrv_WriteByte(MB_TSP_REG_PARAM_0, (u32SrcAddr & 0xff000000) >> 24);
    MDrv_WriteByte(MB_TSP_REG_PARAM_1, (u32SrcAddr & 0x00ff0000) >> 16);
    MDrv_WriteByte(MB_TSP_REG_PARAM_2, (u32SrcAddr & 0x0000ff00) >> 8);
    MDrv_WriteByte(MB_TSP_REG_PARAM_3, (u32SrcAddr & 0x000000ff));
    MDrv_WriteByte(MB_TSP_REG_PARAM_4, (u32SrcLen & 0xff000000) >> 24);
    MDrv_WriteByte(MB_TSP_REG_PARAM_5, (u32SrcLen & 0x00ff0000) >> 16);
    MDrv_WriteByte(MB_TSP_REG_PARAM_6, (u32SrcLen & 0x0000ff00) >> 8);
    MDrv_WriteByte(MB_TSP_REG_PARAM_7, (u32SrcLen & 0x000000ff));
    MDrv_WriteByte(MB_TSP_REG_PARAM_8, (u32DstAddr & 0xff000000) >> 24);
    MDrv_WriteByte(MB_TSP_REG_PARAM_9, (u32DstAddr & 0x00ff0000) >> 16);
    MDrv_WriteByte(MB_TSP_REG_PARAM_A, (u32DstAddr & 0x0000ff00) >> 8);
    MDrv_WriteByte(MB_TSP_REG_PARAM_B, (u32DstAddr & 0x000000ff));

    //fire bit enable
    MDrv_WriteByte(MB_TSP_REG_Status, MDrv_ReadByte(MB_TSP_REG_Status) | BIT1);
}

void _TSPAeonInit(void)
{
    U16 u16CodeSize, u16Counter;
    BOOLEAN bResult;
    BININFO BinInfo;
    //printf("TSPInit\n");

    /*[01-1]reset demux all =======================================================*/
    MDrv_WriteByte(0x1015F4, 0x00);//reset demux all
    MDrv_WriteByte(0x1015F4, 0x02);//reset demux all

    /*[01-2]initial tsp clock =====================================================*/

    /*[01-3]set parallel/serial, internal/external sync , clock invert ============*/
    //temporarily =================================================================//
    MDrv_WriteByte(0x1015FC, (MDrv_ReadByte(0x1015FC) | 0x04));// force interrupt0 enable
    MDrv_WriteByte(0x1015FC, (MDrv_ReadByte(0x1015FC) | 0x20)); // force interrupt1 enable

    //temporarily =================================================================//

    //sdram access ================================================================//
    MDrv_WriteByte(0x1015D0, 0x00);       // qmem_dmask[07:00]  =>0xffffc000
    MDrv_WriteByte(0x1015D1, 0xc0);       // qmem_dmask[15:08]
    MDrv_WriteByte(0x1015D2, 0xff);       // qmem_dmask[23:16]
    MDrv_WriteByte(0x1015D3, 0xff);       // qmem_dmask[31:24]
    MDrv_WriteByte(0x1015C0, 0x00);       // sdr_base[07:00]    =>0x00000000
    MDrv_WriteByte(0x1015C1, 0x00);       // sdr_base[15:08]
    MDrv_WriteByte(0x1015C2, 0x00);       // sdr_base[23:16]
    MDrv_WriteByte(0x1015C3, 0x00);

    BinInfo.B_ID = BIN_ID_CODE_AEON_LZSS_BE;
    bResult = Get_BinInfo(&BinInfo);

    if (bResult != PASS)
    {
        (printf("could not find lzss binary on flash.\n"));
        return;
    }

    //MApi_BDMA_CopyFromResource(BinInfo.B_FAddr, _PA2VA(u32SecbufAddr), BinInfo.B_Len);
    msAPI_MIU_Copy(BinInfo.B_FAddr, u32SecbufAddr, ((BinInfo.B_Len+0x7) & ~0x7), MIU_FLASH2SDRAM);

    //MDrv_BDMA_MemCopy(((MS_BIN_MEMORY_TYPE & MIU1) ? (MS_BIN_ADR | MIU_INTERVAL) : (MS_BIN_ADR)),u32SecbufAddr,BinInfo.B_Len);

    /*[03-1]set code start address ====================================================*/
    MDrv_WriteByte(0x1015f0, ((u32SecbufAddr / 64) >> 0));// 64-byte
    MDrv_WriteByte(0x1015f1, ((u32SecbufAddr / 64) >> 8));
    MDrv_WriteByte(0x10160e, ((u32SecbufAddr / 64) >> 16));

    /*[03-2]set code length ===========================================================*/
    u16CodeSize = ((0x3000 + 7) & ~7) >> 2; // 8-byte aligned in 4-byte unit

    //printf("SecBuff : 0x%x, CodeSize : %x, %x\n", u32SecbufAddr, u16CodeSize, BinInfo.B_Len);

    MDrv_WriteByte(0x1015f2, ((u16CodeSize >> 0)));
    MDrv_WriteByte(0x1015f3, ((u16CodeSize >> 8)));

    /*[04]load code ===================================================================*/
    /*[04-1]start =====================================================================*/
    MDrv_WriteByte(0x1015f4, 0x06);

    /*[04-2]boot up ===================================================================*/
    MDrv_WriteByte(0x1015f4, 0x02);

    /*[04-3]wait until success ========================================================*/
    for (u16Counter = 0; u16Counter < 0x666; u16Counter++)
    {
        if (MDrv_ReadByte(0x1015f4) & BIT3)
        {
            break;
        }
    }

    //0x1502 TSP_BUSY_BIT
    MDrv_WriteByte(MB_TSP_REG_Status, MDrv_ReadByte(MB_TSP_REG_Status) | BIT0);

    /*[04-4]patch hw reset fail =======================================================*/
    //MDrv_WriteByte(0x1015f4, 0x00); // reset demux hw
    MDrv_WriteByte(0x1015f4, 0x03); // reset demux hw

    MDrv_WriteByte(0x1015F4, 0x03);       // tsp_enable
    MDrv_WriteByte(0x10158A, 0x48);       // Pluto; cannot enable "remove byte enable" due to another hw bug
}

bool msAPI_WaitForTSPDecompressDone(U32 timeout)
{
    U32 u32StartTime;

    //printf("Wait :::::: %ld\n", timeout);

    u32StartTime=msAPI_Timer_GetTime0();
    while((MDrv_ReadByte(MB_TSP_REG_Status) & BIT0))
    {
        if((msAPI_Timer_GetTime0() - u32StartTime) > timeout)
        {
            printf("LZSS DECOMPRESS FAILEd !! \n");
            return FALSE;
        }
    }
    //printf("Time cost : %ld\n", (msAPI_Timer_GetTime0() - u32StartTime));

    return TRUE;
}

void msAPI_LzssOnTSPAeon(U16 Bin_ID)
{
    BOOLEAN bResult;
    BININFO BinInfo;
    //printf("LzssOnTSPAeon\n");

    //copy decompressed data from flash to ram
    BinInfo.B_ID = Bin_ID;
    bResult = Get_BinInfo(&BinInfo);
    if (bResult != PASS)
    {
        (printf("could not find 0x%x binary on flash.\n", Bin_ID));
        return;
    }

    //copy compressed data to read buffer
    msAPI_MIU_Copy(BinInfo.B_FAddr, DECOMPRESS_READ_BUFFER_ADR, ((BinInfo.B_Len+0x7) & ~0x7), MIU_FLASH2SDRAM);

    //Init TSP
    _TSPAeonInit();

    //waiting for TSP init
    while(MDrv_ReadByte(MB_TSP_REG_Status) & BIT0);

    //send related info to TSP
    _sendTSPMBX(DECOMPRESS_READ_BUFFER_ADR, (BinInfo.B_Len + 0x07) & ~0x07, ((DECOMPRESS_DATA_BUFFER_MEMORY_TYPE&MIU1)?DECOMPRESS_DATA_BUFFER_ADR|MIU_INTERVAL:DECOMPRESS_DATA_BUFFER_ADR));

    msAPI_WaitForTSPDecompressDone(2000);
}
#endif
#undef MSAPI_DECOMPRESS_C
