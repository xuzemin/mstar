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
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
///////////////////////////////////////////////////////////////////////////////

#ifndef _MSAPI_CI_H_
#define _MSAPI_CI_H_

/*****************************************************************************/
/*                      API Layer                                            */
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*                      Macro                                                */
/*****************************************************************************/
#ifndef GIT_COMMIT
#define GIT_COMMIT "emptyGitCommit"
#endif
#define STRINGIFY(x) #x
#define MACRO(x) STRINGIFY(x)

#define CI_PLUS_FUNCTION_ENABLE         1
#define CI_PLUS_FUNCTION_V1_3_ENABLE    1
#define CI_PLUS_FUNCTION_V1_4_ENABLE    1

#define MSIF_CI_TAG         {'M', 'S', 'I', 'F'}    //Version ID header
#define MSIF_CI_CLASS       {'0', '3'}              //info Class code a 00:driver, 02:app, 03:mw
#define MSIF_CI_CUS         0x6666                  //Customer ID : defaulta internal
#define MSIF_CI_MOD         0x6666                  //Module ID : default
#define MSIF_CI_CHIP        0X000B                  //CHIP ID :  T3
#define MSIF_CI_CPU         '1'                     //CPU : 0:mips 1:aeon
#if CI_PLUS_FUNCTION_V1_4_ENABLE
#define MSIF_CI_LIB_CODE    {'C', 'I', '1', '4'}    //Lib code
#elif CI_PLUS_FUNCTION_V1_3_ENABLE
#define MSIF_CI_LIB_CODE    {'C', 'I', '1', '3'}    //Lib code
#elif CI_PLUS_FUNCTION_ENABLE
#define MSIF_CI_LIB_CODE    {'C', 'I', '1', '2'}    //Lib code
#endif
#define MSIF_CI_LIBVER      {'0', '0'}              //LIB version
#define MSIF_CI_BUILDNUM    {'0', '0'}              //Build Number
#define MSIF_CI_COMMIT      MACRO(GIT_COMMIT)       //Git commit ID (8 digits)
#define MSIF_CI_OS          '0'                     //OS 0:StateMachine 1:eCos 2:Linux

#define BUF_ID_CI_LIB       200

#define CI_VER              /* Character String for DRV/API version */  \
    MSIF_CI_TAG,            /* 'MSIF' */                                \
    MSIF_CI_CLASS,          /* '00'  */                                 \
    MSIF_CI_CUS,            /* 0x0000 */                                \
    MSIF_CI_MOD,            /* 0x0000 */                                \
    MSIF_CI_CHIP,                                                       \
    MSIF_CI_CPU,                                                        \
    MSIF_CI_LIB_CODE,       /* IP */                                    \
    MSIF_CI_LIBVER,         /* 00 ~ 99 */                               \
    MSIF_CI_BUILDNUM,       /* 00 ~ 99 */                               \
    MSIF_CI_COMMIT,         /* Git commit ID (8 digits)# */             \
    MSIF_CI_OS

//**** Resource define  **** //
#define ENABLE_CI_RESOURCE_MANGAER_V2   1
#define ENABLE_CI_APPINFO_V2            1
#define ENABLE_CI_CAS                   1
#define ENABLE_CI_HC                    1   // For CU, the host must support HC
#define ENABLE_CI_DT                    1
#define ENABLE_CI_MMI                   1
#define ENABLE_CI_LSC                   0
#define ENABLE_CI_APPMMI                1
#define ENABLE_CI_COPYPROTECTION        0

#if CI_PLUS_FUNCTION_ENABLE
#if CI_PLUS_FUNCTION_V1_4_ENABLE
#define ENABLE_CI_APPINFO_V3            1
#define ENABLE_CI_APPINFO_V5            1
#define ENABLE_CI_HC_V2                 1
#define ENABLE_CI_HC_V3                 1
#define ENABLE_CI_LSC_V2                0 // NonOS Not Support
#define ENABLE_CI_LSC_V3                0 // NonOS Not Support
#define ENABLE_CI_LSC_V4                0 // NonOS Not Support
#define ENABLE_CI_CC                    1
#define ENABLE_CI_CC_V2                 1
#define ENABLE_CI_CC_V4                 1
#define ENABLE_CI_HLC                   1
#define ENABLE_CI_CU                    1
#define ENABLE_CI_OP                    1
#define ENABLE_CI_OP_V2                 1
#define ENABLE_CI_SAS                   0 // NonOS Not Support
#define ENABLE_CI_APPMMI_V2             1
#define ENABLE_CI_APPMMI_V3             1
#define ENABLE_CI_HSS                   1
#define ENABLE_CI_AUTH                  1
#elif CI_PLUS_FUNCTION_V1_3_ENABLE
#define ENABLE_CI_APPINFO_V3            1
#define ENABLE_CI_APPINFO_V5            0
#define ENABLE_CI_HC_V2                 1
#define ENABLE_CI_HC_V3                 0
#define ENABLE_CI_LSC_V2                0 // NonOS Not Support
#define ENABLE_CI_LSC_V3                0 // NonOS Not Support
#define ENABLE_CI_LSC_V4                0 // NonOS Not Support
#define ENABLE_CI_CC                    1
#define ENABLE_CI_CC_V2                 1
#define ENABLE_CI_CC_V4                 0
#define ENABLE_CI_HLC                   1
#define ENABLE_CI_CU                    1
#define ENABLE_CI_OP                    1
#define ENABLE_CI_OP_V2                 0
#define ENABLE_CI_SAS                   0 // NonOS Not Support
#define ENABLE_CI_APPMMI_V2             1
#define ENABLE_CI_APPMMI_V3             0
#define ENABLE_CI_HSS                   1
#define ENABLE_CI_AUTH                  1
#else
#define ENABLE_CI_APPINFO_V3            1
#define ENABLE_CI_APPINFO_V5            0
#define ENABLE_CI_HC_V2                 0
#define ENABLE_CI_HC_V3                 0
#define ENABLE_CI_LSC_V2                0 // NonOS Not Support
#define ENABLE_CI_LSC_V3                0 // NonOS Not Support
#define ENABLE_CI_LSC_V4                0 // NonOS Not Support
#define ENABLE_CI_CC                    1
#define ENABLE_CI_CC_V2                 0
#define ENABLE_CI_CC_V4                 0
#define ENABLE_CI_HLC                   1
#define ENABLE_CI_CU                    1
#define ENABLE_CI_OP                    0
#define ENABLE_CI_OP_V2                 0
#define ENABLE_CI_SAS                   0 // NonOS Not Support
#define ENABLE_CI_APPMMI_V2             0
#define ENABLE_CI_APPMMI_V3             0
#define ENABLE_CI_HSS                   1
#define ENABLE_CI_AUTH                  1
#endif
#else
#define ENABLE_CI_APPINFO_V3            0
#define ENABLE_CI_APPINFO_V5            0
#define ENABLE_CI_HC_V2                 0
#define ENABLE_CI_HC_V3                 0
#define ENABLE_CI_LSC_V2                0 // NonOS Not Support
#define ENABLE_CI_LSC_V3                0 // NonOS Not Support
#define ENABLE_CI_LSC_V4                0 // NonOS Not Support
#define ENABLE_CI_CC                    0
#define ENABLE_CI_CC_V2                 0
#define ENABLE_CI_CC_V4                 0
#define ENABLE_CI_HLC                   0
#define ENABLE_CI_CU                    0
#define ENABLE_CI_OP                    0
#define ENABLE_CI_OP_V2                 0
#define ENABLE_CI_SAS                   0 // NonOS Not Support
#define ENABLE_CI_APPMMI_V2             0
#define ENABLE_CI_APPMMI_V3             0
#define ENABLE_CI_HSS                   0
#define ENABLE_CI_AUTH                  0
#endif

//If customer want to pass Canal Ready Certification, they should enable this flag and set authentication bin into CI library.
//**** Resource define end ******//

// Application type
#define CI_APPLITYPE_CA     0x01
#define CI_APPLITYPE_EPG    0x02
#define CI_APPLITYPE_UND    0xFF

#define AES_DECRYPT         0
#define AES_ENCRYPT         1

#define SECONDS_PER_MIN     60L
#define SECONDS_PER_HOUR    3600L
#define SECONDS_PER_DAY     86400L

#if ENABLE_CI_CC
#define CI_CC_KEY_NUM                                   5
#define CC_AUTH_MAX_CREDENTIAL_SIZE                     (0x2000)
#define CC_AUTH_MAX_ROOT_CERT_SIZE                      (0x600)
#define CC_AUTH_MAX_DEVICE_CERT_SIZE                    (0x600)
#define CC_AUTH_MAX_BRAND_CERT_SIZE                     (0x600)
#define CC_AUTH_MAX_DEVICE_KEY_CERT_SIZE                (0x600)
#define CC_AUTH_PRNG_SEED_SIZE                          (128 >> 3)
#define CC_AUTH_NONCE_SIZE                              (256 >> 3)
#define CC_AUTH_DH_EXPONENT_SIZE                        (2048 >> 3)
#define CC_AUTH_DHPH_SIZE                               CC_AUTH_DH_EXPONENT_SIZE
#define CC_AUTH_DHPM_SIZE                               CC_AUTH_DH_EXPONENT_SIZE
#define CC_AUTH_DHSK_SIZE                               CC_AUTH_DH_EXPONENT_SIZE
#define CC_AUTH_DHSK_TAIL_SIZE                          (128 >> 3)
#define CC_AUTH_DH_P_SIZE                               CC_AUTH_DH_EXPONENT_SIZE
#define CC_AUTH_DH_G_SIZE                               CC_AUTH_DH_EXPONENT_SIZE
#define CC_AUTH_DH_Q_SIZE                               (256 >> 3)
#define CC_AUTH_SIGNATURE_SIZE                          (2048 >> 3)
#define CC_AUTH_SHA1_HASH_SIZE                          (160 >> 3)
#define CC_AUTH_SHA256_HASH_SIZE                        (256 >> 3)
#define CC_AUTH_MD5_HASH_SIZE                           (128 >> 3)
#define CC_AUTH_NS_SIZE                                 (64 >> 3)
#define CC_AUTH_ID_SIZE                                 (64 >> 3)
#define CC_AUTH_KEY_REGISTER_SIZE                       (8 >> 3)
#define CC_AUTH_AKH_SIZE                                (256 >> 3)
#define CC_AUTH_AKM_SIZE                                (256 >> 3)
#define CC_AUTH_VERSION_SIZE                            (8 >> 3)
#define CC_AUTH_MSG_LABEL_SIZE                          (8 >> 3)
#define CC_AUTH_KP_SIZE                                 (256 >> 3)
#define CC_AUTH_STATUS_SIZE                             (8 >> 3)
#define CC_AUTH_KS_SIZE                                 (256 >> 3)
#define CC_AUTH_AES_128_KEY_SIZE                        (128 >> 3)
#define CC_AUTH_AES_128_IV_SIZE                         (128 >> 3)
#define CC_AUTH_SEK_SIZE                                CC_AUTH_AES_128_KEY_SIZE
#define CC_AUTH_SAK_SIZE                                CC_AUTH_AES_128_KEY_SIZE
#define CC_AUTH_SIV_SIZE                                CC_AUTH_AES_128_IV_SIZE
#define CC_AUTH_SLK_SIZE                                (128 >> 3)
#define CC_AUTH_CLK_SIZE                                (128 >> 3)
#define CC_AUTH_DES_CCK_SIZE                            (64 >> 3)
#define CC_AUTH_AES_CCK_SIZE                            CC_AUTH_AES_128_KEY_SIZE
#define CC_AUTH_AES_CIV_SIZE                            CC_AUTH_AES_128_IV_SIZE
#define CC_AUTH_URI_CONFIRM_SIZE                        (256 >> 3)
#define CC_AUTH_URI_VERSION_SIZE                        (256 >> 3)
#define CC_AUTH_URI_SIZE                                (64 >> 3)
#define CC_AUTH_SAC_AUTH_SIZE                           (16)
#define CC_AUTH_PROGRAM_NUMBER_SIZE                     (16 >> 3)
#define CC_AUTH_RSA_M_N_SIZE                            (256)
#define CC_AUTH_RSA_M_E_SIZE                            (3)
#define CC_AUTH_RSA_N_SIZE                              (256)
#define CC_AUTH_RSA_E_SIZE                              (3)
#define CC_AUTH_RSA_D_SIZE                              (256)
#define CC_AUTH_RSA_P_SIZE                              (128)
#define CC_AUTH_RSA_Q_SIZE                              (128)
#define CC_AUTH_RSA_DP_SIZE                             (128)
#define CC_AUTH_RSA_DQ_SIZE                             (128)
#define CC_AUTH_RSA_QP_SIZE                             (128)
#define CC_AUTH_LICENSE_RCVD_STATUS_SIZE                (8 >> 3)
#define CC_AUTH_OPERATING_MODE_SIZE                     (8 >> 3)
#define CC_AUTH_SRM_CNF_SIZE                            (256 >> 3)
#define CC_AUTH_CERT_DEVICE_ID_LENGTH                   (16)
#define CI_UTC_TIME_LEN                                 (5)
#define CI_CC_PIN_EVENT_PRIVATE_DATA_LEN                (15)
#define CI_CC_SRM_DATA_MAX_LEN                          (5000)
#define CI_VIRTUAL_CHANNEL_INFO_LEN                     (255)
#define CC_AUTH_CSUV_SIZE                               (1)

// URI
#define CC_URI_PROTOCOL_V1                              0x01
#define CC_URI_PROTOCOL_V2                              0x02
#define CC_URI_PROTOCOL_V4                              0x04
// URI - APS
#define CC_URI_APS_COPY_PROTECTION_ENCODING_OFF         0x00
#define CC_URI_APS_AGC_PROCESS_ON_SPLIT_BURST_OFF       0x01
#define CC_URI_APS_AGC_PROCESS_ON_2_LINE_SPLIT_BURST_ON 0x02
#define CC_URI_APS_AGC_PROCESS_ON_4_LINE_SPLIT_BURST_ON 0x03
// URI - EMI
#define CC_URI_EMI_COPY_FREELY                          0x00
#define CC_URI_EMI_COPY_NO_MORE                         0x01
#define CC_URI_EMI_COPY_ONCE                            0x02
#define CC_URI_EMI_COPY_NEVER                           0x03
// URI - RCT
#define CC_URI_RCT_NO_REDISTRIBUTION_CONTROL_ASSERTED   0x00
#define CC_URI_RCT_REDISTRIBUTION_CONTROL_ASSERTED      0x01
// URI - DOT
#define CC_URI_DOT_NO_DIGITAL_ONLY_CONSTRAINT_ASSERTED  0x00
#define CC_URI_DOT_DIGITAL_ONLY_CONSTRAINT_ASSERTED     0x01
// URI - RL
#define CC_URI_RL_DEFAULT_90_MINUTES_APPLIES            0x00
#define CC_URI_RL_6_HOURS_APPLIES                       0x01
#define CC_URI_RL_12_HOURS_APPLIES                      0x02
#define CC_URI_RL_MULTIPLES_OF_24HOURS_APPLIES_START    0x03
#define CC_URI_RL_MULTIPLES_OF_24HOURS_APPLIES_END      0x3F
#define CC_URI_RL_MULTIPLES_OF_24HOURS_APPLIES_END_FOR_CC_V4      0x3FE
#define CC_URI_RL_UNLIMITED_RETENTION_PERIOD_FOR_CC_V4            0x3FF
// [END] URI

#define CI_PLUS_TEST_CREDENTIALS                        FALSE
#define CI_PLUS_PRODUCTION_CREDENTIALS                  TRUE
#define CI_PLUS_CREDENTIALS_IN_CI_LIB                   FALSE
#define CI_PLUS_CREDENTIALS_IN_FLASH                    TRUE
#endif

// CI task Doze duration
#define CI_MONITOR_THREAD_DOZE_DURATION                 50000   //50ms
// CI task Work duration
#define CI_MONITOR_THREAD_NO_DOZE_DURATION              5000    //5ms
// CI task fast duration when LSC has data to be transfer from host to CICAM
#define CI_MONITOR_THREAD_LSC_DURATION                  1       //1us

// OP
// OP Invalid Descriptor Number
#define OP_INVALID_DESCRIPTOR_NUMBER                    0xFF
#define OP_MAX_PROFILE_NAME_SIZE                        50
/// OP Max Size of NIT Sections
#define OP_MAX_NIT_LEN                                  0xFFFF

#define CI_HC_TUNE_WAIT_PMT_THRESHOLD                   2300 //ms

