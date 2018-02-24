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

#ifndef MAPP_TTSCONTROLHANDLER_H
#define MAPP_TTSCONTROLHANDLER_H

#include "Board.h"

#if ENABLE_ATSC_TTS

#include "datatype.h"

#include "libMsTTS.h"


#define TTS_MUTE_BGM                    (1)


#ifdef MAPP_TTSCONTROLHANDLER_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

//TTS tags for number, date, and time.
#define TTS_SPEAK_TAG_END       "</say-as>"
#define TTS_SPEAK_NUMBER_CARDINAL "<say-as interpret-as=\"cardinal\">"
#define TTS_SPEAK_NUMBER_ORDINAL "<say-as interpret-as=\"ordinal\">"
#define TTS_SPEAK_NUMBER_DIGITS "<say-as interpret-as=\"digits\">"
#define TTS_SPEAK_CHARACTERS    "<say-as interpret-as=\"characters\">"
#define TTS_SPEAK_WORDSCHARS    "<say-as interpret-as=\"wordschars\">"
#define TTS_SPEAK_DATE_MDY      "<say-as interpret-as=\"date\" format=\"mdy\">"
#define TTS_SPEAK_DATE_DMY      "<say-as interpret-as=\"date\" format=\"dmy\">"
#define TTS_SPEAK_DATE_YMD      "<say-as interpret-as=\"date\" format=\"ymd\">"
#define TTS_SPEAK_DATE_MD       "<say-as interpret-as=\"date\" format=\"md\">"
#define TTS_SPEAK_DATE_DM       "<say-as interpret-as=\"date\" format=\"dm\">"
#define TTS_SPEAK_DATE_YM       "<say-as interpret-as=\"date\" format=\"ym\">"
#define TTS_SPEAK_DATE_MY       "<say-as interpret-as=\"date\" format=\"my\">"
#define TTS_SPEAK_DATE_D        "<say-as interpret-as=\"date\" format=\"d\">"
#define TTS_SPEAK_DATE_M        "<say-as interpret-as=\"date\" format=\"m\">"
#define TTS_SPEAK_DATE_Y        "<say-as interpret-as=\"date\" format=\"y\">"
#define TTS_SPEAK_TIME_HMS      "<say-as interpret-as=\"time\" format=\"hms\">"
#define TTS_SPEAK_TIME_HM       "<say-as interpret-as=\"time\" format=\"hm\">"
#define TTS_SPEAK_TIME_H        "<say-as interpret-as=\"time\" format=\"h\">"

// MAILBOX relative
#if 0//(TTS_IS_ON_HK == 0)
#define TTS_MBX_CMDID_IDX           0
#define TTS_MBX_TYPE_IDX          TTS_MBX_CMDID_IDX + 1
#define TTS_MBX_DATA1_IDX         TTS_MBX_TYPE_IDX + 1
#define TTS_MBX_DATA2_IDX         TTS_MBX_DATA1_IDX + 1
#define TTS_MBX_DATA3_IDX         TTS_MBX_DATA2_IDX + 1
#define TTS_MBX_DATA4_IDX         TTS_MBX_DATA3_IDX + 1
#define TTS_MBX_DATA5_IDX         TTS_MBX_DATA4_IDX + 1
#define TTS_MBX_DATA6_IDX         TTS_MBX_DATA5_IDX + 1
#define TTS_MBX_DATA7_IDX         TTS_MBX_DATA6_IDX + 1
#define TTS_MBX_DATA8_IDX         TTS_MBX_DATA7_IDX + 1
#define TTS_MBX_BASE_ADDR 0x1033A0
#define TTS_MBX_REG(offset)                         (TTS_MBX_BASE_ADDR + offset)
#define TTS_MBXReadByte(offset)                     MDrv_ReadByte(TTS_MBX_REG(offset))
#define TTS_MBXRead2Byte(offset)                     MDrv_Read2Byte(TTS_MBX_REG(offset))
#define TTS_MBXRead4Byte(offset)                    MDrv_Read4Byte(TTS_MBX_REG(offset))
#define TTS_MBXWriteByte(offset, value)             MDrv_WriteByte(TTS_MBX_REG(offset), value)
#define TTS_MBXWrite2Byte(offset, value)             MDrv_Write2Byte(TTS_MBX_REG(offset), value)
#define TTS_MBXWriteByteMask(offset, value, mask)   MDrv_WriteByteMask(TTS_MBX_REG(offset), value, mask)
#define TTS_MBXWrite4Byte(offset, value)            MDrv_Write4Byte(TTS_MBX_REG(offset), value)
#endif

