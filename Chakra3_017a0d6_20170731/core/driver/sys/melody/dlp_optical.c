////////////////////////////////////////////////////////////////////////////////
//
// optical main
//
////////////////////////////////////////////////////////////////////////////////
#define _DLP_C_
#include "Board.h"
#include "Dlp_Optical.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"
#include "drvGPIO.h"
#include "datatype.h"
//#include "dsp_coef_data.h"
//#include "dsp_inst_data.h"
/* proto type declaration */
UC GetPRESETROMCommand(US wNum, UC *pbData);
UL GetDSPWordSize(US wAdd);
UL GetDSPDataSize(US wAdd, US wSize);
UC CheckMDSPREQ(void);

UL uErrorI2CCount;

void LoopWait(UL dwWait);
static  U8 dpp2600_cmt_lut_load(U8 color);
static  U8 dpp2600_seq_lut_load(U8 table_number);
static  U32  read_dpp2600_i2c(U16 u16BusNumSlaveID, U8 u8addr);
static void WaitDelay(U16 cnt);
//#define I2C_NO_ACK                 0
static void WaitDelay(U16 cnt)//lcqadd for delay 1ms
{
	UINT volatile k;
	UINT i,j;
	for(i=cnt;i>0;i--)
  	{
  		for(j=26810;j>0;j--)
  		{
  	        k++;
  		}
  	}
}
/****************************************************
 * init optical pre
 *
 
 * 
******************************************************/
void PreInitOptical(void)
{
	BlankONOFF=TRUE;
}

//<<gchen @ 20170811 //opt dead if dead then is high		
int Opt3435_deadpin_get_level(void)
{
   return mdrv_gpio_get_level(OPE_3435_DEAD_PIN) ? _HIGH : _LOW;
}
//>>gchen @ 20170811 //opt dead if dead then is high	
/****************************************************
 * init optical main function
 *
 * @param   addr          - I 
 * @param   subaddr       - I 
 * @param   index          - I -
 * @param   verify          -
******************************************************/
void OpticalMain(void)
{
   printf("***************OPTICAL INIT **************\n");
//	PWR_EN_ON();
#if 0
	WaitDelay(100); 
	//start initialize MPE1601_GIO      
	write_i2c_1byte(MPE1601_DEV_ADDR, SYS_CTRL, 0x08);         //EN_GPIO, others are default 0
	write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_DIR_LSB, 0xE7); //bit 3 and bit 4 are input, others are output
	write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_DIR_MSB, 0xFE); //GPIO8 is input, others are output  

	//power on EPE 1.8V    
	write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, EN_1V8_EPE);   

	WaitDelay(100);    
	//delay_ms(100);
	//power on EPE 1.0V 
	write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, EN_1V8_EPE | EN_1V0_EPE);
	WaitDelay(200);   
	//delay_ms(200);
	//power on EPE 3.3V 
	write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, EN_1V8_EPE | EN_1V0_EPE |EN_3V3_EPE);  
	//write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_MSB, FAN_EN); 
		  
	//set PWR_GOOD to DPP2605
	write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, EN_1V8_EPE | EN_1V0_EPE |EN_3V3_EPE | PWR_GOOD);

	WaitDelay(100); 
	//delay_ms(200);
   //reset DPP2605
   write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, EN_1V8_EPE | EN_1V0_EPE |EN_3V3_EPE | PWR_GOOD |EMU_RST_Z);
		
	WaitDelay(600); 

	dpp2600_main_configure();
	
	dpp2600_config_rgb();  
#endif	

}
/****************************************************
 * Write 1 bytes data to the DPP
 *
 * @param   addr          - I - 8 Bit device  Address
 * @param   subaddr       - I - 8 Bit device Sub Address
 * @param   index          - I - data to be written to slave
 * @param   verify          - I
 * 
 * @return  PASS - Completed successfully
 * ERROR - Slave NAck'ed  or read data is not same as write data
******************************************************/
BOOLEAN write_i2c_1byte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 u8Data)
{
 return( MDrv_IIC_WriteBytes(u16BusNumSlaveID, 1, &u8RegAddr, 1, &u8Data) );
}
/****************************************************
 * Write 4 bytes data to the DPP
 *
 * @param   addr          - I - 8 Bit device  Address
 * @param   subaddr       - I - 8 Bit device Sub Address
 * @param   index          - I - data to be written to slave
 * @param   verify          - I
 * 
 * @return  PASS - Completed successfully
 * ERROR - Slave NAck'ed  or read data is not same as write data
******************************************************/
BOOLEAN MDrv_IIC_Write4_Bytes(U16 u16BusNumSlaveID, U8 u8addr, U32 data)
{
    U8 u8Data[4];
    u8Data[0] = (data>>24) & 0xFF;
    u8Data[1] = (data>>16) & 0xFF;
    u8Data[2] = (data>>8) & 0xFF;
    u8Data[3] = (data) & 0xFF;
    return (MDrv_IIC_WriteBytes(u16BusNumSlaveID, 1, &u8addr, 4, u8Data));
}

/****************************************************
 * Write 4 bytes data to the DPP
 *
 * @param   addr          - I - 8 Bit device  Address
 * @param   subaddr       - I - 8 Bit device Sub Address
 * @param   index          - I - data to be written to slave
 * @param   verify          - I
 * 
 * @return  PASS - Completed successfully
 * ERROR - Slave NAck'ed  or read data is not same as write data
******************************************************/
void write_dpp2600_i2c(U16 u16BusNumSlaveID, U8 u8addr, U32 data, U8 verify)
{
	U32 read_data;
	U8 u8Data[4];
    u8Data[0] =(U8) (data>>24) ;
    u8Data[1] =(U8) (data>>16) ;
    u8Data[2] =(U8)(data>>8) ;
    u8Data[3] =(U8) (data) ;
    MDrv_IIC_WriteBytes(u16BusNumSlaveID, 1, &u8addr, 4, u8Data);
    //MDrv_IIC_Write4_Bytes( u16BusNumSlaveID, u8addr, data);
  
   //verify=0;
 	if ( verify ) 
	{
    		read_data=read_dpp2600_i2c(u16BusNumSlaveID, u8addr);
    		if ( read_data != data ) 
		{
		 	printf("\n--we read 2600 data is =%lx-----\n",read_data);
      			printf("\n--we send 2600 data is =%lx-----\n",data);
		
    		}
  	}
}
/****************************************************
 * read 4 bytes data to the DPP
 *
 * @param   addr          - I - 8 Bit device  Address
 * @param   subaddr       - I - 8 Bit device Sub Address
 * @param   index          - I - data to be written to slave
 * @param   verify          - I
 * 
 * @return  PASS - Completed successfully
 * ERROR - Slave NAck'ed  or read data is not same as write data
******************************************************/
U32  read_dpp2600_i2c(U16 u16BusNumSlaveID, U8 u8addr)
{
  	U8 u8Data[4];
	U32 U32data;
	bool status;
	U8 subreadadd;
	subreadadd = (U8) READ_REG_SELECT;
  	u8Data[0] =          u8addr;
  	//status = MDrv_IIC_ReadBytes(addr, i2c_array, 2, &num_written); 
  	status=MDrv_IIC_WriteBytes(u16BusNumSlaveID, 1, &subreadadd, 1, u8Data);
  	// flag an error if necessary
	if (status == FALSE) 
	{
     	printf("\n2600 Slave is not ack or write byte error when write add(READ!!!)\n");
    	return 0;
  	}
	
    status=MDrv_IIC_OPT_ReadBytes(u16BusNumSlaveID,  4, u8Data);
	if (status == FALSE) 
	{
     	printf("\n2600 Slave is not ack or write byte error when read data(READ!!!)\n");
    	return 0;
  	}
	//printf("\n--we read 2600 data is =0x%x%x%x%x-----\n",(u8Data[3]),(u8Data[2]),(u8Data[1]),(u8Data[0]));

    //return ( (((U16)u8Data[0])<<8)|u8Data[1] );
	U32data = ((U32)(u8Data[0]) & 0xff);
   	U32data <<= 8;
   	U32data |= ((U32)(u8Data[1]) & 0xff);
	U32data <<= 8;
   	U32data |= ((U32)(u8Data[2]) & 0xff);
	U32data <<= 8;
	U32data |= ((U32)(u8Data[3]) & 0xff);
	//printf("\n--we read 2600 data is =%lx-----\n",U32data);
  	return U32data;
	#if 0
   	// setup the readback
  	i2c_array[0] = (uint08) READ_REG_SELECT;
  	i2c_array[1] =          subaddr;
  	status = i2c_master_polled_write(addr, i2c_array, 2, &num_written); 
  
  	// flag an error if necessary
	if ( (status == I2C_NO_ACK ) || num_written != 2 ) 
	{
    // 	Puts("\n2600 Slave is not ack or write byte error when write add(READ!!!)\n");
    	*index = 0;
    	return;
  	}
    
  	// perform the read
  	status = i2c_master_polled_read(addr, i2c_array, 4, &num_read); 
  
  	// flag an error if necessary
  	if ( (status == I2C_NO_ACK ) || num_read != 4 )
	{
	//	Puts("\n2600 Slave is not ack or read byte error when read data(READ!!!)\n");	
    	*index = 0;
    	return;
  	}
    // concatenate the bytes to make a word
  	//  *index = (uint32)i2c_array[0]<<24 | (uint32)i2c_array[1]<<16 | i2c_array[2]<<8 | i2c_array[3];
    *index = ((uint32)(i2c_array[0]) & 0xff);
    *index <<= 8;
    *index |= ((uint32)(i2c_array[1]) & 0xff);
    *index <<= 8;
    *index |= ((uint32)(i2c_array[2]) & 0xff);
    *index <<= 8;
    *index |= ((uint32)(i2c_array[3]) & 0xff);
	//Printf("\n--the read data and what we just sent is defferent222==%lx-----\n",index);
	#endif
}



