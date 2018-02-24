#define _MDRV_LD_C_

#include "Board.h"

#if ( LD_ENABLE )
#include "sysinfo.h"

#include "debug.h"

#include "drvGlobal.h"
#include "Panel.h"

#include "mhal_ld.h"
#include "mdrv_ld.h"

#include "mdrv_mfc_spi.h"
#include "mdrv_ldm_dma.h"
#include "mdrv_ldalgo.h"

#include "leddevice.h"

#include "msAPI_LD_PWM.h"


// ======================================================================================

#if(LD_ALGO_RUN_IN_CROP)
#else
StuLdAlgoInit g_LD_stLdAlgoInit;
#endif

static BOOL s_bMDrvLD_InitFinished = FALSE;

static t_sDrvLdCusPtrMap* g_LD_pstCurPtrMap = NULL;

#define psDrvLdInfo     (g_LD_pstCurPtrMap->p_sDrvLdInfo)
#define psDrvLdPQInfo   (g_LD_pstCurPtrMap->p_sDrvLdPQInfo)

// ======================================================================================
#define LD_min(a,b)     (((a) < (b)) ? (a) : (b))
#define LD_max(a,b)     (((a) > (b)) ? (a) : (b))

// ======================================================================================

void MDrv_LD_ISR(void)
{
#ifdef LD_SW_PINGPONG_MODE
    MDrv_WriteRegBit(LD_REG(0x05), TRUE, _BIT1); // LD LDF
    MDrv_WriteRegBit(LD_REG(0x81), TRUE, _BIT5); // LD LDB
#endif
}

void MDrv_LD_Init_Algo(void)
{
    PRINT_CURRENT_LINE();
    printf("MDrv_LD_Init_Algo()\n");

#if(LD_ALGO_RUN_IN_CROP)
    // todo

#else
    //  LD_Algo Init
    MDrv_LDAlgo_Init(&g_LD_stLdAlgoInit);
#endif
}

BOOL MDrv_LD_Init(void)
{
    if( s_bMDrvLD_InitFinished )
        return TRUE;

    PRINT_CURRENT_LINE();

    // Init share mem
    MHal_LD_ShareMem_Init(LD_SHARE_MEM_ADR);

    // Select Led device ...
    // Move out to msAPI_LD.c
    //MDrv_LD_CUS_Init(MDrv_LD_GetLedDev());
    g_LD_pstCurPtrMap = LedDev_Get_CurPtrMap();

    // Put info to share mem
    //printf("Tbl_LD_Gamma=0x%X\n", (U32)(Tbl_LD_Gamma));
    //printf("Tbl_LD_Gamma[1]=0x%X\n", (U32)(Tbl_LD_Gamma[1]));
    //printf("Tbl_LD_Gamma[2]=0x%X\n", (U32)(Tbl_LD_Gamma[2]));
    //printf("Tbl_LD_Remap=0x%X\n", (U32)(Tbl_LD_Remap));


#if(LD_ALGO_RUN_IN_CROP)
    MHal_LD_Set_ShareMem(E_LD_INFO_GAMMA_TBL_ADDR, MsOS_VA2PA( (U32)Tbl_LD_Gamma ) );
    MHal_LD_Set_ShareMem(E_LD_INFO_REMAP_TBL_ADDR, MsOS_VA2PA( (U32)Tbl_LD_Remap ) );
    MHal_LD_Set_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_ADDR, (LD_SHARE_MEM_ADR+0x100) );
    MHal_LD_Set_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_SIZE, (0x700) );
    //MHal_LD_Set_ShareMem(E_LD_INFO_LDM_DMA_PORT, LD_DMA_PORT );
#else
    g_LD_stLdAlgoInit.p_LdAlgo_Tbl_LD_Gamma = Tbl_LD_Gamma;
    g_LD_stLdAlgoInit.p_LdAlgo_Tbl_LD_Remap = Tbl_LD_Remap;
    g_LD_stLdAlgoInit.pu16OutLedBuf = (U16*)MsOS_PA2KSEG1(LD_SHARE_MEM_ADR+0x100);
    g_LD_stLdAlgoInit.u32OutLedBufSize = 0x700;
#endif

    // reg_ld_fix_pipe -> Max request this bit to be 0
    MDrv_WriteRegBit(LD_REG(0x6E), 0, _BIT7);
    // MIU improvement : lsf_ctrl -> h36[0] = 1, lsf_th ->h36[3:1] = 4, spi_ctrl -> h36[8] = 1, spi_th -> h36[11:9] = 4;
    MDrv_Write2Byte(LD_REG(0x6C), 0x0909);

    // New functions in Ultrasonic
    // 1. HW support Nx1/1xN : force 1
    //MHal_LD_Set_Edge2DLineModeEn(_ENABLE);
    // 2. 8b-to-12b LSF decoding : 0 -> linear, 1 -> perceptual
    MHal_LD_Set_CoefEncoding(psDrvLdPQInfo->eEnc);
    // 3. Compensation low gain
    MHal_LD_Set_CompensationLowEn(psDrvLdPQInfo->pu8CompLowTable != NULL);
    // 4. LSF offset
    MHal_LD_Set_LSFOffset(0);

#ifdef LD_SW_PINGPONG_MODE
    // LDF/LDB 0/1 Ping-Pong by SW
    MDrv_WriteRegBit(LD_REG(0x05), 1, _BIT0); // LDF
    MDrv_WriteRegBit(LD_REG(0x81), 1, _BIT4); // LDB
