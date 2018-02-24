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

#define _DRV_MWE_C_

#include "Board.h"
#if (MWE_FUNCTION )
#include "MsTypes.h"

#include "drvMWE.h"
#include "apiXC.h"
#include "apiXC_Ace.h"
#include "apiXC_Dlc.h"
#include "apiPNL.h"
#include "msAPI_Timer.h"
#include "Panel.h"

extern void MApp_Scaler_GetWinInfo(XC_SETWIN_INFO* pWindowInfo, SCALER_WIN eWindow);
extern U16 mvideo_sc_get_h_dis_size(void);
extern U16 mvideo_sc_get_h_dis_pos(void);

//===============================================================================
U32 wMWE_Panel_HStart;
U32 wMWE_Panel_VStart;
U32 wMWE_Panel_XOffset;
U32 wMWE_Panel_YOffset;

static U8 bMWE_ReverseXFlag;
static U8 bMWE_ReverseYFlag;

U8 g_ucMWE_Count;
U16 g_u16MWEStep=0;

static MWE_RECT   _MWERect;
static MWE_FUNC  _MWEFunc;
static U32       _MWETimer = 0;
static U32       _MWEFlag;
#define MWE_TIMER           20//60
#define MWE_MOVE_STEP       120
#define MWE_H_STEP      2//6
#define MWE_V_STEP      8


#define MWE_MOVE_RIGHT    	BIT0
#define MWE_MOVE_LEFT     	BIT1

#define MWE_ZOOM_IN       	BIT2

#define _MWE_MOVE_RIGHT     BIT3
#define _MWE_MOVE_DOWN      BIT4

#define IsMWEZoom_IN() (_MWEFlag&MWE_ZOOM_IN)
#define IsMoveRight() (_MWEFlag&_MWE_MOVE_RIGHT)
#define IsMoveDown() (_MWEFlag&_MWE_MOVE_DOWN)

//------------------Regist define --------------------------
#define BANK_CM_MAIN          	REG_BANK_VOP
#define BANK_CM_SUB          	REG_BANK_S_VOP
#define REG_ADDR_CM_MAIN     	L_BK_VOP(0x26)
#define REG_ADDR_CM_SUB       	L_BK_VOP(0x1D)
#define REG_ADDR_CM_CTL_MAIN    L_BK_VOP(0x2F)
#define REG_ADDR_CM_CTL_SUB     L_BK_VOP(0x26)
#define MASK_CM_CTL             (0x37)

//===============================================================================
//===============================================================================
void MDrv_MWE_Refresh(void)
{
    U8 u8Bank;
    u8Bank = MDrv_ReadByte(BK_SELECT_00);
    MDrv_WriteByte(BK_SELECT_00, REG_BANK_S_VOP);

    #if 0
    printf("\n SUB-WIN hs(%u) he(%u) vs(%u) ve(%u)",
    (U16)(wMWE_Panel_HStart+_MWERect.Xpos),
    (U16)(wMWE_Panel_HStart+_MWERect.Xpos+_MWERect.Xsize-1),
    (U16)(wMWE_Panel_VStart+_MWERect.Ypos),
    (U16)(wMWE_Panel_VStart+_MWERect.Ypos+_MWERect.Ysize- 1));
    #endif
    MDrv_Write2Byte(L_BK_S_VOP(0x08), (U16)(wMWE_Panel_HStart+_MWERect.Xpos+_MWERect.Xsize-1)); // sub-window horizontal end
    MDrv_Write2Byte(L_BK_S_VOP(0x07), (U16)(wMWE_Panel_HStart+_MWERect.Xpos)); // sub-window horizontal start

    MDrv_Write2Byte(L_BK_S_VOP(0x09), (U16)(wMWE_Panel_VStart+_MWERect.Ypos)); // sub-window vertical start

    if(_MWERect.Ysize < 6) _MWERect.Ysize = 6;//Fixed mantis:0037395 To avoid the top line garbage issue

    MDrv_Write2Byte(L_BK_S_VOP(0x0a), (U16)(wMWE_Panel_VStart+_MWERect.Ypos+_MWERect.Ysize- 1)); // sub-window vertical end
    MDrv_WriteByte(BK_SELECT_00, u8Bank);

}
void MDrv_MWE_Init(void)
{
	g_u8MWE_Status=MWE_MODE_OFF;
    g_ucDemoTimeCounter = 0;//3
    g_bMWEInit = 1;
    MDrv_MWE_WinOnOff(DISABLE);


}