/*
CI+ Spec v1.3  [5.10.4 Content License Exchange on Playback]
    On playback of content which has an associated license then the Host shall send the license to the original content recording CICAM for evaluation.
    The license is sent to the CICAM securely on the SAC using the Playback License Exchange Protocol, see section 11.3.4.2.
    The CICAM processes the license to establish whether it still has rights to play the content.
    A new license and URI are returned to the Host to replace the originals in case the information contained has changed, e.g. play count.
    The Playback License Exchange Protocol is performed while playing the content to ensure that playback start is not delayed.
    If the Playback License Exchange response is not OK, or the response takes longer than 10 seconds, then the playback shall be stopped.
    The URI which accompanies the license in the Playback License Exchange Protocol shall be applied immediatly.
*/
//use 9 seconds for delay of host process handling
#define CC_LICENSE_EXCHANGE_TIMEOUT 8000 // 8s

/*****************************************************************************/
/*                      Enum                                                 */
/*****************************************************************************/
typedef enum
{
    EN_NO_MODULE                                        = 0x00,
    EN_MODULE_INITIALIZING,
    EN_MODULE_READY,
    EN_MODULE_RESET,
} E_CARD_STATE;

typedef enum
{
    EN_CI_FUNCTION_RM                                   = 0x00,
    EN_CI_FUNCTION_APPINFO,
    EN_CI_FUNCTION_CAS,
    EN_CI_FUNCTION_HC,
    EN_CI_FUNCTION_DT,
    EN_CI_FUNCTION_MMI,
    EN_CI_FUNCTION_LSC,
    EN_CI_FUNCTION_CC,
    EN_CI_FUNCTION_HLC,
    EN_CI_FUNCTION_CU,
    EN_CI_FUNCTION_OP,
    EN_CI_FUNCTION_SAS,
    EN_CI_FUNCTION_APPMMI,
    EN_CI_FUNCTION_PMT,
    EN_CI_FUNCTION_HSS,
    EN_CI_FUNCTION_AUTH,
    EN_CI_FUNCTION_DEFAULT,

//  please insert new enum before debug count
    EN_CI_FUNCTION_DEBUG_COUNT
} EN_CI_FUNCTION;

typedef enum {
    EN_CIMSG_NONE                                       = 0x00,
    EN_CIMSG_DETECTED,
    EN_CIMSG_REMOVED,
    EN_CIMSG_INVALID,
    EN_CIMSG_DISPLAY,
    EN_CIMSG_LOADINFO,
    EN_CIMSG_LOAD_NONE,
    EN_CIMSG_NOMODULE,
    EN_CIMSG_NOMODULE_DISPLAY,
    EN_CIMSG_TRYAGAIN,
} E_CIMSG_TYPE;

typedef enum
{
    EN_SMARTCARD_TYPE_NONE                              = 0x00,
    EN_SMARTCARD_TYPE_TSDTURKEY,
    EN_SMARTCARD_TYPE_SETANTA,
    EN_SMARTCARD_TYPE_NEOTNT,
    EN_SMARTCARD_TYPE_CONAXNETHERLANDS
} EN_SMARTCARD_TYPE;

typedef enum
{
    EN_APPMMI_REQTYPE_FILE                              = 0x00,
    EN_APPMMI_REQTYPE_DATA                              = 0x01,
    EN_APPMMI_REQTYPE_FILE_HASH                         = 0x02,
    EN_APPMMI_REQTYPE_REQ_TYPES                         = 0x03,
    EN_APPMMI_REQTYPE_INVALID                           = 0xFF
} EN_APPMMI_REQTYPE;

typedef enum
{
    EN_CI_IVALID_VERSION                                = 0x00,
    EN_CI_VERSION_CI                                    = 0x01,
    EN_CI_VERSION_CI_PLUS                               = 0x02
} EN_CI_VERSION;

typedef enum
{
    EN_CI_PLUS_IVALID_VERSION                           = 0x00,
    EN_CI_PLUS_VERSION_1_2                              = 0x01,
    EN_CI_PLUS_VERSION_1_3                              = 0x02,
    EN_CI_PLUS_VERSION_1_4                              = 0x03
} EN_CI_PLUS_VERSION;

typedef enum
{
    E_CI_RESOURCE_NONE                                  = 0x00,
    E_CI_RESOURCE_VERSION_1,
    E_CI_RESOURCE_VERSION_2,
    E_CI_RESOURCE_VERSION_3,
    E_CI_RESOURCE_VERSION_4,
    E_CI_RESOURCE_VERSION_5,
} EN_CI_RESOURCE_VERSION;

typedef enum
{
    EN_HOST_OPERATING_USER                              = 0x00,
    EN_HOST_OPERATING_UNATTENDED,
    EN_HOST_OPERATING_SERVICE,
    EN_HOST_OPERATING_NONE                              = 0xFF
} EN_HOST_OPERATING_TYPE;

typedef enum
{
    EN_AES_TYPE_ECB                                     = 0x00,
    EN_AES_TYPE_CBC,
    EN_AES_TYPE_NONE                                    = 0xFF
} EN_AES_TYPE;

/* EN 50221 Page.28 application_info().application_type  */
typedef enum
{
    EN_CI_APP_TYPE_CA                                   = 0x01,
    EN_CI_APP_TYPE_EPG
} EN_CI_APP_TYPE;

typedef enum
{
    EN_CREDENTIAL_ROOT_CERTIFICATE                      = 0x01,
    EN_CREDENTIAL_HOST_DEVICE_CERTIFICATE,
    EN_CREDENTIAL_HOST_BRAND_CERTIFICATE,
    EN_CREDENTIAL_HDQ,
    EN_CREDENTIAL_DH_P,
    EN_CREDENTIAL_DH_G,
    EN_CREDENTIAL_DH_Q,
    EN_CREDENTIAL_SIV,
    EN_CREDENTIAL_PRNG_SEED,
    EN_CREDENTIAL_SLK,
    EN_CREDENTIAL_CLK,
    EN_CREDENTIAL_NONE                                  = 0xFF
} EN_CREDENTIAL_TYPE;

typedef enum
{
    E_CIPLUS_CC_INVALID_SCRAMBLER_MODE                  = 0x00,
    E_CIPLUS_CC_DES_56_ECB,
    E_CIPLUS_CC_AES_128_CBC,
    E_CIPLUS_IDSA,
    E_CIPLUS_CSA
} E_CIPLUS_CC_SCRAMBLER_MODE;

typedef enum
{
    E_CIPLUS_CC_EVEN_KEY                                = 0x00,
    E_CIPLUS_CC_ODD_KEY,
    E_CIPLUS_CC_INVALID_KEY                             = 0xFF
} E_CIPLUS_CC_KEY_MODE;

typedef enum
{
    EN_CC_CICAM_PIN_CAPABILITIES_NO_HANDLE              = 0x00,
    EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY         = 0x01,
    EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN               = 0x02,
    EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY_CACHED  = 0x03,
    EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN_CACHED        = 0x04
} EN_CC_CICAM_PIN_CAPABILITIES;

typedef enum
{
    EN_CC_PIN_CODE_STATUS_BAD_PIN_CODE                  = 0x00,
    EN_CC_PIN_CODE_STATUS_CICAM_BUSY                    = 0x01,
    EN_CC_PIN_CODE_STATUS_PIN_CODE_CORRECT              = 0x02,
    EN_CC_PIN_CODE_STATUS_PIN_CODE_UNCONFIRMED          = 0x03,
    EN_CC_PIN_CODE_STATUS_VIDEO_BLANKING_NOT_REQUIRED   = 0x04,
    EN_CC_PIN_CODE_STATUS_UNKNOW                        = 0xFF
} EN_CC_PIN_CODE_STATUS;

typedef enum
{
    EN_CC_VERSION_NONE                                  = 0x00,
    EN_CC_VERSION_V1                                    = 0x01,
    EN_CC_VERSION_V2                                    = 0x02,
    EN_CC_VERSION_V4                                    = 0x04
} EN_CC_VERSION;

typedef enum
{
    EN_MMI_TYPE_NONE                                    = 0x00,
    EN_MMI_TYPE_MENU,
    EN_MMI_TYPE_LIST,
    EN_MMI_TYPE_ENQ,
    EN_MMI_TYPE_TEXT
} EN_MMI_TYPE;

typedef enum
{
    // MMI
    CI_EVENT_MMI_NONE                                   = 0x00,
    CI_EVENT_MMI_ENQ,
    CI_EVENT_MMI_MENU,
    CI_EVENT_MMI_LIST,
    CI_EVENT_MMI_CLOSE,
    //APPMMI
    CI_EVENT_APPMMI_REQ_START,
    CI_EVENT_APPMMI_FILE,
    CI_EVENT_APPMMI_DATA,
    CI_EVENT_APPMMI_REQ_NG,
    CI_EVENT_APPMMI_FILE_INQUIRE_OK,
    CI_EVENT_APPMMI_FILE_INQUIRE_NG,
    CI_EVENT_APPMMI_REQ_ABORT,
    //CAS
    CI_EVENT_CAS_CAPMT,
    //HC
    CI_EVENT_HC_TUNE,
    CI_EVENT_HC_REPLACE,
    CI_EVENT_HC_CLEAR_REPLACE,
    CI_EVENT_HC_TUNE_BROADCAST_REQ,
    CI_EVENT_HC_CICAM_PMT_PARSE,
    CI_EVENT_HC_STREAM_PMT_PARSE,
    CI_EVENT_HC_SI_WAKE_UP,
    CI_EVENT_HC_TUNE_FAIL_REPLY,
    CI_EVENT_HC_TUNE_LCN_REQ,
    CI_EVENT_HC_TUNE_IP_REQ,
    CI_EVENT_HC_TUNE_TRIPLET_REQ,
    CI_EVENT_HC_TUNER_STATUS_REQ,
    CI_EVENT_HC_TUNE_ASK_RELEASE_OK,
    CI_EVENT_HC_TUNE_ASK_RELEASE_REFUSED,
    //DT
    CI_EVENT_DT_ENQ,
    //CC
    CI_EVENT_CC_CREDENTIALS_LOAD,
    CI_EVENT_CC_CREDENTIALS_NG,
    CI_EVENT_CC_AUTH_KEY_SAVE,
    CI_EVENT_CC_AUTH_KEY_LOAD,
    CI_EVENT_CC_URI,
    CI_EVENT_CC_DSCMB_KEY,
    CI_EVENT_CC_PIN_REPLY,
    CI_EVENT_CC_SRM_DATA,
    //CU
    CI_EVENT_CU_START,
    CI_EVENT_CU_PROGRESS,
    CI_EVENT_CU_CANCEL,
    CI_EVENT_CU_COMPLETE,
    //OP
    CI_EVENT_OP_STATUS,
    CI_EVENT_OP_NIT,
    CI_EVENT_OP_INFO,
    CI_EVENT_OP_SEARCH_STATUS,
    CI_EVENT_OP_TUNE,
    CI_EVENT_OP_NIT_CHECK,
    //SAS
    CI_EVENT_SAS_SESSION_CONNECT,
    CI_EVENT_SAS_SESSION_DISCONNECT,
    CI_EVENT_SAS_CONNECT_CNF,
    CI_EVENT_SAS_ASYNC_MSG,
    // HSS
    CI_EVENT_HSS,
    //CANAL READY
    CI_EVENT_AUTH_CANAL_READY_CREDENTIALS_LOAD,
    //CAM Reset
    CI_EVENT_CAM_DETECT,
    CI_EVENT_CAM_RESET,
    CI_EVENT_CAM_INIT_INTERRUPT,
    //CI thread
    CI_EVENT_THREAD_WAKE_UP,
    CI_EVENT_THREAD_DOZE_OFF,
    //Other
    CI_EVENT_SYSTEM_TIME_UPDATE,
    // APPINFO
    CI_EVENT_APPINFO_HDS_REQ,
    CI_EVENT_APPINFO_POWER_DOWN_OK,
    CI_EVENT_END                                        = 0xFF
} EN_CI_EVENT;

#define CI_EVENT_NONE                                   CI_EVENT_MMI_NONE //For Chakra2

typedef enum
{
    EN_LSC_CONNECT_ACK                                  = 0x01,
    EN_LSC_DISCONNECT_ACK                               = 0x02,
    EN_LSC_SEND_ACK                                     = 0x06
} EN_LSC_CMD_ACK;

/// CI+ Spec v1.3 Table 11.45: license_status Values
typedef enum
{
    /// OK
    EN_CC_PVR_LICENSE_STATUS_OK                         = 0x00,
    /// Descrambling not possible, no entitlement (record only)
    EN_CC_PVR_LICENSE_STATUS_NO_ENTITLEMENT             = 0x01,
    /// Entitlement rights expired (playback & status check)
    EN_CC_PVR_LICENSE_STATUS_UNDEFINED_ERROR            = 0x02,
    /// Play count exceeded (playback & status check)
    EN_CC_PVR_LICENSE_STATUS_ENTITLEMENT_RIGHTS_EXPIRED = 0x03,
    /// Play count exceeded (playback & status check)
    EN_CC_PVR_LICENSE_STATUS_PLAY_COUNT_EXCEEDED        = 0x04,
    /// Retention limit exceeded (playback & status check)
    EN_CC_PVR_LICENSE_STATUS_RETENTION_LIMIT_EXCEEDED   = 0x05,
    /// Invalid license (playback & status check)
    EN_CC_PVR_LICENSE_STATUS_INVALID_LICENSE            = 0x06,
    /// Reserved
    EN_CC_PVR_LICENSE_STATUS_RESERVED                   = 0xFF
} EN_CC_PVR_LICENSE_STATUS;

/// CI+ Spec v1.3 Table 11.46: Record Start Message
typedef enum
{
    /// Watch_and_Buffer
    EN_CC_PVR_OPERATING_MODE_WATCH_AND_BUFFER           = 0x00,
    /// Timeshift
    EN_CC_PVR_OPERATING_MODE_TIMESHIFT                  = 0x01,
    /// Unattended _Recording
    EN_CC_PVR_OPERATING_MODE_UNATTENDED_RECORDING       = 0x02,
    /// Reserved
    EN_CC_PVR_OPERATING_MODE_RESERVED                   = 0xFF
} EN_CC_PVR_OPERATING_MODE;

typedef enum
{
    EN_CC_DATATYPE_ID_UNKNOW                            = 0,    // unknow_status
    EN_CC_DATATYPE_ID_RECORD_START                      = 40,   // record_start_status
    EN_CC_DATATYPE_ID_MODE_CHANGE                       = 41,   // mode_change_status
    EN_CC_DATATYPE_ID_RECORD_STOP                       = 42    // record_stop_status
} EN_CC_PVR_DATATYPE_ID;

//CAS
typedef enum
{
    EN_CAS_SUSPEND_OPERATION_MODE_DISABLE               = 0x00,
    EN_CAS_SUSPEND_OPERATION_MODE_ONCE                  = 0x01,
    EN_CAS_SUSPEND_OPERATION_MODE_ALWAYS                = 0x02
} EN_CAS_SUSPEND_OPERATION_MODE;

typedef enum
{
    EN_HC_TUNE_REPLY_STATUS_OK                                  = 0x00,
    EN_HC_TUNE_REPLY_STATUS_ERROR_UNSUPPORTED_DELIVERY_SYSTEM   = 0x01,
    EN_HC_TUNE_REPLY_STATUS_ERROR_TUNER_NOT_LOCKING             = 0x02,
    EN_HC_TUNE_REPLY_STATUS_ERROR_TUNER_BUSY                    = 0x03,
    EN_HC_TUNE_REPLY_STATUS_ERROR_BAD_OR_MISSING_PARAMETERS     = 0x04,
    EN_HC_TUNE_REPLY_STATUS_ERROR_SERVICE_NOT_FOUND             = 0x05,
    EN_HC_TUNE_REPLY_STATUS_ERROR_UNDEFINED                     = 0x06,
    EN_HC_TUNE_REPLY_STATUS_RESERVED                            = 0xFF
} EN_HC_TUNE_REPLY_STATUS;

typedef enum
{
    EN_HC_RELEASE_REPLY_STATUS_OK                       = 0x00,
    EN_HC_RELEASE_REPLY_STATUS_REFUSED                  = 0x01,
    EN_HC_RELEASE_REPLY_STATUS_RESERVED                 = 0xFF
} EN_HC_RELEASE_REPLY_STATUS;

// OP
typedef enum
{
    /* CI+ Spec v1.3.1 Table 14.39: profile_type values */
    // 0: The CICAM does not support any profiles and descrambles elementary streams as per DVB CI.
    EN_OP_TYPE_0                                        = 0x00,
    // 1: Profile is a private network that uses a CICAM NIT and has a private profile logical channel list..
    EN_OP_TYPE_1                                        = 0x01,
    // 2: Profiled operation where the Host constructs a logical channel list from the broadcast SI and the CICAM NIT.
    EN_OP_TYPE_2                                        = 0x02,
    // 2-3: Reserved for future use.
    EN_OP_TYPE_RESERVED                                 = 0x03
} EN_OP_TYPE;

