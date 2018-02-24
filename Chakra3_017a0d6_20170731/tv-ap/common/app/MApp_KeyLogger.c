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

#define MAPP_KEYLOGGER_C

//.h file inclue
#include "Utl.h"
#include "IOUtil.h"

#include "Board.h"

#include "drvMIU.h"

#include "msAPI_Global.h"
#include "msAPI_Timer.h"
#include "msAPI_MIU.h"
#include "msAPI_FSCommon.h"
#include "msAPI_FCtrl.h"
#include "msAPI_Flash.h"

#include "MApp_KeyLogger.h"
#include "MApp_Key.h"
#include "MApp_IR.h"
#include "MApp_FlashMap.h"
#include "MApp_EEPROM_Map.h"
#include "MApp_USBDownload.h"
#include "MApp_SaveData.h"

#if ENABLE_KEY_LOGGER
//Macro define


//Configuration
#define _KEY_LOGGER_DATABASE_AREA_FLASH_START_ADDRESS_          (0x10000 * FMAP_FACTORY_SETTING_BANK_START) //Need to be 64KB alignment!!!
#define _KEY_LOGGER_DATABASE_AREA_FLASH_END_ADDRESS_            (FLASH_SIZE - 1)
#define _KEY_LOGGER_FLASH_PARTIAL_BACKUP_FLASH_START_ADDRESS_   (0)     //Need to be 64KB alignment!!!
#define _KEY_LOGGER_FLASH_PARTIAL_BACKUP_FLASH_END_ADDRESS_     (FLASH_SIZE - 1)

#define _KEY_LOGGER_VER_MAJOR_     (0)
#define _KEY_LOGGER_VER_MINOR_     (4)


//=========Header Area===================
#define _KEY_LOGGER_BIN_CRC_OFFSET_                     (0x08)
#define _KEY_LOGGER_BIN_BIN_VER_MAJOR_OFFSET_           (0x0A)
#define _KEY_LOGGER_BIN_BIN_VER_MINOR_OFFSET_           (0x0B)
#define _KEY_LOGGER_BIN_EVENT_LOG_ADDR_OFFSET_          (0x10)
#define _KEY_LOGGER_BIN_EVENT_LOG_LEN_OFFSET_           (0x14)
#define _KEY_LOGGER_BIN_DATABASE_BIN_ADDR_OFFSET_       (0x18)
#define _KEY_LOGGER_BIN_DATABASE_BIN_LEN_OFFSET_        (0x1C)
#define _KEY_LOGGER_BIN_DATABASE_FLASH_ADDR_OFFSET_     (0x20)
#define _KEY_LOGGER_BIN_DATABASE_FLASH_LEN_OFFSET_      (0x24)
#define _KEY_LOGGER_BIN_FLASH_BACKUP_BIN_ADDR_OFFSET_   (0x28)
#define _KEY_LOGGER_BIN_FLASH_BACKUP_BIN_LEN_OFFSET_    (0x2C)
#define _KEY_LOGGER_BIN_FLASH_BACKUP_FLASH_ADDR_OFFSET_ (0x30)
#define _KEY_LOGGER_BIN_FLASH_BACKUP_FLASH_LEN_OFFSET_  (0x34)
#define _KEY_LOGGER_BIN_BIN_END_STRING_ADDR_OFFSET_     (0x38)
#define _KEY_LOGGER_BIN_BIN_END_STRING_LEN_OFFSET_      (0x3C)
#define _KEY_LOGGER_BIN_HEADER_SIZE_                    (0x80)

//=========Payload Area===================
#define _KEY_LOGGER_PAYLOAD_OFFSET_            (_KEY_LOGGER_BIN_HEADER_SIZE_)

#define _KEY_LOGGER_EVENT_DB_ADDR_OFFSET_      (_KEY_LOGGER_PAYLOAD_OFFSET_)
#define _KEY_LOGGER_EVENT_DB_SIZE_             ((sizeof(ST_KEYLOGGER_EVENT))*(_EVENT_DB_EVENT_MAX_NUM_))

#define _KEY_LOGGER_DATABASE_ADDR_OFFSET_      (_KEY_LOGGER_PAYLOAD_OFFSET_)
#define _KEY_LOGGER_DATABASE_SIZE_             (_KEY_LOGGER_DATABASE_AREA_FLASH_END_ADDRESS_ - _KEY_LOGGER_DATABASE_AREA_FLASH_START_ADDRESS_ + 1)

#define _KEY_LOGGER_FLASH_BKP_ADDR_OFFSET_     (_KEY_LOGGER_PAYLOAD_OFFSET_)
#define _KEY_LOGGER_FLASH_BKP_SIZE_            (_KEY_LOGGER_FLASH_PARTIAL_BACKUP_FLASH_END_ADDRESS_ - _KEY_LOGGER_FLASH_PARTIAL_BACKUP_FLASH_START_ADDRESS_ + 1)

#define _KEY_LOGGER_BIN_END_STRING_SIZE_       (8)
//=========Payload Area End===============


#define _KEY_LOGGER_CONFIG_BIN_SIZE_                (0x01)
#define _KEY_LOGGER_CONFIG_BIN_LOGGERMODE_OFFSET_   (0x00)
#define _KEY_LOGGER_WRITE_BIN_RETRY_TIME_MAX_       (5)

#define _KEY_LOGGER_EVENTDB_BIN_NAME_          "KeyLogger_Key_Event_DB.bin"
#define _KEY_LOGGER_DATABASE_BIN_NAME_         "KeyLogger_Database.bin"
#define _KEY_LOGGER_FLASH_BKP_BIN_NAME_        "KeyLogger_Flash.bin"
#define _KEY_LOGGER_CONFIG_BIN_NAME_           "KeyLogger_CFG.bin"

#define _EVENT_DB_EVENT_MAX_NUM_        (1000)
#define _EVENT_DB_EVENT_CHECK_SUM_BIAS  (0x11)

typedef enum
{
    EN_GETCONFIG_RETURN_OK,

    EN_GETCONFIG_RETURN_USB_FAIL,
    EN_GETCONFIG_RETURN_FILE_NOT_EXIST,
}EN_GETCONFIG_RET;


//Local variable
static EN_KEYLOGGER_MODE enKeyLoggerMode;
static ST_KEYLOGGER_EVENT astKeyLogger_EventDb[_EVENT_DB_EVENT_MAX_NUM_];
static ST_KEYLOGGER_EVENT stKeyLogger_Event_OnFire = {0xFFFFFFFF, 0xAA, 0xFF, 0x1, 0x1}; //Next event to execute from queue

static U16 u16ActionExecIdx = 0;
static U16 g_u16ActionSaveIdx = 0;
static U32 u32NextEventExecTime = 0xFFFFFFFF;
static BOOL bSimulatedKeyWaitingParsed = FALSE; //TRUE: some event found, not executed yet
static BOOL bEventExecutionFinished = FALSE;    //TRUE: end of event DB, no further execution
static BOOL bSimulationAbortedByUserInput = FALSE;  //TRUE: Simulating mode, after any user input. FALSE: No user input got yet.
static U32 u32ComboKeyBuffer = 0;   //To store combo key input. Each nibble for 1 key

static const U8 au8KeyLoggerBinHeaderMagicNum[8] = {0xAA, 0xBB, 0xCC, 0x03, 0x55, 0x26, 0x00, 0x6F};
static const U8 au8KeyLoggerBinEndString[_KEY_LOGGER_BIN_END_STRING_SIZE_] = {0xA5, 0x5A, 0xA5, 0x67, 0x34, 0xA5, 0x5A, 0xA5};
static FileEntry g_fileEntry_KeyLogger;


