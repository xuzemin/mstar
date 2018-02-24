////////////////////////////////////////////////////////////////////////////////
//
//optical
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DLP_OPTICAL_H_
#define _DLP_OPTICAL_H_

#ifdef _DLP_C_
#define _DLPOPTICAL_
#else
#define _DLPOPTICAL_ extern
#endif
#include "Board.h"
#define D_PICTURE_MODE_DEFINE

#define MAIN_STATUS               	0x03
#define FLASH_READ                		0x07
#define PBC_CONTROL               	0x08
#define INPUT_SOURCE              	0x0B
#define INPUT_RESOLUTION        	0x0C
#define DATA_FORMAT               	0x0D
//#define IMG_ROTATION              0x0E
#define LONG_FLIP                 		0x0F
#define SHORT_FLIP                		0x10
#define TEST_PAT_SELECT          	0x11
#define R_DRIVE_CURRENT          0x12
#define G_DRIVE_CURRENT       	0x13
#define B_DRIVE_CURRENT          0x14
#define READ_REG_SELECT          0x15
#define RGB_DRIVER_ENABLE      	0x52//16

//AGC registers
#define AGC_SAFETY_MARGIN        	0x17

#define CPU_IF_MODE               		0x18
//#define FRAME_RATE                0x19
//#define CPU_IF_SYNC_METHOD        0x1A
//#define CPU_IF_SOF                0x1B
//#define CPU_IF_EOF                0x1C
//#define CPU_IF_SLEEP              0x1D

#define SEQUENCE_MODE             0x1E
#define SOFT_RESET                0x1F
#define FRONT_END_RESET           0x21
//#define AUTO_PWR_ENABLE           0x22

#define VSYNC_LINE_DELAY          0x23
//#define CPU_PI_HORIZ_START        0x24
//#define CPU_PI_VERT_START         0x25
//#define CPU_PI_HORIZ_WIDTH        0x26
//#define CPU_PI_VERT_HEIGHT        0x27

//#define PIXEL_MASK_CROP           0x28
#define CROP_FIRST_LINE           0x29
#define CROP_LAST_LINE            0x2A
#define CROP_FIRST_PIXEL          0x2B
#define CROP_LAST_PIXEL           0x2C

#define DMD_PARK                  0x2D

//OSD
#define OSD_STATUS                  0x2E

#define MISC_REG                  0x30
#define CHI_CBCR_SWAP             0x32  //DPP2606   //new for DPP2606
#define LED_OVERLAP_CONTROL 0x3C

#define WRITE_KEYSTONE_PROJECTION_PITCH_ANGLE 0xbb
//<<gchen @ 20170821 //yangming opt driver
#define WRITE_INPUT_SOURCE_SELECT 0x5
#define WRITE_RGB_CURRENT	0x54
#define WRITE_KEYSTONE_CORRECTION_CONTROL 0x88
#define WRITE_OPT_RES	0x10
//>>gchen @ 20170821 //yangming opt driver
#define WRITE_3435_FREEZE 0x1a //gchen @ 20170816 //freeze opt
///////////////////2607  start////////////////////////////////////
#define ICP_COMMAND             0x38
#define ICP_DATA                0x39  
#define ICP_COMMAND_HANDSHAKE 0x3a


/* I2C slave address definition */
#define	I2C_SLAVE_ADD_DSP	0x6C		/* DD-2SP/SPR-2 */

/* number of I2C communication retransmission */
#define I2C_RETRYCOUNT		10

/* DSP control command code */
#define DSP_COM_WRITEREAD	0x80
#define DSP_COM_PRROMSTOP	0x43

/* definitions related to PRESETROM command */
#define DSP_ROM_NUM_MIN		0x000
#define DSP_ROM_NUM_MAX		0x3FF
#define PRESETROM0_END		0x0FF
#define PRESETROM1_END		0x1FF
#define PRESETROM2_END		0x2FF
#define PRESETROM3_END		0x3FF

/* DSP register address */
#define DSP_REG_ADD_TOP			0x00	/* register top */
#define DSP_REG_ADD_END			0x3F	/* register end */
#define DSP_REG_ADD_MDSPREQ		0x13	/* MDSPREQ */

/* DSP register bit mask */
#define DSP_REG_MASK_MDSPERR	0x01 	/* MDSPERR */
#define DSP_REG_MASK_SDSPERR	0x01 	/* SDSPERR */
#define DSP_REG_MASK_PLLERR		0x01 	/* PLLERR */

