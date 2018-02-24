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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define _MAPP_AUDIO_C

/********************************************************************************/
/*              Header Files                        */
/********************************************************************************/
#include "Board.h"
#include "datatype.h"
#include "MsTypes.h"
#include "debug.h"
#include <string.h>

#include "drvGPIO.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_Key.h"
#include "MApp_TV.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Font.h"
#include "MApp_Bitmap.h"
#include "MApp_GlobalVar.h"
//ZUI: #include "MApp_DispMenu.h"
#include "msAPI_audio.h"
#include "MApp_Audio.h"
#include "msAPI_Timer.h"
//ZUI: #include "MApp_UiMenu.h"
//ZUI: #include "MApp_UiMenuFunc.h"
#include "MApp_ChannelChange.h"
#include "apiAUDIO.h"
#include "drvAUDIO.h"
#include "drvXC_HDMI_if.h"
#include "apiXC_Hdmi.h"

#if ENABLE_MxL661_GPO
#include "Tuner.h"
#endif

#if (ENABLE_MADMONITOR)
#include "msAPI_audio.h"
#endif

#include "MApp_ATVProc.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_Video.h"
#include "MApp_UiMenuDef.h" //ZUI:
#include "msAPI_CEC.h"

#if ENABLE_PVR
#include "MApp_PVR.h"
#endif

#if ENABLE_EWS
#include "MApp_EWS.h"
#endif

#include "drvGlobal.h"

#if ENABLE_CI_PLUS
extern BOOL MApp_CI_IsOpMode( void );
extern BOOL MApp_CI_GetOpIso639LangCodeByCicamId( U32 u32CicamId, U8* pu8Iso639LangCode );
extern U32 MApp_CI_GetCurrentOpCicamId( void );
#endif

//--------------------------------------------------------------
// Default prescale table.
// It's shoule be declared in each board header file.
//--------------------------------------------------------------
#ifndef S4_AUDIO_PATH_SETTING

 #define Prescale_0dB               0x6F

 #define Prescale_MainSpeaker_DTV   Prescale_0dB-9
 #define Prescale_LineOut_DTV       Prescale_0dB-9
 #define Prescale_SifOut_DTV        Prescale_0dB-9  // Output DTV
 #define Prescale_SpdifOut_DTV      0x00

 #define Prescale_MainSpeaker_ATV   Prescale_0dB-5
 #define Prescale_LineOut_ATV       Prescale_0dB-5
 #define Prescale_SifOut_ATV        Prescale_0dB-5  // Output ATV
 #define Prescale_SpdifOut_ATV      0x00

 #define Prescale_MainSpeaker_AV    Prescale_0dB
 #define Prescale_LineOut_AV        Prescale_0dB
 #define Prescale_SifOut_AV         Prescale_0dB-5  // Output ATV
 #define Prescale_SpdifOut_AV       0x00

 #define Prescale_MainSpeaker_PC    Prescale_0dB
 #define Prescale_LineOut_PC        Prescale_0dB
 #define Prescale_SifOut_PC         Prescale_0dB-5  // Output ATV
 #define Prescale_SpdifOut_PC       0x00

 #define Prescale_MainSpeaker_HDMI  Prescale_0dB-9
 #define Prescale_LineOut_HDMI      Prescale_0dB-9
 #define Prescale_SifOut_HDMI       Prescale_0dB-5  // Output ATV
 #define Prescale_SpdifOut_HDMI     0x00

#endif



U16 TvVolumeTable[] =
//              Volume  Table     (High Byte : Integer part  ; Low Byte : Fraction part)
{ //         1           2                3             4         5            6            7                 8         9            10
                                                                                                       0x7F00,    //  00
    0x4700,    0x4400,    0x4100,    0x3E00,    0x3C00,    0x3A00,    0x3800,    0x3600,    0x3400,    0x3200,    //  10
    0x3000,    0x2E00,    0x2D00,    0x2C00,    0x2B00,    0x2A00,    0x2900,    0x2800,    0x2700,    0x2600,    //  20
    0x2500,    0x2400,    0x2300,    0x2200,    0x2100,    0x2000,    0x1F00,    0x1E04,    0x1E00,    0x1D04,    //  30
    0x1D00,    0x1C04,    0x1C00,    0x1B04,    0x1B00,    0x1A04,    0x1A00,    0x1904,    0x1900,    0x1804,    //  40
    0x1800,    0x1704,    0x1700,    0x1604,    0x1600,    0x1504,    0x1502,    0x1500,    0x1406,    0x1404,    //  50
    0x1402,    0x1400,    0x1306,    0x1304,    0x1302,    0x1300,    0x1206,    0x1204,    0x1202,    0x1200,    //  60
    0x1106,    0x1104,    0x1102,    0x1100,    0x1006,    0x1004,    0x1002,    0x1000,    0x0F07,    0x0F06,    //  70
    0x0F05,    0x0F04,    0x0F03,    0x0F02,    0x0F01,    0x0F00,    0x0E07,    0x0E06,    0x0E05,    0x0E04,    //  80
    0x0E03,    0x0E02,    0x0E01,    0x0E00,    0x0D07,    0x0D06,    0x0D05,    0x0D04,    0x0D03,    0x0D02,    //  90
    0x0D01,    0x0D00,    0x0C07,    0x0C06,    0x0C05,    0x0C04,    0x0C03,    0x0C02,    0x0C01,    0x0C00    //  100
};


U16 TvVolumeTable_HDMI[] =
//              Volume  Table     (High Byte : Integer part  ; Low Byte : Fraction part)
{ //  1           2          3         4         5          6           7           8         9          10
                                                                                                       0x7F00,    //  00
    0x4700,    0x4400,    0x4100,    0x3E00,    0X3600,    0x2800,    0x3800,    0x3600,    0x3400,    0X3000,    //  10
    0x3000,    0x2E00,    0x2D00,    0x2C00,    0X2E00,    0x2A00,    0x2900,    0x2800,    0x2700,    0X2D00,    //  20
    0x2500,    0x2400,    0x2300,    0x2200,    0X2C00,    0x2000,    0x1F00,    0x1E04,    0x1E00,    0X2B00,    //  30
    0x1D00,    0x1C04,    0x1C00,    0x1B04,    0X2900,    0x1A04,    0x1A00,    0x1904,    0x1900,    0X2700,    //  40
    0x1800,    0x1704,    0x1700,    0x1604,    0X2500,    0x1504,    0x1502,    0x1500,    0x1406,    0X2400,    //  50
    0x1402,    0x1400,    0x1306,    0x1304,    0X2300,    0x1300,    0x1206,    0x1204,    0x1202,    0X2200,    //  60
    0x1106,    0x1104,    0x1102,    0x1100,    0X2100,    0x1004,    0x1002,    0x1000,    0x0F07,    0X2000,    //  70
    0x0F05,    0x0F04,    0x0F03,    0x0F02,    0X1D00,    0x0F00,    0x0E07,    0x0E06,    0x0E05,    0x1C04,    //  80
    0x0E03,    0x0E02,    0x0E01,    0x0E00,    0x1B04,    0x0D06,    0x0D05,    0x0D04,    0x0D03,    0x1B00,    //  90
    0x0D01,    0x0D00,    0x0C07,    0x0C06,    0X1A04,    0x0C04,    0x0C03,    0x0C02,    0x0C01,    0x1A00    //  100
};
#if(ENABLE_AUDIO_SURROUND_DBX == ENABLE)
////////////////////////////////DBX table ////////////////////////////////
/** Total Sonics presets */
MS_U32 APP_dbx_TotSonDM[1][95] = {
// Total Sonics TOTSON_STANDARD_TABLE
{
0x000001, 0x000064, 0xFFEE0D, 0x000023, 0x000064, 0x000BB9, 0x007333, 0x000000,
0x000000, 0x000000, 0x001400, 0xFFD800, 0xFFE200, 0x000000, 0x000000, 0x000000,
0x002AD9, 0x000EDB, 0x00007F, 0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0xFFEE0D,
0x000023, 0x000064, 0x000BB9, 0x007333, 0x000000, 0x000000, 0x000000, 0x001400,
0xFFD800, 0xFFE200, 0x000000, 0x000000, 0x000000, 0x002AD9, 0x000EDB, 0x00007F,
0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0x000001, 0x0003E8, 0xFFC400, 0x000000,
0x000000, 0x000001, 0x000000, 0xFFFFFF, 0x006400, 0x000004, 0x000001, 0x000000,
0x000500, 0x000000, 0x000000, 0x000000, 0x000000, 0x000001, 0x0000FA, 0x000001,
0xFFF600, 0x000000, 0x000000, 0x0000C8, 0x0001F4, 0x000023, 0x002A66, 0x002A66,
0x000000, 0x0004C1, 0x000000, 0xFFFC00, 0x000000, 0x000000, 0x000007, 0x000001,
0x0000C8, 0x000000, 0x000001, 0x000064, 0xFFF400, 0x000004, 0x000032, 0x0001F4,
0x007800, 0x000000, 0x000000, 0x016BFF, 0x001DB5, 0x0002F9, 0x16A77E,
},

};

MS_U32  APP_dbx_TotSonPM[1][100] = {
// Total Sonics TOTSON_STANDARD_TABLE
{
0x814A2A, 0x3EB922, 0x0000D3, 0x0001A5, 0x0000D3,
0x814A2A, 0x3EB922, 0x3F5BBE, 0x814884, 0x3F5BBE,
0xC329DF, 0x000000, 0x3EEB1E, 0xC214FD, 0x000000,
0xC1CC56, 0x000000, 0x400000, 0xC1CC56, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0x833942, 0x3CDB04, 0x3E6870, 0x832F20, 0x3E6870,
0x86718C, 0x39DD95, 0x031136, 0x000000, 0xFCEECA,
0x88CFF6, 0x377D9F, 0x400000, 0x88CFF6, 0x377D9F,
0x887475, 0x38C4CF, 0x417DD8, 0x887475, 0x3746F7,
0xA04892, 0x23BD0C, 0x400000, 0xA04892, 0x23BD0C,
0xAE164A, 0x1A02C0, 0x400000, 0xAE164A, 0x1A02C0,
0xC69952, 0x0BD8A2, 0x400000, 0xC69952, 0x0BD8A2,
0xE0F8FE, 0x007486, 0x400000, 0xE0F8FE, 0x007486,
0xF7A72F, 0xF95C11, 0x400000, 0xF7A72F, 0xF95C11,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x814A2A, 0x3EB922, 0x3F5BBE, 0x814884, 0x3F5BBE,
},

};


/** Total Volume presets */
MS_U32  APP_dbx_TotVolDM[2][95] = {
// Total Volume TOTVOL_NORMAL
{
0x000001, 0x0001C2, 0xFFE200, 0x000023, 0x000064, 0x000BB9, 0x006000, 0x006000,
0x000000, 0x000000, 0x000600, 0xFFD800, 0xFFE480, 0x000000, 0x000000, 0x000000,
0x002AD9, 0x000EDB, 0x00007F, 0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0xFFE200,
0x000023, 0x000064, 0x000BB9, 0x006000, 0x006000, 0x000000, 0x000000, 0x000600,
0xFFD800, 0xFFE480, 0x000000, 0x000000, 0x000000, 0x002AD9, 0x000EDB, 0x00007F,
0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0x000001, 0x0003E8, 0xFFC400, 0x000000,
0x000000, 0x000001, 0x000000, 0x19999A, 0x006400, 0x000004, 0x000001, 0x000000,
0x000500, 0x000000, 0x000000, 0x000000, 0x000000, 0x000001, 0x0000FA, 0x000001,
0xFFF600, 0x000000, 0x000000, 0x0000C8, 0x0001F4, 0x000023, 0x002A66, 0x002A66,
0x000000, 0x0004C1, 0x000000, 0xFFFC00, 0x000000, 0x000000, 0x000007, 0x000001,
0x0000C8, 0x000000, 0x000001, 0x000064, 0xFFF400, 0x000004, 0x000032, 0x0001F4,
0x007800, 0x000000, 0x000000, 0x016BFF, 0x001DB5, 0x0002F9, 0x16A77E,
},

// Total Volume TOTVOL_NIGHT
{
0x000001, 0x0001C2, 0xFFE200, 0x000023, 0x000064, 0x000BB9, 0x007333, 0x007333,
0x000000, 0x000000, 0x000600, 0xFFD800, 0xFFE480, 0x000000, 0x000000, 0x000000,
0x002AD9, 0x000EDB, 0x00007F, 0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0xFFE200,
0x000023, 0x000064, 0x000BB9, 0x007333, 0x007333, 0x000000, 0x000000, 0x000600,
0xFFD800, 0xFFE480, 0x000000, 0x000000, 0x000000, 0x002AD9, 0x000EDB, 0x00007F,
0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0x000001, 0x0003E8, 0xFFC400, 0x000000,
0x000000, 0x000001, 0x000000, 0x19999A, 0x006400, 0x000004, 0x000001, 0xFFF400,
0x000500, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x0000FA, 0x000000,
0xFFF600, 0x000000, 0x000000, 0x0000C8, 0x0001F4, 0x000023, 0x002A66, 0x002A66,
0x000000, 0x0004C1, 0x000001, 0xFFFC00, 0x000000, 0x000000, 0x000007, 0x000001,
0x0000C8, 0x000000, 0x000001, 0x000064, 0xFFF400, 0x000004, 0x000032, 0x0001F4,
0x007800, 0x000000, 0x000000, 0x016BFF, 0x001DB5, 0x0002F9, 0x16A77E,
},

};

