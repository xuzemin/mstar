////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2013 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifdef SUPPORT_KMV
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "msmComm.h"
#include "mp4def.h"
#include "mp4util.h"
#include "mp4file.h"
#include "dmxinst.h"

#include "kmv/tool.h"
#include "kmv_api.h"
#ifdef SUPPORT_KMV_DRM
#include "ms_drmkey.h"
#endif

static int GetStcoKMV(MP4FILE *mp4_file, KMVCACHE *pstco, uint32_t chunk_idx,
               FILE_POS STCO_offset, FILE_POS *chunk_offset_e)
{
    uint32_t buffer_offset;
    //STCOKMV *pstco = (STCOKMV *)pTrack->m_pStcoProp;
    uint32_t *curr_page_idx;
    uint8_t *stco_page;
    uint8_t *buf;
    int errtn;

    stco_page       = pstco->cache_page;
    curr_page_idx   = &pstco->page_idx;

    errtn = KMVFileCacheBufferredPage(mp4_file, stco_page, curr_page_idx, STCO_offset,
        KMV_STCOENTRY, chunk_idx, &buffer_offset, KMV_STCO_CACHE);
    if (errtn == 3) {
        MP4_DBG_MSG("File System Error");
        return 1; //File ststem error
    }

    buf = stco_page+buffer_offset;
    *chunk_offset_e = ((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);
    return 0;
}


static int GetStszKMV(MP4FILE *mp4_file, KMVCACHE *pstsz, uint32_t frm_idx, uint32_t idxbefore,
               FILE_POS STSZ_offset, FILE_POS *chunk_offset_e,
               uint8_t *tType, uint16_t *recH, uint16_t *recW, uint16_t *nCompressedSize)
{
    uint32_t buffer_offset;
    uint32_t *curr_page_idx;
    uint8_t *stsz_page;
    uint8_t *buf;
    uint32_t idx;
    int errtn;

    stsz_page       = pstsz->cache_page;
    curr_page_idx   = &pstsz->page_idx;

    for (idx = 0; idx < frm_idx; idx++) {
        errtn = KMVFileCacheBufferredPage(mp4_file, stsz_page, curr_page_idx,
            STSZ_offset, KMV_STSZENTRY, (idx+idxbefore), &buffer_offset, KMV_STSZ_CACHE);
        if (errtn == 3) {
            MP4_DBG_MSG("File System Error");
            return 1; //File system error
        }

        buf = stsz_page+buffer_offset;
        *chunk_offset_e+=buf[5];
    }
    errtn = KMVFileCacheBufferredPage(mp4_file, stsz_page, curr_page_idx, STSZ_offset, 6,
        (frm_idx+idxbefore), &buffer_offset, KMV_STSZ_CACHE);
    if (errtn == 3) {
        MP4_DBG_MSG("File System Error");
        return 1; //File system error
    }
    buf = stsz_page+buffer_offset;
    *tType = buf[0];
    *recH  = (buf[2]<<8)|buf[1];
    *recW  = (buf[4]<<8)|buf[3];
    *nCompressedSize = buf[5];

    return 0;
}

static int GetMapKMV(MP4FILE *mp4_file, KMVCACHE *pmap,
              FILE_POS MAP_offset, FILE_POS data_offset,
              uint32_t nSize, unsigned char *BitsBuf)
{
    uint32_t buffer_offset;
    uint32_t *curr_page_idx;
    uint8_t *map_page;
    uint8_t *buf;
    uint32_t page_offset;
    FILE_OFF errtn;

    map_page        = pmap->cache_page;
    curr_page_idx   = &pmap->page_idx;
    page_offset = data_offset / KMV_MAP_CACHE;

    if (page_offset != *curr_page_idx)
    {
        errtn = MP4FileSetPosition(mp4_file, MAP_offset + page_offset*KMV_MAP_CACHE);
        if (errtn == -1)
        {
            MP4_DBG_MSG("File System Error");
            return 1; //File system error
        }
        MP4FileReadBytes(mp4_file, map_page, KMV_MAP_CACHE+KMV_MAPENTRY);
        *curr_page_idx = page_offset;
    }

    buffer_offset = data_offset - (*curr_page_idx)*KMV_MAP_CACHE;
    buf = map_page+buffer_offset;
    memcpy(BitsBuf,buf,nSize);
    return 0;
}

static int SeekKMVStartCode(MP4FILE *pmp4File, FILE_POS MP4offset)
{
#define KMVSyncWordSize 50
    char MP4Atom[5];
    int posKMV=0;
    FILE_OFF errtn;
    uint8_t KMVBuffer[KMVSyncWordSize];
    const char cbit[5] = {'S','T','S','Z','\0'};
    //const char cbit2[5] = {'S','T','C','O','\0'};
    FILE_POS CurPos, TotalSize;
    MP4Atom[4] = '\0';

    errtn = MP4FileSetPosition(pmp4File,MP4offset);
    if (errtn==-1) {
        return KMV_ERR_FILE_ERROR; //File system error
    }
    CurPos = MP4FileGetPosition(pmp4File);
    TotalSize = MP4FileGetSize(pmp4File);
    if ((TotalSize - CurPos) < KMVSyncWordSize)
        return KMV_ERR_NOT_KMV;   // Not KMV clip

    if (MP4FileReadBytes(pmp4File, KMVBuffer, KMVSyncWordSize) != KMVSyncWordSize)
        return KMV_ERR_NOT_KMV;

    while (posKMV<(KMVSyncWordSize-4))
    {
        memcpy(MP4Atom, &(KMVBuffer[posKMV]),4);
        if (strcmp(MP4Atom,cbit) == 0)
            return KMV_ERR_FILE_ERROR; //Broken KMV Clip
        else
            posKMV+=1;
    }
    return KMV_ERR_NOT_KMV;  //Not KMV Clip
}

static int init_metaoffset(MP4FILE *pmp4File, FILE_POS MP4offset)
{
    char MP4Atom[5];
    const char cbit[5] = {'S','T','S','Z','\0'};
    const char cbit2[5] = {'S','T','C','O','\0'};
    static const uint8_t gIndxSyncWord[KMV_SYNCWORD_LENGTH] = { 0x11, 0x22, 0x33, 0x44 }; // IDX_SYNCWORD
    uint32_t tFrameNo;

    uint8_t SyncWord[KMV_SYNCWORD_LENGTH];
    uint8_t *SyncWord_p = SyncWord;
    //uint8_t* pMapBuf = (uint8_t*)malloc(nFrameSizeInMbs);
    int ReadByte;
    FILE_OFF errtn;
    unsigned int nVersion, i;

    MP4Atom[4] = '\0';

    errtn = MP4FileSetPosition(pmp4File, MP4offset);
    if (errtn == -1)
        return KMV_ERR_FILE_ERROR; //File system error

    //Init Meta Data Offset
    ReadByte = MP4FileReadBytes(pmp4File, (uint8_t*)MP4Atom,4);
    if (ReadByte != 4) {
        return KMV_ERR_NOT_KMV; // MP4 Clip
    }

    if (!mp4_strcasecmp(MP4Atom,cbit2)) {
        MP4FileReadBytes(pmp4File, &pmp4File->m_tSTCO, 4);
        MP4_DBG_MSG("Total Chunk Offset 0x%x\n", pmp4File->m_tSTCO);
        MP4FileReadBytes(pmp4File, &pmp4File->m_nChunk, 3);
        MP4_DBG_MSG("Total No. of Chunk %d\n", pmp4File->m_nChunk);
        MP4FileReadBytes(pmp4File, &pmp4File->m_SampleInChunk, 1);
        MP4_DBG_MSG("No. of Samples in a Chunk %d\n", pmp4File->m_SampleInChunk);
    } else {
        MP4_DBG_MSG("Error: Sample Table Chunk Offset\n");
        return SeekKMVStartCode(pmp4File,MP4offset);
    }

    //check Sample Table Sample Size
    errtn = MP4FileSetPosition(pmp4File, MP4offset + pmp4File->m_tSTCO);
    if (errtn==-1) {
        MP4_DBG_MSG("File system error");
        return KMV_ERR_FILE_ERROR; //File system error
    }

    errtn = MP4FileReadBytes(pmp4File,(uint8_t*)MP4Atom,4);
    if (errtn==-1) {
        MP4_DBG_MSG("File system error");
        return KMV_ERR_FILE_ERROR; //File system error
    }

    if (!strcmp(MP4Atom,cbit)) {
        MP4FileReadBytes(pmp4File, &tFrameNo, 4);
        MP4_DBG_MSG("Total Frame %d\n", tFrameNo);
    } else {
        MP4_DBG_MSG("Error: Sample Table Sample Size\n");
        return KMV_ERR_FILE_ERROR;  //Broken KMV Clip
    }
    pmp4File->m_metaoffset = pmp4File->m_tSTCO + KMV_STSZ_HEADER + (tFrameNo * KMV_SAMPLE_ELEMENT);
    // End of Init Meta Data offset


    errtn = MP4FileSetPosition(pmp4File, MP4offset + pmp4File->m_metaoffset);
    if (errtn==-1) {
        return KMV_ERR_FILE_ERROR; //File ststem error
    }

    // Check MetaData Header
    MP4FileReadBytes(pmp4File,(uint8_t *) SyncWord_p,KMV_SYNCWORD_LENGTH);
    //fread(SyncWord, 1, SYNCWORD_LENGTH, fin);
    for (i=0; i<KMV_SYNCWORD_LENGTH; i++) {
        if (SyncWord[i]!=gIndxSyncWord[i]) {
            MP4_DBG_MSG("Wrong index sync word!\n");
            return KMV_ERR_FILE_ERROR; //Broken KMV Clip
        }
    }
    MP4FileReadBytes(pmp4File,(uint8_t *) &nVersion,4);
    MP4_DBG_MSG("Content Version number =%d\n",(nVersion>>24));
    MP4_DBG_MSG("Tool Version number =%d\n",(nVersion&0xffffff));
    return KMV_SUCCESS;
}

static int GetMetaData(MP4FILE *pmp4File, FILE_POS MP4offset, FILE_POS MetaOffset,
                KMVCACHE *tSTCOKMV, KMVCACHE *tSTSZKMV, KMVCACHE *tMAPKMV,
                unsigned int nFrameCount,
                uint32_t tSTCO, uint32_t nChunk, uint32_t SampleInChunk,
                unsigned char *tType, unsigned short *recH, unsigned short *recW,
                unsigned char *pBitsBuf, uint16_t *nsize)
{

    FILE_POS pChOffset = 0, pFrameOffset = 0;
    uint32_t tnFrameCount = 0;
    //uint16_t nCompressedSize=0;
    unsigned int offsetidx;

    //assert(SampleInChunk==16);

    //Searching for Chunk offset
    if (SampleInChunk == 0) return 1;
    offsetidx = (nFrameCount/SampleInChunk);
    tnFrameCount = (nFrameCount%SampleInChunk);
    if(!(offsetidx<nChunk))
        return 1;
    //assert(offsetidx<nChunk);


    if (GetStcoKMV(pmp4File,tSTCOKMV,offsetidx,(MP4offset+KMV_STCO_HEADER),&pChOffset))
        return 1;

    if (GetStszKMV(pmp4File,tSTSZKMV,tnFrameCount, (offsetidx*SampleInChunk),(MP4offset+tSTCO+KMV_STSZ_HEADER), &pFrameOffset, tType, recH, recW, nsize))
        return 1;

    if (GetMapKMV(pmp4File,tMAPKMV,(MP4offset+MetaOffset+KMV_META_HEADER),(pChOffset+pFrameOffset),*nsize, pBitsBuf))
        return 1;
    //*nsize = nCompressedSize;
    //diag_printf("tType =%d, recH=%d, recW=%d \n",*tType, *recH, *recW);

    if ((*tType<127)||(
#ifdef SUPPORT_KMV_HVGA
        ((*recH!=320)||(*recW!=480))&&
#endif
        ((*recH!=240)||(*recW!=320))&&
        ((*recH!=180)||(*recW!=240))))
        return 1;

    return 0;
}

static void MP4DMX_InitKMVCache(void *pInst, uint8_t *cache, uint8_t *aescache)
{
    MP4DMXInst *pDmx  = (MP4DMXInst *) pInst;
    MP4FILE    *pFile = (MP4FILE    *) pDmx->m_mp4File;

    pFile->m_STCOKMV.cache_page = cache;
    pFile->m_STCOKMV.page_idx   = 0xffffffff;

    pFile->m_STSZKMV.cache_page = pFile->m_STCOKMV.cache_page;
    pFile->m_STSZKMV.cache_page += KMV_STCO_CACHE;
    pFile->m_STSZKMV.cache_page += KMV_STCOENTRY;
    pFile->m_STSZKMV.page_idx   = 0xffffffff;

    pFile->m_MAPBUF.cache_page = pFile->m_STSZKMV.cache_page;
    pFile->m_MAPBUF.cache_page += KMV_STSZ_CACHE;
    pFile->m_MAPBUF.cache_page += KMV_STSZENTRY;
    pFile->m_MAPBUF.page_idx   = 0xffffffff;
    pFile->m_KMVAESCache       = aescache;
#ifdef SUPPORT_KMV_DRM
    KMV_AES_IniCachetab(pFile->m_KMVAESCache);
#endif
}

static void Arraysxor (uint8_t *dst)
{
    int i;
    static const uint8_t MSTAR[16]  = {'d', 'e', 'r', 'e', 't', 's', 'i', 'R', 'g', 'A', 'e', 'T', 'r', 'S', ' ', 'M'};
    for(i=0; i<16; i++) {
        dst[i] = dst[i] ^ MSTAR[i];
    }
}
static int IsNewScramble(MP4FILE *pFile)
{
#define Encrypt_KEY 16
#define Sync_Header 20
    char atomfn2[Sync_Header+1];
    atomfn2[Sync_Header] = '\0';

    MP4FileReadBytes(pFile, atomfn2, Sync_Header);
    //old encrypt atomfn would be STCO
    if (mp4_strcasecmp(atomfn2,"STSZMrSeTgAiRs tered") == 0) {
        MP4FileReadBytes(pFile, pFile->m_KMVscrm, Encrypt_KEY);
        Arraysxor(pFile->m_KMVscrm);
        return 1;
    }
    return 0;
}
#define DRM_vender         (1<<0)
#define DRM_user           (1<<1)
#define Scramble_v0        (1<<0)
#define Scramble_v1        (1<<1)

#define UUID_OFFSET 8
#define UUID_SN 16
#define UUID_KMV 4
#define UUID_DES_HEADER 12
#define UUID_DES_CONTENT 6
#define UUID_FILE_TYPE 3
#define UUID_FILE_TYPE_EXT 3
#define UUID_FILE_MIME_TYPE 11
#define UUID_HEADER (UUID_OFFSET+UUID_SN+UUID_KMV+UUID_DES_HEADER+UUID_DES_CONTENT+UUID_FILE_TYPE+UUID_FILE_TYPE_EXT+UUID_FILE_MIME_TYPE)
#define Fake_UUID_HEADER (UUID_HEADER)
#define CACode_DRM 16
#define Content_Key 16
#define UUID_DRM (1+CACode_DRM+Content_Key)
#define GUID_KMV 16
#define PAST_UUID 4

static int CheckUUIDTag(char atomfn[5], int chktype, int newScramble)
{
    int retval = 0;

    if (chktype & DRM_vender) {
        if(newScramble & Scramble_v0) {
            retval |= ((mp4_strcasecmp(atomfn,"kmvd") ==0)?1:0);
        }
        if(newScramble & Scramble_v1) {
            retval |= ((mp4_strcasecmp(atomfn,"kvd2") ==0)?1:0);
        }
    }
    if (chktype & DRM_user) {
        if (newScramble & Scramble_v0) {
            retval = retval | ((mp4_strcasecmp(atomfn,"kmpw")==0)?1:0);
        }
        if (newScramble & Scramble_v1) {
            retval |= ((mp4_strcasecmp(atomfn,"kpw2") ==0)?1:0);
        }
    }
    return retval;
}

static void PeekHVGAoffset(MP4DMXInst *pDmx, FILE_POS *m_start)
{
    MP4FILE *pFile = pDmx->m_mp4File;
    char atomfn[5];
    atomfn[4] = '\0';
    if (!CheckUUIDTag(atomfn, DRM_vender, Scramble_v0))
    {
        //peek hvga or not
        if (MP4FileSetPosition(pFile, (*m_start + UUID_HEADER - PAST_UUID)) != (FILE_OFF)-1) {
            MP4FileReadBytes(pFile, atomfn, PAST_UUID);
            if ((atomfn[0] == '3' && atomfn[1] == 'd') ||
                mp4_strcasecmp(atomfn,"khvq") == 0) {
                *m_start += Sync_Header;
                *m_start += Encrypt_KEY;
            }
            if ((atomfn[0] == '3' && atomfn[1] == 'd')) {
                uint8_t kmv_type = atomfn[2]-0x30;
                uint8_t kmv_anaglyph = atomfn[3]-0x30;
                pDmx->m_KMV_type = pDmx->m_KMV_type | kmv_type;
                KMV_Init3Dfmt(kmv_anaglyph, &pDmx->m_KMV_type);
            }
        }
    }
}

static int MP4DMX_GetKMV_MetaOffset(void *pInst, FILE_POS *metaoffset, const uint8_t passwd[16])
{
#ifdef SUPPORT_KMV_DRM
    static const uint8_t CACode[CACode_DRM] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};
    static const uint8_t KMVTag[4] = {0x00, 0x00, 0x00, 0x01};
    uint8_t pivot = 0xff;
    uint8_t KMVE2P[4 + CACode_DRM] = {0};
    uint8_t ContentCode[CACode_DRM];
#endif

    uint32_t RetVal = KMV_SUCCESS;
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    FILE_POS m_start;

    char atomfn[5];
    atomfn[4] = '\0';

    pFile = pDmx->m_mp4File;
    memset(pFile->m_KMVscrm, 0xff, 16);

    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.uuid");
    if(!pDataATom)
        return KMV_ERR_NOT_KMV;

    m_start = pDataATom->m_start;
    if (MP4FileSetPosition(pFile, (m_start + UUID_OFFSET+UUID_SN)) == (FILE_OFF)-1)
        return KMV_ERR_NOT_KMV;

    MP4FileReadBytes(pFile,(uint8_t*)atomfn,4);

    if (mp4_strcasecmp(atomfn,"kmvs")!=0) { //not http streaming case
#ifdef SUPPORT_KMV_DRM
        // check KMV DRM atom
        if (CheckUUIDTag(atomfn, DRM_user|DRM_vender, Scramble_v0|Scramble_v1)) {
            if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER)) == (FILE_OFF)-1)
                return KMV_ERR_NOT_KMV;
            pDmx->m_KMV_type = KMV_DRM;
            m_start += UUID_DRM;
            if (CheckUUIDTag(atomfn, DRM_user, Scramble_v0|Scramble_v1) ||
                CheckUUIDTag(atomfn, DRM_vender, Scramble_v1))
            {
                m_start += GUID_KMV;
                m_start += PAST_UUID;
            }
            if (CheckUUIDTag(atomfn, DRM_vender, Scramble_v0|Scramble_v1))
            {
                MMP_GetKey(KMVE2P, KEY_KMV);
                if (memcmp(KMVE2P, KMVTag, 4)) {
                    RetVal = KMV_DMX_LICENSE_NOTEXIST;
                if (CheckUUIDTag(atomfn, DRM_vender, Scramble_v1)) PeekHVGAoffset(pDmx, &m_start);
                    goto END_OF_GetKMV_MetaOffset;
                }
            } else if (passwd != NULL)
                memcpy(KMVE2P + 4, passwd, 16);

            // get 1st key for CA Code decryption
            MP4FileReadBytes(pFile, &pivot, 1);
            KMV_Scramble(KMVE2P + 4, pivot);
            memcpy(pFile->m_KMVkey, (KMVE2P + 4), 16);

            //Check CA Code == Content Code
            MP4FileReadBytes(pFile, ContentCode, CACode_DRM);
            KMV_AES_Decode(ContentCode, CACode_DRM, pFile->m_KMVkey, 0);
            if (memcmp(ContentCode, CACode, CACode_DRM)) {
                if (CheckUUIDTag(atomfn, DRM_user, Scramble_v0)) {
                    RetVal = KMV_DMX_PASSWORD_MISMATCH;
                }
                else if (CheckUUIDTag(atomfn, DRM_user, Scramble_v1))
                {
                    PeekHVGAoffset(pDmx, &m_start);
                    RetVal = KMV_DMX_PASSWORD_MISMATCH;
                }
                else {
                    RetVal = KMV_DMX_LICENSE_MISMATCH;
                    if (CheckUUIDTag(atomfn, DRM_vender, Scramble_v1))
                        PeekHVGAoffset(pDmx, &m_start);
                }
                goto END_OF_GetKMV_MetaOffset;
            }

            // get 2nd key for Content decryption
            MP4FileReadBytes(pFile, ContentCode, Content_Key);
            KMV_AES_Decode(ContentCode, Content_Key, pFile->m_KMVkey, 0);
            memcpy(pFile->m_KMVkey, ContentCode, 16);

            if (CheckUUIDTag(atomfn, DRM_user, Scramble_v0|Scramble_v1) ||
                CheckUUIDTag(atomfn, DRM_vender, Scramble_v1)) {
                if (CheckUUIDTag(atomfn, DRM_user|DRM_vender, Scramble_v1)) {
                    Arraysxor(pFile->m_KMVkey);
                }
                MP4FileReadBytes(pFile, ContentCode, GUID_KMV);
                MP4FileReadBytes(pFile, atomfn, PAST_UUID);
                if (mp4_strcasecmp(atomfn,"km4v") == 0) {
                    KMV_InitHQfmt(KMV_QVGA_M4V, &pDmx->m_KMV_type);
                } else if (mp4_strcasecmp(atomfn,"khvq") == 0) {
                    KMV_InitHQfmt(KMV_HVGA_M4V, &pDmx->m_KMV_type);
                    if(IsNewScramble(pFile)) {
                        m_start += Sync_Header;
                        m_start += Encrypt_KEY;
                    }
                }
#ifdef SUPPORT_KMV_3D
                else if (atomfn[0] == '3' && atomfn[1] == 'd') {
                    uint8_t kmv_type = atomfn[2]-0x30;
                    uint8_t kmv_anaglyph = atomfn[3]-0x30;

                    if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER)) == (FILE_OFF)-1)
                        return KMV_ERR_NOT_KMV;

                    pDmx->m_KMV_type = pDmx->m_KMV_type | kmv_type;
                    KMV_Init3Dfmt(kmv_anaglyph, &pDmx->m_KMV_type);
                    if(IsNewScramble(pFile)) {
                        m_start += Sync_Header;
                        m_start += Encrypt_KEY;
                    }
                }
