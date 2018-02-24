//Copyright (C) 2008 MStar  All Rights Reserved.

/*! \file  drvUsbPTPLib.c
    \brief  Functions for communicating with PTP device.


 \n\b History:
    \n\b Date: 2008/8/18
    \n\b Author: Colin Tsai
    \n\b Reason: Create
    \n
*/
//=============================================================================

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Datatype.h"
#include "debug.h"  // for PLATFORM define
#include "Sysinfo.h"

//#ifdef ENABLE_PTP_HOST
#include "drvUSB.h"
#include "drvUsbPTPLib.h"
#include "drvUsbHostConfig.h"

extern U32 drvUSBHost_PTP_GetObjectData(
    U16 u16OpCode,
    U32 u32TotalSize,
    U32 u32HandleIdx,
    U32 u32FileOffset,
    U32 u32Length,
    U32 u32DRAMAddr);

extern U32 drvUSBHost_PTP_GetObjectHandles(U16 u16ObjFormat, U32 u32AssociObjHandle);
extern U32 drvUSBHost_PTP_GetObjectHandleNo(U32 u32HandleIdx);
extern BOOLEAN drvUSBHost_PTP_GetObjInfo(U32 u32ObjectHandle);
extern U32 drvUSBHost_PTP_GetCurGetObjOffset(void);
extern U8 drvUSBHost_PTP_GetError(void);

extern U32 drvUSBHost_PTP_GetObjectData_Port2(
    U16 u16OpCode,
    U32 u32TotalSize,
    U32 u32HandleIdx,
    U32 u32FileOffset,
    U32 u32Length,
    U32 u32DRAMAddr);

extern U32 drvUSBHost_PTP_GetObjectHandles_Port2(U16 u16ObjFormat, U32 u32AssociObjHandle);
extern U32 drvUSBHost_PTP_GetObjectHandleNo_Port2(U32 u32HandleIdx);
extern BOOLEAN drvUSBHost_PTP_GetObjInfo_Port2(U32 u32ObjectHandle);
extern U32 drvUSBHost_PTP_GetCurGetObjOffset_Port2(void);
extern U8 drvUSBHost_PTP_GetError_Port2(void);

#ifdef ENABLE_PTP
PTP_OBJECTINFO     gPtpObjectInfo;
U8 gPTPHandleBuf[32768];
U8 gPTP2HandleBuf[32768];
//U32 gUsbPtpObjHandlesBufAdr = USB_PTP_OBJHANDLES_BUF_ADR;

U16 CPU2Le16(U16 u16Data)
{
    #if (PLATFORM==MCU8051)
    U16 u16Tmp;

    *(((U8*)(&u16Tmp))+0) = *(((U8*)(&u16Data))+1);
    *(((U8*)(&u16Tmp))+1) = *(((U8*)(&u16Data))+0);
    return(u16Tmp);

    #else
    return(u16Data);
    #endif

}

U32 CPU2Le32(U32 u32Data)
{
    #if (PLATFORM==MCU8051)
    U32 u32Tmp;

    *(((U8*)(&u32Tmp))+0) = *(((U8*)(&u32Data))+3);
    *(((U8*)(&u32Tmp))+1) = *(((U8*)(&u32Data))+2);
    *(((U8*)(&u32Tmp))+2) = *(((U8*)(&u32Data))+1);
    *(((U8*)(&u32Tmp))+3) = *(((U8*)(&u32Data))+0);
    return(u32Tmp);

    #else
    return(u32Data);
    #endif
}

U32 drvUSBHost_PTP_GetPtpObjHandlesBufAdr(void)
{
    return (U32) gPTPHandleBuf;
}

U32 drvUSBHost_PTP_GetPtpObjHandlesBufAdr_Port2(void)
{
    return (U32) gPTP2HandleBuf;
}

