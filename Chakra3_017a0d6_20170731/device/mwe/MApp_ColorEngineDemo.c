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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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

#define _MAPP_COLORENGINEDEMO_C_

#include "Board.h"
#if (COLOR_DEMO_FUNCTION )
#include "MsTypes.h"
#include "string.h"
#include "apiXC.h"

#include "apiXC_Ace.h"
#include "apiXC_Dlc.h"
#include "apiPNL.h"
#include "msAPI_Timer.h"
#include "drvMWE.h"


#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIcomponent.h"
#include "ZUI_exefunc.h"

#include "OSDcp_Bitmap_EnumIndex.h"
#include "msAPI_Memory.h"
#include "MApp_ColorEngineDemo.h"
#include "MApp_GlobalFunction.h"
#include "msAPI_Timer.h"

//-------------------------------------------------------------------------------------------------------------
extern U8 msAPI_Mode_PictureSaturationN100toReallyValue ( U8 u8value );
extern  U8 msAPI_Mode_PictureBrightnessN100toReallyValue ( U8 u8value );
extern  U8 MApp_Scaler_FactoryAdjBrightness(U8 u8Brightness, U8 u8SubBrightness);
extern MS_U8 MApi_XC_Sys_ACE_transfer_Bri(MS_U8 u8Brightness, MS_U8 u8Brightnesstype);

//---------------------------------------------------------------------------------------------------------------
#define UI_HISTOGRAM_BLOCK_STEP            64
MS_U16 wWaveValue[UI_HISTOGRAM_BLOCK_STEP];
MS_U16 wWaveIndex=0;

//--------------------------------------------------------------------------------------------------------------
#if MWE_FUNCTION
static U8 g_RegData_Bak1;
static U8 g_RegData_Bak2;
static U8 g_RegData_Bak3;
static U8 g_RegData_Bak4;
static U8 g_RegData_Bak5;
static U8 g_RegData_Bak6;
static U8 g_RegData_Bak7;
static U8 g_RegData_Bak8;
static U8 g_RegData_Bak9;
static U8 g_RegData_Bak10;
static U8 g_RegData_Bak11;
static U8 g_RegData_Bak12;
static U8 g_RegData_Bak13;
static U8 g_RegData_Bak14;
#define	ANALIZE_COLOR_END_CNT		450
#define	ANALIZE_BOADER_END_CNT		600
#define	ANALIZE_SCENE_END_CNT		200
#define	ANALIZE_FEILD_END_CNT		300


void MApp_UiMenuFunc_MWEAnalizeInit(void)
{
	g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_NONE;
	g_stMWEAnSts.bCnt = 0;
	g_stMWEAnSts.bStepCnt=0;

	g_stMWEAnSts.bBorderAn=TYPE_MWE_AN_OFF;
	g_stMWEAnSts.bColorAn=TYPE_MWE_AN_OFF;
	g_stMWEAnSts.bFeildAn=TYPE_MWE_AN_OFF;
	g_stMWEAnSts.bSceneAn=TYPE_MWE_AN_OFF;

}
BOOLEAN	 MApp_UiMenuFunc_MWEIsAnalizing(void)
{
	if(g_stMWEAnSts.bColorAn == TYPE_MWE_AN_ING ||
	    g_stMWEAnSts.bBorderAn== TYPE_MWE_AN_ING ||
	    g_stMWEAnSts.bSceneAn== TYPE_MWE_AN_ING ||
	    g_stMWEAnSts.bFeildAn== TYPE_MWE_AN_ING )
	{
		return TRUE;
	}
	else
		return FALSE;
}

BOOLEAN MApp_UiMenuFunc_AdjustMWEAnalizeMode(U8 u8Mode)
{

    if((g_stMWEAnSts.bColorAn==TYPE_MWE_AN_ING) ||
	(g_stMWEAnSts.bBorderAn==TYPE_MWE_AN_ING) ||
	(g_stMWEAnSts.bSceneAn==TYPE_MWE_AN_ING) ||
	(g_stMWEAnSts.bFeildAn==TYPE_MWE_AN_ING))
	{
		return 0;
	}
	MDrv_MWE_WinOnOff(ENABLE);
	msAPI_ACE_MWEFuncSel(MWE_MODE_H_SPLIT);
    switch(u8Mode)
   {
	  case 0:
	  		g_stMWEAnSts.bColorAn = TYPE_MWE_AN_ING;
			g_stMWEAnSts.bAnalizeSts=MWE_ANALIZE_COLOR;
			MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_COLOR_SELTEXT);
	      break;
	  case 1:
	  		g_stMWEAnSts.bBorderAn= TYPE_MWE_AN_ING;
			g_stMWEAnSts.bAnalizeSts=MWE_ANALIZE_BORDER;
			MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_BORDER_SELTEXT);
	      break;
 	  case 2:
	  		g_stMWEAnSts.bSceneAn= TYPE_MWE_AN_ING;
			g_stMWEAnSts.bAnalizeSts=MWE_ANALIZE_BRIGHT;
			MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_SCEN_SELTEXT);
	      break;
	  case 3:
	  		g_stMWEAnSts.bFeildAn= TYPE_MWE_AN_ING;
			g_stMWEAnSts.bAnalizeSts=MWE_ANALIZE_COLORFIELD;
			MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_FILED_SELTEXT);
	      break;
    }
    g_stMWEAnSts.bStepCnt=14;
    g_stMWEAnSts.bCnt=0;
	g_wColorEngineDemoStatus|=DLC_ANALIZE_RUNNING;
    return TRUE;
}