MS_U32  APP_dbx_TotVolPM[2][100] = {
// Total Volume TOTVOL_NORMAL
{
0x85CCD0, 0x3A7398, 0x00101A, 0x002034, 0x00101A,
0x85CCD0, 0x3A7398, 0x3D29B2, 0x85AC9C, 0x3D29B2,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0x833942, 0x3CDB04, 0x3E6870, 0x832F20, 0x3E6870,
0x86718C, 0x39DD95, 0x031136, 0x000000, 0xFCEECA,
0x88CFF6, 0x377D9F, 0x400000, 0x88CFF6, 0x377D9F,
0x887475, 0x38C4CF, 0x417DD8, 0x887475, 0x3746F7,
0xA04892, 0x23BD0C, 0x400000, 0xA04892, 0x23BD0C,
0xAE164A, 0x1A02C0, 0x400000, 0xAE164A, 0x1A02C0,
0xC69952, 0x0BD8A2, 0x400000, 0xC69952, 0x0BD8A2,
0xE0F8FE, 0x007486, 0x400000, 0xE0F8FE, 0x007486,
0xF7A72F, 0xF95C11, 0x400000, 0xF7A72F, 0xF95C11,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x814A2A, 0x3EB922, 0x3F5BBE, 0x814884, 0x3F5BBE,
},

// Total Volume TOTVOL_NIGHT
{
0x85CCD0, 0x3A7398, 0x00101A, 0x002034, 0x00101A,
0x85CCD0, 0x3A7398, 0x3D29B2, 0x85AC9C, 0x3D29B2,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0xC46796, 0x000000, 0x400000, 0xC46796, 0x000000,
0x833942, 0x3CDB04, 0x3E6870, 0x832F20, 0x3E6870,
0x86718C, 0x39DD95, 0x031136, 0x000000, 0xFCEECA,
0x88CFF6, 0x377D9F, 0x400000, 0x88CFF6, 0x377D9F,
0x887475, 0x38C4CF, 0x417DD8, 0x887475, 0x3746F7,
0xA04892, 0x23BD0C, 0x400000, 0xA04892, 0x23BD0C,
0xAE164A, 0x1A02C0, 0x400000, 0xAE164A, 0x1A02C0,
0xC69952, 0x0BD8A2, 0x400000, 0xC69952, 0x0BD8A2,
0xE0F8FE, 0x007486, 0x400000, 0xE0F8FE, 0x007486,
0xF7A72F, 0xF95C11, 0x400000, 0xF7A72F, 0xF95C11,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x814A2A, 0x3EB922, 0x3F5BBE, 0x814884, 0x3F5BBE,
},

};


/** Total Surround presets */
MS_U32  APP_dbx_TotSurDM[1][95] = {
//Total Surround TOTSUR_ON
{
0x000001, 0x0001C2, 0xFFEC00, 0x000023, 0x000064, 0x000BB9, 0x007333, 0x007333,
0x000000, 0x000000, 0x000600, 0xFFD800, 0xFFE480, 0x000000, 0x000000, 0x000000,
0x002AD9, 0x000EDB, 0x00007F, 0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0xFFEC00,
0x000023, 0x000064, 0x000BB9, 0x007333, 0x007333, 0x000000, 0x000000, 0x000600,
0xFFD800, 0xFFE480, 0x000000, 0x000000, 0x000000, 0x002AD9, 0x000EDB, 0x00007F,
0x000EDB, 0x009446, 0x00007F, 0x0004F4, 0x000001, 0x0003E8, 0xFFC400, 0x000000,
0x000000, 0x000001, 0x000000, 0x19999A, 0x006400, 0x000004, 0x000001, 0x000000,
0x000500, 0x000000, 0x000000, 0x000000, 0x000000, 0x000001, 0x0000FA, 0x000001,
0x0007D3, 0x000000, 0x000000, 0x000064, 0x000064, 0x000023, 0x002A66, 0x002A66,
0x000000, 0x0004C1, 0x000000, 0x0003FA, 0x000000, 0x000000, 0x000007, 0x000001,
0x0000C8, 0x000000, 0x000001, 0x000064, 0xFFF400, 0x000004, 0x000032, 0x0001F4,
0x007800, 0x000000, 0x000000, 0x016BFF, 0x001DB5, 0x0002F9, 0x16A77E,
},

};
MS_U32  APP_dbx_TotSurPM[1][100] = {
// Total Surround TOTSUR_ON
{
0x85CCD0, 0x3A7398, 0x00101A, 0x002034, 0x00101A,
0x85CCD0, 0x3A7398, 0x3D29B2, 0x85AC9C, 0x3D29B2,
0x814A1D, 0x3EB92E, 0x405E2D, 0x814C85, 0x3E5D69,
0x000000, 0x000000, 0x400000, 0x000000, 0x000000,
0x000000, 0x000000, 0x400000, 0x000000, 0x000000,
0x000000, 0x000000, 0x400000, 0x000000, 0x000000,
0x833942, 0x3CDB04, 0x3E6870, 0x832F20, 0x3E6870,
0x86718C, 0x39DD95, 0x031136, 0x000000, 0xFCEECA,
0x88CFF6, 0x377D9F, 0x400000, 0x88CFF6, 0x377D9F,
0x887475, 0x38C4CF, 0x417DD8, 0x887475, 0x3746F7,
0xA04892, 0x23BD0C, 0x400000, 0xA04892, 0x23BD0C,
0xAE164A, 0x1A02C0, 0x400000, 0xAE164A, 0x1A02C0,
0xC69952, 0x0BD8A2, 0x400000, 0xC69952, 0x0BD8A2,
0xE0F8FE, 0x007486, 0x400000, 0xE0F8FE, 0x007486,
0xF7A72F, 0xF95C11, 0x400000, 0xF7A72F, 0xF95C11,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x000343, 0x000685, 0x000343,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x829442, 0x3D78C9, 0x3EB922, 0x828DBC, 0x3EB922,
0x814A2A, 0x3EB922, 0x3F5BBE, 0x814884, 0x3F5BBE,
},

};

#endif
////////////////////////////////DBX table ////////////////////////////////

void MApp_Audio_Copy_DBX_Parameter(void)
{
#if(ENABLE_AUDIO_SURROUND_DBX == ENABLE)
    MApi_AUDIO_COPY_Parameter(DBX_COPY_TotSonDM,APP_dbx_TotSonDM[0], (sizeof(APP_dbx_TotSonDM)/sizeof(MS_U32)));
    MApi_AUDIO_COPY_Parameter(DBX_COPY_TotSonPM,APP_dbx_TotSonPM[0], (sizeof(APP_dbx_TotSonPM)/sizeof(MS_U32)));
    MApi_AUDIO_COPY_Parameter(DBX_COPY_TotVolDM,APP_dbx_TotVolDM[0], (sizeof(APP_dbx_TotVolDM)/sizeof(MS_U32)));
    MApi_AUDIO_COPY_Parameter(DBX_COPY_TotVolPM,APP_dbx_TotVolPM[0], (sizeof(APP_dbx_TotVolPM)/sizeof(MS_U32)));
    MApi_AUDIO_COPY_Parameter(DBX_COPY_TotSurDM,APP_dbx_TotSurDM[0], (sizeof(APP_dbx_TotSurDM)/sizeof(MS_U32)));
    MApi_AUDIO_COPY_Parameter(DBX_COPY_TotSurPM,APP_dbx_TotSurPM[0], (sizeof(APP_dbx_TotSurPM)/sizeof(MS_U32)));
#endif
}

#if 1//(TV_SYSTEM == TV_PAL)
  #if 1//((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210))    //threshold for VIF
    THR_TBL_TYPE code AuSifInitThreshold_A2[] =
    {
         {0x03 ,0x00 ,} ,     //A2_M    CARRIER1_ON_AMP
         {0x02 ,0x00 ,} ,     //A2_M    CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //A2_M    CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //A2_M    CARRIER1_OFF_NSR
         {0x02 ,0x00 ,} ,     //A2_M    CARRIER2_ON_AMP
         {0x01 ,0x80 ,} ,     //A2_M    CARRIER2_OFF_AMP
         {0x11 ,0x00 ,} ,     //A2_M    CARRIER2_ON_NSR
         {0x15 ,0x00 ,} ,     //A2_M    CARRIER2_OFF_NSR
         {0x02 ,0x80 ,} ,     //A2_M    A2_PILOT_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_M    A2_PILOT_OFF_AMP

         {0x03 ,0x00 ,} ,     //A2_BG   CARRIER1_ON_AMP
         {0x02 ,0x00 ,} ,     //A2_BG   CARRIER1_OFF_AMP
         {0x20 ,0x00 ,} ,     //A2_BG   CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //A2_BG   CARRIER1_OFF_AMP
         {0x02 ,0x00 ,} ,     //A2_BG   CARRIER2_ON_AMP
         {0x01 ,0x80 ,} ,     //A2_BG   CARRIER2_OFF_AMP
         {0x11 ,0x00 ,} ,     //A2_BG   CARRIER2_ON_NSR
         {0x30 ,0x00 ,} ,     //A2_BG   CARRIER2_OFF_NSR
         {0x02 ,0x80 ,} ,     //A2_BG   A2_PILOT_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_BG   A2_PILOT_OFF_AMP

         {0x03 ,0x00 ,} ,     //A2_DK   CARRIER1_ON_AMP
         {0x02 ,0x00 ,} ,     //A2_DK   CARRIER1_OFF_AMP
         {0x13 ,0x00 ,} ,     //A2_DK   CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //A2_DK   CARRIER1_OFF_NSR
         {0x02 ,0x00 ,} ,     //A2_DK   CARRIER2_ON_AMP
         {0x01 ,0x80 ,} ,     //A2_DK   CARRIER2_OFF_AMP
         {0x11 ,0x00 ,} ,     //A2_DK   CARRIER2_ON_NSR
         {0x15 ,0x00 ,} ,     //A2_DK   CARRIER2_OFF_NSR
         {0x02 ,0x80 ,} ,     //A2_DK   A2_PILOT_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_DK   A2_PILOT_OFF_AMP

         {0x03 ,0x00 ,} ,     //FM_I   CARRIER1_ON_AMP
         {0x02 ,0x00 ,} ,     //FM_I   CARRIER1_OFF_AMP
         {0x0E ,0x00 ,} ,     //FM_I   CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //FM_I   CARRIER1_OFF_NSR

         {0x00 ,0xA0 ,} ,     //AM   CARRIER1_ON_AMP
         {0x00 ,0x80 ,} ,     //AM   CARRIER1_OFF_AMP

         {0x23 ,0x00 ,} ,     //NICAM_BG  NICAM_ON_SIGERR
         {0x3f ,0x00 ,} ,     //NICAM_BG  NICAM_OFF_SIGERR

         {0x23 ,0x00 ,} ,     //NICAM_I  NICAM_ON_SIGERR
         {0x3f ,0x00 ,} ,     //NICAM_I  NICAM_OFF_SIGERR

         {0x02 ,0x00 ,} ,     //HIDEV_M  CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //HIDEV_M  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_M  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_M  CARRIER1_OFF_NSR

         {0x02 ,0x00 ,} ,     //HIDEV_BG  CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //HIDEV_BG  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_BG  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_BG  CARRIER1_OFF_NSR

         {0x02 ,0x00 ,} ,     //HIDEV_DK  CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //HIDEV_DK  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_DK  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_DK  CARRIER1_OFF_NSR

         {0x02 ,0x00 ,} ,     //HIDEV_I  CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //HIDEV_I  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_I  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_I  CARRIER1_OFF_NSR

         {0x5A , 0x5A } ,    // Delimiter for extension threshold setting
         {0xA5 , 0xA5 } ,    // Delimiter for extension threshold setting
         {0x40 , 0x00 } ,    // A2_M PILOT_PHASE_ON_THD
         {0x50 , 0x00 } ,    // A2_M PILOT_PHASE_OFF_THD
         {0x0A , 0x00 } ,    // A2_M POLIT_MODE_VALID_RATIO
         {0x00 , 0x90 } ,    // A2_M POLIT_MODE_INVALID_RATIO
         {0xFF , 0xFF } ,    // separtor
         {0x40 , 0x00 } ,    // A2_BG PILOT_PHASE_ON_THD
         {0x50 , 0x00 } ,    // A2_BG PILOT_PHASE_OFF_THD
         {0x0A , 0x00 } ,    // A2_BG POLIT_MODE_VALID_RATIO
         {0x00 , 0x90 } ,    // A2_BG POLIT_MODE_INVALID_RATIO
         {0xFF , 0xFF } ,    // separtor
         {0x40 , 0x00 } ,    // A2_DK PILOT_PHASE_ON_THD
         {0x50 , 0x00 } ,    // A2_DK PILOT_PHASE_OFF_THD
         {0x0A , 0x00 } ,    // A2_DK POLIT_MODE_VALID_RATIO
         {0x00 , 0x90 } ,    // A2_DK POLIT_MODE_INVALID_RATIO
         {0xFF , 0xFF } ,    // separtor
    };
  #else
    THR_TBL_TYPE code AuSifInitThreshold[] =
    {
         {0x01 ,0x50 ,} ,     //A2_M    CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_M    CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //A2_M    CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //A2_M    CARRIER1_OFF_NSR
         {0x01 ,0x00 ,} ,     //A2_M    CARRIER2_ON_AMP
         {0x00 ,0x80 ,} ,     //A2_M    CARRIER2_OFF_AMP
         {0x11 ,0x00 ,} ,     //A2_M    CARRIER2_ON_NSR
         {0x15 ,0x00 ,} ,     //A2_M    CARRIER2_OFF_NSR
         {0x02 ,0x80 ,} ,     //A2_M    A2_PILOT_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_M    A2_PILOT_OFF_AMP

         {0x01 ,0x50 ,} ,     //A2_BG   CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_BG   CARRIER1_OFF_AMP
         {0x20 ,0x00 ,} ,     //A2_BG   CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //A2_BG   CARRIER1_OFF_AMP
         {0x00 ,0x40 ,} ,     //A2_BG   CARRIER2_ON_AMP
         {0x00 ,0x30 ,} ,     //A2_BG   CARRIER2_OFF_AMP
         {0x11 ,0x00 ,} ,     //A2_BG   CARRIER2_ON_NSR
         {0x30 ,0x00 ,} ,     //A2_BG   CARRIER2_OFF_NSR
         {0x02 ,0x80 ,} ,     //A2_BG   A2_PILOT_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_BG   A2_PILOT_OFF_AMP

         {0x01 ,0x50 ,} ,     //A2_DK   CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_DK   CARRIER1_OFF_AMP
         {0x13 ,0x00 ,} ,     //A2_DK   CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //A2_DK   CARRIER1_OFF_NSR
         {0x00 ,0x40 ,} ,     //A2_DK   CARRIER2_ON_AMP
         {0x00 ,0x30 ,} ,     //A2_DK   CARRIER2_OFF_AMP
         {0x11 ,0x00 ,} ,     //A2_DK   CARRIER2_ON_NSR
         {0x15 ,0x00 ,} ,     //A2_DK   CARRIER2_OFF_NSR
         {0x02 ,0x80 ,} ,     //A2_DK   A2_PILOT_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_DK   A2_PILOT_OFF_AMP

         {0x01 ,0x50 ,} ,     //FM_I   CARRIER1_ON_AMP
         {0x01 ,0x00 ,} ,     //FM_I   CARRIER1_OFF_AMP
         {0x0E ,0x00 ,} ,     //FM_I   CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //FM_I   CARRIER1_OFF_NSR

         {0x07 ,0x00 ,} ,     //AM   CARRIER1_ON_AMP
         {0x06 ,0x00 ,} ,     //AM   CARRIER1_OFF_AMP

         {0x23 ,0x00 ,} ,     //NICAM_BG  NICAM_ON_SIGERR
         {0x3f ,0x00 ,} ,     //NICAM_BG  NICAM_OFF_SIGERR

         {0x23 ,0x00 ,} ,     //NICAM_I  NICAM_ON_SIGERR
         {0x3f ,0x00 ,} ,     //NICAM_I  NICAM_OFF_SIGERR

         {0x00 ,0x80 ,} ,     //HIDEV_M  CARRIER1_ON_AMP
         {0x00 ,0x40 ,} ,     //HIDEV_M  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_M  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_M  CARRIER1_OFF_NSR

         {0x00 ,0xB0 ,} ,     //HIDEV_BG  CARRIER1_ON_AMP
         {0x00 ,0x60 ,} ,     //HIDEV_BG  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_BG  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_BG  CARRIER1_OFF_NSR

         {0x00 ,0xB0 ,} ,     //HIDEV_DK  CARRIER1_ON_AMP
         {0x00 ,0x60 ,} ,     //HIDEV_DK  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_DK  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_DK  CARRIER1_OFF_NSR

         {0x00 ,0xB0 ,} ,     //HIDEV_I  CARRIER1_ON_AMP
         {0x00 ,0x60 ,} ,     //HIDEV_I  CARRIER1_OFF_AMP
         {0x12 ,0x00 ,} ,     //HIDEV_I  CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //HIDEV_I  CARRIER1_OFF_NSR

         {0x5A , 0x5A } ,    // Delimiter for extension threshold setting
         {0xA5 , 0xA5 } ,    // Delimiter for extension threshold setting
         {0x40 , 0x00 } ,    // A2_M PILOT_PHASE_ON_THD
         {0x50 , 0x00 } ,    // A2_M PILOT_PHASE_OFF_THD
         {0x0A , 0x00 } ,    // A2_M POLIT_MODE_VALID_RATIO
         {0x00 , 0x90 } ,    // A2_M POLIT_MODE_INVALID_RATIO
         {0xFF , 0xFF } ,    // separtor
         {0x40 , 0x00 } ,    // A2_BG PILOT_PHASE_ON_THD
         {0x50 , 0x00 } ,    // A2_BG PILOT_PHASE_OFF_THD
         {0x0A , 0x00 } ,    // A2_BG POLIT_MODE_VALID_RATIO
         {0x00 , 0x90 } ,    // A2_BG POLIT_MODE_INVALID_RATIO
         {0xFF , 0xFF } ,    // separtor
         {0x40 , 0x00 } ,    // A2_DK PILOT_PHASE_ON_THD
         {0x50 , 0x00 } ,    // A2_DK PILOT_PHASE_OFF_THD
         {0x0A , 0x00 } ,    // A2_DK POLIT_MODE_VALID_RATIO
         {0x00 , 0x90 } ,    // A2_DK POLIT_MODE_INVALID_RATIO
         {0xFF , 0xFF } ,    // separtor
    };
  #endif

