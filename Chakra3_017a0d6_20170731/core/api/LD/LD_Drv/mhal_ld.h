#ifndef _MHAL_LD_H_
#define _MHAL_LD_H_

#include "Board.h"

#if ( LD_ENABLE )

#define LD_MAX_BLOCK_WIDTH      (48)
#define LD_MAX_BLOCK_HEIGHT     (48)
#define LD_MAX_BLOCK_SIZE       (LD_MAX_BLOCK_WIDTH*LD_MAX_BLOCK_HEIGHT)



#define MDrv_LD_MIUReadByte(_BUF_ID, _offset)           \
            (*(volatile U8*) (0x80000000  + (_BUF_ID) + (_offset)))



#define MDrv_LD_MIURead2Bytes(_BUF_ID, _offset)         \
            (*(volatile U16*) (0x80000000  + (_BUF_ID) + (_offset)))



#define MDrv_LD_MIUWriteByte(_BUF_ID, _offset, _val)    \
    do {                                                                                \
            (*((volatile U8*)(0x80000000 + (_BUF_ID) + (_offset)))) = (U8)(_val);    \
    } while(0)

#define MDrv_LD_MIUWrite2Bytes(_BUF_ID, _offset, _val)  \
    do {                                                                                \
            (*((volatile U16*)(0x80000000 + (_BUF_ID) + (_offset)))) = (U16)(_val);  \
    } while(0)


#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
    #define LD_REG(addr)  (0x132E00 | addr)
    #define LD2_REG(addr) (0x134E00 | addr)
#endif


#define MDrv_LD_PackLength  (32)
//================================================================================

// Share mem definition

#define LD_SHARE_MEM_MAGIC_ID   0x55662266

typedef enum
{
    E_LD_INFO_MAGIC_ID              = 0x00,

    // APP to LD_Algo ...
    E_LD_INFO_GAMMA_TBL_ADDR        = 0x01,
    E_LD_INFO_REMAP_TBL_ADDR        = 0x02,
    E_LD_INFO_ALOG_OUT_LED_BUF_ADDR = 0x03,
    E_LD_INFO_ALOG_OUT_LED_BUF_SIZE = 0x04,
    //E_LD_INFO_LDM_DMA_PORT          = 0x05,

    // LD_Algo to APP ...
    E_LD_INFO_ALGO_SPI_BLOCK_ADR = 0x10,


    E_LD_INFO_NUMS              = 0x100,
} EunLdInfoType;

void MHal_LD_ShareMem_Init(U32 u32ShareMemAddr);
void MHal_LD_Set_ShareMem( EunLdInfoType eLdInfo, U32 u32Data);
U32 MHal_LD_Get_ShareMem( EunLdInfoType eLdInfo);

