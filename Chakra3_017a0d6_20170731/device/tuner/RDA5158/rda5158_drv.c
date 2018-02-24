/*

version 1.0 2014.3.31
 Draft version

version 1.1.0 2014.4.18
 * 添加Sleep，CSSI功能函数

version 1.2.0  2014.4.18
 * 关闭IQM ,ATV 时钟

version 1.2.1  2014.4.24
 * 更新频点的ADC设置数组，mrom adc_tbl[];


 version 1.3  2014.6.18
  * 1. 将AGC_Reset放到锁频点之后，reset之前设成fast，完成后设成slow;
  * 2. 更改rdaTVAGC()中AGC的收敛步长;

  version 1.31  2014.6.19
  * 修改100M 以下频率的LNA CAP 算法，提高精确度，提升SNR;
  *提高中频功率;
   * 降低ATV模式的VGA阈值为0x692，防止ADC饱和;

  Version 1.3.2  2014.07.01
 	*5158新版本，修改Mixer_Gain 为4个级别,每级4db;

   Version 1.3.3  2014.07.04
 	*根据revid 芯片版本确定Mixer_Gain;
 	*更新DOWNLOAD 程序，根据air 或cable 选择LNA_Gain 级别;


*/
#ifndef	_RDA5158_DRV_C
#define	_RDA5158_DRV_C


#include "RDA5158/rda5158_drv.h"
#include "RDA5158/rda5158_fw.h"

#include "drvIIC.h"
//#include "hal_extern.h"
S_RDA5158_func*       iptr = NULL;

#define C_RDA5158_LO_ADDRESS           ((U8)  0xC0)
#define RDA_5158_I2C_ADDR (((U16)TUNER_IIC_BUS<<8)| C_RDA5158_LO_ADDRESS)

static MAPI_U16   freq_if_tbl[RDA_TV_MODE_QTY] = {2900,2650,2400,2400,1500,1500,2900,2900,0,0,0};
static MAPI_U16   rfpll_sel_tbl[FREQ_LO_INDEX_QTY] = {0x10,0x8,0x4,0x2,0x1};
static MAPI_U8   mixer_lo_sel_tbl[FREQ_LO_INDEX_QTY] = {0x1,0x0,0x0,0x0,0x0};
//static MAPI_U32   freq_vco_core_tbl[FREQ_LO_INDEX_QTY] = {2,4,8,16,32};
static MAPI_U32   freq_adc_tbl[3] = {162000,172125,182250};
static MAPI_U32   freq_if_out_tbl[RDA_TV_MODE_QTY] = {4400,4650,4200,4200,4500,4500,4100,4100,RDATV_IF_FREQ ,RDATV_IF_FREQ ,RDATV_IF_FREQ };


#define usleep(x) MsOS_DelayTask(x/1000)
static  struct rda_tuner_cfg RDA_tuner_cfg;

void RDA_DELAY_MS(MAPI_U32 cnt)
{
 usleep(cnt * 1000);
}


