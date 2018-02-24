/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nm131.c
**	
**
*******************************************************************************/

#ifndef HAVE_FLOATING_POINT
#define USE_NM131_NOTCH_LUT
#endif

#define DUBGANG_TEST
static void nm131_scan(tTnrScan *p);
static void nm131_notch_spur(void);
static void nm131_notch_ctl(int en, int width);
 extern uint32_t rReg32(uint16_t adr);
 extern void wReg32(uint16_t adr, uint32_t val);
/******************************************************************************
**
**	Tables
**
*******************************************************************************/

/* FRQ_OFFSET: is additional frequency offset added to the RF frequency per standard*/
static const uint32_t rf_freq_offset_lut[] = { 
	/*      nNTSC */  2220000, 
	/*     nPAL_G */  2720000, 
	/*     nPAL_M */  2220000, 
	/*     nPAL_N */  2220000, 
	/*     nPAL_K */  3220000, 
	/*     nPAL_L */  3220000, 
	/*     nDTV_6 */        0, 
	/*   nSECAM_L */  3220000, 
	/*     nDTV_7 */        0, 
	/*   nSECAM_B */  2720000, 
	/*     nPAL_I */  3220000, 
	/*   nSECAM_D */  3220000, 
	/*     nDTV_8 */        0, 
	/*   nFM_RADIO*/  2220000,
	/*	 nDVBT_6  */        0,
	/*	 nDVBT_7  */        0,
	/*	 nDVBT_8  */        0,
};

static const  uint8_t avsep_real /*(0x104)*/[] = {
	/*      nNTSC */ 0x00, 
	/*     nPAL_G */ 0x02, 
	/*     nPAL_M */ 0x00, 
	/*     nPAL_N */ 0x00, 
	/*     nPAL_K */ 0x02, 
	/*     nPAL_L */ 0x02, 
	/*     nDTV_6 */ 0x00, 
	/*   nSECAM_L */ 0x02, 
	/*     nDTV_7 */ 0x00, 
	/*   nSECAM_B */ 0x02, 
	/*     nPAL_I */ 0x02, 
	/*   nSECAM_D */ 0x02, 
	/*     nDTV_8 */ 0x00, 
	/*  nFM_RADIO */ 0x00, 
	/*	 nDVBT_6  */ 0x00,
	/*	 nDVBT_7  */ 0x00,
	/*	 nDVBT_8  */ 0x00,
};
static const uint8_t nm120_aci_lut[] = {
	/*                NM120 */
     /*      nNTSC */ 0x00, 
     /*     nPAL_G */ 0x00, 
     /*     nPAL_M */ 0x00, 
     /*     nPAL_N */ 0x00, 
     /*     nPAL_K */ 0x00, 
     /*     nPAL_L */ 0x00, 
     /*     nDTV_6 */ 0x04, 
     /*   nSECAM_L */ 0x00, 
     /*     nDTV_7 */ 0x04, 
     /*   nSECAM_B */ 0x00, 
     /*     nPAL_I */ 0x00, 
     /*   nSECAM_D */ 0x00, 
     /*     nDTV_8 */ 0x04, 
     /*  nFM_RADIO */ 0x00, 	
};

static const uint8_t aci_lut[] = {
#if 0
	/*                NM120,130,130v and NM131    */
	/*      nNTSC */ 0x00, 
	/*     nPAL_G */ 0x02, 
	/*     nPAL_M */ 0x00, 
	/*     nPAL_N */ 0x00, 
	/*     nPAL_K */ 0x04, 
	/*     nPAL_L */ 0x04, 
	/*     nDTV_6 */ 0x07, 
	/*   nSECAM_L */ 0x04, 
     /*     nDTV_7 */ 0x0d,//0x0a, 
	/*   nSECAM_B */ 0x02, 
	/*     nPAL_I */ 0x04, 
	/*   nSECAM_D */ 0x04, 
     /*     nDTV_8 */ 0x0D, 
	/*  nFM_RADIO */ 0x00, 
#endif
#if 1
     /*                NM120,130,130v and NM131    */
     /*      nNTSC */ 0x00, 
     /*     nPAL_G */ 0x02, 
     /*     nPAL_M */ 0x00, 
     /*     nPAL_N */ 0x00, 
     /*     nPAL_K */ 0x04, 
     /*     nPAL_L */ 0x04, 
     /*     nDTV_6 */ 0x04,//0x07, 
     /*   nSECAM_L */ 0x04, 
     /*     nDTV_7 */ 0x04,//0x0d,//0x0a, 
     /*   nSECAM_B */ 0x02, 
     /*     nPAL_I */ 0x04, 
     /*   nSECAM_D */ 0x04, 
     /*     nDTV_8 */ 0x04,//0x0D, 
     /*  nFM_RADIO */ 0x00, 	
#endif
};

/*add by wang for T:ACI*/
static const uint8_t aci_lut_T[] = {

	/*                NM120,130,130v and NM131    */
	/*      nNTSC */ 0x00, 
	/*     nPAL_G */ 0x02, 
	/*     nPAL_M */ 0x00, 
	/*     nPAL_N */ 0x00, 
	/*     nPAL_K */ 0x04, 
	/*     nPAL_L */ 0x04, 
	/*     nDTV_6 */ 0x04, 
	/*   nSECAM_L */ 0x04, 
	/*     nDTV_7 */ 0x04, 
	/*   nSECAM_B */ 0x02, 
	/*     nPAL_I */ 0x04, 
	/*   nSECAM_D */ 0x04, 
	/*     nDTV_8 */ 0x04,//0x04, 
	/*  nFM_RADIO */ 0x00, 
};


static const  uint32_t adec_ddfs_fq /*(0x230)*/[] = {
	/*      nNTSC */ 0x00015555, 
	/*     nPAL_G */ 0x0001a12f, 
	/*     nPAL_M */ 0x00015555, 
	/*     nPAL_N */ 0x00015555, 
	/*     nPAL_K */ 0x0001ed09, 
	/*     nPAL_L */ 0x0001ed09, 
	/*     nDTV_6 */ 0x0001ed09, 
	/*   nSECAM_L */ 0x0001ed09, 
	/*     nDTV_7 */ 0x0001a12f, 
	/*   nSECAM_B */ 0x0001a12f, 
	/*     nPAL_I */ 0x0001c715, 
	/*   nSECAM_D */ 0x0001ed09, 
	/*     nDTV_8 */ 0x00008000, 
	/*  nFM_RADIO */ 0x00006117, 
	/*	 nDVBT_6  */ 0x0001ed09,
	/*	 nDVBT_7  */ 0x0001a12f,
	/*	 nDVBT_8  */ 0x00008000,
};


static const  uint32_t cvbs_ddfs_audio_out_lut /*(0x234)*/[] = {
	/*      nNTSC */ 0x00015555, 
	/*     nPAL_G */ 0x0001a12f, 
	/*     nPAL_M */ 0x00015555, 
	/*     nPAL_N */ 0x00015555, 
	/*     nPAL_K */ 0x0001ed09, 
	/*     nPAL_L */ 0x0001ed09, 
	/*     nDTV_6 */ 0x00000000, 
	/*   nSECAM_L */ 0x0001ed09, 
	/*     nDTV_7 */ 0x00000000, 
	/*   nSECAM_B */ 0x0001a12f, 
	/*     nPAL_I */ 0x0001c715, 
	/*   nSECAM_D */ 0x0001ed09, 
	/*     nDTV_8 */ 0x00000000, 
	/*  nFM_RADIO */ 0x00015555, 
	/*	 nDVBT_6  */ 0x00000000,
	/*	 nDVBT_7  */ 0x00000000,
	/*	 nDVBT_8  */ 0x00000000,
};
static const  uint8_t ACI_audio_lut /*(0x250)*/[] = {
	/*      nNTSC */ 0x00, 
	/*     nPAL_G */ 0x00, 
	/*     nPAL_M */ 0x00, 
	/*     nPAL_N */ 0x00, 
	/*     nPAL_K */ 0x00, 
	/*     nPAL_L */ 0x01, 
	/*     nDTV_6 */ 0x00, 
	/*   nSECAM_L */ 0x01, 
	/*     nDTV_7 */ 0x00, 
	/*   nSECAM_B */ 0x00, 
	/*     nPAL_I */ 0x00, 
	/*   nSECAM_D */ 0x00, 
	/*     nDTV_8 */ 0x00, 
	/*  nFM_RADIO */ 0x00, 
	/*	 nDVBT_6  */ 0x00,
	/*	 nDVBT_7  */ 0x00,
	/*	 nDVBT_8  */ 0x00,
};

static const  uint32_t ddfs_lut /*(0x1bc)*/[] = {
	/*      nNTSC */ 0x0002a190, 
	/*     nPAL_G */ 0x00033945, 
	/*     nPAL_M */ 0x0002a190, 
	/*     nPAL_N */ 0x0002a190, 
	/*     nPAL_K */ 0x0003d0f9, 
	/*     nPAL_L */ 0x0003d0f9, 
	/*     nDTV_6 */ 0x00000000, 
	/*   nSECAM_L */ 0x0003d0f9, 
	/*     nDTV_7 */ 0x00000000, 
	/*   nSECAM_B */ 0x00033945, 
	/*     nPAL_I */ 0x0003d0f9, 
	/*   nSECAM_D */ 0x0003d0f9, 
	/*     nDTV_8 */ 0x00000000, 
	/*  nFM_RADIO */ 0x00000000, 
	/*	 nDVBT_6  */ 0x00000000,
	/*	 nDVBT_7  */ 0x00000000,
	/*	 nDVBT_8  */ 0x00000000,
};
/* LO_DIV: affects register (0x1D) bits 5-7*/
/* OFF 8 16 24 32 48 72 96*/
static const uint32_t lo_freq_lut[] = { 
	/*               0 */        0, 
	/*               1 */        0, 
	/*               2 */ 435000000, 
	/*               3 */ 237000000, 
	/*               4 */ 214000000, 
	/*               5 */ 118000000, 
	/*               6 */ 79000000, 
	/*               7 */ 53000000, 
};

static const  uint32_t avsep_comp /*(0x104)*/[] = {
	/*      nNTSC */ 0x00000004, 
	/*     nPAL_G */ 0x00000007, 
	/*     nPAL_M */ 0x00000004, 
	/*     nPAL_N */ 0x00000004, 
	/*     nPAL_K */ 0x00000007, 
	/*     nPAL_L */ 0x00000007, 
	/*     nDTV_6 */ 0x00000000, 
	/*   nSECAM_L */ 0x00000007, 
	/*     nDTV_7 */ 0x00000000, 
	/*   nSECAM_B */ 0x00000007, 
	/*     nPAL_I */ 0x00000007, 
	/*   nSECAM_D */ 0x00000007, 
	/*     nDTV_8 */ 0x00000000, 
	/*  nFM_RADIO */ 0x00000004, 
	/*	 nDVBT_6  */ 0x00000000,
	/*	 nDVBT_7  */ 0x00000000,
	/*	 nDVBT_8  */ 0x00000000,
};
static const  uint8_t agc_mode /*(0x104)*/[] = {
	/*      nNTSC */ 0, 
	/*     nPAL_G */ 0, 
	/*     nPAL_M */ 0, 
	/*     nPAL_N */ 0, 
	/*     nPAL_K */ 0, 
	/*     nPAL_L */ 0, 
	/*     nDTV_6 */ 1, 
	/*   nSECAM_L */ 0, 
	/*     nDTV_7 */ 1, 
	/*   nSECAM_B */ 0, 
	/*     nPAL_I */ 0, 
	/*   nSECAM_D */ 0, 
	/*     nDTV_8 */ 1, 
	/*  nFM_RADIO */ 1, 
	/*	 nDVBT_6  */ 1,
	/*	 nDVBT_7  */ 1,
	/*	 nDVBT_8  */ 1,
};

typedef struct {
	uint8_t addr;
	uint8_t val;
} tnr_rf_reg_t;

typedef struct {
	uint16_t addr;
	uint32_t val;
} tnr_bb_reg_t;
#define tnr_rf_defaults_lut_sz (sizeof(tnr_rf_defaults_lut)/sizeof(tnr_rf_defaults_lut[0]))
static const tnr_rf_reg_t tnr_rf_defaults_lut[] = {	
	{ 0x06, 0x48 },
	{ 0x07, 0x40 },
	{ 0x0a, 0xeb },
	{ 0x0b, 0x11 },
	{ 0x0c, 0x10 },
	{ 0x0d, 0x88 },
	{ 0x10, 0x04 },
	{ 0x11, 0x30 },
	{ 0x12, 0x30 },
	{ 0x15, 0xaa },
	{ 0x16, 0x03 },
	{ 0x17, 0x80 },
	{ 0x18, 0x67 },
	{ 0x19, 0xd4 },
	{ 0x1a, 0x44 },
	{ 0x1c, 0x10 },
	{ 0x1d, 0xee },
	{ 0x1e, 0x99 },
	{ 0x21, 0xc5 },
	{ 0x22, 0x91 },
	{ 0x24, 0x01 },
	{ 0x2b, 0x91 },
	{ 0x2d, 0x01 },
	{ 0x2f, 0x80 },
	{ 0x31, 0x00 },
	{ 0x33, 0x00 },
	{ 0x38, 0x00 },
	{ 0x39, 0x2f },
	{ 0x3a, 0x00 },
	{ 0x3b, 0x00 },
}; 

#define nm120_rf_defaults_lut_sz (sizeof(nm120_rf_defaults_lut)/sizeof(nm120_rf_defaults_lut[0]))
static const tnr_rf_reg_t nm120_rf_defaults_lut[] = {
	{ 0x0e, 0x45 },
	{ 0x1b, 0x0e },
	{ 0x23, 0xff },
	{ 0x26, 0x82 },
	{ 0x28, 0x00 },
	{ 0x30, 0xdf },
	{ 0x32, 0xdf },
	{ 0x34, 0x68 },
	{ 0x35, 0x18 },
};

#define nm130_rf_defaults_lut_sz (sizeof(nm130_rf_defaults_lut)/sizeof(nm130_rf_defaults_lut[0]))
static const tnr_rf_reg_t nm130_rf_defaults_lut[] = {
	{ 0x26, 0x80 },
	{ 0x27, 0x5f },
	{ 0x28, 0x00 },		
	{ 0x29, 0x5f },
	{ 0x34, 0x68 },
	{ 0x35, 0x18 },
	{ 0x36, 0x7c },
};

#define nm130v_rf_defaults_lut_sz (sizeof(nm130v_rf_defaults_lut)/sizeof(nm130v_rf_defaults_lut[0]))
static const tnr_rf_reg_t nm130v_rf_defaults_lut[] = {
	{ 0x1b, 0x0e },
	{ 0x28, 0x00 },
	{ 0x2e, 0x56 },
	{ 0x34, 0x78 },
};

#define nm131_rf_defaults_lut_sz (sizeof(nm131_rf_defaults_lut)/sizeof(nm131_rf_defaults_lut[0]))
static const tnr_rf_reg_t nm131_rf_defaults_lut[] = {	
	{ 0x1b, 0x0e },
	{ 0x28, 0x00 },	
};

#define tnr_bb_defaults_lut_sz (sizeof(tnr_bb_defaults_lut)/sizeof(tnr_bb_defaults_lut[0]))
static const tnr_bb_reg_t tnr_bb_defaults_lut[] = {
	{ 0x164, 0x800}, 
	{ 0x1c0, 0x2d8c19c7 },
}; 



typedef struct {
	uint32_t frequency;
	uint8_t val8_0x08;
	uint8_t val8_0x09;
} vhf_filter_cutoff_codes_t;

/* "Setttings for VHF_Code0  VHF_Code1 and VHF_Code2. Affects registers 0x08 and 0x09."*/
static const vhf_filter_cutoff_codes_t vhf_filter_cutoff_codes[] = { 
	/*{If Less than Freq (Hz), Code 1, Code 2, Code 3, VHF_Filter_En, VHF_RC_Bypass, }*/
	{ 45000000, 0xa7, 0x3a, }, 
	{ 55000000, 0x97, 0x39, }, 
	{ 65000000, 0x64, 0x36, }, 
	{ 75000000, 0x53, 0x35, }, 
	{ 85000000, 0x52, 0x35, }, 
	{ 95000000, 0x41, 0x34, }, 
	{105000000, 0x40, 0x34, }, 
	{115000000, 0x40, 0x34, }, 
	{125000000, 0x00, 0x00, }, 
};

