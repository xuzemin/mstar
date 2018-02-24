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


#ifndef __MSAPI_MLE_FONT_VECTOR_C__
#define __MSAPI_MLE_FONT_VECTOR_C__

#ifdef __FEATURE_VECTOR_FONT__
/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_font_base.h"
#include "msAPI_MLE_graphic_types.h"
#include "msAPI_MLE_graphic.h"

#ifdef __THAI_FONT__
#include "msAPI_MLE_font_thai.h"
#endif //__THAI_FONT__

#ifdef __INDIC_FONT__
#include "msAPI_MLE_font_hindi_priv.h"
#endif //__INDIC_FONT__


#ifdef __HEBREW_FONT__
#include "msAPI_MLE_font_hebrew.h"
#endif //__HEBREW_FONT__

#include "msAPI_MLE_font_latine.h"

#include "msAPI_MLE_helper.h"

#define _SUPPORT_FONT_CUS_

#include "msAPI_MLE_font_vector.h"

#include "msAPI_MLE_font_pl.h"
#include "msAPI_MLE_font_types.h"
#include "msAPI_MLE_font_forward.h"
#include "msAPI_COMMON_hashtable.h" // for hash table cache
#include "msAPI_COMMON_hashtable_util.h" // for hash table cache

#include "MsCommon.h"
#include "msAPI_MIU.h"
#include "apiGFX.h"

#define ENCODING_TYPE           FT_ENCODING_UNICODE
#define VERTICAL_RESOLUTION     72     // the vertical resolution in dpi
#define HORIZONTAL_RESOLUTION   72     // the horizontal resolution in dpi
#define DEFAULT_VECTOR_SIZE     20     // default 14 pixel
#define FONT_CNT                (2 + MAX_VECTOR_FONT_NUM)
#define FONT_FROM_MEMORY        0
#define FONT_FROM_FILE          1

#if ( MONO_FONT )
    #define FONT_EDGE_AUTO_CONNECT  0
#else
    #define FONT_EDGE_AUTO_CONNECT  1
#endif

//primes[] in msAPI_COMMON_hastable.c: 193, 389,769, 1543, 3079, 6151
///todo
#if 0
static U16 _g_nTTFBmpInfoCacheCount = 1543;
static U16 _g_nTTFBmpCacheCount = 389;
static U16 _g_nGlyphIdCacheCount = 769;
#ifdef __INDIC_FONT_RULE_CACHE__
static U16 _g_nHindiCacheCount = 1543;
#endif//__INDIC_FONT_RULE_CACHE__
#else
static U16 _g_nTTFBmpInfoCacheCount = 389;
static U16 _g_nTTFBmpCacheCount = 193;
static U16 _g_nGlyphIdCacheCount = 193;
#ifdef __INDIC_FONT_RULE_CACHE__
static U16 _g_nHindiCacheCount = 769;
#endif//__INDIC_FONT_RULE_CACHE__
#endif

//TTF Bitmap Info Cache
static Hashtable_t *_g_pTTFBmpInfoCacheTable = NULL;
static U8 *_g_pTTFBmpInfoCacheData = NULL;
static S32 _g_nTTFBmpInfoCacheSize = 0;
static S32 _g_nTTFBmpInfoCacheHead = 0;
static S32 _g_nTTFBmpInfoCacheTail = 0;
static S32 _g_nTTFBmpInfoCacheLast = 0;

//TTF Bitmap Cache
static BOOLEAN _g_bBmpCacheFull = FALSE;
static Hashtable_t *_g_pTTFBmpCacheTable = NULL;
static U8 *_g_pTTFBmpCacheData = NULL;
static S32 _g_nTTFBmpCacheSize = 0;
static S32 _g_nTTFBmpCacheHead = 0;
static S32 _g_nTTFBmpCacheTail = 0;
static S32 _g_nTTFBmpCacheLast = 0;

//Glyph ID Cache
static Hashtable_t *_g_pGlyphIdCacheTable = NULL;
static U8 *_g_pGlyphIdCacheData = NULL;
static S32 _g_nGlyphIdCacheSize = 0;
static S32 _g_nGlyphIdCacheHead = 0;
static S32 _g_nGlyphIdCacheTail = 0;
static S32 _g_nGlyphIdCacheLast = 0;

//Hindi Rule Cache
#ifdef __INDIC_FONT_RULE_CACHE__
static Hashtable_t *_g_pHindiCacheTable;
static U8 *_g_pHindiCacheData = NULL;
static S32 _g_nHindiCacheSize = 0;
static S32 _g_nHindiCacheHead = 0;
static S32 _g_nHindiCacheTail = 0;
static S32 _g_nHindiCacheLast = 0;
#endif //__INDIC_FONT_RULE_CACHE__

#include "ft2build.h"
#include "ftobjs.h"
#include "ftoutln.h"
#include "ttnameid.h"
#include "ftcache.h"
#include "ftotval.h"
//#include "ftgxval.h"
#include "ftgrays.h"

#define _OTF_VALIDATE_ALL (FT_VALIDATE_GDEF | FT_VALIDATE_GPOS | FT_VALIDATE_GSUB)

#define _FONT_VECTOR_UNIT_PER_EM (1 << 6)
#define _FONT_VECTOR_X_SCALE_FACTOR (72/HORIZONTAL_RESOLUTION)
#define _FONT_VECTOR_Y_SCALE_FACTOR (72/VERTICAL_RESOLUTION)

static FT_Library  context;
static FT_Fixed    ratio = 0x10000;            // default zoom ratio 1.0f in 16.16 format
static U32 g_FontSize = 0;
FT_Face g_FontFace = NULL;

static PFont curFontHandle;
static U8 *pHmemCacheBuf = NULL;
U32 HmemCacheHandle = 0;

/// structure for backward compatibility
static U16 *u16MapVectorSize = NULL;

static U8* gpCurTTFontData = NULL;
static U32 gu32CurTTFontSize = 0;

////static TTF_Card_Data_t *gpCardTTFData = NULL;

////extern CusDispLangData_t *gp_DispLangAry;

// ready for reading font from sd card
TFont FontHandleAry[FONT_CNT] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}};

U8 CreateVectorFont_FromFile_Init = 0;
U8 CreateVectorFont_FromMemory_Init = 0;

//static const U16 font_pathname[] = L"/CARD/DroidSansFallback.dat";
static const U16 *font_pathname = NULL;

//todo skip now
///static BOOLEAN bVectorFont_Exist = FALSE;
static BOOLEAN bVectorFont_Exist = TRUE;
static BOOLEAN bVectorFont_CombineBitmap = FALSE;
////static BOOLEAN g_aCatagoryForceBitmap[FONT_CAT_BITMAP_TOTAL] = {FALSE};
static BOOLEAN bTTFontFromCus = FALSE;

static BOOLEAN bOutOfMemory = FALSE;

//static U8 *m_pu8PreBuffer = NULL;

typedef union { float f;
    S32 s;
    U32 u;
} VAL32;

static S32 _msAPI_MLE_AsValues32(float fVal)
{
    VAL32 v;
    v.f = fVal;
    return v.s;
}

static FT_Fixed _msAPI_MLE_FloatTo16dot16(float f)
{
    S32 i = _msAPI_MLE_AsValues32( f + (float)(128+64) );
    i <<= 10;
    i >>= 10; // sign extend
    return (FT_Fixed) i;
}

#ifdef __BIDI_TEXT__
extern U16 msAPI_MLE_TextArabicVectorGetNextCodes(const U16 *pInTxt, U32 nInLen, U32 nOffset, U32 nSubLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed, BOOLEAN bDispStr, U16 *pLastCode );
#endif //__BIDI_TEXT__
extern BOOLEAN g_bEmappTextTest;
///extern MLE_Ret msAPI_MLE_FONTBASE_VectorFontReloadCusToMem(void);
static S32 msAPI_MLE_FONTBASE_VectorFontZoomValue(S32 nValue);
static MLE_Ret msAPI_MLE_FONTBASE_SetVectorFontSize( U32 nFontSize);
static MLE_Ret msAPI_MLE_FONTBASE_VectorFontGetKerning(U32 u32FontSize, U16 u16PreGlyphId, U16 u16CurrentGlyphId, TTF_Vector *pKVector );
static void _msAPI_MLE_FONTBASE_VectorFontSetCurTTFontData(U8 *pData, U32 u32DataSize);
///static void _msAPI_MLE_FONTBASE_VectorFontChangeFontAsyncReadCB(void *pUser, FileMgrStreamCallback_t* pInfo);

static void _msAPI_MLE_FreeCache(void)
{
    FREEIF(_g_pTTFBmpInfoCacheData);
    if(_g_pTTFBmpInfoCacheTable != NULL)
    {
        msAPI_COMMON_hashtable_destroy(_g_pTTFBmpInfoCacheTable);
        _g_pTTFBmpInfoCacheTable = NULL;            
    }

    FREEIF(_g_pTTFBmpCacheData);
    if(_g_pTTFBmpCacheTable != NULL)
    {
        msAPI_COMMON_hashtable_destroy(_g_pTTFBmpCacheTable);
        _g_pTTFBmpCacheTable = NULL;
    }

    FREEIF(_g_pGlyphIdCacheData);
    if(_g_pGlyphIdCacheTable != NULL)
    {
        msAPI_COMMON_hashtable_destroy(_g_pGlyphIdCacheTable);
        _g_pGlyphIdCacheTable = NULL;
    }

    _g_pTTFBmpInfoCacheData = NULL;
    _g_nTTFBmpInfoCacheSize = 0;
    _g_nTTFBmpInfoCacheHead = 0;
    _g_nTTFBmpInfoCacheTail = 0;
    _g_nTTFBmpInfoCacheLast = 0;

    _g_pTTFBmpCacheData = NULL;
    _g_nTTFBmpCacheSize = 0;
    _g_nTTFBmpCacheHead = 0;
    _g_nTTFBmpCacheTail = 0;
    _g_nTTFBmpCacheLast = 0;

    _g_pGlyphIdCacheData = NULL;
    _g_nGlyphIdCacheSize = 0;
    _g_nGlyphIdCacheHead = 0;
    _g_nGlyphIdCacheTail = 0;
    _g_nGlyphIdCacheLast = 0;

#if defined(__INDIC_FONT__) && defined(__INDIC_FONT_RULE_CACHE__)
    FREEIF(_g_pHindiCacheData);
    if(_g_pHindiCacheTable != NULL)
    {
        msAPI_COMMON_hashtable_destroy(_g_pHindiCacheTable);
        _g_pHindiCacheTable = NULL;
    }

    _g_pHindiCacheData = NULL;
    _g_nHindiCacheSize = 0;
    _g_nHindiCacheHead = 0;
    _g_nHindiCacheTail = 0;
    _g_nHindiCacheLast = 0;

#endif
}

MLE_Ret _msAPI_MLE_InitCache(void)
{
    if(_g_pTTFBmpInfoCacheTable == NULL)
    {
        _g_nTTFBmpInfoCacheSize = (sizeof(unsigned int)+sizeof(TTF_BmpCacheInfo))*_g_nTTFBmpInfoCacheCount;
        _g_nTTFBmpInfoCacheLast = _g_nTTFBmpInfoCacheSize;

        _g_pTTFBmpInfoCacheTable = msAPI_COMMON_hashtable_createEx(97, _g_nTTFBmpInfoCacheCount, msAPI_COMMON_hashtable_hash_int, msAPI_COMMON_hashtable_int_equals);
        if (_g_pTTFBmpInfoCacheTable == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_pTTFBmpInfoCacheTable create failed.");
            return MLE_RET_FAILED;
        }
        
        TTF_TRACE(printf("%s: %d ", __FUNCTION__, _g_nTTFBmpInfoCacheSize));
        _g_pTTFBmpInfoCacheData = (U8*)MALLOC(_g_nTTFBmpInfoCacheSize);
        if (_g_pTTFBmpInfoCacheData == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_pTTFBmpInfoCacheData MALLOC failed.");
            return MLE_RET_FAILED;
        }
    }

    if(_g_pTTFBmpCacheTable == NULL)
    {
#if 0
        BOOLEAN bIsChineseAvailable = FALSE;
        // Check Simple Chinese
        MMI_Common_VerifyLanguageCode(MLE_LANG_CHINESE_S, &bIsChineseAvailable, (IBase *) SH_CurrentContext());
        if(bIsChineseAvailable == FALSE)
        {
            MMI_Common_VerifyLanguageCode(MLE_LANG_CHINESE_T, &bIsChineseAvailable, (IBase *) SH_CurrentContext());
        }

        if(bIsChineseAvailable == TRUE)
        {
            _g_nTTFBmpCacheSize = 200*_g_nTTFBmpCacheCount;
        }
        else
        {
            _g_nTTFBmpCacheSize = 100*_g_nTTFBmpCacheCount;
        }
#else
        _g_nTTFBmpCacheSize = 100*_g_nTTFBmpCacheCount;
#endif
        
        _g_nTTFBmpCacheLast = _g_nTTFBmpCacheSize;
        _g_pTTFBmpCacheTable = msAPI_COMMON_hashtable_createEx(97, _g_nTTFBmpCacheCount, msAPI_COMMON_hashtable_hash_int, msAPI_COMMON_hashtable_int_equals);
        if (_g_pTTFBmpCacheTable == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_TTFBmpCacheTable create failed.");
            return MLE_RET_FAILED;
        }
        TTF_TRACE(printf("%s: %d ", __FUNCTION__, _g_nTTFBmpCacheSize));
        _g_pTTFBmpCacheData = (U8*)MALLOC(_g_nTTFBmpCacheSize);
        if (_g_pTTFBmpCacheData == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_TTFBmpCacheData MALLOC failed.");
            return MLE_RET_FAILED;
        }
    }

    if(_g_pGlyphIdCacheTable == NULL)
    {
        _g_nGlyphIdCacheSize =  (sizeof(unsigned int)+sizeof(U32))*_g_nGlyphIdCacheCount;
        _g_nGlyphIdCacheLast = _g_nGlyphIdCacheSize;

        _g_pGlyphIdCacheTable = msAPI_COMMON_hashtable_createEx(97, _g_nGlyphIdCacheCount, msAPI_COMMON_hashtable_hash_int, msAPI_COMMON_hashtable_int_equals);
        if (_g_pGlyphIdCacheTable == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_GlyphIdCacheTable create failed.");
            return MLE_RET_FAILED;
        }
        TTF_TRACE(printf("%s: %d ", __FUNCTION__, _g_nGlyphIdCacheSize));
        _g_pGlyphIdCacheData = (U8*)MALLOC(_g_nGlyphIdCacheSize);
        if (_g_pGlyphIdCacheData == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_GlyphIdCacheData MALLOC failed.");
            return MLE_RET_FAILED;
        }
    }

#if defined(__INDIC_FONT__) && defined(__INDIC_FONT_RULE_CACHE__)
    if(_g_pHindiCacheTable == NULL)
    {
        _g_nHindiCacheSize =  22*_g_nHindiCacheCount;
        _g_nHindiCacheLast = _g_nHindiCacheSize;

        _g_pHindiCacheTable = msAPI_COMMON_hashtable_createEx(_g_nHindiCacheCount, _g_nHindiCacheCount,  msAPI_COMMON_hashtable_hash_int, msAPI_COMMON_hashtable_int_equals);
        if (_g_pHindiCacheTable == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_pHindiCacheTable create failed");
            return MLE_RET_FAILED;
        }
        TTF_TRACE(printf("%s: %d ", __FUNCTION__, _g_nHindiCacheSize));
        _g_pHindiCacheData = (U8*)MALLOC(_g_nHindiCacheSize);
        if (_g_pHindiCacheData == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_g_pHindiCacheData MALLOC failed");
            return MLE_RET_FAILED;
        }
    }
#endif

    return MLE_RET_SUCCESS;
}
static MLE_Ret _msAPI_MLE_InitStaticBuffer(U32 u32BufferSize)
{
    if (pHmemCacheBuf == NULL && bVectorFont_Exist)
    {
        TTF_TRACE(printf("%s: %d ", __FUNCTION__, sizeof(U8)* u32BufferSize));
        pHmemCacheBuf = MALLOC(sizeof(U8)* u32BufferSize);
        if(pHmemCacheBuf == NULL)
        {
            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_Init_StaticBuffer(), allocate memory failed.");
            return MLE_RET_FAILED;
        }
        MEMSET(pHmemCacheBuf, 0, sizeof(U8)* u32BufferSize);
    }
    
    if (0 == HmemCacheHandle)
    {
//todo skip now             
///        HmemCacheHandle = MsHMEMCreate(pHmemCacheBuf, u32BufferSize);
///        if (0 == HmemCacheHandle)
///        {
///            ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "handle create failed.");
///            return MLE_RET_FAILED;
///        }
//todo skip now             
///        FT_SetMemCacheHandle(HmemCacheHandle);
    }

    return _msAPI_MLE_InitCache();
}

static unsigned int _msAPI_MLE_GetTTFBmpHashKey(U32 u32FontSize, U32 u32GlyphId)
{
    return u32GlyphId+u32FontSize*161527;
}

