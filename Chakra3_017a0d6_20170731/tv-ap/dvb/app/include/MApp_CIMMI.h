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

#ifndef MAPP_CIMMI_H
#define MAPP_CIMMI_H

#ifdef  MAPP_CIMMI_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

#include "MApp_Exit.h"
#include "msAPI_CI.h"
#include "datatype.h"
# if(ENABLE_CI_PLUS)
#include "msAPI_MW_GlobalSt.h"
#endif

#define CI_WAIT                             0
#define CI_TC                               1
#define CI_TPDU_TAG                         2
#define CI_SPDU_TAG                         3

#define TRANSPORT_CONNECTION_ID             1
#define MORE_TPDU_FRAGMENT                  0x80
#define LAST_TPDU_FRAGMENT                  0x00

#define T_SB                                0x80
#define T_RCV                               0x81
#define T_CREATE_T_C                        0x82
#define T_C_T_C_REPLY                       0x83
#define T_DELETE_T_C                        0x84
#define T_D_T_C_REPLY                       0x85
#define T_REQUEST_T_C                       0x86
#define T_NEW_T_C                           0x87
#define T_T_C_ERROR                         0x88
#define T_DATA_LAST                         0xA0
#define T_DATA_MORE                         0xA1

#define T_OPEN_SESSION_REQUEST              0x91
#define T_OPEN_SESSION_RESPONSE             0x92
#define T_CREATE_SESSION                    0x93
#define T_CREATE_SESSION_RESPONSE           0x94
#define T_CLOSE_SESSION_REQUEST             0x95
#define T_CLOSE_SESSION_RESPONSE            0x96
#define T_SESSION_NUMBER                    0x90

#define T_APPLICATION_OBJECT_TAG            0x9F
#define T_APPLICATION_OBJECT_80_TAG         0x80
#define T_APPLICATION_OBJECT_84_TAG         0x84
#define T_APPLICATION_OBJECT_MMI_TAG        0x88
#define T_APPLICATION_OBJECT_COMMS_TAG      0x8C

#define T_PROFILE_ENQ                       0x10
#define T_PROFILE                           0x11
#define T_PROFILE_CHANGE                    0x12
#define T_APPLICATION_INFO_ENQ              0x20
#define T_APPLICATION_INFO                  0x21
#define T_ENTER_MENU                        0x22
#define T_CA_INFO_ENQ                       0x30
#define T_CA_INFO                           0x31
#define T_CA_PMT                            0x32
#define T_CA_PMT_REPLY                      0x33

#define T_TUNE                              0x00
#define T_REPLACE                           0x01
#define T_CLEAR_REPLACE                     0x02
#define T_ASK_RELEASE                       0x03
#define T_DATE_TIME_ENQ                     0x40
#define T_DATE_TIME                         0x41

#define T_CLOSE_MMI                         0x00
#define T_DISPLAY_CONTROL                   0x01
#define T_DISPLAY_REPLY                     0x02
#define T_TEXT_LAST                         0x03
#define T_TEXT_MORE                         0x04
#define T_KEYPAD_CONTROL                    0x05
#define T_KEYPRESS                          0x06
#define T_ENQ                               0x07
#define T_ANSW                              0x08
#define T_MENU_LAST                         0x09
#define T_MENU_MORE                         0x0A
#define T_MENU_ANSW                         0x0B
#define T_LIST_LAST                         0x0C
#define T_LIST_MORE                         0x0D
#define T_SUBTITLE_SEGMENT_LAST             0x0E
#define T_SUBTITLE_SEGMENT_MORE             0x0F
#define T_DISPLAY_MESSAGE                   0x10
#define T_SCENE_END_MARK                    0x11
#define T_SCENE_DONE                        0x12
#define T_SCENE_CONTROL                     0x13
#define T_SUBTITLE_DOWNLOAD_LAST            0x14
#define T_SUBTITLE_DOWNLOAD_MORE            0x15
#define T_FLUSH_DOWNLOAD                    0x16
#define T_DOWNLOAD_REPLY                    0x17

