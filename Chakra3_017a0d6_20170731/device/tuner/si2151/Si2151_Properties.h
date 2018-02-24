/*************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties structures and functions definitions
   FILE: Si2151_Properties.h
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_11
   Revision: 0.4
   Date: December 15 2015
  (C) Copyright 2015, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si2151_PROPERTIES_H_
#define   _Si2151_PROPERTIES_H_

/* Si2151 ATV_AGC_SPEED property definition */
#define   Si2151_ATV_AGC_SPEED_PROP 0x0611

#ifdef    Si2151_ATV_AGC_SPEED_PROP
  #define Si2151_ATV_AGC_SPEED_PROP_CODE 0x000611


    typedef struct { /* Si2151_ATV_AGC_SPEED_PROP_struct */
      unsigned char   if_agc_speed;
   } Si2151_ATV_AGC_SPEED_PROP_struct;

   /* ATV_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO    0
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_89      89
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_105     105
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_121     121
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_137     137
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_158     158
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_172     172
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_178     178
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_185     185
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_196     196
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_206     206
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_216     216
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_219     219
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_222     222
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_223     223
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_248     248
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_250     250
    #define Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_251     251

#endif /* Si2151_ATV_AGC_SPEED_PROP */

/* Si2151 ATV_AGC_SPEED_LOW_RSSI property definition */
#define   Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP 0x0623

#ifdef    Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP
  #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE 0x000623


    typedef struct { /* Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_struct */
      unsigned char   if_agc_speed;
               char   thld;
   } Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_struct;

   /* ATV_AGC_SPEED_LOW_RSSI property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_DEFAULT    158
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_89      89
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_105     105
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_121     121
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_137     137
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158     158
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_172     172
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_178     178
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_185     185
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_196     196
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_206     206
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_216     216
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_219     219
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_222     222
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_223     223
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_248     248
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_250     250
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_251     251

   /* ATV_AGC_SPEED_LOW_RSSI property, THLD field definition (NO TITLE)*/
   #define  Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_LSB         8
   #define  Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_MASK        0xff
   #define  Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_DEFAULT    -128
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_THLD_MIN  -128
    #define Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_THLD_MAX  127

#endif /* Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP */

/* Si2151 ATV_ARTIFICIAL_SNOW property definition */
#define   Si2151_ATV_ARTIFICIAL_SNOW_PROP 0x0624

#ifdef    Si2151_ATV_ARTIFICIAL_SNOW_PROP
  #define Si2151_ATV_ARTIFICIAL_SNOW_PROP_CODE 0x000624


    typedef struct { /* Si2151_ATV_ARTIFICIAL_SNOW_PROP_struct */
      unsigned char   gain;
      unsigned char   period;
   } Si2151_ATV_ARTIFICIAL_SNOW_PROP_struct;

   /* ATV_ARTIFICIAL_SNOW property, GAIN field definition (NO TITLE)*/
   #define  Si2151_ATV_ARTIFICIAL_SNOW_PROP_GAIN_LSB         0
   #define  Si2151_ATV_ARTIFICIAL_SNOW_PROP_GAIN_MASK        0x7f
   #define  Si2151_ATV_ARTIFICIAL_SNOW_PROP_GAIN_DEFAULT    32
    #define Si2151_ATV_ARTIFICIAL_SNOW_PROP_GAIN_GAIN_MIN  0
    #define Si2151_ATV_ARTIFICIAL_SNOW_PROP_GAIN_GAIN_MAX  32

   /* ATV_ARTIFICIAL_SNOW property, PERIOD field definition (NO TITLE)*/
   #define  Si2151_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LSB         7
   #define  Si2151_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_MASK        0x01
   #define  Si2151_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_DEFAULT    1
    #define Si2151_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LONG   0
    #define Si2151_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_SHORT  1

#endif /* Si2151_ATV_ARTIFICIAL_SNOW_PROP */

/* Si2151 ATV_CONFIG_IF_PORT property definition */
#define   Si2151_ATV_CONFIG_IF_PORT_PROP 0x0603

#ifdef    Si2151_ATV_CONFIG_IF_PORT_PROP
  #define Si2151_ATV_CONFIG_IF_PORT_PROP_CODE 0x000603


    typedef struct { /* Si2151_ATV_CONFIG_IF_PORT_PROP_struct */
      unsigned char   atv_out_type;
   } Si2151_ATV_CONFIG_IF_PORT_PROP_struct;

   /* ATV_CONFIG_IF_PORT property, ATV_OUT_TYPE field definition (NO TITLE)*/
   #define  Si2151_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LSB         0
   #define  Si2151_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_MASK        0x0f
   #define  Si2151_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_DEFAULT    8
    #define Si2151_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LIF_DIFF_IF  8
    #define Si2151_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LIF_SE_IFA   12

#endif /* Si2151_ATV_CONFIG_IF_PORT_PROP */

/* Si2151 ATV_EXT_AGC property definition */
#define   Si2151_ATV_EXT_AGC_PROP 0x0607

#ifdef    Si2151_ATV_EXT_AGC_PROP
  #define Si2151_ATV_EXT_AGC_PROP_CODE 0x000607


    typedef struct { /* Si2151_ATV_EXT_AGC_PROP_struct */
      unsigned char   max_10mv;
      unsigned char   min_10mv;
   } Si2151_ATV_EXT_AGC_PROP_struct;

   /* ATV_EXT_AGC property, MAX_10MV field definition (NO TITLE)*/
   #define  Si2151_ATV_EXT_AGC_PROP_MAX_10MV_LSB         8
   #define  Si2151_ATV_EXT_AGC_PROP_MAX_10MV_MASK        0xff
   #define  Si2151_ATV_EXT_AGC_PROP_MAX_10MV_DEFAULT    200
    #define Si2151_ATV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MIN  0
    #define Si2151_ATV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MAX  255

   /* ATV_EXT_AGC property, MIN_10MV field definition (NO TITLE)*/
   #define  Si2151_ATV_EXT_AGC_PROP_MIN_10MV_LSB         0
   #define  Si2151_ATV_EXT_AGC_PROP_MIN_10MV_MASK        0xff
   #define  Si2151_ATV_EXT_AGC_PROP_MIN_10MV_DEFAULT    50
    #define Si2151_ATV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MIN  0
    #define Si2151_ATV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MAX  255

#endif /* Si2151_ATV_EXT_AGC_PROP */

/* Si2151 ATV_HSYNC_OUT property definition */
#define   Si2151_ATV_HSYNC_OUT_PROP 0x0627

#ifdef    Si2151_ATV_HSYNC_OUT_PROP
  #define Si2151_ATV_HSYNC_OUT_PROP_CODE 0x000627


    typedef struct { /* Si2151_ATV_HSYNC_OUT_PROP_struct */
               char   offset;
      unsigned char   polarity;
      unsigned char   width;
   } Si2151_ATV_HSYNC_OUT_PROP_struct;

   /* ATV_HSYNC_OUT property, OFFSET field definition (NO TITLE)*/
   #define  Si2151_ATV_HSYNC_OUT_PROP_OFFSET_LSB         8
   #define  Si2151_ATV_HSYNC_OUT_PROP_OFFSET_MASK        0xff
   #define  Si2151_ATV_HSYNC_OUT_PROP_OFFSET_DEFAULT    0
    #define Si2151_ATV_HSYNC_OUT_PROP_OFFSET_OFFSET_MIN  -128
    #define Si2151_ATV_HSYNC_OUT_PROP_OFFSET_OFFSET_MAX  127

   /* ATV_HSYNC_OUT property, POLARITY field definition (NO TITLE)*/
   #define  Si2151_ATV_HSYNC_OUT_PROP_POLARITY_LSB         0
   #define  Si2151_ATV_HSYNC_OUT_PROP_POLARITY_MASK        0x01
   #define  Si2151_ATV_HSYNC_OUT_PROP_POLARITY_DEFAULT    0
    #define Si2151_ATV_HSYNC_OUT_PROP_POLARITY_LOW   0
    #define Si2151_ATV_HSYNC_OUT_PROP_POLARITY_HIGH  1

   /* ATV_HSYNC_OUT property, WIDTH field definition (NO TITLE)*/
   #define  Si2151_ATV_HSYNC_OUT_PROP_WIDTH_LSB         1
   #define  Si2151_ATV_HSYNC_OUT_PROP_WIDTH_MASK        0x7f
   #define  Si2151_ATV_HSYNC_OUT_PROP_WIDTH_DEFAULT    75
    #define Si2151_ATV_HSYNC_OUT_PROP_WIDTH_WIDTH_MIN  0
    #define Si2151_ATV_HSYNC_OUT_PROP_WIDTH_WIDTH_MAX  127

