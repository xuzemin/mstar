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

///[PVR MODULE - PVR BROWSER AP]

#define MAPP_PVR_BROWSER_C

//system
#include <string.h>
#include "Board.h"

#include "datatype.h"
#include "MsCommon.h"

#include "debug.h"

#if( ENABLE_PVR_BROWSER )

//driver
#include "SysInit.h"                     //MDrv_Sys_PushXdataWindow1Base
#ifdef PVR_8051
#include "drvMIU.h"                     //For MDrv_MIU_Copy
#endif

//api
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_FCtrl.h"                //For msAPI_FCtrl_IsDriveMounted
#include "msAPI_FS_SysInfo.h"           //For GET_DRAM_ADDR
#include "msAPI_MIU.h"                  //For msAPI_MIU_GetW1StartAddress
//ap
#include "MApp_GlobalFunction.h"        //For common Unicode manipulation function
#include "MApp_PVR_Browser.h"           //For itself

//left for testing string out(trans. to ascii)
#include "IOUtil.h"
#include "FSUtil.h"
#include "msAPI_PVRFileSystem.h"
#include "msAPI_PVR.h"

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    U16 u16FileName[PVR_BROWSER_MAX_FILE_NAME_LEN];
    U16 u16ProgramName[PVR_BROWSER_MAX_PROGRAM_NAME_LEN];
    U16 u16ChannelName[PVR_BROWSER_MAX_CHANNEL_NAME_LEN];
    U16 u16ProgDesc[PVR_BROWSER_MAX_PROGRAM_DESC_LEN];
    U32 u32StartTime;
    U32 u32Duration;
    MEMBER_SERVICETYPE enServiceType;
    LongLong u64FileLength;
    //==========================================
    U16 idxPrev; //raw index
    U16 idxNext;
    U16 idxSortByFilePrev;
    U16 idxSortByFileNext;
    U16 idxSortByProgPrev;
    U16 idxSortByProgNext;
    U16 idxSortByChannelPrev;
    U16 idxSortByChannelNext;
    U16 idxSortByStdTimePrev;
    U16 idxSortByStdTimeNext;
    U16 idxSortByFileSizePrev;
    U16 idxSortByFileSizeNext;
} PVR_BROWSER_ENTRY;

#if 1//def MIPS_CHAKRA //[mips]
    //#define PvrGetBrowBufAddr() _PA2VA(((PVR_BROWSER_BUFFER_MEMORY_TYPE&MIU1)?PVR_BROWSER_BUFFER_ADR|MIU_INTERVAL:PVR_BROWSER_BUFFER_ADR))
#else
    //#define PvrGetBrowBufAddr() PVR_BROWSER_BUFFER_ADR
#endif

#define PvrGetBrowBufAddr_PA()  ((PVR_BROWSER_BUFFER_MEMORY_TYPE&MIU1)?PVR_BROWSER_BUFFER_ADR|MIU_INTERVAL:PVR_BROWSER_BUFFER_ADR)
#define PvrGetBrowBufAddr_VA()  MsOS_PA2KSEG1( PvrGetBrowBufAddr_PA() )


#define PVR_BROWSER_DBG(x)      //x
#define PRINT_LIST_DATA         0//default disable; debug only

#define NULL_SLOT_INDEX         PVR_NULL_FILE_INDEX //0xFFFF
#define NOT_FOUND               0xFFFF

#ifdef PVR_UTOPIA
#define PARAM_OFFSET(type, param)  ((U32)&(((type*)0)->param))
#else
#define PARAM_OFFSET(type, param)  ((U16)&(((type*)0)->param))
#endif

#ifdef PVR_UTOPIA
#define MEM_CHECK(addr) do  \
                        {   \
                            if ((addr < PvrGetBrowBufAddr_VA()) || ((addr+sizeof(PVR_BROWSER_ENTRY)))>(PvrGetBrowBufAddr_VA()+PVR_BROWSER_BUFFER_LEN) )\
                            {\
                                __ASSERT(0); \
                                MS_DEBUG_MSG(printf("PVR_BROWSER::[ERR]memory access violation\n"));\
                            }\
                        } while (0)
#else
#define MEM_CHECK(addr) do  \
                        {   \
                            if ((addr < PVR_BROWSER_BUFFER_ADR) || ((addr+sizeof(PVR_BROWSER_ENTRY)))>(PVR_BROWSER_BUFFER_ADR+PVR_BROWSER_BUFFER_LEN) )\
                            {\
                                __ASSERT(0); \
                                MS_DEBUG_MSG(printf("PVR_BROWSER::[ERR]memory access violation\n"));\
                            }\
                        } while (0)
#endif

////////////////////////////////////////////////////////////////////////////////
#define MAX_PVR_BROWSER_ENTRY_SLOT_MAP  (MAX_PVR_BROWSER_ENTRY_NUM+7)/8


//#ifndef ENABLE_HALF_PVR
#if( ENABLE_HALF_PVR == 0 )
static U8        _PB_EntrySlotMap[MAX_PVR_BROWSER_ENTRY_SLOT_MAP];    ///pool buffer slot map
#else
static U8        _PB_EntrySlotMap[1];  // avoid lint error when France's half PVR
#endif

#if 1//def MIPS_CHAKRA //[mips]
    static U32 _PB_ADDR_RESERVE = 0;
#else
    static const U32 _PB_ADDR_RESERVE = PVR_BROWSER_BUFFER_ADR + (U32)PVR_BROWSER_RESERVED_ENTRY_INDEX * sizeof(PVR_BROWSER_ENTRY);
#endif

extern void MApp_TimeShift_DelTsFileName(void);
//**************************************************************************
static U16  _PB_LatestInsertedSlotIdx   = NULL_SLOT_INDEX;///pointer to latest added entry index
static U16  _PB_TotalFileNum            = 0;

static U16  _PB_PlayingPhysicalIndex    = PVR_NULL_FILE_INDEX;///Physical Index of current playing file index
static U16  _PB_RecordingPhysicalIndex  = PVR_NULL_FILE_INDEX;///Physical Index of current recording file index

static U16       _PB_lastLogicalIndex   = PVR_NULL_FILE_INDEX;  //for improve search speed, save latest result of PVR Browser.
static SORT_TYPE _PB_lastSortType       = SORT_NONE;                     //for improve search speed, save latest result of PVR Browser.
static U16       _PB_lastPhysicalIndex  = PVR_NULL_FILE_INDEX; //for improve search speed, save latest result of PVR Browser.

/******************************************************************************/
/// Helper function: Check PVR Browser LEN
/// @param
/// @return FALSE: Have Browser Buffer; TRUE: Don't Have Browser Buffer
/******************************************************************************/
BOOLEAN MApp_PvrBrowser_IsEmptyBuffer(void)
{
    if (0 == PVR_BROWSER_BUFFER_LEN)
    {
        return TRUE;
    }

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// [Browser Internal Implement section]
//  use circular double linked list structure to store browser entry data
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/// Helper function: Find a empty file entry slot in pool buffer
/// @param
/// @return
/******************************************************************************/
static U16 _PB_GetEmptySlot(void)
{
#if( ENABLE_HALF_PVR == 0 )
    U16 idx;
    for (idx=0; idx<MAX_PVR_BROWSER_ENTRY_NUM; idx++)
    {
        U8 i = idx / 8;
        U8 j = idx % 8;
        U8 InUse = GETBIT(_PB_EntrySlotMap[i],j);

        if (!InUse)
            return idx;

    }
#endif
    return NOT_FOUND;
}

U32 _PB_Get_BrowBufAddr_VA_By_EntryIdx(U32 u32EntryIdx)
{
    U32 addr = 0;

    addr = PvrGetBrowBufAddr_VA() + (u32EntryIdx*sizeof(PVR_BROWSER_ENTRY));

    MEM_CHECK(addr);

    return addr;
}

/******************************************************************************/
/// Helper function: Compare new entry with list item
/// @param: pNewEntry,item want to insert
/// @param: u16SlotItem, item to compare
/// @param: sortType,  sort type
/// @return less -1, equal 0, bigger 1
/******************************************************************************/
static S8 _PB_CompareEntry( PVR_BROWSER_ENTRY *pNewEntry, U16 u16SlotItem, SORT_TYPE sortType)
{
   U16 idx;
   union
   {
       U16 u16FileName[PVR_BROWSER_MAX_FILE_NAME_LEN];
       U16 u16ProgramName[PVR_BROWSER_MAX_PROGRAM_NAME_LEN];
       U16 u16ChannelName[PVR_BROWSER_MAX_CHANNEL_NAME_LEN];
       U32 u32StartTime;
       LongLong u64FileLength;
   } xdata tmpBuf;

   if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
   {
       return 0;
   }

#if 1//def PVR_UTOPIA
   //U32 addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
   U32 addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(u16SlotItem);
#else
   U32 addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
#endif

   MEM_CHECK(addr);

   switch(sortType)
   {
    case SORT_NONE:
            return 1;

    case SORT_FILE_NAME:
        addr += PARAM_OFFSET(PVR_BROWSER_ENTRY, u16FileName[0]);
    #ifdef PVR_UTOPIA
            MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(tmpBuf.u16FileName)) ,sizeof(tmpBuf.u16FileName), MIU_SDRAM2SDRAM);
    #else
        MDrv_MIU_Copy(addr, GET_DRAM_ADDR(tmpBuf.u16FileName) ,sizeof(tmpBuf.u16FileName), MIU_SDRAM2SDRAM);
    #endif
        for( idx=0; idx<PVR_BROWSER_MAX_FILE_NAME_LEN; idx++)
        {
            if(tmpBuf.u16FileName[idx] < pNewEntry->u16FileName[idx])
                return 1;
            else if(tmpBuf.u16FileName[idx] > pNewEntry->u16FileName[idx])
                return -1;
            else if(tmpBuf.u16FileName[idx] == 0)
                return 0;
         }
        return 0;
        break;

    case SORT_PROG_NAME:
        addr += PARAM_OFFSET(PVR_BROWSER_ENTRY, u16ProgramName[0]);
    #ifdef PVR_UTOPIA
        MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(tmpBuf.u16ProgramName)) ,sizeof(tmpBuf.u16ProgramName), MIU_SDRAM2SDRAM);
    #else
        MDrv_MIU_Copy(addr, GET_DRAM_ADDR(tmpBuf.u16ProgramName) ,sizeof(tmpBuf.u16ProgramName), MIU_SDRAM2SDRAM);
    #endif
        for( idx=0; idx<PVR_BROWSER_MAX_PROGRAM_NAME_LEN; idx++)
        {
            if(tmpBuf.u16ProgramName[idx] < pNewEntry->u16ProgramName[idx])
                return 1;
            else if(tmpBuf.u16ProgramName[idx] > pNewEntry->u16ProgramName[idx])
                return -1;
            else if(tmpBuf.u16ProgramName[idx] == 0)
                return 0;
         }
        return 0;
        break;

    case SORT_CHANNEL_NAME:
        addr += PARAM_OFFSET(PVR_BROWSER_ENTRY, u16ChannelName[0]);
    #ifdef PVR_UTOPIA
        MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(tmpBuf.u16ChannelName)) ,sizeof(tmpBuf.u16ChannelName), MIU_SDRAM2SDRAM);
    #else
        MDrv_MIU_Copy(addr, GET_DRAM_ADDR(tmpBuf.u16ChannelName) ,sizeof(tmpBuf.u16ChannelName), MIU_SDRAM2SDRAM);
    #endif
        for( idx=0; idx<PVR_BROWSER_MAX_CHANNEL_NAME_LEN; idx++)
        {
            if(tmpBuf.u16ChannelName[idx] < pNewEntry->u16ChannelName[idx])
                return 1;
            else if(tmpBuf.u16ChannelName[idx] > pNewEntry->u16ChannelName[idx])
                return -1;
            else if(tmpBuf.u16ChannelName[idx] == 0)
                return 0;
         }
        return 0;
        break;

    case SORT_PROG_TIME:
        addr += PARAM_OFFSET(PVR_BROWSER_ENTRY, u32StartTime);
    #ifdef PVR_UTOPIA
        tmpBuf.u32StartTime = *(U32 *)addr;
    #else
        MDrv_MIU_Copy(addr, GET_DRAM_ADDR(&tmpBuf.u32StartTime) ,sizeof(U32), MIU_SDRAM2SDRAM);
    #endif
        if(tmpBuf.u32StartTime < pNewEntry->u32StartTime)
        {
            return 1;
        }
        else if(tmpBuf.u32StartTime > pNewEntry->u32StartTime)
        {
            return -1;
        }
        else
        {
            return 0;
        }
        break;

    case SORT_FILE_LENGTH:
         addr += PARAM_OFFSET(PVR_BROWSER_ENTRY, u64FileLength);
    #ifdef PVR_UTOPIA
        MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(&tmpBuf.u64FileLength)) ,sizeof(tmpBuf.u64FileLength), MIU_SDRAM2SDRAM);
    #else
         MDrv_MIU_Copy(addr, GET_DRAM_ADDR(&tmpBuf.u64FileLength) ,sizeof(tmpBuf.u64FileLength), MIU_SDRAM2SDRAM);
    #endif
         if(tmpBuf.u64FileLength.Hi < pNewEntry->u64FileLength.Hi)
             return 1;
         else if(tmpBuf.u64FileLength.Hi > pNewEntry->u64FileLength.Hi)
            return -1;
         else if(tmpBuf.u64FileLength.Lo < pNewEntry->u64FileLength.Lo)
                     return 1;
         else if(tmpBuf.u64FileLength.Lo > pNewEntry->u64FileLength.Lo)
                     return -1;
         return 0;
        break;

      default:
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]Unknown compare type\n"));
        return 0;
   }
}


