////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
////////////////////////////////////////////////////////////////////////////////
#define MHAL_PQ_C


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include <string.h>
#include "MsCommon.h"
#include "MsOS.h"

// Internal Definition
#include "hwreg_utility2.h"
#include "color_reg.h"

#include "drvPQ_Define.h"
#include "Nasa_Main.h"              // table config parameter
#include "drvPQ_Datatypes.h"
#include "mhal_pq.h"
//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#ifndef UNUSED //to avoid compile warnings...
#define UNUSED(var) (void)((var) = (var))
#endif

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
#if 0//NIKON : fix compiling error
extern MS_U16 _u16PQSrcType_DBK_Detect[PQ_MAX_WINDOW]; //For Auto_DBK SW driver used
static MS_U16 _u16PQPre_SrcType = 255;          //For Auto_DBK SW driver used
static MS_BOOL data_read = true;                //For Auto_DBK SW driver used
static MS_BOOL g_bSd_source = true;             //For Check SD mode
static MS_BOOL g_bAnyCandenceEnable = TRUE;
#endif
//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
MS_U32 PQ_RIU_BASE;

// Put this function here because hwreg_utility2 only for hal.
void Hal_PQ_init_riu_base(MS_U32 u32riu_base)
{
    PQ_RIU_BASE = u32riu_base;
}


MS_U8 Hal_PQ_get_sync_flag(MS_BOOL bMainWin)
{
    MS_U16 u16val;
    MS_U8 u8SyncFlag;
    if(bMainWin)
        u16val = MApi_XC_R2BYTE(REG_SC_BK01_1E_L) & 0x00FF;
    else
        u16val = MApi_XC_R2BYTE(REG_SC_BK03_1E_L) & 0x00FF;

    u8SyncFlag = u16val;
    return u8SyncFlag;
}


MS_U8 Hal_PQ_get_input_vsync_value(MS_BOOL bMainWin)
{
    return (Hal_PQ_get_sync_flag(bMainWin) & 0x04) ? 1:0;
}

MS_U8 Hal_PQ_get_output_vsync_value(MS_BOOL bMainWin)
{
    return (Hal_PQ_get_sync_flag(bMainWin) & 0x01) ? 1 : 0;
}

MS_U8 Hal_PQ_get_input_vsync_polarity(MS_BOOL bMainWin)
{
    if(bMainWin)
        return (MApi_XC_R2BYTE(REG_SC_BK01_1E_L) & 0x100) ? 1:0;
    else
        return (MApi_XC_R2BYTE(REG_SC_BK03_1E_L) & 0x100) ? 1:0;
}

void Hal_PQ_set_memfmt_doublebuffer(MS_BOOL bEn)
{
    MApi_XC_W2BYTEMSK(REG_SC_BK12_40_L, bEn ? 0x03 : 0x00, 0x0003);
}

void Hal_PQ_set_sourceidx(MS_BOOL bMain, MS_U16 u16Idx)
{
    if (bMain)
        MApi_XC_W2BYTE(REG_SC_BK00_36_L, u16Idx);
    else
        MApi_XC_W2BYTE(REG_SC_BK00_37_L, u16Idx);
}


void Hal_PQ_set_mem_fmt(MS_BOOL bMainWin, MS_U16 u16val, MS_U16 u16Mask)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK12_02_L, u16val, u16Mask);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK12_42_L, u16val, u16Mask);
}

void Hal_PQ_set_mem_fmt_en(MS_BOOL bMainWin, MS_U16 u16val, MS_U16 u16Mask)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK12_02_L, u16val, u16Mask);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK12_42_L, u16val, u16Mask);
}

void Hal_PQ_set_420upSample(MS_U16 u16value)
{
    MApi_XC_W2BYTE(REG_SC_BK21_76_L, u16value);
}

void Hal_PQ_set_force_y_motion(MS_BOOL bMainWin, MS_U16 u16value)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK22_78_L, u16value, 0x00FF);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK22_78_L, u16value, 0xFF00);
}

MS_U8 Hal_PQ_get_force_y_motion(MS_BOOL bMainWin)
{
    MS_U8 u8val;

    if(bMainWin)
        u8val = (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK22_78_L) & 0x00FF);
    else
        u8val = (MS_U8)((MApi_XC_R2BYTE(REG_SC_BK22_78_L) & 0xFF00)>>8);

    return u8val;
}

void Hal_PQ_set_force_c_motion(MS_BOOL bMainWin, MS_U16 u16value)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK22_79_L, u16value, 0x00FF);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK22_79_L, u16value, 0xFF00);
}

MS_U8 Hal_PQ_get_force_c_motion(MS_BOOL bMainWin)
{
    MS_U8 u8val;

    if(bMainWin)
        u8val = (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK22_79_L) & 0x00FF);
    else
        u8val = (MS_U8)((MApi_XC_R2BYTE(REG_SC_BK22_79_L) & 0xFF00)>>8);
    return u8val;
}

void Hal_PQ_set_dipf_temporal(MS_BOOL bMainWin, MS_U16 u16val)
{
    if(bMainWin)
        MApi_XC_W2BYTE(REG_SC_BK22_14_L, u16val);
    else
        MApi_XC_W2BYTE(REG_SC_BK22_44_L, u16val);
}

MS_U16 Hal_PQ_get_dipf_temporal(MS_BOOL bMainWin)
{
    if(bMainWin)
        return MApi_XC_R2BYTE(REG_SC_BK22_14_L);
    else
        return MApi_XC_R2BYTE(REG_SC_BK22_44_L);
}

void Hal_PQ_set_dipf_spatial(MS_BOOL bMainWin, MS_U16 u16val)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK22_15_L, u16val, 0x00FF);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK22_45_L, u16val, 0x00FF);
}

MS_U8 Hal_PQ_get_dipf_spatial(MS_BOOL bMainWin)
{
    if(bMainWin)
        return (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK22_15_L) & 0x00FF);
    else
        return (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK22_45_L) & 0x00FF);
}

void Hal_PQ_set_vsp_sram_filter(MS_U8 u8vale)
{
    MApi_XC_W2BYTEMSK(REG_SC_BK23_0B_L, ((MS_U16)u8vale)<<8, 0xFF00);
}

