
#include "Board.h"

#if ( LD_ENABLE )
#include "Utl.h"

#include "drvGlobal.h"

#include "mhal_ld.h"

#if( CUR_CPU_IS_SEC_R2 )
    #include "mdrv_ld_sys.h"
#else
#endif

#define FRC_BYTE_PER_WORD           32


#if ENABLE_TWO_SPI
#define LD_DMA_PORT2  MSPI_PORT_NUM2
#elif ENABLE_FOUR_SPI
#define LD_DMA_PORT2  MSPI_PORT_NUM2
#define LD_DMA_PORT3  MSPI_PORT_NUM3
#define LD_DMA_PORT4  MSPI_PORT_NUM4
#endif

//================================================================================

static U32* s_LD_pu32ShareMem = 0;

#define DEBUG_SHARE_MEM(x)  x

void MHal_LD_ShareMem_Init(U32 u32ShareMemAddr)
{
    s_LD_pu32ShareMem = (U32*)MsOS_PA2KSEG1(u32ShareMemAddr);

    //PRINT_CURRENT_LINE();
    DEBUG_SHARE_MEM( printf("MHal_LD_ShareMem_Init(Addr=0x%X)\n", u32ShareMemAddr););
    DEBUG_SHARE_MEM( printf(" => s_LD_pu32ShareMem=0x%X\n", (U32)s_LD_pu32ShareMem); );


#if( CUR_CPU_IS_SEC_R2 )
    // Check share mem magic ID
    if( MHal_LD_Get_ShareMem(E_LD_INFO_MAGIC_ID) != LD_SHARE_MEM_MAGIC_ID )
    {
        printf("Share memory magic id is wrong (0x%X)!", MHal_LD_Get_ShareMem(E_LD_INFO_MAGIC_ID));
        while(1){}
    }
#else
    memset( s_LD_pu32ShareMem, 0 , E_LD_INFO_NUMS*sizeof(U32));
    MHal_LD_Set_ShareMem(E_LD_INFO_MAGIC_ID, LD_SHARE_MEM_MAGIC_ID);
#endif
}

void MHal_LD_Set_ShareMem( EunLdInfoType eLdInfo, U32 u32Data)
{
    if( s_LD_pu32ShareMem == 0 )
        return;

    if( eLdInfo >= E_LD_INFO_NUMS )
        return;

    DEBUG_SHARE_MEM( printf("ShareMem(0x%X)=0x%X\n", eLdInfo, u32Data ); );

    s_LD_pu32ShareMem[eLdInfo] = u32Data;

    MsOS_FlushMemory();
}

U32 MHal_LD_Get_ShareMem( EunLdInfoType eLdInfo)
{
    if( s_LD_pu32ShareMem == 0 )
        return 0;

    if( eLdInfo >= E_LD_INFO_NUMS )
        return 0;

    U32 u32Data = s_LD_pu32ShareMem[eLdInfo];

    //printf("ShareMem(0x%X) ==> 0x%X\n", eLdInfo, u32Data );

    return u32Data;
}

//================================================================================

