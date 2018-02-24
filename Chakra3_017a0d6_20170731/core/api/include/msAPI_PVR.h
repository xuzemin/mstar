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
/*
++++++++++++++++++++++++++++++++++???????????????++++++++++++++++++++++++++++++++++++++++++??????????????????????++++++++++++++++++++++++++++++++++++++++=++????
++++++++++++++++++++++++++++++++++IIIIIIIIIIIIII????????????????????????????????????????????IIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++++++++++++++++++++++++++++++IIIIIIIIIIII????????????????????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=+IIIIIIIIIII+++++++++++++++?$$$$$$$$$77II??????????I???????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++++DMMMMMMMMMMMZI++++++++++++=NMMMMMMMMMMMZ$?I77$$$$$$I?????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMD7=+++++++++IMMMMMMMMMMMMM8OZZ$7I???????????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMM8++++++++++DMMMMMMMMMMMMMD8$I?????????????????III???????????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++=+?=8MMMMMMMMMMMMMMZZ++++++?DMMMMMMMMMMMMMMZZ???????????????IIIIIIIIIII????????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I=DMMMMMMMMMMMMMMMN?=++++8MMMMMMMMMMMMMMMZ$??????????????IIIIIIIIIIIIII??????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I+8MMMMMMMMMMMMMMMMD?=+IDMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIII????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++?I+8MMMMMMMMMMMMMMMMMOI~OMMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIIII????????????IIIIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++II+8MMMMMMMMMMMNNMMNMND8MMNNMMNNMMMMMMMMMMZ$????????????IZZ8888OZ7IIIIIIIIIIIIIIIIIIIIIIZD7IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++++II+8MMMMMMMMMMII????????OOOOOOZ8MMMMMMMMMMZ$??????????ZDMMMMMDDDNND87IIIIIIIIIIIIIII?Z8MMDIIIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI++++++7$ZZZZZZZOOMMMMMMMMMMZ$??????IINMMMMMMD+IIII7I7DMMIIIIIIII?I8NMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI+++++I$ZZZZZZZZ$ZMMMMMMMMMMZ$??????IMMMMMMMMMI??????IIO87IIIIII?DMMMMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++?III+8MMMMMMMMMMI++=$$ZZZZZZZZZIIZMMMMMMMMMMZ$??????MMMMMMMMMMMZ??????????????IIIMMMMMMMMMMD$ZZZZIIIIIIIIII+Z8DDNMMMDDDOO$I?????????????IIIII$ZZZ7IIII7O8887II
+?IIII+8MMMMMMMMMMI++7ZZZZZZZZZZI+IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMM$????????????OMMMMMMMMMMMMMMMMMMNIIIIIIIII8MMMD888DMMMMMMMND$?????????8MMMMMMMMMMOII78MMMMM8?I
+?IIII+8MMMMMMMMMMI?7ZZZZZZZZZZ?++IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMMMM8??????????+++?MMMMMMMMMM8IIIIIIIIIIIZMMM77IIIIIII8MMMMMMMMND?II????8MMMMMMMMMMOODNZII7Z8I7I
?IIIII+8MMMMMMMMMMZZZZZZZZZZZZI+++IZMMMMMMMMMMZ$??????NMMMMMMMMMMMMMMDII??????????IMMMMMMMMMM8IIIIIIIIIIIO8ZI?IIIIIIIIZDMMMMMMMMMD??????8MMMMMMMMMMN8D7IIIIIIIII
?IIIII+8MMMMMMMMMNZZZZZZZZZZZZ++++?ZMMMMMMMMMMZ$??????ZMMMMMMMMMMMMMMMMN7?????????IMMMMMMMMMM8IIIIIIIIIIIIIII?IIIIIIIIZDMMMMMMMMMMI?????8MMMMMMMMMM8IIIIIIIIIIII
?IIIII+8MMMMMMMMN8ZZZZZZZZZZZ?++++?ZMMMMMMMMMMZ$??????I8MMMMMMMMMMMMMMMM8?????????IMMMMMMMMMMO?IIIIIIIIIIIII7I7777777IODMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMNZZZZZZZZZZZZ7+++++?ZMMMMMMMMMMZ$????????8MMMMMMMMMMMMMMMMDD???????IMMMMMMMMMMO??IIIIIIIII7DMMMMMMMDDMDDNMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNZZZZZZZZZZZZ$++++++?ZMMMMMMMMMMZ$I????????7NMMMMMMMMMMMMMMMMDI?????IMMMMMMMMMMO????IIIIIZ8MMMMMMMM7III7ONMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNOZZZZZZZZZZZ7++++++?ZMMMMMMMMMMZ$III??????+IMMMMMMMMMMMMMMMMN$+????IMMMMMMMMMMO????IIII?NMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMNOZZZZZZZZ?++++++?ZMMMMMMMMMMZ$IIII????????ZMMMMMMMMMMMMMMMO?????IMMMMMMMMMMZ?????III$MMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMM?$ZZZZZZ$+++++++?ZMMMMMMMMMMZ$IIIIIIIIII???ZMMMMMMMMMMMMMMDZ????IMMMMMMMMMMZ?????IIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII=DMMMMMMMMMM?++7ZZZ7?+++++++IZMMMMMMMMMMZ$IIIIIIIIIIIIII7OMMMMMMMMMMMM8?????IMMMMMMMMMMZ????IIIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?II?II+8MMMMMMMMMMI++?ZOZ7?+++++++?ZMMMMMMMMMMZ$IIII7OZIIIIIIIII8MMMMMMMMMMMZ?????IMMMMMMMMMM$???OOD7IIMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIMMMMMMMMMMMMMMNNNN8O$I++++?NMNNMMMMMMMMMMMMMMD8I77NM8IIIIIIIIOMMMMMMMMMO??????+8MMMMMMMMMZ??$MM$?IIZMMMMMMMMM?IIIZNMMMMMMMMMMMZ?????8MMMMMMMMMMOIIIIIIIIIIII
?II?MMMMMMMMMMMMMMMMMM88??++++?MMMMMMMMMMMMMMMMMMD8II7IDMMOIIIIIIOMMMMMMMDOIIII??I??NMMMMMMMMMO8MZ$?IIIIZMMMMMMMMZIZ8MDMMMMMMMMMMMO?????8MMMMMMMMMMOIIIIIIIIIIII
?II?DDDDDDDDDDDDDDD8DDZ$++++++?D8D8DDDDDDDDDDDDDDOZIIIIII?7ODMMMMMMMNDZ7?IIIIIII??????ZDMMMMN8Z7??I?IIIIIIIZ8MMMMN8Z??7$ZZZZZZZZZZZ+????IZZZZZZZZZZ7IIIIIIIIIIII
?IIIII++++++++++++++++=+++++++++++IIIIIIIIIIIIIIIIII???I?????I77ZZ77IIIIIIIIIIIII????I???II??????????IIIIIIII?777IIIIIIII???????????????????????IIIIIIIIIIIIIIII
*/
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

