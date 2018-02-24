/******************************************************************************
 *   $ Copyright $ Sony Corporation
 *-----------------------------------------------------------------------------
 *   File Name   : $File: sut_pex41_sat.c $
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

/*************************************************
 Block ID definition for I2C access
**************************************************/
typedef enum {
    SAT_1ST_TUNER,   /* Tag for Main Tuner Block           */
    SAT_2ND_TUNER,   /* Tag for Sub Tuner Block            */
} SAT_BLOCKID;

typedef enum {
    SONY_HORUS_SAT_SYSTEM_UNKNOWN,
    SONY_HORUS_SAT_SYSTEM_DVBS,      /* DVB-S */
    SONY_HORUS_SAT_SYSTEM_DVBS2      /* DVB-S2 */
} SAT_RECEIVE_MODE;

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
static SAT_BLOCKID sat_tuner_block_id;

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

static INT16 Sat_iic_write_val(INT16 id, UINT8 subadr, UINT8 val);
static INT16 Sat_iic_read_val(INT16 id, UINT8 subadr, UINT8* val);
static INT16 Sat_iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len);
static INT16 Sat_iic_read(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len);

static INT16 Sat_write_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
);

static INT16 Sat_read_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
);

/*************************************************
 Wait
**************************************************/
static void Sat_waitms(UINT32 ms);

/*************************************************
 Tuning Sequece
**************************************************/
static void Sat_x_pon(void);                                                /* tuner: Initialize        */
static void Sat_x_tune(UINT32 frequency, SAT_RECEIVE_MODE mode, UINT32 symbolrate);/* tuner: tune              */
static void Sat_x_fin(void);                                                /* tuner: sleep             */

//static void Sat_tuner_gpio(UINT8 val);
static int  Sat_tuner_count(void);

//static void Sat_x_read_agc(UINT8* ifagcreg , UINT8* rfagcreg);
//static INT16 Sat_tuner_calcRSSI(UINT8 ifagcreg , UINT8 rfagcreg);


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
static void Sat_x_pon(void)
{

    UINT8 t_addr;
    UINT8 t_data[3];
    UINT8 data_length;

    DBG_PRINT("Enter x_pon()...\n");

    sat_tuner_block_id = SAT_1ST_TUNER;

    t_addr    = 0x41;
    t_data[0] = 0x07;
    t_data[1] = 0x00;
    t_data[2] = 0x05;
    data_length = 3;
    Sat_iic_write( sat_tuner_block_id, t_addr , t_data, data_length );

    Sat_iic_write_val( sat_tuner_block_id, 0x0C, 0x14 );

    DBG_PRINT(" Done. \n");
    
    return;
}


/******************************************************************************
 * x_tune
 *-----------------------------------------------------------------------------
 * Input        : frequency , mode , symbolrate
 * Output       : none
 * Return       : none
 * Description  : 
 *****************************************************************************/