MS_U8 Hal_PQ_get_vsp_sram_filter(void)
{
    MS_U8 u8val;
    u8val = (MS_U8)((MApi_XC_R2BYTE(REG_SC_BK23_0B_L) & 0xFF00) >> 8);
    return u8val;
}

void Hal_PQ_set_dnr(MS_BOOL bMainWin, MS_U8 u8val)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK06_21_L, u8val, 0x00FF);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK06_01_L, u8val, 0x00FF);
}

MS_U8 Hal_PQ_get_dnr(MS_BOOL bMainWin)
{
    MS_U8 u8val;
    if(bMainWin)
        u8val = (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK06_21_L) & 0x00FF);
    else
        u8val = (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK06_01_L) & 0x00FF);
    return u8val;
}


void Hal_PQ_set_presnr(MS_BOOL bMainWin, MS_U8 u8val)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK06_22_L, u8val, 0x00FF);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK06_02_L, u8val, 0x00FF);
}

MS_U8 Hal_PQ_get_presnr(MS_BOOL bMainWin)
{
    MS_U8 u8val;
    if(bMainWin)
        u8val = (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK06_22_L) & 0x00FF);
    else
        u8val = (MS_U8)(MApi_XC_R2BYTE(REG_SC_BK06_02_L) & 0x00FF);

    return u8val;
}

void Hal_PQ_set_film(MS_BOOL bMainWin, MS_U16 u16val)
{
    if(bMainWin)
        MApi_XC_W2BYTEMSK(REG_SC_BK0A_10_L, u16val, 0xC800);
    else
        MApi_XC_W2BYTEMSK(REG_SC_BK0A_10_L, u16val, 0x0700);
}

MS_U8 Hal_PQ_get_film(MS_BOOL bMainWin)
{
    MS_U8 u8val;
    u8val = (MS_U8)((MApi_XC_R2BYTE(REG_SC_BK0A_10_L) & 0xFF00) >> 8);
    if(bMainWin)
        u8val &= 0xC8;
    else
        u8val &= 0x07;
    return u8val;
}

void Hal_PQ_set_c_sram_table(MS_U8 u8sramtype, void *pData)
{
    MS_U16 i, j, x;
    MS_U8 u8Ramcode[8];
    MS_U32 u32Addr;

    if(u8sramtype != SC_FILTER_C_SRAM1 &&
       u8sramtype != SC_FILTER_C_SRAM2 &&
       u8sramtype != SC_FILTER_C_SRAM3 &&
       u8sramtype != SC_FILTER_C_SRAM4)
    {
        printf("Unknown c sram type %u\n", u8sramtype);
        return;
    }

    u32Addr = (MS_U32)pData;
    SC_BK_STORE_NOMUTEX;

    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x0000, 0x1000);
    MApi_XC_W2BYTEMSK(REG_SC_BK23_41_L, 0x0002, 0x0002); // enable c_sram_rw

    for(i=0; i<64; i++)
    {
        while(MApi_XC_R2BYTE(REG_SC_BK23_41_L) & 0x0100);
        j=i*5;

        if(u8sramtype == SC_FILTER_C_SRAM1)
            MApi_XC_W2BYTEMSK(REG_SC_BK23_42_L, i, 0x01FF);
        else if(u8sramtype == SC_FILTER_C_SRAM2)
            MApi_XC_W2BYTEMSK(REG_SC_BK23_42_L, (i|0x40), 0x01FF);
        else if(u8sramtype == SC_FILTER_C_SRAM3)
            MApi_XC_W2BYTEMSK(REG_SC_BK23_42_L, (i|0x180), 0x01FF);
        else
            MApi_XC_W2BYTEMSK(REG_SC_BK23_42_L, (i|0x1C0), 0x01FF);

        for ( x=0;x<5;x++ )
        {
            u8Ramcode[x] = *((MS_U8 *)(u32Addr + (j+x)));
            PQ_DUMP_FILTER_DBG(printf(" %02x ", u8Ramcode[x] ));
        }
        PQ_DUMP_FILTER_DBG(printf("\n"));

        MApi_XC_W2BYTEMSK(REG_SC_BK23_43_L, (((MS_U16)u8Ramcode[1])<<8|(MS_U16)u8Ramcode[0]), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK23_44_L, (((MS_U16)u8Ramcode[3])<<8|(MS_U16)u8Ramcode[2]), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK23_45_L, u8Ramcode[4], 0x00FF);

        // enable write
        MApi_XC_W2BYTEMSK(REG_SC_BK23_41_L, 0x0100, 0x0100);
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK23_41_L, 0x00, 0x00FF);
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x1000, 0x1000);
    SC_BK_RESTORE_NOMUTEX;

}

void Hal_PQ_set_y_sram_table(MS_U8 u8sramtype, void *pData)
{
    MS_U16 i, j, x;
    MS_U8 u8Ramcode[5];
    MS_U32 u32Addr;

    if(u8sramtype != SC_FILTER_Y_SRAM1 &&
       u8sramtype != SC_FILTER_Y_SRAM2)
    {
        printf("Unknown y sram type %u\n", u8sramtype);
        return;
    }

    u32Addr = (MS_U32)pData;
    SC_BK_STORE_NOMUTEX;
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x0000, 0x1000);
    MApi_XC_W2BYTEMSK(REG_SC_BK23_41_L, 0x0001, 0x0001); // enable y_sram_rw

    for ( i=0; i<64; i++)
    {
        while(MApi_XC_R2BYTE(REG_SC_BK23_41_L) & 0x0100);
            j=i*5;
            // address

        if(u8sramtype == SC_FILTER_Y_SRAM1)
            MApi_XC_W2BYTEMSK(REG_SC_BK23_42_L, (0x0000|i), 0x007F);
        else
            MApi_XC_W2BYTEMSK(REG_SC_BK23_42_L, (0x0040|i), 0x007F);

            for ( x=0;x<5;x++ )
            {
                u8Ramcode[x] = *((MS_U8 *)(u32Addr + (j+x)));
                PQ_DUMP_FILTER_DBG(printf(" %02x ", u8Ramcode[x] ));
            }
        PQ_DUMP_FILTER_DBG(printf("\n"));

        MApi_XC_W2BYTEMSK(REG_SC_BK23_43_L, (((MS_U16)u8Ramcode[1])<<8|(MS_U16)u8Ramcode[0]), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK23_44_L, (((MS_U16)u8Ramcode[3])<<8|(MS_U16)u8Ramcode[2]), 0xFFFF);
        MApi_XC_W2BYTEMSK(REG_SC_BK23_45_L, ((MS_U16)u8Ramcode[4]), 0x00FF);

        // enable write
        MApi_XC_W2BYTEMSK(REG_SC_BK23_41_L, 0x0100, 0x0100);
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK23_41_L, 0x00, 0x00FF);
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x1000, 0x1000);
    SC_BK_RESTORE_NOMUTEX;
}