/* DSP register setting data */
#define DSP_REG_DATA_RTREADY	0x00
#define DSP_REG_DATA_RTDL		0x02
#define DSP_REG_DATA_RTUL		0x03

/* DSP memory address */
#define DSP_MEM_ADD_RAMTOP		0x0000	/* embedded RAM top */
#define DSP_MEM_ADD_RAMEND		0xFFFF	/* embedded RAM end */
#define DSP_MEM_ADD_RTSTARTADR	0x0000	/* RtStartAdr */
#define DSP_MEM_ADD_RTDATA0		0x0002	/* RtData0 */
#define DSP_MEM_ADD_WRAM0END	0x001F	/* WRAM0 end */
#define DSP_MEM_ADD_WRAM1END	0x03FF	/* WRAM1 end */
#define DSP_MEM_ADD_WRAM2END	0x3FFF	/* WRAM2 end */
#define DSP_MEM_ADD_CRAMTOP		0x4000	/* CRAM top */
#define DSP_MEM_ADD_CRAMEND		0x43FF	/* CRAM end */
#define DSP_MEM_ADD_MPRAMEND	0x49FF	/* MPRAM end */
#define DSP_MEM_ADD_QBUSEND		0x7FFF	/* QBUS end */
#define DSP_MEM_ADD_PEQCOEFTOP	0x8000	/* PEQ coefficient area top */
#define DSP_MEM_ADD_PEQCOEFEND	0x8045	/* PEQ coefficient area end */
#define DSP_MEM_ADD_PEQBUFTOP	0x8046	/* PEQ transfer buffer top */
#define DSP_MEM_ADD_PEQPRAMETER	0x8050	/* PEQ transfer parameter area */
#define DSP_MEM_ADD_PEQRAMEND	0xBFFF	/* PEQ coefficient RAM End */

/* DSP memory data mask */
#define DSP_RAM_MASK_PEQAD		0x7F	/* bit[6:0]=1 */

/* definitions related to transfer */
#define TRANS_MAX_SIZE	(US)(2048)		/* maximum transfer size */

/* definitions related to runtime transfer */
#define RT_MAX_SIZE		(US)(10)		/* maximum transfer size */
#define RT_MAX_WAIT		(UL)(21)		/* maximum processing time */

#if ENABLE_HIGH_AND_LOW_LIGHT_SWITCH
typedef enum CURRENT_MODE
{
	SAVEMODE_CURRENT_MODE,
	NORMAL_CURRENT_MODE	
} CURRENT_MODE;
#endif

typedef unsigned char	UC;
typedef unsigned short	US;
typedef unsigned long	UL;
typedef unsigned char	bol;

#define OFF		0
#define ON		1

#define FALSE	0
#define TRUE	1

#define LOW		0
#define HIGH	1

/* result code definition */
#define YH_SUCCESS		0
#define ERROR_I2C		1
/*      ERROR_NAK		2  reserved */
#define ERROR_RT		3
#define ERROR_DSP		4
#define ERROR_PARAM		5
///////////////////2607  end////////////////////////////////////
//GPIO
#define GPIO_CONTROL              0x33
#define GPIO_READ                 0x34


#define SDRAM_BIST_ENABLE         0x46


// AGC registers
#define AGC_CTRL                  0x50
#define AGC_STEP_SIZE_INC         0x52
#define AGC_STEP_SIZE_DEC         0x53
#define AGC_LEAP_SIZE_DEC         0x54
#define AGC_CLIPPED_PIXS          0x55
#define AGC_BRIGHT_PIXS           0x56
#define AGC_BG_PIXS               0x57


// CCA registers
#define CCA_ENABLE                0x5E
#define CCA_C1A                   0x5F
#define CCA_C1B                   0x60
#define CCA_C1C                   0x61
#define CCA_C2A                   0x62
#define CCA_C2B                   0x63
#define CCA_C2C                   0x64
#define CCA_C3A                   0x65
#define CCA_C3B                   0x66
#define CCA_C3C                   0x67
#define CCA_C4A                   0x68
#define CCA_C4B                   0x69
#define CCA_C4C                   0x6A
#define CCA_C5A                   0x6B
#define CCA_C5B                   0x6C
#define CCA_C5C                   0x6D
#define CCA_C6A                   0x6E
#define CCA_C6B                   0x6F
#define CCA_C6C                   0x70
#define CCA_C7A                   0x71
#define CCA_C7B                   0x72
#define CCA_C7C                   0x73