//================================================================================
// h01[0] reg_local_dimming_en
void MHal_LD_Set_LocalDimmingEn(BOOL bEn);
BOOL MHal_LD_Get_LocalDimmingEn(void);
// h01[15] reg_ld_rst
void MHal_LD_Set_SoftReset(BOOL bEn);
BOOL MHal_LD_Get_SoftReset(void);
// h19[19:0] reg_ratio_h_in
void MHal_LD_Set_InputHScalingDownRatio(U32 u32Ratio);
U32  MHal_LD_Get_InputHScalingDownRatio(void);
// h1B[19:0] reg_ratio_v_in
void MHal_LD_Set_InputVScalingDownRatio(U32 u32Ratio);
U32  MHal_LD_Get_InputVScalingDownRatio(void);
// h03[4:0] reg_bl_width
void MHal_LD_Set_LDF_BacklightWidth(U8 u8Width);
U8   MHal_LD_Get_LDF_BacklightWidth(void);
// h03[9:5] reg_bl_height
void MHal_LD_Set_LDF_BacklightHeight(U8 u8Height);
U8   MHal_LD_Get_LDF_BacklightHeight(void);
// h04[25:0] reg_baseaddr0_l
void MHal_LD_Set_LDF_FrameBufBaseAddr_L0(U32 u32Addr);
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_L0(void);
// h06[25:0] reg_baseaddr1_l
void MHal_LD_Set_LDF_FrameBufBaseAddr_L1(U32 u32Addr);
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_L1(void);
// h08[25:0] reg_baseaddr0_r
void MHal_LD_Set_LDF_FrameBufBaseAddr_R0(U32 u32Addr);
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_R0(void);
// h0a[25:0] reg_baseaddr1_r
void MHal_LD_Set_LDF_FrameBufBaseAddr_R1(U32 u32Addr);
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_R1(void);
// h14[25:0] reg_max_adr_ld
void MHal_LD_Set_LDF_MinWritableAddr(U32 u32Addr);
U32  MHal_LD_Get_LDF_MinWritableAddr(void);
// h16[25:0] reg_min_adr_ld
void MHal_LD_Set_LDF_MaxWritableAddr(U32 u32Addr);
U32  MHal_LD_Get_LDF_MaxWritableAddr(void);
// h18[0] reg_miu_adr_limit_en
void MHal_LD_Set_LDF_AddrLimitEn(BOOL bEn);
BOOL MHal_LD_Get_LDF_AddrLimitEn(void);
// h1d[7:0] reg_pel_hlpf_thrd
void MHal_LD_Set_LDF_HLPFThreshold(U8 u8Th);
U8   MHal_LD_Get_LDF_HLPFThreshold(void);
// h1d[12] reg_pel_hlpf_en
void MHal_LD_Set_LDF_HLPFEn(BOOL bEn);
BOOL MHal_LD_Get_LDF_HLPFEn(void);
// h1d[13] reg_pel_hlpf_step
void MHal_LD_Set_LDF_HLPFStep(BOOL bEn);
BOOL MHal_LD_Get_LDF_HLPFStep(void);
// h1f[3:0] reg_alpha
void MHal_LD_Set_LDF_DCMaxAlpha(U8 u8Alpha);
U8   MHal_LD_Get_LDF_DCMaxAlpha(void);
// h1f[7] reg_pel_white_mod_en
void MHal_LD_Set_LDF_PixelWhiteModeEn(BOOL bEn);
BOOL MHal_LD_Get_LDF_PixelWhiteModeEn(void);
// h1f[8] reg_write_dc_max_en
void MHal_LD_Set_LDF_WriteDCMaxEn(BOOL bEn);
BOOL MHal_LD_Get_LDF_WriteDCMaxEn(void);
// h1f[9] reg_write_dc_max_of_en
void MHal_LD_Set_LDF_WriteDCMaxOFEn(BOOL bEn);
BOOL MHal_LD_Get_LDF_WriteDCMaxOFEn(void);
// h1f[15] reg_dc_cbmode
void MHal_LD_Set_LDF_MeanPatchEn(BOOL bEn);
BOOL MHal_LD_Get_LDF_MeanPatchEn(void);
// h22[15:0] reg_dummy0
void MHal_LD_Set_SW_PulseId(U16 u16Id);
U16  MHal_LD_Get_SW_PulseId(void);
// h22[11:0] reg_dummy0
void MHal_LD_Set_SW_PulseMode(U8 u8Mode);
U8   MHal_LD_Get_SW_PulseMode(void);
// h23[7:0] reg_dummy1
void MHal_LD_Set_SW_PulseLEDIntensity(U8 u8Intensity);
U8   MHal_LD_Get_SW_PulseLEDIntensity(void);
// h23[15:8] reg_dummy1
void MHal_LD_Set_SW_PulseLDBIntensity(U8 u8Intensity);
U8   MHal_LD_Get_SW_PulseLDBIntensity(void);
// h24[7:0] reg_dummy2
void MHal_LD_Set_SW_SpatialFilterStrength1(U8 u8Str);
U8   MHal_LD_Get_SW_SpatialFilterStrength1(void);
// h24[15:8] reg_dummy2
void MHal_LD_Set_SW_TemporalFilterStrengthDn(U8 u8Str);
U8   MHal_LD_Get_SW_TemporalFilterStrengthDn(void);
// h25[4:0] reg_dummy3
void MHal_LD_Set_SW_LocalDimmingStrength(U8 u8Str);
U8   MHal_LD_Get_SW_LocalDimmingStrength(void);
// h25[15:8] reg_dummy3
void MHal_LD_Set_SW_GlobalDimmingStrength(U8 u8Str);
U8   MHal_LD_Get_SW_GlobalDimmingStrength(void);
// h29[7:0] reg_dummy15
void MHal_LD_Set_SW_TemporalFilterMaxSpeed(U8 u8Spd);
U8   MHal_LD_Get_SW_TemporalFilterMaxSpeed(void);
// h29[15:8] reg_dummy15
void MHal_LD_Set_SW_MaxThreshold(U8 u8Th);
U8   MHal_LD_Get_SW_MaxThreshold(void);
// h30[19:0] reg_ratio_h_out
void MHal_LD_Set_OutputHScalingUpRatio(U32 u32Ratio);
U32  MHal_LD_Get_OutputHScalingUpRatio(void);
// h32[19:0] reg_ratio_v_out
void MHal_LD_Set_OutputVScalingUpRatio(U32 u32Ratio);
U32  MHal_LD_Get_OutputVScalingUpRatio(void);
// h33[15:0] reg_ratio_h_lsf_cbmode
void MHal_LD_Set_LSF_CB_HRatio(U16 u16Ratio);
U32  MHal_LD_Get_LSF_CB_HRatio(void);
// h34[15:0] reg_ratio_v_lsf_cbmode
void MHal_LD_Set_LSF_CB_VRatio(U16 u16Ratio);
U32  MHal_LD_Get_LSF_CB_VRatio(void);
// h37[0] reg_edge2d_gain_en
void MHal_LD_Set_Edge2DGainEn(BOOL bEn);
BOOL MHal_LD_Get_Edge2DGainEn(void);
// h37[1] reg_edge2d_en
void MHal_LD_Set_Edge2DEn(BOOL bEn);
BOOL MHal_LD_Get_Edge2DEn(void);
// h37[2] reg_edge2d_direct_type_en
void MHal_LD_Set_Edge2DDirectTypeEn(BOOL bEn);
BOOL MHal_LD_Get_Edge2DDirectTypeEn(void);
// h37[4] reg_edge2d_pack16_en
void MHal_LD_Set_Edge2DPack16En(BOOL bEn);
BOOL MHal_LD_Get_Edge2DPack16En(void);
// h37[5] reg_bl_depack16b_mod
void MHal_LD_Set_SpiDepack16En(BOOL bEn);
BOOL MHal_LD_Get_SpiDepack16En(void);
// h37[8] reg_new_edge2d_en
void MHal_LD_Set_Edge2DLocalTypeEn(BOOL bEn);
BOOL MHal_LD_Get_Edge2DLocalTypeEn(void);
// h38[19:0] reg_lsf_h_init
void MHal_LD_Set_LSF_H_InitialPhase_L(U32 u32Phase);
U32 MHal_LD_Get_LSF_H_InitialPhase_L(void);
// h55[19:0] reg_lsf_h_init_r
void MHal_LD_Set_LSF_H_InitialPhase_R(U32 u32Phase);
U32 MHal_LD_Get_LSF_H_InitialPhase_R(void);
// h3a[19:0] reg_lsf_v_init
void MHal_LD_Set_LSF_V_InitialPhase(U32 u32Phase);
U32 MHal_LD_Get_LSF_V_InitialPhase(void);
// h3c[0] reg_lsf_h_shift
void MHal_LD_Set_LSF_H_Boundary_L(BOOL bEn);
BOOL MHal_LD_Get_LSF_H_Boundary_L(void);
// h3c[15] reg_lsf_h_shift_r
void MHal_LD_Set_LSF_H_Boundary_R(BOOL bEn);
BOOL MHal_LD_Get_LSF_H_Boundary_R(void);
// h3c[1] reg_lsf_v_shift
void MHal_LD_Set_LSF_V_Boundary(BOOL bEn);
BOOL MHal_LD_Get_LSF_V_Boundary(void);
// h3c[3:2] reg_edge_level_shift
void MHal_LD_Set_EdgeLevelShift(U8 u8Mode);
U8   MHal_LD_Get_EdgeLevelShift(void);
// h3c[8:4] reg_cmp_blend
void MHal_LD_Set_CompensationBlend(U8 u8Height);
U8   MHal_LD_Get_CompensationBlend(void);
// h3c[10] reg_bld_dither_en
void MHal_LD_Set_BlendingDitherEn(BOOL bEn);
BOOL MHal_LD_Get_BlendingDitherEn(void);
// h3c[13] reg_cmp_dither_en
void MHal_LD_Set_CompensationDitherEn(BOOL bEn);
BOOL MHal_LD_Get_CompensationDitherEn(void);
// h3d[11:0] reg_comp_lut
void MHal_LD_Write_CompensationLUT(U16 u16Lut);
// h3e[11:0] reg_r_comp_lut (readonly);
U16  MHal_LD_Read_CompensationLUT(void);
// h3f[7:0] reg_comp_addr
void MHal_LD_Set_CompensationLUTAddress(U8 u8Addr);
U8   MHal_LD_Get_CompensationLUTAddress(void);
// h3f[10] reg_comp_wd
void MHal_LD_Set_CompensationWriteEn(BOOL bEn);
BOOL MHal_LD_Get_CompensationWriteEn(void);
// h3f[11] reg_comp_rd
void MHal_LD_Set_CompensationReadEn(BOOL bEn);
BOOL MHal_LD_Get_CompensationReadEn(void);
// h3f[12] reg_comp_mod, 1:incremental
void MHal_LD_Set_CompensationMode(BOOL bMode);
BOOL MHal_LD_Get_CompensationMode(void);
// h40[4] reg_read_addr_idx (readonly);
BOOL MHal_LD_Get_CurFrameIdx(void);
// h41[7:0] reg_bl_width_led
void MHal_LD_Set_LED_BacklightWidth(U8 u8Width);
U8   MHal_LD_Get_LED_BacklightWidth(void);
// h41[15:8] reg_bl_height_led
void MHal_LD_Set_LED_BacklightHeight(U8 u8Height);
U8   MHal_LD_Get_LED_BacklightHeight(void);
// h42[7:0] reg_dummy8
void MHal_LD_Set_SW_SpatialFilterStrength4(U8 u8Dist);
U8   MHal_LD_Get_SW_SpatialFilterStrength4(void);
// h42[15:8] reg_dummy8
void MHal_LD_Set_SW_SpatialFilterStrength5(U8 u8Dist);
U8   MHal_LD_Get_SW_SpatialFilterStrength5(void);
// h43[7:0] reg_dummy9
void MHal_LD_Set_SW_MinClampValue(U8 u8Val);
U8   MHal_LD_Get_SW_MinClampValue(void);
// h43[15:8] reg_dummy9
void MHal_LD_Set_SW_TemporalFilterStrengthUp(U8 u8Str);
U8   MHal_LD_Get_SW_TemporalFilterStrengthUp(void);
// h44[0] reg_dummy10
void MHal_LD_Set_SW_AlgorithmEn(BOOL bEn);
BOOL MHal_LD_Get_SW_AlgorithmEn(void);
// h44[1] reg_dummy10
void MHal_LD_Set_SW_ReadLDFEn(BOOL bEn);
BOOL MHal_LD_Get_SW_ReadLDFEn(void);
// h44[2] reg_dummy10
void MHal_LD_Set_SW_WriteSPIEn(BOOL bEn);
BOOL MHal_LD_Get_SW_WriteSPIEn(void);
// h44[3] reg_dummy10
void MHal_LD_Set_SW_WriteLDBEn(BOOL bEn);
BOOL MHal_LD_Get_SW_WriteLDBEn(void);
// h44[5:4] reg_dummy10
void MHal_LD_Set_LEDType(U8 u8Type);
U8   MHal_LD_Get_LEDType(void);

