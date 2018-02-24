//<MStar Software>
//***********************************************************************************
//MStar Software
//Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
//All software, firmware and related documentation herein (“MStar Software”) are intellectual property of MStar Semiconductor, Inc. (“MStar”) and protected by law, including, but not limited to, copyright law and international treaties.  Any use, modification, reproduction, retransmission, or republication of all or part of MStar Software is expressly prohibited, unless prior written permission has been granted by MStar.
//By accessing, browsing and/or using MStar Software, you acknowledge that you have read, understood, and agree, to be bound by below terms (“Terms”) and to comply with all applicable laws and regulations:
//
//1. MStar shall retain any and all right, ownership and interest to MStar Software and any modification/derivatives thereof.  No right, ownership, or interest to MStar Software and any modification/derivatives thereof is transferred to you under Terms.
//2. You understand that MStar Software might include, incorporate or be supplied together with third party’s software and the use of MStar Software may require additional licenses from third parties.  Therefore, you hereby agree it is your sole responsibility to separately obtain any and all third party right and license necessary for your use of such third party’s software.
//3. MStar Software and any modification/derivatives thereof shall be deemed as MStar’s confidential information and you agree to keep MStar’s confidential information in strictest confidence and not disclose to any third party.
//4. MStar Software is provided on an “AS IS” basis without warranties of any kind. Any warranties are hereby expressly disclaimed by MStar, including without limitation, any warranties of merchantability, non-infringement of intellectual property rights, fitness for a particular purpose, error free and in conformity with any international standard.  You agree to waive any claim against MStar for any loss, damage, cost or expense that you may incur related to your use of MStar Software.
//   In no event shall MStar be liable for any direct, indirect, incidental or consequential damages, including without limitation, lost of profit or revenues, lost or damage of data, and unauthorized system use.  You agree that this Section 4 shall still apply without being affected even if MStar Software has been modified by MStar in accordance with your request or instruction for your use, except otherwise agreed by both parties in writing.
//5. If requested, MStar may from time to time provide technical supports or services in relation with MStar Software to you for your use of MStar Software in conjunction with your or your customer’s product (“Services”).  You understand and agree that, except otherwise agreed by both parties in writing, Services are provided on an “AS IS” basis and the warranty disclaimer set forth in Section 4 above shall apply.
//6. Nothing contained herein shall be construed as by implication, estoppels or otherwise: (a) conferring any license or right to use MStar name, trademark, service mark, symbol or any other identification; (b) obligating MStar or any of its affiliates to furnish any person, including without limitation, you and your customers, any assistance of any kind whatsoever, or any information; or (c) conferring any license or right under any intellectual property right.
//7. These terms shall be governed by and construed in accordance with the laws of Taiwan, R.O.C., excluding its conflict of law rules.  Any and all dispute arising out hereof or related hereto shall be finally settled by arbitration referred to the Chinese Arbitration Association, Taipei in accordance with the ROC Arbitration Law and the Arbitration Rules of the Association by three (3) arbitrators appointed in accordance with the said Rules.  The place of arbitration shall be in Taipei, Taiwan and the language shall be English.
//   The arbitration award shall be final and binding to both parties.
//
//本處所有軟體、韌體及相關文檔(下稱「MStar Software」)均為MStar Semiconductor, Inc. (下稱「MStar」)之智慧財產權並為相關法律(包括但不限於著作權法及國際條約)所保護，任何未經MStar事前書面野i之使用、修改、重製、傳送或公開均為禁止的。
//一旦您進入、瀏覽或使用MStar Software，您即聲明您已詳讀、了解並同意為下列條款（下稱「本條款」）所拘束並將遵守相關法規之規定：
//
//1.	MStar仍保有MStar Software及其修改物／衍生物之任何與全部的權利、所有權及利益，您並未因本條款而取得關於MStar Software及其修改物／衍生物之任何與全部的權利、所有權及利益。
//2.	您了解MStar Software可能含有或結合有屬於第三人之軟體或係與第三人之軟體一併提供，而使用MStar Software可能需另行向第三人取得授權，因此您同意您將自行負責向此等第三人取得授權以合法使用MStar Software。
//3.	MStar Software及其修改物／衍生物應被視為MStar的機密資訊，您同意將以最機密保存MStar的機密資訊且不將之揭露予任何第三人。
//4.	MStar Software係「依現狀」所提供而無任何擔保。MStar於此否認對MStar Software提供任何擔保，包括但不限於可商品化、不侵權、符合特定使用目的、無瑕疵及符合任何國際標準之擔保。您同意將不會對MStar主張您因使用MStar Software所生之任何損失、損害、費用或支出。於任何情況下，MStar對於直接的、間接的、附帶的或必然的損害均不負責任，包括但不限於利潤營收損失、資料之毀損遺失及系統被未經授權使用。您並同意，除雙方另有書面協議外，即使MStar曾依您的要求或指示而修改MStar Software，本第4條之規定仍繼續適用而不受影響。
//5.	如經要求，MStar不時將提供技術支援或服務予您，以利您的產品可以與MStar Software一同使用(下稱「服務」)，您了解並同意，除雙方另有書面協議外，所有服務均係「以現狀」提供，第4條之不提供擔保相關規定亦應適用之。
//6.	本條款之任何條款不得被解釋為(無論依默示、禁反言原則或其它)：(a) 授予任何權利以使用MStar之名稱、商標、服務標章、符號或其它識別圖像；(b)課予MStar或其關係企業提供予任何人(包括但不限於您及您的客戶)任何形式的協助或資訊的義務；或(c) 授予任何智慧財產權。
//7.	本條款應依中華民國法律為準據法(不含其衝突法則)。任何基於本條款所生或與本條款相關之爭議最終應依中華民國仲裁法及該協會之仲裁規則解決，仲裁應由3名仲裁人以英文在台灣台北進行，仲裁人應依中華民國仲裁協會之仲裁規則選出，仲裁判斷應為終局的且對雙方均有拘束力。
//***********************************************************************************
//<MStar Software>
//--------------------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------------------
//#include "common.h"

