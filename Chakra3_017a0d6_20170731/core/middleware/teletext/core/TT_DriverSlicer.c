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
 * MODULE     : TT_DriverSlicer
 * FILE       : TT_DriverSlicer.c
 * COPYRIGHT  : TARA Systems GmbH
 * DESCRIPTION:
 *   Teletext driver for slicer
 *
 * REMARK:
 *   This file contains Intellectual Property and must NEVER be released.
 ***********************************************************************/

/***********************************************************************
 * SECTION: #include
 ***********************************************************************/

#include "TT_DriverSlicer.h"
#include "MsTypes.h"
#include "drvVBI.h"
#include "drvDMX_TTX.h"
#include "apiDMX.h"
#include "datatype.h"
#include "TT_API25.h"
#include "debug.h"


/***********************************************************************
 * SECTION: #define
 ***********************************************************************/

#ifdef MSOS_TYPE_LINUX
#define PACKET_ACQ_TASK_STACK_SIZE  0x30000
#define WORKING_TASK_NORMAL_PERIOD  30
#else
#define WORKING_TASK_NORMAL_PERIOD  4
#endif

#define WORKING_TASK_URGENT_PERIOD  1

typedef enum
{
  SLICER_STATE_ACTIVE,
  SLICER_STATE_INACTIVE
}TT_SlicerState;
/***********************************************************************
 * SECTION: Declaration of private functions
 ***********************************************************************/
PRIVATE TT_DRIVER_SLICER_SOURCE _eSlicerSource = TT_DRIVER_SLICER_ATV;
PRIVATE TT_U8 _bEnableTTX_Acquire = FALSE;
PRIVATE MS_S32 _SlicerSyncMutex = 0;
PRIVATE TT_BOOL _doesHaltInputCommand;
PRIVATE TT_SlicerState _SlicerState = SLICER_STATE_INACTIVE;

#ifdef MSOS_TYPE_LINUX
PRIVATE MS_U8 _PacketAcqTaskStack[PACKET_ACQ_TASK_STACK_SIZE];
PRIVATE MS_U32 _SlickerTaskAlarm;
PRIVATE MS_S32 _PacketAcqTaskID = 0;
#else
PRIVATE TT_BOOL _isWorking = FALSE;
#endif
PRIVATE MS_U32 _wakeupPeriod = WORKING_TASK_NORMAL_PERIOD;



PRIVATE void Task_SIGNALSlicer( void );

PRIVATE TT_BOOL _SlicerFreezeSourceInput(void);

PRIVATE void _SlicerThawSourceInput(void);

PRIVATE TT_BOOL _SlicerIsSourceInputFrozen(void);
PRIVATE TT_SlicerState _SlicerGetState(void);
PRIVATE void _SlicerEnterState(TT_SlicerState state);
PRIVATE void _BeforeDigestInput(TT_BOOL* doesApproved,
                                TT_U32* maxNumPacketsApproved);
PRIVATE void _AfterDigestInput(TT_BOOL);

/***********************************************************************
 * SECTION: Definition of public functions
 ***********************************************************************/
/***********************************************************************
 * FUNCTION:
 *
 * DESCRIPTION:
 *
 * PARAMETERS:
 *
 * RETURN:
 ***********************************************************************/
PUBLIC TT_BOOL
  TT_DriverSlicerCreate(void)
{
#ifdef MSOS_TYPE_LINUX
  if(_PacketAcqTaskID == 0)
  {
    void TT_SlicerTask(MS_U32 argc, void* argv);

    _PacketAcqTaskID =
      MsOS_CreateTask((TaskEntry)TT_SlicerTask,
                      0U,
                      E_TASK_PRI_MEDIUM,
                      TRUE,
                      _PacketAcqTaskStack,
                      PACKET_ACQ_TASK_STACK_SIZE,
                      "TTX Slicer Task");
    MS_ASSERT(_PacketAcqTaskID > 0);
 }
#endif

  if(_SlicerSyncMutex == 0)
  {
    _SlicerSyncMutex = OS_CREATE_MUTEX(SlicerSyncMutex);
    MS_ASSERT(_SlicerSyncMutex > 0);
  }

  TT_EngineObj.SetupEventHandler(EVENT_HANDLER_ASK_FREEZE_SOURCE_INPUT,
                                 _SlicerFreezeSourceInput);

  TT_EngineObj.SetupEventHandler(EVENT_HANDLER_ASK_THAW_SOURCE_INPUT,
                                 _SlicerThawSourceInput);

  TT_EngineObj.SetupEventHandler(EVENT_HANDLER_BEFORE_DIGEST_INPUT,
                                 _BeforeDigestInput);

  TT_EngineObj.SetupEventHandler(EVENT_HANDLER_AFTER_DIGEST_INPUT,
                                 _AfterDigestInput);

  while(_SlicerGetState() == SLICER_STATE_ACTIVE)
    MsOS_DelayTask(30);

  _SlicerEnterState(SLICER_STATE_INACTIVE);

  return True;
}