//Internal function prototype declare
static BOOL _MApp_KeyLogger_CheckActionValid(ST_KEYLOGGER_EVENT* pStEvent);
static BOOL _MApp_KeyLogger_GetNextEventIdx(U16 u16StartIdx, U16* pu16NextIdx);
void _MApp_KeyLogger_DWordArrangeToByte_FromLSB(U8* pu8Dst, U32 u32Data);
void _MApp_KeyLogger_ReadDWordFromByte_FromLSB(U8* pu8Src, U32* pu32Data);
BOOL _MApp_KeyLogger_IsCurrentLoggingMode(void);
BOOL _MApp_KeyLogger_IsCurrentSimulatingMode(void);
EN_GETCONFIG_RET _MApp_KeyLogger_GetConfigFromUsbBin(U8* pu8Buf, U32 u32Length);
BOOL _MApp_KeyLogger_GetDataFromBin(EN_KEYLOGGER_PACK_MODE ePackMode, U32* pu32DataPhysicalAddr);
void _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(BOOL bEnable);
BOOL _MApp_KeyLogger_BasicBinValidCheck(U8* pu8RestoreBufferAddr);
BOOL _MApp_KeyLogger_FlashWrite(U32 u32StartAddr, U32 u32WriteSize, U8 * user_buffer);


//External function prototype
BOOLEAN MApp_UsbSaveData_SearchFileInRoot(U8* pu8FileName, FileEntry* pFileEntry);



//========================================================
//1. Common function area (both remote TV/local TV need)
//2. Remote TV only function  --> For collect information
//3. Local TV only function   --> For duplicate problem
//========================================================



//========================================================
//1. Common function area (both remote TV/local TV need)
//========================================================
void MApp_KeyLogger_DataReset(void)
{
    U16 u16DummyIdx = 0;

    u16ActionExecIdx = 0;
    g_u16ActionSaveIdx = 0;
    u32NextEventExecTime = 0xFFFFFFFF;
    bSimulatedKeyWaitingParsed = FALSE;
    bEventExecutionFinished = FALSE;
    memset(&stKeyLogger_Event_OnFire, 0, sizeof(ST_KEYLOGGER_EVENT));

    for(u16DummyIdx=0; u16DummyIdx<_EVENT_DB_EVENT_MAX_NUM_; u16DummyIdx++)
    {
        astKeyLogger_EventDb[u16DummyIdx].u32EventTime = 0xFFFFFFFF;
        astKeyLogger_EventDb[u16DummyIdx].u8CrcResult = 0xAA;
        astKeyLogger_EventDb[u16DummyIdx].u8EventKeyCode = KEY_NULL;
        astKeyLogger_EventDb[u16DummyIdx].u8EventKeyType = KEY_TYPE_IR;
        astKeyLogger_EventDb[u16DummyIdx].u8EventKeyRepeat= 0;
    }

}


