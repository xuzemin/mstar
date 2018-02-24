#ifndef _MAPP_FLASH_MAP_H_
#define _MAPP_FLASH_MAP_H_

#include "Board.h"


//------ FLASH DB setting ------------------------------------------------------
#define FLASH_LAST_BANK     (FLASH_SIZE/FLASH_BLOCK_SIZE -1)

//-------------------------------------------------------------------------------------
// General setting database flash map...

#define FMAP_GEN_SETTING_BANK_COUNT     2
#define FMAP_GEN_SETTING_BANK_START     (FLASH_LAST_BANK - FMAP_GEN_SETTING_BANK_COUNT +1)

#define QUICK_DB_GENSETTING_BANK        FMAP_GEN_SETTING_BANK_START

//=========================================================================
// Channel database flash map...

#ifdef FORCE_DB_CH_FLASH_BANK_COUNT
    #define DB_BANK_COUNT   FORCE_DB_CH_FLASH_BANK_COUNT

#else
    #if (ENABLE_S2)
      #if 1//(!ENABLE_COMPRESS_DATA)
        #define DB_BANK_COUNT                   12
      #else
        #define DB_BANK_COUNT                   4
      #endif

    #elif( ENABLE_ATSC && (!ENABLE_DVBT) && (!ENABLE_S2)) //( DTV_SYSTEM_SEL == DTV_SYSTEM_ATSC )
      #if( ENABLE_ATSC_1000_CHANNEL )
        #define DB_BANK_COUNT                   4
      #else
        #define DB_BANK_COUNT                   2
      #endif


    #elif( ENABLE_DVBT && ENABLE_DVBC && DVB_T_C_DIFF_DB )
        #define DB_BANK_COUNT                   4

    #else //DVBT
      #if( ENABLE_DVBT_1000_LCN || ENABLE_NZ_FREEVIEW )
        #define DB_BANK_COUNT                   2
      #else
        #define DB_BANK_COUNT                   1
      #endif
    #endif // End of ENABLE_S2_8M_FLASH
#endif

#define SYSTEM_BANK_DATABASE0           (FMAP_CH_DB_BANK_START )
#define SYSTEM_BANK_DATABASE0_SIZE      (FLASH_BLOCK_SIZE * DB_BANK_COUNT)
#define SYSTEM_BANK_DATABASE1           (FMAP_CH_DB_BANK_START + DB_BANK_COUNT)
#define SYSTEM_BANK_DATABASE1_SIZE      (FLASH_BLOCK_SIZE * DB_BANK_COUNT)

#define FMAP_CH_DB_BANK_START           (FMAP_GEN_SETTING_BANK_START - FMAP_CH_DB_BANK_COUNT)


#define FMAP_CH_DB_BANK_COUNT               (DB_BANK_COUNT*2)

//-------------------------------------------------------------------------------------
// Factory setting database flash map...

#if(ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK)
    #define FMAP_FACTORY_SETTING_BANK_COUNT     1
#else
    #define FMAP_FACTORY_SETTING_BANK_COUNT     0
#endif
#define FMAP_FACTORY_SETTING_BANK_START     (FMAP_CH_DB_BANK_START - FMAP_FACTORY_SETTING_BANK_COUNT)

//-------------------------------------------------------------------------------------
// HDCP Key setting database flash map...
#if(ENABLE_TCON_BIN_IN_DB)
#define FMAP_TCON_BIN_BANK_COUNT    1
#else
#define FMAP_TCON_BIN_BANK_COUNT    0
#endif
#define FMAP_TCON_BIN_BANK_START     (FMAP_FACTORY_SETTING_BANK_START - FMAP_FACTORY_SETTING_BANK_COUNT)

#if (HDCP_KEY_TYPE == HDCP_KEY_IN_DB ||HDCP22_KEY_TYPE == HDCP22_KEY_IN_DB)
    #define FMAP_HDCP_KEY_BANK_COUNT    1
#else
    #define FMAP_HDCP_KEY_BANK_COUNT    0
#endif

#define FMAP_HDCP_KEY_BANK_START        (FMAP_TCON_BIN_BANK_START - FMAP_HDCP_KEY_BANK_COUNT)

#define HDCP_DB_BANK                    (FMAP_HDCP_KEY_BANK_START)
#define HDCP_DB_SIZE                    (FLASH_BLOCK_SIZE*FMAP_HDCP_KEY_BANK_COUNT)

//-------------------------------------------------------------------------------------
// Version DB setting database flash map...

#if 0//(ENABLE_S2)
    #define FMAP_VERSION_DB_BANK_COUNT  2
#else
    #define FMAP_VERSION_DB_BANK_COUNT  0
#endif

#define FMAP_VERSION_DB_BANK_START      (FMAP_HDCP_KEY_BANK_START - FMAP_VERSION_DB_BANK_COUNT)

//#define VERSION_DB_BANK0                (FMAP_VERSION_DB_BANK_START)
//#define VERSION_DB_BANK1                (VERSION_DB_BANK0-(FMAP_VERSION_DB_BANK_COUNT/2))

//-------------------------------------------------------------------------------------
// OAD setting database flash map...
#if (ENABLE_OAD && (ENABLE_OAD_DATA_SAVE_TO_DB_CH==0) )
    #define FMAP_OAD_BANK_COUNT     1
#else
    #define FMAP_OAD_BANK_COUNT     0
#endif

