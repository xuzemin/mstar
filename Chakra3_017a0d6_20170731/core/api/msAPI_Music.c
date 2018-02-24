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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_MP3.c
/// @brief API for MP3 decoding and display
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_MUSIC_C

#include <stdio.h>
#include <string.h>

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "sysinfo.h"
#include "hwreg.h"
#include "BinInfo.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "drvAUDIO.h"
#include "SysInit.h"
// eaton, compile issue, 20080109
//#include "msGPIO.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "GPIO.h"
#include "drvGPIO.h"
#include "msAPI_MIU.h"
#include "msAPI_Music.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"
#include "msAPI_OCP.h"

#include "IOUtil.h"
#include "msAPI_audio.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "msAPI_DataStreamIO.h"
#include "MApp_Audio.h"


#define MP3_DBG(x)     //x

//**********************************************************
#define MP3_DECODE_DONE             0xFF
#define MP3_BUFFER_TIMEOUT_MS       (1000LU)
#define MP3_DECODE_TIMEOUT_MS       (3000LU)

#define MP3_TAG_BUF_SIZE            128

#define XING_FRAMES                 0x00000001
#define XING_BYTES                  0x00000002
#define XING_TOC                    0x00000004
#define XING_SCALE                  0x00000008

#define GENRE_MAX_NUM  148

static const U8 u8GenreStrMap[GENRE_MAX_NUM][32] =
{
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
    "folk",       //The following genres are Winamp extensions
    "folk-Rock",
    "National Folk",
    "Swing",
    "Fast Fusion",
    "Bebob",
    "Latin",
    "Revival",
    "Celtic",
    "Bluegrass",
    "Avantgarde",
    "Gothic Rock",
    "Progressive Rock",
    "Psychedelic Rock",
    "Symphonic Rock",
    "Slow Rock",
    "Big Band",
    "Chorus",
    "Easy Listening",
    "Acoustic",
    "Humour",
    "Speech",
    "Chanson",
    "Opera",
    "Chamber Music",
    "Sonata",
    "Symphony",
    "Booty Bass",
    "Primus",
    "Porn Groove",
    "Satire",
    "Slow Jam",
    "Club",
    "Tango",
    "Samba",
    "Folklore",
    "Ballad",
    "Power Ballad",
    "Rhythmic Soul",
    "Freestyle",
    "Duet",
    "Punk Rock",
    "Drum Solo",
    "A capella",
    "Euro-House",
    "Dance Hall",
    "Goa",
    "Drum & Bass",
    "Club - House",
    "Hardcore",
    "Terror",
    "Indie",
    "BritPop",
    "Negerpunk",
    "Polsk Punk",
    "Beat",
    "Christian Gangsta Rap",
    "Heavy Metal",
    "Black Metal",
    "Crossover",
    "Contemporary Christian",
    "Christian Rock",
    "Merengue",
    "Salsa",
    "Thrash Metal",
    "Anime",
    "JPop",
    "Synthpop"
};

En_DVB_decSystemType enDecSys = MSAPI_AUD_DVB_NONE; // here we only care if it's JPEG or not JPEG

extern XDATA BYTE g_DspCodeType;

//fix MP3 wrong bitrate&total time issue while playing V2/V2.5 stream, share same table for V2&V2.5
U16 Mp3BitRateTable[5][16] =
{
    {0xffff, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, MP3_INVALID_RATE}, // V1, L1
    {0xffff, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, MP3_INVALID_RATE},    // V1, L2
    {0xffff, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, MP3_INVALID_RATE},     // V1, L3
    {0xffff, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, MP3_INVALID_RATE},    // V2/V2.5, L1
    {0xffff, 8,  16, 24, 32, 40, 48, 56,  64,  80,  96, 112, 128, 144, 160, MP3_INVALID_RATE},     // V2/V2.5, L2/L3
};

U16 Mp3SampleRateTable[3][4] =
{
    {11025, 12000, 8000, MP3_INVALID_RATE}, // v2.5
    {22050, 24000, 16000, MP3_INVALID_RATE}, // v2
    {44100, 48000, 32000, MP3_INVALID_RATE}, // v1
};

/*
U32 SamplePerFrame[3][3]=
{
    {576, 1152, 384}, // v2.5
    {576, 1152, 384}, // v2
    {1152, 1152, 384}, // v1
};
*/
//**********************************************************

/******************************************************************************/
/// API for init Audio decoder initialization and decoding system
/// @param u32Mp3StartAddr \b IN Specify decode system
/******************************************************************************/
void msAPI_Music_Init(En_DVB_decSystemType enDecSystem, U16 u16InitVolume)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    //printf("msAPI_Music_Init(enDecSystem=%u, u16InitVolume=%u)\n", enDecSystem, u16InitVolume);

//    msAPI_Scaler_SetInputSoundSource( &stSystemInfo );
//    MApp_InputSource_ChangeAudioSource( stSystemInfo.enInputSourceType,UI_INPUT_SOURCE_NONE );

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);


    MDrv_AUDIO_SetPlayFileFlag(DSP_DEC, 0);

    enDecSys = MSAPI_AUD_DVB_TONE ;
    if (enDecSys != MSAPI_AUD_DVB_TONE)
    {
        MDrv_AUDIO_Init();
        msAPI_Timer_Delayms(100);

        enDecSys = MSAPI_AUD_DVB_TONE;
        //Audio_Amplifier_ON();  // this is critical because we turn off the amplifier when loading JPEG code to DSP
        //MApp_Audio_Set_AmpOnOff(AUDIO_AMP_ON);
    }

    // Comment this code since need not to change to DTV input source
    // MApp_InputSource_ChangeAudioSource(INPUT_SOURCE_DTV,UI_INPUT_SOURCE_NONE);

    // Why set 2 times?? SetSystem Waste too musch time(1xxms)
//    MApi_AUDIO_SetSystem(MSAPI_AUD_DVB_NONE);

    // Set dec system
    MApi_AUDIO_SetSystem(enDecSystem); // Use 12xms

    // Setup volume
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, u16InitVolume, 0);


    //force unmute ... the mute might be triggerrd from SIF which we can hardly
    // determine which type it is...
    // Unmute will use 5xms
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void msAPI_Music_StartDecode(void)
{
    MP3_DBG(printf("msAPI_Music_StartDecode\n"));
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);//MDrv_MAD_SetDecCmd(0x04);
}

//******************************************************************************
/// Start audio decode.
/// @param  bNewAudioMode     \b IN Specify use new audio mode or not
/// @return NA
//******************************************************************************
void msAPI_Music_StartDecodeEnhance(BOOLEAN bNewAudioMode)
{
    MP3_DBG(printf("msAPI_Music_StartDecodeEnhance: %d\n", bNewAudioMode));

    if(bNewAudioMode)
    {
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYMM_FILE2);
    }
    else
    {
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);//MDrv_MAD_SetDecCmd(0x04);
    }
}

