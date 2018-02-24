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
#define MAPP_CADTVPROC_C

#include "Board.h"
#include "MApp_CADTV_Proc.h"
#include "msAPI_Global.h"
#include "drvAUDIO.h"

static U32 _u32CadtvManualTuningFrequency = DEFAULT_DVBC_FREQUENCY;
static U16 _u16CadtvManualTuningSymbo = DEFAULT_DVBC_SYMBOL_RATE;
static EN_CAB_CONSTEL_TYPE _enCadtvManualTuningQamType= CAB_QAM16;
static U16 _u16CadtvNetworkTuningNetworkID = DEFAULT_DVBC_NID;
void MApp_CATV_RestoreManutuning_settingDefault(void)
{
   _u32CadtvManualTuningFrequency = DEFAULT_DVBC_FREQUENCY;
 _u16CadtvManualTuningSymbo = DEFAULT_DVBC_SYMBOL_RATE;
 _enCadtvManualTuningQamType= CAB_QAM16;
 _u16CadtvNetworkTuningNetworkID = DEFAULT_DVBC_NID;
 }


BOOL MApp_CadtvManualTuning_IncreaseFrequency(void)
{
    if( _u32CadtvManualTuningFrequency+500 <= MAX_DVBC_FREQUENCY )
        _u32CadtvManualTuningFrequency = _u32CadtvManualTuningFrequency+500;
    else
        _u32CadtvManualTuningFrequency = MIN_DVBC_FREQUENCY;
    return TRUE;
}

BOOL MApp_CadtvManualTuning_DecreaseFrequency(void)
{
    if( _u32CadtvManualTuningFrequency-500 >= MIN_DVBC_FREQUENCY )
        _u32CadtvManualTuningFrequency = _u32CadtvManualTuningFrequency-500;
    else
        _u32CadtvManualTuningFrequency = MAX_DVBC_FREQUENCY;
    return TRUE;
}

U32 MApp_CadtvManualTuning_GetFrequency(void)
{
    return _u32CadtvManualTuningFrequency;
}

BOOL MApp_CadtvManualTuning_SetFrequency(U32 u32freq)
{
    if(u32freq <= MAX_DVBC_FREQUENCY && u32freq >= MIN_DVBC_FREQUENCY)
    {
        _u32CadtvManualTuningFrequency = u32freq;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


BOOL MApp_CadtvManualTuning_IncreaseSymbol(void)
{
    if( _u16CadtvManualTuningSymbo+1 <= MAX_DVBC_SYMBOL_RATE)
    {
        _u16CadtvManualTuningSymbo = _u16CadtvManualTuningSymbo+1;
    }
    else
    {
        _u16CadtvManualTuningSymbo = MIN_DVBC_SYMBOL_RATE;
    }
    return TRUE;
}

BOOL MApp_CadtvManualTuning_DecreaseSymbol(void)
{
    if(_u16CadtvManualTuningSymbo-1 > MIN_DVBC_SYMBOL_RATE)
    {
        _u16CadtvManualTuningSymbo = _u16CadtvManualTuningSymbo-1;
    }
    else
    {
        _u16CadtvManualTuningSymbo = MAX_DVBC_SYMBOL_RATE;
    }
    return TRUE;
}

U16 MApp_CadtvManualTuning_GetSymbol(void)
{
    return _u16CadtvManualTuningSymbo;
}

BOOL MApp_CadtvManualTuning_SetSymbol(U16 u16Sym)
{
    if(u16Sym <= MAX_DVBC_SYMBOL_RATE && u16Sym >= MIN_DVBC_SYMBOL_RATE)
    {
         _u16CadtvManualTuningSymbo = u16Sym;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL MApp_CadtvManualTuning_IncreaseQamType(void)
{
    switch( _enCadtvManualTuningQamType )
    {
        case CAB_QAM16:
            _enCadtvManualTuningQamType = CAB_QAM32;
            break;
        case CAB_QAM32:
            _enCadtvManualTuningQamType = CAB_QAM64;
            break;
        case CAB_QAM64:
            _enCadtvManualTuningQamType = CAB_QAM128;
            break;

        case CAB_QAM128:
            _enCadtvManualTuningQamType = CAB_QAM256;
            break;
        case CAB_QAM256:
        default:
            _enCadtvManualTuningQamType = CAB_QAM16;
            break;
    }
    return TRUE;
}

BOOL MApp_CadtvManualTuning_DecreaseQamType(void)
{
    switch( _enCadtvManualTuningQamType )
    {
        case CAB_QAM16:
        default:
            _enCadtvManualTuningQamType = CAB_QAM256;
            break;
        case CAB_QAM32:
            _enCadtvManualTuningQamType = CAB_QAM16;
            break;
        case CAB_QAM64:
            _enCadtvManualTuningQamType = CAB_QAM32;
            break;

        case CAB_QAM128:
            _enCadtvManualTuningQamType = CAB_QAM64;
            break;
        case CAB_QAM256:
            _enCadtvManualTuningQamType = CAB_QAM128;
            break;
    }
    return TRUE;
}

EN_CAB_CONSTEL_TYPE MApp_CadtvManualTuning_GetQamType(void)
{
    return _enCadtvManualTuningQamType;
}

BOOL MApp_CadtvManualTuning_SetQamType(EN_CAB_CONSTEL_TYPE eQAM)
{
    if(eQAM <= CAB_QAM256)
    {
        _enCadtvManualTuningQamType = eQAM;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

U16 MApp_CadtvManualTuning_GetNID(void)
{
    return _u16CadtvNetworkTuningNetworkID;
}

BOOL MApp_CadtvManualTuning_SetNID(U16 u16NID)
{
    _u16CadtvNetworkTuningNetworkID = u16NID;
    return TRUE;
}
#undef MAPP_CADTVPROC_C

