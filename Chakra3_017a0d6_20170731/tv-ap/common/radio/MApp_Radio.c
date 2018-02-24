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
#define MApp_FMRadio_C

#include "Board.h"
#include "Utl.h"

#if(ENABLE_FM_RADIO)

//#include <string.h>

//#include "msAPI_Radio.h"

#include "datatype.h"
#include "MsCommon.h"
//#include "apiXC.h"
//#include "apiXC_Adc.h"
#include "msAPI_Global.h"

#include "drvVIF.h"

#include "Tuner.h"
#include "drvVIF_Temp.h"


#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_FMRadio_Main.h"
#include "msAPI_Tuning.h"

#include "MApp_ChannelChange.h"
#include "msAPI_VD.h"
#include "msAPI_DrvInit.h"
#include "MApp_Audio.h"
#include "MApp_InputSource.h"
#include "msAPI_Timer.h"
#include "MApp_FM_Scan.h"

#include "MApp_GlobalSettingSt.h"
#include "msAPI_audio.h"
#include "MApp_Radio.h"


extern void MDrv_VIF_Init(void);


//------------------------------------------------------------------------------
#define FM_DEBUG(x)    x

#define RADIO_CH_DATA_FREQ_DEFAULT  8700 // 87.0MHz
#define RADIO_CH_DATA_NAME_DEFAULT  "CH1"

//------------------------------------------------------------------------------

U8 g_Radio_u8CurChIdx = 0;
StuRadioChData g_Radio_stCurChData;

U16 g_CurFMFreq;

//U8 g_FMCurChName[RADIO_CH_NAME_LEN];
#define g_FMCurChName   (g_Radio_stCurChData.au8ChName)

//------------------------------------------------------------------------------
void MApp_FMRadio_Var_Init(void)
{
    FM_DEBUG( printf("MApp_FMRadio_Var_Init()\n"); );

    if( stGenSetting.stRadioSetting.u8CurChNO >= RADIO_CH_NUM )
    {
        stGenSetting.stRadioSetting.u8CurChNO = 0;
    }

    g_Radio_u8CurChIdx = stGenSetting.stRadioSetting.u8CurChNO;
    printf("g_Radio_u8CurChIdx=%u\n", g_Radio_u8CurChIdx);

    MApp_FMRadio_LoadCh(g_Radio_u8CurChIdx, &g_Radio_stCurChData );

    //g_Radio_stCurChData.u16Freq_x10K;
    printf("g_Radio_stCurChData.u16Freq_x10K=%u\n", g_Radio_stCurChData.u16Freq_x10K);
}

void MApp_FMRadio_DB_Get_ChDefaultValue(U8 u8ChIdx, StuRadioChData* pstChData)
{
    memset( pstChData, 0, sizeof(StuRadioChData) );

    if( u8ChIdx >= RADIO_CH_NUM )
        return ;

    pstChData->u16Freq_x10K = RADIO_CH_DATA_FREQ_DEFAULT;

    u8ChIdx += 1;
    pstChData->au8ChName[0] = 'C';
    pstChData->au8ChName[1] = 'H';
    pstChData->au8ChName[2] = '0' + u8ChIdx / 10;
    pstChData->au8ChName[3] = '0' + u8ChIdx % 10;
}

void MApp_FMRadio_DB_RestoreToDefault(void)
{
    U8 u8ChIdx;

    memset( &(stGenSetting.stRadioSetting), 0, sizeof(StuRadioSetting) );

    StuRadioChData stChDataTmp = { RADIO_CH_DATA_FREQ_DEFAULT, RADIO_CH_DATA_NAME_DEFAULT };

    for( u8ChIdx = 0; u8ChIdx < RADIO_CH_NUM; ++ u8ChIdx )
    {
        MApp_FMRadio_DB_Get_ChDefaultValue(u8ChIdx, &stChDataTmp );

        stGenSetting.stRadioSetting.astChData[u8ChIdx] = stChDataTmp;
    }

    stGenSetting.stRadioSetting.u8CurChNO = 0;
}

U8 MApp_FMRadio_Get_CurChIdx(void)
{
    return g_Radio_u8CurChIdx;
}

void MApp_FMRadio_Set_CurChIdx(U8 u8ChIdx)
{
    printf("MApp_FMRadio_Set_CurChIdx(u8ChIdx=%u)\n", u8ChIdx );
    g_Radio_u8CurChIdx = u8ChIdx;
}

