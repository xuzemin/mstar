
#include "Board.h"


#if (ENABLE_TEST_PATTERN)

#include "Analog_Reg.h"
#include "color_reg.h"

#include "InfoBlock.h"
#include "SysInit.h"
#include "Utl.h"

#include "drvGlobal.h"
#include "drvPQ.h"

#include "msAPI_Timer.h"

#include "apiXC_Sys.h"
#include "msAPI_BDMA.h"
#include "msAPI_TestPattern.h"

#include "MApp_InputSource.h"
//#include "MApp_XC_PQ.h"

//=================================================================

#define DEBUG_TEST_PATTERN(x)  // x


typedef struct
{
    U32  u32X;
    U32  u32Y;
    U8  u8R;
    U8  u8G;
    U8  u8B;
    U32  u8PicWidth;
}stuPixelInfo;


static BOOL s_TestPattern_bEnable = FALSE;

static U16 s_TestPattern_u16PanelWidth;
static U16 s_TestPattern_u16PanelHigh;

static U16 s_TestPattern_u16MemOffset;
static U16 s_TestPattern_u16MemVLen;

static U32 s_TestPattern_u32DestBufMemAddr;
static U32 s_TestPattern_u32DestBufMemSize;

static U8* s_TestPattern_pu8DstBuf;// = (U8 *)MsOS_PA2KSEG0(SCALER_DNR_BUF_ADR);
static U8* s_TestPattern_pu8DstBuf_NonCache;// = (U8 *)MsOS_PA2KSEG0(SCALER_DNR_BUF_ADR);

static BOOL s_TestPattern_bBackupFreeze;

static BOOL s_TestPattern_bDebugUart = FALSE;


typedef struct
{
    U8 u8R;
    U8 u8G;
    U8 u8B;
} StuTestPatternColor;

static StuTestPatternColor s_TestPattern_stCurColor;

#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)   \
    )
    #define PIX_AlIGN   16
#elif( CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA )
    #define PIX_AlIGN   8
#else
    #define PIX_AlIGN   8  //16 for A6
#endif
static void _DrawBMP_Init(void)
{
    U16 u16MemOffset =1376; //(uc16PicWidth + PIX_AlIGN)&~(PIX_AlIGN-1);
    U16 u16OPMFetch = 1366; //(uc16PicWidth)&~1;
    BOOL bUseScalerUtopia = TRUE;


    DEBUG_TEST_PATTERN(printf("_DrawBMP_Init()\n"););

    s_TestPattern_u16PanelWidth = g_IPanel.Width();
    s_TestPattern_u16PanelHigh = g_IPanel.Height();

    if( s_TestPattern_u16PanelWidth == 1366)
    {
       u16MemOffset =1376; //1376 for A6; //(uc16PicWidth + PIX_AlIGN)&~(PIX_AlIGN-1);
       u16OPMFetch = 1366;//(uc16PicWidth)&~1;
    }
    else if(s_TestPattern_u16PanelWidth == 1600)
    {
       u16MemOffset = 1600;//1376 for A6; //(uc16PicWidth + PIX_AlIGN)&~(PIX_AlIGN-1);
       u16OPMFetch = 1600;//(uc16PicWidth)&~1;
    }
    else if(s_TestPattern_u16PanelWidth == 1920)
    {
       u16MemOffset = 1920;//(uc16PicWidth + PIX_AlIGN)&~(PIX_AlIGN-1);
       u16OPMFetch = 1920;//(uc16PicWidth)&~1;
    }

    s_TestPattern_u16MemOffset = u16MemOffset;
    s_TestPattern_u16MemVLen = s_TestPattern_u16PanelHigh;

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)
    s_TestPattern_u32DestBufMemAddr = SCALER_FB_NO_VDEC_ADR;
#else
    s_TestPattern_u32DestBufMemAddr = ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));
