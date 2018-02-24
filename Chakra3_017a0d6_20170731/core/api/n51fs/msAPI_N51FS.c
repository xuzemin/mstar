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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// @file
// @brief
// @author MStarSemi Inc.
//
//-
//-
//
////////////////////////////////////////////////////////////////////////////////
#define MSAPI_N51FS_C

#include "datatype.h"
#include "debug.h"

#include "msAPI_FSCommon.h"
#include "msAPI_FCtrl.h"

#include "N51FS_File.h"
#include "N51FS_Index.h"
#include "N51FS_Bitmap.h"
#include "msAPI_N51FS.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FSEnv.h"
#include "msAPI_Timer.h"
#include "msAPI_MIU.h"

#define N51FS_DBG(flag,x)  //{if(flag){x;}}

N51FS_Environment* N51FS_GetEnvironmentInfo(U8 enid)
{
    return (N51FS_Environment xdata*)msAPI_FS_GetAddr(FILE_ENVIRONMENT_POOL +(U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE);
}

IndexRecord* N51FS_GetIndexRecordInfo(U8 enid)
{
    return (IndexRecord xdata*)msAPI_FS_GetAddr(FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE+memoffset_N51FS_IndexRecord);
}

U32* N51FS_GetIndexRootInfo(U8 enid)
{
    return (U32 xdata*)msAPI_FS_GetAddr(FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE+memoffset_N51FS_INDEX_ROOT);
}

U32 N51FS_GetIndexRootMIUAddress(U8 enid)
{
    return (FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE+memoffset_N51FS_INDEX_ROOT);
}

IndexVars* N51FS_GetIndexVarsInfo(U8 enid)
{
    return (IndexVars xdata*)msAPI_FS_GetAddr(FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE+memoffset_N51FS_IndexVars);
}

U32 N51FS_GetIndexRecordMIUAddress(U8 enid)
{
      return (FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE+memoffset_N51FS_IndexRecord);
}

U32 N51FS_GetIndexVarsMIUAddress(U8 enid)
{
    return (FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE+memoffset_N51FS_IndexVars);
}
/*
U32 N51FS_GetCurrentFileEntryMIUAddress(U8 enid)
{
    return (FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE+memoffset_N51FS_CurrentFileEntry);
}
*/
U32 N51FS_GetEnvironmentMIUAddressa(U8 enid)
{
    return (FILE_ENVIRONMENT_POOL + (U32)enid*FILE_ENVIRONMENT_MEMORY_SIZE);
}

U32 N51FS_GetTemp0XDataMIUAddr()
{
    return N51FS_TEMP_4K_BUFFER_0;
}

U32 N51FS_DirectoryGetCurrentMFR(U8 environmentId)
{
    U32 result=0xFFFFFFFF;
    result = N51FS_GetEnvironmentInfo(environmentId)->CurrentDirectoryMFR;
    return result;
}

U32 N51FS_DirectoryGetParentMFR(U8 environmentId)
{
    U32 result=0xFFFFFFFF;
    result=N51FS_GetEnvironmentInfo(environmentId)->ParentDirectoryMFR;

    return result;
}


#if 0

void N51FS_ReturnXData(void)
{

    if (u8N51FS_Win1LockCount >  0)
    {
        u8N51FS_Win1LockCount--;
        XBYTE[XDMIU_REG_BASE + 13] = u116N51FS_Win1BaseArray[u8N51FS_Win1LockCount]>>8;
        XBYTE[XDMIU_REG_BASE + 12] = u116N51FS_Win1BaseArray[u8N51FS_Win1LockCount]>>0;

        N51FS_DBG(0,printf("N51FS XData Return: 0x%04x\n",u116N51FS_Win1BaseArray[u8N51FS_Win1LockCount]));
        u116N51FS_Win1BaseArray[u8N51FS_Win1LockCount] = 0;
    }

}
#endif
//XDATA Functions  ======================================================================


/*
static void N51FS_SetFileSystem(N51FS_FileSysStruct fileSys)
{
    N51FS_FileSysStruct* pfs;
    pfs=N51FS_GetFileSystemXData(fileSys.FileSystemID);

    pfs->FileSystemID=fileSys.FileSystemID;//must not be moved
    pfs->FileSystemType=fileSys.FileSystemType;
    pfs->DeviceIndex=fileSys.DeviceIndex;

    pfs->BootIndicator=fileSys.BootIndicator;
    pfs->SystemID=fileSys.SystemID;               //System ID. This byte defin
    pfs->RelativeSector=fileSys.RelativeSector;         //represents the offset from

    pfs->MFTCluster=fileSys.MFTCluster;
    pfs->MFTMirrorCluster=fileSys.MFTMirrorCluster;

    pfs->BytesPerSector=fileSys.BytesPerSector;
    pfs->SectorsPerCluster=fileSys.SectorsPerCluster;

    pfs->TotalSectors=fileSys.TotalSectors;           //Total Sectors.

    //
    pfs->RootDirectory_MFTLCN=fileSys.RootDirectory_MFTLCN;


    N51FS_ReturnXData();
}

*/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
U32 N51FS_ReadMFT_LSN(U8 fileSystemID, U32 MFR)
{
    N51FS_MftDataRun * pDataRun;
    N51FS_FileSysStruct* pfst;
    U8 u8SecPerMFTRecord;
    U8 u8SecPerCluster;
    U8  u8SectorNum;
    U32 u32LCN = 0;

    pfst=(N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fileSystemID);

    u8SecPerMFTRecord = pfst->SectorsPerMFTRecord;
    u8SecPerCluster = pfst->SectorsPerCluster;

    u32LCN = MFR*u8SecPerMFTRecord / u8SecPerCluster;
    u8SectorNum = (U8)(MFR*u8SecPerMFTRecord % u8SecPerCluster);

    //printf("u32LCN=0x%lx , u8SectorNum=0x%lx\n",u32LCN,u8SectorNum);
    pDataRun = (N51FS_MftDataRun xdata* )msAPI_FS_GetAddr(FILE_FAT_TABLE_CACHE + (U32)fileSystemID * FAT_TABLE_CACHE_LEN);

    while(pDataRun->u32LCN != 0 && pDataRun->u32Len != 0)
    {
        if(u32LCN >= pDataRun->u32Len)
        {
            u32LCN -= pDataRun->u32Len;
            pDataRun++;
        }
        else
        {

            u32LCN = (pDataRun->u32LCN + u32LCN) * u8SecPerCluster + u8SectorNum;
            return u32LCN;
        }
    }

    return 0;
}

U32 N51FS_ReadMFTRecord(U8 fileSystemID,U32 MFR,U32 destMIUAddr)
{

    N51FS_FileSysStruct* pfst;
    U32 sectorPerCluster;
    U16 bytesPerSector;
    U32 physicalStartSector;
    S8 deviceIndex;
    U32 recordLSN;
    U32 recordSector;
    U8* pBuff;
    U32 recordSize;
    U8 i;
    U8 u8ReadSectorCnt;
    U16 u16OffsetToFixUp;
    U16 u16FixUpCount;
    U16 u16FixUpNum;
    U16 u16SectorLastWord;
    U16 u16Temp;

    pfst=(N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fileSystemID);

    sectorPerCluster=pfst->SectorsPerCluster;
    bytesPerSector=pfst->BytesPerSector;
    physicalStartSector=pfst->RelativeSector;
    deviceIndex=pfst->DeviceIndex;

    recordLSN = N51FS_ReadMFT_LSN(fileSystemID, MFR);
    recordSector=physicalStartSector+recordLSN;

    N51FS_DBG(0,printf("N51FS_ReadMFTRecord. LSN=0x%08lx,deviceId=%bd\n",(U32)recordLSN,deviceIndex););

    if(!msAPI_MSDCtrl_SectorRead(deviceIndex,recordSector, 1, destMIUAddr))
    {
        __ASSERT(0);
        return 0;
    }

    pBuff = (U8 xdata* )msAPI_FS_GetAddr(destMIUAddr);

    memcpy(&u16Temp,&pBuff[0x06],2);
    //if( ((*((U16*)&pBuff[0x06]))+0x30)>bytesPerSector)
    if( (u16Temp+0x30)>bytesPerSector)
    {
        __ASSERT(0);
        return 0;
    }

    //recordSize=( *((U32*)&pBuff[0x1C]) );
    memcpy(&recordSize,&pBuff[0x1C],4);

    if(!msAPI_MSDCtrl_SectorRead(deviceIndex, recordSector, recordSize/bytesPerSector, destMIUAddr))
    {
        __ASSERT(0);
        return 0;
    }

    /*FIXUP!!*/
    u8ReadSectorCnt = (U8)(recordSize/bytesPerSector);
    //u16OffsetToFixUp = ( *((U16*)&pBuff[0x04]) );
    memcpy(&u16OffsetToFixUp,&pBuff[0x04],2);
    //u16FixUpCount = ( *((U16*)&pBuff[0x06]) );
    memcpy(&u16FixUpCount,&pBuff[0x06],2);
    //u16FixUpNum = *((U16*)&pBuff[u16OffsetToFixUp]);
    memcpy(&u16FixUpNum,&pBuff[u16OffsetToFixUp],2);

    for(i = 1; i <= u8ReadSectorCnt*(bytesPerSector/NTFS_BLOCK_SIZE); i++)
    {
        if(i > u16FixUpCount)
        {
            __ASSERT(0);
            return FALSE;
        }
        //u16SectorLastWord = *(U16 *)(pBuff + i*bytesPerSector - 2);
        memcpy(&u16SectorLastWord,(pBuff + i*NTFS_BLOCK_SIZE - 2),2);
        if(u16SectorLastWord == u16FixUpNum)
        {
            //*(U16 *)(pBuff + i*bytesPerSector - 2) = *(U16*)(pBuff + u16OffsetToFixUp + i*2);
            memcpy((pBuff + i*NTFS_BLOCK_SIZE - 2),(pBuff + u16OffsetToFixUp + i*2),2);
        }
        else
        {
            __ASSERT(0);
            return FALSE;
        }

    }

    N51FS_DBG(0,printf("MFT record at LSN:%lu\n",(U32)recordLSN);dumpMIU(destMIUAddr, 2););

    return recordSize;
}

void N51FS_Attribute_SwapAttrHead(void* pAttrHead)
{
    N51FS_ResidentAttrHead* pHead=(N51FS_ResidentAttrHead*)pAttrHead;
    //pHead->Type=(pHead->Type);
    //pHead->Length=(pHead->Length);
    //pHead->OffsetToName=(pHead->OffsetToName);
    //pHead->Flags=(pHead->Flags);
    //pHead->AttrId=(pHead->AttrId);

    if(pHead->NonResidentFlag)
    {
        N51FS_NonResidentAttrHead* pNH=(N51FS_NonResidentAttrHead*)pHead;
        UNUSED(pNH);
        //pNH->StartVCN=(pNH->StartVCN);
        //pNH->StartVCN_H=(pNH->StartVCN_H);
        //pNH->LastVCN=(pNH->LastVCN);
        //pNH->LastVCN_H=(pNH->LastVCN_H);

        //pNH->OffsetToDataRuns=(pNH->OffsetToDataRuns);
        //pNH->CompressUnitSize=(pNH->CompressUnitSize);

        //pNH->AllocatedSize=(pNH->AllocatedSize);
        //pNH->AllocatedSize_H=(pNH->AllocatedSize_H);
        //pNH->RealSize=(pNH->RealSize);
        //pNH->RealSize_H=(pNH->RealSize_H);
        //pNH->InitialDataSize=(pNH->InitialDataSize);
        //pNH->InitialDataSize_H=(pNH->InitialDataSize_H);
    }
    //else
    //{
        //pHead->LengthOfAttr=(pHead->LengthOfAttr);
        //pHead->OffsetToAttr=(pHead->OffsetToAttr);

    //}

}

/*attribute content will be put at the miu address*/
/*false will return a N51FS_AttributeInfo with size=0.*/
/*startMIUAddr must be the first position of the attribute array*/
static N51FS_AttributeInfo __N51FS_Attribute_Find(U32 startMIUAddr,U32 destMIUAddr,EN_ATTRIBUTE_TYPE attrType, U16* u16Offset)
{
    N51FS_AttributeInfo info;
    U32 currentAddr=startMIUAddr;
    U32 tp;
    U32 size;
    U8 attrBuffer[0x400];

    memset(attrBuffer,0,0x400);
    memset(&info,0,sizeof(N51FS_AttributeInfo));

    msAPI_FS_MIU_Copy(currentAddr,GET_DRAM_ADDR(attrBuffer),0x400);

    while(attrBuffer[0]!=0xFF || attrBuffer[1]!=0xFF || attrBuffer[2]!=0xFF || attrBuffer[3]!=0xFF)
    {
        //tp=( *((U32*)&attrBuffer[0x00]) );
        memcpy(&tp,&attrBuffer[0x00],4);
        //size=( *((U32*)&attrBuffer[0x04]) );
        memcpy(&size,&attrBuffer[0x04],4);

        if(tp==(U32)attrType)
        {

            info.Residented=(attrBuffer[0x08]==0)?TRUE:FALSE;
            info.Size=size;
            info.Type=tp;
            info.NameLength=attrBuffer[0x09];
            //info.ValueOffset=( *((U16*)&attrBuffer[0x14]) );
            memcpy(&(info.ValueOffset),&attrBuffer[0x14],2);

            /*copy the content*/
            if(info.Size>0x1000)
            {
                info.Size = 0x1000;
            }
            msAPI_FS_MIU_Copy(currentAddr, destMIUAddr,info.Size);

            break;
        }
        *u16Offset += (U16)size;
        currentAddr+=size;

        if(currentAddr-startMIUAddr >0x1000||size==0)
        {
            __ASSERT(0);//error, running too far...
            info.Size=0;

            return info;
        }

        msAPI_FS_MIU_Copy(currentAddr,GET_DRAM_ADDR(attrBuffer),0x400);

    }

    return info;
}

//!! the destMIUAddr is also worked as original "attributelist" attribute buffer
//!! see the calling sequence
static N51FS_AttributeInfo __N51FS_AttributeList_Find(U8 fsid,U32 destMIUAddr, EN_ATTRIBUTE_TYPE attrType,U32 u32ListSize, U32 lowestVCN)
{
    N51FS_AttributeInfo info;
    U8* attrBuffer;
    U32 currentAddr=destMIUAddr;
    U32 tp;
    U32 size;
    U32 tmpMFR = 0;
    U32 u32i = 0;
    U16* pMFR;
    U16 attributeOffset;
    U16 u16Temp;
    U32 startVCN, nextStartVCN;
    U32 nextTP;

    memset(&info,0,sizeof(N51FS_AttributeInfo));

    attrBuffer=(U8 *)msAPI_FS_Memory_Allocate(u32ListSize);
    if(attrBuffer==NULL)
    {
        __ASSERT(0);
        return info;
    }

    // get Base File Reference of the attribute
    msAPI_FS_MIU_Copy(currentAddr,GET_DRAM_ADDR(attrBuffer),u32ListSize);
    memcpy(&attributeOffset, attrBuffer+0x14, 2);
    currentAddr += attributeOffset;
    if(attributeOffset >= u32ListSize)
    {
        __ASSERT(0);
        return info;
    }
    memset(&attrBuffer[u32ListSize-attributeOffset],0xFF,4);
    msAPI_FS_MIU_Copy(currentAddr,GET_DRAM_ADDR(attrBuffer),u32ListSize-attributeOffset);

    u32i = 0;
    while(attrBuffer[u32i]!=0xFF || attrBuffer[u32i+1]!=0xFF || attrBuffer[u32i+2]!=0xFF || attrBuffer[u32i+3]!=0xFF)
    {
        memcpy(&tp,&attrBuffer[u32i], 4);
        memcpy(&u16Temp,&attrBuffer[u32i+4], 2);    //Size
        memcpy(&startVCN, &attrBuffer[u32i+8], 4);
        if(attrBuffer[u32i+u16Temp]!=0xFF || attrBuffer[u32i+1+u16Temp]!=0xFF
                      || attrBuffer[u32i+2+u16Temp]!=0xFF || attrBuffer[u32i+3+u16Temp]!=0xFF)
        {
             memcpy(&nextStartVCN, &attrBuffer[u32i+8+u16Temp], 4);
             memcpy(&nextTP,&attrBuffer[u32i+u16Temp], 4);
        }
        else
        {
             nextStartVCN = 0xFFFFFFFF;
        }

        if(tp==(U32)attrType &&(lowestVCN==0|| nextStartVCN==0xFFFFFFFF ||nextTP!=tp ||nextStartVCN>lowestVCN))
        {
            memcpy(&tmpMFR,&attrBuffer[u32i+0x10],4);
            if(tmpMFR == 0)
            {
                __ASSERT(0);
                msAPI_FS_Memory_Free(attrBuffer);
                return info;
            }
            size=N51FS_ReadMFTRecord(fsid, tmpMFR, N51FS_TEMP_4K_FIXUP);
            if(size == 0)
            {
                __ASSERT(0);
                msAPI_FS_Memory_Free(attrBuffer);
                return info;
            }
            pMFR=(U16 xdata *)msAPI_FS_GetAddr(N51FS_TEMP_4K_FIXUP);

            memcpy(&attributeOffset,((U8 *)pMFR)+0x14,2);
            info = __N51FS_Attribute_Find(N51FS_TEMP_4K_FIXUP+attributeOffset, destMIUAddr, attrType, &attributeOffset);
            if(info.Size)
                  break;
            ASSERT(0);
        }

        u32i+=(U32)u16Temp;
        currentAddr+=(U32)u16Temp;
        if(u16Temp == 0)
        {
             break;
        }

        if((currentAddr-destMIUAddr > 0x1000) ||  //error, running too far...
           (tp%0x10 != 0))  //Not attribute!!
        {
            break;
        }

    }

    msAPI_FS_Memory_Free(attrBuffer);
    memset(((U8 *)destMIUAddr)+info.Size, 0xff,4);

    return info;
}

/*attribute content will be put at the miu address*/
/*false will return a N51FS_AttributeInfo with size=0.*/
/*startMIUAddr must be the first position of the attribute array*/
N51FS_AttributeInfo N51FS_Attribute_Find(U8 fsid,U32 startMIUAddr,U32 destMIUAddr,EN_ATTRIBUTE_TYPE attrType, U16* pu16Offset,  U32 lowestVCN)
{
    N51FS_AttributeInfo info;

    //try to read from attribute list
    if(attrType != ATTR_TYPE_ATTRIBUTE_LIST)
    {
        //fill buffer with attribute list
        U16 u16Tmp = *pu16Offset;
        info=__N51FS_Attribute_Find(startMIUAddr,destMIUAddr,ATTR_TYPE_ATTRIBUTE_LIST, &u16Tmp);
        if(info.Size==0)
        {
            goto SERACH_NO_ATTR_LIST;
        }

        if(!info.Residented)
        {
            U8 *pu8DataRun;
            U8 *pu8MappingPairsOffset;
            U16 MappingPairsOffset;            
            U8 *u8OriMemoryAddress;
            U8 u8Header;
            U32 u32Length = 0;
            U32 u32LCNOffset = 0;
            U32 u32CurrentAddr = destMIUAddr;
            U32 u32CurrentSector;
            U32 u32Offset;
            N51FS_FileSysStruct* pFileSys;

            if(info.Size > 0x200)
            {
                __ASSERT(0);//data runs over flow!!
                info.Size = 0;
                return info;
            }

            pu8DataRun = msAPI_FS_Memory_Allocate(0x200);
            if(pu8DataRun == NULL)
            {
                __ASSERT(0);   //Allocate fail!!
                info.Size = 0;
                return info;
            }
            u8OriMemoryAddress = pu8DataRun;
			
            pu8MappingPairsOffset = msAPI_FS_Memory_Allocate(0x2);
            if(pu8MappingPairsOffset == NULL)
            {
                __ASSERT(0);   //Allocate fail!!
                info.Size = 0;
                msAPI_FS_Memory_Free(u8OriMemoryAddress);
                return info;
            }

            pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);
            u32CurrentSector = pFileSys->RelativeSector;

            //to understand this code,you can refer to linux ntfs3g code about "mapping_pairs_offset" in "ATTR_RECORD" struct.
            //or refer to ntfs spec "Table 4.4" and "Table 4.5" about "Offset to the Data Runs".
            msAPI_FS_MIU_Copy((U32)(destMIUAddr+0x20),(U32)pu8MappingPairsOffset,0x2);
            MappingPairsOffset = (pu8MappingPairsOffset[1]<<8) + pu8MappingPairsOffset[0];
            msAPI_FS_Memory_Free(pu8MappingPairsOffset);
            /*copy the data runs*/
            msAPI_FS_MIU_Copy((U32)(destMIUAddr+MappingPairsOffset),(U32)pu8DataRun,(info.Size-MappingPairsOffset));

            info.Size = 0;
            do
            {
                u8Header = pu8DataRun[0];
                pu8DataRun++;
                memcpy(&u32Length,pu8DataRun,(u8Header & 0x0F));
                pu8DataRun += (u8Header & 0x0F);
                memcpy(&u32LCNOffset,pu8DataRun,((u8Header & 0xF0)>>4));
                pu8DataRun += ((u8Header & 0xF0)>>4);

                u32CurrentSector += (u32LCNOffset * pFileSys->SectorsPerCluster);

                u32Offset = (u32Length * pFileSys->SectorsPerCluster * pFileSys->BytesPerSector);
                info.Size += u32Offset;

                if((u32CurrentAddr+u32Offset-destMIUAddr)<=0x1000)
                {
                    BOOLEAN _btmp = TRUE;
                    _btmp = msAPI_MSDCtrl_SectorRead(pFileSys->DeviceIndex, u32CurrentSector, (u32Length * pFileSys->SectorsPerCluster), u32CurrentAddr);
                    u32CurrentAddr += u32Offset;
                }
            }while(pu8DataRun[0]>0 && info.Size<0x1000);
            msAPI_FS_Memory_Free(u8OriMemoryAddress);

            if(info.Size > 0x1000)
            {
                __ASSERT(0);  //Size over flow!!
                info.Size=0;
                return info;
            }
        }
        info = __N51FS_AttributeList_Find(fsid,destMIUAddr,attrType,info.Size, lowestVCN);
        if(info.Size)
            return info;
    }

SERACH_NO_ATTR_LIST:
    if(lowestVCN > 0)
    {
        __ASSERT(0);
        memset(&info, 0, sizeof(info));
    }
    else
    {
        info=__N51FS_Attribute_Find(startMIUAddr,destMIUAddr,attrType,pu16Offset);

        if(info.Size==0)
        {
             __ASSERT(0);
        }
    }
    return info;
}

