#include <math.h>
#include "MsCommon.h"
#include "drvIIC.h"
#include "Board.h"
#include "drvTuner_AV2012.h"
#include "msAPI_Demod.h"

#if (FRONTEND_TUNER_S2_TYPE==AVAILINK_AV2012 || FRONTEND_TUNER_S2_TYPE==AVAILINK_AV2011)
#define  TUNER_AV2012_SLAVE_ID      0xC4//0xC6
#define  TUNER_CRYSTAL_FREQ         27
static MS_U8 _u8SlaveID = TUNER_AV2012_SLAVE_ID;
#if (FRONTEND_TUNER_TYPE!=RAFAEL_R840_TUNER && FRONTEND_TUNER_TYPE != RAFAEL_R842_TUNER)//modified by Weng 2015.04.07
typedef struct
{
    float    LvdBm;
    MS_U16 u16_if_agc;
}S_RSSI_TABLE;
#endif
#define RSSI_ARRAY_NUM 30

static S_RSSI_TABLE rssi_av2102[RSSI_ARRAY_NUM];

static MS_U16                       _u16SignalLevel2[RSSI_ARRAY_NUM][2]=
{//15*2 = 30
    {65535-63530,    922},{65535-59550,    872},
    {65535-54360,    822},{65535-51700,    772},
    {65535-51400,    740},{65535-50950,    730},
    {65535-50220,    720},{65535-49350,    710},
    {65535-48340,    700},{65535-47160,    690},
    {65535-44300,    660},{65535-49600,    675},
    {65535-40100,    591},{65535-45800,    615},
    {65535-44380,    600},{65535-43460,    590},
    {65535-42330,    580},{65535-41410,    570},
    {65535-38500,    522},{65535-36520,    472},
    {65535-34710,    422},{65535-32670,    372},
    {65535-30830,    322},{65535-29080,    272},
    {65535-27390,    222},{65535-25530,    172},
    {65535-23570,    122},{65535-21540,     72},
    {65535-20380,     22},{65535-0    ,      2}
};


#if 1//(FRONTEND_TUNER_TYPE==AVAILINK_AV2011)

MS_U8 TunerInitialSetting[2][42]=
{//test for VideoCon
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29},
    {0x38, 0x00, 0x00, 0x50, 0x1F, 0xA3, 0xFD, 0x00, 0x46, 0x82, 0x88, 0xB4, 0x96, 0x40, 0x94, 0x4A, 0x66, 0x40, 0x80, 0x2B, 0x6A, 0x50, 0x91, 0x27, 0x8F, 0xCC, 0x21, 0x10, 0x80, 0x00, 0xF5, 0x7F, 0x4A, 0x9B, 0xE0, 0xE0, 0x36, 0xCC, 0xAB, 0x97, 0xC5, 0xA8}
};
/*
MS_U8 TunerInitialSetting[2][42]=
{
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29},
    {0x38, 0x00, 0x00, 0x50, 0x1F, 0xA3, 0xFD, 0x58, 0x0E, 0x82, 0x88, 0xB4, 0xD6, 0x40, 0x94,0x9A, 0x66, 0x40, 0x80, 0x2B, 0x6A, 0x50, 0x91, 0x27, 0x8F, 0xCC, 0x21, 0x10, 0x80,0x02, 0xF5, 0x7F, 0x4A, 0x9B, 0xE0, 0xE0, 0x36, 0x00, 0xAB, 0x97, 0xC5, 0xA8}
};
*/
#else
MS_U8 TunerInitialSetting[2][42]=
{
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29},
    {0x38, 0x00, 0x00, 0x50, 0x1F, 0xA3, 0xFD, 0x58, 0xC6, 0x82, 0x88, 0xB4, 0x96, 0x40, 0x94, 0x4A, 0x66, 0x40, 0x80, 0x2B, 0x6A, 0x50, 0x91, 0x27, 0x8F, 0xCC, 0x21, 0x10, 0x80, 0x02, 0xF5, 0x7F, 0x4A, 0x9B, 0xE0, 0xE0, 0x36, 0x02, 0xAB, 0x97, 0xC5, 0xA8}
};
#endif

//MS_BOOL MApi_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
//MS_BOOL MApi_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);