#endif

#if 1//(TV_SYSTEM == TV_NTSC)
    THR_TBL_TYPE code AuSifInitThreshold_BTSC[] =
    {
         {0x33 ,0x33 ,} ,     //BTSC_MONO_ON_NSR_THRESHOLD
         {0x7f ,0xff ,} ,     //BTSC_MONO_OFF_NSR_THRESHOLD
         {0x14 ,0x00 ,} ,     //BTSC_PILOT_ON_AMPLITUDE_THRESHOLD
         {0x10 ,0x00 ,} ,     //BTSC_PILOT_OFF_AMPLITUDE_THRESHOLD
         {0x40 ,0x00 ,} ,     //BTSC_SAP_ON_NSR_THRESHOLD
         {0x7F ,0xFF ,} ,     //BTSC_SAP_OFF_NSR_THRESHOLD
         {0x33 ,0x33 ,} ,     //BTSC_STEREO_ON_THRESHOLD
         {0x7f ,0xff ,} ,     //BTSC_STEREO_OFF_THRESHOLD
         {0x00 ,0x40 ,} ,     //BTSC_SAP_ON_AMPLITUDE_THRESHOLD
         {0x00 ,0x28 ,} ,     //BTSC_SAP_OFF_AMPLITUDE_THRESHOLD
    };

/*
    THR_TBL_TYPE code AuSifInitThreshold_A2_M[] =
    {
         {0x00 ,0x11 ,} ,     //A2_M    CARRIER1_ON_AMP
         {0x00 ,0x0E ,} ,     //A2_M    CARRIER1_OFF_AMP
         {0x1A ,0x00 ,} ,     //A2_M    CARRIER1_ON_NSR
         {0x7F ,0xFF ,} ,     //A2_M    CARRIER1_OFF_NSR
         {0x01 ,0x00 ,} ,     //A2_M    CARRIER2_ON_AMP
         {0x00 ,0x80 ,} ,     //A2_M    CARRIER2_OFF_AMP
         {0x0D ,0x00 ,} ,     //A2_M    CARRIER2_ON_NSR
         {0x13 ,0x00 ,} ,     //A2_M    CARRIER2_OFF_NSR
         {0x02 ,0x80 ,} ,     //A2_M    A2_PILOT_ON_AMP
         {0x01 ,0x00 ,} ,     //A2_M    A2_PILOT_OFF_AMP
    }; */

#endif

//---------------------------------------------------------------

/********************************************************************************/
/*              Local                           */
/********************************************************************************/

#define THRESHOLD_MTS_CHANGED (3)
//static U8 u8MtsThresholdCount = 0;
//static U32 u32MonitorMtsTimer;

#define MTS_MONITOR_POLLING_TIMES (100)
#define MTS_MONITOR_MTSCHANGED_TIMES (500)
#define POLLING_STEREO_COUNTS (20)


#define AC3_MONITOR_TIMES (600)

#define MTS_DBINFO(x) //x


/********************************************************************************/
/*              Functions                           */
/********************************************************************************/
#if ENABLE_DTV

#if ENABLE_EWS
BOOLEAN MApp_Audio_SetEWSAudio(MS_EWSAUDIOINFO mEwsAudioinfo)
{
    //AUD_INFO stAudioStreamInfo;
    U16 u16EWSAudioPID = mEwsAudioinfo.u16EWSAudioPID;
    SI_AUDIOSTREAM_TYPE eEWSAudioType = (SI_AUDIOSTREAM_TYPE)mEwsAudioinfo.u16EWSAudioType;

    printf("\r\n>>>MApp_Audio_SetEWSAudio  Type=%x  PID=%x", eEWSAudioType, u16EWSAudioPID);

    //move up, for invalid audio case, should stop audio
    /* mute during audio language change, to avoid transition noise, KH Tsai */
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    /* stop audio decoder */
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);

    /* stop audio filter */
    //msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AUDIO_FID));
    MApp_Demux_Stop_Filter_Audio();

    /* delay before audio & demux stop to allow enough audio decoding samples to do fade out,
        make the sound smooth, KH Tsai */
    // Already mute at the begin of this function, why need delay??
    //msAPI_Timer_Delayms(256);

    {
        // start filter should be after than start audio decoder to prevent audio ES buffer overflow
        /* set audio PID & start filter */
        //msAPI_DMX_StartFilter( stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID));
        MApp_Demux_Start_Filter_Audio(u16EWSAudioPID);
    }


    AUDIOSTREAM_TYPE eAudType = msAPI_CM_SIAudStreamType_To_AudStreamType(eEWSAudioType);

    /* set decoder system and reload firmware code */
    MApp_ChannelChange_Set_Audio_Decoder_System( eAudType );

    //MApi_AUDIO_SetSystem((En_DVB_decSystemType)stAudioStreamInfo.wAudType);

    /* start audio decoder */
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);

    //unmute all
    MApp_EWS_AudioMuteFlag(TRUE);

    /* unmute the sound */
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    return TRUE;
}
#endif // #if ENABLE_EWS

#if(ENABLE_DVB)
BOOLEAN MApp_Audio_SetAudioLanguage(U8 u8AudSelectedIndex)
{
    AUD_INFO stAudioStreamInfo;

    //move up, for invalid audio case, should stop audio
    /* mute during audio language change, to avoid transition noise, KH Tsai */
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    /* stop audio filter */
    //msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AUDIO_FID));
    MApp_Demux_Stop_Filter_Audio();

    /* stop audio decoder */
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);

    /* delay before audio & demux stop to allow enough audio decoding samples to do fade out,
        make the sound smooth, KH Tsai */
    // Already mute at the begin of this function, why need delay??
    //msAPI_Timer_Delayms(256);

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        MApp_PVR_PlaybackAudioStopLanguage(g_u8AudLangSelected);
    }
    else
#endif
    {
        /* stop audio filter */
        //msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AUDIO_FID));
    }

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        if (!MApp_PVR_PlaybackAudioGetStreamInfo(&stAudioStreamInfo, u8AudSelectedIndex))
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            return FALSE;
        }
    }
    else
#endif
    {
        if( TRUE != msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &stAudioStreamInfo, u8AudSelectedIndex) )
        {
            /* unmute the sound */
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            return FALSE;
        }
    }

    g_u8AudLangSelected=u8AudSelectedIndex;

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        MApp_PVR_PlaybackAudioSelectLanguage(g_u8AudLangSelected);
    }
    else
#endif
    {
        // start filter should be after than start audio decoder to prevent audio ES buffer overflow
        /* set audio PID & start filter */
        //msAPI_DMX_StartFilter( stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID));
        MApp_Demux_Start_Filter_Audio(stAudioStreamInfo.wAudPID);
    }

    AUDIOSTREAM_TYPE eAudStreamType = msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudioStreamInfo);

#if ENABLE_PVR
    if ((MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT) || (!MApp_PVR_IsPlaybacking()))
    {
        g_u16Current_PVR_AudioPID = stAudioStreamInfo.wAudPID;
        //g_wCurrent_AudioType = stAudioStreamInfo.wAudType;
        g_wCurrent_AudioType = eAudStreamType;
    }
#endif

    /* set decoder system and reload firmware code */
    DEBUG_AU_LOAD_CODE(printf("eAudStreamType=%u\n", eAudStreamType););
    switch(eAudStreamType)
    {
        case E_AUDIOSTREAM_MPEG:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_MPEG);
            break;

        case E_AUDIOSTREAM_AC3:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AC3);
            break;

        case E_AUDIOSTREAM_AC3P:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3P);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AC3P);
            break;

        case E_AUDIOSTREAM_MPEG4:
        case E_AUDIOSTREAM_AAC:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AAC);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AACP);
            break;

        case E_AUDIOSTREAM_DRA:
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_DRA);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_RESERVE1);
            break;
        default:
            break;
    };

    //MApi_AUDIO_SetSystem((En_DVB_decSystemType)stAudioStreamInfo.wAudType);

    MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, TRUE);
    /* start audio decoder */
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
    msAPI_Timer_Delayms(30);
    MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, FALSE);

    /* unmute the sound */
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

