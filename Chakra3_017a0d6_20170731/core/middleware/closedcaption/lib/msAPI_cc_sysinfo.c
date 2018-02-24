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
/// @file msAPI_cc_sysinfo.h
/// @brief API for Closed Caption Miscellaneous Setting
/// @author MStar Semiconductor, Inc.
///
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_CC_SYSINFO_C

#include <string.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsTypes.h"
#include "apiGOP.h"

#include "Panel.h"
#include "msAPI_Global.h"
#include "msAPI_Font.h"
#include "msAPI_Video.h"
#include "BinInfo.h"
#include "msAPI_MIU.h"
#include "apiPNL.h"
#include "MApp_GlobalSettingSt.h"
#include "mapi_cc_common.h"
#include "mapi_cc_interface.h"
#include "mapi_cc_decode.h"
#include "mapi_cc_render.h"
#include "mapi_cc_interface.h"
#include "mapi_cc_monitor.h"
#include "msAPI_cc_parser.h"
#include "msAPI_cc_sysinfo.h"
#include "../mapp_closedcaption_customer.h"

#define CC_SYSINFO_DBG(y)       y
#define CC_LANG_KOREAN_TYPE             3//24

//#define KOREAN_CC_ENABLE       0

/********************************************************************************/
/*                    global variable                                           */
/********************************************************************************/
//U8 g_u8FBidBase=0;

/* Extern */
//extern stCaptionSetting_Type stCCOSDSetting;
extern U32 u32CC608RbAddr, u32CC608RbSize, u32CC708RbAddr, u32CC708RbSize;
extern U32 u32CCCacheAddr, u32CCCacheSize;
extern U32 u32CC608CacheAddr, u32CC608CacheSize;
extern U32 u32CCBlock0Addr, u32CCBlock0Size, u32CCBlock1Addr, u32CCBlock1Size;
extern U8 u8CCPR_Temp1, u8CCPR_Temp2, u8CCPR_Temp3, u8CCPR_Temp4;

stIntMemoryAddr stIntMemAddr;
stIntCustomerVariables stIntCustomerVar;

/********************************************************************************/
/*                      Local                                                   */
/********************************************************************************/
U16 u16SysInfoTemp1, u16SysInfoTemp2, u16SysInfoTemp3, u16SysInfoTemp4;
U32 g_GWIN_ALIGND_VALUE;
U32 g_GWIN_ALIGNMENT_MASK;

static U8 CC_LANG, CC_LANG_BAK, CC_LANG_KOREAN_BAK;//s CC_LANG_KOREAN_SYMBOL;

static U8 u8CharWidth, u8CharHeight;

/* Common Variables */
static U8  g_u8CCFontWidth;
static U8  g_u8CCFontHeight;
static U8  g_u8CCRowWidth;
static U8  g_u8CCRowHeight;
static U16 g_u16Axis_XPos;
static U16 g_u16Axis_YPos;
//static U8  g_u8FBidBase;
static U32   g_u32708CaptionTimeout;

extern CC_U32 u32CCQueueAddr,u32CCQueueSize;
extern U32 gu32DTVTimeOut;

#if BRAZIL_CC
static BOOL g_bCCEnableSVS;
static BOOL g_bCCEnableSHS;
#endif

#define CC_DTV_TIME_OUT_MS              0xffffffff    // forever

/* CC608 Variables */
static U8 g_u8Row_TopRsvHeight;
static U8 g_u8Row_BtmRsvHeight;
static U8 g_u8Text_RowNo;
static U8 g_u8Text_YPos;
static U8 g_u8priority;

/* CC708 Variables */
static U8 g_u8WinAnkor_GridWidthMax, g_u8WinAnkor_GridHeightMax;
static U8 g_u8WinAnkor_GridWidthSpace, g_u8WinAnkor_GridHeightSpace;
static U16 g_u16STA_SXLoc, g_u16STA_SYLoc;
static U16 g_u16STA_Width, g_u16STA_Height;

stCCAttrType g_fCCAttrFlag={ .fCCAttr_Support_EdgeAttrSet_Flag = TRUE};
/********************************************************************************/
/*                      Functions                                               */
/********************************************************************************/

///////////////////////////////////////////////////////////////////////////////
/// API used in temporary:
///
/// dummy functions
///
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
U8 devPanel_PANEL_TYPE(void)
{
    if( msAPI_CC_Panel_WIDTH() * 9 >= msAPI_CC_Panel_HEIGHT() * 16 )
        return  _16_9_PANEL;
    else if ( msAPI_CC_Panel_WIDTH() * 3 > msAPI_CC_Panel_HEIGHT() * 4 )
        return  WIDE_PANEL;
    else if( msAPI_CC_Panel_WIDTH() * 4 == msAPI_CC_Panel_HEIGHT() * 5 )
        return  _5_4_PANEL;
    else if( msAPI_CC_Panel_WIDTH() * 3 == msAPI_CC_Panel_HEIGHT() * 4 )
        return  _4_3_PANEL;
    else
        return  OTHER_PANEL;
}

///////////////////////////////////////////////////////////////////////////////
/// Normal APIs:
///
/// normal functions
///
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_CCInfoInit(void)
{
    #if (KOREAN_CC_ENABLE)
    BININFO _BinInfo;
    BOOLEAN bResult;
    U32 _addr;
    U32 u32Wunsung2UnicodeTableAddr = 0;
    #endif

    g_u8CC708_AspectRatio = 0;
    //msAPI_CC608_Timeout_Threshold(2000, 4000);

    #if (KOREAN_CC_ENABLE)
    _BinInfo.B_ID = BIN_ID_WANSUNGCODE_TABLE;

    msAPI_MIU_Get_BinInfo(&_BinInfo, &bResult);
    if (bResult == PASS)
    {
        _addr = _BinInfo.B_FAddr;
        u32Wunsung2UnicodeTableAddr = _addr + sizeof(U32);
        //printf("\nWansung code found in flash, addr=0x%x", u32Wunsung2UnicodeTableAddr);
        CC_RenderFuns.SetCcInfo(NULL, CC_KOREAN_WUNSUNGTABLE, u32Wunsung2UnicodeTableAddr);
    }
    #endif

    // GWIN alignment, the unit is pixel
    #if 0
    #if 0    // 2266 mode
    g_GWIN_ALIGND_VALUE = 4;
    g_GWIN_ALIGNMENT_MASK = 0xFFFC;

    #else                               // I8 mode
        #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || \
             (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
             (CHIP_FAMILY_TYPE == CHIP_FAMILY_A6)   || \
             (CHIP_FAMILY_TYPE ==CHIP_FAMILY_EDEN) || \
             (CHIP_FAMILY_TYPE ==CHIP_FAMILY_EULER) || \
             (CHIP_FAMILY_TYPE ==CHIP_FAMILY_MILAN) || \
             (CHIP_FAMILY_TYPE ==CHIP_FAMILY_MARLON) || \
             (CHIP_FAMILY_TYPE ==CHIP_FAMILY_MAYA)  ||\
             (CHIP_FAMILY_TYPE ==CHIP_FAMILY_WHISKY))

            g_GWIN_ALIGND_VALUE = 16;
            g_GWIN_ALIGNMENT_MASK = 0xFFF0;
            // printf("[ccDebug] : align : 16!\n");
        #else
            g_GWIN_ALIGND_VALUE = 8;
            g_GWIN_ALIGNMENT_MASK = 0xFFF8;
            // printf("[ccDebug] : align : 8!\n");
        #endif
    #endif
    #endif
    MApi_GOP_GetChipCaps(E_GOP_CAP_WORD_UNIT, &g_GWIN_ALIGND_VALUE, sizeof(g_GWIN_ALIGND_VALUE));
    switch(g_GWIN_ALIGND_VALUE)
    {
        case 4:
            g_GWIN_ALIGNMENT_MASK = 0xFFFC;
            break;
        case 8:
            g_GWIN_ALIGNMENT_MASK = 0xFFF8;
            break;
        case 16:
            g_GWIN_ALIGNMENT_MASK = 0xFFF0;
            break;
        case 32:
            g_GWIN_ALIGNMENT_MASK = 0xFFE0;
            break;
        default:
            printf("error:GWIN alignment value error!\n");
            break;
    }
    CC_RenderFuns.SetCcInfo(NULL, CC_ALIGN_VALUE, g_GWIN_ALIGND_VALUE);
}

