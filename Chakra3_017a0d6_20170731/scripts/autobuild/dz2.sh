cd ../../


cp config.tmpl .config -f

PURE_PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games:/tools/bin/
export PATH=/tools/mips-sde-elf-gcc/bin:$PURE_PATH:$PATH

#==================================================================================

rm -rf Bin_* Obj_*

#-----------------------------------------------------------------------------------
#---------- MARLON ----------

PROJ=MIPS_MARLON_128M_DVBT_SZ make

rm -rf Bin_* Obj_*

PROJ=MIPS_MARLON_64M_DVBT_SZ make

rm -rf Bin_* Obj_*

PROJ=MIPS_MARLON_128M_DVBT_SZ_BLOADER make

rm -rf Bin_* Obj_*

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