MAPI_U32 rdaTVDetected(void)
{
    MAPI_U16 tmp;

    tmp = i2c0GetData(0xe0);
    if(tmp == RDA5880DM_PRODUCT_ID)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static RDA_TV_ADC_BY_FRE   adc_tbl[]=  //dtv
{
    //16M xtal
    {123000 ,2000,ADC_172},
    {139000,1000,ADC_172},   //(M/N) 139.25
    {321000,3000,ADC_172},

    //{147000,2000,ADC_182},
    //24M xtal
   {63000,3000,ADC_172},
   //{69000,2000,ADC_172},   
   {79000,2000,ADC_172},
   {93000,2000,ADC_172}, 
   {133000,2000,ADC_172},     //(M/N) 133.25
   {147000,2000,ADC_172},  
   {177000,2000,ADC_172},
   {189000,2000,ADC_172},
   {241000,1000,ADC_172},     //(M/N) 241.25
   {253000,1000,ADC_172},     //(M/N) 253.25 
   {403000,1000,ADC_172},     //(M/N) 403.25 
   {473000,2000,ADC_172},
   {485000,2000,ADC_172},
   {565000,3000,ADC_172},     //(M/N) 565.25 
   {619000,1000,ADC_172},     //(M/N) 619.25 
   {647000,2000,ADC_172},
   {727000,3000,ADC_172},     //(M/N) 727.25 
   {797000,2000,ADC_172},

{54000 ,2000,ADC_182},	
{69000 ,2000,ADC_182},
{81000 ,1000,ADC_182},
{85000,2000,ADC_182},
{141000,1000,ADC_182},
};




void rdaTVI2CSpeedUp(void)
{
      i2c0SendData(0xe2,0xccda);
      i2c0SendData(0xe4,0x69c4);
      i2c0SendData(0xf6,0x0000);
      i2c0SendData(0xf2,0x0000);
      i2c0SendData(0xf2,0x0001);    //dsp reset

      RDA_DELAY_MS(50);    //wait 50ms
	 
      i2c0SendData(0xea,0x8000);

      i2c1SendDataA(0x0101004e,0xfcff);    //32'h0101004e,16'hffff;



      i2c1SendDataA(0x01010040,0x9089);
      i2c1SendDataA(0x01010042,0x8a06);    //Rfpll_regbit_digi<3:0>=1010
      i2c1SendDataA(0x01010046,0x0381);
      i2c1SendDataA(0x0101004a,0xc068);
      i2c1SendDataA(0x01010062,0x2300);
      i2c1SendDataA(0x01010060,0x0000);
      i2c1SendDataA(0x01010061,0x0600);
      i2c1SendDataA(0x01010062,0x3300);    //bbpll_sdm reset
      i2c1SendDataA(0x01010065,0x0e00); 
      i2c0SendData(0xf6,0x0001);  
}

void rdaTVPowerOn(void)
{
	MAPI_U16 tmp=0;

    //switch to bbpll clk
    i2c1SendDataA(0x0141000b,0x0102);
    i2c1SendDataA(0x01010010,0x1700);    //LNA-PU-RFBP=1

	//判断芯片版本
	tmp = i2c0GetData(0xF0);
	if(tmp == 0x81)
		i2c1SendDataA(0x01010033,0xff73);	 //old mixer_gain   3级
	else
    	i2c1SendDataA(0x01010033,0x7bde);	 //new mixer_gain   4级

		
    i2c1SendDataA(0x01010034,0x888F);
    i2c1SendDataA(0x01010035,0x1000);
    i2c1SendDataA(0x01010036,0x1818);
    i2c1SendDataA(0x01010014,0x8803);
    i2c1SendDataA(0x0141003a,0x0080);
    i2c1SendDataA(0x0141003b,0x0080);

//;mix
    i2c1SendDataA(0x0101001e,0x8c3f);    //mixer_reg_bit=1100

//;adc
    i2c1SendDataA(0x01010024,0xC020);    //adc gain=0010 ; Adc_if_bit = 10

//;dac
    i2c1SendDataA(0x01010026,0x240b);    // dac range=11,Dac_cbit=00

//;im 
    i2c1SendDataA(0x0141006e,0x0040);    //imbala_bypass=0


    i2c1SendDataA(0x01410066,0x22cf);
    i2c1SendDataA(0x0141007b,0x0474);
    i2c1SendDataA(0x0141007c,0xf484);
    i2c1SendDataA(0x0141007d,0x1480);
    i2c1SendDataA(0x0141007e,0x9003);

//32'h01010031,16'h7000; //freq_clk_div_7=111
    i2c1SendDataA(0x01010031,0x7000);

    //close IQM/ATV  clock
    i2c1SendDataA(0x01800008,0x0001);     //close IQM_CLK
    i2c1SendDataA(0x00c00008,0x0001);     //close ATV_CLK
 
}


void rdaTVAGC(void)
{
/*
		//agc_lna       
		i2c1SendDataA(0x01410010,0x0018);
		i2c1SendDataA(0x01410014,0x51ff);
		i2c1SendDataA(0x01410016,0x149F);
		i2c1SendDataA(0x01410018,0x0F07);
		i2c1SendDataA(0x01410019,0xc000);
		i2c1SendDataA(0x0141001a,0x0640);
		i2c1SendDataA(0x01410028,0x1B00);
		i2c1SendDataA(0x01410029,0x1B00);
		i2c1SendDataA(0x0141002a,0x1B00);
		i2c1SendDataA(0x0141002b,0x1B00);
		i2c1SendDataA(0x0141002c,0x1B00);
		i2c1SendDataA(0x0141002d,0x1B00);
		i2c1SendDataA(0x0141002e,0x1B00);
		i2c1SendDataA(0x0141002f,0x1B00);
		
		
		//agc_mixer                       
		i2c1SendDataA(0x01410030,0x0018);
		i2c1SendDataA(0x01410031,0x00fF);
		i2c1SendDataA(0x01410032,0x6500);
		i2c1SendDataA(0x01410033,0x5f20);
		i2c1SendDataA(0x01410034,0x001d);
		            
		//agc_flt_vga
		i2c1SendDataA(0x0141003a,0x0080); //vga max          
		i2c1SendDataA(0x0141003b,0x0080);  
		
		i2c1SendDataA(0x01410042,0x6920); //vga th=692       
		i2c1SendDataA(0x01410043,0x0275);                  
		i2c1SendDataA(0x01410044,0xe0ff);                  
		i2c1SendDataA(0x01410045,0x67ff);                  
		i2c1SendDataA(0x01410047,0xf18f);                  
		i2c1SendDataA(0x01410048,0x0500); //h-d=50, 5dB 1/16 
		i2c1SendDataA(0x01410049,0x0300); //h-d=30, 3dB 1/16 
		i2c1SendDataA(0x0141004a,0x0080); //s-h=8, 0.5dB 1/16
		
		//agc_dig                          
		i2c1SendDataA(0x01410051,0x02b4); 
		i2c1SendDataA(0x01410052,0x80ff); 
		i2c1SendDataA(0x01410056,0x23b0); 
		i2c1SendDataA(0x01410057,0x455c); 
		i2c1SendDataA(0x01410058,0xcc83); 
		
		                                 
		//tuner                           
		i2c1SendDataA(0x0141006e,0x0040);
		i2c1SendDataA(0x0141007b,0x0474);
		i2c1SendDataA(0x0141007c,0xf484);
		i2c1SendDataA(0x0141007d,0x1480);
		i2c1SendDataA(0x0141007e,0x9003);
		
		//fm_hv                               
		i2c1SendDataA(0x01c10030,0x0064);    
		i2c1SendDataA(0x01c10031,0x0030);    
		i2c1SendDataA(0x01c10032,0x032a);    
		i2c1SendDataA(0x01c10033,0x0f09);    
		i2c1SendDataA(0x01c10034,0x0144);    
*/

    i2c1SendDataA(0x01010018,0x00C0);  //lna_pdt_g=1100
    i2c1SendDataA(0x0101002e,0x82D8); //Auxadc_gain_pkd=110
    i2c1SendDataA(0x0101002c,0x4c88);
    i2c1SendDataA(0x01010050,0x00c0);
    i2c1SendDataA(0x01010066,0xf444);
    i2c1SendDataA(0x01010067,0x4444);   //LNA_VBC=0100
    i2c1SendDataA(0x01010068,0xffff);
    i2c1SendDataA(0x01010069,0xfff0);
    i2c1SendDataA(0x0101006a,0x0123);
    i2c1SendDataA(0x0101006b,0x4567);

    i2c1SendDataA(0x01410010,0x0018);
    i2c1SendDataA(0x01410014,0x51ff);
    i2c1SendDataA(0x01410016,0x139F);
	i2c1SendDataA(0x01410017,0x114F);
    i2c1SendDataA(0x01410018,0x0F07); 
    i2c1SendDataA(0x01410019,0xc000);
    i2c1SendDataA(0x0141001a,0x0640);
    i2c1SendDataA(0x01410028,0x1B00);
    i2c1SendDataA(0x01410029,0x1B00);
    i2c1SendDataA(0x0141002a,0x1B00);
    i2c1SendDataA(0x0141002b,0x1B00);
    i2c1SendDataA(0x0141002c,0x1B00);
    i2c1SendDataA(0x0141002d,0x1B00);
    i2c1SendDataA(0x0141002e,0x1B00);
    i2c1SendDataA(0x0141002f,0x1B00);

 
    i2c1SendDataA(0x01410030,0x0018);
    i2c1SendDataA(0x01410031,0x00ff);
    i2c1SendDataA(0x01410032,0x6500); 
	i2c1SendDataA(0x01410033,0x5f20);   
    i2c1SendDataA(0x01410034,0x001d);

    i2c1SendDataA(0x01410045,0x67ff);
    i2c1SendDataA(0x01410042,0x6920);   //vga th=692
    i2c1SendDataA(0x01410043,0x0275); 
    i2c1SendDataA(0x01410044,0xE0FF); 	
    i2c1SendDataA(0x01410047,0xf18f);   
    i2c1SendDataA(0x01410048,0x0500);   //h-d=50, 5dB 1/16
    i2c1SendDataA(0x01410049,0x0300);   //h-d=20, 2dB 1/16
    i2c1SendDataA(0x0141004a,0x0080);   //s-h=8, 0.5dB 1/16

    i2c1SendDataA(0x01410033,0x5f20);   
    i2c1SendDataA(0x01410032,0x6500);   

    i2c1SendDataA(0x01410051,0x02b4);     
    i2c1SendDataA(0x01410052,0x80ff); 
    i2c1SendDataA(0x01410056,0x23b0);   //power=0dBm
    i2c1SendDataA(0x01410057,0x455c);   
    i2c1SendDataA(0x01410058,0xcc83); 

    i2c1SendDataA(0x0141000a,0x0000);    //tuner reset
    i2c1SendDataA(0x0141000a,0x0007);

    i2c1SendDataA(0x01010020,0x0007);    //filter reset
    i2c1SendDataA(0x01010020,0x0027);

    i2c1SendDataA(0x01010022,0xB684);    //vga reset
    i2c1SendDataA(0x01010022,0xB68c);    //Adc_buffer_ibit=10

    i2c1SendDataA(0x01010028,0x2190);    //dac reset
    i2c1SendDataA(0x01010028,0x21B0);    //buf_gain=1

}

void rdaDTVSETTING(RDA_TUNER_CFG tuner_cfg)
{
    i2c1SendDataA(0x01010016,0x0ef7);    //add 0306
    i2c1SendDataA(0x0101004e,0xfcff);
    i2c1SendDataA(0x01410042,0x6920);
    //i2c1SendDataA(0x01410056,0x2340);	
    i2c1SendDataA(0x01410066,0x22cf);
    i2c1SendData(PAGE_AGC_TUNER,0x10032,tuner_cfg->i2vth_dtvh);
    i2c1SendData(PAGE_AGC_TUNER,0x10033,tuner_cfg->i2vth_dtvl);
}

void rdaATVSETTING(RDA_TUNER_CFG tuner_cfg)
{
    i2c1SendDataA(0x0101004e,0xfccf);
    i2c1SendDataA(0x01410042,0x6920);
    //i2c1SendDataA(0x01410056,0x2360);	
    i2c1SendDataA(0x01410066,0x22ef);
    i2c1SendData(PAGE_AGC_TUNER,0x10032,tuner_cfg->i2vth_dtvh);
    i2c1SendData(PAGE_AGC_TUNER,0x10033,tuner_cfg->i2vth_dtvl);
}

void rdaCVBSSETTING(void)
{
    i2c1SendDataA(0x0101004e,0xfbff);
    i2c1SendDataA(0x01410056,0x2360);
    i2c1SendDataA(0x01410042,0x6920);
    i2c1SendDataA(0x01410031,0x0046);
    i2c1SendDataA(0x01410033,0x3000);
    
    //cvbs_pal_dk_162m
    i2c1SendDataA(0x01410056,0x2360);
    i2c1SendDataA(0x00c00000,0x0000);
    i2c1SendDataA(0x01800000,0x0000);
    i2c1SendDataA(0x01840010,0xaaaa);
    i2c1SendDataA(0x01840011,0x002a);
    i2c1SendDataA(0x01840017,0x0002);
    i2c1SendDataA(0x00c1001b,0x03c0);
    i2c1SendDataA(0x00c10026,0x0001);
    i2c1SendDataA(0x00c10027,0x0a00);
    i2c1SendDataA(0x00c00000,0x0001);
    i2c1SendDataA(0x01800000,0x0001);
    i2c1SendDataA(0x00c1001f,0x0001);
}

void rdaTVSetATSCMode(RDA_TV_ATSC_MODE mATSC_Mode)
{
	
	if(mATSC_Mode == LNA_ATSC_AIR) 
		i2c1SendDataA(0x00831e08,0x0001);
	else
		i2c1SendDataA(0x00831e08,0x0000);
}

void rdaTV8051Init(void)
{
    i2c1SendDataA(0x00831e00,0x0390);
    i2c1SendDataA(0x00831e01,0x00e0);
    i2c1SendDataA(0x00831e02,0x01b0);
//    i2c1SendDataA(0x00831e00,0x03D0);
//    i2c1SendDataA(0x00831e01,0x0120);
//    i2c1SendDataA(0x00831e02,0x0240);    
//    i2c1SendDataA(0x00831e03,0x0650);
//    i2c1SendDataA(0x00831e04,0x0450);
//    i2c1SendDataA(0x00831e05,0x0580);
    i2c1SendDataA(0x00831e06,0x0058);	
    i2c1SendDataA(0x00831e07,0x0058);

}

void rdaTV8051Start(void)
{
    i2c1SendDataA(0x00800000,0x0001);
}


void rdaTV8051Stop(void)
{
    i2c1SendDataA(0x00800000,0x0000);
    i2c1SendDataA(0x0141001C,0x0780);
    i2c1SendDataA(0x01410034,0x0002);
    i2c1SendDataA(0x0141004B,0x0608);
    i2c1SendDataA(0x0141004C,0xe880);	
}
void rdaDemodFirmwareDL()
{
    MAPI_U32 offset=0x30000;
    MAPI_U32 size=0;
    MAPI_U32 i=0;
    MAPI_U16 buff=0;

    size = sizeof(rda_code);

    for(i=0;i<size;i+=2)
    {
        buff = rda_code[i];
        buff = buff<<8;
        buff = buff|rda_code[i+1];
        i2c1SendData(PAGE_DEMOD_SCU,offset,buff);
		offset = offset + 1;
    }
}

void rdaTVSetDemod(RDA_TUNER_CFG tuner_cfg)
{

    if(tuner_cfg->demod_mach == MSB3393)
    {
        ;i2c1SendDataA(0x01410056,0x239c);
	 ;i2c1SendDataA(0x01410056,0x2365);
	 i2c1SendDataA(0x01410056,0x2380);
        tuner_cfg->freq_if_out = 6000;
    }
    else if(tuner_cfg->demod_mach == X)
    {
        i2c1SendDataA(0x01410056,0x237d);
        tuner_cfg->freq_if_out = RDATV_IF_FREQ;
    }
}

void rdaTVXtalSet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U16 tmp=0;

    if(tuner_cfg->xtal_mode == XTAL_SOLO_MODE)
    {
        tmp = i2c0GetData(0xe4);
        tmp &= 0xfbff;    //e4[10] = 0
        tmp |= 0x0300;    //e4[9:8] = 1
        i2c0SendData(0xe4,tmp);

        tmp = i2c0GetData(0xe6);
        tmp &= 0xfff7;    //0xe6[3]=0
        i2c0SendData(0xe6,tmp);

        tmp = i2c0GetData(0xe8);
        tmp &= 0x0fdf;    //e8[15:12] = 0, e8[5]=0, e8[4:3] = 1
        tmp |= 0x0018;
        i2c0SendData(0xe8,tmp);

        tmp = i2c1GetData(PAGE_AFE_SDM,0x10046);
        tmp |= 0x0200;    //	tmp |= (1<<9);
        tmp &= 0x7fff;    //tmp &= ~(1<<15);
        i2c1SendData(PAGE_AFE_SDM,0x10046,tmp);

        tmp = i2c1GetData(PAGE_AFE_SDM,0x10020);
        tmp &= 0x1fff;    //20[15:13] = 0
        i2c1SendData(PAGE_AFE_SDM,0x10020,tmp);
    }
    else
    {
        ;
    }
}