//===============================================================================
//2006/06/30, for changhong
//When MWE on, copy main quality to MWE
//and set main poor quality.
/*void msMWESetQuality(BYTE ucRegBank)*/
void MDrv_MWE_SetQuality(void)
{
    U8 u8Bank;

    u8Bank = MDrv_ReadByte(BK_SELECT_00);
    // BK19
    MDrv_WriteByte(BK_SELECT_00, 0x19);
    // H-Peak disable
    MDrv_WriteByteMask(0x2F28, 0x00, BIT0);

    // BK18
    MDrv_WriteByte(BK_SELECT_00, 0x18);
    // FCC disable
    MDrv_WriteByte(0x2F22, 0x00);
    MDrv_WriteByteMask(0x2F23, 0x00, BIT0);
    // ICC disable
    MDrv_WriteByteMask(0x2F60, 0x00, BIT2);
    // IBC disable
    MDrv_WriteByteMask(0x2F80, 0x00, BIT6);
    // Y noise masking disable
    MDrv_WriteByteMask(0x2FBA, 0x00, BIT7);
    // C noise masking disable
    MDrv_WriteByteMask(0x2FBB, 0x00, BIT7);
    // IHC disable
    MDrv_WriteByteMask(0x2FC0, 0x00, BIT6);
    // YC-Coring
    MDrv_WriteByte(0x2FB0, 0x00);

    // BK1A
    MDrv_WriteByte(BK_SELECT_00, 0x1A);
    // Y-Adjust
    MDrv_WriteByte(0x2F1F, 0x00);
    // BLE
    MDrv_Write2Byte(0x2F24, 0x8000);
    // WLE
    MDrv_Write2Byte(0x2F26, 0x8000);
    // Y/C gain control
    MDrv_Write2Byte(0x2F2A, 0x4040);

    // BKF
    MDrv_WriteByte(BK_SELECT_00, 0x0F);
    // Gamma
    MDrv_WriteByteMask(0x2F30, 0x00, BIT0);

    // BK9
    MDrv_WriteByte(BK_SELECT_00, 0x09);
    // Poat-Scaling filter
    MDrv_WriteByte(0x2F7A, 0x00);

    // color matrix
    {
        U16 temp, i;
        for(i=0; i<=9;i++)
        {
            MDrv_WriteByte(BK_SELECT_00, BANK_CM_MAIN);
            temp=MDrv_Read2Byte(REG_ADDR_CM_MAIN+(i*2));
            MDrv_WriteByte(BK_SELECT_00, BANK_CM_SUB);
            MDrv_Write2Byte(REG_ADDR_CM_SUB+(i*2), temp);
        }
        MDrv_WriteByte( BK_SELECT_00, BANK_CM_SUB );
        MDrv_WriteByteMask( REG_ADDR_CM_CTL_SUB, 0x35, MASK_CM_CTL ); // Enable color matrix&Change R/B range
    }
    // switch original bank
    MDrv_WriteByte(BK_SELECT_00, u8Bank);

}

void MDrv_MWE_SetMainQuality(void)
{
    U8 u8Bank;

    u8Bank = MDrv_ReadByte(BK_SELECT_00);
    // BK19
    MDrv_WriteByte(BK_SELECT_00, 0x19);
    // H-Peak disable
    MDrv_WriteByteMask(0x2F20, 0x00, BIT0);

    // BK18
    MDrv_WriteByte(BK_SELECT_00, 0x18);
    // FCC disable
    MDrv_WriteByte(0x2F20, 0x00);
    MDrv_WriteByteMask(0x2F21, 0x00, BIT0);
    // ICC disable
    MDrv_WriteByteMask(0x2F60, 0x00, BIT6);
    // IBC disable
    MDrv_WriteByteMask(0x2F80, 0x00, BIT7);
    // Y noise masking disable
    MDrv_WriteByteMask(0x2FAA, 0x00, BIT7);
    // C noise masking disable
    MDrv_WriteByteMask(0x2FAB, 0x00, BIT7);
    // IHC disable
    MDrv_WriteByteMask(0x2FC0, 0x00, BIT7);
    // YC-Coring
    MDrv_WriteByte(0x2FA0, 0x00);

    // BK1A
    MDrv_WriteByte(BK_SELECT_00, 0x1A);
    // Y-Adjust
    MDrv_WriteByte(0x2F1E, 0x00);
    // BLE
    MDrv_Write2Byte(0x2F20, 0x8000);
    // WLE
    MDrv_Write2Byte(0x2F22, 0x8000);
    // Y/C gain control
    MDrv_Write2Byte(0x2F28, 0x4040);

    // BK10
    MDrv_WriteByte(BK_SELECT_00, 0x10);
    // Gamma
    MDrv_WriteByteMask(0x2FA0, 0x00, BIT0);

    // BK7
    MDrv_WriteByte(BK_SELECT_00, 0x07);
    // Poat-Scaling filter
    MDrv_WriteByte(0x2F15, 0x00);

    // switch original bank
    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}

