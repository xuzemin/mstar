////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2013 MStar Semiconductor, Inc.
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


#ifndef MVC_DEMUXER_H
#define MVC_DEMUXER_H

/**
 * @file
 */

#include <stddef.h>
#include <stdint.h>
#include "ms_input.h"
#include "mvc_info.h"

#if !defined(__ANDROID__)
  //#define DLL_PUBLIC //mark for build error
  //#define DLL_LOCAL  //mark for build error
#else
#if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
    #define DLL_PUBLIC
    #define DLL_LOCAL
#endif
#endif

/**
 * @brief Demuxer interface
 *
 * This is the demuxer interface for MStar player.
 *
 * Client application needs to supply input and callback class objects to
 * demuxer. The type of the input object is cb_io_st, which is documented in
 * ms_input.h. It is used as an abstract class for file, memory, or other types
 * of input stream. The type of the callback object is mvc_callback_st, it is
 * used to allocate heap buffer for demuxer parsing, allocating buffer for
 * video and audio samples, and signal stream conditions like end-of-stream.
 *
 * There are two types of demuxer parsing modes, demuxers mostly work in a
 * typical operation mode. For streams with special condition, for example, bad
 * interleave, demuxer can optionally support an "avframe" mode. Both of the
 * interfaces should be supported by client application to use the demuxer
 * library correctly.
 *
 * Demuxer classes for different file formats are exported by function tables
 * of type mvc_dmx_func_st. We currently do not provide factory methods due to
 * code size garbage collection concern. The basic use of demuxer interface
 * looks like: open_file -> set_alloc -> [get_frame_info] -> get_data -> [until
 * all streams ends] -> close_file. the get_frame_info call is only necessary
 * for demuxers supporting avframe interface.
 *
 * Demuxer commits audio/video samples along with timestamp and duration
 * information. The timestamps are either DTS (Decoding Time Stamp) or PTS
 * (Presentation Time Stamp), depending on the information reported by demuxer.
 * All timestamps are measured in us (10^-6) unit. A timestamp of value -1
 * indicates an invalid PTS, which means demuxer cannot determine the correct
 * value. The client application (generally the decoder) should infer the
 * PTS using frame rate or other information. While DTS should always be
 * positive values, PTS can sometimes be negative. Therefore the application
 * should only take -1 as invalid PTS but not other negative values. Duration
 * information cannot be easily obtain in many cases, and it is only reliable
 * for some sepcific scenarios. Duration is also measured in us time unit.
 *
 * A demuxer takes an abstract input class cb_io_st as input. Inside demuxer
 * implementation, it is advised to use buffered class cb_buffer_st for read
 * buffer management. [EDIT]
 * @{
 */

/**
 * The return codes for demuxer functions and callbacks
 */
typedef enum mvc_errno_e
{
    MVC_OK,                 ///< Operation succeeded
    MVC_NoInputSignal,      ///< Signal lost
    MVC_TryAgain,           ///< Failed to parse any sample within reasonable range
    MVC_InvalidParam,       ///< Invalid input parameter
    MVC_NotEnoughMemory,    ///< Memory allocation failed
    MVC_OpenFailed,         ///< File corrupted or not supported
    MVC_SeekFailed,         ///< Seeking operation failed
    MVC_ProgramChanged,     ///< Dynamic program change for live broadcasting
    MVC_EndOfStream,        ///< End of stream reached
    MVC_AVFrameEmpty,       ///< AVFrame queue is empty
    MVC_AllocatorDisabled   ///< Allocator has been disabled
} mvc_errno_et;

/**
 * Enumerations to notify demuxer to drop frames to speed up parsing.
 * Demuxer does not need to follow the ratio strictly or provide all
 * drop modes. However demuxer should provide fallback if it supports
 * some of the modes. For example, a demuxer supporting MVC_DROP_2_3
 * should fallback to this mode when asked to do MVC_DROP_3_4.
 */
typedef enum mvc_drop_level_e
{
    MVC_DROP_NONE,          ///< Full parsing
    MVC_DROP_1_3,           ///< Drop alternative B frames (for IBBPBBP...)
    MVC_DROP_1_2,           ///< Drop all B frames (for IBPBPBP...)
    MVC_DROP_2_3,           ///< Drop all B frames (for IBBPBBP...)
    MVC_DROP_3_4,           ///< Drop all B frames (for IbBbPbBbP...)
    MVC_DROP_FULL,          ///< Drop all non-key frames (intra only)
} mvc_drop_level_et;

/**
 * Enumerations specifying input stream format
 */
