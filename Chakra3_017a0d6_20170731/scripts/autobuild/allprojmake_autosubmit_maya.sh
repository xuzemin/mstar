export CC=/usr/bin/gcc
cd ../../


cp config.tmpl .config -f

PROJ=R2_MAYA_128M_DVBT_DVBT2_DVBC_DVBS make

rm -r Bin_R2_MAYA*
rm -r Obj_R2_MAYA*