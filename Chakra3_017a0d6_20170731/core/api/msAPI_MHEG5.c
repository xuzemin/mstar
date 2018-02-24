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
/// @file msAPI_MHEG5.h
/// @brief API for MHEG-5
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#define _MSAPI_MHEG5_C_

/******************************************************************************/
/*                            Header Files                                    */
/* ****************************************************************************/
#include <string.h>
#include "Board.h"
#include "debug.h"

// Common Definition
#include "datatype.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "MApp_GlobalFunction.h"
#if MHEG5_ENABLE
#include "drvAUDIO.h"
#include "hwreg.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "apiAUDIO.h"

#include "Panel.h"
#include "apiPNL.h"

#include "msAPI_MMap.h"
#include "msAPI_MHEG5.h"

// [END]
#include "MApp_ChannelChange.h"
#include "MApp_Scaler.h"
#include "msAPI_MIU.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "msAPI_Timer.h"
#include "BinInfo.h"
#include "mapp_demux.h"
#include "mapp_si.h"
#include "MApp_MHEG5_Main.h"
#include "MApp_MVDMode.h"
#include "MApp_ChannelList.h"
#include "apiGOP.h"
#include "apiXC_Ace.h"
#include "apiGOP.h"
#if CIPLUS_MHEG
#include "msAPI_CI.h"
#endif
#include "msAPI_audio.h"
#define VIDEO_CROP      1
#if 0
#define M5DBG(x)    \
{   \
    printf("HK: ");  \
    x;  \
}

#define M5_TXRX_DBG(x)    x
#else
#define M5DBG(x)
#define M5_TXRX_DBG(x)
//    add for print some debug message for the
//    "theoretical value" position of iframe
#define ENABLE_IFRAME_OFFSET_DBG_INFO 0
#endif

#if VECTOR_FONT_ENABLE
#include "msAPI_MIU.h" //for msAPI_Font_MVF_EndGenerateBitmaps()
#endif //VECTOR_FONT_ENABLE

#include "msAPI_CPU.h"
#include "msAPI_MailBox.h"
#include "MApp_SignalMonitor.h"

#if (ENABLE_PVR == 1)
#include "MApp_TimeShift.h"
#include "MApp_Playback.h"
#endif
#define MHEG5_HK_VER 0
/// Mail Message Class Type Defines
typedef enum
{
    /// filter 16~31
    E_MHEG5_FILTER_NEXT_16  = 0,
    /// filter 0~15
    E_MHEG5_FILTER_FIRST_16 = 1
}MHEG_FILTER_TYPE;

typedef enum
{
    MHEG_KEY_UP         =   0x07,
    MHEG_KEY_DOWN       =   0x0B,
    MHEG_KEY_LEFT       =   0x0C,
    MHEG_KEY_RIGHT      =   0x0F,
    MHEG_KEY_0          =   0x10,
    MHEG_KEY_1          =   0x11,
    MHEG_KEY_2          =   0x12,
    MHEG_KEY_3          =   0x13,
    MHEG_KEY_4          =   0x14,
    MHEG_KEY_5          =   0x15,
    MHEG_KEY_6          =   0x16,
    MHEG_KEY_7          =   0x17,
    MHEG_KEY_8          =   0x18,
    MHEG_KEY_9          =   0x19,
    MHEG_KEY_SELECT     =   0x0D,
    MHEG_KEY_CANCEL     =   0x09,
    MHEG_KEY_BACK       =   0x0E,
    MHEG_KEY_RED        =   0x1C,
    MHEG_KEY_GREEN      =   0x1D,
    MHEG_KEY_YELLOW     =   0x33,
    MHEG_KEY_BLUE       =   0x34,
    MHEG_KEY_TEXT       =   0x35,
    MHEG_KEY_EPG        =   0x26,
    MHEG_KEY_INFO       =   0x1B,
#if (CIPLUS_MHEG_1_3 || INTERACTION_CHANNEL_STREAM)
    MHEG_KEY_Stop        =   0x71,
    MHEG_KEY_Play        =   0x61,
    MHEG_KEY_Pause       =   0x60,
    MHEG_KEY_SkipForward =   0x72,
    MHEG_KEY_SkipBack    =   0x73,
    MHEG_KEY_FastForward =   0x74,
    MHEG_KEY_Rewind      =   0x75,
     //MHEG_KEY_PLAYPAUSE   =   0x76
#endif
}MHEG_KEY;

// keyboard mapping
typedef struct
{
    unsigned int HouseKeeping_key;
    unsigned int CoProcessor_key;
} MHEGKeyMapEntry;


static MHEGKeyMapEntry mheg_keymap[] =
{
    { KEY_UP,       MHEG_KEY_UP },
    { KEY_DOWN,     MHEG_KEY_DOWN },
    { KEY_LEFT,     MHEG_KEY_LEFT },
    { KEY_RIGHT,    MHEG_KEY_RIGHT },
    { KEY_0,        MHEG_KEY_0 },
    { KEY_1,        MHEG_KEY_1 },
    { KEY_2,        MHEG_KEY_2 },
    { KEY_3,        MHEG_KEY_3 },
    { KEY_4,        MHEG_KEY_4 },
    { KEY_5,        MHEG_KEY_5 },
    { KEY_6,        MHEG_KEY_6 },
    { KEY_7,        MHEG_KEY_7 },
    { KEY_8,        MHEG_KEY_8 },
    { KEY_9,        MHEG_KEY_9 },
    { KEY_SELECT,   MHEG_KEY_SELECT },
    { KEY_EXIT,     MHEG_KEY_CANCEL },
    { KEY_RED,      MHEG_KEY_RED },
    { KEY_GREEN,    MHEG_KEY_GREEN },
    { KEY_YELLOW,   MHEG_KEY_YELLOW },
    { KEY_BLUE,     MHEG_KEY_BLUE },
    { KEY_TTX,      MHEG_KEY_TEXT },
    { KEY_BACK,     MHEG_KEY_BACK },
    { KEY_EPG,      MHEG_KEY_EPG },//for NZ
    { KEY_INFO,     MHEG_KEY_INFO },// for Australia
#if (CIPLUS_MHEG_1_3 || INTERACTION_CHANNEL_STREAM)
    { KEY_STOP,     MHEG_KEY_Stop },//for streaming in D-Book 6
    { KEY_PLAY,     MHEG_KEY_Play },//for streaming in D-Book 6
    { KEY_PAUSE,    MHEG_KEY_Pause },//for streaming in D-Book 6
    { KEY_NEXT,     MHEG_KEY_SkipForward },//for streaming in D-Book 6
    { KEY_PREVIOUS, MHEG_KEY_SkipBack },//for streaming in D-Book 6
    { KEY_FF,       MHEG_KEY_FastForward },//for streaming in D-Book 6
    { KEY_REWIND,   MHEG_KEY_Rewind },//for streaming in D-Book 6
    //{ KEY_PLAY_PAUSE,MHEG_KEY_PLAYPAUSE},
#endif
    { 0, 0 } // terminator
};

#ifdef MHEG5_BIG5_FONT_ENABLE
static U32 u32M5FontSize[4];
#endif

#define MHEG5_DEMUX_FILTER  E_MHEG5_FILTER_FIRST_16

#define MHEG5_QUARTER_VID_MAINTAIN_AR 0 //Open this flag need to modify AEON's code
#define MHEG_AUDIO_LOCALCOPY    1    // feed data to MAD buffer in housekeeping directly because housekeeping is aeon/mips, not slow 8051; also for single chip (linux solution)
extern VDEC_DispInfo gstVidStatus, gstPreVidStatus;
extern U8 MHEG5_GWINID;

static void msAPI_MHEG_AUD_StreamStoppedEvent(void);
static void _msAPI_MHEG5_SendMailboxMsg(U8 _class, U8 _index, MBX_MSG_Type _type, U8 _count,
                                        U8 _p1, U8 _p2, U8 _p3, U8 _p4, U8 _p5, U8 _p6, U8 _p7, U8 _p8, U8 _p9, U8 _p10);

 #define OBA_MSG_TYPE E_MBX_MSG_TYPE_INSTANT

#define M5_MAILBOX_SEND(_class,_index,_type,_count,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10) _msAPI_MHEG5_SendMailboxMsg((U8)_class,(U8)_index,(MBX_MSG_Type)_type,(U8)_count,(U8) _p1,(U8) _p2,(U8) _p3,(U8) _p4,(U8) _p5,(U8) _p6,(U8) _p7,(U8) _p8,(U8) _p9,(U8) _p10)

void M5API_MBX_Clean(void);

static void _M5API_MBX_RegisterMailBox(void);


//===========================================================================================

BOOL msAPI_MHEG_AUD_AEONFeedMAD(U32 addr, U16 number, U32 u32Index);
BOOL msAPI_MHEG_AUD_AEONClearBuffer(U32 addr, U16 number, U8 paddata);
void msAPI_MHEG5_VID_ResetScaleSize( void );
void msAPI_MHEG5_VID_ResetBoxSize( void );



//static  BOOLEAN BlackScreen_for_Ratio_Change = FALSE;
//static  BOOLEAN BlackScreen_for_WAM_Change = FALSE;
static    BOOLEAN bMHEG5Bin = FALSE;

static U32 u32DLABufferAddress = 0;
U8   u8MHEG5_DLA_FBID = 0;
static U8 GraphInfoRefreshType = 0;
static U16 _u16BaseYear = 1980;
static BOOLEAN  bGoBackMHEG5Process = false;

BOOLEAN bMHEG5Drawing = FALSE;
static BOOLEAN _bDsmccExit=TRUE;
//extern void msAPI_MHEG5_VID_GetARCInfo(U8 u8flag);

static void msAPI_MHEG_AUD_SetVolume(S32 dbLevel);

#if MHEG5_NDT
static BOOLEAN bWaitingNDTtrigger = false;
static BOOLEAN bNDTChannelChange = false;
#endif

/******************************************************************************/
/*              Local                                                         */
/* ****************************************************************************/

static MHEG5AudioFileParams Mheg5AudioFileParams =
    {
        .u32MHEGAudioAddr = 0,
        .u32MHEGAudioLoopCounts = 0,
        .u32MHEGAudioLength = 0,
        .u8MHEGAudioIsInfinite = 0,
        .u32MHEGAudioFileIndex = 0,
        .u8MHEG5AudioBeDecoded = 0
        };

static BOOLEAN bMHEG5Running = FALSE;
static U8 u8MHEG5_Key_RegisterGroup = 0;

MHEG5EventHandle _mheg5EventHandle =
{
        .DrawingCallback = NULL
};

#if CIPLUS_MHEG_1_3
static U8 u8SSM = 2;   // 0/1/2 - (default: 2)
static BOOL bSMG = false;

// return - 0: show subtitle; 1: show subtitle with mheg hidden; 2: show mheg
U8 msAPI_MHEG5_GoMHEGWhenSubtitleOn()
{
    if (msAPI_IsCIMHEGRun() == E_MHEG_CI_OFF)
    {
        return 0;   //  show subtitle
    }

    if (u8SSM == 0)
    {
         return 2;  //  show mheg
    }
    else if (u8SSM == 2)
    {
        // check the SMG parameter
        if (bSMG == false)
        {
            return 2;   //  show mheg
        }
        else
        {
            return 1;   //  show subtitle with hidden mheg
        }
    }
    else    //  u8SSM = 1
    {
        if ((stGenSetting.g_SysSetting.fEnableSubTitle == TRUE) && u8SubtitleMenuNum)
        {
            return 0;   //  show subtitle
        }
        else
        {
            return 2;  //  show mheg
        }
    }
}

void msAPI_MHEG5_SetCIPLUSSSM(U8 ssm)
{
    u8SSM =  ssm;
}

MS_U8 MHEG5_FBID = 0xFF;
MS_U8 VIRTUAL_FBID = 0xFF;
MS_U8 MHEG5_NEED_RESTORE = 0;
void msAPI_MHEG5_SetCIPLUSSMG(BOOL smg)
{
    BOOL prevSMG = bSMG;
    bSMG =  smg;
    if (u8SSM == 2)
    {
        if (prevSMG != bSMG)
        {
            if (smg == true)
            {
                MApi_GOP_GWIN_Enable(MHEG5_GWINID,FALSE);
                //  hide mheg plane
                MHEG5_FBID = MApi_GOP_GWIN_GetFBfromGWIN(MHEG5_GWINID);
                MApi_GOP_GWIN_GetFBfromGWIN(MHEG5_GWINID);
                if(VIRTUAL_FBID == 0xFF)
                {
                    VIRTUAL_FBID = MApi_GOP_GWIN_GetFreeFBID();
                    MApi_GOP_GWIN_CreateFB(VIRTUAL_FBID,0,0,20,20,MHEG_GE_FMT);
                }
                MApi_GOP_GWIN_MapFB2Win(VIRTUAL_FBID,MHEG5_GWINID);
                MApi_GOP_GWIN_DeleteWin(MHEG5_GWINID);
            }
            else
            {
                MHEG5_NEED_RESTORE = 1;
                //MApi_GOP_GWIN_MapFB2Win(MHEG5_FBID, MHEG5_GWINID);
                //1254033: [Marlon_120B][CI+1.3] Test 4.2.3 Press the Yellow key , MHEG graphics do not appear in step 45
                MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
                MApi_GOP_GWIN_SetGOPDst(MHEG5_GOP,E_GOP_DST_OP0);
                MApi_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, 0,0, MHEG_XRES_OS, MHEG_YRES_OS);
                MApi_GOP_GWIN_Set_HSCALE(TRUE, MHEG_XRES_OS, g_IPanel.Width());
                MApi_GOP_GWIN_Set_VSCALE(TRUE, MHEG_YRES_OS, g_IPanel.Height());
                MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0,FALSE);
                if(MApi_GOP_GWIN_IsFBExist(MHEG5_FBID))
                {
                    MApi_GOP_GWIN_CreateWin_Assign_FB(MHEG5_GOP,MHEG5_FBID,0,0);
                    MApi_GOP_GWIN_Enable(MHEG5_GWINID,TRUE);
                }
                else
                {
                    MHEG5_FBID = 0xFF;
                }


            }
            //printf("mheg plane\n");
        }
    }
}
void msAPI_MHEG5_RESTORE(void)
{
    if(MHEG5_NEED_RESTORE == 1)
    {
        //  show mheg plane
        MApi_GOP_GWIN_DeleteWin(MHEG5_GWINID);
        MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
        MApi_GOP_GWIN_SetGOPDst(MHEG5_GOP,E_GOP_DST_OP0);
        MApi_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, 0,0, MHEG_XRES_OS, MHEG_YRES_OS);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, MHEG_XRES_OS, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, MHEG_YRES_OS, g_IPanel.Height());
        MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0,FALSE);
        if(MApi_GOP_GWIN_IsFBExist(MHEG5_FBID))
        {
            MApi_GOP_GWIN_CreateWin_Assign_FB(MHEG5_GOP,MHEG5_FBID,0,0);
            MApi_GOP_GWIN_Enable(MHEG5_GWINID,TRUE);
        }
        else
        {
            MHEG5_FBID = 0xFF;
        }
        VIRTUAL_FBID = 0xFF;
        MHEG5_NEED_RESTORE = 0;
    }
    else
    {
       #if (UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
        MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, 1920, 1080);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, 1920, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 1080, g_IPanel.Height());
        MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
       #else
        MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, 1366, 768);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, 1366, g_IPanel.Width());
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, g_IPanel.Height());
        MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
       #endif
    }
}
#endif

#if MHEG5_WITH_SUBTITLE
static U8 u8MHEGSubtitleControl = 1;

U8 msAPI_MHEG5_GetSubtitleMode()
{
    if (MApp_MHEG5_CheckGoMHEG5Process() == 0)
    {
        return 1;   // show subtitle
    }

    // i-frame or SSM == 0 or VideoOffset!=0 or Scale!=full, return 0 to make subtitle exit
    if (g_MHEG5Video.bIFrame==1 || u8MHEGSubtitleControl == 0 || (msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction)==0))
    {
        return 0;   // do not show subtitle
    }
    else
    {
        return 1;   // show subtitle
    }
}

void msAPI_MHEG5_SetSubtitleMode(U8 subtitleControl)
{
    u8MHEGSubtitleControl = subtitleControl;
}

#endif


void msAPI_MHEG5_SetGoBackMHEG5(BOOLEAN bGoBack)
{
    bGoBackMHEG5Process = bGoBack;
}

BOOLEAN msAPI_MHEG5_checkGoBackMHEG5()
{
    return bGoBackMHEG5Process;
}

#if MHEG5_NDT
void msAPI_MHEG5_WaitNDTPid(BOOLEAN bSetNDT)
{
    bWaitingNDTtrigger = bSetNDT;
}

BOOLEAN msAPI_MHEG5_BeWaitingNDTPid()
{
    return bWaitingNDTtrigger;
}

void msAPI_MHEG5_SetNDTChannelChange(BOOLEAN bChannelChange)
{
    bNDTChannelChange = bChannelChange;
}

BOOLEAN msAPI_MHEG5_GetNDTChannelChange()
{
    return bNDTChannelChange;
}

void msAPI_MHEG5_TriggerNDT()
{
    if (msAPI_MHEG5_BeWaitingNDTPid()==false)
        return;

    if(msAPI_MHEG5_GetBinStatus() == FALSE)
    {
        ASSERT(0);
        return;
    }

    printf("trigger ndt dsmcc....\n");

    U16 u16PmtPid = MApp_SI_Get_PMT_PID();

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_TSP
    /*Index*/           ,MB_TSP_CMD_NDT_PID
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x0A

    /*p1*/              ,(U8)((u16PmtPid & 0xFF00) >> 8)
    /*p2*/              ,(U8)(u16PmtPid & 0x00FF)
    /*p3*/              ,(U8)((g_u16CurrentServiceID & 0xFF00) >> 8)
    /*p4*/              ,(U8)(g_u16CurrentServiceID & 0x00FF)
    /*p5*/              ,(U8)((g_wCurrentTS_ID & 0xFF00) >> 8)
    /*p6*/              ,(U8)(g_wCurrentTS_ID & 0x00FF)
    /*p7*/              ,(U8)0x01
    /*p8*/              ,(U8)((g_wCurrent_ONID & 0xFF00) >> 8)
    /*p9*/              ,(U8)(g_wCurrent_ONID & 0x00FF)
    /*p10*/             ,MHEG5_DEMUX_FILTER);// 1 : temp disable inverse filter


    msAPI_MHEG5_WaitNDTPid(false);
}
#endif