#include "MsCommon.h"
#include "MsOS.h"
#include "sysinfo.h"
#include "apiJPEG.h"
#include "verJPD.h"


unsigned int TARGET_LOGO_ADDR;
unsigned int TARGET_LOGO_SIZE;

int g_JpgPitch;
int g_JpgWidth;
int g_JpgHeight;

//-------------------------------------------------------------------------------------------------
//  Local Compiler Options
//-------------------------------------------------------------------------------------------------

//define jpd library
#define UTOPIA_JPD_OLD  1
#define UTOPIA_JPD_NEW  2
#define MS_JPD_API UTOPIA_JPD_NEW

//define slide show test
//#define SLIDE_SHOW_TEST

//-------------------------------------------------------------------------------------------------
// Local Defines
//-------------------------------------------------------------------------------------------------

#define JPEGBASEWIDTHMAX    1920
#define JPEGBASEHEIGHTMAX   1080
#define JPEGPROWIDTHMAX     1024
#define JPEGPROHEIGHTMAX    768

#define verJPD_DEBUG(x)     //x

#if defined(CHIP_T3) || defined(CHIP_T4) || defined(CHIP_T7) || defined(CHIP_JANUS) || defined(CHIP_U4)
#define VERJPD_EVENT_ALL    (E_JPEG_EVENT_DEC_DONE | E_JPEG_EVENT_DEC_ERROR_MASK | E_JPEG_EVENT_DEC_MRB_DONE | E_JPEG_EVENT_DEC_MWB_FULL)
#else
#define VERJPD_EVENT_ALL    (E_JPEG_EVENT_DEC_DONE | E_JPEG_EVENT_DEC_ERROR_MASK | E_JPEG_EVENT_DEC_MRB_DONE)
#endif

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_JPEG_IDLE = 0x01,
    E_JPEG_DECODE_ERR = 0x02,
    E_JPEG_DECODE_HEADER = 0x03,
    E_JPEG_DECODE_BEGIN = 0x04,
    E_JPEG_DECODE_DONE = 0x05,
    E_JPEG_WAITDONE = 0x06,
    E_JPEG_INIT = 0x07,
} EN_JPEG_DECODE_STATE;

typedef enum
{
    E_JPD_BASELINE_TEST     = 1,
    E_JPD_PROGRESSIVE_TEST,
    E_JPD_CMYK_TEST
} EN_JPEG_TEST;

typedef enum
{
    E_JPD_MAIN_DECODE       = 1,
    E_JPD_THUMBNAIL_DECODE
} EN_JPEG_DECODE_TYPE;

/// JPEG decoder file system
typedef struct JPD_FILE_FileSystem_s
{
    void ( *constructor )( struct JPD_FILE_FileSystem_s *structPtr );
    void ( *destructor )( struct JPD_FILE_FileSystem_s *structPtr );
    MS_BOOL (*open)( struct JPD_FILE_FileSystem_s *structPtr );
    void ( *close )( struct JPD_FILE_FileSystem_s *structPtr );
    MS_S32 (*read)( MS_U8 *Pbuf, MS_U32 max_bytes_to_read, MS_BOOL *Peof_flag,
        struct JPD_FILE_FileSystem_s *structPtr);//, MS_U8 Position);
    MS_BOOL ( *get_error_status )( struct JPD_FILE_FileSystem_s *structPtr);
    MS_BOOL ( *reset )( struct JPD_FILE_FileSystem_s *structPtr );
    MS_S32 ( *get_size )( struct JPD_FILE_FileSystem_s *structPtr );
    MS_BOOL eof_flag, error_flag;
} JPD_FILE_FileSystem_t, *PJPD_FILE_FileSystem_t;

//--------------------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------------------
MS_U8 u8BaseLineJPEG[2]={0};
MS_U8 u8ProgressiveJPEG[2]={0};

MS_U8 u8CmykJPEG[] = {};

//--------------------------------------------------------------------------------------------------
// Local Variables
//--------------------------------------------------------------------------------------------------
static EN_JPEG_DECODE_STATE g_state = E_JPEG_INIT;
static JPD_FILE_FileSystem_t _input_stream;
static PJPD_FILE_FileSystem_t _Pinput_stream = &_input_stream;
static MS_U32 u32ReadBuffVirAddr = 0;
static MS_U32 u32IntBuffVirAddr = 0;
static MS_U32 u32OutBuffVirAddr = 0;
//static MS_U16 u16ImageWidth = 0, u16ImageHeight = 0;
//static MS_U16 u16ImageOriWidth = 0, u16ImageOriHeight = 0;
//static MS_U16 u16ImageNonAlignWidth = 0, u16ImageNonAlignHeight = 0;
static MS_U16 u16ImageAlignPitch = 0, u16ImageAlignWidth = 0, u16ImageAlignHeight = 0;
//static MS_U16 u16ErrorCode = 0;
//static MS_U8 u8ScaleDownFactor = 0;
//static MS_BOOL bIsProgressive = FALSE;
//static MS_BOOL bThumbnailFound = FALSE;
//static MS_U8 u8DebugLevel = 0x0;

static MS_U8 *u8InputDataAddr = NULL;
static MS_U32 u32InputDataLength = 0;
static MS_U32 u32ReadPosition = 0;

