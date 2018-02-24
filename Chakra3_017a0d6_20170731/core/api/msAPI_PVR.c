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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_PVR_C

//system
#include "Board.h"                  //For pvr select
#include "MsCommon.h"
#include "debug.h"

#if ENABLE_PVR

//driver
#ifdef PVR_8051
#include "drvUART.h"                //For compiled error
#endif

#ifdef PVR_UTOPIA
#include "SysInit.h"                 //For window1 switch
#endif

#ifndef S3PLUS
#include "apiXC.h"
#include "drvPQ.h"                  //For reduce scaler bw usage
#endif

//api
#include "FSUtil.h"
#include "msAPI_MIU.h"              //For memory dma
#include "msAPI_Timer.h"            //For timer
#include "apiDMX.h"                 //For demux part
#include "apiVDEC.h"
#include "msAPI_FCtrl.h"                //For msAPI_FCtrl_IsDriveMounted
#include "msAPI_PVRFileSystem.h"    //For file system part
#include "msAPI_Player.h"           //For video/audio/scaler function
#include "msAPI_PVR.h"              //For itself
#include "msAPI_Tuner.h"
#include "mapp_demux.h"
#include "apiXC_Sys.h"
#ifdef PVR_UTOPIA
#include "drvAESDMA.h"
#else
#include "drv_aesdma.h"             //For AES encrypt, decrypt
#endif

#if ENABLE_TTX
#include "msAPI_TTX.h"
#endif
#if ENABLE_DVB_T2
#include "MApp_Scan.h"
#endif

#include "MApp_Playback.h"
#include "MApp_TimeShift.h"
#include "MApp_GlobalFunction.h"
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_CIPVR_Adaption.h"              //For pvr
#endif

/*************************************************************************************************/
typedef enum
{
    E_METADATA_UPDATE_FILE = 1, //for Playback
    E_METADATA_UPDATE_MEMORY    //for Timeshift and Playback while Record
} enPvrMetadataUpdateMode;

/*************************************************************************************************/
#define WRITE_CHECK_START               3000                                //record_path   start: 3rd sec
#define WRITE_CHECK_DURATION            1000                                //record_path   check: 1   sec
#define READ_CHECK_START                1000                                //playback_path start: 1st sec
#define READ_CHECK_DURATION             1000                                //playback_path check: 1   sec

#define MAX_WRITE_LENGTH                (U32)0x00040000                     //record_unit  : 256K bytes
#define MIN_WRITE_LENGTH                (U32)0x00001000                     //record_unit  : 4K   bytes
#define MAX_READ_LENGTH                 (U32)0x000C0000                     //playback_unit: 768K bytes (192*4096)
#define MIN_READ_LENGTH                 (U32)0x00001800                     //playback_unit: 6K   bytes (192*32)
#define ALIGNMINWRITE(x)                (x&~(MIN_WRITE_LENGTH-1))
#define ALIGNMINREAD(x)                 ((x/MIN_READ_LENGTH)*MIN_READ_LENGTH)

#define FAT_AVERAGE_READ_WRITE_KBYTES         0x80 //128 KBytes  //need to syn with msAPI_PVRFileSystem.c or refine later
#define FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC 2048 //2048 KBytes/sec  //need to syn with msAPI_PVRFileSystem.c or refine later

#ifdef S3PLUS
                                        // 24000000/32000000 =25.00% off to prevent underrun
                                        //_________________________________________________________
#define MAGIC_NUMBER_TIMER_DELAY        (U32)60000                          //timer_delay: if not use time_stamp
#endif

#define MAX_FAT32_FILE_SIZE_KB          (U32)4123686    //maxmun fat32 record KB size of single file
#ifdef S3PLUS
#define MIN_FAT32_FILE_SIZE_KB          (U32)102400     //100MB
#else
#define MIN_FAT32_FILE_SIZE_KB          (U32)307200     //300MB
#endif

#define PLAYBACK_BUFF_ERR_COUNT         5

#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
#if 0//def PVR_8051
static U8 xdata * _pu8MetadataForWrite = (U8 xdata *)0xf000;
static U8 xdata * _pu8MetadataForRead  = (U8 xdata *)0xf000;
#else
#if 1//def PVR_UTOPIA
#if 1//def MIPS_CHAKRA
static U8* _pu8MetadataForWrite;
static U8* _pu8MetadataForRead;
#else
static U8 * _pu8MetadataForWrite = (U8 *) ((PVR_WRITE_METADATA_BUFFER_MEMORY_TYPE & MIU1) ? (PVR_WRITE_METADATA_BUFFER_ADR | MIU_INTERVAL) : (PVR_WRITE_METADATA_BUFFER_ADR));
static U8 * _pu8MetadataForRead  = (U8 *) ((PVR_READ_METADATA_BUFFER_MEMORY_TYPE & MIU1) ? (PVR_READ_METADATA_BUFFER_ADR | MIU_INTERVAL) : (PVR_READ_METADATA_BUFFER_ADR));
#endif
#else
static U8 * _pu8MetadataForWrite = (U8 *) PVR_WRITE_METADATA_BUFFER_ADR;
static U8 * _pu8MetadataForRead  = (U8 *) PVR_READ_METADATA_BUFFER_ADR;
#endif
#endif
#endif
static _msAPI_PVR_RecordPath _PvrRecordMeataData;
//_________________________________________________________________________________________________

/*************************************************************************************************/
static _msAPI_PVR_RecordPath    _PvrRecordPath[PVR_MAX_RECORD_PATH];        //thhree record   path
static _msAPI_PVR_PlaybackPath  _PvrPlaybackPath[PVR_MAX_PLAYBACK_PATH];    //one    playback path

static U16 _u16BulkFileSystemRWSpeed;   //from Bulk File System
static U32 _u32BulkFileSystemRWLength;  //from Bulk File System

static U8  _u8LPNAccumulator;           //Logical Programme Number Accumulator

static U8  _pu8RecordFID[MSAPI_DMX_RECORD_FILTER_NUMBER];      //co-management of Record FID/PID/PIDCount
static U16 _pu16RecordPID[MSAPI_DMX_RECORD_FILTER_NUMBER];     //co-management of Record FID/PID/PIDCount
static U8  _pu8RecordPIDCount[MSAPI_DMX_RECORD_FILTER_NUMBER]; //co-management of Record FID/PID/PIDCount

#ifdef PVR_UTOPIA
    static U32 _u32MaxDmxCmdSlot = 0;
#endif

#ifndef S3PLUS
//#ifndef PVR_UTOPIA
static U32 u32PvrPauseTimeStamp = 0;
static U32 u32PreWritePointer = 0;
//#endif
#endif

//#ifdef S3PLUS
static BOOLEAN _bAlignSyncByte = FALSE;
static BOOLEAN _bRecordCAPVR = FALSE;
//#endif
/*************************************************************************************************/

/*###############################################################################################*/
/*///////////////////////////////////////// pvr all  ////////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void msAPI_PVR_PlaybackPathWaitAVFifoClean(void)
{
    #ifdef PVR_UTOPIA  //In UTOPIA, TSP will go into block state if it's in file_in mode and AVFifo > 25%. We do things below to prevent this.
    U32 u32VFifoLevel = 0; //u32VFifoLevel=1: empty
    U32 u32AFifoLevel = 0; //u32AFifoLevel=1: empty
    U32 u32Cnt =0;
    U32 u32EmptyCnt =0;
  //  if (MApi_DMX_Pvr_TimeStampDisable() != DMX_FILTER_STATUS_OK) {ASSERT(0);}//disable timestamp to accelerate flush speed
    while(u32Cnt < 10)
    {
        if (MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_VIDEO, TRUE) != DMX_FILTER_STATUS_OK) {ASSERT(0);}
        if (MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, TRUE) != DMX_FILTER_STATUS_OK) {ASSERT(0);}
        msAPI_Timer_Delayms(100);
        if (MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_VIDEO, FALSE) != DMX_FILTER_STATUS_OK) {ASSERT(0);}
        if (MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, FALSE) != DMX_FILTER_STATUS_OK) {ASSERT(0);}
        msAPI_Timer_Delayms(50);
        if (MApi_DMX_AVFifo_Status(DMX_FILTER_TYPE_VIDEO, &u32VFifoLevel) != DMX_FILTER_STATUS_OK) {ASSERT(0);}
        if (MApi_DMX_AVFifo_Status(DMX_FILTER_TYPE_AUDIO, &u32AFifoLevel) != DMX_FILTER_STATUS_OK) {ASSERT(0);}
        if (u32VFifoLevel && u32AFifoLevel)
            u32EmptyCnt++;
        else u32EmptyCnt = 0; //recalculate
        if (u32EmptyCnt > 2) //detect empty status of AV fifo at least 3 times, break;
            break;
        u32Cnt++;
    }
    #endif
    return;
}
#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
void msAPI_PVR_InitMetadataBuff(void)
{
    U8 u8PacketNo;
    U8 u8ProgrammeNo;

#if 1//def MIPS_CHAKRA
    //_pu8MetadataForWrite = (U8 *) ((PVR_WRITE_METADATA_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetWriteMetadataBufAddr() | MIU_INTERVAL) : (PvrGetWriteMetadataBufAddr()));
    _pu8MetadataForWrite = (U8 *) PvrGetWriteMetadataBufAddr_VA();

    //_pu8MetadataForRead  = (U8 *) ((PVR_READ_METADATA_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetReadMetadataBufAddr() | MIU_INTERVAL) : (PvrGetReadMetadataBufAddr()));
    _pu8MetadataForRead  = (U8 *) PvrGetReadMetadataBufAddr_VA();
#endif

    /*[01-0]pvr part ==================================================================*/
    for(u8ProgrammeNo=0; u8ProgrammeNo<PVR_MAX_PROGRAMME_PER_FILE; u8ProgrammeNo++)
    {
        #ifdef PVR_8051
        U16 u16Segment = (PVR_WRITE_METADATA_BUFFER_ADR+u8ProgrammeNo*META_DATA_SIZE)/4096;
        U16 u16Offset  = (PVR_WRITE_METADATA_BUFFER_ADR+u8ProgrammeNo*META_DATA_SIZE)%4096;
        #else
        U32 u16Offset  = u8ProgrammeNo*META_DATA_SIZE;
        #endif

        #ifdef PVR_8051
        if(u16Offset <= 1024)
        #else
        if(1)
        #endif
        {
            #ifdef PVR_8051
            MDrv_Sys_SetXdataWindow1Base(u16Segment);
            #endif
            memset(_pu8MetadataForWrite+u16Offset, 0x00, META_DATA_SIZE);
            for(u8PacketNo=0; u8PacketNo<= META_DATA_SIZE/PVR_TS_PACKET_SIZE; u8PacketNo++)
            {
                #ifndef S3PLUS
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+0]=0x02;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+1]=0x1E;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+2]=0x15;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+3]=0x76;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+4]=0x47;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+5]=0xff;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+6]=0xff;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+7]=u8PacketNo;
                #else
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+0]=0x47;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+1]=0xff;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+2]=0xff;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+3]=u8PacketNo;
                #endif
            }
            #ifdef PVR_8051
            MDrv_Sys_ReleaseXdataWindow1();
            #endif
        }
        else
        {
            U8 u8LastPacketNo=0;

            #ifdef PVR_8051
            MDrv_Sys_SetXdataWindow1Base(u16Segment);
            #endif
            memset(_pu8MetadataForWrite+u16Offset, 0x00, 4096-u16Offset);
            for(u8PacketNo=0; u8PacketNo<= (4096-u16Offset)/PVR_TS_PACKET_SIZE; u8PacketNo++)
            {
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+0]=0x02;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+1]=0x1E;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+2]=0x15;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+3]=0x76;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+4]=0x47;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+5]=0xff;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+6]=0xff;
                _pu8MetadataForWrite[u16Offset+u8PacketNo*PVR_TS_PACKET_SIZE+7]=u8PacketNo;

                u8LastPacketNo=u8PacketNo+1;
            }
            #ifdef PVR_8051
            MDrv_Sys_ReleaseXdataWindow1();
            #endif

            #ifdef PVR_8051
            MDrv_Sys_SetXdataWindow1Base(u16Segment+1);
            #endif
            memset(_pu8MetadataForWrite, 0x00, META_DATA_SIZE-(4096-u16Offset));
            for(u8PacketNo=0; u8PacketNo<= (META_DATA_SIZE-(4096-u16Offset))/PVR_TS_PACKET_SIZE; u8PacketNo++)
            {
                if(u16Offset==2048)
                {
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+0]=0x02;
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+1]=0x1E;
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+2]=0x15;
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+3]=0x76;
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+4]=0x47;
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+5]=0xff;
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+6]=0xff;
                    _pu8MetadataForWrite[64 +u8PacketNo*PVR_TS_PACKET_SIZE+7]=u8LastPacketNo+u8PacketNo;
                }
                else //u16Offset==3072
                {
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+0]=0x02;
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+1]=0x1E;
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+2]=0x15;
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+3]=0x76;
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+4]=0x47;
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+5]=0xff;
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+6]=0xff;
                    _pu8MetadataForWrite[128+u8PacketNo*PVR_TS_PACKET_SIZE+7]=u8LastPacketNo+u8PacketNo;
                }
            }
            #ifdef PVR_8051
            MDrv_Sys_ReleaseXdataWindow1();
            #endif
        }
    }

    #ifdef PVR_8051
    MDrv_Sys_SetXdataWindow1Base(PVR_READ_METADATA_BUFFER_ADR/4096);
    #endif
    memset(_pu8MetadataForRead, 0x00, META_DATA_SIZE);
    for(u8PacketNo=0; u8PacketNo<= META_DATA_SIZE/PVR_TS_PACKET_SIZE; u8PacketNo++)
    {
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+0]=0x02;
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+1]=0x1E;
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+2]=0x15;
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+3]=0x76;
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+4]=0x47;
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+5]=0xff;
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+6]=0xff;
        _pu8MetadataForRead[u8PacketNo*PVR_TS_PACKET_SIZE+7]=u8PacketNo;
    }
    #ifdef PVR_8051
    MDrv_Sys_ReleaseXdataWindow1();
    #endif
}
#endif

enPvrApiStatus msAPI_PVR_Initial(void)
{
    U8 u8PathID;
    U8 u8FID;
    BOOLEAN bRet;

#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
    msAPI_PVR_InitMetadataBuff();
#endif

    for(u8PathID = 0; u8PathID < PVR_MAX_RECORD_PATH; u8PathID++)
    {
        _PvrRecordPath[u8PathID].bInUse = FALSE;
    }

    for(u8PathID = 0; u8PathID < PVR_MAX_PLAYBACK_PATH; u8PathID++)
    {
        _PvrPlaybackPath[u8PathID].bInUse = FALSE;
    }

    /*[01-1]demux part ================================================================*/
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        _pu8RecordFID[u8FID]      = MSAPI_DMX_INVALID_FLT_ID; //all clear
        _pu16RecordPID[u8FID]     = MSAPI_DMX_INVALID_PID;    //all clear
        _pu8RecordPIDCount[u8FID] = 0;                        //all clear
    }

    /*[01-2]file system part ==========================================================*/
    if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
    {
        bRet = msAPI_PVRFS_Initial(TRUE); //force to init first for _enPVRFSFileSystemType
    }
    else
    {
        bRet = msAPI_PVRFS_Initial(FALSE);
    }

    if (bRet)
    {
    #if (ENABLE_BULK_FILE_SYSTEM)
        _u16BulkFileSystemRWSpeed = msAPI_PVRFS_GetBulkSpeed();
        _u32BulkFileSystemRWLength= (U32)msAPI_PVRFS_GetBulkRWKByteOfSpeed()*1024;
    #else
        _u16BulkFileSystemRWSpeed = FAT_DEFAULT_DISK_SPEED_KBYTES_PER_SEC;
        _u32BulkFileSystemRWLength= FAT_AVERAGE_READ_WRITE_KBYTES*1024;
    #endif
      //printf("_u16BulkFileSystemRWSpeed  = %04u  \n", _u16BulkFileSystemRWSpeed);
      //printf("_u32BulkFileSystemRWLength = %08lu \n", _u32BulkFileSystemRWLength);
        _u8LPNAccumulator = 0;


      //printf("reset LPN Accumulator \n");
        return E_PVR_API_STATUS_OK;
    }
    else
    {
        return E_PVR_API_STATUS_FILE_SYS_INIT_FAIL;
    }

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_Initial\n");

}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////////// pvr utilities  ////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static LongLong msAPI_PVR_KToLongLong(U32 u32KByteUnit)
{
    LongLong u64LongLongUnit;
    u64LongLongUnit.Hi = u32KByteUnit>>22;  // <<10 Then >>32
    u64LongLongUnit.Lo = u32KByteUnit<<10;

  //printf("HI:LO=0x%08lx|%08lx\n", u64LongLongUnit.Hi, u64LongLongUnit.Lo);

    return u64LongLongUnit;
}

/***************************************************************************************/

/*###############################################################################################*/
/*//////////////////////////////////////// record path //////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static U8 msAPI_PVR_RecordPathGetWorkingCount(void)
{
    U8 u8PathID;
    U8 u8WorkingCount = 0;

    for(u8PathID = 0; u8PathID < PVR_MAX_RECORD_PATH; u8PathID++)
    {
        if(_PvrRecordPath[u8PathID].bInUse == TRUE)
        {
            u8WorkingCount++;
        }
    }

    return u8WorkingCount;
}

void msAPI_PVR_RecoreReset(_msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    U8 u8PhysicalFltIdx;
    U8 u8VirtualFltIdx;
    U8 u8TempPIDCount[MSAPI_DMX_RECORD_FILTER_NUMBER];
/*
#ifdef PVR_UTOPIA
    BOOL TS_PARALLEL_TYPE = FALSE;

    #if ENABLE_ATSC
        if(IsAtscInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ATSC_OUTPUT;
    #endif
    #if ENABLE_DVBT
        if(IsDVBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBT_OUTPUT;
    #endif
    #if ENABLE_DVBC
        if(IsDVBCInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBC_OUTPUT;
    #endif
    #if ENABLE_DTMB
        if(IsDTMBInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DTMB_OUTPUT;
    #endif
   #if ENABLE_ISDBT
        if(IsISDBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ISDBT_OUTPUT;
    #endif
#endif
*/
    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    for(u8VirtualFltIdx=0; u8VirtualFltIdx<MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
    {
        u8TempPIDCount[u8VirtualFltIdx] = 0;
    }

    for(u8VirtualFltIdx=0; u8VirtualFltIdx<MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
    {
        if(pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if(_pu8RecordPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] == 1)
            {
                msAPI_DMX_Stop(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                msAPI_DMX_Reset(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]); //jack test
              //printf("stop PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
            }
            else
            {
                u8TempPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] ++;
                if(u8TempPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] == _pu8RecordPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]])
                {
                    msAPI_DMX_Stop(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                    msAPI_DMX_Reset(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]); //jack test
                  //printf("stop PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                }
            }
        }
    }

#ifdef PVR_UTOPIA
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
    if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
    {
        MApi_DMX_PvrCA_Stop();
    }
    else
#endif
    {
        MApi_DMX_Pvr_Stop();
    }
#endif
    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        #ifdef PVR_8051
        XBYTE[0x15b7] &= ~0x18;         //<---burst_len Burst length selection in STR2MI MIU write:
                                               //00:    burst length = 8
                                               //01:    burst length = 4
                                               //10,11: burst length = 1
        #else
        {
            U8 u8OrgValue = MDrv_ReadByte(0x15b7);
            u8OrgValue &= ~0x18;
            MDrv_WriteByte(0x15b7,u8OrgValue);
        }
        #endif
    }

    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        #ifdef PVR_8051
        XBYTE[0x15b7] |=  0x18;         //<---burst_len Burst length selection in STR2MI MIU write:
                                               //00:    burst length = 8
                                               //01:    burst length = 4
                                               //10,11: burst length = 1
        #else
        {
            U8 u8OrgValue = MDrv_ReadByte(0x15b7);
            u8OrgValue |= 0x18;
            MDrv_WriteByte(0x15b7,u8OrgValue);
        }
        #endif
    }

    #ifdef PVR_UTOPIA
    {
        DMX_Pvr_info info;
        info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
        info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
        info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
        info.PvrBufSize1 = pstPvrRecordPath->u32BufferLength/2;
        info.pNotify=NULL;

        //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);

        MApi_DMX_Pvr_Open(&info);
    }
    #endif

    for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
    {
        if(pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if(_pu16RecordPID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] == MSAPI_DMX_BYPASS_PID)
            {
                if(pstPvrRecordPath->bRecordAll == FALSE)
                {
                    for(u8PhysicalFltIdx=0; u8PhysicalFltIdx<(MSAPI_DMX_RECORD_FILTER_NUMBER-1); u8PhysicalFltIdx++)
                    {
                        msAPI_DMX_Stop(_pu8RecordFID[u8PhysicalFltIdx]);
                        //printf("stop PID at FID=0x%02bx for PID=0x%04x temporarily \n", _pu8RecordFID[u8PhysicalFltIdx], _pu16RecordPID[u8PhysicalFltIdx]);
                    }
                }

                while(1)
                {
                    if(pstPvrRecordPath->bRecordAll == FALSE)
                    {
                        #ifndef S3PLUS
                        #ifdef PVR_UTOPIA
                        {
                            DMX_Pvr_info info;

                            info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
                            info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
                            info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
                            info.PvrBufSize1=pstPvrRecordPath->u32BufferLength/2;
                            info.pNotify=NULL;
                            //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
                            msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);
                            MApi_DMX_Pvr_Open(&info);
                        }
                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_192);
                        #endif
                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                        #endif
                    }
                    else
                    {
                        #ifndef S3PLUS
                        #ifdef PVR_UTOPIA

                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_188);
                        #endif
                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                        #endif
                    }
                    pstPvrRecordPath->u32BufferReadPointer  = pstPvrRecordPath->u32BufferStart;
                    pstPvrRecordPath->u32BufferWritePointer = pstPvrRecordPath->u32BufferStart;

                    msAPI_DMX_Start(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                    //printf("start PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);

                    msAPI_Timer_Delayms(800);
                    break;

                }

                break;  //do not have to start any other filter
            }
            else    //general recording PID
            {
                if(pstPvrRecordPath->bRecordAll == FALSE)
                {
                    #ifndef S3PLUS
                    #ifdef PVR_UTOPIA

                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_192);
                    #endif
                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                    #endif
                }
                else
                {
                    #ifndef S3PLUS
                    #ifdef PVR_UTOPIA
                    {
                        DMX_Pvr_info info;

                        info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
                        info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
                        info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
                        info.PvrBufSize1 = pstPvrRecordPath->u32BufferLength/2;
                        info.pNotify=NULL;
                        //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
                        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);
                        MApi_DMX_Pvr_Open(&info);
                    }
                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_188);
                    #endif
                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                    #endif
                }
                pstPvrRecordPath->u32BufferReadPointer  = pstPvrRecordPath->u32BufferStart;
                pstPvrRecordPath->u32BufferWritePointer = pstPvrRecordPath->u32BufferStart;
            #ifdef PVR_UTOPIA
            #else
                msAPI_DMX_Start(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                //printf("start PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
            #endif
            msAPI_DMX_Start(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
            }
        }
    }
#ifdef PVR_UTOPIA
    if (pstPvrRecordPath->bRecordAll == FALSE)
    {
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
        if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
        {
            if (DMX_FILTER_STATUS_OK!= MApi_DMX_PvrCA_Start(FALSE))  {printf("<<<MApi_DMX_PvrCA_Start error>>>\n");}
        }
        else
#endif
        {
            if (DMX_FILTER_STATUS_OK!= MApi_DMX_Pvr_Start(FALSE))  {printf("<<<MApi_DMX_Pvr_Start error>>>\n");}
        }
    }
    else
    {
        if (DMX_FILTER_STATUS_OK!= MApi_DMX_PVR_SetPacketMode(FALSE)) {ASSERT(0);} //188 mode
        if (DMX_FILTER_STATUS_OK!= MApi_DMX_Pvr_Start(TRUE))  {ASSERT(0);}
    }
#endif

}

