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
/***********************************************************************
 * MODULE     : TT_PacketBuffer
 * FILE       : TT_PacketBuffer.c
 * COPYRIGHT  : TARA Systems GmbH
 * DESCRIPTION:
 *   Teletext packet buffer
 *
 * REMARK:
 *   This file contains Intellectual Property and must NEVER be released.
 ***********************************************************************/

#ifndef TT_PACKETBUFFER_H
#define TT_PACKETBUFFER_H

#include "TT_API25.h"

/***********************************************************************
 * SECTION: #define
 ***********************************************************************/

#define TT_PACKETBUFFER_PACKET_LENGTH 44

/***********************************************************************
 * SECTION: typedef
 ***********************************************************************/

/***********************************************************************
 * TYPE: TT_PACKETBUFFER_PACKET_HANDLE
 ***********************************************************************/
typedef struct
{
  TT_U8
    Data[ TT_PACKETBUFFER_PACKET_LENGTH ];

} TT_PACKETBUFFER_PACKET;

typedef TT_PACKETBUFFER_PACKET * TT_PACKETBUFFER_PACKET_HANDLE;

/***********************************************************************
 * TYPE: TT_PACKETBUFFER
 ***********************************************************************/
typedef struct
{
  TT_S16
    ReadPointer,
    WritePointer;

#if(TT_TARGET == TT_TARGET_XX)
  TT_PACKETBUFFER_PACKET_HANDLE
    Packet[ TT_PACKETBUFFER_NUM_PACKETS ];
#else
  TT_PACKETBUFFER_PACKET
    Packet[ TT_PACKETBUFFER_NUM_PACKETS ];
#endif

  TT_U16
    NoOfPacketBufferOverflows;

  TT_BOOL
    PacketBufferOverflow;

} TT_PACKETBUFFER;

/***********************************************************************
 * TYPE: TT_PACKETBUFFER_HANDLE
 ***********************************************************************/
typedef TT_PACKETBUFFER * TT_PACKETBUFFER_HANDLE;


#ifdef __cplusplus
  extern "C" {
#endif



/***********************************************************************
 * FUNCTION: TT_PacketBufferCreate
 *
 * DESCRIPTION:
 *   Create Teletext Packet Buffer.
 *
 * RETURN:
 *   TRUE if successfull,
 *   FALSE otherwise.
 ***********************************************************************/
PUBLIC TT_BOOL
TT_PacketBufferCreate( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferDelete
 *
 * DESCRIPTION:
 *   Deletes Teletext PacketBuffer.
 *
 ***********************************************************************/
PUBLIC void
TT_PacketBufferDelete( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferReset
 *
 * DESCRIPTION:
 *   Resets the Teletext PacketBuffer. All Data is removed from the
 *   buffer and the overflow counter is set to zero.
 *
 ***********************************************************************/
PUBLIC void
TT_PacketBufferReset( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferClear
 *
 * DESCRIPTION:
 *   Remove all data from the packet buffer and reset the overflow flag.
 *
 ***********************************************************************/
PUBLIC void
TT_PacketBufferClear( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferSetPacket
 *
 * DESCRIPTION:
 *   Transfer packet data into the packet buffer.
 *
 * PARAMETERS:
 *   aPacket     - pointer to packet data
 *
 * RETURN:
 *   TRUE if successfull,
 *   FALSE otherwise.
 ***********************************************************************/
PUBLIC TT_BOOL
TT_PacketBufferSetPacket(
  TT_PACKETBUFFER_PACKET_HANDLE  aPacket );


/***********************************************************************
 * FUNCTION: TT_PacketBufferGetPacket
 *
 * DESCRIPTION:
 *   Retrieves packet data from packet buffer.
 *
 * RETURN:
 *   On success: pointer to packet data,
 *   NULL on failure.
 ***********************************************************************/
PUBLIC TT_PACKETBUFFER_PACKET_HANDLE
TT_PacketBufferGetPacket( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferIsEmpty
 *
 * DESCRIPTION:
 *   Check if the packet buffer is empty.
 *
 * RETURN:
 *   TRUE if the packet buffer is empty,
 *   NULL otherwise.
 ***********************************************************************/
PUBLIC TT_BOOL
TT_PacketBufferIsEmpty( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferIsOverflow
 *
 * DESCRIPTION:
 *   Check if there is a packet buffer overflow. If there is an overflow,
 *   the the packet buffer should be cleared from the reading task.
 *
 * RETURN:
 *   TRUE if there is packet buffer overflow,
 *   NULL otherwise.
 ***********************************************************************/
PUBLIC TT_BOOL
TT_PacketBufferIsOverflow( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferGetNoOfOverflows
 *
 * DESCRIPTION:
 *   Resuren the nomber of packet buffer overflows since the last reset
 *   or creation.
 *
 * RETURN:
 *   The number of packet buffer overflows.
 ***********************************************************************/
PUBLIC TT_U16
TT_PacketBufferGetNoOfOverflows( void );


/***********************************************************************
 * FUNCTION: TT_PacketBufferSetChannelChangeStartTime
 *
 * DESCRIPTION:
 * Setup the channel change time when channel change at channel fading time
 *
 *
 * RETURN:
 *
 ***********************************************************************/
PUBLIC void
TT_PacketBufferSetChannelChangeStartTime( TT_U32 u32Channelchange_fadingtime );


#ifdef __cplusplus
  }
#endif

#endif /* TT_PACKETBUFFER_H */

/* This Headerfile was generated with C2H.pl ( C2H ) V 1.28 */
/* (c) 2003 by TARA-Systems GmbH Munich */
