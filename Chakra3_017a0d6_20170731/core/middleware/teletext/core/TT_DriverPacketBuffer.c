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

/***********************************************************************
 * SECTION: #include
 ***********************************************************************/
#include "TT_Global.h"
#include "TT_PacketBuffer.h"
#include "MsTypes.h"
#ifndef TTX_ATV_DISABLE
#include "drvVBI.h"
#endif
#include "drvDMX_TTX.h"
#include "TT_DriverSlicer.h"
#include "MsCommon.h"
#include "MsOS.h"
#include "datatype.h"
#include "apiDMX.h"
#include "TT_VETTXOut.h"
#include "TT_DriverIntRam.h"
#ifdef ENABLE_DTV
#if(ENABLE_DTV)
#include "msAPI_demux.h"
#include "mapp_demux.h"
#endif
#endif

#define USING_HARDWARE_PACKET_BUFFER 1

#define THRESHOLD_CHANNEL_CHANGE_TIME_PRD   50000   // us

#define IS_DTV_SYSTEM() (TT_DRIVER_SLICER_DTV == TT_DriverSlicer_Get_CurrentSource())
/***********************************************************************
 * SECTION: Declaration of private variables
 ***********************************************************************/
#if(USING_HARDWARE_PACKET_BUFFER==0)
PRIVATE TT_PACKETBUFFER_HANDLE my_handle;
#endif

static TT_U32 _u32ChannelChangeStartingTime = 0;

static TT_PACKETBUFFER_PACKET_HANDLE _OnepacketHandle = 0;

/***********************************************************************
 * SECTION: Definition of public functions
 ***********************************************************************/

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
TT_U8* nullBuffer;

PRIVATE
void TT_DriverPacketBufferReset(void)
{
  if(IS_DTV_SYSTEM())
  {
    MDrv_DMX_TTX_RingBuffer_Reset();
  }
#ifndef TTX_ATV_DISABLE
  else
  {
    MDrv_VBI_RingBuffer_Reset();
  }
#endif
}

PUBLIC TT_BOOL
TT_PacketBufferCreate( void )
{

#if(USING_HARDWARE_PACKET_BUFFER==0)

  my_handle = TT_DriverIntRamAlloc( TT_PACKETBUFFER_MEM_SIZE );
  if (my_handle == NULL)
    return FALSE;

  TT_DriverIntRamMemset( my_handle, 0, sizeof(TT_PACKETBUFFER) );

  my_handle->NoOfPacketBufferOverflows = 0;
  my_handle->PacketBufferOverflow = FALSE;
#else

  TT_VETTXOutService.Init();

  _OnepacketHandle =
    (TT_PACKETBUFFER_PACKET_HANDLE)TT_DriverIntRamAlloc(sizeof(TT_PACKETBUFFER_PACKET));

  TT_DriverIntRamMemset((void*)_OnepacketHandle,
                        0,
                        sizeof(TT_PACKETBUFFER_PACKET));
#endif

  return TRUE;
}

/***********************************************************************
 * FUNCTION: TT_PacketBufferDelete
 *
 * DESCRIPTION:
 *   Deletes Teletext PacketBuffer.
 *
 ***********************************************************************/
PUBLIC void
TT_PacketBufferDelete( void )
{
#if(USING_HARDWARE_PACKET_BUFFER==0)
  my_handle = NULL;
#endif
}

/***********************************************************************
 * FUNCTION: TT_PacketBufferReset
 *
 * DESCRIPTION:
 *   Resets the Teletext PacketBuffer. All Data is removed from the
 *   buffer and the overflow counter is set to zero.
 *
 ***********************************************************************/
PUBLIC void
TT_PacketBufferReset( void )
{
#if(USING_HARDWARE_PACKET_BUFFER==0)
  my_handle->ReadPointer    = 0;
  my_handle->WritePointer   = 0;
  my_handle->NoOfPacketBufferOverflows = 0;
  my_handle->PacketBufferOverflow = FALSE;
#endif
  TT_DriverPacketBufferReset();
}

/***********************************************************************
 * FUNCTION: TT_PacketBufferClear
 *
 * DESCRIPTION:
 *   Remove all data from the packet buffer and reset the overflow flag.
 *
 ***********************************************************************/