#ifndef MSAPI_PVR_H
#define MSAPI_PVR_H

#if ENABLE_PVR
#include "datatype.h"
#include "msAPI_DTVSystem.h"
#include "apiDMX.h"
#include "msAPI_Player.h"
#include "MApp_Subtitle.h"      //app <--better not be here
#include "msAPI_FSCommon.h"
/*definition ====================================================================================*/
//#####################very special definition for PARDAI version@MSTARSEMI.COM####################
#define PVR_UTOPIA
#define PVR_UTOPIA_T3    //there are many different between T2 & T3

//#####################very special definition for PARDAI version@MSTARSEMI.COM####################

#ifndef S3PLUS
#define PVR_MAX_RECORD_PATH         3
#else
#define PVR_MAX_RECORD_PATH         1
#endif
#define PVR_MAX_PLAYBACK_PATH       1

#define PVR_RECORD_TIME_INFINITE    (U16)(0xffff)
#define PVR_RECORD_LENGTH_INFINITE  (U32)(0xffffffff)

#ifndef S3PLUS
#define PVR_TS_PACKET_SIZE              192
#define PVR_TS_PACKET_HEADER_SIZE         8
#else
#define PVR_TS_PACKET_SIZE              188
#define PVR_TS_PACKET_HEADER_SIZE         4
#endif

//#if (!defined(PVR_8051) && !defined(PVR_UTOPIA)) //Chakra1
//#define ENABLE_PVR_AESDMA           0
//#else
//#define ENABLE_PVR_AESDMA           0
//#endif

