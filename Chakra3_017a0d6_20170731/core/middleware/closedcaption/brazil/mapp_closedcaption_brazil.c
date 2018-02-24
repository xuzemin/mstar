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

//#include "stdafx.h"
#define MAPP_CLOSED_CAPTION_C

/******************************************************************************/
/*                      Header Files                                          */
/* ****************************************************************************/
#include "Board.h"
#if (ATSC_CC == BRA_CC)
#include <string.h>
#include <stdio.h>
#include "datatype.h"
#include "MsCommon.h"
#include "drvSERFLASH.h"
#include "BinInfo.h"
#include "msAPI_MIU.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_demux.h"
#include "msAPI_cc_sysinfo.h"
#include "msAPI_cc_parser.h"
#include "mapp_closedcaption.h"
#include "MApp_Font.h"
#include "MApp_GlobalVar.h"
#include "mapp_demux.h"
#include "MApp_PVR.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "mapi_cc_monitor.h"
#include "apiGOP.h"
#include "mapi_cc_brazil_decode.h"

/*
 * For debug option,
 *
 * please turn on the 'CC_TESTING_SOURCE' in 'msAPI_cc_brazil_parser.h' --> DTV
 * please turn on the 'CC_ATV_TEST' in 'mapp_closedcaption.h'           --> ATV (On:yellow key, off:blue key)
 *
 */
//#define CC_TESTING_SOURCE       0   // 0: normal, 1: fixed PID by demux, 2: from file

#define AHEAD_OF_TIME(len) (len < 100 ? 200 : ((450 + (len / 4500) * 350) + ((len / 4500) + 1) * 250))

// Testing for getting data from demux
#if (CC_TESTING_SOURCE == 1) || (CC_ATV_TEST == 1)
#define CC_UNITEST_PROGRAM
#endif

// Testing for getting data from file
#if (CC_TESTING_SOURCE == 2)
#define CC_UNITEST_PROGRAM
#define CC_READ_LENGTH_ONCE             1024    // We suppose current max. length is 1024 bytes...
#endif

// Print out debug message
#define CC_DBINFO_CMD_1(x)                  //x   //print out
#define SBTL_ERR(x)                 //x
#define VERBOSE                     FALSE
#define PRINT_HEADER                FALSE
#define PES_HEADER_LEN                 16         // min bytes of data that are needed to know the PES packet length and it has to be 4-byte alignment
#define PES_BLOCK_LEN                512     // this depends on demux design

/********************************************************************************/
/*                    define                                                    */
/********************************************************************************/
#define CC_GOP_GWIN_ALPHA_VALUE         0x7f7f

/********************************************************************************/
/*                    global variable                                           */
/********************************************************************************/
static EN_CAPTION_STATE enCCState = STATE_CAPTION_INIT;
static U8 fEnableCCInit = FALSE;

extern BOOLEAN fEnableClosedCaptionFunc;
extern const CC_BrazilDecoder CC_BrazilDecoderFuns;

/********************************************************************************/
/*                      Local                                                   */
/********************************************************************************/
static EN_RET bEn = EXIT_NULL;
#if (CC_TESTING_SOURCE == 2)
static U32 g_u32CcTestPattern_addr = 0, g_u32CcTestPattern_len = 0;
static U32 ccReadTotalCnt = 0;
static U8 au8Buf[CC_READ_LENGTH_ONCE]; // Just testing...
#endif
static U8 u8BkupGOPNum = NA;

static stCaptionSettingVariables stCCVarSetting;
static U8 u8CCmode = SYSINFO_MODE_DTV;

static U8 u8GOPID, u8GWINID, u8GEMODE;

#ifdef CC_UNITEST_PROGRAM
static U32 u32FirstChk = 0;
#endif
static  U16 _u16PesDataLength;

extern U32 g_GWIN_ALIGND_VALUE;

static CC_Buf_Content volatile *ag_ccBytesBuf = ((CC_Buf_Content volatile *)((CCVBI_RINGBUFFER_START_MEMORY_TYPE & MIU1) ? (CCVBI_RINGBUFFER_START_ADR | MIU_INTERVAL) : (CCVBI_RINGBUFFER_START_ADR)));
/********************************************************************************/
/*                      Functions                                               */
/********************************************************************************/
#if (CC_TESTING_SOURCE == 1)
extern void MApp_Dmx_PES_Monitor(U16 u16PID, void *pfNotify, BOOLEAN bFileIn);
#endif

#ifdef CC_UNITEST_PROGRAM
static EN_RET MApp_UniTest_Check(void);
#endif
//static void MApp_ClosedCaption_ProcessUserInput(void);

