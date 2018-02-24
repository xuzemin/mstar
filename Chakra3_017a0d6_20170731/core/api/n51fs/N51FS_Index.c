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
#define N51FS_INDEX_C


#include "datatype.h"
#include "debug.h"

#include "msAPI_FSCommon.h"

#include "msAPI_FCtrl.h"
#include "N51FS_Index.h"
#include "msAPI_N51FS.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FSEnv.h"
#include "msAPI_MIU.h"
#include "msAPI_N51FS.h"
#include "msAPI_Timer.h"
//static U8 code _DUMMY;
#define NIX_DBG(flag,x)  //{if(flag){x;}}


static N51FS_ResidentAttrHead* pIndexRootHead;   //global for local temp
static IndexVars* pIndexVars;       //global for local temp
static IndexRecord* pIndexRecord;  //global for local temp

//static U32 N51FS_Index_NumOfEntries(U8 enId);
U32  N51FS_Index_MapVCN2LCN(U32 u32Addr, U16 u16Offset, U32 VCN);


static void ReOrderIndexEntry(IndexEntryHead* pBuff)
{
    //pBuff->MFTReference = (pBuff->MFTReference);
    //pBuff->MFTReference_H = (pBuff->MFTReference_H);
    //pBuff->EntrySize = (pBuff->EntrySize);
    //pBuff->StreamSize = (pBuff->StreamSize);
    //pBuff->EntryFlag = (pBuff->EntryFlag);
    pBuff->Padding=0;

    if(pBuff->EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        //pBuff->SubNodeVCN = ( *((U32*)((U8*)pBuff + pBuff->EntrySize)) );
        memcpy(&(pBuff->SubNodeVCN),((U8*)pBuff + pBuff->EntrySize),4);
        //pBuff->SubNodeVCN_H = ( *((U32*)((U8*)pBuff + pBuff->EntrySize + 4)) );
        memcpy(&(pBuff->SubNodeVCN_H),((U8*)pBuff + pBuff->EntrySize + 4),4);
    }
}

static void cde_ten(char *p)
{
    U32 lr;
    U32 i=0, j;
    lr=strlen(p);
    while(p[i]=='0')
      ++i;
    if(i>0)
    {
        for(j=0; j<lr-i; ++j)
            p[j]=p[j+i];
        for(j=lr-i; j<lr; ++j)
        {
            p[j]='\0';
        }
    }

    if(p[0]=='\0')
    {
        p[0]='0';
    }
}
static int str_cmp(char *p, char *q)
{
    U32 lr, lu;
    cde_ten(p);
    cde_ten(q);

    lr=strlen(p);
    lu=strlen(q);

    if(lr>lu)
    {
        return 1;
    }
    else if (lr<lu)
    {
        return -1;
    }
    return (strcmp(p, q));
}
static void ssub(char *r, char *u, char *p)
{
    unsigned int i,lr, lu, lp,c=0;
    signed char h,hc;

    lr=strlen(r);
    lu=strlen(u);
    for(i=0; i<lu; ++i)
    {
        h=r[lr-i-1]-u[lu-i-1]-c;
        if(h<0)
        {
            c=1;
            h=h+10;
        }
        else
            c=0;
        p[i]=h+'0';
        hc=h+'0';
    }
    for (i=lu; i<lr; ++i)
    {
        h=r[lr-i-1]-'0'-c;
        if(h<0)
        {
            c=1;
            h=h+10;
        }
        else
            c=0;
        p[i]='0'+h;
        hc='0'+h;
    }
    p[i]='\0';
    lp=i-1;

    while(p[lp]=='0'&&lp!=0)
    {
        p[lp]='\0';
        lp--;
    }

    for(i=0; i<(lp+1)/2; ++i)
    {
        hc=p[i];
        p[i]=p[lp-i];
        p[lp-i]=hc;
    }
    return;
}
static void sdivkr(char *u, int len, char *v, char **rout, char *f)
{
    char  *r, *p;
    unsigned int lu, lv, lr, iw, lp;
    int  kh;
    lu=len;
    lv=strlen(v);

    unsigned int ui_r_mem_alloc_size = (lv+2)*sizeof(char);

    r=(char *)malloc(ui_r_mem_alloc_size);

    if( r == NULL )
        return ;

#if 1 // Clear memory
    memset(r, 0, ui_r_mem_alloc_size );
#else
    for(i=0; i<lv+2; ++i) r[i]='\0';
#endif

    for(iw=0; iw<lu; ++iw)
    {
        cde_ten(r);
        lr=strlen(r);
        r[lr]=u[iw];
        r[lr+1]='\0';
        kh=0;
        while(str_cmp(r, v)>=0)
        {
        //fix coverity error
        #if 0
            if(str_cmp(r, v)<0)
            {
                r = NULL;
            }
            else
        #endif
            {
                lp=strlen(r);
                unsigned int ui_p_mem_alloc_size = (unsigned int)(lp+1)*sizeof(char);
                p=(char *)malloc(ui_p_mem_alloc_size);
                if( p == NULL )
                {
                    free(r);
                    return;
                }
                memset(p, 0, ui_p_mem_alloc_size);

                ssub(r, v, p);

                if( ui_p_mem_alloc_size <= ui_r_mem_alloc_size )
                {
                    memcpy(r, p, ui_p_mem_alloc_size);
                }

                free(p);
            }
            ++kh;
        }
        f[iw]=kh+'0';
    }
    cde_ten(r);
    *rout=r;
    free(r);
    cde_ten(f);
    return;

}
static void ConvLL2Str(unsigned int high,unsigned int low, int *length, char* aa)
{
    int i,j,iLen = 0,m;
    char temp;
    int position;
    int mod = 10;
    int step = 16;

    int c[32] = {0};

    for(i= 0;low > 0;i++)
    {
        m = low & 0xF;
        low >>= 4;
        if(m == 0xF)
            m = 15;
        else if(m == 0x0E)
            m = 14;
        else if(m == 0x0D)
            m = 13;
        else if(m == 0x0C)
            m = 12;
        else if(m == 0x0B)
            m = 11;
        else if(m == 0x0A)
            m = 10;
        c[i] = m;
    }

    while(i < 8 )
        c[i++] = 0;


    for(j= 0;high > 0;j ++)
    {
        m = high & 0xF;
        high >>= 4;
        if(m == 0xF)
            m = 15;
        else if(m == 0x0E)
            m = 14;
        else if(m == 0x0D)
            m = 13;
        else if(m == 0x0C)
            m = 12;
        else if(m == 0x0B)
            m = 11;
        else if(m == 0x0A)
            m = 10;
        c[i++] = m;
    }

    iLen = i;

    i = 0;
    position = iLen - 1;
 while (1)
 {
  while (position >= 0)
  {
   if (c[position] != 0)break;
   else position--;
 }
 if (position < 0)break;

  for ( j = position;j > 0;j--)
  {
   c[j - 1] += (c[j] % mod) * step;
   c[j] = c[j] / mod;
  }
  aa[i++] = c[0] % mod + '0';
  c[0] /= mod;
 }

    iLen = i;
    i = (iLen / 2);
    for(j = 0 ; j < i ; j ++ )
    {
        temp = aa[j];
        aa[j] = aa[iLen - j  - 1];
        aa[iLen - j  - 1] = temp;
    }

    *length = iLen;
    return;
}
static int ConvStr2Int(char *a)
{
    int result = 0;
    int i;
    for(i = 0 ; i < 32 && a[i] != 0; i ++)
    {
        result = result * 10 + (int)(a[i] - '0');
    }
    return result;
}

//(369 * 365 + 89    +   10 *365 + 2) * 86400 * 10000000        //100ns to 1980
#define OFFSET_TO_1980_HI 0x01A8E79F
#define OFFSET_TO_1980_LO 0xE1D58000

static U32 ConvertN51FSTimeTo1980BasedSeconds(U32 Hi,U32 Lo)
{
    LongLong st;
    LongLong _offset;
    char aa[32];
    char *p,*r;
    int len = 0;

    char divider[]="10000000";

    memset(aa, 0, 32);

    st.Hi = Hi;
    st.Lo = Lo;

    _offset.Hi=OFFSET_TO_1980_HI;
    _offset.Lo=OFFSET_TO_1980_LO;
    _offset=LL_subtractLong(&st,&_offset);

    ConvLL2Str(_offset.Hi,_offset.Lo,&len, aa);

    p=(char *)malloc((unsigned int)(len+1)*sizeof(char));

    if( p == NULL )
        return 0;

#if 1 // Clear memory
    memset(p, 0, (len+1) );
#else
    for(i=0; i<len+1; ++i)
        p[i]='\0';
#endif

    sdivkr(aa,len,divider,&r, p);
    _offset.Lo = ConvStr2Int(p);

    free(p);

    return _offset.Lo;

}

