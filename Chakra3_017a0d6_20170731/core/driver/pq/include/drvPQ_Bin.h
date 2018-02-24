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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _DRV_PQ_BIN_H_
#define _DRV_PQ_BIN_H_


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define PQ_BIN_MAX_IP       256
#define PQ_BIN_MAX_PNL      30

#define PQ_BIN_IP_ALL       0xFFFF
#define PQ_BIN_IP_NULL      0xFFFF
#define PQ_BIN_IP_COMM      0xFFFE
#define PQ_BIN_ADDR_NULL    0xFFFFFFFF

#define PQ_BIN_BANK_SIZE    1
#define PQ_BIN_ADDR_SIZE    1
#define PQ_BIN_MASK_SIZE    1

#define PQ_BIN_HEADER_LEN   16
#define PQ_BIN_VERSION_LEN  16
#define PQ_BIN_DUMMY        8

#define PQ_TEXT_BIN_HEADER_LEN   16
#define PQ_TEXT_BIN_VERSION_LEN  16
#define PQ_TEXT_BIN_DUMMY        8


//Size of each table
#define PQ_BIN_GRULE_INFO_SIZE              14
#define PQ_BIN_GRULE_LEVEL_INFO_SIZE        6
#define PQ_BIN_XRULE_INFO_SIZE              12
#define PQ_BIN_SKIPRULE_INFO_SIZE           6
#define PQ_BIN_IP_COMM_INFO_SIZE            16
#define PQ_BIN_SOURCELUT_INFO_SIZE          8


// Item Offset of each table
// GRule
#define PQ_BIN_GRULE_HEADER_LEN             (16)
#define PQ_BIN_GRULE_RULE_NUM_LEN           (2)
#define PQ_BIN_GRULE_PANEL_NUM_LEN          (2)

#define PQ_BIN_GRULE_IP_NUM_OFFSET          (0)
#define PQ_BIN_GRULE_SOURCE_NUM_OFFSET      (PQ_BIN_GRULE_IP_NUM_OFFSET+2)
#define PQ_BIN_GRULE_GROUP_NUM_OFFSET       (PQ_BIN_GRULE_SOURCE_NUM_OFFSET+2)
#define PQ_BIN_GRULE_IPOFFSET_OFFSET        (PQ_BIN_GRULE_GROUP_NUM_OFFSET+2)
#define PQ_BIN_GRULE_RULEOFFSET_OFFSET      (PQ_BIN_GRULE_IPOFFSET_OFFSET+4)

#define PQ_BIN_GRULE_LEVEL_LVL_NUM_OFFSET   (0)
#define PQ_BIN_GRULE_LEVEL_OFFSET_OFFSET    (PQ_BIN_GRULE_LEVEL_LVL_NUM_OFFSET+2)


// XRule
#define PQ_BIN_XRULE_HEADER_LEN             (16)
#define PQ_BIN_XRULE_RULE_NUM_LEN           (2)

#define PQ_BIN_XRULE_IP_NUM_OFFSET          (0)
#define PQ_BIN_XRULE_GROUP_NUM_OFFSET       (PQ_BIN_XRULE_IP_NUM_OFFSET+2)
#define PQ_BIN_XRULE_IPOFFSET_OFFSET        (PQ_BIN_XRULE_GROUP_NUM_OFFSET+2)
#define PQ_BIN_XRULE_GROUPOFFSET_OFFSET     (PQ_BIN_XRULE_IPOFFSET_OFFSET+4)


// SkipRule
#define PQ_BIN_SKIPRULE_HEADER_LEN          (16)
#define PQ_BIN_SKIPRULE_IP_NUM_OFFSET       (0)
#define PQ_BIN_SKIPRULE_OFFSET_OFFSET       (PQ_BIN_SKIPRULE_IP_NUM_OFFSET+2)


// IP & Common
#define PQ_BIN_IP_COMM_HEADER_LEN           (16)
#define PQ_BIN_IP_COMM_IP_NUM_LEN           (2)
#define PQ_BIN_IP_COMM_TABLE_TYPE_OFFSET    (0)
#define PQ_BIN_IP_COMM_COMM_REG_NUM_OFFSET  (PQ_BIN_IP_COMM_TABLE_TYPE_OFFSET+2)
#define PQ_BIN_IP_COMM_IP_REG_NUM_OFFSET    (PQ_BIN_IP_COMM_COMM_REG_NUM_OFFSET+2)
#define PQ_BIN_IP_COMM_IP_GROUP_NUM_OFFSET  (PQ_BIN_IP_COMM_IP_REG_NUM_OFFSET+2)
#define PQ_BIN_IP_COMM_COMMOFFSET_OFFSET    (PQ_BIN_IP_COMM_IP_GROUP_NUM_OFFSET+2)
#define PQ_BIN_IP_COMM_IPOFFSET_OFFSET      (PQ_BIN_IP_COMM_COMMOFFSET_OFFSET+4)


