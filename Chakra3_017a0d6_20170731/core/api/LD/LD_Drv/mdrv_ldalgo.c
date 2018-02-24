#define _MDRV_LDALGO_C_

#include "Board.h"

#if( LD_ENABLE && LD_ALGO_ENABLE )

#if( CUR_CPU_IS_SEC_R2 )
    #include "datatype.h"
    #include "drvGlobal.h"
#endif

#include "mhal_ld.h"

#include "mdrv_ldalgo.h"


//=========================================================
//extern t_sDrvLdCusPtrMap sCusPtrMap;

//extern U8* Tbl_LD_Remap[16];
//extern U8* Tbl_LD_Gamma[16];

#if(0==LD_ALGO_RUN_IN_CROP)
void MApi_LD_Set_HasNewLedData(void);
#endif

//==========================================================

#define LD_MEM_MODE
#define LD_OVERFLOW_FEEDBACK


#define LD_ALGO_KIM_DEBUG   0


#ifdef LD_HISTOGRAM
static U16 HISTOGRAM_bins[32];
#endif

#ifdef LD_OVERFLOW_FEEDBACK
static U16 OVF_blocks[LD_MAX_BLOCK_SIZE] ={0};
#endif

static U16 au16SD_Mean_blocks[LD_MAX_BLOCK_SIZE]={0};
static U16 au16SD_Max_blocks[LD_MAX_BLOCK_SIZE]={0};

U16 g_LDAlgo_SPI_blocks[LD_MAX_BLOCK_SIZE]={0};

static U16 s_LdAlgo_u16LedWidth = 0;
static U16 s_LdAlgo_u16LedHeight = 0;
static U16 s_LdAlgo_u16LedNums = 0;

static U16* s_LDAlgo_pu16OutLedBuf = NULL;
static U32 s_LDAlgo_u32OutLedBufSize = 0;

//----------------------------------------------------

static Typ_Tbl_LD_Gamma* s_LdAlgo_Tbl_LD_Gamma;
static Typ_Tbl_LD_Remap* s_LdAlgo_Tbl_LD_Remap;

//static U16* s_LDAlgo_pu16OutLedData = NULL;

//==========================================================

#define LD_ALGO_min(a,b)    (((a) < (b)) ? (a) : (b))
#define LD_ALGO_max(a,b)    (((a) > (b)) ? (a) : (b))

#define LD_ALGO_TBL_GAMMA   s_LdAlgo_Tbl_LD_Gamma
#define LD_ALGO_TBL_REMAP   s_LdAlgo_Tbl_LD_Remap

//==========================================================

void MDrv_LDAlgo_Init(StuLdAlgoInit* pstLdAlgoInit)
{
    U8 u8ErrorCnt = 0;

    printf("MDrv_LDAlgo_Init()\n");

    s_LdAlgo_u16LedWidth = MHal_LD_Get_LED_BacklightWidth();
    printf("s_LdAlgo_u16LedWidth=%u\n", s_LdAlgo_u16LedWidth);
    if( s_LdAlgo_u16LedWidth > LD_MAX_BLOCK_WIDTH )
    {
        printf("\nError: s_LdAlgo_u16LedWidth=%u\n", s_LdAlgo_u16LedWidth);
        s_LdAlgo_u16LedWidth = 1;
        u8ErrorCnt += 1;
    }

    s_LdAlgo_u16LedHeight = MHal_LD_Get_LED_BacklightHeight();
    printf("s_LdAlgo_u16LedHeight=%u\n", s_LdAlgo_u16LedHeight);
    if( s_LdAlgo_u16LedHeight > LD_MAX_BLOCK_HEIGHT )
    {
        printf("\nError: s_LdAlgo_u16LedHeight=%u\n", s_LdAlgo_u16LedHeight);
        s_LdAlgo_u16LedHeight = 1;
        u8ErrorCnt += 1;
    }

    s_LdAlgo_u16LedNums = s_LdAlgo_u16LedWidth * s_LdAlgo_u16LedHeight;
    printf("s_LdAlgo_u16LedNums=%u\n", s_LdAlgo_u16LedNums);
    if( s_LdAlgo_u16LedNums > LD_MAX_BLOCK_SIZE )
    {
        printf("s_LdAlgo_u16LedNums=%u\n", s_LdAlgo_u16LedNums);
        s_LdAlgo_u16LedNums = 1;
        u8ErrorCnt += 1;
    }

    if( u8ErrorCnt > 0 )
    {
        while(1){}
    }


    // Check share mem magic ID
    if( MHal_LD_Get_ShareMem(E_LD_INFO_MAGIC_ID) != LD_SHARE_MEM_MAGIC_ID )
    {
        printf("Share memory magic id is wrong (0x%X)!", MHal_LD_Get_ShareMem(E_LD_INFO_MAGIC_ID));
        while(1){}
    }

    // Get info from APP
    //printf("Tbl_LD_Gamma=0x%X\n", (U32)(Tbl_LD_Gamma));
    //printf("Sizeof(Tbl_LD_Gamma)=%u\n", sizeof(Tbl_LD_Gamma));

    //s_LdAlgo_Tbl_LD_Gamma = (Typ_Tbl_LD_Gamma*) MsOS_PA2KSEG0( MHal_LD_Get_ShareMem(E_LD_INFO_GAMMA_TBL_ADDR) );
    //s_LdAlgo_Tbl_LD_Remap = (Typ_Tbl_LD_Remap*) MsOS_PA2KSEG0( MHal_LD_Get_ShareMem(E_LD_INFO_REMAP_TBL_ADDR) );

    s_LdAlgo_Tbl_LD_Gamma = pstLdAlgoInit->p_LdAlgo_Tbl_LD_Gamma;
    s_LdAlgo_Tbl_LD_Remap = pstLdAlgoInit->p_LdAlgo_Tbl_LD_Remap;

    printf("s_LdAlgo_Tbl_LD_Gamma=0x%X\n", (U32)(s_LdAlgo_Tbl_LD_Gamma));
    //printf("s_LdAlgo_Tbl_LD_Gamma[1]=0x%X\n", (U32)(s_LdAlgo_Tbl_LD_Gamma[1]));
    printf("s_LdAlgo_Tbl_LD_Remap=0x%X\n", (U32)(s_LdAlgo_Tbl_LD_Remap));

    //printf("ShaerMem-E_LD_INFO_ALOG_OUT_LED_BUF_ADDR=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_ADDR));
    //s_LDAlgo_pu16OutLedBuf = (U16*) MsOS_PA2KSEG1( MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_ADDR) );
    s_LDAlgo_pu16OutLedBuf = pstLdAlgoInit->pu16OutLedBuf;
    printf("s_LDAlgo_pu16OutLedBuf=0x%X\n", (U32)(s_LDAlgo_pu16OutLedBuf));

    //printf("ShaerMem-E_LD_INFO_ALOG_OUT_LED_BUF_SIZE=0x%X\n", MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_SIZE));
    //s_LDAlgo_u32OutLedBufSize = MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_SIZE);
    s_LDAlgo_u32OutLedBufSize = pstLdAlgoInit->u32OutLedBufSize;
    printf("s_LDAlgo_u32OutLedBufSize=0x%X\n", (U32)(s_LDAlgo_u32OutLedBufSize));


    // Send info to APP
    printf("g_LDAlgo_SPI_blocks=0x%X\n", (U32)g_LDAlgo_SPI_blocks);
    MHal_LD_Set_ShareMem(E_LD_INFO_ALGO_SPI_BLOCK_ADR, MsOS_VA2PA( (U32)g_LDAlgo_SPI_blocks) );
}