void rdaTVIQSwap(MAPI_U8 flag)
{
    MAPI_U16 tmp;

    tmp = i2c1GetData(PAGE_AFE_SDM,0x10020);

    if(flag)
    {
        tmp |= 0x1000;
    }
    else
    {
         tmp &= 0xefff;
    }

    i2c1SendData(PAGE_AFE_SDM,0x10020,tmp);
}

MS_BOOL rdaTVTunerOpen(RDA_TUNER_CFG tuner_cfg)
{
    MS_BOOL bRet=TRUE;
    MS_U8 u8Value[2];
    /* Variable declarations */
    //mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(RDA_5158_I2C_ADDR);
    bRet &= MDrv_IIC_WriteBytes((U16)((TUNER_IIC_BUS<<8)|RDA_5158_I2C_ADDR), 0, NULL, 2,u8Value);
    if (bRet ==FALSE)
    {
        printf(" ERROR in RDA5158_WriteReg !!! \n");
    }
    return bRet;	
	 
    //iptr->SetSpeed(40);// about 24k
    //bRet &= iptr->SetSpeed(40);
    rdaTVI2CSpeedUp();
    //iptr->SetSpeed(100);// about 79k
    //bRet &= iptr->SetSpeed(100);
	
    rdaTVPowerOn();
    rdaTVAGC();
    
    rdaTVI2vTh(tuner_cfg);
    rdaTVXtalSet(tuner_cfg);
    rdaTVSetDemod(tuner_cfg);
	
    rdaTV8051Init();     //8051 AGC Setting
    rdaTV8051Stop();
    rdaDemodFirmwareDL();      //8051 download
}



