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
#ifndef _BIN_INFO_H_
#define _BIN_INFO_H_
////////////////////////////////////////////////////////////////////////////////
///@file BinInfo.h
///@version rev.00 00000
///@author MStarSemi Inc.
///@brief Binary files information, Unique ID for each binary used to identify
///
/// Binary file information description include
///     - Binary ID Name, ID code
///     - Binary File Reserved Space, Prefix Word "//~"
///     - Binary File Location, Prefix Word "//@"
/// Example:
///#define BIN_ID_CODE_AEON_MVF 0x0051 //~40KB+512 //@..\LIB\S4\aeon_mvf.bin
///     - Reserved Space 40.5KB
///#define BIN_ID_CODE_AEON_NOSHK 0x0052 //~128KB //@ ..\LIB\S4\HKAEON.bin
///     - Reserved Space 128KB
///
/// PS. 0xC000~0xCFFF Reserved for Customer, Please avoid using these IDs
///
///@endcode
////////////////////////////////////////////////////////////////////////////////


// Code: Audio
#define BIN_ID_CODE_AUDIO_DSP       0x0001  //~800KB    //@..\..\..\core\bin\melody\audio\audio_dsp_melody.bin
//#define BIN_ID_CODE_SE_AUDIO        0x0001  //~1KB     //@..\..\..\core\bin\melody\audio\out_dvb_melody_se.bin
//#define BIN_ID_CODE_ADVSND_AUDIO    0x0002  //~10KB     //@..\..\..\core\bin\melody\audio\out_dvb_melody_advsnd.bin


//#define BIN_ID_CODE_DEC_AUDIO_COMP  0x000A  //~800KB    //@..\..\..\core\bin\melody\audio\audio_dsp_melody.bin -g
//#define BIN_ID_CODE_ADVSND_AUDIO_COMP   0x000B  //~10KB     //@..\..\..\core\bin\melody\audio\out_dvb_melody_advsnd.bin -g

#if( ENABLE_AUDIO_DEC_R2_BIN )
//#define BIN_ID_CODE_AUDIO_DEC_R2_NO_COMP    0x0001  //~1480KB     //@..\..\..\core\bin\melody\audio\aucode_adec_r2.bin
//#define BIN_ID_CODE_AUDIO_DEC_R2_COMP       0x0003  //~1480KB     //@..\..\..\core\bin\melody\audio\aucode_adec_r2.bin -7
#endif

// Code: VD
#define BIN_ID_CODE_VD_DSP          0x0010  //~14KB     //@..\..\..\core\bin\melody\vd\vd_dsp.bin

// Code: DMX
#define BIN_ID_CODE_DEMUX           0x0011  //~18KB     //@..\..\..\core\bin\melody\demux\fwTSP.bin
#define BIN_ID_CODE_DEMUX_COMPRESS  0x0011  //~18KB     //@..\..\..\core\bin\melody\demux\fwTSP.bin

// Code: MHEG5
#define BIN_ID_CODE_MHEG5_A        0x0051 //~958KB   //@..\..\..\core\bin\melody\cape\mheg5_LE.bin
#define BIN_ID_CODE_MHEG5_B        0x0052 //~958KB   //@..\..\..\core\bin\melody\cape\mheg5_LE.bin
#define BIN_ID_CODE_MHEG5_C         0x0053

// Code: vdplayer
#define BIN_ID_CODE_AEON_VDPLAYER   0x0061 //~625KB    //@..\..\..\core\bin\melody\cape\vdplayer.bin -g
#define BIN_ID_CODE_AEON_VDPLAYER_32M   0x0062 //~662KB    //@..\..\..\core\bin\melody\cape\vdplayer_lite.bin -7

#define BIN_ID_CODE_AEON_H264_NO_COMPRESS    0x00B0  //~370KB    //@..\..\..\core\bin\melody\vdec\fwHVD.bin -7
#define BIN_ID_CODE_AEON_H264_COMPRESS       0x00B1  //~370KB    //@..\..\..\core\bin\melody\vdec\fwHVD.bin -7

//#define BIN_ID_CODE_AEON_CAPE       0x0070  //~1400KB   //@..\..\..\core\bin\melody\cape\cape.bin

#define BIN_ID_CODE_AEON_MVD         0x00AA  //~120KB    //@..\..\..\core\bin\melody\vdec\fwMVD.bin -7