void Hal_PQ_set_sram_color_index_table(MS_U8 u8sramtype, void *pData)
{
    MS_U16 i;
    MS_U8 u8Ramcode;
    MS_U32 u32Addr;

    if(u8sramtype != SC_FILTER_SRAM_COLOR_INDEX)
    {
        return;
    }

    u32Addr = (MS_U32)pData;
    SC_BK_STORE_NOMUTEX;
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x0000, 0x1000);

    for(i=0; i<256; i++)
    {
        while(MApi_XC_R2BYTE(REG_SC_BK06_61_L) & 0x0100);

        MApi_XC_W2BYTEMSK(REG_SC_BK06_63_L, i, 0x00FF);
        u8Ramcode = *((MS_U8 *)(u32Addr + (i)));
        PQ_DUMP_FILTER_DBG(printf(" %02x\n", u8Ramcode ));

        MApi_XC_W2BYTEMSK(REG_SC_BK06_62_L, u8Ramcode, 0x0007);
        MApi_XC_W2BYTEMSK(REG_SC_BK06_61_L, 0x0100, 0x0100);
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x1000, 0x1000);
    SC_BK_RESTORE_NOMUTEX;

}

void Hal_PQ_set_sram_color_gain_snr_table(MS_U8 u8sramtype, void *pData)
{
    MS_U16 i;
    MS_U16 u16Ramcode;
    MS_U32 u32Addr;
    MS_U16 u16Gain_DNR;

    if(u8sramtype != SC_FILTER_SRAM_COLOR_GAIN_SNR)
    {
        return;
    }

    u32Addr = (MS_U32)pData;
    SC_BK_STORE_NOMUTEX;
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x0000, 0x1000);

    for(i=0; i<8; i++)
    {
        while(MApi_XC_R2BYTE(REG_SC_BK06_61_L) & 0x0200);

        MApi_XC_W2BYTEMSK(REG_SC_BK06_66_L, i, 0x00FF);

        u16Gain_DNR = MApi_XC_R2BYTE(REG_SC_BK06_65_L) & 0x001F;
        u16Ramcode = *((MS_U8 *)(u32Addr + (i)));
        u16Ramcode = u16Ramcode<<8|u16Gain_DNR;

        PQ_DUMP_FILTER_DBG(printf(" %02x\n", u16Ramcode ));

        MApi_XC_W2BYTEMSK(REG_SC_BK06_64_L, u16Ramcode, 0x1F1F);
        MApi_XC_W2BYTEMSK(REG_SC_BK06_61_L, 0x0200, 0x0200);
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x1000, 0x1000);
    SC_BK_RESTORE_NOMUTEX;
}

void Hal_PQ_set_sram_color_gain_dnr_table(MS_U8 u8sramtype, void *pData)
{
    MS_U16 i;
    MS_U16 u16Ramcode;
    MS_U32 u32Addr;
    MS_U16 u16Gain_SNR;

    if(u8sramtype != SC_FILTER_SRAM_COLOR_GAIN_DNR)
    {
        return;
    }

    u32Addr = (MS_U32)pData;
    SC_BK_STORE_NOMUTEX;
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x0000, 0x1000);

    for(i=0; i<8; i++)
    {
        while(MApi_XC_R2BYTE(REG_SC_BK06_61_L) & 0x0200);

        MApi_XC_W2BYTEMSK(REG_SC_BK06_66_L, i, 0x00FF);

        u16Gain_SNR = MApi_XC_R2BYTE(REG_SC_BK06_65_L) & 0x1F00;
        u16Ramcode = *((MS_U8 *)(u32Addr + (i)));
        u16Ramcode = u16Gain_SNR | u16Ramcode;

        PQ_DUMP_FILTER_DBG(printf(" %02x\n", u16Ramcode ));

        MApi_XC_W2BYTEMSK(REG_SC_BK06_64_L, u16Ramcode, 0x1F1F);
        MApi_XC_W2BYTEMSK(REG_SC_BK06_61_L, 0x0200, 0x0200);
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK00_03_L, 0x1000, 0x1000);
    SC_BK_RESTORE_NOMUTEX;
}

#define ICC_H_SIZE  32
#define ICC_V_SIZE  32
void Hal_PQ_set_sram_icc_crd_table(MS_U8 u8sramtype, void *pData)
{
    MS_U16 i;
    MS_U16 u16Ramcode_L,u16Ramcode_H;
    MS_U16 u16Ramcode;
    MS_U32 u32Addr;

    if(u8sramtype != SC_FILTER_SRAM_ICC_CRD)
    {
        return;
    }

    u32Addr = (MS_U32)pData;
    SC_BK_STORE_NOMUTEX;
    //printf("[%s]\n", __FUNCTION__);
    MApi_XC_W2BYTEMSK(REG_SC_BK1C_78_L, BIT(0), BIT(0)); // io_en disable

    for(i=0; i<(ICC_H_SIZE*ICC_V_SIZE); i++)
    {
        u16Ramcode_L = *((MS_U8 *)(u32Addr + (2*i)));
        u16Ramcode_H = *((MS_U8 *)(u32Addr + (2*i+1)));
        u16Ramcode = ((u16Ramcode_H & 0x01)<<8)+u16Ramcode_L;
        //printf("[%s]HB data=%lx\n",__FUNCTION__, *((MS_U8 *)(u32Addr + (2*i+1))));
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_79_L, i, 0x03FF); // address[9:0]
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7A_L, (u16Ramcode & 0x1FF), 0x01FF); //data[8:0]
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7A_L, BIT(15), BIT(15)); // io_w enable
#if 0 // for debug
{
        MS_U16 u16tmp;
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_79_L, BIT(15), BIT(15)); // io_R enable
        u16tmp=MApi_XC_R2BYTEMSK(REG_SC_BK1C_7B_L, 0x01FF); //data[8:0]
        printf("[%s]ICC_CRD_Data[%d] W=%lx, R=%lx\n", __FUNCTION__, i, u16Ramcode,u16tmp);
}
#endif
    }

    MApi_XC_W2BYTEMSK(REG_SC_BK1C_78_L, 0, BIT(0)); // io_en enable
    SC_BK_RESTORE_NOMUTEX;
}