#endif /* Si2151_ATV_HSYNC_OUT_PROP */

/* Si2151 ATV_LIF_FREQ property definition */
#define   Si2151_ATV_LIF_FREQ_PROP 0x060c

#ifdef    Si2151_ATV_LIF_FREQ_PROP
  #define Si2151_ATV_LIF_FREQ_PROP_CODE 0x00060c


    typedef struct { /* Si2151_ATV_LIF_FREQ_PROP_struct */
      unsigned int    offset;
   } Si2151_ATV_LIF_FREQ_PROP_struct;

   /* ATV_LIF_FREQ property, OFFSET field definition (NO TITLE)*/
   #define  Si2151_ATV_LIF_FREQ_PROP_OFFSET_LSB         0
   #define  Si2151_ATV_LIF_FREQ_PROP_OFFSET_MASK        0xffff
   #define  Si2151_ATV_LIF_FREQ_PROP_OFFSET_DEFAULT    5000
    #define Si2151_ATV_LIF_FREQ_PROP_OFFSET_OFFSET_MIN  0
    #define Si2151_ATV_LIF_FREQ_PROP_OFFSET_OFFSET_MAX  7000

#endif /* Si2151_ATV_LIF_FREQ_PROP */

/* Si2151 ATV_LIF_OUT property definition */
#define   Si2151_ATV_LIF_OUT_PROP 0x060d

#ifdef    Si2151_ATV_LIF_OUT_PROP
  #define Si2151_ATV_LIF_OUT_PROP_CODE 0x00060d


    typedef struct { /* Si2151_ATV_LIF_OUT_PROP_struct */
      unsigned char   amp;
      unsigned char   offset;
   } Si2151_ATV_LIF_OUT_PROP_struct;

   /* ATV_LIF_OUT property, AMP field definition (NO TITLE)*/
   #define  Si2151_ATV_LIF_OUT_PROP_AMP_LSB         8
   #define  Si2151_ATV_LIF_OUT_PROP_AMP_MASK        0xff
   #define  Si2151_ATV_LIF_OUT_PROP_AMP_DEFAULT    100
    #define Si2151_ATV_LIF_OUT_PROP_AMP_AMP_MIN  0
    #define Si2151_ATV_LIF_OUT_PROP_AMP_AMP_MAX  255

   /* ATV_LIF_OUT property, OFFSET field definition (NO TITLE)*/
   #define  Si2151_ATV_LIF_OUT_PROP_OFFSET_LSB         0
   #define  Si2151_ATV_LIF_OUT_PROP_OFFSET_MASK        0xff
   #define  Si2151_ATV_LIF_OUT_PROP_OFFSET_DEFAULT    148
    #define Si2151_ATV_LIF_OUT_PROP_OFFSET_OFFSET_MIN  0
    #define Si2151_ATV_LIF_OUT_PROP_OFFSET_OFFSET_MAX  255

#endif /* Si2151_ATV_LIF_OUT_PROP */

/* Si2151 ATV_PGA_LIMITS property definition */
#define   Si2151_ATV_PGA_LIMITS_PROP 0x061e

#ifdef    Si2151_ATV_PGA_LIMITS_PROP
  #define Si2151_ATV_PGA_LIMITS_PROP_CODE 0x00061e


    typedef struct { /* Si2151_ATV_PGA_LIMITS_PROP_struct */
      unsigned char   max;
      unsigned char   min;
   } Si2151_ATV_PGA_LIMITS_PROP_struct;

   /* ATV_PGA_LIMITS property, MAX field definition (NO TITLE)*/
   #define  Si2151_ATV_PGA_LIMITS_PROP_MAX_LSB         8
   #define  Si2151_ATV_PGA_LIMITS_PROP_MAX_MASK        0xff
   #define  Si2151_ATV_PGA_LIMITS_PROP_MAX_DEFAULT    56
    #define Si2151_ATV_PGA_LIMITS_PROP_MAX_MAX_MIN  0
    #define Si2151_ATV_PGA_LIMITS_PROP_MAX_MAX_MAX  56

   /* ATV_PGA_LIMITS property, MIN field definition (NO TITLE)*/
   #define  Si2151_ATV_PGA_LIMITS_PROP_MIN_LSB         0
   #define  Si2151_ATV_PGA_LIMITS_PROP_MIN_MASK        0xff
   #define  Si2151_ATV_PGA_LIMITS_PROP_MIN_DEFAULT    0
    #define Si2151_ATV_PGA_LIMITS_PROP_MIN_MIN_MIN  0
    #define Si2151_ATV_PGA_LIMITS_PROP_MIN_MIN_MAX  56

#endif /* Si2151_ATV_PGA_LIMITS_PROP */

/* Si2151 ATV_PGA_TARGET property definition */
#define   Si2151_ATV_PGA_TARGET_PROP 0x0617

#ifdef    Si2151_ATV_PGA_TARGET_PROP
  #define Si2151_ATV_PGA_TARGET_PROP_CODE 0x000617


    typedef struct { /* Si2151_ATV_PGA_TARGET_PROP_struct */
      unsigned char   override_enable;
               char   pga_target;
   } Si2151_ATV_PGA_TARGET_PROP_struct;

   /* ATV_PGA_TARGET property, OVERRIDE_ENABLE field definition (NO TITLE)*/
   #define  Si2151_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB         8
   #define  Si2151_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK        0x01
   #define  Si2151_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DEFAULT    0
    #define Si2151_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE  0
    #define Si2151_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE   1

   /* ATV_PGA_TARGET property, PGA_TARGET field definition (NO TITLE)*/
   #define  Si2151_ATV_PGA_TARGET_PROP_PGA_TARGET_LSB         0
   #define  Si2151_ATV_PGA_TARGET_PROP_PGA_TARGET_MASK        0xff
   #define  Si2151_ATV_PGA_TARGET_PROP_PGA_TARGET_DEFAULT    0
    #define Si2151_ATV_PGA_TARGET_PROP_PGA_TARGET_PGA_TARGET_MIN  -13
    #define Si2151_ATV_PGA_TARGET_PROP_PGA_TARGET_PGA_TARGET_MAX  7

#endif /* Si2151_ATV_PGA_TARGET_PROP */

/* Si2151 ATV_RF_TOP property definition */
#define   Si2151_ATV_RF_TOP_PROP 0x0612

#ifdef    Si2151_ATV_RF_TOP_PROP
  #define Si2151_ATV_RF_TOP_PROP_CODE 0x000612


    typedef struct { /* Si2151_ATV_RF_TOP_PROP_struct */
      unsigned char   atv_rf_top;
   } Si2151_ATV_RF_TOP_PROP_struct;

   /* ATV_RF_TOP property, ATV_RF_TOP field definition (NO TITLE)*/
   #define  Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB         0
   #define  Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK        0xff
   #define  Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_DEFAULT    0
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO   0
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_P2DB   4
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_P1DB   5
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_0DB    6
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M1DB   7
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M2DB   8
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M3DB   9
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M4DB   10
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M5DB   11
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M6DB   12
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M7DB   13
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M8DB   14
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M9DB   15
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M10DB  16
    #define Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_M11DB  17

#endif /* Si2151_ATV_RF_TOP_PROP */

/* Si2151 ATV_RSQ_RSSI_THRESHOLD property definition */
#define   Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP 0x0605

#ifdef    Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP
  #define Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE 0x000605


    typedef struct { /* Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_struct */
               char   lo;
   } Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_struct;

   /* ATV_RSQ_RSSI_THRESHOLD property, LO field definition (NO TITLE)*/
   #define  Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB         0
   #define  Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK        0xff
   #define  Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_DEFAULT    -70
    #define Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MIN  -128
    #define Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MAX  127

#endif /* Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP */

/* Si2151 ATV_VIDEO_MODE property definition */
#define   Si2151_ATV_VIDEO_MODE_PROP 0x0604

