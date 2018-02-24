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
// "Copyright (c) 2009, Xceive Corporation <info@xceive.com>
//
// Permission to use, copy, and/or modify this software, only with Xceive ICs,
// for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all source code
// copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE."
//
// < This is a interface for XC5000 TV tuner commands>
//
// Filename : xc5000_control.cpp
// Generated : 1/22/2007 4:41:24 PM
//

#include "xc5000_control.h"

#define XC5000_I2C_ADDR   0xC2

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


/* *************************************************************** */
/* *************************************************************** */
/*                                                                 */
/*              CODE PROVIDED BY XCEIVE                            */
/*                                                                 */
/* *************************************************************** */
/* *************************************************************** */
int xc_write_reg(struct xc5000_state *st, unsigned short int regAddr, unsigned short int i2cData)
{
  unsigned char buf[4];
  int WatchDogTimer = 5;
  int result;
  uint16_t r;
  buf[0] = (regAddr >> 8) & 0xFF;
  buf[1] = regAddr & 0xFF;
  buf[2] = (i2cData >> 8) & 0xFF;
  buf[3] = i2cData & 0xFF;
  result = xc_send_i2c_data(st, XC5000_I2C_ADDR, buf, 4);

  if ( result == XC_RESULT_SUCCESS)
  {
    // wait for busy flag to clear
    while ((WatchDogTimer > 0) && (result == XC_RESULT_SUCCESS))
    {
      if (xc_read_reg(st, XREG_BUSY, &r) == XC_RESULT_SUCCESS && r == 0)
          break;
      xc_wait(100);     // wait 5 ms
      WatchDogTimer--;
    }
  }
  if (WatchDogTimer < 0)
  {
    result = XC_RESULT_I2C_WRITE_FAILURE;
  }
  return result;
}


int xc_load_i2c_sequence(struct xc5000_state *st, unsigned char i2c_sequence[])
{
  int i,nbytes_to_send,result;
  unsigned int length, pos, ind;
  unsigned char buf[XC_MAX_I2C_WRITE_LENGTH];

  ind=0;
  dbgpl(&xc5000_dbg, __FUNCTION__ );
  while ((i2c_sequence[ind]!=0xFF) || (i2c_sequence[ind+1]!=0xFF))
  {
    length = i2c_sequence[ind]* 256 + i2c_sequence[ind+1];
    if (length==0x0000)
    {
      //this is in fact a RESET command
      result = st->cfg->reset(st->fe);
      ind += 2;
      if (result!=XC_RESULT_SUCCESS)
        return result;
    }
    else if (length & 0x8000)
    {
      //this is in fact a WAIT command
      xc_wait(length & 0x7FFF);
      ind += 2;
    }
    else
    {
      //send i2c data whilst ensuring individual transactions do
      //not exceed XC_MAX_I2C_WRITE_LENGTH bytes
      ind += 2;
      buf[0] = i2c_sequence[ind];
      buf[1] = i2c_sequence[ind + 1];
      pos = 2;
      while (pos < length)
      {
        if ((length - pos) > XC_MAX_I2C_WRITE_LENGTH - 2)
        {
          nbytes_to_send = XC_MAX_I2C_WRITE_LENGTH;
        }
        else
        {
          nbytes_to_send = (length - pos + 2);
        }
        for (i=2; i<nbytes_to_send; i++)
        {
          buf[i] = i2c_sequence[ind + pos + i - 2];
        }
        result = xc_send_i2c_data(st, XC5000_I2C_ADDR, buf, nbytes_to_send);

        if (result!=XC_RESULT_SUCCESS)
          return result;

        pos += nbytes_to_send - 2;
      }
      ind += length;
    }
  }
  return XC_RESULT_SUCCESS;
}

