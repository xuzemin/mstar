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

#ifndef __API_CHPROC_H__
#define __API_CHPROC_H__

#include "debug.h"

#include "MApp_GlobalSettingSt.h"
#include "msAPI_DTVSystem.h"
//#include "msAPI_Tuner.h"



#define ENABLE_CH_PROC_2015     0//ENABLE

#ifndef ENABLE_CHPROC_ORDINAL_LIST
  #if ENABLE_SBTVD_CM_APP
    #define ENABLE_CHPROC_ORDINAL_LIST  1

  #elif(ENABLE_DVB)
    #define ENABLE_CHPROC_ORDINAL_LIST  ENABLE_CH_PROC_2015

  #else

    #define ENABLE_CHPROC_ORDINAL_LIST  0
  #endif
#endif


#if( ENABLE_CHRPOC_NEW_FAVORITE_METHOD )
    #define CHPROC_FAV_ACCESS_BOUNDRY   E_PROGACESS_INCLUDE_ALL
#else
    #define CHPROC_FAV_ACCESS_BOUNDRY   E_PROGACESS_INCLUDE_VISIBLE_ONLY
#endif


//------------------------------------------------------------------------------
// Public attributes.
//------------------------------------------------------------------------------
#define INVALID_ORDINAL                 0xFFFF
#define INVALID_ATV_PROGRAM_NUMBER      0xFF

typedef enum
{
    E_SERVICE_ATTR_TYPE             = 0x70,
    E_SERVICE_ATTR_NUMBER           = 0x71,
    E_SERVICE_ATTR_NAME             = 0x72,
    E_SERVICE_ATTR_SKIPPED          = 0x73,
    E_SERVICE_ATTR_FAVORITE         = 0x74,
    E_SERVICE_ATTR_LOCKED           = 0x75,
    E_SERVICE_ATTR_VISIBLE          = 0x76,
    E_SERVICE_ATTR_NUMERIC          = 0x77
} SERVICE_ATTRIBUTE_MEMBER;


//------------------------------------------------------------------------------
// Public functions.
//------------------------------------------------------------------------------

WORD msAPI_CHPROC_CM_GetCurrentOrdinal(MEMBER_SERVICETYPE bServiceType, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);
BOOLEAN msAPI_CHPROC_CM_SetCurrentOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);

U16 msAPI_CHPROC_CM_Get_TotalDtvProgramCount(E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);
WORD msAPI_CHPROC_CM_CountProgram(MEMBER_SERVICETYPE bServiceType, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);

BOOLEAN msAPI_CHPROC_CM_Get_ServiceType_Position_ByOrdinal( MEMBER_SERVICETYPE eServiceType, U16 u16Ordinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary, MEMBER_SERVICETYPE* peServiceType, U16* pu16Position );

WORD msAPI_CHPROC_CM_CountFavoriteProgram(MEMBER_SERVICETYPE bServiceType);
WORD msAPI_CHPROC_CM_GetFirstFavoriteOrdinal(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped);
WORD msAPI_CHPROC_CM_GetNextFavoriteOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped);

//WORD msAPI_CHPROC_CM_GetSimilarOrdinals(MEMBER_SERVICETYPE bServiceType, WORD wPressedNumber, WORD * pwOrdinal, BYTE cSizeOfBuffer);
WORD msAPI_CHPROC_CM_GetMatchedOrdinals(MEMBER_SERVICETYPE bServiceType, WORD wPressedNumber);

BOOLEAN msAPI_CHPROC_CM_GetAttributeOfOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, SERVICE_ATTRIBUTE_MEMBER eAttributeMember, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);
//#define msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, pcBuffer, eAttributeMember, eBoundary)  (printf("%u:%s call GetAttributeOfOrdinal\n", __LINE__, __FILE__)? msAPI_CHPROC_CM_GetAttributeOfOrdinal_2(bServiceType, wOrdinal, pcBuffer, eAttributeMember, eBoundary): 0 )

BOOLEAN msAPI_CHPROC_CM_SetMove2CurrentOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);

#if(ENABLE_CHPROC_ORDINAL_LIST)
void msAPI_CHPROC_ORD_PrintOridialList(void);

void msAPI_CHPROC_CM_ResetOridial(void);
void msAPI_CHPROC_CM_InitOridial(void);
#endif

#if ENABLE_SBTVD_CM_APP
WORD msAPI_CHPROC_CM_GetNextOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped);
WORD msAPI_CHPROC_CM_GetPrevOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped);
WORD msAPI_CHPROC_CM_GetOrdinal_Brazil(MEMBER_SERVICETYPE bServiceType,WORD wPosition);
BOOLEAN msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(WORD wOridinal,MEMBER_SERVICETYPE * pbServiceType,WORD * pwPosition);
MEMBER_SERVICETYPE msAPI_CHPROC_CM_GetServiceTypeByLCN_Brazil(WORD wPosition,WORD * wOridinal);
#endif

#endif // __API_CHPROC_H__

