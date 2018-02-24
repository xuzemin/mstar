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
#define _VERSION_CHECK_C_



#include "util_checkversion.h"


//MiddleWare Include
#if ENABLE_SUBTITLE
#include "msAPI_Subtitle_Pub.h"
#endif

#if ENABLE_TTX
#include "msAPI_TTX.h"
#endif


#if(ENABLE_DTV)
#include "MApp_Dvb_SI.h" // "mapp_si.h"
#endif

#if ENABLE_DTV_EPG
#include "mapp_epgdb_public.h"
#endif

#if 0//(MS_SW_CUS_SEL==SW_CONFIG_TRUNK_ATSC)
#include "msAPI_cc_parser.h"
#endif

#if ENABLE_CI
#include "msAPI_CI.h"
#endif



//driver include
//#ifndef _API_XC_ACE_H_
#include "apiXC_Ace.h"
//#endif

//Driver Include
//#ifndef _API_XC_ACE_H_
#include "apiXC_Ace.h"
//#endif

//#ifndef _DRVAUDIO_H_
#include "drvAUDIO.h"
//#endif

#include "drvAVD.h"

//#ifndef _DRVBDMA_H_
#include "drvBDMA.h"
//#endif

#if ENABLE_CEC
#include "apiCEC.h"
#endif

//#ifndef  _DRV_CPU_H_
#include "drvCPU.h"
//#endif

//#ifndef _DRVDDC2BI_H_
 #include "drvDDC2BI.h"
//#endif

//#ifndef _API_XC_DLC_H_
#include "apiXC_Dlc.h"
//#endif

//#ifndef __API_DMX_H__
#include "apiDMX.h"
//#endif

//#ifndef __DRV_DSCMB_H__
//mark temp
//#include "drvDSCMB.h"
//#endif

//#ifndef _DRV_SERFLASH_H_
#include "drvSERFLASH.h"
//#endif

//#ifndef _API_GFX_H_
#include "apiGFX.h"
//#endif

//#ifndef _API_GOP_H_
#include "apiGOP.h"
//#endif

//#ifdef __DRVGPIO_H__
//temp mark
//#include "drvGPIO.h"
//#endif

//#ifdef DRVXC_HDMI_IF_H
#include "drvXC_IOPort.h"
#include "apiXC.h"
#include "drvXC_HDMI_if.h"
//#endif

//#ifndef _DRVIPAUTH_H_
//temp mark
//#include "drvIPAUTH.h"
//#endif

//#ifndef _DRV_IR_H_
#ifndef MSOS_TYPE_LINUX
#include "drvIR.h"
#endif
//#endif

//#ifndef _API_JPEG_H_
#include "apiJPEG.h"
//#endif

//#ifndef _DRV_MVOP_H_
#include "drvMVOP.h"
//#endif

#if ENABLE_CI
//#ifdef _DRV_PCMCIA_H_
#include "drvPCMCIA.h"
//#endif
#endif

//#ifndef _DRV_PM_H_
#include "drvPM.h"
//#endif

//#ifndef _API_XC_PANEL_H_
#include "apiPNL.h"
//#endif

//#ifndef _DRVPQ_H_
#include "drvPQ.h"
//#endif

//#ifndef _DRV_TEMP_H_
#include "drvPWM.h"
//#endif

//#ifndef _DRVTSP_H_
#include "drvTSP.h"
//#endif

//#ifndef _DRV_VBI_H
//temp mark
//#include "drvVBI.h"
//#endif

//#ifndef _API_VDEC_H_
#include "apiVDEC.h"
//#endif

//#ifndef _DRVTVENCODER_H
#include "drvTVEncoder.h"
//#endif

//#ifndef _API_XC_H_
//#include "apiXC.h"
//#endif


