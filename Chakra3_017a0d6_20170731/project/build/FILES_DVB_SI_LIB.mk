ifeq ($(_FILES_DVB_SI_),)
_FILES_DVB_SI_=ENABLE

#=============================================================================================

SI_FILES += \
        $(ROOT)/core/middleware/si/dvb/mapp_demux_if.c                 \
        $(ROOT)/core/middleware/si/dvb/mapp_si_if.c                     \
        $(ROOT)/core/middleware/si/dvb/mapp_si_util.c                   \


INC_DIR  += \
        -I$(ROOT)/core/middleware/si/dvb/include                    \
        -I$(ROOT)/core/middleware/epg/dvb/include                   \


LINT_INC  += \
        $(ROOT)/core/middleware/si/dvb/include                      \


#=============================================================================================

ifeq ($(OS_TYPE),nos_aeon)

  ifneq ($(SI_LIB_FILE),)
    DTV_LIB += $(MIDDLE_LIB_PATH)/si/dvb/$(SI_LIB_FILE)
  else
    DTV_LIB += $(MIDDLE_LIB_PATH)/si/dvb/libdvbsi_aeonR2.a
  endif

    DTV_LIB += $(MIDDLE_LIB_PATH)/epg/dvb/libdvbepgdb_aeonR2.a               

else ifeq ($(OS_TYPE),nos_arm)

  ifneq ($(SI_LIB_FILE),)
    DTV_LIB += $(MIDDLE_LIB_PATH)/si/dvb/$(SI_LIB_FILE)
  else
    DTV_LIB += $(MIDDLE_LIB_PATH)/si/dvb/libdvbsi_arm.a
  endif

    DTV_LIB += $(MIDDLE_LIB_PATH)/epg/dvb/libdvbepgdb_arm.a        
else


  ifneq ($(SI_LIB_FILE),)
    DTV_LIB += $(MIDDLE_LIB_PATH)/si/dvb/$(SI_LIB_FILE)
  else
    DTV_LIB += $(MIDDLE_LIB_PATH)/si/dvb/libdvbsi_mips.a
  endif

    DTV_LIB += $(MIDDLE_LIB_PATH)/epg/dvb/libdvbepgdb_mips.a            

endif

#=============================================================================================

endif # _FILES_DVB_COMMON_