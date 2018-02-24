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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_BL_MAIN_C
#define MAPP_MAIN_C
//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------

#include "Board.h"
#include "datatype.h"

// Common Definition
#include "MsCommon.h"
#include "msAPI_MIU.h"
#include "drvUSB.h"
#include "MApp_USBDownload.h"
#include "Utl.h"
#include "msAPI_Bootloader.h"
#include "MApp_Version.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_FreqTableDTV.h"
#include "MApp_GlobalVar.h"

#if(ENABLE_DTV)
#include "MApp_BL_SI.h"
#include "MApp_BL_Demux.h"
#include "mapp_demux.h"
#endif
#include "MApp_Scan.h"

//------------------------------------------------------------------------------
// Locals
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
extern void MApp_BL_Init(void);
extern U8 MDrv_USBGetPortEnableStatus(void);
#if (ENABLE_BL_UI)
extern void MApp_BL_DisplaySystem(U8 u8Percent);
extern void MApp_BL_DisplaySystem_clear(void);
extern void MApp_BL_DisplaySystem_setStatus(S8 *status);
#else //(ENABLE_BL_UI)
void MApp_BL_DisplaySystem(U8 u8Percent){UNUSED(u8Percent);}
void MApp_BL_DisplaySystem_clear(void){}
void MApp_BL_DisplaySystem_setStatus(S8 *status){UNUSED(status);}
#endif //(ENABLE_BL_UI)

#if ENABLE_OAD
#include "MApp_OAD.h"
#include "mapp_swupdate.h"
#include "msAPI_demux.h"
#include "msAPI_oad_parser.h"
#include "msAPI_oad_process.h"
#include "msAPI_Tuner.h"
#include "msAPI_Timer.h"
#include "imginfo.h"
#endif

#if 1 //add it tmp to pass compiler
U32 u32OadbufAddr = NULL;
U32 u32OadbufSize = NULL;
U8 au8MonitorSection[4096];
U8 au8DownloadSection[4096];

//BOOLEAN bFoundOAD;
//BOOLEAN bNitFoundInvalidOAD;
#endif

#if ENABLE_OAD

#define TUNER_LOCK_TIME_OUT     5000//ms
#define MONITOR_DSI_TIME_OUT    60000//ms
#define MONITOR_DII_TIME_OUT    60000//ms
#define MONITOR_DDB_TIME_OUT    60000*20//ms
#define DOWNLOAD_BUFFER_ADR_OAD     (( DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR))
#define DOWNLOAD_BUFFER_TYPE_OAD     (( DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? MIU_SDRAM12SDRAM0 : MIU_SDRAM2SDRAM)
#define DOWNLOAD_BUFFER_LEN_OAD      DOWNLOAD_BUFFER_LEN
#define VERSION_CHECK 1
#define FLASH_DIRECT_WRITE 0
#define DATA_BC_ID_SSU          0x000A // DVB-SSU
#define DATA_BC_ID_UK_EC        0x0111 // UK Engineering Channel
#define MAX_DDB_MSGSIZE 4066
#define HW_MODEL_VER_CHECK      0
#define DBG_PRINT(x)    //x

#define MAPP_DMX_SET_PID(a,b)   MApp_BL_Dmx_SetFid(a,(EN_BL_FID)b)
#define MAPP_DMX_GET_PID(a)     MApp_BL_Dmx_GetFid((EN_BL_FID)a)
#define MAPP_DMX_GETSI_4K_SECBUFFER()     MApp_BL_Dmx_GetSI4KSectionBuffer()
#define OAD_MONITOR_FID      EN_BL_OAD_MONITOR_FID
#define OAD_DOWNLOAD_FID     EN_BL_OAD_DOWNLOAD_FID

//static U8  _u8OADDownloadFID=MSAPI_DMX_INVALID_FLT_ID;
static U8 versionNum = 0xff ;
static U32 u32ModuleAddr;
static U16 wOad_PID = 0x150;
U8 u8CountryID = 0;
U16 DTVSourceValue=0;

//static U8  _u8OADMonitorFID=MSAPI_DMX_INVALID_FLT_ID;
static U32 tsVersion;

static U32 u32DownloadSize = 0x0;


extern U32 toSaveVersion;