#define T_COMMS_CMD                         0x00
#define T_CONNECTION_DESCRIPTOR             0x01
#define T_COMMS_REPLY                       0x02
#define T_COMMS_SEND_LAST                   0x03
#define T_COMMS_SEND_MORE                   0x04
#define T_COMMS_RCV_LAST                    0x05
#define T_COMMS_RCV_MORE                    0x06

#define ONE_BYTE_LENGTH                     0x81
#define TWO_BYTE_LENGTH                     0x82

#define ANSWER_ID_CANCEL                    0x00
#define ANSWER_ID_ANSWER                    0x01
#define ANSWER_ID_RESERVED                  0x02    // other values

// String Type
#define MMI_TEXT_TITLE_STRING               0x00
#define MMI_TEXT_SUB_TITLE_STRING           0x01
#define MMI_TEXT_BOTTOM_STRING              0x02
#define MMI_TEXT_CHOICE_STRING              0x03
#define MMI_TEXT_ENQ_STRING                 0x04

#define MMI_TEXT_BLOCK_LIGHTBAR             TRUE
#define MMI_TEXT_BLOCK_NORMAL               FALSE
#define MMI_TEXT_BLOCK_SHADOW               FALSE
#define MMI_TEXT_BLOCK_NO_SHADOW            FALSE

#define MMI_TEXT_SCROLL_STRLEN              50
#define MMI_TEXT_SCROLL_DELAY_TIME          600
#define MMI_TEXT_SCROLL_JUMP_CHAR           3
#define MMI_TEXT_BLOCK_MAXWIDTH_SPACE       60
#define MMI_TEXT_BLCOK_LEFT_SPACE           5

#define MAX_SIM_SCROLL_TEXT_NUM             3

#define MMI_KEY                             0
#define LIST_KEY                            1
#define ENQ_KEY                             2

#if (ENABLE_CI_PLUS)
#define CI_OP_SEARCH_QUERY_POST_EVENT_INTERVAL      (1000) //1s
#define CI_TUNE_DESCRIPTORS_MAX_LEN                 (4095) // 4K - 1: CI+ Spec: descriptor_loop_length is 12bits
#define CI_CANAL_READY_AUTH_BIN_MAX_LEN             (400)  // 400 bytes
#endif//ENABLE_CI_PLUS

typedef struct
{
    unsigned short ReturnNumber;
    unsigned char ReturnString[256];
} CIMMIReturnStructure;

typedef struct
{
    unsigned short xPos;
    unsigned short yPos;
    unsigned char StringType;
    unsigned char bScroll;
//    unsigned char nScrollShowIndex;
    unsigned char nScrollWinID;
    unsigned char xdata *pStringPos;
} TextObjType;

typedef struct
{
    unsigned char   nSelected;
    unsigned char   nCurrentItem;
    unsigned char   xdata *pCurrentTextString;
    unsigned char   xdata *pTextObj;
} MMITextObjectStructure;

//------------------------------------------------------------------------------
// MMI define
//------------------------------------------------------------------------------
// Menu text items
#define MMI_MENU_ENQ                        4
#define MMI_MENU_TITLE                      3
#define MMI_MENU_SUBTITLE                   2
#define MMI_MENU_BOTTOM                     1
#define MMI_MENU_CHOICE                     0
//-----------------------------------------------
// Menu choice selected
#define MMI_MENU_CHOICE_ZERO                0x00
#define MMI_MENU_CHOICE_NONE                0xFF
// Menu choice text buffer define
#define CTBUFSIZE                           0x02
//-----------------------------------------------
// Menu ENQ choice selected
#define MMI_MENU_CHOICE_1ST                 0x00
#define MMI_MENU_CHOICE_NONE                0xFF
//-----------------------------------------------