typedef enum
{
    MB_TTS_LANG_NONE    = TTS_LANG_NONE,
    MB_TTS_LANG_ENGLISH = LANG_EN_US,
    MB_TTS_LANG_SPANISH = LANG_ES_MX,
    MB_TTS_LANG_FRANCH  = LANG_FR_FR,
    MB_TTS_LANG_KOREAN  = LANG_KO_KR,
} EunMsTtsLangId;


#if (TTS_IS_ON_HK == 0)
//-------------------------------
// E_MBX_CLASS_TTS_ENGIE_CMD_IO
//-------------------------------
typedef enum
{
    MB_TTS_ENGINE_CMD_NONE      = 0x00,
    //HK
    MB_TTS_ENGINE_SET_INIT_CMD  =0x01,
    MB_TTS_ENGINE_SET_TEXT_CMD  = 0x02,


    // HK --> R2
    MB_TTS_ENGINE_GET_CAP_CMD      = 0x10,   // supported languages, voice number , buffer size, is_pitch_adjustable, is_voice_adjustable, is_speed_adjustable
    MB_TTS_ENGINE_GET_LANG_CMD     = 0x11,   // 1 parameter : lang
    MB_TTS_ENGINE_GET_PITCH_CMD    = 0x12,   // 1 parameter : pitch
    MB_TTS_ENGINE_GET_VOICE_CMD    = 0x13,   // 1 parameter : voice
    MB_TTS_ENGINE_GET_SPEED_CMD    = 0x14,   // 1 parameter : speed

    MB_TTS_ENGINE_SET_LANG_CMD     = 0x15,
    MB_TTS_ENGINE_SET_PITCH_CMD    = 0x16,
    MB_TTS_ENGINE_SET_VOICE_CMD    = 0x17,
    MB_TTS_ENGINE_SET_SPEED_CMD    = 0x18,

    MB_TTS_ENGINE_SAY_CMD          = 0x19,   // 2 parameters : text buffer and text length
    MB_TTS_ENGINE_RBUF_CMD         = 0x20,   // 2 parameters : buffer address and buffer length

    // R2 --> HK
    MB_TTS_ENGINE_GET_CAP_ACK      = 0x80,
    MB_TTS_ENGINE_GET_LANG_ACK     = 0x81,    // 1 parameter : lang
    MB_TTS_ENGINE_GET_PITCH_ACK    = 0x82,    // 1 parameter : pitch
    MB_TTS_ENGINE_GET_VOICE_ACK    = 0x83,    // 1 parameter : voice
    MB_TTS_ENGINE_GET_SPEED_ACK    = 0x84,    // 1 parameter : speed

    MB_TTS_ENGINE_SET_LANG_ACK     = 0x85,
    MB_TTS_ENGINE_SET_PITCH_ACK    = 0x86,
    MB_TTS_ENGINE_SET_VOICE_ACK    = 0x87,
    MB_TTS_ENGINE_SET_SPEED_ACK    = 0x88,

    MB_TTS_ENGINE_WBUF_CMD         = 0x89,   // 2 parameters : buffer address and buffer length

    MB_TTS_ENGINE_SET_SAY_ACK      = 0x90,

    MB_TTS_ENGINE_CMD_NUM,
} MB_TTS_ENGINE_CMD_IO;
#endif

typedef enum
{
    EN_TTS_SPEAK_NUMBER_CARDINAL,   // 23 -> twenty three
    EN_TTS_SPEAK_NUMBER_ORDINAL,    //  3 -> third
    EN_TTS_SPEAK_NUMBER_DIGITS,     // 23 -> two three
    EN_TTS_SPEAK_CHARACTERS,        // ECFA -> E C F A
    EN_TTS_SPEAK_WORDSCHARS,        // HDMI source - > H D M I source"
    EN_TTS_SPEAK_DATE_MDY,          // mm/dd/yyyy
    EN_TTS_SPEAK_DATE_DMY,          //  dd/mm/yyyy
    EN_TTS_SPEAK_DATE_YMD,          // yyyy/mm/dd
    EN_TTS_SPEAK_DATE_MD,           // mm/dd
    EN_TTS_SPEAK_DATE_DM,           // dd/mm
    EN_TTS_SPEAK_DATE_YM,           // yyyy/mm
    EN_TTS_SPEAK_DATE_MY,           // mm/yyyy
    EN_TTS_SPEAK_DATE_D,            // dd
    EN_TTS_SPEAK_DATE_M,            // mm
    EN_TTS_SPEAK_DATE_Y,            // yyyy
    EN_TTS_SPEAK_TIME_HMS,          // hh:mm:ss
    EN_TTS_SPEAK_TIME_HM,           // hh:mm
    EN_TTS_SPEAK_TIME_H,            // hh
    EN_TTS_SPEAK_NORMAL,            //TTS engine default
} EN_TTS_SPEAK;


