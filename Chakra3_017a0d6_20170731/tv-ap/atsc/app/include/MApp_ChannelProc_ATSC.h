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

#ifndef MAPP_CHANNELPROC_ATSC_H
#define MAPP_CHANNELPROC_ATSC_H

#include "Board.h"

//#include "datatype.h"
#if(ENABLE_ATSC)

#include "MApp_GlobalSettingSt.h"

//-----------------------------------------------------------------------------------------

#define MApp_ChanProc_GetCurIdxMap2ChanBufIdx(x)   ((U8)((U16)(x)-u16CurChanlMoveBaseIndx))


//-----------------------------------------------------------------------------------------

typedef enum
{
    METHOD_MAIN_LIST,
    METHOD_PHY_CH
} EN_SORT_METHOD;



#ifdef MAPP_CHANNELPROC_ATSC_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif


INTERFACE S8 MApp_ChanProc_SortMainList(void xdata *pElem1, void xdata *pElem2);
INTERFACE S8 MApp_ChanProc_SortPhysicalChannel(void xdata *pElem1, void xdata *pElem2);


INTERFACE U16 u16CurChanlMoveBaseIndx;

INTERFACE void MApp_ChanProc_GetSingleChannel(MS_VIRTUAL_CHANNEL *pIdleChanenel, U16 u16Index);
INTERFACE void MApp_ChanProc_SetSingleChannel(MS_VIRTUAL_CHANNEL *pIdleChanenel, U16 u16Index);
INTERFACE MS_VIRTUAL_CHANNEL* MApp_ChanProc_GetChannelPointer(U16 u16Index);
INTERFACE MS_VIRTUAL_CHANNEL* MApp_ChanProc_GetCurChannelPointer(void);
INTERFACE MS_VIRTUAL_CHANNEL* MApp_ChanProc_GetTempChannelPointer(U16 u16Index);


INTERFACE void MApp_ChanProc_GetSingleVirtualChannel(MS_VIRTUAL_CHANNEL *pstVirtualCh_func, U16 u16Index);

//=====================================================================================

INTERFACE EN_DEMOD_ATSC_MODE MApp_ChanProc_Get_ChannelModulation(MS_VIRTUAL_CHANNEL* pstVirCh);
INTERFACE void MApp_ChanProc_Get_TPSetting(MS_VIRTUAL_CHANNEL* pstVirCh, MS_TP_SETTING_ATSC* pTpSetting_ATSC);
INTERFACE BOOL MApp_ChanProc_Is_ChannelAtv(MS_VIRTUAL_CHANNEL* pstVirCh);
INTERFACE BOOL MApp_ChanProc_Is_CurChannelAtv(void);

INTERFACE BOOLEAN MApp_ChanProc_IsInSamePhysicalChannel(U16 u16ProgIdx_1, U16 u16ProgIdx_2);
INTERFACE BOOLEAN MApp_ChanProc_IsInSamePage(U16 u16CurIndex, U8 u8ChanNumPerPage);
INTERFACE U16 MApp_ChanProc_CalculateCurPageBaseIdx(U16 u16CurIndex, U8 u8ChanNumPerPage);
INTERFACE U16 MApp_ChanProc_GetNextFavoriteOrdinal(U16 u16Star);
INTERFACE U16 MApp_ChanProc_GetFirstFavoriteOrdinal(void);
INTERFACE void MApp_ChanProc_GetTotalFavFromMainList(void);
INTERFACE void MApp_ChanProc_GetTotalDispFromMainList(void);
INTERFACE U16 MApp_ChanProc_GetNumOfServices(EN_LIST_TYPE enListType);
INTERFACE void MApp_ChanProc_ResetDelChannel(void);
INTERFACE void MApp_ChanProc_DelChannel(void);
INTERFACE BOOLEAN MApp_ChanProc_CheckAnyChan2bDeleted(void);
INTERFACE U16 MApp_ChanProc_CalculateTotalSrvNum(MS_PHYSICAL_CHANNEL *pstPhysicalChTemp, EN_ANT_TYPE enAntennaType);
#ifdef MAINLISTSRV_ANALOGCH_NUM
INTERFACE U16 MApp_ChanProc_CalculateAnalogSrvNum(MS_PHYSICAL_CHANNEL *pstPhysicalChTemp, EN_ANT_TYPE enAntennaType);
#endif
INTERFACE void MApp_ChanProc_RefreshVirChInfoStartIdx(void);