#define FMAP_OAD_BANK_START         (FMAP_VERSION_DB_BANK_START - FMAP_OAD_BANK_COUNT)

#if( ENABLE_OAD_DATA_SAVE_TO_DB_CH == 0 )
#define OAD_DB_BANK                 FMAP_OAD_BANK_START
#endif

//-------------------------------------------------------------------------------------
// CI  setting database flash map...
#if (ENABLE_CI)
    #define FMAP_CI_BANK_COUNT      1
#else
    #define FMAP_CI_BANK_COUNT      0
#endif

#define FMAP_CI_BANK_START          (FMAP_OAD_BANK_START - FMAP_CI_BANK_COUNT)

#define CIPLUS_KEY_BANK             FMAP_CI_BANK_START
#define CIPLUS_KEY_SIZE             FLASH_BLOCK_SIZE

//-------------------------------------------------------------------------------------
// CIPLUS-KEY setting database flash map...

#if ENABLE_CI_PLUS
//Add CI OP mode database flash map here
//[7 banks are needed for storing op nit data]
// Kervin say: CAM_INFO_DATA need 1 bank
//                      CAM_NIT_DATA(i) need 7 bank
//                      Total need 8 bank?
#define MAX_OP_NIT_DB_COUNT                 MAX_OP_CACHE_NUM
#define CIPLUS_1_3_BANK_CAM_INFO_DATA       FMAP_CI_PLUS_BANK_START //(CIPLUS_KEY_BANK-1)
#define CIPLUS_1_3_BANK_CAM_INFO_COUNT      1

#define CIPLUS_1_3_BANK_CAM_NIT_DATA(i)     (CIPLUS_1_3_BANK_CAM_INFO_DATA + 1 +( ((i)<MAX_OP_CACHE_NUM)?(i):(0) ) )//(CIPLUS_1_3_BANK_CAM_INFO_DATA-1-i) //i<7
//#define CIPLUS_1_3_BANK_SIZE                FLASH_BLOCK_SIZE //64k
#define CIPLUS_1_3_BANK_NUMBER              1
//#define RM_MW_OPCACHE_INFO_START_ADDR       0//(RM_DTV_C_CHSET_START_ADDR+RM_DTV_C_CHSET_SIZE)
#define RM_MW_OPCACHE_INFO_SIZE             (sizeof(MW_OPCACHE_INFO)*MAX_OP_CACHE_NUM)

#if (ENABLE_CI_PLUS_V1_4)
#define CIPLUS_1_4_BANK_VIRTUAL_CHANNEL_START  (CIPLUS_1_3_BANK_CAM_INFO_DATA+CIPLUS_1_3_BANK_CAM_INFO_COUNT)
#define CIPLUS_1_4_BANK_VIRTUAL_CHANNEL_COUNT  1
#define MAX_CI_DB_COUNT   (MAX_OP_NIT_DB_COUNT+CIPLUS_1_3_BANK_CAM_INFO_COUNT+CIPLUS_1_4_BANK_VIRTUAL_CHANNEL_COUNT)
#else
#define MAX_CI_DB_COUNT   (MAX_OP_NIT_DB_COUNT+CIPLUS_1_3_BANK_CAM_INFO_COUNT)
#endif

#define FMAP_CI_PLUS_BANK_COUNT      (MAX_CI_DB_COUNT)

#else
    #define FMAP_CI_PLUS_BANK_COUNT      0
#endif

#define FMAP_CI_PLUS_BANK_START         (FMAP_CI_BANK_START-FMAP_CI_PLUS_BANK_COUNT)

#if ENABLE_CANAL_READY_CIPLUS_AUTH
#define FMAP_CANALREADY_AUTH_COUNT      1
#else
#define FMAP_CANALREADY_AUTH_COUNT      0
#endif

#define FMAP_CANALREADY_AUTH_START          (FMAP_CI_PLUS_BANK_START - FMAP_CANALREADY_AUTH_COUNT)
#define FMAP_CANALREADY_AUTH_BANK           (FMAP_CANALREADY_AUTH_START)
#define FMAP_CANALREADY_AUTH_ADDR           (FMAP_CANALREADY_AUTH_START * FLASH_BLOCK_SIZE)
#define FMAP_CANALREADY_AUTH_SIZE           (FMAP_CANALREADY_AUTH_COUNT * FLASH_BLOCK_SIZE)

//-------------------------------------------------------------------------------------
// Setting Capture Logo flash map...
#if ENABLE_MPLAYER_CAPTURE_LOGO
    #define FMAP_CAPTURE_LOGO_COUNT        8
#else
    #define FMAP_CAPTURE_LOGO_COUNT        0
#endif

#define FMAP_CAPTURE_LOGO_START          (FMAP_CANALREADY_AUTH_START - FMAP_CAPTURE_LOGO_COUNT)
#define FMAP_CAPTURE_LOGO_BANK           (FMAP_CAPTURE_LOGO_START)
#define FMAP_CAPTURE_LOGO_ADDR           (FMAP_CAPTURE_LOGO_START * FLASH_BLOCK_SIZE)
#define FMAP_CAPTURE_LOGO_SIZE           (FMAP_CAPTURE_LOGO_COUNT * FLASH_BLOCK_SIZE)

//-------------------------------------------------------------------------------------
// Total usage
#define FMAP_TOTAL_USE_BANK_END         (FMAP_CAPTURE_LOGO_START)

#endif

