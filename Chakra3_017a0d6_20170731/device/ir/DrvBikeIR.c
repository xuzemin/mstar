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
#include "datatype.h"
#include "msIR.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#ifndef DRVBIKEIR_C
#define DRVBIKEIR_C
#include "include/DrvBikeIR.h"

#define IR_NEC_INTERVAL 108
#define IR_NEC_TIMEOUT  120
static U32 gIRTimeCount = 0;
//#if !(IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
static U8 girmodebk[2];
static BOOLEAN bEnableBKGameMode=FALSE;
//#endif

void MSDrv_GetValFromIRBuf(BYTE *buf,ST_BK_IR_VALUE *st_ir_val)
{
    //U32 *u32tmp;
    //u32tmp = (U32 *)buf;
    //st_ir_val->u8keypad=(U8)((*u32tmp&BKIR_KEYPAD)>>BKIR_KEYPAD_PS);
    //st_ir_val->u8lefrgt=(U8)((*u32tmp&BKIR_LEFT_RIGHT)>>BKIR_LEFT_RIGHT_PS);
    //st_ir_val->u8speed=(U8)((*u32tmp&BKIR_SPEED)>>BKIR_SPEED_PS);
    //st_ir_val->u8hrtbt=(U8)((*u32tmp&BKIR_HEARTBEAT)>>BKIR_HEARTBEAT_PS);

    if(buf[3]&FLAG_BITS)
    {
        st_ir_val->bflag = TRUE;
        st_ir_val->u8speed_hrtbt= (buf[2]&0xfc)>>2;
    }
    else
    {
        st_ir_val->bflag = FALSE;
        st_ir_val->u8speed_hrtbt = buf[2];
    }

    st_ir_val->u8keypad=(buf[3]&BKIR_KEYPAD)>>5;
    st_ir_val->u8lefrgt=((buf[3]&BKIR_LEFT_RIGHT)>>2);
    st_ir_val->bfreshkey=TRUE;
}

BOOLEAN bMSDrv_GetBKGameMode(void)
{
    return bEnableBKGameMode;
}

void MSDrv_BKIR_Init(void)
{
    #if (IR_MODE_SEL != IR_TYPE_FULLDECODE_MODE)
    return;
    #else
    gIRTimeCount = 0;
    g_stBKIRKey.bfreshkey=FALSE;
    g_stBKIRKey.bflag=FALSE;
    g_stBKIRKey.u8keypad=0;
    g_stBKIRKey.u8lefrgt=0;
    g_stBKIRKey.u8speed_hrtbt=0;
    bEnableBKGameMode=TRUE;
    g_stRmInput.u8ir=0;
    g_stRmInput.u8repeat=0;
    girmodebk[0]=msIR_ReadByte(IR_FIFO_CTRL);
    girmodebk[1]=msIR_ReadByte(IR_GLHRM_NUM_H);
    //#if !(IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
    //girmodebk[0]=msIR_ReadByte(IR_FIFO_CTRL);     // {2'b0,IR_SHOT_SEL[1:0],IR_FIFO_FULL_EN,FIFO_DEPTH[2:0]}
    //girmodebk[1]=msIR_ReadByte(IR_GLHRM_NUM_H);     // {2'b0,IR_SHOT_SEL[1:0],IR_FIFO_FULL_EN,FIFO_DEPTH[2:0]}
    //#endif

    ////switch to full decode mode
    //msIR_WriteByte(IR_FIFO_CTRL, 0x0F);     // {2'b0,IR_SHOT_SEL[1:0],IR_FIFO_FULL_EN,FIFO_DEPTH[2:0]}
    //msIR_WriteByte(IR_GLHRM_NUM_H, 0x38);   // {IR_DECOMODE[1:0], GLHRM_EN,GLHRM_NUM[10:8]}

    //switch to raw decode mode
    msIR_WriteByte(IR_FIFO_CTRL, 0x0F);
    msIR_WriteByte(IR_GLHRM_NUM_H, 0x28);
    printf("init bike ir\n");
    #endif
}