//------------------------------------------------------------------------------
// MMI Buffer Structure
//------------------------------------------------------------------------------
typedef struct
{
    U8 ChoiceNumber;        // Total Choice Number 1~254
    U8 ChoiceSelected;      // Exactly selected choice item 1~254
    U8 CChoiceItem;         // Current handle Choice string 0~255
    //U16 MenuLength;         // Total Menu length
    //U16 MenuTextLength;     // Menu text length

    U8 AnswerTextLength;
    U8 bBlindAnswer         :1;
    U8 bEnq                 :1;
    U8 bList                :1;
    U8 bMenuWaitUserAnswer  :1;
    U8 bReserved4           :4;

    //U16 SrcBufSize;
    //U16 SrcIndex;
    //U8 *pSrcBuf;

    // Text String and information
    U8 MenuTextType;
    U8 NumberOfChice;
    U16 TitleTextLength;
    U16 SubTitleTextLength;
    U16 BottomTextLength;
    U16 EnqTextLength;
    U16 ReturnNumber;
    U8 *pTitleBuf;
    U8 *pSubTitleBuf;
    U8 *pBottomBuf;
    U8 *pFirstChoiceBuf;
    U8 *pCurrentChoiceBuf;
    U8 *pLastChoiceBuf;
    U8 *pReturnBuf;
    U8 *pEnqBuf;

    // Drawing feature
    U8 bChoiceItemsScroll   :1;     // Choice number > display number
    U8 bSelectedItemsScroll :1;
    U8 bCalLongString       :1;
    U8 bDisableCalLongString:1;
    U8 bRefreshAllChoice    :1;
    U8 bReserved3           :3;

    U16 TextLength;
    U8 *pTextBuf;
    U8 TextStartReservedSpace;
    U8 CScreenMaxChoiceLine;        // Choice menu maximum display lines 1~6
    U8 CScreenStartChoiceIdx;       // Choice menu display first choice item number 0~255
    U8 CScreenChoiceLineSelected;   // Choice menu display selected line number 1~6
    U8 TempBuf[2];

    U8 r_clr;
    U8 g_clr;
    U8 b_clr;

    // Input information
    U16 InputNumber;                // Input Selected choice item 1~254
    U32 TimerCount;
    U32 TimerCount2; // MediaSet
    U8 bLoopProcessUserInput      :1;
    U8 bPowerOff            :1;
    U8 nFontIndex           :4;
    U8 bReserved2           :2;

    U8  TextTempBuf;
    U32 orgColor;
    U16 FontDispIndex;
    U16 FontDispIndex2;
    U16 orgX;
    U16 StartDispIndex;
    U16 EndDispIndex;
    U8  RowNum;
    U8  *pu8StrHead;
    U8  CalLenBuf[256];
    U8  CalLenIndex;
    U8  RefreshRowUnSelected;
} MMIBufStructure;

//----------------------
// MMI Choice Buffer
//----------------------
typedef struct
{
    U8 *pNextChoiceItemBuf;
    U16 ChoiceLength;
    U8 MMIChoiceBuf[CTBUFSIZE];
} MMIChoiceBufStructure, *PMMIChoiceBufStructure;

#if (ENABLE_CI_PLUS)
/// Define CI+ Tune Applicant for CICAM
typedef enum
{
    /// NONE
    E_CI_TUNE_APPLICANT_NONE,
    /// Host Control
    E_CI_TUNE_APPLICANT_HC,
    /// Operator Profile
    E_CI_TUNE_APPLICANT_OP,
} EN_CI_TUNE_APPLICANT;