#if defined USE_NM131_NOTCH_LUT

typedef struct {
	uint32_t frequency;	
	tNmiTvStd std;
	uint8_t reg_0x114_msb;
	uint16_t reg_0x114_lsb;	
	uint8_t reg_0x118_msb;
	uint16_t reg_0x118_lsb;	
	int u8Width;
} tNmiNotchSpur;

#define nm131_cvbs_notch_spur_sz (sizeof(nm131_cvbs_notch_spur)/sizeof(nm131_cvbs_notch_spur[0]))

static const tNmiNotchSpur  nm131_cvbs_notch_spur[] = {
#define nPAL_M nNTSC
#define nPAL_N nNTSC
#define nSECAM_B nPAL_G
#define nPAL_I nPAL_K
#define nSECAM_D nPAL_K
#if 0//ÂÀÏþÔÆ
	{ 48250000, nPAL_M, 0x6, 0xdce9, 0x31, 0x8bf0 },
	{ 189250000, nPAL_M, 0xf, 0x872d, 0x3, 0xdb80 },
	{ 479250000, nPAL_G, 0xa, 0x4742, 0x33, 0xbcf2 },
	{ 503250000, nPAL_G, 0xa, 0x2f9d, 0x33, 0xa946 },
	{ 527250000, nPAL_G, 0xa, 0x19fc, 0x33, 0x978b },
	{ 551250000, nPAL_G, 0xa, 0x61f, 0x33, 0x8779 },
	{ 575250000, nPAL_G, 0x9, 0xf3d2, 0x33, 0x78da },
	{ 599250000, nPAL_G, 0x9, 0xe2e8, 0x33, 0x6b7c },
	{ 623250000, nPAL_G, 0x9, 0xd33a, 0x33, 0x5f39 },
	{ 647250000, nPAL_G, 0x9, 0xc4a6, 0x33, 0x53f0 },
	{ 671250000, nPAL_G, 0xa, 0x2ce7, 0x33, 0xa70a },
	{ 695250000, nPAL_G, 0xa, 0x1c92, 0x33, 0x99a7 },
	{ 719250000, nPAL_G, 0xa, 0xd43, 0x33, 0x8d3b },
	{ 743250000, nPAL_G, 0x9, 0xfee3, 0x33, 0x81ac },
	{ 767250000, nPAL_G, 0x9, 0xf15c, 0x33, 0x76e6 },
	{ 791250000, nPAL_G, 0x9, 0xe49c, 0x33, 0x6cd3 },
	{ 815250000, nPAL_G, 0x9, 0xd892, 0x33, 0x6364 },
	{ 839250000, nPAL_G, 0x9, 0xcd2f, 0x33, 0x5a88 },
	{ 45750000, nPAL_I, 0xe, 0x8182, 0x39, 0x3fb0 },
	{ 191250000, nPAL_I, 0x7, 0x2b6, 0x31, 0x9e20 },
	{ 215250000, nPAL_I, 0x6, 0xbb2e, 0x31, 0x7c1c },
	{ 479250000, nPAL_I, 0x7, 0x590c, 0x31, 0xc97a },
	{ 503250000, nPAL_I, 0x7, 0x368c, 0x31, 0xb7d8 },
	{ 527250000, nPAL_I, 0x7, 0x1706, 0x31, 0xa818 },
	{ 551250000, nPAL_I, 0x6, 0xfa1c, 0x31, 0x99f2 },
	{ 575250000, nPAL_I, 0x6, 0xdf80, 0x31, 0x8d2b },
	{ 599250000, nPAL_I, 0x6, 0xc6ee, 0x31, 0x8195 },
	{ 623250000, nPAL_I, 0x6, 0xb02d, 0x31, 0x7706 },
	{ 647250000, nPAL_I, 0x6, 0x9b0a, 0x31, 0x6d60 },
	{ 671250000, nPAL_I, 0x7, 0x319f, 0x31, 0xb55d },
	{ 695250000, nPAL_I, 0x7, 0x19d8, 0x31, 0xa97e },
	{ 719250000, nPAL_I, 0x7, 0x395, 0x31, 0x9e8c },
	{ 743250000, nPAL_I, 0x6, 0xeeb0, 0x31, 0x946e },
	{ 767250000, nPAL_I, 0x6, 0xdb0c, 0x31, 0x8b0d },
	{ 791250000, nPAL_I, 0x6, 0xc88b, 0x31, 0x8256 },
	{ 815250000, nPAL_I, 0x6, 0xb717, 0x31, 0x7a37 },
	{ 839250000, nPAL_I, 0x6, 0xa698, 0x31, 0x72a2 },
	{ 67250000, nNTSC, 0x6, 0x3fce, 0xe, 0xbaa7 },
	{ 187250000, nNTSC, 0x6, 0x2cc3, 0xe, 0xc2ad },
	{ 211250000, nNTSC, 0x6, 0x7959, 0xe, 0xa1b7 },
	{ 477250000, nNTSC, 0xf, 0x8e54, 0x3, 0xbe43 },
	{ 501250000, nNTSC, 0xf, 0x8c6e, 0x3, 0xc61d },
	{ 525250000, nNTSC, 0xf, 0x8ab1, 0x3, 0xcd3f },
	{ 549250000, nNTSC, 0xf, 0x8918, 0x3, 0xd3c1 },
	{ 573250000, nNTSC, 0xf, 0x879f, 0x3, 0xd9b8 },
	{ 597250000, nNTSC, 0xf, 0x8642, 0x3, 0xdf34 },
	{ 621250000, nNTSC, 0xf, 0x84fe, 0x3, 0xe444 },
	{ 645250000, nNTSC, 0xf, 0x8de6, 0x3, 0xc00a },
	{ 669250000, nNTSC, 0xf, 0x8c7e, 0x3, 0xc5dd },
	{ 693250000, nNTSC, 0xf, 0x8b2c, 0x3, 0xcb48 },
	{ 717250000, nNTSC, 0xf, 0x89ef, 0x3, 0xd056 },
	{ 741250000, nNTSC, 0xf, 0x88c5, 0x3, 0xd511 },
	{ 765250000, nNTSC, 0xf, 0x87ad, 0x3, 0xd97f },
	{ 789250000, nNTSC, 0xf, 0x86a4, 0x3, 0xdda8 },
	{ 65750000, nPAL_I, 0x3, 0x831c, 0xf, 0x9c19 },
	{ 192250000, nPAL_I, 0x0, 0x25eb, 0x30, 0x2d },
	{ 863250000, nPAL_I, 0x7, 0x1b93, 0x31, 0xaa59 },
	{ 168250000, nPAL_G, 0x3, 0x47a8, 0x30, 0x56fd },
	{ 192250000, nPAL_G, 0x3, 0xa920, 0x30, 0x6ca5 },
	{ 216250000, nPAL_G, 0x3, 0x4add, 0x30, 0x57a9 },
	{ 863250000, nPAL_G, 0xa, 0x1e28, 0x33, 0x9af1 },
	{ 93250000, nPAL_G, 0xf, 0xff9c, 0x0, 0x3850 },
	{ 191250000, nPAL_G, 0xa, 0x74e, 0x33, 0x886d },
	{ 215250000, nPAL_G, 0x9, 0xd67b, 0x33, 0x61c2 },
	{ 93250000, nSECAM_D, 0xf, 0xa253, 0x3c, 0x9905 },
	{ 479250000, nPAL_N, 0xc, 0xb737, 0x36, 0x49e3 },
	{ 503250000, nPAL_N, 0xc, 0xa94d, 0x36, 0x37c5 },
	{ 527250000, nPAL_N, 0xc, 0x9c8f, 0x36, 0x275e },
	{ 551250000, nPAL_N, 0xc, 0x90da, 0x36, 0x1871 },
	{ 575250000, nPAL_N, 0xc, 0x860e, 0x36, 0xace },
	{ 599250000, nPAL_N, 0xc, 0x7c12, 0x35, 0xfe4c },
	{ 623250000, nPAL_N, 0xc, 0x72cf, 0x35, 0xf2c9 },
	{ 647250000, nPAL_N, 0xc, 0x6a32, 0x35, 0xe827 },
	{ 671250000, nPAL_N, 0xc, 0xa81a, 0x36, 0x3638 },
	{ 695250000, nPAL_N, 0xc, 0x9e79, 0x36, 0x29d2 },
	{ 719250000, nPAL_N, 0xc, 0x9571, 0x36, 0x1e47 },
	{ 743250000, nPAL_N, 0xc, 0x8cf5, 0x36, 0x1382 },
	{ 767250000, nPAL_N, 0xc, 0x84f7, 0x36, 0x96f },
	{ 791250000, nPAL_N, 0xc, 0x7d6e, 0x35, 0xfffe },
	{ 815250000, nPAL_N, 0xc, 0x7650, 0x35, 0xf721 },
	{ 839250000, nPAL_N, 0xc, 0x6f94, 0x35, 0xeec9 },
	{ 48250000, nSECAM_B, 0x3, 0x9f51, 0x30, 0x6a5a },
	{ 189250000, nSECAM_B, 0xf, 0xff9c, 0x0, 0x384d },
	{ 210250000, nSECAM_B, 0x2, 0xf252, 0xf, 0xb9f1 },
	{ 91250000, nNTSC, 0x6, 0xc58c, 0xe, 0x7f11 },
	{ 115250000, nNTSC, 0x6, 0x3386, 0xe, 0xbfd7 },
	{ 475250000, nNTSC, 0x6, 0xcc5b, 0xe, 0x7be1 },
	{ 499250000, nNTSC, 0x6, 0xaa14, 0xe, 0x8bc6 },
#else

	{ 48250000, nPAL_G, 0x3, 0x9f51, 0x30, 0x6a5a, 3 },
	{ 48000000, nPAL_G, 0x3, 0x9f51, 0x30, 0x6a5a, 3 },
	{ 48500000, nPAL_G, 0x3, 0x9f51, 0x30, 0x6a5a, 3 },
	
	{ 719250000, nPAL_G, 0xa, 0xd43, 0x33, 0x8d3d, 2 },
	{ 189250000, nPAL_G, 0xf, 0xff9c, 0x0, 0x384d, 0 },
	{ 767250000, nPAL_G, 0x9, 0xf15c, 0x33,0x76e6, 0},
	{ 791250000, nPAL_G, 0x9, 0xe49c, 0x33, 0x6cd3, 0},
	{ 863250000, nPAL_G, 0xa, 0x1e28, 0x33, 0x9af1, 7}, 
	//{ 55392600,   nPAL_G,0x2,  0xc743, 0x30,0x3e3b, 7 },//songbin120517
	{ 54918900,   nPAL_G,0x2,  0xc73b, 0x30,0x3e39, 6 },//songbin120517

	{ 575250000, nPAL_K, 0x6, 0xdf80, 0x31, 0x8d2b, 0},//PALDK
    	{ 791250000, nPAL_K, 0x6, 0xc88b, 0x31, 0x8256, 0},//PALDK
    	{ 863250000, nPAL_K, 0x7, 0x1b93, 0x31, 0xaa59, 7},//PALDK [118]31badb [114]73c7f { 863250000, nPAL_K, 0x7, 0x1b93, 0x31, 0xaa59},//PALDK cccc1401
	{ 55392600,   nPAL_K,0x2,  0xc743, 0x30,0x3e3b, 7 },//songbin 120517

#endif
#undef nPAL_M
#undef nPAL_N
#undef nSECAM_B
#undef nPAL_I
#undef nSECAM_D
};

#endif
/******************************************************************************
**
**	Internal Macro
**
*******************************************************************************/
/**
Calculate 80log10(x), where x is expressed in 17.15 format.
**/
int16_t nmi_log10(u17_15_t x)
{
	int y;
	static const uint8_t LOGLUT[256]= {
		0,  0, 24, 38, 48, 56, 62, 68,
		72, 76, 80, 83, 86, 89, 92, 94,
		96, 98,100,102,104,106,107,109,
		110,112,113,115,116,117,118,119,
		120,121,123,124,125,125,126,127,
		128,129,130,131,131,132,133,134,
		134,135,136,137,137,138,139,139,
		140,140,141,142,142,143,143,144,
		144,145,146,146,147,147,148,148,
		149,149,150,150,150,151,151,152,
		152,153,153,154,154,154,155,155,
		156,156,156,157,157,157,158,158,
		159,159,159,160,160,160,161,161,
		161,162,162,162,163,163,163,164,
		164,164,165,165,165,165,166,166,
		166,167,167,167,167,168,168,168,
		169,169,169,169,170,170,170,170,
		171,171,171,171,172,172,172,172,
		173,173,173,173,174,174,174,174,
		175,175,175,175,175,176,176,176,
		176,177,177,177,177,177,178,178,
		178,178,178,179,179,179,179,179,
		180,180,180,180,180,181,181,181,
		181,181,182,182,182,182,182,182,
		183,183,183,183,183,184,184,184,
		184,184,184,185,185,185,185,185,
		185,186,186,186,186,186,186,187,
		187,187,187,187,187,188,188,188,
		188,188,188,188,189,189,189,189,
		189,189,190,190,190,190,190,190,
		190,191,191,191,191,191,191,191,
		192,192,192,192,192,192,192,193	
	};

	if (x<256)
		y=LOGLUT[x>>0]-6*15*4;
	else if (x<(1ul<<9))
		y=LOGLUT[x>>1]-6*14*4;
	else if (x<(1ul<<10))
		y=LOGLUT[x>>2]-6*13*4;
	else if (x<(1ul<<11))
		y=LOGLUT[x>>3]-6*12*4;
	else if (x<(1ul<<12))
		y=LOGLUT[x>>4]-6*11*4;
	else if (x<(1ul<<13))
		y=LOGLUT[x>>5]-6*10*4;
	else if (x<(1ul<<14))
		y=LOGLUT[x>>6]-6*9*4;
	else if (x<(1ul<<15))
		y=LOGLUT[x>>7]-6*8*4;
	else if (x<(1ul<<16))
		y=LOGLUT[x>>8]-6*7*4;
	else if (x<(1ul<<17))
		y=LOGLUT[x>>9]-6*6*4;
	else if (x<(1ul<<18))
		y=LOGLUT[x>>10]-6*5*4;
	else if (x<(1ul<<19))
		y=LOGLUT[x>>11]-6*4*4;
	else if (x<(1ul<<20))
		y=LOGLUT[x>>12]-6*3*4;
	else if (x<(1ul<<21))
		y=LOGLUT[x>>13]-6*2*4;
	else if (x<(1ul<<22))
		y=LOGLUT[x>>14]-6*1*4;
	else if (x<(1ul<<23))
		y=LOGLUT[x>>15]-6*0*4;
	else if (x<(1ul<<24))
		y=LOGLUT[x>>16]+6*4;
	else
		y=LOGLUT[x>>17]+6*2*4;
	return y;
}

/******************************************************************************
**
**	Demod
**
*******************************************************************************/
static void nm131_set_if_output_voltage(int mV)
{
	uint32_t val32;

	val32 = (mV*0x600)/150;	

	wReg32(0x164, val32);
}
static int nm131_get_if_output_voltage(void)
{
	uint32_t val32;

	val32 = rReg32(0x164);

	return (val32*150)/0x600;	
}

void nm131_demod_T_config_for_dvbt7(int Normal)
{
	//Normal:1:0x0a;0:0x0d
	uint32_t aci=0x0a;
	uint32_t val32;
	/**
		ACI 
	**/
	if(Normal)
		aci=0x0a;
	else
		aci=0x0d;
	
	val32 = rReg32(0x104);
	val32 &= ~(0xful << 11);
	val32 |= (aci << 11);

	wReg32(0x104, val32);
}