/*
U32 MDrv_LDAlgo_Get_SPI_blocks(void)
{
    return MsOS_VA2PA((U32)g_LDAlgo_SPI_blocks);
}
*/

// Assertion : 0 <= IN_blocks[block_idx] < 0xFF00 ----> 0 <= SPI_blocks[block_idx] < 0xFFFF, 0 <= LDB_blocks[block_idx] < 0xFF
void MDrv_LDAlgo_PostProcess(const U16* IN_blocks, U16* SPI_blocks, U8* LDB_blocks)
{
    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;

    U16 n_leds = led_width * led_height;
    U16 block_idx = 0;

    // Form SPI signal & LDB data
    for (block_idx = 0; block_idx < n_leds; block_idx++)
    {
        U16 backlight = IN_blocks[block_idx];
        // transform (0, ..., 0xFF00) to (0, ..., 0xFFFF)
        SPI_blocks[block_idx] = backlight + (backlight >> 8);
        // rounding to 8-bit
        LDB_blocks[block_idx] = (backlight + 0x80) >> 8;
    }

#ifdef LD_MEM_MODE
    static BOOL MEM_init = FALSE;
    static U16 MEM_blocks[LD_MAX_BLOCK_SIZE]; // for measurement
    if (!MEM_init)
    {
        for (block_idx = 0; block_idx < n_leds; block_idx++)
            MEM_blocks[block_idx] = 0;
        MEM_init = TRUE;
    }
#endif

    U8 led_mod = MHal_LD_Get_SW_PulseMode();
    U16 led_id = MHal_LD_Get_SW_PulseId();
    U16 led_str = MHal_LD_Get_SW_PulseLEDIntensity();
    U16 ldb_str = MHal_LD_Get_SW_PulseLDBIntensity();
    if (led_mod == 0x0)
    {
        if (led_id == 0x1) // Left: right LSF, Right: LD on
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
            {
                if (block_idx % led_width >= led_width/2)
                {
                    SPI_blocks[block_idx] = (led_str << 8) | led_str;
                    LDB_blocks[block_idx] = led_str;
                }
            }
        }
        else if (led_id == 0x2) // Left: LD off, Right: LD on
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
            {
                if (block_idx % led_width < led_width/2)
                {
                    SPI_blocks[block_idx] = (led_str << 8) | led_str;
                    LDB_blocks[block_idx] = led_str;
                }
            }
        }
        else if (led_id == 0x3) // Left: LD on, Right: left LSF
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
            {
                if (block_idx % led_width >= led_width/2)
                {
                    SPI_blocks[block_idx] = SPI_blocks[block_idx - led_width/2];
                    LDB_blocks[block_idx] = LDB_blocks[block_idx - led_width/2];
                }
            }
        }
        else if (led_id == 0x4) // Left: right LSF, Right: LD on
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
            {
                if (block_idx % led_width < led_width/2)
                {
                    SPI_blocks[block_idx] = SPI_blocks[block_idx + led_width/2];
                    LDB_blocks[block_idx] = LDB_blocks[block_idx + led_width/2];
                }
            }
        }
    }
    else if (led_mod == 0xf)     // 22[15:12]=4'b1111  real backlight
    {
        if (led_id == 0xfff)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                SPI_blocks[block_idx] = 0xffff;
        }
        else if (led_id < n_leds)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                SPI_blocks[block_idx] = 0;
            SPI_blocks[led_id] = 0xffff;
        }
        MHal_LD_Set_LSFOutMode(0x1);
    }
    else if (led_mod == 0xe)      // 22[15:12]=4'b1110  digital backlight
    {
        for (block_idx = 0; block_idx < n_leds; block_idx++)
            SPI_blocks[block_idx] = 0xffff;
        if (led_id == 0xfff)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                LDB_blocks[block_idx] = 0xff;
        }
        else if (led_id < n_leds)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                LDB_blocks[block_idx] = 0;
            LDB_blocks[led_id] = 0xff;
        }
        MHal_LD_Set_LSFOutMode(0x5);
    }
    else if (led_mod == 0xd)      // 22[15:12]=4'b1101 tunable real backlight
    {
        if (led_id == 0xfff)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                SPI_blocks[block_idx] = (led_str << 8) | ldb_str;;
        }
        else if (led_id < n_leds)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                SPI_blocks[block_idx] = 0;
            SPI_blocks[led_id] = (led_str << 8) | ldb_str;;
        }
    }
    else if (led_mod == 0xc)      // 22[15:12]=4'b1100 tunable digital backlight
    {
        for (block_idx = 0; block_idx < n_leds; block_idx++)
            SPI_blocks[block_idx] = (led_str << 8) | led_str;
        if (led_id == 0xfff)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                LDB_blocks[block_idx] = ldb_str;
        }
        else if (led_id < n_leds)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                LDB_blocks[block_idx] = 0;
            LDB_blocks[led_id] = ldb_str;
        }
    }
#ifdef LD_MEM_MODE
    else if (led_mod == 0xb)      // 22[15:12]=4'b1011 set SPI
    {
        if (led_id == 0xfff)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                SPI_blocks[block_idx] = MEM_blocks[block_idx] = (led_str << 8) | ldb_str;
        }
        else if (led_id < n_leds)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                SPI_blocks[block_idx] = MEM_blocks[block_idx];
            SPI_blocks[led_id] = MEM_blocks[led_id] = (led_str << 8) | ldb_str;;
        }
    }
    else if (led_mod == 0xa)      // 22[15:12]=4'b1010 set LDB
    {
        for (block_idx = 0; block_idx < n_leds; block_idx++)
            SPI_blocks[block_idx] = (led_str << 8) | led_str;
        if (led_id == 0xfff)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                LDB_blocks[block_idx] = MEM_blocks[block_idx] = ldb_str;
        }
        else if (led_id < n_leds)
        {
            for (block_idx = 0; block_idx < n_leds; block_idx++)
                LDB_blocks[block_idx] = MEM_blocks[block_idx];
            LDB_blocks[led_id] = MEM_blocks[led_id] = ldb_str;
        }
    }
#endif
}

void MDrv_LDAlgo_LocalDimmingStrength(U16* BL_blocks)
{
    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;


    U16 n_leds = led_width * led_height;
    U16 block_idx = 0;

    U32 ld_str = MHal_LD_Get_SW_LocalDimmingStrength(); // 0 ~ 0xFF
    ld_str = (ld_str > 0x80) ? ld_str+1 : ld_str;

    U16 min_bl_val = MHal_LD_Get_SW_MinClampValue();
    min_bl_val <<= 8; // 0 ~ 0xFF00

    U16 bl_val = 0;
    for (block_idx = 0; block_idx < n_leds; block_idx++)
    {
        bl_val = (BL_blocks[block_idx] * ld_str + 0xff00 * (256 - ld_str) + 0x80) >> 8; // 0 ~ 0xFF00
        if (bl_val < min_bl_val)
            bl_val = min_bl_val;
        BL_blocks[block_idx] = bl_val;
    }
}

// Assertion : 0 <= BL_blocks[block_idx] <= 0xFFFF
void MDrv_LDAlgo_GlobalDimmingStrength(U16* BL_blocks)
{
    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;

    U16 n_leds = led_width * led_height;
    U16 block_idx = 0;

    U32 gd_str = MHal_LD_Get_SW_GlobalDimmingStrength(); // 0 ~ 0xFF
    for (block_idx = 0; block_idx < n_leds; block_idx++)
        BL_blocks[block_idx] = (BL_blocks[block_idx] * gd_str) / 255;
}

