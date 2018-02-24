

##################################################################
# ATSC - Compile option
##################################################################
#CC_TVOPTS += -DATSC_CC=DTV_CC

##################################################################
# LIB
##################################################################

ifneq ($(BUILD_TARGET),BLOADER_SYSTEM)
ifneq ($(MEMORY_SIZE),MEMORY_32MB)	
APP_FILES += $(TVAP)/atsc/app/MApp_TTSControlHandler.c                  
APP_FILES += $(TVAP)/atsc/app/MApp_TTS_Cus.c                  
APP_FILES += $(TVAP)/atsc/app/MApp_TTS_Cus_Say.c                  
INC_DIR += -I$(ROOT)/core/middleware/tts
INC_DIR += -I$(ROOT)/core/middleware/tts/cbr/aeon
INC_DIR += -I$(ROOT)/core/middleware/tts/mst_rsrc
MM_FILES += $(ROOT)/core/middleware/tts/msAPI_TTS_Sys.c
MM_FILES += $(ROOT)/core/middleware/tts/msAPI_TTS_Debug.c
#MM_FILES += $(ROOT)/core/middleware/tts/mst_rsrc.c

  #if not define in ".config", default is en
  ifeq ($(MS_TTS_LIB_SEL),)	
    MS_TTS_LIB_SEL = MS_TTS_LIB_EN
  endif
  
  # Pass this option to C code(msAPI_TTS_Sys.h)
  CC_TVOPTS += -DMS_TTS_LIB_SEL=$(MS_TTS_LIB_SEL)
  
  ifeq ($(MS_TTS_LIB_SEL),MS_TTS_LIB_EN)	
    TTS_LIB_FOLDER = cbr/aeon/En
  else ifeq ($(MS_TTS_LIB_SEL),MS_TTS_LIB_EN_SP_FR)	
    TTS_LIB_FOLDER = cbr/aeon/EnSpFr
  else ifeq ($(MS_TTS_LIB_SEL),MS_TTS_LIB_EN_KR)	
    TTS_LIB_FOLDER = cbr/aeon/EnKr
  else ifeq ($(MS_TTS_LIB_SEL),MS_TTS_LIB_EN_SP_FR_KR)	
    TTS_LIB_FOLDER = cbr/aeon/EnSpFrKr
    
  endif

    DTV_LIB += $(ROOT)/core/middleware/tts/$(TTS_LIB_FOLDER)/libTTS2.a
    DTV_LIB += $(ROOT)/core/middleware/tts/libMsTTS_r2.a 	
    DTV_LIB += $(ROOT)/core/middleware/tts/mst_rsrc/mst_rsrc_r2.a 	
    
endif
endif

##################################################################
# APP - FILES
##################################################################

APP_FILES +=        \
        $(ROOT)/core/api/dtv_atsc/msAPI_AtscEpgDb.c              \
        $(ROOT)/core/api/dtv_atsc/msAPI_Tuner_ATSC.c              \
        $(ROOT)/core/api/msAPI_Scan_ATSC.c                        \
        $(TVAP)/atsc/app/MAPP_ChannelChange_ATSC.c               \
        $(TVAP)/atsc/app/MApp_ChannelProc_ATSC.c                \
        $(TVAP)/atsc/app/MApp_DataBase_ATSC.c                   \
        $(TVAP)/atsc/app/MApp_EpgDB_ATSC.c                         \
	    $(TVAP)/atsc/app/MApp_HuffmanDecode.c                     \
        $(TVAP)/atsc/app/MApp_MultiTasks_ATSC.c			        \
        $(TVAP)/atsc/app/MApp_Psip.c                              \
        $(TVAP)/atsc/app/MApp_SaveData_ATSC.c                      \
        $(TVAP)/atsc/app/MApp_Scan_ATSC.c                          \
        $(TVAP)/atsc/app/MApp_ScanMenu_ATSC.c                      \
        $(TVAP)/atsc/app/MApp_VChip.c                              \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTchannelinfo_ATSC.c                   \
        $(TVAP)/dvb/ui2/MApp_UiMenuFunc_ATSC.c                            \
        $(TVAP)/dvb/ui2/MApp_UiMenuStr_ATSC.c                            \
        $(TVAP)/dvb/ui2/MApp_ZUI_ACTepg_ATSC.c                         \
		$(TVAP)/dvb/ui2/MApp_ZUI_ACTinstall_ATSC.c                     \
		$(TVAP)/dvb/ui2/MApp_Install_Main_ATSC.c                       \


ifneq ($(BUILD_TARGET),BLOADER_SYSTEM)
APP_FILES += $(TVAP)/atsc/app/MApp_Audio_ATSC.c  

endif

		

INC_DIR  += \
        -I$(ROOT)/core/api/dtv_atsc/                            \
        -I$(TVAP)/atsc/app/                                 \
        -I$(TVAP)/atsc/app/include                          \

ifneq ($(MEMORY_SIZE),MEMORY_32MB)		  
INC_DIR  += \
        -I$(ROOT)/core/middleware/tts/include                
endif		

LINT_INC  += \
        $(TVAP)/atsc/app/                                   \
        $(TVAP)/atsc/app/include                            \