void rdaTVModeIndexSet(RDA_TUNER_CFG tuner_cfg,RDA_TV_MODE mode)
{
    tuner_cfg->tv_mode_index = mode;
}

void rdaTVLNAIndexGet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U32 freq_lo;

    freq_lo = tuner_cfg->freq_lo;
    if((tuner_cfg->lna_mode == LNA_ATSC_MODE)||(tuner_cfg->lna_mode == LNA_DTMB_MODE)||(tuner_cfg->lna_mode == LNA_ATV_MODE))
    {
        if((freq_lo>540000)&&(freq_lo<=870000))
        {
            tuner_cfg->lna_index = LNA_SEL_L1;
        }
        else if((freq_lo>290000)&&(freq_lo<=540000))
        {
            tuner_cfg->lna_index = LNA_SEL_L2;
        }
        else if((freq_lo>133000)&&(freq_lo<=290000))
        {
            tuner_cfg->lna_index = LNA_SEL_L3;
        }
        else if((freq_lo>48000)&&(freq_lo<=133000))
        {
            tuner_cfg->lna_index = LNA_SEL_L4;
        }
        else
        {
            tuner_cfg->lna_index = 0xff;
        }
    }
    else if((tuner_cfg->lna_mode == LNA_DVBT_MODE)||(tuner_cfg->lna_mode == LNA_ISDBT_MODE))
    {
        if((freq_lo>770000)&&(freq_lo<=870000))
        {
            tuner_cfg->lna_index = LNA_SEL_L1;
        }
        else if((freq_lo>380000)&&(freq_lo<=770000))
        {
            tuner_cfg->lna_index = LNA_SEL_L2;
        }
        else if((freq_lo>133000)&&(freq_lo<=380000))
        {
            tuner_cfg->lna_index = LNA_SEL_L3;
        }
        else if((freq_lo>48000)&&(freq_lo<=133000))
        {
            tuner_cfg->lna_index = LNA_SEL_L4;
        }
        else
        {
            tuner_cfg->lna_index = 0xff;
        }
    }
    else if(tuner_cfg->lna_mode == LNA_DVBC_MODE)
    {
    	if((freq_lo>770000)&&(freq_lo<=870000))
    	{
    		tuner_cfg->lna_index = LNA_SEL_L1;
    	}
    	else if((freq_lo>410000)&&(freq_lo<=770000))
    	{
    		tuner_cfg->lna_index = LNA_SEL_L2;
    	}
    	else if((freq_lo>210000)&&(freq_lo<=410000))
    	{
    		tuner_cfg->lna_index = LNA_SEL_L3;
    	}
    	else if((freq_lo>48000)&&(freq_lo<=210000))
    	{
    		tuner_cfg->lna_index = LNA_SEL_L4;
    	}
    	else
    	{
    		tuner_cfg->lna_index = 0xff;
    	}
    }
    else
    {
        tuner_cfg->lna_index = 0xff;
    }
}

void rdaTVFreqloIndexSet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U32 freq_lo_m;

    freq_lo_m = tuner_cfg->freq_lo;
    
    if(freq_lo_m<=900000&&freq_lo_m>435000)
    {
        tuner_cfg->freq_lo_index = FREQ_LO_INDEX_2;
    }
    else if(freq_lo_m<=435000&&freq_lo_m>217500)
    {
        tuner_cfg->freq_lo_index = FREQ_LO_INDEX_4;
    }
    else if(freq_lo_m<=217500&&freq_lo_m>108750)
    {
        tuner_cfg->freq_lo_index = FREQ_LO_INDEX_8;
    }
    else if(freq_lo_m<=108750&&freq_lo_m>54375)
    {
        tuner_cfg->freq_lo_index = FREQ_LO_INDEX_16;
    }
    else if(freq_lo_m<=54375&&freq_lo_m>27187)
    {
        tuner_cfg->freq_lo_index = FREQ_LO_INDEX_32;
    }
    else
    {
        ;
    }
}



void rdaTVPllCalSet(RDA_TUNER_CFG tuner_cfg)
{
//    MAPI_U16 pll_cal_each_cnt_time;
    MAPI_U32 pll_cal_freq_compare;

//    pll_cal_each_cnt_time = xtal*2;
    i2c1SendData(PAGE_AFE_SDM,0x1003a,tuner_cfg->xtal*2);

    pll_cal_freq_compare = (tuner_cfg->freq_vco_core*2)/1000;
    
    i2c1SendData(PAGE_AFE_SDM,0x10039,pll_cal_freq_compare>>16);    //write 39
    i2c1SendData(PAGE_AFE_SDM,0x10038,pll_cal_freq_compare);    // write 38

    i2c1SendData(PAGE_AFE_SDM,0x1003c,0x0000);
    i2c1SendData(PAGE_AFE_SDM,0x1003c,0x0001);    //pll cal reset
}

