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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_vbi.h
/// @brief API for Getting VBI Data from VBI Slicer
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_VE_C

/******************************************************************************/
/*               Header Files                                                 */
/******************************************************************************/
#include <string.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "sysinfo.h"
#include "msAPI_VD.h"

#include "msAPI_VE.h"
#include "drvTVEncoder.h"
#include "apiXC_Sys.h"

#define N_OFFSET                266 // NTSC_EVEN_FIELD_OFFSET
#define P_OFFSET                313 // PAL_EVEN_FIELD_OFFSET

//==============================================================================
/*                    Local                                                     */
//==============================================================================
#define VIDEO_TYPE_CNT          5
#define LINE_RANGE_CNT          4

static U16 ve_video_table[VIDEO_TYPE_CNT][LINE_RANGE_CNT + 1] = {
    // type         odd_start,  odd_end,            even_start,     even_end
    {SIG_NTSC,      0x15,       0x12+N_OFFSET,      0x15,           0x12+N_OFFSET },  // NTSC
    {SIG_PAL_M,     0x15,       0x12+P_OFFSET,      0x15,           0x12+P_OFFSET },  // PAL-M
    {SIG_PAL_NC,    0x15,       0x12+P_OFFSET,      0x15,           0x12+P_OFFSET },  // PAL-NC
    {SIG_NTSC_443,  0x15,       0x12+N_OFFSET,      0x15,           0x12+N_OFFSET },  // NTSC-443, PAL-60
    {SIG_PAL,       0x18,       0x15+P_OFFSET,      0x18,           0x15+P_OFFSET },  // PAL
};

static stVEData_BufferControl veOddControl, veEvenControl;

static BOOL bIsOddField=FALSE;         // True: odd
static BOOL bIsEvenField=FALSE;        // True: even
static BOOL bIsSent=TRUE;
static BOOL bCcRun = FALSE;

/********************************************************************************/
/*                    Functions                                                 */
/********************************************************************************/

void msAPI_VE_Send(void)
{
    if(bCcRun)
    {
        if(!bIsSent)
        {
            if(bIsEvenField)
            {
                //printf("\n s e, w=%d, r=%d", veOddControl.u8WrittenCnt, veOddControl.u8ReadCnt);
                if((veEvenControl.u8WrittenCnt%VE_FIFO_DEEP) == veEvenControl.u8ReadCnt)
                    MDrv_VE_SendCcData(FALSE, VBI_CC_NULL_PACKET);
                else
                    MDrv_VE_SendCcData(FALSE, veEvenControl.data[veEvenControl.u8ReadCnt++]);

                if(veEvenControl.u8ReadCnt >= VE_FIFO_DEEP)
                    veEvenControl.u8ReadCnt = 0;
            }
            else if(bIsOddField)
            {
                //printf("\n s o, w=%d, r=%d", veOddControl.u8WrittenCnt, veOddControl.u8ReadCnt);
                if((veOddControl.u8WrittenCnt%VE_FIFO_DEEP) == veOddControl.u8ReadCnt)
                    MDrv_VE_SendCcData(TRUE, VBI_CC_NULL_PACKET);
                else
                    MDrv_VE_SendCcData(TRUE, veOddControl.data[veOddControl.u8ReadCnt++]);

                if(veOddControl.u8ReadCnt >= VE_FIFO_DEEP)
                    veOddControl.u8ReadCnt = 0;
            }

            bIsSent = TRUE;
        }
    }
}

static void msAPI_VE_FieldIsr(void)            // even field
{
    bIsEvenField = TRUE;
    bIsOddField = FALSE;
    bIsSent = FALSE;
    msAPI_VE_Send();

    MsOS_EnableInterrupt(E_INT_FIQ_FIELD_VE4VBI);
}

static void msAPI_VE_VsyncIsr(void)
{
    if(bIsEvenField)                                // odd field
    {
        bIsOddField = TRUE;
        bIsEvenField = FALSE;
        bIsSent = FALSE;
    }
    msAPI_VE_Send();

    MsOS_EnableInterrupt(E_INT_FIQ_VSYNC_VE4VBI);
}

/******************************************************************************/
// API for VBI Slicer Initialization::
// Initializing VBI Slicer HW
/******************************************************************************/
void msAPI_VE_Init(void)
{
    U8 i=0;

    // initialize variables
    veOddControl.u8ReadCnt = veOddControl.u8WrittenCnt = 0;
    memset((U8 *)veOddControl.data, 0x00, sizeof(U16)*VE_FIFO_DEEP);
    veEvenControl.u8ReadCnt = veEvenControl.u8WrittenCnt = 0;
    memset((U8 *)veEvenControl.data, 0x00, sizeof(U16)*VE_FIFO_DEEP);

    // init
    MDrv_VE_Init(((VE_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VE_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VE_FRAMEBUFFER_ADR)));
    msAPI_Scaler_SetVE(INPUT_SOURCE_DTV, OUTPUT_CVBS2);

    // for even field
    MsOS_AttachInterrupt(E_INT_FIQ_FIELD_VE4VBI, (InterruptCb)msAPI_VE_FieldIsr);
    MsOS_EnableInterrupt(E_INT_FIQ_FIELD_VE4VBI);

    // for odd field
    MsOS_AttachInterrupt(E_INT_FIQ_VSYNC_VE4VBI, (InterruptCb)msAPI_VE_VsyncIsr);
    MsOS_EnableInterrupt(E_INT_FIQ_VSYNC_VE4VBI);

    // switch on
    for(i=0; i<VIDEO_TYPE_CNT; i++) // assume NTSC now, and get the ve table index
    {
        if(ve_video_table[i][0] == SIG_NTSC) break;
    }
    if(i == VIDEO_TYPE_CNT) i = 0;  // NTSC
    MDrv_VE_SetCcRange(ve_video_table[i][1], ve_video_table[i][2], ve_video_table[i][3], ve_video_table[i][4]);

    MDrv_VE_EnableCcSw(TRUE);
}