#endif

    if (psDrvLdInfo->eStage == LD_SPI_STAGE)
    {
        psDrvLdPQInfo->u8LSFWidth = psDrvLdInfo->u8LEDNumW;
        psDrvLdPQInfo->u8LSFHeight = psDrvLdInfo->u8LEDNumH;
        psDrvLdPQInfo->u8LEDWidth = psDrvLdInfo->u8LEDNumW;
        psDrvLdPQInfo->u8LEDHeight = psDrvLdInfo->u8LEDNumH;
        psDrvLdPQInfo->u8LDFWidth = psDrvLdInfo->u8LEDNumW;
        psDrvLdPQInfo->u8LDFHeight = psDrvLdInfo->u8LEDNumH;
        psDrvLdPQInfo->bEdge2DEn = _DISABLE;
        psDrvLdPQInfo->pu8CompTable = NULL;
        psDrvLdPQInfo->pu8CompLowTable = NULL;
        psDrvLdPQInfo->bCompensationEn = _DISABLE;
        psDrvLdPQInfo->eEnc = LD_COEF_PERCEPTUAL;
        psDrvLdPQInfo->pu8Edge2DTable = NULL;

        psDrvLdPQInfo->u32LsfInitialPhase_H = 0x80000;
        psDrvLdPQInfo->u32LsfInitialPhase_V = 0x80000;
        psDrvLdPQInfo->u8DCMaxAlpha = 0x8;
        psDrvLdPQInfo->u8CompensationBlend = 0x10;

        psDrvLdPQInfo->u8GDStrength = 0xFF;
        psDrvLdPQInfo->u8LDStrength = 0xFF;
        psDrvLdPQInfo->eTFStyle = LD_TF_MSTAR;
        psDrvLdPQInfo->u8TFStrengthUp = 0x80;
        psDrvLdPQInfo->u8TFStrengthDn = 0xF8;
        psDrvLdPQInfo->u8TFLowThreshold = 0x28;
        psDrvLdPQInfo->u8TFHightThreshold = 0x38;
        psDrvLdPQInfo->u8TFMaxSpeed = 0x0;
        psDrvLdPQInfo->eSFStyle = LD_SF_MSTAR;
        psDrvLdPQInfo->u8SFStrength1 = 0xFF;
        psDrvLdPQInfo->u8SFStrength2 = 0xFF;
        psDrvLdPQInfo->u8SFStrength3 = 0xFF;
        psDrvLdPQInfo->u8SFStrength4 = 0xFF;
        psDrvLdPQInfo->u8SFStrength5 = 0xFF;
        psDrvLdPQInfo->u8BLMinValue = 0x10;
        psDrvLdPQInfo->u8NRStrength = 0x30;
    }

    MDrv_LD_SPI_Init();
    //MDrv_LDM_DMA_Init();

    MDrv_LD_Int_Init();

    MDrv_LDM_DMA_Init();

    MHal_LD_Set_LocalDimmingEn(_ENABLE);

    MDrv_LD_Init_Algo();

    s_bMDrvLD_InitFinished = TRUE;

    return TRUE;
}

void MDrv_LD_Int_Init(void)
{
    // Set frame width/height from TGEN
    // Need Int Ld  after Tgen init and stable
    psDrvLdInfo->u16PanelWidth = g_IPanel.Width(); //3840;//MDrv_Read2Byte(0x2F1A) - MDrv_Read2Byte(0x2F18) + 1;
    psDrvLdInfo->u16PanelHeight=g_IPanel.Height(); //2160;//MDrv_Read2Byte(0x2F1E) - MDrv_Read2Byte(0x2F1C) + 1;
    MHal_LD_Set_FrameWidth(psDrvLdInfo->u16PanelWidth + 1);
    MHal_LD_Set_FrameHeight(psDrvLdInfo->u16PanelHeight + 1);

    MDrv_LD_LDF_Init();
    MDrv_LD_LDB_Init();
    MDrv_LD_SW_Init();

    if (psDrvLdPQInfo->bEdge2DEn)
    {
        //Load compensation table according to pramater of Edge2D enable
        if (psDrvLdPQInfo->pu8CompLowTable != NULL)
        {
            MHal_LD_Set_CompensationLowEn(_ENABLE);
            MDrv_LD_Load_CompensationTable(psDrvLdPQInfo->pu8CompTable);
            MDrv_LD_Load_CompensationLowTable(psDrvLdPQInfo->pu8CompLowTable);
        }
        else
        {
            MHal_LD_Set_CompensationLowEn(_DISABLE);
            MDrv_LD_Load_CompensationTable(psDrvLdPQInfo->pu8CompTable);
        }

        MHal_LD_Set_CoefEncoding(psDrvLdPQInfo->eEnc);
        MDrv_LD_Load_Edge2DTable(psDrvLdPQInfo->pu8Edge2DTable);
    }
}


#if ENABLE_FOUR_SPI
void MDrv_LD_SetSpiPort(void)
{
todo:? ;
	MDrv_WriteByteMask(REG_1E54,0, BIT1|BIT0);
}
#endif

void MDrv_LD_SPI_Init(void)
{
    MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_STOP); // Stop LDM-DMA

    // MSPI setting
    StuMSPICtrlInfo MSPICtrlInfo;
    MSPICtrlInfo.eMSPIClockGen=psDrvLdInfo->eMSPIClockGen; //MSPI_CLK_SPD_24M;
    MSPICtrlInfo.eMSPIClockDiv=psDrvLdInfo->eMSPIClockDiv; //MSPI_CLK_SPD__DIV_8;
    MSPICtrlInfo.u8ClockPolarity=psDrvLdInfo->u8ClockPolarity;//0 ;
    MSPICtrlInfo.u8ClockPhase=psDrvLdInfo->u8ClockPhase; //0 ;
    MSPICtrlInfo.u8SpiOutputDataBit= psDrvLdInfo->u8SpiDataBit;
    // Setup timing & delay parameter
    MSPICtrlInfo.u8Time_FromTriggerToFirstClock=psDrvLdInfo->u8Time_FromTriggerToFirstClock; //0 // 1 cycle
    MSPICtrlInfo.u8Time_LastClockToDone=psDrvLdInfo->u8Time_LastClockToDone; //0; // 1 cycle
    MSPICtrlInfo.u8Time_BetweenByteToByte=psDrvLdInfo->u8Time_BetweenByteToByte; //0; // 0 cycle
    MSPICtrlInfo.u8Time_FromWriteToRead=psDrvLdInfo->u8Time_FromWriteToRead; //0; // 0 cycle

    if( MDrv_SPI_Init(TRUE,MSPICtrlInfo) == FALSE )
    {
        printf("Init drvMSPI failed!\n");
        return ;
    }

    //MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, 2);
    MHal_LD_Set_SpiDepack16En(TRUE);

#if ( DRV_LD_USE_SWSPI )
#else
#if ENABLE_TWO_SPI
    MHal_LD_Set_DmaMiuPack_Offset_Length(0, 4, 3);