static MS_S32 s32InitByteRead = 0;
static MS_BOOL u8EOF_flag = FALSE;

static JPEG_Info stJPEG_Info;
static JPEG_Status stJPEG_Status;
static const MSIF_Version *pu8JPEG_Ver;

#if defined(MSOS_ISR_SUPPORT)
static MS_U32 u32IsrCnt = 0;
static EN_JPEG_DECODE_STATUS _gDecodeStatus = E_DECODE_NONE;
static MS_U32 u32ISRtimeout = 0;
#endif

static JPEG_EXIF_DateTime _gEXIF_DateTime;
static JPEG_EXIF_Orientation _gEXIF_Orientation;

#ifdef SLIDE_SHOW_TEST
static MS_U8 slide_count = 0;
#endif

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------
static void verJPD_FILE_constructor(JPD_FILE_FileSystem_t *thisPtr);
static void verJPD_FILE_destructor(JPD_FILE_FileSystem_t *thisPtr);
static MS_BOOL verJPD_FILE_open(JPD_FILE_FileSystem_t *thisPtr);
static void verJPD_FILE_close(JPD_FILE_FileSystem_t *thisPtr);
static MS_S32 verJPD_FILE_read(MS_U8 *Pbuf, MS_U32 max_bytes_to_read, MS_BOOL *Peof_flag, JPD_FILE_FileSystem_t *thisPtr);
static MS_BOOL verJPD_FILE_get_error_status(JPD_FILE_FileSystem_t *thisPtr);
static MS_BOOL verJPD_FILE_reset(JPD_FILE_FileSystem_t *thisPtr);
static MS_S32 verJPD_FILE_get_size(JPD_FILE_FileSystem_t *thisPtr);
static void verJPD_InitFileSystem(void);
//static MS_S32 verJPD_FillHdrFunc(MS_U32 BufAddr, MS_U32 BufLength);
static MS_BOOL verJPD_PreLoadBuffer(JPEG_BuffLoadType u8MRBuffType);
static EN_JPEG_DECODE_STATUS verJPD_WaitDone(void);
static void verJPD_SetStatus(void);
static void verJPD_Init(EN_JPEG_TEST u8Source);
static void verJPD_StartDecode(EN_JPEG_DECODE_TYPE decode_type);
#if defined(MSOS_ISR_SUPPORT)
static void verJPD_ISR_CB(void);
static void verJPD_InterruptRequest(void);
#endif

#if defined(MSOS_TYPE_LINUX)
extern MS_BOOL MDrv_MMIO_MMAP(MS_U32 u32Virtualaddr, MS_U32 u32Virtualsize,MS_U32 *u32Baseaddr);
#endif
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//for file read
// APP need to provide his own I/O functions
static void verJPD_FILE_constructor(JPD_FILE_FileSystem_t *thisPtr)
{
    thisPtr->eof_flag = FALSE;
    thisPtr->error_flag = FALSE;
}

static void verJPD_FILE_destructor(JPD_FILE_FileSystem_t *thisPtr)
{
    thisPtr->close( thisPtr );
}

static MS_BOOL verJPD_FILE_open(JPD_FILE_FileSystem_t *thisPtr)
{
    thisPtr->close( thisPtr );
    thisPtr->eof_flag = FALSE;
    thisPtr->error_flag = FALSE;

    return TRUE;
}

static void verJPD_FILE_close(JPD_FILE_FileSystem_t *thisPtr)
{
    thisPtr->eof_flag = FALSE;
    thisPtr->error_flag = FALSE;
}

static MS_S32 verJPD_FILE_read(MS_U8 *Pbuf, MS_U32 max_bytes_to_read, MS_BOOL *Peof_flag, JPD_FILE_FileSystem_t *thisPtr)
{
    MS_U8* u8RequestDataAddr = 0;
    MS_S32 bytes_read = 0;
    MS_S32 i = 0;

    u8RequestDataAddr = Pbuf;

    verJPD_DEBUG(printf("verJPD_FILE_read,u8RequestDataAddr = 0x%lX, FilePosition = %lu, FileLength = %lu\n"
        , (MS_U32)u8RequestDataAddr, u32ReadPosition, u32InputDataLength));

    if (u32ReadPosition <= u32InputDataLength)
    {
        bytes_read = max_bytes_to_read;
        if ((u32ReadPosition + max_bytes_to_read) >= u32InputDataLength)
        {
            bytes_read = u32InputDataLength - u32ReadPosition;
            thisPtr->eof_flag = TRUE;
            *Peof_flag = TRUE;
        }

        for(i = 0; i < bytes_read; i++)
        {
            u8RequestDataAddr[i] = u8InputDataAddr[u32ReadPosition + i];
#if 0
            if(u8RequestDataAddr[i] != u8InputDataAddr[u32ReadPosition + i])
            {
                printf("Error read file.....i = %ld\n", i);
                bytes_read = -1;
                break;
            }
#endif
        }
        MsOS_FlushMemory();
    }
    else
    {
        thisPtr->eof_flag = TRUE;
        *Peof_flag = TRUE;
    }
    u32ReadPosition += bytes_read;
    verJPD_DEBUG(printf("verJPD_FILE_read, bytes_read = %lu\n", bytes_read));
    return bytes_read;
}

static MS_BOOL verJPD_FILE_get_error_status(JPD_FILE_FileSystem_t *thisPtr)
{
    return (thisPtr->error_flag);
}

static MS_BOOL verJPD_FILE_reset(JPD_FILE_FileSystem_t *thisPtr)
{
    thisPtr->error_flag = FALSE;
    thisPtr->eof_flag = FALSE;

    return TRUE;
}

