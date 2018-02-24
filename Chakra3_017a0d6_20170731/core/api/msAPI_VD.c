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
////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_VD.h
/// MStar Application Interface for Video decoder
/// @brief API for Video Decoder
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
//
#define _MSAPI_VD_C_

#include "Board.h"

#include "MsCommon.h"
#include "debug.h"
#include "sysinfo.h"
//#include "BinInfo.h"
#include "SysInit.h"
#include "Utl.h"
#include "GPIO.h"

#include "drvAVD.h"

#include "apiXC.h"
#include "apiXC_Dlc.h"
#include "apiXC_Sys.h"

#include "drvPQ.h"
#include "drvPQ_Define.h"

#include "msAPI_BDMA.h"
#include "msAPI_Global.h"
#include "msAPI_Tuning.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"
#include "msAPI_audio.h"
#include "msAPI_VD.h"
#include "IF_Demodulator.h"

#if ((BRAZIL_CC )|| (ATSC_CC == ATV_CC))
#include "mapi_cc_monitor.h"
#endif

#if (ENABLE_TTX)
#include "msAPI_TTX.h"
#endif

#if (ENABLE_VD_PACH_IN_CHINA||ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM   || (TV_SYSTEM == TV_NTSC) )
#include "MApp_GlobalSettingSt.h"
#endif

#if( CHAKRA3_AUTO_TEST )
#include "MApp_AutoTest.h"
#endif

#include "MApp_GlobalFunction.h"


#define DEBUG_AVD(x)    //x


//****************************************************************************
// Private attributes of this file.
//****************************************************************************
#define AFEC_REG_BASE                           0x3500  // 0x3500 - 0x35FF
#define COMB_REG_BASE                           0x3600  // 0x3600 - 0x36FF
#define BK_AFEC_02  (AFEC_REG_BASE+0x02)
#define BK_AFEC_03  (AFEC_REG_BASE+0x03)
#define BK_AFEC_04  (AFEC_REG_BASE+0x04)
#define BK_AFEC_D0  (AFEC_REG_BASE+0xD0)
#define BK_AFEC_D2  (AFEC_REG_BASE+0xD2)
#define BK_AFEC_D4  (AFEC_REG_BASE+0xD4)
#define BK_AFEC_D5  (AFEC_REG_BASE+0xD5)
#define BK_AFEC_DB  (AFEC_REG_BASE+0xDB)
#define BK_AFEC_C4  (AFEC_REG_BASE+0xC4)
#define BK_COMB_22  (COMB_REG_BASE+0x22)
#define BK_COMB_37  (COMB_REG_BASE+0x37)
#define BK_COMB_38  (COMB_REG_BASE+0x38)
#define BK_COMB_45  (COMB_REG_BASE+0x45)
#define BK_COMB_7C  (COMB_REG_BASE+0x7C)
#define BK_COMB_ED  (COMB_REG_BASE+0xED)

/******************************************************************************************/
// b3 b2 b1 b0    AspectRatio        Format            Position        Active Lives
/********************************************************************************/
//  1  0  0  0        4:3            Full format           -                576
//  0  0  0  1        14:9        Letterbox        Center                504
//  0  0  1  0        14:9        Letterbox        Top                    504
//  1  0  1  1        16:9        Letterbox        Center                430
//  0  1  0  0        16:9        Letterbox        Top                    430
//  1  1  0  1        >16:9        Letterbox        Center                 -
//  1  1  1  0        14:9        Full format        Center                576
//  0  1  1  1        16:9        Full format           -                576
/******************************************************************************************/
#define WSS_4x3_FULL                    0x08
#define WSS_14x9_LETTERBOX_CENTER        0x01
#define WSS_14x9_LETTERBOX_TOP            0x02
#define WSS_16x9_LETTERBOX_CENTER        0x0B
#define WSS_16x9_LETTERBOX_TOP            0x04
#define WSS_ABOVE16x9_LETTERBOX_CENTER    0x0D
#define WSS_14x9_FULL_CENTER            0x0E
#define WSS_16x9_ANAMORPHIC                0x07

#define WSS_MASK        0x0F

const MS_WINDOW_TYPE VideoCaptureWinTbl [] =
{
    {MSVD_HSTART_NTSC,      MSVD_VSTART_NTSC,       MSVD_HACTIVE_NTSC,      480}, // NSTC
    {MSVD_HSTART_PAL,       MSVD_VSTART_PAL,        MSVD_HACTIVE_PAL,       576}, // PAL
    {MSVD_HSTART_SECAM,     MSVD_VSTART_SECAM,      MSVD_HACTIVE_SECAM,     576}, // SECAM
    {MSVD_HSTART_NTSC_443,  MSVD_VSTART_NTSC_443,   MSVD_HACTIVE_NTSC_443,  480}, // NTSC-443/PAL-60
    {MSVD_HSTART_PAL_M,     MSVD_VSTART_PAL_M,      MSVD_HACTIVE_PAL_M,     480}, // PAL-M
    {MSVD_HSTART_PAL_NC,    MSVD_VSTART_PAL_NC,     MSVD_HACTIVE_PAL_NC,    576}, // PAL-Nc
};

const MS_WINDOW_TYPE ExtVDVideoCapture[] =
{
    {0x00, 0x00, 720, 480}, // NSTC
    {0x00, 0x00, 720, 576}, // PAL
    {0x00, 0x00, 720, 576}, // SECAM
    {0x00, 0x00, 720, 480}, // NTSC-443/PAL-60
    {0x00, 0x00, 720, 480}, // PAL-M
    {0x00, 0x00, 720, 576}, // PAL-Nc
};

typedef enum
{
    //E_DETECTION_VERIFY,
    E_DETECTION_START,
    E_VD_STATE__UNSTABLE, //E_DETECTION_WAIT,
    E_VD_STATE__STABLE, //E_DETECTION_DETECT
} STANDARD_DETECTION_STATE;

static AVD_VideoStandardType       m_eVideoStandard;
static AVD_VideoStandardType       m_eCurrentVideoStandard;

static AVD_InputSourceType         m_eVideoSource;
static AVD_VideoStandardType m_eFSMDetectedStandard;
static WORD m_wVideoDownCountTimer;
static WORD m_wVideoUpCountTimer;
static BOOLEAN m_bForceVideoStandardFlag = FALSE;

static U16 m_cPreviousScart1IDLevelForAutoAV;
static U16 m_cPreviousScart2IDLevelForAutoAV;

static STANDARD_DETECTION_STATE m_eStandardDetectionState;
static MS_U16 m_u16LatchStatus;

static SCART_SOURCE_TYPE       VDScart1SrcType;
static ASPECT_RATIO_TYPE      m_eAspectRatioCode;

static BOOLEANS m_BOOLEANS_1;
#define m_bIsVideoFormatChanged             m_BOOLEANS_1.bBOOL_0
#define m_bIsVideoInputChanged              m_BOOLEANS_1.bBOOL_1
#define m_bIsAspectRatioChanged             m_BOOLEANS_1.bBOOL_2
#define m_bIsSyncChanged                    m_BOOLEANS_1.bBOOL_3
#define m_bIs3DCombfilterUsed               m_BOOLEANS_1.bBOOL_4
#define m_bIsAGCEnabled                     m_BOOLEANS_1.bBOOL_5
#define m_bIsScart1SourceTypeChanged        m_BOOLEANS_1.bBOOL_6


static BOOLEANS m_BOOLEANS_2;
#define m_bPermanentVideoMute               m_BOOLEANS_2.bBOOL_0
#define m_bMomentVideoMute                  m_BOOLEANS_2.bBOOL_1
#define m_bByLockVideoMute                  m_BOOLEANS_2.bBOOL_2
#define m_bByParentalVideoMute              m_BOOLEANS_2.bBOOL_3
#define m_bByDuringLimitedTimeVideoMute     m_BOOLEANS_2.bBOOL_4
#define m_bIsAutoAV1Active                  m_BOOLEANS_2.bBOOL_5
#define m_bIsAutoAV2Active                  m_BOOLEANS_2.bBOOL_6
#define FORCEDFREEFUN FALSE

//   BK_AFEC_DC
#define MSK_UD7_BANK                            0x03
#define VAL_UD7_BANK6                           0x00
#define VAL_UD7_BANK7                           0x01
#define MSK_UD7_STATE                           0x0C
#define VAL_UD7_FREE                            0x00
#define VAL_UD7_READ                            0x04
#define VAL_UD7_WRITE                           0x08
#define VAL_UD7_READ_END                        0x0C
#define IS_BITS_MATCHED(val, bits)              (((val)&(bits)) == (bits))
#define ENABLE_NTSC_50                          0
//#define LOCK3DSPEEDUP                           1 // Designer Robert.Chen for Channel Change, COMB_57=0x50,COMB_58=0x20
#define PATCH_COMB_ZONEPLATE                    0
#define NEW_COMB_STILLIMAGE                     0
#define FINE_TUNE_FH_DOT                        1       // fine-tune for Fh image quality, Eris-ATT, James.Lu, 20080328
#define FINE_TUNE_FSC_SHIFT                     0       // fine-tune for Fsc shift cause color bar edge blur, James.Lu, 20080919
#define PATCH_COMB_STILLIMAGE                   1
#define FINE_TUNE_COMB_F2                       1       // fine-tune for bug's life, for Eris-ATT, James.Lu, 20080327
#define FINE_TUNE_3D_COMB                       1       // fine-tune 3D Comb, for Eris-ATT, James.Lu, 20080328
#define COLOR_KILL_HIGH_BOUND                   0x30 // 0x0E //0x89 // adjust this value for color on when RF signal is weak
#define COLOR_KILL_LOW_BOUND                    0x30 // 0x0E //0x15 // adjust this value for color kill level

static MS_U8 u8StdDetStableCnt = 0;
static MS_U8  _u8PreNoiseMag;
static MS_U16 _u16DataH[3];
static MS_U8  _u8HtotalDebounce;
static MS_U8 _u8AutoTuningIsProgress = 0x00; //YES:0x01
static AVD_VideoSystem _eVideoSystem=E_VIDEO_SYSTEM_DVB;

static BOOLEAN bVD_FWStatus = FALSE;    /* TRUE: Nand Flash; FALSE: SPI Flash; */

#if(ENABLE_SW_CH_FREEZE_SCREEN)
BOOLEAN bVideoStandardChanged = FALSE;
#endif
U32 g_VD_u32ForceVideoStd_CountDownTime = 0;

//****************************************************************************
// Private functions of this file.
//****************************************************************************

static void msAPI_AVD_CheckVideoStandard(void);
//static void msAPI_AVD_CheckVideoSourceSwitch(void);
// static void msAPI_AVD_CheckVerticalTotal(void); // <-<<< UNUSED
static void msAPI_AVD_CheckAspectRatio(void);
#if(INPUT_SCART_VIDEO_COUNT>0)
static void msAPI_AVD_CheckAutoAV(void);
#endif
//static void msAPI_AVD_TurnOnAutoAV(void);

#if( !ENABLE_SCART_MONITOR )
static void msAPI_AVD_RetrieveScart1SourceType(void);
#endif

#if ENABLE_ATSC
/******************************************************************************/
///-Get Video Decoder status
///@return
///Status represented bits from VD
///- VD_PAL_SWITCH: BIT9
///- VD_COLOR_LOCKED: BIT10
///- VD_RESET_ON: BIT11
///- VD_VSYNC_50HZ: BIT12
///- VD_INTERLACED: BIT13
///- VD_HSYNC_LOCKED: BIT14
///- VD_SYNC_LOCKED: BIT15
///- VD_MACROVISION: BIT2
///- VD_VCR_MODE: BIT4
///- VD_FSC_3579: BIT6
///- VD_FSC_3575: BIT7
///- VD_FSC_3582: (BIT6|BIT7)
///- VD_FSC_4433: 0
///- VD_FSC_4285: BIT5
/******************************************************************************/
U16 msAPI_AVD_GetStatus ( void )
{
    return MDrv_AVD_GetStatus();
}

/******************************************************************************/
/// -Initial the VD's parameter
/******************************************************************************/
void msAPI_AVD_Parameter_Initial(void)
{
    #if 0
    MDrv_VD_Parameter_Initial();
    #endif
}
#endif


BOOLEAN msAPI_AVD_CheckLockAudioCarrier(void)
{
    U16 u16tmp,u16tmp1=0;
    U8 u8tmp;
    U16 u16outedge,u16outedgesum=0;
    U16 u16noise,u16noisesum=0;
    // in of window H sync edge
    u16tmp1 = MDrv_AVD_GetHsyncEdge() & 0x3F ;
    if(u16tmp1 == 0)
        u16tmp1 = 1 ;// to protect u16tmp1 not equal 0
    // Output of window H sync edge
    MDrv_AVD_SetRegValue(BK_AFEC_04, 0x0B);
    u16outedgesum = MDrv_AVD_GetRegValue(BK_AFEC_03);
    if(u16outedgesum == 0)
        u16outedgesum = 1 ;// to protect u16outedgesum not equal 0
    // noise mag
    MDrv_AVD_SetRegValue(BK_AFEC_04, 0x04);
    u16noisesum = MDrv_AVD_GetRegValue(BK_AFEC_02);
    if(u16noisesum == 0)
        u16noisesum = 1 ;// to protect u16noisesum not equal 0

    for(u8tmp=0;u8tmp<10;u8tmp++)
    {
        // in of window H sync edge
        u16tmp = MDrv_AVD_GetHsyncEdge() & 0x3F;
        u16tmp1 = ((9*u16tmp1) + (1*u16tmp))/10 ;
        // Output of window H sync edge
        MDrv_AVD_SetRegValue(BK_AFEC_04, 0x0B);
        u16outedge = MDrv_AVD_GetRegValue(BK_AFEC_03);
        u16outedgesum = ((9*u16outedgesum) + (1*u16outedge))/10 ;
        // noise mag
        MDrv_AVD_SetRegValue(BK_AFEC_04, 0x04);
        u16noise = MDrv_AVD_GetRegValue(BK_AFEC_02);
        u16noisesum = ((9*u16noisesum) + (1*u16noise))/10 ;
        msAPI_Timer_Delayms(1);
    }

//    printf("\r\n final in of window H edge = %x",u16tmp1);
//    printf("\r\n final out of window H edge = %x",u16outedgesum);
//    printf("\r\n final noise mag = %x",u16noisesum);

    if((u16tmp1>=0x35)||((u16outedgesum >3)&&(u16noise > 0x50)))
        return TRUE;
    else
        return FALSE;
}