#endif

    //s_TestPattern_u32DestBufMemSize = 1920 * 1080 * 3; // Max
    s_TestPattern_u32DestBufMemSize = s_TestPattern_u16MemOffset * s_TestPattern_u16MemVLen * 3; // Max

    s_TestPattern_pu8DstBuf = (U8 *)MsOS_PA2KSEG0(s_TestPattern_u32DestBufMemAddr);
    s_TestPattern_pu8DstBuf_NonCache = (U8*)MsOS_PA2KSEG1(s_TestPattern_u32DestBufMemAddr);

    DEBUG_TEST_PATTERN(printf(" s_TestPattern_u16PanelWidth=0x%X\n", s_TestPattern_u16PanelWidth););
    DEBUG_TEST_PATTERN(printf(" s_TestPattern_u16PanelHigh=0x%X\n", s_TestPattern_u16PanelHigh););

    DEBUG_TEST_PATTERN(printf(" s_TestPattern_u16MemOffset=0x%X\n", s_TestPattern_u16MemOffset););
    DEBUG_TEST_PATTERN(printf(" u16OPMFetch=0x%X\n", u16OPMFetch););
    DEBUG_TEST_PATTERN(printf(" u16MemVLen=0x%X\n", s_TestPattern_u16MemVLen););

    DEBUG_TEST_PATTERN(printf(" s_TestPattern_u32DestBufMemAddr=0x%X\n", s_TestPattern_u32DestBufMemAddr););
    DEBUG_TEST_PATTERN(printf(" s_TestPattern_u32DestBufMemSize=0x%X\n", s_TestPattern_u32DestBufMemSize););

    DEBUG_TEST_PATTERN(printf("s_TestPattern_pu8DstBuf=0x%X\n", s_TestPattern_pu8DstBuf););
    DEBUG_TEST_PATTERN(printf("s_TestPattern_pu8DstBuf_NonCache=0x%X\n", s_TestPattern_pu8DstBuf_NonCache););


    MApi_XC_DisableInputSource(TRUE, MAIN_WINDOW);

    MApi_XC_SetFrameBufferAddress( s_TestPattern_u32DestBufMemAddr, SCALER_DNR_BUF_LEN, MAIN_WINDOW);

    MApi_XC_EnableFrameBufferLess(DISABLE);

    MApi_XC_FreezeImg(ENABLE, MAIN_WINDOW);


    if( bUseScalerUtopia )
    {
        XC_SETWIN_INFO stXCSetWinInfo;

        memset( &stXCSetWinInfo, 0, sizeof(XC_SETWIN_INFO) );

        stXCSetWinInfo.enInputSourceType = INPUT_SOURCE_VGA;
        stXCSetWinInfo.stCapWin.width = u16OPMFetch;
        stXCSetWinInfo.stCapWin.height = s_TestPattern_u16MemVLen;
        stXCSetWinInfo.stCropWin.width = u16OPMFetch;
        stXCSetWinInfo.stCropWin.height = s_TestPattern_u16MemVLen;
        stXCSetWinInfo.stDispWin.width = u16OPMFetch;
        stXCSetWinInfo.stDispWin.height = s_TestPattern_u16MemVLen;

        stXCSetWinInfo.bInterlace = FALSE;
        stXCSetWinInfo.bHDuplicate = FALSE;
        stXCSetWinInfo.u16InputVFreq = 600;
        stXCSetWinInfo.u16InputVTotal = 1125;
        stXCSetWinInfo.u16DefaultHtotal = 2200;
//        MS_U8  u8DefaultPhase;          ///<Obsolete

        if( MApi_XC_SetWindow(&stXCSetWinInfo, sizeof(XC_SETWIN_INFO), MAIN_WINDOW) == FALSE )
        {
            printf("\nError: MApi_XC_SetWindow() failed\n");
        }
    }
    else
    {
        MDrv_PQ_ForceSrcType(PQ_MAIN_WINDOW, MDrv_PQ_Get_Test_Pattern_SrcType());
        MDrv_PQ_LoadSettings(PQ_MAIN_WINDOW);
    }


    // Setup scaler ...

    //U8 u8XcBank = MApi_XC_ReadByte(0x102F00);

    //MDrv_WriteByte( BK_SELECT_00, REG_BANK_SCMI );
    //MDrv_WriteByteMask( L_BK_SCMI(0x19), 0x01, 0x1F );// force count
    //MDrv_WriteByteMask( H_BK_SCMI(0x19), 0x00, BIT1|BIT0 );// disable 6read/8 read mode
    MApi_XC_W2BYTEMSK( REG_SC_BK12_19_L, 0x01, 0x31F );// force count
    //MApi_XC_W2BYTEMSK( REG_SC_BK12_19_H, 0x00, BIT1|BIT0 );// disable 6read/8 read mode

    //MDrv_WriteRegBit( H_BK_SCMI(0x07), 1, BIT3 );// force R bank
    //MDrv_WriteByteMask( H_BK_SCMI(0x07), 0x00, BIT2|BIT1|BIT0 );
    MApi_XC_W2BYTEMSK( REG_SC_BK12_07_L, 0x0800, 0x0F00 );// force R bank

    //MDrv_WriteByteMask( L_BK_SCMI(0x01), 0x10, BIT5|BIT4 ); // 8 bit ps
    MApi_XC_W2BYTEMSK( REG_SC_BK12_01_L, 0x10, BIT5|BIT4 ); // 8 bit ps


    //printf("\r\n  u16MemOffset  %u u16OPMFetch %u",u16MemOffset,u16OPMFetch);
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_SCMI);
    //MDrv_Write2Byte(L_BK_SCMI(0x16), s_TestPattern_u16MemOffset); // output offset
    //MDrv_Write2Byte(L_BK_SCMI(0x17), u16OPMFetch);  // output fetch
    MApi_XC_W2BYTE(REG_SC_BK12_16_L, s_TestPattern_u16MemOffset); // output offset
    MApi_XC_W2BYTE(REG_SC_BK12_17_L, u16OPMFetch);  // output fetch


    //memory format
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_SCMI);
    //MDrv_Write2Byte( L_BK_SCMI(0x02), 0x00); // Memory config
    MApi_XC_W2BYTE(REG_SC_BK12_02_L, 0); // Memory config

    // Write V length
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_PIP);
    //MDrv_Write2Byte(L_BK_PIP(0x15), s_TestPattern_u16MemVLen);// V_Length
    MApi_XC_W2BYTE(REG_SC_BK20_15_L, s_TestPattern_u16MemVLen);// V_Length

    //REG_SC_BK20_1D_L[7:0]  main LB offset
    MApi_XC_W2BYTEMSK(REG_SC_BK20_1D_L, 0, 0xFF); // main LB offset=0

    //REG_SC_BK20_1C_L[7:0]  main Disp offset
    MApi_XC_W2BYTEMSK(REG_SC_BK20_1C_L, 0, 0xFF); // main Disp offset=0

    //hor scaling
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_HVSP); // Bank 23
    //MDrv_WriteByteMask(H_BK_HVSP(0x08), 0x00, BIT0);
    MApi_XC_W2BYTEMSK(REG_SC_BK23_08_L, 0x00, 0x0100); // Scaling off

    //Vertical scaling
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_HVSP); // Bank 23
    //MDrv_WriteByteMask(H_BK_HVSP(0x0A), 0x00, BIT0); // Scaling off
    MApi_XC_W2BYTEMSK(REG_SC_BK23_0A_L, 0x00, 0x0100); // Scaling off

    // H/V Scaling filter off
    MApi_XC_W2BYTEMSK(REG_SC_BK23_0B_L, 0x0000, 0xFFFF );

    //YUV 444->422
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_HVSP);
    //MDrv_WriteByteMask(L_BK_HVSP(0x0C), 0x00, BIT7); // Format 422 Off
    MApi_XC_W2BYTEMSK(REG_SC_BK23_0C_L, 0x00, BIT7 ); // Format 422 Off


    //MDrv_WriteByte( BK_SELECT_00, 0x27 );
    //MDrv_WriteByte( 0x102FE0, 0x01 );   // VIP ByPass
    MApi_XC_W2BYTEMSK(REG_SC_BK27_70_L, 0x0001, 0x0001 ); // VIP ByPass

    //(CSC OFF)
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_VIP); // Bank 18
    //MDrv_WriteByte(L_BK_HVSP(0x6E), 0x00); // CSC off
    MApi_XC_W2BYTEMSK(REG_SC_BK18_6E_L, 0x0000, 0x00FF ); // CSC off


    //  3X3 ByPass = RGB
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_VOP); // Bank 10
    //MDrv_WriteByte(0x102F5E, 0x00); // Color Matrix Off
    MApi_XC_W2BYTEMSK(REG_SC_BK10_2F_L, 0x0000, 0x00FF ); // Color Matrix Off


    // Gamma LUT Off
    //MDrv_WriteByte(BK_SELECT_00, REG_BANK_VOP); // Bank 10
    //MDrv_WriteByteMask(0x102FA0, 0x00, BIT0 ); // Gamma Off
    MApi_XC_W2BYTEMSK(REG_SC_BK10_50_L, 0x0000, BIT0 ); // Gamma Off

    //MApi_XC_WriteByte(0x102F00, u8XcBank);


    DEBUG_TEST_PATTERN(printf("_DrawBMP_Init() end\n"););
}