void msMWEColorAnalizeAdj(U8 ColorReg_A, U8 ColorReg_B)
{
    U8 u8Bank;

    u8Bank = MDrv_ReadByte(BK_SELECT_00);

    MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
    MDrv_WriteByte(L_BK_VIP(0x10), ColorReg_A);//[7:0]
    MDrv_WriteByte(H_BK_VIP(0x28), ColorReg_B);//[15:8]

    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}

void msMWEBorderAnalizeAdj(U8 ColorReg_A)
{
    U8 u8Bank;

    u8Bank = MDrv_ReadByte(BK_SELECT_00);

    MDrv_WriteByte(BK_SELECT_00, REG_BANK_VPS);
    MDrv_WriteByte(H_BK_VPS(0x13), ColorReg_A);//BIT[13:8]

    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}

void msMWEColorBrightAdj(msMWEColorFieldType ucColorIdx,BOOL DecInc)
{
    U8 u8Bank;
	#if (MS_BOARD_TYPE_SEL==BD_MST087E_D01A_HX)
	U32 u8Reg;
	#else
	U16 u8Reg;
	#endif
    switch(ucColorIdx)
    {
        default:
        case MWE_FIELD_RED:
            u8Reg = L_BK_VIP(0x41);
            break;
        case MWE_FIELD_GREEN:
            u8Reg = H_BK_VIP(0x41);
            break;
        case MWE_FIELD_BLUE:
            u8Reg = L_BK_VIP(0x42);
            break;
        case MWE_FIELD_CYAN:
            u8Reg = H_BK_VIP(0x42);
            break;
        case MWE_FIELD_PURPLE:
            u8Reg = L_BK_VIP(0x43);
            break;
        case MWE_FIELD_YELLOW:
            u8Reg = H_BK_VIP(0x43);
            break;
        case MWE_FIELD_SKIN:
            u8Reg = L_BK_VIP(0x44);
            break;
    }
    u8Bank = MDrv_ReadByte(BK_SELECT_00);
    MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
    //ucRegData = MDrv_ReadByte(u8Reg);
    if(DecInc) // +
        MDrv_WriteByte(u8Reg, 0x00);//[5:0]
    else
        MDrv_WriteByte(u8Reg, 0x3F);//[5:0]
    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}

void msMWEColorSaturationAdj(msMWEColorFieldType ucColorIdx,BOOL DecInc)
{
    U8 u8Bank;
	#if (MS_BOARD_TYPE_SEL==BD_MST087E_D01A_HX)
	U32 u8Reg;
	#else
	U16 u8Reg;
	#endif

    switch(ucColorIdx)
    {
        default:
        case MWE_FIELD_RED:
            u8Reg = L_BK_VIP(0x31);
            break;
        case MWE_FIELD_GREEN:
            u8Reg = H_BK_VIP(0x31);
            break;
        case MWE_FIELD_BLUE:
            u8Reg = L_BK_VIP(0x32);
            break;
        case MWE_FIELD_CYAN:
            u8Reg = H_BK_VIP(0x32);
            break;
        case MWE_FIELD_PURPLE:
            u8Reg = L_BK_VIP(0x33);
            break;
        case MWE_FIELD_YELLOW:
            u8Reg = H_BK_VIP(0x33);
            break;
        case MWE_FIELD_SKIN:
            u8Reg = L_BK_VIP(0x34);
            break;
    }
    u8Bank = MDrv_ReadByte(BK_SELECT_00);
    MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
    //ucRegData = MDrv_ReadByte(u8Reg);
    if(DecInc) // +
        MDrv_WriteByte(u8Reg, 0x00);//[3:0]
    else
        MDrv_WriteByte(u8Reg, 0x0F);//[3:0]
    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}

void msMweAnalizeColorStep(BYTE ucStep ) //Step range: 0~12
{
    U16 /*ColorReg_A,*/ ColorReg_B;
    //printf("color step = %bu\n\n",ucStep);

    if (ucStep == 0xff)//recover
    {
        msMWEColorAnalizeAdj(g_RegData_Bak1, g_RegData_Bak2);
	 return;
    }
    if (ucStep == 0)//start
    {
        U8 u8Bank;
        u8Bank = MDrv_ReadByte(BK_SELECT_00);
        MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
        g_RegData_Bak1 = MDrv_ReadByte(L_BK_VIP(0x10));//[7:0]
        g_RegData_Bak2 = MDrv_ReadByte(H_BK_VIP(0x28));//[15:8]
        MDrv_WriteByte(BK_SELECT_00, u8Bank);
    }
    //ColorReg_A = 0xff;
    ColorReg_B = 0xff & ucStep;

    msMWEColorAnalizeAdj(0xff, ColorReg_B);
    return;

}