static BOOLEAN N51FS_Index_InputRecordFromDisk(U8 fsid, U32 u32RootAddr, U32 u32RunListAddr, U32 u32RecordAddr,
                                              U16 u16OffsetToRunList, U16 u16OffsetToAttr,
                                              U32 VCN)
{

    N51FS_FileSysStruct* pfst;
    U32 _sectorPerCluster;
    U16 _bytesPerSector;
    U32 _physicalStartSector;
    U8 _clustersPerRecord;
    S8 deviceIndex;
    U32 LCN;
    U8 i;
    U8 *pBuff;
    U8 u8ReadSectorCnt;
    U16 u16OffsetToFixUp;
    U16 u16FixUpNum;
    U16 u16SectorLastWord;
    U16 u16FixUpCount;
    U8 u8SectorsPerIndexRecord;

    pfst=(N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    _sectorPerCluster=pfst->SectorsPerCluster;
    _bytesPerSector=pfst->BytesPerSector;
    _physicalStartSector=pfst->RelativeSector;
    deviceIndex=pfst->DeviceIndex;
    u8SectorsPerIndexRecord = pfst->SectorsPerIndexRecord;

    pBuff=(U8 xdata*)msAPI_FS_GetAddr(u32RootAddr);

    _clustersPerRecord=*(pBuff+u16OffsetToAttr+0x0C);

    /* special handle: if sector per cluster > 4K, regard "_clustersPerRecord" as sector */
    if(_sectorPerCluster > u8SectorsPerIndexRecord)
    {
        _clustersPerRecord /= u8SectorsPerIndexRecord;
    }
    //copy IndexRecord to buffer
    for(i = 0; i < _clustersPerRecord; i++)
    {
        if(_sectorPerCluster > u8SectorsPerIndexRecord)
        {
            LCN = N51FS_Index_MapVCN2LCN(u32RunListAddr, u16OffsetToRunList, (VCN/_sectorPerCluster));
            if(!msAPI_MSDCtrl_SectorRead(deviceIndex,_physicalStartSector + (LCN * _sectorPerCluster + (VCN%_sectorPerCluster))
                                     , u8SectorsPerIndexRecord, u32RecordAddr + i * u8SectorsPerIndexRecord*_bytesPerSector))
            {
                __ASSERT(0);
                return FALSE;
            }
        }
        else
        {
            LCN = N51FS_Index_MapVCN2LCN(u32RunListAddr, u16OffsetToRunList, VCN);
            if(!msAPI_MSDCtrl_SectorRead(deviceIndex,_physicalStartSector + LCN * _sectorPerCluster
                                 ,_sectorPerCluster, u32RecordAddr + i * _sectorPerCluster*_bytesPerSector))
            {
                __ASSERT(0);
                return FALSE;
            }
            VCN++;
        }
    }
    //FixUP!!
    pBuff = (U8 xdata*)msAPI_FS_GetAddr(u32RecordAddr);

    u8ReadSectorCnt = (U8)(_clustersPerRecord * _sectorPerCluster);
    //u16OffsetToFixUp = ( *((U16*)&pBuff[0x04]) );
    memcpy(&u16OffsetToFixUp,&pBuff[0x04],2);
    //u16FixUpCount = ( *((U16*)&pBuff[0x06]) );
    memcpy(&u16FixUpCount,&pBuff[0x06],2);
    //u16FixUpNum = *((U16*)&pBuff[u16OffsetToFixUp]);
    memcpy(&u16FixUpNum,&pBuff[u16OffsetToFixUp],2);

    for(i = 1; i <= u8ReadSectorCnt*(_bytesPerSector/NTFS_BLOCK_SIZE); i++)
    {
        if(i >= u16FixUpCount)
        {
            //__ASSERT(0);
            return TRUE;
        }
        //u16SectorLastWord = *(U16 *)(pBuff + i*_bytesPerSector - 2);
        memcpy(&u16SectorLastWord,(pBuff + i*NTFS_BLOCK_SIZE - 2),2);

        if(u16SectorLastWord == u16FixUpNum)
        {
            //*(U16 *)(pBuff + i*_bytesPerSector - 2) = *(U16*)(pBuff + u16OffsetToFixUp + i*2);
            memcpy((pBuff + i*NTFS_BLOCK_SIZE - 2),(pBuff + u16OffsetToFixUp + i*2),2);
        }
        else
        {
            __ASSERT(0);
            return FALSE;
        }

    }
    return TRUE;
}


U32  N51FS_Index_MapVCN2LCN(U32 u32Addr, U16 u16Offset, U32 VCN)
{
    U8 offsetField;
    U8 lengthField;
    U32 resultLCN=0;
    U32 eVCN=0;
    U32 sVCN;
    U8* ptr;

    ptr = (U8 xdata*)msAPI_FS_GetAddr(u32Addr);

    ptr += u16Offset;
     NIX_DBG(0,printf("Run List:");dumpMIU(u32Addr+u16Offset,2););
    //printf("\nRun List:");
    //dumpMIU(N51FS_GetIndexRootXDataMIUAddress(enid)+offsetToRunList,16);
    sVCN=0;
    eVCN=0;
    while(TRUE)
    {
        S32 offsetToPrevious=0;
        U32 clength=0;
        U8 i;

        sVCN=eVCN;

        if(ptr[0]==0)
            break;

        lengthField=ptr[0]&0x0F;
        offsetField=(ptr[0]&0xF0)>>4;
        if(lengthField>4||offsetField>4)
        {
            __ASSERT(0);// can not support
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
             NIX_DBG(0,printf("offsetToPrevious=%ld\n",offsetToPrevious););
        }

         NIX_DBG(0,printf("resultLCN=0x%08lx, sVCN=0x%08lx, eVCN=0x%08lx\n",resultLCN,sVCN,eVCN););
        if(sVCN<=VCN&&VCN<eVCN)
        {
            resultLCN+=(VCN-sVCN);
            break;  //found!!
        }

        ptr=(U8*)ptr+1+offsetField+lengthField;

    }

    NIX_DBG(0,printf("VCN:0x%02lx Mapped To LCN:0x%08lx\n",VCN,resultLCN););
    return resultLCN;
}



static BOOLEAN N51FS_Index_LeaveSubNode(U8 enid)
{
    U32 VCN = 0;
    U16 bytes=0;
    U16 u16OffsetToAttr;

    pIndexRootHead=(N51FS_ResidentAttrHead*)N51FS_GetIndexRootInfo(enid);

    u16OffsetToAttr = pIndexRootHead->OffsetToAttr;

    pIndexVars = N51FS_GetIndexVarsInfo(enid);

    if(pIndexVars->PositionStackCount==0 || pIndexVars->PositionStackCount > POSITION_STACK_SIZE)
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        pIndexVars->PositionStackCount--;
        VCN = pIndexVars->PositionStack[pIndexVars->PositionStackCount].VCN;
        bytes = pIndexVars->PositionStack[pIndexVars->PositionStackCount].Bytes;
    }

    pIndexVars->JustLeaveSubNode = TRUE;

    if(pIndexVars->PositionStackCount > 0)
    {
        if(pIndexVars->OffsetToRunList == 0)
        {
            __ASSERT(0);
            return 0;
        }

        if(!N51FS_Index_InputRecordFromDisk(msAPI_FSEnv_GetEnvironment(enid)->u8FileSystemID,
                                           N51FS_GetIndexRootMIUAddress(enid),
                                           N51FS_GetIndexRootMIUAddress(enid),
                                           N51FS_GetIndexRecordMIUAddress(enid),
                                           pIndexVars->OffsetToRunList, u16OffsetToAttr,
                                           VCN))
        {
            __ASSERT(0);
            return FALSE;
        }
    }

    //current stream reset
    pIndexVars->CurrentRecordStartVCN = VCN;
    pIndexVars->CurrentRecordBytePosition = bytes;
    return TRUE;
}


static BOOLEAN N51FS_Index_GoToSubNode(U8 enid)
{
    U32 subNodeLCN=0;
    U32 subNodeVCN;
    U32 _offsetToIndexEntries;
    U16 u16OffsetToAttr;


    pIndexRootHead=(N51FS_ResidentAttrHead*)N51FS_GetIndexRootInfo(enid);

    u16OffsetToAttr = pIndexRootHead->OffsetToAttr;

    pIndexVars=N51FS_GetIndexVarsInfo(enid);

    if(pIndexVars->OffsetToRunList==0)
    {
        __ASSERT(0);
        return FALSE;
    }
    subNodeVCN = pIndexVars->CurrentIndexEntryHead.SubNodeVCN;
    subNodeLCN = N51FS_Index_MapVCN2LCN(N51FS_GetIndexRootMIUAddress(enid), pIndexVars->OffsetToRunList, subNodeVCN);
    if(subNodeLCN>0)
    {
        //Push current index position
        if(pIndexVars->PositionStackCount>=POSITION_STACK_SIZE)
        {
            __ASSERT(0);
            return FALSE;
        }
        else
        {
            pIndexVars->PositionStack[pIndexVars->PositionStackCount].Bytes = pIndexVars->CurrentRecordBytePosition;
            pIndexVars->PositionStack[pIndexVars->PositionStackCount].VCN = pIndexVars->CurrentRecordStartVCN;
            pIndexVars->PositionStackCount++;
        }



        //Read sub node from disk
        if(!N51FS_Index_InputRecordFromDisk(msAPI_FSEnv_GetEnvironment(enid)->u8FileSystemID,
                                           N51FS_GetIndexRootMIUAddress(enid),
                                           N51FS_GetIndexRootMIUAddress(enid),
                                           N51FS_GetIndexRecordMIUAddress(enid),
                                           pIndexVars->OffsetToRunList, u16OffsetToAttr,
                                           subNodeVCN))
        {
            __ASSERT(0);
            return FALSE;
        }

        //current stream reset
        pIndexVars->CurrentRecordStartVCN = subNodeVCN;
        pIndexVars->CurrentRecordBytePosition=0;

        pIndexRecord=(IndexRecord*)N51FS_GetIndexRecordInfo(enid);

        _offsetToIndexEntries= (pIndexRecord->OffsetToIndexEntries);

        NIX_DBG(0,printf("Goto Index Record at LCN:%lu,offsetToIndexEntries=%lu\n",subNodeLCN,(U32)_offsetToIndexEntries);dumpMIU(N51FS_GetIndexRecordMIUAddress(enid),2););

        pIndexVars->CurrentRecordBytePosition = 0x18 + _offsetToIndexEntries;
        return TRUE;
    }
    return FALSE;

}