/***********************************************************************
 * FUNCTION:
 *
 * DESCRIPTION:
 *
 * PARAMETERS:
 *
 * RETURN:
 ***********************************************************************/
PUBLIC TT_BOOL
  TT_DriverSlicerOpen
  (
  char *cEprFile          /* name of EPR file */
  )
{
    cEprFile = cEprFile;

  return True;
}

PUBLIC void
  TT_DriverSlicerClose(void)
{
}

PUBLIC void
  TT_DriverSlicerProcess(void)
{

  if(_bEnableTTX_Acquire)
  {
    Task_SIGNALSlicer();
  }
}

/***********************************************************************
 * SECTION: Definition of private functions
 ***********************************************************************/


/***********************************************************************
 * FUNCTION:
 *
 * DESCRIPTION:
 *
 * PARAMETERS:
 *
 * RETURN:
 ***********************************************************************/

PRIVATE
void Task_SIGNALSlicer( void )
{
	void TT_DecoderInputPackets(void);
	//TT_DecoderSetACQEndCondition(TT_AcqExecuteProcessing());
	//Digest packets and store them into the internal database
	TT_DecoderInputPackets();
}

#ifdef MSOS_TYPE_LINUX
PUBLIC void TT_SlicerTask(MS_U32 argc, void* argv)
{
  _SlickerTaskAlarm =
    MsOS_CreateSemaphore(0,
                         E_MSOS_FIFO,
                         "TT_SLICER_TASK_OBJ");
  MS_ASSERT(_SlickerTaskAlarm > 0);



  UNUSED(argc);
  UNUSED(argv);
  while(TRUE)
  {
    MsOS_ObtainSemaphore(_SlickerTaskAlarm, _wakeupPeriod);

    if(!_SlicerIsSourceInputFrozen())
    {
      if(TT_DriverSlicer_IsAcquireEnabled())
      {
        _SlicerEnterState(SLICER_STATE_ACTIVE);
        TT_DriverSlicerProcess();
      }
      _wakeupPeriod = WORKING_TASK_NORMAL_PERIOD;
    }
    else
    {
        _wakeupPeriod = _wakeupPeriod / 2;
        if(_wakeupPeriod == 0)
            _wakeupPeriod = 1;
    }

    _SlicerEnterState(SLICER_STATE_INACTIVE);
  }
}

#else
PUBLIC void TT_DriverSlicer_AcquireInISR(void)
{
  if(_SlicerIsSourceInputFrozen())
  {
    _wakeupPeriod = 0;

    return;
  }

  if(!TT_DriverSlicer_IsAcquireEnabled())
    return;

  _SlicerEnterState(SLICER_STATE_ACTIVE);
  _isWorking = TRUE;
  if(_wakeupPeriod > 0)
    _wakeupPeriod--;
  if(_wakeupPeriod == 0)
  {
    TT_DriverSlicerProcess();
  }

  _isWorking = FALSE;
  _SlicerEnterState(SLICER_STATE_INACTIVE);
}

#endif

PRIVATE
TT_BOOL  _SlicerFreezeSourceInput()
{
  OS_OBTAIN_MUTEX(_SlicerSyncMutex,
                  MSOS_WAIT_FOREVER);
  _doesHaltInputCommand = TRUE;
  OS_RELEASE_MUTEX(_SlicerSyncMutex);

  while(SLICER_STATE_INACTIVE != _SlicerGetState())
  {
    MsOS_DelayTask(1);
#ifndef MSOS_TYPE_LINUX
    if(_isWorking == TRUE)
    {
        MS_DEBUG_MSG(printf("%s,%d: This should not happen in nos environment\n", __FUNCTION__, __LINE__));
    }
#endif
  }
  return TRUE;
}


