#!/usr/bin/python

import os
import sys
import re
import struct
import crcmod

BOOTLOADER_SIZE = 0x10000

bLittleEndian = False
bCRC16Enable  = True

CRC16 = crcmod.mkCrcFun(0x18005, 0, 0)
CRC32 = crcmod.mkCrcFun(0x104C11DB7, 0, 0)
LZSS = "./scripts/lzss/lzss.out c "

FLAG_COMPRESS = 0x01

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

    return bin_map

def doPack(bin_align, file_align, magic, fn_elf, fn_res,binid_fn):
    dir = os.path.dirname(binid_fn)
    bin_id = parseBinIDInfo(binid_fn)
    f_elf = open(fn_elf, 'r+b', 0)

    f_res = open(fn_res, 'w', 0)
    f_res.close()

    f_res = open(fn_res, 'r+b', 0)


    data = f_elf.read()


    magic = int(magic, 16)
    magic = struct.pack("BBBBB",
                        (magic >> 32) & 0xFF,
                        (magic >> 24) & 0xFF,
                        (magic >> 16) & 0xFF,
                        (magic >> 8)  & 0xFF,
                        (magic >> 0)  & 0xFF)
    idx_magic = data.find(magic)
    if idx_magic < 0:
        sys.stderr.write('Could not find magic signature\n')
        return
    idx_count = idx_magic + len(magic)
    flash_leftsize = struct.unpack('>L', data[idx_count:idx_count+4])[0] # Get left flash size
    idx_count = idx_count + 4
    idx_item  = idx_count + 2
    count = 0

    tail_res=0

    while True:

        (id, ) = struct.unpack('>H', data[idx_item:idx_item+2])
        if id == 0xF000:
            break
        count = count + 1
        tail_res = (tail_res + (bin_align - 1)) & ~(bin_align - 1)

        (fn, rs, flags) = bin_id[id]

        try:
                if flags & FLAG_COMPRESS:
				    os.system(LZSS + dir + "/../" + fn + " " + dir + "/../" + fn + "c");
				    fn = fn + "c"
                b = open(dir + "/../" + fn, "rb")
                d = b.read()

                d += '\x00' * (8 - ((len(d) + 2) % 8))  # padding + CRC16
                d += struct.pack('>H', CRC16(d))

                print "%04X @ %06X %6X %X %s" % (id, tail_res, len(d), flags, fn)

                f_elf.seek(idx_item + 2)
                f_elf.write(struct.pack('>L', tail_res))
                f_elf.write(struct.pack('>L', len(d)))
                f_elf.write(struct.pack('>B', (flags & FLAG_COMPRESS) != 0))

                f_res.seek(tail_res,0)
                f_res.write(d)

                tail_res = tail_res + len(d)

                b.close()
        except IOError, e:
            sys.stderr.write(str(e) + '\n')
            quit(2)

        idx_item = idx_item + 11

    print '%s:\n\t0x%X octets (%f KB / %f MB)' % (fn_res, tail_res, tail_res / 1024.0, tail_res / 1024.0 / 1024.0)

    f_elf.seek(idx_count)
    f_elf.write(struct.pack('>H', count))
    f_elf.close()

    f_res.seek(0)
    crc = struct.pack('>L', CRC32(f_res.read()))
    f_res.write(crc)
    f_res.close()




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
        else:
            args.append(arg)

    bin_align = int(args[0])
    file_align = int(args[1])
    magic = args[2]
    fn_elf = args[3]
    fn_res = args[4]
    binid_fn = args[5]

    #print "%s %s %s %s %s" % (args[0], args[1], args[2], args[3], args[4])
    (z,y,x,w,v) = os.uname()
    #print "%s %s %s %s %s \n" % (z,y,x,w,v)
    if z[:6] == "CYGWIN":
		LZSS = "./scripts/lzss/lzss.exe c "
    else:
		LZSS = "./scripts/lzss/lzss.out c "

    doPack(bin_align, file_align, magic, fn_elf, fn_res, binid_fn)
