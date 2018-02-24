
#define _MAPI_LD_C_

#include "Board.h"

#if ( LD_ENABLE )
#include "debug.h"

#include "drvGlobal.h"

#include "hal_misc.h"
#include "mhal_ld.h"

#include "mdrv_ld.h"

#include "msAPI_LD.h"

#include "mdrv_ldalgo.h"

#include "msAPI_Timer.h"
//#include "mdrv_mfc_3d.h"
//#include "mapp_customer.h"
//#include "System.h"

#include "mdrv_mfc_spi.h"

#include "drvPWM.h"
#include "apiXC.h"

#include "leddevice.h"

#include "msAPI_LD_PWM.h"


//==============================================================================
#define LD_OUT_SPI_RUN_IN_ISR   1

//==============================================================================

static BOOL s_bMApiLD_InitFinished = FALSE;

static U8 s_u8ApiLDISR_Todo_Cnt = 0;

static BOOL g_LD_bEnable = 0;

static U8 g_LD_u8TimeMsAfterVSync = 0;

static U16 * g_LD_pu16AlgoSpiBlock = 0;
static U16 * g_LD_pu16ShareMemLedData = 0;

BOOLEAN g_LD_bAlgoHasNewLedData = 0;


//==============================================================================
// Extern function ...
//extern t_sDrvLdCusPtrMap sCusPtrMap;

#define MDrv_3D_Is_3d_Not_Lonly_MODE()      0

#define LED_DIMMING_WHEN_LD_OFF()           (0xFFFF)

//==============================================================================

BOOL MApi_LD_Init(void)
{
    LedDev_Set_CurDevice(LED_DEVICE_SEL);

    if( MDrv_LD_Init() == FALSE )
    {
        printf("\nError: MDrv_LD_Init() failed!\n");
        return FALSE;
    }

    // Get Algo LedData memory
    U32 u32LdAlgoSpiBlockAddr = MHal_LD_Get_ShareMem(E_LD_INFO_ALGO_SPI_BLOCK_ADR);
    if( u32LdAlgoSpiBlockAddr != 0 )
    {
        MApi_LD_Set_AlgoSpiBlockAddr( (U16*)MsOS_PA2KSEG1( u32LdAlgoSpiBlockAddr ) );
    }

    MApi_LD_Set_ShareMemLedDataAddr( (U16*)MsOS_PA2KSEG1( MHal_LD_Get_ShareMem(E_LD_INFO_ALOG_OUT_LED_BUF_ADDR) ) );


    MHal_LD_Set_SPI_VsyncSel(0);//  1:PWM ,0:Vsync


    LedDev_Init();
    //MApi_LD_Config_OutputSignal_To_LED( MApi_XC_GetOutputVFreqX100()/10 );

    g_LD_bEnable = TRUE;

    s_bMApiLD_InitFinished = TRUE;

    return TRUE;
}

void drv_HDCPMBX_FireInterrupt(U8 u8SrcType);

void MApi_LD_ISR_OVSync(void)
{
    if( s_bMApiLD_InitFinished == FALSE )
        return;

    if( s_u8ApiLDISR_Todo_Cnt < 255 )
        s_u8ApiLDISR_Todo_Cnt += 1;

    //MDrv_LD_ISR();

#if(LD_ALGO_RUN_IN_CROP)
    drv_HDCPMBX_FireInterrupt(1);
#endif

    // Reset counter
    g_LD_u8TimeMsAfterVSync = 0;
}

#define LD_DEBUG_LED_NUM    14

#define USE_SPI_BLOCK       0

#define DEBUG_LED_DATA(x)   //x