typedef enum
{
    /* CI+ Spec v1.3.1 Table 14.39: refresh_request_flag values */
    // 0: The default state, indicates that the CICAM does not need to interrogate the network and is up to date.
    EN_OP_REFRESH_REQUEST_FLAG_DEFAULT                  = 0x00,
    // 1: Advance warning to the Host that something in the network has changed and the CICAM
    // requires the Host to tune in order to perform an update check when convenient. The request
    // shall be deferred until the Host is ready to do the search without interrupting the user.
    EN_OP_REFRESH_REQUEST_FLAG_ADVANCE_WARNING,
    // 2: Urgent request from the CICAM that the network needs to be interrogated in order to acquire
    // information. An urgent request shall only be signalled where the CICAM does not have full
    // functional capability until the network has been interrogated. The Host shall initiate a profile
    // search as soon as possible.
    EN_OP_REFRESH_REQUEST_FLAG_URGENT_REQUEST,
    // 3: Scheduled refresh request from the CICAM that the network needs to be interrogated at a
    // specific update time. The Host shall initiate a profile search at or after the specified time if
    // possible. This may require the Host to automatically wake from standby at the specified time to
    // initiate the search. If the search slot is missed, for example if the receiver is powered off, then
    // the CICAM shall preferably reschedule for a later time rather than force an unnecessary search
    // on the Host.
    EN_OP_REFRESH_REQUEST_FLAG_SCHEDULED_REQUEST
} EN_OP_REFRESH_REQUEST_FLAG;

typedef enum
{
    /* CI+ Spec v1.3.1 Table 14.40: error_flag values */
    // 0: There are no errors.
    EN_OP_ERROR_FLAG_NO_ERROR                       = 0x00,
    // 1: Profile error. The CICAM has encountered an error and cannot acquire the profile, no profile
    // information is cached.
    EN_OP_ERROR_FLAG_PROFILE_ERROR,
    // 2: Unsupported delivery system. The CICAM does not support the delivery system descriptor(s)
    // reported by the Host.
    EN_OP_ERROR_FLAG_UNSUPPORTED_DELIVERY_SYSTEM,
    // 3: Cancelled. The operator search has been interrupted and is incomplete.
    EN_OP_ERROR_FLAG_CANCELLED
} EN_OP_ERROR_FLAG;

typedef enum
{
    /* CI+ Spec v1.3.1 Table 14.41: delivery_system_hint values */
    // 1: TThis is a cable network and may be DVB-C and/or DVB-C2
    EN_OP_DELIVERY_SYSTEM_HINT_DVB_C                = 0x01,
    // 2: This is a satellite network and may be DVB-S and/or DVB-S2
    EN_OP_DELIVERY_SYSTEM_HINT_DVB_S                = 0x02,
    // 3: This is a terrestrial network and may be DVB-T and/or DVB-T2
    EN_OP_DELIVERY_SYSTEM_HINT_DVB_T                = 0x04,
    // 4. This is an IP network
    EN_OP_DELIVERY_SYSTEM_HINT_IP_NETWORK           = 0x08
} EN_OP_DELIVERY_SYSTEM_HINT;

typedef enum
{
    /* CI+ Spec v1.3.1 Table 14.53: status values */
    // 0: The tuning operation was successful and the Host has successfully tuned to the requested location;
    // the tuner is locked and a digital signal is available.
    EN_OP_TUNE_STATUS_OK                                = 0x00,
    // 1: The delivery system descriptor is not supported by the Host.
    EN_OP_TUNE_STATUS_NG_NOT_SUPPORTED,
    // 2: The delivery system descriptor parameters are invalid.
    EN_OP_TUNE_STATUS_NG_PARAMETERS_INVALID,
    // 3: The tuning operation failed.
    // The Host has successfully tuned to the requested location and no signal is present.
    EN_OP_TUNE_STATUS_NG_OPERATION_FAILED
} EN_OP_TUNE_STATUS;

typedef enum
{
    /* CI+ spec v1.4 Table 107: Error field values */
    // 0: No issue - OSDT and/or NIT retrieved.
    EN_OP_NIT_ERROR_FIELD_NO_ISSUE                 = 0x00,
    // 1: NIT error - The NIT cannot be applied. No service from the CICAM NIT have been added to the Host logical channel list.
    EN_OP_NIT_ERROR_FIELD_NIT_ERROR                = 0x01,
    // 2: OSDT error - The URL for OSDT cannot be found. No service from the OSDT have been added to the Host logial channel list,
    // but service from the CICAM NIT will have been added unless indicated otherwise by the operator_nit_management() APDU.
    EN_OP_NIT_ERROR_FIELD_OSDT_ERROR               = 0x02,
    // 3: OSDT error - not supported.
    EN_OP_NIT_ERROR_FIELD_OSDT_ERROR_NOT_SUPPORTED = 0x03,
    // 4: Reserved.
    EN_OP_NIT_ERROR_FIELD_RESERVED                 = 0xFF
} EN_OP_NIT_ERROR_FIELD;

typedef enum
{
    /* CI+ spec v1.4 Table 108: Channel issue type values */
    // 0: LCN colllision - denotes that the LCN provided by the CAM NIT is not unique and has a collision with a LCN
    // provided by broadcast Service Information.
    EN_OP_CHANNEL_ISSUE_TYPE_LCN_COLLISION         = 0x00,
    // 1: Application Domain - denotes that the Application Domain requested in the CICAM NIT is not supported by the Host.
    EN_OP_CHANNEL_ISSUE_TYPE_APPLICATION_MAIN      = 0x01,
    // 2: Serveice not stores - Delivery mechanism not supported.
    EN_OP_CHANNEL_ISSUE_TYPE_SERVICE_NOT_STORED    = 0x02,
    // 3: Reserved for future use
    EN_OP_CHANNEL_ISSUE_TYPE_RESERVED              = 0x03
} EN_OP_CHANNEL_ISSUE_TYPE;

// SAS
typedef enum
{
    EN_SAS_SESSION_STATUS_OK                            = 0x00,
    EN_SAS_SESSION_STATUS_CONNECTION_DENIED_NO_FOUND,
    EN_SAS_SESSION_STATUS_CONNECTION_DENIED_NO_MORE_CONNECTIONS,
    EN_SAS_SESSION_STATUS_RESERVED                      = 0xFF
} EN_SAS_SESSION_STATUS;

typedef enum
{
    EN_SAS_DATA_STATUS_AVAILABLE                        = 0x00,     // 0x00         Data available
    EN_SAS_DATA_STATUS_NOT_AVAILABLE,                               // 0x01         Data not available
    EN_SAS_DATA_STATUS_RESERVED                         = 0xFF      // 0x02-0xFF    Reserved
} EN_SAS_DATA_STATUS;

/* CI+ Spec v1.3.1 Table 14.22: Application Abort Codes */
typedef enum
{
    // 0x00: Reserved for future use.
    EN_APPMMI_ABORT_CODES_RESERVED                       = 0x00,
    // 0x01: User Cancel ¡V The user has initiated termination of the application domain.
    EN_APPMMI_ABORT_CODES_USER_CANCEL                    = 0x01,
    // 0x02: System Cancel ¡V The system has pre-empted the application domain to perform another task.
    EN_APPMMI_ABORT_CODES_SYSTEM_CANCEL                  = 0x02
} EN_APPMMI_ABORT_CODES;

typedef enum
{
    EN_CI_BREAK_POINT_NONE                              = 0x00,
    EN_CI_BREAK_POINT_MEMORY_MODE,
    EN_CI_BREAK_POINT_IO_MODE,
} EN_CI_BREAK_POINT;

typedef enum
{
    EN_CI_INIT_TIMEOUT_ON                              = 0x00,
    EN_CI_INIT_TIMEOUT_OFF,
} EN_CI_CONTROL_INIT_TIMEOUT;

/* CI+ Spec v1.3 Table 11.17: Possible values for status_field
*/
typedef enum
{
    EN_CC_SYNC_CNF_STATUS_OK,
    EN_CC_SYNC_CNF_STATUS_NO_CC_SUPPORT,
    EN_CC_SYNC_CNF_STATUS_HOST_BUSY,
    EN_CC_SYNC_CNF_STATUS_AUTHENTICATION_FAILED,
    EN_CC_SYNC_CNF_STATUS_CICAM_BUSY,
    EN_CC_SYNC_CNF_STATUS_RECORDING_MODE_ERROR,
    EN_CC_SYNC_CNF_STATUS_RESERVED
} EN_CC_SYNC_CNF_STATUS;

/***************** RR2194 CI+1.4 Develop ******************/
typedef enum
{
    EN_APPINFO_HDS_IS_SHOWING,
    EN_APPINFO_HDS_NOT_SHOWING,
    EN_APPINFO_HDS_NOT_SUPPORT,
    EN_APPINFO_HDS_RESERVED
}EN_APPINFO_HDS_STATUS;
/**********************************************************/

/*****************************************************************************/
/*                      Structures                                           */
/*****************************************************************************/
#if CI_PLUS_FUNCTION_ENABLE
/// Data structure for saving credential keys into EEPROM / NAND flash.
typedef struct CI_KEY_SETTING
{
    /// Authentication Key Host
    U8  u8AKH[CC_AUTH_AKH_SIZE];            // CC_AUTH_AKH_SIZE = 32
    /// Diffie-Hellman Secret Key
    U8  u8DHSKTail[CC_AUTH_DHSK_TAIL_SIZE]; // CC_AUTH_DHSK_TAIL_SIZE = 16
    /// CICAM ID
    U8  u8CamID[CC_AUTH_ID_SIZE];           // CC_AUTH_ID_SIZE = 8
    /// CICAM Brand ID
    U16 u16CamBrandID;
    /// E_CIPLUS_CC_AES_128_CBC or E_CIPLUS_CC_DES_56_ECB
    U8  u8ScramblerMode;
    /// Not used
    U8  u8Reserved;
    /// cicam_identifier comes from OP Info
    U32 u32OpCicamIdentifier;
} MS_CI_KEY_SETTING;

/// CI+ Spec v1.4 Table 102: tuner_status_reply APDU
typedef struct
{
    /// This field specifies if the Host believes that at least one tuner of this DSD type is connected to a broadcast
    /// network. This us only a hint to the CICAM if a tune request would be successful.
    BOOL bConnected;
    /// This field specifies the delivery systems supported by the Host and being available for background tunes.
    U8   u8aDeliverySystemDescTag[2];
} CI_HC_DSD;

typedef struct
{
    /// This flag shall be set to 0 if the Host is able to accept tune_ip_req() APDUs for IP-delivered service.
    BOOL bIP_TuneCapable;
    /// This field specific the number of used DSD types supported by the Host.
    U8   u8NumDsd;
    /// This field indicates which DSD is supported by Host
    CI_HC_DSD pstDsd[6];
} CI_HC_TUNER_STATUS;

/// CI+ Spec v1.3 Table 14.37: operator_status_body syntax
typedef struct
{
    /// refresh_request_date: This 16-bit field indicates the date of the next scheduled refresh cycle requested by the
    /// CICAM. The date is specified as UTC Modified Julian Date (MJD).
    /// A value of 0x0000 indicates that no schedule refresh is requested.
    U16 u16RefreshRequestDate;
    /// info_version: This 3-bit field is an identifier that uniquely identifies the version of the profile information
    /// contained in the operator_info() APDU.
    U8 u8InfoVersion:3;
    /// nit_version: This 5-bit field is only interpreted in the context of a non-zero profile and is set to the current
    /// version number of the NIT delivered by the CICAM.
    U8 u8NitVersion:5;
    /// profile_type: This 2-bit field identifies the type of CICAM profile.
    U8 u8ProfileType:2;
    /// initialised_flag: This 1-bit field contains the status of the profile initialisation for the specified profile. A value
    /// of "0" indicates that the profile has not initialised, a value of "1" indicates that the profile has been initialised by
    /// the CICAM.
    U8 u8InitializedFlag:1;
    /// entitlement_change_flag: This 1-bit field shall be set when an entitlement change has occurred which has not
    /// been acknowledged by the Host. A value of "0", the default, indicates that there are no entitlement changes
    /// pending, a value of "1" indicates that an unacknowledged entitlement change is pending.
    U8 u8EntitlementChangeFlag:1;
    /// entitlement_valid_flag: This 1-bit field shall be set when the entitlement is valid, the field is provided for
    /// information only. A value of "1", indicates that entitlement rights have been gained and are valid. A value of "0"
    /// indicates that there are no entitlement rights.
    U8 u8EntitlementValidFlag:1;
    /// reserved
    U8 u8Reserved:1;
    /// refresh_request_flag: This 2-bit field shall be set when the CICAM requires a tuning operation to visit another
    /// multiplex in order to acquire further information about the profile or to check entitlement rights etc.
    U8 u8RefreshRequestFlag:2;
    /// error_flag: This field is a 4-bit flag field which contains the status of the current active profile.
    U8 u8ErrorFlag:4;
    /// delivery_system_hint: This field is a 4-bit field which contains a hint of the delivery system supported by the
    /// Operator Profile and provides the Host with an assessment of the CICAM profile.
    U8 u8DeliverySystemHint:4;
    /// refresh_request_time: This 8-bit field indicates the time of a scheduled refresh cycle requested by the CICAM.
    /// The time is specified in UTC as an integer value in 6 minute intervals from midnight and is valid in the range
    /// 0..239. This field is only interpreted when the refresh_request_date is non-zero. When the refresh_request_flag
    /// is zero then this field shall also be zero.
    U8 u8RefreshRequestTime;
} CI_OP_STATUS;

/// CI+ Spec v1.3 Table 14.46: operator_info APDU syntax
typedef struct
{
    /// cicam_identifier: This 32-bit field identifies a particular hardware instance of the CICAM. The
    /// cicam_identifier shall be unique enough to be used in conjunction with the CICAM_original_network_id to link
    /// a CICAM with an operator profile.
    U32 u32CicamIdentifier;
    /// cicam_original_network_id: This 16-bit field unambiguously identifies the original_network_id identity of the
    /// service operator according to the allocations found in ETSI TS 101 162 [32]. This may differ from the
    /// original_network_id reported in the network due to the historical evolution of the network.
    U16 u16CicamOriginalNetworkID;
    /// reserved2
    U16 u16Reserved2;
    /// reserved1
    U8 u8Reserved1:4;
    /// info_valid: this 1-bit field, when set to "1", indicates that the operator information is present. This bit shall only
    /// be set to "1" when the operator information accurately reflects the contents of the broadcast network.
    U8 u8InfoValid:1;
    /// info_version: This 3-bit field is an identifier that uniquely identifies the version of the profile information
    /// contained within this APDU.
    U8 u8InfoVersion:3;
    /// character_code_table: This 8-bit field identifies the default character set encoding that has been used on the
    /// network where the network operator has deviated from the DVB character encoding format defined by ETSI EN
    /// 300 468 [10], Annex A.
    U8 u8CharacterCodeTable;
    /// encoding_type_id: This 8-bit field qualifies the character_code_table field when set to 0x1f and indicates the
    /// encoding scheme of the string according to the allocations found in ETSI TR 101 162.
    U8 u8EncodingTypeID;
    /// second_byte_value: This 8-bit field qualifies the character_code_table field when set to 0x10and is the first
    /// byte of the 16-bit value used to specify the character code table as defined in ETSI EN 300 468 [10], Annex A,
    /// Table A.4.
    U8 u8SecondByteValue;
    /// third_byte_value: This 8-bit field qualifies the character_code_table field when set to 0x10and is the second
    /// byte of the 16-bit value used to specify the character code table as defined in ETSI EN 300 468 [10], Annex A,
    /// Table A.4.
    U8 u8ThirdByteValue;
    /// sdt_running_status_trusted: This 1-bit field is a hint to the Host that identifies if the running_status field of
    /// the SDT is accurate, is trustable and may be interpreted by the Host. When the field is set to "1" then the SDT
    /// running status is trusted and the Host receiver may indicate services that are not in a active running state. When
    /// the field is set to "0" then the SDT running status shall be interpreted to be always in a running state. The default
    /// Host operation is "0".
    U8 u8SdtRunningStatusTrusted:1;
    /// eit_running_status_trusted: This 1-bit field is a hint to the Host that identifies if the running_status field of
    /// the EIT is accurate, is trusted and may be interpreted by the Host. When the field is set to "1" then the EIT
    /// running status is trusted and correctly indicates whether services are in an active running state. When the field is
    /// set to "0" then the Host shall assume that the EIT running status is always in an active running state. The default
    /// Host operation is "0".
    U8 u8EitRunningStatusTrusted:1;
    /// eit_present_following_usage: This 2-bit field describes the operating state of the EIT present/following event
    /// information in the network according to the values in Table 14.46. The default Host operation is acquisition
    /// from the local multiplex (1).
    U8 u8EitPresentFollowingUsage:2;
    /// eit_schedule_usage: This 3-bit field describes the operating state of the EIT scheduled event information in the
    /// network according to the values in Table 14.47. The default Host operation is acquisition from the local
    /// multiplex (1) or Barker channel operation (3) when a EPG service linkage is present.
    U8 u8EitScheduleUsage:3;
    /// extended_event_usage: This 1-bit field identifies how extended event information is presented and identifies
    /// whether the short_event_descriptor (0x4d) and extended_event_descriptor (0x4e) text fields are used mutually
    /// exclusively. The values are defined in Table 14.48.
    U8 u8ExtendedEventUsage:1;
    /// sdt_other_trusted: This 1-bit field identifies the trusted state of SDT other tables in the network. The field shall
    /// be set to "1" when the SDT is fully cross carried across the network and may be trusted by the Host for accurate
    /// eit_event_trigger state information. The default is "0" and information in SDT actual is trusted only.
    U8 u8SdtOtherTrusted:1;
    /// eit_event_trigger: This 1-bit field identifies if the EIT present/following event transition across the network is
    /// accurate enough to be used for event based recording. When the field is set to "1" then the EIT p/f event transition
    /// (when EIT following becomes EIT present ) is accurately transitioned and may be used as a trigger to start and stop
    /// recording of an event. When the field is "0" then the EIT p/f transition is inaccurate and the Host may use another
    /// mechanism to ensure that the whole event is recorded e.g. addition of a 5min lead-in and trailer time before and
    /// after the event signalled time.
    U8 u8EitEventTrigger:1;
    /// reserved3
    U8 u8Reserved3:6;
    /// ISO_639_language_code: This 24-bit field identifies the default language code of unlabelled text fields and
    /// elementary stream components. The default language code shall be used by the Host to perform component and
    /// text selection in the absence of any explicit signalling from the service operator. Language codes which are
    /// undefined (including ?und? or ?qaa?) shall be assumed to be the default language code specified by this field.
    U8 u8aISO639LanguageCode[3];
    /// profile_name_length: This 8-bit field specifies the length in bytes of the following text field describing the
    /// profile name. For profile_type=1 this field shall always be non-zero and contain a valid profile name. The field
    /// may be zero (0) if there is no profile name.
    U8 u8ProfileNameLen;
    /// profile_name_byte: This is a 8-bit field, a string of "char" fields specifies the profile name. Text information is
    /// coded using the character sets and methods defined in ETSI EN 300 468 [10], Annex A. The profile name shall
    /// be used to label a profile and shall be used in preference to any network name found in any broadcast
    /// information or CICAM NIT.
    U8 au8ProfileName[OP_MAX_PROFILE_NAME_SIZE];
} CI_OP_INFO;