PRIVATE
void _SlicerThawSourceInput(void)
{
  OS_OBTAIN_MUTEX(_SlicerSyncMutex,
                  MSOS_WAIT_FOREVER);
  _doesHaltInputCommand = FALSE;
  OS_RELEASE_MUTEX(_SlicerSyncMutex);

}

PRIVATE
TT_BOOL _SlicerIsSourceInputFrozen(void)
{
  TT_BOOL result;
  OS_OBTAIN_MUTEX(_SlicerSyncMutex,
                  MSOS_WAIT_FOREVER);
  result = _doesHaltInputCommand;
  OS_RELEASE_MUTEX(_SlicerSyncMutex);

  return result;
}

PRIVATE
void _SlicerEnterState(TT_SlicerState state)
{
  OS_OBTAIN_MUTEX(_SlicerSyncMutex,
                  MSOS_WAIT_FOREVER);
  _SlicerState = state;
  OS_RELEASE_MUTEX(_SlicerSyncMutex);
}

PRIVATE
TT_SlicerState _SlicerGetState(void)
{
  return _SlicerState;
}

PRIVATE
void _BeforeDigestInput(TT_BOOL* doesApproved,
                        TT_U32* maxNumPacketsApproved)
{
    DMX_FILTER_STATUS ret;
    *doesApproved = TRUE;
#ifdef MSOS_TYPE_LINUX
    *maxNumPacketsApproved = 0;
#else
    *maxNumPacketsApproved = WORKING_TASK_NORMAL_PERIOD + 2;
#endif
    if(TT_DRIVER_SLICER_DTV == TT_DriverSlicer_Get_CurrentSource())
    {
        ret = MApi_DMX_GetAccess(3);
        if(ret == DMX_FILTER_STATUS_ERROR)
        {
            _wakeupPeriod = WORKING_TASK_URGENT_PERIOD;

            *doesApproved = FALSE;
        }
        else
        {
            _wakeupPeriod = WORKING_TASK_NORMAL_PERIOD;
        }
    }

}

//This is called when _BeforeDigestInput() is successful.
PRIVATE
void _AfterDigestInput(TT_BOOL thereAreUnhandledPackets)
{
    if(TT_DRIVER_SLICER_DTV == TT_DriverSlicer_Get_CurrentSource())
    {
        MApi_DMX_ReleaseAccess();
    }

    if(thereAreUnhandledPackets)
        _wakeupPeriod = WORKING_TASK_URGENT_PERIOD;
    else if(_wakeupPeriod != WORKING_TASK_URGENT_PERIOD)
       _wakeupPeriod = WORKING_TASK_NORMAL_PERIOD;
}

/***********************************************************************
 * FUNCTION:
 *
 * DESCRIPTION:
 *
 * PARAMETERS:
 *
 * RETURN:
 ***********************************************************************/

PUBLIC void TT_DriverSlicer_SetParameter( TT_U32 u32DramStartAddr,TT_U16 u16VBIBufferCount )
{
#ifndef TTX_ATV_DISABLE
    MDrv_VBI_InitializeTTXSlicer(u32DramStartAddr, u16VBIBufferCount);
#endif
    MDrv_DMX_TTX_Init(u32DramStartAddr, u16VBIBufferCount);
}

PUBLIC void TT_DriverSlicer_Set_Source (TT_DRIVER_SLICER_SOURCE eSource)
{
    _eSlicerSource = eSource;
}

PUBLIC TT_DRIVER_SLICER_SOURCE TT_DriverSlicer_Get_CurrentSource(void)
{
    return _eSlicerSource;
}

PUBLIC void TT_DriverSlicer_AcquireEnable(TT_U8 enable)
{
    _bEnableTTX_Acquire = enable;
}

PUBLIC TT_U8 TT_DriverSlicer_IsAcquireEnabled(void)
{
    return _bEnableTTX_Acquire;
}