//Function_Name: drvUsbPTP_GetObjectHandles( )
/*!  \brief Gather all object handles according to parameters passed in.

This function will try to gather all object handles according to parameters passed in.
The handles are stored in memory of PTP library.

    \param u8UsbPort     The USB port number.

    \param u16ObjFormat     The object format code you want to get. All handles returned
                                        will belong to this format. The value 0 means "Dont care"

    \param u32AssociObjHandle     The associate object handle. All handles returned will
                                               be its children. The value 0 means "Don't case",
                                               and 0xFFFFFFFF means the "Root"

\return The number of object handles it got.
*/
U32 drvUsbPTP_GetObjectHandles(
    U8 u8UsbPort,
    U16 u16ObjFormat,
    U32 u32AssociObjHandle)
{
    U16 ObjFormat = u16ObjFormat;
    U32 AssociObjHandle = u32AssociObjHandle;

    //printf("drvUsbPTP_GetObjectHandles: %bd\n", u8UsbPort);
    if (u8UsbPort == USB_PORT_0)
    {
    #ifdef USB_PTP_ENABLE
        return drvUSBHost_PTP_GetObjectHandles(ObjFormat, AssociObjHandle);
    #endif
    }
    else if (u8UsbPort == USB_PORT_2)
    {
    #ifdef USB2_PTP_ENABLE
        if (u8UsbPort == USB_PORT_2)
            return drvUSBHost_PTP_GetObjectHandles_Port2(ObjFormat, AssociObjHandle);
    #endif
    }


    return 0;
}

//Function_Name: drvUsbPTP_GetObjectHandleByIndex( )
/*!  \brief Get real object handle from PTP library memory.

This function will try to get the real object handle from PTP library memory. It should be
called after the function msAPI_PTP_GetObjectHandles.

    \param u8UsbPort     The USB port number.

    \param u32Index     The object index you want to get.

\return Object handle or 0xFFFFFFFF for invalid object handle.
*/
U32 drvUsbPTP_GetObjectHandleByIndex(U8 u8UsbPort, U32 u32Index)
{
    U32 Index = u32Index;

    //printf("drvUsbPTP_GetObjectHandleByIndex:\n");
    if (u8UsbPort == USB_PORT_0)
    {
    #ifdef USB_PTP_ENABLE
        return drvUSBHost_PTP_GetObjectHandleNo(Index);
    #endif
    }
    else if (u8UsbPort == USB_PORT_2)
    {
    #ifdef USB2_PTP_ENABLE
        return drvUSBHost_PTP_GetObjectHandleNo_Port2(Index);
    #endif
    }

    return 0xFFFFFFFF;
}

//Function_Name: drvUsbPTP_GetObjectInfo( )
/*!  \brief Get PTP object information.

This function will try to get object information.

    \param u8UsbPort     The USB port number.
    \param u32ObjectHandle     The object handle you want to get.

\return Pointer for ObjectInfo.
*/
PTP_OBJECTINFO * drvUsbPTP_GetObjectInfo(U8 u8UsbPort, U32 u32ObjectHandle)
{
    PTP_OBJECTINFO *pObjInfo = NULL;
    U32 ObjectHandle = u32ObjectHandle;
//    U8  ii;

    //printf("drvUsbPTP_GetObjectInfo:\n");
    if (u8UsbPort == USB_PORT_0)
    {
    #ifdef USB_PTP_ENABLE
        if (drvUSBHost_PTP_GetObjInfo(ObjectHandle))
            pObjInfo = &gPtpObjectInfo;
    #endif
    }
    else if (u8UsbPort == USB_PORT_2)
    {
    #ifdef USB2_PTP_ENABLE
        if (drvUSBHost_PTP_GetObjInfo_Port2(ObjectHandle))
            pObjInfo = &gPtpObjectInfo;
    #endif
    }

    if (pObjInfo == NULL)
    {
        printf("PTP_GetObjectInfo: Invalid handle\n");
    }
#if 0
    else
    {
        printf("ObjectFormat: %X\n", pObjInfo->ObjectFormat);
        printf("ObjectCompressedSize: %ld\n", pObjInfo->ObjectCompressedSize);
        printf("ThumbFormat: %X\n", pObjInfo->ThumbFormat);
        printf("ThumbCompressedSize: %ld\n", pObjInfo->ThumbCompressedSize);
        printf("ThumbPixWidth: %ld\n", pObjInfo->ThumbPixWidth);
        printf("ThumbPixHeight: %ld\n", pObjInfo->ThumbPixHeight);
        printf("ImagePixWidth: %ld\n", pObjInfo->ImagePixWidth);
        printf("ImagePixHeight: %ld\n", pObjInfo->ImagePixHeight);
        printf("ParentObject: %ld\n", pObjInfo->ParentObject);
        printf("Filename: ");
        for (ii=0; pObjInfo->Filename[ii] != 0; ii++)
            printf("%c", (U8) (pObjInfo->Filename[ii]));
    }
#endif

    return pObjInfo;
}