BOOL MApp_KeyLogger_Init(void)
{
    U8 u8ConfigBuffer[_KEY_LOGGER_CONFIG_BIN_SIZE_]={5};
    U32 u32RestoreBufferPhyAddr = 0;
    U8* pU8RestoreBufferCacheVirtualAddr = NULL;
    EN_GETCONFIG_RET eRet = EN_GETCONFIG_RETURN_USB_FAIL;
    U32 u32UsbStartOffset = 0, u32UsbLength = 0, u32FlashStartOffset = 0, u32FlashLength = 0;
    U8 u8DummyIdx = 0;

    if(stGenSetting.stDebugSetting.bKeyLoggerEnable == FALSE)
    {
        printf("\n\r%s - Not needed, Key logger is disabled.\n", __FUNCTION__);
        return FALSE;
    }

    MApp_KeyLogger_DataReset();

    eRet = _MApp_KeyLogger_GetConfigFromUsbBin(u8ConfigBuffer, _KEY_LOGGER_CONFIG_BIN_SIZE_);

    if(eRet == EN_GETCONFIG_RETURN_FILE_NOT_EXIST)  //No file, create one.
    {
        MApp_KeyLogger_SetMode(EN_KEYLOGGER_MODE_OFF);
        MApp_KeyLogger_ModifyConfigBin(EN_KEYLOGGER_MODE_OFF);
    }
    else if(eRet == EN_GETCONFIG_RETURN_USB_FAIL)
    {
        MApp_KeyLogger_SetMode(EN_KEYLOGGER_MODE_OFF);
    }
    else// if(eRet == EN_GETCONFIG_RETURN_OK)
    {
        MApp_KeyLogger_SetMode((EN_KEYLOGGER_MODE)u8ConfigBuffer[_KEY_LOGGER_CONFIG_BIN_LOGGERMODE_OFFSET_]);
    }

    printf("\n\rMApp_KeyLogger_Init - Current KeyLogger mode = %d", MApp_KeyLogger_GetMode());

    if(MApp_KeyLogger_GetMode() == EN_KEYLOGGER_MODE_OFF)
    {
        //No key logger, no more job to do in this function
        return TRUE;
    }


    switch(MApp_KeyLogger_GetMode())
    {
        //==========Logging=========
        case EN_KEYLOGGER_MODE_LOGGING_KEY_PLUS_DB:
            //Backup DB to USB
            MApp_KeyLogger_Encapsulate(EN_KEYLOGGER_PACK_MODE_DATABASE);
            break;

        case EN_KEYLOGGER_MODE_LOGGING_KEY_PLUS_PARTIAL_FLASH:
            //Backup flash to USB
            MApp_KeyLogger_Encapsulate(EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH);
            break;


        //==========Simulating======
        case EN_KEYLOGGER_MODE_SIMULATING_KEY:
            //Do nothing here, because Load key event db process shared by all simulating case
            break;


        case EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_DB:
        case EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_DB_ALWAYS_RECOVER:
            //1. Recover DB from USB to flash
            //2. If not always recovery mode, set state to Simulate key, then reboot
            //3. else, go on
            if (_MApp_KeyLogger_GetDataFromBin(EN_KEYLOGGER_PACK_MODE_DATABASE, &u32RestoreBufferPhyAddr))
            {
                msAPI_Timer_ResetWDT();
                printf("\n\r Database bin loaded but invalid.");
                pU8RestoreBufferCacheVirtualAddr = (U8 *)(MsOS_PA2KSEG0(u32RestoreBufferPhyAddr));
                if(_MApp_KeyLogger_BasicBinValidCheck(pU8RestoreBufferCacheVirtualAddr) == FALSE)
                {
                    break;//return FALSE;
                }

                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_DATABASE_BIN_ADDR_OFFSET_), &u32UsbStartOffset);
                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_DATABASE_BIN_LEN_OFFSET_), &u32UsbLength);
                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_DATABASE_FLASH_ADDR_OFFSET_), &u32FlashStartOffset);
                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_DATABASE_FLASH_LEN_OFFSET_), &u32FlashLength);

                if((u32UsbStartOffset != _KEY_LOGGER_DATABASE_ADDR_OFFSET_)
                    ||(u32UsbLength != _KEY_LOGGER_DATABASE_SIZE_)
                    ||(u32FlashStartOffset != _KEY_LOGGER_DATABASE_AREA_FLASH_START_ADDRESS_)
                    ||(u32FlashLength != _KEY_LOGGER_DATABASE_SIZE_)
                    )
                {
                    printf("\n\rDatabase address or length mismatch between dumped bin and source code %d", __LINE__);
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                if((u32FlashStartOffset%0x10000 != 0) || (u32FlashLength%0x10000 != 0))
                {
                    printf("\n\rDatabase address not align to 64k byte");
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                if(u32FlashStartOffset+u32FlashLength > FLASH_SIZE)
                {
                    printf("\n\rDatabase end flash address over flash size!!!");
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                printf("\n\rStart to write recovery database data to SPI flash...");

                for(u8DummyIdx = 0; u8DummyIdx<_KEY_LOGGER_WRITE_BIN_RETRY_TIME_MAX_; u8DummyIdx++)
                {
                    msAPI_Timer_ResetWDT();
                    msAPI_Flash_Set_WriteProtect_Disable_Range( u32FlashStartOffset, u32FlashLength);
                    MDrv_FLASH_AddressErase(u32FlashStartOffset, u32FlashLength, TRUE);
                    msAPI_Flash_WaitWriteDone(5000);
                    if(TRUE == _MApp_KeyLogger_FlashWrite(u32FlashStartOffset, u32FlashLength, (pU8RestoreBufferCacheVirtualAddr+u32UsbStartOffset) ))
                    {
                        //Write data success, normal exit path
                        break;
                    }
                    printf("\n\rWrite data to flash fail, retry count=%d @ %s-%d", u8DummyIdx, __FUNCTION__, __LINE__);
                }
                msAPI_Flash_Set_WriteProtect(ENABLE);

                if(u8DummyIdx >= _KEY_LOGGER_WRITE_BIN_RETRY_TIME_MAX_)
                {
                    printf("\n\rWrite data to flash fail !!! @ %s-%d", __FUNCTION__, __LINE__);
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                printf("\n\rWrite recovery database data to SPI flash finished");

                if(MApp_KeyLogger_GetMode() == EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_DB)
                {
                    MApp_KeyLogger_ModifyConfigBin(EN_KEYLOGGER_MODE_SIMULATING_KEY);

                    printf("\n\rWhole chip reset after database data restored to local TV");
                    MDrv_Sys_WholeChipReset();
                    MDrv_Sys_StopCpu(1);
                }
            }
            else
            {
                printf("\n\r Load database bin fail.");
                _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                break;//return FALSE;
            }
            break;

        case EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH:
        case EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH_ALWAYS_RECOVER:
            //1. Recover flash from USB to flash
            //2. If not always recovery mode, set state to Simulate key, then reboot
            //3. else, go on
            if (_MApp_KeyLogger_GetDataFromBin(EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH, &u32RestoreBufferPhyAddr))
            {
                msAPI_Timer_ResetWDT();
                pU8RestoreBufferCacheVirtualAddr = (U8 *)(MsOS_PA2KSEG0(u32RestoreBufferPhyAddr));
                if(_MApp_KeyLogger_BasicBinValidCheck(pU8RestoreBufferCacheVirtualAddr) == FALSE)
                {
                    printf("\n\r Partial flash bin loaded but invalid.");
                    break;//return FALSE;
                }

                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_BIN_ADDR_OFFSET_), &u32UsbStartOffset);
                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_BIN_LEN_OFFSET_), &u32UsbLength);
                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_FLASH_ADDR_OFFSET_), &u32FlashStartOffset);
                _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_FLASH_LEN_OFFSET_), &u32FlashLength);

                if((u32UsbStartOffset != _KEY_LOGGER_FLASH_BKP_ADDR_OFFSET_)
                    ||(u32UsbLength != _KEY_LOGGER_FLASH_BKP_SIZE_)
                    ||(u32FlashStartOffset != _KEY_LOGGER_FLASH_PARTIAL_BACKUP_FLASH_START_ADDRESS_)
                    ||(u32FlashLength != _KEY_LOGGER_FLASH_BKP_SIZE_)
                    )
                {
                    printf("\n\rFlash backup address or length mismatch between dumped bin and source code %d", __LINE__);
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                if((u32FlashStartOffset%0x10000 != 0) || (u32FlashLength%0x10000 != 0))
                {
                    printf("\n\rFlash backup address not align to 64k byte");
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                if(u32FlashStartOffset+u32FlashLength > FLASH_SIZE)
                {
                    printf("\n\rBackup-ed flash end address over flash size!!!");
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                //ToDo..  If recovery region covers AP are, need to recovery all (partial update is prohibitted)

                printf("\n\rStart to write recovery flash data to SPI flash...");

                for(u8DummyIdx = 0; u8DummyIdx<_KEY_LOGGER_WRITE_BIN_RETRY_TIME_MAX_; u8DummyIdx++)
                {
                    msAPI_Timer_ResetWDT();
                    msAPI_Flash_Set_WriteProtect_Disable_Range( u32FlashStartOffset, u32FlashLength);
                    MDrv_FLASH_AddressErase(u32FlashStartOffset, u32FlashLength, TRUE);
                    msAPI_Flash_WaitWriteDone(5000);
                    if(TRUE == _MApp_KeyLogger_FlashWrite(u32FlashStartOffset, u32FlashLength, (pU8RestoreBufferCacheVirtualAddr+u32UsbStartOffset) ))
                    {
                        //Write data success, normal exit path
                        break;
                    }
                    printf("\n\rWrite data to flash fail, retry count=%d @ %s-%d", u8DummyIdx, __FUNCTION__, __LINE__);
                }
                msAPI_Flash_Set_WriteProtect(ENABLE);

                if(u8DummyIdx >= _KEY_LOGGER_WRITE_BIN_RETRY_TIME_MAX_)
                {
                    printf("\n\rWrite data to flash fail !!! @ %s-%d", __FUNCTION__, __LINE__);
                    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                    break;//return FALSE;
                }

                printf("\n\rWrite recovery flash data to SPI flash finished");

                if(MApp_KeyLogger_GetMode() == EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH)
                {
                    MApp_KeyLogger_ModifyConfigBin(EN_KEYLOGGER_MODE_SIMULATING_KEY);

                    printf("\n\rWhole chip reset after partial flash data restored to local TV");
                    MDrv_Sys_WholeChipReset();
                    //while(1);
                    MDrv_Sys_StopCpu(1);
                }
            }
            else
            {
                printf("\n\r Load partial flash bin fail.");
                _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                break;//return FALSE;
            }

            break;

        default:
            //Do nothing
            break;

    }


    if(_MApp_KeyLogger_IsCurrentSimulatingMode())   //EN_KEYLOGGER_MODE_SIMULATING_KEY / EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_DB_ALWAYS_RECOVER / EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH_ALWAYS_RECOVER
    {
        //Load event db from usb to array
        if (_MApp_KeyLogger_GetDataFromBin(EN_KEYLOGGER_PACK_MODE_KEY_EVENT, &u32RestoreBufferPhyAddr))
        {
            pU8RestoreBufferCacheVirtualAddr = (U8 *)(MsOS_PA2KSEG0(u32RestoreBufferPhyAddr));
            if(_MApp_KeyLogger_BasicBinValidCheck(pU8RestoreBufferCacheVirtualAddr) == FALSE)
            {
                printf("\n\r Event DB bin loaded but invalid.");
                _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
                return FALSE;
            }

            _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_EVENT_LOG_ADDR_OFFSET_), &u32UsbStartOffset);
            _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pU8RestoreBufferCacheVirtualAddr + _KEY_LOGGER_BIN_EVENT_LOG_LEN_OFFSET_), &u32UsbLength);

            //Overwrite event db from USB
            memcpy(&astKeyLogger_EventDb, (pU8RestoreBufferCacheVirtualAddr+u32UsbStartOffset), u32UsbLength);

            _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
            printf("\n\r Event DB loading success!");

            if(_MApp_KeyLogger_CheckActionValid(&astKeyLogger_EventDb[0]) == TRUE)
            {
                bSimulatedKeyWaitingParsed = TRUE;
                u16ActionExecIdx = 0;
                memcpy(&stKeyLogger_Event_OnFire, &astKeyLogger_EventDb[0], sizeof(ST_KEYLOGGER_EVENT));
                u32NextEventExecTime = stKeyLogger_Event_OnFire.u32EventTime;
            }
        }
        else
        {
            printf("\n\r Load event DB bin fail.");
            _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
            return FALSE;
        }

    }

    return TRUE;
}