// registers for DMA operations from flash to DPP2600 LUTs
#define FLASH_ADDR_BYTES          0x74
#define FLASH_DUMMY_BYTES         0x75
#define FLASH_WRITE_BYTES         0x76
#define FLASH_READ_BYTES          0x77
#define FLASH_OPCODE              0x78
#define FLASH_START_ADDR          0x79
#define FLASH_DUMMY2              0x7A
#define FLASH_WRITE_DATA          0x7B
#define FLASH_TXDATA_BYTE         0x7C

#define TEMPORAL_DITH_DISABLE     0x7E
#define CMT_OVERLAP                      0x7F
#define CMT_OCB_C1C2_MASK          0x80

#define SEQ_CONTROL               0x82
#define SEQ_VECTOR                0x83
#define DMD_BLOCK_COUNT           0x84
#define DMD_VCC_CONTROL           0x86
#define DMD_PARK_PULSE_COUNT      0x87
#define DMD_PARK_PULSE_WIDTH      0x88
#define DMD_PARK_DELAY            0x89
#define DMD_SHADOW_ENABLE         0x8E
#define SEQ_STATUS                  0x8E
//#define SEQ_STATUS                0x8F
//#define FLASH_CLOCK_CONTROL       0x98



//#define DDR_DRIVER_STRENGTH       0x9A
#define SDC_ENABLE                0x9D
#define SDC_BUFF_SWAP_DISABLE     0xA3

#define YCC2RGB_CONTROL           0xA4

#define CURTAIN_CONTROL           0xA6
#define DDR_BUS_SWAP_ENABLE       0xA7
//#define DMD_TRC_ENABLE            0xA8
//#define DMD_BUS_SWAP_ENABLE       0xA9

#define ACTGEN_ENABLE             0xAE
#define ACTGEN_CONTROL            0xAF
#define ACTGEN_HORIZ_BP           0xB0
#define ACTGEN_VERT_BP            0xB1

#define PARALLEL_BUS_SELECT    0xB2

//OSD
#define OSD_FN_ENABLE           0xB4
#define OSD_OVERRIDE_POSITION   0xB5

// LUT access
#define CMT_SPLASH_LUT_START_ADDR   0xFA
#define CMT_SPLASH_LUT_DEST_SELECT  0xFB
#define CMT_SPLASH_LUT_DATA         0xFC
#define SEQ_RESET_LUT_START_ADDR    0xFD
#define SEQ_RESET_LUT_DEST_SELECT   0xFE
#define SEQ_RESET_LUT_DATA          0xFF


// input source defines
#define PARALLEL_RGB              0
#define INT_TEST_PATTERN          1
#define SPLASH_SCREEN             2
#define CPU_INTF                  3
#define BT656                     4

// input resolution defines
#define QVGA_PORTRAIT             0       // (240h*320v)
#define QVGA_LANDSCAPE            1       // (320h*240v)
#define QWVGA_LANDSCAPE           3       // (427h*240v)
#define VGA_PORTRAIT_2_3          4       // (430h*640v)
#define VGA_LANDSCAPE_3_2         5       // (640h*430v)
#define VGA_PORTRAIT              6       // (480h*640v)
#define VGA_LANDSCAPE             7       // (640h*480v)
#define WVGA_720_PORTRAIT         8       // (480h*720v)
#define WVGA_720_LANDSCAPE        9       // (720h*480v)
#define WVGA_752_PORTRAIT         10      // (480h*752v)
#define WVGA_752_LANDSCAPE        11      // (752h*480v)
#define WVGA_800_PORTRAIT         12      // (480h*800v)
#define WVGA_800_LANDSCAPE        13      // (800h*480v)
#define WVGA_852_PORTRAIT         14      // (480h*852v)
#define WVGA_852_LANDSCAPE        15      // (852h*480v)
#define WVGA_853_PORTRAIT         16      // (480h*853v)
#define WVGA_853_LANDSCAPE        17      // (853h*480v)
#define WVGA_854_PORTRAIT         18      // (480h*854v)
#define WVGA_854_LANDSCAPE        19      // (854h*480v)
#define WVGA_864_PORTRAIT         20      // (480h*864v)
#define WVGA_864_LANDSCAPE        21      // (864h*480v)
#define NTSC_LANDSCAPE            23      // (720h*240v)
#define PAL_LANDSCAPE             25      // (720h*288v)
#define VGA_DMD_OPTICAL_TEST      33      // (456h*684v)
#define WVGA_DMD_OPTICAL_TEST     35      // (608h*684v)

// data format defines
#define RGB565                    0
#define RGB666                    1
#define RGB888                    2

