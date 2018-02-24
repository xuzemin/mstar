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


#ifndef MVC_INFO_H
#define MVC_INFO_H

#include <stdint.h>

#define MVC_MAX_SERVICE_NAME_LEN        (50)
#define MVC_MAX_EVENT_NAME_LEN          (30)

typedef enum mvc_ts_type_e
{
    MVC_TS_PTS,
    MVC_TS_DTS,
} mvc_ts_type_et;

typedef enum mvc_3D_type_e
{
    MVC_3D_NONE,
    MVC_3D_LR,
    MVC_3D_LINE_INTERLEAVE,
} mvc_3D_type_et;

typedef struct mvc_data_info_s
{
    int length;
    unsigned char *payload;
} mvc_data_info_st;

typedef struct mvc_clip_info_s
{
    int seekable;
    int num_program;
    int active_program;
    mvc_ts_type_et ts_type;
} mvc_clip_info_st;

typedef struct mvc_program_info_s
{
    int64_t duration;
    int num_video_streams;
    int num_audio_streams;
    int num_subtitle_streams;
    int num_editions;
    int active_video;
    int active_audio;
    int active_subtitle;
    int active_edition;
    int dynamic_subtitle;
    int divx_plus;
    int divx_drm;
    int divx_trick_track; // trick track exist flag
    mvc_data_info_st title;
    mvc_data_info_st artist;
    mvc_data_info_st private_data;
} mvc_program_info_st;

typedef struct mvc_edition_info_s
{
    int64_t duration;
    int num_chapters;
    int active_chapter;
    mvc_data_info_st title;
    mvc_data_info_st artist;
} mvc_edition_info_st;

typedef struct mvc_chapter_info_s
{
    int64_t start_time;
    int64_t end_time;
    mvc_data_info_st title;
    mvc_data_info_st artist;
} mvc_chapter_info_st;

typedef struct mvc_audio_info_s
{
    int codec;
    int sample_rate;
    int bit_rate;
    int channel_num;
    mvc_data_info_st desc; // description for this track
    char language[4]; // ISO 639-2, use alpha-3 code
} mvc_audio_info_st;

typedef struct mvc_video_info_s
{
    int codec;
    int width;
    int height;
    int frame_rate_num;
    int frame_rate_den;
    int bit_rate;
    int mvc_type;
    mvc_data_info_st desc; // description for this track
} mvc_video_info_st;

typedef struct mvc_subtitle_info_s
{
    int codec;
    mvc_data_info_st config;
    mvc_data_info_st desc; // description for this track
    char language[4]; // ISO 639-2, use alpha-3 code
} mvc_subtitle_info_st;

typedef struct mvc_service_info_s
{
    int service_id;
    int virtual_channel_num_high;
    int virtual_channel_num_low;
    int service_name_len;
    char service_name[MVC_MAX_SERVICE_NAME_LEN];
} mvc_service_info;

typedef struct mvc_EIT_info_s
{
    int     event_id;
    int     running_status;
    int64_t start_time;
    int     duration;
    int     event_name_len;
    char    event_name[MVC_MAX_EVENT_NAME_LEN];
} mvc_EIT_info;

typedef struct mvc_EPG_info_s
{
    int service_num;
    mvc_service_info *service_info;
    int event_num;
    mvc_EIT_info *EIT_info;
} mvc_EPG_info;

#endif /* MVC_INFO_H */