void MDrv_MWE_SetEnhanceQuality(void)
{
    U8 u8Bank;

    u8Bank = MDrv_ReadByte(BK_SELECT_00);

    // BK18
    MDrv_WriteByte(BK_SELECT_00, 0x18);
    MDrv_Write3Byte(0x2F62, 0x0B0B0B);
    MDrv_Write3Byte(0x2F65, 0x0B0B0B);
    MDrv_WriteByte(0x2F68, 0x09);

    // switch original bank
    MDrv_WriteByte(BK_SELECT_00, u8Bank);
}

//===============================================================================
void MDrv_MWE_WindowEnable( MWEType MWEOffOn, PanelSizeType* pMWEPanel )
{
    if (MWEOffOn!=MWE_OFF)
    {
//        PMS_SRC_INFO pSubSrc = &g_SrcInfo[SUB_WINDOW];
//        pSubSrc->InputSourceType = g_SrcInfo[SRC1].InputSourceType ;
//        MDrv_Scaler_ProgInputType(pSubSrc)    ;
        //SetSrc( SRC2, g_SrcInfo[SRC1].InputSrcType );

        wMWE_Panel_HStart = pMWEPanel->wPANEL_HSTART;
        wMWE_Panel_VStart = 0;//pMWEPanel->wPANEL_VSTART;//need always =0
        g_ucMWE_Count = 10;

        if (MWEOffOn==MWE_H_SPLIT)
        {
            //_MWERect.Xsize = pMWEPanel->wPANEL_WIDTH/2;
            _MWERect.Xsize = mvideo_sc_get_h_dis_size()/2;
            _MWERect.Ysize = pMWEPanel->wPANEL_HEIGHT;

#if(MWE_POSITION == MWE_AT_RIGHT)
            //wMWE_Panel_XOffset = pMWEPanel->wPANEL_WIDTH - _MWERect.Xsize;
            wMWE_Panel_XOffset = mvideo_sc_get_h_dis_pos()  + _MWERect.Xsize;
#else
            wMWE_Panel_XOffset =mvideo_sc_get_h_dis_pos();
#endif//(MWE_POSITION == MWE_AT_RIGHT)
            wMWE_Panel_YOffset = pMWEPanel->wPANEL_HEIGHT- _MWERect.Ysize;

            _MWERect.Xpos = wMWE_Panel_XOffset;
            _MWERect.Ypos = 0;
        }
        else if (MWEOffOn==MWE_MOVE)
        {
            _MWERect.Xsize = pMWEPanel->wPANEL_WIDTH/3;
            _MWERect.Ysize = pMWEPanel->wPANEL_HEIGHT/3;

            wMWE_Panel_XOffset = pMWEPanel->wPANEL_WIDTH - _MWERect.Xsize;
            wMWE_Panel_YOffset = pMWEPanel->wPANEL_HEIGHT- _MWERect.Ysize;

            _MWERect.Xpos = 50;
            _MWERect.Ypos = 50;
            bMWE_ReverseYFlag = 1;
            bMWE_ReverseXFlag = 1;
        }
        else if (MWEOffOn==MWE_ZOOM)
        {
            wMWE_Panel_XOffset = pMWEPanel->wPANEL_WIDTH/2;
            wMWE_Panel_YOffset = pMWEPanel->wPANEL_HEIGHT/2;
            _MWERect.Xsize = pMWEPanel->wPANEL_WIDTH/3;
            _MWERect.Ysize = pMWEPanel->wPANEL_HEIGHT/3;

            _MWERect.Xpos = wMWE_Panel_XOffset - _MWERect.Xsize;
            _MWERect.Ypos = wMWE_Panel_YOffset - _MWERect.Ysize;
            bMWE_ReverseYFlag = 1;
            bMWE_ReverseXFlag = 1;
            _MWEFlag |= MWE_ZOOM_IN;

        }

        MDrv_MWE_Refresh();

        //patch..
        //if (MWEOffOn==MWE_H_SPLIT)
        //{
        //    msWriteByte(BK0_00, REG_BANK_MWE);
        //    //msWrite2Bytes(BK3_1E, 0x04);
        //}
    }
#if 0
    MsWriteBit(BK_VOP(0x19),(BOOL)MWEOffOn,BIT4); // enable the sub window frame color enable
#endif
    //g_SrcInfo[SRC2].PCSetting = g_SrcInfo[SRC1].PCSetting;
    //g_SrcInfo[SRC2].VideoSetting =  g_SrcInfo[SRC1].VideoSetting ;
    //g_SrcInfo[SRC2].InputSourceType = g_SrcInfo[SRC1].InputSourceType;
    //g_SrcInfo[SRC2].bColorSpaceYUV = g_SrcInfo[SRC1].bColorSpaceYUV;
    if (g_bMWEInit)
    {
#if 0
        MDrv_Scaler_SetupColor(SRC2);
        //SetupColor(SRC2);
#endif
        //MDrv_MWE_SetQuality();//ucRegBank);//2006/06/30
        g_bMWEInit = 0;
    }

    if (MWEOffOn!=MWE_OFF)
    {
        MDrv_MWE_WinOnOff(ENABLE);
    }
    else
    {

#if 0
        MDrv_Scaler_SetupColor(SRC1);
#endif
        //SetupColor(SRC1); // recover SRC1 quality setting.
        g_bMWEInit = 1;
        MDrv_MWE_WinOnOff(DISABLE);
    }

}

