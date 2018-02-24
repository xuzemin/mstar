////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _DRV_CREADER_H
#define _DRV_CREADER_H
#if 1   // for 51 platform
#include "datatype.h"
#include "debug.h"
#include "msAPI_Timer.h"
#include "SysInit.h"
#else
#include "debug.h"
#ifdef PLATFORM
#undef PLATFORM
#define PLATFORM OPENRISC
#endif
#include <cyg/infra/cyg_type.h>
#include <cyg/infra/cyg_ass.h>
#include <cyg/infra/diag.h>
#include <cyg/hal/hal_arch.h>
#include <cyg/hal/hal_io.h>
#include <cyg/hal/drv_api.h>
#include <cyg/io/io.h>
#include <cyg/io/devtab.h>
#include <cyg/io/disk.h>
#include "MsTypes.h"
#include "MsMemory.h"
#include "MsOs.h"
#include "Mscommon.h"
typedef BOOL                BOOLEAN;

#endif
/*definition ====================================================================================*/
#define CREADER_READ_ONLY                    false
#define CREADER_SECTOR_SIZE_512BYTE            512
#define CREADER_DEBUG_FAT12                    1
#define CREADER_DEBUG_FAT16                    2
#define CREADER_DEBUG_FAT32                    3
#define CREADER_DEBUG_TYPE                    CREADER_DEBUG_FAT32
#if(CREADER_DEBUG_TYPE == CREADER_DEBUG_FAT12)
#if 0
#define CREADER_DEBUG_PATH                    ".\\..\\..\\..\\..\\..\\fat\\diskimage_driveX_fat12.bin"
#define CREADER_DEBUG_DRIVE                    "X"
#else
#define CREADER_DEBUG_PATH                    ".\\..\\..\\..\\..\\..\\fat\\diskimage_sdcard_fat12.bin"
#define CREADER_DEBUG_DRIVE                    "G"
#endif
#elif(CREADER_DEBUG_TYPE == CREADER_DEBUG_FAT16)
#if 0
#define CREADER_DEBUG_PATH                    ".\\..\\..\\..\\..\\..\\fat\\diskimage_driveW_fat16.bin"
#define CREADER_DEBUG_DRIVE                    "W"
#else
#define CREADER_DEBUG_PATH                    ".\\..\\..\\..\\..\\..\\fat\\diskimage_sdcard_fat16.bin"
#define CREADER_DEBUG_DRIVE                    "G"
#endif
#elif(CREADER_DEBUG_TYPE == CREADER_DEBUG_FAT32)
#if 0
#define CREADER_DEBUG_PATH                    ".\\..\\..\\..\\..\\..\\fat\\diskimage_driveV_fat32.bin"
#define CREADER_DEBUG_DRIVE                    "V"
#else
#define CREADER_DEBUG_PATH                    ".\\..\\..\\..\\..\\..\\fat\\diskimage_sdcard_fat32.bin"
#define CREADER_DEBUG_DRIVE                    "G"
#endif
#endif


#define MIU_WIDTH   8
//#define FCIE_MUTEX
#define FCIE_CPU_DELAY
//#define FCIE_CONFIG_1

#if (PLATFORM==OPENRISC)
#define OffShift        2
#define FCIE_BASE         0xBF818000
#define REG(addr) (*(volatile U32 *)(addr))
#define le16_2_cpu(x)   (x)
#elif (PLATFORM==MCU8051)
//#define REG(addr) (*(volatile U8 xdata*)(addr))

#define OffShift        1
#define FCIE_BASE         0x2000

//==========================================================
#define CHIPTOP_BASE                (0xF00<<OffShift)
#define reg_fcie_config             (CHIPTOP_BASE+(0x03<<OffShift)+0)
#define R_FCIE_MODE_1               (0x01<<6)
#define R_FCIE_MODE_2               (0x02<<6)
#define R_FCIE_MODE_MASK            (R_FCIE_MODE_1+R_FCIE_MODE_2)
#define reg_clk_fcie                (CHIPTOP_BASE+(0x1C<<OffShift)+1)
#define reg_pciisgpio               (CHIPTOP_BASE+(0x70<<OffShift)+0)
#define R_PCIISGPIO_MASK            (0x1F)
#define reg_pciconfig               (CHIPTOP_BASE+(0x02<<OffShift)+0)
#define R_PCICONFIG_MASK            (0x03)
#define reg_pcmduse                 (CHIPTOP_BASE+(0x52<<OffShift)+1)
#define R_PCMDUSE_MASK              (0x1)
#define reg_chip_config_overwrite   (CHIPTOP_BASE+(0x00<<OffShift)+0)
#define reg_chip_config_overwrite_1 (CHIPTOP_BASE+(0x00<<OffShift)+1)
#define R_JTAG_SEL_SAR_9            0x02
#define R_JTAG_SEL_SAR_13           0x20
#define R_JTAG_SEL_SAR_MASK         (R_JTAG_SEL_SAR_9+R_JTAG_SEL_SAR_13)
#define reg_test_out_mode           (CHIPTOP_BASE+(0x02<<OffShift)+0)
#define R_TEST_OUT_MODE1            (0x1<<0x6)
#define R_TEST_OUT_MODE2            (0x2<<0x6)
#define R_TEST_OUT_MODE3            (0x3<<0x6)
#define R_TEST_OUT_MODE_MASK        (0x3<<0x6)
#define reg_dspejtagmode            (CHIPTOP_BASE+(0x03<<OffShift)+1)
#define R_DSPJTAG_USE_SAR_PAD           (0x1<<1)
#define R_DSPJTAG_USE_TS1_PAD           (0x2<<1)
#define R_DSPJTAG_USE_PCMCIA_PAD        (0x3<<1)
#define R_DSPJTAG_USE_TS0_PAD           (0x4<<1)
#define R_DSPJTAG_USE_DOUT_PAD          (0x6<<1)
#define R_DSPJTAG_USE_PAD_MASK          (0x7<<1)

#define SAR_BASE                    (0x1D00<<OffShift)
#define reg_oen_sar_gpio            (SAR_BASE+(0x10<<OffShift)+0)
#define R_SAR_GPIO_OUTPUT_EN        (0xF<<4)
#define reg_i_sar_gpio              (SAR_BASE+(0x10<<OffShift)+1)


//==========================================================

#define MIE_EVENT_1       (FCIE_BASE+(0x00<<OffShift)+1)
#define MIE_INT_EN_1      (FCIE_BASE+(0x01<<OffShift)+1)
#define MMA_PRI_REG_1     (FCIE_BASE+(0x02<<OffShift)+1)
#define MIU_DMA1_1        (FCIE_BASE+(0x03<<OffShift)+1)
#define MIU_DMA0_1        (FCIE_BASE+(0x04<<OffShift)+1)
#define CARD_EVENT_1      (FCIE_BASE+(0x05<<OffShift)+1)
#define CARD_INT_EN_1     (FCIE_BASE+(0x06<<OffShift)+1)
#define CARD_DET_1        (FCIE_BASE+(0x07<<OffShift)+1)
#define CARD_PWR_1        (FCIE_BASE+(0x08<<OffShift)+1)
#define INTR_TEST_1       (FCIE_BASE+(0x09<<OffShift)+1)
#define MIE_PATH_CTL_1    (FCIE_BASE+(0x0A<<OffShift)+1)
#define JOB_BL_CNT_1      (FCIE_BASE+(0x0B<<OffShift)+1)
#define TR_BK_CNT_1       (FCIE_BASE+(0x0C<<OffShift)+1)
#define RSP_SIZE_1        (FCIE_BASE+(0x0D<<OffShift)+1)
#define CMD_SIZE_1        (FCIE_BASE+(0x0E<<OffShift)+1)
#define CARD_WD_CNT_1     (FCIE_BASE+(0x0F<<OffShift)+1)
#define SD_MODE_1         (FCIE_BASE+(0x10<<OffShift)+1)
#define SD_CTL_1          (FCIE_BASE+(0x11<<OffShift)+1)
#define SD_STS_1          (FCIE_BASE+(0x12<<OffShift)+1)
#define MS_MODE_1         (FCIE_BASE+(0x13<<OffShift)+1)
#define MS_CTL_1          (FCIE_BASE+(0x14<<OffShift)+1)
#define MS_STS_1          (FCIE_BASE+(0x15<<OffShift)+1)
#define TEST_MODE_1       (FCIE_BASE+(0x30<<OffShift)+1)
#endif