/***************************************************************************************/
_msAPI_PVR_RecordPath * msAPI_PVR_RecordPathOpen(U16 *pu16RecordPathName, enPvrFileMode enFileMode)
{
    U8 u8PathID;
    U8 u8FID;
    U32 u32RecordLengthKB;
    U16 u16RecordTime;

    /*[01-0]pvr part ==================================================================*/
    /*[GROUP0-1]=======================================================================*/
    for(u8PathID = 0; u8PathID < PVR_MAX_RECORD_PATH; u8PathID++)
    {
        if(_PvrRecordPath[u8PathID].bInUse == FALSE)
        {
            _PvrRecordPath[u8PathID].bInUse = TRUE;
            break;
        }
        else if(u8PathID == (PVR_MAX_RECORD_PATH-1))
        {
            return NULL;
        }
    }

    if(u8PathID >= PVR_MAX_RECORD_PATH)
    {
        return NULL;
    }

    u32RecordLastWriteDataSize = 0;
    u32RecordReWriteDataSize = 0;

    _PvrRecordPath[u8PathID].u8LogicalProgrammeNumber   = _u8LPNAccumulator;
    _u8LPNAccumulator ++;
    _PvrRecordPath[u8PathID].u16PlaybackCount= 0;

    /*[01-1]demux part ================================================================*/
    /*[GROUP1-1]=======================================================================*/
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        _PvrRecordPath[u8PathID].u8FilterID[u8FID]      = MSAPI_DMX_INVALID_FLT_ID;
        _PvrRecordPath[u8PathID].u16PID[u8FID]          = MSAPI_DMX_INVALID_PID;
        _PvrRecordPath[u8PathID].enFilterType[u8FID]    = (MSAPI_DMX_FILTER_TYPE) MSAPI_DMX_INVALID_FLT_TYPE;
    }
    _PvrRecordPath[u8PathID].bRecordAll                 = FALSE;

    /*[GROUP1-2]=======================================================================*/
    _PvrRecordPath[u8PathID].u32BufferStart             = 0;
    _PvrRecordPath[u8PathID].u32BufferLength            = 0;
    _PvrRecordPath[u8PathID].u32BufferReadPointer       = 0;
    _PvrRecordPath[u8PathID].u32BufferWritePointer      = 0;

    /*[01-2]file system part ==========================================================*/
    /*[GROUP2-1]=======================================================================*/
    _PvrRecordPath[u8PathID].hWriteFile                 = INVALID_FILE_HANDLE;
    _PvrRecordPath[u8PathID].u32FilePositionKB          = 0;
    _PvrRecordPath[u8PathID].u32FilePosRmnBytes         = 0;
    _PvrRecordPath[u8PathID].u32FileLastPosKB           = 0;
    _PvrRecordPath[u8PathID].u32FileSizeKB              = 0;

    /*[GROUP2-2]=======================================================================*/
    if(enFileMode == E_FILE_MODE_RING)                  //TimeShift usually
    {
        if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
           msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
        {

            U32 tmp=MApp_PVR_TimeShiftGetRecordLengthMB()*1024;

            u32RecordLengthKB = msAPI_PVRFS_GetDriveFreeSpaceMB()*1024;
            if(u32RecordLengthKB > MAX_FAT32_FILE_SIZE_KB)
                u32RecordLengthKB = MAX_FAT32_FILE_SIZE_KB;

            if((u32RecordLengthKB >tmp) && (tmp != 0))
                u32RecordLengthKB=tmp;
        }
        else
        {
        #if (ENABLE_BULK_FILE_SYSTEM)
            u32RecordLengthKB = msAPI_PVRFS_GetTimeShiftRecordLengthMB()*1024;
        #else
            u32RecordLengthKB = 0;
        #endif
        }

        u16RecordTime     = PVR_RECORD_TIME_INFINITE;
    }
    else                                                //Playback  usually
    {
        u32RecordLengthKB = PVR_RECORD_LENGTH_INFINITE;
        u16RecordTime     = PVR_RECORD_TIME_INFINITE;
    }

    _PvrRecordPath[u8PathID].u32FileGapSizeKB           = (u32RecordLengthKB - (PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024))%3;
    _PvrRecordPath[u8PathID].u32FileLimitedSizeKB       = u32RecordLengthKB - _PvrRecordPath[u8PathID].u32FileGapSizeKB;
    _PvrRecordPath[u8PathID].u32FileValidPosStrKB       = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
    _PvrRecordPath[u8PathID].u32FileValidPosEndKB       = 0;
    _PvrRecordPath[u8PathID].u32FileValidDistanceKB     = 0;
    _PvrRecordPath[u8PathID].u32FileValidPeriod         = (U32)u16RecordTime*10;

    /*[GROUP2-3]=======================================================================*/
    _PvrRecordPath[u8PathID].u32FileWriteTime           = 0;
    _PvrRecordPath[u8PathID].u32FileWriteSizeKB         = 0;

    //=================================================================================//
    if(enFileMode == E_FILE_MODE_RING)                  //TimeShift usually
    {
        if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
        {
            _PvrRecordPath[u8PathID].hWriteFile = msAPI_PVRFS_FileCreate(pu16RecordPathName);
        }
        else if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                 msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
        {
            U8 fhander;
            fhander = msAPI_PVRFS_FileOpen(pu16RecordPathName, PVRFS_OPEN_FOR_READ);
            if(fhander != INVALID_FILE_HANDLE)
            {
                msAPI_PVRFS_FileClose(fhander);
                msAPI_PVRFS_FileDelete(pu16RecordPathName);
            }
            msAPI_PVRFS_FileClose(fhander);
            _PvrRecordPath[u8PathID].hWriteFile = msAPI_PVRFS_FileCreate(pu16RecordPathName);
#if (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
            if(MAPP_CIPVR_CIPVRFS_PlaybackFileOpen(pu16RecordPathName,PVRFS_OPEN_FOR_READ) == TRUE)
            {
                MAPP_CIPVR_CIPVRFS_RecordFileClose();
                msAPI_CIPVRFS_FileDelete(pu16RecordPathName);
            }
            MAPP_CIPVR_CIPVRFS_RecordFileCreate(pu16RecordPathName);
#endif
        }
        else
            return NULL;

        if (_PvrRecordPath[u8PathID].hWriteFile == INVALID_FILE_HANDLE)
        {
            _PvrRecordPath[u8PathID].bInUse = FALSE;
            return NULL;
        }
    }
    else                                                //Record    usually
    {
        if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
        {
            if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
                _PvrRecordPath[u8PathID].hWriteFile = msAPI_PVRFS_FileOpen(pu16RecordPathName, PVRFS_OPEN_FOR_WRITE);
            else if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                     msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
            {
                _PvrRecordPath[u8PathID].hWriteFile = msAPI_PVRFS_FileCreate(pu16RecordPathName);
#if (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
                MAPP_CIPVR_CIPVRFS_RecordFileCreate(pu16RecordPathName);
#endif
            }
            if (_PvrRecordPath[u8PathID].hWriteFile == INVALID_FILE_HANDLE)
            {
                _PvrRecordPath[u8PathID].bInUse = FALSE;
                return NULL;
            }
        }
    }
    //=================================================================================//

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/
    /*[GROUP4-1]=======================================================================*/
    _PvrRecordPath[u8PathID].u32RecordedStartSysTime = 0;
    _PvrRecordPath[u8PathID].u32RecordedTime            = 0;
    _PvrRecordPath[u8PathID].u32RecordedPeriod          = 0;
    _PvrRecordPath[u8PathID].u32RecordedTotalTime       = 0;

    /*[GROUP4-2]=======================================================================*/
    _PvrRecordPath[u8PathID].u32PausedTime              = 0;
    _PvrRecordPath[u8PathID].u32PausedPeriod            = 0;

    /*[GROUP4-5]=======================================================================*/
    _PvrRecordPath[u8PathID].u32RecordedKBytes          = 0;
    _PvrRecordPath[u8PathID].u16RecordedMaxRate         = 0;
    _PvrRecordPath[u8PathID].u16RecordedMinRate         = 1000; //<---just for being replaced
    _PvrRecordPath[u8PathID].u16RecordedLstRate         = 0;
    _PvrRecordPath[u8PathID].u16RecordedAvgRate         = 0;
    _PvrRecordPath[u8PathID].u16RecordedErrCount1       = 0;
    _PvrRecordPath[u8PathID].u16RecordedErrCount2       = 0;
    _PvrRecordPath[u8PathID].u16RecordedErrCount3       = 0;

    /*[GROUP4-6]=======================================================================*/
    _PvrRecordPath[u8PathID].u32RecordedStaCheckTime    = 0;

    /*[GROUP4-7]=======================================================================*/
    _PvrRecordPath[u8PathID].bLinkPlayback              = FALSE;

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_RecordPathOpen\n");

    return &_PvrRecordPath[u8PathID];
}

