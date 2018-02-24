///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   Mapi_combo.h
/// @author MStar Semiconductor Inc.
/// @brief  MHL driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MAPI_COMBO_H_
#define _MAPI_COMBO_H_

#include "combo_config.h"

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define COMBO_IP_MASK_PORT0             BIT0
#define COMBO_IP_MASK_PORT1             BIT1
#define COMBO_IP_MASK_PORT2             BIT2
#define COMBO_IP_MASK_PORT3             BIT3
#define COMBO_IP_MASK_PORT4             BIT4
#define COMBO_IP_MASK_PORT5             BIT5
#define COMBO_IP_MASK_VGA               BIT6

#define SET_COMBO_IP_PARAMETER(a,b)     (a |= b)
#define CLR_COMBO_IP_PARAMETER(a,b)     (a &= (~b))

#define COMBO_HDCP_KEY_SIZE             284
#define COMBO_HDCP_BKSV_SIZE            5

#define COMBO_DP_DC_SUPPORT_INDEX_L     (COMBO_DP_DC_SUPPORT_PORT0| (COMBO_DP_DC_SUPPORT_PORT1 <<1)| (COMBO_DP_DC_SUPPORT_PORT2 <<2))
#define COMBO_DP_DC_SUPPORT_INDEX_H     (COMBO_DP_DC_SUPPORT_PORT3| (COMBO_DP_DC_SUPPORT_PORT4 <<1)| (COMBO_DP_DC_SUPPORT_PORT5 <<2))
#define COMBO_DP_DC_SUPPORT_INDEX       (COMBO_DP_DC_SUPPORT_INDEX_L| (COMBO_DP_DC_SUPPORT_INDEX_H <<3))

#define COMBO_DAISY_CHAIN_EDID_PORT     COMBO_DAISY_CHAIN_PORT_SELECT

#define COMBO_DEBUG_MESSAGE             (ENABLE_MSTV_UART_DEBUG)

#define COMBO_HDCP2_AKE_CERTRX_SIZE     522

#define COMBO_HDCP2_ENCODE_KEY_SIZE     1044

#define COMBO_HDCP2_EXTERNAL_KEY_ENABLE_SIZE 1
#define COMBO_HDCP2_SECURE_STORM_KEY    16

typedef enum
{
    COMBO_IP_SELECT_VGA = 0,
    COMBO_IP_SELECT_PORT0,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_1PORT)
    COMBO_IP_SELECT_PORT_END,
#endif
    COMBO_IP_SELECT_PORT1,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_2PORT)
    COMBO_IP_SELECT_PORT_END,
#endif
    COMBO_IP_SELECT_PORT2,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_3PORT)
    COMBO_IP_SELECT_PORT_END,
#endif
    COMBO_IP_SELECT_PORT3,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_4PORT)
    COMBO_IP_SELECT_PORT_END,
#endif
    COMBO_IP_SELECT_PORT4,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_5PORT)
    COMBO_IP_SELECT_PORT_END,
#endif
    COMBO_IP_SELECT_PORT5,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_6PORT)
    COMBO_IP_SELECT_PORT_END,
#endif
    COMBO_IP_SELECT_MASK = COMBO_IP_SELECT_PORT_END,
}EN_COMBO_IP_SELECT;

enum COMBO_INPUT_SELECT_TYPE
{
    COMBO_INPUT_SELECT_PORT0 = 0,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_1PORT)
    COMBO_INPUT_SELECT_PORT_END,
#endif
    COMBO_INPUT_SELECT_PORT1,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_2PORT)
    COMBO_INPUT_SELECT_PORT_END,
#endif
    COMBO_INPUT_SELECT_PORT2,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_3PORT)
    COMBO_INPUT_SELECT_PORT_END,
#endif
    COMBO_INPUT_SELECT_PORT3,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_4PORT)
    COMBO_INPUT_SELECT_PORT_END,
#endif
    COMBO_INPUT_SELECT_PORT4,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_5PORT)
    COMBO_INPUT_SELECT_PORT_END,
#endif
    COMBO_INPUT_SELECT_PORT5,
#if(COMBO_IP_SUPPORT_TYPE == COMBO_IP_SUPPORT_6PORT)
    COMBO_INPUT_SELECT_PORT_END,
