////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DDR2_INIT_H__
#define __DDR2_INIT_H__


#include "Board.h"
#include "c_riubase.h"
#include "drvGlobal.h"

#define    _DRAM_SIZE_NO_LIMIT    0x00
#define    _DRAM_SIZE_2M          0x01
#define    _DRAM_SIZE_4M          0x02
#define    _DRAM_SIZE_8M          0x03
#define    _DRAM_SIZE_16M         0x04
#define    _DRAM_SIZE_32M         0x05
#define    _DRAM_SIZE_64M         0x06
#define    _DRAM_SIZE_128M        0x07
#define    _DRAM_SIZE_256M        0x07

#define    _DRAM_ON_BAORD         _DRAM_SIZE_NO_LIMIT

// A CMD + B DATA
#define MIU0_USE_MIU1_DATA (!CHIP_HAS_DDR_A_DATA && !CHIP_HAS_DDR_B_CMD)


//#if (DRAM_TYPE == DDR_II) && defined(DDRII_ODT)
//#define RV_ODT_0        BIT3
//#define RV_ODT_1        ((!MIU0_USE_MIU1_DATA && ENABLE_MIU_1) ? BIT3 : 0)
//#else
//#define RV_ODT_0        0
//#define RV_ODT_1        0
//#endif

//#define USE_GRP2        1   // GRP2 register that might be unsave
//#define USE_GRP2_UNSAVE 0   // reserved for future

//#define RV_TFREPERIOD   0x60

static const MS_REG_INIT MIU_ATOP_Init[]=
{   // Bank=0x1005nn //offset , data
#if 0
#if ( MIU_INTERFACE ==  DDR2_INTERFACE_QFP )
   _RV32_2( ( RIUBASE_MIU_ATOP + 0x00 ) , 0x0000),   //QFP
#else
   _RV32_2( ( RIUBASE_MIU_ATOP + 0x00 ) , 0x0001),   //ddr2_BGA or DDR3_BGA
#endif
_RV32_2( ( RIUBASE_MIU_ATOP + 0x08 ) , 0xFFFF),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x0A ) , 0x0007),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x0C ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x10 ) , 0x3f00),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x12 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x20 ) , 0x0020),
// By BD_MST087E_D01A temp solution, should use general setting and be removed later
#if (MS_BOARD_TYPE_SEL == BD_MST087E_D01A)
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x22 ) , 0x0015),
#else
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x22 ) , 0x001a),
#endif
_RV32_2( ( RIUBASE_MIU_ATOP + 0x24 ) , 0x0000),
#if (MS_BOARD_TYPE_SEL == BD_MST087F_D01A)
_RV32_2( ( RIUBASE_MIU_ATOP + 0x28 ) , 0x8017),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x2A ) , 0x02B7),
#else
_RV32_2( ( RIUBASE_MIU_ATOP + 0x28 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x2A ) , 0x0000),
#endif
_RV32_2( ( RIUBASE_MIU_ATOP + 0x2c ) , 0x0000),
// By BD_MST087E_D01A temp solution, should use general setting and be removed later
#if (MS_BOARD_TYPE_SEL == BD_MST087E_D01A)
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x30 ) , 0x0000),
#endif
_RV32_2( ( RIUBASE_MIU_ATOP + 0x40 ) , 0x3333),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x42 ) , 0x3033),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x44 ) , 0x3333),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x46 ) , 0x0330),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x48 ) , 0x3333),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x4a ) , 0x3033),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x4c ) , 0x3333),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x4e ) , 0x0330),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x50 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x52 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x54 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x60 ) , 0x2338),  //need refine when chip back
// By BD_MST087E_D01A temp solution, should use general setting and be removed later
#if (MS_BOARD_TYPE_SEL == BD_MST087E_D01A)
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x62 ) , 0x387f),
#else
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x62 ) , 0x387f),  //0x007f --> 0x307f
#endif
_RV32_2( ( RIUBASE_MIU_ATOP + 0x64 ) , 0xf200),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x66 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x68 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x70 ) , 0x0000),      //1.3G:0x0000, 800M/1.066G:0x0300
#if ( MIU_INTERFACE ==  DDR2_INTERFACE_BGA )
    // By BD_MST087E_D01A temp solution, should use general setting and be removed later
    #if (MS_BOARD_TYPE_SEL == BD_MST087E_D01A)
        _RV32_2( ( RIUBASE_MIU_ATOP + 0x72 ) , 0x3603),  //0x0005 -->0x0008  in DDR2 setting
    #else
        _RV32_2( ( RIUBASE_MIU_ATOP + 0x72 ) , 0x0003),  //0x0005 -->0x0008  in DDR2 setting
    #endif
#else
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x72 ) , 0x3803),  //0x0005 -->0x0004
#endif
_RV32_2( ( RIUBASE_MIU_ATOP + 0x78 ) , 0x0000),
_RV32_2( ( RIUBASE_MIU_ATOP + 0x7a ) , 0x0007),
#else
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x38 ) , 0x0033),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x3A ) , 0x0000),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x02 ) , 0x0000),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x3c ) , 0x2000),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x3e ) , 0x0022),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x0e ) , 0x00e7),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x0e ) , 0x00a7),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x6e ) , 0x0077),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x6a ) , 0x00c2),
    _RV32_2( ( RIUBASE_MIU_ATOP + 0x68 ) , 0x00c2),
#endif
    _END_OF_TBL32_
};



