//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Dynamic_EDID.h
/// MStar Application Interface for Timer
/// @brief API for Timer functions
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#define MSAPI_DYNAMIC_EDID_C

/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include "Board.h"

#if ENABLE_DYNAMIC_EDID

// Common Definition
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "debug.h"
// Common
#include "drvGlobal.h"
#include "Utl.h"
#include "sysinfo.h"

#include "msAPI_Dynamic_EDID.h"
//#include "SW_Config.h"


#define DEBUG_DYN_EDID(x)   //x

/******************************************************************************/
/*                               Functions                                    */
/******************************************************************************/

void msApi_Dynamic_EDID_PrintBuf(char* pcBufName, U8* pu8Buf, U8 u8Size)
{
    int i;

    printf("%s[%u]= ", pcBufName, u8Size);
    for( i = 0; i < u8Size; ++ i )
    {
        printf("0x%02X,", pu8Buf[i]);
    }
    printf("\n");
}

U8 msApi_Dynamic_EDID(U8* au8In, U8* au8Out)
{
    ST_EDID_Control stEDIDConfig;
    stEDIDConfig.bSAD = DYN_EDID_DEFAULT;
    stEDIDConfig.stAudio.au8Type[0] = AUDIO_MPEG2|AUDIO_CH_2;
    stEDIDConfig.stAudio.au8Type[1] = AUDIO_192kHZ|AUDIO_96kHZ;
    stEDIDConfig.stAudio.au8Type[2] = AUDIO_24BIT|AUDIO_20BIT|AUDIO_16BIT;
    stEDIDConfig.b4K2K = DYN_EDID_DEFAULT;
    stEDIDConfig.b3D = DYN_EDID_DEFAULT;
    stEDIDConfig.u8PAPort = 0x10;
    if(msApi_Dynamic_EDID_main(au8In, au8Out, &stEDIDConfig))
        return stEDIDConfig.u8PAOut;
    else
        return FALSE;
}

MS_BOOL msApi_Dynamic_EDID_main(U8* au8In, U8* au8Out, ST_EDID_Control *pStatus)
{
    U8 au8Temp[ROWSIZE][COLSIZE];

    DEBUG_DYN_EDID( printf("msApi_Dynamic_EDID_main()\n"); );

    memset(au8Temp,0,sizeof(au8Temp));  // clear array

    if( FALSE == msApi_Dynamic_EDID_Init(au8In, au8Temp) )  // Init Type
    {
        return FALSE;
    }

    // Audio
    msApi_Dynamic_EDID_Audio(pStatus->bSAD, &(pStatus->stAudio), au8Temp);   // DDP SAD

    // Vendor
    msApi_Dynamic_EDID_Vendor_PA(pStatus->u8PAPort, au8Temp);       // Physical Address
    msApi_Dynamic_EDID_Vendor_4K2K(pStatus->b4K2K, au8Temp);        // 4K2K
    msApi_Dynamic_EDID_Vendor_3D(pStatus->b3D, au8Temp);            // 3D

    // Merger
    pStatus->u8PAOut = msApi_Dynamic_EDID_Merger(au8In, au8Out, au8Temp);
    if( 0 == pStatus->u8PAOut )
        return FALSE;


    // CheckSum
    au8Out[0xFF] = msApi_Dynamic_EDID_CheckSum(au8Out, EDID_Start, 0xFE);

    return TRUE;
}

