# How to add a new project
# 1. increase iProjNumber
# 2. add the following project informaiton  
#   projName[x]=R2_NASA_ZUI_32MB_ATVMM
#   boardType[x]=BD_MST195C_D01A_S_NASA
#   tunerType[x]=MxL_601SI_TUNER
#   swType[x]=SW_CONFIG_TRUNK_MARLON_128M_ALL

export CC=/usr/bin/gcc

cd ../../

rm -r -f BIN_MARLON_ALL
mkdir BIN_MARLON_ALL



#===============================================================

BOARD_DIR=./project/boarddef
SW_DIR=./project/swdef

CFG_FILE=./.config

VER_FILE=${BOARD_DIR}/Board

#=============================================================================

if [ "$1" == "" ]; then
	echo "No Version Number"
else
    cp ${VER_FILE}.h ${VER_FILE}.org
    sed -i 's/#define AUTO_BUILD_SW_VER.*/#define AUTO_BUILD_SW_VER                 '${1}'/g' ${VER_FILE}.h
fi


cp config.tmpl .config -f

#==================================================================================================
iProjNumber=17

projName[0]=MIPS_MARLON_128M_ALL
boardType[0]=BD_MST269B_D01A_S_MARLON
tunerType[0]=MxL_661SI_TUNER
swType[0]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[1]=MIPS_MARLON_64M_ALL
boardType[1]=BD_MST269E_D01A_S_MARLON
tunerType[1]=MxL_661SI_TUNER
swType[1]=SW_CONFIG_TRUNK_MARLON_64M_ALL

projName[2]=MIPS_MARLON_64M_DVBT_ISDB_SZ
boardType[2]=BD_MST118B_10ALU
tunerType[2]=SILAB_2151_TUNER
swType[2]=SW_CONFIG_TRUNK_MARLON_64M_ALL

projName[3]=MIPS_MARLON_128M_DVBT_SZ
boardType[3]=BD_MST120B_10ALS
tunerType[3]=SILAB_2151_TUNER
swType[3]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[4]=MIPS_MARLON_64M_DVBT_SZ
boardType[4]=BD_MST118B_10ALU
tunerType[4]=SILAB_2151_TUNER
swType[4]=SW_CONFIG_TRUNK_MARLON_64M_ALL

projName[5]=MIPS_MARLON_128M_DVBT_CERT1
boardType[5]=BD_MST120B_10ALS
tunerType[5]=SILAB_2151_TUNER
swType[5]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[6]=MIPS_MARLON_128M_DVBT_CERT2
boardType[6]=BD_MST120B_10ALS
tunerType[6]=SILAB_2151_TUNER
swType[6]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[7]=MIPS_MARLON_128M_DVBT_CERT3
boardType[7]=BD_MST120B_10ALS
tunerType[7]=SILAB_2151_TUNER
swType[7]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[8]=MIPS_MARLON_128M_DVBT_CERT4
boardType[8]=BD_MST120B_10ALS
tunerType[8]=SILAB_2151_TUNER
swType[8]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[9]=MIPS_MARLON_128M_DVBT_CERT5
boardType[9]=BD_MST120B_10ALS
tunerType[9]=SILAB_2151_TUNER
swType[9]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[10]=MIPS_MARLON_128M_DVBT_CERT6
boardType[10]=BD_MST120B_10ALS
tunerType[10]=SILAB_2151_TUNER
swType[10]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[11]=MIPS_MARLON_128M_DVBT_ASTRA_HD
boardType[11]=BD_MST120B_10ALS
tunerType[11]=SILAB_2151_TUNER
swType[11]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[12]=MIPS_MARLON_128M_DVBT_SGP_MDA
boardType[12]=BD_MST120B_10ALS
tunerType[12]=SILAB_2151_TUNER
swType[12]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[13]=MIPS_MARLON_128M_ALL_AUTOTEST
boardType[13]=BD_MST269B_D01A_S_MARLON
tunerType[13]=MxL_661SI_TUNER
swType[13]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[14]=MIPS_MARLON_128M_DVBT_SZ_STR
boardType[14]=BD_MST120B_10ALS
tunerType[14]=SILAB_2151_TUNER
swType[14]=SW_CONFIG_TRUNK_MARLON_128M_ALL

projName[15]=MIPS_MARLON_64M_ISDB_SZ
boardType[15]=BD_MST118B_10ALU
tunerType[15]=SILAB_2151_TUNER
swType[15]=SW_CONFIG_TRUNK_MARLON_64M_ALL

projName[16]=MIPS_MARLON_128M_DVBT_SZ
boardType[16]=BD_MST127B_10ALSA
tunerType[16]=SILAB_2151_TUNER
swType[16]=SW_CONFIG_TRUNK_MARLON_128M_ALL


iProjIndex=0

while [ "$iProjIndex" != "$iProjNumber" ]
#for iProjIndex in $(seq 1 3)
do

    echo "iProjIndex=$iProjIndex"

    # Get project name
    ProjName=${projName[$iProjIndex]}
    BoardType=${boardType[$iProjIndex]}
    TunerType=${tunerType[$iProjIndex]}
    BD_FILE=${BOARD_DIR}/${BoardType}.h
	SW_FILE=${SW_DIR}/${swType}.h
    
    echo "ProjName=$ProjName"

	  #change Board type and tuner type
	  sed -i 's/BOARD_TYPE_SEL ?=.*/BOARD_TYPE_SEL ?= '${BoardType}'/g' ${CFG_FILE}
	  sed -i 's/#define FRONTEND_TUNER_TYPE.*/#define FRONTEND_TUNER_TYPE             '${TunerType}'/g' ${BD_FILE}

    # Get project name and make    
    PROJ=${ProjName} make autobuild

    # Move bin folder to BIN_MARLON_ALL
    PROJ=${ProjName}
    mv -v Bin_${PROJ} Bin_${PROJ}_${BoardType}_${TunerType}
    mv -v Bin_MIPS_MARLON_* ./BIN_MARLON_ALL/
    rm -r Obj_${PROJ}
	
    iProjIndex=$(($iProjIndex+1))
done


# Move all bin folder
#mv -v Bin_R2_NASA_* ./BIN_MARLON_ALL/
#rm -r Bin_R2_NASA_*


cp config.tmpl .config -f

if [ "$1" == "" ]; then
	echo "No Version Number"
else
    # Recover board.h
    cp ${VER_FILE}.org ${VER_FILE}.h
    rm -r ${VER_FILE}.org
fi

exit 0
