//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and U16ernational treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and U16erest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or U16erest to MStar Software and any
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
#define _APP_HDR_C_
//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include <string.h>
#include "MsCommon.h"
#include "Board.h"
#include "MApp_GlobalSettingSt.h"
#if (ENABLE_HDR)
#include "apiXC.h"
#include "MApp_HDR.h"
#include "drvXC_HDMI_if.h"
#include "msAPI_HDR.h"
#include "MApp_GlobalFunction.h"


BOOLEAN m_bHdrMetadataChanged = FALSE;
BOOLEAN m_bHdrInitialized = FALSE;
BOOLEAN m_bDmaInitialized = FALSE;

SCALER_WIN m_enDstWin = MAIN_WINDOW;

ST_MAPI_HDR_SETTING m_stHdrSettting[MAX_WINDOW] =
{
    {TRUE, TRUE, E_MAPI_XC_HDR_MIDDLE, FALSE, E_MAPI_DOLBY_HDR_MODE_NONE},
    {TRUE, TRUE, E_MAPI_XC_HDR_MIDDLE, FALSE, E_MAPI_DOLBY_HDR_MODE_NONE}
};

BOOLEAN MApp_GetAutoDetectHdrLevel(SCALER_WIN enWin)
{
#if (ENABLE_OPEN_HDR == 1)
    return m_stHdrSettting[enWin].bOpenHdrAutoLevelEnable;
#else
    return FALSE;
#endif
}

BOOLEAN MApp_SetAutoDetectHdrLevel(BOOLEAN bAuto, SCALER_WIN enWin, E_MAPI_XC_HDR_LEVEL enAutoHdrLevel)
{
#if (ENABLE_OPEN_HDR == 1)
    if (enAutoHdrLevel == E_MAPI_XC_HDR_MAX)
    {
        m_bHdrMetadataChanged |= (m_stHdrSettting[enWin].bOpenHdrOn == FALSE);
        m_stHdrSettting[enWin].bOpenHdrOn = TRUE;
    }

    m_bHdrMetadataChanged |= (m_stHdrSettting[enWin].bOpenHdrAutoLevelEnable != bAuto);
    m_stHdrSettting[enWin].bOpenHdrAutoLevelEnable = bAuto;

    if (m_bHdrInitialized == TRUE && m_bHdrMetadataChanged == TRUE)
    {
        return msAPI_RefreshHdrSetting();
    }
    else
    {
        return TRUE;
    }
#else
    return FALSE;
#endif
}

E_MAPI_XC_HDR_LEVEL MApp_GetHdrLevel(SCALER_WIN enWin)
{
#if (ENABLE_OPEN_HDR == 1)
    return m_stHdrSettting[enWin].eOpenHdrManualLevel;
#else
    return E_MAPI_XC_HDR_MAX;
#endif
}

BOOLEAN MApp_IsSupportHdr(void)
{
#if (ENABLE_HDR)
    return TRUE;
#else
    return FALSE;
#endif
}

EN_MAPI_HDR_ERROR_CODE MApp_GetDolbyHdrMode(EN_MAPI_DOLBY_HDR_MODE *peMode, SCALER_WIN enWin)
{
#if (ENABLE_DOLBY_HDR == 1)
    XC_HDR_SUPPORTED_CAPS stCaps;
    stCaps.enHDRType = E_XC_HDR_TYPE_DOLBY;
    stCaps.bSupported = FALSE;
    MApi_XC_GetChipCaps(E_XC_SUPPORT_HDR, (MS_U32*)&stCaps, sizeof(XC_HDR_SUPPORTED_CAPS));

    if (stCaps.bSupported == TRUE)
    {
        (*peMode) = m_stHdrSettting[enWin].eDolbyHdrMode;
        return E_MAPI_HDR_ERROR_SUCCESS;
    }
    else
    {
        return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
    }
#else
    UNUSED(peMode);
    UNUSED(enWin);
    return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
}

EN_MAPI_HDR_ERROR_CODE MApp_SetDolbyHdrMode(EN_MAPI_DOLBY_HDR_MODE eMode, SCALER_WIN enWin)
{
#if (ENABLE_DOLBY_HDR == 1)
    if (enWin != MAIN_WINDOW)
    {
        return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
    }

    XC_HDR_SUPPORTED_CAPS stCaps;
    stCaps.enHDRType = E_XC_HDR_TYPE_DOLBY;
    stCaps.bSupported = FALSE;
    MApi_XC_GetChipCaps(E_XC_SUPPORT_HDR, (MS_U32*)&stCaps, sizeof(XC_HDR_SUPPORTED_CAPS));

    if (stCaps.bSupported == FALSE)
    {
        return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
    }

    if (eMode == m_stHdrSettting[enWin].eDolbyHdrMode)
    {
        // Dolby HDR mode don't change, return success.
        return E_MAPI_HDR_ERROR_SUCCESS;
    }

    // Get Dolby HDR 3D LUT depend on eMode.
    MAPI_DOLBY_HDR_MODE st3dLut;
    st3dLut.eMode = eMode;
    st3dLut.u323dLutSize = 0;
    st3dLut.p3dLut = NULL;

    if (GetHdrSetting(E_MAPI_HDR_DOLBY_MODE_SETTING, &st3dLut, sizeof(MAPI_DOLBY_HDR_MODE)) == FALSE)
    {
        return E_MAPI_HDR_ERROR_UNDEFINED_FAIL;
    }

    st3dLut.p3dLut = (U8*)msAPI_Memory_Allocate(sizeof(U8)*st3dLut.u323dLutSize,BUF_ID_DOLBY_HDR);

    if (GetHdrSetting(E_MAPI_HDR_DOLBY_MODE_SETTING, &st3dLut, sizeof(MAPI_DOLBY_HDR_MODE)) == FALSE)
    {
        if(st3dLut.p3dLut)
        msAPI_Memory_Free(st3dLut.p3dLut, BUF_ID_DOLBY_HDR);
        return E_MAPI_HDR_ERROR_UNDEFINED_FAIL;
    }

    if (m_bDmaInitialized == FALSE)
    {
        //MMapInfo_t *minfo = get_mmap(MMAPInfo::GetInstance()->StrToMMAPID("E_MMAP_ID_XC_DMA"));
        //if (minfo != NULL)
        {
            XC_HDR_DMA_INIT_INFO stDMAInitInfo;
            memset(&stDMAInitInfo, 0, sizeof(XC_HDR_DMA_INIT_INFO));
            //stDMAInitInfo.u32DMAInitInfo_Version = HDR_DMA_INIT_INFO_VERSION;
            stDMAInitInfo.u16DMAInitInfo_Length = sizeof(XC_HDR_DMA_INIT_INFO);
            //stDMAInitInfo.phyBaseAddr = minfo->u32Addr;
            //stDMAInitInfo.u32Size =     minfo->u32Size;
            MApi_XC_HDR_Control(E_XC_HDR_CTRL_INIT_DMA, &stDMAInitInfo);
        }

#ifdef 0//UFO_XC_HDMI_4K2K_DMA
       // minfo = get_mmap(MMAPInfo::GetInstance()->StrToMMAPID("E_MMAP_ID_XC_DMA_HDMI"));
        //if (minfo != NULL)
        {
            XC_HDR_DMA_INIT_INFO stDMAInitInfo;
            memset(&stDMAInitInfo, 0, sizeof(XC_HDR_DMA_INIT_INFO));
            stDMAInitInfo.u32DMAInitInfo_Version = HDR_DMA_INIT_INFO_VERSION;
            stDMAInitInfo.u16DMAInitInfo_Length = sizeof(XC_HDR_DMA_INIT_INFO);
            //stDMAInitInfo.phyBaseAddr = minfo->u32Addr;
            //stDMAInitInfo.u32Size =     minfo->u32Size;
            MApi_XC_HDR_Control(E_XC_HDR_CTRL_INIT_DMA_HDMI, &stDMAInitInfo);
        }
#endif
        m_bDmaInitialized = TRUE;
    }

    // Please implement set Dolby HDR mode by calling utopia function.
    XC_HDR_3DLUT_INFO st3DLutInfo;
    memset(&st3DLutInfo, 0, sizeof(XC_HDR_3DLUT_INFO));
    //st3DLutInfo.u323DLutInfo_Version = HDR_3DLUT_INFO_VERSION;
    st3DLutInfo.u163DLutInfo_Length = sizeof(XC_HDR_3DLUT_INFO);
    st3DLutInfo.pu8Data = st3dLut.p3dLut;
    st3DLutInfo.u32Size = st3dLut.u323dLutSize;
    MApi_XC_HDR_Control(E_XC_HDR_CTRL_SET_3DLUT, &st3DLutInfo);

    m_stHdrSettting[enWin].eDolbyHdrMode = eMode;

    XC_CFD_OSD_CONTROL stCfdOsd;
    memset(&stCfdOsd, 0, sizeof(XC_CFD_OSD_CONTROL));

    //stCfdOsd.u32Version = CFD_OSD_VERSION;
    stCfdOsd.u16Length = sizeof(XC_CFD_OSD_CONTROL);

    stCfdOsd.u8Win = enWin;
    stCfdOsd.bViewModeValid = TRUE;
    switch (eMode)
    {
        case E_MAPI_DOLBY_HDR_MODE_VIVID:
        {
            stCfdOsd.u8ViewMode = 2;
            break;
        }
        case E_MAPI_DOLBY_HDR_MODE_BRIGHTNESS:
        {
            stCfdOsd.u8ViewMode = 1;
            break;
        }
        case E_MAPI_DOLBY_HDR_MODE_DARK:
        {
            stCfdOsd.u8ViewMode = 0;
            break;
        }
        default:
        {
            if(st3dLut.p3dLut)
            msAPI_Memory_Free(st3dLut.p3dLut, BUF_ID_DOLBY_HDR);
            return E_MAPI_HDR_ERROR_UNDEFINED_FAIL;
        }
    }

    XC_CFD_CONTROL_INFO stCfdCtrl;
    memset(&stCfdCtrl, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrl.enCtrlType = E_XC_CFD_CTRL_TYPE_OSD;
    stCfdCtrl.pParam = &stCfdOsd;
    stCfdCtrl.u32ParamLen = sizeof(XC_CFD_OSD_CONTROL);

    if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrl) != E_APIXC_RET_OK)
    {
        if(st3dLut.p3dLut)
        msAPI_Memory_Free(st3dLut.p3dLut, BUF_ID_DOLBY_HDR);
        return E_MAPI_HDR_ERROR_UNDEFINED_FAIL;
    }
    if(st3dLut.p3dLut)
    msAPI_Memory_Free(st3dLut.p3dLut, BUF_ID_DOLBY_HDR);

    return E_MAPI_HDR_ERROR_SUCCESS;