#ifdef    Si2151_ATV_VIDEO_MODE_PROP
  #define Si2151_ATV_VIDEO_MODE_PROP_CODE 0x000604


    typedef struct { /* Si2151_ATV_VIDEO_MODE_PROP_struct */
      unsigned char   invert_spectrum;
      unsigned char   video_sys;
   } Si2151_ATV_VIDEO_MODE_PROP_struct;

   /* ATV_VIDEO_MODE property, INVERT_SPECTRUM field definition (NO TITLE)*/
   #define  Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_LSB         9
   #define  Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_MASK        0x01
   #define  Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_DEFAULT    1
    #define Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_NORMAL    0
    #define Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED  1

   /* ATV_VIDEO_MODE property, VIDEO_SYS field definition (NO TITLE)*/
   #define  Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB         0
   #define  Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK        0x07
   #define  Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DEFAULT    0
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B   0
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH  1
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M   2
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N   3
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I   4
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK  5
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L   6
    #define Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP  7

#endif /* Si2151_ATV_VIDEO_MODE_PROP */

/* Si2151 ATV_VSNR_CAP property definition */
#define   Si2151_ATV_VSNR_CAP_PROP 0x0616

#ifdef    Si2151_ATV_VSNR_CAP_PROP
  #define Si2151_ATV_VSNR_CAP_PROP_CODE 0x000616


    typedef struct { /* Si2151_ATV_VSNR_CAP_PROP_struct */
      unsigned char   atv_vsnr_cap;
   } Si2151_ATV_VSNR_CAP_PROP_struct;

   /* ATV_VSNR_CAP property, ATV_VSNR_CAP field definition (NO TITLE)*/
   #define  Si2151_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB         0
   #define  Si2151_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK        0xff
   #define  Si2151_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_DEFAULT    0
    #define Si2151_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_ATV_VSNR_CAP_MIN  0
    #define Si2151_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_ATV_VSNR_CAP_MAX  127

#endif /* Si2151_ATV_VSNR_CAP_PROP */

/* Si2151 CRYSTAL_TRIM property definition */
#define   Si2151_CRYSTAL_TRIM_PROP 0x0402

#ifdef    Si2151_CRYSTAL_TRIM_PROP
  #define Si2151_CRYSTAL_TRIM_PROP_CODE 0x000402


    typedef struct { /* Si2151_CRYSTAL_TRIM_PROP_struct */
      unsigned char   xo_cap;
   } Si2151_CRYSTAL_TRIM_PROP_struct;

   /* CRYSTAL_TRIM property, XO_CAP field definition (NO TITLE)*/
   #define  Si2151_CRYSTAL_TRIM_PROP_XO_CAP_LSB         0
   #define  Si2151_CRYSTAL_TRIM_PROP_XO_CAP_MASK        0x0f
   #define  Si2151_CRYSTAL_TRIM_PROP_XO_CAP_DEFAULT    8
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_4P7PF   0
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_5P2PF   2
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_5P7PF   4
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_6P2PF   6
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_6P7PF   8
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_7P2PF   10
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_7P7PF   12
    #define Si2151_CRYSTAL_TRIM_PROP_XO_CAP_8P2PF   14

#endif /* Si2151_CRYSTAL_TRIM_PROP */

/* Si2151 DTV_AGC_AUTO_FREEZE property definition */
#define   Si2151_DTV_AGC_AUTO_FREEZE_PROP 0x0714

#ifdef    Si2151_DTV_AGC_AUTO_FREEZE_PROP
  #define Si2151_DTV_AGC_AUTO_FREEZE_PROP_CODE 0x000714


    typedef struct { /* Si2151_DTV_AGC_AUTO_FREEZE_PROP_struct */
      unsigned char   thld;
      unsigned char   timeout;
   } Si2151_DTV_AGC_AUTO_FREEZE_PROP_struct;

   /* DTV_AGC_AUTO_FREEZE property, THLD field definition (NO TITLE)*/
   #define  Si2151_DTV_AGC_AUTO_FREEZE_PROP_THLD_LSB         0
   #define  Si2151_DTV_AGC_AUTO_FREEZE_PROP_THLD_MASK        0xff
   #define  Si2151_DTV_AGC_AUTO_FREEZE_PROP_THLD_DEFAULT    255
    #define Si2151_DTV_AGC_AUTO_FREEZE_PROP_THLD_THLD_MIN  0
    #define Si2151_DTV_AGC_AUTO_FREEZE_PROP_THLD_THLD_MAX  255

   /* DTV_AGC_AUTO_FREEZE property, TIMEOUT field definition (NO TITLE)*/
   #define  Si2151_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_LSB         8
   #define  Si2151_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_MASK        0xff
   #define  Si2151_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_DEFAULT    1
    #define Si2151_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_TIMEOUT_MIN  1
    #define Si2151_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_TIMEOUT_MAX  250

#endif /* Si2151_DTV_AGC_AUTO_FREEZE_PROP */

/* Si2151 DTV_AGC_SPEED property definition */
#define   Si2151_DTV_AGC_SPEED_PROP 0x0708

#ifdef    Si2151_DTV_AGC_SPEED_PROP
  #define Si2151_DTV_AGC_SPEED_PROP_CODE 0x000708


    typedef struct { /* Si2151_DTV_AGC_SPEED_PROP_struct */
      unsigned char   agc_decim;
      unsigned char   if_agc_speed;
   } Si2151_DTV_AGC_SPEED_PROP_struct;

   /* DTV_AGC_SPEED property, AGC_DECIM field definition (NO TITLE)*/
   #define  Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB         8
   #define  Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK        0x03
   #define  Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_DEFAULT    0
    #define Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF  0
    #define Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_2    1
    #define Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_4    2
    #define Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_8    3

   /* DTV_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO  0
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39    39
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_54    54
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_63    63
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_89    89
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_105   105
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_121   121
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_137   137
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_158   158
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_172   172
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_185   185
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_196   196
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_206   206
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_216   216
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_219   219
    #define Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_222   222

#endif /* Si2151_DTV_AGC_SPEED_PROP */

/* Si2151 DTV_CONFIG_IF_PORT property definition */
#define   Si2151_DTV_CONFIG_IF_PORT_PROP 0x0702

#ifdef    Si2151_DTV_CONFIG_IF_PORT_PROP
  #define Si2151_DTV_CONFIG_IF_PORT_PROP_CODE 0x000702


    typedef struct { /* Si2151_DTV_CONFIG_IF_PORT_PROP_struct */
      unsigned char   dtv_out_type;
   } Si2151_DTV_CONFIG_IF_PORT_PROP_struct;

   /* DTV_CONFIG_IF_PORT property, DTV_OUT_TYPE field definition (NO TITLE)*/
   #define  Si2151_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB         0
   #define  Si2151_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK        0x0f
   #define  Si2151_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_DEFAULT    0
    #define Si2151_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF      0
    #define Si2151_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_SE_IFA  4

#endif /* Si2151_DTV_CONFIG_IF_PORT_PROP */

/* Si2151 DTV_EXT_AGC property definition */
#define   Si2151_DTV_EXT_AGC_PROP 0x0705

#ifdef    Si2151_DTV_EXT_AGC_PROP
  #define Si2151_DTV_EXT_AGC_PROP_CODE 0x000705


    typedef struct { /* Si2151_DTV_EXT_AGC_PROP_struct */
      unsigned char   max_10mv;
      unsigned char   min_10mv;
   } Si2151_DTV_EXT_AGC_PROP_struct;

   /* DTV_EXT_AGC property, MAX_10MV field definition (NO TITLE)*/
   #define  Si2151_DTV_EXT_AGC_PROP_MAX_10MV_LSB         8
   #define  Si2151_DTV_EXT_AGC_PROP_MAX_10MV_MASK        0xff
   #define  Si2151_DTV_EXT_AGC_PROP_MAX_10MV_DEFAULT    200
    #define Si2151_DTV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MIN  0
    #define Si2151_DTV_EXT_AGC_PROP_MAX_10MV_MAX_10MV_MAX  255

   /* DTV_EXT_AGC property, MIN_10MV field definition (NO TITLE)*/
   #define  Si2151_DTV_EXT_AGC_PROP_MIN_10MV_LSB         0
   #define  Si2151_DTV_EXT_AGC_PROP_MIN_10MV_MASK        0xff
   #define  Si2151_DTV_EXT_AGC_PROP_MIN_10MV_DEFAULT    50
    #define Si2151_DTV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MIN  0
    #define Si2151_DTV_EXT_AGC_PROP_MIN_10MV_MIN_10MV_MAX  255

