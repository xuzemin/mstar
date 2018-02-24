#ifndef _MHAL_TMDS_H_
#define _MHAL_TMDS_H_

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#if 0
#define _BIT(a)                             (BIT0 << (a))
#define MASKBIT(a)                          (_BIT((1?a) +1) -_BIT((0?a)))
#define MASKSET(a, b, c)                    ((a &~c) | (b &c))
#endif
#define ABS_MINUS(a, b)                     ((a > b)? (a -b): (b -a))

typedef enum
{
    MSCombo_AUDIO_FMT_NON_PCM   = 0,
    MSCombo_AUDIO_FMT_PCM       = 1,
    MSCombo_AUDIO_FMT_UNKNOWN   = 2,
} MSCombo_TMDS_AUDIO_FORMAT;

typedef enum
{
    MSCombo_TMDS_COLOR_DEPTH_6_BIT  = 0,
    MSCombo_TMDS_COLOR_DEPTH_8_BIT  = 1,
    MSCombo_TMDS_COLOR_DEPTH_10_BIT = 2,
    MSCombo_TMDS_COLOR_DEPTH_12_BIT = 3,
    MSCombo_TMDS_COLOR_DEPTH_16_BIT = 4,
    MSCombo_TMDS_COLOR_DEPTH_UNKNOWN = 5,
} MSCombo_TMDS_COLOR_DEPTH_FORMAT;

typedef enum
{
    MSCombo_TMDS_N0_PIX_REP = 0,
    MSCombo_TMDS_2x_PIX_REP = 1,
    MSCombo_TMDS_3x_PIX_REP = 2,
    MSCombo_TMDS_4x_PIX_REP = 3,
    MSCombo_TMDS_5x_PIX_REP = 4,
    MSCombo_TMDS_6x_PIX_REP = 5,
    MSCombo_TMDS_7x_PIX_REP = 6,
    MSCombo_TMDS_8x_PIX_REP = 7,
    MSCombo_TMDS_9x_PIX_REP = 8,
    MSCombo_TMDS_10x_PIX_REP = 9,
    MSCombo_TMDS_RESERVED_PIX_REP = 10,
} MSCombo_TMDS_PIXEL_REPETITION;

typedef enum
{
    MSCombo_TMDS_PORT_0      = 0,
    MSCombo_TMDS_PORT_1      = 1,
    MSCombo_TMDS_PORT_2      = 2,
    MSCombo_TMDS_PORT_3      = 3,
    MSCombo_TMDS_PORT_MAX      = 3,
} MSCombo_TMDS_PORT_INDEX;

typedef enum
{
    MScombo_TMDS_AUD_FREQ_32K       = 32,
    MScombo_TMDS_AUD_FREQ_44K       = 44,
    MScombo_TMDS_AUD_FREQ_48K       = 48,
    MScombo_TMDS_AUD_FREQ_88K       = 88,
    MScombo_TMDS_AUD_FREQ_96K       = 96,
    MScombo_TMDS_AUD_FREQ_176K      = 176,
    MScombo_TMDS_AUD_FREQ_192K      = 192,
    MScombo_TMDS_AUD_FREQ_ERROR     = 0,

} MScombo_TMDS_AUD_FREQ_INDEX;

typedef enum
{
    MSCombo_TMDS_MONO_8_BIT  = 0,
    MSCombo_TMDS_MONO_10_BIT = 1,
    MSCombo_TMDS_MONO_12_BIT = 2,
} MSCombo_TMDS_MONO_BIT;

typedef enum
{
    MSCombo_TMDS_DVI_DEEP_COLOR_8_BIT  = 0,
    MSCombo_TMDS_DVI_DEEP_COLOR_10_BIT = 1,
    MSCombo_TMDS_DVI_DEEP_COLOR_12_BIT = 2,
    MSCombo_TMDS_DVI_DEEP_COLOR_16_BIT = 3,
} MSCombo_TMDS_DVI_DEEP_COLOR;

enum TMDS_HDCP2_MESSAGE_ID_TYPE
{
    TMDS_HDCP2_MSG_ID_NONE = 0,
    TMDS_HDCP2_MSG_ID_AKE_INIT = 2,
    TMDS_HDCP2_MSG_ID_AKE_SEND_CERT = 3,
    TMDS_HDCP2_MSG_ID_AKE_NO_STORED_KM = 4,
    TMDS_HDCP2_MSG_ID_AKE_STORED_KM = 5,
    TMDS_HDCP2_MSG_ID_AKE_SEND_H_PRIME = 7,
    TMDS_HDCP2_MSG_ID_AKE_SEND_PAIRING_INFO = 8,
    TMDS_HDCP2_MSG_ID_LC_INIT = 9,
    TMDS_HDCP2_MSG_ID_LC_SEND_L_PRIME = 10,
    TMDS_HDCP2_MSG_ID_SKE_SEND_EKS = 11,
};