#else
    UNUSED(eMode);
    UNUSED(enWin);
    return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
}

BOOLEAN MApp_IsDolbyHdrVideo(void)
{
#if (ENABLE_DOLBY_HDR == 1)
    BOOLEAN bHdrVideo = FALSE;

    XC_HDR_SUPPORTED_CAPS stCaps;
    stCaps.enHDRType = E_XC_HDR_TYPE_DOLBY;
    stCaps.bSupported = FALSE;
    MApi_XC_GetChipCaps(E_XC_SUPPORT_HDR, (MS_U32*)&stCaps, sizeof(XC_HDR_SUPPORTED_CAPS));

    if (stCaps.bSupported == TRUE)
    {
        XC_CFD_STATUS stCfdStatus;
        memset(&stCfdStatus, 0, sizeof(XC_CFD_STATUS));
        //stCfdStatus.u32Version = CFD_STATUS_VERSION;
        stCfdStatus.u16Length = sizeof(XC_CFD_STATUS);
        stCfdStatus.u8Win = (U8)m_enDstWin;


        XC_CFD_CONTROL_INFO stCfdCtrlInfo;
        memset(&stCfdCtrlInfo, 0, sizeof(XC_CFD_CONTROL_INFO));
        stCfdCtrlInfo.enCtrlType = E_XC_CFD_CTRL_TYPE_STATUS;
        stCfdCtrlInfo.pParam = &stCfdStatus;
        stCfdCtrlInfo.u32ParamLen = sizeof(XC_CFD_STATUS);

        if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrlInfo) == E_APIXC_RET_OK)
        {
            if (stCfdStatus.u8VideoHdrType == E_XC_CFD_HDR_TYPE_DOLBY)
            {
                bHdrVideo |= TRUE;
            }
        }
    }

    return bHdrVideo;
#else
    return FALSE;
#endif
}


BOOLEAN MApp_InitHdrAttributes(EN_MAPI_HDR_ATTRIBUTES enAttribueType, SCALER_WIN enWin, void *pAttributes, U16 u16AttributesSize)
{
#if (ENABLE_HDR)
    BOOLEAN bRet = FALSE;
    switch (enAttribueType)
    {
        case EN_MAPI_HDR_ONOFF_ATTRIBUTES:
            if (u16AttributesSize == sizeof(BOOLEAN))
            {
                BOOLEAN *pbOn = (BOOLEAN*)pAttributes;
                m_stHdrSettting[enWin].bOpenHdrOn = (*pbOn);
                bRet = TRUE;
            }
            break;
        case EN_MAPI_HDR_LEVEL_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_HDR_LEVEL_ATTRIBUTES))
            {
                ST_MAPI_HDR_LEVEL_ATTRIBUTES *pLevelAttributs = (ST_MAPI_HDR_LEVEL_ATTRIBUTES*)pAttributes;
                m_stHdrSettting[enWin].bOpenHdrAutoLevelEnable = pLevelAttributs->bAuto;
                m_stHdrSettting[enWin].eOpenHdrManualLevel = (E_MAPI_XC_HDR_LEVEL)pLevelAttributs->u8Level;
                bRet = TRUE;
            }
            break;
        case EN_MAPI_HDR_DOLBY_MODE_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES))
            {
                ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES *p3DLutAttributes = (ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES*)pAttributes;
                p3DLutAttributes->eResult = MApp_SetDolbyHdrMode((EN_MAPI_DOLBY_HDR_MODE)p3DLutAttributes->u8Mode, enWin);
                bRet = (p3DLutAttributes->eResult==E_MAPI_HDR_ERROR_SUCCESS)?TRUE:FALSE;
            }
            break;
        case EN_MAPI_HDR_DOLBY_SETTING_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_HDR_SETTING_ATTRIBUTES))
            {
                ST_MAPI_HDR_SETTING_ATTRIBUTES *pSetting = (ST_MAPI_HDR_SETTING_ATTRIBUTES*)pAttributes;
                m_stHdrSettting[enWin].bDolbyHdrOn = pSetting->bHdrOn;
                pSetting->eResult = MApp_SetDolbyHdrMode((EN_MAPI_DOLBY_HDR_MODE)pSetting->stMode.u8Mode, enWin);
                bRet = (pSetting->eResult==E_MAPI_HDR_ERROR_SUCCESS)?TRUE:FALSE;
            }
            break;
        default:
            break;
    };

    return bRet;
#else
    return FALSE;
#endif
}