#ifdef LD_HISTOGRAM
void MDrv_LDAlgo_GenHistogram(const U16* SD_blocks)
{
    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;

    U16 n_leds = led_width * led_height;

    U16 block_idx = 0, bin_idx = 0;
    for (bin_idx = 0; bin_idx < 32; bin_idx++)
        HISTOGRAM_bins[bin_idx] = 0;
    for (block_idx = 0; block_idx < n_leds; block_idx++)
        HISTOGRAM_bins[SD_blocks[block_idx] >> 12] ++;
}
#endif

// Assertion : 0 <= LDF_blocks[block_idx] <= 0xFF ----> 0 <= SD_blocks[block_idx] <= 0xFF00
void MDrv_LDAlgo_ScalingDown(const U8* LDF_blocks, U16* SD_blocks)
{
    U16 ldf_width = MHal_LD_Get_LDF_BacklightWidth();
    U16 ldf_height = MHal_LD_Get_LDF_BacklightHeight();
//    U16 led_width = MHal_LD_Get_LED_BacklightWidth();
  //  U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;

    U16 n_leds = led_width * led_height;
    U16 hsd_factor = ldf_width / led_width;
    U16 vsd_factor = ldf_height / led_height;
    if (hsd_factor==0 || vsd_factor == 0)
        return;
    U16 LDF_idx = 0, SD_idx = 0, i = 0, j = 0;

    U16 SortMax_blocks[LD_MAX_BLOCK_WIDTH*LD_MAX_BLOCK_HEIGHT];
    U16 m = 0, n = 0, k = 0;//, insert_idx =0; //, insert_idx = 0;
    U16 u16Max_nth = LD_ALGO_min((U16)MHal_LD_Get_SW_MaxThreshold(), hsd_factor*vsd_factor - 1);
#ifdef LD_OVERFLOW_FEEDBACK
    U32 overflow_cur = 0;
#endif

    for (SD_idx = 0; SD_idx < n_leds; SD_idx++)
        SD_blocks[SD_idx] = 0;

    U32 alpha = MHal_LD_Get_LDF_DCMaxAlpha();
    U32 block_cur = 0, block_mean = 0, block_max = 0; // 0 ~ 0xFF00
    if (MHal_LD_Get_LDF_WriteDCMaxOFEn()) // 4 bytes : OF[15:8] OF[7:0] Max DC
    {
        for (n = 0; n < led_height; n++)
        {
            for (m = 0; m < led_width; m++)
            {
                SD_idx = m + n*led_width;

                for (k = 0; k <= u16Max_nth; k++)
                    SortMax_blocks[k] = 0;

                block_mean = 0;
                overflow_cur = 0;
                for (j = 0; j < vsd_factor; j++)
                {
                    for (i = 0; i < hsd_factor; i++)
                    {
                        LDF_idx = (i + m*hsd_factor) + (j + n*vsd_factor)*ldf_width;

                        // mean
                        block_mean += LDF_blocks[LDF_idx*4];
                        // max
                        block_max = LDF_blocks[LDF_idx*4 + 1];
                        if (block_max > SortMax_blocks[u16Max_nth])
                        {
                            for (k = u16Max_nth+1; k > 0; k--)
                            {
                                if (block_max <= SortMax_blocks[k-1])
                                    break;
                                SortMax_blocks[k] = SortMax_blocks[k-1];
                            }
                            SortMax_blocks[k] = block_max;
                        }
#ifdef LD_OVERFLOW_FEEDBACK
                        overflow_cur += (((U16)LDF_blocks[LDF_idx*4 + 3]) << 8) | LDF_blocks[LDF_idx*4 + 2];
#endif
                    }
                }
                block_mean = (block_mean << 8) / (hsd_factor * vsd_factor);
                block_max = SortMax_blocks[u16Max_nth] << 8;

                if (block_mean > block_max)
                    block_mean=block_max;

                block_cur = (alpha * block_max + (8-alpha) * block_mean + (0x1 << 2)) >> 3;
                SD_blocks[SD_idx] = block_cur;
                au16SD_Mean_blocks[SD_idx]=block_mean;
                au16SD_Max_blocks[SD_idx]=block_max;

#ifdef LD_OVERFLOW_FEEDBACK
                overflow_cur = LD_ALGO_min(overflow_cur*n_leds>>10, 0xFFFF); // normalize to 32x32 LEDs
                OVF_blocks[SD_idx] = overflow_cur;
#endif
            }
        }
    }
    else if (MHal_LD_Get_LDF_WriteDCMaxEn()) // 2 bytes : Max DC
    {
        for (n = 0; n < led_height; n++)
        {
            for (m = 0; m < led_width; m++)
            {
                SD_idx = m + n*led_width;

                for (k = 0; k <= u16Max_nth; k++)
                    SortMax_blocks[k] = 0;

                block_mean = 0;
                for (j = 0; j < vsd_factor; j++)
        {
                    for (i = 0; i < hsd_factor; i++)
            {
                        LDF_idx = (i + m*hsd_factor) + (j + n*vsd_factor)*ldf_width;

                        // mean
                        block_mean += LDF_blocks[LDF_idx*2];
                        // max
                block_max = LDF_blocks[LDF_idx*2 + 1];

                        if (block_max > SortMax_blocks[u16Max_nth])
                        {
                            for (k = u16Max_nth+1; k > 0; k--)
                            {
                                if (block_max <= SortMax_blocks[k-1])
                                    break;
                                SortMax_blocks[k] = SortMax_blocks[k-1];
                            }
                            SortMax_blocks[k] = block_max;
                        }
                    }
                }
                block_mean = (block_mean << 8) / (hsd_factor * vsd_factor);
                block_max = SortMax_blocks[u16Max_nth] << 8;

                if (block_mean > block_max)
                    block_mean=block_max;

                block_cur = (alpha * block_max + (8-alpha) * block_mean + (0x1 << 2)) >> 3;
                SD_blocks[SD_idx] = block_cur;
                au16SD_Mean_blocks[SD_idx]=block_mean;
                au16SD_Max_blocks[SD_idx]=block_max;

            }
        }
    }
    else // 1 bytes : BLEND
    {
        for (j = 0; j < ldf_height; j++)
        {
            for (i = 0; i < ldf_width; i++)
            {
                LDF_idx = i + j*ldf_width;
                block_cur = LDF_blocks[LDF_idx];
                block_cur <<= 8;

                SD_idx = (i / hsd_factor) + (j / vsd_factor)*led_width;
                if (block_cur > SD_blocks[SD_idx])
                    SD_blocks[SD_idx] = block_cur;
            }
        }
    }
#ifdef LD_HISTOGRAM
    MDrv_LDAlgo_GenHistogram(SD_blocks);
#endif
}

void MDrv_LDAlgo_BacklightGamma(U16* BL_blocks, const U8* Table)
{
    if (!Table)
        return;

    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;


    U16 n_leds = led_width * led_height;
    U16 block_idx = 0;
    U16 bl_msb = 0, bl_lsb = 0; // 0 ~ 0xFF
    U32 bl_low = 0, bl_high = 0; // 0 ~ 0xFF00
    for (block_idx = 0; block_idx < n_leds; block_idx++)
    {
        bl_msb = BL_blocks[block_idx] >> 8;
        bl_lsb = BL_blocks[block_idx] & 0xFF;
        bl_low = Table[bl_msb];
        bl_low <<= 8;
        bl_high = Table[(bl_msb == 0xFF) ? bl_msb : bl_msb + 1];
        bl_high <<= 8;
        BL_blocks[block_idx] = ((256-bl_lsb)*bl_low + bl_lsb*bl_high + 0x80) >> 8;
    }
}

