////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __API_OPCACHE_H__
#define __API_OPCACHE_H__

#include "msAPI_CI.h"
#include "msAPI_MW_GlobalSt.h"

/// macro of printf of fatal error message
#define MW_DTV_CI_OPCACHE_DB_FATAL(fmt, arg...)          printf((char *)fmt, ##arg)
/// macro of printf of error message
#define MW_DTV_CI_OPCACHE_DB_ERROR(fmt, arg...)          printf((char *)fmt, ##arg)
/// macro of printf of warning message
#define MW_DTV_CI_OPCACHE_DB_WARNING(fmt, arg...)        printf((char *)fmt, ##arg)
/// macro of printf of info message
#define MW_DTV_CI_OPCACHE_DB_INFO(fmt, arg...)           printf((char *)fmt, ##arg)
/// macro of printf of function entry message
#define MW_DTV_CI_OPCACHE_DB_FUNCTION(fmt, arg...)       // printf((char *)fmt, ##arg)
/// macro of printf of debug message
#define MW_DTV_CI_OPCACHE_DB_DBG(fmt, arg...)            // printf((char *)fmt, ##arg)

/// the maximum op profile name
#define MAX_PROFILE_NAME	(OP_MAX_PROFILE_NAME_SIZE+3)
/// the maximum op nit size
#define MAX_CAM_NIT_SIZE	(1024*63) //63K
/// max op cache number
#define MAX_OP_CACHE_NUM    7

typedef enum
{
    /// op info cache
    E_OPCACHE_INFO,
    /// op cam nit cache
    E_OPCACHE_CAMNIT
} E_OPCACHE_DATA_TYPE;


///to record the triple id
typedef struct
{
    U16 u16OnId;
    U16 u16TsId;
    U16 u16SrvId;
}ST_TRIPLE_ID;

/// op info cache
typedef struct
{
    /// check sum
    U32 u32CheckSum;
    /// op cam id
    U32 u32ID;
    /// op info
    CI_OP_INFO stCiOpInfo;
    /// op nit version
    U8 u8NitVersion;
    /// delivery system type
    EN_DELIVERY_SYS_TYPE eDtvSystemType;
    /// triple id
    ST_TRIPLE_ID stCurProgTripleID; //ONID,TSID,SID
    /// TRUE : used , FALSE: free
    BOOLEAN bUsed;

} MW_OPCACHE_INFO;
/// op nit cache
typedef struct
{
    /// check sum
    U32 u32CheckSum;
    /// op cam id
    U32 u32ID;
    /// op nit section count
    U16 u16SecCount;
    /// op nit
    U8 au8CamNIT[MAX_CAM_NIT_SIZE]; // 1024*64

} MW_OPCACHE_CAMNIT;

/// op cache
typedef struct
{
    /// op info
    MW_OPCACHE_INFO stOpCacheInfo;
    /// op cam nit
    MW_OPCACHE_CAMNIT stOpCamNIT;
} MW_OPCACHE_SAVE;


#ifdef API_OPCACHE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/

//------------------------------------------------------------------------------
// Public functions.
//------------------------------------------------------------------------------
// ------------------------------------------------------------
/// Op Init
/// @return
// -----------------------------------------------------------
INTERFACE void msAPI_OP_OpCacheInit(void);

// ------------------------------------------------------------
/// delete op cache Information from op cache db by cicam identifier
/// @param  u32CicamId     \b IN: cicam identifier
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_DeleteByCicamId(U32 u32CicamId);

// ------------------------------------------------------------
/// delete op cache Information from op cache db by index
/// @param  u8Index    \b IN: index
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_DeleteByIndex(U8 u8Index);

// ------------------------------------------------------------
/// Reset op cache db and storage data
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_Reset (void);

// ------------------------------------------------------------
/// get op cache Info from op cache db by index
/// @param  u8Index     \b IN: u8Index
/// @param  stOpCacheInfo     \b OUT: op cache info
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_GetOpCacheInfoByIndex(U8 u8Index , MW_OPCACHE_INFO *stOpCacheInfo);

// ------------------------------------------------------------
/// get op cache Info from op cache db by cicam identifier
/// @param  u32CicamId     \b IN: cicam identifier
/// @param  stOpCacheInfo     \b OUT: op cache info
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_GetOpCacheInfoByCicamId(U32 u32CicamId, MW_OPCACHE_INFO *stOpCacheInfo);

