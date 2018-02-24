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
#define TDA9886_C
#include "debug.h"
#include "msAPI_Tuning.h"

#include "COFDM_Demodulator.h"
#include "drvIIC.h"

#ifdef DEBUG_IFDEMODULATOR
    #define debugIFDemodulatorPrint(a,b)    debugPrint(a,b)
#else
    #define debugIFDemodulatorPrint(a,b)
#endif


//****************************************************************************
// Private attributes of this file.
//****************************************************************************

#define _IF_DEM_SUB_ADDRESS        0x00

//--------------------------------------------------
// Bescription of status register bits
//--------------------------------------------------
// AFC window
#define _MASK_OF_AFCWIN                    0x80
#define _AFCWIN_IN_WINDOW                0x80
#define _AFCWIN_OUT_OF_WINDOW            0x00

// VIF input level
#define _MASK_OF_VIFLEV                    0x40
#define _VIFLEV_HIGH_LEVEL                0x40
#define _VIFLEV_LOW_LEVEL                0x00

// FM carrier detection
#define _MASK_OF_CARRDET                0x20
#define _CARRDET_DETECTED                0x20
#define _CARRDET_NOT_DETECTED            0x00

// Automatic frequency contrl
#define _MASK_OF_AFC                    0x1E

// Power-on reset
#define _MASK_OF_PONR                    0x01
#define _PONR_AFTER_POWER_ON_RESET        0x01
#define _PONR_AFTER_SUCCESSFUL_READING    0x00

//--------------------------------------------------
// Bit description for switching mode
//--------------------------------------------------
// Output port 2 for SAW switching or monitoring.
#define _B7_OUTPUT_PORT_2_DISABLED    0x80    // High
#define _B7_OUTPUT_PORT_2_ACTIVE    0x00    // Low

// Output port 1 for SAW switching or monitoring.
#define _B6_OUTPUT_PORT_1_DISABLED    0x40    // High
#define _B6_OUTPUT_PORT_1_ACTIVE    0x00    // Low

// Forced audio mute
#define _B5_FORCED_AUDIO_MUTE_ON    0x20
#define _B5_FORCED_AUDIO_MUTE_OFF    0x00

// TV standard modulation
#define _B4B3_POSITIVE_AM_TV        0x00
#define _B4B3_NEGATIVE_FM_TV        0x10
#define _B4B3_POSITIVE_NOT_USED        0x18
#define _B4B3_NEGATIVE_NOT_USED        0x08

// Carrier mode
#define _B2_QSS_MODE                0x04
#define _B2_INTERCARRIER_MODE        0x00

// Auto mute of FM AF output
#define _B1_ACTIVE                    0x02
#define _B1_INACTIVE                0x00

// Video mode (sound trap)
#define _B0_SOUND_TRAP_BYPASS        0x01
#define _B0_SOUND_TRAP_ACTIVE        0x00

//--------------------------------------------------
// Bit description for adjust mode
//--------------------------------------------------
// Audio gain
#define _C7_MINUS_6dB            0x80
#define _C7_0dB                    0x00

// De-emphasis time constant
#define _C6_50us                0x40
#define _C6_75us                0x00

// De-emphasis
#define _C5_ON                    0x20
#define _C5_OFF                    0x00

// Tuner takeover point adjustment
#define _C4C3C2C1C0_PLUS_15dB    0x1F
#define _C4C3C2C1C0_PLUS_14dB    0x1E
#define _C4C3C2C1C0_PLUS_13dB    0x1D
#define _C4C3C2C1C0_PLUS_12dB    0x1C
#define _C4C3C2C1C0_PLUS_11dB    0x1B
#define _C4C3C2C1C0_PLUS_10dB    0x1A
#define _C4C3C2C1C0_PLUS_9dB    0x19
#define _C4C3C2C1C0_PLUS_8dB    0x18
#define _C4C3C2C1C0_PLUS_7dB    0x17
#define _C4C3C2C1C0_PLUS_6dB    0x16
#define _C4C3C2C1C0_PLUS_5dB    0x15
#define _C4C3C2C1C0_PLUS_4dB    0x14
#define _C4C3C2C1C0_PLUS_3dB    0x13
#define _C4C3C2C1C0_PLUS_2dB    0x12
#define _C4C3C2C1C0_PLUS_1dB    0x11
#define _C4C3C2C1C0_PLUS_0dB    0x10    // 0dB is equal to 17mV(RMS).
#define _C4C3C2C1C0_MINUS_1dB    0x0F
#define _C4C3C2C1C0_MINUS_2dB    0x0E
#define _C4C3C2C1C0_MINUS_3dB    0x0D
#define _C4C3C2C1C0_MINUS_4dB    0x0C
#define _C4C3C2C1C0_MINUS_5dB    0x0B
#define _C4C3C2C1C0_MINUS_6dB    0x0A
#define _C4C3C2C1C0_MINUS_7dB    0x09
#define _C4C3C2C1C0_MINUS_8dB    0x08
#define _C4C3C2C1C0_MINUS_9dB    0x07
#define _C4C3C2C1C0_MINUS_10dB    0x06
#define _C4C3C2C1C0_MINUS_11dB    0x05
#define _C4C3C2C1C0_MINUS_12dB    0x04
#define _C4C3C2C1C0_MINUS_13dB    0x03
#define _C4C3C2C1C0_MINUS_14dB    0x02
#define _C4C3C2C1C0_MINUS_15dB    0x01
#define _C4C3C2C1C0_MINUS_16dB    0x00


