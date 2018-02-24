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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "Wrapper_Common.h"
#include "N51FS_Wrapper.h"
#include "stream.h"
#include "linux_51fs_wrap.h"
#include "linux_usb_mount.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <locale.h>

#define MK_DEV_NODE 0



#define USB_MNT_DBG(x) do{ x;}while(0)

const char *GetFirstField(const char *pStr, long *pFieldLen)
{
    const char *pFieldHeader = pStr;

   while(1)
    {
       switch(*pFieldHeader)
       {
          case ' ':
          case '\t':
          case 0x0D:
          case 0x0A:
            pFieldHeader++;
            continue;
          default:
            break;
        }
       break;
    }

   if(pFieldLen)
   {
      *pFieldLen = 0;
       while(1)
       {
           switch(pFieldHeader[*pFieldLen])
           {
               case 0:
               case ' ':
               case '\t':
               case 0x0D:
               case 0x0A:
                 break;
              default:
                 (*pFieldLen)++;
                 continue;
           }
           break;
       }
   }

   return pFieldHeader;

}


int  MountPointDevStatus(const char *dev_name, const char *mountpoint)
{
   char linebuf[256];
   STREAM_HANDLE handle;
   U32 readLen;

   FILE * fp = fopen("/proc/mounts", "r");
   if(fp == NULL)
   {
        WPFS_DBG("/proc/mounts!\n");
        return MNT_IO_ERROR;
   }

   if((handle=Init_streamFile(fp)) == INVALID_STREAM_HANDLE)
   {
       WPFS_DBG("Failed to read file /proc/mounts!\n");
       fclose(fp);
       return MNT_IO_ERROR;
   }

   while(!IsStreamEnd(handle))
   {
       readLen = GetOneLine(handle, linebuf, 256);
      // USB_ST_DBG(printf(" ReadLine:%s\n", linebuf));
       if(readLen)
       {
           if(strstr(linebuf, mountpoint))
            {
              // WPFS_DBG("   mount point(%s) busy!\n", mountpoint);
               Close_stream(handle);
               fclose(fp);
               return MNT_MOUNTPOINT_BUSY;
            }
           if(strstr(linebuf, dev_name))
            {
               //WPFS_DBG("   device(%s) busy!\n", dev_name);
               Close_stream(handle);
               fclose(fp);
               return MNT_DEVICE_BUSY;
            }
        }
    }
   return  MNT_SUCCESS;
}
#if 0
int usb_ntfs3g_mount(const char *dev_name, const char *mount_point, bool bReadOnly)
{
        int retryCnt = 0;
        pid_t pid = fork();
        int res, status;
        if(pid < 0)
            return -1;
        if(pid == 0)
        {
            execl("/bin/ntfs-3g", "/bin/ntfs-3g", dev_name , mount_point, "-o", "locale=en_GB.UTF-8", bReadOnly?"ro":NULL, NULL);
            printf("error, ntfs-3g bin not exists!!\n");
            exit(-1);
        }
        else
        {
           while(retryCnt++ < 1000)
           {
                res = waitpid(pid, &status, WNOHANG);
                if(res != 0 && res !=pid)
                {
                     usleep(200*1000);
                    if(MountPointDevStatus(dev_name, mount_point)  != MNT_SUCCESS)
                   {
                        WPFS_DBG("ntfs-3g mount success on %s\n", dev_name);
                         return 0;
                   }
                    WPFS_DBG("ntfs-3g return %d\n", res);
                    return -1;
                }

                if(res==pid && WEXITSTATUS(status) != 0)
                {
                    WPFS_DBG("ntfs3g return failed%d\n", WEXITSTATUS(status));
                    return -1;
                }
                if(MountPointDevStatus(dev_name, mount_point)  != MNT_SUCCESS)
                {
                    WPFS_DBG("ntfs-3g mount success on %s\n", dev_name);
                    return 0;
                }
                if(res==pid &&  WEXITSTATUS(status) == 0)
                {
                    printf("Serious warning , unknow error!!!!\n");
                 }
                usleep(200*1000);
           }
        }
        return -1;
}
#endif

