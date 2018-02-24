////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
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


#ifndef STREAMING_APP_H
#define STREAMING_APP_H

#include <stdint.h>
#include "ms_io.h"
#include "streaming.h"

#ifdef _MSC_VER
//#define SIM_DATA_GEN // if you would like test timeshift, please enable this one.
#endif

#ifdef SIM_DATA_GEN
#include <time.h>
static clock_t start, end;
static double cpu_time_used;
#define DELAY_MS    (1000.0/(BYTERATE/READSIZE))
#endif
#define BYTERATE     (63*1024)  // MFID2_25f_384_32k.mfs


#ifdef __cplusplus
extern "C" {
#endif

typedef struct timeshift_s
{
    uint32_t    rpos;           // read position of ring file
    uint32_t    wpos;           // write position of ring file
    uint32_t    bytecnt;        // available byte count of ring file
    int32_t     validfilepos;   // useless //the valid file range is from (validfilepos-filesize) to (validfilepos)
    uint32_t    filesize;       // maximal ring file size
    uint32_t    rloopcnt;       // read loop count
    uint32_t    wloopcnt;       // write loop count
} timeshift_st;


#define MAX_CMD_SIZE 100
typedef struct cmdQ_s
{
    int         size;
    uint8_t     queue[MAX_CMD_SIZE];
} cmdQueue_st;

typedef enum
{
    CMD_SET_SERVICE = 0,
    CMD_SET_SERVICEPROVIDER,
    CMD_SCAN_FREQUENCY,
    CMD_GET_SIGNALSTRENGTH,
    CMD_GET_SIGNALQUALITY,
    CMD_GET_LOCKSTATUS,
    CMD_SET_EMM,
} Command_type;

typedef struct signalInfo_s
{
    int signalStrength;
    int signalQuality;
    int signalLockStatus;
} signalInfo_st;

#define MAX_SERVICE_LEN 20
typedef struct service_s
{
    uint8_t Service_payload[MAX_SERVICE_LEN];
    int Service_length;
    int available;
} service_st;

/*
typedef struct programInfo_s
{
    int channel1;
    int channel2;
    int frequency;
    int bandwidth;  // ISDB-T only
    int segNo;      // ISDB-T only
    int16 timeslot[3];
} programInfo_st;
*/
/************************************************************************/
/*       Record/TimeShift  Application                                  */
/************************************************************************/

typedef enum
{
    RECORD_ENABLE = 0,
    TIMESHIFT_ENABLE,
    TIMESHIFT_BYTECNT,
    TIMESHIFT_RPOS,
    TIMESHIFT_WPOS,
    TIMESHIFT_FILESIZE,
} CB_AppStatus;

void init_app_status(void);
int get_app_status(int type);

unsigned long RecordWrite (uint8_t *data, uint32_t data_len);
int RecordStart(const ms_fnchar *filename);
void RecordStop(void);
void RecordGetDration(uint32_t *duration);
int TimeShiftStart(const ms_fnchar *filename, int filesize, cb_buffer_st *cbuf);
void TimeShiftStop(cb_buffer_st *cbuf);
void TimeShiftPlay(cb_buffer_st *cbuf);
void TimeShiftGetDration(uint32_t *s_dur, uint32_t *e_dur);
void TimeShiftReadPos(cb_buffer_st *cbuf, int readsize);
void TimeShiftSeekPos(unsigned int offset);

void ConfigSetDriver(int cmdType, void *pPayload, uint8_t payloadLen);
void ConfigGetDriver(int cmdType);

void CheckCmdBuffer(void);

void GetStatistics(void);
int GetSignalStrength(void);
int GetSignalQuality(void);
int GetLockStatus(void);
void CheckDemodReset(void);
int ResetSignalInfo(void);

int streamingapp_input_plugin(int type);
void streamingapp_init(void);
void streamingapp_deinit(void);
int sreamingapp_wait_set_channel_done(cb_buffer_st *cbuf);

typedef int(*pCbDemodInit)(void *pPayload, uint8_t payloadLen);
typedef int(*pCbSetService)(void *pPayload, uint8_t payloadLen);
typedef int(*pCbSetServiceProvider)(void *pPayload, uint8_t payloadLen);
typedef int(*pCbScanFrequency)(void *pPayload, uint8_t payloadLen);
typedef int(*pCbGetSignalStrength)(void);
typedef int(*pCbGetSignalQuality)(void);
typedef int(*pCbGetLockStatus)(void);

extern pCbDemodInit             fnDemodInit;
extern pCbSetService            fnSetService;
extern pCbSetServiceProvider    fnSetServiceProvider;
extern pCbScanFrequency         fnScanFrequency;
extern pCbGetSignalStrength     fnGetSignalStrength;
extern pCbGetSignalQuality      fnbGetSignalQuality;
extern pCbGetLockStatus         fnGetLockStatus;


#ifdef __cplusplus
}
#endif
#endif /* STREAMING_APP_H */
