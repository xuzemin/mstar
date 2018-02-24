
#----------------------------------------------------------------------------------
ifeq ($(CHIP_FAMILY),EULER)
    chip_name = euler
    OS_TYPE = nos_aeon
else ifeq ($(CHIP_FAMILY),EDEN)
    chip_name = eden
    OS_TYPE = nos_aeon
else ifeq ($(CHIP_FAMILY),NASA)
    chip_name = nasa
    OS_TYPE = nos_aeon
else ifeq ($(CHIP_FAMILY),EMERALD)
    chip_name = emerald
    OS_TYPE = nos_mips
else ifeq ($(CHIP_FAMILY),NUGGET)
    chip_name = nugget
    OS_TYPE = nos_mips
else ifeq ($(CHIP_FAMILY),NIKON)
    chip_name = nikon
    OS_TYPE = nos_mips
else ifeq ($(CHIP_FAMILY),MILAN)
    chip_name = milan
    OS_TYPE = nos_mips

else ifeq ($(CHIP_FAMILY),MAYA)
    chip_name = maya
    OS_TYPE = nos_aeon

else ifeq ($(CHIP_FAMILY),WHISKY)
    chip_name = whisky
    OS_TYPE = nos_aeon

else ifeq ($(CHIP_FAMILY),MELODY)
    chip_name = melody
    OS_TYPE = nos_aeon

else ifeq ($(CHIP_FAMILY),MARLON)
    chip_name = marlon
    OS_TYPE = nos_mips

else ifeq ($(CHIP_FAMILY),MAZDA)
    chip_name = mazda
    OS_TYPE = nos_arm
	
endif

#----------------------------------------------------------------------------------
ifeq ($(OS_TYPE),nos_aeon)
    CC_TVOPTS += -DMCU_AEON
endif    
