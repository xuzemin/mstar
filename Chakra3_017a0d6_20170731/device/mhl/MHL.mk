# ********************************************************************
# MHL_TYPE: 
#     MHL_TYPE_NONE
#     MHL_TYPE_INTERNAL
#     MHL_TYPE_ELAND
#     MHL_TYPE_SI
#     MHL_TYPE_SiI1292
# ENABLE_MHL:
#     ENABLE
#     DISABLE
# ********************************************************************

ENABLE_MHL=DISABLE#
MHL_TYPE=MHL_TYPE_NONE#

# ********************************************************************
# Macro
# ********************************************************************

CC_TVOPTS += \
    -DENABLE_MHL=$(ENABLE_MHL)                                    \
    -DMHL_TYPE=$(MHL_TYPE)                                        \


# ********************************************************************
# MHL_DIR: MHL IC driver directory
# ********************************************************************

ifeq ($(MHL_TYPE),MHL_TYPE_NONE)
#Do nothing.
MHL_DIR= #
else ifeq ($(MHL_TYPE),MHL_TYPE_INTERNAL)
#Reserved
MHL_DIR=Internal
else ifeq ($(MHL_TYPE),MHL_TYPE_ELAND)
MHL_DIR=Eland
else ifeq ($(MHL_TYPE),MHL_TYPE_SI)
#Reserved
MHL_DIR=SI#
else ifeq ($(MHL_TYPE),MHL_TYPE_SiI1292)
MHL_DIR=SiI1292#
else
#Print "Wrong MHL Type" message
endif


ifeq ($(ENABLE_MHL),ENABLE)


# ********************************************************************
#
# ********************************************************************

API_FILES += \
        $(ROOT)/core/api/msAPI_MHL.c

# ********************************************************************
#
# ********************************************************************

DEVICES_FILES += \
        $(ROOT)/device/mhl/Mhl.c


ifeq ($(MHL_TYPE),MHL_TYPE_ELAND)
DEVICES_FILES += \
        $(ROOT)/device/mhl/$(MHL_DIR)/halMHL_ELAND.c               \
        $(ROOT)/device/mhl/$(MHL_DIR)/drvMHL_ELAND.c               \
        $(ROOT)/device/mhl/$(MHL_DIR)/apiMHL_ELAND.c
else ifeq ($(MHL_TYPE),MHL_TYPE_SiI1292)
DEVICES_FILES += \
        $(ROOT)/device/mhl/$(MHL_DIR)/API/si_api1292.c                  \
        $(ROOT)/device/mhl/$(MHL_DIR)/CBUS/si_apiCbus.c                  \
        $(ROOT)/device/mhl/$(MHL_DIR)/MSC/si_apiMSC.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/MSC/si_apiRAP.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/MSC/si_apiRCP.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/EDID/si_apiEdid.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/CEC/si_apiCEC.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/CEC/si_apiCpi.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/MAIN/si_cp1292.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/MAIN/si_cp1292_ext.c               \
        $(ROOT)/device/mhl/$(MHL_DIR)/MAIN/si_cpIr.c               \
        $(ROOT)/device/mhl/$(MHL_DIR)/API/si_regio.c                    \
        $(ROOT)/device/mhl/$(MHL_DIR)/MAIN/si_cpCbus.c                   \
        $(ROOT)/device/mhl/$(MHL_DIR)/CBUS/si_RegioCbus.c        \
        $(ROOT)/device/mhl/$(MHL_DIR)/HAL/si_hal.c
        
endif

# ********************************************************************
#
# ********************************************************************

INC_DIR  += \
        -I$(ROOT)/device/mhl                                        \
        -I$(ROOT)/device/mhl/$(MHL_DIR)

# ********************************************************************
#
# ********************************************************************

LINT_INC  += \
        $(ROOT)/device/mhl                                          \
        $(ROOT)/device/mhl/$(MHL_DIR)

endif