MS_BOOL msApi_Dynamic_EDID_Init(U8* au8In, U8 au8Temp[][COLSIZE])
{
    U8 u8TempLen, u8TempType, u8EndDataLen;
    U8 u8DataOffset;


    DEBUG_DYN_EDID( printf("msApi_Dynamic_EDID_Init()\n"); );

    u8EndDataLen = EDID_Start + au8In[EDID_Start+2]; // End Address

    DEBUG_DYN_EDID( printf("u8EndDataLen=0x%X\n", u8EndDataLen); );

    u8DataOffset = EDID_Start + 4; // Start Address=0x80+4

    DEBUG_DYN_EDID( printf("u8DataOffset=0x%X\n", u8DataOffset); );

    while(u8DataOffset < u8EndDataLen)
    {
        u8TempLen = EDID_LEN(au8In[u8DataOffset]) + 1;
        u8TempType = EDID_TYPE(au8In[u8DataOffset]);
        switch(u8TempType)
        {
            case 1: // Audio
                DEBUG_DYN_EDID( printf("Audio[%u] at = 0x%X ~ 0x%X\n", u8TempLen, u8DataOffset, u8DataOffset + u8TempLen-1); );
                memcpy( au8Temp[EDID_Audio], &(au8In[u8DataOffset]), u8TempLen);
                DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Audio", au8Temp[EDID_Audio], u8TempLen); );
                break;

            case 2: // Video
                DEBUG_DYN_EDID( printf("Video[%u] at = 0x%X ~ 0x%X\n", u8TempLen, u8DataOffset, u8DataOffset + u8TempLen-1); );
                memcpy( au8Temp[EDID_Video], &(au8In[u8DataOffset]), u8TempLen);
                DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Video", au8Temp[EDID_Video], u8TempLen); );
                break;

            case 3: // Vendor
                DEBUG_DYN_EDID( printf("Vendor[%u] at = 0x%X ~ 0x%X\n", u8TempLen, u8DataOffset, u8DataOffset + u8TempLen-1); );
                memcpy( au8Temp[EDID_Vendor], &(au8In[u8DataOffset]), u8TempLen);
                DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Vendor", au8Temp[EDID_Vendor], u8TempLen); );
                break;

            case 4: // Speaker
                DEBUG_DYN_EDID( printf("Speaker[%u] at = 0x%X ~ 0x%X\n", u8TempLen, u8DataOffset, u8DataOffset + u8TempLen-1); );
                memcpy( au8Temp[EDID_Speaker], &(au8In[u8DataOffset]), u8TempLen);
                DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Speaker", au8Temp[EDID_Speaker], u8TempLen); );
                break;

            default:
                printf("\nError: Unknown EDID Type=%u\n", u8TempType);
                return FALSE;
                break;
        }

        u8DataOffset += u8TempLen;
    }

    return TRUE;
}

void msApi_Dynamic_EDID_Vendor_PA(U8 u8Add, U8 au8Temp[][COLSIZE])
{
    au8Temp[EDID_Vendor][4] = u8Add;   // High
    au8Temp[EDID_Vendor][5] = 0x00;    // Low
}