static void _msAPI_MLE_InsertGlyphIdCache(unsigned int nHashKey, U32 u32GlyphId)
{
    BOOLEAN bNeedRelease = FALSE;
    S32 s32TotalSize = 0;
    U16 u16DataSize = 0;
    U32* pCacheData = NULL;

    u16DataSize = sizeof(U32);
    s32TotalSize = u16DataSize + sizeof(nHashKey);
    // remove oldest data
    do 
    {
        bNeedRelease = FALSE;

        // check if exist enough cache memory
        if(_g_nGlyphIdCacheHead > _g_nGlyphIdCacheTail)
        {
            if(_g_nGlyphIdCacheHead+s32TotalSize > _g_nGlyphIdCacheSize)
            {
                bNeedRelease = TRUE;
                _g_nGlyphIdCacheLast = _g_nGlyphIdCacheHead;
                _g_nGlyphIdCacheHead = 0;
            }
        }
        else if (_g_nGlyphIdCacheHead == _g_nGlyphIdCacheTail)
        {
            if(msAPI_COMMON_hashtable_size(_g_pGlyphIdCacheTable) > 0)
                bNeedRelease = TRUE;
        }
        else // _g_nGlyphIdCacheHead < _g_nGlyphIdCacheTail
        {
            if(_g_nGlyphIdCacheTail - _g_nGlyphIdCacheHead < s32TotalSize)
                bNeedRelease = TRUE;
        }

        // release the oldest font in cache
        if(bNeedRelease)
        {
            unsigned int nTmpHashKey = 0;
            MEMCPY(&nTmpHashKey, (_g_pGlyphIdCacheData+_g_nGlyphIdCacheTail), sizeof(nTmpHashKey));
            msAPI_COMMON_hashtable_remove(_g_pGlyphIdCacheTable, (void*)nTmpHashKey);
            //_g_nCountCglyphId--;
            _g_nGlyphIdCacheTail += sizeof(nTmpHashKey)+ u16DataSize;
            if(_g_nGlyphIdCacheTail >= _g_nGlyphIdCacheLast)
                _g_nGlyphIdCacheTail = 0;
        }
    } while (bNeedRelease);

    //set nHashKey at head
    MEMCPY(_g_pGlyphIdCacheData+_g_nGlyphIdCacheHead, &nHashKey, sizeof(nHashKey));
    _g_nGlyphIdCacheHead += sizeof(nHashKey);

    pCacheData = (U32*)((void *)(_g_pGlyphIdCacheData+_g_nGlyphIdCacheHead));
    if ( msAPI_COMMON_hashtable_insert(_g_pGlyphIdCacheTable, (void*)nHashKey, (void*)(pCacheData)) == 0 )
    {
        _g_nGlyphIdCacheHead -= sizeof(nHashKey);
        return;
    }

    //_g_nCountCglyphId++;

    //set Data at head
    MEMCPY(pCacheData, &u32GlyphId, u16DataSize);
    _g_nGlyphIdCacheHead += u16DataSize;

}

static void _msAPI_MLE_InsertTTFBmpInfoCache(unsigned int nHashKey, TTF_BmpCacheInfo* pTTFBmpCacheInf)
{
    BOOLEAN bNeedRelease = FALSE;
    U16 u16DataSize = 0;
    S32 s32TotalSize = 0;
    TTF_BmpCacheInfo* pCacheData = NULL;
    if(pTTFBmpCacheInf == NULL)
    {
        return;
    }

    u16DataSize = sizeof(TTF_BmpCacheInfo);
    s32TotalSize = u16DataSize+sizeof(nHashKey);
    // remove oldest data
    do 
    {
        bNeedRelease = FALSE;

        // check if exist enough cache memory
        if(_g_nTTFBmpInfoCacheHead > _g_nTTFBmpInfoCacheTail)
        {
            if(_g_nTTFBmpInfoCacheHead+s32TotalSize > _g_nTTFBmpInfoCacheSize)
            {
                bNeedRelease = TRUE;
                _g_nTTFBmpInfoCacheLast = _g_nTTFBmpInfoCacheHead;
                _g_nTTFBmpInfoCacheHead = 0;
            }
        }
        else if (_g_nTTFBmpInfoCacheHead == _g_nTTFBmpInfoCacheTail)
        {
            if(msAPI_COMMON_hashtable_size(_g_pTTFBmpInfoCacheTable) > 0)
                bNeedRelease = TRUE;
        }
        else // _g_nTTFBmpInfoCacheHead < _g_nTTFBmpInfoCacheTail
        {
            if(_g_nTTFBmpInfoCacheTail - _g_nTTFBmpInfoCacheHead < s32TotalSize)
                bNeedRelease = TRUE;
        }

        // release the oldest font in cache
        if(bNeedRelease)
        {
            unsigned int nTmpHashKey = 0;
            MEMCPY(&nTmpHashKey, (_g_pTTFBmpInfoCacheData+_g_nTTFBmpInfoCacheTail), sizeof(nTmpHashKey));
            msAPI_COMMON_hashtable_remove(_g_pTTFBmpInfoCacheTable, (void*)nTmpHashKey);
            //_g_nCountBmpInfo--;
            _g_nTTFBmpInfoCacheTail += sizeof(nTmpHashKey)+ u16DataSize;
            if(_g_nTTFBmpInfoCacheTail >= _g_nTTFBmpInfoCacheLast)
                _g_nTTFBmpInfoCacheTail = 0;
        }
    } while (bNeedRelease);

    //set nHashKey at head
    MEMCPY(_g_pTTFBmpInfoCacheData+_g_nTTFBmpInfoCacheHead, &nHashKey, sizeof(nHashKey));
    _g_nTTFBmpInfoCacheHead += sizeof(nHashKey);

    pCacheData = (TTF_BmpCacheInfo*)((void *)(_g_pTTFBmpInfoCacheData+_g_nTTFBmpInfoCacheHead)) ;
    if ( msAPI_COMMON_hashtable_insert(_g_pTTFBmpInfoCacheTable, (void*)nHashKey, (void*)(pCacheData)) == 0 )
    {
        _g_nTTFBmpInfoCacheHead -= sizeof(nHashKey);
        return;
    }
    //_g_nCountBmpInfo++;

    //set Data at head
    MEMCPY(pCacheData, pTTFBmpCacheInf, u16DataSize);
    _g_nTTFBmpInfoCacheHead += u16DataSize;

}

static void _msAPI_MLE_InsertTTFBmpCache(unsigned int nHashKey, S16 rows, S16 pitch, U8* pTTFBmp)
{
    BOOLEAN bNeedRelease = FALSE;
    U16 u16BitmapSize = 0;
    U16 u16DataSize = 0;
    S32 s32TotalSize = 0;

    if(pTTFBmp == NULL || rows == 0 || pitch == 0)
    {
        return;
    }

    u16BitmapSize = rows*pitch;
    u16DataSize = sizeof(rows)+ sizeof(pitch)+ u16BitmapSize;
    s32TotalSize = u16DataSize+sizeof(nHashKey)+sizeof(u16DataSize);

    // remove oldest data
    do 
    {
        bNeedRelease = FALSE;

        // check if exist enough cache memory
        if(_g_nTTFBmpCacheHead > _g_nTTFBmpCacheTail)
        {
            if(_g_nTTFBmpCacheHead+s32TotalSize > _g_nTTFBmpCacheSize)
            {
                bNeedRelease = TRUE;
                _g_nTTFBmpCacheLast = _g_nTTFBmpCacheHead;
                _g_nTTFBmpCacheHead = 0;
            }
        }
        else if (_g_nTTFBmpCacheHead == _g_nTTFBmpCacheTail)
        {
            if(msAPI_COMMON_hashtable_size(_g_pTTFBmpCacheTable) > 0)
                bNeedRelease = TRUE;
        }
        else // _g_TTFBmpCacheHead < _g_TTFBmpCacheTail
        {
            if( (_g_nTTFBmpCacheTail - _g_nTTFBmpCacheHead < s32TotalSize))
                bNeedRelease = TRUE;
        }

        // release the oldest font in cache
        if(bNeedRelease)
        {
            unsigned int nTmpHashKey = 0;
            U16 u16tmpDataSize = 0;

            _g_bBmpCacheFull = TRUE;
            MEMCPY(&nTmpHashKey, (_g_pTTFBmpCacheData+_g_nTTFBmpCacheTail), sizeof(nTmpHashKey));
            MEMCPY(&u16tmpDataSize, (_g_pTTFBmpCacheData+_g_nTTFBmpCacheTail+sizeof(nTmpHashKey)), sizeof(u16tmpDataSize));
            msAPI_COMMON_hashtable_remove(_g_pTTFBmpCacheTable, (void*)nTmpHashKey);
            //_g_nCountBmp--;
            _g_nTTFBmpCacheTail += sizeof(nTmpHashKey)+ sizeof(u16tmpDataSize)+ u16tmpDataSize;
            if(_g_nTTFBmpCacheTail >= _g_nTTFBmpCacheLast)
                _g_nTTFBmpCacheTail = 0;
        }
    } while (bNeedRelease);

    //set nHashKey at head
    MEMCPY(_g_pTTFBmpCacheData+_g_nTTFBmpCacheHead, &nHashKey, sizeof(nHashKey));
    _g_nTTFBmpCacheHead += sizeof(nHashKey);

    //set u16DataSize at head
    MEMCPY(_g_pTTFBmpCacheData+_g_nTTFBmpCacheHead, &u16DataSize, sizeof(u16DataSize));
    _g_nTTFBmpCacheHead += sizeof(u16DataSize);

    if ( msAPI_COMMON_hashtable_insert(_g_pTTFBmpCacheTable, (void*)nHashKey, (void*)(_g_pTTFBmpCacheData+_g_nTTFBmpCacheHead)) == 0 )
    {
        _g_nTTFBmpCacheHead -= sizeof(u16DataSize);
        _g_nTTFBmpCacheHead -= sizeof(nHashKey);
        return;
    }
    //_g_nCountBmp++;

    // set rows
    MEMCPY(_g_pTTFBmpCacheData+_g_nTTFBmpCacheHead, &rows, sizeof(S16));
    _g_nTTFBmpCacheHead += sizeof(S16);

    // set pitch
    MEMCPY(_g_pTTFBmpCacheData+_g_nTTFBmpCacheHead, &pitch, sizeof(S16));
    _g_nTTFBmpCacheHead += sizeof(S16);
   
    //set Data
    MEMCPY(_g_pTTFBmpCacheData+_g_nTTFBmpCacheHead, pTTFBmp, u16BitmapSize);

    _g_nTTFBmpCacheHead += u16BitmapSize;
}

static void _msAPI_MLE_DoOutLine(U8* DstBuf, U16 DstWidth, U16 DstPitch, U16 DstHeight,
                       U8* SrcBuf, U16 SrcWidth, U16 SrcPitch, U16 SrcHeight)
{
    U8 *EndYAdr = SrcBuf + (SrcHeight*SrcPitch);
    U8 *CurAdr, *EndXAdr;
    U8 *DstUpAdr, *DstDownAdr, *DstLeftAdr, *DstRightAdr;
    U16 Tmp;

    DstWidth = DstWidth;
    DstHeight = DstHeight;
    
    while (SrcBuf != EndYAdr)
    {
        DstUpAdr = DstBuf+1;
        DstDownAdr = DstBuf+(DstPitch<<1)+1;
        DstLeftAdr = DstBuf+DstPitch;
        DstRightAdr = DstBuf+DstPitch+2;
        CurAdr = SrcBuf;
        EndXAdr = CurAdr + SrcWidth;
        while (CurAdr != EndXAdr)
        {
            if (*CurAdr > 0)
            {
                Tmp = (U16)*CurAdr + (U16)*DstUpAdr;
                *DstUpAdr = (Tmp > 0xFF)?0xFF:(U8)Tmp;
                Tmp = (U16)*CurAdr + (U16)*DstDownAdr;
                *DstDownAdr = (Tmp > 0xFF)?0xFF:(U8)Tmp;
                Tmp = (U16)*CurAdr + (U16)*DstLeftAdr;
                *DstLeftAdr = (Tmp > 0xFF)?0xFF:(U8)Tmp;
                Tmp = (U16)*CurAdr + (U16)*DstRightAdr;
                *DstRightAdr = (Tmp > 0xFF)?0xFF:(U8)Tmp;
            }
            CurAdr++;
            DstUpAdr++;
            DstDownAdr++;
            DstLeftAdr++;
            DstRightAdr++;
        }
        SrcBuf += SrcPitch;
        DstBuf += DstPitch;
    }
}

static BOOLEAN _msAPI_MLE_CheckChar(FT_Char d)
{
    FT_Int temp = 0;
    temp = d; 
    return temp == d;
}

static BOOLEAN _msAPI_MLE_CheckByte(FT_Byte d)
{
    FT_Int temp = 0;
    temp = d;
    return temp == d;
}

extern void ft_glyphslot_clear( FT_GlyphSlot  slot );

