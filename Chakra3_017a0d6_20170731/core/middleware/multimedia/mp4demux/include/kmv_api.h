////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2010-2012 MStar Semiconductor, Inc.
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


#ifndef KMV_API_H
#define KMV_API_H

#include <stdint.h>

//#define KMV_OUTBUF_FROM_GBUF

#ifdef KMV_OUTBUF_FROM_GBUF
#include "global_buffer.h"
#endif

#define KMV_ENCRYPT
//#define KMV_SPEED_MODE
//#define KMV_SPEED_INPLACE_MODE
//#define KMV_USE_HW_SCL
//#define KMV_USE_HW_DECODE

#define KMV_SYNCWORD_LENGTH     4
#define KMV_MAX_MB_LEN          396
#define KMV_META_LEN            (KMV_MAX_MB_LEN + KMV_SYNCWORD_LENGTH)
#define KMV_BUFFER_ELEMENT      (KMV_META_LEN + 2 + 2 + 2 + 1)
#define KMV_SMALL_RECBUF_SIZE   69120
#define KMV_AES_InvMixtab 256
#define KMV_AES_RoundKeyBuf 256
#define KMV_AES_CACHE ((KMV_AES_InvMixtab<<3) + KMV_AES_RoundKeyBuf)

// KMV Type:
// [3D FMT|Quality]:[VideoCodec]:[3D|SEI|Normal|NotKMV]
#define KMV_NOT_KMV          0x0000
#define KMV_NORMAL           0x0001
#define KMV_SEI              0x0002
#define KMV_DRM              0x0004
#define KMV_3D               0x0008
#define KMV_DUALVIEW         0x0010

#define KMV_AVC_FMT  0x0100
#define KMV_M4V_FMT  0x0200
#define KMV_QVGA     0x1000
#define KMV_HVGA     0x2000

//Anaglyph-type
typedef enum {
    KMV_BlackWhite = 3, //after KMV_HVGA
    KMV_RedCyan,
    KMV_GreenMagenta,
    KMV_YellowBlue,
    KMV_FakeRedCyan,
    Num_KMV_Anaglyp_TYPE,
} e_kmv_anaglyph;

//dual-view type
typedef enum {
    KMV_LR3D = 3, //after KMV_HVGA
    KMV_CrossEyed3D,
    KMV_TopDown3D,
    KMV_DownTop3D,
    KMV_HDMI3D,
    KMV_LeftRight3DReduced,
    KMV_CrossEyed3DReduced,
    KMV_Yt3D,
    KMV_TopDown3DReduced,
    KMV_DownTop3DReduced,
    KMV_MonoDepth,
    KMV_ProhibitedCharacters_0,// <
    KMV_ProhibitedCharacters_1,// ?
    KMV_FakeLR3D,
    KMV_FakeMonoDepth,
    Num_KMV_3D_TYPE,
} e_kmv_dualview_type;


#define KMV_QVGA_AVC (KMV_QVGA | KMV_AVC_FMT)
#define KMV_QVGA_M4V (KMV_QVGA | KMV_M4V_FMT)
#define KMV_HVGA_M4V (KMV_HVGA | KMV_M4V_FMT)

typedef enum KMVRetCode_e
{
    //KMV Return Message
    KMV_SUCCESS = 0x9000,
    KMV_ERR_NOT_KMV,
    KMV_ERR_FILE_ERROR,
    KMV_SMALL_RECT,
    //KMV DRM
    KMV_DMX_LICENSE_NOTEXIST  = 0x9209,
    KMV_DMX_LICENSE_MISMATCH,
    KMV_DMX_PASSWORD_MISMATCH
} KMVRetCode;

typedef struct kmv_class_s
{
    int g_rMB;
    int g_bMB;
    int g_tMB;
    int g_lMB;
    void *outframebuf;
    uint8_t *g_pMapBuf;
    int g_referenced;
    int g_preserved_fps;
#ifdef KMV_OUTBUF_FROM_GBUF
    global_buffer_st *pGbuf;
#endif
} KMV_Class;

typedef struct kmv_meta_s
{
    uint8_t  kmvMeta[KMV_META_LEN];
    uint16_t recH;
    uint16_t recW;
    uint16_t nsize;
    uint8_t  tType;
} kmv_meta_st;

