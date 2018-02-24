/* Automatically generated from a template on 2011 January 24 at 13:47 */ /*( Processed on PC0009853 (joluers) ) */
/***************************************************************************************/
/* FILE: Si2176_Commands.h                                                             */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/

#ifndef    Si2176_COMMANDS_H
#define    Si2176_COMMANDS_H

#define Si2176_COMMAND_PROTOTYPES
/* _status_defines_insertion_start */

/* move code to remove compile error by yooheeyong 20110523 */
/* STATUS structure definition */
  typedef struct { /* Si2170_COMMON_REPLY_struct */
    unsigned char   tunint;
    unsigned char   atvint;
    unsigned char   dtvint;
    unsigned char   err;
    unsigned char   cts;
 }  Si2176_COMMON_REPLY_struct;

/* STATUS fields definition */
  /* STATUS, TUNINT field definition (size 1, lsb 0, unsigned)*/
  #define  Si2176_STATUS_TUNINT_LSB         0
  #define  Si2176_STATUS_TUNINT_MASK        0x01
   #define Si2176_STATUS_TUNINT_NOT_TRIGGERED  0
   #define Si2176_STATUS_TUNINT_TRIGGERED      1
  /* STATUS, ATVINT field definition (size 1, lsb 1, unsigned)*/
  #define  Si2176_STATUS_ATVINT_LSB         1
  #define  Si2176_STATUS_ATVINT_MASK        0x01
   #define Si2176_STATUS_ATVINT_NOT_TRIGGERED  0
   #define Si2176_STATUS_ATVINT_TRIGGERED      1
  /* STATUS, DTVINT field definition (size 1, lsb 2, unsigned)*/
  #define  Si2176_STATUS_DTVINT_LSB         2
  #define  Si2176_STATUS_DTVINT_MASK        0x01
   #define Si2176_STATUS_DTVINT_NOT_TRIGGERED  0
   #define Si2176_STATUS_DTVINT_TRIGGERED      1
  /* STATUS, ERR field definition (size 1, lsb 6, unsigned)*/
  #define  Si2176_STATUS_ERR_LSB         6
  #define  Si2176_STATUS_ERR_MASK        0x01
   #define Si2176_STATUS_ERR_ERROR     1
   #define Si2176_STATUS_ERR_NO_ERROR  0
  /* STATUS, CTS field definition (size 1, lsb 7, unsigned)*/
  #define  Si2176_STATUS_CTS_LSB         7
  #define  Si2176_STATUS_CTS_MASK        0x01
   #define Si2176_STATUS_CTS_COMPLETED  1
   #define Si2176_STATUS_CTS_WAIT       0

/* _status_defines_insertion_point */

/* _commands_defines_insertion_start */
/* Si2176_AGC_OVERRIDE command definition */
#define Si2176_AGC_OVERRIDE_CMD 0x44

