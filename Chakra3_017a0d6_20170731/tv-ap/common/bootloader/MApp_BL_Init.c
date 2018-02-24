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

#define MAPP_BL_INIT_C

#include <stdio.h>
#include "Board.h"

#include "drvSERFLASH.h"

#include "msAPI_DrvInit.h"
#include "msAPI_Flash.h"
#include "msAPI_FS_SysInfo.h"
#include "msAPI_Memory.h"
#include "msAPI_Tuner.h"
//#include "msAPI_MIU.h"
//#include "BinInfo.h"
//#include "InfoBlock.h"

#if(ENABLE_S2)
#include "drvDish.h"
#if ( FRONTEND_DEMOD_S2_TYPE  == EMBEDDED_DVBS_DEMOD)
#include "INTERN_DVBS.h"
#endif
#endif

//extern void UART_Clear(void);
#if (ENABLE_BL_UI)
//refer from display_logo of MBoot
#include "apiGFX.h"
#include "apiGOP.h"
#include "Panel.h"
#include "DemoFineTune.h"
#include "util_symbol.h"
#include "msAPI_Font.h"
#include "BinInfo.h"
#include "msAPI_OSD.h"
#include "msAPI_OSD_Resource.h"
#include "MApp_SaveData.h"

#include "msAPI_DB_CH.h"
#include "msAPI_Timer.h"
#include "msAPI_MIU.h"




#define DEBUG_BL_UI(x)  //x

#define GOP_BUFFER_ADDR                         GOP_GWIN_RB_ADR //0x6100000

MS_BOOL _sc_is_interlace(void)
{
    return 0;
}

MS_U16 _sc_get_h_cap_start(void)
{
    return 0x60;
}
void _Sys_PQ_ReduceBW_ForOSD(MS_U8 PqWin, MS_BOOL bOSD_On)
{
    PqWin=bOSD_On=0;
}

MS_U16  devPanel_HStart(void)
{
    return g_IPanel.HStart();
}

MS_U16 MApp_BL_devPanel_width(void)
{
    return devPanel_WIDTH() >= 1920 ? 1920 : devPanel_WIDTH();
}

MS_U16 MApp_BL_devPanel_height(void)
{
    return devPanel_HEIGHT() >= 1080 ? 1080 : devPanel_HEIGHT();
}

void MApp_BL_Gop_stretch(U16 graph_pitch, U16 graph_width, U16 graph_height, MS_BOOL bHorStretch, MS_BOOL bVerStretch)
{
    U32 u32GWinDispX_Max;
    U32 u32GWinDispY_Max;


    u32GWinDispX_Max = MApp_BL_devPanel_width();
    u32GWinDispY_Max = MApp_BL_devPanel_height();

    if (bHorStretch)
        MApi_GOP_GWIN_Set_HSCALE(TRUE, graph_width, u32GWinDispX_Max);
    if (bVerStretch)
        MApi_GOP_GWIN_Set_VSCALE(TRUE, graph_height, u32GWinDispY_Max);

    MApi_GOP_GWIN_Set_STRETCHWIN(0, E_GOP_DST_OP0, 0, 0, graph_pitch, graph_height);
}