U32 MDrv_LDAlgo_CalcTemporalFilterStrength(U32 str_in, U16 luma_diff, U16 luma_high, U16 luma_low)
{
    U32 str_out;

    if (luma_diff >= luma_high)
    {
        str_out = 0;
    }
    else if (luma_diff <= luma_low)
    {
        str_out = str_in;
    }
    else
    {
        if (luma_high == luma_low)
            return 0xFFFFFFFF;
        str_out = str_in * (luma_high - luma_diff) / (luma_high - luma_low);
    }

    return str_out;
}

// Assertion : 0 <= IN_blocks[block_idx] <= 0xFF00 ----> 0 <= OUT_blocks[block_idx] <= 0xFF00
void MDrv_LDAlgo_TemporalFilter(const U16* IN_blocks, U16* OUT_blocks)
{
    static U16 luma_pre = 0; // 0 ~ 0xFF00
    static U16 PRE_blocks[LD_MAX_BLOCK_SIZE];

    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;

    U16 n_leds = led_width * led_height;
    U16 block_idx = 0;

    U32 tf_strength_dn = MHal_LD_Get_SW_TemporalFilterStrengthDn(); // 0 ~ 0xFF
    U32 tf_strength_up = MHal_LD_Get_SW_TemporalFilterStrengthUp(); // 0 ~ 0xFF
    U32 luma_low = MHal_LD_Get_SW_TemporalFilterLowTh(); luma_low <<= 8; // 0 ~ 0xFF
    U32 luma_high = MHal_LD_Get_SW_TemporalFilterHighTh(); luma_high <<= 8; // 0 ~ 0xFF
    U16 max_speed = MHal_LD_Get_SW_TemporalFilterMaxSpeed(); max_speed <<= 8; // 0~0xFF

    // get frame average luma
    U32 luma_cur = 0;
    for (block_idx = 0; block_idx < n_leds; block_idx++)
        luma_cur += IN_blocks[block_idx];
    luma_cur = (luma_cur + n_leds/2) / n_leds; // 0 ~ 0xFF00

    // calc IIR alpha based on frame average
    U16 luma_diff = (luma_cur > luma_pre) ? luma_cur - luma_pre : luma_pre - luma_cur; // 0 ~ 0xFF00
    U32 alpha_up = MDrv_LDAlgo_CalcTemporalFilterStrength(tf_strength_up, luma_diff, luma_high, luma_low); // 0 ~ 0xFF
    U32 alpha_dn = MDrv_LDAlgo_CalcTemporalFilterStrength(tf_strength_dn, luma_diff, luma_high, luma_low); // 0 ~ 0xFF
    luma_pre = luma_cur;

    U32 alpha = 0;
    U16 block_cur = 0, block_pre = 0;
    for (block_idx = 0; block_idx < n_leds; block_idx++)
    {
        block_cur = IN_blocks[block_idx]; // 0 ~ 0xFF00
        block_pre = PRE_blocks[block_idx]; // 0 ~ 0xFF00

        alpha = (block_cur > block_pre)
              ? (MHal_LD_Get_SW_TemporalFilterStyle() == LD_TF_MSTAR) ? alpha_up
                      : MDrv_LDAlgo_CalcTemporalFilterStrength(tf_strength_up, block_cur - block_pre, luma_high, luma_low)
              : (MHal_LD_Get_SW_TemporalFilterStyle() == LD_TF_MSTAR) ? alpha_dn
                      : MDrv_LDAlgo_CalcTemporalFilterStrength(tf_strength_dn, block_pre - block_cur, luma_high, luma_low);

        // 16-bit IIR
        block_cur = (alpha*block_pre + (256-alpha)*block_cur + 0x80) >> 8;
        if (block_cur == block_pre)
        {
            if (block_cur < IN_blocks[block_idx])
                block_cur ++;
            else if (block_cur > IN_blocks[block_idx])
                block_cur --;
        }

        // limit the max speed
        if (max_speed > 0)
        {
            if (block_cur > block_pre && block_cur - block_pre > max_speed)
                block_cur = block_pre + max_speed;
            else if (block_cur < block_pre && block_pre - block_cur > max_speed)
                block_cur = block_pre - max_speed;
        }

        OUT_blocks[block_idx] = block_cur;
        PRE_blocks[block_idx] = block_cur;
    }
}

