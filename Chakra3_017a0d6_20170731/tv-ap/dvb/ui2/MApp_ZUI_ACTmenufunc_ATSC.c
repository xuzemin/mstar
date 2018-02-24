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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
static U8 u8CCPreviewWinId = 0xff, u8CCPreviewFbId = 0xff;


#if ((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
#define UI_CC_PREVIEW_WIN_WIDTH             288
#define UI_CC_PREVIEW_WIN_HEIGHT            40
#define UI_CC_PREVIEW_WIN_START_X           35
#define UI_CC_PREVIEW_WIN_START_Y           7
#else
#define UI_CC_PREVIEW_WIN_WIDTH            384
#define UI_CC_PREVIEW_WIN_HEIGHT           56
#define UI_CC_PREVIEW_WIN_START_X           50
#define UI_CC_PREVIEW_WIN_START_Y           10
#endif


U16 MApp_UiMenuFunc_DecIncValue_Cycle(BOOLEAN action, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step)
{
    if(action == TRUE)
    {
        if(u16Value >= u16MaxValue)
            return u16MinValue;
        u16Value += u8Step;
        if(u16Value > u16MaxValue)
            u16Value = u16MinValue;
    }
    else if(action == FALSE)
    {
        if(u16Value <= u16MinValue)
            return u16MaxValue;
        if(u16Value < u8Step)
            u16Value = 0;
        else
            u16Value -= u8Step;
        if(u16Value < u16MinValue)
            u16Value = u16MaxValue;
    }
    return u16Value;
}

U8 MApp_GetCurCaptionServiceMode(void)
{
    if(!IsDTVInUse() || stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV == CAPTIONMENU_SERVICE_OFF)
        return stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV;
    else
        return stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV;
}



void MApp_UiMenuFunc_CCGetUserCmd(void)
{
    if (stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_ON)
    {
        stGenSetting.g_CaptionSetting.u8CaptionServiceMode = MApp_GetCurCaptionServiceMode();
        MApp_ClosedCaption_GetUserCmd();
    }
    else if (stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_OFF)
    {
        stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CS_OFF;
        MApp_ClosedCaption_GetUserCmd();
    }
#if (PARSING_CC_WHENMUTE)
    else if (stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_CC_WHEN_MUTE)
    {
        fEnableCCWhenMuteFunc = FALSE;
        stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CS_OFF;
        MApp_ClosedCaption_GetUserCmd();
        if (MApp_Aud_GetMuteStatus())
        {
            fEnableCCWhenMuteFunc = TRUE;
            fEnableClosedCaptionFunc = TRUE;
        }
    }
#endif
}

BOOLEAN MApp_UiMenuFunc_AdjustCCMode(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.u8CCMode = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.u8CCMode, CAPTIONMENU_MODE_OFF, CAPTIONMENU_MODE_NUM-1, 1);
    MApp_UiMenuFunc_CCGetUserCmd();
    return TRUE;
}

U16 MApp_UiMenuFunc_GetCCModeValue(void)
{
    return stGenSetting.g_CaptionSetting.u8CCMode;
}

BOOLEAN MApp_UiMenuFunc_AdjustCCBasic(BOOLEAN action)
{
    if( action == TRUE )
    {
        if( stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV == CAPTIONMENU_SERVICE_TEXT4)
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV = CAPTIONMENU_SERVICE_OFF;
        }
        else
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV++;
        }
    }
    else if( action == FALSE )
    {
        if( stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV == CAPTIONMENU_SERVICE_OFF )
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV = CAPTIONMENU_SERVICE_TEXT4;
        }
        else
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV--;
        }
    }

    if ((stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV==CAPTIONMENU_SERVICE_OFF)&&(stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV==CAPTIONMENU_SERVICE_OFF))
    {
        stGenSetting.g_CaptionSetting.u8CCMode = CAPTIONMENU_MODE_OFF;
    }
    else
    {
        // stGenSetting.g_CaptionSetting.u8CCMode = CAPTIONMENU_MODE_ON;
    }
    if( stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_ON )
    {
        stGenSetting.g_CaptionSetting.u8CaptionServiceMode = MApp_GetCurCaptionServiceMode();
        MApp_ClosedCaption_GetUserCmd();
    }
    else if( stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_OFF )
    {
        stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CAPTIONMENU_SERVICE_OFF;
        MApp_ClosedCaption_GetUserCmd();
    }
    return TRUE;

}