BOOLEAN oad_VersonCheck(U16 type,U8 *pPrivateData)
{
    U16  compatibilityLength,descriptorCount,model,version=0x0,i;
    U8  descriptorType, descriptorLength, specifierType,subDescriptorCount;
    U32 specifierData;
    BOOLEAN swPass=FALSE;
#if HW_MODEL_VER_CHECK
    BOOLEAN hwPass=FALSE;
#endif

    if (!VERSION_CHECK) return TRUE ;

    if (type==DATA_BC_ID_UK_EC) // MIS
    {
        U16 model_hw, version_hw;
        model_hw = GET_2BYTE(&pPrivateData[0]);
        version_hw = GET_2BYTE(&pPrivateData[2]);
        model = msAPI_OAD_GetMISVersionId() >> 16;
        version = msAPI_OAD_GetMISVersionId() & 0xff;
//        model = GET_2BYTE(&pPrivateData[4]);
//        version = GET_2BYTE(&pPrivateData[6]);
#if HW_MODEL_VER_CHECK
        if ((model_hw == HW_MODEL)&&(version_hw == HW_VERSION))
#endif //HW_MODEL_VER_CHECK
        {
            if (model == AP_SW_MODEL)
            {
                tsVersion = (U32)version;
                toSaveVersion = tsVersion;
                return TRUE ;
            }
        }
        return FALSE ;
    }
    else if (type==DATA_BC_ID_SSU) // GroupCompatibility()
    {
        compatibilityLength = GET_2BYTE(pPrivateData);
        pPrivateData += 2;

        if ( compatibilityLength < 2 )
        {
            OAD_ASSERT( printf("Error> msAPI_OAD_ProcessDSI : compatibilityLength = 0x%x\n", compatibilityLength) );
            return FALSE ;
        }

        descriptorCount = GET_2BYTE(pPrivateData); pPrivateData += 2;
        OAD_DEBUG( printf("descriptorCount = %u\n", descriptorCount) );

        for ( i = 0; i < descriptorCount; i ++ )
        {
            descriptorType  = *pPrivateData++;
            descriptorLength= *pPrivateData++;

            switch ( descriptorType )
            {
                case 0x02:
                {
                    specifierType = *pPrivateData++;
                    specifierData = GET_3BYTE( pPrivateData ); pPrivateData += 3;
                    model = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    version = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    subDescriptorCount = *pPrivateData++;
                    tsVersion = (U32)version;
                    OAD_DEBUG( printf("TS=%x\n",tsVersion));
                    if ((specifierType==0x01)&&(model == AP_SW_MODEL)&&(specifierData==CUSTOMER_OUI)) //Do NOT check version
                    {
                        swPass = TRUE;
                    }
                    else
                    {
                        return FALSE ;
                    }
                    //pPrivateData += (descriptorLength-9) ;
                    //OAD_DEBUG( printf("[OTA] specifierType = 0x%02bx, specifierData = 0x%08lx\n", specifierType, specifierData) );
                    break;
                }
                case 0x01:
#if HW_MODEL_VER_CHECK
                    specifierType = *pPrivateData++;
                    specifierData = GET_3BYTE( pPrivateData ); pPrivateData += 3;
                    model = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    version = GET_2BYTE(pPrivateData); pPrivateData += 2;
                    subDescriptorCount = *pPrivateData++;
                    tsVersion = (U32)version;
                    OAD_DEBUG( printf("TS=%x\n",tsVersion));
                    if ((specifierType==0x01)&&(model == HW_MODEL)&&(version == HW_VERSION)&&(specifierData==CUSTOMER_OUI))
                    {
                        hwPass = TRUE;
                    }
                    else
                    {
                        return FALSE ;
                    }
                    //pPrivateData += (descriptorLength-9) ;
                    //OAD_DEBUG( printf("[OTA] specifierType = 0x%02bx, specifierData = 0x%08lx\n", specifierType, specifierData) );
                    break;
#endif
                default:
                {
                    pPrivateData += descriptorLength;
                    OAD_DEBUG( printf("[OTA] descriptorType = 0x%02bx\n", descriptorType) );
                    break;
                }
            }
       }// End of for
    }
#if HW_MODEL_VER_CHECK
    if((swPass == TRUE) && (hwPass == TRUE))
#else //HW_MODEL_VER_CHECK
    if(swPass == TRUE)
#endif //HW_MODEL_VER_CHECK
    {
        toSaveVersion = (U32)version;
        return TRUE ;
    }
    return FALSE ;
}

