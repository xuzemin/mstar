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
#define N51FS_FILE_C

#include "datatype.h"
#include "debug.h"

#include "N51FS_File.h"
#include "msAPI_FCtrl.h"
#include "msAPI_N51FS.h"
#include "msAPI_FS_SysInfo.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_Memory.h"


#define NFL_DBG(flag,x)  //{if(flag){x;}}


typedef struct
{
    U32 MappedLCN;
    U32 BeginVCN;
    U32 EndVCN;
}VCNMapResult;

static N51FS_FileHandle* pFileHandle;

N51FS_FileHandle* N51FS_File_GetHandleInfo(U8 fileHandleID)
{
    return (N51FS_FileHandle xdata*)msAPI_FS_GetAddr(FILE_HANDLE_POOL+FILE_HANDLE_MEMORY_SIZE*fileHandleID);
}

U32* N51FS_File_GetDataAttributeInfo(U8 fileHandleID)
{
    return (U32 xdata*)msAPI_FS_GetAddr(FILE_HANDLE_POOL+FILE_HANDLE_MEMORY_SIZE*fileHandleID+memoffset_FileDataAttribute);
}

U32 N51FS_File_GetDataAttributeXDataMIUAddress(U8 fileHandleID)
{
    return FILE_HANDLE_POOL+FILE_HANDLE_MEMORY_SIZE*fileHandleID+memoffset_FileDataAttribute;
}

