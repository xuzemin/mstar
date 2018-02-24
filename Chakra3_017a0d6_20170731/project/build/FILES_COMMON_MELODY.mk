

BIN_INFO = $(ROOT)/project/image/bininfo/$(chip_name)/BinInfo.h

INC_DIR  += -I$(ROOT)/project/image/bininfo/$(chip_name)

LINT_INC  += $(ROOT)/project/image/bininfo/$(chip_name)

REBUILD_FILES=$(TVAP)/dvb/ui2/MApp_ZUI_ACTmenufunc.c

#----------------------------------------------------------------

# PQ files folder
PQDIR ?= $(chip_name)

##################################################################
# debug msg
##################################################################
CC_TVOPTS += -DENABLE_DBG=0

##################################################################
# Driver / API
##################################################################
DRV_FILES += \
        $(ROOT)/core/driver/power/drvPower_std.c                        \
        $(ROOT)/core/driver/pq/drvPQ.c                                  \
        $(ROOT)/core/driver/pq/drvPQ_Bin.c                              \
        $(ROOT)/core/driver/pq/drvPQ_Text.c                             \
        $(ROOT)/core/driver/pq/drvbw.c                                  \
        $(ROOT)/core/driver/pq/hal/$(PQDIR)/QualityMap_Main.c           \
        $(ROOT)/core/driver/pq/hal/$(PQDIR)/QualityMap_MainEx.c         \
        $(ROOT)/core/driver/pq/hal/$(PQDIR)/mhal_pq.c                   \
        $(ROOT)/core/driver/pq/hal/$(PQDIR)/mhal_pq_adaptive.c		\
        $(ROOT)/core/driver/sys/$(chip_name)/drvUartDebug.c                   \
        $(ROOT)/core/driver/sys/$(chip_name)/SysInit.c                        \
        $(ROOT)/core/driver/sys/$(chip_name)/drvISR.c                         \
        $(ROOT)/core/driver/sys/$(chip_name)/drvPadConf.c                     \
        $(ROOT)/core/driver/usb/$(chip_name)/drvUsbHostLib.c                  \

INC_DIR  += \
        -I$(ROOT)/core/driver/pq/include                                \
        -I$(ROOT)/core/driver/pq/hal/$(PQDIR)/include                   \

##############################################################
# TV-AP
##############################################################
ifeq ($(PARA),1)
APP_FILES += \
          $(TVAP)/common/dmp/MApp_DMP_Main.c					\
          $(TVAP)/common/dmp/MApp_DMP_MiniMenu_Main.c
else
APP_FILES += \
          $(TVAP)/common/app/MApp_PCMode.c                      \
          $(TVAP)/common/dmp/MApp_DMP_Main.c                    \
          $(TVAP)/common/dmp/MApp_DMP_MiniMenu_Main.c		\
          $(TVAP)/common/app/MApp_Logo.c                        \
          $(TVAP)/common/app/MApp_LoadFont.c                    \
          $(TVAP)/common/app/MApp_UsbHeadphone.c                \
          $(TVAP)/common/app/MApp_KeyToSpeech.c                \
          $(TVAP)/common/app/MApp_MSTV_Debug.c
endif