/******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
/// API for CC getting user command program::
/// Getting user commands for CC
/// @return void
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void MApp_ClosedCaption_GetUserCmd(void)
{

    if ( DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode == CS_OFF )
    {
        fEnableClosedCaptionFunc = FALSE;
        g_u8CCType_Option = MSAPI_CC_TYPE_NONE;
        MApp_ClosedCaption_Stop();
        return;
    }

    enCCState = STATE_CAPTION_INIT;

    if ( ( DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode >= CS_CC1 ) && ( DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode <= CS_TEXT4 ) )
    {
        fEnableClosedCaptionFunc = TRUE;
        if ( ( DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode == CS_CC1 ) || ( DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode == CS_CC2 )  \
            || ( DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode == CS_TEXT1 ) || ( DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode == CS_TEXT2 ) )
        {
            g_u8CCType_Option = MSAPI_CC_TYPE_NTSC_FIELD1;
        }
        else
        {
            g_u8CCType_Option = MSAPI_CC_TYPE_NTSC_FIELD2;
        }
    }

    #if 0
    printf("\n...[%s, %d] mode=0x%x, val=%d, val1=%d...\n", __FUNCTION__, __LINE__, DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode,
        fEnableClosedCaptionFunc, g_u8CCType_Option);
    #endif

}

/******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
/// API for CC stop program::
/// Exit for CC
/// @return void
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void MApp_ClosedCaption_Stop(void)
{
    //printf("\n%s ,%d\n", __FUNCTION__, __LINE__);
   if(IsDTVInUse())
   {
       msAPI_CC_DeleteMemory();
       msAPI_CC_SetInputData(CC_INPUT_CAPTIONTYPE, MSAPI_CC_TYPE_NONE);
    }

#if(ENABLE_MIU_1)
  #if(BRAZIL_CC&&(GOP_GWIN_RB2_MEMORY_TYPE&MIU1))
    MApi_GOP_GWIN_SetDoubleHeap(0, 0);
    MApi_GOP_FB_SEL(0);
  #endif
#endif

    if( fEnableCCInit )
    {
        CC_RenderFuns.Reset();
    }

    fEnableCCInit = FALSE;

    MApi_GOP_GWIN_SetDuplication(FALSE, FALSE);
    MApi_GOP_GWIN_SetPalette();
    enCCState = STATE_CAPTION_INIT;

}

/******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
/// API for CC exit program::
/// Exit for CC
/// @return void
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void MApp_ClosedCaption_Exit(void)
{
    //printf("\n%s ,%d\n", __FUNCTION__, __LINE__);
    // If parsing, close the CC
    if(enCCState == STATE_CAPTION_PARSER)
    {
        if(IsDTVInUse())
        {
            // Closing the caption action and release the resource
           mapi_CC_Brazil_Close();// msAPI_CC_Brazil_Close();
        }
//        else
        {
           MApp_ClosedCaption_Stop();
        }

        //make sure the current GOP is CC_USING_GOP_ID
        if(MApi_GOP_GWIN_GetCurrentGOP() != CC_USING_GOP_ID)
            MApi_GOP_GWIN_SwitchGOP(CC_USING_GOP_ID);

        // Recover the stretch
        //msAPI_CC_RecoverStretch();

#if(UI_SKIN_SEL == UI_SKIN_960X540X565 || UI_SKIN_SEL == UI_SKIN_960X540XI8)
        {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0,0, 0, 960, 540);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,960,PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, PANEL_HEIGHT);
        }
#endif

#if((UI_SKIN_SEL ==  UI_SKIN_1366X768X565) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X4444) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X565) \
        ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X8888) )
        #if ((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
			#if ENABLE_854x480_UI
	        if((g_IPanel.Width() >= 960) && (g_IPanel.Height() >= 540))
	        {
	            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
	            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,960, 540);
	            MApi_GOP_GWIN_Set_HSCALE(TRUE,960,PANEL_WIDTH);
	            MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, PANEL_HEIGHT);
	        }
			#else
	        if((g_IPanel.Width() >= 854) && (g_IPanel.Height() >= 480))
	        {
	            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
	            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,854, 480);
	            MApi_GOP_GWIN_Set_HSCALE(TRUE,854,PANEL_WIDTH);
	            MApi_GOP_GWIN_Set_VSCALE(TRUE, 480, PANEL_HEIGHT);
	        }
			#endif
        #else
        if((g_IPanel.Width() >= ZUI_ALIGNED_VALUE(1366,16)) && (g_IPanel.Height() >= 768))
        {
            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0, ZUI_ALIGNED_VALUE(1366,16), 768);
            MApi_GOP_GWIN_Set_HSCALE(TRUE,ZUI_ALIGNED_VALUE(1366,16),PANEL_WIDTH);
            MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, PANEL_HEIGHT);
        }
        #endif
/*
#elif(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
if((g_IPanel.Width() >= 1920) && (g_IPanel.Height() >= 1080))
        {
            MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,UI_OSD_PANE_W, UI_OSD_PANE_H);
            MApi_GOP_GWIN_Set_HSCALE(TRUE,UI_OSD_PANE_W,PANEL_WIDTH);
            MApi_GOP_GWIN_Set_VSCALE(TRUE, UI_OSD_PANE_H, PANEL_HEIGHT);
        }
*/
#endif

#if(ENABLE_MIU_1)
    #if(BRAZIL_CC&&(GOP_GWIN_RB2_MEMORY_TYPE&MIU1))
        MApi_GOP_GWIN_SetDoubleHeap(0, 0);
        MApi_GOP_FB_SEL(0);
    #endif
