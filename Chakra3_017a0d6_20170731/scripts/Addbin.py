

#!/usr/bin/env python

import os, time ,re ,string,sys ,math ,sys,mmap,struct
import pickle

def GetFileLength(f):
  if type(f) == file:
    return os.fstat(f.fileno())[6]
  if type(f) == str:
    return os.stat(f)[6]

def AddNULL():
   while( tsize < Offset_Addr ) :
      fout.write( '\0' )
      #pickle.dump(0, fout)
      tsize=tsize+1


if __name__ == '__main__':
    args = []
    for arg in sys.argv[1:]:
        args.append(arg)
        
print "Addbin:"
print 'source_file:',args[0],'  source_file:',args[1],' output_file:',args[2],'  Address(Hex):',args[3]

Offset_Addr=string.atoi(args[3],16)

fin1 = open(args[0],"rb")
fin2 = open(args[1],"rb")
#fout= open('temp.bin',"wb");
fout= open(args[2],"wb");


#-------------For Keyboad input------------#			
#Key_Input_Str=raw_input()  #Keyboard input

#print'\n',Key_Input_Str,'\n'

#Key_Input_Str_Split=re.split(" ",Key_Input_Str)
#print Key_Input_Str_Split[0]
#print Key_Input_Str_Split[1]
#print Key_Input_Str_Split[2]
#Offset_Addr=string.atoi(Key_Input_Str_Split[3],16)
#print 'Offset_Addr= ',Offset_Addr,'\n'

#fin1 = open(Key_Input_Str_Split[0],"rb")
#fin2 = open(Key_Input_Str_Split[1],"rb")
#fout= open(Key_Input_Str_Split[2],"wb");
#------------For Keyboad input END---------#

#------------Move bin Start----------------#
tsize=GetFileLength(fin1)
AP_Size=GetFileLength(fin2)

#print Key_Input_Str_Split[0],' size=',tsize,'   Address Offset=',Offset_Addr;
print args[0],' size=',tsize,'   Address Offset=',Offset_Addr;

if tsize<Offset_Addr :
  data=fin1.read()  #read all
  fout.write( data )
  x=0x00
  while( tsize < Offset_Addr ) :
    fout.write( '\0' )
    #pickle.dump(0, fout)
    tsize=tsize+1 
  data=fin2.read()
  fout.write( data );
else:
  print 'Warring : Source file bigger than address offset !!';
  data=fin1.read(Offset_Addr);
  fout.write(data)
  data=fin2.read()
  fout.write( data );

fin1.close()
fin2.close()
fout.close();
#------------Move bin end  ----------------#
print 'Insert AP.Bin file size to 0x200\n'
print 'AP.Bin file size = ',AP_Size;
Insert_Byte_Addr=0x200
fin3= open(args[2],"rb+");
#fin3= open('temp.bin',"rb+");
#fin3= open('temp_cc.bin',"rb");





amap = mmap.mmap(fin3.fileno(), 0)

amap.seek(Insert_Byte_Addr)
data = struct.pack('>i',AP_Size)
amap.write(data)
amap.seek(0)


#fout2.write(amap);

#aa=0xff
x=0;

amap.close()
fin3.close();
#fout2.close();


print 'Addbin Done';