#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)/***************************************************************************************/
static enPvrApiStatus   msAPI_PVR_RecordPathUpdateMetadata(_msAPI_PVR_RecordPath * pstPvrRecordPath, enPvrMetadataUpdateMode enUpdateMode)
{
    U32 u32WriteLength;

    /*[01-0]pvr part ==================================================================*/

    /*[01-1]demux part ================================================================*/
    //============== special treatment for factory mode - record all ==============*/
    if(pstPvrRecordPath->bRecordAll == TRUE)
    {
        return E_PVR_API_STATUS_OK;
    }
    //============== special treatment for factory mode - record all ==============*/

    /*[01-2]file system part ==========================================================*/
    if(enUpdateMode == E_METADATA_UPDATE_FILE)
    {
        {
            U16 u16RemainLength  = sizeof(_msAPI_PVR_RecordPath);
            U8  u8WriteLength;
            U8  u8Segment = 0;
            while(1)
            {
                if(u16RemainLength>=184)
                {
                    u8WriteLength = 184;
                }
                else if(u16RemainLength>0)
                {
                    u8WriteLength = u16RemainLength;
                }
                else
                {
                    break;
                }

            #ifdef PVR_8051
                msAPI_MIU_Copy(msAPI_MIU_XData2SDRAMAddr((U16)pstPvrRecordPath)+184*u8Segment, PVR_WRITE_METADATA_BUFFER_ADR+ pstPvrRecordPath->u8LogicalProgrammeNumber*META_DATA_SIZE +PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
            #else
            #ifdef PVR_UTOPIA
                msAPI_MIU_Copy(_VA2PA((U32)pstPvrRecordPath)+184*u8Segment, ((PVR_WRITE_METADATA_BUFFER_MEMORY_TYPE&MIU1)?PVR_WRITE_METADATA_BUFFER_ADR|MIU_INTERVAL:PVR_WRITE_METADATA_BUFFER_ADR)+ pstPvrRecordPath->u8LogicalProgrammeNumber*META_DATA_SIZE +PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
            #else
                msAPI_MIU_Copy(msAPI_MIU_XData2SDRAMAddr((U32)pstPvrRecordPath)+184*u8Segment, PvrGetWriteMetadataBufAddr()+ pstPvrRecordPath->u8LogicalProgrammeNumber*META_DATA_SIZE +PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
            #endif
            #endif

                u16RemainLength -= u8WriteLength;
                u8Segment++;
            }
        }

        if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
        {
            pstPvrRecordPath->u32FilePositionKB = 0;
            pstPvrRecordPath->u32FilePosRmnBytes= 0;
            msAPI_PVRFS_FileSeek(pstPvrRecordPath->hWriteFile, msAPI_PVR_KToLongLong(pstPvrRecordPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN);
            u32WriteLength = msAPI_PVRFS_FileWrite(pstPvrRecordPath->hWriteFile, PvrGetWriteMetadataBufAddr(), PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE);    //3.0K
            pstPvrRecordPath->u32FilePositionKB = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
        }
    }
    else
    {
        {
            U16 u16RemainLength  = sizeof(_msAPI_PVR_RecordPath);
            U8  u8WriteLength;
            U8  u8Segment = 0;
            while(1)
            {
                if(u16RemainLength>=184)
                {
                    u8WriteLength = 184;
                }
                else if(u16RemainLength>0)
                {
                    u8WriteLength = u16RemainLength;
                }
                else
                {
                    break;
                }

            #ifdef PVR_8051
                msAPI_MIU_Copy(msAPI_MIU_XData2SDRAMAddr((U16)pstPvrRecordPath)+184*u8Segment, PVR_READ_METADATA_BUFFER_ADR+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(PVR_READ_METADATA_BUFFER_ADR+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U16)&_PvrRecordMeataData)+184*u8Segment, u8WriteLength, MIU_SDRAM2SDRAM);
            #else
            #ifdef PVR_UTOPIA
                msAPI_MIU_Copy(_VA2PA((U32)pstPvrRecordPath)+184*u8Segment, (((PVR_READ_METADATA_BUFFER_MEMORY_TYPE&MIU1)?PVR_READ_METADATA_BUFFER_ADR|MIU_INTERVAL:PVR_READ_METADATA_BUFFER_ADR))+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy((((PVR_READ_METADATA_BUFFER_MEMORY_TYPE&MIU1)?PVR_READ_METADATA_BUFFER_ADR|MIU_INTERVAL:PVR_READ_METADATA_BUFFER_ADR))+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, _VA2PA((U32)&_PvrRecordMeataData)+184*u8Segment, u8WriteLength, MIU_SDRAM2SDRAM);
            #else
                msAPI_MIU_Copy(msAPI_MIU_XData2SDRAMAddr((U32)pstPvrRecordPath)+184*u8Segment, PvrGetReadMetadataBufAddr()+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(PvrGetReadMetadataBufAddr()+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U32)&_PvrRecordMeataData)+184*u8Segment, u8WriteLength, MIU_SDRAM2SDRAM);
            #endif
            #endif

                u16RemainLength -= u8WriteLength;
                u8Segment++;
            }
        }
        u32WriteLength = 0;
        //pstPvrRecordPath->u32FilePositionKB = pstPvrRecordPath->u32FilePositionKB;  //not changed
    }

    #if 0   //=========================================================================//
    {
        U16 u16ByteNo;
        printf("==================================================================\n");
        printf("write_metadata_record_path   = %04lu\n", u32WriteLength);
        printf("==================================================================\n");
        MDrv_Sys_SetXdataWindow1Base(PVR_WRITE_METADATA_BUFFER_ADR/4096);
        for(u16ByteNo=0; u16ByteNo<META_DATA_SIZE; u16ByteNo++)
        {
            printf("%02bx", _pu8MetadataForWrite[u16ByteNo]);
            if(u16ByteNo%32==31)
                printf("##\n");
        }
        MDrv_Sys_ReleaseXdataWindow1();
        printf("==================================================================\n");
    }
    #endif  //=========================================================================//

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_RecordPathUpdateMetadata\n");

    return E_PVR_API_STATUS_OK;
}
#endif

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_RecordPathSet(_msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    msAPI_PVR_SetRecordCAPVR(pstPvrRecordPath->enEncryptionType);
/*
#ifdef PVR_UTOPIA
    BOOL TS_PARALLEL_TYPE = FALSE;

    #if ENABLE_ATSC
        if(IsAtscInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ATSC_OUTPUT;
    #endif
    #if ENABLE_DVBT
        if(IsDVBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBT_OUTPUT;
    #endif
    #if ENABLE_DVBC
        if(IsDVBCInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBC_OUTPUT;
    #endif
    #if ENABLE_DTMB
        if(IsDTMBInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DTMB_OUTPUT;
    #endif
   #if ENABLE_ISDBT
        if(IsISDBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ISDBT_OUTPUT;
    #endif

#endif
*/
    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        if(pstPvrRecordPath->bRecordAll == FALSE)
        {
        #ifndef S3PLUS
            #ifdef PVR_UTOPIA
            {
                DMX_Pvr_info info;
                DMX_FILTER_STATUS DemuxStatus;
                //MApi_DMX_Init();
                //MApi_DMX_SetOwner(16, 31, TRUE);

                //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
                msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);

                if (DemuxStatus !=DMX_FILTER_STATUS_OK) {ASSERT(0);}
                info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
                info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
                info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
                info.PvrBufSize1 = pstPvrRecordPath->u32BufferLength/2;
                info.pNotify=NULL;

                if (DMX_FILTER_STATUS_OK!= MApi_DMX_Pvr_Open(&info)) {ASSERT(0);}
                if (DMX_FILTER_STATUS_OK!= MApi_DMX_PVR_SetPacketMode(TRUE)) {ASSERT(0);}  //192 mode
            }
            #else
                msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_192);
            #endif
        #else
            msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
        #endif
        }
        else
        {
        #ifndef S3PLUS
            #ifdef PVR_UTOPIA
            {
                DMX_Pvr_info info;
                DMX_FILTER_STATUS DemuxStatus;
                //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
                msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);

                if (DemuxStatus !=DMX_FILTER_STATUS_OK) {ASSERT(0);}
                info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
                info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
                info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
                info.PvrBufSize1 = pstPvrRecordPath->u32BufferLength/2;
                info.pNotify=NULL;

                if (DMX_FILTER_STATUS_OK!= MApi_DMX_Pvr_Open(&info)) {ASSERT(0);}
                if (DMX_FILTER_STATUS_OK!= MApi_DMX_PVR_SetPacketMode(FALSE)) {ASSERT(0);} //188 mode
            }
            #else
                msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_188);
            #endif
        #else
            msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
        #endif
        }
    }

    /*[GROUP1-2]=======================================================================*/
    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        pstPvrRecordPath->u32BufferReadPointer  = pstPvrRecordPath->u32BufferStart;
        pstPvrRecordPath->u32BufferWritePointer = pstPvrRecordPath->u32BufferStart;
    }

    /*[01-2]file system part ==========================================================*/

    //====================== time stamp / ts header checking ==========================//
    #ifndef S3PLUS
    if(pstPvrRecordPath->bRecordAll == FALSE)
    {
        if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
        {
            #ifdef PVR_UTOPIA
            MApi_DMX_Pvr_SetRecordStamp(0);
            #else
            msAPI_DMX_SetRecordStamp(0);
            #endif
        }
    }
    #endif
    //====================== time stamp / ts header checking ==========================//

    /*[01-3]media format ==============================================================*/
    /*[GROUP3-1]=======================================================================*/
    pstPvrRecordPath->enVideoType = msAPI_Player_VideoGetType();

    /*[GROUP3-2]=======================================================================*/
    pstPvrRecordPath->enAudioType   = msAPI_Player_AudioGetType();
    pstPvrRecordPath->enAdAudioType = msAPI_Player_AdAudioGetType();


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_RecordPathSet\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_RecordPathAddPID(_msAPI_PVR_RecordPath * pstPvrRecordPath, U16 u16PID, MSAPI_DMX_FILTER_TYPE enFltType)
{
    U8 u8PhysicalFltIdx;
    U8 u8VirtualFltIdx;

    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    /*[GROUP1-1]=======================================================================*/
    if(u16PID == MSAPI_DMX_INVALID_PID)
    {
      //printf("Invalid PID\n");
        return E_PVR_API_STATUS_INVALID_PID;
    }

    //============== special treatment for factory mode - record all ==============*/
    if(pstPvrRecordPath->bRecordAll == TRUE)
    {
        BOOLEAN bDupPID = FALSE;

        u8PhysicalFltIdx = 0;   //always use filter index 0

        if((_pu16RecordPID[u8PhysicalFltIdx] == MSAPI_DMX_BYPASS_PID) && (_pu8RecordFID[u8PhysicalFltIdx] != MSAPI_DMX_INVALID_FLT_ID))
        {
           // if(enFltType == MSAPI_DMX_FILTER_TYPE_SUBTITLE)     //avoid redudant subtitle pid
            {
                for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                {
                    if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
                    {
                        if(pstPvrRecordPath->u16PID[u8VirtualFltIdx] == u16PID)
                        {
                            if(pstPvrRecordPath->enFilterType[u8VirtualFltIdx] == enFltType)
                            {
                                bDupPID = TRUE;
                              //printf("Du5 PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                                break;
                            }
                        }
                    }
                }
            }

            if(bDupPID == FALSE)
            {
                for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                {
                    if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == MSAPI_DMX_INVALID_FLT_ID)
                    {
                        pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]   = u8PhysicalFltIdx;
                        pstPvrRecordPath->u16PID[u8VirtualFltIdx]       = u16PID;
                        pstPvrRecordPath->enFilterType[u8VirtualFltIdx] = enFltType;

                        _pu8RecordPIDCount[u8PhysicalFltIdx]++;

                      //printf("Du6 PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                        break;
                    }
                }
            }
        }
        else
        {
            _pu16RecordPID[u8PhysicalFltIdx] = MSAPI_DMX_BYPASS_PID; //record_all
        #ifdef PVR_UTOPIA
            {
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
                if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
                {  printf("eDmxFlow = DMX_FLOW_PVR nnn2 %d  \n",pstPvrRecordPath->enEncryptionType);
                    if (DMX_FILTER_STATUS_OK != MApi_DMX_PvrCA_Pid_Open(_pu16RecordPID[u8PhysicalFltIdx], &(_pu8RecordFID[u8PhysicalFltIdx]))) {ASSERT(0);}
                }
                else
#endif
                {
                    if (DMX_FILTER_STATUS_OK != MApi_DMX_Pvr_Pid_Open(_pu16RecordPID[u8PhysicalFltIdx], &(_pu8RecordFID[u8PhysicalFltIdx]))) {ASSERT(0);}
                }
            }
            //printf("MApi_DMX_Pvr_Pid_Open2[%d]=%d\n",u8PhysicalFltIdx,_pu16RecordPID[u8PhysicalFltIdx]);
         #else
            _pu8RecordFID[u8PhysicalFltIdx]  = msAPI_DMX_Open(MSAPI_DMX_FILTER_TYPE_RECORD);
        #endif
        if (_pu8RecordFID[u8PhysicalFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
            {

            #ifdef PVR_UTOPIA
            #else
                msAPI_DMX_SetPid(_pu8RecordFID[u8PhysicalFltIdx], _pu16RecordPID[u8PhysicalFltIdx]);
                msAPI_DMX_Reset(_pu8RecordFID[u8PhysicalFltIdx]);
            #endif
                for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                {
                    if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == MSAPI_DMX_INVALID_FLT_ID)
                    {
                        pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]   = u8PhysicalFltIdx;
                        pstPvrRecordPath->u16PID[u8VirtualFltIdx]       = u16PID;
                        pstPvrRecordPath->enFilterType[u8VirtualFltIdx] = enFltType;

                        _pu8RecordPIDCount[u8PhysicalFltIdx]++;
                      //printf("All PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                        break;
                    }
                    else if(u8VirtualFltIdx == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))
                    {
                      //printf("No More Filter Available for Storing \n");
                        break;
                    }
                }
            }
        }

        return E_PVR_API_STATUS_OK;
    }
    //============== special treatment for factory mode - record all ==============*/

    #define ENABLE_RECORD_ALL   FALSE
    {
        BOOLEAN bDupPID = FALSE;

        for (u8PhysicalFltIdx = 0; u8PhysicalFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8PhysicalFltIdx++)
        {
            if (_pu8RecordFID[u8PhysicalFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
            {
                if(_pu16RecordPID[u8PhysicalFltIdx] == u16PID)
                {
                   // if(enFltType  == MSAPI_DMX_FILTER_TYPE_SUBTITLE)     //avoid redudant subtitle pid
                    {
                        for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                        {
                            if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
                            {
                                if(pstPvrRecordPath->u16PID[u8VirtualFltIdx] == u16PID)
                                {
                                    if(pstPvrRecordPath->enFilterType[u8VirtualFltIdx] == enFltType)
                                    {
                                        bDupPID = TRUE;
                                      //printf("Du1 PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                                        break;
                                    }
                                }
                            }
                        }

                        if(bDupPID == TRUE)
                        {
                            break;
                        }
                    }

                    for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                    {
                        if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == MSAPI_DMX_INVALID_FLT_ID)
                        {
                            pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]   = u8PhysicalFltIdx;
                            pstPvrRecordPath->u16PID[u8VirtualFltIdx]       = u16PID;
                            pstPvrRecordPath->enFilterType[u8VirtualFltIdx] = enFltType;

                            _pu8RecordPIDCount[u8PhysicalFltIdx]++;
                            bDupPID = TRUE;
                          //printf("Du2 PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                            break;
                        }
                    }
                }

                #if ENABLE_RECORD_ALL
                else if (u8PhysicalFltIdx == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))
                {
                    if(_pu16RecordPID[u8PhysicalFltIdx] == MSAPI_DMX_BYPASS_PID)
                    {
                        //if(enFltType == MSAPI_DMX_FILTER_TYPE_SUBTITLE) //avoid redudant subtitle pid
                        {
                            for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                            {
                                if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
                                {
                                    if(pstPvrRecordPath->u16PID[u8VirtualFltIdx] == u16PID)
                                    {
                                        if(pstPvrRecordPath->enFilterType[u8VirtualFltIdx] == enFltType)
                                        {
                                            bDupPID = TRUE;
                                          //printf("Du3 PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                                            break;
                                        }
                                    }
                                }
                            }

                            if(bDupPID == TRUE)
                            {
                                break;
                            }
                        }

                        for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                        {
                            if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == MSAPI_DMX_INVALID_FLT_ID)
                            {
                                pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]   = u8PhysicalFltIdx;
                                pstPvrRecordPath->u16PID[u8VirtualFltIdx]       = u16PID;
                                pstPvrRecordPath->enFilterType[u8VirtualFltIdx] = enFltType;

                                _pu8RecordPIDCount[u8PhysicalFltIdx]++;
                                bDupPID = TRUE;
                              //printf("Du4 PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                                break;
                            }
                        }
                    }
                }
                #endif
            }

            if(bDupPID == TRUE)
            {
                break;
            }
        }

        if(bDupPID == FALSE)
        {
            #if ENABLE_RECORD_ALL
            for (u8PhysicalFltIdx = 0; u8PhysicalFltIdx < (MSAPI_DMX_RECORD_FILTER_NUMBER-1); u8PhysicalFltIdx++)
            #else
            for (u8PhysicalFltIdx = 0; u8PhysicalFltIdx < (MSAPI_DMX_RECORD_FILTER_NUMBER-0); u8PhysicalFltIdx++)
            #endif
            {
                if (_pu8RecordFID[u8PhysicalFltIdx] == MSAPI_DMX_INVALID_FLT_ID)
                {
                    _pu16RecordPID[u8PhysicalFltIdx] = u16PID;
                #ifdef PVR_UTOPIA
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
                    if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
                    {        printf("eDmxFlow = DMX_FLOW_PVR nnn3 %d  \n",pstPvrRecordPath->enEncryptionType);
                         MApi_DMX_PvrCA_Pid_Open(_pu16RecordPID[u8PhysicalFltIdx], &(_pu8RecordFID[u8PhysicalFltIdx]));
                    }
                    else
#endif
                    {
                         MApi_DMX_Pvr_Pid_Open(_pu16RecordPID[u8PhysicalFltIdx], &(_pu8RecordFID[u8PhysicalFltIdx]));
                    }
                    msAPI_DMX_StartFilter(_pu16RecordPID[u8PhysicalFltIdx], enFltType|MSAPI_DMX_FILTER_SOURCE_TYPE_FILE, &(_pu8RecordFID[u8PhysicalFltIdx]));
                    printf("[PVR][Record] PID=%u, FType=%u, FID=%u \n", _pu16RecordPID[u8PhysicalFltIdx], enFltType, _pu8RecordFID[u8PhysicalFltIdx]);
                    //printf("MApi_DMX_Pvr_Pid_Open2[%d]=%d\n",u8PhysicalFltIdx,_pu16RecordPID[u8PhysicalFltIdx]);
                #else
                    _pu8RecordFID[u8PhysicalFltIdx]  = msAPI_DMX_Open(MSAPI_DMX_FILTER_TYPE_RECORD);
                #endif
                    if (_pu8RecordFID[u8PhysicalFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
                    {
                    #ifdef PVR_UTOPIA
                    #else
                        msAPI_DMX_SetPid(_pu8RecordFID[u8PhysicalFltIdx], _pu16RecordPID[u8PhysicalFltIdx]);
                        msAPI_DMX_Reset(_pu8RecordFID[u8PhysicalFltIdx]);
                    #endif

                        for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                        {
                            if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == MSAPI_DMX_INVALID_FLT_ID)
                            {
                                pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]   = u8PhysicalFltIdx;
                                pstPvrRecordPath->u16PID[u8VirtualFltIdx]       = u16PID;
                                pstPvrRecordPath->enFilterType[u8VirtualFltIdx] = enFltType;

                                _pu8RecordPIDCount[u8PhysicalFltIdx]++;
                              //printf("Add PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                                break;
                            }
                            else if(u8VirtualFltIdx == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))
                            {
                              //printf("No More Filter Available for Storing \n");
                                break;
                            }
                        }

                        if(u8VirtualFltIdx >= MSAPI_DMX_RECORD_FILTER_NUMBER)
                        {
                            break;
                        }

                        if(u8VirtualFltIdx == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))               //no filter
                        {
                            break;
                        }

                        if(pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == u8PhysicalFltIdx)  //link well
                        {
                            break;
                        }
                    }
                }

                #if ENABLE_RECORD_ALL
                else if(u8PhysicalFltIdx == (MSAPI_DMX_RECORD_FILTER_NUMBER-2))
                {
                    u8PhysicalFltIdx = MSAPI_DMX_RECORD_FILTER_NUMBER-1;

                    _pu16RecordPID[u8PhysicalFltIdx] = MSAPI_DMX_BYPASS_PID; //record_all
                #ifdef PVR_UTOPIA
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
                    if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
                    {  printf("eDmxFlow = DMX_FLOW_PVR nnn4 %d  \n",pstPvrRecordPath->enEncryptionType);
                        MApi_DMX_PvrCA_Pid_Open(_pu16RecordPID[u8PhysicalFltIdx], &(_pu8RecordFID[u8PhysicalFltIdx]));
                    }
                    else
#endif
                    {
                        MApi_DMX_Pvr_Pid_Open(_pu16RecordPID[u8PhysicalFltIdx], &(_pu8RecordFID[u8PhysicalFltIdx]));
                    }
                    //printf("MApi_DMX_Pvr_Pid_Open[%d]3=%d\n",u8PhysicalFltIdx,_pu16RecordPID[u8PhysicalFltIdx]);
                #else
                    _pu8RecordFID[u8PhysicalFltIdx]  = msAPI_DMX_Open(MSAPI_DMX_FILTER_TYPE_RECORD);
                #endif
                    if (_pu8RecordFID[u8PhysicalFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
                    {

                    #ifdef PVR_UTOPIA
                    #else
                        msAPI_DMX_SetPid(_pu8RecordFID[u8PhysicalFltIdx], _pu16RecordPID[u8PhysicalFltIdx]);
                        msAPI_DMX_Reset(_pu8RecordFID[u8PhysicalFltIdx]);
                    #endif

                        for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
                        {
                            if (pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == MSAPI_DMX_INVALID_FLT_ID)
                            {
                                pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]   = u8PhysicalFltIdx;
                                pstPvrRecordPath->u16PID[u8VirtualFltIdx]       = u16PID;
                                pstPvrRecordPath->enFilterType[u8VirtualFltIdx] = enFltType;

                                _pu8RecordPIDCount[u8PhysicalFltIdx]++;
                              //printf("All PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                                break;
                            }
                            else if(u8VirtualFltIdx == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))
                            {
                              //printf("No More Filter Available for Storing \n");
                                break;
                            }
                        }

                        if(u8VirtualFltIdx >= MSAPI_DMX_RECORD_FILTER_NUMBER)
                        {
                            break;
                        }

                        if(u8VirtualFltIdx == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))               //no filter
                        {
                            break;
                        }

                        if(pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] == u8PhysicalFltIdx)   //link well
                        {
                            break;
                        }
                    }
                    break;
                }
                #endif
            }
        }
    }

    /*[01-2]file system part ==========================================================*/


    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_RecordPathAddPID\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_RecordPathStart(_msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    U8 u8PhysicalFltIdx;
    U8 u8VirtualFltIdx;
#if 0//def PVR_UTOPIA
    BOOL TS_PARALLEL_TYPE = FALSE;

    #if ENABLE_ATSC
        if(IsAtscInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ATSC_OUTPUT;
    #endif
    #if ENABLE_DVBT
        if(IsDVBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBT_OUTPUT;
    #endif
    #if ENABLE_DVBC
        if(IsDVBCInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DVBC_OUTPUT;
    #endif
    #if ENABLE_DTMB
        if(IsDTMBInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_DTMB_OUTPUT;
    #endif
   #if ENABLE_ISDBT
        if(IsISDBTInUse())
            TS_PARALLEL_TYPE = TS_PARALLEL_ISDBT_OUTPUT;
    #endif

#endif

    /*[01-0]pvr part ==================================================================*/

    /*[01-1]demux part ================================================================*/
    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        #ifdef PVR_8051
        XBYTE[0x15b7] |=  0x18;         //<---burst_len Burst length selection in STR2MI MIU write:
                                               //00:    burst length = 8
                                               //01:    burst length = 4
                                               //10,11: burst length = 1
        #else
        {
            U8 u8OrgValue = MDrv_ReadByte(0x15b7);
            u8OrgValue |= 0x18;
            MDrv_WriteByte(0x15b7,u8OrgValue);
        }
        #endif
    }

    #ifdef PVR_UTOPIA
    {
        DMX_Pvr_info info;

        info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
        info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
        info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
        info.PvrBufSize1 = pstPvrRecordPath->u32BufferLength/2;
        info.pNotify=NULL;

        //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);

        MApi_DMX_Pvr_Open(&info);
    }
    #endif

    for (u8VirtualFltIdx = 0; u8VirtualFltIdx < MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
    {
        if(pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if(_pu16RecordPID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] == MSAPI_DMX_BYPASS_PID)
            {
                if(pstPvrRecordPath->bRecordAll == FALSE)
                {
                    for(u8PhysicalFltIdx=0; u8PhysicalFltIdx<(MSAPI_DMX_RECORD_FILTER_NUMBER-1); u8PhysicalFltIdx++)
                    {
                        msAPI_DMX_Stop(_pu8RecordFID[u8PhysicalFltIdx]);
                        //printf("stop PID at FID=0x%02bx for PID=0x%04x temporarily \n", _pu8RecordFID[u8PhysicalFltIdx], _pu16RecordPID[u8PhysicalFltIdx]);
                    }

                    if(pstPvrRecordPath->u32FilePositionKB%3)
                    {
                        U32 u32WriteLength = (3-pstPvrRecordPath->u32FilePositionKB%3)*1024;
                        u32WriteLength = msAPI_PVRFS_FileWrite(pstPvrRecordPath->hWriteFile,  pstPvrRecordPath->u32BufferReadPointer,u32WriteLength);
                        pstPvrRecordPath->u32FilePositionKB+=u32WriteLength/1024;
                        pstPvrRecordPath->u32FileValidPosEndKB = pstPvrRecordPath->u32FilePositionKB;
                    }
                }

                while(1)
                {
                    if(pstPvrRecordPath->bRecordAll == FALSE)
                    {
                        #ifndef S3PLUS
                        #ifdef PVR_UTOPIA
                        {
                            DMX_Pvr_info info;

                            info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
                            info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
                            info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
                            info.PvrBufSize1=pstPvrRecordPath->u32BufferLength/2;
                            info.pNotify=NULL;

                            //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
                            msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);

                            MApi_DMX_Pvr_Open(&info);
                        }
                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_192);
                        #endif
                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                        #endif
                    }
                    else
                    {
                        #ifndef S3PLUS
                        #ifdef PVR_UTOPIA

                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_188);
                        #endif
                        #else
                        msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                        #endif
                    }
                    pstPvrRecordPath->u32BufferReadPointer  = pstPvrRecordPath->u32BufferStart;
                    pstPvrRecordPath->u32BufferWritePointer = pstPvrRecordPath->u32BufferStart;

                    msAPI_DMX_Start(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                    //printf("start PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);

                    msAPI_Timer_Delayms(800);

                    #if 0
                    {
                        U32 u32BufferAlignPacket;
                        #ifdef PVR_8051
                        U16 u16Segment;
                        U16 u16Offset;
                        #endif
                        //read_pointer ##====================
                        u32BufferAlignPacket = pstPvrRecordPath->u32BufferReadPointer-pstPvrRecordPath->u32BufferStart;
                        u32BufferAlignPacket = ALIGNMINREAD(u32BufferAlignPacket);
                        u32BufferAlignPacket+= pstPvrRecordPath->u32BufferStart;
                        #ifdef PVR_8051
                        u16Segment = u32BufferAlignPacket/4096;
                        u16Offset  = u32BufferAlignPacket%4096;
                        MDrv_Sys_SetXdataWindow1Base(u16Segment);
                        if(XBYTE[u16Offset+0xf004] != 0x47)
                        #else
                        if(*(U8 *)(u32BufferAlignPacket+4) != 0x47)
                        #endif
                        {
                          //printf("record packet error-1 at buff_pos=0x%08lx \n", u32BufferAlignPacket);
                        }
                        else
                        {
                          //printf("time_stamp_file   =%02bx %02bx %02bx %02bx \n", XBYTE[u16Offset+0xf000], XBYTE[u16Offset+0xf001], XBYTE[u16Offset+0xf002], XBYTE[u16Offset+0xf003]);
                            break;
                        }
                        //buffer_start ##====================
                        #ifdef PVR_8051
                        u16Segment = pstPvrRecordPath->u32BufferStart/4096;
                        u16Offset  = pstPvrRecordPath->u32BufferStart%4096;
                        MDrv_Sys_SetXdataWindow1Base(u16Segment);
                        if(XBYTE[u16Offset+0xf004] != 0x47)
                        #else
                        if(*(U8 *)(pstPvrRecordPath->u32BufferStart+4) != 0x47)
                        #endif
                        {
                          //printf("record packet error-2 at buff_pos=0x%08lx \n", pstPvrRecordPath->u32BufferStart);
                        }
                        else
                        {
                          //printf("time_stamp_file   =%02bx %02bx %02bx %02bx \n", XBYTE[u16Offset+0xf000], XBYTE[u16Offset+0xf001], XBYTE[u16Offset+0xf002], XBYTE[u16Offset+0xf003]);
                            break;
                        }
                        #ifdef PVR_8051
                        MDrv_Sys_ReleaseXdataWindow1();
                        #endif
                        // ================================##
                    }

                    msAPI_DMX_Stop(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                  //printf("stop PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);

                    #else
                    break;
                    #endif
                }

                break;  //do not have to start any other filter
            }
            else    //general recording PID
            {
                if(pstPvrRecordPath->bRecordAll == FALSE)
                {
                    #ifndef S3PLUS
                    #ifdef PVR_UTOPIA

                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_192);
                    #endif
                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                    #endif
                }
                else
                {
                    #ifndef S3PLUS
                    #ifdef PVR_UTOPIA
                    {
                        DMX_Pvr_info info;

                        info.pPvrBuf0 = _VA2PA(pstPvrRecordPath->u32BufferStart);
                        info.PvrBufSize0 = pstPvrRecordPath->u32BufferLength/2;
                        info.pPvrBuf1 = info.pPvrBuf0 + info.PvrBufSize0;
                        info.PvrBufSize1 = pstPvrRecordPath->u32BufferLength/2;
                        info.pNotify=NULL;
                        //msAPI_Tuner_Serial_Control(TS_PARALLEL_TYPE ? TRUE : FALSE,TRUE);
                        msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_PVR_REC);
                        MApi_DMX_Pvr_Open(&info);
                    }
                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength, MSAPI_DMX_DATAPATH_PACKETMODE_188);
                    #endif
                    #else
                    msAPI_DMX_SetRecordBuffer(pstPvrRecordPath->u32BufferStart, pstPvrRecordPath->u32BufferLength);
                    #endif
                }
                pstPvrRecordPath->u32BufferReadPointer  = pstPvrRecordPath->u32BufferStart;
                pstPvrRecordPath->u32BufferWritePointer = pstPvrRecordPath->u32BufferStart;
            #ifdef PVR_UTOPIA
            #else
                msAPI_DMX_Start(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                //printf("start PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
            #endif
            msAPI_DMX_Start(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
            }
        }
    }
    /*[01-2]file system part ==========================================================*/
#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
    msAPI_PVR_RecordPathUpdateMetadata(pstPvrRecordPath, E_METADATA_UPDATE_FILE);         //Record store metadata after use
#endif

#ifdef PVR_UTOPIA
    if (pstPvrRecordPath->bRecordAll == FALSE)
    {
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
        if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
        {
            if (DMX_FILTER_STATUS_OK!= MApi_DMX_PvrCA_Start(FALSE))  {printf("<<<MApi_DMX_PvrCA_Start error>>>\n");}
        }
        else
#endif
        {
            if (DMX_FILTER_STATUS_OK!= MApi_DMX_Pvr_Start(FALSE))  {printf("<<<MApi_DMX_Pvr_Start error>>>\n");}
        }
    }
    else
    {
        if (DMX_FILTER_STATUS_OK!= MApi_DMX_PVR_SetPacketMode(FALSE)) {ASSERT(0);} //188 mode
        if (DMX_FILTER_STATUS_OK!= MApi_DMX_Pvr_Start(TRUE))  {ASSERT(0);}
    }
#endif
    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/
    /*[GROUP4-1]=======================================================================*/
    pstPvrRecordPath->u32RecordedStartSysTime = MApp_GetLocalSystemTime();
    pstPvrRecordPath->u32RecordedTime  = msAPI_Timer_GetTime0();
    pstPvrRecordPath->u32RecordedTime /=1000;   //one second alignment
    pstPvrRecordPath->u32RecordedTime *=1000;

    /*[GROUP4-6]=======================================================================*/
    pstPvrRecordPath->u32RecordedStaCheckTime = msAPI_Timer_GetTime0() + WRITE_CHECK_START;  //start from 1st sec

    /*[02]global variables ============================================================*/
    //#ifdef S3PLUS
    _bAlignSyncByte = TRUE;
    //#endif
  //printf("msAPI_PVR_RecordPathStart\n");

    return E_PVR_API_STATUS_OK;
}

static BOOL _PVR_GetProgrammeRcdPath(U8 fhandler, int prognum, _msAPI_PVR_RecordPath *pRcdPath)
{
    {
        LongLong llFileLen=msAPI_PVRFS_FileLength(fhandler),llSeekPos;
        U16 u16RemainLength  = sizeof(_msAPI_PVR_RecordPath);
        U8  u8RdLength;
        U8  u8Segment = 0;
        U8  pTempBuf[PVR_TS_PACKET_SIZE];
        llSeekPos.Hi=0;
        llSeekPos.Lo=(prognum*META_DATA_SIZE);
        if( (llFileLen.Hi==0 && llFileLen.Lo<((prognum+1)*META_DATA_SIZE))
            || FALSE==msAPI_PVRFS_FileSeek(fhandler,llSeekPos,PVRFS_SEEK_OPTION_FROM_BEGIN))
            return FALSE;
        while(1)
        {
            if( u16RemainLength>=(PVR_TS_PACKET_SIZE-PVR_TS_PACKET_HEADER_SIZE) )
            {
                u8RdLength = (PVR_TS_PACKET_SIZE-PVR_TS_PACKET_HEADER_SIZE);
            }
            else if(u16RemainLength>0)
            {
                u8RdLength = u16RemainLength;
            }
            else
            {
                break;
            }
            if(PVR_TS_PACKET_SIZE!=msAPI_PVRFS_FileRead(fhandler, (U32)pTempBuf, PVR_TS_PACKET_SIZE))
                return FALSE;

            memcpy((void *)((U32)(pRcdPath)+(PVR_TS_PACKET_SIZE-PVR_TS_PACKET_HEADER_SIZE)*u8Segment),
                    (void *)(pTempBuf+PVR_TS_PACKET_HEADER_SIZE),
                    u8RdLength);

            u16RemainLength -= u8RdLength;
            u8Segment++;
        }
        return TRUE;
    }
}
enPvrApiStatus msAPI_PVR_GetMetaData(U16 *pFileName, _msAPI_PVR_RecordPath *pMetaData)
{
    enPvrApiStatus enRetStatus=E_PVR_API_STATUS_ERROR;
    if( NULL==pFileName || NULL==pMetaData)
    {
        return E_PVR_API_STATUS_ERROR;
    }
    U8 fhander;
    fhander = msAPI_PVRFS_FileOpen(pFileName, PVRFS_OPEN_FOR_READ);
    if( fhander == INVALID_FILE_HANDLE )
    {
        return E_PVR_API_STATUS_ERROR;
    }
    if(TRUE==_PVR_GetProgrammeRcdPath(fhander,0,pMetaData))
    {
        enRetStatus=E_PVR_API_STATUS_OK;
    }
    msAPI_PVRFS_FileClose(fhander);
    return enRetStatus;
}
BOOL msAPI_PVR_IsMStarPVRFile(U16 *pFileName)
{
    BOOL bMStarPVRFile=TRUE;
    _msAPI_PVR_RecordPath MetaData;
    int i;
    if(E_PVR_API_STATUS_OK==msAPI_PVR_GetMetaData(pFileName,&MetaData))
    {
        for(i=0;i<MSAPI_DMX_RECORD_FILTER_NUMBER;i++)
        {
            if(MetaData.u16PID[i]>MSAPI_DMX_INVALID_PID)
            {
                bMStarPVRFile=FALSE;
            }
            else if( ( (MetaData.u16PID[i]==MSAPI_DMX_INVALID_PID) || (MetaData.enFilterType[i]==MSAPI_DMX_INVALID_FLT_TYPE) || (MetaData.u8FilterID[i]==MSAPI_DMX_INVALID_FLT_ID) )
                    &&( (MetaData.u16PID[i]!=MSAPI_DMX_INVALID_PID) || (MetaData.enFilterType[i]!=MSAPI_DMX_INVALID_FLT_TYPE) || (MetaData.u8FilterID[i]!=MSAPI_DMX_INVALID_FLT_ID) )
                    )
            {
                bMStarPVRFile=FALSE;
            }
            else if(MetaData.enFilterType[i]>MSAPI_DMX_INVALID_FLT_TYPE)
            {
                bMStarPVRFile=FALSE;
            }
            else if((MetaData.u16PID[i]==PID_PAT) && (MetaData.enFilterType[i]!=MSAPI_DMX_FILTER_TYPE_SECTION_1K))
            {
                bMStarPVRFile=FALSE;
            }
        }
    }
    else
    {
        bMStarPVRFile=FALSE;
    }
    return bMStarPVRFile;
}

#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
void _PVR_AESDMAEncryptDecrypt(U32 u32Address, U32 u32Length, enPvrAESDMAMode eMode);
#endif
enPvrApiStatus msAPI_PVR_AESDMAEncryptDecrypt(U32 u32VirAddress, U32 u32Length, enPvrAESDMAMode eMode)
{
    UNUSED(u32VirAddress);
    UNUSED(u32Length);
    UNUSED(eMode);
    #if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
    _PVR_AESDMAEncryptDecrypt(u32VirAddress,u32Length,eMode);
    #endif
    return E_PVR_API_STATUS_OK;
}

enPvrEncryptType msAPI_PVR_GetEncryptType(FileEntry *pFileEntry)
{
    U8 u8fHandler;
    U32 u32ReadLength;

    u8fHandler = msAPI_FCtrl_FileOpen(pFileEntry, OPEN_MODE_FOR_READ);
    if( u8fHandler == INVALID_FILE_HANDLE)
    {
        return E_PVR_ENCRYPTION_NONE;
    }
    else
    {
        LongLong llSeekLength;
        _msAPI_PVR_RecordPath tmpPvrRecordMeataData;

        llSeekLength.Lo = 0;
        llSeekLength.Hi = 0;
        msAPI_PVRFS_FileSeek(u8fHandler, llSeekLength, PVRFS_SEEK_OPTION_FROM_BEGIN);
        u32ReadLength = msAPI_PVRFS_FileRead(u8fHandler, PvrGetReadMetadataBufAddr(), META_DATA_SIZE);      //3.0K
        {
            U16 u16tmpRemainLength  = sizeof(_msAPI_PVR_RecordPath);
            U8  u8tmpReadLength;
            U8  u8tmpSegment = 0;
            while(1)
            {
                if(u16tmpRemainLength>=184)
                {
                    u8tmpReadLength = 184;
                }
                else if(u16tmpRemainLength>0)
                {
                    u8tmpReadLength = u16tmpRemainLength;
                }
                else
                {
                    break;
                }

            #ifdef PVR_8051
                msAPI_MIU_Copy(PVR_READ_METADATA_BUFFER_ADR+PVR_TS_PACKET_SIZE*u8tmpSegment+PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U16)&tmpPvrRecordMeataData)+184*u8tmpSegment, u8tmpReadLength, MIU_SDRAM2SDRAM);
            #else
            #ifdef PVR_UTOPIA
                msAPI_MIU_Copy((((PVR_READ_METADATA_BUFFER_MEMORY_TYPE&MIU1)?PVR_READ_METADATA_BUFFER_ADR|MIU_INTERVAL:PVR_READ_METADATA_BUFFER_ADR))+PVR_TS_PACKET_SIZE*u8tmpSegment+PVR_TS_PACKET_HEADER_SIZE, _VA2PA((U32)&tmpPvrRecordMeataData)+184*u8tmpSegment, u8tmpReadLength, MIU_SDRAM2SDRAM);
            #else
                msAPI_MIU_Copy(PvrGetReadMetadataBufAddr()+PVR_TS_PACKET_SIZE*u8tmpSegment+PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U32)&tmpPvrRecordMeataData)+184*u8tmpSegment, u8tmpReadLength, MIU_SDRAM2SDRAM);
            #endif
            #endif

                u16tmpRemainLength -= u8tmpReadLength;
                u8tmpSegment++;
            }
        }

        msAPI_FCtrl_FileClose(u8fHandler);
        return tmpPvrRecordMeataData.enEncryptionType;
    }
}

//#ifdef S3PLUS
//Demuxs' record buffer on Neptune will contain dirty data before recording, need to drop it.
void _PVR_RecordDataAlignSyncByte(_msAPI_PVR_RecordPath* pstPvrRecordPath, U32* u32WriteLength)
{
#ifdef PVR_8051
    U32 u32BufferAlignPacket;
    U16 u16Segment;
    U16 u16Offset;
    U8 u8index=0;
    u32BufferAlignPacket = pstPvrRecordPath->u32BufferReadPointer-pstPvrRecordPath->u32BufferStart;
    u32BufferAlignPacket = ((u32BufferAlignPacket/PVR_TS_PACKET_SIZE)*PVR_TS_PACKET_SIZE);
    u32BufferAlignPacket+= pstPvrRecordPath->u32BufferStart;

    u16Segment = u32BufferAlignPacket/4096;
    u16Offset  = u32BufferAlignPacket%4096;
    MDrv_Sys_SetXdataWindow1Base(u16Segment);

    while(u8index < PVR_TS_PACKET_SIZE)
    {
        if ((XBYTE[u16Offset+0xf000+u8index] == 0x47) && (XBYTE[u16Offset+0xf000+u8index+PVR_TS_PACKET_SIZE] == 0x47))
        {
            break;
        }
        (*u32WriteLength)--;
        pstPvrRecordPath->u32BufferReadPointer++;
        u8index++;
    }
    MDrv_Sys_ReleaseXdataWindow1();
    return;
#else
    U8 *pBufStart=(U8 *)pstPvrRecordPath->u32BufferStart;
    U32 u32BufferRder=pstPvrRecordPath->u32BufferReadPointer-pstPvrRecordPath->u32BufferStart;
    //U32 u32BufferWter=pstPvrRecordPath->u32BufferWritePointer-pstPvrRecordPath->u32BufferStart;
    U32 u32BufLen=pstPvrRecordPath->u32BufferLength;
    U32 u32RealTsPktSize=(pstPvrRecordPath->bRecordAll == FALSE)?192:188;
    U8 u8index=0;
    while(u8index < u32RealTsPktSize&&(*u32WriteLength)>=u32RealTsPktSize)
    {
        if(((pBufStart[(u32BufferRder+u8index)%u32BufLen]==0x47&&pBufStart[(u32BufferRder+u8index+u32RealTsPktSize)%u32BufLen]==0x47)&& (u32RealTsPktSize==188))
            ||((pBufStart[4+(u32BufferRder+u8index)%u32BufLen]==0x47&&pBufStart[4+(u32BufferRder+u8index+u32RealTsPktSize)%u32BufLen]==0x47)&& (u32RealTsPktSize==192)))
        {
            break;
        }
        (*u32WriteLength)--;
        if((++pstPvrRecordPath->u32BufferReadPointer)>=(pstPvrRecordPath->u32BufferStart+u32BufLen))
        {
            pstPvrRecordPath->u32BufferReadPointer=pstPvrRecordPath->u32BufferStart;
        }
        u8index++;
    }
    return;
#endif
}
//#endif