// h44[6] reg_dummy10
void MHal_LD_Set_SW_SpatialFilterStyle(U8 eStyle);
U8   MHal_LD_Get_SW_SpatialFilterStyle(void);

// h44[7] reg_dummy10
void MHal_LD_Set_SW_TemporalFilterStyle(U8 eStyle);
U8   MHal_LD_Get_SW_TemporalFilterStyle(void);

// h46[6] reg_comp_en
void MHal_LD_Set_CompensationEn(BOOL bEn);
BOOL MHal_LD_Get_CompensationEn(void);
// h47[6:0] reg_wid_st_offset_slv_chip
void MHal_LD_Set_LSF_SlaveFirst(U8 u8Blk);
U8   MHal_LD_Get_LSF_SlaveFirst(void);
// h47[14:8] reg_wid_end_mas_chip
void MHal_LD_Set_LSF_MasterLast(U8 u8Blk);
U8   MHal_LD_Get_LSF_MasterLast(void);
// h4b[7:0] reg_bl_globe
void MHal_LD_Set_BacklightGlobeGain(U8 u8Gain);
U8   MHal_LD_Get_BacklightGlobeGain(void);
// h4b[8] reg_bl_globe_mod
void MHal_LD_Set_BacklightGlobeMode(BOOL bMode);
BOOL MHal_LD_Get_BacklightGlobeMode(void);
// h4b[10:9] reg_bl_data_alig
void MHal_LD_Set_BacklightDataAlign(U8 u8Align);
U8   MHal_LD_Get_BacklightDataAlign(void);
// h4c[6:0] reg_bl_width
void MHal_LD_Set_LSF_BacklightWidth(U8 u8Width);
U8   MHal_LD_Get_LSF_BacklightWidth(void);
// h4c[14:8] reg_bl_height
void MHal_LD_Set_LSF_BacklightHeight(U8 u8Height);
U8   MHal_LD_Get_LSF_BacklightHeight(void);
// h4D[25:0] reg_baseaddr0_l
void MHal_LD_Set_LDB_FrameBufBaseAddr_L0(U32 u32Addr);
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_L0(void);
// h4F[25:0] reg_baseaddr1_l
void MHal_LD_Set_LDB_FrameBufBaseAddr_L1(U32 u32Addr);
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_L1(void);
// h51[25:0] reg_baseaddr0_r
void MHal_LD_Set_LDB_FrameBufBaseAddr_R0(U32 u32Addr);
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_R0(void);
// h53[25:0] reg_baseaddr1_r
void MHal_LD_Set_LDB_FrameBufBaseAddr_R1(U32 u32Addr);
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_R1(void);
// h57[7:0] reg_dummy5
void MHal_LD_Set_SW_TemporalFilterLowTh(U8 u8Th);
U8   MHal_LD_Get_SW_TemporalFilterLowTh(void);
// h57[15:8] reg_dummy5
void MHal_LD_Set_SW_TemporalFilterHighTh(U8 u8Th);
U8   MHal_LD_Get_SW_TemporalFilterHighTh(void);
// h58[7:0] reg_dummy6
void MHal_LD_Set_SW_SpatialFilterStrength2(U8 u8Dist);
U8   MHal_LD_Get_SW_SpatialFilterStrength2(void);
// h58[15:8] reg_dummy6
void MHal_LD_Set_SW_SpatialFilterStrength3(U8 u8Dist);
U8   MHal_LD_Get_SW_SpatialFilterStrength3(void);
// h60[5:0] reg_bl_width_dma
void MHal_LD_Set_DMA_BacklightWidth(U8 u8Width);
U8   MHal_LD_Get_DMA_BacklightWidth(void);
// h60[13:8] reg_bl_height_dma
void MHal_LD_Set_DMA_BacklightHeight(U8 u8Height);
U8   MHal_LD_Get_DMA_BacklightHeight(void);
// h63[4:0] reg_bl_width_led
void MHal_LD_Set_LDB_BacklightWidth(U8 u8Width);
U8   MHal_LD_Get_LDB_BacklightWidth(void);
// h63[9:5] reg_bl_height_led
void MHal_LD_Set_LDB_BacklightHeight(U8 u8Height);
U8   MHal_LD_Get_LDB_BacklightHeight(void);
// h64[3:0] reg_miu_pack_offset_0
void MHal_LD_Set_DMA0_PackOffset(U8 u8Offset);
// h65[3:0] reg_miu_pack_length_0
void MHal_LD_Set_DMA0_PackLength(U8 u8Len);
// h65[8] reg_dma0_en
void MHal_LD_Set_DMA0_En(BOOL bEn);
BOOL MHal_LD_Get_DMA0_En(void);
// h66[3:0] reg_miu_pack_offset_1
void MHal_LD_Set_DMA1_PackOffset(U8 u8Offset);
// h67[3:0] reg_miu_pack_length_1
void MHal_LD_Set_DMA1_PackLength(U8 u8Len);
// h67[8] reg_dma1_en
void MHal_LD_Set_DMA1_En(BOOL bEn);
BOOL MHal_LD_Get_DMA1_En(void);
// h68[3:0] reg_miu_pack_offset_2
void MHal_LD_Set_DMA2_PackOffset(U8 u8Offset);
// h69[3:0] reg_miu_pack_length_2
void MHal_LD_Set_DMA2_PackLength(U8 u8Len);
// h69[8] reg_dma2_en
void MHal_LD_Set_DMA2_En(BOOL bEn);
BOOL MHal_LD_Get_DMA2_En(void);
// h6a[3:0] reg_miu_pack_offset_3
void MHal_LD_Set_DMA3_PackOffset(U8 u8Offset);
// h6b[3:0] reg_miu_pack_length_3
void MHal_LD_Set_DMA3_PackLength(U8 u8Len);
// h6b[8] reg_dma3_en
void MHal_LD_Set_DMA3_En(BOOL bEn);
BOOL MHal_LD_Get_DMA3_En(void);
// h6c[5:0] reg_dma_yoff_end_0
void MHal_LD_Set_DMA0_YOffEnd(U8 u8End);
// h6d[5:0] reg_dma_yoff_end_1
void MHal_LD_Set_DMA1_YOffEnd(U8 u8End);
// h6e[5:0] reg_dma_yoff_end_2
void MHal_LD_Set_DMA2_YOffEnd(U8 u8End);
// h6f[5:0] reg_dma_yoff_end_3
void MHal_LD_Set_DMA3_YOffEnd(U8 u8End);
// h70[12:0] reg_frm_width
void MHal_LD_Set_FrameWidth(U16 u16Width);
U16  MHal_LD_Get_FrameWidth(void);
// h71[11:0] reg_frm_height
void MHal_LD_Set_FrameHeight(U16 u16Height);
U16  MHal_LD_Get_FrameHeight(void);
// h72[0] reg_debug_mod
void MHal_LD_Set_DebugMode(BOOL bMode);
BOOL MHal_LD_Get_DebugMode(void);
// h72[3:1] reg_lsf_out_mod
void MHal_LD_Set_LSFOutMode(U8 u8Mode);
U8   MHal_LD_Get_LSFOutMode(void);
// h72[5:4] reg_comp_out_mod
void MHal_LD_Set_CompensationOutMode(U8 u8Mode);
U8   MHal_LD_Get_CompensationOutMode(void);
// h76[11:8] reg_dummy0
void MHal_LD_Set_SW_BacklightInGamma(U8 u8Type);
U8   MHal_LD_Get_SW_BacklightInGamma(void);
// h76[15:12] reg_dummy0
void MHal_LD_Set_SW_BacklightOutGamma(U8 u8Type);
U8   MHal_LD_Get_SW_BacklightOutGamma(void);
// h77[25:0] reg_baseaddr_offset_spi_2
void MHal_LD_Set_SPI_BufBaseAddr_2(U32 u32Addr);
U32  MHal_LD_Get_SPI_BufBaseAddr_2(void);
// h78[15] reg_nxt_spi_access_en
void MHal_LD_Set_NextSpiAccessEn(BOOL bEn);
BOOL MHal_LD_Get_NextSpiAccessEn(void);
// h79[25:0] reg_edge_2d_baseaddr
void MHal_LD_Set_Edge2D_BufBaseAddr(U32 u32Addr);
U32  MHal_LD_Get_Edge2D_BufBaseAddr(void);