BOOLEAN msAPI_AVD_CheckFalseChannel(void)
{
    U16 u16tmp,u16tmp1=0;
    U8 u8tmp;

    for(u8tmp=0;u8tmp<10;u8tmp++)
    {
        u16tmp = (MDrv_AVD_GetRegValue(BK_AFEC_C4) & 0xFF);
        if(u16tmp>u16tmp1)
            u16tmp1=u16tmp;
        if(u16tmp1 ==0x3C)
        {
            //printf("\r\n REG_35C4-1 %x",u16tmp1);
            return TRUE;
        }
        msAPI_Timer_Delayms(1);
    }
    //printf("\r\n REG_35C4-1 %x",u16tmp1);

    return FALSE;

}

#if ENABLE_TTX
//****************************************************************************
/// Get the WSS value from VBI line#16
/// @param bServiceType \b IN: Service type
/// @param None \b IN:
/// @return ASPECT_RATIO_TYPE : the WSS aspect ratio value
/// -@see ASPECT_RATIO_TYPE
//****************************************************************************
ASPECT_RATIO_TYPE msAPI_AVD_GetAspectRatioCodeOfWSS(void)
{
    ASPECT_RATIO_TYPE eAspectRatioCode;
    WORD wWSSData;

    if(msAPI_TTX_GetWssStatus()==FALSE)
        return ARC_INVALID;

    wWSSData = msAPI_TTX_ReadWssWord();

    wWSSData = wWSSData & WSS_MASK;
    switch(wWSSData)
    {
        case WSS_4x3_FULL:
            eAspectRatioCode = ARC4x3_FULL;
            break;
        case WSS_14x9_LETTERBOX_CENTER:
            eAspectRatioCode = ARC14x9_LETTERBOX_CENTER;
            break;
        case WSS_14x9_LETTERBOX_TOP:
            eAspectRatioCode = ARC14x9_LETTERBOX_TOP;
            break;
        case WSS_16x9_LETTERBOX_CENTER:
            eAspectRatioCode = ARC16x9_LETTERBOX_CENTER;
            break;
        case WSS_16x9_LETTERBOX_TOP:
            eAspectRatioCode = ARC16x9_LETTERBOX_TOP;
            break;
        case WSS_ABOVE16x9_LETTERBOX_CENTER:
            eAspectRatioCode = ARC_ABOVE16x9_LETTERBOX_CENTER;
            break;
        case WSS_14x9_FULL_CENTER:
            eAspectRatioCode = ARC14x9_FULL_CENTER;
            break;
        case WSS_16x9_ANAMORPHIC:
            eAspectRatioCode = ARC16x9_ANAMORPHIC;
            break;
        default:
            eAspectRatioCode = ARC_INVALID;
            break;
    }

    return eAspectRatioCode;
}
#endif

AVD_VideoStandardType msAPI_AVD_GetStandardDetection(void)
{
    MS_U16 u16Status;
    return MDrv_AVD_GetStandardDetection(&u16Status);
}

static void msAPI_AVD_InitFactoryMode(void)
{
#if ENABLE_VD_PACH_IN_CHINA
    MDrv_WriteByte(BK_AFEC_D4_ADDRESS,G_FACTORY_SETTING.stVDSetting.u8AFEC_D4);
    MDrv_AVD_SetAFECD4Factory(G_FACTORY_SETTING.stVDSetting.u8AFEC_D4);
    MDrv_WriteByte(BK_AFEC_A0_ADDRESS, G_FACTORY_SETTING.stVDSetting.u8AFEC_A0);
    MDrv_WriteByte(BK_AFEC_A1_ADDRESS, G_FACTORY_SETTING.stVDSetting.u8AFEC_A1);
    MDrv_WriteByteMask(BK_AFEC_66_ADDRESS, (G_FACTORY_SETTING.stVDSetting.u8AFEC_66_Bit76<<6), (BIT7|BIT6));
    MDrv_WriteByteMask(BK_AFEC_6E_ADDRESS, (G_FACTORY_SETTING.stVDSetting.u8AFEC_6E_Bit7654<<4),0xF0);
    MDrv_WriteByteMask(BK_AFEC_6E_ADDRESS, G_FACTORY_SETTING.stVDSetting.u8AFEC_6E_Bit3210,0x0F);
#endif
}

/******************************************************************************/
///- API to initialize video decoder
/******************************************************************************/
void msAPI_AVD_InitVideoSystem(void)
{
    static const MS_REG_INIT _u8VdDecInitializeExt[] =
    {
        //initial AFEC Setting
       // _RV1(BK_AFEC_D4, 0x00),  // TODO update correct value
        _RV1(BK_AFEC_D5, 0x60),
        //_RV1(BK_AFEC_D8, 0x88),
        //_RV1(BK_AFEC_D9, 0x19),
        _END_OF_TBL2_,
    };
    VD_INITDATA sVD_InitData;

    /* Before MDrv_VD_Init(), you should tell VD where F/W is. */
#ifdef ATSC_SYSTEM
    _eVideoSystem=E_VIDEO_SYSTEM_ATSC;
#else
    _eVideoSystem=E_VIDEO_SYSTEM_DVB;
#endif
    // BY 20090409 MDrv_VD_SetFWStaus(bVD_FWStatus, MDrv_Sys_GetBinAddr());

    // Init VD
    // VIF
    sVD_InitData.u32XTAL_Clock = MST_XTAL_CLOCK_HZ; // TODO replace with system define
    #if ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
    sVD_InitData.eDemodType = DEMODE_MSTAR_VIF;
    #elif (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
    sVD_InitData.eDemodType = DEMODE_MSTAR_VIF_MSB1210;
    #else
    sVD_InitData.eDemodType = DEMODE_NORMAL;
    #endif

    sVD_InitData.eLoadCodeType=AVD_LOAD_CODE_BYTE_WRITE;
    sVD_InitData.u32VD_DSP_Code_Address=0;
    sVD_InitData.pu8VD_DSP_Code_Address=0;
    sVD_InitData.u32VD_DSP_Code_Len=0; // use driver internal dsp code instead of flash bin version
    sVD_InitData.u16VDDSPBinID = 0xFFFF;

    sVD_InitData.bAVGainSel = VD_GAIN_OF_AV_SEL;
    sVD_InitData.u8AVGain = VD_GAIN_OF_AV;
    sVD_InitData.u32VDPatchFlag = MSVD_HTOTAL_TYPE|AVD_PATCH_FINE_TUNE_FH_DOT|AVD_PATCH_FINE_TUNE_COMB_F2|AVD_PATCH_FINE_TUNE_3D_COMB|AVD_PATCH_FINE_TUNE_STILL_IMAGE;
#if ENABLE_VD_PACH_IN_CHINA
    if(G_FACTORY_SETTING.stVDSetting.u8AFEC_43==0x74)//Fixed gain
    {
        sVD_InitData.bRFGainSel = VD_USE_FIX_GAIN;
        sVD_InitData.u8RFGain = G_FACTORY_SETTING.stVDSetting.u8AFEC_44;
    }
    else
    {
        sVD_InitData.bRFGainSel = VD_GAIN_OF_RF_SEL;
        sVD_InitData.u8RFGain = VD_GAIN_OF_RF;
    }
    sVD_InitData.u8ColorKillHighBound = G_FACTORY_SETTING.stVDSetting.u8AFEC_D7_HIGH_BOUND;
    sVD_InitData.u8ColorKillLowBound = G_FACTORY_SETTING.stVDSetting.u8AFEC_D7_LOW_BOUND;

#else
    sVD_InitData.bRFGainSel = VD_GAIN_OF_RF_SEL;
    sVD_InitData.u8RFGain = VD_GAIN_OF_RF;
    sVD_InitData.u8ColorKillHighBound = VD_COLOR_KILL_HIGH_BOUND;
    sVD_InitData.u8ColorKillLowBound = VD_COLOR_KILL_LOW_BOUND;
#endif

#if (!ENABLE_PWS)
    sVD_InitData.u32VDPatchFlag|= AVD_PATCH_DISABLE_PWS;
#endif

    sVD_InitData.u8SwingThreshold = VD_SIG_SWING_THRESH;
    sVD_InitData.eVDHsyncSensitivityNormal.u8DetectWinBeforeLock= VD_HSEN_NORMAL_DETECT_WIN_BEFORE_LOCK;
    sVD_InitData.eVDHsyncSensitivityNormal.u8DetectWinAfterLock= VD_HSEN_NOAMRL_DETECT_WIN_AFTER_LOCK;
    sVD_InitData.eVDHsyncSensitivityNormal.u8CNTRFailBeforeLock= VD_HSEN_NORMAL_CNTR_FAIL_BEFORE_LOCK;
    sVD_InitData.eVDHsyncSensitivityNormal.u8CNTRSyncBeforeLock= VD_HSEN_NORMAL_CNTR_SYNC_BEFORE_LOCK;
    sVD_InitData.eVDHsyncSensitivityNormal.u8CNTRSyncAfterLock= VD_HSEN_NORMAL_CNTR_SYNC_AFTER_LOCK;
    sVD_InitData.eVDHsyncSensitivityTuning.u8DetectWinBeforeLock= VD_HSEN_CHAN_SCAN_DETECT_WIN_BEFORE_LOCK;
    sVD_InitData.eVDHsyncSensitivityTuning.u8DetectWinAfterLock= VD_HSEN_CHAN_SCAN_DETECT_WIN_AFTER_LOCK;
    sVD_InitData.eVDHsyncSensitivityTuning.u8CNTRFailBeforeLock= VD_HSEN_CHAN_SCAN_CNTR_FAIL_BEFORE_LOCK;
    sVD_InitData.eVDHsyncSensitivityTuning.u8CNTRSyncBeforeLock= VD_HSEN_CHAN_SCAN_CNTR_SYNC_BEFORE_LOCK;
    sVD_InitData.eVDHsyncSensitivityTuning.u8CNTRSyncAfterLock= VD_HSEN_CHAN_SCAN_CNTR_SYNC_AFTER_LOCK;
    sVD_InitData.u8VdDecInitializeExt=(U8 *)_u8VdDecInitializeExt;

    // comb
    sVD_InitData.u32COMB_3D_ADR = ((COMB_3D_BUF_MEMORY_TYPE & MIU1) ? (COMB_3D_BUF_ADR | MIU_INTERVAL) : (COMB_3D_BUF_ADR));
    sVD_InitData.u32COMB_3D_LEN = COMB_3D_BUF_LEN;

    if (E_AVD_FAIL==MDrv_AVD_Init(&sVD_InitData, sizeof(sVD_InitData)))
    {
        MS_DEBUG_MSG(printf("## %s Fail##\r\n",__FUNCTION__));
    }

    msAPI_AVD_InitFactoryMode();

    m_eVideoStandard = E_VIDEOSTANDARD_NOTSTANDARD;
    m_eCurrentVideoStandard = E_VIDEOSTANDARD_NOTSTANDARD;
    m_eVideoSource = E_INPUT_SOURCE_INVALID;

    m_wVideoDownCountTimer = 0;
    m_wVideoUpCountTimer = 0;

    m_bIsVideoFormatChanged = FALSE;
    m_bIsVideoInputChanged = FALSE;
    m_bIsSyncChanged = FALSE;
    m_bIs3DCombfilterUsed = FALSE;

    m_bPermanentVideoMute = FALSE;
    m_bMomentVideoMute = FALSE;
    m_bByLockVideoMute = FALSE;
    m_bByParentalVideoMute = FALSE;
    m_bByDuringLimitedTimeVideoMute = FALSE;

    m_bIsAutoAV1Active = FALSE;
    m_bIsAutoAV2Active = FALSE;

    m_cPreviousScart1IDLevelForAutoAV = SCART_ID_LEVEL_0V;
    m_cPreviousScart2IDLevelForAutoAV = SCART_ID_LEVEL_0V;

    m_eStandardDetectionState = E_DETECTION_START;

    m_bIsAGCEnabled = TRUE;

    // Scart src type...
    m_bIsScart1SourceTypeChanged = FALSE;
    VDScart1SrcType = E_SCART_SRC_TYPE_UNKNOWN;

    // Aspect Ratio...
    m_bIsAspectRatioChanged = FALSE;
    m_eAspectRatioCode = ARC_INVALID;

    _u16DataH[0] = _u16DataH[1] = _u16DataH[2] = VD_HT_PAL;
    _u8PreNoiseMag=0;
    _u8HtotalDebounce = 0;

    MDrv_AVD_SetFreerunFreq(E_FREERUN_FQ_AUTO);

    //To get the VD_Lib Version Number
    {
        //BY U8 u8Verinfo[32];
        //BY MDrv_VD_GetVDVerString(&u8Verinfo[0]);
     //   printf("VD Lib Build Version ---> %c-%c-%c-%c\n",u8Verinfo[10],u8Verinfo[11]
     //       ,u8Verinfo[12],u8Verinfo[13]);
     //   printf("VD Lib Interface Version ---> %c-%c \n",u8Verinfo[8],u8Verinfo[9]);

    }

}

void msAPI_AVD_Exit(void)
{
    MDrv_AVD_Exit();
}

