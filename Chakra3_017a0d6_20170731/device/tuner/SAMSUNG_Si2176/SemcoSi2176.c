/********************************************************************
* SemcoSi2176.c
* Si2176 Function
* By yooheeyong 2010/05/23
*********************************************************************/
#define Si2176_COMMAND_PROTOTYPES   /* include all Si2176 API command prototypes in "Commands.h" */

#include "SemcoSi2176.h"

#include "UserDefinedIIC.h"
#include "drvIIC.h"


#ifndef UNUSED_SAMSUNG //to avoid compile warnings...
#define UNUSED_SAMSUNG(var) ((var) = (var))
#endif

Si2176Config  Si2176Cfg;

static int nBeforeStep; /* add code for MFT by yooheeyong 20101025 */

/* MFT 관련 추가 변수, by yooheeyong 20101028 */
static unsigned long nLocked_Freq, nCenter_Freq;
static int nCriteriaStep, nLeftMax, nRightMax;

char Si2176_dtv_lifout_amp = 24;

/* 절대값 반환 */
int ABS_SEMCO(int x){
  if(x>0)
     return x;
  else
     return -x;

  return x;
}

/* Initialize Si2176 */
/* 크리스탈 외부 또는 내부 사용하는지 판단 : bXTal_Internal_External - XTAL_INTERNAL/XTAL_EXTERNAL */
int Si2176_Initialize(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp, Si2176_PropObj *lpprop,unsigned char bXTal_Internal_External)
{
int ret;

  /* L0  (I2C Communication) Context */
  L0_Context Si2176_L0;
    Si2176_L1_API_Init(lpSi2176, &Si2176_L0, SI2176_ADDRESS);

    if((ret = Si2176_PowerUpWithPatch(lpSi2176)) != 0)
        {
            printf("%lu:%s; rtn=%u\n", __LINE__, __FILE__, ret);

    return ret;
        }
  else{}

    /* Requester : Kwon Jeoung Hun */

  if((ret = configureSi2176(lpSi2176,lprsp,lpprop,bXTal_Internal_External)) != 0)   /*set up the DTV and ATV */
       {
    return ret;
       }
  else{}

  nBeforeStep = 0xff; /* add code for MFT by yooheeyong 20101025 */

    /* MFT 관련 추가 변수 초기화 , by yooheeyong 20101028 */
    nLocked_Freq = nCenter_Freq = 0;

  return 0;
}