///////////////////////////////////////////////////////////////////////////////
/// API for Reset CC OSD variables::
/// Initialize the variables
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_ResetOsdSetting(stCaptionSettingVariables *pCaptionVarSetting)
{
    // default values
    _stCCVarSetting.u32ATV_Axis_xpos            = pCaptionVarSetting->u32ATV_Axis_xpos = 0;
    _stCCVarSetting.u32ATV_Axis_ypos            = pCaptionVarSetting->u32ATV_Axis_ypos = 0;
    _stCCVarSetting.u32DTV_Axis_xpos            = pCaptionVarSetting->u32DTV_Axis_xpos = 0;
    _stCCVarSetting.u32DTV_Axis_ypos            = pCaptionVarSetting->u32DTV_Axis_ypos = 0;
    _stCCVarSetting.u32Text_608_rowno       = pCaptionVarSetting->u32Text_608_rowno = 0;
    _stCCVarSetting.u32Text_608_ypos        = pCaptionVarSetting->u32Text_608_ypos = 0;
    _stCCVarSetting.u32Cc_lang              = pCaptionVarSetting->u32Cc_lang = CAPTION_FONTSIZE_NORMAL;
    _stCCVarSetting.u32Row_608_toprsvheight = pCaptionVarSetting->u32Row_608_toprsvheight = 1;
    _stCCVarSetting.u32Row_608_btmrsvheight = pCaptionVarSetting->u32Row_608_btmrsvheight = 1;
    _stCCVarSetting.u32Row_708_toprsvheight = pCaptionVarSetting->u32Row_708_toprsvheight = 0;
    _stCCVarSetting.u32Row_708_btmrsvheight = pCaptionVarSetting->u32Row_708_btmrsvheight = 0;
    _stCCVarSetting.u8Row_brazil_toprsvheight = pCaptionVarSetting->u8Row_brazil_toprsvheight = 0;
    _stCCVarSetting.u8Row_brazil_btmrsvheight = pCaptionVarSetting->u8Row_brazil_btmrsvheight = 0;
    _stCCVarSetting.s32XPos_offset= pCaptionVarSetting->s32XPos_offset= 0;
    _stCCVarSetting.s32YPos_offset= pCaptionVarSetting->s32YPos_offset= 0;
    _stCCVarSetting.u8CCEnableSVS = pCaptionVarSetting->u8CCEnableSVS= 0;
    _stCCVarSetting.u8CCEnableSHS = pCaptionVarSetting->u8CCEnableSHS= 0;
    _stCCVarSetting.u32CC_608_ScrollStep = pCaptionVarSetting->u32CC_608_ScrollStep = 0;
    // default CC time-out time
    _stCCVarSetting.u32Timeout_608_capiton  = pCaptionVarSetting->u32Timeout_608_capiton = 5000;
    _stCCVarSetting.u32Timeout_608_text     = pCaptionVarSetting->u32Timeout_608_text = 0xffffffff;
    _stCCVarSetting.u32Timeout_708_caption  = pCaptionVarSetting->u32Timeout_708_caption = 16000;
}