// test pattern defines
#define TPG_CHECKERBOARD          0
#define TPG_BLACK                 1
#define TPG_WHITE                 2
#define TPG_RED                   3
#define TPG_BLUE                  4
#define TPG_GREEN                 5
#define TPG_VLINES_BLACK          6
#define TPG_HLINES_BLACK          7
#define TPG_VLINES_ALT            8
#define TPG_HLINES_ALT            9
#define TPG_DIAG_LINES            10
#define TPG_GREYRAMP_VERT         11
#define TPG_GREYRAMP_HORIZ        12
#define TPG_ANSI_CHECKERBOARD     13

// sequence mode defines
#define SEQ_FREE_RUN              0
#define SEQ_LOCK                  1

// curtain color defines
#define CURTAIN_BLACK             0
#define CURTAIN_RED               1
#define CURTAIN_GREEN             2
#define CURTAIN_BLUE              3
#define CURTAIN_YELLOW            4
#define CURTAIN_MAGENTA           5
#define CURTAIN_CYAN              6
#define CURTAIN_WHITE             7

// LUT defines
#define CMT_LUT_NONE              0
#define CMT_LUT_GREEN             1
#define CMT_LUT_RED               2
#define CMT_LUT_BLUE              3
#define CMT_LUT_ALL               4
#define SPLASH_LUT                5

#define SEQ_LUT_NONE              0
#define SEQ_DRC_LUT_0             1
#define SEQ_DRC_LUT_1             2
#define SEQ_DRC_LUT_2             3
#define SEQ_DRC_LUT_3             4
#define SEQ_SEQ_LUT               5
#define SEQ_DRC_LUT_ALL           6
#define WPC_PROGRAM_LUT           7

#define DMA_STATUS                 0x100//BIT8


//0x2AF --- 67.15%
//0x2B3 --- 67.5%
//0x2B1 --- 67.25%
//0x2B9 --- 68.
//0x23B --- 55.7~55.8
#define R_LED_NORMAL_CURR        	0x19c//0x200//Evan100728   0x2e9//2d9//2d1//2B1 
#define G_LED_NORMAL_CURR        	0x19c//0x200//Evan100728   0x2e9//2d9//2d1//2B1 
#define B_LED_NORMAL_CURR       	0x19c// 0x200//Evan100728   0x2e9//2d9//2B1 

#define R_LED_SAVEMODE_CURR        	0x229//0x200//Evan100728   0x2e9//2d9//2d1//2B1 //change by gchen @ 20110615 //change to 1.0A
#define G_LED_SAVEMODE_CURR        	0x229//0x200//Evan100728   0x2e9//2d9//2d1//2B1 
#define B_LED_SAVEMODE_CURR       	0x229// 0x200//Evan100728   0x2e9//2d9//2B1 


#define INVERSION               1
#define INVERSION_MIRROR             2
#define ORTHOGRAPHY_MIRROR               3
#define ORTHOGRAPHY            4

#define DPP2600_DEV_ADDR      0x36
//#define MPE1601_DEV_ADDR      0x80
#define MPE1601_DEV_ADDR      0x86
//system controller
#define SYS_CTRL          0x03

//interrupt controller


//GPIO controller 
#define GPIO_SET_MSB     0x13
#define GPIO_SET_LSB      0x12
#define GPIO_MP_MSB      0x11
#define GPIO_MP_LSB       0x10
#define GPIO_SET_DIR_MSB 0x15
#define GPIO_SET_DIR_LSB  0x14  

//MPE1601 GPIO setting
#define PWR_GOOD      0x01  //GPIO0 --- output
#define EN_1V8_EPE    0x02  //GPIO1 --- output
#define EN_1V0_EPE    0x04  //GPIO2 --- output
#define EMU_DONE_INT  0x08  //GPIO3 --- input
#define LED_TEMP_INT  0x10  //GPIO4 --- input
#define MOT_EN        0x20  //GPIO5 --- output
#define EMU_RST_Z     0x40  //GPIO6 --- output
#define EN_3V3_EPE    0x80  //GPIO7 --- output
#define OC_OUT        0x01   //GPIO8 --- input
#define MOT_IN1A      0x02  //GPIO9 --- output
#define MOT_IN1B      0x04  //GPIO10 --- output
#define MOT_IN2A      0x08  //GPIO11 --- output
#define MOT_IN2B      0x10  //GPIO12 --- output
#define PWR_EN_EPE    0x20   //GPIO13 --- output
#define TP101         0x40   //GPIO14 --- output
#define FAN_EN        0x80   //GPIO15 --- output