//===================================================================
// fcie register constant
//===================================================================
#define MIE_EVENT       (FCIE_BASE+(0x00<<OffShift))
#define MIE_INT_EN      (FCIE_BASE+(0x01<<OffShift))
#define MMA_PRI_REG     (FCIE_BASE+(0x02<<OffShift))
#define MIU_DMA1        (FCIE_BASE+(0x03<<OffShift))
#define MIU_DMA0        (FCIE_BASE+(0x04<<OffShift))
#define CARD_EVENT      (FCIE_BASE+(0x05<<OffShift))
#define CARD_INT_EN     (FCIE_BASE+(0x06<<OffShift))
#define CARD_DET        (FCIE_BASE+(0x07<<OffShift))
#define CARD_PWR        (FCIE_BASE+(0x08<<OffShift))
#define INTR_TEST       (FCIE_BASE+(0x09<<OffShift))
#define MIE_PATH_CTL    (FCIE_BASE+(0x0A<<OffShift))
#define JOB_BL_CNT      (FCIE_BASE+(0x0B<<OffShift))
#define TR_BK_CNT       (FCIE_BASE+(0x0C<<OffShift))
#define RSP_SIZE        (FCIE_BASE+(0x0D<<OffShift))
#define CMD_SIZE        (FCIE_BASE+(0x0E<<OffShift))
#define CARD_WD_CNT     (FCIE_BASE+(0x0F<<OffShift))
#define SD_MODE         (FCIE_BASE+(0x10<<OffShift))
#define SD_CTL          (FCIE_BASE+(0x11<<OffShift))
#define SD_STS          (FCIE_BASE+(0x12<<OffShift))
#define MS_MODE         (FCIE_BASE+(0x13<<OffShift))
#define MS_CTL          (FCIE_BASE+(0x14<<OffShift))
#define MS_STS          (FCIE_BASE+(0x15<<OffShift))
/*
#define CF_INF_CTL1     (FCIE_BASE+(0x16<<OffShift))
#define CF_INF_CTL2     (FCIE_BASE+(0x17<<OffShift))
#define CF_BUS          (FCIE_BASE+(0x18<<OffShift))
#define CF_STB_SET      (FCIE_BASE+(0x19<<OffShift))
#define CF_CTL          (FCIE_BASE+(0x1A<<OffShift))
#define CIF_FIFO_CTL    (FCIE_BASE+(0x25<<OffShift))
#define SM_INF_CTL      (FCIE_BASE+(0x26<<OffShift))
#define SM_ADR_REQ      (FCIE_BASE+(0x27<<OffShift))
#define SM_CMD_REQ      (FCIE_BASE+(0x28<<OffShift))
#define SM_STB_SET      (FCIE_BASE+(0x29<<OffShift))
#define SM_MODE         (FCIE_BASE+(0x2A<<OffShift))
#define SM_CTL          (FCIE_BASE+(0x2B<<OffShift))
#define SM_STS          (FCIE_BASE+(0x2C<<OffShift))
*/
#define TEST_MODE       (FCIE_BASE+(0x30<<OffShift))
#define CIF_C_ADDR      (FCIE_BASE+(0x40<<OffShift))
#define CIF_D_ADDR      (FCIE_BASE+(0x100<<OffShift))

#if (PLATFORM==OPENRISC)
// system register constant
#define SYSTEM_BASE     0xBF800000
#define reg_pci_drv_0   (SYSTEM_BASE+(0x40<<OffShift))
#define reg_pci_drv_1   (SYSTEM_BASE+(0x41<<OffShift))
#define reg_pci_drv_2   (SYSTEM_BASE+(0x42<<OffShift))
#define reg_pci_drv_3   (SYSTEM_BASE+(0x43<<OffShift))
#define reg_pci_drv_4   (SYSTEM_BASE+(0x44<<OffShift))
#define reg_pci_drv_5   (SYSTEM_BASE+(0x45<<OffShift))

#define reg_pci_rpu_0   (SYSTEM_BASE+(0x50<<OffShift))
#define reg_pci_rpu_1   (SYSTEM_BASE+(0x51<<OffShift))
#define reg_pci_rpu_2   (SYSTEM_BASE+(0x52<<OffShift))
#define reg_pci_rpu_3   (SYSTEM_BASE+(0x53<<OffShift))
#define reg_pci_rpu_4   (SYSTEM_BASE+(0x54<<OffShift))
#define reg_pci_rpu_5   (SYSTEM_BASE+(0x55<<OffShift))

#define reg_pci_rpupci_0    (SYSTEM_BASE+(0x60<<OffShift))
#define reg_pci_rpupci_1    (SYSTEM_BASE+(0x61<<OffShift))
#define reg_pci_rpupci_2    (SYSTEM_BASE+(0x62<<OffShift))
#define reg_pci_rpupci_3    (SYSTEM_BASE+(0x63<<OffShift))
#define reg_pci_rpupci_4    (SYSTEM_BASE+(0x64<<OffShift))
#define reg_pci_rpupci_5    (SYSTEM_BASE+(0x65<<OffShift))

#define reg_pci_rpd_0   (SYSTEM_BASE+(0x70<<OffShift))
#define reg_pci_rpd_1   (SYSTEM_BASE+(0x71<<OffShift))
#define reg_pci_rpd_2   (SYSTEM_BASE+(0x72<<OffShift))
#define reg_pci_rpd_3   (SYSTEM_BASE+(0x73<<OffShift))
#define reg_pci_rpd_4   (SYSTEM_BASE+(0x74<<OffShift))
#define reg_pci_rpd_5   (SYSTEM_BASE+(0x75<<OffShift))
#endif


//#define REG0008         (0x08<<OffShift)
/*
//============================================
//REG0008:offset 0x08
//============================================
#define R_SEL_XTAL_CLK  0x2000
#define R_INVERT_CLOCK  0x0100
#define R_DISABLE_CLOCK 0x0080

#define MIE_CLK_MASK    0x1E00
#define MIE_CLK_350K   (0x0<<9)
#define MIE_CLK_1500K  (0x1<<9)
#define MIE_CLK_6M     (0x2<<9)
#define MIE_CLK_15M    (0x3<<9)
#define MIE_CLK_20M    (0x4<<9)
#define MIE_CLK_25M    (0x5<<9)
#define MIE_CLK_30M    (0x6<<9)
#define MIE_CLK_40M    (0x7<<9)
#define MIE_CLK_50M    (0x8<<9)
#define MIE_CLK_60M    (0x9<<9)
#define MIE_CLK_80M    (0xA<<9)
*/