BOOLEAN MApp_UiMenuFunc_AdjustCCAdvance(BOOLEAN action)
{
    if( action == TRUE )
    {
        if( stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV == CAPTIONMENU_SERVICE_OFF )
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV = CAPTIONMENU_SERVICE_SERVICE1;
        }
        else if( ( stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV >= CAPTIONMENU_SERVICE_SERVICE1 ) && ( stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV < CAPTIONMENU_SERVICE_SERVICE6 ) )
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV++;
        }
        else
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV = CAPTIONMENU_SERVICE_OFF;
        }
    }
    else if( action == FALSE )
    {
        if( stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV == CAPTIONMENU_SERVICE_OFF )
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV = CAPTIONMENU_SERVICE_SERVICE6;
        }
        else if( ( stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV > CAPTIONMENU_SERVICE_SERVICE1 ) && ( stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV <= CAPTIONMENU_SERVICE_SERVICE6 ) )
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV--;
        }
        else
        {
            stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV = CAPTIONMENU_SERVICE_OFF;
        }
    }

    if ((stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV==CAPTIONMENU_SERVICE_OFF)&&(stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV==CAPTIONMENU_SERVICE_OFF))//( stGenSetting.g_CaptionSetting.u8CaptionServiceMode == CAPTIONMENU_SERVICE_OFF )
    {
        stGenSetting.g_CaptionSetting.u8CCMode = CAPTIONMENU_MODE_OFF;
    }
    else
    {
        // stGenSetting.g_CaptionSetting.u8CCMode = CAPTIONMENU_MODE_ON;
    }


    if( stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_ON )
    {
        stGenSetting.g_CaptionSetting.u8CaptionServiceMode = MApp_GetCurCaptionServiceMode();
        MApp_ClosedCaption_GetUserCmd();
    }
    else if( stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_OFF )
    {
        stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CAPTIONMENU_SERVICE_OFF;
        MApp_ClosedCaption_GetUserCmd();
    }
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustCCOptionMode(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.u8CSOptionMode = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.u8CSOptionMode , CAPTIONMENU_OPTIONMODE_DEFAULT, CAPTIONMENU_OPTIONMODE_CUSTOM, 1);
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

static U8 MApp_UiMenu_TransferColor(U8 u8Color)
{
    switch(u8Color)
    {
        default:
        case CAPTION_WINDOW_WHITE:
            return CAPTION_INNER_MIN8COLOR_WHITE;
        case CAPTION_WINDOW_BLACK:
            return CAPTION_INNER_MIN8COLOR_BLACK;
        case CAPTION_WINDOW_RED:
            return CAPTION_INNER_MIN8COLOR_RED;
        case CAPTION_WINDOW_GREEN:
            return CAPTION_INNER_MIN8COLOR_GREEN;
        case CAPTION_WINDOW_BLUE:
            return CAPTION_INNER_MIN8COLOR_BLUE;
        case CAPTION_WINDOW_YELLOW:
            return CAPTION_INNER_MIN8COLOR_YELLOW;
        case CAPTION_WINDOW_MAGENTA:
            return CAPTION_INNER_MIN8COLOR_MAGENTA;
        case CAPTION_WINDOW_CYAN:
            return CAPTION_INNER_MIN8COLOR_CYAN;
    }
}