void MDrv_MWE_WinOnOff(BOOLEAN bEnable)
{
#if 0

    if (bEnable)
        MsWriteRegMask(BK_OP1(0x01),1<<7,BIT7); // Sub windowor MWE Window Enable.
    else
        MsWriteRegMask(BK_OP1(0x01),0,BIT7);    // disable MWE function
#else
    U8 u8Bank;

    if((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
    {
       MApi_XC_GenerateBlackVideo(DISABLE, SUB_WINDOW);
    }

    //mdrv_sc_wait_output_vsync(2, 100);
    if(bEnable)
    {
        MDrv_MWE_SetQuality();
    }

    u8Bank = MDrv_ReadByte(BK_SELECT_00);
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_S_VOP);
    //MDrv_WriteRegBit(L_BK_S_VOP(0x06), bEnable, BIT4); // 2nd window Enable
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_OP1);
    //MDrv_WriteRegBit(L_BK_OP1(0x01), bEnable, BIT7);
	MDrv_WriteByte(BK_SELECT_00, REG_BANK_PIP);
    MDrv_WriteRegBit(L_BK_PIP(0x10), bEnable, BIT2);
    MDrv_WriteRegBit(L_BK_PIP(0x10), bEnable, BIT1);

    MDrv_WriteByte(BK_SELECT_00, u8Bank);
#endif

}

//===============================================================================
void MDrv_MWE_FuncSel(U8 ucMWE_Type,PanelSizeType* pMWEPanel)
{
    U8 u8Bank;

//printf("\n PANEL hs(%u) vs(%u) w(%u) h(%u)", mvideo_pnl_get_hstart(), PANEL_VSTART, PANEL_WIDTH, mvideo_pnl_get_height());

    MDrv_MWE_WindowEnable((MWEType)ucMWE_Type, pMWEPanel);

    u8Bank = MDrv_ReadByte(BK_SELECT_00);
    MDrv_WriteByte(BK_SELECT_00, REG_BANK_S_VOP);
    switch(ucMWE_Type)
    {
        case MWE_H_SPLIT:

        	//_MDrv_Scaler_SetPipBorderColor(SUB_WINDOW,0x00); // black
	        MDrv_WriteByte(L_BK_S_VOP(0x17), 0x00); // black , Sub Window Border Color.

        	//MDrv_Scaler_Set_PipBorderSize(SRC2, 0x02, 0x00, 0x00, 0x00);
	        MDrv_WriteByte(L_BK_S_VOP(0x02), 0x02); // left
	        MDrv_WriteByte(L_BK_S_VOP(0x03), 0x00); // right
	        MDrv_WriteByte(L_BK_S_VOP(0x04), 0x00); // top
	        MDrv_WriteByte(L_BK_S_VOP(0x05), 0x00); // bottom

            break;
        case MWE_MOVE:
        case MWE_ZOOM:
        	//_MDrv_Scaler_SetPipBorderColor(SUB_WINDOW,0x07); // blue
	        MDrv_WriteByte(L_BK_S_VOP(0x17), 0x07); // blue , Sub Window Border Color.

        	//MDrv_Scaler_Set_PipBorderSize(SRC2, 0x11, 0x11, 0x11, 0x11);
	        MDrv_WriteByte(L_BK_S_VOP(0x02), 0x11); // left
	        MDrv_WriteByte(L_BK_S_VOP(0x03), 0x11); // right
	        MDrv_WriteByte(L_BK_S_VOP(0x04), 0x11); // top
	        MDrv_WriteByte(L_BK_S_VOP(0x05), 0x11); // bottom
            break;
        case MWE_OFF:
            break;
        default:
            return;
    }
    MDrv_WriteRegBit(L_BK_S_VOP(0x01), 0, BIT0);
    MDrv_WriteByte(BK_SELECT_00, u8Bank);

}


