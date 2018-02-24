cd ../../


cp config.tmpl .config -f

PURE_PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/tools/bin/
export PATH=/tools/mips-sde-elf-gcc/bin:$PURE_PATH:$PATH

#==================================================================================

rm -rf Bin_* Obj_*

#-----------------------------------------------------------------------------------


#-----------------------------------------------------------------------------------
#---------- MAYA ----------
PROJ=R2_MAYA_128M_ATSC_DVBS make
rm -r Bin_R2_MAYA*
rm -r Obj_R2_MAYA*

PROJ=R2_MAYA_128M_DVBT_DVBT2_DVBC_DVBS make
rm -r Bin_R2_MAYA*
rm -r Obj_R2_MAYA*

PROJ=R2_MAYA_128M_DTMB make
rm -r Bin_R2_MAYA*
rm -r Obj_R2_MAYA*

PROJ=R2_MAYA_128M_ISDB make
rm -r Bin_R2_MAYA*
rm -r Obj_R2_MAYA*