void MApp_KeyLogger_SetMode(EN_KEYLOGGER_MODE eMode)
{
    if(eMode > EN_KEYLOGGER_MODE_MAX)
        return;

    enKeyLoggerMode = eMode;
    //printf("\n\rMApp_KeyLogger_SetMode = %s", ((enKeyLoggerMode == EN_KEYLOGGER_MODE_SIMULATING) ? "EN_KEYLOGGER_MODE_SIMULATING" : ((enKeyLoggerMode == EN_KEYLOGGER_MODE_LOGGING) ? "EN_KEYLOGGER_MODE_LOGGING" : "EN_KEYLOGGER_MODE_OFF")));
    printf("\n\rMApp_KeyLogger_SetMode = %d", enKeyLoggerMode);
    MApp_KeyLogger_DataReset();
}


EN_KEYLOGGER_MODE MApp_KeyLogger_GetMode(void)
{
    if(stGenSetting.stDebugSetting.bKeyLoggerEnable == FALSE)
    {
        return EN_KEYLOGGER_MODE_OFF;
    }
    else
    {
        return enKeyLoggerMode;
    }
}


BOOL _MApp_KeyLogger_IsCurrentLoggingMode(void)
{
    EN_KEYLOGGER_MODE eMode = MApp_KeyLogger_GetMode();

    if((eMode >= EN_KEYLOGGER_MODE_LOGGING_KEY)
        &&(eMode <= EN_KEYLOGGER_MODE_LOGGING_KEY_PLUS_PARTIAL_FLASH))
    {
        return TRUE;
    }

    return FALSE;
}


BOOL _MApp_KeyLogger_IsCurrentSimulatingMode(void)
{
    EN_KEYLOGGER_MODE eMode = MApp_KeyLogger_GetMode();

    if((eMode >= EN_KEYLOGGER_MODE_SIMULATING_KEY)
        &&(eMode <= EN_KEYLOGGER_MODE_SIMULATING_KEY_PLUS_PARTIAL_FLASH_ALWAYS_RECOVER))
    {
        return TRUE;
    }

    return FALSE;
}


void _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(BOOL bEnable)
{
    if(bEnable)
    {
        MDrv_MIU_UnMaskReq(0, MIU_CLIENT_HVD_RW);
        MDrv_MIU_UnMaskReq(0, MIU_CLIENT_MVD_RW);
        MDrv_MIU_UnMaskReq(0, MIU_CLIENT_MVD_BBU_RW);
        MDrv_MIU_UnMaskReq(0, MIU_CLIENT_RVD_RW);
        MDrv_MIU_UnMaskReq(0, MIU_CLIENT_EVD_RW);
    }
    else
    {
        MDrv_MIU_MaskReq(0, MIU_CLIENT_HVD_RW);
        MDrv_MIU_MaskReq(0, MIU_CLIENT_MVD_RW);
        MDrv_MIU_MaskReq(0, MIU_CLIENT_MVD_BBU_RW);
        MDrv_MIU_MaskReq(0, MIU_CLIENT_RVD_RW);
        MDrv_MIU_MaskReq(0, MIU_CLIENT_EVD_RW);
    }
}


void MApp_KeyLogger_Action_DumpAll(void)
{
    U16 u16DummyIdx = 0;

    printf("\n\r===================================================");
    printf("\n\r======Dump KeyLogger Key-Logger Event Log============");
    printf("\n\r===================================================\n");

    printf("\n\renKeyLoggerMode=%d", enKeyLoggerMode);
    printf("\n\r{");

    for(u16DummyIdx=0; u16DummyIdx<30; u16DummyIdx++)
    {
        msAPI_Timer_Delayms(500);
        msAPI_Timer_ResetWDT();
    }

    for(u16DummyIdx=0; u16DummyIdx<_EVENT_DB_EVENT_MAX_NUM_; u16DummyIdx++)
    {
        //printf("\n\rKeyLogger_EventDb[%d]: Key %x thru %s @ %d. (Crc %x). Valid=%d", u16DummyIdx, astKeyLogger_EventDb[u16DummyIdx].u8EventKeyCode, (astKeyLogger_EventDb[u16DummyIdx].u8EventKeyType ? "IR" : "KeyPad"), astKeyLogger_EventDb[u16DummyIdx].u32EventTime, astKeyLogger_EventDb[u16DummyIdx].u8CrcResult, _MApp_KeyLogger_CheckActionValid(&astKeyLogger_EventDb[u16DummyIdx]));
        printf("\n\r    {0x%02x, 0x%04x, 0x%02x, 0x%02x, 0x%02x},", astKeyLogger_EventDb[u16DummyIdx].u8CrcResult, astKeyLogger_EventDb[u16DummyIdx].u32EventTime, astKeyLogger_EventDb[u16DummyIdx].u8EventKeyCode, astKeyLogger_EventDb[u16DummyIdx].u8EventKeyType, astKeyLogger_EventDb[u16DummyIdx].u8EventKeyRepeat);
        //printf("%02x%08x%02x%02x", astKeyLogger_EventDb[u16DummyIdx].u8CrcResult, astKeyLogger_EventDb[u16DummyIdx].u32EventTime, astKeyLogger_EventDb[u16DummyIdx].u8EventKeyCode, astKeyLogger_EventDb[u16DummyIdx].u8EventKeyType);
        msAPI_Timer_ResetWDT();
    }
    printf("\n\r}");
}


static BOOL _MApp_KeyLogger_CheckActionValid(ST_KEYLOGGER_EVENT* pStEvent)
{
    if(pStEvent == NULL)
        return FALSE;

    if(pStEvent->u32EventTime == 0xFFFFFFFF)
        return FALSE;

    if(pStEvent->u8CrcResult != (U8)((U8)(pStEvent->u32EventTime) + pStEvent->u8EventKeyCode + pStEvent->u8EventKeyType + pStEvent->u8EventKeyRepeat + _EVENT_DB_EVENT_CHECK_SUM_BIAS))
        return FALSE;

    return TRUE;
}


#if (_KEYLOGGER_CAPTURE_BY_SPECIAL_IR_KEY_)
void MApp_KeyLogger_ComboKeyChecker(U8 u8InputKey)
{
    if (u8InputKey >= KEY_0 && u8InputKey <= KEY_9)
    {
        u32ComboKeyBuffer = (u32ComboKeyBuffer<<4)|(u8InputKey-KEY_0);

        //printf("u32ComboKeyBuffer:%x\n",u32ComboKeyBuffer);
        if (u32ComboKeyBuffer > 0x00001984)
        {
            u32ComboKeyBuffer = 0;
        }
    }
    else if(u32ComboKeyBuffer == 0x00001984 && u8InputKey == KEY_GREEN)
    {
        if(g_u16ActionSaveIdx>5)
        {
            g_u16ActionSaveIdx-=5;	//Skip logging last five key --> 1-9-8-4-Green
        }
        MApp_KeyLogger_Encapsulate(EN_KEYLOGGER_PACK_MODE_KEY_EVENT);
        u32ComboKeyBuffer = 0;
    }
    else
    {
        u32ComboKeyBuffer=0;
    }
}
#endif


