/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmiioctl_cmn.c
**
**	Driver Tnr Functions
**
*******************************************************************************/

//#include <stdio.h>
//#include <stdarg.h>

/*******************************************************************************
**
**	Driver Global Variables
**
*******************************************************************************/

static int already_init = 0;

typedef struct {
	uint32_t frequency;
	int rssi;
	int overth;
} tNmiFmSeek;


typedef struct {
	uint32_t						chipid;
	tTnrVtbl						tnr;
	tNmiTvStd					standard;
	tNmiFmSeek 				fmSeek[7];
} tNmiDrv;

static tNmiDrv  drv;

/******************************************************************************
**
**	Driver Debug Defines
**
*******************************************************************************/

uint32_t dflag = N_ERR | N_INFO;

static void dPrint(unsigned long flag, char *fmt, ...)
{
	char buf[256];
	va_list args;
	int len;

	if (flag & dflag) { 
		va_start(args, fmt);
		len = vsnprintf(buf, 256, fmt, args);
		va_end(args);
		nmi_log(buf);	
	}

	return;
}

/******************************************************************************
**
**	Driver Tnr Functions
**
*******************************************************************************/

static void nmi_tnr_deinit(void)
{

	already_init = 0;
	return;
}

static int nmi_tnr_init(void *pv)
{
	tNmiDrv *pd = &drv;
	int result	= NMI_S_OK;
	tNmiIn inp;
	tTnrInit *p = (tTnrInit *)pv;

	if (!already_init) {
		memset((void *)pd, 0, sizeof(tNmiDrv));


		/**
			Asic Init
		**/
		memset((void *)&inp, 0, sizeof(tNmiIn));		
		inp.xo							= p->xo;
		inp.ldobypass				= p->ldobypass;
		inp.ai2c                    = p->i2c_adr;
		inp.zone                    = N_ERR|N_INFO;
		inp.hlp.c.write				= nmi_bus_write;
		inp.hlp.c.read				= nmi_bus_read;
		inp.hlp.c.getreadblksz      = nmi_bus_get_read_blksz;
		inp.hlp.c.getwriteblksz     = nmi_bus_get_write_blksz;
		inp.hlp.delay				= nmi_delay;
		inp.hlp.gettick				= nmi_get_tick;
		inp.hlp.log					= nmi_log;
		inp.init_bus_only           = p->init_bus_only;
		inp.xo_out_en               = p->xo_out_en;

		nmi_common_init(&inp, &pd->tnr);

 
		/**
			initialize chip
		**/
		if (pd->tnr.init() < 0) {
			dPrint(N_ERR, "[NMI] Failed to initialize chip...\n");
			result = NMI_E_CHIP_INIT;
			goto _fail_;
		}

		/**
		    Get chip id
		**/
		pd->chipid = pd->tnr.getchipid();

		already_init = 1;
	}

_fail_:

	return result;
}

static uint32_t nmi_tnr_get_chipid(void)
{
	tNmiDrv *pd = &drv;
	uint32_t chipid;

	chipid = pd->tnr.getchipid();

	return chipid;
}


static int nmi_tnr_tune(tTnrTune *p)
{
	int retVal;
	tNmiDrv *pd = &drv;

	retVal = pd->tnr.tune(p);

	return retVal;
}

static void nmi_tnr_reset_demod(void)
{
	tNmiDrv *pd = &drv;

	pd->tnr.reset();
}

static void nmi_tnr_reset_demod_mosaic(void)
{
	tNmiDrv *pd = &drv;

	pd->tnr.reset_mosaic();
}
static void nmi_tnr_get_status(tTnrStatus *p)
{
	tNmiDrv *pd = &drv;

	pd->tnr.getstatus(&p->ds);
	pd->tnr.getlna(&p->gain);
}

static int nmi_tnr_scan(tTnrScan * p)
{
	tNmiDrv *pd = &drv;

	pd->tnr.scan(p);

	return 0;
}
#if !defined NTK_ENV && !defined(MTC_FIX_BUG)  
static void nmi_tnr_set_volume(tTnrVolume *p)
{
	tNmiDrv *pd = &drv;
	pd->tnr.setvolume(p->vol);
}

static void nmi_tnr_get_volume(tTnrVolume *p)
{
	tNmiDrv *pd = &drv;

	p->vol = pd->tnr.getvolume();
}

static void nmi_tnr_set_mute(tTnrMute *p)
{
	tNmiDrv *pd = &drv;
	pd->tnr.setmute(p->mute);
}

static void nmi_tnr_get_mute(tTnrMute *p)
{
	tNmiDrv *pd = &drv;

	p->mute = pd->tnr.getmute();
}
#endif

static void nmi_tnr_lt_ctrl(tTnrLtCtrl *p)
{
	tNmiDrv *pd = &drv;

	pd->tnr.ltctrl(p->enable);
}

#if !defined(NTK_ENV) && !defined(MTC_FIX_BUG)  
void nmi_tnr_set_video_amp(tTnrVideoAmp *p)
{
	tNmiDrv *pd = &drv;
	pd->tnr.setvideoamp(p->amp);
}

static void nmi_tnr_get_video_amp(tTnrVideoAmp *p)
{
	tNmiDrv *pd = &drv;

	p->amp = pd->tnr.getvideoamp();
}

static void nmi_tnr_set_brightness(tTnrBrt *p)
{
	tNmiDrv *pd = &drv;
	pd->tnr.setbrightness(p->brt);
}

static void nmi_tnr_get_brightness(tTnrBrt *p)
{
	tNmiDrv *pd = &drv;

	p->brt = pd->tnr.getbrightness();
}
#endif

static unsigned int nmi_svn_rev_to_int(const char *r)
{
	const unsigned int count = 
		r[11] == ' ' ? 1
		: r[12] == ' ' ? 10
		: r[13] == ' ' ? 100
		: r[14] == ' ' ? 1000
		: r[15] == ' ' ? 10000
		: r[16] == ' ' ? 100000
		: r[17] == ' ' ? 1000000
		: r[18] == ' ' ? 10000000
		: r[19] == ' ' ? 100000000
		: 0;

	if ( r == NULL || r[0] == '\0' || r[10] == '\0' || r[11] == '\0' || r[12] == '\0' || r[13] == '\0' )
		return 0;

	return
		(r[11] == ' ' ? 0 : (r[11]-'0') * (count/10) +
		(r[12] == ' ' ? 0 : (r[12]-'0') * (count/100) + 
		(r[13] == ' ' ? 0 : (r[13]-'0') * (count/1000) + 
		(r[14] == ' ' ? 0 : (r[14]-'0') * (count/10000) + 
		(r[15] == ' ' ? 0 : (r[15]-'0') * (count/100000) +
		(r[16] == ' ' ? 0 : (r[16]-'0') * (count/1000000) +
		(r[17] == ' ' ? 0 : (r[17]-'0') * (count/10000000) +
		(r[18] == ' ' ? 0 : (r[18]-'0') * (count/100000000) +
		(r[19] == ' ' ? 0 : (r[19]-'0') * (count/1000000000) +
		0)))))))));
}
static void nmi_tnr_get_version(tNmiDriverVer * vp)
{	
	vp->major = ASIC_MAJOR_VER;
	vp->minor = ASIC_MINOR_VER;
	vp->rev1 = ASIC_REV1;
	vp->rev2 = ASIC_REV2;
	vp->buildrev = nmi_svn_rev_to_int(BUILD_REV);
}