static void _SetDstbufPixData(stuPixelInfo  *pPixelInfo)
{
    U8* pDstBuf;
    U32 u8AlignSegment;

    //U16 u16X;
    //U16 u16Y;
    U32 u32OffsetR;
    U32 u32OffsetG;
    U32 u32OffsetB;


    //u16X = pPixelInfo->u32X;
    //u16Y = pPixelInfo->u32Y;

    //pDstBuf = (U8 *)MsOS_PA2KSEG0(SCALER_DNR_BUF_ADR);
    pDstBuf = s_TestPattern_pu8DstBuf;

    u8AlignSegment = pPixelInfo->u32X / PIX_AlIGN;

    pPixelInfo->u32X %= PIX_AlIGN;

    if( pPixelInfo->u8PicWidth%PIX_AlIGN )
    {
        pPixelInfo->u8PicWidth = (pPixelInfo->u8PicWidth+PIX_AlIGN)&~(PIX_AlIGN-1);
        if( s_TestPattern_bDebugUart )
        {
            printf("pPixelInfo->u8PicWidth align to 0x%X\n", pPixelInfo->u8PicWidth);
        }
    }


    u32OffsetB = (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X;

    u32OffsetG = u32OffsetB + PIX_AlIGN; //(pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X + PIX_AlIGN;
    u32OffsetR = u32OffsetB + PIX_AlIGN + PIX_AlIGN;//(pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X + PIX_AlIGN*2;

#if 1
    pDstBuf[u32OffsetR] = pPixelInfo->u8R;
    pDstBuf[u32OffsetG] = pPixelInfo->u8G;
    pDstBuf[u32OffsetB] = pPixelInfo->u8B;

#else
    *(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X) = pPixelInfo->u8B;
    *(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X+ PIX_AlIGN) = pPixelInfo->u8G;
    *(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X + PIX_AlIGN*2) = pPixelInfo->u8R;
#endif

    if( s_TestPattern_bDebugUart )
    {
        //printf("{0x%X}", (U32)&(pDstBuf[u32OffsetB]), (U32)&(pDstBuf[u32OffsetG]),(U32)&(pDstBuf[u32OffsetR]));
    }


    if(0)//(pPixelInfo->u32Y ==0)
    {
        printf("\r\n DST <%x, %x, %x>", pPixelInfo->u8B, pPixelInfo->u8G, pPixelInfo->u8R);
        printf("--( %x,",(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X) );
        printf(" %x,",(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X+ PIX_AlIGN));
        printf(" %x)",(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X + PIX_AlIGN*2));
        printf("--( %x,",*(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X) );
        printf(" %x,",*(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X+ PIX_AlIGN));
        printf(" %x)",*(pDstBuf + (pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X + PIX_AlIGN*2));
    }
/*
    if(u8Flag)
    {
        printf("\r\n( %lx,",((pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X) );
        printf(" %lx,",((pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X+ PIX_AlIGN) );
        printf(" %lx)",((pPixelInfo->u8PicWidth*pPixelInfo->u32Y)*3 + u8AlignSegment*PIX_AlIGN*3 + pPixelInfo->u32X + PIX_AlIGN*2) );
    }
*/
}

static void _msAPI_TestPattern_FlushAllMemory(void)
{
    MsOS_Dcache_Flush( (U32)s_TestPattern_pu8DstBuf, s_TestPattern_u32DestBufMemSize);
    MsOS_FlushMemory();
}

#if( ENABLE_BMP_TEST_PATTERN )
static void _GetSrcbufPixData(stuPixelInfo  *pPixelInfo)
{
    U8* pSrcBuf;
    U8 alig;



    pSrcBuf = (U8 *)MsOS_PA2KSEG0(TEST_PATTERN_DEC_BUF_ADR+0x36);// offset header = 0x36
    alig=pPixelInfo->u8PicWidth%4;


    //width is alignment to 4's multiple
#if 1
    pPixelInfo->u8B = *(pSrcBuf + (pPixelInfo->u32Y*pPixelInfo->u8PicWidth + pPixelInfo->u32X)*3 + (pPixelInfo->u32Y)*alig);
    pPixelInfo->u8G = *(pSrcBuf + (pPixelInfo->u32Y*pPixelInfo->u8PicWidth + pPixelInfo->u32X)*3 + 1 + (pPixelInfo->u32Y)*alig);
    pPixelInfo->u8R = *(pSrcBuf + (pPixelInfo->u32Y*pPixelInfo->u8PicWidth + pPixelInfo->u32X)*3 + 2 + (pPixelInfo->u32Y)*alig);

#endif
#if 0
    pPixelInfo->u8B = *(pSrcBuf + (pPixelInfo->u32Y*pPixelInfo->u8PicWidth + pPixelInfo->u32X)*3 );
    pPixelInfo->u8G = *(pSrcBuf + (pPixelInfo->u32Y*pPixelInfo->u8PicWidth + pPixelInfo->u32X)*3 +1);
    pPixelInfo->u8R = *(pSrcBuf + (pPixelInfo->u32Y*pPixelInfo->u8PicWidth + pPixelInfo->u32X)*3 +2);
    #endif

    //printf("\r\n SRC:[ %bx, %bx, %bx]", pPixelInfo->u8B, pPixelInfo->u8G, pPixelInfo->u8R );
}

static U32 _GetBMPSize(U8* pbuf)
{
    U32 u32Tmp=0;

    u32Tmp = *(pbuf+3);
    //printf("a %d b%d  c%d  d%d  \r\n",*(pbuf+3),*(pbuf+2),*(pbuf+1),*(pbuf));
    u32Tmp<<=8;
    u32Tmp |= *(pbuf+2);
    u32Tmp<<=8;
    u32Tmp |= *(pbuf+1);
    u32Tmp<<=8;
    u32Tmp |= *pbuf;

    return u32Tmp;
}

static stuPixelInfo stuPixelData;

static void _BitmapFormatConversion(void)
{
    U32 u32Width, u32Height;
    U8* pSrcBuf;


    pSrcBuf =  (U8 *)MsOS_PA2KSEG0((TEST_PATTERN_DEC_BUF_ADR));//(MAD_JPEG_INTERBUFF_ADR);// offset = 0x36
    //pSrcBuf =  (U8 *)MsOS_PA2KSEG0(DOWNLOAD_BUFFER_ADR+ (DOWNLOAD_BUFFER_LEN));  // offset = 0x36

    u32Width = _GetBMPSize(pSrcBuf+0x12);
    u32Height = _GetBMPSize(pSrcBuf+0x16);
    printf(" BMP size: u32Width=%lu , u32Height=%lu\n", u32Width, u32Height);

    stuPixelData.u8PicWidth = u32Width;

    //KI modify it for PANEL code mirror
    {
        U16 u16SrcX, u16SrcY, u16DstX;
        int iDstY;

        if (0) // (MApi_MirrorEnable())
        {
                for( iDstY = g_IPanel.Height()-1; iDstY >= 0 ; -- iDstY ) // From last line to line-0
                {

                    u16SrcY = iDstY % u32Height;
                    for( u16DstX = 0; u16DstX < g_IPanel.Width(); u16DstX += 1 )
                    {
                        u16SrcX = u16DstX % u32Width;

                        u16SrcX = (u32Width-1) - u16SrcX;

                        stuPixelData.u32X = u16SrcX;
                        stuPixelData.u32Y = u16SrcY;
                        stuPixelData.u8PicWidth = u32Width;
                        _GetSrcbufPixData(&stuPixelData);

                        stuPixelData.u8PicWidth = g_IPanel.Width();
                        stuPixelData.u32X = u16DstX;
                        stuPixelData.u32Y = iDstY;
                        _SetDstbufPixData(&stuPixelData);
                    }
                }

        }
        else
        {

                for( iDstY = 0; iDstY < s_TestPattern_u16PanelHigh/*g_IPanel.Height()*/; ++ iDstY ) // From line-0 to last line
                {

                    u16SrcY = iDstY % u32Height;
                    u16SrcY = (u32Height-1) - u16SrcY; // BMP format is revere

                    for( u16DstX = 0; u16DstX < g_IPanel.Width(); u16DstX += 1 )
                    {
                        u16SrcX = u16DstX % u32Width;

                        stuPixelData.u32X = u16SrcX;
                        stuPixelData.u32Y = u16SrcY;
                        stuPixelData.u8PicWidth = u32Width;
                        _GetSrcbufPixData(&stuPixelData);

                        //printf("{%X,%X,%X}", stuPixelData.u8R,stuPixelData.u8G,stuPixelData.u8B );

                        stuPixelData.u8PicWidth = g_IPanel.Width();
                        stuPixelData.u32X = u16DstX;
                        stuPixelData.u32Y = iDstY;

                        _SetDstbufPixData(&stuPixelData);
                    }
                }

        }
    }

    _msAPI_TestPattern_FlushAllMemory();

    //printf("\r\nFinish!!");
}

static U16 tBitmapfileID[]=
{
     BIN_ID_BMP_TestPattern_0,
     BIN_ID_BMP_TestPattern_1,
};

static BOOLEAN _BitmapDecompress(U8 u8BitmapFileNo)
{
    BININFO BinInfo;
    BOOLEAN bResult;
    U32 u32BMPAddr = (TEST_PATTERN_DEC_BUF_ADR) ; //(VDEC_FRAMEBUFFER_ADR+ (VDEC_FRAMEBUFFER_LEN/2)); //MAD_JPEG_INTERBUFF_ADR;
    //U32 u32BMPAddr =  DOWNLOAD_BUFFER_ADR+ (DOWNLOAD_BUFFER_LEN);


    // Check array size
    if( u8BitmapFileNo >= (sizeof(tBitmapfileID)/sizeof(U16)) )
    {
        printf("\nError: u8BitmapFileNo=%u is over bmp file array!\n", u8BitmapFileNo);
        return FALSE;
    }

    BinInfo.B_ID = tBitmapfileID[u8BitmapFileNo];

    //printf("\r\n  u8BitmapFileNo = %d ",u8BitmapFileNo);
    //printf("\r\n  tBitmapfileID[u8BitmapFileNo] = %d ",tBitmapfileID[u8BitmapFileNo]);

    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if( bResult == FALSE )
    {
        printf("\nError: Get bin info failed!\n");
        return FALSE;
    }

    //printf("\r\n BMP = %x, %lx, %lx, %bd",  BinInfo.B_ID,  BinInfo.B_FAddr,  BinInfo.B_Len, (U16)BinInfo.B_IsComp);

    if (SUCCESS == MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32BMPAddr), _PA2VA(TEST_PATTERN_SRC_BUF_ADR), _PA2VA(TEST_PATTERN_TMP_BUF_ADR)))
    {
        //printf("\r\n Decompress pass!");
        return true;
    }
    else
    {
        //printf("\r\n Decompress fail!");
        printf("\n MDrv_DMA_LoadBin() fail!\n");
        return false;
    }
}