static void MApp_BL_BurstInitGOP(U16 u16X, U16 u16Y, U16 u16Pitch, U16 u16Height, U32 u32GopBuffer)
{
    U32 u32DispX;
    U32 u32DispY;
    U16 u16PanelWidth;
    U32 u32PanelHeight;
    U32 u32Panel_Hstart;
    GOP_InitInfo pGopInit;

    DEBUG_BL_UI( printf("MApp_BL_BurstInitGOP(u16X=%u,u16Y=%u,u16Pitch=%u,u16Height=%u,u32GopBuffer=0x%X)\n", u16X,u16Y,u16Pitch,u16Height,u32GopBuffer); );

    u32DispX = u16X;
    u32DispY = u16Y;
    u16PanelWidth = MApp_BL_devPanel_width();
    u32PanelHeight = MApp_BL_devPanel_height();
    u32Panel_Hstart = devPanel_HStart();

    DEBUG_BL_UI( printf( "u16PanelWidth=%u\n", u16PanelWidth); );
    DEBUG_BL_UI( printf( "u32PanelHeight=%u\n", u32PanelHeight); );
    DEBUG_BL_UI( printf( "u32Panel_Hstart=%u\n", u32Panel_Hstart); );

    MApi_GOP_RegisterFBFmtCB(( MS_U32(*)(MS_U16 pitch,MS_U32 addr , MS_U16 fmt ))msAPI_OSD_RESOURCE_SetFBFmt);
    MApi_GOP_RegisterXCIsInterlaceCB(_sc_is_interlace);
    MApi_GOP_RegisterXCGetCapHStartCB(_sc_get_h_cap_start);
    MApi_GOP_RegisterXCReduceBWForOSDCB(_Sys_PQ_ReduceBW_ForOSD);

    pGopInit.u16PanelWidth = u16PanelWidth;
    pGopInit.u16PanelHeight = u32PanelHeight;
    pGopInit.u16PanelHStr = u32Panel_Hstart;
    pGopInit.u32GOPRBAdr = u32GopBuffer;//((GOP_GWIN_RB_MEMORY_TYPE & MIU1) ? (GOP_GWIN_RB_ADR | MIU_INTERVAL) : (GOP_GWIN_RB_ADR));
    pGopInit.u32GOPRBLen = u16PanelWidth * u32PanelHeight * 2;

    DEBUG_BL_UI( printf( "u32GOPRBAdr=0x%X\n", pGopInit.u32GOPRBAdr); );
    DEBUG_BL_UI( printf( "u32GOPRBLen=0x%X\n", pGopInit.u32GOPRBLen); );

    //there is a GOP_REGDMABASE_MIU1_ADR for MIU1
//    pGopInit.u32GOPRegdmaAdr = 0;//((GOP_REGDMABASE_MEMORY_TYPE & MIU1) ? (GOP_REGDMABASE_ADR | MIU_INTERVAL) : (GOP_REGDMABASE_ADR));
  //  pGopInit.u32GOPRegdmaLen = 0;
    pGopInit.u32GOPRegdmaAdr = ((GOP_REGDMABASE_MEMORY_TYPE & MIU1) ? (GOP_REGDMABASE_ADR | MIU_INTERVAL) : (GOP_REGDMABASE_ADR));//GOP_REGDMABASE_ADR;//
    pGopInit.u32GOPRegdmaLen = GOP_REGDMABASE_LEN;

    pGopInit.bEnableVsyncIntFlip = FALSE;

    MApi_GOP_InitByGOP(&pGopInit, 0);

    U8 u8FbId, u8GwinId;
    u8FbId = MApi_GOP_GWIN_GetFreeFBID();
    u8GwinId =0;

    MApi_GOP_GWIN_CreateFBbyStaticAddr(u8FbId, u32DispX, u32DispY, u16Pitch, u16Height, E_MS_FMT_RGB565, u32GopBuffer);
    printf("%s: u32GopBuffer: 0x%lx, at %d\n", __func__, u32GopBuffer, __LINE__);

    MApi_GOP_GWIN_MapFB2Win(u8FbId, 0);
    MApi_GOP_GWIN_Switch2FB(u8FbId);
    MApi_GOP_GWIN_SetWinDispPosition(u8GwinId, u32DispX, u32DispY);

    MApi_GOP_GWIN_SetBlending(u8GwinId, FALSE, 63);

//    MApi_GOP_GWIN_Enable(u8GwinId, TRUE);
}

