1, copy all the files into a directory;

2, to compile nmicfg.c, nmituner_api.c, nmitnr.c is ok;

3, users need to modify nmiport.c and nmitypes.h, nmituner_api.c to adapt to specific platforms, 
for different platforms, the main difference is data types and head files, change is very small.
nmiport.c: define delay and IIC functions;
nmitypes.h: define data types and include OS related head files;
nmituner_api.c: define tuner driver interfaces to upper layer;

4, main.c is a calling sequence sample;

5, all other .c files and head files will be included automatically, users needn't mind it;

6, this version based on NMI_RELEASE_VER2.1.2.5_01_10_2012 and passed compiling on VS2008;

7, this verion is non-kernel veriosn.
