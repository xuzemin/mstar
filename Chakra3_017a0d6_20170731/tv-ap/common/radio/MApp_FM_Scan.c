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

#define MApp_FM_SCAN_C

//******************************************************************************
//                    Header Files
//******************************************************************************
#include "Board.h"

#if ENABLE_FM_RADIO

#include "datatype.h"
#include "Utl.h"


#include "msAPI_Global.h"
#include "msAPI_IR.h"
#include "msAPI_Tuning.h"
#include "msAPI_audio.h"
#include "msAPI_VD.h"
#include "msAPI_Timer.h"
#include "MApp_ZUI_APIwindow.h"
#include "apiXC.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#include "MApp_InputSource.h"

#include "ZUI_exefunc.h"
#include "MApp_ZUI_Main.h"

#include"MApp_BlockSys.h"
#include"MApp_MultiTasks.h"
#include "IF_Demodulator.h"


#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "ZUI_tables_h.inl"

#include "MApp_SaveData.h"
#include "MApp_GlobalFunction.h"
//#include "MApp_SignalMonitor.h"
#include "MApp_ChannelChange.h"
#include "MApp_TopStateMachine.h"


#include "MApp_FMRadio_Main.h"
#include "MApp_FM_Scan.h"
#include "MApp_Radio_DB.h"
#include "MApp_Radio.h"


//==============================================================
void MApp_ZUI_ACT_FMRadio_ResetListItemFocus(U8 u8ChIdx);

extern EN_FM_SCAN_TYPE enFMScanType;
//extern U16 g_PreFMFreq;

//********************************************************************************
//                     Macro
//********************************************************************************
#define MEASURE_CONUT_NUM   5

#define FM_SCAN_DBINFO(y)      y

#define ENABLE_FM_RADIO_UTOPIA    ENABLE


//********************************************************************************
//                     Local
//********************************************************************************
static EN_FM_SCAN_STATE enFMScanState = STATE_FM_SCAN_IDLE;//STATE_FM_SCAN_INIT;
//static EN_FM_SCAN_STATE enPreFMScanState = STATE_FM_SCAN_INIT;

BOOLEAN bIsOneChannelDetected;
U8 g_u8CurChIdx;
static U8 g_ScanLoopBack = 0;

extern U16 g_CurFMFreq;
static U16 g_PreFMFreq;


#define FmRadioOneChannel50kHzFrequencyStepCheckNum   5 // FM Radio channel bandwidth is 200kHz, we check by 50kHz step.
S16 TH_AMP_DIFF = 0xA0;
S16 TH_AMP_DIFF_DROP = 0x60;
S16 TH_MAX_AMP = 0x4c0;
S16 TH_DC_DIFF = 0x3, TH_DC_GHOST = 0;
S16 TH_DC_DIFF_FLAG = 0x1, TH_AMP_DIFF_FLAG = 0x1, TH_DC_CONTINUE_FLAG = 0x2, TH_AMP_DC_RELATIONSHIP_FLAG = 0x3, TH_NSR_FLAG = 0x3;
S32 AMP_DIFF = 0, AMP_DIFF_PREV = 0, AMP_PREV = 0;
S16 DC_DIFF = 0, DC_PREV = 0, NSR_DIFF = 0, NSR_PREV = 0;
U8 adj_count, lock_count;
U8 got_new_channel = 0;
U16 tmp_g_CurFMFreq[FmRadioOneChannel50kHzFrequencyStepCheckNum] = {0};
S16 tmp_ABS_DC_AMP[FmRadioOneChannel50kHzFrequencyStepCheckNum] = {0};
S16 tmp_DC_DIFF[FmRadioOneChannel50kHzFrequencyStepCheckNum] = {0};
S16 tmp_ABS_AMP[FmRadioOneChannel50kHzFrequencyStepCheckNum] = {0};
S16 tmp_ABS_AMP_DIFF[FmRadioOneChannel50kHzFrequencyStepCheckNum] = {0};
S16 tmp_ABS_NSR_DIFF[FmRadioOneChannel50kHzFrequencyStepCheckNum] = {0};
S32 min_ABS_DC_AMP, max_ABS_AMP;

static int ABS(int x)
{
    return x < 0 ? -x : x;
}