// fcie register constant
//============================================
//MIE_EVENT:offset 0x0
//============================================
#define R_SDIO_INT      0x0080
//#define R_SM_JOB_END    0x0040
//#define R_CF_DATA_END   0x0020
//#define R_CF_CMD_END    0x0010
#define R_MS_DATA_END   0x0008
#define R_SD_DATA_END   0x0004
#define R_SD_CMD_END    0x0002
#define R_MMA_DATA_END  0x0001
//============================================
//MIE_INT_EN:offset 0x1
//============================================
#define R_SDIO_INT_EN   0x0080
//#define R_SM_JOB_ENDE   0x0040
//#define R_CF_DATA_ENDE  0x0020
//#define R_CF_REQ_ENDE   0x0010
#define R_MS_DATA_ENDE  0x0008
#define R_SD_DATA_ENDE  0x0004
#define R_SD_CMD_ENDE   0x0002
#define R_MMA_DATA_ENDE 0x0001
//============================================
//MMA_PRI_REG:offset 0x2
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define    0x10
//#define    0x08
#define R_JOB_RW_DIR        0x0004
#define R_MMA_W_PRIORITY    0x0002
#define R_MMA_R_PRIORITY    0x0001
//============================================
//MIU_DMA1:offset 0x3
//============================================
#define R_DMA_ADDR23   0x0080
#define R_DMA_ADDR22   0x0040
#define R_DMA_ADDR21   0x0020
#define R_DMA_ADDR20   0x0010
#define R_DMA_ADDR19   0x0008
#define R_DMA_ADDR18   0x0004
#define R_DMA_ADDR17   0x0002
#define R_DMA_ADDR16   0x0001
//============================================
//MIU_DMA0:offset 0x4
//============================================
#if (PLATFORM==OPENRISC)
#define R_DMA_ADDR15  0x8000
#define R_DMA_ADDR14  0x4000
#define R_DMA_ADDR13  0x2000
#define R_DMA_ADDR12  0x1000
#define R_DMA_ADDR11  0x0800
#define R_DMA_ADDR10  0x0400
#define R_DMA_ADDR9   0x0200
#define R_DMA_ADDR8   0x0100
#else
#define R_DMA_ADDR15  0x80
#define R_DMA_ADDR14  0x40
#define R_DMA_ADDR13  0x20
#define R_DMA_ADDR12  0x10
#define R_DMA_ADDR11  0x08
#define R_DMA_ADDR10  0x04
#define R_DMA_ADDR9   0x02
#define R_DMA_ADDR8   0x01
#endif
#define R_DMA_ADDR7   0x0080
#define R_DMA_ADDR6   0x0040
#define R_DMA_ADDR5   0x0020
#define R_DMA_ADDR4   0x0010
#define R_DMA_ADDR3   0x0008
#define R_DMA_ADDR2   0x0004
#define R_DMA_ADDR1   0x0002
#define R_DMA_ADDR0   0x0001
//============================================
//CARD_EVENT:offset 0x5
//============================================
//#define    0x80
//#define    0x40
#define    R_SD_PWR_OC_CHG 0x0020
//#define    R_XD_STS_CHG    0x0010
//#define    R_SM_STS_CHG    0x0008
//#define R_CF_STS_CHG    0x0004
#define R_MS_STS_CHG    0x0002
#define R_SD_STS_CHG    0x0001
//============================================
//CARD_INT_EN:offset 0x6
//============================================
//#define    0x80
//#define    0x40
#define    R_SD_PWR_OCDET_EN   0x0020
//#define R_XD_STS_EN 0x0010
//#define R_SM_STS_EN 0x0008
//#define R_CF_STS_EN 0x0004
#define R_MS_STS_EN         0x0002
#define R_SD_STS_EN         0x0001
//============================================
//CARD_DET:offset 0x7
//============================================
//#define    0x80
//#define    0x40
#define    R_SD_OCDET_STS  0x0020
//#define    R_XD_DET_N  0x0010
//#define    R_SM_DET_N  0x0008
//#define R_CF_DET_N  0x0004
#define R_MS_DET_N      0x0002
#define R_SD_DET_N      0x0001
//============================================
//CARD_PWR:offset 0x8
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define    0x10
//#define R_CF_PWR_PAD_OEN    0x0008
#define R_SD_PWR_PAD_OEN    0x0004
//#define R_CF_PWR_ON         0x0002
#define R_SD_PWR_ON         0x0001
#define R_MS_PWR_ON         0x0001
/*
move to venus top
//============================================
//MIE_CLK_SEL:offset 0x9
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define    0x10
#define R_MIE_CLK_SEL3 0x0008
#define R_MIE_CLK_SEL2 0x0004
#define R_MIE_CLK_SEL1 0x0002
#define R_MIE_CLK_SEL0 0x0001

#define MIE_CLK_350K   0x0
#define MIE_CLK_1500K  0x1
#define MIE_CLK_6M     0x2
#define MIE_CLK_15M    0x3
#define MIE_CLK_20M    0x4
#define MIE_CLK_25M    0x5
#define MIE_CLK_30M    0x6
#define MIE_CLK_40M    0x7
#define MIE_CLK_50M    0x8
#define MIE_CLK_60M    0x9
#define MIE_CLK_80M    0xA
*/
//============================================
//INTR_TEST:offset 0x9
//============================================
#if (PLATFORM==OPENRISC)
#define R_FORCE_SD_OC_STS_CHG   0x2000
//#define R_FORCE_XD_STS_CHG      0x1000
//#define R_FORCE_SM_STS_CHG      0x0800
//#define R_FORCE_CF_STS_CHG      0x0400
#define R_FORCE_MS_STS_CHG      0x0200
#define R_FORCE_SD_STS_CHG      0x0100
#else
#define R_FORCE_SD_OC_STS_CHG   0x20
//#define R_FORCE_XD_STS_CHG      0x10
//#define R_FORCE_SM_STS_CHG      0x08
//#define R_FORCE_CF_STS_CHG      0x04
#define R_FORCE_MS_STS_CHG      0x02
#define R_FORCE_SD_STS_CHG      0x01
#endif
#define R_FORCE_SIO_INT         0x0080
//#define R_FORCE_SM_JOB_END      0x0040
//#define R_FORCE_CF_DATA_END     0x0020
//#define R_FORCE_CF_REQ_END      0x0010
#define R_FORCE_MS_DATA_END     0x0008
#define R_FORCE_SD_DATA_END     0x0004
#define R_FORCE_SD_CMD_END      0x0002
#define R_FORCE_MMA_DATA_END    0x0001
//============================================
//MIE_PATH_CTL:offset 0xA
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define R_SM_EN         0x0010
//#define R_CF_EN         0x0008
#define R_MS_EN         0x0004
#define R_SD_EN         0x0002
#define R_MMA_ENABLE    0x0001
//============================================
//JOB_BL_CNT:offset 0xB
//============================================
#define R_JOB_BL_CNT7   0x0080
#define R_JOB_BL_CNT6   0x0040
#define R_JOB_BL_CNT5   0x0020
#define R_JOB_BL_CNT4   0x0010
#define R_JOB_BL_CNT3   0x0008
#define R_JOB_BL_CNT2   0x0004
#define R_JOB_BL_CNT1   0x0002
#define R_JOB_BL_CNT0   0x0001
//============================================
//TR_BK_CNT:offset 0xC
//============================================
#define R_TR_BK_CNT7   0x0080
#define R_TR_BK_CNT6   0x0040
#define R_TR_BK_CNT5   0x0020
#define R_TR_BK_CNT4   0x0010
#define R_TR_BK_CNT3   0x0008
#define R_TR_BK_CNT2   0x0004
#define R_TR_BK_CNT1   0x0002
#define R_TR_BK_CNT0   0x0001
//============================================
//RSP_SIZE:offset 0xD
//============================================
//#define    0x0080
#define R_CIF_RSP6   0x0040
#define R_CIF_RSP5   0x0020
#define R_CIF_RSP4   0x0010
#define R_CIF_RSP3   0x0008
#define R_CIF_RSP2   0x0004
#define R_CIF_RSP1   0x0002
#define R_CIF_RSP0   0x0001
//============================================
//CMD_SIZE:offset 0xE
//============================================
#define R_CIF_CMD6  0x0040
#define R_CIF_CMD5  0x0020
#define R_CIF_CMD4  0x0010
#define R_CIF_CMD3  0x0008
#define R_CIF_CMD2  0x0004
#define R_CIF_CMD1  0x0002
#define R_CIF_CMD0  0x0001

//============================================
//CARD_WD_CNT:offset 0xF
//============================================
#define R_CARD_WD_CNT7  0x0080
#define R_CARD_WD_CNT6  0x0040
#define R_CARD_WD_CNT5  0x0020
#define R_CARD_WD_CNT4  0x0010
#define R_CARD_WD_CNT3  0x0008
#define R_CARD_WD_CNT2  0x0004
#define R_CARD_WD_CNT1  0x0002
#define R_CARD_WD_CNT0  0x0001
//============================================
//SD_MODE:offset 0x10
//============================================
#if (PLATFORM==OPENRISC)
#define R_SDIO_RDWAIT   0x0100
#else
#define R_SDIO_RDWAIT   0x01
#endif
#define R_MMC_BUS_TEST  0x0080
#define R_SD_DATSYNC    0x0040
#define R_SD_DEST       0x0020
#define R_SD_CS_EN      0x0010
#define R_SDDRL         0x0008
#define R_SD_DAT_LINE1  0x0004
#define R_SD_DAT_LINE0  0x0002
#define R_SD_CLK_EN     0x0001
//============================================
//SD_CTL:offset 0x11
//============================================
#if (PLATFORM==OPENRISC)
#define R_SDIO_DET_ON   0x0400
#define R_SDIO_INT_MOD1 0x0200
#define R_SDIO_INT_MOD0 0x0100
#else
#define R_SDIO_DET_ON   0x04
#define R_SDIO_INT_MOD1 0x02
#define R_SDIO_INT_MOD0 0x01
#endif
//#define    0x0080
//#define    0x0040
//#define    0x0020
#define R_SD_DTRX_DIR   0x0010
#define R_SD_DTRX_EN    0x0008
#define R_SD_CMD_EN     0x0004
#define R_SD_RSP_EN     0x0002
#define R_SD_RSPR2_EN   0x0001
//============================================
//SD_STS:offset 0x12
//============================================
#if (PLATFORM==OPENRISC)
#define R_SD_DAT7           0x8000
#define R_SD_DAT6           0x4000
#define R_SD_DAT5           0x2000
#define R_SD_DAT4           0x1000
#define R_SD_DAT3           0x0800
#define R_SD_DAT2           0x0400
#define R_SD_DAT1           0x0200
#define R_SD_DAT0           0x0100
#else
#define R_SD_DAT7           0x80
#define R_SD_DAT6           0x40
#define R_SD_DAT5           0x20
#define R_SD_DAT4           0x10
#define R_SD_DAT3           0x08
#define R_SD_DAT2           0x04
#define R_SD_DAT1           0x02
#define R_SD_DAT0           0x01
#endif

