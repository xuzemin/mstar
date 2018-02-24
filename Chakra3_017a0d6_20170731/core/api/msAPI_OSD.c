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
//  [Doxygen]
/// @file msAPI_OSD.h
/// This file includes MStar application interface for OSD
/// @brief API for OSD functions
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_OSD_C

/********************************************************************************/
/*                    Header Files                                              */
/********************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "datatype.h"
#include "MsTypes.h"
#include "debug.h"

 // FIXME: nameing of GE if
#include "apiGOP.h"
#include "msAPI_OSD.h"
#include "msAPI_Memory.h"
#include "msAPI_Font.h"
#include "msAPI_Timer.h"
#include "debug.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "msAPI_OSD_Resource.h"
#include "sysinfo.h"
#include "msAPI_OCP.h"
#include "MApp_DMP_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_GlobalFunction.h"

#if (ENABLE_THAI_OSD)
    #include "msAPI_Thai_Shaping.h"
#endif
#if (ENABLE_ARABIC_OSD)
    #include "msAPI_Arabic_ushape.h"
#endif

#if ( ENABLE_TTF_FONT )
    #include "msAPI_MLE_font_base.h"
    #include "msAPI_MLE_font_vector.h"
    #include "msAPI_MLE_font_pl.h"
    #include "msAPI_MLE_graphic_types.h"
    #include "msAPI_MLE_graphic_forward.h"
    #include "msAPI_MLE_text_util.h"
    #include "msAPI_MLE_text_priv.h"
    #include "msAPI_MLE_display_priv.h"
#endif

#define APIOSD_DBG(x) //x


#define ENABLE_DEFAULT_KERNING      0
#define ENABLE_SHORT_STRING_BUFFER  1

#if(ENABLE_EWS)
    #define MAX_STRING_BYTES    4096
#else
    #define MAX_STRING_BYTES    1000 // 350  //  255
#endif

static const U16 COMMON_ELLIPSIS_STRING[] = {0x002E, 0x002E, 0x002E, 0x0000};

/********************************************************************************/
/*                     Local                                                    */
/********************************************************************************/
//static GEClrPoint cpoint;
//static GEPoint point;
//static GEClrLine clrline;
//static GERGBColor b_clr,f_clr;
//static GELineFmt lineFmt;
//static GEBitmapFmt bmpfmt;
//static GERectFmt rfmt;
//static GERoundFmt roundfmt;
//static GELineFmt lfmt;
//static GEPESettings    GEPE;
//static GELineRectInfo  GELineRect;
//static GEPESettings  PESet;
//U16 au16InfoScrollLineInx[100];
U16 u16NextLineStartInx = 0;
bit bStopScrollDown= true;

U16 u16AlreadyShowHowManyBytes = 0;
U16 u16RecordOnePageByte[12] = {0};
#if (ENABLE_DTV_EPG)
extern U8 _u8InfoScrollLineCount;
#endif
extern U8 MApp_ZUI_ACT_EPGGetDescInfoPageNum(void);

#if ((ENABLE_TTF_FONT)||defined(PROJ_CERTIFICATION_GROUP1))
    static BOOLEAN bDivxSubtitleMode = TRUE;
#else
    static BOOLEAN bDivxSubtitleMode = FALSE;
#endif



#if ( ENABLE_ARABIC_OSD )
//static BOOLEAN bDivxSubtitleText = FALSE;
static BOOLEAN bHebrewMixedMode = FALSE;
#endif

#if (ENABLE_ARABIC_OSD)
BOOLEAN ArabicCHStringFlag = FALSE;
#endif

#if (ENABLE_TTF_FONT)
static EN_OSDAPI_LANGUAGE enLanguage;
#else
static EN_OSDAPI_LANGUAGE enLanguage = LANGUAGE_OSD_ENGLISH;
#endif

#if ( ENABLE_TTF_FONT )
    static LE_LanguageTag_e enLanguageTag = LE_LANGUAGE_TAG_ENG;
#endif

#if ENABLE_DEFAULT_KERNING
#include "kerning.h"
#else
//static const U8 code _dummy = 0;
#endif //ENABLE_DEFAULT_KERNING

#define STROSD  512//256

#define OSDTTF_TRACE(x) //x

typedef union
{
    U8  U8Str[STROSD*2];
    U16 U16Str[STROSD];
} OSDStringType;

typedef union
{
    U8  U8Str[STROSD*4];
    U16 U16Str[STROSD*2];
} OSDStringTypeDouble;

static OSDStringType TempStr;

#if ( ENABLE_TTF_FONT )
static Mle_TextTable_t *pMleTextTable = NULL;
#endif

static BOOLEAN bEndingTypeNone = FALSE;

#if ( ENABLE_TTF_FONT )
    #if (!MONO_FONT)
        static GFX_PaletteEntry TTFPalette[256];
    #endif
#endif

extern LOADFONT_STRUCT ttf_font_info[];

extern BYTE MApp_GetLanguageForFont(void);

/********************************************************************************/
/*                   Functions                                                  */
/********************************************************************************/
#if (ENABLE_ARABIC_OSD)
static void msAPI_OSD_KurdishFilter(U16 *inp, U16 len);
static void msAPI_OSD_UrduFilter(U16 *inp, U8 len);
static U8 msAPI_OSD_IsArabicVowel(U16 inputc);
#endif

#if ( ENABLE_TTF_FONT )
static BOOLEAN msAPI_OSD_MeasureTextY(U32 nFontSize, U32 u32Height, S32 *ps32Y, U32 *pu32Rows, U32 *pu32FontHeight, BOOLEAN bMultiLine);
static BOOLEAN msAPI_OSD_MeasureLineX( U32 u32FontSize, U16 *pu16Str, U16 u16Strlen, U32 u32Index, OSDClrBtn *pclrBtn, BOOLEAN *pbIsRTLLang, U16 **ppu16Str, U32 *pu32FitLen, U32 *pu32FitWidth, S32 *ps32X, U32 *u32Ell, BOOLEAN *pbIsRTLStr, EN_STRING_ENDING_TYPE enEndingType, BOOLEAN bIsLastDisplayLine);
#endif

//*************************************************************************
//Function name:        msAPI_OSD_u16Strlen
//Passing parameter:    U16 *pu16Str : string pointor
//Return parameter:     U16 : string length
//Description:          Transfer numer into string
//*************************************************************************


void msAPI_OSD_GET_resource()
{
    //printf("OSD GET RESOURCE \n");
   // MApi_GFX_SetShareMode(GFX_NOSHARE);
}

void msAPI_OSD_Free_resource()
{
    //printf("OSD FREE RESOURCE \n");
   // MApi_GFX_SetShareMode(GFX_SHARE);
}

/******************************************************************************/
/// API for Get string length::
/// Get string length
/// @param pu16Str \b IN string pointor
/// @return U16: String length
/******************************************************************************/
U16 msAPI_OSD_u16Strlen(U16 *pu16Str)
{
    U16 u16Count;

    u16Count = 0;

    if (pu16Str == NULL)
    {
        return u16Count;
    }

    while( (*pu16Str++ != 0) && (u16Count < MAX_STRING_BYTES) )
    {
        u16Count++;
    }
    return u16Count;
}

//*************************************************************************
//Function name:        msAPI_OSD_u16Strcpy
//Passing parameter:    U16 *pu16Dest: destnation
//                      U16 *pu16Src: source
//Return parameter:     none
//Description:          string copy
//*************************************************************************

/******************************************************************************/
/// API for string copy::
/// @param *pu16Dest \b OUT string destination
/// @param *pu16Src \b IN string source
/******************************************************************************/
void msAPI_OSD_u16Strcpy(U16 *pu16Dest, U16 *pu16Src)
{
    memcpy(pu16Dest, pu16Src, (msAPI_OSD_u16Strlen(pu16Src)+1) * 2);
}

/******************************************************************************/
/// API for string concatenation::
/// @param pu16Dest \b OUT string destination
/// @param pu16Src \b IN string source
/******************************************************************************/
void msAPI_OSD_u16Strcat(U16 *pu16Dest, U16 *pu16Src)
{
    memcpy(pu16Dest + msAPI_OSD_u16Strlen(pu16Dest), pu16Src, (msAPI_OSD_u16Strlen(pu16Src)+1) * 2);
}

/******************************************************************************/
/// API for string compare::
/// get compared result
/// @param *u16strA \b IN string destination
/// @param *u16strB \b IN string source
/******************************************************************************/
int msAPI_OSD_u16Strcmp(U16 *u16strA, U16 *u16strB)
{
    U16 strlen_a, strlen_b;

    strlen_a = msAPI_OSD_u16Strlen(u16strA)*2;
    strlen_b = msAPI_OSD_u16Strlen(u16strB)*2;
    return memcmp((U8 *) u16strA, (U8 *) u16strB, MAX(strlen_a, strlen_b));
}

/******************************************************************************/
/// API for get string length::
/// Get string length
/// @param *pu8Str \b IN pointer to string
/// @param *u8NoOfBytesPerChar \b IN btyes per char
/// @return U16: String length
/******************************************************************************/
U16 msAPI_OSD_GetStrLength(U8 *pu8Str, EN_CHAR_IDX_LENGTH u8NoOfBytesPerChar)
{
    U16 length = 0;
    U16 i;//, u16tmp[MAX_STRING_BYTES];
    U16 u16Tmp;

    if(u8NoOfBytesPerChar == CHAR_IDX_1BYTE)
    {
         length = strlen((char *)pu8Str);

        if (length > MAX_STRING_BYTES)
        {
            length = MAX_STRING_BYTES;
        }
    }
    else //(u8NoOfBytesPerChar == CHAR_IDX_2BYTE)
    {
        for (i=0; i<MAX_STRING_BYTES; i++)
        {
            u16Tmp = (pu8Str[i*2+1]<<8) + pu8Str[i*2];
            if (u16Tmp == 0)
                break;
            length += 1;
        }
        //length = msAPI_OSD_u16Strlen(u16tmp);
    }

    return length;
}

BOOLEAN msAPI_OSD_IsRTLLanguage( EN_OSDAPI_LANGUAGE enLang )
{
    switch( enLang )
    {
    case LANGUAGE_OSD_ARABIC:
    case LANGUAGE_OSD_HEBREW:
    case LANGUAGE_OSD_PARSI:
    case LANGUAGE_OSD_KURDISH:
    case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
    case LANGUAGE_OSD_UYGHUR:
#endif
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
}

/******************************************************************************/
/// API for get string width::
/// Get string width
/// @param font_handle \b IN font handle
/// @param *pu8Str \b IN pointer to string
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/// @return U16: String width
/******************************************************************************/
U16 msAPI_OSD_GetStrWidth(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn)
{
    U16 i;
    U16 length, width;
    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringType TempBuf;
    OSDStringTypeDouble outbuf;
#if ( ENABLE_ARABIC_OSD )
    U8 bMirrorLang = FALSE;
    U8 bArabicDisplay = FALSE;
    U8 bHebrew = FALSE;
#endif
#if ( ENABLE_THAI_OSD )
    U8 bThaiDisplay = FALSE;
#endif
    U16 nFontID;
#endif

    width = 0;
    length = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth);

        msAPI_OSD_GET_resource();

    if( length )
    {
    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
#if (ENABLE_TTF_FONT)
        switch(MApp_GetLanguageForFont())
#else
        switch(enLanguage)
#endif
        {
        #if ENABLE_ARABIC_OSD
            case LANGUAGE_OSD_ARABIC:
            case LANGUAGE_OSD_PARSI:
            case LANGUAGE_OSD_KURDISH:
            case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
            case LANGUAGE_OSD_UYGHUR:
#endif
                nFontID = FontHandleIndex[font_handle];
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
                if ( nFontID < FONT_MULTILANG_BEGIN )
                {
    /*
                    if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                    {
                        bHebrew = TRUE;
                    }
                    else
    */
                    {
                        if ( bHebrewMixedMode )
                        {
                            bHebrew = TRUE;
                        }
                        else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        {
                            font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                        }

                        if ( !bDivxSubtitleMode )
                        {
                            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                        }
                    }
                }

                if ( bHebrew == FALSE )
                {
                    bArabicDisplay = TRUE;
                }
                break;

            case LANGUAGE_OSD_HEBREW:
                bHebrew = TRUE;
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
                if ( !bDivxSubtitleMode )
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                }
                break;
    #endif

    #if ( ENABLE_THAI_OSD )
            case LANGUAGE_OSD_THAI:
                nFontID = FontHandleIndex[font_handle];
                pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;

                if ( nFontID < FONT_MULTILANG_BEGIN )
                {
    /*
                    if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                    {
                        bHebrew = TRUE;
                    }
                    else
    */
                    {
                        if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                            font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                    }
                }

        #if ( ENABLE_ARABIC_OSD )
                if ( bHebrew == FALSE )
        #endif
                {
                    bThaiDisplay = TRUE;
                }
                break;
    #endif
    /*
            case LANGUAGE_OSD_CHINESE:
                nFontID = FontHandleIndex[font_handle];
                if ( nFontID < FONT_MULTILANG_BEGIN )
                {
                    if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                    {
                        bHebrew = TRUE;
                    }
                    else
                    {
                        if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                        {
                            font_handle = Font[nFontID+18].fHandle;
                        }
                        else if ( nFontID >= FONT_EXT_BEGIN )
                        {
                            //Do Chinese icon unicode conversion here
                        }
                    }
                }
                break;
    */
            default:
                pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
                break;
        }
    #endif

    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
        {
            bMirrorLang = TRUE;
        }
    #endif

        if(pclrBtn->bStringIndexWidth==CHAR_IDX_2BYTE)
        {
        #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
            if (length >= sizeof(TempBuf.U8Str)/2)
            {
                length = sizeof(TempBuf.U8Str)/2 - 1;
            }
        #endif
        #if (ENABLE_ARABIC_OSD)
            if ( bMirrorLang )
            {
                memcpy(TempBuf.U8Str,pu8Str,length*2);
                TempBuf.U16Str[length] = 0;

                //For Subtitle
                if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
                {
                    S32 errorCode = U_ZERO_ERROR;

                    ArabicParser(TempBuf.U16Str, length, outbuf.U16Str, STROSD,
                             U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                             &errorCode);
                    //Every language is possible, you can't skip this filter here
                    msAPI_OSD_KurdishFilter(outbuf.U16Str, length);
                }
                else if ( bArabicDisplay ) //for OSD
                {
                     S32 errorCode = U_ZERO_ERROR;

                    ArabicParser(TempBuf.U16Str, length, outbuf.U16Str, STROSD,
                             U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                             &errorCode);
                    //just skip this function for non Kurdish condition
                    if ( enLanguage == LANGUAGE_OSD_KURDISH )
                    {
                        msAPI_OSD_KurdishFilter(outbuf.U16Str, length);
                    }
                    else if ( enLanguage == LANGUAGE_OSD_URDU )
                    {
                        msAPI_OSD_UrduFilter(outbuf.U16Str, length);
                    }
                }
                else    // for Hebrew
                {
                    memcpy(outbuf.U8Str, pu8Str, length*2);
                }

                outbuf.U16Str[length] = 0;

                pu8Str = outbuf.U8Str;
            }
        #endif

        #if (ENABLE_THAI_OSD)
            else if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
            {
                //if(pclrBtn->bStringIndexWidth == CHAR_IDX_2BYTE)
                //{
                    memcpy(TempBuf.U8Str,pu8Str,length*2);
                    TempBuf.U16Str[length] = 0;

                    //pu16Str = (U16 *)pu8Str;

                    length = Thai_compose(TempBuf.U16Str, 0, length, STROSD, outbuf.U16Str);
                    outbuf.U16Str[length] = 0x0000;

                    pu8Str = outbuf.U8Str;
                //}
            }
            else
        #endif
            {
    //            memcpy(outbuf.U8Str,pu8Str,length*2);
    //            outbuf.U16Str[length] = 0;
    //            pu8Str = outbuf.U8Str;
            }
        }

        if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
            {
                for(i=0; i<length; i++)
                {
                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[i], &BBox_X_Info);
                    width += BBox_X_Info.u8Width;
                }
            }
            else //(pclrBtn->bStringIndexWidth == CHAR_IDX_2BYTE)
            {
                //pu16Str = (U16*)pu8Str;

    #if (ENABLE_ARABIC_OSD)
                    //For Subtitle
                    if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
                    {
                        U16 u16Unicode, u16Unicode2;

                        for(i=0;i<length;i++)
                        {
                            // Check if it is in Arabic Vowel unicode range
                            u16Unicode2 = (pu8Str[i*2+1]<<8) + pu8Str[i*2];

                            if ( i > 0 )
                            {
                                u16Unicode = (pu8Str[i*2-1]<<8) + pu8Str[i*2-2];

                                //if ( msAPI_OSD_IsArabicVowel( pu16Str[i-1] ) )
                                if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    width -= BBox_X_Info.u8Width;
                                    //msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[i], &BBox_X_Info);
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode2, &BBox_X_Info);
                                    width += BBox_X_Info.u8Width;
                                }
                                else
                                {
                                    //msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[i], &BBox_X_Info);
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode2, &BBox_X_Info);
                                    width += BBox_X_Info.u8Width;
                                }
                            }
                            else
                            {
                                //msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[i], &BBox_X_Info);
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode2, &BBox_X_Info);
                                width += BBox_X_Info.u8Width;
                            }
                        }
                    }
                    else if ( bArabicDisplay ) //for OSD
                    {
                        U16 u16Unicode;

                for(i=0; i<length; i++)
                {
                            u16Unicode = (pu8Str[i*2+1]<<8) + pu8Str[i*2];

                            // Check if it is in Arabic Vowel unicode range
                            if ( i > 0 )
                            {
                                //if ( msAPI_OSD_IsArabicVowel( pu16Str[i] ) )
                                if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                                {
                                        //skip current vowel character width
                                        //do nothing here
                                }
                                else
                                {
                                    //msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[i], &BBox_X_Info);
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    width += BBox_X_Info.u8Width;
                                }
                            }
                            else
                            {
                                //msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[i], &BBox_X_Info);
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                    width += BBox_X_Info.u8Width;
                }
            }
                    }
                    else
    #endif
    #if (ENABLE_THAI_OSD)
                    if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
                    {
                        U16 u16Unicode;

                        for(i=0;i<length;i++)
                        {
                            // Check Primary Thai unicode range
                            u16Unicode = (pu8Str[i*2+1]<<8) + pu8Str[i*2];

                            if ( ( u16Unicode <= 0x0E5B ) && ( u16Unicode >= 0x0E01 ) )
                            {
                                if ( MinusDrawTable[ u16Unicode - 0x0E01 ] )
                                {
                                    //Minus coordinate, don't add width
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    width += BBox_X_Info.u8Width;
                                }
                            }
                            else if ( ( u16Unicode <= 0xF71A ) && ( u16Unicode >= 0xF700 ) )
                            {
                                if ( MinusDrawTablePersentation[ u16Unicode - 0xF700 ] )
                                {
                                    //Minus coordinate, don't add width
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    width += BBox_X_Info.u8Width;
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                width += BBox_X_Info.u8Width;
                            }
                        }
                    }
                    else
    #endif
                    {
                        U16 u16Unicode;

                        for(i=0; i<length; i++)
                        {
                            u16Unicode = (pu8Str[i*2+1]<<8) + pu8Str[i*2];

                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                            width += BBox_X_Info.u8Width;
                        }
                    }
                }

    #if (ENABLE_ARABIC_OSD)
            if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
            {
                pclrBtn->Fontfmt.ifont_gap = 0;
            }
    #endif

            if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
            {
                width += ((length-1) * pclrBtn->Fontfmt.ifont_gap);
            }
        }
        else
        {
            msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
            width = length * finfo.width;
        }
    }

      msAPI_OSD_Free_resource();

    return width;
}



#if 1
/******************************************************************************/
/// API for draw line::
/// @param p_clr_line \b IN line color
/******************************************************************************/
void msAPI_OSD_DrawLine(OSDClrLine *p_clr_line)
{

#if GE_DRIVER_TEST

    GELineRect.LineRectCoordinate.v0_x = p_clr_line->x1;
    GELineRect.LineRectCoordinate.v0_y = p_clr_line->y1;
    GELineRect.LineRectCoordinate.v1_x = p_clr_line->x2;
    GELineRect.LineRectCoordinate.v1_y = p_clr_line->y2;
    GELineRect.Gradient_Color_Flag     = GECOLOR_FLAG_CONSTANT;
    GELineRect.ARGBClr.ForeGroundColor.u32Num
    = (p_clr_line->u32LineColor&0xff00ff00) + ((p_clr_line->u32LineColor&0xff)<<16) +((p_clr_line->u32LineColor>>16)&0xff);
    MDrv_GE_LineDraw(&GELineRect);

#else

    GFX_DrawLineInfo pline;

    msAPI_OSD_GET_resource();
    pline.x1 = p_clr_line->x1;
    pline.x2 = p_clr_line->x2;
    pline.y1 = p_clr_line->y1;
    pline.y2 = p_clr_line->y2;
    memcpy(&pline.colorRange.color_s, &p_clr_line->u32LineColor , 4);
    memcpy(&pline.colorRange.color_e, &p_clr_line->u32LineColor , 4);

    pline.flag = 0;
//  memcpy (&clrline, p_clr_line, sizeof(GEClrLine));
//    lfmt.width = p_clr_line->u8LineWidth;
//    MDrv_GE_LineTo(&clrline, &lfmt);
    pline.fmt = GFX_FMT_RGB565;
    pline.width = p_clr_line->u8LineWidth;

    MApi_GFX_DrawLine(&pline);
    msAPI_OSD_Free_resource();

#endif

}
#else
/******************************************************************************/
/// API for draw line::
/// @param pclrBtn \b IN color
/******************************************************************************/
void msAPI_OSD_DrawLine(OSDClrBtn *pclrBtn)
{
/*
    if((pclrBtn->x + pclrBtn->width) > NEWUI_MAIN_MENU_GWIN_WIDTH)
    {
        return;
    }
    else if((pclrBtn->y + pclrBtn->height) > NEWUI_MAIN_MENU_GWIN_HEIGHT)
    {
        return;
    }
*/
#if GE_DRIVER_TEST

    GELineRect.LineRectCoordinate.v0_x = pclrBtn->x;
    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;
    GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width;
    GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height;
    GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_CONSTANT;
    GELineRect.ARGBClr.ForeGroundColor.u32Num
    = (pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);
    MDrv_GE_LineDraw(&GELineRect);

#else

    clrline.x1 = pclrBtn->x;
    clrline.y1 = pclrBtn->y;
    clrline.x2 = pclrBtn->x + pclrBtn->width;
    clrline.y2 = pclrBtn->y + pclrBtn->height;
    lfmt.width = pclrBtn->bFrameWidth;
    memcpy(&clrline.clr, &pclrBtn->b_clr, 4);
    MDrv_GE_LineTo(&clrline, &lfmt);
#endif

}
#endif
/*****************************************************************************************************/

#if ENABLE_DEFAULT_KERNING
static U8 kerningX_(U8 char1, U8 char2)
{
    U8 i;

    if (char1 == 0 || char2 == 0 || char1 > 'Z')
    {
        return 0;
    }

    for (i = 0; i < kerningTblSize; i++)
    {
        if (char1 == kerningTable[i].char1 && char2 == kerningTable[i].char2)
        {
            return kerningTable[i].kVal;
        }
    }
    return 0;
}
#endif //ENABLE_DEFAULT_KERNING
typedef struct
{
    EN_LANGUAGE enLangIndex;
    EN_OSDAPI_LANGUAGE enOSDLangIndex;
} Language2OSDLanguage;

static code Language2OSDLanguage stLanguage2OSDLanguage[]=
{
    {LANGUAGE_CZECH,             LANGUAGE_OSD_CZECH},//0
    {LANGUAGE_DANISH,            LANGUAGE_OSD_DANISH},
    {LANGUAGE_GERMAN,            LANGUAGE_OSD_GERMAN},
    {LANGUAGE_ENGLISH,           LANGUAGE_OSD_ENGLISH},
    {LANGUAGE_SPANISH,           LANGUAGE_OSD_SPANISH},
    {LANGUAGE_GREEK,             LANGUAGE_OSD_GREEK},//5
    {LANGUAGE_FRENCH,            LANGUAGE_OSD_FRENCH},
    {LANGUAGE_CROATIAN,          LANGUAGE_OSD_CROATIAN},
    {LANGUAGE_ITALIAN,           LANGUAGE_OSD_ITALIAN},
    {LANGUAGE_HUNGARIAN,         LANGUAGE_OSD_HUNGARIAN},
    {LANGUAGE_DUTCH,             LANGUAGE_OSD_DUTCH},//10
    {LANGUAGE_NORWEGIAN,         LANGUAGE_OSD_NORWEGIAN},
    {LANGUAGE_POLISH,            LANGUAGE_OSD_POLISH},
    {LANGUAGE_PORTUGUESE,        LANGUAGE_OSD_PORTUGUESE},
    {LANGUAGE_RUSSIAN,           LANGUAGE_OSD_RUSSIAN},
    {LANGUAGE_ROMANIAN,          LANGUAGE_OSD_ROMANIAN},//15
    {LANGUAGE_SLOVENIAN,         LANGUAGE_OSD_SLOVENIAN},
    {LANGUAGE_SERBIAN,           LANGUAGE_OSD_SERBIAN},
    {LANGUAGE_FINNISH,           LANGUAGE_OSD_FINNISH},
    {LANGUAGE_SWEDISH,           LANGUAGE_OSD_SWEDISH},
    {LANGUAGE_BULGARIAN,         LANGUAGE_OSD_BULGARIAN},//20
    {LANGUAGE_SLOVAK,            LANGUAGE_OSD_SLOVAK},
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || CHINESE_SIMP_FONT_ENABLE || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    {LANGUAGE_CHINESE,           LANGUAGE_OSD_CHINESE},
#endif
    {LANGUAGE_GAELIC,            LANGUAGE_OSD_GAELIC},
    {LANGUAGE_WELSH,             LANGUAGE_OSD_WELSH},
    {LANGUAGE_IRISH,             LANGUAGE_OSD_IRISH},//25
    {LANGUAGE_KOREAN,            LANGUAGE_OSD_KOREAN},
    {LANGUAGE_JAPAN,             LANGUAGE_OSD_JAPAN},
    {LANGUAGE_HINDI,             LANGUAGE_OSD_HINDI},
    {LANGUAGE_MAORI,             LANGUAGE_OSD_MAORI},
    {LANGUAGE_MANDARIN,          LANGUAGE_OSD_MANDARIN},//30
    {LANGUAGE_CANTONESE,         LANGUAGE_OSD_CANTONESE},
    {LANGUAGE_TURKISH,           LANGUAGE_OSD_TURKISH},
    {LANGUAGE_NETHERLANDS,       LANGUAGE_OSD_NETHERLANDS},
    {LANGUAGE_ARABIC,            LANGUAGE_OSD_ARABIC},
    {LANGUAGE_ARABIC,            LANGUAGE_OSD_HEBREW},//35
    {LANGUAGE_KURDISH,           LANGUAGE_OSD_KURDISH},
    {LANGUAGE_URDU,              LANGUAGE_OSD_URDU},
    {LANGUAGE_BENGALI,           LANGUAGE_OSD_BENGALI},
    {LANGUAGE_TELUGU,            LANGUAGE_OSD_TELUGU},
    {LANGUAGE_MARATHI,           LANGUAGE_OSD_MARATHI},//40
    {LANGUAGE_TAMIL,             LANGUAGE_OSD_TAMIL},
    {LANGUAGE_MYANMAR,           LANGUAGE_OSD_MYANMAR},
    {LANGUAGE_UYGHUR,            LANGUAGE_OSD_UYGHUR},
    {LANGUAGE_KHMER,             LANGUAGE_OSD_KHMER},
    {LANGUAGE_LAO,               LANGUAGE_OSD_LAO},//45
    {LANGUAGE_ASSAMESE,          LANGUAGE_OSD_ASSAMESE},
    {LANGUAGE_GUJARATI,          LANGUAGE_OSD_GUJARATI},
    {LANGUAGE_KANNADA,           LANGUAGE_OSD_KANNADA},
    {LANGUAGE_MALAYALAM,         LANGUAGE_OSD_MALAYALAM},
    {LANGUAGE_PUNJABI,           LANGUAGE_OSD_PUNJABI},//50
    {LANGUAGE_PARSI,             LANGUAGE_OSD_PARSI},
    {LANGUAGE_THAI,              LANGUAGE_OSD_THAI},//52
#if(ENABLE_COUNTRY_ICELANDIC)
    {LANGUAGE_ICELANDIC,         LANGUAGE_OSD_ICELAND},//53
    {LANGUAGE_SAMI,              LANGUAGE_OSD_SAMI},//54
#endif
};

EN_OSDAPI_LANGUAGE msAPI_OSD_APILanguage2OSDLanguage(EN_LANGUAGE enLangIndex)
{
    U8 u8Loop;

    for(u8Loop = 0; u8Loop < sizeof(stLanguage2OSDLanguage)/sizeof(Language2OSDLanguage); u8Loop++)
    {
        if(stLanguage2OSDLanguage[u8Loop].enLangIndex == enLangIndex)
            return stLanguage2OSDLanguage[u8Loop].enOSDLangIndex;
    }
    return LANGUAGE_OSD_ENGLISH; // Unknow Language, return English.
}

void msAPI_OSD_SetOSDLanguage(EN_OSDAPI_LANGUAGE eLanguage)
{
    enLanguage = eLanguage;

#if ( ENABLE_TTF_FONT )
    switch( eLanguage )
    {
    case LANGUAGE_OSD_CZECH:
        enLanguageTag = LE_LANGUAGE_TAG_CSY;
        break;
    case LANGUAGE_OSD_DANISH:
        enLanguageTag = LE_LANGUAGE_TAG_DAN;
        break;
    case LANGUAGE_OSD_GERMAN:
        enLanguageTag = LE_LANGUAGE_TAG_DEU;
        break;
    case LANGUAGE_OSD_ENGLISH:
        enLanguageTag = LE_LANGUAGE_TAG_ENG;
        break;
    case LANGUAGE_OSD_SPANISH:
        enLanguageTag = LE_LANGUAGE_TAG_ESP;
        break;
    case LANGUAGE_OSD_GREEK:
        enLanguageTag = LE_LANGUAGE_TAG_ELL;
        break;
    case LANGUAGE_OSD_FRENCH:
        enLanguageTag = LE_LANGUAGE_TAG_FRA;
        break;
    case LANGUAGE_OSD_CROATIAN:
        enLanguageTag = LE_LANGUAGE_TAG_HRV;
        break;
    case LANGUAGE_OSD_ITALIAN:
        enLanguageTag = LE_LANGUAGE_TAG_ITA;
        break;
    case LANGUAGE_OSD_HUNGARIAN:
        enLanguageTag = LE_LANGUAGE_TAG_HUN;
        break;
    case LANGUAGE_OSD_DUTCH:
        enLanguageTag = LE_LANGUAGE_TAG_NLD;
        break;
    case LANGUAGE_OSD_NORWEGIAN:
        enLanguageTag = LE_LANGUAGE_TAG_NOR;
        break;
    case LANGUAGE_OSD_POLISH:
        enLanguageTag = LE_LANGUAGE_TAG_PLK;
        break;
    case LANGUAGE_OSD_PORTUGUESE:
        enLanguageTag = LE_LANGUAGE_TAG_PTG;
        break;
    case LANGUAGE_OSD_RUSSIAN:
        enLanguageTag = LE_LANGUAGE_TAG_RUS;
        break;
    case LANGUAGE_OSD_ROMANIAN:
        enLanguageTag = LE_LANGUAGE_TAG_ROM;
        break;
    case LANGUAGE_OSD_SLOVENIAN:
        enLanguageTag = LE_LANGUAGE_TAG_SLV;
        break;
    case LANGUAGE_OSD_SERBIAN:
        enLanguageTag = LE_LANGUAGE_TAG_SRB;
        break;
    case LANGUAGE_OSD_FINNISH:
        enLanguageTag = LE_LANGUAGE_TAG_FIN;
        break;
    case LANGUAGE_OSD_SWEDISH:
        enLanguageTag = LE_LANGUAGE_TAG_SVE;
        break;
    case LANGUAGE_OSD_BULGARIAN:
        enLanguageTag = LE_LANGUAGE_TAG_BGR;
        break;
    case LANGUAGE_OSD_SLOVAK:
        enLanguageTag = LE_LANGUAGE_TAG_SKY;
        break;
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || CHINESE_SIMP_FONT_ENABLE || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    case LANGUAGE_OSD_CHINESE:
        enLanguageTag = LE_LANGUAGE_TAG_ZHT;
        break;
#endif
    case LANGUAGE_OSD_GAELIC:
        enLanguageTag = LE_LANGUAGE_TAG_GAE;
        break;
    case LANGUAGE_OSD_WELSH:
        enLanguageTag = LE_LANGUAGE_TAG_WEL;
        break;
    case LANGUAGE_OSD_IRISH:
        enLanguageTag = LE_LANGUAGE_TAG_IRI;
        break;
    case LANGUAGE_OSD_KOREAN:
        enLanguageTag = LE_SCRIPT_TAG_KORE;
        break;
    case LANGUAGE_OSD_JAPAN:
        enLanguageTag = LE_LANGUAGE_TAG_JAN;
        break;
    case LANGUAGE_OSD_HINDI:
        enLanguageTag = LE_LANGUAGE_TAG_HIN;
        break;
    case LANGUAGE_OSD_MAORI:
        enLanguageTag = LE_LANGUAGE_TAG_MRI;
        break;
    case LANGUAGE_OSD_MANDARIN:
        enLanguageTag = LE_LANGUAGE_TAG_ZHT;
        break;
    case LANGUAGE_OSD_CANTONESE:
        enLanguageTag = LE_LANGUAGE_TAG_ZHH;
        break;
    case LANGUAGE_OSD_TURKISH:
        enLanguageTag = LE_LANGUAGE_TAG_TRK;
        break;
    case LANGUAGE_OSD_NETHERLANDS:
        enLanguageTag = LE_LANGUAGE_TAG_NLD;
        break;
    case LANGUAGE_OSD_ARABIC:
        enLanguageTag = LE_LANGUAGE_TAG_ARA;
        break;
    case LANGUAGE_OSD_HEBREW:
        enLanguageTag = LE_LANGUAGE_TAG_IWR;
        break;
    case LANGUAGE_OSD_KURDISH:
        enLanguageTag = LE_LANGUAGE_TAG_KUR;
        break;
    case LANGUAGE_OSD_URDU:
        enLanguageTag = LE_LANGUAGE_TAG_URD;
        break;
    case LANGUAGE_OSD_BENGALI:
        enLanguageTag = LE_LANGUAGE_TAG_BEN;
        break;
    case LANGUAGE_OSD_TELUGU:
        enLanguageTag = LE_LANGUAGE_TAG_TEL;
        break;
    case LANGUAGE_OSD_MARATHI:
        enLanguageTag = LE_LANGUAGE_TAG_MAR;
        break;
    case LANGUAGE_OSD_TAMIL:
        enLanguageTag = LE_LANGUAGE_TAG_TAM;
        break;
    case LANGUAGE_OSD_MYANMAR:
        enLanguageTag = LE_SCRIPT_TAG_MYMR;
        break;
    case LANGUAGE_OSD_UYGHUR:
        enLanguageTag = LE_LANGUAGE_TAG_UYG;
        break;
    case LANGUAGE_OSD_KHMER:
        enLanguageTag = LE_LANGUAGE_TAG_KHM;
        break;
    case LANGUAGE_OSD_LAO:
        enLanguageTag = LE_LANGUAGE_TAG_LAO;
        break;
    case LANGUAGE_OSD_ASSAMESE:
        enLanguageTag = LE_LANGUAGE_TAG_ASM;
        break;
    case LANGUAGE_OSD_GUJARATI:
        enLanguageTag = LE_LANGUAGE_TAG_GUJ;
        break;
    case LANGUAGE_OSD_KANNADA:
        enLanguageTag = LE_LANGUAGE_TAG_KAN;
        break;
    case LANGUAGE_OSD_MALAYALAM:
        enLanguageTag = LE_LANGUAGE_TAG_MLR;
        break;
    case LANGUAGE_OSD_PUNJABI:
        enLanguageTag = LE_LANGUAGE_TAG_PAN;
        break;
    case LANGUAGE_OSD_PARSI:
        enLanguageTag = LE_LANGUAGE_TAG_FAR;
        break;
    case LANGUAGE_OSD_THAI:
        enLanguageTag = LE_LANGUAGE_TAG_THA;
        break;
    default:
        enLanguageTag = LE_LANGUAGE_TAG_ENG;
        break;
}
#endif
}

EN_OSDAPI_LANGUAGE msAPI_OSD_GetOSDLanguage(void)
{
    return enLanguage;
}

#if ( ENABLE_TTF_FONT )
LE_LanguageTag_e msAPI_OSD_GetOSDLanguageTag(void)
{
    return enLanguageTag;
}
#endif

void msAPI_GOP_GWIN_SetHMirror(BOOL bHMirror)
{
#if ENABLE_PANEL_H_MIRROR
    MApi_GOP_GWIN_SetHMirror(!bHMirror);
#else
    MApi_GOP_GWIN_SetHMirror(bHMirror);
#endif
}

void msAPI_GOP_GWIN_SetVMirror(BOOL bVMirror)
{
    MApi_GOP_GWIN_SetVMirror(bVMirror);
}

#if ( ENABLE_ARABIC_OSD || ENABLE_THAI_OSD || ENABLE_INDIA_OSD || ENABLE_TTF_FONT )
void msAPI_OSD_Set_H_Mirror(BOOLEAN bEnableMirror)
{
    static U8 bMirrorStatus = 0xFF; // 0xFF for first time

#if (MirrorEnable)
    if(stGenSetting.g_SysSetting.g_MirrorEnable)
    {
        bEnableMirror = !bEnableMirror;
    }
#endif
    if ( bMirrorStatus != bEnableMirror )
    {
        msAPI_GOP_GWIN_SetHMirror(bEnableMirror);
        bMirrorStatus = bEnableMirror;
    }
}
#endif

#if (ENABLE_ARABIC_OSD)

#define PURE_ARABIC_CHAR    0
#define ASCII_MARK_CHAR     1
#define PURE_ENGNUM_CHAR    2

#if 0
static BOOLEAN msAPI_OSD_IsArabicHebrew(U16 inputc)
{
    // Arabic Characters unicode range:
    // 0600~ 06FF
    // 0750~ 077F
    // FB50~ FDFF
    // FE70~ FEFF

    // Hebrew Characters unicode range:
    // 0590~ 05FF
    // FB00~ FB4F   not support here

    if(((inputc >= 0x0600) && (inputc <= 0x06FF))
        ||((inputc >= 0x0750) && (inputc <= 0x077F))
        ||((inputc >= 0xFB50) && (inputc <= 0xFDFF))
        ||((inputc >= 0xFE70) && (inputc <= 0xFEFF))
        ||((inputc >= 0x0590) && (inputc <= 0x05FF))
        ||((inputc >= 0xFB00) && (inputc <= 0xFB4F))
      )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}
#endif


static U8 msAPI_OSD_IsNotInArabicHebrew(U16 inputc)
{
    // Arabic Characters unicode range:
    // 0600~ 06FF
    // 0750~ 077F
    // FB50~ FDFF
    // FE70~ FEFF

    // Hebrew Characters unicode range:
    // 0590~ 05FF
    // FB00~ FB4F   not support here

    if ( inputc < 0x0030 )
        return ASCII_MARK_CHAR;

    if ( inputc < 0x003A )  // 0~9
        return PURE_ENGNUM_CHAR;

    if ( inputc < 0x0041 )
        return ASCII_MARK_CHAR;

    if ( inputc < 0x005B )  // A~Z
        return PURE_ENGNUM_CHAR;

    if ( inputc < 0x0061 )
        return ASCII_MARK_CHAR;

    if ( inputc < 0x007B )  // a~z
        return PURE_ENGNUM_CHAR;

    if ( inputc < 0x0590 )
        return ASCII_MARK_CHAR;

    if ( ( inputc > 0x06FF ) && ( inputc < 0x0750 ) )
        return ASCII_MARK_CHAR;

    if ( ( inputc > 0x077F ) && ( inputc < 0xFB50 ) )
        return ASCII_MARK_CHAR;

    if ( ( inputc > 0xFDFF ) && ( inputc < 0xFE70 ) )
        return ASCII_MARK_CHAR;

    if ( inputc > 0xFEFF )
        return ASCII_MARK_CHAR;

    return PURE_ARABIC_CHAR;
}

static U8 msAPI_OSD_IsArabicVowel(U16 inputc)
{
    //Arabic Vowel characters presentation form
    //0xFE70 0xFE72 0xFE74 0xFE76 0xFE78 0xFE7A
    switch(inputc)
    {
    case 0xFE70:
    case 0xFE72:
    case 0xFE74:
    case 0xFE76:
    case 0xFE78:
    case 0xFE7A:
    case 0xFE7C:
    case 0xFE7E:
        return TRUE;
    default:
        return FALSE;
    }
}

static void msAPI_OSD_ReverseAllCharacters(U16 *inp, U16 *outp, U16 len)
{
    U16 i=0;

    while( (i<len) && ( inp[i] != 0x0000 ) )
    {
        outp[len-i-1] = inp[i];
        i++;
    }
}

static void msAPI_OSD_ASCII_MarkReplace( U16 inValue, U16 *outp, U16 i, U16 *indexp, U8 bMirrorLang )
{
    //case for other mirror language
    //dumy code here
    bMirrorLang = bMirrorLang;

    switch( inValue )
    {
    case 0x0028:
        *outp = 0x0029;
        indexp[0] = i;
        break;
    case 0x0029:
        *outp = 0x0028;
        indexp[1] = i;
        break;
    case 0x003C:
        *outp = 0x003E;
        indexp[2] = i;
        break;
    case 0x003E:
        *outp = 0x003C;
        indexp[3] = i;
        break;
    case 0x005B:
        *outp = 0x005D;
        indexp[4] = i;
        break;
    case 0x005D:
        *outp = 0x005B;
        indexp[5] = i;
        break;
    case 0x007B:
        *outp = 0x007D;
        indexp[6] = i;
        break;
    case 0x007D:
        *outp = 0x007B;
        indexp[7] = i;
        break;
/*
    case Other unicode pair 1:
        if ( bMirrorLang )
        {
            *outp = Other unicode pair 2;
            indexp[8] = i;
        }
        else
        {
            *outp = inValue;
        }
        break;
    case Other unicode pair 2:
        if ( bMirrorLang )
        {
            *outp = Other unicode pair 1;
            indexp[9] = i;
        }
        else
        {
            *outp = inValue;
        }
        break;
*/
    default:
        *outp = inValue;
        break;
    }
}

#define WINXP_COMPATIBILITY_MODE    FALSE

static void msAPI_OSD_ReverseNonArabicHebrewCharacters(U16 *inp, U16 *outp, U16 len)
{
    U16 i=0, j=0, k=0, nStartSearchPos;
    U8 nResult, bMirrorLang = FALSE;
#if (!WINXP_COMPATIBILITY_MODE)
    U8 nResultNext = PURE_ARABIC_CHAR, bASCIIFound = FALSE;
    U16 nPureArabicPos = 0xFFFF, nPureEngPos = 0xFFFF;
#endif
    U16 ASCII_Mark_Index[10];
    U16 ASCII_Mark_Index_InLoop[4];

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
    case LANGUAGE_OSD_ARABIC:
    case LANGUAGE_OSD_PARSI:
    case LANGUAGE_OSD_KURDISH:
    case LANGUAGE_OSD_HEBREW:
    case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
    case LANGUAGE_OSD_UYGHUR:
#endif
        bMirrorLang = TRUE;
        break;
    default:
        break;
    }
/*
    if ( bDivxSubtitleMode )
    {
        switch ( External Subtitle Language )
        {
        case LANGUAGE_OSD_HEBREW:
        case LANGUAGE_OSD_ARABIC:
            bMirrorLang = TRUE;
            break;
        }
    }
*/
    for( i = 0; i < len; i++ )
    {
        if ( msAPI_OSD_IsNotInArabicHebrew(inp[i]) == PURE_ARABIC_CHAR )
        {
            break;
        }
    }
    if ( i == len )
    {
        msAPI_OSD_ReverseAllCharacters(inp, outp, len);
/*
        if ( bMirrorLang )
        {
            for(j=0;j<len;j++)
            {
                switch(outp[j])
                {
                case Other unicode pair 1:
                    outp[j] = Other unicode pair 2;
                    break;
                case Other unicode pair 2:
                    outp[j] = Other unicode pair 1;
                    break;
                default:
                    break;
                }
            }
        }
*/
    }
    else
    {
        i = 0;
        memset(ASCII_Mark_Index, 0xFF, sizeof(ASCII_Mark_Index));

        while( (i<len) && ( inp[i] != 0x0000 ) )
        {
            if( ( (nResult = msAPI_OSD_IsNotInArabicHebrew(inp[i])) == PURE_ENGNUM_CHAR) || ( ((i+1) < len) && ( (inp[i] == 0x0025) || (inp[i] == 0x0022) ) && ( inp[i+1] >= 0x0030 ) && ( inp[i+1] <= 0x0039 ) ) )
            {
#if (!WINXP_COMPATIBILITY_MODE)

BackToReversePath:

                nStartSearchPos = i;

                if ( nResult == PURE_ENGNUM_CHAR )
                {
                    nPureEngPos = i;
                }
#endif

                j = 0;
                memset((void *)ASCII_Mark_Index_InLoop, 0xFF, sizeof(ASCII_Mark_Index_InLoop));

                while( (i<len) && ((nResult = msAPI_OSD_IsNotInArabicHebrew(inp[i])) > PURE_ARABIC_CHAR) && ( inp[i] != 0x0000 ) )
                {
#if (!WINXP_COMPATIBILITY_MODE)
                    if ( nResult == PURE_ENGNUM_CHAR )
                    {
                        nPureEngPos = i;
                    }

                    if ( ( (i+1) < len ) && ( nResult == ASCII_MARK_CHAR ) && ( ( nResultNext = msAPI_OSD_IsNotInArabicHebrew(inp[i+1]) ) == PURE_ARABIC_CHAR ) )
#else
                    if ( ( (i+1) < len ) && ( nResult == ASCII_MARK_CHAR ) && ( ( msAPI_OSD_IsNotInArabicHebrew(inp[i+1]) == PURE_ARABIC_CHAR ) || ( inp[i+1] == 0x0020 ) ) )
#endif
                        break;

                    if ( ( i == (len-1) ) && ( nResult == ASCII_MARK_CHAR ) )
                    {
                        switch(inp[i])
                        {
                        case 0x0028:
                            //search 0x0029
                            if ( ( ASCII_Mark_Index_InLoop[0] < nStartSearchPos ) || ( ASCII_Mark_Index_InLoop[0] == 0xFFFF ) )
                            {
                                goto OutWhileNormal;
                            }
                            break;
                        case 0x003C:
                            //search 0x003E
                            if ( ( ASCII_Mark_Index_InLoop[1] < nStartSearchPos ) || ( ASCII_Mark_Index_InLoop[1] == 0xFFFF ) )
                            {
                                goto OutWhileNormal;
                            }
                            break;
                        case 0x005B:
                            //search 0x005D
                            if ( ( ASCII_Mark_Index_InLoop[2] < nStartSearchPos ) || ( ASCII_Mark_Index_InLoop[2] == 0xFFFF ) )
                            {
                                goto OutWhileNormal;
                            }
                            break;
                        case 0x007B:
                            //search 0x007D
                            if ( ( ASCII_Mark_Index_InLoop[3] < nStartSearchPos ) || ( ASCII_Mark_Index_InLoop[3] == 0xFFFF ) )
                            {
                                goto OutWhileNormal;
                            }
                            break;
                        default:
                            goto OutWhileNormal;
                        }
                    }

                    switch( inp[i] )
                    {
#if (!WINXP_COMPATIBILITY_MODE)
                    case 0x002E:
                        if ( ( (i+1) < len ) && ( ( inp[i+1] == 0x0020 ) || ( nResultNext == PURE_ARABIC_CHAR ) ) )
                        {
                            goto OutWhile;
                        }
                        break;
#endif
                    case 0x0020:
                    case 0x0028:
                    case 0x0029:
                    case 0x003C:
                    case 0x003E:
                    case 0x005B:
                    case 0x005D:
                    case 0x007B:
                    case 0x007D:
#if (!WINXP_COMPATIBILITY_MODE)
                        if ( nPureArabicPos == 0xFFFF )
                        {
#endif
                            k = i+1;
                            while( k < len )
                            {
                                if ( msAPI_OSD_IsNotInArabicHebrew(inp[k]) == PURE_ARABIC_CHAR )
                                {
#if (!WINXP_COMPATIBILITY_MODE)
                                    nPureArabicPos = k;
#endif
                                    break;
                                }
                                k++;
                            }
#if (!WINXP_COMPATIBILITY_MODE)
                        }
#endif
                        if ( ( k == (i+1)) && ( k != len ) )
                        {
                            goto OutWhile;
                        }
                        switch(inp[i])
                        {
                        case 0x0029:
                            if ( ASCII_Mark_Index_InLoop[0] == 0xFFFF )
                            {
                                ASCII_Mark_Index_InLoop[0] = i;
                            }
                            break;
                        case 0x003E:
                            if ( ASCII_Mark_Index_InLoop[1] == 0xFFFF )
                            {
                                ASCII_Mark_Index_InLoop[1] = i;
                            }
                            break;
                        case 0x005D:
                            if ( ASCII_Mark_Index_InLoop[2] == 0xFFFF )
                            {
                                ASCII_Mark_Index_InLoop[2] = i;
                            }
                            break;
                        case 0x007D:
                            if ( ASCII_Mark_Index_InLoop[3] == 0xFFFF )
                            {
                                ASCII_Mark_Index_InLoop[3] = i;
                            }
                            break;
                        }
                        break;

#if (!WINXP_COMPATIBILITY_MODE)
                    default:
                        if ( nResult == ASCII_MARK_CHAR )
                        {
                            if ( nPureArabicPos == 0xFFFF )
                            {
                                k = i+1;
                                while( k < len )
                                {
                                    if ( msAPI_OSD_IsNotInArabicHebrew(inp[k]) == PURE_ARABIC_CHAR )
                                    {
                                        nPureArabicPos = k;
                                        break;
                                    }
                                    k++;
                                }
                            }

                            bASCIIFound = TRUE;
                        }
                        break;
#endif
                    }

                    j++;
                    i++;
                }

OutWhileNormal:

#if (!WINXP_COMPATIBILITY_MODE)
                if ( ( bASCIIFound ) && ( i > (nPureEngPos+1) ) && ( nPureArabicPos != 0xFFFF ) )
                {
                    j -= (i - (nPureEngPos+1));
                    i = nPureEngPos+1;
                }
#endif

OutWhile:

                for(k=0;k<j;k++)
                {
                    outp[i-j+k] = inp[i-1-k];
                }
            }
            else
            {
#if (!WINXP_COMPATIBILITY_MODE)
                if ( ( !( ( i == 0 ) && ( inp[i] == 0x002E ) ) ) &&
                ( nResult != PURE_ARABIC_CHAR ) &&
                ( inp[i] != 0x0020 ) &&
                ( inp[i] != 0x0021 ) &&
                ((i+1) < len) &&
                (msAPI_OSD_IsNotInArabicHebrew(inp[i+1]) == PURE_ENGNUM_CHAR) )
                    goto BackToReversePath;
#endif
                if ( ( i == 0 ) || ( i == (len-1) ) )
                {
                    msAPI_OSD_ASCII_MarkReplace( inp[i], &(outp[i]), i, ASCII_Mark_Index, bMirrorLang );
                }
                else
                {
#if (!WINXP_COMPATIBILITY_MODE)
                    U8 bMarkChange = TRUE;

                    if ( (i > 2) && ( msAPI_OSD_IsNotInArabicHebrew(inp[i-2]) == PURE_ENGNUM_CHAR ) )
                    {
                        bMarkChange = FALSE;
                    }

                    if ( ( i > 1 ) && ( inp[i] != 0x0020 ) && (bMarkChange) )
#else
                    if ( ( i > 1 ) && ( inp[i] != 0x0020 ) )
#endif
                    {
                        switch( outp[i-1] )
                        {
                        case 0x0028:
                            if ( ASCII_Mark_Index[1] != (i-1) )
                            {
                                outp[i-1] = 0x0029;
                                ASCII_Mark_Index[0] = i-1;
                            }
                            break;
                        case 0x0029:
                            if ( ASCII_Mark_Index[0] != (i-1) )
                            {
                                outp[i-1] = 0x0028;
                                ASCII_Mark_Index[1] = i-1;
                            }
                            break;
                        case 0x003C:
                            if ( ASCII_Mark_Index[3] != (i-1) )
                            {
                                outp[i-1] = 0x003E;
                                ASCII_Mark_Index[2] = i-1;
                            }
                            break;
                        case 0x003E:
                            if ( ASCII_Mark_Index[2] != (i-1) )
                            {
                                outp[i-1] = 0x003C;
                                ASCII_Mark_Index[3] = i-1;
                            }
                            break;
                        case 0x005B:
                            if ( ASCII_Mark_Index[5] != (i-1) )
                            {
                                outp[i-1] = 0x005D;
                                ASCII_Mark_Index[4] = i-1;
                            }
                            break;
                        case 0x005D:
                            if ( ASCII_Mark_Index[4] != (i-1) )
                            {
                                outp[i-1] = 0x005B;
                                ASCII_Mark_Index[5] = i-1;
                            }
                            break;
                        case 0x007B:
                            if ( ASCII_Mark_Index[7] != (i-1) )
                            {
                                outp[i-1] = 0x007D;
                                ASCII_Mark_Index[6] = i-1;
                            }
                            break;
                        case 0x007D:
                            if ( ASCII_Mark_Index[6] != (i-1) )
                            {
                                outp[i-1] = 0x007B;
                                ASCII_Mark_Index[7] = i-1;
                            }
                            break;
/*
                        case Other unicode pair 1:
                            if ( ( ASCII_Mark_Index[9] != (i-1) ) && ( bMirrorLang ) )
                            {
                                outp[i-1] = Other unicode pair 2;
                                ASCII_Mark_Index[8] = i-1;
                            }
                            break;
                        case Other unicode pair 2:
                            if ( ( ASCII_Mark_Index[8] != (i-1) ) && ( bMirrorLang ) )
                            {
                                outp[i-1] = Other unicode pair 1;
                                ASCII_Mark_Index[9] = i-1;
                            }
                            break;
*/
                        }
                    }

                    msAPI_OSD_ASCII_MarkReplace( inp[i], &(outp[i]), i, ASCII_Mark_Index, bMirrorLang );
                }
                i++;

                if ( ( i < len ) && ( outp[i-1] != 0x0020 ) )
                {
                    switch( inp[i] )
                    {
                    case 0x0028:
                        outp[i] = 0x0029;
                        ASCII_Mark_Index[0] = i;
                        i++;
                        break;
                    case 0x0029:
                        outp[i] = 0x0028;
                        ASCII_Mark_Index[1] = i;
                        i++;
                        break;
                    case 0x003C:
                        outp[i] = 0x003E;
                        ASCII_Mark_Index[2] = i;
                        i++;
                        break;
                    case 0x003E:
                        outp[i] = 0x003C;
                        ASCII_Mark_Index[3] = i;
                        i++;
                        break;
                    case 0x005B:
                        outp[i] = 0x005D;
                        ASCII_Mark_Index[4] = i;
                        i++;
                        break;
                    case 0x005D:
                        outp[i] = 0x005B;
                        ASCII_Mark_Index[5] = i;
                        break;
                    case 0x007B:
                        outp[i] = 0x007D;
                        ASCII_Mark_Index[6] = i;
                        break;
                    case 0x007D:
                        outp[i] = 0x007B;
                        ASCII_Mark_Index[7] = i;
                        break;
/*
                    case Other unicode pair 1:
                        if ( bMirrorLang )
                        {
                            outp[i] = Other unicode pair 2;
                            ASCII_Mark_Index[8] = i;
                        }
                        break;
                    case Other unicode pair 2:
                        if ( bMirrorLang )
                        {
                            outp[i] = Other unicode pair 1;
                            ASCII_Mark_Index[9] = i;
                        }
                        break;
*/
                    }
                }
            }
        }
    }
}

//0xFE70~FEFF
static const U8 u8FE70FormNotConnect[144] =
{
    //FE70
  //0  1  2  3  4  5  6  7  8  9  A  B  c  D  E  F
    1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,//7
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1,//8
    1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,//9
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,//A
    1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,//B
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,//C
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0,//D
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1,//E
    1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 //F
};

//0xFB50~0xFBFF
static const U8 u8FB50FormNotConnect[176] =
{
  //0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,//5
    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,//6
    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,//7
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//8
    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,//9
    1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,//A
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//B
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//C
    0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,//D
    1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,//E
    1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0 //F
};

BOOLEAN msAPI_OSD_IsFormNotConnect(U16 u16Char)
{
    if ( (u16Char >= 0xFB50) && (u16Char <= 0xFBFF) )
    {
        return u8FB50FormNotConnect[u16Char - 0xFB50];
    }
    else if ( (u16Char >= 0xFE70) && (u16Char <= 0xFEFF) )
    {
        return u8FE70FormNotConnect[u16Char - 0xFE70];
    }

    return TRUE;
}

//0xFE70~FEFF
static const U8 u8FE70FormNotConnectForward[144] =
{
    //FE70
  //0  1  2  3  4  5  6  7  8  9  A  B  c  D  E  F
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//7
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1,//8
    0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,//9
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1,//A
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1,//B
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1,//C
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,//D
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,//E
    0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 //F
};

//0xFB50~0xFBFF
static const U8 u8FB50FormNotConnectForward[176] =
{
  //0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1,//5
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//6
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1,//7
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,//8
    1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//9
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1,//A
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//B
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//C
    1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0,//D
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,//E
    1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 //F
};


BOOLEAN msAPI_OSD_IsFormNotConnectForward(U16 u16Char)
{
    if ( (u16Char >= 0xFB50) && (u16Char <= 0xFBFF) )
    {
        return u8FB50FormNotConnectForward[u16Char - 0xFB50];
    }
    else if ( (u16Char >= 0xFE70) && (u16Char <= 0xFEFF) )
    {
        return u8FE70FormNotConnectForward[u16Char - 0xFE70];
    }

    return TRUE;
}

static void msAPI_OSD_KurdishFilter(U16 *inp, U16 len)
{
    #define INITIAL 0
    #define MEDIAL  1
    #define FINAL   2
    #define ISOLATE 3

    U16 i;
    U8 bPrev = 0, bNext = 0, KurdishIndex;
    U8 CharAttribute[STROSD];
    static code U16 UnicodeArray[][4] =
    {
    //  initial, medial, final
    //0x06B5
        { 0xFBBA, 0xFBBB, 0xFBBC, 0x06B5 },  // 0
    //0x06B6
        { 0xFBBD, 0xFBBE, 0xFBBF, 0x06B6 },  // 1
    //0x06B7
        { 0xFBC0, 0xFBC1, 0xFBC2, 0x06B7 },  // 2
    //0x06CE
        { 0xFBC3, 0xFBC4, 0xFBC5, 0x06CE },  // 3
    //0x06A4
        { 0xFBC6, 0xFBC7, 0xFBC8, 0x06A4 },  // 4

    //0x0626, 0xFE89(special case)
        { 0xFE8B, 0xFE8C, 0xFE8C, 0x0626 },  // 5

    //0x0627,0xFE8D,0xFE8E
        { 0xFE8D, 0xFE8E, 0xFE8E, 0xFE8D },  // 6

    //0x0628,0xFE91,0xFE92,0xFE90,0xFE8F
        { 0xFE91, 0xFE92, 0xFE90, 0xFE8F },  // 7

    //0x062A,0xFE97,0xFE98,0xFE96,0xFE95
        { 0xFE97, 0xFE98, 0xFE96, 0xFE95 },  // 8

    //0x06D5,0xFEEA,0xFEE9
        { 0x06D5, 0x06D5, 0xFEEA, 0xFEE9 },  // 9

    //0x06AD,0xFBD5,0xFBD6,0xFBD4,0xFBD3
        { 0xFBD5, 0xFBD6, 0xFBD4, 0xFBD3 },  // 10

    //0x06C8,0xFBDC,0xFBDB
        { 0xFBDB, 0xFBDC, 0xFBDC, 0xFBDB },  // 11

    //0x064A,0xFEF3,0xFEF4,0xFEF2,0xFEF1
        { 0xFEF3, 0xFEF4, 0xFEF2, 0xFEF1 },  // 12

    //0x0643,0xFEDB,0xFEDC,0xFEDA,0xFED9
        { 0xFEDB, 0xFEDC, 0xFEDA, 0xFED9 },  // 13

    //0x06D0,0xFBE6,0xFBE7,0xFBE5,0xFBE4
        { 0xFBE6, 0xFBE7, 0xFBE5, 0xFBE4 },  // 14

    //0x0686,0xFB7C,0xFB7D,0xFB7B,0xFB7A
        { 0xFB7C, 0xFB7D, 0xFB7B, 0xFB7A },  // 15

    //0x0649,0xFBE8,0xFBE9,0xFEF0,0xFEEF
        { 0xFBE8, 0xFBE9, 0xFEF0, 0xFEEF },  // 16

    //0x06CB,0xFBDF,0xFBDE
        { 0xFBDE, 0xFBDF, 0xFBDF, 0xFBDE},  // 17

    //0x067E,0xFB58,0xFB59,0xFB57,0xFB56
        { 0xFB58, 0xFB59, 0xFB57, 0xFB56 },  // 18

    //0x062C,0xFE9F,0xFEA0,0xFE9E,0xFE9D
        { 0xFE9F, 0xFEA0, 0xFE9E, 0xFE9D },  // 19

    //0x062E,0xFEA7,0xFEA8,0xFEA6,0xFEA5
        { 0xFEA7, 0xFEA8, 0xFEA6, 0xFEA5 },  // 20

    //0x062F,0xFEAA,0xFEA9
        { 0xFEA9, 0xFEAA, 0xFEAA, 0xFEA9 },  // 21

    //0x0631,0xFEAE,0xFEAD
        { 0xFEAD, 0xFEAE, 0xFEAE, 0xFEAD },  // 22

    //0x0632,0xFEB0,0xFEAF
        { 0xFEAF, 0xFEB0, 0xFEB0, 0xFEAF },  // 23

    //0x0698,0xFB8B,0xFB8A
        { 0xFB8A, 0xFB8B, 0xFB8B, 0xFB8A },  // 24

    //0x0633,0xFEB3,0xFEB4,0xFEB2,0xFEB1
        { 0xFEB3, 0xFEB4, 0xFEB2, 0xFEB1 },  // 25

    //0x0634,0xFEB7,0xFEB8,0xFEB6,0xFEB5
        { 0xFEB7, 0xFEB8, 0xFEB6, 0xFEB5 },  // 26

    //0x063A,0xFECF,0xFED0,0xFECE,0xFECD
        { 0xFECF, 0xFED0, 0xFECE, 0xFECD },  // 27

    //0x0641,0xFED3,0xFED4,0xFED2,0xFED1
        { 0xFED3, 0xFED4, 0xFED2, 0xFED1 },  // 28

    //0x0642,0xFED7,0xFED8,0xFED6,0xFED5
        { 0xFED7, 0xFED8, 0xFED6, 0xFED5 },  // 29

    //0x06AF,0xFB94,0xFB95,0xFB93,0xFB92
        { 0xFB94, 0xFB95, 0xFB93, 0xFB92 },  // 30

    //0x0644,0xFEDF,0xFEE0,0xFEDE,0xFEDD
        { 0xFEDF, 0xFEE0, 0xFEDE, 0xFEDD },  // 31

    //0x0645,0xFEE3,0xFEE4,0xFEE2,0xFEE1
        { 0xFEE3, 0xFEE4, 0xFEE2, 0xFEE1 },  // 32

    //0x0646,0xFEE7,0xFEE8,0xFEE6,0xFEE5
        { 0xFEE7, 0xFEE8, 0xFEE6, 0xFEE5 },  // 33

    //0x06BE,0xFBAC,0xFBAD,0xFBAB,0xFBAA
        { 0xFBAC, 0xFBAD, 0xFBAB, 0xFBAA },  // 34

    //0x0648,0xFEEE,0xFEED
        { 0xFEEE, 0xFEEE, 0xFEEE, 0xFEED},  // 35

    //0x06C7,0xFBD8,0xFBD7
        { 0xFBD7, 0xFBD7, 0xFBD8, 0xFBD7 },  // 36

    //0x06C6,0xFBDA,0xFBD9
        { 0xFBD9, 0xFBDA, 0xFBDA, 0xFBD9 },  // 37

    //0x06A0
        { 0xFBA1, 0xFBA2, 0xFBA0, 0x06A0 },  // 38

    //0x06A1
        { 0xFBA4, 0xFBA5, 0xFBA3, 0x06A1 },  // 39

    //0x06A2
        { 0xFBA7, 0xFBA8, 0xFBA6, 0x06A2 },  // 40

    //0x06A3
        { 0xFBAA, 0xFBAB, 0xFBA9, 0x06A3 },  // 41

    //0x06A5
        { 0xFBAD, 0xFBAE, 0xFBAC, 0x06A5 },  // 42

    //0x06A6
        { 0xFB70, 0xFB71, 0xFB6F, 0x06A6 },  // 43

    //0x06A7
        { 0xFED3, 0xFED4, 0xFED2, 0x06A7 },  // 44

    //0x06A8
        { 0xFBC6, 0xFBC7, 0xFBC8, 0x06A8 },  // 45

    };

    for(i=0;i<len;i++)
    {
        if ( msAPI_OSD_IsNotInArabicHebrew(inp[i]) == PURE_ARABIC_CHAR )
        {
            CharAttribute[i] = 1;
        }
        else
        {
            CharAttribute[i] = 0;
        }
    }

    for(i=0;i<len;i++)
    {
        //BYTE eLang = MApp_GetLanguageForFont();
        switch(inp[i])
        {
        case 0x06B5:
        case 0x06B6:
        case 0x06B7:
        case 0x06CE:
        case 0x06A4:
            switch(inp[i])
            {
            case 0x06CE:
              KurdishIndex = 3;
              break;
            case 0x06A4:
              KurdishIndex = 4;
              break;
            default:
              KurdishIndex = inp[i] - 0x06B5;
              break;
            }

            if (i == 0)
            {
                if ( CharAttribute[i+1] )
                {
                    //It is initial, do shape
                    inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                }
                else
                {
                    //It is isolated, do nothing
                }
            }
            else if (i == (len-1))
            {
                if ( CharAttribute[i-1] )
                {
                    //It is final, do shape
                    inp[i] = UnicodeArray[KurdishIndex][FINAL];
                }
                else
                {
                    //It is isolated, do nothing
                }
            }
            else
            {
                bPrev = 0;
                bNext = 0;

                if ( CharAttribute[i-1] )
                {
                    //It has previous character
                    bPrev = 1;
                }
                if ( CharAttribute[i+1] )
                {
                    //It has next character
                    bNext = 1;
                }
                if ( ( bPrev ) && ( bNext ) )
                {
                    //It is medial, do shape
                    inp[i] = UnicodeArray[KurdishIndex][MEDIAL];
                }
                else if ( bPrev )
                {
                    //It is final, do shape
                    inp[i] = UnicodeArray[KurdishIndex][FINAL];
                }
                else if ( bNext )
                {
                    //It is initial, do shape
                    inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                }
                else
                {
                    //It is isolated, do nothing
                }
            }
            break;

        case 0x0626:
        case 0xFE89:
        case 0x0627://6
        case 0xFE8D:
        case 0xFE8E:
        case 0x0628://7
        case 0xFE91:
        case 0xFE92:
        case 0xFE90:
        case 0xFE8F:
        case 0x062A://8
        case 0xFE97:
        case 0xFE98:
        case 0xFE96:
        case 0xFE95:
        case 0x06D5://9
        case 0xFEEA:
        case 0xFEE9:
        case 0x06AD://10
        case 0xFBD5:
        case 0xFBD6:
        case 0xFBD4:
        case 0xFBD3:
        case 0x06C8://11
        case 0xFBDC:
        case 0xFBDB:
        case 0x064A://12
        case 0xFEF3:
        case 0xFEF4:
        case 0xFEF2:
        case 0xFEF1:
        case 0x0643://13
        case 0xFEDB:
        case 0xFEDC:
        case 0xFEDA:
        case 0xFED9:
        case 0x06D0://14
        case 0xFBE6:
        case 0xFBE7:
        case 0xFBE5:
        case 0xFBE4:
        case 0x0686://15
        case 0xFB7C:
        case 0xFB7D:
        case 0xFB7B:
        case 0xFB7A:
        case 0x0649://16
        case 0xFBE8:
        case 0xFBE9:
        case 0xFEF0:
        case 0xFEEF:
        case 0x06CB://17
        case 0xFBDF:
        case 0xFBDE:
        case 0x067E://18
        case 0xFB58:
        case 0xFB59:
        case 0xFB57:
        case 0xFB56:
        case 0x062C://19
        case 0xFE9F:
        case 0xFEA0:
        case 0xFE9E:
        case 0xFE9D:
        case 0x062E://20
        case 0xFEA7:
        case 0xFEA8:
        case 0xFEA6:
        case 0xFEA5:
        case 0x062F://21
        case 0xFEAA:
        case 0xFEA9:
        case 0x0631://22
        case 0xFEAE:
        case 0xFEAD:
        case 0x0632://23
        case 0xFEB0:
        case 0xFEAF:
        case 0x0698://24
        case 0xFB8B:
        case 0xFB8A:
        case 0x0633://25
        case 0xFEB3:
        case 0xFEB4:
        case 0xFEB2:
        case 0xFEB1:
        case 0x0634://26
        case 0xFEB7:
        case 0xFEB8:
        case 0xFEB6:
        case 0xFEB5:
        case 0x063A://27
        case 0xFECF:
        case 0xFED0:
        case 0xFECE:
        case 0xFECD:
        case 0x0641://28
        case 0xFED3:
        case 0xFED4:
        case 0xFED2:
        case 0xFED1:
        case 0x0642://29
        case 0xFED7:
        case 0xFED8:
        case 0xFED6:
        case 0xFED5:
        case 0x06AF://30
        case 0xFB94:
        case 0xFB95:
        case 0xFB93:
        case 0xFB92:
        case 0x0644://31
        case 0xFEDF:
        case 0xFEE0:
        case 0xFEDE:
        case 0xFEDD:
        case 0x0645://32
        case 0xFEE3:
        case 0xFEE4:
        case 0xFEE2:
        case 0xFEE1:
        case 0x0646://33
        case 0xFEE7:
        case 0xFEE8:
        case 0xFEE6:
        case 0xFEE5:
        case 0x06BE://34
        case 0xFBAC:
        case 0xFBAD:
        case 0xFBAB:
        case 0xFBAA:
        case 0x0648://35
        case 0xFEEE:
        case 0xFEED:
        case 0x06C7://36
        case 0xFBD8:
        case 0xFBD7:
        case 0x06C6://37
        case 0xFBDA:
        case 0xFBD9:
        case 0x06A0://38
        case 0x06A1://39
        case 0x06A2://40
        case 0x06A3://41
        case 0x06A5://42
        case 0x06A6://43
        case 0x06A7://44
        case 0x06A8://45
            switch(inp[i])
            {
            case 0x0626:
            case 0xFE89:
              KurdishIndex = 5;
              break;
            case 0x0627:
            case 0xFE8D:
            case 0xFE8E:
              KurdishIndex = 6;
              break;
            case 0x0628:
            case 0xFE91:
            case 0xFE92:
            case 0xFE90:
            case 0xFE8F:
              KurdishIndex = 7;
              break;
            case 0x062A:
            case 0xFE97:
            case 0xFE98:
            case 0xFE96:
            case 0xFE95:
              KurdishIndex = 8;
              break;
            case 0x06D5:
            case 0xFEEA:
            case 0xFEE9:
              KurdishIndex = 9;
              break;
            case 0x06AD:
            case 0xFBD5:
            case 0xFBD6:
            case 0xFBD4:
            case 0xFBD3:
              KurdishIndex = 10;
              break;
            case 0x06C8:
            case 0xFBDC:
            case 0xFBDB:
              KurdishIndex = 11;
              break;
            case 0x064A:
            case 0xFEF3:
            case 0xFEF4:
            case 0xFEF2:
            case 0xFEF1:
              KurdishIndex = 12;
              break;
            case 0x0643:
            case 0xFEDB:
            case 0xFEDC:
            case 0xFEDA:
            case 0xFED9:
              KurdishIndex = 13;
              break;
            case 0x06D0:
            case 0xFBE6:
            case 0xFBE7:
            case 0xFBE5:
            case 0xFBE4:
              KurdishIndex = 14;
              break;
            case 0x0686:
            case 0xFB7C:
            case 0xFB7D:
            case 0xFB7B:
            case 0xFB7A:
              KurdishIndex = 15;
              break;
            case 0x0649:
            case 0xFBE8:
            case 0xFBE9:
            case 0xFEF0:
            case 0xFEEF:
              KurdishIndex = 16;
              break;
            case 0x06CB:
            case 0xFBDF:
            case 0xFBDE:
              KurdishIndex = 17;
              break;
            case 0x067E:
            case 0xFB58:
            case 0xFB59:
            case 0xFB57:
            case 0xFB56:
              KurdishIndex = 18;
              break;
            case 0x062C:
            case 0xFE9F:
            case 0xFEA0:
            case 0xFE9E:
            case 0xFE9D:
              KurdishIndex = 19;
              break;
            case 0x062E:
            case 0xFEA7:
            case 0xFEA8:
            case 0xFEA6:
            case 0xFEA5:
              KurdishIndex = 20;
              break;
            case 0x062F:
            case 0xFEAA:
            case 0xFEA9:
              KurdishIndex = 21;
              break;
            case 0x0631:
            case 0xFEAE:
            case 0xFEAD:
              KurdishIndex = 22;
              break;
            case 0x0632:
            case 0xFEB0:
            case 0xFEAF:
              KurdishIndex = 23;
              break;
            case 0x0698:
            case 0xFB8B:
            case 0xFB8A:
              KurdishIndex = 24;
              break;
            case 0x0633:
            case 0xFEB3:
            case 0xFEB4:
            case 0xFEB2:
            case 0xFEB1:
              KurdishIndex = 25;
              break;
            case 0x0634:
            case 0xFEB7:
            case 0xFEB8:
            case 0xFEB6:
            case 0xFEB5:
              KurdishIndex = 26;
              break;
            case 0x063A:
            case 0xFECF:
            case 0xFED0:
            case 0xFECE:
            case 0xFECD:
              KurdishIndex = 27;
              break;
            case 0x0641:
            case 0xFED3:
            case 0xFED4:
            case 0xFED2:
            case 0xFED1:
              KurdishIndex = 28;
              break;
            case 0x0642:
            case 0xFED7:
            case 0xFED8:
            case 0xFED6:
            case 0xFED5:
              KurdishIndex = 29;
              break;
            case 0x06AF:
            case 0xFB94:
            case 0xFB95:
            case 0xFB93:
            case 0xFB92:
              KurdishIndex = 30;
              break;
            case 0x0644:
            case 0xFEDF:
            case 0xFEE0:
            case 0xFEDE:
            case 0xFEDD:
              KurdishIndex = 31;
              break;
            case 0x0645:
            case 0xFEE3:
            case 0xFEE4:
            case 0xFEE2:
            case 0xFEE1:
              KurdishIndex = 32;
              break;
            case 0x0646:
            case 0xFEE7:
            case 0xFEE8:
            case 0xFEE6:
            case 0xFEE5:
              KurdishIndex = 33;
              break;
            case 0x06BE:
            case 0xFBAC:
            case 0xFBAD:
            case 0xFBAB:
            case 0xFBAA:
              KurdishIndex = 34;
              break;
            case 0x0648:
            case 0xFEEE:
            case 0xFEED:
              KurdishIndex = 35;
              break;
            case 0x06C7:
            case 0xFBD8:
            case 0xFBD7:
              KurdishIndex = 36;
              break;
            case 0x06C6:
            case 0xFBDA:
            case 0xFBD9:
              KurdishIndex = 37;
              break;
            case 0x06A0:
              KurdishIndex = 38;
              break;
            case 0x06A1:
              KurdishIndex = 39;
              break;
            case 0x06A2:
              KurdishIndex = 40;
              break;
            case 0x06A3:
              KurdishIndex = 41;
              break;
            case 0x06A5:
              KurdishIndex = 42;
              break;
            case 0x06A6:
              KurdishIndex = 43;
              break;
            case 0x06A7:
              KurdishIndex = 44;
              break;
            case 0x06A8:
              KurdishIndex = 45;
              break;
            default:
              KurdishIndex = inp[i] - 0x06B5;
              break;
            }

            if (i == 0)
            {
                if ( CharAttribute[i+1] )
                {
                    if ( msAPI_OSD_IsFormNotConnect(inp[i+1]) && (inp[i+1] != 0x06D5))
                    {
                        if(inp[i] == 0x06BE)
                        {
                            if(msAPI_OSD_IsFormNotConnectForward(inp[i+1]))
                            {
                                inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                            }
                            else
                            {
                                inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                            }
                        }
                        else if((inp[i] >= 0x06A0) && (inp[i] <= 0x06A9))
                        {
                            inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                        }
                    }
                    else
                    {
                        //It is initial, do shape
                        inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                    }
                }
                else
                {
                    //It is isolated, do nothing
                    inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                }
            }
            else if (i == (len-1))
            {
                if ( CharAttribute[i-1] )
                {
                    if ( msAPI_OSD_IsFormNotConnect(inp[i-1]) )
                    {
                        inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                        if( (inp[i-1] == 0xFBBA) && (inp[i] == 0x06CE))
                        {
                            inp[i] = UnicodeArray[KurdishIndex][FINAL];
                        }
                        else if((inp[i] >= 0x06A0) && (inp[i] <= 0x06A9))
                        {
                            inp[i] = UnicodeArray[KurdishIndex][FINAL];
                        }
                    }
                    else
                    {
                        //It is final, do shape
                        inp[i] = UnicodeArray[KurdishIndex][FINAL];
                    }
                }
                else
                {
                    //It is isolated, do nothing
                    inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                }
            }
            else
            {
                bPrev = 0;
                bNext = 0;

                if ( CharAttribute[i-1] )
                {
                    //It has previous character
                    bPrev = 1;
                }
                if ( CharAttribute[i+1] )
                {
                    //It has next character
                    bNext = 1;
                }
                if ( ( bPrev ) && ( bNext ) )
                {
                    //It is medial, do shape
                    if( (inp[i] == 0x06d5) || (inp[i] == 0xfee9) )
                    {
                        inp[i] = UnicodeArray[KurdishIndex][FINAL];
                        if(msAPI_OSD_IsFormNotConnect(inp[i-1]))
                        {
                            inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                        }
                    }
                    else if( (inp[i] == 0xFBD7) || (inp[i] == 0xFEAD) || (inp[i] == 0x06C7) )
                    {
                        if(msAPI_OSD_IsFormNotConnectForward(inp[i+1]))
                        {
                            if(msAPI_OSD_IsFormNotConnect(inp[i-1]))
                            {
                                inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                            }
                            else
                                inp[i] = UnicodeArray[KurdishIndex][FINAL];
                        }
                        else
                        {
                            if(msAPI_OSD_IsFormNotConnect(inp[i-1]))
                            {
                                inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                            }
                            if( (inp[i+1] == 0xFEDF) || (inp[i+1] == 0xFB58) ) //not connect
                            {
                                inp[i] = UnicodeArray[KurdishIndex][FINAL];
                            }
                        }
                    }
                    else
                    {
                        if( (inp[i-1] == 0x06d5) || (inp[i-1] == 0xfeea) || (inp[i-1] == 0xfee9) )
                        {
                            if(msAPI_OSD_IsFormNotConnectForward(inp[i+1]) && (inp[i+1] != 0x06D5) && (inp[i] !=0xFEB3) &&
                                (inp[i] != 0xfee7) )
                            {
                                inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                            }
                            else
                            {
                                inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                            }
                        }
                        else
                        {
                            if(msAPI_OSD_IsFormNotConnect(inp[i-1]))
                            {
                                if(inp[i] == 0xFEED)//only isolate and final
                                {
                                    inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                                }
                                else if(inp[i] == 0xFEE5 && msAPI_OSD_IsArabicVowel(inp[i+1]))
                                {
                                    inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                                }
                                else if((inp[i] >= 0x06A0) && (inp[i] <= 0x06A9))
                                {
                                    inp[i] = UnicodeArray[KurdishIndex][MEDIAL];
                                }
                                else
                                    inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                            }
                            else
                            {
                                inp[i] = UnicodeArray[KurdishIndex][MEDIAL];
                            }
                        }
                    }
                }
                else if ( bPrev )
                {
                    //It is final, do shape
                    inp[i] = UnicodeArray[KurdishIndex][FINAL];
                    if(msAPI_OSD_IsFormNotConnect(inp[i-1]))
                    {
                        inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                    }
                    if( (inp[i-1] == 0x06d5) || (inp[i-1] == 0xfeea) || (inp[i-1] == 0xfee9) )
                    {
                        inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                    }
                }
                else if ( bNext )
                {
                    //It is initial, do shape
                    inp[i] = UnicodeArray[KurdishIndex][INITIAL];
                }
                else
                {
                    //It is isolated, do nothing
                    inp[i] = UnicodeArray[KurdishIndex][ISOLATE];
                }
            }
            break;

        default:
            break;
        }
    }
}
#endif

void msAPI_OSD_EnterDivxSubtitleMode(BOOLEAN bDivxSubtitle)
{
    bDivxSubtitleMode = bDivxSubtitle;
}

BOOLEAN msAPI_OSD_GetDivxSubtitleMode(void)
{
    return bDivxSubtitleMode;
}

#if (ENABLE_ARABIC_OSD)
/*
void msAPI_OSD_DisplayDivxSubtitleText(BOOLEAN bTextMode)
{
    bDivxSubtitleText = bTextMode;
}
*/

// for mixed language display usage in OSD language selection screen
void msAPI_OSD_SetHebrewLangMixedMode(BOOLEAN bHebrewMixed)
{
    bHebrewMixedMode = bHebrewMixed;
}

static void msAPI_OSD_UrduFilter(U16 *inp, U8 len)
{
    U8 i, j, bPrev, bNext, UrduIndex;
    U8 CharAttribute[STROSD];

	#define DOT_SIGN	0x60c //0x60C is dot sign

	#define URDU_ISOLATED   0
	#define URDU_INITIAL   	1
	#define URDU_MEDIAL   	2
	#define URDU_FINAL   	3
	#define URDU_MAX   	4

	#define URDU_CHAR_MAX   7
	#define URDU_PREV_NUM   31
	#define URDU_NEXT_NUM   2

	static const U16 Urdu_Previous_Block[] =
	{
		0x0627,	0x062F, 0x0648,	0x0631,
		0x0632,	0x0688, 0x0622,	0x0630,
		0x0691, 0xFB88, 0xFB89, 0xFB8C,
		0xFB8D, 0xFE81, 0xFE82, 0xFE8D,
		0xFE8E, 0xFEA9, 0xFEAA, 0xFEAB,
		0xFEAC, 0xFEAD, 0xFEAE, 0xFEAF,
		0xFEB0, 0xFEED, 0xFEEE, 0xFEF5,
		0xFEF6,	0xFEFB, 0xFEFC
	};

	static const U16 Urdu_Next_Block[] =
	{
		0x061F, 0x06D4
	};

	static const U16 Urdu_UnicodeArray[URDU_CHAR_MAX][4] =
	{
		//isolate  inital  medial  final
	//0x0679
		{  0xFB66, 0xFB68, 0xFB69, 0xFB67 },
	//0x0688
		{  0xFB88, 0xFB88, 0xFB89, 0xFB89 },
	//0x0691
		{  0xFB8C, 0xFB8C, 0xFB8D, 0xFB8D },
	//0x06BA
		{  0xFB9E, 0xFB9E, 0xFB9F, 0xFB9F },
	//0x06BE
		{  0xFBAA, 0xFBAC, 0xFBAD, 0xFBAB },
	//0x06C1
		{  0xFBA6, 0xFBA8, 0xFBA9, 0xFBA7 },
	//0x06D2
		{  0xFBAE, 0xFBAE, 0xFBAF, 0xFBAF }
	};

    for (i = 0; i < len; i++)
    {
        if (msAPI_OSD_IsNotInArabicHebrew(inp[i]) == PURE_ARABIC_CHAR && inp[i] != DOT_SIGN)
        {
            CharAttribute[i] = 1;
        }
        else
        {
            CharAttribute[i] = 0;
        }
    }

    for (i = 0; i < len; i++)
    {
        UrduIndex = URDU_CHAR_MAX;
		switch(inp[i])
		{
			case 0x0679:
				UrduIndex = 0;
				break;
			case 0x0688:
				UrduIndex = 1;
			break;
			case 0x0691:
				UrduIndex = 2;
			break;
			case 0x06BA:
				UrduIndex = 3;
			break;
			case 0x06BE:
				UrduIndex = 4;
			break;
			case 0x06C1:
				UrduIndex = 5;
			break;
			case 0x06D2:
				UrduIndex = 6;
			break;
			default:
				break;
		}


        if (UrduIndex < URDU_CHAR_MAX)
        {
            if (i > 0 && CharAttribute[i-1])
            {
                bPrev = 1;
            }
            else
            {
                bPrev = 0;
            }

            if (i < (len-1) && CharAttribute[i+1])
            {
                bNext = 1;
            }
            else
            {
                bNext = 0;
            }

            if (bPrev && bNext)
            {
                for (j = 0; j < URDU_PREV_NUM; j++)
                {
                    if (Urdu_Previous_Block[j] == inp[i-1])
                    {
                        inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_INITIAL];
                        break;
                    }
                }

                if (j == URDU_PREV_NUM)
                {
                    for (j = 0; j < URDU_NEXT_NUM; j++)
                    {
                        if (Urdu_Next_Block[j] == inp[i+1])
                        {
                            inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_FINAL];
                            break;
                        }
                    }

                    if (j == URDU_NEXT_NUM)
                    {
                        inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_MEDIAL];
                    }
                }
            }
            else if (bPrev)
            {
                for (j = 0; j < URDU_PREV_NUM; j++)
                {
                    if (Urdu_Previous_Block[j] == inp[i-1])
                    {
                        inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_ISOLATED];
                        break;
                    }
                }

                if (j == URDU_PREV_NUM)
                {
                    inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_FINAL];
                }
            }
            else if (bNext)
            {
                for (j = 0; j < URDU_NEXT_NUM; j++)
                {
                    if (Urdu_Next_Block[j] == inp[i+1])
                    {
                        inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_ISOLATED];
                        break;
                    }
                }

                if (j == URDU_NEXT_NUM)
                {
                    inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_INITIAL];
                }
            }
            else
            {
                inp[i] = Urdu_UnicodeArray[UrduIndex][URDU_ISOLATED];
            }
        }
    }
}

#endif

#if ( ENABLE_TTF_FONT )
void msAPI_OSD_SetTTFPalette(U32 tColor)
{
#if ( MONO_FONT )
//2 gray level font
    MS_U32 u32temp=0;

    u32temp = (tColor & 0x000000FF) >> 0;
    MApi_GFX_SetIntensity(1, (GFX_Buffer_Format)GFX_FMT_I8, (MS_U32*)&u32temp);
    u32temp = 0;
    MApi_GFX_SetIntensity(0, (GFX_Buffer_Format)GFX_FMT_I8, (MS_U32*)&u32temp);
#else
//256 gray level font
    int i;

    TTFPalette[0].RGB.u8A = 0x00;
    TTFPalette[0].RGB.u8R = 0xFF;
    TTFPalette[0].RGB.u8G = 0x00;
    TTFPalette[0].RGB.u8B = 0xFF;
    for(i=1;i<256;i++)
    {
        TTFPalette[i].RGB.u8A = i;
        TTFPalette[i].RGB.u8R = (tColor & 0x00FF0000) >> 16;
        TTFPalette[i].RGB.u8G = (tColor & 0x0000FF00) >> 8;
        TTFPalette[i].RGB.u8B = (tColor & 0x000000FF) >> 0;
    }
    MApi_GFX_SetPaletteOpt( TTFPalette, 0, 255);
#endif
}
#endif

/******************************************************************************/
/// API for draw text::
/// @param font_handle \b IN font handle
/// @param pu8Str \b IN pointer to string
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )

#if 1
static OSDStringType s_DrawText_OSDString_TempBuf; //OSDStringType TempBuf;
static OSDStringType s_DrawText_OSDString_OutBuf; //OSDStringTypeDouble outbuf;
#if ( ENABLE_ARABIC_OSD )
static OSDStringType s_DrawText_OSDString_Out; //OSDStringType out;
#endif
#else
static OSDStringType* s_pstOSDString_Temp = NULL; //OSDStringType TempBuf;
static OSDStringType* s_pstOSDString_OutBuf = NULL; //OSDStringTypeDouble outbuf;
#if ( ENABLE_ARABIC_OSD )
static OSDStringType* s_pstOSDString_Out = NULL; //OSDStringType out;
#endif
BOOLEAN msAPI_OSD_DrawText_AllocStrBuf(void)
{
    BOOLEAN bRtn = TRUE;

    if( s_pstOSDString_Temp == NULL )
    {
        s_pstOSDString_Temp = msAPI_Memory_Allocate(sizeof(OSDStringType), BUF_ID_DRAW_TEXT);
        if( s_pstOSDString_Temp == NULL )
        {
            bRtn = FALSE;
        }
    }

    if( s_pstOSDString_OutBuf == NULL )
    {
        s_pstOSDString_OutBuf = msAPI_Memory_Allocate(sizeof(OSDStringType), BUF_ID_DRAW_TEXT);
        if( s_pstOSDString_OutBuf == NULL )
        {
            bRtn = FALSE;
        }
    }

#if ( ENABLE_ARABIC_OSD )
    if( s_pstOSDString_Out == NULL )
    {
        s_pstOSDString_Out = msAPI_Memory_Allocate(sizeof(OSDStringType), BUF_ID_DRAW_TEXT);
        if( s_pstOSDString_Out == NULL )
        {
            bRtn = FALSE;
        }
    }
#endif

    return bRtn;
}

void msAPI_OSD_DrawText_FreeStrBuf(void)
{
    if( s_pstOSDString_Temp )
    {
        msAPI_Memory_Free(s_pstOSDString_Temp, BUF_ID_DRAW_TEXT);
        s_pstOSDString_Temp = NULL;
    }

    if( s_pstOSDString_OutBuf == NULL )
    {
        msAPI_Memory_Free(s_pstOSDString_OutBuf, BUF_ID_DRAW_TEXT);
        s_pstOSDString_OutBuf = NULL;
    }

#if ( ENABLE_ARABIC_OSD )
    if( s_pstOSDString_Out == NULL )
    {
        msAPI_Memory_Free(s_pstOSDString_Out, BUF_ID_DRAW_TEXT);
        s_pstOSDString_Out = NULL;
    }
#endif
}
#endif

#endif

void msAPI_OSD_DrawText(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn)
{
    U16 i, len, u16StrWidth;
    U16 scale;
    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    GFX_TextOutInfo text_info;
    OSDSRC_GLYPH_DISP_INFO *pGlyphDispInfo=NULL;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT) )
    #if ( ENABLE_ARABIC_OSD )
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
#endif

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT) )
    U16 nFontID;
#endif

     msAPI_OSD_GET_resource();

    /* check range */
    /*if((pclrBtn->x + pclrBtn->width) > NEWUI_MAIN_MENU_GWIN_WIDTH)
    {
        return;
    }
    else if((pclrBtn->y + pclrBtn->height) > NEWUI_MAIN_MENU_GWIN_HEIGHT)
    {
        return;
    }
    else*/ if((len = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        msAPI_OSD_Free_resource();
        return;
    }

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT) )

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
#if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
        case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                    msAPI_OSD_Set_H_Mirror(FALSE);
                    //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
                }
                else
            */
                {
                    if ( bHebrewMixedMode )
                    {
                        bHebrew = TRUE;
                    }
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                    {
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                    }

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                        msAPI_GE_SetMirror(1, 0);    //patch GE driver
                        msAPI_OSD_Set_H_Mirror(TRUE);
                        //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), TRUE);
                    }
                    else
                    {
                        msAPI_OSD_Set_H_Mirror(FALSE);
                        //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
                    }
                }
            }

            if ( bHebrew == FALSE )
            {
                bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                msAPI_GE_SetMirror(1, 0);    //patch GE driver
                msAPI_OSD_Set_H_Mirror(TRUE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), TRUE);
            }
            else
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
            }
            break;
#endif
#if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }
    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
                msAPI_OSD_Set_H_Mirror(FALSE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            }
            break;
#endif
        /*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            if ( bHebrew == FALSE )
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            }
            break;
        */

#if ( ENABLE_TTF_FONT )
        case LANGUAGE_OSD_HINDI:
        //case LANGUAGE_OSD_URDU:
        case LANGUAGE_OSD_BENGALI:
        case LANGUAGE_OSD_TELUGU:
        case LANGUAGE_OSD_MARATHI:
        case LANGUAGE_OSD_TAMIL:
        case LANGUAGE_OSD_MYANMAR:
        case LANGUAGE_OSD_KHMER:
        case LANGUAGE_OSD_LAO:
        case LANGUAGE_OSD_ASSAMESE:
        case LANGUAGE_OSD_GUJARATI:
        case LANGUAGE_OSD_KANNADA:
        case LANGUAGE_OSD_MALAYALAM:
        case LANGUAGE_OSD_PUNJABI:
            {
                Rect_t stRect_t;
                U32 RowHeight = 0;
                U32 nRows = 0;
                S32 nDrawY = pclrBtn->y;
                MLERet_t  eRet;
                U8 u8count = 0;

                pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
                if ( enLanguage == LANGUAGE_OSD_URDU )
                {
                    if ( bDivxSubtitleMode )
                    {
                        switch( pclrBtn->enTextAlign )
                        {
                            case EN_ALIGNMENT_RIGHT:
                                pclrBtn->enTextAlign = EN_ALIGNMENT_LEFT;
                                break;
                            case EN_ALIGNMENT_LEFT:
                                pclrBtn->enTextAlign = EN_ALIGNMENT_RIGHT;
                                break;
                            default:
                                break;
                        }

                        msAPI_OSD_Set_H_Mirror(FALSE);
                    }
                    else
                    {
                        msAPI_OSD_Set_H_Mirror(TRUE);
                    }
                }
                else
                    msAPI_OSD_Set_H_Mirror(FALSE);

                stRect_t.x = pclrBtn->x;
                stRect_t.y = pclrBtn->y;
                stRect_t.w = pclrBtn->width;
                stRect_t.h = pclrBtn->height;

                OSDTTF_TRACE(printf("%d %s %s, pclrBtn->t_clr=%x\n", __LINE__, __FUNCTION__, __FILE__, pclrBtn->t_clr));

                msAPI_OSD_SetTTFPalette(pclrBtn->t_clr);

                //We can decide font size from font ID, make a mapping table conversion here
                nFontID = FontHandleIndex[font_handle];

                OSDTTF_TRACE(printf("font_handle=%x, nFontID=%x, font_info[nFontID].output_size = %d\n", font_handle, nFontID, ttf_font_info[nFontID].output_size));

                u8count = 0;
                do
                {
                    //Get Font Height
                    if ( msAPI_OSD_MeasureTextY( ttf_font_info[nFontID].output_size, pclrBtn->height, &nDrawY, &nRows, &RowHeight, FALSE) == FALSE )
                    {
                        break;
                    }

                    nDrawY += pclrBtn->y;

                    eRet = msAPI_MLE_Display_DrawTextToBitmap(
                               ttf_font_info[nFontID].output_size,
                               (U16 *)((void *)pu8Str),
                               msAPI_OSD_u16Strlen((U16 *)((void *)pu8Str)),
                               pclrBtn->x,
                               nDrawY,
                               &stRect_t,
                               FONT_TYPE_NORMAL,
                               pclrBtn );

                    u8count++;
                    if ( u8count > 1 )
                        break;

                    if ( ( eRet == MLE_RET_OUT_OF_MEMORY ) || ( msAPI_MLE_GetMemoryNotEnoughFlag() == TRUE ) )
                    {
                        //reset font and cache system to release memory fragmentation
                        msAPI_MLE_FONTBASE_VectorFontReInit(msAPI_MLE_FONT_PL_GetFTBufferSize());
                        msAPI_MLE_SetMemoryNotEnoughFlag(FALSE);
                    }
                } while(eRet == MLE_RET_OUT_OF_MEMORY);
            }
            msAPI_OSD_Free_resource();
            return;

            break;
#endif

        default:
             pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            msAPI_OSD_Set_H_Mirror(FALSE);
            //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            break;
    }
#endif

#if (ENABLE_ARABIC_OSD)
    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }
#endif


#if 0//( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    if( FALSE == msAPI_OSD_DrawText_AllocStrBuf() )
    {
        return;
    }
#endif

    if(pclrBtn->bStringIndexWidth==CHAR_IDX_1BYTE)
    {
        if (len >= sizeof(TempStr.U8Str))
        {
            len = sizeof(TempStr.U8Str) - 1;
        }
    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            //memcpy(TempBuf.U8Str, pu8Str, len);
            memcpy(s_DrawText_OSDString_TempBuf.U8Str, pu8Str, len);
            for(i = 0; i < len; i++)
            {
                //TempStr.U8Str[i] = TempBuf.U8Str[(len-1)-i];
                TempStr.U8Str[i] = s_DrawText_OSDString_TempBuf.U8Str[(len-1)-i];
            }
        }
        else
   #endif
        {
            memcpy(TempStr.U8Str,pu8Str,len);
        }
        TempStr.U8Str[len] = 0;
    }
    else
    {
        if (len >= sizeof(TempStr.U8Str)/2)
        {
            len = sizeof(TempStr.U8Str)/2 - 1;
        }

    #if (!ENABLE_ARABIC_OSD)
        memcpy(TempStr.U8Str,pu8Str,len*2);
        //((U16 *)TempStr)[len] = 0;
        //TempStr[len*2] = TempStr[len*2+1] = 0;
        TempStr.U16Str[len] = 0;
    #else
        if ( bMirrorLang )
        {
            U8 bReverse = TRUE;

            memcpy(TempStr.U8Str,pu8Str,len*2);
            //((U16 *)TempStr)[len] = 0;
            TempStr.U16Str[len] = 0;

            //For Subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempStr.U16Str, len,
                        //outbuf.U16Str, STROSD,
                        s_DrawText_OSDString_OutBuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);

                //Every language is possible, you can't skip this filter here
                //msAPI_OSD_KurdishFilter(outbuf.U16Str, len);
                msAPI_OSD_KurdishFilter(s_DrawText_OSDString_OutBuf.U16Str, len);

                //msAPI_OSD_UrduFilter(outbuf.U16Str, len);
                msAPI_OSD_UrduFilter(s_DrawText_OSDString_OutBuf.U16Str, len);

                //msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, len);
                msAPI_OSD_ReverseAllCharacters(s_DrawText_OSDString_OutBuf.U16Str, s_DrawText_OSDString_Out.U16Str, len);

                //msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, TempStr.U16Str, len);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(s_DrawText_OSDString_Out.U16Str, TempStr.U16Str, len);

                bReverse = FALSE;
            }
            else if ( bArabicDisplay ) //for OSD
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempStr.U16Str, len,
                        //outbuf.U16Str, STROSD,
                        s_DrawText_OSDString_OutBuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);

                //just skip this function for non Kurdish condition
                if ( enLanguage == LANGUAGE_OSD_KURDISH )
                {
                    //msAPI_OSD_KurdishFilter(outbuf.U16Str, len);
                    msAPI_OSD_KurdishFilter(s_DrawText_OSDString_OutBuf.U16Str, len);
                }
                else if ( enLanguage == LANGUAGE_OSD_URDU )
                {
                    //msAPI_OSD_UrduFilter(outbuf.U16Str, len);
                    msAPI_OSD_UrduFilter(s_DrawText_OSDString_OutBuf.U16Str, len);
                }

                //msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, len);
                msAPI_OSD_ReverseAllCharacters(s_DrawText_OSDString_OutBuf.U16Str, s_DrawText_OSDString_Out.U16Str, len);

                //msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, len);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(s_DrawText_OSDString_Out.U16Str, s_DrawText_OSDString_OutBuf.U16Str, len);
            }
            else    // for Hebrew
            {

                if ( bDivxSubtitleMode )    // Divx subtitle
                {
                    //msAPI_OSD_ReverseAllCharacters(TempStr.U16Str, outbuf.U16Str, len);
                    msAPI_OSD_ReverseAllCharacters(TempStr.U16Str, s_DrawText_OSDString_OutBuf.U16Str, len);

                    //msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, len);
                    msAPI_OSD_ReverseNonArabicHebrewCharacters(s_DrawText_OSDString_OutBuf.U16Str, s_DrawText_OSDString_Out.U16Str, len);

                    //msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, len);
                    msAPI_OSD_ReverseAllCharacters(s_DrawText_OSDString_Out.U16Str, s_DrawText_OSDString_OutBuf.U16Str, len);
                }
                else if ( bHebrew )         // Hebrew OSD display
                {
                    //msAPI_OSD_ReverseAllCharacters(TempStr.U16Str, out.U16Str, len);
                    msAPI_OSD_ReverseAllCharacters(TempStr.U16Str, s_DrawText_OSDString_Out.U16Str, len);

                    //msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, len);
                    msAPI_OSD_ReverseNonArabicHebrewCharacters(s_DrawText_OSDString_Out.U16Str, s_DrawText_OSDString_OutBuf.U16Str, len);
                }
                else                        // Other conditions
                {
                    //msAPI_OSD_ReverseAllCharacters(TempStr.U16Str, outbuf.U16Str, len);
                    msAPI_OSD_ReverseAllCharacters(TempStr.U16Str, s_DrawText_OSDString_OutBuf.U16Str, len);

                    //msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, len);
                    msAPI_OSD_ReverseNonArabicHebrewCharacters(s_DrawText_OSDString_OutBuf.U16Str, s_DrawText_OSDString_Out.U16Str, len);

                    //msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, len);
                    msAPI_OSD_ReverseAllCharacters(s_DrawText_OSDString_Out.U16Str, s_DrawText_OSDString_OutBuf.U16Str, len);
                }
            }

            if ( bReverse )
            {
                for(i=0;i<len;i++)
                {
                    //TempStr.U16Str[i] = *(outbuf.U16Str+len-i-1);
                    TempStr.U16Str[i] = *(s_DrawText_OSDString_OutBuf.U16Str+len-i-1);
                }
            }
        }
        else
        {
            memcpy(TempStr.U8Str,pu8Str,len*2);
        }

        //((U16 *)TempStr)[len] = 0;
        TempStr.U16Str[len] = 0;
    #endif
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);

    scale = 100;

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = ((U16)pclrBtn->Fontfmt.height*100 / (U16)finfo.height);
        pclrBtn->Fontfmt.height = scale * finfo.height /100;

        scale = (U8)((U16)pclrBtn->Fontfmt.width*100 / (U16)finfo.width);
        pclrBtn->Fontfmt.width = scale * finfo.width /100;
    }

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_2BYTE)
        {
            //pu16Str = (U16 *)pu8Str;
            //temp solution for compiler warning
            //memcpy(TempBuf.U8Str, pu8Str, len*2);
            memcpy(s_DrawText_OSDString_TempBuf.U8Str, pu8Str, len*2);

            //len = Thai_compose(TempBuf.U16Str, 0, len, STROSD, outbuf.U16Str);
            len = Thai_compose(s_DrawText_OSDString_TempBuf.U16Str, 0, len, STROSD, s_DrawText_OSDString_OutBuf.U16Str);

            //outbuf.U16Str[len] = 0x0000;
            s_DrawText_OSDString_OutBuf.U16Str[len] = 0x0000;

            //pu8Str = outbuf.U8Str;
            pu8Str = s_DrawText_OSDString_OutBuf.U8Str;
        }
    }
#endif

    pGlyphDispInfo = msAPI_Memory_Allocate( sizeof(OSDSRC_GLYPH_DISP_INFO) * len,BUF_ID_GLYPH_DISP_INFO);
    if(pGlyphDispInfo == NULL)
    {
        __ASSERT(0);
        APIOSD_DBG(printf("E_DrawText>> pGlyphDispInfo == NULL\n"));
        msAPI_OSD_Free_resource();
        return;
    }

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
        {
            for (i=0; i<len; i++)
            {
            #if (ENABLE_ARABIC_OSD)
                if ( bMirrorLang )
                    msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, TempStr.U8Str[i], &pGlyphDispInfo[i]);
                else
            #endif
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu8Str[i], &pGlyphDispInfo[i]);
                pGlyphDispInfo[i].u8Width = pGlyphDispInfo[i].u8Width * scale / 100;
            }
        }
        else
        {
            U8 *pu8TempPtr;

#if (ENABLE_ARABIC_OSD)
            if ( bMirrorLang )
            {
                //pu16Str = (U16*) TempStr;
                pu8TempPtr = TempStr.U8Str;
            }
            else
#endif
            {
            //pu16Str = (U16*) pu8Str;
                pu8TempPtr = pu8Str;
            }
            for (i=0; i<len; i++)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, (pu8TempPtr[i*2+1]<<8) + pu8TempPtr[i*2], &pGlyphDispInfo[i]);
                pGlyphDispInfo[i].u8Width = (pGlyphDispInfo[i].u8Width * scale
#if ENABLE_DEFAULT_KERNING
                    //- kerningX_(pu16Str[i], pu16Str[i+1])
                    - kerningX_((pu8TempPtr[i*2+1]<<8) + pu8TempPtr[i*2], (pu8TempPtr[i*4+1]<<8) + pu8TempPtr[i*4])
#endif //ENABLE_DEFAULT_KERNING
                    ) / 100;
            }

        #if (ENABLE_ARABIC_OSD)
            //For Subtitle, if OSD is not mirrored status, go this way, the same with subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
            {
                U16 u16Unicode;

                for(i=0;i<len;i++)
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( i > 0 )
                    {
                        u16Unicode = (pu8TempPtr[i*2-1]<<8) + pu8TempPtr[i*2-2];
                        //if ( msAPI_OSD_IsArabicVowel( pu16Str[i-1] ) )
                        if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                        {
                            pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            u16StrWidth += (pGlyphDispInfo[i].u8Width + pclrBtn->Fontfmt.ifont_gap);
                        }
                    }
                    else
                    {
                        //coordinate no need change
                        u16StrWidth += (pGlyphDispInfo[i].u8Width + pclrBtn->Fontfmt.ifont_gap);
                    }
                }
            }
            else if ( bArabicDisplay ) //for OSD
            {
                U16 u16Unicode;

                for(i=0;i<len;i++)
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( i > 0 )
                    {
                        u16Unicode = (pu8TempPtr[i*2+1]<<8) + pu8TempPtr[i*2];
                        //if ( msAPI_OSD_IsArabicVowel( pu16Str[i] ) )
                        if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                        {
                            S8 nOffset = pGlyphDispInfo[i-1].u8Width - pGlyphDispInfo[i].u8Width;

                            if ( nOffset > 0 )
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = nOffset;
                            else
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                    }
                    else
                    {
                        //coordinate no need change
                    }
                }
            }
            else
        #endif
           {
           #if (ENABLE_THAI_OSD)
            if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
            {
                static U8 prevState = 0;
                U16 u16Unicode;

                prevState = 0;

                for(i=0;i<len;i++)
                {
                    // Check Primary Thai unicode range
                    u16Unicode = (pu8TempPtr[i*2+1]<<8) + pu8TempPtr[i*2];
                    if ( ( u16Unicode <= 0x0E5B ) && ( u16Unicode >= 0x0E01 ) )
                    {
                        if ( MinusDrawTable[ u16Unicode - 0x0E01 ] )
                        {
                            if ( i > 0 )
                            {
                                u16Unicode = (pu8TempPtr[i*2-1]<<8) + pu8TempPtr[i*2-2];
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ u16Unicode - 0x0E01 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ u16Unicode - 0xF700 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-1].u8X0 + pGlyphDispInfo[i-1].u8Width + 1) - (finfo.width);
                            }
                            else
                            {
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            //coordinate no need change
                        }

                        prevState = 1;
                    }
                    else if ( ( u16Unicode <= 0xF71A ) && ( u16Unicode >= 0xF700 ) )
                    {
                        if ( MinusDrawTablePersentation[ u16Unicode - 0xF700 ] )
                        {
                            if ( i > 0 )
                            {
                                u16Unicode = (pu8TempPtr[i*2-1]<<8) + pu8TempPtr[i*2-2];
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ u16Unicode - 0x0E01 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ u16Unicode - 0xF700 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-1].u8X0 + pGlyphDispInfo[i-1].u8Width + 1) - (finfo.width);
                            }
                            else
                            {
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            //coordinate no need change
                        }

                        prevState = 2;
                    }
                    else
                    {
                        //coordinate no need change
                        prevState = 0;
                    }
                }
            }
        #endif
            }
        }
    }
    else
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
        {
            for (i=0; i<len; i++)
            {
            #if (ENABLE_ARABIC_OSD)
                if ( bMirrorLang )
                    msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, TempStr.U8Str[i], &pGlyphDispInfo[i]);
                else
            #endif
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu8Str[i], &pGlyphDispInfo[i]);
                MS_DEBUG_MSG(printf("3 %x:%x\n", pu8Str[i], pGlyphDispInfo[i].u16Index));
            }
        }
        else
        {
            U8 *pu8TempPtr;

#if (ENABLE_ARABIC_OSD)
            if ( bMirrorLang )
            {
                //pu16Str = (U16*) TempStr;
                pu8TempPtr = TempStr.U8Str;
            }
            else
#endif
            {
            //pu16Str = (U16*) pu8Str;
                pu8TempPtr = pu8Str;
            }

            for (i=0; i<len; i++)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, (pu8TempPtr[i*2+1]<<8) + pu8TempPtr[i*2], &pGlyphDispInfo[i]);
                MS_DEBUG_MSG(printf("4 %x:%x\n", pu8Str[i], pGlyphDispInfo[i].u16Index));
            }
        }
    }

    u16StrWidth = 0;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        for (i=0; i< len; i++)
        {
            u16StrWidth += pGlyphDispInfo[i].u8Width;
        }

    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            u16StrWidth += ((len-1) * pclrBtn->Fontfmt.ifont_gap);
        }
    }
    else  // gap/compact + italic
    {
        // italic or default
        u16StrWidth = finfo.width * scale * len / 100;

        // with gap or compact, only one of two
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            u16StrWidth +=  ((len-1) * pclrBtn->Fontfmt.ifont_gap);
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            u16StrWidth -=  ((len-1) * pclrBtn->Fontfmt.dis);
        }
    }

    /* draw string */
    switch(pclrBtn->enTextAlign)
    {
        case EN_ALIGNMENT_DEFAULT: //without BTN_TEXT_GAP
            text_info.dstblk.x = pclrBtn->x;
            break;

        case EN_ALIGNMENT_LEFT:
            text_info.dstblk.x = pclrBtn->x + BTN_TEXT_GAP;
            break;

        case EN_ALIGNMENT_RIGHT:
            if (u16StrWidth + BTN_TEXT_GAP > pclrBtn->width)
                text_info.dstblk.x = pclrBtn->x;
            else
                text_info.dstblk.x = pclrBtn->x + pclrBtn->width - BTN_TEXT_GAP - u16StrWidth;
            break;

        case EN_ALIGNMENT_CENTER:
            if (u16StrWidth > pclrBtn->width)
                text_info.dstblk.x = pclrBtn->x;
            else
                text_info.dstblk.x = pclrBtn->x + (pclrBtn->width - u16StrWidth) / 2;
            break;
    }

    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height * scale / 100) / 2;
    }
    else
    {
        text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height) / 2;
    }
    if (text_info.dstblk.y > 32767)
    {
        //overflow
        text_info.dstblk.y = 0;
    }
    #if 0
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        S16 s16Tmp;
        s16Tmp = ((S16)pclrBtn->height - finfo.height * scale / 100) / 2;
        s16Tmp = pclrBtn->y + s16Tmp;
        if (s16Tmp < 0)
        {
            s16Tmp = 0;
        }
        cpoint.y = s16Tmp;
    }
    else
    {
        S16 s16Tmp;
        s16Tmp = ((S16)pclrBtn->height - finfo.height) / 2;
        s16Tmp = pclrBtn->y + s16Tmp;
        if (s16Tmp < 0)
        {
            s16Tmp = 0;
        }
        cpoint.y = s16Tmp;
    }
    #endif

//    memcpy(&cpoint.clr, &pclrBtn->t_clr, 4);

#if GE_DRIVER_TEST
    FontInfo.FontCoordinate.v0_x =  cpoint.x;
    FontInfo.FontCoordinate.v0_y =  cpoint.y;

    FontInfo.FontCoordinate.width = pclrBtn->Fontfmt.width;
    FontInfo.FontCoordinate.height = pclrBtn->Fontfmt.height;

    FontInfo.Font_SCK_Flag = GESCK_FLAG_SELE_TURNON | GESCK_FLAG_SELE_FOREGROUND;
    FontInfo.Font_Bitblt_Flag = GE_I1_FONT_BITBLT | GE_FONT_FLAG_VARWIDTH | GE_FONT_FLAG_GAP;
    FontInfo.BasicFontInfo.ifont_gap = 2;
    FontInfo.ARGBClr.ForeGroundColor.u32Num
    = (pclrBtn->t_clr&0xff00ff00) + ((pclrBtn->t_clr&0xff)<<16) +((pclrBtn->t_clr>>16)&0xff);
    //FontInfo.ARGBClr.ForeGroundColor.u32Num = (pclrBtn->t_clr&0xff00);

    FontInfo.ARGBClr.BackGroundColor.u32Num = 0;
    FontInfo.BasicFontInfo.fhandle = font_handle;
    FontInfo.Font_Type_Flag          = GEFONT_OSD_TYPE;
     #if 1
      MDrv_GE_FontBitBlt(&FontInfo, pGlyphDispInfo, TempStr.U8Str,pclrBtn->bStringIndexWidth);
     #else
    MDrv_GE_FontBitBlt(&FontInfo,fontAttr, pu8Str,pclrBtn->bStringIndexWidth);
     #endif
    PESet.PE_Enable_Flag = GE_PE_FLAG_DEFAULT;
    MDrv_GE_PixelEngine(&PESet);
#else
    if (pclrBtn->Fontfmt.flag&GEFONT_FLAG_BOLD)
    {
        pclrBtn->Fontfmt.flag |= GFXFONT_FLAG_BOLD;
    }

    text_info.dstblk.width = pclrBtn->width;
    text_info.dstblk.height = pclrBtn->height;
    text_info.flag = pclrBtn->Fontfmt.flag;
    memcpy(&text_info.color, &pclrBtn->t_clr, 4);
    text_info.pGlyphDispInfo = (GFX_GlyphDispInfo*)pGlyphDispInfo;
    text_info.gap = pclrBtn->Fontfmt.ifont_gap;

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && ( External Subtitle Language is Thai ))*/ )
    {
        MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
        MApi_GFX_TextOut(font_handle, pu8Str, pclrBtn->bStringIndexWidth+1, &text_info);
    }
    else
#endif
    {
        MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
        MApi_GFX_TextOut(font_handle, TempStr.U8Str, pclrBtn->bStringIndexWidth+1, &text_info);
    }
#endif

    if(pGlyphDispInfo != NULL)
    {
        MSAPI_MEMORY_FREE(pGlyphDispInfo,BUF_ID_GLYPH_DISP_INFO);
    }
    msAPI_GE_SetMirror(0, 0);    //patch GE driver

    msAPI_OSD_Free_resource();
}

#if ( ENABLE_TTF_FONT )
static BOOLEAN msAPI_OSD_DefaultMeasureLine( const U16 *pu16Text, U32 u32TextLen, U32 u32Width, U32 u32FontSize, U32 u32FontType, BOOLEAN bDiffDirChangeLine, U32 *pu32FitLen )
{
    Mle_TextUtil_BLTable_t sDefaultBLTable = { NULL, 0 };
    Mle_TextUtil_BL_t asDefaultBL[] = {{TEXT_WHITE_SPACE, 1}};

    OSDTTF_TRACE(printf("%d %s Enter\n", __LINE__, __FUNCTION__));
    //unused parameter
    bDiffDirChangeLine = bDiffDirChangeLine;

    if ( pu16Text == NULL || u32TextLen == 0 || pu32FitLen == NULL )
    {
        OSDTTF_TRACE(printf("%d %s Exit\n", __LINE__, __FUNCTION__));
        return FALSE;
    }

    //todo, How to implement LAYOUT_BREAKONWORD? default turn on LAYOUT_BREAKONWORD?
    ///if ( !(pThis->textLayout & LAYOUT_BREAKONWORD) )
    if ( 0 )
    {
        sDefaultBLTable.pBLTable = asDefaultBL;
        sDefaultBLTable.nBLTableSize = 1;
    }

    if ( msAPI_MLE_TEXTUTIL_MeasureTextToLineBreak(pu16Text, u32TextLen, u32Width, u32FontSize, u32FontType, TRUE, pu32FitLen, &sDefaultBLTable) )
    {
        //above have some logical doubt, Ref. Mantis ID:0119865
        //when input "enter""space""space", the Line-length will have error.
        //if ( *pu32FitLen < u32TextLen )
        //{
        //while ( (*pu32FitLen < u32TextLen) && (pu16Text[(*pu32FitLen)] == TEXT_WHITE_SPACE) )
        //{
        //(*pu32FitLen)++;
        //}
        //}
    }
    else
    {
        *pu32FitLen = msAPI_MLE_TEXTUTIL_BidiGetParagraphLength( pu16Text, u32TextLen );
    }

    OSDTTF_TRACE(printf("%d %s Exit\n", __LINE__, __FUNCTION__));
    return TRUE;
}

static BOOLEAN msAPI_OSD_CreateMultiLineTable( U32 u32FontSize, U16 *pu16Str, U32 u32StrLen, U32 u32Width )
{
    Text_MeasureInf_t sLineMeasure;
    MLE_WChar *pwstr = NULL;
//    U32 u32StrLen = 0;

    //Fix me, go this way?
    //if ( FONT_IS_SUPPORT_MULTI_LINE(sFontInfo.nTag) )
    //{
    //todo
        //RELEASEIF( pThis->pITextTable, (IBase *)pThis );
    //}
    //else
    //{
        //Free old table and create new
        //if ( pThis->pITextTable )
        //{
            //return TRUE;
        //}
        //RELEASEIF( pThis->pITextTable, (IBase *)pThis );
    //}

    pwstr = (MLE_WChar *)pu16Str;

    if( NULL == pwstr || 0 == u32StrLen )
        return FALSE;

    OSDTTF_TRACE(printf("%d %s\n", __LINE__, __FUNCTION__));
    ///sLineMeasure.tFontData.nFontCate = FONT_CAT_VECTOR;
    sLineMeasure.tFontData.nFontType = FONT_TYPE_NORMAL;
    sLineMeasure.tFontData.nFontSize = u32FontSize;

    //Always go this way
    //if ( pThis->textLayout & LAYOUT_MULTILINE )
    {
        if ( u32Width == 0 )
        {
            OSDTTF_TRACE(printf("%d %s\n", __LINE__, __FUNCTION__));
            sLineMeasure.nWidth = (U32)(-1); //max width
        }
        else
        {
            OSDTTF_TRACE(printf("%d %s\n", __LINE__, __FUNCTION__));
            sLineMeasure.nWidth = u32Width;
        }
        sLineMeasure.bDiffDirChangeLine = TRUE;
        sLineMeasure.pfnMeasureLine = msAPI_OSD_DefaultMeasureLine;
        ///sLineMeasure.nFunctionData = (U32)pThis;
    }
    //else
    //{
        //sLineMeasure.nWidth = (U32)(-1);  //max width
        //sLineMeasure.bDiffDirChangeLine = FALSE;
        //sLineMeasure.pfnMeasureLine = NULL;
        //sLineMeasure.nFunctionData = 0;
    //}

    OSDTTF_TRACE(printf("%d %s\n", __LINE__, __FUNCTION__));
    //Fix me, Currently we always set bWithoutBidi to FALSE, think about later
    ///pThis->pITextTable = msAPI_MLE_TextCreateLineTable(pwstr, u32StrLen, TRUE,  pThis->bWithoutBidi, &sLineMeasure );
    pMleTextTable = msAPI_MLE_TextCreateLineTable(pwstr, u32StrLen, TRUE,  FALSE, &sLineMeasure );

    return TRUE;
}
#endif

void msAPI_OSD_SetPunctuatedStringS1S2EndingType(BOOLEAN bEnable)
{
    bEndingTypeNone = bEnable;
}

BOOLEAN msAPI_OSD_GetPunctuatedStringS1S2EndingType(void)
{
    return bEndingTypeNone;
}

/******************************************************************************/
/// API for draw Punctuated text::
/// @param font_handle \b IN font handle
/// @param pu16Str \b IN pointer to string
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/// @param max_row_num \b IN max row count
/******************************************************************************/
void msAPI_OSD_DrawPunctuatedString(FONTHANDLE font_handle, U16 *pu16Str, OSDClrBtn *pclrBtn, U8 max_row_num)
{

    S8 gap;
    U8 scale, i, offset_len, cut_strlen;
    U16 total_strlen, width, u16Char;
    U16 max_width, buf_y;
    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    //For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    BOOLEAN bGetLastSpaceinSingleLine;
    U8 u8LastSpaceIndex;
    U16 u16LastSpace_Width;
    U8 bExceed = FALSE;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringTypeDouble outbuf;
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
    #if ( ENABLE_ARABIC_OSD )
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
        U16 CharIndex;
    #endif
#endif
#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT) )
    U16 nFontID;
#endif

    FONTHANDLE Org_font_handle = font_handle;

    /*prevent error*/
    if (pclrBtn->bStringIndexWidth != CHAR_IDX_2BYTE)
    {
        APIOSD_DBG(printf("Only support 2 bytes strubg\n"));
        return;
    }

    //For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    if (max_row_num == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> max_row_num = 0\n"));
        return;
    }
    else if ((total_strlen = msAPI_OSD_GetStrLength((U8*)pu16Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> strlen = 0\n"));
        return;
    }


    msAPI_OSD_GET_resource();


    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
    scale = 1;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)((U16)pclrBtn->Fontfmt.height / (U16)finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)((U16)pclrBtn->Fontfmt.width / (U16)finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }

    if (total_strlen >= sizeof(TempStr.U8Str)/2)
    {
        total_strlen = sizeof(TempStr.U8Str)/2 - 1;
    }

 #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT) )

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
#if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
        case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( bHebrewMixedMode )
                        bHebrew = TRUE;
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                    }
                }
            }

            for(CharIndex=0;CharIndex<total_strlen;CharIndex++)
            {
                if ( msAPI_OSD_IsNotInArabicHebrew(pu16Str[CharIndex]) == PURE_ARABIC_CHAR )
                    break;
            }
            if ( CharIndex == total_strlen )
            {
                bHebrew = FALSE;
                bArabicDisplay = FALSE;
                if ( bHebrew == FALSE )
                    pclrBtn->Fontfmt.ifont_gap = 0;
            }
            else
            {
                if ( bHebrew == FALSE )
                    bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;

            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
            }
            break;
#endif
#if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;

            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }

    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
            }
            break;
#endif
        /*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            break;
        */

#if ( ENABLE_TTF_FONT )

        case LANGUAGE_OSD_HINDI:
        //case LANGUAGE_OSD_URDU:
        case LANGUAGE_OSD_BENGALI:
        case LANGUAGE_OSD_TELUGU:
        case LANGUAGE_OSD_MARATHI:
        case LANGUAGE_OSD_TAMIL:
        case LANGUAGE_OSD_MYANMAR:
        case LANGUAGE_OSD_KHMER:
        case LANGUAGE_OSD_LAO:
        case LANGUAGE_OSD_ASSAMESE:
        case LANGUAGE_OSD_GUJARATI:
        case LANGUAGE_OSD_KANNADA:
        case LANGUAGE_OSD_MALAYALAM:
        case LANGUAGE_OSD_PUNJABI:
        {
            Rect_t stRect_t;
            BOOLEAN bIsLastDisplayLine = FALSE;
            U16 *pu16DisplayString = NULL;
            MLERet_t  eRet1 = MLE_RET_SUCCESS, eRet2 = MLE_RET_SUCCESS;
            U8 u8count = 0;
            U16 *pu16NewStr = NULL;

            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            if ( enLanguage == LANGUAGE_OSD_URDU )
            {
                if ( bDivxSubtitleMode )
                {
                    switch( pclrBtn->enTextAlign )
                    {
                        case EN_ALIGNMENT_RIGHT:
                            pclrBtn->enTextAlign = EN_ALIGNMENT_LEFT;
                            break;
                        case EN_ALIGNMENT_LEFT:
                            pclrBtn->enTextAlign = EN_ALIGNMENT_RIGHT;
                            break;
                        default:
                            break;
                    }

                    msAPI_OSD_Set_H_Mirror(FALSE);
                }
                else
                {
                    msAPI_OSD_Set_H_Mirror(TRUE);
                }
            }
            else
                msAPI_OSD_Set_H_Mirror(FALSE);

            stRect_t.x = pclrBtn->x;
            stRect_t.y = pclrBtn->y;
            stRect_t.w = pclrBtn->width;
            stRect_t.h = pclrBtn->height;

            OSDTTF_TRACE(printf("%d %s %s, pclrBtn->t_clr=%x\n", __LINE__, __FUNCTION__, __FILE__, pclrBtn->t_clr));

            msAPI_OSD_SetTTFPalette(pclrBtn->t_clr);

            OSDTTF_TRACE(printf("%d draw ", __LINE__));
            OSDTTF_TRACE(for(i=0;i<msAPI_OSD_u16Strlen(pu16Str);i++))
            OSDTTF_TRACE({)
                OSDTTF_TRACE(printf("%04X ", pu16Str[i]));
            OSDTTF_TRACE(})
            OSDTTF_TRACE(printf("\n"));

            //We can decide font size from font ID, make a mapping table conversion here
            nFontID = FontHandleIndex[font_handle];

            OSDTTF_TRACE(printf("font_handle=%x, nFontID=%x, font_info[nFontID].output_size = %d\n", font_handle, nFontID, ttf_font_info[nFontID].output_size));

            pu16NewStr = (U16 *)msAPI_Memory_Allocate(total_strlen*sizeof(U16)+1, BUF_ID_DRAW_TEXT);
            if ( pu16NewStr == NULL )
            {
                msAPI_OSD_Free_resource();
                return;
            }

            //filter SI/EPG control code
            for(i=0;i<total_strlen;i++)
            {
                if ( ( pu16Str[i] >= 0x0080 ) && ( pu16Str[i] != 0x008A ) && ( pu16Str[i] <= 0x009F ) )
                {
                    pu16NewStr[i] = 0x0020;
                }
                else
                {
                    pu16NewStr[i] = pu16Str[i];
                }
            }

            pu16Str = pu16NewStr;

            u8count = 0;
            do
            {
                {
                    U16 *pw = NULL;
                    U32 RowHeight = 0;
                    U32 nRows = 0, row;
                    U32 u32EllWidth = 0;
                    U32 nFits = 0;
                    U32 nPixcel = 0;
                    S32 nDrawX,nDrawY = pclrBtn->y;
                    BOOLEAN bIsRTLLang = FALSE;
                    BOOLEAN bIsRTLStr = FALSE;
                    BOOLEAN bFontMirror = FALSE;
                    BOOLEAN bMultiLine = TRUE;
                    EN_STRING_ENDING_TYPE eEndingDot = EN_STRING_ENDING_2_DOT;

                    if ( max_row_num > 1 )
                    {
                        if ( msAPI_OSD_CreateMultiLineTable( ttf_font_info[nFontID].output_size, pu16Str, total_strlen, stRect_t.w) == FALSE )
                        {
                            break;
                        }
                        bMultiLine = TRUE;
                    }
                    else
                    {
                        bMultiLine = FALSE;
                    }
                    OSDTTF_TRACE(printf("%d %s\n", __LINE__, __FUNCTION__));
                    //Get Font Height
                    if ( msAPI_OSD_MeasureTextY( ttf_font_info[nFontID].output_size, pclrBtn->height, &nDrawY, &nRows, &RowHeight, bMultiLine) == FALSE )
                    {
                        OSDTTF_TRACE(printf("%d %s\n", __LINE__, __FUNCTION__));
                        break;
                    }

                    nDrawY += stRect_t.y;

                    if ( nRows > max_row_num )
                    {
                        nRows = max_row_num;
                    }

                    //This is for old API compatibility
                    if ( msAPI_OSD_GetPunctuatedStringS1S2EndingType() == TRUE )
                    {
                        eEndingDot = EN_STRING_ENDING_NONE;
                    }

                    for(row = 1; row <= nRows; row++)
                    {
                        if(row == nRows)
                            bIsLastDisplayLine = TRUE;

                        if ( pu16DisplayString != NULL )
                        {
                            FREE( pu16DisplayString );
                            pu16DisplayString = NULL;
                        }

                        if ( (msAPI_OSD_MeasureLineX( ttf_font_info[nFontID].output_size,
                                                      pu16Str,
                                                      total_strlen,
                                                      (row - 1),
                                                      pclrBtn,
                                                      &bIsRTLLang,
                                                      &pu16DisplayString,
                                                      &nFits,
                                                      &nPixcel,
                                                      &nDrawX,
                                                      &u32EllWidth,
                                                      &bIsRTLStr,
                                                      eEndingDot,
                                                      bIsLastDisplayLine )) == FALSE )
                        {
                            OSDTTF_TRACE(printf("%d break\n", __LINE__));
                            break;
                        }

                        OSDTTF_TRACE(printf("%d bIsRTLLang=%d pu16Str=%X pu16Temp=%X nFits=%d nPixcel=%d nDrawX=%d u32EllWidth=%d bIsRTLStr=%d\n", __LINE__, bIsRTLLang, (U32)pu16Str, (U32)pu16DisplayString, nFits, nPixcel, nDrawX, u32EllWidth, bIsRTLStr));


                        pw = pu16DisplayString;
                        if ( pw == NULL )
                        {
                            continue;
                        }

                        // ignore white space at first if RTF
                        if ( bIsRTLStr && u32EllWidth == 0 /*&& nDrawX >= 0*/ )
                        {
                            while ( nFits > 1 && ((*pw == TEXT_WHITE_SPACE) || MLETEXTUTIL_IsReturnChar(*pw)) )
                            {
                                pw = (U16 *)(pw + 1);
                                nFits = nFits - 1;
                            }
                        }

                        if(nDrawY + (S32)RowHeight < stRect_t.y)
                        {
                            nDrawY += RowHeight;
                            nFits = 0;
                            if ( nDrawY + (S32)RowHeight >= stRect_t.y + stRect_t.h )
                            {
                                bIsLastDisplayLine = TRUE;
                            }
                            continue;
                        }
                        else if(nDrawY>stRect_t.y+stRect_t.h)
                        {
                            break;
                        }

                        nDrawX += stRect_t.x;

                        bFontMirror = ( bIsRTLLang ) && ( !bDivxSubtitleMode );

                        if( u32EllWidth )
                        {
                            if ( bIsRTLLang )
                            {
                                OSDTTF_TRACE(printf("%d\n", __LINE__));
                                if ( bFontMirror )
                                    msAPI_GE_SetMirror(1, 0);    //patch GE driver
                                eRet1 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX, nDrawY, pw, nFits, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                                eRet2 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX - u32EllWidth, nDrawY, COMMON_ELLIPSIS_STRING, eEndingDot, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                                if ( bFontMirror )
                                    msAPI_GE_SetMirror(0, 0);    //patch GE driver
                            }
                            else
                            {
                                OSDTTF_TRACE(printf("%d\n", __LINE__));
                                if ( bFontMirror )
                                    msAPI_GE_SetMirror(1, 0);    //patch GE driver
                                eRet1 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX, nDrawY, pw, nFits, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                                eRet2 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX+nPixcel, nDrawY, COMMON_ELLIPSIS_STRING, eEndingDot, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                                if ( bFontMirror )
                                    msAPI_GE_SetMirror(0, 0);    //patch GE driver
                            }
                        }
                        else
                        {
                            OSDTTF_TRACE(printf("%d pw=%X nFits=%d, nDrawX=%d nDrawY=%d stRect_t.w=%d\n", __LINE__, (U32)pw, nFits, nDrawX, nDrawY, stRect_t.w));
                            //eRet1 = msAPI_MLE_Display_DrawTextToBitmap(ttf_font_info[nFontID].output_size, pw, (S32)nFits, nDrawX, nDrawY, &stRect_t, FONT_TYPE_NORMAL, NULL, 0);
                            if ( bFontMirror )
                                msAPI_GE_SetMirror(1, 0);    //patch GE driver
                            eRet1 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX, nDrawY, pw, nFits, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                            if ( bFontMirror )
                                msAPI_GE_SetMirror(0, 0);    //patch GE driver

                            if(row != nRows) //not the last line
                            {
                                nDrawY += RowHeight;
                                nFits = 0;
                            }
                        }

                        if ( nDrawY + (S32)RowHeight >= stRect_t.y + stRect_t.h )
                        {
                            bIsLastDisplayLine = TRUE;
                        }

                    }

                    if ( pu16DisplayString != NULL )
                    {
                        FREE( pu16DisplayString );
                        pu16DisplayString = NULL;
                    }
                }

                msAPI_MLE_TextTableRelease( pMleTextTable );
                pMleTextTable = NULL;

                u8count++;
                if ( u8count > 1 )
                    break;

                if ( ( eRet1 == MLE_RET_OUT_OF_MEMORY ) || ( eRet2 == MLE_RET_OUT_OF_MEMORY ) || ( msAPI_MLE_GetMemoryNotEnoughFlag() == TRUE ) )
                {
                    //printf("%d reset eRet1=%x eRet2=%x flag=%x\n", __LINE__, eRet1, eRet2, msAPI_MLE_GetMemoryNotEnoughFlag());
                    //reset font and cache system to release memory fragmentation
                    msAPI_MLE_FONTBASE_VectorFontReInit(msAPI_MLE_FONT_PL_GetFTBufferSize());
                    msAPI_MLE_SetMemoryNotEnoughFlag(FALSE);
                }

                if ( pu16DisplayString != NULL )
                {
                    FREEIF( pu16DisplayString );
                    pu16DisplayString = NULL;
                }

            } while( ( eRet1 == MLE_RET_OUT_OF_MEMORY ) || ( eRet2 == MLE_RET_OUT_OF_MEMORY ) );

            if ( pu16DisplayString != NULL )
            {
                FREEIF( pu16DisplayString );
                pu16DisplayString = NULL;
            }

            if ( pu16NewStr != NULL )
            {
                msAPI_Memory_Free(pu16NewStr, BUF_ID_DRAW_TEXT);
            }
        }

        msAPI_OSD_Free_resource();
        return;

        break;
#endif

        default:
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            break;
    }
#endif


#if (ENABLE_ARABIC_OSD)

    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }
#endif

#if (ENABLE_ARABIC_OSD)

    if ( bMirrorLang )
    {
        //For Subtitle
        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
        {
            S32 errorCode = U_ZERO_ERROR;

            ArabicParser(pu16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);
            //Every language is possible, you can't skip this filter here
            msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
            msAPI_OSD_UrduFilter(outbuf.U16Str, total_strlen);
        }
        else if ( bArabicDisplay ) //for OSD
        {
             S32 errorCode = U_ZERO_ERROR;

            ArabicParser(pu16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);
            //just skip this function for non Kurdish condition
            if ( enLanguage == LANGUAGE_OSD_KURDISH )
            {
                msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
            }
            else if ( enLanguage == LANGUAGE_OSD_URDU )
            {
                msAPI_OSD_UrduFilter(outbuf.U16Str, total_strlen);
            }
        }
        else    // for Hebrew
        {
            memcpy(outbuf.U8Str, (U8 *)pu16Str, total_strlen*2);
        }

        outbuf.U16Str[total_strlen] = 0;

        pu16Str = outbuf.U16Str;
    }
    else
#endif

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        //pu16Str = (U16 *)pu8Str;

        total_strlen = Thai_compose(pu16Str, 0, total_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[total_strlen] = 0x0000;

        pu16Str = outbuf.U16Str;
    }
    else
#endif
    {
        //memcpy(outbuf.U8Str,(U8 *)pu16Str,total_strlen*2);

        //outbuf.U16Str[total_strlen] = 0;

        //pu16Str = outbuf.U16Str;
    }

    gap = 0;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
    }
    else
    {
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            gap = -pclrBtn->Fontfmt.dis;
        }
    }

    offset_len = 1; //2;
    buf_y = pclrBtn->y;
    max_width = pclrBtn->width - 2*BTN_TEXT_GAP;

    for (i=0; i<max_row_num && total_strlen; i++)
    {
        width = 0;
        cut_strlen = 0;
        bGetLastSpaceinSingleLine=FALSE;//Reset variable
        u8LastSpaceIndex = 0;//Reset variable
        u16LastSpace_Width = 0; //Reset variable
        bExceed = FALSE;

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            while (width<max_width && cut_strlen<total_strlen)
            {
            #if (ENABLE_ARABIC_OSD)
                //For Subtitle
                if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {
                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen-1] ) )
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen-1], &BBox_X_Info);
                            width -= (BBox_X_Info.u8Width*scale + gap);
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                        width += (BBox_X_Info.u8Width*scale + gap);
                    }
                }
                else if ( bArabicDisplay ) //for OSD
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {
                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen] ) )
                        {
                                //skip current vowel character width
                                //do nothing here
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                        width += (BBox_X_Info.u8Width*scale + gap);
                    }
                }
                else
            #endif
            #if (ENABLE_THAI_OSD)
                if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
                {
                    // Check Primary Thai unicode range
                    if ( ( pu16Str[cut_strlen] <= 0x0E5B ) && ( pu16Str[cut_strlen] >= 0x0E01 ) )
                    {
                        if ( MinusDrawTable[ pu16Str[cut_strlen] - 0x0E01 ] )
                        {
                            //Minus coordinate, don't add width
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else if ( ( pu16Str[cut_strlen] <= 0xF71A ) && ( pu16Str[cut_strlen] >= 0xF700 ) )
                    {
                        if ( MinusDrawTablePersentation[ pu16Str[cut_strlen] - 0xF700 ] )
                        {
                            //Minus coordinate, don't add width
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                        width += (BBox_X_Info.u8Width*scale + gap);
                    }
                }
                else
            #endif
                {
                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                    width += (BBox_X_Info.u8Width*scale + gap);
                }

                cut_strlen++;

                if ((pu16Str[(cut_strlen-1)]==0x20)||((pu16Str[(cut_strlen-1)]>=0x80)&&(pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                    bGetLastSpaceinSingleLine = TRUE;

                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }
        else
        {
            while(width<max_width && cut_strlen<total_strlen)
            {
                cut_strlen++;
                width += (finfo.width + gap);
                if ((pu16Str[(cut_strlen-1)]==0x20)||((pu16Str[(cut_strlen-1)]>=0x80)&&(pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                    bGetLastSpaceinSingleLine = TRUE;

                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }

        if (width >= max_width)
        {
            //cut_strlen--;
            bExceed = TRUE;
        }
#if 0   // Display long string as possible; Sync from DMKIM
        //Set new cut string length to last Space index
        if (bGetLastSpaceinSingleLine&&u8LastSpaceIndex&&(total_strlen > cut_strlen))
        {
            #if (Very_Long_Word_Case==1)
            if ( u16LastSpace_Width>((U16)(max_width/2)) )
            #endif
        {
               //if (i < max_row_num-1)
            cut_strlen = u8LastSpaceIndex;
        }
        }
        //Set new cut string length to last Space index
#endif

        APIOSD_DBG(printf("DrawSmartText>> cut_strlen = %bu\n", cut_strlen));

        if (cut_strlen == 0)
        {
            break;
        }
        else
        {
            if (bExceed && i == max_row_num-1)
            {
                //pu16Str[cut_strlen-1] = 0x01; // ...
                pu16Str[cut_strlen-2] = CHAR_DOT; // .
                pu16Str[cut_strlen-1] = CHAR_DOT; // .
            }
            u16Char = pu16Str[cut_strlen];
            pu16Str[cut_strlen] = 0;
            msAPI_OSD_DrawText(Org_font_handle, (U8*)pu16Str, pclrBtn);
            pu16Str[cut_strlen] = u16Char;

            total_strlen -= cut_strlen;
            pu16Str += (cut_strlen*offset_len);
        }
        pclrBtn->y += pclrBtn->height;
    }

    pclrBtn->y = buf_y;

    msAPI_OSD_Free_resource();

}


/******************************************************************************/
/// API for estimate height of Punctuated text::
/// @param font_handle \b IN font handle
/// @param pu16Str \b IN pointer to string
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/// @param max_row_num \b IN max row count
/// @param pu8rows \b OUT row count
/// @param pu16height \b OUT height (pixels)
/******************************************************************************/
void msAPI_OSD_GetPunctuatedStringHeight(FONTHANDLE font_handle, U16 *pu16Str, OSDClrBtn *pclrBtn, U8 max_row_num,
    U8 * pu8rows, U16 * pu16height)
{

    S8 gap;
    U8 scale, i, offset_len, cut_strlen;
    U16 total_strlen, width; //, u16Char;
    U16 max_width, buf_y;
    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    //For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    BOOLEAN bGetLastSpaceinSingleLine;
    U8 u8LastSpaceIndex;
    U16 u16LastSpace_Width;
    U8 bExceed = FALSE;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || ENABLE_TTF_FONT )
    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
        OSDStringTypeDouble outbuf;
    #endif
    #if ( ENABLE_THAI_OSD )
    U8 bThaiDisplay = FALSE;
    #endif
       U16 nFontID;
    #if ( ENABLE_ARABIC_OSD )
    U8 bMirrorLang = FALSE;
    U8 bArabicDisplay = FALSE;
    U8 bHebrew = FALSE;
    U16 CharIndex;
    #endif
#endif

    *pu8rows = 0;
    *pu16height = 0;

    /*prevent error*/
    if (pclrBtn->bStringIndexWidth != CHAR_IDX_2BYTE)
    {
        APIOSD_DBG(printf("Only support 2 bytes strubg\n"));
        return;
    }

    /*/For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    if (max_row_num == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> max_row_num = 0\n"));
        return;
    }
    else*/ if ((total_strlen = msAPI_OSD_GetStrLength((U8*)pu16Str, CHAR_IDX_2BYTE/*pclrBtn->bStringIndexWidth*/)) == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> strlen = 0\n"));
        return;
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);

    scale = 1;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)((U16)pclrBtn->Fontfmt.height / (U16)finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)((U16)pclrBtn->Fontfmt.width / (U16)finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }

    if (total_strlen >= sizeof(TempStr.U8Str)/2)
    {
        total_strlen = sizeof(TempStr.U8Str)/2 - 1;
    }

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT) )

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
    #if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
        case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;

            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( bHebrewMixedMode )
                        bHebrew = TRUE;
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                    }
                }
            }

            for(CharIndex=0;CharIndex<total_strlen;CharIndex++)
            {
                if ( msAPI_OSD_IsNotInArabicHebrew(pu16Str[CharIndex]) == PURE_ARABIC_CHAR )
                    break;
            }
            if ( CharIndex == total_strlen )
            {
                bHebrew = FALSE;
                bArabicDisplay = FALSE;
                if ( bHebrew == FALSE )
                    pclrBtn->Fontfmt.ifont_gap = 0;
            }
            else
            {
                if ( bHebrew == FALSE )
                    bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
            }
            break;
    #endif
    #if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }
    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
            }
            break;
    #endif
    /*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            break;
    */

#if ( ENABLE_TTF_FONT )

        case LANGUAGE_OSD_HINDI:
        //case LANGUAGE_OSD_URDU:
        case LANGUAGE_OSD_BENGALI:
        case LANGUAGE_OSD_TELUGU:
        case LANGUAGE_OSD_MARATHI:
        case LANGUAGE_OSD_TAMIL:
        case LANGUAGE_OSD_MYANMAR:
        case LANGUAGE_OSD_KHMER:
        case LANGUAGE_OSD_LAO:
        case LANGUAGE_OSD_ASSAMESE:
        case LANGUAGE_OSD_GUJARATI:
        case LANGUAGE_OSD_KANNADA:
        case LANGUAGE_OSD_MALAYALAM:
        case LANGUAGE_OSD_PUNJABI:
        {
            Rect_t stRect_t;
            MLERet_t  eRet1 = MLE_RET_SUCCESS, eRet2 = MLE_RET_SUCCESS;
            U8 u8count = 0;
            U16 *pu16NewStr = NULL;

            stRect_t.x = pclrBtn->x;
            stRect_t.y = pclrBtn->y;
            stRect_t.w = pclrBtn->width;
            stRect_t.h = pclrBtn->height;


            OSDTTF_TRACE(printf("%d draw ", __LINE__));
            OSDTTF_TRACE(for(i=0;i<msAPI_OSD_u16Strlen(pu16Str);i++))
            OSDTTF_TRACE({)
                OSDTTF_TRACE(printf("%04X ", pu16Str[i]));
            OSDTTF_TRACE(})
            OSDTTF_TRACE(printf("\n"));

            //We can decide font size from font ID, make a mapping table conversion here
            nFontID = FontHandleIndex[font_handle];

            OSDTTF_TRACE(printf("font_handle=%x, nFontID=%x, font_info[nFontID].output_size = %d\n", font_handle, nFontID, ttf_font_info[nFontID].output_size));

            pu16NewStr = (U16 *)msAPI_Memory_Allocate(total_strlen*sizeof(U16)+1, BUF_ID_DRAW_TEXT);
            if ( pu16NewStr == NULL )
            {
                return;
            }

            //filter SI/EPG control code
            for(i=0;i<total_strlen;i++)
            {
                if ( ( pu16Str[i] >= 0x0080 ) && ( pu16Str[i] != 0x008A ) && ( pu16Str[i] <= 0x009F ) )
                {
                    pu16NewStr[i] = 0x0020;
                }
                else
                {
                    pu16NewStr[i] = pu16Str[i];
                }
            }

            pu16Str = pu16NewStr;

            u8count = 0;
            do
            {
                {
                    U32 RowHeight = 0;
                    U32 nRows = 0;
                    S32 nDrawY = pclrBtn->y;
                    BOOLEAN bMultiLine = TRUE;

                    if ( max_row_num > 1 )
                    {
                        if ( msAPI_OSD_CreateMultiLineTable( ttf_font_info[nFontID].output_size, pu16Str, total_strlen, stRect_t.w) == FALSE )
                        {
                            break;
                        }
                        bMultiLine = TRUE;
                    }
                    else
                    {
                        bMultiLine = FALSE;
                    }

                    //Get Font Height
                    if ( msAPI_OSD_MeasureTextY( ttf_font_info[nFontID].output_size, pclrBtn->height, &nDrawY, &nRows, &RowHeight, bMultiLine) == FALSE )
                    {
                        OSDTTF_TRACE(printf("%d %s\n", __LINE__, __FUNCTION__));
                        break;
                    }

                    OSDTTF_TRACE(printf("DrawY=%d stRect_t.y=%d, total=%d stRect.h=%d\n", nDrawY, stRect_t.y, (nDrawY + stRect_t.y), stRect_t.h));

                    *(pu8rows) = nRows;
                    *(pu16height) = RowHeight*nRows;
                }

                msAPI_MLE_TextTableRelease( pMleTextTable );
                pMleTextTable = NULL;

                u8count++;
                if ( u8count > 1 )
                    break;

                if ( ( eRet1 == MLE_RET_OUT_OF_MEMORY ) || ( eRet2 == MLE_RET_OUT_OF_MEMORY ) || ( msAPI_MLE_GetMemoryNotEnoughFlag() == TRUE ) )
                {
                    //printf("%d reset eRet1=%x eRet2=%x flag=%x\n", __LINE__, eRet1, eRet2, msAPI_MLE_GetMemoryNotEnoughFlag());
                    //reset font and cache system to release memory fragmentation
                    msAPI_MLE_FONTBASE_VectorFontReInit(msAPI_MLE_FONT_PL_GetFTBufferSize());
                    msAPI_MLE_SetMemoryNotEnoughFlag(FALSE);
                }

            } while( ( eRet1 == MLE_RET_OUT_OF_MEMORY ) || ( eRet2 == MLE_RET_OUT_OF_MEMORY ) );

            if ( pu16NewStr != NULL )
            {
                msAPI_Memory_Free(pu16NewStr, BUF_ID_DRAW_TEXT);
            }
        }

        return;

        break;
#endif

        default:
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            break;
    }
#endif

#if (ENABLE_ARABIC_OSD)
    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }
#endif

#if (ENABLE_ARABIC_OSD)

    if ( bMirrorLang )
    {
        //For Subtitle
        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
        {
            S32 errorCode = U_ZERO_ERROR;

            ArabicParser(pu16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);
            //Every language is possible, you can't skip this filter here
            msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
            msAPI_OSD_UrduFilter(outbuf.U16Str, total_strlen);
        }
        else if ( bArabicDisplay ) //for OSD
        {
             S32 errorCode = U_ZERO_ERROR;

            ArabicParser(pu16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);
            //just skip this function for non Kurdish condition
            if ( enLanguage == LANGUAGE_OSD_KURDISH )
            {
                msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
            }
            else if ( enLanguage == LANGUAGE_OSD_URDU )
            {
                msAPI_OSD_UrduFilter(outbuf.U16Str, total_strlen);
            }
        }
        else    // for Hebrew
        {
            memcpy(outbuf.U8Str, (U8 *)pu16Str, total_strlen*2);
        }

        outbuf.U16Str[total_strlen] = 0;

        pu16Str = outbuf.U16Str;
    }
    else
#endif

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        //pu16Str = (U16 *)pu8Str;

        total_strlen = Thai_compose(pu16Str, 0, total_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[total_strlen] = 0x0000;

        pu16Str = outbuf.U16Str;
    }
    else
#endif
    {
    //memcpy(outbuf.U8Str,(U8 *)pu16Str,total_strlen*2);

    //outbuf.U16Str[total_strlen] = 0;

    //pu16Str = outbuf.U16Str;
    }

    gap = 0;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
    }
    else
    {
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            gap = -pclrBtn->Fontfmt.dis;
        }
    }

    offset_len = 1; //2;
    buf_y = pclrBtn->y;
    max_width = pclrBtn->width - 2*BTN_TEXT_GAP;

    for (i=0; i<max_row_num && total_strlen; i++)
    {
        width = 0;
        cut_strlen = 0;
        bGetLastSpaceinSingleLine=FALSE;//Reset variable
        u8LastSpaceIndex = 0;//Reset variable
        u16LastSpace_Width = 0; //Reset variable
        bExceed = FALSE;

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            while (width<max_width && cut_strlen<total_strlen)
            {
            #if (ENABLE_ARABIC_OSD)
                //For Subtitle
                if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {
                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen-1] ) )
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen-1], &BBox_X_Info);
                            width -= (BBox_X_Info.u8Width*scale + gap);
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                        width += (BBox_X_Info.u8Width*scale + gap);
                    }
                }
                else if ( bArabicDisplay ) //for OSD
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {
                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen] ) )
                        {
                                //skip current vowel character width
                                //do nothing here
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                        width += (BBox_X_Info.u8Width*scale + gap);
                    }
                }
                else
            #endif
            #if (ENABLE_THAI_OSD)
                if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
                {
                    // Check Primary Thai unicode range
                    if ( ( pu16Str[cut_strlen] <= 0x0E5B ) && ( pu16Str[cut_strlen] >= 0x0E01 ) )
                    {
                        if ( MinusDrawTable[ pu16Str[cut_strlen] - 0x0E01 ] )
                        {
                            //Minus coordinate, don't add width
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else if ( ( pu16Str[cut_strlen] <= 0xF71A ) && ( pu16Str[cut_strlen] >= 0xF700 ) )
                    {
                        if ( MinusDrawTablePersentation[ pu16Str[cut_strlen] - 0xF700 ] )
                        {
                            //Minus coordinate, don't add width
                        }
                        else
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                            width += (BBox_X_Info.u8Width*scale + gap);
                        }
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                        width += (BBox_X_Info.u8Width*scale + gap);
                    }
                }
                else
            #endif
                {
                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                    width += (BBox_X_Info.u8Width*scale + gap);
                }

                cut_strlen++;

                if ((pu16Str[(cut_strlen-1)]==0x20)||((pu16Str[(cut_strlen-1)]>=0x80)&&(pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                    bGetLastSpaceinSingleLine = TRUE;

                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }
        else
        {
            while(width<max_width && cut_strlen<total_strlen)
            {
                cut_strlen++;
                width += (finfo.width + gap);
                if ((pu16Str[(cut_strlen-1)]==0x20)||((pu16Str[(cut_strlen-1)]>=0x80)&&(pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                    bGetLastSpaceinSingleLine = TRUE;

                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }

        if (width >= max_width)
        {
            //cut_strlen--;
            bExceed = TRUE;
        }
#if 0   // Display long string as possible; Sync from DMKIM
        //Set new cut string length to last Space index
        if (bGetLastSpaceinSingleLine&&u8LastSpaceIndex&&(total_strlen > cut_strlen))
        {
            #if (Very_Long_Word_Case==1)
            if ( u16LastSpace_Width>((U16)(max_width/2)) )
            #endif
            {
               //if (i < max_row_num-1)
               cut_strlen = u8LastSpaceIndex;
            }
        }
        //Set new cut string length to last Space index
#endif

        APIOSD_DBG(printf("DrawSmartText>> cut_strlen = %bu\n", cut_strlen));

        if (cut_strlen == 0)
        {
            break;
        }
        else
        {
            /*
            if (bExceed && i == max_row_num-1)
            {
                //pu16Str[cut_strlen-1] = 0x01; // ...
                pu16Str[cut_strlen-2] = CHAR_DOT; // .
                pu16Str[cut_strlen-1] = CHAR_DOT; // .
            }
            u16Char = pu16Str[cut_strlen];
            pu16Str[cut_strlen] = 0;
            msAPI_OSD_DrawText(Org_font_handle, (U8*)pu16Str, pclrBtn);
            pu16Str[cut_strlen] = u16Char;
            */

            *(pu8rows) += 1;
            *(pu16height) += pclrBtn->height;

            total_strlen -= cut_strlen;
            pu16Str += (cut_strlen*offset_len);
        }
        pclrBtn->y += pclrBtn->height;
    }

    pclrBtn->y = buf_y;
}


#if 0
/******************************************************************************/
void msAPI_OSD_DrawPunctuatedString_S1(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num)
{
    S8 gap;
    S16 i;
    U8 scale, offset_len;
    U16 cut_strlen, u16LastSpaceIndex;
    U16 total_strlen, strlen, width, bytes_num, total_width;
    U16 max_width, buf_y;
    U8 *pStr;
    U16 *pu16Str;
    FONT_INFO finfo;
    GFX_GlyphBbox_X BBox_X_Info;
//For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    BOOLEAN bGetLastSpaceinSingleLine;
    U16 u16LastSpace_Width;
//For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
       BOOLEAN bIsEmphasis =false;
       BOOLEAN bControlCode0x86 = false;
       BOOLEAN bControlCode0x87 = false;
       BOOLEAN bControlCodeSHY = false;
       BOOLEAN bControlCodeSHY_NewLine = false;
       BOOLEAN bLastSHY = false;
    BOOLEAN bControlCodeSHY_With_NewLine = false;
      // BOOLEAN bNewLine= true;

       U16 u16OrignalxPosition = pclrBtn->x;
       U16 u16OrignalFontfmtFlag = pclrBtn ->Fontfmt.flag;
       U8 pSHYStr[2];
    U32 _timer = 0;
       pSHYStr[0]=0x2d;
       pSHYStr[1]=0;




    _timer = msAPI_Timer_GetTime0();

    if(max_row_num == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> max_row_num = 0\n"));
        return;
    }
    else if ((total_strlen = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> strlen = 0\n"));
        return;
    }

    msAPI_OSD_GET_resource();

        strlen = total_strlen;
    MDrv_GE_GetFontInfo(font_handle, &finfo);
    scale = 1;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)((U16)pclrBtn->Fontfmt.height / (U16)finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)((U16)pclrBtn->Fontfmt.width / (U16)finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }

    gap = 0;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
    }
    else
    {
        if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
              else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            gap = -pclrBtn->Fontfmt.dis;
        }
    }

    if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
    {
        offset_len = 1;
    }
    else
    {
        offset_len = 2;
    }

    buf_y = pclrBtn->y;

    max_width = pclrBtn->width - 2*BTN_TEXT_GAP;
       //width=0;
       total_width =0;
    for(i=0; i<max_row_num && total_strlen; i++)
    {

        width = 0;

        cut_strlen = 0;
        bGetLastSpaceinSingleLine=FALSE;//Reset variable
        u16LastSpaceIndex = 0;//Reset variable
        u16LastSpace_Width = 0; //Reset variable
        bControlCodeSHY_NewLine = false;
        bControlCodeSHY_With_NewLine = false;
        if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
            {
                while(total_width<max_width && cut_strlen<total_strlen)
                {
                    MDrv_GE_GetBBox_X(font_handle, pu8Str[cut_strlen++], &BBox_X_Info);
                    width += (BBox_X_Info.u8Width*scale + gap);
                    total_width += (BBox_X_Info.u8Width*scale + gap);
                    if ((pu8Str[(cut_strlen-1)]==0x20)||((pu8Str[(cut_strlen-1)]>=0x80)&&(pu8Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                    {
                        u16LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                        u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                        bGetLastSpaceinSingleLine = TRUE;

                        if ( pu8Str[(cut_strlen-1)]==0x8A )
                        {
                            pu8Str[(cut_strlen-1)]=0x20;
                            break;
                        }
                        else if ( pu8Str[(cut_strlen-1)]==0x86 )
                        {

                            bIsEmphasis =true;
                            bControlCode0x86 =true;
                            break;
                        }
                        else if ( pu8Str[(cut_strlen-1)]==0x87 )
                        {

                            bControlCode0x87 = true;

                            break;
                        }
                        else
                        {
                            pu8Str[(cut_strlen-1)]=0x20;
                        }
                    }
                }
            }
            else //(pclrBtn->bStringIndexWidth == CHAR_IDX_2BYTE)
            {
                pu16Str = (U16*)pu8Str;

                        if (i==1)
                            u16NextLineStartInx = (strlen -total_strlen);
                        //printf("i = %bu \n", i);
                        //printf("total_strlen = %u \n", total_strlen);
                        //printf("u16NextLineStartInx= %u \n", u16NextLineStartInx);
                while(total_width<max_width && cut_strlen<total_strlen)
                {

                    MDrv_GE_GetBBox_X(font_handle, pu16Str[cut_strlen++], &BBox_X_Info);
                    width += (BBox_X_Info.u8Width*scale + gap);

                    total_width+=(BBox_X_Info.u8Width*scale + gap);
                    // printf("max_width =%u, total_width = %u,  pu16Str[%bu]= %x \n",max_width,total_width,cut_strlen,pu16Str[cut_strlen]);


                    if (total_width>=max_width &&  bLastSHY)
                    {

                        bControlCodeSHY_NewLine =true;

                        bLastSHY = false;
                        //bControlCodeSHY = true;
                    }

                    if ((pu16Str[(cut_strlen-1)]==0x0020)||(pu16Str[(cut_strlen-1)]==0x00AD)||((pu16Str[(cut_strlen-1)]>=0xE080)&&(pu16Str[(cut_strlen-1)]<=0xE09F)) )//if Space Char or Control code
                    {
                        u16LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.

                        u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                        bGetLastSpaceinSingleLine = TRUE;

                        if ( pu16Str[(cut_strlen-1)]==0xE08A )
                        {
                            pu16Str[(cut_strlen-1)]=0x0020;

                            break;
                        }
                        else if ( pu16Str[(cut_strlen-1)]==0xE086 )
                        {

                            bControlCode0x86 =true;

                            break;
                        }
                        else if ( pu16Str[(cut_strlen-1)]==0xE087 )
                        {

                            bControlCode0x87 = true;

                            break;
                        }
                        else if (pu16Str[(cut_strlen-1)]==0x00AD)
                        {
                            bControlCodeSHY = true;


                            break;
                         }
                        else
                        {
                            pu16Str[(cut_strlen-1)]=0x0020;
                        }
                    }
                }
            }
        }
        else
        {
            while(total_width<max_width && cut_strlen<total_strlen)
            {
                cut_strlen++;
                width += (finfo.width + gap);
                total_width += (finfo.width + gap);
                if ((pu8Str[(cut_strlen-1)]==0x20)||((pu8Str[(cut_strlen-1)]>=0x80)&&(pu8Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    u16LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                    bGetLastSpaceinSingleLine = TRUE;

                    if ( pu8Str[(cut_strlen-1)]==0x8A )
                    {
                        pu8Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                        pu8Str[(cut_strlen-1)]=0x20;
                }
            }
        }

        if(width > max_width)
        {
            //if (!bControlCodeSHY_NewLine)
                cut_strlen--;
        }

        //Set new cut string length to last Space index
        if (bGetLastSpaceinSingleLine&&u16LastSpaceIndex&&(total_strlen > cut_strlen))
        {
            cut_strlen = u16LastSpaceIndex;
        }
        //Set new cut string length to last Space index

        APIOSD_DBG(printf("DrawSmartText>> cut_strlen = %bu\n", cut_strlen));

        if(cut_strlen == 0)
        {
            break;
        }
        else
        {
            bytes_num = (cut_strlen+1) * offset_len;
            pStr = msAPI_Memory_Allocate(bytes_num,BUF_ID_DRAW_TEXT);
            if(pStr)
            {
                memcpy(pStr, pu8Str, bytes_num);

                if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
                {
                    pStr[cut_strlen] = 0;
                }
                else
                {

                                   ((U16*)pStr)[cut_strlen]=0;
                                    if (bControlCodeSHY)
                                        ((U16*)pStr)[cut_strlen-1]=0x0020;
                }
                            if (bControlCode0x87)
                            {

                                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_BOLD;
                            }
                            if (bControlCodeSHY_NewLine)
                            {

                                pclrBtn ->bStringIndexWidth = CHAR_IDX_1BYTE;
                                msAPI_OSD_DrawText(font_handle, pSHYStr, pclrBtn);
                                bControlCodeSHY_With_NewLine = bControlCodeSHY;
                                 bControlCodeSHY = false;
                                 pclrBtn->y += pclrBtn->height;
                                 pclrBtn ->x = u16OrignalxPosition;
                                 bLastSHY=false;
                                pclrBtn ->bStringIndexWidth = CHAR_IDX_2BYTE;

                            }

                            if( i != max_row_num-1 ||  !bControlCodeSHY_NewLine )
                    msAPI_OSD_DrawText(font_handle, pStr, pclrBtn);
                else
                    bControlCodeSHY_With_NewLine = false;
                msAPI_Memory_Free(pStr,BUF_ID_DRAW_TEXT);
            }

            total_strlen -= cut_strlen;
            pu8Str += (cut_strlen*offset_len);
        }

        if (bControlCode0x86)
              {
                    bControlCode0x86 = false;
                    bIsEmphasis =true;
                    pclrBtn->x += u16LastSpace_Width;
                     bLastSHY=false;
                     i--; // no need to increase max_row_num
              }
              else if ( bControlCode0x87)
              {

                    bControlCode0x87 = false;
                    bIsEmphasis =false;
                    //pclrBtn->t_clr = 0x003C3C3C;
                    pclrBtn->Fontfmt.flag = u16OrignalFontfmtFlag;
                    pclrBtn->x += u16LastSpace_Width;
                    bLastSHY=false;
                    i--; // no need to increase max_row_num
              }
              else if (bControlCodeSHY)
              {
                    if (bControlCodeSHY_NewLine)
                    {
                        bControlCodeSHY_NewLine =false;
                        bControlCodeSHY = false;
                         bLastSHY=false;
                    }
                    else
                    {

                         bControlCodeSHY = false;
                         bLastSHY=true;
                        //pclrBtn ->x = u16OrignalxPosition;
                        MDrv_GE_GetBBox_X(font_handle, 0x00AD, &BBox_X_Info);
                        pclrBtn->x += u16LastSpace_Width;
                  pclrBtn->x -=(BBox_X_Info.u8Width*scale + gap);
                        if(total_width > (BBox_X_Info.u8Width*scale + gap))
                            total_width-=(BBox_X_Info.u8Width*scale + gap);
                        else
                            total_width=0;
                        i--;
                     }

               }
              else
              {
                   if (!bControlCodeSHY_NewLine)
                    {
                        pclrBtn->y += pclrBtn->height;
                        pclrBtn ->x = u16OrignalxPosition;
                        total_width=0;
                        bLastSHY=false;
                        //width=0;
                    }
            else if(bControlCodeSHY_With_NewLine)
            {
                bControlCodeSHY_NewLine = bControlCodeSHY_With_NewLine = false;
                MDrv_GE_GetBBox_X(font_handle, 0x0020, &BBox_X_Info);
                pclrBtn->x += width;
                if(pclrBtn->x >= (BBox_X_Info.u8Width*scale + gap))
                {
                    pclrBtn->x -=(BBox_X_Info.u8Width*scale + gap);
                    if(pclrBtn->x < u16OrignalxPosition)
                        pclrBtn ->x = u16OrignalxPosition;
                }
                else
                    pclrBtn ->x = u16OrignalxPosition;
                total_width = width;
                if(total_width > (BBox_X_Info.u8Width*scale + gap))
                    total_width-=(BBox_X_Info.u8Width*scale + gap);
                else
                    total_width=0;
            }
                   else
                    {
                        bControlCodeSHY_NewLine=false;
                        pclrBtn->x +=width;
                        total_width = width;
                    }
              }
              if(total_strlen)
                bStopScrollDown =false;
              else
                bStopScrollDown =true;

    }

    pclrBtn->y = buf_y;

    msAPI_OSD_Free_resource();
    printf ("Time = %lu\n", _timer = msAPI_Timer_DiffTimeFromNow(_timer));

}

#else
//BOOLEAN g_EpgTest;

extern U8 u8Scroll_BaseLine;
extern U8 u8Scroll_TotalCount;


/******************************************************************************/
/// API for draw 2 Bytes text::
/// @param font_handle \b IN font handle
/// @param pu8Str \b IN pointer to string
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_Draw2BytesText(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn)
{
    U16 i, len, u16StrWidth;
    U16 scale;
    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    GFX_TextOutInfo text_info;

    OSDSRC_GLYPH_DISP_INFO *pGlyphDispInfo=NULL;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringType TempBuf;
    OSDStringTypeDouble outbuf;
    #if ( ENABLE_ARABIC_OSD )
        OSDStringType out;
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
    U16 nFontID;
#endif

     msAPI_OSD_GET_resource();

    /* check range */
    /*if((pclrBtn->x + pclrBtn->width) > NEWUI_MAIN_MENU_GWIN_WIDTH)
    {
        return;
    }
    else if((pclrBtn->y + pclrBtn->height) > NEWUI_MAIN_MENU_GWIN_HEIGHT)
    {
        return;
    }
    else*/ if((len = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        msAPI_OSD_Free_resource();
        return;
    }

#if 0
    if(pclrBtn->bStringIndexWidth==CHAR_IDX_1BYTE)
    {
        if (len >= sizeof(TempStr.U8Str))
        {
            len = sizeof(TempStr.U8Str) - 1;
        }
        memcpy(TempStr.U8Str,pu8Str,len);
        TempStr.U8Str[len] = 0;

    }
    else
    {
        if (len >= sizeof(TempStr.U8Str)/2)
        {
            len = sizeof(TempStr.U8Str)/2 - 1;
        }
        memcpy(TempStr.U8Str,pu8Str,len*2);
        ((U16 *)TempStr.U8Str)[len] = 0;
    }
#else
#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
#if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
        case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
/*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                    msAPI_OSD_Set_H_Mirror(FALSE);
                    //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
                }
                else
*/
                {
                    if ( bHebrewMixedMode )
                    {
                        bHebrew = TRUE;
                    }
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                    {
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                    }

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                        msAPI_GE_SetMirror(1, 0);    //patch GE driver
                        msAPI_OSD_Set_H_Mirror(TRUE);
                        //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), TRUE);
                    }
                    else
                    {
                        msAPI_OSD_Set_H_Mirror(FALSE);
                        //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
                    }
                }
            }

            if ( bHebrew == FALSE )
            {
                bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                msAPI_GE_SetMirror(1, 0);    //patch GE driver
                msAPI_OSD_Set_H_Mirror(TRUE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), TRUE);
            }
            else
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
            }
            break;
#endif
#if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
/*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
*/
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }

    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
                msAPI_OSD_Set_H_Mirror(FALSE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            }
            break;
#endif
/*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            if ( bHebrew == FALSE )
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            }
            break;
*/
        default:
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            msAPI_OSD_Set_H_Mirror(FALSE);
            //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            break;
    }
#endif

#if (ENABLE_ARABIC_OSD)

    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }
#endif

    if(pclrBtn->bStringIndexWidth==CHAR_IDX_2BYTE)
    {
#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
        if (len >= sizeof(TempBuf.U8Str)/2)
        {
            len = sizeof(TempBuf.U8Str)/2 - 1;
        }
#endif
#if (!ENABLE_ARABIC_OSD)
//        memcpy(TempBuf.U8Str,pu8Str,len*2);
//      TempBuf.U16Str[len] = 0;
#else
        if ( bMirrorLang )
        {
            U8 bReverse = TRUE;

            memcpy(TempBuf.U8Str,pu8Str,len*2);
            TempBuf.U16Str[len] = 0;

            //For Subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, len, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //Every language is possible, you can't skip this filter here
                msAPI_OSD_KurdishFilter(outbuf.U16Str, len);
                msAPI_OSD_UrduFilter(outbuf.U16Str, len);
                msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, len);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, TempBuf.U16Str, len);
                bReverse = FALSE;
            }
            else if ( bArabicDisplay ) //for OSD
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, len, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //just skip this function for non Kurdish condition
                if ( enLanguage == LANGUAGE_OSD_KURDISH )
                {
                    msAPI_OSD_KurdishFilter(outbuf.U16Str, len);
                }
                else if ( enLanguage == LANGUAGE_OSD_URDU )
                {
                    msAPI_OSD_UrduFilter(outbuf.U16Str, len);
                }
                msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, len);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, len);
            }
            else    // for Hebrew
            {

                if ( bDivxSubtitleMode )    // Divx subtitle
                {
                    msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, outbuf.U16Str, len);
                    msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, len);
                    msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, len);
                }
                else if ( bHebrew )         // Hebrew OSD display
                {
                    msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, out.U16Str, len);
                    msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, len);
                }
                else                        // Other conditions
                {
                    msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, outbuf.U16Str, len);
                    msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, len);
                    msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, len);
                }
            }

            if ( bReverse )
            {
                for(i=0;i<len;i++)
                {
                    TempBuf.U16Str[i] = *(outbuf.U16Str+len-i-1);
                }
            }
        }
        else
        {
            memcpy(TempBuf.U8Str,pu8Str,len*2);
        }

        TempBuf.U16Str[len] = 0;
#endif
     }

#endif
    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);

    scale = 100;

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = ((U16)pclrBtn->Fontfmt.height*100 / (U16)finfo.height);
        pclrBtn->Fontfmt.height = scale * finfo.height /100;

        scale = (U8)((U16)pclrBtn->Fontfmt.width*100 / (U16)finfo.width);
        pclrBtn->Fontfmt.width = scale * finfo.width /100;
    }

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_2BYTE)
        {
            //pu16Str = (U16 *)pu8Str;
            //temp solution for compiler warning
            memcpy(TempBuf.U8Str, pu8Str, len*2);

            len = Thai_compose(TempBuf.U16Str, 0, len, STROSD, outbuf.U16Str);
            outbuf.U16Str[len] = 0x0000;

            pu8Str = outbuf.U8Str;
        }
    }
#endif

    pGlyphDispInfo = msAPI_Memory_Allocate( sizeof(OSDSRC_GLYPH_DISP_INFO) * len,BUF_ID_GLYPH_DISP_INFO);
    if(pGlyphDispInfo == NULL)
    {
        __ASSERT(0);
        APIOSD_DBG(printf("E_DrawText>> pGlyphDispInfo == NULL\n"));
        msAPI_OSD_Free_resource();
        return;
    }

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
        {
            for (i=0; i<len; i++)
            {
            #if (ENABLE_ARABIC_OSD)
                if ( bMirrorLang )
                    msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, TempBuf.U8Str[i], &pGlyphDispInfo[i]);
                else
            #endif
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu8Str[i], &pGlyphDispInfo[i]);
                pGlyphDispInfo[i].u8Width = pGlyphDispInfo[i].u8Width * scale / 100;
            }
        }
        else
        {
            U8 *pu8TempPtr;

#if (ENABLE_ARABIC_OSD)
            if ( bMirrorLang )
            {
                pu8TempPtr = TempBuf.U8Str;
            }
            else
#endif
            {
                pu8TempPtr = pu8Str;
            }
            for (i=0; i<len; i++)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, (pu8TempPtr[i*2+1]<<8) | pu8TempPtr[i*2], &pGlyphDispInfo[i]);
                pGlyphDispInfo[i].u8Width = (pGlyphDispInfo[i].u8Width * scale
#if ENABLE_DEFAULT_KERNING
                    //- kerningX_(pu16Str[i], pu16Str[i+1])
                    - kerningX_((pu8TempPtr[i*2+1]<<8) | pu8TempPtr[i*2], (pu8TempPtr[i*4+1]<<8) | pu8TempPtr[i*4])
#endif //ENABLE_DEFAULT_KERNING
                    ) / 100;
            }

        #if (ENABLE_ARABIC_OSD)

            //For Subtitle, if OSD is not mirrored status, go this way, the same with subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
            {
                U16 u16Unicode;

                for(i=0;i<len;i++)
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( i > 0 )
                    {
                        u16Unicode = (pu8TempPtr[i*2-1]<<8) + pu8TempPtr[i*2-2];
                        //if ( msAPI_OSD_IsArabicVowel( pu16Str[i-1] ) )
                        if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                        {
                            pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                    }
                    else
                    {
                        //coordinate no need change
                    }
                }
            }
            else if ( bArabicDisplay ) //for OSD
            {
                U16 u16Unicode;

                for(i=0;i<len;i++)
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( i > 0 )
                    {
                        u16Unicode = (pu8TempPtr[i*2+1]<<8) + pu8TempPtr[i*2];
                        //if ( msAPI_OSD_IsArabicVowel( pu16Str[i] ) )
                        if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                        {
                            S8 nOffset = pGlyphDispInfo[i-1].u8Width - pGlyphDispInfo[i].u8Width;

                            if ( nOffset > 0 )
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = nOffset;
                            else
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                    }
                    else
                    {
                        //coordinate no need change
                    }
                }
            }
            else
        #endif
        #if (ENABLE_THAI_OSD)
            if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
            {
                static U8 prevState = 0;
                U16 u16Unicode;

                prevState = 0;

                for(i=0;i<len;i++)
                {
                    // Check Primary Thai unicode range
                    u16Unicode = (pu8TempPtr[i*2+1]<<8) + pu8TempPtr[i*2];
                    if ( ( u16Unicode <= 0x0E5B ) && ( u16Unicode >= 0x0E01 ) )
                    {
                        if ( MinusDrawTable[ u16Unicode - 0x0E01 ] )
                        {
                            if ( i > 0 )
                            {
                                u16Unicode = (pu8TempPtr[i*2-1]<<8) + pu8TempPtr[i*2-2];
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ u16Unicode - 0x0E01 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ u16Unicode - 0xF700 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-1].u8X0 + pGlyphDispInfo[i-1].u8Width + 1) - (finfo.width);
                            }
                            else
                            {
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            //coordinate no need change
                        }

                        prevState = 1;
                    }
                    else if ( ( u16Unicode <= 0xF71A ) && ( u16Unicode >= 0xF700 ) )
                    {
                        if ( MinusDrawTablePersentation[ u16Unicode - 0xF700 ] )
                        {
                            if ( i > 0 )
                            {
                                u16Unicode = (pu8TempPtr[i*2-1]<<8) + pu8TempPtr[i*2-2];
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ u16Unicode - 0x0E01 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ u16Unicode - 0xF700 ] ) )
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-2].u8X0 + pGlyphDispInfo[i-2].u8Width + 1) - (finfo.width);
                                else
                                    pGlyphDispInfo[i].overlap_info.s8Xoffset = (pGlyphDispInfo[i-1].u8X0 + pGlyphDispInfo[i-1].u8Width + 1) - (finfo.width);
                            }
                            else
                            {
                                pGlyphDispInfo[i].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[i].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            //coordinate no need change
                        }

                        prevState = 2;
                    }
                    else
                    {
                        //coordinate no need change
                        prevState = 0;
                    }
                }
            }
        #endif
            {
            }
        }
    }
    else
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
        {
            for (i=0; i<len; i++)
            {
            #if (ENABLE_ARABIC_OSD)
                if ( bMirrorLang )
                    msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, TempBuf.U8Str[i], &pGlyphDispInfo[i]);
                else
            #endif
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu8Str[i], &pGlyphDispInfo[i]);

            }
        }
        else
        {
            U8 *pu8TempPtr;

#if (ENABLE_ARABIC_OSD)
            if ( bMirrorLang )
            {
                pu8TempPtr = TempBuf.U8Str;
            }
            else
#endif
            {
                pu8TempPtr = pu8Str;
            }
            for (i=0; i<len; i++)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, (pu8TempPtr[i*2+1]<<8) | pu8TempPtr[i*2], &pGlyphDispInfo[i]);
            }
        }
    }

    u16StrWidth = 0;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        for (i=0; i< len; i++)
        {
            u16StrWidth += pGlyphDispInfo[i].u8Width;
        }

    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            u16StrWidth += ((len-1) * pclrBtn->Fontfmt.ifont_gap);
        }
    }
    else  // gap/compact + italic
    {
        // italic or default
        u16StrWidth = finfo.width * scale * len / 100;

        // with gap or compact, only one of two
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            u16StrWidth +=  ((len-1) * pclrBtn->Fontfmt.ifont_gap);
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            u16StrWidth -=  ((len-1) * pclrBtn->Fontfmt.dis);
        }
    }

    /* draw string */
    switch(pclrBtn->enTextAlign)
    {
        case EN_ALIGNMENT_DEFAULT: //without BTN_TEXT_GAP
            text_info.dstblk.x = pclrBtn->x;
            break;

        case EN_ALIGNMENT_LEFT:
            text_info.dstblk.x = pclrBtn->x + BTN_TEXT_GAP;
            break;

        case EN_ALIGNMENT_RIGHT:
            if (u16StrWidth + BTN_TEXT_GAP > pclrBtn->width)
                text_info.dstblk.x = pclrBtn->x;
            else
                text_info.dstblk.x = pclrBtn->x + pclrBtn->width - BTN_TEXT_GAP - u16StrWidth;
            break;

        case EN_ALIGNMENT_CENTER:
            if (u16StrWidth > pclrBtn->width)
                text_info.dstblk.x = pclrBtn->x;
            else
                text_info.dstblk.x = pclrBtn->x + (pclrBtn->width - u16StrWidth) / 2;
            break;
    }

    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height * scale / 100) / 2;
    }
    else
    {
        text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height) / 2;
    }
    if (text_info.dstblk.y > 32767)
    {
        //overflow
        text_info.dstblk.y = 0;
    }
    #if 0
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        S16 s16Tmp;
        s16Tmp = ((S16)pclrBtn->height - finfo.height * scale / 100) / 2;
        s16Tmp = pclrBtn->y + s16Tmp;
        if (s16Tmp < 0)
        {
            s16Tmp = 0;
        }
        cpoint.y = s16Tmp;
    }
    else
    {
        S16 s16Tmp;
        s16Tmp = ((S16)pclrBtn->height - finfo.height) / 2;
        s16Tmp = pclrBtn->y + s16Tmp;
        if (s16Tmp < 0)
        {
            s16Tmp = 0;
        }
        cpoint.y = s16Tmp;
    }
    #endif

    if (pclrBtn->Fontfmt.flag&GEFONT_FLAG_BOLD)
    {
        pclrBtn->Fontfmt.flag |= GFXFONT_FLAG_BOLD;
    }

    text_info.dstblk.width = pclrBtn->width;
    text_info.dstblk.height = pclrBtn->height;
    text_info.flag = pclrBtn->Fontfmt.flag;
    memcpy(&text_info.color, &pclrBtn->t_clr, 4);
    text_info.pGlyphDispInfo = (GFX_GlyphDispInfo*)pGlyphDispInfo;
    text_info.gap = pclrBtn->Fontfmt.ifont_gap;
#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && ( External Subtitle Language is Thai ))*/ )
    {
        MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
        MApi_GFX_TextOut(font_handle, pu8Str, pclrBtn->bStringIndexWidth+1, &text_info);
    }
    else
#endif
#if (ENABLE_ARABIC_OSD)
    if ( bMirrorLang )
    {
        MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
        MApi_GFX_TextOut(font_handle, TempBuf.U8Str, pclrBtn->bStringIndexWidth+1, &text_info);
    }
    else
#endif
    {
        MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
        MApi_GFX_TextOut(font_handle, pu8Str, pclrBtn->bStringIndexWidth+1, &text_info);
    }

    if(pGlyphDispInfo != NULL)
    {
        MSAPI_MEMORY_FREE(pGlyphDispInfo,BUF_ID_GLYPH_DISP_INFO);
    }

    msAPI_GE_SetMirror(0, 0);    //patch GE driver
    msAPI_OSD_Free_resource();
}

#define DBG_SMART_TEXT(x)   //x

/******************************************************************************/
void msAPI_OSD_DrawScrolPunctuatedString(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num)
{
    S8  gap;
    U16 iRow;
    U8  scale, offset_len;
    U16 input_strlen;
    U16 input_char_count, input_last_char_count, output_char_count, output_last_char_count;
    U16 input_char_width=0, output_total_width, output_last_total_width, max_row_width;
    //U16 *u8TempStr;
    U8 u8TempStr[STROSD*2];
    U16 input_char_data = 0;

    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    BOOLEAN bIsOneByteString;
    BOOLEAN bSetNextLineStartInx    = FALSE;
    BOOLEAN bIsSpecialCharacterUsed = FALSE;
    BOOLEAN bIsChar_CRLF    = FALSE;
    BOOLEAN bIsChar_0x86    = FALSE;
    BOOLEAN bIsChar_0x87    = FALSE;
    BOOLEAN bIsChar_SHY     = FALSE;
    BOOLEAN bIsChar_LastSHY = FALSE;
    BOOLEAN bIsChar_Normal  = FALSE;

    U16 u16OriginalPosition_x   = pclrBtn->x;
    U16 u16OriginalPosition_y   = pclrBtn->y;
    U16 u16OriginalFontfmtFlag  = pclrBtn ->Fontfmt.flag;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringType TempBuf;
    OSDStringTypeDouble outbuf;
    #if ( ENABLE_ARABIC_OSD )
        OSDStringType out;
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
    U16 nFontID;
#endif
    FONTHANDLE Org_font_handle = font_handle;

//    U32 _timer = msAPI_Timer_GetTime0();

    // Abnormal condition
    if(max_row_num == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> max_row_num = 0\n"););
        return;
    }
    else if ((input_strlen = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> strlen = 0\n"););
        return;
    }


//printf("@@@@@@@@@@  u8Scroll_BaseLine =%d\n",u8Scroll_BaseLine);
    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_GET_resource();
    //u8TempStr = (U16*)TempStr;

 #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT))

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
    #if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
        case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( bHebrewMixedMode )
                    {
                        bHebrew = TRUE;
                    }
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                    {
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                    }

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                    }
                }
            }

            if ( bHebrew == FALSE )
            {
                bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;

            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
            }
            else
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
            }
            break;
    #endif
    #if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;

            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }

    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
            }
            break;
    #endif
    /*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            break;
    */
#if ( ENABLE_TTF_FONT )
        //Currently Emphasis character effect and other control codes are not implemented in TTF font
        //We only support 0x8A new line chatacter
        case LANGUAGE_OSD_HINDI:
        //case LANGUAGE_OSD_URDU:
        case LANGUAGE_OSD_BENGALI:
        case LANGUAGE_OSD_TELUGU:
        case LANGUAGE_OSD_MARATHI:
        case LANGUAGE_OSD_TAMIL:
        case LANGUAGE_OSD_MYANMAR:
        case LANGUAGE_OSD_KHMER:
        case LANGUAGE_OSD_LAO:
        case LANGUAGE_OSD_ASSAMESE:
        case LANGUAGE_OSD_GUJARATI:
        case LANGUAGE_OSD_KANNADA:
        case LANGUAGE_OSD_MALAYALAM:
        case LANGUAGE_OSD_PUNJABI:
        {
            msAPI_OSD_Free_resource();
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(TRUE);
            msAPI_OSD_DrawPunctuatedString(font_handle, (U16 *)((void *)pu8Str), pclrBtn, max_row_num);
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(FALSE);
        }

        return;

        break;
#endif

        default:
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            break;
    }
#endif

#if (ENABLE_ARABIC_OSD)
    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }

#endif

    if(pclrBtn->bStringIndexWidth==CHAR_IDX_1BYTE)
    {
        if (input_strlen >= sizeof(TempStr.U8Str))
        {
            input_strlen = sizeof(TempStr.U8Str) - 1;
        }

    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            U16 i;

            memcpy(out.U8Str, pu8Str, input_strlen);
            for(i = 0; i < input_strlen; i++)
            {
                TempBuf.U8Str[i] = out.U8Str[(input_strlen-1)-i];
            }
            TempBuf.U8Str[input_strlen] = 0;
            pu8Str = TempBuf.U8Str;
        }
        else
    #endif
        {
            //memcpy(TempBuf.U8Str,pu8Str,len);
        }
    }
    else
    {
    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
        if (input_strlen >= sizeof(TempBuf.U8Str)/2)
        {
            input_strlen = sizeof(TempBuf.U8Str)/2 - 1;
        }
    #endif

    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            memcpy(TempBuf.U8Str,pu8Str,input_strlen*2);
            TempBuf.U16Str[input_strlen] = 0;

            //For Subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //Every language is possible, you can't skip this filter here
                msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
                msAPI_OSD_UrduFilter(outbuf.U16Str, input_strlen);
            }
            else if ( bArabicDisplay ) //for OSD
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //just skip this function for non Kurdish condition
                if ( enLanguage == LANGUAGE_OSD_KURDISH )
                {
                    msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
                }
                else if ( enLanguage == LANGUAGE_OSD_URDU )
                {
                    msAPI_OSD_UrduFilter(outbuf.U16Str, input_strlen);
                }
            }
            else    // for Hebrew
            {
                            memcpy(outbuf.U8Str, TempBuf.U8Str, input_strlen*2);
            }

                   outbuf.U16Str[input_strlen] = 0;
                   pu8Str = outbuf.U8Str;
            }

    #endif
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)(pclrBtn->Fontfmt.height / finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)(pclrBtn->Fontfmt.width / finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }
    else
    {
        scale = 1;
    }

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        //temp solution for compiler warning
        memcpy(TempBuf.U8Str, pu8Str, input_strlen*2);

        input_strlen = Thai_compose(TempBuf.U16Str, 0, input_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[input_strlen] = 0x0000;

        pu8Str = outbuf.U8Str;
    }
#endif

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
    {
    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        gap = pclrBtn->Fontfmt.ifont_gap;
    }
    else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
    {
        gap = -pclrBtn->Fontfmt.dis;
    }
    else
    {
        gap = 0;
    }

    bIsOneByteString        = (pclrBtn->bStringIndexWidth & CHAR_IDX_1BYTE) ? TRUE : FALSE;
    max_row_width           = pclrBtn->width - 2*BTN_TEXT_GAP;
    input_last_char_count   = 0;
    output_total_width      = 0;

    DBG_SMART_TEXT(printf("< Start > gap = %bd, input_strlen = %u\n", gap, input_strlen););

    // Row handle loop
    for (iRow=0, input_char_count=0; /*(iRow<max_row_num +1) && */(input_char_count < input_strlen);)
    {
        if (iRow==1 && bSetNextLineStartInx == FALSE)
        {
            if(0xE08A == ReadU16LE(&pu8Str[input_char_count*2]))
            {
                u16NextLineStartInx = (input_char_count+1);
            }
            else
            {
                u16NextLineStartInx = input_char_count;
            }

            bSetNextLineStartInx = TRUE;
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("< iRow = %u > input_char_count = %u, input_strlen = %u\n", iRow, input_char_count, input_strlen););
            //printf("< iRow = %u > input_char_count = %u, input_strlen = %u\n", iRow, input_char_count, input_strlen);
        }

        // Reset variable
        input_last_char_count   = 0;
        output_char_count       = 0;
        output_last_char_count  = 0;
        output_last_total_width = 0;
        bIsChar_CRLF            = FALSE;
        bIsChar_SHY             = FALSE;
        bIsChar_LastSHY         = FALSE;
        bIsChar_0x86            = FALSE;
        bIsChar_0x87            = FALSE;
        bIsChar_Normal          = FALSE;

        // Filter one word (end with space or control code)
        while ( (output_total_width<max_row_width) && (input_char_count < input_strlen) && ( output_char_count < (STROSD-1)))
        {
            if (bIsOneByteString)   // One byte string
            {
                input_char_data = pu8Str[input_char_count];
                // Contrl code, SHY or space char
                if ((0x20==input_char_data) || ((0x80<=input_char_data)&&(input_char_data<=0x9F)) )
                {
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0x8A==input_char_data )            // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0x86==input_char_data )       // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0x87==input_char_data )       // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        pu8Str[input_char_count]  = 0x20;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal      = TRUE;
                }
            }
            else    // Two bytes string
            {
                //input_char_data = pu16Str[input_char_count];
                input_char_data = (pu8Str[input_char_count*2+1]<<8) + pu8Str[input_char_count*2];
                if ( 0x00AD==input_char_data)               // SHY - soft hyphen
                {
                      bIsSpecialCharacterUsed=TRUE;
                    DBG_SMART_TEXT(printf ("<< SHY [%2u] 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_SHY     = TRUE;
                    bIsChar_LastSHY = TRUE;
                }
                else if ((0x0020==input_char_data) || ( (0xE080<=input_char_data) && (input_char_data<=0xE09F) ) )
                {
                       bIsSpecialCharacterUsed=TRUE;
                    DBG_SMART_TEXT(printf ("<< Control Code [%2u] = 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_LastSHY         = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0xE08A==input_char_data )          // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0xE086==input_char_data )     // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0xE087==input_char_data )     // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        //pu16Str[input_char_count] = 0x0020;
                        pu8Str[input_char_count*2] = 0x20;
                        pu8Str[input_char_count*2+1] = 0x00;
                    }
                }
                  else if (bIsSpecialCharacterUsed==FALSE && (output_total_width + input_char_width >= max_row_width))
                  {


                    bIsChar_LastSHY         = FALSE;
                      input_last_char_count   = input_char_count-1;
                      output_last_char_count  = output_char_count;    // Save the char count to last control char
                      output_last_total_width = output_total_width;   // Save the display width to last control char
                      bIsChar_CRLF        = TRUE;
                  }
                else                                         // Normal char
                {
                    bIsChar_Normal          = TRUE;
                }
            }

            // Retrieve input char width or add null char
            if (bIsChar_Normal || bIsChar_SHY)
            {
                if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
                {
                    if (bIsOneByteString)   // One byte string
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[input_char_count], &BBox_X_Info);
                    }
                    else
                    {
                    #if (ENABLE_ARABIC_OSD)
                        //For Subtitle
                        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
                        {
                            U16 u16Unicode;

                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                u16Unicode = (pu8Str[input_char_count*2-1]<<8) + pu8Str[input_char_count*2-2];

                                if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    //in Arabic language mode, gap is always zero, so we can forget gap value
                                    output_total_width -= (BBox_X_Info.u8Width*scale+gap);
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else if ( bArabicDisplay ) //for OSD
                        {
                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                if ( msAPI_OSD_IsArabicVowel( input_char_data ) )
                                {
                                    //skip current vowel character width
                                    //do nothing here
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                    #if (ENABLE_THAI_OSD)
                        if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
                        {
                            // Check Primary Thai unicode range
                            if ( ( input_char_data <= 0x0E5B ) && ( input_char_data >= 0x0E01 ) )
                            {
                                if ( MinusDrawTable[ input_char_data - 0x0E01 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else if ( ( input_char_data <= 0xF71A ) && ( input_char_data >= 0xF700 ) )
                            {
                                if ( MinusDrawTablePersentation[ input_char_data - 0xF700 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                            input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                        }
                    }
                }
                else
                {
                    input_char_width = finfo.width;
                    input_char_width = (output_char_count==0) ? (finfo.width) : (finfo.width*scale+gap);
                }

                bIsChar_Normal = FALSE;
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_char_count] = 0;
                    u8TempStr[output_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_char_count] = 0;
                    u8TempStr[output_char_count*2] = 0;
                    u8TempStr[output_char_count*2+1] = 0;
                }

                input_char_count++;
                break;
            }

            // check if string width larger than OSD display width
            if ((output_total_width+input_char_width) < max_row_width)
            {
                if (bIsChar_SHY)    // add normal char and space
                {
                    // Save temporary Last SHY char position for display
                    bIsChar_SHY             = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char
                }
                else                // space and other char
                {
                    if(bIsOneByteString)
                    {
                        //((U8*)u8TempStr)[output_char_count++] = pu8Str[input_char_count];
                        u8TempStr[output_char_count++] = pu8Str[input_char_count];
                    }
                    else
                    {
                        //u8TempStr[output_char_count++] = pu16Str[input_char_count];
                        u8TempStr[(output_char_count)*2] = pu8Str[input_char_count*2];
                        u8TempStr[(output_char_count)*2+1] = pu8Str[input_char_count*2+1];
                        output_char_count++;
                    }

                    output_total_width += input_char_width;
                }

                //if (g_EpgTest)
                {
                    DBG_SMART_TEXT(printf("pu16Str[%2u]= 0x%04x(%c), input_char_width = %02u, last_total_width = %4u, output_total_width = %4u, max_row_width =%4u\n", input_char_count, pu16Str[input_char_count], (U8)pu16Str[input_char_count], input_char_width, output_last_total_width, output_total_width, max_row_width););
                }

                input_char_count++;
                if (input_char_count>=input_strlen)     // Draw to the last char
                {
                    bIsChar_LastSHY = FALSE;
                #if(!ENABLE_ARABIC_OSD && !ENABLE_THAI_OSD)
                    {
#if(ENABLE_DTV_EPG && ENABLE_DVB)
                        if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_INFO_DESC_TEXT))
                        {
                            if(_u8InfoScrollLineCount <= (MApp_ZUI_ACT_EPGGetDescInfoPageNum() - 1))
                            {
                                if(bIsOneByteString)
                                {
                                    u8TempStr[output_last_char_count] = 0;
                                }
                                else
                                {
                                    u8TempStr[output_last_char_count*2] = 0;
                                    u8TempStr[output_last_char_count*2+1] = 0;
                                }
                            }
                        }
#endif
                    }
                #endif
                    break;
                }
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count*2] = 0;
                    u8TempStr[output_last_char_count*2+1] = 0;
                }
                break;
            }
        }           // End of while loop

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("1 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
        }

        // Draw text to last control char or space char
        //if ( (output_last_char_count > 0) || (output_char_count > 0))
        {
            // Control code handle
            if (bIsChar_0x86 || bIsChar_0x87)          // character emphasis on/off
            {
                msAPI_OSD_Draw2BytesText(Org_font_handle, u8TempStr, pclrBtn);

                pclrBtn->x = u16OriginalPosition_x + output_last_total_width;

                if (bIsChar_0x86)
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_BOLD;
                }
                else
                {
                    pclrBtn->Fontfmt.flag = u16OriginalFontfmtFlag;
                }
            }
            else
            {
                if(bIsChar_LastSHY && ((pu8Str[input_last_char_count*2+1]<<8) + pu8Str[input_last_char_count*2] == 0x20) )
                    bIsChar_LastSHY = FALSE;

                if (bIsChar_LastSHY)        // Last SHY - soft hyphen
                {
                    u8TempStr[output_last_char_count*2]   = 0xAD; //0x00AD
                    u8TempStr[(output_last_char_count*2)+1] = 0x00;
                    u8TempStr[(output_last_char_count*2)+2] = 0x00; //0x0000
                    u8TempStr[(output_last_char_count*2)+3] = 0x00;

                }
                else                        // Space char or other
                {
                    u8TempStr[(output_char_count*2)]   = 0;
                    u8TempStr[(output_char_count*2)+1]   = 0;
                }
                //printf("iRow=%d\n",iRow);
               // printf("u8Scroll_BaseLine=%d\n",u8Scroll_BaseLine);


                if((iRow <u8Scroll_BaseLine) || (iRow> u8Scroll_BaseLine+max_row_num))
                {
                }
                else
                {

                    msAPI_OSD_Draw2BytesText(font_handle, u8TempStr, pclrBtn);
                    pclrBtn->x  = u16OriginalPosition_x;
                    pclrBtn->y += pclrBtn->height;
                }
                output_total_width     = 0;
                  bIsSpecialCharacterUsed = FALSE;
                iRow++;
            }
            offset_len = 1; // the var needs to be initialized
#if(ENABLE_DTV_EPG)

            if (input_char_count < input_strlen)
            {
                input_char_count = input_last_char_count+1;
                //fixed risk test bug, when play T49 channel of 3458_24.ts,it will show error epg message in second page.mantis:0285711
                u16RecordOnePageByte[_u8InfoScrollLineCount] = input_char_count;
            }
            else
            {

                u16RecordOnePageByte[_u8InfoScrollLineCount] = (input_last_char_count+1);
            }
#endif
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("2 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
            DBG_SMART_TEXT(printf ("<< (x, y) = (%4u, %4u) >>\n", pclrBtn->x, pclrBtn->y););
        }

        if (input_char_count < input_strlen)
        {
            bStopScrollDown = FALSE;
        }
        else
        {
            bStopScrollDown = TRUE;
        }
    }
    if(u8Scroll_TotalCount == 0)
    {
        u8Scroll_TotalCount = iRow;
        //printf("@@@  u8Scroll_TotalCount=%d\n ",u8Scroll_TotalCount);
    }
    pclrBtn->y = u16OriginalPosition_y;

    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_Free_resource();

    //printf ("Time = %lu\n", _timer = msAPI_Timer_DiffTimeFromNow(_timer));
}

#if(ENABLE_ARABIC_OSD)
static U8 msAPI_OSD_ArabicVowel_AdjustY_postion(U16 inputc)
{
    //Arabic Vowel characters presentation form
    switch(inputc)
    {
        case 0xFE70:
        case 0xFE76:
        case 0xFE78:
        case 0xFE7C:
            return 3;
        default:
            return 0;
    }
}
#endif
U16 msAPI_OSD_GetStringWidth_NEW(FONTHANDLE font_handle, U16 *pu16Str, OSDClrBtn *pclrBtn)
{
    S8 gap;
    U8 cut_strlen;
    U16 total_strlen, width , scale;
    U16 max_width, dot_width;

    OSD_RESOURCE_FONT_INFO finfo;
    OSDSRC_GLYPH_DISP_INFO *pGlyphDispInfo = NULL;
    U16 parse_buffer[STROSD*2];
    memset(parse_buffer,0,STROSD*2);


#if ENABLE_SHORT_STRING_BUFFER //speed up drawing string
    OSDSRC_GLYPH_DISP_INFO _s_temp_glyph[32];
#endif

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringType TempBuf;
    OSDStringTypeDouble outbuf;
    #if ( ENABLE_ARABIC_OSD )
        OSDStringType out;
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
#endif

    U8 bIgboDisplay = FALSE;
    U8 bYorDisplay = FALSE;

    memset(&finfo, 0, sizeof(OSD_RESOURCE_FONT_INFO));

    msAPI_OSD_GET_resource();

    if (pclrBtn->bStringIndexWidth != CHAR_IDX_2BYTE)
    {
        APIOSD_DBG(printf("Only support 2 bytes strubg\n"));
        msAPI_OSD_Free_resource();
        return 0;
    }

    if ((total_strlen = msAPI_OSD_GetStrLength((U8*)pu16Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> strlen = 0\n"));
        msAPI_OSD_Free_resource();
        return 0;
    }

    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )

        switch(MApp_GetLanguageForFont())
        {
            case LANGUAGE_OSD_ARABIC:
            case LANGUAGE_OSD_PARSI:
            case LANGUAGE_OSD_KURDISH:
            case LANGUAGE_OSD_URDU:
                {
                    {
                        if ( bHebrewMixedMode )
                        {
                            bHebrew = TRUE;
                        }

                        if ( !bDivxSubtitleMode )
                        {
                            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                        }
                    }
                }
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;

                if ( bHebrew == FALSE )
                {
                    bArabicDisplay = TRUE;
                }
                break;
            case LANGUAGE_OSD_HEBREW:
                bHebrew = TRUE;
                if ( !bDivxSubtitleMode )
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                }
                break;

    #if ( ENABLE_THAI_OSD )
            case LANGUAGE_OSD_THAI:
        #if ( ENABLE_ARABIC_OSD )
                if ( bHebrew == FALSE )
        #endif
                {
                    bThaiDisplay = TRUE;
                }
                break;
    #endif

            default:
                break;
        }
    #endif


#if (ENABLE_ARABIC_OSD)

    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }

#endif

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )

    if (total_strlen >= sizeof(TempBuf.U8Str)/2)
    {
        total_strlen = sizeof(TempBuf.U8Str)/2 - 1;
    }


    //CID 177716 (#1-2 of 2): Pointer to local outside scope (RETURN_LOCAL)
    //At (17): Using "pu16Str", which points to an out-of-scope variable "parse_buffer".

    #if ( ENABLE_ARABIC_OSD )
    if ( bMirrorLang )
    {
        U8 bReverse = TRUE;
        U16 i;

        memcpy(TempBuf.U8Str,(U8 *)pu16Str,total_strlen*2);
        //((U16 *)TempBuf)[total_strlen] = 0;
        TempBuf.U16Str[total_strlen] = 0;

        //For Subtitle
        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
        {
            S32 errorCode = U_ZERO_ERROR;

            ArabicParser(TempBuf.U16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);
            //Every language is possible, you can't skip this filter here
            msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);

            if(MApp_GetMenuLanguage_DTG() == LANGUAGE_OSD_URDU)
                //msAPI_OSD_UrdoFilter(outbuf.U16Str, total_strlen);
            //msAPI_OSD_PersationFilter(outbuf.U16Str, total_strlen);
            msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, total_strlen);
            msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, TempBuf.U16Str, total_strlen);
            bReverse = FALSE;
        }
        else if ( bArabicDisplay ) //for OSD
        {
            S32 errorCode = U_ZERO_ERROR;

            ArabicParser(TempBuf.U16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);
            //just skip this function for non Kurdish condition
            //if ( MApp_GetLanguageForFont() == LANGUAGE_OSD_KURDISH )
            //{
              //  msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
            //}

            msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
            if(MApp_GetMenuLanguage_DTG() == LANGUAGE_OSD_URDU)
               // msAPI_OSD_UrdoFilter(outbuf.U16Str, total_strlen);

               // msAPI_OSD_PersationFilter(outbuf.U16Str, total_strlen);

            msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, total_strlen);
            msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, total_strlen);
        }
        else    // for Hebrew
        {
            if ( bDivxSubtitleMode )    // Divx subtitle
            {
                msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, outbuf.U16Str, total_strlen);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, total_strlen);
                msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, total_strlen);
            }
            else if ( bHebrew )         // Hebrew OSD display
            {
                msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, out.U16Str, total_strlen);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, total_strlen);
            }
            else                        // Other conditions
            {
                msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, outbuf.U16Str, total_strlen);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, total_strlen);
                msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, total_strlen);
            }
        }

        if ( bReverse )
        {
            for(i=0;i<total_strlen;i++)
            {
                TempBuf.U16Str[i] = *(outbuf.U16Str+total_strlen-i-1);
            }
        }

        //((U16 *)TempBuf)[total_strlen] = 0;
        TempBuf.U16Str[total_strlen] = 0;

        pu16Str = TempBuf.U16Str;
    }
    #endif
#endif

    //coverity 177717
    //memset(finfo, 0, sizeof(finfo));
    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);

    scale = 100;

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = ((U16)pclrBtn->Fontfmt.height*100 / (U16)finfo.height);
        pclrBtn->Fontfmt.height = scale * finfo.height /100;

        scale = (U8)((U16)pclrBtn->Fontfmt.width*100 / (U16)finfo.width);
        pclrBtn->Fontfmt.width = scale * finfo.width /100;
    }



#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        total_strlen = Thai_compose(pu16Str, 0, total_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[total_strlen] = 0x0000;

        pu16Str = outbuf.U16Str;
    }
#endif

#if ENABLE_SHORT_STRING_BUFFER //speed up drawing string
    if (total_strlen <= COUNTOF(_s_temp_glyph))
        pGlyphDispInfo = _s_temp_glyph;
    else
#endif
        pGlyphDispInfo = msAPI_Memory_Allocate(sizeof(OSDSRC_GLYPH_DISP_INFO) * total_strlen , BUF_ID_GLYPH_DISP_INFO);
    if (pGlyphDispInfo == NULL)
    {
        __ASSERT(0);
        APIOSD_DBG(printf("E_DrawText>> pGlyphDispInfo == NULL\n"));
        msAPI_OSD_Free_resource();
        return 0;
    }

    gap = 0;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
    #if (ENABLE_ARABIC_OSD)
        {
            U16 cnt;
            BOOL IsBelongToARB = FALSE;
            for(cnt=0;cnt<total_strlen;cnt++)
            {

            }
            if ( (bArabicDisplay) && (IsBelongToARB)/*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
            {
                pclrBtn->Fontfmt.ifont_gap = 0;
            }
        }
    #endif

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
    }
    else
    {
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            gap = -pclrBtn->Fontfmt.dis;
        }
    }

    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_BOLD)
    {
        pclrBtn->Fontfmt.flag |= GFXFONT_FLAG_BOLD;
    }

    max_width = pclrBtn->width;



    dot_width =0;

    max_width -= dot_width;

   // if(pclrBtn->enTextAlign==EN_ALIGNMENT_LEFT ||pclrBtn->enTextAlign==EN_ALIGNMENT_RIGHT)
    //   max_width -= BTN_TEXT_GAP;

    {
        width = 0;
        cut_strlen = 0;

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            static U8 prevState = 0;

            prevState = 0;

            {
                U16 lang;

                lang = MApp_GetMenuLanguage_DTG();

                if(lang == LANGUAGE_OSD_ARABIC || lang == LANGUAGE_OSD_URDU )
                {
                    U16 i;
                    for(i=0;i<total_strlen;i++)
                    {
                        msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu16Str[i], &pGlyphDispInfo[i]);

                        pGlyphDispInfo[i].u8Width = (pGlyphDispInfo[i].u8Width * scale
#if ENABLE_DEFAULT_KERNING
                            - kerningX_(pu16Str[i], pu16Str[i+1])
#endif //ENABLE_DEFAULT_KERNING
                            ) / 100;

                    }


                }
            }


            while (cut_strlen<total_strlen)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu16Str[cut_strlen], &pGlyphDispInfo[cut_strlen]);

                pGlyphDispInfo[cut_strlen].u8Width = (pGlyphDispInfo[cut_strlen].u8Width * scale
#if ENABLE_DEFAULT_KERNING
                    - kerningX_(pu16Str[cut_strlen], pu16Str[cut_strlen+1])
#endif //ENABLE_DEFAULT_KERNING
                    ) / 100;



            #if (ENABLE_ARABIC_OSD)
                //For Subtitle
                if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || ( External Subtitle Language is Arabic ) */ ) )
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {
                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen-1] ) )
                        {
                            width -= pGlyphDispInfo[cut_strlen-1].u8Width;

                            pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            //coordinate no need change
                        }
                    }
                    else
                    {
                        //coordinate no need change
                    }

                    width += (pGlyphDispInfo[cut_strlen].u8Width + gap);
                }
                else if ( bArabicDisplay ) //for OSD
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {

                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen] ) )
                        {
                            //skip current vowel character width
                            //do nothing here
                            S8 nOffset = pGlyphDispInfo[cut_strlen-1].u8Width - pGlyphDispInfo[cut_strlen].u8Width;

                            if ( nOffset > 0 )
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = nOffset;
                            else
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            //pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;
                        pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset =msAPI_OSD_ArabicVowel_AdjustY_postion( pu16Str[cut_strlen] );

                        }
                        else
                        {
                            width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                            //coordinate no need change
                        }
                    }
                    else
                    {
                        width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                        //coordinate no need change
                    }
                }
                else
            #endif
            #if (ENABLE_THAI_OSD)
                if ( ( bThaiDisplay ) || ((bDivxSubtitleMode) /* && (External Subtitle Language is Thai) */ ) )
                {
                    // Check Primary Thai unicode range
                    if ( ( pu16Str[cut_strlen] <= 0x0E5B ) && ( pu16Str[cut_strlen] >= 0x0E01 ) )
                    {
                        if ( MinusDrawTable[ pu16Str[cut_strlen] - 0x0E01 ] )
                        {
                            if ( cut_strlen > 0 )
                            {
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ pu16Str[cut_strlen-1] - 0x0E01 ] ) )
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ pu16Str[cut_strlen-1] - 0xF700 ] ) )
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                else
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-1].u8X0 + pGlyphDispInfo[cut_strlen-1].u8Width + 1) - (finfo.width);
                            }
                            else
                            {
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;

                            //Minus coordinate, don't add width
                        }
                        else
                        {
                            width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                            //coordinate no need change
                        }

                        prevState = 1;
                    }
                    else if ( ( pu16Str[cut_strlen] <= 0xF71A ) && ( pu16Str[cut_strlen] >= 0xF700 ) )
                    {
                        if ( MinusDrawTablePersentation[ pu16Str[cut_strlen] - 0xF700 ] )
                        {
                            if ( cut_strlen > 0 )
                            {
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ pu16Str[cut_strlen-1] - 0x0E01 ] ) )
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ pu16Str[cut_strlen-1] - 0xF700 ] ) )
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                else
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-1].u8X0 + pGlyphDispInfo[cut_strlen-1].u8Width + 1) - (finfo.width);
                            }
                            else
                            {
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;

                            //Minus coordinate, don't add width

                            prevState = 2;
                        }
                        else
                        {
                            width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                            //coordinate no need change
                            prevState = 0;
                        }
                    }
                    else
                    {
                        width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                        //coordinate no need change
                    }
                }
                else
            #endif
                if(bIgboDisplay || bYorDisplay)
                {
                    if ( ( pu16Str[cut_strlen] == 0x0300 ) && ( pu16Str[cut_strlen] == 0x0301 ) )
                    {
                        if ( cut_strlen > 0 )
                        {
                            if(bYorDisplay)
                            {

                              pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen].u8X0 +1+pGlyphDispInfo[cut_strlen-1].u8X0 + pGlyphDispInfo[cut_strlen-1].u8Width + 1) - (finfo.width)-10;
                              pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset -3;
                            }
                            else
                            {
                            pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen].u8X0 +1+pGlyphDispInfo[cut_strlen-1].u8X0 + pGlyphDispInfo[cut_strlen-1].u8Width + 1) - (finfo.width)-10;
                            }
                        }
                        else
                        {
                            width += (pGlyphDispInfo[cut_strlen].u8Width + gap);
                        }
                    }
                    else
                    {
                        width += (pGlyphDispInfo[cut_strlen].u8Width + gap);
                    }
                }
                else
                {
                    width += (pGlyphDispInfo[cut_strlen].u8Width + gap);
                }
                cut_strlen++;

            }
        }
        else
        {
            while( cut_strlen<total_strlen)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu16Str[cut_strlen], &pGlyphDispInfo[cut_strlen]);

                cut_strlen++;
                width += (finfo.width + gap);

            }
        }



        }


       if (pGlyphDispInfo != NULL)
    {
#if ENABLE_SHORT_STRING_BUFFER     //speed up drawing string
        if (total_strlen <= COUNTOF(_s_temp_glyph))
            ; //do nothing: pGlyphDispInfo = _s_glyph;
        else
#endif
            MSAPI_MEMORY_FREE(pGlyphDispInfo, BUF_ID_GLYPH_DISP_INFO);
    }
        msAPI_OSD_Free_resource();


        return   (width+6);// Add 6 is for  request


}

void msAPI_OSD_DrawPunctuatedString_S1_NEW(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num, BOOL enable_3dot)
{
    S8 gap;
    S16 i;
    U8 scale, offset_len, cut_strlen;
    U16 total_strlen, strlen_1, width, bytes_num, total_width;
    U16 max_width, buf_y;
    U8 *pStr;
    OSD_RESOURCE_FONT_INFO finfo;
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    U8 bExceed = FALSE;// for 3dot ending

    //For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    BOOLEAN bGetLastSpaceinSingleLine;
    U8 u8LastSpaceIndex;
    U16 u16LastSpace_Width;
    //For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    BOOLEAN bIsEmphasis =false;

    BOOLEAN bControlCode0x8A = false;
    BOOLEAN bControlCode0x86 = false;
    BOOLEAN bControlCode0x87 = false;
    BOOLEAN bControlCodeSHY_NewLine = false;
    BOOLEAN bLastSHY = false;




    U16 u16OrignalxPosition = pclrBtn->x;
    U16 u16OrignalFontfmtFlag = pclrBtn ->Fontfmt.flag;
    U8 pSHYStr[2];
    pSHYStr[0]=0x2d;
    pSHYStr[1]=0;
    union
        {
            U8 * u8ptr;
            U16 * u16ptr;
        }g_ptr,g_ptr1;

    g_ptr.u8ptr = pu8Str;
    memset(&finfo, 0, sizeof(OSD_RESOURCE_FONT_INFO));

    total_strlen = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth);


    if (total_strlen==0)
    {
        return;
    }

    strlen_1 = total_strlen;
    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
    scale = 1;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)((U16)pclrBtn->Fontfmt.height / (U16)finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)((U16)pclrBtn->Fontfmt.width / (U16)finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }

    gap = 0;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
    }
    else
    {
        if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            gap = -pclrBtn->Fontfmt.dis;
        }
    }

    if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
    {
        offset_len = 1;
    }
    else
    {
        offset_len = 2;
    }

    buf_y = pclrBtn->y;
    max_width = pclrBtn->width - 2*BTN_TEXT_GAP;
    //width=0;
    total_width =0;
    for(i=0; i<max_row_num && total_strlen; i++)
    {
        width = 0;

        cut_strlen = 0;
        bGetLastSpaceinSingleLine=FALSE;//Reset variable
        u8LastSpaceIndex = 0;//Reset variable
        u16LastSpace_Width = 0; //Reset variable
        bExceed = FALSE;// for 3dot ending

        //printf("i =%d\n",i);

        if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
            {
                while(total_width<max_width && cut_strlen<total_strlen)
                {
                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[cut_strlen++], &BBox_X_Info);
                    width += (BBox_X_Info.u8Width*scale + gap);
                    total_width+=(BBox_X_Info.u8Width*scale + gap);
                    if ((pu8Str[(cut_strlen-1)]==0x20)||((pu8Str[(cut_strlen-1)]>=0x80)&&(pu8Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                    {
                        u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                        u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                        bGetLastSpaceinSingleLine = TRUE;

                        if ( pu8Str[(cut_strlen-1)]==0x8A )
                        {
                            pu8Str[(cut_strlen-1)]=0x20;
                            break;
                        }
                        else if ( pu8Str[(cut_strlen-1)]==0x86 )
                        {
                            bIsEmphasis =true;
                            bControlCode0x86 =true;
                            break;
                        }
                        else if ( pu8Str[(cut_strlen-1)]==0x87 )
                        {
                            bControlCode0x87 = true;
                            break;
                        }
                        else
                        {
                            pu8Str[(cut_strlen-1)]=0x20;
                        }
                    }
                }
            }
            else //(pclrBtn->bStringIndexWidth == CHAR_IDX_2BYTE)
            {

                while(total_width<max_width && cut_strlen<total_strlen)
                {
                    // rock modify for arba

                    U16 tempchar;
                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, g_ptr.u16ptr[cut_strlen], &BBox_X_Info);

                    tempchar = g_ptr.u16ptr[cut_strlen+1];
                    g_ptr.u16ptr[cut_strlen+1]=0;


                    width += (BBox_X_Info.u8Width*scale + gap);
                    total_width = msAPI_OSD_GetStringWidth_NEW( font_handle, &g_ptr.u16ptr[0],pclrBtn)-4;//6 is  overcalcuate
                    g_ptr.u16ptr[cut_strlen+1]=tempchar;
                    cut_strlen ++;

                    if ((g_ptr.u16ptr[(cut_strlen-1)]==0x0020)||((g_ptr.u16ptr[(cut_strlen-1)]>=0xE080)&&(g_ptr.u16ptr[(cut_strlen-1)]<=0xE09F)) )//if Space Char or Control code
                    {
                        u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.

                        u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                        bGetLastSpaceinSingleLine = TRUE;

                        if ( g_ptr.u16ptr[(cut_strlen-1)]==0xE08A )// New Line
                        {
                            g_ptr.u16ptr[(cut_strlen-1)]=0x0020;
                            bControlCode0x8A = true;
//#ifdef USE_NL  // Need this "break" for SI test
                            break;
//#endif
                        }
                        else if ( g_ptr.u16ptr[(cut_strlen-1)]==0xE086 )
                        {
                            bControlCode0x86 =true;
                            break;
                        }
                        else if ( g_ptr.u16ptr[(cut_strlen-1)]==0xE087 )
                        {
                            bControlCode0x87 = true;
                            break;
                        }
                        else
                        {
                            g_ptr.u16ptr[(cut_strlen-1)]=0x0020;
                        }
                    }
                }
            }
        }
        else
        {
            while(total_width<max_width && cut_strlen<total_strlen)
                        {
                cut_strlen++;
                width += (finfo.width + gap);
                total_width+=(finfo.width + gap);
                if ((pu8Str[(cut_strlen-1)]==0x20)||((pu8Str[(cut_strlen-1)]>=0x80)&&(pu8Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                            {
                                u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                                bGetLastSpaceinSingleLine = TRUE;

                    if ( pu8Str[(cut_strlen-1)]==0x8A )
                    {
                        pu8Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        pu8Str[(cut_strlen-1)]=0x20;
                            }
                        }
                    }
        }

        //rock for arbic
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_2BYTE  && (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH))
        {

            if(bControlCode0x8A || bControlCode0x86 || bControlCode0x87)
            {
                if((width > max_width)||((total_strlen > cut_strlen)&&(g_ptr.u16ptr[(cut_strlen)-1]!=0x0020))) //if a single word is cut
                {
                    //if (!bControlCodeSHY_NewLine)
                    {

                        cut_strlen--;
                    }
                    bExceed = TRUE;// for 3dot ending
                }


            }
            else
            {

                if((total_width > max_width)||((total_strlen > cut_strlen)&&(g_ptr.u16ptr[(cut_strlen)-1]!=0x0020))) //if a single word is cut
                {
                    //if (!bControlCodeSHY_NewLine)
                    {

                        cut_strlen--;
                    }
                        bExceed = TRUE;// for 3dot ending
                }
            }

        }
        else
        {

            if((width > max_width)||((total_strlen > cut_strlen)&&(g_ptr.u16ptr[(cut_strlen)-1]!=0x0020))) //if a single word is cut
            {
                //if (!bControlCodeSHY_NewLine)
                {

                    cut_strlen--;
                }
                bExceed = TRUE;// for 3dot ending
            }
        }
        //Set new cut string length to last Space index
        if(max_row_num>1)
        {
            if (bGetLastSpaceinSingleLine&&u8LastSpaceIndex&&(total_strlen > cut_strlen))
            {
                {
                    cut_strlen = u8LastSpaceIndex;
                }
            }
        }
        //Set new cut string length to last Space index

        APIOSD_DBG(printk("DrawSmartText>> cut_strlen = %bu\n", cut_strlen));

        if(cut_strlen == 0)
        {
            break;
        }
        else
        {
                // for 3dot ending
                if(enable_3dot==TRUE)
                {
                    if (bExceed && i == max_row_num-1)
                    {
                        {
                            OSDSRC_GLYPH_DISP_INFO pglyphDot, pglyphSpare;
                            U16 u16Cut=0;
                                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, CHAR_DOT, &pglyphDot);

                            do{
                                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, g_ptr.u16ptr[cut_strlen], &pglyphSpare);

                                u16Cut += pglyphSpare.u8Width;
                                cut_strlen--;
                                //printk("Cut=%u / %bu\n / %u \n%",u16Cut,(3*(pglyphDot.u8Width + gap)),cut_strlen);
                            }while( (( u16Cut * scale ) < (3*(pglyphDot.u8Width + gap)))&&(cut_strlen!=0));
                        }
                        if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
                        {
                            pu8Str[cut_strlen] = CHAR_DOT; // .
                            pu8Str[cut_strlen+1] = CHAR_DOT; // .
                            pu8Str[cut_strlen+2] = CHAR_DOT; // .
                            pu8Str[cut_strlen+3] = 0;//end of string
                            msAPI_OSD_DrawText(font_handle, (U8*)pu8Str, pclrBtn);
                        }else //CHAR_IDX_2BYTE
                        {
                            g_ptr.u16ptr[cut_strlen] = CHAR_DOT; // .
                            g_ptr.u16ptr[cut_strlen+1] = CHAR_DOT; // .
                            g_ptr.u16ptr[cut_strlen+2] = CHAR_DOT; // .
                            g_ptr.u16ptr[cut_strlen+3] = 0;//end of string
                            msAPI_OSD_DrawText(font_handle, g_ptr.u8ptr ,pclrBtn);
                        }
                        break;
                    }
                }
                //end "for 3dot ending"
            bytes_num = (cut_strlen+1) * offset_len;

            pStr = msAPI_Memory_Allocate(bytes_num,BUF_ID_DRAW_TEXT);

            g_ptr1.u8ptr = pStr;

            if(pStr)
            {
                memcpy(g_ptr1.u8ptr, g_ptr.u8ptr, bytes_num);

                if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
                {
                    g_ptr1.u8ptr[cut_strlen] = 0;
                }
                else
                {
                    g_ptr1.u16ptr[cut_strlen]=0;
                }

                if (bControlCode0x87)
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_BOLD;
                }

                if( i != max_row_num-1 ||  !bControlCodeSHY_NewLine )
                {
                    msAPI_OSD_DrawText(font_handle, pStr, pclrBtn);
                }

                msAPI_Memory_Free(pStr,BUF_ID_DRAW_TEXT);
            }

            total_strlen -= (cut_strlen);
            g_ptr.u8ptr += ((cut_strlen)*offset_len);

        }

        if (bControlCode0x86)
        {
            bControlCode0x86 = false;
            bIsEmphasis =true;
            pclrBtn->x += u16LastSpace_Width;
            bLastSHY=false;
            i--; // no need to increase max_row_num
        }
        else if ( bControlCode0x87)
        {
            bControlCode0x87 = false;
            bIsEmphasis =false;

            pclrBtn->Fontfmt.flag = u16OrignalFontfmtFlag;
            pclrBtn->x += u16LastSpace_Width;
            bLastSHY=false;
            i--; // no need to increase max_row_num
        }
        else
        {

            bControlCode0x8A = false;
            if (!bControlCodeSHY_NewLine)
            {
                pclrBtn->y += pclrBtn->height;
                pclrBtn ->x = u16OrignalxPosition;
                total_width=0;
                bLastSHY=false;
            }
            else
            {
                bControlCodeSHY_NewLine=false;
                pclrBtn->x +=width;
                total_width = width;
            }
        }
    }

    pclrBtn->y = buf_y;
}


/******************************************************************************/
void msAPI_OSD_DrawPunctuatedString_S1(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num)
{
    S8  gap;
    U16 iRow;
    U8  scale, offset_len;
    U16 input_strlen;
    U16 input_char_count, input_last_char_count, output_char_count, output_last_char_count;
    U16 input_char_width=0, output_total_width, output_last_total_width, max_row_width;
    //U16 *u8TempStr;
    U8 u8TempStr[STROSD*2];
    U16 input_char_data = 0;

    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    BOOLEAN bIsOneByteString;
    BOOLEAN bSetNextLineStartInx    = FALSE;
    BOOLEAN bIsSpecialCharacterUsed = FALSE;
    BOOLEAN bIsChar_CRLF    = FALSE;
    BOOLEAN bIsChar_0x86    = FALSE;
    BOOLEAN bIsChar_0x87    = FALSE;
    BOOLEAN bIsChar_SHY     = FALSE;
    BOOLEAN bIsChar_LastSHY = FALSE;
    BOOLEAN bIsChar_Normal  = FALSE;

    U16 u16OriginalPosition_x   = pclrBtn->x;
    U16 u16OriginalPosition_y   = pclrBtn->y;
    U16 u16OriginalFontfmtFlag  = pclrBtn ->Fontfmt.flag;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringType TempBuf;
    OSDStringTypeDouble outbuf;
    #if ( ENABLE_ARABIC_OSD )
        OSDStringType out;
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
    U16 nFontID;
#endif
    FONTHANDLE Org_font_handle = font_handle;

//    U32 _timer = msAPI_Timer_GetTime0();

    // Abnormal condition
    if(max_row_num == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> max_row_num = 0\n"););
        return;
    }
    else if ((input_strlen = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> strlen = 0\n"););
        return;
    }


    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_GET_resource();
    //u8TempStr = (U16*)TempStr;

 #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) ||(ENABLE_TTF_FONT))

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
    #if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( bHebrewMixedMode )
                    {
                        bHebrew = TRUE;
                    }
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                    {
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                    }

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                    }
                }
            }

            if ( bHebrew == FALSE )
            {
                bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;

            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
            }
            else
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
            }
            break;
    #endif
    #if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;

            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }

    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
            }
            break;
    #endif
    /*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            break;
    */
#if ( ENABLE_TTF_FONT )
        //Currently Emphasis character effect and other control codes are not implemented in TTF font
        //We only support 0x8A new line chatacter
        case LANGUAGE_OSD_HINDI:
        //case LANGUAGE_OSD_URDU:
        case LANGUAGE_OSD_BENGALI:
        case LANGUAGE_OSD_TELUGU:
        case LANGUAGE_OSD_MARATHI:
        case LANGUAGE_OSD_TAMIL:
        case LANGUAGE_OSD_ASSAMESE:
        case LANGUAGE_OSD_GUJARATI:
        case LANGUAGE_OSD_KANNADA:
        case LANGUAGE_OSD_MALAYALAM:
        case LANGUAGE_OSD_PUNJABI:
        {
            msAPI_OSD_Free_resource();
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(TRUE);
            msAPI_OSD_DrawPunctuatedString(font_handle, (U16 *)((void *)pu8Str), pclrBtn, max_row_num);
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(FALSE);
        }

        return;

        break;
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_MYANMAR:
        case LANGUAGE_OSD_KHMER:
        case LANGUAGE_OSD_LAO:
        {
            msAPI_OSD_Free_resource();
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(TRUE);
            msAPI_OSD_DrawPunctuatedString_S1_NEW(font_handle, (void *)pu8Str, pclrBtn, max_row_num,FALSE);
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(FALSE);
        }
            return;
            break;
#endif
#endif

        default:
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            break;
    }
#endif

#if (ENABLE_ARABIC_OSD)
    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }

#endif

    if(pclrBtn->bStringIndexWidth==CHAR_IDX_1BYTE)
    {
        if (input_strlen >= sizeof(TempStr.U8Str))
        {
            input_strlen = sizeof(TempStr.U8Str) - 1;
        }

    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            U16 i;

            memcpy(out.U8Str, pu8Str, input_strlen);
            for(i = 0; i < input_strlen; i++)
            {
                TempBuf.U8Str[i] = out.U8Str[(input_strlen-1)-i];
            }
            TempBuf.U8Str[input_strlen] = 0;
            pu8Str = TempBuf.U8Str;
        }
        else
    #endif
        {
            //memcpy(TempBuf.U8Str,pu8Str,len);
        }
    }
    else
    {
    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
        if (input_strlen >= sizeof(TempBuf.U8Str)/2)
        {
            input_strlen = sizeof(TempBuf.U8Str)/2 - 1;
        }
    #endif

    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            memcpy(TempBuf.U8Str,pu8Str,input_strlen*2);
            TempBuf.U16Str[input_strlen] = 0;

            //For Subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //Every language is possible, you can't skip this filter here
                msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
            }
            else if ( bArabicDisplay ) //for OSD
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //just skip this function for non Kurdish condition
                if ( enLanguage == LANGUAGE_OSD_KURDISH )
                {
                    msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
                }
            }
            else    // for Hebrew
            {
                            memcpy(outbuf.U8Str, TempBuf.U8Str, input_strlen*2);
            }

                   outbuf.U16Str[input_strlen] = 0;
                   pu8Str = outbuf.U8Str;
            }

    #endif
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)(pclrBtn->Fontfmt.height / finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)(pclrBtn->Fontfmt.width / finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }
    else
    {
        scale = 1;
    }

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        //temp solution for compiler warning
        memcpy(TempBuf.U8Str, pu8Str, input_strlen*2);

        input_strlen = Thai_compose(TempBuf.U16Str, 0, input_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[input_strlen] = 0x0000;

        pu8Str = outbuf.U8Str;
    }
#endif

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
    {
    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        gap = pclrBtn->Fontfmt.ifont_gap;
    }
    else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
    {
        gap = -pclrBtn->Fontfmt.dis;
    }
    else
    {
        gap = 0;
    }

    bIsOneByteString        = (pclrBtn->bStringIndexWidth & CHAR_IDX_1BYTE) ? TRUE : FALSE;
    max_row_width           = pclrBtn->width - 2*BTN_TEXT_GAP;
    input_last_char_count   = 0;
    output_total_width      = 0;

    DBG_SMART_TEXT(printf("< Start > gap = %bd, input_strlen = %u\n", gap, input_strlen););

    // Row handle loop
    for (iRow=0, input_char_count=0; (iRow<max_row_num) && (input_char_count < input_strlen);)
    {
        if (iRow==1 && bSetNextLineStartInx == FALSE)
        {
            if(0xE08A == ReadU16LE(&pu8Str[input_char_count*2]))
            {
                u16NextLineStartInx = (input_char_count+1);
            }
            else
            {
                u16NextLineStartInx = input_char_count;
            }

            bSetNextLineStartInx = TRUE;
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("< iRow = %u > input_char_count = %u, input_strlen = %u\n", iRow, input_char_count, input_strlen););
        }

        // Reset variable
        output_char_count       = 0;
        output_last_char_count  = 0;
        output_last_total_width = 0;
        bIsChar_CRLF            = FALSE;
        bIsChar_SHY             = FALSE;
        bIsChar_LastSHY         = FALSE;
        bIsChar_0x86            = FALSE;
        bIsChar_0x87            = FALSE;
        bIsChar_Normal          = FALSE;

        // Filter one word (end with space or control code)
        while ( (output_total_width<max_row_width) && (input_char_count < input_strlen) && ( output_char_count < (STROSD-1)))
        {
            if (bIsOneByteString)   // One byte string
            {
                input_char_data = pu8Str[input_char_count];
                // Contrl code, SHY or space char
                if ((0x20==input_char_data) || ((0x80<=input_char_data)&&(input_char_data<=0x9F)) )
                {
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0x8A==input_char_data )            // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0x86==input_char_data )       // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0x87==input_char_data )       // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        pu8Str[input_char_count]  = 0x20;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal      = TRUE;
                }
            }
            else    // Two bytes string
            {
                //input_char_data = pu16Str[input_char_count];
                input_char_data = (pu8Str[input_char_count*2+1]<<8) + pu8Str[input_char_count*2];
                if ( 0x00AD==input_char_data)               // SHY - soft hyphen
                {
                      bIsSpecialCharacterUsed=TRUE;
                    DBG_SMART_TEXT(printf ("<< SHY [%2u] 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_SHY     = TRUE;
                    bIsChar_LastSHY = TRUE;
                }
                else if ((0x0020==input_char_data) || ( (0xE080<=input_char_data) && (input_char_data<=0xE09F) ) )
                {
                       bIsSpecialCharacterUsed=TRUE;
                    DBG_SMART_TEXT(printf ("<< Control Code [%2u] = 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_LastSHY         = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0xE08A==input_char_data )          // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0xE086==input_char_data )     // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0xE087==input_char_data )     // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        //pu16Str[input_char_count] = 0x0020;
                        pu8Str[input_char_count*2] = 0x20;
                        pu8Str[input_char_count*2+1] = 0x00;
                    }
                }
                  else if (bIsSpecialCharacterUsed==FALSE && (output_total_width + input_char_width >= max_row_width))
                  {


                    bIsChar_LastSHY         = FALSE;
                      input_last_char_count   = input_char_count-1;
                      output_last_char_count  = output_char_count;    // Save the char count to last control char
                      output_last_total_width = output_total_width;   // Save the display width to last control char
                      bIsChar_CRLF        = TRUE;
                  }
                else                                         // Normal char
                {
                    bIsChar_Normal          = TRUE;
                }
            }

            // Retrieve input char width or add null char
            if (bIsChar_Normal || bIsChar_SHY)
            {
                if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
                {
                    if (bIsOneByteString)   // One byte string
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[input_char_count], &BBox_X_Info);
                    }
                    else
                    {
                    #if (ENABLE_ARABIC_OSD)
                        //For Subtitle
                        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
                        {
                            U16 u16Unicode;

                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                u16Unicode = (pu8Str[input_char_count*2-1]<<8) + pu8Str[input_char_count*2-2];

                                if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    //in Arabic language mode, gap is always zero, so we can forget gap value
                                    output_total_width -= (BBox_X_Info.u8Width*scale+gap);
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else if ( bArabicDisplay ) //for OSD
                        {
                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                if ( msAPI_OSD_IsArabicVowel( input_char_data ) )
                                {
                                    //skip current vowel character width
                                    //do nothing here
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                    #if (ENABLE_THAI_OSD)
                        if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
                        {
                            // Check Primary Thai unicode range
                            if ( ( input_char_data <= 0x0E5B ) && ( input_char_data >= 0x0E01 ) )
                            {
                                if ( MinusDrawTable[ input_char_data - 0x0E01 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else if ( ( input_char_data <= 0xF71A ) && ( input_char_data >= 0xF700 ) )
                            {
                                if ( MinusDrawTablePersentation[ input_char_data - 0xF700 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                            input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                        }
                    }
                }
                else
                {
                    input_char_width = finfo.width;
                    input_char_width = (output_char_count==0) ? (finfo.width) : (finfo.width*scale+gap);
                }

                bIsChar_Normal = FALSE;
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_char_count] = 0;
                    u8TempStr[output_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_char_count] = 0;
                    u8TempStr[output_char_count*2] = 0;
                    u8TempStr[output_char_count*2+1] = 0;
                }

                input_char_count++;
                break;
            }

            // check if string width larger than OSD display width
            if ((output_total_width+input_char_width) < max_row_width)
            {
                if (bIsChar_SHY)    // add normal char and space
                {
                    // Save temporary Last SHY char position for display
                    bIsChar_SHY             = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char
                }
                else                // space and other char
                {
                    if(bIsOneByteString)
                    {
                        //((U8*)u8TempStr)[output_char_count++] = pu8Str[input_char_count];
                        u8TempStr[output_char_count++] = pu8Str[input_char_count];
                    }
                    else
                    {
                        //u8TempStr[output_char_count++] = pu16Str[input_char_count];
                        u8TempStr[(output_char_count)*2] = pu8Str[input_char_count*2];
                        u8TempStr[(output_char_count)*2+1] = pu8Str[input_char_count*2+1];
                        output_char_count++;
                    }
                    output_last_char_count  = output_char_count;

                    output_total_width += input_char_width;
                }

                //if (g_EpgTest)
                {
                    DBG_SMART_TEXT(printf("pu16Str[%2u]= 0x%04x(%c), input_char_width = %02u, last_total_width = %4u, output_total_width = %4u, max_row_width =%4u\n", input_char_count, pu16Str[input_char_count], (U8)pu16Str[input_char_count], input_char_width, output_last_total_width, output_total_width, max_row_width););
                }

                input_char_count++;
                if (input_char_count>=input_strlen)     // Draw to the last char
                {
                    bIsChar_LastSHY = FALSE;
                #if(!ENABLE_ARABIC_OSD && !ENABLE_THAI_OSD)
                    {
#if(ENABLE_DTV_EPG  && ENABLE_DVB)
                        if(MApp_ZUI_API_IsWindowVisible(HWND_EPG_INFO_DESC_TEXT))
                        {
                            if(_u8InfoScrollLineCount <= (MApp_ZUI_ACT_EPGGetDescInfoPageNum() - 1))
                            {
                                if(bIsOneByteString)
                                {
                                    u8TempStr[output_last_char_count] = 0;
                                }
                                else
                                {
                                    u8TempStr[output_last_char_count*2] = 0;
                                    u8TempStr[output_last_char_count*2+1] = 0;
                                }
                            }
                        }
#endif
                    }
                #endif
                    break;
                }
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count*2] = 0;
                    u8TempStr[output_last_char_count*2+1] = 0;
                }
                input_last_char_count   = input_char_count-1;
                break;
            }
        }           // End of while loop

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("1 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
        }

        // Draw text to last control char or space char
        //if ( (output_last_char_count > 0) || (output_char_count > 0))
        {
            // Control code handle
            if (bIsChar_0x86 || bIsChar_0x87)          // character emphasis on/off
            {
                msAPI_OSD_Draw2BytesText(Org_font_handle, u8TempStr, pclrBtn);

                pclrBtn->x = u16OriginalPosition_x + output_last_total_width;

                if (bIsChar_0x86)
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_BOLD;
                }
                else
                {
                    pclrBtn->Fontfmt.flag = u16OriginalFontfmtFlag;
                }
            }
            else
            {
                if(bIsChar_LastSHY && ((pu8Str[input_last_char_count*2+1]<<8) + pu8Str[input_last_char_count*2] == 0x20) )
                    bIsChar_LastSHY = FALSE;

                if (bIsChar_LastSHY)        // Last SHY - soft hyphen
                {
                    u8TempStr[output_last_char_count*2]   = 0xAD; //0x00AD
                    u8TempStr[(output_last_char_count*2)+1] = 0x00;
                    u8TempStr[(output_last_char_count*2)+2] = 0x00; //0x0000
                    u8TempStr[(output_last_char_count*2)+3] = 0x00;

                }
                else                        // Space char or other
                {
                    u8TempStr[(output_char_count*2)]   = 0;
                    u8TempStr[(output_char_count*2)+1]   = 0;
                }

                msAPI_OSD_Draw2BytesText(font_handle, u8TempStr, pclrBtn);
                pclrBtn->x  = u16OriginalPosition_x;
                pclrBtn->y += pclrBtn->height;
                output_total_width     = 0;
                  bIsSpecialCharacterUsed = FALSE;
                iRow++;
            }
            offset_len = 1; // the var needs to be initialized
#if(ENABLE_DTV_EPG)

            if (input_char_count < input_strlen)
            {
                input_char_count = input_last_char_count+1;
                //fixed risk test bug, when play T49 channel of 3458_24.ts,it will show error epg message in second page.mantis:0285711
                u16RecordOnePageByte[_u8InfoScrollLineCount] = input_char_count;
            }
            else
            {

                u16RecordOnePageByte[_u8InfoScrollLineCount] = (input_last_char_count+1);
            }
#endif
        }

        #if ENABLE_RIKS_TV
        //fixed risk test bug, when play T49 channel of 3458_24.ts,it will repeat show info .mantis:0874961
        if (iRow==2 && bSetNextLineStartInx == TRUE)
        {
            if(0xE08A == ReadU16LE(&pu8Str[input_char_count*2]))
            {
                u16NextLineStartInx = (input_char_count+1);
            }
            else
            {
                u16NextLineStartInx = input_char_count;
            }

            bSetNextLineStartInx = TRUE;
        }
        #endif

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("2 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
            DBG_SMART_TEXT(printf ("<< (x, y) = (%4u, %4u) >>\n", pclrBtn->x, pclrBtn->y););
        }

        if (input_char_count < input_strlen)
        {
            bStopScrollDown = FALSE;
        }
        else
        {
            bStopScrollDown = TRUE;
        }
    }

    pclrBtn->y = u16OriginalPosition_y;

    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_Free_resource();

    //printf ("Time = %lu\n", _timer = msAPI_Timer_DiffTimeFromNow(_timer));
}
#endif

void msAPI_OSD_DrawPunctuatedString_S2(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num)
{
    S8  gap;
    U16 iRow;
    U8  scale, offset_len;
    U16 input_strlen;
    U16 input_char_count, input_last_char_count, output_char_count, output_last_char_count;
    U16 input_char_width, output_total_width, output_last_total_width, max_row_width;
    //U16 *u8TempStr;
    U8 u8TempStr[STROSD*2];
    U16 input_char_data = 0;

    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    BOOLEAN bIsOneByteString;
    BOOLEAN bSetNextLineStartInx    = FALSE;
    BOOLEAN bIsChar_CRLF    = FALSE;
    BOOLEAN bIsChar_0x86    = FALSE;
    BOOLEAN bIsChar_0x87    = FALSE;
    BOOLEAN bIsChar_SHY     = FALSE;
    BOOLEAN bIsChar_LastSHY = FALSE;
    BOOLEAN bIsChar_Normal  = FALSE;

    U16 u16OriginalPosition_x   = pclrBtn->x;
    U16 u16OriginalPosition_y   = pclrBtn->y;
    U16 u16OriginalFontfmtFlag  = pclrBtn ->Fontfmt.flag;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringType TempBuf;
    OSDStringTypeDouble outbuf;
    #if ( ENABLE_ARABIC_OSD )
        OSDStringType out;
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
    U16 nFontID;
#endif
    FONTHANDLE Org_font_handle = font_handle;

//    U32 _timer = msAPI_Timer_GetTime0();

    // Abnormal condition
    if(max_row_num == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> max_row_num = 0\n"););
        return;
    }
    else if ((input_strlen = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> strlen = 0\n"););
        return;
    }


    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_GET_resource();
    //u8TempStr = (U16*)TempStr;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) ||(ENABLE_TTF_FONT))
#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
    #if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
        case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( bHebrewMixedMode )
                    {
                        bHebrew = TRUE;
                    }
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                    {
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                    }

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                    }
                }
            }

            if ( bHebrew == FALSE )
            {
                bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
            }
            else
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
            }
            break;
    #endif
    #if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;

            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }

    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
            }
            break;
    #endif
    /*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            break;
    */
#if ( ENABLE_TTF_FONT )
            //Currently Emphasis character effect and other control codes are not implemented in TTF font
            //We only support 0x8A new line chatacter
        case LANGUAGE_OSD_HINDI:
        //case LANGUAGE_OSD_URDU:
        case LANGUAGE_OSD_BENGALI:
        case LANGUAGE_OSD_TELUGU:
        case LANGUAGE_OSD_MARATHI:
        case LANGUAGE_OSD_TAMIL:
        case LANGUAGE_OSD_MYANMAR:
        case LANGUAGE_OSD_KHMER:
        case LANGUAGE_OSD_LAO:
        case LANGUAGE_OSD_ASSAMESE:
        case LANGUAGE_OSD_GUJARATI:
        case LANGUAGE_OSD_KANNADA:
        case LANGUAGE_OSD_MALAYALAM:
        case LANGUAGE_OSD_PUNJABI:
        {
            msAPI_OSD_Free_resource();
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(TRUE);
            msAPI_OSD_DrawPunctuatedString(font_handle, (U16 *)((void *)pu8Str), pclrBtn, max_row_num);
            msAPI_OSD_SetPunctuatedStringS1S2EndingType(FALSE);
        }

        return;

        break;
#endif

        default:
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            break;
    }
#endif

#if (ENABLE_ARABIC_OSD)
    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }
#endif

    if(pclrBtn->bStringIndexWidth==CHAR_IDX_1BYTE)
    {
        if (input_strlen >= sizeof(TempStr.U8Str))
        {
            input_strlen = sizeof(TempStr.U8Str) - 1;
        }

    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            U16 i;

            memcpy(out.U8Str, pu8Str, input_strlen);
            for(i = 0; i < input_strlen; i++)
            {
                TempBuf.U8Str[i] = out.U8Str[(input_strlen-1)-i];
            }
            TempBuf.U8Str[input_strlen] = 0;
            pu8Str = TempBuf.U8Str;
        }
        else
        {
    #endif
            //memcpy(TempBuf.U8Str,pu8Str,len);
    #if (ENABLE_ARABIC_OSD)
        }
    #endif
    }
    else
    {
    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )

        if (input_strlen >= sizeof(TempBuf.U8Str)/2)
        {
            input_strlen = sizeof(TempBuf.U8Str)/2 - 1;
        }

    #endif

    #if (ENABLE_ARABIC_OSD)

        if ( bMirrorLang )
        {
            memcpy(TempBuf.U8Str,pu8Str,input_strlen*2);
            TempBuf.U16Str[input_strlen] = 0;

            //For Subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //Every language is possible, you can't skip this filter here
                msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
                msAPI_OSD_UrduFilter(outbuf.U16Str, input_strlen);
            }
            else if ( bArabicDisplay ) //for OSD
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //just skip this function for non Kurdish condition
                if ( enLanguage == LANGUAGE_OSD_KURDISH )
                {
                    msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
                }
                else if ( enLanguage == LANGUAGE_OSD_URDU )
                {
                    msAPI_OSD_UrduFilter(outbuf.U16Str, input_strlen);
                }
            }
            else    // for Hebrew
            {
                memcpy(outbuf.U8Str, TempBuf.U8Str, input_strlen*2);
            }

            outbuf.U16Str[input_strlen] = 0;
            pu8Str = outbuf.U8Str;
        }

    #endif
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)(pclrBtn->Fontfmt.height / finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)(pclrBtn->Fontfmt.width / finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }
    else
    {
        scale = 1;
    }

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        //temp solution for compiler warning
        memcpy(TempBuf.U8Str, pu8Str, input_strlen*2);

        input_strlen = Thai_compose(TempBuf.U16Str, 0, input_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[input_strlen] = 0x0000;

        pu8Str = outbuf.U8Str;
    }
#endif

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
    {
    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        gap = pclrBtn->Fontfmt.ifont_gap;
    }
    else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
    {
        gap = -pclrBtn->Fontfmt.dis;
    }
    else
    {
        gap = 0;
    }

    bIsOneByteString        = (pclrBtn->bStringIndexWidth & CHAR_IDX_1BYTE) ? TRUE : FALSE;
    max_row_width           = pclrBtn->width - 2*BTN_TEXT_GAP;
    input_last_char_count   = 0;
    output_total_width      = 0;

    DBG_SMART_TEXT(printf("< Start > gap = %bd, input_strlen = %u\n", gap, input_strlen););

    // Row handle loop
    for (iRow=0, input_char_count=0; (iRow<max_row_num) && (input_char_count < input_strlen);)
    {
        if (iRow==1  && bSetNextLineStartInx == FALSE)
        {
            u16NextLineStartInx = input_char_count;
            bSetNextLineStartInx = TRUE;
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("< iRow = %u > input_char_count = %u, input_strlen = %u\n", iRow, input_char_count, input_strlen););
        }

        // Reset variable
        output_char_count       = 0;
        output_last_char_count  = 0;
        output_last_total_width = 0;
        bIsChar_CRLF            = FALSE;
        bIsChar_SHY             = FALSE;
        bIsChar_LastSHY         = FALSE;
        bIsChar_0x86            = FALSE;
        bIsChar_0x87            = FALSE;
        bIsChar_Normal          = FALSE;

        // Filter one word (end with space or control code)
        while ( (output_total_width<max_row_width) && (input_char_count < input_strlen) && ( output_char_count < (STROSD-2)))
        {
            if (bIsOneByteString)   // One byte string
            {
                input_char_data = pu8Str[input_char_count];
                // Contrl code, SHY or space char
                if ((0x20==input_char_data) || ((0x80<=input_char_data)&&(input_char_data<=0x9F)) )
                {
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0x8A==input_char_data )            // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0x86==input_char_data )       // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0x87==input_char_data )       // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        pu8Str[input_char_count]  = 0x20;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal      = TRUE;
                }
            }
            else    // Two bytes string
            {
                //input_char_data = pu16Str[input_char_count];
                input_char_data = (pu8Str[input_char_count*2+1]<<8) + pu8Str[input_char_count*2];
                if ( 0x00AD==input_char_data)               // SHY - soft hyphen
                {
                    DBG_SMART_TEXT(printf ("<< SHY [%2u] 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_SHY     = TRUE;
                    bIsChar_LastSHY = TRUE;
                }
                else if ((0x0020==input_char_data) || ( (0xE080<=input_char_data) && (input_char_data<=0xE09F) ) )
                {
                    DBG_SMART_TEXT(printf ("<< Control Code [%2u] = 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_LastSHY         = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0xE08A==input_char_data )          // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0xE086==input_char_data )     // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0xE087==input_char_data )     // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        //pu16Str[input_char_count] = 0x0020;
                        pu8Str[input_char_count*2] = 0x20;
                        pu8Str[input_char_count*2+1] = 0x00;
                    }
                }
                /////////////////////////////////////////////////////////////////////////////////
                //else if( (0x000D == input_char_data) && (0x000A == pu16Str[input_char_count+1]) )
                else if( (0x000D == input_char_data) && (0x000A == ((pu8Str[input_char_count*2+3]<<8) + pu8Str[input_char_count*2])) )
                {
                    bIsChar_LastSHY = TRUE;
                }
                /////////////////////////////////////////////////////////////////////////////////
                else                                        // Normal char
                {
                    bIsChar_Normal          = TRUE;
                }
            }

            // Retrieve input char width or add null char
            if (bIsChar_Normal || bIsChar_SHY)
            {
                if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
                {
                    if (bIsOneByteString)   // One byte string
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[input_char_count], &BBox_X_Info);
                    }
                    else
                    {
                    #if (ENABLE_ARABIC_OSD)
                        //For Subtitle
                        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
                        {
                            U16 u16Unicode;

                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                u16Unicode = (pu8Str[input_char_count*2-1]<<8) + pu8Str[input_char_count*2-2];

                                if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    //in Arabic language mode, gap is always zero, so we can forget gap value
                                    output_total_width -= (BBox_X_Info.u8Width*scale+gap);
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else if ( bArabicDisplay ) //for OSD
                        {
                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                if ( msAPI_OSD_IsArabicVowel( input_char_data ) )
                                {
                                    //skip current vowel character width
                                    //do nothing here
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                    #if (ENABLE_THAI_OSD)
                        if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
                        {
                            // Check Primary Thai unicode range
                            if ( ( input_char_data <= 0x0E5B ) && ( input_char_data >= 0x0E01 ) )
                            {
                                if ( MinusDrawTable[ input_char_data - 0x0E01 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else if ( ( input_char_data <= 0xF71A ) && ( input_char_data >= 0xF700 ) )
                            {
                                if ( MinusDrawTablePersentation[ input_char_data - 0xF700 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                            input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                        }
                    }
                }
                else
                {
                    input_char_width = finfo.width;
                    input_char_width = (output_char_count==0) ? (finfo.width) : (finfo.width*scale+gap);
                }

                bIsChar_Normal = FALSE;
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_char_count] = 0;
                    u8TempStr[output_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_char_count] = 0;
                    u8TempStr[output_char_count*2] = 0;
                    u8TempStr[output_char_count*2+1] = 0;
                    /////////////////////////////////////////////////////////////////////////////////
                    input_char_count++;
                    output_last_char_count   = output_char_count;
                    input_last_char_count = input_char_count;
                    break;
                    /////////////////////////////////////////////////////////////////////////////////
                }

                input_char_count++;
                break;
            }

            // check if string width larger than OSD display width
            if ((output_total_width+input_char_width) < max_row_width)
            {
                if (bIsChar_SHY)    // add normal char and space
                {
                    // Save temporary Last SHY char position for display
                    bIsChar_SHY             = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char
                }
                else                // space and other char
                {
                    if(bIsOneByteString)
                    {
                        //((U8*)u8TempStr)[output_char_count++] = pu8Str[input_char_count];
                        u8TempStr[output_char_count++] = pu8Str[input_char_count];
                    }
                    else
                    {
                        //u8TempStr[output_char_count++] = pu16Str[input_char_count];
                        u8TempStr[(output_char_count++)*2] = pu8Str[input_char_count*2];
                        u8TempStr[(output_char_count++)*2+1] = pu8Str[input_char_count*2+1];
                        /////////////////////////////////////////////////////////////////////////////////
                        output_last_char_count   = output_char_count;
                        input_last_char_count = input_char_count;
                        /////////////////////////////////////////////////////////////////////////////////
                    }

                    output_total_width += input_char_width;
                }

                //if (g_EpgTest)
                {
                    DBG_SMART_TEXT(printf("pu16Str[%2u]= 0x%04x(%c), input_char_width = %02u, last_total_width = %4u, output_total_width = %4u, max_row_width =%4u\n", input_char_count, pu16Str[input_char_count], (U8)pu16Str[input_char_count], input_char_width, output_last_total_width, output_total_width, max_row_width););
                }

                input_char_count++;
                if (input_char_count>=input_strlen)     // Draw to the last char
                {
                    bIsChar_LastSHY = FALSE;
                    break;
                }
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count*2] = 0;
                    u8TempStr[output_last_char_count*2+1] = 0;
                }
                break;
            }
        }           // End of while loop

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("1 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
        }

        // Draw text to last control char or space char
        //if ( (output_last_char_count > 0) || (output_char_count > 0))
        {
            // Control code handle
            if (bIsChar_0x86 || bIsChar_0x87)          // character emphasis on/off
            {
                msAPI_OSD_Draw2BytesText(Org_font_handle, u8TempStr, pclrBtn);

                pclrBtn->x = u16OriginalPosition_x + output_last_total_width;

                if (bIsChar_0x86)
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_BOLD;
                }
                else
                {
                    pclrBtn->Fontfmt.flag = u16OriginalFontfmtFlag;
                }
            }
            else
            {
                if (bIsChar_LastSHY)        // Last SHY - soft hyphen
                {
                    u8TempStr[output_last_char_count*2]   = 0xAD; //0x00AD
                    u8TempStr[(output_last_char_count*2)+1] = 0x00;
                    u8TempStr[(output_last_char_count*2)+2] = 0x00; //0x0000
                    u8TempStr[(output_last_char_count*2)+3] = 0x00;
                }
                else                        // Space char or other
                {
                    u8TempStr[(output_char_count*2)]   = 0;
                    u8TempStr[(output_char_count*2)+1]   = 0;
                }

                msAPI_OSD_Draw2BytesText(Org_font_handle, u8TempStr, pclrBtn);
                pclrBtn->x  = u16OriginalPosition_x;
                pclrBtn->y += pclrBtn->height;
                output_total_width     = 0;
                iRow++;
            }

            if(bIsOneByteString)
                offset_len = 1;
            else
                offset_len = 2; // the var needs to be initialized
            if (input_char_count < input_strlen)
            {
                input_char_count = input_last_char_count+1;
                pu8Str += (input_last_char_count*offset_len);
            }
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("2 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
            DBG_SMART_TEXT(printf ("<< (x, y) = (%4u, %4u) >>\n", pclrBtn->x, pclrBtn->y););
        }

        if (input_char_count < input_strlen)
        {
            bStopScrollDown = FALSE;
        }
        else
        {
            bStopScrollDown = TRUE;
        }
    }

    pclrBtn->y = u16OriginalPosition_y;

    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_Free_resource();

    //printf ("Time = %lu\n", _timer = msAPI_Timer_DiffTimeFromNow(_timer));
}

#if ( ENABLE_TTF_FONT )
static U32 msAPI_OSD_GetTableStrLength( Mle_TextTable_t *pITextTable )
{
    Text_LineData_t sLineData = {0,0,0};
    U32 u32TableSize = 0;
    U32 u32ReturnLen = 0;
    U32 i = 0;

    if ( pITextTable == NULL )
    {
        return 0;
    }

    u32TableSize = msAPI_MLE_TextTableGetSize( pITextTable );

    for ( i = 0; i < u32TableSize; i++ )
    {
        if ( msAPI_MLE_TextTableGetLine(pITextTable, i, &sLineData) == MLE_RET_SUCCESS )
        {
            u32ReturnLen = u32ReturnLen + sLineData.nLength;
        }
    }

    return u32ReturnLen;
}

static U32 msAPI_OSD_CatLines( Mle_TextTable_t *pITextTable, U32 *pu32Pixels, U16 **ppu16String )
{
    U32 u32LineLength = 0;
    U32 u32LineWidth = 0;
    BOOLEAN bLineRTL = FALSE;
    U16 *pu16LineStr = NULL;
    U32 u32TableSize = 0;
    U32 u32CatStrLen = 0;
    U32 u32CharCount = 0;
    U32 u32Width = 0;
    U16 *pu16CatString = NULL;
    BOOLEAN bIsCatOnLeft = FALSE;
    U32 i = 0;
    //FontInfo sFontInf = {0, 0, 0, 0};

    do
    {
        if ( pITextTable == NULL )
        {
            break;
        }

        u32CatStrLen = msAPI_OSD_GetTableStrLength( pITextTable );
        if ( u32CatStrLen == 0 )
        {
            break;
        }

        //ITEXTTABLE_GetFontInf(pITextTable, 0, 0, FONT_TYPE_NORMAL, &sFontInf);

        if ( ppu16String )
        {
            pu16CatString = (U16 *)MALLOC( sizeof(U16) * u32CatStrLen );
        }

        u32TableSize = msAPI_MLE_TextTableGetSize( pITextTable );
        for ( i = 0; i < u32TableSize; i++ )
        {
            u32LineLength = msAPI_MLE_TextTableGetLineDispStr( pITextTable, i, &pu16LineStr, &u32LineWidth, &bLineRTL, TRUE );
            if ( u32LineLength == 0)
            {
                break;
            }

            //if ( i == 0 && !FONT_IS_NO_CONVERT_RTL(sFontInf.nTag) )
            if ( i == 0 )
            {
                bIsCatOnLeft = bLineRTL;
            }

            if ( ppu16String && (pu16CatString != NULL) )
            {
                if ( bIsCatOnLeft )
                {
                    MEMCPY( (void *)(pu16CatString + u32LineLength), pu16CatString, sizeof(U16) * u32CharCount );
                    MEMCPY( (void *)pu16CatString, pu16LineStr, sizeof(U16) * u32LineLength );

                    //if ( bIsCatOnLeft != bLineRTL && !FONT_IS_NO_CONVERT_RTL(sFontInf.nTag) )
                    if ( bIsCatOnLeft != bLineRTL )
                    {
                        msAPI_MLE_TEXTUTIL_UCS2Invert( pu16CatString, u32LineLength, 0, u32LineLength, NULL );
                    }
                }
                else
                {
                    MEMCPY( (void *)(pu16CatString + u32CharCount), pu16LineStr, sizeof(U16) * u32LineLength );

                    //if ( bIsCatOnLeft != bLineRTL && !FONT_IS_NO_CONVERT_RTL(sFontInf.nTag) )
                    if ( bIsCatOnLeft != bLineRTL )
                    {
                        msAPI_MLE_TEXTUTIL_UCS2Invert( (U16 *)(pu16CatString + u32CharCount), u32LineLength, 0, u32LineLength, NULL );
                    }
                }
            }

            FREEIF( pu16LineStr );
            u32CharCount = u32CharCount + u32LineLength;
            u32Width = u32Width + u32LineWidth;
        }
    } while (FALSE);

    if ( ppu16String )
    {
        *ppu16String = pu16CatString;
    }

    if ( pu32Pixels )
    {
        *pu32Pixels = u32Width;
    }

    return u32CatStrLen;
}

static MLE_Ret msAPI_OSD_MeasureEllipsis(U32 nFontSize, U32 u32FontType, EN_STRING_ENDING_TYPE enEndingType, U32 *pu32Width )
{
    U32 u32EllipsisFits = 0;
    U32 u32EllipsisPixels = 0;
    MLE_Ret eRet = MLE_RET_SUCCESS;

    //Get the Pixels that Ellipsis string needs
    eRet = msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize,
            COMMON_ELLIPSIS_STRING,
            enEndingType,
            0,
            enEndingType,
            0, //(U32)(-1),     // if nMaxWidth == 0, means nMaxWidth is not defined
            &u32EllipsisFits,
            &u32EllipsisPixels,
            u32FontType,
            FALSE,
            FALSE);

    if( MLE_RET_SUCCESS != eRet )
    {
        OSDTTF_TRACE(printf("%d eRet=%x\n", __LINE__, eRet));
        *pu32Width = 0;
    }
    else
    {
        OSDTTF_TRACE(printf("%d u32EllipsisFits=%d u32EllipsisPixels=%d\n", __LINE__, u32EllipsisFits, u32EllipsisPixels));
        *pu32Width = u32EllipsisPixels;
    }

    return eRet;
}

static BOOLEAN msAPI_OSD_MeasureTextY(U32 nFontSize, U32 u32Height, S32 *ps32Y, U32 *pu32Rows, U32 *pu32FontHeight, BOOLEAN bMultiLine)
{
    FontInfo sfontInfo = {0, 0, 0, 0};
    U32 u32RealFontHeight;
    U32 u32Rows = 0;
    U32 u32TextHeight = 0;
    S32 s32StartY = 0;
    BOOLEAN bResult = FALSE;

    do
    {
        //Get Font Height
        msAPI_MLE_FONTBASE_Vector_GetInfo(nFontSize, FONT_TYPE_NORMAL, &sfontInfo);
        u32RealFontHeight = sfontInfo.nHeight;
        ///sfontInfo.nHeight = MAX(sfontInfo.nHeight,pThis->fontInfo.MinFontHeight);

        //decide the maximun number of line
        if( bMultiLine )
        {
            u32Rows = u32Height/sfontInfo.nHeight;

            if ( (u32Rows * sfontInfo.nHeight) + u32RealFontHeight <= u32Height )
            {
                u32Rows++;
                OSDTTF_TRACE(printf("%d %s u32Rows=%d\n", __LINE__, __FUNCTION__, u32Rows));
            }
            if ( u32Rows == 0 )
            {
                //This is a patch for Chakra series ZUI, even u32Rows = 0, but actually we can have enough space to draw one line string
                //Because the actual string height is not so big
                OSDTTF_TRACE(printf("%d %s u32Rows=%d u32Height=%d sfontInfo.nHeight=%d, sfontInfo.nAscent=%d, sfontInfo.nDescent=%d\n", __LINE__, __FUNCTION__, u32Rows, u32Height, sfontInfo.nHeight, sfontInfo.nAscent, sfontInfo.nDescent ));
                //break;
                u32Rows = 1;
            }
        }
        else
        {
            u32Rows = 1;
        }

        //check the actually number of rows;
        if ( pMleTextTable )
        {
            U32 u32TableSize = 0;

            u32TableSize = msAPI_MLE_TextTableGetSize(pMleTextTable);
            if( u32Rows > u32TableSize )
                u32Rows = u32TableSize;
        }

        if( u32Rows > 0 )
        {
            u32TextHeight = ((u32Rows - 1) * sfontInfo.nHeight) + u32RealFontHeight;
        }

        //Chakra series only support align middle in vertical direction
        if ( ps32Y )
        {
#if 0
            switch( pclrBtn->enTextAlign )
            {
                case ALIGN_V_BOTTOM:
                    //check the actually number of rows;
                    s32StartY = (s32)(u32Height - u32TextHeight);
                    break;
                case ALIGN_V_MIDDLE:
#endif
                    //check the actually number of rows;
                    s32StartY = ((S32)(u32Height - u32TextHeight)/2);
                    OSDTTF_TRACE(printf("s32StartY=%d\n", s32StartY));
#if 0
                    break;
                case ALIGN_V_TOP:
                default:
                    s32StartY = 0;
                    break;
            }
#endif
        }
        bResult = TRUE;
    }while ( FALSE );

    if ( pu32Rows )
    {
        *pu32Rows = u32Rows;
    }

    if ( ps32Y )
    {
        *ps32Y = s32StartY;
    }

    if ( pu32FontHeight )
    {
        *pu32FontHeight = sfontInfo.nHeight;
    }
    return bResult;
}

static BOOLEAN msAPI_OSD_MeasureLineX( U32 u32FontSize,
                                       U16 *pu16Str,
                                       U16 u16Strlen,
                                       U32 u32Index,
                                       OSDClrBtn *pclrBtn,
                                       BOOLEAN *pbIsRTLLang,
                                       U16 **ppu16Str,
                                       U32 *pu32FitLen,
                                       U32 *pu32FitWidth,
                                       S32 *ps32X,
                                       U32 *u32Ell,
                                       BOOLEAN *pbIsRTLStr,
                                       EN_STRING_ENDING_TYPE enEndingType,
                                       BOOLEAN bIsLastDisplayLine )
{
    U32 u32EllPix = 0;
    U32 u32LineLen = 0;
    U32 u32LineWidth = 0;
    U32 u32TableSize;
    S32 s32LineX = 0;
    BOOLEAN bIsRTL = FALSE;
    BOOLEAN bIsRTLLang = FALSE;
    U16 *pu16TempStr = NULL;
    U32 u32FitLen = 0;
    U32 u32FitWidth = 0;
    BOOLEAN bReturnValue = FALSE;
    BOOLEAN bIsDisplayStr = FALSE;
    S32 s32XStartPos = 0;

    do
    {
#ifdef __BIDI_TEXT__
        //if ( !pThis->bWithoutBidi )
        {
            bIsRTLLang = msAPI_MLE_TEXTUTIL_IsRTLDisplayLanguage();
        }
#endif //__BIDI_TEXT__
        if ( pMleTextTable )
        {
            bIsDisplayStr = TRUE;
            u32TableSize = msAPI_MLE_TextTableGetSize( pMleTextTable );
            if ( u32TableSize == 0 )
            {
                break;
            }

            u32LineLen = msAPI_MLE_TextTableGetLineDispStr( pMleTextTable, u32Index, &pu16TempStr, &u32LineWidth, &bIsRTL, TRUE );
            if ( u32LineLen == 0 )
            {
                break;
            }

            //In Chakra 3, multiline case won't have a chance to go without LAYOUT_MULTILINE flag.
            //Only multiline case will set pMleTextTable to be non-NULL, so we did a modification here
            //if ( (pThis->textLayout & LAYOUT_MULTILINE) != LAYOUT_MULTILINE && u32Index == 0 && u32TableSize > 1 )
            if ( 0 )
            {
                FREE( pu16TempStr );
                u32LineLen = msAPI_OSD_CatLines( pMleTextTable, &u32LineWidth, &pu16TempStr );
                u32TableSize = 1;
            }
        }
        else
        {
            //measure the number of chars could fit in the nWidth
            u32LineLen = u16Strlen;

            if ( u32LineLen == 0 )
            {
                break;
            }

#ifdef __BIDI_TEXT__
            //if ( !pThis->bWithoutBidi && msAPI_MLE_TEXTUTIL_IsArabicText(pu16Str, u32LineLen) )
            if ( msAPI_MLE_TEXTUTIL_IsArabicText(pu16Str, u32LineLen) )
            {
                //in bengali language return length is different from param 2 str length
                u32LineLen = msAPI_MLE_TEXTUTIL_TextToDisplayString( pu16Str, u32LineLen, bIsRTLLang, &pu16TempStr, &bIsRTL, FALSE );
            }
            else
#endif
            {
                //in bengali language return length is different from param 2 str length
                u32LineLen = msAPI_MLE_TEXTUTIL_TextToDisplayString( pu16Str, u32LineLen, bIsRTLLang, &pu16TempStr, &bIsRTL, TRUE );
            }
            bIsDisplayStr = TRUE;

            u32TableSize = 1;
            msAPI_MLE_FONTBASE_Vector_MeasureText(u32FontSize,
                                                  pu16TempStr,
                                                  u32LineLen,
                                                  0,
                                                  u32LineLen,
                                                  0, //maximum
                                                  &u32LineLen,
                                                  &u32LineWidth,
                                                  FONT_TYPE_NORMAL,
                                                  FALSE,
                                                  bIsDisplayStr);
        }
        //printf("%d pclrBtn->width=%d u32LineWidth=%d\n", __LINE__, pclrBtn->width, u32LineWidth);

        // Check is the last line with ell
//          if( ((pThis->textLayout & LAYOUT_ELLIPSIS)) &&
//                ((u32Width < u32LineWidth) ||  //only for one line
//                 ((pThis->textLayout & LAYOUT_MULTILINE) &&  //only for multi-line
//                  u32Index < (u32TableSize - 1) && bIsLastDisplayLine)) )
        if( (enEndingType != EN_STRING_ENDING_NONE) &&
             ((pclrBtn->width < u32LineWidth)  || //only for one line
              (( pMleTextTable ) &&                     //only for multi-line, only multiline case will set pMleTextTable to be non-NULL
              (u32Index < (u32TableSize - 1)) && bIsLastDisplayLine)) )
        {
            S32 s32TempWidth;

            msAPI_OSD_MeasureEllipsis(u32FontSize, FONT_TYPE_NORMAL, enEndingType, &u32EllPix);
            //printf("%d enEndingType=%x u32FontSize=%d u32EllPix=%d\n", __LINE__, enEndingType, u32FontSize, u32EllPix);

            s32TempWidth = u32LineWidth + u32EllPix - pclrBtn->width;
            if ( bIsRTL && (s32TempWidth > 0))
            {
                msAPI_MLE_FONTBASE_Vector_MeasureText( u32FontSize,
                                                       pu16TempStr,
                                                       u32LineLen,
                                                       0,
                                                       u32LineLen,
                                                       s32TempWidth,
                                                       &u32FitLen,
                                                       &u32FitWidth,
                                                       FONT_TYPE_NORMAL,
                                                       FALSE,
                                                       bIsDisplayStr );
                if ((u32FitLen < u32LineLen) && (u32FitWidth < (U32)s32TempWidth))
                {
                    u32FitLen++;
                }

                while ( u32FitLen < u32LineLen && ((pu16TempStr[u32FitLen] == TEXT_WHITE_SPACE) || MLETEXTUTIL_IsReturnChar(pu16TempStr[u32FitLen])) )
                {
                    u32FitLen++;
                }

                s32XStartPos = u32EllPix;
            }

            msAPI_MLE_FONTBASE_Vector_MeasureText( u32FontSize,
                                                   (pu16TempStr + u32FitLen),
                                                   u32LineLen - u32FitLen,
                                                   0,
                                                   u32LineLen - u32FitLen,
                                                   pclrBtn->width - u32EllPix,
                                                   &u32LineLen,
                                                   &u32LineWidth,
                                                   FONT_TYPE_NORMAL,
                                                   FALSE,
                                                   bIsDisplayStr );

            if ( u32FitLen > 0 )
            {
                MEMCPY( (void *)pu16TempStr, (void *)(pu16TempStr + u32FitLen), sizeof(U16) * u32LineLen );
            }
        }

        //decide the x
        switch( pclrBtn->enTextAlign )
        {
            case EN_ALIGNMENT_RIGHT:
                if ( bIsRTLLang ) //ellipical is on left of string
                {
                    s32LineX = (S32)(pclrBtn->width - u32LineWidth);
                }
                else //ellipical is on right of string
                {
                    s32LineX = (S32)(pclrBtn->width - u32LineWidth - u32EllPix);
                }
                break;
            case EN_ALIGNMENT_CENTER:
                if ( bIsRTLLang ) //ellipical is on left of string
                {
                    if ( pclrBtn->width > (u32LineWidth + u32EllPix) )
                    {
                        s32LineX = ((S32)(pclrBtn->width - u32LineWidth + u32EllPix)/2);
                    }
                    else
                    {
                        s32LineX = (S32)(pclrBtn->width - u32LineWidth);
                    }
                }
                else
                {
                    if ( pclrBtn->width > (u32LineWidth + u32EllPix) )
                    {
                        s32LineX = ((S32)(pclrBtn->width - u32LineWidth - u32EllPix)/2);
                    }
                    else
                    {
                        s32LineX = 0;
                    }
                }
                break;

            case EN_ALIGNMENT_LEFT:
            default:
                s32LineX = s32XStartPos;
                break;
        }

        bReturnValue = TRUE;

    }while(FALSE);

    if ( pbIsRTLLang )
    {
        *pbIsRTLLang = bIsRTLLang;
    }

    if( ps32X )
    {
        *ps32X = s32LineX;
    }

    if ( ppu16Str )
    {
        *ppu16Str = pu16TempStr;
    }
    else
    {
        FREE( pu16TempStr );
    }

    if ( pu32FitLen )
    {
        *pu32FitLen = u32LineLen;
    }

    if ( pu32FitWidth )
    {
        *pu32FitWidth = u32LineWidth;
    }

    if ( u32Ell )
    {
        *u32Ell = u32EllPix;
    }

    if ( pbIsRTLStr)
    {
        *pbIsRTLStr = bIsRTL;
    }

    return bReturnValue;
}
#endif

void msAPI_OSD_DrawClippedString(FONTHANDLE font_handle, U16 *pu16Str, OSDClrBtn *pclrBtn, EN_STRING_ENDING_TYPE enEndingType)
{
    S8 gap;
    U8 cut_strlen,dot_count;
    U16 total_strlen, width, u16Char, scale;
    U16 width_offset = 0x00;
    U16 max_width, dot_width;
    GFX_TextOutInfo text_info;
    memset(&text_info,0,sizeof(GFX_TextOutInfo));
    OSD_RESOURCE_FONT_INFO finfo;
    memset(&finfo,0,sizeof(OSD_RESOURCE_FONT_INFO));
//    OSDSRC_GLYPH_BBOX_X BBox_X_Info;

    //GFX_GlyphBbox_X BBox_X_Info;
    U8 bExceed = FALSE;
    OSDSRC_GLYPH_DISP_INFO *pGlyphDispInfo = NULL;
    OSDSRC_GLYPH_DISP_INFO pglyphDot[3];
//    GEClrPoint cpoint;
    U16 pu16dotStr[4];

#if ENABLE_SHORT_STRING_BUFFER //speed up drawing string
    OSDSRC_GLYPH_DISP_INFO _s_temp_glyph[32];
#endif

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT))
    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
        OSDStringType TempBuf;
        OSDStringTypeDouble outbuf;
    #endif
    #if ( ENABLE_ARABIC_OSD )
        OSDStringType out;
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
#endif
#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT))
    U16 nFontID;
#endif

    msAPI_OSD_GET_resource();
//printf("3 strwid =%x, CHAR_IDX_2BYTE =%x\n", pclrBtn->bStringIndexWidth, CHAR_IDX_2BYTE);
    /*prevent error*/
    if (pclrBtn->bStringIndexWidth != CHAR_IDX_2BYTE)
    {
        APIOSD_DBG(printf("Only support 2 bytes strubg\n"));
        msAPI_OSD_Free_resource();
        return;
    }

    if ((total_strlen = msAPI_OSD_GetStrLength((U8*)pu16Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> strlen = 0\n"));
        msAPI_OSD_Free_resource();
        return;
    }

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT))

    int x;
    int len;
    EN_OSDAPI_LANGUAGE tempchar;
    BOOLEAN tempDivxSubtitleMode;
    tempchar = enLanguage;
    tempDivxSubtitleMode = bDivxSubtitleMode;
    len = MApp_ZUI_API_Strlen(pu16Str);
    for(x=0;x<len;x++)
    {
        if(pu16Str[x]>=0x600 && pu16Str[x]<=0x6ff)break;
    }
#if ( ENABLE_ARABIC_OSD )
    if((x<len)&&(ArabicCHStringFlag)&&(enLanguage != LANGUAGE_OSD_ARABIC))
    {
        enLanguage = LANGUAGE_OSD_ARABIC;
        bDivxSubtitleMode = TRUE;
    }
#endif

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
#if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
		case LANGUAGE_OSD_URDU:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
/*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                    msAPI_OSD_Set_H_Mirror(FALSE);
                    //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
                }
                else
*/
                {
                    if ( bHebrewMixedMode )
                    {
                        bHebrew = TRUE;
                    }
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                    {
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                    }

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                        msAPI_GE_SetMirror(1, 0);    //patch GE driver
                        //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), TRUE);
                        msAPI_OSD_Set_H_Mirror(TRUE);
                    }
                    else
                    {
                        msAPI_OSD_Set_H_Mirror(FALSE);
                        //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
                    }
                }
            }

            if ( bHebrew == FALSE )
            {
                bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            pclrBtn->Fontfmt.flag |= GEFONT_FLAG_ARABIC;

            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                msAPI_GE_SetMirror(1, 0);    //patch GE driver
                msAPI_OSD_Set_H_Mirror(TRUE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), TRUE);
            }
            else
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
            }
            break;
#endif
#if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;

            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
/*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
*/
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }

    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
                msAPI_OSD_Set_H_Mirror(FALSE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            }
            break;
#endif
/*
        case LANGUAGE_OSD_CHINESE:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) && ( !bDivxSubtitleText ) )
                    {
                        font_handle = Font[nFontID+18].fHandle;
                    }
                    else if ( nFontID >= FONT_EXT_BEGIN )
                    {
                        //Do Chinese icon unicode conversion here
                    }
                }
            }
            if ( bHebrew == FALSE )
            {
                msAPI_OSD_Set_H_Mirror(FALSE);
                //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            }
            break;
*/
#if ( ENABLE_TTF_FONT )
        case LANGUAGE_OSD_HINDI:
        //case LANGUAGE_OSD_URDU:
        case LANGUAGE_OSD_BENGALI:
        case LANGUAGE_OSD_TELUGU:
        case LANGUAGE_OSD_MARATHI:
        case LANGUAGE_OSD_TAMIL:
        case LANGUAGE_OSD_MYANMAR:
        case LANGUAGE_OSD_KHMER:
        case LANGUAGE_OSD_LAO:
        case LANGUAGE_OSD_ASSAMESE:
        case LANGUAGE_OSD_GUJARATI:
        case LANGUAGE_OSD_KANNADA:
        case LANGUAGE_OSD_MALAYALAM:
        case LANGUAGE_OSD_PUNJABI:
        {
            Rect_t stRect_t;
            MLERet_t  eRet1 = MLE_RET_SUCCESS, eRet2 = MLE_RET_SUCCESS;
            U8 u8count = 0;

            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            if ( enLanguage == LANGUAGE_OSD_URDU )
            {
                if ( bDivxSubtitleMode )
                {
                    switch( pclrBtn->enTextAlign )
                    {
                        case EN_ALIGNMENT_RIGHT:
                            pclrBtn->enTextAlign = EN_ALIGNMENT_LEFT;
                            break;
                        case EN_ALIGNMENT_LEFT:
                            pclrBtn->enTextAlign = EN_ALIGNMENT_RIGHT;
                            break;
                        default:
                            break;
                    }

                    msAPI_OSD_Set_H_Mirror(FALSE);
                }
                else
                {
                    msAPI_OSD_Set_H_Mirror(TRUE);
                }
            }
            else
                msAPI_OSD_Set_H_Mirror(FALSE);
#if 0
            //This is test pattern generator
            if ( enLanguage == LANGUAGE_OSD_HINDI )
            {
                if ( total_strlen >= 11 )
                {
                    printf("Hindi test pattern\n");
                    pu16Str[0] = 0x0911;
                    pu16Str[1] = 0x091F;
                    pu16Str[2] = 0x094B;
                    pu16Str[3] = 0x0020;
                    pu16Str[4] = 0x0935;
                    pu16Str[5] = 0x0949;
                    pu16Str[6] = 0x0932;
                    pu16Str[7] = 0x094D;
                    pu16Str[8] = 0x092F;
                    pu16Str[9] = 0x0942;
                    pu16Str[10] = 0x092E;
                    pu16Str[11] = 0x0000;

                    total_strlen = 11;
                }
            }
#endif
            stRect_t.x = pclrBtn->x;
            stRect_t.y = pclrBtn->y;
            stRect_t.w = pclrBtn->width;
            stRect_t.h = pclrBtn->height;

            OSDTTF_TRACE(printf("%d %s %s, pclrBtn->t_clr=%x\n", __LINE__, __FUNCTION__, __FILE__, pclrBtn->t_clr));

            msAPI_OSD_SetTTFPalette(pclrBtn->t_clr);
            //int i;
            //printf("%d draw ", __LINE__);
            //for(i=0;i<msAPI_OSD_u16Strlen(pu16Str);i++)
            //{
                //printf("%04X ", pu16Str[i]);
            //}
            //printf("\n");

            //We can decide font size from font ID, make a mapping table conversion here
            nFontID = FontHandleIndex[font_handle];

            OSDTTF_TRACE(printf("font_handle=%x, nFontID=%x, font_info[nFontID].output_size = %d\n", font_handle, nFontID, ttf_font_info[nFontID].output_size));

            u8count = 0;
            do
            {
                {
                    U16 *pu16Temp = NULL, *pw = NULL;
                    U32 RowHeight = 0;
                    U32 nRows = 0;
                    U32 u32EllWidth = 0;
                    U32 nFits = 0;
                    U32 nPixcel = 0;
                    S32 nDrawX,nDrawY = pclrBtn->y;
                    BOOLEAN bIsRTLLang;
                    BOOLEAN bIsRTLStr = FALSE;
                    BOOLEAN bFontMirror = FALSE;

                    //Get Font Height
                    if ( msAPI_OSD_MeasureTextY( ttf_font_info[nFontID].output_size, pclrBtn->height, &nDrawY, &nRows, &RowHeight, FALSE) == FALSE )
                    {
                        break;
                    }

                    OSDTTF_TRACE(printf("DrawY=%d stRect_t.y=%d, total=%d stRect.h=%d\n", nDrawY, stRect_t.y, (nDrawY + stRect_t.y), stRect_t.h));
                    nDrawY += stRect_t.y;

                    if ( (msAPI_OSD_MeasureLineX( ttf_font_info[nFontID].output_size,
                                                pu16Str,
                                                 total_strlen,
                                                 0,
                                                 pclrBtn,
                                                 &bIsRTLLang,
                                                 &pu16Temp,
                                                 &nFits,
                                                 &nPixcel,
                                                 &nDrawX,
                                                 &u32EllWidth,
                                                 &bIsRTLStr,
                                                 enEndingType,
                                                 TRUE )) == FALSE )
                    {
                        printf("%d break\n", __LINE__);
                        break;
                    }
                    //printf("%d bIsRTLLang=%d pu16Str=%X pu16Temp=%X nFits=%d nPixcel=%d nDrawX=%d u32EllWidth=%d bIsRTLStr=%d\n", __LINE__, bIsRTLLang, (U32)pu16Str, (U32)pu16Temp, nFits, nPixcel, nDrawX, u32EllWidth, bIsRTLStr);


                    pw = pu16Temp;
                    if ( pw == NULL )
                    {
                        //continue;
                        break;
                    }

                    // ignore white space at first if RTF
                    if ( bIsRTLStr && u32EllWidth == 0 /*&& nDrawX >= 0*/ )
                    {
                        while ( nFits > 1 && ((*pw == TEXT_WHITE_SPACE) || MLETEXTUTIL_IsReturnChar(*pw)) )
                        {
                            pw = (U16 *)(pw + 1);
                            nFits = nFits - 1;
                        }
                    }

                    //Fix me, this logical needs to discuss
                    //if(nDrawY + (S32)RowHeight < DispRect.y)
                    if(nDrawY + (S32)RowHeight < stRect_t.y)
                    {
                        nDrawY += RowHeight;
                        nFits = 0;
                        //if ( nDrawY + (s32)RowHeight >= stRect_t.y + stRect_t.h )
                        //{
                            //bIsLastDisplayLine = TRUE;
                        //}
                        //continue;
                    }
                    else if(nDrawY>stRect_t.y+stRect_t.h)
                    {
                        break;
                    }

                    nDrawX += stRect_t.x;

                    bFontMirror = ( bIsRTLLang ) && ( !bDivxSubtitleMode );

                    if( u32EllWidth )
                    {
                        if ( bIsRTLLang )
                        {
                            OSDTTF_TRACE(printf("%d\n", __LINE__));
                            if ( bFontMirror )
                                msAPI_GE_SetMirror(1, 0);    //patch GE driver
                            eRet1 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX, nDrawY, pw, nFits, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                            eRet2 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX - u32EllWidth, nDrawY, COMMON_ELLIPSIS_STRING, enEndingType, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                            if ( bFontMirror )
                                msAPI_GE_SetMirror(0, 0);    //patch GE driver
                        }
                        else
                        {
                            OSDTTF_TRACE(printf("%d\n", __LINE__));
                            if ( bFontMirror )
                                msAPI_GE_SetMirror(1, 0);    //patch GE driver
                            eRet1 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX, nDrawY, pw, nFits, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                            eRet2 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX+nPixcel, nDrawY, COMMON_ELLIPSIS_STRING, enEndingType, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                            if ( bFontMirror )
                                msAPI_GE_SetMirror(0, 0);    //patch GE driver
                        }
                    }
                    else
                    {
                        //printf("%d pw=%X nFits=%d, nDrawX=%d nDrawY=%d stRect_t.w=%d\n", __LINE__, (U32)pw, nFits, nDrawX, nDrawY, stRect_t.w);
                        if ( bFontMirror )
                            msAPI_GE_SetMirror(1, 0);    //patch GE driver
                        eRet1 = msAPI_MLE_FONTBASE_Vector_DrawText(ttf_font_info[nFontID].output_size, nDrawX, nDrawY, pw, nFits, &stRect_t, FONT_TYPE_NORMAL, pclrBtn, bFontMirror);
                        if ( bFontMirror )
                            msAPI_GE_SetMirror(0, 0);    //patch GE driver
                    }

                    if ( pu16Temp != NULL )
                    {
                        FREE( pu16Temp );
                        pu16Temp = NULL;
                    }
                }

                u8count++;
                if ( u8count > 1 )
                    break;

                if ( ( eRet1 == MLE_RET_OUT_OF_MEMORY ) || ( eRet2 == MLE_RET_OUT_OF_MEMORY ) || ( msAPI_MLE_GetMemoryNotEnoughFlag() == TRUE ) )
                {
                    //printf("%d reset eRet1=%x eRet2=%x flag=%x\n", __LINE__, eRet1, eRet2, msAPI_MLE_GetMemoryNotEnoughFlag());
                    //reset font and cache system to release memory fragmentation
                    msAPI_MLE_FONTBASE_VectorFontReInit(msAPI_MLE_FONT_PL_GetFTBufferSize());
                    msAPI_MLE_SetMemoryNotEnoughFlag(FALSE);
                }
            } while( ( eRet1 == MLE_RET_OUT_OF_MEMORY ) || ( eRet2 == MLE_RET_OUT_OF_MEMORY ) );
        }
        msAPI_OSD_Free_resource();
        return;

        break;
#endif

        default:
            pclrBtn->Fontfmt.flag &= ~GEFONT_FLAG_ARABIC;
            msAPI_OSD_Set_H_Mirror(FALSE);
            //MApi_GOP_Enable_GWIN_HMirror(MApi_GOP_GWIN_GetCurrentGOP(), FALSE);
            break;
    }
#endif

#if (ENABLE_ARABIC_OSD)

    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }

#endif
#if (ENABLE_THAI_OSD)
    if ( (bThaiDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
    {
            pclrBtn->Fontfmt.ifont_gap = 0;
    }
#endif

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )

    if (total_strlen >= sizeof(TempBuf.U8Str)/2)
    {
        total_strlen = sizeof(TempBuf.U8Str)/2 - 1;
    }

    #if ( ENABLE_ARABIC_OSD )
    if ( bMirrorLang )
    {
        U8 bReverse = TRUE;
        U16 i;

        memcpy(TempBuf.U8Str,(U8 *)pu16Str,total_strlen*2);
        //((U16 *)TempBuf)[total_strlen] = 0;
        TempBuf.U16Str[total_strlen] = 0;

        //For Subtitle
        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
        {
            S32 errorCode = U_ZERO_ERROR;

            ArabicParser(TempBuf.U16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);

            //Every language is possible, you can't skip this filter here
            msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
			msAPI_OSD_UrduFilter(outbuf.U16Str, total_strlen);
            msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, total_strlen);
            msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, TempBuf.U16Str, total_strlen);
            bReverse = FALSE;
        }
        else if ( bArabicDisplay ) //for OSD
        {
            S32 errorCode = U_ZERO_ERROR;

            ArabicParser(TempBuf.U16Str, total_strlen, outbuf.U16Str, STROSD,
                     U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                     &errorCode);
            //just skip this function for non Kurdish condition

            if ( enLanguage == LANGUAGE_OSD_KURDISH )
            {
                msAPI_OSD_KurdishFilter(outbuf.U16Str, total_strlen);
            }
            else if ( enLanguage == LANGUAGE_OSD_URDU )
            {
                msAPI_OSD_UrduFilter(outbuf.U16Str, total_strlen);
            }

            msAPI_OSD_ReverseAllCharacters(outbuf.U16Str, out.U16Str, total_strlen);
            msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, total_strlen);
        }
        else    // for Hebrew
        {
            if ( bDivxSubtitleMode )    // Divx subtitle
            {
                msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, outbuf.U16Str, total_strlen);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, total_strlen);
                msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, total_strlen);
            }
            else if ( bHebrew )         // Hebrew OSD display
            {
                msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, out.U16Str, total_strlen);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(out.U16Str, outbuf.U16Str, total_strlen);
            }
            else                        // Other conditions
            {
                msAPI_OSD_ReverseAllCharacters(TempBuf.U16Str, outbuf.U16Str, total_strlen);
                msAPI_OSD_ReverseNonArabicHebrewCharacters(outbuf.U16Str, out.U16Str, total_strlen);
                msAPI_OSD_ReverseAllCharacters(out.U16Str, outbuf.U16Str, total_strlen);
            }
        }

        if ( bReverse )
        {
            for(i=0;i<total_strlen;i++)
            {
                TempBuf.U16Str[i] = *(outbuf.U16Str+total_strlen-i-1);
            }
        }

        //((U16 *)TempBuf)[total_strlen] = 0;
        TempBuf.U16Str[total_strlen] = 0;

        pu16Str = TempBuf.U16Str;
    }
    #endif
#endif
#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (ENABLE_INDIA_OSD) || (ENABLE_TTF_FONT))
    enLanguage = tempchar;
    bDivxSubtitleMode = tempDivxSubtitleMode;
#endif

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);

    if ( finfo.height > pclrBtn->height )
    {
        APIOSD_DBG(printf("[]ERR:hei=%bu,%bu,[%c][%c][%c]\n", (U8)finfo.height,(U8)pclrBtn->height,(U8)pu16Str[0],(U8)pu16Str[1],(U8)pu16Str[2]));
        msAPI_OSD_Free_resource();
        return;
    }

    scale = 100;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = ((U16)pclrBtn->Fontfmt.height*100 / (U16)finfo.height);
        pclrBtn->Fontfmt.height = scale * finfo.height /100;

        scale = (U8)((U16)pclrBtn->Fontfmt.width*100 / (U16)finfo.width);
        pclrBtn->Fontfmt.width = scale * finfo.width /100;
    }

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        total_strlen = Thai_compose(pu16Str, 0, total_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[total_strlen] = 0x0000;

        pu16Str = outbuf.U16Str;
    }
#endif

#if ENABLE_SHORT_STRING_BUFFER //speed up drawing string
    if (total_strlen <= COUNTOF(_s_temp_glyph))
        pGlyphDispInfo = _s_temp_glyph;
    else
#endif
        pGlyphDispInfo = msAPI_Memory_Allocate(sizeof(OSDSRC_GLYPH_DISP_INFO) * total_strlen , BUF_ID_GLYPH_DISP_INFO);
    if (pGlyphDispInfo == NULL)
    {
        __ASSERT(0);
        APIOSD_DBG(printf("E_DrawText>> pGlyphDispInfo == NULL\n"));
        msAPI_OSD_Free_resource();
        return;
    }

    gap = 0;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
    }
    else
    {
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            gap = -pclrBtn->Fontfmt.dis;
        }
    }

    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_BOLD)
    {
        pclrBtn->Fontfmt.flag |= GFXFONT_FLAG_BOLD;
    }

    max_width = pclrBtn->width;

    /*/refine..
    dot_count=0;
    while(dot_count<enEndingType)
        MDrv_GE_GetGlyphDispInfo(font_handle, CHAR_DOT, &pglyphDot[enEndingType-1-dot_count++]);
    */
    if (enEndingType != EN_STRING_ENDING_NONE)
    {
        msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, CHAR_DOT, &pglyphDot[0]);
        for (dot_count = 1; dot_count < enEndingType; dot_count++)
        {
            memcpy(&pglyphDot[dot_count], &pglyphDot[0], sizeof(OSDSRC_GLYPH_DISP_INFO));
        }
    }

    dot_width =0;
    switch (enEndingType)
    {
      #if(1)//  update 20100826
        case EN_STRING_ENDING_NONE:
            break;
        case EN_STRING_ENDING_3_DOT:
            dot_width += (3*(pglyphDot[0].u8Width) + gap);
        case EN_STRING_ENDING_2_DOT:
            dot_width += (2*(pglyphDot[0].u8Width) + gap);
        case EN_STRING_ENDING_1_DOT:
            dot_width += ((pglyphDot[0].u8Width) + gap);
      #else
        case EN_STRING_ENDING_NONE:
            break;
        case EN_STRING_ENDING_3_DOT:
            dot_width += (pglyphDot[2].u8Width + gap);
        case EN_STRING_ENDING_2_DOT:
            dot_width += (pglyphDot[1].u8Width + gap);
        case EN_STRING_ENDING_1_DOT:
            dot_width += (pglyphDot[0].u8Width + gap);
      #endif
    }
    max_width -= dot_width;

    if(pclrBtn->enTextAlign==EN_ALIGNMENT_LEFT ||pclrBtn->enTextAlign==EN_ALIGNMENT_RIGHT)
       max_width -= BTN_TEXT_GAP;

    {
        width = 0;
        cut_strlen = 0;

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            static U8 prevState = 0;

            prevState = 0;

            while (width<(max_width+dot_width) && cut_strlen<total_strlen)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu16Str[cut_strlen], &pGlyphDispInfo[cut_strlen]);
                pGlyphDispInfo[cut_strlen].u8Width = (pGlyphDispInfo[cut_strlen].u8Width * scale
#if ENABLE_DEFAULT_KERNING
                    - kerningX_(pu16Str[cut_strlen], pu16Str[cut_strlen+1])
#endif //ENABLE_DEFAULT_KERNING
                    ) / 100;
                /*/refine..
                MDrv_GE_GetBBox_X(font_handle, pu16Str[cut_strlen++], &BBox_X_Info);
                if ( scale == 100 )
                {
                    width += (BBox_X_Info.u8Width + gap);
                }
                else
                {
                    width += (BBox_X_Info.u8Width*scale/100 + gap);
                }
                */

            #if (ENABLE_ARABIC_OSD)
                //For Subtitle
                if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || ( External Subtitle Language is Arabic ) */ ) )
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {
                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen-1] ) )
                        {
                            width -= pGlyphDispInfo[cut_strlen-1].u8Width;

                            pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            //coordinate no need change
                        }
                    }
                    else
                    {
                        //coordinate no need change
                    }

                    width += (pGlyphDispInfo[cut_strlen].u8Width + gap);
                }
                else if ( bArabicDisplay ) //for OSD
                {
                    // Check if it is in Arabic Vowel unicode range
                    if ( cut_strlen > 0 )
                    {
                        if ( msAPI_OSD_IsArabicVowel( pu16Str[cut_strlen] ) )
                        {
                            //skip current vowel character width
                            //do nothing here
                            S8 nOffset = pGlyphDispInfo[cut_strlen-1].u8Width - pGlyphDispInfo[cut_strlen].u8Width;

                            if ( nOffset > 0 )
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = nOffset;
                            else
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;
                        }
                        else
                        {
                            width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                            //coordinate no need change
                        }
                    }
                    else
                    {
                        width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                        //coordinate no need change
                    }
                }
                else
            #endif
            #if (ENABLE_THAI_OSD)
                if ( ( bThaiDisplay ) || ((bDivxSubtitleMode) /* && (External Subtitle Language is Thai) */ ) )
                {
                    // Check Primary Thai unicode range
                    if ( ( pu16Str[cut_strlen] <= 0x0E5B ) && ( pu16Str[cut_strlen] >= 0x0E01 ) )
                    {
                        if ( MinusDrawTable[ pu16Str[cut_strlen] - 0x0E01 ] )
                        {
                            if ( cut_strlen > 0 )
                            {
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ pu16Str[cut_strlen-1] - 0x0E01 ] ) )
                                {
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                }
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ pu16Str[cut_strlen-1] - 0xF700 ] ) )
                                {
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                }
                                else
                                {
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-1].u8X0 + pGlyphDispInfo[cut_strlen-1].u8Width + 1) - (finfo.width);
                                }
                             }
                            else
                            {
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;

                            //Minus coordinate, don't add width
                        }
                        else
                        {
                            width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                            //coordinate no need change
                        }

                        prevState = 1;
                    }
                    else if ( ( pu16Str[cut_strlen] <= 0xF71A ) && ( pu16Str[cut_strlen] >= 0xF700 ) )
                    {
                        if ( MinusDrawTablePersentation[ pu16Str[cut_strlen] - 0xF700 ] )
                        {
                            if ( cut_strlen > 0 )
                            {
                                if ( ( prevState == 1 ) && ( MinusDrawTable[ pu16Str[cut_strlen-1] - 0x0E01 ] ) )
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                else if ( ( prevState == 2 ) && ( MinusDrawTablePersentation[ pu16Str[cut_strlen-1] - 0xF700 ] ) )
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-2].u8X0 + pGlyphDispInfo[cut_strlen-2].u8Width + 1) - (finfo.width);
                                else
                                    pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = (pGlyphDispInfo[cut_strlen-1].u8X0 + pGlyphDispInfo[cut_strlen-1].u8Width + 1) - (finfo.width);
                            }
                            else
                            {
                                pGlyphDispInfo[cut_strlen].overlap_info.s8Xoffset = 1;
                            }

                            pGlyphDispInfo[cut_strlen].overlap_info.s8Yoffset = 0;

                            //Minus coordinate, don't add width

                            prevState = 2;
                        }
                        else
                        {
                            width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                            //coordinate no need change
                            prevState = 0;
                        }
                    }
                    else
                    {
                        width += (pGlyphDispInfo[cut_strlen].u8Width + gap);

                        //coordinate no need change
                    }
                }
                else
            #endif
                {
                    width += (pGlyphDispInfo[cut_strlen].u8Width + gap);
                }
                cut_strlen++;

                if ( (pu16Str[(cut_strlen-1)]==0x20) || ((pu16Str[(cut_strlen-1)]>=0x80) && (pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }
        else
        {
            while(width<(max_width+dot_width) && cut_strlen<total_strlen)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu16Str[cut_strlen], &pGlyphDispInfo[cut_strlen]);

                cut_strlen++;
                width += (finfo.width + gap);
                if ( (pu16Str[(cut_strlen-1)]==0x20) || ((pu16Str[(cut_strlen-1)]>=0x80) && (pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }

        if (width >= (max_width+dot_width))
        {

            if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
            {
                while(width>=max_width)
                {
                    /*/refine..
                    MDrv_GE_GetBBox_X(font_handle, pu16Str[--cut_strlen], &BBox_X_Info);
                    if ( scale == 100 )
                    {
                        width -= (BBox_X_Info.u8Width + gap);
                    }
                    else
                    {
                        width -=  (BBox_X_Info.u8Width*scale/100 + gap);
                    }
                    */

                    // Maybe we need to consider combination case here for Arabic and Thai languages
                    // If the cut point is at the middle of combination words unicode,
                    // we may see strange words to be displayed or other side effects
                    // We can enhance this case in the future
                    cut_strlen--;
                    if( max_width == 0)
                    {
                        break;
                    }
                    else
                    {
                        if(cut_strlen < total_strlen)
                            width -= (pGlyphDispInfo[cut_strlen].u8Width + gap);
                        else
                            printf("\r\n ERROR !! strlen out of range");
                    }
                }
            }
            else
            {
                while(width>=max_width)
                {
                    cut_strlen--;
                    width -= (finfo.width + gap);
                }
            }
            bExceed = TRUE;
            width_offset = width;
            width += dot_width;
        }

        switch (pclrBtn->enTextAlign)
        {
            case EN_ALIGNMENT_DEFAULT: //without BTN_TEXT_GAP
                text_info.dstblk.x = pclrBtn->x;
                break;

            case EN_ALIGNMENT_LEFT:
                text_info.dstblk.x = pclrBtn->x + BTN_TEXT_GAP;
                break;

            case EN_ALIGNMENT_RIGHT:
                    text_info.dstblk.x = pclrBtn->x + pclrBtn->width - BTN_TEXT_GAP - width;
                break;

            case EN_ALIGNMENT_CENTER:
                    text_info.dstblk.x = pclrBtn->x + (pclrBtn->width - width) / 2;
                break;
        }

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
        {
            text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height * scale / 100) / 2;
        }
        else
        {
            text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height) / 2;
            OSDTTF_TRACE(printf("BMP %d = %d + (%d - %d) / 2\n", text_info.dstblk.y, pclrBtn->y, pclrBtn->height, finfo.height));
        }
//        memcpy(&cpoint.clr, &pclrBtn->t_clr, 4);

        if (cut_strlen > 0)
        {

            //U8 ptrEnd = cut_strlen;

            if (bExceed)
            {
            #if (ENABLE_ARABIC_OSD)
                if ( ( bMirrorLang ) && ( bDivxSubtitleMode == FALSE ) )
                {
                    S16 i;
                    U16 localwidth = 0;
                    S16 index1=0,index2=0;

                    for(i=0;i<cut_strlen;i++)
                    {
                        if ( msAPI_OSD_IsNotInArabicHebrew(pu16Str[i]) == PURE_ARABIC_CHAR )
                            break;
                    }
                    if ( i == cut_strlen )
                    {
                        // No mirror characters found
                        //msAPI_OSD_ReverseAllCharacters(pu16Str, out.U16Str, total_strlen);
                        //memcpy(out.U8Str, (U8 *)pu16Str, total_strlen*2);
                        cut_strlen = 0;
                        for(i=total_strlen-1;i>=0;i--)
                        {
                            localwidth += pGlyphDispInfo[i].u8Width;
                            if ( localwidth >= (max_width+dot_width) )
                            {
                                // Maybe we need to consider combination case here for Arabic and Thai languages
                                // If the cut point is at the middle of combination words unicode,
                                // we may see strange words to be displayed or other side effects
                                // We can enhance this case in the future
                                localwidth -= (pGlyphDispInfo[i].u8Width + gap);
                                break;
                            }
                            out.U16Str[cut_strlen++] = pu16Str[i];
                        }

                        switch (enEndingType)
                        {
                            case EN_STRING_ENDING_3_DOT:
                                pu16Str[2] = CHAR_DOT; // .
                                pu16Str[1] = CHAR_DOT; // .
                                pu16Str[0] = CHAR_DOT; // .
                                i = 3;
                                break;

                            case EN_STRING_ENDING_2_DOT:
                                pu16Str[1] = CHAR_DOT; // .
                                pu16Str[0] = CHAR_DOT; // .
                                i = 2;
                                break;

                            case EN_STRING_ENDING_1_DOT:
                                pu16Str[0] = CHAR_DOT; // .
                                i = 1;
                                break;

                            case EN_STRING_ENDING_NONE:
                                i = 0;
                                break;
                        }

                        for(index1=(S16)(0),index2=(S16)(cut_strlen-1);index1<index2;index1++,index2--)
                        {
                            pu16Str[index1+i] = out.U16Str[index2];
                            pu16Str[index2+i] = out.U16Str[index1];
                        }
                        if ( index1 == index2 )
                        {
                            pu16Str[index1+i] = out.U16Str[index1];
                        }
                        cut_strlen += i;
                        pu16Str[cut_strlen] = 0;

                        for(i=0;i<cut_strlen;i++)
                        {
                            msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu16Str[i], &pGlyphDispInfo[i]);
                            pGlyphDispInfo[i].u8Width = (pGlyphDispInfo[i].u8Width * scale
            #if ENABLE_DEFAULT_KERNING
                                - kerningX_(pu16Str[i], pu16Str[i+1])
            #endif //ENABLE_DEFAULT_KERNING
                                ) / 100;
                        }

                        MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
                        MApi_GFX_TextOut(font_handle, (MS_U8*)pu16dotStr, pclrBtn->bStringIndexWidth+1, &text_info);

                        goto Exit_Display;
                    }

                    // goto normal path
                }
            #endif
                switch (enEndingType)
                {
                    case EN_STRING_ENDING_3_DOT:
                             pu16dotStr[3] = 0; // .
                             pu16dotStr[2] = CHAR_DOT; // .
                             pu16dotStr[1] = CHAR_DOT; //
                             pu16dotStr[0] = CHAR_DOT; // .
                        break;

                    case EN_STRING_ENDING_2_DOT:
                             pu16dotStr[2] = 0; // .
                             pu16dotStr[1] = CHAR_DOT; //
                             pu16dotStr[0] = CHAR_DOT; // .
                        break;

                    case EN_STRING_ENDING_1_DOT:
                             pu16dotStr[1] = 0; // .
                             pu16dotStr[0] = CHAR_DOT; // .
                        break;

                    case EN_STRING_ENDING_NONE:
                        break;
                }
                if (enEndingType != EN_STRING_ENDING_NONE)
                {
                    text_info.dstblk.x += width_offset;

                    #ifndef UI_DRAW_TEXT_I8
//                    text_info.dstblk.x = cpoint.x;
//                    text_info.dstblk.y = cpoint.y;
                    text_info.dstblk.width = pclrBtn->width;
                    text_info.dstblk.height = pclrBtn->height;
                    text_info.flag = pclrBtn->Fontfmt.flag;
                    memcpy(&text_info.color, &pclrBtn->t_clr, 4);
                    text_info.pGlyphDispInfo = (GFX_GlyphDispInfo*)&pglyphDot;
                    text_info.gap = pclrBtn->Fontfmt.ifont_gap;
                    MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
                    MApi_GFX_TextOut(font_handle, (MS_U8*)pu16dotStr, pclrBtn->bStringIndexWidth+1, &text_info);

//                    MApi_GFX_TextOut(font_handle, (U8 *)pu16dotStr, (U8)pclrBtn->bStringIndexWidth, (GEClrPoint *)&cpoint,  (GEFontFmt *)&pclrBtn->Fontfmt, (GLYPH_DISP_INFO *)pglyphDot);
                    #else
                    //FIXME
//                    MApi_GFX_SetAlpha(false, COEF_ASRC, ABL_FROM_ASRC, 0x00000000);
//                    TextOut_common(font_handle, (U8*)pu16dotStr, pclrBtn->bStringIndexWidth, &cpoint,  &pclrBtn->Fontfmt, pglyphDot, 0);
                    #endif

                    text_info.dstblk.x -=  width_offset;
                }

            }
            u16Char = pu16Str[cut_strlen];
            pu16Str[cut_strlen] = 0;
//            text_info.dstblk.x = cpoint.x;
//            text_info.dstblk.y = cpoint.y;
            text_info.dstblk.width = pclrBtn->width;
            text_info.dstblk.height = pclrBtn->height;
            text_info.flag = pclrBtn->Fontfmt.flag;
            text_info.pGlyphDispInfo = (GFX_GlyphDispInfo*)pGlyphDispInfo;
            text_info.gap = pclrBtn->Fontfmt.ifont_gap;
            memcpy(&text_info.color, &pclrBtn->t_clr, 4);
            MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
            MApi_GFX_TextOut(font_handle, (MS_U8*)pu16Str, pclrBtn->bStringIndexWidth+1, &text_info);

            //MApi_GFX_TextOut(font_handle, (U8*)pu16Str, (U8)pclrBtn->bStringIndexWidth, (GEClrPoint *)&cpoint,  (GEFontFmt *)&pclrBtn->Fontfmt, pGlyphDispInfo);
            //msAPI_OSD_DrawText(font_handle, (U8*)pu16Str, pclrBtn);
            pu16Str[cut_strlen] = u16Char;

        }

    }

#if (ENABLE_ARABIC_OSD)
Exit_Display:
#endif

    if (pGlyphDispInfo != NULL)
    {
#if ENABLE_SHORT_STRING_BUFFER     //speed up drawing string
        if (total_strlen <= COUNTOF(_s_temp_glyph))
            ; //do nothing: pGlyphDispInfo = _s_glyph;
        else
#endif
            MSAPI_MEMORY_FREE(pGlyphDispInfo, BUF_ID_GLYPH_DISP_INFO);
    }
        msAPI_GE_SetMirror(0, 0);    //patch GE driver
        msAPI_OSD_Free_resource();
}

/******************************************************************************/
/// API for draw frame:
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_DrawFrame(OSDClrBtn *pclrBtn)
{
    /* check range */
/*
    if(pclrBtn->bFrameWidth==0)
    {
        return;
    }
    else if((pclrBtn->x + pclrBtn->width) > NEWUI_MAIN_MENU_GWIN_WIDTH)
    {
        return;
    }
    else if((pclrBtn->y + pclrBtn->height) > NEWUI_MAIN_MENU_GWIN_HEIGHT)
    {
        return;
    }
*/
#if GE_DRIVER_TEST
    GELineRect.LineRectCoordinate.direction = 0x00;
    GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_CONSTANT ;
    GELineRect.ARGBClr.ForeGroundColor.u32Num
    = (pclrBtn->f_clr&0xff00ff00) + ((pclrBtn->f_clr&0xff)<<16) +((pclrBtn->f_clr>>16)&0xff);

    // draw upper rectangle fill
    GELineRect.LineRectCoordinate.direction = 0x00;
    GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_CONSTANT ;
    GELineRect.LineRectCoordinate.v0_x = pclrBtn->x;
    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;
    GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width - 1;
    GELineRect.LineRectCoordinate.v1_y = pclrBtn->y +  pclrBtn->bFrameWidth-1;
    MDrv_GE_RectDraw(&GELineRect);

    // draw lower rectangle fill
    GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_NONCHANGE;
    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y + pclrBtn->height - pclrBtn->bFrameWidth;
    GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height - 1;
    MDrv_GE_RectDraw(&GELineRect);

    // draw left rectangle fill
    GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_NONCHANGE;
    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;
    GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->bFrameWidth - 1;
    GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height -1 ;
    MDrv_GE_RectDraw(&GELineRect);

    // draw right rectangle fill
    GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_NONCHANGE;
    GELineRect.LineRectCoordinate.v0_x = pclrBtn->x + pclrBtn->width - pclrBtn->bFrameWidth;
    GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width - 1;
    MDrv_GE_RectDraw(&GELineRect);

#else
    GFX_DrawLineInfo pline;
    GFX_RectFillInfo pfillblock;

    msAPI_OSD_GET_resource();

    pfillblock.dstBlock.x = pclrBtn->x;
    pfillblock.dstBlock.y = pclrBtn->y;
    pfillblock.dstBlock.width = pclrBtn->width;
    pfillblock.dstBlock.height = pclrBtn->height;
    memcpy(&pfillblock.colorRange.color_s, &pclrBtn->f_clr, 4);
    memcpy(&pfillblock.colorRange.color_e, &pclrBtn->f_clr, 4);
    pfillblock.flag = 0;

    pline.width = pclrBtn->bFrameWidth;
#if 0
    clrBlock.x = pclrBtn->x;
    clrBlock.y = pclrBtn->y;
    clrBlock.width = pclrBtn->width;
    clrBlock.height = pclrBtn->height;
    memcpy(&clrBlock.clr, &pclrBtn->f_clr, 4);
    lineFmt.width = pclrBtn->bFrameWidth;
#endif
    MApi_GFX_RectFrame(&pfillblock, &pline);

    msAPI_OSD_Free_resource();
#endif
}
/******************************************************************************/
/// API for draw block:
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_DrawBlock(OSDClrBtn *pclrBtn)
{
    /* check range */
/*
    if((pclrBtn->x + pclrBtn->width) > NEWUI_MAIN_MENU_GWIN_WIDTH)
    {
        return;
    }
    else if((pclrBtn->y + pclrBtn->height) > NEWUI_MAIN_MENU_GWIN_HEIGHT)
    {
        return;
    }
*/

    /* set start point coordinate */
    GFX_DrawLineInfo pline;
    GFX_RectFillInfo pfillblock;

    msAPI_OSD_GET_resource();

    /* Initialize the GE format for default setting(RGB565)*/
    pfillblock.fmt = GFX_FMT_RGB565; // 20091215

    pfillblock.dstBlock.x = pclrBtn->x;
    pfillblock.dstBlock.y = pclrBtn->y;


//    GELineRect.LineRectCoordinate.v0_x = pclrBtn->x;
//    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;

#if GE_DRIVER_TEST
    switch(pclrBtn->u8Gradient)
    {
        default:
        case CONSTANT_COLOR:
            GELineRect.LineRectCoordinate.direction = 0x0;
            GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width -1;
            GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height -1;
            GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_CONSTANT;
            GELineRect.ARGBClr.ForeGroundColor.u32Num
            = (pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);
            MDrv_GE_RectDraw(&GELineRect);
            break;

        case GRADIENT_X_COLOR:
            GELineRect.LineRectCoordinate.direction = 0x0;
            GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width-1;
            GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height-1;
            GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_GRADIENT_X;
            GELineRect.ARGBClr.ForeGroundColor.u32Num
            = (pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);
            GELineRect.ARGBClr.GradientXColor.u32Num
            = (pclrBtn->g_clr&0xff00ff00) + ((pclrBtn->g_clr&0xff)<<16) +((pclrBtn->g_clr>>16)&0xff);
            MDrv_GE_RectDraw(&GELineRect);
            break;

        case GRADIENT_Y_COLOR:
            GELineRect.LineRectCoordinate.direction = 0x0;
            GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width-1;
            GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height-1;
            GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_GRADIENT_Y;
            GELineRect.ARGBClr.ForeGroundColor.u32Num
            = (pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);
            GELineRect.ARGBClr.GradientYColor.u32Num
            = (pclrBtn->g_clr&0xff00ff00) + ((pclrBtn->g_clr&0xff)<<16) +((pclrBtn->g_clr>>16)&0xff);
            MDrv_GE_RectDraw(&GELineRect);
            break;

        case GRADIENT_X_CENTER_COLOR:
            GELineRect.LineRectCoordinate.direction = 0x0;
            GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + (pclrBtn->width>>1) - 1;
            GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height -1 ;
            GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_GRADIENT_X;
            GELineRect.ARGBClr.ForeGroundColor.u32Num
            = (pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);
            GELineRect.ARGBClr.GradientXColor.u32Num
            = (pclrBtn->g_clr&0xff00ff00) + ((pclrBtn->g_clr&0xff)<<16) +((pclrBtn->g_clr>>16)&0xff);
            MDrv_GE_RectDraw(&GELineRect);

            GELineRect.LineRectCoordinate.v0_x = pclrBtn->x + pclrBtn->width-1;
            GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_NONCHANGE;
            GELineRect.LineRectCoordinate.direction = 0x01; //x direction change

            MDrv_GE_RectDraw(&GELineRect);
            break;

        case GRADIENT_Y_CENTER_COLOR:
            GELineRect.LineRectCoordinate.direction = 0x0;
            GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width -1;
            GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + (pclrBtn->height>>1) -1;
            GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_GRADIENT_Y;
            GELineRect.ARGBClr.ForeGroundColor.u32Num
            = (pclrBtn->b_clr&0xff00ff00) + ((pclrBtn->b_clr&0xff)<<16) +((pclrBtn->b_clr>>16)&0xff);
            GELineRect.ARGBClr.GradientYColor.u32Num
            = (pclrBtn->g_clr&0xff00ff00) + ((pclrBtn->g_clr&0xff)<<16) +((pclrBtn->g_clr>>16)&0xff);
            MDrv_GE_RectDraw(&GELineRect);

            GELineRect.LineRectCoordinate.direction = 0x02;  //y direction change
            GELineRect.LineRectCoordinate.v0_y = pclrBtn->y + pclrBtn->height - 1;
            GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_NONCHANGE;
            MDrv_GE_RectDraw(&GELineRect);
            break;

    }


    /* draw rectangle frame */
    if(pclrBtn->fHighLight && pclrBtn->bFrameWidth)
    {
        GELineRect.ARGBClr.ForeGroundColor.u32Num
        = (pclrBtn->f_clr&0xff00ff00) + ((pclrBtn->f_clr&0xff)<<16) +((pclrBtn->f_clr>>16)&0xff);

        // draw upper rectangle fill
        GELineRect.LineRectCoordinate.direction = 0x00;
        GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_CONSTANT ;
        GELineRect.LineRectCoordinate.v0_x = pclrBtn->x;
        GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;
        GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width - 1;
        GELineRect.LineRectCoordinate.v1_y = pclrBtn->y +  pclrBtn->bFrameWidth-1;
        MDrv_GE_RectDraw(&GELineRect);

        // draw lower rectangle fill
        GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_NONCHANGE;
        GELineRect.LineRectCoordinate.v0_y = pclrBtn->y + pclrBtn->height - pclrBtn->bFrameWidth;
        GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height - 1;
        MDrv_GE_RectDraw(&GELineRect);

        // draw left rectangle fill
        GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_NONCHANGE;
        GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;
        GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->bFrameWidth - 1;
        GELineRect.LineRectCoordinate.v1_y = pclrBtn->y + pclrBtn->height -1 ;
        MDrv_GE_RectDraw(&GELineRect);

        // draw right rectangle fill
        GELineRect.Gradient_Color_Flag = GECOLOR_FLAG_NONCHANGE;
        GELineRect.LineRectCoordinate.v0_x = pclrBtn->x + pclrBtn->width - pclrBtn->bFrameWidth;
        GELineRect.LineRectCoordinate.v1_x = pclrBtn->x + pclrBtn->width - 1;
        MDrv_GE_RectDraw(&GELineRect);
    }

#else
     switch(pclrBtn->u8Gradient)
    {
        default:
        case CONSTANT_COLOR:

            /* draw rectangle */
            pfillblock.dstBlock.width = pclrBtn->width;
            pfillblock.dstBlock.height = pclrBtn->height;
            /* set gradient color */
            pfillblock.flag = GFXRECT_FLAG_COLOR_CONSTANT ;
            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->b_clr, 4);

            MApi_GFX_RectFill(&pfillblock);
            break;

        case GRADIENT_X_COLOR:
            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
            pfillblock.dstBlock.width = pclrBtn->width;
            pfillblock.dstBlock.height = pclrBtn->height;
            /* set gradient color */
            pfillblock.flag = GFXRECT_FLAG_COLOR_GRADIENT_X ;
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->g_clr, 4);

            /* draw rectangle */
            MApi_GFX_RectFill(&pfillblock);

            break;

        case GRADIENT_Y_COLOR:
            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
            pfillblock.dstBlock.width = pclrBtn->width;
            pfillblock.dstBlock.height = pclrBtn->height;
            /* set gradient color */
            pfillblock.flag = GFXRECT_FLAG_COLOR_GRADIENT_Y ;
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->g_clr, 4);

            /* draw rectangle */
            MApi_GFX_RectFill(&pfillblock);

            break;

        case GRADIENT_XY_COLOR:
            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
            pfillblock.dstBlock.width = pclrBtn->width;
            pfillblock.dstBlock.height = pclrBtn->height;
            /* set gradient color */
            pfillblock.flag = GFXRECT_FLAG_COLOR_GRADIENT_X|GFXRECT_FLAG_COLOR_GRADIENT_Y ;
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->g_clr, 4);

            /* draw rectangle */
            MApi_GFX_RectFill(&pfillblock);


            break;

        case GRADIENT_X_CENTER_COLOR:
            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
            pfillblock.dstBlock.width = pclrBtn->width / 2 ;
            pfillblock.dstBlock.height = pclrBtn->height;
            /* set gradient color */
            pfillblock.flag = GFXRECT_FLAG_COLOR_GRADIENT_X ;
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->g_clr, 4);

            /* draw rectangle */
            MApi_GFX_RectFill(&pfillblock);


            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->g_clr, 4);
            pfillblock.dstBlock.x = pfillblock.dstBlock.x + pfillblock.dstBlock.width ;
            /* set gradient color */
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->b_clr, 4);
            /* draw rectangle */
            MApi_GFX_RectFill(&pfillblock);


            break;

        case GRADIENT_Y_CENTER_COLOR:
            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
            pfillblock.dstBlock.width = pclrBtn->width  ;
            pfillblock.dstBlock.height = pclrBtn->height / 2;
            /* set gradient color */
            pfillblock.flag = GFXRECT_FLAG_COLOR_GRADIENT_Y ;
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->g_clr, 4);

            /* draw rectangle */
            MApi_GFX_RectFill(&pfillblock);


            memcpy(&pfillblock.colorRange.color_s, &pclrBtn->g_clr, 4);
            pfillblock.dstBlock.y = pfillblock.dstBlock.y + pfillblock.dstBlock.height ;
            /* set gradient color */
            memcpy(&pfillblock.colorRange.color_e, &pclrBtn->b_clr, 4);
            /* draw rectangle */
            MApi_GFX_RectFill(&pfillblock);

            break;
    }

    /* draw rectangle frame */
    if(pclrBtn->fHighLight && pclrBtn->bFrameWidth)
    {
        pfillblock.dstBlock.x = pclrBtn->x;
        pfillblock.dstBlock.y = pclrBtn->y;
        pfillblock.dstBlock.width = pclrBtn->width;
        pfillblock.dstBlock.height = pclrBtn->height;
        memcpy(&pfillblock.colorRange.color_s, &pclrBtn->f_clr, 4);
        memcpy(&pfillblock.colorRange.color_e, &pclrBtn->f_clr, 4);
        pfillblock.flag = 0;

        pline.width = pclrBtn->bFrameWidth;
        MApi_GFX_RectFrame(&pfillblock, &pline);
    }



    msAPI_OSD_Free_resource();
//853YE
#endif

}

/******************************************************************************/
/// API for MMI only draw block:
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_DrawMMIBlock(OSDClrBtn *pclrBtn)
{
    U8 u8FrameLineWidth = 0;
    GFX_RectFillInfo pfillblock;

    /* Initialize the GE format for default setting(RGB565)*/
    pfillblock.fmt = GFX_FMT_RGB565; // 20091215

    /* set start point coordinate */
    pfillblock.dstBlock.x = pclrBtn->x;
    pfillblock.dstBlock.y = pclrBtn->y;

//    GELineRect.LineRectCoordinate.v0_x = pclrBtn->x;
//    GELineRect.LineRectCoordinate.v0_y = pclrBtn->y;

    msAPI_OSD_GET_resource();

    /* draw rectangle frame */
    if(pclrBtn->fHighLight && pclrBtn->bFrameWidth)
    {
        u8FrameLineWidth = pclrBtn->bFrameWidth;


        pfillblock.dstBlock.width = pclrBtn->width;
        pfillblock.dstBlock.height = pclrBtn->height;
        /* set gradient color */
        pfillblock.flag = GFXRECT_FLAG_COLOR_CONSTANT ;
        memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
        memcpy(&pfillblock.colorRange.color_e, &pclrBtn->b_clr, 4);

        MApi_GFX_RectFill(&pfillblock);

    }



    pfillblock.dstBlock.x = pclrBtn->x + u8FrameLineWidth;
    pfillblock.dstBlock.y = pclrBtn->y + u8FrameLineWidth;
    pfillblock.dstBlock.width = pclrBtn->width-(U16)(u8FrameLineWidth<<1);
    pfillblock.dstBlock.height = pclrBtn->height-(U16)(u8FrameLineWidth<<1);
    /* set gradient color */
    pfillblock.flag = GFXRECT_FLAG_COLOR_CONSTANT ;
    memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
    memcpy(&pfillblock.colorRange.color_e, &pclrBtn->b_clr, 4);

    MApi_GFX_RectFill(&pfillblock);




    msAPI_OSD_Free_resource();

}

/******************************************************************************/
/// API for draw block:
/// @param font_handle \b IN font handle
/// @param *pu8Str \b IN pointer to string
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_DrawButton(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn)
{
    /* check range */
/*
    if((pclrBtn->x + pclrBtn->width) > NEWUI_MAIN_MENU_GWIN_WIDTH)
    {
        return;
    }
    else if((pclrBtn->y + pclrBtn->height) > NEWUI_MAIN_MENU_GWIN_HEIGHT)
    {
        return;
    }
*/

    /*draw background rectangle*/

    msAPI_OSD_GET_resource();

    msAPI_OSD_DrawBlock(pclrBtn);

    /* draw text*/
    if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
    {
        if(*pu8Str == 0)
        {
            msAPI_OSD_Free_resource();
            return;
        }
    }
    else
    {
        //if(*((U16*)pu8Str) == 0)
        if(((pu8Str[1]<<8) + pu8Str[0]) == 0)
        {
            msAPI_OSD_Free_resource();
            return;
        }
    }

    msAPI_OSD_DrawText(font_handle, pu8Str, pclrBtn);

    msAPI_OSD_Free_resource();
}

/*****************************************************************************************************/

//static U16 angular_increment;
//static U16 normalised_angle;
static U16 x, y, last_y;
static U16 u16Temp1, u16Temp2, u16Temp3, u16Temp4, u16Temp5;
//static U32 u32Loop;


/******************************************************************************/
/// API for draw round frame:
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_DrawRoundFrame(OSDClrBtn *pclrBtn)
{
    GFX_RectFillInfo pfillblock;

    if ( pclrBtn->radius > pclrBtn->width / 2 || pclrBtn->radius > pclrBtn->height / 2 )
    {
        return;
    }

    msAPI_OSD_GET_resource();

    /* Initialize the GE format for default setting(RGB565)*/
    pfillblock.fmt = GFX_FMT_RGB565; // 20091215

    if ( ( pfillblock.dstBlock.width = pclrBtn->width - 2 * pclrBtn->radius ) > 0 )
    {
        /* draw top frame */
        pfillblock.dstBlock.x = pclrBtn->x + pclrBtn->radius;
        pfillblock.dstBlock.y = pclrBtn->y ;
        pfillblock.dstBlock.height = pclrBtn->bFrameWidth;
        /* set gradient color */
        pfillblock.flag = GFXRECT_FLAG_COLOR_CONSTANT ;
        memcpy(&pfillblock.colorRange.color_s, &pclrBtn->f_clr, 4);
        memcpy(&pfillblock.colorRange.color_e, &pclrBtn->f_clr, 4);

        MApi_GFX_RectFill(&pfillblock);


        /* draw bottom frame */
        pfillblock.dstBlock.y = pclrBtn->y + pclrBtn->height - pclrBtn->bFrameWidth - 1;
        MApi_GFX_RectFill(&pfillblock);

    }

    if ( ( pfillblock.dstBlock.height = pclrBtn->height - 2 * pclrBtn->radius ) > 0 )
    {
        /* draw left frame */
        pfillblock.dstBlock.x = pclrBtn->x;
        pfillblock.dstBlock.y = pclrBtn->y + pclrBtn->radius - 1;
        pfillblock.dstBlock.width = pclrBtn->bFrameWidth;
        pfillblock.dstBlock.height += 2;
        MApi_GFX_RectFill(&pfillblock);

        /* draw right frame */
        pfillblock.dstBlock.x = pclrBtn->x + pclrBtn->width - pclrBtn->bFrameWidth;
        MApi_GFX_RectFill(&pfillblock);

    }

    u16Temp1 = pclrBtn->x + pclrBtn->radius - 1;
    u16Temp2 = pclrBtn->y + pclrBtn->radius - 1;
    u16Temp3 = pclrBtn->x + pclrBtn->width - pclrBtn->radius - pclrBtn->bFrameWidth + 1;
    u16Temp4 = pclrBtn->y + pclrBtn->height - pclrBtn->radius - pclrBtn->bFrameWidth;
    last_y = 0;


    u16Temp5 = (pclrBtn->radius*pclrBtn->radius)<<2;
    for (y = 1; ;y++)
    {
        u16Temp5 = u16Temp5 - (y<<3) - 4;

        x = int_sqrt(u16Temp5);
        x = (x - 1)>>1;
        pfillblock.dstBlock.x = u16Temp1 - x;
        pfillblock.dstBlock.y = u16Temp2 - y;
        pfillblock.dstBlock.width = pclrBtn->bFrameWidth;
        pfillblock.dstBlock.height = pclrBtn->bFrameWidth;
        MApi_GFX_RectFill(&pfillblock);

        /* draw left-bottom quarter */
        pfillblock.dstBlock.y = u16Temp4 + y;
        MApi_GFX_RectFill(&pfillblock);

        /* draw right-bottom quarter */
        pfillblock.dstBlock.x = u16Temp3 + x;
        MApi_GFX_RectFill(&pfillblock);

        /* draw right-top quarter */
        pfillblock.dstBlock.y = u16Temp2 - y;
        MApi_GFX_RectFill(&pfillblock);

        /* symmetrical */
        pfillblock.dstBlock.x = u16Temp1 - y;
        pfillblock.dstBlock.y = u16Temp2 - x;
        MApi_GFX_RectFill(&pfillblock);

        /* draw left-bottom quarter */
        pfillblock.dstBlock.y = u16Temp4 + x;
        MApi_GFX_RectFill(&pfillblock);

        /* draw right-bottom quarter */
        pfillblock.dstBlock.x = u16Temp3 + y;
        MApi_GFX_RectFill(&pfillblock);

        /* draw right-top quarter */
        pfillblock.dstBlock.y = u16Temp2 - x;
        MApi_GFX_RectFill(&pfillblock);

        if (x <= y)
            break;
    }

    msAPI_OSD_Free_resource();

}
/******************************************************************************/
/// API for draw round block:
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_DrawRoundBlock(OSDClrBtn *pclrBtn)
{
    GFX_RectFillInfo pfillblock;

    if ( pclrBtn->radius > pclrBtn->width / 2 || pclrBtn->radius > pclrBtn->height / 2 )
    {
        return;
    }

    msAPI_OSD_GET_resource();

    /* Initialize the GE format for default setting(RGB565)*/
    pfillblock.fmt = GFX_FMT_RGB565; // 20091215

    pfillblock.dstBlock.x = pclrBtn->x;
    pfillblock.dstBlock.y = pclrBtn->y + pclrBtn->radius - 1;
    pfillblock.dstBlock.width = pclrBtn->width;
    pfillblock.dstBlock.height = pclrBtn->height - (2*pclrBtn->radius) + 1;
    memcpy(&pfillblock.colorRange.color_s, &pclrBtn->b_clr, 4);
    memcpy(&pfillblock.colorRange.color_e, &pclrBtn->g_clr, 4);
    pfillblock.flag = 0;
    MApi_GFX_RectFill(&pfillblock);


//    GELineRect.Gradient_Color_Flag        = GECOLOR_FLAG_NONCHANGE;
    /* draw top and bottom round */
    u16Temp1 = pclrBtn->x + pclrBtn->radius - 1;
    u16Temp2 = pfillblock.dstBlock.y;
    u16Temp3 = pclrBtn->width - 2 * pclrBtn->radius + 2;
    u16Temp4 = pclrBtn->y + pclrBtn->height - pclrBtn->radius;
    last_y = 0;

    u16Temp5 = (pclrBtn->radius*pclrBtn->radius)<<2;
    for ( y=1; ; y++ )
    {
        u16Temp5 = u16Temp5 - (y<<3) - 4;
        x = int_sqrt(u16Temp5);
        x = (x - 1)>>1;

        /* draw top round */
        pfillblock.dstBlock.x = u16Temp1 - x;
        pfillblock.dstBlock.y = u16Temp2 - y;
        pfillblock.dstBlock.width = u16Temp3 + (x<<1) ; // +1 for compensation of original formula
        pfillblock.dstBlock.height = (y - last_y);
        MApi_GFX_RectFill(&pfillblock);


        /* draw bottom round */
        //GELineRect.LineRectCoordinate.direction = 0x0;
        if(u16Temp4 + y - 1  <   u16Temp4 + last_y)
        {
            pfillblock.dstBlock.y = u16Temp4 + y - 1;
            pfillblock.dstBlock.height = u16Temp4 + last_y - pfillblock.dstBlock.y + 1;
        }
        else
        {
            pfillblock.dstBlock.y = u16Temp4 + last_y;
            pfillblock.dstBlock.height = u16Temp4 + y - pfillblock.dstBlock.y;
        }
        MApi_GFX_RectFill(&pfillblock);



        /* draw top round */
        //GELineRect.LineRectCoordinate.direction = 0x0;
        pfillblock.dstBlock.x = u16Temp1 - y;
        pfillblock.dstBlock.y = u16Temp2 - x;
        pfillblock.dstBlock.width =  u16Temp3 + (y<<1);
        pfillblock.dstBlock.height = u16Temp2 - y +1 - pfillblock.dstBlock.y;
        MApi_GFX_RectFill(&pfillblock);

        /* draw bottom round */
        //GELineRect.LineRectCoordinate.direction = 0x0;
        if(u16Temp4 + last_y  <   u16Temp4 + x - 1)
        {
            pfillblock.dstBlock.y = u16Temp4 + last_y;
            pfillblock.dstBlock.height = u16Temp4 + x - pfillblock.dstBlock.y;
        }
        else
        {
            pfillblock.dstBlock.y = u16Temp4 + x - 1;
            pfillblock.dstBlock.height = u16Temp4 + last_y  - pfillblock.dstBlock.y + 1;
        }

        MApi_GFX_RectFill(&pfillblock);



        last_y = y;

        if (x <= y)
            break;
    }

    if(pclrBtn->fHighLight && pclrBtn->bFrameWidth)
    {
        msAPI_OSD_DrawRoundFrame( pclrBtn );
    }
    else
    {

        /* anti-alias */
        last_y = 0;

//      PESet.PE_Enable_Flag = GE_PE_FLAG_ALPHABLENDING;
//      PESet.ABL.scoef = PESet.ABL.dcoef = 3;
//      PESet.ABL.abl_const = 0x66666666;
        //MDrv_GE_PixelEngine(&PESet);
        //MDrv_GE_SetAlpha(1,3,3,0x55555555);

        MApi_GFX_SetAlphaBlending(COEF_CONST, 0x00);
        MApi_GFX_SetAlphaSrcFrom(ABL_FROM_CONST);
        MApi_GFX_EnableAlphaBlending(TRUE);


        u16Temp5 = (pclrBtn->radius*pclrBtn->radius + (pclrBtn->radius>>1))<<2;

        for ( y=1; ; y++ )
        {
            u16Temp5 = u16Temp5 - (y<<3) - 4;
            x = int_sqrt(u16Temp5);
            x = (x - 1)>>1;

            /* draw top round */
            pfillblock.dstBlock.x = u16Temp1 - x;
            pfillblock.dstBlock.y = u16Temp2 - y;
            pfillblock.dstBlock.width = u16Temp3 + (x<<1) ;
            pfillblock.dstBlock.height = (y - last_y) + 1 ;
            MApi_GFX_RectFill(&pfillblock);


            /* draw bottom round */
            //GELineRect.LineRectCoordinate.direction = 0x0;
            if(u16Temp4 + last_y < u16Temp4 + y - 1)
            {
                pfillblock.dstBlock.y = u16Temp4 + last_y;
                pfillblock.dstBlock.height = u16Temp4 + y - pfillblock.dstBlock.y;
            }
            else
            {
                pfillblock.dstBlock.y = u16Temp4 + y - 1;
                pfillblock.dstBlock.height = u16Temp4 + last_y - pfillblock.dstBlock.y + 1;
            }
            MApi_GFX_RectFill(&pfillblock);


            /* draw top round */
            //GELineRect.LineRectCoordinate.direction = 0x0;
            pfillblock.dstBlock.x = u16Temp1 - y;
            pfillblock.dstBlock.y = u16Temp2 - x;
            pfillblock.dstBlock.width = u16Temp3 + (y<<1);
            pfillblock.dstBlock.height = u16Temp2 - y - pfillblock.dstBlock.y + 1;
            MApi_GFX_RectFill(&pfillblock);




            /* draw bottom round */
            //GELineRect.LineRectCoordinate.direction = 0x0;
            if( u16Temp4 + last_y < u16Temp4 + x - 1 )
            {
                pfillblock.dstBlock.y = u16Temp4 + last_y;
                pfillblock.dstBlock.height = u16Temp4 + x - pfillblock.dstBlock.y;
            }
            else
            {
                pfillblock.dstBlock.y = u16Temp4 + x - 1 ;
                pfillblock.dstBlock.height = u16Temp4 + last_y - pfillblock.dstBlock.y + 1;
            }

            MApi_GFX_RectFill(&pfillblock);


            last_y = y;

            if (x <= y)
                break;
        }

//        PESet.PE_Enable_Flag = GE_PE_FLAG_DEFAULT;
        //MDrv_GE_PixelEngine(&PESet);
        MApi_GFX_EnableAlphaBlending(FALSE);
       MApi_GFX_SetAlphaBlending(COEF_ASRC,0x00);

        /* end AA */
    }

        msAPI_OSD_Free_resource();

}
/******************************************************************************/
/// API for draw round button:
/// @param font_handle \b IN font handle
/// @param *pu8Str \b IN pointer to string
/// @param *pclrBtn \b IN: pointer to OSD component structure
/// -@see OSDClrBtn
/******************************************************************************/
void msAPI_OSD_DrawRoundButton(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn)
{
    /*
        GERGBColor b_clr,f_clr;
        GEPoint point;
        GEClrLine clrline;
        GELineFmt lineFmt;
        LONG32_BYTE u32clr;
        U16 radius;
    */

    /* check range */
    /*if ( ( pclrBtn->x + pclrBtn->width ) > NEWUI_MAIN_MENU_GWIN_WIDTH )
    {
        return;
    }
    else if ( ( pclrBtn->y + pclrBtn->height ) > NEWUI_MAIN_MENU_GWIN_HEIGHT )
    {
        return;
    }
    else*/ if ( pclrBtn->radius > pclrBtn->width / 2 || pclrBtn->radius > pclrBtn->height / 2 )
    {
        return;
    }

    msAPI_OSD_GET_resource();

    /* draw round block */
    msAPI_OSD_DrawRoundBlock(pclrBtn);

    /* draw text */
    if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
    {
        if(*pu8Str == 0)
               {
                     msAPI_OSD_Free_resource();
            return;
                }
    }
    else
    {
        //if(*((U16*)pu8Str) == 0)
        if(((pu8Str[1]<<8) + pu8Str[0]) == 0)
        {
            msAPI_OSD_Free_resource();
            return;
        }
    }

    pclrBtn->x += pclrBtn->radius;
    pclrBtn->width -= 2 * pclrBtn->radius;
       msAPI_OSD_DrawText(font_handle, pu8Str, pclrBtn);
    pclrBtn->x -= pclrBtn->radius;
    pclrBtn->width += 2 * pclrBtn->radius;

       msAPI_OSD_Free_resource();

}

#if 0
/*****************************************************************************************************/
void msAPI_OSD_DrawBitmap(BMPHANDLE Handle, U16 u16StartX, U16 u16StartY, GEBitmapFmt bmpfmt)
{
    GEPoint v0;
    v0.x = u16StartX;
    v0.y = u16StartY;

    if(bmpfmt.bBmpColorKeyEnable)
        MDrv_GE_SetSCK(ENABLE, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);

    //bmpfmt.bScale = FALSE;
    MDrv_GE_DrawBitmap(Handle, &v0, &bmpfmt);

    MDrv_GE_SetSCK(DISABLE, NULL, NULL);
}
#endif


/******************************************************************************/
/// API for draw block::
/// @param Handle \b IN bitmap handle
/// @param u16StartX \b IN x coordinate
/// @param u16StartY \b IN y coordinate
/// @param bmpfmt \b IN bitmap format
/******************************************************************************/
void msAPI_OSD_DrawBitmap(BMPHANDLE Handle, U16 u16StartX, U16 u16StartY, GEBitmapFmt bmpfmt)
{
    msAPI_OCP_DecompressHandle(Handle);

#if GE_DRIVER_TEST
    //if(bmpfmt.bBmpColorKeyEnable)
    //    MDrv_GE_SetSCK(ENABLE, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);

    PESet.PE_Enable_Flag = GE_PE_FLAG_SCK  ;
    //PESet.PE_Enable_Flag  = GE_PE_FLAG_ALPHABLENDING ;
    PESet.sck_set.sck_hth.u32Num = 0xff00ff;
    PESet.sck_set.sck_lth.u32Num = 0xff00ff;
    PESet.sck_set.sck_mode = 0x11;

    //PESet.ABL.abl_const = 0x808080;
    //PESet.ABL.dcoef = PESet.ABL.scoef = 0x3;

    MDrv_GE_PixelEngine(&PESet);

    //MDrv_GE_SetAlpha(ENABLE,0x3, 0x3,0x80808080);

    BitbltInfo.bmphandle = Handle;
    BitbltInfo.BitbltCoordinate.v0_x = u16StartX;
    BitbltInfo.BitbltCoordinate.v0_y = u16StartY;
    BitbltInfo.BitbltCoordinate.width = bmpfmt.width;
    BitbltInfo.BitbltCoordinate.height = bmpfmt.height;
    BitbltInfo.BitbltCoordinate.v2_x = 0;
    BitbltInfo.BitbltCoordinate.v2_y = 0;
    BitbltInfo.dst_fm = 0x17;
    BitbltInfo.src_fm = 0x17;
    if(bmpfmt.bScale)
        BitbltInfo.BmpFlag = GEBBT_FLAG_STBB;
    else
        BitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;

    MDrv_GE_DrawBitmap2(&BitbltInfo);
    //MDrv_GE_SetSCK(DISABLE, NULL, NULL);

    PESet.PE_Enable_Flag = GE_PE_FLAG_DEFAULT ;
    MDrv_GE_PixelEngine(&PESet);

#else

//    GEPoint v0;
    GFX_DrawBmpInfo gfx_bmpfmt;

    msAPI_OSD_GET_resource();

    gfx_bmpfmt.x = u16StartX;
    gfx_bmpfmt.y = u16StartY;



    if (bmpfmt.bBmpColorKeyEnable)
    {
        MApi_GFX_SetSrcColorKey(TRUE, CK_OP_EQUAL, GFX_FMT_ARGB8888, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);
    }



    bmpfmt.clrrange.color_s.r = 0xeF;
    bmpfmt.clrrange.color_s.g = 0x0;
    bmpfmt.clrrange.color_s.b = 0xeF;
    bmpfmt.clrrange.color_e.r = 0xFF;
    bmpfmt.clrrange.color_e.g = 0x0;
    bmpfmt.clrrange.color_e.b = 0xFF;
    //MDrv_GE_SetSCK(ENABLE, CK_OP_EQUAL, GFX_FMT_ARGB8888,  &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);
    MApi_GFX_SetSrcColorKey(TRUE, CK_OP_EQUAL, GFX_FMT_ARGB8888, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);

    MApi_GFX_SetNearestMode(false);
    MApi_GFX_SetPatchMode(true);

    gfx_bmpfmt.height = bmpfmt.height;
    gfx_bmpfmt.width = bmpfmt.width;
//    gfx_bmpfmt.x = v0.x;
//    gfx_bmpfmt.y = v0.y;
    gfx_bmpfmt.bScale= bmpfmt.bScale;

    //bmpfmt.bScale = FALSE;
    MApi_GFX_DrawBitmap(Handle, &gfx_bmpfmt);
    //MDrv_GE_DrawBitmap(Handle, &v0, &bmpfmt);
    MApi_GFX_SetNearestMode(false);
    MApi_GFX_SetPatchMode(false);
//    MDrv_GE_SetSCK(DISABLE, CK_OP_EQUAL, GFX_FMT_ARGB8888,  NULL, NULL);
    MApi_GFX_SetSrcColorKey(FALSE, CK_OP_EQUAL, GFX_FMT_ARGB8888, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);

#if SW_LOAD_BMP_ON_DEMAND
    //In this case, OSD bitmaps are decompressed dynamicly.
    //If we don't flush GE at this point, while GE is doing bitblt, its source buffer maybe overwritten by next turn OSD bitmaps decompression.
    MApi_GFX_FlushQueue();
#endif


    msAPI_OSD_Free_resource();

#endif
#if 0
    MsOS_DelayTask(500);

    BitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;

    MDrv_GE_DrawBitmap2(&BitbltInfo);

    MsOS_DelayTask(500);

    if(bmpfmt.bScale)
        BitbltInfo.BmpFlag = GEBBT_FLAG_STBB;
    else
        BitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;

    MDrv_GE_DrawBitmap2(&BitbltInfo);
#endif
}



/******************************************************************************/
/// API for draw bitmap specifically for subtitle:
/// @param Handle \b IN bitmap handle
/// @param u16StartX \b IN x coordinate
/// @param u16StartY \b IN y coordinate
/// @param bmpfmt \b IN bitmap format
/******************************************************************************/
void msAPI_OSD_DrawBitmap_Subtitle(BMPHANDLE Handle, U16 u16StartX, U16 u16StartY, GEBitmapFmt bmpfmt)
{

//    GEPoint v0;
    GFX_DrawBmpInfo gfx_bmpfmt;

    gfx_bmpfmt.x = u16StartX;
    gfx_bmpfmt.y = u16StartY;

    msAPI_OSD_GET_resource();

    if (bmpfmt.bBmpColorKeyEnable)
    {
        //MDrv_GE_SetSCK(ENABLE, CK_OP_EQUAL, GE_FMT_I8, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);
        MApi_GFX_SetSrcColorKey(TRUE, CK_OP_EQUAL, GFX_FMT_I8, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);

    }

    gfx_bmpfmt.height = bmpfmt.height;
    gfx_bmpfmt.width = bmpfmt.width;
//    gfx_bmpfmt.x = v0.x;
//    gfx_bmpfmt.y = v0.y;
    gfx_bmpfmt.bScale= bmpfmt.bScale;

    MApi_GFX_SetNearestMode(true);
    MApi_GFX_SetPatchMode(true);

    //bmpfmt.bScale = FALSE;
    MApi_GFX_DrawBitmap(Handle, &gfx_bmpfmt);
    MApi_GFX_SetNearestMode(false);
    MApi_GFX_SetPatchMode(false);
//    MDrv_GE_SetSCK(DISABLE, CK_OP_EQUAL, GE_FMT_I8,  NULL, NULL);
    MApi_GFX_SetSrcColorKey(FALSE, CK_OP_EQUAL, GFX_FMT_I8, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);

    msAPI_OSD_Free_resource();

}

/******************************************************************************/
/// API for drawing colorkey bitmap::
/// @param Handle \b IN handle to the bitmap
/// @param u16StartX \b IN start position X
/// @param u16StartY \b IN start position Y
/// @param bmpfmt \b IN bitmap format
/******************************************************************************/
void msAPI_OSD_DrawColorKeyBitmap(BMPHANDLE Handle, U16 u16StartX, U16 u16StartY, MSAPI_GEBitmapFmt bmpfmt)
{
  //  GEPoint v0;
    GFX_DrawBmpInfo gfx_bmpfmt;
    msAPI_OCP_DecompressHandle(Handle);

    msAPI_OSD_GET_resource();

    gfx_bmpfmt.x = u16StartX;
    gfx_bmpfmt.y = u16StartY;

    gfx_bmpfmt.height = bmpfmt.height;
    gfx_bmpfmt.width = bmpfmt.width;
    //gfx_bmpfmt.x = v0.x;
    //gfx_bmpfmt.y = v0.y;
    gfx_bmpfmt.bScale= bmpfmt.bScale;

    if (bmpfmt.bBmpColorKeyEnable)
    {
        //MDrv_GE_SetSCK(ENABLE, CK_OP_EQUAL, GFX_FMT_ARGB8888,  (GERGBColor *)&bmpfmt.clrrange.color_s, (GERGBColor *)&bmpfmt.clrrange.color_e);
        MApi_GFX_SetSrcColorKey(TRUE, CK_OP_EQUAL, GFX_FMT_ARGB8888, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);
    }

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
    MApi_GFX_SetNearestMode(true);
#else
    MApi_GFX_SetNearestMode(false);
#endif
    MApi_GFX_SetPatchMode(true);

    MApi_GFX_DrawBitmap(Handle, &gfx_bmpfmt);

    MApi_GFX_SetNearestMode(false);
    MApi_GFX_SetPatchMode(false);

    //MDrv_GE_SetSCK(DISABLE, CK_OP_EQUAL, GFX_FMT_ARGB8888,  NULL, NULL);
    MApi_GFX_SetSrcColorKey(FALSE, CK_OP_EQUAL, GFX_FMT_ARGB8888, &bmpfmt.clrrange.color_s, &bmpfmt.clrrange.color_e);

#if SW_LOAD_BMP_ON_DEMAND
    //In this case, OSD bitmaps are decompressed dynamicly.
    //If we don't flush GE at this point, while GE is doing bitblt, its source buffer maybe overwritten by next turn OSD bitmaps decompression.
    MApi_GFX_FlushQueue();
#endif

    msAPI_OSD_Free_resource();
}

/******************************************************************************/
/// API for set clip window::
/// @param x0 \b IN start x coordinate
/// @param y0 \b IN start y coordinate
/// @param x1 \b IN end x coordinate + 1 (not included in window)
/// @param y1 \b IN end y coordinate + 1 (not included in window)
/******************************************************************************/
void msAPI_OSD_SetClipWindow(U16 u16X0, U16 u16Y0, U16 u16X1, U16 u16Y1)
{
    GFX_Point v0, v1;
    msAPI_OSD_GET_resource();

    ClipWindow.x0 = u16X0;
    ClipWindow.y0 = u16Y0;
    ClipWindow.x1 = u16X1;
    ClipWindow.y1 = u16Y1;
    v0.x = u16X0;
    v0.y = u16Y0;
    v1.x = u16X1;
    v1.y = u16Y1;
    MApi_GFX_SetClip(&v0, &v1);
    msAPI_OSD_Free_resource();

}

/******************************************************************************/
/// API for restore the backuped clipwindow::
/******************************************************************************/
void msAPI_OSD_RestoreBackupClipWindow()
{
    GFX_Point v0, v1;

    msAPI_OSD_GET_resource();

    ClipWindow.x0 = ClipWindowBackup.x0;
    ClipWindow.y0 = ClipWindowBackup.y0;
    ClipWindow.x1 = ClipWindowBackup.x1;
    ClipWindow.y1 = ClipWindowBackup.y1;
//    MDrv_GE_SetClipWindow(ClipWindow.x0, ClipWindow.y0, ClipWindow.x1 - 1, ClipWindow.y1 - 1);
    v0.x = ClipWindowBackup.x0;
    v0.y = ClipWindowBackup.y0;
    v1.x = ClipWindowBackup.x1;
    v1.y = ClipWindowBackup.y1;
    MApi_GFX_SetClip(&v0, &v1);

    msAPI_OSD_Free_resource();

}

void msAPI_OSD_GetClipWindow(U16 *pX0, U16 *pY0, U16 *pX1, U16 *pY1)
{

    msAPI_OSD_GET_resource();

    *pX0 = ClipWindow.x0;
    *pY0 = ClipWindow.y0;
    *pX1 = ClipWindow.x1;
    *pY1 = ClipWindow.y1;
    //MDrv_GE_GetClipWindow(pX0, pY0, pX1, pY1);

    msAPI_OSD_Free_resource();

}

void msAPI_OSD_BackupClipWindow(void)
{
    ClipWindowBackup.x0 = ClipWindow.x0;
    ClipWindowBackup.y0 = ClipWindow.y0;
    ClipWindowBackup.x1 = ClipWindow.x1;
    ClipWindowBackup.y1 = ClipWindow.y1;
}

/******************************************************************************/
/// API for set Dither::
/// @param bEnable \b IN turn on/off
/******************************************************************************/
void msAPI_OSD_SetDither(BOOLEAN bEnable)
{
    msAPI_OSD_GET_resource();

    MApi_GFX_SetDither(bEnable);

    msAPI_OSD_Free_resource();
}
#if (KEEP_UNUSED_FUNC == 1)
/******************************************************************************/
/// API for set rotation::
/// @param locrotate \b IN local rotation
/// @param glorotate \b IN global rotation
/******************************************************************************/
void msAPI_OSD_SetRotation(U8 locrotate,U8 glorotate)
{
       msAPI_OSD_GET_resource();

       MApi_GFX_SetRotate(locrotate);

       msAPI_OSD_Free_resource();
}
#endif



// Wrapper
BMPHANDLE MDrv_GE_LoadBitmap(MS_U32 addr, MS_U32 u32len, MS_U16 u16width, MS_U16 u16height, MS_U8 dstloc)
{
    UNUSED(dstloc);

    return msAPI_OSD_RESOURCE_LoadBitmap(addr, u32len, u16width, u16height, BMP_FMT_ARGB1555);
}

void MDrv_GE_DrawBitmap(BMPHANDLE handle, GEPoint *ppoint, GEBitmapFmt *pbmpfmt)
{
  //  GEPoint v0;
    GFX_DrawBmpInfo gfx_bmpfmt;

    gfx_bmpfmt.x = ppoint->x;
    gfx_bmpfmt.y = ppoint->y;

    gfx_bmpfmt.height = pbmpfmt->height;
    gfx_bmpfmt.width = pbmpfmt->width;

    gfx_bmpfmt.bScale= pbmpfmt->bScale;
    MApi_GFX_DrawBitmap(handle, &gfx_bmpfmt);

}


void MDrv_GE_BitBlt(GEBitBltInfo *BitbltInfo, GEPitBaseInfo *PitBaseInfo)
{

    GFX_DrawRect bitbltInfo;
    GFX_BufferInfo srcbuf_bak, dstbuf_bak, srcbuf, dstbuf;
    MS_U32 flag = 0;

    bitbltInfo.srcblk.x = BitbltInfo->BitbltCoordinate.v2_x;
    bitbltInfo.srcblk.y = BitbltInfo->BitbltCoordinate.v2_y;
    bitbltInfo.srcblk.width = BitbltInfo->src_width;
    bitbltInfo.srcblk.height = BitbltInfo->src_height;

    bitbltInfo.dstblk.x = BitbltInfo->BitbltCoordinate.v0_x;
    bitbltInfo.dstblk.y = BitbltInfo->BitbltCoordinate.v0_y;
    bitbltInfo.dstblk.width = BitbltInfo->BitbltCoordinate.width;
    bitbltInfo.dstblk.height = BitbltInfo->BitbltCoordinate.height;

    MApi_GFX_GetBufferInfo(&srcbuf_bak, &dstbuf_bak);

    // there is no such source format, set to legacy 1555.
    if( GFX_FMT_ARGB1555_DST == BitbltInfo->src_fm )
    {
        srcbuf.u32ColorFmt = GFX_FMT_ARGB1555;
        MApi_GFX_SetAlpha_ARGB1555(0xFF); //for alpha channel of ARGB1555 bitblt
    }
    else
        srcbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo->src_fm;
    srcbuf.u32Addr = PitBaseInfo->sb_base;
    srcbuf.u32Pitch = PitBaseInfo->sb_pit;
    MApi_GFX_SetSrcBufferInfo(&srcbuf, 0);

    dstbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo->dst_fm;
    dstbuf.u32Addr = PitBaseInfo->db_base;
    dstbuf.u32Pitch = PitBaseInfo->db_pit;
    MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

//printf("MDrv_GE_BitBlt: %x, %x, %x, %x, %x, %x\n", srcbuf.u32ColorFmt, srcbuf.u32Addr, srcbuf.u32Pitch, dstbuf.u32ColorFmt,
//        dstbuf.u32Addr, dstbuf.u32Pitch );

    if( (bitbltInfo.srcblk.width != bitbltInfo.dstblk.width) ||
        (bitbltInfo.srcblk.height != bitbltInfo.dstblk.height))
        flag = GFXDRAW_FLAG_SCALE;

    {
        MApi_GFX_BitBlt(&bitbltInfo, flag);
    }

    MApi_GFX_SetSrcBufferInfo(&srcbuf_bak, 0);
    MApi_GFX_SetDstBufferInfo(&dstbuf_bak, 0);


}
#if TXTFONT_ZOOM2X
#define SUB_BOTTOM_ALIGN 0

void msAPI_OSD_Draw2BytesText_Zoom2X(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn)
{
    U16 i, len, u16StrWidth;
    U16 cut_strlen,scale;
    U16 max_width=0, dot_width=0;
    OSD_RESOURCE_FONT_INFO finfo;
    GFX_TextOutInfo text_info;
    OSDSRC_GLYPH_DISP_INFO *pGlyphDispInfo=NULL;
    OSDSRC_GLYPH_DISP_INFO pglyphDot[3];
    U8 pu8dotStr[4];
    S8 gap=0;
    BOOLEAN bExceed = FALSE;
    U16 width_offset = 0;
    U16 ScaleRatio=1;

     msAPI_OSD_GET_resource();
    /* check range */
    /*if((pclrBtn->x + pclrBtn->width) > NEWUI_MAIN_MENU_GWIN_WIDTH)
    {
        return;
    }
    else if((pclrBtn->y + pclrBtn->height) > NEWUI_MAIN_MENU_GWIN_HEIGHT)
    {
        return;
    }
    else*/ if((len = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        msAPI_OSD_Free_resource();
        return;
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
   // pclrBtn->Fontfmt.ifont_gap=pclrBtn->Fontfmt.ifont_gap+2;
    scale = 200;  // 200
    pclrBtn->Fontfmt.flag |=GEFONT_FLAG_SCALE;  // cann't use
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        //scale = ((U16)pclrBtn->Fontfmt.height*100 / (U16)finfo.height);
        pclrBtn->Fontfmt.height = scale * finfo.height /100;

        //scale = (U8)((U16)pclrBtn->Fontfmt.width*100 / (U16)finfo.width);
        pclrBtn->Fontfmt.width = scale * finfo.width /100;
    }
    pGlyphDispInfo = msAPI_Memory_Allocate( sizeof(GLYPH_DISP_INFO) * len,BUF_ID_GLYPH_DISP_INFO);
    if(pGlyphDispInfo == NULL)
    {
        APIOSD_DBG(printf("E_DrawText>> pGlyphDispInfo == NULL\n"));
        msAPI_OSD_Free_resource();
        return;
    }

    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
    {
        gap= pclrBtn->Fontfmt.ifont_gap;
    }
    else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
    {
       gap=pclrBtn->Fontfmt.dis;
    }
    max_width = pclrBtn->width;

    msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, CHAR_DOT, &pglyphDot[0]);
    for (i = 0; i < 3; i++)
    {
       memcpy(&pglyphDot[i], &pglyphDot[0], sizeof(OSDSRC_GLYPH_DISP_INFO));
    }
    dot_width += (3*(pglyphDot[0].u8Width)+gap);

    max_width -= dot_width;

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
        {
            for (i=0; i<len; i++)
            {
                scale =100;
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu8Str[i], &pGlyphDispInfo[i]);
                pGlyphDispInfo[i].u8Width = pGlyphDispInfo[i].u8Width * scale / 100;
            }
        }
        else
        {
            //pu16Str = (U16*) pu8Str;
            scale =100;
            for (i=0; i<len; i++)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, (pu8Str[i*2+1]<<8) | pu8Str[i*2], &pGlyphDispInfo[i]);
                pGlyphDispInfo[i].u8Width = (pGlyphDispInfo[i].u8Width * scale
#if ENABLE_DEFAULT_KERNING
                    //- kerningX_(pu16Str[i], pu16Str[i+1])
                    - kerningX_((pu8Str[i*2+1]<<8) | pu8Str[i*2], (pu8Str[i*4+1]<<8) | pu8Str[i*4])
#endif //ENABLE_DEFAULT_KERNING
                    ) / 100;
            }
        }
    }
    else
    {
        if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
        {
            for (i=0; i<len; i++)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, pu8Str[i], &pGlyphDispInfo[i]);
            }
        }
        else
        {
            for (i=0; i<len; i++)
            {
                msAPI_OSD_RESOURCE_GetGlyphDispInfo(font_handle, (pu8Str[i+1]<<8) | pu8Str[i], &pGlyphDispInfo[i]);
            }
        }
    }

    u16StrWidth = 0;
    cut_strlen=len;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        ScaleRatio=pclrBtn->Fontfmt.width/finfo.width;
        for (i=0; i< len; i++)
        {
            if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
            {
               u16StrWidth +=pGlyphDispInfo[i].u8Width*ScaleRatio;
            }
            else
           {
              u16StrWidth += pGlyphDispInfo[i].u8Width;
           }
        }

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            u16StrWidth += ((len-1) * gap);
        }
    }
    else  // gap/compact + italic
    {
        // italic or default
        ScaleRatio=1;
        u16StrWidth = finfo.width * ScaleRatio * len;

        // with gap or compact, only one of two
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            u16StrWidth +=  ((len-1) * gap);
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            u16StrWidth -=  ((len-1) * gap);
        }
    }
     if (u16StrWidth >= (max_width+dot_width))
     {
         while(u16StrWidth>=max_width)
         {
              cut_strlen--;
              if( max_width == 0)
              {
                  break;
              }
              else
              {
                  if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
                      u16StrWidth -= (pGlyphDispInfo[cut_strlen].u8Width*ScaleRatio + gap);
                  else
                      u16StrWidth -= (finfo.width + gap);
              }
        }
          bExceed = TRUE;
          width_offset = u16StrWidth;
          u16StrWidth += dot_width;
    }

    /* draw string */
    switch(pclrBtn->enTextAlign)
    {
        case EN_ALIGNMENT_DEFAULT: //without BTN_TEXT_GAP
            text_info.dstblk.x = pclrBtn->x;
            break;

        case EN_ALIGNMENT_LEFT:
            text_info.dstblk.x = pclrBtn->x + BTN_TEXT_GAP;
            break;

        case EN_ALIGNMENT_RIGHT:
            if (u16StrWidth + BTN_TEXT_GAP > pclrBtn->width)
                text_info.dstblk.x = pclrBtn->x;
            else
                text_info.dstblk.x = pclrBtn->x + pclrBtn->width - BTN_TEXT_GAP - u16StrWidth;
            break;

        case EN_ALIGNMENT_CENTER:
            if (u16StrWidth > pclrBtn->width)
            {
                 text_info.dstblk.x = pclrBtn->x;
            }
            else
            {
               text_info.dstblk.x = pclrBtn->x + (pclrBtn->width - u16StrWidth) / 2;
            }
            break;
    }

    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height * scale / 100) / 2;
    }
    else
    {
        text_info.dstblk.y = pclrBtn->y + (S16)(pclrBtn->height - finfo.height) / 2;
    }
    if (text_info.dstblk.y > 32767)
    {
        //overflow
        text_info.dstblk.y = 0;
    }

    if (cut_strlen > 0)
     {
            if (bExceed)
            {
                  if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
                 {
                     pu8dotStr[3] = 0; // .
                     pu8dotStr[2] = CHAR_DOT; // .
                     pu8dotStr[1] = CHAR_DOT; //
                     pu8dotStr[0] = CHAR_DOT; // .
                 }
                 else
                 {
                     pu8dotStr[3] = 0; // .
                     pu8dotStr[2] = 0; // .
                     pu8dotStr[1] = 0; //
                     pu8dotStr[0] = CHAR_DOT; // .
                 }

             text_info.dstblk.x += width_offset;
             text_info.dstblk.width = pclrBtn->Fontfmt.width;;
             text_info.dstblk.height = pclrBtn->Fontfmt.width;;
             text_info.flag = pclrBtn->Fontfmt.flag;
             memcpy(&text_info.color, &pclrBtn->t_clr, 4);
             text_info.pGlyphDispInfo = (GFX_GlyphDispInfo*)&pglyphDot;
             text_info.gap = pclrBtn->Fontfmt.ifont_gap;
             MApi_GFX_TextOut(font_handle, (MS_U8*)pu8dotStr, pclrBtn->bStringIndexWidth+1, &text_info);
             text_info.dstblk.x -=  width_offset;
            }
            if(pclrBtn->bStringIndexWidth == CHAR_IDX_1BYTE)
            {
                pu8Str[cut_strlen] = 0;
            }
            else
            {
               pu8Str[cut_strlen*2] = 0;
               pu8Str[cut_strlen*2+1] = 0;
            }
    text_info.dstblk.width = pclrBtn->Fontfmt.width;
    text_info.dstblk.height = pclrBtn->Fontfmt.height;
    text_info.flag = pclrBtn->Fontfmt.flag;
    memcpy(&text_info.color, &pclrBtn->t_clr, 4);
    text_info.pGlyphDispInfo = (GFX_GlyphDispInfo*)pGlyphDispInfo;
    text_info.gap = pclrBtn->Fontfmt.ifont_gap;

    //printf("\nW:%d,H:%d",text_info.dstblk.width,text_info.dstblk.height);
    //printf("\nFW:%d,FH:%d",pclrBtn->Fontfmt.width,pclrBtn->Fontfmt.height);
    #if ENABLE_ZUI_BACKGROUND_PINK_SUBTITLE_PATCH////issue: subtitle not blending in mm
    MApi_GFX_SetAlpha(false, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
    #else
    MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, text_info.color.a);
    #endif
    MApi_GFX_TextOut(font_handle, pu8Str, pclrBtn->bStringIndexWidth+1, &text_info);
    }

    if(pGlyphDispInfo != NULL)
    {
        MSAPI_MEMORY_FREE(pGlyphDispInfo,BUF_ID_GLYPH_DISP_INFO);
    }

    msAPI_OSD_Free_resource();
}
void msAPI_OSD_DrawPunctuatedString_Zoom2X(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num)
{
    S8  gap;
    U8  rowgap;
    U16 iRow;
    #if (SUB_BOTTOM_ALIGN)
    U16 iRow2;
    #endif
    U8  scale, offset_len;
    U16 input_strlen;
    U16 input_char_count, input_last_char_count, output_char_count, output_last_char_count;
    U16 input_char_width, output_total_width, output_last_total_width, max_row_width;
    //U16 *pOutputString;
    U8 *pOutputString;
    U16 input_char_data;

    OSD_RESOURCE_FONT_INFO finfo;
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;

    BOOLEAN bIsOneByteString;
    BOOLEAN bIsChar_CRLF    = FALSE;
    BOOLEAN bIsChar_0x86    = FALSE;
    BOOLEAN bIsChar_0x87    = FALSE;
    BOOLEAN bIsChar_SHY     = FALSE;
    BOOLEAN bIsChar_LastSHY = FALSE;
    BOOLEAN bIsChar_Normal  = FALSE;

    BOOLEAN bIsChangRowByAuto = FALSE;

    U16 u16OriginalPosition_x   = pclrBtn->x;
    U16 u16OriginalPosition_y   = pclrBtn->y;
    U16 u16OriginalFontfmtFlag  = pclrBtn ->Fontfmt.flag;

    U8  TempStr2[STROSD];

//    U32 _timer = msAPI_Timer_GetTime0();

    // Abnormal condition
    if(max_row_num == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> max_row_num = 0\n"););
        return;
    }
    else if ((input_strlen = msAPI_OSD_GetStrLength(pu8Str, pclrBtn->bStringIndexWidth)) == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> strlen = 0\n"););
        return;
    }


    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_GET_resource();
    //pOutputString = (U16*)TempStr;
    pOutputString = TempStr2;

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
    //pclrBtn->Fontfmt.ifont_gap=pclrBtn->Fontfmt.ifont_gap+2;

    if(0)//pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)(pclrBtn->Fontfmt.height / finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * 2;

        scale = (U8)(pclrBtn->Fontfmt.width / finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * 2;
    }
    else
    {
        scale = 1;
    }

//scale = 2;
//finfo.width = 2*finfo.width;
//finfo.height= 2*finfo.height;
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
    {
        gap = pclrBtn->Fontfmt.ifont_gap;
    }
    else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
    {
        gap = -pclrBtn->Fontfmt.dis;
    }
    else
    {
        gap = 0;
    }

    bIsOneByteString        = (pclrBtn->bStringIndexWidth & CHAR_IDX_1BYTE) ? TRUE : FALSE;
    max_row_width           = pclrBtn->width - 2*BTN_TEXT_GAP;
    input_last_char_count   = 0;
    output_total_width      = 0;

    DBG_SMART_TEXT(printf("< Start > gap = %bd, input_strlen = %u\n", gap, input_strlen););

    #if (SUB_BOTTOM_ALIGN)
    for (iRow2=0, input_char_count=0; (iRow2<max_row_num) && (input_char_count < input_strlen);)
    {
        // Reset variable
        output_char_count       = 0;
        output_last_char_count  = 0;
        output_last_total_width = 0;
        bIsChar_CRLF            = FALSE;
        bIsChar_SHY             = FALSE;
        bIsChar_LastSHY         = FALSE;
        bIsChar_0x86            = FALSE;
        bIsChar_0x87            = FALSE;
        bIsChar_Normal          = FALSE;

        // Filter one word (end with space or control code)
        while ( (output_total_width<max_row_width) && (input_char_count < input_strlen) && ( output_char_count < STROSD))
        {
            if (bIsOneByteString)   // One byte string
            {
                input_char_data = pu8Str[input_char_count];
                // Contrl code, SHY or space char
                if ((0x20==input_char_data) || ((0x80<=input_char_data)&&(input_char_data<=0x9F)) )
                {
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0x8A==input_char_data )            // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0x86==input_char_data )       // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0x87==input_char_data )       // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        pu8Str[input_char_count]  = 0x20;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal      = TRUE;
                }
            }
            else    // Two bytes string
            {
                //input_char_data = pu16Str[input_char_count];
                input_char_data = (pu8Str[input_char_count*2+1]<<8) + pu8Str[input_char_count*2];
                if ( 0x00AD==input_char_data)               // SHY - soft hyphen
                {
                    bIsChar_SHY     = TRUE;
                    bIsChar_LastSHY = TRUE;
                }
                else if ((0x0020==input_char_data) || ( (0xE080<=input_char_data) && (input_char_data<=0xE09F) ) )
                {
                    bIsChar_LastSHY         = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0xE08A==input_char_data )          // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0xE086==input_char_data )     // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0xE087==input_char_data )     // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal          = TRUE;
                }
            }

            // Retrieve input char width or add null char
            if (bIsChar_Normal || bIsChar_SHY)
            {
                if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
                {
                    if (bIsOneByteString)   // One byte string
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[input_char_count], &BBox_X_Info);
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                    }

                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                }
                else
                {
                    input_char_width = finfo.width;
                    input_char_width = (output_char_count==0) ? (finfo.width) : (finfo.width*scale+gap);
                }

                bIsChar_Normal = FALSE;
            }
            else
            {
                input_char_count++;
                break;
            }

            // check if string width larger than OSD display width
            if ((output_total_width+input_char_width) < max_row_width)
            {
                if (bIsChar_SHY)    // add normal char and space
                {
                    // Save temporary Last SHY char position for display
                    bIsChar_SHY             = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char
                }
                else                // space and other char
                {
                    if(bIsOneByteString)
                    {
                        ;
                    }
                    else
                        output_char_count++;

                    output_total_width += input_char_width;
                }

                input_char_count++;
                if (input_char_count>=input_strlen)     // Draw to the last char
                {
                    bIsChar_LastSHY = FALSE;
                    break;
                }
            }
            else
                break;
        }           // End of while loop

        {
            // Control code handle
            if (bIsChar_0x86 || bIsChar_0x87)          // character emphasis on/off
            {
                ;
            }
            else
            {
                output_total_width     = 0;
                iRow2++;
            }
            offset_len = 1; // the var needs to be initialized
            if (input_char_count < input_strlen)
            {
                input_char_count = input_last_char_count+1;
            }
        }
    }

    //printf("\n=============");
    //printf("\nRow Num = %d",iRow2);
    if(iRow2 < max_row_num)
        pclrBtn->y += pclrBtn->height*(max_row_num - iRow2);
    #endif


    // Row handle loop
    for (iRow=0, input_char_count=0; (iRow<max_row_num) && (input_char_count < input_strlen);)
    {
        if (iRow==1)
        {
            u16NextLineStartInx = input_char_count;
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("< iRow = %u > input_char_count = %u, input_strlen = %u\n", iRow, input_char_count, input_strlen););
        }

        // Reset variable
        output_char_count       = 0;
        output_last_char_count  = 0;
        output_last_total_width = 0;
        bIsChar_CRLF            = FALSE;
        bIsChar_SHY             = FALSE;
        bIsChar_LastSHY         = FALSE;
        bIsChar_0x86            = FALSE;
        bIsChar_0x87            = FALSE;
        bIsChar_Normal          = FALSE;

      if((0x0020 == ReadU16LE(&pu8Str[input_char_count*2])
        || 0xE08A == ReadU16LE(&pu8Str[input_char_count*2]))
        && (output_char_count == 0))
        {
           DBG_SMART_TEXT(printf("======> control code at first char[%d][0x%04x]\n", input_char_count, ReadU16LE(&pu8Str[input_char_count*2])));
           input_char_count++;
        }

        // Filter one word (end with space or control code)
        while ( (output_total_width<max_row_width) && (input_char_count < input_strlen) && ( output_char_count < STROSD))
        {
            if (bIsOneByteString)   // One byte string
            {
                input_char_data = pu8Str[input_char_count];
                // Contrl code, SHY or space char
                if ((0x20==input_char_data) || ((0x80<=input_char_data)&&(input_char_data<=0x9F)) )
                {
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0x8A==input_char_data )            // CR/LF
                    {
                        if(bIsChangRowByAuto)
                        {
                            bIsChar_Normal      = TRUE;
                            pu8Str[input_char_count]  = 0x20;
                            bIsChangRowByAuto = FALSE;
                        }
                        else
                        {
                             bIsChar_CRLF        = TRUE;
                        }
                    }
                    else if ( 0x86==input_char_data )       // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0x87==input_char_data )       // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        pu8Str[input_char_count]  = 0x20;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal      = TRUE;
                }
            }
            else    // Two bytes string
            {
                //input_char_data = pu16Str[input_char_count];
                input_char_data = (pu8Str[input_char_count*2+1]<<8) + pu8Str[input_char_count*2];
                if ( 0x00AD==input_char_data)               // SHY - soft hyphen
                {
                    DBG_SMART_TEXT(printf ("<< SHY [%2u] 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_SHY     = TRUE;
                    bIsChar_LastSHY = TRUE;
                }
                else if ((0x0020==input_char_data) || ( (0xE080<=input_char_data) && (input_char_data<=0xE09F) ) )
                {
                    DBG_SMART_TEXT(printf ("<< Control Code [%2u] = 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_LastSHY         = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if ( 0xE08A==input_char_data )          // CR/LF
                    {
                        if(bIsChangRowByAuto)
                        {
                            bIsChar_Normal  = TRUE;
                            pu8Str[input_char_count*2] = 0x20;
                            pu8Str[input_char_count*2+1] = 0x00;
                            bIsChangRowByAuto = FALSE;
                        }
                        else
                        {
                             bIsChar_CRLF        = TRUE;
                        }
                    }
                    else if ( 0xE086==input_char_data )     // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0xE087==input_char_data )     // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        //pu16Str[input_char_count] = 0x0020;
                        pu8Str[input_char_count*2] = 0x20;
                        pu8Str[input_char_count*2+1] = 0x00;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal          = TRUE;
                }
            }

            // Retrieve input char width or add null char
            if (bIsChar_Normal || bIsChar_SHY)
            {
                if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
                {
                    if (bIsOneByteString)   // One byte string
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[input_char_count], &BBox_X_Info);
                    }
                    else
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                    }

                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                }
                else
                {
                    input_char_width = finfo.width;
                    input_char_width = (output_char_count==0) ? (finfo.width) : (finfo.width*scale+gap);
                }

                bIsChar_Normal = FALSE;
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)pOutputString)[output_char_count] = 0;
                    pOutputString[output_char_count] = 0;
                }
                else
                {
                    //pOutputString[output_char_count] = 0;
                    pOutputString[output_char_count*2] = 0;
                    pOutputString[output_char_count*2+1] = 0;
                }

                input_char_count++;
                break;
            }

            // check if string width larger than OSD display width
          if ((output_total_width+input_char_width) < max_row_width)
            {
                if (bIsChar_SHY)    // add normal char and space
                {
                    // Save temporary Last SHY char position for display
                    bIsChar_SHY             = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char
                }
                else                // space and other char
                {
                    if(bIsOneByteString)
                    {
                        //((U8*)pOutputString)[output_char_count++] = pu8Str[input_char_count];
                        pOutputString[output_char_count++] = pu8Str[input_char_count];
                    }
                    else
                    {
                        //pOutputString[output_char_count++] = pu16Str[input_char_count];
                        pOutputString[(output_char_count)*2] = pu8Str[input_char_count*2];
                        pOutputString[(output_char_count)*2+1] = pu8Str[input_char_count*2+1];
                        output_char_count++;
                    }

                    output_total_width += input_char_width;
                }

                //if (g_EpgTest)
                {
                    DBG_SMART_TEXT(printf("pu16Str[%2u]= 0x%04x(%c), input_char_width = %02u, last_total_width = %4u, output_total_width = %4u, max_row_width =%4u\n", input_char_count, pu16Str[input_char_count], (U8)pu16Str[input_char_count], input_char_width, output_last_total_width, output_total_width, max_row_width););
                }

                input_char_count++;
                if (input_char_count>=input_strlen)     // Draw to the last char
                {
                    bIsChar_LastSHY = FALSE;
                    break;
                }
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)pOutputString)[output_last_char_count] = 0;
                    pOutputString[output_last_char_count] = 0;
                }
                else
                {
                    //pOutputString[output_last_char_count] = 0;
                    pOutputString[output_last_char_count*2] = 0;
                    pOutputString[output_last_char_count*2+1] = 0;
                }
                bIsChangRowByAuto = TRUE;
                break;
            }
        }           // End of while loop

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("1 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
        }

        // Draw text to last control char or space char
        //if ( (output_last_char_count > 0) || (output_char_count > 0))
        {
            // Control code handle
            if (bIsChar_0x86 || bIsChar_0x87)          // character emphasis on/off
            {
                msAPI_OSD_Draw2BytesText(font_handle, pOutputString, pclrBtn);

                pclrBtn->x = u16OriginalPosition_x + output_last_total_width;

                if (bIsChar_0x86)
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_BOLD;
                }
                else
                {
                    pclrBtn->Fontfmt.flag = u16OriginalFontfmtFlag;
                }
            }
            else
            {
                if (bIsChar_LastSHY)        // Last SHY - soft hyphen
                {
                    pOutputString[output_last_char_count]   = 0x00AD;
                    pOutputString[output_last_char_count+1] = 0;
                }
                else                        // Space char or other
                {
                    pOutputString[(output_char_count*2)]   = 0;
                    pOutputString[(output_char_count*2)+1]   = 0;
                }

                msAPI_OSD_Draw2BytesText_Zoom2X(font_handle, pOutputString, pclrBtn);
                pclrBtn->x  = u16OriginalPosition_x;
                rowgap = 15;
                pclrBtn->y += pclrBtn->height + rowgap;// add gap between rows for divx sub show
                output_total_width     = 0;
                iRow++;
            }
            offset_len = 1; // the var needs to be initialized
            if (input_char_count < input_strlen)
            {
                input_char_count = input_last_char_count+1;
            }
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("2 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
            DBG_SMART_TEXT(printf ("<< (x, y) = (%4u, %4u) >>\n", pclrBtn->x, pclrBtn->y););
        }

        if (input_char_count < input_strlen)
        {
            bStopScrollDown = FALSE;
        }
        else
        {
            bStopScrollDown = TRUE;
        }
    }

    pclrBtn->y = u16OriginalPosition_y;

    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_Free_resource();

    //printf ("Time = %lu\n", _timer = msAPI_Timer_DiffTimeFromNow(_timer));
}
#endif

#if (ENABLE_UI_3D_PROCESS)
void MDrv_GE_ColorKeyBitBlt(GEBitBltInfo *BitbltInfo, GEPitBaseInfo *PitBaseInfo, MS_U32 clrKeyFrom, MS_U32 clrKeyTo)
{
    GFX_DrawRect bitbltInfo;
    GFX_BufferInfo srcbuf_bak, dstbuf_bak, srcbuf, dstbuf;
    MS_U32 flag = 0;
    MSAPI_GEColorRange clrrange;

    clrrange.color_s.a = 0;
    clrrange.color_s.r=((clrKeyFrom&0x00ff0000)>>16)&0xff;
    clrrange.color_s.g=((clrKeyFrom&0x0000ff00)>>8)&0xff;
    clrrange.color_s.b=((clrKeyFrom&0x000000ff))&0xff;

    clrrange.color_e.a = 0;
    clrrange.color_e.r=((clrKeyTo&0x00ff0000)>>16)&0xff;
    clrrange.color_e.g=((clrKeyTo&0x0000ff00)>>8)&0xff;
    clrrange.color_e.b=((clrKeyTo&0x000000ff))&0xff;

    bitbltInfo.srcblk.x = BitbltInfo->BitbltCoordinate.v2_x;
    bitbltInfo.srcblk.y = BitbltInfo->BitbltCoordinate.v2_y;
    bitbltInfo.srcblk.width = BitbltInfo->src_width;
    bitbltInfo.srcblk.height = BitbltInfo->src_height;

    bitbltInfo.dstblk.x = BitbltInfo->BitbltCoordinate.v0_x;
    bitbltInfo.dstblk.y = BitbltInfo->BitbltCoordinate.v0_y;
    bitbltInfo.dstblk.width = BitbltInfo->BitbltCoordinate.width;
    bitbltInfo.dstblk.height = BitbltInfo->BitbltCoordinate.height;

    MApi_GFX_GetBufferInfo(&srcbuf_bak, &dstbuf_bak);

    // there is no such source format, set to legacy 1555.
    if( GFX_FMT_ARGB1555_DST == BitbltInfo->src_fm )
    {
        srcbuf.u32ColorFmt = GFX_FMT_ARGB1555;
        MApi_GFX_SetAlpha_ARGB1555(0xFF); //for alpha channel of ARGB1555 bitblt
    }
    else
        srcbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo->src_fm;
    srcbuf.u32Addr = PitBaseInfo->sb_base;
    srcbuf.u32Pitch = PitBaseInfo->sb_pit;
    MApi_GFX_SetSrcBufferInfo(&srcbuf, 0);

    dstbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo->dst_fm;
    dstbuf.u32Addr = PitBaseInfo->db_base;
    dstbuf.u32Pitch = PitBaseInfo->db_pit;
    MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

//printf("MDrv_GE_BitBlt: %x, %x, %x, %x, %x, %x\n", srcbuf.u32ColorFmt, srcbuf.u32Addr, srcbuf.u32Pitch, dstbuf.u32ColorFmt,
//        dstbuf.u32Addr, dstbuf.u32Pitch );

    MApi_GFX_SetNearestMode(true); //always enable for color key
    MApi_GFX_SetSrcColorKey(TRUE, CK_OP_EQUAL, GFX_FMT_ARGB8888, &clrrange.color_s, &clrrange.color_e);

#if 1//((GE_BITMAP_FORMAT == MPLAYER_I8) || (GE_BITMAP_FORMAT == MPLAYER_ARGB4444) || (GE_BITMAP_FORMAT == MPLAYER_ARGB8888))//have alpha
    MApi_GFX_SetDither (FALSE); //NOTE: dither is enabled if and only if drawing is total opacity!!
    {
        MApi_GFX_EnableAlphaBlending(TRUE);
        MApi_GFX_SetAlphaSrcFrom( ABL_FROM_ADST ) ;
        MApi_GFX_SetAlphaBlending(COEF_ASRC, 0xFF);
    }
#else
    MApi_GFX_SetDither (TRUE);
    {
        MApi_GFX_EnableAlphaBlending(TRUE);
        MApi_GFX_SetAlphaSrcFrom( ABL_FROM_ADST ) ;
        MApi_GFX_SetAlphaBlending(COEF_ONE, 0xFF);
    }
#endif

    if( (bitbltInfo.srcblk.width != bitbltInfo.dstblk.width) ||
        (bitbltInfo.srcblk.height != bitbltInfo.dstblk.height))
        flag = GFXDRAW_FLAG_SCALE;

    {
        MApi_GFX_BitBlt(&bitbltInfo, flag);
    }

    MApi_GFX_SetSrcBufferInfo(&srcbuf_bak, 0);
    MApi_GFX_SetDstBufferInfo(&dstbuf_bak, 0);

    MApi_GFX_SetNearestMode(false);

}

void MDrv_GE_StretchBitBltPixelAlpha(GEBitBltInfo *BitbltInfo, GEPitBaseInfo *PitBaseInfo)
{

    GFX_DrawRect bitbltInfo;
    GFX_BufferInfo srcbuf_bak, dstbuf_bak, srcbuf, dstbuf;
    MS_U32 flag = 0;

    bitbltInfo.srcblk.x = BitbltInfo->BitbltCoordinate.v2_x;
    bitbltInfo.srcblk.y = BitbltInfo->BitbltCoordinate.v2_y;
    bitbltInfo.srcblk.width = BitbltInfo->src_width;
    bitbltInfo.srcblk.height = BitbltInfo->src_height;

    bitbltInfo.dstblk.x = BitbltInfo->BitbltCoordinate.v0_x;
    bitbltInfo.dstblk.y = BitbltInfo->BitbltCoordinate.v0_y;
    bitbltInfo.dstblk.width = BitbltInfo->BitbltCoordinate.width;
    bitbltInfo.dstblk.height = BitbltInfo->BitbltCoordinate.height;

    MApi_GFX_GetBufferInfo(&srcbuf_bak, &dstbuf_bak);

    // there is no such source format, set to legacy 1555.
    if( GFX_FMT_ARGB1555_DST == BitbltInfo->src_fm )
    {
        srcbuf.u32ColorFmt = GFX_FMT_ARGB1555;
        MApi_GFX_SetAlpha_ARGB1555(0xFF); //for alpha channel of ARGB1555 bitblt
    }
    else
        srcbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo->src_fm;
    srcbuf.u32Addr = PitBaseInfo->sb_base;
    srcbuf.u32Pitch = PitBaseInfo->sb_pit;
    MApi_GFX_SetSrcBufferInfo(&srcbuf, 0);

    dstbuf.u32ColorFmt = (GFX_Buffer_Format)BitbltInfo->dst_fm;
    dstbuf.u32Addr = PitBaseInfo->db_base;
    dstbuf.u32Pitch = PitBaseInfo->db_pit;
    MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

//printf("MDrv_GE_BitBlt: %x, %x, %x, %x, %x, %x\n", srcbuf.u32ColorFmt, srcbuf.u32Addr, srcbuf.u32Pitch, dstbuf.u32ColorFmt,
//        dstbuf.u32Addr, dstbuf.u32Pitch );
    MApi_GFX_SetNearestMode(FALSE); //not color key, so disable it
#if 1//((GE_BITMAP_FORMAT == MPLAYER_I8) || (GE_BITMAP_FORMAT == MPLAYER_ARGB4444) || (GE_BITMAP_FORMAT == MPLAYER_ARGB8888))//have alpha
    MApi_GFX_SetDither (FALSE); //NOTE: dither is enabled if and only if drawing is total opacity!!
    {
        MApi_GFX_EnableAlphaBlending(TRUE);
        MApi_GFX_SetAlphaSrcFrom( ABL_FROM_ADST ) ;
        MApi_GFX_SetAlphaBlending(COEF_ASRC, 0xFF);
    }
#else
    MApi_GFX_SetDither (TRUE);
    {
        MApi_GFX_EnableAlphaBlending(TRUE);
        MApi_GFX_SetAlphaSrcFrom( ABL_FROM_ADST ) ;
        MApi_GFX_SetAlphaBlending(COEF_ONE, 0xFF);
    }
#endif

    if( (bitbltInfo.srcblk.width != bitbltInfo.dstblk.width) ||
        (bitbltInfo.srcblk.height != bitbltInfo.dstblk.height))
        flag = GFXDRAW_FLAG_SCALE;

    {
        MApi_GFX_BitBlt(&bitbltInfo, flag);
    }

    MApi_GFX_SetSrcBufferInfo(&srcbuf_bak, 0);
    MApi_GFX_SetDstBufferInfo(&dstbuf_bak, 0);
}


#endif

#if ENABLE_ATSC

void msAPI_OSD_GetPunctuatedStringRowsLine(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num, U16 *pu16rows)
{
    S8  gap;
    U16 iRow;
    U8  scale, offset_len;
    U16 input_strlen;
    U16 input_char_count, input_last_char_count, output_char_count, output_last_char_count;
    U16 input_char_width=0, output_total_width, output_last_total_width, max_row_width;
    //U16 *u8TempStr;
    U8 u8TempStr[STROSD*2];
    U16 input_char_data, input_char_data_next;

    OSD_RESOURCE_FONT_INFO finfo;
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    BOOLEAN bIsOneByteString;
    BOOLEAN bSetNextLineStartInx    = FALSE;
    BOOLEAN bIsSpecialCharacterUsed = FALSE;
    BOOLEAN bIsChar_CRLF    = FALSE;
    BOOLEAN bIsChar_0x86    = FALSE;
    BOOLEAN bIsChar_0x87    = FALSE;
    BOOLEAN bIsChar_SHY     = FALSE;
    BOOLEAN bIsChar_LastSHY = FALSE;
    BOOLEAN bIsChar_Normal  = FALSE;

    U16 u16OriginalPosition_x   = pclrBtn->x;
    U16 u16OriginalPosition_y   = pclrBtn->y;
    U16 u16OriginalFontfmtFlag  = pclrBtn ->Fontfmt.flag;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
    OSDStringType TempBuf;
    OSDStringTypeDouble outbuf;
    #if ( ENABLE_ARABIC_OSD )
        OSDStringType out;
        U8 bMirrorLang = FALSE;
        U8 bArabicDisplay = FALSE;
        U8 bHebrew = FALSE;
    #endif
    #if ( ENABLE_THAI_OSD )
        U8 bThaiDisplay = FALSE;
    #endif
    U16 nFontID;
#endif
//    FONTHANDLE Org_font_handle = font_handle;

//    U32 _timer = msAPI_Timer_GetTime0();
    memset(&finfo, 0, sizeof(OSD_RESOURCE_FONT_INFO));

    *pu16rows = 0;

    // Abnormal condition
    if(max_row_num == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> max_row_num = 0\n"););
        return;
    }
    else if ((input_strlen = msAPI_OSD_u16Strlen((U16*)(void*)pu8Str)) == 0)
    {
        DBG_SMART_TEXT(printf("E_DrawSmartText>> strlen = 0\n"););
        return;
    }


    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_GET_resource();
    //u8TempStr = (U16*)TempStr;

#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )

#if (ENABLE_TTF_FONT)
    switch(MApp_GetLanguageForFont())
#else
    switch(enLanguage)
#endif
    {
    #if ( ENABLE_ARABIC_OSD )
        case LANGUAGE_OSD_ARABIC:
        case LANGUAGE_OSD_PARSI:
        case LANGUAGE_OSD_KURDISH:
#if (ENABLE_TTF_FONT)
        case LANGUAGE_OSD_UYGHUR:
#endif
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( bHebrewMixedMode )
                    {
                        bHebrew = TRUE;
                    }
                    else if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                    {
                        font_handle = Font[nFontID+FONT_ARABIC_0].fHandle;
                    }

                    if ( !bDivxSubtitleMode )
                    {
                        pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
                    }
                }
            }

            if ( bHebrew == FALSE )
            {
                bArabicDisplay = TRUE;
            }
            break;
        case LANGUAGE_OSD_HEBREW:
            bHebrew = TRUE;
            if ( !bDivxSubtitleMode )
            {
                pclrBtn->Fontfmt.flag |= GEFONT_FLAG_MIRROR;
            }
            else
            {
                //msAPI_OSD_Set_H_Mirror(FALSE);
            }
            break;
    #endif
    #if ( ENABLE_THAI_OSD )
        case LANGUAGE_OSD_THAI:
            nFontID = FontHandleIndex[font_handle];
            if ( nFontID < FONT_MULTILANG_BEGIN )
            {
            /*
                if ( (bDivxSubtitleMode) && ( External Subtitle Language is Hebrew ) )
                {
                    bHebrew = TRUE;
                }
                else
            */
                {
                    if ( ( nFontID < FONT_EXT_BEGIN ) /*&& ( !bDivxSubtitleText )*/ )
                        font_handle = Font[nFontID+FONT_THAI_0].fHandle;
                }
            }

    #if ( ENABLE_ARABIC_OSD )
            if ( bHebrew == FALSE )
    #endif
            {
                bThaiDisplay = TRUE;
            }
            break;
    #endif
        default:
            break;
    }
#endif

#if 0//(ENABLE_LANGUAGE_KOREA)
          if(enLanguage==LANGUAGE_OSD_KOREAN)
          {
           font_handle = Font[FONT_KOREA].fHandle;
       }
#endif

#if (ENABLE_ARABIC_OSD)
    if ( (bArabicDisplay) || (bHebrew) /*|| ( External Subtitle Language is Arabic ) || ( External Subtitle Language is Hebrew )*/ )
    {
        bMirrorLang = TRUE;
    }

#endif

    if(pclrBtn->bStringIndexWidth==CHAR_IDX_1BYTE)
    {
        if (input_strlen >= sizeof(TempStr.U8Str))
        {
            input_strlen = sizeof(TempStr.U8Str) - 1;
        }

    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            U16 i;

            memcpy(out.U8Str, pu8Str, input_strlen);
            for(i = 0; i < input_strlen; i++)
            {
                TempBuf.U8Str[i] = out.U8Str[(input_strlen-1)-i];
            }
            TempBuf.U8Str[input_strlen] = 0;
            pu8Str = TempBuf.U8Str;
        }
        else
        {
    #endif
            //memcpy(TempBuf.U8Str,pu8Str,len);
    #if (ENABLE_ARABIC_OSD)
        }
    #endif
    }
    else
    {
    #if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) )
        if (input_strlen >= sizeof(TempBuf.U8Str)/2)
        {
            input_strlen = sizeof(TempBuf.U8Str)/2 - 1;
        }
    #endif

    #if (ENABLE_ARABIC_OSD)
        if ( bMirrorLang )
        {
            memcpy(TempBuf.U8Str,pu8Str,input_strlen*2);
            TempBuf.U16Str[input_strlen] = 0;

            //For Subtitle
            if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /*|| ( External Subtitle Language is Arabic )*/ ) )
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //Every language is possible, you can't skip this filter here
                msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
            }
            else if ( bArabicDisplay ) //for OSD
            {
                S32 errorCode = U_ZERO_ERROR;

                ArabicParser(TempBuf.U16Str, input_strlen, outbuf.U16Str, STROSD,
                         U_SHAPE_LETTERS_SHAPE|U_SHAPE_LENGTH_FIXED_SPACES_AT_END|U_SHAPE_PRESERVE_PRESENTATION,
                         &errorCode);
                //just skip this function for non Kurdish condition
                if ( enLanguage == LANGUAGE_OSD_KURDISH )
                {
                    msAPI_OSD_KurdishFilter(outbuf.U16Str, input_strlen);
                }
            }
            else    // for Hebrew
            {
                            memcpy(outbuf.U8Str, TempBuf.U8Str, input_strlen*2);
            }

                   outbuf.U16Str[input_strlen] = 0;
                   pu8Str = outbuf.U8Str;
            }

    #endif
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);
    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)(pclrBtn->Fontfmt.height / finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)(pclrBtn->Fontfmt.width / finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }
    else
    {
        scale = 1;
    }

#if (ENABLE_THAI_OSD)
    if ( ( bThaiDisplay ) /* || ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
    {
        //temp solution for compiler warning
        memcpy(TempBuf.U8Str, pu8Str, input_strlen*2);

        input_strlen = Thai_compose(TempBuf.U16Str, 0, input_strlen, STROSD, outbuf.U16Str);
        outbuf.U16Str[input_strlen] = 0x0000;

        pu8Str = outbuf.U8Str;
    }
#endif

    if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
    {
    #if (ENABLE_ARABIC_OSD)
        if ( (bArabicDisplay) /*|| ( ( External Subtitle Language is Arabic ) && (bDivxSubtitleMode == TRUE) )*/ )
        {
            pclrBtn->Fontfmt.ifont_gap = 0;
        }
    #endif

        gap = pclrBtn->Fontfmt.ifont_gap;
    }
    else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
    {
        gap = -pclrBtn->Fontfmt.dis;
    }
    else
    {
        gap = 0;
    }

    bIsOneByteString        = (pclrBtn->bStringIndexWidth & CHAR_IDX_1BYTE) ? TRUE : FALSE;
    max_row_width           = pclrBtn->width - 2*BTN_TEXT_GAP;
    input_last_char_count   = 0;
    output_total_width      = 0;

    DBG_SMART_TEXT(printf("< Start > gap = %bd, input_strlen = %u\n", gap, input_strlen););

    // Row handle loop
    for (iRow=0, input_char_count=0; (iRow<max_row_num) && (input_char_count < input_strlen);)
    {
        if (iRow==1 && bSetNextLineStartInx == FALSE)
        {
            if(0xE08A == ReadU16LE(&pu8Str[input_char_count*2]))
            {
                u16NextLineStartInx = (input_char_count+1);
            }
            else
            {
                u16NextLineStartInx = input_char_count;
            }

            bSetNextLineStartInx = TRUE;
        }

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("< iRow = %u > input_char_count = %u, input_strlen = %u\n", iRow, input_char_count, input_strlen););
        }

        // Reset variable
        output_char_count       = 0;
        output_last_char_count  = 0;
        output_last_total_width = 0;
        bIsChar_CRLF            = FALSE;
        bIsChar_SHY             = FALSE;
        bIsChar_LastSHY         = FALSE;
        bIsChar_0x86            = FALSE;
        bIsChar_0x87            = FALSE;
        bIsChar_Normal          = FALSE;

        // Filter one word (end with space or control code)
        while ( (output_total_width<max_row_width) && (input_char_count < input_strlen) && ( output_char_count < (STROSD-1)))
        {
            if (bIsOneByteString)   // One byte string
            {
                input_char_data = pu8Str[input_char_count];
                input_char_data_next = pu8Str[input_char_count+1];
                // Contrl code, SHY or space char
                if ((0x20==input_char_data) || ((0x80<=input_char_data)&&(input_char_data<=0x9F)) )
                {
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if (( 0x8A==input_char_data ) && ( 0x8A!=input_char_data_next ))          // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0x86==input_char_data )       // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0x87==input_char_data )       // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        pu8Str[input_char_count]  = 0x20;
                    }
                }
                else                                        // Normal char
                {
                    bIsChar_Normal      = TRUE;
                }
            }
            else    // Two bytes string
            {
                //input_char_data = pu16Str[input_char_count];
                input_char_data = (pu8Str[input_char_count*2+1]<<8) + pu8Str[input_char_count*2];
                input_char_data_next = (pu8Str[(input_char_count+1)*2+1]<<8) + pu8Str[(input_char_count+1)*2];
                if ( 0x00AD==input_char_data)               // SHY - soft hyphen
                {
                      bIsSpecialCharacterUsed=TRUE;
                    DBG_SMART_TEXT(printf ("<< SHY [%2u] 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_SHY     = TRUE;
                    bIsChar_LastSHY = TRUE;
                }
                else if ((0x0020==input_char_data) || ( (0xE080<=input_char_data) && (input_char_data<=0xE09F) ) )
                {
                       bIsSpecialCharacterUsed=TRUE;
                    DBG_SMART_TEXT(printf ("<< Control Code [%2u] = 0x%04X >>\n", input_char_count, input_char_data););

                    bIsChar_LastSHY         = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char

                    if (( 0xE08A==input_char_data ) && ( 0xE08A!=input_char_data_next ))         // CR/LF
                    {
                        bIsChar_CRLF        = TRUE;
                    }
                    else if ( 0xE086==input_char_data )     // character emphasis on
                    {
                        bIsChar_0x86        = TRUE;
                    }
                    else if ( 0xE087==input_char_data )     // character emphasis off
                    {
                        bIsChar_0x87        = TRUE;
                    }
                    else                                    // space char and other
                    {
                        bIsChar_Normal      = TRUE;
                        //pu16Str[input_char_count] = 0x0020;
                        pu8Str[input_char_count*2] = 0x20;
                        pu8Str[input_char_count*2+1] = 0x00;
                    }
                }
                  else if (bIsSpecialCharacterUsed==FALSE && (output_total_width + input_char_width >= max_row_width))
                  {


                    bIsChar_LastSHY         = FALSE;
                      input_last_char_count   = input_char_count-1;
                      output_last_char_count  = output_char_count;    // Save the char count to last control char
                      output_last_total_width = output_total_width;   // Save the display width to last control char
                      bIsChar_CRLF        = TRUE;
                  }
                else                                         // Normal char
                {
                    bIsChar_Normal          = TRUE;
                }
            }

            // Retrieve input char width or add null char
            if (bIsChar_Normal || bIsChar_SHY)
            {
                if(pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
                {
                    if (bIsOneByteString)   // One byte string
                    {
                        msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu8Str[input_char_count], &BBox_X_Info);
                    }
                    else
                    {
                    #if (ENABLE_ARABIC_OSD)
                        //For Subtitle
                        if ( (bDivxSubtitleMode == TRUE) && ( (bArabicDisplay) /* || (External Subtitle Language is Arabic) */ ) )
                        {
                            U16 u16Unicode;

                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                u16Unicode = (pu8Str[input_char_count*2-1]<<8) + pu8Str[input_char_count*2-2];

                                if ( msAPI_OSD_IsArabicVowel( u16Unicode ) )
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, u16Unicode, &BBox_X_Info);
                                    //in Arabic language mode, gap is always zero, so we can forget gap value
                                    output_total_width -= (BBox_X_Info.u8Width*scale+gap);
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else if ( bArabicDisplay ) //for OSD
                        {
                            // Check if it is in Arabic Vowel unicode range
                            if ( input_char_count > 0 )
                            {
                                if ( msAPI_OSD_IsArabicVowel( input_char_data ) )
                                {
                                    //skip current vowel character width
                                    //do nothing here
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                    #if (ENABLE_THAI_OSD)
                        if ( ( bThaiDisplay ) /*|| ((bDivxSubtitleMode) && (External Subtitle Language is Thai))*/ )
                        {
                            // Check Primary Thai unicode range
                            if ( ( input_char_data <= 0x0E5B ) && ( input_char_data >= 0x0E01 ) )
                            {
                                if ( MinusDrawTable[ input_char_data - 0x0E01 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else if ( ( input_char_data <= 0xF71A ) && ( input_char_data >= 0xF700 ) )
                            {
                                if ( MinusDrawTablePersentation[ input_char_data - 0xF700 ] )
                                {
                                    //Minus coordinate, don't add width
                                    input_char_width = 0;
                                }
                                else
                                {
                                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                    input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                                }
                            }
                            else
                            {
                                msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                                input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                            }
                        }
                        else
                    #endif
                        {
                            msAPI_OSD_RESOURCE_GetBBox_X(font_handle, input_char_data, &BBox_X_Info);
                            input_char_width = (output_char_count==0) ? (BBox_X_Info.u8Width*scale) : (BBox_X_Info.u8Width*scale+gap);
                        }
                    }
                }
                else
                {
                    input_char_width = finfo.width;
                    input_char_width = (output_char_count==0) ? (finfo.width) : (finfo.width*scale+gap);
                }

                bIsChar_Normal = FALSE;
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_char_count] = 0;
                    u8TempStr[output_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_char_count] = 0;
                    u8TempStr[output_char_count*2] = 0;
                    u8TempStr[output_char_count*2+1] = 0;
                }

                input_char_count++;
                break;
            }

            // check if string width larger than OSD display width
            if ((output_total_width+input_char_width) < max_row_width)
            {
                if (bIsChar_SHY)    // add normal char and space
                {
                    // Save temporary Last SHY char position for display
                    bIsChar_SHY             = FALSE;
                    input_last_char_count   = input_char_count;
                    output_last_char_count  = output_char_count;    // Save the char count to last control char
                    output_last_total_width = output_total_width;   // Save the display width to last control char
                }
                else                // space and other char
                {
                    if(bIsOneByteString)
                    {
                        //((U8*)u8TempStr)[output_char_count++] = pu8Str[input_char_count];
                        u8TempStr[output_char_count++] = pu8Str[input_char_count];
                    }
                    else
                    {
                        //u8TempStr[output_char_count++] = pu16Str[input_char_count];
                        u8TempStr[(output_char_count)*2] = pu8Str[input_char_count*2];
                        u8TempStr[(output_char_count)*2+1] = pu8Str[input_char_count*2+1];
                        output_char_count++;
                    }

                    output_total_width += input_char_width;
                }

                //if (g_EpgTest)
                {
                    DBG_SMART_TEXT(printf("pu16Str[%2u]= 0x%04x(%c), input_char_width = %02u, last_total_width = %4u, output_total_width = %4u, max_row_width =%4u\n", input_char_count, pu16Str[input_char_count], (U8)pu16Str[input_char_count], input_char_width, output_last_total_width, output_total_width, max_row_width););
                }

                input_char_count++;
                if (input_char_count>=input_strlen)     // Draw to the last char
                {
                    bIsChar_LastSHY = FALSE;
                    break;
                }
            }
            else
            {
                if(bIsOneByteString)
                {
                    //((U8*)u8TempStr)[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count] = 0;
                }
                else
                {
                    //u8TempStr[output_last_char_count] = 0;
                    u8TempStr[output_last_char_count*2] = 0;
                    u8TempStr[output_last_char_count*2+1] = 0;
                }
                break;
            }
        }           // End of while loop

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("1 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
        }

        // Draw text to last control char or space char
        //if ( (output_last_char_count > 0) || (output_char_count > 0))
        {
            // Control code handle
            if (bIsChar_0x86 || bIsChar_0x87)          // character emphasis on/off
            {
                //msAPI_OSD_Draw2BytesText(Org_font_handle, u8TempStr, pclrBtn);

                pclrBtn->x = u16OriginalPosition_x + output_last_total_width;

                if (bIsChar_0x86)
                {
                    pclrBtn->Fontfmt.flag |= GEFONT_FLAG_BOLD;
                }
                else
                {
                    pclrBtn->Fontfmt.flag = u16OriginalFontfmtFlag;
                }
            }
            else
            {
                if(bIsChar_LastSHY && ((pu8Str[input_last_char_count*2+1]<<8) + pu8Str[input_last_char_count*2] == 0x20) )
                    bIsChar_LastSHY = FALSE;

                if (bIsChar_LastSHY)        // Last SHY - soft hyphen
                {
                    u8TempStr[output_last_char_count*2]   = 0xAD; //0x00AD
                    u8TempStr[(output_last_char_count*2)+1] = 0x00;
                    u8TempStr[(output_last_char_count*2)+2] = 0x00; //0x0000
                    u8TempStr[(output_last_char_count*2)+3] = 0x00;

                }
                else                        // Space char or other
                {
                    u8TempStr[(output_char_count*2)]   = 0;
                    u8TempStr[(output_char_count*2)+1]   = 0;
                }

                //msAPI_OSD_Draw2BytesText(font_handle, u8TempStr, pclrBtn);
                pclrBtn->x  = u16OriginalPosition_x;
                pclrBtn->y += pclrBtn->height;
                output_total_width     = 0;
                  bIsSpecialCharacterUsed = FALSE;
                iRow++;
            }
            offset_len = 1; // the var needs to be initialized
            if (input_char_count < input_strlen)
            {
                input_char_count = input_last_char_count+1;
            }
            if(iRow < MAX_LINE_ADDDR_NUM)
                g_u16LineAddrs[iRow] = input_char_count;
        }

        *pu16rows = iRow;

        //if (g_EpgTest)
        {
            DBG_SMART_TEXT(printf("2 >> In: char_count= %2u(0x%4X), last_char_count = %2u, Out: char_count = %2u, last_char_count = %2u\n", input_char_count, input_char_data, input_last_char_count, output_char_count, output_last_char_count););
            DBG_SMART_TEXT(printf ("<< (x, y) = (%4u, %4u) >>\n", pclrBtn->x, pclrBtn->y););
        }

        if (input_char_count < input_strlen)
        {
            bStopScrollDown = FALSE;
        }
        else
        {
            bStopScrollDown = TRUE;
        }
    }

    pclrBtn->y = u16OriginalPosition_y;

    // To handle GE Mutex for HKMCU and MHEG engine
    msAPI_OSD_Free_resource();

    //printf ("Time = %lu\n", _timer = msAPI_Timer_DiffTimeFromNow(_timer));



#if 0



    S8 gap;
    U8 scale, i, offset_len, cut_strlen;
    U16 total_strlen, width; //, u16Char;
    U16 max_width, buf_y;
    OSD_RESOURCE_FONT_INFO finfo;
    OSDSRC_GLYPH_BBOX_X BBox_X_Info;
    //For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    BOOLEAN bGetLastSpaceinSingleLine;
    U8 u8LastSpaceIndex;
    U16 u16LastSpace_Width;
    U8 bExceed = FALSE;

    memset(&finfo, 0, sizeof(OSD_RESOURCE_FONT_INFO));
    *pu8rows = 0;
    *pu16height = 0;

    /*prevent error*/
    if (pclrBtn->bStringIndexWidth != CHAR_IDX_2BYTE)
    {
        APIOSD_DBG(printf("Only support 2 bytes strubg\n"));
        return;
    }

    /*/For Last one Space character(ASCII code 0x20) of current string to be displayed in current OSD line.
    if (max_row_num == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> max_row_num = 0\n"));
        return;
    }
    else*/ if ((total_strlen = msAPI_OSD_GetStrLength((U8*)pu16Str, CHAR_IDX_2BYTE/*pclrBtn->bStringIndexWidth*/)) == 0)
    {
        APIOSD_DBG(printf("E_DrawSmartText>> strlen = 0\n"));
        return;
    }

    msAPI_OSD_RESOURCE_GetFontInfo(font_handle, &finfo);

    scale = 1;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_SCALE)
    {
        scale = (U8)((U16)pclrBtn->Fontfmt.height / (U16)finfo.height);
        pclrBtn->Fontfmt.height = finfo.height * scale;

        scale = (U8)((U16)pclrBtn->Fontfmt.width / (U16)finfo.width);
        pclrBtn->Fontfmt.width = finfo.width * scale;
    }

    if (total_strlen >= sizeof(TempStr.U8Str)/2)
    {
        total_strlen = sizeof(TempStr.U8Str)/2 - 1;
    }

#if 0//(ENABLE_LANGUAGE_KOREA)
          if(enLanguage==LANGUAGE_OSD_KOREAN)
          {
           font_handle = Font[FONT_KOREA].fHandle;
       }
#endif

    {
    //memcpy(outbuf.U8Str,(U8 *)pu16Str,total_strlen*2);

    //outbuf.U16Str[total_strlen] = 0;

    //pu16Str = outbuf.U16Str;
    }

    gap = 0;
    if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
    {
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
    }
    else
    {
        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_GAP)
        {
            gap = pclrBtn->Fontfmt.ifont_gap;
        }
        else if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_COMPACT)
        {
            gap = -pclrBtn->Fontfmt.dis;
        }
    }

    offset_len = 1; //2;
    buf_y = pclrBtn->y;
    max_width = pclrBtn->width - 2*BTN_TEXT_GAP;

    for (i=0; i<max_row_num && total_strlen; i++)
    {

    printf("i=%d, total_strlen=%d \n", i, total_strlen);

        width = 0;
        cut_strlen = 0;
        bGetLastSpaceinSingleLine=FALSE;//Reset variable
        u8LastSpaceIndex = 0;//Reset variable
        u16LastSpace_Width = 0; //Reset variable
        bExceed = FALSE;

        if (pclrBtn->Fontfmt.flag & GEFONT_FLAG_VARWIDTH)
        {
            while (width<max_width && cut_strlen<total_strlen)
            {
                {
                    msAPI_OSD_RESOURCE_GetBBox_X(font_handle, pu16Str[cut_strlen], &BBox_X_Info);
                    width += (BBox_X_Info.u8Width*scale + gap);
                }

                cut_strlen++;

                if ((pu16Str[(cut_strlen-1)]==0x20)||((pu16Str[(cut_strlen-1)]>=0x80)&&(pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                    bGetLastSpaceinSingleLine = TRUE;

                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }
        else
        {
            while(width<max_width && cut_strlen<total_strlen)
            {
                cut_strlen++;
                width += (finfo.width + gap);
                if ((pu16Str[(cut_strlen-1)]==0x20)||((pu16Str[(cut_strlen-1)]>=0x80)&&(pu16Str[(cut_strlen-1)]<=0x9F)) )//if Space Char or Control code
                {
                    u8LastSpaceIndex =  cut_strlen;//Set the LastSpaceIndex to current string index.
                    u16LastSpace_Width = width; //Set the LastSpace_Width to current string width.
                    bGetLastSpaceinSingleLine = TRUE;

                    if ( pu16Str[(cut_strlen-1)]==0x8A )
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                        break;
                    }
                    else
                    {
                        //don't modify...pu16Str[(cut_strlen-1)]=0x20;
                    }
                }
            }
        }

        if (width >= max_width)
        {
            //cut_strlen--;
            bExceed = TRUE;
        }

        APIOSD_DBG(printf("DrawSmartText>> cut_strlen = %bu\n", cut_strlen));

        if (cut_strlen == 0)
        {
            break;
        }
        else
        {
            /*
            if (bExceed && i == max_row_num-1)
            {
                //pu16Str[cut_strlen-1] = 0x01; // ...
                pu16Str[cut_strlen-2] = CHAR_DOT; // .
                pu16Str[cut_strlen-1] = CHAR_DOT; // .
            }
            u16Char = pu16Str[cut_strlen];
            pu16Str[cut_strlen] = 0;
            msAPI_OSD_DrawText(Org_font_handle, (U8*)pu16Str, pclrBtn);
            pu16Str[cut_strlen] = u16Char;
            */

            *(pu8rows) += 1;
            *(pu16height) += pclrBtn->height;

printf("*(pu8rows)=%d, *(pu16height)=%d \n", *(pu8rows), *(pu16height));

            total_strlen -= cut_strlen;
            pu16Str += (cut_strlen*offset_len);
        }
        pclrBtn->y += pclrBtn->height;
    }

    pclrBtn->y = buf_y;

    #endif
}
#endif
#undef MSAPI_OSD_C