int xc_initialize(struct xc5000_state *st, XC_TV_STANDARD* new_tv_mode_ptr, XC_CHANNEL_MAP* new_channel_map_ptr)
{
    int result;
    int std_firmware_changed = (new_tv_mode_ptr != st->current_tv_mode_ptr );

    // if base firmware has changed, then do hardware reset and reload base
    // firmware file
    if (! st->base_firmware_downloaded)
    {
       result = st->cfg->reset(st->fe);
       if (result!=XC_RESULT_SUCCESS)
           return result;

       result = xc_load_i2c_sequence(st, st->firmware_ptr);

       if (result!=XC_RESULT_SUCCESS)
           return result;
       st->base_firmware_downloaded = 1;

       xc_write_reg(st, XREG_INIT, 0);

       std_firmware_changed = 1;
    }

    // if standard-specific firmware has changed then reload standard-specific firmware file
    if ( std_firmware_changed ) {

        st->current_tv_mode_ptr = new_tv_mode_ptr;
        st->current_channel_map_ptr = new_channel_map_ptr;

        xc_set_tv_standard(st, new_tv_mode_ptr);

        //do not return error if channel is incorrect...
        xc_set_channel(st, st->current_IF_Freq_khz, st->current_channel_ptr );
        xc_wait(30);                                                     // wait 30ms
    }

    return XC_RESULT_SUCCESS;
}

int xc_set_tv_standard(struct xc5000_state *st, XC_TV_STANDARD* tv_mode_ptr)
{
  int returnStatus = xc_write_reg(st, XREG_VIDEO_MODE, tv_mode_ptr->VideoMode);
  if (returnStatus == XC_RESULT_SUCCESS)
    returnStatus = xc_write_reg(st, XREG_AUDIO_MODE, tv_mode_ptr->AudioMode);
  return returnStatus;
}

int xc_set_rf_frequency(struct xc5000_state *st, long frequency_in_hz)
{
  unsigned int frequency_code;
  if ((frequency_in_hz>1023000000) || (frequency_in_hz<1000000))
    return XC_RESULT_OUT_OF_RANGE;

  frequency_code = (unsigned int)(frequency_in_hz / 15625L);
  return xc_write_reg(st, XREG_RF_FREQ ,frequency_code);
}

int xc_FineTune_RF_frequency(struct xc5000_state *st, int32_t frequency_in_hz)
{
  unsigned int frequency_code;
  if ((frequency_in_hz>1023000000) || (frequency_in_hz<1000000))
    return XC_RESULT_OUT_OF_RANGE;

  frequency_code = (unsigned int)(frequency_in_hz / 15625L);
  return xc_write_reg(st, XREG_FINERFFREQ ,frequency_code);
}

int xc_set_if_frequency(struct xc5000_state *st, long frequency_in_hz)
{
  unsigned int frequency_code = ( (frequency_in_hz/1000) * 1024)/1000;
  return xc_write_reg(st, XREG_IF_OUT ,frequency_code);
}

int xc_set_channel(struct xc5000_state *st, long if_freq_khz, XC_CHANNEL * channel_ptr)
{
    long  rf_freq_khz;

    if ( channel_ptr != NULL )
    {
      rf_freq_khz = channel_ptr->frequency *250/16;            // convert from Mhz to Khz

      xc_set_if_frequency(st, if_freq_khz*1000);           // Set IF out Freq: base on SCode, DCode

      return xc_FineTune_RF_frequency(st, rf_freq_khz*1000 );      // Xc5000 change Freq;
    }
  return XC_RESULT_OUT_OF_RANGE;
}

#if 0
int xc_set_Xtal_frequency(long xtalFreqInKHz)
{
  unsigned int xtalRatio = (32000 * 0x8000)/xtalFreqInKHz;
  return xc_write_reg(XREG_XTALFREQ ,xtalRatio);
}
#endif

int xc_set_rf_mode(struct xc5000_state *st, unsigned short int SourceType)
{
  return xc_write_reg(st, XREG_SIGNALSOURCE, SourceType);
}

#if 0
int xc_set_DDIMode(struct xc5000_state *st, unsigned short int ddimode)
{
  return xc_write_reg(st, XREG_DDIMODE ,ddimode);
}
#endif

int xc_shutdown(struct xc5000_state *st)
{
  st->base_firmware_downloaded = 0;
  st->current_tv_mode_ptr = 0;
  return xc_write_reg(st, XREG_POWER_DOWN, 0);
}

#if 0
int xc_get_ADC_Envelope(struct xc5000_state *st, unsigned short int *adc_envelope)
{
  return xc_read_reg(st, XREG_ADC_ENV, adc_envelope);
}
#endif

