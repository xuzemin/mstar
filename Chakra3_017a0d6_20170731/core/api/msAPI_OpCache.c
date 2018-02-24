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
////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_DTVSystem.h
/// This file includes MStar DTV system application interface
/// @brief API for DTV control
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define API_OPCACHE_C

#include "Board.h"

#if(ENABLE_CI_PLUS)

#include <stddef.h>
#include <string.h>
#include "sysinfo.h"
#include "debug.h"

#include "drvSERFLASH.h"

//#include "msAPI_Memory.h"
#include "msAPI_Flash.h"
//#include "MsOS.h"
#include "msAPI_OpCache.h"
#include "MApp_SaveData.h"
#include "mapp_si_if.h"
#include "msAPI_CI.h"
//#include "msAPI_DTVSystem.h"
//#include "mapp_si.h"
//------------------------------------------------------------------------------
// Local defines
//------------------------------------------------------------------------------
#define DEFAULT_CICAM_NIT_VERSION 0xFF
#define CI_COMPRESS_CTRL_CODE   0x1F
#define CI_ISO_8859_TABLE_CODE  0x10

//------------------------------------------------------------------------------
// functions.
//------------------------------------------------------------------------------
static BOOLEAN msAPI_OP_Load(U32 u32ID);
static U32 msAPI_OP_CalCheckSum(U8 *pBuf, U32 u32BufLen);
static BOOLEAN msAPI_OP_Add(void *pu8CacheData, E_OPCACHE_DATA_TYPE eUpdateType);
static BOOLEAN msAPI_OP_Save(void *pu8CacheData, E_OPCACHE_DATA_TYPE eUpdateType);
static BOOLEAN msAPI_OP_GetStorageCacheInfo(U32 u32ID, MW_OPCACHE_INFO *pstOpCacheInfo);
static BOOLEAN msAPI_OP_WriteDataToFlash(U32 u32ID, U8 *pu8Data, E_OPCACHE_DATA_TYPE eType);
static BOOLEAN msAPI_OP_ReadDataFromFlash(U32 u32ID, U8 *pu8Data, E_OPCACHE_DATA_TYPE eType);

//------------------------------------------------------------------------------
// Variable.
//------------------------------------------------------------------------------
static MW_OPCACHE_INFO _stOpCacheInfo[MAX_OP_CACHE_NUM];
/// op cache data type

//------------------------------------------------------------------------------

#if (ENABLE_CI_PLUS_V1_4)
BOOLEAN msAPI_Virtual_CH_WriteDataToFlash(U8 *pu8Data)
{
    BOOLEAN IsWriteFlashDone = FALSE;
    CIPLUS_Virtual_SERVICE_DATA stVirtualChannel;
    U8 *temp =  NULL;

    memcpy(&stVirtualChannel, pu8Data, sizeof(CIPLUS_Virtual_SERVICE_DATA));

    temp = (U8*)_PA2VA(((CI_VIRTUAL_CH_BUF_MEMORY_TYPE & MIU1) ? (CI_VIRTUAL_CH_BUF_ADR | MIU_INTERVAL) : (CI_VIRTUAL_CH_BUF_ADR)));

    memcpy(temp,&stVirtualChannel,sizeof(CIPLUS_Virtual_SERVICE_DATA));
    MApp_SaveCIVirtualChannel(CIPLUS_1_4_BANK_VIRTUAL_CHANNEL_START, CIPLUS_1_4_BANK_VIRTUAL_CHANNEL_COUNT, &IsWriteFlashDone);

    if (IsWriteFlashDone)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}


BOOLEAN msAPI_Virtual_CH_ReadDataFromFlash(U8 *pu8Data)
{
    U8 *tempptr = (U8*)_PA2VA(((CI_VIRTUAL_CH_BUF_MEMORY_TYPE & MIU1) ? (CI_VIRTUAL_CH_BUF_ADR | MIU_INTERVAL) : (CI_VIRTUAL_CH_BUF_ADR)));
    CIPLUS_Virtual_SERVICE_DATA stVirtualChannel;
    if(MDrv_FLASH_Read(SYSTEM_BANK_SIZE*CIPLUS_1_4_BANK_VIRTUAL_CHANNEL_START, SYSTEM_BANK_SIZE, tempptr))
    {
         memcpy(&stVirtualChannel,tempptr,sizeof(CIPLUS_Virtual_SERVICE_DATA));
         memcpy(pu8Data,&stVirtualChannel,sizeof(CIPLUS_Virtual_SERVICE_DATA));
         return TRUE;
    }
    return FALSE;
}

#endif


void msAPI_OP_OpCacheInit(void)
{
    U32 i;

    // Load OP Cache Info
    for(i = 0; i < MAX_OP_CACHE_NUM; i++)
    {
        memset(&_stOpCacheInfo[i], 0, sizeof(MW_OPCACHE_INFO));
        _stOpCacheInfo[i].u32ID = i;
        _stOpCacheInfo[i].bUsed = FALSE;
        _stOpCacheInfo[i].u8NitVersion = SI_INVALID_PSI_SI_VERSION;
        _stOpCacheInfo[i].eDtvSystemType = E_DELIVERY_SYS_NONE;
        _stOpCacheInfo[i].stCurProgTripleID.u16OnId = SI_INVALID_ON_ID;
        _stOpCacheInfo[i].stCurProgTripleID.u16TsId = SI_INVALID_TS_ID;
        _stOpCacheInfo[i].stCurProgTripleID.u16SrvId = SI_INVALID_SERVICE_ID;
        if(msAPI_OP_Load(i) == FALSE)
        {
            //MW_DTV_CI_OPCACHE_DB_ERROR("OP Cache DB Load error, reset OP Cache DB\n");
            msAPI_OP_Reset();
            break;
        }
    }
}