#endif

        // Switch gop
        if(u8BkupGOPNum != NA)
        {
            MApi_GOP_GWIN_SwitchGOP(u8BkupGOPNum);
            u8BkupGOPNum = NA;
        }

        CC_RenderFuns.Close();
    }

    // Reset the state
    bEn = EXIT_CLOSEDCAPTION_DONE;
    enCCState = STATE_CAPTION_INIT;
    //g_isWriteChar = FALSE;
    fEnableCCInit = FALSE;
}

void MApp_CC_SetStretchWindow(U16 u16StretchWidth, U16 u16StretchHeight)
{
    // SH@20091229, to prevent the blinking when turning on the OSD
    MApi_GOP_GWIN_SwitchGOP(CC_USING_GOP_ID);
    MApi_GOP_GWIN_Set_STRETCHWIN(CC_USING_GOP_ID, E_GOP_DST_OP0, 0, 0, u16StretchWidth, u16StretchHeight);
    MApi_GOP_GWIN_Set_HSCALE(TRUE, u16StretchWidth, devPanel_WIDTH());
    MApi_GOP_GWIN_Set_VSCALE(TRUE, u16StretchHeight, devPanel_HEIGHT());
}

///////////////////////////////////////////////////////////////////////////////
/// API for CC init program::
/// Init for CC
/// @return BOOLEAN: true/false
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
void MApp_ClosedCaption_Init(void)
{
    #if (CC_TESTING_SOURCE == 2)
    BININFO _BinInfo;
    BOOLEAN bResult;
    #endif
    u8GEMODE = CC_GOP_MODE_I8;
    u8GOPID = CC_USING_GOP_ID;
    u8GWINID = CC_USING_GWIN_ID;

    MApp_CC_CtrlParser(CC_SELECTOR_DUMP_DBG_MSG, CC_CONFIG_DUMP_DBG_MSG);

    msAPI_CC_CCInfoInit();

    u8BkupGOPNum = MApi_GOP_GWIN_GetCurrentGOP();
    U16 u16CaptionWidth = CC_ALIGNED_VALUE((CC_U16)msAPI_CC_Panel_WIDTH(), g_GWIN_ALIGND_VALUE) - g_GWIN_ALIGND_VALUE;
    U16 u16CaptionHeight = (CC_U16)msAPI_CC_Panel_HEIGHT();
    CC_RenderFuns.SetCcInfo(NULL, CC_DISWINDOW_WIDTH, u16CaptionWidth);
    CC_RenderFuns.SetCcInfo(NULL, CC_DISWINDOW_HEIGHT, u16CaptionHeight);
    MApp_CC_SetStretchWindow(u16CaptionWidth, u16CaptionHeight);

    CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);

    if(IsDTVInUse())
    {
        CC_DecoderFuns.SetFontHandle(&Font_CC[0]);
        #ifdef CC_CMODEL_SIMULATION
        if( fopen_s(&fpIn, TestPatternFileName, "rb" ) != 0 )
        {
            printf("\n...Open file failed");
            bEn = EXIT_NULL;
        }
        #endif
        MApp_CC_CtrlParser(CC_SELECTOR_RESET_TO_DEFAULT, TRUE);
        MApp_CC_CtrlParser(CC_SELECTOR_ENABLESVS, CC_CONFIG_ENABLESVS);
        MApp_CC_CtrlParser(CC_SELECTOR_ENABLESHS, CC_CONFIG_ENABLESHS);
        CC_BrazilDecoderFuns.EnableDumpRawData(FALSE);

       msAPI_CC_Brazil_SetMisInfo(ENABLE);
       CC_BrazilDecoderFuns.SetPalette();//mapi_CC_Brazil_SetPalette();
       CC_BrazilDecoderFuns.Init();//mapi_CC_Brazil_Init();
       msAPI_CC_SetOsdSetting(&(DB_CC_SETTING.stCaptionSetting) );
       CC_RenderFuns.SetCcInfo(0, CC_ATTRIBUTE_FLAG, (CC_U32)&g_fCCAttrFlag);
        /*
         * ---------------------------------------------------------------
         *  Normally running by Demux PES
         * ---------------------------------------------------------------
         */
        #if (CC_TESTING_SOURCE == 1)
        MApp_ClosedCaption_Open_Filter(278);  // just test...

        /*
         * ---------------------------------------------------------------
         *  Tested by caption pattern files
         * ---------------------------------------------------------------
         */
        #elif (CC_TESTING_SOURCE == 2)

        // Get pattern file
        _BinInfo.B_ID = BIN_ID_CC_TEST_PATTERN;

        msAPI_MIU_Get_BinInfo(&_BinInfo, &bResult);

        if (bResult == PASS)
        {
            g_u32CcTestPattern_addr = _BinInfo.B_FAddr;
            g_u32CcTestPattern_len  = _BinInfo.B_Len;

            printf("\n...CC testing patterns found in flash, addr=0x%x, size=0x%x\n", g_u32CcTestPattern_addr, g_u32CcTestPattern_len);
        }
        else
        {
            g_u32CcTestPattern_addr = 0;
        }

        #endif

        CC_DecoderFuns.Initial();
        CC_RenderFuns.Init();

    }
    else
    {
        CC_DecoderFuns.SetFontHandle(&Font_CC[1]);
        /* In the following code sequence, it should be called in order */
        CC_SourceFuns.VbiInit((U32)(&ag_ccBytesBuf[0]));
        msAPI_CC_SetSysBuffer();
        msAPI_CC_AllocateMemory(g_u8CCType_Option);
        msAPI_CC_ClearBuffer();
        msAPI_CC_SetOsdSetting(&(DB_CC_SETTING.stCaptionSetting));
        //To delete frame buffer
        msAPI_CC_InitialData(g_u8CCType_Option,FALSE);
        CC_DecoderFuns.Initial();
        CC_RenderFuns.Init();

        CC_DecoderFuns.SetPalette(SYSINFO_MODE_608, FALSE);
        CC_DecoderFuns.CC608ParserInit();
    }


    bEn = EXIT_CLOSE;
}