#define PvrGetWriteMetadataBufAddr_PA()    ((PVR_WRITE_METADATA_BUFFER_MEMORY_TYPE & MIU1) ? (PVR_WRITE_METADATA_BUFFER_ADR | MIU_INTERVAL) : (PVR_WRITE_METADATA_BUFFER_ADR))
#define PvrGetReadMetadataBufAddr_PA()     ((PVR_READ_METADATA_BUFFER_MEMORY_TYPE & MIU1) ? (PVR_READ_METADATA_BUFFER_ADR | MIU_INTERVAL) : (PVR_READ_METADATA_BUFFER_ADR))

#define PvrGetWriteMetadataBufAddr_VA()    _PA2VA(PVR_WRITE_METADATA_BUFFER_ADR)
#define PvrGetReadMetadataBufAddr_VA()     _PA2VA(PVR_READ_METADATA_BUFFER_ADR)

#if 1//def MIPS_CHAKRA
    #define PvrGetWriteMetadataBufAddr()    PvrGetWriteMetadataBufAddr_VA()
    #define PvrGetReadMetadataBufAddr()     PvrGetReadMetadataBufAddr_VA()
#else
    #define PvrGetWriteMetadataBufAddr()    PVR_WRITE_METADATA_BUFFER_ADR
    #define PvrGetReadMetadataBufAddr()     PVR_READ_METADATA_BUFFER_ADR
#endif

//__________________________________meta_data_of_pvr_read_write____________________________________
#define META_DATA_SIZE                  (U32)(3072)                         //3.0K , don't change this value

#ifdef S3PLUS
#define PVR_MAX_PROGRAMME_PER_FILE  (U32)(1  )
#else
#if ((PVR_WRITE_METADATA_BUFFER_LEN /0xC00) < 128)     //if chip is 64M,LEN = c00H
#define PVR_MAX_PROGRAMME_PER_FILE  (U32)(1)
#else
#define PVR_MAX_PROGRAMME_PER_FILE  (U32)(128)
#endif
#endif

#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
#define TOTAL_META_DATA_SIZEKB  (U32)(PVR_MAX_PROGRAMME_PER_FILE*(META_DATA_SIZE/1024))

 // Check MMAP
 #if( PVR_WRITE_METADATA_BUFFER_LEN == 0 )
    #error "PVR_WRITE_METADATA_BUFFER_LEN == 0"
 #endif
 #if( PVR_READ_METADATA_BUFFER_LEN == 0 )
    #error "PVR_READ_METADATA_BUFFER_LEN == 0"
 #endif

#endif

#if 1//def PVR_UTOPIA
    #define MSAPI_DMX_INVALID_FLT_TYPE  (MS_U8)0xff
    #define MSAPI_DMX_BYPASS_PID        (MS_U16)0x1fff
    #define PVR_FILE_IN_SIZE            0x90000 //288K for 192
    //#define PVR_FILE_IN_SIZE        0x5E000 //376K for 188
#endif


#define PvrGetWriteSdramAdr_PA()    ((PVR_WRITE_SDRAM_MEMORY_TYPE&MIU1)?PVR_WRITE_SDRAM_ADR|MIU_INTERVAL:PVR_WRITE_SDRAM_ADR)
#define PvrGetReadSdramAdr_PA()     ((PVR_READ_SDRAM_MEMORY_TYPE&MIU1)?PVR_READ_SDRAM_ADR|MIU_INTERVAL:PVR_READ_SDRAM_ADR)

#define PvrGetWriteSdramAdr_VA()    _PA2VA(PvrGetWriteSdramAdr_PA())
#define PvrGetReadSdramAdr_VA()     _PA2VA(PvrGetReadSdramAdr_PA())

#if 1//def MIPS_CHAKRA
    #define PvrGetWriteSdramAdr()   PvrGetWriteSdramAdr_VA()//_PA2VA(((PVR_WRITE_SDRAM_MEMORY_TYPE&MIU1)?PVR_WRITE_SDRAM_ADR|MIU_INTERVAL:PVR_WRITE_SDRAM_ADR))
    #define PvrGetReadSdramAdr()    PvrGetReadSdramAdr_VA()//_PA2VA(((PVR_READ_SDRAM_MEMORY_TYPE&MIU1)?PVR_READ_SDRAM_ADR|MIU_INTERVAL:PVR_READ_SDRAM_ADR))

#else
    #define PvrGetWriteSdramAdr() PVR_WRITE_SDRAM_ADR
    #define PvrGetReadSdramAdr()  PVR_READ_SDRAM_ADR