/* Set Configuration */
/* 크리스탈 외부 또는 내부 사용하는지 판단 : bXTal_Internal_External - XTAL_INTERNAL/XTAL_EXTERNAL */
unsigned char Si2176_Configure(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop, unsigned char bXTal_Internal_External)
{
    //printf("  Si2176_Configure(aud=%u, vid=%u)\n", Si2176Cfg.nSel_atv_audio_mode_audio_sys,
    //                                            Si2176Cfg.nSel_atv_video_mode_video_sys);

  /* TUNER_TUNE_FREQ_CMD_struct tuner_tune_freq; */
  unsigned char wait_for_cts = 0;   /* global flag for CTS checking prior to sending a Si2170 API Command */
  /* default is no CTS check prior to sending Si2170 API Command */
  unsigned char wait_for_response = 1;    /* global flag for CTS checking and Response readback after sending Si2170 API Command */
    /* default is CTS check and Reponse readback after sending Si2170 API Command */

    /* Setting DTV_CONFIG_IF_PORT_PROP property */
  switch(Si2176Cfg.nSel_dtv_out_type)
  {
      case 0:
      lpprop->dtv_config_if_port.dtv_out_type   = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1;  /* Use DLIF (LIF_IF1) */
        break;
      case 1:
      lpprop->dtv_config_if_port.dtv_out_type   = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF2;  /* Use DLIF (LIF_IF2) */
        break;
      case 2:
      lpprop->dtv_config_if_port.dtv_out_type   = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_SE_IF1A;  /* Use DLIF (LIF_SE_IF1A) */
        break;
      case 3:
      lpprop->dtv_config_if_port.dtv_out_type   = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_SE_IF2A;  /* Use DLIF (LIF_SE_IF2A) */
        break;
    default:
    break;
  }

  switch(Si2176Cfg.nSel_dtv_agc_source)
  {
      case 0:
      lpprop->dtv_config_if_port.dtv_agc_source = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_INTERNAL; /* Use internal AGC only */
    break;
      case 1:
      lpprop->dtv_config_if_port.dtv_agc_source = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_DLIF_AGC_3DB; /* Use DLIF AGC 3DB */ /* modify definitin keyword from new library 3.2 by yooheeyong 20100811*/
    break;
    case 2: /* add by yooheeyong from new library v3.2 20100811 */
      lpprop->dtv_config_if_port.dtv_agc_source = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_DLIF_AGC_FULL;  /* Use DLIF AGC 3DB */
    break;
    default:
    break;
  }

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_DTV_CONFIG_IF_PORT_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}

    /* Setting DTV_LIF_FREQ_PROP */
    lpprop->dtv_lif_freq.offset =  Si2176Cfg.nSel_dtv_lif_freq_offset;  //4063;   /* set DLIF center frequency (to 5MHz) */

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_DTV_LIF_FREQ_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}

  /* Setting DTV_LIF_OUT_PROP for DBook ACI */
  lpprop->dtv_lif_out.offset  = 148;
  lpprop->dtv_lif_out.amp  = Si2176_dtv_lifout_amp;

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_DTV_LIF_OUT_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}

    /* Setting DTV_MODE_PROP property */
  switch(Si2176Cfg.nSel_dtv_mode_bw)
  {
    case 6:
      lpprop->dtv_mode.bw = Si2176_DTV_MODE_PROP_BW_BW_6MHZ;        /* DTV BW 6MHz */
    break;
    case 7:
      lpprop->dtv_mode.bw = Si2176_DTV_MODE_PROP_BW_BW_7MHZ;        /* DTV BW 7MHz */
    break;
    case 8:
      lpprop->dtv_mode.bw = Si2176_DTV_MODE_PROP_BW_BW_8MHZ;        /* DTV BW 8MHz */
    break;
    default:
    break;
  }

  switch(Si2176Cfg.nSel_dtv_mode_invert_spectrum)
  {
    case 0:
      lpprop->dtv_mode.invert_spectrum = Si2176_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL; /* Non-inverted spectrum */
    break;
    case 1:
      lpprop->dtv_mode.invert_spectrum = Si2176_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED; /* inverted spectrum */
    break;
    default:
    break;
  }

  switch(Si2176Cfg.nSel_dtv_mode_modulation)
  {
    case SEMCO_DTV_MODE_ATSC:
      lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_ATSC;     /* ATSC DTV demodulation */
    break;
    case SEMCO_DTV_MODE_QAM_US:
      lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_QAM_US;   /* QAM_US DTV demodulation */
    break;
    case SEMCO_DTV_MODE_DVBT:
      lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_DVBT;     /* DVBT DTV demodulation */
    break;
    case SEMCO_DTV_MODE_DVBC:
      lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_DVBC;     /* DVBC DTV demodulation */
    break;
    case SEMCO_DTV_MODE_ISDBT:
      lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_ISDBT;    /* ISDBT DTV demodulation */
    break;
    case SEMCO_DTV_MODE_ISDBC:
      lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_ISDBC;    /* ISDBC DTV demodulation */
    break;
    case SEMCO_DTV_MODE_DTMB: // for DTMB add by yooheeyong 20100813
      lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_DTMB;     /* DTMB demodulation */
    break;
    default:
    break;
  }

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_DTV_MODE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}

    /* Requester : Kwon Jeoung Hun */
  /* modify code by yooheeyong 20101006 */
  /* use the external xtal */
  if(bXTal_Internal_External == SI2176_XTAL_EXTERNAL)
  {
     /* Setting CONFIG_PINS */
    if (Si2176_L1_CONFIG_PINS (lpSi2176, wait_for_cts, wait_for_response,   /* turn off BCLK1 and XOUT */
                      Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_BCLK1_MODE_XOUT,  // 20100818 jhkwon
              Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
              rsp) !=0) {
      return ERROR_Si2176_SENDING_COMMAND;
    }else{}
  }else{
     /* Setting CONFIG_PINS */
    if (Si2176_L1_CONFIG_PINS (lpSi2176, wait_for_cts, wait_for_response,   /* turn off BCLK1 and XOUT */
                      Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,
              Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
              rsp) !=0) {
      return ERROR_Si2176_SENDING_COMMAND;
    }else{}
  }

    /* Setting ATV_VIDEO_MODE_PROP property */
  switch(Si2176Cfg.nSel_atv_video_mode_video_sys)
  {
    case SEMCO_TUNE_ANALOG_B:
        lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;    /* B ATV demodulation */
    break;
    case SEMCO_TUNE_ANALOG_G:
            lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;   /* GH ATV demodulation */
    break;
    case SEMCO_TUNE_ANALOG_M:
        lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;    /* M ATV demodulation */
    break;
    case SEMCO_TUNE_ANALOG_N:
        lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N;      /* N ATV demodulation */
    break;
    case SEMCO_TUNE_ANALOG_I:
        lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;    /* I ATV demodulation */
    break;
    case SEMCO_TUNE_ANALOG_DK:
        lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;     /* DK ATV demodulation */
    break;
    case SEMCO_TUNE_ANALOG_L:
        lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;    /* L ATV demodulation */
    break;
    case SEMCO_TUNE_ANALOG_LP:
        lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;     /* LP ATV demodulation */
    break;
    default:
    break;
  }


  if(Si2176Cfg.nSel_atv_atv_video_mode_tran == 0)
  {
    // Terrestrial 설정됨. 20100705 by yooheeyong
    lpprop->atv_video_mode.trans = Si2176_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;
  }else{
    // Cable 설정됨. 20100705 by yooheeyong
    lpprop->atv_video_mode.trans = Si2176_ATV_VIDEO_MODE_PROP_TRANS_CABLE;

  }

  switch(Si2176Cfg.nSel_atv_video_mod_color)
  {
    case 0:
        lpprop->atv_video_mode.color     = Si2176_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC; /* PAL_NTSC color system */
    break;
    case 1:
        lpprop->atv_video_mode.color     = Si2176_ATV_VIDEO_MODE_PROP_COLOR_SECAM;    /* SECAM color system */
    break;
    default:
    break;
  }