// SourceLUT
#define PQ_BIN_SOURCELUT_HEADER_LEN         (16)
#define PQ_BIN_SOURCELUT_PANEL_NUM_LEN      (2)

#define PQ_BIN_SOURCELUT_SOURCE_NUM_OFFSET  (0)
#define PQ_BIN_SOURCELUT_IP_NUM_OFFSET      (PQ_BIN_SOURCELUT_SOURCE_NUM_OFFSET+2)
#define PQ_BIN_SOURCELUT_OFFSET_OFFSET      (PQ_BIN_SOURCELUT_IP_NUM_OFFSET+2)



#define PQ_BIN_SOURCELUT_DATA_LEN           2 // 2 bytes
#define PQ_BIN_IP_COMM_DATA_LEN             1 // 1 byte


// Text Bin
//Size of each table
#define PQ_TEXT_BIN_SRCTYPE_INFO_SIZE       6
#define PQ_TEXT_BIN_IPNAME_INFO_SIZE        6
#define PQ_TEXT_BIN_GROUPNAME_INFO_SIZE     6

// SrcType
#define PQ_TEXT_BIN_SRCTYPE_HEADER_LEN      (16)
#define PQ_TEXT_BIN_SRCTYPE_SRCNUM_LEN      (2)
#define PQ_TEXT_BIN_SRCTYPE_SRC_NUM_OFFSET  (0)
#define PQ_TEXT_BIN_SRCTYPE_OFFSET_OFFSET   (PQ_TEXT_BIN_SRCTYPE_SRC_NUM_OFFSET+2)


// IPName
#define PQ_TEXT_BIN_IPNAME_HEADER_LEN       (16)
#define PQ_TEXT_BIN_IPNAME_IPNUM_LEN        (2)
#define PQ_TEXT_BIN_IPNAME_IPNUM_OFFSET     (0)
#define PQ_TEXT_BIN_IPNAME_OFFSET_OFFSET    (PQ_TEXT_BIN_IPNAME_IPNUM_OFFSET+2)

// GroupName
#define PQ_TEXT_BIN_GROUPNAME_HEADER_LEN                (16)
#define PQ_TEXT_BIN_GROUPNAME_IPNUM_LEN                 (2)
#define PQ_TEXT_BIN_GROUPNAME_IPGROUP_GROUPNUM_OFFSET   (0)
#define PQ_TEXT_BIN_GROUPNAME_IPGROUP_OFFSET_OFFSET     (PQ_TEXT_BIN_GROUPNAME_IPGROUP_GROUPNUM_OFFSET+2)

#define PQ_TEXT_BIN_GROUPNAME_GROUPOFFSET_LEN           (4)
#define PQ_TEXT_BIN_GROUPNAME_GROUPLENGTH_LEN           (2)
#define PQ_TEXT_BIN_GROUPNAME_GROUPOFFSET_OFFSET        (0)

//-------------------------------------------------------------------------------------------------
//  enum
//-------------------------------------------------------------------------------------------------

typedef enum
{
    PQ_BIN_DISPLAY_ONE = 0,
    PQ_BIN_DISPLAY_PIP,
    PQ_BIN_DISPLAY_POP,
    PQ_BIN_DISPLAY_NUM,
}PQ_BIN_DISPLAY_TYPE;


//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef struct
{
    MS_U16 u16IPNum;
    MS_U16 u16SourceNum;
    MS_U16 u16GroupNum;
    MS_U32 u32IPOffset;
    MS_U32 u32RuleOffset;
}MS_PQBin_GRule_Info;

typedef struct
{
    MS_U16 u16LvlNum;
    MS_U32 u32Offset;
}MS_PQBin_GRule_Level_Info;

typedef struct
{
    MS_U16 u16IPNum;
    MS_U16 u16GroupNum;
    MS_U32 u32IPOffset;
    MS_U32 u32GroupOffset;
}MS_PQBin_XRule_Info;


typedef struct
{
    MS_U16 u16IPNum;
    MS_U32 u32Offset;
}MS_PQBin_SkipRule_Info;