#endif
            }
        } else
#endif
        {
            if (mp4_strcasecmp(atomfn,"kmve") == 0) { //SEI streaming Case
                if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER)) == (FILE_OFF)-1)
                    return KMV_ERR_NOT_KMV;
                KMV_InitSEIfmt(&pDmx->m_KMV_type);
                if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER + UUID_HEADER)) != (FILE_OFF)-1) {
                    if(IsNewScramble(pFile)) {
                        m_start += Sync_Header;
                        m_start += Encrypt_KEY;
                        m_start += UUID_HEADER;
                    }
                }
            }
            else if (mp4_strcasecmp(atomfn,"kmhq") == 0) {
                if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER)) == (FILE_OFF)-1)
                    return KMV_ERR_NOT_KMV;
                KMV_InitHQfmt(KMV_QVGA_AVC, &pDmx->m_KMV_type);
            } else if (mp4_strcasecmp(atomfn,"km4v") == 0) {
                if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER)) == (FILE_OFF)-1)
                    return KMV_ERR_NOT_KMV;
                KMV_InitHQfmt(KMV_QVGA_M4V, &pDmx->m_KMV_type);
            }
#ifdef SUPPORT_KMV_HVGA
            else if (mp4_strcasecmp(atomfn,"khvq") == 0) { //HVGA Case
                if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER)) == (FILE_OFF)-1)
                    return KMV_ERR_NOT_KMV;

                KMV_InitHQfmt(KMV_HVGA_M4V, &pDmx->m_KMV_type);
                if(IsNewScramble(pFile)) {
                    m_start += Sync_Header;
                    m_start += Encrypt_KEY;
                }
            }
