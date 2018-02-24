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

#ifndef MAPP_EIT_H
#define MAPP_EIT_H

////////////////////////////////////////////////////////////////////////////////
///
/// @file mapp_eit.h
/// @author MStar Semiconductor Inc.
/// @brief EIT Parsing and management Functions
///
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                              Include files                                 */
/******************************************************************************/
#include "mapp_epgdb_public.h"

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#ifdef MAPP_EIT_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#ifndef _PA2VA
#define _PA2VA
#endif

#if (ENABLE_DTV_EPG)
// Features configuration
#define MONITOR_OTHER_EIT       TRUE    // enable to receive EIT OTHER
#define EIT_FOR_DTG_ONLY        TRUE    // enable handle a special case for DTG test

#define NOW                     0
#define NEXT                    1
#define MAX_PF_STRING_LENGTH         (4096*sizeof(U16))

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
// Total 13 Bytes
typedef struct
{
    U8  u8VerNum;
    U8  u8SecNum;
    U8  u8SecNum_InSeg;
    U16 u16SecNum_InSrv;

    U8  u8SegNum_InSrv;
    U8  u8TblIdx;
    U16 u16SrvIdx;
    U32 u32CrcValue;
} MS_EIT_PARSE_PARAM;

typedef struct
{
    BYTE bDVB          : 1;
    BYTE bEBU          : 1;
    BYTE bReserved     : 6;
}Sub_VALID_INFO;

/******************************************************************************/
/*                                 Structure                                  */
/******************************************************************************/
// Total 530 Bytes
typedef struct EPG_PACKED
{
    U8  short_event_descriptor[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U8  extended_event_description[MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN];

    U8  start_time[5];
    U8  duration[3];

    U8  version_number;
    U8  u8Parental_Control;
#if  1//ENABLE_SBTVD_DTV_SYSTEM
    U8  u8Parental_ObjectiveContent;
#endif
    U8  u8Content_nibble_level1 : 4;
    U8  u8Content_nibble_level2 : 4;
    U8  u8PreferredNameId;
    U32 u32PDSD_private_data_specifier;
    U8 guidance_descriptor[MW_MAX_GUIDANCE_DESCRIPTOR_LEN];
    U8 u8CMG_Data;
}MS_EIT_CUR_EVENT_PF;

typedef enum
{
    E_COMPONENT_MPEG_AUDIO       = 0x00,
    E_COMPONENT_AC3_AUDIO        = 0x01,
    E_COMPONENT_AAC_AUDIO        = 0x02,
    E_COMPONENT_DVB_SUBTITLE     = 0x03,
    E_COMPONENT_EBU_SUBTITLE     = 0x04,
    E_COMPONENT_UNSUPPORT        = 0xFF
} E_COMPONENT_TYPE;

typedef struct
{
    BOOL bEnableScheduleExtendEvent;
    BOOL bEnablePVR_CRID;
    U32 u32PF_BufferAddress;
    BOOL (*pfNotify_EIT_Cur_PF)(U8 *pu8Section);
} MS_EIT_INIT_PARAMETER;

/******************************************************************************/
/*                                 Variables                                  */
/******************************************************************************/



/******************************************************************************/
/*                              Function Prototypes                           */
/******************************************************************************/
/* Info Banner ********************************************************************************************/
INTERFACE void MApp_EIT_Init(MS_EIT_INIT_PARAMETER* psInitParameter);
INTERFACE BOOL MApp_EIT_GetPfString(U8 sec, U8 *pdest, U16 u16Shift, U16 u16Size );
INTERFACE BOOL MApp_EIT_Is_Cur_PF_Change(void);
INTERFACE void MApp_EIT_Reset_Cur_PF_Change(void);
INTERFACE void MApp_EIT_Cur_PF_Parse(U8 au8Sec[], U8* pu8FirstSectionNo, U8* pu8LastSectionNo, U8* ver);
INTERFACE U8   MApp_EIT_GetCurParentControl(void);
#if 0 // ENABLE_SBTVD_DTV_SYSTEM
INTERFACE U8   MApp_EIT_GetCurParentObjectiveContent(void);
#endif

/* EPG PF ********************************************************************************************/
INTERFACE BOOL MApp_EIT_All_PF_Parse(MS_EIT_PARSE_PARAM* pParse, MW_EN_EPG_PF_SRV_HDR* pPfSrvHdr, U8 au8Sec[]);

/* EPG Schedule ********************************************************************************************/
INTERFACE BOOL MApp_EIT_All_Sche_Parse(MS_EIT_PARSE_PARAM* pParse, MW_EN_EPG_SCHE_SRV_HDR* pSrvScheHdr, U8 pu8Sec4K[]);
INTERFACE void MApp_EIT_All_Sche_ResetFilter( void );




INTERFACE BOOLEAN MApp_EIT_GetCurPFInfo(MS_EIT_CUR_EVENT_PF* pEventInfo);
INTERFACE BOOLEAN MApp_EIT_IsCurPFInfoExist(void);


INTERFACE BOOLEAN MApp_EIT_ResetCurPFInfo(void);
INTERFACE U8 MApp_EIT_GetCurPreferredNameID(void);
INTERFACE BOOLEAN MApp_EIT_FreeCurPFInfo(void);
#endif  //(ENABLE_DTV_EPG)

#undef INTERFACE
#endif /* MAPP_EIT_H */

