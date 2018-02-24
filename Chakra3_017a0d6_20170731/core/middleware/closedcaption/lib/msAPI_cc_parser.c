//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (MStar Software are intellectual property of MStar Semiconductor, Inc. (â€œMStarâ€ and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar.
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (â€œTermsâ€ and to comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
// 2. You understand that MStar Software might include, incorporate or be supplied together with third party software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party software.
// 3. MStar Software and any modification/derivatives thereof shall be deemed as MStar confidential information and you agree to keep MStar confidential information in strictest confidence and not disclose to any third party.
// 4. MStar Software is provided on an basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.
//     In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.
//     You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
// 5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customers product (Services).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an basis and the warranty disclaimer set forth in Section 4 above shall apply.
// 6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
// 7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei,
//     Taiwan and the language shall be English.  The arbitration award shall be final and binding to both parties.
//***********************************************************************************
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

#define MSAPI_CC_PARSER_C
///////////////////////////////////////////////////////////////////////////////
/// @file msapi_cc_parser.h
/// @brief AP Interface for Closed Caption Protocol Parser and system initialization
/// @author MStarSemi Inc.
///
///////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdio.h>
#include "datatype.h"
//#include "drvmvd_cc.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "hwreg.h"
#include "msAPI_Timer.h"
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"
#include "msAPI_Font.h"
#include "msAPI_OSD.h"
//#include "apiVDEC.h"
#include "mapi_cc_common.h"
#include "mapi_cc_interface.h"
#include "mapi_cc_decode.h"
#include "mapi_cc_render.h"
#include "mapi_cc_interface.h"
#include "mapi_cc_monitor.h"
#include "msAPI_cc_parser.h"
#include "msAPI_cc_sysinfo.h"

//#if((ATSC_CC != BRA_CC) && (ATSC_CC != ATV_CC))
//#include "MApp_EpgDB_ATSC.h"
//#endif

#define CC_DBINFO_CMD608_1(x)     //x

#ifndef KEEP_UNUSED_FUNC
#define KEEP_UNUSED_FUNC    0
#endif

#define D6CC_EXIST_MONITORPERIOD     1000  //msec
#define D7CC_EXIST_MONITORPERIOD     60000   //ms

#define MAXCCTEXTBUFSIZE    55 //45

/* Extenal Function list */
//CC Driver
/*
extern void MDrv_CC_Init(void);
extern void MDrv_CC_CM_SetMVDRB_HWAddr(U32 u32StartAddress, BOOLEAN u8CC608);
extern void MDrv_CC_CM_SetParsingType(U8 u8Operation, U16 u16BufferSize, BOOLEAN u8CC608);
//extern BOOLEAN MDrv_CC_CM_GetMVDDecodeStatus(void);
*/
//CC Parser

// External Var

//extern stCaptionSettingType stCCOSDSetting;
U32 u32CC_LastGetTime, u32CC_LastGetTime_608;
#if 0
// -- SH@ 20100401, CC local version, only for local tracking used -->
U8 code CC_VBuf[32] = {'M', 'S', 'I', 'F', '0', '3',
                       0,0,0,0,0,0,
                       'C','C','_','E','.',
                       '0','0','.',
                       '0','1','.',
                       '0', '0' , '4' , '7' , '0' , '3' , '3', '8' ,
                        0};
// <------------------------------------------------------------------
#endif
/*  Common Variable  */
U8 u8CCPR_Temp1, u8CCPR_Temp2, u8CCPR_Temp3, u8CCPR_Temp4;
U16 u16CCPR_Temp1, u16CCPR_Temp2, u16CCPR_Temp3;
U32 u32CCPR_Temp1, u32CCPR_Temp2, u32CCPR_Temp3;

BOOLEAN fCCPacketParsingFlag;
BOOLEAN fCC608Using157;
BOOLEAN XDSFullyCheckFlag = TRUE;

U8  u8CC608Avail;
U8  u8CC708Avail;
U8  u8CCEnableDispGwin;

U8  volatile CC_Packet_Buffer[SIZE_OF_PACKET_BUFFER];

U8 CC_Remain_SrvBuf[128];
U8 u8ServiceRemain_Index;
U8 u8ServiceDelay_Index;
U32 CC_EachPacketBuffer_Size;
/*
// reset CC DRAM parameters
U32 u32CC608RbAddr = (U32)((CC608MVD_RINGBUFFER_START_MEMORY_TYPE & MIU1) ? (CC608MVD_RINGBUFFER_START_ADR | MIU_INTERVAL) : (CC608MVD_RINGBUFFER_START_ADR));
U32 u32CC608RbSize = (U32)CC608MVD_RINGBUFFER_START_LEN;
U32 u32CC708RbAddr =(U32)((CC708MVD_RINGBUFFER_START_MEMORY_TYPE & MIU1) ? (CC708MVD_RINGBUFFER_START_ADR | MIU_INTERVAL) : (CC708MVD_RINGBUFFER_START_ADR));
U32 u32CC708RbSize = (U32)CC708MVD_RINGBUFFER_START_LEN;
U32 u32CCCacheAddr = (U32) ((CCMVD_CACHE_BUFFER_MEMORY_TYPE & MIU1) ? (CCMVD_CACHE_BUFFER_ADR | MIU_INTERVAL) : (CCMVD_CACHE_BUFFER_ADR));
U32 u32CCCacheSize = (U32)CCMVD_CACHE_BUFFER_LEN;
U32 u32CC608CacheAddr = (U32) ((CC608_DISPBUFFER_START_MEMORY_TYPE & MIU1) ? (CC608_DISPBUFFER_START_ADR | MIU_INTERVAL) : (CC608_DISPBUFFER_START_ADR));
U32 u32CC608CacheSize = (U32)CC608_DISPBUFFER_START_LEN;
U32 u32CCBlock0Addr =(U32) ((DTVCC_BLOCK0_START_MEMORY_TYPE & MIU1) ? (DTVCC_BLOCK0_START_ADR | MIU_INTERVAL) : (DTVCC_BLOCK0_START_ADR));
U32 u32CCBlock0Size = (U32)DTVCC_BLOCK0_START_LEN;
U32 u32CCBlock1Addr =(U32) ((DTVCC_BLOCK1_START_MEMORY_TYPE & MIU1) ? (DTVCC_BLOCK1_START_ADR | MIU_INTERVAL) : (DTVCC_BLOCK1_START_ADR));
U32 u32CCBlock1Size = (U32)DTVCC_BLOCK1_START_LEN;
*/
U32 u32CC608RbAddr, u32CC608RbSize;
U32 u32CC708RbAddr, u32CC708RbSize;
U32 u32CCCacheAddr, u32CCCacheSize;
U32 u32CC608CacheAddr, u32CC608CacheSize;
U32 u32CCBlock0Addr,  u32CCBlock0Size;
U32 u32CCBlock1Addr, u32CCBlock1Size;
U16 ccCnt=0;

#if 0
//#if (CC_USE_TEST_PATTERN == 3)
U32 u32CC608_test_patterns_TableAddr;
U32 u32GetCnt=0;
#endif

BOOLEAN cc_driver_need_init;
//#if (CC_FLUSH_MECHANISM == 1)
//extern U32 g_u32AveSpeedTimeVal;
//#endif

#if 0
U8 u8CCLibVer[32] = {CC_VER()};
#else
static MSIF_Version _mw_cc_version = {
    .MW = { MW_CC_VER },
};
#endif

BOOLEAN bCC708Enable;

BOOLEAN bCC608IsValid;

///////////////////////////////////////////////////////////////////////////////
/// API for Get CC Library Version
/// @Param *pVer \b OUT Version 6 Bytes for CC Lib
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
#if 0
void msAPI_CC_GetLIBVerString(U8 *pVer)
{
    if(pVer != NULL)
    {
        memcpy(pVer, &u8CCLibVer[0], sizeof(u8CCLibVer));
    }
}
#else
BOOL msAPI_CC_GetLibVer(const MSIF_Version **ppVersion)
{
    if (!ppVersion)
        return false;

    *ppVersion = &_mw_cc_version;
    return true;
}
#endif

//#if((ATSC_CC != BRA_CC) && (ATSC_CC != ATV_CC))
//extern MS_EPG_EVENT current_event;
//extern U16 current_event_id;
//#endif

///////////////////////////////////////////////////////////////////////////////
/// API for CC System Reset::
/// Reset CC variables
/// @Param u8Mode \b IN  CC Mode selection
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_Reset(void)
{
    u8CC608Avail = 0;
    u8CC708Avail = 0;
    u8CCEnableDispGwin = 0;

    //cc_driver_need_init = TRUE;
    bCC708Enable = FALSE;
#if 0
    //modified in 20160617 for mantis 1146924:cc info abnormal!
    #if ((ATSC_CC != BRA_CC) && (ATSC_CC == DTV_CC))
    MApp_EpgDB_GetCurEvent(&current_event);
    if(current_event_id != current_event.event_id)
    {
        msAPI_CC_ResetExistInfo();
    }
    #else
    msAPI_CC_ResetExistInfo();
    #endif
#endif
    msAPI_CC_ResetExistInfo();

    //printf("R\n");
}

///////////////////////////////////////////////////////////////////////////////
/// API for Closed Caption Driver Block initial::
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_BlockInit(U8 BlockID, U32 u32Address, U32 u32Len)
{
    U8 initialValue;
    if(BlockID == 0)
    {
        initialValue = 0x00;
        CCBBlockInfo->BlockSrc0Address = u32Address;
    }
    else
    {
        initialValue = 0xFF;
        CCBBlockInfo->BlockSrc1Address = u32Address;
    }
    MApi_GFX_ClearFrameBuffer(_VA2PA(u32Address), u32Len, initialValue);
}
///////////////////////////////////////////////////////////////////////////////
/// API for CC System Initialization::
/// Initializing CC Driver, System Controlling functions and variables
/// @Param u8Mode \b IN  CC Mode selection
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_SetDrvVar(void)
{
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_PACKET_BUFFER, (void *)CC_Packet_Buffer);
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_EACHPACKETBUFFER_SIZE, (void *)&CC_EachPacketBuffer_Size);
    CC_SourceFuns.SetInputInfo(CC_INPUT_U32CC608RBADDR, (void *)&u32CC608RbAddr);
    CC_SourceFuns.SetInputInfo(CC_INPUT_U32CC608RBSIZE, (void *)&u32CC608RbSize);
    CC_SourceFuns.SetInputInfo(CC_INPUT_U32CC708RBADDR, (void *)&u32CC708RbAddr);
    CC_SourceFuns.SetInputInfo(CC_INPUT_U32CC708RBSIZE, (void *)&u32CC708RbSize);
    CC_SourceFuns.SetInputInfo(CC_INPUT_U32CCCACHEADDR, (void *)&u32CCCacheAddr);
    CC_SourceFuns.SetInputInfo(CC_INPUT_U32CCCACHESIZE, (void *)&u32CCCacheSize);
    CC_SourceFuns.SetInputInfo(CC_INPUT_U8CCTYPE_OPTION, (void *)&u8CCType_Option);
    CC_SourceFuns.SetInputInfo(CC_INPUT_FACCEXISTFLAG, (void *)&fACCExistFlag);
    CC_SourceFuns.SetInputInfo(CC_INPUT_FDCCEXISTFLAG, (void *)&fDCCExistFlag);
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_DRIVER_NEED_INIT, (void *)&cc_driver_need_init);
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_157_LAST_TIME, (void *)&u32CC157_Last);
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_608_LAST_TIME, (void *)&u32CC608_Last);
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_708_LAST_TIME, (void *)&u32CC708_Last);
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_708_AVAILTYPE, (void *)&u8CC708Avail);
    CC_SourceFuns.SetInputInfo(CC_INPUT_CC_608_AVAILTYPE, (void *)&u8CC608Avail);
    CC_SourceFuns.SetInputInfo(CC_INPUT_XDS_FULLY_CHECK,(void *)&XDSFullyCheckFlag);
}