//Function_Name: drvUsbPTP_GetThumb( )
/*!  \brief Get the thumbnail of object.

This function will try to get the thumbnail of object.

    \param u8UsbPort     The USB port number.
    \param u32ObjectHandle     The object handle you want to get.
    \param u32Offset     The start offset you want to get.
    \param u32Length     The buffer size.
    \param u32BufAddr     The buffer address.

\return acutal thumb size it got.
*/
U32 drvUsbPTP_GetThumb(
    U8 u8UsbPort,
    U32 u32ObjectHandle,
    U32 u32Offset,
    U32 u32Length,
    U32 u32BufAddr)
{
    PTP_OBJECTINFO  *pObjInfo;

    U32 Offset = u32Offset;         // For compile warning when no PTP defined
    U32 Length = u32Length;
    U32 BufAddr = u32BufAddr;

    //printf("drvUsbPTP_GetThumb:\n");
    if (u32Offset == 0)
        pObjInfo = drvUsbPTP_GetObjectInfo(u8UsbPort, u32ObjectHandle);
    else
        pObjInfo = (PTP_OBJECTINFO*) &gPtpObjectInfo;

    if (pObjInfo == NULL)
        return 0;

    if (u8UsbPort == USB_PORT_0)
    {
    #ifdef USB_PTP_ENABLE
        return drvUSBHost_PTP_GetObjectData(PTP_GetThumb, pObjInfo->ThumbCompressedSize,
                u32ObjectHandle, Offset, Length, BufAddr);
    #endif
    }
    else if (u8UsbPort == USB_PORT_2)
    {
    #ifdef USB2_PTP_ENABLE
        return drvUSBHost_PTP_GetObjectData_Port2(PTP_GetThumb, pObjInfo->ThumbCompressedSize,
                u32ObjectHandle, Offset, Length, BufAddr);
    #endif
    }

    return 0;
}


//Function_Name: drvUsbPTP_GetObject( )
/*!  \brief Get the object.

This function will try to get content of object.

Please follow the offset sequence to get the object data. When the u32Offset is zero,
PTP USB driver will issue PTP command (GetObject) to the camera , and get the first bank of data.
For example, if the AP has a 16K buffer to get image data, the operation sequence is as follow.
1st : offset 0 , length 16K
2nd: offset 16K, length 16K
3rd: offset 32K, length 16K
..
If users want to stop or issue other commands before the end of the object data stream,
driver has to read all data at the camera side, it may take a period of time.

    \param u8UsbPort     The USB port number.
    \param u32ObjectHandle     The object handle you want to get.
    \param u32Offset     The start offset you want to get.
    \param u32Length     The size you want to get.
    \param u32BufAddr     Buffer address.

\return acutal object size it got.
*/
extern void drvUSBHost_PTP_SetObjHWindow1(U32 u32PhyAddr);
extern void drvUSBHost_PTP_FreeObjHWindow1(void);

U32 drvUsbPTP_GetObject(
    U8 u8UsbPort,
    U32 u32ObjectHandle,
    U32 u32Offset,
    U32 u32Length,
    U32 u32BufAddr)
{
    PTP_OBJECTINFO  *pObjInfo;
    U32 Offset = u32Offset;         // For compile warning when no PTP defined
    U32 Length = u32Length;
    U32 BufAddr = u32BufAddr;
    //U32 RdBytes;
    //U32 ii, jj, kk, uOffset, PgStart, PgEnd, PgOffset;
    //U8 xdata *pTestBuf = (U8 xdata*)0xF000;

    //printf("drvUsbPTP_GetObject: 0x%lX, %ld, %ld, 0x%lX\n",
    //        u32ObjectHandle, u32Offset, u32Length, u32BufAddr);
    if (u32Offset == 0)
        pObjInfo = drvUsbPTP_GetObjectInfo(u8UsbPort, u32ObjectHandle);
    else
        pObjInfo = (PTP_OBJECTINFO*) &gPtpObjectInfo;

    if (pObjInfo == NULL)
        return 0;

    if (u8UsbPort == USB_PORT_0)
    {
    #ifdef USB_PTP_ENABLE
#if 0
        RdBytes = drvUSBHost_PTP_GetObjectData(PTP_GetObject, pObjInfo->ObjectCompressedSize,
                u32ObjectHandle, Offset, Length, BufAddr);

        PgStart = (BufAddr & 0xFFFFF000);
        PgEnd = ((BufAddr + Length) & 0xFFFFF000);
        uOffset = BufAddr;
        kk = 0;

        for (ii=PgStart; ii<=PgEnd; ii+=0x1000)
        {
            PgOffset = uOffset & 0x00000FFF;

            drvUSBHost_PTP_SetObjHWindow1(ii);
            for (jj=PgOffset; jj<0x1000; jj++, kk++)
            {
                if (kk % 16 == 0)
                    printf("\n %08lx:", BufAddr+kk);

                printf(" %02bX", pTestBuf[jj]);
            }
            printf("\n");
            drvUSBHost_PTP_FreeObjHWindow1();

            uOffset += 0x1000 - PgOffset;
        }

        return RdBytes;
#endif
        return drvUSBHost_PTP_GetObjectData(PTP_GetObject, pObjInfo->ObjectCompressedSize,
                u32ObjectHandle, Offset, Length, BufAddr);
    #endif
    }
    else if (u8UsbPort == USB_PORT_2)
    {
    #ifdef USB2_PTP_ENABLE
        return drvUSBHost_PTP_GetObjectData_Port2(PTP_GetObject, pObjInfo->ObjectCompressedSize,
                u32ObjectHandle, Offset, Length, BufAddr);
    #endif
    }

    return 0;
}

