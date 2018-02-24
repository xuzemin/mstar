/******************************************************************************
 *   $ Copyright $ Sony Corporation
 *-----------------------------------------------------------------------------
 *   File Name   : $File: sut_pex41_terr.c $
 *   Modified    : $Date: 2014/04/21 $ By $Author: $
 *   Revision    : $Revision: 1.0.0.0 $
 *   Description : SUT-PE241/541 Tuner Control Sample Code
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
#include "sut_pex41_rssi.h"

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

typedef struct sony_helene_adjust_param_t {
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
} sony_helene_adjust_param_t;

/*************************************************
 Block ID definition for I2C access
**************************************************/
typedef enum {
    TERR_1ST_TUNER,   /* Tag for 1st Tuner Block                      */
    TERR_2ND_TUNER    /* Tag for 2nd Tuner Block for dual tuner model */
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

typedef enum {
    SONY_ASCOT3_TV_SYSTEM_UNKNOWN,
    /* Analog */
    SONY_HELENE_ATV_MN_EIAJ,  /* System-M (Japan) */
    SONY_HELENE_ATV_MN_SAP,   /* System-M (US) */
    SONY_HELENE_ATV_MN_A2,    /* System-M (Korea) */
    SONY_HELENE_ATV_BG,       /* System-B/G */
    SONY_HELENE_ATV_I,        /* System-I */
    SONY_HELENE_ATV_DK,       /* System-D/K */
    SONY_HELENE_ATV_L,        /* System-L */
    SONY_HELENE_ATV_L_DASH,   /* System-L DASH */
    /* Digital */
    SONY_HELENE_DTV_8VSB,     /* ATSC 8VSB */
    SONY_HELENE_DTV_QAM,      /* US QAM */
    SONY_HELENE_DTV_ISDBT_6,  /* ISDB-T 6MHzBW */
    SONY_HELENE_DTV_ISDBT_7,  /* ISDB-T 7MHzBW */
    SONY_HELENE_DTV_ISDBT_8,  /* ISDB-T 8MHzBW */
    SONY_HELENE_DTV_DVBT_5,   /* DVB-T 5MHzBW */
    SONY_HELENE_DTV_DVBT_6,   /* DVB-T 6MHzBW */
    SONY_HELENE_DTV_DVBT_7,   /* DVB-T 7MHzBW */
    SONY_HELENE_DTV_DVBT_8,   /* DVB-T 8MHzBW */
    SONY_HELENE_DTV_DVBT2_1_7,/* DVB-T2 1.7MHzBW */
    SONY_HELENE_DTV_DVBT2_5,  /* DVB-T2 5MHzBW */
    SONY_HELENE_DTV_DVBT2_6,  /* DVB-T2 6MHzBW */
    SONY_HELENE_DTV_DVBT2_7,  /* DVB-T2 7MHzBW */
    SONY_HELENE_DTV_DVBT2_8,  /* DVB-T2 8MHzBW */
    SONY_HELENE_DTV_DVBC_6,   /* DVB-C 6MHzBW */
    SONY_HELENE_DTV_DVBC_8,   /* DVB-C 8MHzBW */
    SONY_HELENE_DTV_DVBC2_6,  /* DVB-C2 6MHzBW */
    SONY_HELENE_DTV_DVBC2_8,  /* DVB-C2 8MHzBW */
    SONY_HELENE_DTV_DTMB,     /* DTMB */
    
    SONY_HELENE_ATV_MIN = SONY_HELENE_ATV_MN_EIAJ,
    SONY_HELENE_ATV_MAX = SONY_HELENE_ATV_L_DASH,
    SONY_HELENE_DTV_MIN = SONY_HELENE_DTV_8VSB,
    SONY_HELENE_DTV_MAX = SONY_HELENE_DTV_DTMB,
    SONY_ASCOT3_TV_SYSTEM_NUM /* SONY_HELENE_DTV_DTMB + 1 */
} RECEIVE_MODE;

/*************************************************
 default slave address
**************************************************/
#define SLAVE_1ST_ADDRESS   0xC0
#define SLAVE_2ND_ADDRESS   0xC2

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

/* Optimized table for sony module */
static const sony_helene_adjust_param_t g_param_table_sony_module[SONY_ASCOT3_TV_SYSTEM_NUM] = {

    /*
    OUTLMT    IF_BPF_GC                                           BW              BW_OFFSET         IF_OUT_SEL
      |  RF_GAIN  |     RFOVLD_DET_LV1    IFOVLD_DET_LV  IF_BPF_F0 |   FIF_OFFSET     |        AGC_SEL |    IS_LOWERLOCAL
      |     |     |    (VL)  (VH)  (U)   (VL)  (VH)  (U)    |      |       |          |          |     |       |          */
    {0x00, AUTO, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(0),  OFFSET(0),  PORT2, PORT2, 0x00}, /**< SONY_ASCOT3_TV_SYSTEM_UNKNOWN */
    /* Analog */
    {0x00, AUTO, 0x05, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(0),  OFFSET(1),  PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_MN_EIAJ   (System-M (Japan)) */
    {0x00, AUTO, 0x05, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(0),  OFFSET(1),  PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_MN_SAP    (System-M (US)) */
    {0x00, AUTO, 0x05, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, BW_6,  OFFSET(3),  OFFSET(1),  PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_MN_A2     (System-M (Korea)) */
    {0x00, AUTO, 0x05, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, BW_7,  OFFSET(11), OFFSET(5),  PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_BG        (System-B/G) */
    {0x00, AUTO, 0x05, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, BW_8,  OFFSET(2),  OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_I         (System-I) */
    {0x00, AUTO, 0x05, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, BW_8,  OFFSET(2),  OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_DK        (System-D/K) */
    {0x00, AUTO, 0x03, 0x04, 0x0A, 0x04, 0x03, 0x03, 0x03, 0x00, BW_8,  OFFSET(2),  OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_L         (System-L) */
    {0x00, AUTO, 0x03, 0x04, 0x0A, 0x04, 0x03, 0x03, 0x03, 0x00, BW_8,  OFFSET(-1), OFFSET(4),  PORT2, PORT2, 0x00}, /**< SONY_HELENE_ATV_L_DASH    (System-L DASH) */
    /* Digital */
    {0x00, AUTO, 0x09, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, BW_6,  OFFSET(-6), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_8VSB      (ATSC 8VSB) */
    {0x00, AUTO, 0x09, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-6), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_QAM       (US QAM) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-9), OFFSET(-5), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_ISDBT_6   (ISDB-T 6MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_7,  OFFSET(-7), OFFSET(-6), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_ISDBT_7   (ISDB-T 7MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-5), OFFSET(-7), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_ISDBT_8   (ISDB-T 8MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT_5    (DVB-T 5MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT_6    (DVB-T 6MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_7,  OFFSET(-6), OFFSET(-5), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT_7    (DVB-T 7MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-4), OFFSET(-6), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT_8    (DVB-T 8MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_1_7,OFFSET(-10),OFFSET(-10),PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT2_1_7 (DVB-T2 1.7MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT2_5   (DVB-T2 5MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-8), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT2_6   (DVB-T2 6MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_7,  OFFSET(-6), OFFSET(-5), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT2_7   (DVB-T2 7MHzBW) */
    {0x00, AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-4), OFFSET(-6), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBT2_8   (DVB-T2 8MHzBW) */
    {0x00, AUTO, 0x05, 0x08, 0x08, 0x08, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-6), OFFSET(-4), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBC_6    (DVB-C 6MHzBW) */
    {0x00, AUTO, 0x05, 0x08, 0x08, 0x08, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-2), OFFSET(-3), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBC_8    (DVB-C 8MHzBW) */
    {0x00, AUTO, 0x03, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_6,  OFFSET(-6), OFFSET(-2), PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBC2_6   (DVB-C2 6MHzBW) */
    {0x00, AUTO, 0x03, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(-2), OFFSET(0),  PORT2, PORT2, 0x00}, /**< SONY_HELENE_DTV_DVBC2_8   (DVB-C2 8MHzBW) */
    {0x00, AUTO, 0x04, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00, BW_8,  OFFSET(2),  OFFSET(1),  PORT2, PORT2, 0x00}  /**< SONY_HELENE_DTV_DTMB      (DTMB) */

};

static sony_helene_adjust_param_t *param_table;

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

static INT16 Terr_iic_write_val(INT16 id, UINT8 subadr, UINT8 val);
static INT16 Terr_iic_read_val(INT16 id, UINT8 subadr, UINT8* val);
static INT16 Terr_iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len);
static INT16 Terr_iic_read(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len);

static INT16 Terr_write_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
);

static INT16 Terr_read_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
);


/*************************************************
 Wait
**************************************************/
static void Terr_waitms(UINT32 ms);

/*************************************************
 Tuning Sequece
**************************************************/
static void Terr_x_pon(void);                                                /* tuner: Initialize        */
static void Terr_x_tune(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal);     /* tuner: tune              */
static void Terr_x_tune_end(void);                                           /* tuner: tune (after wait) */
static void Terr_x_fin(void);                                                /* tuner: sleep             */
static void Terr_x_read_agc(UINT8* ifagcreg , UINT8* rfagcreg);

static void   Terr_tuner_gpio(UINT8 port, UINT8 val);
static int    Terr_tuner_count(void);
static UINT8* Terr_tuner_init_setparam(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal);
static UINT8  Terr_tuner_setextctrl(UINT32 frequency, RECEIVE_MODE mode);
static INT16  Terr_tuner_calcRSSI(UINT8 ifagcreg , UINT8 rfagcreg);
static UINT8  Terr_tuner_setModuleOffset(UINT32 freq, RECEIVE_MODE mode);


static void Terr_x_read_agc(UINT8* ifagcreg , UINT8* rfagcreg){
    
    UINT8 t_addr;
    UINT8 t_data[2];
    UINT8 data_length;
    UINT8 val;

    t_addr    = 0x87;
    t_data[0] = 0xC4;
    t_data[1] = 0x41;
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    
    
    t_addr    = 0x59;
    t_data[0] = 0x05;
    t_data[1] = 0x01;
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    Terr_iic_read_val ( tuner_block_id, 0x5B, &val );
    *ifagcreg = val;

    t_addr    = 0x59;
    t_data[0] = 0x03;
    t_data[1] = 0x01;
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    Terr_iic_read_val ( tuner_block_id, 0x5B, &val );    
    *rfagcreg = val;

    Terr_iic_write_val( tuner_block_id, 0x59, 0x04 );
    Terr_iic_write_val( tuner_block_id, 0x88, 0x00 );        
    Terr_iic_write_val( tuner_block_id, 0x87, 0xC0 );

    return;
    
}

static INT16 Terr_tuner_calcRSSI(UINT8 ifagcreg , UINT8 rfagcreg){
    
    INT32 ifgain, rfgain,moduleoffset;
    INT32 rssi_x100;
    INT16 if_bpf_gc_x100;
    INT32 rfgainmax_x100;
    INT32 agcreg_x140;
    
    UINT8 type,ofs,bpf,lna;

    static const INT16  BPFGAIN[] = {-6,-4,-2, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 20};

    Terr_iic_read_val ( tuner_block_id, 0x78, &type );
    Terr_iic_read_val ( tuner_block_id, 0x79, &ofs  );
    Terr_iic_read_val ( tuner_block_id, 0x69, &bpf  );
    Terr_iic_read_val ( TERR_1ST_TUNER, 0x85, &lna  );

    agcreg_x140 = ifagcreg * 140;    
    if_bpf_gc_x100 = BPFGAIN[ ( bpf & 0x0F ) ] * 100;
    
    if(agcreg_x140 > 9945 ){
        ifgain = 870 + if_bpf_gc_x100;
    }else{
        ifgain = 870 + if_bpf_gc_x100 + (769 * (9945 - agcreg_x140) + 1275) / 2550;     /* Round */
    }
    
    rfgainmax_x100 = 4150;
    
    if( (ifagcreg > rfagcreg) || (rfagcreg < 20) ) {
        agcreg_x140 = ifagcreg * 140;
    } else { 
        agcreg_x140 = rfagcreg * 140;
    }
    
    if(type == 0x07){
        if(agcreg_x140 <  4896 ){
            rfgain = rfgainmax_x100;
        }else if(agcreg_x140 <  5457 ){
            rfgain = rfgainmax_x100        - ( 85 * (agcreg_x140 -  4896) + 127) / 255; /* Round */
        }else if(agcreg_x140 <  8823 ){
            rfgain = rfgainmax_x100 -  187;
        }else if(agcreg_x140 < 24786 ){
            rfgain = rfgainmax_x100 -  187 - ( 85 * (agcreg_x140 -  8823) + 127) / 255; /* Round */
        }else if(agcreg_x140 < 30090 ){
            rfgain = rfgainmax_x100 - 5508 - (115 * (agcreg_x140 - 24786) + 127) / 255; /* Round */
        }else{
            rfgain = rfgainmax_x100 - 7900 - (160 * (agcreg_x140 - 30090) + 127) / 255; /* Round */
        }
    } else {
        if(agcreg_x140 <  4896 ){
            rfgain = rfgainmax_x100;
        }else if(agcreg_x140 <  5457 ){
            rfgain = rfgainmax_x100        - ( 70 * (agcreg_x140 -  4896) + 127) / 255; /* Round */
        }else if(agcreg_x140 <  8823 ){
            rfgain = rfgainmax_x100 -  154;
        }else if(agcreg_x140 < 24786 ){
            rfgain = rfgainmax_x100 -  154 - ( 70 * (agcreg_x140 -  8823) + 127) / 255; /* Round */
        }else if(agcreg_x140 < 30090 ){
            rfgain = rfgainmax_x100 - 4536 - ( 57 * (agcreg_x140 - 24786) + 127) / 255; /* Round */
        }else{
            rfgain = rfgainmax_x100 - 5722 - (160 * (agcreg_x140 - 30090) + 127) / 255; /* Round */
        }
    }
   
    if(ofs >= 0x80) {
        moduleoffset = ((( ofs - 0x0100 ) * 25) >> 1) - (lna * 1000); 
    } else {
        moduleoffset = ((  ofs            * 25) >> 1) - (lna * 1000); 
    }
        
    rssi_x100 = - ifgain - rfgain + moduleoffset;

    return (INT16)rssi_x100;
    
}
#if 0
/******************************************************************************
 * cmd_help
 *-----------------------------------------------------------------------------
 * help
 *****************************************************************************/
static int Terr_cmd_help(int argc, char **argv)
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
    DBG_PRINT("gettype\n");
    DBG_PRINT("        detect tunermodule \n");
    DBG_PRINT("\n");
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
    DBG_PRINT("lna [ena]\n");
    DBG_PRINT("        LNA control\n");
    DBG_PRINT("        [ena] set [OFF/ON]\n");
    DBG_PRINT("shift [freq] [mode] [region(option)]\n");
    DBG_PRINT("        shift RF frequency without calibration\n");
    DBG_PRINT("        [freq] set frequency [kHz]\n");
    DBG_PRINT("        [mode] set receiving system.\n");
    DBG_PRINT("        [region] set country special information (Option).\n");
    DBG_PRINT("rssi\n");
    DBG_PRINT("        Get RSSI[dBm]\n");
    DBG_PRINT("\n");  
    DBG_PRINT("------------------------------ \n");
    DBG_PRINT("SUT-PEx41 Sample Code\n");
    DBG_PRINT(" (C) Sony corporation\n ");
    DBG_PRINT("     all right reserved.\n\n");

    return 0;
}

/******************************************************************************
 * cmd_error
 *-----------------------------------------------------------------------------
 * show help
 *****************************************************************************/
static int Terr_cmd_error(int argc, char **argv)
{
    DBG_PRINT("Command Error\n");
    Terr_cmd_help(argc, argv);

    return -1;
}
#endif
/******************************************************************************
 * Register Setting (raleted HELENE Application Note basically.)
 *****************************************************************************/

/******************************************************************************
 * x_pon
 *-----------------------------------------------------------------------------
 * Input        : none
 * Output       : none
 * Return       : none
 *****************************************************************************/
static void Terr_x_pon(void)
{

    UINT8 t_addr;
    UINT8 t_data[16];
    UINT8 data_length;
    UINT8 val;
    UINT8 TunerType;

    DBG_PRINT("Enter x_pon()...");

    tuner_block_id = TERR_1ST_TUNER;

    TunerType = Terr_tuner_count();
  
    t_addr     = 0x99;
    t_data[0]  = 0x7A;
    t_data[1]  = 0x01;
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );  
  
    t_addr     = 0x81;
    t_data[0]  = XTAL; // 0x81
    switch(TunerType){ 
        case 1: // single Tuner (SUT-PE244)
            t_data[1]  = 0x84;
            t_data[2]  = 0xE4;
            t_data[3]  = 0x00;
            t_data[4]  = 0x00; // 0x85
            break;
        case 2: // double Tuner (SUT-PE544)
            if(tuner_block_id == TERR_1ST_TUNER){
                t_data[1]  = 0x84;
                t_data[2]  = 0x9E;
                t_data[3]  = 0x00;
                t_data[4]  = 0x01; // 0x85
            }else{
                t_data[1]  = 0x00;
                t_data[2]  = 0x00;
                t_data[3]  = 0x00;
                t_data[4]  = 0x00; // 0x85
            }
            break;
        default:
            if(tuner_block_id == TERR_1ST_TUNER){
                t_data[1]  = 0x84;
                t_data[2]  = 0x9E;
                t_data[3]  = 0x00;
                t_data[4]  = 0x01; // 0x85
            }else{
                t_data[1]  = 0x00;
                t_data[2]  = 0x00;
                t_data[3]  = 0x00;
                t_data[4]  = 0x00; // 0x85
            }
            break;
    }    
    t_data[5]  = 0x10;
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
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    
    
    t_addr     = 0x91;    
    t_data[0]  = 0x10; // 0x91
    t_data[1]  = 0x20;
    t_data[2]  = 0x0A;
    t_data[3]  = 0x00;
    data_length = 4;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    
    Terr_iic_write_val( tuner_block_id, 0x9B, 0x00 );

    Terr_waitms(10);   

    t_addr    = 0x17;
    t_data[0] = 0x90;
    t_data[1] = 0x06;
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    

    Terr_waitms(1);  

    Terr_iic_read_val ( tuner_block_id, 0x19, &val );    
    Terr_iic_write_val( tuner_block_id, 0x95, (val & 0xF0) >> 4 );    

    Terr_iic_write_val( tuner_block_id, 0x74, 0x12 );
    Terr_iic_write_val( tuner_block_id, 0x67, 0x00 );
    t_addr    = 0x5E;
    t_data[0] = 0x15;
    t_data[1] = 0x00;
    t_data[2] = 0x00;
    data_length = 3;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    Terr_iic_write_val( tuner_block_id, 0x88, 0x00 );    
    Terr_iic_write_val( tuner_block_id, 0x87, 0xC0 ); 
  
    Terr_iic_write_val( tuner_block_id, 0x80, 0x01 );   
 
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
static void Terr_x_tune(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal)
{
    UINT8 t_addr;
    UINT8 t_data[8];
    UINT8 data_length;
    UINT8 option = 0x00;
    UINT8 *param;
    //UINT8 reg;

    DBG_PRINT("Enter x_tune()... ");
    
    param = Terr_tuner_init_setparam( frequency, mode, cal);    

    if((mode >= SONY_HELENE_ATV_MIN) && (mode <= SONY_HELENE_ATV_MAX)) option += 0x80;
    if( mode == SONY_HELENE_ATV_L_DASH ) option += 0x40;
    if((mode >= SONY_HELENE_DTV_MIN) && (mode <= SONY_HELENE_DTV_MAX)){
         frequency = (( frequency + 25 / 2 ) / 25 ) * 25;
    }

    if(cal){
        t_addr     = 0x74;
        t_data[0]  = 0x12;     // 0x74
        t_data[1]  = param[0];
        t_data[2]  = param[1];
        t_data[3]  = param[2];
        t_data[4]  = param[3]; // 0x78
        t_data[5]  = Terr_tuner_setModuleOffset(frequency, mode); // 0x79
        data_length = 6;
        Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    }

    Terr_iic_write_val( tuner_block_id, 0x8B, param[26] ); 
    Terr_iic_write_val( tuner_block_id, 0x8E, param[25] ); 

    t_addr     = 0x91;
    t_data[0]  = param[23];
    t_data[1]  = param[24];
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    
     
    t_addr     = 0x9C;
    t_data[0]  = param[4];
    t_data[1]  = param[5];
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    

    t_addr     = 0x87;
    t_data[0]  = 0xC4;       // 0x87
    t_data[1]  = 0x40;
    data_length = 2;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    
 
    t_addr     = 0x5E;
    t_data[0]  = 0xEE;
    t_data[1]  = 0x02;
    t_data[2]  = 0x1E;
    data_length = 3;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    
 
    t_addr     = 0x61;
    t_data[0]  = param[6];
    t_data[1]  = param[7];   // 0x62
    t_data[2]  = param[8];
    t_data[3]  = param[9];
    t_data[4]  = param[10];
    t_data[5]  = param[11];  // 0x66
    t_data[6]  = param[12];
    data_length = 7;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    
    t_addr     = 0x68;    
    t_data[0]  = param[13];  // 0x68
    t_data[1]  = param[22];    
    t_data[2]  = param[14];  
    t_data[3]  = param[15];
    t_data[4]  = param[16];  // 0x6c
    t_data[5]  = param[17];
    t_data[6]  = param[18]; 
    t_data[7]  = param[19];
    data_length = 8;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    
    t_addr     = 0x70;        
    t_data[0]  = ((frequency & 0x0000ff));
    t_data[1]  = ((frequency & 0x00ff00) >>  8);
    t_data[2]  = ((frequency & 0x0f0000) >> 16) + option;
    t_data[3]  = param[20];
    t_data[4]  = param[21];
    data_length = 5;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );    

    DBG_PRINT(" Done. \n");

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

static void Terr_x_tune_end(void)
{

    DBG_PRINT("Enter x_tune_end()... ");
    
    Terr_iic_write_val( tuner_block_id, 0x88, 0x00 );
    Terr_iic_write_val( tuner_block_id, 0x87, 0xC0 );

    DBG_PRINT(" Done. \n");

    return;
}

/******************************************************************************
 * x_fin()
 *-----------------------------------------------------------------------------
 * Input        : none
 * Output       : none
 * Return       : none
 *****************************************************************************/
static void Terr_x_fin(void)
{
    UINT8 t_addr;
    UINT8 t_data[3];
    UINT8 data_length;

    DBG_PRINT("Enter x_fin()...");
	
    Terr_iic_write_val( tuner_block_id, 0x74, 0x12 );
    Terr_iic_write_val( tuner_block_id, 0x67, 0x00 );
    t_addr    = 0x5E;
    t_data[0] = 0x15;
    t_data[1] = 0x00;
    t_data[2] = 0x00;
    data_length = 3;
    Terr_iic_write( tuner_block_id, t_addr , t_data, data_length );
    Terr_iic_write_val( tuner_block_id, 0x88, 0x00 );    
    Terr_iic_write_val( tuner_block_id, 0x87, 0xC0 ); 
    
    DBG_PRINT(" Done. \n");

    return;
}

/******************************************************************************
 * tuner_gpio
 *-----------------------------------------------------------------------------
 * Input        : IFOUT_AGC_PORT port
 * Output       : none
 * Return       : none
 * Description  : control GPIO.
 *****************************************************************************/
static void Terr_tuner_gpio(UINT8 port, UINT8 val)
{

    UINT8 reg;
    
    DBG_PRINT("Enter tuner_gpio()...");

    if(port == 0){
        reg = 0x85;
    }
    
    Terr_iic_write_val( tuner_block_id, reg, val );

    DBG_PRINT(" Done. \n");

    return;
}

/******************************************************************************
 * tuner_init_setparam
 *-----------------------------------------------------------------------------
 * Input        : RECEIVE_MODE m_mode
 * Output       : none
 * Return       : UINT8 *param
 * Description  : select RF Data
 *****************************************************************************/
static UINT8* Terr_tuner_init_setparam(UINT32 frequency, RECEIVE_MODE mode, UINT8 cal)
{
    static UINT8 buf[27];
    sony_helene_adjust_param_t *p;
    UINT8 i;
    UINT8 extctrl;
    UINT8 tmp;

    param_table = (sony_helene_adjust_param_t*)g_param_table_sony_module;

    p = &param_table[mode];


    extctrl = Terr_tuner_setextctrl(frequency, mode);

    if((mode >= SONY_HELENE_ATV_MIN) && (mode <= SONY_HELENE_ATV_MAX)){
        buf[0]  = 0xD9;
        buf[1]  = 0x0F;
        buf[2]  = 0x25;
        buf[3]  = 0x87;        
        buf[4]  = 0x00;
        buf[7]  = 0x20;
        buf[8]  = 0x1C;
        buf[9]  = 0x78;
        buf[10] = 0x08;
        buf[11] = 0x1C;
        buf[26] = 0x01;
    }else if( mode == SONY_HELENE_DTV_DVBC_6  || mode == SONY_HELENE_DTV_DVBC_8 ) {
        buf[0]  = 0xD9;
        buf[1]  = 0x0F;
        buf[2]  = 0x25;
        buf[3]  = 0x87;    
        buf[4]  = 0x00;
        buf[7]  = 0x10;
        buf[8]  = 0x1C;
        buf[9]  = 0x78;
        buf[10] = 0x08;
        buf[11] = 0x1C;
        buf[26] = 0x45;
    }else if( mode == SONY_HELENE_DTV_DVBC2_6 || mode == SONY_HELENE_DTV_DVBC2_8 || mode == SONY_HELENE_DTV_DTMB ) {
        buf[0]  = 0x99;
        buf[1]  = 0x00;
        buf[2]  = 0x24;
        buf[3]  = 0x87;    
        buf[4]  = 0x00;
        buf[7]  = 0x02;
        buf[8]  = 0xB4;
        buf[9]  = 0x78;
        buf[10] = 0x08;
        buf[11] = 0x30;
        buf[26] = 0x45;
    }else if( mode == SONY_HELENE_DTV_8VSB || mode == SONY_HELENE_DTV_QAM) {
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
        buf[26] = 0x45;
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
        buf[26] = 0x45;
    }

    buf[5]  = p->IS_LOWERLOCAL;         
    buf[12] = extctrl;
    buf[13] = p->OUTLMT;
    buf[14] = 0x00;    

    if( mode == SONY_HELENE_DTV_8VSB || mode == SONY_HELENE_DTV_QAM){
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

    buf[17] = ((p->IF_BPF_F0) << 4) + p->BW;
    buf[18] = p->FIF_OFFSET;        
    buf[19] = p->BW_OFFSET;            
    buf[21] = ((p->AGC_SEL) << 4) + p->IF_OUT_SEL;
    if(p->RF_GAIN == AUTO) buf[22] = 0x80                + p->IF_BPF_GC;
    else                   buf[22] = ((p->RF_GAIN) << 4) + p->IF_BPF_GC;

    if(cal == 1){
        buf[6]  = 0x67;
        buf[20] = 0xFF;
    }else{
        buf[6]  = 0x45;
        buf[20] = 0x8F;
    }

    if( mode == SONY_HELENE_DTV_DVBC_6  || mode == SONY_HELENE_DTV_DVBC_8 ) {
        buf[23] = 0x16;
        buf[24] = 0x26;
    }else{
        buf[23] = 0x10;
        buf[24] = 0x20;
    }

    printf("\n------reg  setting------\n");
    printf("    ");    
    for(i= 0;i<= 3;i++) printf("0x%x ",buf[i]); printf("\n    ");
    for(i=26;i<=26;i++) printf("0x%x ",buf[i]); printf("\n    ");    
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

static UINT8 Terr_tuner_setextctrl(UINT32 frequency, RECEIVE_MODE mode){
    
#define GA_MODEL 1    // <- Please change active if you use GA model Tuner. 
    
    UINT8 val;
    
    switch(mode){
        case SONY_HELENE_DTV_8VSB:
        case SONY_HELENE_DTV_QAM:
        case SONY_HELENE_DTV_ISDBT_6:
        case SONY_HELENE_DTV_DVBT_6:
        case SONY_HELENE_DTV_DVBT2_6:
#ifndef GA_MODEL        
        case SONY_HELENE_ATV_MN_SAP:
#endif
        case SONY_HELENE_DTV_DVBC_6:
        case SONY_HELENE_DTV_DVBC2_6:

            if(frequency >= 464000) {
                val = 0x01;
            } else {
                val = 0x00;
            }

            break;

        case SONY_HELENE_DTV_DVBT_7:
        case SONY_HELENE_DTV_DVBT_8:
        case SONY_HELENE_DTV_DVBT2_7:
        case SONY_HELENE_DTV_DVBT2_8:
        case SONY_HELENE_DTV_DTMB:
#ifdef GA_MODEL
        case SONY_HELENE_ATV_MN_SAP:
#endif
        case SONY_HELENE_ATV_BG:
        case SONY_HELENE_ATV_I:
        case SONY_HELENE_ATV_DK:
        case SONY_HELENE_ATV_L:
        case SONY_HELENE_ATV_L_DASH:
        case SONY_HELENE_DTV_DVBC_8:
        case SONY_HELENE_DTV_DVBC2_8:
        default:

            if((mode >= SONY_HELENE_ATV_MIN) && (mode <= SONY_HELENE_ATV_MAX)) {
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

static UINT8 Terr_tuner_setModuleOffset(UINT32 freq, RECEIVE_MODE mode){

    UINT8 i;
    INT16 offset_x100;
    UINT8 offsetreg;
    sony_helene_ModuleParam* table;
    UINT8 lna;
    UINT8 TunerType;

    table = (sony_helene_ModuleParam*)DEFAULT;

    TunerType = Terr_tuner_count();
	if(TunerType == 1){
		table = (sony_helene_ModuleParam*)PE241_RSSI_TABLE;
	}else{
        Terr_iic_read_val ( TERR_1ST_TUNER, 0x85, &lna );		
        if(tuner_block_id == TERR_1ST_TUNER){
            if(lna == 0x01)table = (sony_helene_ModuleParam*)PE541_LNAON_RSSI_TABLE_1ST;
			else           table = (sony_helene_ModuleParam*)PE541_LNAOFF_RSSI_TABLE_1ST;
        }else{
            if(lna == 0x01)table = (sony_helene_ModuleParam*)PE541_LNAON_RSSI_TABLE_2ND;
			else           table = (sony_helene_ModuleParam*)PE541_LNAOFF_RSSI_TABLE_2ND;
        }
	}

    i = 0;
    while( freq < table[i].freq ){
        i++;
    }

    offset_x100 = demod_iftgt[mode] + table[i].param;

    if(offset_x100 > 1588)       offset_x100 =  1588;
    else if(offset_x100 < -1600) offset_x100 = -1600;

    if(offset_x100 > 0) offsetreg = (UINT8)((offset_x100 * 10 + 125/2) / 125);
    else                offsetreg = (UINT8)((offset_x100 * 10 - 125/2) / 125);

    return offsetreg;

}

/******************************************************************************
 * tuner_count
 *-----------------------------------------------------------------------------
 * Input        : UINT8 val
 * Output       : none
 * Return       : none
 * Description  : control GPIO.
 *****************************************************************************/
static int Terr_tuner_count(void)
{
    UINT8 i;
    UINT8 val;

    Terr_iic_write_val( TERR_1ST_TUNER, 0x86, 0x10 );
    Terr_iic_read_val ( TERR_1ST_TUNER, 0x4b, &val );

    if(val == 0x00){
		i = 1;
    }else{
		i = 2;
	}
	 
    return (i);	 
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
static INT16 Terr_iic_write_val(INT16 id, UINT8 subadr, UINT8 val){
    Terr_iic_write(id, subadr, &val, 1);
    return 0;
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
static INT16 Terr_iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len){

    switch( (BLOCKID)id ) {
        
        case TERR_1ST_TUNER:
            Terr_write_tuner( SLAVE_1ST_ADDRESS, subadr, data, len );        
            break;
        case TERR_2ND_TUNER:
            Terr_write_tuner( SLAVE_2ND_ADDRESS, subadr, data, len );
            break;
        default :
            break;
    }
    return 0;
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
static INT16 Terr_iic_read_val(INT16 id, UINT8 subadr, UINT8* val){
    Terr_iic_read(id, subadr, val, 1);
    return 0;
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
static INT16 Terr_iic_read(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len){

    switch( (BLOCKID)id ) {
        
        case TERR_1ST_TUNER:
            Terr_read_tuner( SLAVE_1ST_ADDRESS, subadr, data, len );
            break;
        case TERR_2ND_TUNER:
            Terr_read_tuner( SLAVE_2ND_ADDRESS, subadr, data, len );
            break;
        default :
            break;
    }
    return 0;
}

#define SONY_SUT_RE23x_I2C_ADDR_terr (((UINT16)TUNER_IIC_BUS<<8)|0xC0 )
/******************************************************************************
 * write_tuner
 *****************************************************************************/
static INT16 Terr_write_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
) {

    unsigned char *buffer;

    UNUSED (slv);

    buffer = (unsigned char *)malloc(sizeof(unsigned char)*len + 1);
    buffer[0] = subadr;
    memcpy(&buffer[1],data,len);
    
    if(MDrv_IIC_WriteBytes(SONY_SUT_RE23x_I2C_ADDR_terr, 0, NULL,  len + 1, buffer) == FALSE)
    {
        printf("iptr->WriteBytes(0, NULL, wlength, wdata) == MAPI_FALSE\n");
    }

    free(buffer);

    return 0;
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

static INT16 Terr_read_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
) {
    UNUSED (slv);

    if(MDrv_IIC_ReadBytes(SONY_SUT_RE23x_I2C_ADDR_terr, 1, &subadr, len, data) == FALSE)
    {
        printf("iptr->WriteBytes(0, NULL, wlength, wdata) == MAPI_FALSE\n");
    }
    return 0;
}

/******************************************************************************
 * waitms
 *-----------------------------------------------------------------------------
 * Input : UINT32 ms
 * Output: none
 * Return: void
 *****************************************************************************/
static void Terr_waitms(UINT32 ms) {

    MsOS_DelayTask(ms);
    return;
}

/******************************************************************************
 * History
 *
 * 2014-04-21 v1.0.0.0 initial  
 ******************************************************************************/
