

#if(FRONTEND_TUNER_TYPE == MSTAR_AVATAR2)

// BIT0: calibration
// BIT1: printf calulate information
// BIT2: printf band information
// BIT3: no delay
// BIT4: delay time when scan
// BIT5: print scan state machine
// BIT6: print agc_state value
// BIT7: AVATAR2 patch or not(N+1, N-1)
// BIT8: AVATAR2 gain finetune
// BIT9: print PLL calculation
// BIT10: VCO calibration when <N+1, N-1>
// BIT11: printf IF
// BIT12: printf calibration

U16 g_AVATAR_debug=BIT0|BIT5|BIT6|BIT7|BIT12;
U16 g_AVATAR_debug=BIT0|BIT5|BIT6|BIT7|BIT12;

void TestCommand_AVATAR(void)
{
    BYTE ucPara1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    BYTE ucPara2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];
    BYTE ucPara3 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    U32 oracle_if, r1;
    U32 rf, if2;
    U16 n1;
    U8 n2;
    U32 p2;

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {

        case 0x00:

            printf("<N+1> ");
            oracle_if=1551000000;
            r1=4;
            rf=578000000L;
            if2=36167000;
            devTuner_SetFreq ( rf, if2, oracle_if, r1);

            break;

        case 0x01:

            OracleWriteByte(17, 0x21);
            OracleWriteByte(18, 0xA6);
            OracleWriteByte(25, 0xE4);
            break;

        case 0x02:
            printf("\nZion..");
            ZionWriteByte(13, 0x8A);
            ZionWriteByte(14, 0x6E);
            ZionWriteByte(16, 0x62);
            ZionWriteByte(23, 0xAa);
            ZionWriteByte(24, 0x15);
            ZionWriteByte(76, 0x42);
//            ZionWriteByte(15, 0x82);
            break;



        case 0x03:
            n1=(256L*ucPara1)+ucPara2;
            printf("\nWrite N1=%x", n1);
            OracleWriteByte(0x07,n1);
            OracleWriteByteMask(0x07,n1>>8, 0x0f);
            break;

        case 0x04:
            n2=ucPara1;
            printf("\nWrite N2=%x", n2);
            ZionWriteByte(0x04,n2);
            break;

        case 0x05:  // 3 byte
            n1=(256L*ucPara1)+ucPara2;
            printf("\nWrite N1=%x", n1);
            ZionWriteByte(0x07,n1);
            OracleWriteByteMask(0x07,n1>>8, 0x0f);
            break;



        case 0x10:
            printf("\n mvideo_sc_get_output_vfreq()=%d", mvideo_sc_get_output_vfreq());

#if (DVB_T_C_DIFF_DB || ENABLE_T_C_COMBO)
            printf("\n IsDVBCInUse()=%d", IsDVBCInUse());
#endif


            break;


        case 0x11:
            //printf("\n MApp_TopStateMachine_GetTopStateName(void)=%s", (char* )MApp_TopStateMachine_GetTopStateName());
            //printf("\n MApp_TopStateMachine_GetTopState(void)=%d", (EN_TOP_STATE)MApp_TopStateMachine_GetTopState());

            break;
        case 0x12:
            printf("\n test:12 dvTunerWriteOracle\n");
            devTunerWriteOracle(ucPara1);
            break;

        case 0x13:
            printf("\n test:13 devTunerWriteZion\n");
            devTunerWriteZion(ucPara1);
            break;

        case 0x14:
            printf("\n test:14 dvTunerWriteOracle  devTunerWriteZion  \n");
            devTunerWriteOracle(ucPara1);
            devTunerWriteZion(ucPara1);
            break;

        case 0x15:
            printf("\n test:15 dvTunerReadOracle  \n");
            devTunerReadOracle();
            break;

        case 0x16:
            printf("\n test:16 dvTunerReadZion  \n");
            devTunerReadZion();
            break;

        case 0x17:
            printf("\n  Avatar_VCO_Calibration  \n");
            Avatar_VCO_Calibration();
            break;

        case 0x18:
            printf("\n  dvTunerWriteOracle  devTunerWriteZion & Calibration \n");
            devTunerWriteOracle(ucPara1);
            devTunerWriteZion(ucPara1);
            Avatar_VCO_Calibration();
            break;

        case 0x20:
            if(ucPara1)
                g_ucTunerID=_TUNER_I2C_ID_ZION;
            else
                g_ucTunerID=_TUNER_I2C_ID_ORACLE;
            printf("\n g_ucTunerID=%x  \n", g_ucTunerID);
            break;

        case 0x21:
            printf("\n test:17 write   \n");
            AvatarWriteByte(ucPara1,ucPara2);
            break;

        case 0x22:
            printf("\n test:18 read   \n");
            AvatarReadByte(ucPara1);
            break;

        case 0x23:
            printf("\n AvatarWriteByteMask   \n");
            AvatarWriteByteMask(ucPara1,ucPara2,ucPara3);
            break;

        case 0x24:
            printf("\n test:19 write read   \n");
            AvatarWriteByte(ucPara1, ucPara2);
            AvatarReadByte(ucPara1);
            break;

        case 0x25:
            printf("\n Avatar_TrackingFilter_Calibration  \n");
            Avatar_TrackingFilter_Calibration(224250L*100, 38900000L, 1575000000,2 );
            break;

        case 0x26:
        {
            U8 uValue;
            uValue=ucPara1;
            printf("\n           HWIF_BUF_WriteBit(Chip2, 76, uValue, 0x08);  \n");
            HWIF_BUF_WriteBit(Chip2, 76, uValue, 0x08);
        }
        break;

        case 0x27:
        {
            U8 uValue;
            printf("\n           HWIF_BUF_ReadReg  \n");

            uValue=HWIF_BUF_ReadReg(Chip1, 5);
            printf("\n uValue=%x \n", uValue);
        }
        break;

        case 0x28:
        {
            U8 ret;
            printf("\n           HWIF_BUF_ReadReg  \n");
            ret=Avatar_TrackingFilter_Calibration(224250L*100, 38900000L, 1575000000,2);

            Avatar_WriteTrackingFilterBandcode(ret);
        }
        break;

        case 0x2e:
        {
            printf("\n aci_debug:  0 for none; 1 for <n+1>; 2 for <n-1>; 3 for restore <n>");
            printf("\n aci_debug=%d ", aci_debug);
            aci_debug=ucPara1;
            printf("\n aci_debug=%d ", aci_debug);
        }
        break;
        case 0x2f:
        {
            printf("\n avatar2_debug=%x", avatar2_debug);
            avatar2_debug=(256L*ucPara1) | ucPara2;
            printf("\n avatar2_debug=%x", avatar2_debug);
        }
        break;


        case 0x30:
        {
            printf("\n g_AVATAR_debug=%x", g_AVATAR_debug);
            g_AVATAR_debug=(256L*ucPara1) | ucPara2;
            printf("\n g_AVATAR_debug=%x", g_AVATAR_debug);
        }
        break;



        case 0x31:
        {
            U8 i;
            for(i=0;i<10;i++)
            {
                MsOS_DelayTask(500);
                printf(".");
            }
            printf("\n 500*10 finish");
        }
        break;

        case 0x32:
        {
            U8 i;
            for(i=0;i<100;i++)
            {
                MsOS_DelayTask(50);
                printf(".");
            }
            printf("\n 50*100 finish");
        }
        break;
    }
}
#endif