static void MApp_FM_Scan_ProcessUserInput ( void );
//extern BOOLEAN MApp_ZUI_ACT_ExecuteAutoTuningAction(U16 act);

//********************************************************************************
//                     Functions
//********************************************************************************
EN_FM_SCAN_STATE MApp_FM_Scan_GetState ( void )
{
    return enFMScanState;
}

static void MApp_SetFMScanPercentageNum(void)
{
    u8SFMScanPercentageNum = (g_CurFMFreq -FM_MIN_FREQ )*100 /(FM_MAX_FREQ - FM_MIN_FREQ);
}

static void MApp_SetFMScanFreqNum(U16 u16Freq_x10K)
{
    u16SFMScanFreqNum = u16Freq_x10K;
}

void MApp_FM_Scan_Init ( void )
{
    enFMScanState = STATE_FM_SCAN_INIT;
    MApp_FMRadio_SetState(FMRADIO_STATE_SCAN);

    if (enFMScanType == FM_SCAN_TYPE_ALL)
    {
        MApp_FMRadio_DB_RestoreToDefault();
        g_CurFMFreq = FM_MIN_FREQ;

        g_u8CurChIdx = 0;
        MApp_FMRadio_Set_CurChIdx( g_u8CurChIdx );
    }
    else
    {
        g_u8CurChIdx = MApp_FMRadio_Get_CurChIdx();
    }

    g_PreFMFreq = g_CurFMFreq;
    g_ScanLoopBack = 0;
    AMP_DIFF = 0, AMP_DIFF_PREV = 0, AMP_PREV = 0;
    got_new_channel = 0;
    u8SFMScanPercentageNum = 0;

}


#if 1 // use Amp difference to judge new channel and then use DCAmp to select best frequency for this new channel..
#define NearbyChannalScan 0

S32 MApp_FM_Get_AmpInfo(void)
{
    S32 AMP = 0;

    msAPI_Timer_Delayms(30);    // give 30 milisecond delay to get Amp info.

#if ENABLE_FM_RADIO_UTOPIA
    AMP = MApi_AUDIO_FM_RADIO_GET_AMP();
#endif

    return AMP;
}

S16 MApp_FM_Get_DCAmpInfo(void)
{
    S16 DC_AMP;

    msAPI_Timer_Delayms(30);    // give 30 milisecond delay to get DCAmp info.
    DC_AMP = MApi_AUDIO_FM_RADIO_GET_DC_AMP();
    DC_AMP = ABS(DC_AMP);

    return DC_AMP;
}

S16 MApp_FM_Get_NSR(void)
{
    S16 NSR;

    msAPI_Timer_Delayms(30);    // give 30 milisecond delay to get NSR info.
    NSR = MApi_AUDIO_FM_RADIO_GET_NSR();
    NSR = ABS(NSR);

    return NSR;
}

void MApp_FM_CH_BEST_FREQ_SEL(void)
{
    int i;
    S32 AMP = 0;
    S16 ABS_DC_AMP = 0, ABS_DC_AMP_PREV, ABS_NSR;

    i = 1;
    while ((i < FmRadioOneChannel50kHzFrequencyStepCheckNum) && (got_new_channel))
    {
        i++;
        g_CurFMFreq += 5;   // Freq+20kHz for finding next stop
        MApp_FMRadio_SetFMFreq( g_CurFMFreq );// set Tuner Freq
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_STOP, NULL, NULL);
        msAPI_Timer_Delayms(1);
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_PLAY, NULL, NULL);
        msAPI_Timer_Delayms(45);
        tmp_g_CurFMFreq[adj_count] = g_CurFMFreq;
        AMP = MApp_FM_Get_AmpInfo();
        AMP_DIFF_PREV = AMP_DIFF;
        AMP_DIFF = AMP-AMP_PREV;
        FM_SCAN_DBINFO(printf("AMP_PREV:0x%04X AMP:0x%04X AMP_DIFF:0x%04X\n", AMP_PREV, AMP, AMP_DIFF));
        AMP_PREV = AMP;


#if 0
        if ((i == 2) && (-AMP_DIFF)>= TH_AMP_DIFF_DROP)  // To prevent ghost channel that has amplitude raise >= TH_AMP_DIFF) but drop immediately.
        {
             lock_count = 0;
             adj_count = 0;
             return;
        }