#endif //ENABLE_OAD

int usb_prepare(void);
int usb_check(void);
int oad_prepare(void);
int oad_check(void);

void sw_update_cb(U8 u8Percent)
{
    if(u8Percent > 100)
        u8Percent = 100;
    MApp_BL_DisplaySystem(u8Percent);
    //printf("%s: u8Percent: %u, at %d\n", __func__, u8Percent, __LINE__);
    return;
}

void debug_print2(void)
{
#if 0
    int j;
    U32 u32Addr_in_dram;
    for (j=0; j < 16; j++)
    {
        u32Addr_in_dram = (DOWNLOAD_BUFFER_ADR_OAD | 0x80000000) + j;
        if (j == 0)
            printf("u32Addr_in_dram = 0x%X\n", u32Addr_in_dram);
        printf("%X ", *(U8 *)(u32Addr_in_dram));
    }
#endif
}

int oad_prepare(void)
{
#if ENABLE_OAD
    MS_TP_SETTING stTempTP;
    stTempTP.u32Frequency = 0; //538000; //722000; //562000; //514000; //482000; //490000; //802000;
    stTempTP.enBandWidth = E_RF_CH_BAND_INVALID; //E_RF_CH_BAND_8MHz;
    stTempTP.u8HpLp = 0x00;

    u32OadbufMonitorAddr = (U32)(((OADSEC_BUFFER_MEMORY_TYPE&MIU1)?OADSEC_BUFFER_ADR|MIU_INTERVAL:OADSEC_BUFFER_ADR)); //(_VA2PA((U32)demuxBuf.monitor)) ;
    u32OadbufDownloadAddr = (U32)(((OADSEC_BUFFER_MEMORY_TYPE&MIU1)?OADSEC_BUFFER_ADR|MIU_INTERVAL:OADSEC_BUFFER_ADR) + 0x4000);//(_VA2PA((U32)demuxBuf.download)) ;
    u32OadbufMonitorSize = DMX_BUF_SIZE_MONITOR;
    u32OadbufDownloadSize = DMX_BUF_SIZE_DOWNLOAD;

    msAPI_OAD_ClearData();
    msAPI_OAD_SetOui((U8)(CUSTOMER_OUI>>16), (U8)(CUSTOMER_OUI>>8), (U8)(CUSTOMER_OUI));
    msAPI_OAD_SetVersionCheck(oad_VersonCheck) ;

    OAD_DEBUG( printf("TV=%x\n",AP_SW_VERSION));

    /* Initial OAD Flag */
    bFoundOAD = FALSE;
    bNitFoundInvalidOAD=FALSE;

    // Get OAD info from EEPROM
    MApp_OAD_GetInfo_BL( &wOad_PID, &(stTempTP.u32Frequency), (U8 *)&(stTempTP.enBandWidth),&u8CountryID,&DTVSourceValue);
    printf("OAD upgrade start, %lu !!\n", stTempTP.u32Frequency);
    printf("OAD upgrade start, wOad_PID: 0x%x !!\n",wOad_PID);
    printf("OAD upgrade start, band: %u !!\n", stTempTP.enBandWidth);
    printf("OAD upgrade start, DTVSource: %u !!\n", DTVSourceValue);
  	if(DTVSourceValue == 0)
  	{
    	msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_SOURCE, E_DEMODULATOR_TYPE_DVBT );
		msAPI_InputSrcType_SetType(MAIN_WINDOW, EN_SYS_INPUT_SOURCE_TYPE_DVBT);
  	}
	else if(DTVSourceValue == 1)
	{
    	msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_SOURCE, E_DEMODULATOR_TYPE_DVBC );
		msAPI_InputSrcType_SetType(MAIN_WINDOW, EN_SYS_INPUT_SOURCE_TYPE_DVBC);
	}
	else
	{
    	msAPI_Demod_Init(E_INIT_DEMOD_FOR_CHANGE_SOURCE, E_DEMODULATOR_TYPE_DVBS_S2 );
		msAPI_InputSrcType_SetType(MAIN_WINDOW, EN_SYS_INPUT_SOURCE_TYPE_S2);
	}

    DBG_PRINT( printf("Line: %d\n", __LINE__) );
    //msAPI_Tuner_Serial_Control(FALSE,FALSE); //no CI
    msAPI_Demod_SetupTSPath(E_DEMOD_TSP_PATH_CASE_NORMAL);
    DBG_PRINT( printf("Line: %d\n", __LINE__) );

    msAPI_Tuner_Tune2RfCh(&stTempTP);
    DBG_PRINT( printf("Line: %d\n", __LINE__) );
