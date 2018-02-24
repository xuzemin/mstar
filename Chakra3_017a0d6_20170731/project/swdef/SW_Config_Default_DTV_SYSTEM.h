#ifndef _SW_CONFIG_DEFAULT_DTV_SYSTEM_H_
#define _SW_CONFIG_DEFAULT_DTV_SYSTEM_H_

//=========================================================

#ifndef ENABLE_ATSC
    #define ENABLE_ATSC         DISABLE
#endif

//-------------------------------------------------------------
#ifndef ENABLE_DVBT
  //#if( (DTV_SYSTEM_SEL== DTV_SYSTEM_DVBT)
  //   ||(DTV_SYSTEM_SEL== DTV_SYSTEM_DVBT_Plus_DVBC)
  // )
    //#define ENABLE_DVBT         ENABLE
  //#else
    #define ENABLE_DVBT         DISABLE
  //#endif
#endif
//----------------------------------------------------------------
#ifndef ENABLE_DTMB
    #define ENABLE_DTMB         DISABLE
#endif
//----------------------------------------------------------------
#ifndef ENABLE_S2
    #define ENABLE_S2           DISABLE
#endif
#ifndef ENABLE_DVBS
    #define ENABLE_DVBS         ENABLE_S2
#endif
//----------------------------------------------------------------
#ifndef ENABLE_DVBC
    #define ENABLE_DVBC         DISABLE
#endif
//----------------------------------------------------------------
#ifndef ENABLE_ISDBT
    #define ENABLE_ISDBT        DISABLE
#endif
//-------------------------------------------------------------------
#ifndef ENABLE_DTV
  #if(ENABLE_ATSC || ENABLE_DVBT || ENABLE_DVBS || ENABLE_DVBC || ENABLE_ISDBT|| ENABLE_DTMB)
    #define ENABLE_DTV      ENABLE
  #else
    #define ENABLE_DTV      DISABLE
  #endif
#endif

#if( ENABLE_DVBT || ENABLE_DVBS || ENABLE_DVBC || ENABLE_ISDBT|| ENABLE_DTMB)
    #define ENABLE_DVB      ENABLE
#else
    #define ENABLE_DVB      DISABLE
#endif


#if( ENABLE_DVBT || ENABLE_DVBS || ENABLE_DVBC || ENABLE_DTMB)
    #define ENABLE_DVB_NOISDB      ENABLE
#else
    #define ENABLE_DVB_NOISDB      DISABLE
#endif

#if( ENABLE_ISDBT && !(ENABLE_DVBT||ENABLE_DVBS || ENABLE_DVBC || ENABLE_DTMB) )
    #define ENABLE_ISDBT_NO_DVB     ENABLE
#else
    #define ENABLE_ISDBT_NO_DVB     DISABLE
#endif

#if( ENABLE_ISDBT && (ENABLE_DVBT||ENABLE_DVBS || ENABLE_DVBC || ENABLE_DTMB) )
    #define ENABLE_ISDBT_AND_DVB    ENABLE
#else
    #define ENABLE_ISDBT_AND_DVB    DISABLE
#endif

//=========================================================
#endif // _SW_CONFIG_DEFAULT_DTV_SYSTEM_H_