int usb_mount_dev(const char *devicefolder, const char *dev_name)
{

   U32 usbBusNO,ProcBusNO;
   char mountpoint[64];
   char linebuf[256];
   char *devtypefname="/proc/bus/usb/devices";
   char hotpoint[64];
   char dev_pathname[64];
   long vfsflags = 0;
   int usb_major, usb_minor;
   int len;
   int res;
   FILE *fp;
   FILE *fpdev;
   STREAM_HANDLE handle;
   U32 readLen;
   U8 deviceType;
   BOOLEAN isCDROM_FS = (dev_name[0]=='s' && dev_name[1]=='r');

   int BusMatch = 0;
   int complete = 0;
   deviceType = NO_DEVICE;

     if(strstr(devicefolder, "Mstar-ehci-2"))
            usbBusNO = 2, ProcBusNO = 1;
     else if(strstr(devicefolder, "Mstar-ehci-1"))
            usbBusNO = 1, ProcBusNO = 2;
     else
            usbBusNO = 0, ProcBusNO = 0;
#if 0	//old way 
     if(strstr(devicefolder, "/usb2/"))
            deviceType = USB20_DEVICE;
     else
            deviceType = USB11_DEVICE;
#endif

    fpdev = fopen(devtypefname, "r");
    if(fpdev == NULL)
    {
        printf("failed to open /proc/bus/usb/devices");
        complete = 0;
    }
    else
    {
        if((handle=Init_streamFile(fpdev)) == INVALID_STREAM_HANDLE)
        {
            printf("Failed to read file /proc/bus/usb/device!\n");
        }
        else
        {
            while(!IsStreamEnd(handle))
            {
                readLen = GetOneLine(handle, linebuf, 256);
                if(readLen)
                {
                    sprintf(hotpoint,"Bus=0%1d",ProcBusNO);//Check Bus No
                    if(strstr(linebuf, hotpoint))
                    {
                        BusMatch = 1;
                        complete = 0;
                    }

                    sprintf(hotpoint,"Ver= 1.10");//Check speed
                    if(strstr(linebuf, hotpoint))
                    {
                        deviceType = USB11_DEVICE;
                    }

                    sprintf(hotpoint,"Ver= 2.00");
                    if(strstr(linebuf, hotpoint))
                    {
                        deviceType = USB20_DEVICE;
                    }

                    sprintf(hotpoint,"I:");      //Check device type
                    if(strstr(linebuf, hotpoint))
                    {
                        sprintf(hotpoint,"usb-storage");
                        if(strstr(linebuf, hotpoint))
                        {
                            if(BusMatch == 1 && deviceType != NO_DEVICE)
                            {
                                complete = 1;
                                break;
                            }
                        }
                        else 
                        {
                            complete = 0;
                            BusMatch = 0;
                        }
                    }
                }

            }
        }
        fclose(fpdev);
    }


    if(complete == 0)
    {
        if(strstr(devicefolder, "/usb2/"))
            deviceType = USB20_DEVICE;
        else
            deviceType = USB11_DEVICE;
    }

    //create device node
    sprintf(linebuf, "%s/dev", devicefolder);
    fp = fopen(linebuf, "r");
    if(fp == NULL)
    {
        WPFS_DBG("failed to open %s!\n", linebuf);
        return MNT_IO_ERROR;
    }
    len =  fread( linebuf, 1, 64, fp);
    fclose(fp);
    if(len <= 0)
    {
            WPFS_DBG("failed to open major,minor number of dev\n");
            return MNT_IO_ERROR;
    }
    linebuf[len] = 0;
    if(sscanf(linebuf, "%u:%u", &usb_major, &usb_minor) != 2)
    {
            WPFS_DBG("failed to parse major,minor number of dev\n");
            return MNT_IO_ERROR;
    }
    //LOG(" current device usb bus id is %d, device ID is (%d, %d)\n", usbBusNO, usb_major, usb_minor);

    if(usbBusNO == 0)
    {
        WPFS_DBG(" Failed to detect USB bus from uevent for %s:%s\n", devicefolder, dev_name);
        return MNT_IO_ERROR;
    }


   sprintf(dev_pathname, "/dev/%s", dev_name);
   if(isCDROM_FS || strlen(dev_name)>3)
   {
       sprintf(mountpoint, "/mnt/%s", dev_name);
   }
   else
   {
       sprintf(mountpoint, "/mnt/%s1", dev_name);
   }
#if MK_DEV_NODE
   if (mknod(dev_pathname, 0660 | S_IFBLK, makedev(usb_major, usb_minor)) && errno != EEXIST)
   {
          LOG(" Failed to create device node\n");
          return MNT_IO_ERROR;
   }
   mkdir("/mnt", 0777);
   mkdir(mountpoint, 0777);
#endif


      if((res = MountPointDevStatus(dev_name, mountpoint)) != MNT_SUCCESS)
      {
           printf("device or mount point busy, return %d\n", res);
           return res;
      }
      
    //printf(" Try to mount %s at %s\n",dev_pathname,mountpoint);
    setlocale(LC_ALL,"en_US.UTF-8");
    
/*
    Because Linux UDF doesn't provide VAT write support which is needed for re-writing  WORM disks, we mount cdrom fs as readonly by default
*/
    if(isCDROM_FS)
          vfsflags = MS_RDONLY;
    
   //mount it now
    while(1){
          int rc = mount(dev_pathname, mountpoint, "vfat", vfsflags, "iocharset=utf8,shortname=winnt");//vfat may also be a valid filesystem on CDROM, so we check it
          //for both CDROM & normal block devices

             //LOG(" Try to mount %s at %s as vfat %s, result%d\n", dev_pathname, mountpoint,
                       //   (vfsflags & MS_RDONLY) ?"ro":"rw", rc);
             if(rc)
             {
                 if(isCDROM_FS)
                 {       
                        
                          rc = mount(dev_pathname, mountpoint, "udf", vfsflags, "iocharset=utf8");
                          if(rc==0)
                          {
                              FS_NotifyDrvMount(usbBusNO, usb_major, usb_minor, dev_name, mountpoint, FILE_SYSTEM_TYPE_UDF, FILE_SYSTEM_MOUNT_RO, deviceType);
                          }
                          else
                          {
                               rc = mount(dev_pathname, mountpoint, "iso9660", vfsflags, "iocharset=utf8");
                              if(rc==0)
                              {
                                     FS_NotifyDrvMount(usbBusNO, usb_major, usb_minor, dev_name, mountpoint, FILE_SYSTEM_TYPE_ISO9660, FILE_SYSTEM_MOUNT_RO, deviceType);
                              }
                         }
                }
                else
                {
                     rc = mount(dev_pathname, mountpoint, "ntfs3g", vfsflags, "");
                     if(rc)
                     {
                           rc = mount(dev_pathname, mountpoint, "ext3", vfsflags, "");
                           if(rc==0)
                           {
                               FS_NotifyDrvMount(usbBusNO, usb_major, usb_minor, dev_name, mountpoint, FILE_SYSTEM_TYPE_EXT3,(vfsflags&MS_RDONLY)?FILE_SYSTEM_MOUNT_RO:FILE_SYSTEM_MOUNT_RW, deviceType);
                           }
                    }
                    else
                    {
                       //currently fake as fat
                       FS_NotifyDrvMount(usbBusNO, usb_major, usb_minor, dev_name, mountpoint, FILE_SYSTEM_TYPE_NTFS,(vfsflags&MS_RDONLY)?FILE_SYSTEM_MOUNT_RO:FILE_SYSTEM_MOUNT_RW, deviceType);
                    }
               }
                 //LOG(" Try to mount %s at %s as ntfs (%s), result%d\n", dev_pathname, mountpoint,
                   // (vfsflags & MS_RDONLY) ?"ro":"rw", rc);
             }
             else
             {
                   FS_NotifyDrvMount(usbBusNO, usb_major, usb_minor, dev_name, mountpoint, FILE_SYSTEM_TYPE_FAT,
                                  (vfsflags&MS_RDONLY)?FILE_SYSTEM_MOUNT_RO:FILE_SYSTEM_MOUNT_RW, deviceType);
             }
        if (!rc || (vfsflags & MS_RDONLY) || (errno != EACCES && errno != EROFS))
            {
                   if(rc == 0)
                         return MNT_SUCCESS;
                   else
                        return MNT_UNKNOW_ERROR;
            }
        vfsflags |= MS_RDONLY;
    }

      return MNT_UNKNOW_ERROR;

}