/*
  switch(Si2176Cfg.nSel_atv_mode_invert_spectrum)
  {
    case 0:
      lpprop->atv_video_mode.invert_spectrum = Si2176_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_NORMAL; // Non-inverted spectrum
    break;
    case 1:
      lpprop->atv_video_mode.invert_spectrum = Si2176_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED; // inverted spectrum
    break;
    default:
    break;
  }
*/

  switch(Si2176Cfg.nSel_atv_mode_invert_signal)
  {
    case 0:
      lpprop->atv_video_mode.invert_signal = Si2176_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_NORMAL; /* Non-inverted signal */
    break;
    case 1:
      lpprop->atv_video_mode.invert_signal = Si2176_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_INVERTED; /* inverted signal */
    break;
    default:
    break;
  }

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_VIDEO_MODE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}


  /* Setting ATV_AUDIO_MODE_PROP property */
  switch(Si2176Cfg.nSel_atv_audio_mode_audio_sys)
  {
    case SEMCO_ANALOG_AUDIO_RSVD:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT;
    break;
    case SEMCO_ANALOG_AUDIO_MONO:
            lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MONO;
    break;
    case SEMCO_ANALOG_AUDIO_MONO_NICAM:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MONO_NICAM;
    break;
    case SEMCO_ANALOG_AUDIO_A2:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2;
    break;
    case SEMCO_ANALOG_AUDIO_A2_DK2:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK2;
    break;
    case SEMCO_ANALOG_AUDIO_A2_DK3:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK3;
    break;
    case SEMCO_ANALOG_AUDIO_BTSC:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_BTSC;
    break;
    case SEMCO_ANALOG_AUDIO_EIAJ:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_EIAJ;
    break;
    case Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_SCAN:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_SCAN;
    break;
    case Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK4:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK4;
    break;
    case Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_WIDE_SCAN:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_WIDE_SCAN;
    break;
    default:
    break;
  }

    /* Setting ATV_AUDIO_MODE_PROP property */
  switch(Si2176Cfg.nSel_atv_video_mode_video_sys)
  {
    case SEMCO_TUNE_ANALOG_B:
    case SEMCO_TUNE_ANALOG_G:
    case SEMCO_TUNE_ANALOG_DK:
      lpprop->atv_audio_mode.chan_bw = Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_8X_OVERMOD;
    break;
    case SEMCO_TUNE_ANALOG_M:
    case SEMCO_TUNE_ANALOG_N:
    case SEMCO_TUNE_ANALOG_I:
    case SEMCO_TUNE_ANALOG_L:
    case SEMCO_TUNE_ANALOG_LP:
      lpprop->atv_audio_mode.chan_bw = Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT;
    break;
    default:
      lpprop->atv_audio_mode.chan_bw = Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT;
    break;
  }

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_AUDIO_MODE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}

   ////////////////////////////////////////////////////////////////////////
   /*     added by kimnammin 100806   amp 25~100, amp_default=100, offset -128~127 offset_default 0*/
   lpprop->atv_cvbs_out_fine.amp= Si2176Cfg.nSel_atv_cvbs_out_fine_amp;
   lpprop->atv_cvbs_out_fine.offset = Si2176Cfg.nSel_atv_cvbs_out_fine_offset;
   if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_FINE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
   }else{}

    // added by yooheeyong 20100816
    // amp 0 ~ 255, default = 60, offset 0 ~ 255, default = 135
    lpprop->atv_sif_out.offset = Si2176Cfg.nSel_atv_sif_out_offset;
    lpprop->atv_sif_out.amp    = Si2176Cfg.nSel_atv_sif_out_amp;
    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}

#if 0
   lpprop->atv_cvbs_out.amp= 100;
   lpprop->atv_cvbs_out.offset = 25;
   if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
   }else{}

#endif

/////////////////////////////////////////////////////////////////////////

   lpprop->dtv_agc_speed.agc_decim = 0;  /* add agc_decim by yooheeyong 20101025 */
   switch(Si2176Cfg.if_agc_speed)
   {
      case 0:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
    break;
    case 1:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_89;
    break;
    case 2:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_105;
    break;
    case 3:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_121;
    break;
    case 4:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_137;
    break;
    case 5:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_158;
    break;
    case 6:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_172;
    break;
    case 7:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_185;
    break;
    case 8:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_196;
    break;
    case 9:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_206;
    break;
    case 10:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_216;
    break;
    case 11:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_219;
    break;
    case 12:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_222;
    break;
    default:
    break;
   }

   /* Setting DTV_AGC_SPEED by yooheeyong 20100601*/
   if(Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_DTV_AGC_SPEED_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
   }else{}

    return 0;

}