#endif

        ABS_DC_AMP = MApp_FM_Get_DCAmpInfo();
        DC_DIFF = ABS_DC_AMP - DC_PREV;
        DC_PREV = ABS_DC_AMP;
        printf("ABS_DC_AMP: 0x%02X\n", ABS_DC_AMP);
        printf("2. DC_DIFF:0x%04X \n", DC_DIFF);

        ABS_NSR = MApp_FM_Get_NSR();
        NSR_DIFF = ABS_NSR - NSR_PREV;
        NSR_PREV = ABS_NSR;
        printf("3. ABS_NSR:0x%04X \n", ABS_NSR);

        //if (-(AMP_DIFF+AMP_DIFF_PREV)>= TH_AMP_DIFF)
        if (0)
        {
            FM_SCAN_DBINFO(printf("(AMP_DIFF_PREV+AMP_DIFF):-0x%04X\n", -(AMP_DIFF_PREV+AMP_DIFF)));
            FM_SCAN_DBINFO(printf("got_new_channel = 0\n"));

#if 0
            tmp_ABS_DC_AMP[adj_count] = ABS_DC_AMP;
            if  (min_ABS_DC_AMP > ABS_DC_AMP)
                min_ABS_DC_AMP = ABS_DC_AMP;

            lock_count++;
#else
            tmp_ABS_DC_AMP[adj_count] = 0x7F;  // assign largest DC AMP to this frequency so that this frequency would not be choose as the best.
#endif
            tmp_DC_DIFF[adj_count] = DC_DIFF;
            tmp_ABS_AMP_DIFF[adj_count] = AMP_DIFF;
            tmp_ABS_NSR_DIFF[adj_count] = NSR_DIFF;

            got_new_channel = 0;
            adj_count = 0;
        }
        else
        {
            printf("g_CurFMFreq = %d KHz\n", g_CurFMFreq*10);
            tmp_ABS_DC_AMP[adj_count] = ABS_DC_AMP;
            tmp_ABS_AMP[adj_count] = AMP;
            tmp_DC_DIFF[adj_count] = DC_DIFF;
            tmp_ABS_AMP_DIFF[adj_count] = AMP_DIFF;
            tmp_ABS_NSR_DIFF[adj_count] = NSR_DIFF;

            if  (min_ABS_DC_AMP > ABS_DC_AMP)
                min_ABS_DC_AMP = ABS_DC_AMP;

            if (max_ABS_AMP < AMP)
                max_ABS_AMP = AMP;

            adj_count++;
            lock_count++;

            ABS_DC_AMP_PREV = ABS_DC_AMP;
        }
    }
    AMP_DIFF_PREV = AMP_DIFF;
}