static BOOLEAN N51FS_SearchDataAttribute( N51FS_FileHandle* pCurrentFileHandle, U8 fhid, EN_ATTRIBUTE_TYPE tp,
                     U32 lowestVCN, N51FS_AttributeInfo *pInfo, U32 *pOffset)
{
    U32 size;
    N51FS_AttributeInfo info;
    U32 u32DataOffset;
    U16 u16Temp = 0;;

    if(pInfo == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    memset(pInfo, 0, sizeof(*pInfo));

    size = N51FS_ReadMFTRecord(pCurrentFileHandle->u8FileSystemID,   pCurrentFileHandle->MFTReference, USB_IO_TEMP_ADDR);
    if(size == 0)
    {
        __ASSERT(0);
        return FALSE;
    }
    msAPI_FS_MIU_Copy( USB_IO_TEMP_ADDR + 0x14, GET_DRAM_ADDR(&u16Temp), 2 );
    u32DataOffset = (U32)((u16Temp));

    u16Temp = 0;

    info=N51FS_Attribute_Find(pCurrentFileHandle->u8FileSystemID, USB_IO_TEMP_ADDR + u32DataOffset, N51FS_File_GetDataAttributeXDataMIUAddress(fhid),tp, &u16Temp, lowestVCN);
    if(info.Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }
     u32DataOffset = u32DataOffset + u16Temp;
     if(pOffset)
          *pOffset = u32DataOffset;
     if(pInfo)
         *pInfo = info;
     return TRUE;

}

U32 N51FS_File_MapVCN2LCN(U8 fhid,U32 VCN, U32* lowerboundaryVCN, U32* boundaryVCN,
    U32 tp, BOOLEAN *pFound)
{
    U8 i;
    U8 bCanSearchBack = 1;
    U8 offsetField;
    U8 lengthField;
    U32 resultLCN;
    U32 eVCN=0;
    U32 sVCN;
    U8* ptr;
    N51FS_NonResidentAttrHead* phead;
    N51FS_FileHandle *pCurrentFileHandle;

    pCurrentFileHandle=N51FS_File_GetHandleInfo(fhid);
    *pFound = TRUE;

 TRY_AGAIN:

    phead=(N51FS_NonResidentAttrHead*)N51FS_File_GetDataAttributeInfo(fhid);

    if(phead->OffsetToDataRuns==0)
    {
        __ASSERT(0);
        *pFound = FALSE;
        return 0;
    }
    resultLCN = 0;

    if(VCN< phead->StartVCN)
    {
           if(bCanSearchBack)
           {
                 bCanSearchBack = 0;
                 goto Search_Attribute;
           }
           MS_DEBUG_MSG(printf("error, failed to map runlist for VCN %08x\n", VCN));
           __ASSERT(0);
           *pFound = FALSE;
           return 0;
    }

    ptr=(U8*)phead+phead->OffsetToDataRuns;

    NFL_DBG(0,printf("Run List:");dumpMIU(N51FS_File_GetDataAttributeXDataMIUAddress(fhid)+phead->OffsetToDataRuns,16););

    sVCN=0;
    eVCN=phead->StartVCN;

    bCanSearchBack = 0;

    while(TRUE)
    {
        S32 offsetToPrevious=0;
        U32 clength=0;
        U8  inhole = 0;

        sVCN=eVCN;

        if(ptr[0]==0)
        {

             if(sVCN <= VCN)
                 goto Search_Attribute;
             MS_DEBUG_MSG(printf("error, failed to map runlist for VCN %08x\n", VCN));
             __ASSERT(0);
             *pFound = FALSE;
             return 0;
        }
        lengthField=ptr[0]&0x0F;
        offsetField=(ptr[0]&0xF0)>>4;

        if(lengthField>4||offsetField>4)
        {
            __ASSERT(0);// can not support
            *pFound = FALSE;
            return 0;
        }

        for(i=0;i<lengthField;i++)
            clength=(clength<<8)|ptr[1+lengthField-1-i];


        eVCN+=clength;

        if(offsetField>0)
        {
            if(ptr[lengthField+offsetField]&0x80)
                offsetToPrevious=-1;

            for(i=0;i<offsetField;i++)
                offsetToPrevious=(offsetToPrevious<<8)|ptr[1+lengthField+offsetField-1-i];


            resultLCN+=offsetToPrevious;
             NFL_DBG(0,printf("offsetToPrevious=%ld\n",offsetToPrevious););
             inhole = 0;
        }
        else
        {
              NFL_DBG(0,printf("--runlist hole at %08x(%d), %d\n", sVCN, eVCN-sVCN));
              inhole = 1;
        }

        NFL_DBG(0,printf("resultLCN=0x%08lx, sVCN=0x%08lx, eVCN=0x%08lx\n",resultLCN,sVCN,eVCN););
        if(sVCN<=VCN&&VCN<eVCN)
        {
            if(inhole)
            {
                   MS_DEBUG_MSG(printf("found hole\n"));
                   resultLCN = 0;
            }
            else
                   resultLCN+=(VCN-sVCN);
            *lowerboundaryVCN = sVCN;
            *boundaryVCN=eVCN;
            break;  //found!!
        }

        ptr=(U8*)ptr+1+offsetField+lengthField;
    }

    NFL_DBG(0,printf("VCN:0x%02lx Mapped To LCN:0x%08lx\n",VCN,resultLCN););
    return resultLCN;

Search_Attribute:
    if(N51FS_SearchDataAttribute(pCurrentFileHandle, fhid, (EN_ATTRIBUTE_TYPE)tp,
                            eVCN, NULL, NULL))
   {
            //phead=(N51FS_NonResidentAttrHead*)N51FS_File_GetDataAttributeInfo(fhid);
            goto TRY_AGAIN;
    }
    __ASSERT(0);
    *pFound = FALSE;
    return 0;
}



BOOLEAN N51FS_File_OpenFileRecord(U8 fhid,U32 MFR)
{
    U8 fsid;
    U32* pData;
    U32 u32DataOffset;
    U32 u32BeginVCN=0;
    U32 u32EndVCN=0;
    N51FS_AttributeInfo info;
    N51FS_ResidentAttrHead *pHead;
    BOOLEAN bFound;

    BOOLEAN dataResidented=FALSE;

    pFileHandle=N51FS_File_GetHandleInfo(fhid);

    fsid=pFileHandle->u8FileSystemID;
    pFileHandle->MFTReference=MFR;


    if(!N51FS_SearchDataAttribute(pFileHandle, fhid, ATTR_TYPE_DATA, 0, &info, &u32DataOffset))
    {
        __ASSERT(0);
        return FALSE;
    }

    pData=N51FS_File_GetDataAttributeInfo(fhid);

    N51FS_Attribute_SwapAttrHead(pData);
    pHead=(N51FS_ResidentAttrHead*)pData;

    //We don't support N51FS compressed file.
    if(pHead->Flags & 0x0001)
    {
        MS_DEBUG_MSG(printf("We are trying to support N51FS compressed file......\n"););
//        return FALSE;
    }

    //printf("DataAttribute!!");dumpMIU(N51FS_File_GetDataAttributeXDataMIUAddress(fhid),8);
    u32DataOffset = u32DataOffset + pHead->OffsetToAttr;
    dataResidented=(BOOLEAN)(pHead->NonResidentFlag==0);


    pFileHandle=N51FS_File_GetHandleInfo(fhid);

    pFileHandle->DataResidented=dataResidented;
    LL_assign(&pFileHandle->CurrentBytePosition_LL,0);

    if(dataResidented)
    {
        pFileHandle->StartDataOffset = u32DataOffset;
    }
    else
    {
        N51FS_NonResidentAttrHead *pNonResAttr = (N51FS_NonResidentAttrHead *)pHead;
        pFileHandle->TotalVCN = pNonResAttr->LastVCN + 1;       //~!~
        pFileHandle->CurrentStartLCN = N51FS_File_MapVCN2LCN(fhid, 0, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);
        pFileHandle->NextStartVCN = u32EndVCN;
        pFileHandle->CurrentSectorNo = 0;
        pFileHandle->CurrentVCN =  0;
        pFileHandle->CurrentRunLength = u32EndVCN - u32BeginVCN;

        //~!~
        //get compress meta data
        if(pHead->Flags & 0x0001)
            pFileHandle->u8CompressFlag = 1;
        else
            pFileHandle->u8CompressFlag = 0;
    }
    return TRUE;

}

U32 N51FS_FileRead_Residented(U8 fhid, U32 destMIUAddr,U32 len)
{
    N51FS_FileSysStruct* pfst;
    U8 u8SectorPerCluster;
    U16 u16BytePerSector;
    U32 u32MFR;
    U32 u32RecordLSN;
    U8 u8DeviceIndex;
    U32 u32OriginalReadByte = len;
    U32 u32StartSector;
    U32 u32ProcessByteLength = 0;
    U32 u32ReadSectorCnt;
    U32 u32ReadByteCnt;
    U8 fsid;
    U8 *pu8Data;
    U16 u16SizeOfUSA;//Size in words of Update Sequence Array
    U8 *pu8USA;    //Update Sequence Array
    U8 i=1;

    pFileHandle=N51FS_File_GetHandleInfo(fhid);

    u32MFR = pFileHandle->MFTReference;
    fsid = pFileHandle->u8FileSystemID;

    pfst = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid );

    u8SectorPerCluster = pfst->SectorsPerCluster;
    u16BytePerSector = pfst->BytesPerSector;
    u8DeviceIndex = pfst->DeviceIndex;
    u32RecordLSN = pfst->RelativeSector + N51FS_ReadMFT_LSN(fsid, u32MFR);

    if (pFileHandle->CurrentBytePosition_LL.Lo >= pFileHandle->FileSize_LL.Lo)
    {
        return u32OriginalReadByte;
    }

    if(len + pFileHandle->CurrentBytePosition_LL.Lo > pFileHandle->FileSize_LL.Lo)
    {
        len = pFileHandle->FileSize_LL.Lo-pFileHandle->CurrentBytePosition_LL.Lo ;
    }
    //read Update Sequence Array
    if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,u32RecordLSN, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
    }
    pu8Data=(U8 *)(USB_IO_TEMP_ADDR);
    memcpy(&u16SizeOfUSA,&pu8Data[0x6],2);
    pu8USA=(U8 *)msAPI_Memory_Allocate(u16SizeOfUSA*2,BUF_ID_FILECNTL);
    if(pu8USA == NULL)
    {
        __ASSERT(0);
        return 0;
    }
    memcpy(pu8USA,&pu8Data[0x30],u16SizeOfUSA*2);

    //read head sector
    u32ReadByteCnt = (pFileHandle->StartDataOffset + pFileHandle->CurrentBytePosition_LL.Lo ) % u16BytePerSector;
    if(u32ReadByteCnt)
    {
        u32ReadByteCnt = u16BytePerSector - u32ReadByteCnt;
        if(u32ReadByteCnt > len)
        {
            u32ReadByteCnt = len;
        }
        u32StartSector = u32RecordLSN + (pFileHandle->StartDataOffset + pFileHandle->CurrentBytePosition_LL.Lo )/u16BytePerSector;
        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            msAPI_Memory_Free(pu8USA,BUF_ID_FILECNTL);
            return (u32OriginalReadByte - u32ProcessByteLength);
        }
        msAPI_FS_MIU_Copy (USB_IO_TEMP_ADDR + (pFileHandle->StartDataOffset + pFileHandle->CurrentBytePosition_LL.Lo ) % u16BytePerSector, destMIUAddr, u32ReadByteCnt);
        //Check Update Sequence Number
        pu8Data=(U8 *)(destMIUAddr);
        if((pu8Data[u32ReadByteCnt-2]!=pu8USA[0] || pu8Data[u32ReadByteCnt-1]!=pu8USA[1]) &&
           (u32ReadByteCnt+pFileHandle->StartDataOffset == u16BytePerSector))
        {
            __ASSERT(0);
        }
        else if(u32ReadByteCnt+pFileHandle->StartDataOffset == u16BytePerSector)
        {
            pu8Data[u32ReadByteCnt-2]=pu8USA[i*2];
            pu8Data[u32ReadByteCnt-1]=pu8USA[i*2+1];
            i++;
        }
        u32ProcessByteLength = u32ReadByteCnt;
        pFileHandle->CurrentBytePosition_LL.Lo  += u32ReadByteCnt;
    }

    //read remain data
    while(u32ProcessByteLength  + u16BytePerSector <= len )
    {
        u32StartSector = u32RecordLSN + (pFileHandle->StartDataOffset + pFileHandle->CurrentBytePosition_LL.Lo )/u16BytePerSector;
        u32ReadSectorCnt = (len - u32ProcessByteLength) / u16BytePerSector;
        u32ReadByteCnt = u32ReadSectorCnt * u16BytePerSector;
        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, u32ReadSectorCnt, destMIUAddr + u32ProcessByteLength))
        {
            __ASSERT(0);
            pFileHandle->CurrentBytePosition_LL.Lo  += u32ReadByteCnt;
            msAPI_Memory_Free(pu8USA,BUF_ID_FILECNTL);
            return (u32OriginalReadByte - u32ProcessByteLength);
        }
        //Check Update Sequence Number
        pu8Data=(U8 *)(destMIUAddr + u32ProcessByteLength);
        if(pu8Data[u32ReadByteCnt-2]!=pu8USA[0] || pu8Data[u32ReadByteCnt-1]!=pu8USA[1])
        {
            __ASSERT(0);
        }
        else
        {
            pu8Data[u32ReadByteCnt-2]=pu8USA[i*2];
            pu8Data[u32ReadByteCnt-1]=pu8USA[i*2+1];
            i++;
        }
        u32ProcessByteLength += u32ReadByteCnt;
        pFileHandle->CurrentBytePosition_LL.Lo  += u32ReadByteCnt;
    }

    //read tail sector
    if(u32ProcessByteLength < len)
    {
        u32StartSector = u32RecordLSN + (pFileHandle->StartDataOffset + pFileHandle->CurrentBytePosition_LL.Lo )/u16BytePerSector;
        u32ReadByteCnt = len - u32ProcessByteLength;

        //sector read
        if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
            u32StartSector, 1, USB_IO_TEMP_ADDR))
        {
            __ASSERT(0);
            msAPI_Memory_Free(pu8USA,BUF_ID_FILECNTL);
            return (u32OriginalReadByte - u32ProcessByteLength);
        }
        msAPI_FS_MIU_Copy (USB_IO_TEMP_ADDR, destMIUAddr + u32ProcessByteLength, u32ReadByteCnt);
        u32ProcessByteLength += u32ReadByteCnt;
        pFileHandle->CurrentBytePosition_LL.Lo  += u32ReadByteCnt;
    }

    msAPI_Memory_Free(pu8USA,BUF_ID_FILECNTL);
    return u32OriginalReadByte - u32ProcessByteLength;
}