#define ACK_FLAG     1

#define I2C_WRITE	0
#define I2C_READ	1
//VAR
_DLPOPTICAL_ U8 BlankONOFF;
//functions
// DPP configuration functions
_DLPOPTICAL_ void call_dpp2600_seq(U8 power_mode, U8 picture_mode,BOOL feq_is_60);
_DLPOPTICAL_ void dpp2600_main_configure(void);
_DLPOPTICAL_ U8 dpp2600_flash_dma(U32 flash_address, U32 flash_num_bytes, U8 CMT_SEQz, U8 table_number);
_DLPOPTICAL_ U8 dpp2600_config_tpg(U8 pattern_select);
_DLPOPTICAL_ U8 dpp2600_config_splash(U8 image_number);
_DLPOPTICAL_ void dpp2600_config_rgb(void);
_DLPOPTICAL_ void DPP_WaitForDMA(void);
_DLPOPTICAL_ void SetOpticalPower(U8 power_mode);
#if ENABLE_HIGH_AND_LOW_LIGHT_SWITCH
_DLPOPTICAL_ void SetOpticalPowermode(BYTE power_mode);
#endif
#if FIX_STARTUP_COLOR_DISTORTION
_DLPOPTICAL_ void SetOpticalCurrent(U32 uCurrValue);
#endif
_DLPOPTICAL_ void Optical_Led_Switch(U8 OnOff);
_DLPOPTICAL_ void write_dpp2600_i2c(U16 u16BusNumSlaveID, U8 u8addr, U32 data, U8 verify);
_DLPOPTICAL_ BOOLEAN write_i2c_1byte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 u8Data);
_DLPOPTICAL_ void 	OpticalMain(void);
_DLPOPTICAL_ void dpp2600_config_blank(U8 OnOff);
_DLPOPTICAL_ void PreInitOptical(void);
_DLPOPTICAL_ void Opticalshutdown(void);
//<<gchen @ 20170811 //opt dead if dead then is high		
_DLPOPTICAL_ int Opt3435_deadpin_get_level(void); 
//>>gchen @ 20170811 //opt dead if dead then is high		

//>>wht141107_1
_DLPOPTICAL_ void devOPE_Long_Axis_Flip(U8 OnOff);
_DLPOPTICAL_ void devOPE_Short_Axis_Flip(U8 OnOff);
//<<wht141107_1
_DLPOPTICAL_ void keystone_correction(S8 angle);
_DLPOPTICAL_ void Optical_Led_OpenANDClose(U8 OnOff);
_DLPOPTICAL_ void Optical_YangMing_InputSourceSelect(void);
_DLPOPTICAL_ void Optical_YangMing_RGBCurrent(void);
_DLPOPTICAL_ void Optical_YangMing_KeyStoneCorrection_Control(void);
_DLPOPTICAL_ void Optical_SetRes_854x480(void);
_DLPOPTICAL_ void Optical_SetRes_1280x800(void);
_DLPOPTICAL_ bool Optical_LED_CheckStatus(void); //gchen check 3435 if is ok //20170914

_DLPOPTICAL_ void Mute(void);
_DLPOPTICAL_ void MuteRelease(void);
_DLPOPTICAL_ void SetVolume(UC bVolID);

_DLPOPTICAL_ void SetBalance(signed char bBalID);

_DLPOPTICAL_ void SetCrossover(UC bNetworkID, UC *pbData);

_DLPOPTICAL_ void SetS3D(UC *pbData);
_DLPOPTICAL_ void S3DOn(bool bOn);

_DLPOPTICAL_ void SetHXT(UC *pbData);
_DLPOPTICAL_ void HXTOn(bool bOn);

_DLPOPTICAL_ void SetAEQ(UC *pbData0, UC *pbData1);
_DLPOPTICAL_ void AEQOn(bool bOn);

_DLPOPTICAL_ void PresetLoudnessSetting(UC bEffectID);
_DLPOPTICAL_ void UserLoudnessSetting(UC *pbData);
_DLPOPTICAL_ void LoudnessOn(bool bOn);

_DLPOPTICAL_ void SetPowerLimit(UC *pbData);
_DLPOPTICAL_ void PowerLimitOn(bool bOn);

_DLPOPTICAL_ void SetSoftClip(UC *pbData);
_DLPOPTICAL_ void SoftClipOn(bool bOn);

_DLPOPTICAL_ void SmallSignalDetectionOn(UC *pbData);
_DLPOPTICAL_ void SmallSignalDetectionOff(void);