#elif ENABLE_FOUR_SPI
	MHal_LD_Set_DmaMiuPack_Offset_Length(0, 4, 8, 12, 3);
#else
    MHal_LD_Set_DmaMiuPack_Offset_Length(0x0,0x1F);
#endif
    MHal_LD_Set_DmaEnable(_ENABLE);
    MHal_LD_Set_DmaAccessYEnd(psDrvLdInfo->u8DMAHeight); // ???  u8LedNumV or u8LD_BacklightV ???
#endif

#if ENABLE_FOUR_SPI
	MDrv_LD_SetSpiPort();
#endif

//    MDrv_SPI_VSyncLikeInit();//PWM Vsync like
//    MDrv_SPI_SttInit();//SPI Stt
}

void MDrv_LD_LDF_Init(void)
{
    MHal_LD_Set_LDF_BacklightWidth(psDrvLdPQInfo->u8LDFWidth);
    MHal_LD_Set_LDF_BacklightHeight(psDrvLdPQInfo->u8LDFHeight);

    MHal_LD_Set_InputHScalingDownRatio(((U32)psDrvLdPQInfo->u8LDFWidth << 20)/psDrvLdInfo->u16PanelWidth + 1); // W_ledx1024x1024/W_lcd + 1
    MHal_LD_Set_InputVScalingDownRatio(((U32)psDrvLdPQInfo->u8LDFHeight << 20)/psDrvLdInfo->u16PanelHeight + 1); // H_ledx1024x1024/H_lcd + 1

#ifdef LD_LR_ENGINE
    U32 LDF_pack_per_row = ((psDrvLdPQInfo->u8LDFWidth/2 *4 - 1) / MDrv_LD_PackLength) + 1;
#else
    U32 LDF_pack_per_row = ((psDrvLdPQInfo->u8LDFWidth *4 - 1) / MDrv_LD_PackLength) + 1;
#endif
    U32 LDF_mem_size = LDF_pack_per_row * MDrv_LD_PackLength * psDrvLdPQInfo->u8LDFHeight;
    LDF_mem_size = (LDF_mem_size + 0xFF) >> 8 << 8; // align at 0x100

    U32 u32LDFBaseAddr = psDrvLdInfo->u32BaseAddr;
    MHal_LD_Set_LDF_FrameBufBaseAddr_L0((u32LDFBaseAddr                 ));
    MHal_LD_Set_LDF_FrameBufBaseAddr_L1((u32LDFBaseAddr +   LDF_mem_size));
#ifdef LD_LR_ENGINE
    MHal_LD_Set_LDF_FrameBufBaseAddr_R0((u32LDFBaseAddr + 2*LDF_mem_size));
    MHal_LD_Set_LDF_FrameBufBaseAddr_R1((u32LDFBaseAddr + 3*LDF_mem_size));
#endif

#if 0
	printf("%x\n",u32LDFBaseAddr +   LDF_mem_size);
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
#endif

    MHal_LD_Set_LDF_HLPFEn(TRUE);
    MHal_LD_Set_LDF_HLPFThreshold(0);
    MHal_LD_Set_LDF_HLPFStep(0);

    MHal_LD_Set_LDF_DCMaxAlpha(psDrvLdPQInfo->u8DCMaxAlpha);
    MHal_LD_Set_LDF_WriteDCMaxEn(_ENABLE);
    MHal_LD_Set_LDF_WriteDCMaxOFEn(_DISABLE);
    MHal_LD_Set_LDF_PixelWhiteModeEn(_ENABLE);
}

