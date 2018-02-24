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
#ifndef N51FS_FILE_H
#define N51FS_FILE_H

#include "datatype.h"
#include "msAPI_FSCommon.h"

#ifdef N51FS_FILE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define memoffset_FileDataAttribute 0x400//0x1000
#define memoffset_FileBuffer 0x2000

#define FILE_INPUT_BUFFER_SIZE    0x1000
#define FILE_INPUT_BUFFER_SECTOR_COUNT 8
#define FILE_INPUT_BUFFER_SIZE_POWERof2 12
#define FILE_INPUT_BUFFER_REMAIN_MASK 0xFFF;

#define SECTOR_SIZE_POWERof2 9
#define SECTOR_REMAIN_MASK 0x1FF


typedef struct
{
    FileHandleStruct  pub_fileheader;
    U8 u8FileHandleID;
    U8 u8FileSystemID;

    U32 MFTReference;
    LongLong FileSize_LL;
    U8  FileAttribute[8];
    //U8  FileName[512];

    /*changing*/
    LongLong CurrentBytePosition_LL;
    
    U32 CurrentStartLCN;
    U32 CurrentVCN;
    U8  CurrentSectorNo;
    U32 CurrentRunLength;
    U32 NextStartVCN;

    /*used for residented data*/
    U32 StartDataOffset;

    BOOLEAN DataResidented;
    U8 u8OpenMode;

    U32 TotalVCN;
    U8  u8CompressFlag;
}N51FS_FileHandle; /*existed data runs should be right after this struct*/

INTERFACE N51FS_FileHandle* N51FS_File_GetHandleInfo(U8 fileHandleID);
INTERFACE U32* N51FS_File_GetDataAttributeInfo(U8 fileHandleID);

INTERFACE BOOLEAN N51FS_File_OpenFileRecord(U8 fhid,U32 MFR);
INTERFACE BOOLEAN N51FS_File_StreamReadToMIU(U8 fhid, U32 destMIUAddr,U32 len,U32* readBytes);
INTERFACE BOOLEAN N51FS_File_SeekForward(U8 fhid,U32 len,U32* readBytes);
INTERFACE U32 N51FS_File_MapVCN2LCN(U8 fhid, U32 VCN, U32* lowerboundaryVCN, 
                                                                                                  U32* boundaryVCN, U32 attrType,  BOOLEAN *pFound);
INTERFACE U32 N51FS_FileRead_NonResidented(U8 fhid, U32 destMIUAddr,U32 len);
INTERFACE U32 N51FS_FileRead_Residented(U8 fhid, U32 destMIUAddr,U32 len);

//~!~
INTERFACE U32 N51FS_FileRead_NonResidented_Compress(U8 fhid, U32 destMIUAddr,U32 len);

#undef INTERFACE
#endif