/******************************************************************************/
/// Helper function:
/// @param
/// @return
/******************************************************************************/
static U16 _PB_GetNextEntryIndex(U16 u16SlotItem, SORT_TYPE sortType)
{
    U32 addr;
#ifndef PVR_UTOPIA
    U16 xdata u16NextSlot;
#endif

   if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
   {
       return NULL_SLOT_INDEX;
   }

#if( ENABLE_HALF_PVR == 0 )
    if((PVR_BROWSER_BUFFER_LEN/sizeof(PVR_BROWSER_ENTRY) <= u16SlotItem) ||
        (sortType >= SORT_TYPE_NUM ))
#endif
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]arg error\n"));
        return NULL_SLOT_INDEX;
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(u16SlotItem);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
#endif

    MEM_CHECK(addr);
    switch(sortType)
    {
    case SORT_NONE:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxNext);
            break;
    case SORT_FILE_NAME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFileNext);
            break;
    case SORT_PROG_NAME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByProgNext);
            break;
    case SORT_CHANNEL_NAME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByChannelNext);
            break;
    case SORT_PROG_TIME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByStdTimeNext);
            break;
    case SORT_FILE_LENGTH:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFileSizeNext);
            break;
     default:
        __ASSERT(0);
        return NULL_SLOT_INDEX;
    }

#if 1//def PVR_UTOPIA
    //MApi_BDMA_Copy(addr, _VA2PA(GET_DRAM_ADDR(&u16NextSlot)) ,sizeof(u16NextSlot), MIU_SDRAM2SDRAM);
    return *(U16 *)addr;
#else
    MDrv_MIU_Copy(addr, GET_DRAM_ADDR(&u16NextSlot) ,sizeof(u16NextSlot), MIU_SDRAM2SDRAM);
    return u16NextSlot;
#endif

}


/******************************************************************************/
/// Helper function:
/// @param
/// @return
/******************************************************************************/
static U16 _PB_GetPrevEntryIndex(U16 u16SlotItem, SORT_TYPE sortType)
{
    U32 addr;
#ifndef PVR_UTOPIA
    U16 xdata u16PrevSlot;
#endif

   if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
   {
       return NULL_SLOT_INDEX;
   }

#if( ENABLE_HALF_PVR == 0 )
    if((PVR_BROWSER_BUFFER_LEN/sizeof(PVR_BROWSER_ENTRY) <= u16SlotItem) ||
        (sortType >= SORT_TYPE_NUM))
#endif
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]arg error\n"));
        return NULL_SLOT_INDEX;
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(u16SlotItem);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
#endif

    MEM_CHECK(addr);

    switch(sortType)
    {
    case SORT_NONE:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxPrev);
            break;
    case SORT_FILE_NAME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFilePrev);
            break;
    case SORT_PROG_NAME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByProgPrev);
            break;
    case SORT_CHANNEL_NAME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByChannelPrev);
            break;
    case SORT_PROG_TIME:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByStdTimePrev);
            break;
    case SORT_FILE_LENGTH:
            addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFileSizePrev);
            break;
     default:
        __ASSERT(0);
        return NULL_SLOT_INDEX;
    }

#if 1//def PVR_UTOPIA
    //MApi_BDMA_Copy(addr, _VA2PA(GET_DRAM_ADDR(&u16PrevSlot)) ,sizeof(u16PrevSlot), MIU_SDRAM2SDRAM);
    return *(U16 *)addr;
#else
    MDrv_MIU_Copy(addr, GET_DRAM_ADDR(&u16PrevSlot) ,sizeof(u16PrevSlot), MIU_SDRAM2SDRAM);
    return u16PrevSlot;
#endif
}


/******************************************************************************/
/// Helper function:
/// @param
/// @return
/******************************************************************************/
static E_PVR_RET _PB_SetNextLinkVal(U16 u16SlotItem,  U16 *pu16NextSlot, SORT_TYPE sortType)
{
    U32 addr;

   if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
   {
       return E_PVR_RET_FAIL;
   }

#if( ENABLE_HALF_PVR == 0 )
    if((PVR_BROWSER_BUFFER_LEN/sizeof(PVR_BROWSER_ENTRY) <= u16SlotItem) ||
        (sortType >= SORT_TYPE_NUM))
#endif
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]arg error\n"));
        return E_PVR_RET_FAIL;
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(u16SlotItem);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
#endif

    MEM_CHECK(addr);

    switch(sortType)
    {
        case SORT_NONE:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxNext);
                break;
        case SORT_FILE_NAME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFileNext);
                break;
        case SORT_PROG_NAME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByProgNext);
                break;
        case SORT_CHANNEL_NAME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByChannelNext);
                break;
        case SORT_PROG_TIME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByStdTimeNext);
                break;
        case SORT_FILE_LENGTH:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFileSizeNext);
                break;
         default:
            __ASSERT(0);
    }

#if 1//def PVR_UTOPIA
    MApi_BDMA_Copy(_VA2PA(GET_DRAM_ADDR(pu16NextSlot)) ,_VA2PA(addr), sizeof(U16), MIU_SDRAM2SDRAM);
#else
    MDrv_MIU_Copy(GET_DRAM_ADDR(pu16NextSlot) ,addr, sizeof(U16), MIU_SDRAM2SDRAM);
#endif
    return E_PVR_RET_OK;
}


/******************************************************************************/
/// Helper function:
/// @param
/// @return
/******************************************************************************/
static E_PVR_RET _PB_SetPrevLinkVal(U16 u16SlotItem, U16 *pu16PrevSlot, SORT_TYPE sortType)
{
    U32 addr;

   if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
   {
       return E_PVR_RET_FAIL;
   }

#if( ENABLE_HALF_PVR == 0 )
    if((PVR_BROWSER_BUFFER_LEN/sizeof(PVR_BROWSER_ENTRY) <= u16SlotItem) ||
        (sortType >= SORT_TYPE_NUM))
#endif
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]arg error\n"));
        return E_PVR_RET_FAIL;
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(u16SlotItem);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(u16SlotItem*sizeof(PVR_BROWSER_ENTRY));
#endif

    MEM_CHECK(addr);

    switch(sortType)
    {
        case SORT_NONE:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxPrev);
                break;
        case SORT_FILE_NAME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFilePrev);
                break;
        case SORT_PROG_NAME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByProgPrev);
                break;
        case SORT_CHANNEL_NAME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByChannelPrev);
                break;
        case SORT_PROG_TIME:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByStdTimePrev);
                break;
        case SORT_FILE_LENGTH:
                addr +=PARAM_OFFSET(PVR_BROWSER_ENTRY, idxSortByFileSizePrev);
                break;
        default:
            __ASSERT(0);
    }


#if 1//def PVR_UTOPIA
    MApi_BDMA_Copy(_VA2PA(GET_DRAM_ADDR(pu16PrevSlot)),  _VA2PA(addr), sizeof(U16), MIU_SDRAM2SDRAM);
#else
    MDrv_MIU_Copy(GET_DRAM_ADDR(pu16PrevSlot),  addr, sizeof(U16), MIU_SDRAM2SDRAM);
#endif
    return E_PVR_RET_OK;
}


/******************************************************************************/
/// Helper function:
/// @param
/// @return
/// Note:
/// when call this function, pNewEntry should already saved in slot u16NewEntryTargetSlotID
/// header not used
/******************************************************************************/
static void _PB_SortInsertedEntry(U16 u16ListHeaderSlotID, U16 u16NewEntryTargetSlotID, PVR_BROWSER_ENTRY *pNewEntry, SORT_TYPE sortType)
{
    U16 u16PrevSlotID = u16ListHeaderSlotID;
    U16 u16NextSlotID;
    u16NextSlotID = _PB_GetNextEntryIndex(u16ListHeaderSlotID, sortType);
#if( ENABLE_HALF_PVR == 0 )
     __ASSERT(MAX_PVR_BROWSER_ENTRY_NUM > u16NextSlotID);
#endif
    while(u16NextSlotID != u16ListHeaderSlotID && _PB_CompareEntry(pNewEntry, u16NextSlotID, sortType)>0)
    {
        u16PrevSlotID = u16NextSlotID;
        u16NextSlotID = _PB_GetNextEntryIndex(u16NextSlotID, sortType);
#if( ENABLE_HALF_PVR == 0 )
        __ASSERT(MAX_PVR_BROWSER_ENTRY_NUM > u16NextSlotID);
#endif
    }
     _PB_SetNextLinkVal(u16PrevSlotID, &u16NewEntryTargetSlotID, sortType);
     _PB_SetPrevLinkVal(u16NextSlotID, &u16NewEntryTargetSlotID, sortType);
     _PB_SetPrevLinkVal(u16NewEntryTargetSlotID, &u16PrevSlotID, sortType);
     _PB_SetNextLinkVal(u16NewEntryTargetSlotID, &u16NextSlotID, sortType);
}


/******************************************************************************/
/// Helper function:
/// @param
/// @return
/******************************************************************************/
static void _PB_RemoveEntryBySort(U16 u16RemoveEntrySlotID, SORT_TYPE sortType)
{
     U16 u16NextSlotID = _PB_GetNextEntryIndex(u16RemoveEntrySlotID, sortType);
     U16 u16PrevSlotID = _PB_GetPrevEntryIndex(u16RemoveEntrySlotID, sortType);
#if( ENABLE_HALF_PVR == 0 )
      __ASSERT(MAX_PVR_BROWSER_ENTRY_NUM > u16NextSlotID);
#endif
      __ASSERT(PVR_BROWSER_RESERVED_ENTRY_INDEX != u16RemoveEntrySlotID );
#if( ENABLE_HALF_PVR == 0 )
      __ASSERT(MAX_PVR_BROWSER_ENTRY_NUM > u16RemoveEntrySlotID);
#endif
     _PB_SetPrevLinkVal(u16NextSlotID, &u16PrevSlotID, sortType);
     _PB_SetNextLinkVal(u16PrevSlotID, &u16NextSlotID, sortType);

     ///clear remove entry link pointer to null;
     {
        U16 u16NullSlotID = NULL_SLOT_INDEX;

        _PB_SetPrevLinkVal(u16RemoveEntrySlotID, &u16NullSlotID, sortType);
        _PB_SetNextLinkVal(u16RemoveEntrySlotID, &u16NullSlotID, sortType);
     }

}