#endif /* Si2151_DTV_EXT_AGC_PROP */

/* Si2151 DTV_IF_AGC_SPEED property definition */
#define   Si2151_DTV_IF_AGC_SPEED_PROP 0x0716

#ifdef    Si2151_DTV_IF_AGC_SPEED_PROP
  #define Si2151_DTV_IF_AGC_SPEED_PROP_CODE 0x000716


    typedef struct { /* Si2151_DTV_IF_AGC_SPEED_PROP_struct */
      unsigned char   attack;
      unsigned char   decay;
   } Si2151_DTV_IF_AGC_SPEED_PROP_struct;

   /* DTV_IF_AGC_SPEED property, ATTACK field definition (NO TITLE)*/
   #define  Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK_LSB         0
   #define  Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK_MASK        0xff
   #define  Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK_DEFAULT    0
    #define Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK_AUTO  0

    #define Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK_ATTACK_MIN  0
    #define Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK_ATTACK_MAX  231

   /* DTV_IF_AGC_SPEED property, DECAY field definition (NO TITLE)*/
   #define  Si2151_DTV_IF_AGC_SPEED_PROP_DECAY_LSB         8
   #define  Si2151_DTV_IF_AGC_SPEED_PROP_DECAY_MASK        0xff
   #define  Si2151_DTV_IF_AGC_SPEED_PROP_DECAY_DEFAULT    0
    #define Si2151_DTV_IF_AGC_SPEED_PROP_DECAY_AUTO  0

    #define Si2151_DTV_IF_AGC_SPEED_PROP_DECAY_DECAY_MIN  0
    #define Si2151_DTV_IF_AGC_SPEED_PROP_DECAY_DECAY_MAX  231

#endif /* Si2151_DTV_IF_AGC_SPEED_PROP */

/* Si2151 DTV_INITIAL_AGC_SPEED property definition */
#define   Si2151_DTV_INITIAL_AGC_SPEED_PROP 0x070d

#ifdef    Si2151_DTV_INITIAL_AGC_SPEED_PROP
  #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_CODE 0x00070d


    typedef struct { /* Si2151_DTV_INITIAL_AGC_SPEED_PROP_struct */
      unsigned char   agc_decim;
      unsigned char   if_agc_speed;
   } Si2151_DTV_INITIAL_AGC_SPEED_PROP_struct;

   /* DTV_INITIAL_AGC_SPEED property, AGC_DECIM field definition (NO TITLE)*/
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB         8
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK        0x03
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_DEFAULT    0
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF  0
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_2    1
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_4    2
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_8    3

   /* DTV_INITIAL_AGC_SPEED property, IF_AGC_SPEED field definition (NO TITLE)*/
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB         0
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK        0xff
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_DEFAULT    0
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO  0
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_39    39
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_54    54
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_63    63
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_89    89
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_105   105
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_121   121
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_137   137
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_158   158
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_172   172
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_185   185
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_196   196
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_206   206
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_216   216
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_219   219
    #define Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_222   222

#endif /* Si2151_DTV_INITIAL_AGC_SPEED_PROP */

/* Si2151 DTV_INITIAL_AGC_SPEED_PERIOD property definition */
#define   Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP 0x070e

#ifdef    Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  #define Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE 0x00070e


    typedef struct { /* Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct */
      unsigned int    period;
   } Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct;

   /* DTV_INITIAL_AGC_SPEED_PERIOD property, PERIOD field definition (NO TITLE)*/
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB         0
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK        0xffff
   #define  Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_DEFAULT    0
    #define Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_PERIOD_MIN  0
    #define Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_PERIOD_MAX  65535

#endif /* Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

/* Si2151 DTV_INTERNAL_ZIF property definition */
#define   Si2151_DTV_INTERNAL_ZIF_PROP 0x0710

#ifdef    Si2151_DTV_INTERNAL_ZIF_PROP
  #define Si2151_DTV_INTERNAL_ZIF_PROP_CODE 0x000710


    typedef struct { /* Si2151_DTV_INTERNAL_ZIF_PROP_struct */
      unsigned char   atsc;
      unsigned char   dtmb;
      unsigned char   dvbc;
      unsigned char   dvbt;
      unsigned char   isdbc;
      unsigned char   isdbt;
      unsigned char   qam_us;
   } Si2151_DTV_INTERNAL_ZIF_PROP_struct;

   /* DTV_INTERNAL_ZIF property, ATSC field definition (NO TITLE)*/
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ATSC_LSB         0
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ATSC_MASK        0x01
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ATSC_DEFAULT    1
    #define Si2151_DTV_INTERNAL_ZIF_PROP_ATSC_LIF  0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_ATSC_ZIF  1

   /* DTV_INTERNAL_ZIF property, DTMB field definition (NO TITLE)*/
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DTMB_LSB         6
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DTMB_MASK        0x01
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DTMB_DEFAULT    0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_DTMB_LIF  0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_DTMB_ZIF  1

   /* DTV_INTERNAL_ZIF property, DVBC field definition (NO TITLE)*/
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DVBC_LSB         3
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DVBC_MASK        0x01
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DVBC_DEFAULT    1
    #define Si2151_DTV_INTERNAL_ZIF_PROP_DVBC_LIF  0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_DVBC_ZIF  1

   /* DTV_INTERNAL_ZIF property, DVBT field definition (NO TITLE)*/
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DVBT_LSB         2
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DVBT_MASK        0x01
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_DVBT_DEFAULT    1
    #define Si2151_DTV_INTERNAL_ZIF_PROP_DVBT_LIF  0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_DVBT_ZIF  1

   /* DTV_INTERNAL_ZIF property, ISDBC field definition (NO TITLE)*/
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB         5
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK        0x01
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ISDBC_DEFAULT    1
    #define Si2151_DTV_INTERNAL_ZIF_PROP_ISDBC_LIF  0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_ISDBC_ZIF  1

   /* DTV_INTERNAL_ZIF property, ISDBT field definition (NO TITLE)*/
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB         4
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK        0x01
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_ISDBT_DEFAULT    1
    #define Si2151_DTV_INTERNAL_ZIF_PROP_ISDBT_LIF  0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_ISDBT_ZIF  1

   /* DTV_INTERNAL_ZIF property, QAM_US field definition (NO TITLE)*/
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB         1
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK        0x01
   #define  Si2151_DTV_INTERNAL_ZIF_PROP_QAM_US_DEFAULT    1
    #define Si2151_DTV_INTERNAL_ZIF_PROP_QAM_US_LIF  0
    #define Si2151_DTV_INTERNAL_ZIF_PROP_QAM_US_ZIF  1

#endif /* Si2151_DTV_INTERNAL_ZIF_PROP */

/* Si2151 DTV_LIF_FREQ property definition */
#define   Si2151_DTV_LIF_FREQ_PROP 0x0706

#ifdef    Si2151_DTV_LIF_FREQ_PROP
  #define Si2151_DTV_LIF_FREQ_PROP_CODE 0x000706


    typedef struct { /* Si2151_DTV_LIF_FREQ_PROP_struct */
      unsigned int    offset;
   } Si2151_DTV_LIF_FREQ_PROP_struct;

   /* DTV_LIF_FREQ property, OFFSET field definition (NO TITLE)*/
   #define  Si2151_DTV_LIF_FREQ_PROP_OFFSET_LSB         0
   #define  Si2151_DTV_LIF_FREQ_PROP_OFFSET_MASK        0xffff
   #define  Si2151_DTV_LIF_FREQ_PROP_OFFSET_DEFAULT    5000
    #define Si2151_DTV_LIF_FREQ_PROP_OFFSET_OFFSET_MIN  0
    #define Si2151_DTV_LIF_FREQ_PROP_OFFSET_OFFSET_MAX  7000

#endif /* Si2151_DTV_LIF_FREQ_PROP */

/* Si2151 DTV_LIF_OUT property definition */
#define   Si2151_DTV_LIF_OUT_PROP 0x0707