void msApi_Dynamic_EDID_Vendor_4K2K(U8 b4K2K, U8 au8Temp[][COLSIZE])
{
    U8 u8Index;

    if(b4K2K == DYN_EDID_DEFAULT)
        return;

    U8 u8Vendor_Len = EDID_LEN(au8Temp[EDID_Vendor][0]);    // Vendor Header

    if(au8Temp[EDID_Vendor][8] & BMASK(7:6))
    {
        u8Index = 13;
    }
    else if((au8Temp[EDID_Vendor][8] & BIT6) || (au8Temp[EDID_Vendor][8] & BIT7))
    {
        u8Index = 11;
    }
    else
    {
        u8Index = 9;
    }

    if(b4K2K == DYN_EDID_SUPPORT)    // Support 4K2K
    {
        au8Temp[EDID_Vendor][8] |= BIT5;    //Enable HDMI Video Present

                                                    // Vendor_index - 07 :3D Present
        if(au8Temp[EDID_Vendor][u8Index] & BIT7)    // move 3D structure all & 3D Mask
        {
            if(au8Temp[EDID_Vendor][u8Index+1] & BMASK(7:5))       // 07-05 HDMI 4K2K LEN
            {
                u8Vendor_Len = u8Index+7;
                if(au8Temp[EDID_Vendor][u8Index] & BIT6)     // 06-05 :01(support 3D_Structure_ALL_15..0, no support 3D_MASK_15..0)
                {                               // 06-05 :10(support 3D_Structure_ALL_15..0, support 3D_MASK_15..0)
                    u8Vendor_Len = u8Index+9;
                }
            }
            else
            {
                au8Temp[EDID_Vendor][u8Index+6] = au8Temp[EDID_Vendor][u8Index+2];
                au8Temp[EDID_Vendor][u8Index+7] = au8Temp[EDID_Vendor][u8Index+3];
                u8Vendor_Len = u8Index+7;
                if(au8Temp[EDID_Vendor][u8Index] & BIT6)    // 06-05 :01(support 3D_Structure_ALL_15..0, no support 3D_MASK_15..0)
                {                                           // 06-05 :10(support 3D_Structure_ALL_15..0, support 3D_MASK_15..0)
                    au8Temp[EDID_Vendor][u8Index+8] = au8Temp[EDID_Vendor][u8Index+4];
                    au8Temp[EDID_Vendor][u8Index+9] = au8Temp[EDID_Vendor][u8Index+5];
                    u8Vendor_Len = u8Index+9;
                }
            }
        }
        else
        {
            u8Vendor_Len = u8Index+5;
        }

        au8Temp[EDID_Vendor][u8Index+1] |= BIT7;           // bit 7~5, VIC Len=4
        au8Temp[EDID_Vendor][u8Index+2] = Vendor_4K2K_1;   // 0x01:4K*2K 29.97 30HZ
        au8Temp[EDID_Vendor][u8Index+3] = Vendor_4K2K_2;   // 0x02:4K*2K 25HZ
        au8Temp[EDID_Vendor][u8Index+4] = Vendor_4K2K_3;   // 0x03:4K*2k 24HZ
        au8Temp[EDID_Vendor][u8Index+5] = Vendor_4K2K_4;   // 0X04:4K*2K 24HZ(SMPTE)
    }
    else                    // Not Support 4K2K
    {
                                                    // Vendor_index - 07 :3D Present
        if(au8Temp[EDID_Vendor][u8Index] & BIT7)    // Check 3D Present
        {
            if(au8Temp[EDID_Vendor][u8Index+1] & BMASK(7:5))       // Check 4K2K LEN // 07-05 HDMI 4K2K LEN
            {
                au8Temp[EDID_Vendor][u8Index+2] = au8Temp[EDID_Vendor][u8Index+6];
                au8Temp[EDID_Vendor][u8Index+3] = au8Temp[EDID_Vendor][u8Index+7];
                u8Vendor_Len = u8Index+3;
                if(au8Temp[EDID_Vendor][u8Index] & BIT6)     // 06-05 :01(support 3D_Structure_ALL_15..0, no support 3D_MASK_15..0)
                {                               // 06-05 :10(support 3D_Structure_ALL_15..0, support 3D_MASK_15..0)
                    au8Temp[EDID_Vendor][u8Index+4] = au8Temp[EDID_Vendor][u8Index+8];
                    au8Temp[EDID_Vendor][u8Index+5] = au8Temp[EDID_Vendor][u8Index+9];
                    u8Vendor_Len = u8Index+5;
                }
            }
            else
            {
                u8Vendor_Len = u8Index+3;
                if(au8Temp[EDID_Vendor][u8Index] & BIT6)     // 06-05 :01(support 3D_Structure_ALL_15..0, no support 3D_MASK_15..0)
                {                               // 06-05 :10(support 3D_Structure_ALL_15..0, support 3D_MASK_15..0)
                    u8Vendor_Len = u8Index+5;
                }
            }
        }
        else
        {
            au8Temp[EDID_Vendor][8] &= (~BIT5);    //Disable HDMI Video Present
            u8Vendor_Len = 7;
        }
    }
    //u8Vendor_Len=u8Vendor_Len-EDID_Vendor;
    au8Temp[EDID_Vendor][0] = (au8Temp[EDID_Vendor][0] & BMASK(7:5)) + u8Vendor_Len;
}