static MLE_Ret _msAPI_MLE_LoadTTFBmpAllocate(U32 u32FontSize, U32 u32GlyphId, TTF_Bitmap **ppTTFBitmap, S32 s32XOffset, S32 s32YOffset, U32 u32OLPixels, BOOLEAN bIsNeedBmp)
{
    MLE_Ret eResult = MLE_RET_SUCCESS;

    U32 nOLFontPixels = u32OLPixels * 2;

    unsigned int nHashKey = 0;
    TTF_BmpCacheInfo *pCacheInfo = NULL;
    U8* pCacheBmp = NULL;
    BOOLEAN bIsFoundInfo = FALSE;
    BOOLEAN bIsFoundBmp = FALSE;

    TTF_TRACE(printf("%d sizeof(TTF_Bitmap)=%d\n", __LINE__, sizeof(TTF_Bitmap)));
    TTF_Bitmap *pTTFBmp = (TTF_Bitmap*)MALLOC(sizeof(TTF_Bitmap));
    if(pTTFBmp == NULL)
    {
        //return MLE_RET_FAILED;
        return MLE_RET_OUT_OF_MEMORY;
    }
    MEMSET(pTTFBmp, 0, sizeof(TTF_Bitmap));

    ///MsConsumeSem(MMI_SEM1);

    do 
    {
        nHashKey = _msAPI_MLE_GetTTFBmpHashKey(u32FontSize, u32GlyphId);
        pCacheInfo = (TTF_BmpCacheInfo*)msAPI_COMMON_hashtable_search(_g_pTTFBmpInfoCacheTable, (void*)nHashKey);
        if(pCacheInfo != NULL)
        {
            bIsFoundInfo = TRUE;
        }

        if(bIsNeedBmp == TRUE)
        {
            pCacheBmp = (U8*)msAPI_COMMON_hashtable_search(_g_pTTFBmpCacheTable, (void*)nHashKey);
            if(pCacheBmp != NULL)
            {
                bIsFoundBmp= TRUE;

                if(bIsNeedBmp == TRUE)
                {
                    MEMCPY((void*)&pTTFBmp->rows, (void*)pCacheBmp, sizeof(S16));
                    pCacheBmp += sizeof(S16);
                    MEMCPY((void*)&pTTFBmp->pitch, (void*)pCacheBmp, sizeof(S16));
                    pCacheBmp += sizeof(S16);

                    if(pTTFBmp->rows > ((S32)u32FontSize)*8 || pTTFBmp->pitch > ((S32)u32FontSize)*8)
                    {
                        ///LOG_ERROR(MLE_LEVEL_GRAPHIC, "_msAPI_MLE_LoadTTFBmpAllocate TTFBmpCache get rows and pitch error so break, FontSize = %d, GlyphId = %d, HashKey = %d, rows = %d, pitch = %d", 
                                ///u32FontSize, u32GlyphId, nHashKey, pTTFBmp->rows, pTTFBmp->pitch);

                        eResult = MLE_RET_FAILED;
                        break;
                    }
                }
            }
        }
        
        if(bIsFoundInfo == FALSE || (bIsNeedBmp == TRUE && bIsFoundBmp == FALSE))
        {
            TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
            eResult = msAPI_MLE_FONTBASE_SetVectorFontSize(u32FontSize);
            if(eResult != MLE_RET_SUCCESS)
            {
                break;
            }

#if ( MONO_FONT )
            if(FT_Load_Glyph(g_FontFace, u32GlyphId, FT_LOAD_DEFAULT | FT_LOAD_RENDER | FT_LOAD_MONOCHROME) != 0)
#else
            if(FT_Load_Glyph(g_FontFace, u32GlyphId, FT_LOAD_DEFAULT | FT_LOAD_RENDER) != 0)
#endif
            {
                eResult = MLE_RET_FAILED;
                break;
            }

            // check glyph
            {
                FT_Pos xadvance = 0;
                FT_Pos yadvance = 0;
                FT_GlyphSlot slot = g_FontFace->glyph;
                FT_Bitmap* bitmap = NULL;
                
                if (slot->format != FT_GLYPH_FORMAT_BITMAP )
                {
                    eResult = MLE_RET_FAILED;
                    break;
                }

                bitmap = &slot->bitmap;

                if(bitmap->rows > ((S32)u32FontSize)*8 || bitmap->pitch > ((S32)u32FontSize)*8)
                {
                    ///LOG_ERROR(MLE_LEVEL_GRAPHIC, "Free Type Engine get rows and pitch error so break, FontSize = %d, GlyphId = %d, rows = %d, pitch = %d", 
                            ///u32FontSize, u32GlyphId, bitmap->rows, bitmap->pitch);

                    eResult = MLE_RET_FAILED;
                    break;
                }
                
                /* horizontal advance in pixels */
                xadvance = ( slot->advance.x + 32 ) >> 6;
                yadvance = ( slot->advance.y + 32 ) >> 6;
                
                if ( _msAPI_MLE_CheckByte( (FT_Byte)bitmap->rows  ) == FALSE     ||
                    _msAPI_MLE_CheckByte( (FT_Byte)bitmap->width ) == FALSE    ||
                    _msAPI_MLE_CheckChar( (FT_Char)bitmap->pitch ) == FALSE    ||
                    _msAPI_MLE_CheckChar( (FT_Char)slot->bitmap_left ) == FALSE    ||
                    _msAPI_MLE_CheckChar( (FT_Char)slot->bitmap_top  ) == FALSE    ||
                    _msAPI_MLE_CheckChar( (FT_Char)xadvance ) == FALSE    ||
                    _msAPI_MLE_CheckChar( (FT_Char)yadvance ) == FALSE    )
                {
                    eResult = MLE_RET_FAILED;
                    break;
                }

                if(bIsFoundInfo == FALSE)
                {
                    TTF_BmpCacheInfo sBitCacheInf = {0, 0, 0, 0, 0};
                    sBitCacheInf.width     = (S8)bitmap->width;
                    sBitCacheInf.left      = (S8)slot->bitmap_left;
                    sBitCacheInf.top       = (S8)slot->bitmap_top;
                    sBitCacheInf.xadvance  = (S8)xadvance;
                    sBitCacheInf.yadvance  = (S8)yadvance;
                    pCacheInfo = &sBitCacheInf;
                    _msAPI_MLE_InsertTTFBmpInfoCache(nHashKey, pCacheInfo); //cache
                }

                // insert to bitmap cache
                if((bIsNeedBmp == TRUE && bIsFoundBmp == FALSE) || _g_bBmpCacheFull == FALSE)
                {
                    pTTFBmp->rows = bitmap->rows;
                    pTTFBmp->pitch = bitmap->pitch;

                    if ( pTTFBmp->pitch < 0 )
                    {
                        pTTFBmp->pitch = -pTTFBmp->pitch;
                    }
//For I-1 mono color, pitch should not *8
#if 0
                    if ( bitmap->pixel_mode == 1 )
                    {
                        pTTFBmp->pitch = pTTFBmp->pitch * 8;
                    }
#endif
                    pCacheBmp = bitmap->buffer;
                    _msAPI_MLE_InsertTTFBmpCache(nHashKey, pTTFBmp->rows, pTTFBmp->pitch, pCacheBmp); //cache
                }
            }
        }

        // TTF Bitmap Info
        pTTFBmp->gidx = u32GlyphId;
        pTTFBmp->y = s32YOffset + pCacheInfo->top;
        pTTFBmp->x = s32XOffset + pCacheInfo->left;
        pTTFBmp->width = pCacheInfo->width;
        pTTFBmp->xadvance = pCacheInfo->xadvance;
        pTTFBmp->yadvance = pCacheInfo->yadvance;
        pTTFBmp->iOutLineWidth = u32OLPixels;
        if ( pTTFBmp->iOutLineWidth )
        {
            pTTFBmp->iwidth = pTTFBmp->width + nOLFontPixels;
        }

        pTTFBmp->s32PreGap = 0;
        pTTFBmp->s32PosGap = 0;

        if(pTTFBmp->xadvance > 0 )
        {
            if ( pCacheInfo->left >= 0 )
            {
                pTTFBmp->s32PreGap = pCacheInfo->left;
                if ( (pTTFBmp->xadvance - pCacheInfo->left) > pTTFBmp->width )
                {
                    pTTFBmp->s32PosGap = (pTTFBmp->xadvance - pCacheInfo->left) - pTTFBmp->width;
                }
            }
        }

        if ( pTTFBmp->xadvance > 0 && pCacheInfo->left < 0 )
        {
            pTTFBmp->s32ZeroWidth = pCacheInfo->left;
        }
        else
        {
            pTTFBmp->s32ZeroWidth = 0;
        }

        if(bIsNeedBmp == TRUE) 
        {
            //buffer
            if(pCacheBmp != NULL)
            {
                U16 u16BitmapSize = pTTFBmp->rows * pTTFBmp->pitch;
                pTTFBmp->buffer = (U8*)MALLOC(u16BitmapSize * sizeof(U8));
                if(pTTFBmp->buffer != NULL)
                {
                    //if ( pTTFBmp->buffer == m_pu8PreBuffer )
                    //{
                        //In this case, OSD bitmaps are decompressed dynamicly. 
                        //If we don't flush GE at this point, while GE is doing bitblt, its source buffer maybe overwritten by next turn OSD bitmaps decompression.
                        //We move this operation to here, after font buffer is allocated, to decrease flush times to increase performance
                        //It still not safe to put here
                        //MApi_GFX_FlushQueue();
                    //}
                    
                    MEMCPY(pTTFBmp->buffer, pCacheBmp, u16BitmapSize);
                }
                else
                {
                    //eResult = MLE_RET_FAILED;
                    eResult = MLE_RET_OUT_OF_MEMORY;
                    break;
                }

                //outline buffer
                if (pTTFBmp->iOutLineWidth)
                {
                    pTTFBmp->irows = pTTFBmp->rows + nOLFontPixels;
                    pTTFBmp->ipitch = (pTTFBmp->iwidth + 3) & ~3;

                    u16BitmapSize = pTTFBmp->irows*pTTFBmp->ipitch;
                    pTTFBmp->ibuffer = (U8*)MALLOC(u16BitmapSize);
                    if ( pTTFBmp->ibuffer )
                    {
                        MEMSET(pTTFBmp->ibuffer, 0, u16BitmapSize);
                        _msAPI_MLE_DoOutLine(pTTFBmp->ibuffer, pTTFBmp->iwidth, pTTFBmp->ipitch, pTTFBmp->irows,
                            pTTFBmp->buffer, pTTFBmp->width, pTTFBmp->pitch, pTTFBmp->rows);
                    }
                    else
                    {
                        //eResult = MLE_RET_FAILED;
                        eResult = MLE_RET_OUT_OF_MEMORY;
                        break;
                    }
                }
            }
        }//if(bIsNeedBmp == TRUE) 

        //To prevent memory fragmentation, free here
        ft_glyphslot_clear( g_FontFace->glyph );
    } while (FALSE);
    
    ///MsProduceSem(MMI_SEM1);

    if(eResult == MLE_RET_SUCCESS)
    {
        //Customer request, set not exist char to void, just like bitmap font behavior
        if ( u32GlyphId == 0 )
        {
            pTTFBmp->rows = 0;
            pTTFBmp->width = 0;
            pTTFBmp->xadvance = 0;
            pTTFBmp->yadvance = 0;
        }

        *ppTTFBitmap = pTTFBmp;
    }
    else
    {
        msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pTTFBmp);
    }

    return eResult;
}

static MLE_Ret msAPI_MLE_FONTBASE_VectorFontTFBitmapAllocate(U32 u32FontSize, U32 u32GlyphId, TTF_Bitmap **ppTFBitmap, S32 s32XOffset, S32 s32YOffset, U32 u32OLPixels )
{
    MLE_Ret eResult = MLE_RET_SUCCESS;

    if ( *ppTFBitmap != NULL )
    {
        msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(*ppTFBitmap);
        *ppTFBitmap = NULL;
    }
    
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    eResult = _msAPI_MLE_LoadTTFBmpAllocate(u32FontSize, u32GlyphId, ppTFBitmap, s32XOffset, s32YOffset, u32OLPixels, TRUE);

    if ( eResult != MLE_RET_SUCCESS )
    {
        msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(*ppTFBitmap);
        *ppTFBitmap = NULL;
        
        if ( eResult == MLE_RET_OUT_OF_MEMORY )
        {
            msAPI_MLE_SetMemoryNotEnoughFlag(TRUE);
        }
    }

    return eResult;
}

MLE_Ret msAPI_MLE_FONTBASE_VectorFontGetTFGlyphInfAllocate(U32 u32GlyphId, TTF_Bitmap **pTTFBitmap)
{
    MLE_Ret eResult = _msAPI_MLE_LoadTTFBmpAllocate(g_FontSize, u32GlyphId, pTTFBitmap, 0, 0, 0, FALSE);
    
    if ( eResult == MLE_RET_OUT_OF_MEMORY )
    {
        msAPI_MLE_SetMemoryNotEnoughFlag(TRUE);
    }
    
    return eResult;
}


/******************************/
/*     GLOBAL FUNCTIONS       */
/******************************/

void msAPI_MLE_SetMemoryNotEnoughFlag(BOOLEAN bFlag)
{
    bOutOfMemory = bFlag;
}

BOOLEAN msAPI_MLE_GetMemoryNotEnoughFlag(void)
{
    return bOutOfMemory;
}

void msAPI_MLE_FONTBASE_VectorFontSetExist(void)
{   
#if 0
    U16 u16ArraySize = 0;
    msAPI_MLE_GetFontDataArray(FONT_CAT_VECTOR, NULL, NULL, &u16ArraySize , 1);
    if ( u16ArraySize > 0 )
    {
        bVectorFont_Exist = TRUE;
    }
#else
    bVectorFont_Exist = TRUE;
#endif
}

BOOLEAN msAPI_MLE_FONTBASE_IsVectorFontCombineBitmap(void)  
{
    if(bVectorFont_CombineBitmap)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void _msAPI_MLE_FONTBASE_VectorFontInitEx(U32 u32BufferSize)
{
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__)); 
    if ( bVectorFont_Exist )
    { 
        U32 _minBufferSize = msAPI_MLE_FONT_PL_GetFTBufferMinSize();
        U32 _defaultBufferSize = msAPI_MLE_FONT_PL_GetFTBufferSize();
        
        TTF_TRACE(printf("%d %s %s u32BufferSize=%d\n", __LINE__, __FUNCTION__, __FILE__, u32BufferSize));
        if(_minBufferSize >= u32BufferSize)
        {
            u32BufferSize = _minBufferSize;
        }
        else if(u32BufferSize >= _defaultBufferSize)
        {
            u32BufferSize = msAPI_MLE_FONT_PL_GetFTBufferSize();
        }

        if(_msAPI_MLE_InitStaticBuffer(u32BufferSize) != MLE_RET_SUCCESS)
        {
            TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
            return;
        }
    
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));

        FT_Init_FreeType(&context);
    }
}

#if 0
void msAPI_MLE_FONTBASE_VectorFontInit( void )
{
    ///MsConsumeSem(MMI_SEM1);
    _msAPI_MLE_FONTBASE_VectorFontInitEx(msAPI_MLE_FONT_PL_GetFTBufferSize());
    msAPI_MLE_FONTBASE_CreateVectorFont_FromCus();
    msAPI_MLE_FONTBASE_SetVectorFontSize(DEFAULT_VECTOR_SIZE);
    bTTFontFromCus = TRUE;
    ///MsProduceSem(MMI_SEM1);
}
#endif

void msAPI_MLE_FONTBASE_VectorFontReInit(U32 u32BufferSize)
{
    ///MsConsumeSem(MMI_SEM1);
    msAPI_MLE_FONTBASE_VectorFontUnInit();
    _msAPI_MLE_FONTBASE_VectorFontInitEx(u32BufferSize);
    msAPI_MLE_FONTBASE_CreateVectorFont_FromMemory(gpCurTTFontData, gu32CurTTFontSize);
    msAPI_MLE_FONTBASE_SetVectorFontSize(DEFAULT_VECTOR_SIZE);
    ///MsProduceSem(MMI_SEM1); 
}

#ifdef __INDIC_FONT_RULE_CACHE__
MLE_Ret msAPI_MLE_FONTBASE_VectorFontReSetCache(U16 u16BmpInfoCacheSize, U16 u16BmpCacheSize, U16 u16GlyphIdCacheSize, U16 u16HindiCacheSize)
#else
MLE_Ret msAPI_MLE_FONTBASE_VectorFontReSetCache(U16 u16BmpInfoCacheSize, U16 u16BmpCacheSize, U16 u16GlyphIdCacheSize)
#endif//__INDIC_FONT_RULE_CACHE__
{
    MLE_Ret nRet = MLE_RET_FAILED;

    if(u16BmpInfoCacheSize <= 0 || u16BmpCacheSize <= 0 
        || u16GlyphIdCacheSize <= 0)
    {
        return nRet;
    }
#ifdef __INDIC_FONT_RULE_CACHE__
    if(u16HindiCacheSize <= 0)
        return nRet;
#endif//__INDIC_FONT_RULE_CACHE__

    ///MsConsumeSem(MMI_SEM1);
    _msAPI_MLE_FreeCache();
    _g_nTTFBmpInfoCacheCount = u16BmpInfoCacheSize;
    _g_nTTFBmpCacheCount = u16BmpCacheSize;
    _g_nGlyphIdCacheCount = u16GlyphIdCacheSize;
#ifdef __INDIC_FONT_RULE_CACHE__
    _g_nHindiCacheCount = u16HindiCacheSize;
#endif//__INDIC_FONT_RULE_CACHE__

    nRet = _msAPI_MLE_InitCache();

    ///MsProduceSem(MMI_SEM1);

    return nRet;
}

void msAPI_MLE_FONTBASE_VectorFontUnInit( void )
{
    if( bVectorFont_Exist )
    {
        if(g_FontFace != NULL)
        {
            FT_OpenType_Free(g_FontFace, FontHandleAry[FONT_FROM_MEMORY].pGDEF);
            FT_OpenType_Free(g_FontFace, FontHandleAry[FONT_FROM_MEMORY].pGPOS);
            FT_OpenType_Free(g_FontFace, FontHandleAry[FONT_FROM_MEMORY].pGSUB);
            //FT_TrueTypeGX_Free(newFace, FontHandleAry[FONT_FROM_MEMORY].pKern);
            //FT_TrueTypeGX_Free(newFace, FontHandleAry[FONT_FROM_MEMORY].pMort);

            FT_Done_Face(g_FontFace);
            g_FontFace = NULL;
        }

        MEMSET(FontHandleAry, 0, sizeof(FontHandleAry));
        
        FT_Done_FreeType(context);
//todo skip now     
        ///MsHMEMClose(HmemCacheHandle);
//todo skip now     
///        FT_SetMemCacheHandle(0);
        FREE(pHmemCacheBuf);
        pHmemCacheBuf = NULL;
        HmemCacheHandle = 0;
        context = NULL;
        curFontHandle = NULL;
        CreateVectorFont_FromMemory_Init = 0;
        CreateVectorFont_FromFile_Init = 0;
        g_FontSize = 0;

        _msAPI_MLE_FreeCache();
    }// if bVectorFont_Exist
}

void msAPI_MLE_FONTBASE_VectorFontFree( void )
{
    ///MsConsumeSem(MMI_SEM1);

    msAPI_MLE_FONTBASE_VectorFontUnInit();

    ///MsProduceSem(MMI_SEM1);
    
    bVectorFont_Exist = FALSE;

    if( u16MapVectorSize )
    {
        FREEIF(u16MapVectorSize);
    } 
}

MLE_Ret msAPI_MLE_FONTBASE_VectorFontChangeFontFromCus(U32 nFontId, U32 u32FontSize)
{
    MLE_Ret nRetVal = MLE_RET_SUCCESS;
#ifndef __FEATURE_VECTOR_FONT_ON_T_CARD_ACCESS_FILE__
    U8 *pOldTTFontData = gpCurTTFontData; // have to free
#endif
///    U8 *pFontArray[MAX_VECTOR_FONT_NUM] = {0};
///    U16 u16FontSize = 0;
///    U32 u32FontSizeArray[MAX_VECTOR_FONT_NUM] = {0};

    ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "FONTBASE_VectorFontChangeFontFromCus: ChangeFontFromCus!");
    
    ///MsConsumeSem(MMI_SEM1);
//todo skip now
#if 0
    if(bTTFontFromCus == FALSE)
    {
        //get ttf data and size from cus
        nRetVal = MLE_LoadFontDataToMem();
        if(nRetVal != MLE_RET_SUCCESS)
        {
            LOG_ERROR(MLE_LEVEL_GRAPHIC, "FONTBASE_VectorFontChangeFontFromCus: Out of memory!");
            ///MsProduceSem(MMI_SEM1);
            return MLE_RET_OUT_OF_MEMORY;
        }
        
        nRetVal = FONTBASE_VectorFontReloadCusToMem();
    }
    msAPI_MLE_GetFontDataArray(FONT_CAT_VECTOR, (const U8 **)pFontArray, u32FontSizeArray, &u16FontSize, MAX_VECTOR_FONT_NUM);

    _msAPI_MLE_FONTBASE_VectorFontSetCurTTFontData(pFontArray[nFontId], u32FontSizeArray[nFontId]);
    msAPI_MLE_FONTBASE_VectorFontUnInit();
    