/// DVB mux info
typedef struct _DVB_MUXINFO
{
    /// Satellite table ID
    U16  m_u16SatTableID;           // please don't modify this variable...
    /// Network table ID
    U16  m_u16NetworkTableID;       // please don't modify this variable...
    /// MUX reference count
    U16  m_u16RefCnt;               // please don't modify this variable...
    /// MUX information transportstream ID
    U16  u16TransportStream_ID;
    /// MUX information original network ID
    U16  u16OriginalNetwork_ID;
    // MUX information network ID
    U16  u16Network_ID;
    /// MUX information cell ID
    U16  u16CellID;
    /// MUX information RF channel number
    U8   u8RfNumber;
    /// MUX RF channel frequency
    U32  u32Frequency;
    /// MUX information lossSignal frequency
    U32  u32LossSignal_Frequency;
    /// MUX information lossSignal start time
    U32  u32LossSignal_StartTime;
    /// MUX information sambol rate
    U32  u32SymbRate;               //DVBT no use,DVBC use
    /// MUX information QAM mode
    U8   u8ModulationMode;
    /// MUX information physical layer pipes ID
    U16  u16PlpID;                   //DVBT-2 use only
    /// MUX information High priority/Low Priority
    BOOL bLPCoding;                   //DVBT use only
    /// Satellite ID
    U8   u8SatID;           //DVBS use only
    /// Bandwidth
    U8  u8Bandwidth;
    /// Satellite polarization 0: vertical, 1: horizontal
    U8   bPolarity:   1;    //DVBS use only // 0:V, H:1
    /// 0:Off, 1:On
    U8   bPilots:     1;    //DVBS use only // 0:Off, 1:On
    /// Reserved
    U8   bReserved:   4;    //DVBS use only
} ST_DVB_MUX_INFO;

typedef struct
{
    /// DTV CI+ Descriptor Number of Tune
    U8              u8TuneDescriptorNumber; // Check
    /// DTV CI+ Descriptors Length of Tune
    U16             u16TuneDescriptorsLen; // Check
    /// DTV CI+ Descriptors of Tune
    U8*             pu8TuneDescriptors; // Check
    /// DTV CI+ Mux Info of Tune
    ST_DVB_MUX_INFO stCiTuneMux; // Check
    /// DTV CI+ DVBS Orbital position, only for DVBS tuning
    U16             u16Orbital_position;
    /// DTV CI+ Tuning Timer for Tune
    U32             u32TuningTimer;
} ST_DTV_CI_TUNING_CONTENT;

typedef struct
{
    /// DTV CI+ Tune Resource Owner
    EN_CI_TUNE_APPLICANT eCiTuneApplicant;
    /// DTV CI+ Tune target route
    U8 u8TuneTargetDtvRoute;
    /// DTV CI+ Tune original route
    U8 u8TuneOriginalDtvRoute;
    /// DTV CI+ Original program info
    //ST_DVB_PROGRAMINFO stOriginalProgInfo;
    /// DTV CI+ Tune Process information
    ST_DTV_CI_TUNING_CONTENT stTuningContent;
} ST_DTV_CI_TUNE_INFO;
#endif//ENABLE_CI_PLUS
//------------------------------------------------------------------------------
// Variable
//------------------------------------------------------------------------------
INTERFACE MMIBufStructure *MMI_Buf;     // Main MMI memory pointer
INTERFACE U16 interssnb;                // SSNB
INTERFACE U16 MMI_index;                // MMI common index variable
INTERFACE EN_RET enMMIRetVal;
INTERFACE U32 u32CardStatusChangedTimer;
INTERFACE U8 bChannelChange; // MediaSet
INTERFACE U8 u8MMIKey;      // MediaSet
INTERFACE U8 bActiveMMI;    // MediaSet

#if (ENABLE_CI_PLUS)
INTERFACE ST_DTV_CI_TUNE_INFO g_stCiTuneInfo; // m_stCiTuneInfo
INTERFACE BOOL g_bOpSearchSuspended;
INTERFACE U32 g_u32OpSearchQueryPostEventTimer;
#endif//ENABLE_CI_PLUS
//------------------------------------------------------------------------------
// Function define
//------------------------------------------------------------------------------
// Parsing

// Display
INTERFACE void MMI_DrawMenu(void);
INTERFACE void MMI_DrawText(U8 MenuTextType);
INTERFACE void MMI_DrawEnqBlock(U8 TextNumber, U8 TotalText, U8 bflagUpdate);

// Input
INTERFACE void MMI_ProcessUserInput(U8 keysrc);
INTERFACE void MMI_ProcessUserInput_ENQ(U8 keysrc);

INTERFACE void MMI_MessageHandle(void);
INTERFACE void MMI_RemoveBitmapMessage(void);

//ZUI: refine CIMMI flow: INTERFACE void MApp_CIMMI_Main(void);

