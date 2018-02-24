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

#ifndef _M88DD2000_H_
#define _M88DD2000_H_

/* ------------------------------------
    Header Files
   ------------------------------------ */
#include "datatype.h"

/* ------------------------------------
    Macro Definitions
   ------------------------------------ */
#undef EXTERN

#ifdef _M88DD2000_C_
#define EXTERN
#else
#define EXTERN  extern
#endif


/* ------------------------------------
    Variables Definitions/Declarations
   ------------------------------------ */
#define M88DD2000_devAddr              0x20
#define COFDM_DEM_I2C_ID            M88DD2000_devAddr

typedef enum _MT_FE_MOBILE_MODE
{
    MtFeMobileMode_Auto = 0,
    MtFeMobileMode_On,
    MtFeMobileMode_Off
} MT_FE_MOBILE_MODE;

typedef enum _MT_FE_CARRIER_MODE
{
    MtFeCrrierMode_Undef = 0,
    MtFeCrrierMode_Multicarrier,
    MtFeCrrierMode_SingleCarrier
} MT_FE_CARRIER_MODE;


typedef enum _MT_FE_SPECTRUM_MODE
{
    MtFeSpectrum_Undef = 0,
    MtFeSpectrum_NoInversion,
    MtFeSpectrum_Inversion
} MT_FE_SPECTRUM_MODE;


typedef enum _MT_FE_FRAME_MODE
{
    MtFeFrameMode_Undef = 0,
    MtFeFrameMode_Pn420,
    MtFeFrameMode_Pn945,
    MtFeFrameMode_Pn595
} MT_FE_FRAME_MODE;


typedef enum _MT_FE_INTERLEAVING_DEPTH
{
    MtFeInterleavingDepth_Undef = 0,
    MtFeInterleavingDepth_240,
    MtFeInterleavingDepth_720
} MT_FE_INTERLEAVING_DEPTH;

typedef enum _MT_FE_CONSTELLATION_PATTERN
{
    MtFeConstellationPattern_Undef = 0,
    MtFeConstellationPattern_4Qam,
    MtFeConstellationPattern_4QamNr,
    MtFeConstellationPattern_16Qam,
    MtFeConstellationPattern_32Qam,
    MtFeConstellationPattern_64Qam,
    MtFeConstellationPattern_128Qam,
    MtFeConstellationPattern_256Qam
} MT_FE_CONSTELLATION_PATTERN;

typedef enum _MT_FE_FEC_CODE_RATE
{
    MtFeFecCodeRate_Undef = 0,
    MtFeFecCodeRate_0p4,
    MtFeFecCodeRate_0p6,
    MtFeFecCodeRate_0p8
} MT_FE_FEC_CODE_RATE;

typedef enum _MT_FE_SI_MAP_MODE
{
    MtFeSiMapMode_Undef = 0,
    MtFeSiMapMode_1,
    MtFeSiMapMode_2
} MT_FE_SI_MAP_MODE;

typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_SYMBOL_TIMING_LOCK,
    COFDM_AGC_LOCK,
    COFDM_DESCRAMBLER_LOCK,
    COFDM_BYTE_ALIGNER_LOCK
} COFDM_LOCK_STATUS;

typedef struct _MT_FE_CHAN_INFO
{
    MT_FE_CARRIER_MODE            carrier_mode;
    MT_FE_SPECTRUM_MODE            spectrum_mode;
    MT_FE_FRAME_MODE            frame_mode;
    MT_FE_INTERLEAVING_DEPTH    interleaving_depth;
    MT_FE_CONSTELLATION_PATTERN    constellation_pattern;
    MT_FE_FEC_CODE_RATE            fec_code_rate;
    MT_FE_SI_MAP_MODE            si_map_mode;
} MT_FE_CHAN_INFO;

/* ------------------------------------
    Function Prototypes
   ------------------------------------ */
EXTERN void M88DD2000_Initialize(void);
EXTERN BOOLEAN M88DD2000_InitRegister(void);
EXTERN void M88DD2000_Config(void);
EXTERN BOOLEAN M88DD2000_LoadFw(const U8* p_fw);
EXTERN BOOLEAN M88DD2000_SetMobileMode(MT_FE_MOBILE_MODE eMode);
EXTERN BOOLEAN M88DD2000_GetChannelInfoCode(U32 *pChanInfo);
EXTERN void M88DD2000_ChannelInfoCodeParse(U32 chan_info_code, MT_FE_CHAN_INFO* p_info);
EXTERN BOOLEAN M88DD2000_PresetChannelInfo(MT_FE_CHAN_INFO* p_info);
EXTERN BOOLEAN M88DD2000_SetSiMapMode(MT_FE_SI_MAP_MODE mode);
EXTERN BOOLEAN M88DD2000_EnhancePerformance(U32 chan_info_code);
EXTERN BOOLEAN M88DD2000_Serial_Control(BOOLEAN bEnable);
EXTERN BOOLEAN M88DD2000_SoftReset(void);
EXTERN BOOLEAN M88DD2000_WriteBytesRepeat(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
EXTERN BOOLEAN M88DD2000_ReadBytesRepeat(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
EXTERN BOOLEAN M88DD2000_GetLock(void);
EXTERN BOOLEAN M88DD2000_TSOut_Control(BOOLEAN bEnable);

#endif /* _M88DD2000_H_ */