#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
void _PVR_AESDMAEncryptDecrypt(U32 u32Address, U32 u32Length, enPvrAESDMAMode eMode) //TRUE: encrypt, else decrypt
{
#ifdef PVR_UTOPIA
    U16 u16Index;
    U32 u32AESaddr;
    U32 u32MetaData = u32Address;
    MS_U32 Key[4] = {0x4D535450,
                     0x56523039,
                     0x32313731,
                     0x36303036};

    u32AESaddr = _VA2PA(u32Address);
    //Reset AES DMA
    MDrv_AESDMA_Reset();
    //Min. byte limitation (16X)
    if(u32Length < 16)
    {
        printf("Error: AES Write Buffer not enough\n");
        u32Length = 0;
    }

    //Set read/write buffer
    if ((*((U8 *)u32MetaData)==0x2)
    &&(*((U8 *)u32MetaData + 1)==0x1E)
    &&(*((U8 *)u32MetaData + 2)==0x15)
    &&(*((U8 *)u32MetaData + 3)==0x76))
    {
        // MetaData Don't Need Decrypt
        return;
        //MDrv_AESDMA_SetFileInOut(u32AESaddr + 0xC00, u32Length - 0xC00, u32AESaddr, u32AESaddr+u32Length - 0xC00 -1);
    }
    else
    {
        MDrv_AESDMA_SetFileInOut(u32AESaddr, u32Length, u32AESaddr, u32AESaddr+u32Length-1);
    }

    //Set key.
    MDrv_AESDMA_SetKey(Key);

    if(eMode == E_ENCRYPT)
    {
        // Start to encrypt
        MDrv_AESDMA_SelEng(E_DRVAESDMA_CIPHER_ECB, TRUE);
        MDrv_AESDMA_Start(TRUE);
    }
    else
    {
        // Start to decrypt
        MDrv_AESDMA_SelEng(E_DRVAESDMA_CIPHER_ECB, FALSE);
        MDrv_AESDMA_Start(TRUE);
    }

    for (u16Index = 0; u16Index < 65535; u16Index++)
    {
        if ((MDrv_AESDMA_GetStatus() & BIT(16)))
            break;
    }

    return;

#else
    U8 u8keys0[4] = {0x4D, 0x53, 0x54, 0x50};
    U8 u8keys1[4] = {0x56, 0x52, 0x30, 0x39};
    U8 u8keys2[4] = {0x32, 0x31, 0x37, 0x31};
    U8 u8keys3[4] = {0x36, 0x30, 0x30, 0x36};
    U16 u16Index;
    U16 u16DscrmbBank;

    //Init. AES DMA
    MDRV_AESDMA_Initial();
    //Reset AES DMA
    MDRV_AESDMA_Reset();
    //Min. byte limitation (16X)
    if(u32Length < 16)
    {
        printf("Error: AES Write Buffer not enough\n");
        u32Length = 0;
    }

    //Set read buffer
    MDRV_AESDMA_SetReadFile(u32Address, u32Length);
    //Set write buffer
    MDRV_AESDMA_SetWriteFile(u32Address);
    //Set key.
    MDRV_AESDMA_SetCipherKeys(u8keys0, u8keys1, u8keys2, u8keys3);
    //Get ASE Bank
    u16DscrmbBank = MDRV_AESDMA_GetDscrmbBank()<<8;

    if(eMode == E_ENCRYPT)
    {
        // Start to encrypt
        MDRV_AESDMA_EncryptStart();
    }
    else
    {
        // Start to decrypt
        MDRV_AESDMA_DecryptStart();
    }

    for (u16Index = 0; u16Index < 65535; u16Index++)
    {
        #if (defined(PVR_8051) && !defined(S3PLUS)) //Pluto
        if ((XBYTE[u16DscrmbBank+0xFC] & BIT0) && (XBYTE[u16DscrmbBank+0xFE] & BIT0))
        #elif(!defined(PVR_UTOPIA)) //Chakra1
        if ((MDrv_ReadByte(u16DscrmbBank+0xFC) & BIT0) && (MDrv_ReadByte(u16DscrmbBank+0xFE) & BIT0))
        #else
            __ASSERT(0);
        #endif
        {
            break;
        }
    }
    return;
#endif
}
#endif //#if (ENABLE_PVR_AESDMA)

/***************************************************************************************/
BOOLEAN  msAPI_PVR_IsRecordSpaceEnough(void)
{
    U32 fs = msAPI_PVRFS_GetDriveFreeSpaceMB();
    if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32)
    {
        if(fs  >= MIN_FAT32_FILE_SIZE_KB/1024)
            return TRUE;
    }
    else //BULK
    {
        if(fs >0)
            return TRUE;
    }
    return FALSE;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_RecordPathInput(_msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    U32 u32WritePointer;
    U32 u32WriteLength;
    U32 u32Time1, u32Time2;
    BOOLEAN bFsOverSize = FALSE;
    U32 u32_DBGtimeshiftt0,u32_DBGtimeshiftt1,u32_DBGtswritelen;

    //printf("msAPI_PVR_RecordPathInput()\n" );

    /*[01-0]pvr part ==================================================================*/
  //printf("+\r");

    /*[01-1]demux part ================================================================*/
    /*[01-2]file system part ==========================================================*/
    u32PreWritePointer = pstPvrRecordPath->u32BufferWritePointer;

#if 1//def PVR_UTOPIA
    MApi_DMX_Pvr_WriteGet(&u32WritePointer);

    //printf("u32WritePointer=0x%X\n", u32WritePointer );

  #if 1//def MIPS_CHAKRA
    u32WritePointer = _PA2VA(u32WritePointer);
    //printf("u32WritePointer=0x%X\n", u32WritePointer );
  #endif

#else
    #if (!defined(PVR_8051) && !defined(PVR_UTOPIA)) //Chakra1
    MDrv_WriteByte(0x15FF, (MDrv_ReadByte(0x15FF) | 0x40)); // WP_LOAD
    MDrv_WriteByte(0x15FF, (MDrv_ReadByte(0x15FF) & (~0x40)));// WP_LOAD
    #endif
    u32WritePointer = msAPI_DMX_GetRecordWrite();
#endif
    if(pstPvrRecordPath->u32BufferReadPointer > pstPvrRecordPath->u32BufferWritePointer)
    {
        if(u32WritePointer > pstPvrRecordPath->u32BufferReadPointer)
        {
            #if 0
            printf("PVR_RECORD_OVERRUN-1 [W1-0x%08lx | R-0x%08lx | W2-0x%08lx] \n",
            pstPvrRecordPath->u32BufferWritePointer,
            pstPvrRecordPath->u32BufferReadPointer,
            u32WritePointer);
            #endif
            pstPvrRecordPath->u16RecordedErrCount1++;
            if(pstPvrRecordPath->u16RecordedErrCount1 >= 2)
            {
              //printf("record over run\n");
                return E_PVR_API_STATUS_RECORD_BUFFER_OVERRUN;
            }
        }
        else
        {
            pstPvrRecordPath->u16RecordedErrCount1 = 0;
        }
    }
    else
    {
        if((u32WritePointer < pstPvrRecordPath->u32BufferWritePointer) &&
           (u32WritePointer > pstPvrRecordPath->u32BufferReadPointer )   )
        {
            #if 0
            printf("PVR_RECORD_OVERRUN-2 [R-0x%08lx | W2-0x%08lx | W1-0x%08lx] \n",
            pstPvrRecordPath->u32BufferReadPointer,
            u32WritePointer,
            pstPvrRecordPath->u32BufferWritePointer);
            #endif
            pstPvrRecordPath->u16RecordedErrCount1++;
            if(pstPvrRecordPath->u16RecordedErrCount1 >= 2)
            {
              //printf("record over run2\n");
                return E_PVR_API_STATUS_RECORD_BUFFER_OVERRUN;
            }
        }
        else
        {
            pstPvrRecordPath->u16RecordedErrCount1 = 0;
        }
    }
    pstPvrRecordPath->u32BufferWritePointer = u32WritePointer;

    /*[##-1]check write address & length ==============================================*/
    if (u32WritePointer < pstPvrRecordPath->u32BufferReadPointer)
    {
        u32WriteLength = pstPvrRecordPath->u32BufferStart + pstPvrRecordPath->u32BufferLength - pstPvrRecordPath->u32BufferReadPointer;
    }
    else if (u32WritePointer > pstPvrRecordPath->u32BufferReadPointer)
    {
        u32WriteLength = u32WritePointer - pstPvrRecordPath->u32BufferReadPointer;
#if 1
        if(E_SERVICETYPE_DTV == msAPI_CM_GetCurrentServiceType() && MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            // _bAlignSyncByte = FALSE;
            if(u32WriteLength >= 960*1024)
            {
                u32WriteLength = 960*1024;
            }
            else
            {
                // u32WriteLength = 0;
            }
        }
#endif
    }
    else
    {
        u32WriteLength = 0;
    }

    /*[##-2]align sync byte ===========================================================*/
    //#ifdef S3PLUS
    if (_bAlignSyncByte)
    {
       // if(pstPvrRecordPath->bRecordAll != FALSE)//now just fix record all bug--refine later
        {
            _PVR_RecordDataAlignSyncByte(pstPvrRecordPath, &u32WriteLength);
        }
        _bAlignSyncByte = FALSE;
    }
    //#endif

    if (u32WriteLength > _u32BulkFileSystemRWLength)
    {
        if(E_SERVICETYPE_DTV == msAPI_CM_GetCurrentServiceType() && MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            ;
        }
        else
        {
            if(pstPvrRecordPath->bRecordAll == FALSE)
            {
                u32WriteLength = _u32BulkFileSystemRWLength;
            }
        }

        if ((pstPvrRecordPath->u32FilePositionKB*1024+pstPvrRecordPath->u32FilePosRmnBytes+ u32WriteLength) > (pstPvrRecordPath->u32FileLimitedSizeKB*1024))
        {
            u32WriteLength = (pstPvrRecordPath->u32FileLimitedSizeKB - pstPvrRecordPath->u32FilePositionKB)*1024-pstPvrRecordPath->u32FilePosRmnBytes;
        }
    }
    else
    {
        if ((pstPvrRecordPath->u32FilePositionKB*1024+pstPvrRecordPath->u32FilePosRmnBytes + u32WriteLength) > (pstPvrRecordPath->u32FileLimitedSizeKB*1024))
        {
            u32WriteLength = (pstPvrRecordPath->u32FileLimitedSizeKB - pstPvrRecordPath->u32FilePositionKB)*1024-pstPvrRecordPath->u32FilePosRmnBytes;
        }
        else if(pstPvrRecordPath->u32BufferReadPointer > (pstPvrRecordPath->u32BufferStart + pstPvrRecordPath->u32BufferLength - MIN_WRITE_LENGTH))
        {
            u32WriteLength = u32WriteLength;    //for special case in the gap
            //printf("special_write_gap=0x%08lx \n", u32WriteLength);
        }
        else
        {
            u32WriteLength = ALIGNMINWRITE(u32WriteLength);
        }

        if(u32WriteLength == 0)
        {
          //printf(">\r");
            return E_PVR_API_STATUS_OK;
        }
    }


    // check FAT32 file size =================================================

    if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
       msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    {
        if(pstPvrRecordPath->u32FileSizeKB + (u32WriteLength/1024) > MAX_FAT32_FILE_SIZE_KB)
        {
            u32WriteLength = u32WriteLength - u32WriteLength%PVR_TS_PACKET_SIZE ;
            bFsOverSize = TRUE;
        }
    }

    /*[##-2-1]encrypt data ============================================================*/
#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
    if (pstPvrRecordPath->u32FilePositionKB >= TOTAL_META_DATA_SIZEKB)
    {
        if(pstPvrRecordPath->enEncryptionType != E_PVR_ENCRYPTION_NONE)
            _PVR_AESDMAEncryptDecrypt(pstPvrRecordPath->u32BufferReadPointer, u32WriteLength, E_ENCRYPT);
    }
#endif
    // u32WriteLength = u32WriteLength/PVR_TS_PACKET_SIZE*PVR_TS_PACKET_SIZE;

    /*[##-3]write it ==================================================================*/
    u32Time1 = msAPI_Timer_GetTime0();
    u32_DBGtimeshiftt0 = msAPI_Timer_DiffTimeFromNow(u32Time1);
    u32_DBGtswritelen = u32WriteLength;
    u32WriteLength = msAPI_PVRFS_FileWrite(pstPvrRecordPath->hWriteFile,  pstPvrRecordPath->u32BufferReadPointer,u32WriteLength);
    u32_DBGtimeshiftt1 = msAPI_Timer_DiffTimeFromNow(u32Time1);

    if((u32_DBGtimeshiftt1 - u32_DBGtimeshiftt0) >= 600)
    {
        printf("\r\n [Write %ld Bytes Data need %ldms,it's too long]\n",u32_DBGtswritelen,(u32_DBGtimeshiftt1 - u32_DBGtimeshiftt0));
    }
    u32Time2 = msAPI_Timer_GetTime0();

    /*[GROUP2-3]=======================================================================*/
    pstPvrRecordPath->u32FileWriteTime += (u32Time2-u32Time1);
    pstPvrRecordPath->u32FileWriteSizeKB += (u32WriteLength/1024);

    if (u32WriteLength == 0)
    {
        printf("write error, why?\n");
        if( msAPI_PVRFS_GetDriveFreeSpaceMB()==0)
        {
            //printf("No DISK Space \n");
            printf("......E_PVR_API_STATUS_NO_DISK_SPACE....%d.......\n",__LINE__);
            return E_PVR_API_STATUS_NO_DISK_SPACE;
        }
        else
        {
            return E_PVR_API_STATUS_FILE_WRITE_ERROR;
        }
    }

    //====================== time stamp / ts header checking ==========================//
    #if (!ENABLE_PVR_AESDMA)
    if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_NONE)
    {
        if(pstPvrRecordPath->bRecordAll == FALSE)
        {
            U32 u32BufferAlignPacket;
            #ifdef PVR_8051
            U16 u16Segment;
            U16 u16Offset;
            static U8 u8PktOffset1=0;
            static U8 u8PktOffset2=0;
            #endif
            //read_pointer ##====================
            u32BufferAlignPacket = pstPvrRecordPath->u32BufferReadPointer-pstPvrRecordPath->u32BufferStart;

            #ifndef S3PLUS
            u32BufferAlignPacket = ALIGNMINREAD(u32BufferAlignPacket);
            #else
            u32BufferAlignPacket = ((u32BufferAlignPacket/188)*188);
            #endif
            u32BufferAlignPacket+= pstPvrRecordPath->u32BufferStart;

            #ifdef PVR_8051
            u16Segment = u32BufferAlignPacket/4096;
            u16Offset  = u32BufferAlignPacket%4096;
            MDrv_Sys_SetXdataWindow1Base(u16Segment);
            #ifndef S3PLUS
            if(XBYTE[u16Offset+u8PktOffset1+0xf004] != 0x47)
            #else
            if(u16Offset >= (4096-188*2))   //prevent overflow
            {
                u16Offset -= 188*2;
            }
            if(XBYTE[u16Offset+u8PktOffset1+0xf000] != 0x47)
            #endif
            #else
            if(*(U8 *)(u32BufferAlignPacket+4) != 0x47)
            #endif
            {
                #ifndef S3PLUS
                MS_DEBUG_MSG(printf("record packet error-1 at buff_pos=0x%08lx \n", u32BufferAlignPacket));
                return E_PVR_API_STATUS_RECORD_BUFFER_ERROR;
                #else
                for(u8PktOffset1=0;u8PktOffset1<188; u8PktOffset1++)
                {
                    if((XBYTE[u16Offset+u8PktOffset1+0xf000] == 0x47) &&
                       (XBYTE[u16Offset+u8PktOffset1+0xf0bc] == 0x47)   )
                    {
                        pstPvrRecordPath->u16RecordedErrCount3++;
                        if(pstPvrRecordPath->u16RecordedErrCount3 <= 2)
                        {
                          //printf("Record Packet Offset-1 become %02bu \n", u8PktOffset1);
                            break;
                        }
                        else
                        {
                          //printf("Warning: Record Packet Offset-1 become %02bu \n", u8PktOffset1);
                            break;
                          //return E_PVR_API_STATUS_RECORD_BUFFER_ERROR;
                        }
                    }
                }
                #endif
            }
            else
            {
                pstPvrRecordPath->u16RecordedErrCount3 = 0;
              //printf("time_stamp_file   =%02bx %02bx %02bx %02bx \n", XBYTE[u16Offset+0xf000], XBYTE[u16Offset+0xf001], XBYTE[u16Offset+0xf002], XBYTE[u16Offset+0xf003]);
            }
            #ifdef PVR_8051
            MDrv_Sys_ReleaseXdataWindow1();
            #endif
            //buffer_start ##====================
            #ifdef PVR_8051
            u16Segment = pstPvrRecordPath->u32BufferStart/4096;
            u16Offset  = pstPvrRecordPath->u32BufferStart%4096;
            MDrv_Sys_SetXdataWindow1Base(u16Segment);
            #ifndef S3PLUS
            if(XBYTE[u16Offset+u8PktOffset2+0xf004] != 0x47)
            #else
            if(u16Offset >= (4096-188*2))   //prevent overflow
            {
                u16Offset -= 188*2;
            }
            if(XBYTE[u16Offset+u8PktOffset2+0xf000] != 0x47)
            #endif
            #else
            if(*(U8 *)(pstPvrRecordPath->u32BufferStart+4) != 0x47)
            #endif
            {
                #ifndef S3PLUS
              MS_DEBUG_MSG(printf("record packet error-2 at buff_pos=0x%08lx \n", pstPvrRecordPath->u32BufferStart));
                return E_PVR_API_STATUS_RECORD_BUFFER_ERROR;
                #else
                for(u8PktOffset2=0;u8PktOffset2<188; u8PktOffset2++)
                {
                    if((XBYTE[u16Offset+u8PktOffset2+0xf000] == 0x47) &&
                       (XBYTE[u16Offset+u8PktOffset2+0xf0bc] == 0x47)   )
                    {
                        pstPvrRecordPath->u16RecordedErrCount3++;
                        if(pstPvrRecordPath->u16RecordedErrCount3 <= 2)
                        {
                          //printf("Record Packet Offset-2 become %02bu \n", u8PktOffset2);
                            break;
                        }
                        else
                        {
                          //printf("Warning: Record Packet Offset-2 become %02bu \n", u8PktOffset2);
                            break;
                          //return E_PVR_API_STATUS_RECORD_BUFFER_ERROR;
                        }
                    }
                }
                #endif
            }
            else
            {
               //printf("time_stamp_file   =%02bx %02bx %02bx %02bx \n", XBYTE[u16Offset+0xf000], XBYTE[u16Offset+0xf001], XBYTE[u16Offset+0xf002], XBYTE[u16Offset+0xf003]);
            }
            #ifdef PVR_8051
            MDrv_Sys_ReleaseXdataWindow1();
            #endif
            // ================================##
        }
    }
    #endif
    //====================== time stamp / ts header checking ==========================//

    /*[##-3]statistics ================================================================*/
    /*[GROUP1-2]=======================================================================*/
    pstPvrRecordPath->u32BufferReadPointer+= u32WriteLength;
    if(pstPvrRecordPath->u32BufferReadPointer == (pstPvrRecordPath->u32BufferStart + pstPvrRecordPath->u32BufferLength))
    {
        pstPvrRecordPath->u32BufferReadPointer = pstPvrRecordPath->u32BufferStart;
    }

    u32RecordLastWriteDataSize = u32WriteLength;
    if (u32RecordReWriteDataSize)
    {
        if (u32RecordReWriteDataSize > u32WriteLength)
        {
            u32RecordReWriteDataSize = u32RecordReWriteDataSize - u32WriteLength;
            u32WriteLength = 0;
        }
        else
        {
            u32RecordReWriteDataSize = 0;
            u32WriteLength = u32WriteLength - u32RecordReWriteDataSize;
        }
    }

    /*[GROUP2-1]=======================================================================*/
    pstPvrRecordPath->u32FilePositionKB += (u32WriteLength+pstPvrRecordPath->u32FilePosRmnBytes)/1024;
    pstPvrRecordPath->u32FilePosRmnBytes=(u32WriteLength+pstPvrRecordPath->u32FilePosRmnBytes)%1024;
    pstPvrRecordPath->u32FileValidPosEndKB    = pstPvrRecordPath->u32FilePositionKB;    //need to sync always
    if (pstPvrRecordPath->u32FilePositionKB >= pstPvrRecordPath->u32FileLimitedSizeKB)
    {
      //LongLong u64FileLength;
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@just for alignment@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        #if 0
        if(pstPvrRecordPath->u32FileGapSizeKB != 0)
        {
            msAPI_PVRFS_FileWrite(pstPvrRecordPath->hWriteFile, pstPvrRecordPath->u32BufferReadPointer ,pstPvrRecordPath->u32FileGapSizeKB*1024);
        }
        #endif
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@just for alignment@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        pstPvrRecordPath->u32FilePositionKB = 0;
        pstPvrRecordPath->u32FilePosRmnBytes=0;
        pstPvrRecordPath->u32FileValidPosEndKB    = pstPvrRecordPath->u32FilePositionKB;//need to sync always
        msAPI_PVRFS_FileSeek(pstPvrRecordPath->hWriteFile, msAPI_PVR_KToLongLong(pstPvrRecordPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN);
      //u64FileLength = msAPI_PVRFS_FileLength(pstPvrRecordPath->hWriteFile);
      //printf("#################write-file-siz=0x%08lx|%08lx#################\n", u64FileLength.Hi, u64FileLength.Lo);
      //u64FileLength = msAPI_PVRFS_FileTell(pstPvrRecordPath->hWriteFile);
      //printf("#################write-file-pos=0x%08lx|%08lx#################\n", u64FileLength.Hi, u64FileLength.Lo);
    #if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
        msAPI_PVR_RecordPathUpdateMetadata(pstPvrRecordPath, E_METADATA_UPDATE_FILE);
    #endif
    }
    if( pstPvrRecordPath->u32FileSizeKB < pstPvrRecordPath->u32FileLimitedSizeKB)
    {
        pstPvrRecordPath->u32FileSizeKB += u32WriteLength/1024;
    }
//printf("Write Time:%lu,  %lu,   %lu\n",(u32Time2-u32Time1), u32WriteLength/1024, (u32WriteLength/1024*1000)/(u32Time2-u32Time1));
    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/
    /*[GROUP4-1]=======================================================================*/
    pstPvrRecordPath->u32RecordedPeriod  = msAPI_Timer_DiffTimeFromNow(pstPvrRecordPath->u32RecordedTime)/100;

    /*[02]global variables ============================================================*/
    // printf("msAPI_PVR_RecordPathInput\n");
    if(bFsOverSize)
    {
        return E_PVR_API_STATUS_RECORD_FILE_OVER_SIZE;
    }
    else
    {
        return E_PVR_API_STATUS_OK;
    }
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_RecordPathGatherStatistics(_msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    U32 u32PosDiffKB;

    if (msAPI_Timer_GetTime0() > pstPvrRecordPath->u32RecordedStaCheckTime)
    {
        /*[01-0]pvr part ==============================================================*/


        /*[01-1]demux part ============================================================*/


        /*[01-2]file system part ======================================================*/
      //printf("update meta data - record \n");
        if(pstPvrRecordPath->bLinkPlayback)
        {
        #if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
            msAPI_PVR_RecordPathUpdateMetadata(pstPvrRecordPath, E_METADATA_UPDATE_MEMORY);
        #endif
        }

        /*[GROUP2-1]===================================================================*/
        if(pstPvrRecordPath->u32FilePositionKB > pstPvrRecordPath->u32FileLastPosKB)
        {
            u32PosDiffKB  = pstPvrRecordPath->u32FilePositionKB - pstPvrRecordPath->u32FileLastPosKB;
        }
        else if(pstPvrRecordPath->u32FilePositionKB < pstPvrRecordPath->u32FileLastPosKB)
        {
            u32PosDiffKB  = pstPvrRecordPath->u32FileLimitedSizeKB - pstPvrRecordPath->u32FileLastPosKB;
            u32PosDiffKB += pstPvrRecordPath->u32FilePositionKB;
        }
        else    //no signal
        {
            u32PosDiffKB  = 0;
        }
        pstPvrRecordPath->u32FileLastPosKB = pstPvrRecordPath->u32FilePositionKB;

        /*[GROUP2-2]===================================================================*/
        if((pstPvrRecordPath->u32FileValidPeriod / 10 * pstPvrRecordPath->u16RecordedAvgRate) >= pstPvrRecordPath->u32FileLimitedSizeKB)
        {
            pstPvrRecordPath->u32FileValidPeriod  = pstPvrRecordPath->u32FileLimitedSizeKB / pstPvrRecordPath->u16RecordedAvgRate;

            if(pstPvrRecordPath->u32FileValidPeriod>=(60*10))
            {
                pstPvrRecordPath->u32FileValidPeriod /= (60*10); //the unit is 10 minutes
                pstPvrRecordPath->u32FileValidPeriod *= (60*10); //the unit is 10 minutes
            }
            else
            {
                pstPvrRecordPath->u32FileValidPeriod /= (60*1);  //the unit is 1  minute
                pstPvrRecordPath->u32FileValidPeriod *= (60*1);  //the unit is 1  minute
            }
            if(pstPvrRecordPath->u32FileValidPeriod != 0)
            {
              //printf("===>>>WARNING: valid period becomes %02bu:%02bu:%02bu seconds \n", (U8)(pstPvrRecordPath->u32FileValidPeriod/3600),(U8)(pstPvrRecordPath->u32FileValidPeriod/60-((pstPvrRecordPath->u32FileValidPeriod/3600)*60)), (U8)(pstPvrRecordPath->u32FileValidPeriod%60));
            }
            else
            {
              //printf("===>>>ERROR  : valid period becomes %02bu:%02bu:%02bu seconds \n", (U8)(pstPvrRecordPath->u32FileValidPeriod/3600),(U8)(pstPvrRecordPath->u32FileValidPeriod/60-((pstPvrRecordPath->u32FileValidPeriod/3600)*60)), (U8)(pstPvrRecordPath->u32FileValidPeriod%60));
                return E_PVR_API_STATUS_TIMESHIFT_BUFFER_NOT_ENOUGH;
            }
            pstPvrRecordPath->u32FileValidPeriod *= 10;
        }

        if((msAPI_Timer_DiffTimeFromNow(pstPvrRecordPath->u32RecordedTime)/100) <= pstPvrRecordPath->u32FileValidPeriod)
        {
            pstPvrRecordPath->u32FileValidPosEndKB    = pstPvrRecordPath->u32FilePositionKB;
            pstPvrRecordPath->u32FileValidDistanceKB  = pstPvrRecordPath->u32FilePositionKB-PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
            //pstPvrRecordPath->u32FileValidPosStrKB    = pstPvrRecordPath->u32FileValidPosStrKB; //not changed
        }
        else
        {
            pstPvrRecordPath->u32FileValidPosEndKB    = pstPvrRecordPath->u32FilePositionKB;
            pstPvrRecordPath->u32FileValidDistanceKB  = pstPvrRecordPath->u32FileValidPeriod/10*pstPvrRecordPath->u16RecordedAvgRate;

            /*[01][START | END]========================================================*/
            if(pstPvrRecordPath->u32FileValidPosEndKB > pstPvrRecordPath->u32FileValidPosStrKB)
            {
                pstPvrRecordPath->u32FileValidPosStrKB = pstPvrRecordPath->u32FileValidPosEndKB - pstPvrRecordPath->u32FileValidDistanceKB;
            }

            /*[02][END | START]========================================================*/
            else
            {
                if((pstPvrRecordPath->u32FileValidPosEndKB-PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024) < pstPvrRecordPath->u32FileValidDistanceKB)
                {
                    pstPvrRecordPath->u32FileValidPosStrKB = pstPvrRecordPath->u32FileLimitedSizeKB - pstPvrRecordPath->u32FileValidDistanceKB + (pstPvrRecordPath->u32FileValidPosEndKB - PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024);
                }
                else
                {
                    pstPvrRecordPath->u32FileValidPosStrKB = pstPvrRecordPath->u32FileValidPosEndKB - pstPvrRecordPath->u32FileValidDistanceKB;
                }
            }
        }

        #if 0 //=======================================================================//
        printf("[Str=0x%08lx / Dist=0x%08lx / End=0x%08lx] \n", pstPvrRecordPath->u32FileValidPosStrKB,
                                                                pstPvrRecordPath->u32FileValidDistanceKB,
                                                                pstPvrRecordPath->u32FileValidPosEndKB);
        #endif //======================================================================//

        /*[GROUP2-3]===================================================================*/
        #if 0 //=======================================================================//
        printf("[wr_cnt=%02bu / wr_time=%08lu] \n", pstPvrRecordPath->u8FileWriteCount, pstPvrRecordPath->u32FileWriteTime);
        #endif //======================================================================//

        /*[01-3]system part ===========================================================*/
        /*[GROUP4-5]===================================================================*/
        pstPvrRecordPath->u16RecordedLstRate = (U16)u32PosDiffKB;

        if(msAPI_Timer_DiffTimeFromNow(pstPvrRecordPath->u32RecordedTime) < (WRITE_CHECK_START+1000))
        {
            pstPvrRecordPath->u16RecordedLstRate = pstPvrRecordPath->u16RecordedLstRate / (WRITE_CHECK_START   /1000);

            if((pstPvrRecordPath->u16RecordedLstRate > (_u16BulkFileSystemRWSpeed/100*90)) && (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS))   //90% CPU POWER
            {
              //printf("TS BitRate %04u too HIGH\n", pstPvrRecordPath->u16RecordedLstRate);
                return E_PVR_API_STATUS_DISK_SPEED_SLOW;
            }
            else
            {
              //printf("TS BitRate %04u       OK\n", pstPvrRecordPath->u16RecordedLstRate);
            }
        }
        else
        {
            pstPvrRecordPath->u16RecordedLstRate = pstPvrRecordPath->u16RecordedLstRate / (WRITE_CHECK_DURATION/1000);
        }
        if(pstPvrRecordPath->u16RecordedLstRate > pstPvrRecordPath->u16RecordedMaxRate)
        {
            pstPvrRecordPath->u16RecordedMaxRate = pstPvrRecordPath->u16RecordedLstRate;
        }
        if(pstPvrRecordPath->u16RecordedLstRate < pstPvrRecordPath->u16RecordedMinRate)
        {
            pstPvrRecordPath->u16RecordedMinRate = pstPvrRecordPath->u16RecordedLstRate;
        }

        if(msAPI_Timer_DiffTimeFromNow(pstPvrRecordPath->u32RecordedTime) < (WRITE_CHECK_START+1000))
        {
            pstPvrRecordPath->u32RecordedKBytes += pstPvrRecordPath->u16RecordedLstRate * ( WRITE_CHECK_START   /1000);
        }
        else
        {
            pstPvrRecordPath->u32RecordedKBytes += pstPvrRecordPath->u16RecordedLstRate * ( WRITE_CHECK_DURATION/1000);
        }
        if ((pstPvrRecordPath->u32RecordedPeriod - pstPvrRecordPath->u32PausedPeriod)>10)
            pstPvrRecordPath->u16RecordedAvgRate = (U16)(pstPvrRecordPath->u32RecordedKBytes /((pstPvrRecordPath->u32RecordedPeriod - pstPvrRecordPath->u32PausedPeriod)/10));
      //intf("u16RecordedAvgRate=%u\n", pstPvrRecordPath->u16RecordedAvgRate);

        if(pstPvrRecordPath->u16RecordedLstRate == 0)
        {
            U32 u32WritePointer = 0;
            MApi_DMX_Pvr_WriteGet(&u32WritePointer);
            if(u32PreWritePointer == u32WritePointer)
            {
                pstPvrRecordPath->u16RecordedErrCount2++;
                #if 0 //auto-stop-timeshift ===============================================//
                if(pstPvrRecordPath->u16RecordedErrCount2 >=3600)   //ONE HOUR
                {
                  //printf("FileEND or NoSIGNAL\n");
                    return E_PVR_API_STATUS_RECORD_NO_INPUT;
                }
                #endif //==================================================================//
                pstPvrRecordPath->u32RecordedPeriod  = msAPI_Timer_DiffTimeFromNow(pstPvrRecordPath->u32RecordedTime)/100;
                pstPvrRecordPath->u32PausedPeriod+=10;  //ONE SECOND
            }
        }
        else
        {
            if(pstPvrRecordPath->u16RecordedErrCount2 != 0)
            {
                pstPvrRecordPath->u32PausedPeriod+=5;   //AVG HALF SECOND
            pstPvrRecordPath->u16RecordedErrCount2=0;
        }
        }

        /*[GROUP4-6]===================================================================*/
        pstPvrRecordPath->u32RecordedStaCheckTime += WRITE_CHECK_DURATION;

        #if 0 //=======================================================================//
        printf("REC[%bd]: %04lu M / %02lu:%02lu S : ---:--- S : --:-- S / %04u KB/S (MAX: %04u KB/S / MIN: %04u KB/S / LST: %04u KB/S) @=\n",
                                                                            pstPvrRecordPath->u8LogicalProgrammeNumber,
                                                                            pstPvrRecordPath->u32RecordedKBytes/1024,
                                                                           (pstPvrRecordPath->u32RecordedPeriod/10)/60, (pstPvrRecordPath->u32RecordedPeriod/10)%60,
                                                                            pstPvrRecordPath->u16RecordedAvgRate,
                                                                            pstPvrRecordPath->u16RecordedMaxRate,
                                                                            pstPvrRecordPath->u16RecordedMinRate,
                                                                            pstPvrRecordPath->u16RecordedLstRate);
        #endif //======================================================================//

        /*[02]global variables ========================================================*/
      //printf("msAPI_PVR_RecordPathGatherStatistics\n");

    }
    //======= For Fast Resume After Pause in TimeShift Mode (Especially Radio) ========*/
    else if(msAPI_Timer_DiffTimeFromNow(pstPvrRecordPath->u32RecordedTime) < WRITE_CHECK_START)
    {
        pstPvrRecordPath->u32FileValidPosEndKB    = pstPvrRecordPath->u32FilePositionKB;
        pstPvrRecordPath->u32FileValidDistanceKB  = pstPvrRecordPath->u32FilePositionKB-PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
        //pstPvrRecordPath->u32FileValidPosStrKB    = pstPvrRecordPath->u32FileValidPosStrKB; //not changed
    }
    //======= For Fast Resume After Pause in TimeShift Mode (Especially Radio) ========*/

    if((pstPvrRecordPath->u16RecordedErrCount1 > 0 || pstPvrRecordPath->u16RecordedErrCount3 > 0)
       && (pstPvrRecordPath->u16RecordedLstRate > 0))
    {
        U32 u32WriteRate = 0;
        if (pstPvrRecordPath->u32FileWriteTime)
            u32WriteRate = pstPvrRecordPath->u32FileWriteSizeKB*1000/pstPvrRecordPath->u32FileWriteTime;

      //printf("u16RecordedErrCount1=%d,%d\n",pstPvrRecordPath->u16RecordedErrCount1, pstPvrRecordPath->u16RecordedErrCount3);
      //u32WriteRate = u32WriteRate*10/9; //tolerance
        if(u32WriteRate < pstPvrRecordPath->u16RecordedAvgRate)
        {
            MS_DEBUG_MSG(printf("u32WriteRate=%lu,u16RecordedAvgRate=%u\n",u32WriteRate, pstPvrRecordPath->u16RecordedAvgRate));
            return E_PVR_API_STATUS_DISK_SPEED_SLOW;
        }
        pstPvrRecordPath->u32FileWriteSizeKB = 0;
        pstPvrRecordPath->u32FileWriteTime = 0;
    }
    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_RecordPathStop(_msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    U8 u8VirtualFltIdx;
    U8 u8TempPIDCount[MSAPI_DMX_RECORD_FILTER_NUMBER];

    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    for(u8VirtualFltIdx=0; u8VirtualFltIdx<MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
    {
        u8TempPIDCount[u8VirtualFltIdx] = 0;
    }

    for(u8VirtualFltIdx=0; u8VirtualFltIdx<MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
    {
        if(pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if(_pu8RecordPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] == 1)
            {
                msAPI_DMX_Stop(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
              //printf("stop PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
            }
            else
            {
                u8TempPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] ++;
                if(u8TempPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] == _pu8RecordPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]])
                {
                    msAPI_DMX_Stop(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                  //printf("stop PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                }
            }
        }
    }
#ifdef PVR_UTOPIA
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
    if(pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
    {
        MApi_DMX_PvrCA_Stop();
    }
    else
#endif
    {
        MApi_DMX_Pvr_Stop();
    }
#endif
    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        #ifdef PVR_8051
        XBYTE[0x15b7] &= ~0x18;         //<---burst_len Burst length selection in STR2MI MIU write:
                                               //00:    burst length = 8
                                               //01:    burst length = 4
                                               //10,11: burst length = 1
        #else
        {
            U8 u8OrgValue = MDrv_ReadByte(0x15b7);
            u8OrgValue &= ~0x18;
            MDrv_WriteByte(0x15b7,u8OrgValue);
        }
        #endif
    }

    /*[01-2]file system part ==========================================================*/


    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_RecordPathStop\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_RecordPathClose(_msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    U8 u8VirtualFltIdx;

    /*[01-0]pvr part ==================================================================*/
  //pstPvrRecordPath->bInUse = FALSE; //<MOVE to LAST

    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        _u8LPNAccumulator = 0;
      //printf("reset LPN Accumulator \n");
    }

    /*[01-1]demux part ================================================================*/
    for(u8VirtualFltIdx=0; u8VirtualFltIdx<MSAPI_DMX_RECORD_FILTER_NUMBER; u8VirtualFltIdx++)
    {
        if(pstPvrRecordPath->u8FilterID[u8VirtualFltIdx] != MSAPI_DMX_INVALID_FLT_ID)
        {
            _pu8RecordPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]--;
            if(_pu8RecordPIDCount[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] == 0)
            {
                #ifdef PVR_UTOPIA
                MApi_DMX_Close(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                #else
                msAPI_DMX_Close(_pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]]);
                #endif
              //printf("close PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]], pstPvrRecordPath->u16PID[u8VirtualFltIdx], pstPvrRecordPath->enFilterType[u8VirtualFltIdx]);
                _pu8RecordFID[pstPvrRecordPath->u8FilterID[u8VirtualFltIdx]] = MSAPI_DMX_INVALID_FLT_ID;
            }
        }
    }

    /*[01-2]file system part ==========================================================*/
#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
    msAPI_PVR_RecordPathUpdateMetadata(pstPvrRecordPath, E_METADATA_UPDATE_FILE);
#endif

    if(msAPI_PVR_RecordPathGetWorkingCount() == 1) //itself only
    {
        msAPI_PVRFS_FileClose(pstPvrRecordPath->hWriteFile);
        pstPvrRecordPath->hWriteFile = INVALID_FILE_HANDLE;
#if (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
        MAPP_CIPVR_CIPVRFS_RecordFileClose();
#endif
    }

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[01-0]pvr part ==================================================================*/
    pstPvrRecordPath->bInUse = FALSE; //<MOVE from FIRST
    msAPI_PVR_SetRecordCAPVR(E_PVR_ENCRYPTION_NONE);
    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_RecordPathClose\n");

    return E_PVR_API_STATUS_OK;
}