///////////////////////////////////////////////////////////////////////////////
/// API for Setting Closed Caption type
/// @enInputType  \en IN closed catption type
/// @u32Val        \b   In value of type.
/// @return NULL
///////////////////////////////////////////////////////////////////////////////
void msAPI_CC_SetInputData(EN_PARSER_INPUT enInputType, U32 u32Val)
{
    switch(enInputType)
    {
        case CC_INPUT_CAPTIONTYPE:
            u8CCType_Option = (U8) u32Val;
            break;

        case CC_INPUT_USING157:
            fCC608Using157 = (BOOLEAN) u32Val;
            CC_SourceFuns.SetInputInfo(CC_INPUT_FCC608USING157, &fCC608Using157);
            break;

        case CC_INPUT_PERIODTIME:
            u32CC_Check_Period = u32Val;
            break;

        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API for CC System Initialization::
/// Initializing CC Driver, System Controlling functions and variables
/// @Param u8Mode \b IN  CC Mode selection
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_InitialData(U8 u8CCType, BOOLEAN DTVInUse)
{
    #if 0 //(CC_USE_TEST_PATTERN == 3)
    BININFO _BinInfo;
    BOOLEAN bResult;
    U32 _addr;
    #endif

    u8CCType_Option = u8CCType;
    u32CC_LastGetTime = 0;
    u32CC_LastGetTime_608 = 0;
    cc_driver_need_init = TRUE;
    //msAPI_CC_Reset();

    #ifndef CC_USE_MULTIPLE_GWINS
    //msAPI_CC_SetGOPMode(CC_GOP_MODE_I8);
    //msAPI_CC_VarInit();
    #else
    //msAPI_CC_SetGOPMode(CC_GOP_MODE_2266);
    #endif

    g_fCCAttrFlag.fCCAttr_Italics_FromTRP_Flag = TRUE;
    g_fCCAttrFlag.fCCAttr_Underline_FromTRP_Flag = TRUE;

    if (stCCOSDSetting.u8CSOptionMode == CAPTION_OPTIONMODE_SETBYSTREAM)
    {
        g_fCCAttrFlag.fCCAttr_FGColor_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_FGOpacity_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_BGColor_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_BGOpacity_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_WindowColor_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_WindowOpacity_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_FontStyle_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_FontSize_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_EdgeStyle_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_EdgeColor_FromTRP_Flag = TRUE;
        g_fCCAttrFlag.fCCAttr_WinColorTransparent_WhenFlash_Flag = FALSE;
    }
    else
    {
        if (g_fCCAttrFlag.fCCAttr_Map_UIoption_Flag ==  FALSE)
        {
            g_fCCAttrFlag.fCCAttr_FGColor_FromTRP_Flag = FALSE;
            g_fCCAttrFlag.fCCAttr_FGOpacity_FromTRP_Flag = FALSE;
            g_fCCAttrFlag.fCCAttr_BGColor_FromTRP_Flag = FALSE;
            g_fCCAttrFlag.fCCAttr_BGOpacity_FromTRP_Flag = FALSE;
            if(g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting == TRUE)
            {
                g_fCCAttrFlag.fCCAttr_WindowColor_FromTRP_Flag = FALSE;
                g_fCCAttrFlag.fCCAttr_WindowOpacity_FromTRP_Flag = FALSE;
            }
            else
            {
                g_fCCAttrFlag.fCCAttr_WindowColor_FromTRP_Flag = TRUE;
                g_fCCAttrFlag.fCCAttr_WindowOpacity_FromTRP_Flag = TRUE;
            }
            g_fCCAttrFlag.fCCAttr_FontStyle_FromTRP_Flag = FALSE;
            g_fCCAttrFlag.fCCAttr_FontSize_FromTRP_Flag = FALSE;
            g_fCCAttrFlag.fCCAttr_EdgeStyle_FromTRP_Flag = FALSE;
            g_fCCAttrFlag.fCCAttr_EdgeColor_FromTRP_Flag = FALSE;
            g_fCCAttrFlag.fCCAttr_WinColorTransparent_WhenFlash_Flag = TRUE;
        }
        else
        {
            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionFGColor == CAPTION_FGCOLOR_DEFAULT)
                g_fCCAttrFlag.fCCAttr_FGColor_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_FGColor_FromTRP_Flag = FALSE;

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionFGOpacity == CAPTION_FGOPACITY_DEFAULT)
                g_fCCAttrFlag.fCCAttr_FGOpacity_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_FGOpacity_FromTRP_Flag = FALSE;

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionBGColor == CAPTION_BGCOLOR_DEFAULT)
            {
                g_fCCAttrFlag.fCCAttr_BGColor_FromTRP_Flag = TRUE;
            }
            else
            {
                g_fCCAttrFlag.fCCAttr_BGColor_FromTRP_Flag = FALSE;
            }

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionBGOpacity == CAPTION_BGOPACITY_DEFAULT)
            {
                g_fCCAttrFlag.fCCAttr_BGOpacity_FromTRP_Flag = TRUE;
            }
            else
            {
                g_fCCAttrFlag.fCCAttr_BGOpacity_FromTRP_Flag = FALSE;
            }

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionWindowColor == CAPTION_WINDOWCOLOR_DEFAULT)
                g_fCCAttrFlag.fCCAttr_WindowColor_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_WindowColor_FromTRP_Flag = FALSE;

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionWindowOpacity == CAPTION_WINDOWOPACITY_DEFAULT)
                g_fCCAttrFlag.fCCAttr_WindowOpacity_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_WindowOpacity_FromTRP_Flag = FALSE;

            if(g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting == FALSE)
            {
                g_fCCAttrFlag.fCCAttr_WindowColor_FromTRP_Flag = TRUE;
                g_fCCAttrFlag.fCCAttr_WindowOpacity_FromTRP_Flag = TRUE;
            }

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSFontStyle == CAPTION_FONTSTYLE_DEFAULT)
                g_fCCAttrFlag.fCCAttr_FontStyle_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_FontStyle_FromTRP_Flag = FALSE;

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSFontSize == CAPTION_FONTSIZE_DEFAULT)
                g_fCCAttrFlag.fCCAttr_FontSize_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_FontSize_FromTRP_Flag = FALSE;

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle == CAPTION_EDGESTYLE_DEFAULT)
                g_fCCAttrFlag.fCCAttr_EdgeStyle_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_EdgeStyle_FromTRP_Flag = FALSE;

            if (stCCOSDSetting.astCaptionOptionCustom.u8CSOptionEdgeColor == CAPTION_EDGECOLOR_DEFAULT)
                g_fCCAttrFlag.fCCAttr_EdgeColor_FromTRP_Flag = TRUE;
            else
                g_fCCAttrFlag.fCCAttr_EdgeColor_FromTRP_Flag = FALSE;

            g_fCCAttrFlag.fCCAttr_WinColorTransparent_WhenFlash_Flag = TRUE;
         }
    }
    /* fCCAttr_EnableRrvBlK  is only valid for 608 now, support 708 in future
        if (g_fCCAttrFlag.fCCAttr_EnableRrvBlK == TRUE)
            g_u8CC708_RsvBlk_ColNo = 2;
        else
        */
        g_u8CC708_RsvBlk_ColNo = 0;

    if (DTVInUse)
    {
        CC_SourceFuns.DrvInit(MSAPI_CC_TYPE_NTSC_TWOFIELD);       // always enable both 608/708
        CC_SourceFuns.DrvInit(MSAPI_CC_TYPE_DTVCC);       // always enable both 608/708
    }

    msAPI_CC_SetInputData(CC_INPUT_CAPTIONTYPE, u8CCType);
    msAPI_CC_SetDrvVar();    //msAPI_CC_ResetGWIN();

    //msAPI_CC_GWIN_SetGOPInit();
   // MApi_GOP_RegisterEventNotify(msAPI_CC_GetGopArrangeEvent);

    if ((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2)
        || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_TWOFIELD))
    {
    #if KOREAN_CC_ENABLE
    //benny added for korean 608cc in 20160712 for mantis 1060090
    if(g_fCCAttrFlag.fCCAttr_Suport_Korean_Flag == TRUE)
    {
        if(u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1)
            CC_DecoderFuns.KoreanCCEnv(0);
        else if(u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2)
            CC_DecoderFuns.KoreanCCEnv(1);
    }
    else
    {
        CC_DecoderFuns.KoreanCCEnv(0);
    }
    #endif
        msAPI_CC_SetMisInfo(SYSINFO_MODE_608);
        /* Set SW and HW at the same location of the ring buffer */

    //    if (DTVInUse)
     //   {
            //MDrv_CC_CM_SyncMVDRB_SWAddr2HWAddr(SYSINFO_MODE_608);
   //         MApi_VDEC_CC_UpdateWriteAdd(E_VDEC_CC_608, NULL);
     //   }
    }
    else if (u8CCType_Option == MSAPI_CC_TYPE_DTVCC)
    {
        msAPI_CC_SetMisInfo(SYSINFO_MODE_708);
        /* Set SW and HW at the same location of the ring buffer */
        //MDrv_CC_CM_SyncMVDRB_SWAddr2HWAddr(SYSINFO_MODE_708);
   //     MApi_VDEC_CC_UpdateWriteAdd(E_VDEC_CC_708, NULL);
    }

    msAPI_CC_BlockInit(0, u32CCBlock0Addr, u32CCBlock0Size);
    msAPI_CC_BlockInit(1, u32CCBlock1Addr, u32CCBlock1Size);