//extern uint08 tpg_select;
//extern uint08 splash_image_select;
//extern DATA  BYTE  tic01;
/*************************************************************
 * Common DPP2600 setup for all input types. This must be executed first
 * before attempting to display an image.
 *
 * @return  none
 *
 *************************************************************/
void dpp2600_main_configure(void)
{
	  // write the software version number to a spare register field
	 //write_dpp2600_i2c(DPP2600_DEV_ADDR, MISC_REG, 6, 1);    //wht del
	  
	  // Sequencer registers
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, SEQ_CONTROL, 0, 1);
	  //write_dpp2600_i2c(DPP2600_DEV_ADDR, SEQ_VECTOR, 0x100, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, SEQ_VECTOR, 0, 1);
	  
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, DMD_BLOCK_COUNT, 7, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, DMD_VCC_CONTROL, 0x109, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, DMD_PARK_PULSE_COUNT, 0xA, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, DMD_PARK_PULSE_WIDTH, 0xB, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, DMD_PARK_DELAY, 0x2ED, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, DMD_SHADOW_ENABLE, 0, 1);
	  
	  // serial flash common config
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, FLASH_OPCODE, 0xB, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, FLASH_DUMMY_BYTES, 1, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, FLASH_ADDR_BYTES, 3, 1);

		  // CMT look-up tables
		 // dpp2600_cmt_lut_load(CMT_LUT_GREEN);
		  //dpp2600_cmt_lut_load(CMT_LUT_RED);
		 // dpp2600_cmt_lut_load(CMT_LUT_BLUE);
#ifdef D_PICTURE_MODE_DEFINE                       //此处后续还要更改
	//dpp2600_cmt_lut_load(SEQ_CMT_LUT_5);    //wht10.10.20_2

	// SEQ and DRC look-up tables
	//dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);
	dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
	call_dpp2600_seq(1,5,1);
#else
		  dpp2600_cmt_lut_load(CMT_LUT_ALL);
	  
	  // SEQ and DRC look-up tables
	  dpp2600_seq_lut_load(SEQ_SEQ_LUT);
	  dpp2600_seq_lut_load(SEQ_DRC_LUT_ALL);
#endif

	  
	  // frame buffer memory controller enable
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, SDC_ENABLE, 1, 1);
	  
	  // AGC control
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, AGC_CTRL, 7, 1);
	  
	  // main datapath setup
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, CPU_IF_MODE, 1, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, LONG_FLIP, 1, 1);
	  //write_dpp2600_i2c(DPP2600_DEV_ADDR, SHORT_FLIP, 1, 1);
	  write_dpp2600_i2c(DPP2600_DEV_ADDR, CURTAIN_CONTROL, 0, 1);
	  
	   // LED PWM and enables
		//SetOpticalPower(1);//change by gchen @ 20110427 //change power to 2A then SetOpticalPower(0)
		write_dpp2600_i2c(DPP2600_DEV_ADDR, R_DRIVE_CURRENT, 0X299, 1);
  		write_dpp2600_i2c(DPP2600_DEV_ADDR, G_DRIVE_CURRENT, 0X299, 1);
  		write_dpp2600_i2c(DPP2600_DEV_ADDR, B_DRIVE_CURRENT, 0X299, 1);
	  	write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 7, 1); 
	  //dpp2600_config_blank(ON);
}