void MDrv_LD_LDB_Init(void)
{
#ifdef LD_LR_ENGINE
    U8 u8LDBWidth = psDrvLdPQInfo->bEdge2DEn
                  ? (psDrvLdPQInfo->eLEDType == HAL_LD_EDGE_LR_TYPE ? psDrvLdPQInfo->u8LEDHeight: psDrvLdPQInfo->u8LEDWidth)
                  : psDrvLdPQInfo->u8LEDWidth/2 + 1;
#else
    U8 u8LDBWidth = psDrvLdPQInfo->bEdge2DEn
                  ? (psDrvLdPQInfo->eLEDType == HAL_LD_EDGE_LR_TYPE ? psDrvLdPQInfo->u8LEDHeight: psDrvLdPQInfo->u8LEDWidth)
                  : psDrvLdPQInfo->u8LEDWidth;
#endif
    U8 u8LDBHeight = psDrvLdPQInfo->bEdge2DEn
                   ? (psDrvLdPQInfo->eLEDType == HAL_LD_EDGE_LR_TYPE ? psDrvLdPQInfo->u8LEDWidth : psDrvLdPQInfo->u8LEDHeight)
                   : psDrvLdPQInfo->u8LEDHeight;
    MHal_LD_Set_LDB_BacklightWidth(u8LDBWidth);
    MHal_LD_Set_LDB_BacklightHeight(u8LDBHeight);

    // 1. HW support Nx1/1xN : force 1
    if((psDrvLdPQInfo->u8LEDWidth==1) || (psDrvLdPQInfo->u8LEDHeight==1))
        MHal_LD_Set_Edge2DLineModeEn(_ENABLE);

#ifdef LD_LR_ENGINE
    MHal_LD_Set_LSF_BacklightWidth(psDrvLdPQInfo->bEdge2DEn ? psDrvLdPQInfo->u8LSFWidth : psDrvLdPQInfo->u8LEDWidth/2 + 1);
#else
    MHal_LD_Set_LSF_BacklightWidth(psDrvLdPQInfo->u8LSFWidth);
#endif
    MHal_LD_Set_LSF_BacklightHeight(psDrvLdPQInfo->u8LSFHeight);

    MHal_LD_Set_DMA_BacklightWidth(psDrvLdInfo->u8DMAWidth);
    MHal_LD_Set_DMA_BacklightHeight(psDrvLdInfo->u8DMAHeight);

#ifdef LD_LR_ENGINE
    U32 LDF_pack_per_row = ((psDrvLdPQInfo->u8LDFWidth/2 *4 - 1) / MDrv_LD_PackLength) + 1;
#else
    U32 LDF_pack_per_row = ((psDrvLdPQInfo->u8LDFWidth *4 - 1) / MDrv_LD_PackLength) + 1;
#endif

    U32 LDF_mem_size = LDF_pack_per_row * MDrv_LD_PackLength * psDrvLdPQInfo->u8LDFHeight;
    U32 LDB_pack_per_row = (psDrvLdPQInfo->bEdge2DEn && psDrvLdPQInfo->eLEDType == HAL_LD_LOCAL_TYPE) ? 2 : ((u8LDBWidth + 1) / MDrv_LD_PackLength) + 1;
    U32 LDB_mem_size = LDB_pack_per_row * MDrv_LD_PackLength * u8LDBHeight;
    U32 EDGE2D_mem_size = (psDrvLdPQInfo->u8LSFWidth * psDrvLdPQInfo->u8LSFHeight) * MDrv_LD_PackLength;
    LDF_mem_size = (LDF_mem_size + 0xFF) >> 8 << 8; // align at 0x100
    LDB_mem_size = (LDB_mem_size + 0xFF) >> 8 << 8; // align at 0x100
    EDGE2D_mem_size = (EDGE2D_mem_size + 0xFF) >> 8 << 8; // align at 0x100

#ifdef LR_ENGINE
    U32 u32LDBBaseAddr = psDrvLdInfo->u32BaseAddr + 4*LDF_mem_size;
    #ifdef LD_SW_PINGPONG_MODE
    U32 u32Edge2DBaseAddr = u32LDBBaseAddr + 4*LDB_mem_size;
    #else
    U32 u32Edge2DBaseAddr = u32LDBBaseAddr + 2*LDB_mem_size;
    #endif
    U32 u32SPIBaseAddr = u32Edge2DBaseAddr + EDGE2D_mem_size;
#else
    U32 u32LDBBaseAddr = psDrvLdInfo->u32BaseAddr + 2*LDF_mem_size;
    #ifdef LD_SW_PINGPONG_MODE
    U32 u32Edge2DBaseAddr = u32LDBBaseAddr + 2*LDB_mem_size;
    #else
    U32 u32Edge2DBaseAddr = u32LDBBaseAddr + 1*LDB_mem_size;
    #endif
    U32 u32SPIBaseAddr = u32Edge2DBaseAddr + EDGE2D_mem_size;
#endif

#if 0
	printf("%x\n",u32LDBBaseAddr);
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
#endif

#ifdef LD_SW_PINGPONG_MODE
    MHal_LD_Set_LDB_FrameBufBaseAddr_L0((u32LDBBaseAddr                          ));
    MHal_LD_Set_LDB_FrameBufBaseAddr_L1((u32LDBBaseAddr + LDB_mem_size));
#else
    MHal_LD_Set_LDB_FrameBufBaseAddr_L0((u32LDBBaseAddr               ));
    MHal_LD_Set_LDB_FrameBufBaseAddr_L1((u32LDBBaseAddr               ));
#endif
#ifdef LR_ENGINE
    #ifdef LD_SW_PINGPONG_MODE
    MHal_LD_Set_LDB_FrameBufBaseAddr_R0((u32LDBBaseAddr + 2*LDB_mem_size));
    MHal_LD_Set_LDB_FrameBufBaseAddr_R1((u32LDBBaseAddr + 3*LDB_mem_size));
    #else
    MHal_LD_Set_LDB_FrameBufBaseAddr_R0((u32LDBBaseAddr + LDB_mem_size));
    MHal_LD_Set_LDB_FrameBufBaseAddr_R1((u32LDBBaseAddr + LDB_mem_size));
    #endif
#endif
    MHal_LD_Set_Edge2D_BufBaseAddr((u32Edge2DBaseAddr));
    MHal_LD_Set_SPI_BufBaseAddr((u32SPIBaseAddr));

    MHal_LD_Set_Edge2DEn(psDrvLdPQInfo->bEdge2DEn); // enable -> edge2d mode; diabled -> scaling up mode
    MHal_LD_Set_Edge2DGainEn(FALSE); // not used
    MHal_LD_Set_Edge2DDirectTypeEn(psDrvLdPQInfo->eLEDType == HAL_LD_DIRECT_TYPE ? _ENABLE : _DISABLE);// always enabled because direct type now includes edge type
    MHal_LD_Set_Edge2DLocalTypeEn(psDrvLdPQInfo->eLEDType == HAL_LD_LOCAL_TYPE ? _ENABLE : _DISABLE);

    //U16 u16GuardBand = MDrv_ReadRegBit(0x2F2F, _BIT0) ? (MDrv_Read2Byte(0x2F86) - MDrv_Read2Byte(0x2F84) + 1)*2 - psDrvLdInfo->u16PanelWidth/2 : 0;
    U32 u32LSFRatioH = ((U32)psDrvLdPQInfo->u8LSFWidth<<20) / (psDrvLdInfo->u16PanelWidth - 1); // (W_led + 1)x1024x1024/(W_lcd - 1)
    U32 u32LSFRatioV = ((U32)psDrvLdPQInfo->u8LSFHeight<<20) / (psDrvLdInfo->u16PanelHeight - 1); // H_ledx1024x1024/(H_lcd - 1)
    U32 u32CBRatioH = LD_min((((U32)psDrvLdPQInfo->u8LEDWidth)<<16) / psDrvLdPQInfo->u8LSFWidth, 0xFFFF); // W_ledx(2^16)/W_lsf
    U32 u32CBRatioV = LD_min((((U32)psDrvLdPQInfo->u8LEDHeight)<<16) / psDrvLdPQInfo->u8LSFHeight, 0xFFFF); // H_ledx(2^16)/H_lsf
#ifdef LD_LR_ENGINE
    U16 u16GuardBand = MDrv_ReadRegBit(0x2F2F, _BIT0) ? (MDrv_Read2Byte(0x2F86) - MDrv_Read2Byte(0x2F84) + 1)*2 - psDrvLdInfo->u16PanelWidth/2 : 0;
    U32 u32LSFAccMaster = (psDrvLdPQInfo->u32LsfInitialPhase_H + (psDrvLdInfo->u16PanelWidth/2 + u16GuardBand - 1)*u32LSFRatioH);
    U32 u32LSFMasterLast = (u32LSFAccMaster >> 20);
    U32 u32LSFAccSlave = (psDrvLdPQInfo->u32LsfInitialPhase_H + (psDrvLdInfo->u16PanelWidth/2 - u16GuardBand)*u32LSFRatioH);
    U32 u32LSFSlaveFirst = (u32LSFAccSlave >> 20) - 1;
    U32 u32LSFPhaseH2 = u32LSFAccSlave & 0xFFFFFul;
    //U32 u32LEDAccMaster = u32CBRatioH/2 + u32LSFMasterLast*u32CBRatioH;
    //U32 u32LEDMasterLast = u32LEDAccMaster >> 16;
    U32 u32LEDAccSlave = u32CBRatioH/2 + u32LSFSlaveFirst*u32CBRatioH;
    U32 u32LEDSlaveFirst = u32LEDAccSlave >> 16;
    U32 u32LEDPhaseH2 = u32LEDAccSlave & 0xFFFF;
#endif

    MHal_LD_Set_OutputHScalingUpRatio(u32LSFRatioH);
    MHal_LD_Set_OutputVScalingUpRatio(u32LSFRatioV);
    MHal_LD_Set_LSF_H_InitialPhase_L(psDrvLdPQInfo->u32LsfInitialPhase_H);
    //MHal_LD_Set_LSF_H_InitialPhase_R(u32LSFPhaseH2);
    MHal_LD_Set_LSF_V_InitialPhase(psDrvLdPQInfo->u32LsfInitialPhase_V);
    MHal_LD_Set_LSF_H_Boundary_L(_ENABLE); // _ENABLE -> duplicate
    MHal_LD_Set_LSF_H_Boundary_R(_DISABLE);
    MHal_LD_Set_LSF_V_Boundary(_ENABLE);
    MHal_LD_Set_LSF_CB_HRatio(u32CBRatioH);
    MHal_LD_Set_LSF_CB_VRatio(u32CBRatioV);
#ifdef LD_LR_ENGINE
    MHal_LD_Set_LSF_H_InitialPhase_R(u32LSFPhaseH2);
    MHal_LD_Set_LSF_H_Boundary_R(_DISABLE);
    MHal_LD_Set_LSF_CB_HInit(u32LEDPhaseH2);
    MHal_LD_Set_LSF_MasterLast(u32LSFMasterLast);
    MHal_LD_Set_LSF_SlaveFirst(u32LSFSlaveFirst);
    //MHal_LD_Set_LED_MasterLast(u32LEDMasterLast);
    MHal_LD_Set_LED_SlaveFirst(u32LEDSlaveFirst);
#endif

    MHal_LD_Set_EdgeLevelShift(0); // 0:normal  1:x2  2:x4
    MHal_LD_Set_BlendingDitherEn(FALSE);

    MHal_LD_Set_CompensationEn(psDrvLdPQInfo->bCompensationEn);

  #if 0//(CustomerType==CustomerType_LG_Unicorn)
    if(g_bDDCLDoff!=TRUE)
        MHal_LD_Set_CompensationBlend(psDrvLdPQInfo->u8CompensationBlend);
  #else
    MHal_LD_Set_CompensationBlend(psDrvLdPQInfo->u8CompensationBlend);
  #endif

    MHal_LD_Set_CompensationDitherEn(FALSE);

    MHal_LD_Set_BacklightGlobeMode(psDrvLdInfo->bBacklightGlobeMode);
    MHal_LD_Set_BacklightGlobeGain(psDrvLdInfo->u8BacklightGlobeGain);
    MHal_LD_Set_BacklightDataAlign(psDrvLdInfo->u8BacklightGlobeAlign); // 0:16b  1:12b  2:4b  3:10b
}

