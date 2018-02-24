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
#define MSAPI_HDR_C_
//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include "MsCommon.h"
#include "Board.h"
#include "apiXC.h"
#include "msAPI_Global.h"
#include "Utl.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_PCMode.h"
#if (ENABLE_HDR)
#include "MApp_HDR.h"
#include "msAPI_HDR.h"
#include "drvPQ.h"
#include "apiXC_Dlc.h"
#include "drvXC_HDMI_if.h"
#include "apiXC_Hdmi.h"

EN_MAPI_TIMING m_eHdrVideoTiming;
ST_MAPI_HDR_METADATA m_HdrMetadata;
BOOLEAN m_bHdrHwWorking;
static BOOLEAN m_bPreHdrHwWorking= FALSE;


extern BOOLEAN m_bHdrInitialized;
extern BOOLEAN m_bHdrMetadataChanged;
extern SCALER_WIN m_enDstWin;
extern ST_MAPI_HDR_SETTING m_stHdrSettting[MAX_WINDOW];

PQ_INPUT_SOURCE_TYPE msAPI_SDK2PQInputSourcTypeTrans(INPUT_SOURCE_TYPE_t enApiInputSourceType)
{
    PQ_INPUT_SOURCE_TYPE enPQSourceType = PQ_INPUT_SOURCE_NONE;

    if(IsSrcTypeVga(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_VGA; // VGA
    }
    else if(IsSrcTypeATV(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_TV; // TV
    }
    else if(IsSrcTypeDTV(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_DTV; //DTV
    }
    else if(IsSrcTypeAV(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_CVBS; // AV
    }
    else if(IsSrcTypeScart(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_SCART; // SCART
    }
    else if(IsSrcTypeSV(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_SVIDEO; // SV
    }
    else if(IsSrcTypeHDMI(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_HDMI; // HDMI
    }
    else if(IsSrcTypeYPbPr(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_YPBPR; // COMP
    }
    else if(IsSrcTypeJpeg(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_JPEG; // JPEG
    }
    else if(IsSrcTypeStorage(enApiInputSourceType))
    {
        enPQSourceType = PQ_INPUT_SOURCE_STORAGE; // Storage
    }
    else
    {
        ASSERT(0);
    }

    return enPQSourceType;
}

BOOLEAN msAPI_SetHdrOnOff(BOOLEAN bOn)
{
#if (ENABLE_OPEN_HDR== 1)
    m_bHdrMetadataChanged |= (m_stHdrSettting[m_enDstWin].bOpenHdrOn != bOn);
    m_stHdrSettting[m_enDstWin].bOpenHdrOn = bOn;
    if (m_bHdrInitialized == TRUE && m_bHdrMetadataChanged == TRUE)
    {
#if 1//defined(UFO_XC_HDR_VERSION) && (UFO_XC_HDR_VERSION == 2)
        BOOLEAN bRet = (msAPI_LoadHdrMetadataByHdrIp()==E_MAPI_HDR_ERROR_SUCCESS)?TRUE:FALSE;
        msAPI_FireCfd();
        return bRet;
#else
        return LoadHdrMetadata();
#endif
    }
    else
    {
        return TRUE;
    }
#else
    return FALSE;
#endif
}


BOOLEAN msAPI_GetHdrAttributes(EN_MAPI_HDR_ATTRIBUTES enAttribueType, void *pAttributes, U16 u16AttributesSize)
{
    BOOLEAN bRet = FALSE;
    switch (enAttribueType)
    {
#if (ENABLE_OPEN_HDR== 1)
        case EN_MAPI_HDR_ONOFF_ATTRIBUTES:
            {
                if (u16AttributesSize == sizeof(BOOLEAN))
                {
                    BOOLEAN *pbOn = (BOOLEAN*)pAttributes;
                    (*pbOn) = MApp_GetHdrOnOff();
                    bRet = TRUE;
                }
            }
            break;
        case EN_MAPI_HDR_LEVEL_ATTRIBUTES:
            {
                if (u16AttributesSize == sizeof(ST_MAPI_HDR_LEVEL_ATTRIBUTES))
                {
                    ST_MAPI_HDR_LEVEL_ATTRIBUTES *pLevelAttributs = (ST_MAPI_HDR_LEVEL_ATTRIBUTES*)pAttributes;
                    pLevelAttributs->bAuto = MApp_GetAutoDetectHdrLevel(m_enDstWin);
                    pLevelAttributs->u8Level = MApp_GetHdrLevel(m_enDstWin);
                    bRet = TRUE;
                }
            }
            break;
        case EN_MAPI_HDR_TYPE_ATTRIBUTES:
            {
                if (u16AttributesSize == sizeof(U16))
                {
                    U16 *pu16MetadataType = (U16*)pAttributes;
                    (*pu16MetadataType) = msAPI_GetVideoHdrType();
                    bRet = TRUE;
                }
            }
            break;
#endif
        case EN_MAPI_HDR_OPEN_SETTING_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_HDR_SETTING_ATTRIBUTES))
            {
                ST_MAPI_HDR_SETTING_ATTRIBUTES *pSetting = (ST_MAPI_HDR_SETTING_ATTRIBUTES*)pAttributes;
#if (ENABLE_OPEN_HDR == 1)
                if (IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    pSetting->bHdrVideo = MApp_IsOpenHdrVideo();
                    pSetting->bHdrOn = MApp_GetHdrOnOff();
                    pSetting->bHdrHwWorking = MApp_IsHdrWorking();
                    pSetting->stHdrLevel.bAuto = MApp_GetAutoDetectHdrLevel(m_enDstWin);
                    pSetting->stHdrLevel.u8Level = MApp_GetHdrLevel(m_enDstWin);
                    pSetting->eResult = E_MAPI_HDR_ERROR_SUCCESS;
                    bRet = TRUE;
                }
                else
                {
                    pSetting->bHdrVideo = FALSE;
                    pSetting->bHdrOn = MApp_GetHdrOnOff();
                    pSetting->bHdrHwWorking = FALSE;
                    pSetting->stHdrLevel.bAuto = MApp_GetAutoDetectHdrLevel(m_enDstWin);
                    pSetting->stHdrLevel.u8Level = MApp_GetHdrLevel(m_enDstWin);
                    pSetting->eResult = E_MAPI_HDR_ERROR_INPUT_SOUCE_NOT_SUPPORT;
                }
#else
                pSetting->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
            }
            break;
        case EN_MAPI_HDR_DOLBY_MODE_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES))
            {
                ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES *p3DLutAttributes = (ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES*)pAttributes;
#if (ENABLE_DOLBY_HDR== 1)
                XC_HDR_SUPPORTED_CAPS stCaps;
                stCaps.enHDRType = E_XC_HDR_TYPE_DOLBY;
                stCaps.bSupported = FALSE;
                MApi_XC_GetChipCaps(E_XC_SUPPORT_HDR, (MS_U32*)&stCaps, sizeof(XC_HDR_SUPPORTED_CAPS));

                if ( stCaps.bSupported == TRUE)
                {
                    p3DLutAttributes->u8Mode = m_stHdrSettting[m_enDstWin].eDolbyHdrMode;
                    p3DLutAttributes->eResult = E_MAPI_HDR_ERROR_SUCCESS;
                    bRet = TRUE;
                }
                else
                {
                    p3DLutAttributes->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
                }
#else
                p3DLutAttributes->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
            }
            break;
        case EN_MAPI_HDR_DOLBY_SETTING_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_HDR_SETTING_ATTRIBUTES))
            {
                ST_MAPI_HDR_SETTING_ATTRIBUTES *pSetting = (ST_MAPI_HDR_SETTING_ATTRIBUTES*)pAttributes;
#if (ENABLE_DOLBY_HDR == 1)
                XC_HDR_SUPPORTED_CAPS stCaps;
                stCaps.enHDRType = E_XC_HDR_TYPE_DOLBY;
                stCaps.bSupported = FALSE;
                MApi_XC_GetChipCaps(E_XC_SUPPORT_HDR, (MS_U32*)&stCaps, sizeof(XC_HDR_SUPPORTED_CAPS));

                if (stCaps.bSupported == TRUE)
                {
                    if if (IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                    {
                        pSetting->bHdrVideo = IsDolbyHdrVideo();
                        pSetting->bHdrOn = m_stHdrSettting[m_enDstWin].bDolbyHdrOn;
                        pSetting->bHdrHwWorking = IsHdrWorking();
                        pSetting->stMode.u8Mode = m_stHdrSettting[m_enDstWin].eDolbyHdrMode;
                        pSetting->eResult = E_MAPI_HDR_ERROR_SUCCESS;
                        bRet = TRUE;
                    }
                    else
                    {
                        pSetting->bHdrVideo = FALSE;
                        pSetting->bHdrOn = m_stHdrSettting[m_enDstWin].bDolbyHdrOn;
                        pSetting->bHdrHwWorking = FALSE;
                        pSetting->stMode.u8Mode = m_stHdrSettting[m_enDstWin].eDolbyHdrMode;
                        pSetting->eResult = E_MAPI_HDR_ERROR_INPUT_SOUCE_NOT_SUPPORT;
                    }
                }
                else
                {
                    pSetting->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
                }
#else
                pSetting->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
            }
            break;
        case EN_MAPI_HDR_DOLBY_ONOFF_ATTRIBUTES:
            {
#if (ENABLE_DOLBY_HDR == 1)
                if (u16AttributesSize == sizeof(BOOLEAN))
                {
                    BOOLEAN *pbOn = (BOOLEAN*)pAttributes;
                    (*pbOn) = GetDolbyHdrOnOff();
                    bRet = TRUE;
                }
#endif

            }
            break;
        default:
            break;
    };

    return bRet;
}
extern BOOLEAN MApp_IsDolbyHdrVideo(void);

BOOLEAN msAPI_IsHdrEnable(SCALER_WIN enWin)
{
    UNUSED(enWin);
#if ((ENABLE_OPEN_HDR== 1) || (ENABLE_DOLBY_HDR == 1))
    BOOLEAN bHdrVideo = MApp_IsOpenHdrVideo();
    bHdrVideo ^= MApp_IsDolbyHdrVideo();
    return bHdrVideo;
#else
    return FALSE;
#endif
}

BOOLEAN msAPI_RefreshHdrSetting(void)
{
#if ((ENABLE_OPEN_HDR== 1) || (ENABLE_DOLBY_HDR == 1))
    BOOLEAN bRet = FALSE;
    if (m_bHdrInitialized == TRUE)
    {
        m_bHdrMetadataChanged = TRUE;
        bRet = (msAPI_LoadHdrMetadataByHdrIp()==E_MAPI_HDR_ERROR_SUCCESS)?TRUE:FALSE;
        msAPI_FireCfd();
    }

    return bRet;
#else
    return FALSE;
#endif
}

BOOLEAN msAPI_SetHdrAttributes(EN_MAPI_HDR_ATTRIBUTES enAttribueType, void *pAttributes, U16 u16AttributesSize)
{
    BOOLEAN bRet = FALSE;
    switch (enAttribueType)
    {
#if (ENABLE_OPEN_HDR== 1)
        case EN_MAPI_HDR_ONOFF_ATTRIBUTES:
            {
                if (u16AttributesSize == sizeof(BOOLEAN))
                {
                    BOOLEAN *pbOn = (BOOLEAN*)pAttributes;
                    bRet = msAPI_SetHdrOnOff(*pbOn);
                }
            }
            break;
        case EN_MAPI_HDR_INIT_AUTO_DETECT_ATTRIBUTES:
            {
                if (u16AttributesSize == sizeof(ST_MAPI_HDR_LEVEL_ATTRIBUTES))
                {
                    ST_MAPI_HDR_LEVEL_ATTRIBUTES *pLevelAttributs = (ST_MAPI_HDR_LEVEL_ATTRIBUTES*)pAttributes;
                    bRet = MApp_SetAutoDetectHdrLevel(pLevelAttributs->bAuto, m_enDstWin, (E_MAPI_XC_HDR_LEVEL)pLevelAttributs->u8Level);
                }
            }
            break;
        case EN_MAPI_HDR_LEVEL_ATTRIBUTES:
            {
                if (u16AttributesSize == sizeof(ST_MAPI_HDR_LEVEL_ATTRIBUTES))
                {
                    ST_MAPI_HDR_LEVEL_ATTRIBUTES *pLevelAttributs = (ST_MAPI_HDR_LEVEL_ATTRIBUTES*)pAttributes;
                    if (pLevelAttributs->bAuto == TRUE)
                    {
                        bRet = MApp_SetAutoDetectHdrLevel(pLevelAttributs->bAuto, m_enDstWin, (E_MAPI_XC_HDR_LEVEL)pLevelAttributs->u8Level);
                    }
                    else
                    {
                        bRet = MApp_SetHdrLevel((E_MAPI_XC_HDR_LEVEL)pLevelAttributs->u8Level, m_enDstWin);
                    }
                }
            }
            break;
#endif
        case EN_MAPI_HDR_VIDEO_TIMING_ATTRIBUTES:
            {
                if (u16AttributesSize == sizeof(EN_MAPI_TIMING))
                {
                    EN_MAPI_TIMING *pTimingAttributs = (EN_MAPI_TIMING*)pAttributes;
                    m_eHdrVideoTiming = (*pTimingAttributs);
                }
            }
            break;
        case EN_MAPI_HDR_OPEN_SETTING_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_HDR_SETTING_ATTRIBUTES))
            {
                ST_MAPI_HDR_SETTING_ATTRIBUTES *pSetting = (ST_MAPI_HDR_SETTING_ATTRIBUTES*)pAttributes;
#if (ENABLE_OPEN_HDR == 1)
                if (pSetting->bHdrOn == TRUE)
                {
                    if (pSetting->stHdrLevel.bAuto == TRUE)
                    {
                        ST_MAPI_HDR_LEVEL_ATTRIBUTES *pLevelAttributs = (ST_MAPI_HDR_LEVEL_ATTRIBUTES*)pAttributes;
                        bRet = MApp_SetAutoDetectHdrLevel(pLevelAttributs->bAuto, m_enDstWin, (E_MAPI_XC_HDR_LEVEL)pLevelAttributs->u8Level);
                    }
                    else
                    {
                        bRet = MApp_SetHdrLevel((E_MAPI_XC_HDR_LEVEL)pSetting->stHdrLevel.u8Level, m_enDstWin);
                    }
                }
                else
                {
                    bRet = msAPI_SetHdrOnOff(pSetting->bHdrOn);
                }

                pSetting->eResult = (bRet==TRUE)?E_MAPI_HDR_ERROR_SUCCESS:E_MAPI_HDR_ERROR_UNDEFINED_FAIL;
#else
                pSetting->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
            }
            break;
        case EN_MAPI_HDR_DOLBY_MODE_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES))
            {
                ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES *p3DLutAttributes = (ST_MAPI_DOLBY_HDR_MODE_ATTRIBUTES*)pAttributes;
#if (ENABLE_DOLBY_HDR== 1)
                p3DLutAttributes->eResult = SetDolbyHdrMode((EN_MAPI_DOLBY_HDR_MODE)p3DLutAttributes->u8Mode, m_enDstWin);
                bRet = (p3DLutAttributes->eResult==E_MAPI_HDR_ERROR_SUCCESS)?TRUE:FALSE;
#else
                p3DLutAttributes->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
            }
            break;
        case EN_MAPI_HDR_DOLBY_SETTING_ATTRIBUTES:
            if (u16AttributesSize == sizeof(ST_MAPI_HDR_SETTING_ATTRIBUTES))
            {
                ST_MAPI_HDR_SETTING_ATTRIBUTES *pSetting = (ST_MAPI_HDR_SETTING_ATTRIBUTES*)pAttributes;
#if (ENABLE_DOLBY_HDR == 1)
                pSetting->eResult = SetDolbyHdrOn(pSetting->bHdrOn);
                if (pSetting->eResult == E_MAPI_HDR_ERROR_SUCCESS)
                {
                    pSetting->eResult = SetDolbyHdrMode((EN_MAPI_DOLBY_HDR_MODE)pSetting->stMode.u8Mode, m_enDstWin);
                }
                bRet = (pSetting->eResult==E_MAPI_HDR_ERROR_SUCCESS)?TRUE:FALSE;
#else
                pSetting->eResult = E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
            }
            break;
        default:
            break;
    };

    return bRet;
}

