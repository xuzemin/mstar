
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "drvGlobal.h"


#if (HDMITX_4030_ENABLE)//ENABLE_4030_DEVICE//enabled by Weng 2015.09.16

#if 0//modified by Weng 2015.09.16
#include "drvI2C.h"
#include "MsCommon.h"
#include "Device_hdmitx_4030.h"
//#include "MsTypes.h"
#include "MsOS.h"
#include "msAPI_Timer.h"
#include "mdrv_mfc_utl.h"
#include "drvGPIO.h"
#else
#include "drvIIC.h"
#include "Device_hdmitx_4030.h"
#include <string.h>
#include "msAPI_Timer.h"
////>>>>>>>>>>>>>>>>added by Weng 2015.09.11
#include "chip/MSD91H1BN2.h"
#include "drvGPIO.h"
#endif

#define GET_SYS_TIME() MsOS_GetSystemTime()
#define SET_SYS_DELAY_MS_MS(ms)  msAPI_Timer_Delayms(ms)
#define CHIP_DEPENDENT_IIC_Write(p1, p2, p3, p4, p5) MDrv_IIC_WriteBytes(p1, p2, p3, p4, p5)
#define CHIP_DEPENDENT_IIC_Read(p1, p2, p3, p4, p5)  MDrv_IIC_ReadBytes(p1, p2, p3, p4, p5)
#define device_hdmitx_DBG(x) x


#define DEVICE_I2C_SLAVE_ID       (/*((U16)E_I2C_BUS_DDC2BI<<8)|*/0xA2)//  0xA2//modified by Weng 2015.09.16
#define MBX_REG_BASE           (0x1200)



/// MBX Command Type Index
typedef enum
{
    E_MBX_CONFIQ_VIDEO        = 0x01,
    E_MBX_CONFIQ_AUDIO        = 0x02,
    E_MBX_AVMUTE_TIMING_RESET = 0x03,
    E_MBX_QUERY_EDID_INFO     = 0x04,
    E_MBX_REPORT_EDID_INFO    = 0x05,
    E_MBX_ACK_STATUS_RESPOND  = 0x06,
    E_MBX_DEBUG               = 0xFF,
} EN_MBX_COMMAND_TYPE; // MBX command type

/// MBX Timing Type
typedef enum
{
    E_HDMITX_TIMING_720x576p_50Hz   = 0x00,
    E_HDMITX_TIMING_720x480p_60Hz   = 0x01,
    E_HDMITX_TIMING_1280x720p_50Hz  = 0x02,
    E_HDMITX_TIMING_1280x720p_60Hz  = 0x03,
    E_HDMITX_TIMING_1920x1080p_24Hz = 0x04,
    E_HDMITX_TIMING_1920x1080i_50Hz = 0x05,
    E_HDMITX_TIMING_1920x1080i_60Hz = 0x06,
    E_HDMITX_TIMING_1920x1080p_50Hz = 0x07,
    E_HDMITX_TIMING_1920x1080p_60Hz = 0x08,
    E_HDMITX_TIMING_4K2Kp_25Hz      = 0x09,
    E_HDMITX_TIMING_4K2Kp_30Hz      = 0x0A,
    E_HDMITX_TIMING_4K2Kp_50Hz      = 0x0B,
    E_HDMITX_TIMING_4K2Kp_60Hz      = 0x0C,
    E_HDMITX_TIMING_MAX             = 0x0D,
} EN_HDMITX_VIDEO_TIMING; //  timing type index

/// MBX Color Depth Type
typedef enum
{
    E_HDMITX_COLORS_NOID   = 0,
    E_HDMITX_COLORS_8bits  = 1,
    E_HDMITX_COLORS_10bits = 2,
    E_HDMITX_COLORS_12bits = 3,
} EN_HDMITX_COLOR_DEPTH; //  color type index

/// MBX Video Output Mode
typedef enum
{
    E_HDMITX_VIDEO_OUTPUT_DVI       = 0,
    E_HDMITX_VIDEO_OUTPUT_DVI_HDCP  = 1,
    E_HDMITX_VIDEO_OUTPUT_HDMI      = 2,
    E_HDMITX_VIDEO_OUTPUT_HDMI_HDCP = 3,
} EN_HDMITX_VIDEO_OUTPUT_TYPE; //  video output type index

/// MBX Input Color Type
typedef enum
{
    E_HDMITX_COLORS_INPUT_RGB = 0,
    E_HDMITX_COLORS_INPUT_YUV = 1,
} EN_HDMITX_INPUT_COLOR_TYPE; //  input color type index

/// MBX Output Color Type
typedef enum
{
    E_HDMITX_COLORS_OUTPUT_RGB_444 = 0,
    E_HDMITX_COLORS_OUTPUT_YUV_422 = 1,
    E_HDMITX_COLORS_OUTPUT_YUV_444 = 2,
    E_HDMITX_COLORS_OUTPUT_YUV_420 = 3,
} EN_HDMITX_OUTPUT_COLOR_TYPE; //  output color type index

/// MBX 3D VS Information Type
typedef enum
{
    E_HDMITX_VIDEO_3D_FramePacking     = 0,
    E_HDMITX_VIDEO_3D_FieldAlternative = 1,
    E_HDMITX_VIDEO_3D_LineAlternative  = 2,
    E_HDMITX_VIDEO_3D_SidebySide_FULL  = 3,
    E_HDMITX_VIDEO_3D_L_Dep            = 4,
    E_HDMITX_VIDEO_3D_L_Dep_Graphic_Dep= 5,
    E_HDMITX_VIDEO_3D_TopandBottom     = 6,
    E_HDMITX_VIDEO_3D_SidebySide_Half  = 8,
    E_HDMITX_VIDEO_3D_Not_in_Use       = 15,
} EN_HDMITX_VIDEO_3D_STRUCTURE_TYPE; //  3D VS info type index

/// MBX 4K2K VS Information Type
typedef enum
{
    E_HDMITX_VIDEO_4K2K_Reserved    = 0, // 0x00
    E_HDMITX_VIDEO_4K2K_30Hz        = 1, // 0x01
    E_HDMITX_VIDEO_4K2K_25Hz        = 2, // 0x02
    E_HDMITX_VIDEO_4K2K_24Hz        = 3, // 0x03
    E_HDMITX_VIDEO_4K2K_24Hz_SMPTE  = 4, // 0x04
} EN_HDMITX_VIDEO_4K2K_VIC;//  4K2K VS info type index


/// MBX Audio Frequency Type
typedef enum
{
    E_HDMITX_AUDIO_32KHz   = 0, // 0x00
    E_HDMITX_AUDIO_44KHz   = 1, // 0x01
    E_HDMITX_AUDIO_48KHz   = 2, // 0x02
    E_HDMITX_AUDIO_88KHz   = 3, // 0x03
    E_HDMITX_AUDIO_96KHz   = 4, // 0x04
    E_HDMITX_AUDIO_176KHz  = 5, // 0x05
    E_HDMITX_AUDIO_192KHz  = 6, // 0x06
} EN_HDMITX_AUDIO_FREQUENCY_TYPE;//  audio frequency index

/// MBX Audio Channel Number
typedef enum
{
    E_HDMITX_AUDIO_CH_2    = 2, // 2 channels
    E_HDMITX_AUDIO_CH_8    = 8, // 8 channels
} EN_HDMITX_AUDIO_CHANNEL_COUNT;//  audio channel number index

/// MBX Audio Code Type
typedef enum
{
    E_HDMITX_AUDIO_PCM     = 0, // PCM
    E_HDMITX_AUDIO_NONPCM  = 1, // non-PCM
} EN_HDMITX_AUDIO_CODING_TYPE;//  audio code type index

/// MBX Audio Channel Number
typedef enum
{
    E_HDMITX_AUDIO_SPDIF   = 0, // SPDIF
    E_HDMITX_AUDIO_I2S     = 1, // I2S
} EN_HDMITX_AUDIO_SOURCE_TYPE;//  audio source type index

/// MBX Audio Channel Number
typedef enum
{
    E_HDMITX_AUDIO_FORMAT_PCM   = 0, // PCM
    E_HDMITX_AUDIO_FORMAT_DSD   = 1, // DSD
    E_HDMITX_AUDIO_FORMAT_HBR   = 2, // HBR
} EN_HDMITX_AUDIO_SOURCE_FORMAT;//  audio source format index

/// MBX Video Mute
typedef enum
{
    E_HDMITX_VIDEO_MUTE_DISABLE   = 0, // disable
    E_HDMITX_VIDEO_MUTE_ENABLE    = 1, // enable
} EN_HDMITX_VIDEO_MUTE;//  video mute index

/// MBX Audio Mute
typedef enum
{
    E_HDMITX_AUDIO_MUTE_DISABLE   = 0, // disable
    E_HDMITX_AUDIO_MUTE_ENABLE    = 1, // enable
} EN_HDMITX_AUDIO_MUTE;//  audio mute index

/// MBX Audio Mute
typedef enum
{
    E_HDMITX_AVMUTE_DISABLE   = 0, // disable
    E_HDMITX_AVMUTE_ENABLE    = 1, // enable
} EN_HDMITX_AVMUTE;//  audio and video mute index