void MDrv_LD_SW_Init(void)
{
    MHal_LD_Set_LEDType((U8)psDrvLdPQInfo->eLEDType);
    MHal_LD_Set_LED_BacklightWidth(psDrvLdPQInfo->u8LEDWidth);
    MHal_LD_Set_LED_BacklightHeight(psDrvLdPQInfo->u8LEDHeight);

    MHal_LD_Set_SW_LocalDimmingStrength(psDrvLdPQInfo->u8LDStrength);
    MHal_LD_Set_SW_GlobalDimmingStrength(psDrvLdPQInfo->u8GDStrength);
    MHal_LD_Set_SW_BacklightInGamma(psDrvLdPQInfo->u8InGamma);
    MHal_LD_Set_SW_BacklightOutGamma(psDrvLdPQInfo->u8OutGamma);
    MHal_LD_Set_SW_MinClampValue(psDrvLdPQInfo->u8BLMinValue);

    MHal_LD_Set_SW_SpatialFilterStyle(psDrvLdPQInfo->eSFStyle);
    MHal_LD_Set_SW_SpatialFilterStrength1(psDrvLdPQInfo->u8SFStrength1);
    MHal_LD_Set_SW_SpatialFilterStrength2(psDrvLdPQInfo->u8SFStrength2);
    MHal_LD_Set_SW_SpatialFilterStrength3(psDrvLdPQInfo->u8SFStrength3);
    MHal_LD_Set_SW_SpatialFilterStrength4(psDrvLdPQInfo->u8SFStrength4);
    MHal_LD_Set_SW_SpatialFilterStrength5(psDrvLdPQInfo->u8SFStrength5);

    MHal_LD_Set_SW_TemporalFilterStyle(psDrvLdPQInfo->eTFStyle);
    MHal_LD_Set_SW_TemporalFilterStrengthUp(psDrvLdPQInfo->u8TFStrengthUp);
    MHal_LD_Set_SW_TemporalFilterStrengthDn(psDrvLdPQInfo->u8TFStrengthDn);
    MHal_LD_Set_SW_TemporalFilterLowTh(psDrvLdPQInfo->u8TFLowThreshold);
    MHal_LD_Set_SW_TemporalFilterHighTh(psDrvLdPQInfo->u8TFHightThreshold);
    MHal_LD_Set_SW_TemporalFilterMaxSpeed(psDrvLdPQInfo->u8TFMaxSpeed);

    MHal_LD_Set_SW_PulseMode(0);
    MHal_LD_Set_SW_PulseId(0);
    MHal_LD_Set_SW_PulseLEDIntensity(0);
    MHal_LD_Set_SW_PulseLDBIntensity(0);

    MHal_LD_Set_DebugMode(_DISABLE);
    MHal_LD_Set_LSFOutMode(0); // 0:normal  1:lsf  2:full
    MHal_LD_Set_CompensationOutMode(0); // 0:normal  1:overflow  2:overflow only  3:grid

    MHal_LD_Set_SW_ReadLDFEn(_ENABLE);
    MHal_LD_Set_SW_AlgorithmEn(_ENABLE);
    MHal_LD_Set_SW_WriteLDBEn(_ENABLE);
    MHal_LD_Set_SW_WriteSPIEn(_ENABLE);
}