void msAPI_VE_Close(void)
{
    // turn off VE
    MDrv_VE_Exit();

    // switch off
    MDrv_VE_EnableCcSw(FALSE);

    // even field
    MsOS_DisableInterrupt(E_INT_FIQ_FIELD_VE4VBI);
    MsOS_DetachInterrupt(E_INT_FIQ_FIELD_VE4VBI);

    // odd field
    MsOS_DisableInterrupt(E_INT_FIQ_VSYNC_VE4VBI);
    MsOS_DetachInterrupt(E_INT_FIQ_VSYNC_VE4VBI);
}

void msAPI_VE_Write(MS_BOOL bIsOdd, MS_U16 data)
{
    if(bCcRun)
    {
        if(bIsOdd)
        {
            if(veOddControl.u8WrittenCnt >= VE_FIFO_DEEP)
                veOddControl.u8WrittenCnt = 0;
            //printf("\n w, o, 0x%x, cnt=%d", data, veEvenControl.u8WrittenCnt);
            veOddControl.data[veOddControl.u8WrittenCnt++] = data;
        }
        else
        {
            if(veEvenControl.u8WrittenCnt >= VE_FIFO_DEEP)
                veEvenControl.u8WrittenCnt = 0;
            //printf("\n w, e, 0x%x, cnt=%d", data, veEvenControl.u8WrittenCnt);
            veEvenControl.data[veEvenControl.u8WrittenCnt++] = data;
        }
    }
}

void msAPI_VE_EnableCC(MS_BOOL bIsRun)
{
    if(bIsRun)
        bCcRun = TRUE;
    else
        bCcRun = FALSE;
}

#if 0 // testing for inserting VE
static MS_U8 test_cc1[] =
{
    0xb9, 0x20, 0x20, 0x80, 0x94, 0xad, 0x94, 0xad,
    0x94, 0x2c, 0x94, 0x2c, 0x94, 0xae, 0x94, 0xae,
    0x94, 0x2f, 0x94, 0x2f, 0x94, 0xa7, 0x94, 0xa7,
    0x13, 0x46, 0x13, 0x46, 0x10, 0xa4, 0x10, 0xa4,
    0x20, 0xc1, 0xc2, 0x43, 0xc4, 0x45, 0x46, 0xc7,
    0xc8, 0x49, 0x4a, 0xcb, 0x4c, 0xcd, 0xce, 0x4f,
    0xd0, 0x51, 0x52, 0xd3, 0x54, 0xd5, 0xd6, 0x57,
};

static MS_U8 test_cc3[] =
{
    0xb9, 0x20, 0x20, 0x80, 0x94, 0xad, 0x94, 0xad,
    0x94, 0x2c, 0x94, 0x2c, 0x94, 0xae, 0x94, 0xae,
    0x94, 0x2f, 0x94, 0x2f, 0x94, 0xa7, 0x94, 0xa7,
    0x13, 0x46, 0x13, 0x46, 0x10, 0xa4, 0x10, 0xa4,
    0x20, 0xc1, 0xc2, 0x43, 0xc4, 0x45, 0x46, 0xc7,
    0xc8, 0x49, 0x4a, 0xcb, 0x4c, 0xcd, 0xce, 0x4f,
    0xd0, 0x51, 0x52, 0xd3, 0x54, 0xd5, 0xd6, 0x57,
};

static MS_U32 cc1_size=0, cc3_size=0;
static MS_U32 cc1_cnt=0, cc3_cnt=0;

void msAPI_VE_UniTest(void)
{
    if(u32VETime == 0)
    {
        u32VETime = u32TimeStamp = msAPI_Timer_GetTime0();
    }

    // Wait 20 sec, then start to test...
    if((!u8VEFlag) && ((msAPI_Timer_GetTime0()-u32VETime) > 20000))
    {
        printf("\n VE unitest start\n");
        u8VEFlag = TRUE;
    }

    if(u8VEFlag)
    {
        extern void Hal_VE_SendCcData(MS_BOOL, MS_U16);
        MS_U16 data;

        if(cc1_size == 0)
        {
            cc1_size = sizeof(test_cc1);
            cc3_size = sizeof(test_cc3);
        }

        if(!bIsSent)
        {
            if(bIsOddField)
            {
                data = test_cc1[cc1_cnt%cc1_size] | ((MS_U16)test_cc1[(cc1_cnt+1)%cc1_size]<<8);
                Hal_VE_SendCcData(TRUE, data);
                cc1_cnt += 2;
            }
            else if(bIsEvenField)
            {
                data = test_cc3[cc3_cnt%cc3_size] | ((MS_U16)test_cc3[(cc3_cnt+1)%cc3_size]<<8);
                Hal_VE_SendCcData(FALSE, data);
                cc3_cnt += 2;
            }

            bIsSent = TRUE;
        }

        u32VETime = msAPI_Timer_GetTime0();
    }
}

#endif

#undef MSAPI_VE_C