static void Sat_x_tune(UINT32 frequency, SAT_RECEIVE_MODE mode, UINT32 sr)
{

    UINT8 t_addr;
    UINT8 t_data[6];
    UINT8 data_length;
    UINT8 rate;
//    UINT32 a;
    UINT8 numofTuner;

    DBG_PRINT("Enter x_tune()...");

    numofTuner = Sat_tuner_count();
    
    Sat_iic_write_val( sat_tuner_block_id, 0x15, 0x12 );    

    if(numofTuner == 1){
        Sat_iic_write_val( sat_tuner_block_id, 0x43, 0x06 );
    } else {
        Sat_iic_write_val( sat_tuner_block_id, 0x43, 0x04 );
    }

    Sat_iic_write_val( sat_tuner_block_id, 0x75, 0x99 );
    Sat_iic_write_val( sat_tuner_block_id, 0x9D, 0x00 );
    Sat_iic_write_val( sat_tuner_block_id, 0x01, 0x01 );
    
    t_addr    = 0x04;
    t_data[0] = 0xC4;
    t_data[1] = 0x40;
    data_length = 2;
    Sat_iic_write( sat_tuner_block_id, t_addr, t_data, data_length );
    
    t_addr    = 0x06;
    t_data[0] = 0x02;
    t_data[1] = 0x00; // External LPF
    t_data[2] = 0x20; // FreeSatMode 
    t_data[3] = 0x78;
    t_data[4] = 0x08;
    t_data[5] = 0x30;
    data_length = 6;
    Sat_iic_write( sat_tuner_block_id, t_addr, t_data, data_length );    
    
     if(mode == SONY_HORUS_SAT_SYSTEM_DVBS) {
        if(                       sr <= 4300   ) rate = 0x05;
        else if( (sr > 4300 ) && (sr <= 5100 ) ) rate = 0x06;
        else if( (sr > 5100 ) && (sr <= 6000 ) ) rate = 0x07;
        else if( (sr > 6000 ) && (sr <= 6800 ) ) rate = 0x08;
        else if( (sr > 6800 ) && (sr <= 7700 ) ) rate = 0x09;
        else if( (sr > 7700 ) && (sr <= 8500 ) ) rate = 0x0a;
        else if( (sr > 8500 ) && (sr <= 9400 ) ) rate = 0x0b;
        else if( (sr > 9400 ) && (sr <= 10400) ) rate = 0x0c;
        else if( (sr > 10400) && (sr <= 11900) ) rate = 0x0d;
        else if( (sr > 11900) && (sr <= 13300) ) rate = 0x0e;
        else if( (sr > 13300) && (sr <= 14800) ) rate = 0x0f;
        else if( (sr > 14800) && (sr <= 16300) ) rate = 0x10;
        else if( (sr > 16300) && (sr <= 17800) ) rate = 0x11;
        else if( (sr > 17800) && (sr <= 19300) ) rate = 0x12;
        else if( (sr > 19300) && (sr <= 20700) ) rate = 0x13;
        else if( (sr > 20700) && (sr <= 22200) ) rate = 0x14;
        else if( (sr > 22200) && (sr <= 23700) ) rate = 0x15;
        else if( (sr > 23700) && (sr <= 25200) ) rate = 0x16;
        else if( (sr > 25200) && (sr <= 26700) ) rate = 0x17;
        else if( (sr > 26700) && (sr <= 28100) ) rate = 0x18;
        else if( (sr > 28100) && (sr <= 29600) ) rate = 0x19;
        else if( (sr > 29600) && (sr <= 31100) ) rate = 0x1a;
        else if( (sr > 31100) && (sr <= 32600) ) rate = 0x1b;
        else if( (sr > 32600) && (sr <= 34100) ) rate = 0x1c;
        else if( (sr > 34100) && (sr <= 35600) ) rate = 0x1d;
        else if( (sr > 35600) && (sr <= 37000) ) rate = 0x1e;
        else if( (sr > 37000) && (sr <= 38500) ) rate = 0x1f;
        else if( (sr > 38500) && (sr <= 40000) ) rate = 0x20;
        else if( (sr > 40000) && (sr <= 41500) ) rate = 0x21;
        else if( (sr > 41500) && (sr <= 43000) ) rate = 0x22;
        else if( (sr > 43000) && (sr <= 44400) ) rate = 0x23;
        else if( (sr > 44400) && (sr <= 45000) ) rate = 0x24;
        else printf("ERROR : symbol rate is Illegal.\n");
        
     } else if(mode == SONY_HORUS_SAT_SYSTEM_DVBS2) {
        if(                       sr <= 4500   ) rate = 0x05;
        else if( (sr > 4500 ) && (sr <= 5500 ) ) rate = 0x06;
        else if( (sr > 5500 ) && (sr <= 6400 ) ) rate = 0x07;
        else if( (sr > 6400 ) && (sr <= 7300 ) ) rate = 0x08;
        else if( (sr > 7300 ) && (sr <= 8200 ) ) rate = 0x09;
        else if( (sr > 8200 ) && (sr <= 9100 ) ) rate = 0x0a;
        else if( (sr > 9100 ) && (sr <= 10000) ) rate = 0x0b;
        else if( (sr > 10000) && (sr <= 11700) ) rate = 0x0c;
        else if( (sr > 11700) && (sr <= 13300) ) rate = 0x0d;
        else if( (sr > 13300) && (sr <= 15000) ) rate = 0x0e;
        else if( (sr > 15000) && (sr <= 16700) ) rate = 0x0f;
        else if( (sr > 16700) && (sr <= 18300) ) rate = 0x10;
        else if( (sr > 18300) && (sr <= 20000) ) rate = 0x11;
        else if( (sr > 20000) && (sr <= 21700) ) rate = 0x12;
        else if( (sr > 21700) && (sr <= 23300) ) rate = 0x13;
        else if( (sr > 23300) && (sr <= 25000) ) rate = 0x14;
        else if( (sr > 25000) && (sr <= 26700) ) rate = 0x15;
        else if( (sr > 26700) && (sr <= 28300) ) rate = 0x16;
        else if( (sr > 28300) && (sr <= 30000) ) rate = 0x17;
        else if( (sr > 30000) && (sr <= 31700) ) rate = 0x18;
        else if( (sr > 31700) && (sr <= 33300) ) rate = 0x19;
        else if( (sr > 33300) && (sr <= 35000) ) rate = 0x1a;
        else if( (sr > 35000) && (sr <= 36700) ) rate = 0x1b;
        else if( (sr > 36700) && (sr <= 38300) ) rate = 0x1c;
        else if( (sr > 38300) && (sr <= 40000) ) rate = 0x1d;
        else if( (sr > 40000) && (sr <= 41700) ) rate = 0x1e;
        else if( (sr > 41700) && (sr <= 43300) ) rate = 0x1f;
        else if( (sr > 43300) && (sr <= 45000) ) rate = 0x20;
        else printf("ERROR : symbol rate is Illegal.\n");    
     }    	
	
    t_addr    = 0x0C;
    if(numofTuner == 1 ){
        t_data[0] = 0xFF; //LNA ON
    }else{
        t_data[0] = 0xFE; //LNA Thru
    }
    t_data[1] = 0x02;
    t_data[2] = 0x1E;
	t_data[3] = rate;
    data_length = 4;
    Sat_iic_write( sat_tuner_block_id, t_addr, t_data, data_length );

    t_addr    = 0x10;
    t_data[0] = ((( frequency >> 2 ) & 0x0000ff));
    t_data[1] = ((( frequency >> 2 ) & 0x00ff00) >>  8);
    t_data[2] = ((( frequency >> 2 ) & 0x0f0000) >> 16);
    t_data[3] = 0xFF;
    t_data[4] = 0x00;
    t_data[4] = 0x01;
    data_length = 6;
    Sat_iic_write( sat_tuner_block_id, t_addr , t_data, data_length );    

    Sat_waitms(10);

    Sat_iic_write_val( sat_tuner_block_id, 0x05, 0x00 );
    Sat_iic_write_val( sat_tuner_block_id, 0x04, 0xC0 );
        
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
static void Sat_x_fin(void)
{
    UINT8 t_addr;
    UINT8 t_data[3];
    UINT8 data_length;

    DBG_PRINT("Enter x_fin()...");
    
    Sat_iic_write_val( sat_tuner_block_id, 0x15, 0x12 );
    Sat_iic_write_val( sat_tuner_block_id, 0x43, 0x05 ); // force LNA OFF

    t_addr    = 0x0C;
    t_data[0] = 0x14;
    t_data[1] = 0x00;
    t_data[2] = 0x00;
    data_length = 3;
    Sat_iic_write( sat_tuner_block_id, t_addr, t_data, data_length );    
    
    Sat_iic_write_val( sat_tuner_block_id, 0x01, 0x00 );
    Sat_iic_write_val( sat_tuner_block_id, 0x05, 0x00 );
    Sat_iic_write_val( sat_tuner_block_id, 0x04, 0xC0 );
    
    DBG_PRINT(" Done. \n");

    return;
}
#if 0
/******************************************************************************
 * tuner_gpio
 *-----------------------------------------------------------------------------
 * Input        : UINT8 val
 * Output       : none
 * Return       : none
 * Description  : control GPIO.
 *****************************************************************************/
static void Sat_tuner_gpio(UINT8 val)
{
//    UINT8 t_addr;
//    UINT8 t_data[1];
//    UINT8 data_length;

    UINT8 tmp;

    DBG_PRINT("Enter tuner_gpio()...");

    if(val == 0){
        tmp = 0x00;
    }else {
        tmp = 0x01;
    }
    
    Sat_iic_write_val( SAT_2ND_TUNER, 0x02, tmp );

    DBG_PRINT(" Done. \n");

    return;
}
#endif
/******************************************************************************
 * tuner_count
 *-----------------------------------------------------------------------------
 * Input        : UINT8 val
 * Output       : none
 * Return       : none
 * Description  : control GPIO.
 *****************************************************************************/
static int Sat_tuner_count(void)
{
    UINT8 i;
    UINT8 val;

    Sat_iic_write_val( SAT_1ST_TUNER, 0x86, 0x10 );
    Sat_iic_read_val ( SAT_1ST_TUNER, 0x4b, &val );

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
static INT16 Sat_iic_write_val(INT16 id, UINT8 subadr, UINT8 val){
    Sat_iic_write(id, subadr, &val, 1);
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
static INT16 Sat_iic_read_val(INT16 id, UINT8 subadr, UINT8* val){
    Sat_iic_read(id, subadr, val, 1);
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
static INT16 Sat_iic_write(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len){

    switch( (SAT_BLOCKID)id ) {
        
        case SAT_1ST_TUNER:
            Sat_write_tuner( SLAVE_1ST_ADDRESS, subadr, data, len );
            break;
        case SAT_2ND_TUNER:
            Sat_write_tuner( SLAVE_2ND_ADDRESS, subadr, data, len );
            break;
        default :
            break;
    }
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
static INT16 Sat_iic_read(INT16 id, UINT8 subadr, UINT8 *data, UINT8 len){

    switch( (SAT_BLOCKID)id ) {
        
        case SAT_1ST_TUNER:
            Sat_read_tuner( SLAVE_1ST_ADDRESS, subadr, data, len );
            break;
        case SAT_2ND_TUNER:
            Sat_read_tuner( SLAVE_2ND_ADDRESS, subadr, data, len );
            break;
        default :
            break;
    }
    return 0;
}

#define SONY_SUT_RE23x_I2C_ADDR_sat (((UINT16)TUNER_IIC_BUS<<8)|0xC0 )
/******************************************************************************
 * write_tuner
 *****************************************************************************/
static INT16 Sat_write_tuner(
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
    
    if(MDrv_IIC_WriteBytes(SONY_SUT_RE23x_I2C_ADDR_sat, 0, NULL,  len + 1, buffer) == FALSE)
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

static INT16 Sat_read_tuner(
    UINT8 slv,
    UINT8 subadr,
    UINT8 *data,
    UINT8 len
) {
    UNUSED (slv);

    if(MDrv_IIC_ReadBytes(SONY_SUT_RE23x_I2C_ADDR_sat, 1, &subadr, len, data) == FALSE)
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
static void Sat_waitms(UINT32 ms) {
    
        /*------------------------------------------------
            Add code for wait ( milliseconds unit )
        ------------------------------------------------*/
    MsOS_DelayTask(ms);
    return;
}

/******************************************************************************
 * History
 *
 * 2014-04-21 v1.0.0.0 initial  
 ******************************************************************************/
