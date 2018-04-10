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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_GLOBAL_H
#define MSAPI_GLOBAL_H

//******************************************************************************

#include "MsCommon.h"
#include "drvXC_IOPort.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "debug.h"
#include "drvAUDIO_if.h"
#include "drvSYS.h"
//******************************************************************************

#ifdef MSAPI_GLOBAL_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/********************************************************************************/
/*                     Macro                                                    */
/* ******************************************************************************/



//*************************************************************************
//          Enums
//*************************************************************************
typedef enum
{
    EN_SYS_INPUT_SOURCE_TYPE_NONE       = 0x0000,
    EN_SYS_INPUT_SOURCE_TYPE_S2			= 0x0001,
    EN_SYS_INPUT_SOURCE_TYPE_ATSC		= 0x0002,
    EN_SYS_INPUT_SOURCE_TYPE_DVBT		= 0x0004,
    EN_SYS_INPUT_SOURCE_TYPE_DVBC		= 0x0008,
    EN_SYS_INPUT_SOURCE_TYPE_DTMB       = 0x0010,
    EN_SYS_INPUT_SOURCE_TYPE_ISDBT      = 0x0020,
    EN_SYS_INPUT_SOURCE_TYPE_ATV        = 0x0040,
    EN_SYS_INPUT_SOURCE_TYPE_SCART      = 0x0080,
    EN_SYS_INPUT_SOURCE_TYPE_CVBS       = 0x0100,
    EN_SYS_INPUT_SOURCE_TYPE_VGA        = 0x0200,
    EN_SYS_INPUT_SOURCE_TYPE_HDMI       = 0x0400,
    EN_SYS_INPUT_SOURCE_TYPE_YPBPR      = 0x0800,
    EN_SYS_INPUT_SOURCE_TYPE_SVIDEO     = 0x1000,
    EN_SYS_INPUT_SOURCE_TYPE_STORAGE    = 0x2000,
#if(ENABLE_FM_RADIO)
    EN_SYS_INPUT_SOURCE_TYPE_RADIO      = 0x4000,
#endif
#if(GAME_ENABLE)
    EN_SYS_INPUT_SOURCE_TYPE_GAME       = 0x8000,
#endif
} EN_SYS_INPUT_SOURCE_TYPE;

/// Aspect Ratio Type ==========================================================
typedef enum
{
    /* general */
    VIDEOSCREEN_MIN,                        ///< Video Screen Min
    VIDEOSCREEN_PROGRAM = VIDEOSCREEN_MIN, ///< according AFD or WSS setting
    VIDEOSCREEN_NORMAL,                 ///< Video Screen Normal
    VIDEOSCREEN_FULL,                      ///< video full panel resolution
    VIDEOSCREEN_ZOOM,                   ///< Video Screen Zoom
    VIDEOSCREEN_CINEMA,                 ///< Video Screen Cinema

    //VIDEOSCREEN_WIDE1,
    //VIDEOSCREEN_WIDE2,

    /* specific options for 4:3 panel */
    VIDEOSCREEN_LETTERBOX,          ///< Video Screen Letterbox
    /* specific options for wide panel */
    VIDEOSCREEN_16by9_SUBTITLE,     ///< Video Screen 16:9 subtitle
    VIDEOSCREEN_PANORAMA,           ///< Video Screen Panorama
    /* others */
    VIDEOSCREEN_14by9,                        ///< 14:9
    VIDEOSCREEN_WSS_16by9,                    ///< WSS 16:9
    VIDEOSCREEN_WSS_14by9_LETTERBOX_CENTER,   ///< WSS: 0001 14:9 Letterbox Center
    VIDEOSCREEN_WSS_14by9_LETTERBOX_TOP,      ///< WSS: 0010 14:9 Letterbox Top
    VIDEOSCREEN_WSS_16by9_LETTERBOX_CENTER,   ///< WSS: 1011 16:9 Letterbox Center
    VIDEOSCREEN_WSS_16by9_LETTERBOX_TOP,      ///< WSS: 0100 16:9 Letterbox Top
    VIDEOSCREEN_ZOOM1,                        ///< Video Screen Zoom1
    VIDEOSCREEN_ZOOM2,                        ///< Video Screen Zoom2
    VIDEOSCREEN_JUSTSCAN,                     ///< Video Screen Justscan
    VIDEOSCREEN_SCENE4_3to16_9,               ///< Video Screen Scene 4:3 to 16:9
    VIDEOSCREEN_SCENE16_9to4_3,               ///< Video Screen Scene 16:9 to 4:3
    VIDEOSCREEN_SCENE4_3to16_9_WITH_CCO,      ///< Video Screen Scene 4:3 to 16:9 with CCO
    VIDEOSCREEN_SCENE4_3to4_3_WITH_CCO,       ///< Video Screen Scene 4:3 to 4:3 with CCO
    VIDEOSCREEN_SCENE4_3to16_9_WITH_LB,       ///< Video Screen Scene 4:3 to 16:9 with LB
    VIDEOSCREEN_SCENE4_3to4_3_WITH_LB,        ///< Video Screen Scene 4:3 to 4:3 with LB
    VIDEOSCREEN_ORIGIN,
    VIDEOSCREEN_PROGRAM_16X9,
    VIDEOSCREEN_PROGRAM_4X3,
    VIDEOSCREEN_PROGRAM_14X9,

    VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE,    // Keep source H/V ratio and scale to fit panel
    VIDEOSCREEN_MM_FULL,    // H and V scale to fit panel
    VIDEOSCREEN_MM_1_1,     // Bypass scale
    VIDEOSCREEN_MM_16_9,    // Display window: H:V=16:9
    VIDEOSCREEN_MM_4_3,     // Display window: H:V=4:3
    VIDEOSCREEN_MM_ZOOM1,   // TO BE defined
    VIDEOSCREEN_MM_ZOOM2,   // TO BE defined
    VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER,
#if ENABLE_3D_PROCESS
    VIDEOSCREEN_3D_FULL,
    VIDEOSCREEN_3D_AUTO,
    VIDEOSCREEN_3D_CENTER,
#endif
    VIDEOSCREEN_POINT_TO_POINT, //for pc and HDMI
    VIDEOSCREEN_NUMS,       //< numbers of video screen type
}EN_ASPECT_RATIO_TYPE;

