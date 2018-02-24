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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_DEBUG_C

#include <stdio.h>
#include "autotest.h"

#ifdef MSOS_TYPE_LINUX
#include "MsCommon.h"
#include "madp.h"
#include <string.h>
#endif

#include "datatype.h"
#include "drvIIC.h"
#include "drvGlobal.h"

#include "dbusdebug.h"



#if 0//def ENABLE_DBUS_DEBUG
#define DEBUG_INFO(x)// x

static char _u8commandlist[MAX_CMD_NUM][3]=
{
	"r",
	"w",
	"m",
	"ir",
	"iw",
	"c",
	"k"
};


static unsigned int hexstr2int(char *s)
{
	unsigned int ret=0,i;

	if(strlen(s)>6)	//return int, so max is 0xffff
		return 0xFFFFFFFF;

	for(i=0;i<(unsigned int)strlen(s);i++)
	{
		if(s[i]>='0'&&s[i]<='9')
			ret=(ret<<4)+(s[i]-'0');
		else if(s[i]>='a'&&s[i]<='f')
			ret=(ret<<4)+10+(s[i]-'a');
		else if(s[i]>='A'&&s[i]<='F')
			ret=(ret<<4)+10+(s[i]-'A');
		else
			return 0xFFFFFFFF;

	}
	return ret;
}

static bool getnextvar(char *src,char endch,int *endpos,char *ret)
{
    int i;

    *endpos=0xffff;
    if(strlen(src)==0)
        return FALSE;

    for(i=0;i<(int)strlen(src);i++)
        if(src[i]==endch)
            break;

    if(i!=(int)strlen(src))
    {
        *endpos=i;
        strncpy(ret,src,i);
        ret[i]=0;
    }
    else
    {
        *endpos=0xffff;
        ret[0]=0;
    }

    return TRUE;
}