static BOOLEAN msAPI_OP_Add(void *pu8CacheData, E_OPCACHE_DATA_TYPE eUpdateType)
{
    U32 i;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(pu8CacheData == NULL)
    {
        return FALSE;
    }

    switch(eUpdateType)
    {
        case E_OPCACHE_INFO:
        {
            MW_OPCACHE_INFO stOpCacheInfo;

            for(i = 0; i < MAX_OP_CACHE_NUM; i++)
            {
                if(_stOpCacheInfo[i].bUsed == FALSE)
                {
                    break;
                }
            }

            if(i >= MAX_OP_CACHE_NUM)
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d No free to add op cache\n",__FUNCTION__,__LINE__);
                return FALSE;
            }

            memset(&stOpCacheInfo, 0, sizeof(MW_OPCACHE_INFO));
            memcpy(&stOpCacheInfo, pu8CacheData, sizeof(MW_OPCACHE_INFO));
            stOpCacheInfo.u32ID = i;
            MW_DTV_CI_OPCACHE_DB_DBG("stOpCacheInfo.u32ID %d, %d\n",stOpCacheInfo.u32ID,i);
            if(TRUE == msAPI_OP_Save((void *)&stOpCacheInfo, E_OPCACHE_INFO))
            {
                memcpy(&_stOpCacheInfo[i], &stOpCacheInfo, sizeof(MW_OPCACHE_INFO));
                MW_DTV_CI_OPCACHE_DB_DBG("_stOpCacheInfo[%d] %d\n",i,_stOpCacheInfo[i].bUsed);
            }
            break;
        }
        case E_OPCACHE_CAMNIT:
        {
            MW_OPCACHE_CAMNIT *pstOpCacheCamNIT = (MW_OPCACHE_CAMNIT *)pu8CacheData;

            if(pstOpCacheCamNIT->u32ID >= MAX_OP_CACHE_NUM)
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d Invalid ID to add op cache\n",__FUNCTION__,__LINE__);
                return FALSE;
            }
            msAPI_OP_Save((void *)pstOpCacheCamNIT, E_OPCACHE_CAMNIT);
            break;
        }

        default:
            break;
    }

    return TRUE;
}

static BOOLEAN msAPI_OP_Save(void *pu8CacheData, E_OPCACHE_DATA_TYPE eUpdateType)
{
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,eUpdateType);

    if(pu8CacheData == NULL)
    {
        return FALSE;
    }

    switch(eUpdateType)
    {
        case E_OPCACHE_INFO:
        {
            MW_OPCACHE_INFO *pstOpCacheInfo = (MW_OPCACHE_INFO *)pu8CacheData;
            pstOpCacheInfo->u32CheckSum = msAPI_OP_CalCheckSum((U8 *)pstOpCacheInfo, sizeof(MW_OPCACHE_INFO));
            if(msAPI_OP_WriteDataToFlash(pstOpCacheInfo->u32ID, (U8 *)pstOpCacheInfo, E_OPCACHE_INFO) == FALSE)
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d, write data fail.\n", __FUNCTION__,__LINE__);
                return FALSE;
            }
            break;
        }

        case E_OPCACHE_CAMNIT:
        {
            MW_OPCACHE_CAMNIT *pstCacheCamNIT = (MW_OPCACHE_CAMNIT *)pu8CacheData;

            MW_DTV_CI_OPCACHE_DB_DBG("u32ID:> %ld\n",pstCacheCamNIT->u32ID);
            MW_DTV_CI_OPCACHE_DB_DBG("u16SecCount:> %d\n",pstCacheCamNIT->u16SecCount);
            pstCacheCamNIT->u32CheckSum = msAPI_OP_CalCheckSum((U8 *)pstCacheCamNIT, sizeof(MW_OPCACHE_CAMNIT));
            MW_DTV_CI_OPCACHE_DB_ERROR("pstCacheCamNIT->u32CheckSum  0x%lx\n",pstCacheCamNIT->u32CheckSum);
            if(msAPI_OP_WriteDataToFlash(pstCacheCamNIT->u32ID, (U8 *)pstCacheCamNIT, E_OPCACHE_CAMNIT) == FALSE)
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d, write data fail.\n", __FUNCTION__,__LINE__);
                return FALSE;
            }

            break;
        }

        default:
            break;
    }

    return TRUE;
}

BOOLEAN msAPI_OP_DeleteByCicamId(U32 u32CicamId)
{
    U32 i = 0;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    for(i = 0; i < MAX_OP_CACHE_NUM; i++)
    {
        if((_stOpCacheInfo[i].bUsed == TRUE)&&(_stOpCacheInfo[i].stCiOpInfo.u32CicamIdentifier == u32CicamId))
        {
            return msAPI_OP_DeleteByIndex(i);
        }
    }
    MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d,delete op cache db fail.\n", __FUNCTION__,__LINE__);
    return FALSE;
}