typedef enum
{
    STATE_TTS_INIT,
    STATE_TTS_DECODE_INIT, // Init engine, Get string,...
    STATE_TTS_DECODING,    // Decode for gen PCM
    STATE_TTS_WAIT_DEC_BUF_EMPTY,
    STATE_TTS_WAIT_AUDIO_BUF_EMPTY,
} EN_TTS_STATE;

//======================================================================================
INTERFACE BOOLEAN MApp_TTSControlHandler_Init(EunMsTtsLangId eMsTtsLangId, EunMsTtsLangId eMsTtsLangId_2nd);
INTERFACE void MApp_TTSControlSetLanguage(EunMsTtsLangId eMsTtsLangId, EunMsTtsLangId eMsTtsLangId_2nd);

INTERFACE void MApp_TTSControlHandler_Main(void);
INTERFACE void MApp_TTS_ISR_1ms(void);

//--------------------------------------------------------------------------------------------
//value: 0 ~ 500; default 100
INTERFACE void MApp_TTSControlSetVolume(U16 u16Volume);

//value: 50 ~ 200; default 100
INTERFACE void MApp_TTSControlSetPitch(U16 u16Pitch);

// Speed range: 50 ~ 250
INTERFACE void MApp_TTSControlSetSpeed(U16 u16Speed);
//---------------------------------------------------------------------------------------------
void MApp_TTS_Set_PreloadBuffer_ms(U32 u32DataMs);

void MApp_TTS_Set_EnableUserBreak(BOOLEAN bEnUserBreak);
BOOLEAN MApp_TTS_Get_EnableUserBreak(void);
//---------------------------------------------------------------------------------------------
const char* MApp_TTSControlSpeakFormatMapping(EN_TTS_SPEAK enSpeakFormat);

//void MApp_TTSControlSetTextAndSay(U16* str, U16 len);
//---------------------------------------------------------------------------------------------
BOOLEAN MApp_TTS_Say_Start(void);
BOOLEAN MApp_TTS_Say_Stop(void);

//---------------------------------------------------------------------------------------------
U32 MApp_TTS_Get_AudioBufferLevel_ms(void);
U32 MApp_TTS_Get_AudioBufLevel_ms_ISR(void);

U32 MApp_TTS_Get_DecodeBufferLevel_Byte_ISR(void);
U32 MApp_TTS_Get_DecodeBufferLevel_Byte(void);
U32 MApp_TTS_Get_DecodeBufferLevel_ms(void);
U32 MApp_TTS_Get_DecodeBufferLevel_ms_ISR(void); // Unit is ms

typedef enum
{
    TTS_DEC_BUF_EMPTY,
    TTS_DEC_BUF_NOT_FULL,
    TTS_DEC_BUF_FULL,
} EunTTSDecodeBufStatus;
EunTTSDecodeBufStatus MApp_TTS_Get_DecodeBufStatus(void);

//---------------------------------------------------------------------------------------------

BOOLEAN MApp_TTS_Get_Enable(void);
BOOLEAN MApp_TTS_Is_InWorking(void);
EN_TTS_STATE MApp_TTS_Get_State(void);
BOOLEAN MApp_TTS_Is_AudioStart(void);
BOOLEAN MApp_TTS_Is_InSpeaking(void);

void MApp_TTS_WaitDecodeDone(void);
#define TTS_NO_TIMEOUT  0xFFFFFFFF
void MApp_TTS_WaitSayFinish(U32 u32WaitTimeout);
//---------------------------------------------------------------------------------------------

typedef enum
{
    TTS_DECODE_MODE_NORMAL,
    TTS_DECODE_MODE_FORCE_DEC_BUF_FULL, // MApp_TTSControlHandler_Main() will continue gen data until buffer size is full
    TTS_DECODE_MODE_FORCE_DEC_BUF_SIZE, // MApp_TTSControlHandler_Main() will continue gen data until buffer size is XXX ms
} EunTTSDecodeMode;
void MApp_TTS_Set_DecodeDataMode(EunTTSDecodeMode eTTSDecodeMode, U32 u32Para);

void MApp_TTS_ContiuneDecodingUntilDecBufFull(void);

//---------------------------------------------------------------------------------------------

#undef INTERFACE

#endif // ENABLE_ATSC_TTS

#endif // MAPP_TTSCONTROLHANDLER_H