MS_BOOL AV2012_WriteReg(MS_U8 u8SlaveID, MS_U8 u8Addr, MS_U8 u8Data)
{
    MS_BOOL bRet=TRUE;
    MS_U8 u8Value[2];
    u8Value[0]=u8Addr;
    u8Value[1]=u8Data;
    MS_U8 addr_size =0;
//    bRet &= MDrv_IIC_Write(u8SlaveID, 0, 0, u8Value, 2);
    bRet &= MDrv_IIC_WriteBytes((U16)((DVBS_TUNER_IIC_BUS<<8)|u8SlaveID), 0, &addr_size, 2,u8Value);

	if(bRet)
	{
		//printf(" DevTuner AVL2012 Write u8Addr=[%x]=%x, Success....  \n", u8Addr, u8Data);
	}
	else
	{
		//printf(" DevTuner AVL2012 Write u8Addr=[%x]=%x, Fail...  \n", u8Addr, u8Data);
	}
    return bRet;
}
MS_BOOL AV2012_ReadReg(MS_U8 u8SlaveID, MS_U8 u8Addr, MS_U8 *u8Data)
{
    MS_BOOL bRet=TRUE;
    MS_U8 addr_data =  u8Addr;
    MS_U8 addr_size =0;
//    bRet&=MDrv_IIC_Write(u8SlaveID, 0, 0, &u8Addr, 1);
//    bRet&=MDrv_IIC_Read(u8SlaveID, 0, 0, u8Data, 1);

    bRet&= MDrv_IIC_WriteBytes((U16)((DVBS_TUNER_IIC_BUS<<8)|u8SlaveID), 0, &addr_size, 1,&addr_data);
    bRet&= MDrv_IIC_ReadBytes((U16)((DVBS_TUNER_IIC_BUS<<8)|u8SlaveID), 0, &addr_size,1,u8Data);



	if(bRet)
	{
		//printf("\r\n >>DevTuner AVL2012 Read Success.... \n");
	}
	else
	{
		//printf("\r\n >>DevTuner AVL2012 Read Fail.... \n");
	}
    return bRet;
}

void AV2012_SlaveID_Check(void)
{

#if 0
     MS_U8 regValue;

      _u8SlaveID = 0xC0;
      do
      {
          regValue=(char) (0x38);
          if(AV2012_WriteReg(_u8SlaveID,0,regValue))
          {
               regValue = 0;
               if(AV2012_ReadReg(_u8SlaveID,0,&regValue))
               {
                     if(regValue == 0x38)
                     {
                         break;
                     }
               }
          }
          _u8SlaveID += 0x02;
      } while(_u8SlaveID <= 0xC6);
      if(_u8SlaveID > 0xC6)
      {
           _u8SlaveID = TUNER_AV2012_SLAVE_ID;
      }
#else
      _u8SlaveID = TUNER_AV2012_SLAVE_ID;

#endif

      //printf("\r\n DVBS TUNER SLAVE ID = %x", _u8SlaveID);
}

MS_BOOL MDrv_Tuner_Initial(void)
{
    MS_BOOL bRet=TRUE;
    MS_U8 index_temp; //ohya++ modyify 20130802


    AV2012_SlaveID_Check();

    for (index_temp=0; index_temp < 12; index_temp++)
    {
        bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index_temp], TunerInitialSetting[1][index_temp]);
    }
    MsOS_DelayTask(1);
    for (index_temp=13; index_temp < 42; index_temp++)
    {
        bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index_temp], TunerInitialSetting[1][index_temp]);
    }
    MsOS_DelayTask(1);
    bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][12], TunerInitialSetting[1][12]);
    MsOS_DelayTask(100);
    for (index_temp=0; index_temp < 12; index_temp++)
    {
        bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index_temp], TunerInitialSetting[1][index_temp]);
    }
    MsOS_DelayTask(1);
    for (index_temp=13; index_temp < 42; index_temp++)
    {
        bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index_temp], TunerInitialSetting[1][index_temp]);
    }
    MsOS_DelayTask(1);
    bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][12], TunerInitialSetting[1][12]);
    MsOS_DelayTask(50);
    return bRet;
}

