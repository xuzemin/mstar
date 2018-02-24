#ifndef _LED_PQ_INNO_65INCH_2X16_C_
#define _LED_PQ_INNO_65INCH_2X16_C_

//#include "compen/Tbl_LD_Compensation_Gamma22.c"
//#include "edge2d/Tbl_LD_Edge2D_INNO50inch_TB12.c"
#include "gamma/Tbl_LD_Gamma_IN8925.c"

StuDrvLdPQInfo s_DrvLdPQInfo_INNO65_2X16 =
{
    HAL_LD_EDGE_TB_TYPE, // EnuLD_LED_TYPE eLEDType;

    // PANEL

    //for 1x12 LEDs
    24, 32, // U8 u8LDFWidth, u8LDFHeight; // Statistic width & height
    2, 16, // U8 u8LEDWidth, u8LEDHeight; // LED width & height
    2, 16, // U8 u8LSFWidth, u8LSFHeight; // LSF width & height
    FALSE, // BOOL bCompEn; // Compensation enable
    NULL,   //Tbl_LD_CompensationH_Gamma22, // const U8* pu8CompTable; // Compensation table  SIZE=256x2
    NULL,   //Tbl_LD_CompensationL_Gamma22, // const U8* pu8CompLowTable; // Compensation table  SIZE=256x2
    FALSE, // BOOL bEdge2DEn; // Edge2D enable
    LD_COEF_LINEAR, // EnuLD_COEF_ENCODING eEnc; // Edge2D encoding scheme
    //TO DO
    NULL,   //Tbl_LD_Edge2D_INNO50inch_TB12, // const U8* pu8Edge2DTable; // Edge2D table  SIZE=(u8LEDWidth*u8LEDHeight)*(u8LDFWidth*u8LDFHeight)

    // HW
    0x80000, 0x80000, //U32 u32LsfInitialPhase_H, u32LsfInitialPhase_V;
    0x6, //U8 u8DCMaxAlpha; // statistics : higher -> prefer max, lower -> prefer average
    0x10, //U8 u8CompensationBlend; // pixel compensation tuner : higher -> prefer compensated pixel, lower -> prefer original pixel

    // SW
    0xFF, //U8 u8GDStrength; // global dimming strength
    0xFF, //U8 u8LDStrength; // local dimming strength
    LD_TF_MSTAR, // EnuLD_TEMPORAL_FILTER_STYLE eTFStyle;
    0xF0, //U8 u8TFStrengthUp; // temporal filter strength up
    0xF8, //U8 u8TFStrengthDn; // temporal filter strength down
    0x28, //U8 u8TFLowThreshold; // temporal filter low threshold
    0x38, //U8 u8TFHightThreshold; // temporal filter high threshold
    0x00, //U8 u8TFMaxSpeed; // temporal filter max speed
    LD_SF_LINEAR, // EnuLD_SPATIAL_FILTER_STYLE eSFStyle;
    0x3C, //U8 u8SFStrength; // spatial filter strength
    0x1E, //U8 u8SFStrength2; // spatial filter strength 2
    0x4C, //U8 u8SFStrength3; // spatial filter strength 3
    0xFF, //U8 u8SFStrength4; // spatial filter strength 4
    0xFF, //U8 u8SFStrength5; // spatial filter strength 5
    0x0,  //U8 u8InGamma; // gamma at SW begin
    0x0,  //U8 u8OutGamma; // gamma at SW end
    0x00, //U8 u8BLMinValue; // min clamp value
    0x30, //U8 u8NRStrength; // de-noise strength
};

#endif