#ifdef    Si2151_DTV_LIF_OUT_PROP
  #define Si2151_DTV_LIF_OUT_PROP_CODE 0x000707


    typedef struct { /* Si2151_DTV_LIF_OUT_PROP_struct */
      unsigned char   amp;
      unsigned char   offset;
   } Si2151_DTV_LIF_OUT_PROP_struct;

   /* DTV_LIF_OUT property, AMP field definition (NO TITLE)*/
   #define  Si2151_DTV_LIF_OUT_PROP_AMP_LSB         8
   #define  Si2151_DTV_LIF_OUT_PROP_AMP_MASK        0xff
   #define  Si2151_DTV_LIF_OUT_PROP_AMP_DEFAULT    27
    #define Si2151_DTV_LIF_OUT_PROP_AMP_AMP_MIN  0
    #define Si2151_DTV_LIF_OUT_PROP_AMP_AMP_MAX  255

   /* DTV_LIF_OUT property, OFFSET field definition (NO TITLE)*/
   #define  Si2151_DTV_LIF_OUT_PROP_OFFSET_LSB         0
   #define  Si2151_DTV_LIF_OUT_PROP_OFFSET_MASK        0xff
   #define  Si2151_DTV_LIF_OUT_PROP_OFFSET_DEFAULT    148
    #define Si2151_DTV_LIF_OUT_PROP_OFFSET_OFFSET_MIN  0
    #define Si2151_DTV_LIF_OUT_PROP_OFFSET_OFFSET_MAX  255

#endif /* Si2151_DTV_LIF_OUT_PROP */

/* Si2151 DTV_MODE property definition */
#define   Si2151_DTV_MODE_PROP 0x0703

#ifdef    Si2151_DTV_MODE_PROP
  #define Si2151_DTV_MODE_PROP_CODE 0x000703


    typedef struct { /* Si2151_DTV_MODE_PROP_struct */
      unsigned char   bw;
      unsigned char   invert_spectrum;
      unsigned char   modulation;
   } Si2151_DTV_MODE_PROP_struct;

   /* DTV_MODE property, BW field definition (NO TITLE)*/
   #define  Si2151_DTV_MODE_PROP_BW_LSB         0
   #define  Si2151_DTV_MODE_PROP_BW_MASK        0x0f
   #define  Si2151_DTV_MODE_PROP_BW_DEFAULT    8
    #define Si2151_DTV_MODE_PROP_BW_BW_6MHZ    6
    #define Si2151_DTV_MODE_PROP_BW_BW_7MHZ    7
    #define Si2151_DTV_MODE_PROP_BW_BW_8MHZ    8
    #define Si2151_DTV_MODE_PROP_BW_BW_1P7MHZ  9
    #define Si2151_DTV_MODE_PROP_BW_BW_6P1MHZ  10

   /* DTV_MODE property, INVERT_SPECTRUM field definition (NO TITLE)*/
   #define  Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_LSB         8
   #define  Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_MASK        0x01
   #define  Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_DEFAULT    0
    #define Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL    0
    #define Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED  1

   /* DTV_MODE property, MODULATION field definition (NO TITLE)*/
   #define  Si2151_DTV_MODE_PROP_MODULATION_LSB         4
   #define  Si2151_DTV_MODE_PROP_MODULATION_MASK        0x0f
   #define  Si2151_DTV_MODE_PROP_MODULATION_DEFAULT    2
    #define Si2151_DTV_MODE_PROP_MODULATION_ATSC       0
    #define Si2151_DTV_MODE_PROP_MODULATION_QAM_US     1
    #define Si2151_DTV_MODE_PROP_MODULATION_DVBT       2
    #define Si2151_DTV_MODE_PROP_MODULATION_DVBC       3
    #define Si2151_DTV_MODE_PROP_MODULATION_ISDBT      4
    #define Si2151_DTV_MODE_PROP_MODULATION_ISDBC      5
    #define Si2151_DTV_MODE_PROP_MODULATION_DTMB       6

#endif /* Si2151_DTV_MODE_PROP */

/* Si2151 DTV_PGA_LIMITS property definition */
#define   Si2151_DTV_PGA_LIMITS_PROP 0x0713

#ifdef    Si2151_DTV_PGA_LIMITS_PROP
  #define Si2151_DTV_PGA_LIMITS_PROP_CODE 0x000713


    typedef struct { /* Si2151_DTV_PGA_LIMITS_PROP_struct */
               char   max;
               char   min;
   } Si2151_DTV_PGA_LIMITS_PROP_struct;

   /* DTV_PGA_LIMITS property, MAX field definition (NO TITLE)*/
   #define  Si2151_DTV_PGA_LIMITS_PROP_MAX_LSB         8
   #define  Si2151_DTV_PGA_LIMITS_PROP_MAX_MASK        0xff
   #define  Si2151_DTV_PGA_LIMITS_PROP_MAX_DEFAULT    -1
    #define Si2151_DTV_PGA_LIMITS_PROP_MAX_MAX_MIN  -1
    #define Si2151_DTV_PGA_LIMITS_PROP_MAX_MAX_MAX  56

   /* DTV_PGA_LIMITS property, MIN field definition (NO TITLE)*/
   #define  Si2151_DTV_PGA_LIMITS_PROP_MIN_LSB         0
   #define  Si2151_DTV_PGA_LIMITS_PROP_MIN_MASK        0xff
   #define  Si2151_DTV_PGA_LIMITS_PROP_MIN_DEFAULT    -1
    #define Si2151_DTV_PGA_LIMITS_PROP_MIN_MIN_MIN  -1
    #define Si2151_DTV_PGA_LIMITS_PROP_MIN_MIN_MAX  56

#endif /* Si2151_DTV_PGA_LIMITS_PROP */

/* Si2151 DTV_PGA_TARGET property definition */
#define   Si2151_DTV_PGA_TARGET_PROP 0x070f

#ifdef    Si2151_DTV_PGA_TARGET_PROP
  #define Si2151_DTV_PGA_TARGET_PROP_CODE 0x00070f


    typedef struct { /* Si2151_DTV_PGA_TARGET_PROP_struct */
      unsigned char   override_enable;
               char   pga_target;
   } Si2151_DTV_PGA_TARGET_PROP_struct;

   /* DTV_PGA_TARGET property, OVERRIDE_ENABLE field definition (NO TITLE)*/
   #define  Si2151_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB         8
   #define  Si2151_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK        0x01
   #define  Si2151_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DEFAULT    0
    #define Si2151_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE  0
    #define Si2151_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE   1

   /* DTV_PGA_TARGET property, PGA_TARGET field definition (NO TITLE)*/
   #define  Si2151_DTV_PGA_TARGET_PROP_PGA_TARGET_LSB         0
   #define  Si2151_DTV_PGA_TARGET_PROP_PGA_TARGET_MASK        0xff
   #define  Si2151_DTV_PGA_TARGET_PROP_PGA_TARGET_DEFAULT    0
    #define Si2151_DTV_PGA_TARGET_PROP_PGA_TARGET_PGA_TARGET_MIN  -13
    #define Si2151_DTV_PGA_TARGET_PROP_PGA_TARGET_PGA_TARGET_MAX  7

#endif /* Si2151_DTV_PGA_TARGET_PROP */

/* Si2151 DTV_RF_AGC_SPEED property definition */
#define   Si2151_DTV_RF_AGC_SPEED_PROP 0x0715

#ifdef    Si2151_DTV_RF_AGC_SPEED_PROP
  #define Si2151_DTV_RF_AGC_SPEED_PROP_CODE 0x000715


    typedef struct { /* Si2151_DTV_RF_AGC_SPEED_PROP_struct */
      unsigned char   attack;
      unsigned char   decay;
   } Si2151_DTV_RF_AGC_SPEED_PROP_struct;

   /* DTV_RF_AGC_SPEED property, ATTACK field definition (NO TITLE)*/
   #define  Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK_LSB         0
   #define  Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK_MASK        0xff
   #define  Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK_DEFAULT    0
    #define Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK_AUTO  0

    #define Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK_ATTACK_MIN  0
    #define Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK_ATTACK_MAX  231

   /* DTV_RF_AGC_SPEED property, DECAY field definition (NO TITLE)*/
   #define  Si2151_DTV_RF_AGC_SPEED_PROP_DECAY_LSB         8
   #define  Si2151_DTV_RF_AGC_SPEED_PROP_DECAY_MASK        0xff
   #define  Si2151_DTV_RF_AGC_SPEED_PROP_DECAY_DEFAULT    0
    #define Si2151_DTV_RF_AGC_SPEED_PROP_DECAY_AUTO  0

    #define Si2151_DTV_RF_AGC_SPEED_PROP_DECAY_DECAY_MIN  0
    #define Si2151_DTV_RF_AGC_SPEED_PROP_DECAY_DECAY_MAX  231

