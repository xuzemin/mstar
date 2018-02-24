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

/******************************************************************************
 [Module Name]: DDC2BI.c
 [Date]:    24-April-2006
 [Comment]:
   For Slave I2C functions.
 [Reversion History]:

 Registers read and write command list:
 DATA WRITE : START + 0x6E + 0x10 + addrh + addrl + data + STOP
 DATA READ  : START + 0x6E + 0x10 + addrh + addrl + START + 0x6F + data +STOP

 Functions read and write command list:
 write contrast   : START + 0x6E + 0x20 +  01  +   xxh +   data  + STOP
 read  contrast   : START + 0x6E + 0x20 +  01  +   xxh +   START + 0x6F + (data) + STOP
 write Brightness : START + 0x6E + 0x20 +  02  +   xxh +   data  + STOP
 read  Brightness : START + 0x6E + 0x20 +  02  +   xxh +   START + 0x6F + (data) + STOP
 ON/OFF Panel set : START + 0x6E + 0x20 +  10  +   xxh +   0:OFF 1:ON  + STOP
 ON/OFF Panel Rd  : START + 0x6E + 0x20 +  10  +   xxh +   START + 0x6F + (data) + STOP

*******************************************************************************/

/********************
* INCLUDE FILES     *
*********************/
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "hwreg.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Ace.h"
#include "apiXC_Sys.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_Global.h"
#include "MApp_Scaler.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_GlobalFunction.h"
#include "MApp_XC_PQ.h"
#include "MApp_PCMode.h"
//ZUI_TODO: #include "mapp_uimenufunc.h"
//ZUI_TODO: #include "mapp_uimenu.h"
#include "msAPI_Mode.h"
#include "msAPI_Ram.h"

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#if ENABLE_DDCCI
#define DDC_MSG(x)// x

//==================================================================
// define for Command type.

#define VCP_GetVCPFeature               0x01
#define VCP_SetVCPFeature               0x03
#define VCP_GetTimingRequest            0x07
#define VCP_SaveCurrentSetting          0x0C

#define VCP_GetVCPPage                  0xC4
#define VCP_GetPagedVCP                 0xC6
#define VCP_SetPagedVCP                 0xC8
#define VCP_CapabilitiesRequest         0xF3
#define VCP_AppTest                     0xB1

#define VCP_NewControlValue             0x02
#define VCP_ALL_Reset                   0x04
#define VCP_Bri_Con_Reset               0x05
#define VCP_Geometry_Reset              0x06
#define VCP_Color_Reset                 0x08
#define VCP_TV_Function_Reset           0x0A

#define VCP_COLOR_TEMP_INC              0x0B
#define VCP_COLOR_TEMP_REQ              0x0C

#define VCP_ADJ_Clock                   0x0E
#define VCP_ADJ_Brightness              0x10
#define VCP_ADJ_Contrast                0x12
#define VCP_Select_Color_Preset         0x14
#define VCP_ADJ_Red_Gain                0x16
#define VCP_ADJ_Green_Gain              0x18
#define VCP_ADJ_Blue_Gain               0x1A
#define VCP_Auto_Setup                  0x1E
#define VCP_ADJ_HorizontalPos           0x20
#define VCP_ADJ_VerticalPos             0x30

#define VCP_ADJ_OSD_HorizontalPos       0x38
#define VCP_ADJ_OSD_VerticalPos         0x39
#define VCP_DefaultColorChange          0x3B
#define VCP_ADJ_Phase                   0x3E

#define VCP_ChangeInputSource           0x60
#define VCP_ADJ_AudioVolume             0x62
#define VCP_Offset_Red                  0x6C
#define VCP_Offset_Green                0x6E
#define VCP_Offset_Blue                 0x70

#define VCP_ADJ_Zoom                    0x7C
#define VCP_ADJ_ScalingMode             0x86
#define VCP_ADJ_Sharpness               0x87
#define VCP_ADJ_TV_Saturation           0x8A
#define VCP_ADJ_TV_Channel              0x8B
#define VCP_ADJ_TV_Sharpness            0x8C
#define VCP_ADJ_TV_Mute                 0x8D
#define VCP_ADJ_TV_Contrast             0x8E
#define VCP_ADJ_TV_Audio_Treble         0x8F
#define VCP_ADJ_TV_Hue                  0x90
#define VCP_ADJ_TV_Audio_Bass           0x91
#define VCP_ADJ_TV_Black_Level          0x92
#define VCP_ADJ_TV_Audio_Balance        0x93
#define VCP_ADJ_TV_Audio_Stereo         0x94
#define VCP_ADJ_Window_Position_TL_X    0x95
#define VCP_ADJ_Window_Position_TL_Y    0x96

#define VCP_Window_OnOff                0xA4
#define VCP_Window_Select               0xA5
#define VCP_SyncType                    0xA8
#define VCP_H_FREQ                      0xAC
#define VCP_V_FREQ                      0xAE
#define VCP_DDCCI_Settings              0xB0
#define VCP_MonitorType                 0xB6
#define VCP_Usage_Time                  0xC0
#define VCP_EnableApp                   0xCD
#define VCP_ScalerType                  0xCB
#define VCP_FW_Version                  0xC9
#define VCP_OSD_Lock                    0xCA
#define VCP_ADJ_Language                0xCC
#define VCP_PowerMode                   0xD6
#define VCP_MCCS_Version                0xDF
#define VCP_ADJ_ControlLock             0xE3
#define VCP_ADJ_PipSize                 0xEA
#define VCP_ADJ_PipPosition             0xEB
#define VCP_ADJ_ColorEnhance            0xEC
#define VCP_ADJ_Audio_Src_Select        0xED
#define VCP_Auto_Level                  0xF0
#define VCP_Resolution_Notifier         0xF6

//====================================

#define COLOR_TEMP_INC_STEP             100

//====================================

U8 code CAP_VCP[]=
{ "VCP(02 04 05 06 08 0B 0C 0E 10 12 14(01 02 05 06 08 0B)16 18 1A 1E 20 30 3E 60(01 03 05 07 0C)62 6C 6E 70 7C 86 87 8A 8C 8E 90 94(00 02) 95 96 A4(00 01) A5(00 02) AC AE B6 C0 C6 C8 C9 CA CC(02 03 04 05 09 0A 0B 0C) D6(01 04) DF EA(01 02 03 04) EB EC(00 01 02 03) ED(00 01) F0 F6(00 01)) type(LCD) mccs_ver(2.0)"};

//=======================================================================