#endif
    COMBO_INPUT_SELECT_MASK = COMBO_INPUT_SELECT_PORT_END,
    COMBO_INPUT_SELECT_VGA = COMBO_INPUT_SELECT_MASK,
};

typedef enum
{
    COMBO_IP_TYPE_DVI = 0,
    COMBO_IP_TYPE_DUAL,
    COMBO_IP_TYPE_HDMI,
    COMBO_IP_TYPE_MHL,
    COMBO_IP_TYPE_DP,
    COMBO_IP_TYPE_VGA,
}EN_COMBO_IP_TYPE;

typedef enum
{
    COMBO_IP_CABLE_NONE = 0,
    COMBO_IP_CABLE_DVI,
    COMBO_IP_CABLE_HDMI,
    COMBO_IP_CABLE_MHL,
    COMBO_IP_CABLE_DP,
}EN_COMBO_IP_CABLE;

typedef enum
{
    COMBO_COLOR_FORMAT_RGB         = 0,     ///< HDMI RGB 444 Color Format
    COMBO_COLOR_FORMAT_YUV_422     = 1,     ///< HDMI YUV 422 Color Format
    COMBO_COLOR_FORMAT_YUV_444     = 2,     ///< HDMI YUV 444 Color Format
    COMBO_COLOR_FORMAT_YUV_420     = 3,     ///< HDMI YUV 420 Color Format
    COMBO_COLOR_FORMAT_RESERVED    = 4,     ///< Reserve
    COMBO_COLOR_FORMAT_DEFAULT     = COMBO_COLOR_FORMAT_RGB,///< Default setting
    COMBO_COLOR_FORMAT_UNKNOWN     = 15,    ///< Unknow Color Format
}EN_COLOR_FORMAT_TYPE;

typedef enum
{
    COMBO_COLORIMETRY_xvYCC601    = 0,    ///< HDMI xvYCC601 Colorimetry
    COMBO_COLORIMETRY_xvYCC709    = 1,    ///< HDMI xvYCC709 Colorimetry
    COMBO_COLORIMETRY_sYCC601     = 2,    ///< HDMI sYCC601 colorimetry
    COMBO_COLORIMETRY_ADOBEYCC601 = 3,    ///< HDMI Adobe YCC 601 colorimetry
    COMBO_COLORIMETRY_ADOBERBG    = 4,    ///< HDMI Adobe RGB colorimetry
    COMBO_COLORIMETRY_NONE        = 15,
}EN_COLORIMETRY_TYPE;

typedef enum
{
    COMBO_COLOR_RANGE_DEFAULT    = 0, //depend on video format;
    COMBO_COLOR_RANGE_LIMIT      = 1,
    COMBO_COLOR_RANGE_FULL       = 2,
    COMBO_COLOR_RANGE_RESERVED   = 3,
}EN_COLOR_RANGE_TYPE;

typedef enum
{
    COMBO_YUV_COLORIMETRY_ITU601=0,
    COMBO_YUV_COLORIMETRY_ITU709,
    COMBO_YUV_COLORIMETRY_NoData,
    COMBO_YUV_COLORIMETRY_Max
} EN_YPBPR_COLORIMETRY_TYPE;

typedef enum
{
    COMBO_COLOR_DEPTH_6BIT       = 0,
    COMBO_COLOR_DEPTH_8BIT       = 1,
    COMBO_COLOR_DEPTH_10BIT      = 2,
    COMBO_COLOR_DEPTH_12BIT      = 3,
    COMBO_COLOR_DEPTH_16BIT      = 4,
    COMBO_COLOR_DEPTH_UNKNOW     = 5,
}EN_COLOR_DEPTH_TYPE;