static MS_S32 verJPD_FILE_get_size(JPD_FILE_FileSystem_t *thisPtr)
{
    MS_S32 size = 0;
    thisPtr = thisPtr;
    return size;
}

//--------------------------------------------------------------------------------------------------
static void verJPD_InitFileSystem(void)
{
    _Pinput_stream->constructor = verJPD_FILE_constructor;
    _Pinput_stream->destructor = verJPD_FILE_destructor;
    _Pinput_stream->open = verJPD_FILE_open;
    _Pinput_stream->close = verJPD_FILE_close;
    _Pinput_stream->read = verJPD_FILE_read;
    _Pinput_stream->get_error_status = verJPD_FILE_get_error_status;
    _Pinput_stream->reset = verJPD_FILE_reset;
    _Pinput_stream->get_size = verJPD_FILE_get_size;
}

#if 0
//--------------------------------------------------------------------------------------------------
static MS_S32 verJPD_FillHdrFunc(MS_PHYADDR BufAddr, MS_U32 BufLength)
{
    MS_S32 bytes_read = 0;
    MS_U32 buf_left = 0;
    MS_U32 bufVirAddr = MS_PA2KSEG1((MS_U32)BufAddr);
    verJPD_DEBUG(printf("verJPD_FillHdrFunc, BufAddr = %lu, bufVirAddr = %lu\n", BufAddr, bufVirAddr));
    do
    {
        bytes_read = _Pinput_stream->read((MS_U8 *)(bufVirAddr + buf_left), BufLength - buf_left, &u8EOF_flag, _Pinput_stream);

        if (bytes_read < 0)
        {
            return bytes_read;
        }

        buf_left += bytes_read;
    } while(( buf_left < BufLength ) && ( !u8EOF_flag ));
    MApi_JPEG_UpdateReadInfo(buf_left, u8EOF_flag);
    return buf_left;
}
#endif

//--------------------------------------------------------------------------------------------------
static MS_BOOL verJPD_PreLoadBuffer(JPEG_BuffLoadType u8MRBuffType)
{
    MS_S32 bytes_read = 0;
    MS_U32 buf_left = 0;
    MS_U32 u32RequestDataAddr, u32RequestDataSize;

    if(u8EOF_flag)
    {
        MApi_JPEG_ProcessEOF(u8MRBuffType);
        return TRUE;
    }

    u32RequestDataAddr = u32ReadBuffVirAddr;
    u32RequestDataSize = MAD_JPEG_READBUFF_LEN/2;//verJPD_READBUFF_LEN/2;

    if(u8MRBuffType == E_JPEG_BUFFER_HIGH)
    {
        u32RequestDataAddr += u32RequestDataSize;
    }

    do
    {
        bytes_read = _Pinput_stream->read((MS_U8 *)(u32RequestDataAddr + buf_left), u32RequestDataSize - buf_left, &u8EOF_flag, _Pinput_stream);

        if (bytes_read == -1)
        {
            MApi_JPEG_SetErrCode( E_JPEG_STREAM_READ );
            return FALSE;
        }

        buf_left += bytes_read;
    } while(( buf_left < u32RequestDataSize ) && ( !u8EOF_flag ));
    MApi_JPEG_UpdateReadInfo(buf_left, u8EOF_flag);
    if(buf_left > 0)
    {
        MApi_JPEG_SetMRBufferValid(u8MRBuffType);
    }
#if defined(MSOS_ISR_SUPPORT)
    else
    {
        if(E_JPEG_BUFFER_HIGH == u8MRBuffType)
            MApi_JPEG_SetJPDEventFlag(E_JPEG_EVENT_DEC_MRBH_DONE);
        else if(E_JPEG_BUFFER_LOW == u8MRBuffType)
            MApi_JPEG_SetJPDEventFlag(E_JPEG_EVENT_DEC_MRBL_DONE);
    }
#endif
    return TRUE;
}

