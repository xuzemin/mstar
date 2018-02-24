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

#define MAPP_LOGO_C

///////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include "datatype.h"
#include "Board.h"

#if (DISPLAY_LOGO)
// Common Definition
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiGOP.h"
#include "verJPD.h"

#include "drvCPU.h"
#include "msAPI_CPU.h"

#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "BinInfo.h"

#include "msAPI_Flash.h"

#include "MApp_Logo.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ChannelChange.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_InputSource.h"

#include "mapp_photo.h"
#include "mapp_photo_display.h"
#include "mapp_videoplayer.h"

/////////////////////////////////////////////////////

#define LOGO_DISPLAY_RESOLUTION     DTVRES_704x480_60P

#define LOGO_DBG(x)      //x

#define LOGO_DEC_AND_DISPLAY_BY_NEW_METHOD      1 // Ray, 0219.2013

#if (LOGO_DEC_AND_DISPLAY_BY_NEW_METHOD)
static U8 u8FbId=0xFF, u8GwinId=0xFF;
MS_U32 u32JPDBinSize;
#endif


//**********************************************************
//static U32          g_u32LogoStartTime;         // used for boot logo only
//static U32          g_u32LogoShowDuration_MS;   // used for boot logo only
//static LOGO_INFO    g_BootLogoInfo;
#if (ENABLE_DMP == DISABLE)
U32 handshakeCnt;
#endif
//**********************************************************

#if (LOGO_DEC_AND_DISPLAY_BY_NEW_METHOD)
void gop_stretch(U16 graph_pitch, U16 graph_width, U16 graph_height, MS_BOOL bHorStretch, MS_BOOL bVerStretch)
{
    U32 u32GWinDispX_Max;
    U32 u32GWinDispY_Max;


    u32GWinDispX_Max = devPanel_WIDTH();
    u32GWinDispY_Max = devPanel_HEIGHT();

    if (bHorStretch)
        MApi_GOP_GWIN_Set_HSCALE(TRUE, graph_width, u32GWinDispX_Max);
    if (bVerStretch)
        MApi_GOP_GWIN_Set_VSCALE(TRUE, graph_height, u32GWinDispY_Max);

    MApi_GOP_GWIN_Set_STRETCHWIN(0, E_GOP_DST_OP0, 0, 0, graph_pitch, graph_height);
}

static void BurstYUV422(U16 u16X, U16 u16Y,  U16 u16Width, U16 u16Height, U16 u16Pitch, U32 u32InAddr, U32 u32OutAddr)
{
    //GFX_Config tGFXcfg;
    GFX_BufferInfo src_info, dst_info;
    GFX_DrawRect rect;

    //printf("BurstYUV422, W = %d, H = %d, Pitch = %d, InAdr = 0x%x, OutAdr = 0x%x\n", u16Width, u16Height, u16Pitch, u32InAddr, u32OutAddr);

    //tGFXcfg.bIsCompt = TRUE;
    //tGFXcfg.bIsHK = TRUE;
    GFX_Point gfxPt0 = { 0, 0 };
    GFX_Point gfxPt1 = {(u16Width+15)&0xFFFFF0, u16Height };
    // MApi_GFX_Init(&tGFXcfg);

    src_info.u32Addr = (U32)u32InAddr;
    src_info.u32ColorFmt = GFX_FMT_YUV422;
    src_info.u32Width = u16Width;
    src_info.u32Height = u16Height;
    src_info.u32Pitch = u16Pitch<<1;
    MApi_GFX_SetSrcBufferInfo(&src_info, 0);

    dst_info.u32Addr = u32OutAddr;
    dst_info.u32ColorFmt = GFX_FMT_YUV422;
    dst_info.u32Width = (u16Width+15)&0xFFFFF0;
    dst_info.u32Height = u16Height;
    dst_info.u32Pitch = ((((u16Pitch+15)&0xFFFFF0))<<1);			//unit: byte, I8:1 bytes
    MApi_GFX_SetDstBufferInfo(&dst_info, 0);

    MApi_GFX_SetClip(&gfxPt0, &gfxPt1);

    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_PC, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YUYV);

    rect.srcblk.x = u16X;
    rect.srcblk.y = u16Y;
    rect.srcblk.width = u16Width/*u16Pitch*/;
    rect.srcblk.height = u16Height;

    rect.dstblk.x = u16X;
    rect.dstblk.y = u16Y;
    rect.dstblk.width = (u16Width+15)&0xFFFFF0;;//&~0x10;/*u16Pitch*/;
    rect.dstblk.height = u16Height;

    if( (rect.srcblk.width!= rect.dstblk.width)||(rect.srcblk.height!= rect.dstblk.height) )
    {
        MApi_GFX_BitBlt(&rect, GFXDRAW_FLAG_SCALE);
    }
    else
    {
        MApi_GFX_BitBlt(&rect, 0);
    }
    MApi_GFX_FlushQueue();
}

