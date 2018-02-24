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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
#ifndef _MSAPI_TTX_C_
#define _MSAPI_TTX_C_

#include "SysInit.h"

#if (ENABLE_TTX)
#include "msAPI_TTX.h"
#include "string.h"
#include "sysinfo.h"
#include "BinInfo.h"
#include "debug.h"

#include "drvVBI.h"
#include "drvDMX_TTX.h"

// Panel module
#include "apiPNL.h"
#include "Panel.h"

#include "apiDMX.h"
#include "apiGOP.h"

#include "msAPI_Timer.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_CNI.h"
#include "../cni/msAPI_CNI_cus.c"

#include "mw_debug.h"
#include "TT_API25.h"
#include "TT_GERenderTarget.h"
#include "TT_DriverSlicer.h"
#include "TT_Config.h"

#include "TT_MStarFontCharsMan.h"

#include "TT_PacketBuffer.h"



#define DEBUG_API_TTX(x)    //x

#ifdef DEBUG_TELETEXT
    #define debugTeletextPrint(a,b)    debugPrint(a,b)
#else
    #define debugTeletextPrint(a,b)
#endif

#define PRINT_ATS_INFO 0

//****************************************************************************
// TTX memory layout
//****************************************************************************
// VBI buffer size definition
#define TTX_VBI_BUFFER_COUNT         360

#define TTX_VBI_BUFFER_ADDR                 ((TTXBUF_START_MEMORY_TYPE & MIU1) ? (TTXBUF_START_ADR | MIU_INTERVAL) : (TTXBUF_START_ADR))
// Because VBI slicer will write to (N + 1)th memory address at 1st round, we reserve 256 bytes after VBI buffer)
#define TTX_VBI_BUFFER_SIZE                   (TTXBUF_VBI_SIZE + 256UL)
#define TTX_INTERNAL_BUFFER_ADDR       (TTX_VBI_BUFFER_ADDR + TTX_VBI_BUFFER_SIZE)
#define TTX_INTERNAL_BUFFER_SIZE        (TTXBUF_START_LEN - TTX_VBI_BUFFER_SIZE)

TT_SizeDisplayModeConfig stSizeDisplayModeConfig;
TT_PagenumberConfig stPagenumberConfig;
TT_ListModeColorkeyBarConfig stListModeColorkeyBarConfig;
TT_UpdateModeConfig stUpdateModeConfig;
TT_NavigationBarConfig stNavigationBarConfig;
TT_SubpagebarConfig stSubpagebarConfig;
//****************************************************************************
// local definitions
//****************************************************************************
#define lmiRED              0x00
#define lmiGREEN          0x01
#define lmiYELLOW        0x02
#define lmiCYAN            0x03

#define MIN_TELETEXT_PAGE        0    //100        800~899 map tp  0~99
#define MAX_TELETEXT_PAGE        0x799//899
//****************************************************************************
// local variables
//****************************************************************************
static BOOLEAN  _bAcquireEnable = FALSE;
static BOOLEAN _bScanEnable = FALSE;

//****************************************************************************
// Start of private implementation.
//****************************************************************************
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: _InvertByte()
/// @brief \b Function \b Description:  Doing byte inversion
/// @param <IN>        \b ucVal               : The value to be inverted
/// @param <OUT>         \b None            :
/// @param <RET>          \b            : The inverted value (U8)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
static U8 _InvertByte(U_INT8 ucVal)
{
    U_INT8 ucMask, ucInvCode;

    ucInvCode = 0x00;
    for (ucMask=0x80; ucMask; ucMask>>=1)
    {
        ucInvCode >>= 1; // next bit
        if (ucVal&ucMask)
            ucInvCode |= 0x80;
    } // for
    return ucInvCode;
}

static U16 _TTX_ReadVpsCni(void)
{
    BYTE ucLoop, ucDataIdx;
    BYTE ucVpsDataH, ucVpsDataL;
    BYTE ucPreVpsDataH[7], ucPreVpsDataL[7], IdxCredit[7];
    BYTE ucMaxIdx, ucMaxCredit;

    ucMaxIdx = 0;
    ucMaxCredit = 0;

    for (ucDataIdx = 0; ucDataIdx < 7; ucDataIdx++)
    {
        ucPreVpsDataH[ucDataIdx] = 0x00;
        ucPreVpsDataL[ucDataIdx] = 0x00;
        IdxCredit[ucDataIdx] = 0x00;
    }

    for (ucDataIdx = 0; ucDataIdx < 7; ucDataIdx++)
    {
        MsOS_DelayTask(45);        // 1-frame period pluse 5ms margin. VPS is received once each frame.
        MDrv_VBI_GetVPS_Data(&ucVpsDataL, &ucVpsDataH);

        ucPreVpsDataL[ucDataIdx] = ucVpsDataL;
        ucPreVpsDataH[ucDataIdx] = ucVpsDataH;
    }

    for (ucDataIdx = 0;ucDataIdx < 6; ucDataIdx++)    // gather data equality credit
    {
        for (ucLoop = 1; ((ucLoop + ucDataIdx) < 7); ucLoop++)
        {
            if (ucPreVpsDataL[ucDataIdx] == ucPreVpsDataL[ucDataIdx+ucLoop])
            {
                IdxCredit[ucDataIdx]++;
                IdxCredit[ucDataIdx+ucLoop]++;
            }
        }
    }

    for (ucDataIdx = 0;ucDataIdx<7;ucDataIdx++)        // sort out maximum credit index
    {
        if (IdxCredit[ucDataIdx] > ucMaxCredit)
        {
            ucMaxCredit = IdxCredit[ucDataIdx];
            ucMaxIdx = ucDataIdx;
        }
    }
    ucVpsDataL = ucPreVpsDataL[ucMaxIdx];

    // Initialize credit related parameter for next round
    ucMaxIdx = 0;
    ucMaxCredit = 0;
    for (ucDataIdx = 0; ucDataIdx < 7; ucDataIdx++)
    {
        IdxCredit[ucDataIdx] = 0x00;
    }

    for (ucDataIdx = 0;ucDataIdx < 6; ucDataIdx++)    // gather data equality credit
    {
        for (ucLoop = 1; ((ucLoop + ucDataIdx) < 7); ucLoop++)
        {
            if (ucPreVpsDataH[ucDataIdx] == ucPreVpsDataH[ucDataIdx+ucLoop])
            {
                IdxCredit[ucDataIdx]++;
                IdxCredit[ucDataIdx+ucLoop]++;
            }
        }
    }

    for (ucDataIdx = 0;ucDataIdx<7;ucDataIdx++)
    {
        if (IdxCredit[ucDataIdx] > ucMaxCredit)
        {
            ucMaxCredit = IdxCredit[ucDataIdx];
            ucMaxIdx = ucDataIdx;
        }
    }
    ucVpsDataH = ucPreVpsDataH[ucMaxIdx];

    return MAKEWORD(ucVpsDataH, ucVpsDataL);
}