void MApi_LD_OutSpi_Job(void)
{
    if( 0 == g_LD_bAlgoHasNewLedData )
    {
        return;
    }

    g_LD_bAlgoHasNewLedData = 0;

#if(USE_SPI_BLOCK)
  #if 0
    U8 i;
    printf("%u g_LD_pu16AlgoLedDatat[]=", MsOS_GetSystemTime());
    if( g_LD_pu16AlgoSpiBlock )
    {
        for( i = 0; i < LD_DEBUG_LED_NUM; ++ i )
        {
            printf("%X,", g_LD_pu16AlgoSpiBlock[i]);
        }
    }
    printf("\n");
  #endif

  #if 0
    {
    MDrv_PIU_TIMER_CAP_Init();
    MDrv_PIU_TIMER_CAP_Reset();
    U32 u32T1 = MDrv_PIU_TIMER_CAP_Get_Us();
    LedDev_Set_OutputSPI( g_LD_pu16AlgoSpiBlock );
    U32 u32T2 = MDrv_PIU_TIMER_CAP_Get_Us();
    printf("Use %u\n", u32T2 - u32T1);
    }
  #else
    LedDev_Set_OutputSPI( g_LD_pu16AlgoSpiBlock );
  #endif

#else // Use share mem

    if( g_LD_pu16ShareMemLedData == 0 )
        return;

  #if 1
    BOOLEAN bDataValid = TRUE;

    //printf("g_LD_pu16ShareMemLedData=0x%X\n", (U32)g_LD_pu16ShareMemLedData);

    {
        U16 u16LedDataLen = g_LD_pu16ShareMemLedData[0];
        U16 u16CheckSum = u16LedDataLen;
        U16 u16Tmp;

        U8 u8PQLedWidth = LedDev_Get_PQ_LedWidth();
        U8 u8PQLedHigh = LedDev_Get_PQ_LedHeight();

        if( u16LedDataLen != (u8PQLedWidth*u8PQLedHigh) )
        {
            DEBUG_LED_DATA( printf("Led Num is wrong!(%u)\n", u16LedDataLen); );
            return;
        }

        DEBUG_LED_DATA( printf("%u ; g_LD_pu16ShareMemLedData[%u]=\n", MsOS_GetSystemTime(), u16LedDataLen); );
        U8 x,y,i = 1;
        for( y = 0; y < u8PQLedHigh; ++ y )
        {
            for( x = 0; x < u8PQLedWidth; ++ x )
            {
                u16Tmp = g_LD_pu16ShareMemLedData[i];
                u16CheckSum += u16Tmp;
                DEBUG_LED_DATA( printf("%04X,", u16Tmp); );

                if( x == (u8PQLedWidth-1) )
                {
                    DEBUG_LED_DATA( printf("\n"); );
                }

                i += 1;
            }
        }

        // Check CS...
        //DEBUG_LED_DATA( printf("CS(%X,%X)\n", g_LD_pu16ShareMemLedData[i], u16CheckSum ); );
        if( g_LD_pu16ShareMemLedData[i] != u16CheckSum )
        {
            DEBUG_LED_DATA( printf("CS wrong(%X,%X)\n", g_LD_pu16ShareMemLedData[i], u16CheckSum ); );
        #if(0 == LD_OUT_SPI_RUN_IN_ISR)
            printf("CS wrong(%X,%X)\n", g_LD_pu16ShareMemLedData[i], u16CheckSum );
        #endif
            return;
        }
    }

  #endif

    if( bDataValid )
    {
        LedDev_Set_OutputSPI(&(g_LD_pu16ShareMemLedData[1]));
    }

#endif

}

void MApi_LD_ISR_1ms(void)
{
    if( s_bMApiLD_InitFinished == FALSE )
        return;


    if( g_LD_u8TimeMsAfterVSync < 255 )
    {
        g_LD_u8TimeMsAfterVSync += 1;
    }

#if(LD_ALGO_RUN_IN_CROP)
    if( g_LD_u8TimeMsAfterVSync == 10 )
    {
        g_LD_bAlgoHasNewLedData = 1; // Force has new data
    }
#endif

#if(LD_OUT_SPI_RUN_IN_ISR)
    if( g_LD_u8TimeMsAfterVSync == 14 )
    {
        MApi_LD_OutSpi_Job();
    }
#endif
}

void MApi_LD_Main(void)
{
    if( s_bMApiLD_InitFinished == FALSE )
    {
        printf("\nError: MApi_LD is not inited!\n");
        return;
    }

    if( s_u8ApiLDISR_Todo_Cnt )
    {
        //printf("g_LD_u8TimeMsAfterVSync=%u\n", g_LD_u8TimeMsAfterVSync);

    #if(0 == LD_ALGO_RUN_IN_CROP)
        if( MApi_LD_GetLDEnable() == TRUE )
        {
        #if 0
            {
            MDrv_PIU_TIMER_CAP_Init();
            MDrv_PIU_TIMER_CAP_Reset();
            U32 u32T1 = MDrv_PIU_TIMER_CAP_Get_Us();
            MDrv_LDAlgo_Main();
            U32 u32T2 = MDrv_PIU_TIMER_CAP_Get_Us();
            printf("Use %u\n", u32T2 - u32T1);
            }
        #else
            MDrv_LDAlgo_Main();
        #endif
        }
    #endif


    #if( 0 == LD_OUT_SPI_RUN_IN_ISR )
        MApi_LD_OutSpi_Job();
    #endif

        s_u8ApiLDISR_Todo_Cnt = 0;
    }

}

BOOL MApi_LD_GetLDEnable(void)
{
    return g_LD_bEnable;
}