#else
    nFontId = nFontId;
    TTF_TRACE(printf("TTF Size=%d\n", u32FontSize));
    #if defined( TTF_BUFFER_ADR )
    	_msAPI_MLE_FONTBASE_VectorFontSetCurTTFontData((U8 *)(_PA2VA((TTF_BUFFER_ADR & MIU1) ? (TTF_BUFFER_ADR | MIU_INTERVAL) : (TTF_BUFFER_ADR))), u32FontSize);
		#else
			u32FontSize = u32FontSize;
    #endif
#endif
    
    _msAPI_MLE_FONTBASE_VectorFontInitEx(msAPI_MLE_FONT_PL_GetFTBufferSize());
    nRetVal = msAPI_MLE_FONTBASE_CreateVectorFont_FromMemory(gpCurTTFontData, gu32CurTTFontSize);
    msAPI_MLE_FONTBASE_SetVectorFontSize(DEFAULT_VECTOR_SIZE);
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
#ifndef __FEATURE_VECTOR_FONT_ON_T_CARD_ACCESS_FILE__
    if(bTTFontFromCus == FALSE)
        FREEIF(pOldTTFontData);
#endif

    bTTFontFromCus = TRUE;
        
    ///MsProduceSem(MMI_SEM1);
    
    return nRetVal;
}

static void _msAPI_MLE_FONTBASE_VectorFontSetCurTTFontData(U8 *pData, U32 u32DataSize)
{
    gpCurTTFontData = pData;
    gu32CurTTFontSize = u32DataSize;
}

static MLE_Ret msAPI_MLE_FONTBASE_SetVectorFontSize( U32 u32FontSize)
{
    TTF_TRACE(printf("%d %s %s, g_FontFace=%x, g_FontSize=%d, u32FontSize=%d\n", __LINE__, __FUNCTION__, __FILE__, (U32)g_FontFace, g_FontSize, u32FontSize));
    if(g_FontSize == u32FontSize && g_FontSize != 0)
    {
        TTF_TRACE(printf("%d %s %s, g_FontFace=%x\n", __LINE__, __FUNCTION__, __FILE__, (U32)g_FontFace));
        return MLE_RET_SUCCESS;
    }
    else
    {
        U16 px = 0;
        FT_UInt width  = 0;
        FT_UInt height = 0;
        FT_Error  error;

        TTF_TRACE(printf("%d %s %s, g_FontFace=%x\n", __LINE__, __FUNCTION__, __FILE__, (U32)g_FontFace));
        g_FontSize = u32FontSize;
        px = (g_FontSize * 72) / VERTICAL_RESOLUTION;
        width  = (FT_UInt) px << 6; // 26.6
        height = (FT_UInt) px << 6; // 26.6

        error = FT_Set_Char_Size( g_FontFace, width, height,
            HORIZONTAL_RESOLUTION, VERTICAL_RESOLUTION);

        if(error)
        {
            return MLE_RET_FAILED;
        }

    }
    
    return MLE_RET_SUCCESS;
}

U16 msAPI_MLE_FONTBASE_GetVectorFontSize( void )
{
    U16 px = (g_FontSize * 72) / VERTICAL_RESOLUTION;
    return px;
}

BOOLEAN msAPI_MLE_FONTBASE_IsVectorFontExist(void)  
{
    if( bVectorFont_Exist )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

///FOR APP: zoom vector face
MLE_Ret msAPI_MLE_FONTBASE_ZoomVectorFont(float ZoomFactor)
{
    ///MsConsumeSem(MMI_SEM1);
    ratio = _msAPI_MLE_FloatTo16dot16(ZoomFactor);
    ///MsProduceSem(MMI_SEM1);
    return MLE_RET_SUCCESS;
}

MLE_Ret msAPI_MLE_FONTBASE_CreateVectorFont_FromFile(void)
{
    MLE_Ret nRetVal = MLE_RET_SUCCESS;

    if (CreateVectorFont_FromFile_Init == 0)
    {
        FT_Bytes pBASE = NULL;
        FT_Bytes pGDEF = NULL;
        FT_Bytes pGPOS = NULL;
        FT_Bytes pGSUB = NULL;
        FT_Bytes pJSTF = NULL;
        //FT_Bytes pTables[FT_VALIDATE_GX_LENGTH] = {NULL};

        nRetVal = FT_New_Face(context, (const char *)font_pathname, 0, &g_FontFace);
        if(nRetVal != MLE_RET_SUCCESS)
        {
            ///LOG_ERROR(MLE_LEVEL_GRAPHIC, "FONTBASE_CreateVectorFont_FromFile: FT_New_Face Fail nRetVal = %d", nRetVal);
            return nRetVal;
        }
        FT_Select_Charmap(g_FontFace, ENCODING_TYPE);

        FontHandleAry[FONT_FROM_FILE].fontfrom = FONT_FROM_FILE;
        FontHandleAry[FONT_FROM_FILE].faceIndex = 0;
        FontHandleAry[FONT_FROM_FILE].cmapIndex = g_FontFace->charmap ? FT_Get_Charmap_Index( g_FontFace->charmap )
                : 0;
        
        FT_OpenType_Validate( g_FontFace,
                              _OTF_VALIDATE_ALL,
                              &pBASE,
                              &pGDEF,
                              &pGPOS,
                              &pGSUB,
                              &pJSTF );
        FontHandleAry[FONT_FROM_FILE].pGDEF = (const U8 *)pGDEF;
        FontHandleAry[FONT_FROM_FILE].pGPOS = (const U8 *)pGPOS;
        FontHandleAry[FONT_FROM_FILE].pGSUB = (const U8 *)pGSUB;

        FontHandleAry[FONT_FROM_FILE].u16UnitsPerEM = g_FontFace->units_per_EM;

        CreateVectorFont_FromFile_Init = 1;
    }

    curFontHandle = &FontHandleAry[FONT_FROM_FILE];

    return nRetVal;
}

MLE_Ret msAPI_MLE_FONTBASE_CreateVectorFont_FromMemory(const void* data, U32 size)
{
    MLE_Ret nRetVal = MLE_RET_SUCCESS;
    
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    if (CreateVectorFont_FromMemory_Init == 0)
    {
        FT_Bytes pBASE = NULL;
        FT_Bytes pGDEF = NULL;
        FT_Bytes pGPOS = NULL;
        FT_Bytes pGSUB = NULL;
        FT_Bytes pJSTF = NULL;
        //FT_Bytes pTables[FT_VALIDATE_GX_LENGTH] = {NULL};
    
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
        nRetVal = FT_New_Memory_Face(context, data, size, 0, &g_FontFace);
        if(nRetVal != MLE_RET_SUCCESS)
        {
            TTF_TRACE(printf("%d %s %s, nRetVal=%d\n", __LINE__, __FUNCTION__, __FILE__, nRetVal));
            ///LOG_ERROR(MLE_LEVEL_GRAPHIC, "FONTBASE_CreateVectorFont_FromMemory: FT_New_Memory_Face Fail nRetVal = %d", nRetVal);
            return nRetVal;
        }
        FT_Select_Charmap(g_FontFace, ENCODING_TYPE);

        FontHandleAry[FONT_FROM_MEMORY].fontfrom = FONT_FROM_MEMORY;
        FontHandleAry[FONT_FROM_MEMORY].faceIndex = 0;
        FontHandleAry[FONT_FROM_MEMORY].cmapIndex = g_FontFace->charmap ? FT_Get_Charmap_Index( g_FontFace->charmap )
                : 0;
        
        FT_OpenType_Validate( g_FontFace,
                              _OTF_VALIDATE_ALL,
                              &pBASE,
                              &pGDEF,
                              &pGPOS,
                              &pGSUB,
                              &pJSTF );
        FontHandleAry[FONT_FROM_MEMORY].pGDEF = (const U8 *)pGDEF;
        FontHandleAry[FONT_FROM_MEMORY].pGPOS = (const U8 *)pGPOS;
        FontHandleAry[FONT_FROM_MEMORY].pGSUB = (const U8 *)pGSUB;

        FontHandleAry[FONT_FROM_MEMORY].u16UnitsPerEM = g_FontFace->units_per_EM;

        CreateVectorFont_FromMemory_Init = 1;
    }
    
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    curFontHandle = &FontHandleAry[FONT_FROM_MEMORY];
    _msAPI_MLE_FONTBASE_VectorFontSetCurTTFontData((U8 *)data, size);
     TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    return nRetVal;
}

U32 msAPI_MLE_FONTBASE_VectorFontGetGlyphId(U32 u32UniCode)
{ 
    U32 u32GlyphId = 0;
    U32* pGlyphId = NULL;

    ///MsConsumeSem(MMI_SEM1);
    pGlyphId = (U32*)msAPI_COMMON_hashtable_search(_g_pGlyphIdCacheTable, (void*)u32UniCode);
    if(pGlyphId != NULL)
    {
        u32GlyphId = *pGlyphId;         
    }
    else
    {
        u32GlyphId = FT_Get_Char_Index( g_FontFace, u32UniCode );
        _msAPI_MLE_InsertGlyphIdCache((unsigned int)u32UniCode, u32GlyphId);
    }
    ///MsProduceSem(MMI_SEM1);
    return u32GlyphId;
}

static MLE_Ret msAPI_MLE_FONTBASE_VectorFontGetKerning(U32 u32FontSize, U16 u16PreGlyphId, U16 u16CurrentGlyphId, TTF_Vector *pKVector )
{
    MLE_Ret eResult = MLE_RET_SUCCESS;
    FT_Vector sKVec;

    if ( pKVector == NULL )
    {
        return MLE_RET_BAD_PARAM;
    }

    ///MsConsumeSem(MMI_SEM1);
    eResult = msAPI_MLE_FONTBASE_SetVectorFontSize(u32FontSize);
    if (eResult == MLE_RET_SUCCESS)
    {
        if ( FT_HAS_KERNING(g_FontFace) )
        {
            if (FT_Get_Kerning(g_FontFace, u16PreGlyphId, u16CurrentGlyphId, ft_kerning_default, &sKVec) == 0 )
            {
                pKVector->x = sKVec.x;
                pKVector->y = sKVec.y;
            }
            else
            {
                eResult = MLE_RET_FAILED;
            }
        }
        else
        {
            eResult = MLE_RET_NOT_FOUND;
        }
    }

    ///MsProduceSem(MMI_SEM1);

    return eResult;
}

MLE_Ret msAPI_MLE_FONTBASE_VectorFontGetFaceInf( TTF_FaceInf *pFaceInf, U32 u32FontSize)
{
    MLE_Ret eResult = MLE_RET_SUCCESS;

    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    if ( pFaceInf == NULL )
    {
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
        return MLE_RET_BAD_PARAM;
    }

    ///MsConsumeSem(MMI_SEM1);
    TTF_TRACE(printf("%d %s %s, u32FontSize=%d\n", __LINE__, __FUNCTION__, __FILE__, u32FontSize));
    eResult = msAPI_MLE_FONTBASE_SetVectorFontSize(u32FontSize);
    
    if (eResult == MLE_RET_SUCCESS)
    {
        pFaceInf->ascender = g_FontFace->size->metrics.ascender;
        pFaceInf->descender = g_FontFace->size->metrics.descender;
        pFaceInf->yScale = g_FontFace->size->metrics.y_scale;
        pFaceInf->height = g_FontFace->size->metrics.height;
        pFaceInf->yMax = g_FontFace->bbox.yMax;
    }
    else
    {
        eResult = MLE_RET_FAILED;
    }
    
    ///MsProduceSem(MMI_SEM1);
    
    return eResult;
}

// input 26.6, multiply 16.16, get 26.6, output integer
static S32 msAPI_MLE_FONTBASE_VectorFontZoomValue(S32 nValue)
{
    if (0x10000 == ratio)       // no zooming, return integer directly
    {
        return nValue >> 6;
    }
    else
    {
        return (FT_MulFix(nValue, ratio) >> 6);
    }
}

const U8* msAPI_MLE_FONTBASE_VectorFontGetGDEFTable( void )
{
    const U8 *pGDEF = NULL;
    
    if ( bVectorFont_Exist && curFontHandle != NULL )
    {
        pGDEF = curFontHandle->pGDEF;
    }

    return pGDEF;
}

const U8* msAPI_MLE_FONTBASE_VectorFontGetGPOSTable( void )
{
    const U8 *pGPOS = NULL;
    
    if ( bVectorFont_Exist && curFontHandle != NULL )
    {
        pGPOS = curFontHandle->pGPOS;
    }

    return pGPOS;
}

const U8* msAPI_MLE_FONTBASE_VectorFontGetGSUBTable( void )
{
    const U8 *pGSUB = NULL;
    
    if ( bVectorFont_Exist && curFontHandle != NULL )
    {
        pGSUB = curFontHandle->pGSUB;
    }

    return pGSUB;
}

#if 0
const U8* msAPI_MLE_FONTBASE_VectorFontGetKernTable( void )
{
    const U8 *pKern = NULL;
    
    if ( bVectorFont_Exist && curFontHandle != NULL )
    {
        pKern = curFontHandle->pKern;
    }

    return pKern;
}
#endif

#if 0
const U8* msAPI_MLE_FONTBASE_VectorFontGetMortTable( void )
{
    const U8 *pMort = NULL;
    
    if ( bVectorFont_Exist && curFontHandle != NULL )
    {
        pMort = curFontHandle->pMort;
    }

    return pMort;
}
#endif

U16 msAPI_MLE_FONTBASE_VectorFontGetUnitPerEM( void )
{
    return curFontHandle->u16UnitsPerEM;
}

S32 msAPI_MLE_FONTBASE_VectorFontGetXScaleFactor( void )
{
    return _FONT_VECTOR_X_SCALE_FACTOR;
}

S32 msAPI_MLE_FONTBASE_VectorFontGetYScaleFactor( void )
{
    return _FONT_VECTOR_Y_SCALE_FACTOR;
}

BOOLEAN _msAPI_MLE_FontVectorIsControlChar(U32 u32Unicode)
{
    if ( u32Unicode == 0xFFFF ||    // Non-characters or used in byte order signature
        u32Unicode == 0xFFFE)  // Non-characters
        return TRUE;

    return FALSE;
}

void msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(TTF_Bitmap *pTFBitmap)
{
    if ( pTFBitmap )
    {
        FREEIF(pTFBitmap->buffer);
        FREEIF(pTFBitmap->ibuffer);
        FREE(pTFBitmap);
        pTFBitmap=NULL;
    }
}

#ifdef __INDIC_FONT__
static U16 _msAPI_MLE_FontVectorGetNextCodes(HindiScript_e eScript, LE_LanguageTag_e eLang, const U16 *pInTxt, U32 InLen, U32 nOffset, U32 nSubLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed, BOOLEAN bDispStr, U16 *pLastCode, BOOLEAN bInit, U32 *pu32Features)
#else
static U16 _msAPI_MLE_FontVectorGetNextCodes(LE_LanguageTag_e eLang, const U16 *pInTxt, U32 InLen, U32 nOffset, U32 nSubLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed, BOOLEAN bDispStr, U16 *pLastCode, BOOLEAN bInit)
#endif //__INDIC_FONT__
{
    U16 nLen;

    if ( pLastCode )
    {
        *pLastCode = 0;
    }

    if ( nOffset + nSubLen > InLen )
    {
        return 0;
    }

#ifdef __INDIC_FONT__
    if ( pu32Features )
    {
        *pu32Features = 0;
    }
#endif //__INDIC_FONT__    

#ifdef __BIDI_TEXT__
    nLen = msAPI_MLE_TextArabicVectorGetNextCodes(pInTxt, InLen, nOffset, nSubLen, pOutCode, nOutLen, paConsumed, bDispStr, pLastCode);
    if (nLen != 0)
        return nLen;   
#endif

#ifdef __INDIC_FONT__
    if ( bInit )
    {
        nLen = msAPI_MLE_FontHindiGetNextCodes(eScript, eLang, pInTxt, InLen, nOffset, nSubLen, pOutCode, nOutLen, paConsumed, bDispStr, pu32Features, pInTxt, nOffset);
    }
    else
    {
        nLen = msAPI_MLE_FontHindiGetNextCodes(eScript, eLang, (pInTxt + nOffset), InLen - nOffset, 0, nSubLen, pOutCode, nOutLen, paConsumed, bDispStr, pu32Features, pInTxt, nOffset);
    }
    if ( nLen != 0 )
        return nLen;    
#endif //__INDIC_FONT__ 

    nLen = msAPI_MLE_FontThaiVectorGetNextCodes((pInTxt + nOffset), nSubLen, pOutCode, nOutLen, paConsumed);
    if (nLen != 0)
        return nLen;

    nLen = msAPI_MLE_FontLatineVectorGetNextCodes((pInTxt + nOffset), nSubLen, pOutCode, nOutLen, paConsumed);
    if (nLen != 0)
        return nLen;

#ifdef __HEBREW_FONT__    
    nLen = msAPI_MLE_TextHebrewVectorGetNextCodes((pInTxt + nOffset), nSubLen, pOutCode, nOutLen, paConsumed);
    if (nLen != 0)
        return nLen;
#endif

    if( !msAPI_MLE_FontBaseIsControlChar(pInTxt[nOffset]) )
    {
        pOutCode[0] = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(pInTxt[nOffset]);
        paConsumed[0] = 1;
        paConsumed[1] = 1;
        nLen = 1;

        return nLen;
    }
    else //if ( msAPI_MLE_FontBaseIsControlChar(pInTxt[nOffset]))
    {
        U32 i;
        for (i=nOffset+1; i<InLen; i++)
        {
            if (msAPI_MLE_FontBaseIsControlChar(pInTxt[i])==FALSE)
                break;
        }
        // in whole string are all control characters. 
        if (i==InLen)
        {
            pOutCode[0]= 0;
            nLen = 0;
            paConsumed[0] = InLen-nOffset;          
        }
        else
        {       
            pOutCode[0] = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(pInTxt[i]);
            paConsumed[0] = i-nOffset+1;
            paConsumed[1] = paConsumed[0];
            nLen = 1;
        }
    }

    return nLen;
}

#ifdef __INDIC_FONT__
static void _msAPI_MLE_FontVectorGetNextCodeXOffset(U32 u32FontSize, HindiScript_e eScript, LE_LanguageTag_e eLang, U16 *pu16Glyphs, U16 u16GlyphLen, U16 *pu16BaseOffset, U16 u16NextOffset, S16 *ps16XOffset, S16 *ps16YOffset, S16 *ps16NextXOffset, S16 *ps16NextYOffset, U32 u32Features )
#else
static void _msAPI_MLE_FontVectorGetNextCodeXOffset(U32 u32FontSize, LE_LanguageTag_e eLang, U16 *pu16Glyphs, U16 u16GlyphLen, U16 *pu16BaseOffset, U16 u16NextOffset, S16 *ps16XOffset, S16 *ps16YOffset, S16 *ps16NextXOffset, S16 *ps16NextYOffset )
#endif //__INDIC_FONT__
{
    BOOLEAN bResult = FALSE;

    if ( pu16Glyphs == NULL || pu16BaseOffset == NULL || pu16BaseOffset == NULL || u16GlyphLen == 0 || ps16XOffset == NULL || ps16YOffset == NULL )
    {
        return;
    }

#ifdef __INDIC_FONT__
    {
        bResult = msAPI_MLE_FontHindiVectorGetNextOffset(eScript, eLang, pu16Glyphs, u16GlyphLen, u16NextOffset, pu16BaseOffset, ps16XOffset, ps16YOffset, ps16NextXOffset, ps16NextYOffset, u32Features);
    }
#endif //__INDIC_FONT__

    if ( !bResult )
    {   
        TTF_Vector kVec;

        if ( msAPI_MLE_FONTBASE_VectorFontGetKerning(u32FontSize, pu16Glyphs[(*pu16BaseOffset)], pu16Glyphs[u16NextOffset], &kVec) == MLE_RET_SUCCESS )
        {
            *ps16XOffset = (S16)(kVec.x / 64);
            *ps16YOffset = (S16)(kVec.y / 64);
        }

        *pu16BaseOffset = u16NextOffset;
    }
}

MLE_Ret msAPI_MLE_FONTBASE_Vector_MeasureText(U32 nFontSize, 
                                    const U16 *pText,                    // text buffer pointer
                                    U32 nChars,                          // number of text character
                                    U32 nOffset,                         // 0
                                    U32 nSubLen,                         // still number of text character
                                    U32 nMaxWidth,
                                    U32 *pFits,                          // [out]
                                    U32 *pPixels,                        // [out]
                                    U32 nType,
                                    U32 bSkip,
                                    BOOLEAN bDispStr )                   // FALSE
{
    U32 i=0; 
    U32 xAdvance = 0;
    U32 nRemains = 0;
#ifdef __BIDI_TEXT__
    U32 nBreakLen = 0;
    U32 nBreakRemains = 0;
    U32 previous_glyph = 0;
    MLE_Ret error1 = MLE_RET_SUCCESS;
#endif //__BIDI_TEXT__  
    U32 measure_glyph = 0;
    TTF_FaceInf sFaceInf = {0, 0, 0, 0, 0};
    MLE_Ret error = MLE_RET_SUCCESS;
    BOOLEAN bOutline = (nType&FONT_TYPE_OUTLINE)==0 ? FALSE:TRUE;
    U32 nOLPixels = bOutline? OUTLINE_PIXEL:0;
    S16 nPen_x = 0;
    S16 nLastPen_x = 0;

    bSkip = bSkip;
    
    if (NULL == pText ||
        NULL == pFits ||
        NULL == pPixels)
    {
        return MLE_RET_BAD_PARAM;
    }

    // if offset + remaining character is bigger than number of text character
    if ( (nOffset + nSubLen) > nChars )
    {
        return MLE_RET_BAD_PARAM;
    }
    
    error = msAPI_MLE_FONTBASE_VectorFontGetFaceInf(&sFaceInf, nFontSize);    
    if ( error != MLE_RET_SUCCESS ) 
    {
        ///LOG_ERROR(MLE_LEVEL_GRAPHIC, "msAPI_MLE_FONTBASE_Vector_MeasureText error(%d)", error);
        return MLE_RET_FAILED;
    }

    pText = (pText + nOffset);
    nRemains = nSubLen;

    {
        const U16 *pOriginalText = pText;
        U32 nOriginalLen = nChars;
        U32 nCurrentOffset = nOffset;
#ifdef __BIDI_TEXT__
        S8 nDiff = 0;
        U16 u16BaseOffset = 0;
#endif //__BIDI_TEXT__  
        U32 nConsumed[MAX_CODE_COUNT + 1] = {0}, nLen = 0;
        U16 pCodes[MAX_CODE_COUNT] = {0};
        const U16 *pCurTxt = pText;
        S32 s32CurrentCharWidth = 0;
        S16 s16XShiftOffset = 0;
        S16 s16YShiftOffset = 0;
        S16 s16NextXShiftOffset = 0;
        S16 s16NextYShiftOffset = 0;
        S16 s16LastXShiftOffset = 0;
        S16 s16LastYShiftOffset = 0;
        U32         nCnAdvance = 0;
        BOOLEAN     bCurrentIsCN = FALSE;  
        LE_LanguageTag_e eLang = LE_LANGUAGE_TAG_NULL;
            
#ifdef __INDIC_FONT__
        HindiScript_e eScript = 0;
        U32 u32Features = 0;
#endif //__INDIC_FONT__ 

#if ( ENABLE_TTF_FONT )
        U16 u16_200C_GyphId = 0xFFFE;
        U16 u16_200D_GyphId = 0xFFFE;
        eLang = msAPI_OSD_GetOSDLanguageTag();
        u16_200C_GyphId = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(0x200C);
        u16_200D_GyphId = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(0x200D);
#endif

        while ( nRemains > 0 )
        {
            U16 LastCode = 0;

            if ( EMPTY_CHAR(*pCurTxt) )
            {
                // special character, do not need to draw
                pCurTxt++;
                nCurrentOffset++;
                nRemains--;
                continue;
            }

            if((0x4e00 <= *pCurTxt) && (*pCurTxt <= 0x9fa5) && nOLPixels == 0)
            {
                bCurrentIsCN = TRUE;
            }
            else
            {
                bCurrentIsCN = FALSE;
            }

            if(bCurrentIsCN == TRUE && nCnAdvance >0 && nPen_x > 0)
            {
                nLen = 1;
                nConsumed[0] = 1;
                nConsumed[1] = 1;
                pCodes[0] = 0;
            }
            else
            {                
#ifdef __INDIC_FONT__
                eScript = msAPI_MLE_FontHindiGetCharScript(pOriginalText[nCurrentOffset]);
                nLen = _msAPI_MLE_FontVectorGetNextCodes(eScript, eLang, pOriginalText, nOriginalLen, nCurrentOffset, nRemains, pCodes, MAX_CODE_COUNT, nConsumed, bDispStr, &LastCode, FALSE, &u32Features);
#else
                nLen = _msAPI_MLE_FontVectorGetNextCodes(eLang, pOriginalText, nOriginalLen, nCurrentOffset, nRemains, pCodes, MAX_CODE_COUNT, nConsumed, bDispStr, &LastCode, FALSE);
#endif //__INDIC_FONT__
            }
            pCurTxt += nConsumed[0];
            nCurrentOffset += nConsumed[0];
            if ( nConsumed[0] > nRemains )
            {
                nRemains = 0;
            }
            else
            {
                nRemains -= nConsumed[0];
            }
#ifdef __BIDI_TEXT__
            u16BaseOffset = 0;
#endif //__BIDI_TEXT__ 
            if(bCurrentIsCN == FALSE && nLen == 1  && _msAPI_MLE_FontVectorIsControlChar((U16)pCodes[0]))
            {
                continue;
            }

            nLastPen_x = nPen_x;

            for (i=0; i<nLen; i++)
            {
                S32 s32TempPreGap = 0;
                S32 s32TempPosGap = 0;
                TTF_Bitmap *pTTFBmp = NULL;

                if(bCurrentIsCN == TRUE && nCnAdvance >0 && nPen_x > 0)
                {
                    nPen_x = nPen_x + nCnAdvance;
                    break;
                }

                s16XShiftOffset = 0;
                s16YShiftOffset = 0;
                s16NextXShiftOffset = 0;
                s16NextYShiftOffset = 0;
                
                measure_glyph = pCodes[i];

#ifdef __BIDI_TEXT__                
                //if(previous_glyph != 0)
                {
#ifdef __INDIC_FONT__
                    _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eScript, eLang, pCodes, nLen, &u16BaseOffset, i, &s16XShiftOffset, &s16YShiftOffset, &s16NextXShiftOffset, &s16NextYShiftOffset, u32Features);
#else
                    _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eLang, pCodes, nLen, &u16BaseOffset, i, &s16XShiftOffset, &s16YShiftOffset, &s16NextXShiftOffset, &s16NextYShiftOffset);
#endif //__INDIC_FONT__ 

                    s16XShiftOffset += s16LastXShiftOffset;
                    s16YShiftOffset += s16LastYShiftOffset;
                    
                    s16LastXShiftOffset = s16NextXShiftOffset;
                    s16LastYShiftOffset = s16NextYShiftOffset;
                }

                previous_glyph = measure_glyph;
#endif //__BIDI_TEXT__    

                 ///LOG_TRACE(MLE_LEVEL_GRAPHIC, "glyph id = %d", measure_glyph);
                
#if (FONT_EDGE_AUTO_CONNECT)
                switch( eScript )
                {
                    case HINDI_SCRIPT_DEVA:
                    case HINDI_SCRIPT_BENG:
                    case HINDI_SCRIPT_PUNJ:
                        ft_gray_RenderEdgePatch(ENABLE);
                        break;
                    default:
                        break;
                }
#endif
                
                error = _msAPI_MLE_LoadTTFBmpAllocate(nFontSize, measure_glyph, &pTTFBmp, 0, 0, nOLPixels, FALSE);
#if (FONT_EDGE_AUTO_CONNECT)
                ft_gray_RenderEdgePatch(DISABLE);
#endif
                if(error == MLE_RET_SUCCESS)
                {
                    ///LOG_TRACE(MLE_LEVEL_GRAPHIC, "xadvance = %d", pTTFBmp->xadvance);

                    xAdvance = pTTFBmp->xadvance + s16XShiftOffset;
                    s32CurrentCharWidth = pTTFBmp->width;

                    if ( (S32)(xAdvance) > 0 )
                    {
                        if(bCurrentIsCN == TRUE && nCnAdvance == 0)
                        {
                            nCnAdvance = xAdvance;
                        }

                        if(nOLPixels)
                        {
                            if ( pTTFBmp->s32PreGap < (S32)nOLPixels )
                            {               
                                s32TempPreGap = nOLPixels - (pTTFBmp->s32PreGap);
                            }

                            if ( pTTFBmp->s32PosGap < (S32)nOLPixels )
                            {               
                                s32TempPosGap = nOLPixels - (pTTFBmp->s32PosGap);
                            }
                        }

                        if ( nPen_x == 0 )
                        {
                            if ( pTTFBmp->x < 0 )
                            {
                                xAdvance = xAdvance - pTTFBmp->x;
                            }
                            nPen_x = s32TempPreGap;
                        }

                        if ( (nRemains <= 0 && i == (nLen - 1)) || pTTFBmp->s32ZeroWidth>=0 )
                        {
                            xAdvance = xAdvance + s32TempPosGap;
                        }
                    }
                    else
                    {
                        if(nLen == 1)
                        {
                            xAdvance = (s32CurrentCharWidth + (S32)nOLPixels + s16XShiftOffset);
                        }
                        else
                        {
                            xAdvance = 0;
                        }
                    }

                    TTF_TRACE(printf("%d nPen_x=%d %d nRemains=%d\n", __LINE__, nPen_x, nPen_x + (S16)xAdvance, nRemains));
                    nPen_x = nPen_x + (S16)xAdvance;

                    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pTTFBmp);
                    pTTFBmp = NULL;

                    if(measure_glyph == 0)
                    {
                        break;
                    }
                }
                else
                {
                    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pTTFBmp);
                    pTTFBmp = NULL;
                    ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_Load_TTFBmpAllocate fails");
                    break;
                }

            }//end for (i=0; i<nLen; i++)