void rdaTVRFPLLSDMSet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U32 rfpll_sdm_freq=0;
    MAPI_U32 freq_tmp=tuner_cfg->freq_vco_core;
    MAPI_U16 tmp;
    
    if(tuner_cfg->xtal_mode == XTAL_SOLO_MODE)
    {
        rfpll_sdm_freq = rdaTVMulDivCompensate(freq_tmp,tuner_cfg->xtal*1000,22);    //fix(freq_vco_core/xtal*2^22)
    }
    else
    {
        rfpll_sdm_freq = rdaTVMulDivCompensate(freq_tmp,tuner_cfg->xtal*1000/tuner_cfg->mdll_n,22);    //fix(freq_vco_core/xtalmdll_n*2^22)
    }

    i2c1SendData(PAGE_AFE_SDM,0x10064,rfpll_sdm_freq>>16);
    i2c1SendData(PAGE_AFE_SDM,0x10063,rfpll_sdm_freq);

    tmp = i2c1GetData(PAGE_AFE_SDM,0x10065);
    tmp &= 0xf7ff;;

    i2c1SendData(PAGE_AFE_SDM,0x10065,tmp);

    tmp |= 0x0800;
    i2c1SendData(PAGE_AFE_SDM,0x10065,tmp);    //rfpll_sdm reset
}

RDA_TV_ADC_INDEX rdaTVGetAdcByFreq(MAPI_U32 freq)
{
	MAPI_U16 i;
	
	for(i=0;i<(sizeof(adc_tbl)/sizeof(RDA_TV_ADC_BY_FRE));i++)
	{
		if((freq>=adc_tbl[i].freq-adc_tbl[i].delta)&&(freq<=adc_tbl[i].freq+adc_tbl[i].delta))
		    return adc_tbl[i].adc;
	}

	return ADC_162;
}

void rdaTVBBPLLSDMSet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U32 bbpll_sdm_freq;
    MAPI_U16 tmp;

    if(tuner_cfg->xtal_mode == XTAL_SOLO_MODE)
    {
        bbpll_sdm_freq = rdaTVMulDivCompensate(freq_adc_tbl[tuner_cfg->freq_adc_index],tuner_cfg->xtal*1000,24);
    }
    else
    {
        bbpll_sdm_freq = rdaTVMulDivCompensate(freq_adc_tbl[tuner_cfg->freq_adc_index],tuner_cfg->xtal/tuner_cfg->mdll_n,24);
    }

	i2c1SendData(PAGE_AFE_SDM,0x10061,bbpll_sdm_freq>>16);
	i2c1SendData(PAGE_AFE_SDM,0x10060,bbpll_sdm_freq);

    tmp = i2c1GetData(PAGE_AFE_SDM,0x10062); 
    tmp &= 0xefff;

    i2c1SendData(PAGE_AFE_SDM,0x10062,tmp);

    tmp |= 0x1000;
    i2c1SendData(PAGE_AFE_SDM,0x10062,tmp);    //bbpll_sdm reset

    tmp = i2c1GetData(PAGE_AFE_SDM,0x1002e); 
    tmp &= ~(0x07<<8);

    if(tuner_cfg->chip_mode == TUNER_CHIP_MODE_IFOUT)
    {
       tmp |= (0x02<<8);
    }
    else
    {
        if(tuner_cfg->tv_mode_index < RDA_DTV_6M)
        {
            if((tuner_cfg->freq_adc_index == ADC_162) && (tuner_cfg->tv_mode_index < RDA_DTV_6M))
            {
                tmp |= (0x02<<8);
            }
            else if((tuner_cfg->freq_adc_index == ADC_182))
            {
                tmp |= (0x03<<8);
            }
            else
            {
                tmp |= (0x02<<8);
            }
        }
        else
        {
            tmp |= (0x02<<8);
        }
    }
    i2c1SendData(PAGE_AFE_SDM,0x1002e,tmp);
}


void rdaTVTunerModeSet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U16 tmp;

    tmp = i2c1GetData(PAGE_AGC_TUNER,0x1000b); 
    tmp &= 0xefff;    //set BB_ADC_MODE

    tmp &= 0xf8ff;

    if(tuner_cfg->chip_mode == TUNER_CHIP_MODE_CVBS)
    {
        tmp |= 0x0200;
    }
    else if(tuner_cfg->chip_mode == TUNER_CHIP_MODE_IFOUT)
    {
        if(tuner_cfg->tv_mode_index>=RDA_DTV_6M)
        {
        	tmp |= 0x0500;
        }
        else
        {
        	tmp |= 0x0100;    
        }							//set IFOUT
    }
    else
    {}
    
    tmp &= 0xff8f;
    if(tuner_cfg->tv_mode_index>=RDA_DTV_6M)
    {
    	tmp |= ((tuner_cfg->tv_mode_index-3)<<4);    //set tv mode
    }
    else
    {
    	tmp |= ((tuner_cfg->tv_mode_index)<<4);    //set tv mode  
    }
	   
    tmp &= 0xfff8;
    tmp |= ((tuner_cfg->freq_adc_index)+2);    //set clock mode

    i2c1SendData(PAGE_AGC_TUNER,0x1000b,tmp);

}

void rdaTVRfBpset(RDA_TUNER_CFG tuner_cfg,MAPI_U8 s_value)
{

    MAPI_U16 tmp,tmp_14,tmp_a;

    tmp = i2c1GetData(PAGE_AFE_SDM,0x1001c);

    tmp_14 = i2c1GetData(PAGE_AFE_SDM,0x10014);
    tmp_14 = tmp_14&0x0fff;
    tmp_a = 0x0008;
    tmp_a = tmp_a>>tuner_cfg->lna_index;
    tmp_a = tmp_a<<12;

    if(s_value)
    {
        tmp |= 0x4000;
        tmp_14 = tmp_14|tmp_a;
    }
    else
    {
        tmp = tmp&0xbfff;
    }

    i2c1SendData(PAGE_AFE_SDM,0x10014,tmp_14);
    i2c1SendData(PAGE_AFE_SDM,0x1001c,tmp);

}

void rdaTVIfOutSet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U32 freq_shift;
    MAPI_U16 tmp;

    if(tuner_cfg->tv_mode_index >= RDA_DTV_6M)
    {
        freq_shift = tuner_cfg->freq_if_out;
    }
    else
    {
        freq_shift = freq_if_out_tbl[tuner_cfg->tv_mode_index];
    }

    tmp = rdaTVMulDivCompensate(freq_shift,freq_adc_tbl[tuner_cfg->freq_adc_index],17);

    tmp |= 0x8000;    //set angle in

    i2c1SendData(PAGE_AGC_TUNER,0x10079,tmp);
}