void MApi_LD_SetLDEnable(BOOL enable)
{
    //if( enable == g_LD_bEnable )
    //    return;

    {// init register
        //MApi_LD_SetDemoMode(_DISABLE);
        //MApi_LD_Set_Globaldimming_Strength(_DISABLE, 0 );
        //MApi_LD_Set_Localdimming_Strength(_DISABLE, 0 );
    }

    if(enable == _DISABLE)
    {
      #if 0//((CustomerType==CustomerType_CMI_Ultrasonic)||(CustomerType == CustomerType_INX_Ubike))
        MApi_LD_Set_VideoCompensation_Strength(0);
      #else
        //MHal_LD_Set_CompensationEn(_DISABLE);
      #endif

        #if 0 // Do not turn off algorithm when LD off for avoiding on/off temporal garbage. Provided by color team Ricky.Chen
        MHal_LD_Set_SW_ReadLDFEn(_DISABLE);
        MHal_LD_Set_SW_AlgorithmEn(_DISABLE);
        MHal_LD_Set_SW_WriteLDBEn(_DISABLE);
        #endif
    }
    else
    {
      #if 0//((CustomerType==CustomerType_CMI_Ultrasonic)||(CustomerType == CustomerType_INX_Ubike))
        MHal_LD_Set_CompensationEn(_DISABLE);
        MHal_LD_Set_SW_PulseId(0);
        MHal_LD_Set_SW_PulseMode(0);
        MHal_LD_Set_SW_PulseLEDIntensity(0);
        MHal_LD_Set_SW_PulseLDBIntensity(0);
        MApi_LD_Set_VideoCompensation_Strength(0); //close conpensation for Inno
      #else
        //MHal_LD_Set_CompensationEn(_ENABLE);
      #endif

        #if 0   // Do not turn off algorithm when LD off for avoiding on/off temporal garbage. Provided by color team Ricky.Chen
        MHal_LD_Set_SW_ReadLDFEn(_ENABLE);
        MHal_LD_Set_SW_AlgorithmEn(_ENABLE);
        MHal_LD_Set_SW_WriteLDBEn(_ENABLE);
        #endif
    }

    g_LD_bEnable = enable;
}

void MApi_LD_Set_Localdimming_Strength(BOOL enable, U8 level)
{
    if( s_bMApiLD_InitFinished == FALSE )
    {
        printf("\nError: LD not init !\n");
        return;
    }

    if(enable)
    {
        MDrv_LD_SetLocalDimmingStrength(level);
    }
    else
    {
        MDrv_LD_SetLocalDimmingStrength(0xFF);
    }
}

void MApi_LD_Set_Globaldimming_Strength(BOOL enable, U8 level)
{
    if(enable)
    {
        MDrv_LD_SetGlobalDimmingStrength(level);
    }
    else
    {
        MDrv_LD_SetGlobalDimmingStrength(0xFF);
    }
}

void MApi_LD_Set_VideoCompensation_Strength( U8 level)
{
    if( s_bMApiLD_InitFinished == FALSE )
    {
        printf("\nError: LD not init !!\n");
        return;
    }


    if(level > 0x10) // default value & max value  are 0x10 ,
    {
        level = 0x10 ;
    }
    MDrv_LD_SetCompensationGain(level);   //hardcode refine 20150310
}

//void MApi_LD_Config_OutputSignal_To_LED(U16 u16OutVFreqX10)
void MApi_LD_Set_OutputVFreq(U16 u16OutVFreqX100)
{
    if( s_bMApiLD_InitFinished == FALSE )
    {
        printf("\nError: LD not init !!\n");
        return;
    }

    if( u16OutVFreqX100 < (23*100) )
    {
        printf("\nError: Invalid freq=%d\n", u16OutVFreqX100 );
        return;
    }

    MApi_LD_PWM_Update();

    //MDrv_LD_Config_OutputSignal_To_LED(u16OutVFreqX100/10, MDrv_3D_Is_3d_Not_Lonly_MODE());
    LedDev_Config_OutputSignal_To_LED(u16OutVFreqX100/10, MDrv_3D_Is_3d_Not_Lonly_MODE());
}

void MApi_LD_Set_AlgoSpiBlockAddr(U16* pu16SpiBlock)
{
    PRINT_CURRENT_LINE();
    printf("MApi_LD_Set_AlgoSpiBlockAddr(0x%X)\n", (U32)pu16SpiBlock);
    g_LD_pu16AlgoSpiBlock = pu16SpiBlock;
}

void MApi_LD_Set_ShareMemLedDataAddr(U16* pu16LedDataAddr)
{
    PRINT_CURRENT_LINE();
    printf("MApi_LD_Set_ShareMemLedDataAddr(0x%X)\n", (U32)pu16LedDataAddr);

    g_LD_pu16ShareMemLedData = pu16LedDataAddr;

    printf("g_LD_pu16ShareMemLedData=0x%X\n", (U32)g_LD_pu16ShareMemLedData);
}

void MApi_LD_Set_HasNewLedData(void)
{
    g_LD_bAlgoHasNewLedData = TRUE;
}

//==============================================================================

#endif