enPvrApiStatus msAPI_PVR_RecordChangeFile(U16 *pu16RecordFileName, _msAPI_PVR_RecordPath * pstPvrRecordPath)
{
    U32 u32RecordLengthKB;
    U16 u16RecordTime;

  //printf("msAPI_PVR_RecordFileChange\n");
#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
    msAPI_PVR_RecordPathUpdateMetadata(pstPvrRecordPath, E_METADATA_UPDATE_FILE);
#endif

    msAPI_PVRFS_FileClose(pstPvrRecordPath->hWriteFile);
    /*[01-0]pvr part ==================================================================*/

    /*[01-2]file system part ==========================================================*/
    /*[GROUP2-1]=======================================================================*/
    pstPvrRecordPath->hWriteFile                 = INVALID_FILE_HANDLE;
    pstPvrRecordPath->u32FilePositionKB          = 0;
    pstPvrRecordPath->u32FilePosRmnBytes         = 0;
    pstPvrRecordPath->u32FileLastPosKB           = 0;
    pstPvrRecordPath->u32FileSizeKB              = 0;

    /*[GROUP2-2]=======================================================================*/
    u32RecordLengthKB = PVR_RECORD_LENGTH_INFINITE;
    u16RecordTime     = PVR_RECORD_TIME_INFINITE;

    pstPvrRecordPath->u32FileGapSizeKB           = (u32RecordLengthKB - (PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024))%3;
    pstPvrRecordPath->u32FileLimitedSizeKB       = u32RecordLengthKB - pstPvrRecordPath->u32FileGapSizeKB;
    pstPvrRecordPath->u32FileValidPosStrKB       = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
    pstPvrRecordPath->u32FileValidPosEndKB       = 0;
    pstPvrRecordPath->u32FileValidDistanceKB     = 0;
    pstPvrRecordPath->u32FileValidPeriod         = (U32)u16RecordTime*10;

    /*[GROUP2-3]=======================================================================*/
    pstPvrRecordPath->u32FileWriteTime           = 0;
    pstPvrRecordPath->u32FileWriteSizeKB         = 0;

    //=================================================================================//
    if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
    {
        pstPvrRecordPath->hWriteFile = msAPI_PVRFS_FileOpen(pu16RecordFileName, PVRFS_OPEN_FOR_WRITE);
    }
    else if (msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
             msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    {
        pstPvrRecordPath->hWriteFile = msAPI_PVRFS_FileCreate(pu16RecordFileName);
    }

    if (pstPvrRecordPath->hWriteFile == INVALID_FILE_HANDLE)
    {
        pstPvrRecordPath->bInUse = FALSE;
        return E_PVR_API_STATUS_ERROR;
    }
    //=================================================================================//
    pstPvrRecordPath->u32RecordedTotalTime += pstPvrRecordPath->u32RecordedPeriod;
    pstPvrRecordPath->u32RecordedStaCheckTime    = 0;
    pstPvrRecordPath->u32RecordedKBytes          = 0;

    pstPvrRecordPath->u32RecordedStaCheckTime = msAPI_Timer_GetTime0() + WRITE_CHECK_START;  //start from 1st sec
    /*[GROUP4-7]=======================================================================*/
    pstPvrRecordPath->bLinkPlayback              = FALSE;
#if (0 != PVR_WRITE_METADATA_BUFFER_LEN)
    msAPI_PVR_RecordPathUpdateMetadata(pstPvrRecordPath, E_METADATA_UPDATE_FILE);         //Record store metadata after use
#endif

#if 1//def PVR_UTOPIA
    MApi_DMX_Pvr_WriteGet(&pstPvrRecordPath->u32BufferReadPointer);

 #if 1//def MIPS_CHAKRA
    pstPvrRecordPath->u32BufferReadPointer = _PA2VA(pstPvrRecordPath->u32BufferReadPointer);
 #endif
#else
    pstPvrRecordPath->u32BufferReadPointer = msAPI_DMX_GetRecordWrite();
#endif

    //#ifdef S3PLUS
    _bAlignSyncByte = TRUE;
    //#endif

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////////// playback path /////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static enPvrApiStatus   msAPI_PVR_PlaybackPathUpdateMetadata(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath, enPvrMetadataUpdateMode enUpdateMode)
{
    U32 u32ReadLength;

    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/


    /*[01-2]file system part ==========================================================*/
    if(enUpdateMode == E_METADATA_UPDATE_FILE)
    {
        pstPvrPlaybackPath->u32FilePositionKB = pstPvrPlaybackPath->u8LogicalProgrammeNumber*META_DATA_SIZE/1024;
        msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(pstPvrPlaybackPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN);
        u32ReadLength = msAPI_PVRFS_FileRead(pstPvrPlaybackPath->hReadFile, PvrGetReadMetadataBufAddr(), META_DATA_SIZE);      //3.0K
        {
            U16 u16RemainLength  = sizeof(_msAPI_PVR_RecordPath);
            U8  u8ReadLength;
            U8  u8Segment = 0;
            while(1)
            {
                if(u16RemainLength>=184)
                {
                    u8ReadLength = 184;
                }
                else if(u16RemainLength>0)
                {
                    u8ReadLength = u16RemainLength;
                }
                else
                {
                    break;
                }

            #ifdef PVR_8051
                msAPI_MIU_Copy(PVR_READ_METADATA_BUFFER_ADR+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U16)&_PvrRecordMeataData)+184*u8Segment, u8ReadLength, MIU_SDRAM2SDRAM);
            #else
            #ifdef PVR_UTOPIA
                msAPI_MIU_Copy((((PVR_READ_METADATA_BUFFER_MEMORY_TYPE&MIU1)?PVR_READ_METADATA_BUFFER_ADR|MIU_INTERVAL:PVR_READ_METADATA_BUFFER_ADR))+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, _VA2PA((U32)&_PvrRecordMeataData)+184*u8Segment, u8ReadLength, MIU_SDRAM2SDRAM);
            #else
                msAPI_MIU_Copy(PvrGetReadMetadataBufAddr()+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U32)&_PvrRecordMeataData)+184*u8Segment, u8ReadLength, MIU_SDRAM2SDRAM);
            #endif
            #endif

                u16RemainLength -= u8ReadLength;
                u8Segment++;
            }
        }
        #if (PVR_TS_PACKET_SIZE == 192)
        if (_PvrRecordMeataData.u16RecordedAvgRate == 0)
        {
            if(pstPvrPlaybackPath->enDirection != E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD)
            {
                U32 u32Totaltime = 0;
                LongLong fileLen;
                u32Totaltime = msAPI_PVR_PlaybackGetTotalTimeByTimeStamp(pstPvrPlaybackPath->pstPvrRecordPath->enEncryptionType,pstPvrPlaybackPath->hReadFile);
                if (u32Totaltime >= 10)
                {
                    fileLen = msAPI_PVRFS_FileLength(pstPvrPlaybackPath->hReadFile);
                    _PvrRecordMeataData.u32RecordedKBytes = (fileLen.Lo - PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE)/1024;
                    _PvrRecordMeataData.u32RecordedPeriod=_PvrRecordMeataData.u32FileValidPeriod=u32Totaltime;
                    _PvrRecordMeataData.u16RecordedAvgRate = (U16)(_PvrRecordMeataData.u32RecordedKBytes/(_PvrRecordMeataData.u32RecordedPeriod/10));
                    _PvrRecordMeataData.u32FileValidDistanceKB = _PvrRecordMeataData.u16RecordedAvgRate * (_PvrRecordMeataData.u32RecordedPeriod/10);
                    _PvrRecordMeataData.u32FileValidPosStrKB = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
                    _PvrRecordMeataData.u32FileValidPosEndKB =  _PvrRecordMeataData.u32FileValidPosStrKB + _PvrRecordMeataData.u32FileValidDistanceKB;
                }
            }
        }
        #endif
        pstPvrPlaybackPath->u32FilePositionKB = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
        msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(pstPvrPlaybackPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN);
    }
    else
    {
        #if 0  // Passive from Record Path ============================================//
        {
            U16 u16RemainLength  = sizeof(_msAPI_PVR_RecordPath);
            U8  u8ReadLength;
            U8  u8Segment = 0;
            while(1)
            {
                if(u16RemainLength>=184)
                {
                    u8ReadLength = 184;
                }
                else if(u16RemainLength>0)
                {
                    u8ReadLength = u16RemainLength;
                }
                else
                {
                    break;
                }

                msAPI_MIU_Copy(msAPI_MIU_XData2SDRAMAddr((U16)pstPvrRecordPath)+184*u8Segment, PVR_READ_METADATA_BUFFER_ADR+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8ReadLength, MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(PVR_READ_METADATA_BUFFER_ADR+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U16)&_PvrRecordMeataData)+184*u8Segment, u8ReadLength, MIU_SDRAM2SDRAM);
                u16RemainLength -= u8ReadLength;
                u8Segment++;
            }
        }
        #endif // Passive from Record Path ============================================//
        u32ReadLength = 0;
        //pstPvrPlaybackPath->u32FilePositionKB = pstPvrPlaybackPath->u32FilePositionKB; //not changed
    }

    #if 0   //=========================================================================//
    {
        U16 u16ByteNo;
        printf("==================================================================\n");
        printf("read_metadata_record_path   = %04lu\n", u32ReadLength);
        printf("==================================================================\n");
        MDrv_Sys_SetXdataWindow1Base(PVR_READ_METADATA_BUFFER_ADR/4096);
        for(u16ByteNo=0; u16ByteNo<META_DATA_SIZE; u16ByteNo++)
        {
            printf("%02bx", _pu8MetadataForRead[u16ByteNo]);
            if(u16ByteNo%32==31)
                printf("##\n");
        }
        MDrv_Sys_ReleaseXdataWindow1();
        printf("==================================================================\n");
    }
    #endif  //=========================================================================//

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathUpdateMetadata\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
_msAPI_PVR_PlaybackPath *   msAPI_PVR_PlaybackPathOpen(U16 *pu16PlaybackPathName)
{
    U8 u8PathID;
    U8 u8FID;

    /*[01-0]pvr part ==================================================================*/
    for(u8PathID = 0; u8PathID < PVR_MAX_PLAYBACK_PATH; u8PathID++)
    {
        if(_PvrPlaybackPath[u8PathID].bInUse == FALSE)
        {
            _PvrPlaybackPath[u8PathID].bInUse = TRUE;
            break;
        }
    }

    if(u8PathID >= PVR_MAX_PLAYBACK_PATH)
    {
        return NULL;
    }

    _PvrPlaybackPath[u8PathID].enDirection              = E_PLAYBACK_PATH_DIRECTION_FORWARD;
    _PvrPlaybackPath[u8PathID].u8LogicalProgrammeNumber = 0;

#ifdef S3PLUS
    _PvrPlaybackPath[u8PathID].enPlaySpeed = E_PLAY_SPEED_1X;
#endif

    /*[01-1]demux part ================================================================*/
    /*[GROUP1-1]=======================================================================*/
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        _PvrPlaybackPath[u8PathID].u8FilterID[u8FID]      = MSAPI_DMX_INVALID_FLT_ID;
        _PvrPlaybackPath[u8PathID].u16PID[u8FID]          = MSAPI_DMX_INVALID_PID;
        _PvrPlaybackPath[u8PathID].enFilterType[u8FID]    = (MSAPI_DMX_FILTER_TYPE) MSAPI_DMX_INVALID_FLT_TYPE;
    }

    /*[GROUP1-2]=======================================================================*/
    _PvrPlaybackPath[u8PathID].u32BufferStart           = 0;
    _PvrPlaybackPath[u8PathID].u32BufferLength          = 0;
    _PvrPlaybackPath[u8PathID].u32BufferReadPointer     = 0;
    _PvrPlaybackPath[u8PathID].u32BufferWritePointer    = 0;

    /*[01-2]file system part ==========================================================*/
    /*[GROUP2-1]=======================================================================*/
    _PvrPlaybackPath[u8PathID].hReadFile                = INVALID_FILE_HANDLE;
    _PvrPlaybackPath[u8PathID].u32FilePositionKB        = 0;
    _PvrPlaybackPath[u8PathID].u32FileLastPosKB         = 0;
    _PvrPlaybackPath[u8PathID].u32FileSizeKB            = 0;

    /*[GROUP2-2]=======================================================================*/
    _PvrPlaybackPath[u8PathID].u32FileLimitedSizeKB     = 0;
    _PvrPlaybackPath[u8PathID].u32FileValidPosStrKB     = 0;
    _PvrPlaybackPath[u8PathID].u32FileValidPosEndKB     = 0;

    /*[GROUP2-3]=======================================================================*/
    _PvrPlaybackPath[u8PathID].u32FileReadTime          = 0;
    _PvrPlaybackPath[u8PathID].u8FileReadCount          = 0;


    /*[GROUP2-6]=======================================================================*/
    _PvrPlaybackPath[u8PathID].bABLoopSwitch            = FALSE;

    //############################ ************************* ############################
     _PvrPlaybackPath[u8PathID].pstPvrRecordPath         = NULL;     //<---Linking to Record Path in Playback Mode

    //=================================================================================//
    _PvrPlaybackPath[u8PathID].hReadFile = msAPI_PVRFS_FileOpen(pu16PlaybackPathName, PVRFS_OPEN_FOR_READ);
    if(_PvrPlaybackPath[u8PathID].hReadFile == INVALID_FILE_HANDLE)
    {
        _PvrPlaybackPath[u8PathID].bInUse = FALSE;  //release
        return NULL;
    }
#if (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
    MAPP_CIPVR_CIPVRFS_PlaybackFileOpen(pu16PlaybackPathName,PVRFS_OPEN_FOR_READ);