#if 0
// if found, return attribute MIU addr
// false will return 0
// startMIUAddr must be the first position of the attribute array
#if !LOPEZ_N51FS
U32 N51FS_Attribute_GetMIUAddr(U32 startMIUAddr, EN_ATTRIBUTE_TYPE attrType)
{
    N51FS_AttributeInfo info;
    U8* attrBuffer;
    U32 currentAddr = startMIUAddr;
    U32 tp;
    U32 size;

    memset(&info,0,sizeof(N51FS_AttributeInfo));
    attrBuffer=(U8 *)msAPI_FS_Memory_Allocate(128);
    if(attrBuffer==NULL)
    {
        __ASSERT(0);
        return 0;
    }
    memset(attrBuffer,0,128);

    while(attrBuffer[0]!=0xFF || attrBuffer[1]!=0xFF || attrBuffer[2]!=0xFF || attrBuffer[3]!=0xFF)
    {
        msAPI_FS_MIU_Copy(currentAddr,GET_DRAM_ADDR(attrBuffer),128);

        tp=( *((U32*)&attrBuffer[0x00]) );
        size=( *((U32*)&attrBuffer[0x04]) );
        if(tp==(U32)attrType)
        {
            break;
        }
        currentAddr += size;

        if(currentAddr-startMIUAddr >0x1000)
        {
            __ASSERT(0);//error, running too far...
            msAPI_FS_Memory_Free(attrBuffer);
            return 0;
        }
    }

    msAPI_FS_Memory_Free(attrBuffer);
    return currentAddr;

}
#endif // #if !LOPEZ_N51FS