void large_int_64div32(MAPI_U32* psa,MAPI_U32 dwsb,MAPI_U32* psd,MAPI_U32* psr)
{
    MAPI_U32 dwR,dwD0,dwR0;
    MAPI_U8 i=0,ns=0;
    MAPI_U32 qwR[2] = {0};
    MAPI_U32 dwA0 = psa[1];
    MAPI_U32 dwA1 = psa[0];
    MAPI_U32 dwD1 = dwA1 / dwsb;
    MAPI_U32 dwR1 = dwA1 % dwsb;
    
    dwR	= dwR1;
    i = 0;
    while(dwR)
    {
        dwR >>= 1;
        i ++;
    }
    if(i)
    {
        ns = 32 - i;
        dwR = ( dwA0 << ns ) >> ns;
        dwA0 = ( dwA0 >> i ) | ( dwR1 << ns ) ;
    }
    
    dwD0 = dwA0 / dwsb;
    dwR0 = dwA0 % dwsb;
    
    /*
        ULARGE_INTEGER ulD = { dwD0  , 0  };
        ulD.QuadPart <<= i;
        ulD.HighPart += dwD1;
      
    	  QWORD qwR = ((QWORD)dwR0 << i) + dwR ;
    	  */

    if(i>0)
    {
        qwR[0] = dwR0>>ns;
    }
    
    qwR[1] = dwR0<<i;
    qwR[1] += dwR;	

    //	  qwR = dwD0<<i|(dwD1<<32)
    if((qwR[1] > dwsb) || (qwR[0]>0))
    {
        large_int_64div32((MAPI_U32 *)qwR,dwsb,(MAPI_U32 *)psd,psr);
        //*(QWORD*)psd = dwD0<<i|(dwD1<<32) + *(QWORD*)psd;
        *psd += dwD0>>ns;
        *psd += dwD1;
        if(*(psd+1)+dwD0 < dwD0)
        {
            *psd += 1;
        }
        *(psd+1) += (dwD0<<i);
    }
    else if(qwR[1] == dwsb)
    {
        //*(QWORD*)psd = dwD0<<i|(dwD1<<32) + 1;        
        *psd = dwD0>>ns;
        *(psd+1) += dwD0<<i;
        *psd += dwD1;
        if(*(psd+1) == 0xffffffff)
        {
            *psd += 1;
        }
        *(psd+1) += 1;
        *psr = 0;
    }
    else
    {
        //*(QWORD*)psd = dwD0<<i|(dwD1<<32);
        if(i>0)
        {
            *psd = dwD0>>ns;
        }
        
        *(psd+1) += dwD0<<i;
        *psd += dwD1;
        *psr = *((MAPI_U32 *)qwR);
    }
    
    //*psr = (DWORD)( *(QWORD*)psa - *(QWORD*)psd * dwsb );
}

/*
lna_cap = ((10^12)/(((2*Pi*freq)^2)*A)-B*1000)/D
*/
MAPI_U16 rdaTVLNACapGet(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U32 freq;
    MAPI_U32 div_larg[2] = {0x2330429A,0x7CAE2117};    //0x2330429A7CAE2116+1
//    MAPI_U32 div_larg[2] = {0x5a1525,0x6286dc7e};    //0x5A15256286DC7D+1
    MAPI_U32 ret[2] = {0};
    MAPI_U32 psr,auto_A,auto_B,auto_D;
    MAPI_U32 tmp;

    div_larg[0] = 0x2330429A;
    div_larg[1] = 0x7CAE2117;
    freq = tuner_cfg->freq_lo;

    if(tuner_cfg->lna_index == LNA_SEL_L1)
    {
        auto_A = 62;
        auto_B = 50400;
        auto_D = 577;
        goto DIV_BG;
    }
    
    if((tuner_cfg->lna_mode == LNA_ATSC_MODE)||(tuner_cfg->lna_mode == LNA_ATV_MODE)||(tuner_cfg->lna_mode == LNA_DTMB_MODE))
    {
        if(tuner_cfg->lna_index == LNA_SEL_L2)
        {
            auto_A = 150;
            auto_B = 54600;
            auto_D = 691;
        }
        else if(tuner_cfg->lna_index == LNA_SEL_L3)
        {
            auto_A = 470;
            auto_B = 58300;
            auto_D = 1045;
        }
        else if(tuner_cfg->lna_index == LNA_SEL_L4)
        {
            auto_A = 2200;
            auto_B = 60500;
            auto_D = 1427;
        }
		else
		{
          tmp = 0xffff;
          goto END;
		}
    }
    else if((tuner_cfg->lna_mode == LNA_DVBT_MODE)||(tuner_cfg->lna_mode == LNA_ISDBT_MODE))
    {
        if(tuner_cfg->lna_index == LNA_SEL_L2)
        {
            auto_A = 68;
            auto_B = 61200;
            auto_D = 779;
        }
        else if(tuner_cfg->lna_index == LNA_SEL_L3)
        {
            auto_A = 470;
            auto_B = 58300;
            auto_D = 1045;
        }
        else if(tuner_cfg->lna_index == LNA_SEL_L4)
        {
            auto_A = 2200;
            auto_B = 60500;
            auto_D = 1427;
        }
		else
		{
          tmp = 0xffff;
          goto END;
		}
    }
    else if(tuner_cfg->lna_mode == LNA_DVBC_MODE)
    {
        if(tuner_cfg->lna_index == LNA_SEL_L2)
        {
            auto_A = 68;
            auto_B = 61200;
            auto_D = 779;
        }
        else if(tuner_cfg->lna_index == LNA_SEL_L3)
        {
            auto_A = 270;
            auto_B = 50300;
            auto_D = 886;
        }
        else if(tuner_cfg->lna_index == LNA_SEL_L4)
        {
            auto_A = 820;
            auto_B = 59400;
            auto_D = 1326;
        }
		else
		{
          tmp = 0xffff;
          goto END;
		}
    }
    else
    {
        tmp = 0xffff;
        goto END;
    }

DIV_BG:
    large_int_64div32((MAPI_U32 *)div_larg,freq,(MAPI_U32 *)ret,(MAPI_U32 *)&psr);
    div_larg[0] = 0;
    div_larg[1] = 0;

    psr = ret[0];
    psr = ret[1];
    large_int_64div32((MAPI_U32 *)ret,freq,(MAPI_U32 *)div_larg,(MAPI_U32 *)&psr);

    psr = div_larg[0];
    psr = div_larg[1];

    tmp = div_larg[1];

//    if(tuner_cfg->lna_index != LNA_SEL_L1)
//    {
        tmp = tmp/auto_A;
//    }

    tmp = tmp-auto_B;
    tmp = tmp/auto_D;

    tmp = tmp;



        if(freq<=60000)
        {
            tmp=0x13ff;
        }
        else if((freq>60000)&&(freq<=65000))
        {
           tmp=tmp+70;
        }
        else if ((freq>65000)&&(freq<=86000))
        {
           tmp=tmp+35;
        }

	    else if(freq==61250)
        {
            tmp=0x13e8;
        }

		else if(freq==67250)
        {
            tmp=0x139f;
        }

	       else if(freq==77250)
        {
            tmp=0x1381;
        }

	     if(freq==83250)
        {
            tmp=0x135f;
        }

END:
    return tmp;




	
}

