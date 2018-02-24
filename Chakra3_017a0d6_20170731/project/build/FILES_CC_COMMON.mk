

##################################################################
# CC - Compile option
##################################################################
ifeq ($(ATSC_CC),DTV_CC)
	CC_TVOPTS += -DATSC_CC=DTV_CC
else ifeq ($(ATSC_CC),BRA_CC)
	CC_TVOPTS += -DATSC_CC=BRA_CC
else
	CC_TVOPTS += -DATSC_CC=ATV_CC
endif

ifeq ($(ENABLE_ATSC_KOR),ENABLE)
CC_TVOPTS += -DENABLE_ATSC_KOR=ENABLE
else
CC_TVOPTS += -DENABLE_ATSC_KOR=DISABLE
endif

##################################################################
# CC LIB
##################################################################

ifeq ($(OS_TYPE),nos_mips)

    DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_monitor_sf_mips_nos.a 
    DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_render_gegop_sf_mips_nos.a 

  ifeq ($(ATSC_CC),BRA_CC)
	DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_brazil_sf_mips_nos.a
  endif

  ifeq ($(ENABLE_ATSC_KOR),ENABLE)
	DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_korean_sf_mips_nos.a
  else
	DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_english_sf_mips_nos.a
  endif
  
else ifeq ($(OS_TYPE),nos_arm)

  DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_monitor_hf_arm_nos.a
  DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_render_gegop_hf_arm_nos.a

  ifeq ($(ATSC_CC),BRA_CC)
	DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_brazil_hf_arm_nos.a
  endif

  ifeq ($(ENABLE_ATSC_KOR),ENABLE)
	DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_korean_sf_arm_nos.a
  else
	DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_english_hf_arm_nos.a
  endif  


else
	DTV_LIB += \
		$(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_monitor_hf_aeonr2_nos.a \
		$(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_render_gegop_hf_aeonr2_nos.a

	ifeq ($(ATSC_CC),BRA_CC)
		DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_brazil_hf_aeonr2_nos.a
	endif

	ifeq ($(ENABLE_ATSC_KOR),ENABLE)
		DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_korean_hf_aeonr2_nos.a
	else
		DTV_LIB += $(MIDDLE_LIB_PATH)/closedcaption/lib/libcc_decode_english_hf_aeonr2_nos.a
	endif

endif


##################################################################
# CC - FILES
##################################################################
ifneq ($(ATSC_CC),BRA_CC)
CC_FILES += \
        $(ROOT)/core/middleware/closedcaption/atsc/mapp_closedcaption.c
else
CC_FILES += \
        $(ROOT)/core/middleware/closedcaption/brazil/mapp_closedcaption_brazil.c
endif
CC_FILES += \
        $(ROOT)/core/middleware/closedcaption/lib/msAPI_cc_sysinfo.c   \
        $(ROOT)/core/middleware/closedcaption/lib/msAPI_cc_parser.c    \

INC_DIR  += \
        -I$(ROOT)/core/middleware/closedcaption/lib/include     \
        -I$(ROOT)/core/middleware/closedcaption/atsc			\

LINT_INC  += \
        $(ROOT)/core/middleware/closedcaption/lib/include     \
        $(ROOT)/core/middleware/closedcaption/atsc			\