/****************************************************************************************************
* Function	: dpp2600_cmt_lut_load
*
* Input		:  color:color table to load (red green blue or all)
 *			: 			
*
* Output		:  none
*			 
*
* Return		: 0 - no errors
*                 : 1 - invalid color specified
*
* Description	: Look-up table loading of CMT
*  	
****************************************************************************************************/
static  U8 dpp2600_cmt_lut_load(U8 color)
{
	U32 address, size;
    U8 lut_destination;
	switch (color) 
	{
#ifdef D_PICTURE_MODE_DEFINE
		case 0:	address = CMT_LUT_0_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_0_SIZE;	break;
		
		case 1:	address = CMT_LUT_1_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_1_SIZE;	break;
		
		case 2:	address = CMT_LUT_2_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_2_SIZE;	break;
		
		case 3:	address = CMT_LUT_3_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_3_SIZE;	break;
		
		case 4:	address = CMT_LUT_4_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_4_SIZE;	break;
		
		case 5:	address = CMT_LUT_5_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_5_SIZE;	break;
		
		case 6:	address = CMT_LUT_6_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_6_SIZE;	break;
		
		case 7:	address = CMT_LUT_7_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_7_SIZE;	break;
		
		case 8:	address = CMT_LUT_8_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_8_SIZE;	break;
		
		case 9:	address = CMT_LUT_9_START_ADDR;		lut_destination = CMT_LUT_ALL;	size = CMT_LUT_9_SIZE;	break;
		
		case 10:	address = CMT_LUT_10_START_ADDR; 	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_10_SIZE;	break;
		
		case 11:	address = CMT_LUT_11_START_ADDR; 	lut_destination = CMT_LUT_ALL; size = CMT_LUT_11_SIZE;	break;

		case 12:	address = CMT_LUT_12_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_12_SIZE;	break;
		
		case 13:	address = CMT_LUT_13_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_13_SIZE;	break;
		
		case 14:	address = CMT_LUT_14_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_14_SIZE;	break;
		
		case 15:	address = CMT_LUT_15_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_15_SIZE;	break;
		
		case 16:	address = CMT_LUT_16_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_16_SIZE;	break;
		
		case 17:	address = CMT_LUT_17_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_17_SIZE;	break;
		
		case 18:	address = CMT_LUT_18_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_18_SIZE;	break;
		
		case 19:	address = CMT_LUT_19_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_19_SIZE;	break;
		
		case 20:	address = CMT_LUT_20_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_20_SIZE;	break;
		
		case 21:	address = CMT_LUT_21_START_ADDR;	lut_destination = CMT_LUT_ALL;	size = CMT_LUT_21_SIZE;	break;
		
		case 22:	address = CMT_LUT_22_START_ADDR;	 lut_destination = CMT_LUT_ALL;	size = CMT_LUT_22_SIZE;	break;
		
		case 23:	address = CMT_LUT_23_START_ADDR; 	lut_destination = CMT_LUT_ALL; size = CMT_LUT_23_SIZE;	break;
	#else
		case 1:
			//address = CMT_GRN_LUT_0_START_ADDR;
			address = CMT_LUT_0_START_ADDR;
			lut_destination = CMT_LUT_GREEN;
			size = CMT_LUT_0_SIZE;
			break;
		case 2:
			//address = CMT_RED_LUT_0_START_ADDR;
			address = CMT_LUT_0_START_ADDR+512;
			lut_destination = CMT_LUT_RED;
			size = CMT_LUT_1_SIZE;
			break;
		case 3:
			//address = CMT_BLU_LUT_0_START_ADDR;
			address = CMT_LUT_0_START_ADDR+1024;
			lut_destination = CMT_LUT_BLUE;
			size = CMT_LUT_2_SIZE;
			break;
		case 4:
			address = CMT_LUT_0_START_ADDR;
			lut_destination = CMT_LUT_ALL;
			size = CMT_LUT_0_SIZE;
			break;
#endif
		default:
			address = CMT_LUT_0_START_ADDR;
			lut_destination = CMT_LUT_ALL;
			size = CMT_LUT_0_SIZE;
			return 1;
	};

	// configure DMA from flash to LUT

	dpp2600_flash_dma(address, size, 1, lut_destination);

	return 0;
}
/****************************************************************************************************
* Function	: dpp2600_seq_lut_load
*
* Input		:  table_number - I - sequence or DRC table to load
 *			: 			
*
* Output		:  none
*			 
*
* Return		: 0 - no errors
*                 : 1 - invalid table_number specified
*
* Description	: Look-up table loading of sequence or DRC data
*  	
****************************************************************************************************/
static  U8 dpp2600_seq_lut_load(U8 table_number)
{
	U32 address;
	U32 size = DRC_TABLE_0_SIZE;
    U8 lut_destination;
	  
	switch (table_number) 
	{
#ifdef D_PICTURE_MODE_DEFINE
		case 0: 	address = SEQUENCE_0_START_ADDR;  size = SEQUENCE_0_SIZE;	lut_destination = SEQ_SEQ_LUT;	break;
		
		case 1: 	address = SEQUENCE_1_START_ADDR;  size = SEQUENCE_1_SIZE;	lut_destination = SEQ_SEQ_LUT;	break;
		
		case 2: 	address = SEQUENCE_2_START_ADDR;  size = SEQUENCE_2_SIZE;	lut_destination = SEQ_SEQ_LUT;	break;
		
		case 3: 	address = SEQUENCE_3_START_ADDR;  size = SEQUENCE_3_SIZE;	lut_destination = SEQ_SEQ_LUT;	break;
		
		case 4: 	
		case 5: 			
		case 6: 			
		case 7: 			
		case 8: 			
		case 9: 			
		case 10: 		
		case 11: 		
		case 12: 		
		case 13: 		
		case 14:  address = SEQUENCE_0_START_ADDR;  size = SEQUENCE_0_SIZE;	lut_destination = SEQ_SEQ_LUT; break;	

		case 15: 	address = SEQUENCE_15_START_ADDR;  size = SEQUENCE_15_SIZE;	lut_destination = SEQ_SEQ_LUT;	break;
		
		case 24:	   	address = DRC_TABLE_0_START_ADDR;lut_destination = SEQ_DRC_LUT_ALL; 	break;
#else
		case 1:
			address = DRC_TABLE_0_START_ADDR;
			lut_destination = SEQ_DRC_LUT_0;
			break;
		case 2:
			address = DRC_TABLE_0_START_ADDR;
			lut_destination = SEQ_DRC_LUT_1;
			break;
		case 3:
			address = DRC_TABLE_0_START_ADDR;
			lut_destination = SEQ_DRC_LUT_2;
			break;
		case 4:
			address = DRC_TABLE_0_START_ADDR;
			lut_destination = SEQ_DRC_LUT_3;
			break;
		case 5:
			address = SEQUENCE_0_START_ADDR;
			size = SEQUENCE_0_SIZE;
			lut_destination = SEQ_SEQ_LUT;
			break;
		case 6:
			address = DRC_TABLE_0_START_ADDR;
			lut_destination = SEQ_DRC_LUT_ALL;
			break;
		case 7:
			address = 0x0; // TODO
			lut_destination = WPC_PROGRAM_LUT;
			break;
#endif
		default:
			return 1;
	};

	// configure DMA from flash to LUT

	dpp2600_flash_dma(address, size, 0, lut_destination);

	return 0;
}
/****************************************************************************************************
* Function	: shutdown
*
* Input		:  normal user generated shutdown      	- reason = NORMAL_SHUT_DOWN
 *				:  if LED high temperature             			- reason = LED_HIGH_TEMP_DOWN			
*
* Output		:  none
*			 
*
* Return		: none
*
* Description	: call this function when either a fault occurs or the user requests shutdown
*  	
****************************************************************************************************/
void Opticalshutdown(void)
{
	//U16 i;
#ifdef D_EVT_TWO
      U8 reg_data= 0xff;
#endif	  
	// turn off LEDs
	write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 0, 1);
	// park the DMD
	write_dpp2600_i2c(DPP2600_DEV_ADDR, DMD_PARK, 1, 0);  
#ifdef D_EVT_TWO
  	reg_data &= ~(PWR_GOOD | MOT_EN);
    write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, reg_data);
    WaitDelay(1500);
    reg_data &= ~(PWR_GOOD | MOT_EN | EN_3V3_EPE);
    write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, reg_data);    
    write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_MSB, 0); //to disabl fan
    // turn off EPE 1.0 V power supply
    WaitDelay(200);  
    reg_data &= ~(PWR_GOOD | MOT_EN | EN_3V3_EPE | EN_1V0_EPE);
    write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, reg_data); 
    // delay for power supply sequencing
    WaitDelay(100);
    reg_data &= ~(PWR_GOOD | MOT_EN | EN_3V3_EPE | EN_1V0_EPE |EN_1V8_EPE);
    // turn off EPE 1.8 V power supply
    write_i2c_1byte(MPE1601_DEV_ADDR, GPIO_SET_LSB, reg_data);  

#endif
	  // delay for power supply sequencing
	  WaitDelay(1000);
	  // turn off EPE 2.5 V power supply
	 PWR_EN_OFF();
	  
	  // delay for power supply sequencing
	 WaitDelay(100);
}
/////////////////////////////////////////////////////////////////////////////
// Function name		: setting optical LED power
// Purpose			: 
// Input Parameters	: none.
// Return type		: none.
// Output Parameters: none.
/////////////////////////////////////////////////////////////////////////////
void SetOpticalPower(BYTE power_mode)
{
	write_dpp2600_i2c(DPP2600_DEV_ADDR, R_DRIVE_CURRENT, ( 0==power_mode  ? R_LED_NORMAL_CURR  :  R_LED_SAVEMODE_CURR  ), 1);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, G_DRIVE_CURRENT, ( 0==power_mode  ? G_LED_NORMAL_CURR  :  G_LED_SAVEMODE_CURR  ), 1);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, B_DRIVE_CURRENT, ( 0==power_mode  ? B_LED_NORMAL_CURR  :  B_LED_SAVEMODE_CURR  ), 1);
}
#if ENABLE_HIGH_AND_LOW_LIGHT_SWITCH
/////////////////////////////////////////////////////////////////////////////
// Function name		: setting optical LED power
// Purpose			: 
// Input Parameters	: none.
// Return type		: none.
// Output Parameters: none.
/////////////////////////////////////////////////////////////////////////////
void SetOpticalPowermode(BYTE power_mode)
{
	BYTE i =0;
	BOOL hightlowbit=TRUE;
	U32 udata1[]={0x00000002,0x00000003};//{0x00000001,0x00000003};	
    U32 udata2[]={0x000000bc,0x00000084};//{0x000000b3,0x00000020};
	
	for(i=0;i<6;i++)
	{
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000003+i, 0);
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
		MsOS_DelayTask(10);
		if(hightlowbit)
		{
			write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, udata1[power_mode], 0);
			hightlowbit = FALSE;
		}
		else
		{
			write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, udata2[power_mode], 0);
			hightlowbit = TRUE;
		}
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);
		MsOS_DelayTask(10);
	}
#if 0
//设置红灯高位
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000003, 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
	MsOS_DelayTask(10);
	if(power_mode) //normal:0  savemode:1
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000001, 0);
	else
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000003, 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);
	MsOS_DelayTask(10);
//设置红灯低位
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000004, 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
	MsOS_DelayTask(10);
	if(power_mode) //normal:0  savemode:1
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x000000b3, 0);
	else
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000020, 0);	
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);
	MsOS_DelayTask(10);
//设置绿灯高位
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000005, 0);
MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
	MsOS_DelayTask(10);
	if(power_mode) //normal:0  savemode:1
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000001, 0);
	else
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000003, 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);
	MsOS_DelayTask(10);
//设置绿灯低位
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000006, 0);
MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
	MsOS_DelayTask(10);
	if(power_mode) //normal:0  savemode:1
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x000000b3, 0);
	else
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000020, 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);
	MsOS_DelayTask(10);
//设置蓝灯高位
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000007, 0);
MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
	MsOS_DelayTask(10);
	if(power_mode) //normal:0  savemode:1
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x000000b3, 0);
	else
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000020, 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);
	MsOS_DelayTask(10);
//设置蓝灯低位
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000008, 0);
MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
	MsOS_DelayTask(10);
	if(power_mode) //normal:0  savemode:1
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x000000b3, 0);
	else
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000020, 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
	MsOS_DelayTask(10);
	write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);	
	MsOS_DelayTask(10);