void msMweAnalizeBorderStep(BYTE ucStep) //Step range: 0~6
{
    U16 ColorReg_A;
    U8 u8Bank;

    //printf("border step = %bu\n\n",ucStep);

    if (ucStep == 0)//start
    {
        u8Bank = MDrv_ReadByte(BK_SELECT_00);
        MDrv_WriteByte(BK_SELECT_00, REG_BANK_VPS);
        MDrv_WriteByteMask(L_BK_VPS(0x10), BIT2, BIT2);
        g_RegData_Bak1 = MDrv_ReadByte(H_BK_VPS(0x13));//BIT[13:8]
        MDrv_WriteByte(BK_SELECT_00, u8Bank);
      	MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(0) );

    }

    ColorReg_A = 0x3F*(WORD)ucStep/6;

    msMWEBorderAnalizeAdj(ColorReg_A);

    if (ucStep == 6)//recover
    {
        MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(ST_PICTURE.u8Saturation) );
        u8Bank = MDrv_ReadByte(BK_SELECT_00);
		MDrv_WriteByte(BK_SELECT_00, REG_BANK_VPS);
        MDrv_WriteByteMask(L_BK_VPS(0x10), 0, BIT2);
        MDrv_WriteByte(BK_SELECT_00, u8Bank);
        msMWEBorderAnalizeAdj(g_RegData_Bak1);
    }

}
void msMweAnalizeBrightStep(BYTE ucStep) //Step range: 0~3
{
    U8 u8Bank,SubWinSignalState;
    U8 ucBK14_9F;

    //printf("Scene step = %bu\n\n",ucStep);
    u8Bank = MDrv_ReadByte(BK_SELECT_00);

    switch(ucStep)
    {
        case 0://BAK reg data
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_DLC);
            g_RegData_Bak1 = MDrv_ReadByte(H_BK_DLC(0x10));
            g_RegData_Bak2 = MDrv_ReadByte(L_BK_DLC(0x10));
            g_RegData_Bak3 = MDrv_ReadByte(L_BK_DLC(0x0F));   // Y Level
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VOP);
            g_RegData_Bak4 = MDrv_ReadByte(L_BK_VOP(0x17));//R brit
            g_RegData_Bak5 = MDrv_ReadByte(H_BK_VOP(0x17));//G brit
            g_RegData_Bak6 = MDrv_ReadByte(L_BK_VOP(0x18));//B brit
            break;
        case 1:
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_DLC);
            MDrv_WriteByte(H_BK_DLC(0x10), 0xF0);
            MDrv_WriteByte(L_BK_DLC(0x10), 0x7F);
            MDrv_WriteByte(L_BK_DLC(0x0F), 0xFF);   // Y Level
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VOP);
            MDrv_WriteByte(L_BK_VOP(0x17), 0x80);   // BCR
            MDrv_WriteByte(H_BK_VOP(0x17), 0x80);   // BCG
            MDrv_WriteByte(L_BK_VOP(0x18), 0x80);   // BCB
      		MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(0) );
             break;
        case 2:
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_DLC);
            SubWinSignalState = MDrv_ReadByte(L_BK_DLC(0x0B));
        //    printf("\r\n BK14_28 = %x", SubWinSignalState);
            if(SubWinSignalState > 0x58)
            {
                ucBK14_9F = MDrv_ReadByte(L_BK_DLC(0x0F));
                if(ucBK14_9F > 0x80)
                    MDrv_WriteByte(L_BK_DLC(0x0F), ucBK14_9F-1);
                else
                {
                    MDrv_WriteByte(BK_SELECT_00, REG_BANK_VOP);
                    MDrv_WriteByte(L_BK_VOP(0x17), 0x80-(SubWinSignalState-58)); // Bank 0
                    MDrv_WriteByte(H_BK_VOP(0x17), 0x80-(SubWinSignalState-58)); // Bank 0
                    MDrv_WriteByte(L_BK_VOP(0x18), 0x80-(SubWinSignalState-58)); // Bank 0

                }
                //msAdjustBrightness(SUB_WINDOW, 0x80-(SubWinSignalState-58) );
            }
            else if(SubWinSignalState == 0x58)
            {
                break;
            }
            else
            {
                ucBK14_9F = MDrv_ReadByte(L_BK_DLC(0x0F));
                if(ucBK14_9F >= 80)
                    MDrv_WriteByte(L_BK_DLC(0x0F), 0x00); // Bank E
                else
                    MDrv_WriteByte(L_BK_DLC(0x0F), ucBK14_9F +1); // Bank E
            }
            break;

         default://recover Regist data
         {
            MApi_XC_ACE_PicSetSaturation(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW),  msAPI_Mode_PictureSaturationN100toReallyValue(ST_PICTURE.u8Saturation) );

            MApp_XC_PQ_Set_Brightness(MAIN_WINDOW, TRUE);

            MDrv_WriteByte(BK_SELECT_00, REG_BANK_DLC);
            MDrv_WriteByte(H_BK_DLC(0x10), g_RegData_Bak1);
            MDrv_WriteByte(L_BK_DLC(0x10), g_RegData_Bak2);
            MDrv_WriteByte(L_BK_DLC(0x0F), g_RegData_Bak3);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VOP);
            MDrv_WriteByte(L_BK_VOP(0x17), g_RegData_Bak4);   // BCR
            MDrv_WriteByte(H_BK_VOP(0x17), g_RegData_Bak5);   // BCG
            MDrv_WriteByte(L_BK_VOP(0x17), g_RegData_Bak6);   // BCB
            break;
         }
    }

    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}