typedef struct
{
    MS_U16 u16SourceNum;
    MS_U16 u16IPNum;
    MS_U32 u32Offset;
}MS_PQBin_SourceLUT_Info;


typedef struct
{
    MS_U16 u16TableType;
    MS_U16 u16CommRegNum;
    MS_U16 u16IPRegNum;
    MS_U16 u16IPGroupNum;
    MS_U32 u32CommOffset;
    MS_U32 u32IPOffset;
}MS_PQBin_IP_Common_Info;

typedef struct
{
    MS_U8 u8BinID;
    MS_U32 u32BinStartAddress;
    char  u8Header[PQ_BIN_HEADER_LEN];
    char  u8Version[PQ_BIN_VERSION_LEN];
    MS_U32 u32StartOffset;
    MS_U32 u32EndOffset;
    MS_U8  u8Dummy[PQ_BIN_DUMMY];

    // GRule
    char   u8GRuleHader[PQ_BIN_HEADER_LEN];
    MS_U16 u16GRule_RuleNum;
    MS_U16 u16GRule_PnlNum;
    MS_U32 u32GRule_Offset;
    MS_U32 u32GRule_Pitch;
    MS_U32 u32GRule_Lvl_Offset;
    MS_U32 u32GRule_Lvl_Pitch;

    // XRule
    char   u8XRuleHader[PQ_BIN_HEADER_LEN];
    MS_U16 u16XRuleNum;
    MS_U32 u32XRule_Offset;
    MS_U32 u32XRUle_Pitch;

    // SkipRule
    char   u8SkipRuleHader[PQ_BIN_HEADER_LEN];
    MS_U16 u16SkipRule_IPNum;
    MS_U32 u32SkipRule_Offset;

    // IP & Common
    char   u8IP_Comm_Header[PQ_BIN_HEADER_LEN];
    MS_U16 u16IP_Comm_Num;
    MS_U32 u32IP_Comm_Offset;
    MS_U32 u32IP_Comm_Pitch;


    // SourceLUT
    MS_U8  u8SourceLUT_Header[PQ_BIN_HEADER_LEN];
    MS_U16 u16SourceLUT_PnlNum;
    MS_U32 u32SourceLUT_Offset;
    MS_U32 u32SourceLUT_Pitch;
}MS_PQBin_Header_Info;

typedef struct
{
    MS_U8 u8BinID;
    MS_U32 u32BinStartAddress;
    char  u8Header[PQ_TEXT_BIN_HEADER_LEN];
    char  u8Version[PQ_TEXT_BIN_HEADER_LEN];
    MS_U32 u32StartOffset;
    MS_U32 u32EndOffset;
    MS_U8  u8Dummy[PQ_TEXT_BIN_HEADER_LEN];

    //SourceType
    char   u8SrcTypeHeader[PQ_TEXT_BIN_HEADER_LEN];
    MS_U16 u16SrcNum;
    MS_U32 u32SrcType_Offset;
    MS_U32 u32SrcType_Pitch;

    //IPName
    char   u8IPNameHeader[PQ_TEXT_BIN_HEADER_LEN];
    MS_U16 u16IPNum;
    MS_U32 u32IPName_Offset;
    MS_U32 u32IPName_Pitch;

    //GroupName
    char   u8GroupNameHeader[PQ_TEXT_BIN_HEADER_LEN];
    MS_U16 u16GroupIPNum;
    MS_U32 u32IP_Group_Offset;
    MS_U32 u32IP_Group_pitch;
}MS_PQTextBin_Header_Info;

typedef struct
{
    MS_U32 u32TabOffset;
    MS_U16 u16RegNum;
    MS_U16 u16TableType;
    MS_U16 u16GroupNum;
    MS_U16 u16GroupIdx;
}MS_PQBin_IP_Table_Info;