static void nm131_demod_config(uint32_t rffrequency, tNmiTvStd std, 
							   tNmiOutput output, uint32_t aif, uint32_t vif, uint32_t clk_off_f, 
							   bool_t is_stereo, tTnrTuneMode tuneMode, tNmiDacSel dacSel, bool_t rfinvert)
{
	uint32_t val32;
	uint32_t audio_offset;
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;

	if(ISNM131(chip.priv.chipid)) {
		/* Blind scan changes for NM131 CVBS */
		/* FM audio support */
		if( (pp->output != output) || (pp->std != std) ) {
			if(std != nFM_RADIO) {
				val32 = 0x2d8c19c7;
				if(ISCVBS(output)) {
					/**
					Make demod bw wide enough to locked within 300 KHz.
					**/		
					val32 &= ~(0x3ul << 28);
					val32 &= ~(0x1ul << 27);
				}
			} else {
				val32 = 0x358cffff;			
			}
			wReg32(0x1c0, val32);
		}
	}


	/* analog ATV_AGC target */
	if( (pp->std != std) || (pp->output != output) ) {
		if(ISDTV(std)) {
			wReg32(0x130, 0x200);
		} else {
			wReg32(0x130, 0x1c0);
		}
	}

	if(!ISCVBS(output)) {
		/* If output voltage settings. */
		if(ISDTV(std)) {
			if(rffrequency >= 300000000) {
				wReg32(0x164, 0x500);
			} else {
				wReg32(0x164, 0x600);
			}
		}
	}

	if(pp->output != output) {
		val32 = rReg32(0x234);
		val32 &= ~(7ul << 25);
		if(ISCVBS(output)) {
			if(output == nCvbsBBAud) {
				val32 |=  (2ul << 25);
			} else {
				/* keep 0x234[27:25] = 0. */
			}
		} else {
			val32 |=  (4ul << 25);
		}
		wReg32(0x234, val32);

		if(ISCVBS(output)) {
			wReg32(0x20c, 0x100);
		} else {
			wReg32(0x20c, 0x400);
		}
	}

	/* ADEC mode */
	if( (pp->std != std) || (pp->output != output) ) {
		val32 = rReg32(0x280);
		if(output == nCvbsSif) {
			val32 &= ~(1ul << 0);
		} else if(output == nCvbsBBAud) {
			val32 |= (1ul << 0);
		} else if(output == nVifAif) {
			if(ISNM131(pp->chipid)) {
				val32 &= ~(1ul << 0);
			} else {
				/*NA*/
			}
		} else {
			/*NA*/
		}			
		wReg32(0x280, val32);

		// one time
		/* ADEC DAGC target */
		val32 = rReg32(0x238);
		val32 &= ~0x3fff;
		if(output == nVifAif) {
			val32 |= 0x800;
		} else if(output == nCvbsSif) {
			val32 |= 0x800;
		} else if(output == nCvbsBBAud) {
			val32 |= 0x80;
		} else {
			/*NA*/
		}			
		wReg32(0x238, val32);		


		/* DAC1 inversion */
		/* DAC2 inversion */
		// one time
		val32 = rReg32(0x32c);
		val32 &= ~( (1ul << 14) | ( 1ul << 30) );
		if(ISCVBS(output)) {
			val32 |= ( (1ul << 14) | (1ul << 30) );
		} else {
		}			
		wReg32(0x32c, val32);
	}

	if(is_stereo) {
		if ((std == nNTSC)||(std == nFM_RADIO)) {
			audio_offset = 112106; /* (4724212-4500000)/2 */
		} else {		
			audio_offset= 121093; /* 1/64e-6*15.5/2 */
		}
	} else {
		audio_offset = 0;
	}

	{

		uint32_t audio_ddfs;
		uint32_t aci_audio;

		if(is_stereo) {
			if (std == nNTSC) {
				/**
				audio_offset=(4724212-4500000)/2;
				audio_ddfs = (uint32_t) (audio_offset/(13.5e6/524288));				
				**/			
				audio_ddfs = 4353;
			} if(std == nFM_RADIO) {
				/**
				audio_offset=(4724212-4500000)/2;
				audio_ddfs = (uint32_t) (audio_offset/(13.5e6/524288))*128/450;
				**/			
				audio_ddfs = 1238;

			} else {
				/**
				audio_offset=1/64e-6*15.5/2;
				audio_ddfs=	(uint32_t) (audio_offset/(13.5e6/524288));				
				**/
				audio_ddfs = 4702;
			}
		} else {
			audio_ddfs = 0;
		}

		/**		
		If 0x230[18:0] max. value is 0x7ffff = 19.0 bits.
		then (audio_ddfs+adec_ddfs_fq[std]*2) = 0x230[18:0] * (1+MAX_CLK_OFFSET) = 19.10 bits.
		where MAX_CLK_OFFSET = 0.075269.		
		However:
		adec_ddfs_fq[std]: 17.0
		audio_ddfs: 13.0
		audio_ddfs+adec_ddfs_fq[std]*2: 18.0 and and does not use
		all the allowed 19.10 bits.
		**/
		/* audio_ddfs =	(uint32_t)(1.0 * ddfs/(1 + clk_offset)); */
		audio_ddfs = ((audio_ddfs + (adec_ddfs_fq[std] << 1)) << 14)/((1ul << 14) + (clk_off_f/(216000 >> 5)));
		audio_ddfs |= (1ul << 19);
		wReg32(0x230, audio_ddfs);

		if(tuneMode == nFmScan) {
			wReg32(0x250, 0x02);
		} else {
			aci_audio=ACI_audio_lut[std];
			if ((aci_audio==0) && (is_stereo==1))
				aci_audio=2;
			wReg32(0x250,aci_audio);
		}


	}

	{
		uint32_t  ddfs;
		/**
		DDFS
		**/
		ddfs = ddfs_lut[std];
		/**
		If 0x1bc[19:0] max value is 0xfffff = 20.0 bits.
		then ddfs = 0x1bc[19:0] * (1+MAX_CLK_OFFSET) = 20.10 bits.
		where MAX_CLK_OFFSET = 0.075269.
		However, ddfs_lut[std] is only 18.0 bits and does not use
		all the allowed 20.10 bits.		
		**/

		/* ddfs =	(uint32_t)(1.0 * ddfs/(1 + clk_offset)); */
		ddfs =	(ddfs << 14)/((1ul << 14) + (clk_off_f/(216000 >> 5)));
		if(rfinvert) {
			ddfs |= ((1ul << 21) | (1ul << 20));
		}
		wReg32(0x1bc, ddfs);

	}

	if(pp->std != std) {
		if (std == nFM_RADIO) {
			wReg32(0x1c8, 0x8000);
			wReg32(0x1cc, 0x8000);
			wReg32(0x1d0, 0x8000);
			wReg32(0x110, 0x2);	//songbin 120518
			pp->dconotch_ctl = 0x2;//songbin 120518
			nmi_debug(N_INFO, "*** Notch Disable ***\n");
			wReg32(0x26c, 0);
			wReg32(0x270, 5);
		} else {
			wReg32(0x1c8, 0x8079);
			wReg32(0x1cc, 0x8079);
			wReg32(0x1d0, 0x8079);
			if(std==nPAL_G||std==nPAL_K||std==nPAL_I)//songbin 120518
			{
				wReg32(0x110, 0x6c50);
				nmi_debug(N_INFO, "*** Notch Disable ***\n");
				pp->dconotch_ctl = 0x6c50;
			}
			else
			{
				wReg32(0x110, 0x4c52);
				nmi_debug(N_INFO, "*** Notch Disable ***\n");
				pp->dconotch_ctl = 0x4c52;
			}
			wReg32(0x26c, 2);
			wReg32(0x270, 6);
		}
	}
	
	/**
	CVBS
	**/
	if(ISCVBS(output))
	{
		uint32_t cvbs_a_ddfs;
		if(pp->output != output) {
			wReg32(0x21c, 0x30000000); //CVBS video
		}		

		// CVBS audio
		// every time.
		cvbs_a_ddfs=cvbs_ddfs_audio_out_lut[std];
		/**
		If 0x234[21:0] = 0x3fffff : 22.0 bits.
		then cvbs_a_ddfs = 0x234[21:0] * (1+MAX_CLK_OFFSET) = 22.10 bits.
		where MAX_CLK_OFFSET = 0.075269.	
		However, cvbs_ddfs_audio_out_lut[std] is only 17.0 bits and does not use
		all the allowed 22.10 bits.
		**/	
		/* cvbs_a_ddfs=(uint32_t)(1.0 * cvbs_a_ddfs/(1 + clk_offset)); */
		cvbs_a_ddfs = (cvbs_a_ddfs << 15) /((1 << 15) + (clk_off_f/3375));

		val32 = rReg32(0x234);
		val32 &= ~(0x3ffffful);
		val32 |= cvbs_a_ddfs;
		val32 &= ~( 0x3ul << 28);		
		/* AIF DDFS zero frequency */
		if (output == nCvbsBBAud) {
			val32 |= (1ul << 28);
		}
		wReg32(0x234, val32);

	} else if (output == nIf) {

		uint32_t vddfs_f;
		/*  
		If 0x21c[21:0] max. value is 0x3fffff = 22 bits.
		then 
		(vif+rf_freq_offset_lut[std]) = 0x21c[21:0] * (1+MAX_CLK_OFFSET)*(216000000/4194304) = 27.79 bits,
		where MAX_CLK_OFFSET = 0.075269.
		then (vif+rf_freq_offset_lut[std])/1000 = 17.82 bits.
		(vif+rf_freq_offset_lut[std]) >> 3 = 14.82 bits.
		*/
		if(!rfinvert) {
			vif += rf_freq_offset_lut[std];		
		} else {
			vif -= rf_freq_offset_lut[std];		
		}
		/* vddfs=1.0*(vif+rf_freq_offset_lut[std])/(1 + clk_offset)/(216e6/ 4194304)+0.5; */
		vif /= 1000; /* in KHz. */
		/*vif should be shifted right by 16 bits, but since vif max. vallue is 60000KHz,
		the MSB bit will be truncated. So it is left shifted by 16, then vddfs_f is left
		shifted by 1 after the division*/
		vddfs_f = ( (vif << 16)/(((216000) >>5) + ((clk_off_f) >>14)) );
		vddfs_f = vddfs_f << 1;

		val32=rReg32(0x21c);
		val32 &= ~(0x3ffffful << 0);
		val32 |= vddfs_f;
		val32 &= ~(0x3ul << 28);
		val32 |= (0x4ul << 25);

		/* TODO: check if clearing bit 22 should be appplied for CVBS only. */
		val32 &= ~(1ul << 22); /* Make sure NCO freq. is not negated.  */
		wReg32(0x21c, val32);

		val32 = rReg32(0x234);
		val32 &= ~(0x3ffffful << 0);		
		val32 &= ~(0x3ul << 28);	
		wReg32(0x234, val32);

	} else if (output == nVifAif) {

		uint32_t vddfs_f, addfs_f;
		
		/*  
		If 0x21c[21:0] max. value is 0x3fffff = 22 bits.
		then 
		(vif) = 0x21c[21:0] * (1+MAX_CLK_OFFSET)*(216000000/4194304) = 27.79 bits,
		where MAX_CLK_OFFSET = 0.075269.
		then (vif)/1000 = 17.82 bits.
		(vif) >> 3 = 14.82 bits.
		*/
		/* vddfs=1.0*(vif)/(1 + clk_offset)/(216e6/ 4194304)+0.5; */
		vif /= 1000; /* in KHz. */
		vif >>= 3; /* conserve 3-bits to increase precision. Error between +(1/8000)/2 Hz and -(1/8000)/2 Hz*/
		vddfs_f = ( (vif << 17)/((216000 >> 8) + (clk_off_f >> 17)) );

		val32=rReg32(0x21c);
		val32 &= ~(0x3ffffful << 0);
		val32 |= vddfs_f;		
		val32 &= ~(0x3ul << 28);
		val32 |= (0x4ul << 25);

		/* TODO: check if clearing bit 22 should be appplied for CVBS only. */
		val32 &= ~(1ul << 22); /* Make sure NCO freq. is not negated.  */
		wReg32(0x21c,val32);

		/* aif is 22 bits */
		if(is_stereo) {
			aif += audio_offset;
		}
		/*  
		If 0x234[21:0] max. value is 0x3fffff = 22 bits.
		then 
		(aif+audio_offset) = 0x234[21:0] * (1+MAX_CLK_OFFSET)*(216000000/4194304) = 27.79 bits,
		where MAX_CLK_OFFSET = 0.075269.
		then (aif+audio_offset)/1000 = 17.82 bits.
		(aif+audio_offset) >> 3 = 14.82 bits.
		*/
		/* addfs=1.0*(aif+audio_offset)/(1 + clk_offset)/(216e6/ 4194304)+0.5; */
		aif /= 1000; /* in KHz. */
		aif >>= 3; /* conserve 3-bits to increase precision. Error between +(1/8000)/2 Hz and -(1/8000)/2 Hz*/
		addfs_f = ( (aif << 17)/((216000 >> 8) + (clk_off_f >> 17)) );

		val32 = rReg32(0x234);
		val32 &= ~(0x3ffffful << 0);
		val32 |= addfs_f;
		val32 &= ~(0x3ul << 28);
		wReg32(0x234, val32);
	}


	if(pp->std != std) {
		if ((std == nPAL_L) || (std == nSECAM_L)) {
		#if 1
			val32 = rReg32(0x12c);
			val32 &= ~(0x7ul << 12);
			val32 &= ~(1ul << 7);
			wReg32(0x12c, val32);

			wReg32(0x138, (0x16ul << 5) | (0x16ul << 10) | (0x16ul << 0));
			wReg32(0x148, 0x1001);
			//wReg32(0x148, 0x1ff082);
		#else//swan
			val32 = rReg32(0x12c);
			val32 &= ~(0x7ul << 12);
			//val32 |= (1ul << 12);
			val32 &= ~(1ul << 7);
			wReg32(0x12c, val32);

			wReg32(0x138, (0x18ul << 5) |(0x16ul << 10) | (0x18ul << 0));
			wReg32(0x148, 0x1ff082);
		#endif
		} else {
			/* POR values. */
			val32 = rReg32(0x12c);
			val32 &= ~(0x7ul << 12);
			val32 |= (1ul << 12);
			val32 &= ~(1ul << 7);
			wReg32(0x12c, val32);

			wReg32(0x138, (0x18ul << 5) |(0x16ul << 10) | (0x18ul << 0));
			wReg32(0x148, 0x1ff082);
		}
	}


	/* Manipulate register 0x200 */
	if( (pp->std != std) || (pp->output != output) || ISCVBS(output)) {
		val32 = rReg32(0x200);
		if ((std == nPAL_L) || (std == nSECAM_L)) {			
			if (ISCVBS(output)) {				
				val32 &= ~(1ul << 15);				
			} else {				
				val32 |= (1ul << 15);				
			}			
		} else {			
			val32 |= (1ul << 15);			
		}

		val32 &= ~(0x3ffful << 0);
		if(!ISCVBS(output)) {
			val32 |= (0x800ul << 0);
		} else {
			if(pp->cvbsBrt > 32) {
				pp->cvbsBrt = 32;
			}
			/*Yangru's formula: 0xa00 + 0x40 *x where x can be any number in
			[-16, -15, ? 0, 1, 2, .. 16]*/		
			val32 |= (0x600ul + (((uint32_t)pp->cvbsBrt) << 6));
		}

		wReg32(0x200, val32);
	}

	{
		if ((std == nNTSC)||(std == nFM_RADIO)) {
			/* val32 = (((1+clkOff)*858) << 4) + 3*/
			val32 = ((216000ul << 4) + (clk_off_f >> 5))*858ul;
			val32 = (val32/216000ul) & ~(0xful);
			val32 |= 0x3ul;
			val32 &= ~(0x1fful << 16);
		} else {
			/* val32 = (((1+clkOff)*864) << 4) + 3*/
			val32 = ((216000ul << 4) + (clk_off_f >> 5))*864ul;
			val32 = (val32/216000ul) & ~(0xful);
			val32 |= 0x3ul;
			val32 &= ~(0x1fful << 16);
			if ((std == nPAL_L) || (std == nSECAM_L)) {
				val32 |= (0x139ul << 16);//swan
			} 
		}
		wReg32(0x210, val32);
	}

	val32 = rReg32(0x104);

	val32 |= (1ul << 0);

	val32 &= ~(0x0ful << 27);
	val32 |= (1ul << 28);

	/**
	Soft reset the demod.		
	**/
	val32 |= (1ul << 4);

	/**
	Clear data_stop_val output.
	Clear Reset the PLL 104[5]=0
	**/
	val32 &= ~ ((1ul << 29) | (1ul << 5));


	/**
	Gated clocks management:
	**/
	val32 &= ~(0x7ul << 1); 

	if ((output == nIf) && ISDTV(std)) {
	} else {
		val32 |= (1ul << 1);
	}
	if(output == nIf) {
	} else {
		val32 |= (1ul << 2);
	}
	if(output == nCvbsBBAud) {
		val32 |= (1ul << 3);
	}

	{
		uint32_t agc, aci; 
		aci = aci_lut[std];	
		agc = agc_mode[std];

		if 	(agc == 0) {
			if(clk_off_f > 2764800 /* 0.025 */ ) {
				aci += 1;
			}
		}

		/**
		ACI 
		**/
		val32 &= ~(0xful << 11);
		val32 |= (aci << 11);

		/**
		AGC
		**/
		val32 &= ~(1ul << 15);
		val32 |= (agc << 15);
	}


	{
		uint32_t avsep;
		if (ISCVBS(output)) {

			avsep = avsep_real[std];
			if(clk_off_f > 2764800 /* 0.025 */ )
			{
				avsep += 1;
			}
		} else {

			avsep = avsep_comp[std];

			if(clk_off_f > 3686396 /* 0.0333333 */) {
				avsep += 2;		
			} else if (clk_off_f  > 1843192 /* 0.0166666 */) 	{
				avsep += 1;
			}
		}
		/**
		AVSEP
		**/
		val32 &= ~(0xful << 16);
		val32 |= (avsep << 16);
	}

	/**
	OUTPUT MUX SETTINGS
	**/
	{
		val32 &= ~(0x3ul << 20);  
		val32 &= ~(0xful << 22);
		/**
		CVBS
		**/
		if(ISCVBS(output)) {
			val32 |= (0x6ul << 22); /* 0110 */		
		} else if (output == nIf) {					
			if (ISDTV(std)) {
				val32 |= (0x2ul << 20);
			} else {
				val32 |= (0x2ul << 20);
			}

			if( ISNM120(pp->chipid) || ISNM130(pp->chipid))  {
				val32 |= (0x2ul << 22);
			} else if(ISNM131(pp->chipid) || ISNM130v(pp->chipid)) {
				if(dacSel == nDacDefault)
				{
					val32 |= (0x9ul << 22);
				}
				else if(dacSel == nDac1)
				{
					val32 |= (0x2ul << 22);
				}
				else if(dacSel == nDac2)
				{
					val32 |= (0x8ul << 22);
				}
				else if(dacSel == nDacBoth)
				{
					val32 |= (0xaul << 22);
				}
			} else {			
				/* Illegal case. */				
			}
		} else if (output == nVifAif) {
			if(ISATV(std)) {
				val32 |= (0x1ul << 20); /* AREJ (VIF output) */
				val32 |= (0x6ul << 22);
			} else {
				/* Illegal condition. */
			}
		}		
	}

	wReg32(0x104, val32);

	/**
	Release demod soft reset.
	**/
	val32 &= ~(1ul << 4);

	/**
	Set data_stop_val output.
	Set Reset the PLL 104[5]=1
	**/
	val32 |=  ((1ul << 29) | (1ul << 5));


	wReg32(0x104, val32);

	/**
	Check if pll did not settle, then reset it again.
	**/
	nmi_delay(1);

	if(rReg32(0x328) != 0) {
		val32 &= ~(1ul << 5);
		wReg32(0x104, val32);

		val32 |= (1ul << 5);
		wReg32(0x104, val32);
	}

}
/**
Returns the dagc gain in format (u10.15)
**/
static u17_15_t nm131_demod_dagc_gain(void)
{
	uint32_t gain;
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;


	if(agc_mode[pp->std] == 0) { /* ATV AGC */
		gain = rReg32(0x15c); /* 22 bit */
		/* return (double)gain/(1ul << 12); */
		return gain << 3;
	} else { /* DTV AGC*/
		gain = rReg32(0x194); /* 25 bit */		
		/* return (double)gain/(1ul << 15); */
		return gain;
	}
}

