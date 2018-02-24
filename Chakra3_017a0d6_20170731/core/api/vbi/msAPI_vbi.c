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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_vbi.h
/// @brief API for Getting VBI Data from VBI Slicer
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_VBI_C

/******************************************************************************/
/*               Header Files                                                 */
/******************************************************************************/
#include <string.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "Analog_Reg.h"
#include "apiXC.h"
#include "msAPI_Global.h"
#include "SysInit.h"
#include "drvGlobal.h"
#include "drvVBI.h"
#include "sysinfo.h"
#include "drvvbi_reg.h"
#include "msAPI_vbi.h"
#include "msAPI_VD.h"
#include "msAPI_Timer.h"
#if (((ENABLE_SBTVD_ATV_SYSTEM  )&&(BRAZIL_CC))||(ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#endif

#define VBI_DEBUG                       0

// -- SH@ 20080911, this will check XDS' checksum field -->
#define  ATV_VCHIP_FULLY_CHECKING       0
#define  DTV_VCHIP_FULLY_CHECKING       0

#if (ATV_VCHIP_FULLY_CHECKING == 1) || (DTV_VCHIP_FULLY_CHECKING == 1)
#define  XDS_VCHIP_FULLY_CHECKING
#endif
// <-------------------------------------------------------

#ifndef WSS_statusreport
#define WSS_statusreport                DISABLE
#endif

#define CC_VBI_RECYCLE_TIME             4000
#define ACC_EXIST_COUNT                 60
#define ACC_EXIST_MONITORPERIOD         1000
#define VBI_VCHIP_NO_FRAME_COUNT        500 //Magic number change from (103) Ben.Luo 2011/09/28
#define CHECKVCHIP_TIMEOUT 7000
#define CHECKSTATIONID_TIMEOUT 0xffffffff
#define CHECKNETWORKNAME_TIMEOUT 0xffffffff
#define CHECKPROGRAMTITLE_TIMEOUT 0xffffffff

extern U32 u32CC_Check_Period;
extern U32 u32ACC_Last;
extern BOOLEAN fACCExistFlag;
//==============================================================================
/*                    Local                                                     */
//==============================================================================
static _FifoType astFifo[MCU_FIFO_LENGTH];
static _FifoType stVChipRating,stVChipRatingTemp;
static CAPTION_LAN_t Caption_Language, Caption_Language_Temp;
static U8 Program_TiTle[33],  Program_TiTle_Temp[33];
static U8 Network_Name[33],  Network_Name_Temp[33];
static U8 Station_ID[8], Station_ID_Temp[8];
static U8 g_u8Program_Title_Count;
static U8 g_u8Network_Name_Count;
static U8 g_u8Station_ID_Count;
static U16 u16XDSModeFlag = 0x0000;
static U16 u16XDSPacChecksum = 0;
static U32 _u32CheckVchipTimeout;
static U32 _u32CheckStationIDTimeout;
static U32 _u32CheckNetworkNameTimeout;
static U32 _u32CheckProgramTitleTimeout;

#define bXDSSTARTVCHIPBit             BIT0        //VCHIP
#define bXDSCURRENTVCHIPBit             BIT1        //VCHIP
#define bXDSSTARTPROGRAMTITLEBit              BIT2        //Program Title
#define bXDSCURRENTPROGRAMTITLEBit              BIT3        //Program Title
#define bXDSSTARTSTATIONIDBit                BIT4       //Station ID
#define bXDSCURRENTSTATIONIDBit                BIT5       //Station ID
#define bXDSSTARTCAPTIONSERVICESBit               BIT6          // Caption Service
#define bXDSCURRENTCAPTIONSERVICESBit            BIT7           //Caption Service
#define bXDSSTARTNETWORKNAMEBit                BIT8       //Network Name
#define bXDSCURRENTNETWORKNAMEBit                BIT9       //Network Name


#define XDSSTARTVCHIPFlag                     ((u16XDSModeFlag & bXDSSTARTVCHIPBit)  )
#define XDSCURRENTVCHIPFlag                               ((u16XDSModeFlag & bXDSCURRENTVCHIPBit) >>1  )
#define XDSSTARTPROGRAMTITLEFlag      ((u16XDSModeFlag & bXDSSTARTPROGRAMTITLEBit)  >> 2   )
#define XDSCURRENTPROGRAMTITLEFlag ((u16XDSModeFlag & bXDSCURRENTPROGRAMTITLEBit)  >> 3 )
#define XDSSTARTSTATIONIDFlag            ((u16XDSModeFlag & bXDSSTARTSTATIONIDBit)  >> 4  )
#define XDSCURRENTSTATIONIDFlag        ((u16XDSModeFlag & bXDSCURRENTSTATIONIDBit)     >> 5    )
#define XDSSTARTCAPTIONSERVICESFlag            ((u16XDSModeFlag & bXDSSTARTCAPTIONSERVICESBit)  >> 6   )
#define XDSCURRENTCAPTIONSERVICESFlag        ((u16XDSModeFlag & bXDSCURRENTCAPTIONSERVICESBit)     >> 7    )
#define XDSSTARTNETWORKNAMEFlag            ((u16XDSModeFlag & bXDSSTARTNETWORKNAMEBit)  >> 8   )
#define XDSCURRENTNETWORKNAMEFlag        ((u16XDSModeFlag & bXDSCURRENTNETWORKNAMEBit)     >> 9    )

#define Set_XDSSTARTVCHIPFlag()                      (u16XDSModeFlag |= bXDSSTARTVCHIPBit )
#define Clr_XDSSTARTVCHIPFlag()                        (u16XDSModeFlag &=~bXDSSTARTVCHIPBit )
#define Set_XDSCURRENTVCHIPFlag()                      (u16XDSModeFlag |= bXDSCURRENTVCHIPBit )
#define Clr_XDSCURRENTVCHIPFlag()                        (u16XDSModeFlag &=~bXDSCURRENTVCHIPBit )
#define Set_XDSSTARTPROGRAMTITLEFlag()        (u16XDSModeFlag |= bXDSSTARTPROGRAMTITLEBit  )
#define Clr_XDSSTARTPROGRAMTITLEFlag()        (u16XDSModeFlag &=~bXDSSTARTPROGRAMTITLEBit  )
#define Set_XDSCURRENTPROGRAMTITLEFlag()        (u16XDSModeFlag |= bXDSCURRENTPROGRAMTITLEBit  )
#define Clr_XDSCURRENTPROGRAMTITLEFlag()        (u16XDSModeFlag &=~bXDSCURRENTPROGRAMTITLEBit  )
#define Set_XDSSTARTSTATIONIDFlag()              (u16XDSModeFlag |= bXDSSTARTSTATIONIDBit   )
#define Clr_XDSSTARTSTATIONIDFlag()               (u16XDSModeFlag &=~bXDSSTARTSTATIONIDBit  )
#define Set_XDSCURRENTSTATIONIDFlag()              (u16XDSModeFlag |= bXDSCURRENTSTATIONIDBit   )
#define Clr_XDSCURRENTSTATIONIDFlag()               (u16XDSModeFlag &=~bXDSCURRENTSTATIONIDBit  )
#define Set_XDSSTARTCAPTIONSERVICESFlag()              (u16XDSModeFlag |= bXDSSTARTCAPTIONSERVICESBit   )
#define Clr_XDSSTARTCAPTIONSERVICESFlag()               (u16XDSModeFlag &=~bXDSSTARTCAPTIONSERVICESBit  )
#define Set_XDSCURRENTCAPTIONSERVICESFlag()              (u16XDSModeFlag |= bXDSCURRENTCAPTIONSERVICESBit   )
#define Clr_XDSCURRENTCAPTIONSERVICESFlag()               (u16XDSModeFlag &=~bXDSCURRENTCAPTIONSERVICESBit  )
#define Set_XDSSTARTNETWORKNAMEFlag()              (u16XDSModeFlag |= bXDSSTARTNETWORKNAMEBit   )
#define Clr_XDSSTARTNETWORKNAMEFlag()               (u16XDSModeFlag &=~bXDSSTARTNETWORKNAMEBit  )
#define Set_XDSCURRENTNETWORKNAMEFlag()              (u16XDSModeFlag |= bXDSCURRENTNETWORKNAMEBit   )
#define Clr_XDSCURRENTNETWORKNAMEFlag()               (u16XDSModeFlag &=~bXDSCURRENTNETWORKNAMEBit  )

