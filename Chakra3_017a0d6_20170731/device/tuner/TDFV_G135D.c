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

/******************************************************************************
 Copyright (c) 2004 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: TDFV_G135D.c
 [Date]:        9-Jan-2008
 [Comment]:
   TV tuner subroutines.
 [Reversion History]:
*******************************************************************************/

#define TDFV_G135D_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
//#include "Drviic.h"

#include "msAPI_Tuning.h"
#include "COFDM_Demodulator.h"

#include "TDFV_G135D.h"
#include "SWI2C.h"


static FREQSTEP    m_eFrequencyStep;

#define TUNER_PLL_93MHz ( (m_eFrequencyStep==FREQSTEP_62_5KHz)?(93000L*10/625):(93000L/50))
#define TUNER_PLL_399MHz    ( (m_eFrequencyStep==FREQSTEP_62_5KHz)?(399000L*10/625):(399000L/50))
#define TUNER_PLL_799MHz    ( (m_eFrequencyStep==FREQSTEP_62_5KHz)?(799000L*10/625):(799000L/50))

static FREQSTEP m_eFrequencyStep;

void devTunerSetFreqStep( FREQSTEP eFreqStep )
{
    switch ( eFreqStep )
    {
        case FREQSTEP_31_25KHz:
        case FREQSTEP_62_5KHz:
        case FREQSTEP_50KHz:
            m_eFrequencyStep = eFreqStep;
            break;

        default:
            m_eFrequencyStep = FREQSTEP_50KHz;
            break;
    }
}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
//, WORD wIFData)
{
    BYTE    cTunerData[5];

    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE( wPLLData );
    cTunerData[1] = LOBYTE( wPLLData );

    if ( m_eFrequencyStep == FREQSTEP_50KHz )
    {
        cTunerData[2] = ( _CB1_MSB_BIT | _CB1_TEST_SEL | _CB1_T_XTOUT_BUFFER_ON | _CB1_FREQ_STEP_50KHz );
    }
    else if ( m_eFrequencyStep == FREQSTEP_62_5KHz )
    {
        cTunerData[2] = ( _CB1_MSB_BIT | _CB1_TEST_SEL | _CB1_T_XTOUT_BUFFER_ON | _CB1_FREQ_STEP_62p5KHz );
    }
    else
    {
        cTunerData[2] = ( _CB1_MSB_BIT | _CB1_TEST_SEL | _CB1_T_XTOUT_BUFFER_ON | _CB1_FREQ_STEP_166p67KHz );
    }

    if(eBand == E_RFBAND_VHF_LOW)
    {
        if(wPLLData <= TUNER_PLL_93MHz + msAPI_Tuner_GetIF())
            cTunerData[3] = (_CB2_CP_122uA | _CB2_BAND_SWITCH_VHF_LOW);
        else
            cTunerData[3] = (_CB2_CP_54uA | _CB2_BAND_SWITCH_VHF_LOW);
    }
    else if(eBand == E_RFBAND_VHF_HIGH)
    {
        if(wPLLData <= TUNER_PLL_399MHz + msAPI_Tuner_GetIF())
            cTunerData[3] = (_CB2_CP_122uA | _CB2_BAND_SWITCH_VHF_HIGH);
        else
            cTunerData[3] = (_CB2_CP_580uA | _CB2_BAND_SWITCH_VHF_HIGH);
    }
    else
    {
        if(wPLLData <= TUNER_PLL_799MHz + msAPI_Tuner_GetIF())
            cTunerData[3] = (_CB2_CP_122uA | _CB2_BAND_SWITCH_UHF);
        else
            cTunerData[3] = (_CB2_CP_54uA  | _CB2_BAND_SWITCH_UHF);
    }

    // AGC
    cTunerData[4] = ( _CB1_MSB_BIT | _CB1_AGC_SEL | _CB1_ATC_220nA_2s_150nF | _CB1_IF_OUTPUT_LEVEL_DISABLED );

    if ( FALSE == SW_I2C_WriteBytes( _TUNER_I2C_ID, 0, NULL, 5, cTunerData ) )
    {
        //printf( "IIC Error 1\n" );
    }
}

void devTunerInit(void)
{
    devTunerSetFreqStep( FREQSTEP_50KHz );
}

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    CE6355_SetFrequency((DWORD)(Freq*1000.0), eBandWidth);
}

void devDigitalTuner_Init(void)
{
}

#undef TDFV_G135D_C