/******************************************************************************/
/// @internal
///- This API will send MSG to MHEG5 engin
/// @param msg parameter.
/* ****************************************************************************/
static void _msAPI_MHEG5_SendMailboxMsg(U8 _class, U8 _index, MBX_MSG_Type _type, U8 _count,
                                        U8 _p1, U8 _p2, U8 _p3, U8 _p4, U8 _p5, U8 _p6, U8 _p7, U8 _p8, U8 _p9, U8 _p10)
{
    MBX_Msg m5_mbxMsg;
    MBX_Result mbxResult;
    U32 u32MBXTimeOut = 0;
    U8 count = 0;
    if (msAPI_MHEG5_GetBinStatus() == FALSE)
    {
        return;
    }

    M5DBG(printf("_msAPI_MHEG5_SendMailboxMsg \n"));

    m5_mbxMsg.u8MsgClass            = _class;
    m5_mbxMsg.u8Index               = _index;
    m5_mbxMsg.u8ParameterCount      = _count;
    m5_mbxMsg.eMsgType              = _type;
    m5_mbxMsg.u8Parameters[0]       = _p1;
    m5_mbxMsg.u8Parameters[1]       = _p2;
    m5_mbxMsg.u8Parameters[2]       = _p3;
    m5_mbxMsg.u8Parameters[3]       = _p4;
    m5_mbxMsg.u8Parameters[4]       = _p5;
    m5_mbxMsg.u8Parameters[5]       = _p6;
    m5_mbxMsg.u8Parameters[6]       = _p7;
    m5_mbxMsg.u8Parameters[7]       = _p8;
    m5_mbxMsg.u8Parameters[8]       = _p9;
    m5_mbxMsg.u8Parameters[9]       = _p10;

    u32MBXTimeOut = MsOS_GetSystemTime();

    do
    {
        mbxResult = MSApi_MBX_SendMsg(&m5_mbxMsg);
        switch(mbxResult)
        {
            case E_MBX_ERR_PEER_CPU_BUSY:
            case E_MBX_ERR_PEER_CPU_NOTREADY:
            case E_MBX_ERR_PEER_CPU_NOT_ALIVE:
                //Error Handling here...
                break;
            case E_MBX_ERR_PEER_CPU_OVERFLOW:
                PRINT_CURRENT_LINE();
                MsOS_DelayTask(1);
                break;
            default:
                break;
        }

        if (mbxResult != E_MBX_SUCCESS)
        {
            if (MsOS_Timer_DiffTimeFromNow(u32MBXTimeOut) > 5000)
            {
                printf("_msAPIMHEG5_SendMailboxMsg TimeOut:\n");
                switch(mbxResult)
                {
                    case E_MBX_ERR_NOT_INITIALIZED:
                       printf("Error %d: Not Initialized\n", mbxResult);
                        break;

                    case E_MBX_ERR_NO_MORE_MEMORY:
                        printf("Error %d: No more Memory, Queue Memory Issue\n", mbxResult);
                        break;

                    case E_MBX_ERR_SLOT_BUSY:
                        printf("Error %d: class has been used by other APP\n", mbxResult);
                        break;

                    case E_MBX_ERR_SLOT_AREADY_OPENNED:
                        printf("Error %d: class has been openned by this APP, you do not need to open it again\n", mbxResult);
                        break;

                    case E_MBX_ERR_SLOT_NOT_OPENNED:
                        printf("Error %d: class not registered yet\n", mbxResult);
                        break;

                    case E_MBX_ERR_INVALID_CPU_ID:
                        printf("Error %d: unknow cpu id\n", mbxResult);
                        break;

                    case E_MBX_ERR_INVALID_PARAM:
                        printf("Error %d: invalid parameter\n", mbxResult);
                        break;

                    case E_MBX_ERR_PEER_CPU_BUSY:
                       printf("Error %d: peer cpu is peek Mail from Hardware, you can not send mail now\n", mbxResult);
                        break;

                    case E_MBX_ERR_PEER_CPU_NOT_ALIVE:
                        printf("Error %d: peer cpu do not alive, Mail never peek out, Need check peer cpu is alive or not\n", mbxResult);
                        break;

                    case E_MBX_ERR_PEER_CPU_NOTREADY:
                        printf("Error %d: peer cpu not initialized yet, not ready to receive mail message\n", mbxResult);
                        break;

                    case E_MBX_ERR_PEER_CPU_OVERFLOW:
                        printf("Error %d: peer cpu the dedicated class Overflow!\n", mbxResult);
                        break;

                    case E_MBX_ERR_MSG_ALREADY_FETCHED:
                        printf("Error %d: the mail message has been fetched yet, there has no message in hardware\n", mbxResult);
                        break;

                    case E_MBX_ERR_TIME_OUT:
                        printf("Error %d: time out with dedicated request\n", mbxResult);
                        break;

                    case E_MBX_ERR_NO_MORE_MSG:
                        printf("Error %d: no mail message in message queue\n", mbxResult);
                        break;

                    case E_MBX_ERR_HAS_MSG_PENDING:
                        printf("Error %d: has mail message in queue when un-register mail class or DeInit MailBox Driver\n", mbxResult);
                        break;

                    case E_MBX_ERR_NOT_IMPLEMENTED:
                        printf("Error %d: not implemente yet for request\n", mbxResult);
                        break;

                    case E_MBX_UNKNOW_ERROR:
                        printf("Error %d: unknow error, like system error\n", mbxResult);
                        break;

                    default:
                        printf("Error %d: undefined error\n", mbxResult);
                        break;
                }
                MS_DEBUG_MSG(printf("u8MsgClass       = %d\n", m5_mbxMsg.u8MsgClass));
                MS_DEBUG_MSG(printf("u8Index          = %d\n", m5_mbxMsg.u8Index));
                MS_DEBUG_MSG(printf("u8ParameterCount = %d\n", m5_mbxMsg.u8ParameterCount));
                MS_DEBUG_MSG(printf("eMsgType         = %d\n", m5_mbxMsg.eMsgType));
                MS_DEBUG_MSG(printf("u8Parameters[0]  = 0x%02X\n", m5_mbxMsg.u8Parameters[0]));
                MS_DEBUG_MSG(printf("u8Parameters[1]  = 0x%02X\n", m5_mbxMsg.u8Parameters[1]));
                MS_DEBUG_MSG(printf("u8Parameters[2]  = 0x%02X\n", m5_mbxMsg.u8Parameters[2]));
                MS_DEBUG_MSG(printf("u8Parameters[3]  = 0x%02X\n", m5_mbxMsg.u8Parameters[3]));
                MS_DEBUG_MSG(printf("u8Parameters[4]  = 0x%02X\n", m5_mbxMsg.u8Parameters[4]));
                MS_DEBUG_MSG(printf("u8Parameters[5]  = 0x%02X\n", m5_mbxMsg.u8Parameters[5]));
                MS_DEBUG_MSG(printf("u8Parameters[6]  = 0x%02X\n", m5_mbxMsg.u8Parameters[6]));
                MS_DEBUG_MSG(printf("u8Parameters[7]  = 0x%02X\n", m5_mbxMsg.u8Parameters[7]));
                MS_DEBUG_MSG(printf("u8Parameters[8]  = 0x%02X\n", m5_mbxMsg.u8Parameters[8]));
                MS_DEBUG_MSG(printf("u8Parameters[9]  = 0x%02X\n", m5_mbxMsg.u8Parameters[9]));
                u32MBXTimeOut = MsOS_GetSystemTime();
            }
        }
    }while(((++count)<2)&&(E_MBX_SUCCESS != mbxResult));
}

/******************************************************************************/
/// @internal
///- API for setting current MHEG-5 application key group
/// @param *u8RegisterGroup \b IN: current MHEG application key group
/******************************************************************************/
void msAPI_MHEG5_SetKeyRegisterGroup(U8 u8RegisterGroup)
{
#if CIMHEG_DBG
    printf("KeyRegisterGroup: %d\n", u8RegisterGroup);
#endif
    u8MHEG5_Key_RegisterGroup = u8RegisterGroup;
}

/******************************************************************************/
///- This API will get MHEG-5 application key group
/// @return U8: current key group in MHEG-5
/*****************************************************************************/
U8 msAPI_MHEG5_GetKeyRegisterGroup(void)
{
    return u8MHEG5_Key_RegisterGroup;
}


/******************************************************************************/
///- This function will set MHEG-5 Status
/// @param bRun \b IN:
///- TRUE: MHEG5 is enable
///- FALSE: MHEG5 is disable
/* ****************************************************************************/
void msAPI_MHEG5_SetRun(BOOLEAN bRun)
{
    bMHEG5Running = bRun;
}

/******************************************************************************/
///- This API will get MHEG-5 running Status
/// @return BOOLEAN:
///- TRUE: MHEG5 is running
///- FALSE: MHEG5 is not running
/* ****************************************************************************/
BOOLEAN msAPI_MHEG5_IsRunning(void)
{
    return bMHEG5Running;
}

/******************************************************************************/
///- This function will get MAD current command for MHEG-5 using
/// @return BYTE: MAD current command
/* ****************************************************************************/
AU_DVB_DECCMD msAPI_MHEG_AUD_GetMadCmd()
{
    // S3P, S4L -- only one DSP -- MDrv_AUDIO_ReadByte()

    // in S4 and later project, there are 2 DSPs inside.
    // one is for decoder and the other is for sound effect
    // decoder -- MDrv_Au"Dec"ReadByte
    // soundEffect -- MDrv_Au"Se"ReadByte

    return (MApi_AUDIO_GetCommand(DVB_Audio_Decoder1));

}

/******************************************************************************/
///- This function will set MAD Interrupt flag for MHEG-5 Audio
/* ****************************************************************************/
void msAPI_MHEG_AUD_SetMADIntFlag(BOOLEAN bSet)
{
    MDrv_AUDIO_SetPlayFileFlag(DSP_DEC, bSet);
}

/******************************************************************************/
///- This function will get MAD Interrupt flag for MHEG-5 Audio
///@return U8: MAD interrupt flag
/* ****************************************************************************/
U8 msAPI_MHEG_AUD_GetMADIntFlag()
{
    return (MDrv_AUDIO_GetPlayFileFlag(DSP_DEC));
}

/******************************************************************************/
///- MHEG-5 Audio clear MAD interrupt flag
/* ****************************************************************************/
void msAPI_MHEG_AUD_ClearMADIntFlag()
{
    msAPI_MHEG_AUD_SetMADIntFlag(FALSE);
}

/******************************************************************************/
///- MHEG5 API for stopping audio file playback
/******************************************************************************/
void msAPI_MHEG_AUD_Stop()
{
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);//MDrv_MAD_SetDecCmd(AU_DVB_DECCMD_STOP);
}


/******************************************************************************/
///- This API will change Audio PID for MHEG-5 Audio.
/// @param s32AudioPID \b IN: Audio PID to change.
/// @param wAudType \b IN: Audio Type (AC-3, MPEG, or ... )
/* ****************************************************************************/
void msAPI_MHEG_AUD_ChangeAudPid(S32 s32AudioPID, WORD wAudType)
{
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    //MDrv_MAD_SetDecCmd(AU_DVB_DECCMD_STOP);
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
    msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AUDIO_FID));
    msAPI_DMX_StartFilter(s32AudioPID, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID));
    /* set decoder system and reload firmware code */
    DEBUG_AU_LOAD_CODE( printf("wAudType=%u\n", wAudType ); );
    MApi_AUDIO_SetSystem((En_DVB_decSystemType)wAudType);
    if( wAudType == E_AUDIOSTREAM_AC3 || wAudType == E_AUDIOSTREAM_AC3P)
    {
        MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DrcMode, RF_MODE, 0);    //RF Mod
        MApi_AUDIO_SetAC3Info(Audio_AC3_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
        }
        else
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
        }
    }
    else if( wAudType == E_AUDIOSTREAM_AAC || wAudType == E_AUDIOSTREAM_MPEG4)
    {
        MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DrcMode, RF_MODE, 0);    //RF Mod
        MApi_AUDIO_SetAACInfo(Audio_AAC_infoType_DownmixMode, DOLBY_DOWNMIX_MODE_LTRT, 0);
        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
        }
        else
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
        }
    }
    else
    {
        MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
    }

    MApi_AUDIO_DTV_HDMI_CFG(FALSE);  // DTV mod set False
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
}

// This flag is for HW AUD patch, and will be fixed the MHEG5 2 stop events issue
static U8 gu8audstopevent = FALSE;

/******************************************************************************/
///- This API will play MHEG5 Audio File.
/*****************************************************************************/
void msAPI_MHEG_AUD_PlayMHEG5AudioFile(void)
{
    static U32 tag = 1;
#if (MHEG_AUDIO_LOCALCOPY==0)
    U16 retry_count = 0;
#endif
    U32 writeAddress = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_BufferAddr);
    U32 writeNumber = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_BufferSize);
    U32 nWritten = 0;
    static U32 timer = 0; //mantis 0370672

    if(msAPI_Timer_DiffTime(timer, msAPI_Timer_GetTime0())<20)
    {
       return;
    }
    timer= msAPI_Timer_GetTime0();

    // unmute directly to avoid bugs of signal monitor
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    if (msAPI_MHEG_AUD_GetMadCmd()==AU_DVB_DECCMD_PLAYFILE && msAPI_MHEG_AUD_GetMADIntFlag())
    {
        // clear MAD interrupt flag
        msAPI_MHEG_AUD_ClearMADIntFlag();
    }
    else
    {
        return;
    }

    // make sure audio has been decoded
    //if (Mheg5AudioFileParams.u8MHEG5AudioBeDecoded == 0 && MDrv_MAD_MPEG_GetframeNum()!=0)
    if (Mheg5AudioFileParams.u8MHEG5AudioBeDecoded == 0 && MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_FrameNum)!=0)
    {
        Mheg5AudioFileParams.u8MHEG5AudioBeDecoded= 1;
    }

    // limited loops counts & finish the final loop
    if ((!Mheg5AudioFileParams.u8MHEGAudioIsInfinite) &&
        (Mheg5AudioFileParams.u32MHEGAudioLoopCounts==0))
    {
        // end of play -- all audio data are in MAD buffer
        if (Mheg5AudioFileParams.u8MHEG5AudioBeDecoded &&
            (MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_pcmBuf_currLevel) == 0))
        {
            // the data in MAD buffer is empty. it is end of play.
            if(gu8audstopevent == FALSE)
            {
                msAPI_MHEG_AUD_StreamStoppedEvent();
                gu8audstopevent = TRUE;
            }
            Mheg5AudioFileParams.u32MHEGAudioFileIndex = 0;
            //printf("stop\n");
            tag = 1;
            return;
        }

        gu8audstopevent = FALSE;

        // interrupt MAD
        msAPI_MHEG_AUD_IntMAD(0x00E0);
        msAPI_MHEG_AUD_IntMAD(0x00E0);
        return;
    }


    while ( nWritten < writeNumber)
    {
        U32 u32Size = 0;
        if ((Mheg5AudioFileParams.u32MHEGAudioLength-Mheg5AudioFileParams.u32MHEGAudioFileIndex) < (writeNumber-nWritten))
        {
            u32Size = Mheg5AudioFileParams.u32MHEGAudioLength-Mheg5AudioFileParams.u32MHEGAudioFileIndex;
        }
        else
        {
            u32Size = writeNumber-nWritten;
        }

        if (u32Size+nWritten > writeNumber)
        {
            // this only occurs when the buffer is smaller than the size we want to feed
            u32Size = writeNumber-nWritten;
        }
    #if MHEG_AUDIO_LOCALCOPY
        msAPI_MIU_Copy(Mheg5AudioFileParams.u32MHEGAudioAddr+Mheg5AudioFileParams.u32MHEGAudioFileIndex,
            (msAPI_AUD_GetDspMadBaseAddr(DSP_DEC))+writeAddress+nWritten, u32Size, MIU_SDRAM2SDRAM);
    #else
        msAPI_MHEG_AUD_AEONFeedMAD(writeAddress+nWritten, u32Size, Mheg5AudioFileParams.u32MHEGAudioFileIndex);
        // make sure aeon has feed data to MAD buffer
        while (!(MDrv_ReadByte(MB_51_REG_Status_0) & 0x02))
        {
            retry_count++;
            if (retry_count>10000)
                break;
        }

        {
            U8 u8ReadByte;
            u8ReadByte = MDrv_ReadByte(MB_51_REG_Status_0);
            // clear the control bit
            MDrv_WriteByte(MB_51_REG_Status_0, u8ReadByte & ~0x02);
        }
        retry_count = 0;
    #endif
        nWritten += u32Size;
        Mheg5AudioFileParams.u32MHEGAudioFileIndex += u32Size;

        if (Mheg5AudioFileParams.u32MHEGAudioFileIndex == Mheg5AudioFileParams.u32MHEGAudioLength)
        {
            if (!Mheg5AudioFileParams.u8MHEGAudioIsInfinite)
            {
                --Mheg5AudioFileParams.u32MHEGAudioLoopCounts;
            }
            Mheg5AudioFileParams.u32MHEGAudioFileIndex = 0;
        }

        if (!Mheg5AudioFileParams.u8MHEGAudioIsInfinite && Mheg5AudioFileParams.u32MHEGAudioLoopCounts==0)
        {
            // clear the remaining buffer as 0
        #if MHEG_AUDIO_LOCALCOPY
            memset((void*)_PA2VA((msAPI_AUD_GetDspMadBaseAddr(DSP_DEC))+writeAddress+nWritten), 0, writeNumber-nWritten);
        #else
            msAPI_MHEG_AUD_AEONClearBuffer(writeAddress+nWritten, writeNumber-nWritten, 0);
        #endif
            //printf("ok\n");
            break;
        }
    }

    MApi_AUDIO_MM_SetInput(DVB_Audio_Decoder1,tag++);

    // reset tag
    if ((tag%65535)==0)
        tag = 1;

    // interrupt MAD
    msAPI_MHEG_AUD_IntMAD(0x00E0);
    msAPI_MHEG_AUD_IntMAD(0x00E0);
}

/******************************************************************************/
///- This API will set allocate frame buffer for DynamicLineArt usage in  MHEG-5
/// @return U32 : address of framebuffer for DynamicLineArt
/******************************************************************************/
U32 msAPI_MHEG5_AllocateDLAFB()
{
    U32 retAddr = 0;
    if ((retAddr = msAPI_MHEG5_GetDLAFBAddress())==0)    // i.e. we have not allocate DLA buffer, so we need to allocate it.
    {
        GOP_GwinFBAttr dlafbAttr;

        memset(&dlafbAttr, 0, sizeof(GOP_GwinFBAttr));

        msAPI_MHEG5_CreateFrameBuffer(MHEG_GE_FMT, &dlafbAttr, MHEG_XRES_COORD, MHEG_YRES_COORD, &u32DLABufferAddress, &u8MHEG5_DLA_FBID);

        // CI+ MHEG also use the DLA buffer before entering normal MHEG code flow.
        // so, need to pass the info when the DLA buffer is allocated by CI+ MHEG.
        msAPI_MHEG5_SendDLAInfo(dlafbAttr.addr);

        retAddr = dlafbAttr.addr;
    }

    //printf("DLA addr %lu\n", retAddr);
    return retAddr;
}

/******************************************************************************/
/// This API will reset scale width/height in video action for MHEG if it is invalid format
/// @param pstMHEG5VideoAction \b IN: pointer to video action in MHEG
/******************************************************************************/
static void _msAPI_MHEG5_VID_CheckAndResetScaleSize( MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction )
{

    if ( (pstMHEG5VideoAction->u16Scale_Width == 0) || (pstMHEG5VideoAction->u16Scale_Height == 0) )
    {

        pstMHEG5VideoAction->u16Scale_Width = MHEG_XRES_COORD;
        pstMHEG5VideoAction->u16Scale_Height = MHEG_YRES_COORD;

    }
}

/******************************************************************************/
/// This API will reset box width/height in video action for MHEG if it is invalid format
/// @param pstMHEG5VideoAction \b IN: pointer to video action in MHEG
/******************************************************************************/
static void _msAPI_MHEG5_VID_CheckAndResetBoxSize( MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction )
{

    if ( !(g_MHEG5Video.u8VideoFlag & EVER_SET_VIDEO_BOX_SIZE) )
    {
        pstMHEG5VideoAction->u16BoxSize_X = pstMHEG5VideoAction->u16Scale_Width;
        pstMHEG5VideoAction->u16BoxSize_Y = pstMHEG5VideoAction->u16Scale_Height;
    }
    else
    {
        if ( pstMHEG5VideoAction->u16BoxSize_X > pstMHEG5VideoAction->u16Scale_Width )
            pstMHEG5VideoAction->u16BoxSize_X = pstMHEG5VideoAction->u16Scale_Width;


        if ( pstMHEG5VideoAction->u16BoxSize_Y > pstMHEG5VideoAction->u16Scale_Height )
            pstMHEG5VideoAction->u16BoxSize_Y = pstMHEG5VideoAction->u16Scale_Height;
    }
}

/******************************************************************************/
/// This API will adjust the CentreCutOut position in for MHEG
/// @param pstSrcWin \b IN: pointer to window source position in MHEG
/******************************************************************************/
static void _msAPI_MHEG5_VID_AdjustCentreCutOut(MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction)//, MS_WINDOW_TYPE *pstDstWin)
{
    pstMHEG5VideoAction->s16VideoOffset_X -= (pstMHEG5VideoAction->u16Scale_Width / 6);

    pstMHEG5VideoAction->u16Scale_Width = pstMHEG5VideoAction->u16Scale_Width * 4 /3;
}

/******************************************************************************/
/// This API will adjust the LetterBox position for MHEG
/// @param pstDstWin \b IN: pointer to window position in MHEG
/******************************************************************************/
static void _msAPI_MHEG5_VID_AdjustLetterBox(MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction)//MS_WINDOW_TYPE *pstSrcWin, MS_WINDOW_TYPE *pstDstWin)
{
    pstMHEG5VideoAction->s16VideoOffset_Y = pstMHEG5VideoAction->u16Scale_Height / 8;
    pstMHEG5VideoAction->u16Scale_Height= pstMHEG5VideoAction->u16Scale_Height * 3 /4;
}


/******************************************************************************/
/// This API will adjust the position depending on the Scene Aspect Ratio in MHEG-5
/// @param pstSrcWin \b IN: pointer to src-window position in MHEG
/// @param pstDstWin \b IN: pointer to dst-window position in MHEG
/// @return TRUE if there is Scene Aspect Ratio in MHEG
/******************************************************************************/
static BOOLEAN _msAPI_MHEG5_VID_AdjustSceneAR(MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction)
{
    BOOLEAN ret=FALSE;
    BOOLEAN bIsWide = TRUE;

    g_MHEG5Video.eWAM = EN_MHEG5_WAM_Num;

    //printf("1.msAPI_MHEG5_VID_CalcSceneAR:%bx,%bx\n",g_MHEG5Video.eSceneAspectRatio,g_MHEG5Video.eWAM);
    //printf("g_MHEG5Video.u8VideoFlag2:%bx\n",g_MHEG5Video.u8VideoFlag2);

    // here,the gstVidStatus.u8AspectRate is ready from MVD decode Video
    if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)  //H264 video.
    {
        msAPI_VID_AVCH264IsAspectRatioWide(&gstVidStatus, &bIsWide);
    }
    else // MVD video.
    {
        if(gstVidStatus.u8AspectRate != MVD_ASP_16TO9)
        {
            bIsWide = FALSE;
        }
    }

    //If not wide.
    if  ( bIsWide == FALSE)
    {
        g_MHEG5Video.eWAM = EN_MHEG5_WAM_None;
    }

    if (g_MHEG5Video.eWAM != EN_MHEG5_WAM_None)
    {
        g_MHEG5Video.Pre_eWAM =  g_MHEG5Video.eWAM;


        if (g_MHEG5Video.u8VideoFlag2 == SCENE_CCO)
        {
           g_MHEG5Video.eWAM = EN_MHEG5_WAM_Centre_Cut_Out;
        }
        else if (g_MHEG5Video.u8VideoFlag2 == SCENE_LB)
        {
           g_MHEG5Video.eWAM = EN_MHEG5_WAM_LetterBox;
        }
    }

    //printf("2.msAPI_MHEG5_VID_CalcSceneAspectRatio:%bx,%bx\n",g_MHEG5Video.eSceneAspectRatio,g_MHEG5Video.eWAM);
    // Scene Aspect Ratio
    if ( g_MHEG5Video.eSceneAspectRatio == SCENE_AR_4_3 ) //EN_MHEG5_SceneAspectRatio_4X3 )
    {
        // Panel Aspect Ratio
        if ( g_MHEG5Video.eWAM == EN_MHEG5_WAM_Centre_Cut_Out )
        {
            _msAPI_MHEG5_VID_AdjustCentreCutOut(pstMHEG5VideoAction);
            ret = TRUE;
        }
        else if ( ( g_MHEG5Video.eWAM == EN_MHEG5_WAM_LetterBox ) )
        {
            _msAPI_MHEG5_VID_AdjustLetterBox(pstMHEG5VideoAction);
            ret = TRUE;
        }
    }
    return ret;
}