// Draw CC Preview
#if ENABLE_ATSC_KOR
U8 Korean_CC_Preview[] = {0xAC, 0x00, 0xB0, 0x98, 0xB2, 0xE4, 0x00, 0x61, 0x00, 0x62, 0x00, 0x63};
#else
U8 strE5_CC_Digital_Preview[] = {"CC font: ABC"};
#endif

static U8 u8GOPID, u8GWINID, u8GEMODE;

void MApp_UiMenu_Clear_CC_Preview(U16 Width, U16 Height, U16 u16PosX, U16 u16PosY)
{
    BlinkBlock_Info BBlockInfo;
    UNUSED(u16PosX);
    UNUSED(u16PosY);

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);

    MApi_GOP_GWIN_Switch2Gwin(u8CCPreviewWinId);
    MApi_GOP_GWIN_Switch2FB(u8CCPreviewFbId);

    CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);
    BBlockInfo.BlockSrc0Address= DTVCC_BLOCK0_START_ADR;
    MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK0_START_ADR, DTVCC_BLOCK0_START_LEN, 0);
    BBlockInfo.BlockSrc1Address= DTVCC_BLOCK1_START_ADR;
    MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK1_START_ADR, DTVCC_BLOCK1_START_LEN, 0xff);

    BBlockInfo.TOPRSV_Lines = 0;
    BBlockInfo.BTMRSV_Lines = 0;
    BBlockInfo.BGFlashMode = 1;
    BBlockInfo.BG_Blink = FALSE;
    BBlockInfo.FGColorIndex = CC_COLOR_IDX_TRANSPARENT;
    BBlockInfo.BGColorIndex = CC_COLOR_IDX_TRANSPARENT;

    BBlockInfo.V0_x = 0;
    BBlockInfo.V0_y = 0;
    BBlockInfo.V1_x = Width - 1;
    BBlockInfo.V1_y = Height - 1;
    BBlockInfo.fbId = u8CCPreviewFbId;
    CC_RenderFuns.DrawBlock(&BBlockInfo, FALSE, FALSE);
}


