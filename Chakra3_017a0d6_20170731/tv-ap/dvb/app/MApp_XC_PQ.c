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
#define _APP_XC_PQ_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include <string.h>
#include "MsCommon.h"
#include "Board.h"

// Common Definition
#include "MsCommon.h"
#include "apiXC.h"

// Driver
#include "drvXC_HDMI_if.h"
#include "drvPQ.h"

// API
#include "apiXC_Ace.h"
#include "msAPI_VD.h"
#include "apiXC_Adc.h"
#include "apiXC_Hdmi.h"
#include "apiXC_Sys.h"
#include "apiXC_Dlc.h"
#include "msAPI_Tuning.h"
#include "msAPI_Timer.h"

#include "msAPI_NR.h"
// APP
#include "MApp_GlobalSettingSt.h"           // for ST_VIDEO
#include "MApp_GlobalFunction.h"

#if ENABLE_DMP
#include "mapp_mplayer.h"
#endif

#include "MApp_XC_PQ.h"
#include "QualityEx_Default.h"
#include "MApp_Scaler.h"

#if (XC_BRINGUP == 1)
#include "color_reg.h"
#endif

#if FIXED_3D_SWITCH_PIC_MODE_GARBAGE
#include "MApp_GlobalVar.h"
#endif

#if ENABLE_PIP
#include "MApp_PIP.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------

#if 0
#define MDrv_WRAP_BW_LoadTableByContext(x)
#else
#define MDrv_WRAP_BW_LoadTableByContext(x)   MDrv_BW_LoadTableByContext(x)
#endif

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define PQMSG(x)    //x

//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------
// Set different color setting according to each input

//
// Contrast
//
//OSD    0        90        100        200
//Gain    0.3000  0.9000  1.0000  2.0000