void msAPI_Music_StartBrowse(void)
{
    MP3_DBG(printf("msAPI_Music_StartBrowse\n"));
    // decode data but output no sound
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STARTBROWSE);//MDrv_MAD_SetDecCmd(0x05);
}

void msAPI_Music_StopDecode(void)
{
    MP3_DBG(printf("msAPI_Music_StopDecode\n"));
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);// MDrv_MAD_SetDecCmd(0x00);
}

void msAPI_Music_PauseDecode(void)
{
    MP3_DBG(printf("msAPI_Music_PauseDecode\n"));
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PAUSE);//MDrv_MAD_SetDecCmd(0x06);
}

U8 msAPI_Music_CheckPlayDone(void)
{
    if ((MDrv_AUDIO_ReadDecMailBox(7) == 0) && (msAPI_Music_GetResidualBufferSize() <= ES_ALIGNMENT))
    {
        msAPI_Music_StopDecode();
        MP3_DBG(printf("\nPlay done"));
        return TRUE;
    }
    return FALSE;
}

EN_MP3_LAYER msAPI_Music_GetLayer(void)
{
    // MDrv_MAD_MPEG_GetLayer() return the layer of music. 1 & 2 for layer mpeg 1 & 2. 3 is for mp3
    EN_MP3_LAYER enLayer = EN_MP3_LAYER_NOT_DETERMINE_YET;

    //switch (MDrv_MAD_MPEG_GetLayer())
    switch(MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_Layer))
    {
        case 1:
            enLayer = EN_MP3_LAYER_1;
            break;
        case 2:
            enLayer = EN_MP3_LAYER_2;
            break;
        case 3:
            enLayer = EN_MP3_LAYER_3;
            break;
    }

    return enLayer;
}

U16 msAPI_Music_GetResidualBufferSize(void)
{
    return (MS_U16)MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_esBuf_currLevel);
}

// This function is used to calculate "remained  ES data size in audio pcm buffer"
U16 msAPI_Music_GetPCMBufferSize(U16 u16BitRate)
{
    U32 u32Tmp;

    u32Tmp = (U32)MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_pcmBuf_currLevel); // Unit : Byte
// ES data size = BitRate/8 (Byte)  *  ( pcm sample count / Sampling rate)
//                   = (u16BitRate * 1000 / 8)  * [   pcmBuf_currLevel(Bytes) / 2 (bytes) / 2 (stereo)  / Fs  ]

    u32Tmp = ((U32)u16BitRate * 1000 /8) * (u32Tmp/2/2 )/((U32)MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_SampleRate));

    return (U16)u32Tmp;
}

// This function is used to calculate "remained  ES data size in audio pcm buffer"
U16 msAPI_Music_GetPCMBufferSize2(U16 u16BitRate,U32 u32SampleRate)
{
    U32 u32Tmp;

    u32Tmp = (U32)MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_pcmBuf_currLevel); // Unit : Byte
// ES data size = BitRate/8 (Byte)  *  ( pcm sample count / Sampling rate)
//                   = (u16BitRate * 1000 / 8)  * [   pcmBuf_currLevel(Bytes) / 2 (bytes) / 2 (stereo)  / Fs  ]

    u32Tmp = ((U32)u16BitRate * 1000 /8) * (u32Tmp/2/2 )/(u32SampleRate);

    return (U16)u32Tmp;
}

U32 msAPI_Music_GetCurrentFrameNumber(void)
{
    return MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_FrameNum);
}

U16 msAPI_Music_GetSampleRate(void)
{
    return MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_SampleRate);
}

U16 msAPI_Music_GetBitRate(void)
{
    return MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_BitRate);
}

U32 msAPI_Music_GetBitRateByIndex(U8 u8Version, U8 u8Layer, U8 u8BitRateIndex)
{
    U32 u32BitRate;

    if(u8BitRateIndex >= 16)
    {
        return 0;
    }

    if ((u8Version == 0x3) && (u8Layer == 0x3)) // V1 L1
    {
        u32BitRate = (U32) Mp3BitRateTable[0][u8BitRateIndex];
    }
    else if ((u8Version == 0x3) && (u8Layer == 0x2)) // V1 L2
    {
        u32BitRate = (U32) Mp3BitRateTable[1][u8BitRateIndex];
    }
    else if ((u8Version == 0x3) && (u8Layer == 0x1)) // V1 L3
    {
        u32BitRate = (U32) Mp3BitRateTable[2][u8BitRateIndex];
    }
    //fix MP3 wrong bitrate&total time issue while playing V2/V2.5 stream, share same table for V2&V2.5
    else if (((u8Version == 0x2)||(u8Version == 0x00)) && (u8Layer == 0x3)) // V2/V2.5 L1
    {
        u32BitRate = (U32) Mp3BitRateTable[3][u8BitRateIndex];
    }
    else if (((u8Version == 0x2)||(u8Version == 0x00)) && ((u8Layer == 0x2)||(u8Layer == 0x1))) // V2/V2.5 L2/L3
    {
        u32BitRate = (U32) Mp3BitRateTable[4][u8BitRateIndex];
    }
    else
    {
        return 0;
    }

    return u32BitRate;
}
/******************************************************************************/
/// API for start MP3 data transfer and decode
/// @param u32Mp3StartAddr \b IN Specify the buffer address
/// @param u32Mp3BlockSize \b IN Specify the block size
/******************************************************************************/
void msAPI_Music_SetInput(void)
{
    MApi_AUDIO_SetInput();
}

void msAPI_Music_SetSampleRateIndex(U16 u16Index)
{
     MApi_AUDIO_SetSampleRateIndex(u16Index);
}

void msAPI_Music_SetXPCMParam(XPCM_TYPE audioType, U8 channels, U16 sampleRate, U8 bitsPerSample, U16 blockSize, U16 samplePerBlock)
{
    //MDrv_MAD_XPCM_setParam(audioType, channels, sampleRate, bitsPerSample, blockSize, samplePerBlock);
    MApi_AUDIO_XPCM_Param(audioType, channels, sampleRate, bitsPerSample, blockSize, samplePerBlock);
}

void msAPI_Music_FileEndDataHandle(U32 u32DataLeft)
{
    MP3_DBG(printf("msAPI_Music_FileEndDataHandle, u32DataLeft=0x%x\n", u32DataLeft));
    MApi_AUDIO_FileEndDataHandle(u32DataLeft);
}
U32 msAPI_Music_AudioIsSupported(void)
{
    U32 bIsUnSupportAudio = 0;
    bIsUnSupportAudio = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_audio_unsupported);
    if(bIsUnSupportAudio != 0)
    {
        printf("Audio is not supported!!!Err:0x%x\n", bIsUnSupportAudio);
    }
    return bIsUnSupportAudio;
}