/*
    This function will go to the first index in current directory.

    1. Copy the $INDEX_ROOT (also the $INDEX_ALLOCATION and $BITMAP)
       to the memoffset_IndexRoot

 */
BOOLEAN N51FS_Index_ToFirst(U8 enid)
{
    N51FS_Environment *pN51FSenv;
    N51FS_AttributeInfo attrInfo;
    N51FS_AttributeInfo attrInfo2;
    U16 attributeOffset = 0;
    U8 largeIndexFlag = 0;
    U8* tmpXdata;
    U32 u32Temp = 0;
    U16 u16Temp = 0, u16Temp_1 = 0;
    U8 fsid = 0;
    U32 u32MFR = 0;

    pN51FSenv = N51FS_GetEnvironmentInfo(enid);

    fsid = pN51FSenv->FileSystemID;
    u32MFR = pN51FSenv->CurrentDirectoryMFR;

    NIX_DBG(1, printf("Current Directory currentDirMFR=0x%08lx\n", u32MFR););

    if(0 == N51FS_ReadMFTRecord(fsid, u32MFR, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FS_MIU_Copy( USB_IO_TEMP_ADDR + 0x14, GET_DRAM_ADDR(&attributeOffset), 2 );
    attributeOffset = (attributeOffset);

    //get the parent MFR
    attrInfo=N51FS_Attribute_Find(fsid,USB_IO_TEMP_ADDR + attributeOffset, N51FS_GetIndexRootMIUAddress(enid), ATTR_TYPE_FILE_NAME, &u16Temp, 0);
    if(attrInfo.Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }

    tmpXdata = (U8 *)N51FS_GetIndexRootInfo(enid);

    //u32Temp = (*(U32*)(tmpXdata+( *(U16*)(tmpXdata+0x14))));
    memcpy(&u16Temp_1,(tmpXdata+0x14),2);
    memcpy(&u32Temp,(tmpXdata+u16Temp_1),4);

    pN51FSenv = N51FS_GetEnvironmentInfo(enid);

    pN51FSenv->ParentDirectoryMFR = u32Temp;
    //get parent MFR finished!!

    attrInfo=N51FS_Attribute_Find(fsid,USB_IO_TEMP_ADDR + attributeOffset, N51FS_GetIndexRootMIUAddress(enid),ATTR_TYPE_INDEX_ROOT, &u16Temp, 0);
    NIX_DBG(0,printf("$INDEX_ROOT");dumpMIU(N51FS_GetIndexRootMIUAddress(enid),2););

    if(attrInfo.Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }

    pIndexVars = N51FS_GetIndexVarsInfo(enid);

    memset(pIndexVars, 0x00, sizeof(IndexVars));

    pIndexRootHead = (N51FS_ResidentAttrHead*)N51FS_GetIndexRootInfo(enid);

    //pIndexRootHead->OffsetToAttr=(pIndexRootHead->OffsetToAttr);
    largeIndexFlag = *(((U8*)pIndexRootHead)+pIndexRootHead->OffsetToAttr+0x1C);
    //u32Temp = ( *(U32*)((U8*)pIndexRootHead+pIndexRootHead->OffsetToAttr+0x10))+pIndexRootHead->OffsetToAttr+0x10;
    memcpy(&u32Temp,((U8*)pIndexRootHead+pIndexRootHead->OffsetToAttr+0x10),4);
    u32Temp += (pIndexRootHead->OffsetToAttr+0x10);

    pIndexVars->CurrentRecordBytePosition = u32Temp;
    if( largeIndexFlag & 0x1 ) //Large Index, copy the INDEX_ALLOCATION and BITMAP attribute
    {
        attrInfo2 = N51FS_Attribute_Find(fsid,USB_IO_TEMP_ADDR+attributeOffset,N51FS_GetIndexRootMIUAddress(enid)+attrInfo.Size,ATTR_TYPE_INDEX_ALLOCATION, &u16Temp, 0);
        if(attrInfo2.Size==0)
        {
            __ASSERT(0);
            return FALSE;
        }

        tmpXdata = (U8*)N51FS_GetIndexRootInfo(enid)+attrInfo.Size;

        u16Temp = (U16)(attrInfo.Size + (((N51FS_NonResidentAttrHead*)(void *)tmpXdata)->OffsetToDataRuns));
        pIndexVars->OffsetToRunList = u16Temp;
    }

    NIX_DBG(0,printf("$INDEX_ROOT end!!\n\n"););

    return TRUE;
}

//assume the Stream is at a start of an index
EN_N51FS_INDEX_NEXT_RESULT N51FS_Index_Next(U8 enid, FileEntry* pFileToSet)
{
    N51FS_Environment* pN51FSenv;
    U8 fsid;
    U32 u32CurrentDirectoryMFR;
    U16 u16Temp=0;
    U32 u32Temp_1=0,u32Temp_2=0;
    EN_N51FS_INDEX_NEXT_RESULT indexNextResult=N51FS_INDEX_NEXT_RESULT_ERROR;

    pN51FSenv = N51FS_GetEnvironmentInfo(enid);

    fsid = pN51FSenv->FileSystemID;
    u32CurrentDirectoryMFR = pN51FSenv->CurrentDirectoryMFR;

    pIndexVars = N51FS_GetIndexVarsInfo(enid);

    NIX_DBG(0,printf("IndexEntry next...\n"));
    while(TRUE)
    {
        FS_RESET_WDT();

        if(pIndexVars->LastReached == TRUE)
        {
            indexNextResult=N51FS_INDEX_NEXT_RESULT_LAST;
            break;
        }

        //read index entry from buffer
        if(pIndexVars->PositionStackCount== 0)
        {
            msAPI_FS_MIU_Copy(N51FS_GetIndexRootMIUAddress(enid) + pIndexVars->CurrentRecordBytePosition + 8, GET_DRAM_ADDR(&u16Temp), 2); //read entry size //Eric won't use
            msAPI_FS_MIU_Copy(N51FS_GetIndexRootMIUAddress(enid) + pIndexVars->CurrentRecordBytePosition, N51FS_GetIndexVarsMIUAddress(enid) + sizeof(IndexVars) - sizeof(IndexEntryHead) + 8, u16Temp); //read entry size

            pIndexVars->CurrentRecordBytePosition += u16Temp;

            ReOrderIndexEntry(&(pIndexVars->CurrentIndexEntryHead));
        }
        else
        {
            msAPI_FS_MIU_Copy(N51FS_GetIndexRecordMIUAddress(enid) + pIndexVars->CurrentRecordBytePosition + 8, GET_DRAM_ADDR(&u16Temp), 2); //read entry size //Eric won't use
            msAPI_FS_MIU_Copy(N51FS_GetIndexRecordMIUAddress(enid) + pIndexVars->CurrentRecordBytePosition, N51FS_GetIndexVarsMIUAddress(enid) + sizeof(IndexVars) - sizeof(IndexEntryHead) + 8, u16Temp); //read entry size

            pIndexVars->CurrentRecordBytePosition += u16Temp;
            ReOrderIndexEntry(&(pIndexVars->CurrentIndexEntryHead));
        }

        if(pIndexVars->CurrentIndexEntryHead.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
        {
            if(!pIndexVars->JustLeaveSubNode)
            {
                pIndexVars->CurrentRecordBytePosition -= pIndexVars->CurrentIndexEntryHead.EntrySize;
                if(!N51FS_Index_GoToSubNode(enid))
                {
                    __ASSERT(0);
                    indexNextResult=N51FS_INDEX_NEXT_RESULT_ERROR;
                    break;
                }
                continue;
            }
            else
            {
                pIndexVars->JustLeaveSubNode = FALSE;

                if(pIndexVars->CurrentIndexEntryHead.EntryFlag & INDEX_ENTRY_FLAG_BIT_END)
                {

                    if(pIndexVars->PositionStackCount== 0)
                    {
                        pIndexVars->LastReached = TRUE;
                        indexNextResult = N51FS_INDEX_NEXT_RESULT_LAST;
                        ////<<<<FLOW Control, NOT FOUND!!
                        break;
                    }
                    else
                    {
                        pIndexVars->CurrentRecordBytePosition -= pIndexVars->CurrentIndexEntryHead.EntrySize;
                        if(!N51FS_Index_LeaveSubNode(enid))
                        {
                            __ASSERT(0);
                            indexNextResult=N51FS_INDEX_NEXT_RESULT_ERROR;
                            break;
                        }
                        ////<<<<FLOW Control, Leave SubNode
                        continue;
                    }

                }
                else
                {
                    ////<<<<FLOW Control, FOUND!!
                    indexNextResult=N51FS_INDEX_NEXT_RESULT_SUCCESS;
                }
            }
        }
        else if(pIndexVars->CurrentIndexEntryHead.EntryFlag & INDEX_ENTRY_FLAG_BIT_END)
        {
            if(pIndexVars->PositionStackCount== 0)
            {
                pIndexVars->LastReached = TRUE;
                indexNextResult = N51FS_INDEX_NEXT_RESULT_LAST;
                ////<<<<FLOW Control, NOT FOUND!!
                break;
            }
            else
            {
                pIndexVars->CurrentRecordBytePosition -= pIndexVars->CurrentIndexEntryHead.EntrySize;
                if(!N51FS_Index_LeaveSubNode(enid))
                {
                    __ASSERT(0);
                    indexNextResult = N51FS_INDEX_NEXT_RESULT_ERROR;
                    break;
                }
                ////<<<<FLOW Control, Leave SubNode
                continue;
            }
        }
        else
        {
            ////<<<<FLOW Control, FOUND!!
            indexNextResult=N51FS_INDEX_NEXT_RESULT_SUCCESS;
        }

        if(pIndexVars->CurrentIndexEntryHead.MFTReference<N51FS_SYSTEM_RESERVE_FILE||(*((U8*)pIndexVars+sizeof(IndexVars)+0x41) == FILENAMESPACE_DOS))
        {
            continue;
        }

        //Save to FileEntry
        pFileToSet->FileSystemID = fsid;
        pFileToSet->EnvironmentID = enid;
        //*((U32*)pFileToSet->EntryID) = pIndexVars->CurrentIndexEntryHead.MFTReference;  //Eric won't use
        memcpy(pFileToSet->EntryID,&(pIndexVars->CurrentIndexEntryHead.MFTReference),4);
        //*((U32*)pFileToSet->EntryID_Ext) = u32CurrentDirectoryMFR;  //Eric won't use
        memcpy(pFileToSet->EntryID_Ext,&u32CurrentDirectoryMFR,4);
        //pFileToSet->FileLength.Hi= ( *(U32*)((U8*)pIndexVars+sizeof(IndexVars)+0x34) );  //Eric won't use
        memcpy(&(pFileToSet->FileLength.Hi),((U8*)pIndexVars+sizeof(IndexVars)+0x34),4);
        //pFileToSet->FileLength.Lo= ( *(U32*)((U8*)pIndexVars+sizeof(IndexVars)+0x30) );  //Eric won't use
        memcpy(&(pFileToSet->FileLength.Lo),((U8*)pIndexVars+sizeof(IndexVars)+0x30),4);
        pFileToSet->EntryFileLength = pFileToSet->FileLength.Lo;
        memcpy(&u32Temp_1,((U8*)pIndexVars+sizeof(IndexVars)+0x14),4);
        memcpy(&u32Temp_2,((U8*)pIndexVars+sizeof(IndexVars)+0x10),4);
        pFileToSet->EntrySeconds =ConvertN51FSTimeTo1980BasedSeconds(u32Temp_1, u32Temp_2);

        memcpy(&u32Temp_1,((U8*)pIndexVars+sizeof(IndexVars)+0x38) ,4);
        if(u32Temp_1 & 0x10000000UL)
        {
            pFileToSet->EntryType = ENTRY_TYPE_DIR;
            pFileToSet->EntryAttrib = ENTRY_ATTRIB_DIRECTORY |*((U8*)pIndexVars+sizeof(IndexVars)+0x38);
        }
        else
        {
            pFileToSet->EntryType = ENTRY_TYPE_FILE;
            pFileToSet->EntryAttrib = *((U8*)pIndexVars+sizeof(IndexVars)+0x38);
        }

        // save current FileEntry
        //msAPI_FS_MIU_Copy(GET_DRAM_ADDR(pFileToSet), N51FS_GetCurrentFileEntryMIUAddress(enid),  sizeof(FileEntry));

        break;
    }

    return indexNextResult;
}

#if(!FILE_SYSTEM_SMALL)
IndexHeader* pIndexHeader;

static BOOLEAN N51FS_Delete_SaveRecordToDisk(U8 fsid)
{
    U8 _clustersPerRecord;
    U32 _sectorPerCluster;
    U16 _bytesPerSector;
    U32 _physicalStartSector;
    U8* pBuff;
    U16 u16OffsetToFixUp;
    U16 u16FixUpNum;
    U16 u16FixUpCount;
    U32 LCN;
    U32 VCN;
    N51FS_FileSysStruct* pfst;
    U8 deviceIndex;
    U8 i;
    U8 u8ReadSectorCnt;

    pfst=(N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    _sectorPerCluster=pfst->SectorsPerCluster;
    _bytesPerSector=pfst->BytesPerSector;
    _physicalStartSector=pfst->RelativeSector;
    deviceIndex=pfst->DeviceIndex;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_0);

    _clustersPerRecord = *(pBuff + (U16)pIndexHeader->u32OffsetToIndexRootHeader - 4);

    //[1].FixUP
    pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_1);

    u8ReadSectorCnt = (U8)(_clustersPerRecord * _sectorPerCluster);
    //u16OffsetToFixUp = ( *((U16*)&pBuff[0x04]) );
    memcpy(&u16OffsetToFixUp,&pBuff[0x04],2);
    //u16FixUpCount = ( *((U16*)&pBuff[0x06]) );
    memcpy(&u16FixUpCount,&pBuff[0x06],2);
    //u16FixUpNum = *((U16*)&pBuff[u16OffsetToFixUp]);
    memcpy(&u16FixUpNum,&pBuff[u16OffsetToFixUp],2);

    for(i = 1; i <= u8ReadSectorCnt*(_bytesPerSector/NTFS_BLOCK_SIZE); i++)
    {
        if(i > u16FixUpCount)
        {
            __ASSERT(0);
            return FALSE;
        }
        //*(U16*)(pBuff + u16OffsetToFixUp + i*2) = *(U16*)(pBuff + i*_bytesPerSector - 2);
        memcpy((pBuff + u16OffsetToFixUp + i*2),(pBuff + i*NTFS_BLOCK_SIZE - 2),2);
        //*(U16*)(pBuff + i*_bytesPerSector - 2) = u16FixUpNum;
        memcpy((pBuff + i*NTFS_BLOCK_SIZE - 2),&u16FixUpNum,2);
    }

    //[2]. Save
    VCN = pIndexHeader->u32CurrentRecordStartVCN;
    for(i = 0; i < _clustersPerRecord; i++)
    {
        LCN = N51FS_Index_MapVCN2LCN(pIndexHeader->u32RunListAddr, pIndexHeader->u16OffsetToRunList, VCN);
        if(!msAPI_MSDCtrl_SectorWrite(deviceIndex,_physicalStartSector + LCN * _sectorPerCluster
                                 ,_sectorPerCluster, N51FS_TEMP_4K_BACKUP_BUFFER_1 + i * _sectorPerCluster*_bytesPerSector))
        {
            __ASSERT(0);
            return FALSE;
        }
        VCN++;
    }

    return TRUE;
}

static BOOLEAN N51FS_Delete_LeaveSubNode(U8 fsid)
{
    U8 *pBuff;
    U32 VCN = 0;
    U16 bytes=0;

    if(pIndexHeader->u8PositionStackCount==0 || pIndexHeader->u8PositionStackCount > POSITION_STACK_SIZE)
    {
        __ASSERT(0);
        return FALSE;
    }
    else
    {
        if(pIndexHeader->bRecordDirty)
        {
            N51FS_Delete_SaveRecordToDisk(fsid);
            pIndexHeader->bRecordDirty = FALSE;
        }
        pIndexHeader->u8PositionStackCount--;
        VCN = pIndexHeader->PositionStack[pIndexHeader->u8PositionStackCount].VCN;
        bytes = pIndexHeader->PositionStack[pIndexHeader->u8PositionStackCount].Bytes;
    }

    if(pIndexHeader->u8PositionStackCount > 0)
    {
        if(!N51FS_Index_InputRecordFromDisk(fsid, N51FS_TEMP_4K_BACKUP_BUFFER_0, pIndexHeader->u32RunListAddr, N51FS_TEMP_4K_BACKUP_BUFFER_1, pIndexHeader->u16OffsetToRunList, (U16)(pIndexHeader->u32OffsetToIndexRootHeader - 0x10), VCN))
        {
            __ASSERT(0);
            return FALSE;
        }
        pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

        //pIndexHeader->u32OffsetToEntry = 0x18 + (*(U32 *)(pBuff + 0x18));
        memcpy(&(pIndexHeader->u32OffsetToEntry),(pBuff + 0x18),4);
        pIndexHeader->u32OffsetToEntry += 0x18;
    }
    else
    {
        pIndexHeader->u32CurrentBuffAddr = N51FS_TEMP_4K_BACKUP_BUFFER_0;
        pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

        //pIndexHeader->u32OffsetToEntry = pIndexHeader->u32OffsetToIndexRootHeader + (*(U32 *)(pBuff + pIndexHeader->u32OffsetToIndexRootHeader));
        memcpy(&(pIndexHeader->u32OffsetToEntry),(pBuff + pIndexHeader->u32OffsetToIndexRootHeader),4);
        pIndexHeader->u32OffsetToEntry += pIndexHeader->u32OffsetToIndexRootHeader;
    }

    //current stream reset
    pIndexHeader->u32CurrentRecordStartVCN = VCN;
    pIndexHeader->u32CurrentRecordBytePosition = bytes;

    return TRUE;
}
static BOOLEAN N51FS_Delete_GoToSubNode(U8 fsid, U32 u32SubNodeVCN)
{
    U32 subNodeLCN;
    U8 * pBuff;

    subNodeLCN = N51FS_Index_MapVCN2LCN(pIndexHeader->u32RunListAddr, pIndexHeader->u16OffsetToRunList, u32SubNodeVCN);
    if(subNodeLCN>0)
    {
        //Push current index position
        if(pIndexHeader->u8PositionStackCount >= POSITION_STACK_SIZE)
        {
            __ASSERT(0);
            return FALSE;
        }
        else
        {
            if(pIndexHeader->u8PositionStackCount > 0 && pIndexHeader->bRecordDirty)
            {
                N51FS_Delete_SaveRecordToDisk(fsid);
                pIndexHeader->bRecordDirty = FALSE;
            }

            pIndexHeader->PositionStack[pIndexHeader->u8PositionStackCount].Bytes = pIndexHeader->u32CurrentRecordBytePosition;
            pIndexHeader->PositionStack[pIndexHeader->u8PositionStackCount].VCN = pIndexHeader->u32CurrentRecordStartVCN;
            pIndexHeader->u8PositionStackCount++;
        }

        //Read sub node from disk
        if(!N51FS_Index_InputRecordFromDisk(fsid, N51FS_TEMP_4K_BACKUP_BUFFER_0, pIndexHeader->u32RunListAddr, N51FS_TEMP_4K_BACKUP_BUFFER_1, pIndexHeader->u16OffsetToRunList, (U16)(pIndexHeader->u32OffsetToIndexRootHeader - 0x10), u32SubNodeVCN))
        {
            __ASSERT(0);
            return FALSE;
        }

        //current stream reset
        pIndexHeader->u32CurrentBuffAddr = N51FS_TEMP_4K_BACKUP_BUFFER_1;
        pIndexHeader->u32CurrentRecordStartVCN = u32SubNodeVCN;
        pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

        //pIndexHeader->u32OffsetToEntry = 0x18 + (*(U32 *)(pBuff + 0x18));
        memcpy(&(pIndexHeader->u32OffsetToEntry),(pBuff + 0x18),4);
        pIndexHeader->u32OffsetToEntry += 0x18;
        pIndexHeader->u32CurrentRecordBytePosition = pIndexHeader->u32OffsetToEntry;

        return TRUE;
    }
    return FALSE;

}

BOOLEAN N51FS_Delete_Index_Search(FileEntry *pFileToFind)
{
    U16 attributeOffset = 0;
    U16 u16Temp = 0;
    U16 u16Temp_1 = 0;
    N51FS_AttributeInfo attrInfo;
    N51FS_AttributeInfo attrInfo2;
    U8 *pBuff;
    U8 largeIndexFlag;
    U16 u16OffsetToAttr;
    U8 u8EntryFlag;
    U16 u16EntrySize;
    U32 u32SubNodeVCN;
    U32 u32FileReference;
    U8 u8NextEntryFlag;
    BOOLEAN bJustLeaveSubNode = FALSE;
    U32 u32Temp=0;

    //read parent directory MFT record
    memcpy(&u32Temp,pFileToFind->EntryID_Ext,4);
    //if(0 == N51FS_ReadMFTRecord(pFileToFind->FileSystemID, *((U32*)pFileToFind->EntryID_Ext), N51FS_TEMP_4K_BACKUP_BUFFER_0))
    if(0 == N51FS_ReadMFTRecord(pFileToFind->FileSystemID, u32Temp, N51FS_TEMP_4K_BACKUP_BUFFER_0))
    {
        __ASSERT(0);
        return FALSE;
    }

    msAPI_FS_MIU_Copy( N51FS_TEMP_4K_BACKUP_BUFFER_0 + 0x14, GET_DRAM_ADDR(&attributeOffset), 2 );

    attrInfo = N51FS_Attribute_Find(pFileToFind->FileSystemID,N51FS_TEMP_4K_BACKUP_BUFFER_0 + attributeOffset, USB_IO_TEMP_ADDR, ATTR_TYPE_INDEX_ROOT, &u16Temp, 0);
    if(attrInfo.Size==0)
    {
        __ASSERT(0);
        return FALSE;
    }
    memset(pIndexHeader, 0x00, sizeof(IndexHeader));
    pIndexHeader->u32CurrentBuffAddr = N51FS_TEMP_4K_BACKUP_BUFFER_0;
    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    pIndexHeader->u32OffsetToIndexRootAttr = (U32)(attributeOffset + u16Temp);
    //u16OffsetToAttr = (*(U16 *)(pBuff + pIndexHeader->u32OffsetToIndexRootAttr + 0x14));
    memcpy(&u16OffsetToAttr,(pBuff + pIndexHeader->u32OffsetToIndexRootAttr + 0x14),2);
    u16OffsetToAttr += (pIndexHeader->u32OffsetToIndexRootAttr);
    largeIndexFlag = *(pBuff + u16OffsetToAttr + 0x1C);
    pIndexHeader->u32OffsetToIndexRootHeader = (U32)u16OffsetToAttr + 0x10;
    //pIndexHeader->u32OffsetToEntry = pIndexHeader->u32OffsetToIndexRootHeader + (*(U32 *)(pBuff + pIndexHeader->u32OffsetToIndexRootHeader));
    memcpy(&(pIndexHeader->u32OffsetToEntry),(pBuff + pIndexHeader->u32OffsetToIndexRootHeader),4);
    pIndexHeader->u32OffsetToEntry += pIndexHeader->u32OffsetToIndexRootHeader;

    pIndexHeader->u32CurrentRecordBytePosition = pIndexHeader->u32OffsetToEntry;

    if( largeIndexFlag & 0x1 ) //Large Index, copy the INDEX_ALLOCATION and BITMAP attribute
    {
        u16Temp = 0;
        attrInfo = N51FS_Attribute_Find(pFileToFind->FileSystemID,N51FS_TEMP_4K_BACKUP_BUFFER_0+attributeOffset, USB_IO_TEMP_ADDR, ATTR_TYPE_INDEX_ALLOCATION, &u16Temp, 0);
        if(attrInfo.Size == 0)
        {
            u16Temp = 0;
            attrInfo2 = N51FS_Attribute_Find(pFileToFind->FileSystemID,N51FS_TEMP_4K_BACKUP_BUFFER_0+attributeOffset, USB_IO_TEMP_ADDR, ATTR_TYPE_ATTRIBUTE_LIST, &u16Temp, 0);
            if(attrInfo2.Size == 0)
        {
            __ASSERT(0);
                return FALSE;
        }
            pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BUFFER_0);

            pIndexHeader->u32RunListAddr = N51FS_TEMP_4K_BUFFER_0;
            //pIndexHeader->u16OffsetToRunList = (*(U16 *)(pBuff + 0x20));
            memcpy(&(pIndexHeader->u16OffsetToRunList),(pBuff + 0x20),2);
        }
        else
        {
            pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_0);

            pIndexHeader->u32RunListAddr = N51FS_TEMP_4K_BACKUP_BUFFER_0;
            //pIndexHeader->u16OffsetToRunList = (U16)(attributeOffset + u16Temp + (*(U16 *)(pBuff + attributeOffset + u16Temp + 0x20)));
            memcpy(&u16Temp_1,(pBuff + attributeOffset + u16Temp + 0x20),2);
            pIndexHeader->u16OffsetToRunList = (U16)(attributeOffset + u16Temp + u16Temp_1);
        }
    }

    while(TRUE)
    {
        FS_RESET_WDT();

        pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

        //u32FileReference = (*(U32 *)(pBuff + pIndexHeader->u32CurrentRecordBytePosition));
        memcpy(&u32FileReference,(pBuff + pIndexHeader->u32CurrentRecordBytePosition),4);
        //u16EntrySize = (*(U16 *)(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 8));
        memcpy(&u16EntrySize,(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 8),2);
        u8EntryFlag = *(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 0xC);
        u8NextEntryFlag = *(pBuff + pIndexHeader->u32CurrentRecordBytePosition + u16EntrySize + 0xC);
        //u32SubNodeVCN = (*(U32 *)(pBuff + pIndexHeader->u32CurrentRecordBytePosition + u16EntrySize - 8));
        memcpy(&u32SubNodeVCN,(pBuff + pIndexHeader->u32CurrentRecordBytePosition + u16EntrySize - 8),4);

        if(u8EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
        {
            if(!bJustLeaveSubNode)
            {
                if(!N51FS_Delete_GoToSubNode(pFileToFind->FileSystemID ,u32SubNodeVCN))
                {
                    __ASSERT(0);
                    return FALSE;
                }
            }
            else
            {
                bJustLeaveSubNode = FALSE;

                if(u8EntryFlag & INDEX_ENTRY_FLAG_BIT_END)
                {

                    if(pIndexHeader->u8PositionStackCount== 0)
                    {
                        return FALSE;
                    }
                    else
                    {
                        if(!N51FS_Delete_LeaveSubNode(pFileToFind->FileSystemID))
                        {
                            __ASSERT(0);
                            return FALSE;
                        }
                        bJustLeaveSubNode = TRUE;
                    }

                }
                else
                {
                    memcpy(&u32Temp,pFileToFind->EntryID,4);
                    if(u32Temp == u32FileReference)
                    {
                        //found
                        pIndexHeader->indexEntry.EntryFlag = (U16)u8EntryFlag;
                        pIndexHeader->indexEntry.EntrySize = u16EntrySize;

                        if(pIndexHeader->u32CurrentRecordBytePosition == pIndexHeader->u32OffsetToEntry)
                        {
                            pIndexHeader->indexEntry.bIsFirstEntry = TRUE;
                        }
                        else
                        {
                            pIndexHeader->indexEntry.bIsFirstEntry = FALSE;
                        }

                        if(u8NextEntryFlag & INDEX_ENTRY_FLAG_BIT_END)
                        {
                            pIndexHeader->indexEntry.bIsLastEntry = TRUE;
                        }
                        else
                        {
                            pIndexHeader->indexEntry.bIsLastEntry = FALSE;
                        }
                        return TRUE;
                    }
                    pIndexHeader->u32CurrentRecordBytePosition += u16EntrySize;
                }
            }
        }
        else if(u8EntryFlag & INDEX_ENTRY_FLAG_BIT_END)
        {
            if(pIndexHeader->u8PositionStackCount== 0)
            {
                return FALSE;
            }
            else
            {
                if(!N51FS_Delete_LeaveSubNode(pFileToFind->FileSystemID))
                {
                    __ASSERT(0);
                    return FALSE;
                }
                bJustLeaveSubNode = TRUE;
            }
        }
        else
        {
            memcpy(&u32Temp,pFileToFind->EntryID,4);
            if(u32Temp == u32FileReference)
            {
                //found
                pIndexHeader->indexEntry.EntryFlag = (U16)u8EntryFlag;
                pIndexHeader->indexEntry.EntrySize = u16EntrySize;

                if(pIndexHeader->u32CurrentRecordBytePosition == pIndexHeader->u32OffsetToEntry)
                {
                    pIndexHeader->indexEntry.bIsFirstEntry = TRUE;
                }
                else
                {
                    pIndexHeader->indexEntry.bIsFirstEntry = FALSE;
                }

                if(u8NextEntryFlag & INDEX_ENTRY_FLAG_BIT_END)
                {
                    pIndexHeader->indexEntry.bIsLastEntry = TRUE;
                }
                else
                {
                    pIndexHeader->indexEntry.bIsLastEntry = FALSE;
                }
                return TRUE;
            }
            pIndexHeader->u32CurrentRecordBytePosition += u16EntrySize;
        }
    }
}

static BOOLEAN N51FS_Delete_Index_GetCurrentEntry(void)
{
    U8* pBuff;
    U8 u8NextEntryFlag;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    //pIndexHeader->indexEntry.EntrySize = (*(U16 *)(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 8));
    memcpy(&(pIndexHeader->indexEntry.EntrySize),(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 8),2);
    pIndexHeader->indexEntry.EntryFlag = (U16)*(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 0xC);
    u8NextEntryFlag = *(pBuff + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize + 0xC);

    if(pIndexHeader->u32CurrentRecordBytePosition == pIndexHeader->u32OffsetToEntry)
    {
        pIndexHeader->indexEntry.bIsFirstEntry = TRUE;
    }
    else
    {
        pIndexHeader->indexEntry.bIsFirstEntry = FALSE;
    }

    if(u8NextEntryFlag & INDEX_ENTRY_FLAG_BIT_END)
    {
        pIndexHeader->indexEntry.bIsLastEntry = TRUE;
    }
    else
    {
        pIndexHeader->indexEntry.bIsLastEntry = FALSE;
    }

    return TRUE;
}

static BOOLEAN N51FS_Delete_InsertEntry(U32 u32Offset)
{
    U8* pBuff;
    U32 u32SrcAddr;
    U32 u32DstAddr;
    U32 u32Length;
    U16 u16SrcEntrySize;
    U8  u8SrcEntryFlag;
    U32 u32Size;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_2);

    pBuff += (U16)u32Offset;
    u8SrcEntryFlag = *(pBuff + 0x0C);
    //u16SrcEntrySize = (*(U16 *)(pBuff + 8));
    memcpy(&u16SrcEntrySize,(pBuff + 8),2);
    if(u8SrcEntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        u16SrcEntrySize -= 8;
    }

    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        u16SrcEntrySize += 8;
        u8SrcEntryFlag = INDEX_ENTRY_FLAG_BIT_NODE;
    }
    else
    {
        u8SrcEntryFlag = 0;
    }
    //*(U16 *)(pBuff + 8) = (u16SrcEntrySize);
    memcpy((pBuff + 8),&u16SrcEntrySize,2);

    *(pBuff + 0x0C) = u8SrcEntryFlag;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    if(pIndexHeader->u8PositionStackCount== 0)
    {
        pIndexHeader->bRootDirty = TRUE;

        //update MFT record size
        //u32Size = (*(U32 *)(pBuff + 0x18));
        memcpy(&u32Size,(pBuff + 0x18),4);

        u32Size += u16SrcEntrySize;
        //*(U32 *)(pBuff + 0x18) = (u32Size);
        memcpy((pBuff + 0x18),&u32Size,4);

        u32Length = u32Size - pIndexHeader->u32CurrentRecordBytePosition - u16SrcEntrySize;

        //update Root attribute size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),4);

        u32Size += u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),&u32Size,4);

        //update Root attribute length
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),4);
        u32Size += u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),&u32Size,4);

        //update Root record size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),4);
        u32Size += u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),&u32Size,4);

        //update Root record allocated size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),4);
        u32Size += u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),&u32Size,4);

        if(pIndexHeader->u32RunListAddr == N51FS_TEMP_4K_BACKUP_BUFFER_0 &&
           pIndexHeader->u16OffsetToRunList > pIndexHeader->u32OffsetToIndexRootAttr)
        {
            pIndexHeader->u16OffsetToRunList += u16SrcEntrySize;
        }
    }
    else
    {
        pIndexHeader->bRecordDirty = TRUE;
        //update Root record size
        //u32Size = (*(U32 *)(pBuff + 0x1C));
        memcpy(&u32Size,(pBuff + 0x1C),4);
        u32Size += u16SrcEntrySize;
        //*(U32 *)(pBuff + 0x1C) = (u32Size);
        memcpy((pBuff + 0x1C),&u32Size,4);

        u32Length = u32Size - (pIndexHeader->u32CurrentRecordBytePosition - 0x18) - u16SrcEntrySize;
    }
    u32DstAddr = u32SrcAddr = pIndexHeader->u32CurrentBuffAddr;

    u32DstAddr += pIndexHeader->u32CurrentRecordBytePosition + u16SrcEntrySize;
    u32SrcAddr += pIndexHeader->u32CurrentRecordBytePosition;
    if(u32SrcAddr > u32DstAddr)
    {
    msAPI_FS_MIU_Copy(u32SrcAddr, u32DstAddr, u32Length);
    }
    else if(u32DstAddr > u32SrcAddr)
    {
        msAPI_FS_MIU_Copy_I(u32SrcAddr, u32DstAddr, u32Length);
    }
    msAPI_FS_MIU_Copy(N51FS_TEMP_4K_BACKUP_BUFFER_2 + u32Offset, pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, (U32)u16SrcEntrySize);
    N51FS_Delete_Index_GetCurrentEntry();

    return TRUE;
}


