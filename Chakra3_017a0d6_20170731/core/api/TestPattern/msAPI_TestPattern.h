#ifndef _MSAPI_TEST_PATTERN_H
#define _MSAPI_TEST_PATTERN_H

#include "Board.h"


#if (ENABLE_TEST_PATTERN)

BOOL msAPI_TestPattern_Get_Status(void);

typedef enum
{
    E_TEST_PATTERN_ID_BMP_START = 0,

    E_TEST_PATTERN_ID_BMP_END = 0x0F,

    E_TEST_PATTERN_ID_FULL_SCREEN_BLACK = 0x10,
    E_TEST_PATTERN_ID_FULL_SCREEN_WHITE = 0x11,
    E_TEST_PATTERN_ID_GRAY_LEVEL_H_0_255 = 0x12,
    E_TEST_PATTERN_ID_GRAY_LEVEL_H_255_0 = 0x13,
    E_TEST_PATTERN_ID_GRAY_LEVEL_V_0_255 = 0x14,
    E_TEST_PATTERN_ID_GRAY_LEVEL_V_255_0 = 0x15,

    E_TEST_PATTERN_ID_R_LEVEL_V_0_255 = 0x16,
    E_TEST_PATTERN_ID_G_LEVEL_V_0_255 = 0x17,
    E_TEST_PATTERN_ID_B_LEVEL_V_0_255 = 0x18,

    E_TEST_PATTERN_ID_RECT_1        = 0x20,
    E_TEST_PATTERN_ID_RECT_2        = 0x21,
    E_TEST_PATTERN_ID_CHECKBOX      = 0x22,

    E_TEST_PATTERN_ID_RGB_1         = 0x23,
    E_TEST_PATTERN_ID_RGBW          = 0x24,

    E_TEST_PATTERN_ID_COLOR_BAR     = 0x25,

    E_TEST_PATTERN_ID_V_STRIPE      = 0x30,
    E_TEST_PATTERN_ID_H_STRIPE      = 0x31,

    E_TEST_PATTERN_ID_TEST_1        = 0x50,

    E_TEST_PATTERN_ID_MAX,

} EnuTestPatternId;

BOOL MApp_TestPattern_DrawPattern(U8 u8TPNo);

void MApp_TestPattern_Exit(void);

#endif


#endif

