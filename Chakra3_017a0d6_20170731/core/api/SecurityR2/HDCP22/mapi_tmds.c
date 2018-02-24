#ifndef _MAPI_TMDS_C_
#define _MAPI_TMDS_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "Global.h"
//#include "mdrv_tmds.c"
#include <string.h>
#include "datatype.h"
#include "drvGlobal.h"
#include "msReg.h"


#include "mapi_tmds.h"

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
#if 0
//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_SetConfiguration()
//  [Description]:
//                  use to each combo port type is DVI, Dual or HDMI.
//  [Arguments]:
//                  ucDVIEnableIndex : if bitx = true, means combo(x) is DVI port
//                  ucDualnableIndex :  if bitx = true, means combo(x) is Dual link port
//                  ucHDMIEnableIndex :  if bitx = true, means combo(x) is HDMI port
//                  ucDisplayEnableIndex :   if bitx = true, means combo(x) needs to be display
//  [Return]:
//                  none
//**************************************************************************
void mapi_tmds_SetConfiguration(BYTE ucDVIEnableIndex, BYTE ucDualEnableIndex, BYTE ucHDMIEnableIndex, BYTE ucHDMI2EnableIndex, BYTE ucMHLEnableIndex, BYTE ucDisplayEnableIndex)
{
    mdrv_tmds_SetConfiguration(ucDVIEnableIndex, ucDualEnableIndex, ucHDMIEnableIndex, ucHDMI2EnableIndex, ucMHLEnableIndex, ucDisplayEnableIndex);
}