static BOOLEAN _TTX_GetCNI_VPS(WORD *pwCNI)
{
    if(MDrv_VBI_IsVPS_Ready()==FALSE)
        return FALSE;

    *pwCNI = _TTX_ReadVpsCni();

    return TRUE;
}

#if 0
static BOOLEAN _TTX_GetCNI_8_30_2(WORD *pwCNI)
{
    U_INT8 CmdArry[3]; // command buffer
    U_INT8 ucStutas = FALSE;

    // Packet 8/30 format 2
    CmdArry[2] = 2;
    if (TT_DecoderGetCNI_P830_2(&(CmdArry[0]),&(CmdArry[2])))
    {
        CmdArry[0] = _InvertByte(CmdArry[0]);
        CmdArry[1] = _InvertByte(CmdArry[1]);
        *pwCNI = MAKEWORD(CmdArry[0], CmdArry[1]);
        ucStutas = TRUE;
    }
    else
        *pwCNI = 0xffff;

    if(ucStutas==FALSE)
        return FALSE;
    else
        return TRUE;
}
#endif
static BOOLEAN _TTX_GetCNI_8_30_2(WORD *pwCNI)
{
    U_INT8 CmdArry[2]; // command buffer
    U_INT8 ucStutas = FALSE;

    // Packet 8/30 format 2
    if (TT_EngineObj.Commands.GetCNIP830_2(CmdArry) == TRUE)
    {
        CmdArry[0] = _InvertByte(CmdArry[0]);
        CmdArry[1] = _InvertByte(CmdArry[1]);
        *pwCNI = MAKEWORD(CmdArry[0], CmdArry[1]);
        ucStutas = TRUE;
    }
    else
        *pwCNI = 0xffff;

    if(ucStutas==FALSE)
        return FALSE;
    else
        return TRUE;
}

#if 0
static BOOLEAN _TTX_GetNID_8_30_1(WORD *pwNID)
{
    U_INT8 CmdArry[3]; // command buffer
    U_INT8 ucStutas = FALSE;

    // Packet 8/30 format 1
    CmdArry[2] = 2;
    if (TT_DecoderGetNI_P830_1(&(CmdArry[0]),&(CmdArry[2])))
    {
        CmdArry[0] = _InvertByte(CmdArry[0]);
        CmdArry[1] = _InvertByte(CmdArry[1]);
        *pwNID = MAKEWORD(CmdArry[0], CmdArry[1]);
        ucStutas = TRUE;
    }
    else
        *pwNID = 0xffff;

    if(ucStutas==FALSE)
        return FALSE;
    else
        return TRUE;
}
#endif

static BOOLEAN _TTX_GetNID_8_30_1(WORD *pwNID)
{
    U_INT8 CmdArry[2]; // command buffer
    U_INT8 ucStutas = FALSE;

    // Packet 8/30 format 1
    //if (TT_DecoderGetNI_P830_1(&(CmdArry[0]),&(CmdArry[2])))
    if(TT_EngineObj.Commands.GetNIP830_1(CmdArry))
    {
        CmdArry[0] = _InvertByte(CmdArry[0]);
        CmdArry[1] = _InvertByte(CmdArry[1]);
        *pwNID = MAKEWORD(CmdArry[0], CmdArry[1]);
        ucStutas = TRUE;
    }
    else
        *pwNID = 0xffff;

    if(ucStutas==FALSE)
        return FALSE;
    else
        return TRUE;
}