//--------------------------------------------------------------------------------------------------
static EN_JPEG_DECODE_STATUS verJPD_WaitDone(void)
{
#if defined(MSOS_ISR_SUPPORT)
    if((u32ISRtimeout % 500) == 0)
    {
        JPEG_Event reg_val = MApi_JPEG_GetJPDEventFlag();
        reg_val = reg_val;
    }
    if(u32ISRtimeout++ > 10000 && _gDecodeStatus == E_DECODING)
    {
        verJPD_DEBUG(printf("verJPD_WaitDone : ISR Time OUT!!!\n"));
        _gDecodeStatus = E_DECODE_ERR;
    }
    return _gDecodeStatus;
#elif (MS_JPD_API == UTOPIA_JPD_OLD)
    EN_JPEG_DECODE_STATUS eDecodeStatus = E_DECODING;
    JPEG_Event reg_val = E_JPEG_EVENT_DEC_DONE;

    //For H/W bug, Check Vidx.
    if(E_JPEG_FAILED == MApi_JPEG_HdlVidxChk())
    {
        reg_val = E_JPEG_EVENT_DEC_ERROR_MASK;
    }
    else
    {
        reg_val = MApi_JPEG_GetJPDEventFlag();
    }

    if(E_JPEG_EVENT_DEC_DONE & reg_val)
    {
        verJPD_DEBUG(printf("Decode Done\n"));
        eDecodeStatus = E_DECODE_DONE;
    }
    else if(E_JPEG_EVENT_DEC_ERROR_MASK & reg_val)
    {
        verJPD_DEBUG(printf("Baseline decode error:\n"));
        // temp patch for protect JPD from writing to illegal memory
        //MApi_JPEG_Rst();
        eDecodeStatus = E_DECODE_ERR;
    }
    else if(E_JPEG_EVENT_DEC_MRB_DONE & reg_val)
    {
        JPEG_BuffLoadType PreLoadBuffType = E_JPEG_BUFFER_NONE;
        MApi_JPEG_GetStatus(&stJPEG_Status);
        switch(MApi_JPEG_GetBuffLoadType(&PreLoadBuffType))
        {
            case E_JPEG_OKAY:
                if(!verJPD_PreLoadBuffer(PreLoadBuffType))
                {
                    if(MApi_JPEG_GetErrorCode() == E_JPEG_STREAM_READ)
                        eDecodeStatus = E_STREAM_READ_ERR;
                    else
                        eDecodeStatus = E_DECODE_ERR;
                }
                else
                {
                    eDecodeStatus = E_DECODING;
                }
                break;
            case E_JPEG_FAILED:
                eDecodeStatus = E_DECODE_ERR;
                break;
            case E_JPEG_RETRY:
            default:
                eDecodeStatus = E_DECODING;
                break;
        }
    }
    else if(reg_val == 0)
    {
        eDecodeStatus = E_DECODING;
    }
    return eDecodeStatus;
#elif (MS_JPD_API == UTOPIA_JPD_NEW)
    EN_JPEG_DECODE_STATUS eDecodeStatus = E_DECODING;
    switch(MApi_JPEG_WaitDone())
    {
        case E_JPEG_DEC_DONE:
            verJPD_DEBUG(printf("Decode Done\n"));
            eDecodeStatus = E_DECODE_DONE;
            break;
        case E_JPEG_DEC_FAILED:
        case E_JPEG_DEC_RST_ERROR:
        case E_JPEG_DEC_BITSTREAM_ERROR:
            verJPD_DEBUG(printf("Baseline decode error\n"));
            eDecodeStatus = E_DECODE_ERR;
            break;
        case E_JPEG_DEC_MRBL_DONE:
            if(!verJPD_PreLoadBuffer(E_JPEG_BUFFER_LOW))
            {
                if(MApi_JPEG_GetErrorCode() == E_JPEG_STREAM_READ)
                    eDecodeStatus = E_STREAM_READ_ERR;
                else
                    eDecodeStatus = E_DECODE_ERR;
            }
            else
            {
                eDecodeStatus = E_DECODING;
            }
            break;
        case E_JPEG_DEC_MRBH_DONE:
            if(!verJPD_PreLoadBuffer(E_JPEG_BUFFER_HIGH))
            {
                if(MApi_JPEG_GetErrorCode() == E_JPEG_STREAM_READ)
                    eDecodeStatus = E_STREAM_READ_ERR;
                else
                    eDecodeStatus = E_DECODE_ERR;
            }
            else
            {
                eDecodeStatus = E_DECODING;
            }
            break;
        case E_JPEG_DEC_DECODING:
        default:
            eDecodeStatus = E_DECODING;
            break;
    }
    return eDecodeStatus;
#endif
}

//--------------------------------------------------------------------------------------------------
static void verJPD_SetStatus(void)
{
    if( g_state == E_JPEG_DECODE_DONE )
    {
        verJPD_DEBUG(printf("verJPD_SetStatus:E_JPEG_DECODE_DONE\n"));
        //u16ImageWidth = MApi_JPEG_GetWidth();
        //u16ImageHeight = MApi_JPEG_GetHeight();
        //bIsProgressive = MApi_JPEG_IsProgressive();
        //u16ImageOriWidth = MApi_JPEG_GetOriginalWidth();
        //u16ImageOriHeight = MApi_JPEG_GetOriginalHeight();
        //u16ImageNonAlignWidth = MApi_JPEG_GetNonAlignmentWidth();
        //u16ImageNonAlignHeight = MApi_JPEG_GetNonAlignmentHeight();
        //u8ScaleDownFactor = MApi_JPEG_GetScaleDownFactor();
        //u8DebugLevel = MApi_JPEG_GetDbgLevel();
        MApi_JPEG_GetInfo(&stJPEG_Info);
        MApi_JPEG_GetStatus(&stJPEG_Status);
        MApi_JPEG_GetLibVer(&pu8JPEG_Ver);
        u16ImageAlignPitch = MApi_JPEG_GetAlignedPitch(),
        u16ImageAlignWidth = MApi_JPEG_GetAlignedWidth(),
        u16ImageAlignHeight = MApi_JPEG_GetAlignedHeight();
//        bThumbnailFound = MApi_JPEG_ThumbnailFound();

        printf("verJPD_SetStatus >>>>>>>>>>> w:%d,  h:%d,  p:%d\n",u16ImageAlignWidth,u16ImageAlignHeight,u16ImageAlignPitch);
        g_JpgPitch = MApi_JPEG_GetAlignedPitch();
        g_JpgHeight = MApi_JPEG_GetAlignedHeight();
        g_JpgWidth = MApi_JPEG_GetAlignedWidth();

#if defined(MSOS_ISR_SUPPORT)
        verJPD_DEBUG(printf("u32IsrCnt = %ld\n", u32IsrCnt));
#endif
        MApi_JPEG_GetEXIFDateTime(&_gEXIF_DateTime);
        MApi_JPEG_GetEXIFOrientation(&_gEXIF_Orientation);
    }
    else if( g_state == E_JPEG_DECODE_ERR )
    {
        verJPD_DEBUG(printf("verJPD_SetStatus:E_JPEG_DECODE_ERR\n"));
        //u16ImageWidth = MApi_JPEG_GetWidth();
        //u16ImageHeight = MApi_JPEG_GetHeight();
        //bIsProgressive = MApi_JPEG_IsProgressive();
        //u16ImageOriWidth = MApi_JPEG_GetOriginalWidth();
        //u16ImageOriHeight = MApi_JPEG_GetOriginalHeight();
        //u16ImageNonAlignWidth = MApi_JPEG_GetNonAlignmentWidth();
        //u16ImageNonAlignHeight = MApi_JPEG_GetNonAlignmentHeight();
        //u8ScaleDownFactor = MApi_JPEG_GetScaleDownFactor();
        //u16ErrorCode = MApi_JPEG_GetErrorCode();
        //u8DebugLevel = MApi_JPEG_GetDbgLevel();
        MApi_JPEG_GetInfo(&stJPEG_Info);
        MApi_JPEG_GetStatus(&stJPEG_Status);
        MApi_JPEG_GetLibVer(&pu8JPEG_Ver);
        u16ImageAlignPitch = MApi_JPEG_GetAlignedPitch(),
        u16ImageAlignWidth = MApi_JPEG_GetAlignedWidth(),
        u16ImageAlignHeight = MApi_JPEG_GetAlignedHeight();
//        bThumbnailFound = MApi_JPEG_ThumbnailFound();
#if defined(MSOS_ISR_SUPPORT)
        verJPD_DEBUG(printf("u32IsrCnt = %ld\n", u32IsrCnt));
#endif
        MApi_JPEG_GetEXIFDateTime(&_gEXIF_DateTime);
        MApi_JPEG_GetEXIFOrientation(&_gEXIF_Orientation);
    }
}