#if HD_MHEG5
static void _M5Action_SD2HD(MS_MHEG5_VIDEO_ACTION *Act)
{
    if(Act->s16Position_X >= 0x00)
    {
        Act->s16Position_X   = (U16)((double )Act->s16Position_X * MHEG_XRES / MHEG_XRES_COORD + 0.5);
    }
    else
    {
        Act->s16Position_X   = (S16)((double )Act->s16Position_X * MHEG_XRES / MHEG_XRES_COORD - 0.5);
    }

    if(Act->s16Position_Y >= 0x00)
    {
        Act->s16Position_Y   = (U16)((double )Act->s16Position_Y * MHEG_YRES / MHEG_YRES_COORD + 0.5);
    }
    else
    {
        Act->s16Position_Y   = (S16)((double )Act->s16Position_Y * MHEG_YRES / MHEG_YRES_COORD - 0.5);
    }

    if(Act->s16VideoOffset_X >= 0x00)
    {
        Act->s16VideoOffset_X   = (U16)((double )Act->s16VideoOffset_X * MHEG_XRES / MHEG_XRES_COORD + 0.5);
    }
    else
    {
        Act->s16VideoOffset_X   = (S16)((double )Act->s16VideoOffset_X * MHEG_XRES / MHEG_XRES_COORD - 0.5);
    }

    if(Act->s16VideoOffset_Y >= 0x00)
    {
        Act->s16VideoOffset_Y   = (U16)((double )Act->s16VideoOffset_Y * MHEG_YRES / MHEG_YRES_COORD + 0.5);
    }
    else
    {
        Act->s16VideoOffset_Y   = (S16)((double )Act->s16VideoOffset_Y * MHEG_YRES / MHEG_YRES_COORD - 0.5);
    }

    Act->u16BoxSize_X       = (U16)((double )Act->u16BoxSize_X     * MHEG_XRES / MHEG_XRES_COORD + 0.5);
    Act->u16BoxSize_Y       = (U16)((double )Act->u16BoxSize_Y     * MHEG_YRES / MHEG_YRES_COORD + 0.5);
    Act->u16Scale_Width     = (U16)((double )Act->u16Scale_Width   * MHEG_XRES / MHEG_XRES_COORD + 0.5);
    Act->u16Scale_Height    = (U16)((double )Act->u16Scale_Height  * MHEG_YRES / MHEG_YRES_COORD + 0.5);
}

#if 0
static void _M5Action_HD2SD(MS_MHEG5_VIDEO_ACTION *Act)
{
    Act->s16Position_X      = Act->s16Position_X    * MHEG_XRES_COORD / MHEG_XRES;
    Act->s16Position_Y      = Act->s16Position_Y    * MHEG_YRES_COORD / MHEG_YRES;
    Act->s16VideoOffset_X   = Act->s16VideoOffset_X * MHEG_XRES_COORD / MHEG_XRES;
    Act->s16VideoOffset_Y   = Act->s16VideoOffset_Y * MHEG_YRES_COORD / MHEG_YRES;
    Act->u16BoxSize_X       = Act->u16BoxSize_X     * MHEG_XRES_COORD / MHEG_XRES;
    Act->u16BoxSize_Y       = Act->u16BoxSize_Y     * MHEG_YRES_COORD / MHEG_YRES;
    Act->u16Scale_Width     = Act->u16Scale_Width   * MHEG_XRES_COORD / MHEG_XRES;
    Act->u16Scale_Height    = Act->u16Scale_Height  * MHEG_YRES_COORD / MHEG_YRES;

}
#endif
#endif

/******************************************************************************/
/// @internal
///- This API will do Video Translation for MHEG-5.
/// @param *pstVideoAction \b IN: pointer to MHEG-5 vidieo actions
/// @see MS_MHEG5_VIDEO_ACTION
/// @param *pstClipWin \b OUT: pointer to clip Window information
/// @see MS_MHEG5_VIDEO_CLIPWIN
/* ****************************************************************************/

static void _msAPI_MHEG5_VID_Translation(PMS_ARC_PROG_WIN pstMHEG5_Win,MS_WINDOW_TYPE *pstSrcWin ,MS_MHEG5_VIDEO_ACTION *pstVideoAction, MS_MHEG5_VIDEO_CLIPWIN *pstClipWin )//, MS_WINDOW_TYPE *pstDispWin)
{

//==>> Calculate Display window size

    pstClipWin->u16SrcSize_X = (U16) (((pstClipWin->u16SrcPosition_X + pstClipWin->u16SrcSize_X)* pstSrcWin->width + pstVideoAction->u16Scale_Width/2)    / pstVideoAction->u16Scale_Width);

    pstClipWin->u16SrcPosition_X = (U16) (((U32)pstClipWin->u16SrcPosition_X    * pstSrcWin->width)    / pstVideoAction->u16Scale_Width);

    pstClipWin->u16SrcSize_X     -= pstClipWin->u16SrcPosition_X;


    pstClipWin->u16SrcSize_Y = (U16) (((pstClipWin->u16SrcPosition_Y + pstClipWin->u16SrcSize_Y)* pstSrcWin->height+ pstVideoAction->u16Scale_Height/2)    / pstVideoAction->u16Scale_Height);

    pstClipWin->u16SrcPosition_Y = (U16) (((U32)pstClipWin->u16SrcPosition_Y    *  pstSrcWin->height)  / pstVideoAction->u16Scale_Height);

    pstClipWin->u16SrcSize_Y     -= pstClipWin->u16SrcPosition_Y;

/*
    if(pstVideoAction->u16Scale_Width==MHEG_XRES && pstVideoAction->u16Scale_Height==MHEG_YRES) //Alignment
    {
        U16 u16temp = ((pstClipWin->u16SrcPosition_X + 1) & (~(0x01))) - pstClipWin->u16SrcPosition_X;
        pstClipWin->u16SrcPosition_X += u16temp;
        pstClipWin->u16SrcSize_X -= (u16temp*2);

        u16temp = ((pstClipWin->u16SrcPosition_Y + 1) & (~(0x1))) - pstClipWin->u16SrcPosition_Y;
        pstClipWin->u16SrcPosition_Y += u16temp;
        pstClipWin->u16SrcSize_Y -= (u16temp*2);
    }
*/

    pstClipWin->u16DstSize_X        = (U16) ((((U32)pstClipWin->u16DstSize_X + pstClipWin->u16DstPosition_X)       * pstMHEG5_Win->u16H_DisSize + pstMHEG5_Win->u16H_CapSize/2) / (U32)pstMHEG5_Win->u16H_CapSize);
    pstClipWin->u16DstPosition_X    = (U16) (((S32)pstClipWin->u16DstPosition_X    * pstMHEG5_Win->u16H_DisSize) / (S32)pstMHEG5_Win->u16H_CapSize);// + pstMHEG5_Win->u16H_DisStart;

    pstClipWin->u16DstSize_X        -= pstClipWin->u16DstPosition_X;
    pstClipWin->u16DstPosition_X    += pstMHEG5_Win->u16H_DisStart;

    pstClipWin->u16DstSize_Y        = (U16) ((((U32)pstClipWin->u16DstSize_Y + pstClipWin->u16DstPosition_Y)       * pstMHEG5_Win->u16V_DisSize + pstMHEG5_Win->u16V_CapSize/2) / (U32)pstMHEG5_Win->u16V_CapSize);
    pstClipWin->u16DstPosition_Y    = (U16) (((S32)pstClipWin->u16DstPosition_Y    * pstMHEG5_Win->u16V_DisSize) / (S32)pstMHEG5_Win->u16V_CapSize);// + pstMHEG5_Win->u16V_DisStart;

    pstClipWin->u16DstSize_Y        -= pstClipWin->u16DstPosition_Y;
    pstClipWin->u16DstPosition_Y    += pstMHEG5_Win->u16V_DisStart;

    //(printf("2pstClipWin SRC PO(%u,%u) SIZE:(%u,%u)\n",pstClipWin->u16SrcPosition_X, pstClipWin->u16SrcPosition_Y,pstClipWin->u16SrcSize_X, pstClipWin->u16SrcSize_Y));
    //(printf("2pstClipWin DST PO(%u,%u) SIZE:(%u,%u)\n",pstClipWin->u16DstPosition_X, pstClipWin->u16DstPosition_Y,pstClipWin->u16DstSize_X, pstClipWin->u16DstSize_Y));

}

/******************************************************************************/
/// @internal
///- This API will Calculate clip video.
/// @param *pstVideoAction \b IN: pointer to MHEG-5 vidieo actions
/// @see MS_MHEG5_VIDEO_ACTION
/// @param *pstClipWin \b OUT: pointer to clip Window information
/// @see MS_MHEG5_VIDEO_CLIPWIN
/* ****************************************************************************/

static void _msAPI_MHEG5_VID_CalculateClipWin( MS_ARC_PROG_WIN *pstMHEG5_Win, MS_MHEG5_VIDEO_ACTION *pstVideoAction, MS_MHEG5_VIDEO_CLIPWIN *pstClipWin)
{
    S32 s32DisBoxStart_X, s32DisBoxEnd_X, s32DisBoxStart_Y, s32DisBoxEnd_Y;
    S32 s32SrcBoxStart_X, s32SrcBoxEnd_X, s32SrcBoxStart_Y, s32SrcBoxEnd_Y;

    //S32 s32PositionStart_X,s32PositionEnd_X;

    S32 s32TempX,s32TempY;

    s32DisBoxStart_X = pstVideoAction->s16Position_X + (S32)pstVideoAction->s16VideoOffset_X;
    s32DisBoxStart_Y = pstVideoAction->s16Position_Y + (S32)pstVideoAction->s16VideoOffset_Y;

    s32DisBoxEnd_X = (S32)pstVideoAction->s16Position_X + (S32)pstVideoAction->u16BoxSize_X;
    s32DisBoxEnd_Y = (S32)pstVideoAction->s16Position_Y + (S32)pstVideoAction->u16BoxSize_Y;

    s32SrcBoxStart_X = (S32)pstVideoAction->s16Position_X + (S32)pstVideoAction->s16VideoOffset_X;
    s32SrcBoxStart_Y = (S32)pstVideoAction->s16Position_Y + (S32)pstVideoAction->s16VideoOffset_Y ;
    s32SrcBoxEnd_X = (S32)pstVideoAction->s16Position_X + (S32)pstVideoAction->s16VideoOffset_X + (S32)pstVideoAction->u16Scale_Width;
    s32SrcBoxEnd_Y = (S32)pstVideoAction->s16Position_Y + (S32)pstVideoAction->s16VideoOffset_Y + (S32)pstVideoAction->u16Scale_Height;

    //printf("Action Position :(%03d,%03d) ,offset:(%03d,%03d) \n",pstVideoAction->s16Position_X,pstVideoAction->s16Position_Y,pstVideoAction->s16VideoOffset_X,pstVideoAction->s16VideoOffset_Y);
    //printf("Action scale    :(%03u,%03u) ,box   :(%03u,%03u) \n",pstVideoAction->u16Scale_Width,pstVideoAction->u16Scale_Height,pstVideoAction->u16BoxSize_X,pstVideoAction->u16BoxSize_Y);
    if ( (s32DisBoxEnd_X < 0) || (s32DisBoxStart_X > MHEG_XRES_RANGE) ||
         (s32DisBoxEnd_Y < 0) || (s32DisBoxStart_Y > MHEG_YRES_RANGE) ||
         (s32SrcBoxEnd_X < 0) || (s32SrcBoxStart_X > MHEG_XRES_RANGE) ||
         (s32SrcBoxEnd_Y < 0) || (s32SrcBoxStart_Y > MHEG_YRES_RANGE))
    {
        return;
    }
    if(  (s32SrcBoxStart_X > s32DisBoxEnd_X) || (s32SrcBoxEnd_X < s32DisBoxStart_X) ||
         (s32SrcBoxStart_Y > s32DisBoxEnd_Y) || (s32SrcBoxEnd_Y < s32DisBoxStart_Y) )
    {
        return;
    }

    pstClipWin->u16DstPosition_X = (U16)MAX((S32)MAX(s32DisBoxStart_X , s32SrcBoxStart_X) , 0);

    pstClipWin->u16DstPosition_Y = (U16)MAX((S32)MAX(s32DisBoxStart_Y , s32SrcBoxStart_Y) , 0);

    //printf("1.pstClipWin->u16DstPosition:%u,%u\n",pstClipWin->u16DstPosition_X,pstClipWin->u16DstPosition_Y);


    pstClipWin->u16DstSize_X = (U16)((S32)MIN((S32)MIN( s32SrcBoxEnd_X,
                                                        s32DisBoxEnd_X),
                                                        pstMHEG5_Win->u16H_CapStart+pstMHEG5_Win->u16H_CapSize)
                                                        -pstClipWin->u16DstPosition_X);

    pstClipWin->u16DstSize_Y = (U16)((S32)MIN((S32)MIN( s32SrcBoxEnd_Y,
                                                        s32DisBoxEnd_Y),
                                                        pstMHEG5_Win->u16V_CapStart+pstMHEG5_Win->u16V_CapSize)
                                                        -pstClipWin->u16DstPosition_Y);

    //printf("2.pstClipWin->u16DstSize:%u,%u\n",pstClipWin->u16DstSize_X,pstClipWin->u16DstSize_Y);

    pstClipWin->u16SrcPosition_X = pstClipWin->u16DstPosition_X
                                    - MIN(s32SrcBoxStart_X , pstClipWin->u16DstPosition_X );

    pstClipWin->u16SrcPosition_Y = pstClipWin->u16DstPosition_Y
                                    - MIN(s32SrcBoxStart_Y , pstClipWin->u16DstPosition_Y );

    //printf("3.pstClipWin->u16SrcPosition:%u,%u\n",pstClipWin->u16SrcPosition_X,pstClipWin->u16SrcPosition_Y);



    //===========================
    //Adjust for MHEG5 ARC window


    s32TempX = (S32)((U32)pstClipWin->u16DstPosition_X - (U32)pstMHEG5_Win->u16H_CapStart);
    s32TempY = (S32)((U32)pstClipWin->u16DstPosition_Y - (U32)pstMHEG5_Win->u16V_CapStart);


    if ( s32TempX < 0 )
    {
        pstClipWin->u16SrcPosition_X = (U16)((S32)pstClipWin->u16SrcPosition_X - s32TempX);
        pstClipWin->u16DstSize_X = (U16)((S32)pstClipWin->u16DstSize_X + s32TempX);
    }


    if ( s32TempY < 0 )
    {
        pstClipWin->u16SrcPosition_Y = (U16)((S32)pstClipWin->u16SrcPosition_Y - s32TempY);
        pstClipWin->u16DstSize_Y = (U16)((S32)pstClipWin->u16DstSize_Y + s32TempY);
    }
    //printf("4.pstClipWin->u16SrcPosition:%u,%u\n",pstClipWin->u16SrcPosition_X,pstClipWin->u16SrcPosition_Y);
    //printf("4.pstClipWin->u16DstSize:%u,%u\n",pstClipWin->u16DstSize_X,pstClipWin->u16DstSize_Y);


    pstClipWin->u16SrcSize_X = pstClipWin->u16DstSize_X;
    pstClipWin->u16SrcSize_Y = pstClipWin->u16DstSize_Y;

    pstClipWin->u16DstPosition_X = MAX(pstMHEG5_Win->u16H_CapStart,pstClipWin->u16DstPosition_X) - pstMHEG5_Win->u16H_CapStart;
    pstClipWin->u16DstPosition_Y = MAX(pstMHEG5_Win->u16V_CapStart,pstClipWin->u16DstPosition_Y) - pstMHEG5_Win->u16V_CapStart;


    //(printf("1pstClipWin SRC PO(%u,%u) SIZE:(%u,%u)\n",pstClipWin->u16SrcPosition_X, pstClipWin->u16SrcPosition_Y,pstClipWin->u16SrcSize_X, pstClipWin->u16SrcSize_Y));
    //(printf("1pstClipWin DST PO(%u,%u) SIZE:(%u,%u)\n",pstClipWin->u16DstPosition_X, pstClipWin->u16DstPosition_Y,pstClipWin->u16DstSize_X, pstClipWin->u16DstSize_Y));

}
//======================================================================

/******************************************************************************/
/// @internal
///- This API will set capture window and display window
/// @param *pstMHEG5VideoClipWin \b IN: pointer to MHEG-5 vidieo actions
/// @param *pstSrcWin \b IN: pointer to capture window
/// @param *pstDisWin \b IN: pointer to display window
/*****************************************************************************/
static void _msAPI_MHEG5_VID_SetCaptureAndDisplayWin( MS_MHEG5_VIDEO_CLIPWIN *pstMHEG5VideoClipWin,
                                              MS_WINDOW_TYPE *pstSrcWin,
                                              MS_WINDOW_TYPE *pstDisWin)
{

    pstSrcWin->x = pstMHEG5VideoClipWin->u16SrcPosition_X;
    pstSrcWin->y = pstMHEG5VideoClipWin->u16SrcPosition_Y;

    pstSrcWin->width  = pstMHEG5VideoClipWin->u16SrcSize_X;
    pstSrcWin->height = pstMHEG5VideoClipWin->u16SrcSize_Y;

    pstDisWin->x = pstMHEG5VideoClipWin->u16DstPosition_X;
    pstDisWin->y = pstMHEG5VideoClipWin->u16DstPosition_Y;

    pstDisWin->width  = pstMHEG5VideoClipWin->u16DstSize_X;
    pstDisWin->height = pstMHEG5VideoClipWin->u16DstSize_Y;

    if( (pstSrcWin->y&1)!=0 || (pstSrcWin->height&1)!=0 )
    {
        //need to adjust y/height of crop to even
        U16 h1=pstSrcWin->height,h2=pstDisWin->height;
        U16 ly1=pstSrcWin->y,y2=ly1+h1;
        if( (ly1&1)!=0 )ly1++;
        if( (y2&1)!=0 )y2--;
        pstDisWin->height = ((y2-pstSrcWin->y)*h2 + (h1+1)/2)/h1+pstDisWin->y;
        pstDisWin->y = ((ly1-pstSrcWin->y)*h2 + (h1+1)/2)/h1+pstDisWin->y;
        pstDisWin->height -= pstDisWin->y;
        pstSrcWin->y = ly1;
        pstSrcWin->height = y2-ly1;
    }



    M5DBG(printf("Crop(%u,%u,%u,%u) , Disp(%u,%u,%u,%u)\n",pstSrcWin->x,pstSrcWin->y,pstSrcWin->width,pstSrcWin->height,pstDisWin->x,pstDisWin->y,pstDisWin->width,pstDisWin->height ));

#if defined(ENABLE_IFRAME_OFFSET_DBG_INFO) && (ENABLE_IFRAME_OFFSET_DBG_INFO == 1)
    {
        U16 posX[4]={70,70,360,650};
        U16 posY[4]={70,400,288,506};
        U16 result[2] = {0,0};
        U16 i = 0;
        printf("\t======================\n");
        for(i= 0;i < 4; i++)
        {
            result[0] = (posX[i] - pstSrcWin->x) * pstDisWin->width /pstSrcWin->width+pstDisWin->x;
            result[1] = (posY[i] - pstSrcWin->y) * pstDisWin->height/ pstSrcWin->height + pstDisWin->y;
            printf("\t==>BitmapDecodeOffset : IFrame pos ( %d , %d ) -> ( %d , %d ) , scaler size (H,V) = (0x%X,0x%X)\n",posX[i],posY[i],result[0],result[1],result[0]-pstDisWin->x,result[1]-pstDisWin->y);
        }
        printf("\t======================\n");
    }
#endif
}
//======================================================================

/******************************************************************************/
/// @internal
///- This API will calculate transparency in MHEG
/// @param *pstMHEG5VideoAction \b IN: pointer to MHEG-5 vidieo actions
/*****************************************************************************/
static BOOLEAN _msAPI_MHEG5_VID_CalculateTransparency(MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction,MS_WINDOW_TYPE *pstSrcWin, bool bHDuplicate)
{
    U16 u16Mpeg_X, u16Mpeg_Y;
    U16 u16Scale_X, u16Scale_Y;
    U8 u8ScaleFactor;
    BOOLEAN bRet = FALSE;


    u16Mpeg_X = bHDuplicate ? (pstSrcWin->width/2) : pstSrcWin->width;
    u16Mpeg_Y = pstSrcWin->height;
    u16Scale_X = pstMHEG5VideoAction->u16Scale_Width;
    u16Scale_Y = pstMHEG5VideoAction->u16Scale_Height;

    if ( (u16Scale_X == MHEG_XRES_COORD) && (u16Scale_Y == MHEG_YRES_COORD) )
        u8ScaleFactor = SCALING_FULL;
    else if ( (u16Scale_X == (MHEG_XRES_COORD * 2)) && (u16Scale_Y == (MHEG_YRES_COORD * 2)) )
        u8ScaleFactor = SCALING_2X;
    else if ( (u16Scale_X == (MHEG_XRES_COORD / 2)) && (u16Scale_Y == (MHEG_YRES_COORD / 2)) )
        u8ScaleFactor = SCALING_QUARTER;
    else
        u8ScaleFactor = UNKNOW_SCALING_FACTOR;

    /*
    if ( ((u16Mpeg_X == (MHEG_XRES * 2)) && (u16Mpeg_Y == (MHEG_YRES * 2))) ||
         ((u16Mpeg_X == MHEG_XRES) && (u16Mpeg_Y == MHEG_YRES)) ||
         ((u16Mpeg_X == (MHEG_XRES / 2)) && (u16Mpeg_Y == (MHEG_YRES / 2))) )
    */
    // Only for DTG 6.5.4.2 Transparency  MPEG Encoding
    //if ( (u16Mpeg_X != 352) && (u16Mpeg_Y != 288) )
    //{
    //    bRet = FALSE;
    //}
    //else
    {
        switch (u8ScaleFactor)
        {
            case SCALING_FULL:
                if ( u16Mpeg_X < (MHEG_XRES_COORD / 2) )
                {
                    //printf("u16Scale_Width = %04d, u16BoxSize_X = %04d, s16Position_X = %04d\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->s16Position_X);
                    pstMHEG5VideoAction->u16Scale_Width = u16Mpeg_X * 2;
                    pstMHEG5VideoAction->u16BoxSize_X = u16Mpeg_X * 2;
                    pstMHEG5VideoAction->s16Position_X += ((MHEG_XRES_COORD - (u16Mpeg_X * 2)) / 2);
                    //printf("u16Scale_Width = %04d, u16BoxSize_X = %04d, s16Position_X = %04d\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->s16Position_X);
                    bRet = TRUE;
                }
                /*
                else if ( u16Mpeg_X == (MHEG_XRES / 2) )
                {
                    if ( u16Mpeg_Y < (MHEG_YRES / 2) )
                    {
                        pstMHEG5VideoAction->u16Scale_Height = u16Mpeg_Y * 2;
                        pstMHEG5VideoAction->u16BoxSize_Y = u16Mpeg_Y * 2;
                        pstMHEG5VideoAction->s16Position_Y += ((MHEG_YRES - (u16Mpeg_Y * 2)) / 2);
                    }
                    else if ( u16Mpeg_Y < MHEG_YRES )
                    {
                        pstMHEG5VideoAction->u16Scale_Height = u16Mpeg_Y;
                        pstMHEG5VideoAction->u16BoxSize_Y = u16Mpeg_Y;
                        pstMHEG5VideoAction->s16Position_Y += ((MHEG_YRES - u16Mpeg_Y) / 2);
                    }
                }
                else if ( u16Mpeg_X < MHEG_XRES )
                {
                    pstMHEG5VideoAction->u16Scale_Width = u16Mpeg_X;
                    pstMHEG5VideoAction->u16BoxSize_X = u16Mpeg_X;
                    pstMHEG5VideoAction->s16Position_X += ((MHEG_XRES - u16Mpeg_X) / 2);
                }
                else if ( u16Mpeg_X == MHEG_XRES )
                {
                    pstMHEG5VideoAction->u16Scale_Height = u16Mpeg_Y;
                    pstMHEG5VideoAction->u16BoxSize_Y = u16Mpeg_Y;
                    pstMHEG5VideoAction->s16Position_Y += ((MHEG_YRES - u16Mpeg_Y) / 2);
                }
                */
                break;

            case SCALING_2X:
                break;

            case SCALING_QUARTER:
                if ( u16Mpeg_X < (MHEG_XRES_COORD / 2) )
                {
                    //printf("u16Scale_Width = %04d, u16BoxSize_X = %04d, s16Position_X = %04d\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->s16Position_X);
                    pstMHEG5VideoAction->u16Scale_Width = u16Mpeg_X;
                    pstMHEG5VideoAction->u16BoxSize_X = u16Mpeg_X;
                    pstMHEG5VideoAction->s16Position_X += (((MHEG_XRES_COORD / 2) - u16Mpeg_X) / 2);
                    //printf("u16Scale_Width = %04d, u16BoxSize_X = %04d, s16Position_X = %04d\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->s16Position_X);
                    bRet = TRUE;
                }
                /*
                else if ( u16Mpeg_X == (MHEG_XRES / 2) )
                {
                    if ( u16Mpeg_Y < (MHEG_YRES / 2) )
                    {
                        pstMHEG5VideoAction->u16Scale_Height = u16Mpeg_Y;
                        pstMHEG5VideoAction->u16BoxSize_Y = u16Mpeg_Y;
                        pstMHEG5VideoAction->s16Position_Y += (((MHEG_YRES / 2) - u16Mpeg_Y) / 2);
                    }
                }
                else if ( u16Mpeg_X < MHEG_XRES )
                {
                    pstMHEG5VideoAction->u16Scale_Width = u16Mpeg_X / 2;
                    pstMHEG5VideoAction->u16BoxSize_X = u16Mpeg_X / 2;
                    pstMHEG5VideoAction->s16Position_X += (((MHEG_XRES / 2) - (u16Mpeg_X / 2)) / 2);
                }
                else if ( u16Mpeg_X == MHEG_XRES )
                {
                    ;
                }
                */
                break;

            case UNKNOW_SCALING_FACTOR:
            default:
                break;
        }
    }


    return bRet;
}