U8 msAPI_Music_CheckInputRequest(U32 *pU32WrtAddr, U32 *pU32WrtBytes)
{
    if (MDrv_AUDIO_GetPlayFileFlag(DSP_DEC))
    {
        U32 u32DEC1_BufAddr;
        U32 u32DspDec_BufAddr;

        MDrv_AUDIO_SetPlayFileFlag(DSP_DEC, 0);

        u32DEC1_BufAddr = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_BufferAddr);
        u32DspDec_BufAddr = msAPI_AUD_GetDspMadBaseAddr(DSP_DEC);
        *pU32WrtAddr = u32DEC1_BufAddr + u32DspDec_BufAddr;

        *pU32WrtBytes = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_BufferSize);
        //printf("*pU32WrtBytes=%X\n", *pU32WrtBytes);

    #if( AUDIO_CPU_IS_R2 )
        if( (*pU32WrtAddr < MAD_BASE_BUFFER_ADR)
          ||(*pU32WrtAddr > (MAD_BASE_BUFFER_ADR+MAD_BASE_BUFFER_LEN))
          )
        {
            printf("\nError: Audio access over range!\n");
            printf(" u32DEC1_BufAddr=%X\n", u32DEC1_BufAddr);
            printf(" u32DspDec_BufAddr=%X\n", u32DspDec_BufAddr);
            printf(" *pU32WrtAddr=%X\n", *pU32WrtAddr);
            return FALSE;
        }
    #endif

        return TRUE;
    }

    return FALSE;
}

BOOLEAN msAPI_Music_Parse_ID3v1(U32 u32FileBuffAddr, MP3_INFO *pMp3InfoPtr)
{
    U8 *pFileBufPtr;

    // u32FileBuffAddr must be 4K alignment
    pFileBufPtr = (U8 *)_PA2VA(u32FileBuffAddr);
    if ((pFileBufPtr[0] != 'T') || (pFileBufPtr[1] != 'A') || (pFileBufPtr[2] != 'G'))
    {
        return FALSE;
    }

    //Because we use the same data structure to storage id3 v1 and v2 strings, so we
    //follow the rule of v2 to store our v1's strings. The first character of strings means
    //the strings encoded method. Please refer to the below description.
    //$00 ??ISO-8859-1 (LATIN-1, Identical to ASCII for values smaller than 0x80).
    //$01 ??UCS-2 (UTF-16 encoded Unicode with BOM), in ID3v2.2 and ID3v2.3.
    //$02 ??UTF-16BE encoded Unicode without BOM, in ID3v2.4.
    //$03 ??UTF-8 encoded Unicode, in ID3v2.4.
    pMp3InfoPtr->title[0] = 0;  // indicate ASCII (ISO 8859-1)
    pMp3InfoPtr->title[31] = 0; //The v1 string length is 30
    pMp3InfoPtr->u8TitleLength = MP3_TAG_ID3v1_LENGTH;
    memcpy(pMp3InfoPtr->title+1, pFileBufPtr+3, 30);

    pMp3InfoPtr->artist[0] = 0;  // indicate ASCII (ISO 8859-1)
    pMp3InfoPtr->artist[31] = 0; //The v1 string length is 30
    pMp3InfoPtr->u8ArtistLength = MP3_TAG_ID3v1_LENGTH;
    memcpy(pMp3InfoPtr->artist+1, pFileBufPtr+33, 30);

    pMp3InfoPtr->album[0] = 0;  // indicate ASCII (ISO 8859-1)
    pMp3InfoPtr->album[31] = 0; //The v1 string length is 30
    pMp3InfoPtr->u8AlbumLength = MP3_TAG_ID3v1_LENGTH;
    memcpy(pMp3InfoPtr->album+1, pFileBufPtr+63, 30);

    pMp3InfoPtr->year[0] = 0;  // indicate ASCII (ISO 8859-1)
    pMp3InfoPtr->year[5] = 0; //The v1 string length is 30
    memcpy(pMp3InfoPtr->year+1, pFileBufPtr+93, 4);

    pMp3InfoPtr->comment[0] = 0;  // indicate ASCII (ISO 8859-1)
    pMp3InfoPtr->comment[31] = 0; //The v1 string length is 28 or 30
    memcpy(pMp3InfoPtr->comment+1, pFileBufPtr+97, 30);

    pMp3InfoPtr->genre = pFileBufPtr[127];

    if(pMp3InfoPtr->genre < GENRE_MAX_NUM)
    {
        pMp3InfoPtr->GenreStr[0] = 0;  // indicate ASCII (ISO 8859-1)
        pMp3InfoPtr->GenreStr[31] = 0; //The v1 string length is 30
        pMp3InfoPtr->u8GenreLength = strlen((char*)u8GenreStrMap[pMp3InfoPtr->genre]) + 1;
        msStrncpy((char *)pMp3InfoPtr->GenreStr+1, (const char *)u8GenreStrMap[pMp3InfoPtr->genre], strlen((char*)u8GenreStrMap[pMp3InfoPtr->genre]));
    }
    else
    {
        pMp3InfoPtr->u8GenreLength = 0;
    }

    MP3_DBG(printf("\nID3v1"));
    MP3_DBG(printf("\nTitle: %s", pMp3InfoPtr->title+1));
    MP3_DBG(printf("\nArtist: %s", pMp3InfoPtr->artist+1));
    MP3_DBG(printf("\nAlbum: %s", pMp3InfoPtr->album+1));
    MP3_DBG(printf("\nyear: %s", pMp3InfoPtr->year+1));
    MP3_DBG(printf("\nComment: %s", pMp3InfoPtr->comment+1));
    MP3_DBG(printf("\nGenre: %s\n\n", pMp3InfoPtr->GenreStr+1));

    return TRUE;
}