#if(CHIP_SUPPORT_HEVC)//IMPLEMENT_DTV_H265
#define BIN_ID_CODE_AEON_H265       BIN_ID_MM_EVD
#endif


/******************************************************************************/
/*                       Font Binary definition                             */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Font ID Range: 0x0100 ~ 0x01FF                                           */
/*                                                                            */
/* Unique ID for each binary used to identify the binary entity in the packed */
/* binary. If changed, need to sync them to Bin_ID.h and PackList_X.txt       */
/*----------------------------------------------------------------------------*/

#define BIN_ID_FONT_MSTAR_MVF       0x01A0  //~271KB    //@..\..\..\tv-ap\dvb\ui2\font\MStar_Unicode5.mvf -7
#define BIN_ID_CODE_AEON_MVF        0x01A1  //~81KB    //@..\..\..\core\bin\melody\cape\aeon_mvf_LE.bin
#define BIN_ID_FONT_MSTAR_MVF_ATSC  0x01A2  //~264KB    //@..\..\..\tv-ap\atsc\ui2\font\MStar_Unicode4.mvf
#define BIN_ID_FONT_KOREA_20        0x0100  //~847KB    //@..\..\..\tv-ap\dvb\ui2\font\KOREA_20.bin
//#define BIN_ID_FONT_KOREA_35        0x0101  //~2006KB   //@..\..\..\tv-ap\atsc\ui2\font\KOREA_35.bin
#define BIN_ID_FONT_BIG5_CH         0x0105  //~410KB    //@..\..\..\tv-ap\dvb\ui2\font\Font_Big5_24x24.bin
#define BIN_ID_FONT_SIMP_CH_34X34         0x0101  //~2280KB   //@..\..\..\tv-ap\dvb\ui2\font\CH29034_34x34.bin -g
//#define BIN_ID_FONT_SIMP_CH_66X66         0x0105  //~2280KB   //@..\..\..\tv-ap\dvb\ui2\font\CH29034_66x66.bin -g
#define BIN_ID_FONT_SIMP_CH_24x24   0x0110  //~601KB    //@..\..\..\tv-ap\dvb\ui2\font\Simp_ch_24X24.bin -g
#define BIN_ID_FONT_SIMP_CH_18x18   0x0111  //~479KB    //@..\..\..\tv-ap\dvb\ui2\font\Simp_ch_18X18.bin -g

#define BIN_ID_FONT_ENGLISH_22        0x0102  //~847KB    //@..\..\..\tv-ap\atsc\ui2\font\osd\Font_16x22.bin -c
#define BIN_ID_FONT_ENGLISH_40       0x0103  //~2006KB   //@..\..\..\tv-ap\atsc\ui2\font\osd\Font_32x40.bin -c
#define BIN_ID_FONT_BL_ENG_50       0x011A  //~49KB   //@..\..\..\tv-ap\dvb\ui2\font\English_73_48x56_4color_real_19x54_LE.bin -7

//Font:TTF
#define BIN_ID_FONT_UI_TTF_TAMIL     0x11B   //~59KB     //@..\..\..\tv-ap\dvb\ui2\font\NotoSansTamil-Regular.ttf -g
#define BIN_ID_FONT_UI_TTF_MYMR     0x11C   //~113KB    //@..\..\..\tv-ap\dvb\ui2\font\NotoSansMyanmar-Regular.ttf -g
#define BIN_ID_FONT_UI_TTF_KHMER     0x11E  //~37KB    //@..\..\..\tv-ap\dvb\ui2\font\NotoSansKhmer-Regular.ttf -g
#define BIN_ID_FONT_UI_TTF_LAO     0x11F  //~34KB    //@..\..\..\tv-ap\dvb\ui2\font\NotoSansLao-Regular.ttf -g

//uyghur
#define BIN_ID_FONT_SIMP_CH_UYGH     0x11D  //~567KB     //@..\..\..\tv-ap\dvb\ui2\font\Simp_ch_18X18_gaochuang_changhong.bin

// Font: TT
#define BIN_ID_TTFONT_24_20         0x0201  //~59KB     //@..\..\..\core\bin\common\ttx_font\tt_font_24x20.bin -7
#define BIN_ID_TTFONT_34_30         0x0202  //~135KB     //@..\..\..\core\bin\common\ttx_font\tt_font_34x30.bin -7