U8 MApp_DDC2BI_AlignControl(U8 *pDDCBuffData)
{
    U8 CommandCode, CPCode = 0, ValueH, ValueL, RetValueH = 0, RetValueL = 0, PageValue;
    U8 TPValue;
    U16 WordValue = 0,WordAddr;
    U8 SyncStatus;
    SCALER_WIN eWindow = MAIN_WINDOW;

    #if (ENABLE_PIP)
    if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&& (IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
    {
        eWindow=SUB_WINDOW;
    }
    else
    {
        eWindow=MAIN_WINDOW;
    }
    #endif
    SyncStatus = MApi_XC_PCMonitor_GetSyncStatus(eWindow);

    CommandCode = pDDCBuffData[1];
    PageValue = 0;

    //111----------------------------------------------------------Start
    if(CommandCode == VCP_SetVCPFeature)               // 1-1
    {
        CPCode = pDDCBuffData[2];
        RetValueH = pDDCBuffData[3];
        RetValueL = pDDCBuffData[4];
        WordValue = ((U16)pDDCBuffData[3]<<8) | ((U16)pDDCBuffData[4]);
    }
    else if(CommandCode == VCP_GetVCPFeature)         // 1-2
    {
        CPCode = pDDCBuffData[2];
    }
    #if 0
    else if(CommandCode == VCP_ModeChangeRequest)     // 1-3 xx
    {
        CPCode = pDDCBuffData[2];
        ValueH = pDDCBuffData[3];
    }
    #endif
    else if(CommandCode == VCP_GetPagedVCP)           // 1-4
    {
        PageValue = pDDCBuffData[2];
        CPCode = pDDCBuffData[3];
    }
    else if(CommandCode == VCP_SetPagedVCP)           // 1-5
    {
        PageValue = pDDCBuffData[2];
        CPCode = pDDCBuffData[3];
        RetValueH = pDDCBuffData[4];
        RetValueL = pDDCBuffData[5];
        WordValue = ((U16)pDDCBuffData[4]<<8) | ((U16)pDDCBuffData[5]);
    }
    else if(CommandCode == VCP_CapabilitiesRequest)    // 1-6
    {
        RetValueH = pDDCBuffData[2];
        RetValueL = pDDCBuffData[3];
        WordAddr = ((U16)pDDCBuffData[2]<<8) | ((U16)pDDCBuffData[3]);
        WordValue = sizeof(CAP_VCP);
        if(WordAddr == WordValue)
        {
            pDDCBuffData[0]=0x83;
            pDDCBuffData[1]=0xE3;
            return 3;
        }

        #define CapLen CPCode
        CapLen = (WordAddr+32 >= WordValue)?(WordValue-WordAddr):32;
        pDDCBuffData[0]=CapLen+3+0x80;
        pDDCBuffData[1]=0xE3;
        pDDCBuffData[2]=RetValueH;
        pDDCBuffData[3]=RetValueL;
        for(ValueL = 4;ValueL<CapLen+4;ValueL++)
        {
            pDDCBuffData[ValueL] = CAP_VCP[WordAddr+ValueL-4];
        }
        #undef CapLen
        return pDDCBuffData[0]&~0x80;
    }
    else if(CommandCode == VCP_EnableApp)              // 1-7 xx
    {
        pDDCBuffData[0] = 0x80;
        return 0;//0xFE;
    }
    else if(CommandCode == VCP_AppTest)                // 1-8 xx
    {
        pDDCBuffData[0] = 0x80;
        return 0;//0xFD;
    }
    else if(CommandCode == VCP_GetTimingRequest) // 1-9
    {
        pDDCBuffData[0] = 0x06;
        pDDCBuffData[1] = 0x4E;
        // Fix me !!!! what is 0x03????
        pDDCBuffData[2] = (SyncStatus & 0x03);
        //if(g_bUnsupportMode)    pDDCBuffData[2] |= 0x80;
        //if(!g_bInputTimingStable)   pDDCBuffData[2] |= 0x40;
        if(MApp_PCMode_GetCurrentState(eWindow) == E_PCMODE_STABLE_UN_SUPPORT_MODE)  pDDCBuffData[2] |= 0x80;
        if(MApp_PCMode_GetCurrentState(eWindow) == E_PCMODE_UNSTABLE)           pDDCBuffData[2] |= 0x40;
        WordValue = MApi_XC_PCMonitor_Get_HFreqx10(eWindow);
        pDDCBuffData[3] = WordValue >> 8;
        pDDCBuffData[4] = WordValue & 0x00FF;
        WordValue = MApi_XC_PCMonitor_Get_VFreqx10(eWindow);
        pDDCBuffData[5] = WordValue >> 8;
        pDDCBuffData[6] = WordValue & 0x00FF;
        return 6;
    }
    //111----------------------------------------------------------End

    //GetValue------------------------------------------------------Start
    if(CommandCode == VCP_GetVCPFeature || CommandCode == VCP_GetPagedVCP)
    {
        //Initial-----------------------Start
        if(CommandCode == VCP_GetVCPFeature)
        {
            pDDCBuffData[0] = 0x88;
            pDDCBuffData[1] = 0x02;
            pDDCBuffData[2] = 0x00; // 0->No error, 1->Unsupport
            pDDCBuffData[3] = CPCode;
            pDDCBuffData[4] = 0x01;
            ValueH = 0x00;
            ValueL = 0x00;
            RetValueH = 0x00;
            RetValueL = 0x00;
            TPValue = 0x01;
        }
        else
        {
            pDDCBuffData[0] = 0x89;
            pDDCBuffData[1] = 0xC7;
            pDDCBuffData[2] = 0x00;
            pDDCBuffData[3] = PageValue;
            pDDCBuffData[4] = CPCode;
            pDDCBuffData[5] = 0x01;
            ValueH = 0x00;
            ValueL = 0x00;
            RetValueH = 0x00;
            RetValueL = 0x00;
            TPValue = 0x01;
        }
        //Initial-----------------------End

        //Setting---------------------------------Start
        if(CPCode == VCP_ALL_Reset && PageValue == 0)
        {
            RetValueL = 0;
            ValueL = 1;
        }
        else if(CPCode == VCP_Bri_Con_Reset && PageValue == 0)
        {
            RetValueL = 0;
            ValueL = 1;
        }
        else if(CPCode == VCP_Geometry_Reset && PageValue == 0)   // 2-2
        {
            RetValueL = 0;
            ValueL = 1;
        }
        else if(CPCode == VCP_Color_Reset && PageValue == 0)         // 2-3
        {
            RetValueL = 0;
            ValueL = 1;
        }

        else if(CPCode == VCP_ADJ_Brightness && PageValue == 0)   // 3-5
        {
            RetValueL =  ST_PICTURE.u8Brightness;
            ValueL = 100;
            TPValue = 0x00;
        }
        else if (CPCode == VCP_ADJ_Contrast && PageValue == 0)
        {
            RetValueL =  ST_PICTURE.u8Contrast;
            ValueL = 100;
            TPValue = 0x00;
        }

        else if( (CPCode==VCP_Offset_Red || CPCode==VCP_Offset_Red || CPCode==VCP_Offset_Red) && PageValue==0 )
        {
            if(IsVgaInUse())
                RetValueL = 0;
            else
                pDDCBuffData[2] = 1;

            ValueL = 100;
            TPValue = 0x00;
        }
        #if 0
        else if(CPCode == VCP_ChangeInputSource && PageValue == 0)
        {
            switch(stGenSetting.g_SysSetting.enInputSourceType)
            {
                case INPUT_SOURCE_VGA:
                    RetValueL = 1;
                    break;
                #if 0
                case INPUTSOURCE_DVI:
                    RetValueL = 3;
                    break;
                #endif
                case INPUT_SOURCE_CVBS:
                    RetValueL = 5;
                    break;
                case INPUT_SOURCE_SVIDEO:
                    RetValueL = 7;
                    break;
                case INPUT_SOURCE_YPBPR:
                    RetValueL = 12;
                    break;
            }

            ValueL = 12;
            TPValue = 0x00;
        }
        #endif
        #if 1
        else if(CPCode == VCP_COLOR_TEMP_INC && PageValue == 0 && IsVgaInUse())
        {
            RetValueL = COLOR_TEMP_INC_STEP;
            RetValueH = (COLOR_TEMP_INC_STEP>>8);
            TPValue = 0x01;
        }
        #endif
        #if 0
        else if(CPCode == VCP_COLOR_TEMP_REQ && PageValue == 0 && IsVgaInUse())
        {
            switch(stGenSetting.g_PcColorTempAdjSetting[COLOR_INPUT_PC_VGA].g_PCColorTempIndex)
            {
                case PC_COLOR_TEMP_USER:
                    RetValueL = 0;
                    break;
                case PC_COLOR_TEMP_WARM:
                    RetValueL = ((6500-3000)/COLOR_TEMP_INC_STEP);
                    break;
                case PC_COLOR_TEMP_NORMAL:
                    RetValueL = ((7500-3000)/COLOR_TEMP_INC_STEP);
                    break;
                case PC_COLOR_TEMP_COOL:
                    RetValueL = ((9300-3000)/COLOR_TEMP_INC_STEP);
                    break;
                case PC_COLOR_TEMP_SRGB:
                default:
                    RetValueL = 0x00;
                    break;
            }
            ValueL = 63;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Select_Color_Preset && PageValue == 0 && IsVgaInUse())
        {
            switch(stGenSetting.g_PcColorTempAdjSetting[COLOR_INPUT_PC_VGA].g_PCColorTempIndex)
            {
                case PC_COLOR_TEMP_USER:
                    RetValueL = 0x0B;
                    break;
                case PC_COLOR_TEMP_WARM:
                    RetValueL = 0x05;
                    break;
                case PC_COLOR_TEMP_NORMAL:
                    RetValueL = 0x06;
                    break;
                case PC_COLOR_TEMP_COOL:
                    RetValueL = 0x08;
                    break;
                case PC_COLOR_TEMP_SRGB:
                    RetValueL = 0x01;
                    break;
                default:
                    RetValueL = 0x02;
                    break;
            }
            ValueL = 0x0B;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if (CPCode == VCP_ADJ_Red_Gain && PageValue == 0)
        {
            if(IsVgaInUse()&& (stGenSetting.g_PcColorTempAdjSetting[COLOR_INPUT_PC_VGA].g_PCColorTempIndex == PC_COLOR_TEMP_USER))
                RetValueL = G_ADC_SETTING[ADC_SET_VGA].u8RedGain;
            else
                pDDCBuffData[2] = 1; //Unsupported.

            ValueL = 100;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if (CPCode == VCP_ADJ_Green_Gain && PageValue == 0)
        {
            if(IsVgaInUse()&& (stGenSetting.g_PcColorTempAdjSetting[COLOR_INPUT_PC_VGA].g_PCColorTempIndex == PC_COLOR_TEMP_USER))
                RetValueL = G_ADC_SETTING[ADC_SET_VGA].u8GreenGain;
            else
                pDDCBuffData[2] = 1; //Unsupported.

            ValueL = 100;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if (CPCode == VCP_ADJ_Blue_Gain && PageValue == 0)
        {
            if(IsVgaInUse()&& (stGenSetting.g_PcColorTempAdjSetting[COLOR_INPUT_PC_VGA].g_PCColorTempIndex == PC_COLOR_TEMP_USER))
                RetValueL = G_ADC_SETTING[ADC_SET_VGA].u8BlueGain;
            else
                pDDCBuffData[2] = 1; //Unsupported.

            ValueL = 100;
            TPValue = 0x00;
        }
        #endif
        else if (CPCode == VCP_Auto_Setup && PageValue == 0 && IsVgaInUse())
        {
            RetValueL = 0;
            ValueL = 1;
        }
        else if(CPCode == VCP_Auto_Level && PageValue == 0 && IsVgaInUse())
        {
            RetValueL = 0;
            ValueL = 1;
        }
        else if ( CPCode==VCP_ADJ_HorizontalPos && PageValue == 0 && IsVgaInUse())
        {
            WordValue = g_PcadcModeSetting[eWindow].u16HorizontalStart-MIN_PC_H_START(eWindow);
            RetValueH = WordValue >> 8;
            RetValueL = WordValue & 0x00FF;
            WordValue = MAX_PC_H_START(eWindow)-MIN_PC_H_START(eWindow);
            ValueH = WordValue >> 8;
            ValueL = WordValue & 0x00FF;
            TPValue = 0x00;
        }
        else if ( CPCode==VCP_ADJ_VerticalPos && PageValue == 0 && IsVgaInUse() )
        {
            WordValue = g_PcadcModeSetting[eWindow].u16VerticalStart-MIN_PC_V_START;
            RetValueH = WordValue >> 8;
            RetValueL = WordValue & 0x00FF;
            WordValue = MAX_PC_V_START(eWindow)-MIN_PC_V_START;
            ValueH = WordValue >> 8;
            ValueL = WordValue & 0x00FF;
            TPValue = 0x00;
        }
        else if (CPCode == VCP_ADJ_Phase && PageValue == 0 && IsVgaInUse() )
        {
            RetValueL = g_PcadcModeSetting[eWindow].u16Phase;
            ValueL = 0x3F;
            TPValue = 0x00;
        }
        else if (CPCode == VCP_ADJ_Clock && PageValue == 0 && IsVgaInUse() )
        {
            RetValueH = (g_PcadcModeSetting[eWindow].u16HorizontalTotal-MIN_PC_CLOCK(eWindow))>>8;
            RetValueL = (g_PcadcModeSetting[eWindow].u16HorizontalTotal-MIN_PC_CLOCK(eWindow))&0x00FF;
            WordValue = MAX_PC_CLOCK(eWindow)-MIN_PC_CLOCK(eWindow);
            ValueH = WordValue >> 8;
            ValueL = WordValue & 0x00ff;
            TPValue = 0x00;
        }
        #if 0
        else if(CPCode == VCP_ADJ_Zoom && PageValue == 0)
        {
            if(IsVgaInUse())
                RetValueL = g_PCColorSetting.PcZoom;
            else
                RetValueL = g_VideoSetting.Zoom;

            ValueL = MAX_ZOOM;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_ScalingMode && PageValue == 0)
        {
            if(IsVgaInUse())
                RetValueL = g_PCColorSetting.PcScalingMode;
            else
                RetValueL = g_VideoSetting.VideoScalingMode;

            switch(RetValueL)
            {
                case 0:
                        if(ChkNatureMode())
                            RetValueL = 1;
                        else
                            RetValueL = 2;
                    break;
                case 1:
                        RetValueL = 2;
                    break;
                case 2:
                        if(ChkAspectMode())
                        {
                            if( (((U32)PANEL_WIDTH*100)/g_WindowInfo[SRC1].H_CapSize) <
                                (((U32)PANEL_HEIGHT*100)/g_WindowInfo[SRC1].V_CapSize) )
                                RetValueL = 4;
                            else
                                RetValueL = 3;
                        }
                        else
                            RetValueL = 2;
                    break;
            }

            ValueL = 4;
            TPValue = 0x00;
        }
        #endif
        else if(CPCode == VCP_ADJ_AudioVolume && PageValue == 0)  // 2-16
        {
            RetValueL = stGenSetting.g_SoundSetting.Volume;

            ValueL = 100;
            TPValue = 0x00;
        }
        else if(CPCode == VCP_ADJ_TV_Audio_Stereo && PageValue == 0)
        {
            ValueL = 3;
            TPValue = 0x00;
        }
        #if 0
        else if(CPCode == VCP_OSD_Lock && PageValue == 0)
        {
            if(g_SysSetting.SystemStatus & SYSTEM_OSDLOCK)
                RetValueL = 1;
            else
                RetValueL = 2;

            ValueL = 2;
            TPValue = 0x00;
        }
        #endif
        else if(CPCode == VCP_ADJ_Language && PageValue == 0)
        {
            switch(GET_OSD_MENU_LANGUAGE())
            {
                default:
                case LANGUAGE_ENGLISH:
                    RetValueL=2;
                    break;
                case LANGUAGE_SPANISH:
                    RetValueL=10;
                    break;
                #if 0
                case LANGUAGE_GERMAN:
                    RetValueL=4;
                    break;
                case LANGUAGE_FRANCE:
                    RetValueL=3;
                    break;
                case LANGUAGE_ITALIAN:
                    RetValueL=5;
                    break;
                case LANGUAGE_PYCCK:
                    RetValueL=9;
                    break;
                case LANGUAGE_NETH:
                    RetValueL=11;
                    break;
                case LANGUAGE_SVENSKA:
                    RetValueL=12;
                    break;
                #endif
            }
            ValueL = 12;
            TPValue = 0x00;
        }
        #if 0
        else if(CPCode == VCP_ADJ_Sharpness && PageValue == 0 && IsVgaInUse() )
        {
            RetValueL = stGenSetting.g_PCColorSetting[COLOR_INPUT_PC_VGA][PC_COLOR_MODE_USER].u8Sharpness+1;

            ValueL = 5;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_TV_Saturation && PageValue == 0)
        {
            RetValueL = stGenSetting.g_VideoQualitySetting[VIDEO_PICTURE_SETTING][PICTURE_MODE_USER].stVideoAdjust.u8Saturation;

            ValueL = 100;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if((CPCode==VCP_ADJ_TV_Sharpness || CPCode==VCP_ADJ_Sharpness) && PageValue == 0)
        {
            RetValueL = stGenSetting.g_VideoQualitySetting[VIDEO_PICTURE_SETTING][PICTURE_MODE_USER].stVideoAdjust.u8Sharpness;
            ValueL = 5;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_TV_Contrast && PageValue == 0)
        {
            if(IsVgaInUse())
                RetValueL = stGenSetting.g_PCColorSetting[COLOR_INPUT_PC_VGA][PC_COLOR_MODE_USER].u8Contrast;
            else
                RetValueL = stGenSetting.g_VideoQualitySetting[VIDEO_PICTURE_SETTING][PICTURE_MODE_USER].stVideoAdjust.u8Contrast;

            ValueL = 100;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_TV_Hue && PageValue == 0)
        {
            RetValueL = stGenSetting.g_VideoQualitySetting[VIDEO_PICTURE_SETTING][PICTURE_MODE_USER].stVideoAdjust.u8Hue;

            ValueL = 100;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Window_Select && PageValue == 0)
        {
            RetValueL = (Get_DDC_PipSelect()?2:0);
            ValueL = 2;
            TPValue = 0;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_ColorEnhance && PageValue == 0)
        {
            if(IsVgaInUse())
                RetValueL = g_PCColorSetting.ColorEnhanceIndex - COLOR_ENHANCE_TEXT;
                RetValueL = stGenSetting..g_PcColorTempAdjSetting[COLOR_INPUT_PC_VGA].g_PCColorTempIndex;
            else
                RetValueL = g_VideoSetting.PictureModeIndex - PICTURE_MODE_TEXT;
            ValueL = 3;
            TPValue = 0;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_Audio_Src_Select && PageValue == 0)
        {
            if(GetAudioSourceValue() == SOUND_SOURCE_MAIN)
                RetValueL = 0x00; // PC
            else
                RetValueL = 0x01; // Video

            ValueL = 1;
            TPValue = 0;
        }
        #endif
        else if(CPCode == VCP_MonitorType && PageValue == 0)
        {
            RetValueL = 3;
            ValueL = 3;
            TPValue = 0x01;
        }
        #if 0
        else if(CPCode == VCP_PowerMode && PageValue == 0)
        {
            if(g_SysSetting.SystemStatus & SYSTEM_POWERON)
                RetValueL = 1;
            else
                RetValueL = 4;

            RetValueL = 4;
            TPValue = 0x01;
        }
        #endif
        else if(CPCode == VCP_MCCS_Version && PageValue == 0)
        {
            RetValueH = 2;
            RetValueL = 0;
            ValueH = 2;
            ValueL = 0;
            TPValue = 0x01;
        }
        else if(CPCode == VCP_EnableApp && PageValue == 0)
        {
            RetValueL = 0x45;
            ValueH = 0xFF;
            ValueL = 0xFF;
            TPValue = 0x01;
        }
        else if(CPCode == VCP_ScalerType && PageValue == 0)
        {
            RetValueL =0x05;
            TPValue = 0x01;
        }
        #if 0
        else if(CPCode == VCP_FW_Version && PageValue == 0)
        {
            RetValueH = 0x00;
            RetValueL = FW_VERSION;
            ValueL = 0xFF;
            TPValue = 0x01;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Resolution_Notifier && PageValue == 0)
        {
            if(g_SysSetting.SystemStatus & SYSTEM_RES_NOTICE)
                RetValueL = 1;
            else
                RetValueL = 0;

            ValueL = 1;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_H_FREQ && PageValue == 0 && IsVgaInUse())
        {
            WordValue = (mvideo_sc_cal_hfreqx10(g_wHorizontalPeriod))*10;

            RetValueL = WordValue;
            RetValueH = WordValue>>8;

            ValueL = 0xFF;
            ValueH = 0xFF;
            TPValue = 0x01;
        }
        #endif
        #if 0
        else if(CPCode == VCP_V_FREQ && PageValue == 0 && IsVgaInUse())
        {
            WordValue = mvideo_sc_cal_hfreqx10((MDrv_Scaler_CalculateHFreqX10(g_wHorizontalPeriod)), g_wVerticalTotal)*10;

            RetValueL = WordValue;
            RetValueH = WordValue>>8;

            ValueL = 0xFF;
            ValueH = 0xFF;
            TPValue = 0x01;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Usage_Time && PageValue == 0)
        {
            WordValue = g_BLTimeSetting.dwBLTimeHours;

            RetValueL = WordValue;
            RetValueH = WordValue>>8;

            ValueL = 0xFF;
            ValueH = 0xFF;
            TPValue = 0x01;
        }
        #endif

        //Setting---------------------------------End

        //Transmission----------------------------Start
        if(CommandCode == VCP_GetVCPFeature)
        {
            pDDCBuffData[4] = TPValue;
            pDDCBuffData[5] = ValueH;
            pDDCBuffData[6] = ValueL;
            pDDCBuffData[7] = RetValueH;
            pDDCBuffData[8] = RetValueL;
            return 8;
        }
        else
        {
            pDDCBuffData[5] = TPValue;
            pDDCBuffData[6] = ValueH;
            pDDCBuffData[7] = ValueL;
            pDDCBuffData[8] = RetValueH;
            pDDCBuffData[9] = RetValueL;
            return 9;
        }
        //Transmission----------------------------End
    }
    //GetValue------------------------------------------------------End

    //SetValue------------------------------------------------------Start
    if(CommandCode == VCP_SetVCPFeature || CommandCode == VCP_SetPagedVCP)
    {
        //Initial----------------------------Start
        pDDCBuffData[2] = 0x00; // Result Code
        ValueH = 0x00;
        ValueL = 0xFF;
        TPValue = 0x01;
        //Initial----------------------------End

        //Setting-------------------------------Start
        if(CPCode == VCP_ALL_Reset && PageValue == 0)     // 3-1
        {
            if(WordValue != 0)
            {
                //ExecFactoryRecall();    //km
                #if 0    // feb/09/2006 Alex Liu.
                //msAutoGeometry(AUTO_TUNE_HV_POSITION);        //km

                AdjustPcHPosition(MIA_NOTHING);
                AdjustPcVPosition(MIA_NOTHING);
                //AdjustPcClock(MIA_NOTHING);
                //AdjustPcPhase(MIA_NOTHING);
                usrSaveModeSetting(g_ucRamIndex);
                #endif
                //MDrv_Auto_Geometry(AUTO_TUNE_HV_POSITION);
                //MApp_UiMenuFunc_AdjustPcHPos(MIA_NOTHING);
                //MApp_UiMenuFunc_AdjustPcVPos(MIA_NOTHING);

           }
            ValueL = 1;
        }
        #if 0
        else if(CPCode == VCP_Bri_Con_Reset && PageValue == 0)
        {
            if(WordValue != 0 && IsVgaInUse())
            {
                MApp_DataBase_RestoreDefaultPc();
            }
            ValueL = 1;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Geometry_Reset && PageValue == 0)   // 3-2
        {
            if(WordValue != 0 && IsVgaInUse())
            {
                #if 0    // Jan/24/2006 Alex Liu.
                msAutoGeometry(AUTO_TUNE_HV_POSITION);

                AdjustPcHPosition(MIA_NOTHING);
                AdjustPcVPosition(MIA_NOTHING);
                //AdjustPcClock(MIA_NOTHING);
                //AdjustPcPhase(MIA_NOTHING);
                usrSaveModeSetting(g_ucRamIndex);
                #endif
                //MApp_UiMenuFunc_AdjustPcHPos(MIA_NOTHING);
                //MApp_UiMenuFunc_AdjustPcVPos(MIA_NOTHING);
                //MApp_UiMenuFunc_AdjustPcClock(MIA_NOTHING);
                //MApp_UiMenuFunc_AdjustPcPhase(MIA_NOTHING);

            }
            ValueL = 1;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Color_Reset && PageValue == 0)        // 3-3
        {
            if(WordValue != 0 && IsVgaInUse())
            {
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex = PC_COLOR_TEMP_WARM;
                msAPI_ACE_SetPCColor( g_pstPcColorSetting, g_pstPcColorTempAdjSetting );
            }
            ValueL = 1;
        }
        #endif
        else if(CPCode == VCP_ADJ_Brightness && PageValue == 0)   // 3-5
        {
            if (IsVgaInUse())
            {
                //stGenSetting.g_PCColorSetting[COLOR_INPUT_PC_VGA][PC_COLOR_MODE_USER].u8Brightness = RetValueL;
                //MApp_Picture_Setting_GetPictureValue(PICTURE_VALUE_BRIGHTNESS) = RetValueL;
            }
            else
            {
                //stGenSetting.g_VideoQualitySetting[VIDEO_PICTURE_SETTING][PICTURE_MODE_USER].stVideoAdjust.u8Brightness = RetValueL;
                //MApp_Picture_Setting_GetPictureValue(PICTURE_VALUE_BRIGHTNESS) = RetValueL;
            }

            ST_PICTURE.u8Brightness = RetValueL;
            //ZUI_TODO: MApp_UiMenuFunc_Adju16B1_Picture_User1_Brightness(MIA_NOTHING);

            ValueL = 100;
            TPValue = 0x00;
        }
        else if(CPCode == VCP_ADJ_Contrast && PageValue == 0)     // 3-6
        {
            if (IsVgaInUse())
            {
                //stGenSetting.g_PCColorSetting[COLOR_INPUT_PC_VGA][PC_COLOR_MODE_USER].u8Contrast= RetValueL;
                //MApp_Picture_Setting_GetPictureValue(PICTURE_VALUE_CONTRAST) = RetValueL;
            }
            else
            {
                //stGenSetting.g_VideoQualitySetting[VIDEO_PICTURE_SETTING][PICTURE_MODE_USER].stVideoAdjust.u8Contrast = RetValueL;
                //MApp_Picture_Setting_GetPictureValue(PICTURE_VALUE_CONTRAST) = RetValueL;
            }

            ST_PICTURE.u8Contrast = RetValueL;
            //ZUI_TODO: MApp_UiMenuFunc_Adju16B1_Picture_User1_Contrast(MIA_NOTHING);

            ValueL = 100;
            TPValue = 0x00;
        }
        #if 0
        else if( (CPCode==VCP_Offset_Red || CPCode==VCP_Offset_Red || CPCode==VCP_Offset_Red) && PageValue==0 )
        {
            if(SrcTypeIsPC(SRC1))
            {
                if(g_PCColorSetting.ColorTempIndex == PC_COLOR_TEMP_SRGB && IsPcNormalColorMode())
                {
                    g_PCColorSetting.SRGBBlacklevel = RetValueL;
                }
                else
                {
                    g_PCColorSetting.Blacklevel = RetValueL;
                }
                AdjustPcBlacklevel(MIA_NOTHING);

                if(IsSrcTypeVga(SRC1))
                    usrSavePCColorSetting(PCColor_SET_VGA);
                else
                    usrSavePCColorSetting(PCColor_SET_DVI);
            }
            else
                pDDCBuffData[2] = 1; //Unsupported.

            ValueL = 100;
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ChangeInputSource && PageValue == 0)
        {
                switch(RetValueL)
                {
                    case 1:
                        g_SysSetting.ucInputSourceType = INPUTSOURCE_VGA;
                        break;
                    case 3:
                        g_SysSetting.ucInputSourceType = INPUTSOURCE_DVI;
                        break;
                    case 5:
                        g_SysSetting.ucInputSourceType = INPUTSOURCE_CVBS;
                        break;
                    case 7:
                        g_SysSetting.ucInputSourceType = INPUTSOURCE_SVIDEO;
                        break;
                    case 12:
                        g_SysSetting.ucInputSourceType = INPUTSOURCE_YCBCR;
                        break;
                }
                ValueL = 12;
                TPValue = 0x00;

                InputSourceSwitch(g_SysSetting.ucInputSourceType);

                usrSaveSystemSetting();
        }
        #endif
        #if 0
        else if(CPCode == VCP_COLOR_TEMP_REQ && PageValue == 0 && IsVgaInUse())
        {
            WordValue = 3000 + (WordValue * COLOR_TEMP_INC_STEP);

            if( WordValue <= ((6500+7500)/2) )
            {
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex = PC_COLOR_TEMP_WARM;
            }
            else if( WordValue <= ((7500+9300)/2) && WordValue > ((6500+7500)/2) )
            {
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex = PC_COLOR_TEMP_NORMAL;
            }
            else
            {
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex = PC_COLOR_TEMP_COOL;
            }

            MApp_UiMenuFunc_AdjustOptionColorMode();


            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Select_Color_Preset && PageValue == 0 && IsVgaInUse())        // 3-7
        {
            if(RetValueL == 0x0B)
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex=PC_COLOR_TEMP_USER;
            else if(RetValueL == 0x05)
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex=PC_COLOR_TEMP_WARM;
            else if(RetValueL == 0x06)
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex=PC_COLOR_TEMP_NORMAL;
            else if(RetValueL == 0x08)
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex=PC_COLOR_TEMP_COOL;
            //else if(RetValueL == 0x02)
                //stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex=PC_COLOR_TEMP_NATIVE;
            else if(RetValueL == 0x01)
                stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex=PC_COLOR_TEMP_SRGB;

            ValueL = 0x0B;
            TPValue = 0x00;

            MApp_UiMenuFunc_AdjustOptionColorMode();

        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_Red_Gain && PageValue == 0 &&
                IsVgaInUse() && stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex==PC_COLOR_TEMP_USER)    // 3-8
        {
            g_PCColorTempSetting.RedColor = Get100ToRealValue(RetValueL, MIN_RED_COLOR_TEMP, MAX_RED_COLOR_TEMP);
            AdjustRedColor(MIA_NOTHING);
            ValueL = 100;
            TPValue = 0x00;

            usrSavePCColorTempSetting( &g_PCColorTempSetting, g_PCColorSetting.ColorTempIndex );
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_Green_Gain && PageValue == 0 &&
                IsVgaInUse() && stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex==PC_COLOR_TEMP_USER)    // 3-9
        {
            g_PCColorTempSetting.GreenColor = Get100ToRealValue(RetValueL, MIN_GREEN_COLOR_TEMP, MAX_GREEN_COLOR_TEMP);
            AdjustGreenColor(MIA_NOTHING);
            ValueL = 100;
            TPValue = 0x00;

            usrSavePCColorTempSetting( &g_PCColorTempSetting, g_PCColorSetting.ColorTempIndex );
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_Blue_Gain && PageValue == 0 &&
                IsVgaInUse() && stGenSetting.g_PcColorTempAdjSetting.g_PCColorTempIndex==PC_COLOR_TEMP_USER) // 3-10
        {
            g_PCColorTempSetting.BlueColor = Get100ToRealValue(RetValueL, MIN_BLUE_COLOR_TEMP, MAX_BLUE_COLOR_TEMP);
            AdjustBlueColor(MIA_NOTHING);
            ValueL = 100;
            TPValue = 0x00;

            usrSavePCColorTempSetting( &g_PCColorTempSetting, g_PCColorSetting.ColorTempIndex );
        }
        #endif
         #if 0
        else if(CPCode == VCP_Auto_Setup && PageValue == 0 && IsVgaInUse())        // 3-11
        {

            if(WordValue != 0)
                AutoConfig();
            ValueL = 1;

        }
        #endif
        #if 0
        else if(CPCode == VCP_Auto_Level && PageValue == 0 && IsVgaInUse())        // 3-11
        {
            if(WordValue != 0)
                AutoLevel();
            ValueL = 1;
        }
        #endif
        else if(CPCode == VCP_ADJ_HorizontalPos && PageValue == 0 && IsVgaInUse())    // 3-12
        {
            g_PcadcModeSetting[eWindow].u16HorizontalStart = MIN_PC_H_START(eWindow) + WordValue;
            ValueH = (MAX_PC_H_START(eWindow) - MIN_PC_H_START(eWindow)) >> 8;
            ValueL = (MAX_PC_H_START(eWindow) - MIN_PC_H_START(eWindow)) & 0x00FF;
            TPValue = 0x00;
        }
        else if(CPCode == VCP_ADJ_VerticalPos && PageValue == 0)    // 3-13
        {
            g_PcadcModeSetting[eWindow].u16VerticalStart = MIN_PC_V_START + WordValue;
            //MDrv_SC_ip_set_pc_v_position(MIA_NOTHING);
            ValueH = (MAX_PC_V_START(eWindow) - MIN_PC_V_START) >> 8;
            ValueL = (MAX_PC_V_START(eWindow) - MIN_PC_V_START) & 0x00FF;
            TPValue = 0x00;
        }
        else if(CPCode == VCP_ADJ_Phase && PageValue == 0 && IsVgaInUse())     // 3-14
        {
            g_PcadcModeSetting[eWindow].u16Phase = WordValue;
            //MDrv_ADC_SetADCPhase(MIA_NOTHING);
            ValueL = 0x3F;
            TPValue = 0x00;
        }
        else if(CPCode == VCP_ADJ_Clock && PageValue == 0 && IsVgaInUse())    // 3-4
        {
            g_PcadcModeSetting[eWindow].u16HorizontalTotal = WordValue + MIN_PC_CLOCK(eWindow);
            //MDrv_ADC_SetADCClk(MIA_NOTHING);
            ValueH = ((WORD)(MAX_PC_CLOCK(eWindow) - MIN_PC_CLOCK(eWindow))) >> 8;
            ValueL = ((WORD)(MAX_PC_CLOCK(eWindow) - MIN_PC_CLOCK(eWindow))) & 0x00FF;
            TPValue = 0x00;
        }
        #if 0
        else if(CPCode == VCP_ADJ_Zoom && PageValue == 0 )&& !IsPopTurnOn())
        {
            if(SrcTypeIsPC(SRC1))
                g_PCColorSetting.PcZoom = RetValueL;
            else
                g_VideoSetting.Zoom = RetValueL;

            AdjustZoom(MIA_NOTHING);
            ValueL = MAX_ZOOM;
            TPValue = 0x00;

            if(SrcTypeIsPC(SRC1))
            {
                if(IsSrcTypeVga(SRC1))
                    usrSavePCColorSetting(PCColor_SET_VGA);
                else
                    usrSavePCColorSetting(PCColor_SET_DVI);
            }
            else
            {
                usrSaveVideoSetting();
            }
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_ScalingMode && PageValue == 0 && !IsPopTurnOn())
        {
            switch(RetValueL)
            {
                case 1:
                    g_ucMenuItemIndex = 0;
                    break;
                case 2:
                    g_ucMenuItemIndex = 1;
                    break;
                case 3:
                case 4:
                    g_ucMenuItemIndex = 2;
                    break;
            }
            ExecSetScalingMode();
            ValueL = 4;
            TPValue = 0x00;

            if(SrcTypeIsPC(SRC1))
            {
                if(IsSrcTypeVga(SRC1))
                    usrSavePCColorSetting(PCColor_SET_VGA);
                else
                    usrSavePCColorSetting(PCColor_SET_DVI);
            }
            else
            {
                usrSaveVideoSetting();
            }
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_AudioVolume && PageValue == 0)  // 3-16
        {
            g_SoundSetting.Volume = RetValueL;
            AdjustVolume(MIA_NOTHING);
            ValueL = 100;
            TPValue = 0x00;

            usrSaveSoundSetting();
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_TV_Audio_Stereo && PageValue == 0)
        {
            if(RetValueL == 0)
                g_SoundSetting.AudioMute = 1;
            else
                g_SoundSetting.AudioMute = 0;

            ExecMuteFunc();
            TPValue = 0x00;

            usrSaveSoundSetting();
        }
        #endif
        #if 0
        else if(CPCode == VCP_OSD_Lock && PageValue == 0)
        {
            if(RetValueL == 1)
                g_SysSetting.SystemStatus |= SYSTEM_OSDLOCK;
            else if(RetValueL == 2)
                g_SysSetting.SystemStatus &= ~SYSTEM_OSDLOCK;

            ValueL = 2;
            TPValue = 0x00;

            usrSaveSystemSetting();
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_Language && PageValue == 0) // 3-17
        {
            switch(WordValue)
            {
                case 2:
                    g_SysSetting.Language=LANGUAGE_ENGLISH;
                    break;
                case 4:
                    g_SysSetting.Language=LANGUAGE_GERMAN;
                    break;
                case 3:
                    g_SysSetting.Language=LANGUAGE_FRANCE;
                    break;
                case 5:
                    g_SysSetting.Language=LANGUAGE_ITALIAN;
                    break;
                case 10:
                    g_SysSetting.Language=LANGUAGE_SPANISH;
                    break;
                case 9:
                    g_SysSetting.Language=LANGUAGE_PYCCK;
                    break;
                case 11:
                    g_SysSetting.Language=LANGUAGE_NETH;
                    break;
                case 12:
                    g_SysSetting.Language=LANGUAGE_SVENSKA;
                    break;
            }
            ValueL = 12;
            TPValue = 0x00;

            usrSaveSystemSetting();
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_Sharpness && PageValue == 0 && IsVgaInUse())
        {
            g_PCColorSetting.PcSharpness = RetValueL-1;
            AdjustSharpness(MIA_NOTHING);
            ValueL = 5;
            TPValue = 0x00;

            if(SrcTypeIsPC(SRC1))
            {
                if(IsSrcTypeVga(SRC1))
                    usrSavePCColorSetting(PCColor_SET_VGA);
                else
                    usrSavePCColorSetting(PCColor_SET_DVI);
            }
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_TV_Saturation && PageValue == 0)
        {
            if( (Get_DDC_PipSelect() && SrcTypeIsPC(SRC1)) ||
                (!Get_DDC_PipSelect() && SrcTypeIsVideo(SRC1)) )
            {
                BYTE ucSrcIdx = SrcTypeIsVideo(SRC1)?SRC1:SRC2;
                if( SRC_TYPE_IS_ANLG_YUV(ucSrcIdx) || SRC_WIN_IS_YUV(ucSrcIdx) )
                    g_VideoSetting.HDTVadjust.Saturation= RetValueL;
                else
                    g_VideoSetting.SDTVadjust.Saturation = RetValueL;
                AdjustPictureSaturation(MIA_NOTHING);
                ValueL = 100;

                usrSaveVideoSetting();
            }

            TPValue = 0x00;
        }
        #endif
        #if 0
        else if((CPCode==VCP_ADJ_TV_Sharpness || CPCode==VCP_ADJ_Sharpness) && PageValue == 0)
        {
            if(SrcTypeIsVideo(SRC1))
            {
                BYTE ucSrcIdx = SrcTypeIsVideo(SRC1)?SRC1:SRC2;
                if( SRC_TYPE_IS_ANLG_YUV(ucSrcIdx) || SRC_WIN_IS_YUV(ucSrcIdx) )
                    g_VideoSetting.HDTVadjust.Sharpness= RetValueL-1;
                else
                    g_VideoSetting.SDTVadjust.Sharpness = RetValueL-1;

                AdjustSharpness(MIA_NOTHING);
                ValueL = 5;

                usrSaveVideoSetting();
            }
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_TV_Contrast && PageValue == 0)
        {
            if( (Get_DDC_PipSelect() && SrcTypeIsPC(SRC1)) ||
                (!Get_DDC_PipSelect() && SrcTypeIsVideo(SRC1)) )
            {
                BYTE ucSrcIdx = SrcTypeIsVideo(SRC1)?SRC1:SRC2;
                if( SRC_TYPE_IS_ANLG_YUV(ucSrcIdx) || SRC_WIN_IS_YUV(ucSrcIdx) )
                    g_VideoSetting.HDTVadjust.Contrast = RetValueL;
                else
                    g_VideoSetting.SDTVadjust.Contrast = RetValueL;
                AdjustPictureContrast(MIA_NOTHING);
                ValueL = 100;

                usrSaveVideoSetting();
            }
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_TV_Hue && PageValue == 0)
        {
            if( (Get_DDC_PipSelect() && SrcTypeIsPC(SRC1)) ||
                (!Get_DDC_PipSelect() && SrcTypeIsVideo(SRC1)) )
            {
                BYTE ucSrcIdx = SrcTypeIsVideo(SRC1)?SRC1:SRC2;
                if( SRC_TYPE_IS_ANLG_YUV(ucSrcIdx) || SRC_WIN_IS_YUV(ucSrcIdx) )
                    g_VideoSetting.HDTVadjust.Hue= RetValueL;
                else
                    g_VideoSetting.SDTVadjust.Hue = RetValueL;
                AdjustPictureHue(MIA_NOTHING);
                ValueL = 100;

                usrSaveVideoSetting();
            }
            TPValue = 0x00;
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_ColorEnhance && PageValue == 0)
        {
            if(SrcTypeIsPC(SRC1))
                g_PCColorSetting.ColorEnhanceIndex = RetValueL + COLOR_ENHANCE_TEXT;
            else
                g_VideoSetting.PictureModeIndex = RetValueL + PICTURE_MODE_TEXT;

            SetupColor(SRC1);
            ValueL = 3;
            TPValue = 0;

            if(SrcTypeIsPC(SRC1))
            {
                if(IsSrcTypeVga(SRC1))
                    usrSavePCColorSetting(PCColor_SET_VGA);
                else
                    usrSavePCColorSetting(PCColor_SET_DVI);
            }
            else
            {
                usrSaveVideoSetting();
            }
        }
        #endif
        #if 0
        else if(CPCode == VCP_ADJ_Audio_Src_Select && PageValue == 0)
        {
            if(RetValueL == 0)
                g_SoundSetting.SoundSource = SOUND_SOURCE_MAIN;
            else if(RetValueL == 1)
                g_SoundSetting.SoundSource = SOUND_SOURCE_SUB;

            ExecAudioSource();
            ValueL = 1;
            TPValue = 0;

            usrSaveSoundSetting();
        }
        #endif
        #if 0
        else if(CPCode == VCP_PowerMode && PageValue == 0)
        {
            if((RetValueL==1) && !(g_SysSetting.SystemStatus & SYSTEM_POWERON)) // Turn On
            {
                g_ucMenuPageIndex = MENU_POWER_OFF;
                g_ucMenuItemIndex = 0;
                ExecuteKeyEvent(MIA_GOTONEXT);
            }
            else if((RetValueL==4) && (g_SysSetting.SystemStatus & SYSTEM_POWERON)) // Turn Off
            {
                ExecuteKeyEvent(MIA_POWER);
            }

            usrSaveSystemSetting();

            RetValueL = 4;
            TPValue = 0x01;
        }
        #endif
        #if 0
        else if(CPCode == VCP_Resolution_Notifier && PageValue == 0)
        {
            if(RetValueL == 0) // Off
            {
                ExecDisableResolutionNotify();
            }
            else if(RetValueL == 1) // On
            {
                if(!(g_SysSetting.SystemStatus & SYSTEM_RES_NOTICE))
                    ExecStartResolutionNotify();
                g_SysSetting.SystemStatus |= SYSTEM_RES_NOTICE;
            }

            usrSaveSystemSetting();

            ValueL = 1;
            TPValue = 0;
        }
        #endif

        // Fail condition ---------------------------
        else
        {
            pDDCBuffData[2] = 0x01;
        }
        //Setting----------------------------------End

        //Transmission-----------------------------Start
        if(CommandCode == VCP_SetVCPFeature)
        {
            return 0;
        }
        else
        {
            pDDCBuffData[0] = 0x89;
            pDDCBuffData[1] = 0xC7;
            pDDCBuffData[3] = PageValue;
            pDDCBuffData[4] = CPCode;
            pDDCBuffData[5] = TPValue;
            pDDCBuffData[6] = ValueH;
            pDDCBuffData[7] = ValueL;
            pDDCBuffData[8] = RetValueH;
            pDDCBuffData[9] = RetValueL;
            return 9;
        }
        //Transmission-------------------------------End
    }
    //SetValue------------------------------------------------------End
    else if(CommandCode == VCP_SaveCurrentSetting)  // 1-10
    {
        //usrSaveMenu(USER_SAVE_SOURCE_DIRECTLY);    //km
        return 0;
    }
    else if(CommandCode == VCP_GetVCPPage)              // 1-11
    {
        pDDCBuffData[0]=0x83;
        pDDCBuffData[1]=0xC5;
        pDDCBuffData[2]=0;
        pDDCBuffData[3]=3;
        return 3;
    }
    pDDCBuffData[0] = 0x80;
    return 0;
}

U8 MApp_DDC2BI_FactoryAdjustment(U8 *pDDCBuffData)
{
    U8 CPCode;
    U16 WordValue;
    U16 wNvrAddress = 0;
    //U8 length = 0;
    BYTE i;
    //111----------------------------------------------------------Start
    {
        CPCode = pDDCBuffData[2];
        WordValue = ((U16)pDDCBuffData[3]<<8) | ((U16)pDDCBuffData[4]);
    }

    DDC_MSG(printf("CPCode %bu\n", CPCode));
    DDC_MSG(printf("WordValue 0x%x\n", WordValue));

    //SetValue------------------------------------------------------Start
    {
        //Setting-------------------------------Start
        switch(CPCode)
        {
            case 0x10:
                ST_PICTURE.u8Contrast = WordValue;
                //MApi_XC_ACE_PicSetContrast( MAIN_WINDOW, MApi_XC_IsYUVSpace(MAIN_WINDOW), MApp_Scaler_FactoryContrast(msAPI_Mode_PictureContrastN100toReallyValue(ST_PICTURE.u8Contrast), ST_SUBCOLOR.u8SubContrast) );
                MApp_XC_PQ_Set_Contrast( MAIN_WINDOW, FALSE);
                break;

            case 0xE7://ABUS_EEPROM_READ:    //EEPROM READ
            {
                // EEPROM Read A0,A2,A4,A6,A8,AA,AC,AE
                if((pDDCBuffData[3] >=0xA0)&&(pDDCBuffData[3] <= 0xAE ))
                {
                    wNvrAddress=(pDDCBuffData[3]&0x0F);    // make 0,2,4,6
                    wNvrAddress=(wNvrAddress<<7)|pDDCBuffData[4];
                }
                // EEPROM Read B0,B2,B4,B6,B8,BA,BC,BE
                else if((pDDCBuffData[3] >=0xB0)&&(pDDCBuffData[3] <= 0xBE ))
                {
                    wNvrAddress=((pDDCBuffData[3]&0x0F)>>1);    //make 0,2,4,6 --> 0,1,2,3,4
                    wNvrAddress=((wNvrAddress+8)<<8)|pDDCBuffData[4];
                }
                // EEPROM Read C0,C2,C4,C6,C8,CA,CC,CE
                else if((pDDCBuffData[3] >=0xC0)&&(pDDCBuffData[3] <= 0xCE ))
                {
                    wNvrAddress=((pDDCBuffData[3]&0x0F)>>1);    //make 0,2,4,6 --> 0,1,2,3,4
                    wNvrAddress=((wNvrAddress+16)<<8)|pDDCBuffData[4];
                }
                else if((pDDCBuffData[3] >=0xD0)&&(pDDCBuffData[3] <= 0xDE ))
                {
                    wNvrAddress=((pDDCBuffData[3]&0x0F)>>1);    //make 0,2,4,6 --> 0,1,2,3,4
                    wNvrAddress=((wNvrAddress+24)<<8)|pDDCBuffData[4];
                }

                DDC_MSG(printf("wNvrAddress %x \n", wNvrAddress));
                //nvrReadPage(wNvrAddress, 128, (BYTE *)&DDCBuffer);

                #if (EEPROM_DB_STORAGE==EEPROM_SAVE_ALL)
                msAPI_rmBurstReadBytes(wNvrAddress, (BYTE *)pDDCBuffData, 128);
                #endif

                for(i=0; i<128; i++)
                {
                    *pDDCBuffData = i;
                    pDDCBuffData++;
                }

                return 128;
                break;
            }

#if 0       // comment out by Daten, the length was set to 0 in the begining and these codes do nothing
            case 0xE8://ABUS_EEPROM_WRITE:    //EEPROM WRITE
                {
                    // EEPROM Write A0,A2,A4,A6,A8,AA,AC,AE
                    if ( (pDDCBuffData[3] >=0xA0)&&(pDDCBuffData[3] <= 0xAE ))
                    {
                        if((length >= 1)&&(length <= 16)) //  Length 5(1+4) ~ 20(16+4)
                        {
                            wNvrAddress=(pDDCBuffData[3]&0x0F);    // make 0,2,4,6
                            wNvrAddress=(wNvrAddress<<7)|pDDCBuffData[4];
                        }
                    }
                    // EEPROM Write B0,B2,B4,B6,B8,BA,BC,BE
                    else if ((pDDCBuffData[3] >=0xB0)&&(pDDCBuffData[3] <= 0xBE ))
                    {
                        if((length >= 1)&&(length <= 16)) //  Length 5(1+4) ~ 20(16+4)
                        {
                            wNvrAddress=((pDDCBuffData[3]&0x0F)>>1);    // make 0,2,4,6
                            wNvrAddress=((wNvrAddress+8)<<8)|pDDCBuffData[4];
                        }
                    }

                    //nvrWritePage(wNvrAddress, length, (BYTE *)&DDCBuffer[6]);
                    #if (EEPROM_DB_STORAGE==EEPROM_SAVE_ALL)
                    msAPI_rmBurstWriteBytes(wNvrAddress, (BYTE *)&pDDCBuffData[6], length);
                    #endif
                }
                break;
#endif
            default:
                pDDCBuffData[2] = 0x01;
                break;

        }
        //Setting----------------------------------End
    }
    //SetValue------------------------------------------------------End

    pDDCBuffData[0] = 0x80;
    return 0;
}
#else
U8 code DDC_BI_Dummy;
#endif