void MDrv_PQBin_Parsing(MS_PQBin_Header_Info *pPQBinHeader);
void MDrv_PQBin_LoadCommTable(MS_U16 u16PnlIdx, MS_PQBin_Header_Info *pPQBinHeader);
MS_U16 MDrv_PQBin_GetIPNum(const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetCurrentTableIndex(MS_U16 u16PnlIdx, MS_U16 u16PQIPIdx);
MS_U16 MDrv_PQBin_GetTableNum(MS_U16 u16PQIPIdx, const MS_PQBin_Header_Info* const pPQBinHeader);
void MDrv_PQBin_LoadTableData(MS_U16 u16PnlIdx, MS_U16 u16TabIdx, MS_U16 u16PQIPIdx, MS_PQBin_Header_Info *pPQBinHeader, MS_U8 *pTable, MS_U16 u16TableSize);
void MDrv_PQBin_LoadTable(MS_U16 u16PnlIdx, MS_U16 u16TabIdx, MS_U16 u16PQIPIdx, MS_PQBin_Header_Info *pPQBinHeader);
void MDrv_PQBin_CloneTable(MS_U16 u16PnlIdx, MS_U16 u16TabIdx, MS_U16 u16PQMainIPIdx, MS_U16 u16PQSubIPIdx, MS_PQBin_Header_Info *pPQBinHeader);
void MDrv_PQBin_GetTable(MS_U16 u16PnlIdx, MS_U16 u16TabIdx, MS_U16 u16PQIPIdx, MS_PQBin_IP_Table_Info *pTableInfo, const MS_PQBin_Header_Info* const pPQBinHeader);
void MDrv_PQBin_DumpTable(MS_PQBin_IP_Table_Info* pTabInfo);
MS_U16 MDrv_PQBin_GetTableIndex(MS_U16 u16PQSrcType, MS_U16 u16PQIPIdx, MS_U16 u16PQPnlIdx, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetSkipRule(MS_U16 u16PQIPIdx, const MS_PQBin_Header_Info* const pPQBinHeader);
void MDrv_PQBin_LoadTableBySrcType(MS_U16 u16PQSrcType, MS_U16 u16PQIPIdx, MS_U16 u16PQPnlIdx, MS_PQBin_Header_Info *pPQBinHeader, PQ_WIN eWindow);


MS_U16 MDrv_PQBin_GetXRuleTableIndex(MS_U16 u16XRuleType, MS_U16 u16XRuleIdx, MS_U16 u16XRuleIP, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetXRuleIPIndex(MS_U16 u16XRuleType, MS_U16 u16XRuleIP, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetXRuleIPNum(MS_U16 u16XRuleType, const MS_PQBin_Header_Info* const pPQBinHeader);


MS_U16 MDrv_PQBin_GetGRule_LevelIndex(MS_U16 u16PnlIdx, MS_U16 u16GRuleType, MS_U16 u16GRuleLvlIndex, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetGRule_IPIndex(MS_U16 u16GRuleType, MS_U16 u16GRuleIPIndex, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetGRule_TableIndex(MS_U16 u16GRuleType, MS_U16 u16PQSrcType, MS_U16 u16PQ_NRIdx, MS_U16 u16GRuleIPIndex, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetGRule_GroupNum(MS_U16 u16GRuleType, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetGRule_IPNum(MS_U16 u16GRuleType, const MS_PQBin_Header_Info* const pPQBinHeader);
MS_U16 MDrv_PQBin_GetGRule_LvlNum(    MS_U16 u16PnlIdx,    MS_U16 u16GRuleType,    const MS_PQBin_Header_Info* const pPQBinHeader);


void MDrv_PQBin_SetDisplayType(PQ_BIN_DISPLAY_TYPE enDisplayType);
PQ_BIN_DISPLAY_TYPE MDrv_PQBin_GetDisplayType(void);

void  MDrv_PQBin_SetPanelID(MS_U8 u8PnlID);
MS_U8 MDrv_PQBin_GetPanelIdx(void);

void MDrv_PQBin_Set_MLoadEn(MS_BOOL bEn);

void MDrv_PQBin_CheckCommTable(MS_U16 u16PnlIdx, MS_PQBin_Header_Info * pPQBinHeader);
void MDrv_PQBin_CheckTableBySrcType(MS_U16 u16PQSrcType, MS_U16 u16PQIPIdx, MS_U16 u16PQPnlIdx, MS_PQBin_Header_Info * pPQBinHeader, PQ_WIN eWindow);


void MDrv_PQTextBin_Parsing(MS_PQTextBin_Header_Info *pPQTextBinHeader);
MS_U32 MDrv_PQTextBin_GetSrcType(MS_U16 u16SrcIdx, const MS_PQTextBin_Header_Info* const pPQTextBinHeader);
MS_U32 MDrv_PQTextBin_GetIPName(MS_U16 u16PQIPIdx, const MS_PQTextBin_Header_Info* const pPQTextBinHeader);
MS_U32 MDrv_PQTextBin_GetTableName(MS_U16 u16PQIPIdx, MS_U16 u16TabIdx, const MS_PQTextBin_Header_Info* const pPQTextBinHeader);

#endif