static const MS_REG_INIT MIU_DDR_Init[] =
{
    //===MIU0_MEMPLL===================
    _RV32_2( 0x110d3a, 0x0010 ),  // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2( 0x110d36, 0x4000 ),  // mclk1x_clkph_ck0 / input div_1st/loop_div_1st
    _RV32_2( 0x110d34, 0x0500 ),  // loop_div/input_div

#if (MEMPLL_SEL==MEMCLK_1066MHZ)
    _RV32_2( 0x110d30, 0xd72c ),  // ddfset
    _RV32_2( 0x110d32, 0x0040 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

#if (MEMPLL_SEL==MEMCLK_800MHZ)
    _RV32_2( 0x110d30, 0x6666 ),  // ddfset
    _RV32_2( 0x110d32, 0x0056 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

#if (MEMPLL_SEL==MEMCLK_667MHZ)
    _RV32_2( 0x110d30, 0xc8a6 ),  // ddfset
    _RV32_2( 0x110d32, 0x0067 ),  // ddrpll_reset/ddrpll_porst/ddrpl_pd
#endif

    //===Miu_0 initial=================
#if (MIU0_BANK==0x08)
    _RV32_2( 0x101202, 0x02a2 ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x2a2=ddr2+16bits+8banks+10col+4x
#else
    _RV32_2( 0x101202, 0x0292 ),  //ck/addr/data/cke/data swap/Nx/col/bank/bus width/dram type => 0x292=ddr2+16bits+4banks+10col+4x
#endif
    _RV32_2( 0x101204, 0x008b ),  //if I64Mode =0x8b else =0x0b
    _RV32_2( 0x101206, 0x3420 ),  //refresh cycle=0x20 ,TURN_ON_SCRAMBLE=0x8420
    _RV32_2( 0x101208, 0x1877 ),  //reg_tRCD
    _RV32_2( 0x10120a, 0x1F46 ),  //reg_tRRD
    _RV32_2( 0x10120c, 0x5486 ),  //reg_tWL
    _RV32_2( 0x10120e, 0x2044 ),  //tRFC
    _RV32_2( 0x101210, 0x0a72 ),  //MR0
    _RV32_2( 0x101212, 0x4004 ),  //MR1
    _RV32_2( 0x101214, 0x8000 ),  //MR2
    _RV32_2( 0x101216, 0xC000 ),  //MR3


    //======MIU_ATOP initial======
    _RV32_2( 0x110d0C, 0xF000 ),  // miu_0_atop  start
    _RV32_2( 0x110d00, 0x0001 ),  // miu_0_atop  start
    _RV32_2( 0x110d36, 0x4002 ),  // clk phase
    _RV32_2( 0x110d38, 0x2266 ),  // DQ0/DQ1 phase / dqs0/dqs1 phase
    _RV32_2( 0x110d3a, 0x0000 ),  // mclk1x_skew cmd phase /dqsmask0 /mclk /dqsmask1 phase select
    _RV32_2( 0x110d02, 0xAAAA ),
    _RV32_2( 0x110d3c, 0x0200 ),
    _RV32_2( 0x110d3e, 0x0000 ),
    _RV32_2( 0x110d0e, 0x00e7 ),  // 1/2 reg_en_mask
    _RV32_2( 0x110d0e, 0x00a7 ),  // 2/2 reg_en_mask clr bit6 eg_dqsm_rst_sel
    _RV32_2( 0x110d6e, 0x0077 ),  // reg_dll0_ph //
    _RV32_2( 0x110d6a, 0x00c2 ),  // reg_dll1_code  //refine when DDR_CLK change
    _RV32_2( 0x110d68, 0x00c2 ),  // reg_dll0_code  //refine when DDR_CLK change
    _RV32_2( 0x110d72, 0xF006 ),  //

    _RV32_2( 0x110d5c, 0x3043 ),  // pad driver
    _RV32_2( 0x110d5e, 0x3043 ),  // pad driver
    _RV32_2( 0x110d60, 0x2338 ),  // reg_auto calibration

    _RV32_2( 0x110d36, 0x4003 ),
    _RV32_2( 0x110d38, 0x1145 ),
    _RV32_2( 0x110d3A, 0x0001 ),

    _RV32_2( 0x110d5C, 0x6000 ),
    _RV32_2( 0x110d5E, 0x6000 ),
    _RV32_2( 0x110d6E, 0x0055 ),

#if (MEMPLL_SEL==MEMCLK_1066MHZ || MEMPLL_SEL==MEMCLK_800MHZ)
    _RV32_2( 0x110D10, 0x0300 ),
    _RV32_2( 0x110D36, 0x4002 ),
    _RV32_2( 0x110D38, 0x2266 ),
    _RV32_2( 0x110D3A, 0x0000 ),
    _RV32_2( 0x110D3C, 0x0300 ),
    _RV32_2( 0x110D5C, 0x3043 ),
    _RV32_2( 0x110D5E, 0x3043 ),
#endif

    _END_OF_TBL32_,
};


/*
static const U16 FpgaMiuInit32[] =     //T3 fpga test
{
     0x1202,0x0018,
     0x1204,0x0105,
     0x1210,0x0031,
     0x1212,0x0000,
     // Mdrv_Reset_MIU_0();
     0x121e,0xc001,
     0x121e,0xc000,

     0x1200,0x0008,
     0x1200,0x000c,
     0x1200,0x000e,
     0x1200,0x000f,
     0xffff
};*/


#endif /* __DDR2_16_INIT_H__ */