void msMweAnalizeColorFieldStep(BYTE ucStep )
{
    U8 u8Bank;

    if(g_stMWEAnSts.bCnt %10 && g_stMWEAnSts.bCnt>2) return;

    //printf("field step = %bu\n\n",ucStep);
    u8Bank = MDrv_ReadByte(BK_SELECT_00);

    switch(ucStep)
    {
        case 0://BAK reg data
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            g_RegData_Bak1 = MDrv_ReadByte(L_BK_VIP(0x41));
            g_RegData_Bak2 = MDrv_ReadByte(H_BK_VIP(0x41));
            g_RegData_Bak3 = MDrv_ReadByte(L_BK_VIP(0x42));
            g_RegData_Bak4 = MDrv_ReadByte(H_BK_VIP(0x42));
            g_RegData_Bak5 = MDrv_ReadByte(L_BK_VIP(0x43));
            g_RegData_Bak6 = MDrv_ReadByte(H_BK_VIP(0x43));
            g_RegData_Bak7 = MDrv_ReadByte(L_BK_VIP(0x44));

            g_RegData_Bak8 = MDrv_ReadByte(L_BK_VIP(0x31));
            g_RegData_Bak9 = MDrv_ReadByte(H_BK_VIP(0x31));
            g_RegData_Bak10 = MDrv_ReadByte(L_BK_VIP(0x32));
            g_RegData_Bak11 = MDrv_ReadByte(H_BK_VIP(0x32));
            g_RegData_Bak12 = MDrv_ReadByte(L_BK_VIP(0x33));
            g_RegData_Bak13 = MDrv_ReadByte(H_BK_VIP(0x33));
            g_RegData_Bak14 = MDrv_ReadByte(L_BK_VIP(0x34));
            break;

        case 1:
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x41), 0x00);//[5:0]
            MDrv_WriteByte(H_BK_VIP(0x41), 0x00);//[5:0]
            MDrv_WriteByte(L_BK_VIP(0x42), 0x00);//[5:0]
            MDrv_WriteByte(H_BK_VIP(0x42), 0x00);//[5:0]
            MDrv_WriteByte(L_BK_VIP(0x43), 0x00);//[5:0]
            MDrv_WriteByte(H_BK_VIP(0x43), 0x00);//[5:0]
            MDrv_WriteByte(L_BK_VIP(0x44), 0x00);//[5:0]

            MDrv_WriteByte(L_BK_VIP(0x31), 0x00);//[3:0]
            MDrv_WriteByte(H_BK_VIP(0x31), 0x00);//[3:0]
            MDrv_WriteByte(L_BK_VIP(0x32), 0x00);//[3:0]
            MDrv_WriteByte(H_BK_VIP(0x32), 0x00);//[3:0]
            MDrv_WriteByte(L_BK_VIP(0x33), 0x00);//[3:0]
            MDrv_WriteByte(H_BK_VIP(0x33), 0x00);//[3:0]
            MDrv_WriteByte(L_BK_VIP(0x34), 0x00);//[3:0]
            break;
        case 2://red
            msMWEColorBrightAdj(MWE_FIELD_RED, TRUE);
            break;
        case 3://red
            msMWEColorBrightAdj(MWE_FIELD_RED, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x41), g_RegData_Bak1);//[5:0]
            break;
        case 4://red
            msMWEColorSaturationAdj(MWE_FIELD_RED, TRUE);
            break;
        case 5://red
            msMWEColorSaturationAdj(MWE_FIELD_RED, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x31), g_RegData_Bak8);//[3:0]
            break;

        case 6://green
            msMWEColorBrightAdj(MWE_FIELD_GREEN, TRUE);
            break;
        case 7://green
            msMWEColorBrightAdj(MWE_FIELD_GREEN, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(H_BK_VIP(0x41), g_RegData_Bak2);//[5:0]
            break;
        case 8://green
            msMWEColorSaturationAdj(MWE_FIELD_GREEN, TRUE);
            break;
        case 9://green
            msMWEColorSaturationAdj(MWE_FIELD_GREEN, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(H_BK_VIP(0x31), g_RegData_Bak9);//[3:0]
            break;

        case 10://blue
            msMWEColorBrightAdj(MWE_FIELD_BLUE, TRUE);
            break;
        case 11://blue
            msMWEColorBrightAdj(MWE_FIELD_BLUE, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x42), g_RegData_Bak3);//[5:0]
            break;
        case 12://blue
            msMWEColorSaturationAdj(MWE_FIELD_BLUE, TRUE);
            break;
        case 13://blue
            msMWEColorSaturationAdj(MWE_FIELD_BLUE, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x32), g_RegData_Bak10);//[3:0]
            break;

        case 14://cyan
            msMWEColorBrightAdj(MWE_FIELD_CYAN, TRUE);
            break;
        case 15://cyan
            msMWEColorBrightAdj(MWE_FIELD_CYAN, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(H_BK_VIP(0x42), g_RegData_Bak4);//[5:0]
            break;
        case 16://cyan
            msMWEColorSaturationAdj(MWE_FIELD_CYAN, TRUE);
            break;
        case 17://cyan
            msMWEColorSaturationAdj(MWE_FIELD_CYAN, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(H_BK_VIP(0x32), g_RegData_Bak11);//[3:0]
            break;

        case 18://purple
            msMWEColorBrightAdj(MWE_FIELD_PURPLE, TRUE);
            break;
        case 19://purple
            msMWEColorBrightAdj(MWE_FIELD_PURPLE, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x43), g_RegData_Bak5);//[5:0]
            break;
        case 20://purple
            msMWEColorSaturationAdj(MWE_FIELD_PURPLE, TRUE);
            break;
        case 21://purple
            msMWEColorSaturationAdj(MWE_FIELD_PURPLE, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x33), g_RegData_Bak12);//[3:0]
            break;

        case 22://yellow
            msMWEColorBrightAdj(MWE_FIELD_YELLOW, TRUE);
            break;
        case 23://yellow
            msMWEColorBrightAdj(MWE_FIELD_YELLOW, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(H_BK_VIP(0x43), g_RegData_Bak6);//[5:0]
            break;
        case 24://yellow
            msMWEColorSaturationAdj(MWE_FIELD_YELLOW, TRUE);
            break;
        case 25://yellow
            msMWEColorSaturationAdj(MWE_FIELD_YELLOW, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(H_BK_VIP(0x33), g_RegData_Bak13);//[3:0]
            break;

        case 26://skin
            msMWEColorBrightAdj(MWE_FIELD_SKIN, TRUE);
            break;
        case 27://skin
            msMWEColorBrightAdj(MWE_FIELD_SKIN, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x44), g_RegData_Bak7);//[5:0]
            break;
        case 28://skin
            msMWEColorSaturationAdj(MWE_FIELD_SKIN, TRUE);
            break;
        case 29://skin
            msMWEColorSaturationAdj(MWE_FIELD_SKIN, FALSE);
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x34), g_RegData_Bak14);//[3:0]
            break;

         default://recover Regist data
            MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP);
            MDrv_WriteByte(L_BK_VIP(0x41), g_RegData_Bak1);//[5:0]
            MDrv_WriteByte(H_BK_VIP(0x41), g_RegData_Bak2);//[5:0]
            MDrv_WriteByte(L_BK_VIP(0x42), g_RegData_Bak3);//[5:0]
            MDrv_WriteByte(H_BK_VIP(0x42), g_RegData_Bak4);//[5:0]
            MDrv_WriteByte(L_BK_VIP(0x43), g_RegData_Bak5);//[5:0]
            MDrv_WriteByte(H_BK_VIP(0x43), g_RegData_Bak6);//[5:0]
            MDrv_WriteByte(L_BK_VIP(0x44), g_RegData_Bak7);//[5:0]

            MDrv_WriteByte(L_BK_VIP(0x31), g_RegData_Bak8);//[3:0]
            MDrv_WriteByte(H_BK_VIP(0x31), g_RegData_Bak9);//[3:0]
            MDrv_WriteByte(L_BK_VIP(0x32), g_RegData_Bak10);//[3:0]
            MDrv_WriteByte(H_BK_VIP(0x32), g_RegData_Bak11);//[3:0]
            MDrv_WriteByte(L_BK_VIP(0x33), g_RegData_Bak12);//[3:0]
            MDrv_WriteByte(H_BK_VIP(0x33), g_RegData_Bak13);//[3:0]
            MDrv_WriteByte(L_BK_VIP(0x34), g_RegData_Bak14);//[3:0]
            break;
    }
    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}
