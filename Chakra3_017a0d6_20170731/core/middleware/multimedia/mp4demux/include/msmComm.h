////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
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


#if !defined(MSMINTCAUSE_H)
#define MSMINTCAUSE_H

typedef enum MSMIntCause_e_
{
    /* Device Command */
    MSM_INT_DEV_CHIP = 0x00,
    MSM_INT_DEV_CAM = 0x01,
    MSM_INT_DEV_AUD = 0x02,
    MSM_INT_DEV_IP = 0x03,
    MSM_INT_DEV_DISP = 0x04,
    MSM_INT_DEV_REC = 0x05,
    MSM_INT_DEV_USB = 0x06,
    MSM_INT_DEV_FS = 0x07,
    MSM_INT_DEV_GE = 0x08,
    MSM_INT_DEV_MP = 0x09,
    MSM_INT_DEV_CD = 0x0a,
    MSM_INT_DEV_BOUNDARY = 0x0F,
    MSM_INT_CMD_REDAY = 0x10,
    MSM_INT_CMD_FETCHED = 0x11,
    MSM_INT_CMD_RETURN_READY = 0x12,
    MSM_INT_DATA_READY = 0x13,
    MSM_INT_OSD_BUFFER_READY = 0x14,
    MSM_INT_FRAME_BUFFER_READY = 0x15,
    //MSM_INT_NO_DATA = 0x16,
    MSM_INT_INITREADY = 0x17,
    MSM_INT_FETCHED = 0x18,
    MSM_INT_NOTIFY = 0x19,
    MSM_INT_USB_PC_CONNECT = 0x1a,
    MSM_INT_USB_PC_REMOVE = 0x1b,
    MSM_INT_SD_INSERT = 0x1c,
    MSM_INT_SD_REMOVE = 0x1d,
    MSM_INT_PATCHCODE_READY = 0x1e,
    MSM_INT_ACCEPT_CMD_READY = 0x1f,

    /* Probe */
    MSM_INT_CHECK_SYSTEM_STATUS = 0x20,
    MSM_INT_CHECK_ESSENTIALS = 0x16,

    /* USB request */
    MSM_INT_USB_REQUEST = 0x21,

    /* Direct Write */
    MSM_INT_DIRECT_WRITE_VARIABLE = 0x22,   /* M2 -> BB (count variables) */
    MSM_INT_DIRECT_WRITE_BUFFER = 0x23,     /* M2 -> BB (buffer start address) */
    MSM_INT_DIRECT_WRITE_DONE = 0x24,       /* BB -> M2 */

    /* Date and Time */
    //MSM_INT_DATE_TIME_UPDATE = 0x25,

    /* CDC Direct Write*/
    MSM_INT_CDC_DIRECT_WRITE_VARIABLE = 0x26,   /* M2 -> BB (count variables) */
    MSM_INT_CDC_DIRECT_WRITE_BUFFER = 0x27,     /* M2 -> BB (buffer start address) */
    MSM_INT_CDC_DIRECT_WRITE_DONE = 0x28,

    /* OSD Direct Write*/
    MSM_INT_DIRECT_WRITE_DISPLAY_VARIABLE = 0x29,   /* M2 -> BB (count variables) */
    MSM_INT_DIRECT_WRITE_DISPLAY_BUFFER = 0x2A,     /* M2 -> BB (buffer start address) */
    MSM_INT_DIRECT_WRITE_DISP_DONE = 0x2B,          /* BB -> M2 (display write done) */
    MSM_INT_DIRECT_WRITE_DISP_FLIP = 0x2C,          /* BB -> M2 (display flip) */
    MSM_INT_DIRECT_WRITE_MIDI_VARIABLE = 0x2D,      /* M2 -> BB (midi streaming count variable) */
    MSM_INT_DIRECT_WRITE_MIDI_TABLE = 0x2E,         /* M2 -> BB (midi RO table address) */
    MSM_INT_DIRECT_WRITE_MIDI_TABLE_DONE = 0x2F,    /* BB -> M2 (midi write table done) */
    MSM_INT_DIRECT_WRITE_MIDI_BUFFER = 0x30,        /* M2 -> BB (midi streaming buffer address) */
    MSM_INT_DIRECT_WRITE_MIDI_BUFFER_DONE = 0x31,   /* BB -> M2 (midi write buffer done) */
    MSM_INT_DIRECT_WRITE_MP3_VARIABLE = 0x32,       /* M2 -> BB (mp3 streaming count variable) */
    MSM_INT_DIRECT_WRITE_MP3_BUFFER = 0x33,         /* M2 -> BB (mp3 streaming buffer) */
    MSM_INT_DIRECT_WRITE_MP3_DONE = 0x34,           /* BB -> M2 (mp3 write done) */
    MSM_INT_DIRECT_WRITE_IPTV_VARIABLE = 0x35,      /* M2 -> BB (iptv streaming count variable) */
    MSM_INT_DIRECT_WRITE_IPTV_BUFFER = 0x36,        /* M2 -> BB (iptv streaming buffer) */
    MSM_INT_DIRECT_WRITE_IPTV_DONE = 0x37,          /* BB -> M2 (iptv write done) */
    MSM_INT_DIRECT_WRITE_SHUTTER_VARIABLE = 0x38,   /* M2 -> BB (shutter sound streaming count variable) */
    MSM_INT_DIRECT_WRITE_SHUTTER_BUFFER = 0x39,     /* M2 -> BB (shutter sound streaming buffer) */
    MSM_INT_DIRECT_WRITE_SHUTTER_DONE = 0x3A,       /* BB -> M2 (shutter sound write done) */
    //File Write
    MSM_INT_DIRECT_WRITE_FILE_VARIABLE = 0x3B,      /* M2 -> BB (file write variable) */
    MSM_INT_DIRECT_WRITE_FILE_BUFFER = 0x3C,        /* M2 -> BB (file write buffer) */
    MSM_INT_DIRECT_WRITE_FILE_DONE = 0x3D,          /* BB -> M2 (done) */
    MSM_INT_DIRECT_WRITE_FILE_LENGTH = 0x3E,          /* Get Total File Size */
    MSM_INT_DIRECT_WRITE_FILE_LENGTH_DONE = 0x3F,          /* Get Total File Size */

    /* DISP */
    MSM_INT_DISP_BYPASS_REQUEST = 0x40,
    MSM_INT_DISP_BYPASS_COLOREXPAND_REQUEST = 0x41,
    MSM_INT_DISP_BYPASS_CONFIRM = 0x42,

    MSM_INT_DIRECT_WRITE_JPD_VARIABLE = 0x43,   /* M2 -> BB (jpeg streaming count variable) */
    MSM_INT_DIRECT_WRITE_JPD_BUFFER = 0x44,     /* M2 -> BB (jpeg streaming buffer) */
    MSM_INT_DIRECT_WRITE_JPD_DONE = 0x45,       /* BB -> M2 (jpeg write done) */
    MSM_INT_JPEG_STREAM_DECODE_COMPLETE= 0x46,  /* M2 -> BB */

    MSM_INT_DISP_PICTURE_TUNING_ENABLE = 0x47,
    MSM_INT_DISP_PICTURE_TUNING_DISABLE = 0x48,

    MSM_INT_JPEG_DECODE_COMPLETE= 0x49,

    MSM_INT_OSD_UPDATE_DONE = 0x4A,

    /* REC (0x50~0x5F) */
    MSM_INT_RECORD_STATE_CHANGE = 0x50,
    MSM_INT_RECORD_SAVE_FILE_COMPLETE = 0x51,
    MSM_INT_RECORD_ERROR = 0x52,
    MSM_INT_RECORD_POSITION_UPDATE = 0x53,

    MSM_INT_DIRECT_WRITE_RGB_VARIABLE = 0x54,       /* M2 -> BB (rgb write variable) */
    MSM_INT_DIRECT_WRITE_RGB_BUFFER = 0x55,         /* M2 -> BB (rgb write buffer) */
    MSM_INT_DIRECT_WRITE_RGB_DONE = 0x56,           /* BB -> M2 (rgb write done) */

    /* FS (0x60~0x6F) */
    MSM_INT_FILE_COPY_POSITION_UPDATE = 0x60,
    MSM_INT_FILE_STATUS_UPDATE = 0x61,
    MSM_INT_FILE_FILE_SAVE_SD_COMPLETE = 0x62,
    MSM_INT_COPY_STATE_CHANGE = 0x63,

    //Disk Information Wite
    MSM_INT_DIRECT_WRITE_DISK_INFO_VARIABLE = 0x65, //(sent from Montage to Baseband)
    MSM_INT_DIRECT_WRITE_DISK_INFO_BUFFER   = 0x66,   /* M2 -> BB ( write buffer and size) */
    MSM_INT_DIRECT_WRITE_DISK_INFO_DONE     = 0x67,     /* BB -> M2 (done) */
    MSM_INT_NAND_POWER_ON                   = 0x68,
    MSM_INT_NAND_POWER_OFF                  = 0x69,

    /* USB */
    MSM_INT_USB_SUSPEND                     = 0x70,
    MSM_INT_USB_RESUME                      = 0x71,
    MSM_INT_USB_VBUS_CONNECT                = 0x72,
    MSM_INT_USB_VBUS_REMOVE                 = 0x73,

    /* MP (0x90~0x9F) */
    MSM_INT_PLAY_SATE_CHANGE                = 0x90,
    MSM_INT_PLAY_POSITION_UPDATE            = 0x91,
    MSM_INT_PLAY_ERROR                      = 0x92,
    MSM_INT_BITRATE_CHANGE                  = 0x93,
    MSM_INT_LYRICS_UPDATE                   = 0x94,
    MSM_INT_STREAM_TYPE_INDICATOR           = 0x95,
    /* Shared Data Memory */
    MSM_INT_CMMB_AUDIO_DECODE_DONE          = 0x96,
    /* Bluetooth */
    MSM_INT_BLUETOOTH_STREAM_DECODE_COMPLETE= 0x97,
    MSM_INT_BLUETOOTH_STATUS_UPDATE         = 0x99,

    /* Error Detection (0xA0~0xAF) */
    MSM_INT_M2_EXCEPTION                    = 0xA0,
    MSM_INT_M2_CONFIRM                      = 0xA1,
    MSM_INT_M2_UNDERFLOW                    = 0xA2,
    MSM_INT_BACKTRACE_BUFFER_READY          = 0xA3,
    MSM_INT_HARDWARE_FAILURE                = 0xA4,
    MSM_INT_SYSTEM_SWITCH_AUDIO_AMP         = 0xA5,
    MSM_INT_BASEBAND_EXCEPTION              = 0xA6,
    MSM_INT_PERIPHERAL_CONTROL              = 0xA8, // SD card power

    /* CD */
    MSM_INT_DIRECT_WRITE_CD_VARIABLE        = 0xB0,       /* M2 -> BB (CD write variable) */
    MSM_INT_DIRECT_WRITE_CD_BUFFER          = 0xB1,         /* M2 -> BB (CD write buffer) */
    MSM_INT_DIRECT_WRITE_CD_DONE            = 0xB2,           /* BB -> M2 (CD write done) */
    MSM_INT_DIRECT_WRITE_CD_FIRMWARE        = 0xB3,       /* M2 -> BB (CD firmware address) */
    MSM_INT_DIRECT_WRITE_CD_FIRMWARE_DONE   = 0xB4,  /* BB -> M2 (CD write firmware done) */
    MSM_INT_CD_ACCEPT_CMD_READY             = 0xB5,            /* M2 -> BB (CD ready to accept command) */
    MSM_INT_TAG_BLOCK_SAVE_COMPLETE         = 0xB6,        /* Notify the write data to tag blocks has been completed */
    MSM_INT_DIRECT_WRITE_AES_VARIABLE       = 0xB7,
    MSM_INT_DIRECT_WRITE_AES_BUFFER         = 0xB8,
    MSM_INT_DIRECT_WRITE_AES_DONE           = 0xB9,
    MSM_INT_CD_FIRMWARE_UPGRADE_DONE        = 0xBA,      /* M2 -> B1 */
    MSM_INT_AES_OPERATION_COMPLETE          = 0xBB,         /* M2 -> B1 */

    /* Dynamic Load */
    MSM_INT_DYNAMIC_LOAD_PACKAGE_VARIABLE   = 0xC0,  /* M2 -> BB (package load variable) */
    MSM_INT_DYNAMIC_LOAD_PACKAGE_SECTION    = 0xC1,   /* M2 -> BB (package load section start id) */
    MSM_INT_DYNAMIC_LOAD_PACKAGE_DONE       = 0xC2,      /* BB -> M2 (package load done) */

    /* Shared Data Memory */
    MSM_INT_SHM_SYSTEM_REQUEST              = 0xC3,          /* M3 -> B2 (copy M3 buffer to B2 buffer) */
    MSM_INT_SHM_SYSTEM_REQUEST_ACCEPTED     = 0xC4,         /* M3 -> B2 (copy B2 buffer to M3 buffer) */
    MSM_INT_SHM_COMMAND_REQUEST             = 0xC5,
    MSM_INT_SHM_COMMAND_REQUEST_ACCEPTED    = 0xC6,
    MSM_INT_SHM_BACKTRACE_REQUEST           = 0xC7,               /* B2 -> M3 */
    MSM_INT_SHM_SYSTEM_REQUEST_DONE         = 0xC8,
    MSM_INT_SHM_COMMAND_REQUEST_DONE        = 0xC9,

    /* GEM */
    MSM_INT_DIRECT_WRITE_EMU_VARIABLE       = 0xD0,       /* M2 -> BB (EMU write variable) */
    MSM_INT_DIRECT_WRITE_EMU_BUFFER         = 0xD1,         /* M2 -> BB (EMU write buffer) */
    MSM_INT_DIRECT_WRITE_EMU_DONE           = 0xD2,           /* BB -> M2 (EMU write done) */

    // Storage drive error log
    MSM_INT_STORAGE_ERR_LOG                 = 0xF0,

} MSMIntCause_e;