/* Reset AGC Speed */
unsigned char Si2176_Configure_AGC_RESET(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop)
{
  unsigned char wait_for_cts = 0;
  unsigned char wait_for_response = 1;

   lpprop->dtv_agc_speed.agc_decim = 0;
   Si2176Cfg.if_agc_speed = 0;
   switch(Si2176Cfg.if_agc_speed)
   {
      case 0:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
    break;
    case 1:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_89;
    break;
    case 2:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_105;
    break;
    case 3:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_121;
    break;
    case 4:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_137;
    break;
    case 5:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_158;
    break;
    case 6:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_172;
    break;
    case 7:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_185;
    break;
    case 8:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_196;
    break;
    case 9:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_206;
    break;
    case 10:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_216;
    break;
    case 11:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_219;
    break;
    case 12:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_222;
    break;
    default:
    break;
   }

   /* Setting DTV_AGC_SPEED by yooheeyong 20100601*/
   if(Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_DTV_AGC_SPEED_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
   }else{}
    return 0;
}
/* Set FEF AGC Speed */
unsigned char Si2176_Configure_AGC_FEF(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop)
{
  unsigned char wait_for_cts = 0;
  unsigned char wait_for_response = 1;

   lpprop->dtv_agc_speed.agc_decim = 3;
   Si2176Cfg.if_agc_speed = 1;
   switch(Si2176Cfg.if_agc_speed)
   {
      case 0:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
    break;
    case 1:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_89;
    break;
    case 2:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_105;
    break;
    case 3:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_121;
    break;
    case 4:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_137;
    break;
    case 5:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_158;
    break;
    case 6:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_172;
    break;
    case 7:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_185;
    break;
    case 8:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_196;
    break;
    case 9:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_206;
    break;
    case 10:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_216;
    break;
    case 11:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_219;
    break;
    case 12:
         lpprop->dtv_agc_speed.if_agc_speed = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_222;
    break;
    default:
    break;
   }

   /* Setting DTV_AGC_SPEED by yooheeyong 20100601*/
   if(Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_DTV_AGC_SPEED_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
   }else{}

    return 0;
}

