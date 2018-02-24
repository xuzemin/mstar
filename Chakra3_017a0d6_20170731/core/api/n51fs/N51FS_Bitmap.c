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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// @file
// @brief
// @author MStarSemi Inc.
//
//-
//-
//
////////////////////////////////////////////////////////////////////////////////
#define N51FS_BITMAP_C

#include "msAPI_FS_SysInfo.h"
#include "msAPI_FCtrl.h"
#include "msAPI_N51FS.h"
#include "N51FS_Index.h"
#include "N51FS_File.h"
#include "N51FS_Bitmap.h"
#include "msAPI_MSDCtrl.h"

#define BITMAP_DBG(flag,x)  //{if(flag){x;}}

BOOLEAN N51FS_Bitmap_ClusterFreeByMFR(U8 u8fsid, U32 u32MFR)
{
    N51FS_FileSysStruct* pfst;
    U32 i, j;
    U16 u16Temp = 0;
    U16 u16AttrOffset;
    U8 * pBuff;
    U8 * pBuff2;
    U16 u16OffsetToDataRun;
    U8 u8LengthField;
    U8 u8OffsetField;
    U32 u32ClusterLength;
    S32 s32OffsetToPrevious = 0;
    U32 u32ResultLCN = 0; //WBT Declared variable "u32ResultLCN" without initializer
    U32 u32BitmapLCN;
    U16 u16OffsetToBitmapDataRun = 0;
    U32 u32BitmapStartSector = 0; //WBT Declared variable "u32BitmapStartSector" without initializer
    U32 u32PreBitmapStartSector = 0;
    U8 u8SectorPerClus;
    S8 s8DeviceIndex;
    U16 u16BytePerSector;
    U32 u32PhysicalStartSector;
    U32 u32OffsetToData = 0;
    BOOLEAN bBitmapResidented = FALSE;
    U16 u16ByteNum;

    pfst=(N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8SectorPerClus = pfst->SectorsPerCluster;
    u16BytePerSector = pfst->BytesPerSector;
    u32PhysicalStartSector = pfst->RelativeSector;
    s8DeviceIndex = pfst->DeviceIndex;

    // [1]. read file record
    if(0 == N51FS_ReadMFTRecord(u8fsid, u32MFR, N51FS_TEMP_4K_BACKUP_BUFFER_0))
    {
        __ASSERT(0);
        return FALSE;
    }
    msAPI_FS_MIU_Copy( N51FS_TEMP_4K_BACKUP_BUFFER_0 + 0x14, GET_DRAM_ADDR(&u16Temp), 2 );
    u16AttrOffset = (u16Temp);

    u16Temp = 0;
    if((N51FS_Attribute_Find(u8fsid,N51FS_TEMP_4K_BACKUP_BUFFER_0 + u16AttrOffset, USB_IO_TEMP_ADDR, ATTR_TYPE_DATA, &u16Temp, 0)).Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }
    u16AttrOffset += u16Temp;
    pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_0);

    if((*(pBuff + u16AttrOffset + 8)) == 0) //this file is residented
    {
        return TRUE;
    }
    //u16OffsetToDataRun = u16AttrOffset + (*(U16 *)(pBuff + u16AttrOffset + 0x20));
    memcpy(&u16OffsetToDataRun,(pBuff + u16AttrOffset + 0x20),2);
    u16OffsetToDataRun += u16AttrOffset;

    pBuff += u16OffsetToDataRun;


    // [2]. open bitmap file
    if(0 == N51FS_ReadMFTRecord(u8fsid, N51FS_BITMAP_MFR, N51FS_TEMP_4K_BACKUP_BUFFER_1))
    {
        __ASSERT(0);
        return FALSE;
    }
    msAPI_FS_MIU_Copy( N51FS_TEMP_4K_BACKUP_BUFFER_1 + 0x14, GET_DRAM_ADDR(&u16Temp), 2 );
    u16AttrOffset = (u16Temp);

    u16Temp = 0;
    if((N51FS_Attribute_Find(u8fsid,N51FS_TEMP_4K_BACKUP_BUFFER_1 + u16AttrOffset, USB_IO_TEMP_ADDR, ATTR_TYPE_DATA, &u16Temp, 0)).Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }
    u16AttrOffset += u16Temp;
    pBuff2 = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_1);

    if((*(pBuff2 + u16AttrOffset + 8)) == 0) //this file is residented
    {
        bBitmapResidented = TRUE;
        //u32OffsetToData = u16AttrOffset + (*(U16 *)(pBuff2 + u16AttrOffset + 0x14));
        memcpy(&u32OffsetToData,(pBuff2 + u16AttrOffset + 0x14),2);
        u32OffsetToData += u16AttrOffset;
    }
    else
    {
        //u16OffsetToBitmapDataRun = u16AttrOffset + (*(U16 *)(pBuff2 + u16AttrOffset + 0x20));
        memcpy(&u16OffsetToBitmapDataRun,(pBuff2 + u16AttrOffset + 0x20),2);
        u16OffsetToBitmapDataRun += u16AttrOffset;
    }

    //[3]. reset bitmap
    while(TRUE)
    {
        u32ClusterLength = 0;
        if(pBuff[0]==0)
        {
            if(bBitmapResidented)
            {
                N51FS_WriteMFTRecord(u8fsid, N51FS_BITMAP_MFR, N51FS_TEMP_4K_BACKUP_BUFFER_1);
            }
            else
            {
                if(u32BitmapStartSector != 0)
                {
                    BOOLEAN _btmp = TRUE;
                    _btmp = msAPI_MSDCtrl_SectorWrite((U8)s8DeviceIndex, u32BitmapStartSector, 1, N51FS_TEMP_4K_BACKUP_BUFFER_2);
                }
            }
            return TRUE;
        }
        u8LengthField=pBuff[0]&0x0F;
        u8OffsetField=(pBuff[0]&0xF0)>>4;


        if(u8LengthField>4||u8OffsetField>4)
        {
            __ASSERT(0);// can not support
            return 0;
        }

        for(i=0;i<u8LengthField;i++)
            u32ClusterLength = (u32ClusterLength<<8)|pBuff[1+u8LengthField-1-i];

        if(u8OffsetField>0)
        {
            if(pBuff[u8LengthField+u8OffsetField]&0x80)
                s32OffsetToPrevious = -1;
            for(i=0;i<u8OffsetField;i++)
                s32OffsetToPrevious=(s32OffsetToPrevious<<8)|pBuff[1+u8LengthField+u8OffsetField-1-i];
            u32ResultLCN+=s32OffsetToPrevious;

            if(bBitmapResidented)
            {
                pBuff2 = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_1);

                for(j = 0;j < u32ClusterLength;j++)
                {
                    u16ByteNum = (U16)((u32ResultLCN + j)/8);
                    *(pBuff2 + u32OffsetToData + u16ByteNum) = (*(pBuff2 + u32OffsetToData + u16ByteNum) & (~(1 << (U8)((u32ResultLCN + j)%8))));
                }
            }
            else
            {
                pBuff2 = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_2);

                for(j = 0;j < u32ClusterLength;j++)
                {

                    u32BitmapStartSector = (u32ResultLCN + j)/8;
                    u16ByteNum = (U16)(u32BitmapStartSector%u16BytePerSector);
                    u32BitmapStartSector = u32BitmapStartSector/ u16BytePerSector;
                    u32BitmapLCN = N51FS_Index_MapVCN2LCN(N51FS_TEMP_4K_BACKUP_BUFFER_1, u16OffsetToBitmapDataRun, u32BitmapStartSector / u8SectorPerClus);
                    u32BitmapStartSector = u32BitmapLCN * u8SectorPerClus + u32BitmapStartSector % u8SectorPerClus;
                    u32BitmapStartSector += u32PhysicalStartSector;
                    if(u32BitmapStartSector != u32PreBitmapStartSector)
                    {
                        if(u32PreBitmapStartSector != 0)
                        {
                            if (!msAPI_MSDCtrl_SectorWrite((U8)s8DeviceIndex, u32PreBitmapStartSector, 1, N51FS_TEMP_4K_BACKUP_BUFFER_2)) // WBT Return value of "msAPI_MSDCtrl_SectorWrite" is not checked
                            {
                                __ASSERT(0);
                                return FALSE;
                            }
                        }
                        if(!msAPI_MSDCtrl_SectorRead((U8)s8DeviceIndex, u32BitmapStartSector, 1, N51FS_TEMP_4K_BACKUP_BUFFER_2)) //WBT Return value of "msAPI_MSDCtrl_SectorRead" is not checked
                        {
                            __ASSERT(0);

                            return FALSE;
                        }
                    }
                    *(pBuff2 + u16ByteNum) = (*(pBuff2 + u16ByteNum) & (~(1 << (U8)((u32ResultLCN + j)%8))));
                    u32PreBitmapStartSector = u32BitmapStartSector;

                }
            }

        }
        pBuff=pBuff+1+u8OffsetField+u8LengthField;
    }

    return TRUE;
}