U32 N51FS_FileRead_NonResidented(U8 fhid, U32 destMIUAddr,U32 len)
{
    N51FS_FileSysStruct* pFileSys;
    U8 u8DeviceIndex;
    U32 u32PhysicalStartSector;
    U16 u16BytePerSec;
    U8 u8SecPerClus;
    U32 u32ReadByteCnt;
    U32 u32OriginalReadByte = len;
    U32 u32StartSector;
    U32 u32EndVCN, u32BeginVCN;
    U32 u32RemainSectorNum;
    U32 u32ReadSectorCnt;
    U32 u32ProcessByteLength = 0;
    U8  u8BitCountPerSector;
    LongLong tmpLL;
    LongLong LL_RemainByte;
    LongLong LL_ReadByteCnt;
    BOOLEAN bFound;
    LL_ReadByteCnt.Hi=0;
    LL_ReadByteCnt.Lo=0;

    pFileHandle=N51FS_File_GetHandleInfo(fhid);

    pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(pFileHandle->u8FileSystemID);

    u8DeviceIndex = pFileSys->DeviceIndex;
    u32PhysicalStartSector = pFileSys->RelativeSector;
    u16BytePerSec = pFileSys->BytesPerSector;
    u8SecPerClus = pFileSys->SectorsPerCluster;
    u8BitCountPerSector=pFileSys->BitCountPerSector;

    if (LL_greater_or_equal(&pFileHandle->CurrentBytePosition_LL,&pFileHandle->FileSize_LL))
    {
        return u32OriginalReadByte;
    }

    tmpLL=LL_add(&pFileHandle->CurrentBytePosition_LL,len);
    if(LL_greater(&tmpLL,&pFileHandle->FileSize_LL))
    {
        //is it correct??
        //len = pFileHandle->CurrentBytePosition - pFileHandle->FileSize;
        len=LL_subtractLong(&pFileHandle->FileSize_LL,&pFileHandle->CurrentBytePosition_LL).Lo;
    }

    //read head sector
    u32ReadByteCnt = pFileHandle->CurrentBytePosition_LL.Lo % u16BytePerSec;
    if(u32ReadByteCnt)
    {
        u32ReadByteCnt = u16BytePerSec - u32ReadByteCnt;
        if(u32ReadByteCnt > len)
        {
            u32ReadByteCnt = len;
        }
        u32StartSector = u32PhysicalStartSector + (pFileHandle->CurrentStartLCN + pFileHandle->CurrentVCN) * u8SecPerClus + pFileHandle->CurrentSectorNo;
        //sector read
        if(pFileHandle->CurrentStartLCN)
        {
                if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
                                              u32StartSector, 1, USB_IO_TEMP_ADDR))
                {
                            __ASSERT(0);
                   return (u32OriginalReadByte - u32ProcessByteLength);
                 }
                 msAPI_FS_MIU_Copy (USB_IO_TEMP_ADDR + pFileHandle->CurrentBytePosition_LL.Lo % u16BytePerSec, destMIUAddr, u32ReadByteCnt);
       }
       else
       {
                 NFL_DBG(0,printf("fill hole with zero 0\n"));
                 memset ((void*)destMIUAddr, 0, u32ReadByteCnt);
       }

        u32ProcessByteLength = u32ReadByteCnt;
        pFileHandle->CurrentBytePosition_LL = LL_add(&pFileHandle->CurrentBytePosition_LL,u32ReadByteCnt);

        //get next sector
        if(u32ProcessByteLength < len ||
           ( pFileHandle->CurrentBytePosition_LL.Lo % u16BytePerSec == 0 &&
             LL_greater(&pFileHandle->FileSize_LL,&pFileHandle->CurrentBytePosition_LL)
           ))
        {
            pFileHandle->CurrentSectorNo++;
            if (  pFileHandle->CurrentSectorNo == u8SecPerClus )
            {
                pFileHandle->CurrentSectorNo = 0;
                pFileHandle->CurrentVCN++;
                if(pFileHandle->CurrentVCN >= pFileHandle->CurrentRunLength)
                {
                    pFileHandle->CurrentVCN = 0;
                    pFileHandle->CurrentStartLCN = N51FS_File_MapVCN2LCN(fhid, pFileHandle->NextStartVCN, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);

                    if(bFound == FALSE)
                    {
                       ASSERT(0);
                       return (u32OriginalReadByte - u32ProcessByteLength);
                    }
                    pFileHandle->CurrentRunLength = u32EndVCN - pFileHandle->NextStartVCN;
                    pFileHandle->NextStartVCN = u32EndVCN;
                }
            }
        }
    }

    //read remain data
    while(u32ProcessByteLength  + u16BytePerSec <= len )
    {
        u32StartSector = u32PhysicalStartSector + (pFileHandle->CurrentStartLCN + pFileHandle->CurrentVCN) * u8SecPerClus + pFileHandle->CurrentSectorNo;
        u32RemainSectorNum = (u8SecPerClus - pFileHandle->CurrentSectorNo);
        u32RemainSectorNum += u8SecPerClus * (pFileHandle->CurrentRunLength - pFileHandle->CurrentVCN - 1);

        LL_ReadByteCnt.Lo = len - u32ProcessByteLength;
        LL_RemainByte=LL_multU32(u32RemainSectorNum,(U32)u16BytePerSec);
        if(LL_greater(&LL_RemainByte,&LL_ReadByteCnt))
        {
            u32ReadSectorCnt = LL_ReadByteCnt.Lo/u16BytePerSec;
            LL_ReadByteCnt.Lo = u32ReadSectorCnt * u16BytePerSec;
            pFileHandle->CurrentVCN += u32ReadSectorCnt / u8SecPerClus;
            pFileHandle->CurrentSectorNo += u32ReadSectorCnt % u8SecPerClus;
            if(pFileHandle->CurrentSectorNo >= u8SecPerClus)
            {
                pFileHandle->CurrentVCN++;
                pFileHandle->CurrentSectorNo -= u8SecPerClus;
            }
            //sector read
            if(pFileHandle->CurrentStartLCN)
            {
                  if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
                            u32StartSector, u32ReadSectorCnt, destMIUAddr + u32ProcessByteLength))
                 {
                            __ASSERT(0);
                            pFileHandle->CurrentBytePosition_LL=LL_add(&pFileHandle->CurrentBytePosition_LL,u32ReadByteCnt);
                            return (u32OriginalReadByte - u32ProcessByteLength);
                   }
            }
            else
            {
                   NFL_DBG(0,printf("fill hole with zero 1\n"));
                   memset ((void*)(destMIUAddr+u32ProcessByteLength), 0, u32ReadSectorCnt*u16BytePerSec);
            }

            u32ProcessByteLength += LL_ReadByteCnt.Lo;
            pFileHandle->CurrentBytePosition_LL=LL_add(&pFileHandle->CurrentBytePosition_LL,LL_ReadByteCnt.Lo);
        }
        else
        {
            LL_ReadByteCnt.Lo = u32RemainSectorNum * u16BytePerSec;
            u32ReadSectorCnt = u32RemainSectorNum;

            //sector read
             if(pFileHandle->CurrentStartLCN)
            {
                    if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
                              u32StartSector, u32ReadSectorCnt, destMIUAddr + u32ProcessByteLength))
                    {
                             __ASSERT(0);
                           pFileHandle->CurrentBytePosition_LL=LL_add(&pFileHandle->CurrentBytePosition_LL,u32ReadByteCnt);
                          return (u32OriginalReadByte - u32ProcessByteLength);
                    }
            }
            else
            {
                    NFL_DBG(0,printf("fill hole with zero 2\n"));
                    memset ((void*)(destMIUAddr+u32ProcessByteLength), 0, u32ReadSectorCnt*u16BytePerSec);
            }

            u32ProcessByteLength += LL_ReadByteCnt.Lo;
            pFileHandle->CurrentBytePosition_LL=LL_add(&pFileHandle->CurrentBytePosition_LL,LL_ReadByteCnt.Lo);

            //get next cluster chain
            if(u32ProcessByteLength < len || LL_greater(&pFileHandle->FileSize_LL,&pFileHandle->CurrentBytePosition_LL))
            {
                pFileHandle->CurrentSectorNo = 0;
                pFileHandle->CurrentVCN = 0;
                pFileHandle->CurrentStartLCN = N51FS_File_MapVCN2LCN(fhid, pFileHandle->NextStartVCN, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);
                if(bFound == FALSE)
                {
                    ASSERT(0);
                    return (u32OriginalReadByte - u32ProcessByteLength);
                }
                pFileHandle->CurrentRunLength = u32EndVCN - pFileHandle->NextStartVCN;
                pFileHandle->NextStartVCN = u32EndVCN;
            }
        }
    }

    //read tail sector
    if(u32ProcessByteLength < len)
    {
        u32StartSector = u32PhysicalStartSector + (pFileHandle->CurrentStartLCN + pFileHandle->CurrentVCN) * u8SecPerClus + pFileHandle->CurrentSectorNo;
        u32ReadByteCnt = len - u32ProcessByteLength;

        //sector read
        if(pFileHandle->CurrentStartLCN)
        {
                 if ( !msAPI_MSDCtrl_SectorRead( u8DeviceIndex,
                                            u32StartSector, 1, USB_IO_TEMP_ADDR))
                  {
                              __ASSERT(0);
                              return (u32OriginalReadByte - u32ProcessByteLength);
                   }
                   msAPI_FS_MIU_Copy (USB_IO_TEMP_ADDR, destMIUAddr + u32ProcessByteLength, u32ReadByteCnt);
        }
        else
        {
               NFL_DBG(0, printf("fill hole with zero 3\n"));
               memset ((void*)(destMIUAddr + u32ProcessByteLength), 0, u32ReadByteCnt);
        }

        u32ProcessByteLength += u32ReadByteCnt;
        pFileHandle->CurrentBytePosition_LL=LL_add(&pFileHandle->CurrentBytePosition_LL,u32ReadByteCnt);
    }

    return u32OriginalReadByte - u32ProcessByteLength;

}