void msApi_Dynamic_EDID_Vendor_3D(U8 b3D, U8 au8Temp[][COLSIZE])
{
    U8 u8Index,u8LenTemp = 0;

    if(b3D == DYN_EDID_DEFAULT)
        return;

    U8 u8Vendor_Len = EDID_LEN(au8Temp[EDID_Vendor][0]);    // Vendor Header

    if(au8Temp[EDID_Vendor][8] & BMASK(7:6))
    {
        u8Index = 13;
    }
    else if((au8Temp[EDID_Vendor][8] & BIT6) || (au8Temp[EDID_Vendor][8] & BIT7))
    {
        u8Index = 11;
    }
    else
    {
        u8Index = 9;
    }

    if(b3D == DYN_EDID_SUPPORT)    // Support 3D
    {
        if(au8Temp[EDID_Vendor][u8Index+1] & BMASK(7:5))   // Check 4K2K LEN // bit 7-5, Init HDMI 4K2K LEN
        {
            u8LenTemp = u8Index+6;
        }
        else
        {
            u8LenTemp = u8Index+2;
        }

        au8Temp[EDID_Vendor][8] |= BIT5;     //Enable HDMI Video Present

        au8Temp[EDID_Vendor][u8Index] = 0xA0;              // bit7:    Enable 3D Present
                                            // bit6-5:  3D Multi Present
                                                // 01: support 3D_Structure_ALL_15..0, no support 3D_MASK_15..0
                                                // 10: support 3D_Structure_ALL_15..0, support 3D_MASK_15..0

        au8Temp[EDID_Vendor][u8Index+1] |= 0x02;           // bit 4-0, Init HDMI 3D LEN

        au8Temp[EDID_Vendor][u8LenTemp] = 0x01;    // 3D Structure ALL 15-08 bit8:support "Side-by-Side(Half) with horizontal sub-sampling" 3D formats
        au8Temp[EDID_Vendor][u8LenTemp+1] = 0x41;  // 3D Structure ALL 07-00 bit6:support "Top-and-Bottom" 3D formats
                                            // 3D Structure ALL 07-00 bit0:support "Frame packing" 3D formats.
        u8Vendor_Len = u8LenTemp+1;
    }
    else        // Not Support 3D
    {
        if(au8Temp[EDID_Vendor][u8Index+1] & BMASK(7:5))   // Check 4K2K // bit 7-5, Init HDMI 4K2K LEN
        {
            au8Temp[EDID_Vendor][u8Index+1] &= ~(BMASK(4:0));           // Clean bit 4-0, Init HDMI 3D LEN
            u8Vendor_Len = u8Index+5;
        }
        else
        {
            au8Temp[EDID_Vendor][8] &= (~BIT5);    //Disable HDMI Video Present
            u8Vendor_Len = 7;
        }
    }
    //u8Vendor_Len=u8Vendor_Len-EDID_Vendor;
    au8Temp[EDID_Vendor][0] = (au8Temp[EDID_Vendor][0] & BMASK(7:5))+u8Vendor_Len;
}