#if ENABLE_PVR
    if ((MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT) && (!MApp_PVR_IsPlaybacking()))
    {
        //switch audio when timeshift but not playbacking,we should mute SPDIF out.
        MApi_AUDIO_SPDIF_SetMute(TRUE);
    }
    else if ((MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT) && (MApp_PVR_IsPlaybacking()))
    {
        //fixed: switch audio when timeshift then playing,it will not SPDIF out.
      #if(ENABLE_CHECK_SPDIF_MUTE_STATUS)
        if(MApi_AUDIO_SPDIF_GetMute_Status() == 1)
        {
              MApi_AUDIO_SPDIF_SetMute(FALSE);
        }
      #endif
    }
#endif

#if MHEG5_ENABLE
    g_u16Current_AudioPID = stAudioStreamInfo.wAudPID;
    //g_u16Current_AudioType = stAudioStreamInfo.wAudType;
    g_u16Current_AudioType = eAudStreamType;
#endif

    if(E_AUDIOSTREAM_AC3==eAudStreamType || E_AUDIOSTREAM_AC3P==eAudStreamType)
    {
        //printf("set SPDIF_non-PCM\r\n");
        MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
        MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
        }
        else
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
        }
    }
    else if(E_AUDIOSTREAM_AAC==eAudStreamType || E_AUDIOSTREAM_MPEG4==eAudStreamType)
    {
        MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);    //RF Mod
        MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
        }
        else
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
        }
    }
    else
    {
        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
    }

    if(g_u8LRAudioMode == 0)
    {
        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_STEREO, 0);
    }
    else if(g_u8LRAudioMode == 1)
    {
        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_RR, 0);
        MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_RR, 0);
    }
    else if(g_u8LRAudioMode == 2)
    {
        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SoundMode, MSAPI_AUD_MODE_LL, 0);
        MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_SoundMode, MSAPI_AUD_MPEG_SOUNDMODE_LL, 0);
    }

#if ENABLE_CI_PLUS
    if(TRUE == MApp_CI_IsOpMode())
    {
        MApp_Audio_OpSearchAdAudio();
    }
    else
#endif
    {
        MApp_Audio_SearchAdAudio();
    }

    //printf("SetAdAudio %u \n",g_u8AdAudSelected);
    MApp_Audio_SetAdAudio(g_u8AdAudSelected);

    return TRUE;
}

void MApp_Audio_SetAdAudio(U8 u8AudSelectedIndex)
{
#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        if (0xFF == u8AudSelectedIndex)
        {
            return;
        }
    }
#endif

    AUD_INFO stAudioStreamInfo;
    MApi_AUDIO_SetADOutputMode(AD_OUT_NONE);

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        MApp_PVR_PlaybackAdAudioStopLanguage(u8AudSelectedIndex);
    }
    else
#endif
    {
        //msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AD_FID));
        MApp_Demux_Stop_Filter_AudioDesc();
    }

    //msAPI_AUD_AdjustAudioFactor(E_ADJUST_DTV_AUDIO_COMMAND, E_AUDIO_DVB2_COM_STOP, 0);
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);


#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        if (!MApp_PVR_PlaybackAudioGetStreamInfo(&stAudioStreamInfo, u8AudSelectedIndex))
        {
            return;
        }
    }
    else
#endif
    {
        /* Get Audio Stream Info */
        if (TRUE != msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &stAudioStreamInfo, u8AudSelectedIndex))
            return;
    }


    AUDIOSTREAM_TYPE eAudStreamType = msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudioStreamInfo);


  #if 0
    if (stAudioStreamInfo.wAudType == E_AUDIOSTREAM_AC3)
    {
        /* Stop Ad Audio decoder */
        //msAPI_AUD_AdjustAudioFactor(E_ADJUST_DTV_AUDIO_COMMAND, E_AUDIO_DVB2_COM_STOP, 0);
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);
    }
    else
  #endif
    {
    #if(ENABLE_DVB_AUDIO_DESC)
        if (stGenSetting.g_SoundSetting.bEnableAD)
        {
            DEBUG_AU_LOAD_CODE(printf("eAudStreamType=%u\n", eAudStreamType););

            /* set decoder system and reload firmware code */
            if (eAudStreamType == E_AUDIOSTREAM_AC3)
            {
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AC3);
                msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AC3_AD);
              #if ENABLE_PVR
                g_enCurrent_AudioDescriptorType = E_AUDIOSTREAM_AC3_AD;
              #endif
            }
            else if (eAudStreamType == E_AUDIOSTREAM_MPEG)
            {
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MPEG);
                msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_MPEG_AD);
              #if ENABLE_PVR
                g_enCurrent_AudioDescriptorType = E_AUDIOSTREAM_MPEG_AD;
              #endif
            }
            else if (eAudStreamType == E_AUDIOSTREAM_AC3P)
            {
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AC3P);
                msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AC3P_AD);
              #if ENABLE_PVR
                g_enCurrent_AudioDescriptorType = E_AUDIOSTREAM_AC3P_AD;
              #endif
            }
            else if ((eAudStreamType == E_AUDIOSTREAM_AAC) ||
                    (eAudStreamType == E_AUDIOSTREAM_MPEG4))
            {
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AAC);
                msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AACP_AD);
              #if ENABLE_PVR
                g_enCurrent_AudioDescriptorType = E_AUDIOSTREAM_AACP_AD;
              #endif
            }

        #if ENABLE_PVR
            if (MApp_PVR_IsPlaybacking())
            {
                MApp_PVR_PlaybackAdAudioSelectLanguage(u8AudSelectedIndex);
            }
            else
        #endif
            {
            #if ENABLE_PVR
                g_u16Current_AudioDescriptorPID = stAudioStreamInfo.wAudPID;
            #endif
                // start filter should be after than start audio decoder to prevent audio ES buffer overflow
                /* set audio PID & start filter */
                //printf("## Channel change, ad audio pid 0x%x, u8AdAudFid %bu\n", stAudioStreamInfo.wAudPID, u8AdAFid);
                //msAPI_DMX_StartFilter(stAudioStreamInfo.wAudPID, MSAPI_DMX_FILTER_TYPE_AUDIO2, MApp_Dmx_GetFid(EN_AD_FID));
                MApp_Demux_Start_Filter_AudioDesc(stAudioStreamInfo.wAudPID);
            }


            /* start ad audio decoder */
            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_DTV_AUDIO_COMMAND, E_AUDIO_DVB2_COM_PLAY, 0);
            MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);//stGenSetting.g_SoundSetting.ADOutput);
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_PLAY);
        }
    #endif
    }
}

void MApp_Audio_SearchAdAudio(void)
{
#if(ENABLE_DVB)

    g_u8AdAudSelected = 0xFF;

#if(ENABLE_DVB_AUDIO_DESC)
    if (!stGenSetting.g_SoundSetting.bEnableAD)
    {
        //printf("MApp_UiMenu_SearchAdAudio : AD is disabled\n");
        return;
    }

    MEMBER_SERVICETYPE bServiceType;
    AUD_INFO aAudioStreamInfo;
    AUD_INFO aPriAudioStreamInfo;
    WORD wCurrentPosition;
    U8 AudioLangNum;
    U8 i, j, k;

    memset(&aAudioStreamInfo, 0, sizeof(AUD_INFO));
    memset(&aPriAudioStreamInfo, 0, sizeof(AUD_INFO));


    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    AudioLangNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);


#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        MApp_PVR_PlaybackAudioGetStreamInfo(&aPriAudioStreamInfo, g_u8AudLangSelected);
    }
    else
#endif
    {
        // Get current main audio language
        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aPriAudioStreamInfo, g_u8AudLangSelected);
    }

    if (AudioLangNum != 0)
    {
        for (i = 0; i < AudioLangNum; i++)
        {
        #if ENABLE_PVR
            if (MApp_PVR_IsPlaybacking())
            {
                MApp_PVR_PlaybackAudioGetStreamInfo(&aAudioStreamInfo, i);
            }
            else
        #endif
            {
                /* Get all audio information */
                //printf("(%d)(%s)\n", __LINE__, __func__);
                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
            }

            //printf("bAudType = 0x%02bx\n", aAudioStreamInfo.aISOLangInfo[0].bAudType);

            for (j = 0; j < MAX_AUD_ISOLANG_NUM; j++)
            {
                //printf("j = %d  bAudType = %d\n", j, aAudioStreamInfo.aISOLangInfo[j].bAudType);
                if (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_NONE)
                {
                    break;
                }
                if (aAudioStreamInfo.aISOLangInfo[j].bBroadcastMixedAD == TRUE)
                {
                    break;
                }

                    /* find visual impaired audio stream */
                    if (aAudioStreamInfo.aISOLangInfo[j].bAudType == 0x03)
                    {
                        // find ad's language
                        for (k = 0; k < MAX_AUD_ISOLANG_NUM; k++)
                        {
                            //if (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_NONE)
                                //continue;

                            // ad's language is the same as primary audio's
                            if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex)
                                || ((SI_LANGUAGE_ENGLISH == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex) &&(SI_LANGUAGE_UND== aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex))
                                || ((SI_LANGUAGE_UND == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex) &&(SI_LANGUAGE_ENGLISH== aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex))
                                || ((SI_LANGUAGE_SPANISH_AD == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex) && (SI_LANGUAGE_FRENCH == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex) && OSD_COUNTRY_FRANCE == OSD_COUNTRY_SETTING)
                                || ((SI_LANGUAGE_SPANISH_AD == aAudioStreamInfo.aISOLangInfo[k].bISOLangIndex) && (SI_LANGUAGE_FRENCH == aPriAudioStreamInfo.aISOLangInfo[j].bISOLangIndex) && OSD_COUNTRY_FRANCE == OSD_COUNTRY_SETTING))
                            {
                                if (g_u8AudLangSelected == i)
                                {
                                    //printf("primary audio playing current found ad, find another\n");
                                    continue;
                                }

                                //if (aPriAudioStreamInfo.wAudType != aAudioStreamInfo.wAudType)
                                if (aPriAudioStreamInfo.eSIAudType != aAudioStreamInfo.eSIAudType)
                                {
                                    //printf("primary audio stream type %x differs from ad audio stream type %x\n", aPriAudioStreamInfo.wAudType, aAudioStreamInfo.wAudType);
                                    continue;
                                }

                                //printf("####found ad audio 0x%02bx####\n", i);
                                g_u8AdAudSelected = i;
                                if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex))
                                {
                                    return;
                                }
                            }
                            /*else
                            {
                                u8ADIndex=i;
                                u8ADNum++;
                            }*/
                        }
                    }
                }
        }
    }
    /*if((AudioLangNum==2) &&  (u8ADNum==1))
    {
        g_u8AdAudSelected = u8ADIndex;
    }*/
        //printf("MApp_UiMenu_SearchAdAudio : No AD found\n");

#endif
#endif // ENABLE_DVB
}
#endif // ENABLE_DVB