void msAPI_AVD_ZonePlatePatch(void)
{
    U8 u8Value, u8Motion ;
    static U8 u8PrevLuma = 128;

    #define LUMA_TH1 0x68
    #define LUMA_TH2 0xAA

    u8Value = MApi_XC_DLC_GetAverageValue();

    //printf("MDrv_DLC_GetAverageValue = 0x%x\n",MDrv_DLC_GetAverageValue()) ;
    u8Value=(WORD)((WORD)u8PrevLuma*3+((WORD)u8Value*1))>>2;
    u8PrevLuma = u8Value;

    u8Motion = MDrv_PQ_GetCurrentMotionValue();

    if(IsATVInUse()||IsAVInUse())
    {
        if(u8Motion < 0x0A )
        {
           MDrv_AVD_SetRegValue(BK_COMB_45, (MDrv_AVD_GetRegValue(BK_COMB_45)&(~BIT7)));

           if(u8Value < LUMA_TH1)
           {
                //printf("AAA\n");
                MDrv_AVD_SetRegValue(BK_COMB_22, (MDrv_AVD_GetRegValue(BK_COMB_22)&(~(BIT1|BIT0)))|(BIT1|BIT0));
           }
           else if ((u8Value >= LUMA_TH1)&&(u8Value < LUMA_TH2))
           {
                //printf("CCC\n");
                MDrv_AVD_SetRegValue(BK_COMB_22, (MDrv_AVD_GetRegValue(BK_COMB_22)&(~(BIT1|BIT0)))|(BIT0));
           }
           else
           {
                //printf("DDD\n");
                MDrv_AVD_SetRegValue(BK_COMB_22, (MDrv_AVD_GetRegValue(BK_COMB_22)&(~(BIT1|BIT0))));
           }
        }
        else
        {
           MDrv_AVD_SetRegValue(BK_COMB_45, (MDrv_AVD_GetRegValue(BK_COMB_45)&(~BIT7))|(BIT7));
           MDrv_AVD_SetRegValue(BK_COMB_22, (MDrv_AVD_GetRegValue(BK_COMB_22)&(~(BIT1|BIT0)))|(BIT1|BIT0));
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: msAPI_AVD_SetRegFromDSP()
/// @brief \b Function \b Description: To set AFEC/COMB registers through VD DSP's register.
/// @param <IN>        \b None     :
///
///
/// @param <OUT>       \b None     :
/// @param <RET>       \b None     :
/// @param <GLOBAL>    \b None     :
////////////////////////////////////////////////////////////////////////////////
void msAPI_AVD_SetPatchOption(void)
{//must set patch option before init.
    MS_U32 ePatchFlag=AVD_PATCH_NONE;

#if ENABLE_NTSC_50
    ePatchFlag|=AVD_PATCH_NTSC_50;
#endif
    MDrv_AVD_SetFlag(ePatchFlag);
}

void msAPI_AVD_SetRegFromDSP(void)
{

    U8  u8Ctl;

#if NEW_COMB_STILLIMAGE
    U16 u16Value;
    static U8 check_counter = 0;
    static U8 Total_Nosiemag = 0;
    static U8 status = 2;
    static U16 _u16PreNoiseMag = 0;
#else
    U8 u8Value;
#endif

#if 0 // for DPL debug
    if (MDrv_AVD_GetRegValue(BK_AFEC_DB) & 0x01)
    {
        #define TOTAL_LINE 525*30
        MS_S16 dpl[TOTAL_LINE];
        U16 count,linenumber[TOTAL_LINE],temp[4],prevline=-1;

        for ( count=0 ; count <TOTAL_LINE ; )
        {
          temp[0]=(MDrv_AVD_GetRegValue(BK_AFEC_D0+1)<<8)+MDrv_AVD_GetRegValue(BK_AFEC_D0);
          temp[1]=(MDrv_AVD_GetRegValue(BK_AFEC_D0+1)<<8)+MDrv_AVD_GetRegValue(BK_AFEC_D0);
          temp[2]=(MDrv_AVD_GetRegValue(BK_AFEC_D2+1)<<8)+MDrv_AVD_GetRegValue(BK_AFEC_D2);
          temp[3]=(MDrv_AVD_GetRegValue(BK_AFEC_D2+1)<<8)+MDrv_AVD_GetRegValue(BK_AFEC_D2);
          if (((temp[0]==temp[1]) && (temp[2]==temp[3])) && (prevline!=temp[2]))
          {
            dpl[count]=temp[0];
            //if (MDrv_AVD_GetRegValue(0x36E0)&0x02)  dpl[count] |= 0x4000;
            prevline=linenumber[count]=temp[2];
            count++;
          }
        }

        for ( count=0 ; count <TOTAL_LINE ; count++)
        {
          printf("%x %x\n",dpl[count],linenumber[count]);
        }
    }

    if (MDrv_AVD_GetRegValue(BK_AFEC_DB) & 0x02)
    {
        MS_S16 temp0, temp1;
        temp0=(MS_S16)((MDrv_AVD_GetRegValue(BK_AFEC_D0+1)<<8)+MDrv_AVD_GetRegValue(BK_AFEC_D0));
        temp1=(MS_S16)((MDrv_AVD_GetRegValue(BK_AFEC_D2+1)<<8)+MDrv_AVD_GetRegValue(BK_AFEC_D2));
        printf("VD: %d %d\r\n",temp0, temp1);
    }
#endif

    MDrv_AVD_SetRegFromDSP();

#if (PATCH_COMB_ZONEPLATE == 1)
    {
        msAPI_AVD_ZonePlatePatch();
    }
#elif(PATCH_COMB_STILLIMAGE==1)
    {

#if NEW_COMB_STILLIMAGE
        // comb filter for low signal compesation
        if(m_eVideoSource == E_INPUT_SOURCE_ATV)
        {
            u8Ctl = MDrv_AVD_GetNoiseMag();// get VD noise magnitude
            //printf(" ====================>  Noise mag =%d \n",(int)u8Ctl);
            if (check_counter<10)
            {
                Total_Nosiemag+= u8Ctl;
                check_counter++;
            }
            else
            {
                u16Value =Total_Nosiemag;
                //printf(" ========================>  AVG noise mag =%d \n",(int) u16Value);
                u16Value = ( 8*_u16PreNoiseMag + 8*u16Value )/16;
                /////////////////////////////////////////////////////////////////////////////////////

                if(u16Value <= 0x14)
                {
                    _u16PreNoiseMag = u16Value;
                    check_counter = 0;
                    Total_Nosiemag = 0;
                    u8Ctl = MDrv_AVD_GetRegValue(BK_COMB_38);
                    //printf("=====>Thread =%d \n\n",u16Value);
                    //printf("=====>1Thread1: u16Value =0x%x \n\n",u16Value);
                    MDrv_AVD_SetRegValue(BK_COMB_37, 0x88);
                    MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                    MDrv_AVD_SetRegValue(BK_COMB_7C, 0x10);
                    MDrv_AVD_SetRegValue(BK_COMB_ED, 0x80);
                    //MDrv_AVD_SetRegValue(BK_COMB_C0, 0x6C);
                    status = 1;
                }
                else if(u16Value<=0x29 && u16Value>=0x19)
                {
                    _u16PreNoiseMag = u16Value;
                    check_counter = 0;
                    Total_Nosiemag = 0;
                    u8Ctl = MDrv_AVD_GetRegValue(BK_COMB_38);
                    //printf("=====>Thread =%d \n\n",u16Value);
                    //printf("=====>2Thread2: u16Value =0x%x \n\n",u16Value);
                    MDrv_AVD_SetRegValue(BK_COMB_37, 0x8F);
                    MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                    MDrv_AVD_SetRegValue(BK_COMB_7C, 0x20);
                    MDrv_AVD_SetRegValue(BK_COMB_ED, 0x82);
                    //MDrv_AVD_SetRegValue(BK_COMB_C0, 0x6C);
                    status = 2;
                }
                else if(u16Value >= 0x30)
                {
                    _u16PreNoiseMag = u16Value;
                    check_counter = 0;
                    Total_Nosiemag = 0;
                    u8Ctl = MDrv_AVD_GetRegValue(BK_COMB_38);
                    //printf("=====>Thread =%d \n\n",u16Value);
                    //printf("=====>3Thread3: u16Value =0x%x \n\n",u16Value);
                    MDrv_AVD_SetRegValue(BK_COMB_37, 0x0B);
                    MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                    MDrv_AVD_SetRegValue(BK_COMB_7C, 0x10);
                    MDrv_AVD_SetRegValue(BK_COMB_ED, 0x80);
                    //MDrv_AVD_SetRegValue(BK_COMB_C0/., 0x6C);
                    status = 3;
                }
                else if(u16Value<0x19 && u16Value>0x14)
                {
                    _u16PreNoiseMag = u16Value;
                    check_counter = 0;
                    Total_Nosiemag = 0;
                    u8Ctl = MDrv_AVD_GetRegValue(BK_COMB_38);
                    //printf("=====>Thread =%d \n\n",u16Value);
                    if(status==1)
                    {
                       //printf("=====>4Thread1: u16Value =0x%x \n\n",u16Value);
                       MDrv_AVD_SetRegValue(BK_COMB_37, 0x88);
                       MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                       MDrv_AVD_SetRegValue(BK_COMB_7C, 0x10);
                       MDrv_AVD_SetRegValue(BK_COMB_ED, 0x80);
                       //MDrv_AVD_SetRegValue(BK_COMB_C0, 0x6C);
                       status = 1;
                    }
                    else if(status==2)
                    {
                       //printf("=====>5Thread2: u16Value =0x%x \n\n",u16Value);
                       MDrv_AVD_SetRegValue(BK_COMB_37, 0x8F);
                       MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                       MDrv_AVD_SetRegValue(BK_COMB_7C, 0x20);
                       MDrv_AVD_SetRegValue(BK_COMB_ED, 0x82);
                       //MDrv_AVD_SetRegValue(BK_COMB_C0, 0x6C);
                       status = 2;
                   }
                   else if(status==3)
                   {
                       //printf("=====>6Thread3: u16Value =0x%x \n\n",u16Value);
                       status = 2;
                   }
                }
                else if(u16Value < 0x30 && u16Value > 0x29)
                {
                    _u16PreNoiseMag = u16Value;
                    check_counter = 0;
                    Total_Nosiemag = 0;
                    u8Ctl = MDrv_AVD_GetRegValue(BK_COMB_38);
                    //printf("=====>Thread =%d \n\n",u16Value);

                    if(status==1)
                    {
                        //printf("=====>7Thread1: u16Value =0x%x \n\n",u16Value);
                        status = 2;
                    }
                    else if(status==2)
                    {
                       //printf("=====>8Thread2: u16Value =0x%x \n\n",u16Value);
                       MDrv_AVD_SetRegValue(BK_COMB_37, 0x8F);
                       MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                       MDrv_AVD_SetRegValue(BK_COMB_7C, 0x20);
                       MDrv_AVD_SetRegValue(BK_COMB_ED, 0x82);
                       //MDrv_AVD_SetRegValue(BK_COMB_C0, 0x6C);
                       status = 2;
                    }
                    else if(status==3)
                    {
                       //printf("=====>9Thread3: u16Value =0x%x \n\n",u16Value);
                       MDrv_AVD_SetRegValue(BK_COMB_37, 0x0B);
                       MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                       MDrv_AVD_SetRegValue(BK_COMB_7C, 0x10);
                       MDrv_AVD_SetRegValue(BK_COMB_ED, 0x80);
                       //MDrv_AVD_SetRegValue(BK_COMB_C0, 0x6C);
                       status = 3;
                   }
                }
            /////////////////////////////////////////////////////////////////////////////////////

            }
        }
#else
     // comb filter for low signal compesation
        if(m_eVideoSource == E_INPUT_SOURCE_ATV)
        {
            u8Ctl = MDrv_AVD_GetNoiseMag();// get VD noise magnitude
            u8Value = (1*_u8PreNoiseMag + 1*u8Ctl)/2;
            _u8PreNoiseMag = u8Value;

            u8Ctl = MDrv_AVD_GetRegValue(BK_COMB_38);
            if(u8Value <= 0x02)
            {
                MDrv_AVD_SetRegValue(BK_COMB_37, 0x89);
                MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                MDrv_AVD_SetRegValue(BK_COMB_7C, 0x10);
            }
            else if(u8Value <= 0x04)
            {
                MDrv_AVD_SetRegValue(BK_COMB_37, 0x8A);
                MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                MDrv_AVD_SetRegValue(BK_COMB_7C, 0x10);
            }
            else
            {
                MDrv_AVD_SetRegValue(BK_COMB_37, 0x8B);
                //MDrv_WriteByte(BK_COMB_38, (u8Ctl & 0xF8) | 0x06);
                MDrv_AVD_SetRegValue(BK_COMB_38, (u8Ctl & 0xF8));
                MDrv_AVD_SetRegValue(BK_COMB_7C, 0x20);
            }

            if(u8Value >= 0x08)
            {
                MDrv_AVD_SetRegValue(BK_COMB_37, MDrv_AVD_GetRegValue(BK_COMB_37)&(~BIT7));
            }
        }
#endif
    }
#endif
}


U16 msAPI_AVD_CheckStatusLoop(void) // only for channel scan
{
    return MDrv_AVD_Scan_HsyncCheck(15);
}


/******************************************************************************/
///- API for Video processor of VD
/******************************************************************************/
void msAPI_AVD_VideoProcessor(void)
{
    #define IsVideoSrcVd(x) (E_INPUT_SOURCE_ATV <= (x) && (x) <= E_INPUT_SOURCE_SCART2) // <-<<< CHECK NAMING AND RELOCATION
    if( !IsVideoSrcVd(m_eVideoSource) )
    {
        return;
    }


    m_wVideoUpCountTimer++;
    if( m_wVideoUpCountTimer >= 0xFFF0 )
    {
        m_wVideoUpCountTimer = 1;
    }


    msAPI_AVD_SetRegFromDSP();

#if ENABLE_CH_FORCEVIDEOSTANDARD
    if( g_VD_u32ForceVideoStd_CountDownTime == 1 )
    {
        g_VD_u32ForceVideoStd_CountDownTime = 0;//kent
        //printf("Force VD timeout\n");
        msAPI_AVD_StartAutoStandardDetection();
        //msAPI_Timer_Delayms(70);
    }
#endif

#if(ENABLE_ATSC)
    if( !MApp_Is_InAutoScan_ATSC() )
#endif
    {
        msAPI_AVD_CheckVideoStandard();
    }

    if ( msAPI_Tuner_IsTuningProcessorBusy() == TRUE )
    {
        return;
    }

#if(INPUT_SCART_VIDEO_COUNT>0)
    if( (m_wVideoUpCountTimer % 43) == 0 )
    {
        msAPI_AVD_CheckAutoAV();
    }
#endif

    if( (m_wVideoUpCountTimer % 29) == 0 )
    {
        msAPI_AVD_CheckAspectRatio();
    }

}

/******************************************************************************/
///- This function will get Video standard
/// @return AVD_VideoStandardType: Video standard type
/******************************************************************************/
AVD_VideoStandardType msAPI_AVD_GetVideoStandard(void)
{
    if( m_eVideoStandard == E_VIDEOSTANDARD_NOTSTANDARD )
    {
    #ifdef ATSC_SYSTEM
        return msAPI_AVD_GetResultOfAutoStandardDetection();
    #else
        if( m_eVideoSource == E_INPUT_SOURCE_ATV && TRUE == m_bIsAutoAV2Active )
        {
            msAPI_ATV_GetLastVideoStandard(E_INPUT_SOURCE_SCART2, &m_eVideoStandard);
        }
        else if( m_eVideoSource == E_INPUT_SOURCE_ATV && TRUE == m_bIsAutoAV1Active )
        {
            msAPI_ATV_GetLastVideoStandard(E_INPUT_SOURCE_SCART1, &m_eVideoStandard);
        }
        else
        {
            msAPI_ATV_GetLastVideoStandard(m_eVideoSource, &m_eVideoStandard);
        }
    #endif
    }
    return m_eVideoStandard;
}

AVD_VideoStandardType msAPI_AVD_GetCurrentVideoStandard(void)
{
    return m_eCurrentVideoStandard;
}

/******************************************************************************/
///- This function will check if Video format changed
/// @return BOOLEAN: Video format changed or not
///- TRUE: Video format changed
///- FALSE: Not changed
/******************************************************************************/
BOOLEAN msAPI_AVD_IsVideoFormatChanged(void)
{
    if( m_bIsVideoFormatChanged == FALSE )
    {
        return FALSE;
    }

    //m_bIsVideoFormatChanged = FALSE;  //It's replaced by "msAPI_AVD_SetIsVideoFormatChangedAsFalse" 20100330EL
    return TRUE;
}

void msAPI_AVD_SetIsVideoFormatChangedAsFalse(void)  //20100330EL
{
    m_bIsVideoFormatChanged = FALSE;
}

/******************************************************************************/
///- This function will check if Video input changed
/// @return BOOLEAN: Video input changed or not
///- TRUE: Video input changed
///- FALSE: Not changed
/******************************************************************************/
BOOLEAN msAPI_AVD_IsVideoInputChanged(void)
{
    if( m_bIsVideoInputChanged == FALSE )
    {
        return FALSE;
    }

    m_bIsVideoInputChanged = FALSE;

    return TRUE;
}

/******************************************************************************/
///- This function will start Audo standard detection
/******************************************************************************/
void msAPI_AVD_StartAutoStandardDetection_2(void)
{
    MDrv_AVD_StartAutoStandardDetection();

    g_VD_u32ForceVideoStd_CountDownTime = 0;

    msAPI_AVD_SetForceVideoStandardFlag(FALSE);
}

void msAPI_AVD_ForceVideoStandard_2(AVD_VideoStandardType eVideoStandardType)
{
    //PRINT_CURRENT_LINE();
    //printf("msAPI_AVD_ForceVideoStandard_2(%u)\n", eVideoStandardType);
    MDrv_AVD_ForceVideoStandard(eVideoStandardType);

    g_VD_u32ForceVideoStd_CountDownTime = 0;

    msAPI_AVD_SetForceVideoStandardFlag(TRUE);
}

void msAPI_AVD_Set_ForceVideoStd_CountDownTime(U32 u32Time)
{
    //printf("msAPI_AVD_Set_ForceVideoStd_CountDownTime(%u)\n", u32Time);
    g_VD_u32ForceVideoStd_CountDownTime = u32Time;
}

/******************************************************************************/
///- This function will get result of auto standard detection
/// @return AVD_VideoStandardType: video standard type
/******************************************************************************/
AVD_VideoStandardType msAPI_AVD_GetResultOfAutoStandardDetection(void)
{
    AVD_VideoStandardType eStandard;

    eStandard = msAPI_AVD_GetStandardDetection();
    //printf("msAPI_AVD_GetStandardDetection() =>%u\n", eStandard);

  #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM   /*|| (TV_SYSTEM == TV_NTSC)*/ )
    if(IsATVInUse()&& !msAPI_ATV_IsProgramAutoColorSystem(msAPI_ATV_GetCurrentProgramNumber()))
    {
        m_eVideoStandard = msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());
        //printf ("33333********%bu\n", m_eVideoStandard);
        msAPI_AVD_SetVideoStandard (m_eVideoStandard);
    }
    else
    {
        msAPI_AVD_SetVideoStandard(eStandard);
    }
  #else
    msAPI_AVD_SetVideoStandard(eStandard);
  #endif

    return eStandard;
}

#if (PQ_ENABLE_VD_SAMPLING)
void _msAPI_VD_SetSamplingType(AVD_VideoStandardType eStandard)
{
    MS_PQ_VD_Sampling_Info stVDSamplingInfo;
    PQ_VIDEOSTANDARD_TYPE ePQStandard;
    MS_U32 u32AVDFlag;

    switch(eStandard)
    {
    case E_VIDEOSTANDARD_PAL_BGHI:
        ePQStandard = E_PQ_VIDEOSTANDARD_PAL_BGHI;
        break;
    case E_VIDEOSTANDARD_NTSC_M:
        ePQStandard = E_PQ_VIDEOSTANDARD_NTSC_M;
        break;

    case E_VIDEOSTANDARD_SECAM:
        ePQStandard = E_PQ_VIDEOSTANDARD_SECAM;
        break;

    case E_VIDEOSTANDARD_NTSC_44:
        ePQStandard = E_PQ_VIDEOSTANDARD_NTSC_44;
        break;

    case E_VIDEOSTANDARD_PAL_M:
        ePQStandard = E_PQ_VIDEOSTANDARD_PAL_M;
        break;

    case E_VIDEOSTANDARD_PAL_N:
        ePQStandard = E_PQ_VIDEOSTANDARD_PAL_N;
        break;

    case E_VIDEOSTANDARD_PAL_60:
        ePQStandard = E_PQ_VIDEOSTANDARD_PAL_60;
        break;


    default:
        ePQStandard = E_PQ_VIDEOSTANDARD_NOTSTANDARD;
        break;

    }

    if(ePQStandard != E_PQ_VIDEOSTANDARD_NOTSTANDARD)
    {
        u32AVDFlag = MDrv_AVD_GetFlag() & ~(AVD_PATCH_HTOTAL_MASK);
        memset(&stVDSamplingInfo, 0, sizeof(MS_PQ_VD_Sampling_Info));
        MDrv_PQ_Get_VDSampling_Info(PQ_MAIN_WINDOW, PQ_INPUT_SOURCE_CVBS, ePQStandard, &stVDSamplingInfo);

        if(stVDSamplingInfo.eType == PQ_VD_SAMPLING_ON)
        {
            u32AVDFlag = (u32AVDFlag & ~(AVD_PATCH_HTOTAL_MASK)) | AVD_PATCH_HTOTAL_USER;
            MDrv_AVD_Set_Htt_UserMD(stVDSamplingInfo.u16Htt);
            MDrv_AVD_SetFlag(u32AVDFlag);
        }
        else
        {
            u32AVDFlag = (u32AVDFlag & ~(AVD_PATCH_HTOTAL_MASK)) | AVD_PATCH_HTOTAL_1135;
            MDrv_AVD_SetFlag(u32AVDFlag);
        }


        //printf("VD Sampling SD=%d Sample=%d, Flag=%x\n", stVDSamplingInfo.eType, u32AVDFlag);
    }
}
#endif

/******************************************************************************/
///- This function will set video standard
/// @param eDetectedStandard \b IN: video standard detected
/// -@see AVD_VideoStandardType
/******************************************************************************/
//
void msAPI_AVD_SetVideoStandard_2(AVD_VideoStandardType eDetectedStandard)
{
    AVD_VideoStandardType eStandard;

    DEBUG_AVD( printf("msAPI_AVD_SetVideoStandard_2(0x%x)\n", eDetectedStandard) );
    //printf("msAPI_AVD_SetVideoStandard(%u)\n", eDetectedStandard);

    if( eDetectedStandard == E_VIDEOSTANDARD_NOTSTANDARD )
    {
        // Do nothing?
        //printf("Set Video Standard=No STd!\n");
        //return;

    #if(ENABLE_ATSC)
        eStandard = E_VIDEOSTANDARD_NTSC_M;
    #else
        if( m_eVideoSource == E_INPUT_SOURCE_ATV && TRUE == m_bIsAutoAV2Active )
        {
            msAPI_ATV_GetLastVideoStandard(E_INPUT_SOURCE_SCART2, &eStandard);
        }
        else if( m_eVideoSource == E_INPUT_SOURCE_ATV && TRUE == m_bIsAutoAV1Active )
        {
            msAPI_ATV_GetLastVideoStandard(E_INPUT_SOURCE_SCART1, &eStandard);
        }
        else
        {
            msAPI_ATV_GetLastVideoStandard(m_eVideoSource, &eStandard);
        }
    #endif

        printf("\e[31;1m VD: SetStd: No sync => Use Std=%s \33[m \n",
                        msAPI_AVD_Get_StdString(eStandard) );
    }
    else
    {
        eStandard = eDetectedStandard;
    }


#if(PQ_ENABLE_VD_SAMPLING)
    _msAPI_VD_SetSamplingType(eStandard);
#endif

    MDrv_AVD_SetVideoStandard(eStandard, msAPI_Tuner_IsTuningProcessorBusy());

//    msAPI_TTX_SetVideoStandard(eStandard);

    m_bIsVideoFormatChanged = TRUE;

    m_eVideoStandard = eStandard;

    // Check VD std..., only when VD has signal
    //printf("m_u16LatchStatus=0x%X\n", m_u16LatchStatus);
    if( m_u16LatchStatus&(VD_STATUS_RDY|VD_HSYNC_LOCKED|VD_SYNC_LOCKED) )
    {
        AVD_VideoStandardType eVideoStandardCorrect = m_eVideoStandard;
        BOOLEAN bVDInputIs50Hz = msAPI_AVD_Is_Input50Hz();


        // Correct VD std ...
        switch( m_eVideoStandard )
        {
            default:
                // Do nothing
                break;
            case E_VIDEOSTANDARD_PAL_BGHI: // 50Hz.Pal 443
                if( bVDInputIs50Hz == FALSE ) // Input is 60Hz
                    eVideoStandardCorrect = E_VIDEOSTANDARD_PAL_M;
                break;
            case E_VIDEOSTANDARD_SECAM:
                if( bVDInputIs50Hz == FALSE ) // Input is 60Hz
                    eVideoStandardCorrect = E_VIDEOSTANDARD_PAL_M;
                break;
            case E_VIDEOSTANDARD_PAL_N: // 50Hz.Pal 358
                if( bVDInputIs50Hz == FALSE ) // Input is 60Hz
                    eVideoStandardCorrect = E_VIDEOSTANDARD_PAL_M;
                break;

            case E_VIDEOSTANDARD_NTSC_M: // 60Hz 357
            case E_VIDEOSTANDARD_NTSC_44: // 60Hz. 443
                if( bVDInputIs50Hz == TRUE ) // Input is 50Hz
                    eVideoStandardCorrect = E_VIDEOSTANDARD_PAL_BGHI;
                break;

            case E_VIDEOSTANDARD_PAL_M: // 60Hz 357
            case E_VIDEOSTANDARD_PAL_60: // 60Hz
                if( bVDInputIs50Hz == TRUE ) // Input is 50Hz
                    eVideoStandardCorrect = E_VIDEOSTANDARD_PAL_BGHI;
                break;
        }

        if( eVideoStandardCorrect != m_eVideoStandard )
        {
            printf("VD-SetStd: eVideoStandardCorrect=%s\n", msAPI_AVD_Get_StdString(eVideoStandardCorrect));
        }
    }

    switch( m_eVideoStandard ) // TODO should remove mvideo_vd_set_videosystem()
    {
        case E_VIDEOSTANDARD_PAL_BGHI:  mvideo_vd_set_videosystem(SIG_PAL);       break;
        case E_VIDEOSTANDARD_NTSC_M:    mvideo_vd_set_videosystem(SIG_NTSC);      break;
        case E_VIDEOSTANDARD_SECAM:     mvideo_vd_set_videosystem(SIG_SECAM);     break;
        case E_VIDEOSTANDARD_NTSC_44:   mvideo_vd_set_videosystem(SIG_NTSC_443);  break;
        case E_VIDEOSTANDARD_PAL_M:     mvideo_vd_set_videosystem(SIG_PAL_M);     break;
        case E_VIDEOSTANDARD_PAL_N:     mvideo_vd_set_videosystem(SIG_PAL_NC);    break;
        case E_VIDEOSTANDARD_PAL_60:    mvideo_vd_set_videosystem(SIG_NTSC_443);  break;
        default:                        mvideo_vd_set_videosystem(SIG_PAL);       break;
    }

  #if 0
    msAPI_AVD_ImprovePictureQuality(TTX_DISPLAY_PICTURE_MODE);
  #endif
}

/******************************************************************************/
///- This function will get aspect ratio code
/// @return ASPECT_RATIO_TYPE : aspect ratio type
/******************************************************************************/
ASPECT_RATIO_TYPE msAPI_AVD_GetAspectRatioCode(void)
{
    if ( IS_WSS_ENABLED == FALSE )
    {
        return ARC_INVALID;
    }

    return m_eAspectRatioCode;
}

/******************************************************************************/
///- This function will check if aspect ratio is changed or not
/// @return BOOLEAN : aspect ratio is changed or not
/// - TRUE: aspect ratio is changed
/// - FALSE: Not changed
/******************************************************************************/
BOOLEAN msAPI_AVD_IsAspectRatioChanged(void)
{
    if ( IS_WSS_ENABLED == FALSE )
    {
        return FALSE;
    }

    if ( m_bIsAspectRatioChanged == FALSE )
    {
        return FALSE;
    }

    m_bIsAspectRatioChanged = FALSE;

    return TRUE;
}

/******************************************************************************/
///- This function will be used for waiting Video sync lock
/******************************************************************************/
void msAPI_AVD_WaitForVideoSyncLock(void)
{
    BYTE cLoopStop;

    for(cLoopStop=0; cLoopStop < 10; cLoopStop++)
    {
        if( TRUE == MDrv_AVD_IsSyncLocked() )
        {
            SwitchChannelTimePrintf("[SwitchChannelTime][Exit]msAPI_AVD_WaitForVideoSyncLock(); --- %ld\n");
            break;
        }
        msAPI_Timer_Delayms(20);
    }
}
/******************************************************************************/
///- This function will set Video factory data
/******************************************************************************/

static void msAPI_AVD_SetFactoryMode(void)
{
#if ENABLE_VD_PACH_IN_CHINA
    MDrv_WriteByte(BK_AFEC_D4_ADDRESS,G_FACTORY_SETTING.stVDSetting.u8AFEC_D4);
    MDrv_WriteByteMask(BK_AFEC_D5_ADDRESS, (G_FACTORY_SETTING.stVDSetting.u8AFEC_D5_Bit2<<2), BIT2);
    MDrv_WriteByteMask(BK_AFEC_D8_ADDRESS, G_FACTORY_SETTING.stVDSetting.u8AFEC_D8_Bit3210, 0x0F);
    MDrv_WriteByteMask(BK_AFEC_D9_ADDRESS, G_FACTORY_SETTING.stVDSetting.u8AFEC_D9_Bit0, BIT0);
#endif
}

/******************************************************************************/
///- This function will get Video source
/// @return AVD_InputSourceType: Video source type
/******************************************************************************/
AVD_InputSourceType msAPI_AVD_GetVideoSource(void)
{
    return m_eVideoSource;
}

void msAPI_AVD_SetForceVideoStandardFlag(BOOLEAN bEnable)
{
    m_bForceVideoStandardFlag = bEnable;
}

BOOLEAN msAPI_AVD_GetForceVideoStandardFlag(void)
{
    return m_bForceVideoStandardFlag;
}

/******************************************************************************/
///- This function will set Video source
/// @param eSource \b IN: Video source type
/// -@see AVD_InputSourceType
/******************************************************************************/
void msAPI_AVD_SetVideoSource(AVD_InputSourceType eSource)
{
    //printf("msAPI_AVD_SetVideoSource(src=%u)\n", eSource);
    //printf("m_eVideoSource:%bu \n", m_eVideoSource);
    msAPI_AVD_SetFactoryMode();
    switch(eSource)
    {
    case E_INPUT_SOURCE_ATV:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_ATV,(U8)INPUT_SCART_FB_MUX);
        break;

    case E_INPUT_SOURCE_CVBS1:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_CVBS1,(U8)INPUT_SCART_FB_MUX);
        break;

    case E_INPUT_SOURCE_CVBS2:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_CVBS2,(U8)INPUT_SCART_FB_MUX);
        break;

    case E_INPUT_SOURCE_CVBS3:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_CVBS3,(U8)INPUT_SCART_FB_MUX);
        break;

    case E_INPUT_SOURCE_SVIDEO1:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_SVIDEO1,(U8)INPUT_SCART_FB_MUX);
        break;

    case E_INPUT_SOURCE_SVIDEO2:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_SVIDEO2,(U8)INPUT_SCART_FB_MUX);
        break;

    case E_INPUT_SOURCE_SCART1:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_SCART1,(U8)INPUT_SCART_FB_MUX);
        break;

    case E_INPUT_SOURCE_SCART2:
        MDrv_AVD_SetInput(E_INPUT_SOURCE_SCART2,(U8)INPUT_SCART2_FB_MUX);
        break;

    case E_INPUT_SOURCE_YPbPr: // TODO remove this item
        break;

    default:
        return;
    }

  #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
    if (eSource==E_INPUT_SOURCE_ATV)
    {
        //MDrv_WriteRegBit(0x101E27L, TRUE, BIT0);      //2014.01.09 Dia.chiu, unused settings now, move to driver level
        //MDrv_WriteRegBit(0x101E0BL, FALSE, BIT0);
    }
    else
    {
        //MDrv_WriteRegBit(0x101E27L, FALSE, BIT0);    //2014.01.09 Dia.chiu, unused settings now, move to driver level
      #if (TV_FREQ_SHIFT_CLOCK)
        msAPI_Tuner_Patch_ResetTVShiftClk();
      #endif
    }
  #endif

    msAPI_AVD_SetForcedFreeRun(FALSE);

    m_eVideoSource = eSource;
    m_eVideoStandard = E_VIDEOSTANDARD_NOTSTANDARD;
    m_eCurrentVideoStandard = E_VIDEOSTANDARD_NOTSTANDARD;

    m_bIs3DCombfilterUsed = FALSE;
    VDScart1SrcType = E_SCART_SRC_TYPE_UNKNOWN;

    m_eStandardDetectionState = E_DETECTION_START;
    m_eFSMDetectedStandard = E_VIDEOSTANDARD_NOTSTANDARD;
}

