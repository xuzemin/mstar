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


#ifndef __MSAPI_MLE_LE_C__
#define __MSAPI_MLE_LE_C__

#ifdef __FEATURE_VECTOR_FONT__
/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"

#include "msAPI_MLE_font_vector.h"

#include "msAPI_MLE_le.h"
#include "msAPI_MLE_le_otf.h"
#include "msAPI_MLE_le_otf_def.h"

LE_ClassDefinitionType_e msAPI_MLE_Le_GetGlyphClass( U16 u16GlyphId )
{
    const U8 *pDefTable = msAPI_MLE_FONTBASE_VectorFontGetGDEFTable();
    LE_ClassDefinitionType_e eType = LE_CLASS_DEF_NO;

    if ( pDefTable )
    {
        const U8 *pGlyphClassTable = msAPI_MLE_LeGDEFGetClassDefinitionTable(pDefTable);
    
        eType = (LE_ClassDefinitionType_e)msAPI_MLE_LeGetGlyphClass(pGlyphClassTable, u16GlyphId);
    }

    return eType;
}

U8* msAPI_MLE_Le_CreateSubstProcess( LE_OTF_ScriptTag_e eScript, LE_LanguageTag_e eLang, U16 *pau16Str, U16 u16StrLen, U16 u16CharIndex, U16 *pau16Consumed, U16 *pau16CharFeatures )
{ 
    const U8 *pGSUB = msAPI_MLE_FONTBASE_VectorFontGetGSUBTable();
    U8 *pReturn = NULL;

    if ( pau16Str == NULL || u16StrLen == 0 || u16CharIndex >= u16StrLen || pau16CharFeatures == NULL )
    {
        return NULL;
    }

    if ( pGSUB )
    {   
        const U8 *pGDEF = msAPI_MLE_FONTBASE_VectorFontGetGDEFTable();
        
        pReturn = (U8*)msAPI_MLE_LeCreateGsubProcess(eScript, eLang, pGSUB, pGDEF);
    }
    //else
    //{
    //  const U8 *pMort = FONTBASE_VectorFontGetMortTable();
        
    //  if ( pMort )
    //  {
    //      pReturn = (U8*)LeCreateMortProcess(pMort);
    //  }
    //}

    if ( pReturn )
    {
        LE_ProcessSubstHeader_t *pHeader = (LE_ProcessSubstHeader_t *)((void *)pReturn);
        U32 *pau32AllocOut = NULL;
        U16 *pau16Sequence = NULL;
        U16 *pau16AllocComposedSize = NULL;
        U16 u16OutBufferSize = 0;
        U16 i;
        BOOLEAN bResult = FALSE;

        u16OutBufferSize = u16StrLen * 2;

        do
        {
            pHeader->u16OutBufferSize = u16OutBufferSize;
            pHeader->u16OffsetInOutput = u16CharIndex;

            pau32AllocOut = (U32 *)MALLOC(u16OutBufferSize * sizeof(U32));
            if ( pau32AllocOut == NULL )
            {
                break;
            }

            pau16Sequence = (U16 *)MALLOC(u16OutBufferSize * sizeof(U16));
            if ( pau16Sequence == NULL )
            {
                break;
            }

            pau16AllocComposedSize = (U16 *)MALLOC(u16OutBufferSize * sizeof(U16));
            if ( pau16AllocComposedSize == NULL )
            {
                break;
            }

            for ( i = 0; i < u16StrLen; i++ )
            {
                U16 u16GlyphId = 0;

                if( msAPI_MLE_FontBaseIsControlChar(pau16Str[i]) )
                {
                    u16GlyphId = (U16)(-2); //Control code
                }
                else
                {
                    u16GlyphId = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(pau16Str[i]);
                    if ( u16GlyphId == 0 )
                    {
                        u16GlyphId = (U16)(-1); //Code not exist
                    }
                }

              pau32AllocOut[i] = (U32)((((U32)pau16CharFeatures[i]) << 16) + u16GlyphId);
                pau16Sequence[i] = i;

                if ( pau16Consumed )
                {
                    pau16AllocComposedSize[i] = 1 + pau16Consumed[i];
                }
                else
                {
                        pau16AllocComposedSize[i] = 1;
                }
            }   
            pHeader->pau32OutGlyph = pau32AllocOut; 
            pHeader->pau16Sequence = pau16Sequence;
            pHeader->pau16ComposedSize = pau16AllocComposedSize;
            pHeader->u16OutLen = u16StrLen;
            pHeader->u16OffsetInConposed = 0;
        
            bResult = TRUE;
        }while(FALSE);

        if ( !bResult )
        {
            FREEIF(pHeader->pau32OutGlyph);
            FREEIF(pHeader->pau16Sequence);
            FREEIF(pHeader->pau16ComposedSize);

            if ( pHeader->eType == LE_VECTOR_TYPE_OTF )
            {
                msAPI_MLE_LeFreeGsubProcess(pReturn);
            }
            else if ( pHeader->eType == LE_VECTOR_TYPE_TTF )
            {
                //LeFreeMortProcess(pReturn);
            }
            else
            {
                FREEIF(pReturn);
            }
            pReturn = NULL;
        }
    }
    
    return pReturn;
}