BOOLEAN msAPI_OP_DeleteByIndex(U8 u8Index)
{
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(u8Index >= MAX_OP_CACHE_NUM)
    {
        return FALSE;
    }
    memset(&_stOpCacheInfo[u8Index], 0, sizeof(MW_OPCACHE_INFO));
    _stOpCacheInfo[u8Index].u32ID = u8Index;
    _stOpCacheInfo[u8Index].bUsed = FALSE;
    _stOpCacheInfo[u8Index].u8NitVersion = SI_INVALID_PSI_SI_VERSION;
    _stOpCacheInfo[u8Index].eDtvSystemType = E_DELIVERY_SYS_NONE;
    _stOpCacheInfo[u8Index].stCurProgTripleID.u16OnId = SI_INVALID_ON_ID;
    _stOpCacheInfo[u8Index].stCurProgTripleID.u16TsId = SI_INVALID_TS_ID;
    _stOpCacheInfo[u8Index].stCurProgTripleID.u16SrvId = SI_INVALID_SERVICE_ID;
    msAPI_OP_Save((void *)&_stOpCacheInfo[u8Index], E_OPCACHE_INFO);

    return TRUE;
}

BOOLEAN msAPI_OP_Reset (void)
{
    U32 i = 0;
    MW_OPCACHE_CAMNIT *pstOpCacheCamNIT;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    pstOpCacheCamNIT = (MW_OPCACHE_CAMNIT *)malloc(sizeof(MW_OPCACHE_CAMNIT));
    for(i = 0; i < MAX_OP_CACHE_NUM; i++)
    {
        memset(&_stOpCacheInfo[i], 0, sizeof(MW_OPCACHE_INFO));
        _stOpCacheInfo[i].u32ID = i;
        _stOpCacheInfo[i].bUsed = FALSE;
        _stOpCacheInfo[i].u8NitVersion = SI_INVALID_PSI_SI_VERSION;
        _stOpCacheInfo[i].eDtvSystemType = E_DELIVERY_SYS_NONE;
        _stOpCacheInfo[i].stCurProgTripleID.u16OnId = SI_INVALID_ON_ID;
        _stOpCacheInfo[i].stCurProgTripleID.u16TsId = SI_INVALID_TS_ID;
        _stOpCacheInfo[i].stCurProgTripleID.u16SrvId = SI_INVALID_SERVICE_ID;
        msAPI_OP_WriteDataToFlash(i, (U8 *)&_stOpCacheInfo[i], E_OPCACHE_INFO);
        if(pstOpCacheCamNIT != NULL)
        {
            memset(pstOpCacheCamNIT, 0, sizeof(MW_OPCACHE_CAMNIT));
            msAPI_OP_WriteDataToFlash(i, (U8 *)pstOpCacheCamNIT, E_OPCACHE_CAMNIT);
        }
    }

    if(pstOpCacheCamNIT != NULL)    //Fix coverity 207449 for memory leak
    {
        free(pstOpCacheCamNIT);
        pstOpCacheCamNIT = NULL;
    }
    // CAM NIT need clear ?
    // write flash
    return TRUE;
}

BOOLEAN msAPI_OP_GetOpCacheInfoByIndex(U8 u8Index , MW_OPCACHE_INFO *stOpCacheInfo)
{
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(u8Index >= MAX_OP_CACHE_NUM)
    {
        return FALSE;
    }
    if((_stOpCacheInfo[u8Index].bUsed == FALSE) || (stOpCacheInfo == NULL))
    {
        return FALSE;
    }
    memcpy(stOpCacheInfo, &_stOpCacheInfo[u8Index], sizeof(MW_OPCACHE_INFO));
    return TRUE;
}

BOOLEAN msAPI_OP_GetOpCacheInfoByCicamId(U32 u32CicamId, MW_OPCACHE_INFO *stOpCacheInfo)
{
    U32 i;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);
    if(stOpCacheInfo == NULL)
    {
        return FALSE;
    }
    for(i = 0; i < MAX_OP_CACHE_NUM; i++)
    {
        if((_stOpCacheInfo[i].bUsed == TRUE)&&(_stOpCacheInfo[i].stCiOpInfo.u32CicamIdentifier == u32CicamId))
        {
            memcpy(stOpCacheInfo, &_stOpCacheInfo[i], sizeof(MW_OPCACHE_INFO));
            return TRUE;
        }
    }
    return FALSE;
}

BOOLEAN msAPI_OP_GetOpProfileNameByIndex(U8 u8Index, U8 *pu8Name, U16 u16MaxNameLen)
{
    U8 u8CharacterCodeTable;
    U8 u8EncodingTypeID;
    U8 u8SecondByteValue;
    U8 u8ThirdByteValue;
    U8 au8Buf[MAX_PROFILE_NAME];
    U8 u8ProfileNameLen;
    MW_OPCACHE_INFO stOpCacheInfo;

    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(pu8Name == NULL)
    {
        return FALSE;
    }
    memset(&stOpCacheInfo, 0, sizeof(MW_OPCACHE_INFO));
    if(FALSE == msAPI_OP_GetOpCacheInfoByIndex(u8Index, &stOpCacheInfo))
    {
        return FALSE;
    }

    memset(au8Buf, 0, MAX_PROFILE_NAME);

    u8CharacterCodeTable = stOpCacheInfo.stCiOpInfo.u8CharacterCodeTable;
    u8EncodingTypeID = stOpCacheInfo.stCiOpInfo.u8EncodingTypeID;
    u8SecondByteValue = stOpCacheInfo.stCiOpInfo.u8SecondByteValue;
    u8ThirdByteValue = stOpCacheInfo.stCiOpInfo.u8ThirdByteValue;
    u8ProfileNameLen = stOpCacheInfo.stCiOpInfo.u8ProfileNameLen;

    if(TRUE == msAPI_OP_SetCharCodeTable(stOpCacheInfo.stCiOpInfo.au8ProfileName, u8ProfileNameLen, au8Buf, MAX_PROFILE_NAME, u8CharacterCodeTable, u8EncodingTypeID, u8SecondByteValue, u8ThirdByteValue))
    {
        memcpy(pu8Name, au8Buf, (MAX_PROFILE_NAME > u16MaxNameLen) ? u16MaxNameLen : MAX_PROFILE_NAME);
    }
    else
    {
        memcpy(pu8Name, stOpCacheInfo.stCiOpInfo.au8ProfileName, (u8ProfileNameLen > u16MaxNameLen) ? u16MaxNameLen : u8ProfileNameLen);
    }

    return TRUE;
}