/// CI+ Spec v1.4 Table 106: operator_NIT_management
typedef struct
{
    /// This 2-bit field specifies the issue with the service from the CICAM NIT.
    EN_OP_CHANNEL_ISSUE_TYPE enChannelIssueType;
    /// The 14-bit field indicates the logical cghannel number assigned to the service whoch have not been stored in the
    /// Host logical channel list.
    U16                      u16LCN;
    /// This 8-bit field specified the number of bytes that follow the service_name_length field for describling characters
    /// of the name of the service.
    U8                       u8ServiceNameLen;
    /// These 8-bit characters indicates the name of the service.
    U8                       u8aServiceName[256];
    /// The 8-bit field specifies the number of free LCN values where the serivce may be moved without causing another collision.
    /// The Host shall at a minimum provide rhe first available LCN below and above the requested LCN from the CICAM NIT.
    U8                       u8FreeLcnNumber;
    /// The 14-bit field indicates the logical cghannel number assigned to the service whoch have not been stored in the
    /// Host logical channel list.
    U16                      u16aFreeLCN[256];
}CI_OP_SERVICE_INFO;

/// CI+ Spec v1.3 Table 5.12: URI Version 1 Message Syntax
typedef struct
{
    /// protocol_version:
    ///     This parameter indicates the version of the URI definition and is defined in Table 5.14:
    U8 u8protocol_version;

    /// reserved: N/A
    U8 u8reserved0:2;
    /// rct_copy_control_info:
    ///     This parameter describes the Encryption Plus Non-assert (RCT) bit.
    ///     The Host shall use the RCT bit to trigger redistribution control on Controlled Content when the RCT value is set to a value of one (1) in combination with the EMI bits set to a value of zero,
    ///     zero (0,0), which signals the need for redistribution control to be asserted on Controlled Content without the need to assert numeric copy control as explained in Table 5.18.
    U8 u8rct_copy_control_info:1;
    /// ict_copy_control_info:
    ///     This parameter describes the Image Constrained Trigger (ICT) bit.
    ///     The Host shall use the ICT bit to control a constrained image quality on high definition analogue component outputs explained in Table 5.17.
    U8 u8ict_copy_control_info:1;
    /// emi_copy_control_info:
    ///     This parameter describes the Encryption Mode Indicator (EMI) bits.
    ///     The CI Plus system shall use the EMI bits to exert copy control permissions of digital and analogue outputs as explained in Table 5.16:
    U8 u8emi_copy_control_info:2;

    /// aps_copy_control_info:
    ///     This parameter describes the Analogue Protection System (APS) bits
    ///     which define the setting of analogue copy protection used on the analogue output, as explained in Table 5.15:
    U8 u8aps_copy_control_info:2;
    /// rl_copy_control_info:
    ///     This field describes the retention limit of the recording and/or time-shift of content from the time that it is retained.
    ///     Figure 5.23 shows how the retention limit is applied. The default rl_copy_control_info bits in the URI message shall always be filled with the default retention limit value 0x00
    ///     except when the EMI bits are set to a value of one, one (1,1). When EMI is (1,1) the CICAM may set the rl_copy_control_info bits to a value other than 0x00 (zero) to override the default 90 minutes retention limit,
    ///     other values may signal a retention limit in hours or days. When EMI is (1,1) and the CICAM has not received information from the network then the default rl_copy_control_info value in the URI message is filled with the default retention limit value 0x00.
    U8 u8rl_copy_control_info:6;
    /// reserved: N/A
    U8 u8reserved1:2;

    /// reserved: N/A
    U8 au8reserved[5];
} CI_CC_URI_MESSAGE_V1;

/// CI+ Spec v1.3 Table 5.13: URI Version 2 Message Syntax
typedef struct
{
    /// protocol_version:
    ///     This parameter indicates the version of the URI definition and is defined in Table 5.14:
    U8 u8protocol_version;

    /// dot_copy_control_info:
    ///     This parameter describes the Digital Only Token bit.
    ///     The Host shall use the DOT bit to control analogue video outputs as explained in Table 5.19. When the EMI bits are equal to (1,1)
    ///     the CICAM may set the dot_copy_control_info bit to a value other than (0) to prohibit the output of analogue video content by the Host.
    U8 u8dot_copy_control_info:1;
    /// reserved: N/A
    U8 u8reserved:1;
    /// rct_copy_control_info:
    ///     This parameter describes the Encryption Plus Non-assert (RCT) bit.
    ///     The Host shall use the RCT bit to trigger redistribution control on Controlled Content when the RCT value is set to a value of one (1) in combination with the EMI bits set to a value of zero,
    ///     zero (0,0), which signals the need for redistribution control to be asserted on Controlled Content without the need to assert numeric copy control as explained in Table 5.18.
    U8 u8rct_copy_control_info:1;
    /// ict_copy_control_info:
    ///     This parameter describes the Image Constrained Trigger (ICT) bit.
    ///     The Host shall use the ICT bit to control a constrained image quality on high definition analogue component outputs explained in Table 5.17.
    U8 u8ict_copy_control_info:1;
    /// emi_copy_control_info:
    ///     This parameter describes the Encryption Mode Indicator (EMI) bits.
    ///     The CI Plus system shall use the EMI bits to exert copy control permissions of digital and analogue outputs as explained in Table 5.16:
    U8 u8emi_copy_control_info:2;
    /// aps_copy_control_info:
    ///     This parameter describes the Analogue Protection System (APS) bits which define the setting of
    ///     analogue copy protection used on the analogue output, as explained in Table 5.15:
    U8 u8aps_copy_control_info:2;

    /// rl_copy_control_info:
    ///     This field describes the retention limit of the recording and/or time-shift of content from the time that it is retained.
    ///     Figure 5.23 shows how the retention limit is applied. The default rl_copy_control_info bits in the URI message shall always be filled with the default retention limit value 0x00
    ///     except when the EMI bits are set to a value of one, one (1,1). When EMI is (1,1) the CICAM may set the rl_copy_control_info bits to a value other than 0x00 (zero) to override the default 90 minutes retention limit,
    ///     other values may signal a retention limit in hours or days. When EMI is (1,1) and the CICAM has not received information from the network then the default rl_copy_control_info value in the URI message is filled with the default retention limit value 0x00.
    U8 u8rl_copy_control_info;

    /// reserved: N/A
    U8 au8reserved[5];
} CI_CC_URI_MESSAGE_V2;

/// CI+ Spec v1.4 Table 8: URI Version 4 Message Syntax
typedef struct
{
    /// protocol_version:
    ///     This parameter indicates the version of the URI definition and is defined in Table 5.14:
    U8 u8protocol_version;

    /// dot_copy_control_info:
    ///     This parameter describes the Digital Only Token bit.
    ///     The Host shall use the DOT bit to control analogue video outputs as explained in Table 5.19. When the EMI bits are equal to (1,1)
    ///     the CICAM may set the dot_copy_control_info bit to a value other than (0) to prohibit the output of analogue video content by the Host.
    U8 u8dot_copy_control_info:1;
    /// reserved: N/A
    U8 u8reserved:1;
    /// rct_copy_control_info:
    ///     This parameter describes the Encryption Plus Non-assert (RCT) bit.
    ///     The Host shall use the RCT bit to trigger redistribution control on Controlled Content when the RCT value is set to a value of one (1) in combination with the EMI bits set to a value of zero,
    ///     zero (0,0), which signals the need for redistribution control to be asserted on Controlled Content without the need to assert numeric copy control as explained in Table 5.18.
    U8 u8rct_copy_control_info:1;
    /// ict_copy_control_info:
    ///     This parameter describes the Image Constrained Trigger (ICT) bit.
    ///     The Host shall use the ICT bit to control a constrained image quality on high definition analogue component outputs explained in Table 5.17.
    U8 u8ict_copy_control_info:1;
    /// emi_copy_control_info:
    ///     This parameter describes the Encryption Mode Indicator (EMI) bits.
    ///     The CI Plus system shall use the EMI bits to exert copy control permissions of digital and analogue outputs as explained in Table 5.16:
    U8 u8emi_copy_control_info:2;
    /// aps_copy_control_info:
    ///     This parameter describes the Analogue Protection System (APS) bits which define the setting of
    ///     analogue copy protection used on the analogue output, as explained in Table 5.15:
    U8 u8aps_copy_control_info:2;

    /// rl_copy_control_info:
    ///     This field describes the retention limit of the recording and/or time-shift of content from the time that it is retained.
    ///     Figure 5.23 shows how the retention limit is applied. The default rl_copy_control_info bits in the URI message shall always be filled with the default retention limit value 0x00
    ///     except when the EMI bits are set to a value of one, one (1,1). When EMI is (1,1) the CICAM may set the rl_copy_control_info bits to a value other than 0x00 (zero) to override the default 90 minutes retention limit,
    ///     other values may signal a retention limit in hours or days. When EMI is (1,1) and the CICAM has not received information from the network then the default rl_copy_control_info value in the URI message is filled with the default retention limit value 0x00.
    U8 u8rl_copy_control_info_1:8;

    /// reserved: N/A
    U8 u8reserved2:5;

    /// trick_mode_control_info:
    ///     The parameter describes the trick mode inhibit bit.
    U8 u8trick_mode_control_info:1;

    /// rl_copy_control_info:
    U8 u8rl_copy_control_info_2:2;

    /// reserved: N/A
    U8 au8reserved[4];
}CI_CC_URI_MESSAGE_V4;

/// CI+ Spec v1.3 Section 5.7.5.2: Format of the URI message
typedef union
{
    /// URI v1 Format
    CI_CC_URI_MESSAGE_V1 uri_message_v1;
    /// URI v2 Format
    CI_CC_URI_MESSAGE_V2 uri_message_v2;
    /// URI v4 Format
    CI_CC_URI_MESSAGE_V4 uri_message_v4;
    /// Raw Data of URI Message
    U8 au8URI_Message[CC_AUTH_URI_SIZE];
} CI_CC_URI_MESSAGE;

/// CI+ Spec v1.3 Table 11.26: cc_PIN_capabilities_reply APDU Syntax.
typedef struct
{
    /// capability_field:
    ///     this byte returns the capability code of the CICAM management, see Table 11.27.
    ///     The interpretation of the capability_field values are described in more detail in section 5.11.1.
    U8 u8capability_field;
    /// pin_change_time_utc:
    ///     returns the time when the CICAM PIN was last changed. This is a 40-bit field which specifies the date and time in MJD and UTC when the PIN was last changed
    ///     (See start_time field of the EIT in EN 300 468 [10]). This field is encoded as 40-bits giving the 16 LSBs MJD followed by 24-bits coded as 6 digits in 4-bit BCD.
    ///     This field shall be specified as zero if the PIN is not handled or when it has never been changed. The Host may use the 'change time'
    ///     to warn the end-user that any unattended recording programmed may fail when it was programmed before and scheduled after the time indicated by the pin_change_time_utc field.
    U8 au8pin_change_time_utc[CI_UTC_TIME_LEN];
    /// rating:
    ///     This 8-bit field is coded as DVB rating (3+years). Rating is defined in EN 300 468 [10] parental rating descriptor. This is the current rating as set in the CICAM.
    ///     This field allows the Host to exert parental control when the Host rating is set at a lower level than the CICAM rating. The Host may use the cc_PIN_MMI_req() APDU for this purpose depending on the CICAM PIN capabilities.
    ///     The CICAM shall not request a PIN entry for an age rating less than this value.
    U8 u8rating;
} CI_CC_PIN_CAPABILITIES;

/// CI+ Spec v1.3 Table 11.31: cc_PIN_event APDU Syntax
typedef struct
{
    /// program_number:
    ///     the program number of the associated Record Start protocol for this recording.
    U16 u16program_number;
    /// PINcode_status_field:
    ///     this byte returns the status of the PIN code CICAM management, see Table 11.30.
    U8 u8PINcode_status_field;
    /// rating:
    ///     This 8-bit field is coded as DVB rating (3+years). Rating is defined in EN 300 468 [10] parental rating descriptor.
    ///     It represents the rating of the broadcasted content item that triggered the cc_PIN_event() APDU.
    U8 u8rating;
    /// pin_event_time_utc:
    ///     This field returns the time when the parental rating changed requiring the entry of a PIN.
    ///     This is a 40-bit field which specifies the date and time in MJD and UTC when the parental rating changed (See start_time field of the EIT in EN 300 468 [10]).
    ///     This 40-bit field is coded as 16-bits giving the 16 LSBs of MJD followed by 24 bits coded as 6 digits in 4-bit BCD.
    U8 au8pin_event_time_utc[CI_UTC_TIME_LEN];
    /// pin_event_time_centiseconds:
    ///     This field contains the fractional part (seconds/100) of the time of the change in parental rating requiring the entry of a PIN.
    U8 u8pin_event_time_centiseconds;
    /// private_data:
    ///     These private data bytes provide the CICAM with the option to include additional CAS specific information stored with the maturity rating in the recording.
    ///     The private_data is returned to the CICAM on playback using the cc_PIN_playback() APDU.
    U8 au8private_data[CI_CC_PIN_EVENT_PRIVATE_DATA_LEN];

    /*************** RR2138 CI+ PVR Develop ***************/
    // Pin Event Valid
    BOOL bValid;
    // Need VideoBlanking
    BOOL bVideoBlanking;
    /******************************************************/
} CI_CC_PIN_EVENT;

/***************** RR2138 CI+ PVR Develop *****************/
typedef struct
{
    // CICAM License
    U16                      m_u16program_number;
    EN_CC_PVR_LICENSE_STATUS m_u8license_status;
    BOOL                     m_bUriValid;
    CI_CC_URI_MESSAGE        m_unUriMessage;
    U16                      m_u16CicamLicenseLength;
    U8                       *pu8CicamLicense;
    BOOL                     m_bLicenseAvailable;

    // HOST License
    BOOL                     m_bLicenseValid;
    U8                       m_u8play_count;
}CI_CC_URI_LICENSE;
/**********************************************************/

/***************** RR2194 CI+1.4 Develop *****************/
/// CI+ Spec v1.4 Define struct information of CICAM Virtual Channel descriptor
typedef struct _CIPLUS_Virtual_SERVICE_DATA
{
    U8 au8EventInfo[CI_VIRTUAL_CHANNEL_INFO_LEN];
    ///App Domain Identifier
    U8 au8AppDomainIdentifier[CI_VIRTUAL_CHANNEL_INFO_LEN];
}CIPLUS_Virtual_SERVICE_DATA;
/**********************************************************/