void msAPI_MLE_Le_FreeSubstProcess( U8 *psProcess )
{
    LE_ProcessSubstHeader_t *pHeader = (LE_ProcessSubstHeader_t *)((void *)psProcess);

    if ( psProcess == NULL )
    {
        return;
    }
    
    FREEIF(pHeader->pau32OutGlyph);
    FREEIF(pHeader->pau16Sequence);
    FREEIF(pHeader->pau16ComposedSize);

    if ( pHeader->eType == LE_VECTOR_TYPE_OTF )
    {
        msAPI_MLE_LeFreeGsubProcess(psProcess);
    }
    else if ( pHeader->eType == LE_VECTOR_TYPE_TTF )
    {
        //LeFreeMortProcess(psProcess);
    }
    else
    {
        FREEIF(psProcess);
    }
}

U16 msAPI_MLE_Le_SubstProcessGlyphs( U8 *psProcess, LE_LanguageTag_e eLang, const LE_OTF_FeatureRecord_t *pasFeatureMap, U16 u16FeatureMapSize, U32 u32FeatureTags, U16 *pau16Glyph, U16 *pu16OffsetInOutput, U16 *pu16OffsetInComposed, U16 *pau16ComposedSize )
{
    LE_ProcessSubstHeader_t *pHeader = (LE_ProcessSubstHeader_t *)((void *)psProcess);
    U16 u16OutGlyphLen = 0;

    if ( psProcess == NULL )
    {
        return 0;
    }

    if ( pHeader->eType == LE_VECTOR_TYPE_TTF )
    {
        //LE_MortProcess_t *pMortProcess = (LE_MortProcess_t *)psProcess;
        
      //u16OutGlyphLen = LeMortProcessGlyphs(pMortProcess);
    }
    else if ( pHeader->eType == LE_VECTOR_TYPE_OTF )
    {
        LE_GSUBProcess_t *pGSUBProcess = (LE_GSUBProcess_t *)((void *)psProcess);
        
        u16OutGlyphLen = msAPI_MLE_LeGsubProcessGlyphs(pGSUBProcess, eLang, pasFeatureMap, u16FeatureMapSize, u32FeatureTags);
    }

    if ( u16OutGlyphLen == pHeader->u16OutLen )
    {    
        U16 i;
        
        for ( i = 0; i < u16OutGlyphLen; i++ )
        {
            pau16Glyph[i] = LE_GET_GLYPH_ID(pHeader->pau32OutGlyph[i]);
        }

        if ( pau16ComposedSize )
        {
            U16 *pau16TempComposedSize = pHeader->pau16ComposedSize;

            memcpy(pau16ComposedSize, pau16TempComposedSize, u16OutGlyphLen * sizeof(U16));
        }

        if ( pu16OffsetInOutput )
        {
            *pu16OffsetInOutput = pHeader->u16OffsetInOutput;
        }

        if ( pu16OffsetInComposed )
        {
            *pu16OffsetInComposed = pHeader->u16OffsetInConposed;
        }

        for ( i = pHeader->u16OutLen - 1; i > 0; i-- )
        {
            if ( pau16Glyph[i] == (U16)(-2) )
            {
                u16OutGlyphLen--;

                if ( pau16ComposedSize )
                {
                    pau16ComposedSize[i - 1] = pau16ComposedSize[i - 1] + pau16ComposedSize[i];
                }

                if ( pu16OffsetInOutput )
                {
                    if ( *pu16OffsetInOutput >= i )
                    {
                        *pu16OffsetInOutput = i - 1;
                    }
                }
            }
            else
            {
                break;
            }
        }

        if ( u16OutGlyphLen > 0 )
        {
            for ( i = 0; i < u16OutGlyphLen; i++ )
            {
                if ( pau16Glyph[i] == (U16)(-1) )
                {
                    pau16Glyph[i] = 0;
                }
            }
        }
    }
    else
    {
        u16OutGlyphLen = 0;
    }
      
    if (pau16Glyph[0] == 0x142 && pau16Glyph[1] == 0x7d && pau16Glyph[2] == 0x219 && pau16Glyph[3] == 0x14d)
    {
        pau16Glyph[3] = 0x14e;
    }
    else if (pau16Glyph[0] == 0xa8 && pau16Glyph[1] == 0x92 && pau16Glyph[2] == 0x14d)
    {
        pau16Glyph[2] = 0x14e;
    }
    else if (pau16Glyph[0] == 0xA8 && pau16Glyph[1] == 0x93 && pau16Glyph[2] == 0x210)
    {
        pau16Glyph[2] = 0x211;
    }

    return u16OutGlyphLen;
}