#if SUPPORT_COMPRESS

#define N51FS_CB_SIZE 0x10000
#define N51FS_CB_SIZE_BITS    16
#define N51FS_CB_CLUSTERS 16
#define N51FS_SB_SIZE_MASK  0x0fff
#define N51FS_SB_SIZE       0x1000
#define N51FS_COMPRESSED_ATTR   0x8000

typedef enum
{
    N51FS_SYMBOL    =   0,
    N51FS_PHRASE    =   1,
    N51FS_TOKEN_NUM,
} N51FS_TOKEN;



#define DECOMPRESS_DEBUG(x)    //x
#define DECOMPRESS_MINOR_DEBUG(x)    //x


/**
 * N51FS_Decompress
 *
 * Decompress a compress block
 *
 *
 * Return -1 on errors ; return 0 on success
 */
static S32 N51FS_Decompress(U8 *pu8Dest, const U32 u32Dest_Size, U8 *const pu8CB_Start, const U32 u32CB_Size)
{
    U8 *pu8CB = pu8CB_Start;
    U8 *pu8CB_End = pu8CB_Start + u32CB_Size;
    U8 *pu8Dest_End = pu8Dest + u32Dest_Size;

    U8 *pu8CB_SB_Start,*pu8CB_SB_End;
    U8 *pu8Dest_SB_Start,*pu8Dest_SB_End;

    U8 u8Tag;
    S32 s32Token;

      //for address alignment issue
      U16 *pu16CB_Temp;
      U8 u8Tempp[2] = {0};

      DECOMPRESS_DEBUG(printf("\n\n**********************************begin****************************************************** \n"););

      DECOMPRESS_DEBUG(printf("pu8CB_Start=%x,u32CB_Size=%d,pu8CB_End=%x  :  pu8Dest=%x,u32Dest_Size=%d,pu8Dest_End=%x \n",pu8CB_Start,u32CB_Size,pu8CB_End,pu8Dest,u32Dest_Size,pu8Dest_End););

decompress_next_sb:

     u8Tempp[0] = pu8CB[0];
     u8Tempp[1] = pu8CB[1];
       pu16CB_Temp = (U16 *)(void *)&u8Tempp;

       DECOMPRESS_DEBUG(printf("pu8CB=%x,pu8CB_End =%x ,*pu16CB_Temp =%d \n",pu8CB,pu8CB_End,*pu16CB_Temp););

    if (pu8CB == pu8CB_End || !(*pu16CB_Temp) || pu8Dest == pu8Dest_End)
            return 0;           //compress succeed

    pu8Dest_SB_Start = pu8Dest;
    pu8Dest_SB_End = pu8Dest + N51FS_SB_SIZE;

    if (pu8Dest_SB_End > pu8Dest_End)
      {
             DECOMPRESS_MINOR_DEBUG(printf("1 pu8Dest_SB_End =%x, pu8Dest_End=%x\n",pu8Dest_SB_End , pu8Dest_End););
        goto compress_fail;
      }

    pu8CB_SB_Start = pu8CB;

       u8Tempp[0] = pu8CB[0];
       u8Tempp[1] = pu8CB[1];
       pu16CB_Temp = (U16 *)(void *)&u8Tempp;

    pu8CB_SB_End = pu8CB_SB_Start + ((U16)(*pu16CB_Temp) & N51FS_SB_SIZE_MASK) + 3;
    if (pu8CB_SB_End > pu8CB_End)
      {
             DECOMPRESS_MINOR_DEBUG(printf("3 pu8CB_SB_End =%x, pu8CB_End =%x \n",pu8CB_SB_End , pu8CB_End););
        goto compress_fail;
    }

       u8Tempp[0] = pu8CB[0];
       u8Tempp[1] = pu8CB[1];
       pu16CB_Temp = (U16 *)(void *)&u8Tempp;

      DECOMPRESS_DEBUG(printf("pu16CB_Temp=%d \n",*pu16CB_Temp););

    if (!((*pu16CB_Temp) & N51FS_COMPRESSED_ATTR))
      {//uncompressed sub-block
        pu8CB += 2;
        if (pu8CB_SB_End - pu8CB != N51FS_SB_SIZE)
            {
                   DECOMPRESS_MINOR_DEBUG(printf("4 *pu16CB_Temp=%d ,pu8CB_SB_End =%x, pu8CB  =%x\n",*pu16CB_Temp,pu8CB_SB_End , pu8CB ););
            goto compress_fail;
        }
             //just copy it
        memcpy(pu8Dest, pu8CB, N51FS_SB_SIZE);
        pu8CB += N51FS_SB_SIZE;
        pu8Dest += N51FS_SB_SIZE;
        goto decompress_next_sb;
    }

    //found compressed block
    pu8CB += 2;
decompress_next_tag:
    if (pu8CB == pu8CB_SB_End)
      {
            if (pu8Dest < pu8Dest_SB_End)
            {//filling sub-block with 0s
                U32 u32ZeroBytes = pu8Dest_SB_End - pu8Dest;

                DECOMPRESS_DEBUG(("filling sub-block with 0s.\n"););

                memset(pu8Dest, 0, u32ZeroBytes);
                pu8Dest += u32ZeroBytes;
            }
        goto decompress_next_sb;        //goto next sub-block
    }

    //check if valid
    if (pu8CB > pu8CB_SB_End || pu8Dest > pu8Dest_SB_End)
      {
             DECOMPRESS_MINOR_DEBUG(printf("5 pu8CB =%x, pu8CB_SB_End =%x,pu8Dest =%x, pu8Dest_SB_End =%x \n",pu8CB , pu8CB_SB_End , pu8Dest , pu8Dest_SB_End););
        goto compress_fail;
    }

    u8Tag = *pu8CB++;
      DECOMPRESS_DEBUG(printf("u8Tag=%d \n",u8Tag););

    for (s32Token = 0; s32Token < 8; s32Token++, u8Tag >>= 1)
      {
        U16 u16Length, u16Non_Overlap_Len,u16Lengthmask,u16DShift,u16Temp,i;
        U8 *pu8Dest_Back_Addr;

        if (pu8CB >= pu8CB_SB_End || pu8Dest > pu8Dest_SB_End)
            break;

             //if it is symbol token, just copy it,
        if ((u8Tag & (N51FS_TOKEN_NUM - 1)) == N51FS_SYMBOL)
            {
            *pu8Dest++ = *pu8CB++;
            continue;
        }

            //else, walk back to get the dest string

        if (pu8Dest == pu8Dest_SB_Start)
             {
               DECOMPRESS_MINOR_DEBUG(printf("6 pu8Dest =%x, pu8Dest_SB_Start =%x \n",pu8Dest , pu8Dest_SB_Start););
            goto compress_fail;
             }

            //from ntfs-doc
            for(i=pu8Dest - pu8Dest_SB_Start-1,u16Lengthmask=0xFFF,u16DShift=12;i>=0x10;i>>=1)
            {
                u16Lengthmask >>= 1;       //length mask
                u16DShift--;                    //for calculating back-address offset
            }

             u8Tempp[0] = pu8CB[0];
             u8Tempp[1] = pu8CB[1];
             pu16CB_Temp = (U16 *)(void *)&u8Tempp;

        u16Temp = *pu16CB_Temp;

            pu8Dest_Back_Addr = pu8Dest - (u16Temp >> u16DShift) - 1;       //calculate back-address

        if (pu8Dest_Back_Addr < pu8Dest_SB_Start)
             {
                   DECOMPRESS_MINOR_DEBUG(printf("7 pu8Dest_Back_Addr =%x, pu8Dest_SB_Start =%x, pu8Dest=%x,u16Lengthmask=%d,u16DShift=%d,u8Tag=%d\n",pu8Dest_Back_Addr , pu8Dest_SB_Start,pu8Dest,u16Lengthmask,u16DShift,u8Tag););
            goto compress_fail;
             }

             u16Length = (u16Temp & u16Lengthmask) + 3;

        if (pu8Dest + u16Length > pu8Dest_SB_End)
            {
                   DECOMPRESS_MINOR_DEBUG(printf("8 dest =%x, u16Length =%d, dest_sb_end =%x",pu8Dest , u16Length , pu8Dest_SB_End););
            goto compress_fail;
            }

        //the length want to copy from previous string
        u16Non_Overlap_Len = pu8Dest - pu8Dest_Back_Addr;
        if (u16Length <= u16Non_Overlap_Len)
             {
                    /*
                    ************
                                                |-----------
                    just copy
                    */
            memcpy(pu8Dest, pu8Dest_Back_Addr, u16Length);
            pu8Dest += u16Length;
        }
            else
            {
                    /*
                    ************
                                  |---------------
                    copy the un-overlapped string frist, then copy the left
                    */
            memcpy(pu8Dest, pu8Dest_Back_Addr, u16Non_Overlap_Len);
            pu8Dest += u16Non_Overlap_Len;
            pu8Dest_Back_Addr += u16Non_Overlap_Len;
            u16Length -= u16Non_Overlap_Len;

                   //copy the left overlapped
            while (u16Length--)
                *pu8Dest++ = *pu8Dest_Back_Addr++;
        }
        pu8CB += 2;
    }
    goto decompress_next_tag;

compress_fail:
    DECOMPRESS_DEBUG(printf("decompress fail"););
    return -1;
}