typedef enum
{
    TMDS_HDCP2_INFO_NONE = 0,
    TMDS_HDCP2_INFO_AKE_RTX,
    TMDS_HDCP2_INFO_AKE_TXCAPS,
    TMDS_HDCP2_INFO_AKE_CERTRX,
    TMDS_HDCP2_INFO_AKE_RRX,
    TMDS_HDCP2_INFO_AKE_RXCAPS,
    TMDS_HDCP2_INFO_AKE_EKPUB_KM,
    TMDS_HDCP2_INFO_AKE_EKH_KM_WR,
    TMDS_HDCP2_INFO_AKE_M,
    TMDS_HDCP2_INFO_AKE_H_PRIME,
    TMDS_HDCP2_INFO_AKE_EKH_KM_RD,
    TMDS_HDCP2_INFO_LC_RN,
    TMDS_HDCP2_INFO_LC_L_PRIME,
    TMDS_HDCP2_INFO_SKE_EDKEY_KS,
    TMDS_HDCP2_INFO_SKE_RIV,
} TMDS_HDCP2_INFORMATION_TYPE;

enum TMDS_CABLE_DETECT
{
    TMDS_CABLE_DETECT_NO_INPUT = 0,
    TMDS_CABLE_DETECT_HDMI = 1,
    TMDS_CABLE_DETECT_MHL = 2,
};

#define TMDS_HDCP2_AKE_RTX_SIZE           8
#define TMDS_HDCP2_AKE_TXCAPS_SIZE        3
#define TMDS_HDCP2_AKE_CERTRX_SIZE        522
#define TMDS_HDCP2_AKE_RRX_SIZE           8
#define TMDS_HDCP2_AKE_RXCAPS_SIZE        3
#define TMDS_HDCP2_AKE_EKPUB_KM_SIZE      128
#define TMDS_HDCP2_AKE_EKH_KM_WR_SIZE     16
#define TMDS_HDCP2_AKE_M_SIZE             16
#define TMDS_HDCP2_AKE_H_PRIME_SIZE       32
#define TMDS_HDCP2_AKE_EKH_KM_RD_SIZE     16
#define TMDS_HDCP2_LC_RN_SIZE             8
#define TMDS_HDCP2_LC_L_PRIME_SIZE        32
#define TMDS_HDCP2_SKE_EDKEY_KS_SIZE      16
#define TMDS_HDCP2_SKE_RIV_SIZE           8

#define TMDS_HDCP2_RX_QUEUE_SIZE          129
#define TMDS_HDCP2_TX_QUEUE_SIZE          33


#define ERR_HDMI_CTSN_OVERRANGE     _BIT0
#define ERR_HDMI_CLK_BIG_CHANGE     _BIT1
#define ERR_HDMI_AVMUTE             _BIT2
#define ERR_HDMI_NO_INPUT_CLK       _BIT3
#define ERR_HDMI_AUD_SMP_FLAT       _BIT4
#define ERR_HDMI_AUD_CH_ST_CHANGE   _BIT5
#define ERR_HDMI_AUD_FIFO_ERR       _BIT6
#define ERR_HDMI_AUD_SMP_ERR        _BIT7