/******************************************************************************/
/// Function: Add a browser entry to list
/// @param
/// @return
/******************************************************************************/
static U16 _PB_AddEntryToDB(PVR_BROWSER_ENTRY *pNewEntry)
{
    U16 u16NewEntryTargetSlotID;
    U32 addr;
    U16 i, j;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return NULL_SLOT_INDEX;
    }

    if (NULL == pNewEntry)
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]arg error\n"));
        return NULL_SLOT_INDEX;
    }

    if ((u16NewEntryTargetSlotID = _PB_GetEmptySlot()) == NOT_FOUND)
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[INFO]can't find empty slot\n"));
        _PB_LatestInsertedSlotIdx = NULL_SLOT_INDEX;
        return NULL_SLOT_INDEX;
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr()) + (U32)u16NewEntryTargetSlotID*sizeof(PVR_BROWSER_ENTRY);
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(u16NewEntryTargetSlotID);

    MApi_BDMA_Copy(_VA2PA(GET_DRAM_ADDR(pNewEntry)), _VA2PA(addr), sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);//store new entry to slotid
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)u16NewEntryTargetSlotID*sizeof(PVR_BROWSER_ENTRY);
    MDrv_MIU_Copy(GET_DRAM_ADDR(pNewEntry), addr, sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);//store new entry to slotid
#endif

    _PB_SortInsertedEntry(PVR_BROWSER_RESERVED_ENTRY_INDEX, u16NewEntryTargetSlotID, pNewEntry, SORT_NONE);
    _PB_SortInsertedEntry(PVR_BROWSER_RESERVED_ENTRY_INDEX, u16NewEntryTargetSlotID, pNewEntry, SORT_FILE_NAME);
    _PB_SortInsertedEntry(PVR_BROWSER_RESERVED_ENTRY_INDEX, u16NewEntryTargetSlotID, pNewEntry, SORT_PROG_NAME);
    _PB_SortInsertedEntry(PVR_BROWSER_RESERVED_ENTRY_INDEX, u16NewEntryTargetSlotID, pNewEntry, SORT_CHANNEL_NAME);
    _PB_SortInsertedEntry(PVR_BROWSER_RESERVED_ENTRY_INDEX, u16NewEntryTargetSlotID, pNewEntry, SORT_PROG_TIME);
    _PB_SortInsertedEntry(PVR_BROWSER_RESERVED_ENTRY_INDEX, u16NewEntryTargetSlotID, pNewEntry, SORT_FILE_LENGTH);
    i = u16NewEntryTargetSlotID / 8;
    j = u16NewEntryTargetSlotID % 8;
    SETBIT(_PB_EntrySlotMap[i],j);

    _PB_TotalFileNum++;
    _PB_LatestInsertedSlotIdx = u16NewEntryTargetSlotID;

    _PB_lastPhysicalIndex = PVR_NULL_FILE_INDEX;
    _PB_lastLogicalIndex = PVR_NULL_FILE_INDEX;
    _PB_lastSortType = SORT_NONE;

    return u16NewEntryTargetSlotID;;
}


/******************************************************************************/
/// Function: remove a browser entry from list
/// @param
/// @return
/******************************************************************************/
static E_PVR_RET _PB_DeleteEntryFromDB(const U16 DelEntrySlotId)
{
    U16 i;
    U8 j;
    U8 InUse;
#if( ENABLE_HALF_PVR == 0 )
    if ((DelEntrySlotId == PVR_BROWSER_RESERVED_ENTRY_INDEX)||
        (DelEntrySlotId >= MAX_PVR_BROWSER_ENTRY_NUM))
#endif
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]arg error\n"));
        return E_PVR_RET_ARG_INVALID;
    }

    i = DelEntrySlotId / 8;
    j = DelEntrySlotId % 8;

    //coverity dead_error_line: Cannot reach dead statement "return E_PVR_RET_FAIL;"
    //if(i >= MAX_PVR_BROWSER_ENTRY_SLOT_MAP)
    //    return E_PVR_RET_FAIL; // PVR OVERRUN STATIC

    InUse = GETBIT(_PB_EntrySlotMap[i], j);
    if (!InUse)
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]Oops!try to delete an unused slot\n"));
        return E_PVR_RET_FAIL;
    }

    _PB_RemoveEntryBySort(DelEntrySlotId, SORT_NONE);
    _PB_RemoveEntryBySort(DelEntrySlotId, SORT_FILE_NAME);
    _PB_RemoveEntryBySort(DelEntrySlotId, SORT_PROG_NAME);
    _PB_RemoveEntryBySort(DelEntrySlotId, SORT_CHANNEL_NAME);
    _PB_RemoveEntryBySort(DelEntrySlotId, SORT_PROG_TIME);
    _PB_RemoveEntryBySort(DelEntrySlotId, SORT_FILE_LENGTH);

    CLRBIT(_PB_EntrySlotMap[i],j);
    _PB_TotalFileNum--;
    return E_PVR_RET_OK;

}


/******************************************************************************/
/// Helper function:
/// @param
/// @return: Physical index
/******************************************************************************/
static U16 _PB_GetPhysicalIndex(SORT_TYPE sortList, const SEARCH_DIRECTION Dir, const U16 FromPhysicalIndex, const U16 offset)
{
    U16 SlotId = NULL_SLOT_INDEX;
    U16 idx;

    //__ASSERT( MAX_PVR_BROWSER_ENTRY_NUM > StartingEntrySlotId);
    if ((sortList >= SORT_TYPE_NUM) ||
        (Dir >= LIST_DIRECTION_NUM) ||
        (FromPhysicalIndex > MAX_PVR_BROWSER_ENTRY_NUM))
    {
        __ASSERT(0);
//        PVR_BROWSER_DBG(printf("sortList=%bx\n",sortList));
//        PVR_BROWSER_DBG(printf("Dir=%bx\n",Dir));
//        PVR_BROWSER_DBG(printf("FromPhysicalIndex=%d\n",FromPhysicalIndex));
//        PVR_BROWSER_DBG(printf("offset=%d\n",offset));
        return NULL_SLOT_INDEX;
    }

    SlotId = FromPhysicalIndex;

    for (idx=0; idx<offset; idx++)
    {
        if (Dir == LIST_DIRECTION_UP)
            SlotId = _PB_GetPrevEntryIndex(SlotId, sortList);
        else if (Dir == LIST_DIRECTION_DOWN)
            SlotId = _PB_GetNextEntryIndex(SlotId, sortList);
#if( ENABLE_HALF_PVR == 0 )
        __ASSERT( MAX_PVR_BROWSER_ENTRY_NUM > SlotId );
#endif
    }

   return SlotId;

}

#if PRINT_LIST_DATA
/// debug function; default disable
/******************************************************************************/
/// Debug function:
/// @param
/// @return
/******************************************************************************/
static E_PVR_RET _PB_PrintAllEntryData(SORT_TYPE sortList)
{
    PVR_BROWSER_ENTRY entry;
    //U16 EntryNum = 0;
    U32 addr;
    U16 idx;
    U16 tmpStr[256];
    U16 u16ItemIdx = 0;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_FAIL;
    }

    if (sortList >= SORT_TYPE_NUM)
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]arg error\n"));
        return E_PVR_RET_FAIL;
    }

    printf("PVR_BROWSER::start list traverse...\n");
    switch(sortList)
    {
      case SORT_NONE:
        printf("Sort Type : NONE\n");
        break;
      case SORT_PROG_NAME:
        printf("Sort Type : PROGRAM NAME\n");
        break;
      case SORT_CHANNEL_NAME:
        printf("Sort Type : CHANNEL NAME\n");
        break;
      case SORT_PROG_TIME:
        printf("Sort Type : PROGRAM TIME\n");
        break;
      case SORT_FILE_NAME:
        printf("Sort Type : FILE NAME\n");
        break;
      case SORT_FILE_LENGTH:
        printf("Sort Type : FILE LENGTH\n");
        break;
    }

    printf("------------------------------------------\n");
    printf("[INDEX]          [DATA]\n");
    printf("------------------------------------------\n");

    idx = _PB_GetPhysicalIndex(sortList, LIST_DIRECTION_DOWN, PVR_BROWSER_RESERVED_ENTRY_INDEX, 1);
    while (idx != PVR_BROWSER_RESERVED_ENTRY_INDEX)
    {
    #ifdef PVR_UTOPIA
        addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(idx*sizeof(PVR_BROWSER_ENTRY));
        MEM_CHECK(addr);
        MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(&entry)), sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);    //load to buffer entry
    #else
        addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(idx*sizeof(PVR_BROWSER_ENTRY));
        MEM_CHECK(addr);
        MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&entry), sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);    //load to buffer entry
    #endif
        //printf("[slotId] %u\n", idx);
        printf("[%u]  ", u16ItemIdx);
        printf("%4u%2bu%2bu %2bu:%2bu:%2bu|",
                entry.ProgTime.u16Year, entry.ProgTime.u8Month, entry.ProgTime.u8Day,
                entry.ProgTime.u8Hour, entry.ProgTime.u8Min, entry.ProgTime.u8Sec);
        memset(tmpStr, 0, sizeof(tmpStr));
        memcpy(tmpStr,entry.u16ChannelName,sizeof(entry.u16ChannelName));
        FS_Unicode2ASCII(tmpStr);
        printf("%s|", tmpStr);
        memset(tmpStr, 0, sizeof(tmpStr));
        memcpy(tmpStr,entry.u16ProgramName,sizeof(entry.u16ProgramName));
        FS_Unicode2ASCII(tmpStr);
        printf("%s|", tmpStr);
        memset(tmpStr, 0, sizeof(tmpStr));
        memcpy(tmpStr,entry.u16FileName,sizeof(entry.u16FileName));
        FS_Unicode2ASCII(tmpStr);
        printf("%s\n", tmpStr);

        printf("[ProgTime]%u %bu %bu %bu %bu %bu\n",entry.ProgTime.u16Year,
            entry.ProgTime.u8Month,entry.ProgTime.u8Day, entry.ProgTime.u8Hour, entry.ProgTime.u8Min, entry.ProgTime.u8Sec);

        //printf("[Prev] %u \n", entry.idxPrev);
        //printf("[Next] %u \n", entry.idxNext);
        //printf("======================================\n");

        u16ItemIdx++;

        if (u16ItemIdx > _PB_TotalFileNum)
        {
            __ASSERT(0);
            PVR_BROWSER_DBG(printf("[ERR]list error\n"));
            return E_PVR_RET_FAIL;
        }

        idx =  _PB_GetPhysicalIndex(sortList, LIST_DIRECTION_DOWN, idx, 1);;
    }


    if (u16ItemIdx != _PB_TotalFileNum)
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]list broken or check _PB_TotalFileNum\n"));
        return E_PVR_RET_FAIL;
    }

    printf("------------------------------------------\n");
    printf("PVR_BROWSER::End List traverse!\n Total Entry:%u \n",u16ItemIdx);

    return E_PVR_RET_OK;

}
#endif

////////////////////////////////////////////////////////////////////////////////
// [INTERFACE section] Browser Startup - entry point
//  Create/Destroy/SelectSortList
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/// Helper function: Init PVR_BROWSER_BUFFER_ADR memory pool & related var
/// @param
/// @return
/******************************************************************************/
static E_PVR_RET _PB_BrowserInit(void)
{
    PVR_BROWSER_ENTRY *pListHeader;
    U8 i,j;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_FAIL;
    }

    //printf("_PB_ADDR_RESERVE=0x%X\n", _PB_ADDR_RESERVE);

#if 1//def MIPS_CHAKRA //[mips]
    _PB_ADDR_RESERVE = (U32)PvrGetBrowBufAddr_VA() + (U32)PVR_BROWSER_RESERVED_ENTRY_INDEX * sizeof(PVR_BROWSER_ENTRY);

    //printf("_PB_ADDR_RESERVE=0x%X\n", _PB_ADDR_RESERVE);
#endif
    ///LIST HEADER(PVR_BROWSER_RESERVED_ENTRY_INDEX = 0) init

#if 0//def PVR_8051
    MDrv_Sys_PushXdataWindow1Base();
    MDrv_Sys_SetXdataWindow1Base(_PB_ADDR_RESERVE>>12);

    pListHeader = (PVR_BROWSER_ENTRY xdata *)(msAPI_MIU_GetW1StartAddress() + ((U16)_PB_ADDR_RESERVE & 0xFFF));