/*****************************************************************************/
/*                      Callback Function Prototypes                         */
/*****************************************************************************/
//*****************************************************************************
///f_sac_Callback
/// Description
///   Callback function of CI+ CC f_sac ( SEK, SAK = f-sac(Ks) )
/// @param u8pKs                    \b IN: Pointor to Ks
/// @param u8pSEK                   \b OUT: Pointor to SEK
/// @param u8pSAK                   \b OUT: Pointor to SAK
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
typedef BOOL (*f_sac_Callback)( U8 *u8pKs, U8 *u8pSEK, U8 *u8pSAK );

//*****************************************************************************
///f_cc_Callback
/// Description
///   Callback function of CI+ CC f_cc ( CCK, CIV = f-cc(Kp) )
/// @param eScramblerMode           \b IN: Scrambler Mode
/// @param u8pKp                    \b IN: Pointor to Kp
/// @param u8pCCK                   \b OUT: Pointor to CCK
/// @param u8pCIV                   \b OUT: Pointor to CIV
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
/// Remarks
///   You should watch out for ENDIAN issue.
///   AES CCK Size is 16 bytes.
///   DES CCK Size is 8 bytes, includes parity bits.
//*****************************************************************************
typedef BOOL (*f_cc_Callback)( E_CIPLUS_CC_SCRAMBLER_MODE eScramblerMode, U8 *u8pKp, U8 *u8pCCK, U8 *u8pCIV );

//*****************************************************************************
///f_LoadCredentials_Callback
/// Description
///   Callback function of switching PCMCIA Power.
/// @param eType                    \b IN: CI/CI+ event type
/// @return void:
//*****************************************************************************
typedef BOOL (*f_LoadCredentials_Callback)( void );
#endif
//*****************************************************************************
///f_PolarSSL_ErrorCode_Callback
/// Description
///   Callback function of the handler function for error return value of PolarSSL LIB.
/// @param eType                    \b IN: error return value of PolarSSL LIB
/// @return void:
//*****************************************************************************
typedef void (*f_PolarSSL_ErrorCode_Callback)( U32 );

//*****************************************************************************
///f_SwitchCiPower_Callback
/// Description
///   Callback function of switching PCMCIA Power.
/// @param eType                    \b IN: CI/CI+ event type
/// @return void:
//*****************************************************************************

typedef void (*f_SwitchCiPower_Callback)( BOOL bPowerOn );

//*****************************************************************************
///f_CI_Event_Callback
/// Description
///   Callback function of the event handler function for all CI/CI+ events.
/// @param eType                    \b IN: CI/CI+ event type
/// @return void:
//*****************************************************************************
typedef void (*f_CI_Event_Callback)( EN_CI_EVENT eType );

//*****************************************************************************
///f_CI_Resource_connect
/// Description
///   Callback function of CI resource for connect
/// @param u8CISlot                 \b IN: CI Slot
/// @param u16SessionNB             \b IN: Session Number
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
typedef BOOL (*f_CI_Resource_Connect_Callback)(U8 u8CISlot, U16 u16SessionNB);

//*****************************************************************************
///f_CI_Resource_connect
/// Description
///   Callback function of CI resource for data
/// @param u8CISlot                 \b IN: CI Slot
/// @param u16SessionNB             \b IN: Session Number
/// @param pRxAPDU                  \b IN: Rx APDU Data
/// @return void:
//*****************************************************************************
typedef void (*f_CI_Resource_Data_Callback)(U8 u8CISlot, U16 u16SessionNB, U8 *pRxAPDU);

//*****************************************************************************
///f_CI_Resource_connect
/// Description
///   Callback function of CI resource for close
/// @param u8CISlot                 \b IN: CI Slot
/// @param u16SessionNB             \b IN: Session Number
/// @return void:
//*****************************************************************************
typedef void (*f_CI_Resource_Close_Callback)(U8 u8CISlot, U16 u16SessionNB);

/*****************************************************************************/
/*                      Global Function Prototypes                           */
/*****************************************************************************/
//*****************************************************************************
/// Init CI module
/// @param BOOL                         \b IN: bEnable for enable / disable CI+
/// @return void:
//*****************************************************************************
void msAPI_CI_Initial( BOOL bEnable );

//*****************************************************************************
/// Reset CI module
/// @return void:
//*****************************************************************************
void msAPI_CI_ReInitial( void );

//*****************************************************************************
/// CI mainloop
/// @return void:
//*****************************************************************************
void msAPI_CI_MAINLOOP( void );

//*****************************************************************************
/// Set PMT buffer
/// @param u32BufAdr \b IN: buffer address
/// @return void:
//*****************************************************************************
void msAPI_CI_SetPMTBufAddr( U32 u32BufAdr );

//*****************************************************************************
/// Set CI MMI buffer
/// @param u32BufAdr \b IN: buffer address
/// @return void:
//*****************************************************************************
void msAPI_CI_SetMMIBufAddr( U32 u32BufAdr );

//*****************************************************************************
/// Set MHEG5 file buffer for APPMMI
/// @param u32BufAdr \b IN: buffer address
/// @return void:
//*****************************************************************************
void msAPI_CI_SetMHEG5BufAddr( U32 u32BufAdr );

//*****************************************************************************
/// Check CAM status
/// @return BOOL:
/// -TRUE: CAM is inserted
/// -FALSE: CAM is removed
//*****************************************************************************
BOOL msAPI_CI_CardDetect( void );

//*****************************************************************************
/// Check CAM is inserted or removed
/// @return E_CARD_STATE:
/// -TRUE: CAM is inserted
/// -FALSE: CAM is removed
//*****************************************************************************
E_CARD_STATE msAPI_CI_GetCardState( void );

//*****************************************************************************
/// Check CAM Type
/// @param void \b IN: CICAM State
/// @return EN_SMARTCARD_TYPE: Specific CAM
//*****************************************************************************
EN_SMARTCARD_TYPE msAPI_CI_GetCardType( void );

//*****************************************************************************
/// Get CICAM name from APPINFO text_char
/// @param u8pCICAM_Name                \b OUT: U8 pointer for return CAM name
/// @param u8NameBufferSize             \b IN: Size of Output Name Buffer
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_GetCICAMName( U8 *u8pCICAM_Name, U8 u8NameBufferSize );

//*****************************************************************************
/// Get CAM Manufacturer Name
/// @param u8pManufacturer              \b IN: U8 pointer for return Manufacturer name
/// @return void:
//*****************************************************************************
void msAPI_CI_GetManufacturerName( U8 *u8pManufacturer );

//*****************************************************************************
/// Get application type in APPINFO
/// @return EN_CI_APP_TYPE: application_type
//*****************************************************************************
EN_CI_APP_TYPE msAPI_CI_GetAppType( void );

//*****************************************************************************
/// Get manufacturer in APPINFO
/// @return U16: manufacturer
//*****************************************************************************
U16 msAPI_CI_GetManufacturer( void );

//*****************************************************************************
/// Get manufacturer code in APPINFO
/// @return U16: manufacturer code
//*****************************************************************************
U16 msAPI_CI_GetManufacturerCode( void );

//*****************************************************************************
/// Get Negotiated Buffer Size
/// @return U16: Negotiated Buffer Size
//*****************************************************************************
U16 msAPI_CI_GetNegotiatedSize( void );

//*****************************************************************************
/// Get CIS
/// @param pu8Manufacturer              \b OUT: MAPI_U8 pointer for Manufacturer
/// @param pu8ManufacturerLen           \b OUT: Size of Manufacturer Buffer
///                                         (IN: Size of Output Manufacturer Buffer; OUT: Size of return Manufacturer)
/// @param pu8Product                   \b OUT: MAPI_U8 pointer for Product
/// @param pu8ProductLen                \b OUT: Size for Product
///                                         (IN: Size of Output Product Buffer; OUT: Size of return Product)
/// @param pu8Info1                     \b OUT: MAPI_U8 pointer for Info1
/// @param pu8Info1Len                  \b OUT: Size for Info1
///                                         (IN: Size of Output Info1 Buffer; OUT: Size of return Info1)
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_GetCIS( U8 *pu8Manufacturer, U8 *pu8ManufacturerLen, U8 *pu8Product, U8 *pu8ProductLen, U8 *pu8Info1, U8 *pu8Info1Len );

//*****************************************************************************
/// Install CI event call back function
/// @param f_CI_Event_Callback          \b IN:CI event call back function
/// @return void:
//*****************************************************************************
void msAPI_CI_InstallCallback_CI_Event( f_CI_Event_Callback fnCallback_f_CI_Event );

//*****************************************************************************
/// Remove CICAM
/// @return void:
//*****************************************************************************
void msAPI_CI_RemoveCICAM( void );

//*******************************************************
//  For MMI                                            */
//*******************************************************
// Message variable
//*****************************************************************************
/// Get library version
/// @param ppVersion                    \b IN: U8 double pointer for library version
/// @return BOOL:
/// -TRUE: get version
/// -FALSE: not get version
//*****************************************************************************
BOOL msAPI_CI_GetLibVer( const MSIF_Version **ppVersion );

//*****************************************************************************
/// Get CI MMI message
/// @param void \b IN:
/// @return E_CIMSG_TYPE: MMI display status
//*****************************************************************************
E_CIMSG_TYPE msAPI_CI_GetCIMessageType( void );

//*****************************************************************************
/// Set CI MMI message
/// @param E_CIMSG_TYPE \b IN: MMI display status
/// @return void:
//*****************************************************************************
void msAPI_CI_SetCIMessageType( E_CIMSG_TYPE u8Type );

//*****************************************************************************
/// Check pcmcia register
/// @return U8:
/// -TRUE: CAM status changed
/// -FALSE: CAM status is not changed
//*****************************************************************************
U8 msAPI_CI_Polling( void );

//*****************************************************************************
/// MDrv_PCMCIA_Set_Detect_Trigger:
/// When card inserted, CD pin will be "LOW" in default.
/// Call this function by "TRUE" if CD pin be "HIGH" when card inserted.
/// @param bHighActive                  \b IN:
/// -TRUE: HIGH active
/// -FALSE: LOW active
/// @return void:
//*****************************************************************************
void msAPI_CI_SetCardDetectTrigger( BOOL bHighActive );

//*****************************************************************************
/// Notify Current PMT to CI
/// @param pu8PMTSection                \b IN: U8 pointer for Current PMT
/// @param u16PMTLength                 \b IN: length for Current PMT
/// @return void:
//*****************************************************************************
void msAPI_CI_NotifyCurrentPMTUpdate( U8 *pu8PMTSection, U16 u16PMTLength );

//*****************************************************************************
/// Notify Other PMT to CI
/// @param pu8PMTSection                \b IN: U8 pointer for Other PMT
/// @param u16PMTLength                 \b IN: length for Other PMT
/// @return void:
//*****************************************************************************
void msAPI_CI_NotifyOtherPMTUpdate( U8 *pu8PMTSection, U16 u16PMTLength );

//*****************************************************************************
///msAPI_CI_GetCurrentPMTSection
/// Description
/// Get Current PMT Section from CI LIB
/// @param pu8PMTSection                \b OUT: U8 pointer for current PMT Section
/// @param pu16PMTSectionLen            \b OUT: U16 reference for current PMT Section length
///                                         (IN: Size of Output current PMT Section Buffer; OUT: Size of return current PMT Section)
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_GetCurrentPMTSection( U8 *pu8PMTSection, U16 *pu16PMTSectionLen );

//*****************************************************************************
/// Update PMT Cache into TS Info
/// @param pu8PMTSection                \b IN: U8 pointer for PMT
/// @param u16PMTLength                 \b IN: length for PMT
/// @param bFroceUpdate                 \b IN: TRUE: Replace old cache; FALSE: Check PMT Version First
/// @return void:
//*****************************************************************************
void msAPI_CI_UpdatePMTCache( U8 *pu8PMTSection, U16 u16PMTLength, BOOL bFroceUpdate );

//*****************************************************************************
/// Limit CA_PMT Es Type Count
/// @param bEnable                      \b IN: Enable/Disable Es Type Filter
/// @param u8EsTypeCount                \b IN: length for CA_PMT Es Type
/// @return void:
//*****************************************************************************
void msAPI_CI_EnableLimitEsTypeCount( BOOL bEnable, U8 u8EsTypeCount );

//*****************************************************************************
/// Send empty PMT
/// @param u16ServiceID                 \b IN: service ID
/// @param u8PmtVersion                 \b IN: PMT version
/// @return void:
//*****************************************************************************
void msAPI_CI_SendEmptyPmt( U16 u16ServiceID, U8 u8PmtVersion );

//*****************************************************************************
/// Setup HW Reset Duration of PCMCIA.
/// @param u8HWResetDuration            \b IN: HW Reset Duration (Default: 20ms)
/// @return void:
//*****************************************************************************
void msAPI_CI_SetHWResetDuration( U8 u8HWResetDuration );

//*****************************************************************************
/// Enable CI Performance Monitor
/// @param bEnable                      \b IN: bEnable
/// @return void:
//*****************************************************************************
void msAPI_CI_EnablePerformanceMonitor( BOOL bEnable );

//*****************************************************************************
///setCaPmtSuspend
/// Description
///   Enable / Disable CA PMT suspend.
/// @param enOperateMode          \b IN: operate mode
/// @param u32Timeout          \b IN: timeout (Unit:ms)
/// @return void:
//*****************************************************************************
void msAPI_CI_setCaPmtSuspend(EN_CAS_SUSPEND_OPERATION_MODE enOperateMode, U32 u32Timeout);

//*****************************************************************************
/// Notify CI library AP will exit service
/// @return void:
//*****************************************************************************
void msAPI_CI_NotifyServiceExit( void );

//*****************************************************************************
/// Process all reminded TX, push them into CAM.
/// @return void:
//*****************************************************************************
void msAPI_CI_Process_AllTX( void );

//*****************************************************************************
/// If user want to configure TXRX / RXTX interval for special CI CAM, this function could be used.
/// Notice that this interval will impact performance.
/// Be careful to use this function, don't put huge intervals here.
/// @param u16RXTXIntervalms            \b IN: the min interval between RX and TX packets.
/// @param u16TXRXIntervalms            \b IN: the min interval between TX and RX packets.
/// @param bEnableAlways                \b IN: BOOL for enable interval always or not.
/// - TRUE: Enable interval always.
/// - FALSE: Enable interval when CI Init only.
/// @return void:
//*****************************************************************************
void msAPI_CI_Set_TXRX_Interval( U16 u16RXTXIntervalms, U16 u16TXRXIntervalms, BOOL bEnableAlways );

//*****************************************************************************
/// Set Debug Level of CI
/// @param eCI_Function                 \b IN: CI Function
/// @param u8DebugLevel                 \b IN: Debug Level
///                                                 Bigger value shows more debug msg.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SetDebugLevel( EN_CI_FUNCTION eCI_Function, U8 u8DebugLevel );

//*****************************************************************************
///configResourceDefaultSetting
/// Description
///   customize CI resource ID configure setting
/// Config Resource Default Setting of CI
/// @param eCiVersion             \b IN: CI Version of resource ID level setting
/// @param eCiPlusVersion             \b IN: CI Plus Version of resource ID level setting
/// @param bResourceHighestIdFilterEnable             \b IN: set Resource Highest Id Filter Enable
/// @return void:
//*****************************************************************************
void msAPI_CI_ConfigResourceDefaultSetting( EN_CI_VERSION eCiVersion, EN_CI_PLUS_VERSION eCiPlusVersion, BOOL bResourceHighestIdFilterEnable );

//*****************************************************************************
/// Config Resource of CI
/// @param eCI_Function                 \b IN: CI Function
/// @param bEnable                      \b IN: Config Enable/Disable
///                                                 - TRUE: Enable
///                                                 - FALSE: Disable
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_ConfigResource( EN_CI_FUNCTION eCI_Function, BOOL bEnable );

//*****************************************************************************
/// Register Customer Private Resource to Resource Agent.
/// @param u32ResourceID                \b IN: Resource ID
/// @param f_ResourceConnect            \b IN: Resource Connect Callback Function
/// @param f_ResourceData               \b IN: Resource Data Callback Function
/// @param f_ResourceClose              \b IN: Resource Close Callback Function
/// @param eReourceCIVersion            \b IN: Identify the Resource is CI or CI+ resources.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_AGENT_RegisterPrivateResource( U32 u32ResourceID, f_CI_Resource_Connect_Callback f_ResourceConnect,
                                             f_CI_Resource_Data_Callback f_ResourceData, f_CI_Resource_Close_Callback f_ResourceClose,
                                             EN_CI_VERSION eReourceCIVersion );