void Hal_PQ_get_sram_icc_crd_table(MS_U8 u8sramtype, MS_U16 *pBuf)
{
    MS_U16 i;
//  MS_U16 u16Data[ICC_H_SIZE*ICC_V_SIZE];

    if(u8sramtype != SC_FILTER_SRAM_ICC_CRD)
    {
        return;
    }

    SC_BK_STORE_NOMUTEX;

    MApi_XC_W2BYTEMSK(REG_SC_BK1C_78_L, BIT(0), BIT(0)); // io_en disable

    for(i=0; i<(ICC_H_SIZE*ICC_V_SIZE)/2; i++)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_79_L, i, 0x03FF); // address[9:0]
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_79_L, BIT(15), BIT(15)); // io_R enable
        MsOS_DelayTaskUs(1);

        pBuf[i] = MApi_XC_R2BYTEMSK(REG_SC_BK1C_7B_L, 0x01FF); //data[8:0]
        printf("[%s]ICC_CRD_Data[%d]=%lx\n", __FUNCTION__, i, pBuf[i]);
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK1C_78_L, 0, BIT(0)); // io_en enable
    SC_BK_RESTORE_NOMUTEX;
}

#define IHC_H_SIZE  33
#define IHC_V_SIZE  33
#define BUF_BYTE_SIZE (IHC_H_SIZE*IHC_V_SIZE)
#define MAX_SRAM_SIZE 0x124

#define SRAM1_IHC_COUNT 289//81
#define SRAM2_IHC_COUNT 272//72
#define SRAM3_IHC_COUNT 272//72
#define SRAM4_IHC_COUNT 256//64

#define SRAM1_IHC_OFFSET 0
#define SRAM2_IHC_OFFSET SRAM1_IHC_COUNT
#define SRAM3_IHC_OFFSET (SRAM2_IHC_OFFSET + SRAM2_IHC_COUNT)
#define SRAM4_IHC_OFFSET (SRAM3_IHC_OFFSET + SRAM3_IHC_COUNT)

#define SRAM_IHC_TOTAL_COUNT (SRAM1_IHC_COUNT + SRAM2_IHC_COUNT + SRAM3_IHC_COUNT + SRAM4_IHC_COUNT)

void _Hal_PQ_set_sram_ihc_crd_table(MS_U16 *pBuf, MS_U8 u8SRAM_Idx, MS_U16 u16Cnt)
{
    MS_U16 i;

    if(u8SRAM_Idx > 3)
    {
        u8SRAM_Idx = 0;
    }

    SC_BK_STORE_NOMUTEX;

    MApi_XC_W2BYTEMSK(REG_SC_BK1C_7C_L, BIT(0), BIT(0)); // io_en disable
    MApi_XC_W2BYTEMSK(REG_SC_BK1C_7C_L, u8SRAM_Idx<<1, BIT(2)|BIT(1)); // sram select

    for(i=0; i<u16Cnt; i++)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7D_L, i, 0x01FF); // address[8:0]
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7E_L, pBuf[i], 0x03FF); //data[9:0]
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7E_L, BIT(15), BIT(15)); // io_w enable
#if 0
{
        MS_U16 temp;
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7D_L, BIT(15), BIT(15)); // io_R enable
        MsOS_DelayTaskUs(1);
        temp = MApi_XC_R2BYTEMSK(REG_SC_BK1C_7F_L, 0x03FF); //data[9:0]
        printf("[%s]IHC_CRD_Data[%d] W=%lx, R=%lx\n", __FUNCTION__, i, (pBuf[i] & 0x3FF), temp);
}
#endif
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK1C_7C_L, 0, BIT(0)); // io_en enable
    SC_BK_RESTORE_NOMUTEX;
}

