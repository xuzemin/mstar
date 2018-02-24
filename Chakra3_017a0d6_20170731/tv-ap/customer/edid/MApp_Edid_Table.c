#include "Board.h"

#if (ENABLE_DDC_RAM)

#include "debug.h"
#include "Utl.h"

#if ENABLE_DYNAMIC_EDID
#include "msAPI_Dynamic_EDID.h"
#endif

#include "MApp_Edid_Table.h"

//==============================================================

#include "MApp_Edid_VGA.c"

#if( ENABLE_EDID_HDMI_1p4 )
    #include "MApp_Edid_1p4.c"
#else
    #include "MApp_Edid_1p3.c"
#endif

#if (ENABLE_HDMI_4K_2K||ENABLE_EDID_SWITCH) // 4k X 2k
#include "MApp_Edid_2p0.c"
#endif


//==============================================================

#define EDID_TBL_SIZE   256


#if( ENABLE_EDID_SUPPORT_DDP_SAD )
#define EDID_TBL_SAD_SIZE   3
static BOOL g_EdidTbl_bEnAudioDDP = 0;
static U8 s_EdidTbl_au8SAD[EDID_TBL_SAD_SIZE] = {
        AUDIO_MPEG2 | AUDIO_CH_2,
        AUDIO_192kHZ|AUDIO_96kHZ,
        AUDIO_24BIT|AUDIO_20BIT|AUDIO_16BIT
};
#endif

#define DEBUG_EDID_TBL(x)  // x

void MApp_Edid_CorrectCheckSum(U8* pu8EdidTbl)
{
    int i;
    U8 u8CheckSum = 0;

    for( i = 0; i < 255; ++ i )
    {
        u8CheckSum += pu8EdidTbl[i];
    }

    DEBUG_EDID_TBL( printf("CheckSum: 0x%X, 0x%X ",  u8CheckSum, pu8EdidTbl[255]); );

    pu8EdidTbl[255] = 256 - u8CheckSum;

    DEBUG_EDID_TBL( printf("=> 0x%X\n",  pu8EdidTbl[255]); );
}

void MApp_Edid_PrintTbl(U8* pu8EdidTbl)
{
    printf("\n\\\\========================================================\n");

    int i;

    for( i = 0; i < EDID_TBL_SIZE; ++ i )
    {
        if( (i%16) == 0 )
            printf("/* %02X */ ", i);

        printf("0x%02X,", pu8EdidTbl[i]);

        if( (i%16) == 15 )
            printf("\n");
    }

    printf("\\\\==========================================================\n");
}

#if ENABLE_EDID_SUPPORT_DDP_SAD
BOOL MApp_Edid_ModifyTbl_ForAddDDP_SAD(U8 u8PhyAddr, U8* pu8EdidTbl, U8* pu8PhyAddrPos)
{
    ST_EDID_Control stEDIDConfig;
    U8 au8DynEdidTmpBuf[256];


    stEDIDConfig.bSAD = DYN_EDID_SUPPORT;
    stEDIDConfig.stAudio.au8Type[0] = s_EdidTbl_au8SAD[0];//AUDIO_MPEG2|AUDIO_CH_2;
    stEDIDConfig.stAudio.au8Type[1] = s_EdidTbl_au8SAD[1];//AUDIO_192kHZ|AUDIO_96kHZ;
    stEDIDConfig.stAudio.au8Type[2] = s_EdidTbl_au8SAD[2];//AUDIO_24BIT|AUDIO_20BIT|AUDIO_16BIT;
    stEDIDConfig.b4K2K = DYN_EDID_DEFAULT;
    stEDIDConfig.b3D = DYN_EDID_DEFAULT;
    stEDIDConfig.u8PAPort = u8PhyAddr;

    // Modify  pu8EdidTbl => Gen au8DynEdidTmpBuf
    if( FALSE == msApi_Dynamic_EDID_main(pu8EdidTbl, au8DynEdidTmpBuf, &stEDIDConfig) )
    {
        printf("\nError: Dynamic_EDID failed!\n");
        return FALSE;
    }

    // Copy result to user buf
    *pu8PhyAddrPos = stEDIDConfig.u8PAOut;
    memcpy(pu8EdidTbl, au8DynEdidTmpBuf, EDID_TBL_SIZE);

    DEBUG_EDID_TBL( printf("==> u8PhyAddrPos=0x%X\n", *pu8PhyAddrPos); );

    return TRUE;
}
#endif