/// MBX Timing Change
typedef enum
{
    E_HDMITX_TIMING_CHANGE_DISABLE   = 0, // disable
    E_HDMITX_TIMING_CHANGE_ENABLE    = 1, // enable
} EN_HDMITX_TIMING_CHANGE;//  timing reset index

/// MBX Query Type
typedef enum
{
    E_QUERY_4K2K_VIC             = 1, // 0x01
    E_QUERY_3D_STRUCTURE         = 2, // 0x02
    E_QUERY_AUDIO_DESCRIPTOR_NUM = 3, // 0x03
    E_QUERY_AUDIO_DESCRIPTOR     = 4, // 0x04
    E_QUERY_VIDEO_DESCRIPTOR_NUM = 5, // 0x05
    E_QUERY_VIDEO_DESCRIPTOR     = 6, // 0x06
    E_QUERY_EDID_DATA            = 7, // 0x07
} EN_QUERY_TYPE;//  command 0x04 0x05 query type index


/// MBX 3D Timing Type for Command 0x04 Query
typedef enum
{
    E_HDMITX_QUERY_3DTIMING_1280x720p_50Hz  = 0x00,
    E_HDMITX_QUERY_3DTIMING_1280x720p_60Hz  = 0x01,
    E_HDMITX_QUERY_3DTIMING_1920x1080i_50Hz = 0x02,
    E_HDMITX_QUERY_3DTIMING_1920x1080i_60Hz = 0x03,
    E_HDMITX_QUERY_3DTIMING_1920x1080p_24Hz = 0x04,
    E_HDMITX_QUERY_3DTIMING_1920x1080p_25Hz = 0x05,
    E_HDMITX_QUERY_3DTIMING_1920x1080p_50Hz = 0x06,
    E_HDMITX_QUERY_3DTIMING_1920x1080p_60Hz = 0x07,
    E_HDMITX_QUERY_3DTIMING_4K2Kp_25Hz      = 0x08,
    E_HDMITX_QUERY_3DTIMING_4K2Kp_30Hz      = 0x09,
    E_HDMITX_QUERY_3DTIMING_4K2Kp_50Hz      = 0x0A,
    E_HDMITX_QUERY_3DTIMING_4K2Kp_60Hz      = 0x0B,
    E_HDMITX_QUERY_3DTIMING_MAX             = 0x0C,
} EN_HDMITX_QUERY_3DTIMING; //  3D timing type index for command 0x04 query & 0x05 report

/// MBX 3D VS Information Type for Command 0x05 Report
typedef enum
{
    E_HDMITX_VIDEO_REPORT_3D_FramePacking               = 0x0001,
    E_HDMITX_VIDEO_REPORT_3D_FieldAlternative           = 0x0002,
    E_HDMITX_VIDEO_REPORT_3D_LineAlternative            = 0x0004,
    E_HDMITX_VIDEO_REPORT_3D_SidebySide_FULL            = 0x0008,
    E_HDMITX_VIDEO_REPORT_3D_L_Dep                      = 0x0010,
    E_HDMITX_VIDEO_REPORT_3D_L_Dep_Graphic_Dep          = 0x0020,
    E_HDMITX_VIDEO_REPORT_3D_TopandBottom               = 0x0040,
    E_HDMITX_VIDEO_REPORT_3D_SidebySide_Half_Horizontal = 0x0080,
    E_HDMITX_VIDEO_REPORT_3D_SidebySide_Half_Quincunx   = 0x8000,
} EN_HDMITX_VIDEO_REPORT_3D_STRUCTURE_TYPE; //  3D VS info type index

/// MBX Status Response
typedef enum
{
    E_MBX_REPORT_CONFIQ_VIDEO        = 0x01,
    E_MBX_REPORT_CONFIQ_AUDIO        = 0x02,
    E_MBX_REPORT_AVMUTE_TIMING_RESET = 0x03,
    E_MBX_REPORT_REPORT_EDID_INFO    = 0x04,
    E_MBX_REPORT_DEBUG               = 0x07,
} EN_MBX_RECIEVED_COMMAND_TYPE; // MBX received command type

typedef enum
{
    E_MBX_REPORT_SUCCESS           = 0x00,
    E_MBX_REPORT_FAIL              = 0x01,
    E_MBX_REPORT_PARAMETER_INVALID = 0x02,
    E_MBX_REPORT_COMMAND_INVALID   = 0x03,
} EN_MBX_STATUS_RESPONSE_TYPE; // MBX received status response type

/// MBX Debug Type
typedef enum
{
    E_MBX_DEBUG_TEST_PATTERN     = 0x00,
    E_MBX_DEBUG_DEBUG_MESSAGE    = 0x01,
    E_MBX_DEBUG_FREE_RUN         = 0x02,
    E_MBX_DEBUG_LOCK_STATUS_LPLL = 0x03,
    E_MBX_DEBUG_STATUS_HTT_VTT   = 0x04,
} EN_MBX_DEBUG_TYPE; // MBX received command type

//Global Variables

EN_HDMITX_VIDEO_OUTPUT_TYPE genHDMITX_Mode = E_HDMITX_VIDEO_OUTPUT_HDMI;
EN_HDMITX_INPUT_COLOR_TYPE  genHDMITx_InColor = E_HDMITX_COLORS_INPUT_RGB;
EN_HDMITX_OUTPUT_COLOR_TYPE genHDMITx_OutColor = E_HDMITX_COLORS_OUTPUT_RGB_444;
EN_HDMITX_COLOR_DEPTH       genHDMITx_ColorDepth = E_HDMITX_COLORS_8bits;

EN_HDMITX_AUDIO_FREQUENCY_TYPE    genAudio_Freq = E_HDMITX_AUDIO_48KHz;
EN_HDMITX_AUDIO_CHANNEL_COUNT     genAudio_Ch_Cnt = E_HDMITX_AUDIO_CH_2;
EN_HDMITX_AUDIO_CODING_TYPE       genAudio_CodeType = E_HDMITX_AUDIO_PCM;
EN_HDMITX_AUDIO_SOURCE_FORMAT     genAudio_SrcFmt = E_HDMITX_AUDIO_FORMAT_PCM;
EN_HDMITX_AUDIO_SOURCE_TYPE       genAudio_SrcType = E_HDMITX_AUDIO_I2S;
EN_HDMITX_VIDEO_TIMING            genHDMITx_VideoTiming = E_HDMITX_TIMING_1920x1080p_60Hz;
EN_HDMITX_VIDEO_3D_STRUCTURE_TYPE genHDMITx_3D = E_HDMITX_VIDEO_3D_Not_in_Use;
EN_HDMITX_VIDEO_4K2K_VIC          genHDMITx_4K2K_VIC = E_HDMITX_VIDEO_4K2K_Reserved;



/// MBX Data Struct For Command 0x01 Configure Video
typedef struct ST_MBX_COMMAND_CONFIQ_VIDEO
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_CONFIQ_VIDEO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// flags for actions
    MS_BOOL timing_present;       /// flag of setting timing
    MS_BOOL color_present;        /// flag of setting color flag
    MS_BOOL VSinfo_3D_present;    /// flag of setting 3D_VS flag
    MS_BOOL analog_present;       /// flag of setting current, pren2, precon, tenpre and ten

    /// data
    EN_HDMITX_VIDEO_TIMING timing_idx;        /// timing type
    EN_HDMITX_COLOR_DEPTH color_depth;               /// color depth, 8bit, 10bit, 12bit
    EN_HDMITX_VIDEO_OUTPUT_TYPE output_mode;         /// video output mode, DVI or HDMI
    EN_HDMITX_INPUT_COLOR_TYPE in_color;             /// input color format, RGB or YUV
    EN_HDMITX_OUTPUT_COLOR_TYPE out_color;           /// output color format, RGB or YUV
    EN_HDMITX_VIDEO_3D_STRUCTURE_TYPE vs_3d;  /// 3d vs information
    MS_U8 current;
    MS_BOOL pren2;
    MS_U8 precon;
    MS_U8 tenpre;
    MS_U8 ten;
}ST_MBX_COMMAND_CONFIQ_VIDEO;// struct of configure video

/// MBX Data Struct For Command 0x02 Configure Audio
typedef struct ST_MBX_COMMAND_CONFIQ_AUDIO
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_CONFIQ_AUDIO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// flags for actions
    MS_BOOL inform_present;   /// flag of timing id, frequency, channel number and code type
    MS_BOOL source_present;   /// flag of timing id, source type
    MS_BOOL fmt_present;      /// flag of timing id, source format

    /// data
    EN_HDMITX_AUDIO_FREQUENCY_TYPE frequency;  /// audio frequency
    EN_HDMITX_AUDIO_CHANNEL_COUNT channel_num; /// audio channel number
    EN_HDMITX_AUDIO_CODING_TYPE code_type;     /// audio coding type
    EN_HDMITX_AUDIO_SOURCE_TYPE source_type;   /// audio source type
    EN_HDMITX_AUDIO_SOURCE_FORMAT source_fmt;  /// audio source format
}ST_MBX_COMMAND_CONFIQ_AUDIO;// struct of configure audio