#endif /* Si2151_DTV_RF_AGC_SPEED_PROP */

/* Si2151 DTV_RF_TOP property definition */
#define   Si2151_DTV_RF_TOP_PROP 0x0709

#ifdef    Si2151_DTV_RF_TOP_PROP
  #define Si2151_DTV_RF_TOP_PROP_CODE 0x000709


    typedef struct { /* Si2151_DTV_RF_TOP_PROP_struct */
      unsigned char   dtv_rf_top;
   } Si2151_DTV_RF_TOP_PROP_struct;

   /* DTV_RF_TOP property, DTV_RF_TOP field definition (NO TITLE)*/
   #define  Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB         0
   #define  Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK        0xff
   #define  Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_DEFAULT    0
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO     0
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P6DB     9
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P5P5DB   10
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P5DB     11
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P4P5DB   12
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P4DB     13
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P3P5DB   14
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P3DB     15
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P2P5DB   16
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P2DB     17
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P1P5DB   18
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P1DB     19
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_P0P5DB   20
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_0DB      21
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M0P5DB   22
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M1DB     23
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M1P5DB   24
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M2DB     25
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M2P5DB   26
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M3DB     27
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M3P5DB   28
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M4DB     29
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M4P5DB   30
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB     31
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M5P5DB   32
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M6DB     33
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M6P5DB   34
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M7DB     35
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M7P5DB   36
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M8DB     37
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M8P5DB   38
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M9DB     39
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M9P5DB   40
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M10DB    41
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M10P5DB  42
    #define Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_M11DB    43

#endif /* Si2151_DTV_RF_TOP_PROP */

/* Si2151 DTV_RSQ_RSSI_THRESHOLD property definition */
#define   Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP 0x0704

#ifdef    Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP
  #define Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE 0x000704


    typedef struct { /* Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_struct */
               char   lo;
   } Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_struct;

   /* DTV_RSQ_RSSI_THRESHOLD property, LO field definition (NO TITLE)*/
   #define  Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB         0
   #define  Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK        0xff
   #define  Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_DEFAULT    -80
    #define Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MIN  -128
    #define Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LO_MAX  127

#endif /* Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP */

/* Si2151 DTV_WB_AGC_SPEED property definition */
#define   Si2151_DTV_WB_AGC_SPEED_PROP 0x0717

#ifdef    Si2151_DTV_WB_AGC_SPEED_PROP
  #define Si2151_DTV_WB_AGC_SPEED_PROP_CODE 0x000717


    typedef struct { /* Si2151_DTV_WB_AGC_SPEED_PROP_struct */
      unsigned char   attack;
      unsigned char   decay;
   } Si2151_DTV_WB_AGC_SPEED_PROP_struct;

   /* DTV_WB_AGC_SPEED property, ATTACK field definition (NO TITLE)*/
   #define  Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK_LSB         0
   #define  Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK_MASK        0xff
   #define  Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK_DEFAULT    0
    #define Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK_AUTO  0

    #define Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK_ATTACK_MIN  0
    #define Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK_ATTACK_MAX  231

   /* DTV_WB_AGC_SPEED property, DECAY field definition (NO TITLE)*/
   #define  Si2151_DTV_WB_AGC_SPEED_PROP_DECAY_LSB         8
   #define  Si2151_DTV_WB_AGC_SPEED_PROP_DECAY_MASK        0xff
   #define  Si2151_DTV_WB_AGC_SPEED_PROP_DECAY_DEFAULT    0
    #define Si2151_DTV_WB_AGC_SPEED_PROP_DECAY_AUTO  0

    #define Si2151_DTV_WB_AGC_SPEED_PROP_DECAY_DECAY_MIN  0
    #define Si2151_DTV_WB_AGC_SPEED_PROP_DECAY_DECAY_MAX  231

#endif /* Si2151_DTV_WB_AGC_SPEED_PROP */

/* Si2151 TUNER_BLOCKED_VCO property definition */
#define   Si2151_TUNER_BLOCKED_VCO_PROP 0x0504

#ifdef    Si2151_TUNER_BLOCKED_VCO_PROP
  #define Si2151_TUNER_BLOCKED_VCO_PROP_CODE 0x000504


    typedef struct { /* Si2151_TUNER_BLOCKED_VCO_PROP_struct */
               int    vco_code;
   } Si2151_TUNER_BLOCKED_VCO_PROP_struct;

   /* TUNER_BLOCKED_VCO property, VCO_CODE field definition (NO TITLE)*/
   #define  Si2151_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB         0
   #define  Si2151_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK        0xffff
   #define  Si2151_TUNER_BLOCKED_VCO_PROP_VCO_CODE_DEFAULT    0x8000
    #define Si2151_TUNER_BLOCKED_VCO_PROP_VCO_CODE_VCO_CODE_MIN  -32768
    #define Si2151_TUNER_BLOCKED_VCO_PROP_VCO_CODE_VCO_CODE_MAX  32767

#endif /* Si2151_TUNER_BLOCKED_VCO_PROP */

/* Si2151 TUNER_BLOCKED_VCO2 property definition */
#define   Si2151_TUNER_BLOCKED_VCO2_PROP 0x0508

#ifdef    Si2151_TUNER_BLOCKED_VCO2_PROP
  #define Si2151_TUNER_BLOCKED_VCO2_PROP_CODE 0x000508


    typedef struct { /* Si2151_TUNER_BLOCKED_VCO2_PROP_struct */
               int    vco_code;
   } Si2151_TUNER_BLOCKED_VCO2_PROP_struct;

   /* TUNER_BLOCKED_VCO2 property, VCO_CODE field definition (NO TITLE)*/
   #define  Si2151_TUNER_BLOCKED_VCO2_PROP_VCO_CODE_LSB         0
   #define  Si2151_TUNER_BLOCKED_VCO2_PROP_VCO_CODE_MASK        0xffff
   #define  Si2151_TUNER_BLOCKED_VCO2_PROP_VCO_CODE_DEFAULT    0x8000
    #define Si2151_TUNER_BLOCKED_VCO2_PROP_VCO_CODE_VCO_CODE_MIN  -32768
    #define Si2151_TUNER_BLOCKED_VCO2_PROP_VCO_CODE_VCO_CODE_MAX  32767

#endif /* Si2151_TUNER_BLOCKED_VCO2_PROP */

/* Si2151 TUNER_BLOCKED_VCO3 property definition */
#define   Si2151_TUNER_BLOCKED_VCO3_PROP 0x0509

#ifdef    Si2151_TUNER_BLOCKED_VCO3_PROP
  #define Si2151_TUNER_BLOCKED_VCO3_PROP_CODE 0x000509


    typedef struct { /* Si2151_TUNER_BLOCKED_VCO3_PROP_struct */
               int    vco_code;
   } Si2151_TUNER_BLOCKED_VCO3_PROP_struct;

   /* TUNER_BLOCKED_VCO3 property, VCO_CODE field definition (NO TITLE)*/
   #define  Si2151_TUNER_BLOCKED_VCO3_PROP_VCO_CODE_LSB         0
   #define  Si2151_TUNER_BLOCKED_VCO3_PROP_VCO_CODE_MASK        0xffff
   #define  Si2151_TUNER_BLOCKED_VCO3_PROP_VCO_CODE_DEFAULT    0x8000
    #define Si2151_TUNER_BLOCKED_VCO3_PROP_VCO_CODE_VCO_CODE_MIN  -32768
    #define Si2151_TUNER_BLOCKED_VCO3_PROP_VCO_CODE_VCO_CODE_MAX  32767

#endif /* Si2151_TUNER_BLOCKED_VCO3_PROP */

/* Si2151 TUNER_LO_INJECTION property definition */
#define   Si2151_TUNER_LO_INJECTION_PROP 0x0506

