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
/// @file   drvdma.c
/// @brief  DRAM BDMA control driver
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// The File is the Wrapper for MBX Driver on Chakra2
/// The Usage of App Could be as Below:
/// ----App Init:
/// --------0. If Need, MSApi_MBX_SetInformation(info, size) to Init & Sync. with Co-Processor
/// --------1. MSApi_MBX_Init();
/// --------2. MSApi_MBX_Enable(TRUE);
/// --------3. MSApi_MBX_RegisterMSG(classes, queue_size);
/// ----App Run:
/// --------1. Send Mail: MSApi_MBX_SendMsg(pMsg);
/// -------------Do not need to set pMsg->eRoleID/u8Ctrl/u8S0/u8S1
/// --------2. Recv Mail:
/// ------------a). MSApi_MBX_GetMsgQueueStatus(class, status);
/// ------------b). while(status.stillhasMail) MSApi_MBX_RecvMsg(pMsg);
/// --------3. Reset Mail Queue: MSApi_MBX_ClearMSG(class);
/// ----App Exit:
/// --------1. MSApi_MBX_UnRegisterMSG(class);
/// --------2. MSApi_MBX_Enable(FALSE);
/// --------3. MSApi_MBX_DeInit();
////////////////////////////////////////////////////////////////////////////////

#define _MSAPI_MAILBOX_C_

////////////////////////////////////////////////////////////////////////////////
// Include List
////////////////////////////////////////////////////////////////////////////////
//#include "MsCommon.h"
#include "Board.h"

#include "msAPI_MailBox.h"

////////////////////////////////////////////////////////////////////////////////
// Local defines & local structures
////////////////////////////////////////////////////////////////////////////////
#define MSApi_MBX_DEBUG  0

////////////////////////////////////////////////////////////////////////////////
// Local Global Variables
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// External Funciton
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Global Funciton
////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------
/// Set Information to dedicated Mailbox HW Regs.
/// @param  pU8Info \b IN: The Information which need to set
/// @param  u8Size \b IN: The Size(bytes) of pU8Info
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em>It is used for speciall need when Init-Coprocesser.
///                 Could be called before MDrv_MBX_Init
///                 Could only be called from HK</em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_SetInformation(MS_U8 *pU8Info, MS_U8 u8Size)
{
    return MDrv_MBX_SetInformation(E_MBX_ROLE_CP, pU8Info, u8Size);
}

/// House Keeping do not support this API.
MBX_Result MSApi_MBX_GetInformation(MS_U8 *pU8Info, MS_U8 u8Size)
{
    return MDrv_MBX_GetInformation(E_MBX_ROLE_CP, pU8Info, u8Size);
}

//-------------------------------------------------------------------------------------------------
/// Init Mailbox
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_NO_MORE_MEMORY
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em></em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_Init(void)
{
    MBX_CPU_ID eHKCPU;
    MS_U32 u32TimeoutMillSecs = 1500;

#if MSApi_MBX_DEBUG
    MDrv_MBX_SetDbgLevel(MBX_DBG_LEVEL_ALL);
#endif

#if (defined(MIPS_CHAKRA)||defined(ARM_CHAKRA))
    eHKCPU = E_MBX_CPU_MIPS;
#else
  #ifdef __AEONR2__
    eHKCPU = E_MBX_CPU_R2M;
  #else
    eHKCPU = E_MBX_CPU_AEON;
  #endif
#endif

    return MDrv_MBX_Init(eHKCPU, E_MBX_ROLE_HK, u32TimeoutMillSecs);
}

//-------------------------------------------------------------------------------------------------
/// Deinitialize Mailbox
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_HAS_MSG_PENDING
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_DeInit(void)
{
    return MDrv_MBX_DeInit(TRUE);
}

//-------------------------------------------------------------------------------------------------
/// Enable Message Queue to recv message from peer CPUs, Enable receiving regisited messages in kernel
/// Covered by Reference Cnt which means maybe won't take effect.
/// @param  bEnable \b IN: Enable or not
///                  - # TRUE: enable
///                  - # FALSE: disable
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_Enable(MS_BOOL bEnable)
{
    return MDrv_MBX_Enable(bEnable);
}

//-------------------------------------------------------------------------------------------------
/// Regisiter Message queue for special class
/// @param  eMsgClass \b IN: Mail Message Class, @ref MBX_Class
/// @param  u16MsgQueueSize \b IN: The mail message queue size,
///                                The Max should not exceed @ref MAX_MBX_QUEUE_SIZE
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_NO_MORE_MEMORY
/// @return E_MBX_ERR_SLOT_BUSY
/// @return E_MBX_ERR_SLOT_AREADY_OPENNED
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_RegisterMSG(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize)
{
    return MDrv_MBX_RegisterMSG(eMsgClass, u16MsgQueueSize);
}

