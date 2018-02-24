//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
// < C header file for control of the XC5000 via the i2c interface>
// Copyright 2007 Xceive Inc.  This program is free software: you can
// redistribute it and/or modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation, either version 3 of
// the License or, at your option, any later version. This program is
// distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details. You
// should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/."

//
// C header file for control of the XC5000 via the i2c interface.
//
// Filename : xc5000_control.h
// Generated : 1/22/2007 4:41:24 PM
//
// (c) 2007, Xceive Corporation
//
//
// Disclaimer:
//
// Xceive assumes no responsibility for any consequences arising from the use
// of this computer code, nor from any infringement of patents or the rights of
// third parties that may result from its use. No license is granted by
// implication or otherwise under any patent or other rights of Xceive. The
// customer is responsible for assuring that proper design and operating
// safeguards are observed to minimize inherent and procedural hazards. Xceive
// assumes no responsibility for applications assistance or customer product
// design.
// The present computer code is not authorized for use in medical, life-support
// equipment, or any other application involving a potential risk of severe
// property or environmental damage, personal injury, or death without prior
// express written approval of Xceive.  Any such use is understood to be
// entirely at the user's risk.
//
//

#ifndef __XC5000_CONTROL_H
#define __XC5000_CONTROL_H

/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

#define XC_MAX_I2C_WRITE_LENGTH                     64

#define XC_RESULT_SUCCESS                           0
#define XC_RESULT_RESET_FAILURE                     1
#define XC_RESULT_I2C_WRITE_FAILURE                 2
#define XC_RESULT_I2C_READ_FAILURE                  3
#define XC_RESULT_OUT_OF_RANGE                      5

/* *********************************************************************** */
/* Type Declarations                                                       */
/* *********************************************************************** */

/*
   This represents an I2C firmware file encoded as a string of unsigned char.
   Format is as follows:

   char[0  ]=len0_MSB  -> len = len_MSB * 256 + len_LSB
   char[1  ]=len0_LSB  -> length of first write transaction
   char[2  ]=data0 -> first byte to be sent
   char[3  ]=data1
   char[4  ]=data2
   char[   ]=...
   char[M  ]=dataN  -> last byte to be sent
   char[M+1]=len1_MSB  -> len = len_MSB * 256 + len_LSB
   char[M+2]=len1_LSB  -> length of second write transaction
   char[M+3]=data0
   char[M+4]=data1
   ...
   etc.

   The [len] value should be interpreted as follows:

   len= len_MSB _ len_LSB
   len=1111_1111_1111_1111   : End of I2C_SEQUENCE
   len=0000_0000_0000_0000   : Reset command: Do hardware reset
   len=0NNN_NNNN_NNNN_NNNN   : Normal transaction: number of bytes = {1:32767)
   len=1WWW_WWWW_WWWW_WWWW   : Wait command: wait for {1:32767} ms

   For the RESET and WAIT commands, the two following bytes will contain
   immediately the length of the following transaction.

*/

typedef struct {
    char *            identifier;
    unsigned int      frequency;
    unsigned char     dcode;
} XC_CHANNEL;

typedef struct {
    char        *MapType;
    int         nb_channels;
    XC_CHANNEL  *channels;
} XC_CHANNEL_MAP;


typedef struct {
  char *Name;
  unsigned short AudioMode;
  unsigned short VideoMode;
} XC_TV_STANDARD;

#define XREG_INIT         0x00
#define XREG_VIDEO_MODE   0x01
#define XREG_AUDIO_MODE   0x02
#define XREG_RF_FREQ      0x03
#define XREG_D_CODE       0x04
#define XREG_IF_OUT       0x05
#define XREG_SEEK_MODE    0x07
#define XREG_POWER_DOWN   0x0A
#define XREG_SIGNALSOURCE 0x0D
#define XREG_SMOOTHEDCVBS 0x0E
#define XREG_XTALFREQ     0x0F
#define XREG_FINERFFREQ   0x10
#define XREG_DDIMODE      0x11

#define XREG_ADC_ENV      0x00
#define XREG_QUALITY      0x01
#define XREG_FRAME_LINES  0x02
#define XREG_HSYNC_FREQ   0x03
#define XREG_LOCK         0x04
#define XREG_FREQ_ERROR   0x05
#define XREG_SNR          0x06
#define XREG_VERSION      0x07
#define XREG_PRODUCT_ID   0x08
#define XREG_BUSY         0x09
#define XREG_CLOCKFREQ    0x10

struct xc5000_state;

int xc_write_reg(struct xc5000_state *st, unsigned short int regAddr, unsigned short int i2cData);

// Download firmware
int xc_load_i2c_sequence(struct xc5000_state *, unsigned char i2c_sequence[]);

// Perform calibration and initialize default parameter
int xc_initialize(struct xc5000_state *, XC_TV_STANDARD * new_tv_mode_ptr, XC_CHANNEL_MAP* new_channel_map_ptr);

// Initialize device according to supplied tv mode.
int xc_set_tv_standard(struct xc5000_state *, XC_TV_STANDARD * tv_mode_ptr);

int xc_set_rf_frequency(struct xc5000_state *, long frequency_in_hz);

int xc_FineTune_RF_frequency(struct xc5000_state *st, int32_t frequency_in_hz);

int xc_set_if_frequency(struct xc5000_state *st, long frequency_in_hz);

// to set the TV channel.
int xc_set_channel(struct xc5000_state *st, long if_freq_khz, XC_CHANNEL * channel_ptr);

int xc_set_rf_mode(struct xc5000_state *st, unsigned short int SourceType);

// set crystal frequency, input value is KHz
int xc_set_Xtal_frequency(long xtalFreqInKHz);

int xc_set_DDIMode(unsigned short int ddimode);

// Power-down device.
int xc_shutdown(struct xc5000_state *st);

// Get ADC envelope value.
int xc_get_ADC_Envelope(unsigned short int *adc_envelope);

// Get current frequency error.
int xc_get_frequency_error(struct xc5000_state *st, int32_t *frequency_error_hz);

// Get lock status.
int xc_get_lock_status(struct xc5000_state *st, unsigned short int *lock_status);

// Get device version information.
int xc_get_version(struct xc5000_state *st, unsigned char* hw_majorversion,
                       unsigned char* hw_minorversion,
                       unsigned char* fw_majorversion,
                       unsigned char* fw_minorversion);

// Get device product ID.
int xc_get_product_id(struct xc5000_state *, unsigned short int *product_id);

// Get horizontal sync frequency.
int xc_get_hsync_freq(struct xc5000_state *st, int *hsync_freq_hz);

// Get number of lines per frame.
int xc_get_frame_lines(struct xc5000_state *st, unsigned short int *frame_lines);

// Get quality estimate.
int xc_get_quality(struct xc5000_state *st, unsigned short int *quality);

// Get the Clock Freq of the tuner
int xc_get_clock_freq(unsigned short int *clock_freq);

// tune a channel and return the lock status
int xc_scan_channel(long chnl_freq);

int xc_Write_Seek_Frequency(int numberOfSeek, short int seekFreqcies[]);

// change the channle, like xc_set_channel
void xc_channel_tuning(struct xc5000_state *, long rf_freq_khz, int if_freq_khz );


#endif