static bool_t nm131_demod_get_agc_lock(void)
{
	uint32_t mode, lock;

	mode = rReg32(0x104);
	mode &= (1ul << 15);

	if (mode == 0) {
		/* ATV mode */
		lock = rReg32(0x154);
	} else {
		/* DTV mode */
		lock = rReg32(0x18c);
	}

	if  (lock != 1)
		return 0;

	return 1;
}

static bool_t nm131_demod_get_cpll_lock(void)
{
	uint32_t lock;

	lock = rReg32(0x1e0);
	if (lock != 1)
		return 0;

	return 1;
}

static int16_t nm131_demod_get_snr(void)
{
	uint32_t r32;
	int16_t snrx100, factor;
	uint32_t sig, noise;

	r32 = rReg32(0x218);
	sig = r32 & 0xffff;
	noise = (r32 >> 16) & 0xffff;
	/* TODO: come up with factor values. */
	factor = 0;

	if (sig == 0) {
		snrx100 = -600;
	} else if (noise == 0) {
		snrx100 = 6000;
	} else {
		u17_15_t value;

		value = sig << 15;
		value /= noise;
		snrx100 = 25*nmi_log10(value)+factor;
	}

	return snrx100;
}

static int32_t nm131_demod_get_freq_offset(void)
{
	uint32_t offset_f;

	offset_f = rReg32(0x1e8);

	offset_f = (offset_f >= (1ul << 29)) ? ((offset_f) - (1ul << 30)) : offset_f;
	/* offset = (13.5e6 * offset)/(1ul << 30)/(1ul << 5); */
	offset_f <<= 2;	
	offset_f /= (10180);	

	return offset_f;
}

static int16_t nm131_demod_get_pll_level(void)
{
	uint32_t val32;
	int16_t alocklevel;

	val32 = rReg32(0x1ec);
	alocklevel = (int16_t)((val32 >> 10) & 0x3ff);
	alocklevel = (alocklevel >= 512) ? (alocklevel - 1024) : alocklevel;	

	return alocklevel;
}

static void nm131_demod_soft_reset(void)
{
	uint32_t r32;

	r32 = rReg32(0x104);

	r32 |= 0x1;
	wReg32(0x104, r32);
	r32 |=	(1ul << 4);
	wReg32(0x104, r32);

	r32 &= ~(1ul << 4);
	wReg32(0x104, r32);

	r32 &= ~(0x0ful << 27);
	r32 |= (1ul << 28) + (1ul << 29);
	wReg32(0x104, r32);
	r32 &= ~(1ul << 29);
	wReg32(0x104, r32);
	r32 |= (1ul << 29);
	wReg32(0x104, r32);

}

static void nm131_demod_soft_reset_mosaic(void)
{
	uint32_t val32;

      val32 = rReg32(0x104);

      /** Clear Reset the PLL 104[5]=0 **/

      val32 &= ~ (1ul << 5);

      wReg32(0x104, val32);

      nmi_delay(10);

      /** Set Reset the PLL 104[5]=1 **/

      val32 |=  (1ul << 5);

      wReg32(0x104, val32);

	  nmi_delay(10);

      /** Soft reset the demod. **/

      val32 |= (1ul << 4);

      wReg32(0x104, val32);

      nmi_delay(10);

      /** Release demod soft reset. **/

      val32 &= ~(1ul << 4);

      wReg32(0x104, val32);


}
static void nm131_demod_get_status(tTnrDemodStatus *p)
{
	p->agclock = nm131_demod_get_agc_lock();
	p->cplllock = nm131_demod_get_cpll_lock();
	p->dagc = nm131_demod_dagc_gain();
	p->dsnrx100 = nm131_demod_get_snr();
	p->fqoff = nm131_demod_get_freq_offset();
	p->plllvl = nm131_demod_get_pll_level();
}

/******************************************************************************
**
**	Tuner
**
*******************************************************************************/
static void nm131_set_lna_gain(tNmiLnaGain g)
{
	uint8_t val8;

	val8 = rReg8(0x2b);
	val8 &= ~0x1f;
	val8 |= (1ul << 5);
	if (g == nHiGain) {
		val8 |= 0x11;
	} else if (g == nMiGain) {
		val8 |= 0x10;
	} else if (g == nLoGain) {
		val8 |= 0xf;
	} else if (g == nBypass) {
		val8 |= 0x0e;
	} else if (g == nAtten6) {
		val8 |= 0xd;
	} else if (g == nAtten12) {
		val8 |= 0xc;
	}	else if (g == nAtten18) {
		val8 |= 0xb;
	}	else {
		val8 &= ~(1ul << 5); 
	}				
	wReg8(0x2b, val8);
}

static void nm131_set_lna_gain2(uint8_t g)
{
	uint8_t val8;

	val8 = rReg8(0x2b);
	val8 &= ~ (0x1f | (1 << 7));
	val8 |= (1ul << 5);
	val8 |= g & 0x1f;
	wReg8(0x2b, val8);
}

static void mn131_get_rssi(tTnrGain *pg)
{	
	int16_t rssi_offsetx100, dagcdbx100;
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;

	if(pp->std == nFM_RADIO) {
		u17_15_t dagc;
		dagc = nm131_demod_dagc_gain();
		dagcdbx100 = 25*nmi_log10(dagc);
		dagc >>= 15;
		if ((pp->frequency > 94400000) && (pp->frequency <= 100100000)) {
			if ((dagc > 99) && (dagc <= 119)) { rssi_offsetx100 = 260;
			} else if  ((dagc > 119) &&  (dagc <= 135)) {  rssi_offsetx100 = 140;
			} else if  ((dagc > 135) &&  (dagc <= 148)) {  rssi_offsetx100 = 0;
			} else if  ((dagc > 148) &&  (dagc <= 158)) {  rssi_offsetx100 =  -200;
			} else if  ((dagc > 158) &&  (dagc <= 164)) {  rssi_offsetx100 =  -400;
			} else if   (dagc > 164) { rssi_offsetx100 = -700;
			} else /* if(dagc <= 99) */ {
				if  ((pg->bblicode == 0xf1) || (pg->bblicode == 0xf0)) { rssi_offsetx100 = 430;
				} else if  (pg->bblicode == 0xef) { rssi_offsetx100 = 520;
				} else { rssi_offsetx100 = 340;
				}
			}
		} else {
			if ((dagc > 112) && (dagc <= 142)) { rssi_offsetx100 = 380;
			} else if  ((dagc > 142) &&  (dagc <= 176)) {  rssi_offsetx100 = 330;
			} else if  ((dagc > 176) &&  (dagc <= 206)) {  rssi_offsetx100 = 250;
			} else if  ((dagc > 206) &&  (dagc <= 232)) {  rssi_offsetx100 = 110;
			} else if  ((dagc > 232) &&  (dagc <= 252)) {  rssi_offsetx100 = -240;
			} else if  (dagc > 252) { rssi_offsetx100 = -500;
			} else /* if(dagc <= 112) */ {
				if  ((pg->bblicode == 0xf1) || (pg->bblicode == 0xf0)) { rssi_offsetx100 = 430;
				} else if  (pg->bblicode == 0xef) { rssi_offsetx100 = 520;
				} else { rssi_offsetx100 = 340;
				}
			}
		}

		pg->rssix100 = rssi_offsetx100 - (
			pg->lnadbx100+
			pg->bblidbx100+
			dagcdbx100);

	} else if(ISDTV(pp->std)) {
		if(pp->frequency < 131000000) {
			rssi_offsetx100 = 1450;
		} else if (pp->frequency < 275000000 && 131000000 <= pp->frequency) {
			if  ( pg->bblicode == 0xf1) {
				rssi_offsetx100 = 1200;
			} else {
				rssi_offsetx100 = 1300;
			}
		} else if (pp->frequency < 350000000 && 275000000 <= pp->frequency ) {
			if  (pg->bblicode == 0xf1) {
				rssi_offsetx100 = 1050;
			} else { 
				rssi_offsetx100 = 1150;
			}
		} else if (pp->frequency < 450000000 && 350000000 <= pp->frequency ) {
			if(pg->bblicode == 0xf1) {
				rssi_offsetx100 = 1000;
			} else { 
				rssi_offsetx100 = 1200;
			}
		} else if (pp->frequency < 570000000 && 45000000 <= pp->frequency ) {
			if (pg->bblicode == 0xf1) { 
				rssi_offsetx100 = 1100;
			} else { 
				rssi_offsetx100 = 1250;
			}
		} else if (pp->frequency < 720000000 && 570000000 <= pp->frequency) {
			if  (pg->bblicode == 0xf1) {
				rssi_offsetx100 = 1150;
			} else {
				rssi_offsetx100 = 1350;
			}
		} else /* if (720000000 <= pp->frequency) */  {
			if  (pg->bblicode == 0xf1) { 
				rssi_offsetx100 = 1300;
			} else {
				rssi_offsetx100 = 1450;
			}
		} 

		dagcdbx100 = 25*nmi_log10(nm131_demod_dagc_gain());
		pg->rssix100 = rssi_offsetx100 - (
			pg->lnadbx100+
			pg->bblidbx100+
			(dagcdbx100 + /*100*20*nmi_log10(8)*/1806));
	} else {
		if  (pp->frequency < 125000000) {
			rssi_offsetx100 = -75;
		} else if (pp->frequency < 403000000 && 125000000 <= pp->frequency) {
			rssi_offsetx100 = -250;
		} else if (pp->frequency < 570000000 && 403000000 <= pp->frequency) {
			if (pg->bblicode == 0xf1) {
				rssi_offsetx100 = -200;
			} else {
				rssi_offsetx100 = -100;
			}
		} else if (pp->frequency < 760000000 && 570000000 <= pp->frequency) {
			if (pg->bblicode == 0xf1) {
				rssi_offsetx100 = -150;
			} else {
				rssi_offsetx100 = -30;
			}
		} else /* if(760000000 <= pp->frequency) */ {
			if (pg->bblicode == 0xf1) {
				rssi_offsetx100 = -50;
			} else {
				rssi_offsetx100 = 50;
			}
		}
		dagcdbx100 = 25*nmi_log10(nm131_demod_dagc_gain());			
		pg->rssix100 = rssi_offsetx100 - (
			pg->lnadbx100+
			pg->bblidbx100+
			dagcdbx100);		
	} 
}