//--------------------------------------------------
// Bit description for data mode
//--------------------------------------------------
// VIF AGC and port features
//                                Pin OP1                    Pin OP2                Gain
//----------------------------------------------------------------------------------------
#define _E7E5_00    0x00    //    port function            port function        normal gain
#define _E7E5_01    0x20    //    port function            port function        minimum gain
#define _E7E5_10    0x80    //    port function            VIF-AGC output        normal gain
#define _E7E5_11    0xA0    //    VIF-AGC external input    port function        external gain

// L standard PLL gating
#define _E6_GATING_IN_CASE_OF_36_PERCENT_POSITIVE_MODULATION    0x40
#define _E6_GATING_IN_CASE_OF_0_PERCENT_POSITIVE_MODULATION        0x00

// Vision intermediate frequency selection
#define _E4E3E2_VIF_58p75MHz    0x00    // 0 0 0
#define _E4E3E2_VIF_45p75MHz    0x04    // 0 0 1
#define _E4E3E2_VIF_38p9MHz        0x08    // 0 1 0
#define _E4E3E2_VIF_38p0MHz        0x0C    // 0 1 1
#define _E4E3E2_VIF_33p9MHz        0x10    // 1 0 0
#define _E4E3E2_VIF_33p4MHz        0x14    // 1 0 1

// Sound intercarrier frequency selection(sound 2nd IF)
#define _E1E0_4p5MHz            0x00    // 0 0
#define _E1E0_5p5MHz            0x01    // 0 1
#define _E1E0_6p0MHz            0x02    // 1 0
#define _E1E0_6p5MHz            0x03    // 1 1

#if ( FRONTEND_TUNER_TYPE == LG_TDFV_G135D_TUNER )
#include "TDA9886_Reg_Setting_Tuner_G135D.h"
#elif ( FRONTEND_TUNER_TYPE == XUGUANG_STM_6F_V236H_TUNER )
#include "TDA9886_Reg_Setting_Tuner_STM6F.h"
#elif ( (MS_BOARD_TYPE_SEL==BD_MST556A_T2_10A_HX))
#include "TDA9886_Reg_Setting_BD_MST556A_T2_10A_HX.h"
#else
#include "TDA9886_Reg_Setting_Default.h"
#endif


static IF_FREQ m_eIF_Freq;
//****************************************************************************
// Private functions of this file.
//****************************************************************************



//****************************************************************************
// Start of public implementation
//****************************************************************************

/**
 FUNCTION    : void MDrv_IFDM_Init(void)

 USAGE    : To initialize IF-demodulator.

 INPUT    : None

 OUTPUT    : None

 GLOBALS: None

*/
void MDrv_IFDM_Init(void)
{
    m_eIF_Freq = IF_FREQ_INVALID;

    MDrv_IFDM_SetIF(IF_FREQ_B);
}

/**
 FUNCTION    : AFC MDrv_IFDM_GetFreqDev(void)

 USAGE    : To get frequency deviation.

 INPUT    : None

 OUTPUT    : AFC : Frequency deviation. See below.
                    b3 b2 b1 b0
                    0  1  1  1   under (f0 - 187.5 kHz)
                    0  1  1  0   f0 - 162.5 kHz
                    0  1  0  1   f0 - 137.5 kHz
                    0  1  0  0   f0 - 112.5 kHz
                    0  0  1  1   f0 - 87.5 kHz
                    0  0  1  0   f0 - 62.5 kHz
                    0  0  0  1   f0 - 37.5 kHz
                    0  0  0  0   f0 - 12.5 kHz
                    1  1  1  1   f0 + 12.5 kHz
                    1  1  1  0   f0 + 37.5 kHz
                    1  1  0  1   f0 + 62.5 kHz
                    1  1  0  0   f0 + 87.5 kHz
                    1  0  1  1   f0 + 112.5 kHz
                    1  0  1  0   f0 + 137.5 kHz
                    1  0  0  1   f0 + 162.5 kHz
                    1  0  0  0   over (f0 + 187.5 kHz)

 GLOBALS: None

*/
AFC MDrv_IFDM_GetFreqDev(void)
{
    BYTE cValue;

#if(FRONTEND_TUNER_TYPE == CH_TMI8_C22I1VH_TUNER)
    MDrv_IIC_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);