#define R_SD_WR_PRO_N       0x0020
#define R_SD_CMDRSP_CERR    0x0010
#define R_SD_CMD_NORSP      0x0008
#define R_SD_DAT_STSNEG     0x0004
#define R_SD_DAT_STSERR     0x0002
#define R_SD_DAT_CERR       0x0001
//============================================
//MS_MODE:offset 0x13
//============================================
#if (PLATFORM==OPENRISC)
//#define R_BS_DLY3      0x8000
//#define       0x4000
//#define       0x2000
//#define       0x1000
#define R_TPC3          0x0800
#define R_TPC2          0x0400
#define R_TPC1          0x0200
#define R_TPC0          0x0100
#else
//#define R_BS_DLY3      0x80
//#define       0x40
//#define       0x20
//#define       0x10
#define R_TPC3          0x08
#define R_TPC2          0x04
#define R_TPC1          0x02
#define R_TPC0          0x01
#endif
#define R_BS_DLY2       0x0080
#define R_BS_DLY1       0x0040
#define R_BS_DLY0       0x0020
#define R_DAT_DLY2      0x0010
#define R_DAT_DLY1      0x0008
#define R_DAT_DLY0      0x0004
#define R_MS_DAT_LINE1  0x0002
#define R_MS_DAT_LINE0  0x0001
//============================================
//MS_CTL:offset 0x14
//============================================
//#define       0x0100
//#define      0x0080
//#define    0x0040
//#define    0x0020
#define R_MS_DEST       0x0010
#define R_MS_BURST      0x0008
#define R_MS_BUS_DIR    0x0004
#define R_MS_DTRX_EN    0x0002
#define R_MS_REGTRX_EN  0x0001
//============================================
//MS_STS:offset 0x15
//============================================
//#define    0x0080
//#define    0x0040
#define R_MS_CRCERR    0x0020
#define R_MS_TOUT      0x0010
#define R_DAT3         0x0008
#define R_DAT2         0x0004
#define R_DAT1         0x0002
#define R_DAT0         0x0001
/*
//============================================
//CF_INF_CTL1:offset 0x16
//============================================
//#define   0x8000
//#define   0x4000
//#define   0x2000
//#define   0x1000
//#define   0x0800
//#define   0x0400
//#define   0x0200
//#define   0x0100
//#define   0x0080
//#define   0x0040
//#define   0x0020
#define R_CF_IORDY_OEN  0x0010
#define R_CF_BST_A2     0x0008
#define R_CF_BST_A1     0x0004
#define R_CF_BST_A0     0x0002
#define R_CFBUS_TYPE    0x0001

//============================================
//CF_INF_CTL2:offset 0x17
//============================================
//#define       0x8000
//#define       0x4000
//#define       0x2000
//#define       0x1000
//#define       0x0800
//#define       0x0400
//#define       0x0200
//#define       0x0100
#define R_CF_IORDY  0x0080
#define R_CF_INTRQ  0x0040
#define R_CF_RSTZ   0x0020
#define R_CF_A2     0x0010
#define R_CF_A1     0x0008
#define R_CF_A0     0x0004
#define R_CF_CS1    0x0002
#define R_CF_CS0    0x0001

//============================================
//CF_BUS:offset 0x18
//============================================
#define R_CF_D15 0x8000
#define R_CF_D14 0x4000
#define R_CF_D13 0x2000
#define R_CF_D12 0x1000
#define R_CF_D11 0x0800
#define R_CF_D10 0x0400
#define R_CF_D9  0x0200
#define R_CF_D8  0x0100
#define R_CF_D7  0x0080
#define R_CF_D6  0x0040
#define R_CF_D5  0x0020
#define R_CF_D4  0x0010
#define R_CF_D3  0x0008
#define R_CF_D2  0x0004
#define R_CF_D1  0x0002
#define R_CF_D0  0x0001
//============================================
//CF_STB_SET:offset 0x19
//============================================
#define CF_STBH3 0x0080
#define CF_STBH2 0x0040
#define CF_STBH1 0x0020
#define CF_STBH0 0x0010
#define CF_STBL3 0x0008
#define CF_STBL2 0x0004
#define CF_STBL1 0x0002
#define CF_STBL0 0x0001
//============================================
//CF_CTL:offset 0x1A
//============================================
//#define  0x0080
#define R_CF_BURST_ERR  0x0040
#define R_CF_IORDY_DIS  0x0020
#define R_CF_BURST      0x0010
#define R_CF_DEST       0x0008
#define R_CF_BUS_DIR    0x0004
#define R_CF_DTRX_EN    0x0002
#define R_CF_REG_EN     0x0001
//============================================
//CIF_FIFO_CTL:offset 0x25
//============================================
#define R_CIFD_RD_REQ   0x02
#define R_CIFC_RD_REQ   0x01

//============================================
//SM_INF_CTL:offset 0x26
//============================================
#define R_SM_ALE    0x10
#define R_SM_CEZ    0x08
#define R_SM_WPZ    0x04
#define R_SM_WPDZ   0x02
#define R_SM_RBZ    0x01

//============================================
//SM_ADR_REQ:offset 0x27
//============================================
#define R_SM_REQ_A7 0x80
#define R_SM_REQ_A6 0x40
#define R_SM_REQ_A5 0x20
#define R_SM_REQ_A4 0x10
#define R_SM_REQ_A3 0x08
#define R_SM_REQ_A2 0x04
#define R_SM_REQ_A1 0x02
#define R_SM_REQ_A0 0x01

//============================================
//SM_CMD_REQ:offset 0x28
//============================================
#define R_SM_REQ_D7 0x80
#define R_SM_REQ_D6 0x40
#define R_SM_REQ_D5 0x20
#define R_SM_REQ_D4 0x10
#define R_SM_REQ_D3 0x08
#define R_SM_REQ_D2 0x04
#define R_SM_REQ_D1 0x02
#define R_SM_REQ_D0 0x01

//============================================
//SM_STB_SET:offset 0x29
//============================================
#define SM_STBH3 0x0080
#define SM_STBH2 0x0040
#define SM_STBH1 0x0020
#define SM_STBH0 0x0010
#define SM_STBL3 0x0008
#define SM_STBL2 0x0004
#define SM_STBL1 0x0002
#define SM_STBL0 0x0001

//============================================
//SM_MODE:offset 0x2A
//============================================
//#define  0x0080
//#define  0x0040
//#define  0x0020
//#define  0x0010
//#define  0x0008
#define R_SM_HI_SECTOR  0x0004
#define R_SM_ECC_FUN    0x0002
#define R_SM_PGLEN      0x0001

//============================================
//SM_CTL:offset 0x2B
//============================================
//#define  0x0080
//#define  0x0040
//#define  0x0020
#define R_SM_BURST      0x0010
#define R_SM_DEST       0x0008
#define R_SM_BUS_DIR    0x0004
#define R_SM_DTRX_EN    0x0002
#define R_SM_REG_EN     0x0001

//============================================
//SM_STS:offset 0x2C
//============================================
//#define  0x0080
//#define  0x0040
//#define  0x0020
//#define  0x0010
//#define  0x0008
#define R_SM_HALF_PAGE_END  0x0004
#define R_SM_ECC_RCV_FAIL   0x0002
#define R_SM_ECC_RCV_ACT    0x0001


*/
//============================================
//TEST_MODE:offset 0x30
//============================================
#if (PLATFORM==OPENRISC)
//#define  0x8000
//#define  0x4000
//#define  0x2000
#define R_FCIE_SOFT_RST 0x1000
#define R_SDMS_COLBUS   0x0800
#define R_DEBUG_MODE2   0x0400
#define R_DEBUG_MODE1   0x0200
#define R_DEBUG_MODE0   0x0100
#else
//#define  0x80
//#define  0x40
//#define  0x20
#define R_FCIE_SOFT_RST 0x10
#define R_SDMS_COLBUS   0x08
#define R_DEBUG_MODE2   0x04
#define R_DEBUG_MODE1   0x02
#define R_DEBUG_MODE0   0x01
#endif
//#define  0x0080
//#define  0x0040
//#define  0x0020
//#define  0x0010
#define R_CIFD_BISTFAIL 0x0008
#define R_CIFC_BISTFAIL 0x0004
#define R_DBFB_BISTFAIL 0x0002
#define R_DBFA_BISTFAIL 0x0001
//===================================================================

