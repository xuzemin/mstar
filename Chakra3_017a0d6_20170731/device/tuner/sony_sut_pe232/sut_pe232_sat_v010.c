/******************************************************************************
 *   $ Copyright $ Sony Corporation
 *-----------------------------------------------------------------------------
 *   File Name   : $File: sut_pe23x.c $
 *   Modified    : $Date: 2013/04/24 $ By $Author: $
 *   Revision    : $Revision: 0.10 $
 *   Description : SUT-PE23x Tuner Control Sample Code
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
#include "sut_pe232_rssi.h"

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

/*************************************************
 Block ID definition for I2C access
**************************************************/
typedef enum {
    SAT_1ST_TUNER,   /* Tag for Main Tuner Block           */
} BLOCKID;

typedef enum {
    SONY_HORUS_SAT_SYSTEM_UNKNOWN,
    SONY_HORUS_SAT_SYSTEM_DVBS,      /* DVB-S */
    SONY_HORUS_SAT_SYSTEM_DVBS2      /* DVB-S2 */
} RECEIVE_MODE;

/*************************************************
 default slave address
**************************************************/
#define SLAVE_1ST_ADDRESS   0xC6
//#define SLAVE_2ND_ADDRESS   0xC6
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
#define IIC_CH_SUT                      0 // NO USE

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
#define DBG_PRINT_OUT 0
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
static INT16 iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len);