//2008/3/10: refine CI/MMI flow to independent MMI state...
typedef enum
{
    STATE_CIMMI_INIT,
    STATE_CIMMI_MESSAGE_BOX,
    STATE_CIMMI_WAIT,
    STATE_CIMMI_CLEAN_UP,
    STATE_CIMMI_GOTO_STANDBY,
    STATE_CIMMI_EVENT_HANDLE,
} EN_CIMMI_STATE;

INTERFACE EN_RET MApp_CIMMI_Main(void);
//INTERFACE void MApp_CI_PMT_Parse(U8 *pu8Section);
//2008/3/11: refine CI/MMI interfaces...
#define MAX_CI_MMI_MENU_ITEMS 100 //for conax module Riks smartcard
#define MAX_CIMMI_TEXT_SIZE 4000 //for conax module Riks smartcard
#define MAX_CIMMI_TITLE_SIZE 256
#define MAX_CIMMI_ENQ_SIZE 30

typedef enum
{
    EN_CIMMI_TYPE_NONE,
    EN_CIMMI_TYPE_MENU,
    EN_CIMMI_TYPE_LIST,
    EN_CIMMI_TYPE_ENQ,
} EN_CIMMI_TYPE ;

typedef struct
{
    U8 * pString[MAX_CI_MMI_MENU_ITEMS]; //point to aStringContent[], NULL means no data
    U8 aStringContent[MAX_CIMMI_TEXT_SIZE];
    U8 au8Subtitle[MAX_CIMMI_TITLE_SIZE];
    U8 au8Bottom[MAX_CIMMI_TITLE_SIZE];
    U8 ListCnt;  //adam 20080509 add for test
} _CIMMI_MENU_DATA, _CIMMI_LIST_DATA;

typedef struct
{
    U8 bBlindAns;
    U8 u8AnsLen;
    // enq text is treated as title
} _CIMMI_ENQ_DATA;

typedef struct
{
    EN_CIMMI_TYPE enType;
    U8 aTitleContent[MAX_CIMMI_TITLE_SIZE];
    union
    {
        _CIMMI_MENU_DATA menu_data;
        _CIMMI_LIST_DATA list_data;
        _CIMMI_ENQ_DATA enq_data;
    } content;
    U8 aEnqInputBuffer[MAX_CIMMI_ENQ_SIZE];
} CIMMI_INFO;

INTERFACE BOOLEAN MMI_ParseInformaton(CIMMI_INFO * pInfo); //[out] pInfo for current displaying infomation
INTERFACE BOOLEAN MMI_SelectItem(S8 s8ItemIndex); //[in] s8ItemIndex for menu item index, -1 for back to prev menu
INTERFACE BOOLEAN MMI_BackENQ( void );
INTERFACE BOOLEAN MMI_InputENQ(U8 * pu8Code); //[in] pu8Code for user input PIN code, NULL for cancel

INTERFACE void MApp_CI_Event_Cb(EN_CI_EVENT etype);
INTERFACE BOOL MApp_CI_Date_SendDateTime(void);
INTERFACE void MApp_CI_HSS_Active_Cb( BOOLEAN bActive );
#if( ENABLE_CI_PLUS )
INTERFACE BOOLEAN MApp_CI_Is_CIByPassMode(void);
#endif

INTERFACE BOOLEAN Mapp_MMI_ParseInformaton(U16* DstName, U8 *pu8Src,U16 u16MaxNameLen);

#if (ENABLE_CI_PLUS)
// ------------------------------------------------------------
/// get op profile name by index
/// @param   pu8SrcName   \b IN: input service name
/// @param   u8SrcLen   \b IN: name max length
/// @param   pu8DstName   \b OUT: output service name
/// @param   u8DstMaxLen   \b IN: name max length
/// @param  u32CicamId     \b IN:  current cicamId
/// @return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN MApp_CI_SetCharCodeTableToSrvName(const U8 *pu8SrcName, U8 u8SrcLen, U8 *pu8DstName, U8 u8DstMaxLen, U32 u32CicamId);