BOOLEAN msAPI_OP_GetOpDtvSysTypeByIndex(U8 u8Index, EN_DELIVERY_SYS_TYPE *eDtvSysType)
{
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(u8Index >= MAX_OP_CACHE_NUM)
    {
        return FALSE;
    }
    if((_stOpCacheInfo[u8Index].bUsed == FALSE) || (eDtvSysType == NULL))
    {
        return FALSE;
    }
    *eDtvSysType = _stOpCacheInfo[u8Index].eDtvSystemType;

    return TRUE;
}

BOOLEAN msAPI_OP_GetOpIso639LangCodeByCicamId(U32 u32CicamId, U8 *pu8Iso639LangCode)
{
    MW_OPCACHE_INFO stOpCacheInfo;

    if(pu8Iso639LangCode == NULL)
    {
        return  FALSE;
    }
    if(TRUE == msAPI_OP_GetOpCacheInfoByCicamId(u32CicamId, &stOpCacheInfo))
    {
        if(pu8Iso639LangCode != NULL)
        {
            memcpy(pu8Iso639LangCode, stOpCacheInfo.stCiOpInfo.u8aISO639LanguageCode, 3);
            return TRUE;
        }

    }

    return  FALSE;
}

BOOLEAN msAPI_OP_SetCharCodeTable(const U8 *pu8SrcString, U8 u8SrtLen, U8 *pu8DstString, U8 u8DstLen, U8 u8CharCodeTable, U8 u8EncodeTypeId, U8 u8SecondByte, U8 u8ThirdByte)
{
    U8 *pBuff = NULL;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if((pu8SrcString == NULL) || (pu8DstString == NULL) || (u8SrtLen == 0) || (u8DstLen < 4))
    {
        return FALSE;
    }

    if((pu8SrcString[0] > 0) && (pu8SrcString[0] < 0x1F)) // character code table is exist
    {
        return FALSE;
    }

    if((u8CharCodeTable <= 0) || (u8CharCodeTable > 0x1F)) // character code table is invalid
    {
        return FALSE;
    }

    pBuff = (U8 *)malloc(sizeof(U8)*u8DstLen);
    if(pBuff == NULL)
    {
        return FALSE;
    }

    memset(pBuff, 0, u8DstLen);
    if(u8CharCodeTable == CI_COMPRESS_CTRL_CODE)
    {
        pBuff[0] = u8CharCodeTable;
        pBuff[1] = u8EncodeTypeId;
        memcpy(&pBuff[2], pu8SrcString, (u8SrtLen > (u8DstLen-2)) ? (u8DstLen-2) : u8SrtLen);
    }
    else if(u8CharCodeTable == CI_ISO_8859_TABLE_CODE)
    {
        pBuff[0] = u8CharCodeTable;
        pBuff[1] = u8SecondByte;
        pBuff[2] = u8ThirdByte;
        memcpy(&pBuff[3], pu8SrcString, (u8SrtLen > (u8DstLen-3)) ? (u8DstLen-3) : u8SrtLen);
    }
    else
    {
        pBuff[0] = u8CharCodeTable;
        memcpy(&pBuff[1], pu8SrcString, (u8SrtLen > (u8DstLen-3)) ? (u8DstLen-3) : u8SrtLen);
    }

    memcpy(pu8DstString, pBuff, u8DstLen);
    if(pBuff != NULL)
    {
        free(pBuff);
        pBuff = NULL;
    }

    return TRUE;

}

BOOL msAPI_OP_SetCurr(U32 u32CicamId, const ST_TRIPLE_ID *stTripleId)
{
    U32 i;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);
    if(stTripleId == NULL)
    {
        return FALSE;
    }
    for(i = 0; i < MAX_OP_CACHE_NUM; i++)
    {
        if((_stOpCacheInfo[i].bUsed == TRUE)&&(_stOpCacheInfo[i].stCiOpInfo.u32CicamIdentifier == u32CicamId))
        {
            memcpy(&_stOpCacheInfo[i].stCurProgTripleID, stTripleId, sizeof(ST_TRIPLE_ID));
            return TRUE;
        }
    }

    return FALSE;
}

BOOL msAPI_OP_GetCurr(U32 u32CicamId, ST_TRIPLE_ID *stTripleId)
{
    U32 i;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);
    if(stTripleId == NULL)
    {
        return FALSE;
    }

    for(i = 0; i < MAX_OP_CACHE_NUM; i++)
    {
        if((_stOpCacheInfo[i].bUsed == TRUE)&&(_stOpCacheInfo[i].stCiOpInfo.u32CicamIdentifier == u32CicamId))
        {
            memcpy(stTripleId, &_stOpCacheInfo[i].stCurProgTripleID, sizeof(ST_TRIPLE_ID));
            return TRUE;
        }
    }
    return FALSE;
}