#if ENABLE_CI_PLUS
void MApp_Audio_OpSearchAdAudio(void)
{
    g_u8AdAudSelected = 0xFF;

#if(ENABLE_DVB_AUDIO_DESC)

    if (!stGenSetting.g_SoundSetting.bEnableAD)
    {
        return;
    }


    MEMBER_SERVICETYPE bServiceType;
    AUD_INFO aAudioStreamInfo;
    AUD_INFO aPriAudioStreamInfo;
    WORD wCurrentPosition;
    U8 AudioLangNum;
    U8 i, j, k;
    U8 au8IsoLang[3];
    EN_SI_LANGUAGE eLangcode = SI_LANGUAGE_UND;

    memset(&aAudioStreamInfo, 0x00, sizeof(AUD_INFO)); // fix coverity 207478
    memset(&aPriAudioStreamInfo, 0x00, sizeof(AUD_INFO)); // fix coverity 207479

    if(TRUE == MApp_CI_GetOpIso639LangCodeByCicamId(MApp_CI_GetCurrentOpCicamId(), au8IsoLang))
    {
        eLangcode = msAPI_SI_GetLanguageByISO639LangCode(au8IsoLang);
    }

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    AudioLangNum = msAPI_CM_GetAudioStreamCount(bServiceType, wCurrentPosition);

#if ENABLE_PVR
    if (MApp_PVR_IsPlaybacking())
    {
        MApp_PVR_PlaybackAudioGetStreamInfo(&aPriAudioStreamInfo, g_u8AudLangSelected);
    }
    else
#endif
    {
        // Get current main audio language
        msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aPriAudioStreamInfo, g_u8AudLangSelected);
    }

    if (AudioLangNum != 0)
    {
        for (i = 0; i < AudioLangNum; i++)
        {
        #if ENABLE_PVR
            if (MApp_PVR_IsPlaybacking())
            {
                MApp_PVR_PlaybackAudioGetStreamInfo(&aAudioStreamInfo, i);
            }
            else
        #endif
            {
                /* Get all audio information */
                msAPI_CM_GetAudioStreamInfo(bServiceType, wCurrentPosition, &aAudioStreamInfo, i);
            }

            //printf("bAudType = 0x%02bx\n", aAudioStreamInfo.aISOLangInfo[0].bAudType);

            for (j = 0; j < MAX_AUD_ISOLANG_NUM; j++)
            {
                if (aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == SI_LANGUAGE_NONE)
                {
                    break;
                }
                if (aAudioStreamInfo.aISOLangInfo[j].bBroadcastMixedAD == TRUE)
                {
                    break;
                }

                /* find visual impaired audio stream */
                if (aAudioStreamInfo.aISOLangInfo[j].bAudType == 0x03)
                {
                    // find ad's language
                    for (k = 0; k < MAX_AUD_ISOLANG_NUM; k++)
                    {
                        // ad's language is the same as primary audio's
                        if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == eLangcode)
                            || (SI_LANGUAGE_UND == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex)
                            || (SI_LANGUAGE_QAA == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex)
                            || (SI_LANGUAGE_QAB == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex)
                            || (SI_LANGUAGE_QAC == aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex)
                            )
                        {
                            if (g_u8AudLangSelected == i)
                            {
                                continue;
                            }

                            //if (aPriAudioStreamInfo.wAudType != aAudioStreamInfo.wAudType)
                            if (aPriAudioStreamInfo.eSIAudType != aAudioStreamInfo.eSIAudType)
                            {
                                continue;
                            }

                            printf("\r\n ####found ad audio 0x%x####\n", i);
                            g_u8AdAudSelected = i;
                            if ((aAudioStreamInfo.aISOLangInfo[j].bISOLangIndex == aPriAudioStreamInfo.aISOLangInfo[k].bISOLangIndex))
                            {
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

#endif // ENABLE_DVB_AUDIO_DESC

}
#endif // ENABLE_CI_PLUS

#endif
//Set the sound mode. Depend on global variable stGenSetting.g_SoundSetting.SoundMode.
void MApp_Audio_AdjustSoundMode(void)
{
     MApi_AUDIO_EnableTone(TRUE);
     MApi_AUDIO_SetBass(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass);
     MApi_AUDIO_SetTreble(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble);
}

/*
     The input must be the surround mode option. The format of surround mode option
     is in Analog_DataType.h.
*/
void MApp_Aud_SetSurroundMode(U8 u8SurroundMode)
{
   /*
    Before enabling any surround mode,
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_SURROUND, TRUE , 0 )
    should be called
   */
    //printf("MApp_Aud_SetSurroundMode(u8SurroundMode=%u)\n", u8SurroundMode);

 #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
     MS_U8 u8DecStatus = 0;
 #endif

    switch ( u8SurroundMode & SURROUND_SYSTEM_TYPE_MASK )
    {
        default:
            printf("\nError: unknown u8SurroundMode=%u\n", u8SurroundMode & SURROUND_SYSTEM_TYPE_MASK);
            break;

        case SURROUND_SYSTEM_OFF:
            /* Close all mode */
            MApi_AUDIO_EnableSurround(FALSE);
            MApi_AUDIO_ADVSOUND_ProcessEnable(ADV_NONE);
		   #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
		   MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x00);
	       #endif
            break;
        case SURROUND_SYSTEM_SURROUNDMAX:
            MApi_AUDIO_ADVSOUND_ProcessEnable(ADV_NONE);
            MApi_AUDIO_EnableSurround(TRUE);
			#if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
			MApi_AUDIO_ADVSOUND_ProcessEnable(ADV_NONE);
			MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x00);
			#endif
            break;
        case SURROUND_SYSTEM_SRS:
            MApi_AUDIO_ADVSOUND_ProcessEnable(SRS_TSHD);
			#if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
			MApi_AUDIO_ADVSOUND_ProcessEnable(ADV_NONE);
			MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x00);
			#endif
            break;
        case SURROUND_SYSTEM_VDS:
            // API not support
            #if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
			MApi_AUDIO_ADVSOUND_ProcessEnable(ADV_NONE);
			MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x00);
			#endif
            break;
        case SURROUND_SYSTEM_VSPK:
			#if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
			MApi_AUDIO_ADVSOUND_ProcessEnable(ADV_NONE);
			MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x00);
			#endif
            // API not support
            break;
        case SURROUND_SYSTEM_BBE:
			#if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
			MApi_AUDIO_ADVSOUND_ProcessEnable(ADV_NONE);
			MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x00);
			#endif
            // API not support
            break;
#if (ENABLE_AUDIO_SURROUND_DBX == ENABLE)
		case SURROUND_SYSTEM_DBX:
				//DBX
			//printf("\nin DBX FUCNTION \n");
		    u8DecStatus = 0;
		    if(MApi_AUDIO_GetDecStatus() == MSAPI_AUD_DVB_DECCMD_PLAY)
		    {
		        MApi_AUDIO_SetCommand((En_DVB_decCmdType)MSAPI_AUD_STOP);
		        u8DecStatus = 1;
		    }
		    MApp_Audio_Copy_DBX_Parameter();

		    MApi_AUDIO_ADVSOUND_ProcessEnable(DBX);
			MApi_AUDIO_EnableSurround(FALSE);
			MApi_DBXTV_SetMode(stGenSetting.g_SoundSetting.DBXTV_TotSonMode,stGenSetting.g_SoundSetting.DBXTV_TotVolMode,stGenSetting.g_SoundSetting.TotSurMode,0x1F);
		    msAPI_Timer_Delayms(5);
		    if(u8DecStatus == 1)
		        MApi_AUDIO_SetCommand((En_DVB_decCmdType)MSAPI_AUD_DVB_DECCMD_PLAY);
			break;
#endif
    }
}

//=======================================================
void MApp_Aud_Banlace_Init(void)
{
    MApi_AUDIO_SetBalance(stGenSetting.g_SoundSetting.Balance );
}

void MApp_Aud_AutoVolume_Init(void)
{
    MApi_AUDIO_EnableAutoVolume((BOOLEAN)stGenSetting.g_SysSetting.fAutoVolume);
}

#if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
void MApp_Aud_AudioDelay_Init(void)
{
    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_setSpdifDelay, stGenSetting.g_SoundSetting.Audiodelay, 0);
}
#endif

void MApp_Aud_PEQ_Init(void)
{
    if(ST_AUDIO_PEQ.u8_PEQOnOff)
    {
        msAPI_AUD_SetPEQ(0, ST_AUDIO_PEQ.u8_Gain1Value, (U8)(ST_AUDIO_PEQ.u16_Fo1Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo1Value%100), ST_AUDIO_PEQ.u8_Q1Value);
        msAPI_AUD_SetPEQ(1, ST_AUDIO_PEQ.u8_Gain2Value, (U8)(ST_AUDIO_PEQ.u16_Fo2Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo2Value%100), ST_AUDIO_PEQ.u8_Q2Value);
        msAPI_AUD_SetPEQ(2, ST_AUDIO_PEQ.u8_Gain3Value, (U8)(ST_AUDIO_PEQ.u16_Fo3Value/100), (U8)(ST_AUDIO_PEQ.u16_Fo3Value%100), ST_AUDIO_PEQ.u8_Q3Value);
    }
}

void MApp_Aud_EQ_Init(void)
{	
	MDrv_WriteByteMask(0x110A00,0x80,0x80);
	MDrv_WriteByteMask(0x110A2F,0x80,0x80);
	MDrv_WriteByteMask(0x110A50,0x80,0x80);
	//MDrv_WriteByteMask(0x110A2F,0x10,0x10);
	
	//MDrv_WriteByteMask(0x110A50,0x80,0x80);
	
	printf("WriteByteMask---\n");
	
    MApi_AUDIO_EnableEQ(TRUE);

    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_1, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8120HZ);

    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_2, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8500HZ);

    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_3, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1_dot_5_KHZ);

    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_4, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u8_5KHZ);

    MApi_AUDIO_SetEq(E_EQUALIZER_BAND_5, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].u810KHZ);
}

/********************************************************************************/
///
/// MAD MApp_Audio_SetScartOutAudioEnableMute
///
/********************************************************************************/
void MApp_Audio_HDMI_MODE_CONFIG(HDMI_POLLING_STATUS_t enHDMIPollingStatus, HDMI_PACKET_INFO_t *enHDMIPackInfo)
{
    MS_U32 c_bit, l_bit;
    static AUDIO_HDMI_RX_TYPE prvHdmiRawType = HDMI_RX_Other;
    AUDIO_HDMI_RX_TYPE curHdmiRawType = MApi_AUDIO_HDMI_RX_GetNonPCM();

#if HDMI_DVI_AUDIO_MODE_CONFIG
    if(stGenSetting.g_SysSetting.fEnableHdmiDviAudioModeConfig == EN_HDMI_DVI_AUDIOMODE_ANALOG)
    {
        return;
    }
#endif

    c_bit = MDrv_HDMI_audio_channel_status(0x00) & 0x20; //Check HDMI Copy Right C Bit
    l_bit = MDrv_HDMI_audio_channel_status(0x01) & 0x01; //Check HDMI Copy Right L Bit
    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_SetSCMS, c_bit, l_bit);

    if (MApi_AUDIO_HDMI_GetNonpcmFlag())
       enHDMIPackInfo->enPKT_Status.AudioNotPCM =1;
    else
       enHDMIPackInfo->enPKT_Status.AudioNotPCM =0;

    if (MApi_AUDIO_HDMI_GetNonpcmFlag())
    {  // non-PCM
        if( enHDMIPollingStatus.bIsHDMIMode && ((enHDMIPackInfo->enPKT_Status.AudioNotPCM != enHDMIPackInfo->enPKT_Status.PreAudiostatus)||
                                                (curHdmiRawType != prvHdmiRawType)
                                              #if HDMI_DVI_AUDIO_MODE_CONFIG
                                                || g_HdmiAudioModeChanged
                                              #endif
                                                ))
        {
            enHDMIPackInfo->enPKT_Status.PreAudiostatus = enHDMIPackInfo->enPKT_Status.AudioNotPCM;
            if( enHDMIPackInfo->enPKT_Status.AudioNotPCM)
            {
                MS_DEBUG_MSG(printf("\r\n  non pcm"));
            #if HDMI_DVI_AUDIO_MODE_CONFIG
                if(g_HdmiAudioModeChanged)
                {
                    g_HdmiAudioModeChanged = FALSE;
                    MApi_AUDIO_SetCommand((En_DVB_decCmdType) MSAPI_AUD_STOP );
                }
            #endif
                MApi_AUDIO_SPDIF_SetMute(TRUE);
                MApi_AUDIO_HDMI_SetNonpcm(TRUE);                // HDMI non-PCM setting
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, LINE_MODE, 0);    //Line Mod
                MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);  //LtRt
                MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      AUDIO_DSP1_HDMI_INPUT, AUDIO_OUTPUT_LINEOUT);
                if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                }
                else
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                }
                //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
                MApi_AUDIO_SPDIF_SetMute(FALSE);
            }
        }
    }
    else
    {
        if ( (enHDMIPollingStatus.bIsHDMIMode)
          && (enHDMIPackInfo->enPKT_Status.AudioNotPCM != enHDMIPackInfo->enPKT_Status.PreAudiostatus) )
        {
            enHDMIPackInfo->enPKT_Status.PreAudiostatus = enHDMIPackInfo->enPKT_Status.AudioNotPCM;
            if ( !enHDMIPackInfo->enPKT_Status.AudioNotPCM)
            {
                MS_DEBUG_MSG(printf("\r\n  pcm"));
                MDrv_AUDIO_SetNormalPath(AUDIO_PATH_LINEOUT,      AUDIO_HDMI_INPUT, AUDIO_OUTPUT_LINEOUT);
                MApi_AUDIO_SPDIF_SetMute(TRUE);
                MApi_AUDIO_HDMI_SetNonpcm(FALSE);                // HDMI non-PCM setting
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                MApi_AUDIO_SPDIF_SetMute(FALSE);
            }
        }
    }

    prvHdmiRawType = curHdmiRawType;
}


//======================================================
// User can set different PreScale Gain here level in Mapp_audio.C
// Min. 0x00 --> 0 dBFS ; Max. 0x50 --> -40 dBFS
 // each step -0.5dB
 // Threshold=0x20 ==> -0.5dB * 0x20= -0.5dB * 32= -16dB
 //======================================================

void MApp_Audio_AdjustPreScale(U8 InputSource)
{
  switch(InputSource)
  {
    case E_AUDIOSOURCE_MPEG:
    case E_AUDIOSOURCE_AC3:
        MApi_AUDIO_SetPreScale(AUDIO_PATH_MAIN,Prescale_MainSpeaker_DTV);
        break;

      case E_AUDIOSOURCE_HDMI:
    case E_AUDIOSOURCE_HDMI2:
    case E_AUDIOSOURCE_HDMI3:
        MApi_AUDIO_SetPreScale(AUDIO_PATH_MAIN,Prescale_MainSpeaker_HDMI);
        break;

    case E_AUDIOSOURCE_ATV:
        MApi_AUDIO_SetPreScale(AUDIO_PATH_MAIN,Prescale_MainSpeaker_ATV);
        break;

    case E_AUDIOSOURCE_CVBS1:
    case E_AUDIOSOURCE_CVBS2:
    case E_AUDIOSOURCE_SVIDEO1:
    case E_AUDIOSOURCE_SVIDEO2:
    case E_AUDIOSOURCE_SCART1:
    case E_AUDIOSOURCE_SCART2:
        MApi_AUDIO_SetPreScale(AUDIO_PATH_MAIN,Prescale_MainSpeaker_AV);
        break;

      case E_AUDIOSOURCE_PC:
    case E_AUDIOSOURCE_DVI:
    case E_AUDIOSOURCE_DVI2:
    case E_AUDIOSOURCE_DVI3:
        MApi_AUDIO_SetPreScale(AUDIO_PATH_MAIN,Prescale_MainSpeaker_PC);

    default:
        break;
    }
}