#endif //ENABLE_OAD
    return 0;
}

int oad_check()
{
#if ENABLE_OAD
    UINT8 *pu8Buf = NULL;
    OAD_STATUS_REPORT_TYPE ddbStatus ;
    U16 blockID=0,msgLen=0,msgType=0 ;
    U32 msgAddr = 0 ;
    BOOLEAN Check_FE_Result;
    UINT32 u32DsmccTimer=0;
    MS_TP_SETTING stTempTP;
    #if ENABLE_DVB_T2
    U16 wOad_PID_Orig;
    U8 u8Country = 0;
    #endif
    stTempTP.u32Frequency = 0;
    stTempTP.enBandWidth = E_RF_CH_BAND_INVALID;
    stTempTP.u8HpLp = 0x00;

    u32DsmccTimer = msAPI_Timer_GetTime0();
    while(1)
    {
        if( msAPI_Tuner_CheckLock( &Check_FE_Result,FALSE) == FALSE )
        {
            printf("FE Fail!\n");
        }
        else
        {
            if(Check_FE_Result==FE_LOCK)
            {
                printf("FE Locked.\n");
                goto DownloadBLOAD;
            }
            else
            {
                printf("FE Not Locked. Check_FE_Result = %d\n", Check_FE_Result);
            }
        }

        if (msAPI_Timer_DiffTimeFromNow(u32DsmccTimer) > TUNER_LOCK_TIME_OUT)
        {
            OAD_DEBUG( printf("Error> Exit dvbt oad_check\n") );
            //MApp_OAD_SetMonitorState( EN_OAD_MONITOR_STATE_STOP);
		#if ENABLE_DVB_T2
			u32DsmccTimer = msAPI_Timer_GetTime0();
			MAPP_DTV_Scan_T2_DoScan(DVB_T2_DEMOD, TRUE);

			// Get OAD info from EEPROM
			MApp_OAD_GetInfo_BL( &wOad_PID_Orig, &(stTempTP.u32Frequency), (U8 *)&(stTempTP.enBandWidth),&u8Country, &DTVSourceValue);
			printf("oad_check, %lu !!\n", stTempTP.u32Frequency);
			printf("oad_check, wOad_PID_Orig: 0x%x !!\n",wOad_PID_Orig);
			printf("oad_check, band: %u !!\n", stTempTP.enBandWidth);
			msAPI_Tuner_Tune2RfCh(&stTempTP);

			while(1)
			{
				if( msAPI_Tuner_CheckLock( &Check_FE_Result,FALSE) == FALSE )
				{
					printf("FE Fail!\n");
				}
				else
				{
					if(Check_FE_Result==FE_LOCK)
					{
						printf("FE Locked.\n");
						goto DownloadBLOAD;
					}
					else
					{
						printf("FE Not Locked. Check_FE_Result = %d\n", Check_FE_Result);
					}
				}

				if (msAPI_Timer_DiffTimeFromNow(u32DsmccTimer) > TUNER_LOCK_TIME_OUT)
				{
					OAD_DEBUG( printf("Error> Exit dvbt2 oad_check\n") );
					return 1; //return to do USB download
				}
				MsOS_DelayTask(500);
			}
		#endif
            return 1; //return to do USB download
        }
        MsOS_DelayTask(500);

    }

DownloadBLOAD:
    DBG_PRINT( printf("Line: %d\n", __LINE__) );
    if(msAPI_OAD_CreateSectionFilter( MSAPI_DMX_FILTER_TYPE_OAD_MONITOR,OAD_CONTROL_SECTION_TYPE,OAD_DSMCC_MSGID_DSI,
		wOad_PID, MAPP_DMX_GET_PID(OAD_MONITOR_FID), INVALID_VERSION_NUM) == TRUE)
    {
        printf("Create filter: OK.\n");
        printf("DSI _u8OADMonitorFID = %d\n", *MAPP_DMX_GET_PID(OAD_MONITOR_FID));
    }

    DBG_PRINT( printf("Line: %d\n", __LINE__) );

    u32DsmccTimer = msAPI_Timer_GetTime0();
    while(1)
    {
        pu8Buf = msAPI_OAD_PollingSectionFilter(*MAPP_DMX_GET_PID(OAD_MONITOR_FID), MAPP_DMX_GETSI_4K_SECBUFFER());

        if(pu8Buf)
        {
            printf("DSI Poll filter: OK.\n");
            printf("section data = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", pu8Buf[0], pu8Buf[1], pu8Buf[2], pu8Buf[3], pu8Buf[4]);

            if (OAD_SUCCEED==msAPI_OAD_ProcessDSI(pu8Buf))
            {
                u32DsmccTimer = msAPI_Timer_GetTime0();
                versionNum = msAPI_OAD_GetDsiVersionNum() ;

                if (versionNum!=msAPI_OAD_GetDsiVersionNum())
                {
                    printf("versionNum error !!!\n");
                }
                break;
            }
            else
            {
                printf("process DSI error !!!\n");
            }
        }
        else
        {
            printf("No DSI Data!\n");
        }

        if (msAPI_Timer_DiffTimeFromNow(u32DsmccTimer) > MONITOR_DSI_TIME_OUT)
        {
            OAD_DEBUG( printf("Error> Exit DSI\n") );
            //MApp_OAD_SetMonitorState( EN_OAD_MONITOR_STATE_STOP);
            return 1;
        }
        MsOS_DelayTask(100);
    }

    if(msAPI_OAD_CreateSectionFilter( MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD,OAD_CONTROL_SECTION_TYPE,OAD_DSMCC_MSGID_DII,
		wOad_PID, MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID), INVALID_VERSION_NUM) == TRUE)
    {
        printf("\n");
        printf("DII Create filter: OK.\n");
        printf("DII _u8OADDownloadFID = %d\n", *MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID));

        u32DsmccTimer = msAPI_Timer_GetTime0();
    }
    else
    {
        printf("Error> msAPI_OAD_CreateSectionFilter(OAD_CONTROL_SECTION_TYPE) : Invalid FID=%x\n",*MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID));
        return 1;
    }

    while(1)
    {
        pu8Buf = msAPI_OAD_PollingSectionFilter(*MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID), MAPP_DMX_GETSI_4K_SECBUFFER());
        if(pu8Buf)
        {
            if(OAD_SUCCEED==msAPI_OAD_ProcessDII(pu8Buf))
            {
                msAPI_OAD_DeleteSectionFilter(MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID)) ;
                printf("process DII ok\n");
                break;
            }

            if (msAPI_Timer_DiffTimeFromNow(u32DsmccTimer) > MONITOR_DII_TIME_OUT)
            {
                printf("Error> Timeout to receive DII\n");
                return 1;
            }
        }
        //else
            //printf("No DII Data\n");
    }

    if(msAPI_OAD_CreateSectionFilter( MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD,OAD_DATA_SECTION_TYPE ,OAD_DSMCC_MSGID_DDB,
		wOad_PID,MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID), INVALID_VERSION_NUM) == TRUE)
    {
        printf("\n");
        printf("DDB Create filter: OK.\n");
        printf("DDB _u8OADDownloadFID = %d\n", *MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID));

        u32DsmccTimer = msAPI_Timer_GetTime0();
    }
    else
    {
        printf("Error> msAPI_OAD_CreateSectionFilter(OAD_DATA_SECTION_TYPE) : Invalid FID\n");
    }

    MApp_BL_DisplaySystem_clear(); //clear screen
    MApp_BL_DisplaySystem_setStatus((S8*)"DOWNLOAD");
    MApp_BL_DisplaySystem(0);

    while(1)
    {
        msAPI_Timer_ResetWDT();

        pu8Buf = msAPI_OAD_PollingSectionFilter(*MAPP_DMX_GET_PID(OAD_DOWNLOAD_FID), MAPP_DMX_GETSI_4K_SECBUFFER());

        if(pu8Buf)
        {
            ddbStatus = msAPI_OAD_ProcessDDB(pu8Buf,&blockID,&msgLen,&msgAddr,&msgType) ;

            if ((ddbStatus != OAD_FAIL)&&(msgLen))
            {
                if (msgType==OAD_MODE_OBJCAR)
				{
					if (blockID==0)
					{
					#if FLASH_DIRECT_WRITE
						MDrv_FLASH_Write(u32FlashStartAddr, msgLen, (U8*)msgAddr ) ;
					#else
						memcpy((U8*)MsOS_PA2KSEG1(DOWNLOAD_BUFFER_ADR_OAD),(U8*)msgAddr,(U32)msgLen) ;
					#endif
					}
					else
					{
					#if FLASH_DIRECT_WRITE
						MDrv_FLASH_Write(u32FlashStartAddr+(blockID*msAPI_OAD_GetBlockSize())-BIOP_HEADER_LEN, msgLen, (U8*)msgAddr ) ;
					#else
						memcpy((U8*)MsOS_PA2KSEG1(DOWNLOAD_BUFFER_ADR_OAD+(blockID*msAPI_OAD_GetBlockSize())-BIOP_HEADER_LEN),(U8*)msgAddr,(U32)msgLen) ;
					#endif
					}

				}
                else if (msgType==OAD_MODE_DATACAR)
				{
				#if FLASH_DIRECT_WRITE
					MDrv_FLASH_Write(u32FlashStartAddr+(blockID*msAPI_OAD_GetBlockSize()), msgLen, (U8*)msgAddr ) ;
				#else
					memcpy((U8*)MsOS_PA2KSEG1(DOWNLOAD_BUFFER_ADR_OAD+(blockID*msAPI_OAD_GetBlockSize())),(U8*)msgAddr,(U32)msgLen) ;
				#endif
				}
               u32DownloadSize += msgLen ;
            }

            if (ddbStatus == OAD_COMPLETE)
            {
            #if 0//OAD_TEST
             #if FLASH_DIRECT_WRITE
              #if 0
                MDrv_Sys_SetWatchDogTimer(0);
                MDrv_Sys_EnableWatchDog();
                while(1); // reset
              #else
                msAPI_BLoader_Reboot();
              #endif // #if 0
             #else // #if FLASH_DIRECT_WRITE
                printf("line %d\n", __LINE__);
                cp_debug_print();
                MApp_SwUpdate_Start( SW_UPDATE_MODE_PARTIAL_OAD,FALSE, FALSE, FALSE,DOWNLOAD_BUFFER_ADR_OAD,u32DownloadSize,DOWNLOAD_BUFFER_TYPE_OAD, FALSE);
             #endif // #if FLASH_DIRECT_WRITE
            #else // #if OAD_TEST

                //MApp_OAD_SetDownloadState(EN_OAD_DOWNLOAD_STATE_DDB_COMPLETED) ;
                printf("DDB complete.\n");

            #endif // #if OAD_TEST

            #if FLASH_DIRECT_WRITE
                MDrv_FLASH_WriteProtect(ENABLE) ;
            #endif

                break;
            }
        }

        {
            static U8 u8PrevPersentage=0;
            U8 u8Percentage = MApp_OAD_GetProgress();
            if (u8Percentage > 100)
                u8Percentage = 100;
            //if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_DOWNLOADING )
            if(u8PrevPersentage != u8Percentage)
            {
                u8PrevPersentage = u8Percentage;
                MApp_BL_DisplaySystem(u8Percentage);
                //printf("u8Percentage: %u, at %d\n", u8Percentage, __LINE__);
            }
        }

        if (msAPI_Timer_DiffTimeFromNow(u32DsmccTimer) > MONITOR_DDB_TIME_OUT)
        {
            OAD_DEBUG( printf("Error> Exit DDB\n") );
            printf("DDB timeout!\n");

            return 1;
        }
    }
    MApp_BL_DisplaySystem(100);
    printf("\nOAD Finished\n");

    msAPI_OAD_GetModuleInfo( &u32ModuleAddr, &u32DownloadSize );
    printf("u32ModuleAddr %d, u32DownloadSize %d\n", u32ModuleAddr, u32DownloadSize);
    printf("DOWNLOAD_BUFFER_ADR_OAD 0x%X, DOWNLOAD_BUFFER_LEN_OAD 0x%X\n", DOWNLOAD_BUFFER_ADR_OAD, DOWNLOAD_BUFFER_LEN_OAD);

    debug_print2();

    MApp_BL_DisplaySystem_clear(); //clear screen
    MApp_BL_DisplaySystem_setStatus((S8*)"Software Update(OAD)");
    MApp_BL_DisplaySystem(0);

    if (MApp_SwUpdate_Start( SW_UPDATE_MODE_PARTIAL_OAD,FALSE, FALSE, FALSE,DOWNLOAD_BUFFER_ADR_OAD,u32DownloadSize,DOWNLOAD_BUFFER_TYPE_OAD, FALSE))
        return 0;