void MApp_UiMenu_DrawCCPreviewWin(stCaptionSettingOption_Type *BlinkAttr, CC_FONT * stFont, U16 Width, U16 Height, U16 u16PosX, U16 u16PosY)
{
    CC_ColorInfo_t Blink_ColorInfo;
    BlinkBlock_Info BBlockInfo;
    BlinkChar_Info _CCTextBuf;
    U8 FontIdx;
    UNUSED(Width);
    UNUSED(Height);
    UNUSED(u16PosX);
    UNUSED(u16PosY);

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);

    MApi_GOP_GWIN_Switch2Gwin(u8CCPreviewWinId);
    MApi_GOP_GWIN_Switch2FB(u8CCPreviewFbId);

    CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);
    BBlockInfo.BlockSrc0Address= DTVCC_BLOCK0_START_ADR;
    MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK0_START_ADR, DTVCC_BLOCK0_START_LEN, 0);
    BBlockInfo.BlockSrc1Address= DTVCC_BLOCK1_START_ADR;
    MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK1_START_ADR, DTVCC_BLOCK1_START_LEN, 0xff);

    /* Get Font Width and Height */
    if(BlinkAttr->u8CSFontSize == CAPTION_FONTSIZE_SMALL)
    {
        FontIdx = BlinkAttr->u8CSFontStyle + CC_FONT_SET_NUM; // Small 8 - 15
    }
    else if(BlinkAttr->u8CSFontSize == CAPTION_FONTSIZE_LARGE)
    {
        FontIdx = BlinkAttr->u8CSFontStyle + CC_FONT_SET_NUM*2; // Large 16 - 23
    }
    else // Standard 0 - 7
    {
        FontIdx = BlinkAttr->u8CSFontStyle;
    }

    _CCTextBuf.fHandle = stFont[(FONTHANDLE)FontIdx].fHandle;

    CC_RenderFuns.GetCcFontInfo(_CCTextBuf.fHandle, CC_FONTINFO_WIDTH, &BBlockInfo.Char_Width);
    CC_RenderFuns.GetCcFontInfo(_CCTextBuf.fHandle, CC_FONTINFO_HEIGHT, &BBlockInfo.Char_Height);

    BBlockInfo.TOPRSV_Lines = 0;
    BBlockInfo.BTMRSV_Lines = 0;
    BBlockInfo.BGFlashMode = 1;
    BBlockInfo.BG_Blink = FALSE;
    BBlockInfo.fbId = u8CCPreviewFbId;
    if(g_fCCAttrFlag.fCCAttr_EnableWindowOptionSetting == TRUE)
        BBlockInfo.FGColorIndex = MApp_UiMenu_TransferColor(BlinkAttr->u8CSOptionWindowColor);
    else
        BBlockInfo.FGColorIndex = CC_COLOR_IDX_TRANSPARENT;
    BBlockInfo.BGColorIndex = CC_COLOR_IDX_TRANSPARENT;

    /* Check Window Opacity */
    if (BlinkAttr->u8CSOptionWindowOpacity == CAPTION_WINDOW_FLASHING)
    {
        BBlockInfo.BG_Blink = TRUE;
    }
    else
    {
        BBlockInfo.BG_Blink = FALSE;

        if (BlinkAttr->u8CSOptionWindowOpacity == CAPTION_WINDOW_TRANSLUCENT)
        {
            BBlockInfo.FGColorIndex |= CC_COLOR_IDX_TRANSLUCENT;
        }
        else if (BlinkAttr->u8CSOptionWindowOpacity == CAPTION_WINDOW_TRANSPARENT)
        {
            BBlockInfo.FGColorIndex = CC_COLOR_IDX_TRANSPARENT;
        }
    }

    if(BBlockInfo.BG_Blink == TRUE)
    {
        Blink_ColorInfo.u8Block_BGColorIndex =  BBlockInfo.FGColorIndex;

        CC_RenderFuns.SetSoftBlink(WINDOW_FLASH, &Blink_ColorInfo, NULL);

        BBlockInfo.FGColorIndex = Blink_ColorInfo.u8Block_BGColorIndex;
    }


    BBlockInfo.V0_x = 0;
    BBlockInfo.V0_y = 0;
#if ENABLE_ATSC_KOR
    BBlockInfo.V1_x = BBlockInfo.V0_x + (BBlockInfo.Char_Width * (sizeof(Korean_CC_Preview) + 1)) - 1; //Width - 1;
#else
    BBlockInfo.V1_x = BBlockInfo.V0_x + (BBlockInfo.Char_Width * (sizeof(strE5_CC_Digital_Preview) + 1)) - 1; //Width - 1;
#endif
    BBlockInfo.V1_y = BBlockInfo.Char_Height -1; //Height - 1;
    CC_RenderFuns.DrawBlock(&BBlockInfo, FALSE, FALSE);
}

void MApp_UiMenu_CreateCCPreviewWin(void)
{

//Entering CC preview from MM, the preview window will be out of shape.
#if ( (UI_SKIN_SEL ==  UI_SKIN_1366X768X565) \
    ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X4444) \
    ||(UI_SKIN_SEL ==  UI_SKIN_1366X768X8888) \
    ||(UI_SKIN_SEL ==  UI_SKIN_960X540X565))
  #if (((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE)) \
         ||(UI_SKIN_SEL ==  UI_SKIN_960X540X565))
    #if ENABLE_854x480_UI
	    if((g_IPanel.Width() >= 854) && (g_IPanel.Height() >= 480))
	    {
	        MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
	        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,854, 480);
	        MApi_GOP_GWIN_Set_HSCALE(TRUE,854,PANEL_WIDTH);
	        MApi_GOP_GWIN_Set_VSCALE(TRUE, 480, PANEL_HEIGHT);
	    }
	#else
		if((g_IPanel.Width() >= 960) && (g_IPanel.Height() >= 540))
		{
			MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
			MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,960, 540);
			MApi_GOP_GWIN_Set_HSCALE(TRUE,960,PANEL_WIDTH);
			MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, PANEL_HEIGHT);
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
#elif(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    if((g_IPanel.Width() >= 1920) && (g_IPanel.Height() >= 1080))
    {
        MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0,0, 0,UI_OSD_PANE_W, UI_OSD_PANE_H);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,UI_OSD_PANE_W,PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, UI_OSD_PANE_H, PANEL_HEIGHT);
    }
