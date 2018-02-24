#ifndef _SW_CONFIG_DEFAULT_UI_H_
#define _SW_CONFIG_DEFAULT_UI_H_


//**************************************************************************************
// UI default option...
//----------------------------------------------------------------------------

#ifndef ENABLE_ARABIC_OSD
    #define ENABLE_ARABIC_OSD   0
#endif

#ifndef ENABLE_THAI_OSD
    #define ENABLE_THAI_OSD     0
#endif

//----------------------------------------------------------------------------
//TTF font
//----------------------------------------------------------------------------

#ifndef ENABLE_TTF_FONT
    #define ENABLE_TTF_FONT DISABLE
#endif

#ifndef ENABLE_MYANMAR_OSD
    #define ENABLE_MYANMAR_OSD DISABLE
#endif

#ifndef ENABLE_KHMER_OSD
    #define ENABLE_KHMER_OSD DISABLE
#endif

#ifndef ENABLE_LAO_OSD
    #define ENABLE_LAO_OSD DISABLE
#endif

//----------------------------------------------------------------------------

#ifndef ENABLE_UYGHUR_OSD
    #define ENABLE_UYGHUR_OSD DISABLE
#endif

//----------------------------------------------------------------------------


// Use a smaller bmp.bin for reduce merge.bin size
#ifndef ENABLE_BMP_REDUCE
    #define ENABLE_BMP_REDUCE   0
#endif

#ifndef SW_LOAD_BMP_ON_DEMAND
    #define SW_LOAD_BMP_ON_DEMAND   1
#endif

#ifndef ENABLE_SUBTITLE_SWITCH_MENU
#define ENABLE_SUBTITLE_SWITCH_MENU     DISABLE
#endif

//**************************************************************************************

#endif // _SW_CONFIG_DEFAULT_UI_H_