/* Set Frequency */
/* MFT 관련 파라메터 추가(nCenterFrequency_KHz), by yooheeyong 20101028 */
unsigned char Si2176_SetFrequency(unsigned char nDTV_ATV, L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp, unsigned long nFrequency_KHz, unsigned long nCenterFrequency_KHz, int bTunTINTCheck)
{

    //printf("  Si2176_SetFrequency(Std=%u, Freq=%u)\n", nDTV_ATV, nFrequency_KHz);

        UNUSED(bTunTINTCheck);
   int ret;
  // int count;
   //Si2176_COMMON_REPLY_struct status;
   unsigned char wait_for_cts = 0;    /* global flag for CTS checking prior to sending a Si2176 API Command */
   /* default is no CTS check prior to sending Si2176 API Command */
   unsigned char wait_for_response = 1;    /* global flag for CTS checking and Response readback after sending Si2176 API Command */
     /* default is CTS check and Reponse readback after sending Si2176 API Command */

     /* MFT 관련 변수에 주파수 할당, by yooheeyong 20101116 */
     /*-------------------------------------------------------*/
   nLocked_Freq = nFrequency_KHz;
   nCenter_Freq = nCenterFrequency_KHz;
     nCriteriaStep =  (((int)(nLocked_Freq - nCenter_Freq))*1000)/62500;

   /* 우측 플러스 방향 한계치 구함 */
     nRightMax = 32 + nCriteriaStep;
   if(nRightMax > 32)
    nRightMax = 32;

   /* 좌측 마이너스 방향 한계치 구함 */
   nLeftMax = -32 + nCriteriaStep;
   if(nLeftMax < -32)
         nLeftMax = -32;

   nBeforeStep = nCriteriaStep;//nStep;
   /*-------------------------------------------------------*/

   ret = 1;

    /* Requester : Jang In Jong */
  /* add code by yooheeyong 20101026 */
  /* use the external xtal for digital or disable xtal for analog */
  /*------------------------ begin -------------------------------*/
  if(nDTV_ATV == SEMCO_TUNE_DIGITAL)
  {
     /* Setting CONFIG_PINS */
    if (Si2176_L1_CONFIG_PINS (lpSi2176, wait_for_cts, wait_for_response,   /* turn off BCLK1 and XOUT */
                  Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                  Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                  Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                  Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                  Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                  Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                  Si2176_CONFIG_PINS_CMD_BCLK1_MODE_XOUT,  // 20100818 jhkwon
                  Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                  Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
                  lprsp) !=0) {
      return ERROR_Si2176_SENDING_COMMAND;
    }else{}
  }else{
     /* Setting CONFIG_PINS */
    if (Si2176_L1_CONFIG_PINS (lpSi2176, wait_for_cts, wait_for_response,   /* turn off BCLK1 and XOUT */
                  Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                  Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                  Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                  Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                  Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                  Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                    Si2176_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,
                  Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                        Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
                        lprsp) !=0) {
      return ERROR_Si2176_SENDING_COMMAND;
    }else{}
  }
  /*------------------------ end -------------------------------*/

   // 2010년 9월 3일 추가
   //-------------------------------------
   switch(nDTV_ATV)
   {
     case SEMCO_TUNE_DIGITAL:   /* Digital */
         ret = Tune(lpSi2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV, lprsp,nFrequency_KHz*1000);
     break;

     case SEMCO_TUNE_ANALOG_B:  /* Analog PAL B */
           nFrequency_KHz += 2250;        /* pal b case : plus 2.25 Mhz for center freq. */
         ret = Tune(lpSi2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, lprsp,nFrequency_KHz*1000);
     break;

     case SEMCO_TUNE_ANALOG_G:  /* Analog PAL G/I/DL/SECAM L */
     case SEMCO_TUNE_ANALOG_I:
     case SEMCO_TUNE_ANALOG_DK:
     case SEMCO_TUNE_ANALOG_L:
         nFrequency_KHz += 2750;        /* pal g / i / dk / secam l case : plus 2.75 Mhz for center freq. */
         ret = Tune(lpSi2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, lprsp,nFrequency_KHz*1000);
     break;

     case SEMCO_TUNE_ANALOG_M:  /* nt */
     case SEMCO_TUNE_ANALOG_N:
        //nFrequency_KHz += 1750;        /* nt case : plus 1.75 Mhz for center freq. */ // do comment by yooheeyong 20110719
        ret = Tune(lpSi2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, lprsp,nFrequency_KHz*1000);
     break;

     case SEMCO_TUNE_ANALOG_LP: /* secam lp */
        nFrequency_KHz -= 2750;        /* secam lp case : minus 2.75 Mhz for center freq. */
        ret = Tune(lpSi2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, lprsp,nFrequency_KHz*1000);
     break;

     default:
       return 0;
   }
   //-------------------------------------

   /* Requester : Kwon Jeoung Hun */
   /* Si2176_SetFrequency() 함수 call 이후 Auto 또는 manual tune에 따라 delay() 적용 결정 */
   /* Manual Tune시 아날로그 경우 : max delay 300ms, 디지털 경우 : max delay 100ms  */
   /* Auto Scan시 delay 시간은 전자 VD 자체 타임아웃이 일반적으로 1.5초 설정이므로 굳이 delay 필요 없음 */
  /* The following wait for TUNINT will only work if: */
  /*  in all modes: prop.master_ien.tunien = Si2176_MASTER_IEN_PROP_TUNIEN_ON   */
  /*  in ATV mode : prop.master_ien.atvien = Si2176_MASTER_IEN_PROP_ATVIEN_ON   */
  /*  in DTV mode : prop.master_ien.dtvien = Si2176_MASTER_IEN_PROP_DTVIEN_ON   */
  /*  in DTV mode : prop.tuner_ien.tcien   = Si2176_TUNER_IEN_PROP_TCIEN_ENABLE */
  /* wait for TUNINT, timeout is 100ms */
#if 0
    if(bTunTINTCheck == 1)
  {
    for (count=50; count ;count--)
    {
      if ((ret = CheckStatus(lpSi2176, &status)) != 0)
        return ret;
      if (status.tunint)
        break;
      system_wait(2);

    }

    if (!count)
      return ERROR_Si2176_TUNINT_TIMEOUT;
  }
#endif
  if(ret != 0)
  {
     return 0;
     }
  else
  {
     return 1;
  }

}

/* Check Tuner status */
unsigned char Si2176_GetTunerStatus(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp)
{
   return(TunerStatus(lpSi2176, lprsp));
}

/* Check Analog status */
unsigned char Si2176_GetAnalogStatus(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp)
{
  unsigned char ret;
  ret = ATVStatus(lpSi2176, lprsp);

  switch(Si2176Cfg.nSel_atv_video_mode_video_sys)
  {
    case SEMCO_TUNE_ANALOG_B:
    case SEMCO_TUNE_ANALOG_G:
    case SEMCO_TUNE_ANALOG_M:
    case SEMCO_TUNE_ANALOG_N:
    case SEMCO_TUNE_ANALOG_I:
    case SEMCO_TUNE_ANALOG_DK:
    case SEMCO_TUNE_ANALOG_L:
    break;
    case SEMCO_TUNE_ANALOG_LP:
        lprsp->atv_status.afc_freq = -(lprsp->atv_status.afc_freq);
    break;
    default:
    break;
  }
   return ret;
}

/* Check Digital status */
unsigned char Si2176_GetDigitalStatus(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp)
{
   return(DTVStatus(lpSi2176, lprsp));
}


/* Si2176 On */
void Si2176_On(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp)
{
   PowerUp(lpSi2176, lprsp);
}


/* Si2173 StandBy */
void Si2176_StandBy(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp)
{
   PowerDown(lpSi2176, lprsp);
}


/* Get Carrier Frequency Offset */
int Si2176_GetCarrierFreqOffset(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp)
{
  int offset;

  ATVStatus(lpSi2176, lprsp);

  offset = lprsp->atv_status.afc_freq;

  return offset;
}

