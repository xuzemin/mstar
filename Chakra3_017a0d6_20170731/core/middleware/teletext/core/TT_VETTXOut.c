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
#include "TT_Global.h"
#include "TT_VETTXOut.h"
#include "TT_DriverIntRam.h"
#include "datatype.h"
#include "MsTypes.h"
#include "MsCommon.h"
#include "MsOS.h"
#include "Board.h"
#include "apiXC.h"
#include "apiXC_Sys.h"

#define TTX_PACKET_SIZE 48
#define ADDRESSIGN_ALIGNMENT  16

#define PACKETS_SEND_THRESHOLD  32
#define MAX_PACKET_BUFFER_SIZE 160

#define PEDDING_BUFFER_PAYLOAD_NUM 16

#define VE_DRIVER_TIMEOUT   500

#define TASK_STACK_SIZE  0x30000

typedef struct
{
  MS_U8 data[TTX_PACKET_SIZE];
}TT_TTXPacket;

typedef struct
{
  MS_S32 WriteIndex;
  MS_S32 ReadIndex;
  MS_U32 NumOfLatestSent;
  TT_TTXPacket* packets;
}TT_VEOutState;

#ifdef MSOS_TYPE_LINUX
static MS_U8 _TaskStack[TASK_STACK_SIZE];
static MS_S32 _TaskID = 0;
static MS_S32 _TaskAlarm = 0;
#endif
static TT_VEOutState _VEOutState;
static MS_S32 _SyncObj = 0;
static MS_U8* _peddingData = 0;
//////////////////////////////////////////////////////////////////////
#ifdef MSOS_TYPE_LINUX
static void TT_VETTXOutTask(MS_U32 argc, void* argv);
#else
static void TT_VETTXOutProcess(void);
#endif

static void _VETTXOutAdjustReadIndex(void);
static MS_U32 _VETTXOutNumOfPackets(void);
static MS_U32 _VETTXOutNumOfSendablePackets(void);

static
void TT_VETTXOutInit(void)
{
  MS_U8* buffer = (MS_U8*)TT_DriverIntRamAlloc(
    TTX_PACKET_SIZE*(MAX_PACKET_BUFFER_SIZE+PEDDING_BUFFER_PAYLOAD_NUM)+ADDRESSIGN_ALIGNMENT);
  MS_ASSERT(buffer != 0);

  buffer = (MS_U8*)(((MS_U32)buffer + ADDRESSIGN_ALIGNMENT)/ADDRESSIGN_ALIGNMENT * ADDRESSIGN_ALIGNMENT);

  TT_DriverIntRamMemset(&_VEOutState,
                        0,
                        sizeof(_VEOutState));
  _peddingData = buffer + TTX_PACKET_SIZE*MAX_PACKET_BUFFER_SIZE;

  _VEOutState.packets = (TT_TTXPacket*)((void*)buffer);

  if(_SyncObj == 0)
  {
    _SyncObj = MsOS_CreateMutex(E_MSOS_FIFO,
                                "TT_VEOUT_SYNC_Mutex",
                                MSOS_PROCESS_SHARED);
    MS_ASSERT(_SyncObj > 0);
  }
#ifdef MSOS_TYPE_LINUX
  if(_TaskID == 0)
  {
    _TaskID =
          MsOS_CreateTask((TaskEntry)TT_VETTXOutTask,
                          0U,
                          E_TASK_PRI_HIGH,
                          TRUE,
                          _TaskStack,
                          TASK_STACK_SIZE,
                          "TTX VE-OUT Task");
    MS_ASSERT(_TaskID > 0);
  }
#endif

}

static
MS_BOOL TT_VETTXOutSendPacket(U8* buffer)
{
  MS_U32 numOfPackets;
#ifndef MSOS_TYPE_LINUX
  TT_VETTXOutProcess();
#endif

  if(buffer == 0)
    return FALSE;

  numOfPackets = _VETTXOutNumOfPackets();
  if(numOfPackets >= MAX_PACKET_BUFFER_SIZE - 1)
  {
    //printf("VE Buffer Overflow....\n");
    return FALSE;
  }

  MsOS_FlushMemory();
  TT_DriverIntRamMemcpy(&_VEOutState.packets[_VEOutState.WriteIndex],
                        (void*)_PA2VA((MS_U32)buffer),
                        TTX_PACKET_SIZE);

  OS_OBTAIN_MUTEX(_SyncObj,
                  MSOS_WAIT_FOREVER);

  _VEOutState.WriteIndex++;
  if(_VEOutState.WriteIndex >= MAX_PACKET_BUFFER_SIZE)
  {
    //writeIndex can't catch up the readindex
    if(_VEOutState.ReadIndex != 0)
      _VEOutState.WriteIndex = 0;
    else
      _VEOutState.WriteIndex = MAX_PACKET_BUFFER_SIZE - 1;
  }

  OS_RELEASE_MUTEX(_SyncObj);

#ifdef MSOS_TYPE_LINUX
  if(numOfPackets+1 >= PACKETS_SEND_THRESHOLD)
    MsOS_ReleaseSemaphore(_TaskAlarm);
#endif

  return TRUE;
}

