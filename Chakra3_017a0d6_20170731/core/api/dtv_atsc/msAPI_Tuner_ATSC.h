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
#ifndef MSAPI_TUNER_ATSC_H
#define MSAPI_TUNER_ATSC_H

#include "Board.h"

#include "MApp_GlobalSettingSt.h"
#include "msAPI_Tuner.h"
/********************************************************************************/
/*                     Macro                                                    */
/********************************************************************************/
/* define in msAPI_Tuning.h
#if( TV_FREQ_SHIFT_CLOCK )
typedef enum
{
    SHIFT_CLK_ORIGIN_43d2M,
    SHIFT_CLK_TYPE1_42M,
    SHIFT_CLK_TYPE2_44d4M
} TV_FREQ_SHIFT_MODE;
#endif
*/


#ifdef MSAPI_TUNER_ATSC_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

#if VIF_SCOPE_1M
#define NTSC_FREQ_OFFSET_MAX_COUNT    3
#else
#define NTSC_FREQ_OFFSET_MAX_COUNT    5
#endif

#if (DEMOD_ATSC_USE_UTOPIA)
typedef struct
{
    U8     DemodState;
    U8     ChnProfile[6];
    U8     SNR;
    U8     IPC[2] ;
    U8     TRMode;
    U8     DGAIN[2];//DGAIN
    U8     DGEAR;//DGEAR
    U8     B701;
    U8     AGCRF[2];
    U8     IFGAIN[2];
    U8     PGAIN;//PGAIN
    U8     FWVersion[3];
} stDemod_Message;

INTERFACE stDemod_Message stDemodMessage;
#endif

#if( TV_FREQ_SHIFT_CLOCK )
INTERFACE U8 g_u8_ShiftClk_LastMode;
#endif
INTERFACE S8 FREQ_OFFSET_RANGE_LEFT;
INTERFACE U8 FREQ_OFFSET_RANGE_RIGHT;
INTERFACE U8 FREQ_OFFSET_RANGE_Ch5Ch6_RIGHT;

INTERFACE S8 NTSC_AUTO_FREQ_OFFSET_TABLE[NTSC_FREQ_OFFSET_MAX_COUNT];
INTERFACE S8 NTSC_CH5CH6_OFFSET_TABLE[NTSC_FREQ_OFFSET_MAX_COUNT];

INTERFACE void msAPI_DemodState_INIT_ATSC(void);
INTERFACE void msAPI_Tuner_InitCurrentTPSetting_ATSC(void);
INTERFACE void msAPI_Tuner_Init_ATSC(void);
INTERFACE void msAPI_Tuner_Initialization_ATSC(BOOL bSrcChg);

#if 0 // Daniel test
void msAPI_Tuner_SetFreq_2(U16 u16Frequency, EN_DEMOD_ATSC_MODE enModulation);
#define msAPI_Tuner_SetFreq(u16Frequency, enModulation) do{ PRINT_CURRENT_LINE(); msAPI_Tuner_SetFreq_2(u16Frequency, enModulation); } while(0)
#else
INTERFACE void msAPI_Tuner_SetFreq(U16 u16Frequency, EN_DEMOD_ATSC_MODE enModulation);
#endif

INTERFACE void msAPI_Tuner_ZigZagScan(void);
INTERFACE void msAPI_Tuner_Tune2RfCh_ATSC(MS_TP_SETTING_ATSC *pstTPSetting);
INTERFACE BOOLEAN msAPI_Tuner_IsSameRfChannel_ATSC(MS_TP_SETTING_ATSC *pstTPSetting);
INTERFACE U8 msAPI_Tuner_GetLockStatus(EN_DEMOD_ATSC_MODE enModulation);
INTERFACE U32 msAPI_Tuner_GetTimer2CheckLock(U8 Antenna_Type, U8 u8ScanType, U8 CheckLockStage);
INTERFACE void msAPI_Tuner_PowerOnOff_ATSC(BOOLEAN bPower);
INTERFACE EN_SIGNAL_CONDITION msAPI_Tuner_CheckSignalSNR(void);
INTERFACE void msAPI_Tuner_SetSpectrum(EN_DEMOD_ATSC_SPECTRUM_MODE enSpectrum);
INTERFACE BOOLEAN msAPI_Demodulator_Reset_ATSC(void);
INTERFACE void msAPI_Demodulator_Exit_ATSC(void);
INTERFACE BOOLEAN msAPI_Demodulator_Init(EN_DEMOD_ATSC_MODE enModulation,EN_DEMOD_ATSC_SPECTRUM_MODE enSpectrumType);
INTERFACE BOOLEAN msAPI_Tuner_Wait(U32 WaitTiming);
INTERFACE EN_SCAN_RESULT msAPI_VSB_Check_Lock(void);
INTERFACE BOOLEAN msAPI_VSB_Check_PreLock(void);
INTERFACE BOOLEAN msAPI_VSB_Check_FsyncLock(void);
INTERFACE BOOLEAN msAPI_Qam_Check_PrecLock(void);

INTERFACE EN_SCAN_RESULT msAPI_QAM_Check_Lock(MS_TP_SETTING_ATSC *pstDemodeTPSetting);
INTERFACE BOOLEAN msAPI_NTSC_GetFreq_Offset(MS_TP_SETTING_ATSC *pstModifyTPSetting);
INTERFACE BOOLEAN msAPI_CHECK_AFT_FUNCTION(U16 Frequency, U8 Modulation,U8 *AFT_Result, BOOLEAN *VD_Result);
INTERFACE BOOLEAN msAPI_Demodulator_Get_Lock_ATSC(EN_DEMOD_ATSC_MODE enModulation);
INTERFACE BOOLEAN msAPI_In_AFT_Win_Check(MS_TP_SETTING_ATSC *pstModifyTPSetting);
INTERFACE BOOLEAN msAPI_AFT_Freq_Offset_Tune(MS_TP_SETTING_ATSC *pstModifyTPSetting);
INTERFACE BOOLEAN msAPI_NTSC_Check_Lock(MS_TP_SETTING_ATSC *pstModifyTPSetting);

BOOLEAN msAPI_Tuner_PaThruI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
BOOLEAN msAPI_Tuner_PaThruI2C_ReadBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
INTERFACE void msAPI_Tuner_PaThruI2C(BOOLEAN bEnable);
INTERFACE void msAPI_Tuner_Serial_Control_ATSC(BOOLEAN bParallelMode);
#if( TV_FREQ_SHIFT_CLOCK )
INTERFACE void msAPI_Tuner_Patch_TVShiftClk(BOOL bEnable);
INTERFACE void msAPI_Tuner_Patch_ResetTVShiftClk(void);
INTERFACE void msAPI_Tuner_Patch_TVShiftVDClk(BOOL bEnable);
#endif

INTERFACE EN_SIGNAL_CONDITION msAPI_Tuner_CheckSignalSNR(void);

void msAPI_Tuner_ATSC_Init_FreqVar(void);


#undef INTERFACE

#endif /* MSAPI_OSD_H */