//middle ware layer
MS_U16 MW_Name[MW_Number][5]={
                                  #ifdef _MSAPI_SUBTITLE_H
                                                    MSIF_SUB_LIB_CODE,
                                  #endif

                                  #ifdef TT_API_H
                                                  MSIF_TTX_LIB_CODE,
                                  #endif


                                  #ifdef MAPP_EPGDB_PUBLIC_H
                                                  MSIF_EPG_LIB_CODE,
                                  #endif


                                  #if 0//(MS_SW_CUS_SEL==SW_CONFIG_TRUNK_ATSC)
                                                 MSIF_CC_LIB_CODE,
                                  #endif

                                  #ifdef _MSAPI_CI_H
                                                 MSIF_CI_LIB_CODE,
                                  #endif

                                               {'F','F','F','F', }
                                        };

    MS_U16 MW_LibVersion[MW_Number][3]= {
                                   #ifdef _MSAPI_SUBTITLE_H
                                                    MSIF_SUB_LIBVER,
                                  #endif

                                  #ifdef _TT_API25_H
                                                   MSIF_TTX_LIBVER,
                                  #endif

                                  #ifdef MAPP_EPGDB_PUBLIC_H
                                                  MSIF_EPG_LIBVER,
                                  #endif

                                  #if 0//(MS_SW_CUS_SEL==SW_CONFIG_TRUNK_ATSC)
                                              MSIF_CC_LIBVER,
                                  #endif

                                  #ifdef _MSAPI_CI_H
                                                 MSIF_CI_LIBVER,
                                  #endif

                                                 {'F','F', }
                                               };

     MS_U16 MW_BuildNumber[MW_Number][3]={
                                  #ifdef _MSAPI_SUBTITLE_H
                                                    MSIF_SUB_BUILDNUM,
                                  #endif

                                  #ifdef TT_API_H
                                                   MSIF_TTX_BUILDNUM,
                                  #endif

                                  #ifdef MAPP_EPGDB_PUBLIC_H
                                                  MSIF_EPG_BUILDNUM,
                                  #endif

                                  #if 0//(MS_SW_CUS_SEL==SW_CONFIG_TRUNK_ATSC)
                                              MSIF_CC_BUILDNUM,
                                  #endif

                                  #ifdef _MSAPI_CI_H
                                                 MSIF_CI_BUILDNUM,
                                  #endif
                                                 {'F','F', }
                                              };

     MS_U16 MW_ChangeList[MW_Number][9]={
                                  #ifdef _MSAPI_SUBTITLE_H
                                                    MSIF_SUB_CHANGELIST,
                                  #endif

                                  #ifdef TT_API_H
                                                   MSIF_TTX_CHANGELIST,
                                  #endif

                                  #ifdef MAPP_EPGDB_PUBLIC_H
                                                  MSIF_EPG_CHANGELIST,
                                  #endif

                                  #if 0//(MS_SW_CUS_SEL==SW_CONFIG_TRUNK_ATSC)
                                              MSIF_CC_CHANGELIST,
                                  #endif

                                 #ifdef _MSAPI_CI_H
                                                 MSIF_CI_CHANGELIST,
                                 #endif
                                              {'F','F','F','F','F','F','F','F', }
                                             };

     MS_U16 MW_Match[MW_Number]={1};