void Hal_PQ_set_sram_ihc_crd_table(MS_U8 u8sramtype, void *pData)
{
        // New method for download IHC
        MS_U16 SRAM1_IHC[MAX_SRAM_SIZE] = {0};
        MS_U16 SRAM2_IHC[MAX_SRAM_SIZE] = {0};
        MS_U16 SRAM3_IHC[MAX_SRAM_SIZE] = {0};
        MS_U16 SRAM4_IHC[MAX_SRAM_SIZE] = {0};

        MS_U8* u32Addr = (MS_U8*)pData;

        MS_U16 u16Index = 0 ;
        MS_U16 cont1=0, cont2=0, cont3=0, cont4=0;

        if(u8sramtype != SC_FILTER_SRAM_IHC_CRD)
        {
            return;
        }
        //printf("[%s]SRAM_IHC_TOTAL_COUNT=%u,SRAM2_IHC_OFFSET=%u,SRAM3_IHC_OFFSET=%u,SRAM4_IHC_OFFSET=%u\n",
        //    __FUNCTION__,SRAM_IHC_TOTAL_COUNT,SRAM2_IHC_OFFSET,SRAM3_IHC_OFFSET,SRAM4_IHC_OFFSET);

        for (;u16Index < ((SRAM_IHC_TOTAL_COUNT)*2) ; u16Index+=2)
        {
            if (u16Index < ((SRAM2_IHC_OFFSET)*2))
            {
                //printf("@@u32Addr[%u]=%lx\n",u16Index,(u32Addr[u16Index]));
                //printf("@@u32Addr[%u]=%lx\n",u16Index+1,(u32Addr[u16Index+1]));
                SRAM1_IHC[cont1] = (u32Addr[u16Index+1]) << 8 | (u32Addr[u16Index]);

                //printf("@@SRAM1_IHC[%u]=%lx\n",cont1,(SRAM1_IHC[cont1]));
                cont1++;
            }
            else if (u16Index < ((SRAM3_IHC_OFFSET)*2))
            {
                //printf("@@u32Addr[%u]=%lx\n",u16Index,(u32Addr[u16Index]));
                //printf("@@u32Addr[%u]=%lx\n",u16Index+1,(u32Addr[u16Index+1]));
                SRAM2_IHC[cont2] = (u32Addr[u16Index+1]) << 8 | (u32Addr[u16Index]);

                //printf("@@SRAM2_IHC[%u]=%lx\n",cont2,(SRAM2_IHC[cont2]));
                cont2++;
            }
            else if (u16Index < ((SRAM4_IHC_OFFSET)*2))
            {
                //printf("@@u32Addr[%u]=%lx\n",u16Index,(u32Addr[u16Index]));
                //printf("@@u32Addr[%u]=%lx\n",u16Index+1,(u32Addr[u16Index+1]));
                SRAM3_IHC[cont3] = (u32Addr[u16Index+1]) << 8 | (u32Addr[u16Index]);

                //printf("@@SRAM3_IHC[%u]=%lx\n",cont3,(SRAM3_IHC[cont3]));
                cont3++;
            }
            else
            {
                //printf("@@u32Addr[%u]=%lx\n",u16Index,(u32Addr[u16Index]));
                //printf("@@u32Addr[%u]=%lx\n",u16Index+1,(u32Addr[u16Index+1]));
                SRAM4_IHC[cont4] = (u32Addr[u16Index+1]) << 8 | (u32Addr[u16Index]);

                //printf("@@SRAM4_IHC[%u]=%lx\n",cont4,(SRAM4_IHC[cont4]));
                cont4++;
            }
        }

        _Hal_PQ_set_sram_ihc_crd_table(&SRAM1_IHC[0], 0, SRAM1_IHC_COUNT);
        _Hal_PQ_set_sram_ihc_crd_table(&SRAM2_IHC[0], 1, SRAM2_IHC_COUNT);
        _Hal_PQ_set_sram_ihc_crd_table(&SRAM3_IHC[0], 2, SRAM3_IHC_COUNT);
        _Hal_PQ_set_sram_ihc_crd_table(&SRAM4_IHC[0], 3, SRAM4_IHC_COUNT);

}

void Hal_PQ_get_sram_ihc_crd_table(MS_U8 u8SRAM_Idx, MS_U8 *pBuf)
{
    MS_U16 i;
    MS_U16 u16Size=0;

    if(u8SRAM_Idx > 3)
    {
        u8SRAM_Idx = 0;
    }

    SC_BK_STORE_NOMUTEX;

    MApi_XC_W2BYTEMSK(REG_SC_BK1C_7C_L, BIT(0), BIT(0)); // io_en disable

    switch(u8SRAM_Idx)
    {
        case 0:
            u16Size = SRAM1_IHC_COUNT;
            break;
        case 1:
            u16Size = SRAM2_IHC_COUNT;
            break;
        case 2:
            u16Size = SRAM3_IHC_COUNT;
            break;
        case 3:
            u16Size = SRAM4_IHC_COUNT;
            break;
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK1C_7C_L, u8SRAM_Idx<<1, BIT(2)|BIT(1)); // sram select

    for(i=0; i<u16Size; i++)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7D_L, i, 0x01FF); // address[8:0]
        MApi_XC_W2BYTEMSK(REG_SC_BK1C_7D_L, BIT(15), BIT(15)); // io_R enable
        MsOS_DelayTaskUs(1);

        pBuf[i] = MApi_XC_R2BYTEMSK(REG_SC_BK1C_7F_L, 0x01FF); //data[8:0]
        printf("[%s]IHC_CRD_Data[%d]=%lx\n", __FUNCTION__, i, pBuf[i]);
    }
    MApi_XC_W2BYTEMSK(REG_SC_BK1C_7C_L, 0, BIT(0)); // io_en enable
    SC_BK_RESTORE_NOMUTEX;
}

MS_U16 Hal_PQ_get_420_cup_idx(MS_BOOL bMainWin,MS_420_CUP_TYPE etype)
{
    MS_U16 u16ret;

#if PQ_ENABLE_PIP
    if(bMainWin == FALSE)
    {
        switch(etype)
        {
            case MS_420_CUP_OFF:
            u16ret = PQ_IP_420CUP_OFF_Sub;
            break;

            case MS_420_CUP_ON:
            u16ret = PQ_IP_420CUP_ON_Sub;
            break;

            default:
            u16ret = 0xFFFF;
            break;
        }
    }
    else
#else
    UNUSED(bMainWin);
#endif
    {
        switch(etype)
        {
            case MS_420_CUP_OFF:
            u16ret = PQ_IP_420CUP_OFF_Main;
            break;

            case MS_420_CUP_ON:
            u16ret = PQ_IP_420CUP_ON_Main;
            break;

            default:
            u16ret = 0xFFFF;
            break;
        }
    }
    return u16ret;
}

MS_U16 Hal_PQ_get_hnonlinear_idx(MS_HNONLINEAR_TYPE etype)
{
    MS_U16 u16ret;

    switch(etype)
    {
    case MS_HNONLINEAR_1920_0:
        u16ret = PQ_IP_HnonLinear_H_1920_0_Main;
        break;

    case MS_HNONLINEAR_1920_1:
        u16ret = PQ_IP_HnonLinear_H_1920_1_Main;
        break;

    case MS_HNONLINEAR_1920_2:
        u16ret = PQ_IP_HnonLinear_H_1920_2_Main;
        break;

    case MS_HNONLINEAR_1366_0:
        u16ret = PQ_IP_HnonLinear_H_1366_0_Main;
        break;

    case MS_HNONLINEAR_1366_1:
        u16ret = PQ_IP_HnonLinear_H_1366_1_Main;
        break;

    case MS_HNONLINEAR_1366_2:
        u16ret = PQ_IP_HnonLinear_H_1366_2_Main;
        break;

    default:
        u16ret = PQ_IP_HnonLinear_OFF_Main;
        break;
    }
    return u16ret;
}