BOOL MApp_KeyLogger_ModifyConfigBin(EN_KEYLOGGER_MODE eMode)
{
    U8 u8TempBufferForConfigBin[_KEY_LOGGER_CONFIG_BIN_SIZE_] = {0};

    U8 u8HandleNo;
    U8 u8FileName[60] = {0};
    U16 u16FileName[30] = {0};

    u8TempBufferForConfigBin[_KEY_LOGGER_CONFIG_BIN_LOGGERMODE_OFFSET_] = eMode;
    MsOS_Dcache_Flush( ((U32)&u8TempBufferForConfigBin[0]), _KEY_LOGGER_CONFIG_BIN_SIZE_);
    MsOS_FlushMemory();

    strcpy((char *)u8FileName, _KEY_LOGGER_CONFIG_BIN_NAME_);

    //Store data to USB
    if(!MApp_Usb_InitForWrite())
    {
        printf("\n\rUSB init fail");
        return FALSE;
    }

    // step 1  setup environment
    if(MApp_UsbSaveData_SearchFileInRoot(u8FileName, &g_fileEntry_KeyLogger))
    {
        msAPI_FCtrl_FileDelete(&g_fileEntry_KeyLogger);
        printf("Found and Deleted\n");
    }
    else
    {
        printf("Not Found\n");
    }

    // step 2
	ASCIItoUnicode2((S8*)u8FileName, strlen((char *)u8FileName));

    memset(u16FileName, 0, sizeof(u16FileName));

    memcpy(u16FileName, u8FileName, sizeof(u16FileName));

	u8HandleNo = MApp_UsbSaveData_OpenNewFileForWrite((U16 *)u16FileName, UnicodeLen((S8*)u16FileName));

	printf("OpenForWrite Passed\n");

    printf("HandleNo is 0x%x\n",u8HandleNo);
    if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
    {
        printf("start  write\n");
        msAPI_FCtrl_FileWrite(u8HandleNo, _VA2PA((U32)&u8TempBufferForConfigBin[0]), _KEY_LOGGER_CONFIG_BIN_SIZE_);

        printf("Save to file: msAPI_FCtrl_FileClose\n");
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
    else
    {
        printf("\n\rInvalid Handle");
        return FALSE;
    }
    return TRUE;
}

EN_GETCONFIG_RET _MApp_KeyLogger_GetConfigFromUsbBin(U8* pu8Buf, U32 u32Length)
{
    U8 u8HandleNo;
    U8 u8FileName[60] = {0};

    if((pu8Buf == NULL) || (u32Length==0))
    {
        printf("\n\r Invalid input for %s - %d", __FUNCTION__, __LINE__);
    }

    if(!MApp_Usb_InitForWrite())
    {
        //printf("\n\rUSB init fail");
        return EN_GETCONFIG_RETURN_USB_FAIL;
    }

    strcpy((char *)u8FileName, _KEY_LOGGER_CONFIG_BIN_NAME_);

  	if (MApp_UsbSaveData_SearchFileInRoot((U8 *)u8FileName, &g_fileEntry_KeyLogger))
	{
		u8HandleNo = msAPI_FCtrl_FileOpen(&g_fileEntry_KeyLogger, OPEN_MODE_FOR_READ);

        if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
        {
    		//printf("current file is exist\r\n");

            //What i really wanna do here is cache invalidate, but there is no cache invalidate API in system
            //So the only choice is do cache flush, because this is the only API which include invalidate command
            MsOS_Dcache_Flush((U32)pu8Buf, u32Length);

            msAPI_FCtrl_FileRead(u8HandleNo, _VA2PA((U32)pu8Buf), u32Length);

            //printf("Close file: msAPI_FCtrl_FileClose\n");
            msAPI_FCtrl_FileClose(u8HandleNo);
            return EN_GETCONFIG_RETURN_OK;
        }
        else
        {
            //printf("Open file fail\n");
    		return EN_GETCONFIG_RETURN_FILE_NOT_EXIST;
        }
	}
	else
	{
		//printf("file is not exist\r\n");
		return EN_GETCONFIG_RETURN_FILE_NOT_EXIST;
	}
}

//========================================================
//2. Remote TV only function  --> For collect information
//========================================================
BOOL MApp_KeyLogger_Action_Save(U8 u8KeyType, U8 u8KeyCode, BOOL bKeyRepeat)
{
    U32 u32SystemTime = msAPI_Timer_GetTime0();
    U8 u8CheckSum = 0;

    if(_MApp_KeyLogger_IsCurrentLoggingMode() == FALSE)
        return FALSE;

    //Check event db is full or not
    if(g_u16ActionSaveIdx >= _EVENT_DB_EVENT_MAX_NUM_)
    {
        printf("\n\r %s - %s L:%d Event DB full", __FILE__, __FUNCTION__, __LINE__);
        return FALSE;
    }

    //Calculate Check sum
    u8CheckSum = (U8)((U8)u32SystemTime + u8KeyCode + u8KeyType + bKeyRepeat + _EVENT_DB_EVENT_CHECK_SUM_BIAS);

    //Save to event db
    astKeyLogger_EventDb[g_u16ActionSaveIdx].u8CrcResult= u8CheckSum;
    astKeyLogger_EventDb[g_u16ActionSaveIdx].u32EventTime = u32SystemTime;
    astKeyLogger_EventDb[g_u16ActionSaveIdx].u8EventKeyCode = u8KeyCode;
    astKeyLogger_EventDb[g_u16ActionSaveIdx].u8EventKeyType = u8KeyType;
    astKeyLogger_EventDb[g_u16ActionSaveIdx].u8EventKeyRepeat= bKeyRepeat;
    //printf("\n\rastKeyLogger_EventDb[%d]: Key %x thru %s (repeat=%d) @ %d. (Chksum %x). Valid=%d", g_u16ActionSaveIdx, astKeyLogger_EventDb[g_u16ActionSaveIdx].u8EventKeyCode, (astKeyLogger_EventDb[g_u16ActionSaveIdx].u8EventKeyType ? "IR" : "KeyPad"), astKeyLogger_EventDb[g_u16ActionSaveIdx].u8EventKeyRepeat, astKeyLogger_EventDb[g_u16ActionSaveIdx].u32EventTime, astKeyLogger_EventDb[g_u16ActionSaveIdx].u8CrcResult, _MApp_KeyLogger_CheckActionValid(&astKeyLogger_EventDb[g_u16ActionSaveIdx]));

    //Step forward
    g_u16ActionSaveIdx = g_u16ActionSaveIdx+1;

    return TRUE;
}


BOOL MApp_KeyLogger_Encapsulate(EN_KEYLOGGER_PACK_MODE ePackMode)
{
    U8* pu8CaptureBufferAddr = NULL;
    U16 u16Crc = 0;
//    U32 u32DummyIdx = 0;

    U8 u8HandleNo;
    U8 u8FileName[60] = {0};
    U16 u16FileName[30] = {0};

    U32 u32KeyLoggerBinSize = 0, u32EndOfStringOffset = 0;

    if(_MApp_KeyLogger_IsCurrentLoggingMode() == FALSE)
    {
        printf("\n\r!!! KeyLogger is not working in logging mode");
        return FALSE;
    }

    if(ePackMode == EN_KEYLOGGER_PACK_MODE_KEY_EVENT)
    {
        u32KeyLoggerBinSize = _KEY_LOGGER_BIN_HEADER_SIZE_ + _KEY_LOGGER_EVENT_DB_SIZE_ + _KEY_LOGGER_BIN_END_STRING_SIZE_;
    }
    else if (ePackMode == EN_KEYLOGGER_PACK_MODE_DATABASE)
    {
        u32KeyLoggerBinSize = _KEY_LOGGER_BIN_HEADER_SIZE_ + _KEY_LOGGER_DATABASE_SIZE_ + _KEY_LOGGER_BIN_END_STRING_SIZE_;
    }
    else //if (ePackMode == EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH)
    {
        u32KeyLoggerBinSize = _KEY_LOGGER_BIN_HEADER_SIZE_ + _KEY_LOGGER_FLASH_BKP_SIZE_ + _KEY_LOGGER_BIN_END_STRING_SIZE_;
    }
    u32EndOfStringOffset = u32KeyLoggerBinSize - _KEY_LOGGER_BIN_END_STRING_SIZE_;

    if(VDEC_FRAMEBUFFER_LEN < u32KeyLoggerBinSize)
    {
        printf("\n\r!!!Temp buffer size not enough for Capture!!!");
        return FALSE;
    }

    //==========Environment setup====================

    //Disable some HW engine to steal capture buffer
    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(DISABLE);
    msAPI_Timer_Delayms(1);

    pu8CaptureBufferAddr = (U8 *)(MsOS_PA2KSEG0(VDEC_FRAMEBUFFER_ADR));   //Get virtual and cacheable address.
    memset(pu8CaptureBufferAddr, 0, u32KeyLoggerBinSize);



    //==========Packing header - common==============

    //Byte 0~7: Magic number header.
    memcpy(pu8CaptureBufferAddr, &au8KeyLoggerBinHeaderMagicNum[0], 8);

    //Byte 8~9: Crc, calculate and write at the end

    //Byte A~B: Bin version
    *(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_BIN_VER_MAJOR_OFFSET_) = _KEY_LOGGER_VER_MAJOR_;
    *(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_BIN_VER_MINOR_OFFSET_) = _KEY_LOGGER_VER_MINOR_;

    //Byte 0x38~0x3B: Address offset for End String
    _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_BIN_END_STRING_ADDR_OFFSET_, u32EndOfStringOffset);
    //Byte 0x3C~0x3F: Length for End String
    _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_BIN_END_STRING_LEN_OFFSET_, _KEY_LOGGER_BIN_END_STRING_SIZE_);


    //==========Packing header - seperate============
    if(ePackMode == EN_KEYLOGGER_PACK_MODE_KEY_EVENT)
    {
        //Byte 0x10~0x13: Address offset for EventLog
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_EVENT_LOG_ADDR_OFFSET_, _KEY_LOGGER_EVENT_DB_ADDR_OFFSET_);
        //Byte 0x14~0x17: Length for EventLog
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_EVENT_LOG_LEN_OFFSET_, _KEY_LOGGER_EVENT_DB_SIZE_);
    }
    else if (ePackMode == EN_KEYLOGGER_PACK_MODE_DATABASE)
    {
        //Byte 0x18~0x1B: Bin address offset for database
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_DATABASE_BIN_ADDR_OFFSET_, _KEY_LOGGER_DATABASE_ADDR_OFFSET_);
        //Byte 0x1C~0x1F: Bin length for database
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_DATABASE_BIN_LEN_OFFSET_, _KEY_LOGGER_DATABASE_SIZE_);

        //Byte 0x20~0x23: Flash address offset for database
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_DATABASE_FLASH_ADDR_OFFSET_, _KEY_LOGGER_DATABASE_AREA_FLASH_START_ADDRESS_);
        //Byte 0x24~0x27: Flash length for database
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_DATABASE_FLASH_LEN_OFFSET_, _KEY_LOGGER_DATABASE_SIZE_);
    }
    else //if (ePackMode == EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH)
    {
        //Byte 0x28~0x2B: Bin address offset for flash backup
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_BIN_ADDR_OFFSET_, _KEY_LOGGER_FLASH_BKP_ADDR_OFFSET_);
        //Byte 0x2C~0x2F: Bin length for flash backup
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_BIN_LEN_OFFSET_, _KEY_LOGGER_FLASH_BKP_SIZE_);

        //Byte 0x30~0x33: Flash address offset for flash backup
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_FLASH_ADDR_OFFSET_, _KEY_LOGGER_FLASH_PARTIAL_BACKUP_FLASH_START_ADDRESS_);
        //Byte 0x34~0x37: Flash length for flash backup
        _MApp_KeyLogger_DWordArrangeToByte_FromLSB(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_FLASH_BACKUP_FLASH_LEN_OFFSET_, _KEY_LOGGER_FLASH_BKP_SIZE_);
    }


    //==========Packing payload - seperate===========
    if(ePackMode == EN_KEYLOGGER_PACK_MODE_KEY_EVENT)
    {
        memcpy((pu8CaptureBufferAddr + _KEY_LOGGER_EVENT_DB_ADDR_OFFSET_), &astKeyLogger_EventDb, (sizeof(ST_KEYLOGGER_EVENT))*g_u16ActionSaveIdx);
    }
    else if (ePackMode == EN_KEYLOGGER_PACK_MODE_DATABASE)
    {
        MsOS_Dcache_Flush( (U32)pu8CaptureBufferAddr, u32KeyLoggerBinSize);
        MsOS_FlushMemory();

        msAPI_MIU_Copy( _KEY_LOGGER_DATABASE_AREA_FLASH_START_ADDRESS_, // flash addr
                        _VA2PA((U32)(pu8CaptureBufferAddr + _KEY_LOGGER_DATABASE_ADDR_OFFSET_)), // Dram addr
                        _KEY_LOGGER_DATABASE_SIZE_, // copy size
                        MIU_FLASH2SDRAM );
    }
    else //if (ePackMode == EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH)
    {
        MsOS_Dcache_Flush( (U32)pu8CaptureBufferAddr, u32KeyLoggerBinSize);
        MsOS_FlushMemory();

        msAPI_MIU_Copy( _KEY_LOGGER_FLASH_PARTIAL_BACKUP_FLASH_START_ADDRESS_, // flash addr
                        _VA2PA((U32)(pu8CaptureBufferAddr + _KEY_LOGGER_FLASH_BKP_ADDR_OFFSET_)), // Dram addr
                        _KEY_LOGGER_FLASH_BKP_SIZE_, // copy size
                        MIU_FLASH2SDRAM );
    }


    //==========Packing payload - common=============
    //Byte  ~ : Bin end string
    memcpy(pu8CaptureBufferAddr + u32EndOfStringOffset, &au8KeyLoggerBinEndString[0], _KEY_LOGGER_BIN_END_STRING_SIZE_);

    //Byte 8~9: Check Crc
    u16Crc = msAPI_CRC16_Cal(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_BIN_VER_MAJOR_OFFSET_, u32KeyLoggerBinSize - _KEY_LOGGER_BIN_BIN_VER_MAJOR_OFFSET_);
    *(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_CRC_OFFSET_) = (U8)(u16Crc);
    *(pu8CaptureBufferAddr + _KEY_LOGGER_BIN_CRC_OFFSET_ + 1) = (U8)(u16Crc>>8);

    MsOS_Dcache_Flush( (U32)pu8CaptureBufferAddr, u32KeyLoggerBinSize);
    MsOS_FlushMemory();

    if(ePackMode == EN_KEYLOGGER_PACK_MODE_KEY_EVENT)
    {
        strcpy((char *)u8FileName, _KEY_LOGGER_EVENTDB_BIN_NAME_);
    }
    else if (ePackMode == EN_KEYLOGGER_PACK_MODE_DATABASE)
    {
        strcpy((char *)u8FileName, _KEY_LOGGER_DATABASE_BIN_NAME_);
    }
    else //if (ePackMode == EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH)
    {
        strcpy((char *)u8FileName, _KEY_LOGGER_FLASH_BKP_BIN_NAME_);
    }


    //Store data to USB
    if(!MApp_Usb_InitForWrite())
    {
        printf("\n\rUSB init fail");
        _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
        return FALSE;
    }

    // step 1  setup environment
    if(MApp_UsbSaveData_SearchFileInRoot(u8FileName, &g_fileEntry_KeyLogger))
    {
        msAPI_FCtrl_FileDelete(&g_fileEntry_KeyLogger);
        printf("Found and Deleted\n");
    }
    else
    {
        printf("Not Found\n");
    }

    // step 2
	ASCIItoUnicode2((S8*)u8FileName, strlen((char *)u8FileName));

    memset(u16FileName, 0, sizeof(u16FileName));

    memcpy(u16FileName, u8FileName, sizeof(u16FileName));

	u8HandleNo = MApp_UsbSaveData_OpenNewFileForWrite((U16 *)u16FileName, UnicodeLen((S8*)u16FileName));

	printf("OpenForWrite Passed\n");

    printf("HandleNo is 0x%x\n",u8HandleNo);
    if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
    {
        printf("start  write\n");
        msAPI_FCtrl_FileWrite(u8HandleNo, _VA2PA((U32)pu8CaptureBufferAddr), u32KeyLoggerBinSize);

        printf("Save to file: msAPI_FCtrl_FileClose\n");
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
    else
    {
        printf("\n\rInvalid Handle");
        _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
        return FALSE;
    }

    //Recover HW IP
    msAPI_Timer_Delayms(1);
    _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);

    return TRUE;
}