void msApi_Dynamic_EDID_Audio(U8 bSAD, ST_EDID_Audio *pStatus, U8 au8Temp[][COLSIZE])
{
    U8 i,u8Count=0;
    BOOL bSADFound = FALSE;


    if( bSAD == DYN_EDID_DEFAULT )
        return;

    DEBUG_DYN_EDID( printf("msApi_Dynamic_EDID_Audio()\n"); );

    U8 u8Audio_Len = EDID_LEN(au8Temp[EDID_Audio][0]);    // Audio Header

    DEBUG_DYN_EDID( printf(" -> au8Type[0]=0x%X, 0x%X, 0x%X\n", pStatus->au8Type[0], pStatus->au8Type[1], pStatus->au8Type[2]); );

#define EDID_AUDIO_FORMAT_SHIFT 3
#define EDID_AUDIO_FORMAT_MASK  (0x78)//BMASK(6:3)

    DEBUG_DYN_EDID( printf(" Find format: 0x%X(0x%X)\n",
        (pStatus->au8Type[0]&EDID_AUDIO_FORMAT_MASK),
        (pStatus->au8Type[0]&EDID_AUDIO_FORMAT_MASK)>>EDID_AUDIO_FORMAT_SHIFT ); );

    for(i=1; i <= u8Audio_Len; i+=3)  // check type
    {
        DEBUG_DYN_EDID( printf("  %u 0x%X(0x%X)\n", i,
            (au8Temp[EDID_Audio][i]&EDID_AUDIO_FORMAT_MASK),
            (au8Temp[EDID_Audio][i]&EDID_AUDIO_FORMAT_MASK)>>EDID_AUDIO_FORMAT_SHIFT ); );

        if((au8Temp[EDID_Audio][i] & EDID_AUDIO_FORMAT_MASK) == ((pStatus->au8Type[0]) & EDID_AUDIO_FORMAT_MASK))
        {
            bSADFound = TRUE;
            DEBUG_DYN_EDID( printf("  ==> SAD found\n"); );
            break;
        }

        u8Count ++;
    }

    if( bSAD == DYN_EDID_SUPPORT )
    {
        if( FALSE == bSADFound )  // If not found, need to Add
        {
            au8Temp[EDID_Audio][u8Audio_Len+1] = pStatus->au8Type[0];
            au8Temp[EDID_Audio][u8Audio_Len+2] = pStatus->au8Type[1];
            au8Temp[EDID_Audio][u8Audio_Len+3] = pStatus->au8Type[2];
            u8Audio_Len+=3;
        }
        else // If not found, need to Modify
        {
            au8Temp[EDID_Audio][(u8Count*AudioTypeLen)+1] = pStatus->au8Type[0];
            au8Temp[EDID_Audio][(u8Count*AudioTypeLen)+2] = pStatus->au8Type[1];
            au8Temp[EDID_Audio][(u8Count*AudioTypeLen)+3] = pStatus->au8Type[2];
        }
    }
    else // DYN_EDID_NOT_SUPPORT
    {
        if( bSADFound ) // If found, need to Modify
        {
            if(u8Audio_Len == ((u8Count*AudioTypeLen)+3))
            {
                au8Temp[EDID_Audio][(u8Count*AudioTypeLen)+1] = 0x00;
                au8Temp[EDID_Audio][(u8Count*AudioTypeLen)+2] = 0x00;
                au8Temp[EDID_Audio][(u8Count*AudioTypeLen)+3] = 0x00;
                u8Audio_Len-=3;
            }
            else    // shift array
            {
                U8 u8Audio_Type_Len = (u8Audio_Len/AudioTypeLen);   // Total size
                for(i=u8Count;i<u8Audio_Type_Len;i++)
                {
                    au8Temp[EDID_Audio][(i*AudioTypeLen)+ 1] = au8Temp[EDID_Audio][((i+1)*AudioTypeLen)+1];
                    au8Temp[EDID_Audio][(i*AudioTypeLen)+ 2] = au8Temp[EDID_Audio][((i+1)*AudioTypeLen)+2];
                    au8Temp[EDID_Audio][(i*AudioTypeLen)+ 3] = au8Temp[EDID_Audio][((i+1)*AudioTypeLen)+3];
                }
                u8Audio_Len-=3;
            }
        }
    }

    //u8Audio_Len = u8Audio_Len - EDID_Audio;
    au8Temp[EDID_Audio][0] = (au8Temp[EDID_Audio][0] & BMASK(7:5) ) + u8Audio_Len;
}