// h01[0] reg_local_dimming_en
void MHal_LD_Set_LocalDimmingEn(BOOL bEn)             { MDrv_WriteRegBit(LD_REG(0x02), bEn, _BIT0); }
BOOL MHal_LD_Get_LocalDimmingEn(void)                 { return MDrv_ReadRegBit(LD_REG(0x02), _BIT0); }
// h01[15] reg_ld_rst
void MHal_LD_Set_SoftReset(BOOL bEn)                  { MDrv_WriteRegBit(LD_REG(0x03), bEn, _BIT7); }
BOOL MHal_LD_Get_SoftReset(void)                      { return MDrv_ReadRegBit(LD_REG(0x03), _BIT7); }
// h19[19:0] reg_ratio_h_in
void MHal_LD_Set_InputHScalingDownRatio(U32 u32Ratio) { MDrv_Write4Byte(LD_REG(0x32), u32Ratio); }
U32  MHal_LD_Get_InputHScalingDownRatio(void)         { return MDrv_Read4Byte(LD_REG(0x32)) & 0x0007FFFF; }
// h1B[19:0] reg_ratio_v_in
void MHal_LD_Set_InputVScalingDownRatio(U32 u32Ratio) { MDrv_Write4Byte(LD_REG(0x36), u32Ratio); }
U32  MHal_LD_Get_InputVScalingDownRatio(void)         { return MDrv_Read4Byte(LD_REG(0x36)) & 0x0007FFFF; }
// h03[4:0] reg_bl_width
void MHal_LD_Set_LDF_BacklightWidth(U8 u8Width)       { MDrv_WriteByteMask(LD_REG(0x06), u8Width-1, 0x7F); }
U8   MHal_LD_Get_LDF_BacklightWidth(void)             { return (MDrv_ReadByte(LD_REG(0x06)) & 0x7F)+1; }
// h03[9:5] reg_bl_height
void MHal_LD_Set_LDF_BacklightHeight(U8 u8Height)     { MDrv_Write2ByteMask(LD_REG(0x06), ((U16)u8Height-1) << 8, 0x3F00); }
U8   MHal_LD_Get_LDF_BacklightHeight(void)            { return (U8)((MDrv_Read2Byte(LD_REG(0x06)) & 0x3F00) >> 8)+1; }
// h04[25:0] reg_baseaddr0_l
void MHal_LD_Set_LDF_FrameBufBaseAddr_L0(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0x08), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_L0(void)        { return (MDrv_Read4Byte(LD_REG(0x08)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h06[25:0] reg_baseaddr1_l
void MHal_LD_Set_LDF_FrameBufBaseAddr_L1(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0x0C), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_L1(void)        { return (MDrv_Read4Byte(LD_REG(0x0C)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h08[25:0] reg_baseaddr0_r
void MHal_LD_Set_LDF_FrameBufBaseAddr_R0(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0x10), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_R0(void)        { return (MDrv_Read4Byte(LD_REG(0x10)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h0A[25:0] reg_baseaddr1_r
void MHal_LD_Set_LDF_FrameBufBaseAddr_R1(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0x14), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDF_FrameBufBaseAddr_R1(void)        { return (MDrv_Read4Byte(LD_REG(0x14)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h14[0] reg_max_adr_ld
void MHal_LD_Set_LDF_AddrLimitMax(U32 u32Addr)        { MDrv_Write4Byte(LD_REG(0x28), u32Addr/MDrv_LD_PackLength); }
U32 MHal_LD_Get_LDF_AddrLimitMax(void)                { return (MDrv_Read4Byte(LD_REG(0x28)) & 0x03FFFFFF)*MDrv_LD_PackLength; }
// h16[0] reg_min_adr_ld
void MHal_LD_Set_LDF_AddrLimitMin(U32 u32Addr)        { MDrv_Write4Byte(LD_REG(0x2C), u32Addr/MDrv_LD_PackLength); }
U32 MHal_LD_Get_LDF_AddrLimitMin(void)                { return (MDrv_Read4Byte(LD_REG(0x2C)) & 0x03FFFFFF)*MDrv_LD_PackLength; }
// h18[0] reg_miu_adr_limit_en
void MHal_LD_Set_LDF_AddrLimitEn(BOOL bEn)            { MDrv_WriteRegBit(LD_REG(0x30), bEn, _BIT0); }
BOOL MHal_LD_Get_LDF_AddrLimitEn(void)                { return MDrv_ReadRegBit(LD_REG(0x30), _BIT0); }
// h1d[7:0] reg_pel_hlpf_thrd
void MHal_LD_Set_LDF_HLPFThreshold(U8 u8Th)           { MDrv_WriteByte(LD_REG(0x3A), u8Th); }
U8   MHal_LD_Get_LDF_HLPFThreshold(void)              { return MDrv_ReadByte(LD_REG(0x3A)); }
// h1d[12] reg_pel_hlpf_en
void MHal_LD_Set_LDF_HLPFEn(BOOL bEn)                 { MDrv_WriteRegBit(LD_REG(0x3B), bEn, _BIT4); }
BOOL MHal_LD_Get_LDF_HLPFEn(void)                     { return MDrv_ReadRegBit(LD_REG(0x3B), _BIT4); }
// h1d[13] reg_pel_hlpf_step
void MHal_LD_Set_LDF_HLPFStep(BOOL bEn)               { MDrv_WriteRegBit(LD_REG(0x3B), bEn, _BIT5); }
BOOL MHal_LD_Get_LDF_HLPFStep(void)                   { return MDrv_ReadRegBit(LD_REG(0x3B), _BIT5); }
// h1f[3:0] reg_alpha
void MHal_LD_Set_LDF_DCMaxAlpha(U8 u8Alpha)           { MDrv_WriteByteMask(LD_REG(0x3E), u8Alpha, 0x0F); }
U8   MHal_LD_Get_LDF_DCMaxAlpha(void)                 { return MDrv_ReadByte(LD_REG(0x3E)) & 0x0F; }
// h1f[7] reg_pel_white_mod_en
void MHal_LD_Set_LDF_PixelWhiteModeEn(BOOL bEn)       { MDrv_WriteRegBit(LD_REG(0x3E), bEn, _BIT7); }
BOOL MHal_LD_Get_LDF_PixelWhiteModeEn(void)           { return MDrv_ReadRegBit(LD_REG(0x3E), _BIT7); }
// h1f[8] reg_write_dc_max_en
void MHal_LD_Set_LDF_WriteDCMaxEn(BOOL bEn)           { MDrv_WriteRegBit(LD_REG(0x3F), bEn, _BIT0); }
BOOL MHal_LD_Get_LDF_WriteDCMaxEn(void)               { return MDrv_ReadRegBit(LD_REG(0x3F), _BIT0); }
// h1f[9] reg_write_dc_max_of_en
void MHal_LD_Set_LDF_WriteDCMaxOFEn(BOOL bEn)         { MDrv_WriteRegBit(LD_REG(0x3F), bEn, _BIT1); }
BOOL MHal_LD_Get_LDF_WriteDCMaxOFEn(void)             { return MDrv_ReadRegBit(LD_REG(0x3F), _BIT1); }
// h22[11:0] reg_dummy0
void MHal_LD_Set_SW_PulseId(U16 u16Id)                { MDrv_Write2ByteMask(LD_REG(0x44), u16Id, 0x0FFF); }
U16  MHal_LD_Get_SW_PulseId(void)                     { return MDrv_Read2Byte(LD_REG(0x44)) & 0x0FFF; }
// h22[15:12] reg_dummy0
void MHal_LD_Set_SW_PulseMode(U8 u8Mode)              { MDrv_WriteByteMask(LD_REG(0x45), u8Mode, 0xF0); }
U8   MHal_LD_Get_SW_PulseMode(void)                   { return MDrv_ReadByte(LD_REG(0x45)) >> 4; }
// h23[7:0] reg_dummy1
void MHal_LD_Set_SW_PulseLEDIntensity(U8 u8Intensity) { MDrv_WriteByte(LD_REG(0x46), u8Intensity); }
U8   MHal_LD_Get_SW_PulseLEDIntensity(void)           { return MDrv_ReadByte(LD_REG(0x46)); }
// h23[7:0] reg_dummy1
void MHal_LD_Set_SW_PulseLDBIntensity(U8 u8Intensity) { MDrv_WriteByte(LD_REG(0x47), u8Intensity); }
U8   MHal_LD_Get_SW_PulseLDBIntensity(void)           { return MDrv_ReadByte(LD_REG(0x47)); }
// h24[7:0] reg_dummy2
void MHal_LD_Set_SW_SpatialFilterStrength1(U8 u8Str)  { MDrv_WriteByte(LD_REG(0x48), u8Str); }
U8   MHal_LD_Get_SW_SpatialFilterStrength1(void)      { return MDrv_ReadByte(LD_REG(0x48)); }
// h24[15:8] reg_dummy2
void MHal_LD_Set_SW_TemporalFilterStrengthDn(U8 u8Str){ MDrv_WriteByte(LD_REG(0x49), u8Str); }
U8   MHal_LD_Get_SW_TemporalFilterStrengthDn(void)    { return MDrv_ReadByte(LD_REG(0x49)); }
// h25[7:0] reg_dummy3
void MHal_LD_Set_SW_LocalDimmingStrength(U8 u8Str)    { MDrv_WriteByte(LD_REG(0x4A), u8Str); }
U8   MHal_LD_Get_SW_LocalDimmingStrength(void)        { return MDrv_ReadByte(LD_REG(0x4A)); }
// h25[15:8] reg_dummy3
void MHal_LD_Set_SW_GlobalDimmingStrength(U8 u8Str)   { MDrv_WriteByte(LD_REG(0x4B), u8Str); }
U8   MHal_LD_Get_SW_GlobalDimmingStrength(void)       { return MDrv_ReadByte(LD_REG(0x4B)); }
// h29[7:0] reg_dummy15
void MHal_LD_Set_SW_TemporalFilterMaxSpeed(U8 u8Spd)  { MDrv_WriteByte(LD_REG(0x52), u8Spd); }
U8   MHal_LD_Get_SW_TemporalFilterMaxSpeed(void)      { return MDrv_ReadByte(LD_REG(0x52)); }
// h29[15:8] reg_dummy15
void MHal_LD_Set_SW_MaxThreshold(U8 u8Th)             { MDrv_WriteByte(LD_REG(0x50), u8Th); }
U8   MHal_LD_Get_SW_MaxThreshold(void)                { return MDrv_ReadByte(LD_REG(0x50)); }
// h30[19:0] reg_ratio_h_out
void MHal_LD_Set_OutputHScalingUpRatio(U32 u32Ratio)  { MDrv_Write4Byte(LD_REG(0x60), u32Ratio); }
U32  MHal_LD_Get_OutputHScalingUpRatio(void)          { return MDrv_Read4Byte(LD_REG(0x60)) & 0x0007FFFF; }
// h32[19:0] reg_ratio_v_out
void MHal_LD_Set_OutputVScalingUpRatio(U32 u32Ratio)  { MDrv_Write4Byte(LD_REG(0x64), u32Ratio); }
U32  MHal_LD_Get_OutputVScalingUpRatio(void)          { return MDrv_Read4Byte(LD_REG(0x64)) & 0x0007FFFF; }
// h33[15:0] reg_ratio_h_lsf_cbmode
void MHal_LD_Set_LSF_CB_HRatio(U16 u16Ratio)          { MDrv_Write2Byte(LD_REG(0x68), u16Ratio); }
U32  MHal_LD_Get_LSF_CB_HRatio(void)                  { return MDrv_Read2Byte(LD_REG(0x68)); }
// h34[15:0] reg_ratio_v_lsf_cbmode
void MHal_LD_Set_LSF_CB_VRatio(U16 u16Ratio)          { MDrv_Write2Byte(LD_REG(0x6A), u16Ratio); }
U32  MHal_LD_Get_LSF_CB_VRatio(void)                  { return MDrv_Read2Byte(LD_REG(0x6A)); }
// h37[0] reg_edge2d_gain_en
void MHal_LD_Set_Edge2DGainEn(BOOL bEn)               { MDrv_WriteRegBit(LD_REG(0x6E), bEn, _BIT0); }
BOOL MHal_LD_Get_Edge2DGainEn(void)                   { return MDrv_ReadRegBit(LD_REG(0x6E), _BIT0); }
// h37[1] reg_edge2d_en
void MHal_LD_Set_Edge2DEn(BOOL bEn)                   { MDrv_WriteRegBit(LD_REG(0x6E), bEn, _BIT1); }
BOOL MHal_LD_Get_Edge2DEn(void)                       { return MDrv_ReadRegBit(LD_REG(0x6E), _BIT1); }
// h37[2] reg_edge2d_direct_type_en
void MHal_LD_Set_Edge2DDirectTypeEn(BOOL bEn)         { MDrv_WriteRegBit(LD_REG(0x6E), bEn, _BIT2); }
BOOL MHal_LD_Get_Edge2DDirectTypeEn(void)             { return MDrv_ReadRegBit(LD_REG(0x6E), _BIT2); }
// h37[4] reg_edge2d_pack16_en
void MHal_LD_Set_Edge2DPack16En(BOOL bEn)             { MDrv_WriteRegBit(LD_REG(0x6E), bEn, _BIT4); }
BOOL MHal_LD_Get_Edge2DPack16En(void)                 { return MDrv_ReadRegBit(LD_REG(0x6E), _BIT4); }
// h37[5] reg_bl_depack16b_mod
void MHal_LD_Set_SpiDepack16En(BOOL bEn)              { MDrv_WriteRegBit(LD_REG(0x6E), bEn, _BIT5); }
BOOL MHal_LD_Get_SpiDepack16En(void)                  { return MDrv_ReadRegBit(LD_REG(0x6E), _BIT5); }
// h37[8] reg_new_edge2d_en
void MHal_LD_Set_Edge2DLocalTypeEn(BOOL bEn)          { MDrv_WriteRegBit(LD_REG(0x6F), bEn, _BIT0); }
BOOL MHal_LD_Get_Edge2DLocalTypeEn(void)              { return MDrv_ReadRegBit(LD_REG(0x6F), _BIT0); }
// h38[19:0] reg_lsf_h_init
void MHal_LD_Set_LSF_H_InitialPhase_L(U32 u32Phase)   { MDrv_Write4Byte(LD_REG(0x70), u32Phase); }
U32 MHal_LD_Get_LSF_H_InitialPhase_L(void)            { return MDrv_Read4Byte(LD_REG(0x70)) & 0x0007FFFF; }
// h55[19:0] reg_lsf_h_init_r
void MHal_LD_Set_LSF_H_InitialPhase_R(U32 u32Phase)   { MDrv_Write4Byte(LD_REG(0xAA), u32Phase); }
U32 MHal_LD_Get_LSF_H_InitialPhase_R(void)            { return MDrv_Read4Byte(LD_REG(0xAA)) & 0x0007FFFF; }
// h3a[19:0] reg_lsf_v_init
void MHal_LD_Set_LSF_V_InitialPhase(U32 u32Phase)     { MDrv_Write4Byte(LD_REG(0x74), u32Phase); }
U32 MHal_LD_Get_LSF_V_InitialPhase(void)              { return MDrv_Read4Byte(LD_REG(0x74)) & 0x0007FFFF; }
// h3c[0] reg_lsf_h_shift
void MHal_LD_Set_LSF_H_Boundary_L(BOOL bEn)           { MDrv_WriteRegBit(LD_REG(0x78), bEn, _BIT0); }
BOOL MHal_LD_Get_LSF_H_Boundary_L(void)               { return MDrv_ReadRegBit(LD_REG(0x78), _BIT0); }
// h3c[15] reg_lsf_h_shift_r
void MHal_LD_Set_LSF_H_Boundary_R(BOOL bEn)           { MDrv_WriteRegBit(LD_REG(0x79), bEn, _BIT7); }
BOOL MHal_LD_Get_LSF_H_Boundary_R(void)               { return MDrv_ReadRegBit(LD_REG(0x79), _BIT7); }
// h3c[1] reg_lsf_v_shift
void MHal_LD_Set_LSF_V_Boundary(BOOL bEn)             { MDrv_WriteRegBit(LD_REG(0x78), bEn, _BIT1); }
BOOL MHal_LD_Get_LSF_V_Boundary(void)                 { return MDrv_ReadRegBit(LD_REG(0x78), _BIT1); }
// h3c[3:2] reg_edge_level_shift
void MHal_LD_Set_EdgeLevelShift(U8 u8Mode)            { MDrv_WriteByteMask(LD_REG(0x78), u8Mode << 2, 0x0C); }
U8   MHal_LD_Get_EdgeLevelShift(void)                 { return (MDrv_ReadByte(LD_REG(0x78)) & 0x0C) >> 2; }
// h3c[8:4] reg_cmp_blend
void MHal_LD_Set_CompensationBlend(U8 u8Alpha)        { MDrv_Write2ByteMask(LD_REG(0x78), ((U16)u8Alpha) << 4, 0x01F0); }
U8   MHal_LD_Get_CompensationBlend(void)              { return (MDrv_Read2Byte(LD_REG(0x78)) & 0x01F0) >> 4; }
// h3c[10] reg_bld_dither_en
void MHal_LD_Set_BlendingDitherEn(BOOL bEn)           { MDrv_WriteRegBit(LD_REG(0x79), bEn, _BIT2); }
BOOL MHal_LD_Get_BlendingDitherEn(void)               { return MDrv_ReadRegBit(LD_REG(0x79), _BIT2); }
// h3c[13] reg_cmp_dither_en
void MHal_LD_Set_CompensationDitherEn(BOOL bEn)       { MDrv_WriteRegBit(LD_REG(0x79), bEn, _BIT5); }
BOOL MHal_LD_Get_CompensationDitherEn(void)           { return MDrv_ReadRegBit(LD_REG(0x79), _BIT5); }
// h3d[11:0] reg_comp_lut
void MHal_LD_Write_CompensationLUT(U16 u16Lut)        { MDrv_Write2ByteMask(LD_REG(0x7A), u16Lut, 0x0FFF); }
// h3e[11:0] reg_r_comp_lut (readonly)
U16  MHal_LD_Read_CompensationLUT(void)               { return MDrv_Read2Byte(LD_REG(0x7C)) & 0x0FFF; }
// h3f[7:0] reg_comp_addr
void MHal_LD_Set_CompensationLUTAddress(U8 u8Addr)    { MDrv_WriteByte(LD_REG(0x7E), u8Addr); }
U8   MHal_LD_Get_CompensationLUTAddress(void)         { return MDrv_ReadByte(LD_REG(0x7E)); }
// h3f[10] reg_comp_wd
void MHal_LD_Set_CompensationWriteEn(BOOL bEn)        { MDrv_WriteRegBit(LD_REG(0x7F), bEn, _BIT2); }
BOOL MHal_LD_Get_CompensationWriteEn(void)            { return MDrv_ReadRegBit(LD_REG(0x7F), _BIT2); }
// h3f[11] reg_comp_rd
void MHal_LD_Set_CompensationReadEn(BOOL bEn)         { MDrv_WriteRegBit(LD_REG(0x7F), bEn, _BIT3); }
BOOL MHal_LD_Get_CompensationReadEn(void)             { return MDrv_ReadRegBit(LD_REG(0x7F), _BIT3); }
// h3f[12] reg_comp_mod, 1:incremental
void MHal_LD_Set_CompensationMode(BOOL bMode)         { MDrv_WriteRegBit(LD_REG(0x7F), bMode, _BIT4); }
BOOL MHal_LD_Get_CompensationMode(void)               { return MDrv_ReadRegBit(LD_REG(0x7F), _BIT4); }
// h40[4] reg_read_addr_idx (readonly)
BOOL MHal_LD_Get_CurFrameIdx(void)                    { return (MDrv_ReadRegBit(LD_REG(0x80), _BIT4)>>4); } //return index = 0 or 1
// h41[7:0] reg_bl_width_led
void MHal_LD_Set_LED_BacklightWidth(U8 u8Width)       { MDrv_WriteByte(LD_REG(0x82), u8Width-1); }
U8   MHal_LD_Get_LED_BacklightWidth(void)             { return MDrv_ReadByte(LD_REG(0x82))+1; }
// h41[15:8] reg_bl_height_led
void MHal_LD_Set_LED_BacklightHeight(U8 u8Height)     { MDrv_WriteByte(LD_REG(0x83), u8Height-1); }
U8   MHal_LD_Get_LED_BacklightHeight(void)            { return MDrv_ReadByte(LD_REG(0x83))+1; }
// h42[7:0] reg_dummy8
void MHal_LD_Set_SW_SpatialFilterStrength4(U8 u8Dist) { MDrv_WriteByte(LD_REG(0x84), u8Dist); }
U8   MHal_LD_Get_SW_SpatialFilterStrength4(void)      { return MDrv_ReadByte(LD_REG(0x84)); }
// h42[15:8] reg_dummy8
void MHal_LD_Set_SW_SpatialFilterStrength5(U8 u8Dist) { MDrv_WriteByte(LD_REG(0x85), u8Dist); }
U8   MHal_LD_Get_SW_SpatialFilterStrength5(void)      { return MDrv_ReadByte(LD_REG(0x85)); }
// h43[7:0] reg_dummy9
void MHal_LD_Set_SW_MinClampValue(U8 u8Val)           { MDrv_WriteByte(LD_REG(0x86), u8Val); }
U8   MHal_LD_Get_SW_MinClampValue(void)               { return MDrv_ReadByte(LD_REG(0x86)); }
// h43[15:8] reg_dummy9
void MHal_LD_Set_SW_TemporalFilterStrengthUp(U8 u8Str){ MDrv_WriteByte(LD_REG(0x87), u8Str); }
U8   MHal_LD_Get_SW_TemporalFilterStrengthUp(void)    { return MDrv_ReadByte(LD_REG(0x87)); }
// h44[0] reg_dummy10
void MHal_LD_Set_SW_AlgorithmEn(BOOL bEn)             { MDrv_WriteRegBit(LD_REG(0x88), bEn, _BIT0); }
BOOL MHal_LD_Get_SW_AlgorithmEn(void)                 { return MDrv_ReadRegBit(LD_REG(0x88), _BIT0); }
// h44[1] reg_dummy10
void MHal_LD_Set_SW_ReadLDFEn(BOOL bEn)               { MDrv_WriteRegBit(LD_REG(0x88), bEn, _BIT1); }
BOOL MHal_LD_Get_SW_ReadLDFEn(void)                   { return MDrv_ReadRegBit(LD_REG(0x88), _BIT1); }
// h44[2] reg_dummy10
void MHal_LD_Set_SW_WriteSPIEn(BOOL bEn)              { MDrv_WriteRegBit(LD_REG(0x88), bEn, _BIT2); }
BOOL MHal_LD_Get_SW_WriteSPIEn(void)                  { return MDrv_ReadRegBit(LD_REG(0x88), _BIT2); }
// h44[3] reg_dummy10
void MHal_LD_Set_SW_WriteLDBEn(BOOL bEn)              { MDrv_WriteRegBit(LD_REG(0x88), bEn, _BIT3); }
BOOL MHal_LD_Get_SW_WriteLDBEn(void)                  { return MDrv_ReadRegBit(LD_REG(0x88), _BIT3); }
// h44[5:4] reg_dummy10
void MHal_LD_Set_LEDType(U8 eType)                    { MDrv_WriteByteMask(LD_REG(0x88), eType << 4, _BIT4 | _BIT5); }
U8   MHal_LD_Get_LEDType(void)                        { return (MDrv_ReadByte(LD_REG(0x88)) >> 4) & 0x3; }

// h44[6] reg_dummy10
void MHal_LD_Set_SW_SpatialFilterStyle(U8 eStyle)     { MDrv_WriteRegBit(LD_REG(0xEC), eStyle, _BIT2); }
//U8   MHal_LD_Get_SW_SpatialFilterStyle(void)          { return MDrv_ReadRegBit(LD_REG(0xEC), _BIT2); }
U8 MHal_LD_Get_SW_SpatialFilterStyle(void)            { return ((MDrv_ReadByte(LD_REG(0xEC))&_BIT2)?1:0); }

// h44[7] reg_dummy10
void MHal_LD_Set_SW_TemporalFilterStyle(U8 eStyle)    { MDrv_WriteRegBit(LD_REG(0xEC), eStyle, _BIT3); }
//U8   MHal_LD_Get_SW_TemporalFilterStyle(void)         { return MDrv_ReadRegBit(LD_REG(0xEC), _BIT3); }
U8 MHal_LD_Get_SW_TemporalFilterStyle(void)           { return ((MDrv_ReadByte(LD_REG(0xEC))&_BIT3)?1:0); }

// h46[6] reg_comp_en
void MHal_LD_Set_CompensationEn(BOOL bEn)             { MDrv_WriteRegBit(LD_REG(0x8C), bEn, _BIT6); }
BOOL MHal_LD_Get_CompensationEn(void)                 { return MDrv_ReadRegBit(LD_REG(0x8C), _BIT6); }
// h47[6:0] reg_wid_st_offset_slv_chip
void MHal_LD_Set_LSF_SlaveFirst(U8 u8Blk)             { MDrv_WriteByte(LD_REG(0x8E), u8Blk); }
U8   MHal_LD_Get_LSF_SlaveFirst(void)                 { return MDrv_ReadByte(LD_REG(0x8E)); }
// h47[14:8] reg_wid_end_mas_chip
void MHal_LD_Set_LSF_MasterLast(U8 u8Blk)             { MDrv_WriteByte(LD_REG(0x8F), u8Blk); }
U8   MHal_LD_Get_LSF_MasterLast(void)                 { return MDrv_ReadByte(LD_REG(0x8F)); }
// h4b[7:0] reg_bl_globe
void MHal_LD_Set_BacklightGlobeGain(U8 u8Gain)        { MDrv_WriteByte(LD_REG(0x96), u8Gain); }
U8   MHal_LD_Get_BacklightGlobeGain(void)             { return MDrv_ReadByte(LD_REG(0x96)); }
// h4b[8] reg_bl_globe_mod
void MHal_LD_Set_BacklightGlobeMode(BOOL bMode)       { MDrv_WriteRegBit(LD_REG(0x97), bMode, _BIT0); }
BOOL MHal_LD_Get_BacklightGlobeMode(void)             { return MDrv_ReadRegBit(LD_REG(0x97), _BIT0); }
// h4b[10:9] reg_bl_data_alig
void MHal_LD_Set_BacklightDataAlign(U8 u8Align)       { MDrv_WriteByteMask(LD_REG(0x97), u8Align << 1, 0x06); }
U8   MHal_LD_Get_BacklightDataAlign(void)             { return (MDrv_ReadByte(LD_REG(0x97)) & 0x06) >> 1; }
// h4c[6:0] reg_bl_width
void MHal_LD_Set_LSF_BacklightWidth(U8 u8Width)       { MDrv_WriteByteMask(LD_REG(0x98), u8Width-1, 0x7F); }
U8   MHal_LD_Get_LSF_BacklightWidth(void)             { return (MDrv_ReadByte(LD_REG(0x98)) & 0x7F)+1; }
// h4c[14:8] reg_bl_height
void MHal_LD_Set_LSF_BacklightHeight(U8 u8Height)     { MDrv_WriteByteMask(LD_REG(0x99), u8Height-1, 0x7F); }
U8   MHal_LD_Get_LSF_BacklightHeight(void)            { return (MDrv_ReadByte(LD_REG(0x99)) & 0x7F)+1; }
// h4D[25:0] reg_baseaddr0_l
void MHal_LD_Set_LDB_FrameBufBaseAddr_L0(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0x9A), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_L0(void)        { return (MDrv_Read4Byte(LD_REG(0x9A)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h4F[25:0] reg_baseaddr1_l
void MHal_LD_Set_LDB_FrameBufBaseAddr_L1(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0x9E), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_L1(void)        { return (MDrv_Read4Byte(LD_REG(0x9E)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h51[25:0] reg_baseaddr0_r
void MHal_LD_Set_LDB_FrameBufBaseAddr_R0(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0xA2), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_R0(void)        { return (MDrv_Read4Byte(LD_REG(0xA2)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h53[25:0] reg_baseaddr1_r
void MHal_LD_Set_LDB_FrameBufBaseAddr_R1(U32 u32Addr) { MDrv_Write4Byte(LD_REG(0xA6), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_LDB_FrameBufBaseAddr_R1(void)        { return (MDrv_Read4Byte(LD_REG(0xA6)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h57[7:0] reg_dummy5
void MHal_LD_Set_SW_TemporalFilterLowTh(U8 u8Th)      { MDrv_WriteByte(LD_REG(0x4E), u8Th); }
U8   MHal_LD_Get_SW_TemporalFilterLowTh(void)         { return MDrv_ReadByte(LD_REG(0x4E)); }
// h57[15:8] reg_dummy5
void MHal_LD_Set_SW_TemporalFilterHighTh(U8 u8Th)     { MDrv_WriteByte(LD_REG(0x4F), u8Th); }
U8   MHal_LD_Get_SW_TemporalFilterHighTh(void)        { return MDrv_ReadByte(LD_REG(0x4F)); }
// h58[7:0] reg_dummy6
void MHal_LD_Set_SW_SpatialFilterStrength2(U8 u8Dist) { MDrv_WriteByte(LD_REG(0x4C), u8Dist); }
U8   MHal_LD_Get_SW_SpatialFilterStrength2(void)      { return MDrv_ReadByte(LD_REG(0x4C)); }
// h58[15:8] reg_dummy6
void MHal_LD_Set_SW_SpatialFilterStrength3(U8 u8Dist) { MDrv_WriteByte(LD_REG(0x4D), u8Dist); }
U8   MHal_LD_Get_SW_SpatialFilterStrength3(void)      { return MDrv_ReadByte(LD_REG(0x4D)); }
// h60[5:0] reg_bl_width_dma
void MHal_LD_Set_DMA_BacklightWidth(U8 u8Width)       { MDrv_WriteByteMask(LD_REG(0xC0), u8Width-1, 0x3F); }
U8   MHal_LD_Get_DMA_BacklightWidth(void)             { return (MDrv_ReadByte(LD_REG(0xC0)) & 0x3F)+1; }
// h60[13:8] reg_bl_height_dma
void MHal_LD_Set_DMA_BacklightHeight(U8 u8Height)     { MDrv_WriteByteMask(LD_REG(0xC1), u8Height-1, 0x3F); }
U8   MHal_LD_Get_DMA_BacklightHeight(void)            { return (MDrv_ReadByte(LD_REG(0xC1)) & 0x3F)+1; }
// h63[4:0] reg_bl_width_led
void MHal_LD_Set_LDB_BacklightWidth(U8 u8Width)       { MDrv_WriteByteMask(LD_REG(0xC6), u8Width-1, 0x3F); }
U8   MHal_LD_Get_LDB_BacklightWidth(void)             { return (MDrv_ReadByte(LD_REG(0xC6)) & 0x3F)+1; }
// h63[9:5] reg_bl_height_led
void MHal_LD_Set_LDB_BacklightHeight(U8 u8Height)     { MDrv_Write2ByteMask(LD_REG(0xC6), ((U16)u8Height-1) << 8, 0x3F00); }
U8   MHal_LD_Get_LDB_BacklightHeight(void)            { return ((MDrv_Read2Byte(LD_REG(0xC6)) & 0x3F00) >> 8)+1; }
// h64[3:0] reg_miu_pack_offset_0
void MHal_LD_Set_DMA0_PackOffset(U8 u8Offset)         { MDrv_WriteByteMask(LD_REG(0xC8), u8Offset, 0x1F); }
// h65[3:0] reg_miu_pack_length_0
void MHal_LD_Set_DMA0_PackLength(U8 u8Len)            { MDrv_WriteByteMask(LD_REG(0xCA), u8Len, 0x1F); }
// h65[8] reg_dma0_en
void MHal_LD_Set_DMA0_En(BOOL bEn)                    { MDrv_WriteRegBit(LD_REG(0xCB), bEn, _BIT0); }
BOOL MHal_LD_Get_DMA0_En(void)                        { return MDrv_ReadRegBit(LD_REG(0xCB), _BIT0); }
// h66[3:0] reg_miu_pack_offset_1
void MHal_LD_Set_DMA1_PackOffset(U8 u8Offset)         { MDrv_WriteByteMask(LD_REG(0xCC), u8Offset, 0x1F); }
// h67[3:0] reg_miu_pack_length_1
void MHal_LD_Set_DMA1_PackLength(U8 u8Len)            { MDrv_WriteByteMask(LD_REG(0xCE), u8Len, 0x1F); }
// h67[8] reg_dma1_en
void MHal_LD_Set_DMA1_En(BOOL bEn)                    { MDrv_WriteRegBit(LD_REG(0xCF), bEn, _BIT0); }
BOOL MHal_LD_Get_DMA1_En(void)                        { return MDrv_ReadRegBit(LD_REG(0xCF), _BIT0); }
// h68[3:0] reg_miu_pack_offset_2
void MHal_LD_Set_DMA2_PackOffset(U8 u8Offset)         { MDrv_WriteByteMask(LD_REG(0xD0), u8Offset, 0x1F); }
// h69[3:0] reg_miu_pack_length_2
void MHal_LD_Set_DMA2_PackLength(U8 u8Len)            { MDrv_WriteByteMask(LD_REG(0xD2), u8Len, 0x1F); }
// h69[8] reg_dma2_en
void MHal_LD_Set_DMA2_En(BOOL bEn)                    { MDrv_WriteRegBit(LD_REG(0xD3), bEn, _BIT0); }
BOOL MHal_LD_Get_DMA2_En(void)                        { return MDrv_ReadRegBit(LD_REG(0xD3), _BIT0); }
// h6a[3:0] reg_miu_pack_offset_3
void MHal_LD_Set_DMA3_PackOffset(U8 u8Offset)         { MDrv_WriteByteMask(LD_REG(0xD4), u8Offset, 0x1F); }
// h6b[3:0] reg_miu_pack_length_3
void MHal_LD_Set_DMA3_PackLength(U8 u8Len)            { MDrv_WriteByteMask(LD_REG(0xD6), u8Len, 0x1F); }
// h6b[8] reg_dma3_en
void MHal_LD_Set_DMA3_En(BOOL bEn)                    { MDrv_WriteRegBit(LD_REG(0xD7), bEn, _BIT0); }
BOOL MHal_LD_Get_DMA3_En(void)                        { return MDrv_ReadRegBit(LD_REG(0xD7), _BIT0); }
// h6c[5:0] reg_dma_yoff_end_0
void MHal_LD_Set_DMA0_YOffEnd(U8 u8End)               { MDrv_WriteByteMask(LD_REG(0xD8), u8End, 0x3F); }
// h6d[5:0] reg_dma_yoff_end_1
void MHal_LD_Set_DMA1_YOffEnd(U8 u8End)               { MDrv_WriteByteMask(LD_REG(0xDA), u8End, 0x3F); }
// h6e[5:0] reg_dma_yoff_end_2
void MHal_LD_Set_DMA2_YOffEnd(U8 u8End)               { MDrv_WriteByteMask(LD_REG(0xDC), u8End, 0x3F); }
// h6f[5:0] reg_dma_yoff_end_3
void MHal_LD_Set_DMA3_YOffEnd(U8 u8End)               { MDrv_WriteByteMask(LD_REG(0xDE), u8End, 0x3F); }
// h70[12:0] reg_frm_width
void MHal_LD_Set_FrameWidth(U16 u16Width)             { MDrv_Write2ByteMask(LD_REG(0xE0), u16Width-1, 0x1FFF); }
U16  MHal_LD_Get_FrameWidth(void)                     { return (MDrv_Read2Byte(LD_REG(0xE0)) & 0x1FFF)+1; }
// h71[11:0] reg_frm_height
void MHal_LD_Set_FrameHeight(U16 u16Height)           { MDrv_Write2ByteMask(LD_REG(0xE2), u16Height-1, 0x0FFF); }
U16  MHal_LD_Get_FrameHeight(void)                    { return (MDrv_Read2Byte(LD_REG(0xE2)) & 0x0FFF)+1; }
// h72[0] reg_debug_mod
void MHal_LD_Set_DebugMode(BOOL bMode)                { MDrv_WriteRegBit(LD_REG(0xE4), bMode, _BIT0); }
BOOL MHal_LD_Get_DebugMode(void)                      { return MDrv_ReadRegBit(LD_REG(0xE4), _BIT0); }
// h72[3:1] reg_lsf_out_mod
void MHal_LD_Set_LSFOutMode(U8 u8Mode)                { MDrv_WriteByteMask(LD_REG(0xE4), u8Mode << 1, 0x0E); }
U8   MHal_LD_Get_LSFOutMode(void)                     { return (MDrv_ReadByte(LD_REG(0xE4)) & 0x0E) >> 1; }
// h72[5:4] reg_comp_out_mod
void MHal_LD_Set_CompensationOutMode(U8 u8Mode)       { MDrv_WriteByteMask(LD_REG(0xE4), u8Mode << 4, 0x30); }
U8   MHal_LD_Get_CompensationOutMode(void)            { return (MDrv_ReadByte(LD_REG(0xE4)) & 0x30) >> 4; }
// h76[11:8] reg_dummy0
void MHal_LD_Set_SW_BacklightInGamma(U8 u8Type)       { MDrv_WriteByteMask(LD_REG(0xED), u8Type, 0x0F); }
U8   MHal_LD_Get_SW_BacklightInGamma(void)            { return MDrv_ReadByte(LD_REG(0xED)) & 0x0F; }
// h76[15:12] reg_dummy0
void MHal_LD_Set_SW_BacklightOutGamma(U8 u8Type)     { MDrv_WriteByteMask(LD_REG(0xED), u8Type<<4, 0xF0); }
U8   MHal_LD_Get_SW_BacklightOutGamma(void)          { return (MDrv_ReadByte(LD_REG(0xED)) >> 4) & 0x0F; }
// h77[25:0] reg_baseaddr_offset_spi_2
void MHal_LD_Set_SPI_BufBaseAddr_2(U32 u32Addr)       { MDrv_Write4Byte(LD_REG(0xEE), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_SPI_BufBaseAddr_2(void)              { return (MDrv_Read4Byte(LD_REG(0xEE)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }
// h78[15] reg_nxt_spi_access_en
void MHal_LD_Set_NextSpiAccessEn(BOOL bEn)            { MDrv_WriteRegBit(LD_REG(0xF0), bEn, _BIT7); }
BOOL MHal_LD_Get_NextSpiAccessEn(void)                { return MDrv_ReadRegBit(LD_REG(0xF0), _BIT7); }
// h79[25:0] reg_edge_2d_baseaddr
void MHal_LD_Set_Edge2D_BufBaseAddr(U32 u32Addr)      { MDrv_Write4Byte(LD_REG(0xF2), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD); }
U32  MHal_LD_Get_Edge2D_BufBaseAddr(void)             { return (MDrv_Read4Byte(LD_REG(0xF2)) & 0x1FFFFFF )*FRC_BYTE_PER_WORD; }

#if( CUR_CPU_IS_SEC_R2 == 0 )
// h7B[15] reg_spi_vsync_sel
void MHal_LD_Set_SPI_VsyncSel(BOOL bsrc)              { MDrv_WriteRegBit(LD_REG(0xF7), bsrc, _BIT7); }
// h7E[25:0] reg_baseaddr_offset
void MHal_LD_Set_SPI_BufBaseAddr(U32 u32Addr)         { MDrv_Write4Byte(LD_REG(0xFC), (u32Addr&0x3FFFFFFF)/FRC_BYTE_PER_WORD - MDrv_Read4Byte(LD_REG(0x9A)) - LD_DMA_PORT*MDrv_Read4Byte(LD_REG(0xEE))); }
U32  MHal_LD_Get_SPI_BufBaseAddr(void)                { return ((MDrv_Read4Byte(LD_REG(0x9A)) + MDrv_Read4Byte(LD_REG(0xFC)) + LD_DMA_PORT*MDrv_Read4Byte(LD_REG(0xEE))) & 0x1FFFFFF )*FRC_BYTE_PER_WORD ;}//+ ((LOCAL_DIMMING_MEMORY_TYPE&MIU1)?0x40000000:0); }
#endif

// h02[15:0] reg_ratio_h_lsf_cbmode
void MHal_LD_Set_LSF_CB_HInit(U16 u16Phase)           { MDrv_Write2Byte(LD2_REG(0x04), u16Phase); }
U16  MHal_LD_Get_LSF_CB_HInit(void)                   { return MDrv_Read2Byte(LD2_REG(0x04)); }
// h03[6:0] reg_led_h_dp_cnt_ini
void MHal_LD_Set_LED_SlaveFirst(U8 u8Led)             { MDrv_WriteByte(LD2_REG(0x06), u8Led); }
U8  MHal_LD_Get_LED_SlaveFirst(void)                  { return MDrv_ReadByte(LD2_REG(0x06)); }
// h20[0] reg_ld_coefdec
void MHal_LD_Set_CoefEncoding(BOOL bEnc)              { MDrv_WriteRegBit(LD2_REG(0x40), bEnc, _BIT0); }
BOOL MHal_LD_Get_CoefEncoding(void)                   { return MDrv_ReadRegBit(LD2_REG(0x40), _BIT0); }
// h20[1] reg_ld_edge2d_line_md
void MHal_LD_Set_Edge2DLineModeEn(BOOL bEn)           { MDrv_WriteRegBit(LD2_REG(0x40), bEn, _BIT1); }
BOOL MHal_LD_Get_Edge2DLineModeEn(void)               { return MDrv_ReadRegBit(LD2_REG(0x40), _BIT1); }
// h20[2] reg_ld_comp_low_gain_en
void MHal_LD_Set_CompensationLowEn(BOOL bEn)          { MDrv_WriteRegBit(LD2_REG(0x40), bEn, _BIT2); }
BOOL MHal_LD_Get_CompensationLowEn(void)              { return MDrv_ReadRegBit(LD2_REG(0x40), _BIT2); }
// h20[15:8] reg_ld_lsf_offset
void MHal_LD_Set_LSFOffset(U8 u8Offset)               { MDrv_WriteByte(LD2_REG(0x41), u8Offset); }
U8   MHal_LD_Get_LSFOffset(void)                      { return MDrv_ReadByte(LD2_REG(0x41)); }
// h3d[11:0] reg_comp_lut_2
void MHal_LD_Write_CompensationLowLUT(U16 u16Lut)     { MDrv_Write2ByteMask(LD2_REG(0x7A), u16Lut, 0x0FFF); }
// h3e[11:0] reg_r_comp_lut_2 (readonly)
U16  MHal_LD_Read_CompensationLowLUT(void)            { return MDrv_Read2Byte(LD2_REG(0x7C)) & 0x0FFF; }
// h3f[7:0] reg_comp_addr_2
void MHal_LD_Set_CompensationLowLUTAddress(U8 u8Addr) { MDrv_WriteByte(LD2_REG(0x7E), u8Addr); }
U8   MHal_LD_Get_CompensationLowLUTAddress(void)      { return MDrv_ReadByte(LD2_REG(0x7E)); }
// h3f[10] reg_comp_wd_2
void MHal_LD_Set_CompensationLowWriteEn(BOOL bEn)     { MDrv_WriteRegBit(LD2_REG(0x7F), bEn, _BIT2); }
BOOL MHal_LD_Get_CompensationLowWriteEn(void)         { return MDrv_ReadRegBit(LD2_REG(0x7F), _BIT2); }
// h3f[11] reg_comp_rd_2
void MHal_LD_Set_CompensationLowReadEn(BOOL bEn)      { MDrv_WriteRegBit(LD2_REG(0x7F), bEn, _BIT3); }
BOOL MHal_LD_Get_CompensationLowReadEn(void)          { return MDrv_ReadRegBit(LD2_REG(0x7F), _BIT3); }
// h3f[12] reg_comp_mod_2, 1:incremental
void MHal_LD_Set_CompensationLowMode(BOOL bMode)      { MDrv_WriteRegBit(LD2_REG(0x7F), bMode, _BIT4); }
BOOL MHal_LD_Get_CompensationLowMode(void)            { return MDrv_ReadRegBit(LD2_REG(0x7F), _BIT4); }

#if( CUR_CPU_IS_SEC_R2 == 0 )
#if ENABLE_TWO_SPI
void MHal_LD_Set_DmaMiuPack_Offset_Length(U8 offset1, U8 offset2, U8 len)
{
    MDrv_WriteByteMask(LD_REG(0xC8)+4*LD_DMA_PORT, offset1&0x1F, 0x1F) ; //reg_miu_pack_offset_x
    MDrv_WriteByteMask(LD_REG(0xCA)+4*LD_DMA_PORT, len&0x1F, 0x1F) ; //reg_miu_pack_length_x

    MDrv_WriteByteMask(LD_REG(0xC8)+4*LD_DMA_PORT2, offset2&0x1F, 0x1F) ; //reg_miu_pack_offset_x
    MDrv_WriteByteMask(LD_REG(0xCA)+4*LD_DMA_PORT2, len&0x1F, 0x1F) ; //reg_miu_pack_length_x

}
#elif ENABLE_FOUR_SPI
void MHal_LD_Set_DmaMiuPack_Offset_Length(U8 offset1, U8 offset2,U8 offset3,U8 offset4, U8 len)
{
    MDrv_WriteByteMask(LD_REG(0xC8)+4*LD_DMA_PORT, offset1&0x1F, 0x1F) ; //reg_miu_pack_offset_x
    MDrv_WriteByteMask(LD_REG(0xCA)+4*LD_DMA_PORT, len&0x1F, 0x1F) ; //reg_miu_pack_length_x

    MDrv_WriteByteMask(LD_REG(0xC8)+4*LD_DMA_PORT2, offset2&0x1F, 0x1F) ; //reg_miu_pack_offset_x
    MDrv_WriteByteMask(LD_REG(0xCA)+4*LD_DMA_PORT2, len&0x1F, 0x1F) ; //reg_miu_pack_length_x

	MDrv_WriteByteMask(LD_REG(0xC8)+4*LD_DMA_PORT3, offset3&0x1F, 0x1F) ; //reg_miu_pack_offset_x
	MDrv_WriteByteMask(LD_REG(0xCA)+4*LD_DMA_PORT3, len&0x1F, 0x1F) ; //reg_miu_pack_length_x

	MDrv_WriteByteMask(LD_REG(0xC8)+4*LD_DMA_PORT4, offset4&0x1F, 0x1F) ; //reg_miu_pack_offset_x
	MDrv_WriteByteMask(LD_REG(0xCA)+4*LD_DMA_PORT4, len&0x1F, 0x1F) ; //reg_miu_pack_length_x
}
#else
void MHal_LD_Set_DmaMiuPack_Offset_Length(U8 offset, U8 len)
{
    MDrv_WriteByteMask(LD_REG(0xC8)+4*LD_DMA_PORT, offset&0x1F, 0x1F) ; //reg_miu_pack_offset_x
    MDrv_WriteByteMask(LD_REG(0xCA)+4*LD_DMA_PORT, len&0x1F, 0x1F) ; //reg_miu_pack_length_x

//    MDrv_Write2Byte(LD_REG(0xD4), 0x0); // offset
//    MDrv_Write2Byte(LD_REG(0xD6), 0x010F); // een, all depack [4-0]= 0xF , [5] enable DMA access  , DMA get 128 bit data one time , one piece 8 bit
}
#endif
void MHal_LD_Set_DmaEnable(BOOL bEn)
{
    MDrv_WriteByteMask(LD_REG(0xCB)+4*LD_DMA_PORT, bEn&0x01, 0x01) ; //DMA_x enable
    #if ENABLE_TWO_SPI
    MDrv_WriteByteMask(LD_REG(0xCB)+4*LD_DMA_PORT2, bEn&0x01, 0x01) ; //DMA_x enable
    #elif ENABLE_FOUR_SPI
    MDrv_WriteByteMask(LD_REG(0xCB)+4*LD_DMA_PORT2, bEn&0x01, 0x01) ; //DMA_x enable
    MDrv_WriteByteMask(LD_REG(0xCB)+4*LD_DMA_PORT3, bEn&0x01, 0x01) ; //DMA_x enable
    MDrv_WriteByteMask(LD_REG(0xCB)+4*LD_DMA_PORT4, bEn&0x01, 0x01) ; //DMA_x enable
    #endif

}
void MHal_LD_Set_DmaAccessYEnd(U8 ylen)
{
    MDrv_WriteByteMask(LD_REG(0xD8)+2*LD_DMA_PORT, ylen&0x3F, 0x3F) ; //DMA access y end
    #if ENABLE_TWO_SPI
    MDrv_WriteByteMask(LD_REG(0xD8)+2*LD_DMA_PORT2, ylen&0x3F, 0x3F) ; //DMA access y end
    #elif ENABLE_FOUR_SPI
    MDrv_WriteByteMask(LD_REG(0xD8)+2*LD_DMA_PORT2, ylen&0x3F, 0x3F) ; //DMA access y end
    MDrv_WriteByteMask(LD_REG(0xD8)+2*LD_DMA_PORT3, ylen&0x3F, 0x3F) ; //DMA access y end
    MDrv_WriteByteMask(LD_REG(0xD8)+2*LD_DMA_PORT4, ylen&0x3F, 0x3F) ; //DMA access y end
    #endif
}
#endif // #if( CUR_CPU_IS_SEC_R2 == 0 )

#endif // LD_ENABLE