#endif

/*enumeration ===================================================================================*/
typedef enum
{
    E_FILE_MODE_NORMAL = 1,
    E_FILE_MODE_RING
} enPvrFileMode;

typedef enum
{
    E_DECRYPT,
    E_ENCRYPT
} enPvrAESDMAMode;

typedef enum
{
    E_PVR_ENCRYPTION_NONE    = 0,
    E_PVR_ENCRYPTION_DEFAULT = 1,
    E_PVR_ENCRYPTION_CIPLUS  = 2,
    E_PVR_ENCRYPTION_MAX
} enPvrEncryptType;

typedef enum
{
    E_PLAYBACK_PATH_DIRECTION_FORWARD = 1,
    E_PLAYBACK_PATH_DIRECTION_JUMPFORWARD,
    E_PLAYBACK_PATH_DIRECTION_JUMPBACKWARD,
    E_PLAYBACK_PATH_DIRECTION_FASTFORWARD,
    E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD,
    E_PLAYBACK_PATH_DIRECTION_STEPIN,
    E_PLAYBACK_PATH_DIRECTION_SLOWFORWARD,
} enPvrPlaybackPathDirection;

typedef enum
{
    E_JUMP_BUFFER_CONTINUOUS = 1,
    E_JUMP_BUFFER_RESET
} enPvrJumpBufferMode;

typedef enum
{
    E_PVR_API_STATUS_OK                             = 0,  //original
    E_PVR_API_STATUS_ERROR                          = 1,

    E_PVR_API_STATUS_NO_DISK_FOR_WRITE              = 10, //file sys
    E_PVR_API_STATUS_NO_DISK_FOR_READ               = 11,
    E_PVR_API_STATUS_NO_DISK_SPACE                  = 12,
    E_PVR_API_STATUS_DISK_SPEED_SLOW                = 13,
    E_PVR_API_STATUS_TIMESHIFT_BUFFER_NOT_ENOUGH    = 14,
    E_PVR_API_STATUS_FILE_SYS_INIT_FAIL             = 15,
    E_PVR_API_STATUS_FILE_SEEK_FAIL                 = 16,
    E_PVR_API_STATUS_FILE_WRITE_ERROR               = 17,
    E_PVR_API_STATUS_FILE_READ_ERROR                = 18,
    E_PVR_API_STATUS_FILE_BUMP_START                = 19,
    E_PVR_API_STATUS_FILE_BUMP_END                  = 20,
    E_PVR_API_STATUS_FILE_STILL_HAVE_DATA_WAIT      = 21,

    E_PVR_API_STATUS_RECORD_NO_FILTER               = 40, //demux
    E_PVR_API_STATUS_PLAYBACK_NO_FILTER             = 41,
    E_PVR_API_STATUS_INVALID_PID                    = 42,
    E_PVR_API_STATUS_RECORD_NO_INPUT                = 43,
    E_PVR_API_STATUS_PLAYBACK_NO_OUTPUT             = 44,
    E_PVR_API_STATUS_RECORD_BUFFER_ERROR            = 45,
    E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR          = 46,
    E_PVR_API_STATUS_RECORD_BUFFER_OVERRUN          = 47,
    E_PVR_API_STATUS_PLAYBACK_BUFFER_UNDERRUN       = 48,
    E_PVR_API_STATUS_PLAYBACK_BUFFER_FULL           = 49,
    E_PVR_API_STATUS_RECORD_FILE_OVER_SIZE          = 50,
#if ENABLE_CI_PLUS
    E_PVR_API_STATUS_PROTECTION                     = 51,
#if (ENABLE_CIPLUS_PVR)
    E_PVR_API_STATUS_SUCCESS_CIPLUS_COPY_PROTECTION   = 52,
    E_PVR_API_STATUS_ERROR_CIPLUS_COPY_PROTECTION      = 53,
    E_PVR_API_STATUS_ERROR_CIPLUS_UNPLUGIN                    = 54,
    E_PVR_API_STATUS_ERROR_CIPLUS_UNSUPPORT                 = 55,
    E_PVR_API_STATUS_ERROR_RETENTION_LIMIT_EXPIRED     = 56,
#endif
#endif
} enPvrApiStatus;