typedef enum
{
    COMBO_PACKET_NULL                       = 0x00, //depend on video format;
    COMBO_PACKET_AUDIO_CLOCK_REGENERATION   = 0x01,
    COMBO_PACKET_AUDIO_SAMPLE               = 0x02,
    COMBO_PACKET_GENERAL_CONTROL            = 0x03,
    COMBO_PACKET_ACP_PACKET                 = 0x04,
    COMBO_PACKET_ISRC1_PACKET               = 0x05,
    COMBO_PACKET_ISRC2_PACKET               = 0x06,
    COMBO_PACKET_ONE_BIT_AUDIO_SAMPLE       = 0x07,
    COMBO_PACKET_DST_AUDIO                  = 0x08,
    COMBO_PACKET_HBR_AUDIO_STREAM           = 0x09,
    COMBO_PACKET_GAMUT_METADATA             = 0x0A,
    COMBO_PACKET_VS_INFOFRAME               = 0x81,
    COMBO_PACKET_AVI_INFOFRAME              = 0x82,
    COMBO_PACKET_SPD_INFOFRAME              = 0x83,
    COMBO_PACKET_AUD_INFOFRAME              = 0x84,
    COMBO_PACKET_MPEG_INFOFRAME             = 0x85,
    COMBO_PACKET_DP_MISC                    = 0xFF,
}EN_PACKET_DEFINE_TYPE;

typedef enum
{
    COMBO_SW_RESET_NONE                 = 0,
    COMBO_SW_RESET_WORD_BOUNDARY        = BIT0,
    COMBO_SW_RESET_DP_DECODER           = BIT1,
    COMBO_SW_RESET_DVI_DECODER          = BIT2,
    COMBO_SW_RESET_MHL_AUTO_EQ          = BIT3,
    COMBO_SW_RESET_HDCP                 = BIT4,
    COMBO_SW_RESET_DVI2MUI              = BIT5,
    COMBO_SW_RESET_HDMI                 = BIT6,
    COMBO_SW_RESET_DVI_MSIC             = BIT7,
    COMBO_SW_RESET_DP_RX_SYNTHESIZER    = BIT8,
    COMBO_SW_RESET_DP_LINK_QUALITY      = BIT9,
    COMBO_SW_RESET_CLOCK_GENERATOR      = BIT10,
    COMBO_SW_RESET_DP_VPLL              = BIT11,
    COMBO_SW_RESET_DITHER               = BIT12,
    COMBO_SW_RESET_VIDEO_OUTPUT         = BIT13,
    COMBO_SW_RESET_AVG_FIFO             = BIT14,
    COMBO_SW_RESET_DP_FAST_TRAINING     = BIT15,
    COMBO_SW_RESET_DP_UNPACK            = BIT16,
    COMBO_SW_RESET_ALL                  = BIT17,
}EN_IP_SW_RESET_TYPE;

typedef enum
{
    COMBO_TMDS_N0_PIX_REP = 0,
    COMBO_TMDS_2x_PIX_REP = 1,
    COMBO_TMDS_3x_PIX_REP = 2,
    COMBO_TMDS_4x_PIX_REP = 3,
    COMBO_TMDS_5x_PIX_REP = 4,
    COMBO_TMDS_6x_PIX_REP = 5,
    COMBO_TMDS_7x_PIX_REP = 6,
    COMBO_TMDS_8x_PIX_REP = 7,
    COMBO_TMDS_9x_PIX_REP = 8,
    COMBO_TMDS_10x_PIX_REP = 9,
    COMBO_TMDS_RESERVED_PIX_REP = 10,
} EN_TMDS_PIXEL_REPETITION;

typedef enum
{
    COMBO_TMDS_AUD_FREQ_32K       = 32,
    COMBO_TMDS_AUD_FREQ_44K       = 44,
    COMBO_TMDS_AUD_FREQ_48K       = 48,
    COMBO_TMDS_AUD_FREQ_88K       = 88,
    COMBO_TMDS_AUD_FREQ_96K       = 96,
    COMBO_TMDS_AUD_FREQ_176K      = 176,
    COMBO_TMDS_AUD_FREQ_192K      = 192,
    COMBO_TMDS_AUD_FREQ_ERROR     = 0,

} EN_TMDS_AUD_FREQ_INDEX;

typedef enum
{
    COMBO_AUDIO_FMT_NON_PCM   = 0,
    COMBO_AUDIO_FMT_PCM       = 1,
    COMBO_AUDIO_FMT_UNKNOWN   = 2,
} EN_TMDS_AUDIO_FORMAT;