#else
    pListHeader = (PVR_BROWSER_ENTRY *)_PB_ADDR_RESERVE;
    //printf("pListHeader=0x%X\n", (U32)pListHeader);
#endif

    memset(pListHeader->u16FileName,0,sizeof(pListHeader->u16FileName));
    memset(pListHeader->u16ProgramName,0,sizeof(pListHeader->u16ProgramName));
    memset(pListHeader->u16ChannelName,0,sizeof(pListHeader->u16ChannelName));
    memset(&(pListHeader->u32StartTime),0,sizeof(U32));
    memset(&(pListHeader->u32Duration),0,sizeof(U32));
    memset(&(pListHeader->enServiceType),0,sizeof(MEMBER_SERVICETYPE));
    memset(&(pListHeader->u64FileLength),0,sizeof(LongLong));

    pListHeader->idxPrev                = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxNext                = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByFilePrev      = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByFileNext      = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByProgPrev      = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByProgNext      = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByChannelPrev   = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByChannelNext   = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByStdTimePrev   = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByStdTimeNext   = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByFileSizePrev  = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    pListHeader->idxSortByFileSizeNext  = PVR_BROWSER_RESERVED_ENTRY_INDEX;

#if 0//def PVR_8051
    MDrv_Sys_PopXdataWindow1Base();
#endif
    ///init list
    _PB_LatestInsertedSlotIdx      = NULL_SLOT_INDEX;
    _PB_TotalFileNum               = 0;

    ///init slot map to 0(not used)
    memset(_PB_EntrySlotMap, 0, sizeof(_PB_EntrySlotMap));

    ///lock reserved entry bit
    i = PVR_BROWSER_RESERVED_ENTRY_INDEX / 8;
    j = PVR_BROWSER_RESERVED_ENTRY_INDEX % 8;
    SETBIT(_PB_EntrySlotMap[i],j);

    return E_PVR_RET_OK;
}

//EntryAddr : Virtual Address
static BOOLEAN _PB_SaveFAT32FileInfo(U16 *FileName, U32 EntryAddr)
{
    U8 u8fHandler;

    u8fHandler = msAPI_PVRFS_FileOpen(FileName, PVRFS_OPEN_FOR_WRITE);
    if( u8fHandler == INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        U16 RecordPathSeg = sizeof(_msAPI_PVR_RecordPath);
        U16 u16RemainLength  = sizeof(PVR_BROWSER_ENTRY)-24; //minus sorting index
        U8  u8WriteLength;
        U8  u8Segment = 0;
        LongLong llSeekLen;
        U32 u32fsWriteLen;

        // for coverity error
        RecordPathSeg += 183;
        RecordPathSeg = RecordPathSeg/184;

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
            msAPI_MIU_Copy(_VA2PA(EntryAddr)+184*u8Segment, _VA2PA(PvrGetWriteMetadataBufAddr()) + PVR_TS_PACKET_SIZE*(u8Segment+RecordPathSeg) + PVR_TS_PACKET_HEADER_SIZE, u8WriteLength, MIU_SDRAM2SDRAM);
            u16RemainLength -= u8WriteLength;
            u8Segment++;
        }

        llSeekLen.Lo = PVR_TS_PACKET_SIZE*RecordPathSeg;
        llSeekLen.Hi = 0;
        msAPI_PVRFS_FileSeek(u8fHandler, llSeekLen, PVRFS_SEEK_OPTION_FROM_BEGIN);
        u32fsWriteLen = msAPI_PVRFS_FileWrite(u8fHandler, PvrGetWriteMetadataBufAddr() + (PVR_TS_PACKET_SIZE*RecordPathSeg), META_DATA_SIZE - (PVR_TS_PACKET_SIZE*RecordPathSeg));
        msAPI_PVRFS_FileClose(u8fHandler);
    }
    return TRUE;
}

//****************************************************************************
/// Create, Init PVR browser database
/// @param u8DriveID     \b IN: Drive ID of USB
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_Create(U8 u8DriveID)
{
    PVR_BROWSER_ENTRY E;
    U16 ret;

    /// START preliminary work: check system drive status&register drive to FS
    if (!msAPI_FCtrl_IsDriveMounted(u8DriveID))
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]Drive[%bu] not ready\n",u8DriveID));
        return E_PVR_RET_DRV_NOT_READY;

    }

    if (E_PVR_RET_FAIL == _PB_BrowserInit())
    {
        return E_PVR_RET_FAIL;
    }

    _PB_BrowserInit();
    if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
           msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    {
        U8 u8EnvironmentID = msAPI_FSEnv_Register(msAPI_PVRFS_GetDriveIndex());
        FileEntry fileEntry;

        if(u8EnvironmentID == INVALID_FS_ENVIRONMENT_INDEX)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }

        MApp_TimeShift_DelTsFileName();

        if (msAPI_PVRFS_GetFirstPVRFile(u8EnvironmentID, &fileEntry))
        {
            do
            {
                U8 u8fHandler;
                U32 u32ReadLength;

                u8fHandler = msAPI_FCtrl_FileOpen(&fileEntry, OPEN_MODE_FOR_READ);
                if( u8fHandler == INVALID_FILE_HANDLE)
                {
                    __ASSERT(0);
                    msAPI_FSEnv_UnRegister(u8EnvironmentID);
                    return E_PVR_RET_FAIL;
                }
                else
                {
                    LongLong llSeekLength;
                    U32 u32ReadPointer = PVR_TRICK_MODE_ADR;
                    BOOLEAN bret = 0;

                    llSeekLength = msAPI_PVRFS_FileLength(u8fHandler);
                    llSeekLength.Lo = (llSeekLength.Lo / 192 - 1) * 192;
                    bret = msAPI_PVRFS_FileSeek(u8fHandler,llSeekLength,PVRFS_SEEK_OPTION_FROM_BEGIN);
                    u32ReadLength = msAPI_PVRFS_FileRead(u8fHandler,  _PA2VA(u32ReadPointer), 192);

                    if (((*((U8 *)(_PA2VA(u32ReadPointer) + 0))) == 0x2)
                        && ((*((U8 *)(_PA2VA(u32ReadPointer) + 1))) == 0x1E)
                        && ((*((U8 *)(_PA2VA(u32ReadPointer) + 2))) == 0x15)
                        && ((*((U8 *)(_PA2VA(u32ReadPointer) + 3))) == 0x76)
                        && ((*((U8 *)(_PA2VA(u32ReadPointer) + 4))) == 0x47)
                        && ((*((U8 *)(_PA2VA(u32ReadPointer) + 5))) == 0xFF)
                        && ((*((U8 *)(_PA2VA(u32ReadPointer) + 6))) == 0xFF))
                    {
                        printf("\nPVR file length wrong!!!\n");
                        continue;
                    }

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

                    U16 RecordPathSeg = sizeof(_msAPI_PVR_RecordPath);
                    U16 u16RemainLength  = sizeof(PVR_BROWSER_ENTRY)-24;  //minus index data
                    U8  u8ReadLength;
                    U8  u8Segment = 0;
                    LongLong llSeekLen;

                    // for coverity error
                    RecordPathSeg += 183;
                    RecordPathSeg = RecordPathSeg/184;

                    llSeekLen.Lo = PVR_TS_PACKET_SIZE*RecordPathSeg;
                    llSeekLen.Hi = 0;
                    msAPI_PVRFS_FileSeek(u8fHandler, llSeekLen, PVRFS_SEEK_OPTION_FROM_BEGIN);
                    u32ReadLength = msAPI_PVRFS_FileRead(u8fHandler, PvrGetReadMetadataBufAddr()+(PVR_TS_PACKET_SIZE*RecordPathSeg), META_DATA_SIZE - (PVR_TS_PACKET_SIZE*RecordPathSeg));

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
                    #ifdef PVR_UTOPIA
                        MApi_BDMA_Copy(((PVR_READ_METADATA_BUFFER_MEMORY_TYPE&MIU1)?PVR_READ_METADATA_BUFFER_ADR|MIU_INTERVAL:PVR_READ_METADATA_BUFFER_ADR)+PVR_TS_PACKET_SIZE*(u8Segment+RecordPathSeg) + PVR_TS_PACKET_HEADER_SIZE, _VA2PA(msAPI_MIU_XData2SDRAMAddr((U32)&E+184*u8Segment)), u8ReadLength, MIU_SDRAM2SDRAM);//store new entry to slotid
                    #else //Chakra1
                        msAPI_MIU_Copy(PvrGetReadMetadataBufAddr()+PVR_TS_PACKET_SIZE*(u8Segment+RecordPathSeg) + PVR_TS_PACKET_HEADER_SIZE, msAPI_MIU_XData2SDRAMAddr((U32)&E+184*u8Segment), u8ReadLength, MIU_SDRAM2SDRAM);
                    #endif

                        u16RemainLength -= u8ReadLength;
                        u8Segment++;
                    }

                    msAPI_PVRFS_GetFileNameByFileEntry(u8EnvironmentID, &fileEntry,  msAPI_MIU_XData2SDRAMAddr((U32)(E.u16FileName)), PVR_BROWSER_MAX_FILE_NAME_LEN);

                    E.u16FileName[PVR_BROWSER_MAX_FILE_NAME_LEN-1] = 0;
                    E.u16ProgramName[PVR_BROWSER_MAX_PROGRAM_NAME_LEN-1] = 0;
                    E.u16ChannelName[PVR_BROWSER_MAX_CHANNEL_NAME_LEN-1] = 0;
                    E.u16ProgDesc[PVR_BROWSER_MAX_PROGRAM_DESC_LEN-1] = 0;

                    if (E.u32Duration == 0)
                    {
                    #if (PVR_TS_PACKET_SIZE == 192)
                        E.u32Duration = msAPI_PVR_PlaybackGetTotalTimeByTimeStamp(tmpPvrRecordMeataData.enEncryptionType, u8fHandler)/10;
                    #endif
                    }

                    msAPI_FCtrl_FileClose(u8fHandler);
                    ret = _PB_AddEntryToDB(&E);
                    ///should not happen when pool buffer size is large enough;
                    if (ret == NULL_SLOT_INDEX)
                    {
                        __ASSERT(0);
                        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]_PB_AddEntryToDB fail\n"));
                        break;
                    }
                }

            }while(msAPI_PVRFS_GetNextPVRFile(u8EnvironmentID, &fileEntry));
        }

        msAPI_FSEnv_UnRegister(u8EnvironmentID);
    }
