/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API commands structures and functions definitions
   FILE: Si21XXC_Commands.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef    Si21XXC_COMMANDS_H
#define    Si21XXC_COMMANDS_H

/* _status_defines_insertion_start */

#ifdef __cplusplus
extern "C"{
#endif
/* STATUS structure definition */
  typedef struct { /* Si21XXC_COMMON_REPLY_struct */
    unsigned char   tunint;
    unsigned char   atvint;
    unsigned char   dtvint;
    unsigned char   err;
    unsigned char   cts;
 }  Si21XXC_COMMON_REPLY_struct;

/* STATUS fields definition */
  /* STATUS, TUNINT field definition (address 0, size 1, lsb 0, unsigned)*/
  #define  Si21XXC_STATUS_TUNINT_LSB         0
  #define  Si21XXC_STATUS_TUNINT_MASK        0x01
   #define Si21XXC_STATUS_TUNINT_NOT_TRIGGERED  0
   #define Si21XXC_STATUS_TUNINT_TRIGGERED      1
  /* STATUS, ATVINT field definition (address 0, size 1, lsb 1, unsigned)*/
  #define  Si21XXC_STATUS_ATVINT_LSB         1
  #define  Si21XXC_STATUS_ATVINT_MASK        0x01
   #define Si21XXC_STATUS_ATVINT_NOT_TRIGGERED  0
   #define Si21XXC_STATUS_ATVINT_TRIGGERED      1
  /* STATUS, DTVINT field definition (address 0, size 1, lsb 2, unsigned)*/
  #define  Si21XXC_STATUS_DTVINT_LSB         2
  #define  Si21XXC_STATUS_DTVINT_MASK        0x01
   #define Si21XXC_STATUS_DTVINT_NOT_TRIGGERED  0
   #define Si21XXC_STATUS_DTVINT_TRIGGERED      1
  /* STATUS, ERR field definition (address 0, size 1, lsb 6, unsigned)*/
  #define  Si21XXC_STATUS_ERR_LSB         6
  #define  Si21XXC_STATUS_ERR_MASK        0x01
   #define Si21XXC_STATUS_ERR_ERROR     1
   #define Si21XXC_STATUS_ERR_NO_ERROR  0
  /* STATUS, CTS field definition (address 0, size 1, lsb 7, unsigned)*/
  #define  Si21XXC_STATUS_CTS_LSB         7
  #define  Si21XXC_STATUS_CTS_MASK        0x01
   #define Si21XXC_STATUS_CTS_COMPLETED  1
   #define Si21XXC_STATUS_CTS_WAIT       0

/* _status_defines_insertion_point */

/* _commands_defines_insertion_start */
/* Si21XXC_AGC_OVERRIDE command definition */
#define   Si21XXC_AGC_OVERRIDE_CMD 0x44

#ifdef    Si21XXC_AGC_OVERRIDE_CMD
  #define Si21XXC_AGC_OVERRIDE_CMD_CODE 0x010044

    typedef struct { /* Si21XXC_AGC_OVERRIDE_CMD_struct */
     unsigned char   force_max_gain;
     unsigned char   force_top_gain;
   } Si21XXC_AGC_OVERRIDE_CMD_struct;


    typedef struct { /* Si21XXC_AGC_OVERRIDE_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_AGC_OVERRIDE_CMD_REPLY_struct;

   /* AGC_OVERRIDE command, FORCE_MAX_GAIN field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB         0
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK        0x01
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MIN         0
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX         1
    #define Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE  0
    #define Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE   1
   /* AGC_OVERRIDE command, FORCE_TOP_GAIN field definition (address 1,size 1, lsb 1, unsigned) */
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB         1
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK        0x01
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MIN         0
   #define  Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX         1
    #define Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE  0
    #define Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE   1
#endif /* Si21XXC_AGC_OVERRIDE_CMD */

/* Si21XXC_ATV_RESTART command definition */
#define   Si21XXC_ATV_RESTART_CMD 0x51

#ifdef    Si21XXC_ATV_RESTART_CMD
  #define Si21XXC_ATV_RESTART_CMD_CODE 0x010051

    typedef struct { /* Si21XXC_ATV_RESTART_CMD_struct */
     unsigned char   mode;
   } Si21XXC_ATV_RESTART_CMD_struct;


    typedef struct { /* Si21XXC_ATV_RESTART_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_ATV_RESTART_CMD_REPLY_struct;

   /* ATV_RESTART command, MODE field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_ATV_RESTART_CMD_MODE_LSB         0
   #define  Si21XXC_ATV_RESTART_CMD_MODE_MASK        0x01
   #define  Si21XXC_ATV_RESTART_CMD_MODE_MIN         0
   #define  Si21XXC_ATV_RESTART_CMD_MODE_MAX         1
    #define Si21XXC_ATV_RESTART_CMD_MODE_AUDIO_ONLY   1
    #define Si21XXC_ATV_RESTART_CMD_MODE_AUDIO_VIDEO  0
#endif /* Si21XXC_ATV_RESTART_CMD */

/* Si21XXC_ATV_STATUS command definition */
#define   Si21XXC_ATV_STATUS_CMD 0x52

#ifdef    Si21XXC_ATV_STATUS_CMD
  #define Si21XXC_ATV_STATUS_CMD_CODE 0x010052

    typedef struct { /* Si21XXC_ATV_STATUS_CMD_struct */
     unsigned char   intack;
   } Si21XXC_ATV_STATUS_CMD_struct;


    typedef struct { /* Si21XXC_ATV_STATUS_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   chlint;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   snrlint;
      unsigned char   snrhint;
      unsigned char   audio_chan_bw;
               char   sound_level;
      unsigned char   chl;
      unsigned char   pcl;
      unsigned char   dl;
      unsigned char   snrl;
      unsigned char   snrh;
      unsigned char   video_snr;
               int    afc_freq;
               int    video_sc_spacing;
      unsigned char   video_sys;
      unsigned char   color;
      unsigned char   lines;
      unsigned char   audio_sys;
   }  Si21XXC_ATV_STATUS_CMD_REPLY_struct;

   /* ATV_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_ATV_STATUS_CMD_INTACK_LSB         0
   #define  Si21XXC_ATV_STATUS_CMD_INTACK_MASK        0x01
   #define  Si21XXC_ATV_STATUS_CMD_INTACK_MIN         0
   #define  Si21XXC_ATV_STATUS_CMD_INTACK_MAX         1
    #define Si21XXC_ATV_STATUS_CMD_INTACK_CLEAR  1
    #define Si21XXC_ATV_STATUS_CMD_INTACK_OK     0
   /* ATV_STATUS command, CHLINT field definition (address 1, size 1, lsb 0, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_CHLINT_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_CHLINT_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_CHLINT_CHANGED    1
    #define Si21XXC_ATV_STATUS_RESPONSE_CHLINT_NO_CHANGE  0
   /* ATV_STATUS command, PCLINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si21XXC_ATV_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si21XXC_ATV_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* ATV_STATUS command, DLINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si21XXC_ATV_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si21XXC_ATV_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* ATV_STATUS command, SNRLINT field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRLINT_LSB         3
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRLINT_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRLINT_CHANGED    1
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRLINT_NO_CHANGE  0
   /* ATV_STATUS command, SNRHINT field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRHINT_LSB         4
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRHINT_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRHINT_CHANGED    1
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRHINT_NO_CHANGE  0
   /* ATV_STATUS command, AUDIO_CHAN_BW field definition (address 10, size 4, lsb 0, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_MASK        0x0f
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_12X_OVERMOD     3
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_150_KHZ_OFFSET  8
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_15_KHZ_OFFSET   5
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_30_KHZ_OFFSET   6
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_4X_OVERMOD      1
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_75_KHZ_OFFSET   7
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_7P5_KHZ_OFFSET  4
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_8X_OVERMOD      2
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_CUSTOM          9
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_RSVD            0
   /* ATV_STATUS command, SOUND_LEVEL field definition (address 11, size 8, lsb 0, signed)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_SOUND_LEVEL_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_SOUND_LEVEL_MASK        0xff
   #define  Si21XXC_ATV_STATUS_RESPONSE_SOUND_LEVEL_SHIFT       24
   /* ATV_STATUS command, CHL field definition (address 2, size 1, lsb 0, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_CHL_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_CHL_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_CHL_CHANNEL     1
    #define Si21XXC_ATV_STATUS_RESPONSE_CHL_NO_CHANNEL  0
   /* ATV_STATUS command, PCL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_PCL_LSB         1
   #define  Si21XXC_ATV_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si21XXC_ATV_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* ATV_STATUS command, DL field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_DL_LSB         2
   #define  Si21XXC_ATV_STATUS_RESPONSE_DL_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_DL_LOCKED   1
    #define Si21XXC_ATV_STATUS_RESPONSE_DL_NO_LOCK  0
   /* ATV_STATUS command, SNRL field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRL_LSB         3
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRL_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRL_SNR_LOW      1
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRL_SNR_NOT_LOW  0
   /* ATV_STATUS command, SNRH field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRH_LSB         4
   #define  Si21XXC_ATV_STATUS_RESPONSE_SNRH_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRH_SNR_HIGH      1
    #define Si21XXC_ATV_STATUS_RESPONSE_SNRH_SNR_NOT_HIGH  0
   /* ATV_STATUS command, VIDEO_SNR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SNR_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SNR_MASK        0xff
   /* ATV_STATUS command, AFC_FREQ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si21XXC_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* ATV_STATUS command, VIDEO_SC_SPACING field definition (address 6, size 16, lsb 0, signed)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_MASK        0xffff
   #define  Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_SHIFT       16
   /* ATV_STATUS command, VIDEO_SYS field definition (address 8, size 3, lsb 0, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_MASK        0x07
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_B   0
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_DK  5
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_GH  1
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_I   4
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_L   6
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_LP  7
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_M   2
    #define Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_N   3
   /* ATV_STATUS command, COLOR field definition (address 8, size 1, lsb 4, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_COLOR_LSB         4
   #define  Si21XXC_ATV_STATUS_RESPONSE_COLOR_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_COLOR_PAL_NTSC  0
    #define Si21XXC_ATV_STATUS_RESPONSE_COLOR_SECAM     1
   /* ATV_STATUS command, LINES field definition (address 8, size 1, lsb 7, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_LINES_LSB         7
   #define  Si21XXC_ATV_STATUS_RESPONSE_LINES_MASK        0x01
    #define Si21XXC_ATV_STATUS_RESPONSE_LINES_525  0
    #define Si21XXC_ATV_STATUS_RESPONSE_LINES_625  1
   /* ATV_STATUS command, AUDIO_SYS field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_LSB         0
   #define  Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_MASK        0x0f
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_A2               3
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_A2_DK2           4
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_A2_DK3           5
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_A2_DK4           9
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_BTSC             6
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_EIAJ             7
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_MONO             1
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_MONO_NICAM       2
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_MONO_NICAM_10DB  12
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_MONO_NICAM_6DB   11
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_RSVD             0
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_SCAN             8
    #define Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_WIDE_SCAN        10

#endif /* Si21XXC_ATV_STATUS_CMD */

/* Si21XXC_CONFIG_CLOCKS command definition */
#define   Si21XXC_CONFIG_CLOCKS_CMD 0xc0

#ifdef    Si21XXC_CONFIG_CLOCKS_CMD
  #define Si21XXC_CONFIG_CLOCKS_CMD_CODE 0x0100c0

    typedef struct { /* Si21XXC_CONFIG_CLOCKS_CMD_struct */
     unsigned char   subcode;
     unsigned char   clock_mode;
     unsigned char   en_xout;
   } Si21XXC_CONFIG_CLOCKS_CMD_struct;


    typedef struct { /* Si21XXC_CONFIG_CLOCKS_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_CONFIG_CLOCKS_CMD_REPLY_struct;

   /* CONFIG_CLOCKS command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_LSB         0
   #define  Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_MASK        0xff
   #define  Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_MIN         0
   #define  Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_MAX         0
    #define Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_CODE  0
   /* CONFIG_CLOCKS command, CLOCK_MODE field definition (address 2,size 2, lsb 0, unsigned) */
   #define  Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_LSB         0
   #define  Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_MASK        0x03
   #define  Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_MIN         0
   #define  Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_MAX         2
    #define Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_EXTCLK  2
    #define Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL    0
   /* CONFIG_CLOCKS command, EN_XOUT field definition (address 2,size 3, lsb 2, unsigned) */
   #define  Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_LSB         2
   #define  Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_MASK        0x07
   #define  Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_MIN         0
   #define  Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_MAX         3
    #define Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_DIS_XOUT  0
    #define Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_EN_XOUT   3
#endif /* Si21XXC_CONFIG_CLOCKS_CMD */

/* Si21XXC_CONFIG_I2C command definition */
#define   Si21XXC_CONFIG_I2C_CMD 0xc0

#ifdef    Si21XXC_CONFIG_I2C_CMD
  #define Si21XXC_CONFIG_I2C_CMD_CODE 0x0200c0

    typedef struct { /* Si21XXC_CONFIG_I2C_CMD_struct */
     unsigned char   subcode;
     unsigned char   i2c_broadcast;
   } Si21XXC_CONFIG_I2C_CMD_struct;


    typedef struct { /* Si21XXC_CONFIG_I2C_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_CONFIG_I2C_CMD_REPLY_struct;

   /* CONFIG_I2C command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si21XXC_CONFIG_I2C_CMD_SUBCODE_LSB         0
   #define  Si21XXC_CONFIG_I2C_CMD_SUBCODE_MASK        0xff
   #define  Si21XXC_CONFIG_I2C_CMD_SUBCODE_MIN         36
   #define  Si21XXC_CONFIG_I2C_CMD_SUBCODE_MAX         36
    #define Si21XXC_CONFIG_I2C_CMD_SUBCODE_CODE  36
   /* CONFIG_I2C command, I2C_BROADCAST field definition (address 2,size 2, lsb 0, unsigned) */
   #define  Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_LSB         0
   #define  Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_MASK        0x03
   #define  Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_MIN         0
   #define  Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_MAX         1
    #define Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_DISABLED  0
    #define Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_ENABLED   1
#endif /* Si21XXC_CONFIG_I2C_CMD */

/* Si2178B_CONFIG_PINS command definition */
#define   Si2178B_CONFIG_PINS_CMD 0x12

/* setup "super" structs to handle both Si2178B and Si2190B CONFIG_PINS cases. */
/* use Si21XXC as prefix for these structs (CMD and CMD_REPLY) */
   typedef struct { /* Si21XXC_CONFIG_PINS_CMD_struct */
     unsigned char   gpio1_mode;
     unsigned char   gpio1_read;
     unsigned char   gpio2_mode;
     unsigned char   gpio2_read;
     unsigned char   reserved1;
     unsigned char   reserved2;
     unsigned char   agc1_mode;
     unsigned char   agc1_read;
     unsigned char   agc2_mode;
     unsigned char   agc2_read;
     unsigned char   reserved3;
   } Si21XXC_CONFIG_PINS_CMD_struct;


    typedef struct { /* Si21XXC_CONFIG_PINS_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   gpio1_mode;
      unsigned char   gpio1_state;
      unsigned char   gpio2_mode;
      unsigned char   gpio2_state;
      unsigned char   reserved1;
      unsigned char   reserved2;
      unsigned char   reserved3;
      unsigned char   agc1_mode;
      unsigned char   agc1_state;
      unsigned char   agc2_mode;
      unsigned char   agc2_state;
   }  Si21XXC_CONFIG_PINS_CMD_REPLY_struct;

#ifdef    Si2178B_CONFIG_PINS_CMD
  #define Si2178B_CONFIG_PINS_CMD_CODE 0x010012
   /* CONFIG_PINS command, GPIO1_MODE field definition (address 1,size 7, lsb 0, unsigned) */
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_LSB         0
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_MASK        0x7f
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_MIN         0
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_MAX         3
    #define Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE    1
    #define Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_0    2
    #define Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_1    3
    #define Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, GPIO1_READ field definition (address 1,size 1, lsb 7, unsigned) */
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_READ_LSB         7
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_READ_MASK        0x01
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_READ_MIN         0
   #define  Si2178B_CONFIG_PINS_CMD_GPIO1_READ_MAX         1
    #define Si2178B_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ  0
    #define Si2178B_CONFIG_PINS_CMD_GPIO1_READ_READ         1
   /* CONFIG_PINS command, GPIO2_MODE field definition (address 2,size 7, lsb 0, unsigned) */
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_LSB         0
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_MASK        0x7f
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_MIN         0
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_MAX         3
    #define Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_DISABLE    1
    #define Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_DRIVE_0    2
    #define Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_DRIVE_1    3
    #define Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, GPIO2_READ field definition (address 2,size 1, lsb 7, unsigned) */
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_READ_LSB         7
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_READ_MASK        0x01
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_READ_MIN         0
   #define  Si2178B_CONFIG_PINS_CMD_GPIO2_READ_MAX         1
    #define Si2178B_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ  0
    #define Si2178B_CONFIG_PINS_CMD_GPIO2_READ_READ         1
   /* CONFIG_PINS command, RESERVED1 field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED1_LSB         0
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED1_MASK        0xff
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED1_MIN         1
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED1_MAX         1
    #define Si2178B_CONFIG_PINS_CMD_RESERVED1_RESERVED  1
   /* CONFIG_PINS command, RESERVED2 field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED2_LSB         0
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED2_MASK        0xff
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED2_MIN         1
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED2_MAX         1
    #define Si2178B_CONFIG_PINS_CMD_RESERVED2_RESERVED  1
   /* CONFIG_PINS command, RESERVED3 field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED3_LSB         0
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED3_MASK        0xff
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED3_MIN         1
   #define  Si2178B_CONFIG_PINS_CMD_RESERVED3_MAX         1
    #define Si2178B_CONFIG_PINS_CMD_RESERVED3_RESERVED  1
   /* CONFIG_PINS command, GPIO1_MODE field definition (address 1, size 7, lsb 0, unsigned)*/
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB         0
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK        0x7f
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO1_MODE_DISABLE  1
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_0  2
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_1  3
   /* CONFIG_PINS command, GPIO1_STATE field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB         7
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK        0x01
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_0  0
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_1  1
   /* CONFIG_PINS command, GPIO2_MODE field definition (address 2, size 7, lsb 0, unsigned)*/
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB         0
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK        0x7f
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO2_MODE_DISABLE  1
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO2_MODE_DRIVE_0  2
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO2_MODE_DRIVE_1  3
   /* CONFIG_PINS command, GPIO2_STATE field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB         7
   #define  Si2178B_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK        0x01
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO2_STATE_READ_0  0
    #define Si2178B_CONFIG_PINS_RESPONSE_GPIO2_STATE_READ_1  1
   /* CONFIG_PINS command, RESERVED1 field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2178B_CONFIG_PINS_RESPONSE_RESERVED1_LSB         0
   #define  Si2178B_CONFIG_PINS_RESPONSE_RESERVED1_MASK        0xff
    #define Si2178B_CONFIG_PINS_RESPONSE_RESERVED1_RESERVED1_MIN  1
    #define Si2178B_CONFIG_PINS_RESPONSE_RESERVED1_RESERVED1_MAX  1
   /* CONFIG_PINS command, RESERVED2 field definition (address 4, size 8, lsb 0, unsigned)*/
   #define  Si2178B_CONFIG_PINS_RESPONSE_RESERVED2_LSB         0
   #define  Si2178B_CONFIG_PINS_RESPONSE_RESERVED2_MASK        0xff
    #define Si2178B_CONFIG_PINS_RESPONSE_RESERVED2_RESERVED2_MIN  1
    #define Si2178B_CONFIG_PINS_RESPONSE_RESERVED2_RESERVED2_MAX  1
   /* CONFIG_PINS command, RESERVED3 field definition (address 5, size 8, lsb 0, unsigned)*/
   #define  Si2178B_CONFIG_PINS_RESPONSE_RESERVED3_LSB         0
   #define  Si2178B_CONFIG_PINS_RESPONSE_RESERVED3_MASK        0xff
    #define Si2178B_CONFIG_PINS_RESPONSE_RESERVED3_RESERVED3_MIN  1
    #define Si2178B_CONFIG_PINS_RESPONSE_RESERVED3_RESERVED3_MAX  1

#endif /* Si2178B_CONFIG_PINS_CMD */

/* Si2190B_CONFIG_PINS command definition */
#define   Si2190B_CONFIG_PINS_CMD 0x12

#ifdef    Si2190B_CONFIG_PINS_CMD
  #define Si2190B_CONFIG_PINS_CMD_CODE 0x020012

   /* CONFIG_PINS command, GPIO1_MODE field definition (address 1,size 7, lsb 0, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_MASK        0x7f
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_MAX         5
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE    1
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_0    2
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_1    3
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_ISL_RX     5
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_ISL_TX     4
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, GPIO1_READ field definition (address 1,size 1, lsb 7, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_READ_LSB         7
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_READ_MASK        0x01
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_READ_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_GPIO1_READ_MAX         1
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ  0
    #define Si2190B_CONFIG_PINS_CMD_GPIO1_READ_READ         1
   /* CONFIG_PINS command, GPIO2_MODE field definition (address 2,size 7, lsb 0, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_MASK        0x7f
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_MAX         5
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_DISABLE    1
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_DRIVE_0    2
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_DRIVE_1    3
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_ISL_RX     5
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_ISL_TX     4
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, GPIO2_READ field definition (address 2,size 1, lsb 7, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_READ_LSB         7
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_READ_MASK        0x01
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_READ_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_GPIO2_READ_MAX         1
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ  0
    #define Si2190B_CONFIG_PINS_CMD_GPIO2_READ_READ         1
   /* CONFIG_PINS command, AGC1_MODE field definition (address 3,size 7, lsb 0, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_MODE_MASK        0x7f
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_MODE_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_MODE_MAX         5
    #define Si2190B_CONFIG_PINS_CMD_AGC1_MODE_DISABLE    1
    #define Si2190B_CONFIG_PINS_CMD_AGC1_MODE_DRIVE_0    2
    #define Si2190B_CONFIG_PINS_CMD_AGC1_MODE_DRIVE_1    3
    #define Si2190B_CONFIG_PINS_CMD_AGC1_MODE_ISL_RX     5
    #define Si2190B_CONFIG_PINS_CMD_AGC1_MODE_ISL_TX     4
    #define Si2190B_CONFIG_PINS_CMD_AGC1_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, AGC1_READ field definition (address 3,size 1, lsb 7, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_READ_LSB         7
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_READ_MASK        0x01
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_READ_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_AGC1_READ_MAX         1
    #define Si2190B_CONFIG_PINS_CMD_AGC1_READ_DO_NOT_READ  0
    #define Si2190B_CONFIG_PINS_CMD_AGC1_READ_READ         1
   /* CONFIG_PINS command, AGC2_MODE field definition (address 4,size 7, lsb 0, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_MODE_MASK        0x7f
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_MODE_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_MODE_MAX         5
    #define Si2190B_CONFIG_PINS_CMD_AGC2_MODE_DISABLE    1
    #define Si2190B_CONFIG_PINS_CMD_AGC2_MODE_DRIVE_0    2
    #define Si2190B_CONFIG_PINS_CMD_AGC2_MODE_DRIVE_1    3
    #define Si2190B_CONFIG_PINS_CMD_AGC2_MODE_ISL_RX     5
    #define Si2190B_CONFIG_PINS_CMD_AGC2_MODE_ISL_TX     4
    #define Si2190B_CONFIG_PINS_CMD_AGC2_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, AGC2_READ field definition (address 4,size 1, lsb 7, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_READ_LSB         7
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_READ_MASK        0x01
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_READ_MIN         0
   #define  Si2190B_CONFIG_PINS_CMD_AGC2_READ_MAX         1
    #define Si2190B_CONFIG_PINS_CMD_AGC2_READ_DO_NOT_READ  0
    #define Si2190B_CONFIG_PINS_CMD_AGC2_READ_READ         1
   /* CONFIG_PINS command, RESERVED3 field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si2190B_CONFIG_PINS_CMD_RESERVED3_LSB         0
   #define  Si2190B_CONFIG_PINS_CMD_RESERVED3_MASK        0xff
   #define  Si2190B_CONFIG_PINS_CMD_RESERVED3_MIN         1
   #define  Si2190B_CONFIG_PINS_CMD_RESERVED3_MAX         1
    #define Si2190B_CONFIG_PINS_CMD_RESERVED3_RESERVED  1
   /* CONFIG_PINS command, GPIO1_MODE field definition (address 1, size 7, lsb 0, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK        0x7f
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_DISABLE  1
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_0  2
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_1  3
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_ISL_RX   5
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_ISL_TX   4
   /* CONFIG_PINS command, GPIO1_STATE field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB         7
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK        0x01
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_0  0
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_1  1
   /* CONFIG_PINS command, GPIO2_MODE field definition (address 2, size 7, lsb 0, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK        0x7f
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_DISABLE  1
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_DRIVE_0  2
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_DRIVE_1  3
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_ISL_RX   5
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_ISL_TX   4
   /* CONFIG_PINS command, GPIO2_STATE field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB         7
   #define  Si2190B_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK        0x01
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO2_STATE_READ_0  0
    #define Si2190B_CONFIG_PINS_RESPONSE_GPIO2_STATE_READ_1  1
   /* CONFIG_PINS command, AGC1_MODE field definition (address 3, size 7, lsb 0, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_MASK        0x7f
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_DISABLE  1
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_DRIVE_0  2
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_DRIVE_1  3
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_ISL_RX   5
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_ISL_TX   4
   /* CONFIG_PINS command, AGC1_STATE field definition (address 3, size 1, lsb 7, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC1_STATE_LSB         7
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC1_STATE_MASK        0x01
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC1_STATE_READ_0  0
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC1_STATE_READ_1  1
   /* CONFIG_PINS command, AGC2_MODE field definition (address 4, size 7, lsb 0, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_LSB         0
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_MASK        0x7f
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_DISABLE  1
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_DRIVE_0  2
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_DRIVE_1  3
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_ISL_RX   5
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_ISL_TX   4
   /* CONFIG_PINS command, AGC2_STATE field definition (address 4, size 1, lsb 7, unsigned)*/
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC2_STATE_LSB         7
   #define  Si2190B_CONFIG_PINS_RESPONSE_AGC2_STATE_MASK        0x01
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC2_STATE_READ_0  0
    #define Si2190B_CONFIG_PINS_RESPONSE_AGC2_STATE_READ_1  1

#endif /* Si2190B_CONFIG_PINS_CMD */


/* Si21XXC_DTV_RESTART command definition */
#define   Si21XXC_DTV_RESTART_CMD 0x61

#ifdef    Si21XXC_DTV_RESTART_CMD
  #define Si21XXC_DTV_RESTART_CMD_CODE 0x010061

    typedef struct { /* Si21XXC_DTV_RESTART_CMD_struct */
         unsigned char   nothing;   } Si21XXC_DTV_RESTART_CMD_struct;


    typedef struct { /* Si21XXC_DTV_RESTART_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_DTV_RESTART_CMD_REPLY_struct;

#endif /* Si21XXC_DTV_RESTART_CMD */

/* Si21XXC_DTV_STATUS command definition */
#define   Si21XXC_DTV_STATUS_CMD 0x62

#ifdef    Si21XXC_DTV_STATUS_CMD
  #define Si21XXC_DTV_STATUS_CMD_CODE 0x010062

    typedef struct { /* Si21XXC_DTV_STATUS_CMD_struct */
     unsigned char   intack;
   } Si21XXC_DTV_STATUS_CMD_struct;


    typedef struct { /* Si21XXC_DTV_STATUS_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   chlint;
      unsigned char   chl;
      unsigned char   bw;
      unsigned char   modulation;
   }  Si21XXC_DTV_STATUS_CMD_REPLY_struct;

   /* DTV_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_DTV_STATUS_CMD_INTACK_LSB         0
   #define  Si21XXC_DTV_STATUS_CMD_INTACK_MASK        0x01
   #define  Si21XXC_DTV_STATUS_CMD_INTACK_MIN         0
   #define  Si21XXC_DTV_STATUS_CMD_INTACK_MAX         1
    #define Si21XXC_DTV_STATUS_CMD_INTACK_CLEAR  1
    #define Si21XXC_DTV_STATUS_CMD_INTACK_OK     0
   /* DTV_STATUS command, CHLINT field definition (address 1, size 1, lsb 0, unsigned)*/
   #define  Si21XXC_DTV_STATUS_RESPONSE_CHLINT_LSB         0
   #define  Si21XXC_DTV_STATUS_RESPONSE_CHLINT_MASK        0x01
    #define Si21XXC_DTV_STATUS_RESPONSE_CHLINT_CHANGED    1
    #define Si21XXC_DTV_STATUS_RESPONSE_CHLINT_NO_CHANGE  0
   /* DTV_STATUS command, CHL field definition (address 2, size 1, lsb 0, unsigned)*/
   #define  Si21XXC_DTV_STATUS_RESPONSE_CHL_LSB         0
   #define  Si21XXC_DTV_STATUS_RESPONSE_CHL_MASK        0x01
    #define Si21XXC_DTV_STATUS_RESPONSE_CHL_CHANNEL     1
    #define Si21XXC_DTV_STATUS_RESPONSE_CHL_NO_CHANNEL  0
   /* DTV_STATUS command, BW field definition (address 3, size 4, lsb 0, unsigned)*/
   #define  Si21XXC_DTV_STATUS_RESPONSE_BW_LSB         0
   #define  Si21XXC_DTV_STATUS_RESPONSE_BW_MASK        0x0f
    #define Si21XXC_DTV_STATUS_RESPONSE_BW_BW_1P7MHZ  9
    #define Si21XXC_DTV_STATUS_RESPONSE_BW_BW_6MHZ  6
    #define Si21XXC_DTV_STATUS_RESPONSE_BW_BW_6P1MHZ  10
    #define Si21XXC_DTV_STATUS_RESPONSE_BW_BW_7MHZ  7
    #define Si21XXC_DTV_STATUS_RESPONSE_BW_BW_8MHZ  8
   /* DTV_STATUS command, MODULATION field definition (address 3, size 4, lsb 4, unsigned)*/
   #define  Si21XXC_DTV_STATUS_RESPONSE_MODULATION_LSB         4
   #define  Si21XXC_DTV_STATUS_RESPONSE_MODULATION_MASK        0x0f
    #define Si21XXC_DTV_STATUS_RESPONSE_MODULATION_ATSC    0
    #define Si21XXC_DTV_STATUS_RESPONSE_MODULATION_DTMB    6
    #define Si21XXC_DTV_STATUS_RESPONSE_MODULATION_DVBC    3
    #define Si21XXC_DTV_STATUS_RESPONSE_MODULATION_DVBT    2
    #define Si21XXC_DTV_STATUS_RESPONSE_MODULATION_ISDBC   5
    #define Si21XXC_DTV_STATUS_RESPONSE_MODULATION_ISDBT   4
    #define Si21XXC_DTV_STATUS_RESPONSE_MODULATION_QAM_US  1

#endif /* Si21XXC_DTV_STATUS_CMD */

/* Si2178B_ENABLE_SSVD_ATV command definition */
#define   Si2178B_ENABLE_SSVD_ATV_CMD 0xbb

#ifdef    Si2178B_ENABLE_SSVD_ATV_CMD
  #define Si2178B_ENABLE_SSVD_ATV_CMD_CODE 0x0100bb

    typedef struct { /* Si2178_ENABLE_SSVD_ATV_CMD_struct */
         unsigned char   nothing;   } Si2178B_ENABLE_SSVD_ATV_CMD_struct;


    typedef struct { /* Si2178_ENABLE_SSVD_ATV_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2178B_ENABLE_SSVD_ATV_CMD_REPLY_struct;

#endif /* Si2178B_ENABLE_SSVD_ATV_CMD */

/* Si21XXC_EXIT_BOOTLOADER command definition */
#define   Si21XXC_EXIT_BOOTLOADER_CMD 0x01

#ifdef    Si21XXC_EXIT_BOOTLOADER_CMD
  #define Si21XXC_EXIT_BOOTLOADER_CMD_CODE 0x010001

    typedef struct { /* Si21XXC_EXIT_BOOTLOADER_CMD_struct */
     unsigned char   func;
     unsigned char   ctsien;
   } Si21XXC_EXIT_BOOTLOADER_CMD_struct;


    typedef struct { /* Si21XXC_EXIT_BOOTLOADER_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_EXIT_BOOTLOADER_CMD_REPLY_struct;

   /* EXIT_BOOTLOADER command, FUNC field definition (address 1,size 7, lsb 0, unsigned) */
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_LSB         0
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_MASK        0x7f
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_MIN         1
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_MAX         1
    #define Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_TUNER       1
   /* EXIT_BOOTLOADER command, CTSIEN field definition (address 1,size 1, lsb 7, unsigned) */
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_LSB         7
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_MASK        0x01
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_MIN         0
   #define  Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_MAX         1
    #define Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_OFF  0
    #define Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_ON   1
#endif /* Si21XXC_EXIT_BOOTLOADER_CMD */
/* Si2178B_FINE_TUNE command definition */
#define   Si2178B_FINE_TUNE_CMD 0x45

#ifdef    Si2178B_FINE_TUNE_CMD
  #define Si2178B_FINE_TUNE_CMD_CODE 0x010045

    typedef struct { /* Si2178B_FINE_TUNE_CMD_struct */
     unsigned char   persistence;
     unsigned char   apply_to_lif;
              int    offset_500hz;
   } Si2178B_FINE_TUNE_CMD_struct;


    typedef struct { /* Si2178B_FINE_TUNE_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2178B_FINE_TUNE_CMD_REPLY_struct;

   /* FINE_TUNE command, PERSISTENCE field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2178B_FINE_TUNE_CMD_PERSISTENCE_LSB         0
   #define  Si2178B_FINE_TUNE_CMD_PERSISTENCE_MASK        0x01
   #define  Si2178B_FINE_TUNE_CMD_PERSISTENCE_MIN         0
   #define  Si2178B_FINE_TUNE_CMD_PERSISTENCE_MAX         1
    #define Si2178B_FINE_TUNE_CMD_PERSISTENCE_NON_PERSISTENT  0
    #define Si2178B_FINE_TUNE_CMD_PERSISTENCE_PERSISTENT      1
   /* FINE_TUNE command, APPLY_TO_LIF field definition (address 1,size 1, lsb 1, unsigned) */
   #define  Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_LSB         1
   #define  Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_MASK        0x01
   #define  Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_MIN         0
   #define  Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_MAX         1
    #define Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_APPLY_TO_LIF         1
    #define Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_DO_NOT_APPLY_TO_LIF  0
   /* FINE_TUNE command, OFFSET_500HZ field definition (address 2,size 16, lsb 0, signed) */
   #define  Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_LSB         0
   #define  Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_MASK        0xffff
   #define  Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_SHIFT       16
   #define  Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_MIN         -4000
   #define  Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_MAX         4000
    #define Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_OFFSET_500HZ_MIN  -4000
    #define Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_OFFSET_500HZ_MAX  4000
#endif /* Si2178B_FINE_TUNE_CMD */


/* Si21XXC_FINE_TUNE command definition */
#define   Si21XXC_FINE_TUNE_CMD 0x45

#ifdef    Si21XXC_FINE_TUNE_CMD
  #define Si21XXC_FINE_TUNE_CMD_CODE 0x010045

    typedef struct { /* Si21XXC_FINE_TUNE_CMD_struct */
     unsigned char   persistence;
              int    offset_500hz;
   } Si21XXC_FINE_TUNE_CMD_struct;


    typedef struct { /* Si21XXC_FINE_TUNE_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_FINE_TUNE_CMD_REPLY_struct;

   /* FINE_TUNE command, PERSISTENCE field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_FINE_TUNE_CMD_PERSISTENCE_LSB         0
   #define  Si21XXC_FINE_TUNE_CMD_PERSISTENCE_MASK        0x01
   #define  Si21XXC_FINE_TUNE_CMD_PERSISTENCE_MIN         0
   #define  Si21XXC_FINE_TUNE_CMD_PERSISTENCE_MAX         1
    #define Si21XXC_FINE_TUNE_CMD_PERSISTENCE_NON_PERSISTENT  0
    #define Si21XXC_FINE_TUNE_CMD_PERSISTENCE_PERSISTENT      1
   /* FINE_TUNE command, OFFSET_500HZ field definition (address 2,size 16, lsb 0, signed) */
   #define  Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_LSB         0
   #define  Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_MASK        0xffff
   #define  Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_SHIFT       16
   #define  Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_MIN         -4000
   #define  Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_MAX         4000
    #define Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_OFFSET_500HZ_MIN  -4000
    #define Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_OFFSET_500HZ_MAX  4000
#endif /* Si21XXC_FINE_TUNE_CMD */

/* Si21XXC_GET_PROPERTY command definition */
#define   Si21XXC_GET_PROPERTY_CMD 0x15

#ifdef    Si21XXC_GET_PROPERTY_CMD
  #define Si21XXC_GET_PROPERTY_CMD_CODE 0x010015

    typedef struct { /* Si21XXC_GET_PROPERTY_CMD_struct */
     unsigned char   reserved;
     unsigned int    prop;
   } Si21XXC_GET_PROPERTY_CMD_struct;


    typedef struct { /* Si21XXC_GET_PROPERTY_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data;
   }  Si21XXC_GET_PROPERTY_CMD_REPLY_struct;

   /* GET_PROPERTY command, RESERVED field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si21XXC_GET_PROPERTY_CMD_RESERVED_LSB         0
   #define  Si21XXC_GET_PROPERTY_CMD_RESERVED_MASK        0xff
   #define  Si21XXC_GET_PROPERTY_CMD_RESERVED_MIN         0
   #define  Si21XXC_GET_PROPERTY_CMD_RESERVED_MAX         0
    #define Si21XXC_GET_PROPERTY_CMD_RESERVED_RESERVED_MIN  0
    #define Si21XXC_GET_PROPERTY_CMD_RESERVED_RESERVED_MAX  0
   /* GET_PROPERTY command, PROP field definition (address 2,size 16, lsb 0, unsigned) */
   #define  Si21XXC_GET_PROPERTY_CMD_PROP_LSB         0
   #define  Si21XXC_GET_PROPERTY_CMD_PROP_MASK        0xffff
   #define  Si21XXC_GET_PROPERTY_CMD_PROP_MIN         0
   #define  Si21XXC_GET_PROPERTY_CMD_PROP_MAX         65535
    #define Si21XXC_GET_PROPERTY_CMD_PROP_PROP_MIN  0
    #define Si21XXC_GET_PROPERTY_CMD_PROP_PROP_MAX  65535
   /* GET_PROPERTY command, RESERVED field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_PROPERTY_RESPONSE_RESERVED_LSB         0
   #define  Si21XXC_GET_PROPERTY_RESPONSE_RESERVED_MASK        0xff
   /* GET_PROPERTY command, DATA field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si21XXC_GET_PROPERTY_RESPONSE_DATA_LSB         0
   #define  Si21XXC_GET_PROPERTY_RESPONSE_DATA_MASK        0xffff

#endif /* Si21XXC_GET_PROPERTY_CMD */

/* Si21XXC_GET_REV command definition */
#define   Si21XXC_GET_REV_CMD 0x11

#ifdef    Si21XXC_GET_REV_CMD
  #define Si21XXC_GET_REV_CMD_CODE 0x010011

    typedef struct { /* Si21XXC_GET_REV_CMD_struct */
         unsigned char   nothing;   } Si21XXC_GET_REV_CMD_struct;


    typedef struct { /* Si21XXC_GET_REV_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   pn;
      unsigned char   pn2;
      unsigned char   fwmajor;
      unsigned char   fwminor;
      unsigned int    patch;
      unsigned char   cmpmajor;
      unsigned char   cmpminor;
      unsigned char   cmpbuild;
      unsigned char   chiprev;
   }  Si21XXC_GET_REV_CMD_REPLY_struct;

   /* GET_REV command, PN field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_PN_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_PN_MASK        0xff
   /* GET_REV command, PN2 field definition (address 12, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_PN2_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_PN2_MASK        0xff
   /* GET_REV command, FWMAJOR field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_FWMAJOR_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_FWMAJOR_MASK        0xff
   /* GET_REV command, FWMINOR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_FWMINOR_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_FWMINOR_MASK        0xff
   /* GET_REV command, PATCH field definition (address 4, size 16, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_PATCH_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_PATCH_MASK        0xffff
   /* GET_REV command, CMPMAJOR field definition (address 6, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_CMPMAJOR_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_CMPMAJOR_MASK        0xff
   /* GET_REV command, CMPMINOR field definition (address 7, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_CMPMINOR_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_CMPMINOR_MASK        0xff
   /* GET_REV command, CMPBUILD field definition (address 8, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_CMPBUILD_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_CMPBUILD_MASK        0xff
    #define Si21XXC_GET_REV_RESPONSE_CMPBUILD_CMPBUILD_MIN  0
    #define Si21XXC_GET_REV_RESPONSE_CMPBUILD_CMPBUILD_MAX  255
   /* GET_REV command, CHIPREV field definition (address 9, size 4, lsb 0, unsigned)*/
   #define  Si21XXC_GET_REV_RESPONSE_CHIPREV_LSB         0
   #define  Si21XXC_GET_REV_RESPONSE_CHIPREV_MASK        0x0f
    #define Si21XXC_GET_REV_RESPONSE_CHIPREV_A  1
    #define Si21XXC_GET_REV_RESPONSE_CHIPREV_B  2
    #define Si21XXC_GET_REV_RESPONSE_CHIPREV_C  3
#endif /* Si21XXC_GET_REV_CMD */
/* Si2191C_ISL_STATUS command definition */
#define   Si2191C_ISL_STATUS_CMD 0xbe

#ifdef    Si2191C_ISL_STATUS_CMD
  #define Si2191C_ISL_STATUS_CMD_CODE 0x0100be

    typedef struct { /* Si2191C_ISL_STATUS_CMD_struct */
     unsigned char   clear;
   } Si2191C_ISL_STATUS_CMD_struct;


    typedef struct { /* Si2191C_ISL_STATUS_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   tx;
      unsigned char   rx;
   }  Si2191C_ISL_STATUS_CMD_REPLY_struct;

   /* ISL_STATUS command, CLEAR field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2191C_ISL_STATUS_CMD_CLEAR_LSB         0
   #define  Si2191C_ISL_STATUS_CMD_CLEAR_MASK        0x01
   #define  Si2191C_ISL_STATUS_CMD_CLEAR_MIN         0
   #define  Si2191C_ISL_STATUS_CMD_CLEAR_MAX         1
    #define Si2191C_ISL_STATUS_CMD_CLEAR_CLEAR     1
    #define Si2191C_ISL_STATUS_CMD_CLEAR_NO_CLEAR  0
   /* ISL_STATUS command, TX field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2191C_ISL_STATUS_RESPONSE_TX_LSB         0
   #define  Si2191C_ISL_STATUS_RESPONSE_TX_MASK        0xff
    #define Si2191C_ISL_STATUS_RESPONSE_TX_TX_MIN  0
    #define Si2191C_ISL_STATUS_RESPONSE_TX_TX_MAX  255
   /* ISL_STATUS command, RX field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2191C_ISL_STATUS_RESPONSE_RX_LSB         0
   #define  Si2191C_ISL_STATUS_RESPONSE_RX_MASK        0xff
    #define Si2191C_ISL_STATUS_RESPONSE_RX_RX_MIN  0
    #define Si2191C_ISL_STATUS_RESPONSE_RX_RX_MAX  255

#endif /* Si2191C_ISL_STATUS_CMD */


/* Si21XXC_PART_INFO command definition */
#define   Si21XXC_PART_INFO_CMD 0x02

#ifdef    Si21XXC_PART_INFO_CMD
  #define Si21XXC_PART_INFO_CMD_CODE 0x010002

    typedef struct { /* Si21XXC_PART_INFO_CMD_struct */
         unsigned char   nothing;   } Si21XXC_PART_INFO_CMD_struct;


    typedef struct { /* Si21XXC_PART_INFO_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   chiprev;
      unsigned char   romid;
      unsigned char   part2;
      unsigned char   part;
      unsigned char   pmajor;
      unsigned char   pminor;
      unsigned char   pbuild;
      unsigned int    reserved;
      unsigned long   serial;
   }  Si21XXC_PART_INFO_CMD_REPLY_struct;

   /* PART_INFO command, CHIPREV field definition (address 1, size 4, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_CHIPREV_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_CHIPREV_MASK        0x0f
    #define Si21XXC_PART_INFO_RESPONSE_CHIPREV_A  1
    #define Si21XXC_PART_INFO_RESPONSE_CHIPREV_B  2
    #define Si21XXC_PART_INFO_RESPONSE_CHIPREV_C  3
   /* PART_INFO command, ROMID field definition (address 12, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_ROMID_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_ROMID_MASK        0xff
   /* PART_INFO command, PART2 field definition (address 13, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_PART2_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_PART2_MASK        0xff
   /* PART_INFO command, PART field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_PART_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_PART_MASK        0xff
   /* PART_INFO command, PMAJOR field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_PMAJOR_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_PMAJOR_MASK        0xff
   /* PART_INFO command, PMINOR field definition (address 4, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_PMINOR_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_PMINOR_MASK        0xff
   /* PART_INFO command, PBUILD field definition (address 5, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_PBUILD_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_PBUILD_MASK        0xff
   /* PART_INFO command, RESERVED field definition (address 6, size 16, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_RESERVED_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_RESERVED_MASK        0xffff
   /* PART_INFO command, SERIAL field definition (address 8, size 32, lsb 0, unsigned)*/
   #define  Si21XXC_PART_INFO_RESPONSE_SERIAL_LSB         0
   #define  Si21XXC_PART_INFO_RESPONSE_SERIAL_MASK        0xffffffff

#endif /* Si21XXC_PART_INFO_CMD */

/* Si2190B_PART_INFO2 command definition */
#define   Si2190B_PART_INFO2_CMD 0x0e

#ifdef    Si2190B_PART_INFO2_CMD
  #define Si2190B_PART_INFO2_CMD_CODE 0x01000e

    typedef struct { /* Si2190B_PART_INFO2_CMD_struct */
         unsigned char   nothing;   } Si2190B_PART_INFO2_CMD_struct;


    typedef struct { /* Si2190B_PART_INFO2_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   romid;
      unsigned char   part2;
      unsigned char   reserved;
      unsigned long   serial;
   }  Si2190B_PART_INFO2_CMD_REPLY_struct;

   /* PART_INFO2 command, ROMID field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2190B_PART_INFO2_RESPONSE_ROMID_LSB         0
   #define  Si2190B_PART_INFO2_RESPONSE_ROMID_MASK        0xff
   /* PART_INFO2 command, PART2 field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2190B_PART_INFO2_RESPONSE_PART2_LSB         0
   #define  Si2190B_PART_INFO2_RESPONSE_PART2_MASK        0xff
   /* PART_INFO2 command, RESERVED field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2190B_PART_INFO2_RESPONSE_RESERVED_LSB         0
   #define  Si2190B_PART_INFO2_RESPONSE_RESERVED_MASK        0xff
   /* PART_INFO2 command, SERIAL field definition (address 4, size 32, lsb 0, unsigned)*/
   #define  Si2190B_PART_INFO2_RESPONSE_SERIAL_LSB         0
   #define  Si2190B_PART_INFO2_RESPONSE_SERIAL_MASK        0xffffffff

#endif /* Si2190B_PART_INFO2_CMD */

/* Si21XXC_POWER_DOWN_HW command definition */
#define   Si21XXC_POWER_DOWN_HW_CMD 0xc0

#ifdef    Si21XXC_POWER_DOWN_HW_CMD
  #define Si21XXC_POWER_DOWN_HW_CMD_CODE 0x0300c0

    typedef struct { /* Si21XXC_POWER_DOWN_HW_CMD_struct */
     unsigned char   subcode;
     unsigned char   pd_xo_osc;
     unsigned char   reserved1;
     unsigned char   en_xout;
     unsigned char   reserved2;
     unsigned char   pd_ldo;
     unsigned char   reserved3;
     unsigned char   reserved4;
     unsigned char   reserved5;
     unsigned char   reserved6;
     unsigned char   reserved7;
     unsigned char   reserved8;
   } Si21XXC_POWER_DOWN_HW_CMD_struct;


    typedef struct { /* Si21XXC_POWER_DOWN_HW_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_POWER_DOWN_HW_CMD_REPLY_struct;

   /* POWER_DOWN_HW command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_MASK        0xff
   #define  Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_CODE  0
   /* POWER_DOWN_HW command, PD_XO_OSC field definition (address 2,size 1, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_MASK        0x01
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_MAX         1
    #define Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_XO_OSC_POWER_DOWN  1
    #define Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_XO_OSC_POWER_UP    0
   /* POWER_DOWN_HW command, RESERVED1 field definition (address 2,size 1, lsb 1, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_LSB         1
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_MASK        0x01
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_RESERVED  0
   /* POWER_DOWN_HW command, EN_XOUT field definition (address 2,size 3, lsb 2, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_LSB         2
   #define  Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_MASK        0x07
   #define  Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_MAX         3
    #define Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_DIS_XOUT  0
    #define Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_EN_XOUT   3
   /* POWER_DOWN_HW command, RESERVED2 field definition (address 2,size 3, lsb 5, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_LSB         5
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_MASK        0x07
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_MIN         1
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_MAX         1
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_RESERVED  1
   /* POWER_DOWN_HW command, PD_LDO field definition (address 3,size 1, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_MASK        0x01
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_MAX         1
    #define Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_LDO_POWER_DOWN  1
    #define Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_LDO_POWER_UP    0
   /* POWER_DOWN_HW command, RESERVED3 field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_MASK        0xff
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_RESERVED  0
   /* POWER_DOWN_HW command, RESERVED4 field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_MASK        0xff
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_RESERVED  0
   /* POWER_DOWN_HW command, RESERVED5 field definition (address 6,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_MASK        0xff
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_RESERVED  0
   /* POWER_DOWN_HW command, RESERVED6 field definition (address 7,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_MASK        0xff
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_RESERVED  0
   /* POWER_DOWN_HW command, RESERVED7 field definition (address 8,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_MASK        0xff
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_RESERVED  0
   /* POWER_DOWN_HW command, RESERVED8 field definition (address 9,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_LSB         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_MASK        0xff
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_MIN         0
   #define  Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_MAX         0
    #define Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_RESERVED  0
#endif /* Si21XXC_POWER_DOWN_HW_CMD */

/* Si21XXC_POWER_UP command definition */
#define   Si21XXC_POWER_UP_CMD 0xc0

#ifdef    Si21XXC_POWER_UP_CMD
  #define Si21XXC_POWER_UP_CMD_CODE 0x0400c0

    typedef struct { /* Si21XXC_POWER_UP_CMD_struct */
     unsigned char   subcode;
     unsigned char   clock_mode;
     unsigned char   en_xout;
     unsigned char   pd_ldo;
     unsigned char   reserved2;
     unsigned char   reserved3;
     unsigned char   reserved4;
     unsigned char   reserved5;
     unsigned char   reserved6;
     unsigned char   reserved7;
     unsigned char   reset;
     unsigned char   clock_freq;
     unsigned char   reserved8;
     unsigned char   func;
     unsigned char   ctsien;
     unsigned char   wake_up;
   } Si21XXC_POWER_UP_CMD_struct;


    typedef struct { /* Si21XXC_POWER_UP_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_POWER_UP_CMD_REPLY_struct;

   /* POWER_UP command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_SUBCODE_LSB         0
   #define  Si21XXC_POWER_UP_CMD_SUBCODE_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_SUBCODE_MIN         0
   #define  Si21XXC_POWER_UP_CMD_SUBCODE_MAX         0
    #define Si21XXC_POWER_UP_CMD_SUBCODE_CODE  0
   /* POWER_UP command, CLOCK_MODE field definition (address 2,size 2, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_CLOCK_MODE_LSB         0
   #define  Si21XXC_POWER_UP_CMD_CLOCK_MODE_MASK        0x03
   #define  Si21XXC_POWER_UP_CMD_CLOCK_MODE_MIN         0
   #define  Si21XXC_POWER_UP_CMD_CLOCK_MODE_MAX         2
    #define Si21XXC_POWER_UP_CMD_CLOCK_MODE_EXTCLK  2
    #define Si21XXC_POWER_UP_CMD_CLOCK_MODE_XTAL    0
   /* POWER_UP command, EN_XOUT field definition (address 2,size 3, lsb 2, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_EN_XOUT_LSB         2
   #define  Si21XXC_POWER_UP_CMD_EN_XOUT_MASK        0x07
   #define  Si21XXC_POWER_UP_CMD_EN_XOUT_MIN         0
   #define  Si21XXC_POWER_UP_CMD_EN_XOUT_MAX         3
    #define Si21XXC_POWER_UP_CMD_EN_XOUT_DIS_XOUT  0
    #define Si21XXC_POWER_UP_CMD_EN_XOUT_EN_XOUT   3
   /* POWER_UP command, PD_LDO field definition (address 3,size 1, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_PD_LDO_LSB         0
   #define  Si21XXC_POWER_UP_CMD_PD_LDO_MASK        0x01
   #define  Si21XXC_POWER_UP_CMD_PD_LDO_MIN         0
   #define  Si21XXC_POWER_UP_CMD_PD_LDO_MAX         1
    #define Si21XXC_POWER_UP_CMD_PD_LDO_LDO_POWER_DOWN  1
    #define Si21XXC_POWER_UP_CMD_PD_LDO_LDO_POWER_UP    0
   /* POWER_UP command, RESERVED2 field definition (address 4,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESERVED2_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED2_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESERVED2_MIN         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED2_MAX         0
    #define Si21XXC_POWER_UP_CMD_RESERVED2_RESERVED  0
   /* POWER_UP command, RESERVED3 field definition (address 5,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESERVED3_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED3_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESERVED3_MIN         1
   #define  Si21XXC_POWER_UP_CMD_RESERVED3_MAX         1
    #define Si21XXC_POWER_UP_CMD_RESERVED3_RESERVED  1
   /* POWER_UP command, RESERVED4 field definition (address 6,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESERVED4_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED4_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESERVED4_MIN         1
   #define  Si21XXC_POWER_UP_CMD_RESERVED4_MAX         1
    #define Si21XXC_POWER_UP_CMD_RESERVED4_RESERVED  1
   /* POWER_UP command, RESERVED5 field definition (address 7,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESERVED5_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED5_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESERVED5_MIN         1
   #define  Si21XXC_POWER_UP_CMD_RESERVED5_MAX         1
    #define Si21XXC_POWER_UP_CMD_RESERVED5_RESERVED  1
   /* POWER_UP command, RESERVED6 field definition (address 8,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESERVED6_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED6_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESERVED6_MIN         1
   #define  Si21XXC_POWER_UP_CMD_RESERVED6_MAX         1
    #define Si21XXC_POWER_UP_CMD_RESERVED6_RESERVED  1
   /* POWER_UP command, RESERVED7 field definition (address 9,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESERVED7_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED7_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESERVED7_MIN         1
   #define  Si21XXC_POWER_UP_CMD_RESERVED7_MAX         1
    #define Si21XXC_POWER_UP_CMD_RESERVED7_RESERVED  1
   /* POWER_UP command, RESET field definition (address 10,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESET_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESET_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESET_MIN         1
   #define  Si21XXC_POWER_UP_CMD_RESET_MAX         1
    #define Si21XXC_POWER_UP_CMD_RESET_RESET  1
   /* POWER_UP command, CLOCK_FREQ field definition (address 11,size 2, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_CLOCK_FREQ_LSB         0
   #define  Si21XXC_POWER_UP_CMD_CLOCK_FREQ_MASK        0x03
   #define  Si21XXC_POWER_UP_CMD_CLOCK_FREQ_MIN         2
   #define  Si21XXC_POWER_UP_CMD_CLOCK_FREQ_MAX         2
    #define Si21XXC_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ  2
   /* POWER_UP command, RESERVED8 field definition (address 12,size 8, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_RESERVED8_LSB         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED8_MASK        0xff
   #define  Si21XXC_POWER_UP_CMD_RESERVED8_MIN         0
   #define  Si21XXC_POWER_UP_CMD_RESERVED8_MAX         0
    #define Si21XXC_POWER_UP_CMD_RESERVED8_RESERVED  0
   /* POWER_UP command, FUNC field definition (address 13,size 7, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_FUNC_LSB         0
   #define  Si21XXC_POWER_UP_CMD_FUNC_MASK        0x7f
   #define  Si21XXC_POWER_UP_CMD_FUNC_MIN         0
   #define  Si21XXC_POWER_UP_CMD_FUNC_MAX         0
    #define Si21XXC_POWER_UP_CMD_FUNC_BOOTLOADER  0
   /* POWER_UP command, CTSIEN field definition (address 13,size 1, lsb 7, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_CTSIEN_LSB         7
   #define  Si21XXC_POWER_UP_CMD_CTSIEN_MASK        0x01
   #define  Si21XXC_POWER_UP_CMD_CTSIEN_MIN         0
   #define  Si21XXC_POWER_UP_CMD_CTSIEN_MAX         1
    #define Si21XXC_POWER_UP_CMD_CTSIEN_DISABLE  0
    #define Si21XXC_POWER_UP_CMD_CTSIEN_ENABLE   1
   /* POWER_UP command, WAKE_UP field definition (address 14,size 1, lsb 0, unsigned) */
   #define  Si21XXC_POWER_UP_CMD_WAKE_UP_LSB         0
   #define  Si21XXC_POWER_UP_CMD_WAKE_UP_MASK        0x01
   #define  Si21XXC_POWER_UP_CMD_WAKE_UP_MIN         1
   #define  Si21XXC_POWER_UP_CMD_WAKE_UP_MAX         1
    #define Si21XXC_POWER_UP_CMD_WAKE_UP_WAKE_UP  1
#endif /* Si21XXC_POWER_UP_CMD */

/* Si2190B_REREAD_REPLY command definition */
#define   Si2190B_REREAD_REPLY_CMD 0x17

#ifdef    Si2190B_REREAD_REPLY_CMD
  #define Si2190B_REREAD_REPLY_CMD_CODE 0x010017

    typedef struct { /* Si2190B_REREAD_REPLY_CMD_struct */
     unsigned char   offset;
   } Si2190B_REREAD_REPLY_CMD_struct;


    typedef struct { /* Si2190B_REREAD_REPLY_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   reply1;
      unsigned char   reply10;
      unsigned char   reply11;
      unsigned char   reply12;
      unsigned char   reply13;
      unsigned char   reply14;
      unsigned char   reply15;
      unsigned char   reply2;
      unsigned char   reply3;
      unsigned char   reply4;
      unsigned char   reply5;
      unsigned char   reply6;
      unsigned char   reply7;
      unsigned char   reply8;
      unsigned char   reply9;
   }  Si2190B_REREAD_REPLY_CMD_REPLY_struct;

   /* REREAD_REPLY command, OFFSET field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2190B_REREAD_REPLY_CMD_OFFSET_LSB         0
   #define  Si2190B_REREAD_REPLY_CMD_OFFSET_MASK        0xff
   #define  Si2190B_REREAD_REPLY_CMD_OFFSET_MIN         0
   #define  Si2190B_REREAD_REPLY_CMD_OFFSET_MAX       Si2190B  14
    #define Si2190B_REREAD_REPLY_CMD_OFFSET_OFFSET_MIN  0
    #define Si2190B_REREAD_REPLY_CMD_OFFSET_OFFSET_MAX  14
   /* REREAD_REPLY command, REPLY1 field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY1_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY1_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY1_REPLY1_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY1_REPLY1_MAX  255
   /* REREAD_REPLY command, REPLY10 field definition (address 10, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY10_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY10_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY10_REPLY10_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY10_REPLY10_MAX  255
   /* REREAD_REPLY command, REPLY11 field definition (address 11, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY11_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY11_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY11_REPLY11_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY11_REPLY11_MAX  255
   /* REREAD_REPLY command, REPLY12 field definition (address 12, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY12_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY12_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY12_REPLY12_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY12_REPLY12_MAX  255
   /* REREAD_REPLY command, REPLY13 field definition (address 13, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY13_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY13_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY13_REPLY13_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY13_REPLY13_MAX  255
   /* REREAD_REPLY command, REPLY14 field definition (address 14, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY14_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY14_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY14_REPLY14_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY14_REPLY14_MAX  255
   /* REREAD_REPLY command, REPLY15 field definition (address 15, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY15_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY15_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY15_REPLY15_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY15_REPLY15_MAX  255
   /* REREAD_REPLY command, REPLY2 field definition (address 2, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY2_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY2_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY2_REPLY2_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY2_REPLY2_MAX  255
   /* REREAD_REPLY command, REPLY3 field definition (address 3, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY3_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY3_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY3_REPLY3_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY3_REPLY3_MAX  255
   /* REREAD_REPLY command, REPLY4 field definition (address 4, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY4_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY4_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY4_REPLY4_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY4_REPLY4_MAX  255
   /* REREAD_REPLY command, REPLY5 field definition (address 5, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY5_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY5_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY5_REPLY5_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY5_REPLY5_MAX  255
   /* REREAD_REPLY command, REPLY6 field definition (address 6, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY6_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY6_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY6_REPLY6_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY6_REPLY6_MAX  255
   /* REREAD_REPLY command, REPLY7 field definition (address 7, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY7_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY7_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY7_REPLY7_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY7_REPLY7_MAX  255
   /* REREAD_REPLY command, REPLY8 field definition (address 8, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY8_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY8_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY8_REPLY8_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY8_REPLY8_MAX  255
   /* REREAD_REPLY command, REPLY9 field definition (address 9, size 8, lsb 0, unsigned)*/
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY9_LSB         0
   #define  Si2190B_REREAD_REPLY_RESPONSE_REPLY9_MASK        0xff
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY9_REPLY9_MIN  0
    #define Si2190B_REREAD_REPLY_RESPONSE_REPLY9_REPLY9_MAX  255

#endif /* Si2190B_REREAD_REPLY_CMD */

/* Si2190B_RESET_HW command definition */
#define   Si2190B_RESET_HW_CMD 0xc0

#ifdef    Si2190B_RESET_HW_CMD
  #define Si2190B_RESET_HW_CMD_CODE 0x0500c0

    typedef struct { /* Si2190B_RESET_HW_CMD_struct */
     unsigned char   subcode;
     unsigned char   reserved1;
     unsigned char   reserved2;
   } Si2190B_RESET_HW_CMD_struct;


    typedef struct { /* Si2190B_RESET_HW_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_RESET_HW_CMD_REPLY_struct;

   /* RESET_HW command, SUBCODE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2190B_RESET_HW_CMD_SUBCODE_LSB         0
   #define  Si2190B_RESET_HW_CMD_SUBCODE_MASK        0xff
   #define  Si2190B_RESET_HW_CMD_SUBCODE_MIN         5
   #define  Si2190B_RESET_HW_CMD_SUBCODE_MAX         5
    #define Si2190B_RESET_HW_CMD_SUBCODE_CODE  5
   /* RESET_HW command, RESERVED1 field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2190B_RESET_HW_CMD_RESERVED1_LSB         0
   #define  Si2190B_RESET_HW_CMD_RESERVED1_MASK        0xff
   #define  Si2190B_RESET_HW_CMD_RESERVED1_MIN         0
   #define  Si2190B_RESET_HW_CMD_RESERVED1_MAX         0
    #define Si2190B_RESET_HW_CMD_RESERVED1_RESERVED  0
   /* RESET_HW command, RESERVED2 field definition (address 3,size 8, lsb 0, unsigned) */
   #define  Si2190B_RESET_HW_CMD_RESERVED2_LSB         0
   #define  Si2190B_RESET_HW_CMD_RESERVED2_MASK        0xff
   #define  Si2190B_RESET_HW_CMD_RESERVED2_MIN         0
   #define  Si2190B_RESET_HW_CMD_RESERVED2_MAX         0
    #define Si2190B_RESET_HW_CMD_RESERVED2_RESERVED  0
#endif /* Si2190B_RESET_HW_CMD */

/* Si2190B_SELF_TEST command definition */
#define   Si2190B_SELF_TEST_CMD 0xbb

#ifdef    Si2190B_SELF_TEST_CMD
  #define Si2190B_SELF_TEST_CMD_CODE 0x0100bb

    typedef struct { /* Si2190B_SELF_TEST_CMD_struct */
         unsigned char   nothing;   } Si2190B_SELF_TEST_CMD_struct;


    typedef struct { /* Si2190B_SELF_TEST_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   adc_ref;
      unsigned char   mix_cmb0;
      unsigned char   mix_cmb1;
      unsigned char   mix_cmb2;
      unsigned char   divr_vreg;
      unsigned char   pdcplf_vreg;
      unsigned char   pdcplf_bias;
      unsigned char   vco_vreg1;
      unsigned char   vco_vreg2;
      unsigned char   fbdiv_ireg;
      unsigned char   fbdiv_vreg;
      unsigned char   pdcplf_rccal;
      unsigned char   dac1_vtr;
      unsigned char   dac1_vcom;
      unsigned char   dac2_vtr;
      unsigned char   dac2_vcom;
      unsigned char   if_bias;
      unsigned char   lna_vmid;
      unsigned char   lna_vreg;
      unsigned char   lna_vtr;
      unsigned char   lodiv_core_vreg;
      unsigned char   lodiv_buf_reg;
      unsigned char   rccal_filt;
      unsigned char   rccal_adc;
   }  Si2190B_SELF_TEST_CMD_REPLY_struct;

   /* SELF_TEST command, ADC_REF field definition (address 1, size 1, lsb 0, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_ADC_REF_LSB         0
   #define  Si2190B_SELF_TEST_RESPONSE_ADC_REF_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_ADC_REF_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_ADC_REF_PASS  1
   /* SELF_TEST command, MIX_CMB0 field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_MIX_CMB0_LSB         1
   #define  Si2190B_SELF_TEST_RESPONSE_MIX_CMB0_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_MIX_CMB0_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_MIX_CMB0_PASS  1
   /* SELF_TEST command, MIX_CMB1 field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_MIX_CMB1_LSB         2
   #define  Si2190B_SELF_TEST_RESPONSE_MIX_CMB1_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_MIX_CMB1_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_MIX_CMB1_PASS  1
   /* SELF_TEST command, MIX_CMB2 field definition (address 1, size 1, lsb 3, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_MIX_CMB2_LSB         3
   #define  Si2190B_SELF_TEST_RESPONSE_MIX_CMB2_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_MIX_CMB2_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_MIX_CMB2_PASS  1
   /* SELF_TEST command, DIVR_VREG field definition (address 1, size 1, lsb 4, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_DIVR_VREG_LSB         4
   #define  Si2190B_SELF_TEST_RESPONSE_DIVR_VREG_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_DIVR_VREG_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_DIVR_VREG_PASS  1
   /* SELF_TEST command, PDCPLF_VREG field definition (address 1, size 1, lsb 5, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_PDCPLF_VREG_LSB         5
   #define  Si2190B_SELF_TEST_RESPONSE_PDCPLF_VREG_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_PDCPLF_VREG_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_PDCPLF_VREG_PASS  1
   /* SELF_TEST command, PDCPLF_BIAS field definition (address 1, size 1, lsb 6, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_PDCPLF_BIAS_LSB         6
   #define  Si2190B_SELF_TEST_RESPONSE_PDCPLF_BIAS_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_PDCPLF_BIAS_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_PDCPLF_BIAS_PASS  1
   /* SELF_TEST command, VCO_VREG1 field definition (address 1, size 1, lsb 7, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_VCO_VREG1_LSB         7
   #define  Si2190B_SELF_TEST_RESPONSE_VCO_VREG1_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_VCO_VREG1_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_VCO_VREG1_PASS  1
   /* SELF_TEST command, VCO_VREG2 field definition (address 2, size 1, lsb 0, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_VCO_VREG2_LSB         0
   #define  Si2190B_SELF_TEST_RESPONSE_VCO_VREG2_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_VCO_VREG2_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_VCO_VREG2_PASS  1
   /* SELF_TEST command, FBDIV_IREG field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_FBDIV_IREG_LSB         1
   #define  Si2190B_SELF_TEST_RESPONSE_FBDIV_IREG_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_FBDIV_IREG_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_FBDIV_IREG_PASS  1
   /* SELF_TEST command, FBDIV_VREG field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_FBDIV_VREG_LSB         2
   #define  Si2190B_SELF_TEST_RESPONSE_FBDIV_VREG_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_FBDIV_VREG_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_FBDIV_VREG_PASS  1
   /* SELF_TEST command, PDCPLF_RCCAL field definition (address 2, size 1, lsb 3, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_PDCPLF_RCCAL_LSB         3
   #define  Si2190B_SELF_TEST_RESPONSE_PDCPLF_RCCAL_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_PDCPLF_RCCAL_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_PDCPLF_RCCAL_PASS  1
   /* SELF_TEST command, DAC1_VTR field definition (address 2, size 1, lsb 4, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_DAC1_VTR_LSB         4
   #define  Si2190B_SELF_TEST_RESPONSE_DAC1_VTR_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_DAC1_VTR_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_DAC1_VTR_PASS  1
   /* SELF_TEST command, DAC1_VCOM field definition (address 2, size 1, lsb 5, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_DAC1_VCOM_LSB         5
   #define  Si2190B_SELF_TEST_RESPONSE_DAC1_VCOM_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_DAC1_VCOM_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_DAC1_VCOM_PASS  1
   /* SELF_TEST command, DAC2_VTR field definition (address 2, size 1, lsb 6, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_DAC2_VTR_LSB         6
   #define  Si2190B_SELF_TEST_RESPONSE_DAC2_VTR_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_DAC2_VTR_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_DAC2_VTR_PASS  1
   /* SELF_TEST command, DAC2_VCOM field definition (address 2, size 1, lsb 7, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_DAC2_VCOM_LSB         7
   #define  Si2190B_SELF_TEST_RESPONSE_DAC2_VCOM_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_DAC2_VCOM_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_DAC2_VCOM_PASS  1
   /* SELF_TEST command, IF_BIAS field definition (address 3, size 1, lsb 0, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_IF_BIAS_LSB         0
   #define  Si2190B_SELF_TEST_RESPONSE_IF_BIAS_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_IF_BIAS_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_IF_BIAS_PASS  1
   /* SELF_TEST command, LNA_VMID field definition (address 3, size 1, lsb 1, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_LNA_VMID_LSB         1
   #define  Si2190B_SELF_TEST_RESPONSE_LNA_VMID_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_LNA_VMID_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_LNA_VMID_PASS  1
   /* SELF_TEST command, LNA_VREG field definition (address 3, size 1, lsb 2, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_LNA_VREG_LSB         2
   #define  Si2190B_SELF_TEST_RESPONSE_LNA_VREG_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_LNA_VREG_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_LNA_VREG_PASS  1
   /* SELF_TEST command, LNA_VTR field definition (address 3, size 1, lsb 3, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_LNA_VTR_LSB         3
   #define  Si2190B_SELF_TEST_RESPONSE_LNA_VTR_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_LNA_VTR_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_LNA_VTR_PASS  1
   /* SELF_TEST command, LODIV_CORE_VREG field definition (address 3, size 1, lsb 4, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_LODIV_CORE_VREG_LSB         4
   #define  Si2190B_SELF_TEST_RESPONSE_LODIV_CORE_VREG_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_LODIV_CORE_VREG_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_LODIV_CORE_VREG_PASS  1
   /* SELF_TEST command, LODIV_BUF_REG field definition (address 3, size 1, lsb 5, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_LODIV_BUF_REG_LSB         5
   #define  Si2190B_SELF_TEST_RESPONSE_LODIV_BUF_REG_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_LODIV_BUF_REG_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_LODIV_BUF_REG_PASS  1
   /* SELF_TEST command, RCCAL_FILT field definition (address 3, size 1, lsb 6, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_RCCAL_FILT_LSB         6
   #define  Si2190B_SELF_TEST_RESPONSE_RCCAL_FILT_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_RCCAL_FILT_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_RCCAL_FILT_PASS  1
   /* SELF_TEST command, RCCAL_ADC field definition (address 3, size 1, lsb 7, unsigned)*/
   #define  Si2190B_SELF_TEST_RESPONSE_RCCAL_ADC_LSB         7
   #define  Si2190B_SELF_TEST_RESPONSE_RCCAL_ADC_MASK        0x01
    #define Si2190B_SELF_TEST_RESPONSE_RCCAL_ADC_FAIL  0
    #define Si2190B_SELF_TEST_RESPONSE_RCCAL_ADC_PASS  1

#endif /* Si2190B_SELF_TEST_CMD */

/* Si21XXC_SET_PROPERTY command definition */
#define   Si21XXC_SET_PROPERTY_CMD 0x14

#ifdef    Si21XXC_SET_PROPERTY_CMD
  #define Si21XXC_SET_PROPERTY_CMD_CODE 0x010014

    typedef struct { /* Si21XXC_SET_PROPERTY_CMD_struct */
     unsigned char   reserved;
     unsigned int    prop;
     unsigned int    data;
   } Si21XXC_SET_PROPERTY_CMD_struct;


    typedef struct { /* Si21XXC_SET_PROPERTY_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data;
   }  Si21XXC_SET_PROPERTY_CMD_REPLY_struct;

   /* SET_PROPERTY command, RESERVED field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si21XXC_SET_PROPERTY_CMD_RESERVED_LSB         0
   #define  Si21XXC_SET_PROPERTY_CMD_RESERVED_MASK        0xff
   #define  Si21XXC_SET_PROPERTY_CMD_RESERVED_MIN         0
   #define  Si21XXC_SET_PROPERTY_CMD_RESERVED_MAX         255.0
   /* SET_PROPERTY command, PROP field definition (address 2,size 16, lsb 0, unsigned) */
   #define  Si21XXC_SET_PROPERTY_CMD_PROP_LSB         0
   #define  Si21XXC_SET_PROPERTY_CMD_PROP_MASK        0xffff
   #define  Si21XXC_SET_PROPERTY_CMD_PROP_MIN         0
   #define  Si21XXC_SET_PROPERTY_CMD_PROP_MAX         65535
    #define Si21XXC_SET_PROPERTY_CMD_PROP_PROP_MIN  0
    #define Si21XXC_SET_PROPERTY_CMD_PROP_PROP_MAX  65535
   /* SET_PROPERTY command, DATA field definition (address 4,size 16, lsb 0, unsigned) */
   #define  Si21XXC_SET_PROPERTY_CMD_DATA_LSB         0
   #define  Si21XXC_SET_PROPERTY_CMD_DATA_MASK        0xffff
   #define  Si21XXC_SET_PROPERTY_CMD_DATA_MIN         0
   #define  Si21XXC_SET_PROPERTY_CMD_DATA_MAX         65535
    #define Si21XXC_SET_PROPERTY_CMD_DATA_DATA_MIN  0
    #define Si21XXC_SET_PROPERTY_CMD_DATA_DATA_MAX  65535
   /* SET_PROPERTY command, RESERVED field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_SET_PROPERTY_RESPONSE_RESERVED_LSB         0
   #define  Si21XXC_SET_PROPERTY_RESPONSE_RESERVED_MASK        0xff
    #define Si21XXC_SET_PROPERTY_RESPONSE_RESERVED_RESERVED_MIN  0
    #define Si21XXC_SET_PROPERTY_RESPONSE_RESERVED_RESERVED_MAX  0
   /* SET_PROPERTY command, DATA field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si21XXC_SET_PROPERTY_RESPONSE_DATA_LSB         0
   #define  Si21XXC_SET_PROPERTY_RESPONSE_DATA_MASK        0xffff

#endif /* Si21XXC_SET_PROPERTY_CMD */

/* Si2190B_SSVD_DEBUG_CONFIG command definition */
#define   Si2190B_SSVD_DEBUG_CONFIG_CMD 0x88

#ifdef    Si2190B_SSVD_DEBUG_CONFIG_CMD
  #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CODE 0x010088

    typedef struct { /* Si2190B_SSVD_DEBUG_CONFIG_CMD_struct */
     unsigned char   cvbs_out;
     unsigned char   sif_out;
   } Si2190B_SSVD_DEBUG_CONFIG_CMD_struct;


    typedef struct { /* Si2190B_SSVD_DEBUG_CONFIG_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_SSVD_DEBUG_CONFIG_CMD_REPLY_struct;

   /* SSVD_DEBUG_CONFIG command, CVBS_OUT field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_LSB         0
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_MASK        0xff
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_MIN         0
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_MAX         15
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_CVBS     15
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_0   0
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_1   1
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_10  10
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_11  11
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_12  12
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_13  13
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_14  14
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_2   2
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_3   3
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_4   4
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_5   5
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_6   6
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_7   7
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_8   8
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_TEST_9   9
   /* SSVD_DEBUG_CONFIG command, SIF_OUT field definition (address 2,size 8, lsb 0, unsigned) */
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_LSB         0
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_MASK        0xff
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_MIN         0
   #define  Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_MAX         15
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_SIF      15
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_0   0
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_1   1
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_10  10
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_11  11
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_12  12
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_13  13
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_14  14
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_2   2
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_3   3
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_4   4
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_5   5
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_6   6
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_7   7
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_8   8
    #define Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_TEST_9   9
#endif /* Si2190B_SSVD_DEBUG_CONFIG_CMD */

/* Si2190B_SSVD_HDIV command definition */
#define   Si2190B_SSVD_HDIV_CMD 0x87

#ifdef    Si2190B_SSVD_HDIV_CMD
  #define Si2190B_SSVD_HDIV_CMD_CODE 0x010087

    typedef struct { /* Si2190B_SSVD_HDIV_CMD_struct */
     unsigned char   enable;
     unsigned int    st_ctrl0;
     unsigned int    ha_ctrl0;
   } Si2190B_SSVD_HDIV_CMD_struct;


    typedef struct { /* Si2190B_SSVD_HDIV_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_SSVD_HDIV_CMD_REPLY_struct;

   /* SSVD_HDIV command, ENABLE field definition (address 1,size 8, lsb 0, unsigned) */
   #define  Si2190B_SSVD_HDIV_CMD_ENABLE_LSB         0
   #define  Si2190B_SSVD_HDIV_CMD_ENABLE_MASK        0xff
   #define  Si2190B_SSVD_HDIV_CMD_ENABLE_MIN         0
   #define  Si2190B_SSVD_HDIV_CMD_ENABLE_MAX         1
    #define Si2190B_SSVD_HDIV_CMD_ENABLE_DISABLE  0
    #define Si2190B_SSVD_HDIV_CMD_ENABLE_ENABLE   1
   /* SSVD_HDIV command, ST_CTRL0 field definition (address 2,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_HDIV_CMD_ST_CTRL0_LSB         0
   #define  Si2190B_SSVD_HDIV_CMD_ST_CTRL0_MASK        0xffff
   #define  Si2190B_SSVD_HDIV_CMD_ST_CTRL0_MIN         0
   #define  Si2190B_SSVD_HDIV_CMD_ST_CTRL0_MAX         65535
    #define Si2190B_SSVD_HDIV_CMD_ST_CTRL0_ST_CTRL0_MIN  0
    #define Si2190B_SSVD_HDIV_CMD_ST_CTRL0_ST_CTRL0_MAX  65535
   /* SSVD_HDIV command, HA_CTRL0 field definition (address 4,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_HDIV_CMD_HA_CTRL0_LSB         0
   #define  Si2190B_SSVD_HDIV_CMD_HA_CTRL0_MASK        0xffff
   #define  Si2190B_SSVD_HDIV_CMD_HA_CTRL0_MIN         0
   #define  Si2190B_SSVD_HDIV_CMD_HA_CTRL0_MAX         65535
    #define Si2190B_SSVD_HDIV_CMD_HA_CTRL0_HA_CTRL0_MIN  0
    #define Si2190B_SSVD_HDIV_CMD_HA_CTRL0_HA_CTRL0_MAX  65535
#endif /* Si2190B_SSVD_HDIV_CMD */

/* Si2190B_SSVD_MULTI_REG_RD command definition */
#define   Si2190B_SSVD_MULTI_REG_RD_CMD 0x83

#ifdef    Si2190B_SSVD_MULTI_REG_RD_CMD
  #define Si2190B_SSVD_MULTI_REG_RD_CMD_CODE 0x010083

    typedef struct { /* Si2190B_SSVD_MULTI_REG_RD_CMD_struct */
     unsigned char   reg_sel;
     unsigned char   num_regs;
   } Si2190B_SSVD_MULTI_REG_RD_CMD_struct;


    typedef struct { /* Si2190B_SSVD_MULTI_REG_RD_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data4;
      unsigned int    data5;
      unsigned int    data6;
      unsigned int    data0;
      unsigned int    data1;
      unsigned int    data2;
      unsigned int    data3;
   }  Si2190B_SSVD_MULTI_REG_RD_CMD_REPLY_struct;

   /* SSVD_MULTI_REG_RD command, REG_SEL field definition (address 1,size 5, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_MASK        0x1f
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_MAX         19
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL0    0
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL1    1
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL2    2
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL3    3
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL4    4
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL5    5
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL6    6
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL7    7
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL8    8
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_CTRL9    9
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS0  10
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS1  11
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS2  12
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS3  13
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS4  14
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS5  15
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS6  16
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS7  17
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS8  18
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_SSVD_STATUS9  19
   /* SSVD_MULTI_REG_RD command, NUM_REGS field definition (address 1,size 3, lsb 5, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_LSB         5
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_MASK        0x07
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_MAX         7
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_NUM_REGS_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_NUM_REGS_MAX  7
   /* SSVD_MULTI_REG_RD command, RESERVED field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_RESERVED_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_RESERVED_MASK        0xff
   /* SSVD_MULTI_REG_RD command, DATA4 field definition (address 10, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA4_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA4_MASK        0xffff
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA4_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA4_DATA_MAX  65535
   /* SSVD_MULTI_REG_RD command, DATA5 field definition (address 12, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA5_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA5_MASK        0xffff
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA5_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA5_DATA_MAX  65535
   /* SSVD_MULTI_REG_RD command, DATA6 field definition (address 14, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA6_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA6_MASK        0xffff
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA6_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA6_DATA_MAX  65535
   /* SSVD_MULTI_REG_RD command, DATA0 field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA0_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA0_MASK        0xffff
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA0_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA0_DATA_MAX  65535
   /* SSVD_MULTI_REG_RD command, DATA1 field definition (address 4, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA1_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA1_MASK        0xffff
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA1_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA1_DATA_MAX  65535
   /* SSVD_MULTI_REG_RD command, DATA2 field definition (address 6, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA2_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA2_MASK        0xffff
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA2_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA2_DATA_MAX  65535
   /* SSVD_MULTI_REG_RD command, DATA3 field definition (address 8, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA3_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA3_MASK        0xffff
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA3_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA3_DATA_MAX  65535

#endif /* Si2190B_SSVD_MULTI_REG_RD_CMD */

/* Si2190B_SSVD_MULTI_REG_WR command definition */
#define   Si2190B_SSVD_MULTI_REG_WR_CMD 0x84

#ifdef    Si2190B_SSVD_MULTI_REG_WR_CMD
  #define Si2190B_SSVD_MULTI_REG_WR_CMD_CODE 0x010084

    typedef struct { /* Si2190B_SSVD_MULTI_REG_WR_CMD_struct */
     unsigned char   reg_sel;
     unsigned char   update;
     unsigned char   num_regs;
     unsigned int    data0;
     unsigned int    data1;
     unsigned int    data2;
     unsigned int    data3;
     unsigned int    data4;
     unsigned int    data5;
     unsigned int    data6;
   } Si2190B_SSVD_MULTI_REG_WR_CMD_struct;


    typedef struct { /* Si2190B_SSVD_MULTI_REG_WR_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_SSVD_MULTI_REG_WR_CMD_REPLY_struct;

   /* SSVD_MULTI_REG_WR command, REG_SEL field definition (address 1,size 4, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_MASK        0x0f
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_MAX         9
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL0  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL1  1
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL2  2
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL3  3
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL4  4
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL5  5
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL6  6
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL7  7
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL8  8
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_SSVD_CTRL9  9
   /* SSVD_MULTI_REG_WR command, UPDATE field definition (address 1,size 1, lsb 4, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_LSB         4
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_MASK        0x01
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_MAX         1
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_NO_UPDATE  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_UPDATE     1
   /* SSVD_MULTI_REG_WR command, NUM_REGS field definition (address 1,size 3, lsb 5, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_LSB         5
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_MASK        0x07
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_MAX         7
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_NUM_REGS_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_NUM_REGS_MAX  7
   /* SSVD_MULTI_REG_WR command, DATA0 field definition (address 2,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_MASK        0xffff
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_MAX         65535
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_DATA_MAX  65535
   /* SSVD_MULTI_REG_WR command, DATA1 field definition (address 4,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_MASK        0xffff
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_MAX         65535
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_DATA_MAX  65535
   /* SSVD_MULTI_REG_WR command, DATA2 field definition (address 6,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_MASK        0xffff
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_MAX         65535
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_DATA_MAX  65535
   /* SSVD_MULTI_REG_WR command, DATA3 field definition (address 8,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_MASK        0xffff
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_MAX         65535
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_DATA_MAX  65535
   /* SSVD_MULTI_REG_WR command, DATA4 field definition (address 10,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_MASK        0xffff
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_MAX         65535
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_DATA_MAX  65535
   /* SSVD_MULTI_REG_WR command, DATA5 field definition (address 12,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_MASK        0xffff
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_MAX         65535
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_DATA_MAX  65535
   /* SSVD_MULTI_REG_WR command, DATA6 field definition (address 14,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_LSB         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_MASK        0xffff
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_MIN         0
   #define  Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_MAX         65535
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_DATA_MIN  0
    #define Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_DATA_MAX  65535
#endif /* Si2190B_SSVD_MULTI_REG_WR_CMD */

/* Si2190B_SSVD_POWER_DOWN command definition */
#define   Si2190B_SSVD_POWER_DOWN_CMD 0x82

#ifdef    Si2190B_SSVD_POWER_DOWN_CMD
  #define Si2190B_SSVD_POWER_DOWN_CMD_CODE 0x010082

    typedef struct { /* Si2190B_SSVD_POWER_DOWN_CMD_struct */
         unsigned char   nothing;   } Si2190B_SSVD_POWER_DOWN_CMD_struct;


    typedef struct { /* Si2190B_SSVD_POWER_DOWN_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_SSVD_POWER_DOWN_CMD_REPLY_struct;

#endif /* Si2190B_SSVD_POWER_DOWN_CMD */

/* Si2190B_SSVD_POWER_UP command definition */
#define   Si2190B_SSVD_POWER_UP_CMD 0x81

#ifdef    Si2190B_SSVD_POWER_UP_CMD
  #define Si2190B_SSVD_POWER_UP_CMD_CODE 0x010081

    typedef struct { /* Si2190B_SSVD_POWER_UP_CMD_struct */
         unsigned char   nothing;   } Si2190B_SSVD_POWER_UP_CMD_struct;


    typedef struct { /* Si2190B_SSVD_POWER_UP_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_SSVD_POWER_UP_CMD_REPLY_struct;

#endif /* Si2190B_SSVD_POWER_UP_CMD */

/* Si2190B_SSVD_REG_RD command definition */
#define   Si2190B_SSVD_REG_RD_CMD 0x85

#ifdef    Si2190B_SSVD_REG_RD_CMD
  #define Si2190B_SSVD_REG_RD_CMD_CODE 0x010085

    typedef struct { /* Si2190B_SSVD_REG_RD_CMD_struct */
     unsigned char   reg_sel;
     unsigned char   ignored;
   } Si2190B_SSVD_REG_RD_CMD_struct;


    typedef struct { /* Si2190B_SSVD_REG_RD_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data;
   }  Si2190B_SSVD_REG_RD_CMD_REPLY_struct;

   /* SSVD_REG_RD command, REG_SEL field definition (address 1,size 5, lsb 0, unsigned) */
   #define  Si2190B_SSVD_REG_RD_CMD_REG_SEL_LSB         0
   #define  Si2190B_SSVD_REG_RD_CMD_REG_SEL_MASK        0x1f
   #define  Si2190B_SSVD_REG_RD_CMD_REG_SEL_MIN         0
   #define  Si2190B_SSVD_REG_RD_CMD_REG_SEL_MAX         19
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL0    0
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL1    1
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL2    2
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL3    3
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL4    4
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL5    5
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL6    6
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL7    7
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL8    8
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_CTRL9    9
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS0  10
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS1  11
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS2  12
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS3  13
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS4  14
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS5  15
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS6  16
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS7  17
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS8  18
    #define Si2190B_SSVD_REG_RD_CMD_REG_SEL_SSVD_STATUS9  19
   /* SSVD_REG_RD command, IGNORED field definition (address 1,size 3, lsb 5, unsigned) */
   #define  Si2190B_SSVD_REG_RD_CMD_IGNORED_LSB         5
   #define  Si2190B_SSVD_REG_RD_CMD_IGNORED_MASK        0x07
   #define  Si2190B_SSVD_REG_RD_CMD_IGNORED_MIN         0
   #define  Si2190B_SSVD_REG_RD_CMD_IGNORED_MAX         7.0
   /* SSVD_REG_RD command, RESERVED field definition (address 1, size 8, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_REG_RD_RESPONSE_RESERVED_LSB         0
   #define  Si2190B_SSVD_REG_RD_RESPONSE_RESERVED_MASK        0xff
   /* SSVD_REG_RD command, DATA field definition (address 2, size 16, lsb 0, unsigned)*/
   #define  Si2190B_SSVD_REG_RD_RESPONSE_DATA_LSB         0
   #define  Si2190B_SSVD_REG_RD_RESPONSE_DATA_MASK        0xffff
    #define Si2190B_SSVD_REG_RD_RESPONSE_DATA_DATA_MIN  0
    #define Si2190B_SSVD_REG_RD_RESPONSE_DATA_DATA_MAX  65535

#endif /* Si2190B_SSVD_REG_RD_CMD */

/* Si2190B_SSVD_REG_WR command definition */
#define   Si2190B_SSVD_REG_WR_CMD 0x86

#ifdef    Si2190B_SSVD_REG_WR_CMD
  #define Si2190B_SSVD_REG_WR_CMD_CODE 0x010086

    typedef struct { /* Si2190B_SSVD_REG_WR_CMD_struct */
     unsigned char   reg_sel;
     unsigned char   update;
     unsigned char   ignored;
     unsigned int    data;
   } Si2190B_SSVD_REG_WR_CMD_struct;


    typedef struct { /* Si2190B_SSVD_REG_WR_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_SSVD_REG_WR_CMD_REPLY_struct;

   /* SSVD_REG_WR command, REG_SEL field definition (address 1,size 4, lsb 0, unsigned) */
   #define  Si2190B_SSVD_REG_WR_CMD_REG_SEL_LSB         0
   #define  Si2190B_SSVD_REG_WR_CMD_REG_SEL_MASK        0x0f
   #define  Si2190B_SSVD_REG_WR_CMD_REG_SEL_MIN         0
   #define  Si2190B_SSVD_REG_WR_CMD_REG_SEL_MAX         9
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL0  0
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL1  1
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL2  2
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL3  3
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL4  4
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL5  5
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL6  6
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL7  7
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL8  8
    #define Si2190B_SSVD_REG_WR_CMD_REG_SEL_SSVD_CTRL9  9
   /* SSVD_REG_WR command, UPDATE field definition (address 1,size 1, lsb 4, unsigned) */
   #define  Si2190B_SSVD_REG_WR_CMD_UPDATE_LSB         4
   #define  Si2190B_SSVD_REG_WR_CMD_UPDATE_MASK        0x01
   #define  Si2190B_SSVD_REG_WR_CMD_UPDATE_MIN         0
   #define  Si2190B_SSVD_REG_WR_CMD_UPDATE_MAX         1
    #define Si2190B_SSVD_REG_WR_CMD_UPDATE_NO_UPDATE  0
    #define Si2190B_SSVD_REG_WR_CMD_UPDATE_UPDATE     1
   /* SSVD_REG_WR command, IGNORED field definition (address 1,size 3, lsb 5, unsigned) */
   #define  Si2190B_SSVD_REG_WR_CMD_IGNORED_LSB         5
   #define  Si2190B_SSVD_REG_WR_CMD_IGNORED_MASK        0x07
   #define  Si2190B_SSVD_REG_WR_CMD_IGNORED_MIN         0
   #define  Si2190B_SSVD_REG_WR_CMD_IGNORED_MAX         7.0
   /* SSVD_REG_WR command, DATA field definition (address 2,size 16, lsb 0, unsigned) */
   #define  Si2190B_SSVD_REG_WR_CMD_DATA_LSB         0
   #define  Si2190B_SSVD_REG_WR_CMD_DATA_MASK        0xffff
   #define  Si2190B_SSVD_REG_WR_CMD_DATA_MIN         0
   #define  Si2190B_SSVD_REG_WR_CMD_DATA_MAX         65535
    #define Si2190B_SSVD_REG_WR_CMD_DATA_DATA_MIN  0
    #define Si2190B_SSVD_REG_WR_CMD_DATA_DATA_MAX  65535
#endif /* Si2190B_SSVD_REG_WR_CMD */

/* Si21XXC_STANDBY command definition */
#define   Si21XXC_STANDBY_CMD 0x16

#ifdef    Si21XXC_STANDBY_CMD
  #define Si21XXC_STANDBY_CMD_CODE 0x010016

    typedef struct { /* Si21XXC_STANDBY_CMD_struct */
     unsigned char   type;
   } Si21XXC_STANDBY_CMD_struct;


    typedef struct { /* Si21XXC_STANDBY_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_STANDBY_CMD_REPLY_struct;

   /* STANDBY command, TYPE field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_STANDBY_CMD_TYPE_LSB         0
   #define  Si21XXC_STANDBY_CMD_TYPE_MASK        0x01
   #define  Si21XXC_STANDBY_CMD_TYPE_MIN         0
   #define  Si21XXC_STANDBY_CMD_TYPE_MAX         1
    #define Si21XXC_STANDBY_CMD_TYPE_LNA_OFF  1
    #define Si21XXC_STANDBY_CMD_TYPE_LNA_ON   0
#endif /* Si21XXC_STANDBY_CMD */
/* Si2190B_TUNER_CANCEL_TONE_STATUS command definition */
#define   Si2190B_TUNER_CANCEL_TONE_STATUS_CMD 0x4b

#ifdef    Si2190B_TUNER_CANCEL_TONE_STATUS_CMD
  #define Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_CODE 0x01004b

    typedef struct { /* Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_struct */
     unsigned char   tc_num;
   } Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_struct;


    typedef struct { /* Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   active;
      unsigned char   status;
      unsigned char   type;
               int    freq_khz;
   }  Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_REPLY_struct;

   /* TUNER_CANCEL_TONE_STATUS command, TC_NUM field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_LSB         0
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_MASK        0x01
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_MIN         0
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_MAX         1
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_TC_NUM_ONE  0
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_TC_NUM_TWO  1
   /* TUNER_CANCEL_TONE_STATUS command, ACTIVE field definition (address 3, size 1, lsb 0, unsigned)*/
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_ACTIVE_LSB         0
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_ACTIVE_MASK        0x01
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_ACTIVE_ACTIVE    0
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_ACTIVE_INACTIVE  1
   /* TUNER_CANCEL_TONE_STATUS command, STATUS field definition (address 3, size 4, lsb 1, unsigned)*/
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_LSB         1
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_MASK        0x0f
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_CLOSE_PC  8
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_DELAYED   3
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_ENABLED   0
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_NO_SPUR   6
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_STARTUP   1
   /* TUNER_CANCEL_TONE_STATUS command, TYPE field definition (address 3, size 3, lsb 5, unsigned)*/
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_LSB         5
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_MASK        0x07
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_FS32_SPUR  4
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_FS_SPUR    1
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_LO_SPUR    2
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_TS_SPUR    3
    #define Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_UNKNOWN    0
   /* TUNER_CANCEL_TONE_STATUS command, FREQ_KHZ field definition (address 4, size 16, lsb 0, signed)*/
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_FREQ_KHZ_LSB         0
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_FREQ_KHZ_MASK        0xffff
   #define  Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_FREQ_KHZ_SHIFT       16

#endif /* Si2190B_TUNER_CANCEL_TONE_STATUS_CMD */

/* Si2190B_TUNER_CANCEL_TONE command definition */
#define   Si2190B_TUNER_CANCEL_TONE_CMD 0x4a

#ifdef    Si2190B_TUNER_CANCEL_TONE_CMD
  #define Si2190B_TUNER_CANCEL_TONE_CMD_CODE 0x01004a

    typedef struct { /* Si2191C_TUNER_CANCEL_TONE_CMD_struct */
     unsigned int    div_a;
     unsigned int    div_b;
   } Si2190B_TUNER_CANCEL_TONE_CMD_struct;


    typedef struct { /* Si2191C_TUNER_CANCEL_TONE_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si2190B_TUNER_CANCEL_TONE_CMD_REPLY_struct;

   /* TUNER_CANCEL_TONE command, DIV_A field definition (address 4,size 16, lsb 0, unsigned) */
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_LSB         0
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_MASK        0xffff
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_MIN         0
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_MAX         65535
    #define Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_FREQ_MIN  0
    #define Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_FREQ_MAX  65535
   /* TUNER_CANCEL_TONE command, DIV_B field definition (address 6,size 16, lsb 0, unsigned) */
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_LSB         0
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_MASK        0xffff
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_MIN         0
   #define  Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_MAX         65535
    #define Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_FREQ_MIN  0
    #define Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_FREQ_MAX  65535
#endif /* Si2190B_TUNER_CANCEL_TONE_CMD */



/* Si21XXC_TUNER_STATUS command definition */
#define   Si21XXC_TUNER_STATUS_CMD 0x42

#ifdef    Si21XXC_TUNER_STATUS_CMD
  #define Si21XXC_TUNER_STATUS_CMD_CODE 0x010042

    typedef struct { /* Si21XXC_TUNER_STATUS_CMD_struct */
     unsigned char   intack;
   } Si21XXC_TUNER_STATUS_CMD_struct;


    typedef struct { /* Si21XXC_TUNER_STATUS_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
      unsigned char   tcint;
      unsigned char   rssilint;
      unsigned char   rssihint;
               int    vco_code;
      unsigned long   lo_freq;
      unsigned char   tc;
      unsigned char   rssil;
      unsigned char   rssih;
               char   rssi;
      unsigned long   freq;
      unsigned char   mode;
      unsigned char   sample_freq;
      unsigned char   wb_att_status;
   }  Si21XXC_TUNER_STATUS_CMD_REPLY_struct;

   /* TUNER_STATUS command, INTACK field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_TUNER_STATUS_CMD_INTACK_LSB         0
   #define  Si21XXC_TUNER_STATUS_CMD_INTACK_MASK        0x01
   #define  Si21XXC_TUNER_STATUS_CMD_INTACK_MIN         0
   #define  Si21XXC_TUNER_STATUS_CMD_INTACK_MAX         1
    #define Si21XXC_TUNER_STATUS_CMD_INTACK_CLEAR  1
    #define Si21XXC_TUNER_STATUS_CMD_INTACK_OK     0
   /* TUNER_STATUS command, TCINT field definition (address 1, size 1, lsb 0, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_TCINT_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_TCINT_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_TCINT_CHANGED    1
    #define Si21XXC_TUNER_STATUS_RESPONSE_TCINT_NO_CHANGE  0
   /* TUNER_STATUS command, RSSILINT field definition (address 1, size 1, lsb 1, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSILINT_LSB         1
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSILINT_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSILINT_CHANGED    1
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSILINT_NO_CHANGE  0
   /* TUNER_STATUS command, RSSIHINT field definition (address 1, size 1, lsb 2, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSIHINT_LSB         2
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSIHINT_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSIHINT_CHANGED    1
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSIHINT_NO_CHANGE  0
   /* TUNER_STATUS command, VCO_CODE field definition (address 10, size 16, lsb 0, signed)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_VCO_CODE_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_VCO_CODE_MASK        0xffff
   #define  Si21XXC_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT       16
   /* TUNER_STATUS command, LO_FREQ field definition (address 12, size 32, lsb 0, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_LO_FREQ_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_LO_FREQ_MASK        0xffffffff
   /* TUNER_STATUS command, TC field definition (address 2, size 1, lsb 0, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_TC_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_TC_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_TC_BUSY  0
    #define Si21XXC_TUNER_STATUS_RESPONSE_TC_DONE  1
   /* TUNER_STATUS command, RSSIL field definition (address 2, size 1, lsb 1, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSIL_LSB         1
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSIL_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSIL_LOW  1
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSIL_OK   0
   /* TUNER_STATUS command, RSSIH field definition (address 2, size 1, lsb 2, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSIH_LSB         2
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSIH_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSIH_HIGH  1
    #define Si21XXC_TUNER_STATUS_RESPONSE_RSSIH_OK    0
   /* TUNER_STATUS command, RSSI field definition (address 3, size 8, lsb 0, signed)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSI_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSI_MASK        0xff
   #define  Si21XXC_TUNER_STATUS_RESPONSE_RSSI_SHIFT       24
   /* TUNER_STATUS command, FREQ field definition (address 4, size 32, lsb 0, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_FREQ_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_FREQ_MASK        0xffffffff
   /* TUNER_STATUS command, MODE field definition (address 8, size 1, lsb 0, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_MODE_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_MODE_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_MODE_ATV  1
    #define Si21XXC_TUNER_STATUS_RESPONSE_MODE_DTV  0
   /* TUNER_STATUS command, WB_ATT_STATUS field definition (address 8, size 1, lsb 1, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_LSB         1
   #define  Si21XXC_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_MASK        0x01
    #define Si21XXC_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_OFF  0
    #define Si21XXC_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_ON   1
   /* TUNER_STATUS command, SAMPLE_FREQ field definition (address 9, size 8, lsb 0, unsigned)*/
   #define  Si21XXC_TUNER_STATUS_RESPONSE_SAMPLE_FREQ_LSB         0
   #define  Si21XXC_TUNER_STATUS_RESPONSE_SAMPLE_FREQ_MASK        0xff


#endif /* Si21XXC_TUNER_STATUS_CMD */

/* Si21XXC_TUNER_TUNE_FREQ command definition */
#define   Si21XXC_TUNER_TUNE_FREQ_CMD 0x41

#ifdef    Si21XXC_TUNER_TUNE_FREQ_CMD
  #define Si21XXC_TUNER_TUNE_FREQ_CMD_CODE 0x010041

    typedef struct { /* Si21XXC_TUNER_TUNE_FREQ_CMD_struct */
     unsigned char   mode;
     unsigned long   freq;
   } Si21XXC_TUNER_TUNE_FREQ_CMD_struct;


    typedef struct { /* Si21XXC_TUNER_TUNE_FREQ_CMD_REPLY_struct */
       Si21XXC_COMMON_REPLY_struct * STATUS;
   }  Si21XXC_TUNER_TUNE_FREQ_CMD_REPLY_struct;

   /* TUNER_TUNE_FREQ command, MODE field definition (address 1,size 1, lsb 0, unsigned) */
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_LSB         0
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_MASK        0x01
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_MIN         0
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_MAX         1
    #define Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_ATV  1
    #define Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_DTV  0
   /* TUNER_TUNE_FREQ command, FREQ field definition (address 4,size 32, lsb 0, unsigned) */
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB         0
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK        0xffffffff
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MIN         40000000
   #define  Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MAX         1002000000
    #define Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_FREQ_MIN  40000000
    #define Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_FREQ_MAX  1002000000
#endif /* Si21XXC_TUNER_TUNE_FREQ_CMD */



  /* --------------------------------------------*/
  /* COMMANDS STRUCT                             */
  /* This is used to store all command fields    */
  /* --------------------------------------------*/
  typedef struct { /* Si21XXC_CmdObj struct */
    #ifdef    Si21XXC_AGC_OVERRIDE_CMD
              Si21XXC_AGC_OVERRIDE_CMD_struct       agc_override;
    #endif /* Si21XXC_AGC_OVERRIDE_CMD */
    #ifdef    Si21XXC_ATV_RESTART_CMD
              Si21XXC_ATV_RESTART_CMD_struct        atv_restart;
    #endif /* Si21XXC_ATV_RESTART_CMD */
    #ifdef    Si21XXC_ATV_STATUS_CMD
              Si21XXC_ATV_STATUS_CMD_struct         atv_status;
    #endif /* Si21XXC_ATV_STATUS_CMD */
    #ifdef    Si21XXC_CONFIG_CLOCKS_CMD
              Si21XXC_CONFIG_CLOCKS_CMD_struct      config_clocks;
    #endif /* Si21XXC_CONFIG_CLOCKS_CMD */
    #ifdef    Si21XXC_CONFIG_I2C_CMD
              Si21XXC_CONFIG_I2C_CMD_struct         config_i2c;
    #endif /* Si21XXC_CONFIG_I2C_CMD */
    #ifdef    Si2190B_CONFIG_PINS_CMD
              Si21XXC_CONFIG_PINS_CMD_struct        config_pins;
    #endif /* Si2178B_CONFIG_PINS_CMD */
    #ifdef    Si21XXC_DTV_RESTART_CMD
              Si21XXC_DTV_RESTART_CMD_struct        dtv_restart;
    #endif /* Si21XXC_DTV_RESTART_CMD */
    #ifdef    Si21XXC_DTV_STATUS_CMD
              Si21XXC_DTV_STATUS_CMD_struct         dtv_status;
    #endif /* Si21XXC_DTV_STATUS_CMD */
    #ifdef    Si2178B_ENABLE_SSVD_ATV_CMD
              Si2178B_ENABLE_SSVD_ATV_CMD_struct  enable_ssvd_atv;
    #endif /* Si2178B_ENABLE_SSVD_ATV_CMD */
    #ifdef    Si21XXC_EXIT_BOOTLOADER_CMD
              Si21XXC_EXIT_BOOTLOADER_CMD_struct    exit_bootloader;
    #endif /* Si21XXC_EXIT_BOOTLOADER_CMD */
    #ifdef    Si21XXC_FINE_TUNE_CMD
              Si21XXC_FINE_TUNE_CMD_struct          fine_tune;
    #endif /* Si21XXC_FINE_TUNE_CMD */
    #ifdef    Si21XXC_GET_PROPERTY_CMD
              Si21XXC_GET_PROPERTY_CMD_struct       get_property;
    #endif /* Si21XXC_GET_PROPERTY_CMD */
    #ifdef    Si21XXC_GET_REV_CMD
              Si21XXC_GET_REV_CMD_struct            get_rev;
    #endif /* Si21XXC_GET_REV_CMD */
    #ifdef    Si2191C_ISL_STATUS_CMD
              Si2191C_ISL_STATUS_CMD_struct         isl_status;
    #endif /* Si2191C_ISL_STATUS_CMD */
    #ifdef    Si21XXC_PART_INFO_CMD
              Si21XXC_PART_INFO_CMD_struct          part_info;
    #endif /* Si21XXC_PART_INFO_CMD */
    #ifdef    Si2190B_PART_INFO2_CMD
              Si2190B_PART_INFO2_CMD_struct         part_info2;
    #endif /* Si2190B_PART_INFO2_CMD */
    #ifdef    Si21XXC_POWER_DOWN_HW_CMD
              Si21XXC_POWER_DOWN_HW_CMD_struct      power_down_hw;
    #endif /* Si21XXC_POWER_DOWN_HW_CMD */
    #ifdef    Si21XXC_POWER_UP_CMD
              Si21XXC_POWER_UP_CMD_struct           power_up;
    #endif /* Si21XXC_POWER_UP_CMD */
    #ifdef    Si2190B_REREAD_REPLY_CMD
              Si2190B_REREAD_REPLY_CMD_struct       reread_reply;
    #endif /* Si2190B_REREAD_REPLY_CMD */
    #ifdef    Si2190B_RESET_HW_CMD
              Si2190B_RESET_HW_CMD_struct           reset_hw;
    #endif /* Si2190B_RESET_HW_CMD */
    #ifdef    Si2190B_SELF_TEST_CMD
              Si2190B_SELF_TEST_CMD_struct          self_test;
    #endif /* Si2190B_SELF_TEST_CMD */
    #ifdef    Si21XXC_SET_PROPERTY_CMD
              Si21XXC_SET_PROPERTY_CMD_struct       set_property;
    #endif /* Si21XXC_SET_PROPERTY_CMD */
    #ifdef    Si2190B_SSVD_DEBUG_CONFIG_CMD
              Si2190B_SSVD_DEBUG_CONFIG_CMD_struct  ssvd_debug_config;
    #endif /* Si2190B_SSVD_DEBUG_CONFIG_CMD */
    #ifdef    Si2190B_SSVD_HDIV_CMD
              Si2190B_SSVD_HDIV_CMD_struct          ssvd_hdiv;
    #endif /* Si2190B_SSVD_HDIV_CMD */
    #ifdef    Si2190B_SSVD_MULTI_REG_RD_CMD
              Si2190B_SSVD_MULTI_REG_RD_CMD_struct  ssvd_multi_reg_rd;
    #endif /* Si2190B_SSVD_MULTI_REG_RD_CMD */
    #ifdef    Si2190B_SSVD_MULTI_REG_WR_CMD
              Si2190B_SSVD_MULTI_REG_WR_CMD_struct  ssvd_multi_reg_wr;
    #endif /* Si2190B_SSVD_MULTI_REG_WR_CMD */
    #ifdef    Si2190B_SSVD_POWER_DOWN_CMD
              Si2190B_SSVD_POWER_DOWN_CMD_struct    ssvd_power_down;
    #endif /* Si2190B_SSVD_POWER_DOWN_CMD */
    #ifdef    Si2190B_SSVD_POWER_UP_CMD
              Si2190B_SSVD_POWER_UP_CMD_struct      ssvd_power_up;
    #endif /* Si2190B_SSVD_POWER_UP_CMD */
    #ifdef    Si2190B_SSVD_REG_RD_CMD
              Si2190B_SSVD_REG_RD_CMD_struct        ssvd_reg_rd;
    #endif /* Si2190B_SSVD_REG_RD_CMD */
    #ifdef    Si2190B_SSVD_REG_WR_CMD
              Si2190B_SSVD_REG_WR_CMD_struct        ssvd_reg_wr;
    #endif /* Si2190B_SSVD_REG_WR_CMD */
    #ifdef    Si21XXC_STANDBY_CMD
              Si21XXC_STANDBY_CMD_struct            standby;
    #endif /* Si21XXC_STANDBY_CMD */
    #ifdef    Si2190B_TUNER_CANCEL_TONE_STATUS_CMD
              Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_struct  tuner_cancel_tone_status;
    #endif /* Si2190B_TUNER_CANCEL_TONE_STATUS_CMD */
    #ifdef    Si2190B_TUNER_CANCEL_TONE_CMD
              Si2190B_TUNER_CANCEL_TONE_CMD_struct  tuner_cancel_tone;
    #endif /* Si2190B_TUNER_CANCEL_TONE_CMD */
    #ifdef    Si21XXC_TUNER_STATUS_CMD
              Si21XXC_TUNER_STATUS_CMD_struct       tuner_status;
    #endif /* Si21XXC_TUNER_STATUS_CMD */
    #ifdef    Si21XXC_TUNER_TUNE_FREQ_CMD
              Si21XXC_TUNER_TUNE_FREQ_CMD_struct    tuner_tune_freq;
    #endif /* Si21XXC_TUNER_TUNE_FREQ_CMD */
  } Si21XXC_CmdObj;


  /* --------------------------------------------*/
  /* COMMANDS REPLY STRUCT                       */
  /* This stores all command reply fields        */
  /* --------------------------------------------*/
  typedef struct { /* Si21XXC_CmdReplyObj struct */
    #ifdef    Si21XXC_AGC_OVERRIDE_CMD
              Si21XXC_AGC_OVERRIDE_CMD_REPLY_struct       agc_override;
    #endif /* Si21XXC_AGC_OVERRIDE_CMD */
    #ifdef    Si21XXC_ATV_RESTART_CMD
              Si21XXC_ATV_RESTART_CMD_REPLY_struct        atv_restart;
    #endif /* Si21XXC_ATV_RESTART_CMD */
    #ifdef    Si21XXC_ATV_STATUS_CMD
              Si21XXC_ATV_STATUS_CMD_REPLY_struct         atv_status;
    #endif /* Si21XXC_ATV_STATUS_CMD */
    #ifdef    Si21XXC_CONFIG_CLOCKS_CMD
              Si21XXC_CONFIG_CLOCKS_CMD_REPLY_struct      config_clocks;
    #endif /* Si21XXC_CONFIG_CLOCKS_CMD */
    #ifdef    Si21XXC_CONFIG_I2C_CMD
              Si21XXC_CONFIG_I2C_CMD_REPLY_struct         config_i2c;
    #endif /* Si21XXC_CONFIG_I2C_CMD */
    #ifdef    Si2190B_CONFIG_PINS_CMD
              Si21XXC_CONFIG_PINS_CMD_REPLY_struct        config_pins;
    #endif /* Si2178B_CONFIG_PINS_CMD */
    #ifdef    Si21XXC_DTV_RESTART_CMD
              Si21XXC_DTV_RESTART_CMD_REPLY_struct        dtv_restart;
    #endif /* Si21XXC_DTV_RESTART_CMD */
    #ifdef    Si21XXC_DTV_STATUS_CMD
              Si21XXC_DTV_STATUS_CMD_REPLY_struct         dtv_status;
    #endif /* Si21XXC_DTV_STATUS_CMD */
    #ifdef    Si2178B_ENABLE_SSVD_ATV_CMD
              Si2178B_ENABLE_SSVD_ATV_CMD_REPLY_struct    enable_ssvd_atv;
    #endif /* Si2178B_ENABLE_SSVD_ATV_CMD */
    #ifdef    Si21XXC_EXIT_BOOTLOADER_CMD
              Si21XXC_EXIT_BOOTLOADER_CMD_REPLY_struct    exit_bootloader;
    #endif /* Si21XXC_EXIT_BOOTLOADER_CMD */
    #ifdef    Si21XXC_FINE_TUNE_CMD
              Si21XXC_FINE_TUNE_CMD_REPLY_struct          fine_tune;
    #endif /* Si21XXC_FINE_TUNE_CMD */
    #ifdef    Si21XXC_GET_PROPERTY_CMD
              Si21XXC_GET_PROPERTY_CMD_REPLY_struct       get_property;
    #endif /* Si21XXC_GET_PROPERTY_CMD */
    #ifdef    Si21XXC_GET_REV_CMD
              Si21XXC_GET_REV_CMD_REPLY_struct            get_rev;
    #endif /* Si21XXC_GET_REV_CMD */
    #ifdef    Si2191C_ISL_STATUS_CMD
              Si2191C_ISL_STATUS_CMD_REPLY_struct         isl_status;
    #endif /* Si2191C_ISL_STATUS_CMD */
    #ifdef    Si21XXC_PART_INFO_CMD
              Si21XXC_PART_INFO_CMD_REPLY_struct          part_info;
    #endif /* Si21XXC_PART_INFO_CMD */
    #ifdef    Si2190B_PART_INFO2_CMD
              Si2190B_PART_INFO2_CMD_REPLY_struct         part_info2;
    #endif /* Si2190B_PART_INFO2_CMD */
    #ifdef    Si21XXC_POWER_DOWN_HW_CMD
              Si21XXC_POWER_DOWN_HW_CMD_REPLY_struct      power_down_hw;
    #endif /* Si21XXC_POWER_DOWN_HW_CMD */
    #ifdef    Si21XXC_POWER_UP_CMD
              Si21XXC_POWER_UP_CMD_REPLY_struct           power_up;
    #endif /* Si21XXC_POWER_UP_CMD */
    #ifdef    Si2190B_REREAD_REPLY_CMD
              Si2190B_REREAD_REPLY_CMD_REPLY_struct       reread_reply;
    #endif /* Si2190B_REREAD_REPLY_CMD */
    #ifdef    Si2190B_RESET_HW_CMD
              Si2190B_RESET_HW_CMD_REPLY_struct           reset_hw;
    #endif /* Si2190B_RESET_HW_CMD */
    #ifdef    Si2190B_SELF_TEST_CMD
              Si2190B_SELF_TEST_CMD_REPLY_struct          self_test;
    #endif /* Si2190B_SELF_TEST_CMD */
    #ifdef    Si21XXC_SET_PROPERTY_CMD
              Si21XXC_SET_PROPERTY_CMD_REPLY_struct       set_property;
    #endif /* Si21XXC_SET_PROPERTY_CMD */
    #ifdef    Si2190B_SSVD_DEBUG_CONFIG_CMD
              Si2190B_SSVD_DEBUG_CONFIG_CMD_REPLY_struct  ssvd_debug_config;
    #endif /* Si2190B_SSVD_DEBUG_CONFIG_CMD */
    #ifdef    Si2190B_SSVD_HDIV_CMD
              Si2190B_SSVD_HDIV_CMD_REPLY_struct          ssvd_hdiv;
    #endif /* Si2190B_SSVD_HDIV_CMD */
    #ifdef    Si2190B_SSVD_MULTI_REG_RD_CMD
              Si2190B_SSVD_MULTI_REG_RD_CMD_REPLY_struct  ssvd_multi_reg_rd;
    #endif /* Si2190B_SSVD_MULTI_REG_RD_CMD */
    #ifdef    Si2190B_SSVD_MULTI_REG_WR_CMD
              Si2190B_SSVD_MULTI_REG_WR_CMD_REPLY_struct  ssvd_multi_reg_wr;
    #endif /* Si2190B_SSVD_MULTI_REG_WR_CMD */
    #ifdef    Si2190B_SSVD_POWER_DOWN_CMD
              Si2190B_SSVD_POWER_DOWN_CMD_REPLY_struct    ssvd_power_down;
    #endif /* Si2190B_SSVD_POWER_DOWN_CMD */
    #ifdef    Si2190B_SSVD_POWER_UP_CMD
              Si2190B_SSVD_POWER_UP_CMD_REPLY_struct      ssvd_power_up;
    #endif /* Si2190B_SSVD_POWER_UP_CMD */
    #ifdef    Si2190B_SSVD_REG_RD_CMD
              Si2190B_SSVD_REG_RD_CMD_REPLY_struct        ssvd_reg_rd;
    #endif /* Si2190B_SSVD_REG_RD_CMD */
    #ifdef    Si2190B_SSVD_REG_WR_CMD
              Si2190B_SSVD_REG_WR_CMD_REPLY_struct        ssvd_reg_wr;
    #endif /* Si2190B_SSVD_REG_WR_CMD */
    #ifdef    Si21XXC_STANDBY_CMD
              Si21XXC_STANDBY_CMD_REPLY_struct            standby;
    #endif /* Si21XXC_STANDBY_CMD */
    #ifdef    Si2190B_TUNER_CANCEL_TONE_STATUS_CMD
              Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_REPLY_struct  tuner_cancel_tone_status;
    #endif /* Si2190B_TUNER_CANCEL_TONE_STATUS_CMD */
    #ifdef    Si2190B_TUNER_CANCEL_TONE_CMD
              Si2190B_TUNER_CANCEL_TONE_CMD_REPLY_struct  tuner_cancel_tone;
    #endif /* Si2190B_TUNER_CANCEL_TONE_CMD */
    #ifdef    Si21XXC_TUNER_STATUS_CMD
              Si21XXC_TUNER_STATUS_CMD_REPLY_struct       tuner_status;
    #endif /* Si21XXC_TUNER_STATUS_CMD */
    #ifdef    Si21XXC_TUNER_TUNE_FREQ_CMD
              Si21XXC_TUNER_TUNE_FREQ_CMD_REPLY_struct    tuner_tune_freq;
    #endif /* Si21XXC_TUNER_TUNE_FREQ_CMD */
  } Si21XXC_CmdReplyObj;

#ifdef    Si21XXC_COMMAND_PROTOTYPES
#define   Si21XXC_GET_COMMAND_STRINGS
#endif /* Si21XXC_COMMAND_PROTOTYPES */
#ifdef __cplusplus
}
#endif
#endif /* Si21XXC_COMMANDS_H */