U8 msAPI_OP_GetOpCacheCount(void)
{
    U32 i,j = 0;
    for(i = 0; i < MAX_OP_CACHE_NUM; i++)
    {
        if(_stOpCacheInfo[i].bUsed == TRUE)
        {
            j++;
        }
    }
    //MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,j);

    return j;
}

BOOLEAN msAPI_OP_IsOpCountReachMaxNum(void)
{
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(msAPI_OP_GetOpCacheCount() < MAX_OP_CACHE_NUM)
    {
        return FALSE;
    }
    return TRUE;
}

static BOOLEAN msAPI_OP_GetStorageCacheInfo(U32 u32ID, MW_OPCACHE_INFO * pstOpCacheInfo)
{
    U32 u32CheckSum;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(u32ID >= MAX_OP_CACHE_NUM)
    {
        return FALSE;
    }
    if(pstOpCacheInfo == NULL)
    {
        return FALSE;
    }
    memset(pstOpCacheInfo, 0x00, sizeof(MW_OPCACHE_INFO));
    if(msAPI_OP_ReadDataFromFlash(u32ID, (U8 *)pstOpCacheInfo, E_OPCACHE_INFO) == FALSE)
    {
        MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d, read data fail.\n", __FUNCTION__,__LINE__);
        return FALSE;
    }
    MW_DTV_CI_OPCACHE_DB_DBG("u32ID:> %ld\n",pstOpCacheInfo->u32ID);
    MW_DTV_CI_OPCACHE_DB_DBG("bUsed:> %d\n",pstOpCacheInfo->bUsed);
    MW_DTV_CI_OPCACHE_DB_DBG("u32CicamId:> %ld\n",pstOpCacheInfo->stCiOpInfo.u32CicamIdentifier);
    MW_DTV_CI_OPCACHE_DB_DBG("u16CicamOriginalNetworkID:> 0x%x\n",pstOpCacheInfo->stCiOpInfo.u16CicamOriginalNetworkID);
    MW_DTV_CI_OPCACHE_DB_DBG("u8InfoVersion:> %d\n",pstOpCacheInfo->stCiOpInfo.u8InfoVersion);
    MW_DTV_CI_OPCACHE_DB_DBG("eDtvSystemType:> %d\n",pstOpCacheInfo->eDtvSystemType);
    MW_DTV_CI_OPCACHE_DB_DBG("u8SdtRunningStatusTrusted:> %d\n",pstOpCacheInfo->stCiOpInfo.u8SdtRunningStatusTrusted);
    MW_DTV_CI_OPCACHE_DB_DBG("u8EitRunningStatusTrusted:> %d\n",pstOpCacheInfo->stCiOpInfo.u8EitRunningStatusTrusted);
    MW_DTV_CI_OPCACHE_DB_DBG("u8EitPresentFollowingUsage:> %d\n",pstOpCacheInfo->stCiOpInfo.u8EitPresentFollowingUsage);
    MW_DTV_CI_OPCACHE_DB_DBG("u8EitScheduleUsage:> %d\n",pstOpCacheInfo->stCiOpInfo.u8EitScheduleUsage);
    MW_DTV_CI_OPCACHE_DB_DBG("u8ExtendedEventUsage:> %d\n",pstOpCacheInfo->stCiOpInfo.u8ExtendedEventUsage);
    MW_DTV_CI_OPCACHE_DB_DBG("u8SdtOtherTrusted:> %d\n",pstOpCacheInfo->stCiOpInfo.u8SdtOtherTrusted);
    MW_DTV_CI_OPCACHE_DB_DBG("u8EitEventTrigger:> %d\n",pstOpCacheInfo->stCiOpInfo.u8EitEventTrigger);
    MW_DTV_CI_OPCACHE_DB_DBG("u8NitVersion:> %d\n",pstOpCacheInfo->u8NitVersion);
    if(pstOpCacheInfo->bUsed == TRUE)
    {
        u32CheckSum = msAPI_OP_CalCheckSum((U8 *)pstOpCacheInfo, sizeof(MW_OPCACHE_INFO));
        if(u32CheckSum != pstOpCacheInfo->u32CheckSum)
        {
            MW_DTV_CI_OPCACHE_DB_ERROR("\033[0;32;31m %s:%d,pu8Data read data CheckSum fail.\033[0m\r\n", __FUNCTION__,__LINE__);
            return FALSE;
        }
    }

    return TRUE;

}

BOOLEAN msAPI_OP_GetStorageCacheCamNIT(U32 u32ID, MW_OPCACHE_CAMNIT * pstOpCacheCamNIT)
{
    U32 u32CheckSum;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,u32ID);

    if(u32ID >= MAX_OP_CACHE_NUM)
    {
        return FALSE;
    }

    if(pstOpCacheCamNIT == NULL)
    {
        return FALSE;
    }

    memset(pstOpCacheCamNIT, 0x00, sizeof(MW_OPCACHE_CAMNIT));
    if(msAPI_OP_ReadDataFromFlash(u32ID, (U8 *)pstOpCacheCamNIT, E_OPCACHE_CAMNIT) == FALSE)
    {
        MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d, read data fail.\n", __FUNCTION__,__LINE__);
        return FALSE;
    }
    MW_DTV_CI_OPCACHE_DB_ERROR("pstOpCacheCamNIT->u32ID = %ld\n",pstOpCacheCamNIT->u32ID);
    MW_DTV_CI_OPCACHE_DB_ERROR("pstOpCacheCamNIT->u16SecCount = %d\n",pstOpCacheCamNIT->u16SecCount);
    MW_DTV_CI_OPCACHE_DB_ERROR("pstOpCacheCamNIT->u32CheckSum = 0x%lx\n",pstOpCacheCamNIT->u32CheckSum);

    u32CheckSum = msAPI_OP_CalCheckSum((U8 *)pstOpCacheCamNIT, sizeof(MW_OPCACHE_CAMNIT));
    MW_DTV_CI_OPCACHE_DB_ERROR("u32CheckSum  0x%lx\n",u32CheckSum);
    if(u32CheckSum != pstOpCacheCamNIT->u32CheckSum)
    {
        MW_DTV_CI_OPCACHE_DB_ERROR("%s:%d,pu8Data read data CheckSum fail.\n", __FUNCTION__,__LINE__);
        return FALSE;
    }

    return TRUE;
}

