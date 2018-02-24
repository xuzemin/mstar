#!/usr/bin/python

import os
import sys
import re
import struct
import crcmod

CRC32 = crcmod.mkCrcFun(0x104C11DB7, 0, 0)

if __name__ == '__main__':
    args = []

    for arg in sys.argv[1:]:
        l_arg = arg.lower()
        if l_arg == '-bigendian':
            bLittleEndian = False
        elif l_arg == '-littleendian':
            bLittleEndian = True
        elif l_arg == '-crc16enable':
            bCRC16Enable = True
        elif l_arg == '-crc16disable':
            bCRC16Enable = False
        elif l_arg == '-multiflash':
            bMultiFlash = True
        else:
            args.append(arg)

    dst_fn = args[0]
    f = open(dst_fn, 'r+b', 0)
    f.seek(0)
    f.read()
    tail = f.tell()
    f.seek(0)
    crc32 = CRC32(f.read(tail-4))
    crc = struct.pack('>L', crc32)
    print "crc32  %X" % (crc32)
    f.write(crc)

    f.close()