U8 MApp_FMRadio_GetCurChNum(void)
{
PRINT_CURRENT_LINE();

    if( stGenSetting.stRadioSetting.u8CurChNO >= RADIO_CH_NUM )
    {
        printf("\nError: stGenSetting.stRadioSetting.u8CurChNO=%u\n", stGenSetting.stRadioSetting.u8CurChNO);
        stGenSetting.stRadioSetting.u8CurChNO = 0;
    }

    return stGenSetting.stRadioSetting.u8CurChNO;
}

/*
U16 MApp_FMRadio_GetCurChFreq(void)
{
PRINT_CURRENT_LINE();

    //return stGenSetting.stRadioSetting.astChData[MApp_FMRadio_GetCurChNum()-1].u16Freq_x10K;

    if (g_CurFMFreq < FM_MIN_FREQ || g_CurFMFreq > FM_MAX_FREQ)
    {
        printf("\nError: g_CurFMFreq=%u\n", g_CurFMFreq);

        g_CurFMFreq = FM_MIN_FREQ;
    }

    return g_CurFMFreq;
}
*/

/*
U16 MApp_FMRadio_Get_CurChFreq(void)
{
    return g_Radio_stCurChData.u16Freq_x10K;
}

void MApp_FMRadio_Get_CurChName(U8* pu8ChName)
{
    memcpy( pu8ChName, g_Radio_stCurChData.au8ChName, RADIO_CH_NAME_LEN );
}
*/

U16 MApp_FMRadio_Get_ChFreq(U8 u8ChIdx)
{
    if( u8ChIdx >= RADIO_CH_NUM )
        return 0;

    U16 u16CurFMFreq = stGenSetting.stRadioSetting.astChData[u8ChIdx].u16Freq_x10K;

    if (u16CurFMFreq < FM_MIN_FREQ || u16CurFMFreq > FM_MAX_FREQ)
    {
        u16CurFMFreq = FM_MIN_FREQ;
        stGenSetting.stRadioSetting.astChData[u8ChIdx].u16Freq_x10K = u16CurFMFreq;
    }

    return u16CurFMFreq;
}

void MApp_FMRadio_Get_ChName(U8 u8ChIdx, U8* pu8ChName)
{
    if( u8ChIdx >= RADIO_CH_NUM )
    {
        memcpy( pu8ChName, "xxxxxx", RADIO_CH_NAME_LEN );
        return;
    }

    memcpy( pu8ChName, stGenSetting.stRadioSetting.astChData[u8ChIdx].au8ChName, RADIO_CH_NAME_LEN );
}

BOOLEAN MApp_FMRadio_SaveCh(U8 u8ChIdx, StuRadioChData* pstChData)
{
    printf("MApp_FMRadio_SaveCh(%u)\n", u8ChIdx);
    printf(" Freq=%uK\n", pstChData->u16Freq_x10K *10);

    if( u8ChIdx >= RADIO_CH_NUM )
    {
        printf("\nMApp_FMRadio_SaveCh(u8ChIdx=%u)\n", u8ChIdx);
        return FALSE;
    }

    if( pstChData->u16Freq_x10K < FM_MIN_FREQ )
    {
        pstChData->u16Freq_x10K = FM_MIN_FREQ;
    }
    else if( pstChData->u16Freq_x10K > FM_MAX_FREQ )
    {
        pstChData->u16Freq_x10K = FM_MAX_FREQ;
    }

    stGenSetting.stRadioSetting.astChData[u8ChIdx] = *pstChData;

    return TRUE;
}

BOOLEAN MApp_FMRadio_LoadCh(U8 u8ChIdx, StuRadioChData* pstChData)
{
    if( u8ChIdx >= RADIO_CH_NUM )
    {
        printf("\nMApp_FMRadio_LoadCh(u8ChIdx=%u)\n", u8ChIdx);
        return FALSE;
    }

    if( stGenSetting.stRadioSetting.astChData[u8ChIdx].u16Freq_x10K < FM_MIN_FREQ )
    {
        stGenSetting.stRadioSetting.astChData[u8ChIdx].u16Freq_x10K = FM_MIN_FREQ;
    }
    else if( stGenSetting.stRadioSetting.astChData[u8ChIdx].u16Freq_x10K > FM_MAX_FREQ )
    {
        stGenSetting.stRadioSetting.astChData[u8ChIdx].u16Freq_x10K = FM_MAX_FREQ;
    }

    *pstChData = stGenSetting.stRadioSetting.astChData[u8ChIdx];

    return TRUE;
}