//driver layer
MS_U16 drv_Name[Drv_Number][5]={
                                       #ifdef _API_XC_ACE_H_
                                              MSIF_ACE_LIB_CODE,
                                       #endif

                                       #ifdef _DRVAUDIO_H_
                                               MSIF_AUDIO_LIB_CODE,
                                       #endif

                                       #ifndef _DRV_AVD_H_
                                                MSIF_AVD_LIB_CODE,
                                       #endif

                                       #ifdef _DRVBDMA_H_
                                                MSIF_BDMA_LIB_CODE,
                                       #endif

                                       #ifdef _APICEC_H_
                                                MSIF_CEC_LIB_CODE,
                                       #endif

                                       #ifdef  _DRV_CPU_H_
                                                 MSIF_COPRO_LIB_CODE,
                                       #endif

                                       #ifdef _DRVDDC2BI_H_
                                                MSIF_DDC_LIB_CODE,
                                       #endif

                                       #ifdef _API_XC_DLC_H_
                                                MSIF_DLC_LIB_CODE,
                                       #endif

                                       #ifdef __API_DMX_H__
                                                MSIF_DMX_LIB_CODE,
                                       #endif

                                       #ifdef __DRV_DSCMB_H__
                                              MSIF_DSMB_LIB_CODE,
                                       #endif

                                       #ifdef _DRV_SERFLASH_H_
                                              MSIF_SPIF_LIB_CODE,
                                       #endif

                                       #ifdef _API_GFX_H_
                                                MSIF_GFX_LIB_CODE,
                                       #endif

                                       #ifdef _API_GOP_H_
                                                MSIF_GOP_LIB_CODE,
                                       #endif

                                       #ifdef __DRVGPIO_H__
                                                MSIF_GPIO_LIB_CODE,
                                       #endif

                                       #ifdef DRVXC_HDMI_IF_H
                                                MSIF_HDMI_LIB_CODE,
                                       #endif

                                       #ifdef _DRVIPAUTH_H_
                                               MSIF_IPAUTH_LIB_CODE,
                                       #endif

                                       #ifdef _DRV_IR_H_
                                                MSIF_IR_LIB_CODE,
                                       #endif

                                       #ifdef _API_JPEG_H_
                                                MSIF_JPEG_LIB_CODE,
                                       #endif

                                       #ifdef _DRV_MVOP_H_
                                                MSIF_MVOP_LIB_CODE,
                                       #endif

                                       #ifdef _DRV_PCMCIA_H_
                                                MSIF_PCMCIA_LIB_CODE,
                                       #endif

                                       #ifdef _DRV_PM_H_
                                                MSIF_PM_LIB_CODE,
                                       #endif

                                       #ifdef _API_XC_PANEL_H_
                                                MSIF_PNL_LIB_CODE,
                                       #endif

                                       #ifdef _DRVPQ_H_
                                                MSIF_PQ_LIB_CODE,
                                       #endif

                                       #ifdef _DRV_TEMP_H_
                                                MSIF_PWM_LIB_CODE,
                                       #endif

                                       #ifdef _DRVTSP_H_
                                                MSIF_TSP_LIB_CODE,
                                       #endif

                                       #ifdef _DRV_VBI_H
                                                MSIF_VBI_LIB_CODE,
                                       #endif

                                       #ifdef _API_VDEC_H_
                                                MSIF_VDEC_LIB_CODE,
                                       #endif

                                       #ifdef _DRVTVENCODER_H
                                                MSIF_VE_LIB_CODE,
                                       #endif

                                       #ifdef _API_XC_H_
                                                MSIF_XC_LIB_CODE,
                                       #endif

                                            {'F','F','F','F', }
                                     };

 MS_U16 drv_LibVersion[Drv_Number][3]= {
                                       #ifdef _API_XC_ACE_H_
                                               MSIF_ACE_LIBVER,
                                       #endif

                                       #ifdef _DRVAUDIO_H_
                                               MSIF_AUDIO_LIBVER,
                                       #endif

#ifndef _DRV_AVD_H_
                                      MSIF_AVD_LIBVER,
#endif

                                       #ifdef _DRVBDMA_H_
                                                MSIF_BDMA_LIBVER,
                                       #endif

                                       #ifdef _APICEC_H_
                                                MSIF_CEC_LIBVER,
                                       #endif

                                       #ifdef  _DRV_CPU_H_
                                                 MSIF_COPRO_LIBVER,
                                       #endif

                                       #ifdef _DRVDDC2BI_H_
                                                MSIF_DDC_LIBVER,
                                       #endif

                                       #ifdef _API_XC_DLC_H_
                                                MSIF_DLC_LIBVER,
                                       #endif

                                       #ifdef __API_DMX_H__
                                                MSIF_DMX_LIBVER,
                                       #endif

                                       #ifdef __DRV_DSCMB_H__
                                             MSIF_DSMB_LIBVER,
                                       #endif

                                       #ifdef _DRV_SERFLASH_H_
                                              MSIF_SPIF_LIBVER,
                                       #endif

                                       #ifdef _API_GFX_H_
                                                MSIF_GFX_LIBVER,
                                       #endif

                                       #ifdef _API_GOP_H_
                                                MSIF_GOP_LIBVER,
                                       #endif

                                       #ifdef __DRVGPIO_H__
                                                MSIF_GPIO_LIBVER,
                                       #endif

                                       #ifdef DRVXC_HDMI_IF_H
                                                MSIF_HDMI_LIBVER,
                                       #endif

                                       #ifdef _DRVIPAUTH_H_
                                               MSIF_IPAUTH_LIBVER,
                                       #endif

                                       #ifdef _DRV_IR_H_
                                                MSIF_IR_LIBVER,
                                       #endif

                                       #ifdef _API_JPEG_H_
                                                MSIF_JPEG_LIBVER,
                                       #endif

                                       #ifdef _DRV_MVOP_H_
                                                MSIF_MVOP_LIBVER,
                                       #endif

                                       #ifdef _DRV_PCMCIA_H_
                                                MSIF_PCMCIA_LIBVER,
                                       #endif

                                       #ifdef _DRV_PM_H_
                                                MSIF_PM_LIBVER,
                                       #endif

                                       #ifdef _API_XC_PANEL_H_
                                                MSIF_PNL_LIBVER,
                                       #endif

                                       #ifdef _DRVPQ_H_
                                                MSIF_PQ_LIBVER,
                                       #endif

                                       #ifdef _DRV_TEMP_H_
                                                MSIF_PWM_LIBVER,
                                       #endif

                                       #ifdef _DRVTSP_H_
                                                MSIF_TSP_LIBVER,
                                       #endif

                                       #ifdef _DRV_VBI_H
                                                MSIF_VBI_LIBVER,
                                       #endif

                                       #ifdef _API_VDEC_H_
                                                MSIF_VDEC_LIBVER,
                                       #endif

                                       #ifdef _DRVTVENCODER_H
                                                MSIF_VE_LIBVER,
                                       #endif

                                       #ifdef _API_XC_H_
                                                MSIF_XC_LIBVER,
                                       #endif

                                              {'F','F', }
                                            };

  MS_U16 drv_BuildNumber[Drv_Number][3]={
                                       #ifdef _API_XC_ACE_H_
                                               MSIF_ACE_BUILDNUM,
                                       #endif

                                       #ifdef _DRVAUDIO_H_
                                               MSIF_AUDIO_BUILDNUM,
                                       #endif

#ifndef _DRV_AVD_H_
                                        MSIF_AVD_BUILDNUM,
#endif

                                       #ifdef _DRVBDMA_H_
                                                MSIF_BDMA_BUILDNUM,
                                       #endif

                                       #ifdef _APICEC_H_
                                                MSIF_CEC_BUILDNUM,
                                       #endif

                                       #ifdef  _DRV_CPU_H_
                                                 MSIF_COPRO_BUILDNUM,
                                       #endif

                                       #ifdef _DRVDDC2BI_H_
                                                MSIF_DDC_BUILDNUM,
                                       #endif

                                       #ifdef _API_XC_DLC_H_
                                                MSIF_DLC_BUILDNUM,
                                       #endif

                                       #ifdef __API_DMX_H__
                                                MSIF_DMX_BUILDNUM,
                                       #endif

                                       #ifdef __DRV_DSCMB_H__
                                              MSIF_DSMB_BUILDNUM,
                                       #endif

                                       #ifdef _DRV_SERFLASH_H_
                                              MSIF_SPIF_BUILDNUM,
                                       #endif

                                       #ifdef _API_GFX_H_
                                                MSIF_GFX_BUILDNUM,
                                       #endif

                                       #ifdef _API_GOP_H_
                                                MSIF_GOP_BUILDNUM,
                                       #endif

                                       #ifdef __DRVGPIO_H__
                                                MSIF_GPIO_BUILDNUM,
                                       #endif

                                       #ifdef DRVXC_HDMI_IF_H
                                                MSIF_HDMI_BUILDNUM,
                                       #endif

                                       #ifdef _DRVIPAUTH_H_
                                               MSIF_IPAUTH_BUILDNUM,
                                       #endif

                                       #ifdef _DRV_IR_H_
                                                MSIF_IR_BUILDNUM,
                                       #endif

                                       #ifdef _API_JPEG_H_
                                                MSIF_JPEG_BUILDNUM,
                                       #endif

                                       #ifdef _DRV_MVOP_H_
                                                MSIF_MVOP_BUILDNUM,
                                       #endif

                                       #ifdef _DRV_PCMCIA_H_
                                                MSIF_PCMCIA_BUILDNUM,
                                       #endif

                                       #ifdef _DRV_PM_H_
                                                MSIF_PM_BUILDNUM,
                                       #endif

                                       #ifdef _API_XC_PANEL_H_
                                                MSIF_PNL_BUILDNUM,
                                       #endif

                                       #ifdef _DRVPQ_H_
                                                MSIF_PQ_BUILDNUM,
                                       #endif

                                       #ifdef _DRV_TEMP_H_
                                                MSIF_PWM_BUILDNUM,
                                       #endif

                                       #ifdef _DRVTSP_H_
                                                MSIF_TSP_BUILDNUM,
                                       #endif

                                       #ifdef _DRV_VBI_H
                                                MSIF_VBI_BUILDNUM,
                                       #endif

                                       #ifdef _API_VDEC_H_
                                                MSIF_VDEC_BUILDNUM,
                                       #endif

                                       #ifdef _DRVTVENCODER_H
                                                MSIF_VE_BUILDNUM,
                                       #endif

                                       #ifdef _API_XC_H_
                                                MSIF_XC_BUILDNUM,
                                       #endif

                                              {'F','F', }
                                           };

  MS_U16 drv_ChangeList[Drv_Number][9]={
                                       #ifdef _API_XC_ACE_H_
                                               MSIF_ACE_CHANGELIST,
                                       #endif

                                       #ifdef _DRVAUDIO_H_
                                               MSIF_AUDIO_CHANGELIST,
                                       #endif

#ifndef _DRV_AVD_H_
                                      MSIF_AVD_CHANGELIST,
#endif

                                       #ifdef _DRVBDMA_H_
                                                MSIF_BDMA_CHANGELIST,
                                       #endif

                                       #ifdef _APICEC_H_
                                                MSIF_CEC_CHANGELIST,
                                       #endif

                                       #ifdef  _DRV_CPU_H_
                                                 MSIF_COPRO_CHANGELIST,
                                       #endif

                                       #ifdef _DRVDDC2BI_H_
                                                MSIF_DDC_CHANGELIST,
                                       #endif

                                       #ifdef _API_XC_DLC_H_
                                                MSIF_DLC_CHANGELIST,
                                       #endif

                                       #ifdef __API_DMX_H__
                                                MSIF_DMX_CHANGELIST,
                                       #endif

                                       #ifdef __DRV_DSCMB_H__
                                              MSIF_DSMB_CHANGELIST,
                                       #endif

                                       #ifdef _DRV_SERFLASH_H_
                                              MSIF_SPIF_CHANGELIST,
                                       #endif

                                       #ifdef _API_GFX_H_
                                                MSIF_GFX_CHANGELIST,
                                       #endif

                                       #ifdef _API_GOP_H_
                                                MSIF_GOP_CHANGELIST,
                                       #endif

                                       #ifdef __DRVGPIO_H__
                                                MSIF_GPIO_CHANGELIST,
                                       #endif

                                       #ifdef DRVXC_HDMI_IF_H
                                                MSIF_HDMI_CHANGELIST,
                                       #endif

                                       #ifdef _DRVIPAUTH_H_
                                               MSIF_IPAUTH_CHANGELIST,
                                       #endif

                                       #ifdef _DRV_IR_H_
                                                MSIF_IR_CHANGELIST,
                                       #endif

                                       #ifdef _API_JPEG_H_
                                                MSIF_JPEG_CHANGELIST,
                                       #endif

                                       #ifdef _DRV_MVOP_H_
                                                MSIF_MVOP_CHANGELIST,
                                       #endif

                                       #ifdef _DRV_PCMCIA_H_
                                                MSIF_PCMCIA_CHANGELIST,
                                       #endif

                                       #ifdef _DRV_PM_H_
                                                MSIF_PM_CHANGELIST,
                                       #endif

                                       #ifdef _API_XC_PANEL_H_
                                                MSIF_PNL_CHANGELIST,
                                       #endif

                                       #ifdef _DRVPQ_H_
                                                MSIF_PQ_CHANGELIST,
                                       #endif

                                       #ifdef _DRV_TEMP_H_
                                                MSIF_PWM_CHANGELIST,
                                       #endif

                                       #ifdef _DRVTSP_H_
                                                MSIF_TSP_CHANGELIST,
                                       #endif

                                       #ifdef _DRV_VBI_H
                                                MSIF_VBI_CHANGELIST,
                                       #endif

                                       #ifdef _API_VDEC_H_
                                                MSIF_VDEC_CHANGELIST,
                                       #endif

                                       #ifdef _DRVTVENCODER_H
                                                MSIF_VE_CHANGELIST,
                                       #endif

                                       #ifdef _API_XC_H_
                                                MSIF_XC_CHANGELIST,
                                       #endif

                                           {'F','F','F','F','F','F','F','F', }
                                          };

  MS_U16 drv_Match[Drv_Number]={0};