//#define REG0008         (0x08<<OffShift)
/*
//============================================
//REG0008:offset 0x08
//============================================
#define R_SEL_XTAL_CLK  0x2000
#define R_INVERT_CLOCK  0x0100
#define R_DISABLE_CLOCK 0x0080

#define MIE_CLK_MASK    0x1E00
#define MIE_CLK_350K   (0x0<<9)
#define MIE_CLK_1500K  (0x1<<9)
#define MIE_CLK_6M     (0x2<<9)
#define MIE_CLK_15M    (0x3<<9)
#define MIE_CLK_20M    (0x4<<9)
#define MIE_CLK_25M    (0x5<<9)
#define MIE_CLK_30M    (0x6<<9)
#define MIE_CLK_40M    (0x7<<9)
#define MIE_CLK_50M    (0x8<<9)
#define MIE_CLK_60M    (0x9<<9)
#define MIE_CLK_80M    (0xA<<9)
*/

// fcie register constant
//============================================
//MIE_EVENT:offset 0x0
//============================================
#define R_SDIO_INT      0x0080
//#define R_SM_JOB_END    0x0040
//#define R_CF_DATA_END   0x0020
//#define R_CF_CMD_END    0x0010
#define R_MS_DATA_END   0x0008
#define R_SD_DATA_END   0x0004
#define R_SD_CMD_END    0x0002
#define R_MMA_DATA_END  0x0001
//============================================
//MIE_INT_EN:offset 0x1
//============================================
#define R_SDIO_INT_EN   0x0080
//#define R_SM_JOB_ENDE   0x0040
//#define R_CF_DATA_ENDE  0x0020
//#define R_CF_REQ_ENDE   0x0010
#define R_MS_DATA_ENDE  0x0008
#define R_SD_DATA_ENDE  0x0004
#define R_SD_CMD_ENDE   0x0002
#define R_MMA_DATA_ENDE 0x0001
//============================================
//MMA_PRI_REG:offset 0x2
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define    0x10
//#define    0x08
#define R_JOB_RW_DIR        0x0004
#define R_MMA_W_PRIORITY    0x0002
#define R_MMA_R_PRIORITY    0x0001
//============================================
//MIU_DMA1:offset 0x3
//============================================
#define R_DMA_ADDR23   0x0080
#define R_DMA_ADDR22   0x0040
#define R_DMA_ADDR21   0x0020
#define R_DMA_ADDR20   0x0010
#define R_DMA_ADDR19   0x0008
#define R_DMA_ADDR18   0x0004
#define R_DMA_ADDR17   0x0002
#define R_DMA_ADDR16   0x0001
//============================================
//MIU_DMA0:offset 0x4
//============================================
#if (PLATFORM==OPENRISC)
#define R_DMA_ADDR15  0x8000
#define R_DMA_ADDR14  0x4000
#define R_DMA_ADDR13  0x2000
#define R_DMA_ADDR12  0x1000
#define R_DMA_ADDR11  0x0800
#define R_DMA_ADDR10  0x0400
#define R_DMA_ADDR9   0x0200
#define R_DMA_ADDR8   0x0100
#else
#define R_DMA_ADDR15  0x80
#define R_DMA_ADDR14  0x40
#define R_DMA_ADDR13  0x20
#define R_DMA_ADDR12  0x10
#define R_DMA_ADDR11  0x08
#define R_DMA_ADDR10  0x04
#define R_DMA_ADDR9   0x02
#define R_DMA_ADDR8   0x01
#endif
#define R_DMA_ADDR7   0x0080
#define R_DMA_ADDR6   0x0040
#define R_DMA_ADDR5   0x0020
#define R_DMA_ADDR4   0x0010
#define R_DMA_ADDR3   0x0008
#define R_DMA_ADDR2   0x0004
#define R_DMA_ADDR1   0x0002
#define R_DMA_ADDR0   0x0001
//============================================
//CARD_EVENT:offset 0x5
//============================================
//#define    0x80
//#define    0x40
#define    R_SD_PWR_OC_CHG 0x0020
//#define    R_XD_STS_CHG    0x0010
//#define    R_SM_STS_CHG    0x0008
//#define R_CF_STS_CHG    0x0004
#define R_MS_STS_CHG    0x0002
#define R_SD_STS_CHG    0x0001
//============================================
//CARD_INT_EN:offset 0x6
//============================================
//#define    0x80
//#define    0x40
#define    R_SD_PWR_OCDET_EN   0x0020
//#define R_XD_STS_EN 0x0010
//#define R_SM_STS_EN 0x0008
//#define R_CF_STS_EN 0x0004
#define R_MS_STS_EN         0x0002
#define R_SD_STS_EN         0x0001
//============================================
//CARD_DET:offset 0x7
//============================================
//#define    0x80
//#define    0x40
#define    R_SD_OCDET_STS  0x0020
//#define    R_XD_DET_N  0x0010
//#define    R_SM_DET_N  0x0008
//#define R_CF_DET_N  0x0004
#define R_MS_DET_N      0x0002
#define R_SD_DET_N      0x0001
//============================================
//CARD_PWR:offset 0x8
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define    0x10
//#define R_CF_PWR_PAD_OEN    0x0008
#define R_SD_PWR_PAD_OEN    0x0004
//#define R_CF_PWR_ON         0x0002
#define R_SD_PWR_ON         0x0001
#define R_MS_PWR_ON         0x0001
/*
move to venus top
//============================================
//MIE_CLK_SEL:offset 0x9
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define    0x10
#define R_MIE_CLK_SEL3 0x0008
#define R_MIE_CLK_SEL2 0x0004
#define R_MIE_CLK_SEL1 0x0002
#define R_MIE_CLK_SEL0 0x0001

#define MIE_CLK_350K   0x0
#define MIE_CLK_1500K  0x1
#define MIE_CLK_6M     0x2
#define MIE_CLK_15M    0x3
#define MIE_CLK_20M    0x4
#define MIE_CLK_25M    0x5
#define MIE_CLK_30M    0x6
#define MIE_CLK_40M    0x7
#define MIE_CLK_50M    0x8
#define MIE_CLK_60M    0x9
#define MIE_CLK_80M    0xA
*/
//============================================
//INTR_TEST:offset 0x9
//============================================
#if (PLATFORM==OPENRISC)
#define R_FORCE_SD_OC_STS_CHG   0x2000
//#define R_FORCE_XD_STS_CHG      0x1000
//#define R_FORCE_SM_STS_CHG      0x0800
//#define R_FORCE_CF_STS_CHG      0x0400
#define R_FORCE_MS_STS_CHG      0x0200
#define R_FORCE_SD_STS_CHG      0x0100
#else
#define R_FORCE_SD_OC_STS_CHG   0x20
//#define R_FORCE_XD_STS_CHG      0x10
//#define R_FORCE_SM_STS_CHG      0x08
//#define R_FORCE_CF_STS_CHG      0x04
#define R_FORCE_MS_STS_CHG      0x02
#define R_FORCE_SD_STS_CHG      0x01
#endif
#define R_FORCE_SIO_INT         0x0080
//#define R_FORCE_SM_JOB_END      0x0040
//#define R_FORCE_CF_DATA_END     0x0020
//#define R_FORCE_CF_REQ_END      0x0010
#define R_FORCE_MS_DATA_END     0x0008
#define R_FORCE_SD_DATA_END     0x0004
#define R_FORCE_SD_CMD_END      0x0002
#define R_FORCE_MMA_DATA_END    0x0001
//============================================
//MIE_PATH_CTL:offset 0xA
//============================================
//#define    0x80
//#define    0x40
//#define    0x20
//#define R_SM_EN         0x0010
//#define R_CF_EN         0x0008
#define R_MS_EN         0x0004
#define R_SD_EN         0x0002
#define R_MMA_ENABLE    0x0001
//============================================
//JOB_BL_CNT:offset 0xB
//============================================
#define R_JOB_BL_CNT7   0x0080
#define R_JOB_BL_CNT6   0x0040
#define R_JOB_BL_CNT5   0x0020
#define R_JOB_BL_CNT4   0x0010
#define R_JOB_BL_CNT3   0x0008
#define R_JOB_BL_CNT2   0x0004
#define R_JOB_BL_CNT1   0x0002
#define R_JOB_BL_CNT0   0x0001
//============================================
//TR_BK_CNT:offset 0xC
//============================================
#define R_TR_BK_CNT7   0x0080
#define R_TR_BK_CNT6   0x0040
#define R_TR_BK_CNT5   0x0020
#define R_TR_BK_CNT4   0x0010
#define R_TR_BK_CNT3   0x0008
#define R_TR_BK_CNT2   0x0004
#define R_TR_BK_CNT1   0x0002
#define R_TR_BK_CNT0   0x0001
//============================================
//RSP_SIZE:offset 0xD
//============================================
//#define    0x0080
#define R_CIF_RSP6   0x0040
#define R_CIF_RSP5   0x0020
#define R_CIF_RSP4   0x0010
#define R_CIF_RSP3   0x0008
#define R_CIF_RSP2   0x0004
#define R_CIF_RSP1   0x0002
#define R_CIF_RSP0   0x0001
//============================================
//CMD_SIZE:offset 0xE
//============================================
#define R_CIF_CMD6  0x0040
#define R_CIF_CMD5  0x0020
#define R_CIF_CMD4  0x0010
#define R_CIF_CMD3  0x0008
#define R_CIF_CMD2  0x0004
#define R_CIF_CMD1  0x0002
#define R_CIF_CMD0  0x0001

