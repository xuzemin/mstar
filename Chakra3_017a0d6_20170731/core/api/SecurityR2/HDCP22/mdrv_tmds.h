#ifndef _MDRV_TMDS_H_
#define _MDRV_TMDS_H_

#include "mhal_tmds.h"
#include "combo_config.h"

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define TMDS_IP_SUPPORT_0PORT           0
#define TMDS_IP_SUPPORT_1PORT           1
#define TMDS_IP_SUPPORT_2PORT           2
#define TMDS_IP_SUPPORT_3PORT           3
#define TMDS_IP_SUPPORT_4PORT           4
#define TMDS_IP_SUPPORT_5PORT           5
#define TMDS_IP_SUPPORT_6PORT           6

#define TMDS_IP_SUPPORT_TYPE            COMBO_IP_SUPPORT_TYPE

#define AviPktLossBound      500  //unit:ms
#define VS_PKT_LOSS_BOUND       500
#define GCP_PKT_LOSS_BOUND      500
#define Sub_DEChgRst_BOUND     100
#define Main_DEChgRst_BOUND     10
#define GetPkt_BOUND           100
#define GetAVI_BOUND           2
#define DUAL_LINK_DEBOUNCE_CNT  2
#define AutoEQDone_BOUND     30

#define TMDS_SCDC_ACCESS_ADDERSS_A8     BIT6

// HDCP 2.2
#define TMDS_HDCP2_FUNCTION_SUPPORT     COMBO_HDCP2_FUNCTION_SUPPORT

typedef void (*TMDS_HDCP2_CALL_BACK_FUNC)(BYTE, BYTE*);

enum TMDS_INPUT_SELECT_TYPE
{
    TMDS_INPUT_SELECT_PORT0 = 0,
#if(TMDS_IP_SUPPORT_TYPE == TMDS_IP_SUPPORT_1PORT)
    TMDS_INPUT_SELECT_PORT_END,
#endif
    TMDS_INPUT_SELECT_PORT1,
#if(TMDS_IP_SUPPORT_TYPE == TMDS_IP_SUPPORT_2PORT)
    TMDS_INPUT_SELECT_PORT_END,
#endif
    TMDS_INPUT_SELECT_PORT2,
#if(TMDS_IP_SUPPORT_TYPE == TMDS_IP_SUPPORT_3PORT)
    TMDS_INPUT_SELECT_PORT_END,
#endif
    TMDS_INPUT_SELECT_PORT3,
#if(TMDS_IP_SUPPORT_TYPE == TMDS_IP_SUPPORT_4PORT)
    TMDS_INPUT_SELECT_PORT_END,
#endif
    TMDS_INPUT_SELECT_PORT4,
#if(TMDS_IP_SUPPORT_TYPE == TMDS_IP_SUPPORT_5PORT)
    TMDS_INPUT_SELECT_PORT_END,
#endif
    TMDS_INPUT_SELECT_PORT5,
#if(TMDS_IP_SUPPORT_TYPE == TMDS_IP_SUPPORT_6PORT)
    TMDS_INPUT_SELECT_PORT_END,
#endif
    TMDS_INPUT_SELECT_MASK = TMDS_INPUT_SELECT_PORT_END,
    TMDS_INPUT_SELECT_NONE = TMDS_INPUT_SELECT_MASK,
};

typedef enum
{
    MsCombo_TMDS_TYPE_DVI      = 1, // Support to 165Mhz
    MsCombo_TMDS_TYPE_DUAL     = 2, // Support to 33oMhz
    MsCombo_TMDS_TYPE_HDMI     = 4, // support HDMI packet
    MsCombo_TMDS_TYPE_HDMI2    = 8, // Support HDMI2 packet
    MsCombo_TMDS_TYPE_RESERVED = 16, // Not TMDS port
} MsCombo_TMDS_TYPE;

typedef enum
{
    MSCombo_TMDS_COLOR_RGB         = 0,///< HDMI RGB 444 Color Format
    MSCombo_TMDS_COLOR_YUV_422     = 1,///< HDMI YUV 422 Color Format
    MSCombo_TMDS_COLOR_YUV_444     = 2,///< HDMI YUV 444 Color Format
    MSCombo_TMDS_COLOR_RESERVED    = 3,///< Reserve
    MSCombo_TMDS_COLOR_DEFAULT     = MSCombo_TMDS_COLOR_RGB,///< Default setting
    MSCombo_TMDS_COLOR_UNKNOWN     = 15,///< Unknow Color Format
} MSCombo_TMDS_COLOR_FORMAT;

