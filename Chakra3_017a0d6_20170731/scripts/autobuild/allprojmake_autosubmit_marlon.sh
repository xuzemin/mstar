export CC=/usr/bin/gcc
cd ../../


cp config.tmpl .config -f

PROJ=MIPS_MARLON_128M_ALL make

rm -r Bin_MIPS_MARLON*
rm -r Obj_MIPS_MARLON*