#ifdef    Si2176_AGC_OVERRIDE_CMD

    typedef struct { /* Si2176_AGC_OVERRIDE_CMD_struct */
     unsigned char   force_max_gain;
     unsigned char   force_top_gain;
   } Si2176_AGC_OVERRIDE_CMD_struct;

   /* AGC_OVERRIDE command, FORCE_MAX_GAIN field definition (size 1, lsb 0, unsigned) */
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB         0
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK        0x01
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MIN         0
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX         1
    #define Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE  0
    #define Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE   1
   /* AGC_OVERRIDE command, FORCE_TOP_GAIN field definition (size 1, lsb 1, unsigned) */
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB         1
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK        0x01
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MIN         0
   #define  Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX         1
    #define Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE  0
    #define Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE   1

    typedef struct { /* Si2176_AGC_OVERRIDE_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_AGC_OVERRIDE_CMD_REPLY_struct;

#endif /* Si2176_AGC_OVERRIDE_CMD */

/* Si2176_ATV_RESTART command definition */
#define Si2176_ATV_RESTART_CMD 0x51

#ifdef    Si2176_ATV_RESTART_CMD

    typedef struct { /* Si2176_ATV_RESTART_CMD_struct */
     unsigned char   mode;
   } Si2176_ATV_RESTART_CMD_struct;

   /* ATV_RESTART command, MODE field definition (size 1, lsb 0, unsigned) */
   #define  Si2176_ATV_RESTART_CMD_MODE_LSB         0
   #define  Si2176_ATV_RESTART_CMD_MODE_MASK        0x01
   #define  Si2176_ATV_RESTART_CMD_MODE_MIN         0
   #define  Si2176_ATV_RESTART_CMD_MODE_MAX         1
    #define Si2176_ATV_RESTART_CMD_MODE_AUDIO_ONLY   1
    #define Si2176_ATV_RESTART_CMD_MODE_AUDIO_VIDEO  0

    typedef struct { /* Si2176_ATV_RESTART_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_ATV_RESTART_CMD_REPLY_struct;

#endif /* Si2176_ATV_RESTART_CMD */

/* Si2176_ATV_STATUS command definition */
#define Si2176_ATV_STATUS_CMD 0x52

#ifdef    Si2176_ATV_STATUS_CMD

    typedef struct { /* Si2176_ATV_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2176_ATV_STATUS_CMD_struct;

   /* ATV_STATUS command, INTACK field definition (size 1, lsb 0, unsigned) */
   #define  Si2176_ATV_STATUS_CMD_INTACK_LSB         0
   #define  Si2176_ATV_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2176_ATV_STATUS_CMD_INTACK_MIN         0
   #define  Si2176_ATV_STATUS_CMD_INTACK_MAX         1
    #define Si2176_ATV_STATUS_CMD_INTACK_CLEAR  1
    #define Si2176_ATV_STATUS_CMD_INTACK_OK     0

    typedef struct { /* Si2176_ATV_STATUS_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   chlint;
      unsigned char   pclint;
      unsigned char   dlint;
      unsigned char   snrlint;
      unsigned char   snrhint;
      unsigned char   audio_chan_bw;
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
      unsigned char   trans;
      unsigned char   audio_sys;
      unsigned char   audio_demod_mode;
   }  Si2176_ATV_STATUS_CMD_REPLY_struct;

   /* ATV_STATUS command, CHLINT field definition (size 1, lsb 0, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_CHLINT_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_CHLINT_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_CHLINT_CHANGED    1
    #define Si2176_ATV_STATUS_RESPONSE_CHLINT_NO_CHANGE  0
   /* ATV_STATUS command, PCLINT field definition (size 1, lsb 1, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_PCLINT_LSB         1
   #define  Si2176_ATV_STATUS_RESPONSE_PCLINT_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_PCLINT_CHANGED    1
    #define Si2176_ATV_STATUS_RESPONSE_PCLINT_NO_CHANGE  0
   /* ATV_STATUS command, DLINT field definition (size 1, lsb 2, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_DLINT_LSB         2
   #define  Si2176_ATV_STATUS_RESPONSE_DLINT_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_DLINT_CHANGED    1
    #define Si2176_ATV_STATUS_RESPONSE_DLINT_NO_CHANGE  0
   /* ATV_STATUS command, SNRLINT field definition (size 1, lsb 3, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_SNRLINT_LSB         3
   #define  Si2176_ATV_STATUS_RESPONSE_SNRLINT_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_SNRLINT_CHANGED    1
    #define Si2176_ATV_STATUS_RESPONSE_SNRLINT_NO_CHANGE  0
   /* ATV_STATUS command, SNRHINT field definition (size 1, lsb 4, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_SNRHINT_LSB         4
   #define  Si2176_ATV_STATUS_RESPONSE_SNRHINT_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_SNRHINT_CHANGED    1
    #define Si2176_ATV_STATUS_RESPONSE_SNRHINT_NO_CHANGE  0
   /* ATV_STATUS command, AUDIO_CHAN_BW field definition (size 4, lsb 0, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_MASK        0x0f
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_12X_OVERMOD     3
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_150_KHZ_OFFSET  8
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_15_KHZ_OFFSET   5
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_30_KHZ_OFFSET   6
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_4X_OVERMOD      1
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_75_KHZ_OFFSET   7
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_7P5_KHZ_OFFSET  4
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_8X_OVERMOD      2
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_RSVD            0
   /* ATV_STATUS command, CHL field definition (size 1, lsb 0, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_CHL_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_CHL_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_CHL_CHANNEL     1
    #define Si2176_ATV_STATUS_RESPONSE_CHL_NO_CHANNEL  0
   /* ATV_STATUS command, PCL field definition (size 1, lsb 1, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_PCL_LSB         1
   #define  Si2176_ATV_STATUS_RESPONSE_PCL_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_PCL_LOCKED   1
    #define Si2176_ATV_STATUS_RESPONSE_PCL_NO_LOCK  0
   /* ATV_STATUS command, DL field definition (size 1, lsb 2, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_DL_LSB         2
   #define  Si2176_ATV_STATUS_RESPONSE_DL_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_DL_LOCKED   1
    #define Si2176_ATV_STATUS_RESPONSE_DL_NO_LOCK  0
   /* ATV_STATUS command, SNRL field definition (size 1, lsb 3, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_SNRL_LSB         3
   #define  Si2176_ATV_STATUS_RESPONSE_SNRL_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_SNRL_SNR_LOW      1
    #define Si2176_ATV_STATUS_RESPONSE_SNRL_SNR_NOT_LOW  0
   /* ATV_STATUS command, SNRH field definition (size 1, lsb 4, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_SNRH_LSB         4
   #define  Si2176_ATV_STATUS_RESPONSE_SNRH_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_SNRH_SNR_HIGH      1
    #define Si2176_ATV_STATUS_RESPONSE_SNRH_SNR_NOT_HIGH  0
   /* ATV_STATUS command, VIDEO_SNR field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_VIDEO_SNR_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_VIDEO_SNR_MASK        0xff
   /* ATV_STATUS command, AFC_FREQ field definition (size 16, lsb 0, signed)*/
   #define  Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_MASK        0xffff
   #define  Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT       16
   /* ATV_STATUS command, VIDEO_SC_SPACING field definition (size 16, lsb 0, signed)*/
   #define  Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_MASK        0xffff
   #define  Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_SHIFT       16
   /* ATV_STATUS command, VIDEO_SYS field definition (size 3, lsb 0, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_MASK        0x07
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_B   0
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_DK  5
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_GH  1
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_I   4
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_L   6
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_LP  7
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_M   2
    #define Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_N   3
   /* ATV_STATUS command, COLOR field definition (size 1, lsb 4, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_COLOR_LSB         4
   #define  Si2176_ATV_STATUS_RESPONSE_COLOR_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_COLOR_PAL_NTSC  0
    #define Si2176_ATV_STATUS_RESPONSE_COLOR_SECAM     1
   /* ATV_STATUS command, TRANS field definition (size 1, lsb 6, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_TRANS_LSB         6
   #define  Si2176_ATV_STATUS_RESPONSE_TRANS_MASK        0x01
    #define Si2176_ATV_STATUS_RESPONSE_TRANS_CABLE        1
    #define Si2176_ATV_STATUS_RESPONSE_TRANS_TERRESTRIAL  0
   /* ATV_STATUS command, AUDIO_SYS field definition (size 4, lsb 0, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_LSB         0
   #define  Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_MASK        0x0f
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_A2          3
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_A2_DK2      4
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_A2_DK3      5
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_A2_DK4      9
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_BTSC        6
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_EIAJ        7
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_MONO        1
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_MONO_NICAM  2
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_RSVD        0
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_SCAN        8
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_WIDE_SCAN   10
   /* ATV_STATUS command, AUDIO_DEMOD_MODE field definition (size 2, lsb 4, unsigned)*/
   #define  Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_LSB         4
   #define  Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_MASK        0x03
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_AM   1
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_FM1  2
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_FM2  3
    #define Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_SIF  0

#endif /* Si2176_ATV_STATUS_CMD */

/* Si2176_CONFIG_PINS command definition */
#define Si2176_CONFIG_PINS_CMD 0x12

#ifdef    Si2176_CONFIG_PINS_CMD

    typedef struct { /* Si2176_CONFIG_PINS_CMD_struct */
     unsigned char   gpio1_mode;
     unsigned char   gpio1_read;
     unsigned char   gpio2_mode;
     unsigned char   gpio2_read;
     unsigned char   gpio3_mode;
     unsigned char   gpio3_read;
     unsigned char   bclk1_mode;
     unsigned char   bclk1_read;
     unsigned char   xout_mode;
   } Si2176_CONFIG_PINS_CMD_struct;

   /* CONFIG_PINS command, GPIO1_MODE field definition (size 7, lsb 0, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_MODE_MASK        0x7f
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_MODE_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_MODE_MAX         3
    #define Si2176_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE    1
    #define Si2176_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_0    2
    #define Si2176_CONFIG_PINS_CMD_GPIO1_MODE_DRIVE_1    3
    #define Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, GPIO1_READ field definition (size 1, lsb 7, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_READ_LSB         7
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_READ_MASK        0x01
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_READ_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO1_READ_MAX         1
    #define Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ  0
    #define Si2176_CONFIG_PINS_CMD_GPIO1_READ_READ         1
   /* CONFIG_PINS command, GPIO2_MODE field definition (size 7, lsb 0, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_MODE_MASK        0x7f
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_MODE_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_MODE_MAX         3
    #define Si2176_CONFIG_PINS_CMD_GPIO2_MODE_DISABLE    1
    #define Si2176_CONFIG_PINS_CMD_GPIO2_MODE_DRIVE_0    2
    #define Si2176_CONFIG_PINS_CMD_GPIO2_MODE_DRIVE_1    3
    #define Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, GPIO2_READ field definition (size 1, lsb 7, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_READ_LSB         7
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_READ_MASK        0x01
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_READ_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO2_READ_MAX         1
    #define Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ  0
    #define Si2176_CONFIG_PINS_CMD_GPIO2_READ_READ         1
   /* CONFIG_PINS command, GPIO3_MODE field definition (size 7, lsb 0, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_MODE_MASK        0x7f
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_MODE_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_MODE_MAX         3
    #define Si2176_CONFIG_PINS_CMD_GPIO3_MODE_DISABLE    1
    #define Si2176_CONFIG_PINS_CMD_GPIO3_MODE_DRIVE_0    2
    #define Si2176_CONFIG_PINS_CMD_GPIO3_MODE_DRIVE_1    3
    #define Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE  0
   /* CONFIG_PINS command, GPIO3_READ field definition (size 1, lsb 7, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_READ_LSB         7
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_READ_MASK        0x01
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_READ_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_GPIO3_READ_MAX         1
    #define Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ  0
    #define Si2176_CONFIG_PINS_CMD_GPIO3_READ_READ         1
   /* CONFIG_PINS command, BCLK1_MODE field definition (size 7, lsb 0, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_MODE_MASK        0x7f
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_MODE_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_MODE_MAX         11
    #define Si2176_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE    1
    #define Si2176_CONFIG_PINS_CMD_BCLK1_MODE_NO_CHANGE  0
    #define Si2176_CONFIG_PINS_CMD_BCLK1_MODE_XOUT       10
    #define Si2176_CONFIG_PINS_CMD_BCLK1_MODE_XOUT_HIGH  11
   /* CONFIG_PINS command, BCLK1_READ field definition (size 1, lsb 7, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_READ_LSB         7
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_READ_MASK        0x01
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_READ_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_BCLK1_READ_MAX         1
    #define Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ  0
    #define Si2176_CONFIG_PINS_CMD_BCLK1_READ_READ         1
   /* CONFIG_PINS command, XOUT_MODE field definition (size 7, lsb 0, unsigned) */
   #define  Si2176_CONFIG_PINS_CMD_XOUT_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_CMD_XOUT_MODE_MASK        0x7f
   #define  Si2176_CONFIG_PINS_CMD_XOUT_MODE_MIN         0
   #define  Si2176_CONFIG_PINS_CMD_XOUT_MODE_MAX         10
    #define Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE    1
    #define Si2176_CONFIG_PINS_CMD_XOUT_MODE_NO_CHANGE  0
    #define Si2176_CONFIG_PINS_CMD_XOUT_MODE_XOUT       10

    typedef struct { /* Si2176_CONFIG_PINS_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   gpio1_mode;
      unsigned char   gpio1_state;
      unsigned char   gpio2_mode;
      unsigned char   gpio2_state;
      unsigned char   gpio3_mode;
      unsigned char   gpio3_state;
      unsigned char   bclk1_mode;
      unsigned char   bclk1_state;
      unsigned char   xout_mode;
   }  Si2176_CONFIG_PINS_CMD_REPLY_struct;

   /* CONFIG_PINS command, GPIO1_MODE field definition (size 7, lsb 0, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK        0x7f
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_DISABLE  1
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_0  2
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_DRIVE_1  3
   /* CONFIG_PINS command, GPIO1_STATE field definition (size 1, lsb 7, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB         7
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK        0x01
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_0  0
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_READ_1  1
   /* CONFIG_PINS command, GPIO2_MODE field definition (size 7, lsb 0, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK        0x7f
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_DISABLE  1
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_DRIVE_0  2
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_DRIVE_1  3
   /* CONFIG_PINS command, GPIO2_STATE field definition (size 1, lsb 7, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB         7
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK        0x01
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_READ_0  0
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_READ_1  1
   /* CONFIG_PINS command, GPIO3_MODE field definition (size 7, lsb 0, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_MASK        0x7f
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_DISABLE  1
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_DRIVE_0  2
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_DRIVE_1  3
   /* CONFIG_PINS command, GPIO3_STATE field definition (size 1, lsb 7, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_LSB         7
   #define  Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_MASK        0x01
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_READ_0  0
    #define Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_READ_1  1
   /* CONFIG_PINS command, BCLK1_MODE field definition (size 7, lsb 0, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_MASK        0x7f
    #define Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_DISABLE    1
    #define Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_XOUT       10
    #define Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_XOUT_HIGH  11
   /* CONFIG_PINS command, BCLK1_STATE field definition (size 1, lsb 7, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_LSB         7
   #define  Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_MASK        0x01
    #define Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_READ_0  0
    #define Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_READ_1  1
   /* CONFIG_PINS command, XOUT_MODE field definition (size 7, lsb 0, unsigned)*/
   #define  Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_LSB         0
   #define  Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_MASK        0x7f
    #define Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_DISABLE  1
    #define Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_XOUT     10

#endif /* Si2176_CONFIG_PINS_CMD */

/* Si2176_DTV_RESTART command definition */
#define Si2176_DTV_RESTART_CMD 0x61

#ifdef    Si2176_DTV_RESTART_CMD

    typedef struct { /* Si2176_DTV_RESTART_CMD_struct */
         unsigned char   nothing;   } Si2176_DTV_RESTART_CMD_struct;


    typedef struct { /* Si2176_DTV_RESTART_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_DTV_RESTART_CMD_REPLY_struct;

#endif /* Si2176_DTV_RESTART_CMD */

/* Si2176_DTV_STATUS command definition */
#define Si2176_DTV_STATUS_CMD 0x62

#ifdef    Si2176_DTV_STATUS_CMD

    typedef struct { /* Si2176_DTV_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2176_DTV_STATUS_CMD_struct;

   /* DTV_STATUS command, INTACK field definition (size 1, lsb 0, unsigned) */
   #define  Si2176_DTV_STATUS_CMD_INTACK_LSB         0
   #define  Si2176_DTV_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2176_DTV_STATUS_CMD_INTACK_MIN         0
   #define  Si2176_DTV_STATUS_CMD_INTACK_MAX         1
    #define Si2176_DTV_STATUS_CMD_INTACK_CLEAR  1
    #define Si2176_DTV_STATUS_CMD_INTACK_OK     0

    typedef struct { /* Si2176_DTV_STATUS_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   chlint;
      unsigned char   chl;
      unsigned char   bw;
      unsigned char   modulation;
   }  Si2176_DTV_STATUS_CMD_REPLY_struct;

   /* DTV_STATUS command, CHLINT field definition (size 1, lsb 0, unsigned)*/
   #define  Si2176_DTV_STATUS_RESPONSE_CHLINT_LSB         0
   #define  Si2176_DTV_STATUS_RESPONSE_CHLINT_MASK        0x01
    #define Si2176_DTV_STATUS_RESPONSE_CHLINT_CHANGED    1
    #define Si2176_DTV_STATUS_RESPONSE_CHLINT_NO_CHANGE  0
   /* DTV_STATUS command, CHL field definition (size 1, lsb 0, unsigned)*/
   #define  Si2176_DTV_STATUS_RESPONSE_CHL_LSB         0
   #define  Si2176_DTV_STATUS_RESPONSE_CHL_MASK        0x01
    #define Si2176_DTV_STATUS_RESPONSE_CHL_CHANNEL     1
    #define Si2176_DTV_STATUS_RESPONSE_CHL_NO_CHANNEL  0
   /* DTV_STATUS command, BW field definition (size 4, lsb 0, unsigned)*/
   #define  Si2176_DTV_STATUS_RESPONSE_BW_LSB         0
   #define  Si2176_DTV_STATUS_RESPONSE_BW_MASK        0x0f
    #define Si2176_DTV_STATUS_RESPONSE_BW_BW_6MHZ  6
    #define Si2176_DTV_STATUS_RESPONSE_BW_BW_7MHZ  7
    #define Si2176_DTV_STATUS_RESPONSE_BW_BW_8MHZ  8
   /* DTV_STATUS command, MODULATION field definition (size 4, lsb 4, unsigned)*/
   #define  Si2176_DTV_STATUS_RESPONSE_MODULATION_LSB         4
   #define  Si2176_DTV_STATUS_RESPONSE_MODULATION_MASK        0x0f
    #define Si2176_DTV_STATUS_RESPONSE_MODULATION_ATSC    0
    #define Si2176_DTV_STATUS_RESPONSE_MODULATION_DTMB    6
    #define Si2176_DTV_STATUS_RESPONSE_MODULATION_DVBC    3
    #define Si2176_DTV_STATUS_RESPONSE_MODULATION_DVBT    2
    #define Si2176_DTV_STATUS_RESPONSE_MODULATION_ISDBC   5
    #define Si2176_DTV_STATUS_RESPONSE_MODULATION_ISDBT   4
    #define Si2176_DTV_STATUS_RESPONSE_MODULATION_QAM_US  1

#endif /* Si2176_DTV_STATUS_CMD */

/* Si2176_EXIT_BOOTLOADER command definition */
#define Si2176_EXIT_BOOTLOADER_CMD 0x01

#ifdef    Si2176_EXIT_BOOTLOADER_CMD

    typedef struct { /* Si2176_EXIT_BOOTLOADER_CMD_struct */
     unsigned char   func;
     unsigned char   ctsien;
   } Si2176_EXIT_BOOTLOADER_CMD_struct;

   /* EXIT_BOOTLOADER command, FUNC field definition (size 4, lsb 0, unsigned) */
   #define  Si2176_EXIT_BOOTLOADER_CMD_FUNC_LSB         0
   #define  Si2176_EXIT_BOOTLOADER_CMD_FUNC_MASK        0x0f
   #define  Si2176_EXIT_BOOTLOADER_CMD_FUNC_MIN         0
   #define  Si2176_EXIT_BOOTLOADER_CMD_FUNC_MAX         1
    #define Si2176_EXIT_BOOTLOADER_CMD_FUNC_BOOTLOADER  0
    #define Si2176_EXIT_BOOTLOADER_CMD_FUNC_TUNER       1
   /* EXIT_BOOTLOADER command, CTSIEN field definition (size 1, lsb 7, unsigned) */
   #define  Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_LSB         7
   #define  Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_MASK        0x01
   #define  Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_MIN         0
   #define  Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_MAX         1
    #define Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_OFF  0
    #define Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_ON   1

    typedef struct { /* Si2176_EXIT_BOOTLOADER_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_EXIT_BOOTLOADER_CMD_REPLY_struct;

#endif /* Si2176_EXIT_BOOTLOADER_CMD */

/* Si2176_FINE_TUNE command definition */
#define Si2176_FINE_TUNE_CMD 0x45

#ifdef    Si2176_FINE_TUNE_CMD

    typedef struct { /* Si2176_FINE_TUNE_CMD_struct */
     unsigned char   reserved;
              int    offset_500hz;
   } Si2176_FINE_TUNE_CMD_struct;

   /* FINE_TUNE command, RESERVED field definition (size 8, lsb 0, unsigned) */
   #define  Si2176_FINE_TUNE_CMD_RESERVED_LSB         0
   #define  Si2176_FINE_TUNE_CMD_RESERVED_MASK        0xff
   #define  Si2176_FINE_TUNE_CMD_RESERVED_MIN         0
   #define  Si2176_FINE_TUNE_CMD_RESERVED_MAX         0
   #define  Si2176_FINE_TUNE_CMD_RESERVED_RESERVED    0
   // change code for compatible semco code by yooheeyong 20110523, do comment by yooheeyong 20110523 
   //#define  Si2176_FINE_TUNE_CMD_RESERVED_MAX         1   
   //#define  Si2176_FINE_TUNE_CMD_RESERVED_ATV         1
   //#define  Si2176_FINE_TUNE_CMD_RESERVED_DTV        0

   /* FINE_TUNE command, OFFSET_500HZ field definition (size 16, lsb 0, signed) */
   #define  Si2176_FINE_TUNE_CMD_OFFSET_500HZ_LSB         0
   #define  Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MASK        0xffff
   #define  Si2176_FINE_TUNE_CMD_OFFSET_500HZ_SHIFT       16
   #define  Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MIN         -4000
   #define  Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MAX         4000
    #define Si2176_FINE_TUNE_CMD_OFFSET_500HZ_OFFSET_500HZ_MIN  -4000
    #define Si2176_FINE_TUNE_CMD_OFFSET_500HZ_OFFSET_500HZ_MAX  4000

    typedef struct { /* Si2176_FINE_TUNE_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_FINE_TUNE_CMD_REPLY_struct;

#endif /* Si2176_FINE_TUNE_CMD */

/* Si2176_GET_PROPERTY command definition */
#define Si2176_GET_PROPERTY_CMD 0x15

#ifdef    Si2176_GET_PROPERTY_CMD

    typedef struct { /* Si2176_GET_PROPERTY_CMD_struct */
     unsigned char   reserved;
     unsigned int    prop;
   } Si2176_GET_PROPERTY_CMD_struct;

   /* GET_PROPERTY command, RESERVED field definition (size 8, lsb 0, unsigned) */
   #define  Si2176_GET_PROPERTY_CMD_RESERVED_LSB         0
   #define  Si2176_GET_PROPERTY_CMD_RESERVED_MASK        0xff
   #define  Si2176_GET_PROPERTY_CMD_RESERVED_MIN         0
   #define  Si2176_GET_PROPERTY_CMD_RESERVED_MAX         0
    #define Si2176_GET_PROPERTY_CMD_RESERVED_RESERVED_MIN  0
    #define Si2176_GET_PROPERTY_CMD_RESERVED_RESERVED_MAX  0
   /* GET_PROPERTY command, PROP field definition (size 16, lsb 0, unsigned) */
   #define  Si2176_GET_PROPERTY_CMD_PROP_LSB         0
   #define  Si2176_GET_PROPERTY_CMD_PROP_MASK        0xffff
   #define  Si2176_GET_PROPERTY_CMD_PROP_MIN         0
   #define  Si2176_GET_PROPERTY_CMD_PROP_MAX         65535
    #define Si2176_GET_PROPERTY_CMD_PROP_PROP_MIN  0
    #define Si2176_GET_PROPERTY_CMD_PROP_PROP_MAX  65535

    typedef struct { /* Si2176_GET_PROPERTY_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data;
   }  Si2176_GET_PROPERTY_CMD_REPLY_struct;

   /* GET_PROPERTY command, RESERVED field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_GET_PROPERTY_RESPONSE_RESERVED_LSB         0
   #define  Si2176_GET_PROPERTY_RESPONSE_RESERVED_MASK        0xff
   /* GET_PROPERTY command, DATA field definition (size 16, lsb 0, unsigned)*/
   #define  Si2176_GET_PROPERTY_RESPONSE_DATA_LSB         0
   #define  Si2176_GET_PROPERTY_RESPONSE_DATA_MASK        0xffff

#endif /* Si2176_GET_PROPERTY_CMD */

/* Si2176_GET_REV command definition */
#define Si2176_GET_REV_CMD 0x11

#ifdef    Si2176_GET_REV_CMD

    typedef struct { /* Si2176_GET_REV_CMD_struct */
         unsigned char   nothing;   } Si2176_GET_REV_CMD_struct;


    typedef struct { /* Si2176_GET_REV_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   pn;
      unsigned char   fwmajor;
      unsigned char   fwminor;
      unsigned int    patch;
      unsigned char   cmpmajor;
      unsigned char   cmpminor;
      unsigned char   cmpbuild;
      unsigned char   chiprev;
   }  Si2176_GET_REV_CMD_REPLY_struct;

   /* GET_REV command, PN field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_PN_LSB         0
   #define  Si2176_GET_REV_RESPONSE_PN_MASK        0xff
   /* GET_REV command, FWMAJOR field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_FWMAJOR_LSB         0
   #define  Si2176_GET_REV_RESPONSE_FWMAJOR_MASK        0xff
   /* GET_REV command, FWMINOR field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_FWMINOR_LSB         0
   #define  Si2176_GET_REV_RESPONSE_FWMINOR_MASK        0xff
   /* GET_REV command, PATCH field definition (size 16, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_PATCH_LSB         0
   #define  Si2176_GET_REV_RESPONSE_PATCH_MASK        0xffff
   /* GET_REV command, CMPMAJOR field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_CMPMAJOR_LSB         0
   #define  Si2176_GET_REV_RESPONSE_CMPMAJOR_MASK        0xff
   /* GET_REV command, CMPMINOR field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_CMPMINOR_LSB         0
   #define  Si2176_GET_REV_RESPONSE_CMPMINOR_MASK        0xff
   /* GET_REV command, CMPBUILD field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_CMPBUILD_LSB         0
   #define  Si2176_GET_REV_RESPONSE_CMPBUILD_MASK        0xff
    #define Si2176_GET_REV_RESPONSE_CMPBUILD_CMPBUILD_MIN  0
    #define Si2176_GET_REV_RESPONSE_CMPBUILD_CMPBUILD_MAX  255
   /* GET_REV command, CHIPREV field definition (size 4, lsb 0, unsigned)*/
   #define  Si2176_GET_REV_RESPONSE_CHIPREV_LSB         0
   #define  Si2176_GET_REV_RESPONSE_CHIPREV_MASK        0x0f
    #define Si2176_GET_REV_RESPONSE_CHIPREV_A  1
    #define Si2176_GET_REV_RESPONSE_CHIPREV_B  2

#endif /* Si2176_GET_REV_CMD */

/* Si2176_PART_INFO command definition */
#define Si2176_PART_INFO_CMD 0x02

#ifdef    Si2176_PART_INFO_CMD

    typedef struct { /* Si2176_PART_INFO_CMD_struct */
         unsigned char   nothing;   } Si2176_PART_INFO_CMD_struct;


    typedef struct { /* Si2176_PART_INFO_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   chiprev;
      unsigned char   romid;
      unsigned char   part;
      unsigned char   pmajor;
      unsigned char   pminor;
      unsigned char   pbuild;
      unsigned int    reserved;
      unsigned long   serial;
   }  Si2176_PART_INFO_CMD_REPLY_struct;

   /* PART_INFO command, CHIPREV field definition (size 4, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_CHIPREV_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_CHIPREV_MASK        0x0f
    #define Si2176_PART_INFO_RESPONSE_CHIPREV_A  1
    #define Si2176_PART_INFO_RESPONSE_CHIPREV_B  2
   /* PART_INFO command, ROMID field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_ROMID_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_ROMID_MASK        0xff
   /* PART_INFO command, PART field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_PART_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_PART_MASK        0xff
   /* PART_INFO command, PMAJOR field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_PMAJOR_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_PMAJOR_MASK        0xff
   /* PART_INFO command, PMINOR field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_PMINOR_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_PMINOR_MASK        0xff
   /* PART_INFO command, PBUILD field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_PBUILD_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_PBUILD_MASK        0xff
   /* PART_INFO command, RESERVED field definition (size 16, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_RESERVED_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_RESERVED_MASK        0xffff
   /* PART_INFO command, SERIAL field definition (size 32, lsb 0, unsigned)*/
   #define  Si2176_PART_INFO_RESPONSE_SERIAL_LSB         0
   #define  Si2176_PART_INFO_RESPONSE_SERIAL_MASK        0xffffffff

#endif /* Si2176_PART_INFO_CMD */

/* Si2176_POWER_DOWN command definition */
#define Si2176_POWER_DOWN_CMD 0x13

#ifdef    Si2176_POWER_DOWN_CMD

    typedef struct { /* Si2176_POWER_DOWN_CMD_struct */
         unsigned char   nothing;   } Si2176_POWER_DOWN_CMD_struct;


    typedef struct { /* Si2176_POWER_DOWN_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_POWER_DOWN_CMD_REPLY_struct;

#endif /* Si2176_POWER_DOWN_CMD */

/* Si2176_POWER_UP command definition */
#define Si2176_POWER_UP_CMD 0xc0

#ifdef    Si2176_POWER_UP_CMD

    typedef struct { /* Si2176_POWER_UP_CMD_struct */
     unsigned char   subcode;
     unsigned char   reserved1;
     unsigned char   reserved2;
     unsigned char   reserved3;
     unsigned char   clock_mode;
     unsigned char   clock_freq;
     unsigned char   addr_mode;
     unsigned char   func;
     unsigned char   ctsien;
     unsigned char   wake_up;
   } Si2176_POWER_UP_CMD_struct;

   /* POWER_UP command, SUBCODE field definition (size 8, lsb 0, unsigned) */
   #define  Si2176_POWER_UP_CMD_SUBCODE_LSB         0
   #define  Si2176_POWER_UP_CMD_SUBCODE_MASK        0xff
   #define  Si2176_POWER_UP_CMD_SUBCODE_MIN         5
   #define  Si2176_POWER_UP_CMD_SUBCODE_MAX         5
    #define Si2176_POWER_UP_CMD_SUBCODE_CODE  5
   /* POWER_UP command, RESERVED1 field definition (size 8, lsb 0, unsigned) */
   #define  Si2176_POWER_UP_CMD_RESERVED1_LSB         0
   #define  Si2176_POWER_UP_CMD_RESERVED1_MASK        0xff
   #define  Si2176_POWER_UP_CMD_RESERVED1_MIN         1
   #define  Si2176_POWER_UP_CMD_RESERVED1_MAX         1
    #define Si2176_POWER_UP_CMD_RESERVED1_RESERVED  1
   /* POWER_UP command, RESERVED2 field definition (size 8, lsb 0, unsigned) */
   #define  Si2176_POWER_UP_CMD_RESERVED2_LSB         0
   #define  Si2176_POWER_UP_CMD_RESERVED2_MASK        0xff
   #define  Si2176_POWER_UP_CMD_RESERVED2_MIN         0
   #define  Si2176_POWER_UP_CMD_RESERVED2_MAX         0
    #define Si2176_POWER_UP_CMD_RESERVED2_RESERVED  0
   /* POWER_UP command, RESERVED3 field definition (size 8, lsb 0, unsigned) */
   #define  Si2176_POWER_UP_CMD_RESERVED3_LSB         0
   #define  Si2176_POWER_UP_CMD_RESERVED3_MASK        0xff
   #define  Si2176_POWER_UP_CMD_RESERVED3_MIN         0
   #define  Si2176_POWER_UP_CMD_RESERVED3_MAX         0
    #define Si2176_POWER_UP_CMD_RESERVED3_RESERVED  0
   /* POWER_UP command, CLOCK_MODE field definition (size 2, lsb 0, unsigned) */
   #define  Si2176_POWER_UP_CMD_CLOCK_MODE_LSB         0
   #define  Si2176_POWER_UP_CMD_CLOCK_MODE_MASK        0x03
   #define  Si2176_POWER_UP_CMD_CLOCK_MODE_MIN         1
   #define  Si2176_POWER_UP_CMD_CLOCK_MODE_MAX         3
    #define Si2176_POWER_UP_CMD_CLOCK_MODE_EXTCLK  1
    #define Si2176_POWER_UP_CMD_CLOCK_MODE_XTAL    3
   /* POWER_UP command, CLOCK_FREQ field definition (size 2, lsb 2, unsigned) */
   #define  Si2176_POWER_UP_CMD_CLOCK_FREQ_LSB         2
   #define  Si2176_POWER_UP_CMD_CLOCK_FREQ_MASK        0x03
   #define  Si2176_POWER_UP_CMD_CLOCK_FREQ_MIN         0
   #define  Si2176_POWER_UP_CMD_CLOCK_FREQ_MAX         2
    #define Si2176_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ  2
   /* POWER_UP command, ADDR_MODE field definition (size 1, lsb 4, unsigned) */
   #define  Si2176_POWER_UP_CMD_ADDR_MODE_LSB         4
   #define  Si2176_POWER_UP_CMD_ADDR_MODE_MASK        0x01
   #define  Si2176_POWER_UP_CMD_ADDR_MODE_MIN         0
   #define  Si2176_POWER_UP_CMD_ADDR_MODE_MAX         1
    #define Si2176_POWER_UP_CMD_ADDR_MODE_CAPTURE  1
    #define Si2176_POWER_UP_CMD_ADDR_MODE_CURRENT  0
   /* POWER_UP command, FUNC field definition (size 4, lsb 0, unsigned) */
   #define  Si2176_POWER_UP_CMD_FUNC_LSB         0
   #define  Si2176_POWER_UP_CMD_FUNC_MASK        0x0f
   #define  Si2176_POWER_UP_CMD_FUNC_MIN         0
   #define  Si2176_POWER_UP_CMD_FUNC_MAX         1
    #define Si2176_POWER_UP_CMD_FUNC_BOOTLOADER  0
    #define Si2176_POWER_UP_CMD_FUNC_NORMAL      1
   /* POWER_UP command, CTSIEN field definition (size 1, lsb 7, unsigned) */
   #define  Si2176_POWER_UP_CMD_CTSIEN_LSB         7
   #define  Si2176_POWER_UP_CMD_CTSIEN_MASK        0x01
   #define  Si2176_POWER_UP_CMD_CTSIEN_MIN         0
   #define  Si2176_POWER_UP_CMD_CTSIEN_MAX         1
    #define Si2176_POWER_UP_CMD_CTSIEN_DISABLE  0
    #define Si2176_POWER_UP_CMD_CTSIEN_ENABLE   1
   /* POWER_UP command, WAKE_UP field definition (size 1, lsb 0, unsigned) */
   #define  Si2176_POWER_UP_CMD_WAKE_UP_LSB         0
   #define  Si2176_POWER_UP_CMD_WAKE_UP_MASK        0x01
   #define  Si2176_POWER_UP_CMD_WAKE_UP_MIN         1
   #define  Si2176_POWER_UP_CMD_WAKE_UP_MAX         1
    #define Si2176_POWER_UP_CMD_WAKE_UP_WAKE_UP  1

    typedef struct { /* Si2176_POWER_UP_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_POWER_UP_CMD_REPLY_struct;

#endif /* Si2176_POWER_UP_CMD */

/* Si2176_SET_PROPERTY command definition */
#define Si2176_SET_PROPERTY_CMD 0x14

#ifdef    Si2176_SET_PROPERTY_CMD

    typedef struct { /* Si2176_SET_PROPERTY_CMD_struct */
     unsigned char   reserved;
     unsigned int    prop;
     unsigned int    data;
   } Si2176_SET_PROPERTY_CMD_struct;

   /* SET_PROPERTY command, RESERVED field definition (size 8, lsb 0, unsigned) */
   #define  Si2176_SET_PROPERTY_CMD_RESERVED_LSB         0
   #define  Si2176_SET_PROPERTY_CMD_RESERVED_MASK        0xff
   #define  Si2176_SET_PROPERTY_CMD_RESERVED_MIN         0
   #define  Si2176_SET_PROPERTY_CMD_RESERVED_MAX         255.0
   /* SET_PROPERTY command, PROP field definition (size 16, lsb 0, unsigned) */
   #define  Si2176_SET_PROPERTY_CMD_PROP_LSB         0
   #define  Si2176_SET_PROPERTY_CMD_PROP_MASK        0xffff
   #define  Si2176_SET_PROPERTY_CMD_PROP_MIN         0
   #define  Si2176_SET_PROPERTY_CMD_PROP_MAX         65535
    #define Si2176_SET_PROPERTY_CMD_PROP_PROP_MIN  0
    #define Si2176_SET_PROPERTY_CMD_PROP_PROP_MAX  65535
   /* SET_PROPERTY command, DATA field definition (size 16, lsb 0, unsigned) */
   #define  Si2176_SET_PROPERTY_CMD_DATA_LSB         0
   #define  Si2176_SET_PROPERTY_CMD_DATA_MASK        0xffff
   #define  Si2176_SET_PROPERTY_CMD_DATA_MIN         0
   #define  Si2176_SET_PROPERTY_CMD_DATA_MAX         65535
    #define Si2176_SET_PROPERTY_CMD_DATA_DATA_MIN  0
    #define Si2176_SET_PROPERTY_CMD_DATA_DATA_MAX  65535

    typedef struct { /* Si2176_SET_PROPERTY_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   reserved;
      unsigned int    data;
   }  Si2176_SET_PROPERTY_CMD_REPLY_struct;

   /* SET_PROPERTY command, RESERVED field definition (size 8, lsb 0, unsigned)*/
   #define  Si2176_SET_PROPERTY_RESPONSE_RESERVED_LSB         0
   #define  Si2176_SET_PROPERTY_RESPONSE_RESERVED_MASK        0xff
    #define Si2176_SET_PROPERTY_RESPONSE_RESERVED_RESERVED_MIN  0
    #define Si2176_SET_PROPERTY_RESPONSE_RESERVED_RESERVED_MAX  0
   /* SET_PROPERTY command, DATA field definition (size 16, lsb 0, unsigned)*/
   #define  Si2176_SET_PROPERTY_RESPONSE_DATA_LSB         0
   #define  Si2176_SET_PROPERTY_RESPONSE_DATA_MASK        0xffff

#endif /* Si2176_SET_PROPERTY_CMD */

/* Si2176_STANDBY command definition */
#define Si2176_STANDBY_CMD 0x16

#ifdef    Si2176_STANDBY_CMD

    typedef struct { /* Si2176_STANDBY_CMD_struct */
         unsigned char   nothing;   } Si2176_STANDBY_CMD_struct;


    typedef struct { /* Si2176_STANDBY_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_STANDBY_CMD_REPLY_struct;

#endif /* Si2176_STANDBY_CMD */

/* Si2176_TUNER_STATUS command definition */
#define Si2176_TUNER_STATUS_CMD 0x42

#ifdef    Si2176_TUNER_STATUS_CMD

    typedef struct { /* Si2176_TUNER_STATUS_CMD_struct */
     unsigned char   intack;
   } Si2176_TUNER_STATUS_CMD_struct;

   /* TUNER_STATUS command, INTACK field definition (size 1, lsb 0, unsigned) */
   #define  Si2176_TUNER_STATUS_CMD_INTACK_LSB         0
   #define  Si2176_TUNER_STATUS_CMD_INTACK_MASK        0x01
   #define  Si2176_TUNER_STATUS_CMD_INTACK_MIN         0
   #define  Si2176_TUNER_STATUS_CMD_INTACK_MAX         1
    #define Si2176_TUNER_STATUS_CMD_INTACK_CLEAR  1
    #define Si2176_TUNER_STATUS_CMD_INTACK_OK     0

    typedef struct { /* Si2176_TUNER_STATUS_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
      unsigned char   tcint;
      unsigned char   rssilint;
      unsigned char   rssihint;
               int    vco_code;
      unsigned char   tc;
      unsigned char   rssil;
      unsigned char   rssih;
               char   rssi;
      unsigned long   freq;
      unsigned char   mode;
   }  Si2176_TUNER_STATUS_CMD_REPLY_struct;

   /* TUNER_STATUS command, TCINT field definition (size 1, lsb 0, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_TCINT_LSB         0
   #define  Si2176_TUNER_STATUS_RESPONSE_TCINT_MASK        0x01
    #define Si2176_TUNER_STATUS_RESPONSE_TCINT_CHANGED    1
    #define Si2176_TUNER_STATUS_RESPONSE_TCINT_NO_CHANGE  0
   /* TUNER_STATUS command, RSSILINT field definition (size 1, lsb 1, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSILINT_LSB         1
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSILINT_MASK        0x01
    #define Si2176_TUNER_STATUS_RESPONSE_RSSILINT_CHANGED    1
    #define Si2176_TUNER_STATUS_RESPONSE_RSSILINT_NO_CHANGE  0
   /* TUNER_STATUS command, RSSIHINT field definition (size 1, lsb 2, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_LSB         2
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_MASK        0x01
    #define Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_CHANGED    1
    #define Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_NO_CHANGE  0
   /* TUNER_STATUS command, VCO_CODE field definition (size 16, lsb 0, signed)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_LSB         0
   #define  Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_MASK        0xffff
   #define  Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT       16
   /* TUNER_STATUS command, TC field definition (size 1, lsb 0, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_TC_LSB         0
   #define  Si2176_TUNER_STATUS_RESPONSE_TC_MASK        0x01
    #define Si2176_TUNER_STATUS_RESPONSE_TC_BUSY  0
    #define Si2176_TUNER_STATUS_RESPONSE_TC_DONE  1
   /* TUNER_STATUS command, RSSIL field definition (size 1, lsb 1, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSIL_LSB         1
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSIL_MASK        0x01
    #define Si2176_TUNER_STATUS_RESPONSE_RSSIL_LOW  1
    #define Si2176_TUNER_STATUS_RESPONSE_RSSIL_OK   0
   /* TUNER_STATUS command, RSSIH field definition (size 1, lsb 2, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSIH_LSB         2
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSIH_MASK        0x01
    #define Si2176_TUNER_STATUS_RESPONSE_RSSIH_HIGH  1
    #define Si2176_TUNER_STATUS_RESPONSE_RSSIH_OK    0
   /* TUNER_STATUS command, RSSI field definition (size 8, lsb 0, signed)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSI_LSB         0
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSI_MASK        0xff
   #define  Si2176_TUNER_STATUS_RESPONSE_RSSI_SHIFT       24
   /* TUNER_STATUS command, FREQ field definition (size 32, lsb 0, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_FREQ_LSB         0
   #define  Si2176_TUNER_STATUS_RESPONSE_FREQ_MASK        0xffffffff
   /* TUNER_STATUS command, MODE field definition (size 1, lsb 0, unsigned)*/
   #define  Si2176_TUNER_STATUS_RESPONSE_MODE_LSB         0
   #define  Si2176_TUNER_STATUS_RESPONSE_MODE_MASK        0x01
    #define Si2176_TUNER_STATUS_RESPONSE_MODE_ATV  1
    #define Si2176_TUNER_STATUS_RESPONSE_MODE_DTV  0

#endif /* Si2176_TUNER_STATUS_CMD */

/* Si2176_TUNER_TUNE_FREQ command definition */
#define Si2176_TUNER_TUNE_FREQ_CMD 0x41

#ifdef    Si2176_TUNER_TUNE_FREQ_CMD

    typedef struct { /* Si2176_TUNER_TUNE_FREQ_CMD_struct */
     unsigned char   mode;
     unsigned long   freq;
   } Si2176_TUNER_TUNE_FREQ_CMD_struct;

   /* TUNER_TUNE_FREQ command, MODE field definition (size 1, lsb 0, unsigned) */
   #define  Si2176_TUNER_TUNE_FREQ_CMD_MODE_LSB         0
   #define  Si2176_TUNER_TUNE_FREQ_CMD_MODE_MASK        0x01
   #define  Si2176_TUNER_TUNE_FREQ_CMD_MODE_MIN         0
   #define  Si2176_TUNER_TUNE_FREQ_CMD_MODE_MAX         1
    #define Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV  1
    #define Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV  0
   /* TUNER_TUNE_FREQ command, FREQ field definition (size 32, lsb 0, unsigned) */
   #define  Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB         0
   #define  Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK        0xffffffff
   #define  Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MIN         43000000
   #define  Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MAX         1002000000
    #define Si2176_TUNER_TUNE_FREQ_CMD_FREQ_FREQ_MIN  43000000
    #define Si2176_TUNER_TUNE_FREQ_CMD_FREQ_FREQ_MAX  1002000000

    typedef struct { /* Si2176_TUNER_TUNE_FREQ_CMD_REPLY_struct */
       Si2176_COMMON_REPLY_struct * STATUS;
   }  Si2176_TUNER_TUNE_FREQ_CMD_REPLY_struct;

#endif /* Si2176_TUNER_TUNE_FREQ_CMD */

/* _commands_defines_insertion_point */

/* _commands_struct_insertion_start */

  /* --------------------------------------------*/
  /* COMMANDS STRUCT                             */
  /* This is used to store all command fields    */
  /* --------------------------------------------*/
  typedef union { /* Si2176_CmdObj union */
    #ifdef    Si2176_AGC_OVERRIDE_CMD
              Si2176_AGC_OVERRIDE_CMD_struct               agc_override;
    #endif /* Si2176_AGC_OVERRIDE_CMD */
    #ifdef    Si2176_ATV_RESTART_CMD
              Si2176_ATV_RESTART_CMD_struct                atv_restart;
    #endif /* Si2176_ATV_RESTART_CMD */
    #ifdef    Si2176_ATV_STATUS_CMD
              Si2176_ATV_STATUS_CMD_struct                 atv_status;
    #endif /* Si2176_ATV_STATUS_CMD */
    #ifdef    Si2176_CONFIG_PINS_CMD
              Si2176_CONFIG_PINS_CMD_struct                config_pins;
    #endif /* Si2176_CONFIG_PINS_CMD */
    #ifdef    Si2176_DTV_RESTART_CMD
              Si2176_DTV_RESTART_CMD_struct                dtv_restart;
    #endif /* Si2176_DTV_RESTART_CMD */
    #ifdef    Si2176_DTV_STATUS_CMD
              Si2176_DTV_STATUS_CMD_struct                 dtv_status;
    #endif /* Si2176_DTV_STATUS_CMD */
    #ifdef    Si2176_EXIT_BOOTLOADER_CMD
              Si2176_EXIT_BOOTLOADER_CMD_struct            exit_bootloader;
    #endif /* Si2176_EXIT_BOOTLOADER_CMD */
    #ifdef    Si2176_FINE_TUNE_CMD
              Si2176_FINE_TUNE_CMD_struct                  fine_tune;
    #endif /* Si2176_FINE_TUNE_CMD */
    #ifdef    Si2176_GET_PROPERTY_CMD
              Si2176_GET_PROPERTY_CMD_struct               get_property;
    #endif /* Si2176_GET_PROPERTY_CMD */
    #ifdef    Si2176_GET_REV_CMD
              Si2176_GET_REV_CMD_struct                    get_rev;
    #endif /* Si2176_GET_REV_CMD */
    #ifdef    Si2176_PART_INFO_CMD
              Si2176_PART_INFO_CMD_struct                  part_info;
    #endif /* Si2176_PART_INFO_CMD */
    #ifdef    Si2176_POWER_DOWN_CMD
              Si2176_POWER_DOWN_CMD_struct                 power_down;
    #endif /* Si2176_POWER_DOWN_CMD */
    #ifdef    Si2176_POWER_UP_CMD
              Si2176_POWER_UP_CMD_struct                   power_up;
    #endif /* Si2176_POWER_UP_CMD */
    #ifdef    Si2176_SET_PROPERTY_CMD
              Si2176_SET_PROPERTY_CMD_struct               set_property;
    #endif /* Si2176_SET_PROPERTY_CMD */
    #ifdef    Si2176_STANDBY_CMD
              Si2176_STANDBY_CMD_struct                    standby;
    #endif /* Si2176_STANDBY_CMD */
    #ifdef    Si2176_TUNER_STATUS_CMD
              Si2176_TUNER_STATUS_CMD_struct               tuner_status;
    #endif /* Si2176_TUNER_STATUS_CMD */
    #ifdef    Si2176_TUNER_TUNE_FREQ_CMD
              Si2176_TUNER_TUNE_FREQ_CMD_struct            tuner_tune_freq;
    #endif /* Si2176_TUNER_TUNE_FREQ_CMD */
  } Si2176_CmdObj;
/* _commands_struct_insertion_point */

/* _commands_reply_struct_insertion_start */

  /* --------------------------------------------*/
  /* COMMANDS REPLY STRUCT                       */
  /* This stores all command reply fields        */
  /* --------------------------------------------*/
  typedef struct { /* Si2176_CmdReplyObj struct */
    #ifdef    Si2176_AGC_OVERRIDE_CMD
              Si2176_AGC_OVERRIDE_CMD_REPLY_struct               agc_override;
    #endif /* Si2176_AGC_OVERRIDE_CMD */
    #ifdef    Si2176_ATV_RESTART_CMD
              Si2176_ATV_RESTART_CMD_REPLY_struct                atv_restart;
    #endif /* Si2176_ATV_RESTART_CMD */
    #ifdef    Si2176_ATV_STATUS_CMD
              Si2176_ATV_STATUS_CMD_REPLY_struct                 atv_status;
    #endif /* Si2176_ATV_STATUS_CMD */
    #ifdef    Si2176_CONFIG_PINS_CMD
              Si2176_CONFIG_PINS_CMD_REPLY_struct                config_pins;
    #endif /* Si2176_CONFIG_PINS_CMD */
    #ifdef    Si2176_DTV_RESTART_CMD
              Si2176_DTV_RESTART_CMD_REPLY_struct                dtv_restart;
    #endif /* Si2176_DTV_RESTART_CMD */
    #ifdef    Si2176_DTV_STATUS_CMD
              Si2176_DTV_STATUS_CMD_REPLY_struct                 dtv_status;
    #endif /* Si2176_DTV_STATUS_CMD */
    #ifdef    Si2176_EXIT_BOOTLOADER_CMD
              Si2176_EXIT_BOOTLOADER_CMD_REPLY_struct            exit_bootloader;
    #endif /* Si2176_EXIT_BOOTLOADER_CMD */
    #ifdef    Si2176_FINE_TUNE_CMD
              Si2176_FINE_TUNE_CMD_REPLY_struct                  fine_tune;
    #endif /* Si2176_FINE_TUNE_CMD */
    #ifdef    Si2176_GET_PROPERTY_CMD
              Si2176_GET_PROPERTY_CMD_REPLY_struct               get_property;
    #endif /* Si2176_GET_PROPERTY_CMD */
    #ifdef    Si2176_GET_REV_CMD
              Si2176_GET_REV_CMD_REPLY_struct                    get_rev;
    #endif /* Si2176_GET_REV_CMD */
    #ifdef    Si2176_PART_INFO_CMD
              Si2176_PART_INFO_CMD_REPLY_struct                  part_info;
    #endif /* Si2176_PART_INFO_CMD */
    #ifdef    Si2176_POWER_DOWN_CMD
              Si2176_POWER_DOWN_CMD_REPLY_struct                 power_down;
    #endif /* Si2176_POWER_DOWN_CMD */
    #ifdef    Si2176_POWER_UP_CMD
              Si2176_POWER_UP_CMD_REPLY_struct                   power_up;
    #endif /* Si2176_POWER_UP_CMD */
    #ifdef    Si2176_SET_PROPERTY_CMD
              Si2176_SET_PROPERTY_CMD_REPLY_struct               set_property;
    #endif /* Si2176_SET_PROPERTY_CMD */
    #ifdef    Si2176_STANDBY_CMD
              Si2176_STANDBY_CMD_REPLY_struct                    standby;
    #endif /* Si2176_STANDBY_CMD */
    #ifdef    Si2176_TUNER_STATUS_CMD
              Si2176_TUNER_STATUS_CMD_REPLY_struct               tuner_status;
    #endif /* Si2176_TUNER_STATUS_CMD */
    #ifdef    Si2176_TUNER_TUNE_FREQ_CMD
              Si2176_TUNER_TUNE_FREQ_CMD_REPLY_struct            tuner_tune_freq;
    #endif /* Si2176_TUNER_TUNE_FREQ_CMD */
  } Si2176_CmdReplyObj;
/* _commands_reply_struct_insertion_point */

#ifdef    Si2176_COMMAND_PROTOTYPES




   unsigned char  Si2176_CurrentResponseStatus (Si2176_COMMON_REPLY_struct *ret, unsigned char ptDataBuffer);
   unsigned char  Si2176_pollForCTS            (L1_Si2176_Context *context, unsigned char waitForCTS);
   unsigned char  Si2176_pollForResponse       (L1_Si2176_Context *context, unsigned char waitForResponse, unsigned int nbBytes, unsigned char *pByteBuffer, Si2176_COMMON_REPLY_struct *status);

/* _commands_prototypes_insertion_start */
#ifdef    Si2176_AGC_OVERRIDE_CMD
 unsigned char  Si2176_L1_AGC_OVERRIDE              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   force_max_gain,
                                                                                      unsigned char   force_top_gain,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_AGC_OVERRIDE_CMD */
#ifdef    Si2176_ATV_RESTART_CMD
 unsigned char  Si2176_L1_ATV_RESTART               (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   mode,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_ATV_RESTART_CMD */
#ifdef    Si2176_ATV_STATUS_CMD
 unsigned char  Si2176_L1_ATV_STATUS                (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   intack,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_ATV_STATUS_CMD */
#ifdef    Si2176_CONFIG_PINS_CMD
 unsigned char  Si2176_L1_CONFIG_PINS               (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   gpio1_mode,
                                                                                      unsigned char   gpio1_read,
                                                                                      unsigned char   gpio2_mode,
                                                                                      unsigned char   gpio2_read,
                                                                                      unsigned char   gpio3_mode,
                                                                                      unsigned char   gpio3_read,
                                                                                      unsigned char   bclk1_mode,
                                                                                      unsigned char   bclk1_read,
                                                                                      unsigned char   xout_mode,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_CONFIG_PINS_CMD */
#ifdef    Si2176_DTV_RESTART_CMD
 unsigned char  Si2176_L1_DTV_RESTART               (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_DTV_RESTART_CMD */
#ifdef    Si2176_DTV_STATUS_CMD
 unsigned char  Si2176_L1_DTV_STATUS                (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   intack,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_DTV_STATUS_CMD */
#ifdef    Si2176_EXIT_BOOTLOADER_CMD
 unsigned char  Si2176_L1_EXIT_BOOTLOADER           (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   func,
                                                                                      unsigned char   ctsien,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_EXIT_BOOTLOADER_CMD */
#ifdef    Si2176_FINE_TUNE_CMD
 unsigned char  Si2176_L1_FINE_TUNE                 (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   reserved,
                                                                                                int   offset_500hz,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_FINE_TUNE_CMD */
#ifdef    Si2176_GET_PROPERTY_CMD
 unsigned char  Si2176_L1_GET_PROPERTY              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   reserved,
                                                                                      unsigned int    prop,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_GET_PROPERTY_CMD */
#ifdef    Si2176_GET_REV_CMD
 unsigned char  Si2176_L1_GET_REV                   (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_GET_REV_CMD */
#ifdef    Si2176_PART_INFO_CMD
 unsigned char  Si2176_L1_PART_INFO                 (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_PART_INFO_CMD */
#ifdef    Si2176_POWER_DOWN_CMD
 unsigned char  Si2176_L1_POWER_DOWN                (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_POWER_DOWN_CMD */
#ifdef    Si2176_POWER_UP_CMD
 unsigned char  Si2176_L1_POWER_UP                  (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   subcode,
                                                                                      unsigned char   reserved1,
                                                                                      unsigned char   reserved2,
                                                                                      unsigned char   reserved3,
                                                                                      unsigned char   clock_mode,
                                                                                      unsigned char   clock_freq,
                                                                                      unsigned char   addr_mode,
                                                                                      unsigned char   func,
                                                                                      unsigned char   ctsien,
                                                                                      unsigned char   wake_up,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_POWER_UP_CMD */
#ifdef    Si2176_SET_PROPERTY_CMD
 unsigned char  Si2176_L1_SET_PROPERTY              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   reserved,
                                                                                      unsigned int    prop,
                                                                                      unsigned int    data,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_SET_PROPERTY_CMD */
#ifdef    Si2176_STANDBY_CMD
 unsigned char  Si2176_L1_STANDBY                   (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_STANDBY_CMD */
#ifdef    Si2176_TUNER_STATUS_CMD
 unsigned char  Si2176_L1_TUNER_STATUS              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   intack,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_TUNER_STATUS_CMD */
#ifdef    Si2176_TUNER_TUNE_FREQ_CMD
 unsigned char  Si2176_L1_TUNER_TUNE_FREQ           (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse, 
                                                                                      unsigned char   mode,
                                                                                      unsigned long   freq,
                                                                                      Si2176_CmdReplyObj *rsp);
#endif /* Si2176_TUNER_TUNE_FREQ_CMD */
/* _commands_prototypes_insertion_point */

   unsigned char  Si2176_L1_SendCommand2       (L1_Si2176_Context *api, int cmd, Si2176_CmdObj *c, unsigned char wait_for_cts, unsigned char wait_for_response, Si2176_CmdReplyObj *rsp);

#ifdef    Si2176_GET_COMMAND_STRINGS
   unsigned char    Si2176_L1_GetCommandResponseString(L1_Si2176_Context *api, int cmd, Si2176_CmdReplyObj *rsp, char **separator, char *msg);
#endif /* Si2176_GET_COMMAND_STRINGS */


#endif /* Si2176_COMMAND_PROTOTYPES */
#endif /* Si2176_COMMANDS_H */
/* End of template (2011 January 24 at 13:47) */