//for mw
MSIF_Version *pSUB_Version;
MSIF_Version *pTTX_Version;
MSIF_Version *pEPG_Version;
MSIF_Version *pSI_Version;
MSIF_Version *pCC_Version;
MSIF_Version *pCI_Version;

//for driver
MSIF_Version *pACE_Version;
MSIF_Version *pAUDIO_Version;
MSIF_Version *pAVD_Version;
MSIF_Version *pBDMA_Version;
MSIF_Version *pCEC_Version;
MSIF_Version *pCPU_Version;
MSIF_Version *pDDC2BI_Version;
MSIF_Version *pDLC_Version;
MSIF_Version *pDMX_Version;
MSIF_Version *pDSCMB_Version;
MSIF_Version *pFLASH_Version;
MSIF_Version *pGFX_Version;
MSIF_Version *pGOP_Version;
MSIF_Version *pGPIO_Version;
MSIF_Version *pHDMI_Version;
MSIF_Version *pIPAUTH_Version;
MSIF_Version *pIR_Version;
MSIF_Version *pJPEG_Version;
MSIF_Version *pMVOP_Version;
MSIF_Version *pPCMCIA_Version;
MSIF_Version *pPM_Version;
MSIF_Version *pPNL_Version;
MSIF_Version *pPQ_Version;
MSIF_Version *pPWM_Version;
MSIF_Version *pTSP_Version;
MSIF_Version *pVBI_Version;
MSIF_Version *pVDEC_Version;
MSIF_Version *pVE_Version;
MSIF_Version *pXC_Version;