/******************************************************************************/
///- This API will set graph flag to monitor ARC
/// @param pstDstWin \b IN: pointer to display window
/// @return BOOLEAN - not used
/*****************************************************************************/
U8   msAPI_MHEG5_GetGraphInfoRefreshType(void)
{
    return GraphInfoRefreshType;
}
void msAPI_MHEG5_SetGraphInfoRefreshType(U8 type)
{
    GraphInfoRefreshType = type;
}

//======================================================================
/******************************************************************************/
///- This API will calculate scene aspect ratio in MHEG
/// @param pstDstWin \b IN: pointer to display window
/// @return BOOLEAN - not used
/*****************************************************************************/
BOOLEAN msAPI_MHEG5_CalcSceneAspectRatio(MS_WINDOW_TYPE *pstDstWin)
{
    // Scene Aspect Ratio 4x3
    if ( g_MHEG5Video.eSceneAspectRatio == SCENE_AR_4_3 ) //EN_MHEG5_SceneAspectRatio_4X3 )
    {
        if ( (g_IPanel.AspectRatio()==E_PNL_ASPECT_RATIO_WIDE) )
        {
            pstDstWin->x += (U32)(g_IPanel.Width()) / 8;
            pstDstWin->width = ( U32 )(g_IPanel.Width()) * 3 /4;
            pstDstWin->y = (U32)(g_IPanel.VStart());
            pstDstWin->height = ( U32 )(g_IPanel.Height()) ;
        }
    }
    // Scene Aspect Ratio 16x9
    else if ( g_MHEG5Video.eSceneAspectRatio == SCENE_AR_16_9 )
    {
        if (! (g_IPanel.AspectRatio()==E_PNL_ASPECT_RATIO_WIDE) )
        {
            pstDstWin->y += (U32)(g_IPanel.Height())/8;
            pstDstWin->height = ( U32 )(g_IPanel.Height()) *3 /4;
            pstDstWin->width = ( U32 )(g_IPanel.Width()) ;
        }
#if (PANEL_16_10 == ENABLE)
        else
        {
            pstDstWin->y += (U32)(g_IPanel.Height())/20;
            pstDstWin->height = ( U32 )(g_IPanel.Height()) *9 /10;

        }
#endif
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}
//======================================================================
/******************************************************************************/
///- This API will tell if we want to use AFD settings in video
/// @return BOOLEAN - TRUE: use AFD settings in video
/*****************************************************************************/
BOOLEAN msAPI_MHEG5_VID_AFD_Status(void)
{
    //if (gtPicture.mbSize == u8PSize)
    if(msAPI_MHEG5_IsRunning())
    {
        //printf("msAPI_MHEG5_VID_AFD_Status:%bx,%bx,%bx,%bx\n",g_MHEG5Video.eSceneAspectRatio,g_MHEG5Video.bIFrame,g_MHEG5Video.bHaveVideo,g_MHEG5Video.bFullScreen);
        // Scene Aspec Ratio
        if( g_MHEG5Video.eSceneAspectRatio == SCENE_AR_4_3 )
        {
            return FALSE;
        }
        else if ( g_MHEG5Video.eSceneAspectRatio == SCENE_AR_16_9 )
        {
            return FALSE;
        }
        else if( g_MHEG5Video.bIFrame || !g_MHEG5Video.bHaveVideo )
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    //else
    //{   // UI ARC
        return FALSE;
    //}

}

#if INTERACTION_CHANNEL
/******************************************************************************/
///- This API will send panel aspect ratio, on-screen width/height, and audio pid to MHEG-5 for passing DTG 6.6
/// @param u32Width \b IN: on-screen width
/// @param u32Height \b IN: on-screen height
/// @param u16AudioPid \b IN: audio pid
/*****************************************************************************/
void msAPI_MHEG5_SendICStatus(U16 u8Status)
{

    printf("u8StatusA : %d\n",u8Status);
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CHANNEL
    /*Index*/           ,MB_IC_CHECK_INIT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x02
    /*p1*/              ,(U8)(u8Status)
    /*p2*/              ,(U8)(u8Status>>8)
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

/******************************************************************************/
///- This API will send panel aspect ratio, on-screen width/height, and audio pid to MHEG-5 for passing DTG 6.6
/// @param u32Width \b IN: on-screen width
/// @param u32Height \b IN: on-screen height
/// @param u16AudioPid \b IN: audio pid
/*****************************************************************************/
void msAPI_MHEG5_SendICAddr(U32 u32ICAddr)
{
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CHANNEL
    /*Index*/           ,MB_IC_CHECK_INIT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x04
    /*p1*/              ,(U8)(u32ICAddr>>24)
    /*p2*/              ,(U8)(u32ICAddr>>16)
    /*p3*/              ,(U8)(u32ICAddr>>8)
    /*p4*/              ,(U8)(u32ICAddr)
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}
#endif

/******************************************************************************/
///- This API will send User ARC Event to MHEG-5 for passing DTG 3.10.8.1
/*****************************************************************************/
void msAPI_MHEG5_VID_SendUserArcEvent(void)
{
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_VIDEO
    /*Index*/           ,MB_VID_CMD_SETVTG_EVENT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

/******************************************************************************/
///- This API will tell if we want to use AFD settings in video
/// @parameter bCrop - using crop or not
/// @parameter bUseAFDSetting - current AFD settings
/*****************************************************************************/
BOOLEAN msAPI_MHEG5_VID_SetWindowInfo(XC_SETWIN_INFO *pstXC_SetWin_Info,SCALER_WIN eScalerWindow)
{

    //U32 heightRatio = g_IPanel.Height();
    //U32 widthRatio  = g_IPanel.Width();

    MS_MHEG5_VIDEO_ACTION stMHEG5VideoAction;// = &g_MHEG5Video.stMHEG5VideoAction;
    MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction = &stMHEG5VideoAction;
    MS_MHEG5_VIDEO_CLIPWIN *pstMHEG5VideoClipWin = &g_MHEG5Video.stMHEG5VideoClipWin;
    MS_ARC_PROG_WIN *pstArcProgWin;

    if ( (g_MHEG5Video.bHaveVideo == FALSE && !msAPI_MHEG5_IsIFrameExist()) ||
        (pstXC_SetWin_Info->stCapWin.height == 0) ||(pstXC_SetWin_Info->stCapWin.width==0)||
         ((g_MHEG5Video.bVideoActionNotRdy == TRUE) && (g_MHEG5Video.u8VideoFlag & EVER_SET_VIDEO_STREAM)) )
    {
        M5DBG(printf("msAPI_MHEG5_VID_SetWindowInfo == FALSE\n"));
        //if(g_MHEG5Video.bHaveVideo == FALSE && !msAPI_MHEG5_IsIFrameExist()) printf("M5 SW_INFO return 1\n");
        //if(MApp_Scramble_GetCurStatus() == TRUE && enMVDVideoStatus != MVD_GOOD_VIDEO) printf("M5 SW_INFO return 2\n");
        //if((g_MHEG5Video.bVideoActionNotRdy == TRUE) && (g_MHEG5Video.u8VideoFlag & EVER_SET_VIDEO_STREAM)) printf("M5 SW_INFO return 3\n");
        return FALSE;
    }

    //IFrame => use Iframe Action
    if(msAPI_MHEG5_IsIFrameExist())
    {
        stMHEG5VideoAction = g_MHEG5Video.stMHEG5IFrameAction;
        //use full screen setting
        pstArcProgWin = &g_MHEG5Video.stARCWin;
    }
    //Video => use Video Action
    else
    {
        stMHEG5VideoAction = g_MHEG5Video.stMHEG5VideoAction;

        //AFD only use in FULLSCREEN
        if( msAPI_MHEG5_VID_AFD_Status() &&
            msAPI_MHEG5_VID_IsFullScreen(&stMHEG5VideoAction))
        {
            pstArcProgWin = &g_MHEG5Video.stAFDWin;
        }
        else
        {
            pstArcProgWin = &g_MHEG5Video.stARCWin;
        }
    }

    g_MHEG5Video.bFullScreen = msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction);

    //==>> Check if MHEG5 Action have invalid scale or box size value, then reset it.
    _msAPI_MHEG5_VID_CheckAndResetScaleSize(pstMHEG5VideoAction);
    _msAPI_MHEG5_VID_CheckAndResetBoxSize(pstMHEG5VideoAction);


    //==>> Adjust scene AR video======================================
    if( g_MHEG5Video.eSceneAspectRatio != SCENE_AR_None &&
        msAPI_MHEG5_VID_IsFullScreen(pstMHEG5VideoAction))
    {
        _msAPI_MHEG5_VID_AdjustSceneAR(pstMHEG5VideoAction);
    }


    {
        M5DBG(printf("==============================================\n"));

        //==>> 1.Calculate Transparency
        _msAPI_MHEG5_VID_CalculateTransparency(pstMHEG5VideoAction,&(pstXC_SetWin_Info->stCapWin),pstXC_SetWin_Info->bHDuplicate);
    #if HD_MHEG5
        _M5Action_SD2HD(&stMHEG5VideoAction);
    #endif
        M5DBG(printf(" | 1.Action scale:(%u,%u)  box    (%u,%u);\n",pstMHEG5VideoAction->u16Scale_Width,pstMHEG5VideoAction->u16Scale_Height,pstMHEG5VideoAction->u16BoxSize_X,pstMHEG5VideoAction->u16BoxSize_Y));
        M5DBG(printf(" | 1.Action posi :(%d,%d)  offset (%d,%d);\n",pstMHEG5VideoAction->s16Position_X,pstMHEG5VideoAction->s16Position_Y,pstMHEG5VideoAction->s16VideoOffset_X,pstMHEG5VideoAction->s16VideoOffset_Y));

        //==>> 2. Calculate clip windows
        _msAPI_MHEG5_VID_CalculateClipWin(pstArcProgWin, pstMHEG5VideoAction, pstMHEG5VideoClipWin );

        //==>> 3. Translate 720x576 base display window to panel size.
        _msAPI_MHEG5_VID_Translation( pstArcProgWin, &(pstXC_SetWin_Info->stCapWin), pstMHEG5VideoAction, pstMHEG5VideoClipWin);


        //==>> 4. Set Clip window info to temp crop and display window
        _msAPI_MHEG5_VID_SetCaptureAndDisplayWin(pstMHEG5VideoClipWin, &(pstXC_SetWin_Info->stCropWin),&(pstXC_SetWin_Info->stDispWin));


        {
        //==>> 6. if crop, setup scale ratio================================
            U32 widthScaleRatio = (((U32)pstArcProgWin->u16H_DisSize * pstMHEG5VideoAction->u16Scale_Width + pstArcProgWin->u16H_CapSize/2) /    ((U32)pstArcProgWin->u16H_CapSize));
            U32 heightScaleRatio = (((U32)pstArcProgWin->u16V_DisSize * pstMHEG5VideoAction->u16Scale_Height +pstArcProgWin->u16V_CapSize/2) / ((U32)pstArcProgWin->u16V_CapSize));
            U16 tmpDisWidth,tmpDisHeight;

            M5DBG(printf("MHEG5 SetWindowInfo: ScaleRatio:(%lu,%lu)\n",widthScaleRatio,heightScaleRatio));

            if(pstXC_SetWin_Info->stCapWin.width>widthScaleRatio)
            {
                pstXC_SetWin_Info->bPreHCusScaling = TRUE;            ///<assign pre H customized scaling instead of using XC scaling
                pstXC_SetWin_Info->bHCusScaling = FALSE;

                pstXC_SetWin_Info->u16PreHCusScalingSrc = pstXC_SetWin_Info->stCapWin.width;       ///<pre H customized scaling src width
                pstXC_SetWin_Info->u16PreHCusScalingDst = widthScaleRatio;       ///<pre H customized scaling dst width

                pstXC_SetWin_Info->u16HCusScalingSrc = widthScaleRatio;
                pstXC_SetWin_Info->u16HCusScalingDst = widthScaleRatio;

            }
            else
            {
                pstXC_SetWin_Info->bPreHCusScaling = TRUE;
                pstXC_SetWin_Info->bHCusScaling = FALSE;

                pstXC_SetWin_Info->u16PreHCusScalingSrc = pstXC_SetWin_Info->stCapWin.width;       ///<pre H customized scaling src width
                pstXC_SetWin_Info->u16PreHCusScalingDst = pstXC_SetWin_Info->stCapWin.width;       ///<pre H customized scaling dst width

                pstXC_SetWin_Info->u16HCusScalingSrc = pstXC_SetWin_Info->stCapWin.width;
                pstXC_SetWin_Info->u16HCusScalingDst = widthScaleRatio;

            }

            if(pstXC_SetWin_Info->stCapWin.height>heightScaleRatio)
            {
                pstXC_SetWin_Info->bPreVCusScaling = TRUE;
                pstXC_SetWin_Info->bVCusScaling = FALSE;

                pstXC_SetWin_Info->u16PreVCusScalingSrc = pstXC_SetWin_Info->stCapWin.height;       ///<pre V customized scaling src height
                pstXC_SetWin_Info->u16PreVCusScalingDst = heightScaleRatio;       ///<pre V customized scaling dst height
                pstXC_SetWin_Info->u16VCusScalingSrc = heightScaleRatio;
                pstXC_SetWin_Info->u16VCusScalingDst = heightScaleRatio;
            }
            else
            {
                pstXC_SetWin_Info->bPreVCusScaling = TRUE;
                pstXC_SetWin_Info->bVCusScaling = FALSE;
                pstXC_SetWin_Info->u16PreVCusScalingSrc = pstXC_SetWin_Info->stCapWin.height;       ///<pre V customized scaling src height
                pstXC_SetWin_Info->u16PreVCusScalingDst = pstXC_SetWin_Info->stCapWin.height;       ///<pre V customized scaling dst height
                pstXC_SetWin_Info->u16VCusScalingSrc = pstXC_SetWin_Info->stCapWin.height;
                pstXC_SetWin_Info->u16VCusScalingDst = heightScaleRatio;
            }
            if(msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction))
            {
                pstXC_SetWin_Info->bPreHCusScaling = FALSE;
                pstXC_SetWin_Info->bHCusScaling = FALSE;
                pstXC_SetWin_Info->bPreVCusScaling = FALSE;
                pstXC_SetWin_Info->bVCusScaling = FALSE;
            }

//TMP solution.
#if 0 //(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
            if(MApi_XC_IsFrameBufferEnoughForCusScaling(pstXC_SetWin_Info,eScalerWindow) == FALSE)
            {
                //preScaling down to minimum size.
                pstXC_SetWin_Info->u16PreHCusScalingDst = MHEG_XRES_COORD;       ///<pre H customized scaling min dst width
                pstXC_SetWin_Info->u16HCusScalingSrc =    MHEG_XRES_COORD;
                pstXC_SetWin_Info->u16PreVCusScalingDst = MHEG_YRES_COORD;       ///<pre V customized scaling min dst height
                pstXC_SetWin_Info->u16VCusScalingSrc =    MHEG_YRES_COORD;
            }
#else
            UNUSED(eScalerWindow);
#endif

            if(pstXC_SetWin_Info->stCapWin.width == 0 || pstXC_SetWin_Info->stCapWin.height == 0)
            {
                //printf("pstXC_SetWin_Info->stCapWin:%u,%u\n",pstXC_SetWin_Info->stCapWin.width,pstXC_SetWin_Info->stCapWin.height);
                return FALSE;
            }
            //Finetune cropping size and display size for garbage line. kris 980617.
            {
                //pstXC_SetWin_Info->stCropWin.x = (pstXC_SetWin_Info->stCropWin.x + 1) & ~0x01;
                //pstXC_SetWin_Info->stCropWin.y = (pstXC_SetWin_Info->stCropWin.y + 1) & ~0x01;

                pstXC_SetWin_Info->stCropWin.width = MIN(pstXC_SetWin_Info->stCropWin.x + pstXC_SetWin_Info->stCropWin.width , pstXC_SetWin_Info->stCapWin.width) - pstXC_SetWin_Info->stCropWin.x;
                pstXC_SetWin_Info->stCropWin.height = MIN(pstXC_SetWin_Info->stCropWin.y + pstXC_SetWin_Info->stCropWin.height , pstXC_SetWin_Info->stCapWin.height) - pstXC_SetWin_Info->stCropWin.y;

                //if(!msAPI_MHEG5_VID_IsFullScreen(pstMHEG5VideoAction))
                if(pstMHEG5VideoAction->u16Scale_Width  > MHEG_XRES_COORD || pstMHEG5VideoAction->u16Scale_Height > MHEG_YRES_COORD)
                {
                    tmpDisWidth =  (pstXC_SetWin_Info->stCropWin.width * widthScaleRatio + (pstXC_SetWin_Info->stCapWin.width+1)/2)/ pstXC_SetWin_Info->stCapWin.width;
                    tmpDisHeight = (pstXC_SetWin_Info->stCropWin.height * heightScaleRatio + (pstXC_SetWin_Info->stCapWin.height+1)/2)/ pstXC_SetWin_Info->stCapWin.height;

                    if(pstXC_SetWin_Info->stCropWin.x + pstXC_SetWin_Info->stCropWin.width <= pstXC_SetWin_Info->stCapWin.width)
                        pstXC_SetWin_Info->stDispWin.width = MIN(pstXC_SetWin_Info->stDispWin.width,tmpDisWidth);

                    if(pstXC_SetWin_Info->stCropWin.y + pstXC_SetWin_Info->stCropWin.height <= pstXC_SetWin_Info->stCapWin.height)
                        pstXC_SetWin_Info->stDispWin.height = MIN(pstXC_SetWin_Info->stDispWin.height,tmpDisHeight);
                }
            }
            //End finetune====


            #if 0
            pstXC_SetWin_Info->bHCusScaling = TRUE;
            pstXC_SetWin_Info->u16HCusScalingSrc = pstXC_SetWin_Info->stCropWin.width;
            pstXC_SetWin_Info->u16HCusScalingDst = pstXC_SetWin_Info->stDispWin.width;

            pstXC_SetWin_Info->bVCusScaling = TRUE;
            pstXC_SetWin_Info->u16VCusScalingSrc = pstXC_SetWin_Info->stCropWin.height;
            pstXC_SetWin_Info->u16VCusScalingDst = pstXC_SetWin_Info->stDispWin.height;
            #endif

            //MDrv_SC_set_x_scale(MS_SCALE_MANUAL, gstVidStatus.u16HorSize, widthScaleRatio, MAIN_WINDOW);
            //MDrv_SC_set_y_scale(MS_SCALE_MANUAL, gstVidStatus.u16VerSize, heightSccaleRatio, MAIN_WINDOW);

            //MDrv_SC_set_x_scale(MS_SCALE_MANUAL, pstArcProgWin->u16H_CapSize, ((U32)widthScaleRatio));
            //MDrv_SC_set_y_scale(MS_SCALE_MANUAL, pstArcProgWin->u16V_CapSize, ((U32)heightSccaleRatio));
        }

        //================================================================
    }

    M5DBG(printf("==========================================\n"));

    g_MHEG5Video.stPrevMHEG5VideoAction = *pstMHEG5VideoAction;
    g_MHEG5Video.bPrevFullScreen = g_MHEG5Video.bFullScreen;

    return TRUE;
}


#if GOP_SCALERATIO_FIXED2
/******************************************************************************/
/// This API will send ARC information to MHEG-5
/// @param u8Flag \b IN: MHEG5 Video ARC flag
/******************************************************************************/
void msAPI_MHEG5_VID_SendARCInfo( U8 u8Flag , U8 u8UIARC )
{
    MS_ARC_PROG_WIN * pstMHEG5_Win;

    U8 u8ARC_Control = 0;
    U8 u8AFD = 0;
    S8 u8MsgClass,s8Index1,s8Index2;

    M5DBG(printf("======MailBox 2 AEON - Value : %bu===============\n",u8Flag));


    u8MsgClass = ( (u8Flag & SENDARC_MHEG5_INIT) || (u8Flag & SENDARC_AFD_FOR_GE_MHEG5_INIT) ) ?
                                E_MBX_CLASS_MHEG5_STATE : E_MBX_CLASS_VIDEO;
    if ( u8Flag & SENDARC_AFD )
    {
        //==>1.choice AFDWin setting
        pstMHEG5_Win    = &g_MHEG5Video.stAFDWin;

        //==>2.AFD
        u8AFD           = (gstVidStatus.u8AFD==0) ? E_MVD_AFD_FULL_FRAME : gstVidStatus.u8AFD;

        //==>3.Index part1
        s8Index1        = MB_VID_CMD_SETARC_PART1;

        //==>3.Index part2
        s8Index2        = MB_VID_CMD_SETARC_PART2;

        //==>4.ARC_Control
        u8ARC_Control   = 0;
    }
    else
    {
        //==>1.choice AFDWin setting
        pstMHEG5_Win    = &g_MHEG5Video.stARCWin;

        //==>2.AFD
        u8AFD           = 0;

        //==>3.Index part1
        s8Index1        = (u8MsgClass == E_MBX_CLASS_MHEG5_STATE) ?
                                            MB_MHEG5_STATE_CMD_SETARC_PART1 : MB_VID_CMD_SETARC_PART1;
        //==>3.Index part2
        s8Index2        = (u8MsgClass == E_MBX_CLASS_MHEG5_STATE) ?
                                            MB_MHEG5_STATE_CMD_SETARC_PART2 : MB_VID_CMD_SETARC_PART2;
        //==>4.ARC_Control
        u8ARC_Control   = (u8MsgClass == E_MBX_CLASS_MHEG5_STATE) ?   0 : SETARC_FULL_SCREEN_GE;


    }

    //==> Send Part1 mail.
    M5_MAILBOX_SEND(    u8MsgClass
    /*Index*/           ,s8Index1
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x0A

    /*p1*/              ,( u8UIARC & 0x00FF )
    /*p2*/              ,(   pstMHEG5_Win->u16H_CapStart & 0x00FF )
    /*p3*/              ,( ((pstMHEG5_Win->u16H_CapStart & 0xFF00) >> 8) & 0x00FF )
    /*p4*/              ,(   pstMHEG5_Win->u16V_CapStart & 0x00FF )
    /*p5*/              ,( ((pstMHEG5_Win->u16V_CapStart & 0xFF00) >> 8) & 0x00FF )

    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0

    /*p10*/     ,u8AFD);



    //==> Send Part2 mail.
    M5_MAILBOX_SEND(     u8MsgClass
    /*Index*/           ,s8Index2
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x0A

    /*p1*/              ,u8ARC_Control
    /*p2*/              ,(   pstMHEG5_Win->u16H_CapSize & 0x00FF )
    /*p3*/              ,( ((pstMHEG5_Win->u16H_CapSize & 0xFF00) >> 8) & 0x00FF )
    /*p4*/              ,(   pstMHEG5_Win->u16V_CapSize & 0x00FF )
    /*p5*/              ,( ((pstMHEG5_Win->u16V_CapSize & 0xFF00) >> 8) & 0x00FF )

    /*p6*/              ,(   MHEG_XRES_OS & 0x00FF )
    /*p7*/              ,( ((MHEG_XRES_OS & 0xFF00) >> 8) & 0x00FF )
    /*p8*/              ,(   MHEG_YRES_OS & 0x00FF )
    /*p9*/              ,( ((MHEG_YRES_OS & 0xFF00) >> 8) & 0x00FF )
    /*p10*/     ,u8AFD);


}
#else  //GOP_SCALERATIO_FIXED2

/******************************************************************************/
/// This API will send ARC information to MHEG-5
/// @param u8Flag \b IN: MHEG5 Video ARC flag
/******************************************************************************/
void msAPI_MHEG5_VID_SendARCInfo( U8 u8Flag , U8 u8UIARC )
{
    MBX_Msg mbxMsg;
    MS_ARC_PROG_WIN * pstMHEG5_ARC_Win = &g_MHEG5Video.stARCWin;
    MS_ARC_PROG_WIN * pstMHEG5_AFD_Win = &g_MHEG5Video.stAFDWin;
    U8 u8ARC_Control = 0;
    U8 u8AFD = 0;
    U8 u8CurGWIN = MApi_GOP_GWIN_GetCurrentWinId();

#if (MHEG5_ENABLE)//For Co-exist with OSD we need to release the GE mutex here before trigger the ratio in MHEG5
        if(MHEG5_WITH_OSD == 1 && msAPI_MHEG5_checkGoBackMHEG5() == true)
        {
            msAPI_OSD_BackupClipWindow();
        }
#endif
    //msAPI_MHEG5_VID_GetARCInfo(u8Flag);

//printf("ss\n");

#if 0//GOP_SCALERATIO_FIXED
    //pstMHEG5_ARC_Win->u16H_CapSize = (pstMHEG5_ARC_Win->u16H_CapSize+0x03) & ~0x03;
    pstMHEG5_ARC_Win->u16H_DisSize = (pstMHEG5_ARC_Win->u16H_DisSize+0x07) & ~0x07;
    pstMHEG5_ARC_Win->u16H_CapStart = (pstMHEG5_ARC_Win->u16H_CapStart+0x07) & ~0x07;
    pstMHEG5_ARC_Win->u16H_DisStart = (pstMHEG5_ARC_Win->u16H_DisStart+0x01) & ~0x01;
#endif

    memset(&MailBoxPara, 0, sizeof(MailBox));

    M5DBG(printf("======MailBox 2 AEON - Value : %bu===============\n",u8Flag));

    if ( (u8Flag & SENDARC_MHEG5_INIT) || (u8Flag & SENDARC_AFD_FOR_GE_MHEG5_INIT) )
    {
        mbxMsg.u8MsgClass = E_MBX_CLASS_MHEG5_STATE;
    }
    else
    {
        mbxMsg.u8MsgClass = E_MBX_CLASS_VIDEO;
    }

    //sned Aeon the original Display Window size, this is used for VideoToGraphic
#if (MHEG5_X_STRETCH_WAY==MHEG5_USE_GOP_STRETCH)

     if ( u8Flag & SENDARC_AFD )
     {
        u8AFD                       = (gstVidStatus.u8AFD==0)?E_MVD_AFD_FULL_FRAME : gstVidStatus.u8AFD;
        mbxMsg.u8Index        = MB_VID_CMD_SETVTG;
        mbxMsg.u8ParameterCount= 10;
        mbxMsg.eMsgType= E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8Parameters[0]      = (U8)( u8UIARC & 0x00FF );
        mbxMsg.u8Parameters[1]      = (U8)( pstMHEG5_AFD_Win->u16H_DisStart & 0x00FF );
        mbxMsg.u8Parameters[2]      = (U8)( ((pstMHEG5_AFD_Win->u16H_DisStart & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[3]      = (U8)( pstMHEG5_AFD_Win->u16V_DisStart & 0x00FF );
        mbxMsg.u8Parameters[4]      = (U8)( ((pstMHEG5_AFD_Win->u16V_DisStart & 0xFF00) >> 8) & 0x00FF );

        mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_AFD_Win->u16H_DisSize & 0x00FF );
        mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_AFD_Win->u16H_DisSize & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_AFD_Win->u16V_DisSize & 0x00FF );
        mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_AFD_Win->u16V_DisSize & 0xFF00) >> 8) & 0x00FF );

        mbxMsg.u8Parameters[9]      = u8AFD;

        while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

        MsOS_DelayTask(50);

        mbxMsg.u8Index        = MB_VID_CMD_SETVTG2;
        mbxMsg.u8ParameterCount        = 10;
        mbxMsg.eMsgType         = E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8Parameters[0]      = (U8)( u8UIARC & 0x00FF );
        mbxMsg.u8Parameters[1]      = (U8)( pstMHEG5_ARC_Win->u16H_DisStart & 0x00FF );
        mbxMsg.u8Parameters[2]      = (U8)( ((pstMHEG5_ARC_Win->u16H_DisStart & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[3]      = (U8)( pstMHEG5_ARC_Win->u16V_DisStart & 0x00FF );
        mbxMsg.u8Parameters[4]      = (U8)( ((pstMHEG5_ARC_Win->u16V_DisStart & 0xFF00) >> 8) & 0x00FF );

        mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_ARC_Win->u16H_DisSize & 0x00FF );
        mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_ARC_Win->u16H_DisSize & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_ARC_Win->u16V_DisSize & 0x00FF );
        mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_ARC_Win->u16V_DisSize & 0xFF00) >> 8) & 0x00FF );

        while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

        MsOS_DelayTask(50);

        mbxMsg.u8Index        = MB_VID_CMD_SETVTG_SETTING;
        mbxMsg.u8ParameterCount        = 2;
        mbxMsg.eMsgType         = E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8Parameters[0]      = (U8)( u8UIARC & 0x00FF );
        mbxMsg.u8Parameters[1]      = (U8) TRUE;

        while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

        MsOS_DelayTask(50);

    }