#ifdef __BIDI_TEXT__
            if (nMaxWidth > 0 && measure_glyph != 0)
            {
                S32 nTempXAdvance = xAdvance;
                S16 s16TempXShiftOffset = 0, s16TempYShiftOffset = 0;
                S16 s16TempNextXShiftOffset = 0, s16TempNextYShiftOffset = 0;
                TTF_Bitmap *pTTFBmp = NULL;

                if ( LastCode > 0 && nRemains > 0 )
                {
                    measure_glyph = LastCode;
                    if ( measure_glyph == (U16)(-1) )
                    {
                        measure_glyph = 0;
                    }

                    if ( previous_glyph != 0 )
                    {                                   
                        pCodes[nLen - 1] = LastCode;
                        if ( u16BaseOffset > 0 && u16BaseOffset == nLen - 1 )
                        {
                            u16BaseOffset = u16BaseOffset - 1;
                        }

#ifdef __INDIC_FONT__
                        _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eScript, eLang, pCodes, nLen, &u16BaseOffset, (nLen - 1  ), &s16TempXShiftOffset, &s16TempYShiftOffset, &s16TempNextXShiftOffset, &s16TempNextYShiftOffset, u32Features);
#else
                        _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eLang, pCodes, nLen, &u16BaseOffset, (nLen - 1), &s16TempXShiftOffset, &s16TempYShiftOffset);
#endif //__INDIC_FONT__  

                        //Todo: This part needs to refine
                        //FIXME!
                        /////////////////////////////////////////////
                        //s16TempXShiftOffset += s16LastXShiftOffset;
                        //s16TempYShiftOffset += s16LastYShiftOffset;
                        
                        //s16LastXShiftOffset = s16TempNextXShiftOffset;
                        //s16LastYShiftOffset = s16TempNextYShiftOffset;
                        /////////////////////////////////////////////
                    }

                    previous_glyph = measure_glyph;

#if (FONT_EDGE_AUTO_CONNECT)
                    switch( eScript )
                    {
                        case HINDI_SCRIPT_DEVA:
                        case HINDI_SCRIPT_BENG:
                        case HINDI_SCRIPT_PUNJ:
                            ft_gray_RenderEdgePatch(ENABLE);
                            break;
                        default:
                            break;
                    }
#endif

                    error1 = _msAPI_MLE_LoadTTFBmpAllocate(nFontSize, measure_glyph, &pTTFBmp, 0, 0, nOLPixels, FALSE);
#if (FONT_EDGE_AUTO_CONNECT)
                    ft_gray_RenderEdgePatch(DISABLE);
#endif
                    if(error1 == MLE_RET_SUCCESS)
                    {
                        if ( pTTFBmp->xadvance > 0 )
                        {
                            nTempXAdvance = s16TempXShiftOffset + pTTFBmp->xadvance;
                        }
                        else
                        {
                            nTempXAdvance = 0;
                        }
                    }
                    else
                    {
                        ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_Load_TTFBmpAllocate fails");
                        nTempXAdvance = 0;
                    }

                    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pTTFBmp);
                    pTTFBmp = NULL;
                }

                // original code type is smaller than last code type
                if ( (U32)nTempXAdvance == xAdvance )
                {
                    if ( (U32)(nLastPen_x + xAdvance + nOLPixels) > nMaxWidth )
                    {
                        nRemains += nConsumed[0];
                        nPen_x = (U32)(nLastPen_x + nDiff);
                        break;
                    }
                    nBreakLen = 0;
                    nDiff = 0;
                }
                else
                {
                    if ( (U32)(nLastPen_x + xAdvance + nOLPixels) > nMaxWidth )
                    {
                        if (nBreakLen == 0)
                        {
                            if ( (S32)xAdvance < nTempXAdvance && nRemains > 0 )
                            {
                                nBreakRemains = nRemains + nConsumed[0];
                                nBreakLen = (U32)(nLastPen_x + nDiff);
                                nPen_x = nLastPen_x + xAdvance;
                                continue;
                            }
                            else
                            {
                                nRemains += nConsumed[0];
                                nPen_x = (U32)(nLastPen_x + nDiff);
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    nBreakLen = 0;
                    nDiff = xAdvance - nTempXAdvance;
                }
            }
#endif //__BIDI_TEXT__

            if(nMaxWidth > 0 && nPen_x > (S16)nMaxWidth)
            {
                TTF_TRACE(printf("%d %d %d\n", __LINE__, nMaxWidth, (S16)nMaxWidth));
                nPen_x = nLastPen_x;
                nRemains += nConsumed[0];
                break;
            }
        }
    }