void MSDrv_BKIR_Final(void)
{
    //#if !(IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
    //switch back to original mod
    //msIR_WriteByte(IR_FIFO_CTRL, girmodebk[0]);     // {2'b0,IR_SHOT_SEL[1:0],IR_FIFO_FULL_EN,FIFO_DEPTH[2:0]}
    //msIR_WriteByte(IR_GLHRM_NUM_H, girmodebk[1]);   // {IR_DECOMODE[1:0], GLHRM_EN,GLHRM_NUM[10:8]}
    //#endif

    #if (IR_MODE_SEL != IR_TYPE_FULLDECODE_MODE)
    return;
    #else
    bEnableBKGameMode=FALSE;
    msIR_WriteByte(IR_FIFO_CTRL, girmodebk[0]);
    msIR_WriteByte(IR_GLHRM_NUM_H, girmodebk[1]);
    printf("final bike ir\n");
    #endif
}

extern U8 msIR_GetIrKeyData( void );
U8 MSDrv_Polling_BKIR_Input(void)
{
    #if (IR_MODE_SEL != IR_TYPE_FULLDECODE_MODE)
    return MSRET_OK;
    #else
    U8 i,k=0;
    U8 key,repeat;
    static U8 prev_key=0,rep_counter=0;
    static U32 u32_IRtimerCounter=0,u32_IRtimeout=0;

    //===========================================================
    if (MsOS_Timer_DiffTimeFromNow((u32_IRtimerCounter) >= IR_NEC_INTERVAL*2)
        u32_IRtimerCounter = MsOS_GetSystemTime();
    else
        return MSRET_ERROR;

    //================================================================
    if((msIR_ReadByte(IR_RPT_FIFOEMPTY) & 0x2))
    {
        return MSRET_ERROR;
    }
    else
    {
        for ( i=0; i<BKIR_LENGTH; i++ )
        {

            if ( msIR_ReadByte(IR_RPT_FIFOEMPTY) & 0x2 )
                break;

            g_bIRbuf[k++] = msIR_GetIrKeyData();
            //MsOS_DelayTask(3);
        }

        //if(i!=BKIR_LENGTH)
        //    return MSRET_ERROR;
        //for( i=0;i<k;i++)
        //    printf("bike IR input 0x%x\n",g_bIRbuf[i]);

        if(g_bIRbuf[0]==IR_HEADER_CODE0&&g_bIRbuf[1]==IR_HEADER_CODE1)
        {//remote input
            MsOS_DelayTask(1);
            repeat=msIR_ReadByte(IR_RPT_FIFOEMPTY) & 0x1;
            key=g_bIRbuf[2];
            //printf("\n current IrKey=%x,%x\n",key,repeat);
            if ( ( MsOS_Timer_DiffTimeFromNow( u32_IRtimeout ) >= IR_NEC_TIMEOUT ) && ( u32_IRtimeout != 0xffffffff ) )
            {
                u32_IRtimeout = 0xffffffff;
                msIR_Clear_FIFO();
                if( repeat== 1 && (prev_key == key))
                {
                    printf("repeat code err\n");
                    return MSRET_ERROR;
                }
            }

            if (repeat==0||prev_key != key)
            {
                rep_counter = 0;
                prev_key = key;
                g_stRmInput.u8ir=key;
                g_stRmInput.u8repeat=0;
                g_stBKIRKey.bfreshkey=FALSE;

                printf("\n IrKey=%x,%x\n",prev_key,repeat);

                return MSRET_OK;
            }
            else
            {
                rep_counter++;
                if (rep_counter >= IR_FILTER_REPEAT_NUM)
                {
                    printf("\n REPET=%x,%x\n",prev_key,repeat);
                    prev_key = key;
                    g_stRmInput.u8ir=key;
                    g_stRmInput.u8repeat=1;
                    g_stBKIRKey.bfreshkey=FALSE;
                    return MSRET_OK;
                }
            }
        }
        else if(g_bIRbuf[0]==BIKE_IR_HEADER_CODE0&&g_bIRbuf[1]==BIKE_IR_HEADER_CODE1)
        {//bike ir input
            MSDrv_GetValFromIRBuf(g_bIRbuf,&g_stBKIRKey);
            printf("keypad 0x%x,left or right 0x%x,%s 0x%x\n",g_stBKIRKey.u8keypad,g_stBKIRKey.u8lefrgt,(g_stBKIRKey.bflag?"speed":"heartbeat"),g_stBKIRKey.u8speed_hrtbt);
        }
    }

    return MSRET_OK;
    #endif
}

#undef DRVBIKEIR_C
#endif