#else
    devCOFDM_PassThroughI2C_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);
#endif

    if( (cValue & _MASK_OF_AFCWIN) == _AFCWIN_IN_WINDOW )
    {
        return (AFC) ((cValue&_MASK_OF_AFC)>>1);
    }

    return E_AFC_OUT_OF_AFCWIN;
}

BOOLEAN MDrv_IFDM_IsAFCInWindow(void)
{
    BYTE cValue;
#if(FRONTEND_TUNER_TYPE == CH_TMI8_C22I1VH_TUNER)
    MDrv_IIC_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);
#else
    devCOFDM_PassThroughI2C_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);
#endif

    if( (cValue & _MASK_OF_AFCWIN) == _AFCWIN_IN_WINDOW )
    {
        return TRUE;
    }

    return FALSE;
}

/**
 FUNCTION    : void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq)

 USAGE    : To Set IF.

 INPUT    : eIF_Freq -    IF_FREQ_B : B
                        IF_FREQ_G : G
                        IF_FREQ_I : I
                        IF_FREQ_DK : DK
                        IF_FREQ_L : L
                        IF_FREQ_L_PRIME : L'
                        IF_FREQ_MN : M/N
                        IF_FREQ_J : M(Japan)

 OUTPUT    : None

 GLOBALS: None

*/
void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq)
{
#if(FRONTEND_TUNER_TYPE == CH_TMI8_C22I1VH_TUNER)
    m_eIF_Freq = eIF_Freq;
    drvTunerSetIF(eIF_Freq);
#elif ((FRONTEND_TUNER_TYPE ==PHILIPS_FQD1218_TUNER)||(FRONTEND_TUNER_TYPE ==PHILIPS_FQD1116_TUNER))

        BYTE cIF_Data[11];
        cIF_Data[0]=0x00;
     switch(eIF_Freq)
      {
          case  IF_FREQ_B:
                      cIF_Data[1]=0x38;
                cIF_Data[2]=0xb1;
                cIF_Data[3]=0x4c;
                cIF_Data[4]=0x67;
                cIF_Data[5]=0x40;
                cIF_Data[6]=0x80;
                cIF_Data[7]=0x0c;
                cIF_Data[8]=0x00;
                cIF_Data[9]=0x19;
                cIF_Data[10]=0x00;
                    break;
        case  IF_FREQ_I:
              cIF_Data[1]=0x58;
                cIF_Data[2]=0xb1;
                cIF_Data[3]=0xCC;
                cIF_Data[4]=0x67;
                cIF_Data[5]=0x80;
                cIF_Data[6]=0x80;
                cIF_Data[7]=0x0c;;
                cIF_Data[8]=0x00;
                cIF_Data[9]=0x19;
                cIF_Data[10]=0x00;
                    break;
        case  IF_FREQ_DK:
              cIF_Data[1]=0x78;
                cIF_Data[2]=0xb1;
                cIF_Data[3]=0x4c;
                cIF_Data[4]=0x67;
                cIF_Data[5]=0xc0;
                cIF_Data[6]=0x80;
                cIF_Data[7]=0x0c;;
                cIF_Data[8]=0x00;
                cIF_Data[9]=0x19;
                cIF_Data[10]=0x00;
                    break;
    /*
        case  IF_FREQ_MN:
              cIF_Data[1]=
                cIF_Data[2]=
                cIF_Data[3]=
                cIF_Data[4]=
                cIF_Data[5]=
                cIF_Data[6]=
                cIF_Data[7]=
                cIF_Data[8]=
                cIF_Data[9]=
                cIF_Data[10]=
    */
        case  IF_FREQ_L:
                 cIF_Data[1]= 0x79;
                cIF_Data[2]= 0x37;
                cIF_Data[3]=0x00;
                cIF_Data[4]=0x67;
                cIF_Data[5]=0xc0;
                cIF_Data[6]=0xc0;
                cIF_Data[7]=0x0c;;
                cIF_Data[8]=0x00;
                cIF_Data[9]=0x00;
                cIF_Data[10]=0x16;
                    break;
        case  IF_FREQ_L_PRIME:
                    cIF_Data[1]=0x79;
                cIF_Data[2]=0x7f;
                cIF_Data[3]=0x00;
                cIF_Data[4]=0x60;
                cIF_Data[5]=0xc0;
                cIF_Data[6]=0xc0;
                cIF_Data[7]=0x0c;
                cIF_Data[8]=0x00;
                cIF_Data[9]=0x00;
                cIF_Data[10]=0x16;
                   break;
    default:

        return;

      }

    m_eIF_Freq = eIF_Freq;

    devCOFDM_PassThroughI2C_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 11, cIF_Data);

