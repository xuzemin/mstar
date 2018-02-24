/******************************************************************************
 *   $ Copyright $ Sony Corporation
 *-----------------------------------------------------------------------------
 *   File Name   : $File: sut_rx23x.c $
 *   Modified    : $Date: 2013/10/18 $ By $Author: $
 *   Revision    : $Revision: 0.60 $
 *   Description : SUT-Rx23x Tuner Control Sample Code
 *                 This code is not include I2C communication function.
 *                 It is necessary to add codes for the I2C communication
 *                 properly to execute and compile the code.
 *-----------------------------------------------------------------------------
 * This program may contain information about unfinished products and is subject
 * to change without notice.
 * Sony cannot assume responsibility for any problems arising out of the
 * use of the program
 *****************************************************************************/
/******************************************************************************
 *   includes:
 *    - system includes
 *    - application includes
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "userdef.h"
#include "sut_rx23x_rssi.h"

/*-----------------------------------------
 Add include files, if needed
-------------------------------------------*/

/******************************************************************************
 ******************************************************************************
 ******************************************************************************
 * type definition (struct / enum):
 ******************************************************************************
 ******************************************************************************
 *****************************************************************************/

typedef struct sony_ascot3_adjust_param_t {
    UINT8 OUTLMT;            /**< Addr:0x68 Bit[1:0] : Maximum IF output. (0: 1.5Vp-p, 1: 1.2Vp-p) */
    UINT8 RF_GAIN;           /**< Addr:0x69 Bit[6:4] : RFVGA gain. 0xFF means Auto. (RF_GAIN_SEL = 1) */
    UINT8 IF_BPF_GC;         /**< Addr:0x69 Bit[3:0] : IF_BPF gain. */
    UINT8 RFOVLD_DET_LV1_VL; /**< Addr:0x6B Bit[3:0] : RF overload RF input detect level. (FRF <= 172MHz) */
    UINT8 RFOVLD_DET_LV1_VH; /**< Addr:0x6B Bit[3:0] : RF overload RF input detect level. (172MHz < FRF <= 464MHz) */
    UINT8 RFOVLD_DET_LV1_U;  /**< Addr:0x6B Bit[3:0] : RF overload RF input detect level. (FRF > 464MHz) */
    UINT8 IFOVLD_DET_LV_VL;  /**< Addr:0x6C Bit[2:0] : Internal RFAGC detect level. (FRF <= 172MHz) */
    UINT8 IFOVLD_DET_LV_VH;  /**< Addr:0x6C Bit[2:0] : Internal RFAGC detect level. (172MHz < FRF <= 464MHz) */
    UINT8 IFOVLD_DET_LV_U;   /**< Addr:0x6C Bit[2:0] : Internal RFAGC detect level. (FRF > 464MHz) */
    UINT8 IF_BPF_F0;         /**< Addr:0x6D Bit[5:4] : IF filter center offset. */
    UINT8 BW;                /**< Addr:0x6D Bit[1:0] : 6MHzBW(0x00) or 7MHzBW(0x01) or 8MHzBW(0x02) or 1.7MHzBW(0x03) */
    UINT8 FIF_OFFSET;        /**< Addr:0x6E Bit[4:0] : 5bit signed. IF offset (kHz) = FIF_OFFSET x 50 */
    UINT8 BW_OFFSET;         /**< Addr:0x6F Bit[4:0] : 5bit signed. BW offset (kHz) = BW_OFFSET x 50 (BW_OFFSET x 10 in 1.7MHzBW) */
    UINT8 AGC_SEL;           /**< Addr:0x74 Bit[5:4] : AGC pin select. (0: AGC1, 1: AGC2) 0xFF means Auto (by config flags) */
    UINT8 IF_OUT_SEL;        /**< Addr:0x74 Bit[1:0] : IFOUT pin select. (0: IFOUT1, 1: IFOUT2) 0xFF means Auto. (by config flags) */
    UINT8 IS_LOWERLOCAL;     /**< Addr:0x9C Bit[0]   : Local polarity. (0: Upper Local, 1: Lower Local) */
} sony_ascot3_adjust_param_t;

/*************************************************
 Block ID definition for I2C access
**************************************************/
typedef enum {
    TERR_1ST_TUNER,   /* Tag for 1st Tuner Block                      */
    TERR_2ND_TUNER,   /* Tag for 2nd Tuner Block for dual tuner model */
} BLOCKID;

typedef enum {
    PORT1,            /* use 1 port. use only Dualport model */
    PORT2             /* use 2 port. use Single  & Dualport model */
} IFOUT_AGC_PORT;

typedef enum {
    CABLE,            /* use cable input        */
    TERR              /* use terrestrial input */
} ANT_SWITCH;

typedef enum {
    OFF,              /* use LNA ON       */
    ON                /* use LNA OFF      */
} LNA;

#if 0
typedef enum {
    DISABLE,          /* FILTER disable   */
    ENABLE            /* FILTER enable    */
} FILTER;
#endif


typedef enum {
    SONY_ASCOT3_TV_SYSTEM_UNKNOWN,
    /* Analog */
    SONY_ASCOT3_ATV_MN_EIAJ,  /* System-M (Japan) */
    SONY_ASCOT3_ATV_MN_SAP,   /* System-M (US) */
    SONY_ASCOT3_ATV_MN_A2,    /* System-M (Korea) */
    SONY_ASCOT3_ATV_BG,       /* System-B/G */
    SONY_ASCOT3_ATV_I,        /* System-I */
    SONY_ASCOT3_ATV_DK,       /* System-D/K */
    SONY_ASCOT3_ATV_L,        /* System-L */
    SONY_ASCOT3_ATV_L_DASH,   /* System-L DASH */
    /* Digital */
    SONY_ASCOT3_DTV_8VSB,     /* ATSC 8VSB */
    SONY_ASCOT3_DTV_QAM,      /* US QAM */
    SONY_ASCOT3_DTV_ISDBT_6,  /* ISDB-T 6MHzBW */
    SONY_ASCOT3_DTV_ISDBT_7,  /* ISDB-T 7MHzBW */
    SONY_ASCOT3_DTV_ISDBT_8,  /* ISDB-T 8MHzBW */
    SONY_ASCOT3_DTV_DVBT_5,   /* DVB-T 5MHzBW */
    SONY_ASCOT3_DTV_DVBT_6,   /* DVB-T 6MHzBW */
    SONY_ASCOT3_DTV_DVBT_7,   /* DVB-T 7MHzBW */
    SONY_ASCOT3_DTV_DVBT_8,   /* DVB-T 8MHzBW */
    SONY_ASCOT3_DTV_DVBT2_1_7,/* DVB-T2 1.7MHzBW */
    SONY_ASCOT3_DTV_DVBT2_5,  /* DVB-T2 5MHzBW */
    SONY_ASCOT3_DTV_DVBT2_6,  /* DVB-T2 6MHzBW */
    SONY_ASCOT3_DTV_DVBT2_7,  /* DVB-T2 7MHzBW */
    SONY_ASCOT3_DTV_DVBT2_8,  /* DVB-T2 8MHzBW */
    SONY_ASCOT3_DTV_DVBC_6,   /* DVB-C 6MHzBW */
    SONY_ASCOT3_DTV_DVBC_8,   /* DVB-C 8MHzBW */
    SONY_ASCOT3_DTV_DVBC2_6,  /* DVB-C2 6MHzBW */
    SONY_ASCOT3_DTV_DVBC2_8,  /* DVB-C2 8MHzBW */
    SONY_ASCOT3_DTV_DTMB,     /* DTMB */
    
    SONY_ASCOT3_ATV_MIN = SONY_ASCOT3_ATV_MN_EIAJ,
    SONY_ASCOT3_ATV_MAX = SONY_ASCOT3_ATV_L_DASH,
    SONY_ASCOT3_DTV_MIN = SONY_ASCOT3_DTV_8VSB,
    SONY_ASCOT3_DTV_MAX = SONY_ASCOT3_DTV_DTMB,
    SONY_ASCOT3_TV_SYSTEM_NUM /* SONY_ASCOT3_DTV_DTMB + 1 */
} RECEIVE_MODE;

#if 0
///FREQ type define
typedef enum
{
    ///FREQ INVALID
    IF_FREQ_INVALID,
    ///FREQ B
    IF_FREQ_B,              // 38.90 MHz
    ///FREQ G
    IF_FREQ_G,              // 38.90 MHz
    ///FREQ I
    IF_FREQ_I,              // 38.90 MHz
    ///FREQ DK
    IF_FREQ_DK,             // 38.90 MHz
    ///FREQ L
    IF_FREQ_L,              // 38.90 MHz
    ///FREQ L PRIME
    IF_FREQ_L_PRIME,        // 33.90 MHz
    ///FREQ MN
    IF_FREQ_MN,             // 45.75 MHz
    ///FREQ J
    IF_FREQ_J,              // 58.75 MHz
    ///FREQ PAL 38
    IF_FREQ_PAL_38,         // 38.00 MHz
    ///FREQ MAX IF FREQ
    IF_FREQ_MAX_IF_FREQ,
    ///Digital mode
    IF_DIGITAL_MODE
} IF_FREQ;
#endif
typedef struct _S_SUT_RE23x_dependency_func
{
    UINT8 (*i2c_read)(UINT8, UINT8, UINT8*, MS_U16, UINT8*, MS_U16); 
    UINT8 (*i2c_write)(UINT8, UINT8, UINT8*, MS_U16, UINT8*, MS_U16); 
    void (*ms_delay)(MS_U32);
    UINT8 (*hw_rst_control)(UINT8);
}S_SUT_RE23x_dependency_func, *pS_SUT_RE23x_dependency_func;