//============================================
//CARD_WD_CNT:offset 0xF
//============================================
#define R_CARD_WD_CNT7  0x0080
#define R_CARD_WD_CNT6  0x0040
#define R_CARD_WD_CNT5  0x0020
#define R_CARD_WD_CNT4  0x0010
#define R_CARD_WD_CNT3  0x0008
#define R_CARD_WD_CNT2  0x0004
#define R_CARD_WD_CNT1  0x0002
#define R_CARD_WD_CNT0  0x0001
//============================================
//SD_MODE:offset 0x10
//============================================
#if (PLATFORM==OPENRISC)
#define R_SDIO_RDWAIT   0x0100
#else
#define R_SDIO_RDWAIT   0x01
#endif
#define R_MMC_BUS_TEST  0x0080
#define R_SD_DATSYNC    0x0040
#define R_SD_DEST       0x0020
#define R_SD_CS_EN      0x0010
#define R_SDDRL         0x0008
#define R_SD_DAT_LINE1  0x0004
#define R_SD_DAT_LINE0  0x0002
#define R_SD_CLK_EN     0x0001
//============================================
//SD_CTL:offset 0x11
//============================================
#if (PLATFORM==OPENRISC)
#define R_SDIO_DET_ON   0x0400
#define R_SDIO_INT_MOD1 0x0200
#define R_SDIO_INT_MOD0 0x0100
#else
#define R_SDIO_DET_ON   0x04
#define R_SDIO_INT_MOD1 0x02
#define R_SDIO_INT_MOD0 0x01
#endif
//#define    0x0080
//#define    0x0040
//#define    0x0020
#define R_SD_DTRX_DIR   0x0010
#define R_SD_DTRX_EN    0x0008
#define R_SD_CMD_EN     0x0004
#define R_SD_RSP_EN     0x0002
#define R_SD_RSPR2_EN   0x0001
//============================================
//SD_STS:offset 0x12
//============================================
#if (PLATFORM==OPENRISC)
#define R_SD_DAT7           0x8000
#define R_SD_DAT6           0x4000
#define R_SD_DAT5           0x2000
#define R_SD_DAT4           0x1000
#define R_SD_DAT3           0x0800
#define R_SD_DAT2           0x0400
#define R_SD_DAT1           0x0200
#define R_SD_DAT0           0x0100
#else
#define R_SD_DAT7           0x80
#define R_SD_DAT6           0x40
#define R_SD_DAT5           0x20
#define R_SD_DAT4           0x10
#define R_SD_DAT3           0x08
#define R_SD_DAT2           0x04
#define R_SD_DAT1           0x02
#define R_SD_DAT0           0x01
#endif

