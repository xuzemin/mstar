/* 	CONFIDENTIAL
*********************************************************************************

	File:			dsp_coef_data.h
	Version:		1.00.00
	Description:	Coefficient Data

	Copyright(c) 2012 Yamaha Corporation

*********************************************************************************/

/* headroom coefficients */
static UC bIldAtt[] = {
0x08, 0x00     
};

static UC bAcAtt[] = {
0x10, 0x00     /* AC.Att[15:0] */
};

static UC bSvAtt[] = {
0x08, 0x00,    /* SV.Att[15:0]   */
0x00, 0x10     /* SV.FMAtt[15:0] */
};

static UC bLmtLevAdjDD2SP[] = {
0x40, 0x00,    /* LMT.HiTrim[15:0]  */
0x40, 0x00,    /* LMT.LoTrim[15:0]  */
0x00, 0x07,    /* LMT.HiLevAdj[3:0] */
0x00, 0x07     /* LMT.LoLevAdj[3:0] */
};


/* TopData coefficients */
static UC bTopData[] = {
0x40, 0x00,    /* Top.TopData0[15:0] */
0x20, 0x00,    /* Top.TopData1[15:0] */
0x80, 0x00,    /* Top.TopData2[15:0] */
0xC0, 0x00,    /* Top.TopData3[15:0] */
0x00, 0x08,    /* Top.TopData4[15:0] */
0x00, 0x01     /* Top.TopData5[15:0] */
};

/* Input level detector coefficients */
/* - select SDI0 input path */
static UC bIldSDI0Sel[] = {
0x40, 0x00,    /* ILD.SDI0Sel[15:0] */
0x00, 0x00     /* ILD.SDI1Sel[15:0] */
};



/* - disable input level detection */
static UC bIldOff[] = {
0x00, 0x00,    /* ILD.DetLev[15:0] */
0x00, 0x01,    /* ILD.DetTime[15:0] */
0x00, 0x00     /* ILD.DetRst[15:0]  */
};

/* Spacious sound 3D coefficients */
static UC bS3DNatural[] = {
/*
	detail
	 effect : This effect is the same as a sample command file "S3D Natural".

	usage
	 SetS3D(bS3DNatural);
*/
0x06, 0xA0,    /* S3D.S3DCore.Data0[15:0]   */
0x03, 0x50,    /* S3D.S3DCore.Data1[15:0]   */
0x06, 0xA0,    /* S3D.S3DCore.Data2[15:0]   */
0x5D, 0x64,    /* S3D.S3DCore.Data3[15:0]   */
0xD8, 0x1B,    /* S3D.S3DCore.Data4[15:0]   */
0x26, 0xA1,    /* S3D.S3DCore.Data5[15:0]   */
0xD0, 0xF6,    /* S3D.S3DCore.Data6[15:0]   */
0x40, 0x00,    /* S3D.S3DCore.Data7[15:0]   */
0x2C, 0xCD,    /* S3D.S3DCore.Data8[15:0]   */
0x29, 0xD6,    /* S3D.S3DCore.Data9[15:0]   */
0xDE, 0x0A,    /* S3D.S3DCore.Data10[15:0]  */
0x38, 0x20,    /* S3D.S3DCore.Data11[15:0]  */
0x14, 0x3D,    /* S3D.S3DCore.Data12[15:0]  */
0xDF, 0xED,    /* S3D.S3DCore.Data13[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data14[15:0]  */
0x1B, 0xCA,    /* S3D.S3DCore.Data15[15:0]  */
0x1B, 0xCA,    /* S3D.S3DCore.Data16[15:0]  */
0x08, 0x6C,    /* S3D.S3DCore.Data17[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data18[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data19[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data20[15:0]  */
0x10, 0x13,    /* S3D.S3DCore.Data21[15:0]  */
0x02, 0xA7,    /* S3D.S3DCore.Data22[15:0]  */
0x03, 0x53,    /* S3D.S3DCore.Data23[15:0]  */
0x05, 0x02,    /* S3D.S3DCore.Data24[15:0]  */
0x06, 0x96,    /* S3D.S3DCore.Data25[15:0]  */
0x07, 0x46,    /* S3D.S3DCore.Data26[15:0]  */
0x08, 0x11,    /* S3D.S3DCore.Data27[15:0]  */
0x09, 0x84,    /* S3D.S3DCore.Data28[15:0]  */
0x0A, 0xCE,    /* S3D.S3DCore.Data29[15:0]  */
0x0A, 0xE7,    /* S3D.S3DCore.Data30[15:0]  */
0x0C, 0x26,    /* S3D.S3DCore.Data31[15:0]  */
0x0C, 0xF1,    /* S3D.S3DCore.Data32[15:0]  */
0x0D, 0xBB,    /* S3D.S3DCore.Data33[15:0]  */
0x0E, 0x34,    /* S3D.S3DCore.Data34[15:0]  */
0x0E, 0x74,    /* S3D.S3DCore.Data35[15:0]  */
0x10, 0x02,    /* S3D.S3DCore.Data36[15:0]  */
0x11, 0xFC,    /* S3D.S3DCore.Data37[15:0]  */
0x15, 0x04,    /* S3D.S3DCore.Data38[15:0]  */
0x16, 0x2A,    /* S3D.S3DCore.Data39[15:0]  */
0x16, 0xFD,    /* S3D.S3DCore.Data40[15:0]  */
0x17, 0x86,    /* S3D.S3DCore.Data41[15:0]  */
0x1A, 0x50,    /* S3D.S3DCore.Data42[15:0]  */
0x1A, 0x67,    /* S3D.S3DCore.Data43[15:0]  */
0x1B, 0x4F,    /* S3D.S3DCore.Data44[15:0]  */
0x1E, 0xC2,    /* S3D.S3DCore.Data45[15:0]  */
0x1F, 0x5C,    /* S3D.S3DCore.Data46[15:0]  */
0x1F, 0x65,    /* S3D.S3DCore.Data47[15:0]  */
0x21, 0x94,    /* S3D.S3DCore.Data48[15:0]  */
0x21, 0x96,    /* S3D.S3DCore.Data49[15:0]  */
0x26, 0xDB,    /* S3D.S3DCore.Data50[15:0]  */
0x27, 0x1B,    /* S3D.S3DCore.Data51[15:0]  */
0x27, 0xD5,    /* S3D.S3DCore.Data52[15:0]  */
0x28, 0x02,    /* S3D.S3DCore.Data53[15:0]  */
0x29, 0x75,    /* S3D.S3DCore.Data54[15:0]  */
0x2B, 0x66,    /* S3D.S3DCore.Data55[15:0]  */
0x2B, 0xA2,    /* S3D.S3DCore.Data56[15:0]  */
0x2C, 0xB2,    /* S3D.S3DCore.Data57[15:0]  */
0x30, 0x12,    /* S3D.S3DCore.Data58[15:0]  */
0x39, 0xD1,    /* S3D.S3DCore.Data59[15:0]  */
0x10, 0x1C,    /* S3D.S3DCore.Data60[15:0]  */
0x49, 0x3B,    /* S3D.S3DCore.Data61[15:0]  */
0x41, 0xBA,    /* S3D.S3DCore.Data62[15:0]  */
0x16, 0x6B,    /* S3D.S3DCore.Data63[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data64[15:0]  */
0x1E, 0x78,    /* S3D.S3DCore.Data65[15:0]  */
0x30, 0x38,    /* S3D.S3DCore.Data66[15:0]  */
0x50, 0xA4,    /* S3D.S3DCore.Data67[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data68[15:0]  */
0x6B, 0xA6,    /* S3D.S3DCore.Data69[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data70[15:0]  */
0x30, 0x56,    /* S3D.S3DCore.Data71[15:0]  */
0x37, 0x3A,    /* S3D.S3DCore.Data72[15:0]  */
0x5C, 0x16,    /* S3D.S3DCore.Data73[15:0]  */
0x22, 0x32,    /* S3D.S3DCore.Data74[15:0]  */
0x1F, 0x77,    /* S3D.S3DCore.Data75[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data76[15:0]  */
0x19, 0x33,    /* S3D.S3DCore.Data77[15:0]  */
0x2E, 0xCD,    /* S3D.S3DCore.Data78[15:0]  */
0x23, 0xF3,    /* S3D.S3DCore.Data79[15:0]  */
0x16, 0x07,    /* S3D.S3DCore.Data80[15:0]  */
0x22, 0x13,    /* S3D.S3DCore.Data81[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data82[15:0]  */
0x01, 0x4A,    /* S3D.S3DCore.Data83[15:0]  */
0x34, 0x7B,    /* S3D.S3DCore.Data84[15:0]  */
0x18, 0x36,    /* S3D.S3DCore.Data85[15:0]  */
0x27, 0x80,    /* S3D.S3DCore.Data86[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data87[15:0]  */
0x2C, 0x9D,    /* S3D.S3DCore.Data88[15:0]  */
0x00, 0x01,    /* S3D.S3DCore.Data89[15:0]  */
0x0B, 0x3B,    /* S3D.S3DCore.Data90[15:0]  */
0x30, 0xBB,    /* S3D.S3DCore.Data91[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data92[15:0]  */
0x1E, 0x64,    /* S3D.S3DCore.Data93[15:0]  */
0x29, 0x7F,    /* S3D.S3DCore.Data94[15:0]  */
0x0A, 0x79,    /* S3D.S3DCore.Data95[15:0]  */
0x1B, 0xA7,    /* S3D.S3DCore.Data96[15:0]  */
0x35, 0xB3,    /* S3D.S3DCore.Data97[15:0]  */
0x0D, 0x11,    /* S3D.S3DCore.Data98[15:0]  */
0x00, 0x00,    /* S3D.S3DCore.Data99[15:0]  */
0x46, 0xEE,    /* S3D.S3DCore.Data100[15:0] */
0x35, 0x2D,    /* S3D.S3DCore.Data101[15:0] */
0x1D, 0xA7,    /* S3D.S3DCore.Data102[15:0] */
0x00, 0x01,    /* S3D.S3DCore.Data103[15:0] */
0x05, 0xDD,    /* S3D.S3DCore.Data104[15:0] */
0x3B, 0x52,    /* S3D.S3DCore.Data105[15:0] */
0x31, 0x36,    /* S3D.S3DCore.Data106[15:0] */
0x39, 0x17,    /* S3D.S3DCore.Data107[15:0] */
0x00, 0x00,    /* S3D.S3DCore.Data108[15:0] */
0x00, 0x00,    /* S3D.S3DCore.Data109[15:0] */
0x00, 0x00,    /* S3D.S3DCore.Data110[15:0] */
0x0C, 0x92,    /* S3D.S3DCore.Data111[15:0] */
0x20, 0x6B,    /* S3D.S3DCore.Data112[15:0] */
0x44, 0x45,    /* S3D.S3DCore.Data113[15:0] */
0x1C, 0xC0,    /* S3D.S3DCore.Data114[15:0] */
0x0D, 0x3D,    /* S3D.S3DCore.Data115[15:0] */
0x45, 0x39,    /* S3D.S3DCore.Data116[15:0] */
0x31, 0xD6,    /* S3D.S3DCore.Data117[15:0] */
0x00, 0x02,    /* S3D.S3DCore.Data118[15:0] */
0x2D, 0xA9,    /* S3D.S3DCore.Data119[15:0] */
0x2A, 0x6B,    /* S3D.S3DCore.Data120[15:0] */
0x00, 0x00,    /* S3D.S3DCore.Data121[15:0] */
0x29, 0x6F,    /* S3D.S3DCore.Data122[15:0] */
0x0F, 0xD3,    /* S3D.S3DCore.Data123[15:0] */
0x37, 0x4B,    /* S3D.S3DCore.Data124[15:0] */
0x00, 0x03,    /* S3D.S3DCore.Data125[15:0] */
0x2C, 0x9F,    /* S3D.S3DCore.Data126[15:0] */
0x26, 0x37,    /* S3D.S3DCore.Data127[15:0] */
0x14, 0x7D,    /* S3D.S3DCore.Data128[15:0] */
0x30, 0xA5,    /* S3D.S3DCore.Data129[15:0] */
0x1F, 0x0A,    /* S3D.S3DCore.Data130[15:0] */
0x00, 0x40,    /* S3D.S3DCore.Data131[15:0] */
0x26, 0x5C,    /* S3D.S3DCore.Data132[15:0] */
0x40, 0x00,    /* S3D.S3DCore.Data133[15:0] */
0x20, 0x13,    /* S3D.S3DCore.Data134[15:0] */
0x32, 0xD6,    /* S3D.S3DCore.Data135[15:0] */
0x19, 0x7B,    /* S3D.S3DCore.Data136[15:0] */
0x20, 0x00,    /* EQ0.a0[15:0]              */
0x00, 0x00,    /* EQ0.a1[15:0]              */
0x00, 0x00,    /* EQ0.a2[15:0]              */
0x00, 0x00,    /* EQ0.b1[15:0]              */
0x00, 0x00,    /* EQ0.b2[15:0]              */
0x40, 0x00,    /* EQ1.a0[15:0]              */
0x00, 0x00,    /* EQ1.a1[15:0]              */
0x00, 0x00,    /* EQ1.a2[15:0]              */
0x00, 0x00,    /* EQ1.b1[15:0]              */
0x00, 0x00,    /* EQ1.b2[15:0]              */
0x20, 0x00,    /* EQ2.a0[15:0]              */
0x00, 0x00,    /* EQ2.a1[15:0]              */
0x00, 0x00,    /* EQ2.a2[15:0]              */
0x00, 0x00,    /* EQ2.b1[15:0]              */
0x00, 0x00,    /* EQ2.b2[15:0]              */
0x2D, 0x4F     /* S3DLev[15:0]              */
};