#ifdef __BIDI_TEXT__
    if (nBreakLen)
    {
        nRemains = nBreakRemains;
        nPen_x = nBreakLen;
        TTF_TRACE(printf("%d nPen_x=%d\n", __LINE__, nPen_x));
    }
#endif //__BIDI_TEXT__

    *pFits = nSubLen - nRemains;
    *pPixels = (U16)nPen_x;

    if ( error == MLE_RET_OUT_OF_MEMORY )
    {
        return error;
    }

#ifdef __BIDI_TEXT__
    if ( error1 == MLE_RET_OUT_OF_MEMORY )
    {
        return error1;
    }
#endif
    
    return MLE_RET_SUCCESS;
}

MLE_Ret msAPI_MLE_FONTBASE_Vector_MeasureClippedText(U32 nFontSize, 
        const U16 *pText,                    // text buffer pointer
        U32 nChars,                          // number of text character
        U32 nOffset,                         // 0
        U32 nSubLen,                         // still number of text character
        U32 nMaxWidth,
        U32 *pFits,                          // [out]
        U32 *pPixels,                        // [out]
        U32 nType,
        U32 bSkip,
        BOOLEAN bDispStr )                   // FALSE
{
    U32 i=0; 
    U32 xAdvance = 0;
    U32 nRemains = 0;
#ifdef __BIDI_TEXT__
    U32 nBreakLen = 0;
    U32 nBreakRemains = 0;
    U32 previous_glyph = 0;
    MLE_Ret error1 = MLE_RET_SUCCESS;
#endif //__BIDI_TEXT__  
    U32 measure_glyph = 0;
    TTF_FaceInf sFaceInf = {0, 0, 0, 0, 0};
    MLE_Ret error = MLE_RET_SUCCESS;
    BOOLEAN bOutline = (nType&FONT_TYPE_OUTLINE)==0 ? FALSE:TRUE;
    U32 nOLPixels = bOutline? OUTLINE_PIXEL:0;
    S16 nPen_x = 0;
    S16 nLastPen_x = 0;
    S16 *pPen_x = NULL;
    U8 u8Count = 0;

    bSkip = bSkip;
    
    if (NULL == pText ||
            NULL == pFits ||
            NULL == pPixels)
    {
        return MLE_RET_BAD_PARAM;
    }

    // if offset + remaining character is bigger than number of text character
    if ( (nOffset + nSubLen) > nChars )
    {
        return MLE_RET_BAD_PARAM;
    }

    error = msAPI_MLE_FONTBASE_VectorFontGetFaceInf(&sFaceInf, nFontSize);    
    if ( error != MLE_RET_SUCCESS ) 
    {
        ///LOG_ERROR(MLE_LEVEL_GRAPHIC, "msAPI_MLE_FONTBASE_Vector_MeasureText error(%d)", error);
        return MLE_RET_FAILED;
    }

    pText = (pText + nOffset);
    nRemains = nSubLen;

    pPen_x = (S16 *)MALLOC(nChars * sizeof(S16));
    
    {
        const U16 *pOriginalText = pText;
        U32 nOriginalLen = nChars;
        U32 nCurrentOffset = nOffset;
#ifdef __BIDI_TEXT__
        S8 nDiff = 0;
        U16 u16BaseOffset = 0;
#endif //__BIDI_TEXT__  
        U32 nConsumed[MAX_CODE_COUNT + 1] = {0}, nLen = 0;
        U16 pCodes[MAX_CODE_COUNT] = {0};
        const U16 *pCurTxt = pText;
        S32 s32CurrentCharWidth = 0;
        S16 s16XShiftOffset = 0;
        S16 s16YShiftOffset = 0;
        S16 s16NextXShiftOffset = 0;
        S16 s16NextYShiftOffset = 0;
        S16 s16LastXShiftOffset = 0;
        S16 s16LastYShiftOffset = 0;
        U32         nCnAdvance = 0;
        BOOLEAN     bCurrentIsCN = FALSE;  
        LE_LanguageTag_e eLang = LE_LANGUAGE_TAG_NULL;

#if ( ENABLE_TTF_FONT )
        eLang = msAPI_OSD_GetOSDLanguageTag();
#endif

#ifdef __INDIC_FONT__
        HindiScript_e eScript = 0;
        U32 u32Features = 0;
#endif //__INDIC_FONT__ 

        while ( nRemains > 0 )
        {
            U16 LastCode = 0;

            if ( EMPTY_CHAR(*pCurTxt) )
            {
                // special character, do not need to draw
                pCurTxt++;
                nCurrentOffset++;
                nRemains--;
                continue;
            }

            if((0x4e00 <= *pCurTxt) && (*pCurTxt <= 0x9fa5) && nOLPixels == 0)
            {
                bCurrentIsCN = TRUE;
            }
            else
            {
                bCurrentIsCN = FALSE;
            }

            if(bCurrentIsCN == TRUE && nCnAdvance >0 && nPen_x > 0)
            {
                nLen = 1;
                nConsumed[0] = 1;
                nConsumed[1] = 1;
                pCodes[0] = 0;
            }
            else
            {                
#ifdef __INDIC_FONT__
                eScript = msAPI_MLE_FontHindiGetCharScript(pOriginalText[nCurrentOffset]);
                nLen = _msAPI_MLE_FontVectorGetNextCodes(eScript, eLang, pOriginalText, nOriginalLen, nCurrentOffset, nRemains, pCodes, MAX_CODE_COUNT, nConsumed, bDispStr, &LastCode, FALSE, &u32Features);
#else
                nLen = _msAPI_MLE_FontVectorGetNextCodes(eLang, pOriginalText, nOriginalLen, nCurrentOffset, nRemains, pCodes, MAX_CODE_COUNT, nConsumed, bDispStr, &LastCode, FALSE);
#endif //__INDIC_FONT__
            }
            pCurTxt += nConsumed[0];
            nCurrentOffset += nConsumed[0];
            if ( nConsumed[0] > nRemains )
            {
                nRemains = 0;
            }
            else
            {
                nRemains -= nConsumed[0];
            }
#ifdef __BIDI_TEXT__
            u16BaseOffset = 0;
#endif //__BIDI_TEXT__ 
            if(bCurrentIsCN == FALSE && nLen == 1  && _msAPI_MLE_FontVectorIsControlChar((U16)pCodes[0]))
            {
                continue;
            }

            nLastPen_x = nPen_x;
            pPen_x[u8Count++] = nPen_x;

            for (i=0; i<nLen; i++)
            {
                S32 s32TempPreGap = 0;
                S32 s32TempPosGap = 0;
                TTF_Bitmap *pTTFBmp = NULL;

                if(bCurrentIsCN == TRUE && nCnAdvance >0 && nPen_x > 0)
                {
                    nPen_x = nPen_x + nCnAdvance;
                    break;
                }

                s16XShiftOffset = 0;
                s16YShiftOffset = 0;
                s16NextXShiftOffset = 0;
                s16NextYShiftOffset = 0;
                measure_glyph = pCodes[i];

#ifdef __BIDI_TEXT__                
                //if(previous_glyph != 0)
                {
#ifdef __INDIC_FONT__
                    _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eScript, eLang, pCodes, nLen, &u16BaseOffset, i, &s16XShiftOffset, &s16YShiftOffset, &s16NextXShiftOffset, &s16NextYShiftOffset, u32Features);
#else
                    _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eLang, pCodes, nLen, &u16BaseOffset, i, &s16XShiftOffset, &s16YShiftOffset, &s16NextXShiftOffset, &s16NextYShiftOffset);
#endif //__INDIC_FONT__ 

                    s16XShiftOffset += s16LastXShiftOffset;
                    s16YShiftOffset += s16LastYShiftOffset;
                    
                    s16LastXShiftOffset = s16NextXShiftOffset;
                    s16LastYShiftOffset = s16NextYShiftOffset;
                }

                previous_glyph = measure_glyph;
#endif //__BIDI_TEXT__    

                ///LOG_TRACE(MLE_LEVEL_GRAPHIC, "glyph id = %d", measure_glyph);
                
#if (FONT_EDGE_AUTO_CONNECT)
                switch( eScript )
                {
                    case HINDI_SCRIPT_DEVA:
                    case HINDI_SCRIPT_BENG:
                    case HINDI_SCRIPT_PUNJ:
                        ft_gray_RenderEdgePatch(ENABLE);
                        break;
                    default:
                        break;
                }
#endif
                
                error = _msAPI_MLE_LoadTTFBmpAllocate(nFontSize, measure_glyph, &pTTFBmp, 0, 0, nOLPixels, FALSE);
#if (FONT_EDGE_AUTO_CONNECT)
                ft_gray_RenderEdgePatch(DISABLE);
#endif
                if(error == MLE_RET_SUCCESS)
                {
                    ///LOG_TRACE(MLE_LEVEL_GRAPHIC, "xadvance = %d", pTTFBmp->xadvance);

                    xAdvance = pTTFBmp->xadvance + s16XShiftOffset;
                    s32CurrentCharWidth = pTTFBmp->width;

                    if ( (S32)(xAdvance) > 0 )
                    {
                        if(bCurrentIsCN == TRUE && nCnAdvance == 0)
                        {
                            nCnAdvance = xAdvance;
                        }

                        if(nOLPixels)
                        {
                            if ( pTTFBmp->s32PreGap < (S32)nOLPixels )
                            {               
                                s32TempPreGap = nOLPixels - (pTTFBmp->s32PreGap);
                            }

                            if ( pTTFBmp->s32PosGap < (S32)nOLPixels )
                            {               
                                s32TempPosGap = nOLPixels - (pTTFBmp->s32PosGap);
                            }
                        }

                        if ( nPen_x == 0 )
                        {
                            if ( pTTFBmp->x < 0 )
                            {
                                xAdvance = xAdvance - pTTFBmp->x;
                            }
                            nPen_x = s32TempPreGap;
                        }

                        if ( (nRemains <= 0 && i == (nLen - 1)) || pTTFBmp->s32ZeroWidth>=0 )
                        {
                            xAdvance = xAdvance + s32TempPosGap;
                        }
                    }
                    else
                    {
                        if(nLen == 1)
                        {
                            xAdvance = (s32CurrentCharWidth + (S32)nOLPixels + s16XShiftOffset);
                        }
                        else
                        {
                            xAdvance = 0;
                        }
                    }

                    TTF_TRACE(printf("%d nPen_x=%d %d nRemains=%d\n", __LINE__, nPen_x, nPen_x + (S16)xAdvance, nRemains));
                    nPen_x = nPen_x + (S16)xAdvance;

                    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pTTFBmp);
                    pTTFBmp = NULL;

                    if(measure_glyph == 0)
                    {
                        break;
                    } 
                }
                else
                {
                    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pTTFBmp);
                    pTTFBmp = NULL;
                    ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_Load_TTFBmpAllocate fails");
                    break;
                }

            }//end for (i=0; i<nLen; i++)

#ifdef __BIDI_TEXT__
            if (nMaxWidth > 0 && measure_glyph != 0)
            {
                S32 nTempAdvance = xAdvance;
                S16 s16TempXShiftOffset = 0, s16TempYShiftOffset = 0;
                S16 s16TempNextXShiftOffset = 0, s16TempNextYShiftOffset = 0;
                TTF_Bitmap *pTTFBmp = NULL;

                if ( LastCode > 0 && nRemains > 0 )
                {
                    measure_glyph = LastCode;
                    if ( measure_glyph == (U16)(-1) )
                    {
                        measure_glyph = 0;
                    }

                    if ( previous_glyph != 0 )
                    {                                   
                        pCodes[nLen - 1] = LastCode;
                        if ( u16BaseOffset > 0 && u16BaseOffset == nLen - 1 )
                        {
                            u16BaseOffset = u16BaseOffset - 1;
                        }

#ifdef __INDIC_FONT__
                        _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eScript, eLang, pCodes, nLen, &u16BaseOffset, (nLen - 1), &s16TempXShiftOffset, &s16TempYShiftOffset, &s16TempNextXShiftOffset, &s16TempNextYShiftOffset, u32Features);
#else
                        _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eLang, pCodes, nLen, &u16BaseOffset, (nLen - 1), &s16TempXShiftOffset, &s16TempYShiftOffset);
#endif //__INDIC_FONT__  

                        //Todo: This part needs to refine
                        //FIXME!
                        /////////////////////////////////////////////
                        //s16TempXShiftOffset += s16LastXShiftOffset;
                        //s16TempYShiftOffset += s16LastYShiftOffset;
                        
                        //s16LastXShiftOffset = s16TempNextXShiftOffset;
                        //s16LastYShiftOffset = s16TempNextYShiftOffset;
                        /////////////////////////////////////////////
                    }

                    previous_glyph = measure_glyph;

#if (FONT_EDGE_AUTO_CONNECT)
                    switch( eScript )
                    {
                        case HINDI_SCRIPT_DEVA:
                        case HINDI_SCRIPT_BENG:
                        case HINDI_SCRIPT_PUNJ:
                            ft_gray_RenderEdgePatch(ENABLE);
                            break;
                        default:
                            break;
                    }
#endif
                    
                    error1 = _msAPI_MLE_LoadTTFBmpAllocate(nFontSize, measure_glyph, &pTTFBmp, 0, 0, nOLPixels, FALSE);
#if (FONT_EDGE_AUTO_CONNECT)
                    ft_gray_RenderEdgePatch(DISABLE);
#endif
                    if(error1 == MLE_RET_SUCCESS)
                    {
                        if ( pTTFBmp->xadvance > 0 )
                        {
                            nTempAdvance = s16TempXShiftOffset + pTTFBmp->xadvance;
                        }
                        else
                        {
                            nTempAdvance = 0;
                        }
                    }
                    else
                    {
                        ////LOG_TRACE(MLE_LEVEL_GRAPHIC, "_Load_TTFBmpAllocate fails");
                        nTempAdvance = 0;
                    }

                    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pTTFBmp);
                    pTTFBmp = NULL;
                }

                // original code type is smaller than last code type
                if ( (U32)nTempAdvance == xAdvance )
                {
                    if ( (U32)(nLastPen_x + xAdvance + nOLPixels) > nMaxWidth )
                    {
                        nRemains += nConsumed[0];
                        nPen_x = (U32)(nLastPen_x + nDiff);
                        break;
                    }
                    nBreakLen = 0;
                    nDiff = 0;
                }
                else
                {
                    if ( (U32)(nLastPen_x + xAdvance + nOLPixels) > nMaxWidth )
                    {
                        if (nBreakLen == 0)
                        {
                            if ( (S32)xAdvance < nTempAdvance && nRemains > 0 )
                            {
                                nBreakRemains = nRemains + nConsumed[0];
                                nBreakLen = (U32)(nLastPen_x + nDiff);
                                nPen_x = nLastPen_x + xAdvance;
                                continue;
                            }
                            else
                            {
                                nRemains += nConsumed[0];
                                nPen_x = (U32)(nLastPen_x + nDiff);
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    nBreakLen = 0;
                    nDiff = xAdvance - nTempAdvance;
                }
            }
#endif //__BIDI_TEXT__

            if(nMaxWidth > 0 && nPen_x > (S16)nMaxWidth)
            {
                nPen_x = nLastPen_x;
                nRemains += nConsumed[0];
                
                //measure dot character width
#if 0
#ifdef __INDIC_FONT__
                _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eScript, eLang, pCodes, nLen, &u16BaseOffset, (nLen - 1), &s16TempXShiftOffset,  &s16TempYShiftOffset, u32Features);
#else
                _msAPI_MLE_FontVectorGetNextCodeXOffset(nFontSize, eLang, pCodes, nLen, &u16BaseOffset, (nLen - 1), &s16TempXShiftOffset, &s16TempYShiftOffset);
#endif //__INDIC_FONT__  
#endif
                break;
            }
        }
    }

#ifdef __BIDI_TEXT__
    if (nBreakLen)
    {
        nRemains = nBreakRemains;
        nPen_x = nBreakLen;
        TTF_TRACE(printf("%d nPen_x=%d\n", __LINE__, nPen_x));
    }
#endif //__BIDI_TEXT__

    *pFits = nSubLen - nRemains;
    *pPixels = (U16)nPen_x;

    if ( pPen_x )
        FREE(pPen_x);
    
    if ( error == MLE_RET_OUT_OF_MEMORY )
    {
        return error;
    }

#ifdef __BIDI_TEXT__
    if ( error1 == MLE_RET_OUT_OF_MEMORY )
    {
        return error1;
    }
#endif
    
    return MLE_RET_SUCCESS;
}