void MApp_UiMenuFunc_MWEForceReturn(void) //.wuchao 20080623
{
    g_stMWEAnSts.bStepCnt=14;
    switch ( g_stMWEAnSts.bAnalizeSts)
    {
        case MWE_ANALIZE_COLOR:
		//hansen bug fix
		//g_stMWEAnSts.bAnalizeSts= MWE_ANALIZE_FINISH;
		// g_stMWEAnSts.bColorAn= TYPE_MWE_AN_OFF;
		msMweAnalizeColorStep( 0xff );
		g_stMWEAnSts.bColorAn=TYPE_MWE_AN_OK;
		//if (g_u8MenuPageIndex == MENU_MWE_ANALIZE)
			//MApp_UiMenu_DrawSpecificComponent1(UI_MWE_ANALIZE_START_X, UI_MWE_ANALIZE_ITEM_START_Y(0),DrawMWEColorAnalize,EN_CPSTATE_SELECT);
		break;
        case MWE_ANALIZE_BORDER:
		//g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_FINISH;
		//g_stMWEAnSts.bBorderAn= TYPE_MWE_AN_OFF;
		msMweAnalizeBorderStep( 6);
		g_stMWEAnSts.bBorderAn=TYPE_MWE_AN_OK;
		//if (g_u8MenuPageIndex == MENU_MWE_ANALIZE)
		//MApp_UiMenu_DrawSpecificComponent1(UI_MWE_ANALIZE_START_X, UI_MWE_ANALIZE_ITEM_START_Y(1),DrawMWEBorderAnalize,EN_CPSTATE_SELECT);
              break;
        case MWE_ANALIZE_BRIGHT:
		//g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_FINISH;
		//g_stMWEAnSts.bSceneAn= TYPE_MWE_AN_OFF;
		msMweAnalizeBrightStep( 3 );
		g_stMWEAnSts.bSceneAn= TYPE_MWE_AN_OK;
		//if (g_u8MenuPageIndex == MENU_MWE_ANALIZE)
			//MApp_UiMenu_DrawSpecificComponent1(UI_MWE_ANALIZE_START_X, UI_MWE_ANALIZE_ITEM_START_Y(2),DrawMWEScencAnalize,EN_CPSTATE_SELECT);
              break;
        case MWE_ANALIZE_COLORFIELD:
		//g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_FINISH;
		//g_stMWEAnSts.bFeildAn= TYPE_MWE_AN_OFF;
		msMweAnalizeColorFieldStep( 30 );
		g_stMWEAnSts.bFeildAn= TYPE_MWE_AN_OK;
		//if (g_u8MenuPageIndex == MENU_MWE_ANALIZE)
			//MApp_UiMenu_DrawSpecificComponent1(UI_MWE_ANALIZE_START_X, UI_MWE_ANALIZE_ITEM_START_Y(3),DrawMWEFieldAnalize,EN_CPSTATE_SELECT);
		break;
         default:
              break;
    }

	g_stMWEAnSts.bCnt = 0;
	g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_NONE;
	msAPI_ACE_MWEFuncSel(MWE_MODE_OFF);
	g_wColorEngineDemoStatus&= (~DLC_ANALIZE_RUNNING);

}