static UC bS3DOff[] = {
0x40, 0x00,    /* S3D.ThruSel[15:0] */
0x00, 0x00     /* S3D.S3DSel[15:0]  */
};

/* Harmonics enhancer Extended coefficients */
static UC bHarmonicsExpander[] = {
/*
	detail
	 effect : This effect is the same as a sample command file "HXT Bass1 + High1".

	usage
	 SetHE(bHarmonicsExpander);
*/
0x00, 0x02,    /* HXT.HXTCore.Data0[15:0]  */
0x00, 0x03,    /* HXT.HXTCore.Data1[15:0]  */
0x00, 0x02,    /* HXT.HXTCore.Data2[15:0]  */
0x7E, 0x1B,    /* HXT.HXTCore.Data3[15:0]  */
0xC1, 0xDE,    /* HXT.HXTCore.Data4[15:0]  */
0x3F, 0xA5,    /* HXT.HXTCore.Data5[15:0]  */
0x80, 0xB6,    /* HXT.HXTCore.Data6[15:0]  */
0x3F, 0xA5,    /* HXT.HXTCore.Data7[15:0]  */
0x7F, 0x4A,    /* HXT.HXTCore.Data8[15:0]  */
0xC0, 0xB5,    /* HXT.HXTCore.Data9[15:0]  */
0x12, 0xBF,    /* HXT.HXTCore.Data10[15:0] */
0x25, 0x7D,    /* HXT.HXTCore.Data11[15:0] */
0x12, 0xBF,    /* HXT.HXTCore.Data12[15:0] */
0x00, 0x00,    /* HXT.HXTCore.Data13[15:0] */
0xF5, 0x05,    /* HXT.HXTCore.Data14[15:0] */
0x20, 0xFB,    /* HXT.HXTCore.Data15[15:0] */
0xBE, 0x0A,    /* HXT.HXTCore.Data16[15:0] */
0x20, 0xFB,    /* HXT.HXTCore.Data17[15:0] */
0x31, 0xEB,    /* HXT.HXTCore.Data18[15:0] */
0xEE, 0x00,    /* HXT.HXTCore.Data19[15:0] */
0x3F, 0xB2,    /* HXT.HXTCore.Data20[15:0] */
0x10, 0x00,    /* HXT.HXTCore.Data21[15:0] */
0x10, 0x13,    /* HXT.HXTCore.Data22[15:0] */
0x40, 0x00,    /* HXT.HXTCore.Data23[15:0] */
0x07, 0xF2,    /* HXT.HXTCore.Data24[15:0] */
0x0A, 0xA1,    /* HXT.HXTCore.Data25[15:0] */
0x08, 0x00,    /* HXT.HXTCore.Data26[15:0] */
0x00, 0xE2,    /* HXT.HXTCore.Data27[15:0] */
0x00, 0xC0,    /* HXT.HXTCore.Data28[15:0] */
0x00, 0x00,    /* HXT.HXTCore.Data29[15:0] */
0x00, 0x66,    /* HXT.HXTCore.Data30[15:0] */
0xFD, 0xB9,    /* HXT.HXTCore.Data31[15:0] */
0x00, 0xB2,    /* HXT.HXTCore.Data32[15:0] */
0x64, 0xE7,    /* HXT.HXTCore.Data33[15:0] */
0x03, 0x36,    /* HXT.HXTCore.Data34[15:0] */
0x74, 0xDA,    /* HXT.HXTCore.Data35[15:0] */
0xC3, 0x04,    /* HXT.HXTCore.Data36[15:0] */
0xB3, 0x63,    /* HXT.HXTCore.Data37[15:0] */
0x0E, 0x33,    /* HXT.HXTCore.Data38[15:0] */
0xFE, 0xB8,    /* HXT.HXTCore.Data39[15:0] */
0x00, 0x0B,    /* HXT.HXTCore.Data40[15:0] */
0x00, 0x16,    /* HXT.HXTCore.Data41[15:0] */
0x00, 0x0B,    /* HXT.HXTCore.Data42[15:0] */
0x7B, 0x43,    /* HXT.HXTCore.Data43[15:0] */
0xC4, 0x91,    /* HXT.HXTCore.Data44[15:0] */
0x3F, 0xA5,    /* HXT.HXTCore.Data45[15:0] */
0x80, 0xB6,    /* HXT.HXTCore.Data46[15:0] */
0x3F, 0xA5,    /* HXT.HXTCore.Data47[15:0] */
0x7F, 0x4A,    /* HXT.HXTCore.Data48[15:0] */
0xC0, 0xB5,    /* HXT.HXTCore.Data49[15:0] */
0x1B, 0x6C,    /* HXT.HXTCore.Data50[15:0] */
0x36, 0xD9,    /* HXT.HXTCore.Data51[15:0] */
0x1B, 0x6C,    /* HXT.HXTCore.Data52[15:0] */
0xCA, 0x1B,    /* HXT.HXTCore.Data53[15:0] */
0x08, 0x34,    /* HXT.HXTCore.Data54[15:0] */
0x17, 0xEF,    /* HXT.HXTCore.Data55[15:0] */
0xD0, 0x22,    /* HXT.HXTCore.Data56[15:0] */
0x17, 0xEF,    /* HXT.HXTCore.Data57[15:0] */
0x13, 0xAF,    /* HXT.HXTCore.Data58[15:0] */
0xF3, 0xF2,    /* HXT.HXTCore.Data59[15:0] */
0x00, 0x03,    /* HXT.HXTCore.Data60[15:0] */
0x00, 0x00,    /* HXT.HXTCore.Data61[15:0] */
0x00, 0x03,    /* HXT.HXTCore.Data62[15:0] */
0x10, 0x00,    /* HXT.HXTCore.Data63[15:0] */
0x01, 0xCC,    /* HXT.HXTCore.Data64[15:0] */
0x40, 0x76,    /* HXT.HXTCore.Data65[15:0] */
0x91, 0xAE,    /* HXT.HXTCore.Data66[15:0] */
0x30, 0x06,    /* HXT.HXTCore.Data67[15:0] */
0x6E, 0x52,    /* HXT.HXTCore.Data68[15:0] */
0xCF, 0x84,    /* HXT.HXTCore.Data69[15:0] */
0x43, 0x95,    /* HXT.HXTCore.Data70[15:0] */
0x06, 0xA0,    /* HXT.HXTCore.Data71[15:0] */
0xD3, 0xBF,    /* HXT.HXTCore.Data72[15:0] */
0xF8, 0x77,    /* HXT.HXTCore.Data73[15:0] */
0x29, 0x95,    /* HXT.HXTCore.Data74[15:0] */
0x10, 0x00,    /* HXT.DryMix[15:0]        */
0x10, 0x00     /* HXT.WetMix[15:0]        */
};

static UC bHXTOff[] = {
0x40, 0x00,    /* HXT.ThruSel[15:0] */
0x00, 0x00     /* HXT.HESel[15:0]   */
};