// Assertion : 0 <= IN_blocks[block_idx] <= 0xFF00 ----> 0 <= OUT_blocks[block_idx] <= 0xFF00
void MDrv_LDAlgo_SpatialFilter(const U16* IN_blocks, U16* OUT_blocks)
{
    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;

    U16 n_leds = led_width * led_height;
    U16 block_idx = 0, neighbor_idx = 0;
    for (block_idx = 0; block_idx < n_leds; block_idx++)
        OUT_blocks[block_idx] = IN_blocks[block_idx];

    int i = 0, j = 0, k = 0, p = 0, q = 0;
    U16 sf_str[5];
    sf_str[0] = MHal_LD_Get_SW_SpatialFilterStrength1();
    sf_str[1] = MHal_LD_Get_SW_SpatialFilterStrength2();
    sf_str[2] = MHal_LD_Get_SW_SpatialFilterStrength3();
    sf_str[3] = MHal_LD_Get_SW_SpatialFilterStrength4();
    sf_str[4] = MHal_LD_Get_SW_SpatialFilterStrength5();

    //EnuLD_LED_TYPE led_type = (EnuLD_LED_TYPE)MHal_LD_Get_LEDType();
    if ( MHal_LD_Get_SW_SpatialFilterStyle() /*== LD_SF_LINEAR*/) // linear style
    {
        if (1) // anti-dumbness
        {
            // Make sure (sf_str[0] + 2*sf_str[1] + 2*sf_str[2] + 3*sf_str[3] + 4*sf_str[4] == 256)
            U16 str_left = 256;
            str_left -= sf_str[0];
            if ((str_left >> 1) < sf_str[1])
                sf_str[1] = str_left >> 1;
            str_left -= (sf_str[1] << 1);
            if ((str_left >> 1) < sf_str[2])
                sf_str[2] = str_left >> 1;
            str_left -= (sf_str[2] << 1);
            if ((str_left >> 1) < sf_str[3])
                sf_str[3] = str_left >> 1;
            str_left -= (sf_str[3] << 1);
            if ((str_left >> 1) < sf_str[4])
                sf_str[4] = str_left >> 1;
            str_left -= (sf_str[4] << 1);
            sf_str[0] += str_left;
        }

        U32 block_sum = 0;
        if (led_height <= 2) //(led_type == HAL_LD_EDGE_TB_TYPE)
        {
            U8 nk = (sf_str[4] > 0) ? 5 : (sf_str[3] > 0) ? 4 : (sf_str[2] > 0) ? 3 : (sf_str[1] > 0) ? 2 : 1;
            for (j = 0; j < 2; j++) // led_height == 2
            {
                for (i = 0; i < led_width; i++)
                {
                    block_idx = i + led_width*j;
                    block_sum = IN_blocks[block_idx] * sf_str[0];
                    for (k = 1; k < nk; k++)
                    {
                        p = LD_ALGO_max(i - k, 0); // left
                        neighbor_idx = p + led_width*j;
                        block_sum += (U32)IN_blocks[neighbor_idx] * sf_str[k];

                        p = LD_ALGO_min(i + k, led_width-1); // right
                        neighbor_idx = p + led_width*j;
                        block_sum += (U32)IN_blocks[neighbor_idx] * sf_str[k];
                    }
                    OUT_blocks[block_idx] = LD_ALGO_max(IN_blocks[block_idx], (block_sum + 0x80) >> 8);
                }
            }
        }
        else if (led_width <= 2) //(led_type == HAL_LD_EDGE_LR_TYPE)
        {
            U8 nk = (sf_str[4] > 0) ? 5 : (sf_str[3] > 0) ? 4 : (sf_str[2] > 0) ? 3 : (sf_str[1] > 0) ? 2 : 1;
            for (i = 0; i < 2; i++) // led_width == 2
            {
                for (j = 0; j < led_height; j++)
                {
                    block_idx = i + led_width*j;
                    block_sum = IN_blocks[block_idx] * sf_str[0];
                    for (k = 1; k < nk; k++)
                    {
                        q = LD_ALGO_max(j - k, 0); // up
                        neighbor_idx = i + led_width*q;
                        block_sum += (U32)IN_blocks[neighbor_idx] * sf_str[k];

                        q = LD_ALGO_min(j + k, led_height-1); // down
                        neighbor_idx = i + led_width*q;
                        block_sum += (U32)IN_blocks[neighbor_idx] * sf_str[k];
                    }
                    OUT_blocks[block_idx] = LD_ALGO_max(IN_blocks[block_idx], (block_sum + 0x80) >> 8);
                }
            }
        }
        else// if (led_type == HAL_LD_DIRECT_TYPE)
        {
            U16 TMP_blocks[LD_MAX_BLOCK_SIZE];
            U8 nk = (sf_str[4] > 0) ? 5 : (sf_str[3] > 0) ? 4 : (sf_str[2] > 0) ? 3 : (sf_str[1] > 0) ? 2 : 1;

            // horizontal filtering
            for (j = 0; j < led_height; j++)
            {
                for (i = 0; i < led_width; i++)
                {
                    block_idx = i + led_width*j;
                    block_sum = IN_blocks[block_idx] * sf_str[0];
                    for (k = 1; k < nk; k++)
                    {
                        p = LD_ALGO_max(i - k, 0); // left
                        neighbor_idx = p + led_width*j;
                        block_sum += (U32)IN_blocks[neighbor_idx] * sf_str[k];

                        p = LD_ALGO_min(i + k, led_width-1); // right
                        neighbor_idx = p + led_width*j;
                        block_sum += (U32)IN_blocks[neighbor_idx] * sf_str[k];
                    }
                    TMP_blocks[block_idx] = LD_ALGO_max(IN_blocks[block_idx], (block_sum + 0x80) >> 8);
                }
            }

            // vertical filtering
            for (i = 0; i < led_width; i++)
            {
                for (j = 0; j < led_height; j++)
                {
                    block_idx = i + led_width*j;
                    block_sum = TMP_blocks[block_idx] * sf_str[0];
                    for (k = 1; k < nk; k++)
                    {
                        q = LD_ALGO_max(j - k, 0); // up
                        neighbor_idx = i + led_width*q;
                        block_sum += (U32)TMP_blocks[neighbor_idx] * sf_str[k];

                        q = LD_ALGO_min(j + k, led_height-1); // down
                        neighbor_idx = i + led_width*q;
                        block_sum += (U32)TMP_blocks[neighbor_idx] * sf_str[k];
                    }
                    OUT_blocks[block_idx] = LD_ALGO_max(TMP_blocks[block_idx], (block_sum + 0x80) >> 8);
                }
            }
        }
    }
    else // nonlinear style
    {
        // direct type
        const int N1_direct = 8; // dist = 1.0
        const int xoffset1_direct[8]  = { -1,  0,  1,  0, -1,  1,  1, -1 };
        const int yoffset1_direct[8]  = {  0, -1,  0,  1, -1, -1,  1,  1 };
        const int N2_direct = 16; // dist = 2.0
        const int xoffset2_direct[16] = { -2,  0,  2,  0, -2, -1,  1,  2,  2,  1, -1, -2, -2,  2,  2, -2 };
        const int yoffset2_direct[16] = {  0, -2,  0,  2, -1, -2, -2, -1,  1,  2,  2,  1, -2, -2,  2,  2 };
        const int N3_direct = 24; // dist = 3.0
        const int xoffset3_direct[24] = { -3,  0,  3,  0, -3, -1,  1,  3,  3,  1, -1, -3, -3, -2,  2,  3,  3,  2, -2, -3, -3,  3,  3, -3 };
        const int yoffset3_direct[24] = {  0, -3,  0,  3, -1, -3, -3, -1,  1,  3,  3,  1, -2, -3, -3, -2,  2,  3,  3,  2, -3, -3,  3,  3 };
        const int N4_direct = 32; // dist = 4.0
        const int xoffset4_direct[32]  = { -4,  0,  4,  0, -4, -1,  1,  4,  4,  1, -1, -4, -4, -2,  2,  4,  4,  2, -2, -4, -4, -3,  3,  4,  4,  3, -3, -4, -4,  4,  4, -4 };
        const int yoffset4_direct[32]  = {  0, -4,  0,  4, -1, -4, -4, -1,  1,  4,  4,  1, -2, -4, -4, -2,  2,  4,  4,  2, -3, -4, -4, -3,  3,  4,  4,  3, -4, -4,  4,  4 };
        const int N5_direct = 40; // dist = 5.0
        const int xoffset5_direct[40]  = { -5,  0,  5,  0, -5, -1,  1,  5,  5,  1, -1, -5, -5, -2,  2,  5,  5,  2, -2, -5, -5, -3,  3,  5,  5,  3, -3, -5, -5, -4,  4,  5,  5,  4, -4, -5, -5,  5,  5, -5 };
        const int yoffset5_direct[40]  = {  0, -5,  0,  5, -1, -5, -5, -1,  1,  5,  5,  1, -2, -5, -5, -2,  2,  5,  5,  2, -3, -5, -5, -3,  3,  5,  5,  3, -4, -5, -5, -4,  4,  5,  5,  4, -5, -5,  5,  5 };

        // left-right type
        const int N1_LR = 2; // dist = 1.0
        const int xoffset1_LR[2] = {  0,  0 };
        const int yoffset1_LR[2] = {  1, -1 };
        const int N2_LR = 2; // dist = 2.0
        const int xoffset2_LR[2] = {  0,  0 };
        const int yoffset2_LR[2] = {  2, -2 };
        const int N3_LR = 2; // dist = 3.0
        const int xoffset3_LR[2] = {  0,  0 };
        const int yoffset3_LR[2] = {  3, -3 };
        const int N4_LR = 2; // dist = 4.0
        const int xoffset4_LR[2] = {  0,  0 };
        const int yoffset4_LR[2] = {  4, -4 };
        const int N5_LR = 2; // dist = 5.0
        const int xoffset5_LR[2] = {  0,  0 };
        const int yoffset5_LR[2] = {  5, -5 };

        // top-bottom type
        const int N1_TB = 2; // dist = 1.0
        const int xoffset1_TB[2] = {  1, -1 };
        const int yoffset1_TB[2] = {  0,  0 };
        const int N2_TB = 2; // dist = 2.0
        const int xoffset2_TB[2] = {  2, -2 };
        const int yoffset2_TB[2] = {  0,  0 };
        const int N3_TB = 2; // dist = 3.0
        const int xoffset3_TB[2] = {  3, -3 };
        const int yoffset3_TB[2] = {  0,  0 };
        const int N4_TB = 2; // dist = 4.0
        const int xoffset4_TB[2] = {  4, -4 };
        const int yoffset4_TB[2] = {  0,  0 };
        const int N5_TB = 2; // dist = 5.0
        const int xoffset5_TB[2] = {  5, -5 };
        const int yoffset5_TB[2] = {  0,  0 };

        int N1 = 0, N2 = 0, N3 = 0, N4 = 0, N5 = 0;
        const int *xoffset1 = NULL, *xoffset2 = NULL, *xoffset3 = NULL, *xoffset4 = NULL, *xoffset5 = NULL;
        const int *yoffset1 = NULL, *yoffset2 = NULL, *yoffset3 = NULL, *yoffset4 = NULL, *yoffset5 = NULL;
        if (led_height <= 2) //(led_type == HAL_LD_EDGE_TB_TYPE)
        {
           N1 = N1_TB; N2 = N2_TB; N3 = N3_TB;
            xoffset1 = xoffset1_TB; xoffset2 = xoffset2_TB; xoffset3 = xoffset3_TB;
            yoffset1 = yoffset1_TB; yoffset2 = yoffset2_TB; yoffset3 = yoffset3_TB;
            N4 = N4_TB; N5 = N5_TB;
            xoffset4 = xoffset4_TB; xoffset5 = xoffset5_TB;
            yoffset4 = yoffset4_TB; yoffset5 = yoffset5_TB;
        }
        else if (led_width <= 2) //(led_type == HAL_LD_EDGE_LR_TYPE)
        {
            N1 = N1_LR; N2 = N2_LR; N3 = N3_LR;
            xoffset1 = xoffset1_LR; xoffset2 = xoffset2_LR; xoffset3 = xoffset3_LR;
            yoffset1 = yoffset1_LR; yoffset2 = yoffset2_LR; yoffset3 = yoffset3_LR;
            N4 = N4_LR; N5 = N5_LR;
            xoffset4 = xoffset4_LR; xoffset5 = xoffset5_LR;
            yoffset4 = yoffset4_LR; yoffset5 = yoffset5_LR;
        }
        else// if (led_type == HAL_LD_DIRECT_TYPE)
        {
            N1 = N1_direct; N2 = N2_direct; N3 = N3_direct;
            xoffset1 = xoffset1_direct; xoffset2 = xoffset2_direct; xoffset3 = xoffset3_direct;
            yoffset1 = yoffset1_direct; yoffset2 = yoffset2_direct; yoffset3 = yoffset3_direct;
            N4 = N4_direct; N5 = N5_direct;
            xoffset4 = xoffset4_direct; xoffset5 = xoffset5_direct;
            yoffset4 = yoffset4_direct; yoffset5 = yoffset5_direct;
        }

        for (k = 0; k < 5; k++)
            sf_str[k] <<= 8; // 0 ~ 0xFF00

        for (j = 0; j < led_height; j++)
        {
            for (i = 0; i < led_width; i++)
            {
                block_idx = i + led_width*j;

                // 3x3 non-linear filter
                if (sf_str[0] < 0xFF00)
                {
                    for (k = 0; k < N1; k++)
                    {
                        q = j + yoffset1[k];
                        if (q < 0 || q >= led_height) continue;
                        p = i + xoffset1[k];
                        if (p < 0 || p >= led_width) continue;

                        neighbor_idx = p + led_width*q;
                        if (sf_str[0] + OUT_blocks[block_idx] < IN_blocks[neighbor_idx])
                            OUT_blocks[block_idx] = IN_blocks[neighbor_idx] - sf_str[0];
                    }
                }

                // 5x5 non-linear filter
                if (sf_str[1] < 0xFF00)
                {
                    for (k = 0; k < N2; k++)
                    {
                        q = j + yoffset2[k];
                        if (q < 0 || q >= led_height) continue;
                        p = i + xoffset2[k];
                        if (p < 0 || p >= led_width) continue;

                        neighbor_idx = p + led_width*q;
                        if (sf_str[1] + OUT_blocks[block_idx] < IN_blocks[neighbor_idx])
                            OUT_blocks[block_idx] = IN_blocks[neighbor_idx] - sf_str[1];
                    }
                }

                // 7x7 non-linear filter
                if (sf_str[2] < 0xFF00)
                {
                    for (k = 0; k < N3; k++)
                    {
                        q = j + yoffset3[k];
                        if (q < 0 || q >= led_height) continue;
                        p = i + xoffset3[k];
                        if (p < 0 || p >= led_width) continue;

                        neighbor_idx = p + led_width*q;
                        if (sf_str[2] + OUT_blocks[block_idx] < IN_blocks[neighbor_idx])
                            OUT_blocks[block_idx] = IN_blocks[neighbor_idx] - sf_str[2];
                    }
                }

                // 9x9 non-linear filter
                if (sf_str[3] < 0xFF00)
                {
                    for (k = 0; k < N4; k++)
                    {
                        q = j + yoffset4[k];
                        if (q < 0 || q >= led_height) continue;
                        p = i + xoffset4[k];
                        if (p < 0 || p >= led_width) continue;

                        neighbor_idx = p + led_width*q;
                        if (sf_str[3] + OUT_blocks[block_idx] < IN_blocks[neighbor_idx])
                            OUT_blocks[block_idx] = IN_blocks[neighbor_idx] - sf_str[3];
                    }
                }

                // 11x11 non-linear filter
                if (sf_str[4] < 0xFF00)
                {
                    for (k = 0; k < N5; k++)
                    {
                        q = j + yoffset5[k];
                        if (q < 0 || q >= led_height) continue;
                        p = i + xoffset5[k];
                        if (p < 0 || p >= led_width) continue;

                        neighbor_idx = p + led_width*q;
                        if (sf_str[4] + OUT_blocks[block_idx] < IN_blocks[neighbor_idx])
                            OUT_blocks[block_idx] = IN_blocks[neighbor_idx] - sf_str[4];
                    }
                }
           }
        }
    }
}