//-------------------------------------------------------------------------------------------------
/// Regisiter Message queue for special class With Callback Handler Function
/// @param  eMsgClass \b IN: Mail Message Class, @ref MBX_Class
/// @param  u16MsgQueueSize \b IN: The mail message queue size,
///                                The Max should not exceed @ref MAX_MBX_QUEUE_SIZE
/// @param  notifier \b IN: status change notify call function about this message queue, could be NULL
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_NOT_IMPLEMENTED
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_NO_MORE_MEMORY
/// @return E_MBX_ERR_SLOT_BUSY
/// @return E_MBX_ERR_SLOT_AREADY_OPENNED
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_RegisterMSGWithCallBack(MBX_Class eMsgClass, MS_U16 u16MsgQueueSize, MBX_MAIL_ARRIVE_NOTIFY_FUNC notifier)
{
    return MDrv_MBX_RegisterMSGWithCallBack(eMsgClass, u16MsgQueueSize, notifier);
}

//-------------------------------------------------------------------------------------------------
/// UnRegisiter Message queue for special class
/// @param  eMsgClass \b IN: Mail Message Class, @ref MBX_Class
/// @param  bForceDiscardMsgQueue    \b IN: If Discard Pending Mail Message or not \n
///              - # TRUE: Discard it and De-Init
///              - # FALSE: if has pending mail message,
///                     No Discard and Do not De-Init, return E_MBX_ERR_HAS_MSG_PENDING
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_SLOT_NOT_OPENNED
/// @return E_MBX_ERR_HAS_MSG_PENDING
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_UnRegisterMSG(MBX_Class eMsgClass)
{
    return MDrv_MBX_UnRegisterMSG(eMsgClass, TRUE);
}

//-------------------------------------------------------------------------------------------------
/// Check the message queue status of a special message class
/// @param  eTargetClass \b IN: target class, @ref MBX_Class
/// @param  pMsgQueueStatus \b IN: return the queue status, @ref MBX_MSGQ_Status
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_SLOT_NOT_OPENNED
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_GetMsgQueueStatus(MBX_Class eTargetClass, MBX_MSGQ_Status *pMsgQueueStatus)
{
    return MDrv_MBX_GetMsgQueueStatus(eTargetClass, pMsgQueueStatus);
}

//-------------------------------------------------------------------------------------------------
/// Send message
/// @param  pMsg \b IN: Mail Message Class for sending, must not be NULL, @ref MBX_Msg
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_SLOT_NOT_OPENNED
/// @return E_MBX_ERR_INVALID_CPU_ID
/// @return E_MBX_ERR_PEER_CPU_BUSY
/// @return E_MBX_ERR_PEER_CPU_NOT_ALIVE
/// @return E_MBX_ERR_PEER_CPU_OVERFLOW
/// @return E_MBX_ERR_TIME_OUT
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_SendMsg(MBX_Msg *pMsg)
{
    if(NULL == pMsg)
    {
        return E_MBX_ERR_INVALID_PARAM;
    }

    pMsg->eRoleID = E_MBX_ROLE_CP;
    pMsg->u8Ctrl = pMsg->u8S0 = pMsg->u8S1 = 0x0;

    return MDrv_MBX_SendMsg(pMsg);
}

//-------------------------------------------------------------------------------------------------
/// Recv message
/// @param  eTargetClass \b IN: target class, @ref MBX_Class
/// @param  pMsg \b IN: Mail Message Class for receive, must not be NULL, @ref MBX_Msg
/// @param  u32WaitMillSecs \b IN: if MBX_CHECK_BLOCK_RECV, indentify the timeout millsecons before return
/// @param  u32Flag \b IN: recv flag, has the following possible meaning bits
///                  - # MBX_CHECK_ALL_MSG_CLASS: recv any message class, this means, the targetClass is useless if this bit is set.
///                  - # MBX_CHECK_INSTANT_MSG: check INSTANT message.
///                  - # MBX_CHECK_NORMAL_MSG: Check Normal message.
///                  - # MBX_CHECK_BLOCK_RECV: block this function call until time out if no message available.
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_SLOT_NOT_OPENNED
/// @return E_MBX_ERR_NO_MORE_MSG
/// @return E_MBX_ERR_TIME_OUT
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_RecvMsg(MBX_Class eTargetClass, MBX_Msg *pMsg, MS_U32 u32WaitMillSecs, MS_U32 u32Flag)
{
    return MDrv_MBX_RecvMsg(eTargetClass, pMsg, u32WaitMillSecs, u32Flag);
}

//-------------------------------------------------------------------------------------------------
/// Clear Message queue for special class
/// @param  eMsgClass \b IN: Mail Message Class, @ref MBX_Class
/// @return E_MBX_SUCCESS
/// @return E_MBX_ERR_INVALID_PARAM
/// @return E_MBX_ERR_NOT_INITIALIZED
/// @return E_MBX_ERR_SLOT_NOT_OPENNED
/// @return E_MBX_UNKNOW_ERROR
/// @attention
/// <b>[MXLIB] <em> </em></b>
//-------------------------------------------------------------------------------------------------
MBX_Result MSApi_MBX_ClearMSG(MBX_Class eMsgClass)
{
    return MDrv_MBX_ClearMSG(eMsgClass);
}