void InitGOPEnv(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height,
    U16 u16Pitch, MS_BOOL bHorStretch, MS_BOOL bVerStretch, U32 u32FramBufferAddr)
{
    //U16 *u16TempAddr;
    GFX_Config tGFXcfg;
    GFX_Point gfxPt0 = { 0, 0 };
    GFX_Point gfxPt1 = { 1920, 1080 };

    DEBUG_BL_UI( printf("InitGOPEnv(u16X=%u, u16Y=%u, u16Width=%u, u16Height=%u, u16Pitch=%u, bHorStretch=%u, bVerStretch=%u, u32FramBufferAddr=0x%X)\n",
                u16X, u16Y, u16Width, u16Height, u16Pitch, bHorStretch, bVerStretch, u32FramBufferAddr ); );

    //u16TempAddr = (U16 *)(u32FramBufferAddr|0xA0000000);

    DEBUG_BL_UI( printf("MApi_GFX_Init()\n"); );
    // Init GE driver
    tGFXcfg.bIsCompt = TRUE;
    tGFXcfg.bIsHK = TRUE;
    MApi_GFX_Init(&tGFXcfg);

	gfxPt0.x = u16X;
	gfxPt0.y = u16Y;

	gfxPt1.x = u16X + u16Width;
	gfxPt1.y = u16Y + u16Height;

    DEBUG_BL_UI( printf("MApi_GFX_SetClip()\n"); );
    DEBUG_BL_UI( printf("gfxPt0.x,y=%u,%u\n", gfxPt0.x, gfxPt0.y ); );
    DEBUG_BL_UI( printf("gfxPt1.x,y=%u,%u\n", gfxPt1.x, gfxPt1.y ); );

    MApi_GFX_SetClip(&gfxPt0, &gfxPt1);

    if (bHorStretch)
    {
        u16X = 0;
    }
    if (bVerStretch)
    {
        u16Y = 0;
    }

    MApp_BL_BurstInitGOP(u16X, u16Y, u16Pitch, u16Height, u32FramBufferAddr);

    if (bHorStretch||bVerStretch)
        MApp_BL_Gop_stretch(u16Pitch, u16Width, u16Height, bHorStretch, bVerStretch);

	MApi_GFX_RegisterGetFontCB(msAPI_OSD_RESOURCE_GetFontInfoGFX);
}

void BL_DrawProgressBar(U16 x, U16 y, U16 width, U16 height, U32 t_clr, U32 b_clr, U32 g_clr, U8 u8Gradient, U8 pertvalue)
{
		OSDClrBtn clrBtn2;
		char warningMsg[16];

		clrBtn2.x = x;
		clrBtn2.y = y;
		clrBtn2.radius = 0;
		clrBtn2.width = width;
		clrBtn2.height = height;
		clrBtn2.b_clr = b_clr;
		clrBtn2.g_clr = g_clr;
		clrBtn2.t_clr = t_clr;
		clrBtn2.u8Gradient = u8Gradient;
		clrBtn2.fHighLight = FALSE;
		clrBtn2.Fontfmt.flag = GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP;
		clrBtn2.Fontfmt.ifont_gap = 2;
		clrBtn2.enTextAlign = EN_ALIGNMENT_CENTER;
		clrBtn2.bStringIndexWidth = CHAR_IDX_1BYTE;

		msAPI_OSD_DrawBlock(&clrBtn2);

		memset(warningMsg, 0x00, sizeof(warningMsg));
		snprintf((char *)warningMsg, 14,  "%ld%%", pertvalue);
		msAPI_OSD_DrawText(Font[FONT_0].fHandle, (U8 *)warningMsg, &clrBtn2);
}

void MApp_BL_DisplaySystem_clear(void)
{
    OSDClrBtn clrBtn;

    // clear screen
    clrBtn.x = 0;
    clrBtn.y = 0;
    clrBtn.width = MApp_BL_devPanel_width();
    clrBtn.height = MApp_BL_devPanel_height();
    clrBtn.b_clr = 0xFF000000;
    clrBtn.u8Gradient = CONSTANT_COLOR;
    clrBtn.fHighLight = FALSE;
    msAPI_OSD_DrawBlock(&clrBtn);
}