U8 MApp_FM_Scan_SearchOneCh(void)
{
    S32 AMP = 0;
    U16 index = 0;
    U16 DC_FLAG = 0, AMP_FLAG = 0, AMP_FLAG_CONTINUE = 0, AMP_DC_FLAG_RELATIONSHIP = 0;
    U16 NSR_FLAG = 0, NSR_BREAK_CHECK_FLAG = 0;
    S16 ABS_DC_AMP = 0, ABS_DC_AMP_PREV, ABS_NSR;
    min_ABS_DC_AMP = 0x7FFF;
    max_ABS_AMP = 0;
    got_new_channel = 0;
    adj_count = 0;
    lock_count = 0;

#if ENABLE_FM_RADIO_UTOPIA
    MApi_AUDIO_FM_RADIO_SetScanMode(TRUE);
#endif
    while (g_CurFMFreq <= FM_MAX_FREQ)
    {
        MApp_FM_Scan_ProcessUserInput();

        MApp_SetFMScanFreqNum(g_CurFMFreq);
        MApp_FMRadio_SetFMFreq( g_CurFMFreq );// set Tuner Freq
        MApp_SetFMScanPercentageNum();
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
        FM_SCAN_DBINFO(printf("\n\ng_CurFMFreq = %d KHz\n", g_CurFMFreq*10));
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_STOP, NULL, NULL);
        msAPI_Timer_Delayms(1);
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_PLAY, NULL, NULL);

        AMP = MApp_FM_Get_AmpInfo();
        if (AMP_PREV != 0)
            AMP_DIFF = AMP-AMP_PREV;
        FM_SCAN_DBINFO(printf("1 AMP_PREV:0x%04X AMP:0x%04X AMP_DIFF:0x%04X\n", AMP_PREV, AMP, AMP_DIFF));
        AMP_PREV = AMP;

        //get DC_AMP
        ABS_DC_AMP = MApp_FM_Get_DCAmpInfo();
        ABS_DC_AMP_PREV = ABS_DC_AMP;
        ABS_NSR = MApp_FM_Get_NSR();
        FM_SCAN_DBINFO(printf("1 ABS_DC_AMP: 0x%02X , ABS_NSR: 0x%02X \n", ABS_DC_AMP, ABS_NSR));

        //if (DC_PREV != 0)  // AMP_PREV init value is 0
            DC_DIFF = ABS_DC_AMP - DC_PREV;
        DC_PREV = ABS_DC_AMP;

        NSR_DIFF = ABS_NSR - NSR_PREV;
        NSR_PREV = ABS_NSR;
    search_new_channel:
        if (got_new_channel == 0)
        {
            FM_SCAN_DBINFO(printf("1 AMP_DIFF_PREV:0x%04X AMP_DIFF:0x%04X\n", AMP_DIFF_PREV, AMP_DIFF));
            FM_SCAN_DBINFO(printf("1 (AMP_DIFF_PREV+AMP_DIFF):0x%04X\n", (AMP_DIFF_PREV+AMP_DIFF)));
            if ((AMP_DIFF+AMP_DIFF_PREV)>= TH_AMP_DIFF)
            {
                got_new_channel = 1;
                tmp_g_CurFMFreq[adj_count] = g_CurFMFreq;
                tmp_ABS_DC_AMP[adj_count] = ABS_DC_AMP;
                min_ABS_DC_AMP = ABS_DC_AMP; // consider the rise point
                tmp_ABS_AMP[adj_count] = AMP;
                tmp_DC_DIFF[adj_count] = DC_DIFF;
                tmp_ABS_NSR_DIFF[adj_count] = NSR_DIFF;
                tmp_ABS_AMP_DIFF[adj_count] = AMP_DIFF;
                max_ABS_AMP = AMP;  // consider the rise point

                adj_count++;
                lock_count++;

                printf("1. DC_DIFF:0x%04X  ABS_DC_AMP:0x%04X  DC_PREV:0x%04X\n", DC_DIFF, ABS_DC_AMP, DC_PREV);
                printf("2. NSR_DIFF:0x%04X  ABS_NSR:0x%04X \n", NSR_DIFF, ABS_NSR);
                FM_SCAN_DBINFO(printf("MApp_FM_CH_BEST_FREQ_SEL 1\n"));
                MApp_FM_CH_BEST_FREQ_SEL();
                adj_count = 0;
            }
            else
            {
                AMP_DIFF_PREV = AMP_DIFF;
            }
        }

/////////////////////////////////////////// It's no sense case
        if (lock_count > adj_count)
        {
            index = 0;
            DC_FLAG = 0;
            AMP_FLAG = 0;
            AMP_FLAG_CONTINUE = 0;
            NSR_FLAG = 0;
            NSR_BREAK_CHECK_FLAG = 0;
            while (index < lock_count)
            {
                // The last 2 of DC value if is 0 or 1 will be regarded as ghost channel
                if(((tmp_ABS_DC_AMP[index]) <= TH_DC_DIFF) && (index > 2) && (tmp_ABS_AMP_DIFF[index] <= 0x50))
                {
                    DC_FLAG++;
                }

                // The last 2 of AMP value have two or more less than 0x140 that will be regarded as ghost channel
                // Special case: Add (tmp_ABS_DC_AMP[index] < 0x8) to prevent loss Taiwan channel 90.3 / 90.7
                if( ((tmp_ABS_AMP[index] <= 0x140) && (tmp_ABS_DC_AMP[index] < 0x8)) && (index > 2))
                {
                    AMP_FLAG++;
                }

                // To detect DC value oscillation
                if((ABS(tmp_DC_DIFF[index]) <= 1) && (index > 0))
                {
                    AMP_FLAG_CONTINUE++;
                }

                // in theory, AMP is inversely proportional to DC
                if( (((tmp_ABS_AMP_DIFF[index] <= 0) && (tmp_DC_DIFF[index] <= 0)) || ((tmp_ABS_AMP_DIFF[index] >= 0) && (tmp_DC_DIFF[index] >= 0))) && (index > 0))
                {
                    AMP_DC_FLAG_RELATIONSHIP++;
                }

                // detect NSR oscillation
                if((ABS(tmp_ABS_NSR_DIFF[index]) <= 0x12) && (index > 0) )
                {
                    NSR_FLAG++;
                }

                // set break point, if there is a tmp_ABS_NSR_DIFF[index] >= 0x2A, then we think that is not a ghost channel
                if((ABS(tmp_ABS_NSR_DIFF[index]) >= 0x2A) && (index > 0) )
                {
                    NSR_BREAK_CHECK_FLAG++;
                }
                index++;
            }
        }