typedef enum MSM_SEVERITY_LEVEL_e
{
    MSM_SEVERITY_WARNING = 0x00,
    MSM_SEVERITY_TOLERABLE_ERR = 0x01,
    MSM_SEVERITY_FATAL_ERR = 0x02,
} MSM_SEVERITY_LEVEL;

typedef enum MSM_HWSTAT_IDX_e
{
    MSM_HWSTAT_CHKSUM   = 0x00,
    MSM_HWSTAT_SD       = 0x01,
    MSM_FAT_CHECK_M     = 0x02,
    MSM_FAT_CHECK_U     = 0x03
} MSM_HWSTAT_IDX;

typedef enum MSM_HWSTAT_SD_IDX_e
{
    MSM_SD_CORRUPT_WARNING = 0x01,
    MSM_FAT_CORRECT_M      = 0x02,
    MSM_FAT_INCORRECT_M    = 0x03
} MSM_HWSTAT_SD_IDX;


typedef enum MSMErrcode_e_
{
    /* Common   (0x0000 ~ 0x0FFF) */
    MSMERR_OK = 0x0000,
    MSMERR_FALSE = 0x0001,
    MSMERR_OUT_OF_MEMORY = 0x0002,
    MSMERR_PARAMETER_NOT_VALID = 0x0003,
    MSMERR_EOF = 0x0004,
    MSMERR_FUNC_NOT_IMPL = 0x0005,
    MSMERR_FILE_NOT_EXIST = 0x0006,
    MSMERR_OPEN_FILE_FAILED = 0x0007,
    MSMERR_REJECT = 0x0008,
    MSMERR_SDCARD_NOT_DETECTED = 0x0009,
    MSMERR_NO_CHANNEL = 0x000a,
    MSMERR_MANAGE_RETURN = 0x000b,
    MSMERR_CMD_ACCEPTED = 0x000c,
    MSMERR_ADD_BUFFER_DONE = 0x000d,
    MSMERR_BOUNDARY = 0x000e,
    MSMERR_INIT_FUNC_PLUGIN_FAIL = 0x000f,
    //MSMERR_MIDI_FILESIZE_TOO_BIG = 0x000f,
    MSMERR_SD_MOUNT_FAIL         = 0x0010,
    MSMERR_SD_UMOUNT_FAIL        = 0x0011,
    MSMERR_MOUNT_FAIL            = 0x0010,
    MSMERR_UMOUNT_FAIL           = 0x0011,
    MSMERR_SD_INIT_FAIL          = 0x0012,
    MSMERR_SD_RESOURCE_BUSY_BB   = 0x0013,
    MSMERR_SD_RESOURCE_BUSY_M2   = 0x0014,
    MSMERR_RESOURCE_BUSY_BB      = 0x0013,
    MSMERR_RESOURCE_BUSY_M2      = 0x0014,
    MSMERR_SD_NO_SD              = 0x0015,
    MSMERR_SD_MOUNT_ALREADY      = 0x0016,
    MSMERR_SD_UMOUNT_ALREADY     = 0x0017,
    MSMERR_MOUNT_ALREADY         = 0x0016,
    MSMERR_UMOUNT_ALREADY        = 0x0017,
    MSMERR_SD_CORRUPT            = 0x0018,
    MSMERR_NAND_INIT_FAIL        = 0x0019,
    MSMERR_FILE_CORRUPT          = 0x0020,
    MSMERR_NETWORK_OPEN_FAIL     = 0x0021,
    MSMERR_DISCONT               = 0x0022,

    /* CAM  (0x1000 ~ 0x1FFF) */
    MSMERR_SENSOR_NOT_DETECTED = 0x1001,
    MSMERR_AF_FAIL = 0x1002,

    /* AUD  (0x2000 ~ 0x2FFF) */
    MSMERR_AUD_NONE = 0x2000,
    MSMERR_AUD_RINGDATA_RANGE_ERR = 0x2001,
    MSMERR_AUD_PLAYREC_MODE_NOT_EXIST = 0x2002,
    MSMERR_AUD_RINGDATA_NOT_EXIST = 0x2003,
    MSMERR_AUD_TX_RESET = 0x2004,
    MSMERR_AUD_TX_UNDERFLOW = 0x2005,
    MSMERR_AUD_TX_FULL = 0x2006,
    MSMERR_AUD_TX_ADDED_SAMPLES_OVER = 0x2007,
    MSMERR_AUD_RX_RESET = 0x2008,
    MSMERR_AUD_RX_OVERFLOW = 0x2009,
    MSMERR_AUD_RX_OVERFLOW_CHGSAMPLE_OK = 0x200a,
    MSMERR_AUD_RX_EMPTY = 0x200b,
    MSMERR_AUD_RX_REMOVED_SAMPLES_OVER = 0x200c,
    MSMERR_AUD_DATA_NOT_EXIST = 0x200d,
    MSMERR_AUD_UNKNOW = 0x200e,
    MSMERR_AUD_INIT_FAIL = 0x200f,
    MSMERR_AUD_DECODER_OPEN_FAIL = 0x2010,
    MSMERR_AUD_TX_NOT_DEADY = 0x2011,

    /* SBC  */
    MSMERR_SBCSTREAM_DONE = 0x2100,
    MSMERR_SBCSTREAM_FULL = 0x2101,
    MSMERR_SBCSTREAM_EMPTY = 0x2102,

    //MSMERR_WAV_HEADERPARSER_ERR = 0x2103,
    //MSMERR_WAV_FORMAT_UNSUPPORT = 0x2104,
    MSMERR_AUD_SCMD_REJECT = 0x2105,

    /* IP   (0x3000 ~ 0x3FFF) */

    /* DISP (0x4000 ~ 0x4FFF) */
    MSMERR_BMP_NOT_BMPFILE = 0x4000,
    MSMERR_BMP_BADDEPTH    = 0x4001,

    MSMERR_JPD_NOT_JPGFILE = 0x4100,
    MSMERR_JPD_NOT_SUPP_16BIT_QT = 0x4101,
    MSMERR_JPD_NOT_SUPP_RESTART_MARKER = 0x4102,
    MSMERR_JPD_NOT_SUPP_PRECISION = 0x4103,
    MSMERR_JPD_NOT_SUPP_RESOLUTION = 0x4104,
    MSMERR_JPD_NOT_SUPP_IMG_FORMAT = 0x4105,
    MSMERR_JPD_NO_SOS_MARKER = 0x4106,
    MSMERR_JPD_NOT_SUPP_PROGRESSIVE = 0x4107,
    MSMERR_JPD_NOT_SUPP_DISP_WIDTH = 0x4108,
    MSMERR_JPD_EXIF_HEADER_ERR = 0x4109,
    MSMERR_JPD_EXIF_THUMB_SIZE_ERR = 0x410a,
    MSMERR_JPD_EXIF_THUMB_DEC_ERR = 0x410b,
    MSMERR_JPD_EXIF_THUMB_FMT_ERR = 0x410c,
    MSMERR_JPD_EXIF_NO_THUMB = 0x410d,
    MSMERR_JPD_EXIF_SIZE_ERR = 0x410e,
    MSMERR_JPD_VLD_ERR = 0x410f,
    MSMERR_JPD_EXCEED_QUANTIAZTION_NUM = 0x4110,
    MSMERR_JPD_EXCEED_HUFFMAN_NUM = 0x4111,
    MSMERR_JPD_NOT_SUPP_IDCT = 0x4112,
    MSMERR_JPD_OPEN_FILE_FAIL = 0x4113,
    MSMERR_JPD_HWVLD_ECS_ERR = 0x4114,
    MSMERR_JPD_HWVLD_RST_ERR = 0x4115,
    MSMERR_JPD_HWVLD_UNKNOW_ERR = 0x4116,
    MSMERR_JPD_HWVLD_BITSTREAM_ERR = 0x4117,
    MSMERR_JPD_ICP_NOT_SUPP_SCALE_UP= 0x4118,
    MSMERR_JPD_NOT_SUPP_DISP_HEIGHT = 0x4119,
    MSMERR_JPD_2_BB_FAIL = 0x411a,
    MSMERR_JPD_2_ZOOM_IN_FAIL = 0x411b,
    MSMERR_JPD_2_ZOOM_OUT_FAIL = 0x411c,
    MSMERR_JPD_OUTPUT_RESOLUTION_MISMATCH = 0x411d,
    MSMERR_JPD_ICP_LINE_COUNT_FAIL = 0x411e,
    MSMERR_JPD_HWVLD_TIME_OUT = 0x411f,

    MSMERR_JPGD_BAD_DHT_COUNTS              = 0x4130,
    MSMERR_JPGD_BAD_DHT_INDEX               = 0x4131,
    MSMERR_JPGD_BAD_DHT_MARKER              = 0x4132,
    MSMERR_JPGD_BAD_DQT_MARKER              = 0x4133,
    MSMERR_JPGD_BAD_DQT_TABLE               = 0x4134,
    MSMERR_JPGD_BAD_PRECISION               = 0x4135,
    MSMERR_JPGD_BAD_HEIGHT                  = 0x4136,
    MSMERR_JPGD_BAD_WIDTH                   = 0x4137,
    MSMERR_JPGD_TOO_MANY_COMPONENTS         = 0x4138,
    MSMERR_JPGD_BAD_SOF_LENGTH              = 0x4139,
    MSMERR_JPGD_BAD_VARIABLE_MARKER         = 0x413a,
    MSMERR_JPGD_BAD_DRI_LENGTH              = 0x413b,
    MSMERR_JPGD_BAD_SOS_LENGTH              = 0x413c,
    MSMERR_JPGD_BAD_SOS_COMP_ID             = 0x413d,
    MSMERR_JPGD_W_EXTRA_BYTES_BEFORE_MARKER = 0x413e,
    MSMERR_JPGD_NO_ARITHMITIC_SUPPORT       = 0x413f,
    MSMERR_JPGD_UNEXPECTED_MARKER           = 0x4140,
    MSMERR_JPGD_NOT_JPEG                    = 0x4141,
    MSMERR_JPGD_UNSUPPORTED_MARKER          = 0x4142,
    MSMERR_JPGD_BAD_DQT_LENGTH              = 0x4143,
    MSMERR_JPGD_TOO_MANY_BLOCKS             = 0x4144,
    MSMERR_JPGD_UNDEFINED_QUANT_TABLE       = 0x4145,
    MSMERR_JPGD_UNDEFINED_HUFF_TABLE        = 0x4146,
    MSMERR_JPGD_NOT_SINGLE_SCAN             = 0x4147,
    MSMERR_JPGD_UNSUPPORTED_COLORSPACE      = 0x4148,
    MSMERR_JPGD_UNSUPPORTED_SAMP_FACTORS    = 0x4149,
    MSMERR_JPGD_DECODE_ERROR                = 0x414a,
    MSMERR_JPGD_BAD_RESTART_MARKER          = 0x414b,
    MSMERR_JPGD_ASSERTION_ERROR             = 0x414c,
    MSMERR_JPGD_BAD_SOS_SPECTRAL            = 0x414d,
    MSMERR_JPGD_BAD_SOS_SUCCESSIVE          = 0x414e,
    MSMERR_JPGD_STREAM_READ                 = 0x414f,
    MSMERR_JPGD_NOTENOUGHMEM                = 0x4150,
    MSMERR_SCL_READY_FAIL                   = 0x4151,

    /* REC  (0x5000 ~ 0x5FFF) */
    MSMERR_JPE_FAIL = 0x5000,
    MSMERR_JPE_IBUFOV = 0x5001,
    MSMERR_JPE_OUTOFDISK = 0x5002,
    MSMERR_JPE_REDO = 0x5003,
    MSMERR_CREATE_FILE_ERR = 0x5004,
    MSMERR_JPE_TIMEOUT = 0x5005,
    MSMERR_JPE_NOT_SUPP_RESOLUTION = 0x5006,

    /* REC  (notification return: 0x5100 ~ 0x51FF) */
    MSMERR_REC_START = 0x5100,
    MSMERR_REC_STOP_NORMAL = 0x5101,
    MSMERR_REC_STOP_REACH_TIME_LIMIT = 0x5102,
    MSMERR_REC_STOP_REACH_SIZE_LIMIT = 0x5103,
    MSMERR_REC_STOP_SPACE_FULL = 0x5104,
    MSMERR_REC_SAVE_FILE_COMPLETE = 0x5105,
    MSMERR_REC_PLAY_SHUTTER_SOUND = 0x5106,
    MSMERR_REC_SINGLE_CPATURE = 0x5107,
    MSMERR_REC_STOP_WRITE_ERROR = 0x5108,
    MSMERR_REC_STOP_ABORTED = 0x5109,

    /*REC (QRCODE) */
    MSMERR_QRCODE_DEC_ERR = 0x510b,
    MSMERR_QRCODE_RS_ERR = 0x510c,
    MSMERR_QRCODE_NOT_SUPPORT = 0x510d,
    MSMERR_QRCODE_TIMEOUT = 0x510e,

    /* REC Muxer related part (0x5200~0x53FF) */
    MSMERR_MUX_OPEN_FAILED = 0x5200,
    MSMERR_MUX_CREATE_VDO_TRAK_FAILED = 0x5201,
    MSMERR_MUX_CREATE_ADO_TRAK_FAILED = 0x5202,
    MSMERR_MUX_CREATE_VDO_ATM_FAILED = 0x5203,
    MSMERR_MUX_CREATE_ADO_DAT_FAILED = 0x5204,
    MSMERR_MUX_VDO_WRITE_FAILED = 0x5205,
    MSMERR_MUX_ADO_WRITE_FAILED = 0x5206,
    MSMERR_MUX_CLOSE_FAILED = 0x5207,
    /* REC Video related part (0x5400~0x55FF) */
    MSMERR_REC_HW_INIT_FALIED = 0x5400,
    MSMERR_REC_HW_ENC_FALIED = 0x5401,
    MSMERR_REC_MUXBUF_OVERFLOW = 0x5402,
    MSMERR_REC_SD_SPACE_FULL = 0x5403,
    MSMERR_REC_VDO_DIMENSION = 0x5404,
    MSMERR_REC_AMR_LATE2WRITE = 0x5405,
    MSMERR_REC_NO_ENOUGH_PCM = 0x5406,
    MSMERR_REC_PCM_OVERFLOW = 0x5407,
    MSMERR_REC_VLCBUF_OVERFLOW = 0x5408,
    MSMERR_REC_VDO_LATE2WRITE = 0x5409,
    MSMERR_REC_SCL1_NOTREADY = 0x540A,
    /* REC JPE related part (0x5600~0x57FF) */
    /* REC Audio related part (0x5800~0x59FF) */
    MSMERR_REC_NAND_SPACE_FULL = 0x5800,

    /* USB  (0x6000 ~ 0x6FFF) */

    /* FS   (0x7000 ~ 0x7FFF) */
    MSMERR_DIR_NOTEMPTY = 0x7000,
    MSMERR_DIR_NOT_EXIST = 0x7001,
    MSMERR_CAN_NOT_DELETE_FILE = 0x7002,
    MSMERR_NO_OPEN_FILE = 0x7003,
    MSMERR_NO_FILE_HANDLE = 0x7004,
    MSMERR_ERROR_FILE_HANDLE = 0x7005,
    MSMERR_FILE_HANDLE_CORRUPTED = 0x7006,
    MSMERR_FILENAME_LENGTH_ERROR = 0x7007,
    MSMERR_FILENAME_ERROR = 0x7008,
    MSMERR_FILE_EXIST = 0x7009,
    MSMERR_COPY_BUSY = 0x700A,
    MSMERR_FILE_ABORT_READY = 0x700B,
    MSMERR_DISK_FULL = 0x700C,
    MSMERR_FILE_WRITE_ERROR = 0x700D,
    MSMERR_FILE_SAVE_SD_ERROR = 0x700E,
    MSMERR_FILE_SAVE_SD_COMPLETE = 0x700F,

    MSMERR_COPY_START = 0x7010,
    MSMERR_COPY_ABORT = 0x7011,
    MSMERR_COPY_END = 0x7012,

    //MSMERR_ENOENT   =   0x7013,     //no such entry
    MSMERR_NOT_DIR  =   0x7014,
    MSMERR_NOT_FILE =   0x7015,
    MSMERR_EINVAL   =   0x7016,     //Invalid argument
    MSMERR_FS_REJECT =  0x7017,
    MSMERR_FS_RECOVERY =  0x7018,

    /* GE   (0x8000 ~ 0x8FFF) */

    /* MP   (0x9000 ~ 0x9FFF) */
    /* MP thread common part (0x9000~0x90FF) */
    MSMERR_FORMAT_NOT_SUPPORT = 0x9000,
    MSMERR_PLAY_SEEK_ERROR = 0x9001,
    MSMERR_PLAY_SEEK_OVER_FILE_SIZE = 0x9002,
    MSMERR_PLAY_B2_MALLOC_FAIL = 0x9003,

    /* MP Notification part (0x9100~0x91FF) */
    //MSMERR_PLAY_START = 0x9100,
    MSMERR_PLAY_STOP = 0x9101,
    MSMERR_PLAY_SEEK_COMPLETE = 0x9102,
    //MSMERR_PLAY_PAUSE = 0x9103,
    //MSMERR_PLAY_RESUME = 0x9104,
    MSMERR_PLAY_END = 0x9105,
    MSMERR_PLAY_STREAMS_END = 0x9107,
    //MSMERR_PLAY_SEEKING = 0x910b,

    /* MDTV related part (0x9110~0x912F) */
    MSMERR_BRIDGE_ESTABILISH_COMPLETE = 0x9110,
    MSMERR_MDTV_SEARCH_FREQUENCY_COMPLETE = 0x9111,
    MSMERR_MDTV_SET_FREQUENCY_COMPLETE = 0x9112,
    MSMERR_MDTV_SET_CHANNEL_COMPLETE = 0x9113,//TBD
    MSMEER_MDTV_RECORD_START = 0x9114,
    MSMEER_MDTV_RECORD_STOP = 0x9115,
    MSMERR_MDTV_SNAPSHOT_COMPLETE = 0x9116,
    MSMERR_MDTV_CANCEL_COMPLETE = 0x9117,
    MSMEER_MDTV_TIMESHIFT_START = 0x9118,
    MSMEER_MDTV_TIMESHIFT_STOP = 0x9119,

    /* MDTV error related part (0x9130~0x914F) */
    MSMERR_MDTV_SEARCH_FREQUENCY_FAIL = 0x9130,
    MSMERR_MDTV_SET_FREQUENCY_FAIL = 0x9131,
    MSMEER_MDTV_RECORD_FAIL = 0x9132,
    MSMERR_MDTV_SNAPSHOT_FAIL = 0x9133,
    MSMEER_MDTV_TIMESHIFT_FAIL = 0x9134,


    /* MP Dmxer related part (0x9200~0x93FF) */
    MSMERR_DMX_OPEN_FAILED = 0x9200,
    MSMERR_DMX_READ_ATOM_FAILED = 0x9201,
    MSMERR_DMX_VDO_IDX_INVLD = 0x9202,
    MSMERR_DMX_VDO_READ_INVLD = 0x9203,
    MSMERR_DMX_VDO_BUF_OVERFLOW = 0x9204,
    MSMERR_DMX_EOF = 0x9205,
    MSMERR_DMX_RETRY = 0x9206,
    MSMERR_DMX_NO_INPUT_SIGNAL = 0x9207,
    MSMERR_DMX_READ_ATOM_FINISHED = 0x9208,
    MSMERR_DMX_LICENSE_NOTEXIST  = 0x9209,
    MSMERR_DMX_LICENSE_MISMATCH  = 0x920a,
    MSMERR_DMX_PASSWORD_MISMATCH = 0x920b,
    MSMERR_DMX_GET_OPTIONAL_DATA_FAILED = 0x920c,
    MSMERR_DMX_READ_INVLD = 0x920d,
    /* MP Video related part (0x9400~0x95FF) */
    MSMERR_VDO_END_SEQ = 0x9400,
    MSMERR_VDO_NO_START_CODE = 0x9401,
    MSMERR_VDO_MB_HDR_INVLD = 0x9402,
    MSMERR_VDO_MCBPC_INVLD = 0x9403,
    MSMERR_VDO_CBPY_INVLD = 0x9404,
    MSMERR_VDO_COEF_INVLD = 0x9405,
    MSMERR_VDO_HUF_CODE_INVLD = 0x9406,
    MSMERR_VDO_DC_INVLD = 0x9407,
    MSMERR_VDO_AC_INVLD = 0x9408,
    MSMERR_VDO_WIDTH_INVLD = 0x9409,
    MSMERR_VDO_OPEN_FAIL = 0x940a,
    MSMERR_VDO_ECS_ERR = 0x940b,
    MSMERR_VDO_RESOURCE_LOST = 0x940c,
    MSMERR_VDO_MSTR_M2HW_H263_CLIP = 0x9420,
    MSMERR_VDO_MSTR_SW_MP4SP_CLIP = 0x9421,
    MSMERR_VDO_MSTR_SW_H264_CLIP = 0x9422,
    MSMERR_VDO_MSTR_SW_RM_CLIP = 0x9423,
    MSMERR_VDO_MSTR_HW_MP2V_CLIP = 0x9424,
    MSMERR_VDO_MSTR_SW_FLV_CLIP = 0x9425,
    MSMERR_VDO_MSTR_HW_FLV_CLIP = 0x9426,
    /* MP Mp3 related part (0x9600~0x97FF) */
    MSMERR_ID3_NODATA = 0x9600,
    MSMERR_MP3_DECODE_ERR = 0x9601,
    MSMERR_MP3_CLOSE_ERR = 0x9602,
    MSMERR_LYRICS_NODATA = 0x9603,
    MSMERR_LYRICS_LYRICFILE_ERR = 0x9604,
    MSMERR_AUD_HW_ERR = 0x9605,
    /* MP AMR/ACC related part (0x9800~0x99FF) */
    MSMERR_AMR_DEC_INIT_FAIL = 0x9800,
    MSMERR_AMR_DEC_OPEN_FAIL = 0x9801,
    MSMERR_FILE_READ_ERR = 0x9802,
    MSMERR_AACDecode_ERR = 0x9803,
    MSMERR_AAC_OpenFileErr = 0x9804,
    MSMERR_Aud_TxDrvInitErr = 0x9805,
    MSMERR_AES_DEC_KEY_ERR = 0x9806,
    MSMERR_Decode_ERR = 0x9807,

    /* MP MIDI/WAV related part (0x9A00~0x9BFF) */
    MSMERR_MIDI_DEC_ERR = 0x9A00,
    MSMERR_MIDI_OPENFILE_FAILED = 0x9A01,
    MSMERR_MIDI_FILESIZE_TOO_BIG = 0x9A02,
    MSMERR_MIDI_FORMAT_ERR= 0x9A03,
    MSMERR_MIDI_WAIT_STREAM_FAIL = 0x9A04,
    MSMERR_MIDI_TABLE_ERR = 0x9A05,
    MSMERR_MIDI_GETSTREAMSIZE_ERR = 0x9A06,
    MSMERR_MIDI_EQ_ERR = 0x9A07,
    MSMERR_WAV_HEADERPARSER_ERR = 0x9B00,
    MSMERR_WAV_FORMAT_UNSUPPORT = 0x9B01,
    MSMERR_WAV_PEQ_ERR = 0x9B02,

    MSMERR_WMADecode_ERR = 0x9B05,

    MSMERR_TAG_BLOCK_SAVE_ERROR = 0xA000,
    MSMERR_TAG_BLOCK_SAVE_COMPLETE = 0xA001,
    MSMERR_AES_OPERATION_ERROR = 0xA002,
    MSMERR_AES_OPERATION_COMPLETE = 0xA003,


    //MP Post-Processing related part (0x9C00~0x9CFF)
    MSMERR_POSTPROC_USR_PEQ_ERR      = 0x9C00,
    MSMERR_POSTPROC_SPK_PEQ_ERR      = 0x9C01,
    MSMERR_POSTPROC_LIMITER_PEQ_ERR  = 0x9C02,
    MSMERR_POSTPROC_SURROUND_PEQ_ERR = 0x9C03,
    MSMERR_POSTPROC_DPGA_ERR         = 0x9C04,
    MSMERR_POSTPROC_ADJUSTCLOCK_ERR  = 0x9C05,

    // SRC Main IP Part(0x9C80~0x9CFF)
    MSMERR_SRC_INIT_ERR                 = 0x9C80,
    MSMERR_SRC_PROC_ERR                 = 0x9C81,
    MSMERR_SRC_CLOSE_ERR                = 0x9C82,
    // SRC Memory Layout Part
    MSMERR_SRC_OVEROUTPUTBUFSIZE_ERR    = 0x9C83,
    MSMERR_SRC_OUTBUFFERSIZEINVALID_ERR = 0x9C84,
    // SRC Control Part
    MSMERR_SRC_GETOUTSAMPLERATE_ERR     = 0x9C85,
    MSMERR_SRC_GETOUTSAMPLESIZE_ERR     = 0x9C86,
    MSMERR_SRC_SETPOWER_ERR             = 0x9C87,
    MSMERR_SRC_SETSAMPLERATE_ERR        = 0x9C88,
    MSMERR_SRC_SETRULE_ERR              = 0x9C89,

    /* MP FM/RDS related part (0x9D00~0x9DFF) */
    MSMERR_FMRX_INVLD_INPUTFREQ  = 0x9D00,
    MSMERR_FMRX_INVLD_OUTPUTFREQ = 0x9D01,
    MSMERR_FMRX_RFLO_UNLOCK      = 0x9D02,
    MSMERR_FMRX_BBCARRY_UNLOCK   = 0x9D03,

    /* Boundary  (0xF000 ~ 0xFFFF) */

} MSMErrcode_e;