bool MApp_Analyse_CommandStr(char *cmd)
{
    int i,j;
    char tmp[MAX_MSG_LEN];

    DEBUG_INFO(printf("input cmd %s\n",cmd));
    memset(&st_dbg_cmd,0,sizeof(ST_DEBUG_COMMAND));
	if(cmd[0]=='k') //virtual key input
    {
        st_dbg_cmd.type=DEBUG_CMD_KEY;
        st_dbg_cmd.varnum=0;
        return TRUE;
    }

    getnextvar(cmd,' ',&i,tmp);
    if(i!=0xffff)
    {
       cmd+=(i+1);

       //get the command index
       for(j=0;j<MAX_CMD_NUM;j++)
       {
            if(strcmp(tmp,_u8commandlist[j])==0)
                break;
       }
       if(j==MAX_CMD_NUM)
       {
          printf("invalid command");
          return FALSE;
       }
       else
       {
           getnextvar(cmd,' ',&i,tmp);
           if(i!=0xffff)
           {
              cmd+=(i+1);
              switch(tmp[0])
              {
                case 'r':   //register process
                        if(j==0)
                        {   //read register
                           st_dbg_cmd.type=DEBUG_CMD_READ_REGISTER;
                           st_dbg_cmd.varnum=0;
                           st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);    //register addr
						   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xFFFFFFFF)		//register addr error
						   {
							    printf("register addr err\n");
								return FALSE;
						   }
                           getnextvar(cmd,' ',&i,tmp);
                           if(cmd[0]=='m')
                               st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&cmd[1]);  //multi-read num

						   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xFFFFFFFF)
								st_dbg_cmd.varnum--;

                        }
                        else if(j==1)
                        {//write register
                           st_dbg_cmd.type=DEBUG_CMD_WRITE_REGISTER;
                           st_dbg_cmd.varnum=0;
                           st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);
        			   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xFFFFFFFF)		//register addr error
        			   {
        				    printf("register addr err\n");
        					return FALSE;
        			   }
                           while(getnextvar(cmd,' ',&i,tmp))
                           {
                               if(i!=-1)
                               {
                                    cmd+=(i+1);
                                    if(st_dbg_cmd.varnum<MAX_INPUT_VAR_NUM && tmp[0]=='d')
									{
                                        st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);
										if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xFFFFFFFF)
										{
											st_dbg_cmd.varnum--;
											if(st_dbg_cmd.varnum==1)
											{
												printf("no write data\n");
												return FALSE;
											}
										}
									}
                                    else
                                        break;
                               }
                               else
                                    break;
                           }

						   if(cmd[0]=='d')
								st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&cmd[1]);  //get last write data

                           if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xFFFFFFFF)
								st_dbg_cmd.varnum--;

						   if(st_dbg_cmd.varnum==1)
						   {
								printf("no write data\n");
								return FALSE;
							}
                        }
                        else
						{
							printf("invalid command\n");
                            return FALSE;
						}
                        break;
                 case 'b':  //map bank
                   st_dbg_cmd.type=DEBUG_CMD_MAP_BANK;
                   st_dbg_cmd.varnum=1;
                   st_dbg_cmd.var[0]=hexstr2int(&tmp[1]);
                   if(cmd[0]=='s')  //sub bank
                   {
                        st_dbg_cmd.var[1]=hexstr2int(&cmd[1]);
                        st_dbg_cmd.varnum=2;
                   }
				   if(st_dbg_cmd.var[0]>0xff)
					{
					    st_dbg_cmd.varnum=0;
						printf("bank error\n");
						return FALSE;
					}
                    break;
                 case 'd':
                    if(j==3)    //read external device register with i2c
                    {
                       st_dbg_cmd.type=DEBUG_CMD_READ_REG_WITH_I2C;
                       st_dbg_cmd.varnum=0;
                       st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);
					   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xffff)
					   {
						   printf("device addr error\n");
						   return FALSE;
					   }
                       getnextvar(cmd,' ',&i,tmp);
                       if(i!=0xffff)
                       {
                           cmd+=(i+1);
                           if(tmp[0]!='s')
                           {
                               printf("invalid command\n");
                               return FALSE;
                           }
                           st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);
						   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xffff)
						   {
							   printf("sub addr error\n");
							   return FALSE;
						   }
						   if(cmd[0]=='m')
						   {
                               st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&cmd[1]);  //multi-read num
							   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xffff)
									st_dbg_cmd.varnum--;
							   else
									st_dbg_cmd.type=DEBUG_CMD_READ_MULTI_REG_WITH_I2C;
                           }
                       }
                       else
                       {
                           printf("invalid command\n");
                           return FALSE;
                       }
                    }
                    else if(j==4)   //write external device register with i2c
                    {
                       st_dbg_cmd.type=DEBUG_CMD_WRITE_REG_WITH_I2C;
                       st_dbg_cmd.varnum=0;
                       st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);    //get device addr
					   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xffff)
					   {
						   printf("device addr error\n");
						   return FALSE;
					   }
                       getnextvar(cmd,' ',&i,tmp);
                       if(i!=0xffff)
                       {//get sub addr
                           cmd+=(i+1);
                           if(tmp[0]!='s')
                           {
                               printf("invalid command\n");
                               return FALSE;
                           }
                           st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);
						   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xffff)
						   {
							   printf("sub addr error\n");
							   return FALSE;
						   }
                           while(getnextvar(cmd,' ',&i,tmp))
                           {
                                if(i!=0xffff)
                                {
									cmd+=(i+1);
                                    if(tmp[0]!='d')
                                        break;

                                    st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);
									if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xffff)
								   {
									    st_dbg_cmd.varnum--;
										if(st_dbg_cmd.varnum==2)
											return FALSE;
								   }
                                }
                                else
                                    break;
                           }

						   if(cmd[0]=='d')
								st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&cmd[1]);
						   if(st_dbg_cmd.var[st_dbg_cmd.varnum-1]==0xffff)
								st_dbg_cmd.varnum--;

                           if(st_dbg_cmd.varnum==2)    //no data to write
                           {
                               printf("invalid command\n");
                               return FALSE;
                           }
                       }
                       else
                       {
                           printf("invalid command\n");
                           return FALSE;
                       }
                    }//if(j==xx)
                    break;
                case 'c':   //execute command
                    st_dbg_cmd.type=DEBUG_CMD_EXEC;
                    st_dbg_cmd.varnum=0;
                    st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);    //get command index
                    getnextvar(cmd,' ',&i,tmp);
                    DEBUG_INFO(printf("command idx %d\n",st_dbg_cmd.var[st_dbg_cmd.varnum-1]));
                    while(i!=0xffff)
                    {
                        cmd+=(i+1);
                        if(tmp[0]!='d')
                            break;
                        else
                            st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&tmp[1]);
                        DEBUG_INFO(printf("data is %d\n",st_dbg_cmd.var[st_dbg_cmd.varnum-1]));
                        getnextvar(cmd,' ',&i,tmp);
                    }
                    if(cmd[0]=='d')
                        st_dbg_cmd.var[st_dbg_cmd.varnum++]=hexstr2int(&cmd[1]);

                    DEBUG_INFO(printf("get %d vars\n",st_dbg_cmd.varnum));
                    break;
				default:
					printf("invalid command\n");
					return FALSE;
              }//switch(tmp[0])
           }//if(i!=0xffff)
           else
		   {
              printf("invalid command\n");
              return FALSE;
		   }
       }//if(j!=MAX_CMD_NUM)
    }//if(i!=0xffff)
    else
	{
        printf("invalid command\n");
        return FALSE;
	}

    return TRUE;
}