BOOL MApp_GetMweAnalizeStatus(void)
{
	if(g_wColorEngineDemoStatus&DLC_ANALIZE_RUNNING)
		return TRUE;
	else
		return FALSE;

}
void MAppMweAnalizeHandle(void)
{
    static DWORD  m_dwMweAnalizeTimer;
    if ( msAPI_ACE_MWEStatus() != MWE_H_SPLIT )
        return;

    if(msAPI_Timer_DiffTimeFromNow(m_dwMweAnalizeTimer) < g_stMWEAnSts.bStepCnt)
    {
        return;
    }

    m_dwMweAnalizeTimer = msAPI_Timer_GetTime0();

     g_stMWEAnSts.bCnt++;
    switch ( g_stMWEAnSts.bAnalizeSts)
    {
        case MWE_ANALIZE_COLOR:
	    switch(g_stMWEAnSts.bCnt)
	    {
	    	case 1:
                	msMweAnalizeColorStep( 0 );
		       break;
	    	case 50:
                	msMweAnalizeColorStep(BIT0);
		       break;
	    	case 100:
                	msMweAnalizeColorStep( BIT1 );
		       break;
	    	case 150:
                	msMweAnalizeColorStep( BIT2 );
		       break;
	    	case 200:
                	msMweAnalizeColorStep( BIT3 );
		       break;
	    	case 250:
                	msMweAnalizeColorStep( BIT4 );
		       break;
	    	case 300:
                	msMweAnalizeColorStep( BIT5);
		       break;
	    	case 350:
                	msMweAnalizeColorStep( BIT6 );
		       break;
	    	case 400:
                	msMweAnalizeColorStep( BIT7 );
		       break;
	    	case ANALIZE_COLOR_END_CNT:
                	msMweAnalizeColorStep( 0xff );
		       break;
		default:
			break;
	    }

            if ( g_stMWEAnSts.bCnt > (ANALIZE_COLOR_END_CNT+5) )
            {
		   		g_stMWEAnSts.bAnalizeSts= MWE_ANALIZE_FINISH;
            }
            break;

        case MWE_ANALIZE_BORDER:
	     switch( g_stMWEAnSts.bCnt)
	     	{
	     		case 1:
                		msMweAnalizeBorderStep(0);
				break;
	     		case 50:
                		msMweAnalizeBorderStep(1);
				break;
	     		case 100:
                		msMweAnalizeBorderStep(2);
				break;
	     		case 150:
                		msMweAnalizeBorderStep(3);
				break;
	     		case 250:
                		msMweAnalizeBorderStep(4);
				break;
	     		case 400:
                		msMweAnalizeBorderStep(5);
				break;
	     		case ANALIZE_BOADER_END_CNT:
                		msMweAnalizeBorderStep( 6);
				break;
			default:
				break;
	     	}
            if ( g_stMWEAnSts.bCnt >= (ANALIZE_BOADER_END_CNT+5) )
            {
		   		g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_FINISH;
            }
            break;

        case MWE_ANALIZE_BRIGHT:
            if ( g_stMWEAnSts.bCnt < 2 )
                 msMweAnalizeBrightStep( 0 );
            else if ( g_stMWEAnSts.bCnt ==10 )
                 msMweAnalizeBrightStep( 1 );
            else if ( g_stMWEAnSts.bCnt >= 12 && g_stMWEAnSts.bCnt < 200 )
                msMweAnalizeBrightStep( 2 );
            else if ( g_stMWEAnSts.bCnt == ANALIZE_SCENE_END_CNT)
                 msMweAnalizeBrightStep( 3 );

            if ( g_stMWEAnSts.bCnt > (ANALIZE_SCENE_END_CNT+5) )
            {
		   		g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_FINISH;
            }
            break;

        case MWE_ANALIZE_COLORFIELD:
            switch(g_stMWEAnSts.bCnt)
            {
            		case 1:
                	       msMweAnalizeColorFieldStep( 0 );
				break;
            		case 10:
                	       msMweAnalizeColorFieldStep( 1 );
				break;
            		case 20:
                	       msMweAnalizeColorFieldStep( 2 );
				break;
            		case 30:
                	       msMweAnalizeColorFieldStep( 3 );
				break;
            		case 40:
                	       msMweAnalizeColorFieldStep( 4 );
				break;
            		case 50:
                	       msMweAnalizeColorFieldStep( 5 );
				break;
            		case 60:
                	       msMweAnalizeColorFieldStep( 6 );
				break;
            		case 70:
                	       msMweAnalizeColorFieldStep( 7 );
				break;
            		case 80:
                	       msMweAnalizeColorFieldStep( 8 );
				break;
            		case 90:
                	       msMweAnalizeColorFieldStep( 9 );
				break;
            		case 100:
                	       msMweAnalizeColorFieldStep( 10 );
				break;
            		case 110:
                	       msMweAnalizeColorFieldStep( 11 );
				break;
            		case 120:
                	       msMweAnalizeColorFieldStep( 12 );
				break;
            		case 130:
                	       msMweAnalizeColorFieldStep( 13 );
				break;
            		case 140:
                	       msMweAnalizeColorFieldStep( 14 );
				break;
            		case 150:
                	       msMweAnalizeColorFieldStep( 15 );
				break;
            		case 160:
                	       msMweAnalizeColorFieldStep( 16 );
				break;
            		case 170:
                	       msMweAnalizeColorFieldStep( 17 );
				break;
            		case 180:
                	       msMweAnalizeColorFieldStep( 18 );
				break;
            		case 190:
                	       msMweAnalizeColorFieldStep( 19 );
				break;
            		case 200:
                	       msMweAnalizeColorFieldStep( 20 );
				break;
            		case 210:
                	       msMweAnalizeColorFieldStep( 21 );
				break;
            		case 220:
                	       msMweAnalizeColorFieldStep( 22 );
				break;
            		case 230:
                	       msMweAnalizeColorFieldStep( 23 );
				break;
            		case 240:
                	       msMweAnalizeColorFieldStep( 24 );
				break;
            		case 250:
                	       msMweAnalizeColorFieldStep( 25 );
				break;
            		case 260:
                	       msMweAnalizeColorFieldStep( 26 );
				break;
            		case 270:
                	       msMweAnalizeColorFieldStep( 27 );
				break;
            		case 280:
                	       msMweAnalizeColorFieldStep( 28 );
				break;
            		case 290:
                	       msMweAnalizeColorFieldStep( 29 );
				break;
            		case ANALIZE_FEILD_END_CNT:
                	       msMweAnalizeColorFieldStep( 30 );
				break;
			default:
				break;
            }
            if ( g_stMWEAnSts.bCnt > (ANALIZE_FEILD_END_CNT+5) )
            {
		   g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_FINISH;
            }
            break;

        case MWE_ANALIZE_FINISH:

		   	if(g_stMWEAnSts.bColorAn==TYPE_MWE_AN_ING)
         	{
                 	g_stMWEAnSts.bColorAn=TYPE_MWE_AN_OK;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_COLOR_SELTEXT);
			}
		   if(	g_stMWEAnSts.bBorderAn== TYPE_MWE_AN_ING)
		   {
		   		g_stMWEAnSts.bBorderAn=TYPE_MWE_AN_OK;
				MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_BORDER_SELTEXT);
		   }
		   if(g_stMWEAnSts.bSceneAn== TYPE_MWE_AN_ING)
		   {
		   		g_stMWEAnSts.bSceneAn= TYPE_MWE_AN_OK;
				MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_SCEN_SELTEXT);
		   }
		   if(g_stMWEAnSts.bFeildAn==TYPE_MWE_AN_ING)
		   {
		   		g_stMWEAnSts.bFeildAn= TYPE_MWE_AN_OK;
				MApp_ZUI_API_InvalidateWindow(HWND_MENU_COLOR_DEMO_FILED_SELTEXT);
		   }
		g_stMWEAnSts.bCnt = 0;
		g_stMWEAnSts.bAnalizeSts = MWE_ANALIZE_NONE;
		msAPI_ACE_MWEFuncSel(MWE_MODE_OFF);
		//u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
	case MWE_ANALIZE_NONE:
        default:
			return;
            break;
    }
    //printf("n=%d..",g_stMWEAnSts.bCnt);

}
#endif