/// MBX Data Struct For Command 0x03 Video/Audio Mute and Timing Reset
typedef struct ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_AVMUTE_TIMING_RESET

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// flags for actions
    MS_BOOL video_flag;   /// flag of video mute
    MS_BOOL audio_flag;   /// flag of audio mute
    MS_BOOL avmute_flag;  /// flag of audio and video mute
    MS_BOOL timing_flag;  /// flag of changing timing

    /// data
    EN_HDMITX_VIDEO_MUTE enVideo_mute;
    EN_HDMITX_AUDIO_MUTE enAudio_mute;
    EN_HDMITX_AVMUTE enAV_mute;
    EN_HDMITX_TIMING_CHANGE enTiming;
}ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE;// struct of Video/Audio Mute and Timing Reset

/// MBX Data Struct For Command 0x04 Query EDID Information
typedef struct ST_MBX_COMMAND_QUERY_EDID_INFO
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_QUERY_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type;

    /// data
    EN_HDMITX_QUERY_3DTIMING timing_3d;
    MS_U8 des_startIdx;  // audio/video descriptor start index
    MS_U8 des_endIdx;    // audio/video descriptor end index
    MS_U8 bytes64_Idx;   // 64 bytes index
    MS_U8 edid_Idx;      // EDID block index
}ST_MBX_COMMAND_QUERY_EDID_INFO;// struct of query edid info

/// MBX Data Struct For Command 0x05 Report EDID Information (Different Query Type Has Different Struct)
/// Query Type = 4K2K Vic, Query_Type = E_QUERY_4K2K_VIC 0x01
typedef struct ST_MBX_COMMAND_REPORT_EDID_INFO_4K2KVIC
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_REPORT_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type; /// val = E_QUERY_4K2K_VIC

    /// data
    MS_U8 vic_num; /// number of 4k2k_vic
    EN_HDMITX_VIDEO_4K2K_VIC vic4k2k[8]; /// 4k2k_vic
}ST_MBX_COMMAND_REPORT_EDID_INFO_4K2KVIC;// struct of report edid info 4k2k_vic

/// MBX Data Struct For Command 0x05 Report EDID Information (Different Query Type Has Different Struct)
/// Query Type = 3D Structure, Query_Type = E_QUERY_3D_STRUCTURE 0x02
typedef struct ST_MBX_COMMAND_REPORT_EDID_INFO_3DSTRUCT
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_REPORT_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type; /// val = E_QUERY_3D_STRUCTURE

    /// data
    EN_HDMITX_QUERY_3DTIMING repTiming_3d; /// 3D timing
    EN_HDMITX_VIDEO_REPORT_3D_STRUCTURE_TYPE edid_3d; /// 3D edid structure, combination of EN_HDMITX_VIDEO_REPORT_3D_STRUCTURE_TYPE
}ST_MBX_COMMAND_REPORT_EDID_INFO_3DSTRUCT;// struct of report edid info 3D_structure

/// MBX Data Struct For Command 0x05 Report EDID Information (Different Query Type Has Different Struct)
/// Query Type = Number of Audio Descriptor, Query_Type = E_QUERY_AUDIO_DESCRIPTOR_NUM 0x03
typedef struct ST_MBX_COMMAND_REPORT_EDID_INFO_AUDIODES_NUM
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_REPORT_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type; /// val = E_QUERY_AUDIO_DESCRIPTOR_NUM

    /// data
    MS_U8 auddes_num; /// number of audio descriptor
}ST_MBX_COMMAND_REPORT_EDID_INFO_AUDIODES_NUM;// struct of number of audio descriptor

/// MBX Data Struct For Command 0x05 Report EDID Information (Different Query Type Has Different Struct)
/// Query Type = Audio Descriptor, Query_Type = E_QUERY_AUDIO_DESCRIPTOR 0x04
typedef struct ST_MBX_COMMAND_REPORT_EDID_INFO_AUDIODES
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_REPORT_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type; /// val = E_QUERY_AUDIO_DESCRIPTOR

    /// data
    MS_U8 audstr_Idx; /// start index of audio descriptor
    MS_U8 audend_Idx; /// end index of audio descriptor
    MS_U8 aud_des[33];   /// audio descriptors
}ST_MBX_COMMAND_REPORT_EDID_INFO_AUDIODES;// struct of audio descriptor

/// MBX Data Struct For Command 0x05 Report EDID Information (Different Query Type Has Different Struct)
/// Query Type = Number of Video Descriptor, Query_Type = E_QUERY_VIDEO_DESCRIPTOR_NUM 0x05
typedef struct ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES_NUM
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_REPORT_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type; /// val = E_QUERY_VIDEO_DESCRIPTOR_NUM

    /// data
    MS_U8 viddes_num; /// number of audio descriptor
}ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES_NUM;// struct of number of video descriptor

/// MBX Data Struct For Command 0x05 Report EDID Information (Different Query Type Has Different Struct)
/// Query Type = Video Descriptor, Query_Type = E_QUERY_VIDEO_DESCRIPTOR 0x06
typedef struct ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_REPORT_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type; /// val = E_QUERY_VIDEO_DESCRIPTOR

    /// data
    MS_U8 vidstr_Idx; /// start index of video descriptor
    MS_U8 vidend_Idx; /// end index of video descriptor
    MS_U8 vid_des[33];   /// video descriptors
}ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES;// struct of video descriptor

/// MBX Data Struct For Command 0x05 Report EDID Information (Different Query Type Has Different Struct)
/// Query Type = EDID Raw Data, Query_Type = E_QUERY_EDID_DATA 0x07
typedef struct ST_MBX_COMMAND_REPORT_EDID_INFO_EDIDRAWDATA
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_REPORT_EDID_INFO

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// query type
    EN_QUERY_TYPE query_type; /// val = E_QUERY_EDID_DATA

    /// data
    MS_U8 Idx_edid;    /// index of edid
    MS_U8 Idx_64bytes; /// index of 64bytes
    MS_U8 raw_data[68];   /// raw data
}ST_MBX_COMMAND_REPORT_EDID_INFO_EDIDRAWDATA;// struct of edid raw data

/// MBX Data Struct For Command 0x06 Status Response / ACK-Command
typedef struct ST_MBX_COMMAND_ACK_STATUS_RESPONSE
{
    /// command id
    EN_MBX_COMMAND_TYPE command_idx; /// val = E_MBX_ACK_STATUS_RESPOND

    /// length of the following data
    MS_U8 data_len; /// Bytes

    /// received command
    EN_MBX_RECIEVED_COMMAND_TYPE mbx_reccom; /// received command type

    /// status
    EN_MBX_STATUS_RESPONSE_TYPE mbx_status;  /// received status type

}ST_MBX_COMMAND_ACK_STATUS_RESPONSE;// struct of status response or ack-command

/// Video EDID Data Structure
typedef struct
{
    MS_U8 native;  // Native bit
    MS_U8 EDID_DATA; // Video Data bits
}HDMI_EDID_INFO_DATA;//Initialization


static MS_BOOL IIC_WriteBytes(MS_U16 u16SlaveCfg, MS_U32 uAddrCnt, MS_U8 *pRegAddr, MS_U32 uSize, MS_U8 *pData)
{
    // chip dependent IIC write function

    if( CHIP_DEPENDENT_IIC_Write(u16SlaveCfg,(U8) uAddrCnt, pRegAddr, (U8)uSize, pData) == FALSE)
    {
        return FALSE;
    }
    else
        return TRUE;

}

static MS_BOOL IIC_ReadBytes(MS_U16 u16SlaveCfg, MS_U32 uAddrCnt, MS_U8 *pRegAddr, MS_U32 uSize, MS_U8 *pData)
{
    // chip dependent IIC read function

    if(CHIP_DEPENDENT_IIC_Read(u16SlaveCfg, (U8)uAddrCnt, pRegAddr,(U8) uSize, pData) == FALSE)
    {
        return FALSE;
    }
    else
        return TRUE;
}




MS_BOOL Device_Hdmitx_IIC_WriteBytes(MS_U16 u16Addr, MS_U8 u8Buf)
{
    MS_U8 u8Databuf[5] = {0, 0, 0, 0, 0};
    MS_BOOL bResult = TRUE;
    u8Databuf[0] = 0x10;
    u8Databuf[3] = u8Buf;

    u8Databuf[1] = (MS_U8)(u16Addr >> 8);          //the high byte need not move left 1 bit
    u8Databuf[2] = (MS_U8)((u16Addr & 0xFF));        //the low byte moves left 1 bit, reset bit0 means data low byte

    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 4, u8Databuf) == FALSE)
    {
        bResult = IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 4, u8Databuf);
    }
    return bResult;

}

MS_BOOL Device_Hdmitx_IIC_ReadBytes(MS_U16 u16Addr, MS_U8* pBuf)
{

    MS_BOOL bResult = TRUE;
    MS_U8 u8Databuf[6]={0, 0, 0, 0, 0, 0};

    u8Databuf[0] = 0x10;

    u8Databuf[1] = (MS_U8)(u16Addr >> 8);          //the high byte need not move left 1 bit
    u8Databuf[2] = (MS_U8)((u16Addr & 0xFF));        //the low byte moves left 1 bit, reset bit0 means data low byte

    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 3, u8Databuf) == FALSE)
    {
        bResult &= (IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 3, u8Databuf));
    }

    if(IIC_ReadBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, pBuf) == FALSE)
    {
        bResult &= (IIC_ReadBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, pBuf));
    }
    return bResult;

}

