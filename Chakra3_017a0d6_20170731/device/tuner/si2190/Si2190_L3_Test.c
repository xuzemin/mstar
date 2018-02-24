/***************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 3 API
   L3 sample application
   FILE: Si2190_L3_Test.c
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Tag:  ROM40_0_A_build_10_V0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/
#include "Si2190_L3_Test.h"

/* define TUNER_ONLY if using a Si2190 tuner without demod                                                    */
/* (It should be defined at project/makefile level to use 100% identical code for tuner-only and tuner+demod)   */
/* #define TUNER_ONLY */

#ifdef    TUNER_ONLY

/* define SILABS_DEMOD_EVB if used on a tuner_only application on a demod EVB (opens i2c_passthru in main)      */
/* (It should be defined at project/makefile level to use 100% identical code for tuner-only EVB and demod EVB) */
/* #define SILABS_DEMOD_EVB*/

/* define Si2190_COMMAND_LINE_APPLICATION if using this code in console mode                                                     */
/* (Si2190_COMMAND_LINE_APPLICATION should be defined at project/makefile level to use 100% identical code for console and TV )  */
/* #define Si2190_COMMAND_LINE_APPLICATION */

/* define FRONT_END_COUNT 1 for a single tuner application                                                                         */
/* (FRONT_END_COUNT should be defined at project/makefile level to use 100% identical code for single-frontend and multi-frontend) */
#define FRONT_END_COUNT 1

int  commandCount  = 0;
int  fe;

L1_Si2190_Context          FrontEnd_Table   [FRONT_END_COUNT];
L1_Si2190_Context         *Si2190;
L1_Si2190_Context         *front_end;

/* Also init a simple i2c context to allow i2c communication checking */
L0_Context* i2c;
L0_Context  i2c_context;
CONNECTION_TYPE mode;

#ifdef    SILABS_DEMOD_EVB
/* To be able to test this on SiLabs demod EVB, it must be possible to close the i2c passthru in the demod */
typedef struct demod_Context {
  L0_Context    *i2c;
  L0_Context     i2cObj;
} demod_Context;

/* i2c_passthru                   */
 #define    i2c_passthru_ADDRESS               49165
 #define    i2c_passthru_OFFSET                0
 #define    i2c_passthru_NBBIT                 1
 #define    i2c_passthru_ALONE                 1
 #define    i2c_passthru_SIGNED                0
  #define           i2c_passthru_disabled                      0
  #define           i2c_passthru_enabled                       1

  demod_Context  demodObj;
  demod_Context *demod;
#endif /* SILABS_DEMOD_EVB */

#ifdef USING_ALIF_FILTER
#include "write_ATV_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef    SiTRACES
/************************************************************************************************************************
  Si2190_UserInput_traces function
  Use:        send a traces configuration message to the L0 SiTRACES functions
              the Si2190_UserInput_traces function asks the user which type of configuration he wishes.
              Then, memorize the message and calls SiTraceConfiguration.
  Returns:    void
  Porting:    Not compiled if SiTRACES is not defined in Silabs_L0_API.h
************************************************************************************************************************/
void Si2190_UserInput_traces               (void)
{
    char *configuration;
    char *msg;
    configuration = (char*)malloc(sizeof(char)*100);
    msg           = (char*)malloc(sizeof(char)*100);
    printf("Enter the traces configuration string (-<param> ,<value>): ");
    gets(configuration);
    sprintf(msg, "traces %s", configuration);
    printf("%s",SiTraceConfiguration (msg));
}
#endif /* SiTRACES */
/************************************************************************************************************************
  Si_I2C_UserInput_read function
  Use:        i2c read test function
              Used to retrieve user input before an i2c read
  Behavior:   split user input on spaces to find the address of the chip, the index of the first byte to read
              and the number of bytes to read, then perform the read and display the resulting bytes.
  Porting:    This is for i2c verification only.
  **********************************************************************************************************************/
void Si_I2C_UserInput_read                 (L0_Context* i2c)
{
    int i;
    int readBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    char *array[50];
    int  bytes[50];
    unsigned int iI2CIndex;
    int iNbBytes;
    unsigned char *pbtDataBuffer;

    input = (char*) malloc(sizeof(char)*1000);
    printf("i2c read ");
    gets(input);

    /* strtok splitting input and storing all items, returning first item */
    array[0] = strtok(input," ");
    if(array[0]==NULL) {return;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
        array[loop] = strtok(NULL," ");
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%d", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = nbArgs - 2;
    if (indexSize <0) return;
    iI2CIndex = 0;
    for (i=1; i<= indexSize; i++) {
        iI2CIndex = iI2CIndex + bytes[i];
    }
    iNbBytes  = bytes[loop-1];
    pbtDataBuffer = (unsigned char*)malloc(sizeof(unsigned char)*iNbBytes);
    L0_SetAddress   (i2c, address, indexSize);
    readBytes = L0_ReadRawBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);
    for (i=0; i<readBytes; i++) { printf ("0x%02x ", pbtDataBuffer[i]); }
    if (readBytes) printf("\n");
}
/************************************************************************************************************************
  Si_I2C_UserInput_write function
  Use:        i2c write test function
              Used to retrieve user input before an i2c write
  Behavior:   split user input on spaces to find the address of the chip and the bytes to write,
              then perform the write.
  Porting:    This is for i2c verification only.
  **********************************************************************************************************************/