BOOLEAN msAPI_CheckHdrExtraCondition(SCALER_WIN enWin)
{
    //mapi_scope_lock(scopeLock, &m_HdrCheck_mutex);

    BOOLEAN bRet = FALSE;
//#ifdef UFO_XC_HDR
    BOOLEAN bIsHdrOn = FALSE;
    BOOLEAN bIsHdrFile = FALSE;

    msAPI_GetHdrAttributes(EN_MAPI_HDR_ONOFF_ATTRIBUTES, (void*)&bIsHdrOn, sizeof(BOOL));
    bIsHdrFile = msAPI_IsHdrEnable(enWin);

    //HDR_MSG("[%s:%d] enWin=%d bIsHdrOn=%d bIsHdrFile=%d u16HDRMetadataType=%d\n", __FUNCTION__, __LINE__, enWin, bIsHdrOn, bIsHdrFile, m_HdrMetadata.u16HDRMetadataType);

    if(TRUE == bIsHdrOn && TRUE == bIsHdrFile)
    {
        //P2P mode is not support HDR
        if(TRUE == MDrv_PQ_Get_PointToPoint(PQ_MAIN_WINDOW))
        {
            bIsHdrOn = FALSE;
        }
        //HDR_MSG("[%s:%d] Keep HDR on=%d\n", __FUNCTION__, __LINE__, bIsHdrOn);

        if(FALSE == bIsHdrOn)
        {
            msAPI_SetHdrAttributes(EN_MAPI_HDR_ONOFF_ATTRIBUTES, (void*)&bIsHdrOn, sizeof(BOOLEAN));
        }
    }
//#endif
    return bRet;
}