U8 msApi_Dynamic_EDID_Merger(U8* au8In, U8* au8Out, U8 au8Temp[][COLSIZE])
{
    U8 u8VideoLen = EDID_LEN(au8Temp[EDID_Video][0]) + 1;
    U8 u8AudioLen = EDID_LEN(au8Temp[EDID_Audio][0]) + 1;
    U8 u8SpeakerLen = EDID_LEN(au8Temp[EDID_Speaker][0]) + 1;
    U8 u8VendorLen = EDID_LEN(au8Temp[EDID_Vendor][0]) + 1;
    U8 u8HDMIDataLen = u8AudioLen + u8VideoLen + u8VendorLen + u8SpeakerLen + 4;
    U8 u8PhyAddr_Pos = 0;
    U8 i,u8LoopCount;
    U8 u8OutputDataOffset;


    DEBUG_DYN_EDID( printf("msApi_Dynamic_EDID_Merger()\n"); );
    //DEBUG_DYN_EDID( printf("u8VideoLen=%u\n", u8VideoLen); );
    //DEBUG_DYN_EDID( printf("u8AudioLen=%u\n", u8AudioLen); );
    //DEBUG_DYN_EDID( printf("u8SpeakerLen=%u\n", u8SpeakerLen); );
    //DEBUG_DYN_EDID( printf("u8VendorLen=%u\n", u8VendorLen); );
    DEBUG_DYN_EDID( printf("u8HDMIDataLen=%u\n", u8HDMIDataLen); );


#if 0 // Wait Ian check this ...
    // check overlap
    U8 u8TempLen = 0;
    u8LoopCount = au8In[0xFD];
    while(!u8LoopCount) // count 0x00
    {
        u8TempLen++;
        u8LoopCount = au8In[0xFD-u8TempLen];
    }
#endif

#if 0 // Wait Ian check this ...
    //if(au8Out[EDID_Start+2]>au8In[EDID_Start+2])
    if(au8In[EDID_Start+2])
    {
        //if((au8Out[EDID_Start+2]-au8In[EDID_Start+2])>u8HDMIDataLen)
        {
            printf("EDID Fail - Merger Overlap\n");
            return FALSE;
        }
    }
#endif

    memcpy(au8Out, au8In, 0x80);// Merger 0~127bytes

    // Merger 128~255bytes
//00: Extension tag (which kind of extension block this is); 02h for CEA EDID
//01: Revision number (Version number); 03h for Version 3
    au8Out[EDID_Start+0] = au8In[EDID_Start+0];//0x02;   // EDID header
    au8Out[EDID_Start+1] = au8In[EDID_Start+1];//0x03;   // EDID header
    au8Out[EDID_Start+2] = u8HDMIDataLen;
    au8Out[EDID_Start+3] = au8In[EDID_Start+3];

    // Merger Video array
    u8OutputDataOffset = 0x84;
    DEBUG_DYN_EDID( printf("Video[%u] at = 0x%X ~ 0x%X\n", u8VideoLen,u8OutputDataOffset, u8OutputDataOffset + u8VideoLen-1); );
    memcpy(&au8Out[u8OutputDataOffset], &au8Temp[EDID_Video][0], u8VideoLen);
    DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Video", &au8Out[u8OutputDataOffset], u8VideoLen); );


    // Merger Audio array
    u8OutputDataOffset += (u8VideoLen);
    DEBUG_DYN_EDID( printf("Audio[%u] at = 0x%X ~ 0x%X\n", u8AudioLen,u8OutputDataOffset, u8OutputDataOffset + u8AudioLen-1); );
    memcpy(&au8Out[u8OutputDataOffset], &au8Temp[EDID_Audio][0], u8AudioLen);
    DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Audio", &au8Out[u8OutputDataOffset], u8AudioLen); );


    // Merger Speaker array
    u8OutputDataOffset += (u8AudioLen);
    DEBUG_DYN_EDID( printf("Speaker[%u] at = 0x%X ~ 0x%X\n", u8SpeakerLen,u8OutputDataOffset, u8OutputDataOffset + u8SpeakerLen-1); );
    memcpy(&au8Out[u8OutputDataOffset], &au8Temp[EDID_Speaker][0], u8SpeakerLen);
    DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Speak", &au8Out[u8OutputDataOffset], u8SpeakerLen); );


    // Merger Vendor array
    u8OutputDataOffset += (u8SpeakerLen);
    DEBUG_DYN_EDID( printf("Vendor[%u] at = 0x%X ~ 0x%X\n", u8VendorLen,u8OutputDataOffset, u8OutputDataOffset + u8VendorLen-1); );
    memcpy(&au8Out[u8OutputDataOffset], &au8Temp[EDID_Vendor][0], u8VendorLen);
    DEBUG_DYN_EDID( msApi_Dynamic_EDID_PrintBuf("Vendor", &au8Out[u8OutputDataOffset], u8VendorLen); );
    /*
    for(i=0; i < u8VendorLen; i++)
    {
        au8Out[u8OutputDataOffset+i] = au8Temp[EDID_Vendor][i];
        if(i == 4)                                // return Physical Address
            u8PhyAddr_Pos = u8OutputDataOffset+i;
    }*/
    u8PhyAddr_Pos = u8OutputDataOffset + 4;

    DEBUG_DYN_EDID( printf("PhyAddr pos = 0x%X\n", u8PhyAddr_Pos); );

    // shift arr_in to arr_out
    u8LoopCount = 0xFF - (EDID_Start+au8Out[EDID_Start+2]);
    DEBUG_DYN_EDID( printf("u8LoopCount = 0x%X\n", u8LoopCount); );
    for(i=0; i < u8LoopCount; i++)
    {
        au8Out[EDID_Start+au8Out[EDID_Start+2]+i] = au8In[EDID_Start+au8In[EDID_Start+2]+i];
    }

    return u8PhyAddr_Pos;
}

U8 msApi_Dynamic_EDID_CheckSum(U8* au8In,U8 u8Start, U8 u8End)
{
    U8 i,u8checksum=0;

    for(i=u8Start;i<u8End;i++)
    {
        u8checksum+=au8In[i];
    }
    u8checksum = ~(u8checksum-1);
    return u8checksum;
}

#undef MSAPI_DYNAMIC_EDID_C
#endif