#endif
#ifdef SUPPORT_KMV_3D
            else if (atomfn[0] == '3' && atomfn[1] == 'd') {
                uint8_t kmv_type = atomfn[2]-0x30;
                uint8_t kmv_anaglyph = atomfn[3]-0x30;
                if (MP4FileSetPosition(pFile, (m_start + UUID_HEADER)) == (FILE_OFF)-1)
                    return KMV_ERR_NOT_KMV;
                    pDmx->m_KMV_type = kmv_type;
                    KMV_Init3Dfmt(kmv_anaglyph, &pDmx->m_KMV_type);
                    if(IsNewScramble(pFile)) {
                        m_start += Sync_Header;
                        m_start += Encrypt_KEY;
                    }
                }
#endif
            else
                return KMV_ERR_NOT_KMV;
        }
    }
#ifdef SUPPORT_KMV_DRM
END_OF_GetKMV_MetaOffset:
#endif
    *metaoffset = m_start + UUID_HEADER;
    return RetVal;
}

static int MP4DMX_InitKMVMeta(void *pInst, const uint8_t passwd[16])
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    int errRtl = MSMERR_OK;
    MP4FILE *pfile = (MP4FILE*)pDmx->m_mp4File;
    FILE_POS metapos = pfile->m_pRootAtom->m_pChildAtoms.m_pTail->m_start;