#if( CUR_CPU_IS_SEC_R2 == 0 )
// h7E[25:0] reg_baseaddr_offset
void MHal_LD_Set_SPI_BufBaseAddr(U32 u32Addr);
U32  MHal_LD_Get_SPI_BufBaseAddr(void);
void MHal_LD_Set_SPI_VsyncSel(BOOL bsrc);
#endif

// h02[15:0] reg_ratio_h_lsf_cbmode
void MHal_LD_Set_LSF_CB_HInit(U16 u16Phase);
U16  MHal_LD_Get_LSF_CB_HInit(void);
// h03[6:0] reg_led_h_dp_cnt_ini
void MHal_LD_Set_LED_SlaveFirst(U8 u8Led);
U8  MHal_LD_Get_LED_SlaveFirst(void);
// h20[0] reg_ld_coefdec
void MHal_LD_Set_CoefEncoding(BOOL bEnc);
BOOL MHal_LD_Get_CoefEncoding(void);
// h20[1] reg_ld_edge2d_line_md
void MHal_LD_Set_Edge2DLineModeEn(BOOL bEn);
BOOL MHal_LD_Get_Edge2DLineModeEn(void);
// h20[2] reg_ld_comp_low_gain_en
void MHal_LD_Set_CompensationLowEn(BOOL bEn);
BOOL MHal_LD_Get_CompensationLowEn(void);
// h20[15:8] reg_ld_lsf_offset
void MHal_LD_Set_LSFOffset(U8 u8Offset);
U8   MHal_LD_Get_LSFOffset(void);
// h3d[11:0] reg_comp_lut_2
void MHal_LD_Write_CompensationLowLUT(U16 u16Lut);
// h3e[11:0] reg_r_comp_lut_2 (readonly)
U16  MHal_LD_Read_CompensationLowLUT(void);
// h3f[7:0] reg_comp_addr_2
void MHal_LD_Set_CompensationLowLUTAddress(U8 u8Addr);
U8   MHal_LD_Get_CompensationLowLUTAddress(void);
// h3f[10] reg_comp_wd_2
void MHal_LD_Set_CompensationLowWriteEn(BOOL bEn);
BOOL MHal_LD_Get_CompensationLowWriteEn(void);
// h3f[11] reg_comp_rd_2
void MHal_LD_Set_CompensationLowReadEn(BOOL bEn);
BOOL MHal_LD_Get_CompensationLowReadEn(void);
// h3f[12] reg_comp_mod_2, 1:incremental
void MHal_LD_Set_CompensationLowMode(BOOL bMode);
BOOL MHal_LD_Get_CompensationLowMode(void);

#if( CUR_CPU_IS_SEC_R2 == 0 )
#if ENABLE_TWO_SPI
void MHal_LD_Set_DmaMiuPack_Offset_Length(U8 offset1, U8 offset2, U8 len);
#elif ENABLE_FOUR_SPI
void MHal_LD_Set_DmaMiuPack_Offset_Length(U8 offset1, U8 offset2,U8 offset3,U8 offset4, U8 len);
#else
void MHal_LD_Set_DmaMiuPack_Offset_Length(U8 offset, U8 len);
#endif

void MHal_LD_Set_DmaEnable(BOOL bEn);
void MHal_LD_Set_DmaAccessYEnd(U8 ylen);
#endif // ( CUR_CPU_IS_SEC_R2 == 0 )

//===========================================================================

#endif // LD_ENABLE

#endif // _MHAL_LD_H_