void MDrv_LD_Load_CompensationTable(const U8* pu8CompTable)
{
    U16 u16Lut = 0;
    U16 i = 0;

    MHal_LD_Set_CompensationMode(FALSE); // TRUE -> incremental mode
    for (i = 0; i < 256; i++)
    {
        MHal_LD_Set_CompensationLUTAddress((U8)i);
        u16Lut = *pu8CompTable++;
        u16Lut |= (*pu8CompTable++) << 8;
        MHal_LD_Write_CompensationLUT(u16Lut);
        MHal_LD_Set_CompensationWriteEn(_ENABLE);
    }
}

void MDrv_LD_Load_CompensationLowTable(const U8* pu8CompTable)
{
    U16 u16Lut = 0;
    U16 i = 0;

    MHal_LD_Set_CompensationLowMode(FALSE); // TRUE -> incremental mode
    for (i = 0; i < 256; i++)
    {
        MHal_LD_Set_CompensationLowLUTAddress((U8)i);
        u16Lut = *pu8CompTable++;
        u16Lut |= (*pu8CompTable++) << 8;
        MHal_LD_Write_CompensationLowLUT(u16Lut);
        MHal_LD_Set_CompensationLowWriteEn(_ENABLE);
    }
}

void MDrv_LD_Load_Edge2DTable(const U8* pu8Edge2DTable)
{
    U16 led_width = MHal_LD_Get_LED_BacklightWidth();
    U16 led_height = MHal_LD_Get_LED_BacklightHeight();
    U16 lsf_width = MHal_LD_Get_LSF_BacklightWidth();
    U16 lsf_height = MHal_LD_Get_LSF_BacklightHeight();
    //U16 table_width = (led_width>>1) * (((led_height-1)>>1) + 1);
    U16 table_width = (((led_width-1)>>1)+1) * (((led_height-1)>>1) + 1);
    U16 table_height = lsf_width * lsf_height;
    U32 addr_base = MHal_LD_Get_Edge2D_BufBaseAddr();
    U32 addr_offset = 0;
    U16 i = 0, j = 0;

    U16 pack_length = MDrv_LD_PackLength;
    if (MHal_LD_Get_Edge2DLocalTypeEn())
        table_width = 25;

    for (j = 0; j < table_height; j++)
    {
        addr_offset = j * pack_length;
        for (i = 0; i < table_width; i++)
            MDrv_LD_MIUWriteByte(addr_base, addr_offset++, *pu8Edge2DTable++);
    }
}

//========  TEST Timing  for fine-tune========
#if 0
#define LD_TEST_PWM_DIV                12
#define LD_TEST_PWM_POLARITY           0
#define LD_TEST_PWM_RST_CTRL           (PWM_RST_CTRL__LRFLAG)//(PWM_RST_CTRL__VSYNC)

void MDrv_LD_Set_PWM(U8 pwmch,U16 duty,U16 shift)
{
    PRINT_CURRENT_LINE();
pwmch=pwmch;
duty=duty;
shift=shift;


    MDrv_MFC_PWM_waveform_maker( (DRV_PWM_CH)pwmch , sCusPtrMap.LED_DEVICE_Get_OutputVFreq(pwmch), duty,
                                shift, LD_TEST_PWM_DIV, sCusPtrMap.LED_DEVICE_Get_SyncRstCnt(pwmch),
                                Vsync_DoubleBF, LD_TEST_PWM_RST_CTRL, LD_TEST_PWM_POLARITY);
    MHal_PWM_WaveformResetEnable((DRV_PWM_CH)pwmch, ENABLE);
    MHal_PWM_OutputEn((DRV_PWM_CH)pwmch, ENABLE);
    MDrv_PWM_Set_PadEn( (DRV_PWM_CH)pwmch, ENABLE );
}
#endif

void MDrv_LD_Update_InputSize(U16 height,U16 width)
{
    psDrvLdInfo->u16PanelHeight =  height ;
    psDrvLdInfo->u16PanelWidth = width ;

    MDrv_LD_LDF_Init();
    MDrv_LD_LDB_Init();
}

/*
void MDrv_LD_SetSpiClkDelayFromVsync(U16 u16Val)
{
    MDrv_Write2Byte(LDM_DMA_REG(0x58), u16Val);
} */

//============ LD SW Debug Mode Register   =========================
#if 0

void MDrv_LD_SetLedControlNumber(U16 u16Val)
{PRINT_CURRENT_LINE();
    MDrv_Write2ByteMask(0x3344, u16Val&0x0FFF, 0x0FFF);
}

void MDrv_LD_SetLedControlMode(U8 u8Val)
{//LED control mode
PRINT_CURRENT_LINE();
    U16 u16Val=u8Val;
    MDrv_Write2ByteMask(0x3344, u16Val<<12, 0xF000);
}

void MDrv_LD_SetLedAmplitude(U8 u8Val)
{PRINT_CURRENT_LINE();
    MDrv_WriteByte(0x3346, u8Val);
}

void MDrv_LD_SetLdbAmplitude(U8 u8Val)
{PRINT_CURRENT_LINE();
    MDrv_WriteByte(0x3347, u8Val);
}

void MDrv_LD_SetLocalDimmingStrength(U8 u8Val)
{PRINT_CURRENT_LINE();
    MDrv_WriteByte(0x334A, u8Val);
}