void w2byte(MS_U16 u16Addr, MS_U16 u16val)
{
    MS_U8 u8regval;

    u8regval = (MS_U8)(u16val & 0xFF);
    Device_Hdmitx_IIC_WriteBytes(u16Addr, u8regval);

    u8regval = (MS_U8)(u16val >> 8);
    Device_Hdmitx_IIC_WriteBytes(u16Addr+1, u8regval);
}


MS_U16 r2byte(MS_U16 u16Addr)
{
    MS_U8 u8regval;
    MS_U16 u16regval;

    Device_Hdmitx_IIC_ReadBytes(u16Addr, &u8regval);
    u16regval = u8regval;

    Device_Hdmitx_IIC_ReadBytes(u16Addr+1, &u8regval);
    u16regval |= (((MS_U16)u8regval)<<8);

    return u16regval;
}


MS_BOOL MBX_WriteCommand(EN_MBX_COMMAND_TYPE command_idx, MS_U8 data_len, MS_U8 *pBuf)
{
   int i;
    Device_Hdmitx_IIC_WriteBytes(MBX_REG_BASE | 0x00,command_idx);
    Device_Hdmitx_IIC_WriteBytes(MBX_REG_BASE | 0x01,data_len);
    for(i=0;i<data_len;i++)
    {
         Device_Hdmitx_IIC_WriteBytes(MBX_REG_BASE + 0x02 + i,pBuf[i]);
    }
    return TRUE;
}

MS_BOOL MBX_ReadCommand(EN_MBX_COMMAND_TYPE command_idx, MS_U8 data_len, MS_U8 *pBuf)
{
    MS_U8 read_command;
    int i;
    Device_Hdmitx_IIC_ReadBytes(MBX_REG_BASE | 0x00,&read_command);
    switch(read_command)
    {
        case 0x01:
            command_idx=E_MBX_CONFIQ_VIDEO;
            break;
        case 0x02:
            command_idx=E_MBX_CONFIQ_AUDIO;
            break;
        case 0x03:
            command_idx=E_MBX_AVMUTE_TIMING_RESET;
            break;
        case 0x04:
            command_idx=E_MBX_QUERY_EDID_INFO;
            break;
        case 0x05:
            command_idx=E_MBX_REPORT_EDID_INFO;
            break;
        case 0x06:
            command_idx=E_MBX_ACK_STATUS_RESPOND;
            break;
        case 0xFF:
            command_idx=E_MBX_DEBUG;
            break;
        default:
            return FALSE;
    }
    Device_Hdmitx_IIC_ReadBytes(MBX_REG_BASE | 0x01,&data_len);

    for(i=0;i<data_len;i++)
    {
         Device_Hdmitx_IIC_ReadBytes(MBX_REG_BASE + 0x02 + i,&pBuf[i]);
    }
    return TRUE;

}

MS_BOOL MBX_WriteCommand_Config_Video(ST_MBX_COMMAND_CONFIQ_VIDEO *pBuf)
{
    MS_U8 pData[7];
    int dataIdx=1;
    memset(pData, 0, sizeof(MS_U8)*7);

    device_hdmitx_DBG(printf("[Device ] CommandType(%x), DataLen(%x), TimingPre(%x), ColorPre(%x), VS3DPre(%x), AnalogPre(%x), TimingIdx(%x), ColorDepth(%x), OutputMode(%x), InColor(%x), OutColor(%x), VS3D(%x), Current(%x), Pren2(%x), Precon(%x), Tenpre(%x), Ten(%x)\n",
    (int)pBuf->command_idx,(int)pBuf->data_len,
    (int)pBuf->timing_present,(int)pBuf->color_present,(int)pBuf->VSinfo_3D_present,(int)pBuf->analog_present,
    (int)pBuf->timing_idx,(int)pBuf->color_depth,(int)pBuf->output_mode,(int)pBuf->in_color,(int)pBuf->out_color,(int)pBuf->vs_3d,
    (int)pBuf->current,(int)pBuf->pren2,(int)pBuf->precon,(int)pBuf->tenpre,(int)pBuf->ten));

    if (pBuf->command_idx!=E_MBX_CONFIQ_VIDEO)
    {
        return FALSE;
    }
    if (pBuf->data_len>7)
    {
        return FALSE;
    }

    pData[0]=(pBuf->analog_present<<4)|(pBuf->VSinfo_3D_present<<2)|(pBuf->color_present<<1)|pBuf->timing_present;

    if(pBuf->timing_present && (pBuf->data_len>dataIdx))
    {
        pData[dataIdx]=pBuf->timing_idx;
        dataIdx++;
        pData[dataIdx]=(pBuf->output_mode<<3) | pBuf->color_depth;
        if(!pBuf->color_present)
            dataIdx++;
    }
    if(pBuf->color_present && (pBuf->data_len>dataIdx))
    {
        if(pBuf->timing_present)
            pData[dataIdx]=(pBuf->out_color<<6) | (pBuf->in_color<<5) | pData[dataIdx];
        else
            pData[dataIdx]=(pBuf->out_color<<6) | (pBuf->in_color<<5);
        dataIdx++;
    }
    if(pBuf->VSinfo_3D_present && (pBuf->data_len>dataIdx))
    {
        pData[dataIdx]=pBuf->vs_3d;
        dataIdx++;
    }
    if(pBuf->analog_present && (pBuf->data_len>dataIdx))
    {
        pData[dataIdx]=(pBuf->pren2<<4) | pBuf->current;
        pData[dataIdx+1]=(pBuf->tenpre<<4) | pBuf->precon;
    }

    return MBX_WriteCommand(pBuf->command_idx,pBuf->data_len,pData);

}

MS_BOOL MBX_WriteCommand_Config_Audio(ST_MBX_COMMAND_CONFIQ_AUDIO *pBuf)
{
    MS_U8 pData[5];
    int dataIdx=1;
    memset(pData, 0, sizeof(MS_U8)*5);

    device_hdmitx_DBG(printf("[Device ] CommandType(%x), DataLen(%x), InformPre(%x), SourcePre(%x), FormatPre(%x), Frequency(%x), ChannelNum(%x), CodeType(%x), SourceType(%x), SourceFormat(%x)\n",
    (int)pBuf->command_idx,(int)pBuf->data_len,
    (int)pBuf->inform_present,(int)pBuf->source_present,(int)pBuf->fmt_present,
    (int)pBuf->frequency,(int)pBuf->channel_num,(int)pBuf->code_type,(int)pBuf->source_type,(int)pBuf->source_fmt));

    if(pBuf->command_idx!=E_MBX_CONFIQ_AUDIO)
    {
        return FALSE;
    }
    if(pBuf->data_len>5)
    {
        return FALSE;
    }

    pData[0]=(pBuf->fmt_present<<2)|(pBuf->source_present<<1)|pBuf->inform_present;

    if(pBuf->inform_present && (pBuf->data_len>dataIdx))
    {
        pData[dataIdx]=(pBuf->channel_num<<4)|pBuf->frequency;
        pData[dataIdx+1]=pBuf->code_type;
        dataIdx=dataIdx+2;
    }
    if(pBuf->source_present && (pBuf->data_len>dataIdx))
    {
        pData[dataIdx]=pBuf->source_type;
        dataIdx++;
    }
    if(pBuf->fmt_present && (pBuf->data_len>dataIdx))
    {
        pData[dataIdx]=pBuf->source_fmt;
    }

    return MBX_WriteCommand(pBuf->command_idx,pBuf->data_len,pData);

}

MS_BOOL MBX_WriteCommand_TimingChange_AVmute(ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE *pBuf)
{
    MS_U8 pData[2];
    memset(pData, 0, sizeof(MS_U8)*2);

    device_hdmitx_DBG(printf("[Device ] CommandType(%x), DataLen(%x), VideoFlag(%x), AudioFlag(%x), AVMuteFlag(%x), TimingChangeFlag(%x), EnVideo(%x), EnAudio(%x), EnAVMute(%x), EnTimingChange(%x)\n",
    (int)pBuf->command_idx,(int)pBuf->data_len,
    (int)pBuf->video_flag,(int)pBuf->audio_flag,(int)pBuf->avmute_flag,(int)pBuf->timing_flag,
    (int)pBuf->enVideo_mute,(int)pBuf->enAudio_mute,(int)pBuf->enAV_mute,(int)pBuf->enTiming));

    if (pBuf->command_idx!=E_MBX_AVMUTE_TIMING_RESET)
    {
        return FALSE;
    }
    if (pBuf->data_len>2)
    {
        return FALSE;
    }

    pData[0]=(pBuf->timing_flag<<3)|(pBuf->avmute_flag<<2)|(pBuf->audio_flag<<1)|pBuf->video_flag;
    pData[1]=(pBuf->enTiming<<3)|(pBuf->enAV_mute<<2)|(pBuf->enAudio_mute<<1)|pBuf->enVideo_mute;

    return MBX_WriteCommand(pBuf->command_idx,pBuf->data_len,pData);

}