static INT16 write_tuner(
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
//static int cmd_init(int argc, char **argv);
static int cmd_init(void);
//static int cmd_wake(int argc, char **argv);
static int cmd_wake(void);
//static int cmd_tune(int argc, char **argv);
//static int cmd_sleep(int argc, char **argv);


/* status */
//static int cmd_help(int argc, char **argv);                             /* help */
//static int cmd_error(int argc, char **argv);

/*************************************************
 Tuning Sequece
**************************************************/
static void x_pon(void);                                                /* tuner: Initialize        */
static void x_wake(void);                                               /* tuner: set parameter     */
static void x_tune(UINT32 frequency, UINT32 symbolrate, RECEIVE_MODE mode);/* tuner: tune              */
static void x_fin(void);                                                /* tuner: sleep             */

static UINT8 tuner_calc_E(UINT32 symbolrate,RECEIVE_MODE mode);
/* utility */

/******************************************************************************
 * main
 *-----------------------------------------------------------------------------
 * Input : INT16 argc, char* argv[]
 * Output: none
 * Return: int
 *****************************************************************************/
#if 0
int main(int argc, char* argv[]) {
    INT16 i;


    if (argc < 2) {
        cmd_help(argc - 1, argv);
        return 1;

    }else if (strcmp(argv[1], "1st") == 0) {
        tuner_block_id = SAT_1ST_TUNER;
    }else if (strcmp(argv[1], "help") == 0) {
        cmd_help(argc - 1, argv);
        return 0 ;
        
    }else {
        printf("!!! Command Error !!!\n");
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
    } else if (strcmp(argv[0], "wakeup") == 0) {
        cmd_wake(argc - 2, argv);
    } else if (strcmp(argv[0], "tune") == 0) {
        cmd_tune(argc - 2, argv);
    } else if (strcmp(argv[0], "sleep") == 0) {
        cmd_sleep(argc - 2, argv);    
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
//static int cmd_init(int argc, char **argv)
static int cmd_init(void)
{
    DBG_PRINT("Enter cmd_init\n");

    x_pon();

    return 0;
}
/******************************************************************************
 * cmd_wake
 *-----------------------------------------------------------------------------
 * 
 *****************************************************************************/
//static int cmd_wake(int argc, char **argv)
static int cmd_wake(void)
{
    DBG_PRINT("Enter cmd_wake\n");

    x_wake();

    return 0;
}

/******************************************************************************
 * cmd_tune
 *-----------------------------------------------------------------------------
 *
 *****************************************************************************/
#if 0
static int cmd_tune(int argc, char **argv)
{
    //int i;
    UINT32 frequency;
    UINT32 symbolrate;
    RECEIVE_MODE mode;

    DBG_PRINT("Enter cmd_tune\n");

    if(argc > 1) frequency = atoi(argv[1]);
    else frequency = 1500000;    /* Default: 1500000kHz */ 
    

    

    mode = SONY_HORUS_SAT_SYSTEM_UNKNOWN;
    if (argc > 2) {
        if (strncmp(argv[2], "DVBS"    , 4) == 0) mode = SONY_HORUS_SAT_SYSTEM_DVBS;
        if (strncmp(argv[2], "DVBS2"   , 5) == 0) mode = SONY_HORUS_SAT_SYSTEM_DVBS2;
    } else {
         ;
    }
     
    if(mode == SONY_HORUS_SAT_SYSTEM_UNKNOWN){
        printf("ERROR : selected system is Illegal.\n");
        return 0;
    }     
	
	if(argc > 3) symbolrate = atoi(argv[3]);
    else symbolrate = 30000;     /* Default = 30000kSps */
	
	
    x_tune(frequency, symbolrate, mode);
    waitms(10);

    return 0;

}
#endif
//static int mdev_TunerDigitalSetFreq_SUT(int argc, char **argv)
static int mdev_TunerDigitalSetFreq_SUT(MS_U16 FreqMHz, MS_U32 u32SymbolRate_kHz)
{
    //int i;
    UINT32 frequency;
    UINT32 symbolrate;
    RECEIVE_MODE mode;

    DBG_PRINT("Enter cmd_tune(%d, %d)\n",(int)FreqMHz, (int)u32SymbolRate_kHz );
    
    frequency = FreqMHz*1000;//khz
    symbolrate = u32SymbolRate_kHz;

    mode = SONY_HORUS_SAT_SYSTEM_DVBS;

    cmd_wake();
    x_tune(frequency, symbolrate, mode);
    //x_fin();//mdev_Tuner_sleep_mode();
    waitms(10);

    return 0;
}


/******************************************************************************
 * cmd_sleep
 *-----------------------------------------------------------------------------
 * 
 *****************************************************************************/
#if 0
static int cmd_sleep(int argc, char **argv)
{
    DBG_PRINT("Enter cmd_sleep\n");

    x_fin();

    return 0;
}
#endif





/******************************************************************************
 * cmd_help
 *-----------------------------------------------------------------------------
 * help
 *****************************************************************************/
#if 0
static int cmd_help(int argc, char **argv)
{
    printf("\n\n");

    printf("------------------------------ \n");
    printf("\n");
    printf("*********************************************************\n");
    printf(" 1st \n");
    printf(" : set tuner slave address (1st) before all command\n");
    printf("   Exp : Slv 0xC6 initialization \n");  
    printf("          ./<name> 1st init \n");
    printf("\n");    
    printf("*********************************************************\n");
    printf("####### COMMANDS #######\n");
    printf("init\n");
    printf("        tuner initialization\n");
    printf("\n");
    printf("wakeup\n");
    printf("        tuner wakeup\n");
    printf("\n");
    printf("tune [freq] [sr] [mode] \n");
    printf("        tune\n");
    printf("        [freq] set frequency [kHz]\n");
    printf("        [mode] set receiving system. select below.\n");
    printf("               -----------------------------------\n");
    printf("               DVBS      - DVB-S \n");
    printf("               DVBS2     - DVB-S.2\n");
    printf("               -----------------------------------\n");
    printf("        [sr]   set symbol rate [kSps]\n");
    printf("   Exp : tune 1st on 1500000kHz DVB-S2 30000kSps\n");
    printf("          ./<name> 1st tune 1500000 DVBS2 30000\n");
    printf("sleep\n");
    printf("        sleep\n");
    printf("\n");  
    printf("------------------------------ \n");
    printf("SUT-PE23x Sample Code\n");
    printf(" (C) Sony corporation\n ");
    printf("     all right reserved.\n\n");
    return 0;
}
#endif
/******************************************************************************
 * cmd_error
 *-----------------------------------------------------------------------------
 * show help
 *****************************************************************************/
#if 0
static int cmd_error(int argc, char **argv)
{
    printf("Command Error\n");
    cmd_help(argc, argv);

    return -1;
}
#endif
/******************************************************************************
 * Register Setting (raleted Horus3A Application Note basically.)
 *****************************************************************************/

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
    UINT8 t_data[4];
    UINT8 data_length;

    DBG_PRINT("Enter x_pon()...\n");


    iic_write_val( tuner_block_id, 0x2A, 0x79 ); 
   
    t_addr    = 0x06;
    t_data[0] = XTAL;
    t_data[1] = XTAL;
    t_data[2] = 0x00;
    data_length = 3;
    iic_write( tuner_block_id, t_addr , t_data, data_length );
    
    iic_write_val( tuner_block_id, 0x0A, 0x40 );    
    iic_write_val( tuner_block_id, 0x0E, 0x00 );
    iic_write_val( tuner_block_id, 0x2A, 0x79 );
    iic_write_val( tuner_block_id, 0x29, 0x70 );
    iic_write_val( tuner_block_id, 0x28, 0x3E );
	iic_write_val( tuner_block_id, 0x2A, 0x19 );
    iic_write_val( tuner_block_id, 0x1C, 0x00 );



    t_addr    = 0x11;
    t_data[0] = 0xC0;
    t_data[1] = 0x23;
    data_length = 2;
    iic_write( tuner_block_id, t_addr , t_data, data_length );
    
    waitms(3);

    DBG_PRINT(" Done. \n");
    
    return;
}


/******************************************************************************
 * x_wake()
 *-----------------------------------------------------------------------------
 * Input        : none
 * Output       : none
 * Return       : none
 *****************************************************************************/
static void x_wake(void)
{
    UINT8 t_addr;
    UINT8 t_data[2];
    UINT8 data_length;

    DBG_PRINT("Enter x_wake()...");
    
    t_addr    = 0x11;
    t_data[0] = 0x00;
    t_data[1] = 0x27;
    data_length = 2;
    iic_write( tuner_block_id, t_addr, t_data, data_length );
    
    
	iic_write_val( tuner_block_id, 0x2A, 0x79 );
	iic_write_val( tuner_block_id, 0x1C, 0xC0 );
	iic_write_val( tuner_block_id, 0x29, 0x71 );

    DBG_PRINT(" Done. \n");

    return;
}

/******************************************************************************
 * x_tune
 *-----------------------------------------------------------------------------
 * Input        : frequency , symbolrate , mode
 * Output       : none
 * Return       : none
 * Description  : 
 *****************************************************************************/
static void x_tune(UINT32 frequency, UINT32 symbolrate,RECEIVE_MODE mode)
{
    UINT16 n;
    UINT8 byte_C;
    UINT8 byte_D=0;
    UINT8 byte_E=0;
    UINT8 t_addr;
    UINT8 t_data[5];
    UINT8 data_length; 

    DBG_PRINT("Enter x_tune(%d,%d,%d)... \n",(int)frequency,(int)symbolrate,(int)mode);
    

    /* frequency counter */
    if(frequency <= 1155000) {
        n = (UINT16)((frequency + 500) / 1000) * 2;
        byte_C = 0x80;
    } else {
        n = (UINT16)((frequency + 500) / 1000);
        byte_C = 0x00;
    }
    DBG_PRINT("n(%x)byte_C(%x)... \n",n,byte_C);

    if( frequency < 975000){
        byte_D = 0x3c;
    }else if ( (frequency >=  975000) && (frequency < 1050000) ) {
        byte_D = 0x58;
    }else if ( (frequency >= 1050000) && (frequency < 1150000) ) {
        byte_D = 0x54;
    }else if ( (frequency >= 1150000) && (frequency < 1250000) ) {
        byte_D = 0x70;
    }else if ( (frequency >= 1250000) && (frequency < 1350000) ) {
        byte_D = 0x8c;
    }else if ( (frequency >= 1350000) && (frequency < 1450000) ) {
        byte_D = 0x8a;
    }else if ( (frequency >= 1450000) && (frequency < 1600000) ) {
        byte_D = 0xa7;
    }else if ( (frequency >= 1600000) && (frequency < 1800000) ) {
        byte_D = 0xc4;
    }else if ( (frequency >= 1800000) && (frequency < 2000000) ) {
        byte_D = 0xc2;
    }else {                               /*frequency > 2000000 */
        byte_D = 0xe0;
    }
    DBG_PRINT("byte_D(%d)byte_E(%d)... \n",(int)byte_D,(int)byte_E);

	byte_E = tuner_calc_E( symbolrate , mode );

    

    /* write tuner data */
    t_addr = 0x00;
    t_data[0] = (UINT8)((n & 0x7f80) >> 7);
    t_data[1] = (UINT8)((n & 0x007f) << 1);
    t_data[2] = 0x00;                      
    t_data[3] = 0x00;                      
    t_data[4] = byte_C;                    
    data_length = 5;
    iic_write( tuner_block_id, t_addr, t_data, data_length);
    

    iic_write_val( tuner_block_id, 0x09, byte_D );
    iic_write_val( tuner_block_id, 0x37, byte_E );
    iic_write_val( tuner_block_id, 0x05, 0x80   );
	iic_write_val( tuner_block_id, 0x2A, 0x7B   );

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
static void x_fin(void)
{
    UINT8 t_addr;
    UINT8 t_data[2];
    UINT8 data_length;

    DBG_PRINT("Enter x_fin()...");
    
    iic_write_val( tuner_block_id, 0x2A, 0x79 );
    iic_write_val( tuner_block_id, 0x29, 0x70 );
    iic_write_val( tuner_block_id, 0x28, 0x3E );
    iic_write_val( tuner_block_id, 0x2A, 0x19 );
    iic_write_val( tuner_block_id, 0x1C, 0x00 );


    t_addr    = 0x11;
    t_data[0] = 0xC0;
    t_data[1] = 0x23;
    data_length = 2;
    iic_write( tuner_block_id, t_addr, t_data, data_length );
    
    DBG_PRINT(" Done. \n");

    return;
}

/******************************************************************************
 * tuner_calc_E
 *-----------------------------------------------------------------------------
 * Input        : symbolrate , mode
 * Output       : none
 * Return       : parameter 'E' value
 * Description  : 
 *****************************************************************************/

static UINT8 tuner_calc_E(UINT32 sr,RECEIVE_MODE mode){

    UINT8 byte_E = 0x8A; //Default
	
 	if(mode == SONY_HORUS_SAT_SYSTEM_DVBS) {
		if(                       sr <= 4300   ) byte_E = 0x8A;
		else if( (sr > 4300 ) && (sr <= 5100 ) ) byte_E = 0x8C;
		else if( (sr > 5100 ) && (sr <= 6000 ) ) byte_E = 0x8E;
		else if( (sr > 6000 ) && (sr <= 6800 ) ) byte_E = 0x90;
		else if( (sr > 6800 ) && (sr <= 7700 ) ) byte_E = 0x92;
		else if( (sr > 7700 ) && (sr <= 8500 ) ) byte_E = 0x94;
		else if( (sr > 8500 ) && (sr <= 9400 ) ) byte_E = 0x96;
		else if( (sr > 9400 ) && (sr <= 10400) ) byte_E = 0x98;
		else if( (sr > 10400) && (sr <= 11900) ) byte_E = 0x9A;
		else if( (sr > 11900) && (sr <= 13300) ) byte_E = 0x9C;
		else if( (sr > 13300) && (sr <= 14800) ) byte_E = 0x9E;
		else if( (sr > 14800) && (sr <= 16300) ) byte_E = 0xA0;
		else if( (sr > 16300) && (sr <= 17800) ) byte_E = 0xA2;
	    else if( (sr > 17800) && (sr <= 19300) ) byte_E = 0xA4;
	    else if( (sr > 19300) && (sr <= 20700) ) byte_E = 0xA6;
	    else if( (sr > 20700) && (sr <= 22200) ) byte_E = 0xA8;
	    else if( (sr > 22200) && (sr <= 23700) ) byte_E = 0xAA;
	    else if( (sr > 23700) && (sr <= 25200) ) byte_E = 0xAC;
	    else if( (sr > 25200) && (sr <= 26700) ) byte_E = 0xAE;
	    else if( (sr > 26700) && (sr <= 28100) ) byte_E = 0xB0;
	    else if( (sr > 28100) && (sr <= 29600) ) byte_E = 0xB2;
	    else if( (sr > 29600) && (sr <= 31100) ) byte_E = 0xB4;
	    else if( (sr > 31100) && (sr <= 32600) ) byte_E = 0xB6;
	    else if( (sr > 32600) && (sr <= 34100) ) byte_E = 0xB8;
	    else if( (sr > 34100) && (sr <= 35600) ) byte_E = 0xBA;
	    else if( (sr > 35600) && (sr <= 37000) ) byte_E = 0xBC;
	    else if( (sr > 37000) && (sr <= 38500) ) byte_E = 0xBE;
	    else if( (sr > 38500) && (sr <= 40000) ) byte_E = 0xC0;
	    else if( (sr > 40000) && (sr <= 41500) ) byte_E = 0xC2;
	    else if( (sr > 41500) && (sr <= 43000) ) byte_E = 0xC4;
	    else if( (sr > 43000) && (sr <= 44400) ) byte_E = 0xC6;
	    else if( (sr > 44400) && (sr <= 45000) ) byte_E = 0xC8;
	    else printf("ERROR : symbol rate is Illegal.\n");
	    
 	} else if(mode == SONY_HORUS_SAT_SYSTEM_DVBS2) {
		if(                       sr <= 4500   ) byte_E = 0x8A;
		else if( (sr > 4500 ) && (sr <= 5500 ) ) byte_E = 0x8C;
		else if( (sr > 5500 ) && (sr <= 6400 ) ) byte_E = 0x8E;
		else if( (sr > 6400 ) && (sr <= 7300 ) ) byte_E = 0x90;
		else if( (sr > 7300 ) && (sr <= 8200 ) ) byte_E = 0x92;
		else if( (sr > 8200 ) && (sr <= 9100 ) ) byte_E = 0x94;
		else if( (sr > 9100 ) && (sr <= 10000) ) byte_E = 0x96;
		else if( (sr > 10000) && (sr <= 11700) ) byte_E = 0x98;
		else if( (sr > 11700) && (sr <= 13300) ) byte_E = 0x9A;
		else if( (sr > 13300) && (sr <= 15000) ) byte_E = 0x9C;
		else if( (sr > 15000) && (sr <= 16700) ) byte_E = 0x9E;
		else if( (sr > 16700) && (sr <= 18300) ) byte_E = 0xA0;
		else if( (sr > 18300) && (sr <= 20000) ) byte_E = 0xA2;
	    else if( (sr > 20000) && (sr <= 21700) ) byte_E = 0xA4;
	    else if( (sr > 21700) && (sr <= 23300) ) byte_E = 0xA6;
	    else if( (sr > 23300) && (sr <= 25000) ) byte_E = 0xA8;
	    else if( (sr > 25000) && (sr <= 26700) ) byte_E = 0xAA;
	    else if( (sr > 26700) && (sr <= 28300) ) byte_E = 0xAC;
	    else if( (sr > 28300) && (sr <= 30000) ) byte_E = 0xAE;
	    else if( (sr > 30000) && (sr <= 31700) ) byte_E = 0xB0;
	    else if( (sr > 31700) && (sr <= 33300) ) byte_E = 0xB2;
	    else if( (sr > 33300) && (sr <= 35000) ) byte_E = 0xB4;
	    else if( (sr > 35000) && (sr <= 36700) ) byte_E = 0xB6;
	    else if( (sr > 36700) && (sr <= 38300) ) byte_E = 0xB8;
	    else if( (sr > 38300) && (sr <= 40000) ) byte_E = 0xBA;
	    else if( (sr > 40000) && (sr <= 41700) ) byte_E = 0xBC;
	    else if( (sr > 41700) && (sr <= 43300) ) byte_E = 0xBE;
	    else if( (sr > 43300) && (sr <= 45000) ) byte_E = 0xC0;
	    else printf("ERROR : symbol rate is Illegal.\n");
		
 	} else {
		printf("ERROR : selected mode is Illegal.\n");
 	}
 	
    return (byte_E);

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
    iic_write(id, subadr, &val, 1);
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
static INT16 iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len){

    switch( (BLOCKID)id ) {
        
        case SAT_1ST_TUNER:
            write_tuner( SLAVE_1ST_ADDRESS, subadr, data, len );
            break;
        default :
            break;
    }
    return 0;
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
        bRet &= sut_re23x_dependency_func_obj.i2c_write((MS_U8)slv, &subadr, 1, (MS_U8*)data, (MS_U16)len);

    //printf("[i2c_write]%x, %x,%x, %d\n", slv,subadr, data[0], bRet);

    if(bRet == 0) 
        printf("[Error]i2c write error, %s, %s(),%d\n", __FILE__,__FUNCTION__, __LINE__);

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

    /*------------------------------------------------
        Add code for wait ( milliseconds unit )
    ------------------------------------------------*/
    sut_re23x_dependency_func_obj.MAPI_delay(ms);
    return;
}

// return 0: fail, 1: ok.
UINT8 mdev_Tunerfunc_SUT(const pS_SUT_RE23x_dependency_func pobj)
{
    UINT8 bRet = 1;
 
    sut_re23x_dependency_func_obj.i2c_read = pobj->i2c_read;
    sut_re23x_dependency_func_obj.i2c_write = pobj->i2c_write;
    sut_re23x_dependency_func_obj.MAPI_delay = pobj->MAPI_delay;
    sut_re23x_dependency_func_obj.hw_rst_control = pobj->hw_rst_control;
    
    return bRet;
}

// return 0: fail, 1: ok.
UINT8 mdev_TunerInit_SUT(void)
{

    UINT8 bRet = 1;

    /* tuner reset  */ 
    if (sut_re23x_dependency_func_obj.MAPI_delay == NULL)
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
 #if 0   
    /* tuner i2c address  */
    tuner_block_id = SAT_1ST_TUNER;
    
    param_table = (sony_ascot3_adjust_param_t*)g_param_table_Rx23x;
#endif    
    /* tuner init  */
    // bRet &= terr_tuner_init();
    if (cmd_init() == 0)
        bRet &= 1;
    else 
        bRet &= 0;
    waitms(10);
    return bRet;
}
#if 0
UINT8 mdev_Tuner_read_rssi(float* float_rssi)    
{
    if (cmd_getrssi(float_rssi) == 0)
        return 1;
    else 
        return 0;
}
#endif
void mdev_Tuner_sleep_mode(void)
{
   x_fin();
}
/******************************************************************************
 * History
 *
 * 2013-03-19 v0.10  initial
 *
 ******************************************************************************/