MS_U16 MW_Max;
MS_U16 Drv_Max;

void MApp_CountMax(void)
{
    MS_U16 i=0;
    for(i=0;i<MW_Number;i++)
    {
        if((MW_Name[i][0]=='F')&&(MW_Name[i][1]=='F'))
        {
            MW_Max=i;
           VERSION_DBG( printf("=======> mw_max = %d\n",MW_Max));
            break;
        }
    }
    i=0;
    for(i=0;i<Drv_Number;i++)
    {
        if((drv_Name[i][0]=='F')&&(drv_Name[i][1]=='F'))
        {
            Drv_Max=i;
            VERSION_DBG(printf("=======> drv_max = %d\n",Drv_Max));
            break;
        }
    }
}

void MApp_AllVersion_Init(void)
{

//MW
#ifdef _MSAPI_SUBTITLE_H
    msAPI_Subtitle_GetLibVer((const MSIF_Version**)&pSUB_Version);
#endif

#ifdef TT_API_H
    msAPI_TTX_GetLibVer((const MSIF_Version**)&pTTX_Version);
#endif
#ifdef MAPP_SI_H
    MApp_SI_GetLibVer((const MSIF_Version**)&pSI_Version);
#endif

#ifdef MAPP_EPGDB_PUBLIC_H
    #if ENABLE_DVB
    MApp_Epg_GetLibVer((const MSIF_Version**)&pEPG_Version);
    #endif
#endif


#if 0//(MS_SW_CUS_SEL==SW_CONFIG_TRUNK_ATSC)
    msAPI_CC_GetLibVer((const MSIF_Version**)&pCC_Version);
#endif


#ifdef _MSAPI_CI_H
    msAPI_CI_GetLibVer((const MSIF_Version**)&pCI_Version);
#endif



//driver
#ifdef _API_XC_ACE_H_
    MApi_XC_ACE_GetLibVer((const MSIF_Version**)&pACE_Version);
#endif

#ifdef _DRVAUDIO_H_
    MDrv_AUD_GetLibVer((const MSIF_Version**)&pAUDIO_Version);
#endif

#ifndef _DRV_AVD_H_
    MDrv_AVD_GetLibVer((const MSIF_Version**)&pAUDIO_Version);

#endif

#ifdef _DRVBDMA_H_
        MDrv_BDMA_GetLibVer((const MSIF_Version**)&pBDMA_Version);
#endif

#ifdef _APICEC_H_
         //mark temp
         MApi_CEC_GetLibVer((const MSIF_Version**)&pCEC_Version);
#endif

#ifdef  _DRV_CPU_H_
    //mark temp
    MDrv_COPRO_GetLibVer((const MSIF_Version**)&pCPU_Version);
#endif

#ifdef _DRVDDC2BI_H_
         MDrv_DDC2BI_GetLibVer((const MSIF_Version**)&pDDC2BI_Version);
#endif

#ifdef _API_XC_DLC_H_
         MApi_XC_DLC_GetLibVer((const MSIF_Version**)&pDLC_Version);
#endif

#ifdef __API_DMX_H__
         MApi_DMX_GetLibVer((const MSIF_Version**)&pDMX_Version);
#endif

#ifdef __DRV_DSCMB_H__
      //mark temp
      MDrv_DSCMB_GetLibVer((const MSIF_Version**)&pDSCMB_Version);
#endif

#ifdef _DRV_SERFLASH_H_
       MDrv_SERFLASH_GetLibVer((const MSIF_Version**)&pFLASH_Version);
#endif

#ifdef _API_GFX_H_
          MApi_GFX_GetLibVer((const MSIF_Version**)&pGFX_Version);
#endif

#ifdef _API_GOP_H_
        MApi_GOP_GetLibVer((const MSIF_Version**)&pGOP_Version);
#endif

#ifdef __DRVGPIO_H__
         //mark temp
         MDrv_GPIO_GetLibVer((const MSIF_Version**)&pGPIO_Version);
#endif

#ifdef DRVXC_HDMI_IF_H
        MDrv_HDMI_GetLibVer((const MSIF_Version**)&pHDMI_Version);
#endif

#ifdef _DRVIPAUTH_H_
        //mark temp
        MApp_IPAUTH_GetLibVer((const MSIF_Version**)&pIPAUTH_Version);
#endif

#ifdef _DRV_IR_H_
         //mark temp
         MDrv_IR_GetLibVer((const MSIF_Version**)&pIR_Version);
#endif

#ifdef _API_JPEG_H_
         MApi_JPEG_GetLibVer((const MSIF_Version**)&pJPEG_Version);
#endif

#ifdef _DRV_MVOP_H_
      MDrv_MVOP_GetLibVer((const MSIF_Version**)&pMVOP_Version);
#endif

#ifdef _DRV_PCMCIA_H_
         MDrv_PCMCIA_GetLibVer((const MSIF_Version**)&pPCMCIA_Version);
#endif

#ifdef _DRV_PM_H_
      MDrv_PM_GetLibVer((const MSIF_Version**)&pPM_Version);
#endif

#ifdef _API_XC_PANEL_H_
        MApi_PNL_GetLibVer((const MSIF_Version**)&pPNL_Version);
#endif

#ifdef _DRVPQ_H_
//         MDrv_PQ_GetLibVer((const MSIF_Version**)&pPQ_Version);
#endif

#ifdef _DRV_TEMP_H_
         MDrv_PWM_GetLibVer((const MSIF_Version**)&pPWM_Version);
#endif

#ifdef _DRVTSP_H_
        MDrv_TSP_GetLibVer((const MSIF_Version**)&pTSP_Version);
#endif

#ifdef _DRV_VBI_H
       //mark temp
       MDrv_VBI_GetLibVer((const MSIF_Version**)&pVBI_Version);
#endif

#ifdef _API_VDEC_H_
       MApi_VDEC_GetLibVer((const MSIF_Version**)&pVDEC_Version);
#endif

#ifdef _DRVTVENCODER_H
  #if (ENABLE_VE)
        MDrv_VE_GetLibVer((const MSIF_Version**)&pVE_Version);
  #endif
#endif

#ifdef _API_XC_H_
      MApi_XC_GetLibVer((const MSIF_Version**)&pXC_Version);
#endif

}