MS_BOOL MDrv_Tuner_SetFreq(MS_U16 u16CenterFreq, MS_U32 u32SymbolRate_Hz)
{
    MS_BOOL bRet=TRUE;
    MS_BOOL bAutoScan=FALSE;
    MS_U32 u32FracN;
    MS_U32 BW;
    MS_U32 BF;
    MS_U8 u8Reg[8];


    DEBUG_DEMOD_S( printf("AV2012 tuner setFreq(u16CenterFreq=%u, u32SymbolRate_Hz=%u)\n",u16CenterFreq, u32SymbolRate_Hz ); );

    //printf("Funs=%s, line=%d, u16CenterFreq=%ld, \n",__FUNCTION__,__LINE__, u16CenterFreq);
    //printf("Funs=%s, line=%d, u32SymbolRate_Hz=%ld, \n",__FUNCTION__,__LINE__, u32SymbolRate_Hz);
    if (u32SymbolRate_Hz == 0) //auto-scan mode
    {
	    bAutoScan = TRUE;
    }
    MsOS_DelayTask(50);
    u32FracN = (u16CenterFreq + TUNER_CRYSTAL_FREQ/2)/TUNER_CRYSTAL_FREQ;
    if(u32FracN > 0xff)
    {
   	   u32FracN = 0xff;
    }
    u8Reg[0]=(MS_U8) (u32FracN & 0xff);
    u32FracN = (u16CenterFreq<<17)/TUNER_CRYSTAL_FREQ;
    u32FracN = (u32FracN & 0x1ffff);
    u8Reg[1]=(MS_U8) ((u32FracN>>9)&0xff);
    u8Reg[2]=(MS_U8) ((u32FracN>>1)&0xff);
    u8Reg[3]=(MS_U8) (((u32FracN<<7)&0x80) | 0x50); // default is 0x50
    // Channel Filter Bandwidth Setting.
    if(bAutoScan==TRUE)//requested by BB
    {
        u8Reg[5] = 0xA3; //BW=27MHz
    }
    else
    {
        if(u32SymbolRate_Hz>40000)//for VideoCon
            BW = u32SymbolRate_Hz;
        else
        {
            // rolloff is 35%
            BW = u32SymbolRate_Hz*135/200;
#if 0 //test for PALAPA 3750H3125
            // monsen 20080726, BB request low IF when sym < 6.5MHz
            // add 6M when Rs<6.5M,
            if(u32SymbolRate_Hz<6500)
            {
                BW = BW + 6000;
            }
            if (u32SymbolRate_Hz > 25000)
            {
                // add 4p7M for LNB frequency shifting
                BW = BW + 4700;
            }
            else
            {
                // add 2M for LNB frequency shifting
                BW = BW + 2000;
            }
#endif
            // add 8% margin since fc is not very accurate
            BW = BW*108/100;
        }
        // Bandwidth can be tuned from 4M to 40M
        if( BW< 4000)
        {
            BW = 4000;
        }
        if( BW> 40000)
        {
            BW = 40000;
        }
        BF = (BW*127 + 21100/2) / (21100); // BW(MHz) * 1.27 / 211KHz
        u8Reg[5] = (MS_U8)BF;
    }
    // Sequence 4
    // Send Reg0 ->Reg4
    MsOS_DelayTask(5);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x00, u8Reg[0]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x01, u8Reg[1]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x02, u8Reg[2]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x03, u8Reg[3]);

    MsOS_DelayTask(100);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x00, u8Reg[0]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x01, u8Reg[1]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x02, u8Reg[2]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x03, u8Reg[3]);

    MsOS_DelayTask(5);
    // Sequence 5
    // Send Reg5
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x05, u8Reg[5]);
    MsOS_DelayTask(5);
    // Fine-tune Function Control
    //Tuner fine-tune gain function block. bit2.
    //not auto-scan case. enable block function. FT_block=1, FT_EN=1
    if (bAutoScan==FALSE)
    {
         u8Reg[6] = 0x06;
         bRet&=AV2012_WriteReg(_u8SlaveID, 0x25, u8Reg[6]);
         MsOS_DelayTask(5);
         //Disable RFLP at Lock Channel sequence after reg[37]
         //RFLP=OFF at Lock Channel sequence
         // RFLP can be Turned OFF, only at Receving mode.
         u8Reg[7] = 0x96;
         bRet&=AV2012_WriteReg(_u8SlaveID, 0x0C, u8Reg[7]);
    }
    return bRet;
}

