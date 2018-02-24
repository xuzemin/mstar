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
/*************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 1 API
   API functions definitions used by commands and properties
   FILE: Si2158_L1_API.c
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_1_build_9
   Revision: 0.1
   Tag:  ROM33_2_1_build_9_V0.1
   Date: March 20 2013
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
// #define   Si2158_COMMAND_PROTOTYPES

#include "Si2158_L1_API.h"

/*chip rev constants for integrity checking */
const char Si2158_chiprev          =  1;
/* Last 2 digits of part number */
const char Si2158_part             =  58; /* Change this value if using a chip other than a Si2158 */
const char Si2158_partMajorVersion = '2';
const char Si2158_partMinorVersion = '0';
const char Si2158_partRomid        =  0x33;


/***********************************************************************************************************************
  Si2158_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si2158 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2158_L1_API_Init      (L1_Si2158_Context *api, int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd    = &(api->cmdObj);
    api->rsp    = &(api->rspObj);
    api->prop   = &(api->propObj);
    api->status = &(api->statusObj);

    api->part             = Si2158_part;
    api->chiprev          = Si2158_chiprev;
    api->partMajorVersion = Si2158_partMajorVersion;
    api->partMinorVersion = Si2158_partMinorVersion;
    api->partRomid        = Si2158_partRomid;

    return NO_Si2158_ERROR;
}
/***********************************************************************************************************************
  Si2158_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2158. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si2158_L1_API_Patch     (L1_Si2158_Context *api, int iNbBytes, unsigned char *pucDataBuffer) {
    unsigned char res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2158 Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2158_L1_API_Patch error 0x%02x writing bytes: %s\n", res, Si2158_L1_API_ERROR_TEXT(res) );
      return res;
    }

    res = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2158_ERROR) {
      SiTRACE("Si2158_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2158_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2158_POLLING_RESPONSE;
    }

    return NO_Si2158_ERROR;
}
/***********************************************************************************************************************
  Si2158_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si2158_L1_CheckStatus   (L1_Si2158_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2158_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2158_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2158_L1_API_ERROR_TEXT(unsigned char error_code) {
    switch (error_code) {
        case NO_Si2158_ERROR                     : return (char *)"No Si2158 error";
        case ERROR_Si2158_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2158 context";
        case ERROR_Si2158_PARAMETER_OUT_OF_RANGE : return (char *)"Si2158 parameter(s) out of range";
        case ERROR_Si2158_SENDING_COMMAND        : return (char *)"Error while sending Si2158 command";
        case ERROR_Si2158_CTS_TIMEOUT            : return (char *)"Si2158 CTS timeout";
        case ERROR_Si2158_ERR                    : return (char *)"Si2158 Error (status 'err' bit 1)";
        case ERROR_Si2158_POLLING_CTS            : return (char *)"Si2158 Error while polling CTS";
        case ERROR_Si2158_POLLING_RESPONSE       : return (char *)"Si2158 Error while polling response";
        case ERROR_Si2158_LOADING_FIRMWARE       : return (char *)"Si2158 Error while loading firmware";
        case ERROR_Si2158_LOADING_BOOTBLOCK      : return (char *)"Si2158 Error while loading bootblock";
        case ERROR_Si2158_STARTING_FIRMWARE      : return (char *)"Si2158 Error while starting firmware";
        case ERROR_Si2158_SW_RESET               : return (char *)"Si2158 Error during software reset";
        case ERROR_Si2158_INCOMPATIBLE_PART      : return (char *)"Si2158 Error Incompatible part";
/* _specific_error_text_string_insertion_start */
        case ERROR_Si2158_TUNINT_TIMEOUT         : return (char *)"Si2158 Error TUNINT Timeout";
        case ERROR_Si2158_xTVINT_TIMEOUT         : return (char *)"Si2158 Error xTVINT Timeout";
        case ERROR_Si2158_CRC_CHECK_ERROR        : return (char *)"Si2158 Error CRC Check Error";
/* _specific_error_text_string_insertion_point */
        default                                  : return (char *)"Unknown Si2158 error code";
    }
}
/***********************************************************************************************************************
  Si2158_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2158_L1_API_TAG_TEXT(void) { return (char *)"ROM33_2_1_build_9_V0.1";}

/* _specific_code_insertion_start */
/* _specific_code_insertion_point */