static BOOLEAN msAPI_OP_Load(U32 u32ID)
{
    MW_OPCACHE_INFO stOpCacheInfo;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if(FALSE == msAPI_OP_GetStorageCacheInfo(u32ID, &stOpCacheInfo))
    {
        MW_DTV_CI_OPCACHE_DB_ERROR("\033[0;32;31m %s:%d,Get Storage Cache data fail.\033[0m\r\n", __FUNCTION__,__LINE__);
        return FALSE;
    }
    memcpy(&_stOpCacheInfo[u32ID], &stOpCacheInfo, sizeof(MW_OPCACHE_INFO));
    MW_DTV_CI_OPCACHE_DB_DBG("_stOpCacheInfo[%d].u32ID %ld\n",u32ID,_stOpCacheInfo[u32ID].u32ID);
    MW_DTV_CI_OPCACHE_DB_DBG("_stOpCacheInfo[%d].bUsed %d\n",u32ID,_stOpCacheInfo[u32ID].bUsed);
    MW_DTV_CI_OPCACHE_DB_DBG("_stOpCacheInfo[%d].eDtvSystemType %d\n",u32ID,_stOpCacheInfo[u32ID].eDtvSystemType);
    MW_DTV_CI_OPCACHE_DB_DBG("_stOpCacheInfo[%d].u8NitVersion %d\n",u32ID,_stOpCacheInfo[u32ID].u8NitVersion);
    return TRUE;
}

BOOLEAN msAPI_OP_UpdateCIOpInfo(const CI_OP_INFO *stCiOpInfo)
{
    MW_OPCACHE_INFO stOpCacheInfo;
    BOOL bRet = TRUE;
    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d, %ld\n",__PRETTY_FUNCTION__,__LINE__,stCiOpInfo->u32CicamIdentifier);

    if(stCiOpInfo == NULL)
    {
        return FALSE;
    }
    memset(&stOpCacheInfo, 0, sizeof(MW_OPCACHE_INFO));
    if(FALSE == msAPI_OP_GetOpCacheInfoByCicamId(stCiOpInfo->u32CicamIdentifier, &stOpCacheInfo))
    {
        if(msAPI_OP_GetOpCacheCount() < MAX_OP_CACHE_NUM)
        {
            memcpy(&stOpCacheInfo.stCiOpInfo, stCiOpInfo, sizeof(CI_OP_INFO));
            stOpCacheInfo.u8NitVersion = SI_INVALID_PSI_SI_VERSION;
            stOpCacheInfo.eDtvSystemType = E_DELIVERY_SYS_NONE;
            stOpCacheInfo.stCurProgTripleID.u16OnId = SI_INVALID_ON_ID;
            stOpCacheInfo.stCurProgTripleID.u16TsId = SI_INVALID_TS_ID;
            stOpCacheInfo.stCurProgTripleID.u16SrvId = SI_INVALID_SERVICE_ID;
            stOpCacheInfo.bUsed = TRUE;

            MW_DTV_CI_OPCACHE_DB_DBG("u32ID:> %ld\n",stOpCacheInfo.u32ID);
            MW_DTV_CI_OPCACHE_DB_DBG("bUsed:> %d\n",stOpCacheInfo.bUsed);
            MW_DTV_CI_OPCACHE_DB_DBG("u32CicamId:> %ld\n",stOpCacheInfo.stCiOpInfo.u32CicamIdentifier);
            MW_DTV_CI_OPCACHE_DB_DBG("u16CicamOriginalNetworkID:> 0x%x\n",stOpCacheInfo.stCiOpInfo.u16CicamOriginalNetworkID);
            MW_DTV_CI_OPCACHE_DB_DBG("u8InfoVersion:> %d\n",stOpCacheInfo.stCiOpInfo.u8InfoVersion);
            MW_DTV_CI_OPCACHE_DB_DBG("eDtvSystemType:> %d\n",stOpCacheInfo.eDtvSystemType);
            MW_DTV_CI_OPCACHE_DB_DBG("u8CharacterCodeTable:> %d\n",stOpCacheInfo.stCiOpInfo.u8CharacterCodeTable);
            MW_DTV_CI_OPCACHE_DB_DBG("u8SecondByteValue:> %d\n",stOpCacheInfo.stCiOpInfo.u8SecondByteValue);
            MW_DTV_CI_OPCACHE_DB_DBG("u8ThirdByteValue:> %d\n",stOpCacheInfo.stCiOpInfo.u8ThirdByteValue);
            MW_DTV_CI_OPCACHE_DB_DBG("u8SdtRunningStatusTrusted:> %d\n",stOpCacheInfo.stCiOpInfo.u8SdtRunningStatusTrusted);
            MW_DTV_CI_OPCACHE_DB_DBG("u8EitRunningStatusTrusted:> %d\n",stOpCacheInfo.stCiOpInfo.u8EitRunningStatusTrusted);
            MW_DTV_CI_OPCACHE_DB_DBG("u8EitPresentFollowingUsage:> %d\n",stOpCacheInfo.stCiOpInfo.u8EitPresentFollowingUsage);
            MW_DTV_CI_OPCACHE_DB_DBG("u8EitScheduleUsage:> %d\n",stOpCacheInfo.stCiOpInfo.u8EitScheduleUsage);
            MW_DTV_CI_OPCACHE_DB_DBG("u8ExtendedEventUsage:> %d\n",stOpCacheInfo.stCiOpInfo.u8ExtendedEventUsage);
            MW_DTV_CI_OPCACHE_DB_DBG("u8SdtOtherTrusted:> %d\n",stOpCacheInfo.stCiOpInfo.u8SdtOtherTrusted);
            MW_DTV_CI_OPCACHE_DB_DBG("u8EitEventTrigger:> %d\n",stOpCacheInfo.stCiOpInfo.u8EitEventTrigger);
            MW_DTV_CI_OPCACHE_DB_DBG("u8NitVersion:> %d\n",stOpCacheInfo.u8NitVersion);

            if(FALSE == msAPI_OP_Add((void *)&stOpCacheInfo, E_OPCACHE_INFO))
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("\033[0;32;31m UpdateCIOpInfo : OP Cache Info add fail \033[0m\r\n");
                bRet = FALSE;
            }
        }
    }
    else
    {
        if(stOpCacheInfo.stCiOpInfo.u8InfoVersion != stCiOpInfo->u8InfoVersion)
        {
            memcpy(&stOpCacheInfo.stCiOpInfo, stCiOpInfo, sizeof(CI_OP_INFO));
            if(FALSE == msAPI_OP_Save((void *)&stOpCacheInfo, E_OPCACHE_INFO))
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("\033[0;32;31m UpdateCIOpInfo : OP Cache Info save fail \033[0m\r\n");
                bRet = FALSE;
            }
            else
            {
                memcpy(&_stOpCacheInfo[stOpCacheInfo.u32ID], &stOpCacheInfo, sizeof(MW_OPCACHE_INFO));
            }
        }
    }

    return bRet;
}