typedef enum MVCDemuxType_e
{
    CLIP_DEMUX_TYPE_UNKNOWN,    ///< For demuxer internal, do not use
    CLIP_DEMUX_TYPE_AAC,        ///< Raw AAC audio
    CLIP_DEMUX_TYPE_AMRNB,      ///< Raw AMR-NB audio
    CLIP_DEMUX_TYPE_AMRWB,      ///< Raw AMR-NB audio
    CLIP_DEMUX_TYPE_MPGES,      ///< MPEG-2 Elemental Stream
    CLIP_DEMUX_TYPE_ASF,        ///< Microsoft Advanced Systems Format
    CLIP_DEMUX_TYPE_AVI,        ///< Audio Video Interleave
    CLIP_DEMUX_TYPE_CMMB,       ///< China Multimedia Mobile Broadcasting
    CLIP_DEMUX_TYPE_FLV,        ///< Flash Video
    CLIP_DEMUX_TYPE_M2PS,       ///< MPEG-2 Program Stream
    CLIP_DEMUX_TYPE_M2TS,       ///< MPEG-2 Transport Stream
    CLIP_DEMUX_TYPE_MIDI,       ///< Musical Instrument Digital Interface
    CLIP_DEMUX_TYPE_MKV,        ///< Matroska
    CLIP_DEMUX_TYPE_MP3,        ///< Raw MP3 audio
    CLIP_DEMUX_TYPE_RMFF,       ///< RealMedia
    CLIP_DEMUX_TYPE_RTP,        ///< RTP payload with proprietary header
    CLIP_DEMUX_TYPE_TINY,       ///< Proprietary
    CLIP_DEMUX_TYPE_WAV,        ///< Waveform Audio File Format
    CLIP_DEMUX_TYPE_AC3,        ///< Raw AC-3 audio
    CLIP_DEMUX_TYPE_PMP,        ///< Playstation Portable Format
    CLIP_DEMUX_TYPE_SWF,        ///< Shock Wave Flash
} MVCDemuxType_et;

/**
 * Enumerations specifying video codec format
 */
typedef enum MVCVideoType_e
{
    CLIP_VIDEO_TYPE_ERROR = -1, ///< For demuxer internal, do not use
    CLIP_VIDEO_TYPE_UNKNOWN,    ///< For demuxer internal, do not use
    CLIP_VIDEO_TYPE_MP2V,       ///< MPEG-2 Video
    CLIP_VIDEO_TYPE_DIV3,       ///< DivX 3
    CLIP_VIDEO_TYPE_DIVX,       ///< DivX 4 or later
    CLIP_VIDEO_TYPE_DX50,       ///< DivX 5
    CLIP_VIDEO_TYPE_H263,       ///< H.263
    CLIP_VIDEO_TYPE_IV32,       ///< Indeo Video V3
    CLIP_VIDEO_TYPE_IV41,       ///< Indeo Video V4
    CLIP_VIDEO_TYPE_M263,       ///< MStar H.263 variant
    CLIP_VIDEO_TYPE_M4V,        ///< MPEG-4 Video
    CLIP_VIDEO_TYPE_MP4S,       ///< Microsoft MPEG-4
    CLIP_VIDEO_TYPE_M4S2,       ///< Microsoft MPEG-4
    CLIP_VIDEO_TYPE_MP41,       ///< Microsoft MPEG-4
    CLIP_VIDEO_TYPE_MP42,       ///< Microsoft MPEG-4
    CLIP_VIDEO_TYPE_MP43,       ///< Microsoft MPEG-4
    CLIP_VIDEO_TYPE_WMV1,       ///< Microsoft Windows Media Video 7
    CLIP_VIDEO_TYPE_WMV2,       ///< Microsoft Windows Media Video 8
    CLIP_VIDEO_TYPE_WMV3,       ///< Microsoft Windows Media Video 9
    CLIP_VIDEO_TYPE_WMVA,       ///< Microsoft Windows Media Video 9 Advanced Profile
    CLIP_VIDEO_TYPE_WVC1,       ///< Microsoft Windows Media Video 9 Advanced Profile
    CLIP_VIDEO_TYPE_AVC1,       ///< H.264
    CLIP_VIDEO_TYPE_MVC,        ///< H.264 MVC
    CLIP_VIDEO_TYPE_HEVC,       ///< H.265
    CLIP_VIDEO_TYPE_RVCH,       ///< RealVideo
    CLIP_VIDEO_TYPE_FLV1,       ///< Sorenson H.263
    CLIP_VIDEO_TYPE_RV10,       ///< RealVideo
    CLIP_VIDEO_TYPE_RV20,       ///< RealVideo
    CLIP_VIDEO_TYPE_RV30,       ///< RealVideo
    CLIP_VIDEO_TYPE_RV40,       ///< RealVideo
    CLIP_VIDEO_TYPE_SVQ3,       ///< Sorenson Video V3
    CLIP_VIDEO_TYPE_AVS1,       ///< Chinese Audio Video Standard
    CLIP_VIDEO_TYPE_MJPG,       ///< Motion JPEG
    CLIP_VIDEO_TYPE_MSVC,       ///< Microsoft Video 1
    CLIP_VIDEO_TYPE_VP60,       ///< On2 VP6
    CLIP_VIDEO_TYPE_VP70,       ///< On2 VP7
    CLIP_VIDEO_TYPE_VP80,       ///< On2 VP8
    CLIP_VIDEO_TYPE_DVSD,       ///< DV Video
    CLIP_VIDEO_TYPE_I420,       ///< Raw video in I420 format
} MVCVideoType;