_DLPOPTICAL_ void PlayFM(UC bContentID);

_DLPOPTICAL_ void SetVolume(UC bVolID);
_DLPOPTICAL_ void Uart0Stop(void);
_DLPOPTICAL_ UC Uart0Restart(UC bSlaveAddress, UC bRW);
_DLPOPTICAL_ UC Uart0Out(UC bOutdata);
_DLPOPTICAL_ UC Uart0Start(UC bSlaveAddress, UC bRW);
_DLPOPTICAL_ UC Uart0In(UC *pbInData);
_DLPOPTICAL_ void AddErrorI2CCount(void);
_DLPOPTICAL_ UL GetErrorI2CCOunt(void);
_DLPOPTICAL_ UL ResetErrorI2CCOunt(void);
_DLPOPTICAL_ UC Uart0BurstOut(UC *dwAddress, UL dwSize);
_DLPOPTICAL_ UC Uart0BurstIn(UC *dwAddress, UL dwSize);

_DLPOPTICAL_ UC CheckError(void);
_DLPOPTICAL_ UC DSPWriteReg(UC bAdd, UC bData);
_DLPOPTICAL_ UC DSPReadReg(UC bAdd, UC *pbData);
_DLPOPTICAL_ UC DSPPartWriteReg(UC bAdd, UC bData, UC bMask);
_DLPOPTICAL_ UC DSPLoadPreset(US wNum, US wAdd, UC bSetAdd);
_DLPOPTICAL_ UC DSPStopPreset(void);
_DLPOPTICAL_ UC DSPWriteMem(US wAdd, UC *pbData, US wWordSize);
_DLPOPTICAL_ UC DSPReadMem(US wAdd, UC *pbData, US wWordSize);
_DLPOPTICAL_ UC MDSPCoefRTDL(US wAdd, UC *pbData, US wWordSize);
_DLPOPTICAL_ UC MDSPCoefRTUL(US wAdd, UC *pbData, US wWordSize);
_DLPOPTICAL_ UC SDSPCoefBT(US wAdd, UC *pbData, US wWordSize);
_DLPOPTICAL_ void devOPE_set_Flip(U8 OnOff);
#ifdef D_PICTURE_MODE_DEFINE

#define SEQUENCE_0_START_ADDR        0x00044000L
#define SEQUENCE_0_SIZE                     0x00001000L

#define SEQUENCE_1_START_ADDR        0x00045000L
#define SEQUENCE_1_SIZE                     0x00001000L

#define SEQUENCE_2_START_ADDR        0x00046000L
#define SEQUENCE_2_SIZE                     0x00001000L

#define SEQUENCE_3_START_ADDR        0x00047000L
#define SEQUENCE_3_SIZE                     0x00001000L

#define SEQUENCE_4_START_ADDR        0x00048000L
#define SEQUENCE_4_SIZE                     0x00001000L

#define SEQUENCE_5_START_ADDR        0x00049000L
#define SEQUENCE_5_SIZE                     0x00001000L

#define SEQUENCE_6_START_ADDR        0x0004a000L
#define SEQUENCE_6_SIZE                     0x00001000L

#define CMT_LUT_0_START_ADDR         0x0004b200L
#define CMT_LUT_0_SIZE                      0x00000600L

#define CMT_LUT_1_START_ADDR         0x0004b800L
#define CMT_LUT_1_SIZE                      0x00000600L

#define CMT_LUT_2_START_ADDR         0x0004be00L
#define CMT_LUT_2_SIZE                      0x00000600L

#define CMT_LUT_3_START_ADDR         0x0004c400L
#define CMT_LUT_3_SIZE                      0x00000600L

#define CMT_LUT_4_START_ADDR         0x0004ca00L
#define CMT_LUT_4_SIZE                      0x00000600L

#define CMT_LUT_5_START_ADDR         0x0004d000L
#define CMT_LUT_5_SIZE                      0x00000600L

#define CMT_LUT_6_START_ADDR         0x0004d600L
#define CMT_LUT_6_SIZE                      0x00000600L

#define DRC_TABLE_0_START_ADDR      0x0004dc00L
#define DRC_TABLE_0_SIZE                   0x00000100L

#define SPLASH_0_START_ADDR           0x0004dd00L
#define SPLASH_0_SIZE                        0x00032280L

#define SEQUENCE_7_START_ADDR      0x00080000L
#define SEQUENCE_7_SIZE                   0x00001000L