void MApp_BL_DisplaySystem_setStatus(S8 *status)
{
    OSDClrBtn clrBtn;
    U8 strStatus[32];
    U8 warningMsg[255];

    if(!status)
        return;
    memset(strStatus, 0x00, sizeof(strStatus));
    snprintf((char*)strStatus, strlen((char*)status), "%s", status);

    // draw warning message
	clrBtn.x =  0;
	clrBtn.y =  MApp_BL_devPanel_height() / 4;
	clrBtn.width = MApp_BL_devPanel_width();
	clrBtn.height = MApp_BL_devPanel_height() / 4;
	clrBtn.radius = 0;
	clrBtn.u8Gradient = CONSTANT_COLOR;
	clrBtn.b_clr =  COLOR_BLUE;
	clrBtn.fHighLight =  FALSE;
	clrBtn.t_clr = COLOR_WHITE;
	clrBtn.Fontfmt.flag = GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP;
	clrBtn.Fontfmt.ifont_gap = 2;
	clrBtn.enTextAlign = EN_ALIGNMENT_CENTER;

	clrBtn.bStringIndexWidth = CHAR_IDX_1BYTE;
	memset(warningMsg, 0x00, sizeof(warningMsg));
	//memcpy(warningMsg, "SCANING", 16);
	memcpy(warningMsg, strStatus, 24);

	msAPI_OSD_DrawText(Font[FONT_0].fHandle, (U8 *)warningMsg, &clrBtn);
}

void MApp_BL_DisplaySystem(U8 u8Percent)
{
    OSDClrBtn clrBtn;
    U8 warningMsg[255];
    U32 i, nStep;

    // clear screen
    clrBtn.x = 0;
    clrBtn.y = 0;
    clrBtn.width = MApp_BL_devPanel_width();
    clrBtn.height = MApp_BL_devPanel_height();
    clrBtn.b_clr = 0x00000000;
    clrBtn.u8Gradient = CONSTANT_COLOR;
    clrBtn.fHighLight = FALSE;
    //msAPI_OSD_DrawBlock(&clrBtn);

	// draw warning message
	clrBtn.x =  0;
	//clrBtn.y =  MApp_BL_devPanel_height() / 4;
	clrBtn.y =  0;
	clrBtn.width = MApp_BL_devPanel_width();
	clrBtn.height = MApp_BL_devPanel_height() / 4;
	clrBtn.radius = 0;
	clrBtn.u8Gradient = CONSTANT_COLOR;
	clrBtn.b_clr =  COLOR_BLUE;
	clrBtn.fHighLight =  FALSE;
	clrBtn.t_clr = COLOR_WHITE;
	clrBtn.Fontfmt.flag = GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP;
	clrBtn.Fontfmt.ifont_gap = 2;
	clrBtn.enTextAlign = EN_ALIGNMENT_CENTER;

	clrBtn.bStringIndexWidth = CHAR_IDX_1BYTE;
	memset(warningMsg, 0x00, sizeof(warningMsg));
	memcpy(warningMsg, "DO NOT POWER OFF", 16);

	msAPI_OSD_DrawText(Font[FONT_0].fHandle, (U8 *)warningMsg, &clrBtn);

	MApi_GOP_GWIN_Enable(0, TRUE);

	clrBtn.width = 10;
	//for(i=1;i<=100;i++)
	nStep = ( MApp_BL_devPanel_width() - 120 ) / 100;

	i = (U32)u8Percent;
	{
		if ( i > 0 )
			clrBtn.width = nStep*i;
		//BL_DrawProgressBar((MApp_BL_devPanel_width()-98*18-10)/2, MApp_BL_devPanel_height()/2, clrBtn.width, 100, 0xFFFFFFFF, 0xFF123456, 0xFF1234FF, GRADIENT_X_COLOR, i);
		BL_DrawProgressBar((MApp_BL_devPanel_width()-98*nStep-10)/2, MApp_BL_devPanel_height()/2, clrBtn.width, 100, 0xFFFFFFFF, 0xFF123456, 0xFF1234FF, GRADIENT_X_COLOR, i);
	}
}

