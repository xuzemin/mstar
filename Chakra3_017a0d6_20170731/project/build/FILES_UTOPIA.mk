
##################################################################
# Utopia Driver files
##################################################################

ifeq ($(DRV_BSP_PATH),)
    DRV_BSP_PATH = $(ROOT)/core/drv_bsp/$(chip_name)_nos_r2m/lib
endif

UTOPIA_LIB += \
    $(DRV_BSP_PATH)/libapiAUDIO.a                                  \
    $(DRV_BSP_PATH)/libdrvAUDSP.a                                  \
    $(DRV_BSP_PATH)/libdrvAVD.a                                    \
    $(DRV_BSP_PATH)/libdrvSYS.a                                    \
    $(DRV_BSP_PATH)/libdrvDEMOD.a                                  \
    $(DRV_BSP_PATH)/libdrvIPAUTH.a                                 \
    $(DRV_BSP_PATH)/libdrvVIF.a                                    \
    $(DRV_BSP_PATH)/libdrvPCMCIA.a                                 \
    $(DRV_BSP_PATH)/libdrvIR.a                                     \
    $(DRV_BSP_PATH)/libapiGFX.a                                    \
    $(DRV_BSP_PATH)/libdrvVBI.a                                    \
    $(DRV_BSP_PATH)/libapiGOP.a                                    \
    $(DRV_BSP_PATH)/libdrvSEM.a                                    \
    $(DRV_BSP_PATH)/libdrvGPIO.a                                   \
    $(DRV_BSP_PATH)/libdrvHWI2C.a                                  \
    $(DRV_BSP_PATH)/libdrvSERFLASH.a                               \
    $(DRV_BSP_PATH)/libapiJPEG.a                                   \
    $(DRV_BSP_PATH)/libapiVDEC.a                                   \
    $(DRV_BSP_PATH)/libdrvMVOP.a                                   \
    $(DRV_BSP_PATH)/libdrvCPU.a                                    \
    $(DRV_BSP_PATH)/libdrvPWM.a                                    \
    $(DRV_BSP_PATH)/libdrvBDMA.a                                   \
    $(DRV_BSP_PATH)/libdrvPM.a                                     \
    $(DRV_BSP_PATH)/libdrvSAR.a                                    \
    $(DRV_BSP_PATH)/libdrvMMIO.a                                   \
    $(DRV_BSP_PATH)/libdrvDSCMB.a                                  \
    $(DRV_BSP_PATH)/libdrvUART.a                                   \
    $(DRV_BSP_PATH)/libdrvMFC.a                                    \
    $(DRV_BSP_PATH)/libdrvPWS.a                                    \
    \
    $(DRV_BSP_PATH)/libdrvUSB_HOST_P1.a                            \
    $(DRV_BSP_PATH)/libdrvUSB_HOST_P2.a                            \
    $(DRV_BSP_PATH)/libdrvUSB_HID_P1.a                             \
    $(DRV_BSP_PATH)/libdrvUSB_HID_P2.a                             \
    $(DRV_BSP_PATH)/libdrvMIU.a                                    \
    \
	$(DRV_BSP_PATH)/libdrvAESDMA.a                                 \
    $(DRV_BSP_PATH)/libdrvVE.a                                     \
    \
    $(DRV_BSP_PATH)/libapiMHL.a                                    \
    $(DRV_BSP_PATH)/libdrvMSPI.a               \
    $(DRV_BSP_PATH)/libdrvIRQ.a                \
    $(DRV_BSP_PATH)/libMsOS.a                  \
    $(DRV_BSP_PATH)/libapiDMX.a                \
    $(DRV_BSP_PATH)/libdrvDDC2BI.a             \
    $(DRV_BSP_PATH)/libdrvMBX.a                \
    $(DRV_BSP_PATH)/libapiACE.a                \
    $(DRV_BSP_PATH)/libapiCEC.a                \
    $(DRV_BSP_PATH)/libapiDLC.a                \
    $(DRV_BSP_PATH)/libapiPNL.a                \
    $(DRV_BSP_PATH)/libapiXC.a                 \
    $(DRV_BSP_PATH)/libapiSWI2C.a              \
    $(DRV_BSP_PATH)/libdrvWDT.a                \