typedef enum
{
    MsCombo_TMDS_POWER_ON              = 1,
    MsCombo_TMDS_POWER_STANDBY         = 2,
    MsCombo_TMDS_POWER_OFF             = 4,
    MsCombo_TMDS_POWER_UNKNOWN         = 8,
} MsCombo_TMDS_POWER_STATUS;

typedef enum
{
    TMDS_AUDIO_STATE_OFF = 0,
    TMDS_AUDIO_STATE_ON = 1,
} MsCombo_TMDS_AUD_STATUS;

typedef enum
{
    TMDS_DATA_OUTPUT_OFF = 0,
    TMDS_DATA_OUTPUT_ON = 1,
} MsCombo_TMDS_DATA_STATUS;

enum TMDS_FUNCTION_ENABLE_TYPE
{
    TMDS_FUNCTION_ENABLE_PORT0_FLAG = BIT0,
    TMDS_FUNCTION_ENABLE_PORT1_FLAG = BIT1,
    TMDS_FUNCTION_ENABLE_PORT2_FLAG = BIT2,
    TMDS_FUNCTION_ENABLE_PORT3_FLAG = BIT3,
    TMDS_FUNCTION_ENABLE_PORT4_FLAG = BIT4,
    TMDS_FUNCTION_ENABLE_PORT5_FLAG = BIT5,
    TMDS_FUNCTION_ENABLE_VGA_FLAG = BIT6,
};

enum HDMI_SOURCE_VERSION_TYPE
{
    HDMI_SOURCE_VERSION_NOT_SURE = 0,
    HDMI_SOURCE_VERSION_HDMI14,
    HDMI_SOURCE_VERSION_HDMI20,
};

#if 0
typedef struct
{
    MsCombo_TMDS_TYPE              port_type;
    ST_COMBO_COLOR_FORMAT          input_color;
    MsCombo_TMDS_POWER_STATUS      port_power;
    Bool                           AudioOutputEnable;
    MsCombo_TMDS_AUD_STATUS        AudioOutputState;
    MsCombo_TMDS_DATA_STATUS       DataOutputState;
    WORD                           InputPacketStatus;
    BYTE                           InputPacketError;
    Bool                           ModeChange;
    Bool                           ColorChange;
    BYTE                           InputVideoMode;
    BYTE                           InputAVIInfoReceived;
    BYTE                           InputVSPktReceived;
    BYTE                           InputGCPktReceived;
    BYTE                           GetPktCnt;
    WORD                           AVI_PktLossCnt;
    WORD                           VS_PktLossCnt;
    WORD                           GC_PktLossCnt;
    Bool                           ClrAVMute;
    Bool                           ITContent;
    BYTE                           ScalingInfo;
    BYTE                           AudioErrorStatus;
    BYTE                           AudioOffDebunce;
    Bool                           IsDVIDualLink;
    Bool                           duallink_flag;
    BYTE                           isDualCnt;
    BYTE                           isSingleCnt;
    WORD                           Sub_DeChgRstCnt;
    Bool                           Sub_DEChgRst_flag;
    WORD                           Main_DeChgRstCnt;
    Bool                           Main_DEChgRst_flag;
    Bool                           DualLinkDetectFinish_flag;
    Bool                           SplitterEnable_Over3G;
    Bool                           SplitterEnable_YUV420;
    BYTE                           ucSourceType;
} MsCombo_TMDS_Port;
#endif

#define GET_TMDS_MHL_ENABLE_PORT0()         (Bool)((ucTmds_mhl_port & TMDS_FUNCTION_ENABLE_PORT0_FLAG) ?TRUE :FALSE)
#define GET_TMDS_MHL_ENABLE_PORT1()         (Bool)((ucTmds_mhl_port & TMDS_FUNCTION_ENABLE_PORT1_FLAG) ?TRUE :FALSE)
#define GET_TMDS_MHL_ENABLE_PORT2()         (Bool)((ucTmds_mhl_port & TMDS_FUNCTION_ENABLE_PORT2_FLAG) ?TRUE :FALSE)
#define GET_TMDS_MHL_ENABLE_PORT3()         (Bool)((ucTmds_mhl_port & TMDS_FUNCTION_ENABLE_PORT3_FLAG) ?TRUE :FALSE)
#define GET_TMDS_MHL_ENABLE_PORT4()         (Bool)((ucTmds_mhl_port & TMDS_FUNCTION_ENABLE_PORT4_FLAG) ?TRUE :FALSE)
#define GET_TMDS_MHL_ENABLE_PORT5()         (Bool)((ucTmds_mhl_port & TMDS_FUNCTION_ENABLE_PORT5_FLAG) ?TRUE :FALSE)