//*****************************************************************************
/// Send APDU of Private Resource to CICAM.
/// @param u8CISlot                     \b IN: CI Slot
/// @param u16SessionNB                 \b IN: Session Number
/// @param pAPDUData                    \b IN: APDU Data
/// @param u32APDULen                   \b IN: APDU Data Length
/// @return void:
//*****************************************************************************
void msAPI_CI_PrivateResource_Send_APDU( U8 u8CISlot, U16 u16SessionNB,
                                         const U8 *pAPDUData, U32 u32APDULen );

//*****************************************************************************
//  APPLICATION MMI
//*****************************************************************************
//*****************************************************************************
///Request APPMMI File
/// @param u8pFileName                  \b IN: U8 pointer for file name or data
/// @param u8FileDataLen                \b IN: length of file name or data
/// @param eReqType                     \b IN: request type
/// @return void:
//*****************************************************************************
void msAPI_CI_AppMmi_FileReq( U8 *u8pFileName, U8 u8FileNameLen, EN_APPMMI_REQTYPE eReqType );

//*****************************************************************************
///Inquire APPMMI File
/// @param u8pFileName                  \b IN: U8 pointer of MHEG5 file name or data
/// @param u8FileDataLen                \b IN: length of MHEG5 file name or data
/// @param eReqType                     \b IN: request type
/// @return void:
//*****************************************************************************
void msAPI_CI_AppMmi_FileInquire( U8 *u8pFileName, U8 u8FileDataLen, EN_APPMMI_REQTYPE eReqType );

//*****************************************************************************
///Abort APPMMI Request
/// @param pu8AbortReqCode              \b IN: U8 pointer of AbortReqCode
/// @param u8AbortReqCodeLen            \b IN: length of AbortReqCode
/// @return void:
//*****************************************************************************
void msAPI_CI_AppMmi_AbortReq( const U8 *pu8AbortReqCode, U8 u8AbortReqCodeLen );

//*****************************************************************************
///Request APPMMI Types
/// @return void:
//*****************************************************************************
void msAPI_CI_AppMmi_TypesReq( void );

//*****************************************************************************
///Get APPMMI Veresion
/// @return EN_CI_RESOURCE_VERSION    APPMMI Version
//*****************************************************************************
EN_CI_RESOURCE_VERSION msAPI_CI_AppMmi_GetVersion( void );

//*****************************************************************************
///Get APPMMI File Buffer
/// @return U8: buffer address
//*****************************************************************************
U8* msAPI_CI_AppMmiGetBufPtr( void );

//*****************************************************************************
///Get APPMMI SSM Value
/// @return U8: SSM Value
//*****************************************************************************
U8 msAPI_CI_AppMmi_Get_SSM(void);

/*****************************************************************************/
/*                      MMI Layer                                            */
/*****************************************************************************/
/*****************************************************************************/
/*                      Macro                                                */
/*****************************************************************************/
#define MAX_CIMMI_MENU_ITEMS        100

/*****************************************************************************/
/*                              Structures                                   */
/*****************************************************************************/
//Data structure of MMI_MENU or MMI_LIST
typedef struct
{
    U16 u16TitleLen;
    U8 *pu8Title;
    U16 u16SubtitleLen;
    U8 *pu8Subtitle;
    U16 u16BottomLen;
    U8 *pu8Bottom;
    U8 *pString[MAX_CIMMI_MENU_ITEMS];
    U8 *pStringEnd;
    U8  u8Choice_nb;
} _MMI_MENU, _MMI_LIST;

//Data structure of MMI_ENQ
typedef struct
{
    U8 bBlindAns;
    U8 u8AnsLen;
    U8 u8EnqLen;
    U8 *pu8Enq;
} _MMI_ENQ;

//Data structure of MMI_TEXT
typedef struct
{
    U8 *pu8String;
    U8  u8StringLen;
} _MMI_TEXT;

//Data stucture of MMI messages to sending to AP (Msrv) layer
typedef struct _MMI_INFO
{
    EN_MMI_TYPE enType;
    U8 *MMI_BUF;
    union
    {
        _MMI_MENU menu;
        _MMI_LIST list;
        _MMI_ENQ enq;
        _MMI_TEXT text;
    } content;
    struct _MMI_INFO *next;
} MMI_INFO;

/*****************************************************************************/
/*                      Global Variable Declarations                         */
/*****************************************************************************/

/*****************************************************************************/
/*                      Global Function Prototypes                           */
/*****************************************************************************/
//*****************************************************************************
///msAPI_CI_MMIGetData
/// Description
///   Get MMI data
/// @param void \b IN:
/// @return MMI_INFO: MMI data information
//*****************************************************************************
MMI_INFO *msAPI_CI_MMIGetData( void );

//*****************************************************************************
///Free MMI data
/// @param pMMIInfo                 \b IN: MMI data information pointer
/// @return void:
//*****************************************************************************
void msAPI_CI_MMIFreeData( MMI_INFO *pMMIInfo );

//*****************************************************************************
///msAPI_CI_RemoveControlByte
/// Description
///   Remove control bytes
/// @param pu8Req                       \b IN: U8 pointer for string
/// @param u8Len                        \b IN: length for string
/// @return void:
/// -0: fail to remove
/// -other number: the length after removing
//*****************************************************************************
U8 msAPI_CI_RemoveControlByte( U8 *pu8Req, U8 u8Len );

//*****************************************************************************
///msAPI_CI_MMIEnterMenu
/// Description
///   Enter menu
/// @return void:
//*****************************************************************************
void msAPI_CI_MMIEnterMenu( void );

//*****************************************************************************
///msAPI_CI_MMIAnswerMenu
/// Description
///   Answer menu
/// @param u8Choice                     \b IN: choice number
/// @return void:
//*****************************************************************************
void msAPI_CI_MMIAnswerMenu( U8 u8Choice );

//*****************************************************************************
///Check MMI event
/// @param void                     \b IN:
/// @return U8: event number
//*****************************************************************************
U8 msAPI_CI_MMICheckEvent( void );

//*****************************************************************************
///Clean event
/// @param u8Evt                    \b IN: event number
/// @return void:
//*****************************************************************************
void msAPI_CI_MMIDoneEvent( U8 u8Evt );

//*****************************************************************************
///msAPI_CI_MMICancelEnq
/// Description
///   Cancel ENQ
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_MMICancelEnq( void );

//*****************************************************************************
///msAPI_CI_MMIAnswerEnq
/// Description
///   Answer menu
/// @param pBuffer                      \b IN: U8 pointer for answer
/// @param u8Length                     \b IN:length for answer
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_MMIAnswerEnq( U8 *pBuffer, U8 u8Length );

//*****************************************************************************
///msAPI_CI_MMIClose
/// Description
///   Close MMI
/// @return void:
//*****************************************************************************
void msAPI_CI_MMIClose( void );

//*****************************************************************************
///msAPI_CI_MMI_SetCharacterCodingTables
/// Description
///   Set Character Coding Tables for CICAM
/// @param pu8CharacterCodingTables         \b IN: MAPI_U8 pointer for Character Coding Tables.
/// @param u8CharacterCodingTablesLength    \b IN: MAPI_U8 for Character Coding Tables length.
/// @return void:
//*****************************************************************************
void msAPI_CI_MMI_SetCharacterCodingTables( U8 *pu8CharacterCodingTables, U8 u8CharacterCodingTablesLength );

//*****************************************************************************
///msAPI_CI_NotifySystemUTCtime
/// Description
///   Notify system UTC time into CI library
/// @param pu8UTCTime                   \b IN: U8 pointer for UTC time
/// @return void:
//*****************************************************************************
void msAPI_CI_NotifySystemUTCtime( U8 *pu8UTCTime );

//*****************************************************************************
///msAPI_CI_NotifyCurrentServiceInfo
/// Description
///   Notify CI library the current service information
/// @param u16TS_ID                         \b IN: U16 for transport stream ID
/// @param u16ServiceID                     \b IN: U16 for service ID
/// @return void:
//*****************************************************************************
void msAPI_CI_NotifyCurrentServiceInfo( U16 u16CurrentTS_ID, U16 u16CurrentServiceID );

//*****************************************************************************
///msAPI_CI_FreeAllTSInfo
/// Description
///   Free all TS Info Cache in CI LIB.
/// @return void:
//*****************************************************************************
void msAPI_CI_FreeAllTSInfo( void );

#if ENABLE_CI_DT
//*****************************************************************************
//  Date & Time Resource
//*****************************************************************************
///msAPI_CI_DT_SendUTC
/// Description
/// Send date time UTC into CI library
/// @param pu8UTCTime                   \b IN: U8 pointer for UTC time
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_DT_SendUTC( U8 *pu8UTCTime );

//*****************************************************************************
///msAPI_CI_DT_GetInterval
/// Description
/// Get date time interval
/// @param pu8Interval                  \b OUT: U8 pointer for date time
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_DT_GetInterval( U8 *pu8Interval );
#endif  // #if ENABLE_CI_DT

#if ENABLE_CI_HC
//*****************************************************************************
//  Host Control Resource
//*****************************************************************************
///msAPI_CI_HC_GetTuneInfo
/// Description
/// Get host control tune information
/// @param pu16NetworkID                \b OUT: U16 pointer for network id
/// @param pu16OriginalNetworkID        \b OUT: U16 pointer for original network id
/// @param pu16TransportStreamID        \b OUT: U16 pointer for transport stream id
/// @param pu16ServiceID                \b OUT: U16 pointer for service id
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HC_GetTuneInfo( U16 *pu16NetworkID, U16 *pu16OriginalNetworkID,
                              U16 *pu16TransportStreamID, U16 *pu16ServiceID );

//*****************************************************************************
///msAPI_CI_HC_GetReplaceInfo
/// Description
/// Get host control replace information
/// @param pu8ReplacementRef            \b OUT: U8 pointer for replacement reference
/// @param pu16ReplacedPID              \b OUT: U16 pointer for replaced PID
/// @param pu16ReplacementPID           \b OUT: U16 pointer for replacement PID
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HC_GetReplaceInfo( U8 *pu8ReplacementRef, U16 *pu16ReplacedPID,
                                 U16 *pu16ReplacementPID );

//*****************************************************************************
///msAPI_CI_HC_AskRelease
/// Description
/// Ask host control release
/// @param void \b IN:
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HC_AskRelease( void );

#if ENABLE_CI_HC_V2
//*****************************************************************************
///msAPI_CI_HC_GetTuneDescriptor
/// Description
/// Get host control tune descriptor
/// @param u8pTuneDescriptor            \b OUT: U8 pointer for Tune Descriptor
/// @param u16pTuneDescriptorLen         \b OUT: MAPI_U8 pointer for Tune Descriptor length
///                                         (IN: Size of Output Tune Descriptor Buffer; OUT: Size of return Tune Descriptor)
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HC_GetTuneDescriptor( U8 *u8pTuneDescriptor, U16 *u16pTuneDescriptorLen );

//*****************************************************************************
///msAPI_CI_HC_ReplyTune
/// Description
/// Relpy Tune Status
/// @param eTuneStatus                  \b IN: Tune Status
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HC_ReplyTune( EN_HC_TUNE_REPLY_STATUS eTuneStatus );

//*****************************************************************************
///msAPI_CI_HC_GetTunePMTSection
/// Description
/// Get host control tune PMT section
/// @param u8pTunePMTSection            \b OUT: U8 pointer for Tune PMT Section
/// @param u16pTunePMTSectionLen         \b OUT: MAPI_U16 pointer for Tune PMT Section length
///                                         (IN: Size of Output Tune PMT Section Buffer; OUT: Size of return Tune PMT Section)
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HC_GetTunePMTSection( U8 *u8pTunePMTSection, U16 *u16pTunePMTSectionLen );
#endif

//*****************************************************************************
///msAPI_CI_HC_NotifyTuneDone
/// Description
/// Notify CI LIB Tune Done
/// @return void:
//*****************************************************************************
void msAPI_CI_HC_NotifyTuneDone( void );

//*****************************************************************************
///msAPI_CI_HC_GetBroadcastServiceId
/// Description
///   Get HC broadcast service ID.
/// @return U16: HC broadcast service ID
//*****************************************************************************
U16 msAPI_CI_HC_GetBroadcastServiceId( void );
#endif  //#if ENABLE_CI_HC

#if ENABLE_CI_CC
//*****************************************************************************
//  Content Control Resource
//*****************************************************************************
///msAPI_CI_CC_GetCredentialsBufferAddr
/// Description
/// Get CI+ Credential Buffer Address
/// @param void                         \b IN:
/// @return U8* : CI+ Credential Buffer Address
//*****************************************************************************
U8* msAPI_CI_CC_GetCredentialsBufferAddr( void );

//*****************************************************************************
///msAPI_CI_CC_SetCredential
/// Description
///   Set all kinds of credential into CI LIB.
/// @param eType                        \b IN: Credential type
/// @param pu8Credential                \b IN: Pointor to loaded credential
/// @param u16CredentialLen             \b IN: Length of loaded credential
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
/// Remarks
///   Pay attention to the setup sequence of Root Certificate,
///   Host Device Certificate, Host Brand Certificate, and HDQ.
//*****************************************************************************
BOOL msAPI_CI_CC_SetCredential( EN_CREDENTIAL_TYPE eType, U8 *pu8Credential,
                                U16 u16CredentialLen );

//*****************************************************************************
///msAPI_CI_CC_InstarllCallback_f_sac
/// Description
///   Install f-sac for CI+ CC.
/// @param fnCallback_f_sac             \b IN: Pointor to Callback function of f-sac
/// @return void:
/// Remarks
///   You should watch out for ENDIAN issue.
//*****************************************************************************
void msAPI_CI_CC_InstallCallback_f_sac( f_sac_Callback fnCallback_f_sac );

//*****************************************************************************
///msAPI_CI_CC_InstallCallback_f_cc
/// Description
///   Install f-cc for CI+ CC.
/// @param fnCallback_f_cc              \b IN: Pointor to Callback function of f-cc
/// @return void:
/// Remarks
///   You should watch out for ENDIAN issue.
//*****************************************************************************
void msAPI_CI_CC_InstallCallback_f_cc( f_cc_Callback fnCallback_f_cc );

//*****************************************************************************
///msAPI_CI_CC_InstallCallback_LoadCredentials
/// Description
///   Load CI+ Credentials for CI+ CC.
/// @param f_LoadCredentials_Callback   \b IN: Pointor to Callback function of Load Credentials
/// @return void:
/// Remarks
///   Pay attention to the setup sequence of Root Certificate,
///   Host Device Certificate, Host Brand Certificate, and HDQ.
//*****************************************************************************
void msAPI_CI_CC_InstallCallback_LoadCredentials( f_LoadCredentials_Callback fnCallback_LoadCredentials );

//*****************************************************************************
///msAPI_CI_CC_GetCCK
/// Description
///   Get Dscmb setting
/// @param peScrambleMode               \b OUT: E_CIPLUS_CC_SCRAMBLER_MODE for CI+ Scramble mode
/// @param peKeyMode                    \b OUT: E_CIPLUS_CC_KEY_MODE for CI+ Key mode
/// @param pu8Key                       \b OUT: U8 pointer for CI+ Key
/// @param pu8IV                        \b OUT: U8 pointer for CI+ IV
/// @return void:
//*****************************************************************************
void msAPI_CI_CC_GetCCK( E_CIPLUS_CC_SCRAMBLER_MODE *peScrambleMode, E_CIPLUS_CC_KEY_MODE *peKeyMode, U8 *pu8Key, U8 *pu8IV );

//*****************************************************************************
///msAPI_CI_CC_SetCCK
/// Description
///   Set Content Control Key into CI library. (Only used for CHIP bring-up)
/// @param eScrambleMode                \b IN: E_CIPLUS_CC_SCRAMBLER_MODE for scrambler mode
/// @param pu8OddCCK                    \b IN: U8 pointer for odd CC key
/// @param pu8EvenCCK                   \b IN: U8 pointer for even CC key
/// @param pu8CIV                       \b IN: U8 pointer for CIV
/// @return MAPI_BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SetCCK( E_CIPLUS_CC_SCRAMBLER_MODE eScrambleMode, U8 *pu8OddCCK, U8 *pu8EvenCCK, U8 *pu8CIV );

//*****************************************************************************
///msAPI_CI_CC_SetDescryptKeyForEncryptedCredentials
/// Description
///   If customer uses self encrypted key for Credentials bin, customer should notify CI LIB.
/// @param u8pAesXcbcKey                \b IN: U8 pointer for AES XCBC key
/// @param u8pAesCbcKey                 \b IN: U8 pointer for AES CBC key
/// @param u8pAesCbcIV                  \b IN: U8 pointer for AES CBC IV
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SetDescryptKeyForEncryptedCredentials( U8 *u8pAesXcbcKey, U8 *u8pAesCbcKey, U8 *u8pAesCbcIV );