/******************************************************************************/
///- This function will detect video standard
/// @param eOperationMethod \b IN: Video source type
/// -@see OPERATIONMETHOD
/******************************************************************************/
void msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD eOperationMethod)
{
    AVD_VideoStandardType    eStandard;

    //if( eOperationMethod == OPERATIONMETHOD_AUTOMATICALLY ) // <-<<< OPTIMIZE
    {
        msAPI_AVD_StartAutoStandardDetection();
        eStandard = msAPI_AVD_GetStandardDetection();

      #if 0
        if( eStandard == E_VIDEOSTANDARD_NOTSTANDARD )
        {
            eOperationMethod = OPERATIONMETHOD_MANUALLY;
        }
      #else // Modified by coverity_0464
        UNUSED(eOperationMethod);
      #endif
    }

  #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM   || (TV_SYSTEM == TV_NTSC) )
    if(IsATVInUse())
    {
        eStandard=msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());
        msAPI_AVD_SetVideoStandard(eStandard);
    }
    else
  #endif
    msAPI_AVD_SetVideoStandard(eStandard);

    // This is a input source base color standard.
  #ifndef ATSC_SYSTEM
    if( eStandard != E_VIDEOSTANDARD_NOTSTANDARD )
    {
        if( m_eVideoSource == E_INPUT_SOURCE_ATV && TRUE == m_bIsAutoAV2Active )
        {
            msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_SCART2, eStandard);
        }
        else if( m_eVideoSource == E_INPUT_SOURCE_ATV && TRUE == m_bIsAutoAV1Active )
        {
            msAPI_ATV_SetLastVideoStandard(E_INPUT_SOURCE_SCART1, eStandard);
        }
        else
        {
            msAPI_ATV_SetLastVideoStandard(m_eVideoSource, eStandard);
        }
    }
  #endif

    // This is a channel base color standard.
    if ( m_eVideoSource == E_INPUT_SOURCE_ATV && FALSE == m_bIsAutoAV2Active  && FALSE == m_bIsAutoAV1Active)
    {
        if( TRUE == msAPI_Tuner_IsCurrentChannelAndSavedChannelSame() )
        {
            msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), m_eVideoStandard);
        }
    }
}