void Si_I2C_UserInput_write                (L0_Context* i2c)
{
    int i;
    int writeBytes;
    int loop;
    int nbArgs;
    int indexSize;
    unsigned int address;
    unsigned int uintval;
    unsigned int hexval;
    char *input;
    char *array[50];
    int  bytes[50];
    unsigned int iI2CIndex;
    int iNbBytes;
    unsigned char *pbtDataBuffer;

    input = (char*) malloc(sizeof(char)*1000);
    printf("i2c write ");
    gets(input);

    /* strtok splitting input and storing all items, returning first item */
    array[0] = strtok(input," ");
    if(array[0]==NULL) {return;}
    /* retrieving all remaining items */
    for(loop=1;loop<50;loop++) {
        array[loop] = strtok(NULL," ");
        if(array[loop]==NULL) break;
    }
    nbArgs = loop;
    /* scanning arguments, allowing decimal or hexadecimal input */
    for(loop=0;loop<nbArgs;loop++) {
        hexval=0;
        sscanf(array[loop],"%d", &uintval);
        if (!uintval) sscanf(array[loop],"%x", &hexval);
        bytes[loop] = hexval + uintval;
    }

    address   = bytes[0];
    indexSize = 0;
    if (indexSize <0) return;
    iI2CIndex = 0;
    iNbBytes  = nbArgs-1;
    pbtDataBuffer = (unsigned char*)malloc(sizeof(unsigned char)*iNbBytes);
    for (i=0; i<iNbBytes; i++) { pbtDataBuffer[i] = bytes[i+1]; }
    L0_SetAddress   (i2c, address, indexSize);
    writeBytes = L0_WriteRawBytes (i2c, iI2CIndex, iNbBytes, pbtDataBuffer);
    if (writeBytes) {printf("%d bytes written\n", writeBytes);} else {printf("Write error!\n");}
}
/************************************************************************************************************************
  Si2190_UserInputString function
  Use:        retrieve a string entered by the user
  Parameters: text, a pointer to the string buffer
              max_size, the size allocated by the calling function for the text buffer
  Behavior:   Retrieves the string using fgets to avoid overflows. As fgets keeps the 'carriage return' except
                if the string is longer than max_size, replace it (if present) by the terminating character
  Returns:    the length of the string
************************************************************************************************************************/
int  Si2190_UserInputString                (char* text, int max_size) {
  char *newline;
  if ( fgets(text, max_size, stdin) != NULL ) {
    newline = strchr(text, '\n');             /* search for newline character        */
    if ( newline != NULL ) { *newline = '\0'; /* overwrite trailing newline (if any) */ }
  }
  return (int)(strlen(text));
}
/************************************************************************************************************************
  Si2190_trace function
  Use:        trace toggle function
              Used to toggle tracing for all register accesses, at byte level
  Behavior:   Calls the tracking functions for read and write for both demod and tuner
************************************************************************************************************************/
void Si2190_trace                          (L1_Si2190_Context *api) {
    int trackFlag;
    trackFlag = !api->i2c->trackRead;
    L0_TrackWrite(i2c     , trackFlag);
    L0_TrackRead (i2c     , trackFlag);
    L0_TrackWrite(api->i2c, trackFlag);
    L0_TrackRead (api->i2c, trackFlag);
}
#endif /* TUNER_ONLY */
/************************************************************************************************************************
  NAME: Si2190_configure_i2c_communication
  DESCRIPTION:        Setup USB communication with Si2190 EVB
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    nothing
************************************************************************************************************************/
void Si2190_configure_i2c_communication    (L1_Si2190_Context *api)
{
#ifdef    USB_Capability
    double        retdval;
    char rettxtBuffer[256];
    char *rettxt;
    rettxt = rettxtBuffer;
    L0_Connect (api->i2c, USB);
    L0_Cypress_Configure("-i2c"                 ,"400khz", 0   , &retdval, &rettxt);  /* at 400kHz SCL rate     */
 #ifdef    SILABS_DEMOD_EVB
    L0_Connect (demod->i2c, USB);
 #endif /* SILABS_DEMOD_EVB */
#endif /* USB_Capability */
#ifdef    SILABS_DEMOD_EVB
    L1_WRITE(demod, i2c_passthru, i2c_passthru_enabled);
#endif /* SILABS_DEMOD_EVB */
}
#ifdef Si2190_COMMAND_LINE_APPLICATION
/************************************************************************************************************************
  NAME: Si2190_DisplayStatusByte
  DESCRIPTION:Read Si2190 STATUS byte and display status bits
  Parameter:  Si2190 Context (I2C address)
  Returns:    Si2190/I2C transaction error code
************************************************************************************************************************/
int  Si2190_DisplayStatusByte              (L1_Si2190_Context *api)
{
    int error_code;

    error_code = Si2190_L1_CheckStatus(api);
    if (error_code)
    {
        SiTRACE("Error %d reading STATUS byte\n",error_code);
        printf ("Error %d reading STATUS byte\n",error_code);
        return error_code;
    }

    printf("STATUS: CTS=%d, ERR=%d, DTVINT=%d, ATVINT=%d, TUNINT=%d\n", api->status->cts, api->status->err, api->status->dtvint, api->status->atvint, api->status->tunint);

    return 0;
}
/************************************************************************************************************************
  NAME : Si2190_GetRevision
  DESCRIPTION:  Execute Si2190 GET_REV function and display response fields
  Parameter:  Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int  Si2190_GetRevision                    (L1_Si2190_Context *api)
{
    char message[1000];

    if (Si2190_L1_GET_REV(api) != NO_Si2190_ERROR)          /* execute GET_REV and always read response */
    {
        printf("Error reading GET_REV\n");
        return ERROR_Si2190_SENDING_COMMAND;
    }
    Si2190_L1_GetCommandResponseString(api, Si2190_GET_REV_CMD_CODE,"\n", message);
    printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  NAME: Si2190_ATVStatus
  DESCRIPTION:Reports tuner status from ATV_STATUS response
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_ATVStatus (L1_Si2190_Context *Si2190)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2190_L1_ATV_STATUS(Si2190, Si2190_ATV_STATUS_CMD_INTACK_CLEAR) != NO_Si2190_ERROR) { /* execute ATV_STATUS and always read response */
        printf("Error reading ATV_STATUS\n");
        return ERROR_Si2190_SENDING_COMMAND;
    }
   Si2190_L1_GetCommandResponseString(Si2190, Si2190_ATV_STATUS_CMD_CODE, "\n", message);
   printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  Si2190_DTVStatus function
  Use:        Reports tuner status from DTV_STATUS response
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_DTVStatus (L1_Si2190_Context *Si2190)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2190_L1_DTV_STATUS(Si2190, Si2190_DTV_STATUS_CMD_INTACK_CLEAR) != 0) { /* execute DTV_STATUS and always read response */
        printf("Error reading DTV_STATUS\n");
        return ERROR_Si2190_SENDING_COMMAND;
    }
  Si2190_L1_GetCommandResponseString(Si2190, Si2190_DTV_STATUS_CMD_CODE,"\n", message);                  /* display results */
  printf("%s\n",message);

    return 0;
}
/************************************************************************************************************************
  NAME: Si2190_TunerStatus
  DESCRIPTION:        Reports tuner status from TUNER_STATUS response
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_TunerStatus (L1_Si2190_Context *Si2190)
{
    char *message=(char *) malloc(BUF_SIZE);

    if (Si2190_L1_TUNER_STATUS(Si2190, Si2190_TUNER_STATUS_CMD_INTACK_CLEAR) != NO_Si2190_ERROR) { /* execute TUNER_STATUS and always read response */
        printf("Error reading TUNER_STATUS\n");
        return ERROR_Si2190_SENDING_COMMAND;
    }
  Si2190_L1_GetCommandResponseString(Si2190, Si2190_TUNER_STATUS_CMD_CODE, "\n", message);
  printf("%s\n",message);/* display results */

    return 0;
}