static void nm131_get_lna_gain(tTnrGain *pg)
{
	uint32_t gain, val1, val2, val3;

	gain = rReg8(0x3e);

	val3 = rReg8(0x2d);
	if(val3 == 0) {
		switch (gain) 
		{
		case 0x3:
			pg->lnadbx100 = -900;
			pg->lnacode = 0xe2;
			break;
		case 0x7:
			pg->lnadbx100 = -400;
			pg->lnacode = 0xe3;
			break;
		case 0xf:
			pg->lnadbx100 = 100;
			pg->lnacode = 0xe4;
			break;
		case 0x1f:
			pg->lnadbx100 = 600;
			pg->lnacode = 0xe5;
			break;			
		case 0x3f:
			pg->lnadbx100 = 1200;
			pg->lnacode = 0xe6;
			break;
		case 0x7f:
			pg->lnadbx100 = 1700;
			pg->lnacode = 0xe7;
			break;			
		default:
			pg->lnadbx100 = -900;
			pg->lnacode = 0xe2;
			break;
		}
	} else {
		switch (gain) 
		{
		case 0x3:
			pg->lnadbx100 = -900;
			pg->lnacode = 0xe3;
			break;
		case 0x5:
			pg->lnadbx100 = -700;
			pg->lnacode = 0xe4;
			break;
		case 0x7:
			pg->lnadbx100 = -400;
			pg->lnacode = 0xe5;
			break;
		case 0xb:
			pg->lnadbx100 = -100;
			pg->lnacode = 0xe6;
			break;
		case 0xf:
			pg->lnadbx100 = 100;
			pg->lnacode = 0xe7;
			break;
		case 0x17:
			pg->lnadbx100 = 300;
			pg->lnacode = 0xe8;
			break;
		case 0x1f:
			pg->lnadbx100 = 600;
			pg->lnacode = 0xe9;
			break;
		case 0x2f:
			pg->lnadbx100 = 900;
			pg->lnacode = 0xea;
			break;
		case 0x3f:
			pg->lnadbx100 = 1200;
			pg->lnacode = 0xeb;
			break;
		case 0x5f:
			pg->lnadbx100 = 1400;
			pg->lnacode = 0xec;
			break;			
		case 0x7f:
			pg->lnadbx100 = 1700;
			pg->lnacode = 0xed;
			break;			
		default:
			pg->lnadbx100 = -900;
			pg->lnacode = 0xe3;
			break;
		}
	}


	val1 = rReg8(0x40);
	val2 = rReg8(0x41);
	gain = ((val2 >> 5) & 0x7) | (val1 << 3);

	switch (gain) {
	case 0x7ff:
		pg->bblidbx100 = 3480;
		pg->bblicode	= 0xf1;
		break;
	case 0x3ff:
		pg->bblidbx100 = 2860;
		pg->bblicode 	= 0xf0;
		break;
	case 0x1ff:
		pg->bblidbx100 = 2280;
		pg->bblicode 	= 0xef;
		break;
	case 0xff:
		pg->bblidbx100 = 1670;
		pg->bblicode 	= 0xee;
		break;
	case 0x7f:
		pg->bblidbx100 = 1370;
		pg->bblicode 	= 0xed;
		break;
	case 0x5f:
		pg->bblidbx100 = 1200;
		pg->bblicode = 0xec;
		break;
	case 0x3f:
		pg->bblidbx100 = 950;
		pg->bblicode 	= 0xeb;
		break;
	case 0x2f:
		pg->bblidbx100 = 750;
		pg->bblicode 	= 0xea;
		break;
	case 0x1f:
		pg->bblidbx100 = 450;
		pg->bblicode	= 0xe9;
		break;
	case 0x17:
		pg->bblidbx100 = 240;
		pg->bblicode	= 0xe8;
		break;
	case 0xf:
		pg->bblidbx100 = -90;
		pg->bblicode = 0xe7;
		break;
	case 0xb:
		pg->bblidbx100 = -350;
		pg->bblicode	= 0xe6;
		break;	
	case 0x7:
		pg->bblidbx100 = -700;
		pg->bblicode	= 0xe5;
		break;
	case 0x5:
		pg->bblidbx100 = -900;
		pg->bblicode	= 0xe4;
		break;
	case 0x3:
		pg->bblidbx100 = -1230;
		pg->bblicode	= 0xe3;
		break;
	case 0x2:
		pg->bblidbx100 = -1500;
		pg->bblicode	= 0xe2;
		break;
	case 0x1:
		pg->bblidbx100 = -1800;
		pg->bblicode	= 0xe1;
		break;
	case 0x0:
		pg->bblidbx100 = -2000;
		pg->bblicode	= 0xe0;
		break;
	default:
		pg->bblidbx100 = 9900;
		pg->bblicode	= 0x00;
		break;
	}

	mn131_get_rssi(pg);

	return;	
}

static tNmiSwrfliArg SwrfliArg=
{
	.bbli_upper = 0xf0,
	.bbli_lower = 0xea,
	.bbli_upper2 = 0xf0,
	.bbli_lower2 = 0xef,
	.bbli_avg_enable = 0,
	.bbli_avg_weight = 1*32768,
	.dagc_avg_enable = 0,
	.dagc_avg_weight = 1*32768,
	.use_dagc = 0,
	.dagc_upper = 4*32768,
	.dagc_lower = 2*32768,
};

void nm120_rfli_track(void)
{
	int action;
	static uint8_t bblicode = 0;
	static u17_15_t dagcgain = 0;

	static uint8_t lnagain = 0x3;

	/*tNmiSwrfliArg p;
	p.bbli_upper = 0xf0;
	p.bbli_lower = 0xea;
	p.bbli_upper2 = p.bbli_upper;
	p.bbli_lower2 = 0xef;
	p.bbli_avg_enable = 1;
	p.bbli_avg_weight = 1*32768;
	p.dagc_avg_enable = 1;
	p.dagc_avg_weight = 1*32768;
	p.dagc_upper = 4*32768;
	p.dagc_lower = 2*32768;*/

	tNmiSwrfliArg *p = &SwrfliArg;
	
	do
	{
		tTnrGain g;

		nm131_get_lna_gain(&g);

		if(p->bbli_avg_enable) {		
			bblicode = ( ((((uint32_t)g.bblicode)*p->bbli_avg_weight) 
				+ (((uint32_t)bblicode) * ((1ul << 15) - p->bbli_avg_weight))) >> 15);
		} else {
			bblicode  = g.bblicode;
		}
	} while(0);
	
	do
	{
		u17_15_t tmp;

		tmp = nm131_demod_dagc_gain();

		if(p->dagc_avg_enable) {		
			dagcgain = ( ( (((uint32_t)tmp)*p->dagc_avg_weight) 
				+ (((uint32_t)dagcgain) * ((1ul << 15) - p->dagc_avg_weight))) >> 15);
		} else {
			dagcgain  = tmp;
		}
	} while(0);
	
	if(p->use_dagc) {
		if( (bblicode > p->bbli_upper) && (dagcgain > p->dagc_upper)) {
			action = 1;
		} else if( (bblicode < p->bbli_lower) && (dagcgain < p->dagc_lower)) {
			action = -1;
		} else {			
			action = 0;
		}
	} else {

		if(lnagain < 0xd) {
			if(bblicode > p->bbli_upper) {
				action = 1;
			} else if(bblicode < p->bbli_lower) {
				action = -1;
			} else {			
				action = 0;
			}
		} else { 
			if(bblicode > p->bbli_upper2) {
				action = 1;
			} else if(bblicode < p->bbli_upper2) {
				action = -2;
			} else {			
				action = 0;
			}
		}

	}
	
	if(action > 0) {
		lnagain++;
		if(lnagain > 0xd) lnagain = 0xd;
		nm131_set_lna_gain2(lnagain);
	} else if(action < 0) {
		if(action != -2) {
			lnagain--;
			if(lnagain < 0x3) lnagain = 0x3;
		} else {
			lnagain = 0x9;
		}
		nm131_set_lna_gain2(lnagain);

	} else {
		lnagain = rReg8(0x2b) & 0x0f;
	}	
}

static void nm131_invert_spectum(int invert)
{
	uint32_t val32;
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;

	val32 = rReg32(0x21c);
	if(invert == 0) {		
		val32 &= ~(1ul << 22); /* Make sure NCO freq. is not negated.  */
	} else {		
		val32 |= (1ul << 22); /* Negate NCO freq. */
	}

	if(pp->output == nIf) {
		uint32_t vddfs_f;
		uint32_t vif;

		vddfs_f = val32 & 0x3ffffful;
		/* vif = (rf_freq_offset_lut[std]*2)/(1+clk_offset); */
		vif = rf_freq_offset_lut[pp->std]/1000; /* in KHz. */
		vif >>= (3-1); /* Conserve 3-bit and multiply by 2. */
		if(invert == 0) {
			if(pp->rfinvert == 0) {
				vddfs_f += ( (vif << 17)/((216000 >> 8) + (pp->clk_off_f >> 17)) );
			} else {
				vddfs_f -= ( (vif << 17)/((216000 >> 8) + (pp->clk_off_f >> 17)) );
			}
		} else {
			if(pp->rfinvert == 0) {
				vddfs_f -= ( (vif << 17)/((216000 >> 8) + (pp->clk_off_f >> 17)) );
			} else {
				vddfs_f += ( (vif << 17)/((216000 >> 8) + (pp->clk_off_f >> 17)) );
			}
		}

		val32 &= ~(0x3ffffful << 0);
		val32 |= (vddfs_f & 0x3ffffful);
	}

	wReg32(0x21c,val32);
}

static void nm131_tuner_apply_vhf_filter(uint32_t rffrequency)
{
	size_t i;

	for(i=0; 
		i<((sizeof(vhf_filter_cutoff_codes)
		/sizeof(vhf_filter_cutoff_codes[0]))-1); 
	i++) {
		if( (rffrequency > vhf_filter_cutoff_codes[i].frequency) 
			&& (rffrequency <= vhf_filter_cutoff_codes[i+1].frequency) ) {
				break;
		}
	}		

	wReg8(0x08, vhf_filter_cutoff_codes[i].val8_0x08);
	wReg8(0x09, vhf_filter_cutoff_codes[i].val8_0x09);
}

static void nm131_tuner_config(uint32_t rffrequency, tNmiTvStd std, tNmiOutput output, uint32_t *clk_off_f, tNmiDacSel dac_sel, bool_t rfinvert)
{
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;
	uint32_t			xo_f;
	uint16_t n0_f;
	uint8_t w_f;
	uint32_t n1_f, vco_f;	
	uint8_t r8, r1;	
	const uint8_t    lo_div_lut[] = { 0, 1, 2, 3, 4, 6, 9, 12};

	xo_f = chip.inp.xo; /* in KHz */

	if(ISNM130(pp->chipid)) {
		switch(rffrequency)
		{
		case 147000000: 
			{
				r8 = rReg8(0x21);					
				r8 |= 0x3;
				wReg8(0x21, r8);
			}
			break;
		case 171000000:			
		case 506000000:
		case 554000000:
		case 602000000:
		case 650000000:
		case 698000000:
		case 746000000:
		case 794000000:
		case 842000000:
			{				
				r8 = rReg8(0x21);					
				r8 &= ~(0x3);
				r8 |= 0x2;
				wReg8(0x21, r8);
			}
			break;
		default:
			{
				uint8_t _r8;

				_r8 = rReg8(0x21);					
				_r8 &= ~(0x3);
				_r8 |= 0x1;
				wReg8(0x21, _r8);
			}
		}
	}


	/**
	tune
	**/
	if(std == nFM_RADIO) {
		rffrequency -= 3500000;
	}

	if(chip.inp.xo_out_en) {
		r8 = 0x87;//0x87;//120518
		pp->cvbsMaxVol = 15;
	} else {
		/* XTAL buf handling. */
		if(std == nFM_RADIO) {
			r8 = 0x87;
			pp->cvbsMaxVol = 15;
		} else {
			if((std ==nPAL_K) &&
				(
				 ((rffrequency >= (168250000-150000)) && (rffrequency <= (168250000+150000))) ||
				 ((rffrequency >= (192250000-150000)) && (rffrequency <= (192250000+150000))) ||
				 ((rffrequency >= (216250000-150000)) && (rffrequency <= (216250000+150000))) )){
					r8 = 0x3;
					pp->cvbsMaxVol = 14;
			}else if((rffrequency >= (120250000-150000)) && (rffrequency <= (120250000+150000))){
					r8 = 0x5;
					pp->cvbsMaxVol = 14;
			}
			else if(ISATV(std) && 
				(			
				( rffrequency <= 245250000) ||
				( (rffrequency >= (567250000-150000)) && (rffrequency <= (567250000+150000)) )
				)) {
					r8 = 0x87;
					pp->cvbsMaxVol = 15;
			}
			else {
				r8 = 0x85;
				pp->cvbsMaxVol = 15;
			}
		}
	}
	
	if(r8 != pp->rf_reg_0x05) {
		wReg8(0x05, r8);
		pp->rf_reg_0x05 = r8;
	}

	/* Convert luma freq. to lo frequency at this point. */
	if(!rfinvert) {		
		rffrequency += rf_freq_offset_lut[std]; 
	} else {
		rffrequency -= rf_freq_offset_lut[std]; 	
	}

	for(r1 = 7; r1 > 1; r1--)
	{
		if (rffrequency <= lo_freq_lut[r1]) {
			break;
		}
	}

	pp->lofrequency = rffrequency;

	nm131_tuner_apply_vhf_filter(rffrequency);

	/** vco_f : u23.0 **/
	vco_f = (rffrequency/1000)* (lo_div_lut[r1] << 3);	

	r8 = rReg8(0x21);
	switch(r8 & 0x3) 
	{
	case 0x2: xo_f <<= 1; break;
	case 0x3: xo_f >>= 1; break;
	}

	n0_f = (uint16_t)(vco_f/xo_f);
	/** 
	since vco%xo_f < xo_f, then 
	for xo_f = 12000: vco%xo_f: 13.55074679 bits.
	for xo_f = 24000: vco%xo_f: 14.55074679 bits.
	for xo_f = 48000: vco%xo_f: 15.55074679 bits.
	**/
	/**
	for xo_f = 12000: ((1ul << 31)/xo_f): 17.44925321 bits.
	for xo_f = 24000: ((1ul << 31)/xo_f): 16.44925321 bits.
	for xo_f = 48000: ((1ul << 31)/xo_f): 15.44925321 bits.
	**/
	n1_f = ( ((vco_f%xo_f) * ((1ul << 31)/xo_f)) >> (31-19) ) & 0x7ffff;	

	/** w_f: u5.0 **/
	w_f = (uint8_t)(vco_f / 216000);	
	if (w_f > 31) {
		w_f = 31;
	} else if (w_f < 16) {
		w_f = 16;
	}
	/**
	*clk_off = (((vco/216000000)/w) -1); 
	clk_off_f = clk_off * 216000 * 2^9, where:	
	**/
	*clk_off_f = ( (vco_f << 9)/((uint32_t)w_f) ) - ((1ul << 9)*216000);



	r8 = (uint8_t)(n0_f >> 1);
	wReg8(0x01, r8);
	r8 = (uint8_t)((n1_f << 1) | (n0_f & 0x1));
	wReg8(0x02, r8);
	r8 = (uint8_t)(n1_f >> 7);
	wReg8(0x03, r8);
	r8 = (uint8_t)(((n1_f >> 15) & 0xf) | ((w_f - 16) << 4));
	wReg8(0x04, r8);

	r8 = rReg8(0x1d);
	r8 &= ~(0x7 << 5);
	r8 |= (r1 << 5);
	wReg8(0x1d, r8);

	if(ISNM120(pp->chipid)) {
		if(rffrequency >= 300000000) { /* UHF */		
			wReg8(0x25, 0xf4);
			wReg8(0x27, 0xef);
			wReg8(0x29, 0x4f);
			wReg8(0x2e, 0x34);
			
		} else { /* VHF */			
			wReg8(0x25, 0x78);
			wReg8(0x27, 0x7f);
			wReg8(0x29, 0x7f);
			wReg8(0x2e, 0x12);
		}

		if(rffrequency >= 155000000) {		
			wReg8(0x36, 0x7c);
		} else {
			wReg8(0x36, 0x54);
		}			
	} else if(ISNM130(pp->chipid)) {
		switch(rffrequency)
		{
		case 147000000:				
		case 171000000:				
		case 195000000:
		case 219000000:
		case 243000000:
			wReg8(0x0e, 0x45);
			break;
		default:
			wReg8(0x0e, 0x25);
		}

		if(ISDTV(std)) {
			if( (rffrequency == 115000000) || (rffrequency == 123000000) ) {
				wReg8(0x25, 0x43);
				wReg8(0x2e, 0x78);
			} else {
				wReg8(0x25, 0x56);
				wReg8(0x2e, 0x56);
			}
		} else {
			wReg8(0x25, 0xe9);
			wReg8(0x2e, 0x56);
		}			

		if(rffrequency >= 139000000) {
			wReg8(0x30, 0x1);
			wReg8(0x32, 0x1);
		} else {		
			wReg8(0x30, 0xdf);
			wReg8(0x32, 0xdf);
		}

		switch(rffrequency)
		{
		case 123000000:
		case 147000000:
		case 171000000:
		case 195000000:
		case 219000000:
		case 243000000:
		case 267000000:
		case 291000000:
		case 315000000:
		case 339000000:
		case 363000000:
		case 387000000:
		case 411000000:
		case 435000000:
		case 459000000:
			wReg8(0x1b, 0x08);
			break;
		default:
			wReg8(0x1b, 0x0e);
		}

	} else if(ISNM130v(pp->chipid)) {
		if(ISDTV(std)) {
			wReg8(0x0e, 0x45);
			wReg8(0x25, 0xfa);
			wReg8(0x26, 0x82);

			if(rffrequency >= 818000000) {
				wReg8(0x27, 0x3f);
				wReg8(0x29, 0x3f);				
				wReg8(0x30, 0xaf);
				wReg8(0x32, 0xaf);
			} else if(rffrequency >= 786000000) {
				wReg8(0x27, 0x3f);
				wReg8(0x29, 0x3f);				
				wReg8(0x30, 0xdf);
				wReg8(0x32, 0xdf);
			} else if(rffrequency >= 762000000) {
				wReg8(0x27, 0x5f);
				wReg8(0x29, 0x5f);				
				wReg8(0x30, 0xdf);
				wReg8(0x32, 0xdf);
			} else {
				wReg8(0x27, 0x7f);
				wReg8(0x29, 0x7f);				
				wReg8(0x30, 0xdf);
				wReg8(0x32, 0xdf);				
			}

			if(rffrequency >= 155000000) {		
				wReg8(0x36, 0x7c);
			} else {
				wReg8(0x36, 0x54);
			}

		} else {
			wReg8(0x0e, 0x25);
			wReg8(0x25, 0xe9);
			wReg8(0x26, 0x80);

			wReg8(0x27, 0x01);
			wReg8(0x29, 0x01);
			wReg8(0x30, 0x01);
			wReg8(0x32, 0x01);

			wReg8(0x36, 0x54);
		}	

	} else if(ISNM131(pp->chipid)) {
		if(ISDTV(std)) {
			wReg8(0x0e, 0x45);
			wReg8(0x25, 0xfa);
		} else {
			wReg8(0x0e, 0x25);
			wReg8(0x25, 0xe9);
		}


		if(ISATV(std)) {
			wReg8(0x2e, 0x22);
		} else {
			wReg8(0x2e, 0x56);
		}

		if(output == nIf && ISATV(std)) {
			wReg8(0x26, 0x80);			
		} else { /* IF/DTV, CVBS/SIF/ATV, CVBS/BBAUD/ATV */
			wReg8(0x26, 0x82);
		}

		if(ISCVBS(output)) {
			/* CVBS definitely ATV */
			wReg8(0x27, 0xaf);
			wReg8(0x29, 0xaf);
			wReg8(0x30, 0x0f);
			wReg8(0x32, 0x0f);
			if(std != nFM_RADIO) {
				if(pp->cvbsVideoAmp  < 16) {
					wReg8(0x34, 0xff-pp->cvbsVideoAmp);
				} else {
					wReg8(0x34, 0xf0);
				}
			}  else {
				/* Disable CVBS DAC in FM mode. */
				wReg8(0x34, 0x60); 
			}

			if((pp->cvbsVol < 16) && (pp->cvbsVol <= pp->cvbsMaxVol) ) {
				wReg8(0x35, 0x5f-pp->cvbsVol);
			} else if((pp->cvbsVol < 16) && (pp->cvbsVol > pp->cvbsMaxVol) ){
				wReg8(0x35, 0x5f-pp->cvbsMaxVol);
			}else{
				wReg8(0x35, 0x50);
			}

			wReg8(0x36, 0x54);

		}else {
			/* ATV or DTV */
			if(ISDTV(std)) {
				if(rffrequency >= 818000000) {
					wReg8(0x27, 0x3f);
					wReg8(0x29, 0x3f);				
					wReg8(0x30, 0xaf);
					wReg8(0x32, 0xaf);
				} else if(rffrequency >= 786000000) {
					wReg8(0x27, 0x3f);
					wReg8(0x29, 0x3f);				
					wReg8(0x30, 0xdf);
					wReg8(0x32, 0xdf);
				} else if(rffrequency >= 762000000) {
					wReg8(0x27, 0x5f);
					wReg8(0x29, 0x5f);				
					wReg8(0x30, 0xdf);
					wReg8(0x32, 0xdf);
				} else {
					wReg8(0x27, 0x7f);
					wReg8(0x29, 0x7f);				
					wReg8(0x30, 0xdf);
					wReg8(0x32, 0xdf);				
				}

				if(rffrequency >= 155000000) {		
					wReg8(0x36, 0x7c);
				} else {
					wReg8(0x36, 0x54);
				}
			} else {
				wReg8(0x27, 0x01);
				wReg8(0x29, 0x01);
				wReg8(0x30, 0x01);
				wReg8(0x32, 0x01);

				wReg8(0x36, 0x54);
			}
		}		
	}

	if(ISNM130v(pp->chipid) || ISNM131(pp->chipid)){
		if((output == nIf) && ISATV(std)){
			if((dac_sel == nDac1) || (dac_sel == nDacBoth)){
				if(pp->cvbsVideoAmp < 16) {
					wReg8(0x34, 0x7f-pp->cvbsVideoAmp);
				} else {
					wReg8(0x34, 0x70);
				}
			}
			if((dac_sel == nDac2) || (dac_sel == nDacBoth) || (dac_sel == nDacDefault)){
				if(pp->cvbsVideoAmp  < 16) {
					wReg8(0x35, 0x5f-pp->cvbsVideoAmp);
				} else {
					wReg8(0x35, 0x50);
				}
			}
			if((dac_sel != nDac1) && (dac_sel != nDacBoth)){
				/* Disable DAC1*/
				wReg8(0x34, 0x60); 
			}
			if((dac_sel != nDac2) && (dac_sel != nDacBoth) && (dac_sel != nDacDefault)){
				/* Disable DAC2*/
				wReg8(0x35, 0x40); 
			}

		}else if(!ISCVBS(output)){
			if(ISDTV(std)){
				wReg8(0x34, 0x68);
			}else{
				wReg8(0x34, 0x78);
			}
			wReg8(0x35, 0x18);
		}
	}

	if(ISDTV(std)) {	
		if(rffrequency >= 300000000) {
			wReg8(0x37, 0x84);
		} else if(rffrequency >= 155000000) {		
			wReg8(0x37, 0x9c);
		} else {
			wReg8(0x37, 0x84);
		}		
	} else {
		wReg8(0x37, 0x84);
	}

	return;
}