/**
 * Enumerations specifying audio codec format
 */
typedef enum MVCAudioType_e
{
    CLIP_AUDIO_TYPE_ERROR = -1, ///< For demuxer internal, do not use
    CLIP_AUDIO_TYPE_UNKNOWN,    ///< For demuxer internal, do not use
    CLIP_AUDIO_TYPE_AAC,        ///< Advanced Audio Coding
    CLIP_AUDIO_TYPE_AC3,        ///< Dolby AC-3
    CLIP_AUDIO_TYPE_EAC3,       ///< Dolby Digital Plus
    CLIP_AUDIO_TYPE_AMRNB,      ///< AMR Narrow Band
    CLIP_AUDIO_TYPE_AMRNBIF2,   ///< AMR Narrow Band
    CLIP_AUDIO_TYPE_AMRWB,      ///< AMR Wide Band
    CLIP_AUDIO_TYPE_ATRC,       ///< Sony Adaptive Transform Acoustic Coding
    CLIP_AUDIO_TYPE_COOK,       ///< RealAudio
    CLIP_AUDIO_TYPE_DRA,        ///< Chinese Dynamic Resolution Adaptation
    CLIP_AUDIO_TYPE_DTS,        ///< DTS
    CLIP_AUDIO_TYPE_FLAC,       ///< FLAC
    CLIP_AUDIO_TYPE_MIDI,       ///< MIDI
    CLIP_AUDIO_TYPE_MP3,        ///< MPEG-1 Audio Layer III
    CLIP_AUDIO_TYPE_ADPCM,      ///< ADPCM
    CLIP_AUDIO_TYPE_LPCM,       ///< LPCM
    CLIP_AUDIO_TYPE_PCM,        ///< PCM: general PCM - ADPCM - LPCM
    CLIP_AUDIO_TYPE_SIPR,       ///< RealAudio
    CLIP_AUDIO_TYPE_WMA1,       ///< Windows Media Audio
    CLIP_AUDIO_TYPE_WMA2,       ///< Windows Media Audio
    CLIP_AUDIO_TYPE_WMA3,       ///< Windows Media Audio
    CLIP_AUDIO_TYPE_VORBIS,     ///< Vorbis
    CLIP_AUDIO_TYPE_TRUEHD,     ///< TrueHD
} MVCAudioType;

/**
 * Enumerations specifying subtitle codec format
 */
typedef enum MVCSubtitleType_e
{
    CLIP_SUBTITLE_TYPE_ERROR = -1,  ///< For demuxer internal, do not use
    CLIP_SUBTITLE_TYPE_UNKNOWN,     ///< For demuxer internal, do not use
    CLIP_SUBTITLE_TYPE_DXSB,        ///< DivX XSUB
    CLIP_SUBTITLE_TYPE_DXSA,        ///< DivX XSUB with alpha
    CLIP_SUBTITLE_TYPE_VBSB,        ///< VOBsub
    CLIP_SUBTITLE_TYPE_DVDS,        ///< DVD subtitle (VOBsub without idx file)
    CLIP_SUBTITLE_TYPE_ASS,         ///< ASS subtitle
    CLIP_SUBTITLE_TYPE_SSA,         ///< SSA subtitle
    CLIP_SUBTITLE_TYPE_DVB,         ///< DVB subtitle
    CLIP_SUBTITLE_TYPE_PGS,         ///< PGS subtitle
    CLIP_SUBTITLE_TYPE_SRT,         ///< internal SRT subtitle
    CLIP_SUBTITLE_TYPE_TTF,         ///< TTF subtitle (text with true type font)
    CLIP_SUBTITLE_TYPE_TX3G,        ///< MPEG-4 Timed Text
} MVCSubtitleType;

/**
 * Enumerations specifying stream format
 */
