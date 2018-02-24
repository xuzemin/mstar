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

#include "Board.h"

#if(ENABLE_SBOOT_LOAD_BIN)

#include "debug.h"

#include "drv_Joba.h"

#include "drvMBX.h"

#include "msAPI_Joba.h"

#include "msAPI_MailBox.h"

#include "msAPI_Timer.h"

//====================================================================

#define JOBA_WAIT_LOAD_BIN_TIMEOUT  2000


static StuJobaShareMem* g_Joba_pstShareMem = 0;

static BOOL g_Joba_bIsAlive = FALSE;

void msAPI_Joba_Init(void)
{
    g_Joba_pstShareMem = (StuJobaShareMem*) MsOS_PA2KSEG1(JOBA_SHARE_MEMORY_ADDR);

#if 0
    if( MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_FRC, MM_COMMON_MBX_QUEUESIZE, _Joba_MBX_InterruptHandler) == E_MBX_SUCCESS)
    {
        MsOS_EnableInterrupt(E_INT_FIQ_AEON_TO_BEON);
    }
#endif

    g_Joba_bIsAlive = TRUE;
}

void msAPI_Joba_DeInit(void)
{
    g_Joba_bIsAlive = FALSE;
}

U16 msAPI_Joba_ShareMem_Get_BinInfoIndex(U16 u16BinId)
{
    U16 u16CurIdx;

    for( u16CurIdx = 0; u16CurIdx < g_Joba_pstShareMem->u16LoadBinInfoCount; u16CurIdx += 1)
    {
        if( g_Joba_pstShareMem->astJobaLoadBinInfo[u16CurIdx].u16BinId == u16BinId )
            return u16CurIdx;
    }

    return 0xFFFF;
}

U8 msAPI_Joba_Get_LoadBinResult(U16 u16BinId)
{
    U16 u16CurIdx = msAPI_Joba_ShareMem_Get_BinInfoIndex(u16BinId);

    if( u16CurIdx >= JOBA_LOAD_BIN_INFO_MAX )
        return JOBA_LOADBIN__NONE;

    return g_Joba_pstShareMem->astJobaLoadBinInfo[u16CurIdx].u8Result;
}

BOOL msAPI_Joba_Is_LoadBinDone(U16 u16BinId)
{
    if( msAPI_Joba_Get_LoadBinResult(u16BinId) == JOBA_LOADBIN__DONE )
    {
        return TRUE;
    }

    return FALSE;
}

BOOL msAPI_Joba_WaitLoadBinDone(U16 u16BinId)
{
    printf("msAPI_Joba_WaitLoadBinDone(u16BinId=0x%X) at %u\n", u16BinId, MsOS_GetSystemTime());

    if( FALSE == g_Joba_bIsAlive )
        return FALSE;

    U8 u8LoadBinResult;
    U32 u32Time1 = MsOS_GetSystemTime();

    while(1)
    {
        u8LoadBinResult = msAPI_Joba_Get_LoadBinResult(u16BinId);
        //printf(" u8LoadBinResult=%u at %u\n", u8LoadBinResult, MsOS_GetSystemTime());

        if( u8LoadBinResult == JOBA_LOADBIN__DONE )
        {
            printf(" Done at %u use %u\n", MsOS_GetSystemTime(), msAPI_Timer_DiffTime_2(u32Time1, MsOS_GetSystemTime()));
            return TRUE;
        }
        else if( u8LoadBinResult == JOBA_LOADBIN__NONE )
        {
            printf("\nWarning: No job! (u16BinId=0x%X)\n", u16BinId);
            return FALSE;
        }

        if( msAPI_Timer_DiffTime_2(u32Time1, MsOS_GetSystemTime()) >= JOBA_WAIT_LOAD_BIN_TIMEOUT )
        {
            printf("\nError: Wait timeout (u16BinId=0x%X)\n", u16BinId);
            return FALSE;
        }

        msAPI_Timer_Delayms(2);

    }

    return FALSE;
}

BOOL msAPI_Joba_Add_LoadBin(U16 u16BinId, U32 u32MemAddr)
{
    MBX_Msg mbxMsg;

    PRINT_CURRENT_LINE();

    mbxMsg.eRoleID          = E_MBX_ROLE_CP;
    mbxMsg.eMsgType         = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass       = E_MBX_CLASS_FRC;
    mbxMsg.u8Index          = JOBA_MBX_CMD_LOADBIN;
    mbxMsg.u8ParameterCount = JOBA_MBX_CMD_LOADBIN_PARA_NUM;
    mbxMsg.u8Parameters[0]  = ((U16)u16BinId&0xFF00) >> 8;
    mbxMsg.u8Parameters[1]  = ((U16)u16BinId&0x00FF);
    mbxMsg.u8Parameters[2]  = ((U32)u32MemAddr&0xFF000000) >> 24;
    mbxMsg.u8Parameters[3]  = ((U32)u32MemAddr&0x00FF0000) >> 16;
    mbxMsg.u8Parameters[4]  = ((U32)u32MemAddr&0x0000FF00) >> 8;
    mbxMsg.u8Parameters[5]  = ((U32)u32MemAddr&0x000000FF) ;

    //return (MApi_MBX_SendMsg(&mbxMsg) == E_MBX_SUCCESS);

    MBX_Result eMBX_Result = MSApi_MBX_SendMsg(&mbxMsg);
    if( eMBX_Result != E_MBX_SUCCESS )
    {
        printf("\nError: Send mail failed! eMBX_Result=%u\n", eMBX_Result);
        return FALSE;
    }

    return TRUE;;
}

#endif