BOOLEAN MApp_IsOpenHdrVideo(void)
{
#if (ENABLE_OPEN_HDR == 1)
    BOOLEAN bHdrVideo = FALSE;
#if 1//defined(UFO_XC_HDR_VERSION) && (UFO_XC_HDR_VERSION == 2)
    XC_CFD_STATUS stCfdStatus;
    memset(&stCfdStatus, 0, sizeof(XC_CFD_STATUS));
    //stCfdStatus.u32Version = CFD_STATUS_VERSION;
    stCfdStatus.u16Length = sizeof(XC_CFD_STATUS);
    stCfdStatus.u8Win = (U8)m_enDstWin;

    XC_CFD_CONTROL_INFO stCfdCtrlInfo;
    memset(&stCfdCtrlInfo, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrlInfo.enCtrlType = E_XC_CFD_CTRL_TYPE_STATUS;
    stCfdCtrlInfo.pParam = &stCfdStatus;
    stCfdCtrlInfo.u32ParamLen = sizeof(XC_CFD_STATUS);

    if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrlInfo) == E_APIXC_RET_OK)
    {
        if (stCfdStatus.u8VideoHdrType == E_XC_CFD_HDR_TYPE_OPEN)
        {
            bHdrVideo |= TRUE;
        }
    }
#else
    if ((m_HdrMetadata.u16HDRMetadataType & HDR_METATYPE_MPEG_VUI) &&
        (m_HdrMetadata.stHdrMetadataMpegVUI.u8ColorPrimaries == 9 && m_HdrMetadata.stHdrMetadataMpegVUI.u8TransferCharacteristics == 16 && m_HdrMetadata.stHdrMetadataMpegVUI.u8MatrixCoefficients == 9))
    {
        bHdrVideo |= TRUE;
    }

    if ((m_HdrMetadata.u16HDRMetadataType & HDR_METATYPE_MPEG_VUI) &&
        (m_HdrMetadata.stHdrMetadataMpegVUI.u8ColorPrimaries == 9 && m_HdrMetadata.stHdrMetadataMpegVUI.u8TransferCharacteristics == 14 && m_HdrMetadata.stHdrMetadataMpegVUI.u8MatrixCoefficients == 9))
    {
        bHdrVideo |= TRUE;
    }

    //Currently, only support SDR and ST2084, 0:SDR gamma, 1:HDR gamma, 2:SMPTE ST2084, 3:Future EOTF
    if ((m_HdrMetadata.u16HDRMetadataType & HDR_METADATA_HDMI_INFOFRAME) && (m_HdrMetadata.stHdrMetadataHdmiInfoframe.u8EOTF == 2))
    {
        bHdrVideo |= TRUE;
    }
#endif

    return bHdrVideo;
#else
    return FALSE;
#endif
}

BOOLEAN MApp_IsHlgHdrVideo(void)
{
#if (ENABLE_OPEN_HDR == 1)
    BOOLEAN bHdrVideo = FALSE;
#if 1//defined(UFO_XC_HDR_VERSION) && (UFO_XC_HDR_VERSION == 2)
    XC_CFD_STATUS stCfdStatus;
    memset(&stCfdStatus, 0, sizeof(XC_CFD_STATUS));
    //stCfdStatus.u32Version = CFD_STATUS_VERSION;
    stCfdStatus.u16Length = sizeof(XC_CFD_STATUS);
    stCfdStatus.u8Win = (U8)m_enDstWin;

    XC_CFD_CONTROL_INFO stCfdCtrlInfo;
    memset(&stCfdCtrlInfo, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrlInfo.enCtrlType = E_XC_CFD_CTRL_TYPE_STATUS;
    stCfdCtrlInfo.pParam = &stCfdStatus;
    stCfdCtrlInfo.u32ParamLen = sizeof(XC_CFD_STATUS);

    if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrlInfo) == E_APIXC_RET_OK)
    {
        if (stCfdStatus.u8VideoHdrType == E_XC_CFD_HDR_TYPE_HLG)
        {
            bHdrVideo |= TRUE;
        }
    }
#else
    if ((m_HdrMetadata.u16HDRMetadataType & HDR_METATYPE_MPEG_VUI) &&
        (m_HdrMetadata.stHdrMetadataMpegVUI.u8ColorPrimaries == 9 && m_HdrMetadata.stHdrMetadataMpegVUI.u8TransferCharacteristics == 18 && m_HdrMetadata.stHdrMetadataMpegVUI.u8MatrixCoefficients == 9))
    {
        bHdrVideo |= TRUE;
    }

    //Currently, only support SDR and ST2084, 0:SDR gamma, 1:HDR gamma, 2:SMPTE ST2084, 3:Future EOTF
    if ((m_HdrMetadata.u16HDRMetadataType & HDR_METADATA_HDMI_INFOFRAME) && (m_HdrMetadata.stHdrMetadataHdmiInfoframe.u8EOTF == 3))
    {
        bHdrVideo |= TRUE;
    }
#endif

    return bHdrVideo;
#else
    return FALSE;
#endif
}

BOOLEAN MApp_IsHdrWorking(void)
{
#if (ENABLE_HDR)
#if 1//defined(UFO_XC_HDR_VERSION) && (UFO_XC_HDR_VERSION == 2)
    // Maserati / Maxim /Macan ... use CFD HDR flow.
    XC_CFD_STATUS stCfdStatus;
    memset(&stCfdStatus, 0, sizeof(XC_CFD_STATUS));
    //stCfdStatus.u32Version = CFD_STATUS_VERSION;
    stCfdStatus.u16Length = sizeof(XC_CFD_STATUS);
    stCfdStatus.u8Win = (U8)m_enDstWin;

    XC_CFD_CONTROL_INFO stCfdCtrlInfo;
    memset(&stCfdCtrlInfo, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrlInfo.enCtrlType = E_XC_CFD_CTRL_TYPE_STATUS;
    stCfdCtrlInfo.pParam = &stCfdStatus;
    stCfdCtrlInfo.u32ParamLen = sizeof(XC_CFD_STATUS);

    if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrlInfo) == E_APIXC_RET_OK)
    {
        return stCfdStatus.bIsHdrRunning;
    }

    return FALSE;
#else
    // Monaco / Muji / Monet / Manhattan use old HDR flow.
    return m_bHdrHwWorking;
#endif
#else
    // Not support HDR.
    return FALSE;
#endif

}

BOOLEAN MApp_GetHdrOnOff(void)
{
#if (ENABLE_OPEN_HDR == 1)
    return m_stHdrSettting[m_enDstWin].bOpenHdrOn;
#else
    return FALSE;
#endif
}

BOOLEAN MApp_GetDolbyHdrOnOff(void)
{
#if (ENABLE_DOLBY_HDR == 1)
    return m_stHdrSettting[m_enDstWin].bDolbyHdrOn;
#else
    return FALSE;
#endif
}

BOOLEAN MApp_SetHdrLevel(E_MAPI_XC_HDR_LEVEL enHdrLevel, SCALER_WIN enWin)
{
#if (ENABLE_OPEN_HDR== 1)
    m_bHdrMetadataChanged |= (m_stHdrSettting[enWin].bOpenHdrOn == FALSE);
    m_bHdrMetadataChanged |= (m_stHdrSettting[enWin].bOpenHdrAutoLevelEnable == TRUE);
    m_bHdrMetadataChanged |= (m_stHdrSettting[enWin].eOpenHdrManualLevel != enHdrLevel);

    m_stHdrSettting[enWin].bOpenHdrOn = TRUE;
    m_stHdrSettting[enWin].bOpenHdrAutoLevelEnable = FALSE;
    m_stHdrSettting[enWin].eOpenHdrManualLevel = enHdrLevel;

    if (m_bHdrInitialized == TRUE && m_bHdrMetadataChanged == TRUE)
    {
        return msAPI_RefreshHdrSetting();
    }
    else
    {
        return TRUE;
    }
#else
    return FALSE;
#endif
}


//================== Porting from SN Systeminfo.cpp ==========================//