MLE_Ret msAPI_MLE_FONTBASE_Vector_DrawText(U32 FontSize,              // Size
        S32 xStart,                // start x
        S32 yStart,                // start y
        const U16 *pText,          // text buffer pointer
        U32 nChars,                // number of text character
        Rect_t *pCARect,           // Client area
        U32 nType,                  // Type
        OSDClrBtn *pclrBtn,
        BOOLEAN bFontMirror)
{
    S32 yDiff=0, WidChar=0;
    U32 nOLPixels, i;
    Rect_t GlyRect, DrawRect;
    S32 xFontStart, yFontStart;

    U16 nFontCnt = 0;
    TTF_Bitmap **tfBitmap;
    TTF_Bitmap *tBitmap = NULL;
    U16 u16Height = 0;
    TTF_FaceInf sFaceInf = {0, 0, 0, 0, 0};
    BOOLEAN bOutline = (nType&FONT_TYPE_OUTLINE)==0 ? FALSE : TRUE;
    MLE_Ret error;      
    S16 xOffset = 0;
    S16 s16LastXShiftOffset = 0, s16LastYShiftOffset = 0;
    U32 u32InfBufferSize = nChars + MAX_CODE_COUNT;
    
    HindiScript_e eScript = HINDI_MAX_SCRIPT_NUM;
    
#if ( MONO_FONT )
    pclrBtn = pclrBtn;
#endif
    
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    if (NULL == pText || NULL == pCARect )
    {
        return MLE_RET_BAD_PARAM;
    }
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    error = msAPI_MLE_FONTBASE_VectorFontGetFaceInf(&sFaceInf, FontSize); 
    if ( error != MLE_RET_SUCCESS ) 
    {
        ///LOG_ERROR(MLE_LEVEL_GRAPHIC, "msAPI_MLE_FONTBASE_Vector_DrawText error(%d)", error);
        return MLE_RET_FAILED;
    }
    
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    u16Height = msAPI_MLE_FONTBASE_VectorFontZoomValue(sFaceInf.ascender-sFaceInf.descender);
    if (bOutline)
    {
        u16Height += OUTLINE_PIXEL*2;
    }
    
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    if ( yStart + u16Height < (*pCARect).y ||
            yStart > ((*pCARect).y + (*pCARect).h) )
    {
        TTF_TRACE(printf("yStart=%d, u16Height=%d, (*pCARect).y=%d, (*pCARect).h=%d\n",  yStart, u16Height, (*pCARect).y, (*pCARect).h));
        return MLE_RET_SUCCESS;
    }
    
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    nOLPixels = bOutline ? OUTLINE_PIXEL:0;
    
    TTF_TRACE(printf("%d sizeof(TTF_Bitmap *)=%d, total = %d\n", __LINE__, sizeof(TTF_Bitmap *), (u32InfBufferSize) * sizeof(TTF_Bitmap *)));
    tfBitmap = (TTF_Bitmap **)MALLOC((u32InfBufferSize) * sizeof(TTF_Bitmap *));
    if(tfBitmap == NULL)
    {
        ////LOG_ERROR(MLE_LEVEL_GRAPHIC, "msAPI_MLE_FONTBASE_Vector_DrawText MALLOC tfBitmap error");
        return MLE_RET_OUT_OF_MEMORY;
    }
    MEMSET((void *)tfBitmap, 0, u32InfBufferSize * sizeof(TTF_Bitmap *));
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    {
        const U16 *pOriginalText = pText;
        U32 nOriginalLen = nChars;
        U32 nCurrentOffset = 0;
        U16 pCodes[MAX_CODE_COUNT] = {0};
        U32 nConsumed[MAX_CODE_COUNT + 1] = {0}, nLen = 0;
        const U16 *pCurTxt = pText;
        U16 u16BaseOffset = 0;
        LE_LanguageTag_e eLang = LE_LANGUAGE_TAG_NULL;
        U16 u16_200C_GyphId = 0xFFFE;
        U16 u16_200D_GyphId = 0xFFFE;

#if ( ENABLE_TTF_FONT )
        eLang = msAPI_OSD_GetOSDLanguageTag();
#endif

#ifdef __INDIC_FONT__
        //HindiScript_e eScript;
        U32 u32Features = 0;
#endif //__INDIC_FONT__     

        nFontCnt = 0;
        
        yDiff = msAPI_MLE_FONTBASE_VectorFontZoomValue(sFaceInf.ascender);
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));

        u16_200C_GyphId = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(0x200C);
        u16_200D_GyphId = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(0x200D);

        while ((S32)nChars > 0)
        {
            if ( EMPTY_CHAR(*pCurTxt) )
            {
                // special character, do not need to draw
                pCurTxt++;
                nCurrentOffset++;
                nChars--;
                TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                continue;
            }
            
#ifdef __INDIC_FONT__
            eScript = msAPI_MLE_FontHindiGetCharScript(pOriginalText[nCurrentOffset]);
            nLen = _msAPI_MLE_FontVectorGetNextCodes(eScript, eLang, pOriginalText, nOriginalLen, nCurrentOffset, nChars, pCodes, MAX_CODE_COUNT, nConsumed, TRUE, NULL, FALSE, &u32Features);
#else
            nLen = _msAPI_MLE_FontVectorGetNextCodes(eLang, pOriginalText, nOriginalLen, nCurrentOffset, nChars, pCodes, MAX_CODE_COUNT, nConsumed, TRUE, NULL, FALSE);
#endif //__INDIC_FONT__

            //A patch to prevent nChars < 0
            if ( nConsumed[0] > nChars )
                nConsumed[0] = nChars;
            nChars -= nConsumed[0];
            nCurrentOffset += nConsumed[0];
            pCurTxt += nConsumed[0];
            u16BaseOffset = 0;
            TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));

            if ( tfBitmap )
            {
                if ( u32InfBufferSize < (nFontCnt + nLen) )
                {
                    U32 u32TempInBufferSize = u32InfBufferSize;

                    u32InfBufferSize = nFontCnt + nLen + MAX_CODE_COUNT;
                    tfBitmap = (TTF_Bitmap **)REALLOC(tfBitmap, u32InfBufferSize * sizeof(TTF_Bitmap *));
                    if(tfBitmap == NULL)
                    {
                        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                        
                        ////LOG_ERROR(MLE_LEVEL_GRAPHIC, "msAPI_MLE_FONTBASE_Vector_DrawText REALLOC tfBitmap error");
                        return MLE_RET_OUT_OF_MEMORY;
                    }
                    MEMSET((void *)&(tfBitmap[u32TempInBufferSize]), 0, (u32InfBufferSize - u32TempInBufferSize) * sizeof(TTF_Bitmap *));
                }
            }

            if( _msAPI_MLE_FontVectorIsControlChar((U32)pCodes[0]) && nLen ==1 )
            {
                TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                
                continue;
            }

            s16LastXShiftOffset = 0;
            s16LastYShiftOffset = 0;
            
            for (i=0; i<nLen; i++)
            {
                S16 s16XShiftOffset = 0, s16YShiftOffset = 0;
                S16 s16NextXShiftOffset = 0, s16NextYShiftOffset = 0;

                WidChar = pCodes[i];

                if (WidChar == 0)
                {
///todo skip now
                    ///LOG_TRACE(MLE_LEVEL_GRAPHIC, "missing unicode %x glyph", pCodes[i]);
                    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                    TTF_TRACE(printf("missing unicode %x glyph\n", pCodes[i]));
                }

                TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));

                //if ( (nFontCnt + i) > 0 )
                {
                    s16XShiftOffset = 0;
                    s16YShiftOffset = 0;
                    s16NextXShiftOffset = 0;
                    s16NextYShiftOffset = 0;
                    
#ifdef __INDIC_FONT__
                    _msAPI_MLE_FontVectorGetNextCodeXOffset(FontSize, eScript, eLang, pCodes, nLen, &u16BaseOffset, i, &s16XShiftOffset, &s16YShiftOffset, &s16NextXShiftOffset, &s16NextYShiftOffset, u32Features);
#else
                    _msAPI_MLE_FontVectorGetNextCodeXOffset(FontSize, eLang, pCodes, nLen, &u16BaseOffset, i, &s16XShiftOffset, &s16YShiftOffset, &s16NextXShiftOffset, &s16NextYShiftOffset);
#endif //__INDIC_FONT__
                    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                    
                    s16XShiftOffset += s16LastXShiftOffset;
                    s16YShiftOffset += s16LastYShiftOffset;
                    
                    s16LastXShiftOffset = s16NextXShiftOffset;
                    s16LastYShiftOffset = s16NextYShiftOffset;
                }

                if ( (S32)(xStart + xOffset) > (*pCARect).x + (*pCARect).w )
                {                   
                    TTF_TRACE(printf("%d %s %s, xStart=%d, xOffset=%d, Rect.x=%d, Rect.w=%d\n", __LINE__, __FUNCTION__, __FILE__, xStart, xOffset, (*pCARect).x, (*pCARect).w));
                    
                    break;
                }
                
#if (FONT_EDGE_AUTO_CONNECT)
                switch( eScript )
                {
                    case HINDI_SCRIPT_DEVA:
                    case HINDI_SCRIPT_BENG:
                    case HINDI_SCRIPT_PUNJ:
                        ft_gray_RenderEdgePatch(ENABLE);
                        break;
                    default:
                        break;
                }
#endif
                
                TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));

                if( _msAPI_MLE_FontVectorIsControlChar((U32)pCodes[i]) || ( pCodes[i] == u16_200D_GyphId ) || ( pCodes[i] == u16_200C_GyphId ) )
                {
                    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                
                    continue;
                }

                if ( msAPI_MLE_FONTBASE_VectorFontTFBitmapAllocate(FontSize, WidChar, &tfBitmap[nFontCnt+i], xOffset + s16XShiftOffset, s16YShiftOffset, nOLPixels) != MLE_RET_SUCCESS)
                {
#if (FONT_EDGE_AUTO_CONNECT)
                    ft_gray_RenderEdgePatch(DISABLE);
#endif
                    break;
                }

#if (FONT_EDGE_AUTO_CONNECT)
                ft_gray_RenderEdgePatch(DISABLE);
#endif
                
                tBitmap = tfBitmap[nFontCnt+i];

                if ( yDiff < tBitmap->y )
                {
                    yDiff = tBitmap->y;
                }

                if ( (S32)(tBitmap->xadvance + s16XShiftOffset) > 0 )
                {
                    S32 s32TempPreGap = 0;
                    S32 s32TempPosGap = 0;

                    if(nOLPixels)
                    {
                        if ( tBitmap->s32PreGap < tBitmap->iOutLineWidth )
                        {               
                            s32TempPreGap = tBitmap->iOutLineWidth - (tBitmap->s32PreGap);
                        }

                        if ( tBitmap->s32PosGap < tBitmap->iOutLineWidth )
                        {               
                            s32TempPosGap = tBitmap->iOutLineWidth - (tBitmap->s32PosGap);
                        }
                    }

                    //first char
                    if ( xOffset == 0 )
                    {
                        if ( tBitmap->x < 0 )
                        {
                            tBitmap->xadvance = tBitmap->xadvance - tBitmap->x;
                            tBitmap->x = s32TempPreGap;
                        }
                        else
                        {
                            tBitmap->x = tBitmap->x + s32TempPreGap;
                        }

                        xOffset = tBitmap->xadvance;
                    }
                    else
                    {
                        xOffset = xOffset + tBitmap->xadvance + s16XShiftOffset;
                    }

                    if ( (nChars <= 0 && i == (nLen - 1)) || tBitmap->s32ZeroWidth>=0 )
                    {
                        xOffset = xOffset + s32TempPosGap;
                    }
                }
                else if(nLen == 1) //tBitmap->xadvance <0
                {
                    if(tBitmap->x < xOffset) //means left<0
                    {
                        tBitmap->x = xOffset;
                    }

                    xOffset = xOffset + tBitmap->width + nOLPixels + s16XShiftOffset;

                }

                if(WidChar == 0)
                {
                    nLen = 1;
                }

                //Draw outline
//todo skip now
#if 0
                if ( tBitmap != NULL && tBitmap->iOutLineWidth > 0 && tBitmap->ibuffer )
                {
                    U32 u32DoubleOutLineWidth = tBitmap->iOutLineWidth * 2;
                    S32 s32TempWidth, s32TempHeight;
                    S32 xTempFontStart = 0;
                    S32 yTempFontStart = 0;
                    S32 s32TempY = 0;

                    s32TempY = yDiff - tBitmap->y;

                    xFontStart = xStart + tBitmap->x;
                    yFontStart = yStart + s32TempY;

                    xTempFontStart = xFontStart - tBitmap->iOutLineWidth;
                    yTempFontStart = yFontStart - tBitmap->iOutLineWidth;
                    s32TempWidth = tBitmap->width + u32DoubleOutLineWidth;
                    s32TempHeight = tBitmap->rows + u32DoubleOutLineWidth;

                    MakeRect(&DrawRect, xTempFontStart, yTempFontStart, s32TempWidth, s32TempHeight);   
                    RectIntrsect(&DrawRect, &DrawRect, pCARect);

                    GlyRect.x = (xFontStart < (*pCARect).x) ? ((*pCARect).x - xFontStart) : 0;
                    GlyRect.y = (yFontStart < (*pCARect).y) ? ((*pCARect).y - yFontStart) : 0;
                    GlyRect.w = DrawRect.w;
                    GlyRect.h = DrawRect.h;

                    if (nNumColor > 0)
                    {
                        U8 nColorIdx;

                        nColorIdx = i % nNumColor;

                        ///LOG_TRACE(MLE_LEVEL_GRAPHIC, "[FONT]rand color(%d) index = %d", nNumColor, nColorIdx);
                        nDrawClr=pColors[nColorIdx];
                    }
                    else
                    {
                        nDrawClr=ClrFG;
                    }

                    if ( GlyRect.w > 0 && GlyRect.h > 0 )
                    {
                        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                        BITMAPBASE_BltL8ToBmp(pDst, &DrawRect, tBitmap->ibuffer, tBitmap->iwidth,
                            tBitmap->ipitch, tBitmap->irows, &GlyRect, ClrOL);
                    }

                }//Draw outline