extern void _MApi_XC_Sys_Init_Panel(void);
void Initial_BL_DisplaySystem(void)
{
    OSDClrBtn clrBtn;
    U8 warningMsg[255];
    GFX_BufferInfo dstbuf;

    DEBUG_BL_UI( printf("Initial_BL_DisplaySystem()\n"); );

    Util_InitSymbolTBL();

#if SUPPORT_VX1_OUTPUT
    _MApi_XC_Sys_Init_Panel();
#else

  #if ENABLE_MFC_6M20
    MApi_PNL_Init_MISC(E_APIPNL_MISC_MFC_ENABLE);
    MApi_BD_LVDS_Output_Type(4);
    MApi_PNL_MOD_OutputConfig_User(0x5540, 0x1555, 0x00);
  #else
    if (devPanel_IsTTL(g_PNL_TypeSel)) //TTL output
    {
        MApi_BD_LVDS_Output_Type(0x04);//LVDS user mode
        MApi_PNL_MOD_OutputConfig_User(0x00,0x00,0x00);
    }
    else // LVDS output
    {
        MApi_BD_LVDS_Output_Type(BD_LVDS_CONNECT_TYPE);
    }
  #endif

    MApi_PNL_Init( MApi_XC_GetPanelSpec(g_PNL_TypeSel));
    //g_IPanel.Dump();
    //g_IPanel.SetGammaTbl(E_APIPNL_GAMMA_12BIT, tAllGammaTab, GAMMA_MAPPING_MODE);
#endif

    MApi_PNL_En(TRUE);

    MApi_PNL_SetBackLight(BACKLITE_INIT_SETTING);

    InitGOPEnv(0, 0, ALIGN_8(MApp_BL_devPanel_width()), MApp_BL_devPanel_height(), ALIGN_8(MApp_BL_devPanel_width()), 0, 0, GOP_BUFFER_ADDR);

	msAPI_Font_VariableInit();

	Font[0].fHandle = msAPI_Font_LoadFlashFontToSDRAM(BIN_ID_FONT_BL_ENG_50);

    dstbuf.u32ColorFmt = GFX_FMT_RGB565;
    dstbuf.u32Addr = GOP_BUFFER_ADDR;
    dstbuf.u32Pitch = ALIGN_8(MApp_BL_devPanel_width()*2);
    MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

	// clear screen
    clrBtn.x = 0;
    clrBtn.y = 0;
    clrBtn.width = MApp_BL_devPanel_width();
    clrBtn.height = MApp_BL_devPanel_height();
    clrBtn.b_clr = 0x00000000;
    clrBtn.u8Gradient = CONSTANT_COLOR;
    clrBtn.fHighLight = FALSE;
    msAPI_OSD_DrawBlock(&clrBtn);

	// draw warning message
	clrBtn.x =  0;
	//clrBtn.y =  MApp_BL_devPanel_height() / 4;
	clrBtn.y =  0;
	clrBtn.width = MApp_BL_devPanel_width();
	clrBtn.height = MApp_BL_devPanel_height() / 4;
	clrBtn.radius = 0;
	clrBtn.u8Gradient = CONSTANT_COLOR;
	clrBtn.b_clr =  COLOR_BLUE;
	clrBtn.fHighLight =  FALSE;
	clrBtn.t_clr = COLOR_WHITE;
	clrBtn.Fontfmt.flag = GEFONT_FLAG_VARWIDTH | GEFONT_FLAG_GAP;
	clrBtn.Fontfmt.ifont_gap = 2;
	clrBtn.enTextAlign = EN_ALIGNMENT_CENTER;
#if 1
	clrBtn.bStringIndexWidth = CHAR_IDX_1BYTE;
	memset(warningMsg, 0x00, sizeof(warningMsg));
	memcpy(warningMsg, "DO NOT POWER OFF", 16);
#else
	clrBtn.bStringIndexWidth = CHAR_IDX_2BYTE;
	warningMsg[0] = 'H';
	warningMsg[1] = 0x00;
	warningMsg[2] = 'e';
	warningMsg[3] = 0x00;
	warningMsg[4] = 'l';
	warningMsg[5] = 0x00;
	warningMsg[6] = 'l';
	warningMsg[7] = 0x00;
	warningMsg[8] = 'o';
	warningMsg[9] = 0x00;
	warningMsg[10] = 0x00;
	warningMsg[11] = 0x00;
#endif
	msAPI_OSD_DrawText(Font[FONT_0].fHandle, (U8 *)warningMsg, &clrBtn);

	MApi_GOP_GWIN_Enable(0, TRUE);

    DEBUG_BL_UI(printf("logo display end\n"));
}
#endif //(ENABLE_BL_UI)