INTERFACE U16 MApp_ChanProc_GetProgIdxByVirChNum(MS_VIRTUAL_CHANNEL_NUM *pstVirtualChNum);
INTERFACE U16 MApp_ChanProc_GetProgIdxByVirChIdx(U8 u8PhysicalChIdx, U8 u8VirChInfoIdx);
INTERFACE void MApp_ChanProc_CreateMainList(MS_PHYSICAL_CHANNEL *pstPhysicalChTemp, MS_MAINLIST_A *pstMainListTemp, EN_ANT_TYPE enAntennaType);


// refresh channel buffer
INTERFACE BOOLEAN MApp_ChanProc_RefreshChannelBuffer(EN_LIST_TYPE enListType);

// get program index function
INTERFACE EN_LIST_TYPE MApp_ChanProc_GetCurProgListType( void );
INTERFACE U16 MApp_ChanProc_GetCurMainListProgIndex(void);
INTERFACE U16 MApp_ChanProc_GetCurProgIndex( void );
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
INTERFACE BOOLEAN MApp_ChanProc_IsCurProgIndexAir(void);
INTERFACE U16 MApp_ChanProc_GetCurCableProgIndex(void);
#endif

INTERFACE U16 MApp_ChanProc_GetPreProgIndex( void );
// set program index function
INTERFACE BOOLEAN MApp_ChanProc_SwitchProgIndex(EN_LIST_TYPE enFromListType, EN_LIST_TYPE enToListType);
INTERFACE BOOLEAN MApp_ChanProc_IncProgIndex(EN_LIST_TYPE enListType, U8 incItemsCount, BOOLEAN fSkipHide);
INTERFACE BOOLEAN MApp_ChanProc_DecProgIndex(EN_LIST_TYPE enListType, U8 decItemsCount, BOOLEAN fSkipHide);
INTERFACE BOOLEAN MApp_ChanProc_ChRtnProgIndex(void);
INTERFACE BOOLEAN MApp_ChanProc_SetMainListProgIndex(U16 u16ProgIndex);
INTERFACE void MApp_ChanProc_SaveLastWatched(void);
INTERFACE void MApp_ChanProc_ResetAllIndex(U16 value);
INTERFACE void MApp_ChanProc_ResetProgIdxByVirChIdx(U8 u8PrePhyChIdx, U8 u8PreVirChInfoIdx, U8 u8CurPhyChIdx, U8 u8CurVirChInfoIdx);
BOOLEAN MApp_ChanProc_ResetProgIdx_ToFirstAtvDtv(BOOLEAN bIsAtv);


#define MApp_ChanProc_GetRfChannelPointer( pstVirtualCh_func, prfchannel) do{\
    /*PRINT_CURRENT_LINE(); */\
    MApp_ChanProc_GetRfChannelPointer2( pstVirtualCh_func, prfchannel);\
}while(0);\

INTERFACE void MApp_ChanProc_GetRfChannelPointer2(MS_VIRTUAL_CHANNEL* pstVirtualCh_func,MS_RF_CHANNEL_new* prfchannel);

//INTERFACE void MApp_ChanProc_SetRfChannelPointer(MS_VIRTUAL_CHANNEL* pstVirtualCh_func,MS_RF_CHANNEL_new* prfchannel);


//#if (EPG_THIS_CH==TRUE)
U16 MApp_GetPrevNextProgramIndex(BOOLEAN bPreProgram);
U16 MApp_GetPrevNextProgramIndex_ByProgIndex(BOOLEAN bPreProgram, U16 u16ProgIndex);
//#endif

INTERFACE void MApp_CM_PrintAllCh(void);
INTERFACE BOOLEAN MApp_ChanProc_DecFavProgIndex( U8 decItemsCount, BOOLEAN fSkipHide);
INTERFACE BOOLEAN MApp_ChanProc_IncFavProgIndex( U8 incItemsCount, BOOLEAN fSkipHide);

#if (ASSIGN_NTSC_PROGRAM_AS_DEFAULT_CH == ENABLE)
INTERFACE void MApp_ChanProc_AssignNTSCProg2EveryRFChannel(void);
#endif

BOOLEAN MApp_ChanProc_IsAnyChannelExist(void);


//=====================================================================================
U8 msAPI_CM_ATSC_Get_ServiceType(U16 u16VirChIdx);

//=====================================================================================

U8 msAPI_ChProc_ATSC_Get_Attr_Lock_By_ProgIdx(U16 u16ProgIdx);
U8 msAPI_ChProc_ATSC_Get_Attr_Fav_By_ProgIdx(U16 u16ProgIdx);

MEMBER_SERVICETYPE msAPI_ChProc_ATSC_Get_ServiceType_By_ProgIdx(U16 u16ProgIdx);

//=====================================================================================


#undef INTERFACE


#endif // ENABLE_ATSC


//------------------------------------------------------------------------------

#endif // MAPP_CHANNELPROC_ATSC_H