// ------------------------------------------------------------
/// get op profile name by index
/// @param   u8Index   \b IN: index
/// @param  strProfileName     \b OUT:  profile name
/// @return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_GetOpProfileNameByIndex( U8 u8Index, WORD* ProfileName , U16 u16MaxNameLen);

// ------------------------------------------------------------
/// get op dtv system type by index
/// @param   u8Index   \b IN: index
/// @param  eDtvSysType     \b OUT:  dtv system type
/// @return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_GetOpDtvSysTypeByIndex( U8 u8Index, EN_DELIVERY_SYS_TYPE* eDtvSysType );

// ------------------------------------------------------------
/// get op iso 639 langcode by cicam identifier
/// @param   u32CicamId   \b IN: cicam identifier
/// @param  pu8Iso639LangCode     \b OUT:  iso 639 langcode
/// @return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_GetOpIso639LangCodeByCicamId( U32 u32CicamId, U8* pu8Iso639LangCode );

// ------------------------------------------------------------
/// get current op cicam identifier
/// @return op CICAM id
// -----------------------------------------------------------
INTERFACE U32 MApp_CI_GetCurrentOpCicamId( void );

// ------------------------------------------------------------
/// get op cache count
/// @return op cache count
// -----------------------------------------------------------
INTERFACE U8 MApp_CI_GetOpCacheCount( void );
// ------------------------------------------------------------
/// get op cache count
/// @return op cache count exclude E_DELIVERY_SYS_NONE
// -----------------------------------------------------------
INTERFACE U8 MApp_CI_GetValidOpCacheCount(void);

// ------------------------------------------------------------------------
/// check op cache count reach max cache number
/// @return   \b  return TRUE : reach max number or FALSE : less max number
// ------------------------------------------------------------------------
//INTERFACE BOOL MApp_CI_IsOpCountReachMaxNum(void);

// ------------------------------------------------------------
/// Delete op cache from op cache db by index
/// @param  u8Index    \b IN: index
/// @return None
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_DeleteOpCacheByIndex( U8 u8Index );

// ------------------------------------------------------------
/// Delete op cache from op cache db by cicam identifier
/// @param  u32CicamId    \b IN: cicam identifier
/// @return None
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_DeleteOpCacheByCicamId( U32 u32CicamId );

// ------------------------------------------------------------
/// set current cicam identifier
/// @param  u32CicamId    \b IN: cicam identifier
/// @return None
// -----------------------------------------------------------
INTERFACE void MApp_CI_SetCurrentCicamId(U32 u32CicamId);

// ------------------------------------------------------------
/// get current cicam identifier
/// @return cicam identifier
// -----------------------------------------------------------
INTERFACE U32 MApp_CI_GetCurrentCicamId(void);

// ------------------------------------------------------------
/// set op mode status
/// @param  bOpMpde    \b IN: op mode status
/// @return None
// -----------------------------------------------------------
INTERFACE void MApp_CI_SetOpMode(BOOLEAN bOpMpde);

// ------------------------------------------------------------
/// check Op mode status
/// @return Op mode flag
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_IsOpMode( void );

// ------------------------------------------------------------
/// set current cicamId
/// @param  u32CicamId    \b IN: current cicamId
/// @return
// -----------------------------------------------------------
INTERFACE void MApp_CI_SetCurrentCicamId(U32 u32CicamId);

// ------------------------------------------------------------
/// get current cicamId
/// @return current cicamId
// -----------------------------------------------------------
INTERFACE U32 MApp_CI_GetCurrentCicamId(void);

// ------------------------------------------------------------
/// Reset op cache db
/// @param  bDisableChannel     \b IN: disable channel
/// @return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_ResetOPCacheDB( BOOL bDisableChannel );

// ------------------------------------------------------------
/// compare content byte and get label char
/// @param  u8ContentByte     \b IN: content byte
/// @param  strLabelChar     \b OUT: content label char
/// @param  u16LaelLen     \b IN: label char max length
/// @return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOL MApp_CI_CompareCIContentByte( U8 u8ContentByte, WORD* pLabelChar, U16 u16LaelLen);