#if 0 //unused
/******************************************************************************/
///- This function will get standard frequency
/// @return VIDEOFREQ: Video frequency
/******************************************************************************/
VIDEOFREQ msAPI_AVD_GetStandardFreq(void)
{
    switch(m_eVideoStandard)
    {
    case E_VIDEOSTANDARD_PAL_BGHI:
    case E_VIDEOSTANDARD_SECAM:
    case E_VIDEOSTANDARD_PAL_N:
        return E_VIDEO_FQ_50Hz;

    case E_VIDEOSTANDARD_NTSC_M:
    case E_VIDEOSTANDARD_NTSC_44:
    case E_VIDEOSTANDARD_PAL_M:
    case E_VIDEOSTANDARD_PAL_60:
        return E_VIDEO_FQ_60Hz;

    default:
        break;
    }

    return E_VIDEO_FQ_NOSIGNAL;
}
#endif
/******************************************************************************/
///- This function will get Vertical frequency
/// @return AVD_VideoFreq: Video frequency
/******************************************************************************/
AVD_VideoFreq msAPI_AVD_GetVerticalFreq(void)
{
    return MDrv_AVD_GetVerticalFreq();
}

/******************************************************************************/
///- This function will check if sync is changed or NOT
/// @return BOOLEAN:
/// - TRUE: Sync is changed
/// - FALSE: Sync is not changed
/******************************************************************************/
BOOLEAN msAPI_AVD_IsSyncChanged(void)
{
    if( m_bIsSyncChanged == FALSE )
    {
        return FALSE;
    }

    m_bIsSyncChanged = FALSE;
    return TRUE;
}

/******************************************************************************/
///- This function will check if sync is locked or NOT
/// @return BOOLEAN:
/// - TRUE: Sync is locked
/// - FALSE: Sync is not locked
/******************************************************************************/
BOOLEAN msAPI_AVD_IsSyncLocked(void)
{
    return MDrv_AVD_IsSyncLocked();
}

/******************************************************************************/
///- This function will update auto AV state
/// @return BOOLEAN: status
/// - TRUE: Success
/// - FALSE: Fail
/******************************************************************************/
BOOLEAN msAPI_AVD_UpdateAutoAVState(void)
{
#if( INPUT_SCART_VIDEO_COUNT == 0 )
    return FALSE;
#else
    U16 cCurrentScart1ID;
    U16 cCurrentScart2ID;
    BOOLEAN bResult = FALSE;

    if( FALSE == IS_SCART_ENABLED )
    {
        return FALSE;
    }

    cCurrentScart1ID = GetScart1IDLevel();
    cCurrentScart2ID = GetScart2IDLevel();

    //printf("Scart1ID Level = %bd\n", cCurrentScart1ID);
    //printf("Scart2ID Level = %bd\n", cCurrentScart2ID);

    if( m_cPreviousScart2IDLevelForAutoAV < SCART_16_9_LEVEL && SCART_16_9_LEVEL <= cCurrentScart2ID )
    {
        if( m_bIsAutoAV2Active == FALSE )
        {
            m_bIsAutoAV2Active = TRUE;
            bResult = TRUE;
        }
    }
    else if( cCurrentScart2ID < SCART_16_9_LEVEL && SCART_16_9_LEVEL <= m_cPreviousScart2IDLevelForAutoAV )
    {
        if( m_bIsAutoAV2Active == TRUE )
        {
            m_bIsAutoAV2Active = FALSE;
            bResult = TRUE;
        }
    }
    else if( m_cPreviousScart1IDLevelForAutoAV < SCART_16_9_LEVEL && SCART_16_9_LEVEL <= cCurrentScart1ID )
    {
        if( m_bIsAutoAV1Active == FALSE )
        {
            m_bIsAutoAV1Active = TRUE;
            bResult = TRUE;
        }
    }
    else if( cCurrentScart1ID < SCART_16_9_LEVEL && SCART_16_9_LEVEL <= m_cPreviousScart1IDLevelForAutoAV )
    {
        if( m_bIsAutoAV1Active == TRUE )
        {
            m_bIsAutoAV1Active = FALSE;
            bResult = TRUE;
        }
    }

    /*
    if(bResult == TRUE)
    {
        printf("\nSCART2=%x, SCART1=%x \n",m_bIsAutoAV2Active,m_bIsAutoAV1Active);
    }
    */

    m_cPreviousScart1IDLevelForAutoAV = cCurrentScart1ID;
    m_cPreviousScart2IDLevelForAutoAV = cCurrentScart2ID;

    return bResult;
#endif
}

/******************************************************************************/
///- This function will check if Auto AV is active
/// @param eAutoAVSource \b IN: Auto AV source
/// -@see AVD_AutoAVSourceType
/// @return BOOLEAN: status
/// - TRUE: Auto AV is active
/// - FALSE: Not active
/******************************************************************************/
BOOLEAN msAPI_AVD_IsAutoAVActive(AVD_AutoAVSourceType eAutoAVSource)
{
    if( FALSE == IS_SCART_ENABLED )
    {
        return FALSE;
    }

    switch( eAutoAVSource )
    {
    case E_AUTOAV_SOURCE_1:
        return m_bIsAutoAV1Active;

    case E_AUTOAV_SOURCE_2:
        return m_bIsAutoAV2Active;

    case E_AUTOAV_SOURCE_ALL:
        return (m_bIsAutoAV1Active || m_bIsAutoAV2Active);

    default:
        return FALSE; // Need touch. Invaild parameter.
    }
}

/******************************************************************************/
///- This function will turn off Auto AV
/******************************************************************************/
void msAPI_AVD_TurnOffAutoAV(void)
{
    if( m_bIsAutoAV1Active == FALSE && m_bIsAutoAV2Active == FALSE)
    {
        return;
    }
    m_bIsAutoAV1Active = FALSE;
    m_bIsAutoAV2Active = FALSE;

    msAPI_AVD_SwitchAutoAV();
}

/******************************************************************************/
///- This function will switch Auto AV
/******************************************************************************/
void msAPI_AVD_SwitchAutoAV(void)
{
    m_bIsVideoInputChanged = TRUE;
}