/* Acoustic total-liner EQ core coefficients */
static UC bAEQCore[] = {
/*
	detail
	 effect : This effect is the same as a sample command file "AEQ On",
	          and sample for a specified speaker cabinet.

	usage
	 SetAEQ(bAEQCore, bAEQPEQ);
*/
0x00, 0x07,    /* AC.AEQCore.Data0[15:0]   */
0x00, 0x07,    /* AC.AEQCore.Data1[15:0]   */
0x00, 0x25,    /* AC.AEQCore.Data2[15:0]   */
0x00, 0x25,    /* AC.AEQCore.Data3[15:0]   */
0x00, 0x3B,    /* AC.AEQCore.Data4[15:0]   */
0x00, 0x3B,    /* AC.AEQCore.Data5[15:0]   */
0x00, 0x3F,    /* AC.AEQCore.Data6[15:0]   */
0x00, 0x3F,    /* AC.AEQCore.Data7[15:0]   */
0x00, 0x38,    /* AC.AEQCore.Data8[15:0]   */
0x00, 0x38,    /* AC.AEQCore.Data9[15:0]   */
0x00, 0x2B,    /* AC.AEQCore.Data10[15:0]  */
0x00, 0x2B,    /* AC.AEQCore.Data11[15:0]  */
0x00, 0x10,    /* AC.AEQCore.Data12[15:0]  */
0x00, 0x10,    /* AC.AEQCore.Data13[15:0]  */
0xFF, 0xE3,    /* AC.AEQCore.Data14[15:0]  */
0xFF, 0xE3,    /* AC.AEQCore.Data15[15:0]  */
0xFF, 0xBC,    /* AC.AEQCore.Data16[15:0]  */
0xFF, 0xBC,    /* AC.AEQCore.Data17[15:0]  */
0xFF, 0xB8,    /* AC.AEQCore.Data18[15:0]  */
0xFF, 0xB8,    /* AC.AEQCore.Data19[15:0]  */
0xFF, 0xCD,    /* AC.AEQCore.Data20[15:0]  */
0xFF, 0xCD,    /* AC.AEQCore.Data21[15:0]  */
0xFF, 0xDB,    /* AC.AEQCore.Data22[15:0]  */
0xFF, 0xDB,    /* AC.AEQCore.Data23[15:0]  */
0xFF, 0xD7,    /* AC.AEQCore.Data24[15:0]  */
0xFF, 0xD7,    /* AC.AEQCore.Data25[15:0]  */
0xFF, 0xD3,    /* AC.AEQCore.Data26[15:0]  */
0xFF, 0xD3,    /* AC.AEQCore.Data27[15:0]  */
0xFF, 0xD7,    /* AC.AEQCore.Data28[15:0]  */
0xFF, 0xD7,    /* AC.AEQCore.Data29[15:0]  */
0xFF, 0xD4,    /* AC.AEQCore.Data30[15:0]  */
0xFF, 0xD4,    /* AC.AEQCore.Data31[15:0]  */
0xFF, 0xC7,    /* AC.AEQCore.Data32[15:0]  */
0xFF, 0xC7,    /* AC.AEQCore.Data33[15:0]  */
0xFF, 0xC4,    /* AC.AEQCore.Data34[15:0]  */
0xFF, 0xC4,    /* AC.AEQCore.Data35[15:0]  */
0xFF, 0xD9,    /* AC.AEQCore.Data36[15:0]  */
0xFF, 0xD9,    /* AC.AEQCore.Data37[15:0]  */
0xFF, 0xF1,    /* AC.AEQCore.Data38[15:0]  */
0xFF, 0xF1,    /* AC.AEQCore.Data39[15:0]  */
0xFF, 0xFC,    /* AC.AEQCore.Data40[15:0]  */
0xFF, 0xFC,    /* AC.AEQCore.Data41[15:0]  */
0x00, 0x05,    /* AC.AEQCore.Data42[15:0]  */
0x00, 0x05,    /* AC.AEQCore.Data43[15:0]  */
0x00, 0x17,    /* AC.AEQCore.Data44[15:0]  */
0x00, 0x17,    /* AC.AEQCore.Data45[15:0]  */
0x00, 0x20,    /* AC.AEQCore.Data46[15:0]  */
0x00, 0x20,    /* AC.AEQCore.Data47[15:0]  */
0x00, 0x08,    /* AC.AEQCore.Data48[15:0]  */
0x00, 0x08,    /* AC.AEQCore.Data49[15:0]  */
0xFF, 0xE3,    /* AC.AEQCore.Data50[15:0]  */
0xFF, 0xE3,    /* AC.AEQCore.Data51[15:0]  */
0xFF, 0xDB,    /* AC.AEQCore.Data52[15:0]  */
0xFF, 0xDB,    /* AC.AEQCore.Data53[15:0]  */
0xFF, 0xEC,    /* AC.AEQCore.Data54[15:0]  */
0xFF, 0xEC,    /* AC.AEQCore.Data55[15:0]  */
0xFF, 0xE8,    /* AC.AEQCore.Data56[15:0]  */
0xFF, 0xE8,    /* AC.AEQCore.Data57[15:0]  */
0xFF, 0xB4,    /* AC.AEQCore.Data58[15:0]  */
0xFF, 0xB4,    /* AC.AEQCore.Data59[15:0]  */
0xFF, 0x7A,    /* AC.AEQCore.Data60[15:0]  */
0xFF, 0x7A,    /* AC.AEQCore.Data61[15:0]  */
0xFF, 0x6F,    /* AC.AEQCore.Data62[15:0]  */
0xFF, 0x6F,    /* AC.AEQCore.Data63[15:0]  */
0xFF, 0x94,    /* AC.AEQCore.Data64[15:0]  */
0xFF, 0x94,    /* AC.AEQCore.Data65[15:0]  */
0xFF, 0xB8,    /* AC.AEQCore.Data66[15:0]  */
0xFF, 0xB8,    /* AC.AEQCore.Data67[15:0]  */
0xFF, 0xBB,    /* AC.AEQCore.Data68[15:0]  */
0xFF, 0xBB,    /* AC.AEQCore.Data69[15:0]  */
0xFF, 0xA7,    /* AC.AEQCore.Data70[15:0]  */
0xFF, 0xA7,    /* AC.AEQCore.Data71[15:0]  */
0xFF, 0x95,    /* AC.AEQCore.Data72[15:0]  */
0xFF, 0x95,    /* AC.AEQCore.Data73[15:0]  */
0xFF, 0x9B,    /* AC.AEQCore.Data74[15:0]  */
0xFF, 0x9B,    /* AC.AEQCore.Data75[15:0]  */
0xFF, 0xBE,    /* AC.AEQCore.Data76[15:0]  */
0xFF, 0xBE,    /* AC.AEQCore.Data77[15:0]  */
0xFF, 0xEE,    /* AC.AEQCore.Data78[15:0]  */
0xFF, 0xEE,    /* AC.AEQCore.Data79[15:0]  */
0x00, 0x02,    /* AC.AEQCore.Data80[15:0]  */
0x00, 0x02,    /* AC.AEQCore.Data81[15:0]  */
0xFF, 0xD8,    /* AC.AEQCore.Data82[15:0]  */
0xFF, 0xD8,    /* AC.AEQCore.Data83[15:0]  */
0xFF, 0x83,    /* AC.AEQCore.Data84[15:0]  */
0xFF, 0x83,    /* AC.AEQCore.Data85[15:0]  */
0xFF, 0x42,    /* AC.AEQCore.Data86[15:0]  */
0xFF, 0x42,    /* AC.AEQCore.Data87[15:0]  */
0xFF, 0x42,    /* AC.AEQCore.Data88[15:0]  */
0xFF, 0x42,    /* AC.AEQCore.Data89[15:0]  */
0xFF, 0x6C,    /* AC.AEQCore.Data90[15:0]  */
0xFF, 0x6C,    /* AC.AEQCore.Data91[15:0]  */
0xFF, 0x89,    /* AC.AEQCore.Data92[15:0]  */
0xFF, 0x89,    /* AC.AEQCore.Data93[15:0]  */
0xFF, 0x78,    /* AC.AEQCore.Data94[15:0]  */
0xFF, 0x78,    /* AC.AEQCore.Data95[15:0]  */
0xFF, 0x4C,    /* AC.AEQCore.Data96[15:0]  */
0xFF, 0x4C,    /* AC.AEQCore.Data97[15:0]  */
0xFF, 0x32,    /* AC.AEQCore.Data98[15:0]  */
0xFF, 0x32,    /* AC.AEQCore.Data99[15:0]  */
0xFF, 0x43,    /* AC.AEQCore.Data100[15:0] */
0xFF, 0x43,    /* AC.AEQCore.Data101[15:0] */
0xFF, 0x6A,    /* AC.AEQCore.Data102[15:0] */
0xFF, 0x6A,    /* AC.AEQCore.Data103[15:0] */
0xFF, 0x76,    /* AC.AEQCore.Data104[15:0] */
0xFF, 0x76,    /* AC.AEQCore.Data105[15:0] */
0xFF, 0x55,    /* AC.AEQCore.Data106[15:0] */
0xFF, 0x55,    /* AC.AEQCore.Data107[15:0] */
0xFF, 0x34,    /* AC.AEQCore.Data108[15:0] */
0xFF, 0x34,    /* AC.AEQCore.Data109[15:0] */
0xFF, 0x48,    /* AC.AEQCore.Data110[15:0] */
0xFF, 0x48,    /* AC.AEQCore.Data111[15:0] */
0xFF, 0x7B,    /* AC.AEQCore.Data112[15:0] */
0xFF, 0x7B,    /* AC.AEQCore.Data113[15:0] */
0xFF, 0x84,    /* AC.AEQCore.Data114[15:0] */
0xFF, 0x84,    /* AC.AEQCore.Data115[15:0] */
0xFF, 0x52,    /* AC.AEQCore.Data116[15:0] */
0xFF, 0x52,    /* AC.AEQCore.Data117[15:0] */
0xFF, 0x3C,    /* AC.AEQCore.Data118[15:0] */
0xFF, 0x3C,    /* AC.AEQCore.Data119[15:0] */
0xFF, 0x82,    /* AC.AEQCore.Data120[15:0] */
0xFF, 0x82,    /* AC.AEQCore.Data121[15:0] */
0xFF, 0xDA,    /* AC.AEQCore.Data122[15:0] */
0xFF, 0xDA,    /* AC.AEQCore.Data123[15:0] */
0xFF, 0xC9,    /* AC.AEQCore.Data124[15:0] */
0xFF, 0xC9,    /* AC.AEQCore.Data125[15:0] */
0xFF, 0x53,    /* AC.AEQCore.Data126[15:0] */
0xFF, 0x53,    /* AC.AEQCore.Data127[15:0] */
0xFF, 0x08,    /* AC.AEQCore.Data128[15:0] */
0xFF, 0x08,    /* AC.AEQCore.Data129[15:0] */
0xFF, 0x44,    /* AC.AEQCore.Data130[15:0] */
0xFF, 0x44,    /* AC.AEQCore.Data131[15:0] */
0xFF, 0xB7,    /* AC.AEQCore.Data132[15:0] */
0xFF, 0xB7,    /* AC.AEQCore.Data133[15:0] */
0xFF, 0xDF,    /* AC.AEQCore.Data134[15:0] */
0xFF, 0xDF,    /* AC.AEQCore.Data135[15:0] */
0xFF, 0xAF,    /* AC.AEQCore.Data136[15:0] */
0xFF, 0xAF,    /* AC.AEQCore.Data137[15:0] */
0xFF, 0x80,    /* AC.AEQCore.Data138[15:0] */
0xFF, 0x80,    /* AC.AEQCore.Data139[15:0] */
0xFF, 0x86,    /* AC.AEQCore.Data140[15:0] */
0xFF, 0x86,    /* AC.AEQCore.Data141[15:0] */
0xFF, 0xAA,    /* AC.AEQCore.Data142[15:0] */
0xFF, 0xAA,    /* AC.AEQCore.Data143[15:0] */
0xFF, 0xD8,    /* AC.AEQCore.Data144[15:0] */
0xFF, 0xD8,    /* AC.AEQCore.Data145[15:0] */
0x00, 0x12,    /* AC.AEQCore.Data146[15:0] */
0x00, 0x12,    /* AC.AEQCore.Data147[15:0] */
0x00, 0x41,    /* AC.AEQCore.Data148[15:0] */
0x00, 0x41,    /* AC.AEQCore.Data149[15:0] */
0x00, 0x41,    /* AC.AEQCore.Data150[15:0] */
0x00, 0x41,    /* AC.AEQCore.Data151[15:0] */
0x00, 0x2D,    /* AC.AEQCore.Data152[15:0] */
0x00, 0x2D,    /* AC.AEQCore.Data153[15:0] */
0x00, 0x40,    /* AC.AEQCore.Data154[15:0] */
0x00, 0x40,    /* AC.AEQCore.Data155[15:0] */
0x00, 0x64,    /* AC.AEQCore.Data156[15:0] */
0x00, 0x64,    /* AC.AEQCore.Data157[15:0] */
0x00, 0x48,    /* AC.AEQCore.Data158[15:0] */
0x00, 0x48,    /* AC.AEQCore.Data159[15:0] */
0xFF, 0xFA,    /* AC.AEQCore.Data160[15:0] */
0xFF, 0xFA,    /* AC.AEQCore.Data161[15:0] */
0xFF, 0xF1,    /* AC.AEQCore.Data162[15:0] */
0xFF, 0xF1,    /* AC.AEQCore.Data163[15:0] */
0x00, 0x38,    /* AC.AEQCore.Data164[15:0] */
0x00, 0x38,    /* AC.AEQCore.Data165[15:0] */
0x00, 0x32,    /* AC.AEQCore.Data166[15:0] */
0x00, 0x32,    /* AC.AEQCore.Data167[15:0] */
0xFF, 0x9E,    /* AC.AEQCore.Data168[15:0] */
0xFF, 0x9E,    /* AC.AEQCore.Data169[15:0] */
0xFF, 0x50,    /* AC.AEQCore.Data170[15:0] */
0xFF, 0x50,    /* AC.AEQCore.Data171[15:0] */
0x00, 0x24,    /* AC.AEQCore.Data172[15:0] */
0x00, 0x24,    /* AC.AEQCore.Data173[15:0] */
0x01, 0x86,    /* AC.AEQCore.Data174[15:0] */
0x01, 0x86,    /* AC.AEQCore.Data175[15:0] */
0x02, 0x0A,    /* AC.AEQCore.Data176[15:0] */
0x02, 0x0A,    /* AC.AEQCore.Data177[15:0] */
0x01, 0x94,    /* AC.AEQCore.Data178[15:0] */
0x01, 0x94,    /* AC.AEQCore.Data179[15:0] */
0x01, 0x95,    /* AC.AEQCore.Data180[15:0] */
0x01, 0x95,    /* AC.AEQCore.Data181[15:0] */
0x02, 0xB1,    /* AC.AEQCore.Data182[15:0] */
0x02, 0xB1,    /* AC.AEQCore.Data183[15:0] */
0x03, 0x67,    /* AC.AEQCore.Data184[15:0] */
0x03, 0x67,    /* AC.AEQCore.Data185[15:0] */
0x02, 0x4D,    /* AC.AEQCore.Data186[15:0] */
0x02, 0x4D,    /* AC.AEQCore.Data187[15:0] */
0x00, 0x93,    /* AC.AEQCore.Data188[15:0] */
0x00, 0x93,    /* AC.AEQCore.Data189[15:0] */
0x00, 0x8C,    /* AC.AEQCore.Data190[15:0] */
0x00, 0x8C,    /* AC.AEQCore.Data191[15:0] */
0x02, 0x11,    /* AC.AEQCore.Data192[15:0] */
0x02, 0x11,    /* AC.AEQCore.Data193[15:0] */
0x02, 0x8A,    /* AC.AEQCore.Data194[15:0] */
0x02, 0x8A,    /* AC.AEQCore.Data195[15:0] */
0x00, 0xE1,    /* AC.AEQCore.Data196[15:0] */
0x00, 0xE1,    /* AC.AEQCore.Data197[15:0] */
0xFF, 0x60,    /* AC.AEQCore.Data198[15:0] */
0xFF, 0x60,    /* AC.AEQCore.Data199[15:0] */
0x00, 0x72,    /* AC.AEQCore.Data200[15:0] */
0x00, 0x72,    /* AC.AEQCore.Data201[15:0] */
0x03, 0x03,    /* AC.AEQCore.Data202[15:0] */
0x03, 0x03,    /* AC.AEQCore.Data203[15:0] */
0x04, 0x05,    /* AC.AEQCore.Data204[15:0] */
0x04, 0x05,    /* AC.AEQCore.Data205[15:0] */
0x02, 0xC1,    /* AC.AEQCore.Data206[15:0] */
0x02, 0xC1,    /* AC.AEQCore.Data207[15:0] */
0x01, 0xA6,    /* AC.AEQCore.Data208[15:0] */
0x01, 0xA6,    /* AC.AEQCore.Data209[15:0] */
0x02, 0x97,    /* AC.AEQCore.Data210[15:0] */
0x02, 0x97,    /* AC.AEQCore.Data211[15:0] */
0x04, 0x7A,    /* AC.AEQCore.Data212[15:0] */
0x04, 0x7A,    /* AC.AEQCore.Data213[15:0] */
0x05, 0x76,    /* AC.AEQCore.Data214[15:0] */
0x05, 0x76,    /* AC.AEQCore.Data215[15:0] */
0x05, 0x9C,    /* AC.AEQCore.Data216[15:0] */
0x05, 0x9C,    /* AC.AEQCore.Data217[15:0] */
0x05, 0xCB,    /* AC.AEQCore.Data218[15:0] */
0x05, 0xCB,    /* AC.AEQCore.Data219[15:0] */
0x05, 0xCC,    /* AC.AEQCore.Data220[15:0] */
0x05, 0xCC,    /* AC.AEQCore.Data221[15:0] */
0x05, 0x8B,    /* AC.AEQCore.Data222[15:0] */
0x05, 0x8B,    /* AC.AEQCore.Data223[15:0] */
0x06, 0x1C,    /* AC.AEQCore.Data224[15:0] */
0x06, 0x1C,    /* AC.AEQCore.Data225[15:0] */
0x07, 0x2F,    /* AC.AEQCore.Data226[15:0] */
0x07, 0x2F,    /* AC.AEQCore.Data227[15:0] */
0x06, 0x1A,    /* AC.AEQCore.Data228[15:0] */
0x06, 0x1A,    /* AC.AEQCore.Data229[15:0] */
0x02, 0x82,    /* AC.AEQCore.Data230[15:0] */
0x02, 0x82,    /* AC.AEQCore.Data231[15:0] */
0x00, 0xD4,    /* AC.AEQCore.Data232[15:0] */
0x00, 0xD4,    /* AC.AEQCore.Data233[15:0] */
0x03, 0xE0,    /* AC.AEQCore.Data234[15:0] */
0x03, 0xE0,    /* AC.AEQCore.Data235[15:0] */
0x07, 0x30,    /* AC.AEQCore.Data236[15:0] */
0x07, 0x30,    /* AC.AEQCore.Data237[15:0] */
0x04, 0xEA,    /* AC.AEQCore.Data238[15:0] */
0x04, 0xEA,    /* AC.AEQCore.Data239[15:0] */
0xFF, 0x53,    /* AC.AEQCore.Data240[15:0] */
0xFF, 0x53,    /* AC.AEQCore.Data241[15:0] */
0xFE, 0xFC,    /* AC.AEQCore.Data242[15:0] */
0xFE, 0xFC,    /* AC.AEQCore.Data243[15:0] */
0x07, 0xE3,    /* AC.AEQCore.Data244[15:0] */
0x07, 0xE3,    /* AC.AEQCore.Data245[15:0] */
0x13, 0x15,    /* AC.AEQCore.Data246[15:0] */
0x13, 0x15,    /* AC.AEQCore.Data247[15:0] */
0x12, 0xF1,    /* AC.AEQCore.Data248[15:0] */
0x12, 0xF1,    /* AC.AEQCore.Data249[15:0] */
0xFF, 0xC2,    /* AC.AEQCore.Data250[15:0] */
0xFF, 0xC2,    /* AC.AEQCore.Data251[15:0] */
0xE4, 0xA2,    /* AC.AEQCore.Data252[15:0] */
0xE4, 0xA2,    /* AC.AEQCore.Data253[15:0] */
0xDA, 0xBA,    /* AC.AEQCore.Data254[15:0] */
0xDA, 0xBA,    /* AC.AEQCore.Data255[15:0] */
0x80, 0x01,    /* AC.AEQCore.Data256[15:0] */
0x80, 0x01,    /* AC.AEQCore.Data257[15:0] */
0x30, 0x12,    /* AC.AEQCore.Data258[15:0] */
0x30, 0x12,    /* AC.AEQCore.Data259[15:0] */
0x3A, 0x02,    /* AC.AEQCore.Data260[15:0] */
0x3A, 0x02,    /* AC.AEQCore.Data261[15:0] */
0x22, 0x14,    /* AC.AEQCore.Data262[15:0] */
0x22, 0x14,    /* AC.AEQCore.Data263[15:0] */
0x02, 0x66,    /* AC.AEQCore.Data264[15:0] */
0x02, 0x66,    /* AC.AEQCore.Data265[15:0] */
0xF7, 0xA2,    /* AC.AEQCore.Data266[15:0] */
0xF7, 0xA2,    /* AC.AEQCore.Data267[15:0] */
0xFE, 0x66,    /* AC.AEQCore.Data268[15:0] */
0xFE, 0x66,    /* AC.AEQCore.Data269[15:0] */
0x02, 0x36,    /* AC.AEQCore.Data270[15:0] */
0x02, 0x36,    /* AC.AEQCore.Data271[15:0] */
0xFD, 0x40,    /* AC.AEQCore.Data272[15:0] */
0xFD, 0x40,    /* AC.AEQCore.Data273[15:0] */
0xF9, 0xA9,    /* AC.AEQCore.Data274[15:0] */
0xF9, 0xA9,    /* AC.AEQCore.Data275[15:0] */
0xFC, 0xA6,    /* AC.AEQCore.Data276[15:0] */
0xFC, 0xA6,    /* AC.AEQCore.Data277[15:0] */
0x00, 0x5E,    /* AC.AEQCore.Data278[15:0] */
0x00, 0x5E,    /* AC.AEQCore.Data279[15:0] */
0x00, 0x27,    /* AC.AEQCore.Data280[15:0] */
0x00, 0x27,    /* AC.AEQCore.Data281[15:0] */
0xFE, 0xF4,    /* AC.AEQCore.Data282[15:0] */
0xFE, 0xF4,    /* AC.AEQCore.Data283[15:0] */
0x00, 0xD3,    /* AC.AEQCore.Data284[15:0] */
0x00, 0xD3,    /* AC.AEQCore.Data285[15:0] */
0x05, 0x47,    /* AC.AEQCore.Data286[15:0] */
0x05, 0x47,    /* AC.AEQCore.Data287[15:0] */
0x09, 0x53,    /* AC.AEQCore.Data288[15:0] */
0x09, 0x53,    /* AC.AEQCore.Data289[15:0] */
0x0A, 0xE5,    /* AC.AEQCore.Data290[15:0] */
0x0A, 0xE5,    /* AC.AEQCore.Data291[15:0] */
0x09, 0x9C,    /* AC.AEQCore.Data292[15:0] */
0x09, 0x9C,    /* AC.AEQCore.Data293[15:0] */
0x06, 0xA5,    /* AC.AEQCore.Data294[15:0] */
0x06, 0xA5,    /* AC.AEQCore.Data295[15:0] */
0x04, 0x33,    /* AC.AEQCore.Data296[15:0] */
0x04, 0x33,    /* AC.AEQCore.Data297[15:0] */
0x03, 0x8E,    /* AC.AEQCore.Data298[15:0] */
0x03, 0x8E,    /* AC.AEQCore.Data299[15:0] */
0x03, 0x95,    /* AC.AEQCore.Data300[15:0] */
0x03, 0x95,    /* AC.AEQCore.Data301[15:0] */
0x02, 0x2D,    /* AC.AEQCore.Data302[15:0] */
0x02, 0x2D,    /* AC.AEQCore.Data303[15:0] */
0xFF, 0x47,    /* AC.AEQCore.Data304[15:0] */
0xFF, 0x47,    /* AC.AEQCore.Data305[15:0] */
0xFD, 0x81,    /* AC.AEQCore.Data306[15:0] */
0xFD, 0x81,    /* AC.AEQCore.Data307[15:0] */
0xFE, 0xEF,    /* AC.AEQCore.Data308[15:0] */
0xFE, 0xEF,    /* AC.AEQCore.Data309[15:0] */
0x01, 0xE6,    /* AC.AEQCore.Data310[15:0] */
0x01, 0xE6,    /* AC.AEQCore.Data311[15:0] */
0x02, 0x93,    /* AC.AEQCore.Data312[15:0] */
0x02, 0x93,    /* AC.AEQCore.Data313[15:0] */
0xFF, 0xFF,    /* AC.AEQCore.Data314[15:0] */
0xFF, 0xFF,    /* AC.AEQCore.Data315[15:0] */
0xFD, 0xA7,    /* AC.AEQCore.Data316[15:0] */
0xFD, 0xA7,    /* AC.AEQCore.Data317[15:0] */
0xFE, 0xC1,    /* AC.AEQCore.Data318[15:0] */
0xFE, 0xC1,    /* AC.AEQCore.Data319[15:0] */
0x01, 0xC2,    /* AC.AEQCore.Data320[15:0] */
0x01, 0xC2,    /* AC.AEQCore.Data321[15:0] */
0x02, 0xB4,    /* AC.AEQCore.Data322[15:0] */
0x02, 0xB4,    /* AC.AEQCore.Data323[15:0] */
0x00, 0xEF,    /* AC.AEQCore.Data324[15:0] */
0x00, 0xEF,    /* AC.AEQCore.Data325[15:0] */
0xFF, 0xCA,    /* AC.AEQCore.Data326[15:0] */
0xFF, 0xCA,    /* AC.AEQCore.Data327[15:0] */
0x01, 0x79,    /* AC.AEQCore.Data328[15:0] */
0x01, 0x79,    /* AC.AEQCore.Data329[15:0] */
0x03, 0xE9,    /* AC.AEQCore.Data330[15:0] */
0x03, 0xE9,    /* AC.AEQCore.Data331[15:0] */
0x03, 0xE4,    /* AC.AEQCore.Data332[15:0] */
0x03, 0xE4,    /* AC.AEQCore.Data333[15:0] */
0x01, 0x9F,    /* AC.AEQCore.Data334[15:0] */
0x01, 0x9F,    /* AC.AEQCore.Data335[15:0] */
0xFF, 0xFC,    /* AC.AEQCore.Data336[15:0] */
0xFF, 0xFC,    /* AC.AEQCore.Data337[15:0] */
0x00, 0x2F,    /* AC.AEQCore.Data338[15:0] */
0x00, 0x2F,    /* AC.AEQCore.Data339[15:0] */
0x00, 0x65,    /* AC.AEQCore.Data340[15:0] */
0x00, 0x65,    /* AC.AEQCore.Data341[15:0] */
0xFF, 0x11,    /* AC.AEQCore.Data342[15:0] */
0xFF, 0x11,    /* AC.AEQCore.Data343[15:0] */
0xFD, 0x71,    /* AC.AEQCore.Data344[15:0] */
0xFD, 0x71,    /* AC.AEQCore.Data345[15:0] */
0xFD, 0x87,    /* AC.AEQCore.Data346[15:0] */
0xFD, 0x87,    /* AC.AEQCore.Data347[15:0] */
0xFF, 0x09,    /* AC.AEQCore.Data348[15:0] */
0xFF, 0x09,    /* AC.AEQCore.Data349[15:0] */
0xFF, 0xFA,    /* AC.AEQCore.Data350[15:0] */
0xFF, 0xFA,    /* AC.AEQCore.Data351[15:0] */
0xFF, 0xB6,    /* AC.AEQCore.Data352[15:0] */
0xFF, 0xB6,    /* AC.AEQCore.Data353[15:0] */
0xFF, 0xAC,    /* AC.AEQCore.Data354[15:0] */
0xFF, 0xAC,    /* AC.AEQCore.Data355[15:0] */
0x00, 0xF6,    /* AC.AEQCore.Data356[15:0] */
0x00, 0xF6,    /* AC.AEQCore.Data357[15:0] */
0x02, 0xB6,    /* AC.AEQCore.Data358[15:0] */
0x02, 0xB6,    /* AC.AEQCore.Data359[15:0] */
0x03, 0x70,    /* AC.AEQCore.Data360[15:0] */
0x03, 0x70,    /* AC.AEQCore.Data361[15:0] */
0x02, 0xE1,    /* AC.AEQCore.Data362[15:0] */
0x02, 0xE1,    /* AC.AEQCore.Data363[15:0] */
0x01, 0xCE,    /* AC.AEQCore.Data364[15:0] */
0x01, 0xCE,    /* AC.AEQCore.Data365[15:0] */
0x00, 0xA4,    /* AC.AEQCore.Data366[15:0] */
0x00, 0xA4,    /* AC.AEQCore.Data367[15:0] */
0xFF, 0x47,    /* AC.AEQCore.Data368[15:0] */
0xFF, 0x47,    /* AC.AEQCore.Data369[15:0] */
0xFE, 0x07,    /* AC.AEQCore.Data370[15:0] */
0xFE, 0x07,    /* AC.AEQCore.Data371[15:0] */
0xFD, 0xA8,    /* AC.AEQCore.Data372[15:0] */
0xFD, 0xA8,    /* AC.AEQCore.Data373[15:0] */
0xFE, 0x5B,    /* AC.AEQCore.Data374[15:0] */
0xFE, 0x5B,    /* AC.AEQCore.Data375[15:0] */
0xFF, 0x61,    /* AC.AEQCore.Data376[15:0] */
0xFF, 0x61,    /* AC.AEQCore.Data377[15:0] */
0xFF, 0xF6,    /* AC.AEQCore.Data378[15:0] */
0xFF, 0xF6,    /* AC.AEQCore.Data379[15:0] */
0x00, 0x19,    /* AC.AEQCore.Data380[15:0] */
0x00, 0x19,    /* AC.AEQCore.Data381[15:0] */
0x00, 0x27,    /* AC.AEQCore.Data382[15:0] */
0x00, 0x27,    /* AC.AEQCore.Data383[15:0] */
0x00, 0x39,    /* AC.AEQCore.Data384[15:0] */
0x00, 0x39,    /* AC.AEQCore.Data385[15:0] */
0x00, 0x4B,    /* AC.AEQCore.Data386[15:0] */
0x00, 0x4B,    /* AC.AEQCore.Data387[15:0] */
0x00, 0x94,    /* AC.AEQCore.Data388[15:0] */
0x00, 0x94,    /* AC.AEQCore.Data389[15:0] */
0x01, 0x30,    /* AC.AEQCore.Data390[15:0] */
0x01, 0x30,    /* AC.AEQCore.Data391[15:0] */
0x01, 0xAE,    /* AC.AEQCore.Data392[15:0] */
0x01, 0xAE,    /* AC.AEQCore.Data393[15:0] */
0x01, 0x80,    /* AC.AEQCore.Data394[15:0] */
0x01, 0x80,    /* AC.AEQCore.Data395[15:0] */
0x00, 0xC6,    /* AC.AEQCore.Data396[15:0] */
0x00, 0xC6,    /* AC.AEQCore.Data397[15:0] */
0x00, 0x23,    /* AC.AEQCore.Data398[15:0] */
0x00, 0x23,    /* AC.AEQCore.Data399[15:0] */
0xFF, 0xC9,    /* AC.AEQCore.Data400[15:0] */
0xFF, 0xC9,    /* AC.AEQCore.Data401[15:0] */
0xFF, 0x4A,    /* AC.AEQCore.Data402[15:0] */
0xFF, 0x4A,    /* AC.AEQCore.Data403[15:0] */
0xFE, 0x77,    /* AC.AEQCore.Data404[15:0] */
0xFE, 0x77,    /* AC.AEQCore.Data405[15:0] */
0xFD, 0xE1,    /* AC.AEQCore.Data406[15:0] */
0xFD, 0xE1,    /* AC.AEQCore.Data407[15:0] */
0xFE, 0x10,    /* AC.AEQCore.Data408[15:0] */
0xFE, 0x10,    /* AC.AEQCore.Data409[15:0] */
0xFE, 0xAE,    /* AC.AEQCore.Data410[15:0] */
0xFE, 0xAE,    /* AC.AEQCore.Data411[15:0] */
0xFF, 0x15,    /* AC.AEQCore.Data412[15:0] */
0xFF, 0x15,    /* AC.AEQCore.Data413[15:0] */
0xFF, 0x51,    /* AC.AEQCore.Data414[15:0] */
0xFF, 0x51,    /* AC.AEQCore.Data415[15:0] */
0xFF, 0xF7,    /* AC.AEQCore.Data416[15:0] */
0xFF, 0xF7,    /* AC.AEQCore.Data417[15:0] */
0x01, 0x01,    /* AC.AEQCore.Data418[15:0] */
0x01, 0x01,    /* AC.AEQCore.Data419[15:0] */
0x01, 0x8F,    /* AC.AEQCore.Data420[15:0] */
0x01, 0x8F,    /* AC.AEQCore.Data421[15:0] */
0x01, 0x0F,    /* AC.AEQCore.Data422[15:0] */
0x01, 0x0F,    /* AC.AEQCore.Data423[15:0] */
0x00, 0x14,    /* AC.AEQCore.Data424[15:0] */
0x00, 0x14,    /* AC.AEQCore.Data425[15:0] */
0xFF, 0x9A,    /* AC.AEQCore.Data426[15:0] */
0xFF, 0x9A,    /* AC.AEQCore.Data427[15:0] */
0xFF, 0xCB,    /* AC.AEQCore.Data428[15:0] */
0xFF, 0xCB,    /* AC.AEQCore.Data429[15:0] */
0xFF, 0xFC,    /* AC.AEQCore.Data430[15:0] */
0xFF, 0xFC,    /* AC.AEQCore.Data431[15:0] */
0xFF, 0xC0,    /* AC.AEQCore.Data432[15:0] */
0xFF, 0xC0,    /* AC.AEQCore.Data433[15:0] */
0xFF, 0x58,    /* AC.AEQCore.Data434[15:0] */
0xFF, 0x58,    /* AC.AEQCore.Data435[15:0] */
0xFF, 0x25,    /* AC.AEQCore.Data436[15:0] */
0xFF, 0x25,    /* AC.AEQCore.Data437[15:0] */
0xFF, 0x1E,    /* AC.AEQCore.Data438[15:0] */
0xFF, 0x1E,    /* AC.AEQCore.Data439[15:0] */
0xFF, 0x17,    /* AC.AEQCore.Data440[15:0] */
0xFF, 0x17,    /* AC.AEQCore.Data441[15:0] */
0xFF, 0x2F,    /* AC.AEQCore.Data442[15:0] */
0xFF, 0x2F,    /* AC.AEQCore.Data443[15:0] */
0xFF, 0x8F,    /* AC.AEQCore.Data444[15:0] */
0xFF, 0x8F,    /* AC.AEQCore.Data445[15:0] */
0x00, 0x0C,    /* AC.AEQCore.Data446[15:0] */
0x00, 0x0C,    /* AC.AEQCore.Data447[15:0] */
0x00, 0x4E,    /* AC.AEQCore.Data448[15:0] */
0x00, 0x4E,    /* AC.AEQCore.Data449[15:0] */
0x00, 0x49,    /* AC.AEQCore.Data450[15:0] */
0x00, 0x49,    /* AC.AEQCore.Data451[15:0] */
0x00, 0x3E,    /* AC.AEQCore.Data452[15:0] */
0x00, 0x3E,    /* AC.AEQCore.Data453[15:0] */
0x00, 0x54,    /* AC.AEQCore.Data454[15:0] */
0x00, 0x54,    /* AC.AEQCore.Data455[15:0] */
0x00, 0x6B,    /* AC.AEQCore.Data456[15:0] */
0x00, 0x6B,    /* AC.AEQCore.Data457[15:0] */
0x00, 0x63,    /* AC.AEQCore.Data458[15:0] */
0x00, 0x63,    /* AC.AEQCore.Data459[15:0] */
0x00, 0x52,    /* AC.AEQCore.Data460[15:0] */
0x00, 0x52,    /* AC.AEQCore.Data461[15:0] */
0x00, 0x51,    /* AC.AEQCore.Data462[15:0] */
0x00, 0x51,    /* AC.AEQCore.Data463[15:0] */
0x00, 0x4D,    /* AC.AEQCore.Data464[15:0] */
0x00, 0x4D,    /* AC.AEQCore.Data465[15:0] */
0x00, 0x35,    /* AC.AEQCore.Data466[15:0] */
0x00, 0x35,    /* AC.AEQCore.Data467[15:0] */
0x00, 0x19,    /* AC.AEQCore.Data468[15:0] */
0x00, 0x19,    /* AC.AEQCore.Data469[15:0] */
0x00, 0x0E,    /* AC.AEQCore.Data470[15:0] */
0x00, 0x0E,    /* AC.AEQCore.Data471[15:0] */
0x00, 0x04,    /* AC.AEQCore.Data472[15:0] */
0x00, 0x04,    /* AC.AEQCore.Data473[15:0] */
0xFF, 0xEA,    /* AC.AEQCore.Data474[15:0] */
0xFF, 0xEA,    /* AC.AEQCore.Data475[15:0] */
0xFF, 0xD8,    /* AC.AEQCore.Data476[15:0] */
0xFF, 0xD8,    /* AC.AEQCore.Data477[15:0] */
0xFF, 0xF5,    /* AC.AEQCore.Data478[15:0] */
0xFF, 0xF5,    /* AC.AEQCore.Data479[15:0] */
0x00, 0x31,    /* AC.AEQCore.Data480[15:0] */
0x00, 0x31,    /* AC.AEQCore.Data481[15:0] */
0x00, 0x5C,    /* AC.AEQCore.Data482[15:0] */
0x00, 0x5C,    /* AC.AEQCore.Data483[15:0] */
0x00, 0x71,    /* AC.AEQCore.Data484[15:0] */
0x00, 0x71,    /* AC.AEQCore.Data485[15:0] */
0x00, 0x9C,    /* AC.AEQCore.Data486[15:0] */
0x00, 0x9C,    /* AC.AEQCore.Data487[15:0] */
0x00, 0xE2,    /* AC.AEQCore.Data488[15:0] */
0x00, 0xE2,    /* AC.AEQCore.Data489[15:0] */
0x01, 0x04,    /* AC.AEQCore.Data490[15:0] */
0x01, 0x04,    /* AC.AEQCore.Data491[15:0] */
0x00, 0xD6,    /* AC.AEQCore.Data492[15:0] */
0x00, 0xD6,    /* AC.AEQCore.Data493[15:0] */
0x00, 0x7D,    /* AC.AEQCore.Data494[15:0] */
0x00, 0x7D,    /* AC.AEQCore.Data495[15:0] */
0x00, 0x3A,    /* AC.AEQCore.Data496[15:0] */
0x00, 0x3A,    /* AC.AEQCore.Data497[15:0] */
0x00, 0x14,    /* AC.AEQCore.Data498[15:0] */
0x00, 0x14,    /* AC.AEQCore.Data499[15:0] */
0xFF, 0xE3,    /* AC.AEQCore.Data500[15:0] */
0xFF, 0xE3,    /* AC.AEQCore.Data501[15:0] */
0xFF, 0xA1,    /* AC.AEQCore.Data502[15:0] */
0xFF, 0xA1,    /* AC.AEQCore.Data503[15:0] */
0xFF, 0x7C,    /* AC.AEQCore.Data504[15:0] */
0xFF, 0x7C,    /* AC.AEQCore.Data505[15:0] */
0xFF, 0x8E,    /* AC.AEQCore.Data506[15:0] */
0xFF, 0x8E,    /* AC.AEQCore.Data507[15:0] */
0xFF, 0xBE,    /* AC.AEQCore.Data508[15:0] */
0xFF, 0xBE,    /* AC.AEQCore.Data509[15:0] */
0xFF, 0xE7,    /* AC.AEQCore.Data510[15:0] */
0xFF, 0xE7,    /* AC.AEQCore.Data511[15:0] */
0x20, 0x25,    /* AC.AEQCore.Data512[15:0] */
0x20, 0x25,    /* AC.AEQCore.Data513[15:0] */
0x40, 0x00,    /* AC.LPostLev[15:0]        */
0x40, 0x00     /* AC.RPostLev[15:0]        */
};