typedef enum
{
    COMBO_TMDS_MONO_8_BIT  = 0,
    COMBO_TMDS_MONO_10_BIT = 1,
    COMBO_TMDS_MONO_12_BIT = 2,
} EN_TMDS_MONO_BIT;

typedef enum
{
    COMBO_TMDS_DVI_DEEP_COLOR_8_BIT  = 0,
    COMBO_TMDS_DVI_DEEP_COLOR_10_BIT = 1,
    COMBO_TMDS_DVI_DEEP_COLOR_12_BIT = 2,
    COMBO_TMDS_DVI_DEEP_COLOR_16_BIT = 3,
} EN_TMDS_DVI_DEEP_COLOR;

typedef enum
{
    COMBO_HDMI_VERSION_NOT_SURE = 0,
    COMBO_HDMI_VERSION_HDMI14,
    COMBO_HDMI_VERSION_HDMI20,
}EN_HDMI_VERSION_TYPE;

typedef struct
{
    Bool bConfigFinish;
    Bool bVGAEnableIndex;
    Bool bComboPowerIgnore;
    BYTE ucDVIEnableIndex;
    BYTE ucHDMIEnableIndex;
    BYTE ucHDMI2EnableIndex;
    BYTE ucDualEnableIndex;
    BYTE ucDPEnableIndex;
    BYTE ucHBR20EnableIndex;
    BYTE ucHBR21EnableIndex;
    BYTE ucMHLEnableIndex;
    BYTE ucDaisyEnableIndex;
    BYTE ucDisplayEnableIndex;
}ST_COMBO_IP_PARAMETER;

typedef struct
{
    EN_COLOR_FORMAT_TYPE        ucColorType;
    EN_COLOR_RANGE_TYPE         ucColorRange;
    EN_COLORIMETRY_TYPE         ucColorimetry;
    EN_YPBPR_COLORIMETRY_TYPE   ucYuvColorimetry;
}ST_COMBO_COLOR_FORMAT;

typedef enum
{
    COMBO_IP_POWER_NONE = 0,
    COMBO_IP_POWER_AC_ON,
    COMBO_IP_POWER_DC_ON,
    COMBO_IP_POWER_PS_ON,
    COMBO_IP_POWER_DC_OFF,
    COMBO_IP_POWER_POWER_SAVING,
}EN_COMBO_POWER_STATUS;

typedef enum
{
    COMBO_TMDS_AUDIO_STATE_OFF = 0,
    COMBO_TMDS_AUDIO_STATE_ON = 1,
} EN_TMDS_AUD_STATUS;