MS_BOOL MBX_WriteCommand_Query_EDID(ST_MBX_COMMAND_QUERY_EDID_INFO *pBuf)
{
    MS_U8 pData[3];
    memset(pData, 0, sizeof(MS_U8)*3);

    device_hdmitx_DBG(printf("[Device ] CommandType(%x), DataLen(%x), QueryType(%x), 3DTiming(%x), DescriptorStrIdx(%x), DescriptorEndIdx(%x), 64BytesIdx(%x), EdidIdx(%x)\n",
    (int)pBuf->command_idx,(int)pBuf->data_len,(int)pBuf->query_type,
    (int)pBuf->timing_3d,(int)pBuf->des_startIdx,(int)pBuf->des_endIdx,(int)pBuf->bytes64_Idx,(int)pBuf->edid_Idx));

    if (pBuf->command_idx!=E_MBX_QUERY_EDID_INFO)
    {
        return FALSE;
    }
    if (pBuf->data_len>3)
    {
        return FALSE;
    }

    pData[0]=pBuf->query_type;
    if(pBuf->data_len>1)
    {
        switch(pBuf->query_type)
        {
                case E_QUERY_3D_STRUCTURE:
                    pData[1]=pBuf->timing_3d;
                    pData[2]=0;
                    break;
                case E_QUERY_AUDIO_DESCRIPTOR:
                    pData[1]=pBuf->des_startIdx;
                    pData[2]=pBuf->des_endIdx;
                    break;
                case E_QUERY_VIDEO_DESCRIPTOR:
                    pData[1]=pBuf->des_startIdx;
                    pData[2]=pBuf->des_endIdx;
                    break;
                case E_QUERY_EDID_DATA:
                    pData[1]=pBuf->edid_Idx;
                    pData[2]=pBuf->bytes64_Idx;
                    break;
                default:
                    return FALSE;
        }
    }

    return MBX_WriteCommand(pBuf->command_idx,pBuf->data_len,pData);

}

MS_BOOL MBX_ReadCommand_Report_4K2KVic (ST_MBX_COMMAND_REPORT_EDID_INFO_4K2KVIC *pBuf)
{
    MS_U8 pData[10];
	int i;
    memset(pData, 0, sizeof(MS_U8)*10);


    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->command_idx!=E_MBX_REPORT_EDID_INFO)
        {
            return FALSE;
        }
        if(pData[0]!=0x01)
        {
            return FALSE;
        }
        pBuf->vic_num=pData[1]&0x0F;
        for(i=0;i<(pBuf->data_len - 2);i++)
        {
            switch(pData[i+2])
            {
                    case 0x00:
                        pBuf->vic4k2k[i]=E_HDMITX_VIDEO_4K2K_Reserved;
                        break;
                    case 0x01:
                        pBuf->vic4k2k[i]=E_HDMITX_VIDEO_4K2K_30Hz;
                        break;
                    case 0x02:
                        pBuf->vic4k2k[i]=E_HDMITX_VIDEO_4K2K_25Hz;
                        break;
                    case 0x03:
                        pBuf->vic4k2k[i]=E_HDMITX_VIDEO_4K2K_24Hz;
                        break;
                    case 0x04:
                        pBuf->vic4k2k[i]=E_HDMITX_VIDEO_4K2K_24Hz_SMPTE;
                        break;
                    default:
                        pBuf->vic4k2k[i]=E_HDMITX_VIDEO_4K2K_Reserved;
            }
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


MS_BOOL MBX_ReadCommand_Report_3D_Structure(ST_MBX_COMMAND_REPORT_EDID_INFO_3DSTRUCT *pBuf)
{
    MS_U8 data_len=0x04;
    MS_U8 pData[4];
    MS_U16 Data3D=(0);
    memset(pData, 0, sizeof(MS_U8)*4);

    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->data_len!=data_len)
        {
            return FALSE;
        }
        if(pData[0]==0x02)
        {
            switch(pData[1])
            {
                    case 0x00:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1280x720p_50Hz;
                        break;
                    case 0x01:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1280x720p_60Hz;
                        break;
                    case 0x02:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1920x1080i_50Hz;
                        break;
                    case 0x03:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1920x1080i_60Hz;
                        break;
                    case 0x04:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1920x1080p_24Hz;
                        break;
                    case 0x05:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1920x1080p_25Hz;
                        break;
                    case 0x06:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1920x1080p_50Hz;
                        break;
                    case 0x07:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_1920x1080p_60Hz;
                        break;
                    case 0x08:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_4K2Kp_25Hz;
                        break;
                    case 0x09:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_4K2Kp_30Hz;
                        break;
                    case 0x0A:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_4K2Kp_50Hz;
                        break;
                    case 0x0B:
                        pBuf->repTiming_3d=E_HDMITX_QUERY_3DTIMING_4K2Kp_60Hz;
                        break;
                    default:
                        return FALSE;
            }

            Data3D = (pData[3]<<8) | pData[2];
            pBuf->edid_3d=(EN_HDMITX_VIDEO_REPORT_3D_STRUCTURE_TYPE)Data3D;

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
}

MS_BOOL MBX_ReadCommand_Report_Num_AudioDescriptor(ST_MBX_COMMAND_REPORT_EDID_INFO_AUDIODES_NUM *pBuf)
{
    MS_U8 data_len=0x02;
    MS_U8 pData[2];
    memset(pData, 0, sizeof(MS_U8)*2);


    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->command_idx!=E_MBX_REPORT_EDID_INFO)
        {
            return FALSE;
        }
        if(pBuf->data_len!=data_len)
        {
            return FALSE;
        }
        if(pData[0]!=0x03)
        {
            return FALSE;
        }
        pBuf->auddes_num=pData[1];
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

MS_BOOL MBX_ReadCommand_Report_AudioDescriptor (ST_MBX_COMMAND_REPORT_EDID_INFO_AUDIODES *pBuf)
{
    MS_U8 pData[68];
	int i;
    memset(pData, 0, sizeof(MS_U8)*68);


    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->command_idx!=E_MBX_REPORT_EDID_INFO)
        {
            return FALSE;
        }
        if(pData[0]!=0x04)
        {
            return FALSE;
        }
        pBuf->audstr_Idx=pData[1];
        pBuf->audend_Idx=pData[2];
        for(i=0;i<(pBuf->data_len - 3);i++)
        {
            pBuf->aud_des[i]=pData[i+3];
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

MS_BOOL MBX_ReadCommand_Report_Num_VideoDescriptor(ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES_NUM *pBuf)
{
    MS_U8 data_len=0x02;
    MS_U8 pData[2];
    memset(pData, 0, sizeof(MS_U8)*2);


    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->command_idx!=E_MBX_REPORT_EDID_INFO)
        {
            return FALSE;
        }
        if(pBuf->data_len!=data_len)
        {
            return FALSE;
        }
        if(pData[0]!=0x05)
        {
            return FALSE;
        }
        pBuf->viddes_num=pData[1];
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

MS_BOOL MBX_ReadCommand_Report_VideoDescriptor (ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES *pBuf)
{
    MS_U8 pData[68];
	int i;
    memset(pData, 0, sizeof(MS_U8)*68);


    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->command_idx!=E_MBX_REPORT_EDID_INFO)
        {
            return FALSE;
        }
        if(pData[0]!=0x06)
        {
            return FALSE;
        }
        pBuf->vidstr_Idx=pData[1];
        pBuf->vidend_Idx=pData[2];
        for(i=0;i<(pBuf->data_len - 3);i++)
        {
            pBuf->vid_des[i]=pData[i+3];
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

MS_BOOL MBX_ReadCommand_Report_EDID_RawData(ST_MBX_COMMAND_REPORT_EDID_INFO_EDIDRAWDATA *pBuf)
{
    MS_U8 pData[68];
	int i;
    memset(pData, 0, sizeof(MS_U8)*68);


    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->command_idx!=E_MBX_REPORT_EDID_INFO)
        {
            return FALSE;
        }
        if(pData[0]!=0x07)
        {
            return FALSE;
        }
        pBuf->Idx_edid=pData[1]&0x0F;
        pBuf->Idx_64bytes=pData[1]&0xF0;
        for(i=0;i<(pBuf->data_len - 2);i++)
        {
            pBuf->raw_data[i]=pData[i+2];
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


MS_BOOL MBX_ReadCommand_ACK_Status(ST_MBX_COMMAND_ACK_STATUS_RESPONSE *pBuf)
{
    MS_U8 data_len=0x02;
    MS_U8 pData[2];
    memset(pData, 0, sizeof(MS_U8)*2);

    if(MBX_ReadCommand(pBuf->command_idx,pBuf->data_len,pData))
    {
        if(pBuf->data_len!=data_len)
        {
            return FALSE;
        }
        if(pBuf->command_idx==E_MBX_ACK_STATUS_RESPOND)
        {
            switch(pData[0])
            {
                    case 0x01:
                        pBuf->mbx_reccom=E_MBX_REPORT_CONFIQ_VIDEO;
                        break;
                    case 0x02:
                        pBuf->mbx_reccom=E_MBX_REPORT_CONFIQ_AUDIO;
                        break;
                    case 0x03:
                        pBuf->mbx_reccom=E_MBX_REPORT_AVMUTE_TIMING_RESET;
                        break;
                    case 0x04:
                        pBuf->mbx_reccom=E_MBX_REPORT_REPORT_EDID_INFO;
                        break;
                    default:
                        return FALSE;
            }

            switch(pData[1])
            {
                    case 0x00:
                        pBuf->mbx_status=E_MBX_REPORT_SUCCESS;
                        break;
                    case 0x01:
                        pBuf->mbx_status=E_MBX_REPORT_FAIL;
                        break;
                    case 0x02:
                        pBuf->mbx_status=E_MBX_REPORT_PARAMETER_INVALID;
                        break;
                    default:
                        return FALSE;
            }
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
}



MS_BOOL IIC02(MS_BOOL bEnable)
{
    MS_U8 u8DataBuf[5] = {0x53, 0x45, 0x52, 0x44, 0x42};
    MS_BOOL bResult = TRUE;
    MS_U8 u8cnt = 0;

    if (bEnable)
    {
        u8DataBuf[0] = 0x53;

        while(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 5, u8DataBuf) == FALSE)
        {
            u8cnt++;
            bResult = FALSE;
            if(u8cnt == 0x20)
                break;
        }
    }
    else
    {
        u8DataBuf[0] = 0x45;

        while(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 5, u8DataBuf) == FALSE)
        {
            bResult = FALSE;
            if(u8cnt == 0x20)
                break;
        }
    }
    return bResult;

}

MS_BOOL IIC03(void)
{
    MS_U8 u8DataBuf;
    MS_BOOL bResult = TRUE;

    u8DataBuf = 0x81;
    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf) == FALSE)
    {
        bResult &= IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf);
    }
    u8DataBuf = 0x83;
    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf) == FALSE)
    {
        bResult &= IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf);
    }
    u8DataBuf = 0x84;
    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf) == FALSE)
    {
        bResult &= IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf);
    }
    u8DataBuf = 0x51;
    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf) == FALSE)
    {
        bResult &= IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf);
    }
    u8DataBuf = 0x7F;
    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf) == FALSE)
    {
        bResult &= IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf);
    }

    return bResult;

}