BOOL MApp_Edid_Get_Table(EnuEdidTblSel eEdidTblSel, U8 u8PhyAddr, U8* pu8EdidTbl, U8* pu8PhyAddrPos)
{
    DEBUG_EDID_TBL(PRINT_CURRENT_LINE(););

    DEBUG_EDID_TBL( printf("MApp_Edid_Get_Table(eEdidTblSel=%u, u8PhyAddr=0x%X)\n", eEdidTblSel, u8PhyAddr); );

    if( eEdidTblSel >= E_EDID_TBL_UNKNOWN )
    {
        return FALSE;
    }

    if( eEdidTblSel != E_EDID_TBL_VGA )
    {
        if( pu8PhyAddrPos == NULL )
            return FALSE;
    }

    BOOL bPrintTbl = FALSE;

    if( u8PhyAddr == 0x30 ) // Debug HDMI3
    {
        bPrintTbl = TRUE;
    }

    switch(eEdidTblSel)
    {
        case E_EDID_TBL_VGA:
            memcpy(pu8EdidTbl, EDID_VGA, 128 );
            break;

        case E_EDID_TBL_HDMI_1p3_1p4:
            // Copy internal edid to user buffer
            memcpy(pu8EdidTbl, EDID_DVI_0, EDID_TBL_SIZE );
            *pu8PhyAddrPos = EDID_PA_POS;
            // Replace physical address
            pu8EdidTbl[*pu8PhyAddrPos] = u8PhyAddr;
            // Correction checksum
            MApp_Edid_CorrectCheckSum(pu8EdidTbl);

            DEBUG_EDID_TBL( printf("=> u8PhyAddrPos=0x%X\n", *pu8PhyAddrPos); );

            if( bPrintTbl )
            {
                DEBUG_EDID_TBL( MApp_Edid_PrintTbl(pu8EdidTbl); );
            }

        #if( ENABLE_EDID_SUPPORT_DDP_SAD )
            if( g_EdidTbl_bEnAudioDDP )
            {
            #if ENABLE_DYNAMIC_EDID
                if( FALSE == MApp_Edid_ModifyTbl_ForAddDDP_SAD( u8PhyAddr, pu8EdidTbl, pu8PhyAddrPos) )
                {
                    printf("\nError: Add DD+ SAD failed!\n");
                    return FALSE;
                }

                if( bPrintTbl )
                {
                    DEBUG_EDID_TBL( MApp_Edid_PrintTbl(pu8EdidTbl); );
                }

            #else
                printf("\nError: Undefined DD+ Edid!\n");
                return FALSE;
            #endif
            }
        #endif
            break;

    #if(ENABLE_HDMI_4K_2K||ENABLE_EDID_SWITCH) // 4k X 2k
        case E_EDID_TBL_HDMI_2p0:
            // Copy internal edid to user buffer
            memcpy(pu8EdidTbl, EDID_2p0_DVI_0, 256 );
            *pu8PhyAddrPos = EDID_PA_POS_2P0;
            // Replace physical address
            pu8EdidTbl[*pu8PhyAddrPos] = u8PhyAddr;
            // Correction checksum
            MApp_Edid_CorrectCheckSum(pu8EdidTbl);

            DEBUG_EDID_TBL( printf("=> u8PhyAddrPos=0x%X\n", *pu8PhyAddrPos); );

        #if( ENABLE_EDID_SUPPORT_DDP_SAD )
            if( g_EdidTbl_bEnAudioDDP )
            {
            #if ENABLE_DYNAMIC_EDID
                if( FALSE == MApp_Edid_ModifyTbl_ForAddDDP_SAD( u8PhyAddr, pu8EdidTbl, pu8PhyAddrPos) )
                {
                    printf("\nError: Add DD+ SAD failed!\n");
                    return FALSE;
                }

                if( bPrintTbl )
                {
                    DEBUG_EDID_TBL( MApp_Edid_PrintTbl(pu8EdidTbl); );
                }

            #else
                printf("\nError: Undefined DD+ Edid!\n");
                return FALSE;
            #endif
            }
        #endif
            break;
    #endif


        default:
            printf("\nError: Unsupported EdidTbl=%u\n", eEdidTblSel );
            return FALSE;
            break;
    }

    return TRUE;
}

#if( ENABLE_EDID_SUPPORT_DDP_SAD )
void MApp_Edid_Set_EnableAudioDDP(BOOL bEnAudioDDP, U8* pu8SAD )
{
    printf("MApp_Edid_Set_EnableAudioDDP(%u)\n", bEnAudioDDP);
    g_EdidTbl_bEnAudioDDP = bEnAudioDDP;

    if( bEnAudioDDP )
    {
        if( pu8SAD )
        {
            memcpy(s_EdidTbl_au8SAD, pu8SAD, EDID_TBL_SAD_SIZE);
        }
        else
        {
            s_EdidTbl_au8SAD[0] = AUDIO_MPEG2|AUDIO_CH_2;
            s_EdidTbl_au8SAD[1] = AUDIO_192kHZ|AUDIO_96kHZ;
            s_EdidTbl_au8SAD[2] = AUDIO_24BIT|AUDIO_20BIT|AUDIO_16BIT;
        }
    }
}
#endif

#endif