//======================================================
// User can set different AVC threshold level in Mapp_audio.C
// Min. 0x00 --> 0 dBFS ; Max. 0x50 --> -40 dBFS
 // each step -0.5dB
 // Threshold=0x20 ==> -0.5dB * 0x20= -0.5dB * 32= -16dB
 //======================================================
void MApp_Audio_AdjustAVCThreshold(U8 InputSource)
{
    switch(InputSource)
    {
        case E_AUDIOSOURCE_MPEG:
        case E_AUDIOSOURCE_AC3:
        case E_AUDIOSOURCE_ATV:
        case E_AUDIOSOURCE_CVBS1:
        case E_AUDIOSOURCE_CVBS2:
        case E_AUDIOSOURCE_SVIDEO1:
        case E_AUDIOSOURCE_SVIDEO2:
        case E_AUDIOSOURCE_YPbPr:
        case E_AUDIOSOURCE_PC:
        case E_AUDIOSOURCE_HDMI:
            MApi_AUDIO_SetAvcThreshold(0x20);   //Output Clipping Level = -16 dBFS
            break;
        case E_AUDIOSOURCE_SCART1:
        case E_AUDIOSOURCE_SCART2:
            MApi_AUDIO_SetAvcThreshold(0x20);   //Output Clipping Level = -16 dBFS
            break;

        default:
        MApi_AUDIO_SetAvcThreshold(0x20);     //Output Clipping Level = -16 dBFS
            break;
    }
}

//******************************************************************************
//Function name:    MApp_Audio_AdjustMainVolume
//Return parameter: none
//Description:      Set main speaker volume. 0 ~ 100
//  [Doxygen]
/// Set main speaker volume . 0 ~ 100
/// @param BYTE VolumePercent \b IN  volume percentage 0 ~ 100
//******************************************************************************
void MApp_Audio_AdjustMainVolume(BYTE VolumePercent)
{
    BYTE value1,value2;

    //PRINT_CURRENT_LINE();
    printf("MApp_Audio_AdjustMainVolume(VolumePercent=%u)\n", VolumePercent);

    if( VolumePercent > 100 )
        VolumePercent = 100;

    if(VolumePercent == 0)
    {
        MApi_AUDIO_SetMute(AUDIO_PATH_MAIN_SPEAKER,TRUE);
        MApi_AUDIO_SetMute(AUDIO_PATH_HP,TRUE);
        //MW_AUD_SetSoundMute(SOUND_MUTE_TV, E_MUTE_ON); //gchen @ 20171221
    }


#if(ENABLE_SOUND_NONLINEAR_CURVE)
    VolumePercent = MApp_NonLinearCalculate(MApp_GetNonLinearCurve(NONLINEAR_CURVE_VOLUME),VolumePercent);
#endif
	if(IsHDMIInUse()){
		    value1 = (BYTE)((TvVolumeTable_HDMI[VolumePercent]>>8)&0xFF);
			value2 = (BYTE)(TvVolumeTable[VolumePercent]&0xFF);
	}else{
			value1 = (BYTE)((TvVolumeTable[VolumePercent]>>8)&0xFF);
			value2 = (BYTE)(TvVolumeTable[VolumePercent]&0xFF);
	}

#if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)    \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)   \
    ||(0) )

    MApi_AUDIO_SetAbsoluteVolume(AUDIO_PATH_MAIN,value1,value2);

#else // For T3-like series

    //printf("value1=%u, value2=%u\n", value1, value2);
    MApi_AUDIO_SetAbsoluteVolume(AUDIO_PATH_MAIN_SPEAKER,value1,value2);
    MApi_AUDIO_SetAbsoluteVolume(AUDIO_PATH_HP,value1,value2);
	//<<add by gchen @ 20180206 //I2S Volume Change
	MApi_AUDIO_SetAbsoluteVolume(AUDIO_T3_PATH_I2S,value1,value2);
	MApi_AUDIO_SetAbsoluteVolume(AUDIO_AUOUT1_OUTPUT,value1,value2);
	//>>add by gchen @ 20180206
#endif


    if(VolumePercent != 0)
    {
        MApi_AUDIO_SetMute(AUDIO_PATH_MAIN_SPEAKER,FALSE);
        MApi_AUDIO_SetMute(AUDIO_PATH_HP,FALSE); 
        //MW_AUD_SetSoundMute(SOUND_MUTE_TV, E_MUTE_OFF); //gchen @ 20171221
    }
}

//******************************************************************************
//Function name:    MApp_Audio_AdjustADVolume
//Return parameter: none
//Description:      Set DTV AD(Audio description) Volume. 0 ~ 100
//  [Doxygen]
/// Use volume table to Set AD volume . 0 ~ 100
/// @param BYTE VolumePercent \b IN  volume percentage 0 ~ 100
//******************************************************************************
void MApp_Audio_AdjustADVolume(BYTE VolumePercent)
{
    BYTE value1,value2;

    if( VolumePercent > 100 )
        VolumePercent= 100;

    value1 = (BYTE)((TvVolumeTable[VolumePercent]>>8)&0xFF); // can use another volume table
    value2 = (BYTE)(TvVolumeTable[VolumePercent]&0xFF);

    if(VolumePercent == 0)
    {
        value1 |= 0x80; // mute case, bit[15]
    }

    MApi_AUDIO_SetADAbsoluteVolume(value1);
}

extern BOOLEAN gCECUserControlEnable;
#if(CEC_VERSION_USING == CEC_NEW_VERSION)
extern void msAPI_CEC_SetSystemUnMute(void);
#endif

void MApp_Aud_SetTVSpeaker(void)
{
#if(ENABLE_CEC)
    msAPI_CEC_SetSystemAudioMode(FALSE);

    if (stGenSetting.stHDMISetting.g_bHdmiCecMode == TRUE)
    {
        if (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_IntSpeaker)
        {
            if(stGenSetting.stHDMISetting.g_bHdmiCecDeviceControl == DISABLE)
            {
                gCECUserControlEnable = FALSE;
            }

          #if (CEC_VERSION_USING == CEC_NEW_VERSION)

            msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, FALSE);
            msAPI_CEC_SetSystemUnMute();

          #else
            msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(POSTMSG);
            if (msAPI_AUD_IsAudioMutedByUser() == TRUE)
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
          #endif
        }
        else if (stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp)
        {
            gCECUserControlEnable = TRUE;

          #if (CEC_VERSION_USING == CEC_NEW_VERSION)

            msAPI_CEC_TxMsgSystemAudioModeRequest(POSTMSG, TRUE);

          #else
            if ( IsHDMIInUse() )
            {
                msAPI_CEC_PostMsg_SystemAudioModeReq(POSTMSG, msAPI_CEC_GetActivePhyAddr());
            }
            else
            {
                msAPI_CEC_PostMsg_SystemAudioModeReq(POSTMSG, 0x0000);
            }
          #endif
        }
    }
#endif
}


#define DEBUG_AUDIO_USE_TIME    0

void MApp_Audio_Task_Slow(void)
{
    static U32 s_Audio_Task_Slow_u32LastTime = 0;

    if( msAPI_Timer_DiffTime_2(s_Audio_Task_Slow_u32LastTime, MsOS_GetSystemTime()) < 60 )
    {
        return;
    }
    s_Audio_Task_Slow_u32LastTime = MsOS_GetSystemTime();


    #if  EAR_PHONE_POLLING
      if (GetEarphoneState() != PreEarphoneState)
      {
          PreEarphoneState = GetEarphoneState();
          if (PreEarphoneState == EAR_PHONE_NULL)
          {
              EarPhone_OFF();
              //printf("MUTE_Off()\n");
              MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
          }
          else
          {
              EarPhone_ON();
              //printf("MUTE_On()\n");
              MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);
          }
      }
    #endif


    if( IsHDMIInUse()||IsDTVInUse()||IsStorageInUse() )
    {
    #if(DEBUG_AUDIO_USE_TIME)
        printf(" %d -> %u\n", __LINE__, OS_SYSTEM_TIME());
    #endif

        MApi_Audio_SPDIF_Monitor();
    #if(DEBUG_AUDIO_USE_TIME)
        printf(" %d -> %u\n", __LINE__, OS_SYSTEM_TIME());
    #endif
    }

}

void MApp_Audio_Task(BOOL bRealTimeOnly)
{
    static U32 s_Audio_Task_u32LastTime = 0;

    if( msAPI_Timer_DiffTime_2(s_Audio_Task_u32LastTime, MsOS_GetSystemTime()) < 5 )
    {
        return;
    }
    s_Audio_Task_u32LastTime = MsOS_GetSystemTime();


    // Fast task here ....



    if( bRealTimeOnly == FALSE ) // For slow task
    {
        msAPI_AUD_CheckExpirationOfSpdifMute();
        msAPI_AUD_CheckExpirationOfAudioMute();

#if (ENABLE_MADMONITOR)//Should not ENABLE this macro,or it will cause CI+1.2 Generic Broswer test 3.12.7.2 Fail !!!
    #if 0
    #if ENABLE_DMP
      if (!IsStorageInUse() ||
          /*(MApp_MPlayer_QueryCurrentMediaType() != E_MPLAYER_TYPE_PHOTO) ||*/
          (
              IsStorageInUse() &&
              (
                  (g_eMPlayerInternalState == E_MPLAYER_INTERNAL_STATE_MEDIA_PLAYING && (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MUSIC || MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)) ||
                  (g_eMPlayerInternalState == E_MPLAYER_INTERNAL_STATE_MAIN_MENU && (MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MUSIC) > 0 || MApp_MPlayer_QueryPreviewState(E_MPLAYER_TYPE_MOVIE) > 0))
              )
          )
         )
    #endif  // ENABLE_DMP
    #endif
        {
            //printf(" %d -> %u\n", __LINE__, OS_SYSTEM_TIME());
            TIMER_SET_DELAY_ID_START(E_DELAY_ID_AUDIO_DRV_MApi_Audio_Monitor);
            MApi_Audio_Monitor();
            TIMER_SET_DELAY_ID_END();
            //printf(" %d -> %u\n", __LINE__, OS_SYSTEM_TIME());
        }
#endif

        MApp_Audio_Task_Slow();

    }

}

#if (ENABLE_ATSC)
#include "MApp_Audio_ATSC.h"
#include "MApp_Psip.h"
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_Scan.h"
#include "MApp_VChip.h"
#include "MApp_PCMode.h"


#define AUDIO_SOUNDTRACK_MONITOR_TIMES (200)

static U32 u32MonitorAudioTrackTimer;
//static BOOLEAN bUSerMuteStatus = FALSE;

MS_U8 bCurrentSoundMode;
MS_U8 bPreviousSoundMode;

#if (ENABLE_ATSC_AD_FUNC)
#define INACTIVE_AUDIO  0xFF
void MApp_Audio_SearchAdAudio_ATSC(void)
{
    g_u8AdAudSelected = (U8)INACTIVE_AUDIO;
    U8 u8AudioLangNum = MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum;
    U8 u8i;
    u8i =0;
    U16 u16StreamType = MApp_GetAudioStreamType();

    if (!stGenSetting.g_SoundSetting.bEnableAD)
    {
        //printf("MApp_UiMenu_SearchAdAudio : AD is disabled\n");
        return;
    }

    if(u8AudioLangNum <=1)
    {
        //printf("Only one audio sound track\n");
        return;
    }

    for(u8i=0; u8i < u8AudioLangNum; u8i++)
    {
        if((u8i != g_u8AudLangSelected)&&(astgSoundTrack[u8i].u16AudStreamType == u16StreamType))
        {
            g_u8AdAudSelected = u8i;
            break;
        }
    }
}

void MApp_Audio_SetAdAudio_ATSC(U8 u8AudSelectedIndex)
{
    MApi_AUDIO_SetADOutputMode(AD_OUT_NONE);

    msAPI_DMX_Stop(u8AudFid2);

    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);

    if (stGenSetting.g_SoundSetting.bEnableAD)
    {
        DEBUG_AU_LOAD_CODE(printf("astgSoundTrack[u8AudSelectedIndex].u16AudStreamType=%u\n", astgSoundTrack[u8AudSelectedIndex].u16AudStreamType););

    #if 1 // Use new api
        MApp_Audio_ATSC_Set_DecodeSystem_AD( (EN_AUD_STREAM_TYPE)astgSoundTrack[u8AudSelectedIndex].u16AudStreamType);
    #else
        if(astgSoundTrack[u8AudSelectedIndex].u16AudStreamType ==  AUD_STREAM_TYPE_AC3)
        {
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AC3);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AC3_AD);
        }
        else if(astgSoundTrack[u8AudSelectedIndex].u16AudStreamType ==  AUD_STREAM_TYPE_MPEG)
        {
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MPEG);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_MPEG_AD);
        }
        else if(astgSoundTrack[u8AudSelectedIndex].u16AudStreamType ==  AUD_STREAM_TYPE_AAC)
        {
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AAC);
            msAPI_AUD_Set_CurDspSystem(E_AUDIO_DSP_AACP_AD);
        }
    #endif

        msAPI_DMX_StartFilter(astgSoundTrack[u8AudSelectedIndex].u16AudioPid, MSAPI_DMX_FILTER_TYPE_AUDIO2, &u8AudFid2);
        MApi_AUDIO_SetADOutputMode(AD_OUT_BOTH);//stGenSetting.g_SoundSetting.ADOutput);
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_PLAY);
    }
}
#endif