U16 msAPI_GetVideoHdrType(void)
{
#if ((ENABLE_OPEN_HDR == 1) || (ENABLE_DOLBY_HDR == 1))
    return m_HdrMetadata.u16HDRMetadataType;
#else
    return 0x00;
#endif
}

EN_MAPI_HDR_ERROR_CODE msAPI_SetDolbyHdrOn(BOOLEAN bHdrOn)
{
#if (ENABLE_DOLBY_HDR == 1)
    XC_HDR_SUPPORTED_CAPS stCaps;
    stCaps.enHDRType = E_XC_HDR_TYPE_DOLBY;
    stCaps.bSupported = FALSE;
    MApi_XC_GetChipCaps(E_XC_SUPPORT_HDR, (MS_U32*)&stCaps, sizeof(XC_HDR_SUPPORTED_CAPS));

    if (stCaps.bSupported == TRUE)
    {
        m_bHdrMetadataChanged |= (m_stHdrSettting[m_enDstWin].bDolbyHdrOn != bHdrOn);
        m_stHdrSettting[m_enDstWin].bDolbyHdrOn = bHdrOn;
        #if 0
        if(m_stHdrSettting[m_enDstWin].bDolbyHdrOn)
        {
            sendVideoEvent(E_MAPI_EVENT_HDR_STATUS, m_enDstWin, E_MAPI_VIDEO_DOLBY_HDR_RUNNING, 0);
        }
        else if((!m_stHdrSettting[m_enDstWin].bDolbyHdrOn) && m_stHdrSettting[m_enDstWin].bOpenHdrOn)
        {
            sendVideoEvent(E_MAPI_EVENT_HDR_STATUS, m_enDstWin, E_MAPI_VIDEO_OPEN_HDR_RUNNING, 0);
        }
        else
        {
            sendVideoEvent(E_MAPI_EVENT_HDR_STATUS, m_enDstWin, E_MAPI_VIDEO_HDR_STOP, 0);
        }
        #endif

        if (m_bHdrInitialized == TRUE && m_bHdrMetadataChanged == TRUE)
        {
            EN_MAPI_HDR_ERROR_CODE eRet = LoadHdrMetadataByHdrIp();
            FireCfd();
            return eRet;
        }
        else
        {
            return E_MAPI_HDR_ERROR_SUCCESS;
        }
    }
    else
    {
        return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
    }
#else
    UNUSED(bHdrOn);
    return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
}