void MDrv_LD_Load_LDF_FrameStatistics(U8* LDF_blocks)
{
    U32 addr_base_L = MHal_LD_Get_LDF_FrameBufBaseAddr_L0();
#ifdef LD_LR_ENGINE
    U32 addr_base_R = MHal_LD_Get_LDF_FrameBufBaseAddr_R0();
#endif
#ifdef LD_SW_PINGPONG_MODE
    BOOL bFrameIdx = MDrv_ReadRegBit(0x3304, _BIT0);
    if (MDrv_ReadRegBit(0x3305, _BIT0) && bFrameIdx)
    {
        addr_base_L = MHal_LD_Get_LDF_FrameBufBaseAddr_L1();
#ifdef LD_LR_ENGINE
        addr_base_R = MHal_LD_Get_LDF_FrameBufBaseAddr_R1();
#endif
    }
#else
    if (MHal_LD_Get_CurFrameIdx() == 1)
    {
        addr_base_L = MHal_LD_Get_LDF_FrameBufBaseAddr_L1();
#ifdef LD_LR_ENGINE
        addr_base_R = MHal_LD_Get_LDF_FrameBufBaseAddr_R1();
#endif
    }
#endif


    U16 ldf_width = MHal_LD_Get_LDF_BacklightWidth();
    U16 ldf_height = MHal_LD_Get_LDF_BacklightHeight();
#ifdef LD_LR_ENGINE
    ldf_width /= 2; // left/right 2 engine
#endif
    if (MHal_LD_Get_LDF_WriteDCMaxOFEn()) // 4 bytes : OF[15:8] OF[7:0] Max DC
        ldf_width *= 4;
    else if (MHal_LD_Get_LDF_WriteDCMaxEn()) // 2 bytes : Max DC
        ldf_width *= 2;
    //else // 1 bytes : BLEND
    //    ldf_width *= 1;

    U16 pack_length = 0;
    if (ldf_width > 0)
        pack_length = (((ldf_width - 1) / MDrv_LD_PackLength) + 1) * MDrv_LD_PackLength;

    //    1 2 3 4 5 6            1 2 3      4 5 6
    //    7 8 9 a b c   -->   L: 7 8 9   R: a b c
    //    d e f g h i            d e f      g h i
    //    j k l m n o            j k l      m n o
    U32 addr_offset_L = 0, addr_offset_R = 0;
    U16 i = 0, j = 0;
    for (j = 0; j < ldf_height; j++)
    {
        addr_offset_R = addr_offset_L = j * pack_length;
        for (i = 0; i < ldf_width; i++)
            *LDF_blocks++ = MDrv_LD_MIUReadByte(addr_base_L, addr_offset_L++);
#ifdef LD_LR_ENGINE
        for (i = 0; i < ldf_width; i++)
            *LDF_blocks++ = MDrv_LD_MIUReadByte(addr_base_R, addr_offset_R++);
#endif
    }
#ifdef LD_SW_PINGPONG_MODE
    MDrv_WriteRegBit(0x3304, !bFrameIdx, _BIT0);
#endif
}