// Font: Closed-caption testing patterns
#define BIN_ID_CC_TEST_PATTERN      0x0250  //~19KB    //@..\..\..\core\bin\common\cc_font\Filme_Up.trp.278.PES.dat

//SUPPORT_KOREAN_CC
#define BIN_ID_WANSUNGCODE_TABLE    0x0251  //~18KB    //@..\..\..\core\bin\common\cc_font\wansung2unicode.bin
#define BIN_ID_FONT_CS0_KOREAN      0x0280  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-0.bin
#define BIN_ID_FONT_CS1_KOREAN      0x0281  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-0.bin
#define BIN_ID_FONT_CS2_KOREAN      0x0282  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-0.bin
#define BIN_ID_FONT_CS3_KOREAN      0x0283  //~460KB   //@..\..\..\core\bin\common\cc_font\1366x768\CUS03_Font_CC_38x32_Korean.bin
#define BIN_ID_FONT_CS4_KOREAN      0x0284  //~332KB   //@..\..\..\core\bin\common\cc_font\1366x768\CUS03_Font_CC_32x33_Korean.bin
#define BIN_ID_FONT_CS5_KOREAN      0x0285  //~534KB   //@..\..\..\core\bin\common\cc_font\1366x768\CUS03_Font_CC_48x37_Korean.bin

#define BIN_ID_FONT_CS0_NK          0x0260  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-0.bin
#define BIN_ID_FONT_CS1_NK          0x0261  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-1.bin
#define BIN_ID_FONT_CS2_NK          0x0262  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-2.bin
#define BIN_ID_FONT_CS3_NK          0x0263  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-3.bin
#define BIN_ID_FONT_CS4_NK          0x0264  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-4.bin
#define BIN_ID_FONT_CS5_NK          0x0265  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-5.bin
#define BIN_ID_FONT_CS6             0x0266  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-6.bin
#define BIN_ID_FONT_CS7             0x0267  //~34KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_19x32-7.bin
#define BIN_ID_FONT_CS8             0x0268  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-0.bin
#define BIN_ID_FONT_CS9             0x0269  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-1.bin
#define BIN_ID_FONT_CS10            0x026A  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-2.bin
#define BIN_ID_FONT_CS11            0x026B  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-3.bin
#define BIN_ID_FONT_CS12            0x026C  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-4.bin
#define BIN_ID_FONT_CS13            0x026D  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-5.bin
#define BIN_ID_FONT_CS14            0x026E  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-6.bin
#define BIN_ID_FONT_CS15            0x026F  //~20KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_16x33-7.bin
#define BIN_ID_FONT_CS16            0x0270  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-0.bin
#define BIN_ID_FONT_CS17            0x0271  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-1.bin
#define BIN_ID_FONT_CS18            0x0272  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-2.bin
#define BIN_ID_FONT_CS19            0x0273  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-3.bin
#define BIN_ID_FONT_CS20            0x0274  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-4.bin
#define BIN_ID_FONT_CS21            0x0275  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-5.bin
#define BIN_ID_FONT_CS22            0x0276  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-6.bin
#define BIN_ID_FONT_CS23            0x0277  //~40KB    //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_24x37-7.bin


#define BIN_ID_FONT_CS0_KOREAN_FHD      0x0340  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-0.bin
#define BIN_ID_FONT_CS1_KOREAN_FHD      0x0341  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-0.bin
#define BIN_ID_FONT_CS2_KOREAN_FHD      0x0342  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-0.bin
#define BIN_ID_FONT_CS3_KOREAN_FHD      0x0343  //~460KB    //@..\..\..\core\bin\common\cc_font\1920x1080\CUS03_Font_CC_38x32_Korean.bin
#define BIN_ID_FONT_CS4_KOREAN_FHD      0x0344  //~332KB    //@..\..\..\core\bin\common\cc_font\1920x1080\CUS03_Font_CC_32x33_Korean.bin
#define BIN_ID_FONT_CS5_KOREAN_FHD      0x0345  //~534KB    //@..\..\..\core\bin\common\cc_font\1920x1080\CUS03_Font_CC_48x37_Korean.bin