void rdaTVI2vTh(RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U16 tmp,M,N;

    i2c1SendData(PAGE_AFE_SDM,0x1004E,0xff7f);
    RDA_DELAY_MS(50);

	tmp = i2c1GetData(PAGE_AGC_TUNER,0x10035);
	tmp &= 0xfff0;
    M = tmp>>4;
	N = M+500;

    tmp = tmp|(N<<4);
    tuner_cfg->i2vth_dtvh = tmp;
	tuner_cfg->i2vth_dtvl = tuner_cfg->i2vth_dtvh>>4;
	tuner_cfg->i2vth_dtvl = tuner_cfg->i2vth_dtvl>>2;
	tuner_cfg->i2vth_dtvl=(tuner_cfg->i2vth_dtvl<<4);
	
	
	tuner_cfg->i2vth_atvh = tmp+0x2580;
	tuner_cfg->i2vth_atvl= tuner_cfg->i2vth_atvh>>4;
	tuner_cfg->i2vth_atvl = tuner_cfg->i2vth_atvl>>2;
	tuner_cfg->i2vth_atvl=(tuner_cfg->i2vth_atvl<<4);

}

MAPI_U32 rdaTVMulDivCompensate(MAPI_U32 par1,MAPI_U32 par2,MAPI_U32 par3)
{
	MAPI_U32 result=0;
	MAPI_U32 div_int,div_remain,div_remain1;
	MAPI_U32 mremain,mb,fremain;

	div_int = par1/par2;
	div_remain = par1%par2;

	div_int <<= par3;
	result += div_int;

	mremain = ((MAPI_U32)1<<(32-par3))-1;
	mb = div_remain/mremain;
	fremain = div_remain%mremain;

	div_int = (fremain<<par3)/par2;
	result += div_int;

	div_remain1 = (fremain<<par3)%par2;

	div_int = (mremain<<par3)/par2;
	div_int *= mb;
	result += div_int;

	div_remain = (mremain<<par3)%par2;
	div_remain *= mb;
	div_remain += div_remain1;
	
	div_int = div_remain/par2;
	result += div_int;

	div_remain1 = div_remain%par2;
	div_remain1 *= 2;

	if(div_remain1 >= par2)
		result += 1;
	
	return result;
	
}

void rdaTVSleepnoloop(void)
{
	//500uA
	i2c1SendData(PAGE_AFE_SDM,0x1004E,0x0);
	i2c0SendData(0xe2,0xc4da);
}

void rdaTVSleepwithloop(void)
{
	//12mA
	i2c1SendData(PAGE_AFE_SDM,0x1004E,0x0030);
	i2c0SendData(0xe2,0xc4da);	
}

MAPI_U32  RDATVGetIntensity(void)
{
	MAPI_U32 Lna1=0;
	MAPI_U32 Lna3=0;
	MAPI_U32 I2v=0;
	MAPI_U32 Filter=0;
	MAPI_U32 Vga1=0;
	MAPI_U32 Vga2=0;
	MAPI_U32 digital_polarity=0;
	MAPI_U32 digital=0;
	MAPI_U16 temp = 0;
	MAPI_U32 lna_gain1 = 0;
	MAPI_U32 lna_gain3= 0;
	MAPI_U32 lna_gain= 0;
	MAPI_U32 i2v_gain = 0;
	MAPI_U32 filter_gain = 0;
	MAPI_U32 vga_gain1 = 0;
	MAPI_U32 vga_gain2 = 0;
	MAPI_U32 digital_gain_p=0;
	MAPI_U32 digital_gain_n=0;
	MAPI_U32 intensity;
	MAPI_U16 lna_gain_tab[9]={0,6,11,14,17,20,23,26,30};


	//lna gain   	
	temp = i2c1GetData(PAGE_AGC_TUNER,0x1001C);
	Lna3 = temp & 0x003f;
	lna_gain3=(Lna3*13) >> 6;
	Lna1= (temp>>12)&0x0007; 
	if(Lna1 == 7)
	{
		temp = i2c1GetData(PAGE_AFE_SDM,0x10069);
		temp = temp & 0x000f;
		if(temp == 0x0)
			Lna1 = 8;
	}
	lna_gain1=lna_gain_tab[Lna1];
	lna_gain = lna_gain1+lna_gain3;
	
	//i2v gain
	temp = i2c1GetData(PAGE_AGC_TUNER,0x10034);
	I2v = (temp>>3) & 0x0003;
	if(I2v < 3)
		i2v_gain = I2v*6;
	else 
		i2v_gain = 12;

	//filter gain
	temp = i2c1GetData(PAGE_AGC_TUNER,0x1004B);
	Filter= (temp>>13)&0x3;
	if(Filter < 3)
		filter_gain = Filter*6;
	else 
		filter_gain = 12;

	//vga gain
	temp = i2c1GetData(PAGE_AGC_TUNER,0x1004B);
	Vga1= temp&0x00ff;
	vga_gain1 = (Vga1*6) >> 7;
	temp = i2c1GetData(PAGE_AGC_TUNER,0x1004C);
	Vga2= temp&0x00ff;
	vga_gain2 = (Vga2*6) >> 7;

	//digital gain
	temp = i2c1GetData(PAGE_AGC_TUNER,0x1004B);
	digital= temp & 0x7fff;
	digital_polarity= (temp>>11)&0x1;	

	if(digital_polarity==0)
	{
		digital_gain_p=digital >> 8;
		digital_gain_n = 0;
	}

	else if(digital_polarity==1)  
	{
		digital_gain_n=(0x7fff-digital) >> 8;
		digital_gain_p = 0;
	}

	intensity = lna_gain+i2v_gain+filter_gain+vga_gain1;
	intensity = intensity+vga_gain2+digital_gain_p-digital_gain_n-10;

	return intensity;
}

MAPI_U16 rdaTVSingalStrength(void)
{
	MAPI_U32 vgain = 0;
	MAPI_U16 signal_strength = 0;

	vgain = RDATVGetIntensity();
	if(vgain > 100)
		vgain = 100;
	signal_strength = 100 - vgain;

	if(signal_strength > 90)
	{
		signal_strength = 90;
	}
	if(signal_strength < 20)
	{
		signal_strength = 20;
	}

	return signal_strength;
}