#endif

    if(msAPI_PVRFS_FileRead(_PvrPlaybackPath[u8PathID].hReadFile, PvrGetReadMetadataBufAddr(), META_DATA_SIZE) == 0)    //to check if file is readable
    {
        _PvrPlaybackPath[u8PathID].bInUse = FALSE;  //release
        msAPI_PVRFS_FileClose(_PvrPlaybackPath[u8PathID].hReadFile);
#if (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
    MAPP_CIPVR_CIPVRFS_PlaybackFileClose();
#endif
        _PvrPlaybackPath[u8PathID].hReadFile = INVALID_FILE_HANDLE;
        return NULL;
    }
    _PvrPlaybackPath[u8PathID].u32FilePositionKB = 0;
    msAPI_PVRFS_FileSeek(_PvrPlaybackPath[u8PathID].hReadFile, msAPI_PVR_KToLongLong(_PvrPlaybackPath[u8PathID].u32FilePositionKB) , PVRFS_SEEK_OPTION_FROM_BEGIN);
    //=================================================================================//

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/

    /*[GROUP4-6]=======================================================================*/
    #ifdef S3PLUS
    _PvrPlaybackPath[u8PathID].u32PlayedTunCheckTime    = 0;
    #endif

    /*[GROUP4-7]=======================================================================*/
    _PvrPlaybackPath[u8PathID].bLinkRecord              = FALSE;

    //############################ ************************* ############################

    _PvrPlaybackPath[u8PathID].pstPvrRecordPath  = (_msAPI_PVR_RecordPath *) &_PvrRecordMeataData;   //<---Linking to Record Path in Playback Mode
    msAPI_PVR_PlaybackPathUpdateMetadata(&_PvrPlaybackPath[u8PathID], E_METADATA_UPDATE_FILE);     //Playback load metadata before use

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathOpen\n");

    return &_PvrPlaybackPath[u8PathID];
}
#if (PVR_TS_PACKET_SIZE == 192)
/***********************************************************************************************/
U32 msAPI_PVR_PlaybackGetTotalTimeByTimeStamp(enPvrEncryptType enEncryptionType,U8 u8FileHandle)
{
    LongLong fileLen;
    U32 u32ReadLength,u32Totaltime;
    U32 u32ReadPointer = PVR_TRICK_MODE_ADR;
    U8 buff[8];
    u32Totaltime = 0;
    fileLen = msAPI_PVRFS_FileLength(u8FileHandle);
    //_PvrRecordMeataData.u32RecordedKBytes = (fileLen.Lo - PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE)/1024;
    fileLen.Lo = (fileLen.Lo / 192 - 1) * 192;
    msAPI_PVRFS_FileSeek(u8FileHandle,fileLen,PVRFS_SEEK_OPTION_FROM_BEGIN);
    #ifdef PVR_UTOPIA
        u32ReadLength = msAPI_PVRFS_FileRead(u8FileHandle,  _PA2VA(u32ReadPointer), 192);
    #else
        u32ReadLength = msAPI_PVRFS_FileRead(u8FileHandle,  u32ReadPointer, 192);
    #endif

    if(enEncryptionType != E_PVR_ENCRYPTION_NONE)
    {
#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
         if (u32ReadLength != FAT_MAX_FILE_LENGTH)
        {
             _PVR_AESDMAEncryptDecrypt(_PA2VA(u32ReadPointer), u32ReadLength, E_DECRYPT);
        }
        else
        {
            printf("[PVR][Error] Invalid ReadLength %s %u\n", __FUNCTION__, __LINE__);
        }
#endif
    }

    {
        #ifdef PVR_UTOPIA
            msAPI_MIU_Copy(u32ReadPointer, _VA2PA((U32)&buff[0]), 8, MIU_SDRAM2SDRAM);
        #else
            msAPI_MIU_Copy(u32ReadPointer, XD2PHY(&buff[0]), 8, MIU_SDRAM2SDRAM);
        #endif
        if (buff[4]==0x47)
        {
            u32Totaltime = ((U32)buff[0]<<24)+((U32)buff[1]<<16)+((U32)buff[2]<<8)+(U32)buff[3];
            u32Totaltime = u32Totaltime/9000;
            //_PvrRecordMeataData.u32RecordedPeriod=_PvrRecordMeataData.u32FileValidPeriod=u32Totaltime;
           // _PvrRecordMeataData.u16RecordedAvgRate = (U16)(_PvrRecordMeataData.u32RecordedKBytes/(_PvrRecordMeataData.u32RecordedPeriod/10));
        }
    }
    return u32Totaltime;
}

/***********************************************************************************************/

/***********************************************************************************************/
U32 msAPI_PVR_PlaybackGetPosTimeByTimeStamp(enPvrEncryptType enEncryptionType,U8 u8FileHandle,LongLong filePos)
{
    //LongLong CurfileLen;
    U32 u32ReadLength,u32Totaltime;
    U32 u32ReadPointer = PVR_TRICK_MODE_ADR;
    U8 buff[8];
    u32Totaltime = 0;

    //CurfileLen = msAPI_PVRFS_FileTell(u8FileHandle);

    filePos.Lo = (filePos.Lo / 192 ) * 192;

    msAPI_PVRFS_FileSeek(u8FileHandle,filePos,PVRFS_SEEK_OPTION_FROM_BEGIN);
    #ifdef PVR_UTOPIA
        u32ReadLength = msAPI_PVRFS_FileRead(u8FileHandle,  _PA2VA(u32ReadPointer), 192);
    #else
        u32ReadLength = msAPI_PVRFS_FileRead(u8FileHandle,  u32ReadPointer, 192);
    #endif

    if(enEncryptionType != E_PVR_ENCRYPTION_NONE)
    {
#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
         if (u32ReadLength != FAT_MAX_FILE_LENGTH)
        {
             _PVR_AESDMAEncryptDecrypt(_PA2VA(u32ReadPointer), u32ReadLength, E_DECRYPT);
        }
        else
        {
            printf("[PVR][Error] Invalid ReadLength %s %u\n", __FUNCTION__, __LINE__);
        }
#endif
    }

    {
        #ifdef PVR_UTOPIA
            msAPI_MIU_Copy(u32ReadPointer, _VA2PA((U32)&buff[0]), 8, MIU_SDRAM2SDRAM);
        #else
            msAPI_MIU_Copy(u32ReadPointer, XD2PHY(&buff[0]), 8, MIU_SDRAM2SDRAM);
        #endif

        if (buff[4]==0x47)
        {
            u32Totaltime = ((U32)buff[0]<<24)+((U32)buff[1]<<16)+((U32)buff[2]<<8)+(U32)buff[3];
            //_PvrRecordMeataData.u32RecordedPeriod=_PvrRecordMeataData.u32FileValidPeriod=u32Totaltime;
           // _PvrRecordMeataData.u16RecordedAvgRate = (U16)(_PvrRecordMeataData.u32RecordedKBytes/(_PvrRecordMeataData.u32RecordedPeriod/10));
            u32Totaltime = u32Totaltime/90;
            //_PvrRecordMeataData.u32RecordedPeriod=_PvrRecordMeataData.u32FileValidPeriod=u32Totaltime;
           // _PvrRecordMeataData.u16RecordedAvgRate = (U16)(_PvrRecordMeataData.u32RecordedKBytes/(_PvrRecordMeataData.u32RecordedPeriod/10));
        }
        //msAPI_PVRFS_FileSeek(u8FileHandle,CurfileLen,PVRFS_SEEK_OPTION_FROM_BEGIN);
    }
    return u32Totaltime;
}
/***********************************************************************************************/
#endif

/***************************************************************************************/
void msAPI_PVR_PlaybackCount_Update(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U32 u32WriteLength;
    _PvrRecordMeataData.u16PlaybackCount += 1;

    U16 u16RemainLength  = sizeof(_msAPI_PVR_RecordPath);
    U8  u8WriteLength;
    U8  u8Segment = 0;
    while(1)
    {
            if(u16RemainLength>=184)
            {
                u8WriteLength = 184;
            }
            else if(u16RemainLength>0)
            {
                u8WriteLength = u16RemainLength;
            }
            else
            {
                break;
            }

            #ifdef PVR_8051
                msAPI_MIU_Copy(msAPI_MIU_XData2SDRAMAddr((U16)&_PvrRecordMeataData)+184*u8Segment, PVR_READ_METADATA_BUFFER_ADR+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
            #else
            #ifdef PVR_UTOPIA
                msAPI_MIU_Copy(_VA2PA((U32)&_PvrRecordMeataData)+184*u8Segment,(((PVR_READ_METADATA_BUFFER_MEMORY_TYPE&MIU1)?PVR_READ_METADATA_BUFFER_ADR|MIU_INTERVAL:PVR_READ_METADATA_BUFFER_ADR))+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE , u8WriteLength, MIU_SDRAM2SDRAM);
            #else
                msAPI_MIU_Copy(msAPI_MIU_XData2SDRAMAddr((U32)&_PvrRecordMeataData)+184*u8Segment, PvrGetReadMetadataBufAddr()+PVR_TS_PACKET_SIZE*u8Segment+PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
            #endif
            #endif

            u16RemainLength -= u8WriteLength;
            u8Segment++;
    }

    pstPvrPlaybackPath->u32FilePositionKB = 0;
    msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(pstPvrPlaybackPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN);
    u32WriteLength = msAPI_PVRFS_FileWrite(pstPvrPlaybackPath->hReadFile, PvrGetReadMetadataBufAddr(), PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE);
    pstPvrPlaybackPath->u32FilePositionKB = PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024;
    msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(pstPvrPlaybackPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN);

}
/***************************************************************************************/

enPvrApiStatus  msAPI_PVR_PlaybackPathSet(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
        if (DMX_FILTER_STATUS_OK!= MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_MEM, FALSE, TRUE, TRUE))
        {
            MS_DEBUG_MSG(printf("[VerDemux][%06d] switch to file-in fail\n", __LINE__));
        }
    #else
    msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , MSAPI_DMX_DATAPATH_PACKETMODE_192);
    #endif
    #else
    msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , 0);
    #endif

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_SetPlaybackSpeed(0);
    #endif
    #else
    pstPvrPlaybackPath->u32CurTimerDelay = 0;
    pstPvrPlaybackPath->u32PrvTimerDelay = 0;
    msAPI_DMX_SetPlaybackSpeed(MAGIC_NUMBER_TIMER_DELAY); //init value at begining
    #endif
  //printf("timestamp nop; playback setbuf->setspeed; cmdq nop\n");

    /*[GROUP1-2]=======================================================================*/
    pstPvrPlaybackPath->u32BufferReadPointer  = pstPvrPlaybackPath->u32BufferStart;
    pstPvrPlaybackPath->u32BufferWritePointer = pstPvrPlaybackPath->u32BufferStart;

    /*[01-2]file system part ==========================================================*/

    //############################ ************************* ############################
    pstPvrPlaybackPath->pstPvrRecordPath  = (_msAPI_PVR_RecordPath *) &_PvrRecordMeataData;   //<---Linking to Record Path in Playback Mode
    //############################ ************************* ############################

    //====================== time stamp / ts header checking ==========================//
    #ifndef S3PLUS
    #if 1
    {
        U8 u8PacketHeader[8];

        msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024), PVRFS_SEEK_OPTION_FROM_BEGIN);
        #ifdef PVR_8051
        msAPI_PVRFS_FileRead(pstPvrPlaybackPath->hReadFile, msAPI_MIU_XData2SDRAMAddr((U16)u8PacketHeader), 8);
        #else
        msAPI_PVRFS_FileRead(pstPvrPlaybackPath->hReadFile, pstPvrPlaybackPath->u32BufferStart, 16); //16X aligment for AES

        //flush memory before read it
        MsOS_FlushMemory();
#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
        if(pstPvrPlaybackPath->pstPvrRecordPath->enEncryptionType != E_PVR_ENCRYPTION_NONE)
        {
            _PVR_AESDMAEncryptDecrypt(pstPvrPlaybackPath->u32BufferStart, 16, E_DECRYPT);
        }