#ifdef MSOS_TYPE_LINUX
static
void TT_VETTXOutTask(MS_U32 argc, void* argv)
{
  MS_U32 numOfPackets;
  static MS_BOOL isFirstTime = TRUE;
  static MS_U32  time0 = 0;
  static MS_U32  donePeriod = 0;

  _TaskAlarm =
    MsOS_CreateSemaphore(0,
                         E_MSOS_FIFO,
                         "TT_VEOUT_TASK_OBJ");
  MS_ASSERT(_TaskAlarm > 0);

  UNUSED(argc);
  UNUSED(argv);

  while(TRUE)
  {
    MsOS_ObtainSemaphore(_TaskAlarm, 19);

    if(isFirstTime || msAPI_VE_GetTtxReadDoneStatus())
    {
      _VETTXOutAdjustReadIndex();

      if(!isFirstTime)
        donePeriod = MsOS_GetSystemTime();

      numOfPackets = _VETTXOutNumOfSendablePackets();

      if(numOfPackets > PACKETS_SEND_THRESHOLD)
        numOfPackets = PACKETS_SEND_THRESHOLD;

      if(numOfPackets < PACKETS_SEND_THRESHOLD)
      {
        if(time0 != 0)
        {
            if(!isFirstTime &&
               (MsOS_GetSystemTime() - time0 > 20))
            {
                msAPI_VE_SetTtxBuffer(_VA2PA((MS_U32)_peddingData),
                                      PEDDING_BUFFER_PAYLOAD_NUM*TTX_PACKET_SIZE);
            }
        }
        continue;
      }

      if(numOfPackets != 0)
      {
        MsOS_FlushMemory();
        msAPI_VE_SetTtxBuffer(_VA2PA((MS_U32)&_VEOutState.packets[_VEOutState.ReadIndex]),
                             numOfPackets*TTX_PACKET_SIZE);

        _VEOutState.NumOfLatestSent = numOfPackets;
        isFirstTime = FALSE;

        time0 = MsOS_GetSystemTime();
      }
    }
    else if(donePeriod != 0)
    {
      if(MsOS_GetSystemTime() - donePeriod > VE_DRIVER_TIMEOUT)
        isFirstTime = TRUE;
    }
  }
}
#else
static
void TT_VETTXOutProcess(void)
{
  MS_U32 numOfPackets;
  static MS_BOOL isFirstTime = TRUE;
  static MS_U32  time0 = 0;
  static MS_U32  donePeriod = 0;

  if(isFirstTime || (msAPI_VE_GetTtxReadDoneStatus()))
  {
    if(!isFirstTime)
        donePeriod = MsOS_GetSystemTime();

    _VETTXOutAdjustReadIndex();

    numOfPackets = _VETTXOutNumOfSendablePackets();

    //By experiment,it'd better to send 32 packets in one run
    if(numOfPackets > PACKETS_SEND_THRESHOLD)
      numOfPackets = PACKETS_SEND_THRESHOLD;

    if(numOfPackets < PACKETS_SEND_THRESHOLD)
    {
      if(time0 != 0)
      {
        //MStar VBI needs to be fed with constant data to keep it available
        if(!isFirstTime &&
           (MsOS_GetSystemTime() - time0 > 20))
        {
          msAPI_VE_SetTtxBuffer(_VA2PA((MS_U32)_peddingData),
                                PEDDING_BUFFER_PAYLOAD_NUM*TTX_PACKET_SIZE);

        }
      }
      return;
    }

    if(numOfPackets != 0)
    {
      MsOS_FlushMemory();
      msAPI_VE_SetTtxBuffer(_VA2PA((MS_U32)&_VEOutState.packets[_VEOutState.ReadIndex]),
                           numOfPackets*TTX_PACKET_SIZE);

      _VEOutState.NumOfLatestSent = numOfPackets;

      isFirstTime = FALSE;

      time0 = MsOS_GetSystemTime();
    }
  }
  else if(donePeriod != 0)
  {
    if(MsOS_GetSystemTime() - donePeriod > VE_DRIVER_TIMEOUT)
        isFirstTime = TRUE;
  }

}
#endif

TT_VETTXOut TT_VETTXOutService =
{
  .Init = TT_VETTXOutInit,
  .SendPacket = TT_VETTXOutSendPacket
};
//////////////////////////////////////////////////////////////////////////////////////

static
void _VETTXOutAdjustReadIndex(void)
{
  if(_VEOutState.NumOfLatestSent == 0)
    return;

  OS_OBTAIN_MUTEX(_SyncObj,
                  MSOS_WAIT_FOREVER);
  MS_ASSERT(_VEOutState.ReadIndex + _VEOutState.NumOfLatestSent <= MAX_PACKET_BUFFER_SIZE);

  _VEOutState.ReadIndex += _VEOutState.NumOfLatestSent;
  if(_VEOutState.ReadIndex == MAX_PACKET_BUFFER_SIZE)
    _VEOutState.ReadIndex = 0; //wrap back

  _VEOutState.NumOfLatestSent = 0;

  OS_RELEASE_MUTEX(_SyncObj);

}

static
MS_U32 _VETTXOutNumOfPackets(void)
{
  MS_S32 num;

  OS_OBTAIN_MUTEX(_SyncObj,
                  MSOS_WAIT_FOREVER);
  num = _VEOutState.WriteIndex - _VEOutState.ReadIndex;
  if(num < 0)
    num += MAX_PACKET_BUFFER_SIZE;

  OS_RELEASE_MUTEX(_SyncObj);

  return (MS_U32)num;
}

static
MS_U32 _VETTXOutNumOfSendablePackets(void)
{
  MS_S32 num = 0;

  OS_OBTAIN_MUTEX(_SyncObj,
                  MSOS_WAIT_FOREVER);

  if(_VEOutState.WriteIndex >= _VEOutState.ReadIndex)
    num = _VEOutState.WriteIndex - _VEOutState.ReadIndex;
  else
    num = MAX_PACKET_BUFFER_SIZE - _VEOutState.ReadIndex;

  OS_RELEASE_MUTEX(_SyncObj);

  //MS_ASSERT((num%16) == 0);

  return (MS_U32)num;
}