#if (ENABLE_BULK_FILE_SYSTEM)
    else  //if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
    {
        U16 bulkFileName[PVR_BROWSER_MAX_FILE_NAME_LEN];
        U16 nameLen, bufLen;
        BKFS_POSITION pos;
        BFK_PARA_OPT_RES BKF_RET;
        U16 u16BulkFileID = INVALID_BULK_FILE_ID;

        pos = msAPI_PVRFS_FindFirstPOS();

        memset(bulkFileName,0,sizeof(bulkFileName));
        nameLen = PVR_BROWSER_MAX_FILE_NAME_LEN-1;

        while ((pos = msAPI_PVRFS_FindNextBulkFile(pos, bulkFileName, &nameLen))!=0)
        {
            __ASSERT(nameLen>0);
            memset(E.u16FileName, 0, sizeof(E.u16FileName));
            memcpy(E.u16FileName, bulkFileName, sizeof(U16)*nameLen);
            E.u16FileName[nameLen] = '\0';

            ///get program name
            bufLen =  PVR_BROWSER_MAX_PROGRAM_NAME_LEN-1;//sizeof(E.u16ProgramName);
            BKF_RET = msAPI_PVRFS_GetBulkFileInfo(E.u16FileName,&u16BulkFileID, BKF_PARA_PROGRAM_NAME,E.u16ProgramName,&bufLen);

            if (BKF_RET == BKF_PARA_SUCCESS)
            {
                E.u16ProgramName[bufLen] = '\0';
            }
            else
            {
                switch (BKF_RET)
                {
                  case BKF_PARA_ERROR_NOFILE:
                  case BKF_PARA_LEAK_OF_RET_BUFF:
                  case BKF_PARA_INVALID_PARAM:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET invalid parameter\n"));
                    E.u16ProgramName[0] = '\0';
                    break;
                  case BKF_PARA_ERROR_STORAGE:
                  case BKF_PARA_ERROR_BAD_SECTOR_DATA:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET usb disk error\n"));
                    E.u16ProgramName[0] = '\0';
                    //return E_PVR_RET_DISK_ERROR;
                    break;
                  default:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET unexpected return value\n"));
                }
            }

            ///get channel name
            bufLen = PVR_BROWSER_MAX_CHANNEL_NAME_LEN-1;//sizeof(E.u16ChannelName);
            BKF_RET = msAPI_PVRFS_GetBulkFileInfo(E.u16FileName,&u16BulkFileID,BKF_PARA_CHANNEL_NAME,E.u16ChannelName,&bufLen);

            if (BKF_RET == BKF_PARA_SUCCESS)
            {
                E.u16ChannelName[bufLen] = '\0';
            }
            else
            {
                switch (BKF_RET)
                {
                  case BKF_PARA_ERROR_NOFILE:
                  case BKF_PARA_LEAK_OF_RET_BUFF:
                  case BKF_PARA_INVALID_PARAM:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET invalid parameter\n"));
                    E.u16ChannelName[0] = '\0';
                    break;
                  case BKF_PARA_ERROR_STORAGE:
                  case BKF_PARA_ERROR_BAD_SECTOR_DATA:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET usb disk error\n"));
                    E.u16ChannelName[0] = '\0';
                    //return E_PVR_RET_DISK_ERROR;
                    break;
                  default:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET unexpected return value\n"));
                }
            }

            ///get program description
            bufLen = PVR_BROWSER_MAX_PROGRAM_DESC_LEN-1;//sizeof(E.u16ProgDesc);
            BKF_RET = msAPI_PVRFS_GetBulkFileInfo(E.u16FileName,&u16BulkFileID,BKF_PARA_PROGRAM_DESC,E.u16ProgDesc,&bufLen);

            if (BKF_RET == BKF_PARA_SUCCESS)
            {
                E.u16ProgDesc[bufLen] = '\0';
            }
            else
            {
                switch (BKF_RET)
                {
                  case BKF_PARA_ERROR_NOFILE:
                  case BKF_PARA_LEAK_OF_RET_BUFF:
                  case BKF_PARA_INVALID_PARAM:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET invalid parameter\n"));
                    E.u16ProgDesc[0] = '\0';
                    break;
                  case BKF_PARA_ERROR_STORAGE:
                  case BKF_PARA_ERROR_BAD_SECTOR_DATA:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET usb disk error\n"));
                    E.u16ProgDesc[0] = '\0';
                    //return E_PVR_RET_DISK_ERROR;
                    break;
                  default:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET unexpected return value\n"));
                }
            }

            ///get program time
            bufLen = sizeof(U32);
            BKF_RET = msAPI_PVRFS_GetBulkFileInfo(E.u16FileName,&u16BulkFileID, BKF_PARA_STARTDT, &(E.u32StartTime), &bufLen);
            if ((BKF_RET != BKF_PARA_SUCCESS))
            {
                memset(&(E.u32StartTime), 0, sizeof(U32));

                switch (BKF_RET)
                {
                  case BKF_PARA_ERROR_NOFILE:
                  case BKF_PARA_LEAK_OF_RET_BUFF:
                  case BKF_PARA_INVALID_PARAM:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET invalid parameter\n"));
                    break;
                  case BKF_PARA_ERROR_STORAGE:
                  case BKF_PARA_ERROR_BAD_SECTOR_DATA:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET usb disk error\n"));
                    //return E_PVR_RET_DISK_ERROR;
                    break;
                  default:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET unexpected return value\n"));
                }
            }

            ///get duration
            bufLen = sizeof(U32);
            BKF_RET = msAPI_PVRFS_GetBulkFileInfo(E.u16FileName,&u16BulkFileID, BKF_PARA_DURATION, &(E.u32Duration), &bufLen);

            if ((BKF_RET != BKF_PARA_SUCCESS))
            {
                memset(&(E.u32Duration), 0, sizeof(U32));

                switch (BKF_RET)
                {
                  case BKF_PARA_ERROR_NOFILE:
                  case BKF_PARA_LEAK_OF_RET_BUFF:
                  case BKF_PARA_INVALID_PARAM:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET invalid parameter\n"));
                    break;
                  case BKF_PARA_ERROR_STORAGE:
                  case BKF_PARA_ERROR_BAD_SECTOR_DATA:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET usb disk error\n"));
                    //return E_PVR_RET_DISK_ERROR;
                    break;
                  default:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET unexpected return value\n"));
                }
            }

            ///get service type
            bufLen = sizeof(MEMBER_SERVICETYPE);
            BKF_RET = msAPI_PVRFS_GetBulkFileInfo(E.u16FileName,&u16BulkFileID, BKF_PARA_SERVICE_TYPE, &(E.enServiceType), &bufLen);

            if ((BKF_RET != BKF_PARA_SUCCESS))
            {
                memset(&(E.enServiceType), 0, sizeof(MEMBER_SERVICETYPE));

                switch (BKF_RET)
                {
                  case BKF_PARA_ERROR_NOFILE:
                  case BKF_PARA_LEAK_OF_RET_BUFF:
                  case BKF_PARA_INVALID_PARAM:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET invalid parameter\n"));
                    break;
                  case BKF_PARA_ERROR_STORAGE:
                  case BKF_PARA_ERROR_BAD_SECTOR_DATA:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET usb disk error\n"));
                    break;
                  default:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET unexpected return value\n"));
                }
            }

            ///get file length
            bufLen = sizeof(E.u64FileLength);
            BKF_RET = msAPI_PVRFS_GetBulkFileInfo(E.u16FileName,&u16BulkFileID,BKF_PARA_TELL_FILELENGTH,&(E.u64FileLength),&bufLen);

            if ((BKF_RET != BKF_PARA_SUCCESS))
            {
                memset(&(E.u64FileLength), 0, sizeof(E.u64FileLength));

                switch (BKF_RET)
                {
                  case BKF_PARA_ERROR_NOFILE:
                  case BKF_PARA_LEAK_OF_RET_BUFF:
                  case BKF_PARA_INVALID_PARAM:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET invalid parameter\n"));
                    break;
                  case BKF_PARA_ERROR_STORAGE:
                  case BKF_PARA_ERROR_BAD_SECTOR_DATA:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET usb disk error\n"));
                    //return E_PVR_RET_DISK_ERROR;
                    break;
                  default:
                    __ASSERT(0);
                    PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]BKF_RET unexpected return value\n"));
                }
            }

            ret = _PB_AddEntryToDB(&E);

            ///should not happen when pool buffer size is large enough;
            if (ret == NULL_SLOT_INDEX)
            {
                __ASSERT(0);
                PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]_PB_AddEntryToDB fail\n"));
                break;
            }
            /// clean for next iteration
            memset(bulkFileName,0,sizeof(bulkFileName));
            nameLen = PVR_BROWSER_MAX_FILE_NAME_LEN;
            u16BulkFileID = INVALID_BULK_FILE_ID;
        }
    }
#endif
#if PRINT_LIST_DATA
        printf("dump list data...\n");
        _PB_PrintAllEntryData(SORT_PROG_NAME);
        _PB_PrintAllEntryData(SORT_CHANNEL_NAME);
        _PB_PrintAllEntryData(SORT_PROG_TIME);
#endif

    return E_PVR_RET_OK;
}

//****************************************************************************
/// Clear PVR Browser DB
/// @param none
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_Destroy(void)
{
    _PB_BrowserInit();

    return E_PVR_RET_OK;

}

//****************************************************************************
/// Add new file entry to Browser
/// @param pNewEntry     \b IN: PVR_UI_BROWSER_ENTRY
/// @return E_PVR_RET
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_AddNewEntry(PVR_UI_BROWSER_ENTRY *pNewEntry)
{
    PVR_BROWSER_ENTRY E;
    U16 u16Len;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_ARG_INVALID;
    }

    memset(&E, 0, sizeof(PVR_BROWSER_ENTRY));

    if (pNewEntry == NULL)
    {
        __ASSERT(0);
        return E_PVR_RET_ARG_INVALID;
    }

    ///filename
    if ((u16Len = UnicodeLen((S8*)pNewEntry->u16FileName)) == 0)
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("PVR_BROWSER::[ERR]no file name\n"));
        return E_PVR_RET_ARG_INVALID;
    }

    UnicodeCpy((S8 *) E.u16FileName, (S8 *) pNewEntry->u16FileName);
    UnicodeCpy((S8 *) E.u16ProgramName, (S8 *) pNewEntry->u16ProgramName);
    UnicodeCpy((S8 *) E.u16ChannelName, (S8 *) pNewEntry->u16ChannelName);
    UnicodeCpy((S8 *) E.u16ProgDesc, (S8 *) pNewEntry->u16ProgDesc);

    //avoid data length over flow
    E.u16FileName[PVR_BROWSER_MAX_FILE_NAME_LEN-1] = 0;
    E.u16ProgramName[PVR_BROWSER_MAX_PROGRAM_NAME_LEN-1] = 0;
    E.u16ChannelName[PVR_BROWSER_MAX_CHANNEL_NAME_LEN-1] = 0;
    E.u16ProgDesc[PVR_BROWSER_MAX_PROGRAM_DESC_LEN-1] = 0;

    ///other attribute
    E.u64FileLength = pNewEntry->u64FileLength;
    E.u32StartTime  = pNewEntry->u32StartTime;
    E.u32Duration   = pNewEntry->u32Duration;
    E.enServiceType = pNewEntry->enServiceType;

    if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
           msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
    {
        U16 SlotNumber;
        U32 EntryAddr;

        SlotNumber = _PB_AddEntryToDB(&E);
        if ( SlotNumber == NULL_SLOT_INDEX)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }

    #if 1//def PVR_UTOPIA
        //EntryAddr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : (PvrGetBrowBufAddr()))+(U32)SlotNumber*sizeof(PVR_BROWSER_ENTRY);
        EntryAddr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(SlotNumber);
    #else
        EntryAddr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)SlotNumber*sizeof(PVR_BROWSER_ENTRY);
    #endif

        if(_PB_SaveFAT32FileInfo(E.u16FileName, EntryAddr) == FALSE)
            return E_PVR_RET_FAIL;
    }
#if (ENABLE_BULK_FILE_SYSTEM)
    else  //msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS
    {
        U16 u16BulkFileID = INVALID_BULK_FILE_ID;
        BFK_PARA_OPT_RES ret;

        ret = msAPI_PVRFS_SetBulkFileInfo(E.u16FileName, &u16BulkFileID, BKF_PARA_CHANNEL_NAME, E.u16ChannelName, sizeof(E.u16ChannelName));
        if( ret != BKF_PARA_SUCCESS)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }

        ret = msAPI_PVRFS_SetBulkFileInfo(E.u16FileName, &u16BulkFileID, BKF_PARA_PROGRAM_NAME, E.u16ProgramName, sizeof(E.u16ProgramName));
        if( ret != BKF_PARA_SUCCESS)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }

        ret = msAPI_PVRFS_SetBulkFileInfo(E.u16ProgDesc, &u16BulkFileID, BKF_PARA_PROGRAM_DESC, E.u16ProgDesc, sizeof(E.u16ProgDesc));
        if( ret != BKF_PARA_SUCCESS)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }

        ret = msAPI_PVRFS_SetBulkFileInfo(E.u16FileName, &u16BulkFileID, BKF_PARA_STARTDT, &E.u32StartTime, sizeof(U32));
        if( ret != BKF_PARA_SUCCESS)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }

        ret = msAPI_PVRFS_SetBulkFileInfo(E.u16FileName, &u16BulkFileID, BKF_PARA_DURATION, &E.u32Duration, sizeof(U32));

        if( ret != BKF_PARA_SUCCESS)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }

        if (_PB_AddEntryToDB(&E) == NULL_SLOT_INDEX)
        {
            __ASSERT(0);
            return E_PVR_RET_FAIL;
        }
    }