/*data structure ================================================================================*/
//<<record path>>================================================================================//
typedef struct msAPI_PVR_RecordPath
{
    //pvr ===================================================================//
    BOOLEAN bInUse;                                         //api only      --|GROUP0-1 : On/Off
    U8 u8LogicalProgrammeNumber;                            //api only      -//
    U16 u16PlaybackCount;
    U16 u16ServiceID;                                        //api only      -//

    //demux =================================================================//
    U8  u8FilterID[MSAPI_DMX_RECORD_FILTER_NUMBER];         //api only      --|GROUP1-1 : Filter
    U16 u16PID[MSAPI_DMX_RECORD_FILTER_NUMBER];             //from ap       -||
    MSAPI_DMX_FILTER_TYPE  enFilterType[MSAPI_DMX_RECORD_FILTER_NUMBER];     //
    BOOLEAN bRecordAll;                                     //from ap       -//

    U32 u32BufferStart;                                     //from ap       --|
    U32 u32BufferLength;                                    //from ap        ||GROUP1-2 : Dram Buffer
    U32 u32BufferReadPointer;                               //api only       ||
    U32 u32BufferWritePointer;                              //api only      -//

    //file system ===========================================================//
    U8  hWriteFile;                                         //api only      --|
    U32 u32FilePositionKB;                                  //api only       ||GROUP2-1 : Opened File
    U32 u32FilePosRmnBytes;                                 //api only       make File position counts as bytes, it stores the remainder of KB
    U32 u32FileLastPosKB;                                   //api only       ||
    U32 u32FileSizeKB;                                      //api only      -//

    U32 u32FileGapSizeKB;                                   //api only      --|
    U32 u32FileLimitedSizeKB;                               //api only       ||
    U32 u32FileValidPosStrKB;                               //api only       ||
    U32 u32FileValidPosEndKB;                               //api only       ||GROUP2-2 : Only for Timeshift
    U32 u32FileValidDistanceKB;                             //api only       ||
    U32 u32FileValidPeriod;     //in 1/10   SECOND          //api only      -//

    U32 u32FileWriteTime;       //in 1/1000 SECOND          //api only      --|GROUP2-3 : Only for Debug
    U32 u32FileWriteSizeKB;                                 //api only      -//

    //media format ==========================================================//
    enPlayVideoType enVideoType;                            //from ap        ]]GROUP3-1 : Video

    enPlayAudioType enAudioType;                            //from ap       --|GROUP3-2 : Audio
    enPlayAudioType enAdAudioType;                          //from ap        ||
    U8 u8audioLangTotal;                                    //from ap        ||
    U8 u8audioLangSel;                                      //from ap        ||
    AUD_INFO PVRAudioInfo[MAX_AUD_LANG_NUM];                //from ap       -//

    U16 u8DVBSubtitleServiceNum;                            //from ap       --|GROUP3-3 : Subtitle
    U16 u8SubtitleMenuNum;                                  //from ap        ||
    U8 u8SubtitleMenuSelectedIdx;                           //from ap        ||
    U8 u8TTXSubtitleServiceNum;                             //from ap        ||
    U8 u8EnableSubtitle;                                    //from ap        ||
    U8 u8EnableTTXSubtitle;                                 //from ap        ||
    DVB_SUBTITLE_SERVICE PVRDVBSubtitleServices[MAX_SUBTITLE_SERVICE_NUM];   //
    SUBTITLE_MENU        PVRSubtitleMenu[MAX_SUBTITLE_SERVICE_NUM];          //

    //system ================================================================//
    U32 u32RecordedStartSysTime;        //in 1/1000 SECOND          //api only      --|GROUP4-1 : Recorded Time
    U32 u32RecordedTime;        //in 1/1000 SECOND          //api only      --|GROUP4-1 : Recorded Time
    U32 u32RecordedPeriod;      //in 1/10   SECOND          //api only      -//
    U32 u32RecordedTotalTime;   //in 1/10   SECOND          //api only      -//

    U32 u32PausedTime;          //in 1/1000 SECOND          //api only      --|GROUP4-2 : Paused Time
    U32 u32PausedPeriod;        //in 1/10   SECOND          //api only      -//

    U32 u32RecordedKBytes;      //in KBYTE                  //api only      --|
    U16 u16RecordedMaxRate;     //in KBYTE                  //api only       ||
    U16 u16RecordedMinRate;     //in KBYTE                  //api only       ||GROUP4-5 : Recorded Rate
    U16 u16RecordedLstRate;     //in KBYTE                  //api only       ||
    U16 u16RecordedAvgRate;     //in KBYTE                  //api only       ||
    U16 u16RecordedErrCount1;   //in KBYTE                  //api only       ||
    U16 u16RecordedErrCount2;   //in KBYTE                  //api only       ||
    U16 u16RecordedErrCount3;   //in KBYTE                  //api only      -//

    U32 u32RecordedStaCheckTime;//in 1/1000 SECOND          //api only       ]]GROUP4-6 : Period Check

    U8 u8Parental_Control;

    //############################ ************************* ############################
    BOOLEAN bLinkPlayback;                                  //from ap        ]]GROUP4-7 : Linkage
    //############################ ************************* ############################

    enPvrEncryptType enEncryptionType; //for CI+ PVR, Freeview
    /// CI checking level
    U8 u8CicamCheckLevel;
} _msAPI_PVR_RecordPath;