#ifdef SUPPORT_KMV_DRM
    // always reset before InitKMVMeta
    memset(pfile->m_KMVkey, 0, 16);
#endif

    pDmx->m_KMV_type = KMV_NORMAL;
    pfile->m_MP4offset = metapos;
#define KMV_STREAMMING
#ifdef KMV_STREAMMING
    errRtl = MP4DMX_GetKMV_MetaOffset(pInst, &metapos, passwd);
    if (errRtl == KMV_SUCCESS) {
        errRtl = init_metaoffset(pfile, metapos);
        if (errRtl != KMV_SUCCESS) {
            return KMV_ERR_FILE_ERROR;
        }
    }
    else if (errRtl == KMV_DMX_LICENSE_NOTEXIST || errRtl == KMV_DMX_LICENSE_MISMATCH || errRtl == KMV_DMX_PASSWORD_MISMATCH)
    {
#ifdef SUPPORT_KMV_DRM
        memset(pfile->m_KMVkey, 0, 16);
#endif
        if (init_metaoffset(pfile, metapos) != KMV_SUCCESS) {
            return KMV_ERR_FILE_ERROR;
        }
    }
    else
#endif // KMV_STREAM

    {
        errRtl = init_metaoffset(pfile, metapos);
        if (errRtl != KMV_SUCCESS) {
            pDmx->m_KMV_type = KMV_NOT_KMV;
        }
    }
    pfile->m_MP4offset = metapos;

    return errRtl;
}

