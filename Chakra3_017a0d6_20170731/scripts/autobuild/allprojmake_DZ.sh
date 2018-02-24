cd ../../


cp config.tmpl .config -f

PURE_PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/tools/bin/
export PATH=/tools/mips-sde-elf-gcc/bin:$PURE_PATH:$PATH

#==================================================================================

rm -rf Bin_* Obj_*

#-----------------------------------------------------------------------------------
#---------- Marlon ------------

PROJ=MIPS_MARLON_128M_ALL make
rm -rf Bin_*
rm -rf Obj_*

PROJ=MIPS_MARLON_128M_ALL_AUTOTEST make
rm -rf Bin_*
rm -rf Obj_*

#-----------------------------------------------------------------------------------
#---------- Melody -------------
PROJ=R2_MELODY_ATV_MM_64MB make
rm -rf Bin_*
rm -rf Obj_*

PROJ=R2_MELODY_64M_ISDB make
rm -rf Bin_*
rm -rf Obj_*

#-----------------------------------------------------------------------------------
#---------- EULER ----------

#PROJ=R2_EULER_ZUI_128MB_DVBT make
#rm -r Bin_R2_EULER*
#rm -r Obj_R2_EULER*

#-----------------------------------------------------------------------------------
#---------- EMERALD ----------

PROJ=MIPS_EMERALD_ZUI_MM_128MB_DVBT make
rm -r Bin_MIPS_EMERALD_*
rm -r Obj_MIPS_EMERALD_*

#-----------------------------------------------------------------------------------
#---------- EDEN ----------

#PROJ=R2_EDEN_ZUI_64MB_ATVMM make
PROJ=R2_EDEN_64MB_ATSC make
rm -rf Bin_* Obj_*

#-----------------------------------------------------------------------------------
#---------- NASA ----------
PROJ=R2_NASA_ZUI_64MB_DTMB make
rm -r Bin_R2_NASA*
rm -r Obj_R2_NASA*

#-----------------------------------------------------------------------------------
#---------- MILAN ----------

PROJ=MIPS_MILAN_ZUI_MM_64MB_ALL make
rm -r Bin_MIPS_MILAN*
rm -r Obj_MIPS_MILAN*

PROJ=MIPS_MILAN_ZUI_MM_128MB_ALL make
rm -r Bin_MIPS_MILAN*
rm -r Obj_MIPS_MILAN*

PROJ=MIPS_MILAN_ZUI_MM_128MB_ALL_SZ_BLOADER make
rm -r Bin_MIPS_MILAN*
rm -r Obj_MIPS_MILAN*


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


#-----------------------------------------------------------------------------------
#---------- WHISKY ----------

PROJ=R2_WHISKY_128M_ATSC make
rm -r Bin_R2_WHISKY*
rm -r Obj_R2_WHISKY*

PROJ=R2_WHISKY_64M_ATSC make
rm -r Bin_R2_WHISKY*
rm -r Obj_R2_WHISKY*

PROJ=R2_WHISKY_64M_ATSC_AUTOTEST make
rm -r Bin_R2_WHISKY*
rm -r Obj_R2_WHISKY*

