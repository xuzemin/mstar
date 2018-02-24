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

#ifndef MAPI_CC_MONITOR_H
#define MAPI_CC_MONITOR_H

/***************************************************************************************/
/*                 Header Files                                                        */
/***************************************************************************************/
#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)
/// Format of CC (Closed Caption)
typedef enum
{
    E_VDEC_EX_CC_NONE       = 0x00,
    E_VDEC_EX_CC_608        = 0x01, //For CC608 or 157
    E_VDEC_EX_CC_708        = 0x02, //For CC708
    E_VDEC_EX_CC_UNPACKED   = 0x03,
} VDEC_EX_CCFormat;
#else
#include "apiVDEC_EX.h"
#endif
#include "mapi_cc_type.h"
#include "mapi_cc_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************/
/* Define                                                                   */
/***************************************************************************************/
#define CC608_RDNO                      2
#define CC608_RDINTERVAL  16    // 4   young.yang@20130214 -> For enhance mode
#define CC608_PACKET_SIZE  32  // 8   young.yang@20130214 -> For enhance mode
#define CC608_FRAMEBUFFER_SIZE          6

#define CC_MEASURE_SYSTEM_TIME          0    // 0: None, 1: all

/***************************************************************************************/
/* Enum                                                                              */
/***************************************************************************************/
typedef enum
{
    CC_OFF,
    CC_1,
    CC_2,
    CC_3,
    CC_4,
    TT_1,
    TT_2,
    TT_3,
    TT_4
} EN_EIA608_SRV_TYPE;

typedef enum
{
    CC_INPUT_FCC608USING157     = 0,
    CC_INPUT_CC_PACKET_BUFFER,
    CC_INPUT_CC_EACHPACKETBUFFER_SIZE,
    CC_INPUT_U32CC608RBADDR,
    CC_INPUT_U32CC608RBSIZE,
    CC_INPUT_U32CC708RBADDR,
    CC_INPUT_U32CC708RBSIZE,
    CC_INPUT_U32CCCACHEADDR,
    CC_INPUT_U32CCCACHESIZE,
    CC_INPUT_U8CCTYPE_OPTION,
    CC_INPUT_FACCEXISTFLAG,
    CC_INPUT_FDCCEXISTFLAG,
    CC_INPUT_CC_DRIVER_NEED_INIT,
    CC_INPUT_CC_157_LAST_TIME,
    CC_INPUT_CC_608_LAST_TIME,
    CC_INPUT_CC_708_LAST_TIME,
    CC_INPUT_CC_708_AVAILTYPE,
    CC_INPUT_CC_608_AVAILTYPE,
    CC_INPUT_XDS_FULLY_CHECK,
    CC_INPUT_U32CC_RVU_STC,
    CC_INPUT_DIGITAL_TYPE,
    CC_INPUT_U32RVUCC608RBADDR,
    CC_INPUT_U32RVUCC608RBSIZE,
    CC_INPUT_U32RVUCC708RBADDR,
    CC_INPUT_U32RVUCC708RBSIZE,
    CC_INPUT_FIELD_REVERSE,
    CC_INPUT_RESET_RVUCC,
    CC_INPUT_TRICK_MODE,
    CC_INPUT_SET_POSITION_ACK,
    CC_INPUT_DUMP_DBG_MSG,
    CC_INPUT_FLUKE_PAL_N,
    CC_INPUT_VCHIP_TIMEOUT,
} EN_CC_INPUT_Info;

typedef enum
{
    XDS_INFO_STATIONID,
    XDS_INFO_PROGRAMTITLE,
    XDS_INFO_NETWORKNAME,
    XDS_INFO_CAPTIONLANGUAGE,
}EN_XDS_INFO;
    
/***************************************************************************************/
/* Data structure                                                                      */
/***************************************************************************************/
typedef struct
{
    CC_U8 Data1;
    CC_U8 Data2;
} _FifoType;

typedef struct
{
    CC_U8 ccByte1;         // CCBytes[7:0]
    CC_U8 ccByte2;         // CCBytes[15:8]
    CC_U8 ccPacketCnt;     // ccPacketCnt[4:0]
    CC_U8 ccFrameCnt;      // ccFrameCnt[4:0]
    CC_U8 ccEvenOddFound;  // ccEvenOddFound[0]: even/odd, ccEvenOddFound[6]: even found, ccEvenOddFound[7]: odd found

//    #ifdef PATCH_T3_VBI_WORKAROUND
//    CC_U8 ccReserved[11];  // T3, MIU enlarge to 128 bits...
//   #else
    CC_U8 ccReserved[3];
 //   #endif
} CC_Buf_Content;
/***************************************************************************************/
/* Function structure                                                                      */
/***************************************************************************************/
typedef struct
{
   void (*Open)(void);
   void (*Close)(void);
   VDEC_EX_CCFormat (*TransformCCFmt)(CC_U8 u8CC608);
   void (*DrvInit)(CC_U8 u8CCType);
   void (*SetInputInfo)(CC_U8 select, void *pVal);
   void (*StopMVDParser)(void);
   void (*Stop708Parsing)(void);
   void (*SetBufferStartAddr)(CC_U32 u32StartAddress, CC_U8 u8CC608);
   void (*ParsingCommand)(CC_U8 u8CCEnable, CC_U16 u16BufferSize, CC_U8 u8CCType);
   CC_BOOL (*HasAvailableData)(CC_U8 u8CC608);
   CC_BOOL (*DigitalCCUsing157)(void);
   CC_U8 (*Check608Type)(CC_U8 c1, CC_U8 c2);
        
   void (*VbiInit)(CC_U32 u32Addr);
   void (*YPbPr_Init)(CC_U8 cvbs_no);
   void (*VbiTriggerMonitor)(void);
   EN_VCHIP_DATA_STATUS (*GetEIA608Data)(CC_U8 *pu8EIA608Data1, CC_U8 *pu8EIA608Data2);
   void (*MonitorVBIData)(EN_EIA608_SRV_TYPE enEIA608SrvType);
   CC_U8 (*GetDataFromVBIFifoPacket)(CC_U8 * pFifo);
   void (*ProcessXDS)(_FifoType pstFifo);
   void (*CheckVCHIPTimeOut)(void);
   void (*VchipRateReset)(void);
   CC_U8 (*DataRateSet)(CC_U8 u8Mode);
   CC_U8* (*GetXDSInfo)(EN_XDS_INFO enxdsinfo);
   void (*ResetXDSInfo)(void);
} CC_InputSource;


/***************************************************************************************/
/* Variables                                                                           */
/***************************************************************************************/
extern const CC_InputSource CC_SourceFuns;

/***************************************************************************************/
/* Functions                                                                           */
/***************************************************************************************/

#ifdef __cplusplus
  }
#endif

#endif
///*** please do not remove change list tag ***///
///***$Change: 1042864 $***///