void  MApp_CheckAllVersion(void)
{
    VERSION_DBG(printf("\n============ Check LIB Version ==========="));
     int index=0;

#ifdef _MSAPI_SUBTITLE_H
    if(MApp_CompareVersion(pSUB_Version,&MW_ChangeList[index][0]))
    {
        MW_Match[index]=1;
       VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]));
    }
    else
    {
        MW_Match[index]=0;
        VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3],&(pSUB_Version->MW.changelist)));
        VERSION_DBG(printf("%c%c%c%c  Interface  = ",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3]));
        VERSION_DBG(printf("%c", MW_ChangeList[index][0]));
        VERSION_DBG(printf("%c", MW_ChangeList[index][1]));
        VERSION_DBG(printf("%c", MW_ChangeList[index][2]));
        VERSION_DBG(printf("%c", MW_ChangeList[index][3]));
        VERSION_DBG(printf("%c", MW_ChangeList[index][4]));
        VERSION_DBG(printf("%c", MW_ChangeList[index][5]));
        VERSION_DBG(printf("%c", MW_ChangeList[index][6]));
        VERSION_DBG(printf("%c\n", MW_ChangeList[index][7]));

        printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]);
    }
        // printf("MW_matchp[%d] = %d\n",index,MW_Match[index]);
   index=index+1;
