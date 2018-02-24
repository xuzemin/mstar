/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmiiioctl.h
**	
** 
*******************************************************************************/

#ifndef _NMI_IOCTL_H_
#define _NMI_IOCTL_H_

#include "nmitypes.h"
#include "nmicmndefs.h"
#include "nm131.h"

/******************************************************************************
**
**	NMI IO Return Code 
**
*******************************************************************************/

typedef enum {
	NMI_S_OK = 0,
	NMI_E_FAIL = -1,

	NMI_E_BUS_LOAD = -100,
	NMI_E_BUS_INIT,
	NMI_E_BUS_WRITE,
	NMI_E_BUS_READ,

	NMI_E_CHIP_INIT = -200,

	
} tNmiRetCode;

/******************************************************************************
**
**	Tuner Board Type 
**
*******************************************************************************/

typedef enum {
	EVAL_BOARD = 1,
} tNmiBoard;

/******************************************************************************
**
**	Tuner Interfaces 
**
*******************************************************************************/
#define NMI_DRV_INIT						0x10001000

typedef struct {
	uint8_t						i2c_adr;
	uint32_t					xo; /* in MHz. */
	int							ldobypass;
	int                         init_bus_only;
	int                         xo_out_en; /* Force XO_OUT to be enabled all the time. */
} tTnrInit;

#define NMI_DRV_DEINIT						0x10001001
#define NMI_DRV_GET_CHIPID			0x10001002
#define NMI_DRV_RW_DIR					0x10001003
#define NMI_DRV_RF_RW_DIR				0x10001004
typedef struct
{
	int 			dir;
	uint32_t 	adr;
	int			sz;
	uint32_t 	dat;	
} tTnrRW;

#define NMI_DRV_TUNE							0x10001005
#define NMI_DRV_SCAN							0x10002005
#define NMI_DRV_SET_SCAN_TH                     0x10003005

#define NMI_DRV_RESET_DEMOD 		0x10001006
#define NMI_DRV_GET_STATUS 			0x10001007
#define NMI_DRV_RESET_DEMOD_MOSAIC 0x10001100
typedef struct
{
	tTnrDemodStatus ds;
	tTnrGain	gain;
} tTnrStatus;

#define NMI_DRV_SET_LNA_GAIN		0x10001008

#define NMI_DRV_INVERT_SPECTRUM     0x10001009
#define NMI_DRV_SET_IF_OUTPUT_VOLTAGE     0x1000100a
#define NMI_DRV_GET_IF_OUTPUT_VOLTAGE     0x1000100b

#define NMI_DRV_NOTCH_CTL                 0x1000100c
typedef struct
{
	int enable;
	double frequency;
	int width;	
} tNmiNotchCtl;

/*!
*  @def   NMI_DRV_ATV_SET_ATV_SCAN_LEVEL
*  @brief Controls the FM scan level.
*  @param A pointer to object type tNmiFmScanLevel to nmi_drv_ctl in arg param.
*  @sa    tNmiFmScanLevel 
*/
#define NMI_DRV_SET_FM_SCAN_LEVEL 0x1000100d
/*!
*  @struct tNmiFmScanLevel
*  @brief  FM Scan level.  
*  @sa     NMI_DRV_SET_FM_SCAN_LEVEL
*/
typedef struct {
	int level; /*! [IN]  Valid range 2 to 9. Default value is 3. */
} tNmiFmScanLevel;

/*!
*  @def   NMI_DRV_FM_SCAN
*  @brief Tunes to a specific FM frequency. Retrieves the RSSI.
*  @note  Use it during scan.
*  @param [INOUT] A pointer to object type tTnrFmScan to nmi_drv_ctl in arg param.
*  @sa    tTnrFmScan
*  @sa    NMI_DRV_ATV_SCAN
*/
#define NMI_DRV_FM_SCAN         0x1000100e


/*!
*  @def   NMI_DRV_FM_PROCESS
*  @brief Postprocessing on the FM channel list.
*  @note  Use it during scan.
*  @param [INOUT] A pointer to object type tNmiFMProcess to nmi_drv_ctl in arg param.
*  @sa    tNmiFMProcess
*/
#define NMI_DRV_FM_PROCESS      0x1000100f

/*!
*  @struct tNmiFMProcess
*  @brief  FM scan postprocessing context.
*  @sa     NMI_DRV_FM_PROCESS
*  @sa     tTnrFmScan
*  @sa     NMI_DRV_FM_SCAN
*/
typedef struct {
	int *chnRssi; /*!< [INOUT] rssi list as retrived from tNmiAtvScan.u.rssi. */
	int *chnOverTh; /*!< overth list as retrived from tNmiAtvScan.overth. */
	int chnRssiLen; /*!< [IN] chnRssi array length. */
	int *chnValid; /*!<[INOUT] */
	int chnValidLen; /*![IN] chnValid array length*/
	int chnValidCount; /*![OUT] No of valid channels in chnValid array.*/
} tNmiFMProcess;

/*!
*  @def   NMI_DRV_FM_SEEK
*  @brief Seek to the next FM channel on the list list.
*  @param [INOUT] A pointer to object type tNmiFMSeek to nmi_drv_ctl in arg param.
*  @sa    tNmiFMSeek
*/
#define NMI_DRV_FM_SEEK	        0x10001010

/*!
*  @struct tNmiFMSeek
*  @brief  FM seek context.
*  @sa     NMI_DRV_FM_SEEK
*/
typedef struct {
	int firstchannel;
	uint32_t frequency;
	uint32_t bandwidth;
	int found;
	int rssi;
	int overth;
} tNmiFMSeek;

/*!
*  @def   NMI_DRV_SLEEP
*  @brief Sofware-sleep NM131. Requires pulling down CHIP_EN pin.
*  @param [IN] A NULL pointer.
*/
#define NMI_DRV_SLEEP	        0x10001011

/*!
*  @def   NMI_DRV_SLEEP2
*  @brief Sofware-sleep NM131. Loop-through friendly sleep mode. Does not 
          require pulling down CHIP_EN pin.
*  @param [IN] A NULL pointer.
*/
#define NMI_DRV_SLEEP_LT          0x10001012
#define NMI_DRV_WAKE_UP_LT			0x10001013

#define NMI_DRV_SET_VOLUME      0x10001014
#define NMI_DRV_GET_VOLUME      0x10001015

typedef struct {
	uint8_t vol;
} tTnrVolume;


#define NMI_DRV_LT_CTRL         0x10001016
/**
Loop-through control: enable/disable.
**/
typedef struct {
	bool_t enable;
} tTnrLtCtrl;

#define NMI_DRV_SET_BRIGHTNESS      0x10001017
#define NMI_DRV_GET_BRIGHTNESS      0x10001018

typedef struct {
	uint8_t brt;
} tTnrBrt;

#define NMI_DRV_SET_VIDEO_AMP      0x10001019
#define NMI_DRV_GET_VIDEO_AMP      0x1000101a

typedef struct {
	uint8_t amp;
} tTnrVideoAmp;

#define NMI_DRV_SET_MUTE			0x1000101b
#define NMI_DRV_GET_MUTE			0x1000101c

typedef struct {
	uint8_t mute;		/*1 to activate mute, o otherwise*/
} tTnrMute;

#define NMI_DRV_VERSION								0x20000000
typedef struct
{
	int major;
	int minor;
	int rev1;
	int rev2;
	int buildrev;
} tNmiDriverVer;

#if !defined NTK_ENV
void nmi_tnr_set_video_amp(tTnrVideoAmp *p);
#endif
#endif
