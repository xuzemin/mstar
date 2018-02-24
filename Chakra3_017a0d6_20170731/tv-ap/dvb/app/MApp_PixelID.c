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

#define MAPP_PIXEL_ID_C

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "MsCommon.h"
#include "datatype.h"
#include "Panel.h"
#include "MApp_GlobalVar.h"
#include "msAPI_Timer.h"
#include "apiGOP.h"
#include "MApp_Scaler.h"
#include "MApp_PixelID.h"

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------
#define PIXELID_DBG(x)      //x

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define PIXELID_WIDTH                (g_IPanel.Width())
#define PIXELID_HEIGHT               (g_IPanel.Height())

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static EN_PIXELID_STATE _enPIXELIDState = STATE_PIXELID_IDLE;
static MS_U8 _u8WinId;
static MS_U8 _u8MainFBId;
static MS_U8 _u8GopId = E_GOP_APP;
static MS_BOOL _bPIXELIDInitialized = FALSE;
static MS_U16 u16Temp = 1;
static MS_U32 _u32Addr = 1;

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

void _GFXDraw_Point(SC_INT_SRC eIntNum, void *pParam)
{
    volatile MS_U32 * _pu32addr = (volatile MS_U32 *) pParam;
    U16 u16CurrentBank=0;
    U32 u32Time = 0;
    static U16 _u16LastBank = 0;
    static U32 _u32LastTime = 0;
    U32 U32PixelAddr = 0;

    UNUSED(eIntNum);
    u32Time = MsOS_GetSystemTime();
    if(u32Time - _u32LastTime > 22)
    {
        PIXELID_DBG(printf("-------------Long time: %u\n", u32Time - _u32LastTime);    )
    }
    _u32LastTime = u32Time;
    if(0 == *_pu32addr)
    {
        return;
    }
    U32PixelAddr = _PA2VA(*_pu32addr);
    
    u16CurrentBank = MApi_XC_GetCurrentReadBank(MAIN_WINDOW) & 0x01;
    if(u16CurrentBank == _u16LastBank)
    {
        if(_u16LastBank)
        {
            PIXELID_DBG(printf("-------------L\n");)
        }
        else
        {
            PIXELID_DBG(printf("-------------R\n");)
        }
    }

    if(u16CurrentBank)
    {
          (*((volatile MS_U8*)(U32PixelAddr)))     =  0x01;
          (*((volatile MS_U8*)(U32PixelAddr) + 1)) =  0x00;
          (*((volatile MS_U8*)(U32PixelAddr) + 2)) =  0x00;
          (*((volatile MS_U8*)(U32PixelAddr) + 3)) =  0xFF;

          (*((volatile MS_U8*)(U32PixelAddr) + 4)) =  0xFF;
          (*((volatile MS_U8*)(U32PixelAddr) + 5)) =  0xFF;
          (*((volatile MS_U8*)(U32PixelAddr) + 6)) =  0xFF;
          (*((volatile MS_U8*)(U32PixelAddr) + 7)) =  0xFF;
          MsOS_FlushMemory();
    }
    else
    {
          (*((volatile MS_U8*)(U32PixelAddr)))     =  0xFF;
          (*((volatile MS_U8*)(U32PixelAddr) + 1)) =  0xFF;
          (*((volatile MS_U8*)(U32PixelAddr) + 2)) =  0xFF;
          (*((volatile MS_U8*)(U32PixelAddr) + 3)) =  0xFF;
          
          (*((volatile MS_U8*)(U32PixelAddr) + 4)) =  0x01;
          (*((volatile MS_U8*)(U32PixelAddr) + 5)) =  0x00;
          (*((volatile MS_U8*)(U32PixelAddr) + 6)) =  0x00;
          (*((volatile MS_U8*)(U32PixelAddr) + 7)) =  0xFF;
          MsOS_FlushMemory();
    }

    _u16LastBank = u16CurrentBank;
}