#define COMPRESSBLOCK_DEBUG(x)  //x;

/**
 * N51FS_CB_Compressed - internal function, do not use
 *
 * This is a very specialised function determining if a cb is compressed or
 * uncompressed.  It is assumed that checking for a sparse cb has already been
 * performed and that the cb is not sparse.  It makes all sorts of other
 * assumptions as well and hence it is not useful anywhere other than where it
 * is used at the moment.  Please, do not make this function available for use
 * outside of n51fs_file.c as it is bound to confuse people and not do what they
 * want.
 *
 * Return TRUE on errors so that the error will be detected later on in the
 * code.  Might be a bit confusing to debug but there really should never be
 * errors coming from here.
 */
static BOOLEAN N51FS_CB_Compressed(U8 fhid,U32 u32BeginVCN,U32 u32EndVCN,U32 u32CurVCN,U32 u32CurLCN, U16 u16CbClusters,U32 u32TotalVCN)
{
    U32 u32RLLen = u32EndVCN - u32BeginVCN - u32CurVCN;
    BOOLEAN bFound;

    COMPRESSBLOCK_DEBUG(printf("u32BeginVCN =%d,u32EndVCN=%d,u32CurLCN=%d,u32TotalVCN=%d,u32CurVCN= %d \n",u32BeginVCN,u32EndVCN,u32CurLCN,u32TotalVCN,u32CurVCN););

    if(!u32CurLCN)  //the simplest case 1: a sparse rl
        return 1;

    //the simplest case 2: the rl contains more than u16CbClusters which are all not sparse
    if(u32CurLCN && (u32RLLen >= u16CbClusters))
        return 0;

recheck:
    u16CbClusters -= u32RLLen;

    u32CurLCN = N51FS_File_MapVCN2LCN(fhid, u32EndVCN, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);
    if(!bFound)
    {
        ASSERT(0);
        return 0;
    }

    COMPRESSBLOCK_DEBUG(printf("[1]u32BeginVCN =%d,u32EndVCN=%d,u32CurLCN=%d,u32TotalVCN=%d,u16CbClusters=%d \n",u32BeginVCN,u32EndVCN,u32CurLCN,u32TotalVCN,u16CbClusters););

    if(!u32CurLCN)
        return 1;

    u32RLLen = u32EndVCN - u32BeginVCN;

    if(u32RLLen < u16CbClusters)
    {
        if(u32TotalVCN == u32EndVCN)
            return 0;

        goto recheck;
    }
    ASSERT(u32RLLen >= u16CbClusters);

    return 0;
}