#endif

static BOOLEAN  N51FS_CacheMFTData(N51FS_FileSysStruct* pFileSysToInitial)
{
    U8* pBuff;
    U32 u32Temp;
    U16 u16Temp,u16Temp_1;
    U8 u8ReadSectorCnt;
    U16 u16FixUpNum;
    U16 u16OffsetToFixUp;
    U16 u16SectorLastWord = 0;
    U16 u16OriginalWordd;
    U16 u16FixUpCount;
    U32 u32LCN;
    U32 u32Length;
    U8 u8LengthField, u8OffsetField;
    S32 s32OffsetToPrevious;
    N51FS_MftDataRun dataRun;
    U32 u32DataRunCnt = 0;
    U32 u32TotalDataRunCnt = FAT_TABLE_CACHE_LEN/sizeof(N51FS_MftDataRun);
    U32 u32TableCacheAddress= (FILE_FAT_TABLE_CACHE + (U32)pFileSysToInitial->FileSystemID * FAT_TABLE_CACHE_LEN) ;
    U32 u32RecordSector = pFileSysToInitial->RelativeSector + pFileSysToInitial->MFTCluster * pFileSysToInitial->SectorsPerCluster;
    U8 i;

    //[1] Read MFT record header
    if(!msAPI_MSDCtrl_SectorRead(pFileSysToInitial->DeviceIndex, u32RecordSector, 1, N51FS_TEMP_4K_FIXUP))
    {
        __ASSERT(0);
        return FALSE;
    }

    pBuff=(U8 xdata* )msAPI_FS_GetAddr(N51FS_TEMP_4K_FIXUP);

    memcpy(&u16Temp,&pBuff[0x06],2);

    //if( ((*((U16*)&pBuff[0x06]))+0x30) > pFileSysToInitial->BytesPerSector)   ////Eric won't use
    if( (u16Temp+0x30) > pFileSysToInitial->BytesPerSector)
    {
        __ASSERT(0);
        return FALSE;
    }

    //[2] Read MFT record
    //u32Temp = ( *((U32*)&pBuff[0x1C]) ); //record size
    memcpy(&u32Temp,&pBuff[0x1C],4);

    if(u32Temp > USB_IO_TEMP_LEN)
    {
        __ASSERT(0);
        return FALSE;
    }
    u8ReadSectorCnt = (U8)(u32Temp / pFileSysToInitial->BytesPerSector);

    if(!msAPI_MSDCtrl_SectorRead(pFileSysToInitial->DeviceIndex, u32RecordSector, (U32)u8ReadSectorCnt, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    //[3] FixUP!!
    //u16OffsetToFixUp = ( *((U16*)&pBuff[0x04]) );
    memcpy(&u16OffsetToFixUp,&pBuff[0x04],2);
    //u16FixUpCount = ( *((U16*)&pBuff[0x06]) );
    memcpy(&u16FixUpCount,&pBuff[0x06],2);
    //u16FixUpNum = *((U16*)&pBuff[u16OffsetToFixUp]);
    memcpy(&u16FixUpNum,&pBuff[u16OffsetToFixUp],2);

    for(i = 1; i <= u8ReadSectorCnt*(pFileSysToInitial->BytesPerSector/NTFS_BLOCK_SIZE); i++)
    {
        if(i > u16FixUpCount)
        {
            __ASSERT(0);
            return FALSE;
        }

        msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR + i*NTFS_BLOCK_SIZE - 2, GET_DRAM_ADDR(&u16SectorLastWord), 2);
        if(u16SectorLastWord == u16FixUpNum)
        {
            //u16OriginalWordd = *(U16*)(pBuff + i*2);
            memcpy(&u16OriginalWordd,(pBuff + i*2),2);
            msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&u16OriginalWordd), USB_IO_TEMP_ADDR + i*NTFS_BLOCK_SIZE - 2, 2);
        }
        else
        {
            __ASSERT(0);
            return FALSE;
        }

    }

    //[4] Find $DATA attribute
    msAPI_FS_MIU_Copy( USB_IO_TEMP_ADDR + 0x14, GET_DRAM_ADDR(&u16Temp), 2 );
    u32Temp = (U32)((u16Temp)); //Offset to the first attribute
    if((N51FS_Attribute_Find(pFileSysToInitial->FileSystemID,USB_IO_TEMP_ADDR + u32Temp, N51FS_GetTemp0XDataMIUAddr(), ATTR_TYPE_DATA, &u16Temp, 0)).Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }

    //[5] Cache the data run
    pBuff = (U8 *)msAPI_FS_GetAddr(N51FS_TEMP_4K_BUFFER_0);
    //u32Temp = (U32)((*(U16 *)(pBuff + 0x20)));
    memcpy(&u16Temp_1,(pBuff + 0x20),2);
    u32Temp=(U32)u16Temp_1;

    pBuff += u32Temp;

    u32LCN = 0;
    while(pBuff[0])
    {
        u8LengthField = *pBuff & 0xF;
        u8OffsetField = *pBuff >> 4;
        //printf("\nu8LengthField: %02bx, u8OffsetField: %02bx", u8LengthField, u8LengthField);

        if(u8LengthField > 4 || u8OffsetField > 4)
        {
            __ASSERT(0);// can not support
            return FALSE;
        }

        u32Length = 0;
        for(i=0; i< u8LengthField; i++)
        {
            u32Length = (u32Length<<8) |*(pBuff + 1 + u8LengthField - 1 - i);
        }

        if(*(pBuff + 1+ u8LengthField + u8OffsetField -1) & 0x80)
        {
            s32OffsetToPrevious = -1;
        }
        else
        {
            s32OffsetToPrevious = 0;
        }

        for(i=0; i<u8OffsetField; i++)
        {
            s32OffsetToPrevious = (s32OffsetToPrevious<<8) |*(pBuff + 1+ u8LengthField + u8OffsetField -1-i);
        }
        u32LCN += s32OffsetToPrevious;
        //printf("\nclength: %LX, recordLSN: %LX", clength, recordLSN);
        dataRun.u32LCN = u32LCN;
        dataRun.u32Len = u32Length;
        msAPI_FS_MIU_Copy( GET_DRAM_ADDR(&dataRun), u32TableCacheAddress + u32DataRunCnt*sizeof(N51FS_MftDataRun), sizeof(N51FS_MftDataRun));
        u32DataRunCnt++;
        if(u32DataRunCnt >= u32TotalDataRunCnt)
        {
            __ASSERT(0);// can not support
            return FALSE;
        }
        pBuff += (1 + u8LengthField + u8OffsetField);
    }

    dataRun.u32LCN = 0;
    dataRun.u32Len = 0;
    msAPI_FS_MIU_Copy( GET_DRAM_ADDR(&dataRun), u32TableCacheAddress + u32DataRunCnt*sizeof(N51FS_MftDataRun), sizeof(N51FS_MftDataRun));


    return TRUE;
}