PUBLIC void
TT_PacketBufferClear( void )
{
#if(USING_HARDWARE_PACKET_BUFFER==0)
  my_handle->ReadPointer    = 0;
  my_handle->WritePointer   = 0;
  my_handle->PacketBufferOverflow = FALSE;
#else
  TT_DriverPacketBufferReset();
#endif
}

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
#if(USING_HARDWARE_PACKET_BUFFER==0)
PUBLIC TT_BOOL
TT_PacketBufferSetPacket(
  TT_PACKETBUFFER_PACKET_HANDLE  aPacket )
{
  TT_S16
    NumberOfFreePackets;

  if (my_handle == NULL)
    return FALSE;

  if (my_handle->PacketBufferOverflow)
    return FALSE;

  NumberOfFreePackets = (TT_S16)(my_handle->WritePointer - my_handle->ReadPointer);
  if (NumberOfFreePackets < 0)
    NumberOfFreePackets += TT_PACKETBUFFER_NUM_PACKETS;

  NumberOfFreePackets = (TT_S16)(TT_PACKETBUFFER_NUM_PACKETS - NumberOfFreePackets);

  if (NumberOfFreePackets < 2)
  {
    my_handle->NoOfPacketBufferOverflows++;
    my_handle->PacketBufferOverflow = TRUE;
    return FALSE;
  }

  //TT_DriverIntRamMemcpy( &my_handle->Packet[my_handle->WritePointer], aPacket, sizeof(TT_PACKETBUFFER_PACKET) );
  my_handle->Packet[my_handle->WritePointer] = aPacket;

  if (++my_handle->WritePointer >= TT_PACKETBUFFER_NUM_PACKETS)
    my_handle->WritePointer = 0;

  return TRUE;
}
#endif

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
TT_PacketBufferGetPacket( void )
{
#if(USING_HARDWARE_PACKET_BUFFER==0)
  TT_S16
    NumberOfPackets;

  if (my_handle == NULL)
    return NULL;

  NumberOfPackets = (TT_S16)(my_handle->WritePointer - my_handle->ReadPointer);
  if (NumberOfPackets < 0)
    NumberOfPackets += TT_PACKETBUFFER_NUM_PACKETS;

  if (NumberOfPackets == 0)
    return NULL;

  returnValue = my_handle->Packet[my_handle->ReadPointer];

  if (++my_handle->ReadPointer >= TT_PACKETBUFFER_NUM_PACKETS)
    my_handle->ReadPointer = 0;
#else
  TT_BOOL isSuccessful = FALSE;
  TT_U32  packetPointer;
  TT_U8   *dummy = 0;

  if(IS_DTV_SYSTEM())
  {

     void VE_SavePKtDataInBuffer(TT_U32 pktAddr);
#ifdef ENABLE_DTV
#if(ENABLE_DTV)
     msAPI_DMX_Proc(*MApp_Dmx_GetFid(EN_TTX_FID));
#endif
#endif
     isSuccessful = MDrv_DMX_TTX_GetPacket(&packetPointer);
  }
#ifndef TTX_ATV_DISABLE
  else
  {
    isSuccessful = MDrv_VBI_TTX_GetPacket(&packetPointer);
  }
#endif

  if(isSuccessful)
  {

    dummy = (TT_U8 *)_PA2VA(packetPointer + 4);

    if ( dummy[1] != 0x27 ) /* check framming code */
    {
      dummy = 0;
    }

    MsOS_ReadMemory();
    MsOS_FlushMemory();

    if(dummy != 0)
    {
        TT_DriverIntRamMemcpy(_OnepacketHandle->Data,
                              dummy,
                              TT_PACKETBUFFER_PACKET_LENGTH);

        dummy = (TT_U8*)(_OnepacketHandle);
    }
  }
  else
    dummy = 0;

  if(IS_DTV_SYSTEM())
  {
        TT_VETTXOutService.SendPacket(dummy == 0 ? (MS_U8*)0 : (MS_U8*)packetPointer);
  }
#endif
  return (TT_PACKETBUFFER_PACKET_HANDLE)(void*)dummy;
}

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
PUBLIC TT_BOOL TT_PacketBufferIsEmpty( void )
{
#if(USING_HARDWARE_PACKET_BUFFER==0)
  if (my_handle->WritePointer - my_handle->ReadPointer) /* no of packets */
    return FALSE;

  return TRUE;
#else
  if(IS_DTV_SYSTEM())
    return MDrv_DMX_TTX_PacketBufferIsEmpty();
#ifndef TTX_ATV_DISABLE
  else
    return MDrv_VBI_TTX_PacketBufferIsEmpty();
#else
    return TRUE;
#endif
#endif
}

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
TT_PacketBufferIsOverflow( void )
{
#if(USING_HARDWARE_PACKET_BUFFER==0)
  return my_handle->PacketBufferOverflow;
#else
  TT_BOOL isOverflow = FALSE;

  if(IS_DTV_SYSTEM())
    isOverflow = MDrv_DMX_TTX_PacketBufferIsOverflow();
#ifndef TTX_ATV_DISABLE
  else
  {
      isOverflow = MDrv_VBI_TTX_PacketBufferIsOverflow();

    if(isOverflow)
    {
       if(MsOS_GetSystemTime() - _u32ChannelChangeStartingTime <  THRESHOLD_CHANNEL_CHANGE_TIME_PRD)
       {
           isOverflow = FALSE;
       }
    }
  }
#endif
  return isOverflow;
#endif
}

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
TT_PacketBufferGetNoOfOverflows( void )
{
#if(USING_HARDWARE_PACKET_BUFFER==0)
  return my_handle->NoOfPacketBufferOverflows;
#else
  if(IS_DTV_SYSTEM())
    return MDrv_DMX_TTX_PacketBufferGetNoOfOverflows();
  #ifndef TTX_ATV_DISABLE
  else
    return MDrv_VBI_TTX_PacketBufferGetNoOfOverflows();
  #else
    return 0;
  #endif
#endif
}

PUBLIC void TT_PacketBufferSetChannelChangeStartTime(TT_U32 u32Channelchange_fadingtime)
{
    _u32ChannelChangeStartingTime = u32Channelchange_fadingtime;

}



/* eof */