#endif

    if(u8CCPreviewWinId ==0xff)/*INVALID_WIN_ID*/
    {
        U16 u16X0, u16X1, u16Y0, u16Y1;
        U8 u8PrevGopID;
        BlinkBlock_Info BBlockInfo;

        MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);

        u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();
        msAPI_OSD_GetClipWindow(&u16X0, &u16Y0, &u16X1, &u16Y1);
        //printf("[%s]%lu\n",__FILE__,(U32)__LINE__);
        //printf("CreateWin %d,%d \n",UI_CC_PREVIEW_WIN_WIDTH,UI_CC_PREVIEW_WIN_HEIGHT);

        u8CCPreviewWinId = MApi_GOP_GWIN_CreateWin(UI_CC_PREVIEW_WIN_WIDTH,UI_CC_PREVIEW_WIN_HEIGHT, GFX_FMT_I8);
        u8CCPreviewFbId = MApi_GOP_GWIN_GetFBfromGWIN(u8CCPreviewWinId);
        if(u8CCPreviewWinId == 0xFF)
        {
            printf("\n...failed to create cc preview window...\n");
            return;
        }

        MApi_GOP_GWIN_SetWinPosition(u8CCPreviewWinId, UI_CC_PREVIEW_WIN_START_X, UI_CC_PREVIEW_WIN_START_Y);
        MApi_GOP_GWIN_Switch2Gwin(u8CCPreviewWinId);
        MApi_GOP_GWIN_Switch2FB(u8CCPreviewFbId);
        msAPI_OSD_SetClipWindow(0, 0, UI_CC_PREVIEW_WIN_WIDTH, UI_CC_PREVIEW_WIN_HEIGHT);

        u8GEMODE = CC_GOP_MODE_I8;
        u8GOPID = E_GOP_APP;
        u8GWINID = u8CCPreviewWinId;

        CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);

         /* Clear GWIN First*/
        BBlockInfo.BlockSrc0Address= DTVCC_BLOCK0_START_ADR;
        MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK0_START_ADR, DTVCC_BLOCK0_START_LEN, 0);
        BBlockInfo.BlockSrc1Address= DTVCC_BLOCK1_START_ADR;
        MDrv_GE_ClearFrameBuffer( DTVCC_BLOCK1_START_ADR, DTVCC_BLOCK1_START_LEN, 0xff);
        BBlockInfo.TOPRSV_Lines = 0;
        BBlockInfo.BTMRSV_Lines = 0;
        BBlockInfo.BGFlashMode = 1;
        BBlockInfo.BG_Blink = FALSE;
        BBlockInfo.FGColorIndex = CC_COLOR_IDX_TRANSPARENT;
        BBlockInfo.BGColorIndex = CC_COLOR_IDX_TRANSPARENT;

        BBlockInfo.V0_x = 0;
        BBlockInfo.V0_y = 0;
        BBlockInfo.V1_x = UI_CC_PREVIEW_WIN_WIDTH;
        BBlockInfo.V1_y = UI_CC_PREVIEW_WIN_WIDTH;
        BBlockInfo.fbId = u8CCPreviewFbId;
        CC_RenderFuns.DrawBlock(&BBlockInfo, FALSE, FALSE);  // FIXME

        //msAPI_OSD_DrawBlock(&clrBtn);
        MApi_GOP_GWIN_SetBlending(u8CCPreviewWinId, TRUE, 0x3f);
        MApi_GOP_GWIN_Enable(u8CCPreviewWinId, TRUE);

        MApi_GOP_GWIN_Switch2Gwin(u8PrevGopID);
        msAPI_OSD_SetClipWindow(u16X0, u16Y0, u16X1, u16Y1);

    }
}