/* Retrun Voltage for carrier freq. offset of AFT */
float Si2176_ReturnVoltage(Si2176_CmdReplyObj  *lprsp)
{
    int offset;

  offset = lprsp->atv_status.afc_freq;

  if( offset >= 1000)
    return 5.0;
  else if(offset >= (int)937.5 &&  offset < (int)1000){
        return 5.0;
  }else if(offset >= (int)875 &&  offset < (int)937.5){
        return 5.0;
  }else if(offset >= (int)812.5 &&  offset < (int)875){
        return 5.0;
  }else if(offset >= (int)750 &&  offset < (int)812.5){
        return 5.0;
  }else if(offset >= (int)687.5 &&  offset < (int)750){
        return 5.0;
  }else if(offset >= (int)625 &&  offset < (int)687.5){
        return 5.0;
  }else if(offset >= (int)562.5 &&  offset < (int)625){
        return 5.0;
  }else if(offset >= (int)500 &&  offset < (int)562.5){
        return 5.0;
  }else if(offset >= (int)437.5 &&  offset < (int)500){
        return 5.0;
  }else if(offset >= (int)375 &&  offset < (int)437.5){
        return 5.0;
  }else if(offset >= (int)312.5 &&  offset < (int)375){
        return 5.0;
  }else if(offset >= (int)250 &&  offset < (int)312.5){
        return 5.0;
  }else if(offset >= (int)187.5 &&  offset < (int)250){
        return 4.84375;
  }else if(offset >= (int)125 &&  offset < (int)187.5){
        return 4.0625;
  }else if(offset >= (int)62.5 &&  offset < (int)125){
        return 3.28125;
  }else if(offset > (int)-62.5 &&  offset < (int)62.5){
        return 2.5;
  }else if(offset >(int)-125 &&  offset <= (int)-62.5){
        return 1.71875;
  }else if(offset > (int)-187.5 &&  offset <= (int)-125){
        return 0.9375;
  }else if(offset > (int)-250 &&  offset <= (int)-187.5){
        return 0.15625;
  }else if(offset > (int)-312.5 &&  offset <= (int)-250){
        return 0.0;
  }else if(offset > (int)-375 &&  offset <= (int)-312.5){
        return 0.0;
  }else if(offset > (int)-437.5 &&  offset <= (int)-375){
        return 0.0;
  }else if(offset > (int)-500 &&  offset <= (int)-437.5){
        return 0.0;
  }else if(offset > (int)-562.5 &&  offset <= (int)-500){
        return 0.0;
  }else if(offset > (int)-625 &&  offset <= (int)-562.5){
        return 0.0;
  }else if(offset > (int)-687.5 &&  offset <= (int)-625){
        return 5;
  }else if(offset > (int)-750 &&  offset <= (int)-687.5){
        return 5;
  }else if(offset > (int)-812.5 &&  offset <= (int)-750){
        return 5;
  }else if(offset > (int)-875 &&  offset <= (int)-812.5){
        return 5;
  }else if(offset > (int)-937.5 &&  offset <= (int)-875){
        return 5;
  }else if(offset > (int)-1000 &&  offset <= (int)-937.5){
        return 5;
  }else if(offset > (int)-1062.5 &&  offset <= (int)-1000){
        return 5;
  }else if(offset > (int)-1125 &&  offset <= (int)-1062.5){
        return 5;
  }else if(offset > (int)-1187.5 &&  offset <= (int)-1125){
        return 5;
  }else if(offset > (int)-1250 &&  offset <= (int)-1187.5){
        return 5;
  }else if(offset > (int)-1312.5 &&  offset <= (int)-1250){
        return 5;
  }else if(offset > (int)-1375 &&  offset <= (int)-1312.5){
        return 5;
  }else if(offset > (int)-1437.5 &&  offset <= (int)-1375){
        return 5;
  }else if(offset > (int)-1500 &&  offset <= (int)-1437.5){
        return 5;
  }else if(offset <= (int)-1500){
        return 5;
  }else{}

     return -1;
}