/*************************************************
 default slave address
**************************************************/
#define SLAVE_1ST_ADDRESS   0xC0

/*************************************************
 Number of demod setting
**************************************************/

/*************************************************
 Tuner Setting
**************************************************/
/*********************************************
 If you modify Tuner status, please modify 
 following parameter.
*********************************************/
#define XTAL         (0x10)  // 16MHz

#define AUTO         (0xFF)
#define OFFSET(ofs)  ((UINT8)(ofs) & 0x1F)
#define BW_6         (0x00)
#define BW_7         (0x01)
#define BW_8         (0x02)
#define BW_1_7       (0x03)

#define IIC_CH_SUT                      0 // NO USE
#define SUT_DEBUG_PRINT(x)              // x

/* Optimized table for SUT-Rx23x module */
static const sony_ascot3_adjust_param_t g_param_table_Rx23x[SONY_ASCOT3_TV_SYSTEM_NUM] = {

    /*
    OUTLMT    IF_BPF_GC                                           BW              BW_OFFSET         IF_OUT_SEL
      |  RF_GAIN  |     RFOVLD_DET_LV1    IFOVLD_DET_LV  IF_BPF_F0 |   FIF_OFFSET     |        AGC_SEL |  IS_LOWERLOCAL
      |     |     |    (VL)  (VH)  (U)   (VL)  (VH)  (U)    |      |       |          |          |     |     |          */
    {0x00, AUTO, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(0),  OFFSET(0),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_TV_SYSTEM_UNKNOWN */
    /* Analog */
    {0x00, AUTO, 0x05, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(0),  OFFSET(1),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_MN_EIAJ   (System-M (Japan)) */
    {0x00, AUTO, 0x05, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(0),  OFFSET(1),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_MN_SAP    (System-M (US)) */
    {0x00, AUTO, 0x05, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(3),  OFFSET(1),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_MN_A2     (System-M (Korea)) */
    {0x00, AUTO, 0x05, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, BW_7,  OFFSET(11), OFFSET(5),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_BG        (System-B/G) */
    {0x00, AUTO, 0x05, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, BW_8,  OFFSET(2),  OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_I         (System-I) */
    {0x00, AUTO, 0x05, 0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, BW_8,  OFFSET(2),  OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_DK        (System-D/K) */
    {0x00, AUTO, 0x03, 0x03, 0x06, 0x03, 0x03, 0x03, 0x03, 0x00, BW_8,  OFFSET(2),  OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_L         (System-L) */
    {0x00, AUTO, 0x03, 0x03, 0x06, 0x03, 0x03, 0x03, 0x03, 0x00, BW_8,  OFFSET(-1), OFFSET(4),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_ATV_L_DASH    (System-L DASH) */
    /* Digital */
    {0x00, AUTO, 0x09, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, BW_6,  OFFSET(-6), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_8VSB      (ATSC 8VSB) */
    {0x00, AUTO, 0x09, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-6), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_QAM       (US QAM) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-9), OFFSET(-5), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_ISDBT_6   (ISDB-T 6MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_7,  OFFSET(-7), OFFSET(-6), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_ISDBT_7   (ISDB-T 7MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-5), OFFSET(-7), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_ISDBT_8   (ISDB-T 8MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT_5    (DVB-T 5MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT_6    (DVB-T 6MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_7,  OFFSET(-6), OFFSET(-5), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT_7    (DVB-T 7MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-4), OFFSET(-6), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT_8    (DVB-T 8MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_1_7,OFFSET(-10),OFFSET(-10),PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT2_1_7 (DVB-T2 1.7MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT2_5   (DVB-T2 5MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT2_6   (DVB-T2 6MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_7,  OFFSET(-6), OFFSET(-5), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT2_7   (DVB-T2 7MHzBW) */
    {0x00, AUTO, 0x09, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-4), OFFSET(-6), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBT2_8   (DVB-T2 8MHzBW) */
    {0x00, AUTO, 0x05, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-6), OFFSET(-4), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBC_6    (DVB-C 6MHzBW) */
    {0x00, AUTO, 0x05, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-2), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBC_8    (DVB-C 8MHzBW) */
    {0x00, AUTO, 0x03, 0x08, 0x08, 0x08, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-6), OFFSET(-2), PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBC2_6   (DVB-C2 6MHzBW) */
    {0x00, AUTO, 0x03, 0x08, 0x08, 0x08, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-2), OFFSET(0),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_DTV_DVBC2_8   (DVB-C2 8MHzBW) */
    {0x00, AUTO, 0x04, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(2),  OFFSET(1),  PORT2, PORT2, 0x00}  /**< SONY_ASCOT3_DTV_DTMB      (DTMB) */
};

static sony_ascot3_adjust_param_t *param_table;

static S_SUT_RE23x_dependency_func sut_re23x_dependency_func_obj =
{
    NULL,
    NULL,
    NULL,
    NULL,
};

/*************************************************
 stdout function for debug
**************************************************/
/* #define DBG_PRINT_OUT */
#ifdef  DBG_PRINT_OUT
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...)
#endif

/******************************************************************************
 ******************************************************************************
 ******************************************************************************
 * constants & variable:
 *  - constant
 *  - global variable
 *  - static variable
 ******************************************************************************
 ******************************************************************************
 *****************************************************************************/

/******************************
 I2C Access Block ID
 ******************************/
static BLOCKID tuner_block_id;

/******************************************************************************
 ******************************************************************************
 ******************************************************************************
 * function prototype:
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************/
    
/*************************************************
 I2C access function
**************************************************/

static INT16 iic_write_val(INT16 id, UINT8 subadr, UINT8 val);
static INT16 iic_read_val(INT16 id, UINT8 subadr, UINT8* val);
static INT16 iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len);
static INT16 iic_read(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len);

static INT16 write_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
);

static INT16 read_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
);


/*************************************************
 Wait
**************************************************/
static void waitms(UINT32 ms);

/*************************************************
 Command Wrapper
**************************************************/
static int cmd_init(void);
//static int cmd_tune(int argc, char **argv); 
//static int cmd_sleep(int argc, char **argv);
//static int cmd_antsw(int argc, char **argv);
//static int cmd_shift(int argc, char **argv);

static int cmd_getrssi(float *float_rssi);
/* status */
//static int cmd_help(int argc, char **argv);                             /* help */
//static int cmd_error(int argc, char **argv);

/*************************************************
 Tuning Sequece
**************************************************/
static void x_pon(void);                                                /* tuner: Initialize        */
static void x_tune(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal);     /* tuner: tune              */
static void x_tune_end(void);                                           /* tuner: tune (after wait) */
static void x_fin(void);                                                /* tuner: sleep             */
static void x_read_ss(UINT16* value);

// static void tuner_gpio(UINT8 port, UINT8 val);
static UINT8* tuner_init_setparam(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal, UINT8 reg);
static UINT8 tuner_setextctrl(UINT32 frequency, RECEIVE_MODE mode);
static INT16 tuner_calcRSSI(UINT16 reg);
static UINT8 tuner_setModuleOffset(UINT32 freq, RECEIVE_MODE mode, UINT8 reg);

/* utility */
UINT8 mdev_Tuner_LNA_enable(UINT8 enable);

#if 0
/******************************************************************************
 * main
 *-----------------------------------------------------------------------------
 * Input : INT16 argc, char* argv[]
 * Output: none
 * Return: int
 *****************************************************************************/
int main(int argc, char* argv[]) {
    INT16 i;

    param_table = (sony_ascot3_adjust_param_t*)g_param_table_Rx23x;

    if (argc < 2) {
        cmd_help(argc - 1, argv);
        return 1;
    }else if (strcmp(argv[1], "1st") == 0) {
        tuner_block_id = TERR_1ST_TUNER;
    }else if (strcmp(argv[1], "help") == 0) {
        cmd_help(argc - 1, argv);
        return 0 ;
        
    }else {
        DBG_PRINT("!!! Command Error !!!\n");
        cmd_help(argc - 1, argv);
        return 1;
    }

/*------------------ I2C  Driver open ------------------------*/
/*    Add code to open I2C driver interface.                  */
/*------------------------------------------------------------*/

    /* cut first arg */
    for( i = 0; i < argc - 2; i++ ){ argv[i] = argv[i+2];}

    /* Search/Execute Command */
    if (strcmp(argv[0], "help") == 0) {
        cmd_help(argc - 2, argv);
    } else if (strcmp(argv[0], "init") == 0) {
        cmd_init(argc - 2, argv);
    } else if (strcmp(argv[0], "tune") == 0) {
        cmd_tune(argc - 2, argv);
    } else if (strcmp(argv[0], "sleep") == 0) {
        cmd_sleep(argc - 2, argv);    
    } else if (strcmp(argv[0], "antsw") == 0) {
        cmd_antsw(argc - 2, argv);
    } else if (strcmp(argv[0], "shift") == 0) {
        cmd_shift(argc - 2, argv);
    } else if (strcmp(argv[0], "rssi") == 0) {
        cmd_getrssi(argc - 2, argv);
    } else {
        cmd_error(argc - 2, argv);
    }

/*------------------ I2C  Driver close -----------------------*/
/*    Add code to close I2C driver interface.                 */
/*------------------------------------------------------------*/

    return 0;
}
#endif
/******************************************************************************
 * cmd_init
 *-----------------------------------------------------------------------------
 * 
 *****************************************************************************/
static int cmd_init(void)
{
    DBG_PRINT("Enter cmd_init\n");

    x_pon();

    return 0;
}

#if 0
/******************************************************************************
 * cmd_tune
 *-----------------------------------------------------------------------------
 *
 *****************************************************************************/
static int cmd_tune(int argc, char **argv)
{
    int i;
    UINT32 frequency;
    RECEIVE_MODE mode;

    DBG_PRINT("Enter cmd_tune\n");

    if(argc > 1) frequency = atoi(argv[1]);
    else frequency = 57000;    /* Default: 57000kHz */ 

    mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;
    if (argc > 2) {
        
        if (strncmp(argv[2], "ATSC_8VSB", 9) == 0) mode = SONY_ASCOT3_DTV_8VSB;
        if (strncmp(argv[2], "US_QAM"   , 6) == 0) mode = SONY_ASCOT3_DTV_QAM;
        if (strncmp(argv[2], "ISDBT"    , 5) == 0) mode = SONY_ASCOT3_DTV_ISDBT_6;
        if (strncmp(argv[2], "ISDBT_6M" , 8) == 0) mode = SONY_ASCOT3_DTV_ISDBT_6;
        if (strncmp(argv[2], "ISDBT_7M" , 8) == 0) mode = SONY_ASCOT3_DTV_ISDBT_7;
        if (strncmp(argv[2], "ISDBT_8M" , 8) == 0) mode = SONY_ASCOT3_DTV_ISDBT_8;                
        if (strncmp(argv[2], "DVBT_6M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBT_6;
        if (strncmp(argv[2], "DVBT_7M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBT_7;
        if (strncmp(argv[2], "DVBT_8M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBT_8;
        if (strncmp(argv[2], "DVBT2_6M"  ,8) == 0) mode = SONY_ASCOT3_DTV_DVBT2_6;
        if (strncmp(argv[2], "DVBT2_7M"  ,8) == 0) mode = SONY_ASCOT3_DTV_DVBT2_7;
        if (strncmp(argv[2], "DVBT2_8M"  ,8) == 0) mode = SONY_ASCOT3_DTV_DVBT2_8;
        if (strncmp(argv[2], "DTMB"     , 4) == 0) mode = SONY_ASCOT3_DTV_DTMB;

        if (strncmp(argv[2], "A_MN"     , 4) == 0) mode = SONY_ASCOT3_ATV_MN_SAP;
        if (strncmp(argv[2], "A_BG"     , 4) == 0) mode = SONY_ASCOT3_ATV_BG;
        if (strncmp(argv[2], "A_I"      , 3) == 0) mode = SONY_ASCOT3_ATV_I;
        if (strncmp(argv[2], "A_DK"     , 4) == 0) mode = SONY_ASCOT3_ATV_DK;
        if (strncmp(argv[2], "A_L_N"    , 5) == 0) mode = SONY_ASCOT3_ATV_L;
        if (strncmp(argv[2], "A_L_D"    , 5) == 0) mode = SONY_ASCOT3_ATV_L_DASH;
        
        if (strncmp(argv[2], "DVBC"     , 4) == 0) mode = SONY_ASCOT3_DTV_DVBC_8;
        if (strncmp(argv[2], "DVBC_6M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBC_6;
        if (strncmp(argv[2], "DVBC_8M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBC_8;
        if (strncmp(argv[2], "DVBC2_8M" , 8) == 0) mode = SONY_ASCOT3_DTV_DVBC2_8;

    } else {
         ;
    }

    if(argv[3]){
        if((strncmp(argv[3], "KOREA", 5) == 0) && (strncmp(argv[2], "A_MN" , 4) == 0)) {
            mode = SONY_ASCOT3_ATV_MN_A2;
        }
    }
     
    if(mode == SONY_ASCOT3_TV_SYSTEM_UNKNOWN){
        DBG_PRINT("ERROR : selected system is Illegal.\n");
        return 0;
    }     

    x_tune(frequency, mode, 1);
    waitms(50);
    x_tune_end();

    return 0;

}
#endif

#if 0
/******************************************************************************
 * cmd_sleep
 *-----------------------------------------------------------------------------
 * 
 *****************************************************************************/
static int cmd_sleep(int argc, char **argv)
{
    DBG_PRINT("Enter cmd_sleep\n");

    x_fin();

    return 0;
}
#endif
#if 0
/******************************************************************************
 * cmd_antsw
 *-----------------------------------------------------------------------------
 * 
 *****************************************************************************/
static int cmd_antsw(int argc, char **argv)
{

    ANT_SWITCH ant;

    DBG_PRINT("Enter cmd_antsw\n");

    if(argc > 1) {
        if (strcmp(argv[1], "CABLE") == 0) {
            ant = CABLE;
        }else if (strcmp(argv[1], "TERR") == 0) {
            ant = TERR;
        }else {
            DBG_PRINT("Illigal Params. Use CABLE.\n");
            ant = CABLE;
        }
    }else {
        ant = CABLE;
    }

    tuner_gpio(1, ant);

    return 0;
}
#endif

#if 0
/******************************************************************************
 * cmd_tune
 *-----------------------------------------------------------------------------
 *
 *****************************************************************************/
static int cmd_shift(int argc, char **argv)
{
    int i;
    UINT32 frequency;
    RECEIVE_MODE mode;

    DBG_PRINT("Enter cmd_tune\n");

    if(argc > 1) frequency = atoi(argv[1]);
    else frequency = 57000;    /* Default: 57000kHz */ 

    mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;
    if (argc > 2) {
        
        if (strncmp(argv[2], "ATSC_8VSB", 9) == 0) mode = SONY_ASCOT3_DTV_8VSB;
        if (strncmp(argv[2], "US_QAM"   , 6) == 0) mode = SONY_ASCOT3_DTV_QAM;
        if (strncmp(argv[2], "ISDBT"    , 5) == 0) mode = SONY_ASCOT3_DTV_ISDBT_6;
        if (strncmp(argv[2], "ISDBT_6M" , 8) == 0) mode = SONY_ASCOT3_DTV_ISDBT_6;
        if (strncmp(argv[2], "ISDBT_7M" , 8) == 0) mode = SONY_ASCOT3_DTV_ISDBT_7;
        if (strncmp(argv[2], "ISDBT_8M" , 8) == 0) mode = SONY_ASCOT3_DTV_ISDBT_8;                
        if (strncmp(argv[2], "DVBT_6M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBT_6;
        if (strncmp(argv[2], "DVBT_7M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBT_7;
        if (strncmp(argv[2], "DVBT_8M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBT_8;
        if (strncmp(argv[2], "DVBT2_6M"  ,8) == 0) mode = SONY_ASCOT3_DTV_DVBT2_6;
        if (strncmp(argv[2], "DVBT2_7M"  ,8) == 0) mode = SONY_ASCOT3_DTV_DVBT2_7;
        if (strncmp(argv[2], "DVBT2_8M"  ,8) == 0) mode = SONY_ASCOT3_DTV_DVBT2_8;
        if (strncmp(argv[2], "DTMB"     , 4) == 0) mode = SONY_ASCOT3_DTV_DTMB;

        if (strncmp(argv[2], "A_MN"     , 4) == 0) mode = SONY_ASCOT3_ATV_MN_SAP;
        if (strncmp(argv[2], "A_BG"     , 4) == 0) mode = SONY_ASCOT3_ATV_BG;
        if (strncmp(argv[2], "A_I"      , 3) == 0) mode = SONY_ASCOT3_ATV_I;
        if (strncmp(argv[2], "A_DK"     , 4) == 0) mode = SONY_ASCOT3_ATV_DK;
        if (strncmp(argv[2], "A_L_N"    , 5) == 0) mode = SONY_ASCOT3_ATV_L;
        if (strncmp(argv[2], "A_L_D"    , 5) == 0) mode = SONY_ASCOT3_ATV_L_DASH;
        
        if (strncmp(argv[2], "DVBC"     , 4) == 0) mode = SONY_ASCOT3_DTV_DVBC_8;
        if (strncmp(argv[2], "DVBC_6M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBC_6;
        if (strncmp(argv[2], "DVBC_8M"  , 7) == 0) mode = SONY_ASCOT3_DTV_DVBC_8;
        if (strncmp(argv[2], "DVBC2_8M" , 8) == 0) mode = SONY_ASCOT3_DTV_DVBC2_8;

    } else {
         ;
    }

    if(argv[3]){
        if((strncmp(argv[3], "KOREA", 5) == 0) && (strncmp(argv[2], "A_MN" , 4) == 0)) {
            mode = SONY_ASCOT3_ATV_MN_A2;
        }
    }
     
    if(mode == SONY_ASCOT3_TV_SYSTEM_UNKNOWN){
        DBG_PRINT("ERROR : selected system is Illegal.\n");
        return 0;
    }     
     
    x_tune(frequency, mode, 0);
    waitms(10);
    x_tune_end();

    return 0;

}
#endif


/******************************************************************************
 * cmd_getrssi
 *-----------------------------------------------------------------------------
 * 
 *****************************************************************************/
static int cmd_getrssi(float *float_rssi)
{
    INT16 rssi_x100;
	UINT16 reg;

    DBG_PRINT("Enter cmd_getrssi\n");

    x_read_ss(&reg);
    rssi_x100 = tuner_calcRSSI(reg);

    *float_rssi = (float)rssi_x100/100.0;
    
    DBG_PRINT("SSI:%02d:%02d.%02d, f_ssi=%f\n", (UINT8)tuner_block_id + 1, rssi_x100 / 100, rssi_x100 > 0 ? (rssi_x100 % 100) : -1 * (rssi_x100 % 100),*float_rssi);

    return 0;
}

static INT16 tuner_calcRSSI(UINT16 reg){

    INT32 rssi_x100;
    INT16 val;
    INT32 coef_x100;
    INT32 ofs_x100;
    UINT8 tmp;

    iic_read_val ( tuner_block_id, 0x78, &tmp );
    if(tmp == 0x07){ 
        coef_x100 = 125; ofs_x100 = 1800;
    }else {
        coef_x100 = 100; ofs_x100 = 0;
    }
	
/*
  RSSI           =  COEF      * (reg / 8) + OFS
  RSSI * 100     =  coef_x100 * (reg / 8) + offs_x100
                 = (coef_x100 *  reg      + offs_x100 * 8) >> 3;
*/

    if(reg >= 0x0400) val = (INT16)reg - 0x0800;
	else              val = (INT16)reg;
	
    rssi_x100 = ((coef_x100 * (INT32)(val)) + (ofs_x100 * 8)) >> 3;
	
    return (INT16)rssi_x100;

}

#if 0
/******************************************************************************
 * cmd_help
 *-----------------------------------------------------------------------------
 * help
 *****************************************************************************/
static int cmd_help(int argc, char **argv)
{

    DBG_PRINT("\n\n");

    DBG_PRINT("------------------------------ \n");
    DBG_PRINT("\n");
    DBG_PRINT("*********************************************************\n");
    DBG_PRINT(" main \n");
    DBG_PRINT(" : set tuner slave address (1st or 2nd) before all command\n");
    DBG_PRINT("   Exp : Slv 0xC0 initialization \n");  
    DBG_PRINT("          ./<name> 1st init \n");
    DBG_PRINT("   Exp : Slv 0xC2 initialization \n");
    DBG_PRINT("          ./<name> 2nd init \n");
    DBG_PRINT("\n");    
    DBG_PRINT("*********************************************************\n");
    DBG_PRINT("####### COMMANDS #######\n");
    DBG_PRINT("init\n");
    DBG_PRINT("        tuner initialization\n");
    DBG_PRINT("\n");
    DBG_PRINT("tune [freq] [mode] [region(option)]\n");
    DBG_PRINT("        tune\n");
    DBG_PRINT("        [freq] set frequency [kHz]\n");
    DBG_PRINT("        [mode] set receiving system. select below.\n");
    DBG_PRINT("               -----------------------------------\n");
    DBG_PRINT("               ATSC_8VSB - ATSC 8VSB\n");
    DBG_PRINT("               US_QAM    - US 64QAM & 256QAM\n");
    DBG_PRINT("               ISDBT(_6M)- ISDB-T(6M Bandwidth)\n");
    DBG_PRINT("               ISDBT_7M  - ISDB-T 7M Bandwidth \n");
    DBG_PRINT("               ISDBT_8M  - ISDB-T 8M Bandwidth \n");
    DBG_PRINT("               DVBT_6M   - DVB-T 6M Bandwidth\n");
    DBG_PRINT("               DVBT_7M   - DVB-T 7M Bandwidth\n");
    DBG_PRINT("               DVBT_8M   - DVB-T 8M Bandwidth\n");
    DBG_PRINT("               DVBT2_6M  - DVB-T2 7M Bandwidth\n");
    DBG_PRINT("               DVBT2_7M  - DVB-T2 7M Bandwidth\n");
    DBG_PRINT("               DVBT2_8M  - DVB-T2 8M Bandwidth\n");
    DBG_PRINT("               DTMB      - China Digital\n");
    DBG_PRINT("               A_MN      - Analog system M or N\n");
    DBG_PRINT("               A_BG      - Analog system B or G\n");
    DBG_PRINT("               A_DK      - Analog system D or K\n");
    DBG_PRINT("               A_I       - Analog system I\n");
    DBG_PRINT("               A_L_N     - Analog system L\n");
    DBG_PRINT("               A_L_D     - Analog system L' \n");
    DBG_PRINT("               DVBC(_8M) - DVB-C(8M Bandwidth)\n");
    DBG_PRINT("               DVBC      - DVB-C 6M Bandwidth\n");
    DBG_PRINT("               DVBC2_8M  - DVB-C2 8M Bandwidth\n");  
    DBG_PRINT("               -----------------------------------\n");
    DBG_PRINT("        [region] \n");
    DBG_PRINT("               -----------------------------------\n"); 
    DBG_PRINT("               KOREA     - for System M A2\n");
    DBG_PRINT("               -----------------------------------\n");
    DBG_PRINT("   Exp : tune 1st on 55250kHz analogue System M\n");
    DBG_PRINT("          ./<name> 1st tune 55250 A_MN\n");    
    DBG_PRINT("   Exp : tune 2nd on 666000kHz DVB-T(8M)\n");
    DBG_PRINT("          ./<name> 2nd tune 666000 DVBT_8M \n");    
    DBG_PRINT("sleep\n");
    DBG_PRINT("        sleep\n");
    DBG_PRINT("shift [freq] [mode] [region(option)]\n");
    DBG_PRINT("        shift RF frequency without calibration\n");
    DBG_PRINT("        [freq] set frequency [kHz]\n");
    DBG_PRINT("        [mode] set receiving system.\n");
    DBG_PRINT("        [region] set country special information (Option).\n");
    DBG_PRINT("rssi\n");
    DBG_PRINT("        Get RSSI[dBm]\n");
    DBG_PRINT("\n");  
    DBG_PRINT("------------------------------ \n");
    DBG_PRINT("SUT-Rx23x Sample Code\n");
    DBG_PRINT(" (C) Sony corporation\n ");
    DBG_PRINT("     all right reserved.\n\n");

    return 0;
}
#endif
#if 0
/******************************************************************************
 * cmd_error
 *-----------------------------------------------------------------------------
 * show help
 *****************************************************************************/
static int cmd_error(int argc, char **argv)
{
    DBG_PRINT("Command Error\n");
    cmd_help(argc, argv);

    return -1;
}
#endif
/******************************************************************************
 * Register Setting (raleted A2E Application Note basically.)
 *****************************************************************************/

//static void x_dump_reg(void);

/******************************************************************************
 * x_pon
 *-----------------------------------------------------------------------------
 * Input        : none
 * Output       : none
 * Return       : none
 *****************************************************************************/
static void x_pon(void)
{

    UINT8 t_addr;
    UINT8 t_data[16];
    UINT8 data_length;
    UINT8 val;

    DBG_PRINT("Enter x_pon()...");
  
    t_addr     = 0x96;
    t_data[0]  = 0xAA;
    t_data[1]  = 0xFC;
    t_data[2]  = 0x43;
    t_data[3]  = 0x7A;
    t_data[4]  = 0x01;
    data_length = 5;
    iic_write( tuner_block_id, t_addr , t_data, data_length );  
  
    t_addr     = 0x81;
    t_data[0]  = XTAL; // 0x81
    t_data[1]  = 0x84;
    t_data[2]  = 0xE4;
    t_data[3]  = 0x00;
    t_data[4]  = 0x00; // 0x85
    t_data[5]  = 0x00;
    t_data[6]  = 0xC4;
    t_data[7]  = 0x40;
    t_data[8]  = 0x10; // 0x89
    t_data[9]  = 0x00;
    t_data[10] = 0x45;
    t_data[11] = 0x75;
    t_data[12] = 0x07; // 0x8d
    t_data[13] = 0x1C;
    t_data[14] = 0x3F;
    t_data[15] = 0x02;
    data_length = 16;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	
	
    t_addr     = 0x91;	
    t_data[0]  = 0x30; // 0x91
    t_data[1]  = 0x20;
    t_data[2]  = 0x0A;
    t_data[3]  = 0x00;
    data_length = 4;
    iic_write( tuner_block_id, t_addr , t_data, data_length );
    
	iic_write_val( tuner_block_id, 0x9B, 0x00 );

    waitms(10);   
   
    t_addr    = 0x17;
    t_data[0] = 0x8D;
    t_data[1] = 0x06;
    data_length = 2;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	
    waitms(1);  
    iic_read_val ( tuner_block_id, 0x19, &val );	
    iic_write_val( tuner_block_id, 0x95, (val & 0xF0) >> 4 );	
	   
    t_addr    = 0x17;
    t_data[0] = 0x8C;
    t_data[1] = 0x06;
    data_length = 2;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	
    waitms(1);  
    iic_read_val ( tuner_block_id, 0x19, &val );
	if((val & 0x08) >> 3 == 0){	
        iic_write_val( tuner_block_id, 0x83, 0xE4 );
	}else{
        iic_write_val( tuner_block_id, 0x83, 0x10 );
	}
	   
    iic_write_val( tuner_block_id, 0x67, 0x00 );
    iic_write_val( tuner_block_id, 0x74, 0x12 );
    t_addr    = 0x5E;
    t_data[0] = 0x15;
    t_data[1] = 0x00;
    t_data[2] = 0x00;
    data_length = 3;
    iic_write( tuner_block_id, t_addr , t_data, data_length );
    iic_write_val( tuner_block_id, 0x88, 0x00 );    
    iic_write_val( tuner_block_id, 0x87, 0xC0 ); 
  
    iic_write_val( tuner_block_id, 0x80, 0x01 );   
    
    DBG_PRINT(" Done. \n");
    
    return;
}


/******************************************************************************
 * x_tune
 *-----------------------------------------------------------------------------
 * Input        : TuningParam* pParam
 * Output       : none
 * Return       : none
 * Description  : based on A3 Application Note x_tune()
 *****************************************************************************/
static void x_tune(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal)
{
    UINT8 t_addr;
    UINT8 t_data[8];
    UINT8 data_length;
    UINT8 option = 0x00;
    UINT8 *param;
    UINT8 reg;

    DBG_PRINT("Enter x_tune()... ");
    
    iic_read_val( tuner_block_id, 0x83, &reg );	
    param = tuner_init_setparam( frequency, mode, cal, reg );	

    if((mode >= SONY_ASCOT3_ATV_MIN) && (mode <= SONY_ASCOT3_ATV_MAX)) option += 0x80;
    if( mode == SONY_ASCOT3_ATV_L_DASH ) option += 0x40;
    if((mode >= SONY_ASCOT3_DTV_MIN) && (mode <= SONY_ASCOT3_DTV_MAX)){
         frequency = (( frequency + 25 / 2 ) / 25 ) * 25;
    }

    if(cal){
        t_addr     = 0x74;
        t_data[0]  = 0x12;     // 0x74
        t_data[1]  = param[0];
        t_data[2]  = param[1];
        t_data[3]  = param[2];
        t_data[4]  = param[3]; // 0x78
        t_data[5]  = tuner_setModuleOffset(frequency, mode, reg); // 0x79
        data_length = 6;
        iic_write( tuner_block_id, t_addr , t_data, data_length );
    }

    iic_write_val( tuner_block_id, 0x8E, param[25] ); 

    t_addr     = 0x91;
    t_data[0]  = param[23];
    t_data[1]  = param[24];
    data_length = 2;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	
  
    t_addr     = 0x9C;
    t_data[0]  = param[4];
    t_data[1]  = param[5];
    data_length = 2;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	

    t_addr     = 0x87;
    t_data[0]  = 0xC4; // 0x87
    t_data[1]  = 0x40;
    data_length = 2;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	
 
    t_addr     = 0x5E;
    t_data[0]  = 0xEE;      // 0x5e
    t_data[1]  = 0x02;
    t_data[2]  = 0x1E;
    data_length = 3;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	
 
    t_addr     = 0x61;
    t_data[0]  = param[6];
    t_data[1]  = param[7];  // 0x62
    t_data[2]  = param[8];
    t_data[3]  = param[9];
    t_data[4]  = param[10];
    t_data[5]  = param[11];  // 0x66
	t_data[6]  = param[12];
    t_data[7]  = param[13];  // 0x68
    data_length = 8;
    iic_write( tuner_block_id, t_addr , t_data, data_length );
	
    iic_write_val( tuner_block_id, 0x69, param[22] ); 	
	
    t_addr     = 0x6A;	
    t_data[0]  = param[14];  // 0x6a
    t_data[1]  = param[15];
    t_data[2]  = param[16];
    t_data[3]  = param[17];
    t_data[4]  = param[18];  // 0x6e
    t_data[5]  = param[19];
    data_length = 6;
    iic_write( tuner_block_id, t_addr , t_data, data_length );
	
    t_addr     = 0x70;		
    t_data[0]  = ((frequency & 0x0000ff));
    t_data[1]  = ((frequency & 0x00ff00) >>  8);
    t_data[2]  = ((frequency & 0x0f0000) >> 16) + option;
    t_data[3]  = param[20];
    t_data[4]  = param[21];
    data_length = 5;
    iic_write( tuner_block_id, t_addr , t_data, data_length );	

    DBG_PRINT(" Done. \n");

    // x_dump_reg();

    return;
}

/******************************************************************************
 * x_tune_end
 *-----------------------------------------------------------------------------
 * Input        : none
 * Output       : none
 * Return       : none
 * Description  : A3 Application Note x_tune_end(), sequence number 8-10.
 *****************************************************************************/

static void x_tune_end(void)
{

    DBG_PRINT("Enter x_tune_end()... ");
	
    iic_write_val( tuner_block_id, 0x88, 0x00 );
    iic_write_val( tuner_block_id, 0x87, 0xC0 );

    DBG_PRINT(" Done. \n");

    return;
}

/******************************************************************************
 * x_read_ss()
 *-----------------------------------------------------------------------------
 * Input        : none
 * Output       : none
 * Return       : none
 *****************************************************************************/
static void x_read_ss(UINT16* val)
{
    UINT8 t_addr;
    UINT8 t_data[2];
    UINT8 r_data[2];
    UINT8 data_length;
	UINT16 reg;

    DBG_PRINT("Enter x_read_ss()...");

    t_addr    = 0x87;
    t_data[0] = 0xC4;
    t_data[1] = 0x40;
    data_length = 2;
    iic_write( tuner_block_id, t_addr, t_data, data_length );

    iic_write_val( tuner_block_id, 0x73, 0x30 );
    waitms(5); 
    iic_read ( tuner_block_id, 0x7A, r_data, 2 );

    iic_write_val( tuner_block_id, 0x88, 0x00 );
    iic_write_val( tuner_block_id, 0x87, 0xc0 );
  
    reg = (((UINT16)(r_data[1] & 0xff) << 8) + (UINT16)(r_data[0] & 0xe0)) >> 5;
	*val = reg;

    DBG_PRINT("x=0x%x, y=0x%x, reg=%d\n",r_data[1],r_data[0],reg);

    DBG_PRINT(" Done. \n");

    return;
}

#if 0
static void x_dump_reg(void)
{
    UINT8 r_data = 0;
    UINT8 x = 0, y = 0;

    printf("dump register...Beg\n");
    
    for (y = 0;y<=0xf;y++)
    {
        x = 0;
        printf("%X\t:\t",y<<4);
        for (x = 0;x<=0xf;x++)     
        {
            iic_read ( tuner_block_id, (y<<4)|x, &r_data, 1 );
            printf("%X\t",r_data);
        }
        printf("\n");
    }
    printf("dump register...End\n");    
    return;
}
#endif

/******************************************************************************
 * x_fin()
 *-----------------------------------------------------------------------------
 * Input        : none
 * Output       : none
 * Return       : none
 *****************************************************************************/
static void x_fin(void)
{
    UINT8 t_addr;
    UINT8 t_data[3];
    UINT8 data_length;

    DBG_PRINT("Enter x_fin()...");

    iic_write_val( tuner_block_id, 0x67, 0x00 );
    iic_write_val( tuner_block_id, 0x74, 0x12 );
    t_addr    = 0x5E;
    t_data[0] = 0x15;
    t_data[1] = 0x00;
    t_data[2] = 0x00;
    data_length = 3;
    iic_write( tuner_block_id, t_addr , t_data, data_length );
    iic_write_val( tuner_block_id, 0x88, 0x00 );    
    iic_write_val( tuner_block_id, 0x87, 0xC0 ); 
	
    DBG_PRINT(" Done. \n");

    return;
}
#if 0
/******************************************************************************
 * tuner_gpio
 *-----------------------------------------------------------------------------
 * Input        : IFOUT_AGC_PORT port
 * Output       : none
 * Return       : none
 * Description  : control GPIO.
 *****************************************************************************/
static void tuner_gpio(UINT8 port, UINT8 val)
{

    UINT8 reg;
	
    DBG_PRINT("Enter tuner_gpio()...");

    if(port == 0){
        reg = 0x85;
    }else if(port == 1){
        reg = 0x86;
    }
    
    iic_write_val( tuner_block_id, reg, val );

    DBG_PRINT(" Done. \n");

    return;
}
#endif
/******************************************************************************
 * tuner_init_setparam
 *-----------------------------------------------------------------------------
 * Input        : RECEIVE_MODE m_mode
 * Output       : none
 * Return       : UINT8 *param
 * Description  : select RF Data
 *****************************************************************************/
static UINT8* tuner_init_setparam(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal, UINT8 reg)
{
    static UINT8 buf[26];
    sony_ascot3_adjust_param_t *p;
    UINT8 i;
    UINT8 extctrl;
    UINT8 tmp;

    p = &param_table[mode];

    if( reg == 0xE4 ){
        extctrl = tuner_setextctrl(frequency, mode);
	}else{
		extctrl = 0x00;
	}

	if((mode >= SONY_ASCOT3_ATV_MIN) && (mode <= SONY_ASCOT3_ATV_MAX)){
		buf[0]  = 0xD9;
		buf[1]  = 0x0F;
		buf[2]  = 0x25;
		buf[3]  = 0x87;		
		buf[4]  = 0x00;
		buf[7]  = 0x20;
		buf[8]  = 0x40;
		buf[9]  = 0x78;
		buf[10] = 0x08;
		buf[11] = 0x08;
	}else if( mode == SONY_ASCOT3_DTV_DVBC_6  || mode == SONY_ASCOT3_DTV_DVBC_8 ) {
		buf[0]  = 0xD9;
		buf[1]  = 0x0F;
		buf[2]  = 0x25;
		buf[3]  = 0x87;	
		buf[4]  = 0x00;
		buf[7]  = 0x02;
		buf[8]  = 0x50;
		buf[9]  = 0x78;
		buf[10] = 0x08;
		buf[11] = 0x30;
	}else if( mode == SONY_ASCOT3_DTV_DVBC2_6 || mode == SONY_ASCOT3_DTV_DVBC2_8 || mode == SONY_ASCOT3_DTV_DTMB ) {
		buf[0]  = 0x99;
		buf[1]  = 0x00;
		buf[2]  = 0x24;
		buf[3]  = 0x87;	
		buf[4]  = 0x00;
		buf[7]  = 0x02;
		buf[8]  = 0xAF;
		buf[9]  = 0x78;
		buf[10] = 0x08;
		buf[11] = 0x30;
    }else if( mode == SONY_ASCOT3_DTV_8VSB || mode == SONY_ASCOT3_DTV_QAM) {
		buf[0]  = 0x99;
		buf[1]  = 0x00;
		buf[2]  = 0x24;
		buf[3]  = 0x07;
		buf[4]  = 0x00;
		buf[7]  = 0x02;	
		buf[8]  = 0xAF;
		buf[9]  = 0x78;
		buf[10] = 0x08;
		buf[11] = 0x30;
    }else {
		buf[0]  = 0x99;
		buf[1]  = 0x00;
		buf[2]  = 0x24;
		buf[3]  = 0x87;
		buf[4]  = 0x90;
		buf[7]  = 0x02;
		buf[8]  = 0x38;
		buf[9]  = 0x1E;
		buf[10] = 0x02;
		buf[11] = 0x24;
	}

    buf[5]  = p->IS_LOWERLOCAL;		 
	buf[12] = extctrl;
    buf[13] = p->OUTLMT;
    buf[14] = 0x00;	

    if( mode == SONY_ASCOT3_DTV_8VSB || mode == SONY_ASCOT3_DTV_QAM){
		tmp     = 0x00;
		buf[25] = 0x00;	
	} else {
		tmp     = 0x20;
		buf[25] = 0x1C;			
	}
	
    if( frequency <= 172000 ){
        buf[15] = p->RFOVLD_DET_LV1_VL;	
        buf[16] = tmp + p->IFOVLD_DET_LV_VL;
	}else if ( frequency <= 464000 ){
        buf[15] = p->RFOVLD_DET_LV1_VH;	
        buf[16] = tmp + p->IFOVLD_DET_LV_VH;
	}else{
        buf[15] = p->RFOVLD_DET_LV1_U;	
        buf[16] = tmp + p->IFOVLD_DET_LV_U;		
	}

    if( reg == 0xE4 && p->IS_LOWERLOCAL == 0x01 ){
        buf[17] = 0x10 + p->BW;
	}else{
		buf[17] = ((p->IF_BPF_F0) << 4) + p->BW;
	}

    buf[18] = p->FIF_OFFSET;		
    buf[19] = p->BW_OFFSET;			
    buf[21] = ((p->AGC_SEL) << 4) + p->IF_OUT_SEL;
	if(p->RF_GAIN == AUTO) buf[22] = 0x80                + p->IF_BPF_GC;
    else                   buf[22] = ((p->RF_GAIN) << 4) + p->IF_BPF_GC;

	if(cal == 1){
		buf[6]  = 0x67;
		buf[20] = 0xFF;
	}else{
		buf[6]  = 0x47;
		buf[20] = 0x8F;
	}

	if( mode == SONY_ASCOT3_DTV_DVBC_6  || mode == SONY_ASCOT3_DTV_DVBC_8 ) {
		buf[23] = 0x36;
		buf[24] = 0x26;
	}else{
		buf[23] = 0x30;
		buf[24] = 0x20;
	}

    printf("\n------reg  setting------\n");
    printf("    ");	
	for(i= 0;i<= 3;i++) printf("0x%x ",buf[i]); printf("\n    ");
	for(i=25;i<=25;i++) printf("0x%x ",buf[i]); printf("\n    ");	
	for(i=23;i<=24;i++) printf("0x%x ",buf[i]); printf("\n    ");
	for(i= 4;i<= 5;i++) printf("0x%x ",buf[i]); printf("\n    ");
	for(i= 6;i<=13;i++) printf("0x%x ",buf[i]); printf("\n    ");
	for(i=22;i<=22;i++) printf("0x%x ",buf[i]); printf("\n    ");
	for(i=14;i<=19;i++) printf("0x%x ",buf[i]); printf("\n    ");
	for(i=20;i<=21;i++) printf("0x%x ",buf[i]); printf("\n");  
    printf("\n------------------------\n");

    return (UINT8*) buf;

}

static UINT8 tuner_setextctrl(UINT32 frequency, RECEIVE_MODE mode){
	
//#define GA_MODEL 1	// <- Please change active if you use GA model Tuner. 
	
	UINT8 val;
	
	switch(mode){
		case SONY_ASCOT3_DTV_8VSB:
        case SONY_ASCOT3_DTV_QAM:
        case SONY_ASCOT3_DTV_ISDBT_6:
        case SONY_ASCOT3_DTV_DVBT_6:
        case SONY_ASCOT3_DTV_DVBT2_6:
#ifndef GA_MODEL		
        case SONY_ASCOT3_ATV_MN_SAP:
#endif
        case SONY_ASCOT3_DTV_DVBC_6:
        case SONY_ASCOT3_DTV_DVBC2_6:
				
		    if(frequency >= 464000) {
		        val = 0x01;
		    } else {
		        val = 0x00;
		    }
	    	break;

        case SONY_ASCOT3_DTV_DVBT_7:
        case SONY_ASCOT3_DTV_DVBT_8:
        case SONY_ASCOT3_DTV_DVBT2_7:
        case SONY_ASCOT3_DTV_DVBT2_8:
        case SONY_ASCOT3_DTV_DTMB:
#ifdef GA_MODEL
        case SONY_ASCOT3_ATV_MN_SAP:
#endif
        case SONY_ASCOT3_ATV_BG:
        case SONY_ASCOT3_ATV_I:
        case SONY_ASCOT3_ATV_DK:
        case SONY_ASCOT3_ATV_L:
        case SONY_ASCOT3_ATV_L_DASH:
        case SONY_ASCOT3_DTV_DVBC_8:
        case SONY_ASCOT3_DTV_DVBC2_8:
		default:
			if((mode >= SONY_ASCOT3_ATV_MIN) && (mode <= SONY_ASCOT3_ATV_MAX)) {
			    if(frequency >= 464000) {
		            val = 0x00;
			    } else {
	    	        val = 0x01;
			    }
			}else{
		        val = 0x01;
			}
            break;
	}
	return val;
}

static UINT8 tuner_setModuleOffset(UINT32 freq, RECEIVE_MODE mode, UINT8 reg){

    UINT8 i;
    INT16 offset_x100;
	UINT8 offsetreg;
    sony_ascot3_rx23x_ModuleParam* table;

    if(reg == 0xE4){
        /* Please adjust table to your environment & used module. */
        table = (sony_ascot3_rx23x_ModuleParam*) RE231_RSSI_TABLE;
	
        i = 0;
        while( freq < table[i].freq ){
    	    i++;
        }
	
    	offset_x100 = demod_iftgt[mode] + table[i].param;

        DBG_PRINT("if=%d,table=%d,offset=%d\n",demod_iftgt[mode],table[i].param,offset_x100);

        if(offset_x100 > 1588)       offset_x100 =  1588;
        else if(offset_x100 < -1600) offset_x100 = -1600;
	
        if(offset_x100 > 0) offsetreg = (UINT8)((offset_x100 * 10 + 125/2) / 125);
        else                offsetreg = (UINT8)((offset_x100 * 10 - 125/2) / 125);
	} else {
		offsetreg = 0;
	}

	return offsetreg;

}

/******************************************************************************
 * iic_write_val
 *-----------------------------------------------------------------------------
 * INT16    id      : Block ID (Slave Addr information etc) 
 * UINT8    subadr  : sub address
 * UINT8    val     : data value
 * 
 * retrun           : write data to i2c access (use value as Input). 
 *****************************************************************************/
static INT16 iic_write_val(INT16 id, UINT8 subadr, UINT8 val){
    return iic_write(id, subadr, &val, 1);
    // return 0;
}


/******************************************************************************
 * iic_write
 *-----------------------------------------------------------------------------
 * INT16    id      : Block ID 
 * UINT8    subadr  : sub address
 * UINT8*   data    : pointer to data buffer to send
 * UINT8    len     : data byte length to send
 * 
 * retrun           : write data to i2c access (use pointer as Input). 
 *****************************************************************************/
static INT16 iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len){

    INT16 bRet = 1;

    switch( (BLOCKID)id ) {
        
        case TERR_1ST_TUNER:
            bRet &= write_tuner( SLAVE_1ST_ADDRESS, subadr, data, len );
            break;
        default :
            break;
    }
    return bRet;
}

/******************************************************************************
 * iic_read_val
 *-----------------------------------------------------------------------------
 * INT16    id      : Block ID (Slave Addr information etc) 
 * UINT8    subadr  : sub address
 * UINT8    val     : data value
 * 
 * retrun           : write data to i2c access (use value as Input). 
 *****************************************************************************/
static INT16 iic_read_val(INT16 id, UINT8 subadr, UINT8* val){
    return iic_read(id, subadr, val, 1);
    // return 0;
}

/******************************************************************************
 * iic_read
 *-----------------------------------------------------------------------------
 * INT16    id      : Block ID 
 * UINT8    subadr  : sub address
 * UINT8*   data    : pointer to data buffer to send
 * UINT8    len     : data byte length to send
 * 
 * retrun           : write data to i2c access (use pointer as Input). 
 *****************************************************************************/
static INT16 iic_read(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len){

    INT16 bRet = 1;
    switch( (BLOCKID)id ) {
        
        case TERR_1ST_TUNER:
            bRet &= read_tuner( SLAVE_1ST_ADDRESS, subadr, data, len );
            break;
        default :
            break;
    }
    return bRet;
}


/******************************************************************************
 * write_tuner
 *****************************************************************************/
static INT16 write_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
) {

    UINT8 bRet = 1;
    if (sut_re23x_dependency_func_obj.i2c_write == NULL)
    {
        printf("[Error]%s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);
        bRet = 0;
    }
    else
        bRet &= sut_re23x_dependency_func_obj.i2c_write(IIC_CH_SUT, slv, &subadr, 1, data, len);

    if(bRet == 0) 
        printf("[Error]i2c write error, %s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);

    return (INT16)bRet;
}

/******************************************************************************
 * write_tuner
 *-----------------------------------------------------------------------------
 * unsigned char    slv     : Tuner Slave Addressr (0xC0)
 * unsigned char    subadr  : Sub Address
 * unsigned char*   data    : pointer to data buffer
 * unsigned char    len     : length
 * 
 * retrun                   : 
 *****************************************************************************/

static INT16 read_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
) {

    UINT8 bRet = 1;
    if (sut_re23x_dependency_func_obj.i2c_read == NULL)
    {
        printf("[Error]%s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);
        bRet = 0;
    }
    else
        bRet &= sut_re23x_dependency_func_obj.i2c_read(IIC_CH_SUT, slv, &subadr, 1, data, len);

    if(bRet == 0) 
        printf("[Error]i2c read error, %s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);

    return (INT16)bRet;
}

/******************************************************************************
 * waitms
 *-----------------------------------------------------------------------------
 * Input : UINT32 ms
 * Output: none
 * Return: void
 *****************************************************************************/
static void waitms(UINT32 ms) {

    sut_re23x_dependency_func_obj.ms_delay(ms);
    return;
}


UINT8 mdev_TunerSetPllData_SUT(MS_U32 u32FreqInKHz, IF_FREQ eIF_Freq)
{
    // int i = 0;
    UINT32 frequency = 0;
    RECEIVE_MODE mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;

    DBG_PRINT("Enter cmd_tune\n");

    // if(argc > 1) frequency = atoi(argv[1]);
    // else frequency = 57000;    /* Default: 57000kHz */ 

    if (u32FreqInKHz < 45250 || u32FreqInKHz > 883250)
    {
         printf("ERROR : frequency is Illegal, 45250KHz ~ 883250KHz, freq=%ld\n",u32FreqInKHz);
         return 0;
    }

    frequency = u32FreqInKHz;

//    mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;

    switch(eIF_Freq)
    {
        case IF_FREQ_B:
        case IF_FREQ_G:
            mode = SONY_ASCOT3_ATV_BG;
            SUT_DEBUG_PRINT(printf("mode -> BG\n"));
            break;
        case IF_FREQ_I:
            mode = SONY_ASCOT3_ATV_I;
            SUT_DEBUG_PRINT(printf("mode -> I\n"));
            break;
        case IF_FREQ_DK:
            mode = SONY_ASCOT3_ATV_DK;
            SUT_DEBUG_PRINT(printf("mode -> DK\n"));
            break;
        case IF_FREQ_L:
            mode = SONY_ASCOT3_ATV_L;
            SUT_DEBUG_PRINT(printf("mode -> L\n"));
            break;
        case IF_FREQ_L_PRIME:
            mode = SONY_ASCOT3_ATV_L_DASH;
            SUT_DEBUG_PRINT(printf("mode -> LP\n"));
            break;
        case IF_FREQ_MN:
            mode = SONY_ASCOT3_ATV_MN_SAP;
            SUT_DEBUG_PRINT(printf("mode -> MN\n"));
            break;
        default:
            mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;
            printf("ERROR : selected system is Illegal.\n");
            return 0;
    }

    if(mode == SONY_ASCOT3_TV_SYSTEM_UNKNOWN){
        printf("ERROR : selected system is Illegal. mode=%d\n",eIF_Freq);
        return 0;
    }     

#if 0
    x_init(frequency, mode);

    if((mode >= SONY_ASCOT3_ATV_MIN) && (mode <= SONY_ASCOT3_ATV_MAX)) {
        tuner_setlna(0);
    } else if (mode == SONY_ASCOT3_DTV_DVBC) {
        tuner_setlna(0);
    } else {
        tuner_setlna(1);
    }

    if(frequency >= 470000) {
        tuner_extctrl(S_ENABLE);
    } else {
        tuner_extctrl(S_DISABLE);
    }
#endif

    x_tune(frequency, mode, 1);
    waitms(50);
    x_tune_end();

//    g_status.IFAGC = 0;
//    g_status.RFAGC = 0;

    // 1:true
    return 1;
}

UINT8 mdev_Tunerfunc_SUT(const pS_SUT_RE23x_dependency_func pobj)
{
    UINT8 bRet = 1;
 
    sut_re23x_dependency_func_obj.i2c_read = pobj->i2c_read;
    sut_re23x_dependency_func_obj.i2c_write = pobj->i2c_write;
    sut_re23x_dependency_func_obj.ms_delay = pobj->ms_delay;
    sut_re23x_dependency_func_obj.hw_rst_control = pobj->hw_rst_control;
    
    return bRet;
}

UINT8 mdev_TunerInit_SUT(void)
{

    UINT8 bRet = 1;

    /* tuner reset  */ 
    if (sut_re23x_dependency_func_obj.ms_delay == NULL)
    {
        printf("[Error]%s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);
        bRet = 0;
        return bRet;
    }
    else if (sut_re23x_dependency_func_obj.i2c_read == NULL)
    {
        printf("[Error]%s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);
        bRet = 0;
        return bRet;        
    }
    else if (sut_re23x_dependency_func_obj.i2c_write == NULL)
    {
        printf("[Error]%s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);
        bRet = 0;
        return bRet;        
    }
    
    /* tuner i2c address  */
    tuner_block_id = TERR_1ST_TUNER;
    
    param_table = (sony_ascot3_adjust_param_t*)g_param_table_Rx23x;
    
    /* tuner init  */
    // bRet &= terr_tuner_init();
    if (cmd_init() == 0)
        bRet &= 1;
    else 
        bRet &= 0;

    return bRet;
}

UINT8 mdev_TunerDigitalSetFreq_SUT ( MS_U32 FreqKHz, RF_CHANNEL_BANDWIDTH eBandWidth,EN_TUNER_MODE eNetworktype)
{
    // int i = 0;
    UINT32 frequency = 0;
    RECEIVE_MODE mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;

    DBG_PRINT("Enter cmd_tune\n");

    // if(argc > 1) frequency = atoi(argv[1]);
    // else frequency = 57000;    /* Default: 57000kHz */ 

    if (FreqKHz < 47000 || FreqKHz > 866000)
    {
         printf("ERROR : frequency is Illegal, 47000KHz ~ 866000KHz, freq=%ld\n",FreqKHz);
         return 0;
    }

    frequency = FreqKHz;

//    mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;

    switch(eNetworktype)
    {
        case E_TUNER_DTV_DVB_T_MODE:
            {
                switch(eBandWidth)
                {
                    case E_RF_CH_BAND_6MHz:
                        mode = SONY_ASCOT3_DTV_DVBT_6;
                        break;
                    case E_RF_CH_BAND_7MHz:
                        mode = SONY_ASCOT3_DTV_DVBT_7;                        
                        break;
                    case E_RF_CH_BAND_8MHz:
                        mode = SONY_ASCOT3_DTV_DVBT_8;                        
                        break;
                    default:
                        mode = SONY_ASCOT3_DTV_DVBT_8;                        
                        break;
                }
            }
            break;
        case E_TUNER_DTV_DVB_C_MODE:
            mode = SONY_ASCOT3_DTV_DVBC_8;
            break;
        case E_TUNER_DTV_DTMB_MODE:
            mode = SONY_ASCOT3_DTV_DTMB;
            break;
        case E_TUNER_DTV_ATSC_MODE:
            mode = SONY_ASCOT3_DTV_8VSB;
            break;
        case E_TUNER_DTV_ISDB_MODE:
            {
                switch(eBandWidth)
                {
                    case E_RF_CH_BAND_6MHz:
                        mode = SONY_ASCOT3_DTV_ISDBT_6;
                        break;
                    case E_RF_CH_BAND_7MHz:
                        mode = SONY_ASCOT3_DTV_ISDBT_7;                        
                        break;
                    case E_RF_CH_BAND_8MHz:
                        mode = SONY_ASCOT3_DTV_ISDBT_8;                        
                        break;
                    default:
                        mode = SONY_ASCOT3_DTV_ISDBT_6;                        
                        break;
                }
            }            
            break;
        case E_TUNER_DTV_DVB_T2_MODE:
            {
                switch(eBandWidth)
                {
                    case E_RF_CH_BAND_6MHz:
                        mode = SONY_ASCOT3_DTV_DVBT2_6;
                        break;
                    case E_RF_CH_BAND_7MHz:
                        mode = SONY_ASCOT3_DTV_DVBT2_7;                        
                        break;
                    case E_RF_CH_BAND_8MHz:
                        mode = SONY_ASCOT3_DTV_DVBT2_8;                        
                        break;
                    default:
                        mode = SONY_ASCOT3_DTV_DVBT2_8;                        
                        break;
                }
            }            
            break;            
        case E_TUNER_ATV_PAL_MODE:
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
        case E_TUNER_ATV_NTSC_MODE:
        case E_TUNER_DTV_DVB_S_MODE:            
        default:
            mode = SONY_ASCOT3_TV_SYSTEM_UNKNOWN;
            break;         
    }

    if(mode == SONY_ASCOT3_TV_SYSTEM_UNKNOWN){
        printf("ERROR : selected system is Illegal.\n");
        return 0;
    }     

#if 0
    x_init(frequency, mode);

    if((mode >= SONY_ASCOT3_ATV_MIN) && (mode <= SONY_ASCOT3_ATV_MAX)) {
        tuner_setlna(0);
    } else if (mode == SONY_ASCOT3_DTV_DVBC) {
        tuner_setlna(0);
    } else {
        tuner_setlna(1);
    }

    if(frequency >= 470000) {
        tuner_extctrl(S_ENABLE);
    } else {
        tuner_extctrl(S_DISABLE);
    }
#endif
    x_tune(frequency, mode, 1);
    waitms(50);
    x_tune_end();

//    g_status.IFAGC = 0;
//    g_status.RFAGC = 0;

    // 1:true
    return 1;

}

UINT8 mdev_Tuner_read_rssi(float* float_rssi)    
{
    if (cmd_getrssi(float_rssi) == 0)
        return 1;
    else 
        return 0;
}

void mdev_Tuner_sleep_mode(void)
{
   x_fin();
}

// Rx232 series only
// return:
// 0: fail
// 1: ok
UINT8 mdev_Tuner_LNA_enable(UINT8 enable)
{
    UINT8 reg = 0;
    UINT8 ret = 1;
    ret &= iic_read_val( tuner_block_id, 0x85, &reg );
    if ((reg == 0x00) && (enable == 1))
    {
      ret &= iic_write_val( tuner_block_id, 0x85, 1);
    }
    else if ( (reg == 0x01) && (enable == 0))
    {
      ret &= iic_write_val( tuner_block_id, 0x85, 0);
    }
    if (ret == 0) printf("%s, %d, mdev_Tuner_LNA_enable fail,reg=0x%x\n",__FILE__,__LINE__,reg );

    return ret;
}

/******************************************************************************
 * History
 *
 * 2013-03-05 v0.10  initial release
 * 2013-03-14 v0.20  register update
 *                   fixed minor bugfix
 * 2013-03-14 v0.21  Add 0x69->0x89 at x_tune()
 * 2013-04-12 v0.30  register update
 * 2013-07-01 v0.40  deleted SUT-PE23x
 *                   updated RSSI Table (chenged incluede file)
 *                   modified structure [sony_ascot3_adjust_param_t]
 *                     separated several params [RFOVLD_DET_LV1->RFOVLD_DET_LV1_VL/VH/U] [IFOVLD_DET_LV->IFOVLD_DET_LV_VL/VH/U],
 *                   added DVB-C 6MHz Bandwidth setting
 *                   modified structure [g_param_table_Rx23x]
 *                     modified parameters RFOVLD_DET_LV1_XX, IFOVLD_DET_LV_XX
 *                   modified tuner_calcRSSI()
 *                     change RSSI calicuration method
 *                   fixed typo in cmd_help() 
 *                   changed x_pon()
 *                     deleted Addr 0x30
 *                     changed Addr 0x83
 *                     changed Addr 0x89
 *                     changed Addr 0x90
 *                     added   Addr 0x91-0x94
 *                     added   Addr 0x80
 *                   changed x_tune()
 *                     fixed sizeof t_data (12->8)
 *                     moved   Addr 0x69
 *                     added   Addr 0x91-0x92
 *                   changed x_tune_end()
 *                     deleted Addr 0x69 
 *                   changed tuner_init_setparam()
 *                     changed buf[0]  (ana/DVB-C), (TerrDig/DVB-C2) 
 *                     changed buf[0]  (ana/DVB-C) 
 *                     changed buf[3]  (all system)
 *                     changed buf[7]  (DVB-C)
 *                     changed buf[8]  (DVB-C/DVB-C2)
 *                     changed buf[11] (DVB-C)
 *                     changed buf[15][16] (all system) 
 *                     changed [reg] value 
 *                     added   buf[22] 
 *                     added   buf[23][24]
 *                     changed function to print register setting 
 *                   changed tuner_setextctrl()
 *                     added DVB-C 6MHz Bandwidth setting
 *                   changed tuner_setModuleOffset()
 *                     changed [reg] value 
 * 2013-10-18 v0.60  modified structure [g_param_table_Rx23x]
 *                     modified parameters IFOVLD_DET_LV1_XX (ana) 
 *                     modified parameters RFOVLD_DET_LV_XX  (TerrDig)
 *                   modified tuner_calcRSSI()
 *                     change RSSI calicuration method (ATSC/QAM)
 *                   changed x_pon()
 *                     changed Addr 0x8B
 *                   changed x_tune()
 *                     added   Addr 0x8E
 *                   changed tuner_init_setparam()
 *                     changed buf[7][8]  (ana)
 *                     changed buf[3][4][8]-[11]  (ATSC/QAM)
 *                     changed buf[4][8]-[11]  (DTMB)
 *                     added   buf[25] 
 *                     changed buf[16]  (all system)
 *                   modified tuner_setextctrl()
 *                     changed frequency threshold 470MHz -> 464MHz 
 ******************************************************************************/