static int MP4DMX_ReadKMVMeta(void *pInst, uint32_t frameidx, uint8_t *tType,
    uint16_t *recH, uint16_t *recW, uint8_t *pBuf, uint16_t *nsize)
{
    int errRtl = MSMERR_OK;
    MP4FILE *pFile = (MP4FILE *) pInst;
    FILE_POS metapos = pFile->m_MP4offset;

    *nsize = 0;

    if (metapos > pFile->m_fileSize)
        return MSMERR_DMX_EOF;

    frameidx -= 1;
    errRtl = GetMetaData(pFile, metapos, pFile->m_metaoffset,
                         &pFile->m_STCOKMV, &pFile->m_STSZKMV,
                         &pFile->m_MAPBUF, frameidx,
                         pFile->m_tSTCO,
                         pFile->m_nChunk, pFile->m_SampleInChunk,
                         tType, recH, recW, pBuf, nsize);

    if (errRtl != MSMERR_OK)
        *nsize = 0;

    return errRtl;
}

static int MP4DMX_GetKMV_Name(void *pInst, unsigned char * name, int max_length)
{
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    int read_count;
    name[0] = '\0';

    pFile = pDmx->m_mp4File;
    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.ilst." "\xA9" "nam.data");
    if(!pDataATom)
        return 0;
    if (MP4FileSetPosition(pFile,pDataATom->m_start + 16) == (FILE_OFF)-1) // 8 bytes for atom size and atom type, 4 bytes null, 1 byte version, 3 bytes flag
        return 0;
    read_count = MP4_MIN((int)pDataATom->m_size - 8, max_length);
    if (read_count < 0)
        return 0;
    else
    {
        MP4FileReadBytes(pFile,name,read_count);
        if (read_count < max_length)
        {
            name[read_count] = '\0';
            read_count++;
        }
        return read_count;
    }
}