/* Requester : Jang In Jong */
/* add funtion by yooheeyong 20101006 */
/* modify funtion by yooheeyong 20101025 */
/* Set recommend Amp of a CVBS and a SIF */
unsigned char Si2176_SetAmpForCVBS_SIF(unsigned char nDTV_ATV,L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop)
{
  /* TUNER_TUNE_FREQ_CMD_struct tuner_tune_freq; */
  unsigned char wait_for_cts = 0;   /* global flag for CTS checking prior to sending a Si2170 API Command */
  /* default is no CTS check prior to sending Si2170 API Command */
  unsigned char wait_for_response = 1;    /* global flag for CTS checking and Response readback after sending Si2170 API Command */
    /* default is CTS check and Reponse readback after sending Si2170 API Command */

   switch(nDTV_ATV)
   {

     case SEMCO_TUNE_ANALOG_B:  /* Analog PAL B */
     case SEMCO_TUNE_ANALOG_G:  /* Analog PAL G */
     {
       lpprop->atv_cvbs_out_fine.amp= 53;
       lpprop->atv_cvbs_out_fine.offset = 32;

       if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_FINE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
       }else{}

      #ifdef _MSTAR
      lpprop->atv_sif_out.amp    = 42;
      #endif

      #ifdef _ARSENAL
      lpprop->atv_sif_out.amp    = 95;
      #endif

      lpprop->atv_sif_out.offset = 135;

         if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp) != 0) {
              return ERROR_Si2176_SENDING_COMMAND;
           }else{}

     }
     break;

     case SEMCO_TUNE_ANALOG_I:  /* Analog PAL I */
     {
       lpprop->atv_cvbs_out_fine.amp= 47;
       lpprop->atv_cvbs_out_fine.offset = 32;

       if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_FINE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
       }else{}


      #ifdef _MSTAR
      lpprop->atv_sif_out.amp    = 43;
      #endif

      #ifdef _ARSENAL
      lpprop->atv_sif_out.amp    = 97;
      #endif

      lpprop->atv_sif_out.offset = 135;

         if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp) != 0) {
              return ERROR_Si2176_SENDING_COMMAND;
           }else{}

     }
     break;

     case SEMCO_TUNE_ANALOG_DK: /* Analog DK    */
     {
       lpprop->atv_cvbs_out_fine.amp= 52;
       lpprop->atv_cvbs_out_fine.offset = 32;

       if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_FINE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
       }else{}

      #ifdef _MSTAR
      lpprop->atv_sif_out.amp    = 46;
      #endif

      #ifdef _ARSENAL
      lpprop->atv_sif_out.amp    = 106;
      #endif

      lpprop->atv_sif_out.offset = 135;

         if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp) != 0) {
              return ERROR_Si2176_SENDING_COMMAND;
           }else{}

     }
     break;

     case SEMCO_TUNE_ANALOG_L:  /* Analog SECAM L */
     {
       lpprop->atv_cvbs_out_fine.amp= 48;
       lpprop->atv_cvbs_out_fine.offset = 32;

       if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_FINE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
       }else{}

      #ifdef _MSTAR
      lpprop->atv_sif_out.amp    = 40;
      #endif

      #ifdef _ARSENAL
      lpprop->atv_sif_out.amp    = 95;
      #endif

        lpprop->atv_sif_out.offset = 135;

         if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp) != 0) {
              return ERROR_Si2176_SENDING_COMMAND;
           }else{}


     }
     break;

     case SEMCO_TUNE_ANALOG_LP: /* Analog SECAM LP */
     {
       lpprop->atv_cvbs_out_fine.amp= 48;
       lpprop->atv_cvbs_out_fine.offset = 32;

       if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_FINE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
       }else{}

      #ifdef _MSTAR
      lpprop->atv_sif_out.amp    = 40;
      #endif

      #ifdef _ARSENAL
      lpprop->atv_sif_out.amp    = 95;
      #endif

        lpprop->atv_sif_out.offset = 135;

         if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp) != 0) {
              return ERROR_Si2176_SENDING_COMMAND;
           }else{}

     }
     break;

     case SEMCO_TUNE_ANALOG_M:  /* Analog M */
     case SEMCO_TUNE_ANALOG_N:  /* Analog N */
     {
       lpprop->atv_cvbs_out_fine.amp= 51;
       lpprop->atv_cvbs_out_fine.offset = 32;

       if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_CVBS_OUT_FINE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
       }else{}

      #ifdef _MSTAR
      lpprop->atv_sif_out.amp    = 40;
      #endif

      #ifdef _ARSENAL
      lpprop->atv_sif_out.amp    = 95;
      #endif

        lpprop->atv_sif_out.offset = 135;

         if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp) != 0) {
              return ERROR_Si2176_SENDING_COMMAND;
           }else{}

     }
     break;

     default:
       return 1;
   }

    //printf("Sif out amp is %d , offset is %d \r\n",lpprop->atv_sif_out.amp,lpprop->atv_sif_out.offset );

    return 0;

}

/* Set Audio Sys for Auto Scan */
unsigned char Si2176_SetAudioSysForAutoScan(unsigned char nSel_atv_audio_mode_audio_sys, L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop)
{

  /* TUNER_TUNE_FREQ_CMD_struct tuner_tune_freq; */
  unsigned char wait_for_cts = 0;   /* global flag for CTS checking prior to sending a Si2176 API Command */
  /* default is no CTS check prior to sending Si2176 API Command */
  unsigned char wait_for_response = 1;    /* global flag for CTS checking and Response readback after sending Si2176 API Command */
    /* default is CTS check and Reponse readback after sending Si2176 API Command */

  /* Setting ATV_AUDIO_MODE_PROP property */
  switch(nSel_atv_audio_mode_audio_sys)
  {
    case SEMCO_ANALOG_AUDIO_RSVD:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT;
    break;
    case SEMCO_ANALOG_AUDIO_MONO:
            lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MONO;
    break;
    case SEMCO_ANALOG_AUDIO_MONO_NICAM:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MONO_NICAM;
    break;
    case SEMCO_ANALOG_AUDIO_A2:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2;
    break;
    case SEMCO_ANALOG_AUDIO_A2_DK2:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK2;
    break;
    case SEMCO_ANALOG_AUDIO_A2_DK3:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK3;
    break;
    case SEMCO_ANALOG_AUDIO_BTSC:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_BTSC;
    break;
    case SEMCO_ANALOG_AUDIO_EIAJ:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_EIAJ;
    break;
    case Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_SCAN:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_SCAN;
    break;
    case Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK4:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_A2_DK4;
    break;
    case Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_WIDE_SCAN:
        lpprop->atv_audio_mode.audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_WIDE_SCAN;
    break;
        default:
        break;
  }

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_AUDIO_MODE_PROP, lpprop, rsp) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}

   return 0;
}