///////////////////////////////////////////////////////////////////////////////
/// API for CC entry program::
/// Entrance for CC
/// @return BOOLEAN: true/false
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
EN_RET MApp_ClosedCaption_Main(void)
{
    U8  i;
    U32 _addr;
    U32 u32ReadLen=0;
    U32 u32RetLen=0;

    //printf("\n[%s, %d] : enCCState :%d\n", __FUNCTION__, __LINE__, enCCState);
    bEn = EXIT_CLOSEDCAPTION_NULL;

    #ifdef CC_UNITEST_PROGRAM
    bEn = MApp_UniTest_Check();
    if(bEn == EXIT_CLOSEDCAPTION_NULL)
    {
        return EXIT_CLOSEDCAPTION_NULL;
    }
    #endif

    i = 0;
    _addr = u32ReadLen = u32RetLen = 0;

    if(fEnableClosedCaptionFunc == FALSE)
    {
        return EXIT_CLOSEDCAPTION_NULL;
    }

    switch(enCCState)
    {
        case STATE_CAPTION_INIT:

            if (fEnableCCInit == FALSE)
            {
                CC_DBINFO_CMD_1(printf("\n...STATE_CAPTION_INIT\n"));
                MApp_ClosedCaption_Init();
                if(!bEn)
                {
                    printf("\n...CC init failed");
                    bEn = EXIT_CLOSEDCAPTION_NULL;
                    break;
                }

                fEnableCCInit = TRUE;
            }

            enCCState = STATE_CAPTION_PARSER;
        break;

        case STATE_CAPTION_PARSER:
            if(MApi_GOP_GWIN_GetCurrentGOP() != CC_USING_GOP_ID)
            {
		  MApi_GOP_GWIN_SwitchGOP(u8GOPID);
                MApi_GOP_GWIN_Switch2Gwin(u8GWINID);
                CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);

            }
          // MApp_ClosedCaption_ProcessUserInput();
            if (enCCState == STATE_CAPTION_PARSER)
            {
                //printf("\n[%s, %d] : IsDTVInUse :%d\n", __FUNCTION__, __LINE__, IsDTVInUse());
                if(IsDTVInUse())
               {
                /*
                 * ---------------------------------------------------------------
                 *  Normally running by Demux PES
                 * ---------------------------------------------------------------
                 */

                #if (CC_TESTING_SOURCE != 2)

				QueueElement eQue;
                            U8 u8N=0;
                            // Pick one to check the time stamp
                            U32 u32STC, u32SystemSTC_H;
				MApi_DMX_Stc_Get(&u32SystemSTC_H, &u32STC);

                            while (CC_BrazilDecoderFuns.PeekN(&eQue, u8N++) == TRUE)
                            {
                                CC_DBINFO_CMD_1(printf("\n...[%s, %d] pts:0%x,STC : %d, %d...\n", __FUNCTION__, __LINE__,\
                                    eQue.u32PTS, u32STC, u8N));

                                if (eQue.u32PTS < u32STC|| CC_BrazilDecoderFuns.IsFreeRun(u32STC, eQue.u32PTS))
                                {
                                    // Choose one to decode...
                                    if(CC_BrazilDecoderFuns.Pop(&eQue))
                                    {
                                        CC_BrazilDecoderFuns.RunCaption(&eQue);
                                    }
                                }

                                   // return EXIT_TV_NULL;//CC_ERRCODE_SUCCESS;
                            }

                /*
                 * ---------------------------------------------------------------
                 *  Tested by caption pattern files
                 * ---------------------------------------------------------------
                 */

                #else

                _addr = g_u32CcTestPattern_addr + ccReadTotalCnt;

                MDrv_FLASH_Read(_addr, CC_READ_LENGTH_ONCE, au8Buf);

                // Get the PES
                u32RetLen = msAPI_CC_Brazil_GetPES(au8Buf);

                //printf("\n...retLen=%d, addr=0x%x", u32RetLen, _addr);
                if(u32RetLen > CC_READ_LENGTH_ONCE)
                {
                    printf("\n...over %d bytes\n", CC_READ_LENGTH_ONCE);
                    ccReadTotalCnt = CC_READ_LENGTH_ONCE;
                }
                else
                {
                    ccReadTotalCnt += u32RetLen;
                }

                // Run the caption
                ret = msAPI_CC_Brazil_RunCaption();

                // if ending, out
                if(ccReadTotalCnt >= g_u32CcTestPattern_len)
                {
                    printf("\n\n\n...Read file end, reset it\n\n\n");
                    ccReadTotalCnt = 0;
                }

                if((u32RetLen == 0) && (ret == CC_ERRCODE_QUEUE_EMPTY))
                {
                    bEn = EXIT_CLOSEDCAPTION_NULL;
                    printf("\n...Nothing found...");
                    break;
                }

                #ifdef CC_DUMP_PATTERNS// Dump patterns
                if(u32RetLen > 0)
                {
                    printf("\n-->\n");
                    for(i=0; i<u32RetLen; i++)
                    {
                        printf("0x%02x, ", au8Buf[i]);
                        if((i+1)%16 == 0)   printf("\n");
                    }
                    printf("\n<--\n");
                }
                #endif

                //printf("\n@\n");
                #endif

            }
            else
            {
               //printf("\n[%d]  %s\n",__LINE__, __FUNCTION__);
                //printf("\n[%s, %d] : fEnableClosedCaptionFunc :%d\n", __FUNCTION__, __LINE__, fEnableClosedCaptionFunc);
                msAPI_CC_Parser(0,fEnableClosedCaptionFunc);
            }
            }
        break;

        default:
            enCCState = STATE_CAPTION_PARSER;
        break;
    }

    return bEn;
}