BOOLEAN N51FS_InitialFileSystem(S8 deviceIndex,U32 logicalBlockAddress,U8* partitionBytes,N51FS_FileSysStruct* pFileSysToInitial)
{
    BOOLEAN ret = TRUE;
    U8 clustersPerMFTRecord;
    U8 clustersPerIndexRecord;
    U8* bpb;
    U8 i=0;

    if(sizeof(N51FS_FileSysStruct)>FILE_SYS_STRUCT_SIZE)
    {
        __ASSERT(0);
        return FALSE;
    }

    pFileSysToInitial->RelativeSector= logicalBlockAddress;
    pFileSysToInitial->FileSystemType=FILE_SYSTEM_TYPE_N51FS;
    pFileSysToInitial->DeviceIndex=deviceIndex;
    pFileSysToInitial->SystemID        = 0x07;
    pFileSysToInitial->FileSystemSupport = FILE_SYSTEM_SUPPORT_READ;


    if(partitionBytes!=NULL)
    {
        pFileSysToInitial->BootIndicator   = partitionBytes[0];
        //pFileSysToInitial->RelativeSector= logicalBlockAddress;
        //pFileSysToInitial->PhysicalStartSector=logicalBlockAddress;
    }

    if(!msAPI_MSDCtrl_SectorRead(pFileSysToInitial->DeviceIndex,pFileSysToInitial->RelativeSector,1,USB_IO_TEMP_ADDR))
        return FALSE;

    bpb=(U8 *)msAPI_FS_Memory_Allocate(512);
    if(bpb==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR, GET_DRAM_ADDR(bpb), 512); //Eric Over 512 bytes using MIU_Copy!!


    //pFileSysToInitial->BytesPerSector=( *((U16*)&bpb[0x0b]) );     //Eric won't use
    *((U8 *)&(pFileSysToInitial->BytesPerSector))=bpb[0x0b];
    *(((U8 *)&(pFileSysToInitial->BytesPerSector))+1)=bpb[0x0c];
    pFileSysToInitial->SectorsPerCluster=bpb[0x0d];

    //make sure it is a real ntfs volume(not a exfat volume)
    if(!pFileSysToInitial->BytesPerSector || !pFileSysToInitial->SectorsPerCluster)
    {
    	  __ASSERT(0);
    	  if (bpb != NULL)
    	  {
             msAPI_FS_Memory_Free(bpb);
             bpb = NULL;
    	  }
    	  return FALSE;
    }

    pFileSysToInitial->BitCountPerSector=0;

    for(i=0;i<0xFF;i++)
    {
        if((1<<i)== pFileSysToInitial->BytesPerSector)
        {
            pFileSysToInitial->BitCountPerSector=i;
            break;
        }
    }

    for(i=0;i<0xFF;i++)
    {
        if((1<<i)== pFileSysToInitial->BytesPerSector * pFileSysToInitial->SectorsPerCluster)
        {
            pFileSysToInitial->BitCountPerCluster=i;
            break;
        }
    }
//    printf("BitCountPerSector=%d,BitCountPerCluster=%d \n",pFileSysToInitial->BitCountPerSector,pFileSysToInitial->BitCountPerCluster);

    N51FS_DBG(1,printf("pFileSysToInitial->BitCountPerSector=0x%02bx\n",pFileSysToInitial->BitCountPerSector););

    //pFileSysToInitial->TotalSectors=( *((U32*)&bpb[0x28]) );
    memcpy(&(pFileSysToInitial->TotalSectors),&bpb[0x28],4);
    //pFileSysToInitial->MFTCluster=( *((U32*)&bpb[0x30]) );
    memcpy(&(pFileSysToInitial->MFTCluster),&bpb[0x30],4);
    //pFileSysToInitial->MFTMirrorCluster=( *((U32*)&bpb[0x38]) );
    memcpy(&(pFileSysToInitial->MFTMirrorCluster),&bpb[0x38],4);

    clustersPerMFTRecord=bpb[0x40];
    clustersPerIndexRecord=bpb[0x44];

    pFileSysToInitial->SectorsPerMFTRecord= clustersPerMFTRecord*pFileSysToInitial->SectorsPerCluster;
    pFileSysToInitial->SectorsPerIndexRecord=clustersPerIndexRecord*pFileSysToInitial->SectorsPerCluster;

    if(( clustersPerMFTRecord&0x80 )>0)
    {
        pFileSysToInitial->SectorsPerMFTRecord=(U8)((1 << (~clustersPerMFTRecord+1))/pFileSysToInitial->BytesPerSector);
    }

    if((clustersPerIndexRecord&0x80 )>0)
    {
        pFileSysToInitial->SectorsPerIndexRecord=(U8)((1 << (~clustersPerIndexRecord+1))/pFileSysToInitial->BytesPerSector);
    }

    pFileSysToInitial->ClustersPerFileInputBuffer=FILE_INPUT_BUFFER_SIZE/(pFileSysToInitial->BytesPerSector*pFileSysToInitial->SectorsPerCluster);

    N51FS_DBG(1,printf("N51FS VBR parsed:\n");
               printf("\tBytesPerSector=0x%04x,\n",pFileSysToInitial->BytesPerSector);
               printf("\tSectorsPerCluster=0x%02bx,\n",pFileSysToInitial->SectorsPerCluster);
               printf("\tTotalSectors=0x%08lx,\n",pFileSysToInitial->TotalSectors);
               printf("\tMFTCluster=0x%08lx,\n",pFileSysToInitial->MFTCluster);
               printf("\tRelativeSector=0x%08lx,\n",pFileSysToInitial->RelativeSector);
               printf("\tClustersPerMFTRecord=0x%02bx,\n",clustersPerMFTRecord);
               printf("\tClustersPerIndexRecord=0x%02bx,\n",clustersPerIndexRecord);
               printf("\tSectorsPerMFTRecord=0x%02bx,\n",pFileSysToInitial->SectorsPerMFTRecord);
               printf("\tSectorsPerIndexRecord=0x%02bx,\n",pFileSysToInitial->SectorsPerIndexRecord);
             );
    if(!N51FS_CacheMFTData(pFileSysToInitial))
    {
        ret = FALSE;
    }

    if (bpb != NULL)
    {
        msAPI_FS_Memory_Free(bpb);
        bpb = NULL;
    }

    return ret;
}


#if FILE_SYSTEM_GET_TOTAL_SIZE_ENABLE
U32 N51FS_GetTotalSizeInKB(U8 fsid)
{
    N51FS_FileSysStruct *pFileSys;
    U32 u32TotalSize;
    U8 temp;

    pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    u32TotalSize = ((pFileSys->TotalSectors/pFileSys->SectorsPerCluster)*pFileSys->SectorsPerCluster);

    if(pFileSys->BytesPerSector < 1024)
    {
        temp = (1024/pFileSys->BytesPerSector);
        u32TotalSize /= temp;
    }
    else
    {
        temp = (pFileSys->BytesPerSector/1024);
        u32TotalSize *= temp;
    }

    //printf("u32TotalSize = %lu KB", u32TotalSize);
    return u32TotalSize;
}
#endif


