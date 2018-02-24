#ifndef _MAPP_GLOBAL_SETTING_ST_TV_S2_H_
#define _MAPP_GLOBAL_SETTING_ST_TV_S2_H_


#include "MsTypes.h"

#if(ENABLE_S2)

/*
typedef enum
{
    ZUIUTL_LBNAV_EMPTYFLAG             = BIT0,
    ZUIUTL_LBNAV_SCROLLBAR_ENABLE      = BIT1, //enable scrollbar
    ZUIUTL_LBNAV_PAGEKEY_ENABLE        = BIT2, //enable page up/down key
    ZUIUTL_LBNAV_LRKEY4PAGE_ENABLE     = BIT3, //enable left/right key for page up/down
    ZUIUTL_LBNAV_SCROLLING_ENABLE      = BIT4, //enable scrolling when page changes. others we flip a page.
    ZUIUTL_LBNAV_CONTINUOUS_NAV_ENABLE = BIT5, //enable navigation no stop at beginning/end line.
} ZUIUTL_LBNAV_FLAG;
*/


#define MAX_NUM_OF_SAT      65 //max physical channel
#define MAX_SATNAME_LEN     15
#define MAX_SATTABLEMAP     ((MAX_NUM_OF_SAT+7)/8)

#define MAX_SCANSAT_NUM     MAX_NUM_OF_SAT


//=================================================================

typedef enum
{
    EN_22K_OFF,
    EN_22K_ON,
    EN_22K_AUTO,
    EN_22K_ONOFF_NUM
}MS_EN_22K_ONOFF;

typedef enum
{
    EN_LNBPWR_OFF,
    EN_LNBPWR_13OR18V,
    EN_LNBPWR_13V,
    EN_LNBPWR_18V,
    EN_LNBPWR_ONOFF_NUM
}MS_EN_LNBPWR_ONOFF;


typedef enum
{
    EN_LNBTYPE_C,
    EN_LNBTYPE_KU,
    EN_LNBTYPE_2LOF,
    #if(SUPPORT_UNICABLE)
    EN_LNBTYPE_UNICABLE,
    #endif
    EN_LNBTYPE_NUM
}MS_EN_LNBTYPE;

typedef struct //add by wwt
{
    MS_U16 u16LoLOF; // low LOF value,unit MHz
    MS_U16 u16HiLOF; // high LOF value,unit MHz
    MS_EN_LNBTYPE eLNBType;// Single LOF or Double LOF
    MS_EN_22K_ONOFF e22KOnOff;
    MS_EN_LNBPWR_ONOFF eLNBPwrOnOff;
}MS_GENERAL_SAT_INF;

typedef struct
{
    MS_U8* Location;
    MS_S16 MyLongitude;
    MS_S16 MyLatitude;
}DISH_LOCATION;


#endif // #if(ENABLE_S2)

#if 0//(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
//INTERFACE BYTE g_favorite_type;
#endif

#if ENABLE_S2_DATABASE_DBM
INTERFACE MS_U8 u8DbManageMode;
#endif




#endif