S32 volatile gS32OffsetTime;

#if 1 //from MApp_Init.c
#if (ENABLE_DTV)
//#include "mapp_demux.h"
#include "mapp_si.h"
#include "MApp_SI_Parse.h"
#include "msAPI_DTVSystem.h"
#include "mapp_eit.h"
#include "MApp_EpgTimer.h"
#if (BLOADER)
#include "MApp_BL_SI.h"
#endif
#endif

#if(ENABLE_DTV && ENABLE_BL_OAD_SCAN)
static void _MApp_BL_DTVInit(void)
{
#if 1//(BLOADER)
  #if(ENABLE_ATSC)
    U32 u32SIBufferStartAddress = _PA2VA(((EVENTDB_SDRAM_MEMORY_TYPE & MIU1) ? (EVENTDB_SDRAM_ADR | MIU_INTERVAL) : (EVENTDB_SDRAM_ADR)));
    U32 u32SIBufferSize = EVENTDB_SDRAM_LEN;
    MApp_BL_SI_Init(u32SIBufferStartAddress, u32SIBufferSize);
  #else
    U32 u32SIBufferStartAddress = _PA2VA(((SI_MONITOR_DB_MEMORY_TYPE & MIU1) ? (SI_MONITOR_DB_ADR | MIU_INTERVAL) : (SI_MONITOR_DB_ADR)));
    U32 u32SIBufferSize = SI_MONITOR_DB_LEN;
    MApp_BL_SI_Init(u32SIBufferStartAddress, u32SIBufferSize);
  #endif

#else
    MS_SI_INIT_PARAMETER sSIParameter;
 #if (ENABLE_DTV_EPG)
    DTV_CM_INIT_PARAMETER sDTVNotify;
    MS_EIT_INIT_PARAMETER sEITInitParameter;
 #endif // #if (ENABLE_DTV_EPG)

    /*Clear EPG Timer before loading DataBase*/
  #if ENABLE_DTV_EPG //(ENABLE_DTV)
    MApp_EpgTimer_InitTimerSettings(FALSE);
  #endif

 #if (ENABLE_DTV_EPG)
    memset(&sEITInitParameter,0,sizeof(MS_EIT_INIT_PARAMETER));
 #endif // #if (ENABLE_DTV_EPG)
    memset(&sSIParameter,0,sizeof(MS_SI_INIT_PARAMETER));
 	sSIParameter.u8MaxServiceOneMux=MAX_VC_PER_PHYSICAL;
    sSIParameter.u32SIBufferStartAddress = _PA2VA(((SI_MONITOR_DB_MEMORY_TYPE & MIU1) ? (SI_MONITOR_DB_ADR | MIU_INTERVAL) : (SI_MONITOR_DB_ADR)));
    sSIParameter.u32SIBufferSize = SI_MONITOR_DB_LEN;
    sSIParameter.u32SINameBufferAddress = _PA2VA(((SRV_NAME_BUF_MEMORY_TYPE & MIU1) ? (SRV_NAME_BUF_ADR | MIU_INTERVAL) : (SRV_NAME_BUF_ADR)));

  #if (ENABLE_SBTVD_BRAZIL_APP == 0)
    sSIParameter.eSI_Type=SI_PARSER_DVB;
  #else
    sSIParameter.eSI_Type=SI_PARSER_ISDB_ABNT;
  #endif

    sSIParameter.bSkipUnsupportService = FALSE;


  #if (ENABLE_DTV_EPG)
   sSIParameter.bEnableEPG=TRUE;
  #endif
  #if (ENABLE_SBTVD_BRAZIL_APP == 0)
    sSIParameter.pfNotify_PMT = MApp_SI_Parse_PMT;
  #endif
  #if 1//ENABLE_TS_FILEIN
    sSIParameter.pfNotify_FileIn_PMT = MApp_SI_FileIn_Parse_PMT;
  #endif
  #if ENABLE_OAD
    sSIParameter.pfNotify_NIT = MApp_SI_Parse_NIT;
  #endif
  #if ENABLE_CI
    sSIParameter.pfNotify_SDT = MApp_SI_Parse_SDT;
  #endif


    MApp_SI_Init(&sSIParameter);

    /* init epg database */
#if (ENABLE_DTV_EPG)
 #if (ENABLE_SBTVD_BRAZIL_APP==0)
    sEITInitParameter.u32PF_BufferAddress =_PA2VA(EIT_PF_STRING_BUF_ADR);
    sEITInitParameter.pfNotify_EIT_Cur_PF=MApp_SI_Parse_EIT;
  #if SUPPORT_PVR_CRID
    if(EVENTDB_SDRAM_LEN>=0x0000840000)
    {
        sEITInitParameter.bEnablePVR_CRID=TRUE;
    }
  #endif
  #if ENABLE_SCHE_EXT
    sEITInitParameter.bEnableScheduleExtendEvent=TRUE;
  #endif
    MApp_EIT_Init(&sEITInitParameter);
 #endif // #if (ENABLE_SBTVD_BRAZIL_APP==0)

    memset(&sDTVNotify,0,sizeof(sDTVNotify));
    sDTVNotify.pfNotify_CM_MoveProgram=MApp_Epg_MoveSrvBuffer;
    sDTVNotify.pfNotify_CM_SwapProgram=MApp_Epg_SwapProgram;
    sDTVNotify.pfNotify_SrvPriorityHandler=MApp_Epg_SrvPriorityHandler;
    sDTVNotify.pfNotify_CM_RemoveProgram=MApp_Epg_RemoveProgram;
    msAPI_CM_Init_EPG(&sDTVNotify);

    MApp_EIT_All_Sche_ResetFilter();

    {
        U32 u32EventDbMIUAddrGap = ( (EVENTDB_SDRAM_MEMORY_TYPE&MIU1) ? MIU_INTERVAL : 0x0000000 );
        U32 u32EventDbAddr       = EVENTDB_SDRAM_ADR + u32EventDbMIUAddrGap;
        U32 u32ExtDbMIUAddrGap;//   = ( (EPGEXTDB_SDRAM_MEMORY_TYPE&MIU1) ? MIU_INTERVAL : 0x0000000 );
        U32 u32ExtDbAddr;//         = EPGEXTDB_SDRAM_ADR + u32ExtDbMIUAddrGap;
#if ENABLE_SCHE_EXT
        u32ExtDbMIUAddrGap   = ( (EPGEXTDB_SDRAM_MEMORY_TYPE&MIU1) ? MIU_INTERVAL : 0x0000000 );
        u32ExtDbAddr         = EPGEXTDB_SDRAM_ADR + u32ExtDbMIUAddrGap;
#else
        u32ExtDbMIUAddrGap=u32ExtDbAddr=0;
#endif
  #if SUPPORT_PVR_CRID
        if(EVENTDB_SDRAM_LEN>=0x0000840000)
        {
            MAPP_EPG_SetFunctionFlag(eEN_PVR_CRID);
        }
  #endif

  #if ENABLE_SCHE_EXT
        MAPP_EPG_SetFunctionFlag(eEN_SCHE_EXT);
  #endif
        MApp_EPGDB_Setup(MAX_DTVPROGRAM, _PA2VA(u32EventDbAddr), EVENTDB_SDRAM_LEN, _PA2VA(u32ExtDbAddr), EPGEXTDB_SDRAM_LEN);
        MApp_Epg_Init();

    }
#endif //#if (ENABLE_DTV_EPG)
#endif //if (BLOADER)
}
#endif // #if(ENABLE_DTV && ENABLE_BL_OAD_SCAN)
#endif