// ------------------------------------------------------------
/// get sat info by angle
/// @param  pstSatParam     \b IN: sat param
/// @return TRUE : success or FALSE : failure
// -----------------------------------------------------------
//INTERFACE BOOL MApp_CI_GetSatInfoByAngle( MW_SI_SAT_PARAM *pstSatParam );

//-------------------------------------------------------------------------------------------------
/// Enter Operator Profile of CICAM.
/// @param  u8Index            \b IN: Index.
/// @return  None.
//-------------------------------------------------------------------------------------------------
INTERFACE void MApp_CI_EnterCiOperatorProfile( U8 u8Index );

//-------------------------------------------------------------------------------------------------
/// Exit Operator Profile of CICAM.
/// @return  None.
//-------------------------------------------------------------------------------------------------
INTERFACE void MApp_CI_ExitCiOperatorProfile( void );

//-------------------------------------------------------------------------------------------------
/// CIClearOPSearchSuspended
///     Clear OP Search Suspended Flag to notify CI that UI has displayed OP Search Query UI
/// @return  None.
//-------------------------------------------------------------------------------------------------
INTERFACE void MApp_CI_CIClearOPSearchSuspended( void );

//-------------------------------------------------------------------------------------------------
/// Send operator_search_start() for CI+ OP
/// @param  bUnattendedFlag                 \b IN: This 1-bit field specifies whether the Host is operating
///                                                in an unattended mode (i.e. the user is not present).
///                                                A value of "1" indicates that the user is not present
///                                                and the Host is not able to service any interactive requests.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//-------------------------------------------------------------------------------------------------
INTERFACE BOOL MApp_CI_SendCiOpSearchStart(void);
//-------------------------------------------------------------------------------------------------
/// start to filter video, audio and pcr
/// @param  u16VideoPID              \b IN: video pid.
/// @param  u16AudioPID              \b IN: audio pid.
/// @param  u16PCRPID                \b IN: pcr pid.
/// @return  None.
//-------------------------------------------------------------------------------------------------
INTERFACE void MApp_CI_TuneServicePlayAV( U16 u16VideoPID, U16 u16VideoType, U16 u16AudioPID, U16 u16AudioType, U16 u16PCRPID);

INTERFACE void MApp_CI_CiEventCommandOpTune( void );

/****************************ZIGGO CI+****************************/
INTERFACE BOOL IsCiVodMode(void);
INTERFACE void SetCiHcRelease(void);
INTERFACE void MApp_CI_CiEventCommandHcAskReleaseOk(void);
INTERFACE void MApp_CI_CiEventCommandHcAskReleaseRefused(void);
INTERFACE void MApp_CI_CiEventCommandCamReset(void);
INTERFACE void MApp_CI_HcTuneBackToOriginalProgram(void);
INTERFACE void MApp_CI_Monitor(void);
/*****************************************************************/

/***************** RR2138 CI+ PVR Develop *****************/
INTERFACE void MApp_CI_CC_CopyProtect(U8 u8URI_DOT, U8 u8URI_RCT, U8 u8URI_EMI, U8 u8URI_APS, U8 u8URI_ICT, U8 u8URI_RL);
/**********************************************************/

/***************** RR2194 CI+1.4 Develop ******************/
#if (ENABLE_CI_PLUS_V1_4)
INTERFACE BOOL MApp_CI_AppInfoNotifyPowerDown(void);
INTERFACE BOOL MApp_CI_IsHcKeepAppRunning(void);
INTERFACE BOOL Mapp_CI_SaveVirtualService(U8 *pu8Data);
INTERFACE void MApp_CI_PowerDown_Reset(void);
INTERFACE void MApp_CI_PowerDown_GoToSleep(void);
INTERFACE U32 MApp_CI_PowerDown_CountDownTime(void);
INTERFACE void MApp_CI_PowerDown_Task(void);
INTERFACE BOOL MApp_CI_PowerDown_Is_FuncEnable(void);

#endif
/**********************************************************/

#endif //ENABLE_CI_PLUS

#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
INTERFACE BOOLEAN Mapp_check_valid_key(void);
#endif
#undef INTERFACE

#endif