static BOOLEAN N51FS_Delete_ReplaceEntry(U32 u32Offset)
{
    U8* pBuff;
    U32 u32SrcAddr;
    U32 u32DstAddr;
    U32 u32Length;
    U16 u16DstEntrySize;
    U16 u16SrcEntrySize;
    U8  u8SrcEntryFlag;
    U32 u32Size;
    U16 u16Temp;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_2);

    pBuff += (U16)u32Offset;
    //u16SrcEntrySize = (*(U16 *)(pBuff + 8));
    memcpy(&u16SrcEntrySize,(pBuff + 8),2);
    u8SrcEntryFlag = *(pBuff + 0x0C);
    if(u8SrcEntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        u16SrcEntrySize -= 8;
    }

    u16DstEntrySize = pIndexHeader->indexEntry.EntrySize;

    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        u8SrcEntryFlag = INDEX_ENTRY_FLAG_BIT_NODE;
        u16DstEntrySize -= 8;
        //*(U16 *)(pBuff + 8) = (u16SrcEntrySize + 8);
        u16Temp=(u16SrcEntrySize + 8);
        memcpy((pBuff + 8),&u16Temp,2);
    }
    else
    {
        u8SrcEntryFlag = 0;
        //*(U16 *)(pBuff + 8) = (u16SrcEntrySize);
        memcpy((pBuff + 8),&u16SrcEntrySize,2);
    }
    *(pBuff + 0x0C) = u8SrcEntryFlag;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    if(pIndexHeader->u8PositionStackCount== 0)
    {
        pIndexHeader->bRootDirty = TRUE;
        //update MFT record size
        //u32Size = (*(U32 *)(pBuff + 0x18));
        memcpy(&u32Size,(pBuff + 0x18),4);
        u32Length = u32Size - pIndexHeader->u32CurrentRecordBytePosition - u16DstEntrySize;
        u32Size = u32Size - u16DstEntrySize + u16SrcEntrySize;
        //*(U32 *)(pBuff + 0x18) = (u32Size);
        memcpy((pBuff + 0x18),&u32Size,4);


        //update Root attribute size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),4);
        u32Size = u32Size - u16DstEntrySize + u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),&u32Size,4);

        //update Root attribute length
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),4);
        u32Size = u32Size - u16DstEntrySize + u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),&u32Size,4);

        //update Root record size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),4);
        u32Size = u32Size - u16DstEntrySize + u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),&u32Size,4);

        //update Root record allocated size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),4);
        u32Size = u32Size - u16DstEntrySize + u16SrcEntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),&u32Size,4);

        if(pIndexHeader->u32RunListAddr == N51FS_TEMP_4K_BACKUP_BUFFER_0 &&
           pIndexHeader->u16OffsetToRunList > pIndexHeader->u32OffsetToIndexRootAttr)
        {
            pIndexHeader->u16OffsetToRunList = pIndexHeader->u16OffsetToRunList - u16DstEntrySize + u16SrcEntrySize;
        }
    }
    else
    {
        pIndexHeader->bRecordDirty = TRUE;
        //update Root record size
        //u32Size = (*(U32 *)(pBuff + 0x1C));
        memcpy(&u32Size,(pBuff + 0x1C),4);
        u32Length = u32Size - (pIndexHeader->u32CurrentRecordBytePosition - 0x18) - u16DstEntrySize;
        u32Size = u32Size - u16DstEntrySize + u16SrcEntrySize;
        //*(U32 *)(pBuff + 0x1C) = (u32Size);
        memcpy((pBuff + 0x1C),&u32Size,4);
    }
    u32DstAddr = u32SrcAddr = pIndexHeader->u32CurrentBuffAddr;

    u32DstAddr += pIndexHeader->u32CurrentRecordBytePosition + u16SrcEntrySize;
    u32SrcAddr += pIndexHeader->u32CurrentRecordBytePosition + u16DstEntrySize;
    if(u32SrcAddr > u32DstAddr)
    {
    msAPI_FS_MIU_Copy(u32SrcAddr, u32DstAddr, u32Length);
    }
    else if(u32DstAddr > u32SrcAddr)
    {
        msAPI_FS_MIU_Copy_I(u32SrcAddr, u32DstAddr, u32Length);
    }
    msAPI_FS_MIU_Copy(N51FS_TEMP_4K_BACKUP_BUFFER_2 + u32Offset, pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, (U32)u16SrcEntrySize);
    N51FS_Delete_Index_GetCurrentEntry();
    return TRUE;

}

