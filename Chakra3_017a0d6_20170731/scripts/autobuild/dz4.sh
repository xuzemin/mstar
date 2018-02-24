cd ../../


cp config.tmpl .config -f

PURE_PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/tools/bin/
export PATH=/tools/mips-sde-elf-gcc/bin:$PURE_PATH:$PATH

#==================================================================================

rm -rf Bin_* Obj_*

#-----------------------------------------------------------------------------------

#-----------------------------------------------------------------------------------
#---------- WHISKY ----------

PROJ=R2_WHISKY_128M_ATSC make

rm -rf Bin_* Obj_*

PROJ=R2_WHISKY_64M_ATSC make

rm -rf Bin_* Obj_*

PROJ=R2_WHISKY_ATV_MM_64MB make

rm -rf Bin_* Obj_*

#-----------------------------------------------------------------------------------
#---------- Melody ----------

PROJ=R2_MELODY_64M_ISDB make

rm -rf Bin_* Obj_*

PROJ=R2_MELODY_ATV_MM_32MB make

rm -rf Bin_* Obj_*

PROJ=R2_MELODY_ATV_MM_32MB_GAME make

rm -rf Bin_* Obj_*

PROJ=R2_MELODY_ATV_MM_64MB_GAME make

rm -rf Bin_* Obj_*