#define TMDS_PHY_EFUSE_ADDRESS0     0x141
#define TMDS_PHY_EFUSE_ADDRESS1     0x142
#define TMDS_PHY_EFUSE_ADDRESS2     0x143
#define TMDS_PHY_EFUSE_ADDRESS3     0x144
#define TMDS_PHY_EFUSE_ADDRESS4     0x145
#define TMDS_PHY_EFUSE_ADDRESS5     0x146

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
#if 0
BYTE mhal_tmds_CheckAudioErrorStatus(MSCombo_TMDS_PORT_INDEX enInputPort, BOOL bClrAVMute);
void mhal_tmds_ConfigAudioPort(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_EnableAudioMute(Bool EnableMute);
void mhal_tmds_HDMI20_MUX(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_Initial(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bDual);
void mhal_tmds_EnableIRQ(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_MaskComboIRQ(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
WORD mhal_tmds_HDMIGetPktStatus(MSCombo_TMDS_PORT_INDEX enInputPort);
BYTE mhal_tmds_HDMIGetErrorStatus(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_DE_Stable(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_Clock_Stable(MSCombo_TMDS_PORT_INDEX enInputPort);
BYTE mhal_tmds_GetInputType(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_SubDEChangeReset(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_IsDualLink(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_MainDEChangeReset(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_IsMainLinkStable(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_Link_LockCheck(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
void mhal_tmds_DualLink_ComboMuxClk(MSCombo_TMDS_PORT_INDEX enInputPort, MSCombo_TMDS_PORT_INDEX enInputPortSwitch);
void mhal_tmds_DualLink_Setting(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
void mhal_tmds_PowerControl(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
void mhal_tmds_Set_HPD(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bSetHPD);
void mhal_tmds_reset_status(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag, BYTE ucReset);
Bool mhal_tmds_NoInputClk(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_TimingChg(MSCombo_TMDS_PORT_INDEX enInputPort);
ST_COMBO_COLOR_FORMAT mhal_tmds_GetColor(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_GetITContent(MSCombo_TMDS_PORT_INDEX enInputPort);
BYTE mhal_tmds_GetScaling_Info(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_GetPacketContent(MSCombo_TMDS_PORT_INDEX enInputPort, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData);
BYTE mhal_tmds_DetectCablePlug(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
MScombo_TMDS_AUD_FREQ_INDEX mhal_tmds_GetAudioFreq(MSCombo_TMDS_PORT_INDEX enInputPort);
MSCombo_TMDS_AUDIO_FORMAT mhal_tmds_IsAudioFmtPCM(MSCombo_TMDS_PORT_INDEX enInputPort);
MSCombo_TMDS_COLOR_DEPTH_FORMAT mhal_tmds_GetColorDepthInfo(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_CheckClockValid(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_CheckClockLock(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_ClearClockStatus(MSCombo_TMDS_PORT_INDEX enInputPort);
MSCombo_TMDS_PIXEL_REPETITION mhal_tmds_GetPixelRepetitionInfo(MSCombo_TMDS_PORT_INDEX enInputPort);
WORD mhal_tmds_GetClockRate(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_GetIsOver3G(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_SetIsOver3G(MSCombo_TMDS_PORT_INDEX enInputPort, Bool Flag);
Bool mhal_tmds_GetIsSplitterDone(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_SetIsSplitterDone(MSCombo_TMDS_PORT_INDEX enInputPort, Bool Flag);
Bool mhal_tmds_GetAutoEQCntRst(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_SetAutoEQCntRst(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
Bool mhal_tmds_AutoEQDone(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_TriggerAutoEQ(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bEnable);
void mhal_tmds_CheckAutoEQ(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
void mhal_tmds_ISR(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bMHLSupport);
Bool mhal_tmds_GetNoInputFlag(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_Over3G_420Setting(MSCombo_TMDS_PORT_INDEX enInputPort);
WORD mhal_tmds_HDE_value(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_HDMI20Setting(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
void mhal_tmds_SetMonochromeMode(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bEnable, Bool bFlag, MSCombo_TMDS_MONO_BIT ucBits);
void mhal_tmds_DVIDeepColorSetting(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bEnable, MSCombo_TMDS_DVI_DEEP_COLOR ucBits);
BOOL mhal_tmds_InputIsHDMI2(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_SetSplitter(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
BOOL mhal_tmds_CheckAVMuteINT(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bClr);
BOOL mhal_tmds_CheckAVMute(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_AUPLL_Setting(MScombo_TMDS_AUD_FREQ_INDEX enAudFreq);
void mhal_tmds_HDCPFrameClear(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag);
void mhal_tmds_DeepColorFIFOReset(MSCombo_TMDS_PORT_INDEX enInputPort);
Bool mhal_tmds_GetSCDCStatusFlag(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE ucStatusMask);
#endif
BOOL mhal_tmds_HDCP2CheckWriteDone(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_HDCP2GetRxData(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE *pHDCPData);
BOOL mhal_tmds_HDCP2CheckWriteStart(MSCombo_TMDS_PORT_INDEX enInputPort);
void mhal_tmds_HDCP2SetTxData(MSCombo_TMDS_PORT_INDEX enInputPort, BYTE MessageID, BYTE DataSize, BYTE *pHDCPTxData, BYTE *pHDCPTxData_CertRx);

#endif //_MHAL_TMDS_H_