#endif
    return E_PVR_RET_OK;
}

static E_PVR_RET _PB_GetFileAttribute(PVR_FILE_ATTRIBUTE_MEMBER AttribType, U16 PhysicalIndex, BYTE *pBuffer, const U16 BufLen)
{
    PVR_BROWSER_ENTRY E;
    U32 addr;
    U16 u16OutDataLen;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_ARG_INVALID;
    }

    if ((AttribType >= PVR_PARA_NUM) ||
        (pBuffer == NULL) || (BufLen == 0))
    {
        __ASSERT(0);
        return E_PVR_RET_ARG_INVALID;
    }

    if(AttribType == E_PVR_ATTR_IS_PLAYING)
    {
        if(PhysicalIndex == _PB_PlayingPhysicalIndex)
            pBuffer[0] = TRUE;
        else
            pBuffer[0] = FALSE;
        return E_PVR_RET_OK;
    }
    if(AttribType == E_PVR_ATTR_IS_RECORDING)
    {
        if(PhysicalIndex == _PB_RecordingPhysicalIndex)
            pBuffer[0] = TRUE;
        else
            pBuffer[0] = FALSE;
        return E_PVR_RET_OK;
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)PvrGetBrowBufAddr() + (U32)(PhysicalIndex*sizeof(PVR_BROWSER_ENTRY));
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(PhysicalIndex);

    MEM_CHECK(addr);
    MApi_BDMA_Copy(_VA2PA(addr),_VA2PA(GET_DRAM_ADDR(&E)) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(PhysicalIndex*sizeof(PVR_BROWSER_ENTRY));
    MEM_CHECK(addr);
    MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&E) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#endif

    pBuffer[0] = 0;

    switch(AttribType)
    {
        case E_PVR_ATTR_PROGRAM_NAME:
        {
            u16OutDataLen = UnicodeLen((S8 *) E.u16ProgramName);

            if (u16OutDataLen > BufLen)
            {
                __ASSERT(0);
                PVR_BROWSER_DBG(printf("PVR_BROWSER::[INFO]Data truncated(BufLen smaller than actual data length)\n"));
                memcpy(pBuffer, &E.u16ProgramName[0], BufLen*sizeof(U16));
                pBuffer[BufLen-1] = 0;
                pBuffer[BufLen-2] = 0;
                PVR_BROWSER_DBG(printf("E_PVR_RET_BUF_SIZE_NOT_ENOUGH\n"));
                return E_PVR_RET_BUF_SIZE_NOT_ENOUGH;
            }

            UnicodeCpy((S8*)pBuffer, (S8*)E.u16ProgramName);
        }
        break;

        case E_PVR_ATTR_CHANNEL_NAME:
        {
            u16OutDataLen = UnicodeLen((S8 *) E.u16ChannelName);
            if (u16OutDataLen > BufLen)
            {
                __ASSERT(0);
                PVR_BROWSER_DBG(printf("PVR_BROWSER::[INFO]Data truncated(BufLen smaller than actual data length)\n"));
                memcpy(pBuffer, &E.u16ChannelName[0], BufLen*sizeof(U16));
                pBuffer[BufLen-1] = 0;
                pBuffer[BufLen-2] = 0;
                PVR_BROWSER_DBG(printf("E_PVR_RET_BUF_SIZE_NOT_ENOUGH\n"));
                return E_PVR_RET_BUF_SIZE_NOT_ENOUGH;
            }
            UnicodeCpy((S8*)pBuffer, (S8*)E.u16ChannelName);
        }
        break;

        case E_PVR_ATTR_FILE_NAME:
        {
            u16OutDataLen = UnicodeLen((S8 *) E.u16FileName);

            if (u16OutDataLen > BufLen)
            {
                __ASSERT(0);
                PVR_BROWSER_DBG(printf("PVR_BROWSER::[INFO]Data truncated(BufLen smaller than actual data length)\n"));
                memcpy(pBuffer, &E.u16FileName[0], BufLen*sizeof(U16));
                pBuffer[BufLen-1] = 0;
                pBuffer[BufLen-2] = 0;
                return E_PVR_RET_BUF_SIZE_NOT_ENOUGH;
            }
            UnicodeCpy((S8*)pBuffer, (S8*)E.u16FileName);
        }
        break;

        case E_PVR_ATTR_PROGRAM_DESC:
        {
            u16OutDataLen = UnicodeLen((S8 *) E.u16ProgDesc);

            if (u16OutDataLen > BufLen)
            {
                __ASSERT(0);
                PVR_BROWSER_DBG(printf("PVR_BROWSER::[INFO]Data truncated(BufLen smaller than actual data length)\n"));
                memcpy(pBuffer, &E.u16ProgDesc[0], BufLen*sizeof(U16));
                pBuffer[BufLen-1] = 0;
                pBuffer[BufLen-2] = 0;
                return E_PVR_RET_BUF_SIZE_NOT_ENOUGH;
            }
            UnicodeCpy((S8*)pBuffer, (S8*)E.u16ProgDesc);
        }
        break;

        case E_PVR_ATTR_PROGRAM_START_TIME:
            //*(U32 *)pBuffer = E.u32StartTime;
            memcpy(pBuffer, &E.u32StartTime, sizeof(U32));
            break;

        case E_PVR_ATTR_PROGRAM_DURATION:
            //*(U32 *)pBuffer = E.u32Duration;
            memcpy(pBuffer, &E.u32Duration, sizeof(U32));
            break;

        case E_PVR_ATTR_SERVICE_TYPE:
            if (sizeof(MEMBER_SERVICETYPE) > BufLen)
            {
                PVR_BROWSER_DBG(printf("PVR_BROWSER::overflow)\n"));
                return E_PVR_RET_BUF_SIZE_NOT_ENOUGH;
            }
            memcpy(pBuffer, &E.enServiceType, sizeof(MEMBER_SERVICETYPE));
            break;

        default:
            __ASSERT(0);
        return E_PVR_RET_FAIL;

    }
    return E_PVR_RET_OK;
}


static U16 _PB_LogicalToPhysicalIndex( SORT_TYPE sortType, U16 LogicalIndex)
{
    U16 u16StartPhyIndex;
    U16 u16Offset;
    U16 u16PhysicalIndex;
    SEARCH_DIRECTION SortDir;

//    printf("_PB_LogicalToPhysicalIndex\n");
//    printf("sortType=%bx\n",sortType);
//    printf("LogicalIndex=%bx\n",LogicalIndex);
//    printf("_PB_lastLogicalIndex=%bx\n",_PB_lastLogicalIndex);
//    printf("_PB_lastSortType=%bx\n",_PB_lastSortType);
//    printf("_PB_lastPhysicalIndex=%d\n\n",_PB_lastPhysicalIndex);


    if (LogicalIndex == NULL_SLOT_INDEX)
    {
        __ASSERT(0);
        return E_PVR_RET_FAIL;
    }

    if(_PB_lastLogicalIndex == LogicalIndex && _PB_lastSortType == sortType)
        return _PB_lastPhysicalIndex;

    if(_PB_lastSortType == sortType && _PB_lastLogicalIndex != PVR_NULL_FILE_INDEX)
    {
        u16StartPhyIndex = _PB_lastPhysicalIndex;
        if(LogicalIndex > _PB_lastLogicalIndex)
        {
            u16Offset = LogicalIndex - _PB_lastLogicalIndex;
            SortDir = LIST_DIRECTION_DOWN;
        }
        else
        {
            u16Offset = _PB_lastLogicalIndex - LogicalIndex;
            SortDir = LIST_DIRECTION_UP;
        }
    }
    else
    {
        u16StartPhyIndex = PVR_BROWSER_RESERVED_ENTRY_INDEX;
        u16Offset = LogicalIndex+1;
        SortDir = LIST_DIRECTION_DOWN;
    }
    u16PhysicalIndex = _PB_GetPhysicalIndex(sortType, SortDir, u16StartPhyIndex, u16Offset);

//    printf("u16PhysicalIndex=%d\n\n",u16PhysicalIndex);

    _PB_lastLogicalIndex = LogicalIndex;
    _PB_lastSortType = sortType;
    _PB_lastPhysicalIndex = u16PhysicalIndex;

//    printf("lastLogicalIndex=%bx\n",_PB_lastLogicalIndex);
//    printf("lastSortType=%bx\n",_PB_lastSortType);
//    printf("lastPhysicalIndex=%d\n\n",_PB_lastPhysicalIndex);

    return u16PhysicalIndex;
}

static U16 _PB_GetLogicalIndex( SORT_TYPE sortType, U16 PhysicalIndex)
{
    U16 LogicalIndex;
    U16 CurPhysicalIndex;

//    printf("_PB_GetLogicalIndex\n");
//    printf("sortType=%bx\n",sortType);
//    printf("PhysicalIndex=%d\n",PhysicalIndex);
//    printf("_PB_lastLogicalIndex=%d\n",_PB_lastLogicalIndex);
//    printf("_PB_lastSortType=%bx\n",_PB_lastSortType);
//    printf("_PB_lastPhysicalIndex=%d\n\n",_PB_lastPhysicalIndex);

#if( ENABLE_HALF_PVR == 0 )
    if (PhysicalIndex >= MAX_PVR_BROWSER_ENTRY_NUM || PhysicalIndex == 0)
#endif
    {
        __ASSERT(0);
        return E_PVR_RET_FAIL;
    }
    CurPhysicalIndex = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    for(LogicalIndex=0;LogicalIndex<_PB_TotalFileNum;LogicalIndex++)
    {
        CurPhysicalIndex = _PB_GetPhysicalIndex(sortType, LIST_DIRECTION_DOWN, CurPhysicalIndex, 1);
        if(PhysicalIndex == CurPhysicalIndex)
        {
            _PB_lastLogicalIndex = LogicalIndex;
            _PB_lastSortType = sortType;
            _PB_lastPhysicalIndex = CurPhysicalIndex;
            return LogicalIndex;
        }
    }
    return PVR_NULL_FILE_INDEX;
}

//****************************************************************************
/// Get PVR file attribute
/// @param AttribType   \b IN: attribute type
/// -@see PVR_FILE_ATTRIBUTE_MEMBER
/// @param sortType     \b IN: sorting type of index
/// @param LogicalIndex \b IN: Logical index of file
/// @param *pBuffer     \b IN: point of return value
/// @param BufLen       \b IN: maximum length of return value
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_GetFileAttribute(PVR_FILE_ATTRIBUTE_MEMBER AttribType, SORT_TYPE sortType, U16 LogicalIndex, BYTE *pBuffer, const U16 BufLen)
{
    U16 u16PhysicalIndex;

    if(sortType <= SORT_NONE || sortType >= SORT_TYPE_NUM)
    {
        __ASSERT(0);
        return E_PVR_RET_ARG_INVALID;
    }
    u16PhysicalIndex = _PB_LogicalToPhysicalIndex(sortType, LogicalIndex);

    return _PB_GetFileAttribute(AttribType, u16PhysicalIndex, pBuffer, BufLen);
}

//****************************************************************************
/// Get PVR file all attributes
/// @param sortType     \b IN: sorting type of index
/// @param LogicalIndex \b IN: Logical index of file
/// @param *E           \b IN: point of return value
/// -@see PVR_UI_BROWSER_ENTRY
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_GetFileAttributes(SORT_TYPE sortType, U16 LogicalIndex, PVR_UI_BROWSER_ENTRY *E)
{
    U16 PhyIdx;
    PVR_BROWSER_ENTRY pvrEntry;
    U32 addr;


    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_ARG_INVALID;
    }

    if ((E == NULL))
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("invalid arg\n"));
        return E_PVR_RET_ARG_INVALID;

    }

    PhyIdx = _PB_LogicalToPhysicalIndex(sortType, LogicalIndex);
#if( ENABLE_HALF_PVR == 0 )
    if(PhyIdx == 0 || PhyIdx >= MAX_PVR_BROWSER_ENTRY_NUM)