BOOL msAPI_TestPattern_DrawBitmap(U8 u8TPNo)
{
    BOOL bResult = TRUE;


    printf("msAPI_TestPattern_DrawBitmap(%u)\n", u8TPNo);


    bResult = _BitmapDecompress(u8TPNo);
    if( bResult == FALSE )
    {
        printf("\nError: _BitmapDecompress() fail !!\n");
        return FALSE;
    }

   // MApi_XC_DisableInputSource(TRUE, MAIN_WINDOW);

    // Init HW
    //_DrawBMP_Init();

    // Convert bmp buffer to scaler buffer
    _BitmapFormatConversion();

    //MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);

    //MApi_XC_GenerateBlackVideo( DISABLE, MAIN_WINDOW );

    return bResult;
}

#endif

void msAPI_TestPattern_Init(void)
{
    s_TestPattern_bEnable = TRUE;

    s_TestPattern_bBackupFreeze = MApi_XC_IsFreezeImg(MAIN_WINDOW);

    // disable input source
    MApi_XC_DisableInputSource(TRUE, MAIN_WINDOW);

    //MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
    //MApi_XC_EnableFrameBufferLess(DISABLE);

    MApi_XC_FreezeImg(ENABLE, MAIN_WINDOW);

   // Disable Some HW Engines ...

#if 0//(ENABLE_VE)
    {
        MS_VE_Output_Ctrl OutputCtrl;
        // disable VE
        OutputCtrl.bEnable = FALSE;
        msAPI_VE_SetOutputCtrl(&OutputCtrl);
    }
#endif

    _DrawBMP_Init();

    //if (IsDTVInUse())
    //     msAPI_VID_Command(MSAPI_VID_STOP);
}

void msAPI_TestPattern_Exit(void)
{
    s_TestPattern_bEnable = FALSE;

    //MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
    msAPI_Scaler_SetBlueScreen(ENABLE, 0, 0, MAIN_WINDOW);

    //if (IsDTVInUse())
    //    msAPI_VID_Command(MSAPI_VID_PLAY);

    MApi_XC_FreezeImg(s_TestPattern_bBackupFreeze, MAIN_WINDOW);
}

BOOL msAPI_TestPattern_Get_Status(void)
{
    return s_TestPattern_bEnable;
}

void msAPI_TestPattern_Set_CurColor(U8 u8R, U8 u8G, U8 u8B)
{
    s_TestPattern_stCurColor.u8R = u8R;
    s_TestPattern_stCurColor.u8G = u8G;
    s_TestPattern_stCurColor.u8B = u8B;
}