static UC bAcOff[] = {
0x40, 0x00,    /* AC.ThruSel[15:0] */
0x00, 0x00     /* AC.ACSel[15:0]   */
};

/* Smooth volume coefficients */
static UC bSvFMMix[] = {
/*
	detail
	 FMLMix[15:0]=FMRMix[15:0]=-30dB
*/
0x02, 0x00,    /* SV.FMLMix[15:0] */
0x02, 0x00     /* SV.FMRMix[15:0] */
};

static UC bSvMuteOn[] = {
0x00, 0x00     /* SV.NMute[15:0] */
};

static UC bSvMuteOff[] = {
0x40, 0x00     /* SV.NMute[15:0] */
};


static UC b10bPEQOff[] = {
0x40, 0x00,    /* SV.ThruSel[15:0]   */
0x00, 0x00     /* SV.10bPEQSel[15:0] */
};

static UC bLnDEQ0High[] = {
/*
	detail
	 EQ0 : LSF f=350Hz,  gain=+20dB, q=0.707
	 EQ1 : HSF f=2.4kHz, gain=+17dB, q=0.707
	 Vmax=0dB, Vmin=-40dB

	usage
	 UserLoudnessSetting(bLnDEQ0High);
*/
0x41, 0x6F,    /* SV.EQ0.a0[15:0]  */
0x81, 0x5F,    /* SV.EQ0.a1[15:0]  */
0x3D, 0x54,    /* SV.EQ0.a2[15:0]  */
0x7E, 0xB0,    /* SV.EQ0.b1[15:0]  */
0xC1, 0x4C,    /* SV.EQ0.b2[15:0]  */
0x4F, 0xC6,    /* SV.EQ1.a0[15:0]  */
0x83, 0x78,    /* SV.EQ1.a1[15:0]  */
0x33, 0x2A,    /* SV.EQ1.a2[15:0]  */
0x0E, 0xD7,    /* SV.EQ1.b1[15:0]  */
0xFA, 0xC1,    /* SV.EQ1.b2[15:0]  */
0x26, 0x88,    /* SV.LnRatio[15:0] */
0x17, 0x39     /* SV.LnShift[15:0] */
};