int usb_umount_dev( const char *dev_name)
{
   STREAM_HANDLE handle;
   U32 readLen;
   char mountpoint[64]={0};
   char dev_pathname[64]={0};
   char linebuf[256];
   FILE *fp;
   static char tmpbuf[256];
   sprintf(tmpbuf, "/dev/%s ", dev_name);



   fp = fopen("/proc/mounts", "r");
   if(fp == NULL)
   {
        WPFS_DBG("/proc/mounts!\n");
        return MNT_UNKNOW_ERROR;
   }

   if((handle=Init_streamFile(fp)) == INVALID_STREAM_HANDLE)
   {
       WPFS_DBG("Failed to read file /proc/mounts!\n");
       fclose(fp);
       return MNT_IO_ERROR;
   }

   while(!IsStreamEnd(handle))
   {
       readLen = GetOneLine(handle, linebuf, 256);
      // USB_ST_DBG(printf(" ReadLine:%s\n", linebuf));
       if(readLen)
       {
           if(strstr(linebuf, tmpbuf))
            {
 
                    const char *pFieldHeader = linebuf;
                    long fieldLen;
                    int res;

                    pFieldHeader = GetFirstField(pFieldHeader, &fieldLen);
                    memcpy(dev_pathname, pFieldHeader, fieldLen);
                    dev_pathname[fieldLen] = 0;

                    pFieldHeader = GetFirstField(pFieldHeader+fieldLen, &fieldLen);
                    memcpy(mountpoint, pFieldHeader, fieldLen);
                    mountpoint[fieldLen] = 0;
                    //WPFS_DBG("   find mount point(%s) of %s!\n", mountpoint, dev_pathname);
                    Close_stream(handle);
                    fclose(fp);
                    sync();
                    // WPFS_DBG("   umount point(%s), result:", mountpoint);
                    FS_NotifyDrvUnMount(mountpoint);
                    res = umount2(mountpoint, MNT_FORCE);
              //      WPFS_DBG(" %d!\n", res);
                    return MNT_SUCCESS;
            }
        }
    }
    Close_stream(handle);
    fclose(fp);

    return MNT_MOUNTPOINT_NOTFOUND;

}