#define R_SD_WR_PRO_N       0x0020
#define R_SD_CMDRSP_CERR    0x0010
#define R_SD_CMD_NORSP      0x0008
#define R_SD_DAT_STSNEG     0x0004
#define R_SD_DAT_STSERR     0x0002
#define R_SD_DAT_CERR       0x0001
//============================================
//MS_MODE:offset 0x13
//============================================
#if (PLATFORM==OPENRISC)
//#define R_BS_DLY3      0x8000
//#define       0x4000
//#define       0x2000
//#define       0x1000
#define R_TPC3          0x0800
#define R_TPC2          0x0400
#define R_TPC1          0x0200
#define R_TPC0          0x0100
#else
//#define R_BS_DLY3      0x80
//#define       0x40
//#define       0x20
//#define       0x10
#define R_TPC3          0x08
#define R_TPC2          0x04
#define R_TPC1          0x02
#define R_TPC0          0x01
#endif
#define R_BS_DLY2       0x0080
#define R_BS_DLY1       0x0040
#define R_BS_DLY0       0x0020
#define R_DAT_DLY2      0x0010
#define R_DAT_DLY1      0x0008
#define R_DAT_DLY0      0x0004
#define R_MS_DAT_LINE1  0x0002
#define R_MS_DAT_LINE0  0x0001
//============================================
//MS_CTL:offset 0x14
//============================================
//#define       0x0100
//#define      0x0080
//#define    0x0040
//#define    0x0020
#define R_MS_DEST       0x0010
#define R_MS_BURST      0x0008
#define R_MS_BUS_DIR    0x0004
#define R_MS_DTRX_EN    0x0002
#define R_MS_REGTRX_EN  0x0001
//============================================
//MS_STS:offset 0x15
//============================================
//#define    0x0080
//#define    0x0040
#define R_MS_CRCERR    0x0020
#define R_MS_TOUT      0x0010
#define R_DAT3         0x0008
#define R_DAT2         0x0004
#define R_DAT1         0x0002
#define R_DAT0         0x0001
/*
//============================================
//CF_INF_CTL1:offset 0x16
//============================================
//#define   0x8000
//#define   0x4000
//#define   0x2000
//#define   0x1000
//#define   0x0800
//#define   0x0400
//#define   0x0200
//#define   0x0100
//#define   0x0080
//#define   0x0040
//#define   0x0020
#define R_CF_IORDY_OEN  0x0010
#define R_CF_BST_A2     0x0008
#define R_CF_BST_A1     0x0004
#define R_CF_BST_A0     0x0002
#define R_CFBUS_TYPE    0x0001

//============================================
//CF_INF_CTL2:offset 0x17
//============================================
//#define       0x8000
//#define       0x4000
//#define       0x2000
//#define       0x1000
//#define       0x0800
//#define       0x0400
//#define       0x0200
//#define       0x0100
#define R_CF_IORDY  0x0080
#define R_CF_INTRQ  0x0040
#define R_CF_RSTZ   0x0020
#define R_CF_A2     0x0010
#define R_CF_A1     0x0008
#define R_CF_A0     0x0004
#define R_CF_CS1    0x0002
#define R_CF_CS0    0x0001

//============================================
//CF_BUS:offset 0x18
//============================================
#define R_CF_D15 0x8000
#define R_CF_D14 0x4000
#define R_CF_D13 0x2000
#define R_CF_D12 0x1000
#define R_CF_D11 0x0800
#define R_CF_D10 0x0400
#define R_CF_D9  0x0200
#define R_CF_D8  0x0100
#define R_CF_D7  0x0080
#define R_CF_D6  0x0040
#define R_CF_D5  0x0020
#define R_CF_D4  0x0010
#define R_CF_D3  0x0008
#define R_CF_D2  0x0004
#define R_CF_D1  0x0002
#define R_CF_D0  0x0001
//============================================
//CF_STB_SET:offset 0x19
//============================================
#define CF_STBH3 0x0080
#define CF_STBH2 0x0040
#define CF_STBH1 0x0020
#define CF_STBH0 0x0010
#define CF_STBL3 0x0008
#define CF_STBL2 0x0004
#define CF_STBL1 0x0002
#define CF_STBL0 0x0001
//============================================
//CF_CTL:offset 0x1A
//============================================
//#define  0x0080
#define R_CF_BURST_ERR  0x0040
#define R_CF_IORDY_DIS  0x0020
#define R_CF_BURST      0x0010
#define R_CF_DEST       0x0008
#define R_CF_BUS_DIR    0x0004
#define R_CF_DTRX_EN    0x0002
#define R_CF_REG_EN     0x0001
//============================================
//CIF_FIFO_CTL:offset 0x25
//============================================
#define R_CIFD_RD_REQ   0x02
#define R_CIFC_RD_REQ   0x01

//============================================
//SM_INF_CTL:offset 0x26
//============================================
#define R_SM_ALE    0x10
#define R_SM_CEZ    0x08
#define R_SM_WPZ    0x04
#define R_SM_WPDZ   0x02
#define R_SM_RBZ    0x01

//============================================
//SM_ADR_REQ:offset 0x27
//============================================
#define R_SM_REQ_A7 0x80
#define R_SM_REQ_A6 0x40
#define R_SM_REQ_A5 0x20
#define R_SM_REQ_A4 0x10
#define R_SM_REQ_A3 0x08
#define R_SM_REQ_A2 0x04
#define R_SM_REQ_A1 0x02
#define R_SM_REQ_A0 0x01

//============================================
//SM_CMD_REQ:offset 0x28
//============================================
#define R_SM_REQ_D7 0x80
#define R_SM_REQ_D6 0x40
#define R_SM_REQ_D5 0x20
#define R_SM_REQ_D4 0x10
#define R_SM_REQ_D3 0x08
#define R_SM_REQ_D2 0x04
#define R_SM_REQ_D1 0x02
#define R_SM_REQ_D0 0x01

//============================================
//SM_STB_SET:offset 0x29
//============================================
#define SM_STBH3 0x0080
#define SM_STBH2 0x0040
#define SM_STBH1 0x0020
#define SM_STBH0 0x0010
#define SM_STBL3 0x0008
#define SM_STBL2 0x0004
#define SM_STBL1 0x0002
#define SM_STBL0 0x0001

//============================================
//SM_MODE:offset 0x2A
//============================================
//#define  0x0080
//#define  0x0040
//#define  0x0020
//#define  0x0010
//#define  0x0008
#define R_SM_HI_SECTOR  0x0004
#define R_SM_ECC_FUN    0x0002
#define R_SM_PGLEN      0x0001

//============================================
//SM_CTL:offset 0x2B
//============================================
//#define  0x0080
//#define  0x0040
//#define  0x0020
#define R_SM_BURST      0x0010
#define R_SM_DEST       0x0008
#define R_SM_BUS_DIR    0x0004
#define R_SM_DTRX_EN    0x0002
#define R_SM_REG_EN     0x0001

//============================================
//SM_STS:offset 0x2C
//============================================
//#define  0x0080
//#define  0x0040
//#define  0x0020
//#define  0x0010
//#define  0x0008
#define R_SM_HALF_PAGE_END  0x0004
#define R_SM_ECC_RCV_FAIL   0x0002
#define R_SM_ECC_RCV_ACT    0x0001


*/
//============================================
//TEST_MODE:offset 0x30
//============================================
#if (PLATFORM==OPENRISC)
//#define  0x8000
//#define  0x4000
//#define  0x2000
#define R_FCIE_SOFT_RST 0x1000
#define R_SDMS_COLBUS   0x0800
#define R_DEBUG_MODE2   0x0400
#define R_DEBUG_MODE1   0x0200
#define R_DEBUG_MODE0   0x0100
#else
//#define  0x80
//#define  0x40
//#define  0x20
#define R_FCIE_SOFT_RST 0x10
#define R_SDMS_COLBUS   0x08
#define R_DEBUG_MODE2   0x04
#define R_DEBUG_MODE1   0x02
#define R_DEBUG_MODE0   0x01
#endif
//#define  0x0080
//#define  0x0040
//#define  0x0020
//#define  0x0010
#define R_CIFD_BISTFAIL 0x0008
#define R_CIFC_BISTFAIL 0x0004
#define R_DBFB_BISTFAIL 0x0002
#define R_DBFA_BISTFAIL 0x0001
//===================================================================

//--------------------------------------------------------------------
//    MACROS
//--------------------------------------------------------------------

#define SDRemoved() (REG(CARD_DET) & R_SD_DET_N)
#define MSRemoved() (REG(CARD_DET) & R_MS_DET_N)
#define MDrv_CardPowerOff(x)    REG(CARD_PWR) = 0xFFFFFFF3
#define MDrv_CardPowerOn(x)     REG(CARD_PWR) = ~(x)


/*enumeration ===================================================================================*/
//====================================================
//    JOB_ID constants for Read direction
//====================================================
// CardInfo
#define _2KLUT            0x80
#define _LUTWP            0x40
#define _EJECT            0x20  // Eject (wait for disconnect)
#define _RPT_MEDIA_CHGED  0x10  // First time Attached
#define _MEDIUM_FAILED    0x08
#define _WP               0x04  // Write Protect
#define _READY            0x02  // Ready
#define _INIT_CARD        0x01  // Initiate card

// CREADER_EVENT
#define MMA_END_EVENT           0x000001
#define SD_CMD_END_EVENT        0x000002
#define SD_DATA_END_EVENT       0x000004
#define MS_DATA_END_EVENT       0x000008
#define CF_REQ_END_EVENT        0x000010
#define CF_DATA_END_EVENT       0x000020

#define SD_STSCHG_EVENT         (R_SD_STS_EN<<8)
#define MS_STSCHG_EVENT         (R_MS_STS_EN<<8)
//#define CF_STSCHG_EVENT         (R_CF_STS_EN<<8)
//#define SM_STSCHG_EVENT         (R_SM_STS_EN<<8)
//#define XD_STSCHG_EVENT         (R_XD_STS_EN<<8)

#define CR_HW_EVENT             0x010000
#define CR_RW_REQ_EVENT         0x020000
#define CR_RW_COMPLETE_EVENT    0x040000

//    swFlag
#define _ACCESS_CONTROL     0x80
#define _PRE_SET_WRITE      0x20
#define _PRE_SET_READ       0x10
#define _WAIT_INT               0x02
#define _MS_PRO_SetBusAgain 0x04
#define _MS_PRO_1bit                0x08


// DMA aligement
#define DMA_ALIGNMENT       0x08


// temp setting
#define CKG_FCIE_SHIFT                  (0)
#define FCIE_CLOCK_SEL_SHIFT            (CKG_FCIE_SHIFT+2)
#define FCIE_CLOCK_SEL_335K             (0<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_1_3M             (1<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_5_3M             (2<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_13_5M            (3<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_18M              (4<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_21_5M            (5<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_27M              (6<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_36M              (7<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_43M              (8<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_54M              (9<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_72M              (10<<FCIE_CLOCK_SEL_SHIFT)


#define    RW_OK      0x00
#define    RW_CARDCHG 0x01
#define    RW_FAIL    0x02

enum
{
    CARD_CHG_STS_OK = 0,
    CARD_CHG_STS_REMOVE,
    CARD_CHG_STS_MEDIAFAIL
};
/// Define Read/write direction
typedef enum
{
    /// Read from memory card
    CARD_READ = 0,
    /// write to memory card
    CARD_WRITE = 1
}RW_DIR;


enum
{
    ID_READ_SECTOR=0,
    ID_ISCARDREADY,
    ID_GET_CARD_CAPACITY,

};
//====================================================
//    JOB_ID constants for write direction
//====================================================

enum
{
    ID_WRITE_SECTOR=0
    //ID_ISCARDREADY,
    //ID_GET_CARD_CAPACITY,

};
//====================================================
//    JOB_STS constants
//====================================================
enum
{
    STS_SUCCESS = 0,
    STS_CARDCHG,
    STS_FAIL,
    STS_NOMEDIA,
    STS_MEDIUM_FAILED,
    STS_WRITE_PROTECT,
    STS_ADDR_ERROR,
    STS_MMA_ACTIVE,            // DMA active
    STS_CARD_NOTREADY
};