static UC bLnOff[] = {
0x00, 0x00,    /* SV.LnSel[15:0]     */
0x40, 0x00     /* SV.LnThruSel[15:0] */
};

/* Crossover filter coefficients */
static UC bCf280Hz[] = {
/*
	detail
	 crosover frequency : 280Hz
	
	usage
	 UserCrossoverSetting(2, bCF280Hz);
*/
0x3F, 0x17,    /* CF.HPF.a0[27:12] */
0x0F, 0xD3,    /* CF.HPF.a0[11:0]  */
0x81, 0xD0,    /* CF.HPF.a1[27:12] */
0x00, 0x5B,    /* CF.HPF.a1[11:0]  */
0x3F, 0x17,    /* CF.HPF.a2[27:12] */
0x0F, 0xD3,    /* CF.HPF.a2[11:0]  */
0x7E, 0x25,    /* CF.HPF.b1[27:12] */
0x02, 0x06,    /* CF.HPF.b1[11:0]  */
0xC1, 0xC5,    /* CF.HPF.b2[27:12] */
0x02, 0xBB,    /* CF.HPF.b2[11:0]  */
0x3D, 0xE2,    /* CF.HPF.c0[27:12] */
0x02, 0xCD,    /* CF.HPF.c0[11:0]  */
0x84, 0x3B,    /* CF.HPF.c1[27:12] */
0x0A, 0x65,    /* CF.HPF.c1[11:0]  */
0x3D, 0xE2,    /* CF.HPF.c2[27:12] */
0x02, 0xCD,    /* CF.HPF.c2[11:0]  */
0x7B, 0xB9,    /* CF.HPF.d1[27:12] */
0x0B, 0x50,    /* CF.HPF.d1[11:0]  */
0xC4, 0x31,    /* CF.HPF.d2[27:12] */
0x00, 0x1A,    /* CF.HPF.d2[11:0]  */
0x00, 0x05,    /* CF.LPF.a0[27:12] */
0x06, 0xD0,    /* CF.LPF.a0[11:0]  */
0x00, 0x0A,    /* CF.LPF.a1[27:12] */
0x0D, 0x9F,    /* CF.LPF.a1[11:0]  */
0x00, 0x05,    /* CF.LPF.a2[27:12] */
0x06, 0xD0,    /* CF.LPF.a2[11:0]  */
0x7E, 0x25,    /* CF.LPF.b1[27:12] */
0x02, 0x06,    /* CF.LPF.b1[11:0]  */
0xC1, 0xC5,    /* CF.LPF.b2[27:12] */
0x02, 0xBB,    /* CF.LPF.b2[11:0]  */
0x00, 0x05,    /* CF.LPF.c0[27:12] */
0x05, 0x25,    /* CF.LPF.c0[11:0]  */
0x00, 0x0A,    /* CF.LPF.c1[27:12] */
0x0A, 0x4B,    /* CF.LPF.c1[11:0]  */
0x00, 0x05,    /* CF.LPF.c2[27:12] */
0x05, 0x25,    /* CF.LPF.c2[11:0]  */
0x7B, 0xB9,    /* CF.LPF.d1[27:12] */
0x0B, 0x50,    /* CF.LPF.d1[11:0]  */
0xC4, 0x31,    /* CF.LPF.d2[27:12] */
0x00, 0x1A     /* CF.LPF.d2[11:0]  */
};