/*
void MApp_FMRadio_ChangeCh(U8 u8ChIdx)
{
    if( u8ChIdx >= RADIO_CH_NUM )
        return;

    g_Radio_u8CurChIdx = u8ChIdx;

    MApp_FMRadio_LoadCh(g_Radio_u8CurChIdx, &g_Radio_stCurChData);

    msAPI_Radio_Set_Freq(g_Radio_stCurChData.u16Freq_x10K);
}
*/

EN_FM_SCAN_TYPE enFMScanType;

void MApp_FMRadio_SetFMFreq(U16 u16Freq_x10K)
{
    msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW);
    printf("MApp_FMRadio_SetFMFreq(u16Freq_x10K=%u)", u16Freq_x10K);
    msDebug_ANSI_AllAttrOffText();

    g_CurFMFreq = u16Freq_x10K;

#if 1
    // Alwasy shift 3.5M
    //u16Freq_x10K -= 350;

    devTunerSetFreq(u16Freq_x10K*10000);
#else
    U16 u16PLL = (u16Freq_x10K*10)/50;
    msAPI_SetTunerPLL_FM(u16PLL);
#endif

}

/*
void MApp_FMRadio_SaveCh(U8 u8ChIdx, StuRadioChData radioData)
{
    memcpy(&stGenSetting.stRadioSetting.astChData[u8ChIdx], &radioData, sizeof(StuRadioChData));
}
*/

void MApp_FMRadio_ChgCurCh(U8 u8ChIdx)
{
    PRINT_CURRENT_LINE();

    printf("MApp_FMRadio_ChgCurCh(u8ChIdx=%u)\n", u8ChIdx);

    if( u8ChIdx >= RADIO_CH_NUM )
        return;

    g_Radio_u8CurChIdx = stGenSetting.stRadioSetting.u8CurChNO = u8ChIdx/*+1*/;
    printf("g_Radio_u8CurChIdx=%u\n", g_Radio_u8CurChIdx);

    // Load ch setting
    MApp_FMRadio_LoadCh(g_Radio_u8CurChIdx, &g_Radio_stCurChData );

    //g_CurFMFreq = g_Radio_stCurChData.u16Freq_x10K;
    printf("stCurChData.u16Freq_x10K=%u\n", g_Radio_stCurChData.u16Freq_x10K);

    MApp_FMRadio_SetFMFreq(g_Radio_stCurChData.u16Freq_x10K);
}

void MApp_FMRadio_Init(void)
{
//PRINT_CURRENT_LINE();
    FM_DEBUG( printf("MApp_FMRadio_Init\n"); );

    MApp_FMRadio_Var_Init();

    //Set VIF
    MDrv_VIF_Init();


    //DRV_VIF_SetSoundSystem(VIF_SOUND_MN);
    MDrv_IFDM_SetIF(IF_FREQ_MN);

    //DRV_VIF_SetIfFreq(IF_FREQ_3890);
    MDrv_IFDM_SetVifIfFreq(TUNER_IF_FREQ_KHz); // MaxLiner661 => 38900L

    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_FMRADIO, ENABLE, 0, MAIN_WINDOW);

//////////////////////////////////////////////////////////////////

    MApp_FMRadio_SetFMFreq(g_Radio_stCurChData.u16Freq_x10K);

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
}

void MApp_FMRadio_SetTestCh(void)
{
    StuRadioChData radioData;
    radioData.u16Freq_x10K = 8910;
    strcpy((char *)radioData.au8ChName, "test");
    MApp_FMRadio_SaveCh(0, &radioData);
    radioData.u16Freq_x10K = 8990;
    MApp_FMRadio_SaveCh(1, &radioData);
    radioData.u16Freq_x10K = 9230;
    MApp_FMRadio_SaveCh(2, &radioData);
    radioData.u16Freq_x10K = 9670;
    MApp_FMRadio_SaveCh(3, &radioData);
    radioData.u16Freq_x10K = 9890;
    MApp_FMRadio_SaveCh(4, &radioData);
    //radioData.u16Freq_x10K = 9670;
    //MApp_FMRadio_SaveCh(1, radioData);
}

#endif