typedef enum MSMNotification_e_
{
    /* Common */
    MSMEVENT_INITREADY = 0x0000,
    MSMEVENT_ACCEPT_CMD_READY,
    MSMEVENT_MCU_RESET,
    MSMEVENT_COMMAND_ERROR,
    MSMEVENT_WATCHDOG_TIMEOUT,
    MSMEVENT_SD_INSERT,
    MSMEVENT_SD_REMOVE,
    MSMEVENT_USB_PC_CONNECT,
    MSMEVENT_USB_PC_REMOVE,
    MSMEVENT_USB_REQUEST,
    MSMEVENT_CMD_ACCEPTED,
    MSMEVENT_DIRECT_WRITE_VARIABLE,
    MSMEVENT_DIRECT_WRITE_BUFFER,
    MSMEVENT_FRAME_BUFFER_READY,

    /* Media Playback */
    MSMEVENT_PLAY_SATE_CHANGE,
    MSMEVENT_PLAY_POSITION_UPDATE,
    MSMEVENT_PLAY_ERROR,
    MSMEVENT_BITRATE_CHANGE,
    MSMEVENT_LYRICS_UPDATE,

    /* Recording */
    MSMEVENT_RECORD_STATE_CHANGE,
    MSMEVENT_RECORD_SAVE_FILE_COMPLETE,
    MSMEVENT_RECORD_ERROR,
    MSMEVENT_RECORD_POSITION_UPDATE,

    MSMEVENT_NUM,
    MSMEVENT_SYS_CATEGORY,
    MSMEVENT_PLAYBACK_CATEGORY,
    MSMEVENT_RECORD_CATEGORY,
    MSMEVENT_ALL_TYPE,
    MSMEVENT_INVALID

} MSMNotification_e;


#endif /* MSMINTCAUSE_H */