//*************************************************************************
//          Structures
//*************************************************************************
// display system information
typedef struct
{
    INPUT_SOURCE_TYPE_t enInputSourceType; //< Input source type
    EN_ASPECT_RATIO_TYPE enAspectRatio;

} MS_SYS_INFO;

typedef struct
{
    INPUT_SOURCE_TYPE_t u8InputSource;
    INPUT_SOURCE_TYPE_t u8CVBSOutVideoSource;
    AUDIO_INPUT_TYPE    u8CVBSOutAudioSource;
}CVBS_OUTPUT_INFO;


/********************************************************************************/
/*                   Function Prototypes                     */
/********************************************************************************/

#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
INTERFACE BOOLEAN gbBootTimeFinish;
INTERFACE U32 gU32BootTime;
INTERFACE U32 gU32BootStepTime;
INTERFACE U32 gU32ATCkPtTime;   //auto test check point
INTERFACE U32 gU32CompressStepTime;
INTERFACE U32 gU32CompressTotalStepTime;

#define INIT_AUTOTEST_CHECKPT(sbootT) gU32ATCkPtTime = msAPI_Timer_GetTime0()-sbootT;
#define SET_AUTOTEST_CHECKPT() gU32ATCkPtTime = msAPI_Timer_GetTime0();

#define PRINT_AUTOTEST_TIME(ChkPtStr, u32Time) \
    printf("[AT][CK3][%s][%u]\n", ChkPtStr, u32Time);

#define PRINT_AUTOTEST_CHECKPT_TIME(ChkPtStr) \
    {\
        printf("[AT][CK3][%s][%u]\n", ChkPtStr, msAPI_Timer_DiffTimeFromNow(gU32ATCkPtTime)); \
    }
#else

#define SET_AUTOTEST_CHECKPT()
#define PRINT_AUTOTEST_TIME(ChkPtStr, u32Time)
#define PRINT_AUTOTEST_CHECKPT_TIME(ChkPtStr)
#endif	//(ENABLE_AUTOTEST || ENABLE_BOOTTIME)

INTERFACE U16 gU8Timer10ms;    //xzm @ 20171222
INTERFACE U8 gU8LastItem;
#if (ENABLE_CHCHANGETIME)
INTERFACE BOOLEAN gbKeyPress;
INTERFACE BOOLEAN gbReadyTimingMonitorFlag;
INTERFACE U32 gU32ChChangeTime;
#endif
#if (ENABLE_EAR_PHONE_VALUME_LINE)
INTERFACE U8 gU8EarPhoneChangeFlag; //add by gchen @ 20111021 //ear phone volume line
#endif


#if(ENABLE_SWITCH_CHANNEL_TIME)
    INTERFACE U32 gU32SwitchChannelTime;

    #define SwitchChannelTimeSetBegin() printf("[SwitchChannelTime] start >>\n");\
                                        gU32SwitchChannelTime = msAPI_Timer_GetTime0()
    #define SwitchChannelTimePrintf(x)  printf(x, msAPI_Timer_DiffTimeFromNow(gU32SwitchChannelTime))