//--------------------------------------------------------------------------------------------------
/// API for JPEG decoder initialization::
static void verJPD_Init(EN_JPEG_TEST u8Source)
{
    verJPD_DEBUG(printf("verJPD_Init\n"));

    //for test code
    g_state = E_JPEG_INIT;
    //u16ImageWidth = 0;
    //u16ImageHeight = 0;
    //u16ImageOriWidth = 0;
    //u16ImageOriHeight = 0;
    //u16ImageNonAlignWidth = 0;
    //u16ImageNonAlignHeight = 0;
    //u16ErrorCode = 0;
    //u8ScaleDownFactor = 0;
    //bIsProgressive = FALSE;

    //u8DebugLevel = 0x0;

    s32InitByteRead = 0;
    u8EOF_flag = FALSE;

    u32ReadBuffVirAddr = MS_PA2KSEG1((MS_U32)MAD_JPEG_READBUFF_ADR);
    u32IntBuffVirAddr = MS_PA2KSEG1((MS_U32)MAD_JPEG_INTERBUFF_ADR);
    u32OutBuffVirAddr = MS_PA2KSEG1((MS_U32)MAD_JPEG_OUT_ADR);

    printf("u32ReadBuffVirAddr = %lx, u32IntBuffVirAddr = %lx, u32OutBuffVirAddr = %lx\n", u32ReadBuffVirAddr, u32IntBuffVirAddr, u32OutBuffVirAddr);

    if(u8Source == E_JPD_BASELINE_TEST) //BaseLine
    {
        u8InputDataAddr = (MS_U8 *)u8BaseLineJPEG;
        u32InputDataLength = sizeof(u8BaseLineJPEG);
    }
    else if(u8Source == E_JPD_PROGRESSIVE_TEST) //Progressive
    {
        u8InputDataAddr = (MS_U8 *)u8ProgressiveJPEG;
        u32InputDataLength = sizeof(u8ProgressiveJPEG);
    }
    else if(u8Source == E_JPD_CMYK_TEST) //CMYK
    {
        u8InputDataAddr = (MS_U8 *)u8CmykJPEG;
        u32InputDataLength = sizeof(u8CmykJPEG);
    }

    u32ReadPosition = 0;

#if defined(MSOS_ISR_SUPPORT)
    u32IsrCnt = 0;
    _gDecodeStatus = E_DECODE_NONE;
    u32ISRtimeout = 0;
#endif

    _gEXIF_DateTime.bHasDataTime = FALSE;
    _gEXIF_DateTime.u32Year = 0;
    _gEXIF_DateTime.u32Month = 0;
    _gEXIF_DateTime.u32Day = 0;
    _gEXIF_DateTime.u32Hour = 0;
    _gEXIF_DateTime.u32Minute = 0;
    _gEXIF_DateTime.u32Second = 0;
    _gEXIF_Orientation = E_JPEG_EXIF_ORIENT_NOT_FOUND;

    verJPD_InitFileSystem();

    MApi_JPEG_SetDbgLevel(E_JPEG_DEBUG_NONE);
}