static void MP4DMX_GetKMV_Year(void *pInst, unsigned short * year)
{
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    char temp[5];
    *year = 0;
    pFile = pDmx->m_mp4File;
    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.ilst." "\xA9" "day.data");
    if(!pDataATom)
        return;
    if (MP4FileSetPosition(pFile,pDataATom->m_start + 16) == (FILE_OFF)-1) // 8 bytes for atom size and atom type, 4 bytes null, 1 byte version, 3 bytes flag
        return;
    assert(pDataATom->m_size - 8 >= 4);
    MP4FileReadBytes(pFile,(uint8_t*)temp,4); // ex : year 2010
    temp[4] = '\0';
    *year = atoi(temp);
}

static void MP4DMX_GetKMV_Duration(void *pInst, unsigned short * duration)
{
    // unit : minute
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    char temp[5];
    *duration = 0;
    pFile = pDmx->m_mp4File;
    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.ilst." "\xA9" "cmt.data");
    if(!pDataATom)
        return;
    if (MP4FileSetPosition(pFile,pDataATom->m_start + 16) == (FILE_OFF)-1) // 8 bytes for atom size and atom type, 4 bytes null, 1 byte version, 3 bytes flag
        return;
    MP4FileReadBytes(pFile,(uint8_t*)temp,4); // assume the duration is at most 4-digit
    temp[4] = '\0';
    *duration = atoi(temp);
}