#if 0 // No DP in U11
typedef enum
{
    COMBO_DP_VERSION_11 = 0,
	COMBO_DP_VERSION_12,
	#if ENABLE_DAISY_CHAIN
	COMBO_DP_VERSION_12MST,
	#endif
	COMBO_DP_VERSION_UNKNOW,
} EN_DP_VERSION;
#endif

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
#if 0
void msAPI_combo_IPSetPowerStatus(EN_COMBO_POWER_STATUS ucComboPowerStatus);
void msAPI_combo_IPConfiguration(Bool bDisplayEnable, EN_COMBO_IP_SELECT ucComboSelect, EN_INPUTPORT_TYPE ucComboType);
void msAPI_combo_IPPMIsrHandler(void);
void msAPI_combo_IPIsrHandler(InterruptNum eIntNum);
void msAPI_combo_IPInitial(void);
#endif
void msAPI_combo_IPHandler(void);
#if 0
void msAPI_combo_IPTimerIsrHandler(void);
ST_COMBO_COLOR_FORMAT msAPI_combo_IPGetColorFormat(EN_COMBO_IP_SELECT ucComboSelect);
EN_COLOR_DEPTH_TYPE msAPI_combo_IPGetColorDepth(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPGetPacketContent(EN_COMBO_IP_SELECT ucComboSelect, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData);
EN_COMBO_IP_CABLE msAPI_combo_IPGetCableDetect(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPCheckSourceAlive(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPControlHPD(EN_COMBO_IP_SELECT ucComboSelect, Bool bSetHPD);
void msAPI_combo_IPCreateAudioPath(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPConfigGlobalMute(Bool bEnable);
void msAPI_combo_IPClockControl(EN_COMBO_IP_SELECT ucComboSelect, Bool bClockHigh);
void msAPI_combo_IPPowerOn(void);
void msAPI_combo_IPPowerDown(void);
void msAPI_combo_IPPowerSaving(void);
Bool msAPI_combo_IPGetSplitFlag(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPCheckAudioStatus(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPLoadEDIDPort(EN_COMBO_IP_SELECT ucComboSelect);
#endif
Bool msAPI_combo_IPInsertHDCP22Key(Bool bExternalKey, BYTE *pu8SecureStormData);
#if 0
//-------------------------------------------------------------------------------------------------
//  TMDS function
//-------------------------------------------------------------------------------------------------
BYTE msAPI_combo_IPGetTmdsModeInfo(EN_COMBO_IP_SELECT ucComboSelect);
BYTE msAPI_combo_IPGetTmdsClkStable(EN_COMBO_IP_SELECT ucComboSelect);
EN_TMDS_AUD_FREQ_INDEX msAPI_combo_IPGetTmdsAudioFreq(EN_COMBO_IP_SELECT ucComboSelect);
EN_TMDS_AUDIO_FORMAT msAPI_combo_IPGetTmdsIsAudioFmtPCM(EN_COMBO_IP_SELECT ucComboSelect);
EN_TMDS_PIXEL_REPETITION msAPI_combo_IPGetPixelRepetitionInfo(EN_COMBO_IP_SELECT ucComboSelect);
WORD msAPI_combo_IPGetTmdsClockRate(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPSetTmdsMonochromeMode(EN_COMBO_IP_SELECT ucComboSelect, Bool bEnable, Bool bFlag, EN_TMDS_MONO_BIT ucBits);
void msAPI_combo_IPSetTmdsDVIDeepColorSetting(EN_COMBO_IP_SELECT ucComboSelect, Bool bEnable, EN_TMDS_DVI_DEEP_COLOR ucBits);
BOOL msAPI_combo_IPCheckAVMuteINT(EN_COMBO_IP_SELECT ucComboSelect, Bool bClr);
BYTE msAPI_combo_IPGetScalingInfo(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPGetITContent(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPGetTmdsIsDVIDualLink(EN_COMBO_IP_SELECT ucComboSelect);
EN_TMDS_AUD_STATUS msAPI_combo_IPGetTMDSAudioOutputState(EN_COMBO_IP_SELECT ucComboSelect);
EN_HDMI_VERSION_TYPE msAPI_combo_IPGetHDMISourceVersion(EN_COMBO_IP_SELECT ucComboSelect);
//-------------------------------------------------------------------------------------------------
//  MHL function
//-------------------------------------------------------------------------------------------------
BYTE msAPI_combo_IPGetCbusMSGKeyEvent(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPCbusSendRCPCommand(EN_COMBO_IP_SELECT ucComboSelect, BYTE ucKeyCode);
//-------------------------------------------------------------------------------------------------
//  DP function
//-------------------------------------------------------------------------------------------------
void msAPI_combo_IPSetDPGuardBand(EN_COMBO_IP_SELECT ucComboSelect, WORD usGuardBandValue);
void msAPI_combo_IPGetDPHVInformation(EN_COMBO_IP_SELECT ucComboSelect, WORD *usHTotalValue, WORD *usVTotalValue);
Bool msAPI_combo_IPGetDPInterlaceFlag(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPGetDPAstorPTGInterlacePatch(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPDPCheckIgnoreDPMS(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPSetDPVersion(EN_COMBO_IP_SELECT ucComboSelect, EN_DP_VERSION ucDPVersion);
Bool msAPI_combo_IPGetDPDRRFlag(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPSetDPDRRFunction(EN_COMBO_IP_SELECT ucComboSelect, Bool bEnable);
WORD msAPI_combo_IPGetDPPixelClock(EN_COMBO_IP_SELECT ucComboSelect);
Bool msAPI_combo_IPDPCheckMSAChg(EN_COMBO_IP_SELECT ucComboSelect);
void msAPI_combo_IPDPClrMSAChg(EN_COMBO_IP_SELECT ucComboSelect);
#endif

#endif