#endif
}
#endif
#if FIX_STARTUP_COLOR_DISTORTION
/////////////////////////////////////////////////////////////////////////////
// Function name		: setting optical LED power
// Purpose			: 
// Input Parameters	: none.
// Return type		: none.
// Output Parameters: none.
/////////////////////////////////////////////////////////////////////////////
void SetOpticalCurrent(U32 uCurrValue)
{
	BYTE i =0;
	BOOL hightlowbit=TRUE;
	U32 u8Data[2];	
    
	u8Data[0] = (U32)(uCurrValue >> 8);
	u8Data[1] = (U32)(uCurrValue & 0x000000ff);

	//printf("\nu8Data[0] = %4x\n",u8Data[0]);
	//printf("\nu8Data[1] = %4x\n",u8Data[1]);
	for(i=0;i<6;i++)
	{
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, 0x00000003+i, 0);
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d0, 0);
		MsOS_DelayTask(10);
		if(hightlowbit)
		{
			write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, u8Data[0], 0);
			hightlowbit = FALSE;
		}
		else
		{
			write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_DATA, u8Data[1], 0);
			hightlowbit = TRUE;
		}
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND_HANDSHAKE,0x00000001 , 0);
		MsOS_DelayTask(10);
		write_dpp2600_i2c(DPP2600_DEV_ADDR, ICP_COMMAND, 0x000000d2, 0);
		MsOS_DelayTask(10);
	}
}
#endif

#ifdef D_PICTURE_MODE_DEFINE
/****************************************************************************************************
* Function	: call_dpp2600_seq
*
* Input		:  none 
 *			: 			
*
* Output		:  none
*			 
*
* Return		: none
*
* Description	: Configure datapath for parallel RGB operation
*  	
****************************************************************************************************/
void call_dpp2600_seq(U8 power_mode, U8 picture_mode,BOOL feq_is_60)
{
    //dpp2600_config_blank(FALSE);//lcqdd optical 
     printf("\r\n optical freq ====== 0 %d",feq_is_60);
    switch(power_mode)
    {
        case 1:
		switch(picture_mode)
			{
				case 1:
			       if(feq_is_60)
			       {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_0); //CMT enhanced
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_6);  //CMT enhanced
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 2:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_1); //CMT 2.2
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_7);  //CMT 2.2
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 3:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_2); //CMT 2.5
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_8);  //CMT 2.5
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 4:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_3); //CMT linear
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_9);  //CMT linear
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 5:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_4); //CMT film
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_10);  //CMT film
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;	
				case 6:
			    	if(feq_is_60)
			       {
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_5); //CMT video
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_11);  //CMT video
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				default:
					break;
			}
	        break;
        
        case 2:
		switch(picture_mode)
			{
				case 1:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_12); //CMT enhanced
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_18);  //CMT enhanced
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 2:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_13); //CMT 2.2
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_19);  //CMT 2.2
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 3:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_14); //CMT 2.5
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_20);  //CMT 2.5
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 4:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_15); //CMT linear
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_21);  //CMT linear
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				case 5:
			            if(feq_is_60)
			            {
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_16); //CMT film
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
					//dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_22);  //CMT film
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;	
				case 6:
	            	if(feq_is_60)
	            	{
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_0);  //Seq 0
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_17); //CMT video
					//	dpp2600_seq_lut_load(SEQ_DRC_LUT_16); // DRC table
					}
					else //50Hz
					{
						dpp2600_seq_lut_load(SEQ_SEQ_LUT_1);  //Seq 1
						dpp2600_cmt_lut_load(SEQ_CMT_LUT_23);  //CMT video						
						//dpp2600_seq_lut_load(SEQ_DRC_LUT_16);
					}
					break;
				default:
					break;				
			}
	       break;
        
        default:
	        break;
    } 
	//write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 7, 1);
}
#endif
/**
 * Configure datapath for LUT (seq/CMT/SPlash) DMA
 *
 * @param   flash_address   - I - Data address in flash
 * @param   flash_num_bytes - I - Data size in flash
 * @param   CMT_SEQz        - I - select mailbox to load data to: 0=sequence/DRC, 1=CMT/splash/OSD
 * @param   table_number    - I - mailbox number to be loaded
 *
 * @return  0 - no errors
 *          1 - invalid flash address specified
 *          2 - invalid mailbox specified
 *          3 - invalid table_number / mailbox combination
 *
 */
U8 dpp2600_flash_dma(U32 flash_address, U32 flash_num_bytes, U8 CMT_SEQz, U8 table_number)
{
  U8 mailbox_address, mailbox_select;

  // check argument validity
  if ( flash_address > 0x1fffff )
    return 1;
  if ( CMT_SEQz > 1 )
    return 2;
#ifndef D_PICTURE_MODE_DEFINE
	if ( (CMT_SEQz == 0 && table_number > 6) ||(CMT_SEQz == 1 && table_number > 5) )
	{
    return 3;
	}
#endif

//  if ( (CMT_SEQz == 0 && table_number > 6) ||  (CMT_SEQz == 1 && table_number > 5) )
  //  return 3;
  
  // set mailbox parameters
	if ( CMT_SEQz ) 
	{
    mailbox_address = CMT_SPLASH_LUT_START_ADDR;
    mailbox_select = CMT_SPLASH_LUT_DEST_SELECT;
  	} else 
  	{
    mailbox_address = SEQ_RESET_LUT_START_ADDR;
    mailbox_select = SEQ_RESET_LUT_DEST_SELECT;
  }
  
  // configure DMA from flash to LUT
  write_dpp2600_i2c(DPP2600_DEV_ADDR, PBC_CONTROL, 0, 0);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, FLASH_START_ADDR, flash_address, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, FLASH_READ_BYTES, flash_num_bytes, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, mailbox_address, 0, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, mailbox_select, table_number, 1);
  // transfer control to flash controller
  write_dpp2600_i2c(DPP2600_DEV_ADDR, PBC_CONTROL, 1, 0);

  // check status of DMA transfer
  // read status until the transfer is complete
  DPP_WaitForDMA();

  // return register access to I2c  
 
  write_dpp2600_i2c(DPP2600_DEV_ADDR, PBC_CONTROL, 0, 0);

  // close LUT access
  write_dpp2600_i2c(DPP2600_DEV_ADDR, mailbox_select, 0, 1);
  
  // no errors
  return 0;
}
/*****************************************************************
 * Wait for DMA to complete
 * Note: This function call will not return until either DMA is complete or timeout
 *****************************************************************/
void DPP_WaitForDMA(void)
{
    U8   timer_diff;
    U32 dpp2600_status;
  	// check status of DMA transfer
  	// read status until the transfer is complete
  	timer_diff=0;
  	do 
	{
    	dpp2600_status=read_dpp2600_i2c(DPP2600_DEV_ADDR, MAIN_STATUS);
        	    
    	// break if we've waited for ~100ms
   		if ( timer_diff > 100 )
    	{
    		
    		printf("\n--Wait for DMA time out-----\n");  
			break;
    	}
		timer_diff++;
		WaitDelay(1);
  	} while ( (dpp2600_status & DMA_STATUS) == DMA_STATUS );

}
/****************************************
 * Configure datapath for parallel RGB operation
 *
 ***************************************/
void dpp2600_config_rgb(void)
{
  // enable video board output drivers
  write_dpp2600_i2c(DPP2600_DEV_ADDR, SEQ_CONTROL, 0, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, ACTGEN_CONTROL, 0x16, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, SEQUENCE_MODE, SEQ_LOCK, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, DATA_FORMAT, RGB888, 1);
  //write_dpp2600_i2c(DPP2600_DEV_ADDR, INPUT_RESOLUTION, WVGA_864_LANDSCAPE, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, INPUT_RESOLUTION, WVGA_854_LANDSCAPE, 1);
  write_dpp2600_i2c(DPP2600_DEV_ADDR, INPUT_SOURCE, PARALLEL_RGB, 1);
  // turn image back on
  write_dpp2600_i2c(DPP2600_DEV_ADDR, SEQ_CONTROL, 1, 1);
}

/***************************************
 *OPTICAL ON OFF
 *
************************************** */
 void dpp2600_config_blank(U8 OnOff)
{
	Optical_Led_Switch(OnOff);
}
void Optical_Led_Switch(U8 OnOff)
{
	if(OnOff)
   	{
		//write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, (OnOff ? 7:0), 1);
	 	write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 7, 1);
		printf("optical turn on!!!!!!!!!!\n");
   	}
	else
	{
	 	write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 0, 1);
		printf("optical turn off###########\n");
	}
}
void devOPE_set_Flip(U8 OnOff)
{
	switch(OnOff){
			case INVERSION:
				write_i2c_1byte(DPP2600_DEV_ADDR,B_DRIVE_CURRENT,0x00); 
				break;
			case INVERSION_MIRROR:
				write_i2c_1byte(DPP2600_DEV_ADDR,B_DRIVE_CURRENT,0x02 ); 
				break;
			case ORTHOGRAPHY_MIRROR:
				write_i2c_1byte(DPP2600_DEV_ADDR,B_DRIVE_CURRENT,0x04 ); 
				break;
			case ORTHOGRAPHY:
				write_i2c_1byte(DPP2600_DEV_ADDR,B_DRIVE_CURRENT,0x06 ); 
				break;
	}
}