void MApp_BL_LoadFlashData(void)
{
#if( ENABLE_OAD && (ENABLE_OAD_DATA_SAVE_TO_DB_CH))
    //extern void MApp_DB_CH_Init(void);
    //MApp_DB_CH_Init(); //load country setting in database

    Stru_DB_CH_InitData stDB_CH_InitData =
    {
        DB_CH_VERSION_ID, //U32 u32MagicId;

        // Flash ...
        FMAP_CH_DB_BANK_START,//U8 u8FlashBankStart;
        DB_BANK_COUNT,//U8 u8FlashSaveBankCount;

        // Dram
        RAM_DISK_DB_64K_START_ADDR,//U32 u32DramDataAddr;
        RM_OAD_SETTING_SIZE,//U32 u32DramDataSize;

        // CallBack function
        NULL,//MApp_DB_CH_CallBack_BeforeWriteFlash, //void (*pfCallBack_BeforeWriteFlash)(void);

        // Debug
        1, //U8 u8DebugFlag;
    } ;

    msAPI_DB_CH_Init( &stDB_CH_InitData );

    msAPI_DB_CH_Printf_Variable();

    memset( (U8*)_PA2VA(RAM_DISK_DB_64K_START_ADDR) ,0,RM_OAD_SETTING_SIZE);
    MsOS_FlushMemory();


    // Load data from flash to dram~
    BOOL bLoadCHDataFromFlashResult = msAPI_DB_CH_LoadFromFlash();

    if( bLoadCHDataFromFlashResult == FALSE )
    {
        //bDB_CH_CheckDataResult = FALSE;
        printf("\nBL Error: Load OAD_Setting from flash failed\n");
    }
    else
    {
        // Check DB_CH ID:
        //bDB_CH_CheckDataResult = MApp_DB_CH_CheckData();
        //bDB_Gen_VersionCheckResult = 0;
        //if( bDB_CH_CheckDataResult == FALSE )
        {
            //printf("\nError: DB_CH Check data Fail!\n");
            //MApp_DB_CH_WriteMagicDataToDram();
        }
    }

#endif //ENABLE_OAD

}