//---------------------------------------------------------------------------------------------------------------
MS_U16 MApp_GetHistogramWaveValue(U16 u16temp)
{
    MS_U16 WValue;
	MS_U16 g_wLumaHistogram32H[32];
    MS_U8 DLCIndex = u16temp/2;//32 step
	XC_DLC_ApiStatus DLC_Status;
	MApi_XC_DLC_GetStatus_Ex(&DLC_Status,MAIN_WINDOW);
	memcpy(g_wLumaHistogram32H,DLC_Status.DLCluma.g_wLumaHistogram32H,sizeof(g_wLumaHistogram32H));
    if(DLCIndex==31)
    {
         WValue = g_wLumaHistogram32H[DLCIndex] ;
    }
    else
    {
        if (g_wLumaHistogram32H[DLCIndex+1]>g_wLumaHistogram32H[DLCIndex])
            WValue = g_wLumaHistogram32H[DLCIndex] + (((g_wLumaHistogram32H[DLCIndex+1]-g_wLumaHistogram32H[DLCIndex])/2)*(u16temp%2)) ;
        else
            WValue = g_wLumaHistogram32H[DLCIndex] - (((g_wLumaHistogram32H[DLCIndex]-g_wLumaHistogram32H[DLCIndex+1])/2)*(u16temp%2)) ;
    }
    if(WValue>0xFFF)
        WValue = 0xFFF;
    else
        WValue += 0x10-1;

    return WValue;
}


void MApp_UiMenu_InitHistogramWave(void)
{
	MS_U16 i=0;
	for(i=0;i<UI_HISTOGRAM_BLOCK_STEP;i++)
		wWaveValue[i]=0x00;
 	wWaveIndex=0;

}

void MApp_UiMenu_HistogramWaveCommand(BOOL flags)
{
	if(flags)
	{
		U8 i=0;
		for(i=0;i<UI_HISTOGRAM_BLOCK_STEP;i++)
		{
			wWaveValue[i]=MApp_GetHistogramWaveValue(i);//init histogramvalue
		}
		g_wColorEngineDemoStatus|=DLC_HISTOGRAM_RUNNING;
	}
	else
	{
		g_wColorEngineDemoStatus&= (~DLC_HISTOGRAM_RUNNING);
	}

}

BOOL MApp_UiMenu_GetHistogramWaveStatus(void)
{
	if(g_wColorEngineDemoStatus&DLC_HISTOGRAM_RUNNING)
		return TRUE;
	else
		return FALSE;
}