// ------------------------------------------------------------
/// get op profile name from op cache db by index
/// @param  u8Index     \b IN: index
/// @param  pu8Name     \b OUT:  profile name
/// @param  u16NameLen     \b In:  profile name max length
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_GetOpProfileNameByIndex(U8 u8Index, U8 *pu8Name, U16 u16MaxNameLen);

// ------------------------------------------------------------
/// get op dtv system type from op cache db by index
/// @param  u8Index     \b IN: index
/// @param  eDtvSysType     \b OUT:  dtv system type
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_GetOpDtvSysTypeByIndex(U8 u8Index, EN_DELIVERY_SYS_TYPE *eDtvSysType);

// ------------------------------------------------------------
/// get op iso 639 langcode by cicam identifier
/// @param  u32CicamId     \b IN: cicam identifier
/// @param  pu8Iso639LangCode     \b OUT:  iso 639 langcode
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_GetOpIso639LangCodeByCicamId(U32 u32CicamId, U8 *pu8Iso639LangCode);

// ------------------------------------------------------------
/// set char table code
/// @param  pu8SrcString     \b IN:  source string
/// @param  u8SrtLen     \b IN: length
/// @param  pu8DstString     \b OUT:  output string
/// @param  u8DstLen     \b IN: max length
/// @param  u8CharCodeTable     \b IN: char code table
/// @param  u8EncodeTypeId     \b IN: encode type id
/// @param  u8SecondByte     \b IN:  secondary byte
/// @param  u8ThirdByte     \b IN: third byte
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_SetCharCodeTable(const U8 *pu8SrcString, U8 u8SrtLen, U8 *pu8DstString, U8 u8DstLen, U8 u8CharCodeTable, U8 u8EncodeTypeId, U8 u8SecondByte, U8 u8ThirdByte);


// ------------------------------------------------------------
/// set op current program tripleId to op cache db by cicam identifier
/// @param  u32CicamId     \b IN: cicam identifier
/// @param  stTripleId     \b IN: op cache info current program tripleId
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_SetCurr(U32 u32CicamId, const ST_TRIPLE_ID *stTripleId);

// ------------------------------------------------------------
/// get op current program tripleId from op cache db by cicam identifier
/// @param  u32CicamId     \b IN: op cache cicam identifier
/// @param  stTripleId     \b OUT: op cache current program tripleId
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_GetCurr(U32 u32CicamId, ST_TRIPLE_ID *stTripleId);

// ------------------------------------------------------------
/// get op cache count
/// @return             \b  return op cache count
// -----------------------------------------------------------
INTERFACE U8 msAPI_OP_GetOpCacheCount(void);

// ------------------------------------------------------------
/// check op cache count reach max cache number
/// @return   \b  return TRUE : reach max number or FALSE : less max number
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_IsOpCountReachMaxNum(void);

// ------------------------------------------------------------
/// get cahce nit data from storage
/// @param  u32ID     \b IN: cache ID
/// @param  pstOpCacheCamNIT     \b OUT: op cache nit data
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_GetStorageCacheCamNIT(U32 u32ID, MW_OPCACHE_CAMNIT *pstOpCacheCamNIT);

// ------------------------------------------------------------
/// update ci op info
/// @param  stCiOpInfo     \b IN: ci op info
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_UpdateCIOpInfo(const CI_OP_INFO *stCiOpInfo);

// ------------------------------------------------------------
/// update ci op info
/// @param  u32CicamId     \b IN: cicam identifier
/// @param  pu8NitSection     \b IN: point of nit section data
/// @param  u16SecLen     \b IN: total section length
/// @param  u16SecCount     \b IN: section count
/// @param  eDtvSystemType     \b IN: nit delivery system type
/// @return             \b  return TRUE : success or FALSE : failure
// -----------------------------------------------------------
INTERFACE BOOLEAN msAPI_OP_UpdateCICamNIT(U32 u32CicamId, U8 *pu8NitSection, U16 u16SecLen, U16 u16SecCount, EN_DELIVERY_SYS_TYPE eDtvSystemType);

#if (ENABLE_CI_PLUS_V1_4)
INTERFACE BOOLEAN msAPI_Virtual_CH_WriteDataToFlash(U8 *pu8Data);
#endif

#undef INTERFACE
#endif // __API_DTVSYSTEM_H__