/******************************************************************************/
/// MApp_SoundMtsSifSoundModeTrans
/// @param App_MTS \b IN
/******************************************************************************/
MS_U8 MApp_SoundMtsSifSoundModeTrans(MS_U8 App_MTS)
{
    AUDIOMODE_TYPE Driver_MTS;
    switch(App_MTS)
    {
        case SOUND_MTS_MONO:
            Driver_MTS=E_AUDIOMODE_MONO;
            break;

        case SOUND_MTS_STEREO:
            Driver_MTS=E_AUDIOMODE_K_STEREO;
            break;

    #if (TV_SYSTEM == TV_NTSC)
        case SOUND_MTS_SAP:
            Driver_MTS=E_AUDIOMODE_MONO_SAP;
            break;
    #endif

        case SOUND_MTS_LANG_AB:
            Driver_MTS=E_AUDIOMODE_DUAL_AB;
            break;

        default:
            Driver_MTS=E_AUDIOMODE_MONO;
            break;
    }

    return Driver_MTS;
}

MS_BOOL MApp_AUDIO_IsSifSoundModeExist(EN_SOUND_MTS_TYPE enSifSoundMode)
{
    bCurrentSoundMode = MApi_AUDIO_SIF_GetSoundMode();
    //printf("bCurrentSoundMode = 0x%bx\n", bCurrentSoundMode);
    //printf("set enSifSoundMode = %bd\n", enSifSoundMode);
#if 1
    switch ( enSifSoundMode )
    {
        case SOUND_MTS_MONO:
            if((bCurrentSoundMode ==E_AUDIOMODE_MONO)||(bCurrentSoundMode ==E_AUDIOMODE_K_STEREO)||
                (bCurrentSoundMode==E_AUDIOMODE_MONO_SAP)||(bCurrentSoundMode==E_AUDIOMODE_STEREO_SAP)||(bCurrentSoundMode==E_AUDIOMODE_DUAL_A))
            {
                return TRUE;
            }
            break;

        case SOUND_MTS_STEREO:
            if((bCurrentSoundMode ==E_AUDIOMODE_K_STEREO)||(bCurrentSoundMode==E_AUDIOMODE_STEREO_SAP))
            {
                return TRUE;
            }
            break;
      #if (TV_SYSTEM == TV_NTSC)
        case SOUND_MTS_SAP:
            if((bCurrentSoundMode==E_AUDIOMODE_MONO_SAP)||(bCurrentSoundMode==E_AUDIOMODE_STEREO_SAP)||(bCurrentSoundMode==E_AUDIOMODE_DUAL_A))
            {
                return TRUE;
            }
            break;
      #endif

        default:
            return FALSE;
    }
    return FALSE;
#else
    enSifSoundMode = enSifSoundMode;

    return NULL;
#endif
}


BOOLEAN MApp_Aud_GetUserMuteStatus(void)
{
    return msAPI_AUD_IsAudioMutedByUser();
}

BOOLEAN MApp_Aud_SetMtsMode(void)
{
    /* mute */
#if 0
    if(g_bInputBlocked == FALSE && ( MApp_VChip_GetCurVChipBlockStatus() == FALSE))
    {
        //TV has been muted by E_AUDIO_BYBLOCK_MUTEON or E_AUDIO_BYVCHIP_MUTEON
        //so there is no need to mute TV
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
#else
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
#endif

    if ( IsDTVInUse() )
    {
        U16 u16AudioPID_func;

        u16AudioPID_func = MApp_GetAudioSoundTrackPID( g_u8AudLangSelected );

        //20120806 Max add for MTS switch mpeg/ac3
        EN_AUD_STREAM_TYPE eAudStreamType = MApp_GetAudioStreamType();

        /* stop audio decoder */
        MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );

        /* stop audio filter */
        msAPI_DMX_Stop( u8AudFid );

        DEBUG_AU_LOAD_CODE( printf("eAudStreamType=%u\n", eAudStreamType); );

        //20120806 Max add for MTS switch mpeg/ac3
    #if 1
        MApp_Audio_ATSC_Set_DecodeSystem(eAudStreamType);
    #else
        if(eAudStreamType == AUD_STREAM_TYPE_MPEG)
        {
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
        }
        else if(eAudStreamType == AUD_STREAM_TYPE_AAC)
        {
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AAC);
        }
        else
        {
            MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);
        }
    #endif

        // start filter should be after than start audio decoder to prevent audio ES buffer overflow
        /* set audio PID & start filter */
        msAPI_DMX_StartFilter( u16AudioPID_func, MSAPI_DMX_FILTER_TYPE_AUDIO, &u8AudFid );

        /* start audio decoder */
        MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_PLAY );

    }
    else // IsATVInUse
    {
        /* sif set sound mode */
        MApi_AUDIO_SIF_SetSoundMode(MApp_SoundMtsSifSoundModeTrans( g_u8AudLangSelected) );
        bPreviousSoundMode = bCurrentSoundMode;
    }

    /* unmute */
#if 0
    if(g_bInputBlocked||( MApp_VChip_GetCurVChipBlockStatus()))
    {
    // do nothing...
    }
    else
    {
        if(!MApp_Aud_GetUserMuteStatus())
       {
           msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       }
        msAPI_Timer_Delayms( 100 ); // to avoid mts key POP noise

        //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
#else
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
#endif
    return TRUE;
}

void MApp_AudioStreamMonitor(void)
{
    if(msAPI_Timer_DiffTimeFromNow(u32MonitorAudioTrackTimer) > AUDIO_SOUNDTRACK_MONITOR_TIMES)
    {
        BOOLEAN bReloadAudiotrack = FALSE;
        U16 u16AudioPID = MSAPI_DMX_INVALID_PID;

        if(fTableAudioNumChanged)
        {
            U16 u16CurAudioPID;

            u16CurAudioPID = MApp_GetAudioSoundTrackPID(g_u8AudLangSelected);
            MApp_ReMapAudioLanguage();

        #if(ENABLE_ATSC_VIDEO_DESC)
            if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_ON)
                u16AudioPID = MApp_SetPreferAudioSoundTrackPID(0);
            else //if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
        #endif
            {
                u16AudioPID = MApp_SetPreferAudioSoundTrackPIDNew();
            }

            if(u16CurAudioPID != u16AudioPID)
            {
                /* stop audio decoder */
                MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );

                /* stop audio filter */
                msAPI_DMX_Stop( u8AudFid );

                bReloadAudiotrack = TRUE;
                //g_u8AudLangSelected = 0;
            }
        }

        if( fTableAudioStreamTypeChange )
        {
            MApp_ReMapAudioLanguage();

        #if(ENABLE_ATSC_VIDEO_DESC)
            if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_ON)
                u16AudioPID = MApp_SetPreferAudioSoundTrackPID(0);
            else //if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
        #endif
            {
                u16AudioPID = MApp_SetPreferAudioSoundTrackPIDNew();
            }

            bReloadAudiotrack = TRUE;
        }

        if(bReloadAudiotrack)
        {
        /*
            if(fTableAudioStreamTypeChange)
            {
                MApp_ReMapAudioLanguage();
                //if(stGenSetting.g_SoundSetting.enSoundDigitalSelect == SOUND_AUDIO_DIGITAL_DEFAULT)
                if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
                    u16AudioPID = MApp_SetPreferAudioSoundTrackPIDNew();
                else
                    u16AudioPID = MApp_SetPreferAudioSoundTrackPID(0);
            } */

            //u16AudioPID = MApp_SetPreferAudioSoundTrackPIDNew();

            if(fTableAudioNumChanged)
            {
                /* set audio PID & start filter */
                msAPI_DMX_StartFilter( u16AudioPID, MSAPI_DMX_FILTER_TYPE_AUDIO, &u8AudFid );
            }

            EN_AUD_STREAM_TYPE eTempStreamType = MApp_GetAudioStreamType();
            DEBUG_AU_LOAD_CODE( printf("eTempStreamType=%u\n", eTempStreamType); );

            /* set decoder system and reload firmware code */
            MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );

        #if 1 // Use new api
            // Stop decoder & change decode system
            MApp_Audio_ATSC_Set_DecodeSystem(eTempStreamType);
        #else
            if(eTempStreamType == AUD_STREAM_TYPE_MPEG)
            {
                 MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
            }
            else if(eTempStreamType == AUD_STREAM_TYPE_AAC)
            {
                 MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AAC);
            }
            else
            {
                 MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);
            }
        #endif

            if ( eTempStreamType != AUD_STREAM_TYPE_AC3)
            {
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
            }
            else
            {
              #if (ENABLE_UI_SPDIF_SETTING==ENABLE)
                if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                }
                else
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                }
              #else
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
              #endif
            }

            MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_PLAY );
        }

        if(fTableAudioLanguageChange)
        {
            MApp_ReMapAudioLanguage();
        }

        fTableAudioStreamTypeChange = FALSE;
        fTableAudioNumChanged = FALSE;
        fTableAudioLanguageChange = FALSE;
        u32MonitorAudioTrackTimer = msAPI_Timer_GetTime0();
    }
}

#if 0//do not use this function from CK2
void MApp_Aud_EnableMute ( BOOLEAN bEnableMute )
{
    //printf("MApp_Aud_EnableMute(%u)\n", bEnableMute);

    if ( bEnableMute )
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        bUSerMuteStatus = TRUE;
    }
    else
    {
        if ( MApp_VChip_GetCurVChipBlockStatus() )
            return;

        if ( stGenSetting.g_SoundSetting.Volume )
        {
            if ( IsDTVInUse() )
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
            else if ( IsDigitalSourceInUse() )
            {
                if ( msAPI_AVD_IsSyncLocked() )
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
                else
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
            }
            else if (IsAnalogSourceInUse())
            {
                  if (MApp_PCMode_GetCurrentState(MAIN_WINDOW) == E_PCMODE_STABLE_SUPPORT_MODE)   //(!(g_bInputTimingChange||g_bUnsupportMode||msAPI_Scaler_SyncLossFlag()))
                  {
                      msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                  }
             }
            else // IsMEDIAInUse()
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
        }
        else
        {
           msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }

        bUSerMuteStatus = FALSE;
    }
}
#endif

//do not use this function from CK2
void MApp_Aud_SetPathUnMute(void)
{
    if( (!g_bInputBlocked) && (!MApp_VChip_GetCurVChipBlockStatus()) )
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

        /*if( !MApp_Aud_GetUserMuteStatus() )
        {  // mute by user.....
            MApp_Aud_EnableMute(AUD_APP_VOLUME_UNMUTE);
        }*/

        MApi_AUDIO_SPDIF_SetMute(FALSE);
    }
}

BOOLEAN MApp_Aud_GetMuteStatus ( void )
{
#if ENABLE_INPUT_LOCK
    return ( msAPI_AUD_IsAudioMutedByUser() || g_bInputBlocked );
#else
    return msAPI_AUD_IsAudioMutedByUser();
#endif
}


#if ENABLE_ATSC
void MApp_Aud_GetNextAvailableMtsMode ( BOOLEAN bForce )
{
    if ( IsAtscInUse() )
    {
        iu8Buffer_i = MApp_ChanProc_GetCurIdxMap2ChanBufIdx( MApp_ChanProc_GetCurProgIndex() );
        pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();
    }
    else // IsATVInUse
    {
        bCurrentSoundMode = MApi_AUDIO_SIF_GetSoundMode();
        if(bForce) // Non_Hotkey Selection Behavior
        {
            switch(stGenSetting.g_SoundSetting.Mts)
            {
                case SOUND_MTS_STEREO:
              #if (TV_SYSTEM == TV_NTSC)
                case SOUND_MTS_SAP:
              #endif
                    if ( MApp_AUDIO_IsSifSoundModeExist(stGenSetting.g_SoundSetting.Mts ) )
                    {
                        g_u8AudLangSelected = stGenSetting.g_SoundSetting.Mts;
                    }
                    else
                    {
                        g_u8AudLangSelected =  SOUND_MTS_MONO;
                    }
                    break;

                case SOUND_MTS_MONO:
                default:
                    g_u8AudLangSelected = SOUND_MTS_MONO;
                    break;
            }
        }
        else // HotKey MTS selection Behavior
        {
            g_u8AudLangSelected = stGenSetting.g_SoundSetting.Mts;
            while(g_u8AudLangSelected != SOUND_MTS_MONO)
            {
                if(MApp_AUDIO_IsSifSoundModeExist( (EN_SOUND_MTS_TYPE)g_u8AudLangSelected ))
                {
                    break;
                }
                else
                {
                    g_u8AudLangSelected = (g_u8AudLangSelected+1)%SOUND_MTS_NUM;
                    stGenSetting.g_SoundSetting.Mts = (EN_SOUND_MTS_TYPE)g_u8AudLangSelected;
                }
            }
        }
    }
}