void _MApp_KeyLogger_DWordArrangeToByte_FromLSB(U8* pu8Dst, U32 u32Data)
{
    if(pu8Dst == NULL)
        return;

    *(pu8Dst)   = (U8)(u32Data);
    *(pu8Dst+1) = (U8)(u32Data >> 8);
    *(pu8Dst+2) = (U8)(u32Data >> 16);
    *(pu8Dst+3) = (U8)(u32Data >> 24);
}



//========================================================
//3. Local TV only function   --> For duplicate problem
//========================================================
BOOL MApp_KeyLogger_Action_Task(void)
{
    U16 u16SearchedIdx = 0;

    EN_KEYLOGGER_MODE eMode = MApp_KeyLogger_GetMode();

    if(eMode < EN_KEYLOGGER_MODE_SIMULATING_KEY)
        return FALSE;

    if((bSimulatedKeyWaitingParsed == FALSE)    //No event waiting execution
        &&(bEventExecutionFinished == FALSE)    //Event queue not empty
        )
    {
        if(_MApp_KeyLogger_GetNextEventIdx(u16ActionExecIdx, &u16SearchedIdx))
        {
            bSimulatedKeyWaitingParsed = TRUE;
            u16ActionExecIdx = u16SearchedIdx;
            memcpy(&stKeyLogger_Event_OnFire, &astKeyLogger_EventDb[u16SearchedIdx], sizeof(ST_KEYLOGGER_EVENT));
            u32NextEventExecTime = stKeyLogger_Event_OnFire.u32EventTime;
            return TRUE;
        }
    }

    return FALSE;
}