#define Clr_XDSSYSTEMFLAG()         (u16XDSModeFlag = 0x0000   )

#define XDS_VCHIP_DEBUG(x)  //x

//#ifdef XDS_VCHIP_FULLY_CHECKING
//static _FifoType stVChipRatingTemp;
//#endif
static U8 g_u8VBISliceCount;
static U8 g_u8VBIReadCount;
static U8 g_u8VBIWriteCount;
static U8 g_u8VBIVChipIdleCount;
static U16 g_u16ChkNoVBI=0;

// SH@ This table is requested from C.J Hung. PAL-60 is same as NTSC-433 in CC part
#define VIDEO_TYPE_CNT          5
#define VIDEO_REGISTER_CNT      7
static U8 video_standard_vbi_settings[VIDEO_TYPE_CNT][VIDEO_REGISTER_CNT + 1] = {
   // type          41h[7:0]   42h[5:0]    44h[7:0]    4Bh[5:0]    4Dh[7:0]    50h[4:0]    51h[4:0]
    {SIG_NTSC,      0x52,      0x1c,       0x39,       0x24,       0x8e,       0x12,       0x12},  // NTSC
    {SIG_PAL_M,     0x52,      0x1c,       0x39,       0x26,       0x8e,       0x12,       0x12},  // PAL-M
    {SIG_PAL_NC,    0x52,      0x1c,       0x39,       0x16,       0x8e,       0x12,       0x12},  // PAL-NC
    {SIG_NTSC_443,  0x52,      0x23,       0x47,       0x32,       0xb0,       0x12,       0x12},  // NTSC-443, PAL-60
    {SIG_PAL,       0xb5,      0x23,       0x47,       0x22,       0xb0,       0x15,       0x15},  // PAL
};

#ifdef XDS_VCHIP_FULLY_CHECKING
static U8 g_u8VBITmpData1;
static U8 g_u8VBITmpData2;
#endif

/******************************************************************************/
/*                  CC Bytes Buffer (HW new architecture for Saturn2)         */
/******************************************************************************/
typedef struct
{
    U8 ccByte1;         // CCBytes[7:0]
    U8 ccByte2;         // CCBytes[15:8]
    U8 ccPacketCnt;     // ccPacketCnt[4:0]
    U8 ccFrameCnt;      // ccFrameCnt[4:0]
    U8 ccEvenOddFound;  // ccEvenOddFound[0]: even/odd, ccEvenOddFound[6]: even found, ccEvenOddFound[7]: odd found

    #ifdef PATCH_T3_VBI_WORKAROUND
    U8 ccReserved[11];  // T3, MIU enlarge to 128 bits...
    #else
    U8 ccReserved[3];
    #endif
} CC_Buf_Content;

#define CC_BUF_PACKER_CNT_MASK      0x1F
#define CC_BUF_FRAME_CNT_MASK       0x1F
#define CC_BUF_EVEN_ODD_MASK        0x01
#define CC_BUF_EVEN_FOUND_MASK      0x40
#define CC_BUF_ODD_FOUND_MASK       0x80

#define CC_BUF_LEN_MAX              MCU_FIFO_LENGTH

#define CC_BUF_FIXED_ADDR           0x4500

#define CC_EVEN_FOUND(ccEvenOddFound) (((ccEvenOddFound) & (CC_BUF_EVEN_FOUND_MASK | CC_BUF_EVEN_ODD_MASK)) == (CC_BUF_EVEN_FOUND_MASK | CC_BUF_EVEN_ODD_MASK))
#define CC_ODD_FOUND(ccEvenOddFound) (((ccEvenOddFound) & (CC_BUF_ODD_FOUND_MASK  | CC_BUF_EVEN_ODD_MASK)) == CC_BUF_ODD_FOUND_MASK)



/* CCByte Buffer */
static CC_Buf_Content volatile *ag_ccBytesBuf = ((CC_Buf_Content volatile *)((CCVBI_RINGBUFFER_START_MEMORY_TYPE & MIU1) ? (CCVBI_RINGBUFFER_START_ADR | MIU_INTERVAL) : (CCVBI_RINGBUFFER_START_ADR)));
static CC_Buf_Content volatile *g_ccBytesBuf;

static U8 g_u8CCBytesBufRdPtr;

/* CCByte Odd Parity Check */
static U8 code parityCheckTbl[16] = { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 }; // 0: even, 1: odd

static U32 g_u32LastVbiTime; //andy@SEC:20070326

#define PARITY_CHECK_ERROR(data) ((parityCheckTbl[(data)&0x0F] + parityCheckTbl[(data)>>4]) != 1) // Odd Parity Check

//extern void MDrv_Timer_Delayus(U32 u32DelayTime);

/********************************************************************************/
/*                    Functions                                                 */
/********************************************************************************/

/******************************************************************************/
// API for VBI Slicer Initialization::
// Initializing VBI Slicer HW
/******************************************************************************/
void msAPI_VBI_Init(void)
{
    U32 u32Addr;

    u32Addr = (((U32)(&ag_ccBytesBuf[0])));
#if (VBI_DEBUG)
    printf("\n vbi init, addr:0x%x, ptr:0x%x, size:%d\n", ((U32)(&ag_ccBytesBuf[0])), g_ccBytesBuf, sizeof(CC_Buf_Content));
#endif
    //u32Addr is PA in here
    MDrv_VBI_CC_InitSlicer((U32)RIU_MAP, (u32Addr), CC_BUF_LEN_MAX);

    g_ccBytesBuf = (CC_Buf_Content *)(_PA2VA(u32Addr));


    #if (WSS_statusreport)
    MDrv_VBI_WSS_SetVpsByteNum(0x01);
    #endif

    // set the datarate in different video system...It should put in 'MApp_VD_TimingHandler()' next time...
    msAPI_VBI_CC_DataRateSet(SIG_NTSC); // Fix NTSC in temporal

    /* init cc bytes buffer and read pointer */
    memset((U8 *)g_ccBytesBuf, 0x00, sizeof (CC_Buf_Content)*(CC_BUF_LEN_MAX+1));
    memset((U8 *)astFifo, 0x00, sizeof(astFifo[0])*MCU_FIFO_LENGTH);

    g_u8CCBytesBufRdPtr = 1;

    #ifdef XDS_VCHIP_FULLY_CHECKING
    g_u8VBITmpData1 = 0;
    g_u8VBITmpData2 = 0;
    #endif

    stVChipRating.Data1 = 0x00;
    stVChipRating.Data2 = 0x00;
    stVChipRatingTemp.Data1 = 0;
    stVChipRatingTemp.Data2 = 0;

    g_u8VBISliceCount = 0;
    g_u8VBIReadCount = 0;
    g_u8VBIWriteCount = 0;
    g_u8Program_Title_Count = 0;
    g_u8Station_ID_Count = 0;
    _u32CheckVchipTimeout = msAPI_Timer_GetTime0();
    _u32CheckStationIDTimeout = msAPI_Timer_GetTime0();
    _u32CheckNetworkNameTimeout = msAPI_Timer_GetTime0();
    _u32CheckProgramTitleTimeout = msAPI_Timer_GetTime0();
    Clr_XDSSYSTEMFLAG();
    memset(Program_TiTle, '\0', sizeof(Program_TiTle));
    memset(Program_TiTle_Temp, '\0', sizeof(Program_TiTle_Temp));
    memset(Station_ID, '\0', sizeof(Station_ID));
    memset(Station_ID_Temp, '\0', sizeof(Station_ID_Temp));
    memset(Network_Name, '\0', sizeof(Network_Name));
    memset(Network_Name_Temp, '\0', sizeof(Network_Name_Temp));
    memset(&Caption_Language, NULL, sizeof(Caption_Language));
    memset(&Caption_Language_Temp, NULL, sizeof(Caption_Language_Temp));

}

#ifndef DISABLE_COMPONENT_VBI
/******************************************************************************/
/// API to turn on VBI from YPbPr Initialization::
/// Initializing VBI Slicer HW
/******************************************************************************/
void msAPI_VBI_YPbPr_Init(U8 cvbs_no)
{
    if(cvbs_no > 7) cvbs_no = 1;

    MDrv_VBI_CC_InitYPbYr(cvbs_no);
}
#endif