MM_FILES += \
        $(ROOT)/core/middleware/multimedia/mapp_big52unicode_a4a8.c         \
        $(ROOT)/core/middleware/multimedia/mapp_big52unicode_a9af.c         \
        $(ROOT)/core/middleware/multimedia/mapp_big52unicode_b0bb.c         \
        $(ROOT)/core/middleware/multimedia/mapp_big52unicode_bcc6.c         \
        $(ROOT)/core/middleware/multimedia/mapp_big52unicode_f9_a1a3.c      \
        $(ROOT)/core/middleware/multimedia/mapp_gb2unicode1.c               \
        $(ROOT)/core/middleware/multimedia/mapp_gb2unicode.c                \
        $(ROOT)/core/middleware/multimedia/mapp_music.c                     \
        $(ROOT)/core/middleware/multimedia/mapp_mplayer.c                   \
        $(ROOT)/core/middleware/multimedia/mapp_mplayer_subtitle.c          \
        $(ROOT)/core/middleware/multimedia/mapp_photo.c                     \
        $(ROOT)/core/middleware/multimedia/mapp_photo_display.c             \
        $(ROOT)/core/middleware/multimedia/mapp_ptp.c                       \
        $(ROOT)/core/middleware/multimedia/mapp_txt.c                       \
        $(ROOT)/core/middleware/multimedia/mapp_videoplayer.c               \
        $(ROOT)/core/middleware/multimedia/mapp_wma.c                       \
        $(ROOT)/core/middleware/multimedia/mapp_digitalmedia.c              \
        $(ROOT)/core/middleware/multimedia/mapp_buffermanage.c              \
        $(ROOT)/core/middleware/multimedia/verJPD.c                         \
        $(ROOT)/core/middleware/multimedia/stillimage/msapi_stillimage.c    \
        $(ROOT)/core/middleware/multimedia/stillimage/msapi_stillimage_bm.c \
        $(ROOT)/core/middleware/multimedia/stillimage/msapi_jpeg_decoder.c  \
        $(ROOT)/core/middleware/multimedia/stillimage/msapi_bmp_decoder.c   \
        $(ROOT)/core/middleware/multimedia/stillimage/msapi_gif_decoder.c   \
        $(ROOT)/core/middleware/multimedia/stillimage/msapi_stillimage_dlmalloc.c \

UTIL_FILES += \
		$(ROOT)/core/api/utl/Utl.c                         \
		$(ROOT)/core/mms/drvMmsDisp.c                      \
		$(ROOT)/core/mms/cat/drvMmsCat.c                   \
		$(ROOT)/core/mms/cfg/drvMmsCfg.c                   \
		$(ROOT)/core/mms/cfg/board/drvMmsCfgBoardPanel.c         \
		$(ROOT)/core/mms/cfg/chip/drvMmsCfgChipWDT.c             \
		$(ROOT)/core/mms/cfg/chip/drvMmsCfgChipDBG_CMD.c         \
		$(ROOT)/core/mms/cfg/sw/drvMmsCfgSwUSB.c                 \
		$(ROOT)/core/mms/cfg/sw/drvMmsCfgSwIR.c                  \
		$(ROOT)/core/mms/dbg/drvMmsDbg.c                   \
		$(ROOT)/core/mms/dbg/drv/drvMmsDbgDrvMvd.c         \
	    $(ROOT)/core/mms/dbg/drv/drvMmsDbgDrvAeon.c         \

UI_FILES += \
          $(TVAP)/common/dmp/MApp_ZUI_ACTdmp.c              \
          $(TVAP)/common/dmp/MApp_ZUI_ACTdmpminimenu.c      \
          $(TVAP)/common/ui/MApp_ZUI_ACTeffect.c                   \