static void BurstInitGOP(U16 u16X, U16 u16Y, U16 u16Pitch, U16 u16Width, U16 u16Height,
U32 u32GopBuffer, MS_BOOL bHorStretch, MS_BOOL bVerStretch)
{
    U32 u32DispX;
    U32 u32DispY;
    GOP_InitInfo pGopInit;

    u32DispX = u16X;
    u32DispY = u16Y;
    u16Pitch = ((u16Pitch+15)&0xfffff0);
    //MApi_GOP_RegisterFBFmtCB(( MS_U32(*)(MS_U16 pitch,MS_U32 addr , MS_U16 fmt ))OSD_RESOURCE_SetFBFmt);
    //MApi_GOP_RegisterXCIsInterlaceCB(_sc_is_interlace);
    //MApi_GOP_RegisterXCGetCapHStartCB(_sc_get_h_cap_start);
    //MApi_GOP_RegisterXCReduceBWForOSDCB(_Sys_PQ_ReduceBW_ForOSD);
    pGopInit.u16PanelWidth = g_IPanel.Width();
    pGopInit.u16PanelHeight = g_IPanel.Height();
    pGopInit.u16PanelHStr = g_IPanel.HStart();
    pGopInit.u32GOPRBAdr = u32GopBuffer;//((GOP_GWIN_RB_MEMORY_TYPE & MIU1) ? (GOP_GWIN_RB_ADR | MIU_INTERVAL) : (GOP_GWIN_RB_ADR));
    pGopInit.u32GOPRBLen = 0x003F4800;
    pGopInit.u32GOPRegdmaAdr = ((GOP_REGDMABASE_MEMORY_TYPE & MIU1) ? (GOP_REGDMABASE_ADR | MIU_INTERVAL) : (GOP_REGDMABASE_ADR));//GOP_REGDMABASE_ADR;//
    pGopInit.u32GOPRegdmaLen = GOP_REGDMABASE_LEN;
    pGopInit.bEnableVsyncIntFlip = FALSE;

    MApi_GOP_InitByGOP(&pGopInit, 0);
    //MApi_GOP_GWIN_SwitchGOP(0);

    if (bHorStretch||bVerStretch)
        gop_stretch(u16Pitch, u16Width, u16Height, bHorStretch, bVerStretch);

    MApi_GOP_GWIN_SetGOPDst(0, E_GOP_DST_OP0);
    #if (MAZDA_SET_GOPALPHAINVERSE)
    MApi_GOP_GWIN_SetAlphaInverse_EX(0, TRUE);
    #endif

    u8FbId = MApi_GOP_GWIN_GetFreeFBID();
    u8GwinId = MApi_GOP_GWIN_GetFreeWinID();

    if((0xFF == u8FbId) || (0xFF == u8GwinId))
    {
        printf("%s: u8OsdLayerFbId: 0x%x, at %d\n", __func__, u8FbId, __LINE__);
        printf("%s: u8OsdLayerGwinId: 0x%x, at %d\n", __func__, u8GwinId, __LINE__);
        printf("%s: Error: MApi_GOP_GWIN_GetFreeFBID or MApi_GOP_GWIN_GetFreeWinID failed, at %d\n", __func__, __LINE__);
        // TODO: destroy logo
        return;
    }

    MApi_GOP_GWIN_CreateFBbyStaticAddr(u8FbId, u32DispX, u32DispY, u16Pitch, u16Height, E_MS_FMT_YUV422, u32GopBuffer);
    MApi_GOP_GWIN_MapFB2Win(u8FbId, u8GwinId);
    MApi_GOP_GWIN_SetWinDispPosition(u8GwinId, u32DispX, u32DispY);

    MApi_GOP_GWIN_SetBlending(u8GwinId, FALSE, 0x3F);

}
#endif