//<<playback path>>==============================================================================//
typedef struct msAPI_PVR_PlaybackPath
{
    // pvr ==================================================================//
    BOOLEAN bInUse;                                         //api only      --|
    enPvrPlaybackPathDirection enDirection;                 //api only       ||GROUP0-1 : On/Off
    U8 u8LogicalProgrammeNumber;                            //api only      -//

    //demux =================================================================//
    U8  u8FilterID[MSAPI_DMX_RECORD_FILTER_NUMBER];         //api only      --|GROUP1-1 : Filter
    U16 u16PID[MSAPI_DMX_RECORD_FILTER_NUMBER];             //from ap       -||
    MSAPI_DMX_FILTER_TYPE  enFilterType[MSAPI_DMX_RECORD_FILTER_NUMBER];     //

    U32 u32BufferStart;                                     //from ap       --|
    U32 u32BufferLength;                                    //from ap        ||GROUP1-2 : Dram Buffer
    U32 u32BufferReadPointer;                               //api only       ||
    U32 u32BufferWritePointer;                              //api only      -//

	#ifdef S3PLUS
    U32 u32CurTimerDelay;                                   //api only      --|GROUP1-3 : Delay Control
    U32 u32PrvTimerDelay;                                   //api only      -//
    #endif

    U32 u32STC;                                             //api only       ]]GROUP1-4 : TS Clock

    //file system ===========================================================//
    U8  hReadFile;                                          //api only      --|
    U32 u32FilePositionKB;                                  //api only       ||GROUP2-1 : Opened File
    U32 u32FileLastPosKB;                                   //api only       ||
    U32 u32FileSizeKB;                                      //api only      -//

    U32 u32FileLimitedSizeKB;                               //from ap        ||
    U32 u32FileValidPosStrKB;                               //from ap        ||
    U32 u32FileValidPosEndKB;                               //from ap        ||GROUP2-2 : Only for Timeshift

    U32 u32FileReadTime;        //in 1/10   SECOND          //api only      --|GROUP2-3 : Only for Debug
    U8  u8FileReadCount;                                    //api only      -//

    U16 u16FileReadAccumulatorKB;                           //api only       ]]GROUP2-4 : For Fast Forward

    BOOLEAN bABLoopSwitch;                                  //from ap       --|GROUP2-6 : For AB Loop
    U32 u32FilePosAKB;                                      //from ap       -//

    //media format ==========================================================//
    enPlayVideoType enVideoType;                            //from ap        ]]GROUP3-1 : Video

    enPlayAudioType enAudioType;                            //from ap       --|GROUP3-2 : Audio
    enPlayAudioType enAdAudioType;                          //from ap        //
	AUD_INFO PVRAudioInfo[MAX_AUD_LANG_NUM];				//from ap		-//

    //system ================================================================//
    U16 u16PlayedErrCount3;     //in KBYTE                  //api only      -//

#ifdef S3PLUS
    U32 u32PlayedTunCheckTime;  //in 1/1000 SECOND          //api only      -//
    enPlaySpeed enPlaySpeed;
#endif

    //############################ ************************* ############################
    BOOLEAN bLinkRecord;                                    //from ap        ]]GROUP4-7 : Linkage
    _msAPI_PVR_RecordPath * pstPvrRecordPath; //<---Linking to Record Path in Playback Mode
    //############################ ************************* ############################
    BOOLEAN bNeedSetTimeStamp;
} _msAPI_PVR_PlaybackPath;