BOOLEAN msAPI_SetHDRMode(PQ_WIN eWindow, MS_U16 u16GRuleLevelIndex)
{
    return MDrv_PQ_EnableHDRMode(eWindow ,u16GRuleLevelIndex);
}

BOOLEAN msAPI_GetHDMIMode(void)
{
    return FALSE;
}


EN_MAPI_HDR_ERROR_CODE msAPI_LoadHdrMetadataByHdrIp(void)
{
    //UNUSED(m_bPreHdrHwWorking);
#if (ENABLE_OPEN_HDR == 1) || (ENABLE_DOLBY_HDR== 1)
    if (m_bHdrMetadataChanged == FALSE)
    {
        return E_MAPI_HDR_ERROR_SUCCESS;
    }

    // Check HDR/3D conflict
    #if 0
    if (m_pIs3dEnableCb != NULL && m_pIs3dEnableCb() == TRUE)
    {
        sendVideoEvent(E_MAPI_EVENT_CONFLICT, m_enDstWin, E_MAPI_CONFLICT_3D, E_MAPI_CONFLICT_HDR);

        m_bHdrInitialized = TRUE;
        return E_MAPI_HDR_CONFLICT;
    }

    mapi_display* pDisplay = mapi_display::GetInstance();
    if (pDisplay == NULL)
    {
        return E_MAPI_HDR_ERROR_UNDEFINED_FAIL;
    }
    #endif

    XC_HDR_SUPPORTED_CAPS stCaps;
    stCaps.enHDRType = E_XC_HDR_TYPE_DOLBY;
    stCaps.bSupported = FALSE;
    //MApi_XC_GetChipCaps(E_XC_SUPPORT_HDR, (MS_U32*)&stCaps, sizeof(XC_HDR_SUPPORTED_CAPS)); //TODO

    EN_MAPI_HDR_ERROR_CODE eRet = E_MAPI_HDR_ERROR_UNDEFINED_FAIL;

    XC_CFD_HDR stCfdHdr;
    memset(&stCfdHdr, 0, sizeof(XC_CFD_HDR));
    stCfdHdr.u32Version = CFD_HDR_VERSION;
    stCfdHdr.u16Length = sizeof(XC_CFD_HDR);
    stCfdHdr.u8Win = m_enDstWin;
    stCfdHdr.u8HdrType = E_XC_CFD_HDR_TYPE_NONE;

#if (ENABLE_DOLBY_HDR == 1)
    if ((m_stHdrSettting[m_enDstWin].bDolbyHdrOn == TRUE) && (stCaps.bSupported == TRUE))
    {
        stCfdHdr.u8HdrType |= E_XC_CFD_HDR_TYPE_DOLBY;
    }
#endif

#if (ENABLE_OPEN_HDR== 1)
    if (MApp_GetHDRUserSetting() != EN_HDR_OFF)
    {
        stCfdHdr.u8HdrType |= (E_XC_CFD_HDR_TYPE_OPEN | E_XC_CFD_HDR_TYPE_HLG);
    }
#endif

    // Set Open HDR level.
    if ((MApp_GetHDRUserSetting() == EN_HDR_AUTO))
    {
    #if 0
        if(IS_4K_TIMING(m_eHdrVideoTiming))
        {
            stCfdHdr.u8TmoLevel = E_MAPI_XC_HDR_HIGH;
        }
        else
    #endif
        {
            stCfdHdr.u8TmoLevel = E_MAPI_XC_HDR_MIDDLE;
        }
    }
    else
    {
        // Use manual HDR level setting.
        stCfdHdr.u8TmoLevel = m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel;
    }

    XC_CFD_CONTROL_INFO stCfdCtrl;
    memset(&stCfdCtrl, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrl.enCtrlType = E_XC_CFD_CTRL_TYPE_HDR;
    stCfdCtrl.pParam = &stCfdHdr;
    stCfdCtrl.u32ParamLen = sizeof(XC_CFD_HDR);

    MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrl);

    m_bHdrHwWorking = MApp_IsHdrWorking();
    if ((MApp_IsDolbyHdrVideo() == TRUE) && (m_bHdrHwWorking == TRUE))
    {
        #if 0 //by customer,need customer gamma table setting
        BOOLEAN bHdrEnable = FALSE;
        SetGammaTableProp(E_MAPI_HDR_ENABLE, &bHdrEnable, sizeof(BOOLEAN));
        RefreshGammaTable();
        #endif

        if (m_stHdrSettting[m_enDstWin].eDolbyHdrMode == E_MAPI_DOLBY_HDR_MODE_VIVID)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_DOLBY_VIVID);
        }
        else if (m_stHdrSettting[m_enDstWin].eDolbyHdrMode == E_MAPI_DOLBY_HDR_MODE_BRIGHTNESS)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_DOLBY_BRIGHTNESS);
        }
        else if (m_stHdrSettting[m_enDstWin].eDolbyHdrMode == E_MAPI_DOLBY_HDR_MODE_DARK)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_DOLBY_DARK);
        }
        else
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_DOLBY_USER);
        }

        eRet = E_MAPI_HDR_ERROR_SUCCESS;
    }
    else if ((MApp_IsOpenHdrVideo() == TRUE) && (m_bHdrHwWorking == TRUE))
    {
        // Set Open HDR level.
        MAPI_OPEN_HDR_TONE_MAPPING  stTmoAttribute;
        if ((m_stHdrSettting[m_enDstWin].bOpenHdrAutoLevelEnable == TRUE) || (m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_REF_MODE))
        {
        #if 0
            if (IS_4K_TIMING(m_eHdrVideoTiming))
            {
                stTmoAttribute.eLevel= E_MAPI_XC_HDR_HIGH;
            }
            else
        #endif
            {
                stTmoAttribute.eLevel = E_MAPI_XC_HDR_MIDDLE;
            }
        }
        else
        {
            // Use manual HDR level setting.
            stTmoAttribute.eLevel = m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel;
        }

        MApp_GetHdrSetting(E_MAPI_HDR_OPEN_TONE_MAPPING_SETTING, &stTmoAttribute, sizeof(MAPI_OPEN_HDR_TONE_MAPPING));

        MAPI_XC_HDR_LEVEL_ATTRIBUTES stHdrLevelAttribute;
        memset(&stHdrLevelAttribute, 0, sizeof(MAPI_XC_HDR_LEVEL_ATTRIBUTES));
        MApp_GetHdrLevelAttribues(stTmoAttribute.eLevel, &stHdrLevelAttribute);

        ST_XC_DLC_TMO_INFO stTmo;
        memset(&stTmo, 0, sizeof(ST_XC_DLC_TMO_INFO));
        //stTmo.u32TMOInfo_Version = DLC_TMO_INFO_VERSION;
        stTmo.u16TMOInfo_Length = sizeof(ST_XC_DLC_TMO_INFO);

        stTmo.u16SrcMinRatio = stTmoAttribute.u16SrcMinRatio;
        stTmo.u16SrcMedRatio = stTmoAttribute.u16SrcMedRatio;
        stTmo.u16SrcMaxRatio = stTmoAttribute.u16SrcMaxRatio;

        stTmo.u16TgtMin = stTmoAttribute.u16TgtMinRatio;
        stTmo.u16TgtMed = stTmoAttribute.u16TgtMedRatio;
        stTmo.u16TgtMax = stTmoAttribute.u16TgtMaxRatio;

        stTmo.u16FrontSlopeMin = stTmoAttribute.u16FrontSlopeMin;
        stTmo.u16FrontSlopeMax = stTmoAttribute.u16FrontSlopeMax;
        stTmo.u16BackSlopeMin = stTmoAttribute.u16BackSlopeMin;
        stTmo.u16BackSlopeMax = stTmoAttribute.u16BackSlopeMax;

        stTmo.u16SceneChangeThrd = stTmoAttribute.u16SceneChangeThrd;
        stTmo.u16SceneChangeRatioMax = stTmoAttribute.u16SceneChangeRatioMax;

        stTmo.u8IIRRatio = stTmoAttribute.u8IIRRatio;
        stTmo.u8TMOTargetMode = stTmoAttribute.u8TMO_TargetMode;
        stTmo.u16SDRPanelGain = stTmoAttribute.u16SDRPanelGain;

        stTmo.u16Smin = stHdrLevelAttribute.u16Smin;
        stTmo.u16Smed = stHdrLevelAttribute.u16Smed;
        stTmo.u16Smax = stHdrLevelAttribute.u16Smax;
        stTmo.u16Tmin = stHdrLevelAttribute.u16Tmin;
        stTmo.u16Tmed = stHdrLevelAttribute.u16Tmed;
        stTmo.u16Tmax = stHdrLevelAttribute.u16Tmax;

        if ((m_stHdrSettting[m_enDstWin].bOpenHdrAutoLevelEnable == FALSE) && (m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_REF_MODE))
        {
            stTmo.bRefMode = TRUE;
        }
        else
        {
            stTmo.bRefMode = FALSE;
        }

        MApi_XC_DLC_SetTMOInfo(&stTmo);

        //msAPI_SendVideoEvent(E_MAPI_EVENT_VIDEO_STATUS, m_enDstWin, E_MAPI_VIDEO_OPEN_HDR_RUNNING, 0);

        if(m_stHdrSettting[m_enDstWin].bOpenHdrAutoLevelEnable == TRUE)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OPEN_AUTO);
        }
        else if(m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_LOW)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OPEN_LOW);
        }
        else if(m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_MIDDLE)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OPEN_MID);
        }
        else if(m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_HIGH)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OPEN_HIGH);
        }
        else if(m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_REF_MODE)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OPEN_REF);
        }
        else
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OFF);
        }

        eRet = E_MAPI_HDR_ERROR_SUCCESS;
    }
    else if ((MApp_IsHlgHdrVideo() == TRUE) && (m_bHdrHwWorking == TRUE))
    {
        #if 0 //by customer,need customer gamma table setting
        BOOLEAN bHdrEnable = FALSE;
        SetGammaTableProp(mapi_display_datatype::E_MAPI_HDR_ENABLE, &bHdrEnable, sizeof(BOOLEAN));
        RefreshGammaTable();
        #endif

        //msAPI_SendVideoEvent(E_MAPI_EVENT_VIDEO_STATUS, m_enDstWin, E_MAPI_VIDEO_OPEN_HDR_RUNNING, 0);

        if(m_stHdrSettting[m_enDstWin].bOpenHdrAutoLevelEnable == TRUE)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_HLG_AUTO);
        }
        else if(m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_LOW)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_HLG_LOW);
        }
        else if(m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_MIDDLE)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_HLG_MID);
        }
        else if(m_stHdrSettting[m_enDstWin].eOpenHdrManualLevel == E_MAPI_XC_HDR_HIGH)
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_HLG_HIGH);
        }
        else
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OFF);
        }

        eRet = E_MAPI_HDR_ERROR_SUCCESS;
    }
    else
    {
        #if 0 //by customer,need customer gamma table setting
        BOOLEAN bHdrEnable = FALSE;
        SetGammaTableProp(mapi_display_datatype::E_MAPI_HDR_ENABLE, &bHdrEnable, sizeof(BOOLEAN));
        RefreshGammaTable();
        #endif

        //msAPI_SendVideoEvent(E_MAPI_EVENT_VIDEO_STATUS, m_enDstWin, E_MAPI_VIDEO_HDR_STOP, 0);

        if((m_bPreHdrHwWorking == TRUE) || (m_bHdrInitialized == FALSE))
        {
            msAPI_SetHDRMode(PQ_MAIN_WINDOW, E_MAPI_PQL_HDR_OFF);
        }

        eRet = E_MAPI_HDR_ERROR_SUCCESS;
    }


    m_bPreHdrHwWorking = m_bHdrHwWorking;

    m_bHdrMetadataChanged = FALSE;
    m_bHdrInitialized = TRUE;

    return eRet;