BOOL msAPI_TestPattern_ClearMemory(void)
{
    U32 u32ClearSize = s_TestPattern_u32DestBufMemSize;

    //printf("msAPI_TestPattern_ClearMemory()\n");

    //printf(" u32ClearSize=%u\n", u32ClearSize);

    memset( s_TestPattern_pu8DstBuf, 0,  u32ClearSize);

    _msAPI_TestPattern_FlushAllMemory();

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_FullScreen_White(void)
{
    U32 u32ClearSize = s_TestPattern_u32DestBufMemSize;

    printf("msAPI_TestPattern_Draw_FullScreen_White()\n");

    //printf(" u32ClearSize=%u\n", u32ClearSize);

    memset( s_TestPattern_pu8DstBuf, 0xFF,  u32ClearSize);

    _msAPI_TestPattern_FlushAllMemory();

    return TRUE;
}

#define TEST_PAT_MEM_OFFSET_BY_LINE(line)   (s_TestPattern_u16MemOffset * 3 * (line))

void _msAPI_TestPattern_CopyLine( U16 u16SrcLineIdx, U16 u16TgtLineIdx, U16 u16LineCount, BOOLEAN bFlushMem )
{
    U32 u32CopySize = s_TestPattern_u16MemOffset * 3 * u16LineCount;

    memcpy( s_TestPattern_pu8DstBuf+TEST_PAT_MEM_OFFSET_BY_LINE(u16TgtLineIdx),
            s_TestPattern_pu8DstBuf+TEST_PAT_MEM_OFFSET_BY_LINE(u16SrcLineIdx),  u32CopySize);

    if( bFlushMem )
    {
        _msAPI_TestPattern_FlushAllMemory();
    }
}

void _msAPI_TestPattern_CopyLine_Short( U16 u16SrcLineIdx, U16 u16TgtLineIdx, U16 u16XStart, U16 u16PixelCount, BOOLEAN bFlushMem )
{
    U32 u32CopySize = 3 * u16PixelCount;

    memcpy( s_TestPattern_pu8DstBuf+TEST_PAT_MEM_OFFSET_BY_LINE(u16TgtLineIdx) + u16XStart*3,
            s_TestPattern_pu8DstBuf+TEST_PAT_MEM_OFFSET_BY_LINE(u16SrcLineIdx) + u16XStart*3, u32CopySize);

    if( bFlushMem )
    {
        _msAPI_TestPattern_FlushAllMemory();
    }
}

void msAPI_TestPattern_DrawPixel(U16 u16XStart, U16 u16YStart)
{
    stuPixelInfo stuPixel;

    stuPixel.u32X = u16XStart;
    stuPixel.u32Y = u16YStart;
    stuPixel.u8R = s_TestPattern_stCurColor.u8R;
    stuPixel.u8G = s_TestPattern_stCurColor.u8G;
    stuPixel.u8B = s_TestPattern_stCurColor.u8B;

    _SetDstbufPixData(&stuPixel);
}

BOOL msAPI_TestPattern_DrawLine_H(U16 u16XStart, U16 u16YStart, U16 u16Len)
{
    U16 i;
    stuPixelInfo stuPixel;

    //DEBUG_TEST_PATTERN(printf("Line_H: %u,%u,%u\n", u16XStart, u16YStart, u16Len););

    if( u16XStart >= s_TestPattern_u16MemOffset )
        return FALSE;

    if( u16XStart + u16Len > s_TestPattern_u16MemOffset )
    {
        //printf("Line_H: %u,%u,%u\n", u16XStart, u16YStart, u16Len);
        //printf("s_TestPattern_u16MemOffset=%u\n", s_TestPattern_u16MemOffset);

        u16Len = s_TestPattern_u16MemOffset - u16XStart;

        //printf("Line_H: fix u16Len=%u\n", u16Len);
    }

    stuPixel.u8PicWidth = s_TestPattern_u16MemOffset;

    for( i = 0; i < u16Len; i += 1 )
    {
        stuPixel.u32X = u16XStart + i;
        stuPixel.u32Y = u16YStart;
        stuPixel.u8R = s_TestPattern_stCurColor.u8R;
        stuPixel.u8G = s_TestPattern_stCurColor.u8G;
        stuPixel.u8B = s_TestPattern_stCurColor.u8B;
        _SetDstbufPixData(&stuPixel);
    }

    return TRUE;
}

BOOL msAPI_TestPattern_DrawLine_V(U16 u16XStart, U16 u16YStart, U16 u16Len)
{
    U16 i;
    stuPixelInfo stuPixel;

    //DEBUG_TEST_PATTERN(printf("Line_V: %u,%u,%u\n", u16XStart, u16YStart, u16Len););

    if( u16YStart >= s_TestPattern_u16MemVLen )
        return FALSE;

    if( u16YStart + u16Len > s_TestPattern_u16MemVLen )
    {
        u16Len = s_TestPattern_u16MemVLen - u16YStart;
        //printf("Line_V: fix u16Len=%u\n", u16Len);
    }

    stuPixel.u8PicWidth = s_TestPattern_u16MemOffset;

    for( i = 0; i < u16Len; i += 1 )
    {
        stuPixel.u32X = u16XStart;
        stuPixel.u32Y = u16YStart + i;
        stuPixel.u8R = s_TestPattern_stCurColor.u8R;
        stuPixel.u8G = s_TestPattern_stCurColor.u8G;
        stuPixel.u8B = s_TestPattern_stCurColor.u8B;
        _SetDstbufPixData(&stuPixel);
    }

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_Rect_1(U16 u16XStart, U16 u16YStart, U16 u16XSize, U16 u16YSize )
{
    msAPI_TestPattern_DrawLine_H(u16XStart, u16YStart, u16XSize);
    msAPI_TestPattern_DrawLine_V(u16XStart, u16YStart, u16YSize);

    msAPI_TestPattern_DrawLine_H(u16XStart, u16YStart+u16YSize-1, u16XSize);
    msAPI_TestPattern_DrawLine_V(u16XStart+u16XSize-1, u16YStart, u16YSize);

    _msAPI_TestPattern_FlushAllMemory();

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_Rect_2(U16 u16XStart, U16 u16YStart, U16 u16XSize, U16 u16YSize, BOOL bFlushMemory )
{
    U16 i;

    //printf("msAPI_TestPattern_Draw_Rect_2(u16XStart=0x%X, u16YStart=0x%X, u16XSize=0x%X, u16YSize=0x%X)\n", u16XStart, u16YStart, u16XSize, u16YSize);

    if( u16XSize == 0 || u16YSize == 0 )
    {
        return FALSE;
    }

    if( (u16XStart == 0) && (u16XSize >= s_TestPattern_u16PanelWidth ) )
    {
        // More faster
        //printf("Use copy!\n");
        msAPI_TestPattern_DrawLine_H(u16XStart, u16YStart, u16XSize);

        // Copy line
        for( i = 1; i < u16YSize; ++ i )
        {
            _msAPI_TestPattern_CopyLine( u16YStart, u16YStart + i, 1, FALSE );
        }
    }
    else
    {
        if( ((u16XStart%PIX_AlIGN) == 0)&&((u16XSize%PIX_AlIGN) == 0) )
        {
            //printf("[1]\n");

            // Draw first line
            msAPI_TestPattern_DrawLine_H(u16XStart, u16YStart, u16XSize);

            // Copy line
            for( i = 1; i < u16YSize; ++ i )
            {
                _msAPI_TestPattern_CopyLine_Short( u16YStart, u16YStart + i, u16XStart, u16XSize, FALSE );
            }
        }
        else
        {
            //printf("[2]\n");
            for( i = 0; i < u16YSize; ++ i )
            {
                msAPI_TestPattern_DrawLine_H(u16XStart, u16YStart+i, u16XSize);
            }
        }
    }

    if( bFlushMemory )
    {
        _msAPI_TestPattern_FlushAllMemory();
    }

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_Checkbox(void)
{
    U16 u16X;
    U16 u16Y;
    BOOL bFlag = 0;

#define CHECK_BOX_SIZE  128

    printf("msAPI_TestPattern_Draw_Checkbox()\n");

    msAPI_TestPattern_Set_CurColor(0xFF, 0xFF, 0xFF);

    for( u16Y = 0; (u16Y + 0) < s_TestPattern_u16MemVLen; u16Y += CHECK_BOX_SIZE )
    {
        if( bFlag )
            u16X = CHECK_BOX_SIZE;
        else
            u16X = 0;
        for( ; (u16X + 0) < s_TestPattern_u16MemOffset; u16X += (CHECK_BOX_SIZE*2) )
        {
            msAPI_TestPattern_Draw_Rect_2(u16X, u16Y, CHECK_BOX_SIZE, CHECK_BOX_SIZE, FALSE);
        }

        bFlag = !bFlag;
    }

    _msAPI_TestPattern_FlushAllMemory();

    return TRUE;
}

#define TEST_PAT_LEVEL_CHANGE_COLOR(color, step)   do { \
    color = color + step;   \
    if( color > 255 )   \
        color = 255;    \
    else if( color < 0 )    \
        color = 0;  \
} while(0)

BOOL msAPI_TestPattern_Draw_Level(BOOL bIsV,
    U8 u8ColorInitValue_R, U8 u8ColorInitValue_G, U8 u8ColorInitValue_B,
    S8 s8ColorStep_R, S8 s8ColorStep_G, S8 s8ColorStep_B,
    U16 u16RepeatPixelNum)
{
    U16 u16X;
    U16 u16Y;
    S16 s16Color_R, s16Color_G, s16Color_B;
    U16 u16PixelCount = 0;


    printf("msAPI_TestPattern_Draw_Level(v=%u, u8ColorInit=%u,%u,%u, s8ColorStep=%d,%d,%d, u16RepeatPixelNum=%u)\n",
        bIsV,
        u8ColorInitValue_R, u8ColorInitValue_G, u8ColorInitValue_B,
        s8ColorStep_R, s8ColorStep_G, s8ColorStep_B,
        u16RepeatPixelNum);

    s16Color_R = u8ColorInitValue_R;
    s16Color_G = u8ColorInitValue_G;
    s16Color_B = u8ColorInitValue_B;

    msAPI_TestPattern_Set_CurColor(s16Color_R, s16Color_G, s16Color_B);

    if( bIsV )
    {
        for( u16Y = 0; u16Y < s_TestPattern_u16MemVLen; ++ u16Y )
        {
            msAPI_TestPattern_DrawLine_H( 0, u16Y, s_TestPattern_u16MemOffset);

            u16PixelCount += 1;
            if( u16PixelCount >= u16RepeatPixelNum )
            {
                u16PixelCount = 0;

                TEST_PAT_LEVEL_CHANGE_COLOR(s16Color_R, s8ColorStep_R);
                TEST_PAT_LEVEL_CHANGE_COLOR(s16Color_G, s8ColorStep_G);
                TEST_PAT_LEVEL_CHANGE_COLOR(s16Color_B, s8ColorStep_B);

                msAPI_TestPattern_Set_CurColor(s16Color_R, s16Color_G, s16Color_B);
            }
        }

        _msAPI_TestPattern_FlushAllMemory();

    }
    else // Hor
    {
        // Dram 1st line
        for( u16X = 0; u16X < s_TestPattern_u16MemOffset; u16X += 1 )
        {
            //msAPI_TestPattern_DrawLine_V( u16X, 0, s_TestPattern_u16MemVLen);

            msAPI_TestPattern_DrawPixel(u16X, 0);

            u16PixelCount += 1;
            if( u16PixelCount >= u16RepeatPixelNum )
            {
                u16PixelCount = 0;

                TEST_PAT_LEVEL_CHANGE_COLOR(s16Color_R, s8ColorStep_R);
                TEST_PAT_LEVEL_CHANGE_COLOR(s16Color_G, s8ColorStep_G);
                TEST_PAT_LEVEL_CHANGE_COLOR(s16Color_B, s8ColorStep_B);

                msAPI_TestPattern_Set_CurColor(s16Color_R, s16Color_G, s16Color_B);
            }
        }

        // Copy line-0 to line-1~n
        U16 u16LineIdx;
        for( u16LineIdx = 1; u16LineIdx < s_TestPattern_u16MemVLen; ++ u16LineIdx )
        {
            //printf("%u) ", i);
            _msAPI_TestPattern_CopyLine(0, u16LineIdx, 1, FALSE);
        }

        _msAPI_TestPattern_FlushAllMemory();

    }

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_GrayLevel(BOOL bIsV, U8 u8ColorInitValue, S8 s8ColorStep, U16 u16RepeatPixelNum)
{
#if 1
    return msAPI_TestPattern_Draw_Level( bIsV,
        u8ColorInitValue, u8ColorInitValue, u8ColorInitValue,
        s8ColorStep, s8ColorStep, s8ColorStep,
        u16RepeatPixelNum );

#else
    U16 u16X;
    U16 u16Y;
    S16 s16Color;
    U16 u16PixelCount = 0;


    printf("msAPI_TestPattern_Draw_GrayLevel(v=%u, u8ColorInitValue=%u, s8ColorStep=%d, u16RepeatPixelNum=%u)\n",
        bIsV, u8ColorInitValue, s8ColorStep, u16RepeatPixelNum);

    s16Color = u8ColorInitValue;
    msAPI_TestPattern_Set_CurColor(s16Color, s16Color, s16Color);

    if( bIsV )
    {
        for( u16Y = 0; u16Y < s_TestPattern_u16MemVLen; ++ u16Y )
        {
            msAPI_TestPattern_DrawLine_H( 0, u16Y, s_TestPattern_u16MemOffset);

            u16PixelCount += 1;
            if( u16PixelCount >= u16RepeatPixelNum )
            {
                u16PixelCount = 0;

                s16Color = s16Color + s8ColorStep;
                if( s16Color > 255 )
                    s16Color = 255;
                else if( s16Color < 0 )
                    s16Color = 0;
                msAPI_TestPattern_Set_CurColor(s16Color, s16Color, s16Color);
            }
        }
    }
    else // Hor
    {
        for( u16X = 0; u16X < s_TestPattern_u16MemOffset; u16X += 1 )
        {
            msAPI_TestPattern_DrawLine_V( u16X, 0, s_TestPattern_u16MemVLen);

            u16PixelCount += 1;
            if( u16PixelCount >= u16RepeatPixelNum )
            {
                u16PixelCount = 0;

                s16Color = s16Color + s8ColorStep;
                if( s16Color > 255 )
                    s16Color = 255;
                else if( s16Color < 0 )
                    s16Color = 0;
                msAPI_TestPattern_Set_CurColor(s16Color, s16Color, s16Color);
            }
        }
    }

    return TRUE;
#endif
}

BOOL msAPI_TestPattern_Draw_RGB(void)
{
    U16 u16YSize;
    U16 u16YSize_2;

    u16YSize = s_TestPattern_u16MemVLen/3;
    u16YSize_2 = s_TestPattern_u16MemVLen - (u16YSize*2);

    // R Bar
    msAPI_TestPattern_Set_CurColor(0xFF, 0, 0);
    msAPI_TestPattern_Draw_Rect_2(0, 0, s_TestPattern_u16MemOffset, u16YSize, FALSE);

    // G Bar
    msAPI_TestPattern_Set_CurColor(0, 0xFF, 0);
    msAPI_TestPattern_Draw_Rect_2(0, u16YSize, s_TestPattern_u16MemOffset, u16YSize, FALSE);

    // B Bar
    msAPI_TestPattern_Set_CurColor(0, 0, 0xFF);
    msAPI_TestPattern_Draw_Rect_2(0, u16YSize*2, s_TestPattern_u16MemOffset, u16YSize_2, FALSE);

    _msAPI_TestPattern_FlushAllMemory();

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_RGBW(void)
{
    U16 u16YSize;
    U16 u16YSize_2;

    u16YSize = s_TestPattern_u16MemVLen/4;
    u16YSize_2 = s_TestPattern_u16MemVLen - (u16YSize*3);

    // R Bar
    msAPI_TestPattern_Set_CurColor(0xFF, 0, 0);
    msAPI_TestPattern_Draw_Rect_2(0, 0, s_TestPattern_u16MemOffset, u16YSize, FALSE);

    // G Bar
    msAPI_TestPattern_Set_CurColor(0, 0xFF, 0);
    msAPI_TestPattern_Draw_Rect_2(0, u16YSize, s_TestPattern_u16MemOffset, u16YSize, FALSE);

    // B Bar
    msAPI_TestPattern_Set_CurColor(0, 0, 0xFF);
    msAPI_TestPattern_Draw_Rect_2(0, u16YSize*2, s_TestPattern_u16MemOffset, u16YSize, FALSE);

    // W Bar
    msAPI_TestPattern_Set_CurColor(0XFF, 0xFF, 0xFF);
    msAPI_TestPattern_Draw_Rect_2(0, u16YSize*3, s_TestPattern_u16MemOffset, u16YSize_2, FALSE);

    _msAPI_TestPattern_FlushAllMemory();

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_Stripe(BOOL bIsVertical)
{
    U16 u16X;
    U16 u16Y;
    stuPixelInfo stuPixel;

    stuPixel.u8PicWidth = s_TestPattern_u16MemOffset;

    if( bIsVertical )
    {
        // Draw 1st line
        for( u16X = 0; u16X < s_TestPattern_u16MemOffset; u16X += 2 )
        {
            stuPixel.u32X = u16X;
            stuPixel.u32Y = 0;
            stuPixel.u8R = s_TestPattern_stCurColor.u8R;
            stuPixel.u8G = s_TestPattern_stCurColor.u8G;
            stuPixel.u8B = s_TestPattern_stCurColor.u8B;
            _SetDstbufPixData(&stuPixel);
        }

        // Copy 1st line to other line
        for( u16Y = 1; u16Y < s_TestPattern_u16MemVLen; ++ u16Y )
        {
            _msAPI_TestPattern_CopyLine( 0, u16Y, 1, FALSE );
        }

        //_msAPI_TestPattern_FlushAllMemory();
    }
    else
    {
        // Draw 1st line
        msAPI_TestPattern_DrawLine_H(0,0,s_TestPattern_u16MemOffset);

        // 2nd line is black

        // Copy first 2 line to other line
        for( u16Y = 2; u16Y < s_TestPattern_u16MemVLen; u16Y += 2 )
        {
            _msAPI_TestPattern_CopyLine( 0, u16Y, 2, FALSE );
        }

        //_msAPI_TestPattern_FlushAllMemory();
    }

    _msAPI_TestPattern_FlushAllMemory();

    return TRUE;
}

BOOL msAPI_TestPattern_Draw_COLOR_BAR(void)
{
#define COLOR_BAR_COLOR_NUM 8
    U8 au8Color[COLOR_BAR_COLOR_NUM][3] =
    {
        {0xFF,  0xFF,   0xFF},
        {0xFF,  0xFF,   0   },
        {0,     0xFF,   0xFF},
        {0,     0xFF,   0   },
        {0xFF,  0,      0xFF},
        {0xFF,  0,      0   },
        {0,     0,      0xFF},
        {0,     0,      0   },
    };

    U16 i;
    U16 u16XStart, u16XSize;

    u16XSize = s_TestPattern_u16PanelWidth / COLOR_BAR_COLOR_NUM;

#if 1

    for( i = 0; i < COLOR_BAR_COLOR_NUM; ++ i )
    {
        u16XStart = u16XSize * i;
        msAPI_TestPattern_Set_CurColor(au8Color[i][0], au8Color[i][1], au8Color[i][2]);
        //msAPI_TestPattern_Draw_Rect_2(u16XStart, 0, u16XSize, s_TestPattern_u16PanelHigh);
        msAPI_TestPattern_DrawLine_H(u16XStart, 0, u16XSize);
    }

    // Copy line 0 to line 1~n
    for( i = 1; i < s_TestPattern_u16MemVLen; ++ i )
    {
        //printf("%u) ", i);
        _msAPI_TestPattern_CopyLine(0, i, 1, FALSE);
    }
    _msAPI_TestPattern_FlushAllMemory();


#else
    for( i = 0; i < COLOR_BAR_COLOR_NUM; ++ i )
    {
        u16XStart = u16XSize * i;
        msAPI_TestPattern_Set_CurColor(au8Color[i][0], au8Color[i][1], au8Color[i][2]);
        msAPI_TestPattern_Draw_Rect_2(u16XStart, 0, u16XSize, s_TestPattern_u16PanelHigh);
    }
#endif

    return TRUE;
}


BOOL MApp_TestPattern_Draw_Test1(void)
{
    //U16 i;
    //stuPixelInfo stuPixel;

    printf("msAPI_TestPattern_DrawLine()\n");

    //stuPixel.u8PicWidth = s_TestPattern_u16MemOffset;
   // printf(" s_TestPattern_u16MemOffset=%u\n", s_TestPattern_u16MemOffset);

    //s_TestPattern_bDebugUart = 1;

    msAPI_TestPattern_Set_CurColor(0xFF, 0xFF, 0xFF);

#if 1
    msAPI_TestPattern_DrawLine_H(0,0,100);
    msAPI_TestPattern_DrawLine_H(0,10,100);
    msAPI_TestPattern_DrawLine_H(0,20,100);
    msAPI_TestPattern_DrawLine_H(0,30,100);
#endif

#if 1
    msAPI_TestPattern_DrawLine_V(0, 0, 100);
    msAPI_TestPattern_DrawLine_V(10, 0, 100);
    msAPI_TestPattern_DrawLine_V(20, 0, 100);
    msAPI_TestPattern_DrawLine_V(30, 0, 100);
#endif

    _msAPI_TestPattern_FlushAllMemory();

    s_TestPattern_bDebugUart = 0;

    return TRUE;
}

static E_UI_INPUT_SOURCE enBackInputSource;

BOOL MApp_TestPattern_DrawPattern(U8 u8TPNo)
{
    BOOL bResult = TRUE;

    printf("MApp_TestPattern_DrawPattern(u8TPNo=%u)\n", u8TPNo);

    if( u8TPNo >= E_TEST_PATTERN_ID_MAX )
    {
        printf("\nError: Unsupported Pattern=%u!\n", u8TPNo);
        return FALSE;
    }

    if( msAPI_TestPattern_Get_Status() == FALSE )
    {
        enBackInputSource = UI_INPUT_SOURCE_TYPE;//MApp_InputSource_GetRecordSource();//SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW);

        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_RGB;
        MApp_InputSource_ChangeInputSource(MAIN_WINDOW);

        msAPI_TestPattern_Init();

    }

#if 0
    printf("SEG0=%X\n", MsOS_PA2KSEG0(0x10000));
    printf("SEG1=%X\n", MsOS_PA2KSEG1(0x10000));
    printf("PA0=%X\n", MsOS_VA2PA( MsOS_PA2KSEG0(0x10000)) );
    printf("PA1=%X\n", MsOS_VA2PA( MsOS_PA2KSEG1(0x10000)) );
#endif

    // Disable input source
    //MApi_XC_DisableInputSource(TRUE, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );

    U32 u32DrawTime1 = MsOS_GetSystemTime();

#if( ENABLE_BMP_TEST_PATTERN )
    if( u8TPNo <= E_TEST_PATTERN_ID_BMP_END )
    {
        bResult = msAPI_TestPattern_DrawBitmap(u8TPNo);
    }
    else
#endif
    {
        msAPI_TestPattern_ClearMemory();

        switch(u8TPNo)
        {
            case E_TEST_PATTERN_ID_FULL_SCREEN_BLACK:
                //bResult = msAPI_TestPattern_ClearMemory();
                break;
            case E_TEST_PATTERN_ID_FULL_SCREEN_WHITE:
                bResult = msAPI_TestPattern_Draw_FullScreen_White();
                break;

            case E_TEST_PATTERN_ID_GRAY_LEVEL_H_0_255:
                bResult = msAPI_TestPattern_Draw_GrayLevel(0,0,1,7);
                break;

            case E_TEST_PATTERN_ID_GRAY_LEVEL_H_255_0:
                bResult = msAPI_TestPattern_Draw_GrayLevel(0,255,-1,7);
                break;

            case E_TEST_PATTERN_ID_GRAY_LEVEL_V_0_255:
                bResult = msAPI_TestPattern_Draw_GrayLevel(1, 0, 1, 4);
                break;

            case E_TEST_PATTERN_ID_GRAY_LEVEL_V_255_0:
                bResult = msAPI_TestPattern_Draw_GrayLevel(1,255,-1,4);
                break;

            case E_TEST_PATTERN_ID_R_LEVEL_V_0_255:
                bResult = msAPI_TestPattern_Draw_Level( 1,
                    0, 0, 0,
                    1, 0, 0,
                    4);
                break;

            case E_TEST_PATTERN_ID_G_LEVEL_V_0_255:
                bResult = msAPI_TestPattern_Draw_Level( 1,
                    0, 0, 0,
                    0, 1, 0,
                    4);
                break;

            case E_TEST_PATTERN_ID_B_LEVEL_V_0_255:
                bResult = msAPI_TestPattern_Draw_Level( 1,
                    0, 0, 0,
                    0, 0, 1,
                    4);
                break;

            case E_TEST_PATTERN_ID_RECT_1:
                msAPI_TestPattern_Set_CurColor(0xFF, 0xFF, 0xFF);
                bResult = msAPI_TestPattern_Draw_Rect_1(0,0,1920,1080);
                break;

            case E_TEST_PATTERN_ID_RECT_2:
                msAPI_TestPattern_Set_CurColor(0xFF, 0xFF, 0xFF);
                bResult = msAPI_TestPattern_Draw_Rect_2(480, 270, 960, 540, TRUE);
                break;

            case E_TEST_PATTERN_ID_CHECKBOX:
                bResult = msAPI_TestPattern_Draw_Checkbox();
                break;

            case E_TEST_PATTERN_ID_RGB_1:
                bResult = msAPI_TestPattern_Draw_RGB();
                break;

            case E_TEST_PATTERN_ID_RGBW:
                bResult = msAPI_TestPattern_Draw_RGBW();
                break;

            case E_TEST_PATTERN_ID_COLOR_BAR:
                bResult = msAPI_TestPattern_Draw_COLOR_BAR();
                break;

            case E_TEST_PATTERN_ID_V_STRIPE:
                msAPI_TestPattern_Set_CurColor(0xFF, 0xFF, 0xFF);
                bResult = msAPI_TestPattern_Draw_Stripe(1);
                break;

            case E_TEST_PATTERN_ID_H_STRIPE:
                msAPI_TestPattern_Set_CurColor(0xFF, 0xFF, 0xFF);
                bResult = msAPI_TestPattern_Draw_Stripe(0);
                break;

            case E_TEST_PATTERN_ID_TEST_1:
                //msAPI_TestPattern_ClearMemory();
                bResult = MApp_TestPattern_Draw_Test1();
                break;

            default:
                bResult = FALSE;
                printf("\nError: Unsupported pattern=0x%X\n", u8TPNo);
                break;
        }
    }

    if( bResult == FALSE )
    {
        printf("\nError: Draw pattern fail !!\n");
        return FALSE;
    }

    printf("Draw time use %u\n", msAPI_Timer_DiffTime_2(u32DrawTime1, MsOS_GetSystemTime()) );

    // Enable input source
    MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);

    // Unmute
    MApi_XC_GenerateBlackVideo( DISABLE, MAIN_WINDOW );

    return bResult;
}

void MApp_TestPattern_Exit(void)
{
    if( msAPI_TestPattern_Get_Status() == TRUE  )
    {
        msAPI_TestPattern_Exit();

        //MApp_InputSource_SwitchSource(enBackInputSource,MAIN_WINDOW);

        UI_INPUT_SOURCE_TYPE = enBackInputSource;

        MApp_InputSource_ChangeInputSource(MAIN_WINDOW);

    }
}

#endif