#endif
    {
        PVR_BROWSER_DBG(printf("sortType=%bx,LogicalIndex=%d,PhyIdx=%d\n",sortType,LogicalIndex,PhyIdx));
        __ASSERT(0);
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)PhyIdx*sizeof(PVR_BROWSER_ENTRY);
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(PhyIdx);
    MEM_CHECK(addr);
    MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(&pvrEntry)) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)PhyIdx*sizeof(PVR_BROWSER_ENTRY);
    MEM_CHECK(addr);
    MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#endif

    memcpy(E->u16FileName, pvrEntry.u16FileName, sizeof(E->u16FileName));
    memcpy(E->u16ProgramName, pvrEntry.u16ProgramName, sizeof(E->u16ProgramName));
    memcpy(E->u16ChannelName, pvrEntry.u16ChannelName, sizeof(E->u16ChannelName));
    memcpy(&(E->u64FileLength), &(pvrEntry.u64FileLength), sizeof(E->u64FileLength));
    E->u32StartTime = pvrEntry.u32StartTime;
    E->u32Duration = pvrEntry.u32Duration;
    E->enServiceType = pvrEntry.enServiceType;

    if(PhyIdx == _PB_PlayingPhysicalIndex)
        E->isPlaying = TRUE;
    else
        E->isPlaying = FALSE;

    if(PhyIdx == _PB_RecordingPhysicalIndex)
        E->isRecording = TRUE;
    else
        E->isRecording = FALSE;

    return E_PVR_RET_OK;
}


//****************************************************************************
/// Get PVR file all attributes
/// @param sortType     \b IN: sorting type of index
/// @param LogicalIndex \b IN: Logical index of file
/// @param *E           \b IN: point of return value
/// -@see PVR_UI_BROWSER_ENTRY
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_GetRecordingAttributes(PVR_UI_BROWSER_ENTRY *E)
{
    PVR_BROWSER_ENTRY pvrEntry;
    U32 addr;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_ARG_INVALID;
    }

    if ((E == NULL))
    {
        __ASSERT(0);
        PVR_BROWSER_DBG(printf("invalid arg\n"));
        return E_PVR_RET_ARG_INVALID;

    }

    if(_PB_RecordingPhysicalIndex == PVR_NULL_FILE_INDEX)
        return E_PVR_RET_BROWSER_NO_FILE_IN_RECORDING;

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : (PvrGetBrowBufAddr()))+(U32)_PB_RecordingPhysicalIndex*sizeof(PVR_BROWSER_ENTRY);
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(_PB_RecordingPhysicalIndex);
    MEM_CHECK(addr);
    MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(&pvrEntry)) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)_PB_RecordingPhysicalIndex*sizeof(PVR_BROWSER_ENTRY);
    MEM_CHECK(addr);
    MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#endif

    memcpy(E->u16FileName, pvrEntry.u16FileName, sizeof(E->u16FileName));
    memcpy(E->u16ProgramName, pvrEntry.u16ProgramName, sizeof(E->u16ProgramName));
    memcpy(E->u16ChannelName, pvrEntry.u16ChannelName, sizeof(E->u16ChannelName));
    memcpy(&(E->u64FileLength), &(pvrEntry.u64FileLength), sizeof(E->u64FileLength));
    E->u32StartTime = pvrEntry.u32StartTime;
    E->u32Duration = pvrEntry.u32Duration;
    E->enServiceType = pvrEntry.enServiceType;

    return E_PVR_RET_OK;
}

//****************************************************************************
/// Get playing file attribute
/// @param AttribType   \b IN: attribute type
/// -@see PVR_FILE_ATTRIBUTE_MEMBER
/// @param *pBuffer     \b IN: point of return value
/// @param BufLen       \b IN: maximum length of return value
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_GetPlayingAttribute(PVR_FILE_ATTRIBUTE_MEMBER AttribType, BYTE *pBuffer, const U16 BufLen)
{
    if(_PB_PlayingPhysicalIndex == PVR_NULL_FILE_INDEX)
        return E_PVR_RET_BROWSER_NO_FILE_IN_PLAYING;
    else
        return _PB_GetFileAttribute(AttribType, _PB_PlayingPhysicalIndex, pBuffer, BufLen);
}

//****************************************************************************
/// Get playing file Logical Index
/// @param sortType     \b IN: sorting type of index
/// @return U32 : PVR_NULL_FILE_INDEX means no playing file
//****************************************************************************
U32 MApp_PvrBrowser_GetPlayingIndex(SORT_TYPE sortType)
{
    if(_PB_PlayingPhysicalIndex == PVR_NULL_FILE_INDEX)
        return PVR_NULL_FILE_INDEX;
    else
    {
        if(_PB_lastSortType == sortType && _PB_lastPhysicalIndex == _PB_PlayingPhysicalIndex)
            return _PB_lastLogicalIndex;
        else
            return _PB_GetLogicalIndex(sortType, _PB_PlayingPhysicalIndex);
    }
}

//****************************************************************************
/// Get recordinging file attribute
/// @param AttribType   \b IN: attribute type
/// -@see PVR_FILE_ATTRIBUTE_MEMBER
/// @param *pBuffer     \b IN: point of return value
/// @param BufLen       \b IN: maximum length of return value
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_GetRecordingAttribute(PVR_FILE_ATTRIBUTE_MEMBER AttribType, BYTE *pBuffer, const U16 BufLen)
{
    if(_PB_RecordingPhysicalIndex == PVR_NULL_FILE_INDEX)
        return E_PVR_RET_BROWSER_NO_FILE_IN_RECORDING;
    else
        return _PB_GetFileAttribute(AttribType, _PB_RecordingPhysicalIndex, pBuffer, BufLen);
}


//****************************************************************************
/// Get Recording file Logical Index
/// @param sortType     \b IN: sorting type of index
/// @return U32 : PVR_NULL_FILE_INDEX means no playing file
//****************************************************************************
U32 MApp_PvrBrowser_GetRecordingIndex(SORT_TYPE sortType)
{
    if(_PB_RecordingPhysicalIndex == PVR_NULL_FILE_INDEX)
        return PVR_NULL_FILE_INDEX;
    else
    {
        if(_PB_lastSortType == sortType && _PB_lastPhysicalIndex == _PB_RecordingPhysicalIndex)
            return _PB_lastLogicalIndex;
        else
            return _PB_GetLogicalIndex(sortType, _PB_RecordingPhysicalIndex);
    }
}

//****************************************************************************
/// Get total PVR file number
/// @param none
/// @return WORD : total file number
//****************************************************************************
U16 MApp_PvrBrowser_GetTotalFileNum(void)
{
    return _PB_TotalFileNum;
}

//****************************************************************************
/// Conver logical index between two sorting type
/// @param OldSortType   \b IN: attribute type
/// -@see SORT_TYPE
/// @param OldLogicalIndex     \b IN: Original logical index
/// @param NewSortType   \b IN: Newly sorting type
/// -@see SORT_TYPE
/// @return WORD : newly logical index of newly sorting type
//****************************************************************************
U16 MApp_PvrBrowser_ConvertIndex(SORT_TYPE OldSortType, U16 OldLogicalIndex, SORT_TYPE NewSortType)
{
    U16 PhyIdx,NewLogIdx;
    U16 CompareIdx;

    PVR_BROWSER_DBG(printf("MApp_PvrBrowser_ConvertIndex\n"));

    if(OldSortType <= SORT_NONE || OldSortType >= SORT_TYPE_NUM)
    {
        __ASSERT(0);
        return PVR_NULL_FILE_INDEX;
    }
    if(NewSortType <= SORT_NONE || NewSortType >= SORT_TYPE_NUM)
    {
        __ASSERT(0);
        return PVR_NULL_FILE_INDEX;
    }
    if(OldLogicalIndex > _PB_TotalFileNum)
    {
        __ASSERT(0);
        return PVR_NULL_FILE_INDEX;
    }

    PhyIdx = _PB_LogicalToPhysicalIndex(OldSortType, OldLogicalIndex);
#if( ENABLE_HALF_PVR == 0 )
    __ASSERT(PhyIdx > 0 && PhyIdx < MAX_PVR_BROWSER_ENTRY_NUM);
#endif
    CompareIdx = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    for(NewLogIdx=0 ; NewLogIdx<_PB_TotalFileNum ; NewLogIdx++)
    {
        CompareIdx = _PB_GetPhysicalIndex(NewSortType, LIST_DIRECTION_DOWN, CompareIdx, 1);
        if(CompareIdx == PhyIdx)
        {
            _PB_lastLogicalIndex = NewLogIdx;
            _PB_lastSortType = NewSortType;
            _PB_lastPhysicalIndex = PhyIdx;

            return NewLogIdx;
        }
    }
    __ASSERT(0);
    return PVR_NULL_FILE_INDEX;
}

#if 0
//****************************************************************************
/// Get PVR file Index by File name
/// @param sortType     \b IN: sorting type of index
/// @param *FileName     \b IN: File Name
/// @return E_PVR_RET : File index of sort type, 0xFFFF means not exist
//****************************************************************************
U16 MApp_PvrBrowser_GetIndexByFileName(SORT_TYPE sortType, U16 *FileName)
{
    PVR_BROWSER_ENTRY pvrEntry;
    U16 PhyIdx,NewLogIdx;
    U16 CompareIdx;
    U32 addr;

    PhyIdx = PVR_BROWSER_RESERVED_ENTRY_INDEX;
    for(NewLogIdx=0 ; NewLogIdx<_PB_TotalFileNum ; NewLogIdx++)
    {
        PhyIdx = _PB_GetPhysicalIndex(sortType, LIST_DIRECTION_DOWN, PhyIdx, 1);

#ifdef PVR_UTOPIA
        addr = (U32)PvrGetBrowBufAddr()+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
        MEM_CHECK(addr);
        MApi_BDMA_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#else
        addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
        MEM_CHECK(addr);
        MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#endif
        if(FS_strequal_U(FileName, pvrEntry.u16FileName))
            return NewLogIdx;
    }

    __ASSERT(0);
    return PVR_NULL_FILE_INDEX;
}
#endif

//****************************************************************************
/// Check whether File exist already
/// @param *FileName     \b IN: File Name
/// @return U16 : physical index of file, 0xFFFF means not exist
//****************************************************************************
U16 MApp_PvrBrowser_IsFileExist(U16 *FileName)
{
    PVR_BROWSER_ENTRY pvrEntry;
    U16 PhyIdx = 0xFFFF;
    U32 addr = 0;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_ARG_INVALID;
    }

    if(FileName != NULL)
    {
        for(PhyIdx = 1 ; PhyIdx<=_PB_TotalFileNum ; PhyIdx++)
        {
        #if 1//def PVR_UTOPIA
            //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
            addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(PhyIdx);
            MEM_CHECK(addr);
            MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(&pvrEntry)) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #else
            addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
            MEM_CHECK(addr);
            MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #endif

            if(FS_strequal_U((U16*)FileName, pvrEntry.u16FileName))
            {
                return PhyIdx;;
            }
        }
    }
    return PVR_NULL_FILE_INDEX;
}