//>>wht141107_1
void devOPE_Long_Axis_Flip(U8 OnOff)
{
	if(OnOff)
	{
		write_dpp2600_i2c(DPP2600_DEV_ADDR,LONG_FLIP,0x01 ,0); //MP333
		//MsOS_DelayTask(50);
	}
	else
	{
		write_dpp2600_i2c(DPP2600_DEV_ADDR,LONG_FLIP,0x00 ,0); //MP333
		//MsOS_DelayTask(50);
	}
}
/***************************************
 *Brilliant Color Control
 *
************************************** */
void devOPE_Short_Axis_Flip(U8 OnOff)
{
	if(OnOff)
	{
		write_dpp2600_i2c(DPP2600_DEV_ADDR,SHORT_FLIP,0x01 ,0); //MP333
		//MsOS_DelayTask(50);
	}
	else
	{
		write_dpp2600_i2c(DPP2600_DEV_ADDR,SHORT_FLIP,0x00 ,0); //MP333
		//MsOS_DelayTask(50);
	}
}
//<<wht141107_1
/***************************************
 *keystone correction
 *
************************************** */
void keystone_correction(S8 angle)
{

 printf("optical keystone_correction angle = %d !!!!!!!!!!\n", angle); 
  
 int iCurrent = angle*10 + 620;
 printf("optical keystone_correction iCurrent = %d !!!!!!!!!!\n", iCurrent); 
 //SetOpticalCurrent(iCurrent);

}
/***************************************
 *LED open and close
 *
************************************** */
void Optical_Led_OpenANDClose(U8 OnOff)
{
	if(OnOff)
   	{
	 	//write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 7, 1);
	 	//MDrv_IIC_WriteByte(DPP2600_DEV_ADDR, WRITE_3435_FREEZE, 0x01); //gchen
  		//MsOS_DelayTask(50);
		MDrv_IIC_WriteByte(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 7);
		//MsOS_DelayTask(50);
  		//MDrv_IIC_WriteByte(DPP2600_DEV_ADDR, WRITE_3435_FREEZE, 0x00); //gchen
  		
		printf("optical turn on!!!!!!!!!!\n");
   	}
	else
	{
	 	//write_dpp2600_i2c(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 0, 1);
	 	//MDrv_IIC_WriteByte(DPP2600_DEV_ADDR, WRITE_3435_FREEZE, 0x01); //gchen
  		//MsOS_DelayTask(50);
		MDrv_IIC_WriteByte(DPP2600_DEV_ADDR, RGB_DRIVER_ENABLE, 0);
		//MsOS_DelayTask(50);
  		//MDrv_IIC_WriteByte(DPP2600_DEV_ADDR, WRITE_3435_FREEZE, 0x00); //gchen
  		
		printf("optical turn off###########\n");
	}
}

//gchen check 3435 if is ok //20170914
bool Optical_LED_CheckStatus(void)
{
	bool bRet = false;
	U8 uGetData;
	bRet = MDrv_IIC_ReadByte(DPP2600_DEV_ADDR, 0x53, &uGetData);
	
	return bRet;
}

void Optical_SetRes_1280x800(void)
{
	printf("optical Optical_SetRes_1280x800!!!!!!!!!!\n");
	U8 u8Data[8];
	U8 subadd;
	subadd = (U8) WRITE_OPT_RES;
    u8Data[0] =(U8)0x00;
    u8Data[1] =(U8)0x00;
    u8Data[2] =(U8)0x00;
    u8Data[3] =(U8)0x00;
	u8Data[4] =(U8)0x00;
	u8Data[5] =(U8)0x05;
	u8Data[6] =(U8)0x20;
	u8Data[7] =(U8)0x03;
    MDrv_IIC_WriteBytes(DPP2600_DEV_ADDR, 1, &subadd, 8, u8Data);
}

void Optical_SetRes_854x480(void)
{
	printf("optical Optical_SetRes_854x480!!!!!!!!!!\n");
	U8 u8Data[8];
	U8 subadd;
	subadd = (U8) WRITE_OPT_RES;
    u8Data[0] =(U8)0x00;
    u8Data[1] =(U8)0x00;
    u8Data[2] =(U8)0x00;
    u8Data[3] =(U8)0x00;
	u8Data[4] =(U8)0x56;
	u8Data[5] =(U8)0x03;
	u8Data[6] =(U8)0xe0;
	u8Data[7] =(U8)0x01;
    MDrv_IIC_WriteBytes(DPP2600_DEV_ADDR, 1, &subadd, 8, u8Data);
}

void Optical_YangMing_InputSourceSelect(void)
{
	//MDrv_IIC_WriteByte(DPP2600_DEV_ADDR, WRITE_INPUT_SOURCE_SELECT, 0);
	
	U8 u8Data[4];
	U8 subadd;
	subadd = (U8) INPUT_SOURCE;
    u8Data[0] =(U8)0x00;
    u8Data[1] =(U8)0x00;
    u8Data[2] =(U8)0x00;
    u8Data[3] =(U8)0x00;
    MDrv_IIC_WriteBytes(DPP2600_DEV_ADDR, 1, &subadd, 4, u8Data);
}


void Optical_YangMing_RGBCurrent(void)
{
	U8 u8Data[6];
	U8 subadd;
	subadd = (U8) WRITE_RGB_CURRENT;
    u8Data[0] =(U8)0xb8;
    u8Data[1] =(U8)0x01;
    u8Data[2] =(U8)0xd6;
    u8Data[3] =(U8)0x01;
	u8Data[4] =(U8)0xae;
	u8Data[5] =(U8)0x01;
    MDrv_IIC_WriteBytes(DPP2600_DEV_ADDR, 1, &subadd, 6, u8Data);
}

void Optical_YangMing_KeyStoneCorrection_Control(void)
{
	U8 u8Data[5];
	U8 subadd;
	subadd = (U8) WRITE_KEYSTONE_CORRECTION_CONTROL;
    u8Data[0] =(U8)0x01;
    u8Data[1] =(U8)0x4c;
    u8Data[2] =(U8)0x01;
    u8Data[3] =(U8)0x00;
	u8Data[4] =(U8)0x01;
    MDrv_IIC_WriteBytes(DPP2600_DEV_ADDR, 1, &subadd, 5, u8Data);
}


void LoopWait(UL dwWait)
{
	UL i;
	
	/* 
		The "for" sentence processing takes approximately 12 clocks (=500 nsec).
		Doubled "dwWait" is 1 microsecond.
	*/
	dwWait *= 2;
	
	for(i = 0; i < dwWait; i++);
}

/* **************************************************** */
/* GetPRESETROMCommand									*/
/*		parameter:										*/
/*			unsigned short		wNum					*/
/*								(ROM block number)		*/
/*														*/
/*			*unsigned char		pbCommand				*/
/*								(command code)			*/
/*														*/
/*		return value:									*/
/*			unsigned char		processing result		*/
/*														*/
/*		description:									*/
/*			obtain PRESETROM command. 					*/
/* **************************************************** */
UC GetPRESETROMCommand(US wNum, UC *pbCommand)
{
	UC bResult = YH_SUCCESS;
	
	if(wNum <= PRESETROM0_END)
	{
		*pbCommand = 0x70;
		*(pbCommand+1) = wNum;
	}
	else if(wNum <= PRESETROM1_END)
	{
		*pbCommand = 0x71;
		*(pbCommand+1) = wNum - (PRESETROM0_END+1);
	}
	else if(wNum <= PRESETROM2_END)
	{
		*pbCommand = 0x72;
		*(pbCommand+1) = wNum - (PRESETROM1_END+1);
	}
	else if(wNum <= PRESETROM3_END)
	{
		*pbCommand = 0x73;
		*(pbCommand+1) = wNum - (PRESETROM2_END+1);
	}
	else
	{
		bResult = ERROR_PARAM;
	}
	
	return(bResult);
}

