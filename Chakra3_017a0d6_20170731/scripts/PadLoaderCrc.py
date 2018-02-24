#!/usr/bin/python

import os
import sys
import re
import struct
import crcmod

BOOTLOADER_SIZE = 0x10000
PM_CODE_SIZE = 0x10000     # The size of PM code is 64K bytes.
CHUNK_HEADER_SIZE = 0x80   # The size of chunk header is 128 bytes.

bLittleEndian = False
bCRC16Enable  = True
bMultiFlash = False

CRC16 = crcmod.mkCrcFun(0x18005, 0, 0)
CRC32 = crcmod.mkCrcFun(0x104C11DB7, 0, 0)
LZSS = "./scripts/lzss/lzss.out c "

FLAG_COMPRESS = 0x01
FLAG_FLASH2   = 0x02

class SecondFlash(object):
    def __init__(self, filename, base=0):
        self.filename = filename
        self.base = base
        self.bin = []

    def add(self, id):
        self.bin.append(id)

def getFlashTable2(data):
    magic = struct.pack("BBBB", 0x39, 0xB6, 0x5B, 0x53)
    tbl2 = data.find(magic)
    if tbl2 < 0:
        return None
    for i in '\x01' + data[tbl2+4:tbl2+10]:
        n = tbl2 + 10
        while True:
            len = struct.unpack('>H', data[n:n+2])[0]
            if len == 0xFFFF:
                n += 2
                break
            len >>= 14
            n += (2 + (len + 1) * 2)
    print "n "
    print n
    return data[tbl2:n]


def parseBinIDInfo(binid_fn):
    bin_map = {}
    define = re.compile('^\s*#define\s+(\S+)\s+(\S+)\s+//~([0-9]+)KB(\+[0-9]*)?\s+//@(\S+)\s+(..*)?')
    f_binid = open(binid_fn)
    for l in f_binid:
        m = define.match(l)
        if (m):
            id = int(m.group(2).strip(), 16)
            len = int(m.group(3), 10) * 1024
            if m.group(4) is not None:
                len = len + int(m.group(4), 10)
            fn = m.group(5).strip().replace('\\', '/')
            flags = 0
            if m.group(6) is not None:
                if m.group(6).find('-c') >= 0:
                    flags |= FLAG_COMPRESS
                if m.group(6).find('-2') >= 0:
                    flags |= FLAG_FLASH2
            bin_map[id] = (fn, len, flags)
            print 'bin_map %x %s %x %x' % (id, fn, len, flags)

    return bin_map

def padCrc(file_align, magic, dst_fn):
    print "file_align %d" % (file_align)
    f = open(dst_fn, 'r+b', 0)

    f.seek(0)
    data = f.read()
    tail = f.tell()
    print "org tail 0x%X" % (tail)
    ap_offset = ((tail + file_align - 1) / file_align) * file_align
    ap_offset_bytes = struct.pack("BBBB",
                        (ap_offset >> 0) & 0xFF,
                        (ap_offset >> 8) & 0xFF,
                        (ap_offset >> 16)  & 0xFF,
                        (ap_offset >> 24)  & 0xFF)
    print "AP offset 0x%X" % (ap_offset)
    f.seek((BOOTLOADER_SIZE + PM_CODE_SIZE + 0x18))
    f.write(ap_offset_bytes)

    fAP = open(ap_c_fn, 'r+b', 0)
    datac = fAP.read()
    len_of_AP = fAP.tell()
    print "len_of_AP: 0x%X" % (len_of_AP)
    fAP.close()

    f.seek(0)
    data = f.read()
    print "lendata 0x%X" % (len(data))
    f.seek(BOOTLOADER_SIZE)
    data = f.read(len(data) - BOOTLOADER_SIZE - 2)
    crc = struct.pack('>H', CRC16(data))
    print "crc16  %X" % (CRC16(data))
    f.write(crc)

    tail = f.tell()
    print "org tail 0x%X" % (tail)
    tail_new = ((tail + file_align - 1) / file_align) * file_align
    print "new tail 0x%X" % (tail_new)
    paddedZeros = '\x00' * (tail_new - tail)
    f.write(paddedZeros)

    f.seek((BOOTLOADER_SIZE + PM_CODE_SIZE + CHUNK_HEADER_SIZE))
    data = f.read(len_of_AP)
    crc32 = CRC32(data)
    crc32_bytes = struct.pack("BBBB",
                        (crc32 >> 0) & 0xFF,
                        (crc32 >> 8) & 0xFF,
                        (crc32 >> 16)  & 0xFF,
                        (crc32 >> 24)  & 0xFF)
    print "crc32 of AP %X" % (crc32)
    f.seek((BOOTLOADER_SIZE + PM_CODE_SIZE + 0x14))
    f.write(crc32_bytes)

    f.close()

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

    bin_align = int(args[0])
    file_align = int(args[1])
    magic = args[2]
    dst_fn = args[3]
    binid_fn = args[4]
    ImgInfo_Offset = int(args[5])
    ap_c_fn = args[6]
    flash2_bin = []

    print "args %s %s %s %s %s" % (args[0], args[1], args[2], args[3], args[4])
    (z,y,x,w,v) = os.uname()
    print "os_uname %s %s %s %s %s \n" % (z,y,x,w,v)
    if z[:5] == "CYGWIN":
		LZSS = "./scripts/lzss/lzss.exe c "
    else:
		LZSS = "./scripts/lzss/lzss.out c "

    # doPack(bin_align, file_align, magic, dst_fn, binid_fn)
    padCrc(file_align, magic, dst_fn)