BOOLEAN _MApp_Logo_LoadJpeg(U16 u16LogoBinID)
{
    BININFO BinInfo;
    BOOLEAN bResult;
    //U32 u32LogoAddr = ((MAD_JPEG_DISPLAY_MEMORY_TYPE & MIU1) ? (MAD_JPEG_DISPLAY_ADR | MIU_INTERVAL) : (MAD_JPEG_DISPLAY_ADR));
    U32 u32LogoAddr = LOGO_SRC_FILE_BUF_ADR;


#if(ENABLE_MPLAYER_CAPTURE_LOGO)
    if(stGenSetting.g_SysSetting.UsrLogo == POWERON_LOGO_USER)
    {
    #if 0//def MSOS_TYPE_LINUX
        if(!_MApp_Logo_LoadJpeg_From_File(u32LogoAddr))
        {
            BinInfo.B_ID = u16LogoBinID;//(U32)BIN_ID_JPEG_BOOT_LOGO;
            MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
            if (bResult != PASS)
            {
                LOGO_DBG( printf( "could not find logo binary on flash.\n" ) );
                return FALSE;
            }
            msAPI_MIU_LoadLogo(BinInfo.B_FAddr, u32LogoAddr, GE_ALIGNED_VALUE(BinInfo.B_Len, 8));
        }
    #else
        BinInfo.B_FAddr = USER_LOGO_FLASH_START_ADDR + stGenSetting.g_SysSetting.u8UsrLogoIdx * USER_LOGO_LENGTH_PER_LOGO;
        BinInfo.B_Len = USER_LOGO_LENGTH_PER_LOGO;

       //msAPI_Flash_ChipSelect(E_FLASH_CHIP_SELECT_1);
       //MDrv_SERFLASH_Init();

        msAPI_Flash_Read(BinInfo.B_FAddr, BinInfo.B_Len, (U8 *)_PA2VA(u32LogoAddr));

       // msAPI_Flash_ChipSelect(E_FLASH_CHIP_SELECT_0);
       // MDrv_SERFLASH_Init();
    #endif
    }
    else
#endif
    {
        BinInfo.B_ID = u16LogoBinID;//(U32)BIN_ID_JPEG_BOOT_LOGO;
        MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);

        if (bResult != PASS)
        {
            LOGO_DBG( printf( "could not find logo binary on flash.\n" ) );
            return FALSE;
        }

        msAPI_MIU_LoadLogo(BinInfo.B_FAddr, u32LogoAddr, GE_ALIGNED_VALUE(BinInfo.B_Len, 8));
    }


#if (LOGO_DEC_AND_DISPLAY_BY_NEW_METHOD)
    u32JPDBinSize = GE_ALIGNED_VALUE(BinInfo.B_Len, 8);
#endif

    return TRUE;
}

BOOLEAN MApp_Logo_Load(void)
{
    BOOLEAN bRet = FALSE;

    if(!_MApp_Logo_LoadJpeg(BIN_ID_JPEG_BOOT_LOGO))
    {
        LOGO_DBG(printf(" msAPI_Logo_LoadJpeg failed\n"));
        return FALSE;
    }

#if (LOGO_DEC_AND_DISPLAY_BY_NEW_METHOD)

    //verJPD_Main(MAD_JPEG_DISPLAY_ADR, u32JPDBinSize);
    verJPD_Main(LOGO_SRC_FILE_BUF_ADR, u32JPDBinSize);

    bRet = TRUE;

#else
    {
        LOGO_DBG(printf("load co-processor code\n"));
    #if( VD_PLAYER_IS_IN_CROP_CPU )
        MApp_VDPlayer_LoadBinToCrop();
    #endif
        msAPI_Timer_Delayms(70);
    }

    MApp_Photo_MemCfg(
            //((MAD_JPEG_DISPLAY_MEMORY_TYPE & MIU1) ? (MAD_JPEG_DISPLAY_ADR | MIU_INTERVAL) : (MAD_JPEG_DISPLAY_ADR)), MAD_JPEG_DISPLAY_LEN,
            LOGO_SRC_FILE_BUF_ADR, LOGO_SRC_FILE_BUF_SIZE,
            ((MAD_JPEG_OUT_MEMORY_TYPE & MIU1) ? (MAD_JPEG_OUT_ADR | MIU_INTERVAL) : (MAD_JPEG_OUT_ADR)), MAD_JPEG_OUT_LEN,
            ((MAD_JPEG_INTERBUFF_MEMORY_TYPE & MIU1) ? (MAD_JPEG_INTERBUFF_ADR | MIU_INTERVAL) : (MAD_JPEG_INTERBUFF_ADR)), MAD_JPEG_INTERBUFF_LEN, PHOTO_MEMPOOL_BUFFER_SIZE);

    if (MApp_Photo_DecodeMemory_Init(FALSE, NULL))
    {
        EN_RET enPhotoRet;
        while ((enPhotoRet = MApp_Photo_Main()) == EXIT_PHOTO_DECODING)
        ;

        if (((enPhotoRet == EXIT_PHOTO_DECODE_DONE) && (MApp_Photo_GetErrCode() == E_PHOTO_ERR_NONE)) || (enPhotoRet == EXIT_PHOTO_DECODE_ONE_FRAME_DONE))
        {
            bRet = TRUE;
        }

    }

#endif
    if (bRet == FALSE)
    {
        LOGO_DBG(printf("logo decode failed\n"));
    }

    return bRet;
}