static UC bCf21ch[] = {
/*
	detail
	 digital network : 2.1ch
	 
	 MonoMix[15:0]=0dB
	 HPFSel[15:0]=0dB,  HThruSel[15:0]=-Åá
	 LPFSel[15:0]=-6dB, LThruSel[15:0]=-Åá
*/
0x40, 0x00,    /* CF.MonoMix[15:0]  */
0x40, 0x00,    /* CF.HPFSel[15:0]   */
0x00, 0x00,    /* CF.HThruSel[15:0] */
0x20, 0x00,    /* CF.LPFSel[15:0]   */
0x00, 0x00     /* CF.LThruSel[15:0] */
};


static UC bBalanceCoef[][4] = {
{0x40, 0x00, 0x00, 0x00},    
{0x40, 0x00, 0x01, 0x9C},    /* LBal=0dB,   RBal=-32dB */
{0x40, 0x00, 0x01, 0xCE},    /* LBal=0dB,   RBal=-31dB */
{0x40, 0x00, 0x02, 0x06},    /* LBal=0dB,   RBal=-30dB */
{0x40, 0x00, 0x02, 0x45},    /* LBal=0dB,   RBal=-29dB */
{0x40, 0x00, 0x02, 0x8C},    /* LBal=0dB,   RBal=-28dB */
{0x40, 0x00, 0x02, 0xDC},    /* LBal=0dB,   RBal=-27dB */
{0x40, 0x00, 0x03, 0x35},    /* LBal=0dB,   RBal=-26dB */
{0x40, 0x00, 0x03, 0x99},    /* LBal=0dB,   RBal=-25dB */
{0x40, 0x00, 0x04, 0x0A},    /* LBal=0dB,   RBal=-24dB */
{0x40, 0x00, 0x04, 0x88},    /* LBal=0dB,   RBal=-23dB */
{0x40, 0x00, 0x05, 0x15},    /* LBal=0dB,   RBal=-22dB */
{0x40, 0x00, 0x05, 0xB4},    /* LBal=0dB,   RBal=-21dB */
{0x40, 0x00, 0x06, 0x66},    /* LBal=0dB,   RBal=-20dB */
{0x40, 0x00, 0x07, 0x2E},    /* LBal=0dB,   RBal=-19dB */
{0x40, 0x00, 0x08, 0x0F},    /* LBal=0dB,   RBal=-18dB */
{0x40, 0x00, 0x09, 0x0A},    /* LBal=0dB,   RBal=-17dB */
{0x40, 0x00, 0x0A, 0x25},    /* LBal=0dB,   RBal=-16dB */
{0x40, 0x00, 0x0B, 0x62},    /* LBal=0dB,   RBal=-15dB */
{0x40, 0x00, 0x0C, 0xC5},    /* LBal=0dB,   RBal=-14dB */
{0x40, 0x00, 0x0E, 0x54},    /* LBal=0dB,   RBal=-13dB */
{0x40, 0x00, 0x10, 0x13},    /* LBal=0dB,   RBal=-12dB */
{0x40, 0x00, 0x12, 0x0A},    /* LBal=0dB,   RBal=-11dB */
{0x40, 0x00, 0x14, 0x3D},    /* LBal=0dB,   RBal=-10dB */
{0x40, 0x00, 0x16, 0xB5},    /* LBal=0dB,   RBal=-9dB  */
{0x40, 0x00, 0x19, 0x7B},    /* LBal=0dB,   RBal=-8dB  */
{0x40, 0x00, 0x1C, 0x96},    /* LBal=0dB,   RBal=-7dB  */
{0x40, 0x00, 0x20, 0x13},    /* LBal=0dB,   RBal=-6dB  */
{0x40, 0x00, 0x23, 0xFD},    /* LBal=0dB,   RBal=-5dB  */
{0x40, 0x00, 0x28, 0x62},    /* LBal=0dB,   RBal=-4dB  */
{0x40, 0x00, 0x2D, 0x4F},    /* LBal=0dB,   RBal=-3dB  */
{0x40, 0x00, 0x32, 0xD6},    /* LBal=0dB,   RBal=-2dB  */
{0x40, 0x00, 0x39, 0x0A},    /* LBal=0dB,   RBal=-1dB  */
{0x40, 0x00, 0x40, 0x00},    /* LBal=0dB,   RBal=0dB   */
{0x39, 0x0A, 0x40, 0x00},    /* LBal=-1dB,  RBal=0dB   */
{0x32, 0xD6, 0x40, 0x00},    /* LBal=-2dB,  RBal=0dB   */
{0x2D, 0x4F, 0x40, 0x00},    /* LBal=-3dB,  RBal=0dB   */
{0x28, 0x62, 0x40, 0x00},    /* LBal=-4dB,  RBal=0dB   */
{0x23, 0xFD, 0x40, 0x00},    /* LBal=-5dB,  RBal=0dB   */
{0x20, 0x13, 0x40, 0x00},    /* LBal=-6dB,  RBal=0dB   */
{0x1C, 0x96, 0x40, 0x00},    /* LBal=-7dB,  RBal=0dB   */
{0x19, 0x7B, 0x40, 0x00},    /* LBal=-8dB,  RBal=0dB   */
{0x16, 0xB5, 0x40, 0x00},    /* LBal=-9dB,  RBal=0dB   */
{0x14, 0x3D, 0x40, 0x00},    /* LBal=-10dB, RBal=0dB   */
{0x12, 0x0A, 0x40, 0x00},    /* LBal=-11dB, RBal=0dB   */
{0x10, 0x13, 0x40, 0x00},    /* LBal=-12dB, RBal=0dB   */
{0x0E, 0x54, 0x40, 0x00},    /* LBal=-13dB, RBal=0dB   */
{0x0C, 0xC5, 0x40, 0x00},    /* LBal=-14dB, RBal=0dB   */
{0x0B, 0x62, 0x40, 0x00},    /* LBal=-15dB, RBal=0dB   */
{0x0A, 0x25, 0x40, 0x00},    /* LBal=-16dB, RBal=0dB   */
{0x09, 0x0A, 0x40, 0x00},    /* LBal=-17dB, RBal=0dB   */
{0x08, 0x0F, 0x40, 0x00},    /* LBal=-18dB, RBal=0dB   */
{0x07, 0x2E, 0x40, 0x00},    /* LBal=-19dB, RBal=0dB   */
{0x06, 0x66, 0x40, 0x00},    /* LBal=-20dB, RBal=0dB   */
{0x05, 0xB4, 0x40, 0x00},    /* LBal=-21dB, RBal=0dB   */
{0x05, 0x15, 0x40, 0x00},    /* LBal=-22dB, RBal=0dB   */
{0x04, 0x88, 0x40, 0x00},    /* LBal=-23dB, RBal=0dB   */
{0x04, 0x0A, 0x40, 0x00},    /* LBal=-24dB, RBal=0dB   */
{0x03, 0x99, 0x40, 0x00},    /* LBal=-25dB, RBal=0dB   */
{0x03, 0x35, 0x40, 0x00},    /* LBal=-26dB, RBal=0dB   */
{0x02, 0xDC, 0x40, 0x00},    /* LBal=-27dB, RBal=0dB   */
{0x02, 0x8C, 0x40, 0x00},    /* LBal=-28dB, RBal=0dB   */
{0x02, 0x45, 0x40, 0x00},    /* LBal=-29dB, RBal=0dB   */
{0x02, 0x06, 0x40, 0x00},    /* LBal=-30dB, RBal=0dB   */
{0x01, 0xCE, 0x40, 0x00},    /* LBal=-31dB, RBal=0dB   */
{0x01, 0x9C, 0x40, 0x00},    /* LBal=-32dB, RBal=0dB   */
{0x00, 0x00, 0x40, 0x00}     
};