U32 msAPI_Music_Parse_ID3v2(U32 u32FileHandle, U32 u32FileBuffAddr, U32 u32FileBuffLen, MP3_INFO *pMp3InfoPtr, BOOLEAN bGetMp3OffsetOnly)
{
    U32 currentIdx, u32baseIdx;
    U32 u32FrameId, u32FrameSize, u32TagSize;
    U8 *pDstPtr=NULL, *pFileBufPtr, u8ID3Ver, u8CopyLen,u8OffsetTemp;

    // u32FileBuffAddr must be 4K alignment
    pFileBufPtr = (U8 *)_PA2VA(u32FileBuffAddr);
    if ((pFileBufPtr[0] != 'I') || (pFileBufPtr[1] != 'D') || (pFileBufPtr[2] != '3'))
    {
        MP3_DBG(printf("\nNo ID3 tag"));
        return 0;
    }

    u8ID3Ver = pFileBufPtr[3];

    u32TagSize = (U32) (pFileBufPtr[6] & 0x7F);
    u32TagSize <<= 7;
    u32TagSize |= (U32) (pFileBufPtr[7] & 0x7F);
    u32TagSize <<= 7;
    u32TagSize |= (U32) (pFileBufPtr[8] & 0x7F);
    u32TagSize <<= 7;
    u32TagSize |= (U32) (pFileBufPtr[9] & 0x7F);

    if (bGetMp3OffsetOnly == TRUE)
    {
        return (u32TagSize + 10);
    }

    if(u8ID3Ver == 0x02)
    {
        u8OffsetTemp=0x6;
    }
    else //u8ID3Ver == 0x03 , u8ID3Ver == 0x04
    {
        u8OffsetTemp=0xA;
    }

    pMp3InfoPtr->u8GenreLength = 0;

    u32baseIdx = 0;
    currentIdx = 0x0A;
//    while (currentIdx != (u32TagSize + 10))
    while (currentIdx <= (u32TagSize + 10)) //avoid endless loop
    {
        if(currentIdx > u32FileBuffLen - u8OffsetTemp)
        {
            u32baseIdx += currentIdx;
            msAPI_DataStreamIO_Seek(u32FileHandle, u32baseIdx, E_DATA_STREAM_SEEK_SET);
            msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, u32FileBuffLen);
            currentIdx = 0;
        }

        u8CopyLen = 0;
        if(u8ID3Ver == 0x02)
        {
            memcpy(&u32FrameId,pFileBufPtr + currentIdx,4);
            u32FrameId = (Swap32(u32FrameId) >>8) & 0x00FFFFFF;
            memcpy(&u32FrameSize,pFileBufPtr + currentIdx + 3,4);
            u32FrameSize = (Swap32(u32FrameSize)>>8) & 0x00FFFFFF;
            if (u32FrameId == 0x00000000)
            {
                break;
            }

            if(currentIdx + u32FrameSize + u8OffsetTemp > u32FileBuffLen)
            {
                if(currentIdx != 0)
                {
                    u32baseIdx += currentIdx;
                    msAPI_DataStreamIO_Seek(u32FileHandle, u32baseIdx, E_DATA_STREAM_SEEK_SET);
                    msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, u32FileBuffLen);
                    currentIdx = 0;
                }
            }

            switch (u32FrameId)
            {
                case MP3_TAG_ID3v2_2_TAL:
                    pDstPtr = (U8*)pMp3InfoPtr->album;
                    pMp3InfoPtr->u8AlbumLength = u32FrameSize;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->album)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->album)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->album));
                    break;
                case MP3_TAG_ID3v2_2_TCM:
                    pDstPtr = (U8*)pMp3InfoPtr->artist;
                    pMp3InfoPtr->u8ArtistLength = u32FrameSize;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->artist)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->artist)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->artist));
                    break;
                case MP3_TAG_ID3v2_2_TT2:
                    pDstPtr = (U8*)pMp3InfoPtr->title;
                    pMp3InfoPtr->u8TitleLength = u32FrameSize;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->title)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->title)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->title));
                    break;
                case MP3_TAG_ID3v2_2_TYE:
                    pDstPtr = (U8*)pMp3InfoPtr->year;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->year)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->year)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->year));
                    break;
                case MP3_TAG_ID3v2_2_PIC:
                    {
                        U8 strJpg[]="JPG";
                        u8CopyLen=0;
                        if((strcasecmp((const char *)(pFileBufPtr + currentIdx + u8OffsetTemp+1), (const char *)strJpg))==0)
                        {
                            U16 offset;
                            offset=currentIdx+u8OffsetTemp+1+3;
                            MP3_DBG(printf("found jpeg tag\n"));

                            //Picture type
                            offset++;

                            //Description
                            while(*((U8*)pFileBufPtr+offset)!=0)
                            {
                                offset++;
                            }
                            //Description '\0'
                            offset++;

                            //picture data
                            MP3_DBG(printf("offset=%d\n",offset));

                            pMp3InfoPtr->jpgOffset=u32baseIdx+offset;
                            pMp3InfoPtr->jpgSize=u32FrameSize-(offset-currentIdx-u8OffsetTemp);
                            MP3_DBG(printf("size=%d\n",pMp3InfoPtr->jpgSize));
                        }
                    }
                    break;
                case MP3_TAG_ID3v2_2_TCO:
                    pDstPtr = (U8*)pMp3InfoPtr->GenreStr;
                    pMp3InfoPtr->u8GenreLength = u32FrameSize;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->GenreStr)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->GenreStr)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->GenreStr));
                    break;
            }
        }
        else if(u8ID3Ver == 0x03 || u8ID3Ver == 0x04)
        {
            U8 bytes[4];
            U8 *tagSize;

            memcpy(&u32FrameId,pFileBufPtr + currentIdx,4);
            u32FrameId = Swap32(u32FrameId);
            tagSize = (U8*)&(pFileBufPtr[currentIdx + 4]);
            // The ID3v2 tag size is encoded with four bytes
            // where the most significant bit (bit 7)
            // is set to zero in every byte,
            // making a total of 28 bits.
            // The zeroed bits are ignored
            if(u8ID3Ver == 0x04)
            {
                bytes[3] =   tagSize[3]             | ((tagSize[2] & 1) << 7) ;
                bytes[2] = ((tagSize[2] >> 1) & 63) | ((tagSize[1] & 3) << 6) ;
                bytes[1] = ((tagSize[1] >> 2) & 31) | ((tagSize[0] & 7) << 5) ;
                bytes[0] = ((tagSize[0] >> 3) & 15) ;
            }
            else
            {
                bytes[3] = tagSize[3];
                bytes[2] = tagSize[2];
                bytes[1] = tagSize[1];
                bytes[0] = tagSize[0];
            }

            u32FrameSize  = ((U32)bytes[3]          |
                            ((U32)bytes[2] << 8)    |
                            ((U32)bytes[1] << 16)   |
                            ((U32)bytes[0] << 24));

            if (u32FrameId == 0x00000000)
            {
                break;
            }

            if(currentIdx + u32FrameSize + u8OffsetTemp > u32FileBuffLen)
            {
                if(currentIdx != 0)
                {
                    u32baseIdx += currentIdx;
                    msAPI_DataStreamIO_Seek(u32FileHandle, u32baseIdx, E_DATA_STREAM_SEEK_SET);
                    msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, u32FileBuffLen);
                    currentIdx = 0;
                }
            }

            switch (u32FrameId)
            {
                case MP3_TAG_ID3v2_3_TALB:
                    pDstPtr = (U8*)pMp3InfoPtr->album;
                    pMp3InfoPtr->u8AlbumLength = u32FrameSize;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->album)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->album)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->album));
                    break;
                case MP3_TAG_ID3v2_3_TPE1:
                    pDstPtr = (U8*)pMp3InfoPtr->artist;
                    pMp3InfoPtr->u8ArtistLength = u32FrameSize;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->artist)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->artist)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->artist));
                    break;
                case MP3_TAG_ID3v2_3_TIT2:
                    pDstPtr = (U8*)pMp3InfoPtr->title;
                    pMp3InfoPtr->u8TitleLength = u32FrameSize;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->title)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->title)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->title));
                    break;
                case MP3_TAG_ID3v2_3_TYER:
                    pDstPtr = (U8*)pMp3InfoPtr->year;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->year)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->year)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->year));
                    break;

                case MP3_TAG_ID3v2_3_TCON:
                    {
                        pDstPtr = (U8*)pMp3InfoPtr->GenreStr;
                        pMp3InfoPtr->u8GenreLength = u32FrameSize;
                        if (u32FrameSize > (sizeof(pMp3InfoPtr->GenreStr)-1))
                        {
                            u8CopyLen = sizeof(pMp3InfoPtr->GenreStr)-1;
                        }
                        else
                        {
                            u8CopyLen = u32FrameSize;
                        }
                        memset(pDstPtr, 0, sizeof(pMp3InfoPtr->GenreStr));
                    }
                    break;

                case MP3_TAG_ID3v2_4_TDRC:
                    pDstPtr = (U8*)pMp3InfoPtr->year;
                    if (u32FrameSize > (sizeof(pMp3InfoPtr->year)-1))
                    {
                        u8CopyLen = sizeof(pMp3InfoPtr->year)-1;
                    }
                    else
                    {
                        u8CopyLen = u32FrameSize;
                    }
                    memset(pDstPtr, 0, sizeof(pMp3InfoPtr->year));
                    break;
                case MP3_TAG_ID3v2_3_APIC:
                {
                    U8 strJpg[]="image/jpeg";
                    U8 strJpg2[]="image/jpg";
                    u8CopyLen=0;
                    if((strcasecmp((const char *)(pFileBufPtr + currentIdx + u8OffsetTemp+1), (const char *)strJpg))==0)
                    {
                        U16 offset;
                        offset=currentIdx+u8OffsetTemp+1;
                        MP3_DBG(printf("found jpeg tag\n"));

                        //MINE type
                        while(*((U8*)pFileBufPtr+offset)!=0)
                        {
                            offset++;
                        }
                        //MINE type '\0'
                        offset++;

                        //Picture type
                        offset++;

                        //Description
                        while(*((U8*)pFileBufPtr+offset)!=0)
                        {
                            offset++;
                        }
                        //Description '\0'
                        offset++;

                        //picture data
                        MP3_DBG(printf("offset=%d\n",offset));

                        pMp3InfoPtr->jpgOffset=u32baseIdx+offset;
                        pMp3InfoPtr->jpgSize=u32FrameSize-(offset-currentIdx-u8OffsetTemp);
                        MP3_DBG(printf("size=%d\n",pMp3InfoPtr->jpgSize));
                    }
                    else if((strcasecmp((const char *)(pFileBufPtr + currentIdx + u8OffsetTemp+1), (const char *)strJpg2))==0)
                    {
                        U16 offset;
                        offset=currentIdx+u8OffsetTemp+1;
                        MP3_DBG(printf("found jpg tag\n"));

                        //MINE type
                        while(*((U8*)pFileBufPtr+offset)!=0)
                        {
                            offset++;
                        }
                        //MINE type '\0'
                        offset++;

                        //Picture type
                        offset++;

                        //Description
                        while(*((U8*)pFileBufPtr+offset)!=0)
                        {
                            offset++;
                        }
                        //Description '\0'
                        offset++;

                        //picture data
                        MP3_DBG(printf("offset=%d\n",offset));

                        pMp3InfoPtr->jpgOffset=u32baseIdx+offset;
                        pMp3InfoPtr->jpgSize=u32FrameSize-(offset-currentIdx-u8OffsetTemp);
                        MP3_DBG(printf("size=%d\n",pMp3InfoPtr->jpgSize));
                    }
                }
                    break;
            }
        }
        else
        {
            //Not support!
            break;
        }

        if(u8CopyLen != 0)
        {
            memcpy(pDstPtr, pFileBufPtr + currentIdx + u8OffsetTemp, u8CopyLen);
        }

        currentIdx += (u32FrameSize + u8OffsetTemp);
    }

    MP3_DBG(printf("\nTitle: %s", pMp3InfoPtr->title+1));
    MP3_DBG(printf("\nArtist: %s", pMp3InfoPtr->artist+1));
    MP3_DBG(printf("\nAlbum: %s", pMp3InfoPtr->album+1));
    MP3_DBG(printf("\nyear: %s", pMp3InfoPtr->year+1));
    MP3_DBG(printf("\nComment: %s", pMp3InfoPtr->comment+1));

    return (u32TagSize + 10);
}

