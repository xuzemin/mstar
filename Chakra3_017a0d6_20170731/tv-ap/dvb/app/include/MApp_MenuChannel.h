////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    MApp_MenuChannel.c
/// @author MStar Semiconductor Inc.
/// @brief  Channel Menu Helper Function
///
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_MENUCHANNELPROC_H_
#define _MAPP_MENUCHANNELPROC_H_
#include "msAPI_Tuner.h"
#include "msAPI_DTVSystem.h"
#include "MApp_Scan.h"
/*
#define DEFAULT_DVBC_CONSTEL_TYPE   CAB_QAM64 //[CHINA_TEST]
#define DEFAULT_DVBC_SYMBOL_RATE    6875
#define DEFAULT_DVBC_NIT_FREQUENCY  243000
#define DEFAULT_DVBS2_FREQUENCY      1000000//339000  //for cosmic D268
#define DEFAULT_DVBC_NIT_TIMEOUT    6000
#define DEFAULT_SIPARSER_TIMEOUT    25000 //10000

#define DEFAULT_FREQUENCY_ADJ_STEP  8000//100////500
#define DEFAULT_QAMTYPE_ADJ_STEP    1
#define DEFAULT_QAMTYPE_ADJ_MAX     CAB_QAM256
#define DEFAULT_QAMTYPE_ADJ_MIN     CAB_QAM16
*/

#define DVBC_NIT_FREQ_CNT_MAX       80

#define MAX_TPSOFSAT_NUM       MAX_DTV_S2_MUX_NUMBER

#define INVALID_SAT_ID                   0xFF
typedef enum
{
    SCAN_SAVEALL,
    SCAN_SAVEFREE,

    SCAN_SAVETYPE_NUM
}SCAN_SAVETYPE;

typedef enum
{
    SCAN_SERVICE_ALL,
    SCAN_SERVICE_DTV,
    SCAN_SERVICE_RADIO,

    SCAN_SERVICETYPE_NUM
}SCAN_SERVICETYPE;


extern void MApp_MenuChannel_FullScan_Start(void);
extern void MApp_MenuChannel_BuildScan_Start(void);
extern void MApp_MenuChannel_NetworkScan_Start(void);
extern void MApp_MenuChannel_ManuScan_Start(void);

extern MS_BOOL MApp_MenuChannel_ResetScanSatIDList(void);
extern MS_BOOL MApp_MenuChannel_AddScanSat(MS_U8 SatID);
extern MS_BOOL MApp_MenuChannel_ResetScanTpList(void);
#if(ENABLE_S2) //ohya ++ 20130802
extern MS_BOOL MApp_MenuChannel_AddScanTp(DTVPROGRAMID_M stTpParam);

extern MS_BOOL MApp_MenuChannel_SetLNBPower(MS_EN_LNBPWR_ONOFF enLNBPowe,MS_U8 u8Polarity,MS_BOOL bPorInvert);
#endif

#endif // _MAPP_MENUCHANNELPROC_H_