void MDrv_LD_SetGlobalDimmingStrength(U8 u8Val)
{PRINT_CURRENT_LINE();
    MDrv_WriteByte(0x334B, u8Val);
}

void MDrv_LD_SetCompensationEnable(BOOL bEn)
{PRINT_CURRENT_LINE();
    MDrv_WriteByteMask(0x338C, (bEn&_BIT0)<<6, _BIT6);
}

void MDrv_LD_SetCompensationGain(U8 u8Val)
{PRINT_CURRENT_LINE();
    if(u8Val>0x10)
        {u8Val=0x10;}//range: 0~16

    MDrv_Write2ByteMask(0x3378, ((U16)u8Val)<<4, 0x01F0);// bit 4~ 8
}

void MDrv_LD_DemoModeInit(void)
{PRINT_CURRENT_LINE();
#if ((CustomerType == CustomerType_CMI_Ultrasonic)||(CustomerType == CustomerType_INX_Ubike))
    MDrv_LD_SetCompensationEnable(_DISABLE);//case 3   //hardcode refine 20150310
#else
    MDrv_LD_SetCompensationEnable(_ENABLE);//case 3   //hardcode refine 20150310
#endif
    MDrv_Write2Byte(0x33BE, 0x0FFF);//case 2
    MDrv_Write2Byte(0x33F8, 0x0FFF);//case 2

    {//case 1   //hardcode refine 20150310
        MDrv_LD_SetLedControlNumber(0);
        MDrv_LD_SetLedControlMode(0);
    }

    // Comment by Daniel
#if 0// (PANEL_TYPE_SEL == PNL_LTA750HQ01_VX1_FHD_240HZ)
    MDrv_Write2Byte(0x333E, 0x0084); //case 1,3
    MDrv_WriteByte(0x33ED, 0x06); //case 1,3
    MDrv_WriteByte(0x338A, 0x10);  //Unicorn ECO item register conflic 3376[7:0]->3345[7:0]
#endif
}

void MDrv_LD_SetDemoMode(U8 mode)
{
PRINT_CURRENT_LINE();
    switch(mode)
    {
    /*
        case 0:
            gbdemo_case4_enable =FALSE;
            break;
    */
        case 1:
            MDrv_Write2Byte(0x3344, 0x0002); // left panel : LD on,  right panel : LD off
            MDrv_WriteByte(0x3346, 0xFF);

            // Comment by Daniel

#if 0//(PANEL_TYPE_SEL == PNL_LTA750HQ01_VX1_FHD_240HZ)
            MDrv_Write2Byte(0x333E, 0x0088); //case 1,3
            MDrv_WriteByte(0x33ED, 0x00 ); //case 1,3
            MDrv_WriteByte(0x338A, 0x00);  //Unicorn ECO item register conflic 3376[7:0]->3345[7:0]
#endif
            break;

        case 2://show LD backlight L/R compare

            MDrv_Write2Byte(0x3344, 0x0005); // left panel : LD on,  right panel : LD off
            MDrv_WriteByte(0x3346, 0xFF);
            MDrv_WriteByteMask(0x338C, 0, _BIT6);

            MDrv_Write2Byte(0x33BE, 0);//R
            MDrv_Write2Byte(0x33F8, 0x0FFF);//L
            break;

        case 3://show LD backlight
            MDrv_WriteByteMask(0x338C, 0, _BIT6);

    // Comment by Daniel
#if 0//(PANEL_TYPE_SEL == PNL_LTA750HQ01_VX1_FHD_240HZ)
            MDrv_Write2Byte(0x333E, 0x0088); //case 1,3
            MDrv_WriteByte(0x33ED, 0x00 ); //case 1,3
            MDrv_WriteByte(0x338A, 0x00);  //Unicorn ECO item register conflic 3376[7:0]->3345[7:0]
#endif
            break;

        case 4:// black light LED sequential running
            {
                MDrv_Write2ByteMask(0x3344, 0x7000, 0xF000); // 0x45 high-byte = 0x7 . demo mode
                MDrv_Write2Byte(0x3346, 0xFFFF);
                MDrv_WriteByteMask(0x338C, 0, _BIT6);
//                _MApi_LD_Set_Enable_DemoMode_Case4(TRUE,4);
            }
            break;
        default:
            break;
    }
}

void MDrv_LD_SetSpiOuputAvg(U8 u8Val)
{PRINT_CURRENT_LINE();
    MDrv_WriteByte(0x3355,u8Val);
}

void MDrv_LD_SetSpiOuputMin(U8 u8Val)
{PRINT_CURRENT_LINE();
    MDrv_WriteByte(0x3356,u8Val);
}

void MDrv_LD_SetSpiOuputMax(U8 u8Val)
{PRINT_CURRENT_LINE();
    MDrv_WriteByte(0x3357,u8Val);
}

#else

void MDrv_LD_SetLedControlNumber(U16 u16Val)
{
    //MDrv_Write2ByteMask(0x3344, u16Val&0x0FFF, 0x0FFF);
    MDrv_Write2ByteMask(LD_REG(0x44), u16Val&0x0FFF, 0x0FFF);
}

void MDrv_LD_SetLedControlMode(U8 u8Val)
{//LED control mode
    U16 u16Val = u8Val;
    //MDrv_Write2ByteMask(0x3344, u16Val<<12, 0xF000);
    MDrv_Write2ByteMask(LD_REG(0x44), u16Val<<12, 0xF000);
}

void MDrv_LD_SetLedAmplitude(U8 u8Val)
{
    //MDrv_WriteByte(0x3346, u8Val);
    MDrv_WriteByte(LD_REG(0x46), u8Val);
}

void MDrv_LD_SetLdbAmplitude(U8 u8Val)
{
    //MDrv_WriteByte(0x3347, u8Val);
    MDrv_WriteByte(LD_REG(0x47), u8Val);
}

void MDrv_LD_SetLocalDimmingStrength(U8 u8Val)
{
    //MDrv_WriteByte(0x334A, u8Val);
    MDrv_WriteByte( LD_REG(0x4A), u8Val);
}

void MDrv_LD_SetGlobalDimmingStrength(U8 u8Val)
{
    //MDrv_WriteByte(0x334B, u8Val);
    MDrv_WriteByte( LD_REG(0x4B), u8Val);
}