#else

    // CFD disable Open / Dolby HDR
    XC_CFD_HDR stCfdHdr;
    memset(&stCfdHdr, 0, sizeof(XC_CFD_HDR));
    //stCfdHdr.u32Version = CFD_HDR_VERSION;
    stCfdHdr.u16Length = sizeof(XC_CFD_HDR);
    stCfdHdr.u8Win = m_enDstWin;
    stCfdHdr.u8HdrType = E_XC_CFD_HDR_TYPE_NONE;

    XC_CFD_CONTROL_INFO stCfdCtrl;
    memset(&stCfdCtrl, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrl.enCtrlType = E_XC_CFD_CTRL_TYPE_HDR;
    stCfdCtrl.pParam = &stCfdHdr;
    stCfdCtrl.u32ParamLen = sizeof(XC_CFD_HDR);

    MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrl);

    return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
#endif
    return E_MAPI_HDR_ERROR_DRIVER_NOT_SUPPORT;
}



BOOLEAN msAPI_FireCfd(void)
{
    #if 0
    if(IsActive() == MAPI_FALSE)
    {
        ERR_VIDEO_BASE("[%s][%d] Video base need to initialize\n", __FUNCTION__, __LINE__);
        return MAPI_FALSE;
    }
    #endif
    XC_ApiStatus stXcStatus;
    memset(&stXcStatus, 0, sizeof(XC_ApiStatus));
    MApi_XC_GetStatus(&stXcStatus, (m_enDstWin==SUB_WINDOW)?SUB_WINDOW:MAIN_WINDOW);

    XC_CFD_FIRE stCfdFire;
    memset(&stCfdFire, 0, sizeof(XC_CFD_FIRE));
    //stCfdFire.u32Version = CFD_FIRE_VERSION;
    stCfdFire.u16Length = sizeof(XC_CFD_FIRE);
    stCfdFire.u8Win = (U8)m_enDstWin;
    stCfdFire.u8InputSource = msAPI_SDK2PQInputSourcTypeTrans(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
    if (stCfdFire.u8InputSource == PQ_INPUT_SOURCE_HDMI && msAPI_GetHDMIMode() == FALSE)
    {
        stCfdFire.u8InputSource = PQ_INPUT_SOURCE_DVI;
    }
    stCfdFire.bIsRgbBypass = stXcStatus.bForceRGBin;
    stCfdFire.bIsHdMode = MDrv_PQ_CheckHDMode((PQ_WIN)m_enDstWin);

    XC_CFD_CONTROL_INFO stCfdCtrl;
    memset(&stCfdCtrl, 0, sizeof(XC_CFD_CONTROL_INFO));
    stCfdCtrl.enCtrlType = E_XC_CFD_CTRL_TYPE_FIRE;
    stCfdCtrl.pParam = &stCfdFire;
    stCfdCtrl.u32ParamLen = sizeof(XC_CFD_FIRE);

    if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrl) == E_APIXC_RET_OK)
    {
        return TRUE;
    }

    return FALSE;
}