static BOOLEAN N51FS_Delete_RemoveEntry(U8* pu8SubNodeVCN)
{
    U8* pBuff;
    U32 u32SrcAddr;
    U32 u32DstAddr;
    U32 u32Length;
    U32 u32Size;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    if(pIndexHeader->u8PositionStackCount== 0)
    {
        pIndexHeader->bRootDirty = TRUE;

        //update MFT record size
        //u32Size = (*(U32 *)(pBuff + 0x18));
        memcpy(&u32Size,(pBuff + 0x18),4);
        u32Size -= pIndexHeader->indexEntry.EntrySize;
        //*(U32 *)(pBuff + 0x18) = (u32Size);
        memcpy((pBuff + 0x18),&u32Size,4);

        u32Length = u32Size - pIndexHeader->u32CurrentRecordBytePosition;

        //update Root attribute size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),4);
        u32Size -= pIndexHeader->indexEntry.EntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),&u32Size,4);

        //update Root attribute length
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),4);
        u32Size -= pIndexHeader->indexEntry.EntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),&u32Size,4);

        //update Root record size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),4);
        u32Size -= pIndexHeader->indexEntry.EntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),&u32Size,4);

        //update Root record allocated size
        //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8));
        memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),4);
        u32Size -= pIndexHeader->indexEntry.EntrySize;
        //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8) = (u32Size);
        memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),&u32Size,4);


        if(pIndexHeader->u32RunListAddr == N51FS_TEMP_4K_BACKUP_BUFFER_0 &&
           pIndexHeader->u16OffsetToRunList > pIndexHeader->u32OffsetToIndexRootAttr)
        {
            pIndexHeader->u16OffsetToRunList -= pIndexHeader->indexEntry.EntrySize;
        }
    }
    else
    {
        pIndexHeader->bRecordDirty = TRUE;

        //update Root record size
        //u32Size = (*(U32 *)(pBuff + 0x1C));
        memcpy(&u32Size,(pBuff + 0x1C),4);
        u32Size -= pIndexHeader->indexEntry.EntrySize;
        //*(U32 *)(pBuff + 0x1C) = (u32Size);
        memcpy((pBuff + 0x1C),&u32Size,4);

        u32Length = u32Size - (pIndexHeader->u32CurrentRecordBytePosition - 0x18);

    }
    u32DstAddr = u32SrcAddr = pIndexHeader->u32CurrentBuffAddr;

    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        memcpy(pu8SubNodeVCN, pBuff + (U16)(pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize) - 8, 8);
    }

    u32DstAddr += pIndexHeader->u32CurrentRecordBytePosition;
    u32SrcAddr += pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize;
    if(u32SrcAddr > u32DstAddr)
    {
    msAPI_FS_MIU_Copy(u32SrcAddr, u32DstAddr, u32Length);
    }
    else if(u32DstAddr > u32SrcAddr)
    {
        msAPI_FS_MIU_Copy_I(u32SrcAddr, u32DstAddr, u32Length);
    }
    N51FS_Delete_Index_GetCurrentEntry();
    return TRUE;
}