MWE_RECT* MDrv_MWE_GetRect(void)
{
    return &_MWERect;
}
//===============================================================================

//===============================================================================

#if (MWE_FUNCTION )
/******************************************************************************/
/*                     Local                                                  */
/* ****************************************************************************/


U16 mvideo_sc_get_h_dis_size(void)
{
    XC_SETWIN_INFO xc_win;
	MApp_Scaler_GetWinInfo(&xc_win,MAIN_WINDOW);
	return xc_win.stDispWin.width;
}

U16 mvideo_sc_get_h_dis_pos(void)
{
    XC_SETWIN_INFO xc_win;
	MApp_Scaler_GetWinInfo(&xc_win,MAIN_WINDOW);
	return xc_win.stDispWin.x;
}
U16 mvideo_sc_get_v_dis_size(void)
{
    XC_SETWIN_INFO xc_win;
	MApp_Scaler_GetWinInfo(&xc_win,MAIN_WINDOW);
	return xc_win.stDispWin.height;
}

U16 mvideo_sc_get_v_dis_pos(void)
{
    XC_SETWIN_INFO xc_win;
	MApp_Scaler_GetWinInfo(&xc_win,MAIN_WINDOW);
	return xc_win.stDispWin.y;
}

#define MWE_MAX_XPOS    (mvideo_sc_get_h_dis_size()-1 +   MApi_XC_GetPanelSpec(g_PNL_TypeSel)->m_wPanelHStart))
#define MWE_MIN_XPOS    (mvideo_sc_get_h_dis_pos() + MApi_XC_GetPanelSpec(g_PNL_TypeSel)->m_wPanelHStart))
#define MWE_MAX_YPOS    (mvideo_pnl_get_height())
#define MWE_MIN_YPOS    (0)
#define MWE_MAX_XSIZE   (mvideo_sc_get_v_dis_size())
#define MWE_MIN_XSIZE   (0)

static BOOLEAN bMWEStatus=FALSE;

/******************************************************************************/
/*                   Functions                                                */
/******************************************************************************/

void msAPI_ACE_MWElnit( void )
{
    PanelSizeType   mwe_area;
	PanelType *ptype= MApi_XC_GetPanelSpec(g_PNL_TypeSel);
    mwe_area.wPANEL_HSTART =ptype->m_wPanelHStart;
    mwe_area.wPANEL_VSTART = ptype->m_wPanelVStart;
    mwe_area.wPANEL_WIDTH  = ptype->m_wPanelWidth;
    mwe_area.wPANEL_HEIGHT = ptype->m_wPanelHeight;

    MDrv_MWE_Init();
    MDrv_MWE_FuncSel(MWE_H_SPLIT, &mwe_area);
    MDrv_MWE_WinOnOff(FALSE);
    bMWEStatus = FALSE;
}

void msAPI_ACE_EnableMWE(BOOLEAN bEnable)
{
    bMWEStatus = bEnable;
    MDrv_MWE_WinOnOff(bEnable);


}

BOOLEAN msAPI_ACE_MWEStatus(void)
{
    return bMWEStatus;
}