#endif

#ifdef TT_API_H
      if(MApp_CompareVersion(pTTX_Version,&MW_ChangeList[index][0]))
      {
          MW_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]));
      }
      else
      {
          MW_Match[index]=0;
          VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3],&(pTTX_Version->MW.changelist)));
          VERSION_DBG(printf("%c%c%c%c  Interface  = ",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][0]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][1]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][2]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][4]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][5]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][6]));
          VERSION_DBG(printf("%c\n", MW_ChangeList[index][7]));



          printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]);
      }
        // printf("MW_matchp[%d] = %d\n",index,MW_Match[index]);
     index=index+1;


#endif

#ifdef MAPP_EPGDB_PUBLIC_H
      if(MApp_CompareVersion(pEPG_Version,&MW_ChangeList[index][0]))
      {
          MW_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]));
      }
      else
      {
          MW_Match[index]=0;
          VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3],&(pEPG_Version->MW.changelist)));
          VERSION_DBG(printf("%c%c%c%c  Interface  = ",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][0]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][1]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][2]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][4]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][5]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][6]));
          VERSION_DBG(printf("%c\n", MW_ChangeList[index][7]));



          printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]);
      }
       //  printf("MW_matchp[%d] = %d\n",index,MW_Match[index]);
     index=index+1;

#endif


#if 0//(MS_SW_CUS_SEL==SW_CONFIG_TRUNK_ATSC)
      if(MApp_CompareVersion(pCC_Version,&MW_ChangeList[index][0]))
      {
          MW_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]));
      }
      else
      {
          MW_Match[index]=0;
          VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3],&(pCC_Version->MW.changelist)));
          VERSION_DBG(printf("%c%c%c%c  Interface  = ",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][0]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][1]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][2]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][4]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][5]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][6]));
          VERSION_DBG(printf("%c\n", MW_ChangeList[index][7]));


          printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]);
      }
        // printf("MW_matchp[%d] = %d\n",index,MW_Match[index]);
     index=index+1;

#endif


#ifdef _MSAPI_CI_H
      if(MApp_CompareVersion(pCI_Version,&MW_ChangeList[index][0]))
      {
          MW_Match[index]=1;
        VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]));
      }
      else
      {
          MW_Match[index]=0;
          VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3],&(pCI_Version->MW.changelist)));
          VERSION_DBG(printf("%c%c%c%c  Interface  = ",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][0]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][1]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][2]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][3]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][4]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][5]));
          VERSION_DBG(printf("%c", MW_ChangeList[index][6]));
          VERSION_DBG(printf("%c\n", MW_ChangeList[index][7]));


          printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",MW_Name[index][0],MW_Name[index][1],MW_Name[index][2],MW_Name[index][3], MW_Match[index]);
      }
         //printf("MW_matchp[%d] = %d\n",index,MW_Match[index]);
     index=index+1;

#endif



//driver
index=0;
#ifdef _API_XC_ACE_H_
         if(MApp_CompareVersion(pACE_Version,&drv_ChangeList[index][0]))
         {
             drv_Match[index]=1;
           VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
         }
         else
         {
             drv_Match[index]=0;
             VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pACE_Version->MW.changelist)));
             VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
             VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));

             printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
         }
         //printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
        index=index+1;
#endif

#ifdef _DRVAUDIO_H_
         if(MApp_CompareVersion(pAUDIO_Version,&drv_ChangeList[index][0]))
         {
             drv_Match[index]=1;
            VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
         }
         else
         {
             drv_Match[index]=0;
             VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pAUDIO_Version->MW.changelist)));
             VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
             VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


             printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
         }
         //printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
        index=index+1;
#endif

#ifdef _DRVBDMA_H_
         if(MApp_CompareVersion(pBDMA_Version,&drv_ChangeList[index][0]))
         {
             drv_Match[index]=1;
             VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
         }
         else
         {
             drv_Match[index]=0;
             VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pBDMA_Version->MW.changelist)));
             VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
             VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


             printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
         }
         //printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
        index=index+1;
#endif

#ifdef _APICEC_H_
         if(MApp_CompareVersion(pCEC_Version,&drv_ChangeList[index][0]))
         {
             drv_Match[index]=1;
           VERSION_DBG( printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
         }
         else
         {
             drv_Match[index]=0;
             VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pCEC_Version->MW.changelist)));
             VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
             VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


             printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
         }
         //printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
        index=index+1;