typedef struct kmv_frame_buffer_ext
{
    uint8_t       **src_y;
    uint8_t       **src_u;
    uint8_t       **src_v;
    int             width;
    int             height;
    int            *stride_y;
    int            *stride_uv;
    kmv_meta_st    *kmv_metabuf;
    int             in_fmt;
    int             out_fmt;
    void          **privateData;
} KMV_frame_buffer_ext;

typedef void   (* pfn_free)(void *ctx, void *p);
typedef void * (* pfn_malloc)(void *ctx, int size);

void kmv_free(void *player, pfn_free cbfree, KMV_Class* kmv_obj, uint32_t* kmv_type);
int kmv_alloc(void *player, pfn_malloc cbmalloc, pfn_free cbfree, KMV_Class* kmv_obj, uint32_t *kmv_type);

int  KMV_AES_Decode(uint8_t *buf, int filelen, uint8_t *drmkey, uint8_t *aescache);
void KMV_AES_IniCachetab(uint8_t *aescache);
void KMV_AES_SPS_PPS(uint8_t *buf, int filelen, uint8_t *drmkey);
int  KMV_IsDRM(uint32_t kmv_type);
void KMV_InitSEIfmt(uint32_t *kmv_type);
void KMV_InitHQfmt(uint16_t HQfmt, uint32_t* kmv_type);
void KMV_Init3Dfmt(uint8_t HQfmt, uint32_t* kmv_type);
void KMV_Scramble(uint8_t *CheckID, uint8_t pivot);

typedef struct kmv_func_s
{
    void      (* KMV_DecryptFrame)(uint8_t *buf, int len, uint8_t *key, uint32_t kmv_type);
    int       (* kmv_recon_frame2)(KMV_frame_buffer_ext *frame_buf, KMV_Class* kmv_obj, uint32_t kmv_type, uint32_t *need_rec_buffer);
    int       (* KMV_IsSpeedMode)(uint32_t kmv_type);
    uint8_t*  (* KMV_RequestMap)(void);
    uint8_t*  (* KMV_GetValMap)(void);
    int       (* KMV_DecodeOneMap)(uint8_t *pBitsBuf, uint8_t *pMapBuf, int nFrameSizeInMbs);
#ifdef SUPPORT_KMV_DRM
    int       (* KMV_AES_Decode)(uint8_t *buf, int filelen, uint8_t *drmkey, uint8_t *aescache);
    void      (* KMV_AES_IniCachetab)(uint8_t *aescache);
    void      (* KMV_AES_SPS_PPS)(uint8_t *buf, int filelen, uint8_t *drmkey);
    int       (* KMV_IsDRM)(uint32_t kmv_type);
#endif // SUPPORT_KMV_DRM
    int       (* KMV_IsAnaglyph)(uint32_t kmv_type);
    int       (* KMV_IsDualView)(uint32_t kmv_type);
    int       (* KMV_IsMonoDepth)(uint32_t kmv_type);
    int       (* KMV_IsM4vfmt)(uint32_t kmv_type);
    int       (* KMV_IsSEIfmt)(uint32_t kmv_type);
    void      (* KMV_Resetfmt)(uint32_t *kmv_type);
    int       (* KMV_InterpretSEIMessage)(uint8_t *buf, int size);
    int       (* MP4DMX_GetKMV_Name)(void *pInst, unsigned char * name, int max_length);
    void      (* MP4DMX_GetKMV_Year)(void *pInst, unsigned short * year);
    int       (* MP4DMX_GetKMV_Starring)(void *pInst, unsigned char * starring, int max_length);
    void      (* MP4DMX_GetKMV_Cover)(void *pInst, unsigned char *coverBuffer, unsigned int *coverLength, int max_length);
    int       (* MP4DMX_GetKMV_Synopsis)(void *pInst, unsigned char * synopsis, int max_length);
    void      (* MP4DMX_GetKMV_Category)(void *pInst, unsigned int * category);
    void      (* MP4DMX_GetKMV_Duration)(void *pInst, unsigned short *duration);
    void      (* MP4DMX_InitKMVCache)(void *pInst, unsigned char *cache, uint8_t *aescache);
    int       (* MP4DMX_InitKMVMeta)(void *pInst, const uint8_t *passwd);
    int       (* MP4DMX_ReadKMVMeta)(void *pInst, uint32_t frameidx, uint8_t *tType, uint16_t *recH, uint16_t *recW, uint8_t *pBuf, uint16_t *nsize);
} kmv_func_st;

void Enable_kmv_func_plugin(int page_page_mode);
kmv_func_st *Get_kmv_func(void);

#endif /* KMV_API_H */