void msAPI_ACE_MWEFuncSel(MWE_FUNC  mwe_func)
{
    MWEType mwe_type;
    PanelSizeType   mwe_area;
	PanelType *ptype= MApi_XC_GetPanelSpec(g_PNL_TypeSel);

    if (mwe_func == MWE_MODE_OFF && _MWEFunc == MWE_MODE_OFF)
    {
        return;
    }

    _MWEFunc = mwe_func;

    switch (_MWEFunc)
    {
    default:
    case MWE_MODE_OFF:
        mwe_type = MWE_OFF;
        break;
    case MWE_MODE_H_SCAN:
    case MWE_MODE_H_SPLIT:
        mwe_type = MWE_H_SPLIT;
        break;
    case MWE_MODE_MOVE:
        mwe_type = MWE_MOVE;
        break;
    case MWE_MODE_ZOOM:
        mwe_type = MWE_ZOOM;

    }


    mwe_area.wPANEL_HSTART =ptype->m_wPanelHStart;
    mwe_area.wPANEL_VSTART = ptype->m_wPanelVStart;
    mwe_area.wPANEL_WIDTH  = ptype->m_wPanelWidth;
    mwe_area.wPANEL_HEIGHT = ptype->m_wPanelHeight;
    bMWEStatus = mwe_type;
    MDrv_MWE_FuncSel(mwe_type, &mwe_area);
}

static void _MWE_H_Scan(void)
{
#if(MWE_POSITION == MWE_AT_RIGHT)
    U32 xpos;
    MWE_RECT *pRect = MDrv_MWE_GetRect();

    xpos  = pRect->Xpos;

 	if(_MWEFlag& MWE_MOVE_RIGHT)
    {
        if( (xpos  + MWE_H_STEP) > (U32)MWE_MAX_XPOS)
        {
            xpos = MWE_MAX_XPOS;
            _MWEFlag &= ~MWE_MOVE_RIGHT;
        }
        else
        {
            xpos += MWE_H_STEP;
        }
    }
    else
    {
        if(xpos > MWE_H_STEP)
        {
            if ( (xpos - MWE_H_STEP) > (U32)MWE_MIN_XPOS)
            {
                xpos -= MWE_H_STEP;
            }
            else
            {
                xpos = MWE_MIN_XPOS;
                _MWEFlag |= MWE_MOVE_RIGHT;
            }
        }
        else
        {
            _MWEFlag |= MWE_MOVE_RIGHT;
        }
    }

    if (xpos > pRect->Xpos)
    {
        pRect->Xsize -= (xpos-pRect->Xpos);
    }
    else
    {
        pRect->Xsize += (pRect->Xpos-xpos);
    }
    pRect->Xpos = xpos;
#else
    U32 xsize;
    MWE_RECT *pRect = MDrv_MWE_GetRect();

    xsize  = pRect->Xsize;

 	if(_MWEFlag& MWE_MOVE_RIGHT)
    {
        if( (xsize  + MWE_H_STEP) > (U32)MWE_MAX_XSIZE)
        {
            xsize = MWE_MAX_XSIZE;
            _MWEFlag &= ~MWE_MOVE_RIGHT;
        }
        else
        {
            xsize += MWE_H_STEP;
        }
    }
    else
    {
        if(xsize > MWE_H_STEP)
        {
            if ( (xsize - MWE_H_STEP) > (U32)MWE_MIN_XSIZE)
            {
                xsize -= MWE_H_STEP;
            }
            else
            {
                xsize = MWE_MIN_XSIZE;
                _MWEFlag |= MWE_MOVE_RIGHT;
            }
        }
        else
        {
            _MWEFlag |= MWE_MOVE_RIGHT;
        }
    }

    pRect->Xsize= xsize;
#endif//(MWE_POSITION == MWE_AT_RIGHT)

    //printf(" HScan %d, %d\n", pRect->Xpos, pRect->Xsize);

}