BOOLEAN msAPI_HDR_GetHDRMetaData(sHDR_METADATA *pstHDRMetadata)
{
    return MDrv_HDMI_GetHDRMetaData(pstHDRMetadata);
}

#if 0
BOOLEAN msAPI_HDR_GetAviInfoFrameData(ST_MAPI_HDR_HDMIAVI_INFOFRAME *stAviInfoFrame)
{
    memset(stAviInfoFrame, 0, sizeof(ST_MAPI_HDR_HDMIAVI_INFOFRAME));
    stAviInfoFrame->PixelFormat = PIXEL_FORMAT(m_stHdmiPacketAviInforFrameData[0]);
    stAviInfoFrame->Colorimetry = COLORIMETRY(m_stHdmiPacketAviInforFrameData[1]);
    stAviInfoFrame->ExtendedColorimetry = EXTENDED_COLORIMETRY(m_stHdmiPacketAviInforFrameData[2]);
    stAviInfoFrame->RgbQuantizationRange = RGB_QUANTIZATION_RANGE(m_stHdmiPacketAviInforFrameData[2]);
    stAviInfoFrame->YccQuantizationRange = YCC_QUANTIZATION_RANGE(m_stHdmiPacketAviInforFrameData[4]);
    stAviInfoFrame->StaticMetadataDescriptorID = 0;
    return TRUE;
}
#endif