/*function ======================================================================================*/
#ifdef MSAPI_PVR_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE U32 u32RecordLastWriteDataSize;
INTERFACE U32 u32RecordReWriteDataSize;

#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
INTERFACE void msAPI_PVR_InitMetadataBuff(void);
#endif

INTERFACE enPvrApiStatus msAPI_PVR_Initial(void);

INTERFACE _msAPI_PVR_RecordPath *   msAPI_PVR_RecordPathOpen(U16 *pu16RecordPathName, enPvrFileMode enFileMode);
INTERFACE enPvrApiStatus msAPI_PVR_RecordPathSet(_msAPI_PVR_RecordPath * pstPvrRecordPath);
INTERFACE enPvrApiStatus msAPI_PVR_RecordPathAddPID(_msAPI_PVR_RecordPath * pstPvrRecordPath, U16 u16PID, MSAPI_DMX_FILTER_TYPE enFltType);
INTERFACE enPvrApiStatus msAPI_PVR_RecordPathStart(_msAPI_PVR_RecordPath * pstPvrRecordPath);
INTERFACE enPvrApiStatus msAPI_PVR_RecordPathInput(_msAPI_PVR_RecordPath * pstPvrRecordPath);
INTERFACE enPvrApiStatus msAPI_PVR_RecordPathGatherStatistics(_msAPI_PVR_RecordPath * pstPvrRecordPath);
INTERFACE enPvrApiStatus msAPI_PVR_RecordPathStop(_msAPI_PVR_RecordPath * pstPvrRecordPath);
INTERFACE enPvrApiStatus msAPI_PVR_RecordPathClose(_msAPI_PVR_RecordPath * pstPvrRecordPath);

INTERFACE _msAPI_PVR_PlaybackPath * msAPI_PVR_PlaybackPathOpen(U16 *pu16PlaybackPathName);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathSet(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathAddPID(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath, U16 u16PID, MSAPI_DMX_FILTER_TYPE enFltType);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathDelPID(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath, U16 u16PID, MSAPI_DMX_FILTER_TYPE enFltType);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathStart(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathForwardOutput(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);

INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathJumpForward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath, U32 u16JumpSecond, enPvrJumpBufferMode enBufferMode);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathStepIn(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathSlowForward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathFastForward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathFastBackward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathPause(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathResume(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathStop(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_PlaybackPathClose(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
INTERFACE enPvrApiStatus msAPI_PVR_RecordChangeFile(U16 *pu16RecordFileName, _msAPI_PVR_RecordPath * pstPvrRecordPath);
INTERFACE BOOLEAN  msAPI_PVR_IsRecordSpaceEnough(void);
INTERFACE void msAPI_PVR_PlaybackPathWaitAVFifoClean(void);
#ifdef PVR_UTOPIA
    INTERFACE void msAPI_PVR_ClearBitStreamBuff(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath);
#endif
#if (PVR_TS_PACKET_SIZE == 192)
INTERFACE U32 msAPI_PVR_PlaybackGetTotalTimeByTimeStamp(enPvrEncryptType enEncryptionType,U8 u8FileHandle);
INTERFACE U32 msAPI_PVR_PlaybackGetPosTimeByTimeStamp(enPvrEncryptType enEncryptionType,U8 u8FileHandle,LongLong filePos);
#endif
INTERFACE void msAPI_PVR_RecoreReset(_msAPI_PVR_RecordPath * pstPvrRecordPath);
INTERFACE enPvrApiStatus msAPI_PVR_GetMetaData(U16 *pFileName, _msAPI_PVR_RecordPath *pMetaData);
INTERFACE BOOL msAPI_PVR_IsMStarPVRFile(U16 *pFileName);
INTERFACE enPvrApiStatus msAPI_PVR_AESDMAEncryptDecrypt(U32 u32VirAddress, U32 u32Length, enPvrAESDMAMode eMode);
INTERFACE enPvrEncryptType msAPI_PVR_GetEncryptType(FileEntry *pFileEntry);
INTERFACE BOOL msAPI_PVR_GetRecordCAPVR(void);
INTERFACE void msAPI_PVR_SetRecordCAPVR(enPvrEncryptType enEncryptionType);
#undef INTERFACE
#endif// #if ENABLE_PVR
#endif