void rdaTVSetFreq_tune(MAPI_U32 freq,MAPI_U32 bw, RDA_TUNER_CFG tuner_cfg)
{
    MAPI_U16 tmp,lna_cap,tmp_a;

    tuner_cfg->freq = freq;
    tuner_cfg->freq_lo = freq + freq_if_tbl[tuner_cfg->tv_mode_index];
    rdaTVLNAIndexGet(tuner_cfg);
    rdaTVFreqloIndexSet(tuner_cfg);

    lna_cap = rdaTVLNACapGet(tuner_cfg);
    lna_cap &= 0x00ff;
    tmp = i2c1GetData(PAGE_AFE_SDM,0x10010);
    tmp &= 0xff00;
    tmp |= lna_cap;
    i2c1SendData(PAGE_AFE_SDM,0x10010,tmp);

    tmp = i2c1GetData(PAGE_AFE_SDM,0x10069);
    tmp &= 0xfff0;
    if(tuner_cfg->lna_index == LNA_SEL_L4)
    {
        tmp |= 0x0008;
    }
    i2c1SendData(PAGE_AFE_SDM,0x10069,tmp);

    tmp = i2c1GetData(PAGE_AFE_SDM,0x10014);
    tmp &= 0x00ff;
    tmp_a = 0x0008;
    tmp_a = tmp_a>>(tuner_cfg->lna_index);
    tmp_a = tmp_a<<8;
    tmp |= tmp_a;
    tmp_a = tmp_a<<4;
    tmp = tmp|tmp_a;
    i2c1SendData(PAGE_AFE_SDM,0x10014,tmp);
      
    tuner_cfg->freq_vco_core = (tuner_cfg->freq_lo)<<(tuner_cfg->freq_lo_index+1);
    tmp = i2c1GetData(PAGE_AFE_SDM,0x1004a);
    tmp &= 0x83ff;
    tmp_a = rfpll_sel_tbl[tuner_cfg->freq_lo_index]<<10;
    tmp = tmp_a|tmp;
    i2c1SendData(PAGE_AFE_SDM,0x1004a,tmp);

    tmp = i2c1GetData(PAGE_AFE_SDM,0x1001c);
    tmp &= 0xff7f;
    tmp |= mixer_lo_sel_tbl[tuner_cfg->freq_lo_index]<<7;
    i2c1SendData(PAGE_AFE_SDM,0x1001c,tmp);

    tmp = i2c1GetData(PAGE_AFE_SDM,0x1004a);
    if(tuner_cfg->freq_vco_core >= 1270000)
    {
        tmp &= 0x7FFB;
    }
    else
    {
        tmp |= 0x800C;
    }
    i2c1SendData(PAGE_AFE_SDM,0x1004a,tmp);

    
    rdaTVPllCalSet(tuner_cfg);
    
  

    rdaTVRFPLLSDMSet(tuner_cfg);
//    rdaTVGetAdcByFreq(freq);
    
    tuner_cfg->freq_adc_index = rdaTVGetAdcByFreq(tuner_cfg->freq);
//    rdaTVIfOutSet();
    rdaTVBBPLLSDMSet(tuner_cfg);
    rdaTVTunerModeSet(tuner_cfg);
    rdaTVIfOutSet(tuner_cfg);

	i2c1SendData(PAGE_AGC_TUNER,0x10045,0x677f);	//AGC_FAST
    i2c1SendData(PAGE_AGC_TUNER,0x10047,0xff11);
	i2c1SendData(PAGE_AGC_TUNER,0x10057,0x4558);
	i2c1SendData(PAGE_AGC_TUNER,0x10058,0xcc88);
	//AGV_reset
	i2c1SendData(PAGE_AGC_TUNER,0x1000a,0x0000);
	i2c1SendData(PAGE_AGC_TUNER,0x1000a,0x0004);
	i2c1SendData(PAGE_AGC_TUNER,0x1000a,0x0006);
    i2c1SendData(PAGE_AGC_TUNER,0x1000a,0x0007);    //tuner reset
    RDA_DELAY_MS(200);    //wait 50ms
    
	i2c1SendData(PAGE_AGC_TUNER,0x10045,0x67bf);	//AGC_SLOW
    i2c1SendData(PAGE_AGC_TUNER,0x10047,0xf11f);
	i2c1SendData(PAGE_AGC_TUNER,0x10057,0x455c);
	i2c1SendData(PAGE_AGC_TUNER,0x10058,0xcc83);
	RDA_DELAY_MS(5);
}


BOOLEAN rdaTVInitial(void)
{  
    RDA_tuner_cfg.demod_mach = X;
    RDA_tuner_cfg.xtal = RDATV_XTAL;
    RDA_tuner_cfg.xtal_mode = XTAL_SOLO_MODE;
    RDA_tuner_cfg.lna_mode = LNA_ATV_MODE;  
    RDA_tuner_cfg.chip_mode = TUNER_CHIP_MODE_IFOUT;

	
	rdaTVTunerOpen(&RDA_tuner_cfg);
	return TRUE;
}

void rdaTVDtvFreqTuneSet(MAPI_U32 freq,MAPI_U16 eBand, MAPI_U8 mATSC_Mode)
{
		MAPI_U16 tmp=0;

		rdaTV8051Stop();

		printf("~~~~~~~~~~~~~~ RDA5158 DTV Set fre:%ld, band:%d\n",freq,eBand);

		if(mATSC_Mode == 1)
			RDA_tuner_cfg.atsc_mode = LNA_ATSC_AIR;
		else
			RDA_tuner_cfg.atsc_mode = LNA_ATSC_CABLE;
		
	
		tmp = i2c0GetData(0xF0);
		if(tmp == 0x81)
		 	rdaTVSetATSCMode(LNA_ATSC_CABLE);		//老版本，默认为cable
		else
			rdaTVSetATSCMode(RDA_tuner_cfg.atsc_mode);	      //为新版本，接收从上级传回来的Mode [cable]	 	   
		
 switch(eBand)
    {
        case 6000:
        RDA_tuner_cfg.tv_mode_index =  RDA_DTV_6M;
	 i2c1SendDataA(0x01010020,0x002a);  	
        break;
        
        case 7000:
        RDA_tuner_cfg.tv_mode_index = RDA_DTV_7M;
	 i2c1SendDataA(0x01010020,0x0027);  	
        break;
        
        case 8000:
        RDA_tuner_cfg.tv_mode_index = RDA_DTV_8M;
	 i2c1SendDataA(0x01010020,0x0027);  	
        break;
        
        default:
        RDA_tuner_cfg.tv_mode_index = RDA_DTV_8M;
        break;
    }

      rdaDTVSETTING(&RDA_tuner_cfg);
	rdaTVIQSwap(0);
   
       rdaTVSetFreq_tune(freq,0, &RDA_tuner_cfg);

	rdaTV8051Start();
       

}



void rdaTVAtvFreqTuneSet(MAPI_U32 freq, RDA_TV_MODE tv_mode)
{	
    rdaTV8051Stop();
	
    rdaATVSETTING(&RDA_tuner_cfg);
    
    RDA_tuner_cfg.tv_mode_index = tv_mode;

	printf("~~~~~~~~~~~~~~ RDA5158 ATV Set fre:%ld, mode:%d\n",freq,tv_mode);
	
	rdaTVSetATSCMode(LNA_ATSC_CABLE);		//先默认为[cable]
	if(tv_mode == RDA_M)
		{
         	i2c1SendDataA(0x01010020,0x002f);// 6M filter       	
		}
	else
		{
         	i2c1SendDataA(0x01010020,0x0027);// 8M filter
		}
	
    rdaTVIQSwap(0);

	rdaTVSetFreq_tune(freq,0, &RDA_tuner_cfg);

	rdaTV8051Start();
}
#endif