#define BIN_ID_FONT_CS0_NK_FHD          0x0346 //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-0.bin
#define BIN_ID_FONT_CS1_NK_FHD          0x0347  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-1.bin
#define BIN_ID_FONT_CS2_NK_FHD          0x0348  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-2.bin
#define BIN_ID_FONT_CS3_NK_FHD          0x0349  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-3.bin
#define BIN_ID_FONT_CS4_NK_FHD          0x034A  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-4.bin
#define BIN_ID_FONT_CS5_NK_FHD          0x034B  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-5.bin
#define BIN_ID_FONT_CS6_FHD             0x034C  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-6.bin
#define BIN_ID_FONT_CS7_FHD             0x034D  //~34KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_19x32-7.bin
#define BIN_ID_FONT_CS8_FHD             0x034E  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-0.bin
#define BIN_ID_FONT_CS9_FHD             0x034F  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-1.bin
#define BIN_ID_FONT_CS10_FHD            0x0350  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-2.bin
#define BIN_ID_FONT_CS11_FHD            0x0351  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-3.bin
#define BIN_ID_FONT_CS12_FHD            0x0352  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-4.bin
#define BIN_ID_FONT_CS13_FHD            0x0353  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-5.bin
#define BIN_ID_FONT_CS14_FHD            0x0354  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-6.bin
#define BIN_ID_FONT_CS15_FHD            0x0355  //~20KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_16x33-7.bin
#define BIN_ID_FONT_CS16_FHD            0x0356  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-0.bin
#define BIN_ID_FONT_CS17_FHD            0x0357  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-1.bin
#define BIN_ID_FONT_CS18_FHD            0x0358  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-2.bin
#define BIN_ID_FONT_CS19_FHD            0x0359  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-3.bin
#define BIN_ID_FONT_CS20_FHD            0x035A  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-4.bin
#define BIN_ID_FONT_CS21_FHD            0x035B  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-5.bin
#define BIN_ID_FONT_CS22_FHD            0x035C  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-6.bin
#define BIN_ID_FONT_CS23_FHD            0x035D  //~40KB     //@..\..\..\core\bin\common\cc_font\1920x1080\Font_CC_24x37-7.bin

#if BRAZIL_CC
//for Brazil CC ,SWF 960*540
#define BIN_ID_FONT_DTVCC           0x0278  //~16KB     //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_18x18-0_brazil.bin -g
//for ATV CC
#define BIN_ID_FONT_ATVCC           0x0279  //~16KB     //@..\..\..\core\bin\common\cc_font\1366x768\Font_CC_18x18-0.bin -g
#endif

// JPEG: Logo
#define BIN_ID_JPEG_BOOT_LOGO_DVB       0x0300  //~50KB   //@..\..\..\tv-ap\dvb\ui2\logo\Portronics_logo.jpg

#define BIN_ID_MELODY_ON_DVB            0x0701  //~55KB   //@..\..\..\tv-ap\dvb\ui2\logo\mp3.mp3

// PANEL.BIN
#define BIN_ID_PANEL                    0x0747  //~2KB     //@..\..\..\core\bin\common\PanelBin\Panel.Bin

//===============================================================================================

// BMP for 1366x768x565
#define BIN_ID_OSDCP_BMP_1366x768x565           0x0301  //~533KB   //@..\..\..\tv-ap\dvb\ui2\res1366x768x565\osdcomposer\osdbin\ZUI_bitmap.bin -g
#define BIN_ID_OSDCP_BMP_1366x768x565_SW_LOAD   0x0302  //~533KB   //@..\..\..\tv-ap\dvb\ui2\res1366x768x565\osdcomposer\osdbin\ZUI_bitmap_SW_LOAD.bin
// BMP for 960x540x565
#define BIN_ID_OSDCP_BMP_960x540x565            0x0311  //~533KB   //@..\..\..\tv-ap\dvb\ui2\res960x540x565\osdcomposer\osdbin\ZUI_bitmap.bin -g
#define BIN_ID_OSDCP_BMP_960x540x565_SW_LOAD    0x0312  //~220KB   //@..\..\..\tv-ap\dvb\ui2\res960x540x565\osdcomposer\osdbin\ZUI_bitmap_SW_LOAD.bin
// BMP for 965x540xI8
#define BIN_ID_OSDCP_BMP_960x540xI8_SW_LOAD     0x0322  //~161KB   //@..\..\..\tv-ap\dvb\ui2\res960x540xI8\osdcomposer\osdbin\ZUI_bitmap_I8_SW_LOAD.bin