U8 MApp_KeyLogger_GetSimulatedKey(U8* pU8KeyCode, U8* pU8KeyType, BOOL* pBRepeatKey)
{
    if((pU8KeyCode==NULL) || (pU8KeyType==NULL) || (pBRepeatKey==NULL))
    {
        printf("\n\rInvalid pointer @ Line-%d of %s", __LINE__, __FUNCTION__);
        return MSRET_ERROR;
    }

    if(bSimulatedKeyWaitingParsed
        && (u32NextEventExecTime <= msAPI_Timer_GetTime0())
        )
    {
        //Get Key
        *pU8KeyCode = stKeyLogger_Event_OnFire.u8EventKeyCode;
        *pU8KeyType = stKeyLogger_Event_OnFire.u8EventKeyType;
        *pBRepeatKey = stKeyLogger_Event_OnFire.u8EventKeyRepeat;
        printf("\n\r!!!Got Key!!! Keycode=%x, KeyType=%s", *pU8KeyCode, ((*pU8KeyType) ? "IR" : "KeyPad"));

        //Clear flag
        bSimulatedKeyWaitingParsed = FALSE;

        return MSRET_OK;
    }
    return MSRET_ERROR;
}


static BOOL _MApp_KeyLogger_GetNextEventIdx(U16 u16StartIdx, U16* pu16NextIdx)
{
    U16 u16SearchIdx = 0;

    if(u16StartIdx >= _EVENT_DB_EVENT_MAX_NUM_)
        return FALSE;

    if(pu16NextIdx == NULL)
        return FALSE;

    //printf("\n\r==EventSearch Start===");

    for(u16SearchIdx=u16StartIdx+1; u16SearchIdx<_EVENT_DB_EVENT_MAX_NUM_; u16SearchIdx++)
    {
        //printf(" %d", u16SearchIdx);

        if(u16SearchIdx+1 >= _EVENT_DB_EVENT_MAX_NUM_)  //Last entry of DB, no more valid event
        {
            bEventExecutionFinished = TRUE;
            printf("\n\r########KeyLogger event simulation finished#######");
        }

        if(/*(astKeyLogger_EventDb[u16SearchIdx].u32EventTime != 0xFFFFFFFF)
            &&*/(_MApp_KeyLogger_CheckActionValid(&astKeyLogger_EventDb[u16SearchIdx])))
        {
            *pu16NextIdx = u16SearchIdx;
            //printf("\n\rEvent found = %d!", u16SearchIdx);
            return TRUE;
        }

    }
    //printf("\n\r==EventSearch End===");
    return FALSE;
}


void _MApp_KeyLogger_ReadDWordFromByte_FromLSB(U8* pu8Src, U32* pu32Data)
{
    if((pu8Src == NULL) || (pu32Data == NULL))
        return;

    *(pu32Data) = ((U32)(*(pu8Src+3)))<<24;
    *(pu32Data) |= ((U32)(*(pu8Src+2)))<<16;
    *(pu32Data) |= ((U32)(*(pu8Src+1)))<<8;
    *(pu32Data) |= ((U32)(*(pu8Src  )));
}

//When user enter any key input during simulation, termination simulation
BOOL MApp_KeyLogger_TerminateSimulation(void)
{
    if(MApp_KeyLogger_GetMode() < EN_KEYLOGGER_MODE_SIMULATING_KEY)
        return FALSE;

    if(bSimulationAbortedByUserInput)   //2nd and later termination
        return FALSE;

    bSimulationAbortedByUserInput = TRUE;
    u16ActionExecIdx = _EVENT_DB_EVENT_MAX_NUM_;
    bEventExecutionFinished = TRUE;
    bSimulatedKeyWaitingParsed = FALSE;
    memset(&stKeyLogger_Event_OnFire, 0, sizeof(ST_KEYLOGGER_EVENT));
    printf("\n\rKey logger simulation aborted by user input");
    return TRUE;
}