//////////////////////////////////write when lock to unlock
        if (lock_count > adj_count)
        {
            index = 0;
            while (index < lock_count)
            {
                if (((AMP_FLAG > TH_AMP_DIFF_FLAG) || (DC_FLAG > TH_DC_DIFF_FLAG) || (AMP_FLAG_CONTINUE > TH_DC_CONTINUE_FLAG)) && (max_ABS_AMP < TH_MAX_AMP ) && (NSR_BREAK_CHECK_FLAG == 0))
                {
                    printf("Freq = %d KHz fail !!!\n", tmp_g_CurFMFreq[index]*10);
                    printf("DC_FLAG = %d  AMP_FLAG = %d AMP_FLAG_CONTINUE = %d \n", DC_FLAG, AMP_FLAG, AMP_FLAG_CONTINUE);
                    printf("AMP_DC_FLAG_RELATIONSHIP = %d  NSR_FLAG = %d  NSR_BREAK_CHECK_FLAG = %d  \n", AMP_DC_FLAG_RELATIONSHIP, NSR_FLAG, NSR_BREAK_CHECK_FLAG);
                    got_new_channel = 0;
                    #if ENABLE_FM_RADIO_UTOPIA
                        MApi_AUDIO_FM_RADIO_SetScanMode(FALSE);
                    #endif
                    return false;
                }

                if ( (AMP_DC_FLAG_RELATIONSHIP > TH_AMP_DC_RELATIONSHIP_FLAG) || (NSR_FLAG > TH_NSR_FLAG))
                {
                    printf("Freq = %d KHz fail !!!\n", tmp_g_CurFMFreq[index]*10);
                    printf("DC_FLAG = %d  AMP_FLAG = %d AMP_FLAG_CONTINUE = %d \n", DC_FLAG, AMP_FLAG, AMP_FLAG_CONTINUE);
                    printf("AMP_DC_FLAG_RELATIONSHIP = %d  NSR_FLAG = %d \n", AMP_DC_FLAG_RELATIONSHIP, NSR_FLAG, NSR_BREAK_CHECK_FLAG);
                    got_new_channel = 0;
                    #if ENABLE_FM_RADIO_UTOPIA
                        MApi_AUDIO_FM_RADIO_SetScanMode(FALSE);
                    #endif
                    return false;
                }

/*                if ( (tmp_ABS_AMP[index] == max_ABS_AMP) && (tmp_DC_DIFF[index] > TH_DC_GHOST))
                {
                    printf("Freq = %d KHz fail !!!\n", tmp_g_CurFMFreq[index]*10);
                    printf("The chosen DC value is large than pre_DC value !!!\n");
                    got_new_channel = 0;
                    return false;
                }
*/

/*               if ( (tmp_ABS_AMP[index] == max_ABS_AMP) && (tmp_ABS_DC_AMP[index] > 0x8))
                {
                    printf("Freq = %d KHz fail !!!\n", tmp_g_CurFMFreq[index]*10);
                    printf("The chosen DC value is too large, make no sense, it's probably a ghost channel !!!\n");
                    got_new_channel = 0;
                    return false;
                }
*/
                if ( tmp_ABS_AMP[index] == max_ABS_AMP )
                {
                    printf("Freq = %d KHz Lock!!!\n\n", tmp_g_CurFMFreq[index]*10);
                    printf("DC_FLAG = %d  AMP_FLAG = %d AMP_FLAG_CONTINUE = %d \n", DC_FLAG, AMP_FLAG, AMP_FLAG_CONTINUE);
                    printf("AMP_DC_FLAG_RELATIONSHIP = %d  NSR_FLAG = %d  NSR_BREAK_CHECK_FLAG = %d  \n", AMP_DC_FLAG_RELATIONSHIP, NSR_FLAG, NSR_BREAK_CHECK_FLAG);

                    StuRadioChData stuRadioData;
                    memset(&stuRadioData, 0, sizeof(StuRadioChData));
                    MApp_FMRadio_DB_Get_ChDefaultValue(g_u8CurChIdx, &stuRadioData);

                    stuRadioData.u16Freq_x10K = tmp_g_CurFMFreq[index];

                    MApp_FMRadio_SaveCh(g_u8CurChIdx, &stuRadioData);
                    break;
                }
                index++;
            }

#if (NearbyChannalScan == 0)
            got_new_channel = 0;
#endif
            if  (got_new_channel == 0)
            {
            #if ENABLE_FM_RADIO_UTOPIA
                MApi_AUDIO_FM_RADIO_SetScanMode(FALSE);
            #endif
                return TRUE;
            }

            lock_count = 0;
            adj_count = 0;
            min_ABS_DC_AMP = 0x7FFF;
            max_ABS_AMP = 0;
            g_CurFMFreq += 5;   // Freq+20kHz for finding next stop
            MApp_FMRadio_SetFMFreq( g_CurFMFreq );// set Tuner Freq
            printf("g_CurFMFreq = %d KHz\n", g_CurFMFreq*10);
            printf("Continue searching nearby channel..\n");
            goto search_new_channel;
        }

        ////////////////////////////////////////////////////////////////////////
        if ( adj_count == 0 && lock_count == 0 )
            break;
    }
    //printf("lock_count = %d\n", lock_count);