#endif

    if ( u8Flag & SENDARC_AFD )
    {
        u8AFD                       = (gstVidStatus.u8AFD==0)?E_MVD_AFD_FULL_FRAME : gstVidStatus.u8AFD;

        mbxMsg.u8Index        = MB_VID_CMD_SETARC_PART1;
        mbxMsg.u8ParameterCount        = 10;
        mbxMsg.eMsgType         = E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8Parameters[0]      = (U8)( u8UIARC & 0x00FF );
        mbxMsg.u8Parameters[1]      = (U8)( pstMHEG5_AFD_Win->u16H_CapStart & 0x00FF );
        mbxMsg.u8Parameters[2]      = (U8)( ((pstMHEG5_AFD_Win->u16H_CapStart & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[3]      = (U8)( pstMHEG5_AFD_Win->u16V_CapStart & 0x00FF );
        mbxMsg.u8Parameters[4]      = (U8)( ((pstMHEG5_AFD_Win->u16V_CapStart & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_AFD_Win->u16H_DisStart & 0x00FF );
        mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_AFD_Win->u16H_DisStart & 0xFF00) >> 8) & 0x00FF );
        #if (MHEG5_Y_STRETCH_WAY==MHEG5_USE_GE_STRETCH)
            mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_AFD_Win->u16V_DisStart & 0x00FF );
            mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_AFD_Win->u16V_DisStart & 0xFF00) >> 8) & 0x00FF );
        #else
            mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_AFD_Win->u16V_CapStart & 0x00FF );
            mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_AFD_Win->u16V_CapStart & 0xFF00) >> 8) & 0x00FF );
        #endif

        mbxMsg.u8Parameters[9]      = u8AFD;

        M5DBG(printf("MEHG-AFD-CapStart :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_AFD_Win->u16H_CapStart ,pstMHEG5_AFD_Win->u16V_CapStart ));
        M5DBG(printf("MEHG-AFD-DisStart :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_AFD_Win->u16H_DisStart,pstMHEG5_AFD_Win->u16V_DisStart));
    }
    else
    {
        u8AFD                       = 0;

        if(mbxMsg.u8MsgClass == E_MBX_CLASS_MHEG5_STATE)
        {
            mbxMsg.u8Index    = MB_MHEG5_STATE_CMD_SETARC_PART1;
        }
        else
        {
            mbxMsg.u8Index    = MB_VID_CMD_SETARC_PART1;
        }
        mbxMsg.u8ParameterCount        = 10;
        mbxMsg.eMsgType         = E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8Parameters[0]      = (U8)( u8UIARC & 0x00FF );
        mbxMsg.u8Parameters[1]      = (U8)( pstMHEG5_ARC_Win->u16H_CapStart & 0x00FF );
        mbxMsg.u8Parameters[2]      = (U8)( ((pstMHEG5_ARC_Win->u16H_CapStart & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[3]      = (U8)( pstMHEG5_ARC_Win->u16V_CapStart & 0x00FF );
        mbxMsg.u8Parameters[4]      = (U8)( ((pstMHEG5_ARC_Win->u16V_CapStart & 0xFF00) >> 8) & 0x00FF );
        #if (MHEG5_X_STRETCH_WAY == MHEG5_USE_GE_STRETCH)
            mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_ARC_Win->u16H_DisStart & 0x00FF );
            mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_ARC_Win->u16H_DisStart & 0xFF00) >> 8) & 0x00FF );
        #else
            #if GOP_SCALERATIO_FIXED
            mbxMsg.u8Parameters[5]      = (U8)( (pstMHEG5_ARC_Win->u16H_DisStart/2) & 0x00FF );
            mbxMsg.u8Parameters[6]      = (U8)( (((pstMHEG5_ARC_Win->u16H_DisStart/2) & 0xFF00) >> 8) & 0x00FF );
            #else
            mbxMsg.u8Parameters[5]      = 0;
            mbxMsg.u8Parameters[6]      = 0;
            #endif
        #endif

        #if (MHEG5_Y_STRETCH_WAY == MHEG5_USE_GE_STRETCH)
            mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_ARC_Win->u16V_DisStart & 0x00FF );
            mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_ARC_Win->u16V_DisStart & 0xFF00) >> 8) & 0x00FF );
        #else
            mbxMsg.u8Parameters[7]      = (U8)( (pstMHEG5_ARC_Win->u16V_DisStart /2)& 0x00FF );
            mbxMsg.u8Parameters[8]      = (U8)( (((pstMHEG5_ARC_Win->u16V_DisStart /2)& 0xFF00) >> 8) & 0x00FF );
        #endif

        mbxMsg.u8Parameters[9]      = u8AFD;

        M5DBG(printf("MEHG-ARC-CapStart :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_ARC_Win->u16H_CapStart,pstMHEG5_ARC_Win->u16V_CapStart));
        M5DBG(printf("MEHG-ARC-DisStart :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_ARC_Win->u16H_DisStart,pstMHEG5_ARC_Win->u16V_DisStart));
    }

    while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

    MsOS_DelayTask(50);

    if ( u8Flag & SENDARC_AFD )
    {
        mbxMsg.u8MsgClass = E_MBX_CLASS_VIDEO;
        u8ARC_Control               = 0;
        u8AFD                       = (gstVidStatus.u8AFD==0)?E_MVD_AFD_FULL_FRAME : gstVidStatus.u8AFD;


        mbxMsg.u8Index        = MB_VID_CMD_SETARC_PART2;
        mbxMsg.u8ParameterCount = 10;
        mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8Parameters[0]      = u8ARC_Control;
        mbxMsg.u8Parameters[1]      = (U8)( pstMHEG5_AFD_Win->u16H_CapSize & 0x00FF );
        mbxMsg.u8Parameters[2]      = (U8)( ((pstMHEG5_AFD_Win->u16H_CapSize & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[3]      = (U8)( pstMHEG5_AFD_Win->u16V_CapSize & 0x00FF );
        mbxMsg.u8Parameters[4]      = (U8)( ((pstMHEG5_AFD_Win->u16V_CapSize & 0xFF00) >> 8) & 0x00FF );
        #if (MHEG5_X_STRETCH_WAY == MHEG5_USE_GE_STRETCH)
        mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_AFD_Win->u16H_DisSize & 0x00FF );
        mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_AFD_Win->u16H_DisSize & 0xFF00) >> 8) & 0x00FF );
        #else
        mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_AFD_Win->u16H_CapSize & 0x00FF );
        mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_AFD_Win->u16H_CapSize & 0xFF00) >> 8) & 0x00FF );
        #endif


        #if (MHEG5_Y_STRETCH_WAY == MHEG5_USE_GE_STRETCH)
        mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_AFD_Win->u16V_DisSize & 0x00FF );
        mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_AFD_Win->u16V_DisSize & 0xFF00) >> 8) & 0x00FF );
        #else
        mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_AFD_Win->u16V_CapSize & 0x00FF );
        mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_AFD_Win->u16V_CapSize & 0xFF00) >> 8) & 0x00FF );
        #endif

        mbxMsg.u8Parameters[9]      = u8AFD;


        M5DBG(printf("MEHG-AFD-CapSize :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_AFD_Win->u16H_CapSize,pstMHEG5_AFD_Win->u16V_CapSize));
        M5DBG(printf("MEHG-AFD-DisSize :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_AFD_Win->u16H_DisSize,pstMHEG5_AFD_Win->u16V_DisSize));


        //(printf("send AFD CAP:(%u,%u,%u,%u) DSP(%u,%u,%u,%u)\n",pstMHEG5_AFD_Win->u16H_CapStart,pstMHEG5_AFD_Win->u16V_CapStart,pstMHEG5_AFD_Win->u16H_CapSize,pstMHEG5_AFD_Win->u16V_CapSize,pstMHEG5_AFD_Win->u16H_DisStart,pstMHEG5_AFD_Win->u16V_DisStart,pstMHEG5_AFD_Win->u16H_DisSize,pstMHEG5_AFD_Win->u16V_DisSize));
    }
    else
    {

        #if (MHEG5_X_STRETCH_WAY == MHEG5_USE_GOP_STRETCH)
        //printf("ARC:%u->%u\n", pstMHEG5_ARC_Win->u16H_CapSize, pstMHEG5_ARC_Win->u16H_DisSize);
        //printf("ARC:u16H_DisStart  %u \n", pstMHEG5_ARC_Win->u16H_DisStart );
       MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);


#if GOP_SCALERATIO_FIXED
    #if(MHEG5_Y_STRETCH_WAY == MHEG5_USE_GOP_STRETCH)
    MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
        MApi_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, 0,0, ((g_IPanel.Width()+7)& ~0x07)/2, ((g_IPanel.Height()+7)& ~0x07)/2);
    #else
        MDrv_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, 0,0, ((g_IPanel.Width()+7)& ~0x07)/2, g_IPanel.Height());
    #endif

#else
        MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
        MApi_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, 0,0, pstMHEG5_ARC_Win->u16H_CapSize, g_IPanel.Height());
#endif



#if !GOP_SCALERATIO_FIXED //GOP stretch ratio is not fixed, we need to reset GOP ratio here everytime....

        MApi_GOP_GWIN_SetHDisplaySize(MHEG5_GWINID,
                                      pstMHEG5_ARC_Win->u16H_CapSize+4,
                                      pstMHEG5_ARC_Win->u16H_DisStart);


        MApi_GOP_GWIN_Set_HSCALE(TRUE, pstMHEG5_ARC_Win->u16H_CapSize,
                                       pstMHEG5_ARC_Win->u16H_DisSize);