#if 0
    #if (CC_USE_TEST_PATTERN == 3)
     _BinInfo.B_ID = BIN_ID_WANSUNGCODE_TABLE;

    msAPI_MIU_Get_BinInfo(&_BinInfo, &bResult);
    if (bResult == PASS)
    {
        _addr = _BinInfo.B_FAddr;
        u32CC608_test_patterns_TableAddr = _addr;
        printf("\nTest CC patterns found in flash");
    }

    u32GetCnt = 0;
    #endif
#endif

    msAPI_CC_SendingVar();
}

///////////////////////////////////////////////////////////////////////////////
/// API for Allocating CC System Memory Requirement::
/// Dynamically allocate system required memory
/// @Param u8Mode \b IN  CC Mode selection
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_AllocateMemory(U8 u8CCType)
{
    u8CCType_Option = u8CCType;

    if(fCCDynamicMemAllocFlag)
        msAPI_CC_DeleteMemory();

    fCCDynamicMemAllocFlag = FALSE;

    if (fCCDynamicMemAllocFlag == FALSE)
    {
        if ((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2)
            || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_TWOFIELD))
        {
            CC_DBINFO_L2(printf("\nCreate 608 Memory\n"));

            u16CCPR_Temp1 = sizeof(CC608_CodeSyntax_CntlAttr);
            CC_DBINFO_L2(printf("\nCC608_CodeSyntax_CntlAttr Size -> %x", u16CCPR_Temp1));
            pstCC608_Cntl = (CC608_CodeSyntax_CntlAttr *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
            CC_DBINFO_L2(printf("\nCC608_CodeSyntax_CntlAttr Addr -> %lx", (U16) pstCC608_Cntl));
            if (pstCC608_Cntl == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }

            u16CCPR_Temp1 = SIZE_OF_SERVICE_BUFFER;
            CC_DBINFO_L2(printf("\nSIZE_OF_SERVICE_BUFFER Size -> %lx", u16CCPR_Temp1));
            CC_Service_Buffer = (U8 *) msAPI_Memory_Allocate(u16CCPR_Temp1, BUF_ID_CC);
            if (CC_Service_Buffer == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }

            if(CCBBlockInfo == NULL)
            {
                u16CCPR_Temp1 = sizeof(BlinkBlock_Info);
                CC_DBINFO_L2(printf("\nBlinkBlock Size Size -> %lx", u16CCPR_Temp1));
                CCBBlockInfo = (BlinkBlock_Info *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
                CC_DBINFO_L2(printf("\nCC708_BlinkBlock Addr -> %x", (U16) CCBBlockInfo));
                if (CCBBlockInfo == NULL)
                {
                    CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
                }
            }

            // added by Andy, to save the displayed caption
            u16CCPR_Temp1 = sizeof(CC608_Display_Buffer);
            cc608DispBuff = (CC608_Display_Buffer *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
            if (cc608DispBuff == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }

            #if KOREAN_CC_ENABLE
            cc608DispBuffa = (CC608_Display_Buffer *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
            if (cc608DispBuffa == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }
            #endif

            #if KOREAN_CC_ENABLE
                u16CCPR_Temp2 = sizeof(CC608_CodeSyntax_CntlAttr) + SIZE_OF_SERVICE_BUFFER + 2*sizeof(CC608_Display_Buffer);
            #else
            u16CCPR_Temp2 = sizeof(CC608_CodeSyntax_CntlAttr) + SIZE_OF_SERVICE_BUFFER + sizeof(CC608_Display_Buffer);
            #endif

            CC_DBINFO_L2(printf("\nAllocationSize: %lx", u16CCPR_Temp2));
        }
        else if (u8CCType_Option == MSAPI_CC_TYPE_DTVCC)
        {
            CC_DBINFO_L2(printf("\nCreate 708 Memory\n"));
            u16CCPR_Temp1 = sizeof(CC708_Grph_CntlAttr);
            CC_DBINFO_L2(printf("\nCC708_Grph_CntlAttr Size -> %x", u16CCPR_Temp1));
            pstCC708_Cntl = (CC708_Grph_CntlAttr *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
            CC_DBINFO_L2(printf("\nCC708_Grph_CntlAttr Addr -> %x", (U16) pstCC708_Cntl));
            if (pstCC708_Cntl == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }

            u16CCPR_Temp1 = sizeof(CC708_CodeSyntax_TRPAttr);
            CC_DBINFO_L2(printf("\nCC708_CodeSyntax_TRPAttr Size -> %x", u16CCPR_Temp1));
            pstCC708_Trp = (CC708_CodeSyntax_TRPAttr *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
            CC_DBINFO_L2(printf("\nCC708_CodeSyntax_TRPAttr Addr -> %x", (U16) pstCC708_Trp));
            if (pstCC708_Trp == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }

            //u16CCPR_Temp1 = (g_u8MaxColPlus * sizeof(BlinkChar_Info));
            u16CCPR_Temp1 = (MAXCCTEXTBUFSIZE * sizeof(BlinkChar_Info));
            CC_DBINFO_L2(printf("\nCCTextBuf Size -> %x", u16CCPR_Temp1));
            CCTextBuf = (BlinkChar_Info *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
            CC_DBINFO_L2(printf("\nCC708_CodeSyntax_TRPAttr Addr -> %x", (U16) CCTextBuf));
            if (CCTextBuf == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }

            if(CCBBlockInfo == NULL)
            {
                u16CCPR_Temp1 = sizeof(BlinkBlock_Info);
                CC_DBINFO_L2(printf("\nBlinkBlock Size Size -> %x", u16CCPR_Temp1));
                CCBBlockInfo = (BlinkBlock_Info *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
                CC_DBINFO_L2(printf("\nCC708_BlinkBlock Addr -> %x", (U16) CCBBlockInfo));
                if (CCBBlockInfo == NULL)
                {
                    CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
                }
            }

            u16CCPR_Temp1 = SIZE_OF_SERVICE_BUFFER;
            CC_DBINFO_L2(printf("\SIZE_OF_SERVICE_BUFFER Size -> %x", u16CCPR_Temp1));
            CC_Service_Buffer = (U8 *) msAPI_Memory_Allocate((U16) u16CCPR_Temp1, BUF_ID_CC);
            CC_DBINFO_L2(printf("\nCC_Service_Buffer Addr -> %x", (U16) CC_Service_Buffer));
            if (CC_Service_Buffer == NULL)
            {
                CC_DBINFO_EX(printf("\nCC Allocation Memory Error"));
            }

            u16CCPR_Temp2 = sizeof(CC708_Grph_CntlAttr) + sizeof(CC708_CodeSyntax_TRPAttr) + (MAXCCTEXTBUFSIZE * sizeof(BlinkChar_Info)) + sizeof(BlinkBlock_Info) + SIZE_OF_SERVICE_BUFFER;

            CC_DBINFO_TEMP(printf("\nAllocationSize: %X", u16CCPR_Temp2));
        }

        fCCDynamicMemAllocFlag = TRUE;
    } // if (fCCDynamicMemAllocFlag == FALSE)

}

///////////////////////////////////////////////////////////////////////////////
/// API for Releasing CC System Memory Requirement::
/// Dynamically release system required memory
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_DeleteMemory(void)
{
    if (fCCDynamicMemAllocFlag == TRUE)
    {
        if ((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2)
            || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_TWOFIELD))
        {
            if (pstCC608_Cntl != NULL)
                MSAPI_MEMORY_FREE(pstCC608_Cntl, BUF_ID_CC);
            if (CC_Service_Buffer != NULL)
                MSAPI_MEMORY_FREE(CC_Service_Buffer, BUF_ID_CC);
            if (cc608DispBuff != NULL)
                MSAPI_MEMORY_FREE(cc608DispBuff, BUF_ID_CC);
            if (CCBBlockInfo != NULL)
                MSAPI_MEMORY_FREE(CCBBlockInfo, BUF_ID_CC);
            #if KOREAN_CC_ENABLE
            if (cc608DispBuffa != NULL)
                MSAPI_MEMORY_FREE(cc608DispBuffa, BUF_ID_CC);
            #endif
        }
        else if (u8CCType_Option == MSAPI_CC_TYPE_DTVCC)
        {
            if (pstCC708_Cntl != NULL)
                MSAPI_MEMORY_FREE(pstCC708_Cntl, BUF_ID_CC);
            if (pstCC708_Trp != NULL)
                MSAPI_MEMORY_FREE(pstCC708_Trp, BUF_ID_CC);
            if (CC_Service_Buffer != NULL)
                MSAPI_MEMORY_FREE(CC_Service_Buffer, BUF_ID_CC);
            if (CCBBlockInfo != NULL)
                MSAPI_MEMORY_FREE(CCBBlockInfo, BUF_ID_CC);
            if (CCTextBuf != NULL)
                MSAPI_MEMORY_FREE(CCTextBuf, BUF_ID_CC);
        }
        fCCDynamicMemAllocFlag = FALSE;

    }

}

///////////////////////////////////////////////////////////////////////////////
/// API for Setting CC System Memory Buffer::
/// Set CC System Controlling variables and Memory Buffers as default
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_ClearBuffer(void)
{
#if 0
    for (u8CCPR_Temp1 = 0; u8CCPR_Temp1 < MAX_CS_WINDOW_NO; u8CCPR_Temp1++)
    {
        #ifdef CC_USE_MULTIPLE_GWINS
        MApi_GOP_GWIN_DestroyWin(u8CCPR_Temp1);
        MApi_GOP_GWIN_SetBlending(u8CCPR_Temp1, TRUE, 0x3f);    //0x3f need to be set for blink2266
        #else
        if(u8CCPR_Temp1 < 4)
            MApi_GOP_GWIN_SetBlending(g_u8CCGwinID, TRUE, 0x3f);    //0x3f need to be set for blink2266
            //MApi_GOP_GWIN_SetBlending(u8CCPR_Temp1, TRUE, 0x3f);    //0x3f need to be set for blink2266
        #endif
    }
#endif
    if ((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2)
        || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_TWOFIELD))
    {
        memset(pstCC608_Cntl, INVALID, sizeof(CC608_CodeSyntax_CntlAttr));
        memset((U8 *)CC_Packet_Buffer, INVALID, SIZE_OF_PACKET_BUFFER);
        memset((U8 *)CC_Service_Buffer, INVALID, SIZE_OF_SERVICE_BUFFER);
        //CLEAR_CC608_DISPLAY_BUFFER();
        //CC_DecoderFuns.CC608ParserInit();
    }
    else if (u8CCType_Option == MSAPI_CC_TYPE_DTVCC)
    {
        //CC708
        memset((U8 *)CC_Packet_Buffer, INVALID, SIZE_OF_PACKET_BUFFER);
        memset((U8 *)CC_Service_Buffer, INVALID, SIZE_OF_SERVICE_BUFFER);

        memset(CCTextBuf, INVALID, (g_u8MaxColPlus * sizeof(BlinkChar_Info)));
        memset(CCBBlockInfo, INVALID, sizeof(BlinkBlock_Info));

        // Reset TRP Data Structure
        memset(pstCC708_Trp, NA, sizeof(CC708_CodeSyntax_TRPAttr));

        //CC_DecoderFuns.Reset708CtrlData();

        msAPI_CC_BlockInit(0, u32CCBlock0Addr, u32CCBlock0Size);
        msAPI_CC_BlockInit(1, u32CCBlock1Addr, u32CCBlock1Size);
    }

}

///////////////////////////////////////////////////////////////////////////////
/// API for initialize Caption Decode::
/// Set CC Decoder
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_WakeUp(void)
{
    CC_DecoderFuns.Initial();
    CC_DecoderFuns.SetFontHandle(&Font_CC[0]);

     if((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2)
            || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_TWOFIELD))
    {
    #if 0
    //benny move this to msAPI_CC_InitialData in 20160712!
    #if KOREAN_CC_ENABLE
        if(g_fCCAttrFlag.fCCAttr_Suport_Korean_Flag == TRUE)
        {
            if(u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1)
                CC_DecoderFuns.KoreanCCEnv(0);
            else if(u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2)
                CC_DecoderFuns.KoreanCCEnv(1);
        }
        else
        {
            CC_DecoderFuns.KoreanCCEnv(0);
        }
   #endif
   #endif
        //mapi_CC608_ErrorStop_Threshold(0xff, 0xff);       // 0xff to stop this function
    //    CC_DecoderFuns.Timeout_Threshold(0xff, 0xff);
        CC_DecoderFuns.SetPalette(SYSINFO_MODE_608, FALSE);
        CC_DecoderFuns.CC608ParserInit();
    }
    else if(u8CCType_Option == MSAPI_CC_TYPE_DTVCC)
    {
         CC_DecoderFuns.SetPalette(SYSINFO_MODE_708, TRUE);
         CC_DecoderFuns.Reset708CtrlData();
    }
}
///////////////////////////////////////////////////////////////////////////////
/// Set CC exist period time::
/// @return
///   - #NULL
///////////////////////////////////////////////////////////////////////////////
void msAPI_CC_SetPeriodTime(U32 u32PeriodTime)
{
    u32CC_Check_Period = u32PeriodTime;
}


///////////////////////////////////////////////////////////////////////////////
/// Reset vchip rating info::
/// @return
///   - #NULL
///////////////////////////////////////////////////////////////////////////////
void msAPI_CC_VchipRateReset(void)
{
    CC_SourceFuns.VchipRateReset();
}

///////////////////////////////////////////////////////////////////////////////
/// Reset CC exist info::
/// @return
///   - #NULL
///////////////////////////////////////////////////////////////////////////////
void msAPI_CC_ResetExistInfo(void)
{
    /* CC Info initialize */
    SET_708CCISEXIST(FALSE);
    SET_608CCISEXIST(FALSE);
    u32CC708_Last = 0;
    u32CC608_Last = 0;
    u32CC157_Last = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// API to check Digital CC708 availability::
/// @return
///   - # TRUE CC708 is avaiable
///   - # FALSE CC708 is not available
///////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_CC_DigitalCC708_Available(void)
{
    #if _CC_DEBUG_CCPKT_
    return TRUE;
    #endif
    if(u32CC_Check_Period == 0)
    {
        if(CHECKCCEXIST(fDCCExistFlag))
            return TRUE;
        else
            return FALSE;
    }
    else
    {
        if ((u32CC708_Last == 0)||(!CHECKCCEXIST(fDCCExistFlag)))
            return FALSE;

        if (msAPI_Timer_DiffTimeFromNow(u32CC708_Last) <= u32CC_Check_Period)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API to check Digital CC708 available type::
/// @return
///   - # bit0 for service1, bit1 for service2,...
///////////////////////////////////////////////////////////////////////////////
U8 msAPI_CC_DigitalCC708_AvailableType(void)
{
    return u8CC708Avail;
}

///////////////////////////////////////////////////////////////////////////////
/// API to check Digital CC608 availability::
/// @return
///   - # TRUE CC608 is avaiable
///   - # FALSE CC608 is not available
///////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_CC_DigitalCC608_Available(void)
{
    U32 u32DigCC608_Last = 0;

    if(u32CC_Check_Period == 0)
    {
        if(CHECKCCEXIST(fACCExistFlag))
            return TRUE;
        else
            return FALSE;
    }
    else
    {
        if(CC_SourceFuns.DigitalCCUsing157())
            u32DigCC608_Last = u32CC157_Last;
        else
            u32DigCC608_Last = u32CC608_Last;

        if((u32DigCC608_Last == 0)||(!CHECKCCEXIST(fACCExistFlag)))
            return FALSE;

        if ((u32DigCC608_Last != 0)&& (msAPI_Timer_DiffTimeFromNow(u32DigCC608_Last) <= u32CC_Check_Period))
        {
            return TRUE;
        }
        else
            return FALSE;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API to check Analog CC608 availability::
/// @return
///   - # TRUE CC608 is avaiable
///   - # FALSE CC608 is not available
///////////////////////////////////////////////////////////////////////////////
BOOLEAN msAPI_CC_AnalogCC608_Available(void)
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
        if ((u32CC608_Last == 0)||(!CHECKCCEXIST(fACCExistFlag)))
            return FALSE;

        if (msAPI_Timer_DiffTimeFromNow(u32CC608_Last) <= u32CC_Check_Period)
        {
            return TRUE;
        }
        else
            return FALSE;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// API to check Digital CC608 available type::
/// @return
///   - # bit0 for field 1, bit1 for field 2,...
///////////////////////////////////////////////////////////////////////////////
U8 msAPI_CC_CC608_AvailableType(void)
{
    return u8CC608Avail;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void msAPI_CC_EnableDispGwin(U8 u8win, BOOLEAN bEnable)
{
    if(bEnable)
    {
        u8CCEnableDispGwin |= (1 << u8win);
    }
    else
    {
        u8CCEnableDispGwin &= ~(1 << u8win);
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
U8 msAPI_CC_GetEnableDispGwin(void)
{
    return u8CCEnableDispGwin;
}

#if !_CC_DEBUG_GETONE_708_
///////////////////////////////////////////////////////////////////////////////
/// API for Digital Closed Caption Protocol Parser::
/// Get Digital CC Service Raw Data from MVD CC Driver
///////////////////////////////////////////////////////////////////////////////
//extern BOOLEAN bCC708ForceExit;

//void msAPI_CC_DigitalCC_Parser(void)
void msAPI_CC_DigitalCC_Parser(BOOLEAN fEnableCCFunc)
{
    U8 u8CC608;
    BOOLEAN fHasData;
    for (u8CC608 = 0; u8CC608 <= 1; u8CC608++)
    {
        //printf("\nI: %d ; R: 7: %d ; 6: %d", (U8)u8CC608, (U8)MvdCcRunning[0], MvdCcRunning[1]);
            // SH@ fixed abnormal display for C15xx.trp, 10-3.(need to match the new MVD fw)
           // if(!MDrv_CC_CM_IsMvdRstDone(u8CC608))
#if 0
        if(E_VDEC_OK != MApi_VDEC_CC_GetIsRstDone(CC_SourceFuns.TransformCCFmt(u8CC608) ))
            continue;

        if (MvdCcRunning[u8CC608] == FALSE)
            continue;

        //u8MVDOverflow = MDrv_CC_CM_GetOverflowStatus(u8CC608);
        u8MVDOverflow = MApi_VDEC_CC_GetIsBuffOverflow(CC_SourceFuns.TransformCCFmt(u8CC608));

        #if _CC_DEBUG_CCPKT_
        u8MVDOverflow = FALSE;
        #endif

        if (u8MVDOverflow == TRUE)
        {
            fCC_Overflow_Status[u8CC608] = TRUE;
        }

        if (fCC_Overflow_Status[u8CC608] == TRUE)
        {
            if (u8CC608 == 0)
            {
                CC_SourceFuns.SetBufferStartAddr((U32)_VA2PA(u32CC708RbAddr), u8CC608);
                CC_SourceFuns.ParsingCommand(TRUE, (U16)(u32CC708RbSize), MSAPI_CC_TYPE_DTVCC);
            }
            else
            {
                CC_SourceFuns.SetBufferStartAddr((U32)_VA2PA(u32CC608RbAddr), u8CC608);
                CC_SourceFuns.ParsingCommand(TRUE, (U16)(u32CC608RbSize), MSAPI_CC_TYPE_NTSC_TWOFIELD);
            }
            fCC_Overflow_Status[u8CC608] = FALSE;
            continue;
        }
#endif
        #ifndef CC_USE_MULTIPLE_GWINS
        // Software blinking
        //SH@ 20110304, to prevent the garbage in flashing for UI
        if((fEnableCCFunc)&&(fCCDynamicMemAllocFlag))
        {
                // SH@ this will flush the last words
            CC_RenderFuns.SoftBlinkEngine();
         }
        #endif
        /* Get CC Raw Data */
        fHasData =  CC_SourceFuns.HasAvailableData(u8CC608);
        #if 0
        if (u8CC608 == 0)
            printf("\nK7K7:%d", fHasData);
        else
            printf("\nK6K6");
        #endif

        if (fHasData == FALSE)
        {
            if(u8CC608==0)
                CC_DecoderFuns.DecodeRemData(fEnableCCFunc);
            continue;
        }

        if(u8CC608 ==0)
        {     // 708
    //        u8CC708Avail |= CC_DecoderFuns.Check708Type();

            if (u8CCType_Option == MSAPI_CC_TYPE_DTVCC)
            {
              //  if(FALSE == g_fCCAttrFlag.fCCAttr_Packet_Dump_Flag)
                {
                    #if (!_CC_DEBUG_CCPKT_)
                    /*
                    if  (stCCOSDSetting.u8CCMode != CS_OFF)
                        msAPI_CC708_Service_Parser();
                    */
                    if(fEnableCCFunc == TRUE)
                    {
                        #if (CC_MEASURE_SYSTEM_TIME == 0)
                        CC_DecoderFuns.Decode708(fEnableCCFunc);
                        #else
                        U32 u32CC_LastTime;
                        u32CC_LastTime = MsOS_GetSystemTime();
                        CC_DecoderFuns.Decode708(fEnableCCFunc);
                        printf("[%d]", MsOS_GetSystemTime() - u32CC_LastTime);
                        #endif
                    }

                    //if(bCC708ForceExit)
                    //    return;

                    #else
                    CC_DecoderFuns.Decode708(fEnableCCFunc);
                    #endif
                }

            }
        }
        else
        {
         //   u8CC608Avail |= msAPI_CC608_Digital_CheckType();

            if ((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2))
               //|| (u8CCType_Option == MSAPI_CC_TYPE_NTSC_TWOFIELD))
            {
                /*
                if  (stCCOSDSetting.u8CCMode != CS_OFF)
                    msAPI_CC608_Service_Parser();
                */
                //printf("\nEnable: %bd",(U8)fEnableCCFunc);
                if(fEnableCCFunc == TRUE)
                {

                    CC_DecoderFuns.Decode608();
                }
            }

             CC_DecoderFuns.DecodeVChip();

            // -- Get an average interval of getting packet -------------------------->
            if(u8CC608 == 0)   // 708
            {
                u32CC_LastGetTime = MsOS_GetSystemTime();
            }
            else    // 608
            {
                // Field 1
                if(((stCCOSDSetting.u8CaptionServiceModeATV >= CS_CC1) && (stCCOSDSetting.u8CaptionServiceModeATV <= CS_CC2)) ||
                    ((stCCOSDSetting.u8CaptionServiceModeATV >= CS_TEXT1) && (stCCOSDSetting.u8CaptionServiceModeATV <= CS_TEXT2)))
                {
                    if((CC_Packet_Buffer[0] != 0xFF && CC_Packet_Buffer[0] != 0x80) ||
                        (CC_Packet_Buffer[1] != 0xFF && CC_Packet_Buffer[1] != 0x80))
                    {
                        u32CC_LastGetTime_608 = MsOS_GetSystemTime();
                    }
                }
                // Field 2
                else if(((stCCOSDSetting.u8CaptionServiceModeATV >= CS_CC3) && (stCCOSDSetting.u8CaptionServiceModeATV <= CS_CC4)) ||
                    ((stCCOSDSetting.u8CaptionServiceModeATV >= CS_TEXT3) && (stCCOSDSetting.u8CaptionServiceModeATV <= CS_TEXT4)))
                {
                    if((CC_Packet_Buffer[4] != 0xFF && CC_Packet_Buffer[4] != 0x80) ||
                        (CC_Packet_Buffer[5] != 0xFF && CC_Packet_Buffer[5] != 0x80))
                    {
                        u32CC_LastGetTime_608 = MsOS_GetSystemTime();
                    }
                }
            }
        }
        //(printf("\nSetRA"));
#if 0
            //MDrv_CC_PM_SetMVDRB_ReadAddr(CC_EachPacketBuffer_Size, u8CC608);
            VDEC_CC_INPUTDATA.u32Ver = 0;
            VDEC_CC_INPUTDATA.u32Val= CC_EachPacketBuffer_Size;
            MApi_VDEC_CC_UpdateReadAdd(msAPI_CC_TranformCCFormat(u8CC608) , (MS_U32 *)(&VDEC_CC_INPUTDATA));
#endif
    } // if (msAPI_CC_HasAvailableData() == TRUE)

    if ((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD2))
    {
        CC_DecoderFuns.Check608TimeOut();
        //(printf("\nProtection - 608"));
    }

    if (u8CCType_Option == MSAPI_CC_TYPE_DTVCC)
    {
        CC_DecoderFuns.Check708TimeOut();
        //(printf("\nProtection - 708"));
    }

}
#else
extern void msAPI_CC_GetDataFromSDRAM(U32 u32SrcAddress, U32 u32DstAddress, U32 u32Len, U8 u8CC608);
void msAPI_CC_DigitalCC_Parser(BOOLEAN fEnableCCFunc)
{
    U8 u8MVDOverflow, u8CC608;

    int iii, j;
    U32 u32DstAddr, u32ReadAddr, u32WriteAddr;
    U8 u8size;

    u8CC608 = 0;

    //u32WriteAddr = MDrv_CC_PM_GetMVDRB_WriteAddr(u8CC608);
    u32WriteAddr = MApi_VDEC_CC_GetWriteAdd(msAPI_CC_TranformCCFormat(u8CC608))
   // u32ReadAddr = MDrv_CC_PM_GetMVDRB_ReadAddr(u8CC608);
    u32ReadAddr =  MApi_VDEC_CC_GetReadAdd(msAPI_CC_TranformCCFormat(u8CC608));
    u8MVDOverflow = MApi_VDEC_CC_GetIsBuffOverflow(E_VDEC_CC_708);
    u8size = MApi_VDEC_CC_GetIsBuffOverflow(E_VDEC_CC_608);

    printf("\nRA: 0x%08LX ; WA: 0x%08LX ; OV7: 0x%x ; OV6: 0x%x", u32ReadAddr , u32WriteAddr, u8MVDOverflow, u8size);

    //if (u8MVDOverflow == TRUE)
    //if (u32WriteAddr > (0xA2D000 - 0x40))
    if (u32WriteAddr > ((u32CC708RbAddr+u32CC708RbSize) - 0x60))
    {
        printf("\nGET ONE BUFFER");
        CC_SourceFuns.StopMVDParser();

        u32ReadAddr = u32CC708RbAddr;
        u32DstAddr = (U16)&CC_Packet_Buffer[0];
        u8size = 8;

        for (iii=0; iii < ((u32CC708RbSize - 0x60)/u8size); iii++)
        {
            u32DstAddr = (U16)&CC_Packet_Buffer[0];
            msAPI_CC_GetDataFromSDRAM((U32)u32ReadAddr, (U32)(u32DstAddr), u8size, u8CC608);
            u32ReadAddr += u8size;

            for (j=0; j<u8size; j++)
            {
                printf("0x%02bX, ", CC_Packet_Buffer[j]);
            }
            printf("\n");
        }

        (printf("\nRSUM[4]"));
        while(1);
    }

}

#endif


///////////////////////////////////////////////////////////////////////////////
/// API for Analog Closed Caption Protocol Parser::
/// Get Analog CC Service Raw Data from VBI Slice Driver
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_AnalogCC_Parser(void)
{
    CC_DecoderFuns.AnalogCC_Parser();
}

#if KEEP_UNUSED_FUNC
///////////////////////////////////////////////////////////////////////////////
/// API for the time out scheme of EIA608 Closed Caption Presentation::
/// The time out scheme of EIA608 CC
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_Check_TimeOut(void)
{
    if ((u8CCType_Option == MSAPI_CC_TYPE_NTSC_FIELD1) || (u8CCType_Option ==MSAPI_CC_TYPE_NTSC_FIELD2) )
        CC_DecoderFuns.Check608TimeOut();
}
#endif

///////////////////////////////////////////////////////////////////////////////
/// API for CC Main Parser::
/// Selecting Analog or Digital Closed Caption Parser
/// @Param Type \b IN  Selecting Analog/Digital Closed Caption Parser
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void msAPI_CC_Parser(U8 u8CCType, BOOLEAN fEnableCCFunc)
{
    if(u8CCType)
    {
        msAPI_CC_DigitalCC_Parser(fEnableCCFunc);
    }
    else
    {
    #if 0
        if(stCCOSDSetting.u8CaptionServiceModeATV >= CS_CC1)
        {
            CC_DBFLUSH_MEMORY_CMD(printf("\n...[%s, %d]...\n", __FUNCTION__, __LINE__));
            CC_RenderFuns.FlushEngine(CC_ROLL_UP_DOWN, CC_FLUSH_AllWIN);
        }
    #endif
        msAPI_CC_AnalogCC_Parser();
    }
}

/******************************************************************************/

#undef MSAPI_CC_PARSER_C