MS_BOOL IIC01(MS_BOOL bEnable)
{

    MS_U8 u8DataBuf;
    MS_BOOL bResult = FALSE;

    if(bEnable)
        u8DataBuf = 0x35;
    else
        u8DataBuf = 0x34;

    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf) == FALSE)
    {
        bResult = IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf);
    }

    u8DataBuf = 0x71;
    if(IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf) == FALSE)
    {
        bResult = IIC_WriteBytes(DEVICE_I2C_SLAVE_ID, 0, NULL, 1, &u8DataBuf);
    }

    return bResult;

}

void Chip_IIC_Init(void)
{
    IIC01(FALSE);
    IIC02(FALSE);
    IIC02(TRUE);
    IIC03();
    IIC01(TRUE);
}

void Chip_Init(void)
{
    w2byte(0x1304, 0x0001);
    w2byte(0x1E40, 0x0000);
    w2byte(0x1E42, 0x0000);
    w2byte(0x1E44, 0x0000);
    w2byte(0x1E46, 0x0000);
    w2byte(0x1E48, 0x0000);
    w2byte(0x1E4A, 0x0000);
    w2byte(0x1E4C, 0x0000);
    w2byte(0x1E4E, 0x0000);
    w2byte(0x1E60, 0x0000);
    w2byte(0x1E62, 0x0000);
    w2byte(0x1E64, 0x0000);
    w2byte(0x1E66, 0x0000);
    w2byte(0x1E68, 0x0000);
    w2byte(0x1E74, 0x0000);
    w2byte(0x1E76, 0x0020);
    w2byte(0x1E78, 0x0000);
    w2byte(0x1E7A, 0x0000);
    w2byte(0x0B00, 0x0000);
    w2byte(0x0B80, 0x1000);
    w2byte(0x000FE4, 0x0001);
    w2byte(0x000EC0, 0x000B);
    w2byte(0x000EC2, 0x0000);
    w2byte(0x000EC4, 0x0000);
    w2byte(0x000EC6, 0x0000);
    w2byte(0x000EC8, 0x0000);
    w2byte(0x000ED4, 0x0005);
    w2byte(0x000ED6, 0x0001);
    w2byte(0x000ED8, 0x0007);
    w2byte(0x000EDA, 0x0001);
    SET_SYS_DELAY_MS_MS(10);
    w2byte(0x000EDE, 0x0001);
    w2byte(0x001E72, 0x0800);
    w2byte(0x001E72, 0x1800);
    w2byte(0x1E20, 0x0003);
    w2byte(0x1C80, 0x0001);
    SET_SYS_DELAY_MS_MS(1);
    w2byte(0x1C80, 0x000F);
}

void Send_Interrupt(void)
{
    w2byte(0x2B0C, 0x0000);
    w2byte(0x2B0C, 0x0001);
}

MS_BOOL Read_ACK(void)
{
    MS_BOOL bgpio=FALSE;

    //bgpio =mdrv_gpio_get_level(PIN_117);//modified by Weng 2015.09.16
    bgpio=TRUE;
	msAPI_Timer_Delayms(100);//added by Weng 2015.09.16
	//printf("Read_ACK is %d\n",bgpio);//added by Weng 2015.09.16
    if(bgpio)
        return TRUE;
    else
        return FALSE;
}

void Set_ACK_Low(void)
{
    w2byte(0x1250,0x0000);
    w2byte(0x0A02, (r2byte(0x0A02) & 0xFFDF));
    w2byte(0x0A0A, (r2byte(0x0A0A) | 0x0020));
}

MS_BOOL Fn_WaitACK(void)
{
    //read  ACK
    MS_U32 bFirstTimer;
    MS_U32 bTimer;
    bFirstTimer= GET_SYS_TIME();
   while(!Read_ACK())
    {
        SET_SYS_DELAY_MS_MS(100);
        bTimer=GET_SYS_TIME();
        if((int)(bTimer-bFirstTimer)>5000)
        {
            return FALSE;
        }
    }

	//SET_SYS_DELAY_MS_MS(200);
    return TRUE;
}