#endif
         MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
        #endif

        if ( (u8Flag & SENDARC_MHEG5_INIT) || (u8Flag & SENDARC_AFD_FOR_GE_MHEG5_INIT) )
        {
            mbxMsg.u8MsgClass  = MB_CLASS_MHEG5_STATE;
            u8ARC_Control           = 0;
            u8AFD                   = 0;
        }
        else if ( u8Flag & SENDARC_SCENE_RATIO_CHANGE )
        {
            mbxMsg.u8MsgClass      = MB_CLASS_VIDEO;
            u8ARC_Control               = 0;
            u8AFD                       = 0;
        }
        else if ( u8Flag & SENDARC_ARC_CHANGE )
        {
            mbxMsg.u8MsgClass  = MB_CLASS_VIDEO;
/*
            if ( g_MHEG5Video.bARCChange == TRUE )
                u8ARC_Control = 0; //SETARC;
            else if ( g_MHEG5Video.bARCAdj_H == TRUE )
                u8ARC_Control = SETARC_ADJ_H;
            else if ( g_MHEG5Video.bARCAdj_V == TRUE )
                u8ARC_Control = SETARC_ADJ_V;
            else
*/
            u8ARC_Control = SETARC_FULL_SCREEN_GE;

            u8AFD = 0;
        }
        else if ( u8Flag & SENDARC_AFD_FOR_GE )
        {
            mbxMsg.u8MsgClass  = MB_CLASS_VIDEO;
            u8ARC_Control           = SETARC_FULL_SCREEN_GE;
            u8AFD                   = 0;
        }

        if(mbxMsg.u8MsgClass == MB_CLASS_MHEG5_STATE)
        {
            mbxMsg.u8Index    = MB_MHEG5_STATE_CMD_SETARC_PART2;
        }
        else
        {
            mbxMsg.u8Index    = MB_VID_CMD_SETARC_PART2;
        }
        mbxMsg.u8ParameterCount= 10;
        mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
        mbxMsg.u8Parameters[0]      = u8ARC_Control;
        mbxMsg.u8Parameters[1]      = (U8)( pstMHEG5_ARC_Win->u16H_CapSize & 0x00FF );
        mbxMsg.u8Parameters[2]      = (U8)( ((pstMHEG5_ARC_Win->u16H_CapSize & 0xFF00) >> 8) & 0x00FF );
        mbxMsg.u8Parameters[3]      = (U8)( pstMHEG5_ARC_Win->u16V_CapSize & 0x00FF );
        mbxMsg.u8Parameters[4]      = (U8)( ((pstMHEG5_ARC_Win->u16V_CapSize & 0xFF00) >> 8) & 0x00FF );

        #if (MHEG5_X_STRETCH_WAY == MHEG5_USE_GE_STRETCH)
        mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_ARC_Win->u16H_DisSize & 0x00FF );
        mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_ARC_Win->u16H_DisSize & 0xFF00) >> 8) & 0x00FF );
        #else
            #if GOP_SCALERATIO_FIXED
            mbxMsg.u8Parameters[5]      = (U8)( (pstMHEG5_ARC_Win->u16H_DisSize/2) & 0x00FF );
            mbxMsg.u8Parameters[6]      = (U8)( (((pstMHEG5_ARC_Win->u16H_DisSize/2) & 0xFF00) >> 8) & 0x00FF );
            #else
            mbxMsg.u8Parameters[5]      = (U8)( pstMHEG5_ARC_Win->u16H_CapSize & 0x00FF );
            mbxMsg.u8Parameters[6]      = (U8)( ((pstMHEG5_ARC_Win->u16H_CapSize & 0xFF00) >> 8) & 0x00FF );
            #endif
        #endif

        #if (MHEG5_Y_STRETCH_WAY == MHEG5_USE_GE_STRETCH)
            mbxMsg.u8Parameters[7]      = (U8)( pstMHEG5_ARC_Win->u16V_DisSize & 0x00FF );
            mbxMsg.u8Parameters[8]      = (U8)( ((pstMHEG5_ARC_Win->u16V_DisSize & 0xFF00) >> 8) & 0x00FF );
        #else
            mbxMsg.u8Parameters[7]      = (U8)( (pstMHEG5_ARC_Win->u16V_DisSize/2) & 0x00FF );
            mbxMsg.u8Parameters[8]      = (U8)( (((pstMHEG5_ARC_Win->u16V_DisSize/2) & 0xFF00) >> 8) & 0x00FF );
        #endif

        mbxMsg.u8Parameters[9]      = u8AFD;

        M5DBG(printf("MEHG-ARC-CapSize :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_ARC_Win->u16H_CapSize,pstMHEG5_ARC_Win->u16V_CapSize));
        M5DBG(printf("MEHG-ARC-DisSize :\n"));
        M5DBG(printf("H: %d  V : %d \n",pstMHEG5_ARC_Win->u16H_DisSize,pstMHEG5_ARC_Win->u16V_DisSize));


        //printf("send ARC CAP:(%u,%u,%u,%u) DSP(%u,%u,%u,%u)\n",pstMHEG5_ARC_Win->u16H_CapStart,pstMHEG5_ARC_Win->u16V_CapStart,pstMHEG5_ARC_Win->u16H_CapSize,pstMHEG5_ARC_Win->u16V_CapSize,pstMHEG5_ARC_Win->u16H_DisStart,pstMHEG5_ARC_Win->u16V_DisStart,pstMHEG5_ARC_Win->u16H_DisSize,pstMHEG5_ARC_Win->u16V_DisSize);
    }

    while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

    MsOS_DelayTask(50);
/*
    if ( msAPI_MHEG5_IsRunning()==TRUE && g_MHEG5Video.bIFrame )
    {
        //msAPI_IFrame_Cal_Window(OPTION_CHANGE_ARC);
        msAPI_MHEG5_VID_SetWindowInfo(TRUE,FALSE);
        msAPI_Scaler_SetTimingAndWindow ( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));

    }*/
#if (MHEG5_ENABLE)//request the GE mutex back to 51
        if(MHEG5_WITH_OSD == 1 && msAPI_MHEG5_checkGoBackMHEG5() == true)
        {

            msAPI_Timer_Delayms(100);

            MApi_GOP_GWIN_Switch2Gwin(u8CurGWIN);
            msAPI_OSD_RestoreBackupClipWindow();  // 20071211 Justin Yang for Q.Menu cut the half of highlight
        }
#endif

}
#endif

/******************************************************************************/
/// This API will check if the video action is the same as before
/// @return BOOLEAN - TRUE : if video action is the same as before
/******************************************************************************/
BOOLEAN msAPI_MHEG5_VID_IsSameVideoAction( MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction, MS_MHEG5_VIDEO_ACTION *pstPrevMHEG5VideoAction)
{

    //printf("SW %u %u\n", pstMHEG5VideoAction->u16Scale_Width, pstPrevMHEG5VideoAction->u16Scale_Width);
    //printf("SH %u %u\n", pstMHEG5VideoAction->u16Scale_Height, pstPrevMHEG5VideoAction->u16Scale_Height);
    //printf("BX %u %u\n", pstMHEG5VideoAction->u16BoxSize_X, pstPrevMHEG5VideoAction->u16BoxSize_X);
    //printf("BY %u %u\n", pstMHEG5VideoAction->u16BoxSize_Y, pstPrevMHEG5VideoAction->u16BoxSize_Y);
    //printf("PX %d %d\n", pstMHEG5VideoAction->s16Position_X, pstPrevMHEG5VideoAction->s16Position_X);
    //printf("PY %d %d\n", pstMHEG5VideoAction->s16Position_Y, pstPrevMHEG5VideoAction->s16Position_Y);
    //printf("OX %d %d\n", pstMHEG5VideoAction->s16VideoOffset_X, pstPrevMHEG5VideoAction->s16VideoOffset_X);
    //printf("OY %d %d\n", pstMHEG5VideoAction->s16VideoOffset_Y, pstPrevMHEG5VideoAction->s16VideoOffset_Y);


    if ( (pstPrevMHEG5VideoAction->u16Scale_Width == pstMHEG5VideoAction->u16Scale_Width) &&
         (pstPrevMHEG5VideoAction->u16Scale_Height == pstMHEG5VideoAction->u16Scale_Height) &&
         (pstPrevMHEG5VideoAction->u16BoxSize_X == pstMHEG5VideoAction->u16BoxSize_X) &&
         (pstPrevMHEG5VideoAction->u16BoxSize_Y == pstMHEG5VideoAction->u16BoxSize_Y) &&
         (pstPrevMHEG5VideoAction->s16Position_X == pstMHEG5VideoAction->s16Position_X) &&
         (pstPrevMHEG5VideoAction->s16Position_Y == pstMHEG5VideoAction->s16Position_Y) &&
         (pstPrevMHEG5VideoAction->s16VideoOffset_X == pstMHEG5VideoAction->s16VideoOffset_X) &&
         (pstPrevMHEG5VideoAction->s16VideoOffset_Y == pstMHEG5VideoAction->s16VideoOffset_Y) )

    {
        return TRUE;
    }
    else if( (pstPrevMHEG5VideoAction->u16Scale_Width == 0xFFFF) &&
         (pstPrevMHEG5VideoAction->u16Scale_Height == 0xFFFF) &&
         (pstPrevMHEG5VideoAction->u16BoxSize_X == 0xFFFF) &&
         (pstPrevMHEG5VideoAction->u16BoxSize_Y == 0xFFFF) &&
         (pstPrevMHEG5VideoAction->s16Position_X == 0x7FFF) &&
         (pstPrevMHEG5VideoAction->s16Position_Y == 0x7FFF) &&
         (pstPrevMHEG5VideoAction->s16VideoOffset_X == 0x7FFF) &&
         (pstPrevMHEG5VideoAction->s16VideoOffset_Y == 0x7FFF) &&
         (msAPI_VID_GetPlayMode()== MSAPI_VID_PLAY) &&
         (pstMHEG5VideoAction->u16BoxSize_X == MHEG_XRES_COORD) &&
         (pstMHEG5VideoAction->u16BoxSize_Y == MHEG_YRES_COORD) &&
         (pstMHEG5VideoAction->s16Position_X == 0) &&
         (pstMHEG5VideoAction->s16Position_Y == 0) &&
         (pstMHEG5VideoAction->s16VideoOffset_X == 0) &&
         (pstMHEG5VideoAction->s16VideoOffset_Y == 0) )
    {
        if ( ((pstMHEG5VideoAction->u16Scale_Width == 0) &&
              (pstMHEG5VideoAction->u16Scale_Height == 0)) ||
             ((pstMHEG5VideoAction->u16Scale_Width == MHEG_XRES_COORD) &&
              (pstMHEG5VideoAction->u16Scale_Height == MHEG_YRES_COORD)) )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

}

/******************************************************************************/
/// This API will check if the video is full
/// @parameter pstMHEG5VideoAction \b : IN video action to check if it is full
/// @return BOOLEAN - TRUE : if video action is full
/******************************************************************************/
BOOLEAN msAPI_MHEG5_VID_IsFullScreen( MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction )
{

    if ( (pstMHEG5VideoAction->u16BoxSize_X     == MHEG_XRES_COORD)   && (pstMHEG5VideoAction->u16BoxSize_Y       == MHEG_YRES_COORD) &&
         (pstMHEG5VideoAction->u16Scale_Width   == MHEG_XRES_COORD)   && (pstMHEG5VideoAction->u16Scale_Height    == MHEG_YRES_COORD) &&
         (pstMHEG5VideoAction->s16Position_X    == 0)           && (pstMHEG5VideoAction->s16Position_Y      == 0) &&
         (pstMHEG5VideoAction->s16VideoOffset_X == 0)           && (pstMHEG5VideoAction->s16VideoOffset_Y   == 0))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************/
/// This API will check if the video is i-frame
/// @return BOOLEAN - TRUE : if video is i-frame
/******************************************************************************/
BOOLEAN msAPI_MHEG5_IsIFrameExist()
{
    return ( g_MHEG5Video.bIFrame);
}

/******************************************************************************/
//                                                             Local functions
/* ****************************************************************************/
/******************************************************************************/
/// @internal
///- This API will set Audio volume
/// @param dbLevel \b IN: Set Audio volume
/* ****************************************************************************/
void msAPI_MHEG_AUD_SetVolume(S32 dbLevel)
{
    //printf("dbLevel %ld\n", dbLevel);

    if (stGenSetting.g_SoundSetting.Volume + dbLevel < 0)
    {
        // MHEG Ap Mute
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MHEGAP_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    else
    {
        U8 u8Volume = 0;

        if (stGenSetting.g_SoundSetting.Volume + dbLevel >100)
        {
            u8Volume = 100;
        }
        else
        {
            u8Volume = stGenSetting.g_SoundSetting.Volume + dbLevel;
        }

        // change volume, but not update ui
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, u8Volume, 0);

        // MHEG AP UnMute
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MHEGAP_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    }
}

/******************************************************************************/
/// @internal
///- This function will read mail box for MHEG-5 Audio
/// @param paramNum \b IN: parameter number
/// @return WORD: mailbox data read back
/* ****************************************************************************/
U32 msAPI_MHEG_AUD_ReadMailBox(BYTE paramNum)
{
    return (U32)MDrv_AUDIO_ReadDecMailBox(paramNum);
}

/******************************************************************************/
/// @internal
///- This function will write mail box for MHEG-5 Audio
/// @param paramNum \b IN: parameter number
/// @param data1 \b IN: mailbox data to write
/* ****************************************************************************/
void msAPI_MHEG_AUD_WriteMailBox(BYTE paramNum, WORD data1)
{
    MDrv_AUDIO_WriteDecMailBox(paramNum, data1);
}

/******************************************************************************/
/// @internal
///- initialize MAD for MHEG-5 Audio
/// @param cmd \b IN: Command
/* ****************************************************************************/
void msAPI_MHEG_AUD_IntMAD(WORD cmd)
{
    MDrv_AUDIO_FwTriggerDSP(cmd);
}


/******************************************************************************/
/// @internal
///- MHEG-5 Audio process mailbox
/// @param *u8AeonMailBox \b IN: Pointer to Aeon mail box data
/* ****************************************************************************/
void msAPI_MHEG_AUD_ProcessMailbox(U8 *u8AeonMailBox)
{
    S32 s32TmpVolume;
    S32 s32AudioPid;

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
    BOOL    bShortMuteTime = 0;
#endif

    if (u8AeonMailBox[1] == AUD_MAILBOX_CLASS_COMMON)    // stop, play, resync
    {
        switch (u8AeonMailBox[2])
        {
            case MSAPI_AUD_AEON_CMD_51_DECCMD_STOP_FILEPLAY:
            case MSAPI_AUD_AEON_CMD_51_DECCMD_STOP:
#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                if (u8AeonMailBox[2] == MSAPI_AUD_AEON_CMD_51_DECCMD_STOP_FILEPLAY)
                {
                    bShortMuteTime = 1;
                }

                // do mute protection to avoid noise
                if (bShortMuteTime)
                {
                    // set mute no delay
                    msAPI_AUD_SetByPassDelayFlag(TRUE);
                }
#endif

                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);//MDrv_MAD_SetDecCmd(AU_DVB_DECCMD_STOP);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                if (bShortMuteTime)
                {
                    // reset mute delay as default
                    msAPI_AUD_SetByPassDelayFlag(FALSE);
                }
#endif

                //printf("AUD STOP\n");
                g_u16Current_AudioPID |= 0x4000;
                break;

            case MSAPI_AUD_AEON_CMD_51_DECCMD_PLAY:
                #if (ENABLE_PVR == 1)
                if(!(((MApp_TimeShift_StateMachineGet()==E_TIMESHIFT_STATE_RECORDING) && MApp_TimeShift_IfPause())
                || (MApp_Playback_StateMachineGet()==E_PLAYBACK_STATE_PAUSE)))
                #endif
                {
                    if(MApi_AUDIO_GetDecStatus() != MSAPI_AUD_DVB_DECCMD_PLAY)
                    {
                        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);//MDrv_MAD_SetDecCmd(AU_DVB_DECCMD_PLAY);
                    }
                }
                g_u16Current_AudioPID &= ~0x4000;
                //printf("AUD PLAY\n");
                break;

            case MSAPI_AUD_AEON_CMD_51_SETVOLUME:
                s32TmpVolume = (((S32)u8AeonMailBox[3])<<24)|(((S32)u8AeonMailBox[4])<<16)|(((S32)u8AeonMailBox[5])<<8)|u8AeonMailBox[6];
                //printf("%bu %bu %bu %bu\n", u8AeonMailBox[3], u8AeonMailBox[4], u8AeonMailBox[5], u8AeonMailBox[6]);
                //printf("setVolume %lu\n", s32TmpVolume);
                msAPI_MHEG_AUD_SetVolume(s32TmpVolume);
                break;

            case MSAPI_AUD_AEON_CMD_51_SET_PID:
                s32AudioPid = (((S32)u8AeonMailBox[3])<<24)|(((S32)u8AeonMailBox[4])<<16)|(((S32)u8AeonMailBox[5])<<8)|u8AeonMailBox[6];
                //printf("msAPI_MHEG_AUD_ProcessMailbox: PID= %lu\n", s32AudioPid);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
                msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_AUDIO_FID));

                // start filter should be after than start audio decoder to prevent audio ES buffer overflow
                /* set audio PID & start filter */
                msAPI_DMX_StartFilter( s32AudioPid, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID) );

                /* start audio decoder */
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
                msAPI_Timer_Delayms(10);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                g_u16Current_AudioPID = s32AudioPid&~0xE000;
                g_u16Current_AudioPID &= ~0x4000;
                break;

            default:
                break;
        }
    }
    else if (u8AeonMailBox[1] == AUD_MAILBOX_CLASS_MHEG5)   //playfile
    {
        switch (u8AeonMailBox[2])
        {
            case MSAPI_AUD_AEON_CMD_51_DECCMD_CONTINUE:
                //printf("continue\n");

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                msAPI_AUD_SetByPassDelayFlag(TRUE); // no time delay when audio mute on/off
#endif

                // do mute protection to avoid audio noise
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);//MDrv_MAD_SetDecCmd(AU_DVB_DECCMD_PLAYFILE);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                msAPI_AUD_SetByPassDelayFlag(FALSE);    // reset time delay when audio mute on/off
#endif

                break;

            case MSAPI_AUD_AEON_CMD_51_DECCMD_PAUSE:
                //printf("pause\n");

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                msAPI_AUD_SetByPassDelayFlag(TRUE); // no time delay when audio mute on/off
#endif

                // do mute protection to avoid audio noise
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PAUSE);//MDrv_MAD_SetDecCmd(AU_DVB_DECCMD_PAUSE);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                msAPI_AUD_SetByPassDelayFlag(FALSE);    // reset time delay when audio mute on/off
#endif

                break;

            case MSAPI_AUD_AEON_CMD_51_DECCMD_PLAYFILE:
                // loop
                Mheg5AudioFileParams.u32MHEGAudioLoopCounts =
                    (((U32)u8AeonMailBox[3])<<24)|(((U32)u8AeonMailBox[4])<<16)|(((U32)u8AeonMailBox[5])<<8)|u8AeonMailBox[6];

                if (Mheg5AudioFileParams.u32MHEGAudioLoopCounts==0)
                {
                    Mheg5AudioFileParams.u8MHEGAudioIsInfinite = 1;
                }
                else
                {
                    Mheg5AudioFileParams.u8MHEGAudioIsInfinite = 0;
                }

                Mheg5AudioFileParams.u32MHEGAudioFileIndex = 0;

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                msAPI_AUD_SetByPassDelayFlag(TRUE);    // set no time delay when audio mute on/off
#endif

                // mute on
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);//MDrv_MAD_SetDecCmd(AU_DVB_DECCMD_PLAYFILE);

                // mute off
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

#if (ENABLE_CHANNEL_CHANGE_MUTE_ON_OFF_DELAY)
                msAPI_AUD_SetByPassDelayFlag(FALSE);    // reset time delay when audio mute on/off
#endif

                g_u16Current_AudioPID |= 0x4000;
                break;

            case MSAPI_AUD_AEON_CMD_51_DECCMD_PLAYFILE_PARAM:
                // just get param, don't cmd MAD to do something
                // addr
                Mheg5AudioFileParams.u32MHEGAudioAddr =
                    (((U32)u8AeonMailBox[3])<<24)|(((U32)u8AeonMailBox[4])<<16)|(((U32)u8AeonMailBox[5])<<8)|u8AeonMailBox[6];
                // length
                Mheg5AudioFileParams.u32MHEGAudioLength = (((U32)u8AeonMailBox[7])<<24)|(((U32)u8AeonMailBox[8])<<16)|(((U32)u8AeonMailBox[9])<<8)|u8AeonMailBox[10];
                //printf("AUD PLAYFILE %LX, %Lu\n", Mheg5AudioFileParams.u32MHEGAudioAddr, Mheg5AudioFileParams.u32MHEGAudioLength);

                Mheg5AudioFileParams.u8MHEG5AudioBeDecoded = 0;

                /* [MHEG5 SD] Test case 3.5.3 Audio File Formats - Scene 3                                                                      */
                /* If IP Using Memory copy to DDR to playback audio file, like MM(MHEG5)/DTV/HDMI through R2 processor.    */
                /* Need send below audio play command to trigger audio file output sound.                                                 */
                /* Reference audio bank 0x112E_98 bit 15-10                                                                                          */
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILETSP);
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                break;

            default:
                break;
        }
    }
}

/******************************************************************************/
/// @internal
///- MHEG-5 Audio Stream stop event.
/* ****************************************************************************/
static void msAPI_MHEG_AUD_StreamStoppedEvent(void)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_AUDIO
    /*Index*/           ,0
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01

    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
/// @internal
///- This API will send mailbox to tell aeon to clear buffer when feeding data in aeon.
/* ****************************************************************************/

BOOL msAPI_MHEG_AUD_AEONClearBuffer(U32 addr, U16 number, U8 paddata)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MAD
    /*Index*/           ,0x01
    /*MsgType*/         ,OBA_MSG_TYPE
    /*ParameterCount*/  ,0x07

    /*p1*/              ,(U8)(addr       & 0xFF)
    /*p2*/              ,(U8)((addr>>8)  & 0xFF)
    /*p3*/              ,(U8)(number & 0xFF)
    /*p4*/              ,(U8)((number>>8) & 0xFF)
    /*p5*/              ,(U8)(paddata)
    /*p6*/              ,(U8)((addr>>16) & 0xFF)
    /*p7*/              ,(U8)((addr>>24) & 0xFF)
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;
}

/******************************************************************************/
/// @internal
///- This API will send mailbox to Aeon for feeding data to MAD.
/* ****************************************************************************/
BOOL msAPI_MHEG_AUD_AEONFeedMAD(U32 addr, U16 number, U32 u32Index)
{


    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
     M5_MAILBOX_SEND(    E_MBX_CLASS_MAD
    /*Index*/           ,0x00
    /*MsgType*/         ,OBA_MSG_TYPE
    /*ParameterCount*/  ,0x0a

    /*p1*/              ,(U8)(addr       & 0xFF)
    /*p2*/              ,(U8)((addr>>8)  & 0xFF)
    /*p3*/              ,(U8)(number & 0xFF)
    /*p4*/              ,(U8)((number>>8) & 0xFF)
    /*p5*/              ,(U8)(u32Index        & 0xFF)
    /*p6*/              ,(U8)((u32Index>>8)   & 0xFF)
    /*p7*/              ,(U8)((u32Index>>16)  & 0xFF)
    /*p8*/              ,(U8)((u32Index>>24)  & 0xFF)
    /*p9*/              ,(U8)((addr>>16) & 0xFF)
    /*p10*/             ,(U8)((addr>>24) & 0xFF));


    return TRUE;
}

/******************************************************************************/
///- This API will reset video scaling settings in MHEG
/*****************************************************************************/
void msAPI_MHEG5_VID_ResetScaleSize( void )
{
    MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction = &g_MHEG5Video.stMHEG5VideoAction;
    //MS_MHEG5_VIDEO_ACTION *pstPrevMHEG5VideoAction = &g_MHEG5Video.stPrevMHEG5VideoAction;



    if ( (pstMHEG5VideoAction->u16Scale_Width == 0) || (pstMHEG5VideoAction->u16Scale_Height == 0) )
    {

        pstMHEG5VideoAction->u16Scale_Width = MHEG_XRES_COORD;
        pstMHEG5VideoAction->u16Scale_Height = MHEG_YRES_COORD;

    }
}