///////////////////////////////////////////////////////////////////////////////
///
///
/// API for UI Interface:
///
///
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// API to init Closed-caption
///
/// @return void
///////////////////////////////////////////////////////////////////////////////
void MApp_CC_Initialize(void)
{
#if ENABLE_ISDBT
    if(!IS_SBTVD_APP)
        return;
#endif

    CC_SourceFuns.VbiInit((U32)(&ag_ccBytesBuf[0]));
    msAPI_CC_VchipRateReset();

    msAPI_CC_SetSysBuffer();
    msAPI_CC_SetDrvVar();
}


///////////////////////////////////////////////////////////////////////////////
/// API to run the Closed-caption parser
///
/// @return error code
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_StartParser(void)
{
    // enable CC
    fEnableClosedCaptionFunc = TRUE;

    // return
    return  CC_ERRORCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// API to control the CC parser
///
/// @param selector /b IN
/// @param value /b IN the selector's value
/// @return error code
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_CtrlParser(U32 selector, U32 value)
{
    S32 *pTempVal = NULL;
    CC_DBINFO_CMD_1(printf("\n...[%s, %d] selector=0x%x, val=0x%x...\n", __FUNCTION__, __LINE__, selector, value));

    // Functionality select
    switch (selector)
    {

        //--------------------------------------------------------------------------
        //  action
        //--------------------------------------------------------------------------
        case CC_SELECTOR_MODE:

            if(value != SYSINFO_MODE_ATV)
            {
                u8CCmode = SYSINFO_MODE_DTV;
            }
            else
            {
                u8CCmode = SYSINFO_MODE_ATV;
            }

            break;

        case CC_SELECTOR_SERVICE:

            if(IsDTVInUse())
            {
                DB_CC_SETTING.stCaptionSetting.u8CaptionServiceModeDTV = value;
            }
            else
            {
                DB_CC_SETTING.stCaptionSetting.u8CaptionServiceModeATV = value;
            }

            DB_CC_SETTING.stCaptionSetting.u8CaptionServiceMode = value;

            MApp_ClosedCaption_GetUserCmd();

            break;

        case CC_SELECTOR_RESET_TO_DEFAULT:

            if(value != 0)
            {
                msAPI_CC_ResetOsdSetting(&stCCVarSetting);
            }

            break;

        //--------------------------------------------------------------------------
        //  attribute
        //--------------------------------------------------------------------------


        //--------------------------------------------------------------------------
        //  offset, length...
        //--------------------------------------------------------------------------
        case CC_SELECTOR_ROW_TOPRSVHEIGHT:

            if(u8CCmode == SYSINFO_MODE_DTV)
            {
                stCCVarSetting.u8Row_brazil_toprsvheight = value;
            }
            else
            {
                stCCVarSetting.u32Row_608_toprsvheight = value;
            }

            break;

        case CC_SELECTOR_ROW_BTMRSVHEIGHT:

            if(u8CCmode == SYSINFO_MODE_DTV)
            {
                stCCVarSetting.u8Row_brazil_btmrsvheight = value;
            }
            else
            {
                stCCVarSetting.u32Row_608_btmrsvheight = value;
            }

            break;

        case CC_SELECTOR_ATV_AXIS_XPOS:

            stCCVarSetting.u32ATV_Axis_xpos = value;

            break;

        case CC_SELECTOR_ATV_AXIS_YPOS:

            stCCVarSetting.u32ATV_Axis_ypos = value;

            break;

        case CC_SELECTOR_DTV_AXIS_XPOS:

            stCCVarSetting.u32DTV_Axis_xpos = value;

            break;

        case CC_SELECTOR_DTV_AXIS_YPOS:

            stCCVarSetting.u32DTV_Axis_ypos = value;

            break;

        case CC_SELECTOR_CC_LANG:

            stCCVarSetting.u32Cc_lang = value;

            break;

        case CC_SELECTOR_TEXT_ROWNO:

            stCCVarSetting.u32Text_608_rowno = value;

            break;

        case CC_SELECTOR_TEXT_YPOS:

            stCCVarSetting.u32Text_608_ypos = value;

            break;

        case CC_SELECTOR_608_SCROLL_STEP:

             stCCVarSetting.u32CC_608_ScrollStep = value;

              break;

        case CC_SELECTOR_608_TIMEOUT_CAPITON:

            stCCVarSetting.u32Timeout_608_capiton = value;

            break;

        case CC_SELECTOR_608_TIMEOUT_TEXT:

            stCCVarSetting.u32Timeout_608_text = value;

            break;

        case CC_SELECTOR_DTV_TIMEOUT_CAPTION:

            stCCVarSetting.u32Timeout_DTV_caption = value;

            break;

        case CC_SELECTOR_AXIS_X_OFFSET:

            pTempVal = (S32*)value;
            stCCVarSetting.s32XPos_offset = (S32)*pTempVal;

            break;

        case CC_SELECTOR_AXIS_Y_OFFSET:

            pTempVal = (S32*)value;
            stCCVarSetting.s32YPos_offset = (S32)*pTempVal;

            break;

        case  CC_SELECTOR_TRANSLUCENT:

            CC_RenderFuns.SetCcInfo(0, CC_TRANSTUCENT_VALUE, value);

            break;

        case CC_SELECTOR_ENABLESVS:
            stCCVarSetting.u8CCEnableSVS= (U8)value;
            break;

        case CC_SELECTOR_ENABLESHS:
            stCCVarSetting.u8CCEnableSHS= (U8)value;
            break;

        case CC_SELECTOR_DUMP_DBG_MSG:
            CC_SourceFuns.SetInputInfo(CC_INPUT_DUMP_DBG_MSG, (void *)&value);
            break;


        //--------------------------------------------------------------------------
        //  default...
        //--------------------------------------------------------------------------
        default:

            printf("\n...[%s, %d] failed...\n", __FUNCTION__, __LINE__);

    }

    // updated
    if((selector >= CC_SELECTOR_ROW_TOPRSVHEIGHT) && (selector <= CC_SELECTOR_DEBUG))
    {
        msAPI_CC_SetVarSetting(&stCCVarSetting);
    }


    return  CC_ERRORCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// API to stop the Closed-caption parser
///
/// @return error code
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_StopParser(void)
{
    // disable CC
    fEnableClosedCaptionFunc = FALSE;

    // exit CC flow
    MApp_ClosedCaption_Exit();

    #ifdef CC_UNITEST_PROGRAM
    u32FirstChk = 0;
    #endif

    // return
    return  CC_ERRORCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/// API to get the closed-caption's info
///
/// @param selector /b IN
/// @return given value
///////////////////////////////////////////////////////////////////////////////
U32 MApp_CC_GetInfo(U32 selector)
{

    CC_DBINFO_CMD_1(printf("\n...[%s, %d] selector=0x%x...\n", __FUNCTION__, __LINE__, selector));

    // Functionality select
    switch (selector)
    {
        case CC_SELECTOR_ERROR_CODE:
            return  ((U32)CC_ERRORCODE_SUCCESS);

            break;

        case CC_SELECTOR_STATUS_CODE:
            return  ((U32)enCCState);

            break;

        default:
            printf("\n...[%s, %d] failed...\n", __FUNCTION__, __LINE__);
    }

    return  CC_ERRORCODE_SUCCESS;
}
/******************************************************************************/
/*static void MApp_ClosedCaption_ProcessUserInput(void)
{
    switch(u8KeyCode)
    {
        case KEY_NULL:
        case 0x27:      // Just using in temporary
            if (fEnableCCInit == FALSE)
                enCCState = STATE_CAPTION_INIT;
            else
                enCCState = STATE_CAPTION_PARSER;
            break;

        default:
            MApp_ClosedCaption_Exit();
        break;
    }
    // Don't clear the IR Key
    //u8KeyCode = KEY_NULL;
}*/

///////////////////////////////////////////////////////////////////////////////
///
///
/// Unitest program for Closed-Caption
///
///
///////////////////////////////////////////////////////////////////////////////

#ifdef CC_UNITEST_PROGRAM
void MApp_UniTest(void)
{
    U32 u32Err;

    #if (CC_TESTING_SOURCE == 1)
    printf("\n...[%s, %d] enter (from fixed PID)...\n", __FUNCTION__, __LINE__);
    #elif (CC_TESTING_SOURCE == 2)
    printf("\n...[%s, %d] enter (from file)...\n", __FUNCTION__, __LINE__);
    #endif

    /*
     *  DTV
     */
    if(IsDTVInUse())
    {

        // Set caption mode
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_MODE, CC_MODE_DTV);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Set caption service
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_SERVICE, CC_SERVICE_SERVICE1);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Start to parse
        u32Err = MApp_CC_StartParser();
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

    }

    /*
     *  ATV
     */
    else
    {

        // Set caption mode
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_MODE, CC_MODE_ATV);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Set caption service
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_SERVICE, CC_SERVICE_CC1);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Reset to default values --> Be run after 'Set caption mode'
        u32Err = MApp_CC_CtrlParser(CC_SELECTOR_RESET_TO_DEFAULT, ENABLE);
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

        // Start to parse
        u32Err = MApp_CC_StartParser();
        if(u32Err ==  CC_ERRORCODE_FAIL)
        {
            printf("\n...[%s, %d] fail...\n", __FUNCTION__, __LINE__);
        }

    }

}