BOOL msAPI_OP_UpdateCICamNIT(U32 u32CicamId, U8 *pu8NitSection, U16 u16SecLen, U16 u16SecCount, EN_DELIVERY_SYS_TYPE eDtvSystemType)
{
    U8 u8NitVersion;
    MW_OPCACHE_INFO stOpCacheInfo;
    MW_OPCACHE_CAMNIT *pstOpCacheCamNIT = NULL;;

    MW_DTV_CI_OPCACHE_DB_FUNCTION("%s:%d\n",__PRETTY_FUNCTION__,__LINE__);

    if((pu8NitSection == NULL) || (u16SecLen == 0) || (eDtvSystemType == E_DELIVERY_SYS_NONE))
    {
        MW_DTV_CI_OPCACHE_DB_ERROR("UpdateCICamNIT : CICAM NIT section is not available");
        return FALSE;
    }

    memset(&stOpCacheInfo, 0, sizeof(MW_OPCACHE_INFO));
    if(FALSE == msAPI_OP_GetOpCacheInfoByCicamId(u32CicamId, &stOpCacheInfo))
    {
        MW_DTV_CI_OPCACHE_DB_ERROR("UpdateCICamNIT : CicamId is not available");
        return FALSE;
    }
    else
    {
        u8NitVersion = ( pu8NitSection[5] >> 1 ) & 0x1F;
        MW_DTV_CI_OPCACHE_DB_DBG("u16CicamOriginalNetworkID  0x%x\n",stOpCacheInfo.stCiOpInfo.u16CicamOriginalNetworkID);
        MW_DTV_CI_OPCACHE_DB_DBG("u8NitVersion %d, %d\n",u8NitVersion,stOpCacheInfo.u8NitVersion);

        if(stOpCacheInfo.u8NitVersion != u8NitVersion)
        {
            pstOpCacheCamNIT = (MW_OPCACHE_CAMNIT *)malloc(sizeof(MW_OPCACHE_CAMNIT));
            if(pstOpCacheCamNIT ==  NULL)
            {
                return FALSE;
            }
            memset(pstOpCacheCamNIT, 0x00, sizeof(MW_OPCACHE_CAMNIT));
            stOpCacheInfo.u8NitVersion = u8NitVersion;
            stOpCacheInfo.eDtvSystemType = eDtvSystemType;
            //update op cache info
            if(FALSE == msAPI_OP_Save((void *)&stOpCacheInfo, E_OPCACHE_INFO))
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("\033[0;32;31m UpdateCICamNIT : OP Cache Info save fail \033[0m\r\n");
                if(pstOpCacheCamNIT != NULL)
                {
                    free(pstOpCacheCamNIT);
                    pstOpCacheCamNIT = NULL;
                }
                return FALSE;

            }
            memcpy(&_stOpCacheInfo[stOpCacheInfo.u32ID], &stOpCacheInfo, sizeof(MW_OPCACHE_INFO));
            pstOpCacheCamNIT->u16SecCount = u16SecCount;
            pstOpCacheCamNIT->u32ID = stOpCacheInfo.u32ID;
            memcpy(pstOpCacheCamNIT->au8CamNIT, pu8NitSection, (u16SecLen > MAX_CAM_NIT_SIZE) ? MAX_CAM_NIT_SIZE : u16SecLen);
            // update op cache nit
            if(FALSE == msAPI_OP_Save((void *)pstOpCacheCamNIT, E_OPCACHE_CAMNIT))
            {
                MW_DTV_CI_OPCACHE_DB_ERROR("\033[0;32;31m UpdateCICamNIT : OP Cache CAMNIT save fail \033[0m\r\n");
                if(pstOpCacheCamNIT != NULL)
                {
                    free(pstOpCacheCamNIT);
                    pstOpCacheCamNIT = NULL;
                }
                return FALSE;
            }
            else
            {
                DB_CI_PLUS_SETTING.u16OpChannelIdex = 0;
            }
        }
    }

    if(pstOpCacheCamNIT != NULL)
    {
        free(pstOpCacheCamNIT);
        pstOpCacheCamNIT = NULL;
    }
    return TRUE;
}