#endif //ENABLE_OAD
    return 0;
}

int usb_prepare(void)
{
    return 0;
}

int usb_check(void)
{
    U8 u8PortEnStatus = 0;

    //USB init
    MDrv_UsbDeviceConnect();
    MDrv_UsbDeviceConnect_Port2();
    MsOS_DelayTask(500);

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    //printf("u8PortEnStatus = %d\n", u8PortEnStatus);

    MDrv_Sys_ClearWatchDog();

    if((u8PortEnStatus & BIT0) == BIT0)
    {
        if (!MDrv_UsbDeviceConnect())
        {
            //if((u8PortEnStatus & BIT1) != BIT1)
            {
                printf("USB Port1 is Not detected!\n");
            }
        }
        else
        {
            printf("USB Port1 is detected.\n");

            MApp_UsbDownload_Init(BIT0, sw_update_cb);

            if (MW_UsbDownload_Search())
            {
                printf("updated file in USB is found.\n");

                MApp_BL_DisplaySystem_clear(); //clear screen
                MApp_BL_DisplaySystem_setStatus((S8*)"Software Update(USB)");
                MApp_BL_DisplaySystem(0);
                MW_UsbDownload_Start();

                //MDrv_MIU_SPI_SetOffset(0LU);
                MDrv_Sys_SetWatchDogTimer(0);
                MDrv_Sys_EnableWatchDog();

                while(1);   // Necessary because of using watch dog reset
                //break;
            }
            else //no sw file detected
            {
                if((u8PortEnStatus & BIT1) != BIT1)
                {
                    printf("No updated file in USB is found!\n");
                }
            }
        }
    }
    else
    {
        printf(".");
    }

    if((u8PortEnStatus & BIT1) == BIT1)
    {
        if (!MDrv_UsbDeviceConnect_Port2())
        {
            //if((u8PortEnStatus & BIT1) != BIT1)
            {
                printf("USB Port2 is Not detected!\n");
            }
        }
        else
        {
            printf("USB Port2 is detected.\n");

            MApp_UsbDownload_Init(BIT1, sw_update_cb);

            if (MW_UsbDownload_Search())
            {
                printf("updated file in USB is found.\n");

                MApp_BL_DisplaySystem_clear(); //clear screen
                MApp_BL_DisplaySystem_setStatus((S8*)"Software Update(USB)");
                MApp_BL_DisplaySystem(0);
                MW_UsbDownload_Start();

                //MDrv_MIU_SPI_SetOffset(0LU);
                MDrv_Sys_SetWatchDogTimer(0);
                MDrv_Sys_EnableWatchDog();

                while(1);   // Necessary because of using watch dog reset
                //break;
            }
            else //no sw file detected
            {
                if((u8PortEnStatus & BIT0) != BIT0)
                {
                    printf("No updated file in USB is found!\n");
                }
            }
        }
    }
    else
    {
        printf(".");
    }

    return 0;
}