#else
    #define SwitchChannelTimeSetBegin()
    #define SwitchChannelTimePrintf(x)
#endif


#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME || ENABLE_CHCHANGETIME )
INTERFACE U32 gU32TmpTime;
#endif

extern BOOL gbTVAutoScanChannelEnable;

//============================================================
#if (ENABLE_MSTV_UART_DEBUG)
INTERFACE U8 msAPI_UART_DecodeCommand( void );
INTERFACE void dbgVersionMessage(void);
void MCUPause(char* pcStr, int i);
#define CPU_PAUSE()     MCUPause(__FILE__,__LINE__)
//#define PRINT_CURRENT_LINE()    printf("\n %lu:%s", __LINE__, __FILE__);
#endif

#if ENABLE_DDCCI
INTERFACE void MDrv_DDC2BI_Init(void);
INTERFACE void MDrv_DDC2BI_CommandHandler(void);
#define  msAPI_DDC2BI_Init()                MDrv_DDC2BI_Init()
#define  msAPI_DDC2BI_CommandHandler()      MDrv_DDC2BI_CommandHandler()
#endif

INTERFACE void msAPI_InputSrcType_SetType(SCALER_WIN eWindow,EN_SYS_INPUT_SOURCE_TYPE enInpSrcType);
INTERFACE EN_SYS_INPUT_SOURCE_TYPE msAPI_InputSrcType_GetType(SCALER_WIN eWindow);
INTERFACE BOOLEAN msAPI_InputSrcType_InUsedType(SCALER_WIN eWindow,EN_SYS_INPUT_SOURCE_TYPE enInpSrcType);

#define IsHDMIInUse()               (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_HDMI))
#define IsVgaInUse()                (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_VGA))
#define IsYPbPrInUse()              (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_YPBPR))
#define IsAVInUse()                 (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_CVBS))
#define IsSVInUse()                 (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_SVIDEO))

#define IsATVInUse()                (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_ATV))

#if (ENABLE_FM_RADIO)
#define IsRADIOInUse()          (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_RADIO))
#endif

#if(GAME_ENABLE)
#define IsGameInUse()          (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_GAME))
#endif

//-------------------------------------------------------------------------------
#if ENABLE_S2
    #define IsS2InUse()         (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_S2))
#else
    #define IsS2InUse()         0
#endif

#if(ENABLE_S2)
    #define IsS2TVInUse()       (IsS2InUse())
#endif

#if(ENABLE_DVBT)
    #define IsDVBTInUse()       (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_DVBT) )
#else
    #define IsDVBTInUse()       0
#endif

#if( ENABLE_DVBC )
    #define IsDVBCInUse()       (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_DVBC))
#else
    #define IsDVBCInUse()       0
#endif

#if(ENABLE_ATSC)
    #define IsAtscInUse()       (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_ATSC) )
#else
    #define IsAtscInUse()       0
#endif

#if(ENABLE_DTMB)
    #define IsDTMBInUse()       (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_DTMB) )
#else
    #define IsDTMBInUse()       0
#endif

#if(ENABLE_ISDBT)
    #define IsISDBTInUse()      (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_ISDBT) )
#else
    #define IsISDBTInUse()      0
#endif


#define IsDVBInUse()            (IsDVBTInUse()||IsS2InUse()||IsDVBCInUse()||IsDTMBInUse()||IsISDBTInUse())

#if(ENABLE_DTV)
    extern BOOL msAPI_DTV_Comm_IsDTVInUse(void);
    #define IsDTVInUse()  msAPI_DTV_Comm_IsDTVInUse()
#else
    #define IsDTVInUse()    0
#endif


#if( ENABLE_ISDBT )
    BOOLEAN msAPI_SRC_IS_SBTVD_InUse(void);
#else
    #define msAPI_SRC_IS_SBTVD_InUse()  0
#endif


#if( ENABLE_ISDBT_AND_DVB )
    extern BOOL g_bIsSbtvdAppEn;
    #define IS_COUNTRY_USE_SBTVD()  (g_bIsSbtvdAppEn)
#elif( ENABLE_ISDBT )
    #define IS_COUNTRY_USE_SBTVD()  (1)
#else
    #define IS_COUNTRY_USE_SBTVD()  (0)
#endif

#define IS_SBTVD_APP            IS_COUNTRY_USE_SBTVD()

//-------------------------------------------------------------------------------