/* **************************************************** */
/* GetDSPWordSize										*/
/*		parameter:										*/
/*			unsigned short		wAdd					*/
/*								(DSP memory address)	*/
/*														*/
/*		return value:									*/
/*			unsigned long		word size				*/
/*														*/
/*		descripton:										*/
/*			obtain word size of the DSP memory.			*/
/* **************************************************** */
UL GetDSPWordSize(US wAdd)
{
	if     (wAdd <= DSP_MEM_ADD_WRAM0END)	return(2);
	else if(wAdd <= DSP_MEM_ADD_WRAM1END)	return(4);
	else if(wAdd <= DSP_MEM_ADD_WRAM2END)	return(4);
	else if(wAdd <= DSP_MEM_ADD_CRAMEND)	return(2);
	else if(wAdd <= DSP_MEM_ADD_MPRAMEND)	return(5);
	else if(wAdd <= DSP_MEM_ADD_QBUSEND)	return(4);
	else if(wAdd <= DSP_MEM_ADD_PEQRAMEND)	return(3);
	else return(2);
}

/* **************************************************** */
/* GetDSPDataSize										*/
/*		parameter:										*/
/*			unsigned short		wAdd					*/
/*								(DSP memory address)	*/
/*														*/
/*			unsigned short		wSize					*/
/*								(data size)				*/
/*														*/
/*		return value:									*/
/*			unsigned long		byte size				*/
/*														*/
/*		description:									*/
/*			obtain byte size.							*/
/* **************************************************** */
UL GetDSPDataSize(US wAdd, US wSize)
{
	US wCnt;
	UL dwResult = 0;
	
	for(wCnt = 0; wCnt < wSize; wCnt++)
	{
		dwResult += GetDSPWordSize(wAdd + wCnt);
	}
	
	return(dwResult);
}

/* **************************************************** */
/* CheckMDSPREQ											*/
/*		parameter:										*/
/*			none										*/
/*														*/
/*		return value:									*/
/*			unsigned char		processing result		*/
/*														*/
/*		description:									*/
/*			check DSP register : 0x13 MDSPREQ.			*/
/* **************************************************** */
UC CheckMDSPREQ(void)
{
	UC bData, bResult;
	
	/* wait for 1 sample time(=21 microseconds) */
	LoopWait(RT_MAX_WAIT);
	
	/* output start condition */
	bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
	/* transmit address */
	if(bResult == YH_SUCCESS)
	{
		bResult = Uart0Out(DSP_REG_ADD_MDSPREQ);
	}
	
	/* output start conditions again */
	if(bResult == YH_SUCCESS)
	{
		bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_READ);
	}
	
	/* receive data */
	if(bResult == YH_SUCCESS)
	{
		bResult = Uart0In(&bData);
	}
	
	/* output stop condition */
	//if(bResult != YH_SUCCESS)
	Uart0Stop();
	
	if(bResult == YH_SUCCESS)
	{
		if(bData != DSP_REG_DATA_RTREADY)
		{
			return(ERROR_RT);
		}
	}
	return(bResult);
}

/* **************************************************** */
/* CheckError											*/
/*		parameter:										*/
/*			none										*/
/*														*/
/*		return value:									*/
/*			unsigned char		processing result		*/
/*														*/
/*		description:									*/
/*			check errors of DSP. 						*/
/* **************************************************** */
UC CheckError(void)
{
	UC bMDSPST, bSDSPST, bPLLERR;
	UC bResult;
	
	bResult  = DSPReadReg(0x1B, &bMDSPST);		
	bResult += DSPReadReg(0x20, &bSDSPST);		
	bResult += DSPReadReg(0x23, &bPLLERR);		

	if(bResult == YH_SUCCESS)
	{
		if( (bMDSPST  & DSP_REG_MASK_MDSPERR)  |	
			(bSDSPST  & DSP_REG_MASK_SDSPERR)  |	
			(bPLLERR  & DSP_REG_MASK_PLLERR) )		
			
		{
			printf("CheckError ERROR_DSP");
			return(ERROR_DSP);
		}
	}
	printf("CheckError 0");
	return(bResult);
}

/* **************************************************** */
/* DSPWriteReg											*/
/*		parameter:										*/
/*			unsigned char		bAdd					*/
/*								(destination address)	*/
/*														*/
/*			unsigned char		bData					*/
/*								(setting data)			*/
/*														*/
/*		return value:									*/
/*			unsigned char		processing result		*/
/*														*/
/*		description:									*/
/*			set DSP register.							*/
/* **************************************************** */
UC DSPWriteReg(UC bAdd, UC bData)
{
	UC bResult;
	US wNakCount = 0;
	
	/* check address */
	#if 0 
	if( (bAdd < DSP_REG_ADD_TOP) || (bAdd > DSP_REG_ADD_END) )
	{
		return(ERROR_PARAM);
	}
	#endif
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit address */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bAdd);
		}
		
		/* transmit data */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bData);
		}
		
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	
	return(bResult);
}

/* **************************************************** */
/* DSPReadReg											*/
/*		parameter:										*/
/*			unsigned char		bAdd					*/
/*								(source address)		*/
/*														*/
/*			*unsigned char		pbData					*/
/*								(acquired data)			*/
/*														*/
/*		return value:									*/
/*			unsigned char		processing result		*/
/*														*/
/*		description:									*/
/*			obtain data form DSP register.				*/
/* **************************************************** */
UC DSPReadReg(UC bAdd, UC *pbData)
{
	UC bResult;
	US wNakCount = 0;
	#if 0
	/* check address */
	if( (bAdd < DSP_REG_ADD_TOP) || (bAdd > DSP_REG_ADD_END) )
	{
		return(ERROR_PARAM);
	}
	#endif
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit address */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bAdd);
		}
		
		/* output start conditions again */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_READ);
		}
		
		/* receive data */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0In(pbData);
		}
		
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	
	return(bResult);
}

/* **************************************************** */
/* DSPPartWriteReg										*/
/*		parameter:										*/
/*			unsigned char		bAdd					*/
/*						   		(destination address)	*/
/*														*/
/*			unsigned char		bData					*/
/*								(setting data)			*/
/*														*/
/*			unsigned char		bMask					*/
/*								(mask)					*/
/*														*/
/*		return value:									*/
/*			unsigned char		processing result		*/
/*														*/
/*		description:									*/
/*			set DSP register by bits					*/
/* **************************************************** */
UC DSPPartWriteReg(UC bAdd, UC bData, UC bMask)
{
	UC bResult, bTmp;
	
	/* obtain data from register */
	bResult = DSPReadReg(bAdd, &bTmp);
	if(bResult != YH_SUCCESS)
	{
		return(bResult);
	}
	
	/* create setting data */
	bData = ( (bTmp & ~bMask) | (bData & bMask) );
	
	/* set register */
	bResult = DSPWriteReg(bAdd, bData);
	
	return(bResult);
}

/* ******************************************************************** */
/* DSPLoadPreset														*/
/*		parameter:														*/
/*			unsigned short		wNum									*/
/*								(ROM block number)						*/
/*																		*/
/*			unsigned short		wAdd									*/
/*								(top address of transfer destination)	*/
/*																		*/
/*			unsigned char		bSetAdd									*/
/*								(1: set address)						*/
/*								(others: not set address)				*/
/*																		*/
/*		return value:													*/
/*			unsigned char		processing result						*/
/*																		*/
/*		description:													*/
/*			load preset pattern.										*/
/* ******************************************************************** */
UC DSPLoadPreset(US wNum, US wAdd, UC bSetAdd)
{
	UC bCommand[2], bStartAdd[2];
	UC bResult;
	US wNakCount = 0;
	#if 0
	/* check ROM block number */
	if( (wNum < DSP_ROM_NUM_MIN) || (wNum > DSP_ROM_NUM_MAX) )
	{
		return(ERROR_PARAM);
	}
	#endif
	/* when setting address */
	bStartAdd[0] = 0x00;
	bStartAdd[1] = 0x00;
	if(bSetAdd == TRUE)
	{
		/* check address */
		if( (wAdd < DSP_MEM_ADD_CRAMTOP) || (wAdd > DSP_MEM_ADD_CRAMEND) )
		{
			return(ERROR_PARAM);
		}
		
		bStartAdd[0] = ( (wAdd - DSP_MEM_ADD_CRAMTOP) >> 8 ) & 0xFF;
		bStartAdd[1] = (wAdd - DSP_MEM_ADD_CRAMTOP) & 0xFF;
	}
	
	/* obtain PRESETROM command */
	bResult = GetPRESETROMCommand(wNum, bCommand);
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* when setting address */
		if(bSetAdd == TRUE)
		{
			/* transmit WRITE/READ command */
			if(bResult == YH_SUCCESS)
			{
				bResult = Uart0Out(DSP_COM_WRITEREAD);
			}
			
			/* transmit address of RtStartAdr */
			if(bResult == YH_SUCCESS)
			{
				bResult = Uart0Out( (DSP_MEM_ADD_RTSTARTADR >> 8) & 0xFF );
			}
			
			if(bResult == YH_SUCCESS)
			{
				bResult = Uart0Out(DSP_MEM_ADD_RTSTARTADR & 0xFF);
			}
			
			/* transmit top address of transfer destination */
			if(bResult == YH_SUCCESS && bStartAdd[0] != NULL)
			{
					bResult = Uart0Out(bStartAdd[0]);
			}
			
			if(bResult == YH_SUCCESS && bStartAdd[1] != NULL)
			{
					bResult = Uart0Out(bStartAdd[1]);
			}
			
			/* output start conditions again */
			if(bResult == YH_SUCCESS)
			{
				bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_WRITE);
			}
		}
		
		/* transmit PRESETROM command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bCommand[0]);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bCommand[1]);
		}
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	return(bResult);
}

/* **************************************************** */
/* DSPStopPreset										*/
/*		parameter:										*/
/*			none										*/
/*														*/
/*		return value:									*/
/*			unsigned char		processing result		*/
/*														*/
/*		description:									*/
/*			abort load of preset pattern.				*/
/* **************************************************** */
UC DSPStopPreset(void)
{
	UC bResult;
	US wNakCount = 0;
	
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit PRROMSTOP command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_PRROMSTOP);
		}
		
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	
	return(bResult);
}