void MApp_Logo_Display(BOOLEAN bDisplayLogo)
{
#if (LOGO_DEC_AND_DISPLAY_BY_NEW_METHOD)

    if(bDisplayLogo)
    {
        MS_U16 u16X=0, u16Y=0;
        MS_BOOL bHorStretch=0, bVerStretch=0;

        // fill frame buffer to black color
        msAPI_GE_ClearFrameBufferByWord((U32)PHOTO_DISPLAY_BUFFER_ADDR,
               (PHOTO_ADJUSTED_PANEL_WIDTH * PANEL_HEIGHT * 2),
               0x80008000);

        // after clear frame buffer, flush cmd
        MApi_GFX_FlushQueue();

        BurstYUV422(0, 0, JPG_GetAlignmentWidth(), JPG_GetAlignmentHeight(), JPG_GetAlignmentPitch(), JPG_GetOutRawDataAddr(), PHOTO_DISPLAY_BUFFER_ADDR);

        if((g_IPanel.Width() != JPG_GetAlignmentWidth()) || (g_IPanel.Width() != JPG_GetAlignmentPitch()))
        {
            bHorStretch = 1;
            u16X = 0;
        }
        if(g_IPanel.Height() != JPG_GetAlignmentHeight())
        {
            bVerStretch = 1;
            u16Y = 0;
        }

        BurstInitGOP(u16X, u16Y, JPG_GetAlignmentPitch(), JPG_GetAlignmentWidth(), JPG_GetAlignmentHeight(), PHOTO_DISPLAY_BUFFER_ADDR, bHorStretch, bVerStretch);

        MApi_GOP_GWIN_Enable(u8GwinId, TRUE);

    }
    else
    {
        MApi_GOP_GWIN_Enable(u8GwinId, FALSE);
        MApi_GOP_GWIN_DeleteWin(u8GwinId);
        MApi_GOP_GWIN_DeleteFB(u8FbId);
    }

#else

    if (bDisplayLogo)
    {
        MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_DMP, MAIN_WINDOW);
        MApp_Photo_InitFullScreenDisplay();
        MApp_Photo_SlideShow(FALSE);

        if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
        {
            U32 u32WhileEnteredTime = msAPI_Timer_GetTime0();
            while(1)
            {
                if(MApp_Photo_GIFIsDisplayDone())
                {
                    MApp_Photo_GIFResetDisplay();
                    break;
                }
                else{
                    MApp_Photo_GIFDisplay(FALSE);
                    MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
                }
                MApp_Photo_Main();
                if( msAPI_Timer_DiffTimeFromNow(u32WhileEnteredTime) > 10000 )
                {
                    //Time out
                    break;
                }
            }
        }
        else
        {
             MApp_Photo_Display(FALSE);
             MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
        }
        MApp_Photo_Stop();
    }
    else
    {
        MApp_Photo_Display_Stop();
        //restore original input source setting
        MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
        MApp_Photo_SlideShow(TRUE);
    }

#endif
}

#if( ENABLE_DMP && ENABLE_MPLAYER_CAPTURE_LOGO )
BOOLEAN MApp_SaveLogo_EraseFlash(U32 u32FlashStartAddr, U32 u32DataSize)
{
    if (u32DataSize == 0)
    {
        return FALSE;
    }

    msAPI_Flash_AddressErase(u32FlashStartAddr, u32DataSize, TRUE);

    LOGO_DBG(printf("MApp_SaveLogo_EraseFlash OK\n");)

    return TRUE;
}

BOOLEAN MApp_SaveLogo_WriteFlash(U32 u32SrcAddr, U32 u32FlashAddr, U32 u32DataSize)
{
    U32     u32LeftSize;
    U16     u32CopySize;

    u32LeftSize = u32DataSize;
    u32CopySize = XDATA_WIN1_SIZE;

    while (u32LeftSize > 0)
    {
        if (u32LeftSize < XDATA_WIN1_SIZE)
        {
            u32CopySize = u32LeftSize;
        }

        if (!msAPI_Flash_Write(u32FlashAddr, u32CopySize, (U8 *)_PA2VA(u32SrcAddr)))
        {
            LOGO_DBG(printf("MApp_SaveLogo_WriteFlash: Writing error\n"));
            return FALSE;
        }

        u32SrcAddr += u32CopySize;
        u32FlashAddr += u32CopySize;
        u32LeftSize -= u32CopySize;

    }

    LOGO_DBG(printf("MApp_SaveLogo_WriteFlash OK\n");)

    return TRUE;
}
#endif  // EANBLE_DMP

//----------------------------------------------------
#endif  //#if (DISPLAY_LOGO)

#undef MAPP_LOGO_C