#define IsHDMIColorRangeLimitFormat(width,height,interlace) ((720 == width) && (240 == height) && (FALSE == interlace)) \
    || ((720 == width) && (288 == height) && (FALSE == interlace)) \
    || ((720 == width) && (480 == height) && (FALSE == interlace)) \
    || ((720 == width) && (576 == height) && (FALSE == interlace)) \
    || ((1440 == width) && (240 == height) && (FALSE == interlace)) \
    || ((1440 == width) && (288 == height) && (FALSE == interlace)) \
    || ((1440 == width) && (480 == height) && (FALSE == interlace)) \
    || ((1440 == width) && (576 == height) && (FALSE == interlace)) \
    || ((1280 == width) && (720 == height) && (FALSE == interlace)) \
    || ((1920 == width) && (1080 == height) && (FALSE == interlace)) \
    || ((2880 == width) && (240 == height) && (FALSE == interlace)) \
    || ((2880 == width) && (288 == height) && (FALSE == interlace)) \
    || ((2880 == width) && (480 == height) && (FALSE == interlace)) \
    || ((2880 == width) && (576 == height) && (FALSE == interlace)) \
    || ((720 == width) && (480 == height) && (TRUE == interlace)) \
    || ((720 == width) && (576 == height) && (TRUE == interlace)) \
    || ((1440 == width) && (480 == height) && (TRUE == interlace)) \
    || ((1440 == width) && (576 == height) && (TRUE == interlace)) \
    || ((1920 == width) && (1080 == height) && (TRUE == interlace)) \
    || ((2880 == width) && (480 == height) && (TRUE == interlace)) \
    || ((2880 == width) && (576 == height) && (TRUE == interlace))