void MApp_BL_Init(void)
{
    //BININFO   BinInfo;
    //BOOLEAN bResult;
    /*MDrv_DMA_CB_Init((eDmaType_t) DRAM_BYTEDMA, DUMMY_ADR,DUMMY_LEN,
                          BMP_INFO_POOL_LEN, BMP_INFO_POOL_ADR,
                          FONT_INFO_POOL_LEN, FONT_INFO_POOL_ADR);*/

    /* initialize all device drivers */
    msAPI_ChipInit();

    msAPI_Interrupt_Init();

    /* initialize 8K bytes memory pool */
    msAPI_Memory_Init();

    //MApp_Panel_Init();

    //Init Scaler, LVDS...etc
    msAPI_DrvInit_InitForBLoader();

#if (ENABLE_BL_UI)
	Initial_BL_DisplaySystem();
#endif //(ENABLE_BL_UI)

    //printf("#1\n");
	MDrv_FLASH_WriteProtect(ENABLE);

    //msAPI_MIU_Get_BinInfo(&BinInfo, &bResult) ;
    //bResult = Get_BinInfo(&BinInfo);


#if (EEPROM_DB_STORAGE != EEPROM_SAVE_ALL)
  #if (ENABLE_BOOTTIME)
    gU32BootStepTime = msAPI_Timer_GetTime0();
  #endif

    //MApp_CheckFlash();
    MApp_BL_LoadFlashData();

  #if (ENABLE_BOOTTIME)
    gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootStepTime);
    printf("[boot step time]MApp_BL_LoadFlashData = %ld\n", gU32TmpTime);
  #endif
#endif //

    //UART_Clear();

#if(ENABLE_DTV && ENABLE_BL_OAD_SCAN)
    _MApp_BL_DTVInit();
#endif

#if ENABLE_OAD
  #if 0//( FRONTEND_DEMOD_S2_TYPE  == EMBEDDED_DVBS_DEMOD)
    MDrv_Dish_Init();
  #endif

    //msAPI_Tuner_Initialization_BySource();
    //msAPI_Tuner_InitExternDemod();

  #if(ENABLE_ATSC)
    msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_SOURCE, E_DEMODULATOR_TYPE_ATSC);
  #else
    msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_SOURCE, E_DEMODULATOR_TYPE_DVBT );
  #endif

    //msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);

#endif

    msAPI_FS_Init();
}
#undef MAPP_BL_INIT_C