static void MP4DMX_GetKMV_Cover(void *pInst, unsigned char *coverBuffer, unsigned int *coverLength, int max_length)
{
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    int read_count;
    *coverLength = 0;
    if(coverBuffer == NULL)
    {
        return;
    }
    pFile = pDmx->m_mp4File;
    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.ilst.covr.data");
    if(!pDataATom)
        return;
    if (MP4FileSetPosition(pFile,pDataATom->m_start + 16) == (FILE_OFF)-1) // 8 bytes for atom size and atom type, 4 bytes null, 1 byte version, 3 bytes flag
        return;
    read_count = MP4_MIN((int)pDataATom->m_size - 8, max_length);
    if(read_count < 0)
        *coverLength = 0;
    else
    {
        MP4FileReadBytes(pFile,coverBuffer,read_count);
        *coverLength = read_count;
    }
}

static int MP4DMX_GetKMV_Starring(void *pInst, unsigned char * starring, int max_length)
{
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    int read_count;
    starring[0] = '\0';

    pFile = pDmx->m_mp4File;
    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.ilst." "\xA9" "art.data");
    if(!pDataATom)
        return 0;
    if (MP4FileSetPosition(pFile,pDataATom->m_start + 16) == (FILE_OFF)-1) // 8 bytes for atom size and atom type, 4 bytes null, 1 byte version, 3 bytes flag
        return 0;
    read_count = MP4_MIN((int)pDataATom->m_size - 8, max_length);
    if (read_count < 0)
    {
        return 0;
    }
    else
    {
        MP4FileReadBytes(pFile,starring,read_count);
        if (read_count < max_length)
        {
            starring[read_count] = '\0';
            read_count++;
        }
        return read_count;
    }
}