MS_U16 Hal_PQ_get_madi_idx(MS_BOOL bMainWin, MS_MADI_TYPE etype)
{
    MS_U16 u16ret;

    if(FALSE ==  bMainWin)
    {
        //This chip dosen't have the sub window, so skip sub win madi idx get function
        u16ret = 0xFFFF;
        return u16ret;
    }

    switch(etype)
    {
    case MS_MADI_25_4R:
        u16ret = PQ_IP_MADi_25_4R_Main;
        break;
    case MS_MADI_25_4R_MC:
        u16ret = PQ_IP_MADi_25_4R_MC_Main;
        break;
    case MS_MADI_25_6R_MC:
        u16ret = PQ_IP_MADi_25_6R_MC_Main;
        break;
    case MS_MADi_25_4R_MC_Yonly:
        u16ret = PQ_IP_MADi_25_4R_MC_Yonly_Main;
        break;
    case MS_MADI_25_2R:
        u16ret = PQ_IP_MADi_25_2R_Main;
        break;
    case MS_MADI_27_4R:
        u16ret = PQ_IP_MADi_27_4R_Main;
        break;
    case MS_MADI_27_2R:
        u16ret = PQ_IP_MADi_27_2R_Main;
        break;
    case MS_MADI_P_MODE8:
        u16ret = PQ_IP_MADi_P_MODE8_Main;
        break;
    case MS_MADI_P_MODE10:
        u16ret = PQ_IP_MADi_P_MODE10_Main;
        break;
    case MS_MADI_P_MODE_MOT10:
        u16ret = PQ_IP_MADi_P_MODE_MOT10_Main;
        break;

    case MS_MADI_P_MODE_MOT8:
        u16ret = PQ_IP_MADi_P_MODE_MOT8_Main;
        break;

    case MS_MADI_24_4R:
        u16ret = PQ_IP_MADi_24_4R_Main;
        break;

    case MS_MADI_24_2R:
        u16ret = PQ_IP_MADi_24_2R_Main;
        break;

    case MS_MADI_26_4R:
        u16ret = PQ_IP_MADi_26_4R_Main;
        break;

    case MS_MADI_26_2R:
        u16ret = PQ_IP_MADi_26_2R_Main;
        break;

    case MS_MADI_24_4R_880:
        u16ret = PQ_IP_MADi_24_4R_880_Main;
        break;

    case MS_MADI_24_2R_880:
        u16ret = PQ_IP_MADi_24_2R_880_Main;
        break;
    case MS_MADI_25_4R_MC_NW:
        u16ret = PQ_IP_MADi_25_4R_MC_NW_Main;
        break;

    case MS_MADI_25_4R_884:
        u16ret = PQ_IP_MADi_25_4R_884_Main;
        break;

    case MS_MADI_25_4R_880:
        u16ret = PQ_IP_MADi_25_4R_880_Main;
        break;

    case MS_MADI_25_2R_884:
        u16ret = PQ_IP_MADi_25_2R_884_Main;
        break;

    case MS_MADI_25_2R_880:
        u16ret = PQ_IP_MADi_24_2R_880_Main;
        break;

    case MS_MADI_25_6R_MC_NW:
        u16ret = PQ_IP_MADi_25_6R_MC_NW_Main;
        break;

    case MS_MADI_25_12F_8R_MC:
        u16ret = PQ_IP_MADi_25_12F_8R_MC_Main;
        break;

    case MS_MADI_25_14F_8R_MC:
        u16ret = PQ_IP_MADi_25_14F_8R_MC_Main;
        break;

    case MS_MADI_25_16F_8R_MC:
        u16ret = PQ_IP_MADi_25_16F_8R_MC_Main;
        break;

    case MS_MADI_P_MODE8_444:
    	u16ret = PQ_IP_MADi_P_MODE8_444_Main;
    	break;
    case MS_MADI_P_MODE10_444:
    	u16ret = PQ_IP_MADi_P_MODE10_444_Main;
    	break;

    case MS_MADI_P_MODE_MOT10_8Frame:
    	u16ret = PQ_IP_MADi_P_MODE_MOT10_8Frame_Main;
    	break;

    case MS_MADI_P_MODE_MOT10_4Frame:
    	u16ret = PQ_IP_MADi_P_MODE_MOT10_4Frame_Main;
    	break;

    case MS_MADI_P_MODE_MC_3Frame:
    	u16ret = PQ_IP_MADi_P_MODE_MC_3Frame_Main;
    	break;

    case MS_MADI_25_14F_6R_MC:
        u16ret = PQ_IP_MADi_25_14F_6R_MC_Main;
        break;

    case MS_MADI_P_MODE_MC_6Frame_6R:
        u16ret = PQ_IP_MADi_P_MODE_MC_6Frame_6R_Main;
        break;

    case MS_MADI_P_MODE_MC_12Frame_8R:
        u16ret = PQ_IP_MADi_P_MODE_MC_12Frame_8R_Main;
        break;

#if PQ_ENABLE_RFBL
    case MS_MADI_RFBL_MC:
        u16ret = PQ_IP_MADi_RFBL_MC_Main;
        break;

    case MS_MADI_RFBL_P_MODE_MC:
        u16ret = PQ_IP_MADi_RFBL_P_MODE_MC_Main;
        break;
#endif
	case MS_MADI_P_MODE8_2BYTE_3D:
		u16ret = PQ_IP_MADi_P_MODE8_2BYTE_3D_Main;
		break;

    default:
        u16ret = 0xFFFF;
        PQ_WARN("Use default madi idx: %d\n", u16ret );
        break;
    }
    return u16ret;
}