#endif
        u8PacketHeader[0] = *(U8 *)(pstPvrPlaybackPath->u32BufferStart+0);
        u8PacketHeader[1] = *(U8 *)(pstPvrPlaybackPath->u32BufferStart+1);
        u8PacketHeader[2] = *(U8 *)(pstPvrPlaybackPath->u32BufferStart+2);
        u8PacketHeader[3] = *(U8 *)(pstPvrPlaybackPath->u32BufferStart+3);
        u8PacketHeader[4] = *(U8 *)(pstPvrPlaybackPath->u32BufferStart+4);
        //]
        #endif
        msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(0                  ), PVRFS_SEEK_OPTION_FROM_BEGIN);
        if(u8PacketHeader[4] != 0x47)
        {
              //printf("playback packet error0, why? \n");
            //return E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR;
        }
        else
        {
          //printf("time_stamp_file_s =%02bx %02bx %02bx %02bx \n", u8PacketHeader[0], u8PacketHeader[1], u8PacketHeader[2], u8PacketHeader[3]);
        }
        pstPvrPlaybackPath->bNeedSetTimeStamp=TRUE;
    }
    #endif
    #endif
    //====================== time stamp / ts header checking ==========================//

    msAPI_PVR_PlaybackPathUpdateMetadata(pstPvrPlaybackPath, E_METADATA_UPDATE_FILE);     //Playback load metadata before use

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathSet\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_PlaybackPathAddPID(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath, U16 u16PID, MSAPI_DMX_FILTER_TYPE enFltType)
{
    U8 u8FID;

    /*[01-0]pvr part ==================================================================*/

    if(pstPvrPlaybackPath  == NULL)
    {
        // Fix Mantis 983867
        // If first time to do Timeshift, then press stop, it will go to here but pstPvrPlaybackPath is NULL.
        // If pstPvrPlaybackPath is NULL, then it will system crash when the following code go to pstPvrPlaybackPath->u8FilterID[u8FID]
        return E_PVR_API_STATUS_PLAYBACK_NO_FILTER;
    }

    /*[01-1]demux part ================================================================*/
    /*[GROUP1-1]=======================================================================*/
    if(u16PID == MSAPI_DMX_INVALID_PID)
    {
      //printf("Invalid PID\n");
        return E_PVR_API_STATUS_INVALID_PID;
    }

#ifdef PVR_UTOPIA
    //MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_MEM, TRUE, TRUE, TRUE);
#else
    msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_MIU, MSAPI_DMX_DATAPATH_IN_MIU, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
#endif
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] == MSAPI_DMX_INVALID_FLT_ID)
        {
            pstPvrPlaybackPath->u16PID[u8FID] = u16PID;
            pstPvrPlaybackPath->enFilterType[u8FID] = enFltType;
         #ifdef PVR_UTOPIA
            msAPI_DMX_StartFilter(pstPvrPlaybackPath->u16PID[u8FID], pstPvrPlaybackPath->enFilterType[u8FID]|MSAPI_DMX_FILTER_SOURCE_TYPE_FILE, &pstPvrPlaybackPath->u8FilterID[u8FID]);
         #else
            msAPI_DMX_StartFilter(pstPvrPlaybackPath->u16PID[u8FID], pstPvrPlaybackPath->enFilterType[u8FID], &pstPvrPlaybackPath->u8FilterID[u8FID]);
         #endif
            if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
            {
                break;
            }
            else if(u8FID == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))
            {
              //printf("No More Filter Available for Playbacking \n");
                break;
            }
        }
    }

    #ifndef PVR_UTOPIA
    msAPI_DMX_RestoreDataPath();
    #endif

    /*[01-2]file system part ==========================================================*/


    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathAddPID\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathDelPID(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath, U16 u16PID, MSAPI_DMX_FILTER_TYPE enFltType)
{
    U8 u8FID;

    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    /*[GROUP1-1]=======================================================================*/
    if(u16PID == MSAPI_DMX_INVALID_PID)
    {
      //printf("Invalid PID\n");
        return E_PVR_API_STATUS_INVALID_PID;
    }

#ifdef PVR_UTOPIA
    //MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_MEM, TRUE, TRUE, TRUE);
#else
    msAPI_DMX_SetDataPath(MSAPI_DMX_DATAPATH_MIU, MSAPI_DMX_DATAPATH_IN_MIU, MSAPI_DMX_DATAPATH_SYNCMODE_EXTERNAL);
#endif
    for(u8FID=0; u8FID<MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if((pstPvrPlaybackPath->u8FilterID[u8FID]   != MSAPI_DMX_INVALID_FLT_ID) &&
           (pstPvrPlaybackPath->u16PID[u8FID]       == u16PID                  ) &&
           (pstPvrPlaybackPath->enFilterType[u8FID] == enFltType ) )
        {
            msAPI_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            msAPI_DMX_Close(pstPvrPlaybackPath->u8FilterID[u8FID]);
            pstPvrPlaybackPath->u8FilterID[u8FID] = MSAPI_DMX_INVALID_FLT_ID;
          //printf("Stop PID at FID=0x%02bx for PID=0x%04x TYPE=0x%02bx \n", pstPvrPlaybackPath->u8FilterID[u8FID], pstPvrPlaybackPath->u16PID[u8FID], pstPvrPlaybackPath->enFilterType[u8FID]);
            break;
        }
        else if(u8FID == (MSAPI_DMX_RECORD_FILTER_NUMBER-1))
        {
          //printf("No Filter Matched \n");
            break;
        }
    }

    #ifndef PVR_UTOPIA
    msAPI_DMX_RestoreDataPath();
    #endif

    /*[01-2]file system part ==========================================================*/


    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathDelPID\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_PlaybackPathStart(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
#ifndef S3PLUS
    #ifdef PVR_UTOPIA
        DMX_Filein_info g_FileinInfo;
        g_FileinInfo.PKT_Mode = DMX_PKTMODE_192;
        g_FileinInfo.Rate = 0x0;

        if (DMX_FILTER_STATUS_OK!=MApi_DMX_Filein_Info(&g_FileinInfo))
        {
            ASSERT(0);
        }

        MApi_DMX_Pvr_TimeStampEnable();
        #ifdef PVR_UTOPIA
            if(!MApi_DMX_Filein_IsIdle())
            {
                MApi_DMX_Filein_CMDQ_Reset();
            }
            MApi_DMX_Filein_CMDQ_GetEmptyNum(&_u32MaxDmxCmdSlot);
            //printf("_u8MaxDmxCmdSlot=%lu\n",_u32MaxDmxCmdSlot);
        #endif

        pstPvrPlaybackPath->u32BufferWritePointer = pstPvrPlaybackPath->u32BufferStart;
        pstPvrPlaybackPath->u32BufferReadPointer = pstPvrPlaybackPath->u32BufferStart;
        u32PvrPauseTimeStamp = 0;
    #else
        msAPI_DMX_TimeStampEnable();
        u32PvrPauseTimeStamp = 0;
    #endif
    u32PreWritePointer = 0;
#endif
    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_PlaybackEnable();
    #endif

  //printf("timestamp enable; playback enable; cmdq nop\n");

    /*[01-2]file system part ==========================================================*/
    pstPvrPlaybackPath->u32FilePositionKB = pstPvrPlaybackPath->u32FileValidPosStrKB;   //jump to LPN_pos
    msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(pstPvrPlaybackPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN);

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/
    /*[GROUP4-6]=======================================================================*/
    #ifdef S3PLUS
    pstPvrPlaybackPath->u32PlayedTunCheckTime = msAPI_Timer_GetTime0();
    #endif

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathStart\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_PlaybackPathForwardOutput(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U32 u32ReadPointer;
    U32 u32ReadLength;
    U32 u32Time1, u32Time2;
    BOOL bCanSetStamp=FALSE;

    /*[01-0]pvr part ==================================================================*/
  //printf("-\r");

    /*[01-1]demux part ================================================================*/
    #ifdef S3PLUS

    if(pstPvrPlaybackPath->u32CurTimerDelay != pstPvrPlaybackPath->u32PrvTimerDelay)
    {
        switch (pstPvrPlaybackPath->enPlaySpeed)
       {
        case E_PLAY_SPEED_1X:
            msAPI_DMX_SetPlaybackSpeed(pstPvrPlaybackPath->u32CurTimerDelay);
            break;

        case E_PLAY_SPEED_2X:
            msAPI_DMX_SetPlaybackSpeed(pstPvrPlaybackPath->u32CurTimerDelay*3/5);
            break;

        default:
            msAPI_DMX_SetPlaybackSpeed(pstPvrPlaybackPath->u32CurTimerDelay/4);
            break;
        }
        pstPvrPlaybackPath->u32PrvTimerDelay = pstPvrPlaybackPath->u32CurTimerDelay;
    }
    #endif

    /*[01-2]file system part ==========================================================*/

    //====================== time stamp / ts header checking ==========================//
    #ifndef S3PLUS
    {
        U32 u32TimeStamp;
        U32 u32TimeCounter;

        //time stamp ==================================================================//
    #ifdef PVR_8051
        XBYTE[0x15fb]=0x47;
        u32TimeStamp  = XBYTE[0x15d4];
        u32TimeStamp  = u32TimeStamp<<8;
        XBYTE[0x15fb]=0x48;
        u32TimeStamp |= XBYTE[0x15d6];
        u32TimeStamp  = u32TimeStamp<<8;
        u32TimeStamp |= XBYTE[0x15d5];
        u32TimeStamp  = u32TimeStamp<<8;
        u32TimeStamp |= XBYTE[0x15d4];
    #else
        //#ifdef MIPS_CHAKRA //not mips
            #ifdef PVR_UTOPIA_T3
                MApi_DMX_GetFileInTimeStamp(&u32TimeStamp);
            #else
            {
                U8 *Tstamp, *Tstamp2;
                U32 u32Tstamp,u32Tstamp2;
                Tstamp = (U8 *)(pstPvrPlaybackPath->u32BufferReadPointer);
                Tstamp2= (U8 *)(pstPvrPlaybackPath->u32BufferWritePointer);
                u32Tstamp= Tstamp[0]<<24 | Tstamp[1]<<16 | Tstamp[2]<<8 | Tstamp[3];
                u32Tstamp2= Tstamp2[0]<<24 | Tstamp2[1]<<16 | Tstamp2[2]<<8 | Tstamp2[3];
                if(u32Tstamp > u32Tstamp2)
                    u32TimeStamp = u32Tstamp;
                else
                    u32TimeStamp = u32Tstamp2;


            }
            #endif
/*
        #else
        MDrv_WriteByte(0x15fb,0x47);
        u32TimeStamp  = MDrv_ReadByte(0x15d4);
        u32TimeStamp  = u32TimeStamp<<8;
        MDrv_WriteByte(0x15fb,0x48);
        u32TimeStamp |= MDrv_ReadByte(0x15d6);
        u32TimeStamp  = u32TimeStamp<<8;
        u32TimeStamp |= MDrv_ReadByte(0x15d5);
        u32TimeStamp  = u32TimeStamp<<8;
        u32TimeStamp |= MDrv_ReadByte(0x15d4);
        #endif
*/
    #endif
        //time counter ================================================================//
        #ifdef PVR_UTOPIA
        MApi_DMX_Pvr_GetPlaybackStamp(&u32TimeCounter);
        //printf("u32TimeCounter=%x\n",u32TimeCounter);
        #else
        u32TimeCounter = msAPI_DMX_GetPlaybackStamp();
        #endif

        #ifndef S3PLUS
        if(u32TimeStamp == 0xFFFFFFFF)
        {
            #ifdef PVR_UTOPIA
            MApi_DMX_Pvr_TimeStampDisable();
            #else
            msAPI_DMX_TimeStampDisable();
            #endif

            msAPI_Timer_Delayms(100);

            #ifdef PVR_UTOPIA
            MApi_DMX_Pvr_TimeStampEnable();
            MApi_DMX_Pvr_SetPlaybackStamp(0x00000000);
            #else
            msAPI_DMX_TimeStampEnable();
            msAPI_DMX_SetPlaybackStamp(0x00000000);
            #endif
        }
        else
        #endif

        //reset time counter ==========================================================//
        if(((u32TimeStamp > u32TimeCounter) && (u32TimeStamp - u32TimeCounter > 0x20000)) ||
           ((u32TimeCounter > u32TimeStamp) && (u32TimeCounter - u32TimeStamp > 0x20000))   )
        {
          //printf("reset time_counter: time_ts_stamp =0x%08lx / time_counter = 0x%08lx \n", u32TimeStamp, u32TimeCounter);
            if ((0xFFFFFFFF - u32TimeStamp) > 0x1000)
                u32TimeStamp  = u32TimeStamp+0x1000;

            #ifdef PVR_UTOPIA
            MApi_DMX_Pvr_SetPlaybackStamp(u32TimeStamp);
            #else
            msAPI_DMX_SetPlaybackStamp(u32TimeStamp);
            #endif
        }
        else if(((u32TimeStamp > u32TimeCounter) && (u32TimeStamp - u32TimeCounter > 0x2000)) ||
                ((u32TimeCounter > u32TimeStamp) && (u32TimeCounter - u32TimeStamp > 0x2000))   )
        {
          //printf("warning!!!!!!!!!!!: time_ts_stamp =0x%08lx / time_counter = 0x%08lx \n", u32TimeStamp, u32TimeCounter);
        }
        else
        {
          //printf("                  : time_ts_stamp =0x%08lx / time_counter = 0x%08lx \n", u32TimeStamp, u32TimeCounter);
        }
        //=============================================================================//
    }
    #endif
    //====================== time stamp / ts header checking ==========================//

#ifdef PVR_UTOPIA
    //calculate a virtual read point for PARADISE VERSION
    {
        U32 EmptySlotNum;
        if(MApi_DMX_Filein_IsIdle())
        {
            //printf("Idle\n");
        }
        else
        {
            MApi_DMX_Filein_CMDQ_GetEmptyNum(&EmptySlotNum); //the return number is not correct, need to check DMX driver
        #if (PVR_READ_SDRAM_LEN >= (PVR_FILE_IN_SIZE*3))
            U32 LimitSlotNum = 0;
            if(pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_STEPIN)
            {
                LimitSlotNum = 5;
            }
            else
            {
                LimitSlotNum = 10;
            }
            if(EmptySlotNum > _u32MaxDmxCmdSlot-LimitSlotNum)
        #else
            if(EmptySlotNum > _u32MaxDmxCmdSlot-5)
        #endif
            {
                //printf("EmptySlotNum=%d\n",EmptySlotNum);
            }
            else
            {
                //printf("Queue Full,%d\n",EmptySlotNum);
                //printf(".");
                return E_PVR_API_STATUS_OK;
            }
        }
        u32ReadPointer = pstPvrPlaybackPath->u32BufferReadPointer;
        //printf("u32ReadPointer=%x\n",u32ReadPointer);
    }
#endif
#ifdef PVR_UTOPIA
    {
        U32 u32ReadWriteDistanceKB;
        u32ReadLength = PVR_FILE_IN_SIZE;
        if ((pstPvrPlaybackPath->u32BufferStart + pstPvrPlaybackPath->u32BufferLength) < (pstPvrPlaybackPath->u32BufferWritePointer + PVR_FILE_IN_SIZE))
        {
            u32ReadLength = pstPvrPlaybackPath->u32BufferStart + pstPvrPlaybackPath->u32BufferLength - pstPvrPlaybackPath->u32BufferWritePointer ;
        }

        u32ReadWriteDistanceKB = pstPvrPlaybackPath->u32FileValidPosEndKB - pstPvrPlaybackPath->u32FilePositionKB;
        if((u32ReadLength/1024) > u32ReadWriteDistanceKB)
        {
            u32ReadLength = u32ReadWriteDistanceKB*1024;
            u32ReadLength = ALIGNMINREAD(u32ReadLength);
        }

        if ( (pstPvrPlaybackPath->u32FileLimitedSizeKB !=0) && ((pstPvrPlaybackPath->u32FilePositionKB + u32ReadLength/1024) > pstPvrPlaybackPath->u32FileLimitedSizeKB) )
        {
            u32ReadLength = (pstPvrPlaybackPath->u32FileLimitedSizeKB - pstPvrPlaybackPath->u32FilePositionKB)*1024;
        }

        if(u32ReadLength == 0)
        {
          //printf("<\r");
            return E_PVR_API_STATUS_OK;
        }
    }
#else
    {
        U32 u32ReadWriteDistanceKB;

        /*[##-1]check read address & length ===============================================*/
    #ifdef S3PLUS //prevent S3P HW bug: to prevent read pointer from being equal to write pointer, if equal, it will return wrong read pointer
        if( u32ReadPointer == pstPvrPlaybackPath->u32BufferWritePointer)
        {
            u32ReadLength = pstPvrPlaybackPath->u32BufferLength*4/5;
        }
        else if( u32ReadPointer < pstPvrPlaybackPath->u32BufferWritePointer)
        {
            if(pstPvrPlaybackPath->u32BufferReadPointer == u32ReadPointer)
                u32ReadLength = 0;
            else
                u32ReadLength = pstPvrPlaybackPath->u32BufferStart + pstPvrPlaybackPath->u32BufferLength - pstPvrPlaybackPath->u32BufferWritePointer;

        }
        else if(pstPvrPlaybackPath->u32BufferWritePointer < u32ReadPointer)
        {
            u32ReadLength = u32ReadPointer - pstPvrPlaybackPath->u32BufferWritePointer;
            if(u32ReadLength > pstPvrPlaybackPath->u32BufferLength*4/5)
                u32ReadLength = u32ReadLength - pstPvrPlaybackPath->u32BufferLength*4/5;
            else
                u32ReadLength = 0;
        }
        else
        {
            u32ReadLength = 0;
        }
    #else
        if( u32ReadPointer <= pstPvrPlaybackPath->u32BufferWritePointer)
        {
            u32ReadLength = pstPvrPlaybackPath->u32BufferStart + pstPvrPlaybackPath->u32BufferLength - pstPvrPlaybackPath->u32BufferWritePointer;
        }
        else if(pstPvrPlaybackPath->u32BufferWritePointer < u32ReadPointer)
        {
            u32ReadLength = u32ReadPointer - pstPvrPlaybackPath->u32BufferWritePointer;
        }
        else
        {
            u32ReadLength = 0;
        }
    #endif
        pstPvrPlaybackPath->u32BufferReadPointer = u32ReadPointer;

        u32ReadWriteDistanceKB = pstPvrPlaybackPath->u32FileValidPosEndKB - pstPvrPlaybackPath->u32FilePositionKB;
        if((u32ReadLength/1024) > u32ReadWriteDistanceKB)
        {
            u32ReadLength = u32ReadWriteDistanceKB*1024;
        }

        if (u32ReadLength > MAX_READ_LENGTH)
        {
            u32ReadLength = MAX_READ_LENGTH;
            if ((pstPvrPlaybackPath->u32FilePositionKB + u32ReadLength/1024) > pstPvrPlaybackPath->u32FileLimitedSizeKB)
            {
                u32ReadLength = (pstPvrPlaybackPath->u32FileLimitedSizeKB - pstPvrPlaybackPath->u32FilePositionKB)*1024;
            }
        }
        else
        {
            if ((pstPvrPlaybackPath->u32FilePositionKB + u32ReadLength/1024) > pstPvrPlaybackPath->u32FileLimitedSizeKB)
            {
                u32ReadLength = (pstPvrPlaybackPath->u32FileLimitedSizeKB - pstPvrPlaybackPath->u32FilePositionKB)*1024;
            }
            else if(pstPvrPlaybackPath->u32BufferWritePointer > (pstPvrPlaybackPath->u32BufferStart + pstPvrPlaybackPath->u32BufferLength - MIN_READ_LENGTH))
            {
                u32ReadLength = u32ReadLength;    //for special case in the gap
              //printf("special_read_gap=0x%08lx \n", u32ReadLength);
            }
            else
            {
                u32ReadLength = ALIGNMINREAD(u32ReadLength);
            }

            if(u32ReadLength == 0)
            {
              //printf("<\r");
                return E_PVR_API_STATUS_OK;
            }
        }
    }
#endif
#ifndef S3PLUS
    if(pstPvrPlaybackPath->bNeedSetTimeStamp && (PVR_TS_PACKET_SIZE==192))
    {
        LongLong llTemp1,llTemp2;
        llTemp1=msAPI_PVRFS_FileTell(pstPvrPlaybackPath->hReadFile);
        llTemp2=msAPI_PVR_KToLongLong(PVR_MAX_PROGRAMME_PER_FILE * META_DATA_SIZE/1024);
        if(llTemp1.Hi || llTemp1.Lo>=llTemp2.Lo)
        {
            if(llTemp1.Lo>=llTemp2.Lo)
            {
                llTemp1.Lo-=llTemp2.Lo;
            }
            else
            {
                llTemp1.Hi--;
                llTemp1.Lo +=(1+~llTemp2.Lo);
            }
            llTemp1.Hi = (llTemp1.Hi%PVR_TS_PACKET_SIZE)*(0xFFFFFFFF%PVR_TS_PACKET_SIZE+1);
            llTemp1.Lo = (llTemp1.Lo%PVR_TS_PACKET_SIZE);
            if(((llTemp1.Hi+llTemp1.Lo)%PVR_TS_PACKET_SIZE)==0)
            {
                bCanSetStamp=TRUE;
            }
        }
    }
#endif
    /*[##-2]read it ===================================================================*/
    u32Time1 = msAPI_Timer_GetTime0();
    u32ReadLength = msAPI_PVRFS_FileRead(pstPvrPlaybackPath->hReadFile,  pstPvrPlaybackPath->u32BufferWritePointer, u32ReadLength);
    u32Time2 = msAPI_Timer_GetTime0();

    if (u32ReadLength == FAT_MAX_FILE_LENGTH)
    {
        return E_PVR_API_STATUS_OK;
    }

    /*[##-2-1]decrypt data ============================================================*/
#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
    if ((u32ReadLength != 0) && (pstPvrPlaybackPath->u32FilePositionKB >= TOTAL_META_DATA_SIZEKB))
    {
        //flush memory before read it
        MsOS_FlushMemory();
        if(pstPvrPlaybackPath->pstPvrRecordPath->enEncryptionType != E_PVR_ENCRYPTION_NONE)
        {
            _PVR_AESDMAEncryptDecrypt(pstPvrPlaybackPath->u32BufferWritePointer, u32ReadLength, E_DECRYPT);
        }
    }
#endif
    /*[GROUP2-3]=======================================================================*/
    pstPvrPlaybackPath->u32FileReadTime += (u32Time2-u32Time1);
    pstPvrPlaybackPath->u8FileReadCount++;

    if (u32ReadLength == 0)
    {
        //printf("read error, why?, line %lu\n",(U32)__LINE__);
        return E_PVR_API_STATUS_OK;
    }
    else
    {
    #ifndef S3PLUS
        if(pstPvrPlaybackPath->bNeedSetTimeStamp && bCanSetStamp)
        {
            U32 u32TimeStamp;
            U8 *u8PacketHeader=(U8 *)(pstPvrPlaybackPath->u32BufferWritePointer);
            u32TimeStamp  = u8PacketHeader[0];
            u32TimeStamp  = u32TimeStamp << 8;
            u32TimeStamp |= u8PacketHeader[1];
            u32TimeStamp  = u32TimeStamp << 8;
            u32TimeStamp |= u8PacketHeader[2];
            u32TimeStamp  = u32TimeStamp << 8;
            u32TimeStamp |= u8PacketHeader[3];

    #ifdef PVR_UTOPIA
            MApi_DMX_Pvr_SetPlaybackStamp(u32TimeStamp);
    #else
            msAPI_DMX_SetPlaybackStamp(u32TimeStamp);
    #endif
            pstPvrPlaybackPath->bNeedSetTimeStamp=FALSE;
        }
    #endif

    #ifdef PVR_UTOPIA
        //printf("u32BufferWritePointer=%x,%x\n",_VA2PA(pstPvrPlaybackPath->u32BufferWritePointer),pstPvrPlaybackPath->u32BufferWritePointer);
        if (DMX_FILTER_STATUS_OK!=MApi_DMX_Filein_Start(DMX_PES_NO_BYPASS_FIFO, _VA2PA(pstPvrPlaybackPath->u32BufferWritePointer), u32ReadLength))
        {
            ASSERT(0);
        }
        //extern void MApi_VDEC_DbgDumpStatus(void);
        //MApi_VDEC_DbgDumpStatus();
        pstPvrPlaybackPath->u32BufferReadPointer = pstPvrPlaybackPath->u32BufferWritePointer;
    #endif
    }

    /*[GROUP2-4]=======================================================================*/
    if(pstPvrPlaybackPath->u16FileReadAccumulatorKB > (u32ReadLength/1024))
    {
        pstPvrPlaybackPath->u16FileReadAccumulatorKB -= (u32ReadLength/1024);
    }
    else
    {
        pstPvrPlaybackPath->u16FileReadAccumulatorKB = 0;
    }

    //====================== time stamp / ts header checking ==========================//
    #if (!ENABLE_PVR_AESDMA)
    if(pstPvrPlaybackPath->pstPvrRecordPath->enEncryptionType == E_PVR_ENCRYPTION_NONE)
    {
        U32 u32BufferAlignPacket;
        #ifdef PVR_8051
        U16 u16Segment;
        U16 u16Offset;
        static U8 u8PktOffset1=0;
        static U8 u8PktOffset2=0;
        #endif
        //write_pointer ##===================
        u32BufferAlignPacket = pstPvrPlaybackPath->u32BufferWritePointer-pstPvrPlaybackPath->u32BufferStart;
        #ifndef S3PLUS
        u32BufferAlignPacket = ALIGNMINREAD(u32BufferAlignPacket);
        #else
        u32BufferAlignPacket = ((u32BufferAlignPacket/188)*188);
        #endif
        u32BufferAlignPacket+= pstPvrPlaybackPath->u32BufferStart;
        #ifdef PVR_8051
        u16Segment = u32BufferAlignPacket/4096;
        u16Offset  = u32BufferAlignPacket%4096;
        MDrv_Sys_SetXdataWindow1Base(u16Segment);
        #ifndef S3PLUS
        if(XBYTE[u16Offset+u8PktOffset1+0xf004] != 0x47)
        #else
        if(u16Offset >= (4096-188*2))   //prevent overflow
        {
            u16Offset -= 188*2;
        }
        if(XBYTE[u16Offset+u8PktOffset1+0xf000] != 0x47)
        #endif
        #else
        if(*(U8 *)(u32BufferAlignPacket+4) != 0x47)
        #endif
        {
            #ifndef S3PLUS
            MS_DEBUG_MSG(printf("playback packet error-1 at buff_pos=0x%08lx \n", u32BufferAlignPacket));
            pstPvrPlaybackPath->u16PlayedErrCount3++;
            if (pstPvrPlaybackPath->u16PlayedErrCount3 > PLAYBACK_BUFF_ERR_COUNT)
            {
                //return E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR;
            }
            #else
            for(u8PktOffset1=0;u8PktOffset1<188; u8PktOffset1++)
            {
                if((XBYTE[u16Offset+u8PktOffset1+0xf000] == 0x47) &&
                   (XBYTE[u16Offset+u8PktOffset1+0xf0bc] == 0x47)   )
                {
                    pstPvrPlaybackPath->u16PlayedErrCount3++;
                    if(pstPvrPlaybackPath->u16PlayedErrCount3 <= 2)
                    {
                      printf("Play Packet Offset-1 become %02bu \n", u8PktOffset1);
                        break;
                    }
                    else
                    {
                        printf("Warning: Play Packet Offset-1 become %02bu \n", u8PktOffset1);
                        break;
                      //return E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR;
                    }
                }
            }
            #endif
        }
        else
        {
            pstPvrPlaybackPath->u16PlayedErrCount3 = 0;
          //printf("time_stamp_file   =%02bx %02bx %02bx %02bx \n", XBYTE[u16Offset+0xf000], XBYTE[u16Offset+0xf001], XBYTE[u16Offset+0xf002], XBYTE[u16Offset+0xf003]);
        }
        #ifdef PVR_8051
        MDrv_Sys_ReleaseXdataWindow1();
        #endif
        //buffer_start ##====================
        #ifdef PVR_8051
        u16Segment = pstPvrPlaybackPath->u32BufferStart/4096;
        u16Offset  = pstPvrPlaybackPath->u32BufferStart%4096;
        MDrv_Sys_SetXdataWindow1Base(u16Segment);
        #ifndef S3PLUS
        if(XBYTE[u16Offset+u8PktOffset2+0xf004] != 0x47)
        #else
        if(u16Offset >= (4096-188*2))   //prevent overflow
        {
            u16Offset -= 188*2;
        }
        if(XBYTE[u16Offset+u8PktOffset2+0xf000] != 0x47)
        #endif
        #else
        if(*(U8 *)(pstPvrPlaybackPath->u32BufferStart+4) != 0x47)
        #endif
        {
            #ifndef S3PLUS
          MS_DEBUG_MSG(printf("playback packet error-2 at buff_pos=0x%08lx \n", pstPvrPlaybackPath->u32BufferStart));
            pstPvrPlaybackPath->u16PlayedErrCount3++;
            if (pstPvrPlaybackPath->u16PlayedErrCount3 > PLAYBACK_BUFF_ERR_COUNT)
            {
                //return E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR;
            }
            #else
            for(u8PktOffset2=0;u8PktOffset2<188; u8PktOffset2++)
            {
                if((XBYTE[u16Offset+u8PktOffset2+0xf000] == 0x47) &&
                   (XBYTE[u16Offset+u8PktOffset2+0xf0bc] == 0x47)   )
                {
                    pstPvrPlaybackPath->u16PlayedErrCount3++;
                    if(pstPvrPlaybackPath->u16PlayedErrCount3 <= 2)
                    {
                      printf("Play Packet Offset-2 become %02bu \n", u8PktOffset2);
                        break;
                    }
                    else
                    {
                        printf("Warning: Play Packet Offset-2 become %02bu \n", u8PktOffset2);
                        break;
                      //return E_PVR_API_STATUS_PLAYBACK_BUFFER_ERROR;
                    }
                }
            }
            #endif
        }
        else
        {
          //printf("time_stamp_file   =%02bx %02bx %02bx %02bx \n", XBYTE[u16Offset+0xf000], XBYTE[u16Offset+0xf001], XBYTE[u16Offset+0xf002], XBYTE[u16Offset+0xf003]);
        }
        #ifdef PVR_8051
        MDrv_Sys_ReleaseXdataWindow1();
        #endif
        // ================================##
    }
    #endif
    //====================== time stamp / ts header checking ==========================//


    /*[##-3]statistics ================================================================*/
    /*[GROUP1-2]=======================================================================*/
    pstPvrPlaybackPath->u32BufferWritePointer += u32ReadLength;
    if(pstPvrPlaybackPath->u32BufferWritePointer == (pstPvrPlaybackPath->u32BufferStart + pstPvrPlaybackPath->u32BufferLength))
    {
        pstPvrPlaybackPath->u32BufferWritePointer = pstPvrPlaybackPath->u32BufferStart;
    }

    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_SetPlaybackWrite(pstPvrPlaybackPath->u32BufferWritePointer);
    #endif

    /*[GROUP2-1]=======================================================================*/
    pstPvrPlaybackPath->u32FilePositionKB   += u32ReadLength/1024;
    if (pstPvrPlaybackPath->u32FilePositionKB >= pstPvrPlaybackPath->u32FileLimitedSizeKB)
    {
      //LongLong u64FileLength;
        pstPvrPlaybackPath->u32FilePositionKB = 0;
        msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(pstPvrPlaybackPath->u32FilePositionKB) , PVRFS_SEEK_OPTION_FROM_BEGIN);
      //u64FileLength = msAPI_PVRFS_FileLength(pstPvrPlaybackPath->hReadFile);
      //printf("#################read-file-siz=0x%08lx|%08lx##################\n", u64FileLength.Hi, u64FileLength.Lo);
      //u64FileLength = msAPI_PVRFS_FileTell(pstPvrPlaybackPath->hReadFile);
      //printf("#################read-file-pos=0x%08lx|%08lx##################\n", u64FileLength.Hi, u64FileLength.Lo);

        msAPI_PVR_PlaybackPathUpdateMetadata(pstPvrPlaybackPath, E_METADATA_UPDATE_FILE);
    }

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathForwardOutput\n");

    return E_PVR_API_STATUS_OK;
}


/***************************************************************************************/


static U32 GetLinearFilePos(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath ,U32 u16JumpSecond,U32 u32FileValidPosStrKB,U32 u32FileValidPosEndKB)
{
    U32 low,high,mid;
    U32 mid_time;
    U32 Jump_time;

    if (u16JumpSecond <= 0)
    {
        return u32FileValidPosStrKB;
    }

    if(MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT)
    {
        Jump_time = MApp_TimeShift_GetRecordEndTimeSec() - MApp_TimeShift_GetRecordStartTimeSec();
    }
    else
    {

        //Jump_time = MApp_Playback_GetRecordEndTimeSec() - MApp_Playback_GetRecordStartTimeSec();
        Jump_time = MApp_Playback_GetTotalTimeSec();
    }
    Jump_time = Jump_time*1000;

    if (u16JumpSecond >= Jump_time)
    {
        if((u32FileValidPosEndKB*1024) % PVR_TS_PACKET_SIZE)
        {
            return u32FileValidPosEndKB;// -(u32FileValidPosEndKB*1024) % PVR_TS_PACKET_SIZE;
        }
        else
        {
            return u32FileValidPosEndKB - PVR_TS_PACKET_SIZE;
        }
    }
    if(u16JumpSecond <= 0)
    {
        return u32FileValidPosStrKB;
    }

    low = u32FileValidPosStrKB/PVR_TS_PACKET_SIZE;
    high = u32FileValidPosEndKB/PVR_TS_PACKET_SIZE;

    if (low >= high)
    {
        return 0;
    }
    else
    {
        mid = (low + high) / 2;
        while (low <= high)
        {
            mid = (low + high) / 2;
            mid_time = msAPI_PVR_PlaybackGetPosTimeByTimeStamp(pstPvrPlaybackPath->pstPvrRecordPath->enEncryptionType, pstPvrPlaybackPath->hReadFile,msAPI_PVR_KToLongLong(mid*PVR_TS_PACKET_SIZE));
            if (mid_time == u16JumpSecond)
            {
                return  mid*PVR_TS_PACKET_SIZE;
            }
            else if (mid_time > u16JumpSecond)
            {
                high = mid - 1;
            }
            else if (mid_time < u16JumpSecond)
            {
                low = mid + 1;
            }
        }
        return  mid*PVR_TS_PACKET_SIZE; // target_second not found, return nearest
    }
}


/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathJumpForward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath, U32 u16JumpSecond, enPvrJumpBufferMode enBufferMode)
{
    #define READ_LENGTH_UNIT        3       //3K
    #define ALIGNLENGTHUNIT(x)      ((x/READ_LENGTH_UNIT)*READ_LENGTH_UNIT)

    U32 u32JumpKByte;
    U32 mid_time;

    /*[01-0]pvr part ==================================================================*/
    if(pstPvrPlaybackPath->enDirection != E_PLAYBACK_PATH_DIRECTION_FASTFORWARD)    //Fast Forward always (8x/16x/32x)
    {
        pstPvrPlaybackPath->enDirection = E_PLAYBACK_PATH_DIRECTION_JUMPFORWARD;
    }

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    u32PvrPauseTimeStamp = 0;
    #else
    u32PvrPauseTimeStamp = 0; //force reset timestamp
    #endif
    #endif

    /*[01-1]demux part ================================================================*/
    if(enBufferMode == E_JUMP_BUFFER_RESET)
    {
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_PlaybackDisable();
        #endif

        #ifndef S3PLUS
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , MSAPI_DMX_DATAPATH_PACKETMODE_192);
        #endif
        #else
        msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , 0);
        #endif
        pstPvrPlaybackPath->u32BufferReadPointer  = pstPvrPlaybackPath->u32BufferStart;
        pstPvrPlaybackPath->u32BufferWritePointer = pstPvrPlaybackPath->u32BufferStart;

        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_SetPlaybackWrite(pstPvrPlaybackPath->u32BufferWritePointer);
        #endif

        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        msAPI_PVR_PlaybackPathWaitAVFifoClean(); ////MIPS, NonOS
        #else
        msAPI_DMX_PlaybackEnable();
        #endif
      //printf("timestamp nop; playback disable->resetbuf->enable; cmdq nop\n");
    }

    u32JumpKByte = GetLinearFilePos(pstPvrPlaybackPath, u16JumpSecond,pstPvrPlaybackPath->u32FileValidPosStrKB,pstPvrPlaybackPath->u32FileValidPosEndKB);
    pstPvrPlaybackPath->u32FilePositionKB =  u32JumpKByte ;
    mid_time = msAPI_PVR_PlaybackGetPosTimeByTimeStamp(pstPvrPlaybackPath->pstPvrRecordPath->enEncryptionType, pstPvrPlaybackPath->hReadFile,msAPI_PVR_KToLongLong(u32JumpKByte));
    MApi_DMX_Pvr_SetPlaybackStamp(mid_time*90);//mid_time ΢

    pstPvrPlaybackPath->u32FileLastPosKB = pstPvrPlaybackPath->u32FilePositionKB;
  //printf("[JumpByte=%08lu KB | JumpSecond=%04u SEC | JumpTo=%08lu KB]\n", u32JumpKByte, u16JumpSecond, pstPvrPlaybackPath->u32FilePositionKB);
    if (!msAPI_PVRFS_FileSeek(pstPvrPlaybackPath->hReadFile, msAPI_PVR_KToLongLong(pstPvrPlaybackPath->u32FilePositionKB), PVRFS_SEEK_OPTION_FROM_BEGIN))
    {
        return E_PVR_API_STATUS_FILE_SEEK_FAIL;
    }

    /*[01-3]media format ==============================================================*/

    #ifdef S3PLUS
    pstPvrPlaybackPath->u16PlayedErrCount3 = 0;
    #endif

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathJumpForward\n");

    if(u32JumpKByte == 0)
    {
        return E_PVR_API_STATUS_FILE_BUMP_END;
    }
    else
    {
        return E_PVR_API_STATUS_OK;
    }
}



