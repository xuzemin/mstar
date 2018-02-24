export CC=/usr/bin/gcc
cd ../../


cp config.tmpl .config -f

PROJ=R2_MELODY_ATV_MM_32MB make

rm -r Bin_R2_MELODY*
rm -r Obj_R2_MELODY*