MS_U16 Hal_PQ_get_sram_size(MS_U16 u16sramtype)
{
    MS_U16 u16ret;

    switch(u16sramtype)
    {
    case SC_FILTER_Y_SRAM1:
        u16ret = PQ_IP_SRAM1_SIZE_Main;
        break;

    case SC_FILTER_Y_SRAM2:
        u16ret = PQ_IP_SRAM2_SIZE_Main;
        break;

    case SC_FILTER_Y_SRAM3:
        u16ret = PQ_IP_SRAM3_SIZE_Main;
        break;

    case SC_FILTER_Y_SRAM4:
        u16ret = PQ_IP_SRAM4_SIZE_Main;
        break;

    case SC_FILTER_C_SRAM1:
        u16ret = PQ_IP_C_SRAM1_SIZE_Main;
        break;

    case SC_FILTER_C_SRAM2:
        u16ret = PQ_IP_C_SRAM2_SIZE_Main;
        break;

    case SC_FILTER_C_SRAM3:
        u16ret = PQ_IP_C_SRAM3_SIZE_Main;
        break;

    case SC_FILTER_C_SRAM4:
        u16ret = PQ_IP_C_SRAM4_SIZE_Main;
        break;

    case SC_FILTER_SRAM_COLOR_INDEX:
        u16ret = PQ_IP_SRAM_COLOR_INDEX_SIZE_Main;
        break;
#if 0
    case SC_FILTER_SRAM_COLOR_GAIN_SNR:
        u16ret = PQ_IP_SRAM_COLOR_GAIN_SNR_SIZE_Main;
        break;

    case SC_FILTER_SRAM_COLOR_GAIN_DNR:
        u16ret = PQ_IP_SRAM_COLOR_GAIN_DNR_SIZE_Main;
        break;
#endif
    case SC_FILTER_SRAM_ICC_CRD:
        u16ret = PQ_IP_VIP_ICC_CRD_SRAM_SIZE_Main;
        break;

    case SC_FILTER_SRAM_IHC_CRD:
        u16ret = PQ_IP_VIP_IHC_CRD_SRAM_SIZE_Main;
        break;

    default:
        u16ret = 0;
        break;
    }

    return u16ret;
}

MS_U8 Hal_PQ_get_madi_fbl_mode(MS_BOOL bMemFmt422,MS_BOOL bInterlace)
{
    UNUSED(bInterlace);
    if(bMemFmt422)
    {
        return MS_MADI_P_MODE_MOT10;
    }
    else
    {
        return MS_MADI_P_MODE8;
    }
}

MS_U16 Hal_PQ_get_csc_ip_idx(MS_BOOL bMainWin,MS_CSC_IP_TYPE enCSC)
{
    MS_U16 u16Ret;

#if PQ_ENABLE_PIP
    if(bMainWin == FALSE)
    {
        switch(enCSC)
        {
            case MS_CSC_IP_CSC:
            u16Ret = PQ_IP_CSC_Sub;
            break;

            default:
            case MS_CSC_IP_VIP_CSC:
            u16Ret = PQ_IP_VIP_CSC_Sub;
            break;
        }
    }
    else
#else
    UNUSED(bMainWin);
#endif
    {
        switch(enCSC)
        {
            case MS_CSC_IP_CSC:
            u16Ret = PQ_IP_CSC_Main;
            break;

            default:
            case MS_CSC_IP_VIP_CSC:
            u16Ret = PQ_IP_VIP_CSC_Main;
            break;
        }
    }
    return u16Ret;
}

MS_U16 Hal_PQ_get_422To444_idx(MS_BOOL bMainWin, MS_422To444_TYPE etype)
{
    MS_U16 u16ret;
  #if PQ_ENABLE_PIP
    if(bMainWin == FALSE)
    {
        switch(etype)
        {
        case MS_422To444_ON:
            u16ret = PQ_IP_422To444_ON_Sub;
            break;
        case MS_422To444_OFF:
            u16ret = PQ_IP_422To444_OFF_Sub;
            break;

        default:
            u16ret = 0xFFFF;
            PQ_WARN("Use default 422To444 idx: %d\n", u16ret );
            break;
        }
    }
    else
#else
    UNUSED(bMainWin);
#endif
    {
        switch(etype)
        {
        case MS_422To444_ON:
            u16ret = PQ_IP_422To444_ON_Main;
            break;
        case MS_422To444_OFF:
            u16ret = PQ_IP_422To444_OFF_Main;
            break;

        default:
            u16ret = 0xFFFF;
            PQ_WARN("Use default 422To444 idx: %d\n", u16ret );
            break;
        }
    }
    return u16ret;
}

MS_U8 Hal_PQ_get_422To444_mode(MS_BOOL bMemFmt422)
{
    if(bMemFmt422)
    {
        return MS_422To444_ON;
    }
    else
    {
        return MS_422To444_OFF;
    }
}

MS_U16 Hal_PQ_get_ip_idx(MS_BOOL bMainWin,MS_PQ_IP_TYPE eType)
{
    MS_U16 u16ret;

  #if PQ_ENABLE_PIP
    if(bMainWin == FALSE)
    {
        switch(eType)
        {
        case MS_PQ_IP_VD_SAMPLING:
            u16ret = PQ_IP_VD_Sampling_no_comm_Sub;
            break;
        case MS_PQ_IP_HSD_SAMPLING:
            u16ret = PQ_IP_HSD_Sampling_Sub;
            break;
        case MS_PQ_IP_ADC_SAMPLING:
            u16ret = PQ_IP_ADC_Sampling_Sub;
            break;
        default:
            u16ret = 0xFFFF;
            break;
        }
    }
    else
#else
    UNUSED(bMainWin);
#endif
    {
        switch(eType)
        {
        case MS_PQ_IP_VD_SAMPLING:
            u16ret = PQ_IP_VD_Sampling_no_comm_Main;
            break;
        case MS_PQ_IP_HSD_SAMPLING:
            u16ret = PQ_IP_HSD_Sampling_Main;
            break;
        case MS_PQ_IP_ADC_SAMPLING:
            u16ret = PQ_IP_ADC_Sampling_Main;
            break;
        default:
            u16ret = 0xFFFF;
            break;
        }
    }
    return u16ret;
}