/* ******************************************************************** */
/* DSPWriteMem															*/
/*		parameter:														*/
/*			unsigned short		wAdd									*/
/*								(top address of transfer destination)	*/
/*																		*/
/*			*unsigned char		pbData									*/
/*								(setting data)							*/
/*																		*/
/*			unsigned short		wWordSize								*/
/*								(data size. word by word.)				*/
/*																		*/
/*		return value:													*/
/*			unsigned char		processing result						*/
/*																		*/
/*		description:													*/
/*			set DSP memory.												*/
/* ******************************************************************** */
UC DSPWriteMem(US wAdd, UC *pbData, US wWordSize)
{
	UL dwByteSize, dwTmp;
	UC bResult;
	US wNakCount = 0;
	
	/* check size */
	if( (wWordSize <= 0) || (wWordSize > TRANS_MAX_SIZE) )
	{
		return(ERROR_PARAM);
	}

	/* check area */
	dwTmp = (UL)wAdd + (UL)wWordSize - 1;
	#if 0
	if( (wAdd < DSP_MEM_ADD_RAMTOP) || (dwTmp > DSP_MEM_ADD_RAMEND) )
	{
		return(ERROR_PARAM);
	}
	#endif
	/* convert size by words to by bytes */
	dwByteSize = GetDSPDataSize(wAdd, wWordSize);
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit WRITE/READ command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_WRITEREAD);
		}
		/* transmit address */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (wAdd >> 8) & 0xFF );
		}
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(wAdd & 0xFF);
		}
		/* transmit data */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0BurstOut(pbData, dwByteSize);
		}
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{	
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	return(bResult);
}

/* **************************************************************** */
/* DSPReadMem														*/
/*		parameter:													*/
/*			unsigned short		wAdd								*/
/*								(top address of transfer source)	*/
/*																	*/
/*			*unsigned char		pbData								*/
/*								(acquired data)						*/
/*																	*/
/*			unsigned short		wWordSize							*/
/*								(data size. word by word.)			*/
/*		return value:												*/
/*																	*/
/*			unsigned char		processing result					*/
/*																	*/
/*		description:												*/
/*			obtain data form DSP memory.							*/
/* **************************************************************** */
UC DSPReadMem(US wAdd, UC *pbData, US wWordSize)
{
	UL dwByteSize, dwTmp;
	UC bResult;
	US wNakCount = 0;
	
	/* check size */
	if( (wWordSize <= 0) || (wWordSize > TRANS_MAX_SIZE) )
	{
		return(ERROR_PARAM);
	}

	/* check area */
	dwTmp = (UL)wAdd + (UL)wWordSize - 1;
	#if 0
	if( (wAdd < DSP_MEM_ADD_RAMTOP) || (dwTmp > DSP_MEM_ADD_RAMEND) )
	{
		return(ERROR_PARAM);
	}
	#endif
	/* convert size by words to by bytes */
	dwByteSize = GetDSPDataSize(wAdd, wWordSize);

	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit WRITE/READ command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_WRITEREAD);
		}
		
		/* transmit address */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (wAdd >> 8) & 0xFF );
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(wAdd & 0xFF);
		}
		
		/* transmit zero */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(0x00);
		}
		
		/* output start conditions again */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_READ);
		}
		
		/* receive data */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0BurstIn(pbData, dwByteSize);
		}
		
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	
	return(bResult);
}

/* ******************************************************************** */
/* MDSPCoefRTDL															*/
/*		parameter:														*/
/*			unsigned short		wAdd									*/
/*								(top address of transfer destination)	*/
/*																		*/
/*			*unsigned char		pbData									*/
/*								(setting data)							*/
/*																		*/
/*			unsigned short		wWordSize								*/
/*								(data size. word by word.)				*/
/*		return value:													*/
/*																		*/
/*			unsigned char		processing result						*/
/*																		*/
/*		description:													*/
/*			set DSP memory by runtime transfer.							*/
/* ******************************************************************** */
UC MDSPCoefRTDL(US wAdd, UC *pbData, US wWordSize)
{
	UL dwByteSize, dwTmp;
	UC bStartAdd[2];
	UC bResult;
	US wNakCount = 0;
	
	/* check size */
	if( (wWordSize < 1) || (wWordSize > RT_MAX_SIZE) )
	{
		return(ERROR_PARAM);
	}
		
	/* check area */
	dwTmp = (UL)wAdd + (UL)wWordSize - 1;
	if( (wAdd < DSP_MEM_ADD_CRAMTOP) || (dwTmp > DSP_MEM_ADD_CRAMEND) )
	{
		return(ERROR_PARAM);
	}
	
	/* prepare transfer data (top address of transfer destination) */
	bStartAdd[0] = ( (wAdd - DSP_MEM_ADD_CRAMTOP) >> 8 ) & 0xFF;
	bStartAdd[1] = (wAdd - DSP_MEM_ADD_CRAMTOP) & 0xFF;
	
	/* convert size by words to by bytes */
	dwByteSize = GetDSPDataSize(wAdd, wWordSize);
	
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit WRITE/READ command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_WRITEREAD);
		}
		
		/* transmit address of RtStartAdr */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (DSP_MEM_ADD_RTSTARTADR >> 8) & 0xFF );
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_MEM_ADD_RTSTARTADR & 0xFF);
		}
		
		/* transmit top address of transfer destination */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bStartAdd[0]);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bStartAdd[1]);
		}
		
		/* transmit size */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(0x00);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (UC)(wWordSize - 1) );
		}
		
		/* transfer data to RtData*(*=0-9) */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0BurstOut(pbData, dwByteSize);
		}
		
		/* output start conditions again */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		}
		
		/* request runtime transfer */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_REG_ADD_MDSPREQ);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_REG_DATA_RTDL);
		}
		
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	
	/* when runtime transfer processing is successful */
	if(bResult == YH_SUCCESS)
	{
		/* obtain/inform processing result of DSP */
		return(CheckMDSPREQ());
	}
	
	return(bResult);
}