void MApp_Aud_SetBass ( U8 u8Bass )
{
    MS_S16 Gain = 0;
    MS_U16 Fo = 400;   //Fo: 10 ~ 16000
    MS_U8 QValue = 70;  //Fo: 50 ~ 90

    /* Gain */
    if(u8Bass >= 100)
    {
        u8Bass = 100;
        Gain = 120;
    }
    else if (u8Bass == 0)
    {
        Gain = -120;
    }
    else
    {
        Gain = (int)((u8Bass - 50) * 120 / 50); // (0 ~ 100) <-> (-120 ~ 120)
    }
    msAPI_AUD_SetTONE(0,Gain,Fo,QValue); // Bass for 400HZ

    //MApi_AUDIO_SetBass( u8Bass );
}

void MApp_Aud_SetTreble ( U8 u8Treble )
{
    MS_S16 Gain = 0;
    MS_U16 Fo = 8000;   //Fo: 10 ~ 16000
    MS_U8 QValue = 70;  //Fo: 50 ~ 90

    /* Gain */
    if(u8Treble >= 100)
    {
        u8Treble = 100;
        Gain = 120;
    }
    else if (u8Treble == 0)
    {
        Gain = -120;
    }
    else
    {
        Gain = (int)((u8Treble - 50) * 120 / 50); // (0 ~ 100) <-> (-120 ~ 120)
    }
    msAPI_AUD_SetTONE(1,Gain,Fo,QValue); // treble for 8KHZ

    //MApi_AUDIO_SetTreble( u8Treble );
}

#endif

#if ENABLE_SOUNDTRACK_CHECKER_NEW
extern MS_U8   MDrv_MAD_Rpt_DTVES(void);

//#define AUDIO_TRACK_CHECK_WAIT_TIME     (2000)  // how long we have to wait before we check if the audio PID exists after setting a audio PID
//******************************************************************************
/// MApp_AUD_PreferSoundTrack_Checker
//******************************************************************************
void MApp_AUD_PreferSoundTrack_Checker(void)
{
    static U32 u32AudTrackChkWaitTime = 2000;  // how long we have to wait before we check if the audio PID exists after setting a audio PID
    static U8 u8SignalLockDebounce = 0;

    // check if this aduio track exists
    if (unchecked_audio_track_num)
    {
        if (MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum == 0)
        {
            unchecked_audio_track_num = 0;
            return;
        }
        if ((start_decode_audio_time == 0) && (bFlagTrackChecker ==0))
        {
            if (MApp_Check_FE_Status( MApp_ChanProc_GetCurChannelPointer()) == FE_LOCK)
            {
                u8SignalLockDebounce++;
                if (u8SignalLockDebounce >= 5)
                {
                    u8SignalLockDebounce = 0;
                    start_decode_audio_time = msAPI_Timer_GetTime0();
                    bFlagTrackChecker = 1;
                }
                return;
            }
            else
            {
                u8SignalLockDebounce = 0;
                return;
            }
        }
        if (msAPI_Timer_DiffTimeFromNow(start_decode_audio_time) > u32AudTrackChkWaitTime)
        {
            unchecked_audio_track_num --;

            EN_AUD_STREAM_TYPE eCurAudStreamType = MApp_GetAudioStreamType();

            if( eCurAudStreamType == AUD_STREAM_TYPE_AC3 )
            {
                if (!msAPI_AUD_DECODER_GetMAD_LOCK() && (msAPI_AUD_DECODER_GetMAD_PCMBufLevel(E_AUDIOSTREAM_AC3_)==0))
                {
                    printf("AC3: MAD lock = 0\n");

                    if ( ++u8AudioType > (PreferSoundTrack_Number+1) )
                    {
                        printf("SoundTrack %d has NO AC3\n", g_u8AudLangSelected);
                        g_u8AudLangSelected++;
                        g_u8AudLangSelected %= MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum;
                        u8AudioType = 0;
                        u32AudTrackChkWaitTime= 2000;
                    }
                    else
                    {
                        u32AudTrackChkWaitTime= 2000;
                        astgSoundTrack[g_u8AudLangSelected].u16AudStreamType = AUD_STREAM_TYPE_MPEG;
                    }

                    //DEBUG_AU_LOAD_CODE( printf("astgSoundTrack[g_u8AudLangSelected].u16AudStreamType=%u\n", astgSoundTrack[g_u8AudLangSelected].u16AudStreamType); );

                #if 1 // Use new function
                    MApp_Audio_ATSC_ReInit_DecodeSystem_ByAudLangIdx(g_u8AudLangSelected);

                #else
                    MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );

                    //MApi_AUDIO_SetSystem_Test(0,astgSoundTrack[g_u8AudLangSelected].u16AudStreamType);
                    //MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
                    if(astgSoundTrack[g_u8AudLangSelected].u16AudStreamType == AUD_STREAM_TYPE_MPEG)
                    {
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
                    }
                    else if(astgSoundTrack[g_u8AudLangSelected].u16AudStreamType == AUD_STREAM_TYPE_AAC)
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AAC);
                    else
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);

                    MApp_Aud_SetMtsMode();
                #endif

                    //AC3 Set SPDIF depend on UI SPDIF Type
                  #if (ENABLE_UI_SPDIF_SETTING==ENABLE)
                    if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                    {
                        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                    }
                    else
                    {
                        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                    }
                  #else
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                  #endif

                    start_decode_audio_time = msAPI_Timer_GetTime0();
                }
                else
                {
                    u32AudTrackChkWaitTime= 2000;
                    unchecked_audio_track_num = 0;
                    printf("SoundTrack %u has AC3\n", g_u8AudLangSelected);
                }
            }
            //else if ((MApp_GetAudioStreamType() == AUD_STREAM_TYPE_MPEG)||(MApp_GetAudioStreamType() == AUD_STREAM_TYPE_AAC ))
            else if( (eCurAudStreamType == AUD_STREAM_TYPE_MPEG) || (eCurAudStreamType == AUD_STREAM_TYPE_AAC) )
            {
                if ( !msAPI_AUD_DECODER_GetMAD_LOCK() )
                {
                    printf("AuCodecType=%u, MAD lock = 0\n", eCurAudStreamType);
                    if ( ++u8AudioType > (PreferSoundTrack_Number+1) )
                    {
                        printf("SoundTrack %d has NO MPEG\n", g_u8AudLangSelected);
                        g_u8AudLangSelected++;
                        g_u8AudLangSelected %= MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum;
                        u8AudioType = 0;
                        u32AudTrackChkWaitTime= 2000;
                    }
                    else
                    {
                        u32AudTrackChkWaitTime= 2000;
                        astgSoundTrack[g_u8AudLangSelected].u16AudStreamType = AUD_STREAM_TYPE_AC3;
                    }

                    //DEBUG_AU_LOAD_CODE( printf("astgSoundTrack[g_u8AudLangSelected].u16AudStreamType=%u\n", astgSoundTrack[g_u8AudLangSelected].u16AudStreamType); );

                #if 1 // Use new function
                    MApp_Audio_ATSC_ReInit_DecodeSystem_ByAudLangIdx(g_u8AudLangSelected);

                #else

                    MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );
                    //MApi_AUDIO_SetSystem_Test(1,astgSoundTrack[g_u8AudLangSelected].u16AudStreamType);
                    //MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);

                    if(AUD_STREAM_TYPE_MPEG == astgSoundTrack[g_u8AudLangSelected].u16AudStreamType)
                    {
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
                    }
                    else if(AUD_STREAM_TYPE_AAC == astgSoundTrack[g_u8AudLangSelected].u16AudStreamType)
                    {
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AAC);
                    }
                    else
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);

                    MApp_Aud_SetMtsMode();
                #endif

                  #if (ENABLE_UI_SPDIF_SETTING==ENABLE)
                    if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                    {
                        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                    }
                    else
                  #endif
                    {
                        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                    }

                    start_decode_audio_time = msAPI_Timer_GetTime0();
                }
                else
                {
                    u32AudTrackChkWaitTime= 2000;
                    unchecked_audio_track_num = 0;
                    printf("SoundTrack %d has MPEG\n", g_u8AudLangSelected);
                }
            }
        }
    }
}

#else
#define AUDIO_TRACK_CHECK_WAIT_TIME     (1000)  // how long we have to wait before we check if the audio PID exists after setting a audio PID

//******************************************************************************
/// MApp_AUD_PreferSoundTrack_Checker
//******************************************************************************
void MApp_AUD_PreferSoundTrack_Checker(void)
{
    // check if this aduio track exists
    if (start_decode_audio_time)
    {
        if (MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum == 0)
        {
            start_decode_audio_time = 0;
            unchecked_audio_track_num = 0;
            return;
        }

        if (msAPI_Timer_DiffTimeFromNow(start_decode_audio_time) > AUDIO_TRACK_CHECK_WAIT_TIME)
        {
            start_decode_audio_time = 0;

            unchecked_audio_track_num--;
            if (unchecked_audio_track_num <= 0)
            {
                unchecked_audio_track_num = 0;
                return;
            }

            if (MApp_GetAudioStreamType() == AUD_STREAM_TYPE_AC3)
            {
                //if (!MApi_AUDIO_GetAC3Info(Audio_AC3_infoType_DecStatus))
                if (!msAPI_AUD_DECODER_GetMAD_LOCK() && (msAPI_AUD_DECODER_GetMAD_PCMBufLevel(E_AUDIOSTREAM_AC3_)==0))
                {
                    if ( ++u8AudioType > (PreferSoundTrack_Number+1) )
                    {
                        MTS_DBINFO(printf("SoundTrack %d has NO AC3\n", g_u8AudLangSelected));
                        g_u8AudLangSelected++;
                        g_u8AudLangSelected %= MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum;
                        u8AudioType = 0;
                    }
                    else
                    {
                        astgSoundTrack[g_u8AudLangSelected].u16AudStreamType = AUD_STREAM_TYPE_MPEG;

                        DEBUG_AU_LOAD_CODE( printf("astgSoundTrack[g_u8AudLangSelected].u16AudStreamType=%u\n", astgSoundTrack[g_u8AudLangSelected].u16AudStreamType); );

                        MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_MPEG);
                        MApp_Aud_SetMtsMode();
                    #if (ENABLE_UI_SPDIF_SETTING==ENABLE)
                        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                        }
                        else
                    #endif
                        {
                             MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                        }
                        start_decode_audio_time = msAPI_Timer_GetTime0();
                    }
                }
                else
                {
                   // unchecked_audio_track_num = 0;
                    MTS_DBINFO(printf("SoundTrack %bu has AC3\n", g_u8AudLangSelected));
                }
            }
            else if ((MApp_GetAudioStreamType() == AUD_STREAM_TYPE_MPEG)||(MApp_GetAudioStreamType() == AUD_STREAM_TYPE_AAC ))
            {
                //if (!MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_DecStatus))
                if (!msAPI_AUD_DECODER_GetMAD_LOCK())
                {
                    if ( ++u8AudioType > (PreferSoundTrack_Number+1) )
                    {
                        printf("SoundTrack %d has NO MPEG\n", g_u8AudLangSelected);
                        g_u8AudLangSelected++;
                        g_u8AudLangSelected %= MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum;
                        u8AudioType = 0;
                    }
                    else
                    {
                        astgSoundTrack[g_u8AudLangSelected].u16AudStreamType = AUD_STREAM_TYPE_AC3;
                        DEBUG_AU_LOAD_CODE( printf("astgSoundTrack[g_u8AudLangSelected].u16AudStreamType=%u\n", astgSoundTrack[g_u8AudLangSelected].u16AudStreamType); );

                        MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );
                        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_AC3);
                        MApp_Aud_SetMtsMode();
                        start_decode_audio_time = msAPI_Timer_GetTime0();
                    #if (ENABLE_UI_SPDIF_SETTING==ENABLE)
                        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                        }
                        else
                    #endif
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                        }
                    }
                }
                else
                {
                   // unchecked_audio_track_num = 0;
                    MTS_DBINFO(printf("SoundTrack %d has MPEG\n", g_u8AudLangSelected));
                }
            }
        }
    }
}
#endif
#endif

void MApp_Audio_Set_AmpOnOff(BOOL bAmpOn)
{
    msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW);

    printf("MApp_Audio_Set_AmpOnOff(bAmpOn=%u)%s\n", bAmpOn, ANSI_COLOR_OFF_STR);


    if( bAmpOn )
    {
    	AMP_ENABLE();//gchen  @ 20171218
    #ifdef Audio_Amplifier_ON
        Audio_Amplifier_ON();
    #endif
    }
    else
    {
    	AMP_DISABLE();//gchen  @ 20171218
    #ifdef Audio_Amplifier_OFF
        Audio_Amplifier_OFF();
    #endif
    }
}

void MApp_Audio_Set_AmpMute(BOOL bAmpMute)
{
  #if 1
    msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW);

    printf("MApp_Audio_Set_AmpMute(%u)%s\n", bAmpMute, ANSI_COLOR_OFF_STR);

  #endif

    if( bAmpMute )
    {
        // MUTE_On() = Adj_Volume_Off()
        MUTE_On();
    }
    else
    {
        // MUTE_Off() =  Adj_Volume_On()
        //gchen @ 20180207
        printf("MApp_Audio_Set_AmpMute 11111 gchen \n");
        if(EAR_PHONE_get_level() != EAR_PHONE_NULL)
        {
        	printf("MApp_Audio_Set_AmpMute Mute Off no ear phone 22222 gchen \n");
        	MUTE_Off();
        }
    }
}

#undef _MAPP_AUDIO_C