/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathStepIn(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U8 u8FID;
    BOOLEAN bDataReset;
    /*[01-0]pvr part ==================================================================*/
    if(pstPvrPlaybackPath->enDirection != E_PLAYBACK_PATH_DIRECTION_STEPIN)
    {
        pstPvrPlaybackPath->enDirection = E_PLAYBACK_PATH_DIRECTION_STEPIN;
        bDataReset = TRUE;
    }
    else
    {
        bDataReset = FALSE;
    }    //MApi_DMX_BypassFileInTimeStamp(FALSE);
    //MApi_VDEC_AVSyncOn(FALSE, 0, 0);
    //MApi_DMX_Pvr_TimeStampEnable();
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if (pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO
                #ifndef S3PLUS
                ||
                pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO2
                #endif
                )
            {
            #ifdef PVR_UTOPIA
                MApi_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            #else
                msAPI_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            #endif
            }
        }
    }

    /*[01-2]file system part ==========================================================*/
    /*[GROUP2-4]=======================================================================*/
    pstPvrPlaybackPath->u16FileReadAccumulatorKB = 0;

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathSlowForward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U8 u8FID;
    BOOLEAN bDataReset;

    /*[01-0]pvr part ==================================================================*/
    if(pstPvrPlaybackPath->enDirection != E_PLAYBACK_PATH_DIRECTION_SLOWFORWARD)
    {
        pstPvrPlaybackPath->enDirection = E_PLAYBACK_PATH_DIRECTION_SLOWFORWARD;
        bDataReset = TRUE;
    }
    else
    {
        bDataReset = FALSE;
    }

    /*[01-1]demux part ================================================================*/
    #ifdef S3PLUS
        pstPvrPlaybackPath->u32PrvTimerDelay = 0; //reset DMX play speed
    #endif

    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_PlaybackResume(); //<--***later
    #endif
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if (pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO
                #ifndef S3PLUS
                ||
                pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO2
                #endif
                )
            {
            #ifdef PVR_UTOPIA
                MApi_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            #else
                msAPI_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            #endif
            }
        }
    }
  //printf("timestamp disable; playback resume; cmdq disable\n");

    /*[01-2]file system part ==========================================================*/
    /*[GROUP2-4]=======================================================================*/
    pstPvrPlaybackPath->u16FileReadAccumulatorKB = 0;

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/
    /*[GROUP4-4]=======================================================================*/


    #ifdef S3PLUS
    pstPvrPlaybackPath->u16PlayedErrCount3 = 0;
    #endif

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathFastForward\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathFastForward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U8 u8FID;
    BOOLEAN bDataReset;

    /*[01-0]pvr part ==================================================================*/
    if(pstPvrPlaybackPath->enDirection != E_PLAYBACK_PATH_DIRECTION_FASTFORWARD)
    {
        pstPvrPlaybackPath->enDirection = E_PLAYBACK_PATH_DIRECTION_FASTFORWARD;
        bDataReset = TRUE;
    }
    else
    {
        bDataReset = FALSE;
    }

    /*[01-1]demux part ================================================================*/
    #ifdef S3PLUS
        pstPvrPlaybackPath->u32PrvTimerDelay = 0; //reset DMX play speed
    #endif

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
//    MApi_DMX_Pvr_TimeStampDisable();
    u32PvrPauseTimeStamp = 0;
    #else
    msAPI_DMX_TimeStampDisable();
    u32PvrPauseTimeStamp = 0;
    #endif

    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_DisableCmdQ();    //<--***first
    #endif
    #endif

    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_PlaybackResume(); //<--***later
    #endif
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if (pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO
                #ifndef S3PLUS
                ||
                pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO2
                #endif
                )
            {
            #ifdef PVR_UTOPIA
                MApi_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            #else
                msAPI_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            #endif
            }
        }
    }
  //printf("timestamp disable; playback resume; cmdq disable\n");

    /*[01-2]file system part ==========================================================*/
    /*[GROUP2-4]=======================================================================*/
    pstPvrPlaybackPath->u16FileReadAccumulatorKB = 0;

    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/




    #ifdef S3PLUS
    pstPvrPlaybackPath->u16PlayedErrCount3 = 0;
    #endif

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathFastForward\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathFastBackward(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U8 u8FID;
    BOOLEAN bDataReset;

    /*[01-0]pvr part ==================================================================*/
    if(pstPvrPlaybackPath->enDirection != E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD)
    {
        pstPvrPlaybackPath->enDirection = E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD;
        bDataReset = TRUE;
    }
    else
    {
        bDataReset = FALSE;
    }

    /*[01-1]demux part ================================================================*/
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
  //  MApi_DMX_Pvr_TimeStampDisable();
    u32PvrPauseTimeStamp = 0;
    #else
    msAPI_DMX_TimeStampDisable();
    u32PvrPauseTimeStamp = 0;
    #endif
    #endif

    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_PlaybackDisable();
    #endif

    pstPvrPlaybackPath->u32BufferWritePointer = pstPvrPlaybackPath->u32BufferStart; //cmdq reset
    MDrv_GE_ClearFrameBuffer(((PVR_TRICK_MODE_MEMORY_TYPE&MIU1)?PVR_TRICK_MODE_ADR|MIU_INTERVAL:PVR_TRICK_MODE_ADR), PVR_TRICK_MODE_LEN, 0x00);         //buf  reset
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    msAPI_DMX_EnableCmdQ();
    #endif
    #endif
    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if (pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO
                #ifndef S3PLUS
                ||
                pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO2
                #endif
                )
            {
                msAPI_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            }
        }
    }
  //printf("timestamp disable; playback disable; cmdq enable\n");

    /*[01-2]file system part ==========================================================*/


    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/



    #ifdef S3PLUS
    pstPvrPlaybackPath->u16PlayedErrCount3 = 0;
    #endif

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathFastBackward\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_PlaybackPathPause(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U8 u8FID;

    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    if((pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FORWARD) ||
        (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTFORWARD) ||
        (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_SLOWFORWARD) )
    {
        if(pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTFORWARD)
        {
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            msAPI_PVR_PlaybackPathWaitAVFifoClean();
            #else
            msAPI_DMX_PlaybackDisable();
            #endif

            #ifndef S3PLUS
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , MSAPI_DMX_DATAPATH_PACKETMODE_192);
            #endif
            #else
            msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , 0);
            #endif
            pstPvrPlaybackPath->u32BufferReadPointer  = pstPvrPlaybackPath->u32BufferStart;
            pstPvrPlaybackPath->u32BufferWritePointer = pstPvrPlaybackPath->u32BufferStart;

            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_DMX_SetPlaybackWrite(pstPvrPlaybackPath->u32BufferWritePointer);
            #endif

            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_DMX_PlaybackEnable();
            #endif
          //printf("timestamp nop; playback disable->resetbuf->enable->pause, cmdq nop\n");
        }
        else
        {
          //printf("timestamp nop; playback pause; cmdq nop\n");
        #ifndef S3PLUS
        #ifdef PVR_UTOPIA
            MApi_DMX_Pvr_GetPlaybackStamp(&u32PvrPauseTimeStamp);
        #else
            u32PvrPauseTimeStamp = msAPI_DMX_GetPlaybackStamp()+45000;
        #endif
        #endif
        }

        #ifdef PVR_UTOPIA
            //MApi_DMX_Filein_Pause();
        #else
            msAPI_DMX_PlaybackPause();
        #endif

        if(pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FORWARD)
        {
            for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
            {
                if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
                {
                    if (pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_PCR)
                    {
                    #ifdef PVR_UTOPIA
                        {
                            MS_U32 u32STC32;
                            MS_U32 u32STC;

                            MApi_DMX_Stc_Get(&u32STC32, &u32STC);
                            pstPvrPlaybackPath->u32STC = u32STC;
                            MApi_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
                        }
                    #else
                        pstPvrPlaybackPath->u32STC = msAPI_DMX_GetStc();
                        msAPI_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
                    #endif
                      //printf("Pause_STC=0x%08lx \n", pstPvrPlaybackPath->u32STC);
                        break;
                    }
                }
            }
        }
    }
    else    //(pstPvrPlaybackPath->enPathDirection == E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD)
    {
        #ifndef S3PLUS
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        while(msAPI_DMX_GetQueuingCmdNum() != 0)
        #endif
        {
          //printf("Wait CmdQ to be empty\n");
        }

        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_DisableCmdQ();
        #endif

        #ifdef PVR_UTOPIA
       // MApi_DMX_Pvr_TimeStampDisable();
        u32PvrPauseTimeStamp = 0;
        #else
            msAPI_DMX_TimeStampDisable();
            u32PvrPauseTimeStamp = 0;
        #endif
        #endif
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_PlaybackDisable();
        #endif
        #ifndef S3PLUS
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , MSAPI_DMX_DATAPATH_PACKETMODE_192);
        #endif
        #else
        msAPI_DMX_SetPlaybackBuffer(pstPvrPlaybackPath->u32BufferStart,  pstPvrPlaybackPath->u32BufferLength, 0 , 0);
        #endif
        pstPvrPlaybackPath->u32BufferReadPointer  = pstPvrPlaybackPath->u32BufferStart;
        pstPvrPlaybackPath->u32BufferWritePointer = pstPvrPlaybackPath->u32BufferStart;
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_SetPlaybackWrite(pstPvrPlaybackPath->u32BufferWritePointer);
        #endif
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        msAPI_DMX_PlaybackEnable();
        #endif
      //printf("timestamp disable; playback disable->resetbuf->enable; cmdq disable\n");
    }

    /*[01-2]file system part ==========================================================*/


    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/

    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathPause\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus  msAPI_PVR_PlaybackPathResume(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U8 u8FID;

    /*[01-0]pvr part ==================================================================*/
    #ifdef PVR_UTOPIA
    if((pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTFORWARD) ||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD) ||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_JUMPFORWARD)||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_JUMPBACKWARD)||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_SLOWFORWARD))
    {
        MApi_DMX_BypassFileInTimeStamp(TRUE);
        msAPI_PVR_ClearBitStreamBuff(pstPvrPlaybackPath); //CL:81713
        MApi_DMX_BypassFileInTimeStamp(FALSE);
    }
    #endif

    /*[01-1]demux part ================================================================*/
    #ifdef S3PLUS
    pstPvrPlaybackPath->u32PrvTimerDelay = 0; //reset DMX play speed
    #endif

    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
        {
            if (pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_PCR)
            {
                //pstPvrPlaybackPath->u32STC-=45000;  //minus half second
            #ifdef PVR_UTOPIA
                MApi_DMX_Stc_Set(0, pstPvrPlaybackPath->u32STC);
            #else
                msAPI_DMX_SetStc(pstPvrPlaybackPath->u8FilterID[u8FID], pstPvrPlaybackPath->u32STC);
            #endif
            #ifdef PVR_UTOPIA
            {
                MS_U32 u32STC32;
                MS_U32 u32STC;

                MApi_DMX_Stc_Get(&u32STC32, &u32STC);
                pstPvrPlaybackPath->u32STC = u32STC;

                MApi_DMX_SectReset(pstPvrPlaybackPath->u8FilterID[u8FID]);
                MApi_DMX_Start(pstPvrPlaybackPath->u8FilterID[u8FID]);
            }
            #else
                pstPvrPlaybackPath->u32STC = msAPI_DMX_GetStc();

                msAPI_DMX_Reset(pstPvrPlaybackPath->u8FilterID[u8FID]);
                msAPI_DMX_Start(pstPvrPlaybackPath->u8FilterID[u8FID]);
            #endif
              //printf("Resume_STC=0x%08lx \n", pstPvrPlaybackPath->u32STC);
                break;
            }
        }
    }

    if ((pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTFORWARD ) ||
        (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD) ||
        (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_JUMPFORWARD )||  //FF||FB->PAUSE->JF||JB, CL81712
        (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_JUMPBACKWARD ) ||
        (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_STEPIN )||
        (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_SLOWFORWARD))
    {
        for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
        {
            if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
            {
                if (pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO
                    #ifndef S3PLUS
                    ||
                    pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_AUDIO2
                    #endif
                    )
                {
                #ifdef PVR_UTOPIA
                    BOOLEAN bEnable = FALSE;
                    if (MApi_DMX_IsStart(pstPvrPlaybackPath->u8FilterID[u8FID],&bEnable) != DMX_FILTER_STATUS_OK)
                        {ASSERT(0);}
                    if (!bEnable)
                    {
                        MApi_DMX_SectReset(pstPvrPlaybackPath->u8FilterID[u8FID]);
                        MApi_DMX_Start(pstPvrPlaybackPath->u8FilterID[u8FID]);
                    }
                #else
                    msAPI_DMX_Reset(pstPvrPlaybackPath->u8FilterID[u8FID]);
                    msAPI_DMX_Start(pstPvrPlaybackPath->u8FilterID[u8FID]);
                #endif
                }
            }
        }
    }
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if (u32PvrPauseTimeStamp == 0)
    {
        MApi_DMX_Pvr_TimeStampEnable();
    }
    else
    {
        MApi_DMX_Pvr_SetPlaybackStamp(u32PvrPauseTimeStamp);
        u32PvrPauseTimeStamp = 0;
    }
    #else
        if(u32PvrPauseTimeStamp == 0)
        {
            msAPI_DMX_TimeStampEnable();
        }
        else
        {
            msAPI_DMX_SetPlaybackStamp(u32PvrPauseTimeStamp); //start from PAUSE state
            u32PvrPauseTimeStamp = 0;
        }
    #endif
    #endif
    #ifdef PVR_UTOPIA
    //MApi_DMX_Filein_Resume();
    #else
    msAPI_DMX_PlaybackResume();
    #endif
  //printf("timestamp enable; playback resume; cmdq nop\n");


    /*[01-3]media format ==============================================================*/

    /*[GROUP4-4]=======================================================================*/
    if((pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_JUMPFORWARD ) ||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_JUMPBACKWARD) ||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTFORWARD ) ||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_FASTBACKWARD)||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_STEPIN ) ||
       (pstPvrPlaybackPath->enDirection == E_PLAYBACK_PATH_DIRECTION_SLOWFORWARD))
    {
        pstPvrPlaybackPath->enDirection = E_PLAYBACK_PATH_DIRECTION_FORWARD;
    }


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathResume\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathStop(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U8 u8FID;

    /*[01-0]pvr part ==================================================================*/


    /*[01-1]demux part ================================================================*/
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
 //   MApi_DMX_Pvr_TimeStampDisable();
    u32PvrPauseTimeStamp = 0;
    #else
    msAPI_DMX_TimeStampDisable();
    u32PvrPauseTimeStamp = 0;
    #endif
    u32PreWritePointer = 0;
    #endif
    #ifdef PVR_UTOPIA
        //MApi_DMX_Filein_CMDQ_Reset(); //has been done by using msAPI_PVR_PlaybackPathWaitAVFifoClean();
    #else
        msAPI_DMX_PlaybackDisable();
    #endif
  //printf("timestamp disable; playback disable; cmdq nop\n");

    for(u8FID=0; u8FID<MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if(pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID)
        {
            msAPI_DMX_Stop(pstPvrPlaybackPath->u8FilterID[u8FID]);
            msAPI_DMX_Close(pstPvrPlaybackPath->u8FilterID[u8FID]);
        }
    }

    /*[01-2]file system part ==========================================================*/


    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathStop\n");

    return E_PVR_API_STATUS_OK;
}

/***************************************************************************************/
enPvrApiStatus msAPI_PVR_PlaybackPathClose(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    /*[01-0]pvr part ==================================================================*/
    pstPvrPlaybackPath->bInUse = FALSE;

    /*[01-1]demux part ================================================================*/


    /*[01-2]file system part ==========================================================*/
    msAPI_PVR_PlaybackCount_Update(pstPvrPlaybackPath);
    msAPI_PVR_PlaybackPathUpdateMetadata(pstPvrPlaybackPath, E_METADATA_UPDATE_FILE);   //<---not necessary, just for symmetry
    msAPI_PVRFS_FileClose(pstPvrPlaybackPath->hReadFile);
    pstPvrPlaybackPath->hReadFile = INVALID_FILE_HANDLE;
#if (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
    MAPP_CIPVR_CIPVRFS_PlaybackFileClose();
#endif
    /*[01-3]media format ==============================================================*/


    /*[01-4]system part ===============================================================*/


    /*[02]global variables ============================================================*/
  //printf("msAPI_PVR_PlaybackPathClose\n");

    return E_PVR_API_STATUS_OK;
}
/***************************************************************************************/
#ifdef PVR_UTOPIA
#include "drvTSP.h"

void msAPI_PVR_ClearBitStreamBuff(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    #define SKIP_RAW_SIZE   184
  //  #define SKIP_PKT_NUM   22
    #define SKIP_PACKET_SIZE 192

    U32 BuffAdr;
  //  U32 BuffLen;
    U16 VideoPID;
    U8 u8FID;
    U32 FlushStarTime,FlushStarTime1;
    BOOL bRet = FALSE;
    U32 u32BufSize = 2048;
    U16 u16MostTimes = u32BufSize / SKIP_PACKET_SIZE;
    U32 u32SkipPKTsSize = u16MostTimes * SKIP_PACKET_SIZE;
    U8 u8Idx = 0;
    VDEC_PatternType stVdecType = E_VDEC_PATTERN_FLUSH;
    U8* pu8Addr;
    U32 u32LeastLength = 0;
    U16 u16LeastTime = 0;
    U8 u8SendSkipTimer = 0;

    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID
            && pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_VIDEO)
        {
            break;
        }
    }

    if(u8FID >= MSAPI_DMX_RECORD_FILTER_NUMBER)
        return;

    BuffAdr = pstPvrPlaybackPath->u32BufferStart;
  //  BuffLen = pstPvrPlaybackPath->u32BufferLength;
    VideoPID = pstPvrPlaybackPath->u16PID[u8FID];

    pu8Addr = (U8 *)(BuffAdr);

    MApi_DMX_Filein_CMDQ_Reset();

    memset(pu8Addr, 0xFF, u32BufSize);
    u32LeastLength = MApi_VDEC_GetPatternLeastLength(E_VDEC_PATTERN_FLUSH);//

    if (u32LeastLength == (0xFFFFFFFFUL))   // U32_MAX, MPEG case need more pattern to flush data
    {
        u32LeastLength = u16MostTimes * SKIP_RAW_SIZE;
        u8SendSkipTimer = 0xFF;
    }
    else//H264 need less pattern to flush data  //H264  u32LeastLength==0x98
    {
        u8SendSkipTimer = 2;
    }
    u16LeastTime = (u32LeastLength / SKIP_RAW_SIZE) + ((u32LeastLength % SKIP_RAW_SIZE > 0) ? 1 : 0);
    if (u16LeastTime > u16MostTimes)
    {
        u16LeastTime = u16MostTimes;
    }
    for(u8Idx = 0; u8Idx < u16MostTimes ; u8Idx++)  //around 4K
    {
        U32 u32Remainder = SKIP_RAW_SIZE;
        pu8Addr[0] = 0;
        pu8Addr[1] = 0;
        pu8Addr[2] = 0;
        pu8Addr[3] = 0;

        pu8Addr[4] = 0x47;
        pu8Addr[5] = (U8)(VideoPID >> 8);
        pu8Addr[6] = (U8)(VideoPID);
        pu8Addr[7] = ((u8Idx & 0xf) | 0x10);

        if (u8Idx < u16LeastTime)
        {
            if(u8Idx==0)
            {
                pu8Addr[8] = 0x0;
                pu8Addr[9] = 0x0;
                pu8Addr[10] = 0x01;
                pu8Addr[11] = 0xE0;
                pu8Addr[12] = 0x0;
                pu8Addr[13] = 0x0;
                pu8Addr[14] = 0x80;
                pu8Addr[15] = 0x0;
                pu8Addr[16] = 0x0;
            }
            else
            {
               MApi_VDEC_GenPattern(stVdecType, _VA2PA((MS_U32)&pu8Addr[8]), &u32Remainder);
            }
        }
        pu8Addr += SKIP_PACKET_SIZE;
    }

    MApi_VDEC_EnableLastFrameShow(FALSE);

    while(MApi_VDEC_Flush(E_VDEC_FREEZE_AT_CUR_PIC) != E_VDEC_OK)
    {
        bRet = TRUE;
        FlushStarTime = msAPI_Timer_GetTime0();
        while (!MApi_DMX_Filein_IsIdle())
        {
            if (msAPI_Timer_DiffTimeFromNow(FlushStarTime) > 300)
            {
                printf("1)Wait MApi_DMX_Filein_IsIdle() time out!\n");
                bRet = FALSE;
                break;
            }
        }
        if(bRet)
        {
            FlushStarTime = msAPI_Timer_GetTime0();
            while (MApi_DMX_Filein_Start(DMX_PES_NO_BYPASS_FIFO,_VA2PA(BuffAdr), u32SkipPKTsSize) != DMX_FILTER_STATUS_OK)
            {
                if (msAPI_Timer_DiffTimeFromNow(FlushStarTime) > 300)
                {
                    printf("2)Wait MApi_DMX_Filein_IsIdle() time out!\n");
                    break;
                }
            }
        }
    }
    FlushStarTime = msAPI_Timer_GetTime0();

    while (MApi_VDEC_IsAllBufferEmpty() != E_VDEC_OK)
    {
        bRet = TRUE;

        if(msAPI_Timer_DiffTimeFromNow(FlushStarTime) > 1000)
        {
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_VIDEO, TRUE);
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, TRUE);
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO2, TRUE);
            while (!MApi_DMX_Filein_IsIdle())
            {
                msAPI_Timer_Delayms(3);
            }
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_VIDEO, FALSE);
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO, FALSE);
            MApi_DMX_AVFifo_Reset(DMX_FILTER_TYPE_AUDIO2, FALSE);

            printf("3)Wait MApi_DMX_Filein_IsIdle() time out!\n");

            break;
        }
        if (u8SendSkipTimer)
        {
            if (u8SendSkipTimer <= 2)
                u8SendSkipTimer--;
            FlushStarTime1 = msAPI_Timer_GetTime0();
            while(!MApi_DMX_Filein_IsIdle())
            {
                if (msAPI_Timer_DiffTimeFromNow(FlushStarTime1) > 300)
                {
                    printf("4)Wait MApi_DMX_Filein_IsIdle() time out!\n");
                    bRet = FALSE;
                    break;
                }
            }
            FlushStarTime1 = msAPI_Timer_GetTime0();
            if(bRet)
            {
                while (MApi_DMX_Filein_Start(DMX_PES_NO_BYPASS_FIFO,_VA2PA(BuffAdr), u32SkipPKTsSize) != DMX_FILTER_STATUS_OK)
                {
                    if (msAPI_Timer_DiffTimeFromNow(FlushStarTime1) > 300)
                    {
                        printf("5)Wait MApi_DMX_Filein_IsIdle() time out!\n");
                        break;
                    }
                }
                msAPI_Timer_Delayms(5);
            }
         }
    }
}

#endif

#if 0//def PVR_UTOPIA
#define SKIP_RAW_SIZE   184
#define SKIP_PKT_NUM   22
#define SKIP_PACKET_SIZE 192
static void msAPI_PVR_MakeSkipDataPKT(U16 u16VideoPID, U32 u32BuffAddress)
{
    U8 u8Idx = 0;
    VDEC_PatternType stVdecType = E_VDEC_PATTERN_FLUSH;
    U8* pu8Addr;
    pu8Addr = (U8 *)u32BuffAddress;
    for(u8Idx = 0; u8Idx < SKIP_PKT_NUM ; u8Idx++)  //around 4K
    {
        U32 u32Remainder = SKIP_RAW_SIZE;
        pu8Addr[0] = 0;
        pu8Addr[1] = 0;
        pu8Addr[2] = 0;
        pu8Addr[3] = 0;

        pu8Addr[4] = 0x47;
        pu8Addr[5] = (U8)(u16VideoPID >> 8);
        pu8Addr[6] = (U8)(u16VideoPID);
        pu8Addr[7] = ((u8Idx & 0xf) | 0x10);

        #ifdef PVR_UTOPIA
        MApi_VDEC_GenPattern(stVdecType, _VA2PA((MS_U32)&pu8Addr[8]), &u32Remainder);
        #else
        MDrv_VDEC_GenPattern(stVdecType, _VA2PA((MS_U32)&pu8Addr[8]), &u32Remainder);
        #endif
#if 0
{
    U32 i = 0;
    printf("\n");
    for(i = 0; i < 16; i ++)
    {
        printf("[%d] = %x, ",i,(U32)pu8Addr[i]);
    }
    printf("\n");

}
#endif
    pu8Addr += SKIP_PACKET_SIZE;
    }

    return;
}

#include "drvTSP.h"
//void msAPI_PVR_ClearBitStreamBuff(U16 u16VideoPID, U32 u32BuffAddress, U32 u32BuffLen)
void msAPI_PVR_ClearBitStreamBuff(_msAPI_PVR_PlaybackPath * pstPvrPlaybackPath)
{
    U32 BuffAdr;
    U32 BuffLen;
    U16 VideoPID;
    U8 u8FID;
    U32 FlushStarTime;
    U8 u8ErrorCount;
    //VDEC_Result stVDECResult;

    for (u8FID = 0; u8FID < MSAPI_DMX_RECORD_FILTER_NUMBER; u8FID++)
    {
        if (pstPvrPlaybackPath->u8FilterID[u8FID] != MSAPI_DMX_INVALID_FLT_ID
            && pstPvrPlaybackPath->enFilterType[u8FID] == MSAPI_DMX_FILTER_TYPE_VIDEO)
        {
            break;
        }
    }

    if(u8FID >= MSAPI_DMX_RECORD_FILTER_NUMBER)
        return;

    BuffAdr = pstPvrPlaybackPath->u32BufferStart;
    BuffLen = pstPvrPlaybackPath->u32BufferLength;
    VideoPID = pstPvrPlaybackPath->u16PID[u8FID];

    //printf("wait DMX idle\n");

    MApi_DMX_Filein_CMDQ_Reset();

    while(!MApi_DMX_Filein_IsIdle())
    {
        //printf("MDrv_TSP_AVFifo_Reset\n");
       // MDrv_TSP_AVFifo_Reset(E_DRVTSP_FLT_TYPE_VIDEO, TRUE);
       // MDrv_TSP_AVFifo_Reset(E_DRVTSP_FLT_TYPE_AUDIO, TRUE);
       // MDrv_TSP_AVFifo_Reset(E_DRVTSP_FLT_TYPE_AUDIO2, TRUE);
    } //wait TSP empty

    //MApi_VDEC_Flush(E_VDEC_FREEZE_AT_CUR_PIC);
    MApi_VDEC_EnableLastFrameShow(FALSE);
    u8ErrorCount = 0;
    while((MApi_VDEC_Flush(E_VDEC_FREEZE_AT_CUR_PIC) != E_VDEC_OK)&&((u8ErrorCount++)<10))
    {
        msAPI_PVR_MakeSkipDataPKT(VideoPID, BuffAdr);
        if(MApi_DMX_Filein_Start(DMX_PES_NO_BYPASS_FIFO,_VA2PA(BuffAdr), SKIP_PACKET_SIZE*SKIP_PKT_NUM) != DMX_FILTER_STATUS_OK)
        {
            MS_DEBUG_MSG(printf("Filein buff error\n"));
        }
    }
    FlushStarTime = msAPI_Timer_GetTime0();
    do{
        if(MApi_DMX_Filein_IsIdle())
        {
            if(BuffLen >= SKIP_PACKET_SIZE*SKIP_PKT_NUM)
            {
                msAPI_PVR_MakeSkipDataPKT(VideoPID, BuffAdr);
                if(MApi_DMX_Filein_Start(DMX_PES_NO_BYPASS_FIFO,_VA2PA(BuffAdr), SKIP_PACKET_SIZE*SKIP_PKT_NUM) != DMX_FILTER_STATUS_OK)
                {
                    MS_DEBUG_MSG(printf("Filein buff error\n"));
                }
                msAPI_Timer_Delayms(10);
            }
            else
            {
                BuffAdr = pstPvrPlaybackPath->u32BufferStart;
                BuffLen = pstPvrPlaybackPath->u32BufferLength;
            }

            BuffAdr += (SKIP_PACKET_SIZE*SKIP_PKT_NUM);
            BuffLen -= (SKIP_PACKET_SIZE*SKIP_PKT_NUM);
        }
        else
        {
            U32 SlotNum;
            MApi_DMX_Filein_CMDQ_GetEmptyNum(&SlotNum);
            //printf("SlotNum=%lu\n",SlotNum);
        }

        if(msAPI_Timer_DiffTimeFromNow(FlushStarTime) > 3000)
        {
            MS_DEBUG_MSG(printf("time out\n"));
            break;
        }

    }while (MApi_VDEC_IsAllBufferEmpty() != E_VDEC_OK);
}
#endif

#ifdef PVR_8051
BOOLEAN code compile_msapi_pvr;
#endif

BOOL msAPI_PVR_GetRecordCAPVR(void)
{
    return _bRecordCAPVR;
}

void msAPI_PVR_SetRecordCAPVR(enPvrEncryptType enEncryptionType)
{
#if 0//(ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR)
    if(enEncryptionType == E_PVR_ENCRYPTION_CIPLUS)
    {
        _bRecordCAPVR = TRUE;
    }
    else
#endif
    {
        _bRecordCAPVR = FALSE;
    }
    printf("<<<<<<enEncryptionType=%d>>>>>\n",enEncryptionType);
}
#endif//ENABLE_PVR

#undef MSAPI_PVR_C