void MApp_UiMenu_DeleteCCPreviewWin(void)
{
    if(u8CCPreviewWinId != 0xff)
    {
        MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
        MApi_GOP_GWIN_DeleteWin(u8CCPreviewWinId);
        u8CCPreviewWinId=0xff;
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
        CC_RenderFuns.Close();
    }
}


BOOLEAN MApp_UiMenu_CC_Preview(void)
{
#if Support_Caption_Preview
    U16 u16X0, u16X1, u16Y0, u16Y1;
    stCaptionSettingOption_Type BlinkAttr;
    U8 u8PrevGopID;

    if(u8CCPreviewWinId == 0xFF)
    {
        printf("\n...failed to get cc preview window...\n");
        return FALSE;
    }

    u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();
     MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    msAPI_OSD_GetClipWindow(&u16X0, &u16Y0, &u16X1, &u16Y1);

    MApi_GOP_GWIN_Switch2Gwin(u8CCPreviewWinId);
    MApi_GOP_GWIN_Switch2FB(u8CCPreviewFbId);
    CC_RenderFuns.Open(&u8GEMODE, &u8GOPID, &u8GWINID);

    MApi_GOP_GWIN_SetBlending(u8GWINID,TRUE,0xff);

    msAPI_OSD_SetClipWindow(0, 0, UI_CC_PREVIEW_WIN_WIDTH, UI_CC_PREVIEW_WIN_HEIGHT);
    memcpy(&BlinkAttr, &stGenSetting.g_CaptionSetting.astCaptionOptionCustom, sizeof(stCaptionSettingOption_Type));
    if (stGenSetting.g_CaptionSetting.u8CSOptionMode==CAPTIONMENU_OPTIONMODE_DEFAULT)
    {
        memset(&BlinkAttr, 0xFF, sizeof(stCaptionSettingOption_Type));
        //BlinkAttr.u8CSOptionWindowColor = CAPTION_WINDOW_BLACK;
        //BlinkAttr.u8CSOptionFGColor = CAPTION_FG_WHITE;
    }
    MApp_ClosedCaption_MapUIDefaultSetting(&BlinkAttr);
    MApp_UiMenu_Clear_CC_Preview(UI_CC_PREVIEW_WIN_WIDTH, UI_CC_PREVIEW_WIN_HEIGHT, UI_CC_PREVIEW_WIN_START_X, UI_CC_PREVIEW_WIN_START_Y);
    //MApp_UiMenu_DrawCCPreviewWin(&BlinkAttr, &Font_CC[0], UI_CC_PREVIEW_WIN_WIDTH, UI_CC_PREVIEW_WIN_HEIGHT, UI_CC_PREVIEW_WIN_START_X, UI_CC_PREVIEW_WIN_START_Y);
#if ENABLE_ATSC_KOR
    MApp_ClosedCaption_Preview(&BlinkAttr, &Font_CC[0], Korean_CC_Preview, sizeof(Korean_CC_Preview)/2, UI_CC_PREVIEW_WIN_START_X, UI_CC_PREVIEW_WIN_START_Y);
#else
    MApp_ClosedCaption_Preview(&BlinkAttr, &Font_CC[0], strE5_CC_Digital_Preview, sizeof(strE5_CC_Digital_Preview), UI_CC_PREVIEW_WIN_START_X, UI_CC_PREVIEW_WIN_START_Y);
#endif
    MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);
    msAPI_OSD_SetClipWindow(u16X0, u16Y0, u16X1, u16Y1);
    return TRUE;
#else
    return FALSE;
#endif
}

