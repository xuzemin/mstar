/****************************************************************************
*
* 							LG Innotek Co.,Ltd.
*
* Copyright (C) 2012, LG Innotek, Gwangju, Korea, All Rights Reserved.
*
* File: LGIT_Tuner_Common.h
*
* version: 1.00.00
*
* Description: 
*
* Description			Version		Date		Author
* ---------------------------------------------------------------------
* Create				1.00.00		2012.03.28	JH.KIM
****************************************************************************/

#ifndef _LGIT_TUNER_API_COMMON_H
#define _LGIT_TUNER_API_COMMON_H

typedef enum{
  LGIT_TUNER_STD_DVBC = 0,
  LGIT_TUNER_STD_DVBC2,
  LGIT_TUNER_STD_DVBT,
  LGIT_TUNER_STD_DVBT2,
  LGIT_TUNER_STD_DVBS,
  LGIT_TUNER_STD_DVBS2,
  LGIT_TUNER_STD_8VSB,
  LGIT_TUNER_STD_USQAM,
  LGIT_TUNER_STD_ISDBT,
  LGIT_TUNER_STD_ISDBS,
  LGIT_TUNER_STD_DTMB,
  LGIT_TUNER_STD_PAL_B = 20,
  LGIT_TUNER_STD_PAL_G,
  LGIT_TUNER_STD_PAL_I,
  LGIT_TUNER_STD_PAL_D,
  LGIT_TUNER_STD_SECAM_L,
  LGIT_TUNER_STD_SECAM_LP,
  LGIT_TUNER_STD_NTSC,
  LGIT_TUNER_STD_PAL_M,
  LGIT_TUNER_STD_ATV_SCAN = 30,
}Lgit_tuner_standard_t;

typedef enum{
  LGIT_TUNER_BW_1_7MHz = 0,
  LGIT_TUNER_BW_5MHz,
  LGIT_TUNER_BW_6MHz,
  LGIT_TUNER_BW_7MHz,
  LGIT_TUNER_BW_8MHz,
  LGIT_TUNER_BW_10MHz,
}Lgit_tuner_bandwidth_t;

typedef enum{
  LGIT_TUNER_IQ_NORMAL = 0,
  LGIT_TUNER_IQ_INVERTED,
}Lgit_tuner_specinv_t;

typedef enum{
  LGIT_TUNER_IFAGC_POS = 0,
  LGIT_TUNER_IFAGC_NEG,
}Lgit_tuner_ifagc_por_t;

#endif /* _LGIT_TUNER_API_COMMON_H */