U32 msAPI_Music_GetPlayTick(void)
{
    return MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_1ms_PTS);
}

U16 msAPI_Music_GetEsMEMCnt(void)
{
    return MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_PCMBufferSize);
}

void msAPI_Music_CleanFileEndData(U32 StrAddr, U32 length, U32 ClearValue)
{
    MP3_DBG(printf("msAPI_Music_CleanFileEndData, addr=0x%x, len=0x%x\n", StrAddr, length));
    //MApi_GFX_ClearFrameBufferByWord() didn't work in T4 m4a case??
    //anyway, use memset to clear
    //MApi_GFX_ClearFrameBufferByWord(StrAddr, length, ClearValue);
    memset((void*)_PA2VA(StrAddr), ClearValue, length);
    MApi_GFX_FlushQueue();
}

U32 msAPI_Music_GetMP3CBRFrameSize(U8 u8Version,U8 u8Layer,U8 u8PaddingFlag,U8 u8SampleRateIndex,U8 u8BitRateIndex)
{
    U32 u32FrameSize = 0;
    U32 u32SampleRate = 0;
    U32 u32BitRate;

    if (u8Version == EN_MP3_VERSION_2_5) // v2.5
    {
        u32SampleRate = Mp3SampleRateTable[0][u8SampleRateIndex];
    }
    else if (u8Version == EN_MP3_VERSION_2) // v2
    {
        u32SampleRate = Mp3SampleRateTable[1][u8SampleRateIndex];
    }
    else if (u8Version == EN_MP3_VERSION_1) // v1
    {
        u32SampleRate = Mp3SampleRateTable[2][u8SampleRateIndex];
    }
    else
    {
        return 0;
    }

    if ((u8Version == 0x3) && (u8Layer == 0x3)) // V1 L1
    {
        u32BitRate = (U32) Mp3BitRateTable[0][u8BitRateIndex];
    }
    else if ((u8Version == 0x3) && (u8Layer == 0x2)) // V1 L2
    {
        u32BitRate = (U32) Mp3BitRateTable[1][u8BitRateIndex];
    }
    else if ((u8Version == 0x3) && (u8Layer == 0x1)) // V1 L3
    {
        u32BitRate = (U32) Mp3BitRateTable[2][u8BitRateIndex];
    }
    //fix MP3 wrong bitrate&total time issue while playing V2/V2.5 stream, share same table for V2&V2.5
    else if (((u8Version == 0x2)||(u8Version == 0x00)) && (u8Layer == 0x3)) // V2/V2.5 L1
    {
        u32BitRate = (U32) Mp3BitRateTable[3][u8BitRateIndex];
    }
    else if (((u8Version == 0x2)||(u8Version == 0x00)) && ((u8Layer == 0x2)||(u8Layer == 0x1))) // V2/V2.5 L2/L3
    {
        u32BitRate = (U32) Mp3BitRateTable[4][u8BitRateIndex];
    }
    else
    {
        return 0;
    }

    if ((u32SampleRate == 0xffff) || (u32BitRate == 0xffff))
    {
        return 0;
    }
    else
    {
        // Samples Per Frame: ref:http://www.codeproject.com/KB/audio-video/mpegaudioinfo.aspx
        // Frame Size = ( (Samples Per Frame / 8 * Bitrate) / Sampling Rate) + Padding Size
        //             | MPEG 1 | MPEG 2 (LSF) | MPEG 2.5 (LSF)
        // Layer I     |   384  |     384      |     384
        // Layer II    |  1152  |    1152      |    1152
        // Layer III   |  1152  |     576      |     576
        if (u8Layer == EN_MP3_LAYER_1)
        {
            u32FrameSize = (((48 * u32BitRate) * 1000) / u32SampleRate);
            u32FrameSize = ((u32FrameSize>>2)<<2);
            //In Layer I, a slot is always 4 byte long, in all other the layers a slot is 1 byte long.
            if(u8PaddingFlag)
            {
                u32FrameSize += 4;
            }
        }
        else if ((u8Layer == EN_MP3_LAYER_2) || ((u8Version == EN_MP3_VERSION_1) && (u8Layer == EN_MP3_LAYER_3)))
        {
            u32FrameSize = ((144 * u32BitRate * 1000) / u32SampleRate) + u8PaddingFlag;
        }
        else
        {
            u32FrameSize = ((72 * u32BitRate * 1000) / u32SampleRate) + u8PaddingFlag;
        }
    }

    return u32FrameSize;
}