bool MApp_Debug_ReceiveMsg(unsigned char * pu8InData, unsigned short u16InDataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize)
{
    unsigned short pid;

    u16InDataSize=u16InDataSize;
    pu8OutData=pu8OutData;
    u16OutDataSize=u16OutDataSize;

    pid=(pu8InData[0]<<8)+pu8InData[1];
    DEBUG_INFO(printf("receive debug msg,pid %d,in size %d\n",pid,u16InDataSize));

    MApp_Analyse_CommandStr((char *)&(pu8InData[2]));
    st_dbg_cmd.pid=pid;

    DEBUG_INFO(printf("command type %d,var num %d\n",st_dbg_cmd.type,st_dbg_cmd.varnum));
    return TRUE;
}


void MApp_InitDebug_MsgChannel(void)
{
    unsigned char channelIndex;

    MAdp_MSGCH_Init();
    channelIndex = MAdp_MSGCH_GetChannelIndex(DEBUG_CH_NAME);
    MAdp_MSGCH_SetCallBack(channelIndex, MApp_Debug_ReceiveMsg);

}

void MApp_Polling_Debug_Cmd(void)
{
    unsigned int addr,data,i;

    if(st_dbg_cmd.type!=DEBUG_CMD_MAX)
    {
      switch((U8)st_dbg_cmd.type)
      {
            case DEBUG_CMD_READ_REGISTER:
                data=MDrv_ReadByte(st_dbg_cmd.var[0]);
                printf("read register 0x%x,data 0x%x\n",st_dbg_cmd.var[0],data);
                break;
            case DEBUG_CMD_WRITE_REGISTER:
                i=1;
                addr=st_dbg_cmd.var[0];
                while(i<st_dbg_cmd.varnum)
                {
                    printf("write register 0x%x,data 0x%x\n",addr,st_dbg_cmd.var[i]);
                    MDrv_WriteByte(addr,st_dbg_cmd.var[i]);
                    addr++;i++;
                }
                break;
            case DEBUG_CMD_MAP_BANK:
                {
                    char bankmap[17][60]={
                    "r/c  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n",
                    "00   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "01   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "02   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "03   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "04   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "05   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "06   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "07   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "08   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "09   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "0a   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "0b   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "0c   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "0d   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "0e   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n",
                    "0f   ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n"};
                    unsigned char buf[256],j,k;

                    if(st_dbg_cmd.var[0]>0xff)
                        printf("bank error\n");
                    else
                        printf("read bank 0x%x\n",st_dbg_cmd.var[0]);

                    addr=st_dbg_cmd.var[0]<<8;
                    if(st_dbg_cmd.varnum>1)
                    {
                        data=st_dbg_cmd.var[1]; //sub bank
                        MDrv_WriteByte(addr,data);
                    }
                    for(i=0;i<256;i++)
                    {
                        buf[i]=MDrv_ReadByte(addr+i);
                        DEBUG_INFO(printf("read add 0x%04x,data 0x%02x\n",addr+i,buf[i]));
                    }

                    for(i=1;i<17;i++)
                        for(j=0;j<16;j++)
                        {
                           k=(buf[(i-1)*16+j]>>4)&0x0f;
                           bankmap[i][j*3+5]=(k>=10)?(k-10+'a'):(k+'0');
                           k=buf[(i-1)*16+j]&0x0f;
                           bankmap[i][j*3+6]=(k>=10)?(k-10+'a'):(k+'0');
                        }

                    for(i=0;i<17;i++)
                        printf("%s",bankmap[i]);

                }
                break;
            case DEBUG_CMD_READ_REG_WITH_I2C:
                {
                    unsigned char u8AddrLen,ret;
                    unsigned short subaddr;
                    addr=st_dbg_cmd.var[0];
                    if(st_dbg_cmd.var[1]==0xffff)
                    {
                        u8AddrLen=0;
                        subaddr=0;
                    }
                    else if(st_dbg_cmd.var[1]>0xff)
                    {
                        u8AddrLen=2;
                        subaddr=st_dbg_cmd.var[1];
                    }
                    else
                    {
                        u8AddrLen=1;
                        subaddr=st_dbg_cmd.var[1];
                    }

                    MDrv_IIC_ReadBytes(addr, u8AddrLen, (U8 *)&subaddr, 1, &ret);

                    printf("read device addr 0x%x, sub addr 0x%x, data 0x%x\n",addr,subaddr,ret);
                }
                break;
            case DEBUG_CMD_READ_MULTI_REG_WITH_I2C:
                {
                    unsigned char u8AddrLen,ret[MAX_MSG_LEN];
                    unsigned short subaddr;
                    addr=st_dbg_cmd.var[0];
                    if(st_dbg_cmd.var[1]==0xffff)
                    {
                        u8AddrLen=0;
                        subaddr=0;
                    }
                    else if(st_dbg_cmd.var[1]>0xff)
                    {
                        u8AddrLen=2;
                        subaddr=st_dbg_cmd.var[1];
                    }
                    else
                    {
                        u8AddrLen=1;
                        subaddr=st_dbg_cmd.var[1];
                    }

                    MDrv_IIC_ReadBytes(addr, u8AddrLen, (U8 *)&subaddr, st_dbg_cmd.var[2], ret);

                    printf("read device addr 0x%x\n",addr);
                    for(i=0;i<st_dbg_cmd.var[2];i++)
                        printf("sub addr 0x%x, data 0x%x\n",subaddr+i,ret[i]);
                }
                break;

            case DEBUG_CMD_WRITE_REG_WITH_I2C:
                {
                    unsigned char u8AddrLen,d;
                    unsigned short subaddr;
                    addr=st_dbg_cmd.var[0];
                    if(st_dbg_cmd.var[1]==0xffff)
                    {
                        u8AddrLen=0;
                        subaddr=0;
                    }
                    else if(st_dbg_cmd.var[1]>0xff)
                    {
                        u8AddrLen=2;
                        subaddr=st_dbg_cmd.var[1];
                    }
                    else
                    {
                        u8AddrLen=1;
                        subaddr=st_dbg_cmd.var[1];
                    }

                    d=st_dbg_cmd.var[2];

                    MDrv_IIC_WriteBytes(addr, u8AddrLen, (U8 *)&subaddr, 1, &d);

                    printf("write device addr 0x%x, sub addr 0x%x, data 0x%x\n",addr,subaddr,d);
                }
                break;
            case DEBUG_CMD_WRITE_MULTI_REG_WITH_I2C:
                {
                    unsigned char u8AddrLen,d[MAX_MSG_LEN];
                    unsigned short subaddr;
                    addr=st_dbg_cmd.var[0];
                    if(st_dbg_cmd.var[1]==0xffff)
                    {
                        u8AddrLen=0;
                        subaddr=0;
                    }
                    else if(st_dbg_cmd.var[1]>0xff)
                    {
                        u8AddrLen=2;
                        subaddr=st_dbg_cmd.var[1];
                    }
                    else
                    {
                        u8AddrLen=1;
                        subaddr=st_dbg_cmd.var[1];
                    }

                    for(i=0;i<(unsigned int)st_dbg_cmd.varnum-2;i++)
                        d[i]=st_dbg_cmd.var[i+2];

                    MDrv_IIC_WriteBytes(addr, u8AddrLen, (U8 *)&subaddr, st_dbg_cmd.varnum-2, d);

                    printf("write device addr 0x%x\n",addr);

                    for(i=0;i<(unsigned int)st_dbg_cmd.varnum-2;i++)
                        printf("sub addr 0x%x, data 0x%x\n",subaddr+i,d[i]);
                }
                break;

            case DEBUG_CMD_EXEC:
                switch(st_dbg_cmd.var[0])   //command index
                {
#if ENABLE_DTV
                    case 1:
                    {
                        typedef enum
                        {
                            E_RF_CH_BAND_6MHz = 0x01,       ///< 6MHz
                            E_RF_CH_BAND_7MHz = 0x02,       ///< 7MHz
                            E_RF_CH_BAND_8MHz = 0x03,       ///< 8MHz
                            E_RF_CH_BAND_INVALID            ///< Invalid
                        } RF_CHANNEL_BANDWIDTH;
                        extern void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth);
                        devDigitalTuner_SetFreq(st_dbg_cmd.var[1],(RF_CHANNEL_BANDWIDTH)0);
                        break;
                    }
                    case 2:
                    {
                        #ifndef u_int8
                        #define u_int8 unsigned char
                        #endif


                        #if (FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)
                        extern int  ATBMWrite(u_int8 base_addr, u_int8 register_addr, u_int8 *data);
                        ATBMWrite(st_dbg_cmd.var[1],st_dbg_cmd.var[2],(u_int8 *)&(st_dbg_cmd.var[3]));

                        printf("write base addr 0x%02x,register addr 0x%02x, data 0x%02x\n",st_dbg_cmd.var[1],st_dbg_cmd.var[2],st_dbg_cmd.var[3]);
                        #endif
                        break;
                    }
                    case 3:
                    {
                        #ifndef u_int8
                        #define u_int8 unsigned char
                        #endif
                        #if (FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)
                        extern int  ATBMRead(u_int8 base_addr, u_int8 register_addr, u_int8 *data);
                        ATBMRead(st_dbg_cmd.var[1],st_dbg_cmd.var[2],(u_int8 *)&(st_dbg_cmd.var[3]));
                        printf("read base addr 0x%02x,register addr 0x%02x, data 0x%02x\n",st_dbg_cmd.var[1],st_dbg_cmd.var[2],st_dbg_cmd.var[3]);
                        #endif
                        break;
                    }
                    case 4:
                    {
                        #if (FRONTEND_DEMOD_TYPE == ALTOBEAM_883X)
                        extern void ATBMInit(void);
                        ATBMInit();
                        #endif
                        break;
                    }
                    case 5:
                    {
                        U8 tmp[5];
                        extern BOOLEAN devCOFDM_PassThroughI2C_WriteBytes(U8 u8SlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
                        for(i=0;i<5;i++)
                            tmp[i]=st_dbg_cmd.var[i+1];
                        printf("Tuner: 0x%02x,  0x%02x,  0x%02x,  0x%02x,  0x%02x\n", tmp[0],tmp[1],tmp[2],tmp[3],tmp[4]);
                        devCOFDM_PassThroughI2C_WriteBytes(0xc2,0,NULL,5,tmp);
                        break;
                    }
#endif
                    default:
                        break;
                }
                break;
      }
      //MAdp_MSGCH_SendSignal(st_dbg_cmd.pid,MAdp_MSGCH_GetChannelIndex(DEBUG_CH_NAME), reply, len);
      st_dbg_cmd.type=DEBUG_CMD_MAX;
    }
}
#endif


#undef MAPP_DEBUG_C