//****************************************************************************
/// Set Attribute by file name
/// @param AttribType     \b IN: the attribute to be setup
/// @param *FileName      \b IN: the file name to be search
/// @param para           \b IN: the parameter to be setup
/// @return U16 : Physical index of file, 0xFFFF means not exist
//****************************************************************************
U16 MApp_PvrBrowser_SetAttributeByFileName(PVR_FILE_ATTRIBUTE_MEMBER AttribType, U16 *FileName, void *para)
{
    PVR_BROWSER_ENTRY pvrEntry;
    U16 PhyIdx = 0xFFFF;
    U32 addr = 0;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_ARG_INVALID;
    }

 //it should rewrite the search algorithm later to speed up the performance
    if(FileName != NULL)
    {
        for(PhyIdx = 1 ; PhyIdx<=_PB_TotalFileNum ; PhyIdx++)
        {
        #if 1//def PVR_UTOPIA
            //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
            addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(PhyIdx);
            MEM_CHECK(addr);
            MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(&pvrEntry)) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #else
            addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
            MEM_CHECK(addr);
            MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #endif

            if(FS_strequal_U((U16*)FileName, pvrEntry.u16FileName))
            {
                break;
            }
        }
        if(PhyIdx > _PB_TotalFileNum)
        {
            return PVR_NULL_FILE_INDEX;
        }
    }
    else
    {
        if(!(AttribType == E_PVR_ATTR_IS_PLAYING || AttribType == E_PVR_ATTR_IS_RECORDING))
            return PVR_NULL_FILE_INDEX;
    }


    switch(AttribType)
    {
        case E_PVR_ATTR_IS_PLAYING:
            if(FileName == NULL)
            {
                _PB_PlayingPhysicalIndex = PVR_NULL_FILE_INDEX;
            }
            else
            {
                _PB_PlayingPhysicalIndex = PhyIdx;
            }
            return PhyIdx;

        case E_PVR_ATTR_IS_RECORDING:
            if(FileName == NULL)
            {
                _PB_RecordingPhysicalIndex = PVR_NULL_FILE_INDEX;
            }
            else
            {
                _PB_RecordingPhysicalIndex = PhyIdx;
            }
            return PhyIdx;

        case E_PVR_ATTR_PROGRAM_DURATION:
        {
            U32 recTime = *(U32*)para;

            pvrEntry.u32Duration = recTime;
        #ifdef PVR_UTOPIA
            MApi_BDMA_Copy(_VA2PA(GET_DRAM_ADDR(&pvrEntry)), _VA2PA(addr), sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #else
            MDrv_MIU_Copy(GET_DRAM_ADDR(&pvrEntry), addr, sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #endif

            if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                   msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
            {
                _PB_SaveFAT32FileInfo(FileName, addr);
            }
        #if (ENABLE_BULK_FILE_SYSTEM)
            else if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
            {
                U16 u16BulkFileID = INVALID_BULK_FILE_ID;
                msAPI_PVRFS_SetBulkFileInfo(FileName, &u16BulkFileID, BKF_PARA_DURATION, &recTime, sizeof(U32));
            }
        #endif
        }
            return PhyIdx;

        case E_PVR_ATTR_PROGRAM_NAME:
        {
            UnicodeCpy((S8 *) pvrEntry.u16ProgramName, (S8 *) para);
        #ifdef PVR_UTOPIA
            MApi_BDMA_Copy(_VA2PA(GET_DRAM_ADDR(&pvrEntry)), _VA2PA(addr), sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #else
            MDrv_MIU_Copy(GET_DRAM_ADDR(&pvrEntry), addr, sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #endif

            if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                   msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
            {
                _PB_SaveFAT32FileInfo(FileName, addr);
            }
        #if (ENABLE_BULK_FILE_SYSTEM)
            else if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
            {
                U16 u16BulkFileID = INVALID_BULK_FILE_ID;
                msAPI_PVRFS_SetBulkFileInfo(FileName, &u16BulkFileID, BKF_PARA_PROGRAM_NAME, para, sizeof(pvrEntry.u16ProgramName));
            }
        #endif
        }
            return PhyIdx;


        case E_PVR_ATTR_PROGRAM_DESC:
        {
            UnicodeCpy((S8 *) pvrEntry.u16ProgDesc, (S8 *) para);
        #ifdef PVR_UTOPIA
            MApi_BDMA_Copy(_VA2PA(GET_DRAM_ADDR(&pvrEntry)), _VA2PA(addr), sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #else
            MDrv_MIU_Copy(GET_DRAM_ADDR(&pvrEntry), addr, sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #endif

            if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                   msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
            {
                _PB_SaveFAT32FileInfo(FileName, addr);
            }
        #if (ENABLE_BULK_FILE_SYSTEM)
            else if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
            {
                U16 u16BulkFileID = INVALID_BULK_FILE_ID;
                msAPI_PVRFS_SetBulkFileInfo(FileName, &u16BulkFileID, BKF_PARA_PROGRAM_DESC, para, sizeof(pvrEntry.u16ProgDesc));
            }
        #endif
        }
            return PhyIdx;

        case E_PVR_ATTR_CHANNEL_NAME:
        {
            UnicodeCpy((S8 *) pvrEntry.u16ChannelName, (S8 *) para);
        #ifdef PVR_UTOPIA
            MApi_BDMA_Copy(_VA2PA(GET_DRAM_ADDR(&pvrEntry)), _VA2PA(addr), sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #else
            MDrv_MIU_Copy(GET_DRAM_ADDR(&pvrEntry), addr, sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #endif

            if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_N51FAT32 ||
                   msAPI_PVRFS_GetFileSystemType() == PVR_FS_LINUX_FAT)
            {
                _PB_SaveFAT32FileInfo(FileName, addr);
            }
        #if (ENABLE_BULK_FILE_SYSTEM)
            else if(msAPI_PVRFS_GetFileSystemType() == PVR_FS_BULKFS)
            {
                U16 u16BulkFileID = INVALID_BULK_FILE_ID;
                msAPI_PVRFS_SetBulkFileInfo(FileName, &u16BulkFileID, BKF_PARA_CHANNEL_NAME, para, sizeof(pvrEntry.u16ChannelName));
            }
        #endif
        }
            return PhyIdx;

        default:
            return PVR_NULL_FILE_INDEX;
    }

    __ASSERT(0);
    PVR_BROWSER_DBG(printf("E_PVR_RET_BUK_FILES_NOT_FOUND\n"));
    return PVR_NULL_FILE_INDEX;
}

//****************************************************************************
/// Get logical index by by file name
/// @param SortType       \b IN: the the sort type
/// @param *FileName      \b IN: the file name to be search
/// @return U16 : logical index of SortType , 0xFFFF means not exist
//****************************************************************************
U16 MApp_PvrBrowser_GetLogicalIndexByFileName(SORT_TYPE SortType, U16 *FileName)
{
    PVR_BROWSER_ENTRY pvrEntry;
    U16 PhyIdx = 0xFFFF;
    U32 addr = 0;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return PVR_NULL_FILE_INDEX;
    }

 //it should rewrite the search algorithm later to speed up the performance
    if(FileName != NULL)
    {
        for(PhyIdx = 1 ; PhyIdx<=_PB_TotalFileNum ; PhyIdx++)
        {
        #if 1//def PVR_UTOPIA
            //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
            addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(PhyIdx);
            MEM_CHECK(addr);
            MApi_BDMA_Copy(_VA2PA(addr), _VA2PA(GET_DRAM_ADDR(&pvrEntry)) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #else
            addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)(PhyIdx*sizeof(PVR_BROWSER_ENTRY));
            MEM_CHECK(addr);
            MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
        #endif

            if(FS_strequal_U((U16*)FileName, pvrEntry.u16FileName))
            {
                break;
            }
        }
    }
    else
    {
        return PVR_NULL_FILE_INDEX;
    }

    return _PB_GetLogicalIndex(SortType, PhyIdx);
}

//****************************************************************************
/// Delete PVR file entry
/// @param sortType     \b IN: sorting type of index
/// @param LogicalIndex \b IN: Logical index of file
/// @return E_PVR_RET : success or fail
//****************************************************************************
E_PVR_RET MApp_PvrBrowser_DeleteFileEntry(SORT_TYPE sortType, U16 LogicalIndex)
{
    U16 PhyIdx;
    PVR_BROWSER_ENTRY pvrEntry;
    U32 addr;

    if (TRUE == MApp_PvrBrowser_IsEmptyBuffer())
    {
        return E_PVR_RET_FAIL;
    }

    PVR_BROWSER_DBG(printf("MApp_PvrBrowser_DeleteFileEntry\n"));

    PhyIdx = _PB_LogicalToPhysicalIndex(sortType, LogicalIndex);
#if( ENABLE_HALF_PVR == 0 )
    if(PhyIdx <=0 || PhyIdx >= MAX_PVR_BROWSER_ENTRY_NUM)
#endif
    {
        __ASSERT(0);
        return E_PVR_RET_FAIL;
    }

#if 1//def PVR_UTOPIA
    //addr = (U32)((PVR_BROWSER_BUFFER_MEMORY_TYPE & MIU1) ? (PvrGetBrowBufAddr() | MIU_INTERVAL) : PvrGetBrowBufAddr())+(U32)PhyIdx*sizeof(PVR_BROWSER_ENTRY);
    addr = _PB_Get_BrowBufAddr_VA_By_EntryIdx(PhyIdx);
    MEM_CHECK(addr);
    MApi_BDMA_Copy(_VA2PA(addr),_VA2PA(GET_DRAM_ADDR(&pvrEntry)) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#else
    addr = (U32)PVR_BROWSER_BUFFER_ADR+(U32)PhyIdx*sizeof(PVR_BROWSER_ENTRY);
    MEM_CHECK(addr);
    MDrv_MIU_Copy(addr,GET_DRAM_ADDR(&pvrEntry) ,sizeof(PVR_BROWSER_ENTRY), MIU_SDRAM2SDRAM);
#endif
//    printf("PhyIdx=%d\n",PhyIdx);
//    printf("sortType=%bx\n",sortType);
//    printf("LogicalIndex=%bx\n",LogicalIndex);
//    printf("_PB_lastLogicalIndex=%bx\n",_PB_lastLogicalIndex);
//    printf("_PB_lastSortType=%bx\n",_PB_lastSortType);
//    printf("_PB_lastPhysicalIndex=%d\n\n",_PB_lastPhysicalIndex);

    if(msAPI_PVRFS_FileDelete(pvrEntry.u16FileName))
    {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        msAPI_CIPVRFS_FileDelete(pvrEntry.u16FileName);
#endif
        if(_PB_lastPhysicalIndex == PhyIdx)
        {
            if (_PB_TotalFileNum == 1)
            {
                _PB_lastPhysicalIndex = PVR_NULL_FILE_INDEX;
                _PB_lastLogicalIndex = PVR_NULL_FILE_INDEX;
                _PB_lastSortType = SORT_NONE;
            }
            else
            {
                if(_PB_lastLogicalIndex == (_PB_TotalFileNum-1))
                {
                    _PB_lastPhysicalIndex = _PB_GetPhysicalIndex(_PB_lastSortType, LIST_DIRECTION_UP, PhyIdx, 1);
                    _PB_lastLogicalIndex--;
                }
                else
                {
                    _PB_lastPhysicalIndex = _PB_GetPhysicalIndex(_PB_lastSortType, LIST_DIRECTION_DOWN, PhyIdx, 1);
                }
            }
        }
        else
        {
            if(sortType == _PB_lastSortType)
            {
                if(LogicalIndex < _PB_lastLogicalIndex)
                {
                    _PB_lastLogicalIndex--;
                }
            }
            else
            {
                _PB_lastPhysicalIndex = PVR_NULL_FILE_INDEX;
                _PB_lastLogicalIndex = PVR_NULL_FILE_INDEX;
                _PB_lastSortType = SORT_NONE;
            }
        }
//    printf("_PB_lastLogicalIndex2=%bx\n",_PB_lastLogicalIndex);
//    printf("_PB_lastSortType2=%bx\n",_PB_lastSortType);
//    printf("_PB_lastPhysicalIndex2=%d\n\n\n",_PB_lastPhysicalIndex);

        return _PB_DeleteEntryFromDB(PhyIdx);
    }
    else
        return E_PVR_RET_FAIL;
}

//****************************************************************************
/// Check whether any file is playing
/// @param none
/// @return BOOLEN : TRUE: ther is one file playing now
//****************************************************************************
BOOLEAN MApp_PvrBrowser_IsAnyFilePlaying(void)
{
    if(_PB_PlayingPhysicalIndex == PVR_NULL_FILE_INDEX)
        return FALSE;
    else
        return TRUE;
}

//****************************************************************************
/// Check whether any file is recording
/// @param none
/// @return BOOLEN : TRUE: ther is one file playing now
//****************************************************************************
BOOLEAN MApp_PvrBrowser_IsAnyFileRecording(void)
{
    if(_PB_RecordingPhysicalIndex == PVR_NULL_FILE_INDEX)
        return FALSE;
    else
        return TRUE;
}
#else
U8 code pvr_browser;
#endif //ENABLE_PVR
#undef MAPP_PVR_BROWSER_C