/* Limiter coefficients */
static UC bPowerLimit[] = {
/*
	detail
	 - HGC : gain shift=26.3dB, curve shift=26.3dB, ratio=0.5
	         limit=-24.6dB, decay=5.27s, preattack=0ms, attack=0ms

	 - LGC : gain shift=26.3dB, curve shift=26.3dB, ratio=0.5
	         limit=-24.6dB, decay=5.27s, attack=15ms

	usage
	 SetPowerLimit(bPowerLimit);
*/
0x06, 0x33,    /* LMT.HGC.GainShift[15:0]  */
0x06, 0x33,    /* LMT.HGC.CurveShift[15:0] */
0x20, 0x00,    /* LMT.HGC.Ratio[15:0]      */
0x07, 0x8A,    /* LMT.HGC.Limit[15:0]      */
0x00, 0x03,    /* LMT.HGC.Decay[15:0]      */
0xFF, 0xFF,    /* LMT.HGC.PreAttack[15:0]  */
0x40, 0x00,    /* LMT.HATK.a0[27:12]       */
0x00, 0x00,    /* LMT.HATK.a0[11:0]        */
0x00, 0x00,    /* LMT.HATK.a1[27:12]       */
0x00, 0x00,    /* LMT.HATK.a1[11:0]        */
0x00, 0x00,    /* LMT.HATK.b1[27:12]       */
0x00, 0x00,    /* LMT.HATK.b1[11:0]        */
0x06, 0x33,    /* LMT.LGC.GainShift[15:0]  */
0x06, 0x33,    /* LMT.LGC.CurveShift[15:0] */
0x20, 0x00,    /* LMT.LGC.Ratio[15:0]      */
0x07, 0x8A,    /* LMT.LGC.Limit[15:0]      */
0x00, 0x03,    /* LMT.LGC.Decay[15:0]      */
0x40, 0x00,    /* LMT.LATK.a0[27:12]       */
0x00, 0x00,    /* LMT.LATK.a0[11:0]        */
0x00, 0x00,    /* LMT.LATK.a1[27:12]       */
0x00, 0x00,    /* LMT.LATK.a1[11:0]        */
0x00, 0x00,    /* LMT.LATK.b1[27:12]       */
0x00, 0x00     /* LMT.LATK.b1[11:0]        */
};