static MAPI_XC_HDR_LEVEL_ATTRIBUTES m_stHdrLevelAttributes[E_MAPI_XC_HDR_MAX];
static MAPI_XC_HDR_LEVEL_ATTRIBUTES m_stHlgLevelAttributes[E_MAPI_XC_HDR_MAX];
#if (ENABLE_DOLBY_HDR)
static ST_MAPI_DOLBY_HDR_GLOBAL_DIMMING_ATTRIBUTES m_stDolbyGlobalDimmingAttributes;
#endif
MAPI_OPEN_HDR_TONE_MAPPING m_stOpenHdrToneMapping[E_MAPI_XC_HDR_MAX];
MAPI_HDR_CUSTOMER_DLC m_4KHdrCustomerDlc;
MAPI_HDR_CUSTOMER_DLC m_2KHdrCustomerDlc;
MAPI_TIMING_GAMMA_TABLE_MAPPING m_4KHdrCustomerGammaTable;
MAPI_TIMING_GAMMA_TABLE_MAPPING m_2KHdrCustomerGammaTable;


BOOLEAN MApp_GetHdrSetting(E_MAPI_HDR_SETTING eType, void *pSetting, U16 u16SettingSize)
{
    BOOLEAN bRet = FALSE;
    switch (eType)
    {
        case E_MAPI_HDR_CUSTOMER_DLC_SETTING:
            if (u16SettingSize == sizeof(MAPI_HDR_CUSTOMER_DLC))
            {
                MAPI_HDR_CUSTOMER_DLC *pDlc = (MAPI_HDR_CUSTOMER_DLC*)pSetting;
                bRet = MApp_GetHdrCustomerDlcSetting(pDlc);
            }
            break;
        case E_MAPI_HDR_CUSTOMER_GAMMA_TABLE_SETTING:
            if (u16SettingSize == sizeof(MAPI_TIMING_GAMMA_TABLE_MAPPING))
            {
                MAPI_TIMING_GAMMA_TABLE_MAPPING *pGammaTable = (MAPI_TIMING_GAMMA_TABLE_MAPPING*)pSetting;
                bRet = MApp_GetHdrCustomerGammaTableSetting(pGammaTable);
            }
            break;
        case E_MAPI_HDR_CUSTOMER_COLOR_PRIMARIES_SETTING:
            if (u16SettingSize == sizeof(MAPI_HDR_CUSTOMER_COLOR_PRIMARIES))
            {
            #if 0//TODO
                MAPI_HDR_CUSTOMER_COLOR_PRIMARIES *pCustomerColorPrimaries = (MAPI_HDR_CUSTOMER_COLOR_PRIMARIES*)pSetting;
                const PanelInfo_t* const pPanelInfo = GetActivePanel();
                pCustomerColorPrimaries->bCustomerEnable = pPanelInfo->stCfdAttribute.bCustomerColorPrimaries;
                pCustomerColorPrimaries->u16sWx = pPanelInfo->stCfdAttribute.u16SourceWx;
                pCustomerColorPrimaries->u16sWy = pPanelInfo->stCfdAttribute.u16SourceWy;
            #endif
                bRet = TRUE;
            }
            break;
        case E_MAPI_HDR_OPEN_TONE_MAPPING_SETTING:
            if (u16SettingSize == sizeof(MAPI_OPEN_HDR_TONE_MAPPING))
            {
                MAPI_OPEN_HDR_TONE_MAPPING *pToneMappingSetting = (MAPI_OPEN_HDR_TONE_MAPPING*)pSetting;
                memcpy(pToneMappingSetting, &m_stOpenHdrToneMapping[pToneMappingSetting->eLevel], sizeof(MAPI_OPEN_HDR_TONE_MAPPING));
                bRet = TRUE;
            }
            break;

#if (ENABLE_DOLBY_HDR)  //TODO
        case E_MAPI_HDR_DEFAULT_DOLBY_MODE_SETTING:
            if (u16SettingSize == sizeof(EN_MAPI_DOLBY_HDR_MODE))
            {
                EN_MAPI_DOLBY_HDR_MODE *pDefaultMode = (EN_MAPI_DOLBY_HDR_MODE*)pSetting;

                std::map<EN_MAPI_DOLBY_HDR_MODE, MAPI_DOLBY_HDR_MODE>::iterator iter = m_DolbyHdrModeMap.begin();
                if (iter != m_DolbyHdrModeMap.end())
                {
                    (*pDefaultMode) = iter->second.eMode;
                    bRet = TRUE;
                }
            }
            break;
        case E_MAPI_HDR_DOLBY_MODE_SETTING:
            if (u16SettingSize == sizeof(MAPI_DOLBY_HDR_MODE))
            {
                MAPI_DOLBY_HDR_MODE *pDolbyHdrMode = (MAPI_DOLBY_HDR_MODE*)pSetting;

                std::map<EN_MAPI_DOLBY_HDR_MODE, MAPI_DOLBY_HDR_MODE>::iterator iter = m_DolbyHdrModeMap.find(pDolbyHdrMode->eMode);
                if (iter != m_DolbyHdrModeMap.end())
                {
                    if (iter->second.bCheckLoad == FALSE)
                    {
                        // Load specified 3D LUT table.
                        if (LoadDolbyHdr3DLut(pDolbyHdrMode->eMode) == TRUE)
                        {
                            iter = m_DolbyHdrModeMap.find(pDolbyHdrMode->eMode);
                        }
                    }

                    if (iter->second.p3dLut != NULL)
                    {
                        if (pDolbyHdrMode->p3dLut == NULL || pDolbyHdrMode->u323dLutSize == 0)
                        {
                            pDolbyHdrMode->u323dLutSize = iter->second.u323dLutSize;
                            bRet = TRUE;
                        }
                        else
                        {
                            if (pDolbyHdrMode->u323dLutSize < iter->second.u323dLutSize)
                            {
                                pDolbyHdrMode->u323dLutSize = iter->second.u323dLutSize;
                                bRet = FALSE;
                            }
                            else
                            {
                                pDolbyHdrMode->u323dLutSize = iter->second.u323dLutSize;
                                memcpy(pDolbyHdrMode->p3dLut, iter->second.p3dLut, iter->second.u323dLutSize);
                                bRet = TRUE;
                            }
                        }
                    }
                }
            }
            break;
#endif
        default:
            break;
    }

    return bRet;

}