//*****************************************************************************
/// Get CAM brand ID
/// @param pu16BrandID                  \b OUT: U16 pointer for CAM Brand ID
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_Get_CICAM_BrandID( U16 *pu16BrandID );

//*****************************************************************************
/// Get credential valid date range
/// @param u32ValidFromDate             \b OUT: U32 for credential valid from date
/// @param u32ValidToDate               \b OUT: U32 for credential valid to date
/// @return void:
//*****************************************************************************
void msAPI_CI_CC_Get_CredentialValidDateRange( U32 *u32ValidFromDate, U32 *u32ValidToDate );

//*****************************************************************************
/// Get current URI information
/// @param pu8RCT                       \b OUT: U8 pointer for RCT
/// @param pu8EMI                       \b OUT: U8 pointer for EMI
/// @param pu8APS                       \b OUT: U8 pointer for APS
/// @param pu8ICT                       \b OUT: U8 pointer for ICT
/// @param pu8RL                        \b OUT: U8 pointer for RL
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_GetURI( U8 *pu8RCT, U8 *pu8EMI, U8 *pu8APS, U8 *pu8ICT, U8 *pu8RL );

//*****************************************************************************
/// msAPI_CI_CC_RecordingAcceptable
/// @param bSecurityStorageSupport      \b IN: PVR support security recording or not
/// @return BOOL:
/// - TRUE: yes
/// - FALSE: no
//*****************************************************************************
BOOL msAPI_CI_CC_RecordingAcceptable( BOOL bSecurityStorageSupport );

//*****************************************************************************
///msAPI_CI_CC_Retrigger_URI
/// Description
///   re trigger current URI information from CI+ CAM.
/// @return void:
//*****************************************************************************
void msAPI_CI_CC_Retrigger_URI( void );

//*****************************************************************************
/// Reset URI information
/// @return void:
//*****************************************************************************
void msAPI_CI_CC_Reset_URI( void );

//-------------------------------------------------------------------------------------------------
/// CI Plus Retention Limit Time
/// @param  u8URI_EMI                           \b IN: u8URI_EMI
/// @param  u8URI_RL                            \b IN: u8URI_RL
/// @param  pu32RententionLimitTime             \b OUT: Rentention Limit Time
/// @return TRUE : Rentention Limit PVR file.
/// @return FALSE: Non-Rentention Limit PVR file.
//-------------------------------------------------------------------------------------------------
BOOL msAPI_CI_CC_GetRetentionLimitTime( CI_CC_URI_LICENSE stUriLicense, U32 *pu32RententionLimitTime );

//*****************************************************************************
/// Set credential type
/// @param bProductionCredentials               \b IN: BOOL
/// - TRUE: production credential
/// - FALSE: testing credential (in DEFALUT)
/// @param bCredentialsBinFromFlash             \b IN: BOOL
/// - TRUE: CredentialsBin is in Flash
/// - FALSE: CredentialsBin is in CI LIB (in DEFALUT)
/// @return void:
//*****************************************************************************
void msAPI_CI_CC_SetCredentialsType( BOOL bProductionCredentials, BOOL bCredentialsBinFromFlash );

//*****************************************************************************
/// Get credential type
/// @param void \b IN:
/// @return BOOL:
/// - TRUE: production credential
/// - FALSE: testing credential
//*****************************************************************************
BOOL msAPI_CI_CC_GetCredentialsType( void );

//*****************************************************************************
/// Get CAM version
/// @param void \b IN:
/// @return EN_CI_VERSION: CAM version
//*****************************************************************************
EN_CI_VERSION msAPI_CI_CC_CAM_Mode( void );

//*****************************************************************************
/// Set FID
/// @param u8Fid \b IN: U8 for FID
/// @param bEnable \b IN: BOOL
/// - TRUE: Add FID to list
/// - FALSE: Remove FID from list
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SetFID( U8 u8Fid, BOOL bEnable );

//*****************************************************************************
/// Save auth key setting to flash
/// @param pstCiKeySetting              \b IN: MS_CI_KEY_SETTING pointer for key setting
/// @param bEnableEncrypt               \b IN: BOOL
/// - TRUE: Enable encrytion function
/// - FALSE: Disable encrytion function
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SaveKeyToFlash( MS_CI_KEY_SETTING* pstCiKeySetting, BOOL bEnableEncrypt );

//*****************************************************************************
/// Load auth key setting from flash
/// @param pstCiKeySetting              \b OUT: MS_CI_KEY_SETTING pointer for key setting
/// @param bEnableEncrypt               \b IN: BOOL
/// - TRUE: Enable encrytion function
/// - FALSE: Disable encrytion function
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_LoadKeyFromFlash( MS_CI_KEY_SETTING *pstCiKeySetting, BOOL bEnableEncrypt );

//*****************************************************************************
/// Get HOST ID from Host Device Certificate
/// @param u8pHOSTID                    \b OUT: U8 pointer for HOST ID
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_GetHOSTID( U8 *u8pHOSTID );

//*****************************************************************************
/// Get CICAM ID from CICAM Device Certificate
/// @param u8pCICAMID                   \b OUT: U8 pointer for CICAM ID
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_GetCICAMID( U8 *u8pCICAMID );

//*****************************************************************************
/// Get CI Plus Authentication status
/// @return BOOL:
/// - TRUE: Authentication
/// - FALSE: Non Authentication
//*****************************************************************************
BOOL msAPI_CI_CC_GetAuthenticationStatus( void );

//*****************************************************************************
/// Get CC Version of CICAM
/// @return EN_CC_VERSION: CC Version
//*****************************************************************************
EN_CC_VERSION msAPI_CI_CC_GetCicamCCVersion( void );

#if ENABLE_CI_CC_V2
//*****************************************************************************
/// Get current URI information v2
/// @param pu8DOT                       \b OUT: U8 pointer for DOT
/// @param pu8RCT                       \b OUT: U8 pointer for RCT
/// @param pu8EMI                       \b OUT: U8 pointer for EMI
/// @param pu8APS                       \b OUT: U8 pointer for APS
/// @param pu8ICT                       \b OUT: U8 pointer for ICT
/// @param pu8RL                        \b OUT: U8 pointer for RL
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_GetURIv2( U8 *pu8DOT, U8 *pu8RCT, U8 *pu8EMI, U8 *pu8APS, U8 *pu8ICT, U8 *pu8RL );

//*****************************************************************************
///msAPI_CI_CC_SetSrmSupported
/// Description
///     Set CC Srm Supported
/// @param bSupported     \b IN: bSupported or not
/// @return void:
//*****************************************************************************
void msAPI_CI_CC_SetSrmSupported(BOOL bSupported);

//*****************************************************************************
///msAPI_CI_CC_GetSrmDataLength
/// Description
///     get CC SRM Data Length
/// @return U16: SRM Data Length
//*****************************************************************************
U16 msAPI_CI_CC_GetSrmDataLength(void);

//*****************************************************************************
///msAPI_CI_CC_GetSrmData
/// Description
/// @param u8SrmDataBuffer     \b IN: SrmData Buffer for copy data.
/// @param u16SrmDataBufferLength        \b IN: SrmData Buffer Length.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_GetSrmData(U8 *u8SrmDataBuffer, U16 u16SrmDataBufferLength);

//*****************************************************************************
///msAPI_CI_CC_SendRecordStart
/// Description
///   Send CC cc_sac_data_req APDU for Record Start message.
/// @param eOperatingMode                   \b IN: Record operating mode
/// @param u16ProgramNumber                 \b IN: The program number of the associated Record Start protocol for this recording.
/// @param u8pPinCode                       \b IN: Payload for the PIN code, one byte is used for each pin code digit in ASCII format.
/// @param u16PinCodeLen                    \b IN: Length of Pin Code Data
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SendRecordStart( EN_CC_PVR_OPERATING_MODE eOperatingMode, U16 u16ProgramNumber, U8* u8pPinCode, U16 u16PinCodeLen );

//*****************************************************************************
///msAPI_CI_CC_ChangeRecordOperatingMode
/// Description
///   Send CC cc_sac_data_req APDU for Change Operating Mode message.
/// @param eOperatingMode                   \b IN: Record operating mode
/// @param u16ProgramNumber                 \b IN: The program number of the associated Record Start protocol for this recording.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_ChangeRecordOperatingMode( EN_CC_PVR_OPERATING_MODE eOperatingMode, U16 u16ProgramNumber );

//*****************************************************************************
///msAPI_CI_CC_SendRecordStop
/// Description
///   Send CC cc_sac_data_req APDU for Record Stop message.
/// @param u16ProgramNumber                 \b IN: The program number of the associated Record Start protocol for this recording.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SendRecordStop( U16 u16ProgramNumber );

//*****************************************************************************
///msAPI_CI_CC_ReqPinCapabilities
/// Description
///   Send CC cc_PIN_capabilities_req APDU to CICAM.
/// @param void                             \b IN:
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_ReqPinCapabilities( void );

//*****************************************************************************
///msAPI_CI_CC_SendPinCmd
/// Description
///   Send CC cc_PIN_cmd APDU to CICAM.
/// @param u8pPinCode                       \b IN: Ponitor of PIN code, one byte is used for each pin code digit in ASCII format.
/// @param u8PinCodeLen                     \b IN: Length of u8pPinCodeData
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SendPinCmd( U8 *u8pPinCode, U8 u8PinCodeLen );

//*****************************************************************************
///msAPI_CI_CC__SendPinPlayback
/// Description
///     Send CC cc_PIN_playback APDU to CICAM.
/// @param stPinEvent                       \b IN: stPinEvent object.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_SendPinPlayback( const CI_CC_PIN_EVENT* stpPinEvent );

//*****************************************************************************
///msAPI_CI_CC_ReqPinMMI
/// Description
///   Send CC cc_PIN_MMI_req APDU to CICAM.
/// @param u8pPinCode                       \b IN: Ponitor of PIN code, one byte is used for each pin code digit in ASCII format.
/// @param u8PinCodeLen                     \b IN: Length of u8pPinCodeData.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_ReqPinMMI( U8 *u8pPinCode, U8 u8PinCodeLen );

//*****************************************************************************
///maAPI_CI_CC_PinEventUpdate
/// Description
///     Get CC Pin Event
/// @param pCI_CC_PIN_EVENT                 \b OUT: Ponitor of CC Pin Event.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CC_PinEventUpdate( CI_CC_PIN_EVENT* pPinEvent );

//*****************************************************************************
///msAPI_CI_CC_GetRecordStartStatus
/// Description
///   Get CC Record Start Status.
/// @param void                             \b IN:
/// @return EN_CC_SAC_SYNC_CNF_STATUS: Record Start Status
//*****************************************************************************
EN_CC_SYNC_CNF_STATUS msAPI_CI_CC_GetRecordStartStatus( void );

//*****************************************************************************
///msAPI_CI_CC_GetModeChangeStatus
/// Description
///   Get CC Mode Change Status.
/// @param void                             \b IN:
/// @return EN_CC_SAC_SYNC_CNF_STATUS: Mode Change Status
//*****************************************************************************
EN_CC_SYNC_CNF_STATUS msAPI_CI_CC_GetModeChangeStatus( void );

//*****************************************************************************
///msAPI_CI_CC_GetRecordStopStatus
/// Description
///   Get CC Record Stop Status.
/// @param void                             \b IN:
/// @return EN_CC_SAC_SYNC_CNF_STATUS: Record Stop Status
//*****************************************************************************
EN_CC_SYNC_CNF_STATUS msAPI_CI_CC_GetRecordStopStatus( void );

//*****************************************************************************
///msAPI_CI_CC_GetCicamPinCapability
/// Description
///   Get CC Cicam Pin Capability.
/// @param void                             \b IN:
/// @return EN_CC_CICAM_PIN_CAPABILITIES: Cicam Pin Capability
//*****************************************************************************
EN_CC_CICAM_PIN_CAPABILITIES msAPI_CI_CC_GetCicamPinCapability( void );

//*****************************************************************************
///msAPI_CI_CC_GetCicamRating
/// Description
///   Get CC Cicam Rating.
/// @param void                             \b IN:
/// @return U8: CC Cicam Rating
//*****************************************************************************
U8 msAPI_CI_CC_GetCicamRating( void );

//*****************************************************************************
///msAPI_CI_CC_GetPINcodeStatus
/// Description
///   Get CC Cicam Rating.
/// @param bPinCmdReply    \b IN: status reply target
/// @param bpTimeout      \b OUT: check time out or not
/// @return EN_CC_PIN_CODE_STATUS:
//*****************************************************************************
EN_CC_PIN_CODE_STATUS msAPI_CI_CC_GetPINcodeStatus( BOOL bPinCmdReply, BOOL* bpTimeout );

//*****************************************************************************
///msAPI_CI_CC_GetPINcodeCache
/// Description
///   Get CC Cicam Rating.
/// @return U16:
//*****************************************************************************
U16 msAPI_CI_CC_GetPINcodeCache( void );
#endif
#endif  // #if ENABLE_CI_CC

#if ENABLE_CI_HSS
//*****************************************************************************
//  Host Service Shunning
//*****************************************************************************
///msAPI_CI_HSS_Check
/// Description
///   HSS check
/// @return void:
//*****************************************************************************
void msAPI_CI_HSS_Check( void );

//*****************************************************************************
///msAPI_CI_HSS_Active
/// Description
///   HSS active
/// @param bActive                          \b IN: BOOL
/// - TRUE: Active HSS
/// - FALSE: In-active HSS
/// @return void:
//*****************************************************************************
void msAPI_CI_HSS_Active( BOOL bActive );

//*****************************************************************************
///msAPI_CI_HSS_Set
/// Description
///   Set HSS information
/// @param pu8Section                       \b IN: U8 pointer for SDT cache
/// @param u16TS_ID                         \b IN: U16 for transport stream ID
/// @param u16ServiceID                     \b IN: U16 for service ID
/// @return void:
//*****************************************************************************
void msAPI_CI_HSS_Set( U8 *pu8Section, U16 u16Length, U16 u16TS_ID, U16 u16ServiceID );

//*****************************************************************************
///msAPI_CI_HSS_Get
/// Description
///   Get HSS status
/// @return BOOL:
/// - TRUE: HSS active
/// - FALSE: HSS in-active
//*****************************************************************************
BOOL msAPI_CI_HSS_Get( void );

//*****************************************************************************
///msAPI_CI_HSS_SetEventDelay
/// Description
///   Delay Send CI_EVENT_HSS
/// @return void:
//*****************************************************************************
void msAPI_CI_HSS_SetEventDelay(U32 u32Timeout);
#endif  // #if ENABLE_CI_HSS

#if ENABLE_CI_HLC
//*****************************************************************************
//  Host Language & Country Resource
//*****************************************************************************
//*****************************************************************************
///msAPI_CI_HLC_SetCountry
/// Description
///   Set HLC country
/// @param pCountry                         \b IN: U8 pointer for country
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HLC_SetCountry( U8 *pCountry );

//*****************************************************************************
///msAPI_CI_HLC_SetLanguage
/// Description
///   Set HLC language
/// @param pLanguage                        \b IN: U8 pointer for language
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_HLC_SetLanguage( U8 *pLanguage );
#endif // #if ENABLE_CI_HLC

#if ENABLE_CI_CU
//*****************************************************************************
//  CAM Firmware Upgrade Resource
//*****************************************************************************
///msAPI_CI_CU_SetHostOPMode
/// Description
///   Set CU host operation mode
/// @param eType                            \b IN: EN_HOST_OPERATING_TYPE for operation mode
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CU_SetHostOPMode( EN_HOST_OPERATING_TYPE eType );

//*****************************************************************************
///msAPI_CI_CU_GetProgressStatus
/// Description
///   Get CU progressing status
/// @param pu8Percentage                    \b OUT: U8 pointer for CU percentage
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CU_GetProgressStatus( U8 *pu8Percentage );

//*****************************************************************************
///msAPI_CI_CU_GetDownloadTime
/// Description
///   Get CU download time
/// @param pu16Time                         \b OUT: U16 pointer for CU download time
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_CU_GetDownloadTime( U16 *pu16Time );

//*****************************************************************************
///msAPI_CI_CU_GetState
/// Description
///   Get CU state
/// @return BOOL:
/// - TRUE: Under CU progress
/// - FALSE: Otherwise
//*****************************************************************************
BOOL msAPI_CI_CU_GetState( void );
#endif  // #if ENABLE_CI_CU

#if ENABLE_CI_OP
//*****************************************************************************
//  Operator Profile Resource
//*****************************************************************************
///msAPI_CI_OP_SendStatusReq
/// Description
///   Send operator_status_req() APDU to enter profile and/or request current profile information.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendStatusReq( void );