/************************************************************************************************************************
  NAME: Si2190_SSVD_RegRead
  DESCRIPTION: Read one SSVD IP register
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_SSVD_RegRead(L1_Si2190_Context *Si2190)
{
  int uIn=0;
  char entry[MAX_LENGTH];
  char *message=(char *) malloc(BUF_SIZE);
  printf("Enter Register Address to Read \n");
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%d",&uIn) < 1)
    {
       printf ("Error invalid register\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
    }
    if (Si2190_L1_SSVD_REG_RD(Si2190,(unsigned char) uIn,Si2190_SSVD_REG_RD_CMD_IGNORED_MIN) != NO_Si2190_ERROR)
    {
        printf("Error reading Si2190_L1_SSVD_REG_RD\n");
        return ERROR_Si2190_SENDING_COMMAND;
    }
       Si2190_L1_GetCommandResponseString(Si2190,Si2190_SSVD_REG_RD_CMD_CODE,"\n", message);
       printf("%s\n",message);
  }
    return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_SSVD_RegWrite
  DESCRIPTION:        Write one SSVD IP register
  Parameter:  Pointer to Si2190 Context (I2C address)

  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_SSVD_RegWrite(L1_Si2190_Context *Si2190)
{
  unsigned int uIn=0;
  unsigned int uData=0;
  char entry[MAX_LENGTH];
  printf("Enter Register Address to Write 0-9\n");
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%u",&uIn) < 1)
    {
       printf ("Error invalid register\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
    }
    printf("Enter Register Value to write. \n");
    fgets(entry,MAX_LENGTH,stdin);
       if (strlen(entry) > 1)
       {
            if (sscanf(entry,"%u",&uData) < 1)
            {
                printf ("Error invalid data\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
            }
            if (Si2190_L1_SSVD_REG_WR(Si2190,(unsigned char) uIn,Si2190_SSVD_REG_WR_CMD_UPDATE_UPDATE,Si2190_SSVD_REG_WR_CMD_IGNORED_MIN,uData) != NO_Si2190_ERROR)
            {
                printf("Error reading Si2190_L1_SSVD_REG_WR\n");
                return ERROR_Si2190_SENDING_COMMAND;
            }
       }
  }
     return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_MultiRead
  DESCRIPTION:        Read up to seven sequential SSVD IP registers
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_MultiRead(L1_Si2190_Context *Si2190)
{
  unsigned int uIn=0;
  unsigned int uData=0;
  char entry[MAX_LENGTH];
  char *message=(char *) malloc(BUF_SIZE);
  printf("Enter Register Starting Address to Read 0-19\n");
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%u",&uIn) < 1)
    {
       printf ("Error invalid register\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
    }
    printf("Enter Number of Registers to read (1-7)\n");
    fgets(entry,MAX_LENGTH,stdin);
       if (strlen(entry) > 1)
       {
            if (sscanf(entry,"%u",&uData) < 1)
            {
                printf ("Error invalid data\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
            }

            if (Si2190_L1_SSVD_MULTI_REG_RD(Si2190,(unsigned char) uIn,(unsigned char) uData) != NO_Si2190_ERROR)
            {
                printf("Error reading Si2190_L1_SSVD_REG_WR\n");
                return ERROR_Si2190_SENDING_COMMAND;
            }
            Si2190_L1_GetCommandResponseString(Si2190,Si2190_SSVD_MULTI_REG_RD_CMD_CODE,"\n", message);
            printf("%s\n",message);
       }
  }

    return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_MultiWrite
  DESCRIPTION:        Write up to seven sequential SSVD IP registers.
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_MultiWrite(L1_Si2190_Context *Si2190)
{
  unsigned int uIn=0;
  unsigned int regs;
  unsigned int data[] = {0,0,0,0,0,0,0};
  int i;
  char entry[MAX_LENGTH];
  printf("Enter the starting Register Address to Write 0-9\n");
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%u",&uIn) < 1)
    {
       printf ("Error invalid register\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
    }
     printf("Enter Number of Registers to write (1-7)\n");
     fgets(entry,MAX_LENGTH,stdin);
       if (strlen(entry) > 1)
       {
            if (sscanf(entry,"%u",&regs) < 1)
            {
                printf ("Error invalid data\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
            }
           for (i=0;i<regs;i++)
           {
                printf("Enter Register Value for register %d. \n",i+1);
                fgets(entry,MAX_LENGTH,stdin);
                if (strlen(entry) > 1)
                {
                    if (sscanf(entry,"%u",&data[i]) < 1)
                    {
                        printf ("Error invalid data\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
                    }
                }
           }

            if (Si2190_L1_SSVD_MULTI_REG_WR(Si2190,(unsigned char) uIn,Si2190_SSVD_REG_WR_CMD_UPDATE_UPDATE,(unsigned char) regs,data[0],data[1],data[2],data[3],data[4],data[5],data[6]) != NO_Si2190_ERROR)
            {
                printf("Error reading Si2190_L1_SSVD_MULTI_REG_WR\n");
                return ERROR_Si2190_SENDING_COMMAND;
            }
       }
  }
    return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_SSVD_HDiv
  DESCRIPTION:        This command controls the SSVD Horizontal Divide feature.
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Si2190_SSVD_HDiv(L1_Si2190_Context *Si2190)
{
    unsigned int uEnable=0;
    unsigned int uStCtrl0=0;
    unsigned int uHaCtrl0=0;

  char entry[MAX_LENGTH];
  printf("Enter 1=Enable or 0=Disable \n");
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%u",&uEnable) < 1)
    {
       printf ("Error invalid register\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
    }
    printf("Enter ST_Ctrl0 value \n");
    fgets(entry,MAX_LENGTH,stdin);
    if (sscanf(entry,"%u",&uStCtrl0) < 1)
    {
       printf ("Error invalid data\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
    }
    printf("Enter HA_Ctrl0 value \n");
    fgets(entry,MAX_LENGTH,stdin);
    if (sscanf(entry,"%u",&uHaCtrl0) < 1)
    {
       printf ("Error invalid data\nPlease press <Enter> to continue\n"); getc(stdin); return 1;
    }
   if (Si2190_L1_SSVD_HDIV(Si2190,uEnable, uStCtrl0, uHaCtrl0) != NO_Si2190_ERROR)
   {
        printf("Error sending Si2190_L1_SSVD_HDIV\n");
        return ERROR_Si2190_SENDING_COMMAND;
   }

  }
    return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_GetUserFrequency
  DESCRIPTION: Function to process user input frequency and return an error if invalid.
  Parameter: unsigned long *fIn - returns the user entered frequency in Hz.
  Returns : 1 if an error occurred, 0 otherwise.
************************************************************************************************************************/
int Si2190_GetUserFrequency(unsigned long *fIn)
{
  char entry[MAX_LENGTH];
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%ld",fIn) < 1)
          { printf ("Error invalid frequency\nPlease press <Enter> to continue\n"); getc(stdin); return 1;}
  }
  else
  { printf ("Error invalid frequency \nPlease press <Enter> to continue\n"); getc(stdin); return 1;}
  SiTRACE("fIn %ld\n",*fIn);
  return 0;
}
/************************************************************************************************************************
  NAME: Si2190_GetFineTuneOffset
  DESCRIPTION: Function to process user input frequency and return an error if invalid.
  Parameter: int *fIn - returns the user entered frequency in Hz.
  Returns : 1 if an error occurred, 0 otherwise.
************************************************************************************************************************/
int Si2190_GetFineTuneOffset(int *fIn)
{
  char entry[MAX_LENGTH];
  fgets(entry,MAX_LENGTH,stdin);
  if (strlen(entry) > 1)
  {
    if (sscanf(entry,"%d",fIn) < 1)
          { printf ("Error invalid frequency\nPlease press <Enter> to continue\n"); getc(stdin); return 1;}
  }
  else
  { printf ("Error invalid frequency \nPlease press <Enter> to continue\n"); getc(stdin); return 1;}
  SiTRACE("fIn %ld\n",*fIn);
  return 0;
}
/************************************************************************************************************************
  Si2190_help function
  Use:        console application help function
              Used to explain how to init the EVB, tune and scan
************************************************************************************************************************/
int  Si2190_help                           (void) {
    printf("\n\
----------------------------------------------------------------------------\n\
       This is a demonstration application used to illustrate how to use    \n\
            the Si2190 API delivered by Silicon Laboratories                \n\
                                                                            \n\
       It demonstrates a dual front-end case                                \n\
                                                                            \n\
       Most platforms will only have one front-end, therefore               \n\
       the second one will not work correctly                               \n\
                                                                            \n\
                                                                            \n\
    Enter 'help' to display the help.                                       \n\
    Enter 'm'    to display the menu.                                       \n\
                                                                            \n\
----------------------------------------------------------------------------\n");
  return 0;
}
/************************************************************************************************************************
  NAME: Si2190_menu
  DESCRIPTION: Si2190 user menu function
              Used to display the various possibilities offered to the user
  Behavior:   Prints the menu in the console
************************************************************************************************************************/
void Si2190_menu                           (unsigned char full) {
  if (full) {
  printf("\
-----------------------------------------------------------------------\n\
   Console mode Application Menu:\n\
-----------------------------------------------------------------------\n\
 ------  i2c ---------\n\
read           : read bytes from i2c       \n\
write          : write bytes to i2c        \n\
USB            : connect i2c in USB  mode  \n\
CUST           : connect i2c in CUST mode  \n\
trace          : toggle L0 traces\n\
traces         : manage L0 traces (use 'traces' then 'help' for details)\n\
------  Si2190 ------\n\
");
}
  printf("\
InitAndConfig  : Initialize and Configure the Si2190\n\
Status         : Read Si2190 STATUS\n\
GetRevision    : Display revision info\n");
#ifdef USING_ATV_FILTER
printf ("LoadATVVidfilt : Load the ATV videofilter\n");
#endif
#ifdef USING_DLIF_FILTER
printf("LoadDLIFVidfilt : Load the DLIF videofilter\n");
#endif
printf("ATVConfig      : Configure the Properties for ATV mode\n\
DTVConfig      : Configure the Properties for DTV mode\n\
TunerConfig    : Configure the Properties for the Tuner\n\
CommonConfig   : Configure the Common Properties \n\
ATVTune        : Tune an ATV channel\n\
DTVTune        : Tune a DTV channel\n\
TunerStatus    : Display Tuner Status (TC, RSSI, ...)\n\
ATVStatus      : Display ATV Status   (CHL, VSNR, ...)\n\
DTVStatus      : Display DTV Status   (CHL, ...)\n\
ChannelScanM   : Do a channel scan for ATV system M\n\
ChannelScanPal : Do a channel scan for ATV system PAL\n\
AGCOverride    : Override the AGC Control\n\
Standby        : Put the Part in Standby Mode\n\
Powerdown      : Powerdown the Part\n\
XOUTOn         : Turn on XOUT\n\
XOUTOff        : Turn off XOUT\n\
FineTune       : Fine Tune the channel.");
printf("\n------  SSVD Commands ------\n\
SSVD_PowerUp   : Powerup the SSVD block.\n\
SSVD_PowerDown : Powerdown the SDVD block.\n\
SSVD_RegRead   : Read a single SSVD Register.\n\
SSVD_RegWrite  : Write a single SSVD Register.\n\
SSVD_MultiRead : Read multiple SSVD registers.\n\
SSVD_MultiWrite: Write multiple SSVD registers.\n\
SSVD_HDiv      : SSVD HDiv command.\n\
");
  if (full) {
  printf(" ------ console -----\n\
help           : display application help\n\
cls            : clear screen\n\
m              : display this menu\n\
exit           : exit application\n\
");
  }
  printf("----------------------------------------------------------------------------\n");
}
/************************************************************************************************************************
  NAME: Si2190_demoLoop
  DESCRIPTION: Demo application loop function
              Used to call all available demod functions, based on the user's entry
  Behavior:   Wait for the user to enter a string, then calls the selected function
************************************************************************************************************************/
int Si2190_demoLoop (L1_Si2190_Context *Si2190, char* choice) {
    char entry[MAX_LENGTH];
    int errcode;
    unsigned long freq;
    int ifreq;
    unsigned long  minRange, maxRange;
    int i;
    freq = 0;

    sprintf(entry, "%s", choice);

#ifdef    TUNER_ONLY
    if (fe > FRONT_END_COUNT) return 0;
    Si2190 = &(FrontEnd_Table[fe]);

    if (strlen(choice) > 0) {
        SiTRACE("choice '%s'\n",choice);
    } else {
        printf("\n%04d FrontEnd[%d] Command > ", ++commandCount, fe);
        fgets(entry,MAX_LENGTH,stdin);
        if (strlen(entry) > 0) entry[strlen(entry)-1]='\0';
    }

    /* front end selection */
    if ( (strcmp_nocase(entry, "0")==0) & (FRONT_END_COUNT>0) ) { fe = 0; printf ("Controlling FrontEnd %d\n",fe); return 1;}
    if ( (strcmp_nocase(entry, "1")==0) & (FRONT_END_COUNT>1) ) { fe = 1; printf ("Controlling FrontEnd %d\n",fe); return 1;}
    if ( (strcmp_nocase(entry, "2")==0) & (FRONT_END_COUNT>2) ) { fe = 2; printf ("Controlling FrontEnd %d\n",fe); return 1;}
    if ( (strcmp_nocase(entry, "3")==0) & (FRONT_END_COUNT>3) ) { fe = 3; printf ("Controlling FrontEnd %d\n",fe); return 1;}
#endif /* TUNER_ONLY */

    if (strcmp_nocase(entry, "exit"          )==0) { return 0;}
#ifdef    TUNER_ONLY
#ifdef    SiTRACES
    else if (strcmp_nocase(entry, "traces"   )==0) { Si2190_UserInput_traces();}
#endif /* SiTRACES */
    else if (strcmp_nocase(entry, "read"     )==0) { Si_I2C_UserInput_read (i2c);}
    else if (strcmp_nocase(entry, "write"    )==0) { Si_I2C_UserInput_write(i2c);}
    else if (strcmp_nocase(entry, "usb"      )==0) { mode = USB;}
    else if (strcmp_nocase(entry, "cust"     )==0) { mode = CUSTOMER;}
    else if (strcmp_nocase(entry, "simu"     )==0) { mode = SIMU;}
    else if (strcmp_nocase(entry, "trace"    )==0) { Si2190_trace (Si2190); }
#endif /* TUNER_ONLY */
    else if (strcmp_nocase(entry, "InitAndConfig"          )==0)
    {
         if (Si2190_Init(Si2190) == 0 ) {
           Si2190_Configure(Si2190);
         } else {
          SiTRACE("\n");
          SiTRACE("ERROR ----------------------------------\n");
          SiTRACE("ERROR initializing the Si2190 at 0x%02x!\n", Si2190->i2c->address );
          SiTRACE("ERROR ----------------------------------\n");
          SiTRACE("\n");
         }
    }
    else if (strcmp_nocase(entry, "Status"        )==0) { Si2190_DisplayStatusByte     (Si2190); }
    else if (strcmp_nocase(entry, "GetRevision"   )==0) { Si2190_GetRevision           (Si2190); }
#ifdef USING_ATV_FILTER
    else if (strcmp_nocase(entry, "LoadATVVidFilt"   )==0) { Si2190_LoadVideofilter(Si2190,ATV_VIDFILT_TABLE,ATV_VIDFILT_LINES); }
#endif
#ifdef USING_DLIF_FILTER
    else if (strcmp_nocase(entry, "LoadDLIFVidFilt"   )==0) { Si2190_LoadVideofilter(Si2190,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES); }
#endif
    else if (stricmp(entry, "ATVConfig"     )==0)
    {
         Si2190_setupATVProperties(Si2190);
         printf("Sending Properties to Si2190\n");
         Si2190_downloadATVProperties(Si2190);
         printf("Done \n");
    }
    else if (stricmp(entry, "DTVConfig"     )==0)
    {
         Si2190_setupDTVProperties(Si2190);
         printf("Sending Properties to Si2190\n");
         Si2190_downloadDTVProperties(Si2190);
         printf("Done \n");
     }
    else if (stricmp(entry, "TunerConfig"   )==0)
    {
         Si2190_setupTUNERProperties(Si2190);
         printf("Sending Properties to Si2190\n");
         Si2190_downloadTUNERProperties(Si2190);
         printf("Done \n");
    }
    else if (stricmp(entry, "CommonConfig"  )==0)
    {
         Si2190_setupCOMMONProperties(Si2190);
         printf("Sending Properties to Si2190\n");
         Si2190_downloadCOMMONProperties(Si2190);
         printf("Done \n");
    }
    else if (stricmp(entry, "ATVTune"       )==0)
    {
        printf("ATV Center Frequency (in Hz)? ");

        if ((errcode=Si2190_GetUserFrequency(&freq)) != NO_Si2190_ERROR) {
           SiTRACE ("Si2190_GetUserFrequency error 0x%02x\n", errcode);
           return errcode;
        }
        Si2190_setupProperty(Si2190,Si2190_PropertyIndex(Si2190,"ATV_VIDEO_MODE"));

        if ((errcode=Si2190_ATVTune (Si2190, freq,  Si2190->prop->atv_video_mode.video_sys, Si2190->prop->atv_video_mode.color, Si2190->prop->atv_video_mode.invert_signal)) != NO_Si2190_ERROR)
          { printf ("Error returned from ATVTune error = %s\nPlease press <Enter> to continue\n",Si2190_L1_API_ERROR_TEXT(errcode)); getc(stdin); return 1;}

  }
  else if (stricmp(entry, "DTVTune"       )==0)
  {
        printf("DTV Center Frequency (in Hz)? ");
        if ((errcode=Si2190_GetUserFrequency(&freq)) != NO_Si2190_ERROR)
           return errcode;
        Si2190_setupProperty(Si2190,Si2190_PropertyIndex(Si2190, "DTV_MODE"));

    if ((errcode=Si2190_DTVTune (Si2190, freq, Si2190->prop->dtv_mode.bw, Si2190->prop->dtv_mode.modulation, Si2190->prop->dtv_mode.invert_spectrum)) != NO_Si2190_ERROR)
      { printf ("Error returned from DTVTune error = %s\nPlease press <Enter> to continue\n",Si2190_L1_API_ERROR_TEXT(errcode)); getc(stdin); return 1;}

  }
    else if (stricmp(entry, "TunerStatus"   )==0) { Si2190_TunerStatus(Si2190);}
    else if (stricmp(entry, "ATVStatus"     )==0) { Si2190_ATVStatus(Si2190); }
    else if (stricmp(entry, "DTVStatus"     )==0) { Si2190_DTVStatus(Si2190);     }
    else if (stricmp(entry, "CLS"           )==0) { system("cls");}
    else if (stricmp(entry, "XOUTOn"           )==0) { Si2190_XoutOn(Si2190);}
    else if (stricmp(entry, "XOUTOff"           )==0) { Si2190_XoutOff(Si2190);}
    else if (stricmp(entry, "Powerdown"           )==0) { Si2190_Powerdown(Si2190);}
    else if (stricmp(entry, "Standby"           )==0) { Si2190_Standby(Si2190);}

    else if (stricmp(entry, "ChannelScanM"  )==0)
  {
     printf("Frequency Scan Start Hz ? ");
    if ((errcode=Si2190_GetUserFrequency(&minRange)) != NO_Si2190_ERROR)
       return errcode;

    printf("Frequency Scan Stop Hz ? ");
    if ((errcode=Si2190_GetUserFrequency(&maxRange)) != NO_Si2190_ERROR)
       return errcode;

    Si2190_setupProperty(Si2190,Si2190_PropertyIndex(Si2190,"ATV_RSQ_RSSI_THRESHOLD"));
    Si2190_setupProperty(Si2190,Si2190_PropertyIndex(Si2190,"ATV_RSQ_SNR_THRESHOLD"));

    Si2190_ATV_Channel_Scan_M(Si2190,minRange,maxRange, Si2190->prop->atv_rsq_rssi_threshold.lo, Si2190->prop->atv_rsq_rssi_threshold.hi,
      Si2190->prop->atv_rsq_snr_threshold.lo, Si2190->prop->atv_rsq_snr_threshold.hi );
    if ((Si2190->ChannelListSize) > 0)
    {
      printf("Channels Found \n");
      for (i=0; i< Si2190->ChannelListSize;++i)
        printf("%d\t%ld\n",i+1,Si2190->ChannelList[i]);
    }
    else
    {
      printf("No Channels Found \n");
    }
  }
  else if (stricmp(entry, "ChannelScanPal"  )==0)
  {
    printf("Frequency Scan Start Hz ? ");
       if ((errcode=Si2190_GetUserFrequency(&minRange)) != NO_Si2190_ERROR)
       return errcode;


    printf("Frequency Scan Stop Hz ? ");
      if ((errcode=Si2190_GetUserFrequency(&maxRange)) != NO_Si2190_ERROR)
       return errcode;


    Si2190_setupProperty(Si2190,Si2190_PropertyIndex(Si2190,"ATV_RSQ_RSSI_THRESHOLD"));
    Si2190_setupProperty(Si2190,Si2190_PropertyIndex(Si2190,"ATV_RSQ_SNR_THRESHOLD"));

    Si2190_ATV_Channel_Scan_PAL(Si2190,minRange,maxRange,
                                Si2190->prop->atv_rsq_rssi_threshold.lo,
                                Si2190->prop->atv_rsq_rssi_threshold.hi,
                                Si2190->prop->atv_rsq_snr_threshold.lo,
                                Si2190->prop->atv_rsq_snr_threshold.hi );
    if ((Si2190->ChannelListSize) > 0)
    {
      printf("Channels Found \n");
      printf("Num\tType\tChannel \n");
      for (i=0; i< Si2190->ChannelListSize;++i)
        printf("%d\t%s\t%ld\n",i,Si2190->ChannelType[i],Si2190->ChannelList[i]);
    }
    else
    {
      printf("No Channels Found \n");
    }
  }
   else if (stricmp(entry,"AGCOverride"    )==0)
    {
        printf("AGC Override Mode (MAX,TOP,NORMAL)?");
        fgets(entry,MAX_LENGTH,stdin);
        if (strlen(entry) > 0) entry[strlen(entry)-1]='\0';

        if      ( (strcmp_nocase(entry, "MAX")==0) ) { Si2190_AGC_Override(Si2190, Si2190_FORCE_MAX_AGC); }
        else if ( (strcmp_nocase(entry, "TOP")==0) ) { Si2190_AGC_Override(Si2190, Si2190_FORCE_TOP_AGC); }
        else if ( (strcmp_nocase(entry, "NORMAL")==0) ) { Si2190_AGC_Override(Si2190, Si2190_FORCE_NORMAL_AGC); }
        else    { printf ("Error Invalid Choice\nPlease press <Enter> to continue\n"); getc(stdin); return 1;}

    }
   else if (stricmp(entry, "FineTune"       )==0)
    {
        printf("Fine Tune Offset Frequency (in kHz)? ");

        if ((errcode=Si2190_GetFineTuneOffset(&ifreq)) != NO_Si2190_ERROR) {
           SiTRACE ("Si2190_GetFineTuneOffset error 0x%02x\n", errcode);
           return errcode;
        }
/*  Use the NON_PERSISTENT value and DO_NOT_APPLY_TO_LIF  for the FINE_TUNE command */
/*  Multiply the freq in khz * 2 to get freq in (500 hz) */
        if ((errcode=Si2190_L1_FINE_TUNE (Si2190, Si2190_FINE_TUNE_CMD_PERSISTENCE_NON_PERSISTENT, Si2190_FINE_TUNE_CMD_APPLY_TO_LIF_DO_NOT_APPLY_TO_LIF, ifreq*2.0)) != NO_Si2190_ERROR)
          { printf ("Error returned from ATVTune error = %s\nPlease press <Enter> to continue\n",Si2190_L1_API_ERROR_TEXT(errcode)); getc(stdin); return 1;}

    }
    else if  ( (strcmp_nocase(entry, "SSVD_PowerUp")==0) )   { Si2190_L1_SSVD_POWER_UP(Si2190); }
    else if  ( (strcmp_nocase(entry, "SSVD_PowerDown")==0) ) { Si2190_L1_SSVD_POWER_DOWN(Si2190); }
    else if  ( (strcmp_nocase(entry, "SSVD_RegRead")==0) )   { Si2190_SSVD_RegRead(Si2190); }
    else if  ( (strcmp_nocase(entry, "SSVD_RegWrite")==0) )  { Si2190_SSVD_RegWrite(Si2190); }
    else if  ( (strcmp_nocase(entry, "SSVD_MultiRead")==0) ) { Si2190_MultiRead(Si2190); }
    else if  ( (strcmp_nocase(entry, "SSVD_MultiWrite")==0) ){ Si2190_MultiWrite(Si2190); }
    else if  ( (strcmp_nocase(entry, "SSVD_HDiv")==0) )      { Si2190_SSVD_HDiv(Si2190); }
    else if (strcmp_nocase(entry, "m"             )==0) { Si2190_menu(1);}
    else if (strcmp_nocase(entry, "help"          )==0) { Si2190_help();}
    else if (strcmp_nocase(entry, "cls"           )==0) { system("cls");}
    else                                          { Si2190_menu(1);}

  return 1;
}
#endif  /* Si2190_COMMAND_LINE_APPLICATION  */