typedef enum mvc_stream_type_e
{
    MVC_STREAM_NONE,
    MVC_STREAM_PROG,
    MVC_STREAM_AUDIO,
    MVC_STREAM_VIDEO,
    MVC_STREAM_SUBTITLE,
    MVC_STREAM_ESG,
    MVC_STREAM_EMG,
    MVC_STREAM_CA,
    MVC_STREAM_PROG2, // hack
    MVC_STREAM_BROADCAST,
    MVC_STREAM_EDITION,
    MVC_STREAM_CHAPTER,
} mvc_stream_type_et;

typedef enum mvc_paket_type_e
{
    MVC_PACKET_PAYLOAD = 0, /// < payload
    MVC_PACKET_CONFIG,      /// < config packet
    MVC_PACKET_DISC,        /// < inform discontinuity
} mvc_paket_type_et;

typedef enum mvc_input_type_e
{
    MVC_INPUT_MASTER = 0,
    MVC_INPUT_TRICK_FORWARD,
    MVC_INPUT_TRICK_BACKWARD,
} mvc_input_type_et;

/**
 * Enumerations specifying notifications
 */
typedef enum mvc_event_e
{
    MVC_EVENT_EOS,  ///< End of stream
} mvc_event_et;

/**
 * Enumerations specifying the direction of seek operation
 * [EDIT] more description
 */
typedef enum mvc_seek_direction_e
{
    MVC_SEEK_FORWARD,
    MVC_SEEK_BACKWARD,
} mvc_seek_direction_et;

/**
 * Callback functions
 * Client supplied callback functions for demuxer to do memory allocation,
 * event notification, and data delivery. Demuxer will call these functions
 * with \p context as the first argument.
 */
typedef struct mvc_callback_s
{
    /**
     * Notify events happened during demuxer operations.
     * @param[in] ctx Callback context
     * @param[in] type Stream type for which the event applies to
     * @param[in] event The event which demuxer wants to notify
     * @return MVC_OK
     */
    int     (* notify)(void *ctx, mvc_stream_type_et type, mvc_event_et event);

    /**
     * Allocates specified memory with proper alignment (at least 8).
     * @param[in] ctx Callback context
     * @param[in] size The size of the memory to allocate
     * @return allocated memory pointer or 0 if allocation failed.
     */
    void *  (* malloc)(void *ctx, size_t size);

    /**
     * Frees any pointer returned by malloc callback function. NULL pointer is
     * allowed as the pointer to be freed.
     * @param[in] ctx Callback context
     * @param[in,out] ptr Address to the pointer to be freed. Upon output the
     *                      pointer in \p ptr should be set to 0.
     */
    void    (* freep)(void *ctx, void *ptr);

    /**
     * Get current system time, it is not necessary to set any time base.
     * Demuxer will only rely on relative values.
     * @param[in] ctx Callback context
     * @return current System time in us time unit
     */
    int64_t (* get_time)(void *ctx);

    /**
     * Allocates a buffer to write parsed payload data to. Demuxer should not
     * call this function during open and seek operations. After a successful
     * commit operation, sometimes there will be data remained in previous
     * allocated buffer. In order to reduce memory operations, demuxer will
     * allocate immediately with size equal to the remaining data size. Callback
     * function shall handle this case and keep the data available in the new
     * allocated buffer.
     * @param[in] ctx Callback context
     * @param[in] type Stream type of the payload data
     * @param[in,out] buffer Pointer to receive allocated buffer. If allocation
     *                       failed, the pointer in \p buffer must be set to 0.
     * @param[in] size Size of the buffer to allocate
     * @retval MVC_OK if allocation succeeded
     * @retval MVC_NotEnoughMemory if \p size is too large or stream is disabled.
     * @retval MVC_InvalidParam if function is called during wrong state.
     */
    int     (* stream_alloc)(void *ctx, mvc_stream_type_et type, void **buffer, int size);

    /**
     * Discard previous allocated buffer.
     * @param[in] ctx Callback context
     * @param[in] type Stream type of the payload data
     * @return MVC_OK
     */
    int     (* stream_discard)(void *ctx, mvc_stream_type_et type);

    /**
     * Commit parsed data. The size shall not exceed the last allocated size.
     * @param[in] ctx Callback context
     * @param[in] type Stream type of the payload data
     * @param[in] size Data size to commit
     * @param[in] pts The timestamp of the first decoded sample in this buffer
     * @param[in] duration The duration of the first decoded sample in this buffer
     * @param[in] packet_type Indicate the type of this buffer, defined in mvc_paket_type_et
     * @return MVC_OK
     */
    int     (* stream_commit)(void *ctx, mvc_stream_type_et type, int size, int64_t pts, int64_t duration, int packet_type);

    /**
     * Reallocate buffer with a different size. Upon successful reallocation,
     * the content of the buffer up to the smaller one of the old and new
     * buffer sizes shall be kept the same.
     * @param[in] ctx Callback context
     * @param[in] type Stream type of the payload data
     * @param[in,out] buffer Pointer to receive allocated buffer. If allocation
     *                       failed, the pointer in \p buffer must be set to 0.
     * @param[in] size Size of the buffer to allocate
     * @retval MVC_OK if allocation succeeded
     * @retval MVC_NotEnoughMemory if \p size is too large or stream is disabled.
     * @retval MVC_InvalidParam if function is called during wrong state.
     */
    int     (* stream_realloc)(void *ctx, mvc_stream_type_et type, void **buffer, int size);

    /**
     * Callback context. Demuxer will call callback functions with \p context
     * as the first argument.
     */
    void *context;
} mvc_callback_st;