U32 N51FS_FileRead_NonResidented_Compress(U8 fhid, U32 destMIUAddr,U32 len)
{
    N51FS_FileSysStruct* pFileSys;
    U8 u8DeviceIndex;
    U32 u32PhysicalStartSector;
    U16 u16BytePerSec,u16BitsCountPerCluster;
    U8 u8SecPerClus;
    U32 u32OriginalReadByte = len;
    U8  u8BitCountPerSector;
    U32 u32_cb_nrs = 0;
    U32 u32EndVCN, u32BeginVCN,u32VCN,u32CurrentRLVCN;
    U32 u32cb_size_mask,offset;

    LongLong tmpLL,tmpLL1;
    BOOLEAN bFound,bCbBlock;
    U32 u32ToRead,u32Total=0,u32ProcessByteLength = 0;
    U32 u32SectorInRUN;
    U32 u32StartSector;
    U32 u32ReadSectorCnt;
    U8  u8EndFlag = 0;
    U32 u32TotalVCN,u32FileStartVCN,u32FileNextVCN,u32FileCurRunLen;

    pFileHandle=N51FS_File_GetHandleInfo(fhid);

    pFileSys = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(pFileHandle->u8FileSystemID);

    u8DeviceIndex = pFileSys->DeviceIndex;
    u32PhysicalStartSector = pFileSys->RelativeSector;
    u16BytePerSec = pFileSys->BytesPerSector;
    u8SecPerClus = pFileSys->SectorsPerCluster;
    u8BitCountPerSector=pFileSys->BitCountPerSector;
    u16BitsCountPerCluster=pFileSys->BitCountPerCluster;

    u32TotalVCN = pFileHandle->TotalVCN;
    u32FileStartVCN = pFileHandle->CurrentVCN;
    u32FileNextVCN = pFileHandle->NextStartVCN;
    u32FileCurRunLen = pFileHandle->CurrentRunLength;

    //!!!!!
    pFileHandle->CurrentSectorNo = 0;

    COMPRESSBLOCK_DEBUG(printf("destMIUAddr=%x,u32PhysicalStartSector=%d,u8DeviceIndex=%d,len=%ld,len1=%x,curLCN=%d,curVCN=%d,NextStartVCN=%d \n",destMIUAddr,u32PhysicalStartSector,u8DeviceIndex,len,len,pFileHandle->CurrentStartLCN,pFileHandle->CurrentVCN,pFileHandle->NextStartVCN););
    COMPRESSBLOCK_DEBUG(printf("curPosHigh=%d,curPosLow=%d,FileLenHigh=%d,FileLenLow=%d \n",pFileHandle->CurrentBytePosition_LL.Hi,pFileHandle->CurrentBytePosition_LL.Lo,pFileHandle->FileSize_LL.Hi,pFileHandle->FileSize_LL.Lo););

    if (LL_greater_or_equal(&pFileHandle->CurrentBytePosition_LL,&pFileHandle->FileSize_LL))
    {//read out of file range, just return
        return u32OriginalReadByte;
    }

    tmpLL=LL_add(&pFileHandle->CurrentBytePosition_LL,len);
    if(LL_greater(&tmpLL,&pFileHandle->FileSize_LL))
    {
        //is it correct??
        //len = pFileHandle->CurrentBytePosition - pFileHandle->FileSize;
        len=LL_subtractLong(&pFileHandle->FileSize_LL,&pFileHandle->CurrentBytePosition_LL).Lo;
    }


//step1:calcute cb_nrs by len
    u32cb_size_mask = N51FS_CB_SIZE - 1;
    tmpLL1.Hi = pFileHandle->CurrentBytePosition_LL.Hi;
    tmpLL1.Lo = pFileHandle->CurrentBytePosition_LL.Lo;
    offset = tmpLL1.Lo & u32cb_size_mask;
    COMPRESSBLOCK_DEBUG(printf("tmpLL1.Hi==%d,tmpLL1.Lo=%d,offset = %d\n",tmpLL1.Hi,tmpLL1.Lo,offset););
    tmpLL1.Lo = pFileHandle->CurrentBytePosition_LL.Lo & ~u32cb_size_mask;
    tmpLL1 = LL_LongDivU32(&tmpLL1,u8SecPerClus*u16BytePerSec);      //
    u32BeginVCN = (tmpLL1.Hi << 31) + tmpLL1.Lo;


    tmpLL=LL_add(&pFileHandle->CurrentBytePosition_LL,len+N51FS_CB_SIZE - 1);
    tmpLL.Hi = pFileHandle->CurrentBytePosition_LL.Hi;
    tmpLL.Lo = tmpLL.Lo & ~u32cb_size_mask;
    COMPRESSBLOCK_DEBUG(printf("tmpLL.Hi==%d,tmpLL.Lo=%d \n",tmpLL.Hi,tmpLL.Lo,offset););
    tmpLL = LL_LongDivU32(&tmpLL,u8SecPerClus*u16BytePerSec);      //
    u32EndVCN = (tmpLL.Hi << 31 ) + tmpLL.Lo;


    u32_cb_nrs = (u32EndVCN - u32BeginVCN) << u16BitsCountPerCluster >>N51FS_CB_SIZE_BITS;
    COMPRESSBLOCK_DEBUG(printf("u32EndVCN = %d, u32BeginVCN = %d ,u32_cb_nrs=%d \n",u32EndVCN,u32BeginVCN,u32_cb_nrs););

    if(u32BeginVCN)
    {//do not read from the beginning of the file
        U32 temp1,temp2;
        u32CurrentRLVCN = N51FS_File_MapVCN2LCN(fhid, u32BeginVCN, &temp1, &temp2, ATTR_TYPE_DATA, &bFound);
        pFileHandle->CurrentVCN = (u32BeginVCN - temp1) & ~15;
        COMPRESSBLOCK_DEBUG(printf("u32BeginVCN = %d , temp1=%d ,temp2 = %d,u32CurrentRLVCN=%d,CurrentVCN=%d \n",u32BeginVCN, temp1,temp2,u32CurrentRLVCN,pFileHandle->CurrentVCN););
        u32BeginVCN = temp1;
    }

do_next_cb:
//step2:for each cb,read it to src buffers
    u32_cb_nrs--;
    u32VCN = u32BeginVCN;
    u32BeginVCN += N51FS_CB_CLUSTERS;

    u32CurrentRLVCN = N51FS_File_MapVCN2LCN(fhid, u32VCN, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);
    pFileHandle->NextStartVCN = u32EndVCN;
    pFileHandle->CurrentRunLength = u32EndVCN - u32BeginVCN;
    pFileHandle->CurrentStartLCN = u32CurrentRLVCN;
    COMPRESSBLOCK_DEBUG(printf("u32CurrentRLVCN=%d, u32VCN=%d,u32BeginVCN=%d, u32EndVCN=%d,bFound=%d \n",u32CurrentRLVCN,u32VCN,u32BeginVCN, u32EndVCN,bFound););
    bCbBlock = N51FS_CB_Compressed(fhid,u32BeginVCN,u32EndVCN,pFileHandle->CurrentVCN,u32CurrentRLVCN, N51FS_CB_CLUSTERS,u32TotalVCN);
    COMPRESSBLOCK_DEBUG(printf("bCbBlock=%d \n",bCbBlock););

    u32ToRead = N51FS_CB_SIZE;
    u32ProcessByteLength = 0;
    while(u32ToRead > 0 && !u8EndFlag)    //read a whole cb block
    {
        COMPRESSBLOCK_DEBUG(printf("##########[befin while] u8EndFlag=%d,CurrentSectorNo=%d \n",u8EndFlag,pFileHandle->CurrentSectorNo););
        u32StartSector = u32PhysicalStartSector + (pFileHandle->CurrentStartLCN + pFileHandle->CurrentVCN) * u8SecPerClus + pFileHandle->CurrentSectorNo;
        u32SectorInRUN = (pFileHandle->CurrentRunLength - pFileHandle->CurrentVCN) * u8SecPerClus;  //total sectors of this runlist
        if(pFileHandle->CurrentSectorNo)
            u32SectorInRUN -= pFileHandle->CurrentSectorNo;       //current run's remaing sector

        u32ReadSectorCnt = MIN(u32SectorInRUN,u32ToRead>>9);    //num of readsector count

        COMPRESSBLOCK_DEBUG(printf("CurrentRunLength=%d,CurrentVCN=%d,CurrentStartLCN=%d,CurrentSectorNo=%d,NextStartVCN=%d \n",pFileHandle->CurrentRunLength,pFileHandle->CurrentVCN,pFileHandle->CurrentStartLCN,pFileHandle->CurrentSectorNo,pFileHandle->NextStartVCN););
        COMPRESSBLOCK_DEBUG(printf("u32ProcessByteLength=%d,u32StartSector=%d,u32SectorInRUN=%d,u32ReadSectorCnt=%d \n",u32ProcessByteLength,u32StartSector,u32SectorInRUN,u32ReadSectorCnt););

        if(!u32CurrentRLVCN)
        {//a sparse runlist
            COMPRESSBLOCK_DEBUG(printf("in sparse run \n"););
            memset((void *)(N51FS_CB_SRC_BUFFER_ADDR + u32ProcessByteLength),0,u32ReadSectorCnt*u16BytePerSec);
        }
        else
        {
            COMPRESSBLOCK_DEBUG(printf("in data run \n"););
            if (!msAPI_MSDCtrl_SectorRead( u8DeviceIndex,u32StartSector, u32ReadSectorCnt, N51FS_CB_SRC_BUFFER_ADDR + u32ProcessByteLength))
            {
                __ASSERT(0);
                //do not updata current position if fail
                //return u32OriginalReadByte;
                goto err_out;
            }
        }

        //update vcn&sector info
        if(u32ReadSectorCnt == u32SectorInRUN)
        {
            COMPRESSBLOCK_DEBUG(printf("pFileHandle->TotalVCN=%d, u32EndVCN=%d \n",pFileHandle->TotalVCN ,u32EndVCN););
            //Todo:if it is end of the data run, do not froward the rl info
/*
            if(0 &&(pFileHandle->TotalVCN <= u32EndVCN))
            {
                pFileHandle->CurrentVCN = pFileHandle->CurrentRunLength;
                pFileHandle->CurrentSectorNo = 0;
                u8EndFlag = 1;
            }
*/
            tmpLL = LL_add(&pFileHandle->CurrentBytePosition_LL, u32ProcessByteLength + u32ReadSectorCnt * u16BytePerSec);
            if( LL_greater(&tmpLL,&pFileHandle->FileSize_LL) )
            {
                COMPRESSBLOCK_DEBUG(printf("tmpLL.lo=%d,hi=%d; filesize.lo=%d,hi=%d \n",tmpLL.Lo,tmpLL.Hi,pFileHandle->FileSize_LL.Lo,pFileHandle->FileSize_LL.Hi););
                pFileHandle->CurrentVCN = pFileHandle->CurrentRunLength;
                pFileHandle->CurrentSectorNo = 0;
                u8EndFlag = 1;
            }
            else
            {
                //forward to next runlist
                pFileHandle->CurrentVCN = 0;
                pFileHandle->CurrentSectorNo = 0;
                u32CurrentRLVCN =  N51FS_File_MapVCN2LCN(fhid, pFileHandle->NextStartVCN, &u32BeginVCN, &u32EndVCN, ATTR_TYPE_DATA, &bFound);
                pFileHandle->NextStartVCN = u32EndVCN;
                pFileHandle->CurrentRunLength = u32EndVCN - u32BeginVCN;
                if(u32CurrentRLVCN)
                    pFileHandle->CurrentStartLCN = u32CurrentRLVCN;
                //else
                //    ;   //sparse rl;

                if(bFound == FALSE)
                {
                    ASSERT(0);
                    goto err_out;
                    //return (u32OriginalReadByte - u32ProcessByteLength);
                }
            }
            COMPRESSBLOCK_DEBUG(printf("u32CurrentRLVCN=%d, u32VCN=%d,u32BeginVCN=%d, u32EndVCN=%d,bFound=%d \n",u32CurrentRLVCN,u32VCN,u32BeginVCN, u32EndVCN,bFound););
        }
        else if(u32ReadSectorCnt == u32ToRead>>9)
        {//read within the runlist, and read it all
            COMPRESSBLOCK_DEBUG(printf("read within the runlist, and read it all, \n"););
//            pFileHandle->CurrentSectorNo += u32ReadSectorCnt;
//            pFileHandle->CurrentSectorNo %= u8SecPerClus;
            pFileHandle->CurrentSectorNo = 0;
            pFileHandle->CurrentVCN += u32ReadSectorCnt/u8SecPerClus;
            COMPRESSBLOCK_DEBUG(printf("CurrentSectorNo=%d,CurrentVCN=%d,u32ReadSectorCnt=%d \n",pFileHandle->CurrentSectorNo,pFileHandle->CurrentVCN,u32ReadSectorCnt););
            ASSERT(pFileHandle->CurrentVCN < pFileHandle->CurrentRunLength);
        }
        else
        {
            ASSERT(0);
        }

        u32ProcessByteLength += u32ReadSectorCnt * u16BytePerSec;
        u32ToRead -= u32ReadSectorCnt * u16BytePerSec;

        COMPRESSBLOCK_DEBUG(printf("u32ProcessByteLength=%d, u32ToRead=%d,u32ReadSectorCnt=%d \n",u32ProcessByteLength, u32ToRead,u32ReadSectorCnt););
        COMPRESSBLOCK_DEBUG(printf("[end while]##########\n"););
    }

    //step3:for each cb, decompress it
    if(bCbBlock && N51FS_Decompress((U8 *)N51FS_CB_DST_BUFFER_ADDR,N51FS_CB_SIZE,(U8 *)N51FS_CB_SRC_BUFFER_ADDR,N51FS_CB_SIZE))
    {
        COMPRESSBLOCK_DEBUG(printf("decompress error! \n"););
    }

    COMPRESSBLOCK_DEBUG(printf("\n\n**********************************end****************************************************** \n"););

    //step4: copy to dest
    u32ToRead = MIN(len,N51FS_CB_SIZE-offset);
    if(bCbBlock)
        msAPI_FS_MIU_Copy(N51FS_CB_DST_BUFFER_ADDR+offset, destMIUAddr, u32ToRead);
    else
        msAPI_FS_MIU_Copy(N51FS_CB_SRC_BUFFER_ADDR+offset, destMIUAddr, u32ToRead);

    u32Total += u32ToRead;
    offset = 0;
    len -= u32ToRead;
    destMIUAddr = destMIUAddr + u32ToRead;
    pFileHandle->CurrentBytePosition_LL = LL_add(&pFileHandle->CurrentBytePosition_LL, u32ToRead);

    COMPRESSBLOCK_DEBUG(printf("u32ToRead=%d,u32Total=%d,len=%d,destMIUAddr=%x,CurrentBytePosition_LL=%d \n",u32ToRead,u32Total,len,destMIUAddr,pFileHandle->CurrentBytePosition_LL.Lo););

    if(u32_cb_nrs)
        goto do_next_cb;

    COMPRESSBLOCK_DEBUG(printf("[return]curLCN=%d,curVCN=%d,NextStartVCN=%d,CurrentRunLength=%d,CurrentSectorNo=%d\n",pFileHandle->CurrentStartLCN,pFileHandle->CurrentVCN,pFileHandle->NextStartVCN,pFileHandle->CurrentRunLength,pFileHandle->CurrentSectorNo););
    return 0;

err_out:
    //!!!todo: reset the file pointer
    printf("N51FS file read compress err out!!!!!! \n");
    return -1;
}
#else
U32 N51FS_FileRead_NonResidented_Compress(U8 fhid, U32 destMIUAddr,U32 len)
{
    ASSERT(0);
    fhid = 0;
    destMIUAddr = 0;
    printf("Not support NTFS with NonResidented Compress format\n");

    return len;
}
#endif

BOOLEAN N51FS_File_CloseFileRecord(U8 fhid)
{
    // Complier Warning
    fhid = fhid;
    return TRUE;
}

#undef N51FS_FILE_C