#if( ENABLE_ISDBT_AND_DVB )
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  (IS_SBTVD_APP ? UI_INPUT_SOURCE_ISDBT : UI_INPUT_SOURCE_DVBT)
#elif( ENABLE_ATSC )
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  UI_INPUT_SOURCE_ATSC
#elif( ENABLE_DVBT )
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  UI_INPUT_SOURCE_DVBT
#elif( ENABLE_DTMB )
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  UI_INPUT_SOURCE_DTMB
#elif( ENABLE_ISDBT )
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  UI_INPUT_SOURCE_ISDBT
#elif( ENABLE_DVBC)
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  UI_INPUT_SOURCE_DVBC
#elif( ENABLE_DVBS)
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  UI_INPUT_SOURCE_S2
#else
    #define SYS_DEFAULT_DTV_UI_INPUTSOURCE  UI_INPUT_SOURCE_ATV
#endif

#define DTV_DVBT_USE_UI_INPUTSOURCE     UI_INPUT_SOURCE_DVBT
#define DTV_DTMD_USE_UI_INPUTSOURCE     UI_INPUT_SOURCE_DTMB
#define DTV_DVBC_USE_UI_INPUTSOURCE     UI_INPUT_SOURCE_DVBC
#define DTV_DVBS_USE_UI_INPUTSOURCE     UI_INPUT_SOURCE_S2


//-------------------------------------------------------------------------------
#define IsScartInUse()              (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_SCART))
#define IsStorageInUse()            (msAPI_InputSrcType_InUsedType(MAIN_WINDOW,EN_SYS_INPUT_SOURCE_TYPE_STORAGE))

#if(ENABLE_S2)
#define IsAnyTVSourceInUse()        ( IsATVInUse() || IsDTVInUse() || IsS2InUse())
#else
#define IsAnyTVSourceInUse()        ( IsATVInUse() || IsDTVInUse() )
#endif
#define IsAnalogSourceInUse()       ( IsVgaInUse() || IsYPbPrInUse() || IsHDMIInUse() )
#define IsDigitalSourceInUse()      ( IsAVInUse() || IsSVInUse() || IsATVInUse() || IsScartInUse() )

//--------------------------------------------------------------------------------------------------------
#define IsSrcUseHDMIPort(win)       (msAPI_InputSrcType_InUsedType(win,EN_SYS_INPUT_SOURCE_TYPE_HDMI))

//--------------------------------------------------------------------------------------------------------
#if ((MARLON_SUPPORT_STR) &&(STR_ENABLE == ENABLE))
#define IsSTREnable()   MDrv_SYS_SupportSTR()
INTERFACE MS_BOOL  g_bPQTableSTRReset;
#endif
//--------------------------------------------------------------------------------------------------------

INTERFACE MS_SYS_INFO stSystemInfo[2];

#define SYS_INPUT_SOURCE_TYPE(WIN) stSystemInfo[WIN].enInputSourceType

//--------------------------------------------------------------------------------------------------------

#if(ENABLE_DECOMP7_USE_HK_MEMORY)
INTERFACE U8 g_au8Decomp7TmpBuf[0x4000];
#endif

//--------------------------------------------------------------------------------------------------------


#define ENABLE_SW_CRC32 1
#if(ENABLE_SW_CRC32)
U32 msAPI_CRC_Cal(const U8* pu8DataBuf, U32 u32DataSize);
#endif


#define ENABLE_SW_CRC16 1
#if( ENABLE_SW_CRC16 )
U16 msAPI_CRC16_Cal(const U8* pu8DataBuf, U32 u32DataSize);
#endif

#if(ENABLE_BIN_FILE_CRC)
U16 msAPI_CRC16_BinFile(const U8* pu8DataBuf, U32 u32DataSize); // For bin file
#endif

//--------------------------------------------------------------------------------------------------------
// U16 String API...
U16 Str16_StrLen(const U16 *pu16Str);
U16 Str16_StrCpy(U16 *pu16Dest, const U16 *pu16Src);
U16 Str16_StrNCpy(U16 *pu16Dest, const U16 *pu16Src, U16 u16MaxSize);
U16 Str16_StrU8toU16(U16* pu16StrDest, const U8* pu8StrSrc, U16 u16MaxSize);
void Str16_PrintStr(const U16* pu16UniStr);

//--------------------------------------------------------------------------------------------------------

#define MsMin(a,b)  (((a) < (b)) ? (a) : (b))
#define MsMax(a,b)  (((a) > (b)) ? (a) : (b))

//--------------------------------------------------------------------------------------------------------
U32 msOS_CacheToNonCache(U32 u32CacheAddr);

//******************************************************************************

#undef INTERFACE

//******************************************************************************

#endif /* MSAPI_GLOBAL_H */