//==================================================================
#if(ENABLE_SCART_MONITOR)
static BOOLEAN s_AVD_bScartSrcIsStable = FALSE;
static SCART_SOURCE_TYPE s_AVD_bStableScartSrcType = E_SCART_SRC_TYPE_UNKNOWN;
void msAPI_AVD_Scart_Monitor(void)
{
    static U8 s_u8ScartSrcRGBStableCount = 0;
    static BOOLEAN s_bOldScartIsRGB = 0;
    BOOLEAN bCurScartIsRGB = msAPI_AVD_IsScartRGB();

    //if( bCurScartIsRGB )
    {
        //printf("Old=%u, CurScartIsRGB=%u\n", s_bOldScartIsRGB, bCurScartIsRGB);
    }

    if( bCurScartIsRGB == s_bOldScartIsRGB )
    {
        if( s_u8ScartSrcRGBStableCount < 255 )
            s_u8ScartSrcRGBStableCount += 1;

        if( s_AVD_bScartSrcIsStable == FALSE )
        {
            if( s_u8ScartSrcRGBStableCount >= 20 )
            {
                s_AVD_bScartSrcIsStable = TRUE;
                printf("1. Scart Src: %u", s_AVD_bStableScartSrcType);
                if( bCurScartIsRGB )
                {
                    s_AVD_bStableScartSrcType = E_SCART_SRC_TYPE_RGB;
                    printf(" => RGB\n");
                }
                else
                {
                    s_AVD_bStableScartSrcType = E_SCART_SRC_TYPE_CVBS;
                    printf(" => CVBS\n");
                }

            }
        }
    }
    else
    {
        s_u8ScartSrcRGBStableCount = 0;

        if( s_AVD_bStableScartSrcType != E_SCART_SRC_TYPE_CVBS )
        {
            printf("2. Scart Src => CVBS\n");
        }

        s_AVD_bScartSrcIsStable = FALSE;
        s_AVD_bStableScartSrcType = E_SCART_SRC_TYPE_CVBS;
    }

    s_bOldScartIsRGB = bCurScartIsRGB;


    // Pass result to VDScart1SrcType
    if( VDScart1SrcType != s_AVD_bStableScartSrcType )
    {
        m_bIsScart1SourceTypeChanged = TRUE;
        VDScart1SrcType = s_AVD_bStableScartSrcType;
        printf("VDScart1SrcType => %u\n", VDScart1SrcType);
    }
}
#endif

/******************************************************************************/
///- This function will get Scart 1 source type
/// @return SCART_SOURCE_TYPE: SCART 1 source type
/******************************************************************************/
SCART_SOURCE_TYPE msAPI_AVD_GetScart1SrcType ( void )
{
    if( FALSE == IS_SCART_ENABLED )
    {
        return E_SCART_SRC_TYPE_CVBS;
    }

#if( !ENABLE_SCART_MONITOR )
    //if ( VDScart1SrcType == E_SCART_SRC_TYPE_UNKNOWN )
    {
        msAPI_AVD_RetrieveScart1SourceType();
    }
#endif

    return VDScart1SrcType;
}

/******************************************************************************/
///- This function will check if Scart 1 source type is changed or NOT
/// @return BOOLEAN: SCART 1 source type is changed or not
/// - TRUE: source type changed
/// - FALSE: not changed
/******************************************************************************/
BOOLEAN msAPI_AVD_IsScart1SourceTypeChanged(void)
{
    if( FALSE == IS_SCART_ENABLED )
    {
        return FALSE;
    }

    if( m_bIsScart1SourceTypeChanged == FALSE )
    {
        return FALSE;
    }

    //printf("rtn s1 changed!\n");
    m_bIsScart1SourceTypeChanged = FALSE;
    return TRUE;
}

/******************************************************************************/
///- This function will clear Aspect ratio
/******************************************************************************/
void msAPI_AVD_ClearAspectRatio(void)
{
    if( m_eAspectRatioCode == ARC_INVALID )
    {
        m_bIsAspectRatioChanged = FALSE;
    }
    else
    {
        m_bIsAspectRatioChanged = TRUE;
    }

    m_eAspectRatioCode = ARC_INVALID;
}

/******************************************************************************/
///- This function will suppress auto AV
/******************************************************************************/
void msAPI_AVD_SuppressAutoAV(void)
{
    msAPI_AVD_UpdateAutoAVState();
    m_bIsAutoAV1Active = FALSE;
    m_bIsAutoAV2Active = FALSE;
}


/******************************************************************************/
///- This function will enable/disable Forced free run
/// @param bEnable: enable/disable Forced free run
/// - TRUE: enable Forced free run
/// - FALSE: disable Forced free run
/******************************************************************************/
void msAPI_AVD_SetForcedFreeRun(BOOLEAN bEnable)
{
#if FORCEDFREEFUN == TRUE
    AVD_VideoStandardType eVideoStandard;

    if( bEnable == FALSE )
    {
        MDrv_AVD_SetFreerunFreq(E_FREERUN_FQ_AUTO);
    }
    else
    {
        eVideoStandard = msAPI_AVD_GetVideoStandard();

        switch(eVideoStandard)
        {
        case E_VIDEOSTANDARD_PAL_BGHI:
        case E_VIDEOSTANDARD_SECAM:
        case E_VIDEOSTANDARD_PAL_N:
            MDrv_AVD_SetFreerunFreq(E_FREERUN_FQ_50Hz);
            break;

        case E_VIDEOSTANDARD_NTSC_M:
        case E_VIDEOSTANDARD_NTSC_44:
        case E_VIDEOSTANDARD_PAL_M:
        case E_VIDEOSTANDARD_PAL_60:
            MDrv_AVD_SetFreerunFreq(E_FREERUN_FQ_60Hz);
            break;
        }
    }
#else
    bEnable = bEnable; // delete waring
#endif
}

/******************************************************************************/
///- This function will enable/disable Horizontal sync detection for tuning
/// @param bEnable: enable/disable Hsync detection
/// - TRUE: enable Hsync detection
/// - FALSE: disable Hsync detection
/******************************************************************************/
void msAPI_AVD_SetHsyncDetectionForTuning(BOOLEAN bEnable)
{
    MDrv_AVD_SetHsyncDetectionForTuning(bEnable);

    if(bEnable)
    {
        _u8AutoTuningIsProgress = 1;
    }
    else
    {
        _u8AutoTuningIsProgress = 0;
    }
}

void msAPI_AVD_3DCombSpeedup(void)
{
    MDrv_AVD_3DCombSpeedup();
}

void msAPI_AVD_SetChannelChange(void)
{
    MDrv_AVD_SetChannelChange();
    MDrv_AVD_3DCombSpeedup();

    msAPI_AVD_CheckStdDetStableReset();
}

/******************************************************************************/
///- This function will set where VD F/W is on.
/// @param bFWStatus: VD F/W Status
/// - TRUE: VD F/W is on Nand Flash
/// - FALSE: VD F/W is on SPI Flash
/******************************************************************************/
void msAPI_AVD_SetFWStatus(BOOLEAN bFWStatus)
{
    bVD_FWStatus = bFWStatus;
}

//****************************************************************************
// Start of private implementation
//****************************************************************************

U8 msAPI_AVD_CheckStdDetStableCnt(void)
{
    return u8StdDetStableCnt;
}

BOOL msAPI_AVD_Is_VDStable(void)
{
    if( (m_eStandardDetectionState == E_VD_STATE__STABLE)
      //&&(u8StdDetStableCnt == 0)
      )
    {
        return TRUE;
    }

    return FALSE;
}

void msAPI_AVD_CheckStdDetStableReset(void)
{
    //printf("[VD]Reset state\n");
    m_eStandardDetectionState = E_DETECTION_START;
    m_eCurrentVideoStandard = E_VIDEOSTANDARD_NOTSTANDARD;

    m_eFSMDetectedStandard = E_VIDEOSTANDARD_NOTSTANDARD;

    m_u16LatchStatus = 0;

    m_bIsVideoFormatChanged = 0;
}