//====================================================
//    CardDetect constants
//====================================================
enum
{
    DETECT_NOCARD = 0,
    DETECT_NOCARD_CARDCHG,
    DETECT_CARDEXIST,
    DETECT_CARDEXIST_CARDCHG,
};


/// Define memory card type
typedef enum ECARDTYPE
{
    /// unknow memory card
    _UNKNOW = 0,
    /// MMC card
    _MMC,
    /// SD card
    _SD,
    /// SmartMedia card
    _SM,
    /// xD-Picture card
    _XD,
    /// MemoryStick card
    _MS,
    /// Memory Stick Pro card
    _MSPro,
    /// Compact Flash card
    _CF
} CARDTYPE;

/// Declare Card information
typedef struct CARDINFO_STRUCT
{
    /// Memory card ready or not
    BOOLEAN Ready;    // Card Ready?
    /// Card type
    CARDTYPE eCardType;
    /// Card capacity
    U32 Capacity;    // sector count
    /// Sector size
    U32 BlkSz;    // sector size
}CARDINFO;


/// Define IO function status
typedef enum
{
    /// Success
    RW_STS_OK = 0,
    /// No memory card
    RW_STS_NOMEDIA,
    /// IO error
    RW_STS_IO_ERROR,
    /// Write protect
    RW_STS_WRITE_PROTECT,
    /// Time out
    RW_STS_TIMEOUT,
    /// request card address error
    RW_STS_ADDRESS_ERROR,
    ///
    RW_STS_ECC_ERROR,
    ///
    RW_STS_PROGRAM_FAIL

}RW_STATUS;

/// Declare Card DMA information
typedef struct _DMARW
{
    /// DRAM address, must be 8 bytes aligned
    U32    DMA_ADR;
    /// sector address
    U32    LBA;
    /// sector count
    U8    LEN;
    /// use callback?
    //BOOL callback;
    /// CallBack function
    //FS_NonBlockCallback CDriver_Callback;
    /// Read/Write direction
    RW_DIR     RW;
}DMARW;

typedef struct _CDRREG
{
    U32 MIE_EVENT_MIR;
    U32 MIE_INT_EN_MIR;
    U32 CARD_EVENT_MIR;
    U32 SD_MODE_MIR;
}CDRREG;

/// Declare Card operations function point
typedef struct card_operations_struct
{
    /// memory card initial function
    U8 (*card_init)(void);
    /// memory Read/Write function
    RW_STATUS (*card_rw)(DMARW *);
}card_operations;

/// Card Reader Driver struct
typedef struct CD_INIT_STRUCT
{
    /// Memory card type
    CARDTYPE  CardType;
    /// Clock seeting for current memory card
    U32  CardClk;
    /// misc card status
    U32  CardInfo;
    /// CIS/Boot block address, SM/xD/MS only
    U32  BootBlk;
    U32  swFlag;
    /// capacity of current memory card
    U32 CardCapa;
    // Sector size of current memory card
    U32 BlkSize;
    U32 OldAddr;
    int iEventID;// OS event
    U8 rw_status;
    /// DMA information
    DMARW dmarw;
    CDRREG reg;
    /// Memory card operations function point
    struct card_operations_struct *c_op;
}CARD_DRIVER;

#if (PLATFORM==OPENRISC)
#ifdef ECOS_DISK_DRIVER
typedef struct ide_disk_info_t_ {
    cyg_uint8 port;
    cyg_uint8 chan;
} ide_disk_info_t;
#endif
#endif
/*function ======================================================================================*/
#ifdef DRV_CREADER
#define DRV_CREADER_INTERFACE
#else
#define    DRV_CREADER_INTERFACE extern
#endif

#if (PLATFORM == MCU8051) //================================================<<<
DRV_CREADER_INTERFACE void MDrv_CReader_LoadCode(void);
DRV_CREADER_INTERFACE U8 MDrv_CReader_CardDetect(void);
DRV_CREADER_INTERFACE U8 MDrv_CReader_WaitCardReady(void);
DRV_CREADER_INTERFACE U32 MDrv_CReader_ReadCapacity(void);
#endif//PLATFORM_MCU8051 //=================================================>>>

DRV_CREADER_INTERFACE U8 MDrv_CReader_Initial(void );
#if ((PLATFORM != MCU8051) && (PLATFORM != OPENRISC)) //================================================<<<
DRV_CREADER_INTERFACE U8 MDrv_CReader_Read(void *CardPtr, U32 u32StartSector, U32 u32SectorCount, U8 *pu8Buffer);
#else //<<<=================================================================>>>
DRV_CREADER_INTERFACE U8 MDrv_CReader_Read( U32 u32StartSector, U32 u32SectorCount, U32 u32BufferAddress);
#endif//PLATFORM_MCU8051 //=================================================>>>
DRV_CREADER_INTERFACE U8 MDrv_CReader_Write(U32 u32StartSector, U32 u32SectorCount, U32 u32DRAMAddr);
//DRV_CREADER_INTERFACE U8 MDrv_CReader_Erase(void *CardPtr, U32 u32StartSector, U32 u32SectorCount);

#if ((PLATFORM != MCU8051) && (PLATFORM != OPENRISC)) //================================================<<<
DRV_CREADER_INTERFACE void MDrv_CReader_ReadTest(U32 u32StartSector, U32 u32SectorCount);
#else //<<<=================================================================>>>
DRV_CREADER_INTERFACE void MDrv_CReader_ReadTest(void);
#endif//PLATFORM_MCU8051 //=================================================>>>

#if ((PLATFORM != MCU8051) && (PLATFORM != OPENRISC)) //================================================<<<
DRV_CREADER_INTERFACE void MDrv_CReader_WriteTest(U32 u32StartSector, U32 u32SectorCount);
#else //<<<=================================================================>>>
DRV_CREADER_INTERFACE void MDrv_CReader_WriteTest(void);
DRV_CREADER_INTERFACE void _CARDREADER_RW_TEST(void);
#endif//PLATFORM_MCU8051 //=================================================>>>

DRV_CREADER_INTERFACE U32 _DrvCARDREADER_CRD_SLOT_CHG(void);
DRV_CREADER_INTERFACE U8 _DrvCARDREADER_GetCMD_RSP_BUF(U8 addr);
DRV_CREADER_INTERFACE void _DrvCARDREADER_SetCMD_RSP_BUF(U8 u8addr, U8 u8value);
DRV_CREADER_INTERFACE void _DrvCARDREADER_SetFCIE_Clock(U16 Clk);
DRV_CREADER_INTERFACE U8 _DrvCARDREADER_GetCIFIFO(U16 u16addr);
DRV_CREADER_INTERFACE void _DrvCARDREADER_SetCIFIFO(U8 u8addr, U8 u8value);
DRV_CREADER_INTERFACE U32 _DrvCARDREADER_wMIEEvent(U32 ReqVal, U32 bDev, U32 u32WaitMs);
DRV_CREADER_INTERFACE void _DrvCARDREADER_SetDMA_Addr(U32 DMA_ADDR);
/*===============================================================================================*/
#if (PLATFORM==OPENRISC)
void MDrv_CARDREADER_GETCARDINFO(CARDINFO *pCARDINFO);
void MDrv_CARDREADER_TASK(U32 argc, void *argv);
RW_STATUS MDrv_CARDREADER_CARD_RW(DMARW *pDMARW);
#ifdef ECOS_DISK_DRIVER
bool CardReader_init(struct cyg_devtab_entry *tab);
Cyg_ErrNo CardReader_read(disk_channel *chan,
                                void         *buf,
                                U32    len,
                                U32    block_num);


Cyg_ErrNo CardReader_write(disk_channel *chan,
                                const void   *buf,
                                U32    len,
                                U32    block_num);

Cyg_ErrNo CardReader_get_config(disk_channel *chan,
                                        U32    key,
                                        const void   *xbuf,
                                        U32   *len);

Cyg_ErrNo CardReader_set_config(disk_channel *chan,
                                        U32    key,
                                        const void   *xbuf,
                                        U32   *len);

Cyg_ErrNo CardReader_lookup( struct cyg_devtab_entry **tab,
                                    struct cyg_devtab_entry  *sub_tab,
                                    const char               *name);
#endif
#endif // (PLATFORM==OPENRISC)

#endif    /*_DRV_CREADER_H END */