/**
 * Demuxer class definition
 */
typedef struct mvc_dmx_func_s
{
    /* static member */
    int (* probe)(const uint8_t *header, int len, cb_io_st *cbio, int noio); // if noio, don't use cbio

    /* normal interface */
    int (* open_file  )(void **ctx, cb_io_st *cbio, void *buffer, int bufsize, int ringbuf_size, const mvc_callback_st *cb);
    int (* close_file )(void *ctx);
    int (* get_info   )(void *ctx, mvc_stream_type_et type, int index, void *info);
    int (* get_data   )(void *ctx, mvc_stream_type_et *type, int *bufsize, int64_t *pts);
    int (* seek_time  )(void *ctx, int dir, int64_t *pts, int query_only);
    int (* resync_time)(void *ctx, int64_t resync_time);
    int (* set_track  )(void *ctx, mvc_stream_type_et type, int index, int64_t pts, mvc_input_type_et input_type);
    int (* set_drop   )(void *ctx, mvc_drop_level_et level);

    /* avframe interface */
    int  (* get_frame_info )(void *ctx, mvc_stream_type_et *type, int *bufsize, int64_t *pts, int *is_intra);
    int  (* get_frame_data )(void *ctx, mvc_stream_type_et *type, int *bufsize, int64_t *pts);
    void (* reset_avframe  )(void *ctx, mvc_stream_type_et type);
    void (* discard_avframe)(void *ctx, mvc_stream_type_et type);
    int  (* queue_avframe  )(void *ctx, int size, mvc_stream_type_et type, int64_t target_PTS);
    int  (* deliver_avframe)(void *ctx, int *len, int64_t *pts, mvc_stream_type_et type);
    int  (* peek_avframe   )(void *ctx, int *frame_size, int64_t *pts, mvc_stream_type_et type);

    /* capability */
    int min_context_size;
    int support_avframe_video;
    int support_avframe_audio;
} mvc_dmx_func_st;

/**
 * WIP
 */
const mvc_dmx_func_st *mvc_demuxer_create(MVCDemuxType_et type);

extern const mvc_dmx_func_st mvc_aaca_demuxer;
extern const mvc_dmx_func_st mvc_amrn_demuxer;
extern const mvc_dmx_func_st mvc_amrw_demuxer;
extern const mvc_dmx_func_st mvc_asff_demuxer;
extern const mvc_dmx_func_st mvc_avif_demuxer;
extern const mvc_dmx_func_st mvc_cmmb_demuxer;
extern const mvc_dmx_func_st mvc_flvf_demuxer;
extern const mvc_dmx_func_st mvc_m2ps_demuxer;
extern const mvc_dmx_func_st mvc_m2ts_demuxer;
extern const mvc_dmx_func_st mvc_pmpf_demuxer;
extern const mvc_dmx_func_st mvc_swff_demuxer;
extern const mvc_dmx_func_st mvc_mpges_demuxer;
extern const mvc_dmx_func_st mvc_midi_demuxer;
extern const mvc_dmx_func_st mvc_mkvf_demuxer;
extern const mvc_dmx_func_st mvc_mp3a_demuxer;
extern const mvc_dmx_func_st mvc_rmvb_demuxer;
extern const mvc_dmx_func_st mvc_rtpp_demuxer;
extern const mvc_dmx_func_st mvc_tiny_demuxer;
extern const mvc_dmx_func_st mvc_wavf_demuxer;
extern const mvc_dmx_func_st mvc_ac3a_demuxer;

extern const mvc_dmx_func_st mvc_plugin_demuxer;

#endif /* MVC_DEMUXER_H */