/*  Set MFT */
/*  nStep is VD offset */
/*  modify by yooheeyong 20101025 */
/* MFT 관련 수정 , by yooheeyong 20101028 */
unsigned char Si2176_SetMFT(int nStep, L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop)
{
  /* TUNER_TUNE_FREQ_CMD_struct tuner_tune_freq; */
  unsigned char wait_for_cts = 0;   /* global flag for CTS checking prior to sending a Si2176 API Command */
  /* default is no CTS check prior to sending Si2176 API Command */
  unsigned char wait_for_response = 1;    /* global flag for CTS checking and Response readback after sending Si2176 API Command */
        /* default is CTS check and Reponse readback after sending Si2176 API Command */
  int ret=1;

        int nReal_Step = 0;
       UNUSED(lpprop);
  if(nStep == 32 && nBeforeStep == -32){
       Si2176_L1_FINE_TUNE (lpSi2176, wait_for_cts, wait_for_response,Si2176_FINE_TUNE_CMD_RESERVED_RESERVED,-4000, rsp);
       nReal_Step = nRightMax - nCriteriaStep;
       Si2176_L1_FINE_TUNE (lpSi2176, wait_for_cts, wait_for_response,Si2176_FINE_TUNE_CMD_RESERVED_RESERVED,-(125*nReal_Step), rsp);
  }else if(nStep == -32 && nBeforeStep == 32){
       Si2176_L1_FINE_TUNE (lpSi2176, wait_for_cts, wait_for_response,Si2176_FINE_TUNE_CMD_RESERVED_RESERVED,4000, rsp);
       nReal_Step = nLeftMax - nCriteriaStep;
       Si2176_L1_FINE_TUNE (lpSi2176, wait_for_cts, wait_for_response,Si2176_FINE_TUNE_CMD_RESERVED_RESERVED,-(125*nReal_Step), rsp);
  }else{

    if(nStep > nRightMax)
            nReal_Step = nRightMax + ABS_SEMCO(nCriteriaStep);
    else if(nStep < nLeftMax)
            nReal_Step = nLeftMax - ABS_SEMCO(nCriteriaStep);
    else
      nReal_Step = nStep - nCriteriaStep; /* 움직이어야 하는 스텝 */

    if(nReal_Step > 32)
      nReal_Step = 32;
    else if(nReal_Step < -32)
      nReal_Step = -32;

    Si2176_L1_FINE_TUNE (lpSi2176, wait_for_cts, wait_for_response,Si2176_FINE_TUNE_CMD_RESERVED_RESERVED,-(125*nReal_Step), rsp);
  }

  nBeforeStep = nStep;

  return (unsigned char)ret;

}


/* ATV Sync Lock */
/* Return : lock - 1, unlock - 0 */
/* add by yooheeyong 20101025 */
unsigned char Si2176_ATV_Sync_Lock(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp)
{
    ATVStatus(lpSi2176, lprsp);

  if(lprsp->atv_status.pcl)
    return 1;
  else
    return 0;
}

/* ATV Master Lock */
/* Return : lock - 1, unlock - 0 */
/* add by yooheeyong 20101025 */
unsigned char Si2176_ATV_Master_Lock(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp)
{
    ATVStatus(lpSi2176, lprsp);

  if(lprsp->atv_status.dl)
    return 1;
  else
    return 0;
}

/* Get RSSI */
int Si2176_GetRSSI(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp)
{
   Si2176_GetTunerStatus(lpSi2176,lprsp);

   return ((int)(lprsp->tuner_status.rssi));
}


/* 임시 코드 */
/* Set AFC Range */
unsigned char Si2176_Configure_AFC_Range(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop, int nSelAFC)
{
  unsigned char wait_for_cts = 0;
  unsigned char wait_for_response = 1;

  /* nSelAFC
    0 - 100  KHz
      1 - 500  KHz
      2 - 1000 KHz
      3 - 1500 KHz
      4 - 2000 KHz
    */

  switch(nSelAFC)
  {
      case 0:
           lpprop->atv_afc_range.range_khz  =  100;
        break;
      case 1:
           lpprop->atv_afc_range.range_khz  =  500;
        break;
      case 2:
           lpprop->atv_afc_range.range_khz  =  1000;
        break;
      case 3:
           lpprop->atv_afc_range.range_khz  =  1500;
        break;
      case 4:
           lpprop->atv_afc_range.range_khz  =  2000;
        break;
  }

    if (Si2176_L1_SetProperty2(lpSi2176, wait_for_response, wait_for_cts, Si2176_ATV_AFC_RANGE_PROP, lpprop, rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }else{}

    return 0;
}