static void nm131_tune_internal(tTnrTune *tune, tTnrTuneMode tuneMode)
{
	uint32_t clk_off_f;
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;

	nm131_tuner_config(tune->rf, tune->std, tune->output, &clk_off_f, tune->dacSel, tune->rfinvert);
	nm131_demod_config(tune->rf, tune->std, tune->output, tune->aif, tune->vif,
		clk_off_f, tune->is_stereo, tuneMode, tune->dacSel, tune->rfinvert);

	pp->clk_off_f = clk_off_f;
	pp->std = tune->std;
	pp->output = tune->output;
	pp->frequency = tune->rf;
	pp->tuneMode = tuneMode;
	pp->dacsel = tune->dacSel;
	pp->rfinvert = tune->rfinvert;

	return;
}


static int nm131_tune(tTnrTune *tune)
{
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;

	if(ISNM131(chip.priv.chipid)) {
		if(ISCVBS(tune->output)) {
			if(tune->std == nFM_RADIO) {
				nm131_tune_internal(tune, nTuneOnly);
			} else if(!tune->single_tune) {
				tTnrScan scan;

				memcpy(&scan.tune, tune, sizeof(tTnrTune));
				scan.alocklevel = 0;
				scan.found = 0;
				nm131_scan(&scan);		

				if(scan.found) {			
					int fqoff;

					fqoff = (int)nm131_demod_get_freq_offset();

					if( abs(fqoff) > 30000) {
						tune->rf += fqoff;

						nm131_tune_internal(tune, nTuneOnly);
					} else {
					}
					nm131_notch_spur();	
				} else {
				}
			} else {
				nm131_tune_internal(tune, nTuneOnly);
				nm131_notch_spur();	
			}
		} else {
			/**
			if we switch from CVBS to IF, then make sure notch is off. 
			**/
			if(ISCVBS(pp->output)) {
				nm131_notch_ctl(0, 0);
			}
			nm131_tune_internal(tune, nTuneOnly);
		}
	}
	else if(ISNM130v(chip.priv.chipid))//ÂÀÏþÔÆ
	{
			nm131_tune_internal(tune, nTuneOnly);
			nm131_notch_spur();
	}
	else
	{
		nm131_tune_internal(tune, nTuneOnly);
	}
	if(tune->vif == 6150000)
		nmi_delay(200);//add This!! If no this delay, Secam L/L'' will not be locked.
	return 0;

}