#define SEQUENCE_8_START_ADDR        0x00081800L
#define SEQUENCE_8_SIZE                     0x00001000L

#define SEQUENCE_9_START_ADDR        0x00083000L
#define SEQUENCE_9_SIZE                     0x00001000L

#define SEQUENCE_15_START_ADDR        0x0008C000L
#define SEQUENCE_15_SIZE                     0x00001000L

#define CMT_LUT_7_START_ADDR         0x0008e000L
#define CMT_LUT_7_SIZE                      0x00000600L

#define CMT_LUT_8_START_ADDR         0x0008e800L
#define CMT_LUT_8_SIZE                      0x00000600L

#define CMT_LUT_9_START_ADDR         0x0008f000L
#define CMT_LUT_9_SIZE                      0x00000600L

#define CMT_LUT_10_START_ADDR         0x0008f800UL
#define CMT_LUT_10_SIZE                      0x00000600UL

#define CMT_LUT_11_START_ADDR         0x00090000UL
#define CMT_LUT_11_SIZE                      0x00000600UL

#define CMT_LUT_12_START_ADDR         0x00090800UL
#define CMT_LUT_12_SIZE                      0x00000600UL

#define CMT_LUT_13_START_ADDR         0x00091000UL
#define CMT_LUT_13_SIZE                      0x00000600UL

#define CMT_LUT_14_START_ADDR         0x00091800UL
#define CMT_LUT_14_SIZE                      0x00000600UL

#define CMT_LUT_15_START_ADDR         0x00092000UL
#define CMT_LUT_15_SIZE                      0x00000600UL

#define CMT_LUT_16_START_ADDR         0x00092800UL
#define CMT_LUT_16_SIZE                      0x00000600UL

#define CMT_LUT_17_START_ADDR         0x00093000UL
#define CMT_LUT_17_SIZE                      0x00000600UL

#define CMT_LUT_18_START_ADDR         0x00093800UL
#define CMT_LUT_18_SIZE                      0x00000600UL

#define CMT_LUT_19_START_ADDR         0x00094000UL
#define CMT_LUT_19_SIZE                      0x00000600UL

#define CMT_LUT_20_START_ADDR         0x00094800UL
#define CMT_LUT_20_SIZE                      0x00000600UL

#define CMT_LUT_21_START_ADDR         0x00095000UL
#define CMT_LUT_21_SIZE                      0x00000600UL

#define CMT_LUT_22_START_ADDR         0x00095800UL
#define CMT_LUT_22_SIZE                      0x00000600UL

#define CMT_LUT_23_START_ADDR         0x00096000UL
#define CMT_LUT_23_SIZE                      0x00000600UL

#define CMT_LUT_31_START_ADDR         0x0008D800UL
#define CMT_LUT_31_SIZE                      0x00000600UL

#define SPLASH_1_START_ADDR          0x0009a000L
#define SPLASH_1_SIZE                       0x00032280L

#define SPLASH_2_START_ADDR          0x000cd000L
#define SPLASH_2_SIZE                       0x00032280L

#define SPLASH_3_START_ADDR          0x00100000L
#define SPLASH_3_SIZE                       0x00032280L


#define SEQ_SEQ_LUT_0          0
#define SEQ_SEQ_LUT_1          1
#define SEQ_SEQ_LUT_2          2
#define SEQ_SEQ_LUT_3          3
#define SEQ_SEQ_LUT_4          4
#define SEQ_SEQ_LUT_5          5
#define SEQ_SEQ_LUT_6          6
#define SEQ_SEQ_LUT_7          7
#define SEQ_SEQ_LUT_8          8
#define SEQ_SEQ_LUT_9          9
#define SEQ_SEQ_LUT_10          10
#define SEQ_SEQ_LUT_11          11
#define SEQ_SEQ_LUT_12          12
#define SEQ_SEQ_LUT_13          13
#define SEQ_SEQ_LUT_14          14
#define SEQ_SEQ_LUT_15          15

#define SEQ_CMT_LUT_0            0
#define SEQ_CMT_LUT_1            1
#define SEQ_CMT_LUT_2            2
#define SEQ_CMT_LUT_3            3
#define SEQ_CMT_LUT_4            4
#define SEQ_CMT_LUT_5            5
#define SEQ_CMT_LUT_6            6
#define SEQ_CMT_LUT_7            7
#define SEQ_CMT_LUT_8            8
#define SEQ_CMT_LUT_9            9
#define SEQ_CMT_LUT_10            10
#define SEQ_CMT_LUT_11            11
#define SEQ_CMT_LUT_12            12
#define SEQ_CMT_LUT_13            13
#define SEQ_CMT_LUT_14            14
#define SEQ_CMT_LUT_15            15
#define SEQ_CMT_LUT_16            16
#define SEQ_CMT_LUT_17            17
#define SEQ_CMT_LUT_18            18
#define SEQ_CMT_LUT_19            19
#define SEQ_CMT_LUT_20            20
#define SEQ_CMT_LUT_21            21
#define SEQ_CMT_LUT_22            22
#define SEQ_CMT_LUT_23           23