U32 msAPI_Music_GetFileTime(
        U32 u32FileBuffAddr,
        U32 u32FileSize,
        EN_MP3_VERSION *penVersion,
        EN_MP3_LAYER *penLayer,
        U16 *pu16BitRate,
        U32 *pu32SampleRate,
        U8 *pbFlag,
        U16 *pu16TOCLength,
        U8 *pu8TOC)
{
    U8 *pFileBufPtr;
    U32 u32Tag, u32FrameCnt=0;
    U32 u32SampleRate;
    U8 u8Version, u8Layer, u8Offset;
    U16 u16Mp3HeaderOffset;
    U8  u8PaddingFlag;
    U32 u32Mp3FileTime;
    U32 u32MemPos = u32FileBuffAddr-((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR));
    U8 u8HeaderSecondByte;

    *pbFlag = 0;
    *pu16TOCLength = 0 ;

    pFileBufPtr = (U8*)_PA2VA(u32FileBuffAddr);
    // Seek the file to find the MP3 header, max seek 4096 bytes
    u16Mp3HeaderOffset = 0;
//Mp3_Get_FirstFrame: // update to fix "cannot play ILOVEU.mp3"
    while((!(pFileBufPtr[u16Mp3HeaderOffset] == 0xff &&
            (pFileBufPtr[u16Mp3HeaderOffset+1] & 0xe0) == 0xe0))
        &&((u16Mp3HeaderOffset+u32MemPos)<0xFFE))
    {
        u16Mp3HeaderOffset++;
    }
    if (!(pFileBufPtr[u16Mp3HeaderOffset] == 0xff && (pFileBufPtr[u16Mp3HeaderOffset+1] & 0xe0) == 0xe0))
    {
        return 0;   // not MP3 file
    }

    u8Version = (pFileBufPtr[u16Mp3HeaderOffset+1] >> 0x3) & 0x3;
    u8Layer = (pFileBufPtr[u16Mp3HeaderOffset+1] >> 0x1) & 0x3;
    *penVersion= (EN_MP3_VERSION)u8Version;
    *penLayer = (EN_MP3_LAYER)u8Layer;
    u8HeaderSecondByte = pFileBufPtr[u16Mp3HeaderOffset+1];

    u8PaddingFlag = (pFileBufPtr[u16Mp3HeaderOffset+2] & 0x02) >> 1;
    u32SampleRate = (pFileBufPtr[u16Mp3HeaderOffset+2] & 0x0c) >> 2;
    if (u8Version == EN_MP3_VERSION_2_5) // v2.5
    {
        u32SampleRate = Mp3SampleRateTable[0][u32SampleRate];
    }
    else if (u8Version == EN_MP3_VERSION_2) // v2
    {
        u32SampleRate = Mp3SampleRateTable[1][u32SampleRate];
    }
    else if (u8Version == EN_MP3_VERSION_1) // v1
    {
        u32SampleRate = Mp3SampleRateTable[2][u32SampleRate];
    }
    else
    {
        u32SampleRate = 0xffff;
    }
    *pu32SampleRate = u32SampleRate;

    u8Offset = 36;  // mpeg1, channel != mono
    memcpy(&u32Tag,(pFileBufPtr + u16Mp3HeaderOffset + u8Offset),4);
    u32Tag=Swap32(u32Tag);
    if (u32Tag == MP3_TAG_XING)
    {
        *pbFlag |= MP3_FLAG_VBR_XING;
    }
    else if(u32Tag == MP3_TAG_VBRI)
    {
        *pbFlag |= MP3_FLAG_VBR_VBRI;
    }
    else
    {
        u8Offset = 21;  // mpeg1, channel == mono or mpeg2, channel != mono
        memcpy(&u32Tag,(pFileBufPtr + u16Mp3HeaderOffset + u8Offset),4);
        u32Tag=Swap32(u32Tag);
        if (u32Tag == MP3_TAG_XING)
        {
            *pbFlag |= MP3_FLAG_VBR_XING;
        }
        else
        {
            u8Offset = 13;  // mpeg1, channel == monoo
            //u32Tag = *(U32 *)(pFileBufPtr + u16Mp3HeaderOffset + u8Offset);
            memcpy(&u32Tag,(pFileBufPtr + u16Mp3HeaderOffset + u8Offset),4);
            u32Tag=Swap32(u32Tag);
            if (u32Tag == MP3_TAG_XING)
            {
                *pbFlag |= MP3_FLAG_VBR_XING;
            }
        }
    }

    if(*pbFlag & MP3_FLAG_VBR_XING)               // VBR_Xing
    {
        if(pFileBufPtr[u16Mp3HeaderOffset + u8Offset + 7] & XING_FRAMES)
        {
            memcpy(&u32FrameCnt,(pFileBufPtr + u16Mp3HeaderOffset + u8Offset + 8),4);
            u32FrameCnt=Swap32(u32FrameCnt);  //SPEC: Big-endian
        }

        // Samples Per Frame: ref:http://www.codeproject.com/KB/audio-video/mpegaudioinfo.aspx
        // Frame Size = ( (Samples Per Frame / 8 * Bitrate) / Sampling Rate) + Padding Size
        //             | MPEG 1 | MPEG 2 (LSF) | MPEG 2.5 (LSF)
        // Layer I     |   384  |     384      |     384
        // Layer II    |  1152  |    1152      |    1152
        // Layer III   |  1152  |     576      |     576

        if(u8Layer!=EN_MP3_LAYER_RESERVED && u8Version!=EN_MP3_VERSION_RESERVED)
        {
            if(u8Layer==EN_MP3_LAYER_1)
            {
                u32FrameCnt*=384;
            }
            else if((u8Layer==EN_MP3_LAYER_2) || ((u8Layer==EN_MP3_LAYER_3) && (u8Version==EN_MP3_VERSION_1)))
            {
                u32FrameCnt*=1152;
            }
            else
            {
                u32FrameCnt*=576;
            }
        }
        else
        {
            printf("Layer or version is reserved, no sample per frame; music duration may be wrong\n");
        }



        u32Mp3FileTime = u32FrameCnt / u32SampleRate;

        if(u32FrameCnt!=0)
        {
            *pu16BitRate = (U16)(u32FileSize*8 / (u32FrameCnt/(u32SampleRate/1000)));
        }
        else
        {
            *pu16BitRate = (U16)MP3_INVALID_RATE;
        }

        if ((pFileBufPtr[u16Mp3HeaderOffset + u8Offset + 7] & XING_TOC) && (pu8TOC != NULL))
        {
            *pu16TOCLength=100;
            memcpy(pu8TOC, pFileBufPtr + u16Mp3HeaderOffset + u8Offset + 16, 100);
        }

    }
    else if(*pbFlag & MP3_FLAG_VBR_VBRI)   //VBR_VBRI
    {
        memcpy(&u32FrameCnt,(pFileBufPtr + u16Mp3HeaderOffset + u8Offset + 14),4);
        u32FrameCnt=Swap32(u32FrameCnt);  //SPEC: Big-endian

        // Samples Per Frame: ref:http://www.codeproject.com/KB/audio-video/mpegaudioinfo.aspx
        // Frame Size = ( (Samples Per Frame / 8 * Bitrate) / Sampling Rate) + Padding Size
        //             | MPEG 1 | MPEG 2 (LSF) | MPEG 2.5 (LSF)
        // Layer I     |   384  |     384      |     384
        // Layer II    |  1152  |    1152      |    1152
        // Layer III   |  1152  |     576      |     576

        if(u8Layer!=EN_MP3_LAYER_RESERVED && u8Version!=EN_MP3_VERSION_RESERVED)
        {
            if(u8Layer==EN_MP3_LAYER_1)
            {
                u32FrameCnt*=384;
            }
            else if((u8Layer==EN_MP3_LAYER_2) || ((u8Layer==EN_MP3_LAYER_3) && (u8Version==EN_MP3_VERSION_1)))
            {
                u32FrameCnt*=1152;
            }
            else
            {
                u32FrameCnt*=576;
            }
        }
        else
        {
            printf("Layer or version is reserved, no sample per frame; music duration may be wrong\n");
        }

        u32Mp3FileTime = u32FrameCnt / u32SampleRate;

        if(u32FrameCnt!=0)
        {
            *pu16BitRate = (U16)(u32FileSize*8 / (u32FrameCnt/(u32SampleRate/1000)));
        }
        else
        {
            *pu16BitRate = (U16)MP3_INVALID_RATE;
        }

        memcpy(pu16TOCLength,(pFileBufPtr + u16Mp3HeaderOffset + u8Offset + 18), 2);
        if(*pu16TOCLength>0 && *pu16TOCLength<100)
        {
           memcpy(pu8TOC, pFileBufPtr + u16Mp3HeaderOffset + u8Offset + 26, *pu16TOCLength);
        }
    }
    else  //CBR
    {
        u32Mp3FileTime = 0;
    }

    return u32Mp3FileTime;
}