MS_BOOL MDrv_Tuner_CheckLock(void)
{
    MS_BOOL bRet=TRUE;
    MS_U8 u8Data=FALSE;

    bRet&=AV2012_ReadReg(_u8SlaveID, 0x0B, &u8Data);
    if (bRet==FALSE)
    {
        return bRet;
    }
    else
    {
        if ((u8Data&0x03)!=0x03)
        {
            bRet=FALSE;
        }
    }
    //printf("\r\n =============>> Tuner Status 0x%x,bRet = %d\n", u8Data,bRet);
    return bRet;
}

MS_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks)
{
    return MDrv_Tuner_SetFreq(u16CenterFreq_MHz, u32SymbolRate_Ks);
}
MS_BOOL MDrv_DVBS_Tuner_Initial(void)
{
    return MDrv_Tuner_Initial();
}
MS_BOOL MDrv_DVBS_Tuner_CheckLock(void)
{
    return MDrv_Tuner_CheckLock();
}
// input IF_AGC,
// return dBm.
float MDrv_DVBS_Tuner_Get_RSSI(MS_U16 u16_gain)
{
    MS_U8 indx = 0;
    MS_U8 arry_size = 0;
    float rf_dbm = 0.0;

    if( rssi_av2102[0].u16_if_agc != (0xffff-_u16SignalLevel2[0][0]))
    {
        MS_U8 u8_i = 0;
        for(u8_i = 0;u8_i<RSSI_ARRAY_NUM;u8_i++)
        {
           rssi_av2102[u8_i].LvdBm = (float)_u16SignalLevel2[u8_i][1]/10.0*(-1.0);
           rssi_av2102[u8_i].u16_if_agc = 0xffff - _u16SignalLevel2[u8_i][0];
        }
    }

    arry_size = sizeof(rssi_av2102)/sizeof(S_RSSI_TABLE);

    // printf("array_size = %d, gain=0x%x\n",arry_size,u16_gain);

    if (u16_gain > rssi_av2102[0].u16_if_agc)
    {
        rf_dbm = (float)(u16_gain - rssi_av2102[1].u16_if_agc)/(float)(rssi_av2102[0].u16_if_agc - rssi_av2102[1].u16_if_agc)*(rssi_av2102[0].LvdBm - rssi_av2102[1].LvdBm)+rssi_av2102[1].LvdBm;
    }
    else if (u16_gain < rssi_av2102[arry_size-1].u16_if_agc)
    {
        rf_dbm = (float)(u16_gain - rssi_av2102[arry_size-2].u16_if_agc)/(float)(rssi_av2102[arry_size-1].u16_if_agc - rssi_av2102[arry_size-2].u16_if_agc)*(rssi_av2102[arry_size-1].LvdBm - rssi_av2102[arry_size-2].LvdBm)+rssi_av2102[arry_size-2].LvdBm;
    }
    else
    {
        for(indx = 0;indx<arry_size;indx++)
        {
            if (u16_gain > rssi_av2102[indx].u16_if_agc)
                break;
        }

        if( indx == 0 ) // Fix coverity CID188333
        {
            printf("\nError: Undefine indx = 0!\n");
            rf_dbm = 0;
        }
        else if( indx >= RSSI_ARRAY_NUM )
        {
            printf("\nError: indx >= RSSI_ARRAY_NUM!\n");
            rf_dbm = 0;
        }
        else// if( indx<RSSI_ARRAY_NUM )	//Fix coverity CID197167
        {
            rf_dbm = (float)(u16_gain - rssi_av2102[indx].u16_if_agc)/(float)(rssi_av2102[indx-1].u16_if_agc - rssi_av2102[indx].u16_if_agc)*(rssi_av2102[indx-1].LvdBm - rssi_av2102[indx].LvdBm)+rssi_av2102[indx].LvdBm;
        }
    }

    // printf("gain=0x%x,rf_dbm=%f, indx=%d, arry_size=%d\n",u16_gain,rf_dbm,indx,arry_size);

    return rf_dbm;
}

#endif
