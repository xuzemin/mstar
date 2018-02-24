/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nm131.h
**		These are the parameters used by the ASIC driver. 
**
** 
*******************************************************************************/
#ifndef _NM131_H_
#define _NM131_H_

/******************************************************************************
**
**	NMI Tuner Interface Functions Parameters
**
*******************************************************************************/

typedef struct {
	uint32_t    rf;  /*!< in Hz */
	uint32_t    aif; /*!< in Hz */
	uint32_t    vif; /*!< in Hz */
	tNmiTvStd   std;
	tNmiOutput  output;	
	bool_t      is_stereo;
	bool_t      single_tune; /*!<
							 Control frequency offset compensation.
							 Valid only for NM131/CVBS.
							 FALSE: tuning twice to compensate.
							 TRUE: tune once and do not compensate.
							 */
	tNmiDacSel	dacSel;		/*!<
							Select which Dac will carry the output in case of
							IF on NM130v and NM131 only*/
	bool_t      rfinvert;      /*!< Select if input RF spectrum is inverted.
							FALSE (Default): No inversion, TRUE: inverted.*/
} tTnrTune;

typedef struct {
	tTnrTune            tune;
	bool_t             found;
	int                 alocklevel;	
} tTnrScan;

/*!
*  @struct tTnrTuneMode
*  @brief  Enumeration to specify the purpose of tuning. 
*  @details Affects changing some register in the tuning sequence which depend 
*           on the purpose of tuning.
*/
typedef enum {
	nTuneOnly, /*!< Tune to watch and listen.  */
	nAtvScan, /*!< Tune to do ATV scan */
	nFmScan /*!< Tune to do FM scan */
} tTnrTuneMode;

/*!
*  @struct tTnrFmScan
*  @brief  FM scan  context.
*  @sa     NMI_DRV_FM_SCAN
*/
typedef struct {
	uint32_t frequency;/*!< Frequency in Hz. */	
	int16_t rssix100;/*!< (For FM only): FM RSSI value. */
	int overth; /*(For FM only): No. of FM frequencies above the theshold. */
} tTnrFmScan;

typedef struct {
	int16_t lnadbx100;
	int16_t bblidbx100;
	int16_t rssix100;
	uint8_t	bblicode;
	uint8_t lnacode;
} tTnrGain;

typedef struct {
	u17_15_t dagc;	
	int32_t fqoff;
	int16_t dsnrx100;
	int16_t	plllvl;
	bool_t agclock;
	bool_t cplllock;
} tTnrDemodStatus;


/******************************************************************************
**
**	NMI Tuner Function Table
**
*******************************************************************************/

typedef struct {
	int (*init)(void);
	uint32_t (*getchipid)(void);
	uint32_t (*r32)(uint16_t);
	void (*w32)(uint16_t, uint32_t);
	uint8_t (*rfr)(uint8_t);
	void (*rfw)(uint8_t, uint8_t);	
	int (*tune)(tTnrTune *);
	u17_15_t (*getdagc)(void);
	bool_t (*agclock)(void);
	bool_t (*cplllock)(void);
	int16_t (*getsnr)(void);
	int32_t (*getfreqoffset)(void);
	int16_t (*getplllevel)(void);
	void (*reset)(void);
         void(*reset_mosaic)(void);
	void (*getstatus)(tTnrDemodStatus *);
	void (*getlna)(tTnrGain *);
	void (*setgain)(tNmiLnaGain);
	void (*invertspectum) (int);
	void (*setifoutvoltage) (int);
	int (*getifoutvoltage) (void);
	void (*notchctl)(int, uint32_t, int);
	void (*setscanlevel)(int);
	void (*scan)(tTnrScan*);
	void (*fmscan)(tTnrFmScan*);
	void (*fmavgrssi)(int *, int, int*,int *);
	void (*fmscanlist)(int *, int *, int *, int *, int, int, int *);
	int (*fmseek)(int *,int *, int);
	int16_t (*getadecrssi)(void);
	int (*getoverthcount)(void);
	void (*setfmscanth)(int);
	void (*sleep)(void);	
	void (*sleep_lt)(void);
	void (*wake_up_lt)(void);
	void (*setvolume)(uint8_t);
	uint8_t (*getvolume)(void);
	void (*setvideoamp)(uint8_t);
	uint8_t (*getvideoamp)(void);
	void (*setbrightness)(uint8_t);
	uint8_t (*getbrightness)(void);
	void (*ltctrl)(bool_t);
	void (*setmute)(uint8_t);
	uint8_t (*getmute)(void);
} tTnrVtbl;

/*******************************************************************************
**
**	Driver Bus Test feature
**
*******************************************************************************/
/*!
*  @struct  tNmiBusTest
*  @brief   API interface for NM5625 driver bus test. 
*  @details 
*           When bus test mode is active, driver executes a bus test routine
*           instead of regular initialization. Since bus test would not 
*           allocate memory for burst read/write test, the caller should provide
*           memory for the NM5625 bus burst read/write test. If caller did not 
*           provide a buffer, then driver will ignore the burst read/write test.
*  @sa      NMI_DRV_INIT
*/
typedef struct {
	int enableTest; /*!< [IN] 0: disabled (Default). 1 or otherwise: enabled .*/
	uint8_t * buf; /*!< [IN] Temporary memory provided by upper layer for the 
				   burst read/write test. */
	uint32_t len; /*!< [IN] Temporary Buffer length. */
} tNmiBusTest;


/******************************************************************************
**
**	NMI OS dependent Functions
**
*******************************************************************************/

typedef struct {
	struct control{
		int (*read)(uint8_t, uint8_t *, uint32_t);
		int (*write)(uint8_t, uint8_t *, uint32_t);
		uint32_t (*getreadblksz)(void);
		uint32_t (*getwriteblksz)(void);
	} c;
	void (*delay)(uint32_t);
	uint32_t (*gettick)(void);
	void (*log)(char *);
} tNmiHlpVtbl;

/******************************************************************************
**
**	NMI Common Share Data Structure
**
*******************************************************************************/

typedef struct {
	uint32_t xo; /* in Hz. */
	int ldobypass;
	uint8_t ai2c;
	uint32_t zone;
	bool_t init_bus_only;
	tNmiHlpVtbl hlp;	
	tNmiBusTest busTest; /*!< [IN] Testing feature: when used, driver executes
						a bus test routine instead of regular initialization.*/
	bool_t xo_out_en; /*!< Force XO_OUT to be enabled all the time. */
} tNmiIn;

#endif