EN_RET MApp_UniTest_Check(void)
{

    if(u32FirstChk == 0)
    {
        u32FirstChk = msAPI_Timer_GetTime0();
    }

    if((msAPI_Timer_GetTime0()-u32FirstChk) < (1000))
    {
        printf("+");
        return EXIT_CLOSEDCAPTION_NULL;
    }
    else
    {
        if(u32FirstChk != 1000000)
        {
            u32FirstChk = 0;
            if(u32FirstChk == 0)
            {
                MApp_UniTest();     // test
                u32FirstChk = 1000000;
            }
        }
    }

    return EXIT_CLOSEDCAPTION_DONE;
}

#endif


/******************************************************************************/
/// Callback function of PES monitor
/***************************************************************************/
void MApp_ClosedCaption_PES_Cb(U8 u8FID, MSAPI_DMX_FILTER_STATUS enStatus)
{
    U8  pbuff[PES_HEADER_LEN];
    U32 u32CopiedLen = 0, u32RmnSize ;

    static U16 _u16PesLength;
    static U32 _u32SDRAMAddress;
    static U32 u32SDRAMAddress;
    static U32 u32PTSLow;

    EN_CC_PES_STATE RetState = CC_GET_PES_STATE_TOBECONTINUED;
    U32 u32BufferAddress = ((DTVCC_PES_START_MEMORY_TYPE & MIU1) ? (DTVCC_PES_START_ADR | MIU_INTERVAL) : (DTVCC_PES_START_ADR));

#if ( PRINT_HEADER == 1) || ( VERBOSE == 1 )
    U16 u16PesIndex;
#endif
#if (!ENABLE_BRAZIL_CC_DETECT_FLAG)
    if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) != STATE_CAPTION_PARSER)
    {
        MApp_Dmx_PES_Restart();
        //printf("\n...CC init is not ready 1...\n");
        return;
    }