#ifdef    TUNER_ONLY
/************************************************************************************************************************
  NAME: main
  DESCRIPTION:  Main Routine
 ************************************************************************************************************************/
int  main(int argc, char *argv[]) {
    argc=argc; /* To avoid compiler warning */
    argv=argv; /* To avoid compiler warning */

    SiTraceDefaultConfiguration();
    SiTraceConfiguration("traces -output file -file on -verbose on -function on -line on\n");

    /* I2C pointer initialization (to allow i2c validation) */
    i2c = &i2c_context;
    L0_Init(i2c);

    #ifdef    SILABS_DEMOD_EVB
      demod = &(demodObj);
      demod->i2c = &(demod->i2cObj);
      demod->i2c->address    = 0xc8;
      demod->i2c->indexSize  = 2;
      demod->i2c->trackWrite = 1;
    #endif /* SILABS_DEMOD_EVB */

    /* Software Init */
    for (fe=0; fe<FRONT_END_COUNT; fe++) {
      front_end = &(FrontEnd_Table[fe]);
      Si2190_L1_API_Init(front_end, Si2190_BASE_ADDRESS+(2*fe));
      front_end->i2c->trackRead = front_end->i2c->trackWrite = 1;
      Si2190_configure_i2c_communication  (front_end);
      if (Si2190_Init(front_end) != 0 ) {
        SiTRACE("\n");
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("ERROR initializing the Si2190 at 0x%02x!\n",Si2190_BASE_ADDRESS+(2*fe) );
        SiTRACE("ERROR ----------------------------------\n");
        SiTRACE("\n");
      }
    }

    fe = 0;
    /* Front-end pointers initialization */
    front_end = &(FrontEnd_Table[fe]);

#ifdef    Si2190_COMMAND_LINE_APPLICATION
    while (Si2190_demoLoop(front_end,""));
#endif /* Si2190_COMMAND_LINE_APPLICATION */

    return 0;
}
#endif /* TUNER_ONLY */