//*****************************************************************************
///msAPI_CI_OP_SendNitReq
/// Description
///   Send operator_nit_req() APDU to request the current CICAM NIT sections.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendNitReq( void );

//*****************************************************************************
///msAPI_CI_OP_SendInfoReq
/// Description
///   Send operator_info_req() APDU to request the Operator information.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendInfoReq( void );

//*****************************************************************************
///msAPI_CI_OP_SendSearchStart
/// Description
///   Send operator_search_start() APDU to notify CICAM that Host permission to initiate a network search..
/// @param bUnattendedFlag                  \b IN: Unattended Flag
/// @param u8pServiceType                   \b IN: Ponitor of Service Type
/// @param u8ServiceTypeLoopLen             \b IN: Length of Service Type
/// @param u8pDeliveryCapability            \b IN: Ponitor of Delivery Capability
/// @param u8DeliveryCapabilityLoopLen      \b IN: Length of Delivery Capability
/// @param u8pApplicationCapability         \b IN: Ponitor of Application Capability
/// @param u8ApplicationCapabilityLoopLen   \b IN: Length of Application Capability
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendSearchStart( BOOL bUnattendedFlag,
                                  U8 *u8pServiceType, U8 u8ServiceTypeLoopLen,
                                  U8 *u8pDeliveryCapability, U8 u8DeliveryCapabilityLoopLen,
                                  U8 *u8pApplicationCapability, U8 u8ApplicationCapabilityLoopLen );

//*****************************************************************************
///msAPI_CI_OP_SendExit
/// Description
///   Send operator_exit() APDU to notify CICAM that Host has left the service operator profile.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendExit( void );

//*****************************************************************************
///msAPI_CI_OP_SendTuneStatus
/// Description
///   Send operator_tune_status() APDU to notify CICAM that Host tune request has completed.
/// @param u8DescriptorNumber               \b IN: This 8-bit field identifies the next unprocessed descriptor number in the operator_tune() APDU which has not been processed by the Host.
/// @param u8SignalStrength                 \b IN: Signal Strength
/// @param u8SignalQuality                  \b IN: Signal Quality
/// @param eStatus                          \b IN: The status of the tune request.
/// @param pu8Descriptor                    \b IN: A loop of delivery system descriptors that describes the currently tuned location of the Host that is
///                                                passing through the CICAM or descriptors causing an error. The descriptor loop shall contain a single delivery
///                                                system location only, which may be described by one or more descriptors.
/// @param u16DescriptorLen                 \b IN: Length of delivery system descriptors.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendTuneStatus( U8 u8DescriptorNumber, U8 u8SignalStrength,
                                 U8 u8SignalQuality, EN_OP_TUNE_STATUS eStatus,
                                 U8* pu8Descriptor, U16 u16DescriptorLen );

//*****************************************************************************
///msAPI_CI_OP_SendEntitlementAck
/// Description
///   Send operator_entitlement_ack() APDU for confirmation that entitlement change has been enacted.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendEntitlementAck( void );

//*****************************************************************************
///msAPI_CI_OP_SendSearchCancel
/// Description
///   Send operator_search_cancel() APDU to the CICAM to cancel a profile search sequence.
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_SendSearchCancel( void );

//*****************************************************************************
///msAPI_CI_OP_GetStatus
/// Description
///   Get status body of operator_status().
/// @param pstInfo                          \b OUT: U8 pointer of status body of operator_status()
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_GetStatus( CI_OP_STATUS *pstInfo );

//*****************************************************************************
///msAPI_CI_OP_GetInfo
/// Description
///   Get info body of operator_info().
/// @param pstOP_Info                       \b OUT: U8 pointer of info body of operator_info()
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_GetInfo( CI_OP_INFO *pstOP_Info );

//*****************************************************************************
///msAPI_CI_OP_GetNIT
/// Description
///   Get NIT of operator_nit().
/// @param pu8OP_NIT                        \b OUT: U8 pointer of NIT of operator_nit()
/// @param u16pOP_NITLen                     \b OUT: U16 pointer for Length of NIT of operator_nit()
///                                             (IN: Size of Output NIT Buffer; OUT: Size of return NIT)
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_GetNIT( U8 *pu8OP_NIT, U16 *u16pOP_NITLen );

//*****************************************************************************
///msAPI_CI_OP_GetTuneDescriptor
/// Description
///   Get tune descriptor for OP
/// @param pu8TuneDescriptor                \b OUT: U8 pointer for Tune Descriptor
/// @param u16pTuneDescriptorLen             \b OUT: U16 pointer for Tune Descriptor length
///                                             (IN: Size of Output Tune Descriptor Buffer; OUT: Size of return Tune Descriptor)
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_OP_GetTuneDescriptor( U8 *u8pTuneDescriptor, U16 *u16pTuneDescriptorLen );

//*****************************************************************************
///msAPI_CI_OP_IsCicamInProfile
/// Description
///   Query the status which is In-Profile mode or Out-Profile for CI+ CAM.
/// @return MAPI_BOOL:
/// - TRUE: In-Profile
/// - FALSE: Out-Profile
//*****************************************************************************
BOOL msAPI_CI_OP_IsCicamInProfile( void );
#endif

#if ENABLE_CI_SAS
//*****************************************************************************
//  Specific Application Support Resource
//*****************************************************************************
///msAPI_CI_SAS_ConnectRqst
/// Description
///   Send an SAS_connect_rqst() APDU with a unique identifier of the private Host application.
/// @param u8pPrivateHostApplicationID      \b IN: U8 point for unique identifier of the private Host application
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SAS_ConnectRqst( U8 *u8pPrivateHostApplicationID );

//*****************************************************************************
///msAPI_CI_SAS_AsyncMsg
/// Description
///    The sas_async_msg() APDU is bi-directional and can originate from either side of the CHI.
///    It is the responsibility of the applications to take care of overflow prevention and ensure reliable delivery of messages.
/// @param u8SessionIndex               \b IN: U8 SAS Session Index of the SAS session
/// @param u8MsgNb                      \b IN: U8 Message Nb
/// @param u16MsgLen                    \b IN: U16 Length of Message
/// @param u8pMsg                       \b IN: U8 point for Message
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SAS_AsyncMsg( U8 u8SessionIndex, U8 u8MsgNb, U16 u16MsgLen, U8 *u8pMsg );
#endif

#if ENABLE_CI_AUTH
/* tag + length + protocol_version + protocol_name + CANAL_READY_HOST_BRAND + CANAL_READY_HOST_MODEL + signature */
void msAPI_CI_AUTH_SetCanalReadyAuthBin( U8 *u8pCanalReadyAuthBin, U16 u16CanalReadyAuthBinSize );
#endif

//*****************************************************************************
//  APIs of PolarSSL operation
//*****************************************************************************
//*****************************************************************************
///msAPI_CI_SSL_AesEcbCrypt
/// Description
///   Do AES-128 ECB Encryption/Decryption.
/// @param u8CryptMode                  \b IN: Crypt Mode - AES_DECRYPT(0) or AES_ENCRYPT(1)
/// @param pu8CryptKey                  \b IN: Pointor to Crypt Key
/// @param pu8CryptText                 \b IN: Pointor to Crypt Text
/// @param u16CryptTextLen              \b IN: Length of Crypt Text
/// @param pu8OutputCryptText           \b OUT: Pointor to Output Crypt Text
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SSL_AesEcbCrypt( U8 u8CryptMode, U8 *pu8CryptKey,
                               U8 *pu8CryptText, U16 u16CryptTextLen,
                               U8 *pu8OutputCryptText );

//*****************************************************************************
///msAPI_CI_SSL_AesCbcCrypt
/// Description
///   Do AES-128 CBC Encryption/Decryption.
/// @param u8CryptMode                  \b IN: Crypt Mode - AES_DECRYPT(0) or AES_ENCRYPT(1)
/// @param pu8CryptKey                  \b IN: Pointor to Crypt Key
/// @param pu8CryptText                 \b IN: Pointor to Crypt Text
/// @param u16CryptTextLen              \b IN: Length of Crypt Text
/// @param pu8CryptIV                   \b IN: Pointor to Crypt IV
/// @param pu8OutputCryptText           \b OUT: Pointor to Output Crypt Text
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SSL_AesCbcCrypt( U8 u8CryptMode, U8 *pu8CryptKey,
                               U8 *pu8CryptText, U16 u16CryptTextLen,
                               U8 *pu8CryptIV,
                               U8 *pu8OutputCryptText );

//*****************************************************************************
///msAPI_CI_SSL_SHA1
/// Description
///   Do SHA-1 Hash.
/// @param pu8InputData                 \b IN: Pointor to Input Data
/// @param u16InputDataLen              \b IN: Length of Input Data
/// @param pu8HashVaule                 \b OUT: Pointor to Hash Value
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SSL_SHA1( U8 *pu8InputData, U16 u16InputDataLen,
                        U8 *pu8HashVaule );

//*****************************************************************************
///msAPI_CI_SSL_SHA256
/// Description
///   Do SHA-256 Hash.
/// @param pu8InputData                 \b IN: Pointor to Input Data
/// @param u16InputDataLen              \b IN: Length of Input Data
/// @param pu8HashVaule                 \b OUT: Pointor to Hash Value
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SSL_SHA256( U8 *pu8InputData, U16 u16InputDataLen,
                          U8 *pu8HashVaule );

//*****************************************************************************
///msAPI_CI_SSL_MD5_Hash
/// Description
///   Do MD5 Hash.
/// @param pu8InputData         \b IN: Pointor to Input Data
/// @param u16InputDataLen      \b IN: Length of Input Data
/// @param pu8HashVaule         \b OUT: Pointor to Hash Value
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
//*****************************************************************************
BOOL msAPI_CI_SSL_MD5_Hash( U8 *pu8InputData, U16 u16InputDataLen,
                            U8 *pu8HashVaule );

//*****************************************************************************
///msAPI_CI_SSL_GetRandomNum
/// Description
///   Get Random Number.
/// @param pu8RandomNum                 \b OUT: Pointor to Output Random Number
/// @param u16RandomNumLen              \b IN: Length of Random Number
/// @return BOOL:
/// - TRUE: success
/// - FALSE: fail
/// Remarks
///   The length of Random Number can't be bigger than 256 bytes once.
//*****************************************************************************
BOOL msAPI_CI_SSL_GetRandomNum( U8 *pu8RandomNum, U16 u16RandomNumLen );

//*****************************************************************************
/// Install error code of polarSSL callback function
/// @param fnCallback_f_PolarSSL_ErrorCode  \b IN: f_PolarSSL_ErrorCode_Callback pointer for error code of polarSSL callback function
/// @return void:
//*****************************************************************************
void msAPI_CI_SSL_InstallCallback_PolarSSL_ErrorCode( f_PolarSSL_ErrorCode_Callback fnCallback_f_PolarSSL_ErrorCode );

//*****************************************************************************
/// Following functions are only for special test using special CICAM.
//*****************************************************************************

//*****************************************************************************
/// This function is used only for internal auto-testing.
/// When calling it, CI library treat CAM as removed.
/// @param bEnable                          \b IN: BOOL
/// - TRUE: Remove CAM
/// - FALSE: Insert CAM
/// @return void:
//*****************************************************************************
void msAPI_CI_SetDetectEnable( BOOL bEnable );

//*****************************************************************************
///msAPI_CI_SetBreakPoint
/// Description
///   Don't Use
///   This function is used only for Break Point of CI Flow.
/// @param eBreakPoint                      \b IN: break point purpose
/// @return void:
//*****************************************************************************
void msAPI_CI_SetBreakPoint( EN_CI_BREAK_POINT eBreakPoint );

//*****************************************************************************
///msAPI_CI_IsBreakPointOK
/// Description
///   Don't Use
///   This function is used only for Break Point of CI Flow.
/// @param eBreakPoint                      \b IN: break point purpose
/// @return void:
//*****************************************************************************
BOOL msAPI_CI_IsBreakPointOK( EN_CI_BREAK_POINT eBreakPoint );

//*****************************************************************************
///msAPI_CI_WriteAttribMem
/// Description
///   Write attribute memory.
/// @param u16Addr                          \b IN: U16 for write address
/// @param u8Value                          \b IN: U8 for write value
/// @return void:
//*****************************************************************************
void msAPI_CI_WriteAttribMem( U16 u16Addr, U8 u8Value );

//*****************************************************************************
///msAPI_CI_ReadAttribMem
/// Description
///   Read attribute memory.
/// @param u16Addr                          \b IN: U16 for read address
/// @param pDest                            \b OUT: U8 for read value
/// @return void:
//*****************************************************************************
void msAPI_CI_ReadAttribMem( U16 u16Addr, U8 *pDest );

//*****************************************************************************
///msAPI_CI_WriteIOMem
/// Description
///   Write IO memory.
/// @param u16Addr                          \b IN: U16 for write address
/// @param u8Value                          \b IN: U8 for write value
/// @return void:
//*****************************************************************************
void msAPI_CI_WriteIOMem( U16 u16Addr, U8 u8Value );

//*****************************************************************************
///msAPI_CI_ReadIOMem
/// Description
///   Read IO memory.
/// @param u16Addr                          \b IN: U16 for read address
/// @return U8: read value
//*****************************************************************************
U8 msAPI_CI_ReadIOMem( U16 u16Addr );

//*****************************************************************************
///msAPI_CI_controlInitTImeout
/// Description
///   Turn ON/OFF Initial timeout.
/// @param eControlInitTimeout               \b IN: EN_CI_CONTROL_INIT_TIMEOUT for turn ON/OFF
/// @return void:
//*****************************************************************************
void msAPI_CI_controlInitTImeout( EN_CI_CONTROL_INIT_TIMEOUT eControlInitTimeout );

//*****************************************************************************
///msAPI_CI_getFuncStatus
/// Description
///   Judge Resource is Connecting
/// @param eCI_Function               \b IN: Resource Name
/// @return: TRUE: Connecting    FALSE: Disconnect
//*****************************************************************************
BOOL msAPI_CI_getFuncStatus(EN_CI_FUNCTION eCI_Function);

//*****************************************************************************
///msAPI_CI_setHCWaitPmtThreshold
/// Description
///   Set HC Wait PMT Timeout
/// @param u32WaitTimeMs              \b IN: Timeout
/// @return: void
//*****************************************************************************
void msAPI_CI_setHCWaitPmtThreshold(U32 u32WaitTimeMs);

/***************** RR2138 CI+ PVR Develop *****************/
BOOL msAPI_CI_CC_GetCicamUriLicenseUpdate(CI_CC_URI_LICENSE *pstUriLicense, BOOL bWaitPop);
void msAPI_CI_CC_UriMappingConvert(BOOL bScramble, BOOL bRecording, BOOL bPlaybacking,
                                   CI_CC_URI_LICENSE pstUriLicense, U8 *u8URI_DOT, U8 *u8URI_RCT, U8 *u8URI_EMI, U8 *u8URI_APS, U8 *u8URI_ICT, U8 *u8URI_RL);
BOOL msAPI_CI_CC_ExchangePlaybackLicense(U32 u32TimeStamp, CI_CC_URI_LICENSE *pstUriLicense, BOOL bPlayback);
BOOL msAPI_CI_CC_GetHostUriLicenseUpdate(U32 *u32TimeStamp, CI_CC_URI_LICENSE *pstUriLicense, BOOL bPlayback);
U8 msAPI_CI_CC_GetLicenseCount(void);
void msAPI_CI_CC_SupportCopyNeverRecording(BOOL bSupport);
/*********************************************************/

/***************** RR2194 CI+1.4 Develop *****************/
void msAPI_CI_AppInfo_EnterCicamVirtualChannel(void);
void msAPI_CI_AppInfo_SendHDSConfirm(EN_APPINFO_HDS_STATUS enHDSStatus);
BOOL msAPI_CI_AppInfo_NotifyPowerDown(void);
BOOL msAPI_CI_OP_SendOPNitManagement(EN_OP_NIT_ERROR_FIELD enErrorCode, U8 u8ServiceNum, CI_OP_SERVICE_INFO *pstServiceInfo);
BOOL msAPI_CI_HC_ReplyHCTunerStatus(CI_HC_TUNER_STATUS *pstTunerStatus);
BOOL msAPI_CI_HC_GetHCTuneLCNInfo(U16 *pu16LogicChannelNumber);
BOOL msAPI_CI_HC_GetHCTuneTripletInfo(U16 *pu16OriginalNetworkID, U16 *pu16TransportStreamID, U16 *pu16ServiceID, U16 *pu16DeliverySystemDescTag);
BOOL msAPI_CI_HC_GetHCTuneQuietlyFlag(void);
BOOL msAPI_CI_HC_GetHCAppRunningFlag(void);
/*********************************************************/

//*****************************************************************************
/// Above functions are only for special test using special CICAM.
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // #ifndef _MSAPI_CI_H_

///*** please do not remove change list tag ***///
///***$Change: 1445493 $***///