BOOLEAN N51FS_Bitmap_MFRFree(U8 u8fsid, U32 u32MFR)
{
    U8 * pBuff;
    S8 s8DeviceIndex;
    U8 u8SectorPerClus;
    U16 u16Temp = 0;
    U16 u16AttrOffset;
    U16 u16OffsetToDataRun;
    U16 u16BytePerSector;
    U32 u32BitmapLCN;
    U32 u32BitmapStartSector;
    U32 u32PhysicalStartSector;
    U32 u32Pivot, u32Offset;
    N51FS_AttributeInfo info;
    N51FS_FileSysStruct* pfst;

    pfst=(N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);

    u8SectorPerClus = pfst->SectorsPerCluster;
    u16BytePerSector = pfst->BytesPerSector;
    u32PhysicalStartSector = pfst->RelativeSector;
    s8DeviceIndex = pfst->DeviceIndex;

    // [1]. read MFT(0) file record and get bitmap data run
    if(0 == N51FS_ReadMFTRecord(u8fsid, 0, N51FS_TEMP_4K_BACKUP_BUFFER_0))
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FS_MIU_Copy( N51FS_TEMP_4K_BACKUP_BUFFER_0 + 0x14, GET_DRAM_ADDR(&u16Temp), 2 );
    u16AttrOffset = (u16Temp);

    u16Temp = 0;
    info = N51FS_Attribute_Find(u8fsid,N51FS_TEMP_4K_BACKUP_BUFFER_0 + u16AttrOffset, USB_IO_TEMP_ADDR, ATTR_TYPE_BITMAP, &u16Temp, 0);
    if(info.Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }
    u16AttrOffset += u16Temp;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_0);

    if((*(pBuff + u16AttrOffset + 8)) == 0)
    {
        //this file is residented
        __ASSERT(0);
        return TRUE;
    }
    //u16OffsetToDataRun = u16AttrOffset + (*(U16 *)(pBuff + u16AttrOffset + 0x20));
    memcpy(&u16OffsetToDataRun,(pBuff + u16AttrOffset + 0x20),2);
    u16OffsetToDataRun += u16AttrOffset;

    u32BitmapLCN = N51FS_Index_MapVCN2LCN(N51FS_TEMP_4K_BACKUP_BUFFER_0, u16OffsetToDataRun, (u32MFR/0x1000) / u8SectorPerClus);
    //printf("\n### u32BitmapLCN: %LX", u32BitmapLCN);


    // [2]. reset bitmap data
    u32MFR %= 0x1000;
    u32BitmapStartSector = (u32BitmapLCN * u8SectorPerClus);
    if(!msAPI_MSDCtrl_SectorRead((U8)s8DeviceIndex, u32BitmapStartSector, 1, N51FS_TEMP_4K_BACKUP_BUFFER_0))
    {
        __ASSERT(0);
        return FALSE;
    }
    u32Pivot = u32MFR/8;
    u32Offset = (1 << (u32MFR%8));
    pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_0);

    *(pBuff + u32Pivot) &= ~u32Offset;

    if(!msAPI_MSDCtrl_SectorWrite((U8)s8DeviceIndex, u32BitmapStartSector, 1, N51FS_TEMP_4K_BACKUP_BUFFER_0))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}


#undef N51FS_BITMAP_C