/******************************************************************************/
///- This API will reset video box settings in MHEG
/*****************************************************************************/
void msAPI_MHEG5_VID_ResetBoxSize( void )
{
    MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction = &g_MHEG5Video.stMHEG5VideoAction;


    if ( !(g_MHEG5Video.u8VideoFlag & EVER_SET_VIDEO_BOX_SIZE) )
    {
        pstMHEG5VideoAction->u16BoxSize_X = pstMHEG5VideoAction->u16Scale_Width;
        pstMHEG5VideoAction->u16BoxSize_Y = pstMHEG5VideoAction->u16Scale_Height;
    }
    else
    {
        if ( pstMHEG5VideoAction->u16BoxSize_X > pstMHEG5VideoAction->u16Scale_Width )
            pstMHEG5VideoAction->u16BoxSize_X = pstMHEG5VideoAction->u16Scale_Width;


        if ( pstMHEG5VideoAction->u16BoxSize_Y > pstMHEG5VideoAction->u16Scale_Height )
            pstMHEG5VideoAction->u16BoxSize_Y = pstMHEG5VideoAction->u16Scale_Height;
    }
}

/******************************************************************************/
///- This API will check the valid of channel in MHEG
/// @param eCmdType \b IN: service type
/// @param u16InputValue \b IN: input value to be checked
/// @return BOOLEAN - TRUE: if channel is valid
/*****************************************************************************/
BOOLEAN msAPI_MHEG5_ServiceValidChecking(MB_SERVICE_CMD eCmdType, U16 u16InputValue, U16 u16InputValue2, U16 u16InputValue3, U16 *u16OutputValue, U16 *u16OutputValue2, U16 *u16OutputValue3, U8 *u8IsValid)
{
    U16 u16Value;
    U16 u16Loop,U16LoopEnd;
    U16LoopEnd = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

    // video
    //printf("1..%u %u %u\n",u16InputValue,u16InputValue2,u16InputValue3);
    for ( u16Loop = 0; u16Loop < U16LoopEnd; u16Loop++ )
    {
        u16Value = (eCmdType == MB_SERVICE_CMD_LCN) ? msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV, u16Loop) : msAPI_CM_GetService_ID(E_SERVICETYPE_DTV, u16Loop);
        if ( u16InputValue == u16Value )
        {
            if((eCmdType == MB_SERVICE_CMD_LCN) && !msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV,u16Loop, E_ATTRIBUTE_IS_LCN_VALID))
            {
                break;
            }
            *u16OutputValue = msAPI_CM_GetService_ID(E_SERVICETYPE_DTV,u16Loop);
            *u16OutputValue2 = msAPI_CM_GetON_ID(E_SERVICETYPE_DTV, u16Loop);
            *u16OutputValue3 = msAPI_CM_GetTS_ID(E_SERVICETYPE_DTV, u16Loop);
            *u8IsValid = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV,u16Loop, E_ATTRIBUTE_IS_DELETED) ? 0 : 1;

            if ((eCmdType == MB_SERVICE_CMD_SERVICE_ID)||(eCmdType == MB_SERVICE_CMD_SERVICE_ID_PLUS_CHECKTSID))
            {
                // check onid
                if (*u16OutputValue2 == u16InputValue2)
                {
                    if ((!msAPI_CM_IS_SID_Unique_Country())&&(eCmdType == MB_SERVICE_CMD_SERVICE_ID_PLUS_CHECKTSID))
                    {
                        if (*u16OutputValue3 == u16InputValue3)
                        {
                            return TRUE;
                        }
                    }
                    else
                    {
                        return TRUE;
                    }
                }

            }
            else
                return TRUE;
        }
    }
    // audio
    if ( u16Loop >= U16LoopEnd )
    {
        U16LoopEnd = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

        for ( u16Loop = 0; u16Loop < U16LoopEnd; u16Loop++ )
        {
            u16Value = (eCmdType == MB_SERVICE_CMD_LCN) ? msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_RADIO,u16Loop) : msAPI_CM_GetService_ID(E_SERVICETYPE_RADIO,u16Loop);
            if(u16InputValue == u16Value)
            {
                if((eCmdType == MB_SERVICE_CMD_LCN) && !msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO,u16Loop, E_ATTRIBUTE_IS_LCN_VALID))
                {
                    break;
                }
                *u16OutputValue = msAPI_CM_GetService_ID(E_SERVICETYPE_RADIO,u16Loop);
                *u16OutputValue2 = msAPI_CM_GetON_ID(E_SERVICETYPE_RADIO, u16Loop);
                *u16OutputValue3 = msAPI_CM_GetTS_ID(E_SERVICETYPE_RADIO, u16Loop);
                *u8IsValid = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV,u16Loop, E_ATTRIBUTE_IS_DELETED) ? 0 : 1;

                if ((eCmdType == MB_SERVICE_CMD_SERVICE_ID)||(eCmdType == MB_SERVICE_CMD_SERVICE_ID_PLUS_CHECKTSID))
                {
                    // check onid
                    if (*u16OutputValue2 == u16InputValue2)
                    {
                        if ((!msAPI_CM_IS_SID_Unique_Country())&&(eCmdType == MB_SERVICE_CMD_SERVICE_ID_PLUS_CHECKTSID))
                        {
                            if (*u16OutputValue3 == u16InputValue3)
                            {
                                return TRUE;
                            }
                        }
                        else
                        {
                            return TRUE;
                        }
                    }
                }
                else
                    return TRUE;
            }
        }
    }
    #if NORDIG_FUNC //for Nordig Spec v2.0
    if ( u16Loop >= U16LoopEnd )
    {
        U16LoopEnd = msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

        for ( u16Loop = 0; u16Loop < U16LoopEnd; u16Loop++ )
        {
            u16Value = (eCmdType == MB_SERVICE_CMD_LCN) ? msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DATA,u16Loop) : msAPI_CM_GetService_ID(E_SERVICETYPE_DATA,u16Loop);
            if(u16InputValue == u16Value)
            {
                if((eCmdType == MB_SERVICE_CMD_LCN) && !msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA,u16Loop, E_ATTRIBUTE_IS_LCN_VALID))
                {
                    break;
                }
                *u16OutputValue = msAPI_CM_GetService_ID(E_SERVICETYPE_DATA,u16Loop);
                *u16OutputValue2 = msAPI_CM_GetON_ID(E_SERVICETYPE_DATA, u16Loop);
                *u16OutputValue3 = msAPI_CM_GetTS_ID(E_SERVICETYPE_DATA, u16Loop);
                *u8IsValid = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV,u16Loop, E_ATTRIBUTE_IS_DELETED) ? 0 : 1;

                if ((eCmdType == MB_SERVICE_CMD_SERVICE_ID)||(eCmdType == MB_SERVICE_CMD_SERVICE_ID_PLUS_CHECKTSID))
                {
                    // check onid
                    if (*u16OutputValue2 == u16InputValue2)
                    {
                        if ((!msAPI_CM_IS_SID_Unique_Country())&&(eCmdType == MB_SERVICE_CMD_SERVICE_ID_PLUS_CHECKTSID))
                        {
                            if (*u16OutputValue3 == u16InputValue3)
                            {
                                return TRUE;
                            }
                        }
                        else
                        {
                            return TRUE;
                        }
                    }
                }
                else
                    return TRUE;
            }
        }
    }
    #endif
    return FALSE;

}


// IN -- GE buffer format
// OUT -- GE buffer ID and GE buffer attribute
/******************************************************************************/
///- This API will create framebuffer in MHEG
/// @param gefmt \b IN: current ge format
/// @param fbAttr \b IN: frame buffer structure
/// @param width \b IN: length in x
/// @param height \b IN: length in y
/// @param fbAddr \b IN: frame buffer address
/// @param fbId \b IN: frame buffer if
/// @return U8 - not used
/*****************************************************************************/
U8 msAPI_MHEG5_CreateFrameBuffer(GFX_Buffer_Format gefmt, GOP_GwinFBAttr *fbAttr, U16 width, U16 height, U32 *fbAddr, U8 *fbId)
{
    U8 u8FBID = MApi_GOP_GWIN_GetFreeFBID();

#if MHEG5_STATIC_FB
    MApi_GOP_GWIN_CreateFBbyStaticAddr(u8FBID, 0, 0, width, height, gefmt, MHEG5_STATIC_DLA_FB_ADDR);
#else
    MApi_GOP_GWIN_CreateFB(u8FBID, 0, 0, width, height, gefmt);
#endif

    MApi_GOP_GWIN_GetFBInfo(u8FBID,  fbAttr);

    *fbAddr    = fbAttr->addr;
    *fbId    = u8FBID;

    return u8FBID;
}


/******************************************************************************/
///- This API will get frame buffer address for DynamicLineArt in MHEG
/******************************************************************************/
U32 msAPI_MHEG5_GetDLAFBAddress()
{
    return u32DLABufferAddress;
}

/******************************************************************************/
///- This API will update frame buffer address from GOP re-arrange
/******************************************************************************/
void msAPI_MHEG5_UpdateDLAFBAddress(U32 u32DLABufferAddress_update)
{
    u32DLABufferAddress = u32DLABufferAddress_update;
}

/******************************************************************************/
///- This API will get MHEG-5 bin status
/******************************************************************************/
BOOLEAN msAPI_MHEG5_GetBinStatus(void)
{
    return bMHEG5Bin;
}

/******************************************************************************/
///- This API will set MHEG-5 bin status
/******************************************************************************/
void msAPI_MHEG5_SetBinStatus(BOOLEAN status)
{
    if((status == FALSE) && (_bDsmccExit == FALSE))
    {
        MS_DEBUG_MSG(printf("\n\n/*************warning! DSMCC not exit************/\n\n"));
    }
    bMHEG5Bin = status;
#if CSA_ENABLE
    msAPI_DMX_CSA_Enable(status,MHEG5_DEMUX_FILTER);
#endif
}
/******************************************************************************/
/// API for MHEG5 to set Drawing flag
/******************************************************************************/
void M5API_GFX_SetMHEGDrawFlag(bool bDrawing)
{
    bMHEG5Drawing = bDrawing;
}
/******************************************************************************/
///- This API tells us if MHEG-5 Engine draws anything on screen
/******************************************************************************/
BOOLEAN msAPI_MHEG5_IsMHEGDraw(void)
{
    return (bMHEG5Running && bMHEG5Drawing);
}

/******************************************************************************/
///- This API tells us if MHEG-5 Engine draws anything on screen
/******************************************************************************/
//When MB receive "MB_MHEG5_STATE_DRAW_EVENT" msg, it will call this callback function.
void msAPI_MHEG5_SetDrawingCallback(CALLBACK callback)
{
    _mheg5EventHandle.DrawingCallback = callback;
}


/******************************************************************************/
///- This API will tell MHEG-5 engine to use GE semaphore
/*****************************************************************************/
void msAPI_MHEG5_UseGeSemaphore()
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_SEMAPHORE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01

    /*p1*/              ,GE_CONTROL_BY_SEMAPHORE
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
/// This API will change the color of on-screen buffer in MHEG-5
/// If we want to change the background color of on-screen buffer in projects such as PDP,
/// We need to call this function in MApp_MHEG5_Init()
/// If we want to use this api, we need version of mheg5_LE.bin > 40816
/// @param u32Color \b IN: backgound color
/*****************************************************************************/
void msAPI_MHEG5_ChangeOSBackgroundColor(U32 u32Color)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_OS_BAK_COLOR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x04

    /*p1*/              ,(U8)(u32Color&0xFF)
    /*p2*/              ,(U8)((u32Color>>8) & 0xFF)
    /*p3*/              ,(U8)((u32Color>>16) & 0xFF)
    /*p4*/              ,(U8)((u32Color>>24) & 0xFF)
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);


}

/******************************************************************************/
///- This API will send command to make MHEG-5 engine to close and destroy all current MHEG-5 OSD
/*****************************************************************************/
void msAPI_MHEG5_QuitOSD()
{


    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(E_MBX_CLASS_INPUT
    /*Index*/           ,MB_INPUT_CMD_IR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x03

    /*p1*/              ,KEY_EXIT
    /*p2*/              ,KEY_EXIT
    /*p3*/              ,KEY_EXIT
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}


/******************************************************************************/
///- This API will send render target format, panel width and panel height to initialize mheg engine
/*****************************************************************************/
void msAPI_MHEG5_SendPanelInfo()
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_PNL_INFO
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x05

    /*p1*/              ,MHEG5_RenderTarget_Fmt
    /*p2*/              ,PANEL_WIDTH&0xFF
    /*p3*/              ,(PANEL_WIDTH>>8)&0xFF
    /*p4*/              ,PANEL_HEIGHT&0xFF
    /*p5*/              ,(PANEL_HEIGHT>>8)&0xFF
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

static U16 currAudioPid = 0x1FFF;

/******************************************************************************/
///- This API will send panel aspect ratio, on-screen width/height, and audio pid to MHEG-5 for passing DTG 6.6
/// @param u32Width \b IN: on-screen width
/// @param u32Height \b IN: on-screen height
/// @param u16AudioPid \b IN: audio pid
/*****************************************************************************/
void msAPI_MHEG5_SendOSWidthHeight_AudioPid_PanelRatio(U32 u32Width, U32 u32Height, U16 u16AudioPid, U16 u16VideoPid)
{
    U8 u8panelratio;

    if (currAudioPid != u16AudioPid)
    {
        currAudioPid = u16AudioPid;
    }

    if(g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3)
    {
        u8panelratio = 0;
    }
    else if(g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE)
    {
        u8panelratio = 1;
    }
    else if(g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_OTHER)
    {
        u8panelratio = 2;
    }
    else
    {
        u8panelratio = 1;
    }

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
#if CIPLUS_MHEG
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_AUD_PID_PNL_RATIO
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x0A

    /*p1*/              ,MHEG5_RenderTarget_Fmt
    /*p2*/              ,u32Width&0xFF
    /*p3*/              ,(u32Width>>8)&0xFF
    /*p4*/              ,u32Height&0xFF
    /*p5*/              ,(u32Height>>8)&0xFF
    /*p6*/              ,u16AudioPid & 0xFF
    /*p7*/              ,(u16AudioPid >> 8) & 0xFF
    /*p8*/              ,u8panelratio
    /*p9*/              ,u16VideoPid & 0xFF
    /*p10*/             ,(u16VideoPid >> 8) & 0xFF);

#else
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_AUD_PID_PNL_RATIO
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x08

    /*p1*/              ,MHEG5_RenderTarget_Fmt
    /*p2*/              ,u32Width&0xFF
    /*p3*/              ,(u32Width>>8)&0xFF
    /*p4*/              ,u32Height&0xFF
    /*p5*/              ,(u32Height>>8)&0xFF
    /*p6*/              ,u16AudioPid & 0xFF
    /*p7*/              ,(u16AudioPid >> 8) & 0xFF
    /*p8*/              ,u8panelratio
    /*p9*/              ,0
    /*p10*/             ,0);

    u16VideoPid = u16VideoPid;  // avoid warning only
#endif
}


/******************************************************************************/
///- This API will send panel aspect ratio, on-screen width/height, and audio pid to MHEG-5 for passing DTG 6.6
/// @param u32Width \b IN: on-screen width
/// @param u32Height \b IN: on-screen height
/// @param u16AudioPid \b IN: audio pid
/*****************************************************************************/
void msAPI_MHEG5_SendCurrentAudioPidType(U16 u16AudioPid)
{

    if (currAudioPid != u16AudioPid)
    {
        currAudioPid = u16AudioPid;

        M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
        /*Index*/           ,MB_MHEG5_STATE_CMD_UPDATE_CUR_AUDIO
        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
        /*ParameterCount*/  ,0x02

        /*p1*/              ,u16AudioPid & 0xFF
        /*p2*/              ,((U8)(u16AudioPid >> 8)) & 0xFF
        /*p3*/              ,0
        /*p4*/              ,0
        /*p5*/              ,0
        /*p6*/              ,0
        /*p7*/              ,0
        /*p8*/              ,0
        /*p9*/              ,0
        /*p10*/             ,0);
    }

}


/******************************************************************************/
///- This API will send frame buffer address and on-screen address to MHEG-5
/// @param u32FBAddr \b IN: frame buffer address
/// @param u32DRAMRBlkStart \b IN: on-screen buffer address
/*****************************************************************************/
void msAPI_MHEG5_SendFBGWinOSAddr(U32 u32FBAddr, U32 u32DRAMRBlkStart)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_OS_FB
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x08

    /*p1*/              ,u32FBAddr&0xFF
    /*p2*/              ,(u32FBAddr>>8)&0xFF
    /*p3*/              ,(u32FBAddr>>16)&0xFF
    /*p4*/              ,(u32FBAddr>>24)&0xFF
    /*p5*/              ,u32DRAMRBlkStart&0xFF
    /*p6*/              ,(u32DRAMRBlkStart>>8)&0xFF
    /*p7*/              ,(u32DRAMRBlkStart>>16)&0xFF
    /*p8*/              ,(u32DRAMRBlkStart>>24)&0xFF
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
///- This API will send frame buffer address for DynamicLineArt to MHEG-5
/// @param fbAttr \b IN: frame buffer
/*****************************************************************************/
void msAPI_MHEG5_SendDLAInfo(U32 fbAddr)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_DLA_FB
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x04

    /*p1*/              ,fbAddr&0xFF
    /*p2*/              ,(fbAddr>>8)&0xFF
    /*p3*/              ,(fbAddr>>16)&0xFF
    /*p4*/              ,(fbAddr>>24)&0xFF
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

static U8 msAPI_MHEG5_ConvertKey(U8 u8Key)
{
    MHEGKeyMapEntry *map = mheg_keymap;

    while(map->CoProcessor_key!=0 && map->HouseKeeping_key != u8Key)
    {
        map++;
    }

    if (map->CoProcessor_key != 0)  // i.e. found the corresponding key
    {
        //printf("found key.... %d\n", map->CoProcessor_key);
        return (U8)map->CoProcessor_key;
    }
    else    // not found
    {
        // return the original key value
        //printf("not found key .... %d\n", u8Key);
        return u8Key;
    }
}

/******************************************************************************/
///- This API is for transmitting IR key to MHEG-5
/// @param u8Key \b IN: IR Key to transmit
/// @param Status \b IN: status for Aeon
/******************************************************************************/
void msAPI_MHEG5_Key_Transmit(U8 u8Key, U8 Status)
{
    U8 u8MHEGKey = msAPI_MHEG5_ConvertKey(u8Key);

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_INPUT
    /*Index*/           ,MB_INPUT_CMD_IR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x03

    /*p1*/              ,u8MHEGKey
    /*p2*/              ,Status
    /*p3*/              ,MHEG5_HK_VER
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
///- This API will trigger DSMCC. (Starting MHEG-5 data processing)
/// @param u16PmtPid \b IN: PMT PID
/******************************************************************************/
void msAPI_MHEG5_TriggerDsmcc(U16 u16PmtPid)
{
    // If your country setting is Australia, return directly
    if (IS_NOT_MHEG5_COUNTRY(OSD_COUNTRY_SETTING))
    {
        return;
    }
    M5DBG(printf("msAPI_MHEG5_TriggerDsmcc\n"));
    U8 u8MailBoxIndex = MB_TSP_CMD_ADD_PID;
#if CIPLUS_MHEG
    // do not trigger dsmcc when cimheg already runs
    if (msAPI_IsCIMHEGRun() == E_MHEG_CI_RUNNING)
    {
        //printf("tirgger and return...\n");
        return;
    }

    //printf("trigger dsmcc....\n");
#endif
    if(msAPI_MHEG5_GetBinStatus() == FALSE)
    {
        ASSERT(0);
        return;
    }

#if MHEG5_NDT
    if (msAPI_MHEG5_BeWaitingNDTPid())
    {
        // reset this when normal mheg dsmcc trigger
        msAPI_MHEG5_WaitNDTPid(false);
    }
#endif
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_TSP
    /*Index*/           ,u8MailBoxIndex
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x0A

    /*p1*/              ,(U8)((u16PmtPid & 0xFF00) >> 8)
    /*p2*/              ,(U8)(u16PmtPid & 0x00FF)
    /*p3*/              ,(U8)((g_u16CurrentServiceID & 0xFF00) >> 8)
    /*p4*/              ,(U8)(g_u16CurrentServiceID & 0x00FF)
    /*p5*/              ,(U8)((g_wCurrentTS_ID & 0xFF00) >> 8)
    /*p6*/              ,(U8)(g_wCurrentTS_ID & 0x00FF)
    /*p7*/              ,(U8)0x01
    /*p8*/              ,(U8)((g_wCurrent_ONID & 0xFF00) >> 8)
    /*p9*/              ,(U8)(g_wCurrent_ONID & 0x00FF)
    /*p10*/             ,MHEG5_DEMUX_FILTER);// 1 : temp disable inverse filter
    _bDsmccExit=FALSE;
}

/******************************************************************************/
///- This API will Stop DSMCC (Stopping MHEG-5 dat processing)
/******************************************************************************/
void msAPI_MHEG5_StopDsmcc(BOOLEAN bWait)
{
    int wait=0;
    M5DBG(printf("msAPI_MHEG5_StopDsmcc\n"));

    if(msAPI_MHEG5_GetBinStatus() == FALSE)
    {
        printf("msAPI_MHEG5_StopDsmcc assert\n");
        ASSERT(0);
        return;
    }

#if 0//MHEG5_NDT
    if (msAPI_MHEG5_BeWaitingNDTPid())
    {
        return;
    }
#endif

        printf("M5_MAILBOX_SEND start\n");
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_TSP
    /*Index*/           ,MB_TSP_CMD_DEL_PID
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x00

    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

        printf("M5_MAILBOX_SEND end\n");
    if(bWait)
    {
        wait=0;

        while((wait++ < 50) && (_bDsmccExit==FALSE))
        {
            msAPI_Timer_Delayms(10);
        }
        if(_bDsmccExit==FALSE) {MS_DEBUG_MSG(printf("\n\n/************warning!wait DSMCC exit time out**********/\n\n"));}
    }

    printf("M5API_MBX_Clean start\n");
    //Clean MB MSG
    M5API_MBX_Clean();
    printf("M5API_MBX_Clean done\n");

    enCheckMHEGLoadingStatus=EN_MHEG5_WAIT;
}
/******************************************************************************/
/// This API will tell MHEG-5 Engine the current settings of ARC
/// @parameter OnlyRefresh \b : IN do video refresh or not
/******************************************************************************/
void msAPI_MHEG5_Send_ARC_Setting(BOOLEAN OnlyRefresh,BOOLEAN bGEDisplayfollowARC,BOOLEAN u8IFrameContorl,BOOLEAN bNeedGetDrawingEventByReg,BOOLEAN bNeedGetDrawingEventByMail)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_SETARC_SETTING
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x05

    /*p1*/              ,OnlyRefresh
    /*p2*/              ,bGEDisplayfollowARC
    /*p3*/              ,u8IFrameContorl            //TRUE -> IFrame size contorl follow video flow.
    /*p4*/              ,bNeedGetDrawingEventByReg
    /*p5*/              ,bNeedGetDrawingEventByMail
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
///- API for sending changestream information to MHEG5 Video
/******************************************************************************/
void msAPI_MHEG5_VID_Send_CHANGESTREAM(void)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_VIDEO
    /*Index*/           ,MB_VID_CMD_CHANGESTREAM
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x02

    /*p1*/              ,gstVidStatus.u8AFD
    /*p2*/              ,gstVidStatus.u8AspectRate
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
///- This API will destroy DynamicLineArt frame buffer
/******************************************************************************/
void msAPI_MHEG5_DestroyDLAFB()
{
    // clear DLA buffer address
    u32DLABufferAddress = 0;
    // destroy fb
    MApi_GOP_GWIN_DestroyFB(u8MHEG5_DLA_FBID);
    //printf("msAPI_MHEG5_DestroyDLAFB %bu\n", u8MHEG5_DLA_FBID);


    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_DLA_FB
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x04

    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}


