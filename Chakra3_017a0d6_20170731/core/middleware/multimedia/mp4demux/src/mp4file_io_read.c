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


#include <string.h>
#include <assert.h>
#include "ms_io.h"
#include "mp4file.h"
#include "mp4util.h"
#ifdef MIPSDEV
#include "ms-cexcept.h"
#endif

cb_off_t MP4FileSkipBytes(MP4FILE *pfile, FILE_OFF numBytes)
{
#ifdef USE_STREAM_LIB
    return pfile->cbuffer.cb_seek64(&pfile->cbuffer, numBytes, CB_SEEK_CUR);
#else
    return pfile->m_cbio->seek(pfile->m_cbio, numBytes, SEEK_CUR);
#endif
}

uint8_t MP4FileReadUInt8(MP4FILE *pfile)
{
    uint8_t data=0;
   if (MP4FileReadBytes(pfile, &data, 1) != 1)
        return 0;

    return data;
}

uint32_t MP4FileReadBytes(MP4FILE *pmp4file, void *pBytes, uint32_t numBytes)
{
    uint32_t readbytes =0;

    // handle degenerate cases
    if (numBytes == 0)
        return 0;

#ifdef USE_STREAM_LIB
    readbytes = pmp4file->cbuffer.cb_read(&pmp4file->cbuffer, pBytes, numBytes);
#else
    readbytes = pmp4file->m_cbio->read(pmp4file->m_cbio, pBytes, numBytes);
#endif
    if (readbytes != numBytes)
        return readbytes;

    return numBytes;
}

#ifdef USE_ATOM_BUFFERRED_READ
uint32_t MP4FileCacheBufferredPage(MP4FILE *mp4_file, uint8_t *page, uint32_t *curr_page_index,
                                    FILE_POS atom_file_pos, uint32_t table_size, uint32_t cache_size, uint32_t entry_size, uint32_t entry_index
                                    , uint32_t *buffer_offset)
{
    uint32_t page_offset;

    page_offset = (entry_index * entry_size) / cache_size;

    if (page_offset != *curr_page_index)
    {
        uint32_t read_size;

#ifdef CACHE_ENTIRE_ATOM
        assert(*curr_page_index == (uint32_t)-1);
#endif
        MP4FileSetPosition(mp4_file, atom_file_pos + page_offset * cache_size);
        // get the remaining size of current table
        read_size = table_size - page_offset * cache_size;
        // read size is the min of cache page size and remaining size
        read_size = MP4_MIN(cache_size + entry_size, read_size);
        MP4FileReadBytes(mp4_file, page, read_size);
        *curr_page_index = page_offset;
    }

    *buffer_offset = entry_index * entry_size - (*curr_page_index) * cache_size;

    return 0;
}

uint32_t MP4FileReadBufferredBytes(uint8_t* pBufferredBytes, uint8_t* pBytes, uint32_t *read_start, uint32_t numBytes)
{
    // handle degenerate cases
    if (numBytes == 0)
        return 0;

    memcpy((void*)pBytes, (void*)(pBufferredBytes+(*read_start)), numBytes);

    *read_start += numBytes;

    return numBytes;
}

uint16_t MP4FileReadBufferredUInt16(uint8_t* pBufferredBytes, uint32_t *read_start)
{
    uint8_t *buf = pBufferredBytes+(*read_start);

    *read_start += 2;
    return ((buf[0] << 8) | buf[1]);
}

uint32_t MP4FileReadBufferredUInt32(uint8_t* pBufferredBytes, uint32_t *read_start)
{
    uint8_t *buf = pBufferredBytes+(*read_start);

    *read_start += 4;
    return ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
}

uint64_t MP4FileReadBufferredUInt64(uint8_t* pBufferredBytes, uint32_t *read_start)
{
    uint64_t output;

    output = MP4FileReadBufferredUInt32(pBufferredBytes, read_start);
    output <<= 32;
    output |= MP4FileReadBufferredUInt32(pBufferredBytes, read_start);

    return output;
}
#endif

#ifdef SUPPORT_KMV
uint32_t KMVFileCacheBufferredPage(MP4FILE *mp4_file, uint8_t *page, uint32_t *curr_page_index,
                                   FILE_POS atom_file_pos, uint32_t entry_size, uint32_t entry_index
                                   , uint32_t *buffer_offset, uint32_t CacheSize)
{
    uint32_t page_offset;
    FILE_OFF errtn;

    page_offset = entry_index * entry_size / CacheSize;
    if (page_offset != *curr_page_index)
    {
        errtn = MP4FileSetPosition(mp4_file, atom_file_pos + page_offset*CacheSize);
        if (errtn == -1)
            return 3; //File ststem error

        MP4FileReadBytes(mp4_file, page, CacheSize+entry_size);
        *curr_page_index = page_offset;
    }

    *buffer_offset = entry_index*entry_size - (*curr_page_index)*CacheSize;

    return 0;
}
#endif // SUPPORT_KMV

uint16_t MP4FileReadUInt16(MP4FILE *pfile)
{
    uint8_t data[2] = {0};

    if (MP4FileReadBytes(pfile, &data[0], 2) != 2)
        return 0;

    return ((data[0] << 8) | data[1]);
}

uint32_t MP4FileReadUInt32(MP4FILE *pfile)
{
    uint8_t data[4] = {0};

    if (MP4FileReadBytes(pfile, &data[0], 4) != 4)
        return 0;

    return ((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
}

uint64_t MP4FileReadUInt64(MP4FILE *pfile)
{
    uint32_t i;
    uint8_t data[8] = {0};
    uint64_t result = 0;
    uint64_t temp;

    if (MP4FileReadBytes(pfile, &data[0], 8) != 8)
        return 0;

    for (i = 0; i < 8; i++) {
        temp = data[i];
        result |= temp << ((7 - i) * 8);
    }
    return result;
}