//Function_Name: drvUsbPTP_GetObjectEnd( )
/*!  \brief Terminate the operation of getting object.

This function will try to terminate the operation of getting object.

    \param u8UsbPort     The USB port number.
    \param u32ObjectHandle     The object handle you want to get.
    \param u32BufAddr     The buffer address. (buffer size must be 16KB at least)

\return none.
*/
void drvUsbPTP_GetObjectEnd(U8 u8UsbPort, U32 u32ObjectHandle, U32 u32BufAddr)
{
    U32 BufAddr = u32BufAddr;
    U32 ObjectHandle = u32ObjectHandle;
    U32 RemainSize = gPtpObjectInfo.ObjectCompressedSize;

    if (u8UsbPort == USB_PORT_0)
    {
    #ifdef USB_PTP_ENABLE
        RemainSize -= drvUSBHost_PTP_GetCurGetObjOffset();
        while (RemainSize > 0)
        {
            U32 TransLen;

            if (RemainSize > 16384)
                TransLen = 16384;
            else
                TransLen = RemainSize;

            drvUSBHost_PTP_GetObjectData(PTP_GetObject, gPtpObjectInfo.ObjectCompressedSize,
                    ObjectHandle, drvUSBHost_PTP_GetCurGetObjOffset(), TransLen, BufAddr);

            RemainSize -= TransLen;
        }
    #endif
    }
    else if (u8UsbPort == USB_PORT_2)
    {
    #ifdef USB2_PTP_ENABLE
        RemainSize -= drvUSBHost_PTP_GetCurGetObjOffset_Port2();
        while (RemainSize > 0)
        {
            U32 TransLen;

            if (RemainSize > 16384)
                TransLen = 16384;
            else
                TransLen = RemainSize;

            drvUSBHost_PTP_GetObjectData_Port2(PTP_GetObject, gPtpObjectInfo.ObjectCompressedSize,
                    ObjectHandle, drvUSBHost_PTP_GetCurGetObjOffset_Port2(), TransLen, BufAddr);

            RemainSize -= TransLen;
        }
    #endif
    }
}

//Function_Name: drvUsbPTP_GetError( )
/*!  \brief Get the error code of PTP.

This function will try to get the error code of PTP library.

    \param u8UsbPort     The USB port number.

\return USB error code.
    #define HOST20_OK                              0x00
    #define HOST20_FAIL                            0x01
    #define HOST20_FATAL                      0x02
    #define HOST20_DEVICE_STALL             0x03
    #define HOST20_TRANSACTION_ERROR   0x04
*/
U8 drvUsbPTP_GetError(U8 u8UsbPort)
{
    if (u8UsbPort == USB_PORT_0)
    {
    #ifdef USB_PTP_ENABLE
        return drvUSBHost_PTP_GetError();
    #endif
    }
    else if (u8UsbPort == USB_PORT_2)
    {
    #ifdef USB2_PTP_ENABLE
        return drvUSBHost_PTP_GetError_Port2();
    #endif
    }

    return 0;   //HOST20_OK
}

#endif //#ifdef ENABLE_PTP