static BOOLEAN N51FS_Delete_Index_GotoParent(U8 fsid)
{
    if(pIndexHeader->u8PositionStackCount == 0)
    {
        __ASSERT(0);
        return FALSE;
    }
    if(!N51FS_Delete_LeaveSubNode(fsid))
    {
        __ASSERT(0);
        return FALSE;
    }

    N51FS_Delete_Index_GetCurrentEntry();
    return TRUE;
}

static BOOLEAN N51FS_Delete_Index_GotoPrevEntry(void)
{
    U8* pBuff;
    U32 u32CurrentOffset;
    U16 u16CurrentEntrySize;

    if(pIndexHeader->indexEntry.bIsFirstEntry)
    {
        return FALSE;
    }

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    u32CurrentOffset = pIndexHeader->u32OffsetToEntry;
    //u16CurrentEntrySize = (*(U16 *)(pBuff + u32CurrentOffset + 8));
    memcpy(&u16CurrentEntrySize,(pBuff + u32CurrentOffset + 8),2);
    while(u32CurrentOffset + u16CurrentEntrySize != pIndexHeader->u32CurrentRecordBytePosition)
    {
        u32CurrentOffset += u16CurrentEntrySize;
        //u16CurrentEntrySize = (*(U16 *)(pBuff + u32CurrentOffset + 8));
        memcpy(&u16CurrentEntrySize,(pBuff + u32CurrentOffset + 8),2);
    }

    pIndexHeader->u32CurrentRecordBytePosition = u32CurrentOffset;

    N51FS_Delete_Index_GetCurrentEntry();
    return TRUE;
}