/**
Use this function only in CVBS/SIF or CVBS/BBAud.
vol a number between 0 and 16. 0: min gain. 16: max gain.
**/
static void nm131_set_volume(uint8_t vol)
{
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	if(ISCVBS(pp->output)) {
		if(vol < 16) {
			uint8_t val8;
			if(vol > pp->cvbsMaxVol){
				vol = pp->cvbsMaxVol;
			}
			val8 = 0x5f - vol;
			wReg8(0x35, val8);
			wReg32(0x27c, 0x1010);
			pp->cvbsVol = vol;
			
		} else if(vol == 16) {
			wReg8(0x35, (0x5f-pp->cvbsMaxVol));
			wReg32(0x27c, 0x1818);

			pp->cvbsVol = vol;
		}
	}
}
/**
Use this function only in CVBS/SIF or CVBS/BBAud.
Returns a number between 0 and 16. 0: min gain. 16: max gain.
**/
static uint8_t nm131_get_volume(void)
{
	uint8_t val8;
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	if(ISCVBS(pp->output)) {
		val8 = rReg8(0x35);

		if((val8 >= 0x50) && (val8 <= 0x5f)) {
			uint32_t val32;

			val32 = rReg32(0x27c);
			if(val32 == 0x1818) {
				return 16;
			} else {
				return 0x5f - val8;
			}
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

static void nm131_lt_ctrl(bool_t enable)
{
	if(enable) {		
		wReg8(0x0a, 0xf8);		
	} else {
		/**
		Always make sure these values are the same as the those in 
		tnr_rf_defaults_lut.
		**/
		wReg8(0x0a, 0xeb);
	}
}

/**
Use this function only in CVBS/SIF, CVBS/BBAud or IF.
brt a number between 0 and 15. 0: min amplitude. 15: max amplitude.
**/
static void nm131_set_video_amplitude(uint8_t amp)
{
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;
	
	if(ISCVBS(pp->output)) {
		if(amp < 16) {
			if(pp->std != nFM_RADIO) {
				uint8_t val8;				
				val8 = 0xff - amp;
				wReg8(0x34, val8);
			}
			pp->cvbsVideoAmp = amp;
		}
	}
	else if((pp->output == nIf) && ISATV(pp->std)
		&& (ISNM130v(pp->chipid) || ISNM131(pp->chipid))){
		if((pp->dacsel == nDac1) || (pp->dacsel == nDacBoth)){
			if(amp < 16) {
				uint8_t val8;
				val8 = 0x7f - amp;
				wReg8(0x34, val8);
			}
		}
		if((pp->dacsel == nDac2) || (pp->dacsel == nDacBoth) || (pp->dacsel == nDacDefault)){
			if(amp < 16) {
				uint8_t val8;				
				val8 = 0x5f - amp;
				wReg8(0x35, val8);
			}
		}
		pp->cvbsVideoAmp = amp;
	}
}

/**
Use this function only in CVBS/SIF, CVBS/BBAud or IF.
Returns a number between 0 and 15. 0: min gain. 15: max gain.
**/
static uint8_t nm131_get_video_amplitude(void)
{
	uint8_t val8;
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	if(ISCVBS(pp->output)) {
		if(pp->std != nFM_RADIO) {
			val8 = rReg8(0x34);

			if((val8 >= 0xf0) /* && (val8 <= 0xff) */) {
				return 0xff - val8;
			} else {
				return 0;
			}
		} else {
			return pp->cvbsVideoAmp;			
		}
	}else if((pp->output == nIf) && ISATV(pp->std)){
		if(ISNM130v(pp->chipid) || ISNM131(pp->chipid)){
			if((pp->dacsel == nDac1) || (pp->dacsel == nDacBoth)){
				if(pp->std != nFM_RADIO) {
					val8 = rReg8(0x34);

					if((val8 >= 0x70) && (val8 <= 0x7f)) {
						return 0x7f - val8;
					} else {
						return 0;
					}
				} else {
					return pp->cvbsVideoAmp;			
				}
			}
			if((pp->dacsel == nDac2) || (pp->dacsel == nDacBoth) || (pp->dacsel == nDacDefault))
			{
				if(pp->std != nFM_RADIO) {
					val8 = rReg8(0x35);

					if((val8 >= 0x50) /* && (val8 <= 0xff) */) {
						return 0x5f - val8;
					} else {
						return 0;
					}
				} else {
					return pp->cvbsVideoAmp;			
				}
			}
		}else{
			if(pp->std != nFM_RADIO) {
					val8 = rReg8(0x34);

					
						return 0xf - (val8&0xf);
					
				} else {
					return 0;			
				}
			
		}
	}
	else {
		return 0;
	}
	return 0;
}

/**
Use this function only in CVBS/SIF or CVBS/BBAud.
luma a number between 0 and 32. 0: min luma brightness. 32: max brightness.
**/
static void nm131_set_brightness(uint8_t brightness)
{
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	if(ISCVBS(pp->output)) {
		uint32_t val32;
		if(brightness > 32)
		{
			brightness = 32;
		}

		val32 = rReg32(0x200);
		val32 &= ~(0x3fff);
		/*Yangru's formula: 0xa00 + 0x40 *x where x can be any number in
		[-16, -15, ? 0, 1, 2, .. 16]*/
		val32 |= (0x600 + (brightness << 6));
		wReg32(0x200, val32);
		
		pp->cvbsBrt = brightness;
	
	}
}

/**
Use this function only in CVBS/SIF or CVBS/BBAud.
Returns a number between 0 and 32. 0: min brightness. 32: max brightness.
**/
static uint8_t nm131_get_brightness(void)
{
	uint32_t val32;
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	if(ISCVBS(pp->output)){
		if(pp->std != nFM_RADIO) {
			val32 = rReg32(0x200);
			val32 &= 0x3fff;
			val32 -= 0x600;
			val32 = val32 >> 6;
			return val32;
		} else {
			return pp->cvbsBrt;
		}
	} else {
		return 0;
	}
}

static void nm131_set_mute(uint8_t mute)
{
	uint32_t val32;
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;
	if(ISCVBS(pp->output) || (pp->output == nVifAif)){
		if(mute != pp->mute){
			val32 = rReg32(0x35);
			if(mute == 0){
				val32 |= (0x1ul<<4);
			}
			else{
				val32 &= ~(0x1ul<<4);
			}
			wReg32(0x35, val32);
			pp->mute = mute;
		}
	}
}

static uint8_t nm131_get_mute(void)
{
	uint32_t val32;
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	if(ISCVBS(pp->output) || (pp->output == nVifAif)){
		val32 = rReg32(0x35);
		return (0x1ul & (val32>>4));
	}
	else{
		return 0;
	}

}
/******************************************************************************
**
**	FM
**
*******************************************************************************/
static int nm131_get_overthcount(void)
{
	uint32_t val32;
	val32 = rReg32(0x254);
	val32 &= 0xffff;
	return val32;
}

static int16_t nm131_adec_get_rssi(void)
{
	uint32_t val32; 
	int16_t rssix100;
	u17_15_t agc, dagc;
	tTnrGain rfg;
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;
	
	val32 = rReg32(0x24c);
	nmi_debug(N_VERB, "0x24c (%08x)\n", val32);
	val32 &= 0x3fffffff;
	agc = val32 >> 5;

	rssix100 = 25 * nmi_log10(agc);
	dagc = nm131_demod_dagc_gain();
	rssix100 += 25 * nmi_log10(dagc);

	nm131_get_lna_gain(&rfg);
	rssix100 += rfg.lnadbx100;
	rssix100 += rfg.bblidbx100;
	rssix100 += 600;

	rssix100 = 12000 - rssix100;
	if (rssix100 < 0)
		rssix100 = 0;
	if (rssix100 > 12700)
		rssix100 = 12700;

	if(pp->frequency == 96000000 && rssix100 < 1700) {
		rssix100 = 0;
	}
		
	return (int16_t)rssix100;
}
static void nm131_fm_set_scan_level(int level)
{
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	if ((level < 2) && (level > 9))
		return;

	pp->fmscanth = level; 

	return;
}

static void nm131_fm_get_window_rssi(int *orssi, int len, int *wrssi,int *overth)
{
	int k;
	for(k=0;k<len;k++){
		*(overth+k)=(*(orssi+k)>>8);
		*(orssi+k)=(*(orssi+k))&0xff;
	}
	for (k=0; k<len; k++) {
		if (k==0)
			*(wrssi+k)=*(orssi+k)+*(orssi+k)+*(orssi+k+1);
		else if (k==len-1)
			*(wrssi+k)=*(orssi+k-1)+*(orssi+k)+*(orssi+k);
		else
			*(wrssi+k)=*(orssi+k-1)+*(orssi+k)+*(orssi+k+1);

		*(wrssi+k) = *(wrssi+k)/3;
	}
}
static int nm131_fm_find_dip(int *overth, int len)
{
	int pos,dip,k;
	pos=-1;
	dip=  65535;
	for (k=0; k<len; k++) {
		if (*(overth+k) < dip) {
	   		dip=*(overth+k);
	    	pos=k;
  		}
	}
	return pos;
}

static int nm131_fm_find_peak(int *rssi, int len)
{
	int pos,peak,k;

	pos=-1;
	peak=0;
	for (k=0; k<len; k++) {
		if (*(rssi+k) > peak) {
	   		peak=*(rssi+k);
	    	pos=k;
  		}
	}

	return pos;
}

static void nm131_fm_select_channel_list(int *orssi, int *wrssi, int *clist, int *nc, int cmax, int clen, int *overth)
{
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;
  	int done=0;
  	int num=0;
  	int posN2;
  	int posP2;
	int posN1;
  	int posP1;
  	int k,idx;
  	int pos;
  	int r_cond,l_cond,least_cond;
  	int relative_th = pp->fmscanth;
  	int least_th=3;
	int dev;
	int or_cond,ol_cond;
	int wrelative_th=1;
	int relative_ratio_th=2;
	int max_overth=250;
	int posL,posR;
	int relative_th_side=2;
	int use_new_search=0;

	if (clen == 206) {
		dev = 2;
	} else {
		//relative_th = 4;
		dev = 4;
	}
    
 	while (!done) {
		if (use_new_search==0) {
			pos = nm131_fm_find_peak(wrssi, clen);
		} else {
			pos = nm131_fm_find_dip(overth, clen);
		}
      
      if (pos==-1) {
          done=1;
      } else {
          //posN2=(pos-2)<0?0:pos-2;
          //posP2=(pos+2)>=ch_len?ch_len-1:pos+2;
          posN2 = (pos-dev)<0?(pos+dev):(pos-dev);
          posN2 = (posN2>=clen)?(clen-1):posN2;
          posP2 = ((pos+dev)>=clen)?(pos-dev):(pos+dev);
          posP2 = (posP2<0)?0:posP2;
                    
			posN1 = (pos-dev/2)<0?(pos+dev/2):(pos-dev/2);
			posN1 = (posN1>=clen)?(clen-1):posN1;
			posP1 = ((pos+dev/2)>=clen)?(pos-dev/2):(pos+dev/2);
			posP1 = (posP1<0)?0:posP1;
			posR = ((pos+1)>=clen)?(pos-1):(pos+1);
			posR = (posR<0)?0:posR;
			posL = (pos-1)<0?(pos+1):(pos-1);
			posL = (posL>=clen)?(clen-1):posL;
			if (use_new_search == 0) {
				l_cond = ((*(wrssi+pos)) >= (*(orssi+posN2)+wrelative_th));
				r_cond = ((*(wrssi+pos)) >= (*(orssi+posP2)+wrelative_th));
				ol_cond = ((*(orssi+pos)) >= (*(orssi+posN1)+relative_th));
				or_cond = ((*(orssi+pos)) >= (*(orssi+posP1)+relative_th));
				if (clen != 206) {
					if (ol_cond)
						ol_cond = ((*(orssi+posL)) >= (*(orssi+posN1)+relative_th_side));
					if (or_cond)
						or_cond = ((*(orssi+posR)) >= (*(orssi+posP1)+relative_th_side));
				}
				least_cond = (*(orssi+pos) >= least_th);
			} else {
				l_cond = ((*(overth+pos))*relative_ratio_th) <= (*(overth+posN1));
				r_cond = ((*(overth+pos))*relative_ratio_th) <= (*(overth+posP1));

				nmi_debug(N_VERB, "(%d)pos(%d)(%d)(%d):(%d)(%d)(%d)\n", dev, pos, posN1, posP1, *(orssi+pos), *(orssi+posN1), *(orssi+posP1));
				  
				ol_cond = ((*(orssi+pos)) >= (*(orssi+posN1)+relative_th));
				or_cond = ((*(orssi+pos)) >= (*(orssi+posP1)+relative_th));
				least_cond = (*(orssi+pos) >= least_th) && ((*(overth+pos))<=max_overth);
			}

			if (l_cond && r_cond && least_cond && or_cond && ol_cond) {

				*(clist+num)=pos;	/* review */
                  
				if (use_new_search==0){    
					for (k=-2;k<3;k++) {
					  idx=pos+k;
					  idx=(idx<0)?0:idx;
					  idx=(idx>=clen)?clen-1:idx;
					  *(wrssi+idx)=-1;
					}
				} else {
					for(k=-1*dev/2;k<=dev/2;k++){
						idx=pos+k;
						idx=(idx<0)?0:idx;
						idx=(idx>=clen)?clen-1:idx;
						*(overth+idx)=65535;
					}
			  	}
             num++;
				if (num>=cmax)
					done=1;
			} else {
				if (use_new_search==0){
				  *(wrssi+pos)=-1;
				} else {
					*(overth+pos)=65535;
			  	}
			}
		}
	}

	*(nc)=num;
}

static int nm131_fm_seek_select(int *rssi, int *overth, int sz)
{
	int i;
	int aRssi[3];
	int mRssi = 0, pos = 0;
	int start_cond, end_cond, least_cond;
	int relative_th=2;
	int wrelative_th=1;
	int least_th=3;
	int found = 0;
	int start_ocond=1, end_ocond=1;
	int relative_ratio_th=2;
	//int max_overth=250;
	int relative_th_side=2;
	
	//tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;
	int use_new_search=1;

	/**
		make decision
	**/
	if (sz == 7) {
		aRssi[0] = (rssi[0] + rssi[1] + rssi[2] + rssi[3] + rssi[4])/5;
		aRssi[1] = (rssi[1] + rssi[2] + rssi[3] + rssi[4] + rssi[5])/5;
		aRssi[2] = (rssi[2] + rssi[3] + rssi[4] + rssi[5] + rssi[6])/5;
	} else {
		aRssi[0] = (rssi[0] + rssi[1] + rssi[2])/3;
		aRssi[1] = (rssi[1] + rssi[2] + rssi[3])/3;
		aRssi[2] = (rssi[2] + rssi[3] + rssi[4])/3;
	}

	for (i = 0; i < 3; i++) {
		if (aRssi[i] > mRssi) {
			mRssi = aRssi[i];
			pos = i; 
		}
	}

	if (use_new_search==0) {	
		if (sz == 7) {
			start_ocond = (aRssi[1] >= (wrelative_th + rssi[0]));
			end_ocond = (aRssi[1] >= (wrelative_th + rssi[6]));
			start_cond = ((*(rssi+3)) >= (*(rssi+1)+relative_th));
			end_cond = ((*(rssi+3)) >= (*(rssi+5)+relative_th));
			if (start_cond)
				start_cond=((*(rssi+2)) >= (*(rssi+1)+relative_th_side));
			if (end_cond)
				end_cond = ((*(rssi+4)) >= (*(rssi+5)+relative_th_side));
			least_cond = (*(rssi+3) )>= least_th;
		} else {
			start_ocond = (aRssi[pos] >= (wrelative_th + rssi[0]));
			end_ocond = (aRssi[pos] >= (wrelative_th + rssi[4]));
			start_cond = ((*(rssi+2)) >= (*(rssi+1)+relative_th));
			end_cond = ((*(rssi+2)) >= (*(rssi+3)+relative_th));
			least_cond = (*(rssi+2) )>= least_th;
		}
		if ((pos == 1) && start_cond && end_cond && least_cond && start_ocond && end_ocond)
			found = 1;
	} else {
		if (sz == 7) {
			start_ocond = 0;
			if (((*(overth+3))*relative_ratio_th) <= (*(overth+1)))
				if (((*(overth+3))*relative_ratio_th) <= (*(overth+2)))
					start_ocond=1;
			end_ocond = 0;
			if 	(((*(overth+3))*relative_ratio_th) <= (*(overth+5)))
				if (((*(overth+3))*relative_ratio_th) <= (*(overth+4)))
					end_ocond=1;
			start_cond = ((*(rssi+3)) >= (*(rssi+1)+relative_th));
			end_cond = ((*(rssi+3)) >= (*(rssi+5)+relative_th));
			least_cond = (*(rssi+3) )>= least_th;

			pos=1;
		} else {
			start_ocond = ((*(overth+2))*relative_ratio_th) <= (*(overth+1));
			end_ocond =   ((*(overth+2))*relative_ratio_th) <= (*(overth+3));
			start_cond = ((*(rssi+2)) >= (*(rssi+1)+relative_th));
			end_cond = ((*(rssi+2)) >= (*(rssi+3)+relative_th));
			least_cond = (*(rssi+2) )>= least_th;
			pos=1;
		}

		if ((pos == 1) && start_cond && end_cond && least_cond && start_ocond && end_ocond)
			found = 1;
	}

	return found;
}

static void nm131_fm_scan(tTnrFmScan * p)
{	
	tTnrTune tune;	

	memset(&tune, 0, sizeof(tune));
	tune.output = nCvbsBBAud;
	tune.rf = p->frequency;		
	tune.std = nFM_RADIO;	
	nm131_tune_internal(&tune, nFmScan);			
	nmi_delay(20);
	p->rssix100 = nm131_adec_get_rssi();
	p->overth = nm131_get_overthcount();

	//nmi_debug(N_INFO, "FM: frequency (%d), rssi (%d),  overth (%d)\n", p->frequency, p->rssi, p->overth);


	
}

/******************************************************************************
**
**	ATV Scan
**
*******************************************************************************/
void nm131_set_scan_level(int level) 
{	
	switch(level) 
	{
	case 1: chip.priv.alocklevelth = 65; break;
	case 2: chip.priv.alocklevelth = 60; break;
	case 3: chip.priv.alocklevelth = 55; break;
	case 4: chip.priv.alocklevelth = 50; break;
	case 5: chip.priv.alocklevelth = 45; break;
	case 6: chip.priv.alocklevelth = 40; break;
	case 7: chip.priv.alocklevelth = 35; break;
	default: chip.priv.alocklevelth = 45;
	}
}

void nm131_scan(tTnrScan *p)
{
	uint32_t val32;	
	int alocklevel;	

	nm131_tune_internal(&p->tune, nAtvScan);

	nmi_delay(30);

	val32 = rReg32(0x1ec);
	alocklevel = (val32 >> 10) & 0x3ff;
	alocklevel = (alocklevel >= 512) ? (alocklevel - 1024) : alocklevel;	
	//nmi_debug(N_INFO, "1. freq = %f MHz, alocklevel (%d)\r\n", p->tune.rf/1000000.0, alocklevel);				
	p->alocklevel = alocklevel;
	if (alocklevel >= chip.priv.alocklevelth) {
		p->found = 1;
	} else {		
		p->found = 0;
	}
}

/******************************************************************************
**
**	Init Functions
**
*******************************************************************************/

static uint32_t nm131_get_chipid(void) 
{
	uint32_t chipid;

	chipid = rReg32(0x3fc);
	nmi_debug(N_INFO, "@ %u: Chip ID (%08x)\n", nmi_get_tick(), chipid);

	return chipid;
}

static void nm131_bus_test(void)
{
	int i, len;
	uint8_t *buf;	

	buf = chip.inp.busTest.buf;	
	len = chip.inp.busTest.len;


	if(len > 0x3c) {
		nmi_debug(N_INFO, "@ %u: Max. bus test length is 0x3c.\n", nmi_get_tick());
		len = 0x3c;
	}


	for(i=0; i<len; i++) {
		buf[i] = i;			
	}

	nmi_debug(N_INFO, "@ %u: Begin bus test.\n", nmi_get_tick());

	wRegBurst(0, buf, len);

	nmi_debug(N_INFO, "@ %u: Burst write done.\n", nmi_get_tick());

	for(i=0; i<len; i++) {
		buf[i] = rReg8(i);
		if(buf[i] != i) {
			break;
		}
	}

	if(i<len) {
		nmi_debug(
			N_INFO, 
			"@ %u: Bus test failed"
			" at i = %d expected = %d, val = %d.\n",
			nmi_get_tick(), i, i, buf[i]);
	} else {
		nmi_debug(N_INFO, "@ %u: Bus test passed.\n", nmi_get_tick());
	}
}

static int nm131_chip_init(void)
{
	uint8_t val8;
	uint32_t idx;
	tNmiPriv *pp = (tNmiPriv *)&chip.priv;

	pp->chipid = nm131_get_chipid();

	if ((!ISNM131(pp->chipid)) && (!ISNM120(pp->chipid)) && (!ISNM130(pp->chipid)) && (!ISNM130v(pp->chipid)) ) 
	{
		nmi_debug(N_ERR, "Failed, incorrect chip id...\n");
		return -1;
	}

	/**
	Scan Threshold
	**/
	nm131_set_scan_level(7);

	/**
	FM Scan Threshold
	**/
	pp->fmscanth = 3;

	/**
	Tune mode.
	**/
	pp->tuneMode = (tTnrTuneMode)-1;

	/**
	CVBS/SIF, CVBS/BBAud volume
	**/
	pp->cvbsVol = 15;
	pp->cvbsMaxVol = 15;
	/**
	CVBS/SIF, CVBS/BBAud brightness
	**/
	pp->cvbsVideoAmp = 15;//0;
	/**
	CVBS/SIF, CVBS/BBAud contrast
	**/
	pp->cvbsBrt = 8;

	pp->std = nInvalidNmiTvStd;	
	pp->output = nInvalidNmiOutput;	
	pp->dconotch_ctl = 0x45c2ul; /* por value. */
	pp->rf_reg_0x05 = 0x87; /* por value. */
	
	//chip.inp.xo *= 1000; /* from MHz to KHz. */
	//chip.inp.xo = ; /* from MHz to KHz. */

	if(chip.inp.busTest.enableTest) {
		nm131_bus_test();
	}

	if(chip.inp.init_bus_only) {
		return 0;
	}

#ifdef PC_ENV
	nm131_power_on_reset();
#endif

	for(idx=0; idx<tnr_rf_defaults_lut_sz; idx++) {
		wReg8(tnr_rf_defaults_lut[idx].addr, tnr_rf_defaults_lut[idx].val);
	}

	/**
	Configure LDO bypass.
	**/
	val8 = rReg8(0x36);
	if (chip.inp.ldobypass) {		
		val8 |= (1ul << 7);
	} else {
		val8 &= ~(1ul << 7);
	}
	wReg8(0x36, val8);		

	for(idx=0; idx<tnr_bb_defaults_lut_sz; idx++) {
		wReg32(tnr_bb_defaults_lut[idx].addr, tnr_bb_defaults_lut[idx].val);
	}

	if(ISNM120(pp->chipid)) {
		for(idx=0; idx<nm120_rf_defaults_lut_sz; idx++) {		
			wReg8(nm120_rf_defaults_lut[idx].addr, nm120_rf_defaults_lut[idx].val);
		}
	} else if(ISNM130(pp->chipid)) {
		for(idx=0; idx<nm130_rf_defaults_lut_sz; idx++) {		
			wReg8(nm130_rf_defaults_lut[idx].addr, nm130_rf_defaults_lut[idx].val);
		}
	} else if(ISNM130v(pp->chipid)) {
		for(idx=0; idx<nm130v_rf_defaults_lut_sz; idx++) {		
			wReg8(nm130v_rf_defaults_lut[idx].addr, nm130v_rf_defaults_lut[idx].val);
		}
	} else if(ISNM131(pp->chipid)) {
		for(idx=0; idx<nm131_rf_defaults_lut_sz; idx++) {		
			wReg8(nm131_rf_defaults_lut[idx].addr, nm131_rf_defaults_lut[idx].val);
		}
	}

	/* Initialize the loop-through sleep/wakeup shadow registers. */
	pp->sleep_lt_backup.reg_0x00 = rReg8(0x00);
	pp->sleep_lt_backup.reg_0x34 = rReg8(0x34);
	pp->sleep_lt_backup.reg_0x35 = rReg8(0x35);

	return 0;
}

/******************************************************************************
**
**	Notch Functions
**
*******************************************************************************/
static void nm131_notch_ctl(int en, int width)
{
	tNmiPriv 	*pp = (tNmiPriv *)&chip.priv;

	if (en) {
		if (
			(pp->dconotch_ctl & (1ul << 1)) ||
			( ((pp->dconotch_ctl >> 12)& 0x7ul) != (uint32_t)width) 
			) {
				if(pp->std == nFM_RADIO) {
				nmi_debug(N_INFO, "*** Notch cannot work on FM. ***\n");
				return;
			}
			pp->dconotch_ctl &= ~(0x7ul << 12);
			pp->dconotch_ctl |= ((((uint32_t)width) & 0x7ul) << 12);
			pp->dconotch_ctl &= ~(1ul << 1);			
			//wReg32(0x110, pp->dconotch_ctl);//songbin 120518
			nmi_debug(N_INFO, "*** Notch Enable ***\n");
		}
	} else {
		if (!(pp->dconotch_ctl & (1ul << 1))) {			
			pp->dconotch_ctl |= (1ul << 1);
			//wReg32(0x110, pp->dconotch_ctl);//songbin 120518
			nmi_debug(N_INFO, "*** Notch Disable ***\n");
		}
	}

	return;
}

#if defined HAVE_FLOATING_POINT
static void nm131_set_notch_frequency(int32_t freq)
{
	uint32_t reg_i, reg_q;
	double foff, ppm, temp, fsamp;
	int temp2;
	tNmiPriv 		*pp = (tNmiPriv *)&chip.priv;

	foff = 0;
	ppm = ((double)pp->clk_off_f)/216000.0/(1ul << 9);	

	fsamp = 13500000 * (1 + ppm);


	temp = cos(2 * 3.14156 * ((freq + foff) / fsamp)); 
	temp2 = (int) (temp * (1ul <<20));
	reg_i = (temp2 < 0) ? ( (1 << 22) + temp2) : temp2;

	temp = sin(2 * 3.14156 * ((freq + foff) / fsamp)); 
	temp2 = (int) (temp * (1ul <<20));
	reg_q = (temp2 < 0) ? ( (1ul << 22) + temp2) : temp2;

	wReg32(0x114, reg_i);
	wReg32(0x118, reg_q);
	nmi_debug(N_INFO, "Notch: i (%08x), q (%08x)\n", reg_i, reg_q);
}
#endif

#if !defined USE_NM131_NOTCH_LUT
static void nm131_notch_set(int en, uint32_t frequency, int width)
{
	tNmiPriv 	*pp = (tNmiPriv *)&chip.priv;

	if (en) {
		int32_t spur_off;
		
		spur_off = frequency - pp->lofrequency;		
		nm131_set_notch_frequency(spur_off);
		nm131_notch_ctl(1, width);
	} else {
		nm131_notch_ctl(0, 0);
	}
}
#else
static void nm131_notch_set(int en, uint32_t frequency, int width)
{
	en = en;
	frequency = frequency;
	width = width;
	
	nmi_debug(N_ERR, "Notch calculation is not supportd on fixed point driver.\n");
}
#endif

#if defined USE_NM131_NOTCH_LUT

static void nm131_notch_spur(void)
{
	/**
	Call this function after nm131_tune_internal is done.
	This functions depends on pp->std, pp->lofrequency, pp->notchOn.
	**/
	tNmiPriv 	*pp = (tNmiPriv *)&chip.priv;	

	if(ISDTV(pp->std) || (pp->std == nFM_RADIO)) {
		nm131_notch_ctl(0, 0);
	} else {
		const tNmiNotchSpur *spurp;
		tNmiTvStd std;
		uint32_t frequency;
//printf("\n\n------Enter Spur---- pp->std = %d\n\n", pp->std);
		if ((pp->std == nNTSC) || (pp->std == nPAL_M) || (pp->std == nPAL_N)) {
			std = nNTSC;
		} else if ((pp->std == nPAL_G) || (pp->std == nSECAM_B)) {
			std = nPAL_G;
		} else {
			std = nPAL_K;
		}
		frequency = pp->frequency;

		for(spurp = &nm131_cvbs_notch_spur[0];
			spurp<&nm131_cvbs_notch_spur[nm131_cvbs_notch_spur_sz];
			spurp++) {
				if(std == spurp->std) {
					if(
						(frequency >= (spurp->frequency-150000)) &&
						(frequency <= (spurp->frequency+150000)))
					{
						printf("--00---\n");
						break;
					}
				}
		}

		if(spurp == &nm131_cvbs_notch_spur[nm131_cvbs_notch_spur_sz]) {
			nm131_notch_ctl(0, 0);
		} else {
			uint32_t val32; 

			val32 = spurp->reg_0x114_msb;
			val32 = (val32 << 16) | spurp->reg_0x114_lsb;
			wReg32(0x114, val32);

			val32 = spurp->reg_0x118_msb;
			val32 = (val32 << 16) | spurp->reg_0x118_lsb;
			wReg32(0x118, val32);	
			printf("--spurp->u8Width = %d---\n", spurp->u8Width);
			nm131_notch_ctl(1, spurp->u8Width);
		}
	}
}

void nm131_notch_dynamic(int open)
{
      if(open == 1)
      {
      	nm131_notch_spur();
      }
	  else
	  {
	     nm131_notch_ctl(0, 0);
	  }
}
#else
static void nm131_notch_spur(void)
{
	/**
	Call this function after nm131_tune_internal is done.
	This functions depends on pp->std, pp->lofrequency, pp->notchOn.
	**/
	tNmiPriv 	*pp = (tNmiPriv *)&chip.priv;	

	if(ISDTV(pp->std)  || (pp->std == nFM_RADIO)) {
		nm131_notch_ctl(0, 0);
	} else {
		tNmiTvStd std;

		if ((pp->std == nNTSC) || (pp->std == nPAL_M) || (pp->std == nPAL_N)) {
			std = nNTSC;
		} else if ((pp->std == nPAL_G) || (pp->std == nSECAM_B)) {
			std = nPAL_G;
		} else {
			std = nPAL_K;
		}

		if(			
			((pp->frequency >= ( 120250000-150000)) && (pp->frequency <= ( 120250000+150000)) && (std == nPAL_K)) ||
			((pp->frequency >= ( 168250000-150000)) && (pp->frequency <= ( 168250000+150000)) && (std == nPAL_K)) ||
			((pp->frequency >= ( 192250000-150000)) && (pp->frequency <= ( 192250000+150000)) && (std == nPAL_K)) ||
			((pp->frequency >= ( 216250000-150000)) && (pp->frequency <= ( 216250000+150000)) && (std == nPAL_K)) ||
			((pp->frequency >= ( 65750000-150000)) && (pp->frequency <= ( 65750000+150000)) && (std == nPAL_G))) {
				nm131_notch_ctl(0, 0);
		} else {
			uint32_t xo, bh, bl, hrmnch, hrmncl;

			xo = (uint32_t)chip.inp.xo * 1000;

			if(pp->lofrequency > pp->frequency) { /* CVBS spectrum is normal. */
				if ((std == nNTSC) || (std == nPAL_M) || (std == nPAL_N)) {
					bh = pp->frequency + (4500000 + 750000);
					bl = pp->frequency - 1250000;	
				} else if ((std == nPAL_G) || (std == nSECAM_B)) {
					bh = pp->frequency + (5500000 + 750000);
					bl = pp->frequency - 1250000;		
				} else /* if(std == nPAL_K) */ {
					bh = pp->frequency + (6500000 + 750000);
					bl = pp->frequency - 1250000;	
				}
			} else { /* CVBS spectrum is inverted. */
				if ((std == nNTSC) || (std == nPAL_M) || (std == nPAL_N)) {
					bl = pp->frequency - (4500000 + 750000);
					bh = pp->frequency + 1250000;	
				} else if ((std == nPAL_G) || (std == nSECAM_B)) {
					bl = pp->frequency - (5500000 + 750000);
					bh = pp->frequency + 1250000;		
				} else /* if(std == nPAL_K) */ {
					bl = pp->frequency - (6500000 + 750000);
					bh = pp->frequency + 1250000;	
				}
			}

			hrmnch = bh/xo;
			hrmncl = bl/xo;

			if(hrmnch == hrmncl) {
				nm131_notch_ctl(0, 0);
			} else {
				int32_t spur_off;

				spur_off = (int32_t)(hrmnch*xo) - (int32_t)pp->lofrequency;			
				nm131_set_notch_frequency(spur_off);
				nm131_notch_ctl(1, 7);
			}
		}
	}
}
#endif
/******************************************************************************
**
**	Sleep
**
*******************************************************************************/
/**
Requires pulling down CHIP_EN pin to reset. 
**/
void nm131_software_sleep(void)
{	
	uint32_t val32;

	val32 = rReg32(0x104);
	val32 &= ~(1ul << 0);
	wReg32(0x104, val32);
	wReg8(0x00, 0x04);	
	wReg8(0x34, 0x00);
	wReg8(0x35, 0x00);	
	wReg8(0x36, 0x04); /* Don't write 0 to avoid glitch on xo out. */	
	wReg8(0x00, 0x00);	
	val32 |= (1ul << 0);
	wReg32(0x104, val32);	
}

/**
Does does not require pulling down CHIP_EN pin to reset.
Loop through can work with this sleep mode.
**/
void nm131_software_sleep_lt(void)
{
	uint32_t val32;
	uint8_t val8;
	tNmiPriv 	*pp = (tNmiPriv *)&chip.priv;

	val32 = rReg32(0x104);
	val32 &= ~(1ul << 0);
	wReg32(0x104, val32);
	
	pp->sleep_lt_backup.reg_0x00 = rReg8(0x00);
	wReg8(0x00, 0x0d);

	val8 = rReg8(0x07);
	val8 &= ~(1 << 6);
	wReg8(0x07, val8);
	
	/* 
	* Turn off VHF filter. 
	* No need to turn it on during wake up since it is turned on 
	* in nm131_tuner_apply_vhf_filter() only when needed.
	*/
	val8 = rReg8(0x09);
	val8 &= ~(1 << 4);
	wReg8(0x09, val8);

	val8 = rReg8(0x0b);
	val8 &= ~(1 << 4);
	wReg8(0x0b, val8);

	pp->sleep_lt_backup.reg_0x34 = rReg8(0x34);
	wReg8(0x34, 0x00);
	pp->sleep_lt_backup.reg_0x35 = rReg8(0x35);
	wReg8(0x35, 0x00);

}
void nm131_software_wake_up_lt(void)
{
	uint32_t val32;
	uint8_t val8;
	tNmiPriv 	*pp = (tNmiPriv *)&chip.priv;	

	wReg8(0x00, pp->sleep_lt_backup.reg_0x00);

	val32 = rReg32(0x104);
	val32 |= (1ul << 0);
	wReg32(0x104, val32);
	
	

	val8 = rReg8(0x07);
	val8 |= (1 << 6);
	wReg8(0x07, val8);

/*	
	val8 = rReg8(0x09);
	val8 &= ~(1 << 4);
	wReg8(0x09, val8);
*/
	val8 = rReg8(0x0b);
	val8 |= (1 << 4);
	wReg8(0x0b, val8);

	wReg8(0x34, pp->sleep_lt_backup.reg_0x34);
	wReg8(0x35, pp->sleep_lt_backup.reg_0x35);

}


/******************************************************************************
**
**	External Register Access from Upper layers for debugging
**
*******************************************************************************/
static void wReg8Debug(uint8_t adr, uint8_t val8)
{
	tNmiPriv * pp = &chip.priv;
	
	wReg8(adr, val8);

	if(adr == 0x34) {
		if(ISCVBS(pp->output)) {
			if((val8 >= 0xf0) /* && (val8 <= 0xff) */) {
				pp->cvbsVideoAmp =  0xff - val8;
			} else {
				pp->cvbsVideoAmp = 0;
			}
		} else {
			pp->cvbsVideoAmp = 0;
		}
	} else if(adr == 0x35) {
		if(ISCVBS(pp->output)) {
			if((val8 >= 0x50) && (val8 <= 0x5f)) {
				uint32_t val32;

				val32 = rReg32(0x27c);
				if(val32 == 0x1818) {
					pp->cvbsVol = 16;
				} else {
					pp->cvbsVol = 0x5f - val8;
				}
			} else {
				pp->cvbsVol = 0;
			}
		} else {
			pp->cvbsVol = 0;
		}
	} else if(adr == 0x05) {
		pp->rf_reg_0x05 = val8;
	}
}
static void wReg32Debug(uint16_t adr, uint32_t val32)
{
	tNmiPriv * pp = &chip.priv;

	wReg32(adr, val32);

	if(adr == 0x110) {
		pp->dconotch_ctl = val32;		
	} else if(adr == 0x27c) {
		uint8_t val8 = rReg8(0x35);
		if(ISCVBS(pp->output)) {
			if((val8 >= 0x50) && (val8 <= 0x5f)) {
				if(val32 == 0x1818) {
					pp->cvbsVol = 16;
				} else {
					pp->cvbsVol = 0x5f - val8;
				}
			} else {
				pp->cvbsVol = 0;
			}
		} else {
			pp->cvbsVol = 0;
		}
	}
}

/******************************************************************************
**
**	Virtual Function Set Up
**
*******************************************************************************/

static void nm131_vtbl_init(tTnrVtbl *ptv)
{
	ptv->init                   = nm131_chip_init;
	ptv->getchipid              = nm131_get_chipid;
	ptv->r32                    = rReg32;
	ptv->w32                    = wReg32Debug;
	ptv->rfr                    = rReg8;
	ptv->rfw                    = wReg8Debug;
	ptv->tune                   = nm131_tune;
	ptv->getdagc                = nm131_demod_dagc_gain;
	ptv->agclock                = nm131_demod_get_agc_lock;
	ptv->cplllock               = nm131_demod_get_cpll_lock;
	ptv->getsnr                 = nm131_demod_get_snr;
	ptv->getfreqoffset          = nm131_demod_get_freq_offset;
	ptv->getplllevel            = nm131_demod_get_pll_level;
	ptv->reset                  = nm131_demod_soft_reset;
	ptv->reset_mosaic		= nm131_demod_soft_reset_mosaic;
	ptv->getstatus              = nm131_demod_get_status;
	ptv->getlna                 = nm131_get_lna_gain;
	ptv->setgain                = nm131_set_lna_gain;
	ptv->invertspectum          = nm131_invert_spectum;
	ptv->setifoutvoltage        = nm131_set_if_output_voltage;
	ptv->getifoutvoltage        = nm131_get_if_output_voltage;
	ptv->notchctl               = nm131_notch_set;
	ptv->setscanlevel           = nm131_set_scan_level;
	ptv->scan                   = nm131_scan;
	ptv->fmscan                 = nm131_fm_scan;
	ptv->fmavgrssi              = nm131_fm_get_window_rssi;
	ptv->fmscanlist             = nm131_fm_select_channel_list;
	ptv->fmseek                 = nm131_fm_seek_select;
	ptv->getadecrssi            = nm131_adec_get_rssi;
	ptv->getoverthcount         = nm131_get_overthcount;
	ptv->setfmscanth            = nm131_fm_set_scan_level;
	ptv->sleep                  = nm131_software_sleep;
	ptv->sleep_lt               = nm131_software_sleep_lt;
	ptv->wake_up_lt				= nm131_software_wake_up_lt;
	ptv->setvolume              = nm131_set_volume;
	ptv->getvolume              = nm131_get_volume;
	ptv->setvideoamp			= nm131_set_video_amplitude;
	ptv->getvideoamp			= nm131_get_video_amplitude;
	ptv->setbrightness          = nm131_set_brightness;
	ptv->getbrightness          = nm131_get_brightness;
	ptv->ltctrl                 = nm131_lt_ctrl;
	ptv->setmute				= nm131_set_mute;
	ptv->getmute				= nm131_get_mute;
}