static void _TTX_BeforeUpdatePage(TT_U32 magPage,
                                  TT_U32 subPage)
{
  MS_DEBUG_MSG(MWprintf(MWDBG_TELETEXT, MWDBGLVL_TEST, printf("121_TTX_P%lx\n",magPage)));
  MS_DEBUG_MSG(MWprintf(MWDBG_TELETEXT, MWDBGLVL_TEST, printf("121_TTX _SubPage%lx\n",subPage)));
  UNUSED(magPage);
  UNUSED(subPage);
}
//****************************************************************************
// Start of public implementation.
//****************************************************************************
#if 0
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetCMD()
/// @brief \b Function \b Description:  Set TTX commands to TTX system
/// @param <IN>        \b wCMD             : Teletext commands
/// @param <IN>        \b parm1             : parameter 1
/// @param <IN>        \b parm2             : parameter 2
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_SetCMD(U16 wCMD, U16 parm1, U16 parm2)
{
    TT_QUEUE_MESSAGE  message;

    message.Info      = wCMD;
    message.Param1    = parm1;
    message.Param2  = parm2;
    TT_QueueSet(TT_QUEUE_KEY, &message );
    TT_MainProcess();
}
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_OnOffVBISlicer()
/// @brief \b Function \b Description:  Turn on/off the VBI slicer
/// @param <IN>        \b on               : enable/disable VBI slicer
///                                                   - -Disable(0)
///                                                   - -Enable(1)
/// @param <OUT>         \b None            :
/// @param <RET>          \b None            :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_OnOffVBISlicer(U8 on)
{
#ifndef TTX_ATV_DISABLE
    MDrv_VBI_EnableTTXSlicer(on);
#else
    UNUSED(on);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_CheckTTX()
/// @brief \b Function \b Description:  Check VBI H/W TTX indication status
/// @param <IN>        \b None               :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :
///                                                 TTX Not found(False).
///                                                 TTX Found(True)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_TTX_CheckTTX(void)
{
#ifndef TTX_ATV_DISABLE
    return MDrv_VBI_IsTTX_Ready();
#else
    return FALSE;
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_CheckTTXSignal()
/// @brief \b Function \b Description:  Test if there's TTX signal
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :
///                                         - The TTX signal is valid(TRUE)
///                                         - The TTX signal is invalid(FALSE)
/// @param <GLOBAL>    \b None            :
/// COMMENT :
/// In 300ms, if the amount of valid headers is greater than DEFAULT_TTX_HEADER_COUNT
/// then we think it is a valid TTX channel
////////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_TTX_CheckTTXSignal(void)
{
  //return TT_AcqCheckTTXSignal();
  return TT_EngineObj.Status.DoesHaveTTXSignals();
}
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_CheckTTXClockSignal()
/// @brief \b Function \b Description:  Test if there's TTX clock
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :
///                                             - There's TTX clock info(1)
///                                             - There's TTX clock info(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_TTX_CheckTTXClockSignal(void)
{

  return TT_EngineObj.Status.DoesHaveClockInfo();
}
#if 0
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_AcqGetCurrentPage()
/// @brief \b Function \b Description:  Returns the current page and subpage number.
/// @param <IN>        \b None             :
/// @param <OUT>         \b aMagPage            :   the Magpage number
/// @param <OUT>         \b aSubPage            :   the Subpage number
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_AcqGetCurrentPage (U16 *aMagPage, U16 *aSubPage)
{
    TT_ACQ_PAGE current_page;

    TT_AcqGetPage(TT_ACQ_CURRENT_PAGE, &current_page);
    *aMagPage = current_page.MagPage;
    *aSubPage = current_page.SubPage;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_AcqSetCurrentPage()
/// @brief \b Function \b Description:  Set the current page and subpage number.
/// @param <IN>         \b aMagPage            :   the Magpage number
/// @param <IN>         \b aSubPage            :   the Subpage number
/// @param <OUT>        \b None             :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_AcqSetCurrentPage (U16 aMagPage, U16 aSubPage)
{
    TT_ACQ_PAGE current_page;

    current_page.MagPage = aMagPage;
    current_page.SubPage = aSubPage;
    TT_AcqSetPage(current_page);
}
#endif
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GetWssStatus()
/// @brief \b Function \b Description:  Check the WSS decode status
/// @param <IN>        \b None               :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :   The WSS checking value
///                                                     WSS detected(1)
///                                                     WSS detected(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
U8 msAPI_TTX_GetWssStatus(void)
{
    return MDrv_VBI_IsWSS_Ready();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_ReadWssWord()
/// @brief \b Function \b Description:  Get the WSS value
/// @param <IN>        \b None               :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :  (U16) WSS value
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
U16 msAPI_TTX_ReadWssWord(void)
{
    return MDrv_VBI_GetWSS_Data();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetSource()
/// @brief \b Function \b Description:  set TTX input source
/// @param <IN>        \b Source             :  analog(0), digital(1)
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_SetSource(U8 source)
{
    TT_DRIVER_SLICER_SOURCE eSource = TT_DRIVER_SLICER_ATV;

    if(TTX_SOURCE_ANALOG==source)
        eSource = TT_DRIVER_SLICER_ATV;
    else
        eSource = TT_DRIVER_SLICER_DTV;

    TT_DriverSlicer_Set_Source(eSource);
}
#if 0
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetNaviMode()
/// @brief \b Function \b Description:  Set TTX navigation mode
/// @param <IN>        \b mode             :  TTX mode setting
///                                                 TT_DEC_HOLD_MODE(0x01)
///                                                 TT_DEC_REVEAL_MODE(0x02)
///                                                 TT_DEC_SIZE_MODE(0x04)
///                                                 TT_DEC_CANCEL_MODE(0x08)
///                                                 TT_DEC_MIX_MODE(0x10)
///                                                 TT_DEC_LIST_MODE(0x20)
///                                                 TT_DEC_CLOCK_MODE(0x40)
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_SetNaviMode(U16 mode)
{
    TT_DecoderSetMode(mode);
}
#endif
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GetSubtitlesAvailable()
/// @brief \b Function \b Description:  Check if there is subtitle page
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b           :
///                                                         Subtitle page found(1)
///                                                         Subtitle page not found(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
U32 msAPI_TTX_GetSubtitlesAvailable( void )
{
  //return TT_AcqGetSubtitlesAvailable();
  return TT_EngineObj.Status.DoesHaveSubtitles();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GetSubtitlePage()
/// @brief \b Function \b Description:  Get subtitle page information
/// @param <IN>        \b sub_index             :  Index of subtile pages
/// @param <OUT>         \b magPage            : Magazine page of the subtitle page
/// @param <OUT>         \b subPage            : Subcode of the subtitle page
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_TTX_GetSubtitlePage(U8 sub_index, U16 *magPage, U16 *subPage)
{
    //return TT_AcqGetSubtitlePage(sub_index, magPage, subPage);
    return TT_EngineObj.Commands.GetSubtitlePage(sub_index, magPage, subPage);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetOSDParameters()
/// @brief \b Function \b Description:  et TTX drawing parameters
/// @param <IN>        \b param             : the parameter indication
///                                                 - OSD_H_START (the X offset of TTX window)
///                                                 - OSD_V_START (the Y offset of TTX window)
///                                                 - OSD_WINDOW_WIDTH (the width of TTX window)
///                                                 - OSD_WINDOW_HEIGHT (the height of TTX window)
///                                                 - OSD_PAT_MODE (if it is PAT(picture and TTX) mode)
///                                                 - OSD_TRANSPARENT_COLOR_KEY (TTX transparent color key)
///                                                 - OSD_TRANSPARENT_COLOR (TTX transparent color)
/// @param <IN>        \b value             :   the value of corresponding input parameter
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_SetOSDParameters(U8 param, U32 value)
{
    // This function needs to be implemented
    // Need to refactoring all definition in TT_DriverDisplay.c
    UNUSED(param);
    UNUSED(value);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_Decoder_Process()
/// @brief \b Function \b Description:  TTX main routine, it needs to be run in task
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_Decoder_Process(void)
{
  //TT_MainProcess(); //Contains TTX ACQ, Decoder, and Display!
  TT_EngineObj.Heartbeat();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_GETColorKey()
/// @brief \b Function \b Description:  Get the LIST mode status
/// @param <IN>        \b None             :
/// @param <OUT>         \b None            :
/// @param <RET>          \b            :   LIST mode(1), non-LIST mode(0)
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_TTX_GETColorKey(void)
{
    // This function needs to be implemented
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_TTX_SetVideoStandard()
/// @brief \b Function \b Description:  Set video standard to VBI register
/// @param <IN>        \b ucVideoSystem             :
///                                                                 SIG_NTSC,           ///< NTSC
///                                                                 SIG_PAL,           ///< PAL
///                                                                 SIG_SECAM,           ///< SECAM
///                                                                 SIG_NTSC_443,           ///< NTSC 443
///                                                                 SIG_PAL_M,           ///< PAL M
///                                                                 SIG_PAL_NC,           ///< PAL NC
/// @param <OUT>         \b None            :
/// @param <RET>          \b None           :
/// @param <GLOBAL>    \b None            :
////////////////////////////////////////////////////////////////////////////////
void msAPI_TTX_SetVideoStandard(AVD_VideoStandardType ucVideoSystem)
{
#ifndef TTX_ATV_DISABLE
    VBI_VIDEO_STANDARD eStandard = VBI_VIDEO_OTHERS;

    if(ucVideoSystem==E_VIDEOSTANDARD_SECAM)
        eStandard = VBI_VIDEO_SECAM;
    else if(ucVideoSystem==E_VIDEOSTANDARD_PAL_N)
        eStandard = VBI_VIDEO_PAL_NC;
    else
        eStandard = VBI_VIDEO_OTHERS;

    MDrv_VBI_SetVideoStandard(eStandard);
#else
    UNUSED(ucVideoSystem);
#endif
}

//****************************************************************************
/// Reset TTX decoding system
/// @param None \b IN:
/// @return None :
//****************************************************************************
void msAPI_TTX_ResetAcquisition(void)
{
    //msAPI_TTX_SetCMD(TT_DEC_RESET, 0, 0);
    TT_EngineObj.Commands.Reset();
}

//****************************************************************************
/// Check each TTX system event/status is valid or not
/// @param eStatus \b IN: checking status
/// -@see eTELETEXT_STATUS
/// @param *pbValid \b OUT: checking status
/// - TRUE: the checked status is valid
/// - FALSE: the checked status is invalid
/// @return BOOLEAN : return status
/// -@see BOOLEAN
//****************************************************************************
BOOLEAN msAPI_TTX_IsStatusValid(eTELETEXT_STATUS eStatus, BOOLEAN *pbValid)
{
    //TT_DEC_STATUS decoder_status;
    *pbValid = FALSE;

    switch( eStatus )
    {
        case TT_VALID_LISTMODE:
            //TT_DecoderGetStatus(&decoder_status);
            *pbValid = TT_EngineObj.Status.IsListModeActive();//decoder_status.List;
            break;

        case TT_VALID_VPS:
            *pbValid = MDrv_VBI_IsVPS_Ready();
            break;

        case TT_VALID_PACKET_8_30_1:
            {
                WORD tmp;

                *pbValid = _TTX_GetNID_8_30_1(&tmp);
            }
            break;

        case TT_VALID_PACKET_8_30_2:
            {
                WORD tmp;

                *pbValid = _TTX_GetCNI_8_30_2(&tmp);
            }
            break;

        case TT_VALID_TELETEXT_SIGNAL:
            *pbValid = msAPI_TTX_CheckTTX();
            break;

        case TT_VALID_WSS:
            *pbValid = msAPI_TTX_GetWssStatus();
            break;

        case TT_VALID_CURRENT_PAGE:
            *pbValid = FALSE;
            break;

        case TT_VALID_MIXMODE:
            //TT_DecoderGetStatus(&decoder_status);
            *pbValid = TT_EngineObj.Status.IsMixModeActive();//decoder_status.Mix;
            break;

        case TT_VALID_CANCELMODE:
            //TT_DecoderGetStatus(&decoder_status);
            *pbValid = TT_EngineObj.Status.IsCancelModeActive();//decoder_status.Cancel;
            break;

        case TT_VALID_SUBTITLE:
            //TT_DecoderGetStatus(&decoder_status);
            *pbValid = TT_EngineObj.Status.IsCurrentPageSubNews();//decoder_status.SubNews;
            break;
        case TT_VALID_SUBPAGEINPUT_ON:
            *pbValid = TT_EngineObj.Status.IsSubpageInputOn();
            break;
        case TT_VALID_SUBPAGEINPUT_AVAILABLE:
            *pbValid = TT_EngineObj.Status.IsSubpageAvailable();
            break;
        case TT_VALID_DISPLAY_OPENED:
            *pbValid = TT_EngineObj.Status.IsDisplayOpened();
            break;
        case TT_VALID_UPDATEMODE:
            *pbValid = TT_EngineObj.Status.IsUpdateModeActive();
            break;
        case TT_VALID_SHOWNOSUBPAGE:
            *pbValid = TT_EngineObj.Status.IsShowNoSubpage();
            break;
        case TT_VALID_REVEALMODE:
            *pbValid = TT_EngineObj.Status.IsRevealModeActive();
            break;
        case TT_VALID_NEWSFLASH:
            *pbValid = TT_EngineObj.Status.IsCurrentPageFlashNews();
            break;
         default:
            break;
    }

    return TRUE;
}

//****************************************************************************
/// ATS system: Get ATV station name from Teletext system. It will base on VPS, P830FM1 and P830FM2
/// @param *sStationName \b OUT: Station name string
/// @param bArraySize \b IN: the length for input array "sStationName"
/// @param *pcPriority \b OUT: The sorting priority of sStationName
/// @return FUNCTION_RESULT : the return status
/// -@see FUNCTION_RESULT
//****************************************************************************
BOOLEAN msAPI_TTX_GetStationNameFromTeletext(BYTE *sStationName, BYTE bArraySize, BYTE *pcPriority)
{
    WORD wValueVPS = 0xFFFF;
    WORD wValueFm1 = 0xFFFF;
    WORD wValueFm2 = 0xFFFF;
    WORD StationId;
    BYTE Priority;
    BOOLEAN bValid;

    #if ENABLE_CUSTOMER_ATS_TABLE
    WORD *pExtTable = NULL;
    #endif

    memset(sStationName, 0, bArraySize);

    if( TRUE == msAPI_TTX_IsStatusValid(TT_VALID_VPS, &bValid) )
    {
       if( bValid == TRUE )
       {
            #if PRINT_ATS_INFO
            printf("Detect VPS\n");
            #endif

            _TTX_GetCNI_VPS(&wValueVPS);
       }
    }

    if( TRUE == msAPI_TTX_IsStatusValid(TT_VALID_PACKET_8_30_2, &bValid) )
    {
        if( bValid == TRUE )
        {
            #if PRINT_ATS_INFO
            printf("Detect P830FM2\n");
            #endif
            _TTX_GetCNI_8_30_2(&wValueFm2);
        }
    }

    if( TRUE == msAPI_TTX_IsStatusValid(TT_VALID_PACKET_8_30_1, &bValid) )
    {
        if( bValid == TRUE )
        {
            #if PRINT_ATS_INFO
            printf("Detect P830FM1\n");
            #endif

            _TTX_GetNID_8_30_1(&wValueFm1);
        }
    }

    #if PRINT_ATS_INFO
    printf("VPS/CNI: 0x%x P830FM1: 0x%x P830FM2: 0x%x\n", wValueVPS, wValueFm1, wValueFm2);
    #endif

    #if ENABLE_CUSTOMER_ATS_TABLE
    pExtTable = msAPI_CNI_Cus_GetExtATSTable();
    Priority = msAPI_CNI_FindStationInfo(wValueVPS, wValueFm1, wValueFm2, &StationId, pExtTable);
    #else
    Priority = msAPI_CNI_FindStationInfo(wValueVPS, wValueFm1, wValueFm2, &StationId, NULL);
    #endif
    if(Priority!=CNI_NOT_FOUND)
    {
        msAPI_CNI_GetStationName(StationId, sStationName);

        if(pcPriority!=NULL)
            *pcPriority = Priority;

        #if PRINT_ATS_INFO
        {
            BYTE buffer[6];

            memcpy(buffer, sStationName, 5);
            buffer[5] = '\0';

            printf("Matched: %s , priority 0x%bx\n", buffer, Priority);
        }
        #endif

        return TRUE;
    }

    return FALSE;
}

BOOLEAN msAPI_TTX_SetListPageNumber(BYTE cListIndex, WORD wPageNumber)
{
    WORD wPageRed, wPageGreen, wPageYellow, wPageCyan;

    TT_EngineObj.Commands.GetListPageNums(&wPageRed, &wPageGreen, &wPageYellow, &wPageCyan);
    /*
    if(( wPageNumber < MIN_TELETEXT_PAGE )||(wPageNumber > MAX_TELETEXT_PAGE ))
    {
        return FALSE;
    }
    */
    if(( wPageNumber  > MIN_TELETEXT_PAGE ) && (wPageNumber < MAX_TELETEXT_PAGE))
    {
        if(cListIndex == lmiRED)
            wPageRed = wPageNumber;
        else if(cListIndex == lmiGREEN)
            wPageGreen = wPageNumber;
        else if(cListIndex == lmiYELLOW)
            wPageYellow = wPageNumber;
        else if(cListIndex == lmiCYAN)
            wPageCyan = wPageNumber;
        else
            return FALSE;

        TT_EngineObj.Commands.SetListPageNums(wPageRed, wPageGreen, wPageYellow, wPageCyan);

        return TRUE;
      }
    else
        return FALSE;
}

BOOLEAN msAPI_TTX_GetListPageNumber(BYTE cListIndex, WORD *pwPageNumber)
{
    WORD wPageRed, wPageGreen, wPageYellow, wPageCyan;

    TT_EngineObj.Commands.GetListPageNums(&wPageRed, &wPageGreen, &wPageYellow, &wPageCyan);

    if(cListIndex == lmiRED){
         if( wPageRed != 0xFFF && wPageRed >= 0x800)
            wPageRed = (TT_U16)(wPageRed - 0x800);
        *pwPageNumber = wPageRed;
        }
    else if(cListIndex == lmiGREEN){
             if( wPageGreen != 0xFFF && wPageGreen >= 0x800)
            wPageGreen = (TT_U16)(wPageGreen - 0x800);
        *pwPageNumber = wPageGreen;
        }
    else if(cListIndex == lmiYELLOW){
                 if( wPageYellow != 0xFFF && wPageYellow >= 0x800)
            wPageYellow = (TT_U16)(wPageYellow - 0x800);
        *pwPageNumber = wPageYellow;
        }
    else if(cListIndex == lmiCYAN){
                     if( wPageCyan != 0xFFF && wPageCyan >= 0x800)
            wPageCyan = (TT_U16)(wPageCyan - 0x800);
        *pwPageNumber = wPageCyan;
        }
    else
        return FALSE;

    if(( *pwPageNumber  > MIN_TELETEXT_PAGE ) && (*pwPageNumber < MAX_TELETEXT_PAGE))
        return TRUE;
    else
        return FALSE;

}
//****************************************************************************
/// For TTX list mode system. It will get the corresponding pagelink from CM DB, and set to TTX List mode
/// @param None \b IN:
/// @return BOOLEAN : return status
/// -@see BOOLEAN
//****************************************************************************
BOOLEAN msAPI_TTX_ModifyListPageNumber(void)
{
    WORD wPageRed = 0xFFF,
         wPageGreen = 0xFFF,
         wPageYellow = 0xFFF,
         wPageCyan = 0xFFF;

    msAPI_ATV_GetListPageNumber((BYTE) lmiRED, &wPageRed);
    msAPI_ATV_GetListPageNumber((BYTE) lmiGREEN, &wPageGreen);
    msAPI_ATV_GetListPageNumber((BYTE) lmiYELLOW, &wPageYellow);
    msAPI_ATV_GetListPageNumber((BYTE) lmiCYAN, &wPageCyan);

    TT_EngineObj.Commands.SetListPageNums(wPageRed, wPageGreen, wPageYellow, wPageCyan);
    return TRUE;
}

//****************************************************************************
/// For TTX list mode system. It will save the corresponding pagelink to CM DB
/// @param None \b IN:
/// @return BOOLEAN : return status
/// -@see BOOLEAN
//****************************************************************************
BOOLEAN msAPI_TTX_SaveListPageNumber(void)
{
    WORD wPageRed, wPageGreen, wPageYellow, wPageCyan;

    TT_EngineObj.Commands.GetListPageNums(&wPageRed, &wPageGreen, &wPageYellow, &wPageCyan);

    msAPI_ATV_SetListPageNumber((BYTE) lmiRED, wPageRed);
    msAPI_ATV_SetListPageNumber((BYTE) lmiGREEN, wPageGreen);
    msAPI_ATV_SetListPageNumber((BYTE) lmiYELLOW, wPageYellow);
    msAPI_ATV_SetListPageNumber((BYTE) lmiCYAN, wPageCyan);

    return TRUE;
}
extern BOOLEAN bTTXInISR;
U32 MApi_TTX_GetWriteAddress(U8 SecFltNo)
{
    U32 addr = 0;

    if(SecFltNo==DMX_DMXID_NULL)
        return TTX_VBI_BUFFER_ADDR;

    MApi_DMX_SectWriteGet(SecFltNo,&addr);

    return addr;
}

void  msAPI_TTX_SetTTXSubtitleTitleOn(TT_BOOL bOn)
{
    TT_EngineObj.Commands.SetSubtitleTitleOnWithTTXMode(bOn);
}

//****************************************************************************
/// Init the TTX whole system. This function must be called at system startup
/// @param None \b IN:
/// @return BOOLEAN :
/// - TRUE:   TTX init succeed
/// - FASLE:  TTX init fail
//****************************************************************************

BOOL msAPI_TTX_InitSystem(void)
{
    DEBUG_API_TTX( printf("msAPI_TTX_InitSystem()\n"););

    #define MAX_TTX_PAGES_NUM ((TTXBUF_START_LEN - 0x40000)/0x0800UL)
    #if (MAX_TTX_PAGES_NUM<20 || MAX_TTX_PAGES_NUM>4096)
    #error ttx-init-error
    #endif

    MDrv_DMX_TTX_SetFilterID(DMX_DMXID_NULL);
    MDrv_DMX_TTX_SetCB(MApi_TTX_GetWriteAddress);
#ifndef TTX_ATV_DISABLE
    MDrv_VBI_Init(E_VBI_TELETEXT);
#endif
    TT_DriverSlicer_SetParameter(TTX_VBI_BUFFER_ADDR, TTX_VBI_BUFFER_COUNT);

    TT_EngineObj.SetupDecoder(&TT_DecoderL15);

    TT_GERenderTarget.Create(E_GOP_APP);

#ifdef TTX_USING_MSTAR_FONT_BIN
    TT_CharRenderSystem.Create(TT_MStarFontCharsMan,
                               &TT_GERenderTarget);

    TT_EngineObj.SetupRenderSystem(&TT_CharRenderSystem);
#else
    TT_BitmapRenderSystem.Create(TT_DefaultFontCharsMan,
                                 &TT_GERenderTarget);

    TT_EngineObj.SetupRenderSystem(&TT_BitmapRenderSystem);
#endif

    stSizeDisplayModeConfig.IsNewSizeDisplayMode = TRUE;
    TT_EngineObj.SetupBehaviorConfig(BEHAVIOR_CONFIG_SIZE_DISPLAY_MODE, &stSizeDisplayModeConfig);

    stPagenumberConfig.PrefixWithP = TRUE;
    stPagenumberConfig.TopPrefixWithP = TRUE;
    TT_EngineObj.SetupBehaviorConfig(BEHAVIOR_CONFIG_PAGENUMBER, &stPagenumberConfig);

    stListModeColorkeyBarConfig.FlashModeForSelection = TRUE;
    stListModeColorkeyBarConfig.ShowListSymbol = FALSE;
    TT_EngineObj.SetupBehaviorConfig(BEHAVIOR_CONFIG_LISTMODE_COLORKEY_BAR, &stListModeColorkeyBarConfig);

    stUpdateModeConfig.IndicateC8UpdateByCancelUpdateMode = FALSE;
    stUpdateModeConfig.ForegroundNoUpdate = TT_COLOR_WHITE;
    stUpdateModeConfig.BackgroundNoUpdate = TT_COLOR_BLACK;
    stUpdateModeConfig.ForegroundAfterUpdate = TT_COLOR_BLACK;
    stUpdateModeConfig.BackgroundAfterUpdate = TT_COLOR_YELLOW;
    stUpdateModeConfig.DoesShowPageNumber = TRUE;
    TT_EngineObj.SetupBehaviorConfig(BEHAVIOR_CONFIG_UPDATE_MODE, &stUpdateModeConfig);
    TT_EngineObj.SetupBehaviorConfig(BEHAVIOR_CONFIG_CANCEL_MODE, NULL);

    stNavigationBarConfig.TopLinkShowPageNumber = FALSE;
    TT_EngineObj.SetupBehaviorConfig(BEHAVIOR_CONFIG_NAVIGATION_BAR_CONFIG, &stNavigationBarConfig);

    stSubpagebarConfig.ConfigFlags = 0xFFFFFFFFU;
    stSubpagebarConfig.SubpageBarBackground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_BACKGROUND;
    stSubpagebarConfig.ActiveCycleSymbolForeground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_CYCLE_SYMBOL_FOREGROUND;
    stSubpagebarConfig.ActiveCycleSymbolBackground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_CYCLE_SYMBOL_BACKGROUND;
    stSubpagebarConfig.InactiveCycleSymbolForeground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_CYCLE_SYMBOL_FOREGROUND;
    stSubpagebarConfig.InactiveCycleSymbolBackground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_CYCLE_SYMBOL_BACKROUND;
    stSubpagebarConfig.ActiveSubpageForeground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_SUBPAGE_FOREGROUND;
    stSubpagebarConfig.ActiveSubpageBackground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_SUBPAGE_BACKGROUND;
    stSubpagebarConfig.InactiveSubpageForeground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_SUBPAGE_FOREGROUND;
    stSubpagebarConfig.InactiveSubpageBackground = TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_SUBPAGE_BACKROUND;
    stSubpagebarConfig.IsVisible = TRUE;
    stSubpagebarConfig.IsShowNoSubpage = FALSE;
    TT_EngineObj.SetupBehaviorConfig(BEHAVIOR_CONFIG_SUBPAGE_BAR, &stSubpagebarConfig);

    TT_EngineObj.SetupEventHandler(EVENT_HANDLER_BEFORE_UPDATE_PACGE,
                                   _TTX_BeforeUpdatePage);

    TT_EngineObj.Init(TTX_INTERNAL_BUFFER_ADDR,
                      TTX_INTERNAL_BUFFER_SIZE);

    TT_EngineObj.Commands.SetListPageNums(0x100, 0x200, 0x300, 0x400);

    return TRUE;
}

//****************************************************************************
/// Get the TTX TTX real start buffer in DRAM
/// @param None \b IN:
/// @return U32 : TTX VBI start buffer address in DRAM
//****************************************************************************
U32 msAPI_TTX_GetVBIStartAddress(void)
{
    return TTX_VBI_BUFFER_ADDR;
}

//****************************************************************************
/// Get the TTX VBI buffer size in DRAM
/// @param None \b IN:
/// @return U32 : TTX real start buffer address in DRAM
//****************************************************************************
U32 msAPI_TTX_GetVBI_BufferSize(void)
{
    return TTXBUF_VBI_SIZE;
}

//****************************************************************************
/// Get the status which TTX packet acquire is running in ISR or not
/// @param None \b IN:
/// @return BOOLEAN :
/// - TRUE:   TTX ISR is running
/// - FASLE:  TTX ISR is not running
//****************************************************************************
U8 msAPI_TTX_Get_VBIAcquireEnableStatus(void)
{
    return TT_DriverSlicer_IsAcquireEnabled();//_bAcquireEnable;
}

//****************************************************************************
/// Enable/disable TTX packet acquire in ISR
/// @param enable \b IN:
/// - TRUE: enable TTX packet acquire in ISR
/// - DISABLE: disable TTX packet acquire in ISR
/// @return None :
//****************************************************************************
void msAPI_TTX_VBIAcquireEnable(U8 enable)
{
    _bAcquireEnable = enable;
    TT_DriverSlicer_AcquireEnable(enable);
}

//****************************************************************************
/// Enable/disable TTX packet acquire in ISR (just for ATV scan purpose)
/// @param enable \b IN:
/// - TRUE: enable TTX packet acquire in ISR
/// - DISABLE: disable TTX packet acquire in ISR
/// @return None :
//****************************************************************************
void msAPI_TTX_VBIAcquireScanEnable(U8 enable)
{
    _bScanEnable = enable;
    TT_DriverSlicer_AcquireEnable(enable);
}

//****************************************************************************
/// msAPI_TTX_LoadFon(): Load TTX font to DRAM
/// @param None \b IN:
/// @return None :
//****************************************************************************
void msAPI_TTX_LoadFont(void)
{
    //TT_DriverFont_LoadFont();
}

//****************************************************************************
/// msAPI_TTX_SetFontInfo(): set TTX font information
/// @param FontW \b IN: the font width
/// @param FontH \b IN: the font height
/// @param CharW \b IN: the displayed character width
/// @param CharH \b IN: the displayed character height
/// @param addr \b IN: the font address in DRAM
/// @param glyphSize \b IN: the glyph size of the font
/// @param u16BinID \b IN: the font BIN ID in flash
/// @return None :
//****************************************************************************
void msAPI_TTX_SetFontInfo(U_INT8 FontW, U_INT8 FontH,  U_INT8 CharW, U_INT8 CharH, U_INT32 addr, U_INT32 flashAddr, U_INT8 glyphSize, U_INT16 u16BinID)
{
    //TT_DriverFont_SetFontInfo(FontW, FontH, CharW, CharH, addr, flashAddr, glyphSize, u16BinID);
    UNUSED(FontW);
    UNUSED(FontH);
    UNUSED(CharW);
    UNUSED(CharH);
    UNUSED(addr);
    UNUSED(flashAddr);
    UNUSED(glyphSize);
    UNUSED(u16BinID);
}


//****************************************************************************
/// (DTV) set TTX filter ID to TTX system
/// @param u8DTVTTXFid \b IN: TTX filter ID
/// @return None :
//****************************************************************************
void msAPI_TTX_SetTTXFid(U_INT8 u8DTVTTXFid)
{
    MDrv_DMX_TTX_SetFilterID(u8DTVTTXFid);
}

void msAPI_TTX_OpenRenderObj(U32 ttxMarginH,
                             U32 ttxMarginV,
                             U32 displayX,
                             U32 displayY,
                             U32 displayWidth,
                             U32 displayHeight,
                             BOOL isTransparent)
{
  TT_GERenderTarget_Attach(ttxMarginH,
                           ttxMarginV,
                           displayX,
                           displayY,
                           displayWidth,
                           displayHeight,
                           isTransparent);

}

void msAPI_TTX_CloseRenderObj()
{
  TT_GERenderTarget_Detach();
}

void msAPI_TTX_CollectPackets(void)
{
#ifdef MSOS_TYPE_LINUX
#else
  TT_DriverSlicer_AcquireInISR();
#endif
}

void msAPI_TTX_Stop(void)
{
    DEBUG_API_TTX( printf("msAPI_TTX_Stop()\n"););
    TT_EngineObj.ShutDown();
}

void msAPI_TTX_Run(void)
{
  TT_EngineObj.KickOff();
  //msAPI_TTX_SetTTXSubtitleTitleOn(TRUE);
}

void msAPI_TTX_Command(TELETEXT_COMMAND command)
{
    msAPI_TTX_CommandExt(command,
                         TRUE,
                         0U,
                         0U);
}

void msAPI_TTX_CommandExt(TELETEXT_COMMAND command,
                                     MS_BOOL boolParam,
                                     MS_U32 param1,
                                     MS_U32 param2)
{
    switch(command)
    {
        case TTX_DIGIT_0:
        case TTX_DIGIT_1:
        case TTX_DIGIT_2:
        case TTX_DIGIT_3:
        case TTX_DIGIT_4:
        case TTX_DIGIT_5:
        case TTX_DIGIT_6:
        case TTX_DIGIT_7:
        case TTX_DIGIT_8:
        case TTX_DIGIT_9:
            TT_EngineObj.Commands.Digit(command - TTX_DIGIT_0);
            break;

        case TTX_PAGE_UP:
        {
            BOOLEAN isSubpageInputOn;
            BOOLEAN isSubpageAvailable;

            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_ON, &isSubpageInputOn);
            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_AVAILABLE, &isSubpageAvailable);

            TT_EngineObj.Commands.KeyUp(isSubpageInputOn&&isSubpageAvailable);
        }
        break;

        case TTX_PAGE_DOWN:
        {
            BOOLEAN isSubpageInputOn;
            BOOLEAN isSubpageAvailable;

            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_ON, &isSubpageInputOn);
            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_AVAILABLE, &isSubpageAvailable);

            TT_EngineObj.Commands.KeyDown(isSubpageInputOn&&isSubpageAvailable);

            break;
        }


        case TTX_SUBPAGE:
            TT_EngineObj.Commands.SubpageInputOnOff();
            break;

        case TTX_PAGE_LEFT:
            TT_EngineObj.Commands.KeyLeft();
            break;

        case TTX_PAGE_RIGHT:
            TT_EngineObj.Commands.KeyRight();
            break;

        case TTX_RED:
        {
            BOOLEAN isSubpageInputOn;
            BOOLEAN isSubpageAvailable;

            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_ON, &isSubpageInputOn);
            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_AVAILABLE, &isSubpageAvailable);

            if(!isSubpageInputOn)
            {
                TT_EngineObj.Commands.KeyRed();
            }
            else
            {
                TT_EngineObj.Commands.KeyDown(isSubpageAvailable);
            }

            break;
        }


        case TTX_GREEN:
        {
            BOOLEAN isSubpageInputOn;
            BOOLEAN isSubpageAvailable;

            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_ON, &isSubpageInputOn);
            msAPI_TTX_IsStatusValid(TT_VALID_SUBPAGEINPUT_AVAILABLE, &isSubpageAvailable);

            if(!isSubpageInputOn)
            {
                TT_EngineObj.Commands.KeyGreen();
            }
            else
            {
                TT_EngineObj.Commands.KeyUp(isSubpageAvailable);
            }

            break;
        }


        case TTX_YELLOW:
            TT_EngineObj.Commands.KeyYellow();
            break;

        case TTX_CYAN:
            TT_EngineObj.Commands.KeyCyan();
            break;

        case TTX_MIX:
            TT_EngineObj.Commands.MixModeOnOff();
            break;

        case TTX_SUBTITLE_TTX_ON:
            TT_EngineObj.Commands.SubtitleOn(param1, param2);
            break;

        case TTX_SUBTITLE_NAVIGATION_MODE:
            TT_EngineObj.Commands.SubtitleNavigationMode();
            break;

        case TTX_TEXT:
            TT_EngineObj.Commands.TTXOn();
            break;

        case TTX_PAT:
            TT_EngineObj.Commands.TTXOnPAT();
            break;

        case TTX_TV:
            TT_EngineObj.Commands.TTXOff();
            break;

        case TTX_CLOCK:
            if(boolParam == TRUE)
                TT_EngineObj.Commands.ClockOn();
            else
                TT_EngineObj.Commands.ClockOff();
            break;

        case TTX_STATUS_DISPLAY:
            if(boolParam == TRUE)
                TT_EngineObj.Commands.StatusOn(param1, param2);
            else
                TT_EngineObj.Commands.StatusOff();
            break;

        case TTX_UPDATE:
            TT_EngineObj.Commands.KeyUpdate();
            break;

        case TTX_INDEX:
            TT_EngineObj.Commands.KeyIndex();
            break;

        case TTX_HOLD:
            TT_EngineObj.Commands.KeyHold();
            break;

        case TTX_LIST:
            TT_EngineObj.Commands.KeyList(0);
            break;

        case TTX_SIZE:
            TT_EngineObj.Commands.KeySize();
            break;

        case TTX_REVEAL:
            TT_EngineObj.Commands.KeyReveal();
            break;

        case TTX_CLEAR_LIST:
            TT_EngineObj.Commands.ClearList();
            break;

        case TTX_GOTO_PAGE:
            TT_EngineObj.Commands.SetPage(param1, param2);
            break;

        case TTX_CYCLE_SUBPAGE:
             TT_EngineObj.Commands.SetSubpageCycle();
             break;

        case TTX_CANCEL:
            TT_EngineObj.Commands.KeyCancel();
             break;

        default:
            MS_ASSERT(0);
        break;
    }
}

void msAPI_TTX_SetLanguageGroup(TT_Charset_Group language)
{
    DEBUG_API_TTX( printf("msAPI_TTX_SetLanguageGroup(lang=%u)\n", language););

    switch(language)
    {
        case TT_Charset_Group_West:
            TT_EngineObj.Commands.SetLanguageWest();
            break;

        case TT_Charset_Group_East:
            TT_EngineObj.Commands.SetLanguageEast();
            break;

        case TT_Charset_Group_Russian:
            TT_EngineObj.Commands.SetLanguageRussian();
            break;

        case TT_Charset_Group_Arabic:
            TT_EngineObj.Commands.SetLanguageArabic();
            break;

        case TT_Charset_Group_Farsi:
            TT_EngineObj.Commands.SetLanguageFarsi();
            break;

        default:
            MS_ASSERT(0);
            break;
    }
}

void msAPI_TTX_SetPage(TT_U32 magNum, TT_U32 pageNum)
{
    TT_EngineObj.Commands.SetPage(magNum, pageNum);
}

void msAPI_TTX_SetDTVIndexPage(TT_U32 magNum, TT_U32 pageNum)
{
    TT_EngineObj.Commands.SetDTVIndexPage(magNum, pageNum);
}

void msAPI_TTX_SetFlofTopEnable(void)
{
    DEBUG_API_TTX( printf("msAPI_TTX_SetFlofTopEnable()\n"););
    TT_EngineObj.Commands.SetColorKeyMode(TT_COLOR_KEY_NAVI_FLOF_TOP);
}

BOOLEAN msAPI_TTX_GetHeaderTime(TT_U8 *Hour, TT_U8 *Minute, TT_U8 *Second)
{
    return TT_EngineObj.Commands.GetClockData(Hour, Minute, Second);
}

BOOLEAN msAPI_TTX_DoesReceiveDataPacketWithPrefix(U16 magPage, U8* prefix, U16 size)
{
    return 0 == TT_EngineObj.Commands.QueryIfDataPacketWitPrefix(magPage,
                                                                 prefix,
                                                                 size);
}

void msAPI_TTX_GetInternalTTXWindowSize(U32* width,
                                              U32* height,
                                              U32 ttxMarginH,
                                              U32 ttxMarginV,
                                              U32 displayWidth,
                                              U32 displayHeight)
{
    TT_GERenderTarget_GetInternalWindowSize(width,
                                                  height,
                                                  ttxMarginH,
                                                  ttxMarginV,
                                                  displayWidth,
                                                  displayHeight);
}


void msAPI_TTX_SetChannelChangeTime( U32 channel_change_time)
{
    TT_PacketBufferSetChannelChangeStartTime(channel_change_time);
}

U8 msAPI_TTX_GetC12C13C14Values()
{
    return TT_EngineObj.Status.GetC12C13C14Values();
}

#endif  // #if (ENABLE_TTX)

#undef _MSAPI_TTX_C_
#endif
