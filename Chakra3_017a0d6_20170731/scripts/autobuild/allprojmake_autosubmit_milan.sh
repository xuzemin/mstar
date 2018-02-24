export CC=/usr/bin/gcc
cd ../../


cp config.tmpl .config -f

PROJ=MIPS_MILAN_ZUI_MM_128MB_ALL make

rm -r Bin_MIPS_MILAN*
rm -r Obj_MIPS_MILAN*