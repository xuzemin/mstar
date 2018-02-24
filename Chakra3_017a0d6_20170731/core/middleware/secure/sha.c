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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#include "sha.h"

#define SHA1_OPTI_SPD               0 // enable is worse at 4K ICache.
#define SHA256_OPTI_SPD             1

#define blk0(i)                     (W[i] = data[i])

// SHA-256 Hash Computation

inline U32 rotrFixed(U32 x, unsigned int y)
{
    return((x>>y) | (x<<(sizeof(U32)*8-y)));
}

static const U32 SHA256_K[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define blk2(i)                     (W[i&15] += s1(W[(i-2)&15])+W[(i-7)&15]+s0(W[(i-15)&15]))

#define Ch(x,y,z)                   (z^(x&(y^z)))
#define Maj(x,y,z)                  ((x&y)|(z&(x|y)))

#define a(i)                        T[(0-i)&7]
#define b(i)                        T[(1-i)&7]
#define c(i)                        T[(2-i)&7]
#define d(i)                        T[(3-i)&7]
#define e(i)                        T[(4-i)&7]
#define f(i)                        T[(5-i)&7]
#define g(i)                        T[(6-i)&7]
#define h(i)                        T[(7-i)&7]

// for SHA256
#define S0(x)                       (rotrFixed(x,2)^rotrFixed(x,13)^rotrFixed(x,22))
#define S1(x)                       (rotrFixed(x,6)^rotrFixed(x,11)^rotrFixed(x,25))
#define s0(x)                       (rotrFixed(x,7)^rotrFixed(x,18)^(x>>3))
#define s1(x)                       (rotrFixed(x,17)^rotrFixed(x,19)^(x>>10))

#if SHA256_OPTI_SPD
#define R(i)                        h(i) += S1(e(i))+Ch(e(i),f(i),g(i))+SHA256_K[i+j]+(j?blk2(i):blk0(i));  \
	                                d(i) += h(i);                                                           \
                                    h(i) += S0(a(i)) + Maj(a(i),b(i),c(i))
#else
#define R(i)                        _R(i, j, W, T, data);
void _R(unsigned i, unsigned j, U32 *W, U32 *T, const U32 *data)
{
    h(i) += S1(e(i))+Ch(e(i),f(i),g(i))+SHA256_K[i+j]+(j?blk2(i):blk0(i));
	d(i) += h(i);
    h(i) += S0(a(i)) + Maj(a(i),b(i),c(i));
}
#endif

#define OBSELETE                    1
#if (!OBSELETE)
// Generate a padding data to specfied buffer and returen byte length of padded block
MS_U32 SHA1_SHA256_Pad(U8 *msg, U32 msglen, U8 *pad)
{
    //CAUTION: message buffer should be enough for padding to n*512 bits

    U32 padlen, padmsglen, pad_word_i, pad_word_end, pad_1;
    int i, pad_i;

    // msg + pad( + len_info(64) = n*512

    msg_word_i = (bitlen>>9)<<4; // bitlen / 512
    msg_word_end = (bitlen+31)>>5;

    if (bitlen % 512)
    {
        // copy last non-block message
        for (pad_i = 0; pad_i < (msg_word_end-msg_word_i); i++)
        {
            pad[pad_i] = *(((U32*)msg)+(msg_word_i+pad_i));
        }

        pad[0] = *(((U32*)msg)+(bitlen%512));
        pad_1 = 1 << (31-(bitlen%32));
        pad[0] = (pad[0] & ~(pad_1-1)) | pad_1;
    }
    else
    {
        pad[0] = 0x80000000;
        for (i = 1; i < 15; i++)
        {
            pad[0];
        }
        pad[15] = bitlen;
        return 16;
    }

    pad_word_len = (bitlen%512)
                   pad_word_end = (((bitlen + 1 + 64) + 511) & ~512) >> (3+2);

    // padding 1

    // padding 0
    for (i = pad_word_i+1; i < pad_word_end; i++)
    {
        *(((U32*)msg)+i) = 0;
    }

    // padding len
    *(((U32*)msg)+pad_word_end) = bitlen;
}
#endif

void SHA256_Init(U32 *hash)
{
    hash[0] = 0x6a09e667;
    hash[1] = 0xbb67ae85;
    hash[2] = 0x3c6ef372;
    hash[3] = 0xa54ff53a;
    hash[4] = 0x510e527f;
    hash[5] = 0x9b05688c;
    hash[6] = 0x1f83d9ab;
    hash[7] = 0x5be0cd19;
}

void SHA256_Hash(const U32 *data, U32 *hash)
{
    U32                 W[16];
    U32                 T[8];
    int                 j;

    // Initialize state and local variable
    for (j = 0; j < 16; j++)
    {
        W[j] = 0;
    }

    for (j = 0; j < 8; j++)
    {
        T[j] = hash[j];
    }

    // Interative Hash Computation
    for (j = 0; j < 64; j += 16)
    {
        /* R( 0)
        h(0) += S1(e(0))+Ch(e(0),f(0),g(0))+SHA256_K[0+j]+(j?blk2(0):blk0(0));
        d(0) += h(0);
        h(0) += S0(a(0)) + Maj(a(0),b(0),c(0));
        */
        R( 0); R( 1); R( 2); R( 3);
        R( 4); R( 5); R( 6); R( 7);
        R( 8); R( 9); R(10); R(11);
        R(12); R(13); R(14); R(15);
    }

    // Update new hash value
    hash[0] += a(0);
    hash[1] += b(0);
    hash[2] += c(0);
    hash[3] += d(0);
    hash[4] += e(0);
    hash[5] += f(0);
    hash[6] += g(0);
    hash[7] += h(0);
}

// SHA-1 Hash Computation
inline U32 rotlFixed(U32 x, unsigned int y)
{
    return((x<<y) | (x>>(sizeof(U32)*8-y)));
}

#define blk1(i)                     (W[i&15] = rotlFixed(W[(i+13)&15]^W[(i+8)&15]^W[(i+2)&15]^W[i&15],1))

#define f1(x, y, z)                 (z^(x&(y^z)))
#define f2(x, y, z)                 (x^y^z)
#define f3(x, y, z)                 ((x&y)|(z&(x|y)))
#define f4(x, y, z)                 (x^y^z)

#if SHA1_OPTI_SPD

// (R0,R1), R2, R3, R4
#define R0(v, w, x, y, z, i)        z+= f1(w,x,y) + blk0(i) + 0x5A827999 + rotlFixed(v,5); w = rotlFixed(w,30);
#define R1(v, w, x, y, z, i)        z+= f1(w,x,y) + blk1(i) + 0x5A827999 + rotlFixed(v,5); w = rotlFixed(w,30);
#define R2(v, w, x, y, z, i)        z+= f2(w,x,y) + blk1(i) + 0x6ED9EBA1 + rotlFixed(v,5); w = rotlFixed(w,30);
#define R3(v, w, x, y, z, i)        z+= f3(w,x,y) + blk1(i) + 0x8F1BBCDC + rotlFixed(v,5); w = rotlFixed(w,30);
#define R4(v, w, x, y, z, i)        z+= f4(w,x,y) + blk1(i) + 0xCA62C1D6 + rotlFixed(v,5); w = rotlFixed(w,30);

#else

#define R0(v, w, x, y, z, i)        _R0(v, &w, x, y, &z, i, W, data)
#define R1(v, w, x, y, z, i)        _R1(v, &w, x, y, &z, i, W, data)
#define R2(v, w, x, y, z, i)        _R2(v, &w, x, y, &z, i, W, data)
#define R3(v, w, x, y, z, i)        _R3(v, &w, x, y, &z, i, W, data)
#define R4(v, w, x, y, z, i)        _R4(v, &w, x, y, &z, i, W, data)
void _R0(U32 v, U32 *w, U32 x, U32 y, U32 *z, unsigned int i, U32 *W, const U32 *data)
{
    data = data;
    *z += f1(*w, x, y) + blk0(i) + 0x5A827999 + rotlFixed(v, 5);
    *w = rotlFixed(*w, 30);
}
void _R1(U32 v, U32 *w, U32 x, U32 y, U32 *z, unsigned int i, U32 *W, const U32 *data)
{
    data = data;
    *z += f1(*w, x, y) + blk1(i) + 0x5A827999 + rotlFixed(v, 5);
    *w = rotlFixed(*w, 30);
}
void _R2(U32 v, U32 *w, U32 x, U32 y, U32 *z, unsigned int i, U32 *W, const U32 *data)
{
    data = data;
    *z += f2(*w, x, y) + blk1(i) + 0x6ED9EBA1 + rotlFixed(v, 5);
    *w = rotlFixed(*w, 30);
}
void _R3(U32 v, U32 *w, U32 x, U32 y, U32 *z, unsigned int i, U32 *W, const U32 *data)
{
    data = data;
    *z += f3(*w, x, y) + blk1(i) + 0x8F1BBCDC + rotlFixed(v, 5);
    *w = rotlFixed(*w, 30);
}
void _R4(U32 v, U32 *w, U32 x, U32 y, U32 *z, unsigned int i, U32 *W, const U32 *data)
{
    data = data;
    *z += f4(*w, x, y) + blk1(i) + 0xCA62C1D6 + rotlFixed(v, 5);
    *w = rotlFixed(*w, 30);
}

#endif

void SHA1_Init(U32 *hash)
{
    hash[0] = 0x67452301L;
    hash[1] = 0xEFCDAB89L;
    hash[2] = 0x98BADCFEL;
    hash[3] = 0x10325476L;
    hash[4] = 0xC3D2E1F0L;
}

void SHA1_Hash(const U32 *data, U32 *hash)
{
    U32                 W[16];
    U32                 A, B, C, D, E;
    int                 i;

#if !SHA1_OPTI_SPD
    U32 temp;
#endif

    for (i = 0; i < 16; i++)
    {
        W[i] = 0;
    }

    // Copy hash value to working variable
    A = hash[0];
    B = hash[1];
    C = hash[2];
    D = hash[3];
    E = hash[4];

    // 80 iteration of hash function
#if SHA1_OPTI_SPD

    R0(a, b, c, d, e,  0); R0(e, a, b, c, d,  1); R0( d, e, a, b, c,  2); R0( c, d, e, a, b,  3);
    R0(b, c, d, e, a,  4); R0(a, b, c, d, e,  5); R0( e, a, b, c, d,  6); R0( d, e, a, b, c,  7);
    R0(c, d, e, a, b,  8); R0(b, c, d, e, a,  9); R0( a, b, c, d, e, 10); R0( e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12); R0(c, d, e, a, b, 13); R0( b, c, d, e, a, 14); R0( a, b, c, d, e, 15);

    R1(e, a, b, c, d, 16); R1(d, e, a, b, c, 17); R1( c, d, e, a, b, 18); R1( b, c, d, e, a, 19);

    R2(a, b, c, d, e, 20); R2(e, a, b, c, d, 21); R2( d, e, a, b, c, 22); R2( c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24); R2(a, b, c, d, e, 25); R2( e, a, b, c, d, 26); R2( d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28); R2(b, c, d, e, a, 29); R2( a, b, c, d, e, 30); R2( e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32); R2(c, d, e, a, b, 33); R2( b, c, d, e, a, 34); R2( a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36); R2(d, e, a, b, c, 37); R2( c, d, e, a, b, 38); R2( b, c, d, e, a, 39);

    R3(a, b, c, d, e, 40); R3(e, a, b, c, d, 41); R3( d, e, a, b, c, 42); R3( c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44); R3(a, b, c, d, e, 45); R3( e, a, b, c, d, 46); R3( d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48); R3(b, c, d, e, a, 49); R3( a, b, c, d, e, 50); R3( e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52); R3(c, d, e, a, b, 53); R3( b, c, d, e, a, 54); R3( a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56); R3(d, e, a, b, c, 57); R3( c, d, e, a, b, 58); R3( b, c, d, e, a, 59);

    R4(a, b, c, d, e, 60); R4(e, a, b, c, d, 61); R4( d, e, a, b, c, 62); R4( c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64); R4(a, b, c, d, e, 65); R4( e, a, b, c, d, 66); R4( d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68); R4(b, c, d, e, a, 69); R4( a, b, c, d, e, 70); R4( e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72); R4(c, d, e, a, b, 73); R4( b, c, d, e, a, 74); R4( a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76); R4(d, e, a, b, c, 77); R4( c, d, e, a, b, 78); R4( b, c, d, e, a, 79);
#else
    i = 0;
    while (i < 16)
    {
        R0(A, B, C, D, E, i++);
        temp = A;
        A = E; E = D; D = C; C = B; B = temp;
    }
    while (i < 20)
    {
        R1(A, B, C, D, E, i++);
        temp = A;
        A = E; E = D; D = C; C = B; B = temp;
    }
    while (i < 40)
    {
        R2(A, B, C, D, E, i++);
        temp = A;
        A = E; E = D; D = C; C = B; B = temp;
    }
    while (i < 60)
    {
        R3(A, B, C, D, E, i++);
        temp = A;
        A = E; E = D; D = C; C = B; B = temp;
    }
    while (i < 80)
    {
        R4(A, B, C, D, E, i++);
        temp = A;
        A = E; E = D; D = C; C = B; B = temp;
    }
#endif

    // Add the working variable back to hash value
    hash[0] += A;
    hash[1] += B;
    hash[2] += C;
    hash[3] += D;
    hash[4] += E;
}

#define HASH_INIT                   SHA256_Init
#define HASH_FUNC                   SHA256_Hash

#define SHA_HASH_LEN 8 // 32-bit count, 5 for SHA-1, 8 for SHA-256,384,512

U32 sha_H[SHA_HASH_LEN];
SHA_BLOCK sha_M; // temp buffer for message block

void SECURE_Hash(U8 *pu8Message, U32 u32Length)
{
    U8 msg[4];
    int len, i;
    U32 msg_addr;
    U32 tmp;

    HASH_INIT(sha_H);

    msg_addr = (U32)(pu8Message);
    len = u32Length;

    while (len > 0)
    {
        if (len < 64) // last 1 data block
        {
            // move n*32 bits data
            for (i = 0; i < (len&~3);)
            {
                //*(U32*)msg = *(U32*)(msg_addr);
                msg[0] = *(U8 *)msg_addr;
                msg[1] = *((U8 *)msg_addr + 1);
                msg[2] = *((U8 *)msg_addr + 2);
                msg[3] = *((U8 *)msg_addr + 3);
                msg_addr += 4;

                sha_M[i/4] = (msg[0] << 24) | (msg[1] << 16) | (msg[2] << 8) | msg[3];
                i += 4;
            }

            // move non-32 bits data
            //shift = 24;
            //*(U32*)msg = *(U32*)(msg_addr);
            msg[0] = *(U8 *)msg_addr;
            msg[1] = *((U8 *)msg_addr + 1);
            msg[2] = *((U8 *)msg_addr + 2);
            msg[3] = *((U8 *)msg_addr + 3);
            msg_addr += 4;

            // append and stuffing
            sha_M[i/4] = 0;
            while (i < len)
            {
                sha_M[i/4] |= msg[i%4] << (24-((i%4)*8));
                i++;
                //shift -= 8;
            }
            // 1 append
            sha_M[i/4] |= 0x80 << (24-((i%4)*8));
            i = (i + 4) & ~3;

            if (i >= 56) // i=56~63, not enough for padding 8-byte(64-bit) length
            {
                // 0 append
                for (; i < 64;)
                {
                    sha_M[i/4] = 0;
                    i += 4;
                }
                HASH_FUNC(sha_M, sha_H);
                // reset to next block
                i = 0;
            }
            // 0 append
            for (; i < 56;)
            {
                sha_M[i/4] = 0;
                i += 4;
            }
            sha_M[14] = 0;
            sha_M[15] = u32Length << 3; // bit count
        }
        else
        {
            // move n*32 bits data
            for (i = 0; i < 64;)
            {
                //*(U32*)msg = *(U32*)(msg_addr);
                msg[0] = *(U8 *)msg_addr;
                msg[1] = *((U8 *)msg_addr + 1);
                msg[2] = *((U8 *)msg_addr + 2);
                msg[3] = *((U8 *)msg_addr + 3);
                msg_addr += 4;

                sha_M[i/4] = (msg[0] << 24) | (msg[1] << 16) | (msg[2] << 8) | msg[3];
                i += 4;
            }
        }
        HASH_FUNC(sha_M, sha_H);
        len -= 64;
    }

    // Hash revert to digit
    for (i = 0; i < SHA_HASH_DIGI_LEN/2; i++)
    {
        tmp = sha_H[SHA_HASH_DIGI_LEN-1-i];
        sha_H[SHA_HASH_DIGI_LEN-1-i] = sha_H[i];
        sha_H[i] = tmp;
    }
}