BOOL _MApp_KeyLogger_GetDataFromBin(EN_KEYLOGGER_PACK_MODE ePackMode, U32* pu32DataPhysicalAddr)
{
    U8 u8FileName[60] = {0};
    U8 u8HandleNo;
    U32 u32FileLength = 0, u32TempBufferAddr=0;

    if(ePackMode == EN_KEYLOGGER_PACK_MODE_KEY_EVENT)
    {
        strcpy((char *)u8FileName, _KEY_LOGGER_EVENTDB_BIN_NAME_);
    }
    else if (ePackMode == EN_KEYLOGGER_PACK_MODE_DATABASE)
    {
        strcpy((char *)u8FileName, _KEY_LOGGER_DATABASE_BIN_NAME_);
    }
    else //if (ePackMode == EN_KEYLOGGER_PACK_MODE_PARTIAL_FLASH)
    {
        strcpy((char *)u8FileName, _KEY_LOGGER_FLASH_BKP_BIN_NAME_);
    }

    //Try to get data from USB.
    if(!MApp_Usb_InitForWrite())
    {
        printf("\n\rUSB init fail");
        return FALSE;
    }

  	if (MApp_UsbSaveData_SearchFileInRoot((U8 *)u8FileName, &g_fileEntry_KeyLogger))
	{
		u8HandleNo = msAPI_FCtrl_FileOpen(&g_fileEntry_KeyLogger, OPEN_MODE_FOR_READ);

        if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
        {
    		printf("current file is exist\r\n");

            u32FileLength = msAPI_FCtrl_FileLength(u8HandleNo);
            printf("\n\ru32FileLength=%d at line %d", u32FileLength, __LINE__);

            if(VDEC_FRAMEBUFFER_LEN < u32FileLength)
            {
                printf("\n\r!!! Temp buffer size not enough for Restore data!!!");
                return FALSE;
            }

            //Disable some HW engine to get capture buffer
            _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(DISABLE);
            msAPI_Timer_Delayms(1);

            u32TempBufferAddr = VDEC_FRAMEBUFFER_ADR;

            MsOS_Dcache_Flush( MsOS_PA2KSEG0(VDEC_FRAMEBUFFER_ADR), u32FileLength);

            msAPI_FCtrl_FileRead(u8HandleNo, VDEC_FRAMEBUFFER_ADR, u32FileLength);

            msAPI_FCtrl_FileClose(u8HandleNo);

            if(pu32DataPhysicalAddr != NULL)
            {
                *pu32DataPhysicalAddr = u32TempBufferAddr;  //Let caller know where to fetch data
            }
            return TRUE;
        }
        else
        {
            //printf("Open file fail\n");
    		return FALSE;
        }
	}
	else
	{
		//printf("database file is not exist\r\n");
		return FALSE;
	}
}

BOOL _MApp_KeyLogger_BasicBinValidCheck(U8* pu8RestoreBufferAddr)
{
    U32 u32DummyIdx = 0, u32EndStringStartOffset = 0, u32BinEnd = 0;
    U16 u16CrcRead = 0, u16CrcCalculated = 0;

    if(pu8RestoreBufferAddr == NULL)
    {
        return FALSE;
    }

    //Check header magic number
    for(u32DummyIdx=0; u32DummyIdx<8; u32DummyIdx++)
    {
        if(*(pu8RestoreBufferAddr+u32DummyIdx) != au8KeyLoggerBinHeaderMagicNum[u32DummyIdx])
        {
            printf("\n\rHeader magic number mismatch!");
            _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
            return FALSE;
        }
    }

    //Check bin version
    if(((*(pu8RestoreBufferAddr + _KEY_LOGGER_BIN_BIN_VER_MAJOR_OFFSET_)) != _KEY_LOGGER_VER_MAJOR_)
        ||((*(pu8RestoreBufferAddr + _KEY_LOGGER_BIN_BIN_VER_MINOR_OFFSET_)) != _KEY_LOGGER_VER_MINOR_))
    {
        printf("\n\rBin file version mismatch!");
        _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
        return FALSE;
    }

    //Check end of bin string
    _MApp_KeyLogger_ReadDWordFromByte_FromLSB((pu8RestoreBufferAddr + _KEY_LOGGER_BIN_BIN_END_STRING_ADDR_OFFSET_), &u32EndStringStartOffset);

    for(u32DummyIdx=0; u32DummyIdx < _KEY_LOGGER_BIN_END_STRING_SIZE_; u32DummyIdx++)
    {
        if(*(pu8RestoreBufferAddr + u32EndStringStartOffset + u32DummyIdx) != au8KeyLoggerBinEndString[u32DummyIdx])
        {
            printf("\n\End of bin string mismatch!");
            _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
            return FALSE;
        }
    }

    //Check Crc
    u32BinEnd = u32EndStringStartOffset + _KEY_LOGGER_BIN_END_STRING_SIZE_;

    u16CrcCalculated = msAPI_CRC16_Cal(pu8RestoreBufferAddr + _KEY_LOGGER_BIN_BIN_VER_MAJOR_OFFSET_, u32BinEnd - _KEY_LOGGER_BIN_BIN_VER_MAJOR_OFFSET_);
    u16CrcRead = (U16)(*(pu8RestoreBufferAddr + _KEY_LOGGER_BIN_CRC_OFFSET_));    //LSB
    u16CrcRead |= (((U16)(*(pu8RestoreBufferAddr + _KEY_LOGGER_BIN_CRC_OFFSET_ + 1))) << 8);    //MSB
    if(u16CrcRead != u16CrcCalculated)
    {
        printf("\n\rCrc check mismatch!");
        _MApp_KeyLogger_TempBufferOwnerWriteRequestEn(ENABLE);
        return FALSE;
    }

    return TRUE;

}

BOOL _MApp_KeyLogger_FlashVerify( U32 u32FlashAddr, U32 u32DataSize, U8* pu8DataBuf)
{
    U8 au8TmpBuf[256];
    U16 i;
    U8* p8DramData;
    U32 u32AddrOffset = 0;
    U16 u16CurCheckSize = 0;

    while( u32AddrOffset < u32DataSize )
    {
        if( (u32DataSize - u32AddrOffset) < 256 )
            u16CurCheckSize = u32DataSize - u32AddrOffset;
        else
            u16CurCheckSize = 256;

        if( FALSE == MDrv_FLASH_Read(u32FlashAddr + u32AddrOffset, u16CurCheckSize, au8TmpBuf) )
        {
            printf("\nError: Verify : Read flash failed @ %s\n", __FUNCTION__);
            return FALSE;
        }

        p8DramData = pu8DataBuf + u32AddrOffset;

        for( i = 0; i < u16CurCheckSize; ++ i )
        {
            if( au8TmpBuf[i] != p8DramData[i] )
            {
                printf("\nError: Verify: data diff at Flash:0x%X. @ %s\n", u32FlashAddr + u32AddrOffset + i, __FUNCTION__);
                return FALSE;
            }
        }

        u32AddrOffset += u16CurCheckSize;
    }

    return TRUE; //Exit with success
}

BOOL _MApp_KeyLogger_FlashWrite(U32 u32StartAddr, U32 u32WriteSize, U8 * user_buffer)
{
    BOOL bRtn;

    bRtn = MDrv_FLASH_Write( u32StartAddr, u32WriteSize, user_buffer );
    if( FALSE == bRtn )
    {
        printf("\nError: MDrv_FLASH_Write failed (0x%X,%u)\n", u32StartAddr, u32WriteSize);
        return FALSE;
    }

    // Verify the data on flash
    bRtn = _MApp_KeyLogger_FlashVerify( u32StartAddr, u32WriteSize, user_buffer);
    if( FALSE == bRtn )
    {
        printf("\nError: Write flash verify failed (0x%X,%u)\n", u32StartAddr, u32WriteSize);
        return FALSE;
    }

    return TRUE;
}
#endif
#undef MAPP_KEYLOGGER_C