#endif
            }

            nFontCnt += i;

            if ( (S32)(xStart + xOffset) > (*pCARect).x + (*pCARect).w)
            {
                break;
            }
        }
    }

    for (i = 0; i < nFontCnt; i++)
    {
        if ( tfBitmap[i] != NULL && tfBitmap[i]->buffer )
        {
            Rect_t preDrawRect; /// before rect intrsect
            S32 s32TempY = 0;

            s32TempY = yDiff - tfBitmap[i]->y;

            xFontStart = xStart + tfBitmap[i]->x;
            
            yFontStart = yStart + s32TempY;

            MakeRect(&DrawRect, xFontStart, yFontStart,  tfBitmap[i]->width, tfBitmap[i]->rows);

            preDrawRect = DrawRect;
            //RectIntrsect(&DrawRect, &DrawRect, pCARect);

            GlyRect.x = (xFontStart < (*pCARect).x) ? ((*pCARect).x - xFontStart) : 0;
            GlyRect.y = (yFontStart < (*pCARect).y) ? ((*pCARect).y - yFontStart) : 0;
            GlyRect.w = DrawRect.w;
            GlyRect.h = DrawRect.h;

#if 0
            if (nNumColor > 0)
            {
                U8 nColorIdx;

                nColorIdx = i % nNumColor;

                ///LOG_TRACE(MLE_LEVEL_GRAPHIC, "[FONT]rand color(%d) index = %d", nNumColor, nColorIdx);
                ///todo skip now
                //nDrawClr=pColors[nColorIdx];
            }
            else
            {
                ///todo skip now
                //nDrawClr=ClrFG;
            }
#endif
            
            /*   DrawRect = Intersect(preDrawRect, pCARect) 
                **        --> DrawRect's w/h <= preDrawRect's w/h, DrawRect's x/y >= preDrawRect's x/y
                **   if DrawRect's w/h < preDrawRect's w/h means partial update, 
                **   In partial update, font's outline(white color) may be drawn on font area(should be on font outline area)
                **   so that adjustment is needed to to fix the font area which is made dirty by outline draw before.
                **   (first draw is outline, second draw is on font itself, fix first draw at second draw)
                **   There will be 4 cases of partial update Left-Top, Right-Top, Left-Bottom, Right-Bottom intersect with preDrawRect
                **   If partial update are is in the internal of preDrawRect(no intersect), we can consider it as Right-Bottom case.
                **/

            // draw text
            // partical draw        
            if( (preDrawRect.w > DrawRect.w) || (preDrawRect.h > DrawRect.h) ) 
            {
                if( (preDrawRect.x == DrawRect.x) && (preDrawRect.y == DrawRect.y) ) //Left-Top adjust
                {
                    DrawRect.x = xFontStart;
                    DrawRect.y = yFontStart;

                    if ( tfBitmap[i]->width < DrawRect.w )
                    {
                        DrawRect.w = tfBitmap[i]->width; // <-- draw right one more pixel to fix the dirty area which is made by outline before
                    }

                    if ( tfBitmap[i]->rows < DrawRect.h )
                    {
                        DrawRect.h = tfBitmap[i]->rows; // <-- draw down one more pixel to fix the dirty area which is made by outline before
                    }
                }
                else  //Right-Top, Left-Bottom, Right-Bottom adjust
                {
                    S32 _xFontStart, _yFontStart;

                    _xFontStart = xFontStart;
                    _yFontStart = yFontStart;

                    // shift the DrawRect left/up by making a new rect.
                    MakeRect(&DrawRect, _xFontStart, _yFontStart, tfBitmap[i]->width, tfBitmap[i]->rows);

                    // intersect the new rect with CARect
                    RectIntrsect(&DrawRect, &DrawRect, pCARect);

                    GlyRect.x = (_xFontStart < (*pCARect).x)? (*pCARect).x - _xFontStart: 0;
                    GlyRect.y = (_yFontStart < (*pCARect).y)? (*pCARect).y - _yFontStart: 0;
                }
            }
            else // DrawRect totally included in CARect
            {
                DrawRect.x = xFontStart;
                DrawRect.y = yFontStart;

                DrawRect.w = tfBitmap[i]->width;
                DrawRect.h = tfBitmap[i]->rows;
            }

            GlyRect.w = DrawRect.w;
            GlyRect.h = DrawRect.h;

            if ( GlyRect.w > 0 && GlyRect.h > 0 )
            {
#if 0               
                int ii, jj;
                
                TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));             

                for ( ii = 0 ; ii < tfBitmap[i]->rows;  ++ ii)
                {
                    for ( jj = 0 ; jj < tfBitmap[i]->width;  ++ jj)
                    {
                        //  if it has gray>0 we set show it as 1, o otherwise 
                        //printf( " %d " , tfBitmap[i]->buffer[ii * tfBitmap[i]->width + jj] ? 1 : 0 );
                        printf( " %02X " , tfBitmap[i]->buffer[ii * tfBitmap[i]->width + jj] );
                    } 
                    printf( " \n " );
                } 
#endif
                TTF_TRACE(printf("DrawRect x=%d, y=%d, w=%d, h=%d\n", DrawRect.x, DrawRect.y, DrawRect.w, DrawRect.h));
                TTF_TRACE(printf("GlyRect x=%d, y=%d, w=%d, h=%d\n", GlyRect.x, GlyRect.y, GlyRect.w, GlyRect.h));
                //printf("tfBitmap[%d] buffer=%x, w=%d, pitch=%d, rows=%d, nDrawClr=%x\n", i, (U32)tfBitmap[i]->buffer, tfBitmap[i]->width, tfBitmap[i]->pitch, tfBitmap[i]->rows, nDrawClr);
                TTF_TRACE(printf("tfBitmap[%d] buffer=%x, w=%d, pitch=%d, rows=%d\n", i, (U32)tfBitmap[i]->buffer, tfBitmap[i]->width, tfBitmap[i]->pitch, tfBitmap[i]->rows));
                ///BITMAPBASE_BltL8ToBmp(pDst, &DrawRect, tfBitmap[i]->buffer, tfBitmap[i]->width,
                                      ///tfBitmap[i]->pitch, tfBitmap[i]->rows, &GlyRect, nDrawClr);
                                
                GFX_BufferInfo srcbuf;
                GFX_DrawRect bitbltInfo;
#if ( MONO_FONT )
                MS_U32 u32Colorkey= 0x00000000;
                //No alpha

#else
                MS_U32 u32Colorkey= 0x00FF00FF;

                MApi_GFX_SetAlpha(true, COEF_ASRC, ABL_FROM_CONST, (pclrBtn->t_clr >> 24));
#endif
                
                if ( bFontMirror )
                {
                    bitbltInfo.srcblk.x = tfBitmap[i]->width-1;
                    bitbltInfo.dstblk.x = xStart+tfBitmap[nFontCnt-1]->x + tfBitmap[nFontCnt-1]->width -1 - tfBitmap[i]->x - tfBitmap[i]->width+1;
                }
                else
                {
                    bitbltInfo.srcblk.x = 0;
                    bitbltInfo.dstblk.x = DrawRect.x;
                }
                bitbltInfo.srcblk.y = 0;
                bitbltInfo.srcblk.width = tfBitmap[i]->width;
                bitbltInfo.srcblk.height = tfBitmap[i]->rows;
                
                bitbltInfo.dstblk.y = DrawRect.y;
                bitbltInfo.dstblk.width = tfBitmap[i]->width;
                bitbltInfo.dstblk.height = tfBitmap[i]->rows;
                
                if ( (S16)bitbltInfo.dstblk.x < 0 )
                    bitbltInfo.dstblk.x = 0;
                if ( (S16)bitbltInfo.dstblk.y < 0 )
                    bitbltInfo.dstblk.y = 0;

#if ( MONO_FONT )
                srcbuf.u32ColorFmt = GFX_FMT_I1;
#else
                srcbuf.u32ColorFmt = GFX_FMT_I8;
#endif
                srcbuf.u32Addr = _VA2PA((U32)tfBitmap[i]->buffer);
                srcbuf.u32Pitch = (U32)tfBitmap[i]->pitch;
                srcbuf.u32Width = tfBitmap[i]->width;
                srcbuf.u32Height = tfBitmap[i]->rows;

                //Because the address is already cacheable address, so we don't need to convert to cacheable address again
                //MsOS_Dcache_Flush((U32)(((U32)(tfBitmap[i]->buffer) & NON_CACHEABLE_TO_CACHEABLE_MASK) & (~15)),(U32)(((tfBitmap[i]->pitch*tfBitmap[i]->rows)+15) & (~15)));
                MsOS_Dcache_Flush((U32)((U32)(tfBitmap[i]->buffer) & (~15)),(U32)(((tfBitmap[i]->pitch*tfBitmap[i]->rows)+15) & (~15)));

                MApi_GFX_SetSrcBufferInfo(&srcbuf, 0);

                MApi_GFX_SetNearestMode(FALSE); //always enable for color key
                MApi_GFX_SetDither(FALSE);

#if ( MONO_FONT )
                MApi_GFX_SetSrcColorKey(ENABLE, CK_OP_EQUAL, GFX_FMT_I8, &u32Colorkey, &u32Colorkey);
#else
                MApi_GFX_SetSrcColorKey(ENABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555, &u32Colorkey, &u32Colorkey);
#endif
    
                MApi_GFX_BitBlt(&bitbltInfo, GFXDRAW_FLAG_DEFAULT);

#if ( MONO_FONT )
                MApi_GFX_SetSrcColorKey(DISABLE, CK_OP_EQUAL, GFX_FMT_I8, &u32Colorkey, &u32Colorkey);
#else
                //MApi_GFX_SetSrcColorKey(DISABLE, CK_OP_EQUAL, GFX_FMT_ARGB8888,  NULL, NULL);
                MApi_GFX_SetSrcColorKey(DISABLE, CK_OP_EQUAL, GFX_FMT_ARGB1555,  &u32Colorkey, &u32Colorkey);
#endif

                //In this case, OSD bitmaps are decompressed dynamicly. 
                //If we don't flush GE at this point, while GE is doing bitblt, its source buffer maybe overwritten by next turn OSD bitmaps decompression.
                //We move this operation to just after font buffer is allocated, to increase performance
                //It still not safe to put there, so do GFX flush queue here
                MApi_GFX_FlushQueue();
                
                //m_pu8PreBuffer = tfBitmap[i]->buffer;
            }
        }

        msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(tfBitmap[i]);
    }
    if (tfBitmap)
        FREE(tfBitmap);

///todo skip now
#if 0
    if ( nType & FONT_TYPE_UNDERLINE )
    {
        S32 xLen;
        S32 zoomedHeight;
        if ( xStart < (*pCARect).x )
        {
            xStart = (*pCARect).x;
        }

        if ( (DrawRect.x+DrawRect.w) >= (*pCARect).x + (*pCARect).w )
        {
            xLen = (*pCARect).x + (*pCARect).w - xStart;
        }
        else
        {
            xLen = (DrawRect.x+DrawRect.w) - xStart;
        }

        zoomedHeight = msAPI_MLE_FONTBASE_VectorFontZoomValue(sFaceInf.height);
        if ((yStart + zoomedHeight > (*pCARect).y) && (yStart + zoomedHeight <= (*pCARect).y+(*pCARect).h) && (xLen > 0) )
        {
            BITMAPBASE_DrawHLine(pDst,
                                 xStart,
                                 yStart + msAPI_MLE_FONTBASE_VectorFontZoomValue(sFaceInf.height) - 1,
                                 xLen,
                                 ClrFG,
                                 ROP_COPYSRC);
        }
    }
#endif
    
    return MLE_RET_SUCCESS;

}

MLE_Ret msAPI_MLE_FONTBASE_Vector_GetInfo(U32 nFontSize,           // Font Size to query
                                U32 Type,
                                FontInfo *pinfo)
{
    MLE_Ret error = MLE_RET_SUCCESS;

    TTF_FaceInf sFaceInf = {0, 0, 0, 0, 0};

    error = msAPI_MLE_FONTBASE_VectorFontGetFaceInf(&sFaceInf, nFontSize);    
    if ( error != MLE_RET_SUCCESS ) 
    {
        //LOG_ERROR(MAE_LEVEL_GRAPHIC, "_GetInfo_VectorFont error(%d)", error);       
        return MLE_RET_FAILED;
    }

    //pinfo->nHeight = msAPI_MLE_FONTBASE_VectorFontZoomValue(sFaceInf.height);
    pinfo->nHeight = msAPI_MLE_FONTBASE_VectorFontZoomValue(sFaceInf.ascender-sFaceInf.descender);
    pinfo->nAscent = msAPI_MLE_FONTBASE_VectorFontZoomValue(sFaceInf.ascender);
    pinfo->nDescent = msAPI_MLE_FONTBASE_VectorFontZoomValue((sFaceInf.descender) * (-1));

    if (Type & FONT_TYPE_OUTLINE)
    {
        pinfo->nHeight += OUTLINE_PIXEL*2;
        pinfo->nAscent += OUTLINE_PIXEL;
        pinfo->nDescent += OUTLINE_PIXEL;
    }

    return MLE_RET_SUCCESS;
}

#ifdef __INDIC_FONT_RULE_CACHE__
void msAPI_MLE_FONTBASE_Vector_InsertHindiCache(U32 u32Offset, U16* pau16Cluster, U16 u16ClusterLen, U16 *pu16OutCode, U16 u16OutCodeLen, U32 *pau32Consumed, U32 u32Features)
{
    unsigned int nHashKey = 0, nHashKeyVerify = 0;
    U16 u16DataSize = 0;
    S32 s32TotalSize = 0;
    U16 u16Comsume = 0;
    U32 *pConsumed = NULL;
    BOOLEAN bNeedRelease = FALSE;

    if(u32Offset != 0 || pau16Cluster == NULL || u16ClusterLen <2 || u16ClusterLen>5)
    {
        return;
    }


    /*if(_g_nHindiCacheHead + 1000 > _g_nHindiCacheSize)
    {
        return;
    }*/

    //calculate consume size
    pConsumed = pau32Consumed;
    for(u16Comsume=0; u16Comsume<MAX_CODE_COUNT; u16Comsume++)
    {
        if((*pConsumed) == 0)
        {
            break;
        }
        pConsumed++;
    }

    u16DataSize = sizeof(nHashKeyVerify) + sizeof(u16OutCodeLen)+ u16OutCodeLen * sizeof(MLE_WChar) + sizeof(u16Comsume) + u16Comsume*sizeof(U32)+ sizeof(u32Features);
    s32TotalSize = u16DataSize+sizeof(nHashKey)+sizeof(u16DataSize);
    // remove oldest data
    do 
    {
        bNeedRelease = FALSE;

        // check if exist enough cache memory
        if(_g_nHindiCacheHead > _g_nHindiCacheTail)
        {
            if(_g_nHindiCacheHead+s32TotalSize > _g_nHindiCacheSize)
            {
                bNeedRelease = TRUE;
                _g_nHindiCacheLast = _g_nHindiCacheHead;
                _g_nHindiCacheHead = 0;
            }
        }
        else if (_g_nHindiCacheHead == _g_nHindiCacheTail)
        {
            if(msAPI_COMMON_hashtable_size(_g_pHindiCacheTable) > 0)
                bNeedRelease = TRUE;
        }
        else // _g_nFontCacheHead < _g_nFontCacheTail
        {
            if(_g_nHindiCacheTail - _g_nHindiCacheHead < (S32)(u16DataSize+sizeof(nHashKey)+sizeof(u16DataSize)))
                bNeedRelease = TRUE;
        }

        // release the oldest font in cache
        if(bNeedRelease)
        {
            U16 u16tmpDataSize = 0;
            MEMCPY(&nHashKey, (_g_pHindiCacheData+_g_nHindiCacheTail), sizeof(nHashKey));
            MEMCPY(&u16tmpDataSize, (_g_pHindiCacheData+_g_nHindiCacheTail+sizeof(nHashKey)), sizeof(u16tmpDataSize));
            msAPI_COMMON_hashtable_remove(_g_pHindiCacheTable, (void*)nHashKey);
            _g_nHindiCacheTail += sizeof(nHashKey) + sizeof(u16tmpDataSize) + u16tmpDataSize;
            if(_g_nHindiCacheTail >= _g_nHindiCacheLast)
                _g_nHindiCacheTail = 0;
        }
    } while (bNeedRelease);

    //set nHashKey at head
    nHashKey = msAPI_COMMON_hashtable_wstr_int((void*)pau16Cluster, u16ClusterLen);
    nHashKeyVerify = msAPI_COMMON_hashtable_wstr_inverse_int((void*)pau16Cluster, u16ClusterLen);
    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, &nHashKey, sizeof(nHashKey));
    _g_nHindiCacheHead += sizeof(nHashKey);

    //set u16DataSize at head
    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, &u16DataSize, sizeof(u16DataSize));
    _g_nHindiCacheHead += sizeof(u16DataSize);

    if ( msAPI_COMMON_hashtable_insert(_g_pHindiCacheTable, (void*)nHashKey, (void*)(_g_pHindiCacheData+_g_nHindiCacheHead)) == 0 )
    {
        _g_nHindiCacheHead -= sizeof(u16DataSize);
        _g_nHindiCacheHead -= sizeof(nHashKey);
        return;
    }

    //set Data at head
    MEMSET(_g_pHindiCacheData+_g_nHindiCacheHead, 0, u16DataSize);

    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, &nHashKeyVerify, sizeof(nHashKeyVerify));
    _g_nHindiCacheHead += sizeof(nHashKeyVerify);
    
    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, &u16OutCodeLen, sizeof(u16OutCodeLen));
    _g_nHindiCacheHead += sizeof(u16OutCodeLen);

    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, &u16Comsume, sizeof(u16Comsume));
    _g_nHindiCacheHead += sizeof(u16Comsume);

    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, &u32Features, sizeof(u32Features));
    _g_nHindiCacheHead += sizeof(u32Features);

    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, (void*)pau32Consumed, u16Comsume * sizeof(U32));
    _g_nHindiCacheHead += u16Comsume*sizeof(U32);

    MEMCPY(_g_pHindiCacheData+_g_nHindiCacheHead, (void*)pu16OutCode, u16OutCodeLen*sizeof(MLE_WChar));
    _g_nHindiCacheHead += u16OutCodeLen*sizeof(MLE_WChar);

}

void* msAPI_MLE_FONTBASE_Vector_SearchHindiCache(U16 *pu16Cluster, U16 u16CluserSize, U32 u32Features, BOOLEAN *bKeyDuplicate)
{
    void *pResult = NULL;
    U8 *pu8Result = NULL;
    unsigned int nKey = 0, nHashKeyVerify = 0, nHashKeyVerify_input;
    U32 u32VerifyFeature = 0;
    *bKeyDuplicate = FALSE;
    if(pu16Cluster !=NULL && u16CluserSize !=0)
    {
        nKey = msAPI_COMMON_hashtable_wstr_int(pu16Cluster, u16CluserSize);
        pResult = msAPI_COMMON_hashtable_search(_g_pHindiCacheTable, (void*)nKey);
        if ( pResult != NULL )
        {
            nHashKeyVerify_input = msAPI_COMMON_hashtable_wstr_inverse_int(pu16Cluster, u16CluserSize);
            MEMCPY((void*)&nHashKeyVerify, pResult, sizeof(nHashKeyVerify));
            if ( nHashKeyVerify_input == nHashKeyVerify )
            {
                pu8Result = (U8 *)pResult;
                pu8Result += sizeof(nHashKeyVerify);

                MEMCPY((void *)&u32VerifyFeature, (pu8Result + sizeof(U16) + sizeof(U16)), sizeof(U32));
                if ( u32Features == u32VerifyFeature )
                {
                    pResult = (void *)pu8Result;
                }
                else
                {
                    pResult = NULL;
                    *bKeyDuplicate = TRUE;
                }
            }
            else
            {
                pResult = NULL;
                *bKeyDuplicate = TRUE;
            }
        }
    }
    return pResult;
}
#endif //__INDIC_FONT_RULE_CACHE__

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MLE_FONT_VECTOR_C__