//******************************************************************************
/**
 * @brief   Conver ID3v1/ID3v2 String to Unicode
 * @remarks
 * @param   pu8SrcString - Source string
 * @param   pu16DstString - Target buffer for store convert data
 * @param   u32StrLen - Source string length
 * @return  TRUE/FALSE
 */
//******************************************************************************
BOOL msAPI_Music_ConvertId3String2Unicode(U8 *pu8SrcString, U16 *pu16DstString, U16 u32StrLen)
{
    BOOL bRet = FALSE;

    if (pu8SrcString != NULL && pu16DstString != NULL && (u32StrLen > 0))
    {

        switch(pu8SrcString[0])
        {
            case 0://encoding = "ISO-8859-1";//pu8SrcString[0]=0x00
            default:
                if(u32StrLen<=1)
                {
                   bRet = FALSE;
                }
                else
                {
                    memcpy((U8 *)pu16DstString,&pu8SrcString[1],u32StrLen-1);
                    ASCIItoUnicode2((S8 *)pu16DstString,u32StrLen-1);
                    bRet = TRUE;
                }
                break;

            case 1://encoding = "UTF-16";//pu8SrcString[0]=0x01 , pu8SrcString[1]=0xFF , pu8SrcString[2]=0xFE
                if(u32StrLen<=3)
                {
                   bRet = FALSE;
                }
                else
                {
                    memcpy((U8 *)pu16DstString,&pu8SrcString[3],u32StrLen-3);
                    bRet = TRUE;
                }
                break;

            case 2://encoding = "UTF-16BE";//pu8SrcString[0]=0x02 , without BOM (0xFE, 0xFF)
                if(u32StrLen<=1)
                {
                   bRet = FALSE;
                }
                else
                {
                    U16 i;
                    //Endian swap
                    #define ByteSwap16(x) (((x) & 0x00ff) << 8 | ((x) & 0xff00) >> 8)

                    memcpy((U8 *)pu16DstString,&pu8SrcString[1],u32StrLen-1);
                    for(i=0 ; i<((u32StrLen-1) >> 1) ; i++)
                    {
                        pu16DstString[i] = ByteSwap16(pu16DstString[i]);
                    }
                    bRet = TRUE;
                }
                break;

            case 3://encoding = "UTF-8"; //pu8SrcString[0]=0x03 , without BOM (0xEF, 0xBB, 0xBF)
                if(u32StrLen<=1)
                {
                   bRet = FALSE;
                }
                else
                {
                    msAPI_OCP_MappinUTF8ToUCS2((U8*)&pu8SrcString[1], pu16DstString, (U16)(u32StrLen-1), (U16)(u32StrLen-1));
                    bRet = TRUE;
                }
                break;
        }

        #if 0//debug
        {
            U32 i;
            printf("********************************************************************\n");
            for(i=0;i<u32StrLen;i++)
            {
                printf("src=%x-->dst=%x\n",pu8SrcString[i],pu16DstString[i]);
            }
            printf("********************************************************************\n");
        }
        #endif
    }

    return bRet;
}

