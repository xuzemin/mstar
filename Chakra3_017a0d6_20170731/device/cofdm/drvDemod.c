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
#include <stdio.h>
#include <string.h>
#include "MsCommon.h"
//#include "HbCommon.h"
#include "Board.h"
#ifdef TWIN_TUNER
#include "drvDemod.h"
#include "drvTuner.h"
extern s_tuner* twin_tuner[2];
s_demod* twin_demod[2];
static MS_S8 DemodNum = -1;
extern void initdemod_MSDVBT_51(void);
extern s_demod*  getdemodstruct_MSDVBT_51(void);
extern void initdemod_MXL101SF(void);
extern s_demod*  getdemodstruct_MXL101SF(void);
extern DMX_FILTER_STATUS MApi_DMX_FlowSet(DMX_FLOW DmxFlow, DMX_FLOW_INPUT DmxFlowInput, MS_BOOL bClkInv, MS_BOOL bExtSync, MS_BOOL bParallel);

MS_BOOL MDrv_Demod_Init(void)
{
    MS_S8 i =0;
#if(FRONTEND_TWIN_DEMOD_TYPE&DEMOD_MSDVBT_51)
    initdemod_MSDVBT_51();
    twin_demod[i] =(s_demod*)getdemodstruct_MSDVBT_51();
    twin_demod[i]->bEnable =TRUE;
    twin_demod[i]->bispreemptive=FALSE;
    twin_demod[i]->auto_timeout = FEC_timeout;
    twin_demod[i]->manual_timeout = FEC_timeout;
    twin_demod[i]->lock_timeout= FEC_timeout;
    twin_demod[i]->i_demod = DEMOD_MSDVBT_51;
    twin_demod[i]->demod_dmx_input = (DEMOD_MSDVBT_51 == FRONTEND_DEMOD_TYPE) ? DMX_INPUT : DMX_INPUT2;
    ++i;
#endif
#if(FRONTEND_TWIN_DEMOD_TYPE&DEMOD_MXL101SF)
    initdemod_MXL101SF();
    twin_demod[i] =(s_demod*)getdemodstruct_MXL101SF();
    twin_demod[i]->bEnable =TRUE;
    twin_demod[i]->bispreemptive=FALSE;
    twin_demod[i]->auto_timeout = 2000;
    twin_demod[i]->manual_timeout = 600;
    twin_demod[i]->lock_timeout= 2000;
    twin_demod[i]->i_demod= DEMOD_MXL101SF;
    twin_demod[i]->demod_dmx_input = (DEMOD_MXL101SF == FRONTEND_DEMOD_TYPE) ? DMX_INPUT : DMX_INPUT2;
    ++i;
#endif

    if(i>2)
    {
        printf("errror\n");
        return FALSE;
    }
    DemodNum = i-1;
    for(i=i-1; i>=0; i--)
    {
        if(twin_demod[i]->demod_init()== FALSE)
            return FALSE;
    }
    if(i !=0)
    {
        twin_demod[0]->bispreemptive = TRUE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_Open(void)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_open())
            return TRUE;
    }
    return FALSE;
}

MS_BOOL MDrv_Demod_Close(void)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_close()== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_Reset(void)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_reset()== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_TsOut(MS_BOOL bEnable)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_tsout(bEnable)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_PowerOnOff(MS_BOOL bPowerOn)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        twin_demod[i]->demod_poweronoff(bPowerOn);
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_SetBW(MS_U32 u32BW)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_setbw(u32BW)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_GetBW(MS_U32 *pu32BW)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_getbw(pu32BW)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetLock(MS_BOOL *pbLock,MS_U8 i_dmd)
{
    if(twin_demod[i_dmd]->demod_getlock(pbLock)== FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetSNR(MS_U32 *pu32SNR)
{

    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_getsnr(pu32SNR)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_GetBER(float *pfBER)
{

    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_getber(pfBER)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetPWR(MS_S32 *ps32Signal)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_getpwr(ps32Signal)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_Config(MS_U8 *pRegParam)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_config(pRegParam)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_GetParam(DEMOD_MS_FE_CARRIER_PARAM* pParam)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_getparam(pParam)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_SetMode(Demod_Mode* pMode)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_setmode(pMode)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_SetOutoutPath(DEMOD_INTERFACE_MODE path)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_setoutoutpath(path)== FALSE)
            return FALSE;
    }
    return TRUE;
}
DEMOD_INTERFACE_MODE MDrv_Demod_GetOutoutPath(void)
{
    DEMOD_INTERFACE_MODE ret = DEMOD_INTERFACE_PARALLEL;
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        ret=twin_demod[i]->demod_getoutoutpath();
    }
    return ret;
}

