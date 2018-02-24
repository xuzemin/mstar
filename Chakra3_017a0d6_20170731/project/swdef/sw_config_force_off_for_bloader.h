#ifndef _SW_CONFIG_FORCE_OFF_FOR_BLOADER_H_
#define _SW_CONFIG_FORCE_OFF_FOR_BLOADER_H_

#if(BLOADER)

    #if(MHEG5_ENABLE)
        #undef MHEG5_ENABLE
        #define MHEG5_ENABLE    0
    #endif

    #if( ENABLE_DTV_EPG )
        #undef ENABLE_DTV_EPG
        #define ENABLE_DTV_EPG  0
    #endif

    #if( ENABLE_PVR )
        #undef ENABLE_PVR
        #define ENABLE_PVR  0
    #endif

    #if( ENABLE_3D_PROCESS )
        #undef ENABLE_3D_PROCESS
        #define ENABLE_3D_PROCESS  0
    #endif

    #ifdef ENABLE_BACKLIGHT_ADJUST
        #undef ENABLE_BACKLIGHT_ADJUST
        #define ENABLE_BACKLIGHT_ADJUST 0
    #else
        #define ENABLE_BACKLIGHT_ADJUST 0
    #endif

    #define FILE_SYSTEM_WRITE_ENABLE 0

    #undef ENABLE_COPY_PASTE
    #define ENABLE_COPY_PASTE   0

    #define ENABLE_DELETE_SELECTED_FILES    0

    #undef ENABLE_DTV_DB_DUMP
    #define ENABLE_DTV_DB_DUMP 0

    #undef ENABLE_UART_MSG_TO_USB
    #define ENABLE_UART_MSG_TO_USB 0

    #undef ENABLE_SCRIPT_EXECUTE
    #define ENABLE_SCRIPT_EXECUTE 0

    #undef ENABLE_SUBTITLE
    #define ENABLE_SUBTITLE         DISABLE

    #undef ENABLE_TTX
    #define ENABLE_TTX              DISABLE


#endif // BLOADER

#endif // _SW_CONFIG_FORCE_OFF_FOR_BLOADER_H_