//******************************************************************************
/**
 * @brief   Search if there is special Unicode string in Genre string, if we find it, parse it and get the index number, then return predefined string by the index number
 * @remarks
 * @param   pu16SrcStr - Source string
 * @param   u32DstBuflen - Source string length
 * @return  Output replaced string, if it is NULL, it means not found, change.
 */
//******************************************************************************
U8 *msAPI_Music_MappingGenreStr(U16* pu16SrcStr, U32 u32DstBuflen)
{
    U32 i = 0;
    U32 u32GenreIndex = 0xFFFFFFFF;

    if(pu16SrcStr == NULL)
    {
        return NULL;
    }

    while(i < u32DstBuflen)
    {
        switch(pu16SrcStr[i])
        {
        //'('
        case 0x0028:
            {
                U8 k = 1;
                u32GenreIndex = 0;
                //between '0' and '9' and number <= 3
                while((pu16SrcStr[i+k] >= 0x0030) && (pu16SrcStr[i+k] <= 0x0039) && (k <= 3))
                {
                    //convert number to interger
                    u32GenreIndex = u32GenreIndex * 10 + (U32)(pu16SrcStr[i+k] - 0x0030);
                    k++;
                }

                i += (k-1);
            }
            break;
        //')'
        case 0x0029:
            if((u32GenreIndex != 0xFFFFFFFF) && (u32GenreIndex < GENRE_MAX_NUM))
            {
                //exit this while loop
                MP3_DBG(printf("\nu32GenreIndex=%ld\n",u32GenreIndex));
                return ( (U8 *)u8GenreStrMap[u32GenreIndex] );
            }
        default:
            break;
        }

        i++;
    }

    return NULL;
}

//******************************************************************************
/**
 * @brief   Search if there is special id3 v1/v2 string pattern in Genre string, if we find it, parse it and get the index number, then return predefined string by the index number
 * @remarks
 * @param   pu8SrcString - Source string
 * @param   pu8SrcStrLen - Source string length
 * @return  TRUE: Source string was replaced.(pu8SrcString and pu8SrcStrLen were modified.) FALSE: No string replace occurred.
 */
//******************************************************************************
BOOLEAN msAPI_Music_ReMapGenreStr(U8 *pu8SrcString, U8 *pu8SrcStrLen)
{
    U16 u16GenreStr[MP3_INFO_LENGTH+1]={0};
    U8 *pu8OutString = NULL;

    if (pu8SrcString != NULL)
    {
        //prevent mp3 genre over UI buffer size
        if(*pu8SrcStrLen > (MP3_INFO_LENGTH-1))
        {
            *pu8SrcStrLen = (MP3_INFO_LENGTH-1);
        }

        //printf("genre, u32SrcStrLen=%lu\n", u32SrcStrLen);

        if(msAPI_Music_ConvertId3String2Unicode(pu8SrcString, u16GenreStr, *pu8SrcStrLen))
        {
            pu8OutString = msAPI_Music_MappingGenreStr(u16GenreStr, *pu8SrcStrLen);
            if  ( pu8OutString != NULL )
            {
                //Replace original string
                pu8SrcString[0] = 0x00; // 0x00 <-- ISO-8859-1
                *pu8SrcStrLen = strlen((char *)pu8OutString);
                msStrncpy((char *)&(pu8SrcString[1]), (char *)pu8OutString, *pu8SrcStrLen);
                *pu8SrcStrLen += 2; //+1 for 0x00 <-- ISO-8859-1
                                                //+1 for null character ending, total +2
                return TRUE;
            }
            else
                return FALSE;
        }
    }

    return FALSE;
}

//******************************************************************************
/**
 * @brief   Set audio parameter by codec
 * @remarks
 * @param   Specify decode system
 */
//******************************************************************************
void msAPI_Music_SetAudioParam(En_DVB_decSystemType enDecSystem)
{
    if(enDecSystem == MSAPI_AUD_DVB_MP3 || enDecSystem == MSAPI_AUD_DVB_MPEG)
    {
    }
    else if(enDecSystem == MSAPI_AUD_DVB_AAC)
    {
    }
    else if(enDecSystem == MSAPI_AUD_DVB_FLAC)
    {
    }
    else if(enDecSystem == MSAPI_AUD_DVB_AC3 || enDecSystem == MSAPI_AUD_DVB_AC3P)
    {
    }
    else if(enDecSystem == MSAPI_AUD_DVB_WMA || enDecSystem == MSAPI_AUD_DVB_DTS || enDecSystem == MSAPI_AUD_DVB_XPCM)
    {
    }
    else if(enDecSystem == MSAPI_AUD_DVB_VORBIS)
    {
        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_ADEC1_reqDataSize,FILE_SIZE_16KB,0);
    }
    else if( (enDecSystem == MSAPI_AUD_DVB_AMR_NB) || (enDecSystem == MSAPI_AUD_DVB_AMR_WB) )
    {
    }
}


#undef MSAPI_MUSIC_C