#if 0
BOOLEAN msAPI_SetHdmiCfd(SCALER_WIN eWindow)
{
    PCMode_Info stPcmode_info[2];
    //stPcmode_info[eWindow] = MApp_PCMode_LoadModeToLocal(eWindow);

#if defined(UFO_XC_HDR) && defined(UFO_XC_HDR_VERSION) && (UFO_XC_HDR_VERSION >= 2)
    if (MApi_XC_HDMI_GetHdmiType(stSystemInfo[eWindow].enInputSourceType) == E_HDMI_STATUS_HDMI)
    {
        BOOL bInterlace = ((stPcmode_info[eWindow].sModeParseInputInfo.u8SyncStatus & XC_MD_INTERLACE_BIT)!=0)? TRUE : FALSE;

        XC_CFD_HDMI stCfdHdmi;
        memset(&stCfdHdmi, 0, sizeof(XC_CFD_HDMI));
        stCfdHdmi.u32Version = CFD_HDMI_VERSION;
        stCfdHdmi.u16Length = sizeof(XC_CFD_HDMI);

        stCfdHdmi.u8Win = eWindow;

        const HDMI_PACKET_INFO_t *m_stHdmiPacketInfo = MApi_XC_HDMI_GetPacketInfo();

        if ((m_stHdmiPacketInfo->enPKT_Value.PKT_AVI_VALUE != 0) && (MDrv_HDMI_Get_AVIInfoFrameVer() == E_AVI_INFOFRAME_VERSION2))
        {
            if (MDrv_HDMI_Get_ColorRange() == E_HDMI_COLOR_RANGE_FULL)
            {
                stCfdHdmi.bIsFullRange = TRUE;
            }
            else if (MDrv_HDMI_Get_ColorRange() == E_HDMI_COLOR_RANGE_LIMIT)
            {
                stCfdHdmi.bIsFullRange = FALSE;
            }
            else
            {
#if 0//((STB_ENABLE == 0) || (ENABLE_HDMI_RX == 1))
                if (MS_HDMI_CONTENT_Graphics == MDrv_HDMI_Get_Content_Type())
                {
                    stCfdHdmi.bIsFullRange = TRUE;
                }
                else
#endif
                {
                    // check whether color range limit format
                    if (IsHDMIColorRangeLimitFormat(stPcmode_info[eWindow].sModeParseInputInfo.sDVI_HDMI_DE_Info.width, stPcmode_info[eWindow].sModeParseInputInfo.sDVI_HDMI_DE_Info.height, bInterlace) == TRUE)
                    {
                        stCfdHdmi.bIsFullRange = FALSE;
                    }
                    else
                    {
                        stCfdHdmi.bIsFullRange = TRUE;
                    }
                }
            }
        }
        else if (IsHDMIColorRangeLimitFormat(stPcmode_info[eWindow].sModeParseInputInfo.sDVI_HDMI_DE_Info.width, stPcmode_info[eWindow].sModeParseInputInfo.sDVI_HDMI_DE_Info.height, bInterlace) == TRUE)
        {
            stCfdHdmi.bIsFullRange = FALSE;
        }
        else
        {
            stCfdHdmi.bIsFullRange = TRUE;
        }

#if 0//todo
        /// AVI infoframe
        ST_MAPI_HDR_HDMIAVI_INFOFRAME stAviInfoframe;
        msAPI_HDR_GetAviInfoFrameData(&stAviInfoframe);
        stCfdHdmi.u8PixelFormat = stAviInfoframe.PixelFormat;
        stCfdHdmi.u8Colorimetry = stAviInfoframe.Colorimetry;
        stCfdHdmi.u8ExtendedColorimetry = stAviInfoframe.ExtendedColorimetry;
        stCfdHdmi.u8RgbQuantizationRange = stAviInfoframe.RgbQuantizationRange;
        stCfdHdmi.u8YccQuantizationRange = stAviInfoframe.YccQuantizationRange;
#endif
        sHDR_METADATA stHdrInfoframe;
        memset((void *)&stHdrInfoframe, 0, sizeof(sHDR_METADATA));
        if (msAPI_HDR_GetHDRMetaData(&stHdrInfoframe) == TRUE)
        {
            stCfdHdmi.bHDRInfoFrameValid = TRUE;
            stCfdHdmi.u8EOTF = stHdrInfoframe.u8EOTF;
            stCfdHdmi.u8SMDID = stHdrInfoframe.u8Static_Metadata_ID;
            stCfdHdmi.u16Display_Primaries_x[0] = stHdrInfoframe.u16Display_Primaries_X[0];
            stCfdHdmi.u16Display_Primaries_x[1] = stHdrInfoframe.u16Display_Primaries_X[1];
            stCfdHdmi.u16Display_Primaries_x[2] = stHdrInfoframe.u16Display_Primaries_X[2];
            stCfdHdmi.u16Display_Primaries_y[0] = stHdrInfoframe.u16Display_Primaries_Y[0];
            stCfdHdmi.u16Display_Primaries_y[1] = stHdrInfoframe.u16Display_Primaries_Y[1];
            stCfdHdmi.u16Display_Primaries_y[2] = stHdrInfoframe.u16Display_Primaries_Y[2];
            stCfdHdmi.u16White_point_x = stHdrInfoframe.u16White_Point_X;
            stCfdHdmi.u16White_point_y = stHdrInfoframe.u16White_Point_Y;
            stCfdHdmi.u16MasterPanelMaxLuminance = stHdrInfoframe.u16Max_Display_Mastering_Luminance;
            stCfdHdmi.u16MasterPanelMinLuminance = stHdrInfoframe.u16Min_Display_Mastering_Luminance;
            stCfdHdmi.u16MaxContentLightLevel = stHdrInfoframe.u16Maximum_Content_Light_Level;
            stCfdHdmi.u16MaxFrameAvgLightLevel = stHdrInfoframe.u16Maximum_Frame_Average_Light_Level;
        }
        else
        {
            stCfdHdmi.bHDRInfoFrameValid = FALSE;
        }

        XC_CFD_CONTROL_INFO stCfdCtrlInfo;
        memset(&stCfdCtrlInfo, 0, sizeof(XC_CFD_CONTROL_INFO));
        stCfdCtrlInfo.enCtrlType = E_XC_CFD_CTRL_TYPE_HDMI;
        stCfdCtrlInfo.pParam = &stCfdHdmi;
        stCfdCtrlInfo.u32ParamLen = sizeof(XC_CFD_HDMI);

        if (MApi_XC_HDR_Control(E_XC_HDR_CTRL_CFD_CONTROL, &stCfdCtrlInfo) == E_APIXC_RET_OK)
        {
            return TRUE;
        }

        return FALSE;
    }
    else
    {
        return FALSE;
    }
#endif

    return TRUE;
}
#endif

#endif //#if (ENABLE_HDR)
#undef MSAPI_HDR_C_