static UC bLmtOff[] = {
0x40, 0x00,    /* LMT.HGCThruSel[15:0] */
0x00, 0x00,    /* LMT.HGCSel[15:0]     */
0x40, 0x00,    /* LMT.LGCThruSel[15:0] */
0x00, 0x00     /* LMT.LGCSel[15:0]     */
};

static UC bLmtLoMixOff[] = {
0x00, 0x00     /* LMT.LoMix[15:0] */
};

static UC bLmtSMix[] = {
0x40, 0x00,    /* LMT.SMix[15:0] */
0x00, 0x00     /* LMT.XMix[15:0] */
};

static UC bSoftcClipper[] = {
/*
	detail
	 PreLev=8.8dB, PostLev=-8.8dB, CompLev=0.333

	usage
	 SetSoftClip(bSoftcClipper);
*/
0x2C, 0x11,    /* LMT.PreLev[15:0]  */
0x17, 0x3D,    /* LMT.PostLev[15:0] */
0x2A, 0xA0     /* LMT.CompLev[15:0] */
};

static UC bLmtSCOff[] = {
0x40, 0x00,    /* LMT.SCThruSel[15:0] */
0x00, 0x00     /* LMT.SCSel[15:0]     */
};

static UC bLmt21ch[] = {
/*
	detail
	 LAmpOut[15:0]=0dB,  LAmpOut[15:0]=0dB
	 LSDO0Out[15:0]=6dB, RSDO0Out[15:0]=6dB
	 LSDO1Out[15:0]=0dB, RSDO1Out[15:0]=0dB
*/
0x20, 0x00,    /* LMT.LAmpOut[15:0]   */
0x20, 0x00,    /* LMT.RAmpOut[15:0]   */
0x40, 0x00,    /* LMT.LSDO0Out[15:0]  */
0x40, 0x00,    /* LMT.RSDO0Out[15:0]  */
0x20, 0x00,    /* LMT.LSDO1Out[15:0]  */
0x20, 0x00     /* LMT.RSDO1Out[15:0]  */
};

/* 10bands PEQ coefficients */
static UC bAEQPEQ[] = {
/*
	detail
	 effect : This effect is the same as a sample command file "AEQ On",
	          and sample for a specified speaker cabinet.

	usage
	 SetAEQ(bAEQCore, bAEQPEQ);
*/
0x20, 0x00, 0x00,    /* Band0.a0  */
0x00, 0x00, 0x00,    /* Band0.a1  */
0x00, 0x00, 0x00,    /* Band0.a2  */
0x00, 0x00, 0x00,    /* Band0.b1  */
0x00, 0x00, 0x00,    /* Band0.b2  */
0x20, 0x00, 0x00,    /* Band1.a0  */
0x00, 0x00, 0x00,    /* Band1.a1  */
0x00, 0x00, 0x00,    /* Band1.a2  */
0x00, 0x00, 0x00,    /* Band1.b1  */
0x00, 0x00, 0x00,    /* Band1.b2  */
0x20, 0x00, 0x00,    /* Band2.a0  */
0x00, 0x00, 0x00,    /* Band2.a1  */
0x00, 0x00, 0x00,    /* Band2.a2  */
0x00, 0x00, 0x00,    /* Band2.b1  */
0x00, 0x00, 0x00,    /* Band2.b2  */
0x20, 0x00, 0x00,    /* Band3.a0  */
0x00, 0x00, 0x00,    /* Band3.a1  */
0x00, 0x00, 0x00,    /* Band3.a2  */
0x00, 0x00, 0x00,    /* Band3.b1  */
0x00, 0x00, 0x00,    /* Band3.b2  */
0x20, 0x00, 0x00,    /* Band4.a0  */
0x00, 0x00, 0x00,    /* Band4.a1  */
0x00, 0x00, 0x00,    /* Band4.a2  */
0x00, 0x00, 0x00,    /* Band4.b1  */
0x00, 0x00, 0x00,    /* Band4.b2  */
0x20, 0x00, 0x00,    /* Band5.a0  */
0x00, 0x00, 0x00,    /* Band5.a1  */
0x00, 0x00, 0x00,    /* Band5.a2  */
0x00, 0x00, 0x00,    /* Band5.b1  */
0x00, 0x00, 0x00,    /* Band5.b2  */
0x1F, 0xAC, 0x82,    /* Band6.a0H */
0xC6, 0x55, 0xFA,    /* Band6.a0L */
0x1E, 0x17, 0xC0,    /* Band6.a1H */
0x39, 0xAA, 0x05,    /* Band6.a1L */
0xE2, 0x3B, 0xBC,    /* Band6.a2H */
0x6C, 0x1A, 0x83,    /* Band6.a2L */
0x5D, 0x42, 0xDB,    /* Band6.b1H */
0x6D, 0x79, 0x57,    /* Band6.b1L */
0x22, 0xBD, 0x25,    /* Band6.b2H */
0x26, 0x6C, 0x26,    /* Band6.b2L */
0x20, 0x2F, 0x5C,    /* Band7.a0H */
0xC0, 0x67, 0xE4,    /* Band7.a0L */
0x1F, 0x71, 0x78,    /* Band7.a1H */
0x3F, 0x98, 0x1B,    /* Band7.a1L */
0xE0, 0x5F, 0x2B,    /* Band7.a2H */
0x10, 0x54, 0x71,    /* Band7.a2L */
0x29, 0x12, 0x80,    /* Band7.b1H */
0x18, 0x4B, 0xD9,    /* Band7.b1L */
0x56, 0xED, 0x80,    /* Band7.b2H */
0x57, 0x5F, 0xB6,    /* Band7.b2L */
0x20, 0x17, 0xC1,    /* Band8.a0H */
0xC0, 0x40, 0x9F,    /* Band8.a0L */
0x1F, 0xAB, 0x33,    /* Band8.a1H */
0x3F, 0xBF, 0x60,    /* Band8.a1L */
0xE0, 0x3D, 0x0B,    /* Band8.a2H */
0x0E, 0xA5, 0xDB,    /* Band8.a2L */
0x43, 0x44, 0xED,    /* Band8.b1H */
0x68, 0x0D, 0xF6,    /* Band8.b1L */
0x3C, 0xBB, 0x13,    /* Band8.b2H */
0x09, 0x4C, 0x2F,    /* Band8.b2L */
0x20, 0x0B, 0xE6,    /* Band9.a0H */
0xC0, 0x1F, 0x7A,    /* Band9.a0L */
0x1F, 0xD5, 0x85,    /* Band9.a1H */
0x3F, 0xE0, 0x85,    /* Band9.a1L */
0xE0, 0x1E, 0x94,    /* Band9.a2H */
0x33, 0x0A, 0x0F,    /* Band9.a2L */
0x0C, 0x22, 0xB9,    /* Band9.b1H */
0x06, 0xDA, 0xC4,    /* Band9.b1L */
0x73, 0xDD, 0x47,    /* Band9.b2H */
0x46, 0x1B, 0x2D     /* Band9.b2L */
};


/* end of file*/
