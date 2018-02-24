# How to add a new project
# 1. increase iProjNumber
# 2. add the following project informaiton
#   projName[x]=R2_NASA_ZUI_32MB_ATVMM
#   boardType[x]=BD_MST195C_D01A_S_NASA
#   tunerType[x]=MxL_601SI_TUNER
#   swType[x]=SW_CONFIG_TRUNK_MILAN_128M_ALL

export CC=/usr/bin/gcc

cd ../../
rm -r -f BIN_MELODY_ALL
mkdir BIN_MELODY_ALL



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
iProjNumber=14

projName[0]=R2_MELODY_ATV_MM_64MB
boardType[0]=BD_MST242C_D01A_S
tunerType[0]=MxL_661SI_TUNER
swType[0]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[1]=R2_MELODY_ATV_MM_64MB
boardType[1]=BD_MST242B_D01A_S
tunerType[1]=MxL_661SI_TUNER
swType[1]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[2]=R2_MELODY_ATV_MM_32MB
boardType[2]=BD_MST242A_D01A_S
tunerType[2]=MxL_661SI_TUNER
swType[2]=SW_CONFIG_TRUNK_MELODY_32M_AtvMM

projName[3]=R2_MELODY_ATV_MM_64MB
boardType[3]=BD_MST096B_10ARU_15384
tunerType[3]=MxL_661SI_TUNER
swType[3]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[4]=R2_MELODY_ATV_MM_64MB
boardType[4]=BD_MST097B_10ARB_15384
tunerType[4]=MxL_661SI_TUNER
swType[4]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[5]=R2_MELODY_ATV_MM_64MB_AUTOTEST
boardType[5]=BD_MST242C_D01A_S
tunerType[5]=MxL_661SI_TUNER
swType[5]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[6]=R2_MELODY_64M_ISDB
boardType[6]=BD_MST106B_10ARU_16115_ISDB_MELODY
tunerType[6]=MxL_661SI_TUNER
swType[6]=SW_CONFIG_TRUNK_MELODY_64M_ISDB_SZ

projName[7]=R2_MELODY_ATV_MM_32MB
boardType[7]=BD_MST094B_20ARJ_16234
tunerType[7]=MxL_661SI_TUNER
swType[7]=SW_CONFIG_TRUNK_MELODY_32M_AtvMM

projName[8]=R2_MELODY_ATV_MM_32MB_GAME
boardType[8]=BD_MST094B_20ARJ_16234
tunerType[8]=MxL_661SI_TUNER
swType[8]=SW_CONFIG_TRUNK_MELODY_32M_AtvMM

projName[9]=R2_MELODY_ATV_MM_32MB_GAME
boardType[9]=BD_MST242A_D01A_S
tunerType[9]=MxL_661SI_TUNER
swType[9]=SW_CONFIG_TRUNK_MELODY_32M_AtvMM

projName[10]=R2_MELODY_ATV_MM_64MB_GAME
boardType[10]=BD_MST096B_10ARU_15384
tunerType[10]=MxL_661SI_TUNER
swType[10]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[11]=R2_MELODY_ATV_MM_64MB_GAME
boardType[11]=BD_MST097B_10ARB_15384
tunerType[11]=MxL_661SI_TUNER
swType[11]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[12]=R2_MELODY_ATV_MM_64MB_GAME
boardType[12]=BD_MST242B_D01A_S
tunerType[12]=MxL_661SI_TUNER
swType[12]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

projName[13]=R2_MELODY_ATV_MM_64MB_GAME
boardType[13]=BD_MST242C_D01A_S
tunerType[13]=MxL_661SI_TUNER
swType[13]=SW_CONFIG_TRUNK_MELODY_64M_AtvMM

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

    # Move bin folder to BIN_MELODY_ALL
    PROJ=${ProjName}
    mv -v Bin_${PROJ} Bin_${PROJ}_${BoardType}_${TunerType}
    mv -v Bin_R2_MELODY_* ./BIN_MELODY_ALL/
    rm -r Obj_${PROJ}

    iProjIndex=$(($iProjIndex+1))
done

exit 0