#ifdef    Si2151_TUNER_LO_INJECTION_PROP
  #define Si2151_TUNER_LO_INJECTION_PROP_CODE 0x000506


    typedef struct { /* Si2151_TUNER_LO_INJECTION_PROP_struct */
      unsigned char   band_1;
      unsigned char   band_2;
      unsigned char   band_3;
   } Si2151_TUNER_LO_INJECTION_PROP_struct;

   /* TUNER_LO_INJECTION property, BAND_1 field definition (NO TITLE)*/
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_1_LSB         0
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_1_MASK        0x01
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_1_DEFAULT    1
    #define Si2151_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE   0
    #define Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_2 field definition (NO TITLE)*/
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_2_LSB         1
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_2_MASK        0x01
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_2_DEFAULT    0
    #define Si2151_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE   0
    #define Si2151_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE  1

   /* TUNER_LO_INJECTION property, BAND_3 field definition (NO TITLE)*/
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_3_LSB         2
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_3_MASK        0x01
   #define  Si2151_TUNER_LO_INJECTION_PROP_BAND_3_DEFAULT    0
    #define Si2151_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE   0
    #define Si2151_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE  1

#endif /* Si2151_TUNER_LO_INJECTION_PROP */

/* Si2151 TUNER_RETURN_LOSS property definition */
#define   Si2151_TUNER_RETURN_LOSS_PROP 0x0507

#ifdef    Si2151_TUNER_RETURN_LOSS_PROP
  #define Si2151_TUNER_RETURN_LOSS_PROP_CODE 0x000507


    typedef struct { /* Si2151_TUNER_RETURN_LOSS_PROP_struct */
      unsigned char   config;
      unsigned char   mode;
      unsigned char   reserved;
   } Si2151_TUNER_RETURN_LOSS_PROP_struct;

   /* TUNER_RETURN_LOSS property, CONFIG field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_LSB         0
   #define  Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_MASK        0xff
   #define  Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_DEFAULT    127
    #define Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_75   75
    #define Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_83   83
    #define Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_91   91
    #define Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_103  103
    #define Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_115  115
    #define Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_127  127

   /* TUNER_RETURN_LOSS property, MODE field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_PROP_MODE_LSB         8
   #define  Si2151_TUNER_RETURN_LOSS_PROP_MODE_MASK        0x01
   #define  Si2151_TUNER_RETURN_LOSS_PROP_MODE_DEFAULT    0
    #define Si2151_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL  0
    #define Si2151_TUNER_RETURN_LOSS_PROP_MODE_CABLE        1

   /* TUNER_RETURN_LOSS property, RESERVED field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_PROP_RESERVED_LSB         9
   #define  Si2151_TUNER_RETURN_LOSS_PROP_RESERVED_MASK        0x7f
   #define  Si2151_TUNER_RETURN_LOSS_PROP_RESERVED_DEFAULT    74
    #define Si2151_TUNER_RETURN_LOSS_PROP_RESERVED_RESERVED  74
#endif /* Si2151_TUNER_RETURN_LOSS_PROP */

/* Si2151 TUNER_RETURN_LOSS_OPTIMIZE property definition */
#define   Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP 0x050b

#ifdef    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP
  #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CODE 0x00050b


    typedef struct { /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_struct */
      unsigned char   config;
      unsigned char   disengagement_delay;
      unsigned char   engagement_delay;
      unsigned char   thld;
   } Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_struct;

   /* TUNER_RETURN_LOSS_OPTIMIZE property, CONFIG field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_LSB         3
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_MASK        0x1f
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DEFAULT    30
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_2        0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_3        1
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_4        2
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_5        3
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_6        4
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_7        5
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_8        6
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_9        7
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_10       8
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_11       9
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_13       10
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_15       11
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_17       12
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_19       13
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_23       14
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_27       15
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_31       16
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_35       17
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_39       18
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_43       19
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_47       20
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_51       21
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_59       22
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_67       23
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_75       24
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_83       25
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_91       26
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_103      27
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_115      28
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_127      29
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DISABLE  30

   /* TUNER_RETURN_LOSS_OPTIMIZE property, DISENGAGEMENT_DELAY field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_LSB         12
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_MASK        0x0f
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_DEFAULT    10
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_DISENGAGEMENT_DELAY_MIN  0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_DISENGAGEMENT_DELAY_MAX  15

   /* TUNER_RETURN_LOSS_OPTIMIZE property, ENGAGEMENT_DELAY field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_LSB         8
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_MASK        0x0f
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_DEFAULT    7
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_ENGAGEMENT_DELAY_MIN  0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_ENGAGEMENT_DELAY_MAX  15

   /* TUNER_RETURN_LOSS_OPTIMIZE property, THLD field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_LSB         0
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_MASK        0x07
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_DEFAULT    0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_THLD_MIN  0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_THLD_MAX  7

#endif /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP */

/* Si2151 TUNER_RETURN_LOSS_OPTIMIZE_2 property definition */
#define   Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP 0x050c

#ifdef    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
  #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_CODE 0x00050c


    typedef struct { /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_struct */
      unsigned char   engagement_delay;
      unsigned char   thld;
      unsigned char   window;
   } Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_struct;

   /* TUNER_RETURN_LOSS_OPTIMIZE_2 property, ENGAGEMENT_DELAY field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_LSB         8
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_MASK        0x0f
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_DEFAULT    15
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_ENGAGEMENT_DELAY_MIN  0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_ENGAGEMENT_DELAY_MAX  15

   /* TUNER_RETURN_LOSS_OPTIMIZE_2 property, THLD field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_LSB         0
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_MASK        0x1f
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_DEFAULT    31
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_THLD_MIN  0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_THLD_MAX  31

   /* TUNER_RETURN_LOSS_OPTIMIZE_2 property, WINDOW field definition (NO TITLE)*/
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_LSB         5
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_MASK        0x07
   #define  Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_DEFAULT    0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_WINDOW_MIN  0
    #define Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_WINDOW_MAX  7

#endif /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */

/* Si2151 TUNER_TF1_BOUNDARY_OFFSET property definition */
#define   Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP 0x050f

#ifdef    Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP
  #define Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_CODE 0x00050f


    typedef struct { /* Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_struct */
               int    tf1_boundary_offset;
   } Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_struct;

   /* TUNER_TF1_BOUNDARY_OFFSET property, TF1_BOUNDARY_OFFSET field definition (NO TITLE)*/
   #define  Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_LSB         0
   #define  Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_MASK        0xffff
   #define  Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_DEFAULT    0
    #define Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_TF1_OFFSET_MIN  -100
    #define Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_TF1_OFFSET_MAX  100

#endif /* Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP */

/* Si2151 XOUT property definition */
#define   Si2151_XOUT_PROP 0x0404

#ifdef    Si2151_XOUT_PROP
  #define Si2151_XOUT_PROP_CODE 0x000404


    typedef struct { /* Si2151_XOUT_PROP_struct */
      unsigned char   amp;
   } Si2151_XOUT_PROP_struct;

   /* XOUT property, AMP field definition (NO TITLE)*/
   #define  Si2151_XOUT_PROP_AMP_LSB         0
   #define  Si2151_XOUT_PROP_AMP_MASK        0x01
   #define  Si2151_XOUT_PROP_AMP_DEFAULT    0
    #define Si2151_XOUT_PROP_AMP_HIGH  0
    #define Si2151_XOUT_PROP_AMP_LOW   1