// BMP for 1920x1080x565
#define BIN_ID_OSDCP_BMP_1920x1080x565          0x0303  //~533KB   //@..\..\..\tv-ap\dvb\ui2\res1920x1080x565\osdcomposer\osdbin\ZUI_bitmap.bin -g
#define BIN_ID_OSDCP_BMP_1920x1080x565_SW_LOAD  0x0304  //~533KB   //@..\..\..\tv-ap\dvb\ui2\res1920x1080x565\osdcomposer\osdbin\ZUI_bitmap_SW_LOAD.bin

#define BIN_ID_OSDCP_PALETTE                    0x0320  //~2KB    //@..\..\..\tv-ap\dvb\ui2\res960x540xI8\osdcomposer\osdbin\ZUI_palette.bin


// String for 1366x768
#define BIN_ID_OSDCP_TEXT_1366x768x565          0x0380  //~285KB   //@..\..\..\tv-ap\dvb\ui2\res1366x768x565\osdcomposer\osdbin\ZUI_strings.bin  -g
#define BIN_ID_OSDCP_TEXT_960x540x565           0x0388  //~285KB   //@..\..\..\tv-ap\dvb\ui2\res960x540x565\osdcomposer\osdbin\ZUI_strings.bin  -7
#define BIN_ID_OSDCP_TEXT_960x540xI8            0x0390  //~285KB   //@..\..\..\tv-ap\dvb\ui2\res960x540xI8\osdcomposer\osdbin\ZUI_strings.bin  -g
#define BIN_ID_OSDCP_TEXT_1920x1080x565         0x0391  //~285KB   //@..\..\..\tv-ap\dvb\ui2\res1920x1080x565\osdcomposer\osdbin\ZUI_strings.bin  -g

#if ENABLE_KEY_TO_SPEECH
// Audio for KTS
#define BIN_ID_KTS_POWER_ON                     0x0400  //~16KB   //@..\..\..\tv-ap\common\KTS_resource\PowerOn.pcm
#define BIN_ID_KTS_POWER_OFF                    0x0401  //~31KB   //@..\..\..\tv-ap\common\KTS_resource\PowerOff.pcm
#define BIN_ID_KTS_CHANNEL_UP                   0x0402  //~31KB   //@..\..\..\tv-ap\common\KTS_resource\ChannelUp.pcm
#define BIN_ID_KTS_CHANNEL_DOWN                 0x0403  //~19KB   //@..\..\..\tv-ap\common\KTS_resource\ChannelDown.pcm
#define BIN_ID_KTS_VOLUME_UP                    0x0404  //~34KB   //@..\..\..\tv-ap\common\KTS_resource\VolumeUp.pcm
#define BIN_ID_KTS_VOLUME_DOWN                  0x0405  //~41KB   //@..\..\..\tv-ap\common\KTS_resource\VolumeDown.pcm
#define BIN_ID_KTS_MUTE_ON                      0x0406  //~30KB   //@..\..\..\tv-ap\common\KTS_resource\MuteOn.pcm
#define BIN_ID_KTS_MUTE_OFF                     0x0407  //~29KB   //@..\..\..\tv-ap\common\KTS_resource\MuteOff.pcm
#define BIN_ID_KTS_MENU                         0x0408  //~27KB   //@..\..\..\tv-ap\common\KTS_resource\Menu.pcm
#define BIN_ID_KTS_SOURCE                       0x0409  //~26KB   //@..\..\..\tv-ap\common\KTS_resource\Source.pcm
#endif
//=================================================================================================


// Demod DSP Code
#define BIN_ID_MSB1210              0x0837   //~23KB          //@..\..\..\core\bin\common\demodulator\demod_msb1210.bin
#define BIN_ID_INTERN_DVBT          0x0838  //~20KB     //@..\..\..\core\bin\maya\vd\demod_intern_dvbt.bin
#define BIN_ID_INTERN_DVBC          0x0839  //~9KB      //@..\..\..\core\bin\maya\vd\demod_intern_dvbc.bin
#define BIN_ID_INTERN_ATSC          0x083A  //~21KB     //@..\..\..\core\bin\maya\vd\demod_intern_atsc.bin