BOOLEAN MApp_GetHdrLevelAttribues(E_MAPI_XC_HDR_LEVEL enHdrLevel, MAPI_XC_HDR_LEVEL_ATTRIBUTES *pAttribues)
{
    if (pAttribues == NULL)
    {
        return FALSE;
    }

    //if (enHdrLevel >= E_MAPI_XC_HDR_LOW && enHdrLevel < E_MAPI_XC_HDR_MAX)
    {
        memcpy(pAttribues, &m_stHdrLevelAttributes[enHdrLevel], sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
        return TRUE;
    }
    return FALSE;
}


BOOLEAN MApp_GetHlgLevelAttributes(E_MAPI_XC_HDR_LEVEL enHlgLevel, MAPI_XC_HDR_LEVEL_ATTRIBUTES *pAttributes)
{
    if (pAttributes == NULL)
    {
        return FALSE;
    }

    //if (enHlgLevel >= E_MAPI_XC_HDR_LOW && enHlgLevel < E_MAPI_XC_HDR_MAX)
    {
        memcpy(pAttributes, &m_stHlgLevelAttributes[enHlgLevel], sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
        return TRUE;
    }

    return FALSE;
}


BOOLEAN MApp_GetHdrCustomerDlcSetting(MAPI_HDR_CUSTOMER_DLC *pstHdrDlc)
{
#if (ENABLE_HDMI_4K_2K)
    if( MDrv_HDMI_Check4K2K() ) // Input timing is 4K
    {
        pstHdrDlc->bFixDlcEnable = m_4KHdrCustomerDlc.bFixDlcEnable;
        memcpy(pstHdrDlc->u8FixDlcCurve, m_4KHdrCustomerDlc.u8FixDlcCurve, sizeof(m_4KHdrCustomerDlc.u8FixDlcCurve));
    }
    else
#endif
    {
        pstHdrDlc->bFixDlcEnable = m_2KHdrCustomerDlc.bFixDlcEnable;
        memcpy(pstHdrDlc->u8FixDlcCurve, m_2KHdrCustomerDlc.u8FixDlcCurve, sizeof(m_2KHdrCustomerDlc.u8FixDlcCurve));
    }
    return TRUE;
}


BOOLEAN MApp_GetHdrCustomerGammaTableSetting(MAPI_TIMING_GAMMA_TABLE_MAPPING *pstHdrGammaTable)
{
#if (ENABLE_HDMI_4K_2K)
    if( MDrv_HDMI_Check4K2K() ) // Input timing is 4K
    {
        pstHdrGammaTable->u8GammaTableIndex = m_4KHdrCustomerGammaTable.u8GammaTableIndex;
    }
    else
#endif
    {
        pstHdrGammaTable->u8GammaTableIndex = m_2KHdrCustomerGammaTable.u8GammaTableIndex;
    }

    return (pstHdrGammaTable->u8GammaTableIndex==0)?FALSE:TRUE;
}


#if 0
BOOLEAN MApp_LoadDolbyHdr3DLut(EN_MAPI_DOLBY_HDR_MODE enMode)
{
    std::map<EN_MAPI_DOLBY_HDR_MODE, MAPI_DOLBY_HDR_MODE>::iterator iter = m_DolbyHdrModeMap.find(enMode);
    if (iter == m_DolbyHdrModeMap.end())
    {
        // Specified Mode doesn't exists.
        return FALSE;
    }

    if (iter->second.p3dLut != NULL)
    {
        // 3D LUT have been load.
        return TRUE;
    }

    if (iter->second.bCheckLoad == TRUE)
    {
        // 3D LUT have been load but load fail.
        return FALSE;
    }

    FILE *p3dLutBin = fopen(iter->second.s3dLutPath.c_str(), "rb");
    if (p3dLutBin == NULL)
    {
        iter->second.bCheckLoad = TRUE;
        return FALSE;
    }

    fseek(p3dLutBin, 0, SEEK_END);
    MAPI_U32 u32Size = ftell(p3dLutBin);
    fseek(p3dLutBin, 0, SEEK_SET);

    iter->second.u323dLutSize = u32Size;
    iter->second.p3dLut = new MAPI_U8[u32Size];
    fread(iter->second.p3dLut , u32Size, 1, p3dLutBin);
    fclose(p3dLutBin);

    iter->second.bCheckLoad = TRUE;
    return TRUE;

}


BOOLEAN MApp_LoadDolbyHdr3DLutPath(dictionary *pHdrIni)
{
    for (MAPI_U8 i = 1 ; i < E_MAPI_DOLBY_HDR_MODE_MAX ; i++)
    {
        char *p3dLutBinFile = iniparser_getstr(pHdrIni, g_DolbyHdr3dLutPath[i]);
        if (p3dLutBinFile != NULL)
        {
            MAPI_DOLBY_HDR_MODE DolbyHdrMode;
            DolbyHdrMode.eMode = (EN_MAPI_DOLBY_HDR_MODE)i;
            DolbyHdrMode.s3dLutPath = p3dLutBinFile;
            DolbyHdrMode.bCheckLoad = FALSE;
            DolbyHdrMode.u323dLutSize = 0;
            DolbyHdrMode.p3dLut = NULL;
            m_DolbyHdrModeMap[(EN_MAPI_DOLBY_HDR_MODE)i] = DolbyHdrMode;
        }
    }

    return TRUE;
}


BOOLEAN MApp_LoadDolbyHdrGlobalDimmingAttributes(dictionary *pHdrIni, ST_MAPI_DOLBY_HDR_GLOBAL_DIMMING_ATTRIBUTES *pstAttributes)
{
    pstAttributes->bGlobalDimming = iniparser_getint(pHdrIni, "dolby_global_dimming:enable_global_dimming", 0);
    pstAttributes->s8DelayFrame = iniparser_getint(pHdrIni, "dolby_global_dimming:delay_frame", 0);

    return TRUE;
}
#endif


void MApp_LoadHdrLevelAttributes(MAPI_XC_HDR_LEVEL_ATTRIBUTES stHdrLevelAttributes[E_MAPI_XC_HDR_MAX], MAPI_XC_HDR_LEVEL_ATTRIBUTES stHlgLevelAttributes[E_MAPI_XC_HDR_MAX])
{
    // HDR10
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16Smin = 1024;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16Smed = 3072;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16Smax = 10000;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16Tmin = 256;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16Tmed = 544;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16Tmax = 768;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16MidSourceOffset = 410;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16MidTargetOffset = 420;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16MidSourceRatio = 300;
    stHdrLevelAttributes[E_MAPI_XC_HDR_LOW].u16MidTargetRatio = 500;

    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Smin = 1024;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Smed = 3072;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Smax = 10000;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Tmin = 256;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Tmed = 576;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Tmax = 768;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16MidSourceOffset = 430;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16MidTargetOffset = 480;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16MidSourceRatio = 400;
    stHdrLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16MidTargetRatio = 400;

    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Smin = 1024;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Smed = 3072;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Smax = 10000;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Tmin = 256;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Tmed = 640;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Tmax = 768;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16MidSourceOffset = 418;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16MidTargetOffset = 510;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16MidSourceRatio = 200;
    stHdrLevelAttributes[E_MAPI_XC_HDR_HIGH].u16MidTargetRatio = 500;

    // HLG
    stHlgLevelAttributes[E_MAPI_XC_HDR_LOW].u16Smin = 0;
    stHlgLevelAttributes[E_MAPI_XC_HDR_LOW].u16Smed = 512;
    stHlgLevelAttributes[E_MAPI_XC_HDR_LOW].u16Smax = 10000;
    stHlgLevelAttributes[E_MAPI_XC_HDR_LOW].u16Tmin = 0;
    stHlgLevelAttributes[E_MAPI_XC_HDR_LOW].u16Tmed = 384;
    stHlgLevelAttributes[E_MAPI_XC_HDR_LOW].u16Tmax = 1024;

    stHlgLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Smin = 0;
    stHlgLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Smed = 512;
    stHlgLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Smax = 10000;
    stHlgLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Tmin = 0;
    stHlgLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Tmed = 512;
    stHlgLevelAttributes[E_MAPI_XC_HDR_MIDDLE].u16Tmax = 1024;

    stHlgLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Smin = 0;
    stHlgLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Smed = 512;
    stHlgLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Smax = 10000;
    stHlgLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Tmin = 0;
    stHlgLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Tmed = 640;
    stHlgLevelAttributes[E_MAPI_XC_HDR_HIGH].u16Tmax = 1024;

}


void MApp_LoadHdrToneMappingAttributes(MAPI_OPEN_HDR_TONE_MAPPING stToneMapping[E_MAPI_XC_HDR_MAX])
{
    stToneMapping[E_MAPI_XC_HDR_LOW].eLevel = E_MAPI_XC_HDR_LOW;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16SrcMinRatio = 10;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16SrcMedRatio = 512;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16SrcMaxRatio = 1019;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16TgtMinRatio = 500;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16TgtMedRatio = 50;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16TgtMaxRatio = 100;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16FrontSlopeMin = 256;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16FrontSlopeMax = 512;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16BackSlopeMin = 128;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16BackSlopeMax = 256;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16SceneChangeThrd = 512;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16SceneChangeRatioMax = 1024;
    stToneMapping[E_MAPI_XC_HDR_LOW].u8IIRRatio = 31;
    stToneMapping[E_MAPI_XC_HDR_LOW].u8TMO_TargetMode = 1;
    stToneMapping[E_MAPI_XC_HDR_LOW].u16SDRPanelGain = 56;

    stToneMapping[E_MAPI_XC_HDR_MIDDLE].eLevel = E_MAPI_XC_HDR_MIDDLE;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16SrcMinRatio = 10;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16SrcMedRatio = 512;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16SrcMaxRatio = 1019;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16TgtMinRatio = 500;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16TgtMedRatio = 50;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16TgtMaxRatio = 100;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16FrontSlopeMin = 256;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16FrontSlopeMax = 512;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16BackSlopeMin = 128;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16BackSlopeMax = 256;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16SceneChangeThrd = 512;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16SceneChangeRatioMax = 1024;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u8IIRRatio = 31;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u8TMO_TargetMode = 0;
    stToneMapping[E_MAPI_XC_HDR_MIDDLE].u16SDRPanelGain = 60;

    stToneMapping[E_MAPI_XC_HDR_HIGH].eLevel = E_MAPI_XC_HDR_HIGH;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16SrcMinRatio = 10;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16SrcMedRatio = 512;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16SrcMaxRatio = 1019;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16TgtMinRatio = 500;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16TgtMedRatio = 50;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16TgtMaxRatio = 1100;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16FrontSlopeMin = 256;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16FrontSlopeMax = 512;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16BackSlopeMin = 128;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16BackSlopeMax = 256;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16SceneChangeThrd = 512;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16SceneChangeRatioMax = 1024;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u8IIRRatio = 31;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u8TMO_TargetMode = 0;
    stToneMapping[E_MAPI_XC_HDR_HIGH].u16SDRPanelGain = 64;

}


BOOLEAN MApp_LoadHdrCustomerDlcAttributes(U8 u8ResType, MAPI_HDR_CUSTOMER_DLC *pstHdrDlc)
{
    //TODO:
    UNUSED(u8ResType);
    UNUSED(pstHdrDlc);
    return TRUE;
}

BOOLEAN MApp_LoadHdrCustomerGammaTableAttributes(U8 u8ResType, MAPI_TIMING_GAMMA_TABLE_MAPPING *pstHdrCustomerGammaTable)
{
    //TODO:
    UNUSED(u8ResType);
    UNUSED(pstHdrCustomerGammaTable);
    return TRUE;
}

BOOLEAN MApp_InitHdr(void)
{
#if 0
    // Init HDR attributes.
    MS_USER_SYSTEM_SETTING stUserSystemSetting;
    GetMSrvSystemDatabase()->GetUserSystemSetting(&stUserSystemSetting);

    // Set Open HDR on/off attribute.
    InitHdrAttributes(EN_MAPI_HDR_ONOFF_ATTRIBUTES, MAIN_WINDOW, (void*)&stUserSystemSetting.bOpenHdrOn[MAIN_WINDOW], sizeof(BOOLEAN));
    InitHdrAttributes(EN_MAPI_HDR_ONOFF_ATTRIBUTES, SUB_WINDOW, (void*)&stUserSystemSetting.bOpenHdrOn[SUB_WINDOW], sizeof(BOOLEAN));

    // Set Open HDR level attribute.
    ST_MAPI_HDR_LEVEL_ATTRIBUTES stLevelAttributes;
    stLevelAttributes.bAuto = stUserSystemSetting.bOpenHdrAutoLevelEnable[MAIN_WINDOW];
    stLevelAttributes.u8Level = stUserSystemSetting.u8OpenHdrManualLevel[MAIN_WINDOW];
    InitHdrAttributes(EN_MAPI_HDR_LEVEL_ATTRIBUTES, MAIN_WINDOW, (void*)&stLevelAttributes, sizeof(ST_MAPI_HDR_LEVEL_ATTRIBUTES));
    stLevelAttributes.bAuto = stUserSystemSetting.bOpenHdrAutoLevelEnable[SUB_WINDOW];
    stLevelAttributes.u8Level = stUserSystemSetting.u8OpenHdrManualLevel[SUB_WINDOW];
    InitHdrAttributes(EN_MAPI_HDR_LEVEL_ATTRIBUTES, SUB_WINDOW, (void*)&stLevelAttributes, sizeof(ST_MAPI_HDR_LEVEL_ATTRIBUTES));
#endif
#if ENABLE_DOLBY_HDR//TO DO
    // Set main window Dolby HDR on / off and mode.
    U8 u8DolbyMode = stUserSystemSetting.u8DolbyHdrPicMode[MAIN_WINDOW];

    EN_MAPI_DOLBY_HDR_MODE eDefaultDolbyMode = E_MAPI_DOLBY_HDR_MODE_NONE;
    if (u8DolbyMode == E_MAPI_DOLBY_HDR_MODE_NONE && MApp_GetHdrSetting(E_MAPI_HDR_DEFAULT_DOLBY_MODE_SETTING, &eDefaultDolbyMode, sizeof(EN_MAPI_DOLBY_HDR_MODE)) == MAPI_TRUE)
    {
        // Fisrt system boot. The Dolby HDR mode is illegal value in datatbase. Use default Dolby HDR mode in hdr.ini.
        u8DolbyMode = (U8)eDefaultDolbyMode;
    }

    ST_MAPI_HDR_SETTING_ATTRIBUTES stDolbyHdrSetting;
    memset(&stDolbyHdrSetting, 0, sizeof(ST_MAPI_HDR_SETTING_ATTRIBUTES));
    stDolbyHdrSetting.bHdrOn = stUserSystemSetting.bDolbyHdrOn[MAIN_WINDOW];
    stDolbyHdrSetting.stMode.u8Mode = u8DolbyMode;
    if(SetDolbyHdrMode((EN_MAPI_DOLBY_HDR_MODE)pSetting->stMode.u8Mode,MAIN_WINDOW) != E_MAPI_HDR_ERROR_SUCCESS)
    {
       printf("\nSetDolbyHdrMode Fail!!\n");
       return FALSE;

    }
#endif

    return TRUE;
}

BOOLEAN MApp_SetPanelCfd(const PanelInfo_t* const pstPanelInfo)
{
#if 1//defined(UFO_XC_HDR_VERSION) && (UFO_XC_HDR_VERSION >= 2)
    //ST_MAPI_DOLBY_HDR_GLOBAL_DIMMING_ATTRIBUTES stAttributes;
    //memset(&stAttributes, 0, sizeof(ST_MAPI_DOLBY_HDR_GLOBAL_DIMMING_ATTRIBUTES));
    //getDolbyGlobalDimmingAttributes(&stAttributes);
    XC_CFD_PANEL stCfdPanel;
    memset(&stCfdPanel, 0, sizeof(XC_CFD_PANEL));
    //stCfdPanel.u32Version = CFD_PANEL_VERSION;
    stCfdPanel.u16Length = sizeof(XC_CFD_PANEL);

    stCfdPanel.u8ColorFormat = pstPanelInfo->stCfdAttribute.u8ColorFormat;
    stCfdPanel.u8ColorDataFormat = pstPanelInfo->stCfdAttribute.u8ColorDataFormat;
    stCfdPanel.bIsFullRange = pstPanelInfo->stCfdAttribute.bIsFullRange;
    stCfdPanel.u16Display_Primaries_x[0] = pstPanelInfo->stCfdAttribute.u16tRx;
    stCfdPanel.u16Display_Primaries_x[1] = pstPanelInfo->stCfdAttribute.u16tGx;
    stCfdPanel.u16Display_Primaries_x[2] = pstPanelInfo->stCfdAttribute.u16tBx;
    stCfdPanel.u16Display_Primaries_y[0] = pstPanelInfo->stCfdAttribute.u16tRy;
    stCfdPanel.u16Display_Primaries_y[1] = pstPanelInfo->stCfdAttribute.u16tGy;
    stCfdPanel.u16Display_Primaries_y[2] = pstPanelInfo->stCfdAttribute.u16tBy;
    stCfdPanel.u16White_point_x = pstPanelInfo->stCfdAttribute.u16tWx;
    stCfdPanel.u16White_point_y = pstPanelInfo->stCfdAttribute.u16tWy;
    stCfdPanel.u16MaxLuminance = pstPanelInfo->stCfdAttribute.u16MaxLuminance;
    stCfdPanel.u16MedLuminance = pstPanelInfo->stCfdAttribute.u16MedLuminance;
    stCfdPanel.u16MinLuminance = pstPanelInfo->stCfdAttribute.u16MinLuminance;
    stCfdPanel.bLinearRgb = pstPanelInfo->stCfdAttribute.bLinearRgb;
    stCfdPanel.bCustomerColorPrimaries = pstPanelInfo->stCfdAttribute.bCustomerColorPrimaries;
    stCfdPanel.u16SourceWx = pstPanelInfo->stCfdAttribute.u16SourceWx;
    stCfdPanel.u16SourceWy = pstPanelInfo->stCfdAttribute.u16SourceWy;
#if 0//CFD_PANEL_VERSION >= 2
    const PanelBacklightPWMInfo* const pstPWMInfo = mapi_syscfg_fetch::GetInstance()->GetPanelBacklightPWMInfo();
    if (pstPWMInfo != NULL)
    {
        stCfdPanel.u8PWMPort = pstPWMInfo->u8PWMPort;
    }
    stCfdPanel.s8DelayFrame = stAttributes.s8DelayFrame; // config in the hdr.ini
    stCfdPanel.bGlobalDimming = stAttributes.bGlobalDimming; // config in the hdr.ini
#endif

    XC_CFD_CONTROL_INFO stCfdCtrl;
    memset(&stCfdCtrl, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrl.enCtrlType = E_XC_CFD_CTRL_TYPE_PANEL;
    stCfdCtrl.pParam = &stCfdPanel;
    stCfdCtrl.u32ParamLen = sizeof(XC_CFD_PANEL);

    if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrl) == E_APIXC_RET_OK)
    {
        return TRUE;
    }
#endif

    return FALSE;
}

EN_MS_HDR MApp_GetHDRUserSetting(void)
{
    return stGenSetting.g_SysSetting.enHdrSetting;
}



void MApp_HDR_Handler(void)
{
    sHDR_METADATA pstMetadata;
    msAPI_HDR_GetHDRMetaData(&pstMetadata);

    //debug
    printf("MApp_HDR_Handler:\n");
    printf("pstMetadata.u8EOTF = %d\n", pstMetadata.u8EOTF);
    printf("pstMetadata.u16Max_Display_Mastering_Luminance = %d\n", pstMetadata.u16Max_Display_Mastering_Luminance);
    printf("pstMetadata.u16Min_Display_Mastering_Luminance = %d\n", pstMetadata.u16Min_Display_Mastering_Luminance);
    printf("pstMetadata.u8Static_Metadata_ID = %d\n", pstMetadata.u8Static_Metadata_ID);
    printf("pstMetadata.u16Version = %d\n", pstMetadata.u16Version);
    printf("pstMetadata.u16Maximum_Content_Light_Level = %d\n", pstMetadata.u16Maximum_Content_Light_Level);

    if (m_bHdrInitialized == TRUE && m_bHdrMetadataChanged == TRUE)
    {
        printf("MApp_HDR_Handler 2\n");

        m_bHdrMetadataChanged = FALSE;

        //msAPI_SetHdmiCfd(MAIN_WINDOW);  //TODO

    }
}


BOOLEAN MApp_HDR_Init_Panel(void)
{
    //According to panel type. currently use a temp setting.
    PanelInfo_t pstPanelInfo;
    pstPanelInfo.stCfdAttribute.u8ColorFormat = 3;
    pstPanelInfo.stCfdAttribute.u8ColorDataFormat = 0;
    pstPanelInfo.stCfdAttribute.bIsFullRange = 1;
    pstPanelInfo.stCfdAttribute.u16tRx = 3200;
    pstPanelInfo.stCfdAttribute.u16tRy = 16455;
    pstPanelInfo.stCfdAttribute.u16tGx = 15000;
    pstPanelInfo.stCfdAttribute.u16tGy = 30000;
    pstPanelInfo.stCfdAttribute.u16tBx = 7500;
    pstPanelInfo.stCfdAttribute.u16tBy = 3000;
    pstPanelInfo.stCfdAttribute.u16tWx = 15635;
    pstPanelInfo.stCfdAttribute.u16tWy = 16450;
    pstPanelInfo.stCfdAttribute.u16MaxLuminance = 100;
    pstPanelInfo.stCfdAttribute.u16MedLuminance = 50;
    pstPanelInfo.stCfdAttribute.u16MinLuminance = 500;
    pstPanelInfo.stCfdAttribute.bLinearRgb = 1;
    pstPanelInfo.stCfdAttribute.bCustomerColorPrimaries = 0;
    pstPanelInfo.stCfdAttribute.u16SourceWx = 15635;
    pstPanelInfo.stCfdAttribute.u16SourceWy = 16450;

    return MApp_SetPanelCfd(&pstPanelInfo);

}


void MApp_HDR_Init_Tmo(void)
{
#if 1//(CFD_TMO_VERSION == 0)
    ST_KDRV_XC_CFD_TMO stCfdTmo;
    memset(&stCfdTmo, 0, sizeof(ST_KDRV_XC_CFD_TMO));
    stCfdTmo.u32Version = CFD_TMO_VERSION;
    stCfdTmo.u16Length = sizeof(ST_KDRV_XC_CFD_TMO);

    MAPI_XC_HDR_LEVEL_ATTRIBUTES stTmoAttribute;
    memset(&stTmoAttribute, 0, sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
    MApp_GetHdrLevelAttribues(E_MAPI_XC_HDR_LOW, &stTmoAttribute);
    stCfdTmo.u16Hdr10Smin[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Smin;
    stCfdTmo.u16Hdr10Smed[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Smed;
    stCfdTmo.u16Hdr10Smax[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Smax;
    stCfdTmo.u16Hdr10Tmin[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Tmin;
    stCfdTmo.u16Hdr10Tmed[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Tmed;
    stCfdTmo.u16Hdr10Tmax[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Tmax;

    memset(&stTmoAttribute, 0, sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
    MApp_GetHdrLevelAttribues(E_MAPI_XC_HDR_MIDDLE, &stTmoAttribute);
    stCfdTmo.u16Hdr10Smin[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Smin;
    stCfdTmo.u16Hdr10Smed[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Smed;
    stCfdTmo.u16Hdr10Smax[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Smax;
    stCfdTmo.u16Hdr10Tmin[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Tmin;
    stCfdTmo.u16Hdr10Tmed[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Tmed;
    stCfdTmo.u16Hdr10Tmax[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Tmax;

    memset(&stTmoAttribute, 0, sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
    MApp_GetHdrLevelAttribues(E_MAPI_XC_HDR_HIGH, &stTmoAttribute);
    stCfdTmo.u16Hdr10Smin[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Smin;
    stCfdTmo.u16Hdr10Smed[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Smed;
    stCfdTmo.u16Hdr10Smax[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Smax;
    stCfdTmo.u16Hdr10Tmin[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Tmin;
    stCfdTmo.u16Hdr10Tmed[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Tmed;
    stCfdTmo.u16Hdr10Tmax[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Tmax;

    memset(&stTmoAttribute, 0, sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
    MApp_GetHlgLevelAttributes(E_MAPI_XC_HDR_LOW, &stTmoAttribute);
    stCfdTmo.u16HlgSmin[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Smin;
    stCfdTmo.u16HlgSmed[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Smed;
    stCfdTmo.u16HlgSmax[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Smax;
    stCfdTmo.u16HlgTmin[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Tmin;
    stCfdTmo.u16HlgTmed[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Tmed;
    stCfdTmo.u16HlgTmax[E_MAPI_XC_HDR_LOW] = stTmoAttribute.u16Tmax;

    memset(&stTmoAttribute, 0, sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
    MApp_GetHlgLevelAttributes(E_MAPI_XC_HDR_MIDDLE, &stTmoAttribute);
    stCfdTmo.u16HlgSmin[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Smin;
    stCfdTmo.u16HlgSmed[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Smed;
    stCfdTmo.u16HlgSmax[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Smax;
    stCfdTmo.u16HlgTmin[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Tmin;
    stCfdTmo.u16HlgTmed[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Tmed;
    stCfdTmo.u16HlgTmax[E_MAPI_XC_HDR_MIDDLE] = stTmoAttribute.u16Tmax;

    memset(&stTmoAttribute, 0, sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
    MApp_GetHlgLevelAttributes(E_MAPI_XC_HDR_HIGH, &stTmoAttribute);
    stCfdTmo.u16HlgSmin[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Smin;
    stCfdTmo.u16HlgSmed[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Smed;
    stCfdTmo.u16HlgSmax[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Smax;
    stCfdTmo.u16HlgTmin[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Tmin;
    stCfdTmo.u16HlgTmed[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Tmed;
    stCfdTmo.u16HlgTmax[E_MAPI_XC_HDR_HIGH] = stTmoAttribute.u16Tmax;

    XC_CFD_CONTROL_INFO stCfdCtrl;
    memset(&stCfdCtrl, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrl.enCtrlType = E_XC_CFD_CTRL_SET_TMO;
    stCfdCtrl.pParam = &stCfdTmo;
    stCfdCtrl.u32ParamLen = sizeof(ST_KDRV_XC_CFD_TMO);

    MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrl);
#endif


}

#if 1 //wait for XC api
void MApp_AutoDownload_Config(void)
{
    XC_AUTODOWNLOAD_CLIENT_SUPPORTED_CAPS stCaps;
    memset(&stCaps, 0, sizeof(XC_AUTODOWNLOAD_CLIENT_SUPPORTED_CAPS));
    stCaps.enClient = E_XC_AUTODOWNLOAD_CLIENT_HDR;
    //MApi_XC_GetChipCaps(E_XC_SUPPORT_AUTODOWNLOAD_CLIENT, (MS_U32*)&stCaps, sizeof(XC_AUTODOWNLOAD_CLIENT_SUPPORTED_CAPS));
    if (stCaps.bSupported == TRUE)
    {
        {
            XC_AUTODOWNLOAD_CONFIG_INFO stAutodownloadCfgInfo;
            stAutodownloadCfgInfo.u32ConfigInfo_Version = AUTODOWNLOAD_CONFIG_INFO_VERSION;
            stAutodownloadCfgInfo.u16ConfigInfo_Length = sizeof(XC_AUTODOWNLOAD_CONFIG_INFO);

            stAutodownloadCfgInfo.enClient = E_XC_AUTODOWNLOAD_CLIENT_HDR; /// current client
            stAutodownloadCfgInfo.phyBaseAddr = XC_AUTODOWNLOAD_ADR;                /// baseaddr
            stAutodownloadCfgInfo.u32Size = XC_AUTODOWNLOAD_LEN;                    /// size
            stAutodownloadCfgInfo.bEnable = TRUE;                    /// enable/disable the client
            stAutodownloadCfgInfo.enMode = E_XC_AUTODOWNLOAD_TRIGGER_MODE;;     /// work mode
            MApi_XC_AutoDownload_Config(&stAutodownloadCfgInfo);
        }

        {
            XC_AUTODOWNLOAD_CONFIG_INFO stAutodownloadCfgInfo;
            stAutodownloadCfgInfo.u32ConfigInfo_Version = AUTODOWNLOAD_CONFIG_INFO_VERSION;
            stAutodownloadCfgInfo.u16ConfigInfo_Length = sizeof(XC_AUTODOWNLOAD_CONFIG_INFO);

            stAutodownloadCfgInfo.enClient = E_XC_AUTODOWNLOAD_CLIENT_XVYCC; /// current client
            stAutodownloadCfgInfo.phyBaseAddr = XC_AUTODOWNLOAD_XVYCC_ADR;                /// baseaddr
            stAutodownloadCfgInfo.u32Size = XC_AUTODOWNLOAD_XVYCC_LEN;                    /// size
            stAutodownloadCfgInfo.bEnable = TRUE;                    /// enable/disable the client
            stAutodownloadCfgInfo.enMode = E_XC_AUTODOWNLOAD_TRIGGER_MODE;;     /// work mode
            MApi_XC_AutoDownload_Config(&stAutodownloadCfgInfo);
        }
    }
}
#endif

BOOLEAN MApp_HDR_Init(void)
{
    // HDR customer DLC setting.
    MApp_LoadHdrCustomerDlcAttributes(0, &m_4KHdrCustomerDlc);
    MApp_LoadHdrCustomerDlcAttributes(1, &m_2KHdrCustomerDlc);

    // HDR customer gamma table setting.
    MApp_LoadHdrCustomerGammaTableAttributes(0, &m_4KHdrCustomerGammaTable);
    MApp_LoadHdrCustomerGammaTableAttributes(1, &m_2KHdrCustomerGammaTable);

    // HDR10 / HLG level setting.
    MApp_LoadHdrLevelAttributes(m_stHdrLevelAttributes, m_stHlgLevelAttributes);

    // Open HDR tone mapping.
    MApp_LoadHdrToneMappingAttributes(m_stOpenHdrToneMapping);

    //Config Auto Download
    MApp_AutoDownload_Config();

#if 0 //set mem addr for VDEC
    {
        XC_HDR_OTT_SHARE_MEMORY_INFO stHdrOttShareMemInfo;
        memset(&stHdrOttShareMemInfo, 0, sizeof(XC_HDR_OTT_SHARE_MEMORY_INFO));
        stHdrOttShareMemInfo.u32ShareMemInfo_Version = HDR_OTT_SHARE_MEMORY_INFO_VERSION;             ///<Version of current structure. Please always set to "HDR_OTT_SHARE_MEMORY_INFO_VERSION" as input
        stHdrOttShareMemInfo.u16ShareMemInfo_Length = sizeof(XC_HDR_OTT_SHARE_MEMORY_INFO);           ///<Length of this structure, u16ShareMemInfo_Length=sizeof(XC_HDR_SHARE_MEMORY_INFO)
        stHdrOttShareMemInfo.phyBaseAddr = XC_DOLBY_HDR_ADR;                                          /// Share memory baseaddr
        stHdrOttShareMemInfo.u32Size = XC_DOLBY_HDR_LEN;                                              /// Share memory size
        MApi_XC_HDR_Control(E_XC_HDR_CTRL_SET_OTT_SHARE_MEMORY, &stHdrOttShareMemInfo);
    }
#endif

    MApp_HDR_Init_Panel();
    MApp_HDR_Init_Tmo();

    MApi_XC_MLoad_Cus_Init(E_MLCLIENT_MAIN_HDR, CFD_MLOAD_ADR, CFD_MLOAD_LEN);
    MApi_XC_MLoad_Cus_Enable(E_MLCLIENT_MAIN_HDR, TRUE);

    m_bHdrInitialized = TRUE;
    return TRUE;

}


#endif //#if (ENABLE_HDR)
#undef _APP_HDR_C_