void main_loop(void)
{
#if (ENABLE_BL_OAD_SCAN)
    EN_OAD_SCAN_STATE scanState, preState=STATE_OAD_SCAN_END ;
    U8 u8Percentage=0;
    U16 wOad_PID_Orig;
    MS_TP_SETTING stOrigTP;
    static BOOLEAN bUseDefaultCountry = FALSE; // Use country setting in database for the first scan/loop
    U8 u8Country = 0;
	U16 DTVSource = 0;

    MApp_BL_DisplaySystem_clear(); //clear screen
    MApp_BL_DisplaySystem_setStatus((S8*)"SCAN");
    MApp_BL_DisplaySystem(0);

    {
        DBG_PRINT( printf("goto usb_check() !! at %d\n", __LINE__) );
        usb_check();

        MApp_OAD_GetInfo_BL( &wOad_PID_Orig, &(stOrigTP.u32Frequency), (U8 *)&(stOrigTP.enBandWidth),&u8Country,&DTVSource);
        DBG_PRINT( printf("OAD upgrade start, PID : 0x%x !!\n", wOad_PID_Orig) );
        DBG_PRINT( printf("OAD upgrade start, freq: %lu !!\n", stOrigTP.u32Frequency) );
        DBG_PRINT( printf("OAD upgrade start, band: %u !!\n", (U8)stOrigTP.enBandWidth) );
        DBG_PRINT( printf("goto oad_check() !! at %d\n", __LINE__) );
        oad_check();
        //TODO: if OADInfo valid
        MApp_BL_DisplaySystem_setStatus((S8*)"SCAN");
    }

    // Use DEFAULT_COUNTRY for OAD scan
    if((bUseDefaultCountry == TRUE) && (DEFAULT_COUNTRY != msAPI_CM_GetCountry()))
    {
        msAPI_CM_SetCountry(DEFAULT_COUNTRY); //TODO: consider general case
    }
    else
    {
        // when data base is empty, set UK as default country.
        if((u8Country == 0x00)&&(stOrigTP.u32Frequency == 0x00)&&(stOrigTP.enBandWidth == 0x00))
        {
            u8Country = E_UK;
        }
    	 msAPI_CM_SetCountry((MEMBER_COUNTRY)u8Country);
    }
    MApp_OAD_Init();
    MApp_OAD_Monitor();
    while(1)
    {
#if ENABLE_ATSC
            scanState = MApp_OAD_Scan_BL_ATSC(&u8Percentage) ;
#else
        scanState = MApp_OAD_Scan(&u8Percentage) ;
#endif

        MApp_BL_DisplaySystem(u8Percentage);
        if(scanState==STATE_OAD_SCAN_NEXT_CHANNEL)
        {
            //Check usb if switch to next channel. (shorter time gap to check usb)
            //DBG_PRINT( printf("goto usb_check() !! at %d\n", __LINE__) );
            //usb_check();
        }
        else if (scanState==STATE_OAD_SCAN_END)
        {
            MS_TP_SETTING stTempTP;
            MApp_OAD_GetInfo_BL( &wOad_PID, &(stTempTP.u32Frequency), (U8 *)&(stTempTP.enBandWidth), &u8Country,&DTVSource);
            DBG_PRINT( printf("OAD upgrade start, PID : 0x%x !!\n", wOad_PID) );
            DBG_PRINT( printf("OAD upgrade start, freq: %lu !!\n", stTempTP.u32Frequency) );
            DBG_PRINT( printf("OAD upgrade start, band: %u !!\n", (U8)stTempTP.enBandWidth) );
            if((wOad_PID == wOad_PID_Orig) &&
                (stTempTP.u32Frequency == stOrigTP.u32Frequency) &&
                ((U8)stTempTP.enBandWidth == (U8)stOrigTP.enBandWidth)) //OAD Scan finds no OAD information available
                break;
            DBG_PRINT( printf("goto oad_check() !! at %d\n", __LINE__) );
            oad_check();
            break ;
        }
        if(preState != scanState)
        {
            preState = scanState;
            printf("u8Percentage: %u, scanState: %x, at %d\n", u8Percentage, scanState, __LINE__);
        }
        MsOS_DelayTask(25);
        MApp_OAD_Monitor();
        MsOS_DelayTask(25);
    }
    bUseDefaultCountry = TRUE; // Always use DEFAULT_COUNTRY after the first scan/loop
#else //(ENABLE_BL_OAD_SCAN)
    usb_check();
    oad_check();
#endif //(ENABLE_BL_OAD_SCAN)
}

int main(void)
{
    printf("Init.");
    MApp_BL_Init();

    printf("prepare USB/OAD upgrade !!\n");
    MDrv_Sys_ClearWatchDog();

    usb_prepare();

#if ENABLE_OAD
    oad_prepare();
#endif

    {
        MApp_UsbDownload_Init(0, sw_update_cb); // register callback for sw upgrade
    }

    MApp_BL_DisplaySystem_clear(); //clear screen
    MApp_BL_DisplaySystem(0);

    while(1)
    {
        main_loop();
    }

    return 0;
}

#undef MAPP_BL_MAIN_C

