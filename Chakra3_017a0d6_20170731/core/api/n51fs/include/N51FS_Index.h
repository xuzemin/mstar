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
#ifndef N51FS_INDEX_H
#define N51FS_INDEX_H

#include "datatype.h"

#define POSITION_STACK_SIZE 16

typedef struct
{
    U32 VCN;
    U16 Bytes;
}IndexEntryPosition;

typedef struct
{
    U32 SubNodeVCN;
    U32 SubNodeVCN_H;
    U32 MFTReference;
    U32 MFTReference_H;
    U16 EntrySize;
    U16 StreamSize;
    U16 EntryFlag;
    U16 Padding;
}IndexEntryHead;



typedef struct
{
    U8  PositionStackCount;
    IndexEntryPosition PositionStack[POSITION_STACK_SIZE];
    BOOLEAN JustLeaveSubNode;
    BOOLEAN LastReached;

    //Stream vars
    U16 OffsetToRunList;
    U32 CurrentRecordStartVCN;
    U32 CurrentRecordBytePosition;

    IndexEntryHead  CurrentIndexEntryHead;//make sure that this is the last member of this struct
    //It is assumed that the corresponding stream is followed (see pg.98 from 0x10)

}IndexVars;

typedef struct
{
    U8 MagicNum[4];
    U16 OffsetToUpdateSequence;
    U16 SizeOfUpdateSequence;
    U8 LogFileSequence[8];
    U32 VCN;
    U32 VCN_H;
    U32 OffsetToIndexEntries;
    U32 SizeOfIndexEntries;
    U32 AllocatedSizeOfIndexEntries;
    U8 LeafNode;
    U8 Padding[3];
    U16 UpdateSequence;
}IndexRecord;

typedef struct
{
    U16 EntrySize;
    U16 EntryFlag;
    BOOLEAN bIsFirstEntry;
    BOOLEAN bIsLastEntry;
}IndexEntry;

typedef struct
{
    U32 u32OffsetToEntry;
    U32 u32CurrentBuffAddr;
    U32 u32CurrentRecordBytePosition;
    U32 u32CurrentRecordStartVCN;
    U32 u32OffsetToIndexRootAttr;
    U32 u32OffsetToIndexRootHeader;
    U32 u32RunListAddr;
    U16 u16OffsetToRunList;
    U8  u8PositionStackCount;
    IndexEntryPosition PositionStack[POSITION_STACK_SIZE];
    U8 u8SubNodVCN[8];
    BOOLEAN bRecordDirty;
    BOOLEAN bRootDirty;

    IndexEntry indexEntry;
}IndexHeader;


typedef enum
{
    N51FS_INDEX_NEXT_RESULT_ERROR,
    N51FS_INDEX_NEXT_RESULT_SUCCESS,
    N51FS_INDEX_NEXT_RESULT_LAST,

}EN_N51FS_INDEX_NEXT_RESULT;


#ifdef N51FS_INDEX_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//=======================

INTERFACE IndexRecord* N51FS_GetIndexRecordInfo(U8 enid);

INTERFACE U32* N51FS_GetIndexRootInfo(U8 enid);
INTERFACE U32 N51FS_GetIndexRootMIUAddress(U8 enid);

INTERFACE IndexVars* N51FS_GetIndexVarsInfo(U8 enid);
INTERFACE U32 N51FS_GetIndexRecordMIUAddress(U8 enid);
INTERFACE U32 N51FS_GetIndexVarsMIUAddress(U8 enid);


//=======================
INTERFACE BOOLEAN N51FS_Index_ToFirst(U8 enid);
INTERFACE EN_N51FS_INDEX_NEXT_RESULT N51FS_Index_Next(U8 enid, FileEntry* pFileToSet);
INTERFACE U32  N51FS_Index_MapVCN2LCN(U32 u32Addr, U16 u16Offset, U32 VCN);

//N51FS Delete========================
INTERFACE BOOLEAN N51FS_Delete_Index_Search(FileEntry *pFileToFind);
INTERFACE BOOLEAN N51FS_Delete_RemoveLeaf(U8 fsid);
INTERFACE BOOLEAN N51FS_Delete_RemoveNode(U8 fsid);
INTERFACE BOOLEAN N51FS_Delete_MarkMFTRecordUnused(U8 fsid, U32 MFR);

#undef INTERFACE
#endif