void MDrv_LD_SetCompensationEnable(BOOL bEn)
{
    //MDrv_WriteByteMask(0x338C, (bEn&_BIT0)<<6, _BIT6);
    MDrv_WriteByteMask(LD_REG(0x8C), (bEn&_BIT0)<<6, _BIT6);
}

void MDrv_LD_SetCompensationGain(U8 u8Val)
{
    if(u8Val>0x10)
        {u8Val=0x10;}//range: 0~16

    //MDrv_Write2ByteMask(0x3378, ((U16)u8Val)<<4, 0x01F0);// bit 4~ 8
    MDrv_Write2ByteMask(LD_REG(0x78), ((U16)u8Val)<<4, 0x01F0);// bit 4~ 8
}

#if 0
void MDrv_LD_DemoModeInit(void)
{
#if 0//((CustomerType == CustomerType_CMI_Ultrasonic)||(CustomerType == CustomerType_INX_Ubike))
    MDrv_LD_SetCompensationEnable(_DISABLE);//case 3   //hardcode refine 20150310
#else
    MDrv_LD_SetCompensationEnable(_ENABLE);//case 3   //hardcode refine 20150310
#endif

    //MDrv_Write2Byte(0x33BE, 0x0FFF);//case 2
    MDrv_Write2Byte(LD_REG(0xBE), 0x0FFF);//case 2
    //MDrv_Write2Byte(0x33F8, 0x0FFF);//case 2
    MDrv_Write2Byte(LD_REG(0xF8), 0x0FFF);//case 2

    {//case 1   //hardcode refine 20150310
        MDrv_LD_SetLedControlNumber(0);
        MDrv_LD_SetLedControlMode(0);
    }

    // Comment by Daniel
#if 0// (PANEL_TYPE_SEL == PNL_LTA750HQ01_VX1_FHD_240HZ)
    MDrv_Write2Byte(0x333E, 0x0084); //case 1,3
    MDrv_WriteByte(0x33ED, 0x06); //case 1,3
    MDrv_WriteByte(0x338A, 0x10);  //Unicorn ECO item register conflic 3376[7:0]->3345[7:0]
#endif
}

void MDrv_LD_SetDemoMode(U8 mode)
{
    switch(mode)
    {
    /*
        case 0:
            gbdemo_case4_enable =FALSE;
            break;
    */
        case 1:
            //MDrv_Write2Byte(0x3344, 0x0002); // left panel : LD on,  right panel : LD off
            MDrv_Write2Byte(LD_REG(0x44), 0x0002); // left panel : LD on,  right panel : LD off

            //MDrv_WriteByte(0x3346, 0xFF);
            MDrv_WriteByte(LD_REG(0x46), 0xFF);

            // Comment by Daniel

#if 0//(PANEL_TYPE_SEL == PNL_LTA750HQ01_VX1_FHD_240HZ)
            MDrv_Write2Byte(0x333E, 0x0088); //case 1,3
            MDrv_WriteByte(0x33ED, 0x00 ); //case 1,3
            MDrv_WriteByte(0x338A, 0x00);  //Unicorn ECO item register conflic 3376[7:0]->3345[7:0]
#endif
            break;

        case 2://show LD backlight L/R compare

            //MDrv_Write2Byte(0x3344, 0x0005); // left panel : LD on,  right panel : LD off
            MDrv_Write2Byte(LD_REG(0x44), 0x0005); // left panel : LD on,  right panel : LD off

            //MDrv_WriteByte(0x3346, 0xFF);
            MDrv_WriteByte(LD_REG(0x46), 0xFF);

            //MDrv_WriteByteMask(0x338C, 0, _BIT6);
            MDrv_WriteByteMask(LD_REG(0x8C), 0, _BIT6);

            //MDrv_Write2Byte(0x33BE, 0);//R
            MDrv_Write2Byte(LD_REG(0xBE), 0);//R

            //MDrv_Write2Byte(0x33F8, 0x0FFF);//L
            MDrv_Write2Byte(LD_REG(0xF8), 0x0FFF);//L
            break;

        case 3://show LD backlight
            //MDrv_WriteByteMask(0x338C, 0, _BIT6);
            MDrv_WriteByteMask(LD_REG(0x8C), 0, _BIT6);

    // Comment by Daniel
#if 0//(PANEL_TYPE_SEL == PNL_LTA750HQ01_VX1_FHD_240HZ)
            MDrv_Write2Byte(0x333E, 0x0088); //case 1,3
            MDrv_WriteByte(0x33ED, 0x00 ); //case 1,3
            MDrv_WriteByte(0x338A, 0x00);  //Unicorn ECO item register conflic 3376[7:0]->3345[7:0]
#endif
            break;

        case 4:// black light LED sequential running
            {
                //MDrv_Write2ByteMask(0x3344, 0x7000, 0xF000); // 0x45 high-byte = 0x7 . demo mode
                MDrv_Write2ByteMask(LD_REG(0x44), 0x7000, 0xF000); // 0x45 high-byte = 0x7 . demo mode

                //MDrv_Write2Byte(0x3346, 0xFFFF);
                MDrv_Write2Byte(LD_REG(0x46), 0xFFFF);

                //MDrv_WriteByteMask(0x338C, 0, _BIT6);
                MDrv_WriteByteMask(LD_REG(0x8C), 0, _BIT6);
//                _MApi_LD_Set_Enable_DemoMode_Case4(TRUE,4);
            }
            break;
        default:
            break;
    }
}
#endif

void MDrv_LD_SetSpiOuputAvg(U8 u8Val)
{
    //MDrv_WriteByte(0x3355,u8Val);
    MDrv_WriteByte(LD_REG(0x55),u8Val);
}

void MDrv_LD_SetSpiOuputMin(U8 u8Val)
{
    //MDrv_WriteByte(0x3356,u8Val);
    MDrv_WriteByte(LD_REG(0x56),u8Val);
}

void MDrv_LD_SetSpiOuputMax(U8 u8Val)
{
    //MDrv_WriteByte(0x3357,u8Val);
    MDrv_WriteByte(LD_REG(0x57),u8Val);
}
#endif

#endif // LD_ENABLE

#undef _MDRV_LD_C_