#if ENABLE_FM_RADIO_UTOPIA
    MApi_AUDIO_FM_RADIO_SetScanMode(FALSE);
#endif

    return FALSE;
}
#endif

void MApp_FM_Scan_End( void )
{
    g_ScanLoopBack = 0;

    // Load first channel...
    if( enFMScanType == FM_SCAN_TYPE_ALL )
    {
        g_Radio_u8CurChIdx = 0;
        MApp_FMRadio_LoadCh(g_Radio_u8CurChIdx, &g_Radio_stCurChData );

        g_CurFMFreq = g_Radio_stCurChData.u16Freq_x10K;
        //printf("g_CurFMFreq=%u\n", g_CurFMFreq);

        MApp_FMRadio_SetFMFreq(g_CurFMFreq);
    }
    else
    {
        //
    }

}

//For ZUI use
void MApp_FM_Scan_Stop ( void )
{
    enFMScanState = STATE_FM_SCAN_END;
}

EN_RET MApp_FM_Scan ( void )
{
    EN_RET enFMScanRetVal;

    enFMScanRetVal = EXIT_NULL;

    MApp_FM_Scan_ProcessUserInput();

    FM_SCAN_DBINFO( printf( "==============================\n" ) );

    switch ( enFMScanState )
    {
        case STATE_FM_SCAN_INIT:
            FM_SCAN_DBINFO( printf( "STATE_FM_SCAN_INIT>>\n" ) );
            enFMScanState = STATE_FM_SCAN_WAIT;
            break;

        case STATE_FM_SCAN_WAIT:
            FM_SCAN_DBINFO( printf( "STATE_FM_SCAN_WAIT>>\n" ) );
            enFMScanState = STATE_FM_SCAN_TUNING;
            break;

        case STATE_FM_SCAN_TUNING:
            FM_SCAN_DBINFO( printf( "STATE_FM_SCAN_TUNING>>\n" ) );

            //printf("g_u8CurChIdx=%u\n", g_u8CurChIdx);
            //printf("g_PreFMFreq=%u\n", g_PreFMFreq);
            //printf("g_CurFMFreq=%u\n", g_CurFMFreq);


            if (enFMScanType == FM_SCAN_TYPE_ONECH)
            {
                //g_CurFMFreq < FM_MAX_FREQ;

                bIsOneChannelDetected = MApp_FM_Scan_SearchOneCh();
                if (bIsOneChannelDetected)
                {
                    FM_SCAN_DBINFO( printf( "Got one channel Freq is %d KHz\n", g_CurFMFreq *10) );
                    enFMScanState = STATE_FM_SCAN_END;
                    break;
                }
                else
                {
                    g_CurFMFreq += 5;

                    if (g_CurFMFreq > FM_MAX_FREQ)
                    {
                        g_CurFMFreq = FM_MIN_FREQ;
                        g_ScanLoopBack = 1;
                    }

                    if ((g_CurFMFreq >= g_PreFMFreq) && (g_ScanLoopBack == 1))
                    {
                        enFMScanState = STATE_FM_SCAN_END;
                        break;
                    }
                }
            }
            else //FM_SCAN_TYPE_ALL
            {
                //printf("g_u8CurChIdx=%u\n", g_u8CurChIdx);

                bIsOneChannelDetected = MApp_FM_Scan_SearchOneCh();
                if (bIsOneChannelDetected)
                {
                    g_u8CurChIdx++;
                    if (g_u8CurChIdx >= RADIO_CH_NUM)
                    {
                        g_u8CurChIdx = 0;
                        //FM_CUR_CH = 0;  //set to first channel
                        enFMScanState = STATE_FM_SCAN_END;
                        break;
                    }
                    MApp_FMRadio_Set_CurChIdx( g_u8CurChIdx );
                }

                g_CurFMFreq += 5;
                if (g_CurFMFreq > FM_MAX_FREQ)
                {
                    enFMScanState = STATE_FM_SCAN_END;
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
                    break;
                }

            }
            break;


        case STATE_FM_SCAN_SHOW_INFO:
            FM_SCAN_DBINFO( printf( "STATE_FM_SCAN_SHOW_INFO>>\n" ) );
            break;

        case STATE_FM_SCAN_END:
            FM_SCAN_DBINFO( printf( "STATE_FM_SCAN_END>>\n" ) );

            MApp_FM_Scan_End();

            if( enFMScanType == FM_SCAN_TYPE_ALL )
            {
                MApp_ZUI_API_ShowWindow(HWND_FMRADIO_AUTOTUNE_INFO_PAGE, SW_HIDE);

                //MApp_ZUI_API_SetFocus(HWND_FMRADIO_LIST_ITEM1);
                MApp_ZUI_ACT_FMRadio_ResetListItemFocus(MApp_FMRadio_Get_CurChIdx());
            }

            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);

            enFMScanState = STATE_FM_SCAN_IDLE;
            MApp_FMRadio_SetState(FMRADIO_STATE_SCAN_END);
            break;


        case STATE_FM_SCAN_IDLE:
            //FM_SCAN_DBINFO( printf( "STATE_FM_SCAN_IDLE>>\n" ) );
            break;


        case STATE_FM_SCAN_PAUSE:
            FM_SCAN_DBINFO( printf( "STATE_FM_SCAN_PAUSE>>\n" ) );
            break;


        case STATE_FM_SCAN_GOTO_STANDBY:
            MApp_FM_Scan_End();
            enFMScanRetVal =EXIT_GOTO_STANDBY;
            enFMScanState = STATE_FM_SCAN_INIT;
            break;

        default:
            break;
    }

    return enFMScanRetVal;
}

#if 1
//********************************************************************************
//            Static Functions
//********************************************************************************
static void MApp_FM_Scan_ProcessUserInput( void )
{
    printf("u8KeyCode: 0x%x\n",u8KeyCode);
    switch ( u8KeyCode )
    {
        case KEY_POWER:
        case DSC_KEY_PWROFF:
        case KEY_PAUSE:
        case KEY_EXIT:
            bFMStopScan = 1;
            MApp_FM_Scan_Stop();
            break;

        default:
            break;
    }

}
#endif

void MApp_FM_SetFMScanState(EN_FM_SCAN_STATE atvScanState)
{
    enFMScanState = atvScanState;
}

//******************************************************************************
#endif //#if ENABLE_FM_RADIO
#undef MApp_FM_SCAN_C