#endif

    CC_DBINFO_CMD_1(printf("\n...get pes, _u16PesDataLength=%d", _u16PesDataLength));
    //u8FID = 0x00;// ignore the warning message

    if (( enStatus == MSAPI_DMX_FILTER_STATUS_REQUESTMEET) || (enStatus == MSAPI_DMX_FILTER_STATUS_PESAVAILABLE ))
    {
        if (_u16PesDataLength == 0)
        {
            // SDRAM --> SDRAM
            //u16CopiedLen = msAPI_DMX_CopyPes(u8FID, (U32)u32BufferAddress, PES_HEADER_LEN, FALSE);
            MApi_DMX_CopyData(u8FID, (U8*)_PA2VA(u32BufferAddress), PES_HEADER_LEN, &u32CopiedLen, &u32RmnSize, NULL) ;

            if (u32CopiedLen > 0 )
            {
                // SDRAM --> XDATA
                memcpy(pbuff, (U8 *)_PA2VA(u32BufferAddress), PES_HEADER_LEN);
                //msAPI_MIU_Copy((U32)u32BufferAddress, XD2PHY(pbuff), PES_HEADER_LEN, MIU_SDRAM2SDRAM);

#if ( PRINT_HEADER == 1) || ( VERBOSE == 1)
                printf("\n\nhead-->\n");
                for(u16PesIndex=0 ; u16PesIndex < u32CopiedLen ; u16PesIndex++)
                {
                    printf("%02bx ",*(pbuff + u16PesIndex));
                }
#endif
                _u16PesDataLength = pbuff[4];
                _u16PesDataLength = _u16PesDataLength << 8;
                _u16PesDataLength |= pbuff[5];
                _u16PesDataLength += 6;                  //plus header

                u32SDRAMAddress = CC_BrazilDecoderFuns.AllocateQue(_u16PesDataLength); //(U32) msAPI_CC_Brazil_AllocateQue(_u16PesDataLength);

                _u32SDRAMAddress = u32SDRAMAddress;
                _u16PesLength = _u16PesDataLength;

                u32PTSLow = CC_BrazilDecoderFuns.SetPTS(&pbuff[7]); //msAPI_CC_Brazil_SetPTS(&pbuff[7]);

                // XDATA --> SDRAM
               //msAPI_MIU_Copy(XD2PHY(pbuff), (U32)u32SDRAMAddress, PES_HEADER_LEN, MIU_SDRAM2SDRAM);
            //   memcpy(u32SDRAMAddress, pbuff/*(U8 *)_PA2VA(u32BufferAddress)*/, PES_HEADER_LEN);
                 memcpy((U8 *)u32SDRAMAddress, pbuff, PES_HEADER_LEN);
                _u16PesDataLength -= u32CopiedLen;
                u32SDRAMAddress += u32CopiedLen;

                //[05-4]check header ==================================================//
                if(pbuff[3] != 0xbd)
                {
                    CC_DBINFO_CMD_1(printf("\nMSAPI_DMX: Header is incorrect !!!\n"));
                    _u16PesDataLength = 0;
                    RetState = CC_GET_PES_STATE_FAIL;
                }

            }
            else
            {
                CC_DBINFO_CMD_1(printf("\nMSAPI_DMX: Copy pes is failed1 !\n"));
                _u16PesDataLength = 0;
            }

        }
        else if (_u16PesDataLength > PES_BLOCK_LEN)// body
        {
             MApi_DMX_CopyData(u8FID, (U8*)/*_PA2VA*/(u32SDRAMAddress), PES_HEADER_LEN, &u32CopiedLen, &u32RmnSize, NULL) ;

            if (u32CopiedLen > 0)
            {

#if ( VERBOSE == 1)
                U8 u8i = 0;

                printf("\n --> body\n");
                for(u8i=0 ; u8i < ( u32CopiedLen / PES_HEADER_LEN ) ; u8i++)
                {
                    // replace from msAPI_MIU_Copy to memcpy
                    memcpy(pbuff, (U8 *)(u32SDRAMAddress + PES_HEADER_LEN * u8i), PES_HEADER_LEN);
                    printf("\n");

                    for(u16PesIndex=0 ; u16PesIndex < PES_HEADER_LEN ; u16PesIndex++)
                    {
                        printf("%02bx ",*( pbuff + u16PesIndex));
                    }
                }
#endif
                _u16PesDataLength = _u16PesDataLength - u32CopiedLen;
                u32SDRAMAddress += u32CopiedLen;
            }
            else
            {
                CC_DBINFO_CMD_1(printf("MSAPI_DMX: Copy pes is failed2 !\n"));
                _u16PesDataLength = 0;
            }
        }
        else// Tail
        {
            CC_DBINFO_CMD_1(printf("\n...addr=0x%x", u32SDRAMAddress));
            MApi_DMX_CopyData(u8FID, (U8*)(u32SDRAMAddress), _u16PesDataLength, &u32CopiedLen, &u32RmnSize, NULL) ;


            if (u32CopiedLen > 0)
            {

#if ( VERBOSE == 1)
                U8 u8i = 0;

                printf("\n --> tail\n");

                for(u8i=0 ; u8i < (u32CopiedLen / PES_HEADER_LEN) +1 ; u8i++)
                {
                    // replace from msAPI_MIU_Copy to memcpy
                    memcpy(pbuff, (U8 *)(u32SDRAMAddress + PES_HEADER_LEN * u8i), PES_HEADER_LEN);

                    printf("\n");

                    for(u16PesIndex=0 ; u16PesIndex < PES_HEADER_LEN ; u16PesIndex++)
                    {
                        printf("%02bx ",*( pbuff + u16PesIndex));
                    }
                }
#endif
                if (u32CopiedLen >= _u16PesDataLength)
                {

                    // Push into the queue once the whole PES is copied.
#if ( VERBOSE == 0 )
                    // Push data to Queue
#if (ENABLE_BRAZIL_CC_DETECT_FLAG)
                    if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
#endif
                    {
                        //if(!msAPI_CC_Brazil_Queue_Push((U32) _u32SDRAMAddress, _u16PesLength, u32PTSLow - AHEAD_OF_TIME(_u16PesLength)))
                        if(!CC_BrazilDecoderFuns.Push((U32) _u32SDRAMAddress, _u16PesLength, u32PTSLow - AHEAD_OF_TIME(_u16PesLength)))
                        {
                            CC_DBINFO_CMD_1(printf("\n...Push data failed...\n"));
                        }
                    }
#endif
                    _u16PesDataLength = 0;
                    RetState = CC_GET_PES_STATE_FINISH;
                 }
                 else
                 {
                    _u16PesDataLength -= u32CopiedLen;
                    u32SDRAMAddress += u32CopiedLen;
                 }
            }
            else
            {
                CC_DBINFO_CMD_1(printf("MSAPI_DMX: Copy pes is failed3 !\n"));
                _u16PesDataLength = 0;
            }
        }
    }
    else //if (( enStatus == MSAPI_DMX_FILTER_STATUS_SECAVAILABLE) || (enStatus == MSAPI_DMX_FILTER_STATUS_OVERFLOW ))
    {
       RetState = CC_GET_PES_STATE_FAIL;
    }

    if ( CC_GET_PES_STATE_FAIL == RetState )
    {
       MApp_Dmx_PES_Restart();
    }
}// if
/******************************************************************************/
static BOOLEAN _bCCFileIn = TRUE;
void MApp_ClosedCaption_Open_Filter(U16 u16PID)
{
    #if ENABLE_PVR
    _bCCFileIn = MApp_PVR_IsPVRStatePlaybacking() ? TRUE : FALSE;
    #else
    _bCCFileIn = FALSE;
    #endif
    _u16PesDataLength = 0;
    MApp_Dmx_PES_Monitor(u16PID,MApp_ClosedCaption_PES_Cb,_bCCFileIn);
}
BOOLEAN MApp_IsCCFileIn(void)
{
    return _bCCFileIn;
}
#endif //(ATSC_CC == BRA_CC)

#undef MAPP_CLOSED_CAPTION_C