static void _MWE_MOVE(void)
{
		MWE_RECT *pRect = MDrv_MWE_GetRect();

	    if( IsMoveRight() )
	    {
	        if( (pRect->Xpos + pRect->Xsize + MWE_H_STEP) >mvideo_sc_get_h_dis_size() )
	        {
	            pRect->Xpos = mvideo_sc_get_h_dis_size() -pRect->Xsize;
	            _MWEFlag&= ~_MWE_MOVE_RIGHT;
	        }
	        else
	        {
	            pRect->Xpos += MWE_H_STEP;
	        }
	    }
	    else
	    {
	      //  if( (wMWE_Xpos < MWE_H_STEP) || ((wMWE_Xpos - MWE_H_STEP) < MWE_H_MIN) )
	        if( (pRect->Xpos < MWE_H_STEP) )
	        {
	            pRect->Xpos = 0;
	            _MWEFlag |= _MWE_MOVE_RIGHT;
	        }
	        else
	        {
	            pRect->Xpos -= MWE_H_STEP;
	        }
	    }

	    if( IsMoveDown() )
	    {
	        if ((pRect->Ypos + pRect->Ysize + MWE_V_STEP ) > mvideo_sc_get_v_dis_size() )
	        {
	            pRect->Ypos -= MWE_V_STEP;
	            _MWEFlag &= ~_MWE_MOVE_DOWN;
	        }
	        else
	        {
	            pRect->Ypos += MWE_V_STEP;
	        }
	    }
	    else
	    {
	        if( (pRect->Ypos < MWE_V_STEP) || ((pRect->Ypos - MWE_V_STEP) < 1) )
	        {
	            pRect->Ypos += MWE_V_STEP;
	            _MWEFlag |= _MWE_MOVE_DOWN;
	        }
	        else
	        {
	             pRect->Ypos -= MWE_V_STEP;
	        }
	    }
}

static void _MWE_ZOOM(void)
{
		MWE_RECT *pRect = MDrv_MWE_GetRect();

	    if (IsMWEZoom_IN())
	    {
	        g_u16MWEStep ++;
	        if(( (pRect->Xsize*g_u16MWEStep/MWE_MOVE_STEP) <mvideo_sc_get_h_dis_size() )
		&&( (pRect->Ysize*g_u16MWEStep/MWE_MOVE_STEP) < mvideo_sc_get_v_dis_size()))
	        {
	            pRect->Xsize =mvideo_sc_get_h_dis_size()*g_u16MWEStep/MWE_MOVE_STEP;
	            pRect->Ysize =  mvideo_sc_get_v_dis_size()*g_u16MWEStep/MWE_MOVE_STEP;
	        }
	        else
	        {
	          	pRect->Xsize =mvideo_sc_get_h_dis_size();
	            pRect->Ysize =  mvideo_sc_get_v_dis_size();
	            _MWEFlag &= ~MWE_ZOOM_IN;
	            g_u16MWEStep = MWE_MOVE_STEP;
	        }
	    }
	    else
	    {
	        g_u16MWEStep --;
	        if ((pRect->Xsize  > ( mvideo_sc_get_h_dis_size()/MWE_MOVE_STEP))
		&&(pRect->Ysize  > ( mvideo_sc_get_v_dis_size()/MWE_MOVE_STEP)))
	        {
	            pRect->Xsize = mvideo_sc_get_h_dis_size()*g_u16MWEStep/MWE_MOVE_STEP;
	            pRect->Ysize = mvideo_sc_get_v_dis_size()*g_u16MWEStep/MWE_MOVE_STEP;
	        }
	        else
	        {
	            pRect->Xsize = 2;
	            pRect->Ysize = 2;
	            _MWEFlag |= MWE_ZOOM_IN;
	            g_u16MWEStep = 0;
	        }
	    }
	    pRect->Xpos= wMWE_Panel_XOffset -pRect->Xsize/2;
	    pRect->Ypos = wMWE_Panel_YOffset - pRect->Ysize/2;
}
void msAPI_ACE_MWEHandle( void )
{
    if (_MWEFunc == MWE_MODE_OFF)
        return;

    if (msAPI_Timer_DiffTimeFromNow(_MWETimer) < MWE_TIMER)
        return;

    _MWETimer = msAPI_Timer_GetTime0();

    switch (_MWEFunc)
    {
    case MWE_MODE_MOVE:
		_MWE_MOVE();
		break;
    case MWE_MODE_ZOOM:
		_MWE_ZOOM();
		break;
    case MWE_MODE_H_SCAN:
        _MWE_H_Scan();
        break;
    default:
        return;
    }

    //mvideo_sc_wait_output_vsync(1, 50);
    MApi_XC_WaitOutputVSync(1, 50,MAIN_WINDOW);
    MDrv_MWE_Refresh();


}

#endif

#endif // #if (MWE_FUNCTION == _ENABLE)

#undef _DRV_MWE_C_

