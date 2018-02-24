///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    mdrv_tmds.c
/// @author MStar Semiconductor Inc.
/// @brief  TMDS driver Function
///////////////////////////////////////////////////////////////////////////////////////////////////

//#ifndef _MDRV_TMDS_C_
//#define _MDRV_TMDS_C_

#include "Board.h"

#if( ENABLE_SECURITY_R2_HDCP22 )


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "Global.h"
#include "msReg.h"
#include "MsTypes.h"
#include "drvXC_IOPort.h"


#include <string.h>
#include "apiXC.h"
//#include "System.h"
#include "mdrv_tmds.h"
//#include "mhal_tmds.c"

#define DRV_TMDS_PrtMsg(str)                    //printMsg(str)
#define DRV_TMDS_PrtData(str, x)                //printData(str, x)

//MsCombo_TMDS_Port tmds_port[TMDS_INPUT_SELECT_MASK];
BYTE tmds_hdmi_port;
BYTE tmds_hdmi2_port;
BYTE tmds_dvi_port;
BYTE tmds_dual_port;
BYTE ucTmds_mhl_port;

BYTE *pHDCPTxData_CertRx;

BYTE GetAVICnt[TMDS_INPUT_SELECT_MASK];
WORD HDE_Value[TMDS_INPUT_SELECT_MASK];
WORD AutoEQDoneCnt[TMDS_INPUT_SELECT_MASK];

//patch for DVI dual-Link;
//static WORD DeStableCnt = 0;
//#define DE_STABLE_CNT_LIMIT 200

TMDS_HDCP2_CALL_BACK_FUNC pmdrv_tmds_HDCP2RxEventProc = NULL;