/* **************************************************************** */
/* MDSPCoefRTUL														*/
/*		parameter:													*/
/*			unsigned short		wAdd								*/
/*								(top address of transfer source)	*/
/*																	*/
/*			*unsigned char		pbData								*/
/*								(acquired data)						*/
/*																	*/
/*			unsigned short		usWordSize							*/
/*								(data size.word by word.)			*/
/*																	*/
/*		return value:												*/
/*			unsigned char		processing result					*/
/*																	*/
/*		description:												*/
/*			obtain data from  DSP memory by runtime transfer.		*/
/* **************************************************************** */
UC MDSPCoefRTUL(US wAdd, UC *pbData, US wWordSize)
{
	UL dwByteSize, dwTmp;
	UC bStartAdd[2];
	UC bResult;
	US wNakCount = 0;
	
	/* check size */
	if( (wWordSize < 1) || (wWordSize > RT_MAX_SIZE) )
	{
		return(ERROR_PARAM);
	}
		
	/* check area */
	dwTmp = (UL)wAdd + (UL)wWordSize - 1;
	if( (wAdd < DSP_MEM_ADD_CRAMTOP) || (dwTmp > DSP_MEM_ADD_CRAMEND) )
	{
		return(ERROR_PARAM);
	}
	
	/* prepare the transfer data (top address of transfer source) */
	bStartAdd[0] = ( (wAdd - DSP_MEM_ADD_CRAMTOP) >> 8 ) & 0xFF;
	bStartAdd[1] = (wAdd - DSP_MEM_ADD_CRAMTOP) & 0xFF;
	
	/* convert size by words to by bytes */
	dwByteSize = GetDSPDataSize(wAdd, wWordSize);
	
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit WRITE/READ command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_WRITEREAD);
		}
		
		/* transmit address of RtStartAdr */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (DSP_MEM_ADD_RTSTARTADR >> 8) & 0xFF );
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_MEM_ADD_RTSTARTADR & 0xFF);
		}
		
		/* transmit top address of transfer source */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bStartAdd[0]);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bStartAdd[1]);
		}
		
		/* transmit size */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(0x00);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (UC)(wWordSize - 1) );
		}
		
		/* output start conditions again */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		}
		
		/* request runtime transfer */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_REG_ADD_MDSPREQ);
		}
		
		if( bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_REG_DATA_RTUL);
		}
		
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	
	/* when runtime transfer processing is successful */
	if(bResult == YH_SUCCESS)
	{
		/* obtain processing result of DSP */
		bResult = CheckMDSPREQ();
		
		/* when processing for DSP is failed */
		if(bResult != YH_SUCCESS)
		{
			return(bResult);
		}
	}
	
	wNakCount = 0;
	
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit WRITE/READ command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_WRITEREAD);
		}
		
		/* transmit address of RtData0 */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (DSP_MEM_ADD_RTDATA0 >> 8) & 0xFF );
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_MEM_ADD_RTDATA0 & 0xFF);
		}
		
		/* transmit zero */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(0x00);
		}
		
		/* output start conditions again */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_READ);
		}
		
		/* acquire data from RtData*(*=0-9) */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0BurstIn(pbData, dwByteSize);
		}
		
		/* output stop condition */
		//if(bResult != YH_SUCCESS)
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	
	return(bResult);
}


UC SDSPCoefBT(US wAdd, UC *pbData, US wWordSize)
{
	UL dwByteSize, dwTmp;
	UC bPEQPrameter, bResult;
	US wNakCount = 0;
	
	/* check size */
	if( (wWordSize != 5) && (wWordSize != 10) )
	{
		return(ERROR_PARAM);
	}
		
	/* check area */
	dwTmp = (UL)wAdd + (UL)wWordSize - 1;
	if( (wAdd < DSP_MEM_ADD_PEQCOEFTOP) || (dwTmp > (DSP_MEM_ADD_PEQCOEFEND)) )
	{
		return(ERROR_PARAM);
	}

	/* prepare transfer parameter */
	if(wWordSize == 0x5)
		bPEQPrameter = ( 0x00 | (wAdd & DSP_RAM_MASK_PEQAD) );
	else
		bPEQPrameter = ( 0x80 | (wAdd & DSP_RAM_MASK_PEQAD) );
	
	/* convert size by words to by bytes */
	dwByteSize = GetDSPDataSize(wAdd, wWordSize);
	
	while(1)
	{
		/* output start condition */
		bResult = Uart0Start(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		/* transmit WRITE/READ command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_WRITEREAD);
		}
		
		/* transmit PEQ coefficient buffer address */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (DSP_MEM_ADD_PEQBUFTOP >> 8) & 0xFF );
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_MEM_ADD_PEQBUFTOP & 0xFF);
		}
		
		/* transfer data */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0BurstOut(pbData, dwByteSize);
		}
		
		/* output start conditions again */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Restart(I2C_SLAVE_ADD_DSP, I2C_WRITE);
		}
		
		/* transmit WRITE/READ command */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_COM_WRITEREAD);
		}
		
		/* transmit address of transfer parameter */
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out( (DSP_MEM_ADD_PEQPRAMETER >> 8) & 0xFF );
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(DSP_MEM_ADD_PEQPRAMETER & 0xFF);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(bPEQPrameter);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(0x00);
		}
		
		if(bResult == YH_SUCCESS)
		{
			bResult = Uart0Out(0x00);
		}
		
		Uart0Stop();
		
		if(bResult == ERROR_I2C)
		{
			if(wNakCount++ >= I2C_RETRYCOUNT)
			{
				return(bResult);
			}
		}
		else
		{
			break;
		}
	}
	return(bResult);
}

/* end of file*/


UC Uart0Start(UC bSlaveAddress, UC bRW)
{
/*
	This function depends on the device.
	Please write the program code which realizes the following.
	
	1) To I2C bus, set start condition, and output DD-2SP/SPR-2's I2C slave address (0x6C) and Read/Write bit.
	   
	   if write (bRW=0) : start condition + 0xD8
	   if read  (bRW=1) : start condition + 0xD9
	   
	2) If a result of 1) is normal (acknowledge is returned), return "SUCCESS".
	   Other than the above, return "ERROR_I2C".
*/
		UC bRead;
		bRead = 1;
		bRead = I2C_Start();
		//printf("I2C_Start I2C_Start--- %d \n",bRead);
		//bRead = I2C_Write_Byte(bSlaveAddress);//;
		bSlaveAddress = 0;
		if(bRW)
		{
			bRead = I2C_Write_Byte(0xD9);
		}
		else
		{
			bRead = I2C_Write_Byte(0xD8);
		}
		if(bRead == 0)
		{
			return YH_SUCCESS;
		}
		else
		{	
			return ERROR_I2C;
		}
}


void Uart0Stop(void)
{
/*
	This function depends on the device.
	Please write the program code which realizes the following.
	
	- To I2C bus, set stop condition.
*/
	I2C_Stop();
}


UC Uart0Restart(UC bSlaveAddress, UC bRW)
{
	if(I2C_Start()){
		return ERROR_I2C;
	}else{
		return Uart0Out((bSlaveAddress << 1) | bRW);
	}
}


UC Uart0Out(UC bOutdata)
{
	UC bResult ;
	bResult = 1;
	bResult = I2C_Write_Byte(bOutdata);
	
	if(bResult == 0 ){
		return YH_SUCCESS;
	}
	else
	{	
		AddErrorI2CCount();
		return ERROR_I2C;
	}
}


void AddErrorI2CCount(void)
{
	uErrorI2CCount++;
}

UL GetErrorI2CCOunt(void)
{	
	return uErrorI2CCount;
}

UL ResetErrorI2CCOunt(void)
{	
	return (uErrorI2CCount = 0);
}


UC Uart0In(UC *pbInData)
{
/*
	This function depends on the device.
	Please write the program code which realizes the following.
	
	1) From I2C bus, recive 1 byte data.
	   
	2) If a result of 1) is normal, output acknowledge to I2C bus, and return "SUCCESS".
	   Other than the above, output negative acknowledge to I2C bus, and return "ERROR_I2C".
*/
	*pbInData = I2C_Read_Byte(1);
	return YH_SUCCESS;
}


UC Uart0BurstOut(UC *dwAddress, UL dwSize)
{
/*
	This function depends on the device.
	Please write the program code which realizes the following.
	
	1) To I2C bus, output "dwSize" bytes data continuously.
	   
	2) If a result of 1) is normal (acknowledge is returned), return "SUCCESS".
	   Other than the above, return "ERROR_I2C".
*/
	UL i;
	UC bResult;
	bResult = 0;;
	for(i=0;i<dwSize;i++)
	{
		bResult = I2C_Write_Byte(*dwAddress);
		dwAddress++;
		if(bResult != 0)
		{
			return ERROR_I2C;
		}
	}
	return YH_SUCCESS;
}

UC Uart0BurstIn(UC *dwAddress, UL dwSize)
{
	while(dwSize)
	{
		if(dwSize == 1)
		{
			*dwAddress = I2C_Read_Byte(1);
		}
		else
		{
			*dwAddress = I2C_Read_Byte(1);
			dwAddress++;
		}
		dwSize--;
	}
	return YH_SUCCESS;
}


void SetVolume(UC bVolID)
{
	US wPresetNum; //gchen
	
	/* master volume setting */
	if(bVolID >= 1 && bVolID <= 0x85)
	{
		/* less than 100dB */
		if(bVolID <= 0xF)
		{
			wPresetNum = 0x03BA - (US)bVolID;
		}
		/* more than 99dB */
		else
		{
			wPresetNum = 0x03A9 - (US)( (bVolID - 0x10) * 2 );
		}
		
		DSPLoadPreset(wPresetNum, 0, 0);
	}
}