void msAPI_VBI_CC608ExistCheck(U8 u8D6CC_Data1, U8 u8D6CC_Data2)
{
    if(CHECKCCEXIST(fACCExistFlag))
        return;

    if ((u8D6CC_Data1 & 0x76) == 0x14)
    {
        u8D6CC_Data2 &= 0x7F;
        if ( (u8D6CC_Data2   == 0x20) ||       // RCL
             (u8D6CC_Data2   == 0x25) ||      // RU2
             (u8D6CC_Data2   == 0x26) ||      // RU3
             (u8D6CC_Data2   == 0x27) ||      // RU4
             (u8D6CC_Data2   == 0x29) ||      // RDC
             (u8D6CC_Data2   == 0x2A) ||      // RTX
             (u8D6CC_Data2   == 0x2B))         // TxR

        {
            SET_608CCISEXIST(TRUE);
            return;
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
/// API to check Analog CC608 availability::
/// @return
///   - # TRUE CC608 is avaiable
///   - # FALSE CC608 is not available
///////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_VBI_AnalogCC608_Available(void)
{
    if(u32CC_Check_Period == 0)
    {
        if(CHECKCCEXIST(fACCExistFlag))
            return TRUE;
        else
            return FALSE;
    }
    else
    {
        if ((u32ACC_Last == 0)||(!CHECKCCEXIST(fACCExistFlag)))
            return FALSE;

        if (msAPI_Timer_DiffTimeFromNow(u32ACC_Last) <= u32CC_Check_Period)
        {
            return TRUE;
        }
        else
            return FALSE;
    }
}


/********************************************************************************/
/// API for Checking VChip Status::
/// Checking VChip status
/// @Param pu8EIA608Data1 \b IN  the First VChip Data Byte
/// @Param pu8EIA608Data2 \b IN  the Second VChip Data Byte
/// @return VChip Status
/********************************************************************************/
EnuVChipDataStatus msAPI_VBI_GetEIA608Data(U8 *pu8EIA608Data1, U8 *pu8EIA608Data2)
{
    EnuVChipDataStatus status;

    if(stVChipRating.Data1&BIT6 && stVChipRating.Data2&BIT6)
    {
        if( (*pu8EIA608Data1 != stVChipRating.Data1) || (*pu8EIA608Data2 != stVChipRating.Data2) )
        {
            *pu8EIA608Data1 = stVChipRating.Data1;
            *pu8EIA608Data2 = stVChipRating.Data2;
            status = VCHIP_DATA_CHANGE;
        }
        else
        {
            status = VCHIP_DATA_NO_CHANGE;
        }
        #if (DTV_608_VCHIP_DEBUG == 1)
        printf("\n #######  vc -> %x, %x\n", stVChipRating.Data1, stVChipRating.Data2);
        #endif
    }
    else
    {
        *pu8EIA608Data1 = 0;
        *pu8EIA608Data2 = 0;
        status = VCHIP_DATA_NONE;
    }

    return status;
}

/********************************************************************************/
/// API for get program title::
/// get program title
/// @Param none
/// @return pointer of program title
/********************************************************************************/
U8* msAPI_VBI_GetProgramTitle(void)
{
    if(Program_TiTle[0] == '\0')
    {
      return NULL;
    }
    else
    {
      return &(Program_TiTle[0]);
    }
}

/********************************************************************************/
/// API for get station ID::
/// get station ID
/// @Param none
/// @return pointer of station ID
/********************************************************************************/
U8* msAPI_VBI_GetStationID(void)
{
    if(Station_ID[0] == '\0')
    {
      return NULL;
    }
    else
    {
      return &(Station_ID[0]);
    }
}

/********************************************************************************/
/// API for get Network Name::
/// get Network Name
/// @Param none
/// @return pointer of Network Name
/********************************************************************************/
U8* msAPI_VBI_GetNetworkName(void)
{
    if(Network_Name[0] == '\0')
    {
      return NULL;
    }
    else
    {
      return &(Network_Name[0]);
    }
}

void msAPI_VBI_GetCaptionLanguage(CAPTION_LAN_t *pcaptionlan)
{
    pcaptionlan = &Caption_Language;
}

void msAPI_VBI_SetCaptionLanguage(U8 u8DATA)
{
    U8 LanBit, CaptionSerBit;
    EnCaptionLanguage eServiceLan = CL_UNKNOWN;
    LanBit = CaptionSerBit = 0;

    LanBit =(u8DATA & 0x38)>>3;
    CaptionSerBit = (u8DATA & 0x07);

    switch(LanBit)
    {
        case 0:
            eServiceLan = CL_UNKNOWN;
            break;
        case 1:
            eServiceLan = CL_ENGLISH;
            break;
        case 2:
            eServiceLan = CL_SPANISH;
            break;
        case 3:
            eServiceLan = CL_FRENCH;
            break;
        case 4:
            eServiceLan = CL_GERMAN;
            break;
        case 5:
            eServiceLan = CL_ITALIAN;
            break;
        case 6:
        case 7:
        default:
            eServiceLan = CL_UNKNOWN;
            break;
    }

    switch(CaptionSerBit)
    {
        case 0:
            Caption_Language_Temp.CC1_LANGUAGE = eServiceLan;
            break;
        case 1:
            Caption_Language_Temp.TEXT1_LANGUAGE = eServiceLan;
            break;
        case 2:
            Caption_Language_Temp.CC2_LANGUAGE = eServiceLan;
            break;
        case 3:
            Caption_Language_Temp.TEXT2_LANGUAGE = eServiceLan;
            break;
         case 4:
            Caption_Language_Temp.CC3_LANGUAGE = eServiceLan;
            break;
         case 5:
            Caption_Language_Temp.TEXT3_LANGUAGE = eServiceLan;
            break;
          case 6:
            Caption_Language_Temp.CC4_LANGUAGE = eServiceLan;
            break;
          case 7:
            Caption_Language_Temp.TEXT4_LANGUAGE = eServiceLan;
            break;
    }
}

/********************************************************************************/
/// API for Analyzing VChip Data Command::\n
/// Analyze VChip Data Bytes and set VChip flow control status
/// @Param pstFifo \b IN  the VBI Data structure
/********************************************************************************/
static void msAPI_VBI_ParseXDS(_FifoType *pstFifo)
{
    #ifdef XDS_VCHIP_FULLY_CHECKING
    U8 RatingCheckSum ;
    #endif

    if(pstFifo->Data1 == ALL_END)
    {
       if((XDSSTARTVCHIPFlag)||(XDSCURRENTVCHIPFlag))
       {
           // #ifdef XDS_VCHIP_FULLY_CHECKING
           #if 0
            #if (ATV_VCHIP_FULLY_CHECKING == 1) || (DTV_VCHIP_FULLY_CHECKING == 1)
            RatingCheckSum=(U8)((stVChipRatingTemp.Data1 + stVChipRatingTemp.Data2 + CURRENT_START + PROGRAM_RATING + ALL_END + pstFifo->Data2) & 0x7F) ;
             //printf("\n...chk:0x%bx", RatingCheckSum);
            if(RatingCheckSum == 0)
            {
                if((g_u8VBITmpData1 != stVChipRatingTemp.Data1) || (g_u8VBITmpData2 != stVChipRatingTemp.Data2))
                {
                    g_u8VBITmpData1 = stVChipRatingTemp.Data1;
                    g_u8VBITmpData2 = stVChipRatingTemp.Data2;
                }
                else
                {
                    stVChipRating.Data1 = stVChipRatingTemp.Data1;
                    stVChipRating.Data2 = stVChipRatingTemp.Data2;
                }
            }
            #elif (ATV_VCHIP_FULLY_CHECKING == 1)
            if(IsAnalogSourceInUse())
            {
                RatingCheckSum=(U8)((stVChipRatingTemp.Data1 + stVChipRatingTemp.Data2 + CURRENT_START + PROGRAM_RATING + ALL_END + pstFifo->Data2) & 0x7F) ;

                if(RatingCheckSum == 0)
                {
                    if((g_u8VBITmpData1 != stVChipRatingTemp.Data1) || (g_u8VBITmpData2 != stVChipRatingTemp.Data2))
                    {
                        g_u8VBITmpData1 = stVChipRatingTemp.Data1;
                        g_u8VBITmpData2 = stVChipRatingTemp.Data2;
                    }
                    else
                    {
                        stVChipRating.Data1 = stVChipRatingTemp.Data1;
                        stVChipRating.Data2 = stVChipRatingTemp.Data2;
                    }
                }
            }
            #elif (DTV_VCHIP_FULLY_CHECKING == 1)
            if(IsDigitalSourceInUse())
            {
                RatingCheckSum=(U8)((stVChipRatingTemp.Data1 + stVChipRatingTemp.Data2 + CURRENT_START + PROGRAM_RATING + ALL_END + pstFifo->Data2) & 0x7F) ;

                if(RatingCheckSum == 0)
                {
                    if((g_u8VBITmpData1 != stVChipRatingTemp.Data1) || (g_u8VBITmpData2 != stVChipRatingTemp.Data2))
                    {
                        g_u8VBITmpData1 = stVChipRatingTemp.Data1;
                        g_u8VBITmpData2 = stVChipRatingTemp.Data2;
                    }
                    else
                    {
                        stVChipRating.Data1 = stVChipRatingTemp.Data1;
                        stVChipRating.Data2 = stVChipRatingTemp.Data2;
                    }
                }
            }
            #endif
            #else
            u16XDSPacChecksum +=ALL_END;
            u16XDSPacChecksum += pstFifo->Data2;
             /* yym @ 2013.1.20 see EIA-608B page 32
             "The Checksum Data Byte represents the 7-bit binary number necessary for the sum of the Start and Type
             characters, all of the following Informational characters plus the End and Checksum characters to equal zero" */
             if((u16XDSPacChecksum & 0x7F) == 0)
             //if(u16XDSPacChecksum > 0xFF)
             {
                stVChipRating.Data1 = stVChipRatingTemp.Data1;
                stVChipRating.Data2 = stVChipRatingTemp.Data2;
                XDS_VCHIP_DEBUG(printf("\n Vchip rating sending: Data1 = %x , Data2 = %x . \n",  stVChipRating.Data1,  stVChipRating.Data2));
             }
             else
             {
                XDS_VCHIP_DEBUG(printf("\n Vchip rating checksum error !!!!!!!!"));
             }
            #endif
             _u32CheckVchipTimeout = msAPI_Timer_GetTime0();
             g_u8VBIVChipIdleCount = 0;
             u16XDSPacChecksum =0;
        }
        else if((XDSSTARTPROGRAMTITLEFlag)||(XDSCURRENTPROGRAMTITLEFlag))
        {
            memset(Program_TiTle, '\0', sizeof(Program_TiTle));
            memcpy(Program_TiTle, Program_TiTle_Temp, sizeof(Program_TiTle));
            memset(Program_TiTle_Temp, '\0', sizeof(Program_TiTle_Temp));
            g_u8Program_Title_Count = 0;
            _u32CheckProgramTitleTimeout = msAPI_Timer_GetTime0();
        }
        else if((XDSSTARTNETWORKNAMEFlag)||(XDSCURRENTNETWORKNAMEFlag))
        {
            memset(Network_Name, '\0', sizeof(Network_Name));
            memcpy(Network_Name, Network_Name_Temp, sizeof(Network_Name));
            memset(Network_Name_Temp, '\0', sizeof(Network_Name_Temp));
            g_u8Network_Name_Count = 0;
            _u32CheckNetworkNameTimeout = msAPI_Timer_GetTime0();
        }
        else if((XDSSTARTSTATIONIDFlag)||(XDSCURRENTSTATIONIDFlag))
        {
            memset(Station_ID, '\0', sizeof(Station_ID));
            memcpy(Station_ID, Station_ID_Temp, sizeof(Station_ID));
            memset(Station_ID_Temp, '\0', sizeof(Station_ID_Temp));
            g_u8Station_ID_Count = 0;
            _u32CheckStationIDTimeout = msAPI_Timer_GetTime0();
        }
        else if((XDSSTARTCAPTIONSERVICESFlag)||(XDSCURRENTCAPTIONSERVICESFlag))
        {
            memcpy(&Caption_Language, &Caption_Language_Temp,sizeof(Caption_Language));
        }
        Clr_XDSSYSTEMFLAG();
    }
    else
    {
       if((XDSSTARTVCHIPFlag)||(XDSCURRENTVCHIPFlag))
       {
          u16XDSPacChecksum = 0;
          Clr_XDSSTARTVCHIPFlag();
          Clr_XDSCURRENTVCHIPFlag();
       }
       else if((XDSSTARTPROGRAMTITLEFlag)||(XDSCURRENTPROGRAMTITLEFlag))
       {
            Clr_XDSSTARTPROGRAMTITLEFlag();
            Clr_XDSCURRENTPROGRAMTITLEFlag();
       }
       else if((XDSSTARTNETWORKNAMEFlag)||(XDSCURRENTNETWORKNAMEFlag))
        {
            Clr_XDSSTARTNETWORKNAMEFlag();
            Clr_XDSCURRENTNETWORKNAMEFlag();
        }
       else if((XDSSTARTSTATIONIDFlag)||(XDSCURRENTSTATIONIDFlag))
        {
            Clr_XDSSTARTSTATIONIDFlag();
            Clr_XDSCURRENTSTATIONIDFlag();
        }
       else if((XDSSTARTCAPTIONSERVICESFlag)||(XDSCURRENTCAPTIONSERVICESFlag))
        {
            Clr_XDSSTARTCAPTIONSERVICESFlag();
            Clr_XDSCURRENTCAPTIONSERVICESFlag();
        }
        Clr_XDSSYSTEMFLAG();

       if(pstFifo->Data1 == CURRENT_START)
       {
          if(pstFifo->Data2 == PROGRAM_RATING)
          {
             XDS_VCHIP_DEBUG(printf("\n  @@ Vchip rating Start \n"));
             Set_XDSSTARTVCHIPFlag();
             stVChipRatingTemp.Data1 = 0;
             stVChipRatingTemp.Data2 = 0;
             u16XDSPacChecksum = (CURRENT_START+PROGRAM_RATING);
          }
          else if(pstFifo->Data2 == PROGRAM_NAME)
          {
            g_u8Program_Title_Count = 0;
            memset(Program_TiTle_Temp, '\0', sizeof(Program_TiTle_Temp));
            Set_XDSSTARTPROGRAMTITLEFlag();
          }
          else if(pstFifo->Data2 == CAPTION_SERVICE)
          {
            Set_XDSSTARTCAPTIONSERVICESFlag();
          }
       }
       else if(pstFifo->Data1 == CURRENT_CONTI)
       {
          if(pstFifo->Data2 == PROGRAM_RATING)
          {
            XDS_VCHIP_DEBUG(printf("\n  @@ Vchip rating Continue \n"));
            Set_XDSCURRENTVCHIPFlag();
            /* yym @ 2013.1.20  see EIA-608B page 32: "No Continue/Type control character pairs are ever part of the checksum calculation"  */
            //u16XDSPacChecksum = (CURRENT_CONTI+PROGRAM_RATING);
          }
          else if(pstFifo->Data2 == PROGRAM_NAME)
          {
            Set_XDSCURRENTPROGRAMTITLEFlag();
          }
          else if(pstFifo->Data2 == CAPTION_SERVICE)
          {
            Set_XDSCURRENTCAPTIONSERVICESFlag();
          }
       }
       else if(pstFifo->Data1 == CHANNEL_START)
       {
          if(pstFifo->Data2 == Network_Names)
          {
             g_u8Network_Name_Count = 0;
             memset(Network_Name_Temp, '\0', sizeof(Network_Name_Temp));
             Set_XDSSTARTNETWORKNAMEFlag();
          }
          else if(pstFifo->Data2 == Call_Letters)
          {
             g_u8Station_ID_Count = 0;
             memset(Station_ID_Temp, '\0', sizeof(Station_ID_Temp));
             Set_XDSSTARTSTATIONIDFlag();
          }
        }
       else if(pstFifo->Data1 == CHANNEL_CONTI)
       {
           if(pstFifo->Data2 == Network_Names)
           {
             Set_XDSCURRENTNETWORKNAMEFlag();
           }
           if(pstFifo->Data2 == Call_Letters)
           {
             Set_XDSCURRENTSTATIONIDFlag();
           }
        }
    }
}

/********************************************************************************/
/// API for Analyzing EIA608 Raw Data for Closed Caption and VChip Data::
/// Analyze EIA608 Raw Data, checking which data belong to VChip or CC.
/// @Param pstFifo \b IN  the VBI Data structure
/********************************************************************************/
void msAPI_VBI_ProcessXDS(_FifoType pstFifo)
{
    pstFifo.Data1 &= 0x7F;
    pstFifo.Data2 &= 0x7F;

    #if (DTV_608_VCHIP_DEBUG == 1)
    printf("\n vc data(%bx, %bx)", pstFifo.Data1, pstFifo.Data2);
    #endif

    if((pstFifo.Data1 >= 0x01) && (pstFifo.Data1 <= 0x0F))//XDS control code
    {
        msAPI_VBI_ParseXDS(&pstFifo);
    }
    else if((pstFifo.Data1 >= 0x10) && (pstFifo.Data1 <= 0x1F))//CC command
    {
        Clr_XDSSYSTEMFLAG();
    }
    else
    {
        if((XDSSTARTVCHIPFlag)||(XDSCURRENTVCHIPFlag))
        {
            if((stVChipRatingTemp.Data1 == 0)&&(stVChipRatingTemp.Data2 == 0))
            {
                if((pstFifo.Data1&BIT6) && (pstFifo.Data2&BIT6)) //VChip Rating
                {
                    //    #ifdef XDS_VCHIP_FULLY_CHECKING
                    #if 0
                    #if (ATV_VCHIP_FULLY_CHECKING == 1) || (DTV_VCHIP_FULLY_CHECKING == 1)
                    stVChipRatingTemp.Data1 = pstFifo.Data1;
                    stVChipRatingTemp.Data2 = pstFifo.Data2;
                    #elif (ATV_VCHIP_FULLY_CHECKING == 1)
                    if(IsAnalogSourceInUse())
                    {
                        stVChipRatingTemp.Data1 = pstFifo.Data1;
                        stVChipRatingTemp.Data2 = pstFifo.Data2;
                    }
                    else
                    {
                        stVChipRating.Data1 = pstFifo.Data1;
                        stVChipRating.Data2 = pstFifo.Data2;
                    }
                    #elif (DTV_VCHIP_FULLY_CHECKING == 1)
                    if(IsDigitalSourceInUse())
                    {
                        stVChipRatingTemp.Data1 = pstFifo.Data1;
                        stVChipRatingTemp.Data2 = pstFifo.Data2;
                    }
                    else
                    {
                        stVChipRating.Data1 = pstFifo.Data1;
                        stVChipRating.Data2 = pstFifo.Data2;
                    }
                    #endif

                    #else
                      XDS_VCHIP_DEBUG(printf("\n Vchip rating DATA 1= %x, DATA 2 = %x. \n" ,pstFifo.Data1, pstFifo.Data2));
                      stVChipRatingTemp.Data1 = pstFifo.Data1;
                      stVChipRatingTemp.Data2 = pstFifo.Data2;

                      u16XDSPacChecksum+= stVChipRatingTemp.Data1;
                      u16XDSPacChecksum+= stVChipRatingTemp.Data2;
                    #endif
                }
                else
                {
                    u16XDSPacChecksum= 0;
                    Clr_XDSSTARTVCHIPFlag();
                    Clr_XDSCURRENTVCHIPFlag();
                }
             }
             else
             {
                  u16XDSPacChecksum= 0;
                  stVChipRatingTemp.Data1 = 0;
                  stVChipRatingTemp.Data2 = 0;
                  Clr_XDSSTARTVCHIPFlag();
                  Clr_XDSCURRENTVCHIPFlag();
             }
        }
        else if((XDSSTARTPROGRAMTITLEFlag)||(XDSCURRENTPROGRAMTITLEFlag))
        {
            if(g_u8Program_Title_Count < 31)
            {
                Program_TiTle_Temp[g_u8Program_Title_Count] = pstFifo.Data1;
                Program_TiTle_Temp[g_u8Program_Title_Count+1] = pstFifo.Data2;
                g_u8Program_Title_Count +=2;
            }
        }
        else if((XDSSTARTNETWORKNAMEFlag)||(XDSCURRENTNETWORKNAMEFlag))
        {
            if(g_u8Network_Name_Count < 31)
            {
                Network_Name_Temp[g_u8Network_Name_Count] = pstFifo.Data1;
                Network_Name_Temp[g_u8Network_Name_Count+1] = pstFifo.Data2;
                g_u8Network_Name_Count +=2;
            }
        }
        else if((XDSSTARTSTATIONIDFlag)||(XDSCURRENTSTATIONIDFlag))
        {
            if(g_u8Station_ID_Count < 5)
            {
                Station_ID_Temp[g_u8Station_ID_Count] = pstFifo.Data1;
                Station_ID_Temp[g_u8Station_ID_Count+1] = pstFifo.Data2;
                g_u8Station_ID_Count +=2;
            }
        }
        else if((XDSSTARTCAPTIONSERVICESFlag)||(XDSCURRENTCAPTIONSERVICESFlag))
        {
             if((pstFifo.Data1&BIT6) && (pstFifo.Data2&BIT6))
             {
                 msAPI_VBI_SetCaptionLanguage(pstFifo.Data1);
                 msAPI_VBI_SetCaptionLanguage(pstFifo.Data2);
             }
             else
             {
                Clr_XDSSTARTCAPTIONSERVICESFlag();
                Clr_XDSCURRENTCAPTIONSERVICESFlag();
             }
        }

    }
}
void msAPI_VBI_ResetVchipRating(void)
{
   if(msAPI_Timer_DiffTimeFromNow(_u32CheckVchipTimeout) > CHECKVCHIP_TIMEOUT)
   {
        #ifdef XDS_VCHIP_FULLY_CHECKING
        g_u8VBITmpData1 = 0;
        g_u8VBITmpData2 = 0;
        #endif

        XDS_VCHIP_DEBUG(printf("\n Vchip Rating Reset !!!!!!!!!!!!!!!!!!!!!! \n"));

        stVChipRating.Data1 = 0x00;
        stVChipRating.Data2 = 0x00;
        stVChipRatingTemp.Data1 = 0x00;
        stVChipRatingTemp.Data1 = 0x00;
        _u32CheckVchipTimeout = msAPI_Timer_GetTime0();
   }
}

void msAPI_VBI_ResetXDSInfo(void)
{
   if(msAPI_Timer_DiffTimeFromNow(_u32CheckStationIDTimeout) > CHECKSTATIONID_TIMEOUT)
   {
        memset(Station_ID, '\0', sizeof(Station_ID));
        _u32CheckStationIDTimeout = msAPI_Timer_GetTime0();
   }

   if(msAPI_Timer_DiffTimeFromNow(_u32CheckNetworkNameTimeout) > CHECKNETWORKNAME_TIMEOUT)
   {
        memset(Network_Name, '\0', sizeof(Network_Name));
        _u32CheckNetworkNameTimeout = msAPI_Timer_GetTime0();
   }

    if(msAPI_Timer_DiffTimeFromNow(_u32CheckProgramTitleTimeout) > CHECKPROGRAMTITLE_TIMEOUT)
   {
        memset(Program_TiTle, '\0', sizeof(Program_TiTle));
        _u32CheckProgramTitleTimeout = msAPI_Timer_GetTime0();
   }
}
void msAPI_VBI_CheckCCInfo(void)
{
    _FifoType OnePacket;

    // field 1
    OnePacket.Data1 = g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1 & 0x7F;
    OnePacket.Data2 = g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2 & 0x7F;

    // SWS 060109 => Text&Miceslleous CMD ´ëÀÀ
    if(((OnePacket.Data1&0x76)==0x14 ) && ((OnePacket.Data2>=0x20) && (OnePacket.Data2<=0x2F)) )
    {
        // SWS 070220 => FIELD1 Parity checking
        //if(XBYTE[BK_VBI_55] & 0x04 || XBYTE[BK_VBI_55] & 0x08) // even field check
        if (PARITY_CHECK_ERROR(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1) || PARITY_CHECK_ERROR(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2))
        {
            return;
        }
    }
}
// =================================================================================

/********************************************************************************/
/// API for Getting VBI Data from VBI Slicer::
/// Getting VBI Data from VBI Ring Buffer of VBI Slicer periodically
/// @Param enEIA608SrvType \b IN  the VBI Data Type
/********************************************************************************/
void msAPI_VBI_MonitorVBIData(EN_EIA608_SRV_TYPE enEIA608SrvType)
{
    U8 /*u8Bank,*/ u8Count, u8CcPacketCnt; // <- remove the bank change code
    _FifoType stFifotemp;

    // u8Bank = XBYTE[BK_SELECT_00]; <- remove the bank change code
    // XBYTE[BK_SELECT_00] = REG_BANK_VBI; <- remove the bank change code
#if (VBI_DEBUG)
    enEIA608SrvType = CC_1;// test CC_1 odd field and CC_3 even field.

    while(1)
    {
#endif
        #if (WSS_statusreport)
        if(MDrv_VBI_IsWSS_Ready()&BIT7)
        {
            printf("WSS\r\n");
        }
        else
        {
            printf("No WSS\r\n");
        }
        #endif
        u8Count = 0;

        while (u8Count < MCU_FIFO_LENGTH)
        {
            u8CcPacketCnt = MDrv_VBI_CC_GetInfo(VBI_CC_PACKET_COUNT);

            if ((g_u8CCBytesBufRdPtr == u8CcPacketCnt) ||
                ((g_u8CCBytesBufRdPtr+CC_BUF_LEN_MAX) == u8CcPacketCnt))
            {
                // -- SH@ when no VBI, reset VBI data to prevent blocking -------->
                if(MDrv_VBI_CC_GetInfo(VBI_CC_BYTE_FOUND_INDICATION) == 0)
                {
                    static U8 cnt = 0;
                    g_u16ChkNoVBI++;
                    if (g_u16ChkNoVBI>cnt)
                    {
                        cnt = g_u16ChkNoVBI;
                        //printf("%u\n", cnt);
                    }
                }
                else if(g_u16ChkNoVBI > 0)
                {
                    g_u16ChkNoVBI--;
                }

                if (g_u16ChkNoVBI > VBI_VCHIP_NO_FRAME_COUNT)
                {
                    g_u16ChkNoVBI = 0;

                    #ifdef XDS_VCHIP_FULLY_CHECKING
                    g_u8VBITmpData1 = 0;
                    g_u8VBITmpData2 = 0;
                    #endif

                    stVChipRating.Data1 = 0x00;
                    stVChipRating.Data2 = 0x00;

                    stVChipRatingTemp.Data1 = 0;
                    stVChipRatingTemp.Data2 = 0;
                }
                // <------------------------------------------------------

                break;
            }
            else
            {
                u8Count++;

                MDrv_VBI_CC_SetFrameCnt(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccFrameCnt);
                MDrv_VBI_CC_EnableSlicer(TRUE);

                // For avoiding data inconsistency when CC slicer sends the latest data into memory and software accesses the data at the same time
                // It must be over 64 us
                if(u8CcPacketCnt >= g_u8CCBytesBufRdPtr)
                {
                    if(u8CcPacketCnt - g_u8CCBytesBufRdPtr == 1)
                    {
                        MsOS_DelayTaskUs(64);
                    }
                    else if(u8CcPacketCnt == CC_BUF_LEN_MAX && g_u8CCBytesBufRdPtr == 0)
                    {
                        MsOS_DelayTaskUs(64);
                    }
                }

                msAPI_VBI_CheckCCInfo();

                #ifdef PATCH_T3_VBI_WORKAROUND
                MsOS_ReadMemory();  // T3 MIPS has EV-bridge, so we need to flush. Otherwise, it will lose some characters...
                #endif

                /* field 2 */
                if (CC_EVEN_FOUND(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccEvenOddFound))
                {

                    stFifotemp.Data1 = g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1;
                    stFifotemp.Data2 = g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2;

                    g_u8CCBytesBufRdPtr++;
                    if (g_u8CCBytesBufRdPtr >= CC_BUF_LEN_MAX) // i.e. g_u8CCBytesBufRdPtr %= CC_BUF_LEN_MAX
                    {
                        g_u8CCBytesBufRdPtr = 0;
                    }

                    /* parity check */
                    if (PARITY_CHECK_ERROR(stFifotemp.Data1) ||
                        PARITY_CHECK_ERROR(stFifotemp.Data2))
                    {
                        Clr_XDSSYSTEMFLAG();
                    }
                    else
                    {
                        msAPI_VBI_ProcessXDS(stFifotemp);
                    }

                    if ( enEIA608SrvType==CC_3 ||
                         enEIA608SrvType==CC_4 ||
                         enEIA608SrvType==TT_3 ||
                         enEIA608SrvType==TT_4 )
                    {
                        if ( ( !( (stFifotemp.Data1 == 0x00) || (stFifotemp.Data2 == 0x00) ) ) &&
                             ( !( (stFifotemp.Data1 == 0x80) && (stFifotemp.Data2 == 0x80) ) ) )
                        {
                            astFifo[g_u8VBIWriteCount].Data1 = stFifotemp.Data1;
                            astFifo[g_u8VBIWriteCount].Data2 = stFifotemp.Data2;

                            #if 0
                            /* field 2 */
                            printf( "@@@ [%06d] [%d]=[%c %c] (%02X %02X) (%02X %02X)\r\n", (U32)msAPI_Timer_GetTime0(), g_u8VBIWriteCount,
                                                                   (U8)(astFifo[g_u8VBIWriteCount].Data1&0x7F),
                                                                   (U8)(astFifo[g_u8VBIWriteCount].Data2&0x7F),
                                                                   (U8)(astFifo[g_u8VBIWriteCount].Data1&0x7F),
                                                                   (U8)(astFifo[g_u8VBIWriteCount].Data2&0x7F),
                                                                   (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1),
                                                                   (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2) );
                            #endif

                            g_u8VBIWriteCount++;
                            if (g_u8VBIWriteCount >= MCU_FIFO_LENGTH) // i.e. g_u8VBIWriteCount %= MCU_FIFO_LENGTH;
                            {
                                g_u8VBIWriteCount = 0;
                            }
                        }
                    }
                }
                /* field 1 */
                else if (CC_ODD_FOUND(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccEvenOddFound))
                {

                    /* field 1 */
                    stFifotemp.Data1 = g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1;
                    stFifotemp.Data2 = g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2;

                    if ( enEIA608SrvType==CC_1 ||
                         enEIA608SrvType==CC_2 ||
                         enEIA608SrvType==TT_1 ||
                         enEIA608SrvType==TT_2 )
                    {
                        if ( ( !( (stFifotemp.Data1 == 0x00) || (stFifotemp.Data2 == 0x00) ) ) &&
                             ( !( (stFifotemp.Data1 == 0x80) && (stFifotemp.Data2 == 0x80) ) ) )
                        {
                            astFifo[g_u8VBIWriteCount].Data1 = stFifotemp.Data1;
                            astFifo[g_u8VBIWriteCount].Data2 = stFifotemp.Data2;

                            #if 0
                            printf( "\n    [%06d](%02d,%2d)[%02d,%02d][%c %c]=(%02X %02X) (%02X %02X)", (U32)msAPI_Timer_GetTime0(), (U8)u8CcPacketCnt, g_u8CCBytesBufRdPtr, u8Count,\
                                                   (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccPacketCnt),
                                                       (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1&0x7F),
                                                       (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2&0x7F),
                                                       (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1&0x7F),
                                                       (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2&0x7F),
                                                       (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte1),
                                                       (U8)(g_ccBytesBuf[g_u8CCBytesBufRdPtr].ccByte2));
                            #endif
                            g_u8VBIWriteCount++;
                            if (g_u8VBIWriteCount >= MCU_FIFO_LENGTH) // i.e. g_u8VBIWriteCount %= MCU_FIFO_LENGTH;
                            {
                                g_u8VBIWriteCount = 0;
                            }
                        }
                    }

                    g_u8CCBytesBufRdPtr++;
                    if (g_u8CCBytesBufRdPtr >= CC_BUF_LEN_MAX) // i.e. g_u8CCBytesBufRdPtr %= CC_BUF_LEN_MAX
                    {
                        g_u8CCBytesBufRdPtr = 0;
                    }
                }
                else
                {
                    /* ASSERT */
                }

                msAPI_VBI_CC608ExistCheck(stFifotemp.Data1, stFifotemp.Data2);
                u32ACC_Last = MsOS_GetSystemTime();

            }
        }

        // XBYTE[BK_SELECT_00] = u8Bank; <- remove the bank change code
        if (u8Count != 0) //andy@SEC:20070326
        {
            g_u32LastVbiTime = msAPI_Timer_GetTime0();
        }

#if (VBI_DEBUG)
        msAPI_VBI_Dump();
    }
#endif
}

#if 1
/********************************************************************************/
/// API for valid VBI Data::
/// Getting valid VBI Data
/// @Param  pFifo \b OUT  Valid VBI Data
/// @return Valid VBI Data Size
/********************************************************************************/
U8 msAPI_VBI_GetDataFromVBIFifoPacket(U8 * pFifo)
{
    U8 u8Count = 0;
    #if 0
    U8 RatingType, Level, TVLevel1, TVLevel2;
    #endif


    while ( (g_u8VBIReadCount != g_u8VBIWriteCount) && (u8Count < ((MCU_FIFO_LENGTH+1)>>2)) )
  //while ( (g_u8VBIReadCount != g_u8VBIWriteCount) && (u8Count < MCU_FIFO_LENGTH) )
    {
        pFifo[u8Count++] = astFifo[g_u8VBIReadCount].Data1;
        pFifo[u8Count++] = astFifo[g_u8VBIReadCount].Data2;
        #if 0  // remove later
        printf( "$$$ [%d]=[%c %c] (%02X %02X)\n", g_u8VBIReadCount,
                                                (U8)(astFifo[g_u8VBIReadCount].Data1&0x7F),
                                                (U8)(astFifo[g_u8VBIReadCount].Data2&0x7F),
                                                (U8)(astFifo[g_u8VBIReadCount].Data1&0x7F),
                                                (U8)(astFifo[g_u8VBIReadCount].Data2&0x7F) );
        #endif

        #if 0
        //Debug info
        if (!(astFifo[g_u8VBIReadCount].Data1&BIT3))
        {
            printf("\nMPAA: ");
            RatingType = 2;
        }
        else if (!(astFifo[g_u8VBIReadCount].Data1&BIT4))
        {
            printf("\nUSTV: ");
            RatingType = 1;
        }
        else if (!(astFifo[g_u8VBIReadCount].Data1&BIT5))
        {
            if (!(astFifo[g_u8VBIReadCount].Data2&BIT3))
            {
                printf("\nC ENG: ");
                RatingType = 3;
            }
            else
            {
                printf("\nUnknown!");
                RatingType = 5;
            }
        }
        else
        {
            if (astFifo[g_u8VBIReadCount].Data2&BIT3)
            {
                printf("\nUnknown!");
                RatingType = 5;
            }
            else
            {
                printf("\nC FRE: ");
                RatingType = 4;
            }
        }

        // Get RatingLevel
        if (RatingType==2)
        {
            Level = (astFifo[g_u8VBIReadCount].Data1 & 0x07)%7;
            if (Level == 0)
                printf("NA");
            else if (Level ==1)
                printf("G");
            else if (Level ==2)
                printf("PG");
            else if (Level ==3)
                printf("PG-13");
            else if (Level ==4)
                printf("R");
            else if (Level ==5)
                printf("NC-17");
            else if (Level ==6)
                printf("X");
            else if (Level ==7)
                printf("NR");
            printf("\n");
        }
        else if(RatingType==1) // English/French
        {
            Level = (astFifo[g_u8VBIReadCount].Data2 & 0x07)%7;
            if (Level == 0)
                printf("None");
            else if (Level ==1)
                printf("TV-Y");
            else if (Level ==2)
                printf("TV-Y7");
            else if (Level ==3)
                printf("TV-G");
            else if (Level ==4)
                printf("TV-PG");
            else if (Level ==5)
                printf("TV-14");
            else if (Level ==6)
                printf("TV-MA");
            else if (Level ==7)
                printf("None");
            printf(" -- ");
        }
        else if (RatingType==3) // English
        {
            Level = (astFifo[g_u8VBIReadCount].Data2 & 0x07)%7;
            if (Level == 0)
                printf("E");
            else if (Level ==1)
                printf("C");
            else if (Level ==2)
                printf("C8+");
            else if (Level ==3)
                printf("G");
            else if (Level ==4)
                printf("PG");
            else if (Level ==5)
                printf("14+");
            else if (Level ==6)
                printf("18+");
            else if (Level ==7)
                printf("NA");
            printf("\r\n");
        }
        else if (RatingType==4) // French
        {
            Level = (astFifo[g_u8VBIReadCount].Data2 & 0x07)%7;
            if (Level == 0)
                printf("E");
            else if (Level ==1)
                printf("G");
            else if (Level ==2)
                printf("8ans+");
            else if (Level ==3)
                printf("13ans+");
            else if (Level ==4)
                printf("16ans+");
            else if (Level ==5)
                printf("18ans+");
            else if (Level ==6)
                printf("NA");
            else if (Level ==7)
                printf("NA");
            printf("\n");
        }

        // Get TVRating FVSLD
        if (RatingType==1)
        {
            TVLevel1 = (astFifo[g_u8VBIReadCount].Data1&BIT5) >> 5; //D
            TVLevel2 = (astFifo[g_u8VBIReadCount].Data2&0x38) >> 3; //FSL
            if(astFifo[g_u8VBIReadCount].Data2&BIT5)
            {
                if(Level == 2) // TV-Y7
                {
                    if (TVLevel2 & 0x04)
                        printf("FV");
                }
                else if ((Level == 4) || (Level == 5) || (Level == 6))
                {
                    if (TVLevel1)
                        printf("D");
                    if (TVLevel2 & 0x01)
                        printf("L");
                    if (TVLevel2 & 0x02)
                        printf("S");
                    if (TVLevel2 & 0x04)
                        printf("F");
                }
            }
            printf("\n");
        }
        #endif

        g_u8VBIReadCount++;
        g_u8VBIReadCount %= MCU_FIFO_LENGTH;
    }

    return u8Count;
}
#else
#define CC608_PATTERN_1       0     //cc1, fluke54200
#define CC608_PATTERN_2       0     //cc2, fluke54200
#define CC608_PATTERN_3       0     //cc3, fluke54200
#define CC608_PATTERN_4       0     //cc4, fluke54200
#define CC608_PATTERN_5       1     //cc RU2 to RU3 to RU4

#if (CC608_PATTERN_1)
static U8 CC608_Pattern[] = {
                        0x94, 0x2C, 0x94, 0x2C, 0x94, 0xAE, 0x94, 0xAE, 0x94, 0x2F, 0x94, 0x2F, 0x94, 0xA7, 0x94, 0xA7,
                        0x13, 0x46, 0x13, 0x46, 0x10, 0xA4, 0x10, 0xA4, 0x20, 0xC1, 0xC2, 0x43, 0xC4, 0x45, 0x46, 0xC7,
                        0xC8, 0x49, 0x4A, 0xCB, 0x4C, 0xCD, 0xCE, 0x4F, 0xD0, 0x51, 0x52, 0xD3, 0x54, 0xD5, 0xD6, 0x57,
                        0x58, 0xD9, 0xDA, 0x20, 0x94, 0xAD, 0x94, 0xAD, 0x13, 0xCE, 0x13, 0xCE, 0x10, 0x25, 0x10, 0x25,
                        0x20, 0x61, 0x62, 0xE3, 0x64, 0xE5, 0xE6, 0x67, 0x68, 0xE9, 0xEA, 0x6B, 0xEC, 0x6D, 0x6E, 0xEF,
                        0x70, 0xF1, 0xF2, 0x73, 0xF4, 0x75, 0x76, 0xF7, 0xF8, 0x79, 0x7A, 0x20, 0x94, 0xAD, 0x94, 0xAD,
                        0x13, 0x45, 0x13, 0x45, 0x10, 0x20, 0x10, 0x20, 0x20, 0xA1, 0x2C, 0xAE, 0x3B, 0xBA, 0xA7, 0xA2,
                        0x23, 0x25, 0x26, 0x40, 0x2F, 0xA8, 0x29, 0x5B, 0x5D, 0xAB, 0xAD, 0x7C, 0xBC, 0x3D, 0x3E, 0xBF,
                        0x91, 0xB5, 0xA4, 0x80, 0x91, 0xB6, 0x20, 0x80, 0x94, 0xAD, 0x94, 0xAD, 0x13, 0xC8, 0x13, 0xC8,
                        0x10, 0xA1, 0x10, 0xA1, 0x20, 0x2A, 0x91, 0x38, 0x91, 0x3B, 0xFB, 0xDC, 0x91, 0xBA, 0x91, 0xBC,
                        0x5E, 0x80, 0x91, 0x3D, 0xFD, 0xFE, 0x91, 0x3E, 0xDF, 0x80, 0x91, 0xBF, 0xE0, 0x20, 0x91, 0xB0,
                        0x91, 0x31, 0x91, 0x34, 0x91, 0x32, 0x91, 0xB3, 0x91, 0x37, 0x20, 0x80, 0x91, 0xB9, 0x20, 0x7F,
                        0x20, 0x80, 0x94, 0xAD, 0x94, 0xAD, 0x13, 0x4C, 0x13, 0x4C, 0x20, 0x80, 0x10, 0xA8, 0x10, 0xA8,
                        0x20, 0x80, 0x97, 0xAE, 0x97, 0xAE, 0x97, 0x25, 0x97, 0x25, 0x20, 0x20, 0x20, 0xB0, 0x31, 0x32,
                        0xB3, 0x34, 0xB5, 0xB6, 0x37, 0x38, 0xB9, 0x20, 0x20, 0x80, 0x94, 0xAD, 0x94, 0xAD,
                     };
#endif

#if (CC608_PATTERN_2)
static U8 CC608_Pattern[] = {
                        0x9D, 0x2C, 0x9D, 0xAE, 0x9D, 0x29, 0x9E, 0xC8, 0x20, 0x20, 0x98, 0x23, 0x1F, 0xAE, 0x43, 0xEC,
                        0xEF, 0x73, 0xE5, 0x64, 0x20, 0x43, 0x61, 0x70, 0xF4, 0xE9, 0xEF, 0x6E, 0x20, 0x43, 0x43, 0x34,
                        0x20, 0x6D, 0xEF, 0x64, 0xE5, 0xAE, 0x20, 0x80, 0x01, 0x85, 0x46, 0x40, 0x8F, 0xE5,
                     };
#endif

#if (CC608_PATTERN_3)
static U8 CC608_Pattern[] = {
                        0x15, 0x2C, 0x15, 0xAE, 0x15, 0x20, 0x16, 0x46, 0x20, 0x20, 0x10, 0xA2, 0x43, 0xEC, 0xEF, 0x73,
                        //0x15, 0x2C, 0x15, 0xAE, 0x15, 0x20, 0x16, 0xC4, 0x20, 0x20, 0x10, 0xA2, 0x43, 0xEC, 0xEF, 0x73,
                        0xE5, 0x64, 0x20, 0x43, 0x61, 0x70, 0xF4, 0xE9, 0xEF, 0x6E, 0x20, 0x43, 0x43, 0xB3, 0x20, 0x6D,
                        0xEF, 0x64, 0xE5, 0xAE, 0x20, 0x80, 0x15, 0x2F,
                     };
#endif

#if (CC608_PATTERN_4)
static U8 CC608_Pattern[] = {
                        0x9D, 0x2C, 0x9D, 0xAE, 0x9D, 0x29, 0x9E, 0xC8, 0x20, 0x20, 0x98, 0x23, 0x1F, 0xAE, 0x43, 0xEC,
                        0xEF, 0x73, 0xE5, 0x64, 0x20, 0x43, 0x61, 0x70, 0xF4, 0xE9, 0xEF, 0x6E, 0x20, 0x43, 0x43, 0x34,
                        0x20, 0x6D, 0xEF, 0x64, 0xE5, 0xAE, 0x20, 0x80, 0x01, 0x85, 0x46, 0x40, 0x8F, 0xE5,
                     };
#endif

#if (CC608_PATTERN_5)
static U8 CC608_Pattern[] = {
                        0x94, 0x2C, 0x94, 0x2C, 0x94, 0xAE, 0x94, 0xAE, 0x94, 0x2F, 0x94, 0x2F, 0x94, 0x25, 0x94, 0x25,
                        0x94, 0x46, 0x94, 0x46, 0x10, 0xA4, 0x10, 0xA4, 0x20, 0xC1, 0xC2, 0x43, 0xC4, 0x45, 0x46, 0xC7,     //First Row
                        0x94, 0xAD, 0x94, 0xAD, 0x94, 0xCE, 0x94, 0xCE, 0x10, 0x25, 0x10, 0x25, 0x20, 0x61, 0x62, 0xE3,
                        0x64, 0xE5, 0xE6, 0x67, 0x94, 0xAD, 0x94, 0xAD, 0x94, 0xC2, 0x94, 0xC2, 0x10, 0x25, 0x10, 0x25,
                        //0x20, 0xB0, 0x31, 0x32, 0xB3, 0x34, 0xB5, 0xB6, 0x94, 0xAD, 0x94, 0xAD,
                        0x20, 0xB0, 0x31, 0x32, 0xB3, 0x34, 0xB5, 0xB6, 0x94, 0x26, 0x94, 0x26, 0x13, 0xE6, 0x13, 0xE6,
                        0x10, 0xA4, 0x10, 0xA4, 0x20, 0x62, 0xE3, 0x43, 0x46, 0xC7, 0xC4, 0x45,
                     };
#endif



U8 msAPI_VBI_GetDataFromVBIFifoPacket(U8 * pFifo)
{
    U8 u8Count = 0;

    printf("\nVBI_DATA");
    while (u8Count < sizeof(CC608_Pattern))
    {
        pFifo[u8Count] = CC608_Pattern[u8Count];
        u8Count++;
        pFifo[u8Count] = CC608_Pattern[u8Count];
        u8Count++;
    }

    return u8Count;
}
#endif

U32 msAPI_VBI_LastVBITime(void) //andy@SEC:20070326
{
   return g_u32LastVbiTime;
}

//==============================================================================
/// API to Set CC data rate::
/// Set CC's data rate
/// @Param  u8Mode \b IN video system mode
/// @return TRUE:: Successfully set
///         FALSE:: Fail
//==============================================================================
U8 msAPI_VBI_CC_DataRateSet(U8 u8Mode)
{
    U8 i=0;

    // Get the video system's type
    for(i=0; i<VIDEO_TYPE_CNT; i++)
    {
        if(video_standard_vbi_settings[i][0] == u8Mode) break;
    }

    if(i >= VIDEO_TYPE_CNT)
    {
        return FALSE;
    }

    return (MDrv_VBI_CC_SetDataRate(video_standard_vbi_settings[i]));
}

#if (VBI_DEBUG) // testing for CC
static U8 CC_Packet_Buffer[32];
static U8 CC_Service_Buffer[2];
static U8 pidx = 0, u8CcLen = 0;
void msAPI_VBI_Dump(void)
{
    U8 u8Loop;

    u8CcLen = msAPI_VBI_GetDataFromVBIFifoPacket((U8 *)&CC_Packet_Buffer[0]);

    u8Loop = 0;
    while ( u8Loop < u8CcLen )
    {
        CC_Service_Buffer[0] = CC_Packet_Buffer[u8Loop++];
        CC_Service_Buffer[1] = CC_Packet_Buffer[u8Loop++];

        if (pidx == 0)
        {
            printf("\n");
        }

        printf("0x%02x, 0x%02x, ", CC_Service_Buffer[0], CC_Service_Buffer[1]);
        pidx += 2;
        if (pidx == 8)  pidx = 0;
    }

}
#endif

#undef MSAPI_VBI_C