ZUI_FILES += \
          $(TVAP)/common/zui/MApp_ZUI_APIalphatables.c             \
          $(TVAP)/common/zui/MApp_ZUI_APIChineseIME.c              \
          $(TVAP)/common/zui/MApp_ZUI_APIcomponent.c               \
          $(TVAP)/common/zui/MApp_ZUI_APIcontrols.c                \
          $(TVAP)/common/zui/MApp_ZUI_APIdraw.c                    \
          $(TVAP)/common/zui/MApp_ZUI_APIgdi.c                     \
          $(TVAP)/common/zui/MApp_ZUI_APIpostables.c               \
          $(TVAP)/common/zui/MApp_ZUI_APIstrings.c                 \
          $(TVAP)/common/zui/MApp_ZUI_APIstyletables.c             \
          $(TVAP)/common/zui/MApp_ZUI_APItables.c                  \
          $(TVAP)/common/zui/MApp_ZUI_APIwindow.c                  \
          $(TVAP)/common/zui/MApp_ZUI_CTLanimation.c               \
          $(TVAP)/common/zui/MApp_ZUI_CTLautoclose.c               \
          $(TVAP)/common/zui/MApp_ZUI_CTLballprogbar.c             \
          $(TVAP)/common/zui/MApp_ZUI_CTLballprogbarcolor.c        \
          $(TVAP)/common/zui/MApp_ZUI_CTLbgtransparent.c           \
          $(TVAP)/common/zui/MApp_ZUI_CTLbuttonclick.c             \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynabmp.c                 \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynacolortext.c           \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynaepgpunctext.c         \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynalist2.c               \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynalist.c                \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynapunctext.c            \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynatext.c                \
          $(TVAP)/common/zui/MApp_ZUI_CTLdynatexteffect.c          \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffect.c                  \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectcube.c              \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectfall.c              \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectflip.c              \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectfold.c              \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectpopup.c             \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectroll.c              \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectslideitem.c         \
          $(TVAP)/common/zui/MApp_ZUI_CTLeffectzoom.c              \
          $(TVAP)/common/zui/MApp_ZUI_CTLgrid.c                    \
          $(TVAP)/common/zui/MApp_ZUI_CTLkeyboard.c                \
          $(TVAP)/common/zui/MApp_ZUI_CTLmainframe.c               \
          $(TVAP)/common/zui/MApp_ZUI_CTLmarquee.c                 \
          $(TVAP)/common/zui/MApp_ZUI_CTLmotiontrans.c             \
          $(TVAP)/common/zui/MApp_ZUI_CTLpercentprogbar.c          \
          $(TVAP)/common/zui/MApp_ZUI_CTLradiobutton.c             \
          $(TVAP)/common/zui/MApp_ZUI_CTLrectprogbar.c             \
          $(TVAP)/common/zui/MApp_ZUI_CTLscroller.c                \
          $(TVAP)/common/zui/MApp_ZUI_CTLslider.c                  \
          $(TVAP)/common/zui/MApp_ZUI_CTLspin.c                    \
          $(TVAP)/common/zui/MApp_ZUI_CTLtextviewer.c              \
          #$(TVAP)/common/zui/MApp_ZUI_CTLfake3d.c                  

INC_DIR  += \
         -I$(TVAP)/common/app/include                              \
         -I$(TVAP)/common/ui/include                               \
		 -I$(ROOT)/core/mms/dbg/include                            \
		 -I$(ROOT)/core/mms/dbg/ap/include                         \
		 -I$(ROOT)/core/mms/dbg/mw/include                         \
		 -I$(ROOT)/core/mms/dbg/drv/include                        \
         -I$(ROOT)/core/mms/                                       \
         -I$(ROOT)/core/mms/cfg/include                            \
         -I$(ROOT)/core/mms/cfg/board/include                      \
         -I$(ROOT)/core/mms/cfg/chip/include                       \
         -I$(ROOT)/core/mms/cfg/sw/include                         \

LINT_INC  += \
          $(TVAP)/common/app/                                      \
          $(TVAP)/common/app/include                               \
          $(TVAP)/common/ui/                                       \
          $(TVAP)/common/ui/include                                \


COMMON_DTV_LIB += \
    $(DRV_BSP_PATH)/libdrvMSPI.a               \

#=================================================================================================
#Middleware libraries
ifeq ($(MULTIMEDIA_ARCHITECTURE),HK_MM)
CC_TVOPTS += -DENABLE_HK_MM=1
DTV_LIB += \
    $(ROOT)/core/middleware/multimedia/lib/libvdplayer.a
else
CC_TVOPTS += -DENABLE_HK_MM=0
MM_FILES += \
    $(ROOT)/core/middleware/multimedia/mapp_vdplayer_bm.c

endif

ifeq ($(ENABLE_HK_MP4), 1)
    CC_TVOPTS += -DENABLE_HK_MP4=1
    include $(MIDDLE_LIB_PATH)/multimedia/mp4demux/build/chakra/mp4demux.mk
endif

ifeq ($(ENABLE_HK_SUBTITLE), 1)
    CC_TVOPTS += -DENABLE_HK_SUBTITLE=1
    CC_TVOPTS += -DSUPPORT_SUBTITLE=1
endif

ifeq ($(ENABLE_HK_DRM_GENCODE), 1)
CC_TVOPTS += -DENABLE_HK_DRM_GENCODE=1
DTV_LIB += \
    $(ROOT)/core/bin/$(chip_name)/cape/libdrmcodegen.a
endif

include project/build/FILES_APP_COMMON.mk