#else
    BYTE cSwitchingValue, cAdjustValue, cDataValue;
    BYTE cIF_Data[4];

    switch(eIF_Freq)
    {
#if(FRONTEND_TUNER_TYPE == LG_TDFV_G135D_TUNER)
        case IF_DIGITAL_MODE:
        cSwitchingValue = _Digital_SWITCHING_FUNCTIONS_VALUE;
        cAdjustValue = _Digital_ADJUST_FUNCTIONS_VALUE;
        cDataValue = _Digital_DATA_FUNCTIONS_VALUE;
        break;
#endif
    case IF_FREQ_B:
        cSwitchingValue = _BG_SWITCHING_FUNCTIONS_VALUE;
        cAdjustValue = _BG_ADJUST_FUNCTIONS_VALUE;
        cDataValue = _BG_DATA_FUNCTIONS_VALUE;
        break;

    case IF_FREQ_I:
        cSwitchingValue = _I_SWITCHING_FUNCTIONS_VALUE;
        cAdjustValue = _I_ADJUST_FUNCTIONS_VALUE;
        cDataValue = _I_DATA_FUNCTIONS_VALUE;
        break;

    case IF_FREQ_DK:
        cSwitchingValue = _DK_SWITCHING_FUNCTIONS_VALUE;
        cAdjustValue = _DK_ADJUST_FUNCTIONS_VALUE;
        cDataValue = _DK_DATA_FUNCTIONS_VALUE;
        break;

    case IF_FREQ_MN:
        cSwitchingValue = _MN_SWITCHING_FUNCTIONS_VALUE;
        cAdjustValue = _MN_ADJUST_FUNCTIONS_VALUE;
        cDataValue = _MN_DATA_FUNCTIONS_VALUE;
        break;

    case IF_FREQ_L:
        cSwitchingValue = _L_SWITCHING_FUNCTIONS_VALUE;
        cAdjustValue = _L_ADJUST_FUNCTIONS_VALUE;
        cDataValue = _L_DATA_FUNCTIONS_VALUE;
        break;

    case IF_FREQ_L_PRIME:
        cSwitchingValue = _L_PRIME_SWITCHING_FUNCTIONS_VALUE;
        cAdjustValue = _L_PRIME_ADJUST_FUNCTIONS_VALUE;
        cDataValue = _L_PRIME_DATA_FUNCTIONS_VALUE;
        break;

    default:
        debugIFDemodulatorPrint("Error! Why do you come here. Get out. 0x%x",eIF_Freq);
        return;
    }

//    if( m_eIF_Freq == eIF_Freq )
//        return;

    m_eIF_Freq = eIF_Freq;

    cIF_Data[0] = _IF_DEM_SUB_ADDRESS;
    cIF_Data[1] = cSwitchingValue;
    cIF_Data[2] = cAdjustValue;
    cIF_Data[3] = cDataValue;
    devCOFDM_PassThroughI2C_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 4, cIF_Data);

#endif

}

void MDrv_IFDM_CVBSOff(void)
{
    BYTE cIF_Data[4];

    cIF_Data[0] = _IF_DEM_SUB_ADDRESS;
    cIF_Data[1] = _TUNER_CVBS_NOT_USED_VALUE;
    cIF_Data[2] = _BG_ADJUST_FUNCTIONS_VALUE;
    cIF_Data[3] = _BG_DATA_FUNCTIONS_VALUE;

    //printf("MDrv_IFDM_CVBSOff\n");

    #if(FRONTEND_TUNER_TYPE == CH_TMI8_C22I1VH_TUNER)
    #else
        devCOFDM_PassThroughI2C_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 4, cIF_Data);
    #endif
}

IF_FREQ MDrv_IFDM_GetIF(void)
{
    return m_eIF_Freq;
}
#undef TDA9886_C