///////////////////////////////////////////////////////////////////////////////
/// API for Set FONT information
/// @param FontNumber \b IN  Font Number
///////////////////////////////////////////////////////////////////////////////
void msAPI_CC_SetFontInfo(U8 FontNumber)
{
    if(FontNumber >= 24)
        g_fCCAttrFlag.fCCAttrEnable24Fonts = TRUE;
    else
        g_fCCAttrFlag.fCCAttrEnable24Fonts = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// API for Setting CC System RingBuffer::
/// Initialize the CC RingBuffers' setting
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_SetSysBuffer(void)
{
    // reset CC DRAM parameters
    u32CC608RbAddr = _PA2VA((CC608MVD_RINGBUFFER_START_MEMORY_TYPE & MIU1) ? (CC608MVD_RINGBUFFER_START_ADR | MIU_INTERVAL) : (CC608MVD_RINGBUFFER_START_ADR));
    u32CC608RbSize = (U32)CC608MVD_RINGBUFFER_START_LEN;

    u32CC708RbAddr = _PA2VA((CC708MVD_RINGBUFFER_START_MEMORY_TYPE & MIU1) ? (CC708MVD_RINGBUFFER_START_ADR | MIU_INTERVAL) : (CC708MVD_RINGBUFFER_START_ADR));
    u32CC708RbSize = (U32)CC708MVD_RINGBUFFER_START_LEN;

    u32CCCacheAddr = _PA2VA((CCMVD_CACHE_BUFFER_MEMORY_TYPE & MIU1) ? (CCMVD_CACHE_BUFFER_ADR | MIU_INTERVAL) : (CCMVD_CACHE_BUFFER_ADR));
    u32CCCacheSize = (U32)CCMVD_CACHE_BUFFER_LEN;

    u32CC608CacheAddr = _PA2VA((CC608_DISPBUFFER_START_MEMORY_TYPE & MIU1) ? (CC608_DISPBUFFER_START_ADR | MIU_INTERVAL) : (CC608_DISPBUFFER_START_ADR));
    u32CC608CacheSize = (U32)CC608_DISPBUFFER_START_LEN;
    #if ( MEMORY_MAP != MMAP_16MB )
    u32CCBlock0Addr = _PA2VA((DTVCC_BLOCK0_START_MEMORY_TYPE & MIU1) ? (DTVCC_BLOCK0_START_ADR | MIU_INTERVAL) : (DTVCC_BLOCK0_START_ADR));
    u32CCBlock0Size = (U32)DTVCC_BLOCK0_START_LEN;
    u32CCBlock1Addr = _PA2VA((DTVCC_BLOCK1_START_MEMORY_TYPE & MIU1) ? (DTVCC_BLOCK1_START_ADR | MIU_INTERVAL) : (DTVCC_BLOCK1_START_ADR));
    u32CCBlock1Size = (U32)DTVCC_BLOCK1_START_LEN;
    #endif

    CC_RenderFuns.SetCcInfo(NULL, CC_BLOCK0_ADDR, u32CCBlock0Addr);
    CC_RenderFuns.SetCcInfo(NULL, CC_BLOCK1_ADDR, u32CCBlock1Addr);

    // set variables for T3/T2
   // g_bMVD_ON_MIU1 = ((VDEC_AEON_MEMORY_TYPE & MIU1) ? TRUE : FALSE);

}

///////////////////////////////////////////////////////////////////////////////
/// API for Setting variable info to CC system::
/// Setting variable info to CC system
/// @param pCaptionVarSetting \b IN  User Setting
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_SetVarSetting(stCaptionSettingVariables *pCaptionVarSetting)
{
    if(pCaptionVarSetting != NULL)
    {
        if(pCaptionVarSetting->u32ATV_Axis_xpos != _stCCVarSetting.u32ATV_Axis_xpos)
            _stCCVarSetting.u32ATV_Axis_xpos = pCaptionVarSetting->u32ATV_Axis_xpos;

        if(pCaptionVarSetting->u32ATV_Axis_ypos != _stCCVarSetting.u32ATV_Axis_ypos)
            _stCCVarSetting.u32ATV_Axis_ypos = pCaptionVarSetting->u32ATV_Axis_ypos;

        if(pCaptionVarSetting->u32DTV_Axis_xpos != _stCCVarSetting.u32DTV_Axis_xpos)
            _stCCVarSetting.u32DTV_Axis_xpos = pCaptionVarSetting->u32DTV_Axis_xpos;

        if(pCaptionVarSetting->u32DTV_Axis_ypos != _stCCVarSetting.u32DTV_Axis_ypos)
            _stCCVarSetting.u32DTV_Axis_ypos = pCaptionVarSetting->u32DTV_Axis_ypos;

        if(pCaptionVarSetting->u32Text_608_rowno != _stCCVarSetting.u32Text_608_rowno)
            _stCCVarSetting.u32Text_608_rowno = pCaptionVarSetting->u32Text_608_rowno;

        if(pCaptionVarSetting->u32Text_608_ypos != _stCCVarSetting.u32Text_608_ypos)
            _stCCVarSetting.u32Text_608_ypos = pCaptionVarSetting->u32Text_608_ypos;

        if(pCaptionVarSetting->u32Cc_lang != _stCCVarSetting.u32Cc_lang)
            _stCCVarSetting.u32Cc_lang = pCaptionVarSetting->u32Cc_lang;

        if(pCaptionVarSetting->u32Row_608_toprsvheight != _stCCVarSetting.u32Row_608_toprsvheight)
            _stCCVarSetting.u32Row_608_toprsvheight = pCaptionVarSetting->u32Row_608_toprsvheight;

        if(pCaptionVarSetting->u32Row_608_btmrsvheight != _stCCVarSetting.u32Row_608_btmrsvheight)
            _stCCVarSetting.u32Row_608_btmrsvheight = pCaptionVarSetting->u32Row_608_btmrsvheight;

        if(pCaptionVarSetting->u32Row_708_toprsvheight != _stCCVarSetting.u32Row_708_toprsvheight)
            _stCCVarSetting.u32Row_708_toprsvheight = pCaptionVarSetting->u32Row_708_toprsvheight;

        if(pCaptionVarSetting->u32Row_708_btmrsvheight != _stCCVarSetting.u32Row_708_btmrsvheight)
            _stCCVarSetting.u32Row_708_btmrsvheight = pCaptionVarSetting->u32Row_708_btmrsvheight;

        if(pCaptionVarSetting->u32CC_608_ScrollStep != _stCCVarSetting.u32CC_608_ScrollStep)
            _stCCVarSetting.u32CC_608_ScrollStep = pCaptionVarSetting->u32CC_608_ScrollStep;

        if(pCaptionVarSetting->u32Timeout_608_capiton != _stCCVarSetting.u32Timeout_608_capiton)
            _stCCVarSetting.u32Timeout_608_capiton = pCaptionVarSetting->u32Timeout_608_capiton;

        if(pCaptionVarSetting->u32Timeout_608_text != _stCCVarSetting.u32Timeout_608_text)
            _stCCVarSetting.u32Timeout_608_text = pCaptionVarSetting->u32Timeout_608_text;

        if(pCaptionVarSetting->u32Timeout_708_caption != _stCCVarSetting.u32Timeout_708_caption)
            _stCCVarSetting.u32Timeout_708_caption = pCaptionVarSetting->u32Timeout_708_caption;

        if(pCaptionVarSetting->u32Timeout_DTV_caption != _stCCVarSetting.u32Timeout_DTV_caption)
            _stCCVarSetting.u32Timeout_DTV_caption = pCaptionVarSetting->u32Timeout_DTV_caption;

        if(pCaptionVarSetting->s32XPos_offset != _stCCVarSetting.s32XPos_offset)
            _stCCVarSetting.s32XPos_offset = pCaptionVarSetting->s32XPos_offset;

        if(pCaptionVarSetting->s32YPos_offset != _stCCVarSetting.s32YPos_offset)
            _stCCVarSetting.s32YPos_offset = pCaptionVarSetting->s32YPos_offset;

        if(pCaptionVarSetting->u8CCEnableSVS != _stCCVarSetting.u8CCEnableSVS)
            _stCCVarSetting.u8CCEnableSVS = pCaptionVarSetting->u8CCEnableSVS;

        if(pCaptionVarSetting->u8CCEnableSHS != _stCCVarSetting.u8CCEnableSHS)
            _stCCVarSetting.u8CCEnableSHS = pCaptionVarSetting->u8CCEnableSHS;

    }
}

///////////////////////////////////////////////////////////////////////////////
/// API for Setting User selection info to CC system::
/// Setting User selection info to CC system
/// @param pCaptionOSDSetting \b IN  User Setting
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_SetOsdSetting(stCaptionSetting_Type * pCaptionOSDSetting)
{
    if(fCCDynamicMemAllocFlag == FALSE)
    {
        printf("\n Can't allocate caption memory!!!");
        return;
    }

    //Disable now, and enable it later!
    (*pCaptionOSDSetting).u8CSWinPosition = CAPTION_WIN_NONE;
    (*pCaptionOSDSetting).u8CSWinGrid = CAPTION_WIN_GRID_NONE;
    memcpy(&stCCOSDSetting, pCaptionOSDSetting, sizeof(stCaptionSetting_Type));

    CC_SYSINFO_DBG(printf("\r\n[OSD] SerMode: %d ; DTV: %d ; ATV: %d ; CCMode: %d ; CSOpMode: %d",
                    stCCOSDSetting.u8CaptionServiceMode,
                    stCCOSDSetting.u8CaptionServiceModeDTV,
                    stCCOSDSetting.u8CaptionServiceModeATV,
                    stCCOSDSetting.u8CCMode,
                    stCCOSDSetting.u8CSOptionMode
                    ));  //CC_DBINFO_Color

    CC_SYSINFO_DBG(printf("\r\n[OSD] FG: %d ; BG: %d ; FO: %d ; BO: %d",
                    stCCOSDSetting.astCaptionOptionCustom.u8CSOptionFGColor,
                    stCCOSDSetting.astCaptionOptionCustom.u8CSOptionBGColor,
                    stCCOSDSetting.astCaptionOptionCustom.u8CSOptionFGOpacity,
                    stCCOSDSetting.astCaptionOptionCustom.u8CSOptionBGOpacity
                    ));  //CC_DBINFO_Color

    CC_SYSINFO_DBG(printf("\r\n[OSD] FSize: %d ; FStyle: %d ; EColor: %d ; EStyle: %d",
                    stCCOSDSetting.astCaptionOptionCustom.u8CSFontSize,
                    stCCOSDSetting.astCaptionOptionCustom.u8CSFontStyle,
                    stCCOSDSetting.astCaptionOptionCustom.u8CSOptionEdgeColor,
                    stCCOSDSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle
                    ));  //CC_DBINFO_Color

    g_fCCAttrFlag.fCCAttrEnableAutoSTAbyVideoFmt = CC_CONFIG_fCCAttrEnableAutoSTAbyVideoFmt;

    #if PARSING_CC_FONTEDGE
    g_fCCAttrFlag.fCCAttr_EnableFontEdge = TRUE;
    g_fCCAttrFlag.fCCAttr_EdgeOpacity_NoTransparent_Flag = TRUE;   //0: Has Transparent color ; 1: Dont support
    #else
    g_fCCAttrFlag.fCCAttr_EnableFontEdge = FALSE;
    g_fCCAttrFlag.fCCAttr_EdgeOpacity_NoTransparent_Flag = FALSE;   //0: Has Transparent color ; 1: Dont support
    #endif

    g_fCCAttrFlag.fCCAttr_Parity_Error_Solid_Block_Flag = CC_CONFIG_fCCAttr_Parity_Error_Solid_Block_Flag;     // 1: CC608 Parity Check error, create sold block
    g_fCCAttrFlag.fCCAttr_EnableRrvBlK = CC_CONFIG_fCCAttr_EnableRrvBlK;

    #if (KOREAN_CC_ENABLE)
    g_fCCAttrFlag.fCCAttr_Suport_Korean_Flag = TRUE;
    g_fCCAttrFlag.fCCAttr_Wansung_Code_Flag = TRUE;
    g_fCCAttrFlag.fCCAttrEnable24Fonts = CC_CONFIG_fCCAttrEnable24Fonts;
    #else
    g_fCCAttrFlag.fCCAttr_Suport_Korean_Flag = FALSE;
    g_fCCAttrFlag.fCCAttr_Wansung_Code_Flag = FALSE;
    g_fCCAttrFlag.fCCAttrEnable24Fonts = CC_CONFIG_fCCAttrEnable24Fonts;
    #endif

    g_fCCAttrFlag.fCCAttr_EnableSemiTransparentOnTextMode_Flag = CC_CONFIG_fCCAttr_EnableSemiTransparentOnTextMode_Flag;

    g_fCCAttrFlag.fCCAttr_Packet_Dump_Flag = CC_CONFIG_fCCAttr_Packet_Dump_Flag;                    //For Dump CC Data.
    g_fCCAttrFlag.fCCAttrEnableGopZoom = CC_CONFIG_fCCAttrEnableGopZoom;
    g_fCCAttrFlag.fCCAttr_GOP_Use_FBPool2 = CC_CONFIG_fCCAttr_GOP_Use_FBPool2;

    g_fCCAttrFlag.fCCAttr_Support_Border_Opacity = CC_CONFIG_fCCAttr_Support_Border_Opacity;
    g_fCCAttrFlag.fCCAttr_Support_WindowBorder_Flag = CC_CONFIG_fCCAttr_Support_WindowBorder_Flag;
    g_fCCAttrFlag.fCCAttr_DLW_Call_GEngine = CC_CONFIG_fCCAttr_DLW_Call_GEngine;
    g_fCCAttrFlag.fCCAttr_Font_Indention_Flag = CC_CONFIG_fCCAttr_Font_Indention_Flag;
    g_fCCAttrFlag.fCCAttr_Show_Window_Has_Text = CC_CONFIG_fCCAttr_Show_Window_Has_Text;
    g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting = CC_CONFIG_fCCAttr_EnableWindowOptionSetting;
    g_fCCAttrFlag.fCCAttr_Support_Deep_Color = CC_CONFIG_fCCAttr_Support_Deep_Color;       //TRUE: 64 color palette; FALSE: 8 color palette
    g_fCCAttrFlag.fCCAttr_Support_ATVAttrSet_Flag = CC_CONFIG_fCCAttr_Support_ATVAttrSet_Flag;   //Choice For Setting BG&FG Color for ATV.
    g_fCCAttrFlag.fCCAttr_Support_EdgeAttrSet_Flag = CC_CONFIG_fCCAttr_Support_EdgeAttrSet_Flag;  //Choice For Setting Edge Attribute.
    g_fCCAttrFlag.fCCAttr_Support_OtherLanguage_Flag = CC_CONFIG_fCCAttr_Support_OtherLanguage_Flag; //Choice For Setting Other Language(chinese or other).
    g_fCCAttrFlag.fCCAttr_Expletive_Show_Flag = CC_CONFIG_fCCAttr_Expletive_Show_Flag; //Choice For SPA Texttag11!

    #if Support_Caption_Preview
        g_fCCAttrFlag.fCCAttr_Map_UIoption_Flag = FALSE;
    #else
        g_fCCAttrFlag.fCCAttr_Map_UIoption_Flag = TRUE;
    #endif

//    if( ENABLE == g_stFactorySetting.g_u8FactoryImageRotate)
//    {
        g_fCCAttrFlag.fCCAttr_Wait_GFX_Flush_Queue = CC_CONFIG_fCCAttr_Wait_GFX_Flush_Queue;
//    }
//    else
//    {
//        g_fCCAttrFlag.fCCAttr_Wait_GFX_Flush_Queue = FALSE;
//    }
}

/******************************************************************************/
void msAPI_CC_GetCanvasInfo(U8 u8Mode)
{
    if (u8Mode)
    {
        g_u8Row_TopRsvHeight = _stCCVarSetting.u32Row_608_toprsvheight;
        g_u8Row_BtmRsvHeight = _stCCVarSetting.u32Row_608_btmrsvheight;
    }
    else
    {
        g_u8Row_TopRsvHeight = _stCCVarSetting.u32Row_708_toprsvheight;
        g_u8Row_BtmRsvHeight = _stCCVarSetting.u32Row_708_btmrsvheight;

        /* visible area */
        if (g_fCCAttrFlag.fCCAttrEnable24Fonts == TRUE)
        {
            //Coverity 218404
    #if (BRAZIL_CC)
            CC_RenderFuns.GetCcFontInfo(Font_CC[1].fHandle, CC_FONTINFO_WIDTH, &u8CharWidth);
            CC_RenderFuns.GetCcFontInfo(Font_CC[1].fHandle, CC_FONTINFO_HEIGHT, &u8CharHeight);
    #else
            CC_RenderFuns.GetCcFontInfo(Font_CC[16].fHandle, CC_FONTINFO_WIDTH, &u8CharWidth);
            CC_RenderFuns.GetCcFontInfo(Font_CC[16].fHandle, CC_FONTINFO_HEIGHT, &u8CharHeight);
    #endif
            g_u16STA_Width = (u8CharWidth * 42);
            g_u16STA_Height = (u8CharHeight + g_u8Row_TopRsvHeight + g_u8Row_BtmRsvHeight) * 20;
        }
        else
        {
            CC_RenderFuns.GetCcFontInfo(Font_CC[0].fHandle, CC_FONTINFO_WIDTH, &u8CharWidth);
            CC_RenderFuns.GetCcFontInfo(Font_CC[0].fHandle, CC_FONTINFO_HEIGHT, &u8CharHeight);

            g_u16STA_Width = (u8CharHeight * 42);
            g_u16STA_Height = (u8CharHeight + g_u8Row_TopRsvHeight + g_u8Row_BtmRsvHeight) * 20;
        }

        /* left-top position */
        if (g_PNL_TypeSel == PNL_SXGA_AU17_EN05)
        {
          g_u16STA_SXLoc = 196;
          g_u16STA_SYLoc = 84;
          CC_SYSINFO_DBG(printf("\nPNL_AU17_EN05_SXGA"));
        }
        else if (g_PNL_TypeSel == PNL_WXGA_AU20_T200XW02 )    //16:9
        {
            g_u16STA_SXLoc = 148; //296;
            g_u16STA_SYLoc = 57; //68;
        }
//        else if (g_PNL_TypeSel == PNL_AU19PW01_WXGA)    //16:9
//        g_u16STA_SXLoc = 172;
//        g_u16STA_SYLoc = 74;
        else if (g_PNL_TypeSel == PNL_WSXGA_AU22_M201EW01)    //16:10
        {
            g_u16STA_SXLoc = 84;
            g_u16STA_SYLoc = 79;
        }
        else{
            g_u16STA_SXLoc = 100; //32;
            g_u16STA_SYLoc = 70; //32;
        }
    }
}

void LmsAPI_CC_GetCanvasInfo(U8 u8Mode, U8 u8AspectRate)
{
    if (u8Mode)
    {
        g_u8Row_TopRsvHeight = _stCCVarSetting.u32Row_608_toprsvheight;
        g_u8Row_BtmRsvHeight = _stCCVarSetting.u32Row_608_btmrsvheight;
    }
    else
    {
        g_u8Row_TopRsvHeight = _stCCVarSetting.u32Row_708_toprsvheight;
        g_u8Row_BtmRsvHeight = _stCCVarSetting.u32Row_708_btmrsvheight;

        if(CAPTION_ASP_4TO3 == u8AspectRate)
        {
            CC_SYSINFO_DBG(printf("\n 4:3"));
            g_u16STA_Width = (U16)(((U16)msAPI_CC_Panel_WIDTH() * 16) / 25);
            g_u16STA_Height = (U16)(((U16)msAPI_CC_Panel_HEIGHT() * 5) / 6);

            g_u16STA_SXLoc = (U16)(((U16)msAPI_CC_Panel_WIDTH()  - g_u16STA_Width) / 2);
            g_u16STA_SXLoc = (U16)g_u16STA_SXLoc & g_GWIN_ALIGNMENT_MASK;
            g_u16STA_SYLoc = (U16)(((U16)msAPI_CC_Panel_HEIGHT() - g_u16STA_Height) /2);
            /* patch position */
            g_u16STA_SXLoc  += 16;
            g_u16STA_SYLoc  += 35;
        }
        else
        {
            CC_SYSINFO_DBG(printf("\n 16:9"));
            g_u16STA_Width = (U16)(((U16)msAPI_CC_Panel_WIDTH() * 5) / 6);
            g_u16STA_Height = (U16)(((U16)msAPI_CC_Panel_HEIGHT() * 5) / 6);

            g_u16STA_SXLoc = (U16)(((U16)msAPI_CC_Panel_WIDTH()  - g_u16STA_Width) / 2);
            g_u16STA_SXLoc = (U16)g_u16STA_SXLoc & g_GWIN_ALIGNMENT_MASK;
            /* patch position */
//            g_u16STA_SXLoc -= 12;
            g_u16STA_SXLoc += 16;

            g_u16STA_SYLoc = (U16)(((U16)msAPI_CC_Panel_HEIGHT() - g_u16STA_Height) /2);
            /* patch position */
            g_u16STA_SYLoc += 35;
//            g_u16STA_SYLoc -= 10;

            CC_SYSINFO_DBG(printf("\n...sta w=%d, h=%d, sx=%d, sy=%d", g_u16STA_Width, g_u16STA_Height, g_u16STA_SXLoc, g_u16STA_SYLoc));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API for Setting CC708 Safe Title Area::
/// Automatic set STA and location
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_AutoJustifySTA(void)
{
    if (g_fCCAttrFlag.fCCAttrEnable24Fonts == TRUE)
    {
    // Coverity 218403
    #if (BRAZIL_CC)
        CC_RenderFuns.GetCcFontInfo(Font_CC[1].fHandle, CC_FONTINFO_WIDTH, &u8CharWidth);
        CC_RenderFuns.GetCcFontInfo(Font_CC[1].fHandle, CC_FONTINFO_HEIGHT, &u8CharHeight);
    #else
        CC_RenderFuns.GetCcFontInfo(Font_CC[16].fHandle, CC_FONTINFO_WIDTH, &u8CharWidth);
        CC_RenderFuns.GetCcFontInfo(Font_CC[16].fHandle, CC_FONTINFO_HEIGHT, &u8CharHeight);
    #endif

        u16SysInfoTemp1 = u8CharWidth;
        u16SysInfoTemp2 = (u8CharHeight + g_u8Row_TopRsvHeight + g_u8Row_BtmRsvHeight);
        u16SysInfoTemp3 = (u16SysInfoTemp1 * (g_u8MaxColNo+g_u8CC708_RsvBlk_ColNo));
        u16SysInfoTemp4 = (u16SysInfoTemp2 * CC708_MAX_ROW_NUMBER);

        if ((msAPI_CC_Panel_WIDTH()-devPanel_Get_HSYNC_BACK_PORCH()) > u16SysInfoTemp3)
        {
            g_u16STA_Width = u16SysInfoTemp3;
            g_u16STA_SXLoc = ((((U16)msAPI_CC_Panel_WIDTH() - g_u16STA_Width) /2) & g_GWIN_ALIGNMENT_MASK);
        }

        if ((msAPI_CC_Panel_HEIGHT()-devPanel_Get_VSYNC_BACK_PORCH()) > u16SysInfoTemp4)
        {
            g_u16STA_Height = u16SysInfoTemp4;
            g_u16STA_SYLoc = (((U16)msAPI_CC_Panel_HEIGHT() - g_u16STA_Height) /2);
        }

        g_u16STA_SXLoc = ((((U16)msAPI_CC_Panel_WIDTH() - g_u16STA_Width) /2) & g_GWIN_ALIGNMENT_MASK);
        g_u16STA_SYLoc = (((U16)msAPI_CC_Panel_HEIGHT() - g_u16STA_Height) /2);
    }
    else
    {
        CC_RenderFuns.GetCcFontInfo(Font_CC[0].fHandle, CC_FONTINFO_WIDTH, &u8CharWidth);
        CC_RenderFuns.GetCcFontInfo(Font_CC[0].fHandle, CC_FONTINFO_HEIGHT, &u8CharHeight);

        u16SysInfoTemp1 = u8CharWidth;
        u16SysInfoTemp2 = (u8CharHeight + g_u8Row_TopRsvHeight + g_u8Row_BtmRsvHeight);

        if (g_fCCAttrFlag.fCCAttrEnableGopZoom == TRUE) // three font size
        {
            u16SysInfoTemp3 = ((u16SysInfoTemp1 * (g_u8MaxColNo+g_u8CC708_RsvBlk_ColNo)) << 1);
            u16SysInfoTemp4 = ((u16SysInfoTemp2 * CC708_MAX_ROW_NUMBER) << 1);
        }
        else    // one fone size
        {
            u16SysInfoTemp3 = (u16SysInfoTemp1 * (g_u8MaxColNo+2));
            u16SysInfoTemp4 = (u16SysInfoTemp2 * CC708_MAX_ROW_NUMBER);
        }

        #if 0
        printf("\n77-> FW: %u ; FH: %u ; CW: %u ; CH: %u", u16SysInfoTemp1, u16SysInfoTemp2, u16SysInfoTemp3, u16SysInfoTemp4);
        #endif

        if ((msAPI_CC_Panel_WIDTH()-devPanel_Get_HSYNC_BACK_PORCH()) > u16SysInfoTemp3)
        {
            g_u16STA_Width = u16SysInfoTemp3;
            g_u16STA_SXLoc = ((((U16)msAPI_CC_Panel_WIDTH() - g_u16STA_Width) /2) & g_GWIN_ALIGNMENT_MASK);
        }

        if ((msAPI_CC_Panel_HEIGHT()-devPanel_Get_VSYNC_BACK_PORCH()) > u16SysInfoTemp4)
        {
            g_u16STA_Height = u16SysInfoTemp4;
            g_u16STA_SYLoc = (((U16)msAPI_CC_Panel_HEIGHT() - g_u16STA_Height) /2);
        }

        #if 0
        printf("\n77-> CW1: %u ; CH1: %u ; SX: %u ; SY: %u", g_u16STA_Width, g_u16STA_Height, g_u16STA_SXLoc, g_u16STA_SYLoc);
        #endif
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API for Setting CC miscellaneous Requirement::
/// Setting CC miscellaneous
/// @Param u8Mode \b IN  CC Mode selection
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_SetMisInfo(U8 u8Mode)
{
    U8 u8CC708_AspectRatio;
    VDEC_DispInfo _stVidStatus;

    msAPI_VID_GetVidInfo(&_stVidStatus);

    if(CAPTION_ASP_INVALID == g_u8CC708_AspectRatio)
        u8CC708_AspectRatio = _stVidStatus.u8AspectRate - 2;
    else
        u8CC708_AspectRatio = g_u8CC708_AspectRatio;
    /* Get Panel info / font info etc */
    if (g_fCCAttrFlag.fCCAttrEnableAutoSTAbyVideoFmt == FALSE)
        msAPI_CC_GetCanvasInfo(u8Mode);
    else
        LmsAPI_CC_GetCanvasInfo(u8Mode, u8CC708_AspectRatio);

    /* CC608 Screen Setting, 34X15 */
    if (u8Mode == SYSINFO_MODE_608)
    {
    /*
        if (g_fCCAttrFlag.fCCAttrEnable24Fonts == TRUE)
            CC_LANG = _stCCVarSetting.u32Cc_lang*8;   //LARGE FONT TYPE =0
        else
            CC_LANG = _stCCVarSetting.u32Cc_lang;   // STANDARD FONT TYPE =0
    */
           CC_SYSINFO_DBG(printf("\n...u32Cc_lang:%d, fCCAttrEnable24Fonts:%d", _stCCVarSetting.u32Cc_lang, g_fCCAttrFlag.fCCAttrEnable24Fonts));
            switch(_stCCVarSetting.u32Cc_lang)
            {
                case CAPTION_FONTSIZE_SMALL:
                   if (g_fCCAttrFlag.fCCAttrEnable24Fonts == TRUE)
                        CC_LANG = 8;
                    else
                        CC_LANG = 1;
                    break;

                case CAPTION_FONTSIZE_NORMAL:
                    if (g_fCCAttrFlag.fCCAttrEnable24Fonts == TRUE)
                        CC_LANG = 0;
                    else
                        CC_LANG = 0;
                    break;

                case CAPTION_FONTSIZE_LARGE:
                    if (g_fCCAttrFlag.fCCAttrEnable24Fonts == TRUE)
                        CC_LANG = 16;
                    else
                        CC_LANG = 2;
                    break;

                 default:
                 case CAPTION_FONTSIZE_DEFAULT:
                    CC_LANG = 0;
                    break;
            }


      #if((ATSC_CC == ATV_CC)||(BRAZIL_CC))
           // CC_LANG = 16;
	     CC_LANG = 0;  //jany add for milan ck3
      #endif
        CC_LANG_BAK = CC_LANG;

        // Choose the Korean font table
      #if KOREAN_CC_ENABLE
         switch(_stCCVarSetting.u32Cc_lang)
         {
            case CAPTION_FONTSIZE_NORMAL:
            CC_LANG_KOREAN_BAK = CC_LANG_KOREAN_TYPE;
                break;
            case CAPTION_FONTSIZE_SMALL:
            CC_LANG_KOREAN_BAK = CC_LANG_KOREAN_TYPE+1;
                break;
            case CAPTION_FONTSIZE_LARGE:
            CC_LANG_KOREAN_BAK = CC_LANG_KOREAN_TYPE+2;
                break;
            default:
                break;
          }
      #endif

        /* Get Font Width and Height */
        CC_RenderFuns.GetCcFontInfo(Font_CC[CC_LANG].fHandle, CC_FONTINFO_WIDTH, &g_u8CCFontWidth);
        CC_RenderFuns.GetCcFontInfo(Font_CC[CC_LANG].fHandle, CC_FONTINFO_HEIGHT, &g_u8CCFontHeight);

        CC_SYSINFO_DBG(printf("\n...w:%d, h:%d , Handle: %d", g_u8CCFontWidth, g_u8CCFontHeight, CC_LANG));

        g_u8CCRowWidth = g_u8CCFontWidth;
        g_u8CCRowHeight = (g_u8Row_TopRsvHeight + g_u8CCFontHeight + g_u8Row_BtmRsvHeight);

      #if KOREAN_CC_ENABLE
        U32 u32KoreanMaxCol, u32KoreanMaxRow;
        u32KoreanMaxCol = u32KoreanMaxRow = 0;

        CC_DecoderFuns.GetDecodeInfo(KOREAN_CC_ROW_NUMBER, &u32KoreanMaxRow);
        CC_DecoderFuns.GetDecodeInfo(KOREAN_CC_COL_NUMBER, &u32KoreanMaxCol);

        u16SysInfoTemp1 = ((g_u8CCRowWidth * u32KoreanMaxCol));
        u16SysInfoTemp2 = ((g_u8CCRowHeight * u32KoreanMaxRow));
      #else
        u16SysInfoTemp1 = ((g_u8CCRowWidth * CC_MAX_COL_NUMBER));
        u16SysInfoTemp2 = ((g_u8CCRowHeight * CC_MAX_ROW_NUMBER));
      #endif

        g_u16Axis_XPos = ((((U16)msAPI_CC_Panel_WIDTH()) - u16SysInfoTemp1) >> 1);
        g_u16Axis_XPos = CC_ALIGNED_VALUE(g_u16Axis_XPos, g_GWIN_ALIGND_VALUE);
        g_u16Axis_YPos = ((((U16)msAPI_CC_Panel_HEIGHT()) - u16SysInfoTemp2) >> 1);

        g_u8Text_RowNo = 15;
        g_u8Text_YPos = 0;
        g_u8priority = 0;

        if(_stCCVarSetting.u32ATV_Axis_xpos > 0)
            g_u16Axis_XPos  = _stCCVarSetting.u32ATV_Axis_xpos;
        if(_stCCVarSetting.u32ATV_Axis_ypos > 0)
            g_u16Axis_YPos  = _stCCVarSetting.u32ATV_Axis_ypos;
        if(_stCCVarSetting.u32Text_608_rowno > 0)
            g_u8Text_RowNo  = _stCCVarSetting.u32Text_608_rowno;
        if(_stCCVarSetting.u32Text_608_ypos > 0)
            g_u8Text_YPos   = _stCCVarSetting.u32Text_608_ypos;

        CC_DecoderFuns.Timeout_Threshold(_stCCVarSetting.u32Timeout_608_capiton, _stCCVarSetting.u32Timeout_608_text);//270000);//hjkoh 071204 remove text timeout.

        // set CC608 error stop threshold
        // high is 5, low is 2 (in 1 second, how many pair CC data is incorrect
        // if error pair in 1 second is higher than 5, stop cc display
        // if error pair in 1 second is lower than 2, resume cc display
        //msAPI_CC608_ErrorStop_Threshold(5, 2);

        CC_SYSINFO_DBG(printf("\n6XLoc: %u ; YPos: %u ; PW: %u ; PH: %u", g_u16Axis_XPos, g_u16Axis_YPos, (U16)msAPI_CC_Panel_WIDTH(), (U16)msAPI_CC_Panel_HEIGHT()));
        CC_SYSINFO_DBG(printf("\n6Xlang: %u ; Kor lang: %u", CC_LANG, CC_LANG_KOREAN_BAK));

        return ;
    }

    /* CC708 Screen Setting */
    if (u8Mode == SYSINFO_MODE_708)
    {
        /* Get the coordinate */
      #if (KOREAN_CC_ENABLE)
        if(TRUE == g_fCCAttrFlag.fCCAttr_Suport_Korean_Flag)
        {
            msAPI_VID_GetVidInfo(&_stVidStatus);

                if (ASP_4TO3 == _stVidStatus.u8AspectRate)
                {
                    g_u8WinAnkor_GridWidthMax = 160;
                    g_u8MaxColNo = 40;  // 0 ~ 31, total 32
                    CC_SYSINFO_DBG(printf("\nASP_4TO3"));
                }
                else
                {
                    g_u8WinAnkor_GridWidthMax = 210;
                    g_u8MaxColNo = 52;  // 0 ~ 41, total 42
                    CC_SYSINFO_DBG(printf("\nASP_16TO9"));
                }
        }
        else
      #endif
        {
            //msAPI_VID_GetVidInfo(&_stVidStatus);

            if (CAPTION_ASP_4TO3 == u8CC708_AspectRatio)
            {
                g_u8WinAnkor_GridWidthMax = 160;
                g_u8MaxColNo = 32;  // 0 ~ 31, total 32
                CC_SYSINFO_DBG(printf("\nASP_4TO3"));
            }
            else
            {
                g_u8WinAnkor_GridWidthMax = 210;
                g_u8MaxColNo = 42;  // 0 ~ 41, total 42
                CC_SYSINFO_DBG(printf("\nASP_16TO9"));
            }
        }
        g_u8MaxColPlus = g_u8MaxColNo + g_u8CC708_RsvBlk_ColNo + 1;
        g_u8WinAnkor_GridHeightMax = 75;

      #if 0
        printf("\n7XLoc1: %u ; YPos: %u ; PW: %u ; PH: %u", g_u16STA_SXLoc, g_u16STA_SYLoc, (U16)msAPI_CC_Panel_WIDTH(), (U16)msAPI_CC_Panel_HEIGHT());
      #endif

        //if (g_fCCAttrFlag.fCCAttrEnableAutoSTAbyVideoFmt == FALSE)
        //    msAPI_CC_AutoJustifySTA();

        g_u8WinAnkor_GridWidthSpace = (U8)((g_u16STA_Width * 10) / g_u8WinAnkor_GridWidthMax);
        g_u8WinAnkor_GridHeightSpace = (U8)((g_u16STA_Height * 10) / g_u8WinAnkor_GridHeightMax);
        //printf("\ng_u8WinAnkor_GridHeightSpace: %bd", g_u8WinAnkor_GridHeightSpace);

        g_u16Axis_XPos = g_u16STA_SXLoc & g_GWIN_ALIGNMENT_MASK;
        g_u16Axis_YPos = g_u16STA_SYLoc;

        if(_stCCVarSetting.u32DTV_Axis_xpos > 0)
            g_u16Axis_XPos  = _stCCVarSetting.u32DTV_Axis_xpos;
        if(_stCCVarSetting.u32DTV_Axis_ypos > 0)
            g_u16Axis_YPos  = _stCCVarSetting.u32DTV_Axis_ypos;

        if(_stCCVarSetting.u32Timeout_708_caption > 0)
            g_u32708CaptionTimeout = _stCCVarSetting.u32Timeout_708_caption;
        else
            g_u32708CaptionTimeout = 16000;

        CC_SYSINFO_DBG(printf("\nXLoc: %u ; YPos: %u", g_u16Axis_XPos, g_u16Axis_YPos));
        CC_SYSINFO_DBG(printf("\nSTA W: %u, H: %u", g_u16STA_Width, g_u16STA_Height));
        CC_SYSINFO_DBG(printf("\nPanel W: %u, H: %u", (U16)msAPI_CC_Panel_WIDTH(), (U16)msAPI_CC_Panel_HEIGHT()));
    }

}

///////////////////////////////////////////////////////////////////////////////
/// API for getting UI panel width::
/// get UI panel width
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
U16 msAPI_CC_Panel_WIDTH(void)
{
    if(UI_OSD_PANE_W > 0)
    {
        #if BRAZIL_CC
            return CC_WINDOW_WIDTH_SWF;
        #elif ((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
            return 960;//(U16)UI_OSD_PANE_W;
        #else
            if (UI_OSD_PANE_W == 1920)
                return 1366; //By using stretch method to fulfill
            else
                return (U16)UI_OSD_PANE_W;
        #endif
    }
    else
    {
        return (U16)devPanel_WIDTH();
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API for getting UI panel height::
/// get UI panel height
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
U16 msAPI_CC_Panel_HEIGHT(void)
{
    if(UI_OSD_PANE_H > 0)
    {
        #if BRAZIL_CC
            return CC_WINDOW_HEIGHT_SWF;
        #elif ((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
            return 540;//(U16)UI_OSD_PANE_H;
        #else
            if (UI_OSD_PANE_H == 1080)
                return 768; //By using stretch method to fulfill
            else
                return (U16)UI_OSD_PANE_H;
        #endif
    }
    else
    {
        return (U16)devPanel_HEIGHT();
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API for getting UI panel height::
/// get UI panel height
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_Customer_GetVariables(stIntCustomerVariables *pp)
{
    pp->cc_lang = CC_LANG;
    pp->cc_lang_bak = CC_LANG_BAK;
    pp->cc_lang_korean_bak = CC_LANG_KOREAN_BAK;

    pp->u16Axis_XPos = g_u16Axis_XPos;
    pp->u16Axis_YPos = g_u16Axis_YPos;

    pp->u16STA_Width = g_u16STA_Width;
    pp->u16STA_Height = g_u16STA_Height;

    pp->u16STA_SXLoc = g_u16STA_SXLoc;
    pp->u16STA_SYLoc = g_u16STA_SYLoc;

    pp->u8CCFontWidth = g_u8CCFontWidth;
    pp->u8CCFontHeight = g_u8CCFontHeight;
    pp->u8CCRowWidth = g_u8CCRowWidth;
    pp->u8CCRowHeight = g_u8CCRowHeight;

    pp->u8MaxColNo = g_u8MaxColNo;
    pp->u8MaxColPlus = g_u8MaxColPlus;

    pp->u8Row_TopRsvHeight = g_u8Row_TopRsvHeight;
    pp->u8Row_BtmRsvHeight = g_u8Row_BtmRsvHeight;

    pp->u8Text_RowNo = g_u8Text_RowNo;
    pp->u8Text_YPos = g_u8Text_YPos;

    pp->u8WinAnkor_GridWidthMax = g_u8WinAnkor_GridWidthMax;
    pp->u8WinAnkor_GridHeightMax = g_u8WinAnkor_GridHeightMax;
    pp->u8WinAnkor_GridWidthSpace = g_u8WinAnkor_GridWidthSpace;
    pp->u8WinAnkor_GridHeightSpace = g_u8WinAnkor_GridHeightSpace;

    pp->u8CCType_Option = u8CCType_Option;

}

///////////////////////////////////////////////////////////////////////////////
/// API for getting UI panel height::
/// get UI panel height
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_Customer_GetMemoryAddr(stIntMemoryAddr *pp)
{
    pp->u32CCCacheAddr = u32CCCacheAddr;//MsOS_PA2KSEG1(u32CCCacheAddr);
    pp->u32CCCacheSize = u32CCCacheSize;
    pp->u32CC608CacheAddr = u32CC608CacheAddr;//MsOS_PA2KSEG1(u32CC608CacheAddr);
    pp->u32CC608CacheSize = u32CC608CacheSize;

    pp->pstCC608_Cntl = (U8 *)pstCC608_Cntl;
    pp->Service_Buffer = (U8 *)CC_Service_Buffer;
    pp->cc608DispBuff = (U8 *)cc608DispBuff;
    #if KOREAN_CC_ENABLE
    pp->cc608DispBuffa = (U8 *)cc608DispBuffa;
    #endif

    pp->CCBBlockInfo = (U8 *)CCBBlockInfo;
    pp->pstCC708_Cntl = (U8 *)pstCC708_Cntl;
    pp->pstCC708_Trp = (U8 *)pstCC708_Trp;
    pp->CCTextBuf = (U8 *)CCTextBuf;
}

///////////////////////////////////////////////////////////////////////////////
/// API for sending Decode control data
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_SendingVar(void)
{
    // set memory addr
    msAPI_CC_Customer_GetMemoryAddr(&stIntMemAddr);

    // set global variables
    msAPI_CC_Customer_GetVariables(&stIntCustomerVar);

    CC_DecoderFuns.InitVar(&stIntMemAddr, &stIntCustomerVar, &g_fCCAttrFlag,  &stCCOSDSetting);
}

#if BRAZIL_CC

/******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
/// API for setting Brazil CC parameters
/// @Param u8Mode \b IN DTV switch
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_Brazil_SetMisInfo(U8 u8Mode) // 1: Brazil DTV 0: None
{
    if (u8Mode == ENABLE)
    {
        #if 0
        if(_stCCVarSetting.u32Cc_lang <= CAPTION_FONTSIZE_LARGE)
        {
            #if 0
            CC_LANG = _stCCVarSetting.u32Cc_lang;
            #else // for all panels in DTV CC
            CC_LANG = CAPTION_FONTSIZE_LARGE;   // 18x18
            #endif
        }
        else
        {
            CC_LANG = CAPTION_FONTSIZE_SMALL;
        }
        #else
        CC_LANG = CAPTION_FONTSIZE_NORMAL;   // 18x18
        #endif

      //  g_u8TranslucentValue = 0;

        if(_stCCVarSetting.s32XPos_offset!= 0)
        {
            g_u16Axis_XPos  = _stCCVarSetting.s32XPos_offset;
        }

        if(_stCCVarSetting.s32YPos_offset != 0)
        {
            g_u16Axis_YPos  = _stCCVarSetting.s32YPos_offset;
        }
/*
        if(_stCCVarSetting.u8TranslucentAlphaValue != 0)
        {
            g_u8TranslucentValue  = _stCCVarSetting.u8TranslucentAlphaValue;
        }
*/
        if(_stCCVarSetting.u8CCEnableSVS != 0)
            g_bCCEnableSVS = TRUE;
        else
            g_bCCEnableSVS = FALSE;

        if(_stCCVarSetting.u8CCEnableSHS != 0)
            g_bCCEnableSHS = TRUE;
        else
            g_bCCEnableSHS = FALSE;
/*
        if(_stCCVarSetting.u8CCDebug != 0)
        {
            g_bCCIsDebug  = TRUE;
        }
*/
        // DTV Time-Out
        if(_stCCVarSetting.u32Timeout_DTV_caption != 0)
        {
            gu32DTVTimeOut  = _stCCVarSetting.u32Timeout_DTV_caption;
        }
        else
        {
            gu32DTVTimeOut  = CC_DTV_TIME_OUT_MS;
        }
    }

    return;
}

void msAPI_CC_Brazil_SysInfoInit(void)
{
    // reset CC DRAM parameters

    u32CCBlock0Addr = (U32)_PA2VA(((DTVCC_BLOCK0_START_MEMORY_TYPE& MIU1) ? (DTVCC_BLOCK0_START_ADR | MIU_INTERVAL) : (DTVCC_BLOCK0_START_ADR)));
    u32CCBlock0Size = (U32)DTVCC_BLOCK0_START_LEN;
    u32CCBlock1Addr = (U32)_PA2VA(((DTVCC_BLOCK1_START_MEMORY_TYPE& MIU1) ? (DTVCC_BLOCK1_START_ADR | MIU_INTERVAL) : (DTVCC_BLOCK1_START_ADR)));
    u32CCBlock1Size = (U32)DTVCC_BLOCK1_START_LEN;
    u32CCQueueAddr  = (U32)_PA2VA(((DTVCC_QUEUE_START_MEMORY_TYPE& MIU1) ? (DTVCC_QUEUE_START_ADR | MIU_INTERVAL) : (DTVCC_QUEUE_START_ADR)));
    u32CCQueueSize  = (U32)DTVCC_QUEUE_START_LEN;
}

#endif

#undef MSAPI_CC_SYSINFO_C