//--------------------------------------------------------------------------------------------------
/// API for starting JPEG data decoding
//--------------------------------------------------------------------------------------------------
static void verJPD_StartDecode(EN_JPEG_DECODE_TYPE decode_type)
{
    if(g_state != E_JPEG_INIT)
    {
        verJPD_DEBUG(printf("verJPD_StartDecode failed, state = %d\n", g_state));
        return;
    }

    // init JPEG DECODE BUFFER
    {
        JPEG_InitParam InitParam;

        verJPD_DEBUG(printf("verJPD_StartDecode: INIT\n"));

        MApi_JPEG_SetMaxDecodeResolution(JPEGBASEWIDTHMAX, JPEGBASEHEIGHTMAX);
        MApi_JPEG_SetProMaxDecodeResolution(JPEGPROWIDTHMAX, JPEGPROHEIGHTMAX);

        //InitParam.u32MRCBufAddr =  MS_VA2PA((((unsigned int)0x80A01000)|0x20000000) + 0x278000);  // (((unsigned int)0x80A01000)|0x20000000) + 0x278000; //verJPD_READBUFF_ADR;
        //InitParam.u32MRCBufAddr =  MS_VA2PA((((unsigned int)0x80A01000)|0x20000000) + ResBIN_LogoOffset);
        InitParam.u32MRCBufAddr =  TARGET_LOGO_ADDR;
        InitParam.u32MRCBufSize = MAD_JPEG_READBUFF_LEN;// verJPD_READBUFF_LEN;
        InitParam.u32MWCBufAddr = MAD_JPEG_OUT_ADR;//verJPD_OUT_ADR;
        InitParam.u32MWCBufSize = MAD_JPEG_OUT_LEN;//verJPD_OUT_LEN;
        InitParam.u32InternalBufAddr = MAD_JPEG_INTERBUFF_ADR;//verJPD_INTERBUFF_ADR;
        InitParam.u32InternalBufSize = MAD_JPEG_INTERBUFF_LEN;//verJPD_INTERBUFF_LEN;
        InitParam.u32DecByteRead = TARGET_LOGO_SIZE;// file size
        InitParam.bEOF = TRUE;  //u8EOF_flag; // TRUE, the number of read_act, End of File ?
        if(E_JPD_MAIN_DECODE == decode_type)
        {
            InitParam.u8DecodeType = E_JPEG_TYPE_MAIN;
        }
        else
        {
            InitParam.u8DecodeType = E_JPEG_TYPE_THUMBNAIL;
        }
        InitParam.bInitMem = TRUE;
        InitParam.pFillHdrFunc = NULL; //(JPEG_FillHdrFunc)verJPD_FillHdrFunc; // NULL

        MApi_JPEG_Init(&InitParam);

        if(MApi_JPEG_GetErrorCode() == E_JPEG_NO_ERROR)
        {
            g_state = E_JPEG_DECODE_HEADER;
        }
        else
        {
            g_state = E_JPEG_DECODE_ERR;
            verJPD_DEBUG(printf("verJPD_StartDecode: Init failed\n"));
        }
    }

    verJPD_DEBUG(printf("verJPD_StartDecode: INIT DONE : EventFlag = 0x%04X\n", MApi_JPEG_GetJPDEventFlag()));

    //parse JPEG Header
    if(g_state == E_JPEG_DECODE_HEADER)
    {
        verJPD_DEBUG(printf("verJPD_StartDecode: DECODE HEADER\n"));
        if(E_JPEG_FAILED == MApi_JPEG_DecodeHdr())
        {
            if(MApi_JPEG_GetErrorCode() == E_JPEG_STREAM_READ)
            {
                verJPD_DEBUG(printf("verJPD_StartDecode: DecodeHdr read failed\n"));
                g_state = E_JPEG_IDLE;
            }
            else
            {
                verJPD_DEBUG(printf("verJPD_StartDecode: DecodeHdr failed\n"));
                g_state = E_JPEG_DECODE_ERR;
            }
        }
        else
        {
            g_state = E_JPEG_DECODE_BEGIN;
        }
    }
    verJPD_DEBUG(printf("verJPD_StartDecode: DECODE HEADER DONE : EventFlag = 0x%04X\n", MApi_JPEG_GetJPDEventFlag()));

    if(g_state == E_JPEG_IDLE)
    {
        verJPD_DEBUG(printf("verJPD_StartDecode: IDLE\n"));
        MApi_JPEG_Rst();
        MApi_JPEG_Exit();
        g_state = E_JPEG_INIT;
        return;
    }

#if defined(MSOS_ISR_SUPPORT)
    if(TRUE != MApi_JPEG_IsProgressive())
    {
        _gDecodeStatus = E_DECODING;
        verJPD_InterruptRequest();
    }
#endif

    //begin decode
    while(g_state == E_JPEG_DECODE_BEGIN)
    {
        verJPD_DEBUG(printf("verJPD_StartDecode: DECODE BEGIN\n"));
        switch(MApi_JPEG_Decode())
        {
            case E_JPEG_DONE:
                g_state = E_JPEG_DECODE_BEGIN;
                break;
            case E_JPEG_OKAY:
#if defined(MSOS_ISR_SUPPORT)
                if(TRUE == MApi_JPEG_IsProgressive())
                {    //Progressive decoding is done in decode begin state.
                    _gDecodeStatus = E_DECODE_DONE;
                }
#endif
                g_state = E_JPEG_WAITDONE;
                break;
            case E_JPEG_FAILED:
            default:
                verJPD_DEBUG(printf("verJPD_StartDecode: DecodeBegin failed\n"));
                g_state = E_JPEG_DECODE_ERR;
                break;
        }
    }
    verJPD_DEBUG(printf("verJPD_StartDecode: DECODE BEGIN DONE : EventFlag = 0x%04X\n", MApi_JPEG_GetJPDEventFlag()));

    //wait done
    verJPD_DEBUG(printf("verJPD_StartDecode: WAITDONE\n"));
    while(g_state == E_JPEG_WAITDONE)
    {
        switch(verJPD_WaitDone())
        {
            case E_DECODE_DONE:
                g_state = E_JPEG_DECODE_DONE;
                break;

            case E_DECODING:
                g_state = E_JPEG_WAITDONE;
                break;

            case E_STREAM_READ_ERR:
            case E_DECODE_ERR:
            default:
                verJPD_DEBUG(printf("verJPD_StartDecode: WaitDone failed\n"));
                g_state = E_JPEG_DECODE_ERR;
                MApi_JPEG_Rst();
                break;
        }
    }

    verJPD_SetStatus();
#if defined(MSOS_ISR_SUPPORT)
    if(TRUE != MApi_JPEG_IsProgressive())
    {
        MApi_JPEG_DisableISR();
    }
#endif
    MApi_JPEG_Exit();
    g_state = E_JPEG_INIT;
}