// MM FW code
#define BIN_ID_MM_HVD               0x0901   //~152KB          //@..\..\..\core\bin\melody\vdec\fwHVD.bin -g
#define BIN_ID_MM_HVD_VLC           0x0902   //~125KB          //@..\..\..\core\bin\melody\vdec\fwHVD_VLC.bin -g
#define BIN_ID_MM_MVD               0x0903   //~134KB          //@..\..\..\core\bin\melody\vdec\fwMVD.bin -g
#define BIN_ID_MM_RVD               0x0904   //~151KB          //@..\..\..\core\bin\melody\vdec\fwRVD.bin
#define BIN_ID_MM_RVD_VLC           0x0905   //~151KB          //@..\..\..\core\bin\melody\vdec\fwRVDvlcmem.bin
#define BIN_ID_MM_VPU               0x0906   //~400KB          //@..\..\..\core\bin\melody\vdec\fwVPU_MM.bin -7
#define BIN_ID_MM_VPU_VLC           0x0907   //~125KB          //@..\..\..\core\bin\melody\vdec\fwVPU_VLC_MM.bin -7
#define BIN_ID_MM_EVD               0x0908   //~152KB          //@..\..\..\core\bin\melody\vdec\fwEVD.bin -g

// PQ BIN
#define BIN_ID_PQ_MAIN              0x0909   //~400KB        //@..\..\..\core\driver\pq\hal\melody\include\melody_Main.bin
#define BIN_ID_PQ_MAIN_TEXT         0x090A   //~22KB         //@..\..\..\core\driver\pq\hal\melody\include\melody_Main_Text.bin
#define BIN_ID_PQ_MAIN_EX           0x090B   //~20KB         //@..\..\..\core\driver\pq\hal\melody\include\melody_Main_Ex.bin
#define BIN_ID_PQ_MAIN_EX_TEXT      0x090C   //~4KB          //@..\..\..\core\driver\pq\hal\melody\include\melody_Main_Ex_Text.bin

// TCon bin
#define BIN_ID_TCON_WXGA_IPS32_Panasonic_For_CUS144  0x0A00   //~11KB          //@..\..\..\core\bin\maya\panel\TCON_WXGA_IPS32_Panasonic_For_Cus144.bin

// Free Font Notice
#define BIN_ID_FREE_FONT_NOTICE     0xD000  //~5KB     //@..\..\..\core\bin\common\cc_font\FreeFontNotice.txt

// ISP update flag
#define BIN_ID_ISP_UPDATE_FLAG      0xE000

//=====================================================================
// Please don't modify this BIN ID 0xEFFF.
// It will be verified by Bin Manager Tool for customer key check.
#if (SUPPORT_BIN_MANAGER) //
#define BIN_ID_BINMANAGER_KEY       0xEFFF  //~1KB      //@..\..\..\project\image\BinManagerCustomerKey.bin
#endif

// Magic number
#define BIN_ID_MAGIC_55AAABCD       0xF000  //~1KB  //@..\..\..\project\image\MagicNum55AAABCD.bin

#define BIN_PACKAGE_HEADER_ID0  0x54454C09
#define BIN_PACKAGE_HEADER_ID1  0x58336900
#define BIN_DISPLAY_HEADER_ID0  0x54454C09
#define BIN_DISPLAY_HEADER_ID1  0x31207341
#define BIN_DRAMMAP_HEADER_ID0  0x4D5354FA
#define BIN_DRAMMAP_HEADER_ID1  0x50417461
#define BIN_IRMAP_HEADER_ID     0x77554321
#define BIN_KEYPAD_HEADER_ID    0x4368656E

#define BIN_PACKAGE_HEADER_SIZE 0x0C
#define BIN_PACKAGE_NUMBER_SIZE 0x02
#define BIN_PACKAGE_BINFO_SIZE  0x0B

#define BIN_PACKAGE_HEADER_ADDR 0x00
#define BIN_PACKAGE_NUMBER_ADDR (BIN_PACKAGE_HEADER_ADDR+BIN_PACKAGE_HEADER_SIZE)
#define BIN_PACKAGE_BINFO_ADDR  (BIN_PACKAGE_NUMBER_ADDR+BIN_PACKAGE_NUMBER_SIZE)


//--------------------------------------------
// Reserved for Customer: Range 0xC000-0xCFFF
//--------------------------------------------
//#define BIN_ID_CUSTOMER_RESERVED_1    0xC000
//...
//#define BIN_ID_CUSTOMER_RESERVED_X    0xCFFF
typedef struct _BIN_INFO_
{
    U16 B_ID;                 //!< Unique ID
    U32 B_FAddr;              //!< Start address
    U32 B_Len;                //!< Length in bytes
    U8  B_IsComp;             //!< Is bin compressed
} BININFO;

#endif  //_BIN_INFO_H_