static BOOLEAN N51FS_Delete_Index_GotoNextEntry(void)
{
    pIndexHeader->u32CurrentRecordBytePosition += pIndexHeader->indexEntry.EntrySize;
    N51FS_Delete_Index_GetCurrentEntry();
    return TRUE;
}


static BOOLEAN N51FS_Delete_Index_GotoChild(U8 fsid)
{
    U8* pBuff;
    U32 u32SubNodeVCN;

    if(pIndexHeader->u8PositionStackCount >= POSITION_STACK_SIZE)
    {
        __ASSERT(0);
        return FALSE;
    }

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    //u32SubNodeVCN = (*(U32 *)(pBuff + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize - 8));
    memcpy(&u32SubNodeVCN,(pBuff + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize - 8),4);

    if(!N51FS_Delete_GoToSubNode(fsid ,u32SubNodeVCN))
    {
        __ASSERT(0);
        return FALSE;
    }
    N51FS_Delete_Index_GetCurrentEntry();
    return TRUE;
}

static BOOLEAN N51FS_Delete_Index_GotoLastEntry(void)
{
    U8* pBuff;
    U16 u16EntrySize;
    U8 u8NextEntryFlag;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    //u16EntrySize = (*(U16 *)(pBuff + (U16)(pIndexHeader->u32CurrentRecordBytePosition) + 8));
    memcpy(&u16EntrySize,(pBuff + (U16)(pIndexHeader->u32CurrentRecordBytePosition) + 8),2);
    u8NextEntryFlag = *(pBuff + (U16)(pIndexHeader->u32CurrentRecordBytePosition) + u16EntrySize + 0xC);
    while((u8NextEntryFlag & INDEX_ENTRY_FLAG_BIT_END) == 0)
    {
        pIndexHeader->u32CurrentRecordBytePosition += u16EntrySize;
        //u16EntrySize = (*(U16 *)(pBuff + (U16)(pIndexHeader->u32CurrentRecordBytePosition) + 8));
        memcpy(&u16EntrySize,(pBuff + (U16)(pIndexHeader->u32CurrentRecordBytePosition) + 8),2);
        u8NextEntryFlag = *(pBuff + (U16)(pIndexHeader->u32CurrentRecordBytePosition) + u16EntrySize + 0xC);
    }
    N51FS_Delete_Index_GetCurrentEntry();
    return TRUE;
}

static BOOLEAN N51FS_Delete_ReplaceSubNodeVCN(U8* u8SubNodeVCN)
{
    U8* pBuff;
    U8 u8Temp[8];

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    memcpy(u8Temp, pBuff + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize - 8, 8);
    memcpy(pBuff + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize - 8, u8SubNodeVCN, 8);
    memcpy(u8SubNodeVCN, u8Temp, 8);
    if(pIndexHeader->u8PositionStackCount == 0)
    {
        pIndexHeader->bRootDirty = TRUE;
    }
    else
    {
        pIndexHeader->bRecordDirty = TRUE;
    }
    return TRUE;
}

static BOOLEAN N51FS_Delete_GetSubNodeVCN(U8* u8SubNodeVCN)
{
    U8* pBuff;

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(pIndexHeader->u32CurrentBuffAddr);

    memcpy(u8SubNodeVCN, pBuff + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize - 8, 8);
    return TRUE;
}

static BOOLEAN N51FS_Delete_Steal(U8 fsid)
{
    U32 u32Offset;

    N51FS_Delete_Index_GotoParent(fsid);
    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_END)
    {
        //steal from left
        goto STEAL_FROM_LEFT;
    }
    else
    {
        //move to next entry
        N51FS_Delete_Index_GotoNextEntry();
        N51FS_Delete_Index_GotoChild(fsid);
        if(pIndexHeader->indexEntry.bIsLastEntry)
        {
            N51FS_Delete_Index_GotoParent(fsid);
            N51FS_Delete_Index_GotoPrevEntry();
            goto STEAL_FROM_LEFT;
        }
        else
        {
            //copy current entry to sdram first
            msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, N51FS_TEMP_4K_BACKUP_BUFFER_2, pIndexHeader->indexEntry.EntrySize);
            u32Offset = pIndexHeader->indexEntry.EntrySize;
            N51FS_Delete_RemoveEntry(pIndexHeader->u8SubNodVCN);//then remove it
            N51FS_Delete_Index_GotoParent(fsid);
            N51FS_Delete_Index_GotoPrevEntry();

            //copy current entry to sdram
            msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, N51FS_TEMP_4K_BACKUP_BUFFER_2 + u32Offset, pIndexHeader->indexEntry.EntrySize);
            //replace current entry
            N51FS_Delete_ReplaceEntry(0);
            N51FS_Delete_Index_GotoChild(fsid);
            N51FS_Delete_InsertEntry(u32Offset);
            if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
            {
                N51FS_Delete_Index_GotoNextEntry();
                N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
                N51FS_Delete_Index_GotoPrevEntry();
                N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
            }
            return TRUE;
        }
    }