#if defined(MSOS_ISR_SUPPORT)
static void verJPD_ISR_CB(void)
{
    JPEG_Event reg_val = MApi_JPEG_GetJPDEventFlag();
    verJPD_DEBUG(printf("verJPD_ISR_CB!!, JPD Event = 0x%04x\n", reg_val));
    u32IsrCnt++;

    if((g_state != E_JPEG_DECODE_BEGIN)
    && (g_state != E_JPEG_WAITDONE))
    {
        verJPD_DEBUG(printf("verJPD_ISR_CB: Wrong state to get isr CB!!\n"));
        MApi_JPEG_SetJPDEventFlag(VERJPD_EVENT_ALL);
        _gDecodeStatus = E_DECODE_ERR;
        return;
    }

    if(E_JPEG_EVENT_DEC_DONE & reg_val)
    {
        verJPD_DEBUG(printf("verJPD_ISR_CB:Decode Done\n"));
        MApi_JPEG_SetJPDEventFlag(VERJPD_EVENT_ALL);
        _gDecodeStatus = E_DECODE_DONE;
    }
    else if((E_JPEG_EVENT_DEC_ERROR_MASK & reg_val)
#if defined(CHIP_T3) || defined(CHIP_T4) || defined(CHIP_T7) || defined(CHIP_JANUS) || defined(CHIP_U4)
    || (E_JPEG_EVENT_DEC_MWB_FULL & reg_val)
#endif
    )
    {
        verJPD_DEBUG(printf("verJPD_ISR_CB:Baseline decode error:\n"));
        MApi_JPEG_SetJPDEventFlag(VERJPD_EVENT_ALL);
        // temp patch for protect JPD from writing to illegal memory
        //MApi_JPEG_Rst();
        _gDecodeStatus = E_DECODE_ERR;
    }
    else if(E_JPEG_EVENT_DEC_MRB_DONE & reg_val)
    {
        JPEG_BuffLoadType PreLoadBuffType = E_JPEG_BUFFER_NONE;
        MApi_JPEG_GetStatus(&stJPEG_Status);
        switch(MApi_JPEG_GetBuffLoadType(&PreLoadBuffType))
        {
            case E_JPEG_OKAY:
                if(!verJPD_PreLoadBuffer(PreLoadBuffType))
                {
                    if(MApi_JPEG_GetErrorCode() == E_JPEG_STREAM_READ)
                        _gDecodeStatus = E_STREAM_READ_ERR;
                    else
                        _gDecodeStatus = E_DECODE_ERR;
                }
                else
                {
                    _gDecodeStatus = E_DECODING;
                }
                break;
            case E_JPEG_FAILED:
                MApi_JPEG_SetJPDEventFlag(VERJPD_EVENT_ALL);
                _gDecodeStatus = E_DECODE_ERR;
                break;
            case E_JPEG_RETRY:
            default:
                _gDecodeStatus = E_DECODING;
                break;
        }
    }
    else if(reg_val == 0)
    {
        _gDecodeStatus = E_DECODING;
    }
}

static void verJPD_InterruptRequest(void)
{
    verJPD_DEBUG(printf("verJPD_InterruptRequest\n"));
    MApi_JPEG_EnableISR((JPEG_IsrFuncCb)verJPD_ISR_CB);
}
#endif

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
int JPG_GetAlignmentWidth(void)
{
    return g_JpgWidth;
}
int JPG_GetAlignmentHeight(void)
{
    return g_JpgHeight;
}
int JPG_GetAlignmentPitch(void)
{
    return g_JpgPitch;
}
MS_U32 JPG_GetOutRawDataAddr(void)
{
    return MAD_JPEG_OUT_ADR;// verJPD_OUT_ADR;
}
//--------------------------------------------------------------------------------------------------
///Entry function for JPD testing.
//--------------------------------------------------------------------------------------------------
void verJPD_Main(MS_U32 u32SrcAddr, MS_U32 u32SrcSize)
{
    verJPD_DEBUG(printf("verJPD_Main... Start!!\n"));

    TARGET_LOGO_ADDR = u32SrcAddr;
    TARGET_LOGO_SIZE = u32SrcSize;

#ifdef SLIDE_SHOW_TEST
    slide_count = 4;
    while(slide_count)
    {
        verJPD_DEBUG(printf("=====slide show test : count = %d=====\n", slide_count));
        if((slide_count%2) == 1)
        {
            verJPD_Init(E_JPD_BASELINE_TEST);
        }
        else
        {
            verJPD_Init(E_JPD_PROGRESSIVE_TEST);
        }

        //Preload data for init JPEG decoder data.
        s32InitByteRead = _Pinput_stream->read((MS_U8 *)u32ReadBuffVirAddr, MAD_JPEG_READBUFF_LEN, &u8EOF_flag, _Pinput_stream);

        if(s32InitByteRead < 0)
        {
            verJPD_DEBUG(printf("Initial read file error!!\n"));
        }

        verJPD_StartDecode(E_JPD_MAIN_DECODE);
        slide_count--;
    }
#else
    verJPD_Init(E_JPD_BASELINE_TEST);

    //Preload data for init JPEG decoder data.
    s32InitByteRead = _Pinput_stream->read((MS_U8 *)u32ReadBuffVirAddr, MAD_JPEG_READBUFF_LEN, &u8EOF_flag, _Pinput_stream);

    if(s32InitByteRead < 0)
    {
        verJPD_DEBUG(printf("Initial read file error!!\n"));
    }

    verJPD_StartDecode(E_JPD_MAIN_DECODE);
////    verJPD_StartDecode(E_JPD_THUMBNAIL_DECODE);

    verJPD_DEBUG(printf("verJPD_Main... End!!\n"));
#endif
}


