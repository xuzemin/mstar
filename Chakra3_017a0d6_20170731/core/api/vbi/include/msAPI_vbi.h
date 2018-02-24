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
#ifndef MSAPI_VBI_H
#define MSAPI_VBI_H

#include "datatype.h"

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7)
#define PATCH_T3_VBI_WORKAROUND         1   // SH@ 20090706, T3 patch for VBI
#endif

/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define MCU_FIFO_LENGTH     31 // the max len of CC buffer 31 (i.e. 5-bit: 11111b)
#define DTV_608_VCHIP_DEBUG 0
#define VBI_DEBUG           0


#define SET_608CCISEXIST(col)                 (fACCExistFlag = col)

/********************************************************************************/
/*                    typedef struct                                                  */
/********************************************************************************/
typedef struct
{
    U8 Data1;
    U8 Data2;
} _FifoType;

typedef struct
{
    U8 CC1_LANGUAGE;
    U8 CC2_LANGUAGE;
    U8 CC3_LANGUAGE;
    U8 CC4_LANGUAGE;
    U8 TEXT1_LANGUAGE;
    U8 TEXT2_LANGUAGE;
    U8 TEXT3_LANGUAGE;
    U8 TEXT4_LANGUAGE;
}CAPTION_LAN_t;
/********************************************************************************/
/*                    Enum                                                      */
/********************************************************************************/
typedef enum
{
    VCHIP_DATA_NONE,
    VCHIP_DATA_NO_CHANGE,
    VCHIP_DATA_CHANGE
} EnuVChipDataStatus;

typedef enum
{
    CL_UNKNOWN,
    CL_ENGLISH,
    CL_SPANISH,
    CL_FRENCH,
    CL_GERMAN,
    CL_ITALIAN,
    CL_OTHER,
    CL_NONE,
}EnCaptionLanguage;

typedef enum
{
    CURRENT_START = 0x01,
    CURRENT_CONTI,
    FUTURE_START,
    FUTURE_CONTI,
    CHANNEL_START,
    CHANNEL_CONTI,
    MISC_START,
    MISC_CONTI,
    PUBLIC_START,
    PUBLIC_CONTI,
    RESERVED_START,
    RESERVED_CONTI,
    UNDEFINED_START,
    UNDEFINED_CONTI,
    ALL_END
} _XDSControlType;

typedef enum
{
    IDENTIFICATION = 0x01,
    PROGRAM_LENGTH,
    PROGRAM_NAME,
    PROGRAM_TYPE,
    PROGRAM_RATING,
    AUDIO_SERVICE,
    CAPTION_SERVICE,
    CGMS_A,
    ASPECT_RATIO,
    DESCRIPTION    = 0x10,

    NETWORK_NAME   = 0x01,
    NETWORK_CALL   = 0x02

} _XDSCurrentType;

typedef enum
{
    Network_Names = 0x01,
    Call_Letters,
    Tape_Delay,
    Transmission_Signal_Identifier
} _XDSChannelType;



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


#ifdef MSAPI_VBI_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


/********************************************************************************/
/*                    Function Prototype                                           */
/********************************************************************************/
INTERFACE void msAPI_VBI_CC608ExistCheck(U8 u8D6CC_Data1, U8 u8D6CC_Data2);
INTERFACE BOOLEAN msAPI_VBI_AnalogCC608_Available(void);
INTERFACE void msAPI_VBI_Init(void);
INTERFACE EnuVChipDataStatus msAPI_VBI_GetEIA608Data(U8 *pu8EIA608Data1, U8 *pu8EIA608Data2);
INTERFACE U8* msAPI_VBI_GetProgramTitle(void);
INTERFACE U8* msAPI_VBI_GetStationID(void);
INTERFACE U8* msAPI_VBI_GetNetworkName(void);
INTERFACE void msAPI_VBI_GetCaptionLanguage(CAPTION_LAN_t *pcaptionlan);
INTERFACE void msAPI_VBI_ResetVchipRating(void);
INTERFACE void msAPI_VBI_ResetXDSInfo(void);
INTERFACE void msAPI_VBI_MonitorVBIData(EN_EIA608_SRV_TYPE enEIA608SrvType);
INTERFACE U8 msAPI_VBI_GetDataFromVBIFifoPacket(U8 * pFifo);
INTERFACE void msAPI_VBI_ProcessXDS(_FifoType pstFifo);
INTERFACE U32 msAPI_VBI_LastVBITime(void); //andy@SEC:20070326
INTERFACE U8 msAPI_VBI_CC_DataRateSet(U8 u8Mode);
#ifndef DISABLE_COMPONENT_VBI
INTERFACE void msAPI_VBI_YPbPr_Init(U8 cvbs_no);
#endif
#if (VBI_DEBUG)
INTERFACE void msAPI_VBI_Dump(void);
#endif
#undef INTERFACE
#endif