#if 0
//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_CheckAudioErrorStatus()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_CheckAudioErrorStatus(MSCombo_TMDS_PORT_INDEX enInputPort, BOOL bClrAVMute)
{
    tmds_port[enInputPort].AudioErrorStatus = mhal_tmds_CheckAudioErrorStatus(enInputPort, bClrAVMute);
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_HDMIGetPktStatus()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_HDMIGetPktStatus(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    tmds_port[enInputPort].InputPacketStatus = mhal_tmds_HDMIGetPktStatus(enInputPort);

    if( tmds_port[enInputPort].InputPacketStatus & BIT3)
    {
        tmds_port[enInputPort].InputAVIInfoReceived = 1;
    }

    if( tmds_port[enInputPort].InputPacketStatus & BIT7)
    {
        tmds_port[enInputPort].InputVSPktReceived = 1;
    }

    if( tmds_port[enInputPort].InputPacketStatus & BIT4)
    {
        tmds_port[enInputPort].InputGCPktReceived = 1;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_EnableAudioMute()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_EnableAudioMute(MsCombo_TMDS_AUD_STATUS AudioStatus)
{
    if (AudioStatus == TMDS_AUDIO_STATE_OFF)
    {
        mhal_tmds_EnableAudioMute(TRUE);
    }
    else
    {
        mhal_tmds_EnableAudioMute(FALSE);
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_CheckAudio()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_CheckAudio(BYTE ucComboPort)
{
    MsCombo_TMDS_AUD_STATUS TmpAudStatus;

    //b'4: audio sample error; b'5:  audio sample polarity error;
    if (tmds_port[ucComboPort].InputPacketError & (BIT4 | BIT5))
    {
        TmpAudStatus = TMDS_AUDIO_STATE_OFF;
    }
    //b'5: reg_asample_pkt; b'6: reg_acr_pkt
    else if ((tmds_port[ucComboPort].InputPacketStatus & (BIT5 | BIT6)) == (BIT5 | BIT6) )
    {
		if(mdrv_tmds_IsAudioFmtPCM(ucComboPort)==MSCombo_AUDIO_FMT_NON_PCM)
        {
            TmpAudStatus = TMDS_AUDIO_STATE_OFF;
        }
        else if (tmds_port[ucComboPort].DataOutputState == TMDS_DATA_OUTPUT_ON)
        {
            TmpAudStatus = TMDS_AUDIO_STATE_ON;
        }
        else
        {
            TmpAudStatus = TMDS_AUDIO_STATE_OFF;
        }
    }
    else if (tmds_port[ucComboPort].AudioErrorStatus == 0)
    {
        TmpAudStatus = TMDS_AUDIO_STATE_ON;
    }
    else
    {
        TmpAudStatus = TMDS_AUDIO_STATE_OFF;
    }

    if( tmds_port[ucComboPort].AudioOutputState == TMDS_AUDIO_STATE_ON && TmpAudStatus == TMDS_AUDIO_STATE_OFF )
    {
        if( ++tmds_port[ucComboPort].AudioOffDebunce < 20 )
        {
            return ;
        }
    }
    else
    {
        tmds_port[ucComboPort].AudioOffDebunce = 0;
    }

    if( TmpAudStatus != tmds_port[ucComboPort].AudioOutputState )
    {
        _mdrv_tmds_EnableAudioMute(TmpAudStatus);

        tmds_port[ucComboPort].AudioOutputState = TmpAudStatus;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_CheckClockValid()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool _mdrv_tmds_CheckClockValid(BYTE enInputPort)
{
    return mhal_tmds_CheckClockValid((MSCombo_TMDS_PORT_INDEX)enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_CheckClockLock()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool _mdrv_tmds_CheckClockLock(BYTE enInputPort)
{
    return mhal_tmds_CheckClockLock((MSCombo_TMDS_PORT_INDEX)enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_CheckAutoEQ()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_CheckAutoEQ(BYTE enInputPort)
{
    Bool bFlag = FALSE;
    Bool bAutoEQCntRst = FALSE;
    MSCombo_TMDS_PORT_INDEX i = (MSCombo_TMDS_PORT_INDEX)enInputPort;

    bAutoEQCntRst = mhal_tmds_GetAutoEQCntRst(i);

    if(bAutoEQCntRst == TRUE)
    {
        AutoEQDoneCnt[i] = 0;
        bAutoEQCntRst = FALSE;

        mhal_tmds_SetAutoEQCntRst(i, FALSE);
    }

    if(AutoEQDoneCnt[i] > AutoEQDone_BOUND)
    {
        bFlag = TRUE;
    }

    mhal_tmds_CheckAutoEQ(i, bFlag);
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_AudioPollingProc()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_AudioPollingProc(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    MScombo_TMDS_AUD_FREQ_INDEX enAudioFreq = mhal_tmds_GetAudioFreq(enInputPort);

    _mdrv_tmds_CheckAudio((BYTE)enInputPort);

    if(enAudioFreq > MScombo_TMDS_AUD_FREQ_96K)
    {
        mhal_tmds_AUPLL_Setting(MScombo_TMDS_AUD_FREQ_176K);
    }
    else if(enAudioFreq > MScombo_TMDS_AUD_FREQ_48K)
    {
        mhal_tmds_AUPLL_Setting(MScombo_TMDS_AUD_FREQ_88K);
    }
    else
    {
        mhal_tmds_AUPLL_Setting(MScombo_TMDS_AUD_FREQ_32K);
    }

#if (ENABLE_AUDIO_AUTO_MUTE || ENABLE_AUDIO_AUTO_FADING)
    _mdrv_tmds_CheckAudioErrorStatus(enInputPort, tmds_port[enInputPort].ClrAVMute);

    tmds_port[enInputPort].ClrAVMute = FALSE;

#endif
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_HDMIPollingProc()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_HDMIPollingProc(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(mhal_tmds_NoInputClk(enInputPort))
    {
        mhal_tmds_TriggerAutoEQ(enInputPort, FALSE);
        mhal_tmds_SetIsOver3G(enInputPort, FALSE);
        mhal_tmds_HDMI20Setting(enInputPort, FALSE);
    }

    if(mhal_tmds_Clock_Stable(enInputPort))
    {
        if(!mhal_tmds_AutoEQDone(enInputPort))
        {
            if(mhal_tmds_GetIsOver3G(enInputPort))
            {
                _mdrv_tmds_CheckAutoEQ(enInputPort);
            }
        }

        if(mhal_tmds_GetIsSplitterDone(enInputPort) == FALSE)
        {
            if(mhal_tmds_InputIsHDMI2(enInputPort))
            {
                if(mhal_tmds_GetIsOver3G(enInputPort) == FALSE)
                {
                    mhal_tmds_HDMI20Setting(enInputPort, TRUE);
                    mhal_tmds_SetIsOver3G(enInputPort, TRUE);
                }
            }
            else
            {
                if(mhal_tmds_GetIsOver3G(enInputPort) == TRUE)
                {
                    mhal_tmds_HDMI20Setting(enInputPort, FALSE);
                    mhal_tmds_SetIsOver3G(enInputPort, FALSE);
                }
            }
        }
    }
    if(mhal_tmds_DE_Stable(enInputPort)) //DE stable
    {
        tmds_port[enInputPort].InputVideoMode = mhal_tmds_GetInputType(enInputPort);

        if(tmds_port[enInputPort].InputVideoMode) //  Input is HDMI
        {
            if(mhal_tmds_TimingChg(enInputPort))
            {
                mhal_tmds_HDCPFrameClear(enInputPort, FALSE);
            }

            mhal_tmds_DeepColorFIFOReset(enInputPort);

            tmds_port[enInputPort].InputAVIInfoReceived = 0;
            tmds_port[enInputPort].InputVSPktReceived = 0;
            tmds_port[enInputPort].InputGCPktReceived = 0;
            tmds_port[enInputPort].DataOutputState = TMDS_DATA_OUTPUT_ON;

            tmds_port[enInputPort].InputPacketError= mhal_tmds_HDMIGetErrorStatus(enInputPort);

            if(tmds_port[enInputPort].GetPktCnt > GetPkt_BOUND)
            {
                _mdrv_tmds_HDMIGetPktStatus(enInputPort);

                tmds_port[enInputPort].GetPktCnt = 0;
            }

            if(tmds_port[enInputPort].InputAVIInfoReceived)
            {
                tmds_port[enInputPort].AVI_PktLossCnt = 0;
                tmds_port[enInputPort].input_color = (ST_COMBO_COLOR_FORMAT)mhal_tmds_GetColor(enInputPort);
                tmds_port[enInputPort].ScalingInfo = mhal_tmds_GetScaling_Info(enInputPort);
                tmds_port[enInputPort].ITContent = mhal_tmds_GetITContent(enInputPort);

                if(mhal_tmds_GetIsSplitterDone(enInputPort) == FALSE)
                {
                    GetAVICnt[enInputPort]++;

                    if(GetAVICnt[enInputPort] > GetAVI_BOUND)
                    {
                        GetAVICnt[enInputPort] = 0;

                        if(mhal_tmds_InputIsHDMI2(enInputPort) && (!(tmds_port[enInputPort].input_color.ucColorType == COMBO_COLOR_FORMAT_YUV_420)))
                        {
                            tmds_port[enInputPort].SplitterEnable_Over3G = TRUE;

                            mhal_tmds_SetSplitter(enInputPort, TRUE);
                            mhal_tmds_SetIsSplitterDone(enInputPort, TRUE);
                        }
                        else if(tmds_port[enInputPort].input_color.ucColorType == COMBO_COLOR_FORMAT_YUV_420)
                        {
                            if(mhal_tmds_InputIsHDMI2(enInputPort))
                            {
                                mhal_tmds_Over3G_420Setting(enInputPort);
                            }

                            if(HDE_Value[enInputPort] == mhal_tmds_HDE_value(enInputPort))
                            {
                                HDE_Value[enInputPort] = 0;
                                tmds_port[enInputPort].SplitterEnable_YUV420 = TRUE;

                                mhal_tmds_SetSplitter(enInputPort, FALSE);
                                mhal_tmds_SetIsSplitterDone(enInputPort,TRUE);
                            }

                            HDE_Value[enInputPort] = mhal_tmds_HDE_value(enInputPort);
                        }
                        else
                        {
                            tmds_port[enInputPort].SplitterEnable_Over3G = FALSE;
                            tmds_port[enInputPort].SplitterEnable_YUV420 = FALSE;

                            mhal_tmds_SetIsSplitterDone(enInputPort, TRUE);
                        }
                    }
                }
            }
            else
            {
                if(tmds_port[enInputPort].AVI_PktLossCnt>AviPktLossBound) //temp
                {
                    tmds_port[enInputPort].AVI_PktLossCnt = 0;
                    tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_RGB;
                    tmds_port[enInputPort].ScalingInfo = 0;
                    tmds_port[enInputPort].ITContent = 0;

                    mhal_tmds_reset_status(enInputPort, TRUE, 0x00);
                }
            }

            if(tmds_port[enInputPort].InputVSPktReceived)
            {
                tmds_port[enInputPort].VS_PktLossCnt = 0;
            }
            else
            {
                if(tmds_port[enInputPort].VS_PktLossCnt > VS_PKT_LOSS_BOUND)
                {
                    tmds_port[enInputPort].VS_PktLossCnt = 0;
                }
            }

            if(tmds_port[enInputPort].InputGCPktReceived)
            {
                tmds_port[enInputPort].GC_PktLossCnt = 0;

                if(mhal_tmds_CheckAVMute(enInputPort))
                {
                    tmds_port[enInputPort].ClrAVMute = FALSE;
                }
                else
                {
                    tmds_port[enInputPort].ClrAVMute = TRUE;
                }
            }
            else
            {
                if(tmds_port[enInputPort].GC_PktLossCnt > GCP_PKT_LOSS_BOUND)
                {
                    tmds_port[enInputPort].GC_PktLossCnt = 0;
                    tmds_port[enInputPort].ClrAVMute = TRUE;
                }
            }

            if(tmds_port[enInputPort].AudioOutputEnable == TRUE)
            {
                _mdrv_tmds_AudioPollingProc(enInputPort);
            }

            if(tmds_port[enInputPort].ucSourceType == HDMI_SOURCE_VERSION_NOT_SURE)
            {
                if(mhal_tmds_GetSCDCStatusFlag(enInputPort, TMDS_SCDC_ACCESS_ADDERSS_A8))
                {
                    tmds_port[enInputPort].ucSourceType = HDMI_SOURCE_VERSION_HDMI20;
                }
                else
                {
                    tmds_port[enInputPort].ucSourceType = HDMI_SOURCE_VERSION_HDMI14;
                }
            }
        }
        else // Input is DVI
        {
            if(mhal_tmds_TimingChg(enInputPort))
            {
                mhal_tmds_HDCPFrameClear(enInputPort, TRUE);

                tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_RGB;

                mhal_tmds_reset_status(enInputPort, TRUE, 0xDD);
            }
        }
    }
    else  //DE unstable
    {
        tmds_port[enInputPort].ucSourceType = HDMI_SOURCE_VERSION_NOT_SURE;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_DVIPollingProc()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_DVIPollingProc(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    if(mhal_tmds_DE_Stable(enInputPort))//DE stable
    {
        tmds_port[enInputPort].InputVideoMode = mhal_tmds_GetInputType(enInputPort);

        if(tmds_port[enInputPort].InputVideoMode == 0) //DVI mode
        {
            if(mhal_tmds_TimingChg(enInputPort))
            {
                DRV_TMDS_PrtMsg("Combo Timing CHG");

                mhal_tmds_HDCPFrameClear(enInputPort, TRUE);

                tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_RGB;

                mhal_tmds_reset_status(enInputPort, TRUE, 0xDD);
            }
        }
        else
        {
            mhal_tmds_HDCPFrameClear(enInputPort, FALSE);

            DRV_TMDS_PrtMsg("not support HDMI mode in DVI port!!!"); //temp
        }
    }
    else  //DE unstable
    {
        //do nothing.
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_tmds_DVIDualPollingProc()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void _mdrv_tmds_DVIDualPollingProc(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    Bool bLockFlag = FALSE;
    Bool bResetStatus = FALSE;

    if(mhal_tmds_DE_Stable(enInputPort))//DE stable
    {
        tmds_port[enInputPort].InputVideoMode = mhal_tmds_GetInputType(enInputPort);

        if(tmds_port[enInputPort].InputVideoMode == 0) //DVI mode
        {
            if(mhal_tmds_NoInputClk(enInputPort))
            {
                tmds_port[enInputPort].Main_DEChgRst_flag = FALSE;
                tmds_port[enInputPort].Sub_DEChgRst_flag = FALSE;
                tmds_port[enInputPort].DualLinkDetectFinish_flag = FALSE;
            }

            if(_mdrv_tmds_CheckClockValid((BYTE)enInputPort))
            {
				if(tmds_port[enInputPort].duallink_flag == FALSE)
				{
					mhal_tmds_DualLink_Setting(enInputPort, TRUE); //restore single link setting, so we can get correct VDE info

					tmds_port[enInputPort].duallink_flag = TRUE;
				}
                else
                {
                    DRV_TMDS_PrtMsg("Combo Timing CHG");

                    tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_RGB;

                    if(tmds_port[enInputPort].Main_DEChgRst_flag == FALSE)
                    {
                        mhal_tmds_MainDEChangeReset(enInputPort);

                        tmds_port[enInputPort].Main_DeChgRstCnt = 0;
                        tmds_port[enInputPort].Main_DEChgRst_flag = TRUE;
                    }

                    if(tmds_port[enInputPort].Main_DeChgRstCnt > Main_DEChgRst_BOUND)
                    {
                        tmds_port[enInputPort].Main_DEChgRst_flag = FALSE;

                        if(mhal_tmds_IsMainLinkStable(enInputPort))
                        {
                            if(tmds_port[enInputPort].Sub_DEChgRst_flag == FALSE)
                            {
                                mhal_tmds_SubDEChangeReset(enInputPort);

                                tmds_port[enInputPort].Sub_DeChgRstCnt = 0;
                                tmds_port[enInputPort].Sub_DEChgRst_flag = TRUE;
                            }

                            if(tmds_port[enInputPort].Sub_DeChgRstCnt > Sub_DEChgRst_BOUND)
                            {
                                tmds_port[enInputPort].Sub_DEChgRst_flag = FALSE;

                                if(mhal_tmds_IsDualLink(enInputPort))
                                {
                                    if (tmds_port[enInputPort].isDualCnt != 0)
                                    {
                                        tmds_port[enInputPort].isDualCnt--;
                                        tmds_port[enInputPort].isSingleCnt = DUAL_LINK_DEBOUNCE_CNT;
                                    }
                                    else
                                    {
                                        mhal_tmds_DualLink_Setting(enInputPort, TRUE);

    							        tmds_port[enInputPort].duallink_flag = TRUE;
                                        tmds_port[enInputPort].isDualCnt = DUAL_LINK_DEBOUNCE_CNT; //restore defalut value
    							        tmds_port[enInputPort].IsDVIDualLink = TRUE;

                                        bLockFlag = mhal_tmds_Link_LockCheck(enInputPort,TRUE);
                                        bResetStatus = TRUE;

                                        DRV_TMDS_PrtData("Dual link timing, lock status = 0x%x",bLockFlag);
                                    }
                                }
                                else
                                {
                                    if(tmds_port[enInputPort].isSingleCnt != 0)
                                    {
                                        tmds_port[enInputPort].isSingleCnt--;
                                        tmds_port[enInputPort].isDualCnt = DUAL_LINK_DEBOUNCE_CNT;
                                    }
                                    else
                                    {
                                        mhal_tmds_DualLink_Setting(enInputPort, FALSE);

    							        tmds_port[enInputPort].duallink_flag = FALSE;
                                        tmds_port[enInputPort].isSingleCnt = DUAL_LINK_DEBOUNCE_CNT; //restore defalut value
                                        tmds_port[enInputPort].IsDVIDualLink = FALSE;

                                        bLockFlag = mhal_tmds_Link_LockCheck(enInputPort,FALSE);
                                        bResetStatus = TRUE;

                                        DRV_TMDS_PrtData("Single link timing, lock status = 0x%x",bLockFlag);
                                    }
                                }

                                if(bResetStatus)
                                {
                                    mhal_tmds_reset_status(enInputPort, TRUE, 0xDD);
                                    mhal_tmds_ClearClockStatus(enInputPort);

                                    tmds_port[enInputPort].DualLinkDetectFinish_flag = TRUE;
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            mhal_tmds_HDCPFrameClear(enInputPort, FALSE);

            tmds_port[enInputPort].DualLinkDetectFinish_flag = TRUE;

            DRV_TMDS_PrtMsg("not support HDMI mode in DVI port!!!"); //temp
        }
    }
    else  //DE unstable
    {
        //do nothing.
    }
}
#endif

#if(TMDS_HDCP2_FUNCTION_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_HDCP2Handler()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_HDCP2Handler(MSCombo_TMDS_PORT_INDEX enInputPort)
{
    BYTE ucHDCPRxData[TMDS_HDCP2_RX_QUEUE_SIZE]={0};

    // U11 will bypass HDMI Rx to Tx, thus, even the current input is not HDMI,
    // it is necessary to allow HDCP22 work.
    //if(tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_HDMI)
    //if (gmfcSysInfo.enInputSourceType == INPUT_SOURCE_HDMI)
    {
        // HDCP 2.2 RX
        if(mhal_tmds_HDCP2CheckWriteDone(enInputPort))
        {
            mhal_tmds_HDCP2GetRxData(enInputPort, ucHDCPRxData);

            if(pmdrv_tmds_HDCP2RxEventProc != NULL)  // Have call back function
            {
                pmdrv_tmds_HDCP2RxEventProc((BYTE)enInputPort, ucHDCPRxData);       //pmdrv_tmds_HDCP2RxEventProc = mdrv_combo_HDCP2RxEventProc
            }
        }
    }
}

#endif

#if 0
//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_SetConfiguration()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_SetConfiguration(BYTE ucDVIEnableIndex, BYTE ucDualEnableIndex, BYTE ucHDMIEnableIndex, BYTE ucHDMI2EnableIndex, BYTE ucMHLEnableIndex, BYTE ucDisplayEnableIndex)
{
    MSCombo_TMDS_PORT_INDEX enInputPort;

    tmds_dvi_port = ucDVIEnableIndex;
    tmds_dual_port = ucDualEnableIndex;
    tmds_hdmi_port = ucHDMIEnableIndex;
    tmds_hdmi2_port = ucHDMI2EnableIndex;
    ucTmds_mhl_port = ucMHLEnableIndex;

    for(enInputPort = MSCombo_TMDS_PORT_0; enInputPort <= MSCombo_TMDS_PORT_MAX; enInputPort++)
    {
        if(ucDisplayEnableIndex & (BIT0 << enInputPort))
        {
            tmds_port[enInputPort].port_power= MsCombo_TMDS_POWER_ON;

            if(tmds_hdmi2_port & (BIT0 << enInputPort))
            {
                mhal_tmds_HDMI20_MUX(enInputPort);
            }
        }
        else
        {
            tmds_port[enInputPort].port_power= MsCombo_TMDS_POWER_OFF;
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_Initial()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_Initial(void)
{
    MSCombo_TMDS_PORT_INDEX enInputPort;

    for(enInputPort = MSCombo_TMDS_PORT_0; enInputPort <= MSCombo_TMDS_PORT_MAX; enInputPort++)
    {
        if(tmds_dvi_port & (BIT0 << enInputPort))
        {
            tmds_port[enInputPort].port_type = MsCombo_TMDS_TYPE_DVI;
            tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_RGB;

            mhal_tmds_Initial(enInputPort, FALSE);
            mhal_tmds_MaskComboIRQ(enInputPort, FALSE);
        }
        else if(tmds_dual_port & (BIT0 << enInputPort))
        {
            tmds_port[enInputPort].port_type = MsCombo_TMDS_TYPE_DUAL;
            tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_RGB;

            mhal_tmds_Initial(enInputPort, TRUE);
            mhal_tmds_MaskComboIRQ(enInputPort, FALSE);
        }
        else if(tmds_hdmi_port & (BIT0 << enInputPort))
        {
            tmds_port[enInputPort].port_type = MsCombo_TMDS_TYPE_HDMI;
            tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_DEFAULT;

            mhal_tmds_Initial(enInputPort, FALSE);
            mhal_tmds_MaskComboIRQ(enInputPort, TRUE);
            mhal_tmds_EnableIRQ(enInputPort);
        }
        else if(tmds_hdmi2_port & (BIT0 << enInputPort))
        {
            tmds_port[enInputPort].port_type = MsCombo_TMDS_TYPE_HDMI2;
            tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_DEFAULT;

            mhal_tmds_Initial(enInputPort, FALSE);
            mhal_tmds_MaskComboIRQ(enInputPort, TRUE);
            mhal_tmds_EnableIRQ(enInputPort);
        }
        else
        {
            tmds_port[enInputPort].port_type = MsCombo_TMDS_TYPE_RESERVED;
            tmds_port[enInputPort].input_color.ucColorType = COMBO_COLOR_FORMAT_UNKNOWN;
        }

        tmds_port[enInputPort].input_color.ucColorimetry = COMBO_COLORIMETRY_NONE;
        tmds_port[enInputPort].input_color.ucColorRange = COMBO_COLOR_RANGE_DEFAULT;
        tmds_port[enInputPort].input_color.ucYuvColorimetry = COMBO_YUV_COLORIMETRY_ITU601;

        tmds_port[enInputPort].AudioOutputState = TMDS_AUDIO_STATE_OFF;
        tmds_port[enInputPort].DataOutputState = TMDS_DATA_OUTPUT_OFF;
        tmds_port[enInputPort].AudioOutputEnable = FALSE;
        tmds_port[enInputPort].InputPacketStatus = 0;
        tmds_port[enInputPort].InputPacketError = 0;
        tmds_port[enInputPort].ModeChange = 0;
        tmds_port[enInputPort].ColorChange = 0;
        tmds_port[enInputPort].InputVideoMode = 0;
        tmds_port[enInputPort].InputAVIInfoReceived = 0;
        tmds_port[enInputPort].InputVSPktReceived = 0;
        tmds_port[enInputPort].InputGCPktReceived = 0;
        tmds_port[enInputPort].GetPktCnt = 0;
        tmds_port[enInputPort].AVI_PktLossCnt = 0;
        tmds_port[enInputPort].VS_PktLossCnt = 0;
        tmds_port[enInputPort].GC_PktLossCnt = 0;
        tmds_port[enInputPort].ClrAVMute = TRUE;
        tmds_port[enInputPort].ITContent = FALSE;
        tmds_port[enInputPort].ScalingInfo = 0;
        tmds_port[enInputPort].AudioErrorStatus = 0;
        tmds_port[enInputPort].AudioOffDebunce = 0;
        tmds_port[enInputPort].IsDVIDualLink = FALSE;
        tmds_port[enInputPort].duallink_flag = FALSE;
        tmds_port[enInputPort].isDualCnt = DUAL_LINK_DEBOUNCE_CNT;
        tmds_port[enInputPort].isSingleCnt = DUAL_LINK_DEBOUNCE_CNT;
        tmds_port[enInputPort].Sub_DeChgRstCnt = 0;
        tmds_port[enInputPort].Sub_DEChgRst_flag = FALSE;
        tmds_port[enInputPort].Main_DeChgRstCnt = 0;
        tmds_port[enInputPort].Main_DEChgRst_flag = FALSE;
        tmds_port[enInputPort].DualLinkDetectFinish_flag = FALSE;
        tmds_port[enInputPort].SplitterEnable_Over3G = FALSE;
        tmds_port[enInputPort].SplitterEnable_YUV420 = FALSE;
        tmds_port[enInputPort].ucSourceType = HDMI_SOURCE_VERSION_NOT_SURE;
        GetAVICnt[enInputPort] = 0;
        HDE_Value[enInputPort] = 0;
        AutoEQDoneCnt[enInputPort] = 0;
    }
}

//**************************************************************************
//  [Function Name]:
//                  _mdrv_mhl_CheckDisplayConfig()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_PowerControl(MSCombo_TMDS_PORT_INDEX enInputPort, Bool bFlag)
{
    mhal_tmds_PowerControl(enInputPort, bFlag);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetAudioOutputState()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MsCombo_TMDS_AUD_STATUS mdrv_tmds_GetAudioOutputState(BYTE ucInputPort)
{
    MsCombo_TMDS_AUD_STATUS ucAudioOutputState = TMDS_AUDIO_STATE_OFF;

    if(ucInputPort <= MSCombo_TMDS_PORT_MAX)
    {
        return tmds_port[ucInputPort].AudioOutputState;
    }
    else
    {
        return ucAudioOutputState;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_Handler()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_Handler(void)
{
    static MSCombo_TMDS_PORT_INDEX enInputPort = MSCombo_TMDS_PORT_0;

#if(TMDS_HDCP2_FUNCTION_SUPPORT)
    if((tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_HDMI) && (tmds_port[enInputPort].port_power == MsCombo_TMDS_POWER_ON))
    {
        mdrv_tmds_HDCP2Handler(enInputPort);
    }

#endif

    if(tmds_port[enInputPort].port_power == MsCombo_TMDS_POWER_ON) // Power On
    {
        if(tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_HDMI)
        {
            _mdrv_tmds_HDMIPollingProc(enInputPort);
        }
        else if(tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_DUAL)
        {
            _mdrv_tmds_DVIDualPollingProc(enInputPort);
        }
        else if(tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_DVI)
        {
            _mdrv_tmds_DVIPollingProc(enInputPort);
        }
    }
    else // Power off
    {
        //mdrv_tmds_PowerControl(i, FALSE);
        tmds_port[enInputPort].InputPacketStatus = 0;
        tmds_port[enInputPort].InputPacketError = 0;
        tmds_port[enInputPort].ModeChange = 0;
        tmds_port[enInputPort].ColorChange = 0;
        tmds_port[enInputPort].InputVideoMode= 0;
        tmds_port[enInputPort].AVI_PktLossCnt = 0;
        tmds_port[enInputPort].VS_PktLossCnt = 0;
    }

    if(enInputPort < MSCombo_TMDS_PORT_MAX)
    {
        enInputPort++;
    }
    else
    {
        enInputPort = MSCombo_TMDS_PORT_0;
    }
}
#endif

#if 0
//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_TimerInterrupt()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_TimerInterrupt(void)
{
    MSCombo_TMDS_PORT_INDEX i;

    for(i = MSCombo_TMDS_PORT_0; i <= MSCombo_TMDS_PORT_MAX; i++)
    {
        if(tmds_port[i].port_power == MsCombo_TMDS_POWER_ON)
        {
            if(tmds_port[i].AVI_PktLossCnt <= AviPktLossBound )
            {
                tmds_port[i].AVI_PktLossCnt++;
            }

            if(tmds_port[i].VS_PktLossCnt <= VS_PKT_LOSS_BOUND)
            {
                tmds_port[i].VS_PktLossCnt++;
            }

            if(tmds_port[i].GC_PktLossCnt <= GCP_PKT_LOSS_BOUND)
            {
                tmds_port[i].GC_PktLossCnt++;
            }

            if(tmds_port[i].InputVideoMode && (tmds_port[i].GetPktCnt <= GetPkt_BOUND))
            {
                tmds_port[i].GetPktCnt++;
            }

            if((tmds_port[i].Sub_DEChgRst_flag == TRUE) && (tmds_port[i].Sub_DeChgRstCnt <= Sub_DEChgRst_BOUND))
            {
                tmds_port[i].Sub_DeChgRstCnt++;
            }

            if((tmds_port[i].Main_DEChgRst_flag == TRUE) && (tmds_port[i].Main_DeChgRstCnt <= Main_DEChgRst_BOUND))
            {
                tmds_port[i].Main_DeChgRstCnt++;
            }

            if(AutoEQDoneCnt[i] <= AutoEQDone_BOUND)
            {
                AutoEQDoneCnt[i]++;
            }
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_Set_HPD()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_Set_HPD(BYTE ucComboSelect, Bool bSetHPD)
{
    mhal_tmds_Set_HPD((MSCombo_TMDS_PORT_INDEX)ucComboSelect, bSetHPD);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_Get_Color_Format()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
ST_COMBO_COLOR_FORMAT mdrv_tmds_Get_Color_Format(BYTE ucInputPort)
{
    ST_COMBO_COLOR_FORMAT tmpColorFmt = {COMBO_COLOR_FORMAT_DEFAULT, COMBO_COLOR_RANGE_DEFAULT, COMBO_COLORIMETRY_NONE, COMBO_YUV_COLORIMETRY_ITU601};

    if(ucInputPort < TMDS_INPUT_SELECT_MASK)
    {
        return tmds_port[ucInputPort].input_color;
    }
    else
    {
        return tmpColorFmt;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_ConfigAudioPort()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_ConfigAudioPort(BYTE ucComboPort, Bool bEnableAud)
{
    BYTE i;

    if ((tmds_port[ucComboPort].port_type == MsCombo_TMDS_TYPE_HDMI)&&(bEnableAud == TRUE))
    {
        msWriteByteMask( REG_162F2A, 0 ,BIT4 );    // For DP port
        mhal_tmds_ConfigAudioPort((MSCombo_TMDS_PORT_INDEX)ucComboPort);
        tmds_port[ucComboPort].AudioOutputEnable = TRUE;

	    for (i=0; i <= MSCombo_TMDS_PORT_MAX; i++)
	    {
			tmds_port[i].AudioOutputState = TMDS_AUDIO_STATE_OFF;
    	}

        //clear other ports' status
        for (i=0; i <= MSCombo_TMDS_PORT_MAX; i++)
        {
            if (i != ucComboPort)
            {
                tmds_port[i].AudioOutputEnable = FALSE;
            }
        }
    }
    else
    {
        for (i=0; i <= MSCombo_TMDS_PORT_MAX; i++)
		{
            tmds_port[i].AudioOutputEnable = FALSE;
			tmds_port[i].AudioOutputState = TMDS_AUDIO_STATE_OFF;
		}
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_Input_Is_HDMI()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mdrv_tmds_Input_Is_HDMI(BYTE ucInputPort)
{
    if(ucInputPort < TMDS_INPUT_SELECT_MASK)
    {
        return tmds_port[ucInputPort].InputVideoMode;
    }
    else
    {
        return 0;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetScaling_Info()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mdrv_tmds_GetScaling_Info(BYTE ucInputPort)
{
    if(ucInputPort < TMDS_INPUT_SELECT_MASK)
    {
        return tmds_port[ucInputPort].ScalingInfo;
    }
    else
    {
        return 0;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetITContent()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mdrv_tmds_GetITContent(BYTE ucInputPort)
{
    if(ucInputPort < TMDS_INPUT_SELECT_MASK)
    {
        return tmds_port[ucInputPort].ITContent;
    }
    else
    {
        return 0;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetPacketContent()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_GetPacketContent(BYTE ucInputPort, EN_PACKET_DEFINE_TYPE ucPacketType, BYTE ucPacketLength, BYTE *pPacketData)
{
    //return all zero data if ucInputPort value is invalid
    BYTE i;

    for (i=0; i < ucPacketLength; i++)
    {
        *(pPacketData + i) = 0;
    }

    if(ucInputPort <= MSCombo_TMDS_PORT_MAX)
    {
        WORD wPktStatus = 0;
        Bool bPktReceived = FALSE;

        wPktStatus = tmds_port[ucInputPort].InputPacketStatus;

        //no packet received
        if (wPktStatus == 0)
            return;
        else
        {
            switch (ucPacketType)
            {
                case COMBO_PACKET_NULL:
                    if (wPktStatus & _BIT8)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_AUDIO_CLOCK_REGENERATION:
                    if (wPktStatus & _BIT6)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_AUDIO_SAMPLE:
                    if (wPktStatus & _BIT5)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_GENERAL_CONTROL:
                    if (wPktStatus & _BIT4)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_ACP_PACKET:
                    if (wPktStatus & _BIT11)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_ISRC1_PACKET:
                    if (wPktStatus & _BIT10)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_ISRC2_PACKET:
                    if (wPktStatus & _BIT9)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_ONE_BIT_AUDIO_SAMPLE:
                    //TBD: not support?
                break;
                case COMBO_PACKET_DST_AUDIO:
                    if (wPktStatus & _BIT12)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_HBR_AUDIO_STREAM:
                    if (wPktStatus & _BIT15)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_GAMUT_METADATA:
                    if (wPktStatus & _BIT14)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_VS_INFOFRAME:
                    if (wPktStatus & _BIT7)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_AVI_INFOFRAME:
                    if (wPktStatus & _BIT3)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_SPD_INFOFRAME:
                    if (wPktStatus & _BIT2)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_AUD_INFOFRAME:
                    if (wPktStatus & _BIT1)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_MPEG_INFOFRAME:
                    if (wPktStatus & _BIT0)
                        bPktReceived = TRUE;
                break;
                case COMBO_PACKET_DP_MISC:
                default:
                    //not support here
                break;
            }

            if (bPktReceived == TRUE)
                mhal_tmds_GetPacketContent((MSCombo_TMDS_PORT_INDEX)ucInputPort, ucPacketType, ucPacketLength, pPacketData);
            else
                return;
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_DetectCablePlug()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mdrv_tmds_DetectCablePlug(BYTE ucInputPort)
{
    BYTE bCableDetect = 0;

    bCableDetect = mhal_tmds_DetectCablePlug((MSCombo_TMDS_PORT_INDEX)ucInputPort, GET_TMDS_MHL_ENABLE_PORT(ucInputPort));

    if(bCableDetect == TMDS_CABLE_DETECT_HDMI)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_Clock_Stable()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
Bool mdrv_tmds_Clock_Stable(BYTE enInputPort)
{
    if(tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_DUAL)
    {
        if(tmds_port[enInputPort].DualLinkDetectFinish_flag == TRUE)
            return mhal_tmds_Clock_Stable((MSCombo_TMDS_PORT_INDEX)enInputPort);
        else
            return FALSE;
    }
    else
    {
        if(mhal_tmds_Clock_Stable((MSCombo_TMDS_PORT_INDEX)enInputPort))
		    return mhal_tmds_Link_LockCheck((MSCombo_TMDS_PORT_INDEX)enInputPort, FALSE);
        else
            return FALSE;
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetAudioFreq()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MScombo_TMDS_AUD_FREQ_INDEX mdrv_tmds_GetAudioFreq(BYTE enInputPort)
{
    return mhal_tmds_GetAudioFreq((MSCombo_TMDS_PORT_INDEX)enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_IsAudioFmtPCM()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MSCombo_TMDS_AUDIO_FORMAT mdrv_tmds_IsAudioFmtPCM(BYTE enInputPort)
{
    //if this port is not enabled, then it has no audio clock, which will cause audio channel status register has unreliable value;
    if ( tmds_port[enInputPort].AudioOutputEnable == FALSE )
        return MSCombo_AUDIO_FMT_UNKNOWN;

    return mhal_tmds_IsAudioFmtPCM((MSCombo_TMDS_PORT_INDEX)enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetColorDepthInfo()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MSCombo_TMDS_COLOR_DEPTH_FORMAT mdrv_tmds_GetColorDepthInfo(BYTE enInputPort)
{
    if (tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_HDMI)
        return mhal_tmds_GetColorDepthInfo((MSCombo_TMDS_PORT_INDEX)enInputPort);
    else
        return MSCombo_TMDS_COLOR_DEPTH_UNKNOWN;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetPixelRepetitionInfo()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MSCombo_TMDS_PIXEL_REPETITION mdrv_tmds_GetPixelRepetitionInfo(BYTE enInputPort)
{
    if (tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_HDMI)
        return mhal_tmds_GetPixelRepetitionInfo((MSCombo_TMDS_PORT_INDEX)enInputPort);
    else
        return MSCombo_TMDS_RESERVED_PIX_REP;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetClockRate()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
WORD mdrv_tmds_GetClockRate(BYTE enInputPort)
{
    return mhal_tmds_GetClockRate((MSCombo_TMDS_PORT_INDEX)enInputPort);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_ISR()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_ISR(void)
{
    BYTE ucInputPort;

    for ( ucInputPort = MSCombo_TMDS_PORT_0; ucInputPort <= MSCombo_TMDS_PORT_MAX; ucInputPort++ )
    {
        if (tmds_port[ucInputPort].port_type == MsCombo_TMDS_TYPE_HDMI)
        {
            mhal_tmds_ISR((MSCombo_TMDS_PORT_INDEX)ucInputPort, GET_TMDS_MHL_ENABLE_PORT(ucInputPort));

            if(mhal_tmds_GetNoInputFlag((MSCombo_TMDS_PORT_INDEX)ucInputPort))
            {

            }
        }
    }
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_SetMonochromeMode()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_SetMonochromeMode(BYTE enInputPort, Bool bEnable, Bool bFlag, MSCombo_TMDS_MONO_BIT ucBits)
{
    mhal_tmds_SetMonochromeMode((MSCombo_TMDS_PORT_INDEX)enInputPort, bEnable, bFlag, ucBits);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_DVIDeepColorSetting()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_DVIDeepColorSetting(BYTE enInputPort, Bool bEnable, MSCombo_TMDS_DVI_DEEP_COLOR ucBits)
{
    mhal_tmds_DVIDeepColorSetting((MSCombo_TMDS_PORT_INDEX)enInputPort, bEnable, ucBits);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetSplitFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL mdrv_tmds_GetSplitFlag(BYTE enInputPort)
{
    if((tmds_port[enInputPort].SplitterEnable_Over3G == TRUE) || (tmds_port[enInputPort].SplitterEnable_YUV420== TRUE))
        return TRUE;
    else
        return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_CheckAVMuteINT()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL mdrv_tmds_CheckAVMuteINT(BYTE enInputPort, Bool bClr)
{
    return mhal_tmds_CheckAVMuteINT((MSCombo_TMDS_PORT_INDEX)enInputPort, bClr);
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_CheckAudioStatus()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL mdrv_tmds_CheckAudioStatus(BYTE enInputPort)
{
    if (tmds_port[(MSCombo_TMDS_PORT_INDEX)enInputPort].port_type == MsCombo_TMDS_TYPE_HDMI)
    {
        if ((tmds_port[(MSCombo_TMDS_PORT_INDEX)enInputPort].InputPacketStatus & (BIT5 | BIT6)) == (BIT5 | BIT6) )
            return TRUE;
        else
            return FALSE;
    }
    else
        return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_IsDVIDualLink()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BOOL mdrv_tmds_IsDVIDualLink(BYTE enInputPort)
{
	if (tmds_port[(MSCombo_TMDS_PORT_INDEX)enInputPort].port_type == MsCombo_TMDS_TYPE_DUAL)
		return tmds_port[enInputPort].IsDVIDualLink;
	else
		return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_GetSourceVersionType()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
BYTE mdrv_tmds_GetSourceVersionType(BYTE enInputPort)
{
	return tmds_port[enInputPort].ucSourceType;
}
#endif

#if(TMDS_HDCP2_FUNCTION_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_SetHDCP2CallBackFunction()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_SetHDCP2CallBackFunction(TMDS_HDCP2_CALL_BACK_FUNC pHDCP2RxFunc, BYTE *pHDCP2CertRx)
{
    pmdrv_tmds_HDCP2RxEventProc = pHDCP2RxFunc;
    pHDCPTxData_CertRx = pHDCP2CertRx;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_tmds_HDCP2TxEventProc()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mdrv_tmds_HDCP2TxEventProc(BYTE enInputPort, BYTE ucMessageID, BYTE ucDataSize, BYTE *pHDCPTxData)
{
    if(ucDataSize <= TMDS_HDCP2_TX_QUEUE_SIZE)
    {
        // U11 will bypass HDMI Rx to Tx, thus, even the current input is not HDMI,
        // it is necessary to allow HDCP22 work.
        //if(tmds_port[enInputPort].port_type == MsCombo_TMDS_TYPE_HDMI)
        //if (gmfcSysInfo.enInputSourceType == INPUT_SOURCE_HDMI)
        {
            // HDCP 2.2 TX
            //D printf("check write start\r\n");
            if(!mhal_tmds_HDCP2CheckWriteStart((MSCombo_TMDS_PORT_INDEX)enInputPort))
            {
                //D printf("send tx data \r\n");
                mhal_tmds_HDCP2SetTxData((MSCombo_TMDS_PORT_INDEX)enInputPort, ucMessageID, ucDataSize, pHDCPTxData, pHDCPTxData_CertRx);
            }
        }
    }
    else
    {
        DRV_TMDS_PrtData(" TMDS HDCP2.2 Tx queue size too small port %d", enInputPort);
    }
}

#endif

#endif // ENABLE_SECURITY_R2_HDCP22