static int MP4DMX_GetKMV_Synopsis(void *pInst, unsigned char * synopsis, int max_length)
{
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    int read_count;
    synopsis[0] = '\0';

    pFile = pDmx->m_mp4File;
    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.ilst." "\xA9" "lyr.data");
    if(!pDataATom)
        return 0;
    if (MP4FileSetPosition(pFile,pDataATom->m_start + 16) == (FILE_OFF)-1) // 8 bytes for atom size and atom type, 4 bytes null, 1 byte version, 3 bytes flag
        return 0;
    read_count = MP4_MIN((int)pDataATom->m_size - 8, max_length);
    if (read_count < 0)
        return 0;
    else
    {
        MP4FileReadBytes(pFile,synopsis,read_count);
        if (read_count < max_length)
        {
            synopsis[read_count] = '\0';
            read_count++;
        }
        return read_count;
    }
}

static void MP4DMX_GetKMV_Category(void *pInst, unsigned int * category)
{
    // category use enumerator, range 0~18
    MP4FILE *pFile;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4ATOM *pDataATom;
    int read_count;
    char temp[3];
    *category = 0xff;
    pFile = pDmx->m_mp4File;
    pDataATom = MP4AtomFindAtom(pFile->m_pRootAtom,"moov.udta.meta.ilst." "\xA9" "grp.data");
    if(!pDataATom)
        return;
    if (MP4FileSetPosition(pFile,pDataATom->m_start + 16) == (FILE_OFF)-1) // 8 bytes for atom size and atom type, 4 bytes null, 1 byte version, 3 bytes flag
        return;
    // the category is classfied by enum, the number of entry is at most 99 => at most 2 char is enough
    if(pDataATom->m_size == 10)
    {
        read_count = 2;
        MP4FileReadBytes(pFile,(uint8_t*)temp,read_count);
        temp[read_count] = '\0';
        *category = atoi(temp);
    }
    else if (pDataATom->m_size == 9)
    {
        read_count = 1;
        MP4FileReadBytes(pFile,(uint8_t*)temp,read_count);
        temp[read_count] = '\0';
        *category = atoi(temp);
    }
}

int Enable_kmv_demux_plugin(kmv_func_st *kmv_hdr)
{
    if (!kmv_hdr) return 0;

    kmv_hdr->MP4DMX_GetKMV_Name          = MP4DMX_GetKMV_Name;
    kmv_hdr->MP4DMX_GetKMV_Year          = MP4DMX_GetKMV_Year;
    kmv_hdr->MP4DMX_GetKMV_Starring      = MP4DMX_GetKMV_Starring;
    kmv_hdr->MP4DMX_GetKMV_Cover         = MP4DMX_GetKMV_Cover;
    kmv_hdr->MP4DMX_GetKMV_Synopsis      = MP4DMX_GetKMV_Synopsis;
    kmv_hdr->MP4DMX_GetKMV_Category      = MP4DMX_GetKMV_Category;
    kmv_hdr->MP4DMX_GetKMV_Duration      = MP4DMX_GetKMV_Duration;
    kmv_hdr->MP4DMX_InitKMVCache         = MP4DMX_InitKMVCache;
    kmv_hdr->MP4DMX_InitKMVMeta          = MP4DMX_InitKMVMeta;
    kmv_hdr->MP4DMX_ReadKMVMeta          = MP4DMX_ReadKMVMeta;

    return 1;
}
#endif // SUPPORT_KMV