#if 1//(ENABLE_PICTURE_NONLINEAR_CURVE == FALSE)
#if 0
T_MS_NONLINEAR_CURVE code stContrastCurveTblForHDTV =
{
    {0,     (ACE_Contrast_DefaultValue_HDTV * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_HDTV * 90 / 100 ) },
    {99,    (ACE_Contrast_DefaultValue_HDTV - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_HDTV      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForSDTV =
{
    {0,     (ACE_Contrast_DefaultValue_SDTV * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_SDTV * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_SDTV - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_SDTV      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForATV =
{
    {0,     (ACE_Contrast_DefaultValue_ATV * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_ATV * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_ATV - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_ATV      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForAV =
{
    {0,     (ACE_Contrast_DefaultValue_AV * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_AV * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_AV - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_AV      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForSV =
{
    {0,     (ACE_Contrast_DefaultValue_SV * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_SV * 90 / 100 ) },
    {99,    (ACE_Contrast_DefaultValue_SV - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_SV      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForYPBPR_HD =
{
    {0,     (ACE_Contrast_DefaultValue_YPBPR_HD * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_YPBPR_HD * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_YPBPR_HD - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_YPBPR_HD      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForYPBPR_SD =
{
    {0,     (ACE_Contrast_DefaultValue_YPBPR_SD * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_YPBPR_SD * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_YPBPR_SD - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_YPBPR_SD      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForHDMI_HD =
{
    {0,     (ACE_Contrast_DefaultValue_HDMI_HD * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_HDMI_HD * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_HDMI_HD - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_HDMI_HD      ) },
};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForHDMI_SD =
{
    {0,     (ACE_Contrast_DefaultValue_HDMI_SD * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_HDMI_SD * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_HDMI_SD - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_HDMI_SD      ) },
};

//T_MS_NONLINEAR_CURVE code stContrastCurveTblForVGA =
//{
//    {0,     (ACE_Contrast_DefaultValue_VGA_DVI * 30 / 100 ) },
//    {90,    (ACE_Contrast_DefaultValue_VGA_DVI     ) },
//    {99,    (ACE_Contrast_DefaultValue_VGA_DVI + 9 ) },
//    {100,   (ACE_Contrast_DefaultValue_VGA_DVI + 10) },
//};

T_MS_NONLINEAR_CURVE code stContrastCurveTblForVGA =
{
    {0,     (ACE_Contrast_DefaultValue_VGA_DVI * 30 / 100 ) },
    {90,    (ACE_Contrast_DefaultValue_VGA_DVI * 90 / 100) },
    {99,    (ACE_Contrast_DefaultValue_VGA_DVI - 1  ) },
    {100,   (ACE_Contrast_DefaultValue_VGA_DVI      ) },
};
#endif

//===================================================
//OSD        0    40    50    100    200
//Offset    -64 0    2    64    128

T_MS_NONLINEAR_CURVE code stBrightnessCurveTbl =
{
    {0,     (126-64) },
    {40,    (126)    },
    {50,    (126+2)  },
    {100,   (126+64) },
};

//
// Saturation
//
//OSD  0         50         70         100
//Gain 0.3000  1.0000  1.2000  1.5000
#if( ENABLE_DTV )
T_MS_NONLINEAR_CURVE code stSaturationCurveTblForHDTV =
{
    {0,     (ACE_Saturation_DefaultValue_HDTV * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_HDTV    )},
    {70,    (ACE_Saturation_DefaultValue_HDTV * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_HDTV * 150 / 100 )},
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForSDTV =
{
    {0,     (ACE_Saturation_DefaultValue_SDTV * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_SDTV    )},
    {70,    (ACE_Saturation_DefaultValue_SDTV * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_SDTV * 150 / 100 )},
};
#endif

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForATV =
{
    {0,     (ACE_Saturation_DefaultValue_ATV * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_ATV    )},
    {70,    (ACE_Saturation_DefaultValue_ATV * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_ATV * 150 / 100 ) },
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForAV =
{
    {0,     (ACE_Saturation_DefaultValue_AV * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_AV    )},
    {70,    (ACE_Saturation_DefaultValue_AV * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_AV * 150 / 100 ) },
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForSV =
{
    {0,     (ACE_Saturation_DefaultValue_SV * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_SV    )},
    {70,    (ACE_Saturation_DefaultValue_SV * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_SV * 150 / 100 ) },
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForYPBPR_HD =
{
    {0,     (ACE_Saturation_DefaultValue_YPBPR_HD * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_YPBPR_HD    )},
    {70,    (ACE_Saturation_DefaultValue_YPBPR_HD * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_YPBPR_HD * 150 / 100 ) },
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForYPBPR_SD =
{
    {0,     (ACE_Saturation_DefaultValue_YPBPR_SD * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_YPBPR_SD    )},
    {70,    (ACE_Saturation_DefaultValue_YPBPR_SD * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_YPBPR_SD * 150 / 100 ) },
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForHDMI_HD =
{
    {0,     (ACE_Saturation_DefaultValue_HDMI_HD * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_HDMI_HD    )},
    {70,    (ACE_Saturation_DefaultValue_HDMI_HD * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_HDMI_HD * 150 / 100 ) },
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForHDMI_SD =
{
    {0,     (ACE_Saturation_DefaultValue_HDMI_SD * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_HDMI_SD    )},
    {70,    (ACE_Saturation_DefaultValue_HDMI_SD * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_HDMI_SD * 150 / 100 ) },
};

T_MS_NONLINEAR_CURVE code stSaturationCurveTblForVGA =
{
    {0,     (ACE_Saturation_DefaultValue_VGA_DVI * 1 / 100 ) },
    {50,    (ACE_Saturation_DefaultValue_VGA_DVI    )},
    {70,    (ACE_Saturation_DefaultValue_VGA_DVI * 120 / 100 )},
    {100,   (ACE_Saturation_DefaultValue_VGA_DVI * 150 / 100 ) },
};


//
// Sharpness
//
#if( ENABLE_DTV )
T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForHDTV =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_HDTV - 8)},
    {70,    (ACE_Sharpness_DefaultValue_HDTV    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForSDTV =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_SDTV - 8)},
    {70,    (ACE_Sharpness_DefaultValue_SDTV    )},
    {100,   (0x3F)},
};
#endif
T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForATV =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_ATV - 8)},
    {70,    (ACE_Sharpness_DefaultValue_ATV    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForAV =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_AV - 8)},
    {70,    (ACE_Sharpness_DefaultValue_AV    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForSV =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_SV - 8)},
    {70,    (ACE_Sharpness_DefaultValue_SV    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForYPBPR_HD =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_YPBPR_HD - 8)},
    {70,    (ACE_Sharpness_DefaultValue_YPBPR_HD    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForYPBPR_SD =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_YPBPR_SD - 8)},
    {70,    (ACE_Sharpness_DefaultValue_YPBPR_SD    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForHDMI_HD =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_HDMI_HD - 8)},
    {70,    (ACE_Sharpness_DefaultValue_HDMI_HD    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForHDMI_SD =
{
    {0,     (0x00)},
    {50,    (ACE_Sharpness_DefaultValue_HDMI_SD - 8)},
    {70,    (ACE_Sharpness_DefaultValue_HDMI_SD    )},
    {100,   (0x3F)},
};

T_MS_NONLINEAR_CURVE code stSharpnessCurveTblForVGA =
{
    {0,     (ACE_Sharpness_DefaultValue_VGA_DVI - 20)},
    {50,    (ACE_Sharpness_DefaultValue_VGA_DVI - 10)},
    {70,    (ACE_Sharpness_DefaultValue_VGA_DVI     )},
    {100,   (ACE_Sharpness_DefaultValue_VGA_DVI + 10)},
};

//==============================================================
//OSD -50 0 50
//Angle[radian] -0.349 0 0.349
//Angle[degree] -20 0 20

T_MS_NONLINEAR_CURVE code stHueCurveTbl =
{
    {0,     (ACE_Hue_DefaultValue_ATV - 15) },
    {50,    (ACE_Hue_DefaultValue_ATV) },
    {99,    (ACE_Hue_DefaultValue_ATV + 14) },
    {100,   (ACE_Hue_DefaultValue_ATV + 15) },
};

T_MS_NONLINEAR_CURVE code stHueCurveTblForHDMI =
{
    {0,     (ACE_Hue_DefaultValue_ATV - 20) },
    {50,    (ACE_Hue_DefaultValue_ATV) },
    {99,    (ACE_Hue_DefaultValue_ATV + 19) },
    {100,   (ACE_Hue_DefaultValue_ATV + 20) },
};
#endif

typedef enum{
    ePictureItem_Brightness=0,
    ePictureItem_Contrast,
    ePictureItem_Saturation,
    ePictureItem_Sharpness
} ePictureItem;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
extern MS_S16 S16DACColorCorrectionMatrix[32];

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#define OffsetValForSECAM_Brightness    0
#define OffsetValForSECAM_Contras       0
#define OffsetValForSECAM_Saturation    6
#define OffsetValForSECAM_Sharpness     0

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

//#define SATURATION_CURVE_START


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

void MApp_PicSetNR(T_MS_NR_MODE * eNRMode, INPUT_SOURCE_TYPE_t enInputSourceType)
{
    UNUSED(enInputSourceType);
    switch(eNRMode -> eNR)
    {
        case MS_NR_OFF:
            MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_OFF, MAIN_WINDOW );
        break;
        case MS_NR_LOW:
            MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_LOW, MAIN_WINDOW );
        break;
        case MS_NR_MIDDLE:
            MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_MID, MAIN_WINDOW );
        break;
        case MS_NR_HIGH:
            MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_HIGH, MAIN_WINDOW );
        break;
        case MS_NR_DEFAULT:
            MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_DEFAULT, MAIN_WINDOW );
        break;
        default:
        case MS_NR_AUTO:
            MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_AUTO, MAIN_WINDOW );
        break;
    }
}
void MApp_PicSet_InitMPEGNR(PQ_WIN eWindow)
{
  //printf("\n ST_VIDEO.eNRMode.eMPEG_NR =%d\n",ST_VIDEO.eNRMode.eMPEG_NR);
   if( MS_MPEG_NR_LOW == ST_VIDEO.eNRMode.eMPEG_NR )
    {
        MDrv_PQ_LoadMPEGNRTable(eWindow, PQ_MPEG_NR_LOW);
    }
    else if( MS_MPEG_NR_MIDDLE == ST_VIDEO.eNRMode.eMPEG_NR )
    {
        MDrv_PQ_LoadMPEGNRTable(eWindow, PQ_MPEG_NR_MID);
    }
    else if( MS_MPEG_NR_HIGH == ST_VIDEO.eNRMode.eMPEG_NR )
    {
        MDrv_PQ_LoadMPEGNRTable(eWindow, PQ_MPEG_NR_HIGH);
    }
    else if( MS_MPEG_NR_OFF == ST_VIDEO.eNRMode.eMPEG_NR )
    {
        MDrv_PQ_LoadMPEGNRTable(eWindow, PQ_MPEG_NR_OFF);
    }
    else if( MS_MPEG_NR_DEFAULT == ST_VIDEO.eNRMode.eMPEG_NR )
    {
        MDrv_PQ_LoadMPEGNRTable(eWindow, PQ_MPEG_NR_DEFAULT);
    }

}
//////////////////////////////////////////////////////////////////
// Set user(UI) PQ settings
// including: DLC/ACE 3x3 matrix/NR/
//            HUE/Saturation/Brightness/Contrast/black level/Gamma
// parameter:
//    [IN]  enInputSourceType
//////////////////////////////////////////////////////////////////

static void MApp_Picture_ColorCtrl(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow)
{
    PQ_WIN enPQWin = PQ_MAIN_WINDOW;
    PQ_DISPLAY_TYPE enDisplaType = PQ_DISPLAY_ONE;

  #if (ENABLE_PIP)
    switch(eWindow)
    {
        default:
        case MAIN_WINDOW:
            enPQWin = PQ_MAIN_WINDOW;
            break;
        case SUB_WINDOW:
            enPQWin = PQ_SUB_WINDOW;
            break;
    }
  #endif

    //if(U16PQSrcType!= MDrv_PQ_GetSrcType(enPQWin))
    //{
    #if (ENABLE_PIP)
        if(IsPIPSupported())
        {
            switch(MApp_Get_PIPMode())
            {
                case EN_PIP_MODE_PIP:
                    enDisplaType = PQ_DISPLAY_PIP;
                    //printf("PQ_DISPLAY_PIP\n");
                break;
                case EN_PIP_MODE_POP_FULL:
                case EN_PIP_MODE_POP:
                    enDisplaType = PQ_DISPLAY_POP;
                    //printf("PQ_DISPLAY_POP\n");
                break;

                default:
                case EN_PIP_MODE_OFF:
                    enDisplaType = PQ_DISPLAY_ONE;
                    //printf("PQ_DISPLAY_ONE\n");
                break;
            }
        }
    #endif

        MDrv_PQ_Set_DisplayType(g_IPanel.Width(), enDisplaType);

    #if (XC_BRINGUP == 1)   //Disable Y/C SRAM filter for bring up
        {
            MApi_XC_W2BYTE(REG_SC_BK23_0B_L, 0x0000);
        }
    #endif

    if(g_u8switchPicModeFlag==FALSE)
    {
        MDrv_PQ_LoadSettings(enPQWin);
    }
    else
    {
       // printf("don't load PQ\n");
    }

    if(MDrv_PQ_Get_PointToPoint(PQ_MAIN_WINDOW))
    {
        MDrv_PQ_LoadPTPTable(PQ_MAIN_WINDOW, PQ_PTP_PTP);
    }
    //    U16PQSrcType = MDrv_PQ_GetSrcType(enPQWin);
    //}


    if ((enInputSourceType >= INPUT_SOURCE_HDMI)  && (enInputSourceType < INPUT_SOURCE_HDMI_MAX)) //check source type
    {
        MS_U16 u16InputWidth = MDrv_PQ_GetHsize(enPQWin);
        MS_U16 u16InputHeight = MDrv_PQ_GetVsize(enPQWin);
        MS_BOOL bIsInterlaced = MDrv_PQ_IsInterlace(enPQWin);

        // check whether received AVI info
        if ((BIT(3) == MApi_XC_HDMI_GetPacketInfo()->enPKT_Value.PKT_AVI_VALUE)
            && (E_AVI_INFOFRAME_VERSION2 == MDrv_HDMI_Get_AVIInfoFrameVer()))
        {
            if (E_HDMI_COLOR_RANGE_LIMIT == MDrv_HDMI_Get_ColorRange()) //color range limit and version 2
            {
                stGenSetting.g_SysSetting.enAUTOCOLORRANGE = EN_COLOR_RANGE_16_235;
            }
            else if (E_HDMI_COLOR_RANGE_FULL == MDrv_HDMI_Get_ColorRange()) //color range full and version 2
            {
                stGenSetting.g_SysSetting.enAUTOCOLORRANGE = EN_COLOR_RANGE_0_255;
            }
            else // color range default
            {
                if (TRUE == IsHDMIColorRangeLimitFormat(u16InputWidth, u16InputHeight, bIsInterlaced))
                {
                    stGenSetting.g_SysSetting.enAUTOCOLORRANGE = EN_COLOR_RANGE_16_235;
                }
                else
                {
                    stGenSetting.g_SysSetting.enAUTOCOLORRANGE = EN_COLOR_RANGE_0_255;
                }
            }
        }
        else // no avi info or not version 2
        {
            // check whether color range limit format
            if (TRUE == IsHDMIColorRangeLimitFormat(u16InputWidth, u16InputHeight, bIsInterlaced))
            {
                stGenSetting.g_SysSetting.enAUTOCOLORRANGE = EN_COLOR_RANGE_16_235;
            }
            else
            {
                stGenSetting.g_SysSetting.enAUTOCOLORRANGE = EN_COLOR_RANGE_0_255;
            }
        }
    }
    else if ((enInputSourceType < INPUT_SOURCE_HDMI) || (enInputSourceType > INPUT_SOURCE_HDMI_MAX))
    {
        stGenSetting.g_SysSetting.enAUTOCOLORRANGE = EN_COLOR_RANGE_0_255;
    }

#if ENABLE_DBC
    if(eWindow == MAIN_WINDOW)
    {
        MApi_XC_Sys_DLC_DBC_YCGainInit();
    }
#else
  #if ENABLE_DLC
    if(eWindow == MAIN_WINDOW)
    {
        MApi_XC_DLC_CGC_Init();
    }
  #endif
#endif

    if(IsSrcTypeATV(enInputSourceType))
    {
        MApi_XC_ACE_DMS(MAIN_WINDOW, TRUE) ;
    }
    else
    {
        MApi_XC_ACE_DMS(MAIN_WINDOW, FALSE) ;
    }

#if (ENABLE_DLC)
    if( MApi_XC_DLC_GetLumaCurveStatus()) // This reg value is control by PQ Excel
    {
        if (!g_bEnableDLC)
        {
            g_bEnableDLC = TRUE;
            MApi_XC_DLC_SetOnOff(ENABLE, MAIN_WINDOW);
        }
    }
    else
    {
        g_bEnableDLC = FALSE;
    }
    //printf("g_bEnableDLC=%u\n", g_bEnableDLC);
#endif

#if (ENABLE_DBC)
    if( MApi_XC_DLC_GetLumaCurveStatus())
    {
        MApi_XC_Sys_DLC_DBC_OnOff(ENABLE);
    }
    else
    {
        MApi_XC_Sys_DLC_DBC_OnOff(DISABLE);
    }
#endif

    MApp_Scaler_AutoDisablePQ_UC();
}

code short  tBypassColorCorrectionMatrix[] =
{
   0x0400, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x0000, 0x0000,
   0x0400,-0x02E6, 0x0288,-0x05BB, 0x07A4,-0x062C, 0x06F3,-0x073C,
  -0x0024, 0x01BF, 0x07EF,-0x0116, 0x01EE, 0x052C,-0x03BB, 0x00B1,
  -0x0831, 0x0100,-0x0000, 0x0000,-0x0000, 0x0000, 0x0000, 0x0000,
};

MS_BOOL MDrv_ACE_GetSkipWaitVsync( MS_BOOL bScalerWin);

#if( LD_ENABLE )
void MApp_Picture_Set_LD(EN_MS_PICTURE ePictureMode)
{
    U8 u8LdMode = 0;

    printf("MApp_Picture_Set_LD(ePictureMode=%u)\n", ePictureMode);

    switch(ePictureMode)
    {
        default:
        case PICTURE_Vivid:
            u8LdMode = 0;
            break;
        case PICTURE_Soft:
            u8LdMode = 1;
            break;
    }

    printf("u8LdMode=%u\n", u8LdMode);

    if(u8LdMode == 1)
    {

    }
    else
    {

    }

}
#endif

void MApp_SetPictureMode(SCALER_WIN eWindow, BOOL bSetInBlanking )
{
    BOOL bBackupAceWaitVSync = MDrv_ACE_GetSkipWaitVsync(eWindow);

    //LOG_CHANGE_CHANNEL_TIME("PicMod-1");

    //printf("bBackupAceWaitVSync=%u\n", bBackupAceWaitVSync);
    MApi_XC_ACE_SkipWaitVsync( eWindow, (bSetInBlanking?FALSE:TRUE) );
    //printf("MDrv_ACE_GetSkipWaitVsync(eWindow)=%u\n", MDrv_ACE_GetSkipWaitVsync(eWindow));

    if(MApi_XC_IsYUVSpace(eWindow))
    {
        MApi_XC_ACE_SetPCYUV2RGB( eWindow, TRUE);

        //LOG_CHANGE_CHANNEL_TIME("PicMod-2");

        if((IsDigitalSourceInUse() && ((mvideo_vd_get_videosystem() == SIG_NTSC) || (mvideo_vd_get_videosystem() == SIG_NTSC_443))))
        {
            MApi_XC_ACE_PicSetHue( eWindow, MApi_XC_IsYUVSpace(eWindow), msAPI_Mode_PictureHueN100toReallyValue( ST_VIDEO.astPicture[ST_VIDEO.ePicture].u8Hue) );
        }
        else
        {
            MApi_XC_ACE_PicSetHue( eWindow, MApi_XC_IsYUVSpace(eWindow), msAPI_Mode_PictureHueN100toReallyValue(50) );
        }

        //LOG_CHANGE_CHANNEL_TIME("PicMod-3");

        MApi_XC_ACE_PicSetSaturation( eWindow, MApi_XC_IsYUVSpace(eWindow), msAPI_Mode_PictureSaturationN100toReallyValue( ST_VIDEO.astPicture[ST_VIDEO.ePicture].u8Saturation) );

        //LOG_CHANGE_CHANNEL_TIME("PicMod-4");

        if(MApi_XC_Sys_IsSrcHD(eWindow))
        {
            PQ_WIN ePQWin = ((eWindow == SUB_WINDOW) ? PQ_SUB_WINDOW : PQ_MAIN_WINDOW);

            if(TRUE == MDrv_PQ_GetR2YEqSelect(ePQWin))
            {
                MApi_XC_ACE_SelectYUVtoRGBMatrix( eWindow, E_XC_ACE_YUV_TO_RGB_MATRIX_SDTV, NULL);
            }
            else
            {
                MApi_XC_ACE_SelectYUVtoRGBMatrix( eWindow, E_XC_ACE_YUV_TO_RGB_MATRIX_HDTV, NULL);
            }
        }
        else
        {
            MApi_XC_ACE_SelectYUVtoRGBMatrix( eWindow, E_XC_ACE_YUV_TO_RGB_MATRIX_SDTV, NULL);
        }

        //LOG_CHANGE_CHANNEL_TIME("PicMod-5");

    }
    else
    {
        MApi_XC_ACE_SetPCYUV2RGB( eWindow, FALSE);
    }

    //LOG_CHANGE_CHANNEL_TIME("PicMod-6");

#if _TEST_VGA_
    MApi_XC_ACE_PicSetSharpness( MAIN_WINDOW, 0);
#else
    MApi_XC_ACE_PicSetSharpness( MAIN_WINDOW, msAPI_Mode_PictureSharpnessN100toReallyValue(ST_VIDEO.astPicture[ST_VIDEO.ePicture].u8Sharpness) );
#endif

#if( LD_ENABLE )
    MApp_Picture_Set_LD(ST_VIDEO.ePicture);
#endif

    MApi_XC_ACE_SkipWaitVsync( eWindow, bBackupAceWaitVSync );

    //LOG_CHANGE_CHANNEL_TIME("PicMod-7");
}

void MApp_PQ_Set_ColorTemp( SCALER_WIN eWindow)
{
    U8 u8DataSrcIdx = DATA_INPUT_SOURCE_TYPE(eWindow);
    U8 u8ColorTempIdx = ST_PICTURE.eColorTemp;
    T_MS_COLOR_TEMP colorTempSetting;


    if( u8DataSrcIdx >= DATA_INPUT_SOURCE_NUM )
    {
        return;
    }

    if( u8ColorTempIdx >= MS_COLOR_TEMP_COUNT )
    {
        return;
    }

    colorTempSetting = (G_WHITE_BALANCE_SETTING[u8DataSrcIdx].astColorTemp[u8ColorTempIdx]);

    //printf(" sizeof(T_MS_WHITEBALANCE)= %u\n", sizeof(T_MS_WHITEBALANCE));
    //printf(" sizeof(T_MS_COLOR_TEMP)= %u\n", sizeof(T_MS_COLOR_TEMP));
    /*
    {
        U8 i;

        for(i = 0; i < DATA_INPUT_SOURCE_NUM; i++)
        {
            printf("G_WHITE_BALANCE_SETTING[%u]=%X\n", i,(U32)&(G_WHITE_BALANCE_SETTING[i]));
            {
                U8 j;
                for(j = 0; j < MS_COLOR_TEMP_COUNT; j++)
                {
                    printf(" G_colorTemp_SETTING[%u]=%X\n", j,(U32)&(G_WHITE_BALANCE_SETTING[i].astColorTemp[j]));
                }
            }
        }
    } */

/*
    printf(" u8DataSrcIdx= %u\n", u8DataSrcIdx);
    printf(" u8ColorTempIdx= %u\n", u8ColorTempIdx);

    printf("ST_COLOR_TEMP:\n");

    printf(" cRedOffset: %u\n", colorTempSetting.cRedOffset);
    printf(" cGreenOffset: %u\n", colorTempSetting.cGreenOffset);
    printf(" cBlueOffset: %u\n", colorTempSetting.cBlueOffset);

    printf(" cRedColor: %u\n", colorTempSetting.cRedColor);
    printf(" cGreenColor: %u\n", colorTempSetting.cGreenColor);
    printf(" cBlueColor: %u\n", colorTempSetting.cBlueColor);

    printf(" cRedScaleValue: %u\n", colorTempSetting.cRedScaleValue);
    printf(" cGreenScaleValue: %u\n", colorTempSetting.cGreenScaleValue);
    printf(" cBlueScaleValue: %u\n", colorTempSetting.cBlueScaleValue);
*/

    if( MApi_XC_MLoad_GetStatus() == E_MLOAD_ENABLED )
    {
        MApi_XC_ACE_SkipWaitVsync( eWindow, FALSE);
    }


#if ENABLE_NEW_COLORTEMP_METHOD

    #if ENABLE_PRECISE_RGBBRIGHTNESS
    {
      #if 0
        XC_ACE_color_temp_ex2 stXC_ACE_color_temp_ex2;
        stXC_ACE_color_temp_ex2.cRedOffset = pColorTempSetting->cRedOffset;
        stXC_ACE_color_temp_ex2.cGreenOffset = pColorTempSetting->cGreenOffset;
        stXC_ACE_color_temp_ex2.cBlueOffset = pColorTempSetting->cBlueOffset;
        stXC_ACE_color_temp_ex2.cRedColor = pColorTempSetting->cRedColor;
        stXC_ACE_color_temp_ex2.cGreenColor = pColorTempSetting->cGreenColor;
        stXC_ACE_color_temp_ex2.cBlueColor = pColorTempSetting->cBlueColor;
        stXC_ACE_color_temp_ex2.cRedScaleValue = pColorTempSetting->cRedScaleValue;
        stXC_ACE_color_temp_ex2.cGreenScaleValue = pColorTempSetting->cGreenScaleValue;
        stXC_ACE_color_temp_ex2.cBlueScaleValue = pColorTempSetting->cBlueScaleValue;
        MApi_XC_ACE_PicSetPostColorTemp_V02( eWindow, &stXC_ACE_color_temp_ex2);
      #else
        XC_ACE_color_temp_ex st_ACE_color_temp_ex;
        memset( &st_ACE_color_temp_ex, 0, sizeof(XC_ACE_color_temp_ex) );
        st_ACE_color_temp_ex.cRedOffset = colorTempSetting.cRedOffset;
        st_ACE_color_temp_ex.cGreenOffset = colorTempSetting.cGreenOffset;
        st_ACE_color_temp_ex.cBlueOffset = colorTempSetting.cBlueOffset;
        st_ACE_color_temp_ex.cRedColor = colorTempSetting.cRedColor;
        st_ACE_color_temp_ex.cGreenColor = colorTempSetting.cGreenColor;
        st_ACE_color_temp_ex.cBlueColor = colorTempSetting.cBlueColor;
        st_ACE_color_temp_ex.cRedScaleValue = colorTempSetting.cRedScaleValue;
        st_ACE_color_temp_ex.cGreenScaleValue = colorTempSetting.cGreenScaleValue;
        st_ACE_color_temp_ex.cBlueScaleValue = colorTempSetting.cBlueScaleValue;
        MApi_XC_ACE_PicSetPostColorTemp2Ex(eWindow, MApi_XC_IsYUVSpace(eWindow), &st_ACE_color_temp_ex);
        //MApi_XC_ACE_PicSetColorTemp( eWindow, MApi_XC_IsYUVSpace(eWindow), &ST_COLOR_TEMP );
      #endif
    }
    #else
    {
        // Please don't use this!!
        //pi_XC_ACE_PicSetColorTemp(MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), (XC_ACE_color_temp *) &ST_COLOR_TEMP);
        //pi_XC_ACE_PicSetColorTemp( eWindow, MApi_XC_IsYUVSpace(eWindow),  &ST_COLOR_TEMP );
        ///MApi_XC_ACE_PicSetBrightnessInVsync(eWindow, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
    }
    #endif

#else

    // todo:
    #if ENABLE_PRECISE_RGBBRIGHTNESS
        //MApi_XC_ACE_PicSetColorTemp( eWindow, MApi_XC_IsYUVSpace(eWindow), (XC_ACE_color_temp_ex *) &ST_COLOR_TEMP );
        //MApi_XC_ACE_PicSetBrightnessPreciseInVsync(eWindow, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
    #else
        //MApi_XC_ACE_PicSetColorTemp( eWindow, MApi_XC_IsYUVSpace(eWindow), (XC_ACE_color_temp *) &ST_COLOR_TEMP );
        //MApi_XC_ACE_PicSetBrightnessInVsync(eWindow, MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cRedOffset, BRIGHTNESS_R ), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cGreenOffset, BRIGHTNESS_G), MApi_XC_Sys_ACE_transferRGB_Bri(ST_COLOR_TEMP.cBlueOffset, BRIGHTNESS_B));
    #endif

#endif

}

#define DEBUG_PQ_BRI(x) //x
void MApp_XC_PQ_Set_Brightness(SCALER_WIN eWindow, BOOL bSetInVBlanking)
{
    U8 u8Bri_1, u8Bri_2;
    U8 u8Bri_R, u8Bri_G, u8Bri_B;
    U8 u8DataIdx = DATA_INPUT_SOURCE_TYPE(eWindow);
    BOOL bBackupAceWaitVSync;


    DEBUG_PQ_BRI(printf("MApp_XC_PQ_Set_Brightness(win=%u)\n", eWindow););

    if( u8DataIdx >= DATA_INPUT_SOURCE_NUM )
    {
        printf("\nError: u8DataIdx=%u\n", u8DataIdx );
        return;
    }

    u8Bri_1 = msAPI_Mode_PictureBrightnessN100toReallyValue(ST_PICTURE.u8Brightness);
    DEBUG_PQ_BRI(printf(" ST_PICTURE.u8Brightness=%u, u8Bri_1=%u\n", ST_PICTURE.u8Brightness, u8Bri_1); );

    u8Bri_2 = MApp_Scaler_FactoryAdjBrightness(u8Bri_1, G_SUB_COLOR_SETTING[u8DataIdx].u8SubBrightness);
    DEBUG_PQ_BRI(printf(" ST_SUBCOLOR.u8Brightness=%u, u8Bri_2=%u\n", G_SUB_COLOR_SETTING[u8DataIdx].u8SubBrightness, u8Bri_2););

    u8Bri_R = MApi_XC_Sys_ACE_transfer_Bri( u8Bri_2, BRIGHTNESS_R);
    u8Bri_G = MApi_XC_Sys_ACE_transfer_Bri( u8Bri_2, BRIGHTNESS_G);
    u8Bri_B = MApi_XC_Sys_ACE_transfer_Bri( u8Bri_2, BRIGHTNESS_B);

    DEBUG_PQ_BRI(printf(" => u8Brightness=%u %u %u\n", u8Bri_R, u8Bri_G, u8Bri_B););



    bBackupAceWaitVSync = MDrv_ACE_GetSkipWaitVsync(eWindow);

    if( MApi_XC_MLoad_GetStatus() == E_MLOAD_ENABLED )
    {
        MApi_XC_ACE_SkipWaitVsync( eWindow, (bSetInVBlanking?FALSE:TRUE) );
    }
    else
    {
        if( bSetInVBlanking ) // Set in V blanking
        {
            MApi_XC_WaitOutputVSync(1, 50, eWindow);
        }
    }

    MApi_XC_ACE_PicSetBrightness(eWindow, u8Bri_R, u8Bri_G, u8Bri_B );

    MApi_XC_ACE_SkipWaitVsync( eWindow, bBackupAceWaitVSync );
}

#define DEBUG_PQ_CON(x) //x
void MApp_XC_PQ_Set_Contrast(SCALER_WIN eWindow, BOOL bSetInVBlanking)
{
    U8 u8Con_1, u8Con_2;
    U8 u8DataIdx = DATA_INPUT_SOURCE_TYPE(eWindow);
    BOOL bBackupAceWaitVSync;


    DEBUG_PQ_CON(printf("MApp_XC_PQ_Set_Contrast(win=%u)\n", eWindow););

    if( u8DataIdx >= DATA_INPUT_SOURCE_NUM )
    {
        printf("\nError: u8DataIdx=%u\n", u8DataIdx );
        return;
    }

    u8Con_1 = msAPI_Mode_PictureContrastN100toReallyValue(ST_PICTURE.u8Contrast);
    DEBUG_PQ_CON(printf(" ST_PICTURE.u8Contrast=%u, u8Con_1=%u\n", ST_PICTURE.u8Contrast, u8Con_1); );

    u8Con_2 = MApp_Scaler_FactoryContrast(u8Con_1, G_SUB_COLOR_SETTING[u8DataIdx].u8SubContrast);
    DEBUG_PQ_CON(printf(" ST_SUBCOLOR.u8SubContrast=%u, u8Con_2=%u\n", G_SUB_COLOR_SETTING[u8DataIdx].u8SubContrast, u8Con_2););


    bBackupAceWaitVSync = MDrv_ACE_GetSkipWaitVsync(eWindow);

    if( MApi_XC_MLoad_GetStatus() == E_MLOAD_ENABLED )
    {
        MApi_XC_ACE_SkipWaitVsync( eWindow, (bSetInVBlanking?FALSE:TRUE) );
    }
    else
    {
        if( bSetInVBlanking ) // Set in V blanking
        {
            MApi_XC_WaitOutputVSync(1, 50, eWindow);
        }
    }

    MApi_XC_ACE_PicSetContrast(eWindow, MApi_XC_IsYUVSpace(eWindow), u8Con_2);

    MApi_XC_ACE_SkipWaitVsync( eWindow, bBackupAceWaitVSync );
}

void MApp_Picture_Setting_SetColor( INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow )
{
    PQ_WIN ePQWin;
    BOOL bSetInVBlanking = TRUE;
    BOOL bBackupAceWaitVSync;


    switch(eWindow)
    {
        default:
        case MAIN_WINDOW:
            ePQWin = PQ_MAIN_WINDOW;
            break;
        case SUB_WINDOW:
            ePQWin = PQ_SUB_WINDOW;
            break;
    }

    //printf("%s Set Color\n", (ePQWin == PQ_MAIN_WINDOW)?("Main win"):("Sub win"));

    // When mute screen, no need menuload function.
    if( msAPI_Scaler_GetScreenMute(eWindow)
      ||(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)) && msAPI_Tuner_IsTuningProcessorBusy() )
      )
    {
        bSetInVBlanking = FALSE;
    }
    //printf("bNeedUseMenuLoad=%u\n", bNeedUseMenuLoad);
    //printf(" MApi_XC_MLoad_GetStatus()=%u\n",  MApi_XC_MLoad_GetStatus());


    bBackupAceWaitVSync = MDrv_ACE_GetSkipWaitVsync(eWindow);

    // Control ACE use menuload or not
    MApi_XC_ACE_SkipWaitVsync( eWindow, (bSetInVBlanking?FALSE:TRUE) );


    //LOG_CHANGE_CHANNEL_TIME("Color-1");

    // bandwidth setting
#if (XC_BRINGUP == 0)
    MDrv_WRAP_BW_LoadTableByContext(ePQWin);
#endif

    //LOG_CHANGE_CHANNEL_TIME("Color-2");

    // ACE related
    MApp_Picture_ColorCtrl(enInputSourceType, eWindow);

    //LOG_CHANGE_CHANNEL_TIME("Color-3");

    if(MDrv_PQ_Get_PointToPoint(PQ_MAIN_WINDOW))
    {
        MApi_XC_ACE_ColorCorrectionTable( MAIN_WINDOW, (S16*)tBypassColorCorrectionMatrix);
    }
    else
    {
        MApi_XC_ACE_ColorCorrectionTable( eWindow, (S16*)tVideoColorCorrectionMatrix);
    }

    //LOG_CHANGE_CHANNEL_TIME("Color-4");

    MApp_SetPictureMode(eWindow, bSetInVBlanking);

    //LOG_CHANGE_CHANNEL_TIME("Color-5");

    MApp_XC_PQ_Set_Brightness( eWindow, bSetInVBlanking);

    //LOG_CHANGE_CHANNEL_TIME("Color-6");

    MApp_PQ_Set_ColorTemp(eWindow);

    //LOG_CHANGE_CHANNEL_TIME("Color-6.1");

    // Set Contrast
    //MApp_XC_PQ_Set_Contrast( eWindow, FALSE);
    //Fix  1160633.  while change picture mode...if contrast is different from previous setting, picture will not wait vsync...
    MApp_XC_PQ_Set_Contrast( eWindow, bSetInVBlanking);


    //LOG_CHANGE_CHANNEL_TIME("Color-6.2");

    // NR
    MApp_PicSetNR( (T_MS_NR_MODE*) &ST_VIDEO.eNRMode, enInputSourceType );

    //LOG_CHANGE_CHANNEL_TIME("Color-6.3");

#if ENABLE_DYNAMIC_NR
    mAPI_DynamicNR_GetGuassinSNR();
    msAPI_DynamicNR_GetSharpness();
    msAPI_DynamicNR_GetCoring();
#endif
   MApp_PicSet_InitMPEGNR(PQ_MAIN_WINDOW);

    //LOG_CHANGE_CHANNEL_TIME("Color-6");

#if ENABLE_3D_PROCESS
    if((E_XC_3D_OUTPUT_LINE_ALTERNATIVE == MApi_XC_Get_3D_Output_Mode())
        || (E_XC_3D_OUTPUT_TOP_BOTTOM == MApi_XC_Get_3D_Output_Mode())
        || (E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF == MApi_XC_Get_3D_Output_Mode()))
    {
        #if FIXED_3D_SWITCH_PIC_MODE_GARBAGE
            if(g_u8switchPicModeFlag == 0)
            {
                MDrv_PQ_3DCloneforPIP(TRUE);
            }
        #else
            MDrv_PQ_3DCloneforPIP(TRUE);
        #endif
    }
#endif

    // ADC related
    if(IsSrcTypeScart(enInputSourceType) && msAPI_AVD_IsScartRGB())
    {
        MApi_XC_ADC_AdjustGainOffset( &(G_ADC_SETTING[ADC_SET_VGA].stAdcGainOffsetSetting) );
    }

    //LOG_CHANGE_CHANNEL_TIME("Color-7");

    // DLC related
#if ENABLE_DLC
    if(!IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        if (MApi_XC_IsYUVSpace(eWindow))
        {
        #if ENABLE_DMP
            if(IsSrcTypeStorage(enInputSourceType) &&
               (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO))
            {
                #if 1//(defined(S3PLUS)) fix luminance changed during Photo display
                MApi_XC_DLC_SetOnOff(DISABLE, eWindow);
                #endif
            }
        #endif
        }
    }
#endif

    // DBC related
#if ENABLE_DBC
    if(!IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        if (MApi_XC_IsYUVSpace(eWindow))
        {
        #if ENABLE_DMP
            if(IsSrcTypeStorage(enInputSourceType) &&
               (MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_PHOTO))
            {
                MApi_XC_Sys_DLC_DBC_OnOff(DISABLE);
            }
        #endif
        }
    }
#endif

    //LOG_CHANGE_CHANNEL_TIME("Color-8");

    if(stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_AUTO)
    {
        if(stGenSetting.g_SysSetting.enAUTOCOLORRANGE == EN_COLOR_RANGE_16_235)
        {
            MDrv_PQ_SetColorRange(ePQWin, FALSE);
        }
        else if(stGenSetting.g_SysSetting.enAUTOCOLORRANGE == EN_COLOR_RANGE_0_255)
        {
            MDrv_PQ_SetColorRange(ePQWin, TRUE);
        }
    }
    else
    {
        if(IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))
        {
            if(stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_16_235)
            {
                MDrv_PQ_SetColorRange(ePQWin, FALSE);
            }
            else if(stGenSetting.g_SysSetting.enCOLORRANGE == EN_COLOR_RANGE_0_255)
            {
                MDrv_PQ_SetColorRange(ePQWin, TRUE);
            }
        }
        else //not HDMI color range depend on enAUTOCOLORRANGE
        {
            if(stGenSetting.g_SysSetting.enAUTOCOLORRANGE == EN_COLOR_RANGE_16_235)
            {
                MDrv_PQ_SetColorRange(ePQWin, FALSE);
            }
            else if(stGenSetting.g_SysSetting.enAUTOCOLORRANGE == EN_COLOR_RANGE_0_255)
            {
                MDrv_PQ_SetColorRange(ePQWin, TRUE);
            }
        }
    }

    //LOG_CHANGE_CHANNEL_TIME("Color-9");

#if ENABLE_TCON
    MApi_XC_SetGammaOnOff(0);
#endif

    MApi_XC_ACE_SkipWaitVsync( eWindow, bBackupAceWaitVSync );

    //LOG_CHANGE_CHANNEL_TIME("Color-10");
}

U8 _msAPI_Mode_GetPictureOffsetValForSECAM(ePictureItem PictureItem, U8 u8value)
{
    char _u8OffsetTmp=0;

    if (/*IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||*/ IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))||
        IsSrcTypeScart(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeSV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        if(mvideo_vd_get_videosystem() == SIG_SECAM )
        {
            switch(PictureItem)
            {
                case ePictureItem_Brightness:   _u8OffsetTmp = OffsetValForSECAM_Brightness;    break;
                case ePictureItem_Contrast:     _u8OffsetTmp = OffsetValForSECAM_Contras;       break;
                case ePictureItem_Saturation:   _u8OffsetTmp = OffsetValForSECAM_Saturation;    break;
                case ePictureItem_Sharpness:    _u8OffsetTmp = OffsetValForSECAM_Sharpness;     break;
                default:                        _u8OffsetTmp = 0;   break;
            }
            if(u8value == 0)
                _u8OffsetTmp = 0;
            if(u8value == 100)
                _u8OffsetTmp = 0;
        }
    }
    return (u8value+_u8OffsetTmp)>=100 ? 100:((u8value+_u8OffsetTmp)<=0? 0:(u8value+_u8OffsetTmp));
}

/******************************************************************************/
///-This function will get true value of contrast for picture mode
///@param u8value: scaled value
///@return true value of contrast
//*************************************************************************
U8 msAPI_Mode_PictureContrastN100toReallyValue ( U8 u8value )
{
    u8value =_msAPI_Mode_GetPictureOffsetValForSECAM(ePictureItem_Contrast,u8value);

#if(ENABLE_PICTURE_NONLINEAR_CURVE)
    return MApp_NonLinearCalculate(MApp_GetNonLinearCurve(NONLINEAR_CURVE_CONTRAST),u8value);
#else
    return N100toReallyValue( u8value, MIN_VIDEO_CONTRAST, MAX_VIDEO_CONTRAST );
#endif
}

/******************************************************************************/
///-This function will get true value of Brightness for picture mode
///@param u8value: scaled value
///@return true value of Brightness
//*************************************************************************
U8 msAPI_Mode_PictureBrightnessN100toReallyValue ( U8 u8value )
{
    u8value = _msAPI_Mode_GetPictureOffsetValForSECAM(ePictureItem_Brightness,u8value);
#if(ENABLE_PICTURE_NONLINEAR_CURVE)
    return MApp_NonLinearCalculate(MApp_GetNonLinearCurve(NONLINEAR_CURVE_BRIGHTNESS),u8value);
#else
    return N100toReallyValue( u8value, MIN_VIDEO_BRIHTNESS, MAX_VIDEO_BRIHTNESS );
#endif
    //return msAPI_CalNonLinearCurve(u8value, &stBrightnessCurveTbl );
}

/******************************************************************************/
///-This function will get true value of Brightness for picture mode
///@param u8value: scaled value
///@return true value of Brightness
//*************************************************************************

/******************************************************************************/
///-This function will get true value of hue for picture mode
///@param u8value: scaled value
///@return  true value of hue true value of hue
//*************************************************************************
U8 msAPI_Mode_PictureHueN100toReallyValue ( U8 u8value )
{
#if(ENABLE_PICTURE_NONLINEAR_CURVE)
    return MApp_NonLinearCalculate(MApp_GetNonLinearCurve(NONLINEAR_CURVE_HUE),u8value);
#else
    if(MApi_XC_HDMI_GetHdmiType(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == E_HDMI_STATUS_HDMI)
    {
        return msAPI_CalNonLinearCurve(u8value, &stHueCurveTblForHDMI );
    }
    else
    {
        return msAPI_CalNonLinearCurve(u8value, &stHueCurveTbl );
    }
#endif
}

/******************************************************************************/
///-This function will get true value of saturation for picture mode
///@param u8value: scaled saturation
///@return true value of saturation
//*************************************************************************
U8 msAPI_Mode_PictureSaturationN100toReallyValue ( U8 u8value )
{
    T_MS_NONLINEAR_CURVE* pCurve;

    u8value = _msAPI_Mode_GetPictureOffsetValForSECAM(ePictureItem_Saturation,u8value);

#if(ENABLE_PICTURE_NONLINEAR_CURVE)

    pCurve = NULL;//fix uncall warning.

    return MApp_NonLinearCalculate(MApp_GetNonLinearCurve(NONLINEAR_CURVE_SATURATION),u8value);

#else

    if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        pCurve = &stSaturationCurveTblForATV;
    }
#if( ENABLE_DTV )
    else if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        if (MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            pCurve = &stSaturationCurveTblForHDTV;
        }
        else
        {
            pCurve = &stSaturationCurveTblForSDTV;
        }
    }
#endif
    else if (IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
    #if (INPUT_SCART_VIDEO_COUNT > 0)
             || IsSrcTypeScart(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
    #endif
            )
    {
        pCurve = &stSaturationCurveTblForAV;
    }
    else if (IsSrcTypeSV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        pCurve = &stSaturationCurveTblForSV;
    }
    else if (IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        if (MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            pCurve = &stSaturationCurveTblForYPBPR_HD;
        }
        else
        {
            pCurve = &stSaturationCurveTblForYPBPR_SD;
        }
    }
  #if (INPUT_HDMI_VIDEO_COUNT > 0)
    else if(MApi_XC_HDMI_GetHdmiType(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == E_HDMI_STATUS_HDMI)
    {
        if (MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            pCurve = &stSaturationCurveTblForHDMI_HD;
        }
        else
        {
            pCurve = &stSaturationCurveTblForHDMI_SD;
        }
    }
  #endif
    else /* VGA & DVI */
    {
        pCurve = &stSaturationCurveTblForVGA;
    }

    return msAPI_CalNonLinearCurve(u8value, pCurve);
#endif
}

/******************************************************************************/
///-This function will get true value of sharpness for picture mode
///@param u8value: scaled sharpness
///@return true value of sharpness
//*************************************************************************
U8 msAPI_Mode_PictureSharpnessN100toReallyValue ( U8 u8value )
{
    T_MS_NONLINEAR_CURVE* pCurve;

    u8value = _msAPI_Mode_GetPictureOffsetValForSECAM(ePictureItem_Sharpness,u8value);

#if(ENABLE_PICTURE_NONLINEAR_CURVE)
    pCurve = NULL;//fix uncall warning.
    return MApp_NonLinearCalculate(MApp_GetNonLinearCurve(NONLINEAR_CURVE_SHARPNESS),u8value);
#else

    if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        pCurve = &stSharpnessCurveTblForATV;
    }
#if( ENABLE_DTV )
    else if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        if (MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            pCurve = &stSharpnessCurveTblForHDTV;
        }
        else
        {
            pCurve = &stSharpnessCurveTblForSDTV;
        }
    }
#endif
    else if (IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
    #if (INPUT_SCART_VIDEO_COUNT > 0)
            || IsSrcTypeScart(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
    #endif
            )
    {
        pCurve = &stSharpnessCurveTblForAV;
    }
    else if (IsSrcTypeSV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        pCurve = &stSharpnessCurveTblForSV;
    }
    else if (IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
    {
        if (MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            pCurve = &stSharpnessCurveTblForYPBPR_HD;
        }
        else
        {
            pCurve = &stSharpnessCurveTblForYPBPR_SD;
        }
    }
    #if (INPUT_HDMI_VIDEO_COUNT > 0)
    else if(MApi_XC_HDMI_GetHdmiType(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == E_HDMI_STATUS_HDMI)
    {
        if (MApi_XC_Sys_IsSrcHD(MAIN_WINDOW))
        {
            pCurve = &stSharpnessCurveTblForHDMI_HD;
        }
        else
        {
            pCurve = &stSharpnessCurveTblForHDMI_SD;
        }
    }
    #endif
    else /* VGA & DVI */
    {
        pCurve = &stSharpnessCurveTblForVGA;
    }

    return msAPI_CalNonLinearCurve(u8value, pCurve);
#endif
}


#undef _APP_XC_PQ_C_