BOOLEAN msAPI_AVD_GetVDisStable(void)
{
    if(m_eStandardDetectionState == E_VD_STATE__STABLE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// please call every 10 ms
#define VD_CHECK_STD_PERIOD     10 // ms, this value should check with MApp_ATVProc_Handler()

#define VD_CHECK_STD_SIGNAL_CHANGE_THRESHOLD            (40/VD_CHECK_STD_PERIOD) // 40ms
#define VD_CHECK_STD_SIGNAL_CHANGE_THRESHOLD_FORCE_MODE (40/VD_CHECK_STD_PERIOD) // 40ms

#define VD_CHECK_STD_STABLE_THRESHOLD_CVBS              (30/VD_CHECK_STD_PERIOD) // 30ms
#define VD_CHECK_STD_STABLE_THRESHOLD_ATV_CUR_NO_STD    (200/VD_CHECK_STD_PERIOD) // 100ms
#define VD_CHECK_STD_STABLE_THRESHOLD_ATV_AUTO_SCAN     (30/VD_CHECK_STD_PERIOD) // 30ms

#if(ENABLE_ATSC&&ENABLE_ATSC_ATV_ONLY_NTSC)
#define VD_CHECK_STD_STABLE_THRESHOLD_ATV_NORMAL        (10/VD_CHECK_STD_PERIOD) // 30ms
#else
#define VD_CHECK_STD_STABLE_THRESHOLD_ATV_NORMAL        (30/VD_CHECK_STD_PERIOD) // 30ms
#endif

#define DEBUG_VD_CHECK_STD(x)   //x
static void msAPI_AVD_CheckVideoStandard(void)
{
    static U32 u32VDCheckStd_LastTime = 0;
    MS_U16 u16VDStatus;
    static MS_U16 u16VDStatus_Last = 0;
    AVD_VideoStandardType eDetectedStandardCurrent;
    static AVD_VideoStandardType eDetectedStandardCurrent_Last = E_VIDEOSTANDARD_MAX;


    if( msAPI_Timer_DiffTime_2(u32VDCheckStd_LastTime, MsOS_GetSystemTime()) < VD_CHECK_STD_PERIOD )
    {
        return;
    }

    u32VDCheckStd_LastTime = MsOS_GetSystemTime();
    //printf("[%u]", u32VDCheckStd_LastTime);

    eDetectedStandardCurrent = MDrv_AVD_GetStandardDetection(&u16VDStatus);
    //printf("MDrv_AVD_GetStandardDetection()=> %u\n",eDetectedStandardCurrent);
    //if( msAPI_AVD_GetForceVideoStandardFlag() )
    //    printf(" {%d} ",eDetectedStandardCurrent);


#if(CHAKRA3_AUTO_TEST)
    BOOLEAN bPrintATInfo = FALSE;

  #if(ENABLE_ATSC)
    if( (m_eStandardDetectionState != E_VD_STATE__STABLE)
      //||(eDetectedStandardCurrent != E_VIDEOSTANDARD_NTSC_M)
      )
    {
        if( !MApp_Is_InAutoScan_ATSC() )
        {
            bPrintATInfo = TRUE;
        }
    }
  #else

    if( m_eStandardDetectionState != E_VD_STATE__STABLE )
    {
        bPrintATInfo = TRUE;
    }

  #endif

    if( bPrintATInfo )
    {
        printf("[VD] 0x%X, Std=%u(%s), S=%u, t=%u\n", u16VDStatus,
            eDetectedStandardCurrent, msAPI_AVD_Get_StdString(eDetectedStandardCurrent),
            //MDrv_AVD_GetNoiseMag(),
            m_eStandardDetectionState,
            g_AT_u32ChangeSourceTime );
    }
#endif


    if( eDetectedStandardCurrent != eDetectedStandardCurrent_Last )
    {
        DEBUG_AVD(printf("VdStd: %u -> %u\n", eDetectedStandardCurrent_Last, eDetectedStandardCurrent););
    #if 0//(CHAKRA3_AUTO_TEST)
        if( bPrintATInfo )
            printf("VdStd: %u -> %u\n", eDetectedStandardCurrent_Last, eDetectedStandardCurrent);
    #endif
        eDetectedStandardCurrent_Last = eDetectedStandardCurrent;
    }

    // Log vd status change...
    // Clear VCR flag
    u16VDStatus &= (~VD_VCR_MODE);
    if(u16VDStatus != u16VDStatus_Last)
    {
        //printf("[VD] status: %X -> %X\n", u16VDStatus_Last, u16VDStatus);
        u16VDStatus_Last = u16VDStatus;
    }

    BOOLEAN bVdIsReady = (u16VDStatus&VD_STATUS_RDY)?1:0;

  #if (ENABLE_ATSC && ENABLE_ATSC_ATV_ONLY_NTSC)
    if( IsATVInUse() )
    {
        // Clear 50Hz flag
        u16VDStatus &= (~VD_VSYNC_50HZ);
    }
    if( IsATVInUse()&&(u16VDStatus&VD_HSYNC_LOCKED) )
    {
        // Clear 50Hz flag
        eDetectedStandardCurrent = E_VIDEOSTANDARD_NTSC_M;
        bVdIsReady = TRUE;
    }
  #endif


    //printf("m_eStandardDetectionState=%u\n", m_eStandardDetectionState);

    switch (m_eStandardDetectionState)
    {
        case E_DETECTION_START:
            DEBUG_VD_CHECK_STD( printf(" E_DETECTION_START:\n"); );
        #if 0//(CHAKRA3_AUTO_TEST)
            if(bPrintATInfo)
                printf("== E_DETECTION_START: ==\n");
        #endif
            m_eFSMDetectedStandard = eDetectedStandardCurrent;
            u8StdDetStableCnt = 0;
            m_eCurrentVideoStandard = E_VIDEOSTANDARD_NOTSTANDARD;
            DEBUG_VD_CHECK_STD( printf(" 0x%X, m_eFSMDetectedStandard=%u\n", u16VDStatus, m_eFSMDetectedStandard ); );

            if( bVdIsReady )
            {
                m_eStandardDetectionState = E_VD_STATE__UNSTABLE;
            }

            break;

        case E_VD_STATE__UNSTABLE:
            //printf("\r\n E_VD_STATE__UNSTABLE %d %d (%d)", m_eFSMDetectedStandard, eDetectedStandardCurrent, u8StdDetStableCnt);
            if( (m_eFSMDetectedStandard == eDetectedStandardCurrent)&&(bVdIsReady) )
            {
                MS_U16 u16DebounceValue;

                if ( m_eVideoSource == E_INPUT_SOURCE_ATV )
                {
                    if ( eDetectedStandardCurrent == E_VIDEOSTANDARD_NOTSTANDARD )
                    {
                        u16DebounceValue = VD_CHECK_STD_STABLE_THRESHOLD_ATV_CUR_NO_STD;
                    }
                    else if ( msAPI_Tuner_IsTuningProcessorBusy() )
                    {
                        u16DebounceValue = VD_CHECK_STD_STABLE_THRESHOLD_ATV_AUTO_SCAN;
                    }
                    else
                    {
                        u16DebounceValue = VD_CHECK_STD_STABLE_THRESHOLD_ATV_NORMAL;
                    }
                }
                else
                {
                    u16DebounceValue = VD_CHECK_STD_STABLE_THRESHOLD_CVBS;
                }

                u8StdDetStableCnt += 1;

                //printf("u8StdDetStableCnt=%u\n", u8StdDetStableCnt);
                if( (u8StdDetStableCnt >= u16DebounceValue) )
                {
                    //printf("[VD]u16DebounceValue=%u\n", u16DebounceValue);

                    printf("[VD] stable => %s(%u) at %u\n", msAPI_AVD_Get_StdString(m_eFSMDetectedStandard), m_eFSMDetectedStandard, g_Debug_u32Time_ChangeChannel);

                #if(CHAKRA3_AUTO_TEST)
                    AT_LOG("VD Stable");
                #endif

                #if(DEBUG_CHG_SRC_TIME)
                    //printf("VD-1 %u\n", g_Debug_u32Time_ChangeSrc);
                    msDebug_PrintChgSrcTime("VD Stable");
                #endif

                    SwitchChannelTimePrintf("[SwitchChannelTime][Pre]msAPI_AVD_SetVideoStandard(m_eFSMDetectedStandard); --- %ld\n");

                  #if (BRAZIL_CC)//ISDB Open PAL_NC CC
                    if(IS_SBTVD_APP)
                    {
                        if (E_VIDEOSTANDARD_PAL_N == m_eFSMDetectedStandard)
                        {
                            //msAPI_VBI_CC_DataRateSet(SIG_PAL_NC);
                            CC_SourceFuns.DataRateSet(E_VIDEOSTANDARD_PAL_N);
                        }
                        else
                        {
                            //msAPI_VBI_CC_DataRateSet(SIG_NTSC);
                            CC_SourceFuns.DataRateSet(E_VIDEOSTANDARD_NTSC_M);
                        }
                    }
                #endif

                    m_u16LatchStatus = u16VDStatus;
                    //printf("Set m_u16LatchStatus=0x%X\n", m_u16LatchStatus);
                    m_eCurrentVideoStandard = m_eFSMDetectedStandard;

                    msAPI_AVD_SetVideoStandard(m_eFSMDetectedStandard);
                    m_bIsVideoFormatChanged = TRUE;

                    m_eStandardDetectionState = E_VD_STATE__STABLE;
                    u8StdDetStableCnt = 0;
                }
            }
            else
            {
                //printf(" VD chg: %u -> %u\n", m_eFSMDetectedStandard, eDetectedStandardCurrent);
                m_eStandardDetectionState = E_DETECTION_START;
            }
            break;

        case E_VD_STATE__STABLE: // signal is stable
            //printf("\r\n E_VD_STATE__STABLE %d %d (%d)", m_eFSMDetectedStandard, eDetectedStandardCurrent, u8StdDetStableCnt);
            if( (m_eFSMDetectedStandard != eDetectedStandardCurrent)||(bVdIsReady==FALSE) )
            {
                U8 u8SignalChangeThreshold = VD_CHECK_STD_SIGNAL_CHANGE_THRESHOLD;

                DEBUG_AVD( printf("[VD] %s(%u) -> %s(%u) at %u\n",
                        msAPI_AVD_Get_StdString(m_eFSMDetectedStandard), m_eFSMDetectedStandard,
                        msAPI_AVD_Get_StdString(eDetectedStandardCurrent), eDetectedStandardCurrent,
                        g_Debug_u32Time_ChangeChannel
                        ) );

                if( msAPI_AVD_GetForceVideoStandardFlag() ) // When force mode enable
                {
                    // VD report std == force std
                    if( eDetectedStandardCurrent != E_VIDEOSTANDARD_NOTSTANDARD )
                    {
                        u8SignalChangeThreshold = VD_CHECK_STD_SIGNAL_CHANGE_THRESHOLD_FORCE_MODE;
                    }
                }

                u8StdDetStableCnt += 1;
                if( u8StdDetStableCnt >= u8SignalChangeThreshold )
                {
                    u8StdDetStableCnt = 0;
                    //printf("[VD]u8SignalChangeThreshold=%u, for=%u\n", u8SignalChangeThreshold,  msAPI_AVD_GetForceVideoStandardFlag());
                    DEBUG_AVD( printf("[VD] Std changed => %s(%u at %u\n",
                        msAPI_AVD_Get_StdString(eDetectedStandardCurrent),
                        eDetectedStandardCurrent, g_Debug_u32Time_ChangeChannel));

                    if( IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    {
                        //printf("\r\n VD standard changed main %d %d",m_eFSMDetectedStandard,eDetectedStandardCurrent);
                      #if (ENABLE_SW_CH_FREEZE_SCREEN)
                        bVideoStandardChanged = TRUE;
                      #else
                        msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, MAIN_WINDOW);
                      #endif
                    }

                    m_eStandardDetectionState = E_DETECTION_START;
                    m_eCurrentVideoStandard = E_VIDEOSTANDARD_NOTSTANDARD;
                }
            }
            else
            {
                u8StdDetStableCnt = 0;
              #if (ENABLE_SW_CH_FREEZE_SCREEN)
                bVideoStandardChanged = FALSE;
              #endif
            }
            break;

        default:
            m_eStandardDetectionState = E_DETECTION_START;
            break;
    }
}

#if 0
static void msAPI_AVD_CheckVideoSourceSwitch(void)
{
#if 0 //  MStar DVB Project does not use S-Video.
        if( m_eVideoSource == E_VIDEOSOURCE_SVIDEO1 )
        {
            m_bIsVideoInputChanged = TRUE;
            msAPI_AVD_SetVideoMuteDuringLimitedTime(DELAY_FOR_STABLE_VIDEO);
//            msAPI_AVD_SetVideoSource(vscCVBS1);
            msAPI_AVD_SetVideoSource(E_VIDEOSOURCE_SVIDEO1);
            msAPI_AVD_WaitForVideoSyncLock();
            msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
            msAPI_TTX_ResetAcquisition();
        }
        if( m_eVideoSource == E_VIDEOSOURCE_CVBS1 )
        {
            m_bIsVideoInputChanged = TRUE;
            msAPI_AVD_SetVideoMuteDuringLimitedTime(DELAY_FOR_STABLE_VIDEO);
//            msAPI_AVD_SetVideoSource(vscSVIDEO1);
            msAPI_AVD_SetVideoSource(E_VIDEOSOURCE_CVBS1);
            msAPI_AVD_WaitForVideoSyncLock();
            msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
            msAPI_TTX_ResetAcquisition();
        }

/*
    if( m_eVideoSource == E_VIDEOSOURCE_CVBS1 || m_eVideoSource == E_VIDEOSOURCE_SVIDEO1 )
    {
        if( TRUE == IS_SVIDEO_CONNECTED )
        {
            if( m_eVideoSource == E_VIDEOSOURCE_SVIDEO1 )
            {
                m_bIsVideoInputChanged = TRUE;
                msAPI_AVD_SetVideoMuteDuringLimitedTime(DELAY_FOR_STABLE_VIDEO);
                msAPI_AVD_SetVideoSource(E_VIDEOSOURCE_CVBS1);
                msAPI_AVD_WaitForVideoSyncLock();
                msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
                msAPI_TTX_ResetAcquisition();
            }
        }
        else
        {
            if( m_eVideoSource == E_VIDEOSOURCE_CVBS1 )
            {
                m_bIsVideoInputChanged = TRUE;
                msAPI_AVD_SetVideoMuteDuringLimitedTime(DELAY_FOR_STABLE_VIDEO);
                msAPI_AVD_SetVideoSource(E_VIDEOSOURCE_SVIDEO1);
                msAPI_AVD_WaitForVideoSyncLock();
                msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
                msAPI_TTX_ResetAcquisition();
            }
        }
    }
*/
#endif
}
#endif

static void msAPI_AVD_CheckAspectRatio(void)
{
#if(INPUT_SCART_VIDEO_COUNT>0)
    U16 cCurrentScart1ID;
    U16 cCurrentScart2ID;
#endif

    ASPECT_RATIO_TYPE eAspectRatioCode;

    if( IS_WSS_ENABLED == FALSE )
    {
        return;
    }

#if ENABLE_TTX
    eAspectRatioCode = msAPI_AVD_GetAspectRatioCodeOfWSS();
#else
    eAspectRatioCode = ARC_INVALID;
#endif

    DEBUG_AVD( printf("Old=%u, Cur ARCode=%u\n", m_eAspectRatioCode, eAspectRatioCode); );

#if(INPUT_SCART_VIDEO_COUNT>0)
    if( eAspectRatioCode == ARC_INVALID )
    {
        if( (m_eVideoSource == E_INPUT_SOURCE_ATV && m_bIsAutoAV2Active == TRUE)
         || ( m_eVideoSource == E_INPUT_SOURCE_SCART2)
          )
        {
            cCurrentScart2ID = GetScart2IDLevel();

            DEBUG_AVD(printf("@@@ Scart2IDLevel = %d\n", cCurrentScart2ID);)

            if( SCART_4_3_LEVEL < cCurrentScart2ID )        // Level 1B: +9.5V to +12V
            {
                eAspectRatioCode = ARC4x3_FULL;
            }
            else if ( SCART_16_9_LEVEL < cCurrentScart2ID )    // Level 1A: +4.5V to +7V
            {
                eAspectRatioCode = ARC16x9_ANAMORPHIC;
            }
            else                                            // Level 0: 0V to 2V
            {
                eAspectRatioCode = ARC_INVALID;// need touch. I should check whether this is correct or not.
            }
        }
        else if( (m_eVideoSource == E_INPUT_SOURCE_ATV && m_bIsAutoAV1Active == TRUE)
              || (m_eVideoSource == E_INPUT_SOURCE_SCART1)
               )
        {
            cCurrentScart1ID = GetScart1IDLevel();

            DEBUG_AVD( printf("@@@ Scart1IDLevel = %d\n", cCurrentScart1ID); );

            if( cCurrentScart1ID > SCART_4_3_LEVEL )        // Level 1B: +9.5V to +12V
            {
                eAspectRatioCode = ARC4x3_FULL;
            }
            else if ( cCurrentScart1ID > SCART_16_9_LEVEL )    // Level 1A: +4.5V to +7V
            {
                eAspectRatioCode = ARC16x9_ANAMORPHIC;
            }
            else                                            // Level 0: 0V to 2V
            {
                eAspectRatioCode = ARC_INVALID;// need touch. I should check whether this is correct or not.
            }
        }
    }
#endif

    if( m_eAspectRatioCode != eAspectRatioCode )
    {
        DEBUG_AVD( printf("AR change: %u -> %u\n", m_eAspectRatioCode, eAspectRatioCode ); );

        if( eAspectRatioCode != ARC_INVALID )
        {
            //PRINT_CURRENT_LINE();
            m_bIsAspectRatioChanged = TRUE;
        }

        m_eAspectRatioCode = eAspectRatioCode;
    }
}

#if(INPUT_SCART_VIDEO_COUNT>0)
static void msAPI_AVD_CheckAutoAV(void)
{
    if( FALSE == IS_SCART_ENABLED )
    {
        return;
    }

    if( TRUE == msAPI_AVD_UpdateAutoAVState() )
    {
        if( E_INPUT_SOURCE_ATV != m_eVideoSource )
        {
            return;
        }
        //printf("[msAPI_AVD_CheckAutoAV]\n");
        msAPI_AVD_SwitchAutoAV();
    }
}
#endif

#if 0
static void msAPI_AVD_TurnOnAutoAV(void)
{
    if( FALSE == IS_SCART_ENABLED )
        return;

    if( m_bIsAutoAV2Active == TRUE )
    {
        MDrv_AVD_SetInput(E_INPUT_SOURCE_SCART2,(U8)INPUT_SCART_FB_MUX);
    }
    else if( m_bIsAutoAV1Active == TRUE )
    {
        MDrv_AVD_SetInput(E_INPUT_SOURCE_SCART1,(U8)INPUT_SCART_FB_MUX);
    }

    m_bIs3DCombfilterUsed = FALSE;

    msAPI_AVD_WaitForVideoSyncLock();

#if ENABLE_TTX
    msAPI_TTX_ResetAcquisition();
#endif
    msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);

}
#endif

#if 0
static void msAPI_AVD_PriTurnOffAutoAV(void)
{
    AUDIOMODE_TYPE    eAudioMode;

    //if( FALSE == IS_SCART_ENABLED )
        return;
    msAPI_AVD_SetMuxPower(E_VIDEOSOURCE_ATV);
    MDrv_VD_SetInput(E_INPUT_SOURCE_ATV,(U8)INPUT_SCART_FB_MUX);
    m_bIs3DCombfilterUsed = FALSE;

    msAPI_AVD_WaitForVideoSyncLock();
#if ENABLE_TTX
    msAPI_TTX_ResetAcquisition();
#endif
    msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);

}
#endif

#if( !ENABLE_SCART_MONITOR )
static void msAPI_AVD_RetrieveScart1SourceType(void)
{
    SCART_SOURCE_TYPE ePreviousScart1SrcType;

    ePreviousScart1SrcType = VDScart1SrcType;

    if( m_eVideoSource == E_INPUT_SOURCE_SCART1 ||
        (m_eVideoSource == E_INPUT_SOURCE_ATV && m_bIsAutoAV1Active == TRUE) )
    {
        if ( TRUE == msAPI_AVD_IsScartRGB() )
        {
            printf("S1 -> RGB\n");
            VDScart1SrcType = E_SCART_SRC_TYPE_RGB;
        }
        else
        {
            printf("S1 -> CVBS\n");
            VDScart1SrcType = E_SCART_SRC_TYPE_CVBS;
        }

        if ( ePreviousScart1SrcType != E_SCART_SRC_TYPE_UNKNOWN &&
             ePreviousScart1SrcType != VDScart1SrcType )
        {
            //printf("Set m_bIsScart1SourceTypeChanged=1\n");
            m_bIsScart1SourceTypeChanged = TRUE;
        }
    }
    else
    {
        printf("S1 -> unknown\n");
        VDScart1SrcType = E_SCART_SRC_TYPE_UNKNOWN;
    }
}
#endif