static void _PixelID_Init(void)
{
    GOP_GwinFBAttr stFBattr;
    U8 u8GopBank = 0;
    
    PIXELID_DBG(printf("%d, %d, %d\n", E_GOP_APP, E_GOP_OSD, E_GOP_CAP);)

    u8GopBank = MApi_GOP_GWIN_GetCurrentGOP();

    MApi_GOP_GWIN_SwitchGOP(_u8GopId);
    
    /////////// main framebuffer 1
    _u8WinId = MApi_GOP_GWIN_CreateWin(32, 32, GFX_FMT_ARGB8888);
    PIXELID_DBG(printf("Main Gwin Id = %d\n", _u8WinId));
    
    _u8MainFBId = MApi_GOP_GWIN_GetFBfromGWIN(_u8WinId);
    PIXELID_DBG(printf("Main FB Id = %d\n", _u8MainFBId ));
    
    MApi_GOP_GWIN_GetFBInfo(_u8MainFBId, &stFBattr);
    _u32Addr = stFBattr.addr;

    //printf("%x, %x, %x, %x, %x\n",stFBattr.width, stFBattr.height, stFBattr.dispWidth, stFBattr.dispHeight,stFBattr.size);
    MApi_GFX_ClearFrameBufferByWord(stFBattr.addr, stFBattr.size, 0x00000000);

    //MApi_GOP_Set_PixelID_Addr(_u8MainFBId, _u8WinId, stFBattr.addr);
    //MApi_GOP_Set_GPIO3DPin(BALL_AA10 - 1);//AA10, GPIO147

    ///////// generic setting
    MApi_GOP_GWIN_Set_STRETCHWIN(_u8GopId,E_GOP_DST_OP0, 0, 0, 32, 32);
    MApi_GOP_GWIN_Set_HSCALE(FALSE, 1, 1);
    MApi_GOP_GWIN_Set_VSCALE(FALSE, 1, 1);

    MApi_GOP_GWIN_Enable(_u8WinId, TRUE);
    //MApi_GOP_GWIN_SetBlending(_u8WinId, TRUE, 0x3F);//by-pixel
    MApi_GOP_GWIN_SetBlending(_u8WinId, FALSE, 0x3F);//by-pixel

    MApi_XC_InterruptAttach(SC_INT_VSINT, _GFXDraw_Point, (void *) &_u32Addr);
                
    MApi_GOP_GWIN_SwitchGOP(u8GopBank);
    u16Temp = 1;
    _bPIXELIDInitialized = TRUE;
}

static void _PixelID_Exit(void)
{
    _u32Addr = 0;
    //sent 0 as gwin address, then kernel will skip draw pixel ID
    //MApi_GOP_Set_PixelID_Addr(_u8MainFBId,_u8WinId, 0);
    //MApi_GOP_Set_GPIO3DPin(0);//AA10, GPIO147
    MApi_GOP_GWIN_Enable(_u8WinId, FALSE);
    MApi_XC_InterruptDeAttach(SC_INT_VSINT, _GFXDraw_Point, (void *) &_u32Addr);

    //because _u8MainFBId2 is connected with gwin at this time, so no need to free it.
    MApi_GOP_GWIN_DestroyWin(_u8WinId);
    _bPIXELIDInitialized = FALSE;
}


MS_BOOL MApp_PixelID_IsEnabled(void)
{
    return _bPIXELIDInitialized;
}

void MApp_PixelID_Set(EN_PIXELID_STATE eState)
{
    _enPIXELIDState = eState;
}

void MApp_PixelID(void)
{
    switch(_enPIXELIDState)
    {
        case STATE_PIXELID_INIT:
            PIXELID_DBG(printf("STATE_PIXELID_INIT\n"));
            _PixelID_Init();
            _enPIXELIDState = STATE_PIXELID_IDLE;
            break;

        case STATE_PIXELID_SWITCH:
        {            
            //PIXELID_DBG(printf("STATE_PIXELID_DISPLAY_OSD\n"));
            //MApi_GOP_Switch_GWIN_2_FB(_u8MainFBId,_u8WinId,0,&u16QC);
            MApi_GOP_GWIN_MapFB2Win(_u8MainFBId,_u8WinId);
            u16Temp = u16Temp + 1;
            _enPIXELIDState = STATE_PIXELID_IDLE; // STATE_PIXELID_SCALER_SETWINDOW;

        }break;

        case STATE_PIXELID_SCALER_SETWINDOW:
            break;

        case STATE_PIXELID_EXIT:
            PIXELID_DBG(printf("STATE_PIXELID_EXIT\n"));
            if (_bPIXELIDInitialized)
            {
                _PixelID_Exit();
            }
            _enPIXELIDState = STATE_PIXELID_IDLE;
            break;
        
        case STATE_PIXELID_IDLE:
            //PIXELID_DBG(printf("STATE_PIXELID_IDLE\n"));
            break;
    }
}