MS_BOOL Fn_WaitReport(void)
{
    //read  ACK
    MS_U32 bFirstTimer;
    MS_U32 bTimer;
    bFirstTimer=GET_SYS_TIME();
    while((r2byte(0x1200) & 0xFF)!=0x05)
    {
        SET_SYS_DELAY_MS_MS(100);
        bTimer=GET_SYS_TIME();
        if((int)(bTimer-bFirstTimer)>5000)
        {
            return FALSE;
        }
    }
    return TRUE;
}

 BOOL device_hdmitx_4030_Chip_Init(void)
 {
 	//init
    MS_U8 chipID;
    MS_U16 chipCPU;
    MS_U32 bFirstTimer;
    MS_U32 bTimer;

    Chip_IIC_Init();

    //read ChipID
    Device_Hdmitx_IIC_ReadBytes(0x1E00,&chipID);
    device_hdmitx_DBG(printf("[Device ] show ChipID 1E 00 =%x\n",chipID));
    if(chipID!=0x97)
    {
        device_hdmitx_DBG(printf("[Device ] Read Chip ID FAIL!!!\n"));
        return FALSE;
    }

    Chip_Init();

    //read  CPU Status
    chipCPU=r2byte(0x1EFE);
    bFirstTimer=GET_SYS_TIME();
    while(chipCPU!=0xB430)
    {
        bTimer=GET_SYS_TIME();
        if((int)(bTimer-bFirstTimer)>5000)
        {
           device_hdmitx_DBG( printf("[Device ] Init Fail! CPU not ready! Time out!\n"));
            return FALSE;
        }
        SET_SYS_DELAY_MS_MS(100);
        chipCPU=r2byte(0x1EFE);
    }

    return TRUE;
 }

 BOOL device_hdmitx_SetTimingType(EN_MAPI_HDMITX_TIMING_TYPE enTiming)
{
	 switch(enTiming)
	 {
		 case E_MAPI_HDMITX_TIMING_576_50P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_720x576p_50Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_480_60P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_720x480p_60Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_720_50P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_1280x720p_50Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_720_60P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_1280x720p_60Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_1080_24P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_1920x1080p_24Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_1080_50I:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_1920x1080i_50Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_1080_60I:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_1920x1080i_60Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_1080_50P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_1920x1080p_50Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_1080_60P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_1920x1080p_60Hz;
			 device_hdmitx_DBG(printf("\r\n[Device 4030] E_HDMITX_TIMING_1920x1080p_60Hz\n"));
			 break;
		 case E_MAPI_HDMITX_TIMING_4K2K_25P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_4K2Kp_25Hz;
			 break;
		 case E_MAPI_HDMITX_TIMING_4K2K_30P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_4K2Kp_30Hz;
			 break;

		 case E_MAPI_HDMITX_TIMING_4K2K_50P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_4K2Kp_50Hz;
			 device_hdmitx_DBG(printf("\r\n[Device 4030] E_MAPI_HDMITX_TIMING_4K2K_50P\n"));
			 break;

		 case E_MAPI_HDMITX_TIMING_4K2K_60P:
			 genHDMITx_VideoTiming = E_HDMITX_TIMING_4K2Kp_60Hz;
			 device_hdmitx_DBG(printf("\r\n[Device 4030] E_MAPI_HDMITX_TIMING_4K2K_60P\n"));
			 break;
		 default:
			 device_hdmitx_DBG(printf("[Device 4030] Wrong Mode of EN_MAPI_HDMITX_TIMING_TYPE \n"));
			 return FALSE;
	 }

	// genMAPI_HDMITxTming = enTiming;

	 //Set Timing Example, Timing=4K2K_60
	 //Set Audio & Video Mute
	 ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE setFlag;
	 setFlag.command_idx=E_MBX_AVMUTE_TIMING_RESET;
	 setFlag.data_len=0x02;
	 setFlag.video_flag   = FALSE;
	 setFlag.audio_flag   = FALSE;
	 setFlag.avmute_flag  = TRUE;
	 setFlag.timing_flag  = FALSE;
	 setFlag.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
	 setFlag.enAV_mute	  = E_HDMITX_AVMUTE_ENABLE;
	 setFlag.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
	 setFlag.enTiming	  = E_HDMITX_TIMING_CHANGE_DISABLE;
	 MBX_WriteCommand_TimingChange_AVmute(&setFlag);
	 Send_Interrupt();
	 if(!Fn_WaitACK())//read  ACK
	 {
		 device_hdmitx_DBG(printf("[Device ] Read ACK Fail!!!\n"));
		 return FALSE;
	 }

	 Set_ACK_Low();//set ACK low after read it high

	 //Set Timing Change Flag
	 ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE setTmgChg;
	 setTmgChg.command_idx=E_MBX_AVMUTE_TIMING_RESET;
	 setTmgChg.data_len=0x02;
	 setTmgChg.video_flag	= FALSE;
	 setTmgChg.audio_flag	= FALSE;
	 setTmgChg.avmute_flag	= FALSE;
	 setTmgChg.timing_flag	= TRUE;
	 setTmgChg.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
	 setTmgChg.enAV_mute	= E_HDMITX_AVMUTE_DISABLE;
	 setTmgChg.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
	 setTmgChg.enTiming 	= E_HDMITX_TIMING_CHANGE_ENABLE;
	 MBX_WriteCommand_TimingChange_AVmute(&setTmgChg);
	 Send_Interrupt();
	 if(!Fn_WaitACK())//read  ACK
	 {
		 device_hdmitx_DBG(printf("[Device ] Read ACK Fail!!!\n"));
		 return FALSE;
	 }

	 Set_ACK_Low();//set ACK low after read it high

	 //Set	Video
	// genHDMITx_VideoTiming = E_HDMITX_TIMING_4K2Kp_60Hz;
	 ST_MBX_COMMAND_CONFIQ_VIDEO setTiming;
	 setTiming.command_idx=E_MBX_CONFIQ_VIDEO;
	 setTiming.data_len=0x03;
	 setTiming.timing_present	 = TRUE;
	 setTiming.color_present	 = TRUE;
	 setTiming.VSinfo_3D_present = FALSE;
	 setTiming.analog_present	 = FALSE;
	 setTiming.timing_idx  = genHDMITx_VideoTiming;
	 setTiming.color_depth = genHDMITx_ColorDepth;
	 setTiming.output_mode = genHDMITX_Mode;
	 setTiming.in_color    = genHDMITx_InColor;
	 setTiming.out_color   = genHDMITx_OutColor;
	 setTiming.vs_3d	   = E_HDMITX_VIDEO_3D_FramePacking;
	 setTiming.current=0;
	 setTiming.pren2=FALSE;
	 setTiming.precon=0;
	 setTiming.tenpre=0;
	 setTiming.ten=0;
	 MBX_WriteCommand_Config_Video(&setTiming);
	 Send_Interrupt();
	 if(!Fn_WaitACK())//read  ACK
	 {
		 device_hdmitx_DBG(printf("[Device ] Read ACK Fail!!!\n"));
		 return FALSE;
	 }

	 Set_ACK_Low();//set ACK low after read it high

	 //Set	Audio
	 ST_MBX_COMMAND_CONFIQ_AUDIO setAudio;
	 setAudio.command_idx=E_MBX_CONFIQ_AUDIO;
	 setAudio.data_len=0x05;
	 setAudio.inform_present = TRUE;
	 setAudio.source_present = TRUE;
	 setAudio.fmt_present	 = TRUE;
	 setAudio.frequency 	 = genAudio_Freq;
	 setAudio.channel_num	 = genAudio_Ch_Cnt;
	 setAudio.code_type 	 = genAudio_CodeType;
	 setAudio.source_type	 = genAudio_SrcType;
	 setAudio.source_fmt	 = genAudio_SrcFmt;
	 MBX_WriteCommand_Config_Audio(&setAudio);
	 Send_Interrupt();
	 if(!Fn_WaitACK())//read  ACK
	 {
		 device_hdmitx_DBG(printf("[Device ] Read ACK Fail!!!\n"));
		 return FALSE;
	 }

	 Set_ACK_Low();//set ACK low after read it high

	 //Set Timing Change Flag Off
	 setTmgChg.command_idx=E_MBX_AVMUTE_TIMING_RESET;
	 setTmgChg.data_len=0x02;
	 setTmgChg.video_flag	= FALSE;
	 setTmgChg.audio_flag	= FALSE;
	 setTmgChg.avmute_flag	= FALSE;
	 setTmgChg.timing_flag	= TRUE;
	 setTmgChg.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
	 setTmgChg.enAV_mute	= E_HDMITX_AVMUTE_DISABLE;
	 setTmgChg.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
	 setTmgChg.enTiming 	= E_HDMITX_TIMING_CHANGE_DISABLE;
	 MBX_WriteCommand_TimingChange_AVmute(&setTmgChg);
	 Send_Interrupt();
	 if(!Fn_WaitACK())//read  ACK
	 {
		 device_hdmitx_DBG(printf("[Device ] Read ACK Fail!!!\n"));
		 return FALSE;
	 }

	 Set_ACK_Low();//set ACK low after read it high

	 //Set Audio & Video Mute Off (Turn AV on)
	 setFlag.command_idx=E_MBX_AVMUTE_TIMING_RESET;
	 setFlag.data_len=0x02;
	 setFlag.video_flag   = FALSE;
	 setFlag.audio_flag   = FALSE;
	 setFlag.avmute_flag  = TRUE;
	 setFlag.timing_flag  = FALSE;
	 setFlag.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
	 setFlag.enAV_mute=E_HDMITX_AVMUTE_DISABLE;
	 setFlag.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
	 setFlag.enTiming	  = E_HDMITX_TIMING_CHANGE_DISABLE;
	 MBX_WriteCommand_TimingChange_AVmute(&setFlag);
	 Send_Interrupt();
	 if(!Fn_WaitACK())//read  ACK
	 {
		 device_hdmitx_DBG(printf("[Device ] Read ACK Fail!!!\n"));
		 return FALSE;
	 }

	 Set_ACK_Low();//set ACK low after read it high

  return TRUE;
}


#if(HDMITX_4030_ENABLE==ENABLE)
void device_hdmitx_SetTmingByPanel(PANEL_RESOLUTION_TYPE enResolutionType)
 {
    if(enResolutionType==PNL_HDMITX_VB1_4K2K_60P_MS)
    {
        device_hdmitx_SetTimingType(E_MAPI_HDMITX_TIMING_4K2K_60P);
    }
    else if (enResolutionType==PNL_HDMITX_VB1_4K2K_30P_MS)
    {
        device_hdmitx_SetTimingType(E_MAPI_HDMITX_TIMING_4K2K_30P);
        MDrv_Write2Byte(0x111E00, 0X4000);
    }
    else if (enResolutionType==PNL_HDMITX_VB1_FHD_60P_MS)
    {
        device_hdmitx_SetTimingType(E_MAPI_HDMITX_TIMING_1080_60P);
        MDrv_Write2Byte(0x111E00, 0X4000);
        MDrv_Write2Byte(0x111E02, 0X0001);
    }
 }
#endif

void main_test(void)
{
    //init

    //Set Timing Example, Timing=4K2K_60
    //Set Audio & Video Mute
    ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE setFlag;
    setFlag.command_idx=E_MBX_AVMUTE_TIMING_RESET;
    setFlag.data_len=0x02;
    setFlag.video_flag   = TRUE;
    setFlag.audio_flag   = FALSE;
    setFlag.avmute_flag  = TRUE;
    setFlag.timing_flag  = FALSE;
    setFlag.enVideo_mute = E_HDMITX_VIDEO_MUTE_ENABLE;
    setFlag.enAV_mute    = E_HDMITX_AVMUTE_ENABLE;
    setFlag.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
    setFlag.enTiming     = E_HDMITX_TIMING_CHANGE_DISABLE;
    MBX_WriteCommand_TimingChange_AVmute(&setFlag);
    Send_Interrupt();
        if(!Fn_WaitACK())//read  ACK
        {
            device_hdmitx_DBG(printf("[Device ] Read ACK Fail!!!\n"));
          //  return FALSE;
        }

        Set_ACK_Low();//set ACK low after read it high

}