#define SEQ_DRC_LUT_16            24
//power_mode
#define power_mode_1_nomal     1
#define power_mode_2_save       2

//picture mode
#define picture_mode_enhanced      1
#define picture_mode_22      2  
#define picture_mode_25     3
#define picture_mode_linear	  4
#define picture_mode_film	  5
#define picture_mode_video	  6
#else
#define BITSTREAM_START_ADDR         0x00000000L
#define BITSTREAM_SIZE               0x00040000L

#define WPC_FW_0_START_ADDR          0x00040000L
#define WPC_FW_0_SIZE                0x00000ce8L

#define SEQUENCE_0_START_ADDR        0x00044000L
#define SEQUENCE_0_SIZE              0x00001000L

#define SEQUENCE_1_START_ADDR        0x00045000L
#define SEQUENCE_1_SIZE              0x00001000L

#define SEQUENCE_2_START_ADDR        0x00046000L
#define SEQUENCE_2_SIZE              0x00001000L

#define SEQUENCE_3_START_ADDR        0x00047000L
#define SEQUENCE_3_SIZE              0x00001000L

#define SEQUENCE_4_START_ADDR        0x00048000L
#define SEQUENCE_4_SIZE              0x00001000L

#define SEQUENCE_5_START_ADDR        0x00049000L
#define SEQUENCE_5_SIZE              0x00001000L

#define SEQUENCE_6_START_ADDR        0x0004a000L
#define SEQUENCE_6_SIZE              0x00001000L

#define CMT_LUT_0_START_ADDR         0x0004b200L
#define CMT_LUT_0_SIZE               0x00000600L

#define CMT_LUT_1_START_ADDR         0x0004b800L
#define CMT_LUT_1_SIZE               0x00000600L

#define CMT_LUT_2_START_ADDR         0x0004be00L
#define CMT_LUT_2_SIZE               0x00000600L

#define CMT_LUT_3_START_ADDR         0x0004c400L
#define CMT_LUT_3_SIZE               0x00000600L

#define CMT_LUT_4_START_ADDR         0x0004ca00L
#define CMT_LUT_4_SIZE               0x00000600L

#define CMT_LUT_5_START_ADDR         0x0004d000L
#define CMT_LUT_5_SIZE               0x00000600L

#define CMT_LUT_6_START_ADDR         0x0004d600L
#define CMT_LUT_6_SIZE               0x00000600L

#define DRC_TABLE_0_START_ADDR       0x0004dc00L
#define DRC_TABLE_0_SIZE             0x00000100L

#define SPLASH_0_START_ADDR          0x0004dd00L
#define SPLASH_0_SIZE                0x00032280L

#define SEQUENCE_7_START_ADDR        0x00080000L
#define SEQUENCE_7_SIZE              0x00001000L

#define SEQUENCE_8_START_ADDR        0x00081800L
#define SEQUENCE_8_SIZE              0x00001000L

#define SEQUENCE_9_START_ADDR        0x00083000L
#define SEQUENCE_9_SIZE              0x00001000L

#define CMT_LUT_7_START_ADDR         0x0008e000L
#define CMT_LUT_7_SIZE               0x00000600L

#define CMT_LUT_8_START_ADDR         0x0008e800L
#define CMT_LUT_8_SIZE               0x00000600L

#define CMT_LUT_9_START_ADDR         0x0008f000L
#define CMT_LUT_9_SIZE               0x00000600L

#define SPLASH_1_START_ADDR          0x0009a000L
#define SPLASH_1_SIZE                0x00032280L

#define SPLASH_2_START_ADDR          0x000cd000L
#define SPLASH_2_SIZE                0x00032280L

#define SPLASH_3_START_ADDR          0x00100000L
#define SPLASH_3_SIZE                0x00032280L

#define OPT_SPLASH_0_START_ADDR      0x00134000L
#define OPT_SPLASH_0_SIZE            0x000cb100L
#endif


#endif // _DLP_OPTICAL_H_