MS_U16 Hal_PQ_get_hsd_sampling_idx(MS_BOOL bMainWin,MS_HSD_SAMPLING_TYPE eType)
{
    MS_U16 u16ret;
  #if PQ_ENABLE_PIP
    if(bMainWin == FALSE)
    {
        switch(eType)
        {
        case MS_HSD_SAMPLING_Div_1_000:
            u16ret = PQ_IP_HSD_Sampling_Div_1o000_Sub;
            break;

        case MS_HSD_SAMPLING_Div_1_125:
            u16ret = PQ_IP_HSD_Sampling_Div_1o125_Sub;
            break;

        case MS_HSD_SAMPLING_Div_1_250:
            u16ret = PQ_IP_HSD_Sampling_Div_1o250_Sub;
            break;

        case MS_HSD_SAMPLING_Div_1_375:
            u16ret = PQ_IP_HSD_Sampling_Div_1o375_Sub;
            break;

        case MS_HSD_SAMPLING_Div_1_500:
            u16ret = PQ_IP_HSD_Sampling_Div_1o500_Sub;
            break;

        case MS_HSD_SAMPLING_Div_1_625:
            u16ret = PQ_IP_HSD_Sampling_Div_1o625_Sub;
            break;

        case MS_HSD_SAMPLING_Div_1_750:
            u16ret = PQ_IP_HSD_Sampling_Div_1o750_Sub;
            break;

        case MS_HSD_SAMPLING_Div_1_875:
            u16ret = PQ_IP_HSD_Sampling_Div_1o875_Sub;
            break;

        case MS_HSD_SAMPLING_Div_2_000:
            u16ret = PQ_IP_HSD_Sampling_Div_2o000_Sub;
            break;

        default:
            u16ret = 0xFFFF;
            break;
        }
    }
    else
    #else
    UNUSED(bMainWin);
    #endif
    {
        switch(eType)
        {
        case MS_HSD_SAMPLING_Div_1_000:
            u16ret = PQ_IP_HSD_Sampling_Div_1o000_Main;
            break;

        case MS_HSD_SAMPLING_Div_1_125:
            u16ret = PQ_IP_HSD_Sampling_Div_1o125_Main;
            break;

        case MS_HSD_SAMPLING_Div_1_250:
            u16ret = PQ_IP_HSD_Sampling_Div_1o250_Main;
            break;

        case MS_HSD_SAMPLING_Div_1_375:
            u16ret = PQ_IP_HSD_Sampling_Div_1o375_Main;
            break;

        case MS_HSD_SAMPLING_Div_1_500:
            u16ret = PQ_IP_HSD_Sampling_Div_1o500_Main;
            break;

        case MS_HSD_SAMPLING_Div_1_625:
            u16ret = PQ_IP_HSD_Sampling_Div_1o625_Main;
            break;

        case MS_HSD_SAMPLING_Div_1_750:
            u16ret = PQ_IP_HSD_Sampling_Div_1o750_Main;
            break;

        case MS_HSD_SAMPLING_Div_1_875:
            u16ret = PQ_IP_HSD_Sampling_Div_1o875_Main;
            break;

        case MS_HSD_SAMPLING_Div_2_000:
            u16ret = PQ_IP_HSD_Sampling_Div_2o000_Main;
            break;

        default:
            u16ret = 0xFFFF;
            break;
        }
    }
    return u16ret;
}

void Hal_PQ_OPWriteOff_Enable(MS_BOOL bEna)
{
    MApi_XC_W2BYTEMSK(REG_SC_BK12_27_L, bEna, BIT(0));
}

MS_U16 Hal_PQ_get_adc_sampling_idx(MS_BOOL bMainWin,MS_ADC_SAMPLING_TYPE eType)
{
    MS_U16 u16ret;
    #if PQ_ENABLE_PIP
    if(bMainWin == FALSE)
    {
        switch(eType)
        {
        case MS_ADC_SAMPLING_X_1:
            u16ret = PQ_IP_ADC_Sampling_x1_Sub;
            break;

        case MS_ADC_SAMPLING_X_2:
            u16ret = PQ_IP_ADC_Sampling_x2_Sub;
            break;
        case MS_ADC_SAMPLING_X_4:
            u16ret = PQ_IP_ADC_Sampling_x4_Sub;
            break;
        default:
            u16ret = 0xFFFF;
            break;
        }
    }
    else
    #else
    UNUSED(bMainWin);
    #endif
    {
        switch(eType)
        {
        case MS_ADC_SAMPLING_X_1:
            u16ret = PQ_IP_ADC_Sampling_x1_Main;
            break;

        case MS_ADC_SAMPLING_X_2:
            u16ret = PQ_IP_ADC_Sampling_x2_Main;
            break;
        case MS_ADC_SAMPLING_X_4:
            u16ret = PQ_IP_ADC_Sampling_x4_Main;
            break;
        default:
            u16ret = 0xFFFF;
            break;
        }
    }
    return u16ret;
}

MS_U16 Hal_PQ_get_rw_method(MS_BOOL bMainWin)
{
    MS_U16 u16method;
    if(bMainWin)
    {
        u16method  = (MApi_XC_R2BYTE(REG_SC_BK01_21_L) & 0xC000);
    }
    else
    {
        u16method  = (MApi_XC_R2BYTE(REG_SC_BK03_21_L) & 0xC000);
    }
    return u16method;
}

void Hal_PQ_set_sram_xvycc_gamma_table(MS_U8 u8sramtype, void *pData)
{
    u8sramtype = u8sramtype;
    pData = pData;
}

void Hal_PQ_set_rw_method(MS_BOOL bMainWin, MS_U16 u16method)
{
   if(bMainWin)
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK01_21_L, u16method, 0xC000);
    }
    else
    {
        MApi_XC_W2BYTEMSK(REG_SC_BK03_21_L, u16method, 0xC000);
    }

}

MS_BOOL HAL_PQ_user_mode_control(void)
{
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// set equation to VIP CSC
// Both equation selection rules are
// 0: SDTV(601) R  G  B  : 16-235
// 1: SDTV(601) R  G  B  : 0-255
/// @param bMainWin       \b IN: Enable
//-------------------------------------------------------------------------------------------------
void HAL_PQ_set_SelectCSC(MS_U16 u16selection, MS_BOOL  bMainWin)
{
    if (bMainWin)
    {
        if (u16selection==0)
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0F_L, 0xF0, 0xFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0E_L, 0x00, 0x03);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_16_L, 0x4A, 0xFF);
        }
        else
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0F_L, 0x00, 0xFF);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0E_L, 0x00, 0x03);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_16_L, 0x40, 0xFF);
        }
    }
    else
    {
        if (u16selection==0)
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0F_L, 0xF000, 0xFF00);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0E_L, 0x0000, 0x0300);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_16_L, 0x4A00, 0xFF00);
        }
        else
        {
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0F_L, 0x0000, 0xFF00);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_0E_L, 0x0000, 0x0300);
            MApi_XC_W2BYTEMSK(REG_SC_BK1A_16_L, 0x4000, 0xFF00);
        }
    }
}