U8* msAPI_MLE_Le_CreatePosProcess( LE_OTF_ScriptTag_e eScript, LE_LanguageTag_e eLang, U16 *pau16Str, U16 u16StrLen, U16 u16BaseOffset, U16 u16NextOffset )
{ 
    const U8 *pGPOS = msAPI_MLE_FONTBASE_VectorFontGetGPOSTable();
    const U8 *pGDEF = msAPI_MLE_FONTBASE_VectorFontGetGDEFTable();
    LE_FontInstanceInf_t sLeFontInstanceInf = {0, 0, 0, 0, 0};
    U8 *pReturn = NULL;

    if ( pau16Str == NULL || u16StrLen == 0 || u16BaseOffset >= u16StrLen || u16NextOffset >= u16StrLen )
    {
        return NULL;
    }

    if ( u16BaseOffset > u16NextOffset )
    {
        return NULL;
    }

    sLeFontInstanceInf.u16UnitsPerEM = msAPI_MLE_FONTBASE_VectorFontGetUnitPerEM();
    sLeFontInstanceInf.u16XPixelsPerEM = msAPI_MLE_FONTBASE_GetVectorFontSize();
    sLeFontInstanceInf.u16YPixelsPerEM = msAPI_MLE_FONTBASE_GetVectorFontSize();
    sLeFontInstanceInf.s32XScaleFactor = msAPI_MLE_FONTBASE_VectorFontGetXScaleFactor();
    sLeFontInstanceInf.s32YScaleFactor = msAPI_MLE_FONTBASE_VectorFontGetYScaleFactor();
    
    pReturn = (U8*)msAPI_MLE_LeCreateGposProcess(eScript, eLang, pGPOS, pGDEF, &sLeFontInstanceInf);

    if ( pReturn )
    {
        LE_ProcessPosHeader_t *pHeader = (LE_ProcessPosHeader_t *)((void *)pReturn);
        U32 *pau32AllocIn = NULL;
        BOOLEAN bResult = FALSE;
        U16 i;

        do
        {
            pHeader->u16BaseOffset = u16BaseOffset;
            pHeader->u16NextOffset = u16NextOffset;

            pau32AllocIn = (U32 *)MALLOC(u16StrLen * sizeof(U32));
            if ( pau32AllocIn == NULL )
            {
                break;
            }
            
            for ( i = 0; i < u16StrLen; i++ )
            {
                pau32AllocIn[i] = (U32)pau16Str[i];
            }
    
            pHeader->pau32InGlyph = pau32AllocIn;   
            pHeader->u16InLen = u16StrLen;      
            bResult = TRUE;
        }while(FALSE);

        if ( !bResult )
        {
            FREEIF(pHeader->pau32InGlyph);
            msAPI_MLE_LeFreeGposProcess(pReturn);
            pReturn = NULL;
        }
    }
    
    return pReturn;
}

void msAPI_MLE_Le_FreePosProcess( U8 *psProcess )
{
    LE_ProcessPosHeader_t *pHeader = (LE_ProcessPosHeader_t *)((void *)psProcess);

    if ( psProcess == NULL )
    {
        return;
    }
    
    FREEIF(pHeader->pau32InGlyph);
    msAPI_MLE_LeFreeGposProcess(psProcess);
}

BOOLEAN msAPI_MLE_Le_PosProcessGlyphs( U8 *psProcess, LE_LanguageTag_e eLang, const LE_OTF_FeatureRecord_t *pasFeatureMap, U16 u16FeatureMapSize, U32 u32FeatureTags, U16 *pu16BaseOffset, S16 *ps16XOffset, S16 *ps16YOffset, S16 *ps16NextXOffset, S16 *ps16NextYOffset )
{
    LE_GPOSProcess_t *pGPOSProcess = (LE_GPOSProcess_t *)((void *)psProcess);
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL )
    {
        return FALSE;
    }

    bResult = msAPI_MLE_LeGposProcessGlyphs(pGPOSProcess, eLang, pasFeatureMap, u16FeatureMapSize, u32FeatureTags);

    if ( bResult )
    {
        *ps16XOffset = msAPI_MLE_LeFontXUnitToPoint(&pGPOSProcess->sFontInstanceInf, pGPOSProcess->sPosInf.s32XPlacementAdjustment);
        *ps16YOffset = msAPI_MLE_LeFontYUnitToPoint(&pGPOSProcess->sFontInstanceInf, pGPOSProcess->sPosInf.s32YPlacementAdjustment);
        *pu16BaseOffset = pGPOSProcess->sHeader.u16BaseOffset;
        *ps16NextXOffset = msAPI_MLE_LeFontXUnitToPoint(&pGPOSProcess->sFontInstanceInf, pGPOSProcess->sNextPosInf.s32XPlacementAdjustment);
        *ps16NextYOffset = msAPI_MLE_LeFontYUnitToPoint(&pGPOSProcess->sFontInstanceInf, pGPOSProcess->sNextPosInf.s32YPlacementAdjustment);
    }

    return bResult;
}

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MLE_LE_C__