/******************************************************************************/
///- This API send channel infomation to MHEG5 engin
/******************************************************************************/
void msAPI_MHEG5_SendChannelInfo(U8 bResult ,U16 u16ServiceID,U16 u16OnID,U16 u16TsID,U8 u8IsValid)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CHANNEL
    /*Index*/           ,(U8)bResult
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x07

    /*p1*/              ,((u16ServiceID & 0xFF00) >> 8)
    /*p2*/              ,(u16ServiceID & 0x00FF)
    // pass back onid to aeon
    /*p3*/              ,((u16OnID & 0xFF00) >> 8)
    /*p4*/              ,(u16OnID & 0x00FF)
    // pass back tsid to aeon
    /*p5*/              ,((u16TsID & 0xFF00) >> 8)
    /*p6*/              ,(u16TsID & 0x00FF)
    /*p7*/              ,u8IsValid
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
/// API for Set system base year
/******************************************************************************/

void msAPI_MHEG5_SetBaseYear(U16 u16BaseYear)
{
    _u16BaseYear = u16BaseYear;
}
/******************************************************************************/
/// API for IR key transmit::
/******************************************************************************/
void msAPI_MHEG5_SystemTime_Transmit(U32 u32SystemTime, S32 s32OffsetTime)
{
    M5_MAILBOX_SEND(    E_MBX_CLASS_SYSTEM
    /*Index*/           ,MB_SYS_CMD_SYS_TIMER
    /*MsgType*/         ,OBA_MSG_TYPE
    /*ParameterCount*/  ,0x0a

    /*p1*/              ,( u32SystemTime      & 0xFF)
    /*p2*/              ,((u32SystemTime>>8 ) & 0xFF)
    /*p3*/              ,((u32SystemTime>>16) & 0xFF)
    /*p4*/              ,((u32SystemTime>>24) & 0xFF)
    /*p5*/              ,( s32OffsetTime      & 0xFF)
    /*p6*/              ,((s32OffsetTime>>8 ) & 0xFF)
    /*p7*/              ,((s32OffsetTime>>16) & 0xFF)
    /*p8*/              ,((s32OffsetTime>>24) & 0xFF)
    /*p9*/              ,( _u16BaseYear       & 0xFF)
    /*p10*/             ,((_u16BaseYear>>8 )  & 0xFF));
}

/******************************************************************************/
/// API for MHEG5 to switch video codec
/******************************************************************************/

BOOLEAN     M5API_VID_Switch2Codec  (VDEC_CodecType eVDEC_CodecType, BOOLEAN bIframe)

{
    if (bIframe)    // always need to reset mvd if iframe
    {
        //Stop old codec
        msAPI_VID_Command(MSAPI_VID_STOP);
        // load code if needed
        if(msAPI_VID_GetCodecType() != eVDEC_CodecType)
        {
            //printf("msAPI_VID_GetCodecType():%x   -> %x\n",msAPI_VID_GetCodecType(),eVDEC_CodecType);
            //Set new codec
            msAPI_VID_SetMappingAVCParameter(eVDEC_CodecType);
        }
        //Init video variable
        MApp_VID_VariableInit();
        //Init new codec
        if(eVDEC_CodecType == E_VDEC_CODEC_TYPE_H264)
            msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_FILE);
        else
            msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);
        }
    else
    {
        if(msAPI_VID_GetCodecType() != eVDEC_CodecType)
        {
            //printf("msAPI_VID_GetCodecType():%x   -> %x\n",msAPI_VID_GetCodecType(),eVDEC_CodecType);

            //Stop old codec
            msAPI_VID_Command(MSAPI_VID_STOP);
            //Set new codec
            msAPI_VID_SetMappingAVCParameter(eVDEC_CodecType);
            //Init video variable
            MApp_VID_VariableInit();
            //Init new codec
            msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);
        }
    }
    return true;
}

/******************************************************************************/
/// API for MHEG5 to exec video command
/******************************************************************************/
void        M5API_VID_Command       (U8 u8VIDcommand)

{
    //if(u8VIDcommand == MSAPI_VID_PLAY)
    //{
    //    //M5API_VID_Switch2Codec(g_MHEG5Video.CodecType);
    //    msAPI_VID_Command(u8VIDcommand);
    //}
    //else
    if(u8VIDcommand == MSAPI_VID_STOP)
    {
        msAPI_VID_Command(u8VIDcommand);
        MApp_VID_VariableInit();

        //MApi_VDEC_EnableTurboMode(TRUE);
        msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);
        //MApi_VDEC_EnableTurboMode(FALSE);
    }
    else if(u8VIDcommand == MSAPI_VID_PAUSE)
    {
        MApi_VDEC_SetFreezeDisp(TRUE);
    }
    else
    {
        if((TRUE == g_bIsImageFrozen) && (u8VIDcommand == MSAPI_VID_PLAY))
        MApi_VDEC_SetFreezeDisp(FALSE);
        msAPI_VID_Command(u8VIDcommand);
    }
    M5DBG(printf("M5API VideoCommand:%x\n",u8VIDcommand));
}

/******************************************************************************/
///  API for MHEG5 to clean MB MSG
/******************************************************************************/
void        M5API_MBX_Clean       (void)

{
    MSApi_MBX_ClearMSG(E_MBX_CLASS_MHEG5_STATE);
    MSApi_MBX_ClearMSG(E_MBX_CLASS_CHANNEL);
    MSApi_MBX_ClearMSG(E_MBX_CLASS_MPEG);
    MSApi_MBX_ClearMSG(E_MBX_CLASS_VIDEO);
    MSApi_MBX_ClearMSG(E_MBX_CLASS_AUDIO);
    MSApi_MBX_ClearMSG(E_MBX_CLASS_CI);
    MSApi_MBX_ClearMSG(E_MBX_CLASS_INPUT);
    MSApi_MBX_ClearMSG(E_MBX_CLASS_SYSTEM);
}

/******************************************************************************/
/// API for init Network
/******************************************************************************/
#if MHEG5_NETWORK
void msAPI_MHEG5_InitNetwork()
{
    M5_MAILBOX_SEND(    MB_CLASS_SYSTEM,
                        MB_SYS_CMD_SYS_NETWORK,
                        OBA_MSG_TYPE,
                        0x01,

                        ETHNET_PHY_TYPE,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0);
}
#endif

/******************************************************************************/
/// MHEG5 register MB process callback function
/******************************************************************************/
void _HandleMHEG5MSG(MBX_Msg *pMsg, MS_BOOL *pbAddToQueue)
{
    //For compiler error
    //eMsgClass       = eMsgClass;
    //pMsgQueueStatus = pMsgQueueStatus;
    if((E_MBX_CLASS_SYSTEM == pMsg->u8MsgClass)&&(MB_MHEG5_STATE_DSMCC_EXIT == pMsg->u8Index))
    {
        _bDsmccExit=TRUE;
        *pbAddToQueue = FALSE;
    }
    else
    {
        UNUSED(pMsg);
        //*pMsg = *pMsg;
        *pbAddToQueue = TRUE;
    }
    //printf("_HandleMHEG5MSG:%bx , %lx\n",eMsgClass,pMsgQueueStatus->status);
}

#define Mprintf(a,b) b

/******************************************************************************/
/// API for MHEG5 to register MB class
/******************************************************************************/
static void _M5API_MBX_RegisterMailBox(void)
{
    static BOOLEAN bRegister=FALSE;

    if(bRegister)
    {
        return;
    }

    //Register MB callback function
    Mprintf("REG E_MBX_CLASS_MHEG5_STATE %bx \n",MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_MHEG5_STATE,   MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));
    Mprintf("REG E_MBX_CLASS_CHANNEL %bx \n",    MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_CHANNEL,       MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));
    Mprintf("REG E_MBX_CLASS_MPEG %bx \n",       MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_MPEG,          MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));
    Mprintf("REG E_MBX_CLASS_VIDEO %bx \n",      MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_VIDEO,         MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));
    Mprintf("REG E_MBX_CLASS_AUDIO %bx \n",      MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_AUDIO,         MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));
    Mprintf("REG E_MBX_CLASS_CI %bx \n",         MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_CI,            MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));
    Mprintf("REG E_MBX_CLASS_INPUT %bx \n",      MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_INPUT,         MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));
    Mprintf("REG E_MBX_CLASS_SYSTEM %bx \n",     MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_SYSTEM,        MHEG5_COMMON_MBX_QUEUESIZE , _HandleMHEG5MSG));

    bRegister=TRUE;
}
/*
static void _M5API_MBX_UnRegisterMailBox(void)
{
    Mprintf("REG E_MBX_CLASS_MHEG5_STATE %bx \n",MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_MHEG5_STATE));
    Mprintf("REG E_MBX_CLASS_CHANNEL %bx \n",    MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_CHANNEL));
    Mprintf("REG E_MBX_CLASS_MPEG %bx \n",       MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_MPEG));
    Mprintf("REG E_MBX_CLASS_VIDEO %bx \n",      MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_VIDEO));
    Mprintf("REG E_MBX_CLASS_AUDIO %bx \n",      MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_AUDIO));
    Mprintf("REG E_MBX_CLASS_CI %bx \n",         MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_CI));
    Mprintf("REG E_MBX_CLASS_INPUT %bx \n",      MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_INPUT));
    Mprintf("REG E_MBX_CLASS_SYSTEM %bx \n",     MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_SYSTEM));
    //MSApi_MBX_Enable(FALSE);
    //MSApi_MBX_DeInit();
}
*/


#if CIPLUS_MHEG
static E_MHEG_CI_STATUS bCIMHEGRun = E_MHEG_CI_OFF;

/******************************************************************************/
///- This API will tell MHEG to abort busy waiting for file ready
/******************************************************************************/
void msAPI_MHEG5_SendCIMHEGAbort()//U8 bInitialObject)
{
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CI
    /*Index*/           ,MB_CI_CMD_MHEGCI
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01

    /*p1*/              ,MB_CI_CMD_MHEGCI_ABORT
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}


/******************************************************************************/
///- This API will tell MHEG that CIMHEG is triggered
/******************************************************************************/
void msAPI_MHEG5_SendCIMHEGRequestStart()//U8 bInitialObject)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CI
    /*Index*/           ,MB_CI_CMD_MHEGCI
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01

    /*p1*/              ,MB_CI_CMD_MHEGCI_INITOBJ
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
///- This API will tell MHEG that CIMHEG file is ready
/******************************************************************************/
void msAPI_MHEG5_SendCIMHEGFileReady()
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CI
    /*Index*/           ,MB_CI_CMD_MHEGCI
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01

    /*p1*/              ,MB_CI_CMD_MHEGCI_FILEREADY
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}


/******************************************************************************/
/******************************************************************************/
void msAPI_MHEG5_SendCIMHEGFileExistence(BOOL bExistence)
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CI
    /*Index*/           ,MB_CI_CMD_MHEGCI
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,10

    /*p1*/              ,MB_CI_CMD_MHEGCI_FILE_EXISTENCE_RESPONSE
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,bExistence);

}


void msAPI_MHEG5_SendCIMHEGFileNG()
{

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CI
    /*Index*/           ,MB_CI_CMD_MHEGCI
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,9

    /*p1*/              ,MB_CI_CMD_MHEGCI_FILE_NG
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}



/******************************************************************************/
///- This API will set CIMHEG running status for MHEG-5
/// @param bRun \b IN: running or not
/******************************************************************************/
void msAPI_MHEG5_SetCIMHEGRun(E_MHEG_CI_STATUS bRun)
{
    printf("[CI+][MHEG] Set Status(%d) \n", (int)bRun);

    bCIMHEGRun = bRun;

#if CIPLUS_MHEG_1_3
    if (E_MHEG_CI_OFF == bRun)
    {
        msAPI_MHEG5_SetCIPLUSSSM(2);    //  default value = 2
        msAPI_MHEG5_SetCIPLUSSMG(FALSE);
    }
#endif

}

/******************************************************************************/
///- This API will get CIMHEG running status of MHEG-5
/// @return bCIMHEGRun \b IN: running or not
/******************************************************************************/
E_MHEG_CI_STATUS msAPI_IsCIMHEGRun()
{
    return bCIMHEGRun;
}

/******************************************************************************/
///- This API will allocate buffer for CIMHEG processing in MHEG-5
/******************************************************************************/
void msAPI_MHEG5_AllocateCIMHEGBuffer()
{
    U32 dlaFBAddr = 0;
    // if CIMHEG, allocate DynamicLineArt Buffer here. Do not allocate DynamicLineArt Buffer in MApp_MHEG5_Init
    if ((dlaFBAddr = msAPI_MHEG5_GetDLAFBAddress())==0)    // i.e. we have not allocate DLA buffer, so we need to allocate it.
    {
        dlaFBAddr = msAPI_MHEG5_AllocateDLAFB();
        // set
    }
    msAPI_CI_SetMHEG5BufAddr(_PA2VA(dlaFBAddr));
}

void msAPI_MHEG5_CIMHEGNG()
{
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_TSP
    /*Index*/           ,MB_TSP_CMD_EXIT_MHEG
    /*MsgType*/        ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/ ,0x00

    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

}

/******************************************************************************/
///- This API will tell MHEG to abort busy waiting for file ready
/******************************************************************************/
void msAPI_MHEG5_SendCIMHEGExitWaitBootState(void)//U8 bInitialObject)
{
    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_CI
    /*Index*/           ,MB_CI_CMD_MHEGCI
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01

    /*p1*/              ,MB_CI_CMD_MHEGCI_EXIT_CIMHEG5_STATE
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}


#endif

/******************************************************************************/
/******************************************************************************/


void msAPI_MHEG5_Bean_Init(void)
{
    if(msAPI_MHEG5_GetBinStatus() == FALSE)
    {
        M5DBG(printf("msAPI_MHEG5_Bean_Init\n"));
        msAPI_MHEG5_SetBinStatus(TRUE);

#if 1//defined(MIPS_CHAKRA) || defined(__AEONR2__)
        msAPI_COPRO_Init(BIN_ID_CODE_MHEG5,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MEM_ADR | MIU_INTERVAL) : (AEON_MEM_ADR)),AEON_MEM_LEN);
#else
        msAPI_COPRO_Init(BIN_ID_CODE_MHEG5,((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)),BEON_MEM_LEN);
#endif

        msAPI_MMap_SendMMapAddr();
    }

    _M5API_MBX_RegisterMailBox();
}


#if DEBUG_SYS_INFO_REPORT
U8 AeonHeartBeat[12];
U32 AeonHeartBeatTime;
/******************************************************************************/
///- This API will do system status report for debugging
/*****************************************************************************/
void msAPI_System_StatusReport(void)
{
    U16 i;

    // 1. Check GE Busy
    if((XBYTE[PE_REG_STATUS + GE_REG_BASE] & REG_PE_CMD_RDY_MASK ) != REG_CMD_FIFO_STATUS)
    {
        for(i=0; i<20; i++)
            printf("-");
        printf("GE Hangup");
        for(i=0; i<20; i++)
            printf("-");
        printf("\n");
        for(i=GE_REG_BASE; i<STRLD_REG_BASE; i++)
        {
            printf(" %02bX", XBYTE[i]);
            if((i&0x000F)==0x000F)
                printf("\n");
        }
    }
    else
        printf("GE still alive:0x%02bX!\n", XBYTE[PE_REG_STATUS + GE_REG_BASE]);

    // 2. Check Aeon is still alive
    for(i=0; i<4; i++)
        printf("-");
    printf("Aeon Cardiac Arrest Period: %Lu Second!", msAPI_Timer_GetSystemTime()-AeonHeartBeatTime);
    for(i=0; i<4; i++)
        printf("-");
    printf("\n");
    for(i=0; i<sizeof(AeonHeartBeat); i++)
        printf(" %02bX", AeonHeartBeat[i]);
    printf("\n");
}

/******************************************************************************/
///- This API will process system mailbox for debugging
/// @param u8MailBox \b : IN - pointer to mailbox
/*****************************************************************************/
void msAPI_System_ProcessMailboxMsg(U8 *u8MailBox)
{
    U8 i;
    // Command Index
    switch (u8MailBox[1])
    {
        case MB_AEON_IDX_AEON_HEARTBEAT:
            AeonHeartBeatTime = msAPI_Timer_GetSystemTime();
            for(i=0; i<sizeof(AeonHeartBeat); i++)
                AeonHeartBeat[i] = u8MailBox[i+2];
            break;
        default:
             break;
    }
}
#endif//DEBUG_SYS_INFO_REPORT

#if ENABLE_AUTOTEST
/******************************************************************************/
/// This API will turn on/off autotest in MHEG5
/// @param bAutoTest \b IN:
///- TRUE: AutoTest is enable
///- FALSE: AutoTest is disable
/*****************************************************************************/
void msAPI_MHEG5_AUTOTEST_Enable(BOOLEAN bAutoTest)
{

    U8 u8AutoTest = 0;
    if(bAutoTest)
    {
        u8AutoTest = 1;
    }

    //M5_MAILBOX_SEND(MsgClass , Index , MsgType , ParameterCount , Parameter .....);
    M5_MAILBOX_SEND(    E_MBX_CLASS_AUTO_TEST
    /*Index*/           ,MB_AUTOTEST_ENABLE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x01

    /*p1*/              ,u8AutoTest
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);


}
#endif

#ifdef MHEG5_BIG5_FONT_ENABLE
void msAPI_MHEG5_LoadBig5Font(void)
{
    U8 i;
    U32 FAddr = ((MHEG5_FONTBUFFER_MEMORY_TYPE & MIU1) ? (MHEG5_FONTBUFFER_ADR | MIU_INTERVAL) : (MHEG5_FONTBUFFER_ADR));

    BOOLEAN bResult;
    BININFO FontBinInfo;

    //printf("msAPI_MHEG5_LoadBig5Font:\n");
    for(i = 0; i < 4; i++)
    {
        FontBinInfo.B_ID = BIN_ID_AEON_M5FONT_24LE + i;
        MDrv_Sys_Get_BinInfo(&FontBinInfo, &bResult);
        if(bResult == PASS)
        {
            //printf("Addr:%lx , VA(Addr):%lx\n",FAddr,_PA2VA(FAddr));

            msAPI_MIU_Copy (FontBinInfo.B_FAddr, (((DECOMPRESS_DATA_BUFFER_MEMORY_TYPE&MIU1)?DECOMPRESS_DATA_BUFFER_ADR|MIU_INTERVAL:DECOMPRESS_DATA_BUFFER_ADR)), ((FontBinInfo.B_Len + 0x07) & ~0x07), MIU_FLASH2SDRAM);

            ms_DecompressInit((U8 *)_PA2VA(FAddr));

            u32M5FontSize[i] = ms_Decompress((U8 *)_PA2VA((U32)((DECOMPRESS_DATA_BUFFER_MEMORY_TYPE & MIU1) ? (DECOMPRESS_DATA_BUFFER_ADR | MIU_INTERVAL) : (DECOMPRESS_DATA_BUFFER_ADR))), FontBinInfo.B_Len);

            ms_DecompressDeInit();

            u32M5FontSize[i] = (u32M5FontSize[i] + 0x07) & ~0x07;
            FAddr += u32M5FontSize[i];
        }
    }

    FontBinInfo.B_ID = BIN_ID_AEON_M5FONT_RM;
    MDrv_Sys_Get_BinInfo(&FontBinInfo, &bResult);
    if(bResult == PASS)
    {
        msAPI_MIU_Copy (FontBinInfo.B_FAddr, ((M5_FONTRM_BUFFER_MEMORY_TYPE & MIU1) ? (M5_FONTRM_BUFFER_ADR | MIU_INTERVAL) : (M5_FONTRM_BUFFER_ADR)), ((FontBinInfo.B_Len + 0x07) & ~0x07), MIU_FLASH2SDRAM);
    }
}

void msAPI_MHEG5_SendM5FontInfo(void)
{

    M5_MAILBOX_SEND(    E_MBX_CLASS_MHEG5_STATE
    /*Index*/           ,MB_MHEG5_STATE_CMD_M5FONTSIZE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0x09
    /*p1*/              ,(U8)u32M5FontSize[0] & 0xFF
    /*p2*/              ,(U8)(u32M5FontSize[0] >> 8) & 0xFF
    /*p3*/              ,(U8)(u32M5FontSize[0] >> 16) & 0xFF
    /*p4*/              ,(U8)u32M5FontSize[1] & 0xFF
    /*p5*/              ,(U8)(u32M5FontSize[1] >> 8) & 0xFF
    /*p6*/              ,(U8)(u32M5FontSize[1] >> 16) & 0xFF
    /*p7*/              ,(U8)u32M5FontSize[2] & 0xFF
    /*p8*/              ,(U8)(u32M5FontSize[2] >> 8) & 0xFF
    /*p9*/              ,(U8)(u32M5FontSize[2] >> 16) & 0xFF
    /*p10*/             ,0);
}
#endif

#endif //MHEG5_ENABLE

#undef _MSAPI_MHEG5_C_