void MDrv_LD_Output_LDB_FrameBacklight(const U8* LDB_blocks)
{
    U32 addr_base_L = MHal_LD_Get_LDB_FrameBufBaseAddr_L0();
#ifdef LD_LR_ENGINE
    U32 addr_base_R = MHal_LD_Get_LDB_FrameBufBaseAddr_R0();
#endif
#ifdef LD_SW_PINGPONG_MODE
    BOOL bFrameIdx = MDrv_ReadRegBit(REG_3380, _BIT0);
    if (MDrv_ReadRegBit(0x3381, _BIT4) && !bFrameIdx)
    {
        addr_base_L = MHal_LD_Get_LDB_FrameBufBaseAddr_L1();
#ifdef LD_LR_ENGINE
        addr_base_R = MHal_LD_Get_LDB_FrameBufBaseAddr_R1();
#endif
    }
#endif

    //U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    //U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 led_width = s_LdAlgo_u16LedWidth;
    U16 led_height = s_LdAlgo_u16LedHeight;

    U16 led_half_width = (led_width + 1) >> 1;
    U16 led_half_height = (led_height + 1) >> 1;
    U16 block_idx = 0;

    U16 ldb_width = MHal_LD_Get_LDB_BacklightWidth();
    //U16 ldb_height = MHal_LD_Get_LDB_BacklightHeight();

    U32 addr_offset = 0;
    U16 pack_length = 0;
    U16 i = 0, j = 0;

    if (led_width > 0)
        pack_length = (((ldb_width - 1) / MDrv_LD_PackLength) + 1) * MDrv_LD_PackLength;

    if (MHal_LD_Get_Edge2DLocalTypeEn())
    {
        pack_length *= 2;
        for (j = 0; j < led_height; j++)
        {
            addr_offset = j*pack_length;
            for (i = 0; i < ldb_width; i++)
            {
                MDrv_LD_MIUWriteByte(addr_base_L, addr_offset, *LDB_blocks);
                #ifdef LD_LR_ENGINE
                MDrv_LD_MIUWriteByte(addr_base_R, addr_offset, *LDB_blocks);
                #endif
                addr_offset++;
                LDB_blocks++;
            }
        }
    }
    else if (MHal_LD_Get_Edge2DEn()) // ldb_width = led_width
    {
        //    1 2 3 4 5            1 2 3 7 8      1 2 3 7 8
        //    7 8 9 a b   -->   L: 9 4 5 a b   R: 9 4 5 a b
        //    d e f g h            d e f g h      d e f g h
        block_idx = 0;
        addr_offset = 0;
        // top-left quater
        for (j = 0; j < led_half_height; j++)
        {
            for (i = 0; i < led_half_width; i++)
            {
                MDrv_LD_MIUWriteByte(addr_base_L, addr_offset, LDB_blocks[i + j*led_width]);
#ifdef LD_LR_ENGINE
                MDrv_LD_MIUWriteByte(addr_base_R, addr_offset, LDB_blocks[i + j*led_width]);
#endif
                addr_offset ++;
                if (block_idx % ldb_width == ldb_width - 1)
                    addr_offset += pack_length - ldb_width;
                block_idx ++;
            }
        }
        // top-left quater
        for (j = 0; j < led_half_height; j++)
        {
            for (i = led_half_width; i < led_width; i++)
            {
                MDrv_LD_MIUWriteByte(addr_base_L, addr_offset, LDB_blocks[i + j*led_width]);
#ifdef LD_LR_ENGINE
                MDrv_LD_MIUWriteByte(addr_base_R, addr_offset, LDB_blocks[i + j*led_width]);
#endif
                addr_offset ++;
                if (block_idx % ldb_width == ldb_width - 1)
                    addr_offset += pack_length - ldb_width;
                block_idx ++;
            }
        }
        // bottom-left quater
        for (j = led_half_height; j < led_height; j++)
        {
            for (i = 0; i < led_half_width; i++)
            {
                MDrv_LD_MIUWriteByte(addr_base_L, addr_offset, LDB_blocks[i + j*led_width]);
#ifdef LD_LR_ENGINE
                MDrv_LD_MIUWriteByte(addr_base_R, addr_offset, LDB_blocks[i + j*led_width]);
#endif
                addr_offset ++;
                if (block_idx % ldb_width == ldb_width - 1)
                    addr_offset += pack_length - ldb_width;
                block_idx ++;
            }
        }
        // bottom-left quater
        for (j = led_half_height; j < led_height; j++)
        {
            for (i = led_half_width; i < led_width; i++)
            {
                MDrv_LD_MIUWriteByte(addr_base_L, addr_offset, LDB_blocks[i + j*led_width]);
#ifdef LD_LR_ENGINE
                MDrv_LD_MIUWriteByte(addr_base_R, addr_offset, LDB_blocks[i + j*led_width]);
#endif
                addr_offset ++;
                if (block_idx % ldb_width == ldb_width - 1)
                    addr_offset += pack_length - ldb_width;
                block_idx ++;
            }
        }
    }
    else  // ldb_width = led_width/2 + 1
    {
        //    1 2 3 4 5 6            1 2 3 4      3 4 5 6
        //    7 8 9 a b c   -->   L: 7 8 9 a   R: 9 a b c
        //    d e f g h i            d e f g      f g h i
        //    j k l m n o            j k l m      l m n o
        for (j = 0; j < led_height; j++)
        {
            addr_offset = j*pack_length;
            for (i = 0; i < ldb_width; i++)
                MDrv_LD_MIUWriteByte(addr_base_L, addr_offset++, *LDB_blocks++);

#ifdef LD_LR_ENGINE
            LDB_blocks -= 2;

            addr_offset = j*pack_length;
            for (i = led_width-ldb_width; i < led_width; i++)
                MDrv_LD_MIUWriteByte(addr_base_R, addr_offset++, *LDB_blocks++);
#endif
        }
    }
#ifdef LD_SW_PINGPONG_MODE
    MDrv_WriteRegBit(REG_3380, !bFrameIdx, _BIT0);
#endif
}