//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_Initial()
//  [Description]:
//                  use to initial variable
//  [Arguments]:
//                  none
//  [Return]:
//                  none
//**************************************************************************
void mapi_tmds_Initial(void)
{
    mdrv_tmds_Initial();
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_ConfigAudioPort()
//  [Description]:
//                  configurate which port is going to be the audio source
//  [Arguments]:
//                  none
//  [Return]:
//                  none
//**************************************************************************
void mapi_tmds_ConfigAudioPort(BYTE ucInputPort, Bool bEnableAud)
{
    mdrv_tmds_ConfigAudioPort(ucInputPort, bEnableAud);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_Handler()
//  [Description]:
//                  use to polling HDMI status,
//                  ex: input format, packet status, color format
//  [Arguments]:
//                  none
//  [Return]:
//                  none
//**************************************************************************
void mapi_tmds_Handler(void)
{
    mdrv_tmds_Handler();
}

void mapi_tmds_TimerInterrupt(void)
{
    mdrv_tmds_TimerInterrupt();
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_Set_HPD()
//  [Description]:
//                  use to control hot plug pin
//  [Arguments]:
//                  ucComboSelect : combo port
//                  bSetHPD : 1 = HIGH, 0 = LOW
//  [Return]:
//                  none
//**************************************************************************
void mapi_tmds_Set_HPD(BYTE ucComboSelect, Bool bSetHPD)
{
    mdrv_tmds_Set_HPD(ucComboSelect, bSetHPD);
}


//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_Get_Color_Format()
//  [Description]:
//                  use to get input color format
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  typedef struct
//                  {
//                      EN_COLOR_FORMAT_TYPE    ucColorType;
//                      EN_COLOR_RANGE_TYPE     ucColorRange;
//                      EN_COLORIMETRY_TYPE     ucColorimetry;
//                   } ST_COMBO_COLOR_FORMAT;
//
//**************************************************************************
ST_COMBO_COLOR_FORMAT mapi_tmds_Get_Color_Format(BYTE ucInputPort)
{
    return mdrv_tmds_Get_Color_Format(ucInputPort);
}


//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_Input_Is_HDMI()
//  [Description]:
//                  use to check input signal is HDMI or DVI
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//                  1: HDMI
//                  0: DVI
//**************************************************************************
BYTE mapi_tmds_Input_Is_HDMI(BYTE ucInputPort)
{
	return mdrv_tmds_Input_Is_HDMI(ucInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetPacketContent()
//  [Description]:
//                  use to obtain HDMI packet contents
//  [Arguments]:
//                  enInputPort : combo port
//                  ucPacketType: indicate the type of the packet which is going to be extracted
//                  ucPacketLength: the total length to be extracted (byte unit)
//                  pPacketData: pointer, address which store return content
//  [Return]:
//                  none
//
//**************************************************************************
void mapi_tmds_GetPacketContent(BYTE ucInputPort, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData)
{
    mdrv_tmds_GetPacketContent(ucInputPort, ucPacketType, ucPacketLength, pPacketData);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_DetectCablePlug()
//  [Description]:
//                  detect if HDMI/DVI cable is attached.
//  [Arguments]:
//                  ucInputPort : combo port
//  [Return]:
//                  none
//
//**************************************************************************
Bool mapi_tmds_DetectCablePlug(BYTE ucInputPort)
{
    return mdrv_tmds_DetectCablePlug(ucInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_Clock_Stable()
//  [Description]:
//                  detect if HDMI/DVI clock status.
//  [Arguments]:
//                  ucInputPort : combo port
//  [Return]:
//                  none
//
//**************************************************************************
Bool mapi_tmds_Clock_Stable(BYTE enInputPort)
{
    return mdrv_tmds_Clock_Stable(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetAudioFreq()
//  [Description]:
//                  calculate current HDMI audio frequence by CTS/N value;
//                  formula:
//                      freq = (F_tmds * N) / (128 * CTS);
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MScombo_TMDS_AUDFREQ_INDEX
//
//**************************************************************************
MScombo_TMDS_AUD_FREQ_INDEX mapi_tmds_GetAudioFreq(BYTE enInputPort)
{
    return mdrv_tmds_GetAudioFreq(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_IsAudioFmtPCM()
//  [Description]:
//                  check audio format information, is it PCM or non-PCM?
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MSCombo_TMDS_AUDIO_FORMAT:
//                      MSCombo_AUDIO_FMT_NON_PCM   = 0,
//                      MSCombo_AUDIO_FMT_PCM       = 1,
//                      MSCombo_AUDIO_FMT_UNKNOWN   = 2,
//
//**************************************************************************
MSCombo_TMDS_AUDIO_FORMAT mapi_tmds_IsAudioFmtPCM(BYTE enInputPort)
{
    return mdrv_tmds_IsAudioFmtPCM(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetColorDepthInfo()
//  [Description]:
//                  return color depth information, ex: 8bit, 10bit, or 12 bit by parsing GCP packet content
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MSCombo_TMDS_COLOR_DEPTH_FORMAT
//              8_BIT  = 0,
//              10_BIT = 1,
//              12_BIT = 2,
//              16_BIT = 3,
//              UNKNOWN = 4,
//**************************************************************************

MSCombo_TMDS_COLOR_DEPTH_FORMAT mapi_tmds_GetColorDepthInfo(BYTE enInputPort)
{
    return mdrv_tmds_GetColorDepthInfo(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetPixelRepetitionInfo()
//  [Description]:
//                  return pxiel repetition info
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  MSCombo_TMDS_PIXEL_REPETITION
//              no = 0,
//              2x = 1,
//              3x = 2,
//              4x = 3,
//              5x = 4,
//              6x = 5,
//              7x = 6,
//              8x = 7,
//              9x = 8,
//             10x = 9,
//**************************************************************************
MSCombo_TMDS_PIXEL_REPETITION mapi_tmds_GetPixelRepetitionInfo(BYTE enInputPort)
{
    return mdrv_tmds_GetPixelRepetitionInfo(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mhal_tmds_GetClockRate()
//  [Description]:
//                  return clcok rate
//  [Arguments]:
//                  enInputPort
//  [Return]:
//
//**************************************************************************
WORD mapi_tmds_GetClockRate(BYTE enInputPort)
{
    return mdrv_tmds_GetClockRate(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_ISR()
//  [Description]:
//                  interrupt handler for tmds CLK_STABLE
//  [Arguments]:
//                  [MSCombo_TMDS_PORT_INDEX]PortIdx
//  [Return]:
//                  void
//
//**************************************************************************
void mapi_tmds_ISR(void)
{
    mdrv_tmds_ISR();
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_SetMonochromeMode()
//  [Description]:
//                  used for DVI mono mode setting
//  [Arguments]:
//                  enInputPort
//                  bEnable : True -> enable mono mode, False -> disable mono mode and change to dual link setting for next timing detect
//                  bFlag : True ->  dual link mode. False -> single mode.
//                  ucBits : mono bit
//  [Return]:
//                  None
//**************************************************************************
void mapi_tmds_SetMonochromeMode(BYTE enInputPort, Bool bEnable, Bool bFlag, MSCombo_TMDS_MONO_BIT ucBits)
{
    mdrv_tmds_SetMonochromeMode(enInputPort, bEnable, bFlag, ucBits);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_DVIDeepColorSetting()
//  [Description]:
//                  used for DVI deep color mode setting
//  [Arguments]:
//                  enInputPort
//                  bEnable : True : enable deep color mode, False : disable deep color mode and change to dual link setting for next timing detect
//                  ucBits : color depth
//  [Return]:
//                  None
//**************************************************************************
void mapi_tmds_DVIDeepColorSetting(BYTE enInputPort, Bool bEnable, MSCombo_TMDS_DVI_DEEP_COLOR ucBits)
{
    mdrv_tmds_DVIDeepColorSetting(enInputPort, bEnable, ucBits);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetSplitFlag()
//  [Description]:
//                  return HDMI2.0 input signal is over 3.4G or not
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  TRUE: 2p, FALSE: 1p
//**************************************************************************
BOOL mapi_tmds_GetSplitFlag(BYTE enInputPort)
{
    return mdrv_tmds_GetSplitFlag(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_CheckAVMuteINT()
//  [Description]:
//                  return if the AV mute packet is received.
//  [Arguments]:
//                  enInputPort
//                  bClr : True to clr INT status, false to polling status
//  [Return]:
//                  BOOL
//**************************************************************************
BOOL mapi_tmds_CheckAVMuteINT(BYTE enInputPort, Bool bClr)
{
    return mdrv_tmds_CheckAVMuteINT(enInputPort, bClr);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_CheckAudioStatus()
//  [Description]:
//                  return if HDMI receive audio packets
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  BOOL
//**************************************************************************
BOOL mapi_tmds_CheckAudioStatus(BYTE enInputPort)
{
    return mdrv_tmds_CheckAudioStatus(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetScaling_Info()
//  [Description]:
//                  use to get input scaling info
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//**************************************************************************
BYTE mapi_tmds_GetScaling_Info(BYTE ucInputPort)
{
    return mdrv_tmds_GetScaling_Info(ucInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetITContent()
//  [Description]:
//                  use to get input IT content info.
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//**************************************************************************
BOOL mapi_tmds_GetITContent(BYTE enInputPort)
{
    return mdrv_tmds_GetITContent(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_IsDVIDualLink()
//  [Description]:
//                  return TRUE if DVI dual link, else return FALSE;
//  [Arguments]:
//                  enInputPort
//  [Return]:
//                  BOOL
//**************************************************************************
BOOL mapi_tmds_IsDVIDualLink(BYTE enInputPort)
{
	return mdrv_tmds_IsDVIDualLink(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_PowerOnPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_tmds_PowerOnPort(BYTE ucInputPort)
{
    ucInputPort = 0;
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_PowerDownPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_tmds_PowerDownPort(BYTE ucInputPort)
{
    ucInputPort = 0;
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetAudioOutputState()
//  [Description]:
//                  use to get audio output state.
//  [Arguments]:
//                  enInputPort : combo port
//  [Return]:
//**************************************************************************
MsCombo_TMDS_AUD_STATUS mapi_tmds_GetAudioOutputState(BYTE enInputPort)
{
    return mdrv_tmds_GetAudioOutputState(enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_GetSourceVersionType()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mapi_tmds_GetSourceVersionType(BYTE ucInputPort)
{
    return mdrv_tmds_GetSourceVersionType(ucInputPort);
}
#endif

#if(TMDS_HDCP2_FUNCTION_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_SetHDCP2CallBackFunction()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_tmds_SetHDCP2CallBackFunction(TMDS_HDCP2_CALL_BACK_FUNC pHDCP2RxFunc, BYTE *pHDCP2CertRx)
{
    //D PRINT_SECURITY("set call back");

    mdrv_tmds_SetHDCP2CallBackFunction(pHDCP2RxFunc, pHDCP2CertRx);
}

//**************************************************************************
//  [Function Name]:
//                  mapi_tmds_HDCP2TxEventProc()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mapi_tmds_HDCP2TxEventProc(BYTE enInputPort, BYTE ucMessageID, BYTE ucDataSize, BYTE *pHDCPTxData)
{
    //PRINT_SECURITY("TxEventProc");

    mdrv_tmds_HDCP2TxEventProc(enInputPort, ucMessageID, ucDataSize, pHDCPTxData);
}

#endif

#endif // _MAPI_TMDS_C_

