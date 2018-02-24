#ifndef _MAPI_TMDS_H_
#define _MAPI_TMDS_H_

#include "combo_config.h"
#include "mdrv_tmds.h"

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define TMDS_HDMI14_CLK_CHANNEL_EQ          COMBO_HDMI14_CLK_CHANNEL_EQ
#define TMDS_HDMI14_B_CHANNEL_EQ            COMBO_HDMI14_B_CHANNEL_EQ
#define TMDS_HDMI14_G_CHANNEL_EQ            COMBO_HDMI14_G_CHANNEL_EQ
#define TMDS_HDMI14_R_CHANNEL_EQ            COMBO_HDMI14_R_CHANNEL_EQ

#define TMDS_HDMI20_CLK_CHANNEL_EQ          COMBO_HDMI20_CLK_CHANNEL_EQ
#define TMDS_HDMI20_B_CHANNEL_EQ            COMBO_HDMI20_B_CHANNEL_EQ
#define TMDS_HDMI20_G_CHANNEL_EQ            COMBO_HDMI20_G_CHANNEL_EQ
#define TMDS_HDMI20_R_CHANNEL_EQ            COMBO_HDMI20_R_CHANNEL_EQ

//-------------------------------------------------------------------------------------------------
//  Interface Link
//-------------------------------------------------------------------------------------------------
#define TMDS_CABLE_SAR_DETECT_PORT0         hwDigital0Cable_Pin
#define TMDS_CABLE_SAR_DETECT_PORT1         hwDigital1Cable_Pin
#define TMDS_CABLE_SAR_DETECT_PORT2         hwDigital2Cable_Pin
#define TMDS_CABLE_SAR_DETECT_PORT3         hwDigital3Cable_Pin
#define TMDS_CABLE_SAR_DETECT_PORT4         hwDigital4Cable_Pin
#define TMDS_CABLE_SAR_DETECT_PORT5         hwDigital5Cable_Pin

#define TMDS_CABLE_5V_DETECT_PORT0          hwDigital0Cable_Pin
#define TMDS_CABLE_5V_DETECT_PORT1          hwDigital1Cable_Pin
#define TMDS_CABLE_5V_DETECT_PORT2          hwDigital2Cable_Pin
#define TMDS_CABLE_5V_DETECT_PORT3          hwDigital3Cable_Pin
#define TMDS_CABLE_5V_DETECT_PORT4          hwDigital4Cable_Pin
#define TMDS_CABLE_5V_DETECT_PORT5          hwDigital5Cable_Pin

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------
#if 0
void mapi_tmds_SetConfiguration(BYTE ucDVIEnableIndex, BYTE ucDualEnableIndex, BYTE ucHDMIEnableIndex, BYTE ucHDMI2EnableIndex, BYTE ucMHLEnableIndex, BYTE ucDisplayEnableIndex);
void mapi_tmds_Initial(void);
void mapi_tmds_ConfigAudioPort(BYTE ucInputPort, Bool bEnableAud);
void mapi_tmds_Handler(void);
void mapi_tmds_TimerInterrupt(void);
void mapi_tmds_Set_HPD(BYTE ucComboSelect, Bool bSetHPD);
ST_COMBO_COLOR_FORMAT mapi_tmds_Get_Color_Format(BYTE ucInputPort);
BYTE mapi_tmds_Input_Is_HDMI(BYTE ucInputPort);
void mapi_tmds_GetPacketContent(BYTE ucInputPort, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData);
Bool mapi_tmds_DetectCablePlug(BYTE ucInputPort);
Bool mapi_tmds_Clock_Stable(BYTE enInputPort);
MScombo_TMDS_AUD_FREQ_INDEX mapi_tmds_GetAudioFreq(BYTE enInputPort);
MSCombo_TMDS_AUDIO_FORMAT mapi_tmds_IsAudioFmtPCM(BYTE enInputPort);
MSCombo_TMDS_COLOR_DEPTH_FORMAT mapi_tmds_GetColorDepthInfo(BYTE enInputPort);
MSCombo_TMDS_PIXEL_REPETITION mapi_tmds_GetPixelRepetitionInfo(BYTE enInputPort);
WORD mapi_tmds_GetClockRate(BYTE enInputPort);
void mapi_tmds_ISR(void);
void mapi_tmds_SetMonochromeMode(BYTE enInputPort, Bool bEnable, Bool bFlag, MSCombo_TMDS_MONO_BIT ucBits);
void mapi_tmds_DVIDeepColorSetting(BYTE enInputPort, Bool bEnable, MSCombo_TMDS_DVI_DEEP_COLOR ucBits);
BOOL mapi_tmds_GetSplitFlag(BYTE enInputPort);
BOOL mapi_tmds_CheckAVMuteINT(BYTE enInputPort, Bool bClr);
BOOL mapi_tmds_CheckAudioStatus(BYTE enInputPort);
BYTE mapi_tmds_GetScaling_Info(BYTE ucInputPort);
BOOL mapi_tmds_GetITContent(BYTE enInputPort);
BOOL mapi_tmds_IsDVIDualLink(BYTE enInputPort);
void mapi_tmds_PowerOnPort(BYTE ucInputPort);
void mapi_tmds_PowerDownPort(BYTE ucInputPort);
MsCombo_TMDS_AUD_STATUS mapi_tmds_GetAudioOutputState(BYTE enInputPort);
BYTE mapi_tmds_GetSourceVersionType(BYTE ucInputPort);
#endif

#if(TMDS_HDCP2_FUNCTION_SUPPORT)
void mapi_tmds_SetHDCP2CallBackFunction(TMDS_HDCP2_CALL_BACK_FUNC pHDCP2RxFunc, BYTE *pHDCP2CertRx);
void mapi_tmds_HDCP2TxEventProc(BYTE enInputPort, BYTE ucMessageID, BYTE ucDataSize, BYTE *pHDCPTxData);
#endif

#endif //_MAPI_TMDS_H_