MS_BOOL MDrv_Demod_I2C_ByPass(MS_BOOL bOn)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_i2c_bypass(bOn)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_SetTsSerial(MS_BOOL bSerial)
{

    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if(twin_demod[i]->demod_settsserial(bSerial)== FALSE)
            return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_Restart_Type(DEMOD_MS_FE_CARRIER_PARAM* pParam,DEMOD_EN_FE_TUNE_MODE eMode, MS_U8 i_demod)
{
    if (twin_demod[i_demod]->demod_restart_type(pParam,eMode,i_demod) == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_GetMaxLockTime(DEMOD_EN_FE_TUNE_MODE eMode, MS_U32 *u32LockTime)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(!twin_demod[i]->bEnable||!twin_demod[i]->bispreemptive)
            continue;
        if (DEMOD_FE_TUNE_AUTO == eMode)
        {
            *u32LockTime =  twin_demod[i]->auto_timeout;
        }
        else
        {
            *u32LockTime =  twin_demod[i]->manual_timeout;
        }
    }
    return TRUE;
}

MS_BOOL MDrv_Demod_GetSignalQuality(MS_U16*quality)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if (!(twin_demod[i]->bEnable)||!(twin_demod[i]->bispreemptive))
            continue;
        if (twin_demod[i]->demod_getsignalquality(quality) == FALSE)
        {
            return FALSE;
        }
    }
    return TRUE;
}

DMX_FLOW_INPUT  MDrv_Demod_GetDMXInputType_Play(void)
{
    MS_S8 i = DemodNum;
    DMX_FLOW_INPUT  dmx_input_type = DMX_INPUT;
    for(; i>=0; i--)
    {
        if (!(twin_demod[i]->bEnable)||!(twin_demod[i]->bispreemptive))
            continue;
        dmx_input_type = twin_demod[i]->demod_dmx_input;
    }
    return dmx_input_type;
}

DMX_FLOW_INPUT  MDrv_Demod_GetDMXInputType_Record(MS_U8* i_demod)
{
    MS_S8 i = DemodNum;
    DMX_FLOW_INPUT  dmx_input_type = DMX_INPUT;
    for(; i>=0; i--)
    {
        if ((twin_demod[i]->bEnable)&&(!twin_demod[i]->bispreemptive))
        {
            if(twin_demod[i]->dmd_lock_status==TRUE)
            {
                dmx_input_type = twin_demod[i]->demod_dmx_input;
                *i_demod = i;
            }
            else
            {
                dmx_input_type=MDrv_Demod_GetDMXInputType_Play();
                *i_demod = DemodNum-i;
            }
        }
    }
    return dmx_input_type;
}

void MDrv_Demod_Change_Demod(void)
{
    if((twin_tuner[0]->bEnable == TRUE) && (twin_tuner[1]->bEnable == TRUE)        \
         && (twin_demod[0]->bEnable == TRUE) && (twin_demod[1]->bEnable == TRUE))
    {
        MS_BOOL t_temp, d_temp;
        t_temp = twin_tuner[0]->bispreemptive;
        twin_tuner[0]->bispreemptive = !t_temp;
        twin_tuner[1]->bispreemptive = t_temp;
        d_temp = twin_demod[0]->bispreemptive;
        twin_demod[0]->bispreemptive = !d_temp;
        twin_demod[1]->bispreemptive = d_temp;
    }
    int i = 0;
    for(; i<2; i++)
    {
        if(!(twin_demod[i]->bEnable == TRUE)||!(twin_demod[i]->bispreemptive == TRUE))
            continue;
        MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, twin_demod[i]->demod_dmx_input, FALSE, TRUE, TS_PARALLEL_OUTPUT);

    }
}

MS_S8 MDrv_Demod_Get_DemodNum(void)
{
    return DemodNum;
}

MS_S8 MDrv_Demod_Get_PreemtiveDMD_Index(void)
{
    MS_S8 i = DemodNum;
    for(; i>=0; i--)
    {
        if(twin_demod[i]->bEnable && twin_demod[i]->bispreemptive)
        {
            return i;
        }
    }
    HB_ASSERT(i>=0);
    return -1;
}

void MDrv_Demod_SetLockStatus(MS_BOOL block,MS_U8 i_dmd)
{
    twin_demod[i_dmd]->dmd_lock_status=block;
}

MS_BOOL MDrv_Demod_GetLockStatus(MS_U8 i_dmd)
{
    return twin_demod[i_dmd]->dmd_lock_status;
}

MS_S16 MDrv_Demod_GetLockTime(MS_U8 i_dmd)
{
    return twin_demod[i_dmd]->lock_timeout;
}

#endif