#endif

#ifdef  _DRV_CPU_H_
     if(MApp_CompareVersion(pCPU_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pCPU_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
         //printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRVDDC2BI_H_
     if(MApp_CompareVersion(pDDC2BI_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pDDC2BI_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
        // printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _API_XC_DLC_H_
         if(MApp_CompareVersion(pDLC_Version,&drv_ChangeList[index][0]))
         {
             drv_Match[index]=1;
             VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
         }
         else
         {
             drv_Match[index]=0;
             VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pDLC_Version->MW.changelist)));
             VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
             VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
             VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


             printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
         }
        // printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
        index=index+1;
#endif

#ifdef __API_DMX_H__
     if(MApp_CompareVersion(pDMX_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pDMX_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
        // printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef __DRV_DSCMB_H__
      if(MApp_CompareVersion(pDSCMB_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pDSCMB_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
       // printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRV_SERFLASH_H_
     if(MApp_CompareVersion(pFLASH_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pFLASH_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
         //printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _API_GFX_H_
     if(MApp_CompareVersion(pGFX_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG( printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pGFX_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
       //  printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _API_GOP_H_
     if(MApp_CompareVersion(pGOP_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pGOP_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
       //  printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef __DRVGPIO_H__
     if(MApp_CompareVersion(pGPIO_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
       VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pGPIO_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
      //   printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef DRVXC_HDMI_IF_H
     if(MApp_CompareVersion(pHDMI_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pHDMI_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
     //    printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRVIPAUTH_H_
     if(MApp_CompareVersion(pIPAUTH_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pIPAUTH_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
      //   printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRV_IR_H_
     if(MApp_CompareVersion(pIR_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pIR_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
      //   printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _API_JPEG_H_
     if(MApp_CompareVersion(pJPEG_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG( printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pJPEG_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
     //    printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRV_MVOP_H_
     if(MApp_CompareVersion(pMVOP_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pMVOP_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
        // printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRV_PCMCIA_H_
     if(MApp_CompareVersion(pPCMCIA_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pPCMCIA_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
     //    printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRV_PM_H_
     if(MApp_CompareVersion(pPM_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pPM_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
    //     printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _API_XC_PANEL_H_
     if(MApp_CompareVersion(pPNL_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pPNL_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
     //    printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#if 0
#ifdef _DRVPQ_H_
     if(MApp_CompareVersion(pPQ_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG( printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pPQ_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
      //   printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif
#endif

#ifdef _DRV_TEMP_H_
     if(MApp_CompareVersion(pPWM_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pPWM_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
     //    printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRVTSP_H_
     if(MApp_CompareVersion(pTSP_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
         VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pTSP_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));

         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
     //    printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRV_VBI_H
     if(MApp_CompareVersion(pVBI_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
       VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pVBI_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
     //    printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _API_VDEC_H_
     if(MApp_CompareVersion(pVDEC_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
       VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pVDEC_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));

         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
       //  printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _DRVTVENCODER_H
     if(MApp_CompareVersion(pVE_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
       VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pVE_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
      //   printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif

#ifdef _API_XC_H_
     if(MApp_CompareVersion(pXC_Version,&drv_ChangeList[index][0]))
     {
         drv_Match[index]=1;
        VERSION_DBG(printf("---> %c%c%c%c MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3], drv_Match[index]));
     }
     else
     {
         drv_Match[index]=0;
         VERSION_DBG(printf("%c%c%c%c  Library     = %s\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],&(pXC_Version->MW.changelist)));
         VERSION_DBG(printf("%c%c%c%c  Interface  = ",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][0]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][1]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][2]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][3]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][4]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][5]));
         VERSION_DBG(printf("%c", drv_ChangeList[index][6]));
         VERSION_DBG(printf("%c\n", drv_ChangeList[index][7]));


         printf("---> %c%c%c%c VERSION is not MATCH!!(%d)\n",drv_Name[index][0],drv_Name[index][1],drv_Name[index][2],drv_Name[index][3],drv_Match[index]);
     }
      //   printf("drv_matchp[%d] = %d\n",index,drv_Match[index]);
    index=index+1;
#endif


    printf("======================================\n");

}


Bool MApp_CompareVersion(MSIF_Version  *pVersion, MS_U16 *IF_Version)
{
   MS_U8 iRet, i;
   bool match=true;
   i = 0;
   iRet=0;

   VERSION_DBG(printf("\n----------------------------------\n"));
   for(i=0;i<8;i++)
   {
     VERSION_DBG( printf("%c : %c -->",*(IF_Version+i),*((pVersion->MW.changelist)+i)));
      iRet=*(IF_Version+i)- *((pVersion->MW.changelist)+i);
    VERSION_DBG( printf("iRet = %d :",iRet));
      if(iRet!=0)
      {
            match=false;
            VERSION_DBG(printf("Failed!\n"));
            break;
      }
      else
      {
           VERSION_DBG(printf("Sucess!\n"));
      }
   }

   return match;

}