BOOLEAN msAPI_AVD_IsScartRGB(void)
{
    return IsScartRGB();
}

#if(PQ_ENABLE_VD_SAMPLING)
void msAPI_AVD_GetCaptureWindowByPQ(MS_WINDOW_TYPE *stCapWin, EN_VD_SIGNALTYPE enVideoSystem, MS_PQ_VD_Sampling_Info *pInfo)
{
    //printf("msAPI_AVD_GetCaptureWindowByPQ(enVideoSystem=%u)\n", enVideoSystem);

    if( pInfo->eType == PQ_VD_SAMPLING_ON )
    {
        //printf("!from pq!\n");
        stCapWin->x = pInfo->u16Hstart;
        stCapWin->y = pInfo->u16Vstart;
        stCapWin->width = pInfo->u16Hsize;
        stCapWin->height = pInfo->u16Vsize;
    }
    else
    {
        memcpy(stCapWin, &VideoCaptureWinTbl[enVideoSystem], sizeof(MS_WINDOW_TYPE));
    }

    //printf("AVD Get Capture: sd=%d, Sample=%d, x:%x y:%x w:%d h:%d\n", enVideoSystem, pInfo->eType, stCapWin->x, stCapWin->y, stCapWin->width, stCapWin->height);
}
#endif

void msAPI_AVD_GetCaptureWindow(MS_WINDOW_TYPE *stCapWin, EN_VD_SIGNALTYPE enVideoSystem, MS_BOOL IsUseExtVD)
{
    if(IsUseExtVD)
    {
        memcpy(stCapWin, &ExtVDVideoCapture[enVideoSystem], sizeof(MS_WINDOW_TYPE));
    }
    else
    {
        memcpy(stCapWin, &VideoCaptureWinTbl[enVideoSystem], sizeof(MS_WINDOW_TYPE));
        #if 0 // TODO, add externsion function
        switch (enVideoSystem) // for future extension
        {
            case SIG_NTSC:
                MDrv_AVD_GetCaptureWindow(stCapWin, E_VIDEOSTANDARD_NTSC_M);
                break;
            case SIG_PAL:
                MDrv_AVD_GetCaptureWindow(stCapWin, E_VIDEOSTANDARD_PAL_BGHI);
                break;
            case SIG_SECAM:
                MDrv_AVD_GetCaptureWindow(stCapWin, E_VIDEOSTANDARD_SECAM);
                break;
            case SIG_NTSC_443:
                MDrv_AVD_GetCaptureWindow(stCapWin, E_VIDEOSTANDARD_NTSC_44);
                break;
            case SIG_PAL_M:
                MDrv_AVD_GetCaptureWindow(stCapWin, E_VIDEOSTANDARD_PAL_M);
                break;
            case SIG_PAL_NC:
                MDrv_AVD_GetCaptureWindow(stCapWin, E_VIDEOSTANDARD_PAL_N);
                break;
            default:
                MDrv_AVD_GetCaptureWindow(stCapWin, E_VIDEOSTANDARD_PAL_BGHI);
                break;
        }
        #endif
    }
    //printf("msAPI_AVD_GetCaptureWindow %x %x %d %d\n", stCapWin->x, stCapWin->y, stCapWin->width, stCapWin->height);
}

//VD
static EN_VD_SIGNALTYPE g_ucVideoSystem;

EN_VD_SIGNALTYPE mvideo_vd_get_videosystem(void)
{
    return g_ucVideoSystem;
}

void mvideo_vd_set_videosystem(EN_VD_SIGNALTYPE ucVideoSystem)
{
    //printf("mvideo_vd_set_videosystem(ucVideoSystem=%u)\n", ucVideoSystem);
    g_ucVideoSystem = ucVideoSystem;
}

U16 msAPI_AVD_Get_LatchStatus(void)
{
    return m_u16LatchStatus;
}

//BOOLEAN IsVDHasSignal(void)
BOOLEAN msAPI_AVD_IsHasStableSignal(void)
{
    return (m_eCurrentVideoStandard != E_VIDEOSTANDARD_NOTSTANDARD);
}

/******************************************************************************/
///This function will return VD's Horizontal period
///@param enGetSyncType \b IN
///EN_GET_SYNC_TYPE is SYNC type
///-GET_SYNC_DIRECTLY
///-GET_SYNC_STABLE
///-GET_SYNC_VIRTUAL
///@return
///- U16 VD Horizontal Period
/******************************************************************************/
U16 msAPI_Scaler_VD_GetHPeriod (SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t eCurrentSrc,EN_GET_SYNC_TYPE enGetSyncType)
{
    U8 u8StableCounter;
    XC_IP_SYNC_STATUS sXC_SyncStatus;

    switch(enGetSyncType)
    {
        default:
        case GET_SYNC_DIRECTLY:
            MApi_XC_GetSyncStatus(eCurrentSrc, &sXC_SyncStatus, eWindow);
            break;
        case GET_SYNC_STABLE:
        case GET_SYNC_VIRTUAL:
            for(u8StableCounter = 0 ; u8StableCounter < 5 ; u8StableCounter++)
            {
                MApi_XC_GetSyncStatus(eCurrentSrc, &sXC_SyncStatus, eWindow);
                if( (MApi_XC_CalculateHFreqx10(sXC_SyncStatus.u16Hperiod) >= 135) &&
                    (MApi_XC_CalculateHFreqx10(sXC_SyncStatus.u16Hperiod) <= 178) )
                {
                    break;
                }
                else
                {
                    if(enGetSyncType==GET_SYNC_VIRTUAL)
                        sXC_SyncStatus.u16Hperiod = 0;
                }
            }
            if((enGetSyncType == GET_SYNC_VIRTUAL) && (sXC_SyncStatus.u16Hperiod == 0))
            {
                if(sXC_SyncStatus.u16Vtotal > 566)
                    sXC_SyncStatus.u16Hperiod = MST_XTAL_CLOCK_HZ/15625;
                else
                    sXC_SyncStatus.u16Hperiod = MST_XTAL_CLOCK_HZ/15734;
            }
            break;
    }
    return sXC_SyncStatus.u16Hperiod;
}

/******************************************************************************/
///This function will return VD's Vertical total
///@param enGetSyncType \b IN
///enGetSyncType is SYNC type
///- GET_SYNC_DIRECTLY
///- GET_SYNC_STABLE
///- GET_SYNC_VIRTUAL
///@param u16HFreqX10 \b IN
///- Horizontal frequncy
///@return
///- U16: VD Vertical Total
/******************************************************************************/
U16 msAPI_Scaler_VD_GetVTotal (SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t eCurrentSrc,EN_GET_SYNC_TYPE enGetSyncType, U16 u16HFreqX10)
{
    U8 u8StableCounter = 0;
    XC_IP_SYNC_STATUS sXC_Sync_Status;

    switch(enGetSyncType)
    {
        default:
        case GET_SYNC_DIRECTLY:
            MApi_XC_GetSyncStatus(eCurrentSrc, &sXC_Sync_Status, eWindow);
            break;

        case GET_SYNC_STABLE:
        case GET_SYNC_VIRTUAL:
            for(u8StableCounter = 0 ; u8StableCounter < 3 ; u8StableCounter++)
            {
                MApi_XC_GetSyncStatus(eCurrentSrc, &sXC_Sync_Status, eWindow);
                //printf("XC VT=%u\n", sXC_Sync_Status.u16Vtotal);
                if(sXC_Sync_Status.u16Vtotal >= 465 && sXC_Sync_Status.u16Vtotal <= 730)//+-7Hz if(u16VerticalTotal >= 510 && u16VerticalTotal <= 640)
                {
                    break;
                }
                else
                {
                    if(enGetSyncType==GET_SYNC_VIRTUAL)
                        sXC_Sync_Status.u16Vtotal = 0;
                }
            }
            if(enGetSyncType==GET_SYNC_VIRTUAL && sXC_Sync_Status.u16Vtotal==0)
            {
                if(u16HFreqX10 == 156)
                    sXC_Sync_Status.u16Vtotal = 625;
                else
                    sXC_Sync_Status.u16Vtotal = 525;
            }
            break;
    }

    return sXC_Sync_Status.u16Vtotal;
}

#if (TV_FREQ_SHIFT_CLOCK)
void msAPI_AVD_ShiftClk(AVD_ATV_CLK_TYPE eShiftMode)
{
     MDrv_AVD_SetShiftClk(ENABLE,eShiftMode);
}
#endif

const char* msAPI_AVD_Get_StdString(AVD_VideoStandardType eVDStd)
{
    char* pcStr;

    switch(eVDStd)
    {
        default:
            pcStr = "Unknown";
            break;
        case E_VIDEOSTANDARD_PAL_BGHI:
            pcStr = "PAL";
            break;
        case E_VIDEOSTANDARD_NTSC_M:
            pcStr = "NTSC";
            break;
        case E_VIDEOSTANDARD_SECAM:
            pcStr = "SECAM";
            break;
        case E_VIDEOSTANDARD_NTSC_44:
            pcStr = "NTSC443";
            break;
        case E_VIDEOSTANDARD_PAL_M:
            pcStr = "PAL_M";
            break;
        case E_VIDEOSTANDARD_PAL_N:
            pcStr = "PAL_N";
            break;
        case E_VIDEOSTANDARD_PAL_60:
            pcStr = "PAL_60";
            break;
        case E_VIDEOSTANDARD_NOTSTANDARD:
            pcStr = "NO SYNC";
            break;
        case E_VIDEOSTANDARD_AUTO:
            pcStr = "AUTO";
            break;
    }

    return pcStr;
}

BOOL msAPI_AVD_Is_Input50Hz(void)
{
    if( m_u16LatchStatus&VD_VSYNC_50HZ )
    {
        //printf("m_u16LatchStatus=0%X\n", m_u16LatchStatus);
        return TRUE;
    }
    else
        return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// Get video decoder status
/// VD_SYNC_LOCKED                  ((BIT(15)))\n
/// VD_HSYNC_LOCKED                 ((BIT(14)))\n
/// VD_INTERLACED                   ((BIT(13)))\n
/// VD_VSYNC_50HZ                   ((BIT(12)))\n
/// VD_RESET_ON                     ((BIT(11)))\n
/// VD_COLOR_LOCKED                 ((BIT(10)))\n
/// VD_PAL_SWITCH                   ((BIT(9)))\n
/// VD_FSC_TYPE                     ((BIT(7))|(BIT(6))|(BIT(5)))\n
/// VD_FSC_3579                     ((BIT(6)))              // NTSC\n
/// VD_FSC_3575                     ((BIT(7)))              // PAL(M)\n
/// VD_FSC_3582                     ((BIT(7))|(BIT(6)))         // PAL(Nc)\n
/// VD_FSC_4433                     (0)                 // PAL or NTSC443\n
/// VD_FSC_4285                     (BIT(5))              // SECAM\n
/// VD_VCR_MODE                     (BIT(4))\n
/// VD_VCR_PAUSE                    (BIT(3))\n
/// VD_MACROVISION                  (BIT(2))\n
/// VD_BURST_ON                        (BIT(1))\n
/// VD_STATUS_RDY                   (BIT(0))\n
////////////////////////////////////////////////////////////////////////////////
void msAPI_AVD_PrintInfo(void)
{
    AVD_VideoStandardType eCurVdStd;
    U16 u16VdStatus;
    U16 u16VdVTotal;
    AVD_VideoFreq eVdVFreq;


    printf("VD info:\n");

    printf(" m_eStandardDetectionState=%u\n", m_eStandardDetectionState);
    printf(" u8StdDetStableCnt=%u\n", u8StdDetStableCnt);

    printf(" m_eFSMDetectedStandard=%u\n", m_eFSMDetectedStandard);
    printf(" m_eCurrentVideoStandard=%u\n", m_eCurrentVideoStandard);
    printf(" m_u16LatchStatus=0x%X\n", m_u16LatchStatus);
    printf(" msAPI_AVD_GetVideoStandard()=%u\n", msAPI_AVD_GetVideoStandard());



    eCurVdStd = MDrv_AVD_GetStandardDetection(&u16VdStatus);
    u16VdVTotal = MDrv_AVD_GetVTotal();
    eVdVFreq = MDrv_AVD_GetVerticalFreq();

    printf(" u16VdStatus=0x%X, curStatus=0x%X\n", u16VdStatus, MDrv_AVD_GetStatus());

    printf(" eCurVdStd=%u\n", eCurVdStd);
    printf(" u16VdVTotal=%u\n", u16VdVTotal);


    if( u16VdStatus&VD_STATUS_RDY )
    {
        printf(" | VD_STATUS_RDY");
    }
    if( u16VdStatus&VD_HSYNC_LOCKED )
    {
        printf(" | VD_HSYNC_LOCKED");
    }
    if( u16VdStatus&VD_SYNC_LOCKED )
    {
        printf(" | VD_SYNC_LOCKED");
    }

    if( u16VdStatus&VD_VSYNC_50HZ )
    {
        printf(" | VD_VSYNC_50HZ");
    }
    if( u16VdStatus&VD_BURST_ON )
    {
        printf(" | VD_BURST_ON");
    }
    if( u16VdStatus&VD_COLOR_LOCKED )
    {
        printf(" | VD_COLOR_LOCKED");
    }
    if( u16VdStatus&VD_PAL_SWITCH )
    {
        printf(" | VD_PAL_SWITCH");
    }
    printf("\n");

  #if 0
    // Scaler
    {
        XC_IP_SYNC_STATUS sXC_SyncStatus;

        MApi_XC_GetSyncStatus(stSystemInfo[MAIN_WINDOW].enInputSourceType,
            &sXC_SyncStatus, MAIN_WINDOW);

    }
  #endif

    printf("\n");
}



#undef _MSAPI_VD_C_

