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
#ifndef _MAPP_BL_SI_H_
#define _MAPP_BL_SI_H_

#define BL_PAT_MONITOR_PERIOD          2000    /* ms */
#define BL_PMT_MONITOR_PERIOD          500    /* ms */

#define BL_SI_MAX_VC_PER_PHYSICAL      70

// Error Check
#define BL_MAX_NUM_OF_CRC_ERROR    2

/******************************************************************************/
/*                     enum.                                 */
/******************************************************************************/
typedef enum
{
    EN_SI_PARSE_INIT,
    EN_SI_PARSE_WAIT_PAT_READY,
    EN_SI_PARSE_WAIT_ALL_PMT_READY,
}EN_SI_PARSE_STATE;

typedef enum
{
    EN_BL_FIRSTLOOP = 1,
    EN_BL_SECONDLOOP,
} EN_BL_LOOP_TYPE;

typedef enum
{
    EN_BL_PAT,
    EN_BL_PMT,
} EN_BL_PSIP_TABLE;

/* TABLE ID definition */
typedef enum
{
    // MPEG-2 table id
    BL_TID_PAS         = 0x00,             // program_association_section
    BL_TID_PMS         = 0x02,             // program_map_section
} EN_BL_PSIP_TID;

/* Stream Type */
typedef enum
{
    ST_BL_DSMCC_DATA_TYPE_A    = 0x0A,
    ST_BL_DSMCC_DATA_TYPE_B    = 0x0B,
    ST_BL_DSMCC_DATA_TYPE_C    = 0x0C,
    ST_BL_DSMCC_DATA_TYPE_D    = 0x0D,
    ST_BL_DSMCC_DATA_TYPE_E    = 0x0E,
    ST_BL_OP_MPEG2_VID         = 0x80,
} EN_BL_SI_STREAM_TYPE;

/* descriptor tag definition */
typedef enum
{
    TAG_BL_SID             = 0x52,         // stream_identifier_descriptor
    TAG_BL_DBID            = 0x66,            // data_broadcast_id_descriptor
}EN_BL_SI_TAG;

/******************************************************************************/
/*                     struct                                 */
/******************************************************************************/
typedef struct
{
    U8 u8NumOfPatItems;
    U16 u16ProgNum[BL_SI_MAX_VC_PER_PHYSICAL];
    U16 u16PmtPID[BL_SI_MAX_VC_PER_PHYSICAL];
}BL_SI_PAT_INFO;


/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#ifdef MAPP_BL_SI_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/******************************************************************************/
/*                       Global Function Prototypes                           */
/******************************************************************************/
INTERFACE void MApp_BL_SI_PAT_Parse(U8 *pu8Section);
INTERFACE void MApp_BL_SI_PMT_Parse(U8 *pu8Section);
INTERFACE void MApp_BL_SI_Init(U32 u32BufferStart, U32 u32BufferSize);
INTERFACE void MApp_BL_SI_ParseStateInit(void);
INTERFACE void MApp_BL_SI_DisableTableMonitor(void);
INTERFACE BL_SI_PAT_INFO* MApp_BL_SI_GetPatScanInfo(void);
INTERFACE BOOLEAN MApp_BL_SI_Table_Monitor(void);
#undef INTERFACE
#endif

