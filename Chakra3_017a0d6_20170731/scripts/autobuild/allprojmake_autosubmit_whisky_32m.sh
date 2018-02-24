export CC=/usr/bin/gcc
cd ../../


cp config.tmpl .config -f

PROJ=R2_WHISKY_32M_ATSC make

rm -r Bin_R2_WHISKY*
rm -r Obj_R2_WHISKY*