#define GET_TMDS_MHL_ENABLE_PORT(a)         (Bool)((ucTmds_mhl_port & _BIT(a)) ?TRUE :FALSE)

extern BYTE ucTmds_mhl_port;

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
#if 0
void mdrv_tmds_SetConfiguration(BYTE ucDVIEnableIndex, BYTE ucDualEnableIndex, BYTE ucHDMIEnableIndex, BYTE ucHDMI2EnableIndex, BYTE ucMHLEnableIndex, BYTE ucDisplayEnableIndex);
void mdrv_tmds_Initial(void);
void mdrv_tmds_ConfigAudioPort(BYTE ucComboPort, Bool bEnableAud);
MsCombo_TMDS_AUD_STATUS mdrv_tmds_GetAudioOutputState(BYTE ucInputPort);
#endif

void mdrv_tmds_Handler(void);
void mdrv_tmds_HDCP2Handler(MSCombo_TMDS_PORT_INDEX enInputPort);

#if 0
void mdrv_tmds_Set_HPD(BYTE ucComboSelect, Bool bSetHPD);
ST_COMBO_COLOR_FORMAT mdrv_tmds_Get_Color_Format(BYTE ucInputPort);
BYTE mdrv_tmds_Input_Is_HDMI(BYTE ucInputPort);
BYTE mdrv_tmds_GetScaling_Info(BYTE ucInputPort);
Bool mdrv_tmds_GetITContent(BYTE ucInputPort);
void mdrv_tmds_GetPacketContent(BYTE ucInputPort, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData);
Bool mdrv_tmds_DetectCablePlug(BYTE ucInputPort);
Bool mdrv_tmds_Clock_Stable(BYTE enInputPort);
MScombo_TMDS_AUD_FREQ_INDEX mdrv_tmds_GetAudioFreq(BYTE enInputPort);
MSCombo_TMDS_AUDIO_FORMAT mdrv_tmds_IsAudioFmtPCM(BYTE enInputPort);
MSCombo_TMDS_COLOR_DEPTH_FORMAT mdrv_tmds_GetColorDepthInfo(BYTE enInputPort);
MSCombo_TMDS_PIXEL_REPETITION mdrv_tmds_GetPixelRepetitionInfo(BYTE enInputPort);
WORD mdrv_tmds_GetClockRate(BYTE enInputPort);
void mdrv_tmds_ISR(void);
void mdrv_tmds_SetMonochromeMode(BYTE enInputPort, Bool bEnable, Bool bFlag, MSCombo_TMDS_MONO_BIT ucBits);
void mdrv_tmds_DVIDeepColorSetting(BYTE enInputPort, Bool bEnable, MSCombo_TMDS_DVI_DEEP_COLOR ucBits);
BOOL mdrv_tmds_GetSplitFlag(BYTE enInputPort);
BOOL mdrv_tmds_CheckAVMuteINT(BYTE enInputPort, Bool bClr);
BOOL mdrv_tmds_CheckAudioStatus(BYTE enInputPort);
BOOL mdrv_tmds_IsDVIDualLink(BYTE enInputPort);
BYTE mdrv_tmds_GetSourceVersionType(BYTE enInputPort);
#endif

#if(TMDS_HDCP2_FUNCTION_SUPPORT)
void mdrv_tmds_SetHDCP2CallBackFunction(TMDS_HDCP2_CALL_BACK_FUNC pHDCP2RxFunc, BYTE *pHDCP2CertRx);
void mdrv_tmds_HDCP2TxEventProc(BYTE enInputPort, BYTE ucMessageID, BYTE ucDataSize, BYTE *pHDCPTxData);
#endif

#endif //_MDRV_TMDS_H_