STEAL_FROM_LEFT:
    if(pIndexHeader->indexEntry.bIsFirstEntry)
    {
        N51FS_Delete_Index_GotoChild(fsid);
        return FALSE;
    }
    if(!N51FS_Delete_Index_GotoPrevEntry())
    {
        __ASSERT(0);
        return FALSE;
    }
    N51FS_Delete_Index_GotoChild(fsid);
    if(pIndexHeader->indexEntry.bIsLastEntry)
    {
        N51FS_Delete_Index_GotoParent(fsid);
        N51FS_Delete_Index_GotoNextEntry();
        N51FS_Delete_Index_GotoChild(fsid);
        return FALSE;
    }
    N51FS_Delete_Index_GotoLastEntry();
    //copy current entry to sdram first
    msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, N51FS_TEMP_4K_BACKUP_BUFFER_2, pIndexHeader->indexEntry.EntrySize);
    u32Offset = pIndexHeader->indexEntry.EntrySize;
    N51FS_Delete_RemoveEntry(pIndexHeader->u8SubNodVCN);//then remove it
    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
    }
    N51FS_Delete_Index_GotoParent(fsid);
    //copy current entry to sdram
    msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, N51FS_TEMP_4K_BACKUP_BUFFER_2 + u32Offset, pIndexHeader->indexEntry.EntrySize);
    //replace current entry
    N51FS_Delete_ReplaceEntry(0);
    //move to next entry
    N51FS_Delete_Index_GotoNextEntry();
    N51FS_Delete_Index_GotoChild(fsid);
    N51FS_Delete_InsertEntry(u32Offset);
    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
    }

    return TRUE;
}

static BOOLEAN N51FS_Delete_Combine(U8 fsid)
{
    U8 * pBuff;
    U8 u8SrcEntryFlag;
    U32 u32Size;
    U32 u32Length;
    U16 u16Temp=0;
    U32 u32Temp=0;

    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_GetSubNodeVCN(pIndexHeader->u8SubNodVCN);

    }
    N51FS_Delete_Index_GotoParent(fsid);

    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_END)
    {
        goto COMBINE_LEFT;
    }
    msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, N51FS_TEMP_4K_BACKUP_BUFFER_2, pIndexHeader->indexEntry.EntrySize);
    N51FS_Delete_Index_GotoNextEntry();
    N51FS_Delete_Index_GotoChild(fsid);
    N51FS_Delete_InsertEntry(0);
    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
    }
    N51FS_Delete_Index_GotoParent(fsid);
    N51FS_Delete_Index_GotoPrevEntry();
    N51FS_Delete_RemoveEntry(pIndexHeader->u8SubNodVCN);
    return TRUE;
COMBINE_LEFT:
    if(!N51FS_Delete_Index_GotoPrevEntry())
    {
        N51FS_Delete_Index_GotoChild(fsid);
        if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
        {
            N51FS_Delete_GetSubNodeVCN(pIndexHeader->u8SubNodVCN);
            N51FS_Delete_Index_GotoParent(fsid);
            N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
        }
        else
        {
            N51FS_Delete_Index_GotoParent(fsid);

            pBuff = (U8 xdata*)msAPI_FS_GetAddr(N51FS_TEMP_4K_BACKUP_BUFFER_0);

            //update MFT record size
            //u32Size = (*(U32 *)(pBuff + 0x18));
            memcpy(&u32Size,(pBuff + 0x18),4);
            u32Size -= 8;
            //*(U32 *)(pBuff + 0x18) = (u32Size);
            memcpy((pBuff + 0x18),&u32Size,4);

            u32Length = u32Size - pIndexHeader->u32CurrentRecordBytePosition - pIndexHeader->indexEntry.EntrySize + 8;

            //update Root attribute size
            //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4));
            memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),4);
            u32Size -= 8;
            //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4) = (u32Size);
            memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 4),&u32Size,4);

            //update Root attribute length
            //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10));
            memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),4);
            u32Size -= 8;
            //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10) = (u32Size);
            memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootAttr) + 0x10),&u32Size,4);

            //update Root record size
            //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4));
            memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),4);
            u32Size -= 8;
            //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4) = (u32Size);
            memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 4),&u32Size,4);

            //update Root record allocated size
            //u32Size = (*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8));
            memcpy(&u32Size,(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),4);
            u32Size -= 8;
            //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8) = (u32Size);
            memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 8),&u32Size,4);

            //set small index
            //*(U32 *)(pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 0x0C) = 0;
            u32Temp=0;
            memcpy((pBuff + (U16)(pIndexHeader->u32OffsetToIndexRootHeader) + 0x0C),&u32Temp,4);

            if(pIndexHeader->u32RunListAddr == N51FS_TEMP_4K_BACKUP_BUFFER_0 &&
               pIndexHeader->u16OffsetToRunList > pIndexHeader->u32OffsetToIndexRootAttr)
            {
                pIndexHeader->u16OffsetToRunList -= 8;
            }

            u8SrcEntryFlag = INDEX_ENTRY_FLAG_BIT_END;
            *(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 0x0C) = u8SrcEntryFlag;
            //*(U16 *)(pBuff + pIndexHeader->u32CurrentRecordBytePosition + 8) = (pIndexHeader->indexEntry.EntrySize - 8);
            u16Temp=(pIndexHeader->indexEntry.EntrySize - 8);
            memcpy((pBuff + pIndexHeader->u32CurrentRecordBytePosition + 8),&u16Temp,2);

            msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize,
                              pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition + pIndexHeader->indexEntry.EntrySize - 8, u32Length);
            pIndexHeader->bRootDirty = TRUE;

        }
        return TRUE;
    }
    msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, N51FS_TEMP_4K_BACKUP_BUFFER_2, pIndexHeader->indexEntry.EntrySize);
    N51FS_Delete_Index_GotoChild(fsid);
    N51FS_Delete_Index_GotoNextEntry();
    N51FS_Delete_InsertEntry(0);
    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_Index_GotoNextEntry();
        N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
        N51FS_Delete_Index_GotoPrevEntry();
        N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
    }
    N51FS_Delete_Index_GotoParent(fsid);
    N51FS_Delete_RemoveEntry(pIndexHeader->u8SubNodVCN);//then remove it
    if(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_ReplaceSubNodeVCN(pIndexHeader->u8SubNodVCN);
    }
    return TRUE;
}

BOOLEAN N51FS_Delete_RemoveLeaf(U8 fsid)
{
    BOOLEAN bContinue = TRUE;
    if(!N51FS_Delete_RemoveEntry(pIndexHeader->u8SubNodVCN))
    {
        __ASSERT(0);
        return FALSE;
    }

    while(bContinue && pIndexHeader->indexEntry.bIsFirstEntry && pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_END)
    {
        if(pIndexHeader->u8PositionStackCount == 0)
        {
            break;
        }
        bContinue = FALSE;
        //Steal
        if(!N51FS_Delete_Steal(fsid))
        {
            //combine
            bContinue = TRUE;
            if(!N51FS_Delete_Combine(fsid))
            {
                __ASSERT(0);
                return FALSE;
            }
        }
    }

    if(pIndexHeader->bRecordDirty)
    {
        N51FS_Delete_SaveRecordToDisk(fsid);
    }
    return TRUE;
}

BOOLEAN N51FS_Delete_RemoveNode(U8 fsid)
{
    U8 u8LayerCount = 0;

    //move to next entry
    N51FS_Delete_Index_GotoNextEntry();
    while(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_Index_GotoChild(fsid);
        u8LayerCount++;
    }
    msAPI_FS_MIU_Copy(pIndexHeader->u32CurrentBuffAddr + pIndexHeader->u32CurrentRecordBytePosition, N51FS_TEMP_4K_BACKUP_BUFFER_2, pIndexHeader->indexEntry.EntrySize);
    while(u8LayerCount)
    {
        N51FS_Delete_Index_GotoParent(fsid);
        u8LayerCount--;
    }
    N51FS_Delete_Index_GotoPrevEntry();
    N51FS_Delete_ReplaceEntry(0);
    N51FS_Delete_Index_GotoNextEntry();
    while(pIndexHeader->indexEntry.EntryFlag & INDEX_ENTRY_FLAG_BIT_NODE)
    {
        N51FS_Delete_Index_GotoChild(fsid);
    }

    return TRUE;
}

BOOLEAN N51FS_Delete_MarkMFTRecordUnused(U8 fsid, U32 MFR)
{
    N51FS_FileSysStruct* pfst;
    U32 recordSector;
    U32 physicalStartSector;
    U8 deviceIndex;
    U8 *pBuff;

    pfst = (N51FS_FileSysStruct*)FCtrl_GetFileSystemInfo(fsid);

    physicalStartSector = pfst->RelativeSector;
    deviceIndex = pfst->DeviceIndex;

    recordSector = physicalStartSector + N51FS_ReadMFT_LSN(fsid, MFR);
    if(!msAPI_MSDCtrl_SectorRead(deviceIndex,recordSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }

    pBuff = (U8 xdata*)msAPI_FS_GetAddr(USB_IO_TEMP_ADDR);

    pBuff[0x10] ++;     // sequence number incremented
    if(pBuff[0x10] == 0)
        pBuff[0x11] ++;
    pBuff[0x16] = 0x00;
    pBuff[0x17] = 0x00;

    if(!msAPI_MSDCtrl_SectorWrite(deviceIndex, recordSector, 1, USB_IO_TEMP_ADDR))
    {
        __ASSERT(0);
        return FALSE;
    }
    return TRUE;
}
#endif

#undef N51FS_INDEX_C