void MApp_UiMenu_DrawHistogramWave(void)
{
    MS_U16 u16Value;

    if (++wWaveIndex >= UI_HISTOGRAM_BLOCK_STEP)
	{
        wWaveIndex = 0;
   		MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_RESET_AUTO_CLOSE_TIMER);//for osd auto close
	}

    u16Value = MApp_GetHistogramWaveValue(wWaveIndex);
    if (wWaveValue[wWaveIndex] == u16Value)
        return;
    else
        wWaveValue[wWaveIndex] = u16Value;

	if(MApp_ZUI_API_GetFocus()==(HWND_MENU_DLC_HISTOGRAM_DEMO))
	{
		MApp_ZUI_API_InvalidateWindow(HWND_MENU_DLC_HISTOGTAM_BG);
	}
}

//-----------------------------------------------------------------------
void MApp_InitColorEngineDemo(void)
{
	MApp_UiMenu_InitHistogramWave();
	MApp_UiMenuFunc_MWEAnalizeInit();
	#if(MWE_FUNCTION)
	MDrv_MWE_Init();
	#endif
	g_wColorEngineDemoStatus=0x0000;

}

void MApp_ColorEngineHandler(void)
{
	if(MApp_UiMenu_GetHistogramWaveStatus())
	{
		MApp_UiMenu_DrawHistogramWave();
	}

	if(MApp_GetMweAnalizeStatus())
	{
		MAppMweAnalizeHandle();
	}
    #if (MWE_FUNCTION  )
    if (msAPI_ACE_MWEStatus())
	{
		msAPI_ACE_MWEHandle();
	}
	#endif



}
//-ZUI_Function_define----------------------------------------------------
S32 _MApp_ZUI_CTL_ColorDemo_SliderBarPaint(HWND hwnd, PMSG pMsg)
{
    static const DRAW_BITMAP _ZUI_TBLSEG DrawScanProgressButtomBar =
    {
         //BMPHANDLE handle;
         E_BMP_BMP_VSLIDE_BAR_M_NONE, //U16 u16BitmapIndex;
         TRUE, //BOOLEAN bSrcColorKey;
         0xFF00FF, //OSD_COLOR srcColorKeyFrom;
         0xFF00FF, //OSD_COLOR srcColorKeyEnd;
         255, //U8 u8Constant_Alpha;
     };

    static const DRAW_BITMAP _ZUI_TBLSEG DrawScanProgressTopBar =
    {
         //BMPHANDLE handle;
         E_BMP_BMP_VSLIDE_BAR_M_FULL, //U16 u16BitmapIndex;
         TRUE, //BOOLEAN bSrcColorKey;
         0xFF00FF, //OSD_COLOR srcColorKeyFrom;
         0xFF00FF, //OSD_COLOR srcColorKeyEnd;
         255, //U8 u8Constant_Alpha;
     };

    switch(pMsg->message)
    {
        case MSG_PAINT:
        {
            const PAINT_PARAM * param = (const PAINT_PARAM*)pMsg->wParam;
            RECT rect;
            U8 i;//location_value,
            U16 value;
            DRAW_BITMAP * pDraw_BitMap = (DRAW_BITMAP*)_ZUI_MALLOC(sizeof(DRAW_BITMAP));

            for(i=0;i<UI_HISTOGRAM_BLOCK_STEP;i++)
            {
                rect = *(param->rect);
                rect.left+=(rect.width+rect.width/4)*i;//draw wWaveIndex HistogramWave
                if(pDraw_BitMap)
                {
                    //if(param->bIsFocus)
                    {
                        memcpy(pDraw_BitMap, &DrawScanProgressButtomBar, sizeof(DRAW_BITMAP));//&DrawSliderBottomProgressBar, sizeof(DRAW_BITMAP));
                        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, pDraw_BitMap, &param->dc, &rect);//CP_NO_SCALER_BITMAP
                    }
                }
                else
                {
                    __ASSERT(0);
                    return FALSE;
                }
                value =wWaveValue[i]/0x10;// MApp_ZUI_ACT_GetDynamicValue(hwnd);
                value=(value*100)/0x100;//linenear from 255 to 100

                rect.top+=(U32)(rect.height *(100-value)/ 100);
                rect.height = (U32)(rect.height * value / 100);

                if(value)
                {
                    if(pDraw_BitMap)
                    {
                        //if(param->bIsFocus)
                        {
                            memcpy(pDraw_BitMap, &DrawScanProgressTopBar, sizeof(DRAW_BITMAP));//&DrawSliderBottomProgressBar, sizeof(DRAW_BITMAP));
                            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, pDraw_BitMap, &param->dc, &rect);//CP_NO_SCALER_BITMAP
                        }
                    }
                }
            }
            _ZUI_FREE(pDraw_BitMap);
        }
        return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, pMsg);
}
S32 MApp_ZUI_CTL_ColorDemo_SliderBarWinProc(HWND hwnd, PMSG pMsg)
{
	switch(pMsg->message)
    {
        case MSG_PAINT:
            //draw default at the background...
            //DEFAULTWINPROC(hwnd, pMsg);
            //should be visible: if ((win->dwState & WS_VISIBLE))
            {
                _MApp_ZUI_CTL_ColorDemo_SliderBarPaint(hwnd, pMsg);
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, pMsg);
}
#endif // #if (MWE_FUNCTION == _ENABLE)

#undef _MAPP_COLORENGINEDEMO_C_