static U32 msAPI_OP_CalCheckSum(U8 *pBuf, U32 u32BufLen)
{
    U32 u32CheckSum, u32Idx;

    u32CheckSum = 0;

    u32Idx = sizeof(u32CheckSum);   // skip checksum field
    while(u32Idx < u32BufLen)
    {
        u32CheckSum += pBuf[u32Idx];
        u32Idx++;
    }

    //ask to mstar
    return (u32CheckSum + 0x55);
}


//static MW_OPCACHE_INFO opcacheinfo[MAX_OP_CACHE_NUM];

static BOOLEAN msAPI_OP_WriteDataToFlash(U32 u32ID, U8 *pu8Data, E_OPCACHE_DATA_TYPE eType)
{
    BOOLEAN IsWriteFlashDone = FALSE;
    U8 *temp =  NULL;

    if(pu8Data == NULL)
    {
        return FALSE;
    }

    if( u32ID >= MAX_OP_CACHE_NUM )
    {
        printf("\nError: msAPI_OP_WriteDataToFlash(): u32ID=%u!\n", u32ID);
        return FALSE;
    }

    if(eType == E_OPCACHE_INFO)
    {
        MW_OPCACHE_INFO opcacheinfo[MAX_OP_CACHE_NUM];

        memcpy(opcacheinfo,_stOpCacheInfo,sizeof(MW_OPCACHE_INFO)*MAX_OP_CACHE_NUM);
        memcpy(&opcacheinfo[u32ID],pu8Data,sizeof(MW_OPCACHE_INFO));

        //E_OPCACHE_INFO save in the same bank in Flash
        temp = (U8*)_PA2VA(((OPCACHE_BUF_MEMORY_TYPE & MIU1) ? (OPCACHE_BUF_ADR | MIU_INTERVAL) : (OPCACHE_BUF_ADR)));
        memcpy(temp,opcacheinfo,sizeof(MW_OPCACHE_INFO)*MAX_OP_CACHE_NUM);//Copy data to OP dram buffer
        MApp_SaveOpCacheDate(CIPLUS_1_3_BANK_CAM_INFO_DATA, CIPLUS_1_3_BANK_NUMBER, &IsWriteFlashDone);

        if (IsWriteFlashDone)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(eType == E_OPCACHE_CAMNIT)
    {
        temp =(U8*) _PA2VA(((OPCACHE_BUF_MEMORY_TYPE & MIU1) ? (OPCACHE_BUF_ADR | MIU_INTERVAL) : (OPCACHE_BUF_ADR)));
        memcpy(temp,pu8Data,sizeof(MW_OPCACHE_CAMNIT));
        MApp_SaveOpCacheDate(CIPLUS_1_3_BANK_CAM_NIT_DATA(u32ID), CIPLUS_1_3_BANK_NUMBER, &IsWriteFlashDone);

        if (IsWriteFlashDone)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

static BOOLEAN msAPI_OP_ReadDataFromFlash(U32 u32ID, U8 *pu8Data, E_OPCACHE_DATA_TYPE eType)
{
    U8 *tempptr = (U8*)_PA2VA(((OPCACHE_BUF_MEMORY_TYPE & MIU1) ? (OPCACHE_BUF_ADR | MIU_INTERVAL) : (OPCACHE_BUF_ADR)));

    if(u32ID >= MAX_OP_CACHE_NUM)   //fix coverity CID207395
    {
        return FALSE;
    }

    if(eType == E_OPCACHE_INFO)
    {
        MW_OPCACHE_INFO opcacheinfo[MAX_OP_CACHE_NUM];

       if ( MDrv_FLASH_Read(SYSTEM_BANK_SIZE*CIPLUS_1_3_BANK_CAM_INFO_DATA, SYSTEM_BANK_SIZE,  tempptr))
       {
            memcpy(opcacheinfo,tempptr,sizeof(opcacheinfo));
            memcpy(pu8Data,&opcacheinfo[u32ID],sizeof(MW_OPCACHE_INFO));
            return TRUE;
       }
       else
       {
            return FALSE;
       }
    }
    else if(eType == E_OPCACHE_CAMNIT)
    {
       if ( MDrv_FLASH_Read(SYSTEM_BANK_SIZE*CIPLUS_1_3_BANK_CAM_NIT_DATA(u32ID), SYSTEM_BANK_SIZE,  tempptr))
       {
            memcpy(pu8Data,tempptr,sizeof(MW_OPCACHE_CAMNIT));
       }
       else
       {
            return FALSE;
       }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

#endif // #if(ENABLE_CI_PLUS)

#undef API_OPCACHE_C