#endif /* Si2151_XOUT_PROP */



  /* --------------------------------------------*/
  /* PROPERTIES STRUCT                           */
  /* This stores all property fields             */
  /* --------------------------------------------*/
  typedef struct {
    #ifdef    Si2151_ATV_AGC_SPEED_PROP
              Si2151_ATV_AGC_SPEED_PROP_struct                 atv_agc_speed;
    #endif /* Si2151_ATV_AGC_SPEED_PROP */
    #ifdef    Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP
              Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_struct        atv_agc_speed_low_rssi;
    #endif /* Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef    Si2151_ATV_ARTIFICIAL_SNOW_PROP
              Si2151_ATV_ARTIFICIAL_SNOW_PROP_struct           atv_artificial_snow;
    #endif /* Si2151_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef    Si2151_ATV_CONFIG_IF_PORT_PROP
              Si2151_ATV_CONFIG_IF_PORT_PROP_struct            atv_config_if_port;
    #endif /* Si2151_ATV_CONFIG_IF_PORT_PROP */
    #ifdef    Si2151_ATV_EXT_AGC_PROP
              Si2151_ATV_EXT_AGC_PROP_struct                   atv_ext_agc;
    #endif /* Si2151_ATV_EXT_AGC_PROP */
    #ifdef    Si2151_ATV_HSYNC_OUT_PROP
              Si2151_ATV_HSYNC_OUT_PROP_struct                 atv_hsync_out;
    #endif /* Si2151_ATV_HSYNC_OUT_PROP */
    #ifdef    Si2151_ATV_LIF_FREQ_PROP
              Si2151_ATV_LIF_FREQ_PROP_struct                  atv_lif_freq;
    #endif /* Si2151_ATV_LIF_FREQ_PROP */
    #ifdef    Si2151_ATV_LIF_OUT_PROP
              Si2151_ATV_LIF_OUT_PROP_struct                   atv_lif_out;
    #endif /* Si2151_ATV_LIF_OUT_PROP */
    #ifdef    Si2151_ATV_PGA_LIMITS_PROP
              Si2151_ATV_PGA_LIMITS_PROP_struct                atv_pga_limits;
    #endif /* Si2151_ATV_PGA_LIMITS_PROP */
    #ifdef    Si2151_ATV_PGA_TARGET_PROP
              Si2151_ATV_PGA_TARGET_PROP_struct                atv_pga_target;
    #endif /* Si2151_ATV_PGA_TARGET_PROP */
    #ifdef    Si2151_ATV_RF_TOP_PROP
              Si2151_ATV_RF_TOP_PROP_struct                    atv_rf_top;
    #endif /* Si2151_ATV_RF_TOP_PROP */
    #ifdef    Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP
              Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_struct        atv_rsq_rssi_threshold;
    #endif /* Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef    Si2151_ATV_VIDEO_MODE_PROP
              Si2151_ATV_VIDEO_MODE_PROP_struct                atv_video_mode;
    #endif /* Si2151_ATV_VIDEO_MODE_PROP */
    #ifdef    Si2151_ATV_VSNR_CAP_PROP
              Si2151_ATV_VSNR_CAP_PROP_struct                  atv_vsnr_cap;
    #endif /* Si2151_ATV_VSNR_CAP_PROP */
    #ifdef    Si2151_CRYSTAL_TRIM_PROP
              Si2151_CRYSTAL_TRIM_PROP_struct                  crystal_trim;
    #endif /* Si2151_CRYSTAL_TRIM_PROP */
    #ifdef    Si2151_DTV_AGC_AUTO_FREEZE_PROP
              Si2151_DTV_AGC_AUTO_FREEZE_PROP_struct           dtv_agc_auto_freeze;
    #endif /* Si2151_DTV_AGC_AUTO_FREEZE_PROP */
    #ifdef    Si2151_DTV_AGC_SPEED_PROP
              Si2151_DTV_AGC_SPEED_PROP_struct                 dtv_agc_speed;
    #endif /* Si2151_DTV_AGC_SPEED_PROP */
    #ifdef    Si2151_DTV_CONFIG_IF_PORT_PROP
              Si2151_DTV_CONFIG_IF_PORT_PROP_struct            dtv_config_if_port;
    #endif /* Si2151_DTV_CONFIG_IF_PORT_PROP */
    #ifdef    Si2151_DTV_EXT_AGC_PROP
              Si2151_DTV_EXT_AGC_PROP_struct                   dtv_ext_agc;
    #endif /* Si2151_DTV_EXT_AGC_PROP */
    #ifdef    Si2151_DTV_IF_AGC_SPEED_PROP
              Si2151_DTV_IF_AGC_SPEED_PROP_struct              dtv_if_agc_speed;
    #endif /* Si2151_DTV_IF_AGC_SPEED_PROP */
    #ifdef    Si2151_DTV_INITIAL_AGC_SPEED_PROP
              Si2151_DTV_INITIAL_AGC_SPEED_PROP_struct         dtv_initial_agc_speed;
    #endif /* Si2151_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef    Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
              Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_struct  dtv_initial_agc_speed_period;
    #endif /* Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef    Si2151_DTV_INTERNAL_ZIF_PROP
              Si2151_DTV_INTERNAL_ZIF_PROP_struct              dtv_internal_zif;
    #endif /* Si2151_DTV_INTERNAL_ZIF_PROP */
    #ifdef    Si2151_DTV_LIF_FREQ_PROP
              Si2151_DTV_LIF_FREQ_PROP_struct                  dtv_lif_freq;
    #endif /* Si2151_DTV_LIF_FREQ_PROP */
    #ifdef    Si2151_DTV_LIF_OUT_PROP
              Si2151_DTV_LIF_OUT_PROP_struct                   dtv_lif_out;
    #endif /* Si2151_DTV_LIF_OUT_PROP */
    #ifdef    Si2151_DTV_MODE_PROP
              Si2151_DTV_MODE_PROP_struct                      dtv_mode;
    #endif /* Si2151_DTV_MODE_PROP */
    #ifdef    Si2151_DTV_PGA_LIMITS_PROP
              Si2151_DTV_PGA_LIMITS_PROP_struct                dtv_pga_limits;
    #endif /* Si2151_DTV_PGA_LIMITS_PROP */
    #ifdef    Si2151_DTV_PGA_TARGET_PROP
              Si2151_DTV_PGA_TARGET_PROP_struct                dtv_pga_target;
    #endif /* Si2151_DTV_PGA_TARGET_PROP */
    #ifdef    Si2151_DTV_RF_AGC_SPEED_PROP
              Si2151_DTV_RF_AGC_SPEED_PROP_struct              dtv_rf_agc_speed;
    #endif /* Si2151_DTV_RF_AGC_SPEED_PROP */
    #ifdef    Si2151_DTV_RF_TOP_PROP
              Si2151_DTV_RF_TOP_PROP_struct                    dtv_rf_top;
    #endif /* Si2151_DTV_RF_TOP_PROP */
    #ifdef    Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP
              Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_struct        dtv_rsq_rssi_threshold;
    #endif /* Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef    Si2151_DTV_WB_AGC_SPEED_PROP
              Si2151_DTV_WB_AGC_SPEED_PROP_struct              dtv_wb_agc_speed;
    #endif /* Si2151_DTV_WB_AGC_SPEED_PROP */
    #ifdef    Si2151_TUNER_BLOCKED_VCO_PROP
              Si2151_TUNER_BLOCKED_VCO_PROP_struct             tuner_blocked_vco;
    #endif /* Si2151_TUNER_BLOCKED_VCO_PROP */
    #ifdef    Si2151_TUNER_BLOCKED_VCO2_PROP
              Si2151_TUNER_BLOCKED_VCO2_PROP_struct            tuner_blocked_vco2;
    #endif /* Si2151_TUNER_BLOCKED_VCO2_PROP */
    #ifdef    Si2151_TUNER_BLOCKED_VCO3_PROP
              Si2151_TUNER_BLOCKED_VCO3_PROP_struct            tuner_blocked_vco3;
    #endif /* Si2151_TUNER_BLOCKED_VCO3_PROP */
    #ifdef    Si2151_TUNER_LO_INJECTION_PROP
              Si2151_TUNER_LO_INJECTION_PROP_struct            tuner_lo_injection;
    #endif /* Si2151_TUNER_LO_INJECTION_PROP */
    #ifdef    Si2151_TUNER_RETURN_LOSS_PROP
              Si2151_TUNER_RETURN_LOSS_PROP_struct             tuner_return_loss;
    #endif /* Si2151_TUNER_RETURN_LOSS_PROP */
    #ifdef    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP
              Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_struct    tuner_return_loss_optimize;
    #endif /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP */
    #ifdef    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
              Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_struct  tuner_return_loss_optimize_2;
    #endif /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */
    #ifdef    Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP
              Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_struct     tuner_tf1_boundary_offset;
    #endif /* Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP */
    #ifdef    Si2151_XOUT_PROP
              Si2151_XOUT_PROP_struct                          xout;
    #endif /* Si2151_XOUT_PROP */
  } Si2151_PropObj;

/* #define   Si2151_GET_PROPERTY_STRING */

#endif /* _Si2151_PROPERTIES_H_ */