// Obtain current frequency error
// Refer to datasheet for values.
int xc_get_frequency_error(struct xc5000_state *st, int32_t *frequency_error_hz)
{
  unsigned short int data;
  short int signed_data;
  int result;

  result = xc_read_reg(st, XREG_FREQ_ERROR, &data);
  if (result)
    return result;

  signed_data = (short int)data;
  (*frequency_error_hz) = (signed_data * 156250)/10;

  return 0;
}

// Obtain current lock status.
// Refer to datasheet for values.
int xc_get_lock_status(struct xc5000_state *st, unsigned short int *lock_status)
{
  return xc_read_reg(st, XREG_LOCK, lock_status);
}

// Obtain Version codes.
// Refer to datasheet for values.
int xc_get_version(struct xc5000_state *st, unsigned char* hw_majorversion,
                       unsigned char* hw_minorversion,
                       unsigned char* fw_majorversion,
                       unsigned char* fw_minorversion)
{
  unsigned short int data;
  int result;

  result = xc_read_reg(st, XREG_VERSION, &data);
  if (result)
    return result;

    (*hw_majorversion) = (data>>12) & 0x0F;
    (*hw_minorversion) = (data>>8) & 0x0F;
    (*fw_majorversion) = (data>>4) & 0x0F;
    (*fw_minorversion) = (data) & 0x0F;

  return 0;
}

// Obtain Product ID.
// Refer to datasheet for values.
int xc_get_product_id(struct xc5000_state *st, unsigned short int *product_id)
{
  return xc_read_reg(st, XREG_PRODUCT_ID, product_id);
}

// Obtain current horizontal video frequency.
// Refer to datasheet for values.
int xc_get_hsync_freq(struct xc5000_state *st, int *hsync_freq_hz)
{
  unsigned short int regData;
  int result;

  result = xc_read_reg(st, XREG_HSYNC_FREQ, &regData);
  if (result)
    return result;
  (*hsync_freq_hz) = ((regData & 0x0fff) * 763)/100;
  return result;
}

 // Obtain current number of lines per frame.
 // Refer to datasheet for values.
int xc_get_frame_lines(struct xc5000_state *st, unsigned short int *frame_lines)
{
  return xc_read_reg(st, XREG_FRAME_LINES, frame_lines);
}

// Obtain current video signal quality.
// Refer to datasheet for values.
int xc_get_quality(struct xc5000_state *st, unsigned short int *quality)
{
  return xc_read_reg(st, XREG_QUALITY, quality);
}

// Get the Clock Freq of the tuner
#if 0
int xc_get_clock_freq(unsigned short int *clock_freq)
{
  return xc_read_reg(XREG_CLOCKFREQ, clock_freq);
}
#endif

#if 0
unsigned short int WaitForLock()
{
  unsigned short int lockState = 0;
  int watchDogCount = 40;
  while ((lockState == 0) && (watchDogCount > 0))
  {
    xc_get_lock_status(&lockState);
    if (lockState != 1)
    {
      xc_wait(5);      // wait 5 ms
      watchDogCount--;
    }
  }
  return lockState;
}
#endif

#if 0
bool xc_scan_channel(long chnl_freq)
{
  long freq_error, min_freq_error, max_freq_error;
  unsigned short int quality, max_quality;
  int res;
  bool  chnl_found = false;

  if (xc_set_rf_frequency(chnl_freq) != XC_RESULT_SUCCESS)
    return false;
  if (WaitForLock()== 1)
  {
    chnl_found = true;
    //add new channel
  }
  return chnl_found;
}
#endif

#if 0
int xc_Write_Seek_Frequency(int numberOfSeek, short int seekFreqcies[])
{
  // each unit of seekFreqcies is 15.625 KHz
  int seekIndex, commStatus = 0;
  commStatus = xc_write_reg(XREG_SEEK_MODE, numberOfSeek << 4);
  for (seekIndex=0; seekIndex < numberOfSeek; seekIndex++)
  {
    commStatus |= xc_write_reg(XREG_SEEK_MODE, seekFreqcies[seekIndex] << 4 + seekIndex + 1);
  }
  return commStatus;
}
#endif

// change the channle, like xc_set_channel
void xc_channel_tuning(struct xc5000_state *st, long rf_freq_khz, int if_freq_khz )
{
  xc_set_if_frequency(st, if_freq_khz * 1000);
  xc_FineTune_RF_frequency(st, rf_freq_khz * 1000);
  xc_wait(10);                             // wait to make sure the channel is stable!
}