/*int main_test(void)
{
    //init
    MS_U8 chipID;
    MS_U16 chipCPU;
    MS_U32 bFirstTimer;
    MS_U32 bTimer;

    Chip_IIC_Init();

    //read ChipID
    Device_Hdmitx_IIC_ReadBytes(0x1E00,&chipID);
    printf("[Device ] show ChipID 1E 00 =%x\n",chipID);
    if(chipID!=0x97)
    {
        printf("[Device ] Read Chip ID FAIL!!!\n");
        return FALSE;
    }

    Chip_Init();

    //read  CPU Status
    chipCPU=r2byte(0x1EFE);
    bFirstTimer=GET_SYS_TIME();
    while(chipCPU!=0xB430)
    {
        bTimer=GET_SYS_TIME();
        if((int)(bTimer-bFirstTimer)>5000)
        {
            printf("[Device ] Init Fail! CPU not ready! Time out!\n");
            return FALSE;
        }
        SET_SYS_DELAY_MS_MS(100);
        chipCPU=r2byte(0x1EFE);
    }

    //Set Timing Example, Timing=4K2K_60
    //Set Audio & Video Mute
    ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE setFlag;
    setFlag.command_idx=E_MBX_AVMUTE_TIMING_RESET;
    setFlag.data_len=0x02;
    setFlag.video_flag   = FALSE;
    setFlag.audio_flag   = FALSE;
    setFlag.avmute_flag  = TRUE;
    setFlag.timing_flag  = FALSE;
    setFlag.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
    setFlag.enAV_mute    = E_HDMITX_AVMUTE_ENABLE;
    setFlag.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
    setFlag.enTiming     = E_HDMITX_TIMING_CHANGE_DISABLE;
    MBX_WriteCommand_TimingChange_AVmute(&setFlag);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }

    Set_ACK_Low();//set ACK low after read it high

    //Set Timing Change Flag
    ST_MBX_COMMAND_TIMING_CHANGE_AVMUTE setTmgChg;
    setTmgChg.command_idx=E_MBX_AVMUTE_TIMING_RESET;
    setTmgChg.data_len=0x02;
    setTmgChg.video_flag   = FALSE;
    setTmgChg.audio_flag   = FALSE;
    setTmgChg.avmute_flag  = FALSE;
    setTmgChg.timing_flag  = TRUE;
    setTmgChg.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
    setTmgChg.enAV_mute    = E_HDMITX_AVMUTE_DISABLE;
    setTmgChg.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
    setTmgChg.enTiming     = E_HDMITX_TIMING_CHANGE_ENABLE;
    MBX_WriteCommand_TimingChange_AVmute(&setTmgChg);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }

    Set_ACK_Low();//set ACK low after read it high

    //Set  Video
    genHDMITx_VideoTiming = E_HDMITX_TIMING_4K2Kp_60Hz;
    ST_MBX_COMMAND_CONFIQ_VIDEO setTiming;
    setTiming.command_idx=E_MBX_CONFIQ_VIDEO;
    setTiming.data_len=0x03;
    setTiming.timing_present    = TRUE;
    setTiming.color_present     = TRUE;
    setTiming.VSinfo_3D_present = FALSE;
    setTiming.analog_present    = FALSE;
    setTiming.timing_idx  = genHDMITx_VideoTiming;
    setTiming.color_depth = genHDMITx_ColorDepth;
    setTiming.output_mode = genHDMITX_Mode;
    setTiming.in_color    = genHDMITx_InColor;
    setTiming.out_color   = genHDMITx_OutColor;
    setTiming.vs_3d       = E_HDMITX_VIDEO_3D_FramePacking;
    setTiming.current=0;
    setTiming.pren2=FALSE;
    setTiming.precon=0;
    setTiming.tenpre=0;
    setTiming.ten=0;
    MBX_WriteCommand_Config_Video(&setTiming);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }

    Set_ACK_Low();//set ACK low after read it high

    //Set  Audio
    ST_MBX_COMMAND_CONFIQ_AUDIO setAudio;
    setAudio.command_idx=E_MBX_CONFIQ_AUDIO;
    setAudio.data_len=0x05;
    setAudio.inform_present = TRUE;
    setAudio.source_present = TRUE;
    setAudio.fmt_present    = TRUE;
    setAudio.frequency      = genAudio_Freq;
    setAudio.channel_num    = genAudio_Ch_Cnt;
    setAudio.code_type      = genAudio_CodeType;
    setAudio.source_type    = genAudio_SrcType;
    setAudio.source_fmt     = genAudio_SrcFmt;
    MBX_WriteCommand_Config_Audio(&setAudio);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }

    Set_ACK_Low();//set ACK low after read it high

    //Set Timing Change Flag Off
    setTmgChg.command_idx=E_MBX_AVMUTE_TIMING_RESET;
    setTmgChg.data_len=0x02;
    setTmgChg.video_flag   = FALSE;
    setTmgChg.audio_flag   = FALSE;
    setTmgChg.avmute_flag  = FALSE;
    setTmgChg.timing_flag  = TRUE;
    setTmgChg.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
    setTmgChg.enAV_mute    = E_HDMITX_AVMUTE_DISABLE;
    setTmgChg.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
    setTmgChg.enTiming     = E_HDMITX_TIMING_CHANGE_DISABLE;
    MBX_WriteCommand_TimingChange_AVmute(&setTmgChg);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }

    Set_ACK_Low();//set ACK low after read it high

    //Set Audio & Video Mute Off (Turn AV on)
    setFlag.command_idx=E_MBX_AVMUTE_TIMING_RESET;
    setFlag.data_len=0x02;
    setFlag.video_flag   = FALSE;
    setFlag.audio_flag   = FALSE;
    setFlag.avmute_flag  = TRUE;
    setFlag.timing_flag  = FALSE;
    setFlag.enVideo_mute = E_HDMITX_VIDEO_MUTE_DISABLE;
    setFlag.enAV_mute=E_HDMITX_AVMUTE_DISABLE;
    setFlag.enAudio_mute = E_HDMITX_AUDIO_MUTE_DISABLE;
    setFlag.enTiming     = E_HDMITX_TIMING_CHANGE_DISABLE;
    MBX_WriteCommand_TimingChange_AVmute(&setFlag);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }

    Set_ACK_Low();//set ACK low after read it high



    //Get EDID Data Sample
    MS_U8 u8Num;
    HDMI_EDID_INFO_DATA *penEDIDVic;
    MS_U8 i;
    MS_U8 u8MaxNum = u8Num > 32 ? 32 : u8Num;
    ST_MBX_COMMAND_QUERY_EDID_INFO getVideoNum;
    ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES_NUM getNum;
    ST_MBX_COMMAND_QUERY_EDID_INFO setVideoEdid;
    ST_MBX_COMMAND_REPORT_EDID_INFO_VIDEODES getVideoEdid;

    memset(penEDIDVic, 0 , sizeof(HDMI_EDID_INFO_DATA)*u8Num);

    //Get the Number of Video Descriptors
    getVideoNum.command_idx=E_MBX_QUERY_EDID_INFO;
    getVideoNum.data_len=0x01;
    getVideoNum.query_type=E_QUERY_VIDEO_DESCRIPTOR_NUM;
    MBX_WriteCommand_Query_EDID(&getVideoNum);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }
    Set_ACK_Low();//set ACK low after read it high
    if(Fn_WaitReport())
    {
        MBX_ReadCommand_Report_Num_VideoDescriptor(&getNum);
        if(u8MaxNum>getNum.viddes_num)
            u8MaxNum=getNum.viddes_num;
    }
    else
    {
        printf("[Device ] Get EDID Number Fail!\n");
        return FALSE;
    }

    //Get Video Descriptors
    setVideoEdid.command_idx=E_MBX_QUERY_EDID_INFO;
    setVideoEdid.data_len=0x03;
    setVideoEdid.query_type=E_QUERY_VIDEO_DESCRIPTOR;
    setVideoEdid.des_startIdx=0x00;
    setVideoEdid.des_endIdx= u8MaxNum - 1;
    MBX_WriteCommand_Query_EDID(&setVideoEdid);
    Send_Interrupt();
    if(!Fn_WaitACK())//read  ACK
    {
        printf("[Device ] Read ACK Fail!!!\n");
        return FALSE;
    }
    Set_ACK_Low();//set ACK low after read it high
    if(Fn_WaitReport())
    {
        MBX_ReadCommand_Report_VideoDescriptor(&getVideoEdid);
        for(i=0;i<u8MaxNum;i++)
        {
             penEDIDVic[i].EDID_DATA = (MS_U8)(getVideoEdid.vid_des[i] & 0x7F);
             penEDIDVic[i].native    = (MS_U8)(getVideoEdid.vid_des[i] & 0x80)>>7;
        }

    }
    else
    {
        printf("[Device ] Get EDID Fail! Wait no EDID Info!\n");
        return FALSE;
    }

    return TRUE;

}
*/
#endif