#if FILE_SYSTEM_GET_FREE_SPACE_ENABLE
U32 N51FS_GetFreeSpaceInKB(U8 fsid)
{
    FileEntry stFileEntry;
    U8 u8Filehandle;
    U8 *pu8Buffer;
    N51FS_FileSysStruct *pFileSys;
    U32 u32SizeReaded, u32SizeToRead, u32Len;
    U32 u32FreeClusterCount, u32TotalFreeSize;
    U16 u16Temp;
    U16 u16Loop;
    U8 u8Enlarge;

    static code U8 au8ZeroBitCountArray[256] =
    {
        8,7,7,6,7,6,6,5,7,6,6,5,6,5,5,4,    //0x00 - 0x0F
        7,6,6,5,6,5,5,4,6,5,5,4,5,4,4,3,    //0x10 - 0x1F
        7,6,6,5,6,5,5,4,6,5,5,4,5,4,4,3,    //0x20 - 0x2F
        6,5,5,4,5,4,4,3,5,4,4,3,4,3,3,2,    //0x30 - 0x3F
        7,6,6,5,6,5,5,4,6,5,5,4,5,4,4,3,    //0x40 - 0x4F
        6,5,5,4,5,4,4,3,5,4,4,3,4,3,3,2,    //0x50 - 0x5F
        6,5,5,4,5,4,4,3,5,4,4,3,4,3,3,2,    //0x60 - 0x6F
        5,4,4,3,4,3,3,2,4,3,3,2,3,2,2,1,    //0x70 - 0x7F
        7,6,6,5,6,5,5,4,6,5,5,4,5,4,4,3,    //0x80 - 0x8F
        6,5,5,4,5,4,4,3,5,4,4,3,4,3,3,2,    //0x90 - 0x9F
        6,5,5,4,5,4,4,3,5,4,4,3,4,3,3,2,    //0xA0 - 0xAF
        5,4,4,3,4,3,3,2,4,3,3,2,3,2,2,1,    //0xB0 - 0xBF
        6,5,5,4,5,4,4,3,5,4,4,3,4,3,3,2,    //0xC0 - 0xCF
        5,4,4,3,4,3,3,2,4,3,3,2,3,2,2,1,    //0xD0 - 0xDF
        5,4,4,3,4,3,3,2,4,3,3,2,3,2,2,1,    //0xE0 - 0xEF
        4,3,3,2,3,2,2,1,3,2,2,1,2,1,1,0     //0xF0 - 0xFF
    };

    N51FS_DBG(0,printf(" \n enter N51FS_GetFreeSpace \n"));
    N51FS_DBG(0,printf("N51FS_GetFreeSpace fsid = %lu\n", (U32)fsid));

    N51FS_GetFileEntryByMFR(fsid, N51FS_BITMAP_MFR, &stFileEntry);
    u8Filehandle = msAPI_FCtrl_FileOpen(&stFileEntry, OPEN_MODE_BINARY_FOR_READ);
    if(u8Filehandle == INVALID_FILE_HANDLE)
    {
        N51FS_DBG(1,printf("N51FS_GetFreeSpace INVALID FILE HANDLE\n"));
        __ASSERT(0);
        return 0;
    }

    pu8Buffer = (U8 xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    u32SizeReaded = 0;
    u32SizeToRead = 0;
    u32FreeClusterCount = 0;

    N51FS_DBG(0,printf("N51FS_GetFreeSpace File length = %lu\n", stFileEntry.FileLength.Lo));

    if(stFileEntry.FileLength.Lo > 0x20000)
        u8Enlarge = 10;
    else
        u8Enlarge = 0;
    u16Temp = (1 << u8Enlarge);

    msAPI_FCtrl_FileSeek(u8Filehandle, 0, FILE_SEEK_SET);
    while(stFileEntry.FileLength.Lo > u32SizeReaded)
    {
        if(stFileEntry.FileLength.Lo - u32SizeReaded > 0x1000)
            u32SizeToRead = 0x1000;
        else
            u32SizeToRead = stFileEntry.FileLength.Lo - u32SizeReaded;
        u32Len = msAPI_FCtrl_FileRead(u8Filehandle, _VA2PA(USB_IO_TEMP_ADDR), u32SizeToRead);
        if(u32Len==u32SizeToRead)  //by Ken / Kiwi 080829
        {
            //read failed...
            __ASSERT(0);
            msAPI_FCtrl_FileClose(u8Filehandle);
            return 0;
        }
        u16Loop = u32SizeToRead - u32Len - 1;

        while(u16Loop)
        {
            u32FreeClusterCount += au8ZeroBitCountArray[pu8Buffer[u16Loop]];
            if(u16Loop< u16Temp)
                break;
            u16Loop -= u16Temp;
        }
        if(!u8Enlarge)
            u32FreeClusterCount += au8ZeroBitCountArray[pu8Buffer[0]];

        u32SizeReaded = u32SizeReaded + u32SizeToRead - u32Len;
    }

    N51FS_DBG(0, printf(" N51FS_GetFreeSpace u32SizeReaded = %lu\n",u32SizeReaded));
    N51FS_DBG(0, printf(" N51FS_GetFreeSpace Free Cluster = %lu\n", u32FreeClusterCount));

    msAPI_FCtrl_FileClose(u8Filehandle);

    pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    N51FS_DBG(0, printf("N51FS_GetFreeSpace SectorsPerCluster = %lu\n", pFileSys->SectorsPerCluster));
    N51FS_DBG(0, printf("N51FS_GetFreeSpace BytesPerSector = %lu\n", pFileSys->BytesPerSector));

    u32TotalFreeSize = (u32FreeClusterCount << u8Enlarge) * pFileSys->SectorsPerCluster;
    if(pFileSys->BytesPerSector < 1024)
    {
        u16Temp = (1024/pFileSys->BytesPerSector);
        u32TotalFreeSize /= u16Temp;
    }
    else
    {
        u16Temp = (pFileSys->BytesPerSector/1024);
        u32TotalFreeSize *= u16Temp;
    }

    N51FS_DBG(0, printf(" \n exit N51FS_GetFreeSpace \n"));

    return u32TotalFreeSize;
}

BOOLEAN N51FS_GetFileEntryByMFR(U8 u8fsid, U32 u32mfr, FileEntry *pFileToSet)
{
    U16 u16AttributeOffset;
    U8 *pBuff;
    N51FS_AttributeInfo stAttrInfo;
    U8 c0, c1;
    U32 u32FileLength, u32FileLengthHI,u32FileFlag;
    U8* pu8TmpXdata;
    U16 u16TmpOffset = 0;

    N51FS_DBG(0,printf(" \n enter N51FS_GetFileEntryByMFR \n"));
    if(0 == N51FS_ReadMFTRecord(u8fsid, u32mfr, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    //u16AttributeOffset = ( *((U16*)&pBuff[0x14]) );
    memcpy(&u16AttributeOffset,&pBuff[0x14],2);

    stAttrInfo = N51FS_Attribute_Find(u8fsid,USB_IO_TEMP_ADDR + u16AttributeOffset, N51FS_GetTemp0XDataMIUAddr(), ATTR_TYPE_FILE_NAME, &u16TmpOffset, 0);
    if(stAttrInfo.Size == 0)
    {
        N51FS_DBG(0,printf("N51FS_GetFileEntryByMFR find filename attribute fail\n"));
        return FALSE;
    }

    pu8TmpXdata = (U8 *)msAPI_FS_GetAddr(N51FS_TEMP_4K_BUFFER_0);

    //u16TmpOffset= (*(U16*)(pu8TmpXdata + 0x14)) + 0x30;   //offset to real size of the file
    memcpy(&u16TmpOffset,(pu8TmpXdata + 0x14),2);
    u16TmpOffset += 0x30;

    //u32FileLength = (*(U32*)(pu8TmpXdata + u16TmpOffset));
    memcpy(&u32FileLength,(pu8TmpXdata + u16TmpOffset),4);

    //u32FileLengthHI=(*(U32*)(pu8TmpXdata + u16TmpOffset+0x04));
    memcpy(&u32FileLengthHI,(pu8TmpXdata + u16TmpOffset+0x04),4);

    //u16TmpOffset = (*(U16*)(pu8TmpXdata + 0x14)) + 0x38;  //offset to file flag
    memcpy(&u16TmpOffset,(pu8TmpXdata + 0x14),2);
    u16TmpOffset += 0x38;

    //u32FileFlag = (*(U32*)(pu8TmpXdata + u16TmpOffset));
    memcpy(&u32FileFlag,(pu8TmpXdata + u16TmpOffset),4);

    //u16TmpOffset = (*(U16*)(pu8TmpXdata + 0x14)) + 0x42;  //offset to file name
    memcpy(&u16TmpOffset,(pu8TmpXdata + 0x14),2);
    u16TmpOffset += 0x42;

    c0 = *(U8*)(pu8TmpXdata + u16TmpOffset);
    c1 = *(U8*)(pu8TmpXdata + u16TmpOffset + 0x02);

    pFileToSet->FileSystemID = u8fsid;
    //*((U32*)pFileToSet->EntryID) = u32mfr;
    memcpy(pFileToSet->EntryID,&u32mfr,4);
    pFileToSet->EntryFileLength = u32FileLength;
    pFileToSet->FileLength.Hi=u32FileLengthHI;
    pFileToSet->FileLength.Lo=u32FileLength;

    pFileToSet->EntryType = ENTRY_TYPE_FILE;
    if(u32FileFlag & 0x10000000UL)
    {
        pFileToSet->EntryType=ENTRY_TYPE_DIR;
        if(c0=='.')
        {
            if(c1=='.')
                pFileToSet->EntryType=ENTRY_TYPE_DIR_DOTDOT;
            else
                pFileToSet->EntryType=ENTRY_TYPE_DIR_DOT;
        }
    }

    N51FS_DBG(0,printf(" \n exit N51FS_GetFileEntryByMFR \n"));
    return TRUE;
}
#endif

#if FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
U8 N51FS_FileRecordFindVolumeLabel(U8 u8DriveIndex, U16 *VolLabName, U8 VolLabNameLen)
{
    U32 MFR=3;      //MFR of $Volume
    U16 u16Temp;
    U8 attrBuffer[0x400];
    U32 tp;
    U32 size;
    U8 attrType=ATTR_TYPE_VOLUMN_NAME;
    U32 startMIUAddr;
    U32 currentAddr;
    U16 u16AttrOffset;

    size = N51FS_ReadMFTRecord(u8DriveIndex, MFR, USB_IO_TEMP_ADDR);
    if(size == 0)
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FS_MIU_Copy( USB_IO_TEMP_ADDR + 0x14, GET_DRAM_ADDR(&u16Temp), 2 );
    u16AttrOffset = (u16Temp);
    N51FS_DBG(1,printf("u16AttrOffset = 0x%x\n\n",u16AttrOffset));

    startMIUAddr = USB_IO_TEMP_ADDR + u16AttrOffset;
    currentAddr = startMIUAddr;
    msAPI_FS_MIU_Copy(startMIUAddr ,GET_DRAM_ADDR(attrBuffer),0x400);

    N51FS_DBG(1,printf("startMIUAddr = 0x%08lx\n",startMIUAddr));
    N51FS_DBG(1,printf("currentAddr = 0x%08lx\n",currentAddr));

    while(attrBuffer[0]!=0xFF || attrBuffer[1]!=0xFF || attrBuffer[2]!=0xFF || attrBuffer[3]!=0xFF)
    {
        //tp=( *((U32*)&attrBuffer[0x00]));
        memcpy(&tp,&attrBuffer[0x00],4);
        //size=( *((U32*)&attrBuffer[0x04]) );
        memcpy(&size,&attrBuffer[0x04],4);

        if(tp==(U32)attrType)
        {
            U8 i;
            U8 NameLength = (attrBuffer[0x10]/2);
            //U16 ValueOffset = ( *((U16*)&attrBuffer[0x14]) );
            U16 ValueOffset;
            memcpy(&ValueOffset,&attrBuffer[0x14],2);

            N51FS_DBG(1,printf("NameLength = %bd\n",NameLength));
            N51FS_DBG(1,printf("ValueOffset = %u\n",ValueOffset));

            VolLabNameLen = VolLabNameLen>NameLength?NameLength:VolLabNameLen;
            for(i=0;i<VolLabNameLen;i++)
            {
                //VolLabName[i]=(*((U16*)&attrBuffer[ValueOffset+(i*2)]) );
                memcpy(&VolLabName[i],&attrBuffer[ValueOffset+(i*2)],2);
                N51FS_DBG(1,printf("0x%04x ",VolLabName[i]));
            }
            return NameLength;
        }

        currentAddr+=size;
        N51FS_DBG(1,printf("currentAddr = 0x%08lx\n\n",currentAddr));

        if(currentAddr-startMIUAddr >0x1000)
        {
            __ASSERT(0);//error, running too far...
            return 0;
        }

        msAPI_FS_MIU_Copy(currentAddr,GET_DRAM_ADDR(attrBuffer),0x400);

    }

    // Nothing Found
    return 0;
}
#endif // #if FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE


BOOLEAN N51FS_DirectoryChange(U8 enid,U32 mfr)
{
    N51FS_GetEnvironmentInfo(enid)->CurrentDirectoryMFR=mfr;

    return N51FS_Index_ToFirst(enid);
}

BOOLEAN N51FS_SaveEnvironment(U8 enid)
{
    FS_EnvironmentStruct* pEnv=msAPI_FSEnv_GetEnvironment(enid);

    N51FS_Environment* pN51FS_Env=N51FS_GetEnvironmentInfo(enid);

    pN51FS_Env->CurrentDirectoryMFR=0xFFFFFFFF;
    pN51FS_Env->ParentDirectoryMFR=0xFFFFFFFF;
    pN51FS_Env->EnvironmentID=enid;
    pN51FS_Env->DeviceIndex=pEnv->u8DeviceIndex;
    pN51FS_Env->FileSystemID=pEnv->u8FileSystemID;
    return TRUE;

    //printf("N51FS_Environment Saved!! EnvironmentID=%bu, DeviceIndex=%bu\n",enid,pEnv->u8DeviceIndex);
}

void N51FS_HandlePostCreate(U8 fhid,U8 fileSystemId,U32 fileLengthHI,U32 fileLengthLo,U8 openMode )
{
    N51FS_FileHandle* pN51FS_Handle=N51FS_File_GetHandleInfo(fhid);

    pN51FS_Handle->u8FileSystemID=fileSystemId;
    pN51FS_Handle->u8FileHandleID=fhid;

    pN51FS_Handle->MFTReference=0;
    pN51FS_Handle->FileSize_LL.Lo=fileLengthLo;
    pN51FS_Handle->FileSize_LL.Hi=fileLengthHI;

    /*changing*/
    pN51FS_Handle->CurrentBytePosition_LL.Lo=0;
    pN51FS_Handle->CurrentBytePosition_LL.Hi=0;

    pN51FS_Handle->DataResidented=FALSE;

    pN51FS_Handle->CurrentStartLCN = 0;
    pN51FS_Handle->CurrentVCN = 0;
    pN51FS_Handle->CurrentSectorNo = 0;
    pN51FS_Handle->CurrentRunLength = 0;
    pN51FS_Handle->NextStartVCN = 0;
    pN51FS_Handle->StartDataOffset = 0;

    //Open Mode
    pN51FS_Handle->u8OpenMode = openMode;

    //~!~compress flag
   pN51FS_Handle->u8CompressFlag = 0;
}


//============================================================================

U8 N51FS_EntryGetCurrentNameToMIU(U8 enid,U32 destMIUAddr,U8 charLen)
{
    U8 fileNameLen=0;
    U16* pBuffer;
    U8 i=0;
    IndexVars* pIndexVars;

    /*the N51FS_Index_GetCurrentIndexEntryStream() method is not used due to stream */
    if(charLen==0)
        return 0;

    pBuffer=msAPI_FS_Memory_Allocate(256*2);
    if(pBuffer==NULL)
    {
        __ASSERT(0);
        return 0;
    }

    pIndexVars=N51FS_GetIndexVarsInfo(enid);

    fileNameLen= *((U8*)pIndexVars+sizeof(IndexVars)+0x40);
    fileNameLen=(charLen>fileNameLen)?fileNameLen:charLen;

    //N51FS_DBG(0,printf("siszeof IndexVars=%lu. IndexEntry Next:  " ,(U32)sizeof(IndexVars));dumpMIU(N51FS_GetIndexVarsXDataMIUAddress(enid)+sizeof(IndexVars),16););  //Eric won't use
    N51FS_DBG(0,printf("sizeof IndexVars=%lu. IndexEntry Next:  \n" ,(U32)sizeof(IndexVars));dumpMIU(N51FS_GetIndexVarsMIUAddress(enid)+sizeof(IndexVars),2););

    memcpy((U8*)pBuffer,(U8*)pIndexVars+sizeof(IndexVars)+0x42,fileNameLen*2);

    for(i=0;i<fileNameLen;i++)
    {
        if(pBuffer[i]==0)
        {
            fileNameLen=i;
            break;
        }

        //pBuffer[i]=(pBuffer[i]);
    }

    msAPI_FS_MIU_Copy( GET_DRAM_ADDR(pBuffer), destMIUAddr,fileNameLen*2);

    if (pBuffer != NULL)
    {
        msAPI_FS_Memory_Free(pBuffer);
        pBuffer = NULL;
    }

    return fileNameLen;
}


#if (!FILE_SYSTEM_SMALL)

#if FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE
void N51FS_EntryGetCurrentFileEntry(U8 enid, FileEntry *entry)
{
    IndexVars* pIndexVars;
    U8 fileNameLen;

    pIndexVars=N51FS_GetIndexVarsInfo(enid);

    fileNameLen = *((U8*)pIndexVars+sizeof(IndexVars)+0x40);

    memcpy((U8*)entry, (U8*)pIndexVars+sizeof(IndexVars)+fileNameLen+2, sizeof(FileEntry));
}

U8 N51FS_EntryGetFileNameByFileEntry(U8 enid, FileEntry *entry, U32 destMIUAddr, U8 charLen, BOOLEAN *bIsLongName)
{
    U8 u8fsid;
    U8 *pData, *pDataEnd;
    U16 offsetToTheFirstAttribute;
    U32 mfr;
    U8 fileNameLen = 0;
    U32 u32Size;
    U16 *pu16Temp;
    U32 u32Temp;
    U16 u16Temp = 0;
    BOOLEAN bFound =FALSE, bFirstLoop = TRUE;

    u8fsid = msAPI_FSEnv_GetEnvironment(enid)->u8FileSystemID;
    //mfr = *((U32*)entry->EntryID);
    memcpy(&mfr,entry->EntryID,4);
    u32Size = N51FS_ReadMFTRecord(u8fsid, mfr, USB_IO_TEMP_ADDR);
    if(u32Size == 0)
    {
        __ASSERT(0);
        return FALSE;
    }

    pData = (U8 xdata *)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);
    pDataEnd = pData+0x1000UL;

    //offsetToTheFirstAttribute = ( *((U16*)(pData+0x14)) );
    memcpy(&offsetToTheFirstAttribute,(pData+0x14),2);
    pData += offsetToTheFirstAttribute;

TRY_AGAIN:

    while(*pData != 0xFF || *(pData + 1) != 0xFF || *(pData + 2) != 0xFF || *(pData + 3) !=0xFF)
    {
        //u32Size = ( *((U32*)(pData + 4)));
        memcpy(&u32Size,(pData + 4),4);

        memcpy(&u32Temp,pData,4);
        //if(ATTR_TYPE_FILE_NAME == ( *((U32*)pData)))
        if(u32Temp == ATTR_TYPE_FILE_NAME)
        {
            fileNameLen = *(pData + 0x58);

            if((TRUE == *bIsLongName) && (*(pData + 0x59) == FILENAMESPACE_DOS))
            {
                pData += u32Size;
                continue;
            }
            else if((FALSE == *bIsLongName) && (*(pData + 0x59) == FILENAMESPACE_POSIX))
            {
                pData += u32Size;
                continue;
            }

            fileNameLen=fileNameLen>charLen?charLen:fileNameLen;
            if(TRUE == *bIsLongName)
            {
                U8 i;  //0~255
                U16 fileName[256];

                for(i=0; i<fileNameLen; i++)
                {
                    //fileName[i] = (*((U16*)(pData + 0x5A) + i));
                    pu16Temp = ((U16*)(void *)(pData + 0x5A) + i);
                    memcpy(&fileName[i],pu16Temp,2);
                }

                msAPI_FS_MIU_Copy( GET_DRAM_ADDR(&fileName[0]), destMIUAddr, fileNameLen*2);
            }
            else
            {
                U8 i; //0~255
                U8 fileName[256];

                for(i=0; i<fileNameLen; i++)
                {
                    fileName[i] = *(pData + 0x5A + (i*2));
                }

                msAPI_FS_MIU_Copy( GET_DRAM_ADDR(&fileName[0]), destMIUAddr, fileNameLen);
            }
            bFound = TRUE;
            break;
        }
        pData += u32Size;
        if(pData >= pDataEnd)
            break;
    }

    if(bFound==FALSE && bFirstLoop==TRUE)
    {
        //fill buffer with attribute list
        U8 attribList[0x400];
        bFirstLoop = FALSE;
        N51FS_AttributeInfo info=__N51FS_Attribute_Find(USB_IO_TEMP_ADDR+offsetToTheFirstAttribute,GET_DRAM_ADDR(&attribList[0]),ATTR_TYPE_ATTRIBUTE_LIST,&u16Temp);

        if(info.Size==0)
        {
            __ASSERT(0);
            return 0;
        }

        msAPI_FS_MIU_Copy(GET_DRAM_ADDR(&attribList[0]), USB_IO_TEMP_ADDR, info.Size);

        if(!info.Residented)
        {
            U8 *pu8DataRun;
            U8 *pu8DataHead;
            U8 u8Header;
            U32 u32Length = 0;
            U32 u32LCNOffset = 0;
            U32 u32CurrentAddr = USB_IO_TEMP_ADDR;
            U32 u32CurrentSector;
            U32 u32Offset;
            N51FS_FileSysStruct* pFileSys;
            pu8DataHead = pu8DataRun = msAPI_FS_Memory_Allocate(0x200);
            if((info.Size > 0x200) || (pu8DataRun==NULL))
            {
                __ASSERT(0);//data runs over flow!!
                return 0;
            }

            pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(u8fsid);
            u32CurrentSector = pFileSys->RelativeSector;

            /*copy the data runs*/
            msAPI_FS_MIU_Copy(USB_IO_TEMP_ADDR+0x40, (U32)pu8DataRun,(info.Size-0x40));

            info.Size = 0;
            do
            {
                u8Header = pu8DataRun[0];
                pu8DataRun++;
                memcpy(&u32Length,pu8DataRun,(u8Header & 0x0F));
                pu8DataRun += (u8Header & 0x0F);
                memcpy(&u32LCNOffset,pu8DataRun,((u8Header & 0xF0)>>4));
                pu8DataRun += ((u8Header & 0xF0)>>4);

                u32CurrentSector += (u32LCNOffset * pFileSys->SectorsPerCluster);

                u32Offset = (u32Length * pFileSys->SectorsPerCluster * pFileSys->BytesPerSector);
                info.Size += u32Offset;

                if(u32CurrentAddr+u32Offset-USB_IO_TEMP_ADDR<=0x1000)
                {
                    BOOLEAN _btmp = TRUE;
                    _btmp = msAPI_MSDCtrl_SectorRead(pFileSys->DeviceIndex, u32CurrentSector, (u32Length * pFileSys->SectorsPerCluster), u32CurrentAddr);
                    u32CurrentAddr += u32Offset;
                }

            }while(pu8DataRun[0]>0 && info.Size<0x1000);
            msAPI_FS_Memory_Free(pu8DataHead);

            if(info.Size > 0x1000)
            {
                __ASSERT(0);  //Size over flow!!
                info.Size=0;
                return 0;
            }
        }
        info = __N51FS_AttributeList_Find(u8fsid, USB_IO_TEMP_ADDR,ATTR_TYPE_FILE_NAME,info.Size, 0);
        if(info.Size)
        {
                pData = (U8 xdata *)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);
                pDataEnd = pData+0x1000UL;
                offsetToTheFirstAttribute = 0;
               goto TRY_AGAIN;
         }
    }
    *bIsLongName=FALSE; //this flag is for HasShortNameOnly

    return fileNameLen;
}

#endif // #if FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE


BOOLEAN N51FS_WriteMFTRecord(U8 fileSystemID,U32 MFR,U32 SrcMIUaddr)
{
    N51FS_FileSysStruct* pfst;
    U32 u32RecordLSN;
    U32 u32PhysicalStartSector;
    S8 s8DeviceIndex;
    U16 i;
    U8 * pBuff;
    U16 u16OffsetToFixUp;
    U16 u16FixUpCount;
    U16 u16FixUpNum;
    U8 u8ReadSectorCnt;
    U16 u16BytesPerSec;
    U32 u32RecordSize;

    pfst=(N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fileSystemID);

    u16BytesPerSec = pfst->BytesPerSector;
    u32PhysicalStartSector = pfst->RelativeSector;
    s8DeviceIndex = pfst->DeviceIndex;

    u32RecordLSN = N51FS_ReadMFT_LSN(fileSystemID, MFR);

    //[1].FixUP
    pBuff = (U8 xdata*)msAPI_FS_GetAddr(SrcMIUaddr);

    //u32RecordSize = (*(U32 *)(pBuff + 0x1C));
    memcpy(&u32RecordSize,(pBuff + 0x1C),4);
    u8ReadSectorCnt = (U8)(u32RecordSize /  u16BytesPerSec);
    //u16OffsetToFixUp = ( *((U16*)&pBuff[0x04]) );
    memcpy(&u16OffsetToFixUp,&pBuff[0x04],2);
    //u16FixUpCount = ( *((U16*)&pBuff[0x06]) );
    memcpy(&u16FixUpCount,&pBuff[0x06],2);
    //u16FixUpNum = *((U16*)&pBuff[u16OffsetToFixUp]);
    memcpy(&u16FixUpNum,&pBuff[u16OffsetToFixUp],2);

    for(i = 1; i <= u8ReadSectorCnt*(u16BytesPerSec/NTFS_BLOCK_SIZE); i++)
    {
        if(i > u16FixUpCount)
        {
            __ASSERT(0);
            return FALSE;
        }
        //*(U16*)(pBuff + u16OffsetToFixUp + i*2) = *(U16*)(pBuff + i*u16BytesPerSec - 2);
        memcpy((pBuff + u16OffsetToFixUp + i*2),(pBuff + i*NTFS_BLOCK_SIZE - 2),2);
        //*(U16*)(pBuff + i*u16BytesPerSec - 2) = u16FixUpNum;
        memcpy((pBuff + i*NTFS_BLOCK_SIZE - 2),&u16FixUpNum,2);
    }

    //[2]. Save
    if(!msAPI_MSDCtrl_SectorWrite((U8)s8DeviceIndex, u32PhysicalStartSector + u32RecordLSN, u8ReadSectorCnt, SrcMIUaddr))
    {
        __ASSERT(0);
        return FALSE;

    }
    return TRUE;
}

extern IndexHeader* pIndexHeader;
BOOLEAN N51FS_FileDelete(FileEntry *pFileEntry)
{
    U8 i;
    U32 u32Temp;
    pIndexHeader = (IndexHeader*) msAPI_FS_Memory_Allocate(sizeof(IndexHeader));

    if(pIndexHeader == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    //search the index
    for(i = 0;i <2;i++)
    {
        if(!N51FS_Delete_Index_Search(pFileEntry))
        {
            if(i == 0)
            {
                __ASSERT(0);
                msAPI_FS_Memory_Free(pIndexHeader);
                return FALSE;
            }
            else
            {
                break;
            }
        }
        if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
        {
            N51FS_Delete_RemoveNode(pFileEntry->FileSystemID);
        }

        if(!N51FS_Delete_RemoveLeaf(pFileEntry->FileSystemID))
        {
            __ASSERT(0);
            msAPI_FS_Memory_Free(pIndexHeader);
            return FALSE;
        }

        if(pIndexHeader->bRootDirty)
        {
            //N51FS_WriteMFTRecord(pFileEntry->FileSystemID, *((U32*)pFileEntry->EntryID_Ext), N51FS_TEMP_4K_BACKUP_BUFFER_0);
            memcpy(&u32Temp,pFileEntry->EntryID_Ext,4);
            N51FS_WriteMFTRecord(pFileEntry->FileSystemID, u32Temp, N51FS_TEMP_4K_BACKUP_BUFFER_0);
        }
    }

    msAPI_FS_Memory_Free(pIndexHeader);

    memcpy(&u32Temp,pFileEntry->EntryID,4);
    //if(!N51FS_Delete_MarkMFTRecordUnused(pFileEntry->FileSystemID, *((U32*)pFileEntry->EntryID)))
    if(!N51FS_Delete_MarkMFTRecordUnused(pFileEntry->FileSystemID, u32Temp))
    {
        __ASSERT(0);
        return FALSE;
    }

    memcpy(&u32Temp,pFileEntry->EntryID,4);
    //if(!N51FS_Bitmap_ClusterFreeByMFR(pFileEntry->FileSystemID, *((U32*)pFileEntry->EntryID)))
    if(!N51FS_Bitmap_ClusterFreeByMFR(pFileEntry->FileSystemID, u32Temp))
    {
        __ASSERT(0);
        return FALSE;
    }

    memcpy(&u32Temp,pFileEntry->EntryID,4);
    //if(!N51FS_Bitmap_MFRFree(pFileEntry->FileSystemID, *((U32*)pFileEntry->EntryID)))
    if(!N51FS_Bitmap_MFRFree(pFileEntry->FileSystemID, u32Temp))
    {
        __ASSERT(0);
        return FALSE;
    }

    return TRUE;
}

#endif//FILE_SYSTEM_SMALL


BOOLEAN N51FS_EntryFirst(U8 enId)
{
    return N51FS_Index_ToFirst(enId);
}

EN_ENTRY_NEXT_RESULT N51FS_EntryNext(U8 enId,FileEntry* pFileToSet)
{
    EN_N51FS_INDEX_NEXT_RESULT indexNextResult = N51FS_INDEX_NEXT_RESULT_ERROR;
    EN_ENTRY_NEXT_RESULT result = ENTRY_NEXT_RESULT_SUCCESS;


    if(enId == INVALID_FS_ENVIRONMENT_INDEX||msAPI_FSEnv_GetEnvironment(enId) == NULL)
    {
        return ENTRY_NEXT_RESULT_ERROR;
    }

    pFileToSet->FileSystemID = msAPI_FSEnv_GetEnvironment(enId)->u8FileSystemID;

    indexNextResult = N51FS_Index_Next(enId, pFileToSet);

    if(indexNextResult == N51FS_INDEX_NEXT_RESULT_ERROR)
    {
        result=ENTRY_NEXT_RESULT_ERROR;
    }
    else if(indexNextResult == N51FS_INDEX_NEXT_RESULT_LAST)
    {
        result=ENTRY_NEXT_RESULT_LAST;
    }

    return result;
}


BOOLEAN N51FS_FileOpen(U8 handleId,U32 mfr)
{
    if(handleId!=INVALID_FILE_HANDLE)
        return N51FS_File_OpenFileRecord(handleId,mfr);
    else
        return FALSE;
}

U32 N51FS_FileRead(U8 handleId,U32 MIUAddr,U32 len)
{
    N51FS_FileHandle* pFileHandle;
    BOOLEAN bIsResidented;

    if(len == 0 || handleId == INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return len;
    }

    pFileHandle=N51FS_File_GetHandleInfo(handleId);
    bIsResidented = pFileHandle->DataResidented;

    if(bIsResidented)
    {
        return N51FS_FileRead_Residented(handleId, MIUAddr, len);
    }
    else
    {
        if(pFileHandle->u8CompressFlag)
            return N51FS_FileRead_NonResidented_Compress(handleId, MIUAddr, len);
        else
            return N51FS_FileRead_NonResidented(handleId, MIUAddr, len);
    }
}

#if FILE_SYSTEM_FILE_TELL_ENABLE
LongLong N51FS_FileTell(U8 handleId)
{
    LongLong val;
    N51FS_FileHandle* pHandle;

    if(handleId==INVALID_FILE_HANDLE)
    {
        val.Hi=0xFFFFFFFF;
        val.Lo=0xFFFFFFFF;
        return val;
    }

    pHandle=N51FS_File_GetHandleInfo(handleId);

    val=pHandle->CurrentBytePosition_LL;
    return val;
}
#endif


BOOLEAN N51FS_FileClose(U8 handleId)
{
    handleId = handleId;
    return TRUE;
}
BOOLEAN N51FS_FileSeek(U8 handleId, U32 u32Length, EN_FILE_SEEK_OPTION seekOption)
{
#if 1
    BOOLEAN bIsResidented;
    U32 u32BeginVCN, u32EndVCN;
    N51FS_FileHandle* pN51FS_Handle;
    LongLong currentPosition;
    U16 u16BytePerSec;
    U8 u8SecPerClus;
    U32 u32SectorNo;
    U8 u8BitCountPerSector;
    U32 targetVCN;
    BOOLEAN bFound;
    BOOLEAN bMatchFileEnd;

    N51FS_FileSysStruct* pFileSys;

    if(handleId==INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        return FALSE;
    }

    pN51FS_Handle=N51FS_File_GetHandleInfo(handleId);

    pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(pN51FS_Handle->u8FileSystemID);

    u16BytePerSec = pFileSys->BytesPerSector;
    u8SecPerClus = pFileSys->SectorsPerCluster;
    u8BitCountPerSector=pFileSys->BitCountPerSector;

    bIsResidented = pN51FS_Handle->DataResidented;
    currentPosition = pN51FS_Handle->CurrentBytePosition_LL;

    //calculate set position
    if(seekOption == FILE_SEEK_SET)
    {
        LL_assign(&currentPosition,0);
    }

    currentPosition=LL_add(&currentPosition,u32Length);

    //check overflow
    if(LL_greater(&currentPosition,&pN51FS_Handle->FileSize_LL))
    {
        currentPosition=pN51FS_Handle->FileSize_LL;
    }
    if(LL_equal(&currentPosition,&pN51FS_Handle->FileSize_LL))
           bMatchFileEnd = TRUE;
    else
           bMatchFileEnd = FALSE;

    if(bIsResidented)
    {
        pN51FS_Handle->CurrentBytePosition_LL= currentPosition;
        return TRUE;
    }
    else
    {
        u32SectorNo = LL_rshift(&currentPosition,u8BitCountPerSector).Lo;
        targetVCN = u32SectorNo / u8SecPerClus;
        pN51FS_Handle->CurrentSectorNo = (U8)(u32SectorNo % u8SecPerClus);

        pN51FS_Handle->CurrentStartLCN = N51FS_File_MapVCN2LCN(handleId ,0, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);
        if(!bFound)
        {
            ASSERT(0);
            return FALSE;
        }
        pN51FS_Handle->NextStartVCN = u32EndVCN;

        pN51FS_Handle->CurrentRunLength = u32EndVCN - u32BeginVCN;

        u32SectorNo = LL_rshift(&currentPosition,u8BitCountPerSector).Lo;
        pN51FS_Handle->CurrentVCN = targetVCN;
        pN51FS_Handle->CurrentSectorNo = (U8)(u32SectorNo % u8SecPerClus);

        while(pN51FS_Handle->CurrentVCN >= pN51FS_Handle->CurrentRunLength)
        {

            if(!bMatchFileEnd ||  pN51FS_Handle->CurrentVCN != pN51FS_Handle->CurrentRunLength)
            {
                  pN51FS_Handle->CurrentVCN -= pN51FS_Handle->CurrentRunLength;
                  pN51FS_Handle->CurrentStartLCN = N51FS_File_MapVCN2LCN(handleId ,pN51FS_Handle->NextStartVCN, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);
            }
            else
            {
                  break;
            }
            if(!bFound)
            {
                ASSERT(0);
               return FALSE;
            }
            pN51FS_Handle->NextStartVCN = u32EndVCN;
            pN51FS_Handle->CurrentRunLength = u32EndVCN - u32BeginVCN;
        }
        /*if(pN51FS_Handle->CurrentStartLCN == 0)
        {
            printf("in Seek, pFileHandle->CurrentStartLCN = 0\n");
            __ASSERT(0);
            //return FALSE;
        }*/
        pN51FS_Handle->CurrentBytePosition_LL = currentPosition;
        return TRUE;
    }

#else //keep previous s32Offset code

    BOOLEAN bIsResidented;
    U32 u32BeginVCN, u32EndVCN;
    N51FS_FileHandle* pN51FS_Handle;
    LongLong currentPosition;
    U16 u16BytePerSec;
    U8 u8SecPerClus;
    U32 u32SectorNo;
    U8 u8BitCountPerSector;

    N51FS_FileSysStruct* pFileSys;


    if(handleId==INVALID_FILE_HANDLE)
                return FALSE;

        pN51FS_Handle=N51FS_File_GetHandleXData(handleId);

    pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemXData(pN51FS_Handle->u8FileSystemID);
    u16BytePerSec = pFileSys->BytesPerSector;
    u8SecPerClus = pFileSys->SectorsPerCluster;
    u8BitCountPerSector=pFileSys->BitCountPerSector;
    msAPI_FS_ReturnXData();

    bIsResidented = pN51FS_Handle->DataResidented;
    currentPosition = pN51FS_Handle->CurrentBytePosition_LL;

    //calculate set position
    if(seekOption == FILE_SEEK_SET)
    {
        if(offset < 0)
        {
            LL_assign(&currentPosition,0);

        }
        else
        {
            LL_assign(&currentPosition,(U32)offset);
        }
    }
    else //FILE_SEEK_CUR
    {
        if(offset<0)
        {
            LongLong _tmp;
            LL_assign(&_tmp,abs(offset));
            if(LL_greater_or_equal(&_tmp,&currentPosition))
            {
                LL_assign(&currentPosition,0);
            }
            else
            {
                 currentPosition=LL_subtract(&currentPosition,(U32)abs(offset));
            }
        }
        else
        {
            currentPosition=LL_add(&currentPosition,(U32)offset);
        }
    }

    if(LL_greater(&currentPosition,&pN51FS_Handle->FileSize_LL))
    {
        __ASSERT(0);
        N51FS_ReturnXData();
        return FALSE;
    }

    if(bIsResidented)
    {
        pN51FS_Handle->CurrentBytePosition_LL= currentPosition;
        N51FS_ReturnXData();
        return TRUE;
    }
    else
    {
        pN51FS_Handle->CurrentStartLCN = N51FS_File_MapVCN2LCN(handleId, pN51FS_Handle->StartVCN, &u32BeginVCN, &u32EndVCN);
        if(pN51FS_Handle->CurrentStartLCN == 0)
        {
            __ASSERT(0);
            N51FS_ReturnXData();
            return FALSE;
        }
        pN51FS_Handle->NextStartVCN = u32EndVCN;
        pN51FS_Handle->CurrentVCN = pN51FS_Handle->StartVCN - u32BeginVCN;
        pN51FS_Handle->CurrentRunLength = u32EndVCN - u32BeginVCN;

        u32SectorNo = LL_rshift(&currentPosition,u8BitCountPerSector).Lo;
        pN51FS_Handle->CurrentVCN += u32SectorNo / u8SecPerClus;
        pN51FS_Handle->CurrentSectorNo = (U8)(u32SectorNo % u8SecPerClus);

        while(pN51FS_Handle->CurrentVCN >= pN51FS_Handle->CurrentRunLength)
        {
            pN51FS_Handle->CurrentVCN -= pN51FS_Handle->CurrentRunLength;
            pN51FS_Handle->CurrentStartLCN = N51FS_File_MapVCN2LCN(handleId, pN51FS_Handle->NextStartVCN, &u32BeginVCN, &u32EndVCN);
            if(pN51FS_Handle->CurrentStartLCN == 0)
            {
                __ASSERT(0);
                N51FS_ReturnXData();
                return FALSE;
            }
            pN51FS_Handle->NextStartVCN = u32EndVCN;
            pN51FS_Handle->CurrentRunLength = u32EndVCN - u32BeginVCN;
        }
        pN51FS_Handle->CurrentBytePosition_LL = currentPosition;
        N51FS_ReturnXData();
        return TRUE;
    }
#endif
}


LongLong N51FS_FileLength(U8 handleId)
{
    LongLong result;
    LL_assign(&result,0);

    if(handleId==INVALID_FILE_HANDLE)
        return result;

    result= N51FS_File_GetHandleInfo(handleId)->FileSize_LL;

    return result;
}


#if 0
static BOOLEAN N51FS_ClusterFreeFromFHID(U8 u8enid, U8 u8fhid)
{
    U8 u8BitmapFH;
    U8 *pBuffer;
    FileEntry stFileEntry;
    U32 u32StartVCN, u32LastVCN, u32CurrentLCN, u32CurrentVCN, u32EndVCN;
    U32 u32PrevLCN;
    //U32 u32DontCare;
    U8* ptr;
    U8 u8fsid;
    N51FS_FileHandle *pFileHandle;
    //N51FS_NonResidentAttrHead* phead;
    U32 i;

/*
    pFileHandle = N51FS_File_GetHandleXData(u8fhid);
    u8fsid = pFileHandle->u8FileSystemID;
    u32StartVCN = pFileHandle->StartVCN;
    u32LastVCN = pFileHandle->LastVCN;
    N51FS_ReturnXData();
*/
    // 1. open bitmap file
    N51FS_GetFileEntryByMFR(u8enid, N51FS_BITMAP_MFR, &stFileEntry);
    u8BitmapFH = msAPI_FCtrl_FileOpen(&stFileEntry, OPEN_MODE_BINARY_FOR_READ);
    if(u8BitmapFH == INVALID_FILE_HANDLE)
    {
        printf("N51FS_Bitmap_ClusterFreeFromFHID cannot open bitmap file\n");
        __ASSERT(0);
        return 0;
    }

    pFileHandle = N51FS_File_GetHandleXData(u8BitmapFH);
    u8fsid = pFileHandle->u8FileSystemID;
    u32StartVCN = pFileHandle->StartVCN;
    u32LastVCN = pFileHandle->LastVCN;
    N51FS_ReturnXData();

    printf("N51FS_Bitmap_ClusterFreeFromFHID : u32StartVCN = %lu \n", u32StartVCN);
    printf("N51FS_Bitmap_ClusterFreeFromFHID : u32LastVCN = %lu \n", u32LastVCN);


    u32PrevLCN = N51FS_File_MapVCN2LCN(u8BitmapFH, i, &u32EndVCN);
    printf("N51FS_Bitmap_ClusterFreeFromFHID : u32StartLCN = %lu \n", u32PrevLCN);
    for(i = u32StartVCN + 1; i < u32LastVCN; i++)
    {
        u32CurrentLCN = N51FS_File_MapVCN2LCN(u8BitmapFH, i, &u32EndVCN);
        if(u32PrevLCN + 1 != u32CurrentLCN)
            printf("N51FS_Bitmap_ClusterFreeFromFHID : %lu th LNC = %lu, u32EndVCN = %lu \n", i, u32LastVCN, u32EndVCN);
        u32PrevLCN = u32CurrentLCN;

    }
    printf("N51FS_Bitmap_ClusterFreeFromFHID : u32EndLCN = %lu \n", u32CurrentLCN);

/*
    pBuffer = msAPI_FS_Memory_Allocate(512);
    if(pBuffer == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    for(u32CurrentVCN = u32StartVCN; u32CurrentVCN < u32LastVCN; u32CurrentVCN = u32EndVCN)
    {
        U32 u32BitmapPos;
        u32CurrentLCN = N51FS_File_MapVCN2LCN(u8fhid, u32CurrentVCN, &u32EndVCN);
        u32BitmapPos = u32CurrentLCN >> 8;
        for(i = 0; i < u32EndVCN - u32CurrentVCN ; i++)
        {
            //update u32CurrentLCN + i
        }
    }

    N51FS_ReturnXData();

    msAPI_FS_Memory_Free(pBuffer);
    // 2. seek and clear bit in u8fhid.
*/
}
#endif


/*************************************************************************************************************/
#undef MSAPI_N51FS_C

