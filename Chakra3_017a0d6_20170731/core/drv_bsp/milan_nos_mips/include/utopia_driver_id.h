#ifndef _UTOPIA_DRIVER_ID_H_
#define _UTOPIA_DRIVER_ID_H_

// add new module here
#define INCLUDED_MODULE \
    PREFIX(UTOPIA) \
    PREFIX(BDMA) \
    PREFIX(AESDMA) \
    PREFIX(DSCMB) \
    PREFIX(CI) \
    PREFIX(GOP) \
    PREFIX(GFX) \
    PREFIX(TVENCODER) \
    PREFIX(XC) \
    PREFIX(MBX) \
    PREFIX(TSP) \
    PREFIX(DIP) \
    PREFIX(PNL) \
    PREFIX(VBI) \
    PREFIX(ACE) \
    PREFIX(DLC) \
    PREFIX(IR) \
    PREFIX(SAR) \
    PREFIX(MIU) \
    PREFIX(PWS) \
    PREFIX(FLASH) \
    PREFIX(SEAL) \
    PREFIX(CMDQ) \
    PREFIX(MMFI) \
    PREFIX(SEM) \
    PREFIX(SYS) \
    PREFIX(VDEC_EX) \
    PREFIX(MVOP)    \
    PREFIX(AVD)    \
    PREFIX(DMX) \
    PREFIX(RTC) \
    PREFIX(HWI2C) \
    PREFIX(VDEC) \
    PREFIX(UART) \
    PREFIX(PWM) \
    PREFIX(NJPEG_EX) \
    PREFIX(GPD) \
    PREFIX(CPU) \

enum eMsModule {
#define PREFIX(MODULE) MODULE_##MODULE,
    INCLUDED_MODULE
#undef PREFIX
};

#endif