#define LDALGO_DEBUG_LED_NUM     14
void MDrv_LDAlgo_Output_SPI_Signal(U16* SPI_blocks)
{
    SPI_blocks=SPI_blocks;

#if 0
    {
        U16 i;
        for( i = 0; i < LD_TEST_LED_NUM; ++ i )
        {
            SPI_blocks[i] = i + 0x10;
        }
    }
#endif

#if 0
    U8 i;
    printf("LDAlgo out[]=");
    for( i = 0; i < LDALGO_DEBUG_LED_NUM; ++ i )
    {
        printf("%X,", SPI_blocks[i]);
    }
    printf("\n");
#endif


#if 1 // Copy result led data to another buf for HK
    U16 u16LedIdx = 0;
    U16 u16CheckSum = 0;
    s_LDAlgo_pu16OutLedBuf[0] = s_LdAlgo_u16LedNums;
    u16CheckSum = s_LdAlgo_u16LedNums;
    for (u16LedIdx = 0; u16LedIdx < s_LdAlgo_u16LedNums; u16LedIdx ++)
    {
        // Check over range
        if( (U32)((u16LedIdx+2)*2) >= (s_LDAlgo_u32OutLedBufSize) )
            break;

        s_LDAlgo_pu16OutLedBuf[u16LedIdx+1] = SPI_blocks[u16LedIdx];
        u16CheckSum += SPI_blocks[u16LedIdx];
    }
    s_LDAlgo_pu16OutLedBuf[u16LedIdx+1] = u16CheckSum;


 #if 0
    U8 i;
    printf("OutLedBuf out[]=");
    for( i = 0; i < (s_LdAlgo_u16LedNums+2); ++ i )
    {
        printf("%X,", s_LDAlgo_pu16OutLedBuf[i]);
    }
    printf("\n");
 #endif

#endif


    MsOS_Dcache_Flush( (U32)SPI_blocks, s_LdAlgo_u16LedNums*2);

    MsOS_FlushMemory();

    // Notify LD driver: Data update~
#if(LD_ALGO_RUN_IN_CROP)
    // todo
#else
    MApi_LD_Set_HasNewLedData();
#endif

}

void MDrv_LDAlgo_Main(void)
{
//printf("{LDAlgo}");
    static U8 LDF_blocks[4*LD_MAX_BLOCK_WIDTH*LD_MAX_BLOCK_HEIGHT]={0};
    static U16 SD_blocks[LD_MAX_BLOCK_SIZE]={0};
    static U16 TF_blocks[LD_MAX_BLOCK_SIZE]={0};
    static U16 SF_blocks[LD_MAX_BLOCK_SIZE]={0};
    static U8 LDB_blocks[LD_MAX_BLOCK_SIZE]={0};
    //static U16 SPI_blocks[LD_MAX_BLOCK_SIZE]={0};
    U16* SPI_blocks = g_LDAlgo_SPI_blocks;

    // Runtime estimator
//    static U32 u32StartTime = msAPI_Timer_GetSystemTime(), u32EndTime = 0;

    // Frequency counter
//    static BOOL bLockTime = FALSE;
//    static U32 u32LdFreqPerSec = 0;
//    if (!bLockTime)
//    {
//        bLockTIme = TRUE;
//        u32LdFreqPerSec = 0;
//    }

    s_LdAlgo_u16LedWidth = MHal_LD_Get_LED_BacklightWidth();
    s_LdAlgo_u16LedHeight = MHal_LD_Get_LED_BacklightHeight();


#if(LD_ALGO_KIM_DEBUG)
    if (MHal_LD_Get_SoftReset())
    {
        // Modify psDrvLdInfo & psDrvLdPQInfo HERE!!
        psDrvLdPQInfo->u8LDFWidth = MHal_LD_Get_LDF_BacklightWidth();
        psDrvLdPQInfo->u8LDFHeight = MHal_LD_Get_LDF_BacklightHeight();
        psDrvLdPQInfo->u8LEDWidth = MHal_LD_Get_LED_BacklightWidth();
        psDrvLdPQInfo->u8LEDHeight = MHal_LD_Get_LED_BacklightHeight();
        psDrvLdPQInfo->u8LSFWidth = MHal_LD_Get_LSF_BacklightWidth();
        psDrvLdPQInfo->u8LSFHeight = MHal_LD_Get_LSF_BacklightHeight();
        psDrvLdPQInfo->eLEDType = (EnuLD_LED_TYPE) MHal_LD_Get_LEDType();

        // Reset algorithm parameters & Edge2D table & compensation table by current register content.
        MDrv_LD_Int_Init();
    }
#endif

    U8 in_gamma = MHal_LD_Get_SW_BacklightInGamma();
    U8 out_gamma = MHal_LD_Get_SW_BacklightOutGamma();

    // SW input
    if (MHal_LD_Get_SW_ReadLDFEn())
        MDrv_LD_Load_LDF_FrameStatistics(LDF_blocks);

    // SW algorithm begin
    if (MHal_LD_Get_SW_AlgorithmEn())
    {
        MDrv_LDAlgo_ScalingDown(LDF_blocks, SD_blocks);       // LDF -> SD
        MDrv_LDAlgo_BacklightGamma(SD_blocks, LD_ALGO_TBL_GAMMA[in_gamma]);
        MDrv_LDAlgo_SpatialFilter(SD_blocks, TF_blocks);     // SD -> TF
        MDrv_LDAlgo_TemporalFilter(TF_blocks, SF_blocks);      // TF -> SF
        MDrv_LDAlgo_LocalDimmingStrength(SF_blocks);
        MDrv_LDAlgo_BacklightGamma(SF_blocks, LD_ALGO_TBL_REMAP[out_gamma]);
        MDrv_LDAlgo_PostProcess(SF_blocks, SPI_blocks, LDB_blocks);      // process SPI & LDB
        MDrv_LDAlgo_GlobalDimmingStrength(SPI_blocks);
    }
    // SW algorithm end
#if 0
	U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    	U16 led_height = MHal_LD_Get_LED_BacklightHeight();

       U16 n_leds = led_width * led_height;


	U8 i;
	printf("xxxxxxxxxxxLDF_blocksxxxxxxxxxxxxxxxxx\n");
	U16 ldf_width = MHal_LD_Get_LDF_BacklightWidth();
	#ifdef LD_LR_ENGINE
    	ldf_width /= 2; // left/right 2 engine
	#endif
    	if (MHal_LD_Get_LDF_WriteDCMaxOFEn()) // 4 bytes : OF[15:8] OF[7:0] Max DC
        ldf_width *= 4;
    	else if (MHal_LD_Get_LDF_WriteDCMaxEn()) // 2 bytes : Max DC
        ldf_width *= 2;
	for( i=0;i<ldf_width;i++)
		printf("%x\n",LDF_blocks[i]);
	printf("xxxxxxxxxxxSDBLKxxxxxxxxxxxxxxxxx\n");
	for( i=0;i<n_leds;i++)
		printf("%x\n",SD_blocks[i]);
	#endif

    // SW output
    if ( MHal_LD_Get_SW_WriteSPIEn() )
    {
        MDrv_LDAlgo_Output_SPI_Signal(SPI_blocks); // real backlight
    }

    if (MHal_LD_Get_SW_WriteLDBEn())
        MDrv_LD_Output_LDB_FrameBacklight(LDB_blocks); // digital backlight

	#if 0
	printf("xxxxxxxxxxxSPIBLKxxxxxxxxxxxxxxxxx\n");
	for( i=0;i<n_leds;i++)
	printf("%x\n",SPI_blocks[i]);
	#endif


    // Runtime estimator
//    u32EndTime = msAPI_Timer_GetSystemTime();//u32ThisTime;
//    MDrv_Write2Byte(0x1EFC, (u32EndTime - u32StartTime));

    // Frequency counter
//    u32LdFreqPerSec++;
//    u32EndTime = msAPI_Timer_GetSystemTime();
//    if (u32EndTime - u32StartTime > 1000000)
//    {
//        bLockTime = FALSE;
//        MDrv_Write2Byte(0x1EFC, u32LdFreqPerSec);
//    }
}

#endif
